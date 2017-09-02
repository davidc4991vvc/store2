// MainAr.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include "Common/MyException.h"
#include "Common/StdOutStream.h"

#include "Windows/Error.h"
#include "Windows/NtCheck.h"
=======
#include "../../../Common/MyException.h"
#include "../../../Common/StdOutStream.h"

#include "../../../Windows/ErrorMsg.h"
#include "../../../Windows/NtCheck.h"
>>>>>>> upstream/master

#include "../Common/ArchiveCommandLine.h"
#include "../Common/ExitCode.h"

#include "ConsoleClose.h"

using namespace NWindows;

<<<<<<< HEAD
CStdOutStream *g_StdStream = 0;

extern int Main2(
  #ifndef _WIN32
  int numArgs, const char *args[]
  #endif
);

static const char *kExceptionErrorMessage = "\n\nError:\n";
static const char *kUserBreak  = "\nBreak signaled\n";
static const char *kMemoryExceptionMessage = "\n\nERROR: Can't allocate required memory!\n";
static const char *kUnknownExceptionMessage = "\n\nUnknown Error\n";
static const char *kInternalExceptionMessage = "\n\nInternal Error #";

#define NT_CHECK_FAIL_ACTION (*g_StdStream) << "Unsupported Windows version"; return NExitCode::kFatalError;
=======
CStdOutStream *g_StdStream = NULL;
CStdOutStream *g_ErrStream = NULL;

extern int Main2(
  #ifndef _WIN32
  int numArgs, char *args[]
  #endif
);

static const char *kException_CmdLine_Error_Message = "Command Line Error:";
static const char *kExceptionErrorMessage = "ERROR:";
static const char *kUserBreakMessage  = "Break signaled";
static const char *kMemoryExceptionMessage = "ERROR: Can't allocate required memory!";
static const char *kUnknownExceptionMessage = "Unknown Error";
static const char *kInternalExceptionMessage = "\n\nInternal Error #";

static void FlushStreams()
{
  if (g_StdStream)
    g_StdStream->Flush();
}

static void PrintError(const char *message)
{
  FlushStreams();
  if (g_ErrStream)
    *g_ErrStream << "\n\n" << message << endl;
}

#define NT_CHECK_FAIL_ACTION *g_StdStream << "Unsupported Windows version"; return NExitCode::kFatalError;
>>>>>>> upstream/master

int MY_CDECL main
(
  #ifndef _WIN32
<<<<<<< HEAD
  int numArgs, const char *args[]
  #endif
)
{
=======
  int numArgs, char *args[]
  #endif
)
{
  g_ErrStream = &g_StdErr;
>>>>>>> upstream/master
  g_StdStream = &g_StdOut;

  NT_CHECK

  NConsoleClose::CCtrlHandlerSetter ctrlHandlerSetter;
  int res = 0;
<<<<<<< HEAD
=======
  
>>>>>>> upstream/master
  try
  {
    res = Main2(
    #ifndef _WIN32
    numArgs, args
    #endif
    );
  }
  catch(const CNewException &)
  {
<<<<<<< HEAD
    (*g_StdStream) << kMemoryExceptionMessage;
=======
    PrintError(kMemoryExceptionMessage);
>>>>>>> upstream/master
    return (NExitCode::kMemoryError);
  }
  catch(const NConsoleClose::CCtrlBreakException &)
  {
<<<<<<< HEAD
    (*g_StdStream) << endl << kUserBreak;
    return (NExitCode::kUserBreak);
  }
  catch(const CArchiveCommandLineException &e)
  {
    (*g_StdStream) << kExceptionErrorMessage << e << endl;
=======
    PrintError(kUserBreakMessage);
    return (NExitCode::kUserBreak);
  }
  catch(const CArcCmdLineException &e)
  {
    PrintError(kException_CmdLine_Error_Message);
    if (g_ErrStream)
      *g_ErrStream << e << endl;
>>>>>>> upstream/master
    return (NExitCode::kUserError);
  }
  catch(const CSystemException &systemError)
  {
    if (systemError.ErrorCode == E_OUTOFMEMORY)
    {
<<<<<<< HEAD
      (*g_StdStream) << kMemoryExceptionMessage;
=======
      PrintError(kMemoryExceptionMessage);
>>>>>>> upstream/master
      return (NExitCode::kMemoryError);
    }
    if (systemError.ErrorCode == E_ABORT)
    {
<<<<<<< HEAD
      (*g_StdStream) << endl << kUserBreak;
      return (NExitCode::kUserBreak);
    }
    (*g_StdStream) << endl << endl << "System error:" << endl <<
        NError::MyFormatMessageW(systemError.ErrorCode) << endl;
=======
      PrintError(kUserBreakMessage);
      return (NExitCode::kUserBreak);
    }
    if (g_ErrStream)
    {
      PrintError("System ERROR:");
      *g_ErrStream << NError::MyFormatMessage(systemError.ErrorCode) << endl;
    }
>>>>>>> upstream/master
    return (NExitCode::kFatalError);
  }
  catch(NExitCode::EEnum &exitCode)
  {
<<<<<<< HEAD
    (*g_StdStream) << kInternalExceptionMessage << exitCode << endl;
    return (exitCode);
  }
  /*
  catch(const NExitCode::CMultipleErrors &multipleErrors)
  {
    (*g_StdStream) << endl << multipleErrors.NumErrors << " errors" << endl;
    return (NExitCode::kFatalError);
  }
  */
  catch(const UString &s)
  {
    (*g_StdStream) << kExceptionErrorMessage << s << endl;
=======
    FlushStreams();
    if (g_ErrStream)
      *g_ErrStream << kInternalExceptionMessage << exitCode << endl;
    return (exitCode);
  }
  catch(const UString &s)
  {
    if (g_ErrStream)
    {
      PrintError(kExceptionErrorMessage);
      *g_ErrStream << s << endl;
    }
>>>>>>> upstream/master
    return (NExitCode::kFatalError);
  }
  catch(const AString &s)
  {
<<<<<<< HEAD
    (*g_StdStream) << kExceptionErrorMessage << s << endl;
=======
    if (g_ErrStream)
    {
      PrintError(kExceptionErrorMessage);
      *g_ErrStream << s << endl;
    }
>>>>>>> upstream/master
    return (NExitCode::kFatalError);
  }
  catch(const char *s)
  {
<<<<<<< HEAD
    (*g_StdStream) << kExceptionErrorMessage << s << endl;
    return (NExitCode::kFatalError);
  }
  catch(int t)
  {
    (*g_StdStream) << kInternalExceptionMessage << t << endl;
    return (NExitCode::kFatalError);
  }
  catch(...)
  {
    (*g_StdStream) << kUnknownExceptionMessage;
    return (NExitCode::kFatalError);
  }
  return  res;
=======
    if (g_ErrStream)
    {
      PrintError(kExceptionErrorMessage);
      *g_ErrStream << s << endl;
    }
    return (NExitCode::kFatalError);
  }
  catch(const wchar_t *s)
  {
    if (g_ErrStream)
    {
      PrintError(kExceptionErrorMessage);
      *g_ErrStream << s << endl;
    }
    return (NExitCode::kFatalError);
  }
  catch(int t)
  {
    if (g_ErrStream)
    {
      FlushStreams();
      *g_ErrStream << kInternalExceptionMessage << t << endl;
      return (NExitCode::kFatalError);
    }
  }
  catch(...)
  {
    PrintError(kUnknownExceptionMessage);
    return (NExitCode::kFatalError);
  }

  return res;
>>>>>>> upstream/master
}
