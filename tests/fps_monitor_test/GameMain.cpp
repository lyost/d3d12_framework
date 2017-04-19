#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <cmath>
#include <directxmath.h>
#include "GameMain.h"
#include "FrameworkException.h"
#include "log.h"
#include "lodepng/lodepng.h"
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
  m_model = new TestModel(graphics, m_pipeline->GetShaderResourceDescHeap(), m_pipeline->GetCommandList());
  m_pipeline->SetModel(m_model);

  // setup the cameras for the viewport
  Viewport full_viewport = graphics.GetDefaultViewport();
  m_camera_angle = 3 * XM_PI / 2;
  m_camera = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(0, 0, -10, 1), XMFLOAT4(0, 0, 1, 0), XMFLOAT4(0, 1, 0, 0));
  m_pipeline->SetCamera(m_camera);

  CreateFPSMonitor();
  m_pipeline->SetFPSMonitor(m_fps);
}

void GameMain::UnloadContent()
{
  delete m_camera;
  delete m_model;
  delete m_pipeline;
  delete m_fps;
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

  m_fps->Update(actual_ms);
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
    m_camera = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(0, 0, -10, 1), XMFLOAT4(0, 0, 1, 0), XMFLOAT4(0, 1, 0, 0));
    UpdateCamera();
    m_pipeline->SetCamera(m_camera);

    m_fps->Resize(graphics);
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

void GameMain::CreateFPSMonitor()
{
  map<char, vector<float> > lookup_table;
  ifstream in("fps_font.txt");
  UINT char_width;
  UINT char_height;
  float left;
  float right;
  float top;
  float bottom;
  char  key;
  char  newline;
  if (!in.good())
  {
    ostringstream out;
    out << "Failed to load fps_font.txt\n";
    log_print(out.str().c_str());
    exit(1);
  }
  in >> char_width >> char_height;
  in.read(&key, 1);
  while ((in.read(&key, 1) >> left >> right >> top >> bottom).read(&newline, 1))
  {
    vector<float> uv;
    uv.push_back(left);
    uv.push_back(right);
    uv.push_back(top);
    uv.push_back(bottom);

    lookup_table.insert(make_pair(key, uv));
  }

  unsigned char* image_data = NULL;
  unsigned width = 0;
  unsigned height = 0;
  if (lodepng_decode32_file(&image_data, &width, &height, "fps_font.png"))
  {
    ostringstream out;
    out << "Failed to load fps_font.ping\n";
    log_print(out.str().c_str());
    exit(1);
  }

  GraphicsCore& graphics = GetGraphics();
  const UINT num_bytes = width * height * sizeof(UINT);
  vector<UINT8> bytes(num_bytes);
  memcpy(&(bytes[0]), image_data, num_bytes);

  m_fps = new FPSMonitor(graphics, FPS_MONITOR_NUM_SAMPLES, lookup_table, width, height, bytes, char_width, char_height);
  free(image_data);
}
