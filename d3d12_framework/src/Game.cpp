#include <sstream>
#include "Game.h"
#include "Time/Timer.h"
using namespace std;

Game::Game(WCHAR* title)
:m_mspf(1000 / 60),
 m_run(true)
{
  // create the game window
  m_window = Window::CreateDefaultWindow(title,ResizeHandler,this);
  
  // handle the error case of failing to create the window
  if (!m_window)
  {
    exit(1);
  }
  
  // create the D3D12 core for the window
  m_graphics = GraphicsCore::CreateD3D12(m_window->GetHandle());
}

Game::~Game()
{
  delete m_graphics;
  delete m_window;
}

void Game::Run()
{
  // perform init
  LoadContent();
  
  // get a timer
  Timer* timer = Timer::GetTimer();
  
  // message loop
  MSG msg = {0};
  UINT actual_ms = 0;
  while(m_run && msg.message != WM_QUIT)
  {
    // handle messages
    if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    // check if it's time for another update/render cycle
    else if (timer->CheckDelta(m_mspf, actual_ms))
    {
      Update(m_mspf, actual_ms);
      Draw(m_mspf, actual_ms);
    }
  }
  
  // perform cleanup
  UnloadContent();
}

void Game::Fullscreen(bool enable)
{
  UINT width;
  UINT height;
  m_window->GetWindowClientDim(width,height);
  
  m_graphics->Fullscreen(width,height,enable);
}

void Game::Exit()
{
  m_run = false;
}

void Game::OnResize(UINT width,UINT height)
{
  m_graphics->OnResize(width,height);
}

Window& Game::GetWindow()
{
  return *m_window;
}

GraphicsCore& Game::GetGraphics()
{
  return *m_graphics;
}

UINT Game::GetMSPerFrame() const
{
  return m_mspf;
}

void Game::SetMSPerFrame(UINT mspf)
{
  m_mspf = mspf;
}

void Game::ResizeHandler(void* arg,UINT width,UINT height)
{
  Game* game = (Game*)arg;
  game->OnResize(width,height);
}
