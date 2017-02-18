#include <windows.h>
#include "GameMain.h"
#include "log.h"

int WINAPI wWinMain(HINSTANCE instance,HINSTANCE prev_instance,
  LPWSTR cmd_line,int cmd_show)
{
  // setup the logger
  log_mechanism(LOG_DEBUG_STRING,NULL);
  
  // create a test game
  GameMain* game = new GameMain(L"test window");
  
  // allow it to run
  game->Run();
  
  // cleanup and exit
  delete game;
  log_close();
  return 0;
}
