#ifndef PERFORMANCE_TIMER_H
#define PERFORMANCE_TIMER_H

#include "Time/Timer.h"

/// <summary>
/// High resolution performance counter based timer, requires hardware support
/// </summary>
class PerformanceTimer : public Timer
{
  public:
    /// <summary>
    /// Checks if a high resolution performance counter is supported.  If so,
    /// an instance of PerformanceTimer is created
    /// </summary>
    /// <returns>
    /// pointer to a PerformanceTimer
    /// NULL if a high resolution performance counter is not supported
    /// </returns>
    static PerformanceTimer* Create();
    
    /// <summary>
    /// Checks if the specified amount of time has ellapsed between now and the
    /// last stored reference time.  If it has, then the reference time is
    /// updated as well
    /// <summary>
    /// <param name="ms">
    /// desired number of milliseconds to have ellapsed
    /// </param>
    /// <returns>
    /// true  if the requested amount of time has ellapsed
    /// false otherwise
    /// </returns>
    bool CheckDelta(UINT ms);
    
  private:
    PerformanceTimer(float freq);
    
    /// <summary>
    /// number of ticks of the perfomance counter per ms
    /// </summary>
    float m_freq;
    
    /// <summary>
    /// reference time
    /// </summary>
    LARGE_INTEGER m_ref_time;
};

#endif /* PERFORMANCE_TIMER_H */
