#include <sstream>
#include <directxmath.h>
#include "TestGraphicsPipeline.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

TestGraphicsPipeline::TestGraphicsPipeline(GraphicsCore& graphics)
:m_model(NULL),
 m_camera(NULL)
{
  try
  {
    RootSignatureConfig* config = RootSignatureConfig::CreateD3D12(1, 0);
    config->SetStageAccess(true, true, false, false, false, true, true);
    config->SetParamAsConstantBufferView(0, 0, 0, SHADER_VISIBILITY_VERTEX);
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
    vertex_shader = Shader::LoadD3D12("input_layout_influence_stream_output_vs.cso");
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
    pixel_shader = Shader::LoadD3D12("input_layout_influence_stream_output_ps.cso");
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
    input_layout = InputLayout::CreateD3D12(1);
    input_layout->SetNextElement(SEM_POSITION, 0, R32G32B32_FLOAT, 0, false);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create input layout:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  StreamOutputConfig* stream_output;
  try
  {
    RenderTargetViewConfig* rtv_config = RenderTargetViewConfig::CreateD3D12(1);
    rtv_config->SetAlphaToCoverageEnable(false);
    rtv_config->SetIndependentBlendEnable(false);
    rtv_config->SetFormat(0, RTVF_R8G8B8A8_UNORM);

    stream_output = StreamOutputConfig::CreateD3D12(1);
    stream_output->SetEntry(0, 0, SEM_SV_POSITION, 0, 0, 4, 0, sizeof(XMFLOAT4));

    m_pipeline = Pipeline::CreateD3D12(graphics, *input_layout, TOPOLOGY_TRIANGLE, *vertex_shader, stream_output, *pixel_shader, NULL, *rtv_config, *m_root_sig, CULL_BACK, 1, 0, true);

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

  try
  {
    m_command_list = CommandList::CreateD3D12Direct(graphics, m_pipeline);
    m_command_list->Close();
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create command list:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the scissor rect that matches the viewport
  Viewport full_viewport = graphics.GetDefaultViewport();
  m_scissor_rect = ViewportToScissorRect(graphics.GetDefaultViewport());

  try
  {
    m_vert_array = VertexBufferArray::CreateD3D12(1);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create vertex buffer array:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  try
  {
    m_so_buffers.reserve(1);
    m_so_buffers.push_back(StreamOutputBuffer::CreateD3D12(graphics, *stream_output, 0, 65536));

    m_so_array = StreamOutputBufferArray::CreateD3D12(1);
    m_so_array->Set(0, *(m_so_buffers[0]));
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create stream output buffer:\n" << err.what();
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

  // create the constant buffers
  try
  {
    m_constant_buffer = ConstantBuffer::CreateD3D12(graphics, *m_shader_buffer_heap, sizeof(XMMATRIX));
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create constant buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_scratch_buffer = ConstantBuffer::CreateD3D12(graphics, *m_shader_buffer_heap, sizeof(UINT64));
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create scratch constant buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  try
  {
    m_readback = ReadbackBuffer::CreateD3D12(graphics, (UINT)(sizeof(UINT64) * m_so_buffers.size()));
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create readback buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  CreateDepthStencil(graphics);

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

  delete stream_output;
}

TestGraphicsPipeline::~TestGraphicsPipeline()
{
  delete m_readback;
  delete m_so_array;
  delete m_so_buffers[0];
  delete m_depth_stencil;
  delete m_shader_buffer_heap;
  delete m_heap_array;
  delete m_constant_buffer;
  delete m_scratch_buffer;
  delete m_vert_array;
  delete m_command_list;
  delete m_pipeline;
  delete m_root_sig;
}

ShaderResourceDescHeap* TestGraphicsPipeline::GetShaderResourceDescHeap() const
{
  return m_shader_buffer_heap;
}

CommandList* TestGraphicsPipeline::GetCommandList() const
{
  return m_command_list;
}

void TestGraphicsPipeline::SetModel(const TestModel* model)
{
  m_model = model;

  // add the vertex buffer to the vertex buffer array
  try
  {
    m_vert_array->Set(0, *m_model->GetVertexBuffer());
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to set model vertex buffer into the vertex buffer array:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void TestGraphicsPipeline::SetCamera(const Camera* cam)
{
  m_camera = cam;
}

void TestGraphicsPipeline::Draw(GraphicsCore& graphics)
{
  try
  {
    const RenderTarget& current_render_target = graphics.GetBackBuffer().GetCurrentRenderTarget();

    // draw and write to the stream output buffer
    float clear_color[4] = { .3f, .3f, .3f, 1 };
    m_command_list->Reset(m_pipeline);
    m_command_list->SetRootSignature(*m_root_sig);
    m_command_list->RSSetViewport(graphics.GetDefaultViewport());
    m_command_list->RSSetScissorRect(m_scissor_rect);
    m_command_list->PrepRenderTarget(current_render_target);
    m_command_list->OMSetRenderTarget(current_render_target, *m_depth_stencil);
    m_command_list->ClearRenderTarget(current_render_target, clear_color);
    m_command_list->ClearDepthStencil(*m_depth_stencil, 1);

    // make sure writing to the stream output buffer starts at the beginning of its vertex memory
    m_so_buffers[0]->PrepReset(*m_command_list, *m_scratch_buffer);

    XMMATRIX tmp;
    XMMATRIX wvp = XMMatrixIdentity();
    m_camera->GetView(tmp);
    wvp *= tmp;
    m_camera->GetProjection(tmp);
    wvp *= tmp;
    wvp = XMMatrixTranspose(wvp);
    m_constant_buffer->Upload(&wvp, 0, sizeof(wvp));

    m_command_list->SetHeapArray(*m_heap_array);
    m_command_list->SetConstantBuffer(0, *m_constant_buffer);

    m_command_list->IASetTopology(IA_TOPOLOGY_TRIANGLE_STRIP);
    m_command_list->IASetVertexBuffers(*m_vert_array);
    m_command_list->SOSetBuffers(*m_so_array);

    m_command_list->DrawInstanced(m_model->GetVertexBuffer()->GetNumVertices(), 1, 0);
    m_command_list->Close();
    graphics.ExecuteCommandList(*m_command_list);
    graphics.WaitOnFence();

    // determine the number of vertices written to the stream output buffer
    vector<UINT> num_verts;
    StreamOutputBuffer::GetNumVerticesWrittenD3D12(graphics, *m_command_list, m_so_buffers, *m_readback, num_verts);

    ostringstream debug_log;
    debug_log << "Stream output buffer num verts: " << num_verts[0] << '\n';
    log_print(debug_log.str().c_str());

    m_command_list->Reset(NULL);
    m_command_list->RenderTargetToPresent(current_render_target);
    m_command_list->Close();

    graphics.ExecuteCommandList(*m_command_list);

    graphics.Swap();
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to draw frame:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void TestGraphicsPipeline::Resize(GraphicsCore& graphics)
{
  const Viewport& full_viewport = graphics.GetDefaultViewport();
  m_scissor_rect = ViewportToScissorRect(full_viewport);

  delete m_depth_stencil;
  CreateDepthStencil(graphics);
}

void TestGraphicsPipeline::CreateDepthStencil(GraphicsCore& graphics)
{
  Viewport full_viewport = graphics.GetDefaultViewport();

  try
  {
    m_depth_stencil = DepthStencil::CreateD3D12(graphics, (UINT)full_viewport.width, (UINT)full_viewport.height, 1);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create depth stencil:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}
