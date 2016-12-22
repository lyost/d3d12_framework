#include "Window.h"
#include <windowsx.h>
#include <sstream>
#include "log.h"
using namespace std;

map<HWND,Window*> Window::s_wnds;

/// <summary>
/// Helper function for WndProc for processing WM_KEYDOWN/UP messages to check
/// whether it is an extended key that is pressed or not
/// </summary>
/// <param name="lparam">
/// the lparam received by WndProc
/// </param>
/// <returns>
/// true if it is an extended key
/// false otherwise
/// </returns>
static bool IsExtendedKey(LPARAM lparam)
{
  return (lparam & (1 << 24)) != 0;
}

Window::Window()
:m_instance(0),
 m_wnd(0),
 m_class_name(NULL),
 m_closed(false),
 m_resize_handler(NULL),
 m_arg(NULL),
 m_mouse_visible(false)
{
}

Window::~Window()
{
  if (m_closed == false)
  {
    DestroyWindow(m_wnd);
  }
  UnregisterClass(m_class_name,m_instance);
  
  // remove the window from the map
  s_wnds.erase(m_wnd);
}

Window* Window::CreateDefaultWindow(WCHAR* title,
  void (*resize_handler)(void*,UINT,UINT),void* arg)
{
  Window* back           = new Window;
  back->m_instance       = GetModuleHandle(NULL);
  back->m_class_name     = title;
  back->m_resize_handler = resize_handler;
  back->m_arg            = arg;
  
  // register class
  WNDCLASSEX wcex;
  wcex.cbSize        = sizeof(wcex);
  wcex.style         = CS_HREDRAW|CS_VREDRAW;
  wcex.lpfnWndProc   = WndProc;
  wcex.cbClsExtra    = 0;
  wcex.cbWndExtra    = 0;
  wcex.hInstance     = back->m_instance;
  wcex.hIcon         = LoadIcon(back->m_instance,IDI_APPLICATION);
  wcex.hCursor       = LoadCursor(NULL,IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wcex.lpszMenuName  = NULL;
  wcex.lpszClassName = back->m_class_name;
  wcex.hIconSm       = wcex.hIcon;
  if (!RegisterClassEx(&wcex))
  {
    back->m_class_name = NULL;
    delete back;
    return NULL;
  }

  // create window
  RECT rc = { 0, 0, 640, 480 };
  AdjustWindowRect(&rc,WS_OVERLAPPEDWINDOW,FALSE);
  back->m_wnd = CreateWindow(wcex.lpszClassName,title,WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,CW_USEDEFAULT,rc.right - rc.left,rc.bottom - rc.top,NULL,
    NULL,back->m_instance,NULL);
  if (!back->m_wnd)
  {
    delete back;
    return NULL;
  }
  
  // now that the window was created with a non-null hCursor, set the mouse
  // pointer displaying to true
  back->m_mouse_visible = true;

  // display the window
  ShowWindow(back->m_wnd,1);
  
  // add the window to the map of handles to windows
  s_wnds.insert(make_pair(back->m_wnd,back));

  return back;
}

HWND& Window::GetHandle()
{
  return m_wnd;
}

void Window::ShowMousePointer(bool show)
{
  if (m_mouse_visible != show)
  {
    ShowCursor(show);
    m_mouse_visible = show;
  }
}

bool Window::ConstrainMousePointer(bool constrain)
{
  if (constrain)
  {
    RECT rect;
    if (GetWindowRect(m_wnd,&rect))
    {
      return ClipCursor(&rect) != 0;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return ClipCursor(NULL) != 0;
  }
}

void Window::Resize(int width,int height)
{
  // take into account the non-client part of the window
  // not implemented: might need to be updated for handling full screen
  RECT rect = { 0, 0, width, height };
  AdjustWindowRect(&rect,WS_OVERLAPPEDWINDOW,FALSE);
  width  = rect.right - rect.left;
  height = rect.bottom - rect.top;
  
  // perform the resize
  BOOL rc = SetWindowPos(m_wnd,0,0,0,width,height,SWP_NOMOVE|SWP_NOZORDER);
  if (!rc)
  {
    if (log_would_output())
    {
      ostringstream out;
      out << "Failed to resize window. Error code: " << GetLastError() << '\n';
      log_print(out.str().c_str());
    }
  }
}

void Window::GetWindowClientDim(UINT& width,UINT& height) const
{
  RECT rect;
  GetClientRect(m_wnd,&rect);
  width  = rect.right  - rect.left;
  height = rect.bottom - rect.top;
}

bool Window::GetDesktopSize(UINT& width,UINT& height) const
{
  width = GetSystemMetrics(SM_CXSCREEN);
  if (width == 0)
  {
    if (log_would_output())
    {
      ostringstream out;
      out << "Failed to get desktop width, error code " << GetLastError()
          << '\n';
      log_print(out.str().c_str());
    }
    return false;
  }
  
  height = GetSystemMetrics(SM_CYSCREEN);
  if (height == 0)
  {
    if (log_would_output())
    {
      ostringstream out;
      out << "Failed to get desktop height, error code " << GetLastError()
          << '\n';
      log_print(out.str().c_str());
    }
    return false;
  }
  
  return true;
}

const MouseState& Window::GetMouseState() const
{
  return m_mouse;
}

const KeyboardState& Window::GetKeyboardState() const
{
  return m_keyboard;
}

LRESULT CALLBACK Window::WndProc(HWND wnd,UINT message,WPARAM wparam,
  LPARAM lparam)
{
  LRESULT back = 0;
  
  PAINTSTRUCT ps;
  
  // find the matching window instance
  map<HWND,Window*>::iterator wnd_it = s_wnds.find(wnd);
  
  // if the window instance is unknown, then default processing
  if (wnd_it == s_wnds.end())
  {
    return DefWindowProc(wnd,message,wparam,lparam);
  }
  
  // otherwise, handle cared about messages
  switch (message)
  {
    case WM_PAINT:
      BeginPaint(wnd,&ps);
      EndPaint(wnd,&ps);
      break;

    case WM_DESTROY:
      wnd_it->second->m_closed = true;
      PostQuitMessage(0);
      break;
      
    case WM_KEYDOWN:
      wnd_it->second->m_keyboard.SetKeyDown((int)wparam,IsExtendedKey(lparam));
      break;
      
    case WM_KEYUP:
      wnd_it->second->m_keyboard.SetKeyUp((int)wparam,IsExtendedKey(lparam));
      break;
      
    case WM_MOUSEMOVE:
      wnd_it->second->m_mouse.SetPos(
        GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
      break;
      
    case WM_LBUTTONDOWN:
      wnd_it->second->m_mouse.SetButtonDown(MouseState::LEFT);
      break;
      
    case WM_LBUTTONUP:
      wnd_it->second->m_mouse.SetButtonUp(MouseState::LEFT);
      break;
      
    case WM_RBUTTONDOWN:
      wnd_it->second->m_mouse.SetButtonDown(MouseState::RIGHT);
      break;
      
    case WM_RBUTTONUP:
      wnd_it->second->m_mouse.SetButtonUp(MouseState::RIGHT);
      break;
      
    case WM_MBUTTONDOWN:
      wnd_it->second->m_mouse.SetButtonDown(MouseState::MIDDLE);
      break;
      
    case WM_MBUTTONUP:
      wnd_it->second->m_mouse.SetButtonUp(MouseState::MIDDLE);
      break;
      
    case WM_XBUTTONDOWN:
      wnd_it->second->m_mouse.SetButtonDown(
        GET_XBUTTON_WPARAM(wparam) == XBUTTON1 ?
        MouseState::X1 : MouseState::X2);
      back = TRUE;
      break;
      
    case WM_XBUTTONUP:
      wnd_it->second->m_mouse.SetButtonUp(
        GET_XBUTTON_WPARAM(wparam) == XBUTTON1 ?
        MouseState::X1 : MouseState::X2);
      back = TRUE;
      break;
      
    case WM_MOUSEWHEEL:
      wnd_it->second->m_mouse.AdjustWheelY(GET_WHEEL_DELTA_WPARAM(wparam));
      break;
      
    case WM_MOUSEHWHEEL:
      wnd_it->second->m_mouse.AdjustWheelX(GET_WHEEL_DELTA_WPARAM(wparam));
      break;
      
    case WM_SIZE:
      wnd_it->second->m_resize_handler(wnd_it->second->m_arg,LOWORD(lparam),
        HIWORD(lparam));
      break;
      
    default:
      return DefWindowProc(wnd,message,wparam,lparam);
  }

  return back;
}
