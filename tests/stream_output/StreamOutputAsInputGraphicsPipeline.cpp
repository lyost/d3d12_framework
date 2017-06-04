#include <sstream>
#include <directxmath.h>
#include "StreamOutputAsInputGraphicsPipeline.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

StreamOutputAsInputGraphicsPipeline::StreamOutputAsInputGraphicsPipeline(GraphicsCore& graphics, TestGraphicsPipeline& normal_pipeline)
:m_camera(NULL)
{
  try
  {
    RootSignatureConfig* config = RootSignatureConfig::CreateD3D12(1, 0);
    config->SetStageAccess(true, true, false, false, false, true, false);
    config->SetParamAsConstantBufferView(0, 0, 0, SHADER_VISIBILITY_VERTEX);
    m_so_root_sig = RootSignature::CreateD3D12(graphics, *config);
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
    m_so_vertex_shader = Shader::LoadD3D12("stream_output_vs_so.cso");
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
    DepthStencilConfig ds_config;
    ds_config.depth_enable        = true;
    ds_config.stencil_enable      = false;
    ds_config.dsv_format          = D32_FLOAT;
    ds_config.depth_write_enabled = true;
    ds_config.depth_comparison    = COMPARISON_FUNC_LESS_EQUAL;

    RenderTargetViewConfig* rtv_config = RenderTargetViewConfig::CreateD3D12(1);
    rtv_config->SetAlphaToCoverageEnable(false);
    rtv_config->SetIndependentBlendEnable(false);
    rtv_config->SetFormat(0, RTVF_R8G8B8A8_UNORM);

    m_so_pipeline = Pipeline::CreateD3D12(graphics, *normal_pipeline.m_input_layout, TOPOLOGY_TRIANGLE, *m_so_vertex_shader, NULL, *normal_pipeline.m_pixel_shader, &ds_config, *rtv_config, *m_so_root_sig,
      1, 0, true);
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
    m_so_vert_array = VertexBufferArray::CreateD3D12(1);
    m_so_vert_array->Set(0, *(normal_pipeline.m_so_buffers[0]));
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create stream output vertex buffer array:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_readback = ReadbackBuffer::CreateD3D12(graphics, (UINT)(sizeof(UINT64) * normal_pipeline.m_so_buffers.size()));
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create readback buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  m_command_list    = normal_pipeline.m_command_list;
  m_so_buffers      = normal_pipeline.m_so_buffers;
  m_scissor_rect    = normal_pipeline.m_scissor_rect;
  m_depth_stencil   = normal_pipeline.m_depth_stencil;
  m_constant_buffer = normal_pipeline.m_constant_buffer;
  m_heap_array      = normal_pipeline.m_heap_array;
}

StreamOutputAsInputGraphicsPipeline::~StreamOutputAsInputGraphicsPipeline()
{
  delete m_readback;
  delete m_so_vert_array;
  delete m_so_vertex_shader;
  delete m_so_pipeline;
  delete m_so_root_sig;
}

void StreamOutputAsInputGraphicsPipeline::SetCamera(const Camera* cam)
{
  m_camera = cam;
}

void StreamOutputAsInputGraphicsPipeline::Draw(GraphicsCore& graphics)
{
  try
  {
    const RenderTarget& current_render_target = graphics.GetBackBuffer().GetCurrentRenderTarget();

    // determine the number of vertices written to the stream output buffer
    vector<UINT> num_verts;
    StreamOutputBuffer::GetNumVerticesWrittenD3D12(graphics, *m_command_list, m_so_buffers, *m_readback, num_verts);

    ostringstream debug_log;
    debug_log << "Stream output buffer num verts: " << num_verts[0] << '\n';
    log_print(debug_log.str().c_str());

    // draw using the stream output buffer as input
    m_command_list->Reset(m_so_pipeline);
    m_command_list->SetRootSignature(*m_so_root_sig);
    m_command_list->RSSetViewport(graphics.GetDefaultViewport());
    m_command_list->RSSetScissorRect(m_scissor_rect);
    m_command_list->OMSetRenderTarget(current_render_target, *m_depth_stencil);

    XMMATRIX wvp = XMMatrixTranslation(2, 0, 0);
    XMMATRIX tmp;
    m_camera->GetView(tmp);
    wvp *= tmp;
    m_camera->GetProjection(tmp);
    wvp *= tmp;
    wvp = XMMatrixTranspose(wvp);
    m_constant_buffer->Upload(&wvp, 0, sizeof(wvp));
    m_command_list->SetConstantBuffer(0, *m_constant_buffer);

    m_command_list->SetHeapArray(*m_heap_array);
    m_command_list->SetConstantBuffer(0, *m_constant_buffer);

    m_command_list->SOBufferToVertexBuffer(*(m_so_buffers[0]));
    m_command_list->IASetTopology(IA_TOPOLOGY_TRIANGLE_LIST);
    m_command_list->IASetVertexBuffers(*m_so_vert_array);
    m_command_list->DrawInstanced(num_verts[0], 0, 1, 0);
    m_command_list->SOVertexBufferToStreamOutputBuffer(*(m_so_buffers[0]));

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

void StreamOutputAsInputGraphicsPipeline::Resize(GraphicsCore& graphics, TestGraphicsPipeline& normal_pipeline)
{
  const Viewport& full_viewport = graphics.GetDefaultViewport();
  m_scissor_rect = ViewportToScissorRect(full_viewport);

  m_depth_stencil = normal_pipeline.m_depth_stencil;
}
