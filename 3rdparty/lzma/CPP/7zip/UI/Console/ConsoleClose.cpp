// ConsoleClose.cpp

#include "StdAfx.h"

#include "ConsoleClose.h"

<<<<<<< HEAD
static int g_BreakCounter = 0;
static const int kBreakAbortThreshold = 2;

namespace NConsoleClose {

=======
#if !defined(UNDER_CE) && defined(_WIN32)
#include "../../../Common/MyWindows.h"
#endif

namespace NConsoleClose {

unsigned g_BreakCounter = 0;
static const unsigned kBreakAbortThreshold = 2;

>>>>>>> upstream/master
#if !defined(UNDER_CE) && defined(_WIN32)
static BOOL WINAPI HandlerRoutine(DWORD ctrlType)
{
  if (ctrlType == CTRL_LOGOFF_EVENT)
  {
    // printf("\nCTRL_LOGOFF_EVENT\n");
    return TRUE;
  }

  g_BreakCounter++;
  if (g_BreakCounter < kBreakAbortThreshold)
    return TRUE;
  return FALSE;
  /*
<<<<<<< HEAD
  switch(ctrlType)
=======
  switch (ctrlType)
>>>>>>> upstream/master
  {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
      if (g_BreakCounter < kBreakAbortThreshold)
      return TRUE;
  }
  return FALSE;
  */
}
#endif

<<<<<<< HEAD
bool TestBreakSignal()
{
  #ifdef UNDER_CE
  return false;
  #else
  /*
  if (g_BreakCounter > 0)
    return true;
  */
  return (g_BreakCounter > 0);
  #endif
}

=======
/*
>>>>>>> upstream/master
void CheckCtrlBreak()
{
  if (TestBreakSignal())
    throw CCtrlBreakException();
}
<<<<<<< HEAD
=======
*/
>>>>>>> upstream/master

CCtrlHandlerSetter::CCtrlHandlerSetter()
{
  #if !defined(UNDER_CE) && defined(_WIN32)
<<<<<<< HEAD
  if(!SetConsoleCtrlHandler(HandlerRoutine, TRUE))
=======
  if (!SetConsoleCtrlHandler(HandlerRoutine, TRUE))
>>>>>>> upstream/master
    throw "SetConsoleCtrlHandler fails";
  #endif
}

CCtrlHandlerSetter::~CCtrlHandlerSetter()
{
  #if !defined(UNDER_CE) && defined(_WIN32)
<<<<<<< HEAD
  if(!SetConsoleCtrlHandler(HandlerRoutine, FALSE))
    throw "SetConsoleCtrlHandler fails";
=======
  if (!SetConsoleCtrlHandler(HandlerRoutine, FALSE))
  {
    // warning for throw in destructor.
    // throw "SetConsoleCtrlHandler fails";
  }
>>>>>>> upstream/master
  #endif
}

}
