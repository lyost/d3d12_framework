#ifndef TIMER_H
#define TIMER_H

#include <windows.h>

/// <summary>
/// Base class and factory for timers
/// </summary>
class Timer
{
  public:
    /// <summary>
    /// Retrieves the highest performance timer available
    /// </summary>
    /// <remarks>
    /// this is only expected to be called once per program execution, so the
    /// timers are not cached
    /// </remarks>
    /// <returns>
    /// pointer to a timer
    /// </returns>
    static Timer* GetTimer();
    
    virtual ~Timer();
    
    /// <summary>
    /// Checks if the specified amount of time has ellapsed between now and the
    /// last stored reference time.  If it has, then the reference time is
    /// updated as well
    /// <summary>
    /// <param name="ms">
    /// desired number of milliseconds to have ellapsed
    /// </param>
    /// <param name="actual_ms">
    /// actual number of milliseconds ellapsed when this function returns true
    /// </param>
    /// <returns>
    /// true  if the requested amount of time has ellapsed
    /// false otherwise
    /// </returns>
    virtual bool CheckDelta(UINT ms, UINT& actual_ms) = 0;
    
  private:
};

#endif /* TIMER_H */
