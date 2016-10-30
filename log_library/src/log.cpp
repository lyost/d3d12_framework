#include <fstream>
#include <windows.h>
#include "../public_inc/log.h"
using namespace std;
    
/// <summary>
/// which mechanism to use
/// </summary>
static LogMechanism mechanism = LOG_NONE;
    
/// <summary>
/// if m_mechanism is set to LOG_FILE, then a pointer to the ofstream for the
/// file
/// otherwise, NULL
/// </summary>
static ofstream* file = NULL;

void log_mechanism(LogMechanism mech,const WCHAR* path)
{
  // cleanup the old mechanism
  if (mechanism == LOG_FILE && file)
  {
    delete file;
    file = NULL;
  }
  
  // prep the new mechanism for new messages
  mechanism = mech;
  if (mechanism == LOG_FILE && path)
  {
    file = new ofstream(path);
    if (file->good())
    {
      delete file;
      file = NULL;
    }
  }
}

void log_close()
{
  delete file;
  file = NULL;
  mechanism = LOG_NONE;
}

void log_print(const char* message)
{
  switch (mechanism)
  {
    case LOG_NONE:
      // no need to do anything
      break;
      
    case LOG_DEBUG_STRING:
      OutputDebugStringA(message);
      break;
      
    case LOG_FILE:
      if (file)
      {
        (*file) << message;
      }
      break;
      
    case LOG_MESSAGE_BOX:
      MessageBoxA(NULL,message,"Error",MB_OK);
      break;
  }
}

void log_print(const WCHAR* message)
{
  switch (mechanism)
  {
    case LOG_NONE:
      // no need to do anything
      break;
      
    case LOG_DEBUG_STRING:
      OutputDebugStringW(message);
      break;
      
    case LOG_FILE:
      if (file)
      {
        (*file) << message;
      }
      break;
      
    case LOG_MESSAGE_BOX:
      MessageBoxW(NULL,message,L"Error",MB_OK);
      break;
  }
}

bool log_good()
{
  return mechanism != LOG_FILE || (file != NULL && file->good());
}

bool log_would_output()
{
  return (mechanism != LOG_NONE && mechanism != LOG_FILE)
    || (mechanism == LOG_FILE && file && file->good());
}
