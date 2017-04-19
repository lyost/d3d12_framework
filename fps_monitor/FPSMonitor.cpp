#include <sstream>
#include <iomanip>
#include "FPSMonitor.h"
#include "Graphics/VertexDeclarations/Vertex_PositionTexture.h"
#include "Graphics/Textures/TextureUploadBuffer.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

FPSMonitor::FPSMonitor(GraphicsCore& graphics, UINT sample_size, const map<char, vector<float> >& lookup_table, UINT width, UINT height, const vector<UINT8>& bytes, UINT char_width, UINT char_height)
:m_next_sample_index(0),
 m_char_width_px(char_width),
 m_char_height_px(char_height)
{
  m_samples.resize(sample_size, 0);

  try
  {
    RootSignatureConfig* config = RootSignatureConfig::CreateD3D12(2, 1);
    config->SetStageAccess(true, true, false, false, false, true, false);
    config->SetParamAsDescriptorTable(0, 1, SHADER_VISIBILITY_PIXEL);
    config->SetRangeAsShaderResourceView(0, 0, 1, 0, 0);
    config->SetParamAsConstantBufferView(1, 0, 0, SHADER_VISIBILITY_VERTEX);
    config->SetSampler(0, TEXTURE_FILTER_MIN_MAG_MIP_LINEAR, TEXTURE_ADDRESS_MODE_WRAP, TEXTURE_ADDRESS_MODE_WRAP, TEXTURE_ADDRESS_MODE_WRAP, 0, 1, COMPARISON_FUNC_NEVER, BORDER_COLOR_TRANSPARENT_BLACK,
      0, 0, 0, 0, SHADER_VISIBILITY_PIXEL);
    m_root_sig = RootSignature::CreateD3D12(graphics, *config);
    delete config;
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create root signature:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  Shader* vertex_shader;
  Shader* pixel_shader;
  InputLayout* input_layout;
  try
  {
    vertex_shader = Shader::LoadD3D12("fps_monitor_vs.cso");
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to load vertex shader:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    pixel_shader = Shader::LoadD3D12("fps_monitor_ps.cso");
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to load pixel shader:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  try
  {
    input_layout = InputLayout::CreateD3D12(3);
    input_layout->SetNextElement(SEM_POSITION, 0, R32G32_FLOAT, 0, false);
    input_layout->SetNextElement(SEM_TEXCOORD, 0, R32G32_FLOAT, 0, false);
    input_layout->SetNextElement(SEM_TEXCOORD, 1, R32_FLOAT,    0, false);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create input layout:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  try
  {
    RenderTargetViewConfig* rtv_config = RenderTargetViewConfig::CreateD3D12(1);
    rtv_config->SetAlphaToCoverageEnable(false);
    rtv_config->SetIndependentBlendEnable(false);
    rtv_config->SetFormat(0, RTVF_R8G8B8A8_UNORM);
    m_pipeline = Pipeline::CreateD3D12(graphics, *input_layout, TOPOLOGY_TRIANGLE, *vertex_shader, NULL, *pixel_shader, *rtv_config, *m_root_sig);
    delete rtv_config;
    delete input_layout;
    delete pixel_shader;
    delete vertex_shader;
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create pipeline:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the scissor rect that matches the viewport
  Viewport full_viewport = graphics.GetDefaultViewport();
  m_scissor_rect = ViewportToScissorRect(graphics.GetDefaultViewport());

  // compute clip space char width and height
  m_char_width  = char_width  / full_viewport.width;
  m_char_height = char_height / full_viewport.height;

  CommandList* command_list;
  try
  {
    command_list = CommandList::CreateD3D12Direct(graphics, m_pipeline);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create command list:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the vertex buffer
  const UINT num_chars = CHARS_PER_ROW * NUM_ROWS;
  for (UINT i = 0; i < num_chars; i++)
  {
    float x = (i % CHARS_PER_ROW) * m_char_width;
    float y = (i / CHARS_PER_ROW) * -m_char_height;
    m_vertex_buffer_data[i * VERTS_PER_CHAR    ] = { XMFLOAT2(-1 + x,                y),                 XMFLOAT2(0.0f, 0.0f), 0.0f };
    m_vertex_buffer_data[i * VERTS_PER_CHAR + 1] = { XMFLOAT2(-1 + x,                y - m_char_height), XMFLOAT2(0.0f, 1.0f), 0.0f };
    m_vertex_buffer_data[i * VERTS_PER_CHAR + 2] = { XMFLOAT2(-1 + x + m_char_width, y - m_char_height), XMFLOAT2(1.0f, 1.0f), 0.0f };
    m_vertex_buffer_data[i * VERTS_PER_CHAR + 3] = { XMFLOAT2(-1 + x + m_char_width, y),                 XMFLOAT2(1.0f, 0.0f), 0.0f };
  }
  try
  {
    m_verts = VertexBuffer_Custom::CreateD3D12(graphics, VERTS_PER_CHAR * num_chars, sizeof(VertexBufferEntry), m_vertex_buffer_data);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create vertex buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the index buffer
  WORD indices[num_chars * INDICES_PER_CHAR];
  for (UINT i = 0; i < num_chars; i++)
  {
    indices[i * INDICES_PER_CHAR    ] = i * VERTS_PER_CHAR;
    indices[i * INDICES_PER_CHAR + 1] = i * VERTS_PER_CHAR + 2;
    indices[i * INDICES_PER_CHAR + 2] = i * VERTS_PER_CHAR + 1;
    indices[i * INDICES_PER_CHAR + 3] = i * VERTS_PER_CHAR;
    indices[i * INDICES_PER_CHAR + 4] = i * VERTS_PER_CHAR + 3;
    indices[i * INDICES_PER_CHAR + 5] = i * VERTS_PER_CHAR + 2;
  }
  try
  {
    m_indices = IndexBuffer16::CreateD3D12(graphics, ARRAYSIZE(indices), indices);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create index buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create vertex buffer array
  try
  {
    m_vert_array = VertexBufferArray::CreateD3D12(1);
    m_vert_array->Set(0, *m_verts);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create vertex buffer array:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the descriptor heap
  try
  {
    m_shader_buffer_heap = ShaderResourceDescHeap::CreateD3D12(graphics, 2);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create resource descriptor heap:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the constant buffer
  try
  {
    const UINT buffer_size = (UINT)(sizeof(float) * 4 * lookup_table.size());
    m_lookup_table = ConstantBuffer::CreateD3D12(graphics, *m_shader_buffer_heap, buffer_size);

    float* table = new float[buffer_size];
    float* pos = table;
    map<char, vector<float> >::const_iterator lookup_it = lookup_table.begin();
    UINT i = 0;
    while (lookup_it != lookup_table.end())
    {
      m_key_to_index.insert(make_pair(lookup_it->first, i));
      vector<float>::const_iterator uv_it = lookup_it->second.begin();
      while (uv_it != lookup_it->second.end())
      {
        *pos = *uv_it;
        ++pos;

        ++uv_it;
      }

      ++lookup_it;
      ++i;
    }

    m_lookup_table->Upload(table, 0, buffer_size);
    
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create constant buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the heap array
  try
  {
    m_heap_array = HeapArray::CreateD3D12(1);
    m_heap_array->SetHeap(0, *m_shader_buffer_heap);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create heap array:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the texture
  try
  {
    m_font = Texture2D::CreateD3D12(graphics, *m_shader_buffer_heap, width, height, R8B8G8A8_UNORM);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  TextureUploadBuffer* upload_texture;
  try
  {
    upload_texture = TextureUploadBuffer::CreateD3D12(graphics, *m_font);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture upload buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // start uploading the texture
  try
  {
    upload_texture->PrepUpload(graphics, *command_list, *m_font, bytes);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // finish uploading the textures
  try
  {
    command_list->Close();
    graphics.ExecuteCommandList(*command_list);
    graphics.WaitOnFence();
    delete command_list;
    delete upload_texture;
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to finish uploading textures:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

FPSMonitor::~FPSMonitor()
{
  delete m_font;
  delete m_lookup_table;
  delete m_root_sig;
  delete m_pipeline;
  delete m_vert_array;
  delete m_verts;
  delete m_indices;
  delete m_shader_buffer_heap;
  delete m_heap_array;
}

void FPSMonitor::Update(UINT ms)
{
  m_samples[m_next_sample_index] = ms;
  m_next_sample_index = (m_next_sample_index + 1) % m_samples.size();

  UINT ms_min = UINT_MAX;
  UINT ms_max = 0;
  UINT ms_total = 0;
  vector<UINT>::const_iterator sample_it = m_samples.begin();
  while (sample_it != m_samples.end())
  {
    UINT sample = *sample_it;
    if (sample < ms_min)
    {
      ms_min = sample;
    }
    if (sample > ms_max)
    {
      ms_max = sample;
    }
    ms_total += sample;

    ++sample_it;
  }

  float fps_min = 1 / (ms_max / 1000.0f);
  float fps_max = 1 / (ms_min / 1000.0f);
  float fps_avg = 1 / (ms_total / (float)m_samples.size() / 1000.0f);

  // update the instance buffer data to contain the equivalent of "Avg 000.0", "Min 000.0", and "Max 000.0"
  const UINT num_rows = 3;
  const UINT chars_per_row = 9;
  const UINT num_chars = chars_per_row * num_rows;
  ostringstream out;
  out << fixed << setprecision(1) << "Avg ";
  if (ms_total == 0 || fps_avg >= 1000)
  {
    out << "---.-";
  }
  else
  {
    out << setw(5) << fps_avg;
  }
  out << "Min ";
  if (ms_max == 0 || fps_min >= 1000)
  {
    out << "---.-";
  }
  else
  {
    out << setw(5) << fps_min;
  }
  out << "Max ";
  if (ms_min == 0 || fps_max >= 1000)
  {
    out << "---.-";
  }
  else
  {
    out << setw(5) << fps_max;
  }
  string tmp = out.str();
  const char* buffer = tmp.c_str();
  for (UINT i = 0; i < num_chars; i++)
  {
    float index = (float)m_key_to_index.at(buffer[i]);
    m_vertex_buffer_data[i * VERTS_PER_CHAR    ].lookup_index = index;
    m_vertex_buffer_data[i * VERTS_PER_CHAR + 1].lookup_index = index;
    m_vertex_buffer_data[i * VERTS_PER_CHAR + 2].lookup_index = index;
    m_vertex_buffer_data[i * VERTS_PER_CHAR + 3].lookup_index = index;
  }

  try
  {
    m_verts->Upload(0, m_vertex_buffer_data, sizeof(VertexBufferEntry) * num_chars * VERTS_PER_CHAR);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to update instance buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void FPSMonitor::Draw(GraphicsCore& graphics, CommandList* command_list) const
{
  try
  {
    const RenderTarget& current_render_target = graphics.GetBackBuffer().GetCurrentRenderTarget();
    command_list->Reset(m_pipeline);
    command_list->SetRootSignature(*m_root_sig);
    command_list->RSSetViewport(graphics.GetDefaultViewport());
    command_list->RSSetScissorRect(m_scissor_rect);

    command_list->SetHeapArray(*m_heap_array);
    command_list->SetTextureAsStartOfDescriptorTable(0, *m_font);
    command_list->SetConstantBuffer(1, *m_lookup_table);

    command_list->OMSetRenderTarget(current_render_target);

    command_list->IASetTopology(IA_TOPOLOGY_TRIANGLE_LIST);
    command_list->IASetVertexBuffers(*m_vert_array);
    command_list->IASetIndexBuffer(*m_indices);

    command_list->DrawIndexedInstanced(m_indices->GetNumIndices(), 1, 0);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to draw frame:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void FPSMonitor::Resize(GraphicsCore& graphics)
{
  // create the scissor rect that matches the viewport
  Viewport full_viewport = graphics.GetDefaultViewport();
  m_scissor_rect = ViewportToScissorRect(graphics.GetDefaultViewport());

  // compute clip space char width and height
  m_char_width  = m_char_width_px  / full_viewport.width;
  m_char_height = m_char_height_px / full_viewport.height;

  const UINT num_chars = CHARS_PER_ROW * NUM_ROWS;
  for (UINT i = 0; i < num_chars; i++)
  {
    float x = (i % CHARS_PER_ROW) * m_char_width;
    float y = (i / CHARS_PER_ROW) * -m_char_height;
    m_vertex_buffer_data[i * VERTS_PER_CHAR    ].pos = XMFLOAT2(-1 + x,                y);
    m_vertex_buffer_data[i * VERTS_PER_CHAR + 1].pos = XMFLOAT2(-1 + x,                y - m_char_height);
    m_vertex_buffer_data[i * VERTS_PER_CHAR + 2].pos = XMFLOAT2(-1 + x + m_char_width, y - m_char_height);
    m_vertex_buffer_data[i * VERTS_PER_CHAR + 3].pos = XMFLOAT2(-1 + x + m_char_width, y);
  }
}
