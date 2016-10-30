#ifndef LOG_H
#define LOG_H

/// <summary>
/// Enum of various log mechanisms that are supported
/// </summary>
enum LogMechanism
{
  LOG_NONE = 0,
  LOG_DEBUG_STRING,
  LOG_FILE,
  LOG_MESSAGE_BOX
};

/// <summary>
/// Sets how messages should be logged
/// </summary>
/// <param name="mech">
/// which mechanism to use
/// </param>
/// <param name="path">
/// if mech is set to FILE, then the path to the file to output to
/// <remarks>
/// The file will be overwritten, and rolling when the file is full is
/// not implemented
/// </remarks>
/// </param>
void log_mechanism(LogMechanism mech,const WCHAR* path);

/// <summary>
/// Closes the current log
/// </summary>
void log_close();

/// <summary>
/// Logs the specified message
/// <remarks>
/// does not automatically include a newline at the end.  If that is
/// desired, then it needs to be part of the string pointed to by message
/// </remarks>
/// </summary>
/// <param name="message">
/// message to log
/// </param>
void log_print(const char* message);

/// <summary>
/// Logs the specified message
/// <remarks>
/// does not automatically include a newline at the end.  If that is
/// desired, then it needs to be part of the string pointed to by message
/// </remarks>
/// </summary>
/// <param name="message">
/// message to log
/// </param>
void log_print(const WCHAR* message);

/// <summary>
/// Checks whether the logging mechanism is currently ready for more output
/// or not
/// </summary>
/// <returns>
/// true if the logging mechanism is currently ready for more output
/// false if the logging mechanims can't handle output
/// </returns>
bool log_good();

/// <summary>
/// Checks whether the logging mechanism will actually output messagse
/// (usefui to check this before calling Print on a string that has
/// computed)
/// </summary>
/// <returns>
/// true if messages will be outputted somewhere
/// false otherwise
/// </returns>
bool log_would_output();


#endif /* LOG_H */
