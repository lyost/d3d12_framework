#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <cmath>
#include <directxmath.h>
#include "GameMain.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

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

  Viewport full_viewport = graphics.GetDefaultViewport();
  m_scissor_rect = ViewportToScissorRect(graphics.GetDefaultViewport());

  try
  {
    m_command_list = CommandList::CreateD3D12Direct(graphics, NULL);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create command list:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  CreateDepthStencil(graphics);

  m_pipeline_pos = new TestGraphicsPipelinePos(graphics);
  m_model_pos = new TestModelPos(graphics);
  m_pipeline_pos->SetModel(m_model_pos);

  m_pipeline_pos_color = new TestGraphicsPipelinePosColor(graphics);
  m_model_pos_color = new TestModelPosColor(graphics);
  m_pipeline_pos_color->SetModel(m_model_pos_color);

  m_pipeline_pos_tex_u = new TestGraphicsPipelinePosTexU(graphics);
  m_model_pos_tex_u = new TestModelPosTexU(graphics, m_pipeline_pos_tex_u->GetShaderResourceDescHeap(), m_command_list);
  m_pipeline_pos_tex_u->SetModel(m_model_pos_tex_u);

  m_command_list->Reset(NULL);
  m_pipeline_pos_tex_uv = new TestGraphicsPipelinePosTexUV(graphics);
  m_model_pos_tex_uv = new TestModelPosTexUV(graphics, m_pipeline_pos_tex_uv->GetShaderResourceDescHeap(), m_command_list);
  m_pipeline_pos_tex_uv->SetModel(m_model_pos_tex_uv);

  m_command_list->Reset(NULL);
  m_pipeline_pos_tex_uvw = new TestGraphicsPipelinePosTexUVW(graphics);
  m_model_pos_tex_uvw = new TestModelPosTexUVW(graphics, m_pipeline_pos_tex_uvw->GetShaderResourceDescHeap(), m_command_list);
  m_pipeline_pos_tex_uvw->SetModel(m_model_pos_tex_uvw);

  // setup the cameras for the viewport
  m_camera_angle = 3 * XM_PI / 2;
  m_camera = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(0, 0, -10, 1), XMFLOAT4(0, 0, 1, 0), XMFLOAT4(0, 1, 0, 0));
  m_pipeline_pos->SetCamera(m_camera);
  m_pipeline_pos_color->SetCamera(m_camera);
  m_pipeline_pos_tex_u->SetCamera(m_camera);
  m_pipeline_pos_tex_uv->SetCamera(m_camera);
  m_pipeline_pos_tex_uvw->SetCamera(m_camera);
}

void GameMain::UnloadContent()
{
  delete m_depth_stencil;
  delete m_command_list;
  delete m_camera;
  delete m_model_pos;
  delete m_model_pos_color;
  delete m_model_pos_tex_u;
  delete m_model_pos_tex_uv;
  delete m_model_pos_tex_uvw;
  delete m_pipeline_pos;
  delete m_pipeline_pos_color;
  delete m_pipeline_pos_tex_u;
  delete m_pipeline_pos_tex_uv;
  delete m_pipeline_pos_tex_uvw;
}

void GameMain::Update(UINT step_ms, UINT actual_ms)
{
  static bool resized = false;
  static bool fullscreen = false;
  static bool num_1_down = false;
  static bool num_2_down = false;

  try
  {
    Window& window = GetWindow();
    const KeyboardState& keyboard = window.GetKeyboardState();
    if (keyboard.IsKeyDown(VK_ESCAPE, false))
    {
      Exit();
    }
    else if (keyboard.IsKeyDown(VK_LEFT, true))
    {
      m_camera_angle -= XM_PI * step_ms / 1000.0f; // todo: bounds
      UpdateCamera();
    }
    else if (keyboard.IsKeyDown(VK_RIGHT, true))
    {
      m_camera_angle += XM_PI * step_ms / 1000.0f; // todo: bounds
      UpdateCamera();
    }
    else if (keyboard.IsKeyDown(VK_F1, false) && !resized)
    {
      window.Resize(1024, 768);
      resized = true;
    }
    else if (keyboard.IsKeyDown(VK_F2, false) && !fullscreen)
    {
      // enter full screen mode
      Fullscreen(true);
      fullscreen = true;
    }
    else if (keyboard.IsKeyDown(VK_F3, false) && fullscreen)
    {
      // return to window mode
      Fullscreen(false);
      fullscreen = false;
    }
    else if (keyboard.IsKeyDown(VK_OEM_4, false))
    {
      window.ShowMousePointer(false);
    }
    else if (keyboard.IsKeyDown(VK_OEM_6, false))
    {
      window.ShowMousePointer(true);
    }
    else if (keyboard.IsKeyDown('9', false))
    {
      window.ConstrainMousePointer(true);
    }
    else if (keyboard.IsKeyDown('0', false))
    {
      window.ConstrainMousePointer(false);
    }

    if (keyboard.IsKeyDown(VK_NUMPAD1, false))
    {
      num_1_down = true;
    }
    else if (num_1_down)
    {
      num_1_down = false;
      m_model_pos->UpdateVertexBuffer(true);
      m_model_pos_color->UpdateVertexBuffer(true);
      m_model_pos_tex_u->UpdateVertexBuffer(true);
      m_model_pos_tex_uv->UpdateVertexBuffer(true);
      m_model_pos_tex_uvw->UpdateVertexBuffer(true);
    }
    if (keyboard.IsKeyDown(VK_NUMPAD2, false))
    {
      num_2_down = true;
    }
    else if (num_2_down)
    {
      num_2_down = false;
      m_model_pos->UpdateVertexBuffer(false);
      m_model_pos_color->UpdateVertexBuffer(false);
      m_model_pos_tex_u->UpdateVertexBuffer(false);
      m_model_pos_tex_uv->UpdateVertexBuffer(false);
      m_model_pos_tex_uvw->UpdateVertexBuffer(false);
    }
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to complete update:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void GameMain::Draw(UINT step_ms, UINT actual_ms)
{
  GraphicsCore& graphics = GetGraphics();

  const RenderTarget& current_render_target = graphics.GetBackBuffer().GetCurrentRenderTarget();

  m_command_list->Reset(NULL);
  m_command_list->RSSetViewport(graphics.GetDefaultViewport());
  m_command_list->RSSetScissorRect(m_scissor_rect);

  float clear_color[4] = { .3f, .3f, .3f, 1 };
  m_command_list->PrepRenderTarget(current_render_target);
  m_command_list->OMSetRenderTarget(current_render_target, *m_depth_stencil);
  m_command_list->ClearRenderTarget(current_render_target, clear_color);
  m_command_list->ClearDepthStencil(*m_depth_stencil, 1);

  m_pipeline_pos->Draw(graphics, *m_command_list);
  m_pipeline_pos_color->Draw(graphics, *m_command_list);
  m_pipeline_pos_tex_u->Draw(graphics, *m_command_list);
  m_pipeline_pos_tex_uv->Draw(graphics, *m_command_list);
  m_pipeline_pos_tex_uvw->Draw(graphics, *m_command_list);

  m_command_list->RenderTargetToPresent(current_render_target);
  m_command_list->Close();
  graphics.ExecuteCommandList(*m_command_list);

  graphics.Swap();
}

void GameMain::OnResize(UINT width,UINT height)
{
  try
  {
    Game::OnResize(width, height);

    GraphicsCore& graphics = GetGraphics();

    delete m_depth_stencil;
    CreateDepthStencil(graphics);

    const Viewport& full_viewport = graphics.GetDefaultViewport();
    m_scissor_rect = ViewportToScissorRect(graphics.GetDefaultViewport());
    delete m_camera;
    m_camera = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(0, 0, -10, 1), XMFLOAT4(0, 0, 1, 0), XMFLOAT4(0, 1, 0, 0));
    UpdateCamera();
    m_pipeline_pos->SetCamera(m_camera);
    m_pipeline_pos_color->SetCamera(m_camera);
    m_pipeline_pos_tex_u->SetCamera(m_camera);
    m_pipeline_pos_tex_uv->SetCamera(m_camera);
    m_pipeline_pos_tex_uvw->SetCamera(m_camera);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to resize:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void GameMain::UpdateCamera()
{
  const float orbit_dist = 10;

  XMFLOAT4 pos(orbit_dist * cos(m_camera_angle), 0, orbit_dist * sin(m_camera_angle), 1);
  XMFLOAT4 dir;
  XMFLOAT4 up(0, 1, 0, 0);

  XMFLOAT4 origin(0, 0, 0, 1);
  XMVECTOR pos_vector = XMLoadFloat4(&pos);
  XMVECTOR origin_vector = XMLoadFloat4(&origin);
  XMVECTOR dir_vector = origin_vector - pos_vector;
  XMVector4Normalize(dir_vector);
  XMStoreFloat4(&dir, dir_vector);

  m_camera->SetView(pos, dir, up);
}

void GameMain::CreateDepthStencil(GraphicsCore& graphics)
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
