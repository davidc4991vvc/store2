<<<<<<< HEAD
// ConsoleCloseUtils.h

#ifndef __CONSOLECLOSEUTILS_H
#define __CONSOLECLOSEUTILS_H

namespace NConsoleClose {

bool TestBreakSignal();
=======
// ConsoleClose.h

#ifndef __CONSOLE_CLOSE_H
#define __CONSOLE_CLOSE_H

namespace NConsoleClose {

extern unsigned g_BreakCounter;

inline bool TestBreakSignal()
{
  #ifdef UNDER_CE
  return false;
  #else
  return (g_BreakCounter != 0);
  #endif
}
>>>>>>> upstream/master

class CCtrlHandlerSetter
{
public:
  CCtrlHandlerSetter();
  virtual ~CCtrlHandlerSetter();
};

class CCtrlBreakException
{};

<<<<<<< HEAD
void CheckCtrlBreak();
=======
// void CheckCtrlBreak();
>>>>>>> upstream/master

}

#endif
