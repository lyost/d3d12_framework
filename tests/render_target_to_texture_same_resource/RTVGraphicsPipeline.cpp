#include <sstream>
#include <directxmath.h>
#include "RTVGraphicsPipeline.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

RTVGraphicsPipeline::RTVGraphicsPipeline(GraphicsCore& graphics, const TestGraphicsPipeline& main_pipeline)
:m_model(NULL),
 m_root_sig(main_pipeline.m_root_sig),
 m_command_list(main_pipeline.m_command_list),
 m_heap_array(main_pipeline.m_heap_array),
 m_constant_buffer(main_pipeline.m_constant_buffer),
 m_depth_stencil(main_pipeline.m_depth_stencil),
 m_vert_array(main_pipeline.m_vert_array)
{
  try
  {
    m_rtv_pixel_shader = Shader::LoadD3D12("render_target_to_texture_same_resource_gen_texture_ps.cso");
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to load secondary pixel shader:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  try
  {
    RenderTargetViewConfig* rtv_config = RenderTargetViewConfig::CreateD3D12(1);
    rtv_config->SetAlphaToCoverageEnable(false);
    rtv_config->SetIndependentBlendEnable(false);
    rtv_config->SetFormat(0, RTVF_R8G8B8A8_UNORM);
    m_rtv_pipeline = Pipeline::CreateD3D12(graphics, *main_pipeline.m_input_layout, TOPOLOGY_TRIANGLE, *main_pipeline.m_vertex_shader, NULL, *m_rtv_pixel_shader, DEPTH_FUNC_LESS_EQUAL, *rtv_config,
      *m_root_sig);
    delete rtv_config;
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create pipeline:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

RTVGraphicsPipeline::~RTVGraphicsPipeline()
{
  delete m_rtv_texture;
  delete m_rtv_pixel_shader;
  delete m_rtv_pipeline;
}

void RTVGraphicsPipeline::SetModel(GraphicsCore& graphics, const TestModel* model)
{
  m_model = model;
  try
  {
    m_rtv_texture = RenderTarget::CreateD3D12FromTexture(graphics, *m_model->GetTexture());
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create custom render target:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void RTVGraphicsPipeline::Draw(GraphicsCore& graphics)
{
  try
  {
    Texture2DRenderTarget* texture = m_model->GetTexture();
    const IndexBuffer16* index_buffer = m_model->GetIndexBuffer();

    m_command_list->Close();
    m_command_list->Reset(m_rtv_pipeline);

    Viewport viewport   = graphics.GetDefaultViewport();
    viewport.width      = RTV_TEX_WIDTH;
    viewport.height     = RTV_TEX_HEIGHT;
    viewport.top_left_x = 0;
    viewport.top_left_y = 0;

    RECT scissor_rect = ViewportToScissorRect(viewport);

    m_command_list->SetRootSignature(*m_root_sig);
    m_command_list->RSSetViewport(viewport);
    m_command_list->RSSetScissorRect(scissor_rect);

    Camera* camera = new Camera(RTV_TEX_WIDTH / (float)RTV_TEX_HEIGHT, 0.01f, 100.0f, XMFLOAT4(0, 0, -2, 1), XMFLOAT4(0, 0, 1, 0), XMFLOAT4(0, 1, 0, 0));

    // upload the wvp matrix for the camera to the constant buffer
    XMMATRIX tmp;
    XMMATRIX wvp = XMMatrixIdentity();
    camera->GetView(tmp);
    wvp *= tmp;
    camera->GetProjection(tmp);
    wvp *= tmp;
    wvp = XMMatrixTranspose(wvp);
    m_constant_buffer->Upload(&wvp, 0, sizeof(wvp));

    m_command_list->SetHeapArray(*m_heap_array);
    m_command_list->SetTextureAsStartOfDescriptorTable(0, *texture);
    m_command_list->SetConstantBuffer(1, *m_constant_buffer);

    float clear_color[4] = { 0, 0, 0, 1 };
    m_command_list->TextureToRenderTarget(*texture);
    m_command_list->OMSetRenderTarget(*m_rtv_texture, *m_depth_stencil);
    m_command_list->ClearRenderTarget(*m_rtv_texture, clear_color);
    m_command_list->ClearDepthStencil(*m_depth_stencil, 1);

    m_command_list->IASetTopology(IA_TOPOLOGY_TRIANGLE_LIST);
    m_command_list->IASetVertexBuffers(*m_vert_array);
    m_command_list->IASetIndexBuffer(*index_buffer);

    m_command_list->DrawIndexedInstanced(index_buffer->GetNumIndices(), 1, 0);

    m_command_list->RenderTargetToTexture(*m_rtv_texture);

    m_command_list->Close();
    graphics.ExecuteCommandList(*m_command_list);
    graphics.WaitOnFence();

    delete camera;
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to draw to custom render target and copy to texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}
