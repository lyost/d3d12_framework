#include "Time/Timer.h"
#include "private_inc/Time/PerformanceTimer.h"
#include "private_inc/Time/TickTimer.h"

Timer* Timer::GetTimer()
{
  // try to get a performance timer
  Timer* back = PerformanceTimer::Create();
  if (!back)
  {
    back = new TickTimer;
  }
  return back;
}

Timer::~Timer()
{
}
