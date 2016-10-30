#include <cstring>
#include "Input/MouseState.h"

MouseState::MouseState()
:m_x(0),
 m_y(0),
 m_scroll_x(0),
 m_scroll_y(0)
{
  memset(m_buttons,0,sizeof(m_buttons));
}

void MouseState::SetPos(int x,int y)
{
  m_x = x;
  m_y = y;
}

void MouseState::AdjustWheelX(int delta)
{
  m_scroll_x += delta;
}

void MouseState::AdjustWheelY(int delta)
{
  m_scroll_y += delta;
}

void MouseState::SetButtonDown(Buttons button)
{
  m_buttons[button] = true;
}

void MouseState::SetButtonUp(Buttons button)
{
  m_buttons[button] = false;
}

int MouseState::GetXPos() const
{
  return m_x;
}

int MouseState::GetYPos() const
{
  return m_y;
}

int MouseState::GetWheelX() const
{
  return m_scroll_x;
}

int MouseState::GetWheelY() const
{
  return m_scroll_y;
}

bool MouseState::IsButtonPressed(Buttons button) const
{
  return m_buttons[button];
}
