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
    config->SetStageAccess(true, true, true, true, true, true, true);
    config->SetParamAsConstantBufferView(0, 0, 0, SHADER_VISIBILITY_GEOMETRY);
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

  try
  {
    m_vertex_shader = Shader::LoadD3D12("stream_output_vs.cso");
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
    m_hull_shader = Shader::LoadD3D12("stream_output_hs.cso");
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to load hull shader:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_domain_shader = Shader::LoadD3D12("stream_output_ds.cso");
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to load domain shader:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_geometry_shader = Shader::LoadD3D12("stream_output_gs.cso");
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to load geometry shader:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_pixel_shader = Shader::LoadD3D12("stream_output_ps.cso");
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
    m_input_layout = InputLayout::CreateD3D12(1);
    m_input_layout->SetNextElement(SEM_POSITION, 0, R32G32B32_FLOAT, 0, false);
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
    stream_output->SetStreamToRasterizer(0);
    stream_output->SetEntry(0, 0, SEM_POSITION, 0, 0, 4, 0, sizeof(XMFLOAT4)); // just want the raw position, not the transformed that gets passed to the pixel shader as well

    m_pipeline = Pipeline::CreateD3D12(graphics, *m_input_layout, TOPOLOGY_PATCH, *m_vertex_shader, *m_hull_shader, *m_domain_shader, *m_geometry_shader, stream_output, *m_pixel_shader,
      DEPTH_FUNC_LESS_EQUAL, *rtv_config, *m_root_sig, 1, 0, true);

    delete rtv_config;
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
    m_so_buffers.push_back(StreamOutputBuffer::CreateD3D12(graphics, *stream_output, 0, 6));

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
  delete m_so_array;
  delete m_so_buffers[0];
  delete m_depth_stencil;
  delete m_shader_buffer_heap;
  delete m_heap_array;
  delete m_constant_buffer;
  delete m_scratch_buffer;
  delete m_vert_array;
  delete m_vertex_shader;
  delete m_hull_shader;
  delete m_domain_shader;
  delete m_geometry_shader;
  delete m_pixel_shader;
  delete m_input_layout;
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
    const IndexBuffer16* index_buffer = m_model->GetIndexBuffer();

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
    XMMATRIX wvp = XMMatrixTranslation(-2, 0, 0);
    m_camera->GetView(tmp);
    wvp *= tmp;
    m_camera->GetProjection(tmp);
    wvp *= tmp;
    wvp = XMMatrixTranspose(wvp);
    m_constant_buffer->Upload(&wvp, 0, sizeof(wvp));

    m_command_list->SetHeapArray(*m_heap_array);
    m_command_list->SetConstantBuffer(0, *m_constant_buffer);

    m_command_list->IASetTopology(IA_TOPOLOGY_4_CONTROL_POINT_PATCH);
    m_command_list->IASetVertexBuffers(*m_vert_array);
    m_command_list->IASetIndexBuffer(*index_buffer);
    m_command_list->SOSetBuffers(*m_so_array);

    m_command_list->DrawIndexedInstanced(index_buffer->GetNumIndices(), 1, 0);
    m_command_list->Close();
    graphics.ExecuteCommandList(*m_command_list);
    graphics.WaitOnFence();

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
