#include <sstream>
#include <cmath>
#include <directxmath.h>
#include "FrameworkException.h"
#include "GameMain.h"
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
  m_pipeline = new TestGraphicsPipeline(graphics);

  m_model = new TestModel(graphics, m_pipeline->GetShaderResourceDescHeap(), m_pipeline->GetCommandList());
  m_pipeline->SetModel(m_model);

  // setup the cameras for the viewport
  m_camera_angle = 3 * XM_PI / 2;
  m_camera[0] = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(  0,  0, -10, 1), XMFLOAT4( 0,  0, 1, 0), XMFLOAT4(0, 1,  0, 0));
  m_camera[1] = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4( 10,  0,   0, 1), XMFLOAT4(-1,  0, 0, 0), XMFLOAT4(0, 1,  0, 0));
  m_camera[2] = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(-10,  0,   0, 1), XMFLOAT4( 1,  0, 0, 0), XMFLOAT4(0, 1,  0, 0));
  m_camera[3] = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(  0, 10,   0, 1), XMFLOAT4( 0, -1, 0, 0), XMFLOAT4(0, 0, -1, 0));
  for (UINT i = 0; i < TestGraphicsPipeline::NUM_VIEWPORTS; i++)
  {
    m_pipeline->SetCamera(i, m_camera[i]);
  }
}

void GameMain::UnloadContent()
{
  delete m_pipeline;
  for (int i = 0; i < TestGraphicsPipeline::NUM_VIEWPORTS; i++)
  {
    delete m_camera[i];
  }
  delete m_model;
}

void GameMain::Update(UINT step_ms, UINT actual_ms)
{
  static bool resized = false;
  static bool fullscreen = false;

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
  m_pipeline->Draw(graphics);
}

void GameMain::OnResize(UINT width,UINT height)
{
  try
  {
    Game::OnResize(width, height);

    GraphicsCore& graphics = GetGraphics();
    Viewport full_viewport = graphics.GetDefaultViewport();
    m_pipeline->Resize(graphics);

    for (UINT i = 0; i < TestGraphicsPipeline::NUM_VIEWPORTS; i++)
    {
      delete m_camera[i];
    }
    m_camera[0] = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(  0,  0, -10, 1), XMFLOAT4( 0,  0, 1, 0), XMFLOAT4(0, 1,  0, 0));
    m_camera[1] = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4( 10,  0,   0, 1), XMFLOAT4(-1,  0, 0, 0), XMFLOAT4(0, 1,  0, 0));
    m_camera[2] = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(-10,  0,   0, 1), XMFLOAT4( 1,  0, 0, 0), XMFLOAT4(0, 1,  0, 0));
    m_camera[3] = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(  0, 10,   0, 1), XMFLOAT4( 0, -1, 0, 0), XMFLOAT4(0, 0, -1, 0));
    UpdateCamera();
    for (UINT i = 0; i < TestGraphicsPipeline::NUM_VIEWPORTS; i++)
    {
      m_pipeline->SetCamera(i, m_camera[i]);
    }
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

  m_camera[0]->SetView(pos, dir, up);
}
