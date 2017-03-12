#include <sstream>
#include <cmath>
#include "GameMain.h"
#include <directxmath.h>
#include "Graphics/RootSignatureConfig.h"
#include "Graphics/RenderTargetViewConfig.h"
#include "Graphics/RenderTargetViewFormats.h"
#include "Graphics/VertexDeclarations/Vertex_PositionTexture.h"
#include "Graphics/StreamOutputConfig.h"
#include "Graphics/DepthEnums.h"
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
  m_so_pipeline = new StreamOutputAsInputGraphicsPipeline(graphics, *m_pipeline);
  m_model = new TestModel(graphics, m_pipeline->GetShaderResourceDescHeap(), m_pipeline->GetCommandList());
  m_pipeline->SetModel(m_model);

  // setup the cameras for the viewport
  Viewport full_viewport = graphics.GetDefaultViewport();
  m_camera_angle = 3 * XM_PI / 2;
  m_camera = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(0, 0, -10, 1), XMFLOAT4(0, 0, 1, 0), XMFLOAT4(0, 1, 0, 0));
  m_pipeline->SetCamera(m_camera);
  m_so_pipeline->SetCamera(m_camera);
}

void GameMain::UnloadContent()
{
  delete m_camera;
  delete m_model;
  delete m_pipeline;
  delete m_so_pipeline;
}

void GameMain::Update(UINT ms)
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
      m_camera_angle -= XM_PI * ms / 1000.0f; // todo: bounds
      UpdateCamera();
    }
    else if (keyboard.IsKeyDown(VK_RIGHT, true))
    {
      m_camera_angle += XM_PI * ms / 1000.0f; // todo: bounds
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

void GameMain::Draw(UINT ms)
{
  GraphicsCore& graphics = GetGraphics();
  m_pipeline->Draw(graphics);
  m_so_pipeline->Draw(graphics);
}

void GameMain::OnResize(UINT width,UINT height)
{
  try
  {
    Game::OnResize(width, height);

    GraphicsCore& graphics = GetGraphics();
    m_pipeline->Resize(graphics);
    m_so_pipeline->Resize(graphics, *m_pipeline);

    const Viewport& full_viewport = graphics.GetDefaultViewport();
    delete m_camera;
    m_camera = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(0, 0, -10, 1), XMFLOAT4(0, 0, 1, 0), XMFLOAT4(0, 1, 0, 0));
    UpdateCamera();
    m_pipeline->SetCamera(m_camera);
    m_so_pipeline->SetCamera(m_camera);
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
