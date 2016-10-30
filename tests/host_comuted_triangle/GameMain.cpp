#include "GameMain.h"
#include <directxmath.h>
#include "Graphics/RootSignatureConfig.h"
#include "Graphics/RenderTargetViewConfig.h"
#include "Graphics/RenderTargetViewFormats.h"
#include "Graphics/VertexDeclarations/Vertex_PositionColor.h"
using namespace DirectX;

GameMain::GameMain(WCHAR* title)
:Game(title)
{
}

GameMain::~GameMain()
{
}

void GameMain::LoadContent()
{
  GraphicsCore& graphics = GetGraphics();

  RootSignatureConfig* config = RootSignatureConfig::CreateD3D12(0, 0);
  config->SetStageAccess(true, true, false, false, false, true, false);
  m_root_sig = RootSignature::CreateD3D12(graphics, *config);
  if (m_root_sig == NULL)
  {
    exit(1);
  }

  m_vertex_shader = Shader::LoadD3D12("host_computed_triangle_vs.cso");
  if (m_vertex_shader == NULL)
  {
    exit(1);
  }
  m_pixel_shader = Shader::LoadD3D12("host_computed_triangle_ps.cso");
  if (m_pixel_shader == NULL)
  {
    exit(1);
  }

  m_input_layout = InputLayout::CreateD3D12(2);
  m_input_layout->SetNextElement(SEM_POSITION, 0, R32G32B32_FLOAT, 0, false);
  m_input_layout->SetNextElement(SEM_COLOR, 0, R32G32B32A32_FLOAT, 0, false);

  RenderTargetViewConfig* rtv_config = RenderTargetViewConfig::CreateD3D12(1);
  rtv_config->SetAlphaToCoverageEnable(false);
  rtv_config->SetIndependentBlendEnable(false);
  rtv_config->SetFormat(0, RTVF_R8G8B8A8_UNORM);
  m_pipeline = Pipeline::CreateD3D12(graphics, *m_input_layout, TOPOLOGY_TRIANGLE, *m_vertex_shader, *m_pixel_shader, *rtv_config, *m_root_sig);
  if (m_pipeline == NULL)
  {
    exit(1);
  }

  m_command_list = CommandList::CreateD3D12Direct(graphics, m_pipeline);
  m_command_list->Close();

  // create the scissor rect that matches the viewport
  Viewport full_viewport = graphics.GetDefaultViewport();
  m_scissor_rect = ViewportToScissorRect(graphics.GetDefaultViewport());

  // create the vertex buffer
  const Viewport& default_viewport = graphics.GetDefaultViewport();
  float aspect_ratio = default_viewport.width / default_viewport.height;
  Vertex_PositionColor vertices[] =
  {
    { XMFLOAT3( 0.0f,   0.25f * aspect_ratio, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
    { XMFLOAT3( 0.25f, -0.25f * aspect_ratio, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
    { XMFLOAT3(-0.25f, -0.25f * aspect_ratio, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
  };
  m_verts = VertexBuffer_PositionColor::CreateD3D12(graphics, ARRAYSIZE(vertices), vertices);
  if (m_verts == NULL)
  {
    exit(1);
  }

  // combine the vertex and instance buffer
  m_vert_array = VertexBufferArray::CreateD3D12(1);
  m_vert_array->Set(0, *m_verts);
}

void GameMain::UnloadContent()
{
  delete m_vert_array;
  delete m_verts;
  delete m_vertex_shader;
  delete m_pixel_shader;
  delete m_input_layout;
  delete m_command_list;
  delete m_pipeline;
  delete m_root_sig;
}

void GameMain::Update(UINT ms)
{
  Window& window = GetWindow();
  const KeyboardState& keyboard = window.GetKeyboardState();
  if (keyboard.IsKeyDown(VK_ESCAPE,false))
  {
    Exit();
  }
}

void GameMain::Draw(UINT ms)
{
  GraphicsCore& graphics = GetGraphics();
  const RenderTarget& currentRenderTarget = graphics.GetBackBuffer().GetCurrentRenderTarget();
  m_command_list->Reset(m_pipeline);
  m_command_list->SetRootSignature(*m_root_sig);
  m_command_list->RSSetViewport(graphics.GetDefaultViewport());
  m_command_list->RSSetScissorRect(m_scissor_rect);

  float clear_color[4] = { .3f, .3f, .3f, 1 };
  m_command_list->PrepRenderTarget(currentRenderTarget);
  m_command_list->OMSetRenderTarget(currentRenderTarget);
  m_command_list->ClearRenderTarget(currentRenderTarget, clear_color);

  m_command_list->IASetTopology(IA_TOPOLOGY_TRIANGLE_LIST);
  m_command_list->IASetVertexBuffers(*m_vert_array);
  
  m_command_list->DrawInstanced(m_verts->GetNumVertices(), 1, 0);

  m_command_list->RenderTargetToPresent(currentRenderTarget);
  m_command_list->Close();
  
  graphics.ExecuteCommandList(*m_command_list);

  graphics.Swap();
}

void GameMain::OnResize(UINT width,UINT height)
{
  Game::OnResize(width,height);
  
  // resize the viewports
  /*D3D11_Core& graphics = GetGraphics();
  D3D11_VIEWPORT full_viewport = graphics.GetDefaultViewport();
  D3D11_VIEWPORT section_viewport = full_viewport;
  section_viewport.Width /= 2;
  section_viewport.Height /= 2;
  m_viewports.SetViewport(0,section_viewport);
  section_viewport.TopLeftX = section_viewport.Width;
  m_viewports.SetViewport(1,section_viewport);
  section_viewport.TopLeftX = 0;
  section_viewport.TopLeftY = section_viewport.Height;
  m_viewports.SetViewport(2,section_viewport);
  section_viewport.TopLeftX = section_viewport.Width;
  m_viewports.SetViewport(3,section_viewport);
  
  // setup the cameras for the viewports
  float aspect_ratio = full_viewport.Width / full_viewport.Height;
  m_cameras[0]->SetAspecRatio(aspect_ratio);
  m_cameras[1]->SetAspecRatio(aspect_ratio);
  m_cameras[2]->SetAspecRatio(aspect_ratio);
  m_cameras[3]->SetAspecRatio(aspect_ratio);*/
}
