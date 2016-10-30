#include "Input/KeyboardState.h"
#include <windows.h>
#include <winuser.h>
using namespace std;

// since Microsoft doesn't define the max virtual key code, do it to one beyond
// the max they document
static const int VK_MAX = VK_OEM_CLEAR + 1;

KeyboardState::KeyboardState()
{
  // init to no keys pressed for all virtual key codes
  m_pressed.resize(VK_MAX * 2);
  for (vector<bool>::size_type i = 0; i < VK_MAX * 2; ++i)
  {
    m_pressed.push_back(false);
  }
}

void KeyboardState::SetKeyDown(int key,bool extended)
{
  m_pressed[ToIndex(key,extended)] = true;
}

void KeyboardState::SetKeyUp(int key,bool extended)
{
  m_pressed[ToIndex(key,extended)] = false;
}

bool KeyboardState::IsKeyDown(int key,bool extended) const
{
  return m_pressed[ToIndex(key,extended)];
}

vector<bool>::size_type KeyboardState::ToIndex(int key,bool extended) const
{
  return key * 2 + (extended ? 1 : 0);
}
