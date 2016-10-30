#include "Time/Timer.h"
#include "Time/PerformanceTimer.h"
#include "Time/TickTimer.h"

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
