#include "private_inc/Time/TickTimer.h"

TickTimer::TickTimer()
{
  m_ref_time = GetTickCount();
}

bool TickTimer::CheckDelta(UINT ms)
{
  DWORD curr_time = GetTickCount();
  if ((curr_time - m_ref_time) >= ms)
  {
    m_ref_time = curr_time;
    
    return true;
  }
  
  return false;
}
