#include <sstream>
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
  m_pipeline = new TestGraphicsPipeline(graphics);
  m_light_pos = XMFLOAT3(8, 0, 0);
  m_model = new TestModel(graphics, m_pipeline->GetShaderResourceDescHeap(), m_pipeline->GetCommandList());
  m_occluder = new Occluder(graphics, m_light_pos, m_pipeline->GetShaderResourceDescHeap(), m_pipeline->GetCommandList());
  m_pipeline->SetLightPos(m_light_pos);
  m_pipeline->SetOccluder(m_occluder);
  m_pipeline->SetModel(m_model);

  SetupCamera();
}

void GameMain::UnloadContent()
{
  delete m_camera;
  delete m_model;
  delete m_occluder;
  delete m_pipeline;
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
      m_model->MoveWorldPos(0, 0, step_ms / -1000.0f);
    }
    else if (keyboard.IsKeyDown(VK_RIGHT, true))
    {
      m_model->MoveWorldPos(0, 0, step_ms / 1000.0f);
    }
    else if (keyboard.IsKeyDown(VK_UP, true))
    {
      m_model->MoveWorldPos(0, step_ms / 1000.0f, 0);
    }
    else if (keyboard.IsKeyDown(VK_DOWN, true))
    {
      m_model->MoveWorldPos(0, step_ms / -1000.0f, 0);
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
    m_pipeline->Resize(graphics);

    const Viewport& full_viewport = graphics.GetDefaultViewport();
    delete m_camera;
    SetupCamera();
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to resize:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void GameMain::SetupCamera()
{
  GraphicsCore& graphics = GetGraphics();
  Viewport full_viewport = graphics.GetDefaultViewport();

  float dist = 20;
  float orbit_angle = XM_PI / 2;
  XMFLOAT4 pos(dist * cos(orbit_angle), 0, dist * sin(orbit_angle), 1);
  XMFLOAT4 dir;
  XMFLOAT4 up(0, 1, 0, 0);

  XMFLOAT4 origin(0, 0, 0, 1);
  XMVECTOR pos_vector = XMLoadFloat4(&pos);
  XMVECTOR origin_vector = XMLoadFloat4(&origin);
  XMVECTOR dir_vector = origin_vector - pos_vector;
  XMVector4Normalize(dir_vector);
  XMStoreFloat4(&dir, dir_vector);

  m_camera = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, pos, dir, up);
  m_pipeline->SetCamera(m_camera);
}
