#include "private_inc/Time/TickTimer.h"

TickTimer::TickTimer()
{
  m_ref_time = GetTickCount();
}

bool TickTimer::CheckDelta(UINT ms, UINT& actual_ms)
{
  DWORD curr_time = GetTickCount();
  DWORD delta = curr_time - m_ref_time;
  if (delta >= ms)
  {
    m_ref_time = curr_time;
    actual_ms = (UINT)delta;
    
    return true;
  }
  
  return false;
}
