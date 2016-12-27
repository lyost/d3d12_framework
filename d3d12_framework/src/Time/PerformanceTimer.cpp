#include "private_inc/Time/PerformanceTimer.h"

PerformanceTimer* PerformanceTimer::Create()
{
  LARGE_INTEGER freq;
  if (!QueryPerformanceFrequency(&freq))
  {
    return NULL;
  }
  else if (freq.QuadPart == 0)
  {
    return NULL;
  }
  
  return new PerformanceTimer(freq.QuadPart / 1000.0f);
}

PerformanceTimer::PerformanceTimer(float freq)
:m_freq(freq)
{
  QueryPerformanceCounter(&m_ref_time);
}

bool PerformanceTimer::CheckDelta(UINT ms)
{
  LARGE_INTEGER curr_time;
  QueryPerformanceCounter(&curr_time);
  float delta = (curr_time.QuadPart - m_ref_time.QuadPart) / m_freq;
  if (delta >= ms)
  {
    m_ref_time = curr_time;
    
    return true;
  }
  
  return false;
}