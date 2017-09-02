// Main.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#if defined( _WIN32) && defined( _7ZIP_LARGE_PAGES)
#include "../../../../C/Alloc.h"
#endif

#include "Common/MyInitGuid.h"

#include "Common/CommandLineParser.h"
#include "Common/IntToString.h"
#include "Common/MyException.h"
#include "Common/StdOutStream.h"
#include "Common/StringConvert.h"
#include "Common/StringToInt.h"

#include "Windows/Error.h"
#ifdef _WIN32
#include "Windows/MemoryLock.h"
#endif

#include "../Common/ArchiveCommandLine.h"
#include "../Common/ExitCode.h"
#include "../Common/Extract.h"
=======
#include "../../../Common/MyWindows.h"

#ifdef _WIN32
#include <Psapi.h>
#endif

#include "../../../../C/CpuArch.h"

#if defined( _7ZIP_LARGE_PAGES)
#include "../../../../C/Alloc.h"
#endif

#include "../../../Common/MyInitGuid.h"

#include "../../../Common/CommandLineParser.h"
#include "../../../Common/IntToString.h"
#include "../../../Common/MyException.h"
#include "../../../Common/StringConvert.h"
#include "../../../Common/StringToInt.h"
#include "../../../Common/UTFConvert.h"

#include "../../../Windows/ErrorMsg.h"

#ifdef _WIN32
#include "../../../Windows/MemoryLock.h"
#endif

#include "../../../Windows/TimeUtils.h"

#include "../Common/ArchiveCommandLine.h"
#include "../Common/ExitCode.h"
#include "../Common/Extract.h"

>>>>>>> upstream/master
#ifdef EXTERNAL_CODECS
#include "../Common/LoadCodecs.h"
#endif

<<<<<<< HEAD
#include "BenchCon.h"
=======
#include "../../Common/RegisterCodec.h"

#include "BenchCon.h"
#include "ConsoleClose.h"
>>>>>>> upstream/master
#include "ExtractCallbackConsole.h"
#include "List.h"
#include "OpenCallbackConsole.h"
#include "UpdateCallbackConsole.h"

<<<<<<< HEAD
#if !defined(EXTERNAL_CODECS) && defined(_NO_CRYPTO)
#define IT_IS_REDUCED_VERSION
#endif

#ifdef IT_IS_REDUCED_VERSION
=======
#include "HashCon.h"

#ifdef PROG_VARIANT_R
>>>>>>> upstream/master
#include "../../../../C/7zVersion.h"
#else
#include "../../MyVersion.h"
#endif

using namespace NWindows;
using namespace NFile;
using namespace NCommandLineParser;

#ifdef _WIN32
HINSTANCE g_hInstance = 0;
#endif
<<<<<<< HEAD
extern CStdOutStream *g_StdStream;

static const char *kCopyrightString = "\n7-Zip"
#ifndef EXTERNAL_CODECS
#ifdef IT_IS_REDUCED_VERSION
=======

extern CStdOutStream *g_StdStream;
extern CStdOutStream *g_ErrStream;

extern unsigned g_NumCodecs;
extern const CCodecInfo *g_Codecs[];

extern unsigned g_NumHashers;
extern const CHasherInfo *g_Hashers[];

static const char *kCopyrightString = "\n7-Zip"
#ifndef EXTERNAL_CODECS
#ifdef PROG_VARIANT_R
>>>>>>> upstream/master
" (r)"
#else
" (a)"
#endif
#endif

<<<<<<< HEAD
#ifdef _WIN64
" [64]"
#endif

" " MY_VERSION_COPYRIGHT_DATE "\n";

static const char *kHelpString =
    "\nUsage: 7z"
#ifndef EXTERNAL_CODECS
#ifdef IT_IS_REDUCED_VERSION
=======
#ifdef MY_CPU_64BIT
" [64]"
#elif defined MY_CPU_32BIT
" [32]"
#endif

" " MY_VERSION_COPYRIGHT_DATE "\n\n";

static const char *kHelpString =
    "Usage: 7z"
#ifndef EXTERNAL_CODECS
#ifdef PROG_VARIANT_R
>>>>>>> upstream/master
    "r"
#else
    "a"
#endif
#endif
    " <command> [<switches>...] <archive_name> [<file_names>...]\n"
    "       [<@listfiles...>]\n"
    "\n"
    "<Commands>\n"
<<<<<<< HEAD
    "  a: Add files to archive\n"
    "  b: Benchmark\n"
    "  d: Delete files from archive\n"
    "  e: Extract files from archive (without using directory names)\n"
    "  l: List contents of archive\n"
//    "  l[a|t][f]: List contents of archive\n"
//    "    a - with Additional fields\n"
//    "    t - with all fields\n"
//    "    f - with Full pathnames\n"
    "  t: Test integrity of archive\n"
    "  u: Update files to archive\n"
    "  x: eXtract files with full paths\n"
    "<Switches>\n"
    "  -ai[r[-|0]]{@listfile|!wildcard}: Include archives\n"
    "  -ax[r[-|0]]{@listfile|!wildcard}: eXclude archives\n"
    "  -bd: Disable percentage indicator\n"
    "  -i[r[-|0]]{@listfile|!wildcard}: Include filenames\n"
    "  -m{Parameters}: set compression Method\n"
    "  -o{Directory}: set Output directory\n"
    #ifndef _NO_CRYPTO
    "  -p{Password}: set Password\n"
    #endif
    "  -r[-|0]: Recurse subdirectories\n"
    "  -scs{UTF-8 | WIN | DOS}: set charset for list files\n"
    "  -sfx[{name}]: Create SFX archive\n"
    "  -si[{name}]: read data from stdin\n"
    "  -slt: show technical information for l (List) command\n"
    "  -so: write data to stdout\n"
    "  -ssc[-]: set sensitive case mode\n"
    "  -ssw: compress shared files\n"
    "  -t{Type}: Set type of archive\n"
    "  -u[-][p#][q#][r#][x#][y#][z#][!newArchiveName]: Update options\n"
    "  -v{Size}[b|k|m|g]: Create volumes\n"
    "  -w[{path}]: assign Work directory. Empty path means a temporary directory\n"
    "  -x[r[-|0]]]{@listfile|!wildcard}: eXclude filenames\n"
    "  -y: assume Yes on all queries\n";
=======
    "  a : Add files to archive\n"
    "  b : Benchmark\n"
    "  d : Delete files from archive\n"
    "  e : Extract files from archive (without using directory names)\n"
    "  h : Calculate hash values for files\n"
    "  i : Show information about supported formats\n"
    "  l : List contents of archive\n"
    "  rn : Rename files in archive\n"
    "  t : Test integrity of archive\n"
    "  u : Update files to archive\n"
    "  x : eXtract files with full paths\n"
    "\n"
    "<Switches>\n"
    "  -- : Stop switches parsing\n"
    "  -ai[r[-|0]]{@listfile|!wildcard} : Include archives\n"
    "  -ax[r[-|0]]{@listfile|!wildcard} : eXclude archives\n"
    "  -ao{a|s|t|u} : set Overwrite mode\n"
    "  -an : disable archive_name field\n"
    "  -bb[0-3] : set output log level\n"
    "  -bd : disable progress indicator\n"
    "  -bs{o|e|p}{0|1|2} : set output stream for output/error/progress line\n"
    "  -bt : show execution time statistics\n"
    "  -i[r[-|0]]{@listfile|!wildcard} : Include filenames\n"
    "  -m{Parameters} : set compression Method\n"
    "    -mmt[N] : set number of CPU threads\n"
    "  -o{Directory} : set Output directory\n"
    #ifndef _NO_CRYPTO
    "  -p{Password} : set Password\n"
    #endif
    "  -r[-|0] : Recurse subdirectories\n"
    "  -sa{a|e|s} : set Archive name mode\n"
    "  -scc{UTF-8|WIN|DOS} : set charset for for console input/output\n"
    "  -scs{UTF-8|UTF-16LE|UTF-16BE|WIN|DOS|{id}} : set charset for list files\n"
    "  -scrc[CRC32|CRC64|SHA1|SHA256|*] : set hash function for x, e, h commands\n"
    "  -sdel : delete files after compression\n"
    "  -seml[.] : send archive by email\n"
    "  -sfx[{name}] : Create SFX archive\n"
    "  -si[{name}] : read data from stdin\n"
    "  -slp : set Large Pages mode\n"
    "  -slt : show technical information for l (List) command\n"
    "  -snh : store hard links as links\n"
    "  -snl : store symbolic links as links\n"
    "  -sni : store NT security information\n"
    "  -sns[-] : store NTFS alternate streams\n"
    "  -so : write data to stdout\n"
    "  -spd : disable wildcard matching for file names\n"
    "  -spe : eliminate duplication of root folder for extract command\n"
    "  -spf : use fully qualified file paths\n"
    "  -ssc[-] : set sensitive case mode\n"
    "  -ssw : compress shared files\n"
    "  -stl : set archive timestamp from the most recently modified file\n"
    "  -stm{HexMask} : set CPU thread affinity mask (hexadecimal number)\n"
    "  -stx{Type} : exclude archive type\n"
    "  -t{Type} : Set type of archive\n"
    "  -u[-][p#][q#][r#][x#][y#][z#][!newArchiveName] : Update options\n"
    "  -v{Size}[b|k|m|g] : Create volumes\n"
    "  -w[{path}] : assign Work directory. Empty path means a temporary directory\n"
    "  -x[r[-|0]]{@listfile|!wildcard} : eXclude filenames\n"
    "  -y : assume Yes on all queries\n";
>>>>>>> upstream/master

// ---------------------------
// exception messages

static const char *kEverythingIsOk = "Everything is Ok";
static const char *kUserErrorMessage = "Incorrect command line";
static const char *kNoFormats = "7-Zip cannot find the code that works with archives.";
static const char *kUnsupportedArcTypeMessage = "Unsupported archive type";
<<<<<<< HEAD

static CFSTR kDefaultSfxModule = FTEXT("7zCon.sfx");

static void ShowMessageAndThrowException(CStdOutStream &s, LPCSTR message, NExitCode::EEnum code)
{
  s << message << endl;
  throw code;
}

static void PrintHelpAndExit(CStdOutStream &s)
{
  s << kHelpString;
  ShowMessageAndThrowException(s, kUserErrorMessage, NExitCode::kUserError);
}

=======
// static const char *kUnsupportedUpdateArcType = "Can't create archive for that type";

static CFSTR kDefaultSfxModule = FTEXT("7zCon.sfx");

static void ShowMessageAndThrowException(LPCSTR message, NExitCode::EEnum code)
{
  if (g_ErrStream)
    *g_ErrStream << endl << "ERROR: " << message << endl;
  throw code;
}

>>>>>>> upstream/master
#ifndef _WIN32
static void GetArguments(int numArgs, const char *args[], UStringVector &parts)
{
  parts.Clear();
  for (int i = 0; i < numArgs; i++)
  {
    UString s = MultiByteToUnicodeString(args[i]);
    parts.Add(s);
  }
}
#endif

<<<<<<< HEAD
static void ShowCopyrightAndHelp(CStdOutStream &s, bool needHelp)
{
  s << kCopyrightString;
  // s << "# CPUs: " << (UInt64)NWindows::NSystem::GetNumberOfProcessors() << "\n";
  if (needHelp)
    s << kHelpString;
}

#ifdef EXTERNAL_CODECS
static void PrintString(CStdOutStream &stdStream, const AString &s, int size)
{
  int len = s.Length();
  stdStream << s;
  for (int i = len; i < size; i++)
    stdStream << ' ';
}
#endif

static void PrintString(CStdOutStream &stdStream, const UString &s, int size)
{
  int len = s.Length();
  stdStream << s;
  for (int i = len; i < size; i++)
    stdStream << ' ';
}

static inline char GetHex(Byte value)
{
  return (char)((value < 10) ? ('0' + value) : ('A' + (value - 10)));
=======
static void ShowCopyrightAndHelp(CStdOutStream *so, bool needHelp)
{
  if (!so)
    return;
  *so << kCopyrightString;
  // *so << "# CPUs: " << (UInt64)NWindows::NSystem::GetNumberOfProcessors() << endl;
  if (needHelp)
    *so << kHelpString;
}


static void PrintStringRight(CStdOutStream &so, const AString &s, unsigned size)
{
  unsigned len = s.Len();
  for (unsigned i = len; i < size; i++)
    so << ' ';
  so << s;
}

static void PrintUInt32(CStdOutStream &so, UInt32 val, unsigned size)
{
  char s[16];
  ConvertUInt32ToString(val, s);
  PrintStringRight(so, s, size);
}

static void PrintLibIndex(CStdOutStream &so, int libIndex)
{
  if (libIndex >= 0)
    PrintUInt32(so, libIndex, 2);
  else
    so << "  ";
  so << ' ';
}

static void PrintString(CStdOutStream &so, const UString &s, unsigned size)
{
  unsigned len = s.Len();
  so << s;
  for (unsigned i = len; i < size; i++)
    so << ' ';
}

static inline char GetHex(unsigned val)
{
  return (char)((val < 10) ? ('0' + val) : ('A' + (val - 10)));
}

static void PrintWarningsPaths(const CErrorPathCodes &pc, CStdOutStream &so)
{
  FOR_VECTOR(i, pc.Paths)
  {
    so << pc.Paths[i] << " : ";
    so << NError::MyFormatMessage(pc.Codes[i]) << endl;
  }
  so << "----------------" << endl;
}

static int WarningsCheck(HRESULT result, const CCallbackConsoleBase &callback,
    const CUpdateErrorInfo &errorInfo,
    CStdOutStream *so,
    CStdOutStream *se,
    bool showHeaders)
{
  int exitCode = NExitCode::kSuccess;
  
  if (callback.ScanErrors.Paths.Size() != 0)
  {
    if (se)
    {
      *se << endl;
      *se << "Scan WARNINGS for files and folders:" << endl << endl;
      PrintWarningsPaths(callback.ScanErrors, *se);
      *se << "Scan WARNINGS: " << callback.ScanErrors.Paths.Size();
      *se << endl;
    }
    exitCode = NExitCode::kWarning;
  }
  
  if (result != S_OK || errorInfo.ThereIsError())
  {
    if (se)
    {
      UString message;
      if (!errorInfo.Message.IsEmpty())
      {
        message.AddAscii(errorInfo.Message);
        message.Add_LF();
      }
      {
        FOR_VECTOR(i, errorInfo.FileNames)
        {
          message += fs2us(errorInfo.FileNames[i]);
          message.Add_LF();
        }
      }
      if (errorInfo.SystemError != 0)
      {
        message += NError::MyFormatMessage(errorInfo.SystemError);
        message.Add_LF();
      }
      if (!message.IsEmpty())
        *se << L"\nError:\n" << message;
    }

    // we will work with (result) later
    // throw CSystemException(result);
    return NExitCode::kFatalError;
  }

  unsigned numErrors = callback.FailedFiles.Paths.Size();
  if (numErrors == 0)
  {
    if (showHeaders)
      if (callback.ScanErrors.Paths.Size() == 0)
        if (so)
        {
          if (se)
            se->Flush();
          *so << kEverythingIsOk << endl;
        }
  }
  else
  {
    if (se)
    {
      *se << endl;
      *se << "WARNINGS for files:" << endl << endl;
      PrintWarningsPaths(callback.FailedFiles, *se);
      *se << "WARNING: Cannot open " << numErrors << " file";
      if (numErrors > 1)
        *se << 's';
      *se << endl;
    }
    exitCode = NExitCode::kWarning;
  }
  
  return exitCode;
}

static void ThrowException_if_Error(HRESULT res)
{
  if (res != S_OK)
    throw CSystemException(res);
}


static void PrintNum(UInt64 val, unsigned numDigits, char c = ' ')
{
  char temp[64];
  char *p = temp + 32;
  ConvertUInt64ToString(val, p);
  unsigned len = MyStringLen(p);
  for (; len < numDigits; len++)
    *--p = c;
  *g_StdStream << p;
}

static void PrintTime(const char *s, UInt64 val, UInt64 total)
{
  *g_StdStream << endl << s << " Time =";
  const UInt32 kFreq = 10000000;
  UInt64 sec = val / kFreq;
  PrintNum(sec, 6);
  *g_StdStream << '.';
  UInt32 ms = (UInt32)(val - (sec * kFreq)) / (kFreq / 1000);
  PrintNum(ms, 3, '0');
  
  while (val > ((UInt64)1 << 56))
  {
    val >>= 1;
    total >>= 1;
  }

  UInt64 percent = 0;
  if (total != 0)
    percent = val * 100 / total;
  *g_StdStream << " =";
  PrintNum(percent, 5);
  *g_StdStream << '%';
}

#ifndef UNDER_CE

#define SHIFT_SIZE_VALUE(x, num) (((x) + (1 << (num)) - 1) >> (num))

static void PrintMemUsage(const char *s, UInt64 val)
{
  *g_StdStream << "    " << s << " Memory =";
  PrintNum(SHIFT_SIZE_VALUE(val, 20), 7);
  *g_StdStream << " MB";
}

EXTERN_C_BEGIN
typedef BOOL (WINAPI *Func_GetProcessMemoryInfo)(HANDLE Process,
    PPROCESS_MEMORY_COUNTERS ppsmemCounters, DWORD cb);
EXTERN_C_END

#endif

static inline UInt64 GetTime64(const FILETIME &t) { return ((UInt64)t.dwHighDateTime << 32) | t.dwLowDateTime; }

static void PrintStat()
{
  FILETIME creationTimeFT, exitTimeFT, kernelTimeFT, userTimeFT;
  if (!
      #ifdef UNDER_CE
        ::GetThreadTimes(::GetCurrentThread()
      #else
        // NT 3.5
        ::GetProcessTimes(::GetCurrentProcess()
      #endif
      , &creationTimeFT, &exitTimeFT, &kernelTimeFT, &userTimeFT))
    return;
  FILETIME curTimeFT;
  NTime::GetCurUtcFileTime(curTimeFT);

  #ifndef UNDER_CE
  
  PROCESS_MEMORY_COUNTERS m;
  memset(&m, 0, sizeof(m));
  BOOL memDefined = FALSE;
  {
    /* NT 4.0: GetProcessMemoryInfo() in Psapi.dll
       Win7: new function K32GetProcessMemoryInfo() in kernel32.dll
       It's faster to call kernel32.dll code than Psapi.dll code
       GetProcessMemoryInfo() requires Psapi.lib
       Psapi.lib in SDK7+ can link to K32GetProcessMemoryInfo in kernel32.dll
       The program with K32GetProcessMemoryInfo will not work on systems before Win7
       // memDefined = GetProcessMemoryInfo(GetCurrentProcess(), &m, sizeof(m));
    */

    Func_GetProcessMemoryInfo my_GetProcessMemoryInfo = (Func_GetProcessMemoryInfo)
        ::GetProcAddress(::GetModuleHandleW(L"kernel32.dll"), "K32GetProcessMemoryInfo");
    if (!my_GetProcessMemoryInfo)
    {
      HMODULE lib = LoadLibraryW(L"Psapi.dll");
      if (lib)
        my_GetProcessMemoryInfo = (Func_GetProcessMemoryInfo)::GetProcAddress(lib, "GetProcessMemoryInfo");
    }
    if (my_GetProcessMemoryInfo)
      memDefined = my_GetProcessMemoryInfo(GetCurrentProcess(), &m, sizeof(m));
    // FreeLibrary(lib);
  }

  #endif

  UInt64 curTime = GetTime64(curTimeFT);
  UInt64 creationTime = GetTime64(creationTimeFT);
  UInt64 kernelTime = GetTime64(kernelTimeFT);
  UInt64 userTime = GetTime64(userTimeFT);

  UInt64 totalTime = curTime - creationTime;
  
  PrintTime("Kernel ", kernelTime, totalTime);
  PrintTime("User   ", userTime, totalTime);
  
  PrintTime("Process", kernelTime + userTime, totalTime);
  #ifndef UNDER_CE
  if (memDefined) PrintMemUsage("Virtual ", m.PeakPagefileUsage);
  #endif
  
  PrintTime("Global ", totalTime, totalTime);
  #ifndef UNDER_CE
  if (memDefined) PrintMemUsage("Physical", m.PeakWorkingSetSize);
  #endif
  
  *g_StdStream << endl;
}

static void PrintHexId(CStdOutStream &so, UInt64 id)
{
  char s[32];
  ConvertUInt64ToHex(id, s);
  PrintStringRight(so, s, 8);
>>>>>>> upstream/master
}

int Main2(
  #ifndef _WIN32
<<<<<<< HEAD
  int numArgs, const char *args[]
=======
  int numArgs, char *args[]
>>>>>>> upstream/master
  #endif
)
{
  #if defined(_WIN32) && !defined(UNDER_CE)
  SetFileApisToOEM();
  #endif
<<<<<<< HEAD
  
  UStringVector commandStrings;
=======

  UStringVector commandStrings;
  
>>>>>>> upstream/master
  #ifdef _WIN32
  NCommandLineParser::SplitCommandLine(GetCommandLineW(), commandStrings);
  #else
  GetArguments(numArgs, args, commandStrings);
  #endif

  if (commandStrings.Size() == 1)
  {
<<<<<<< HEAD
    ShowCopyrightAndHelp(g_StdOut, true);
    return 0;
  }
  commandStrings.Delete(0);

  CArchiveCommandLineOptions options;

  CArchiveCommandLineParser parser;

  parser.Parse1(commandStrings, options);

  if (options.HelpMode)
  {
    ShowCopyrightAndHelp(g_StdOut, true);
    return 0;
  }

  #if defined(_WIN32) && defined(_7ZIP_LARGE_PAGES)
  if (options.LargePages)
  {
    SetLargePageSize();
    NSecurity::EnableLockMemoryPrivilege();
  }
  #endif

  CStdOutStream &stdStream = options.StdOutMode ? g_StdErr : g_StdOut;
  g_StdStream = &stdStream;

  if (options.EnableHeaders)
    ShowCopyrightAndHelp(stdStream, false);

  parser.Parse2(options);

  CCodecs *codecs = new CCodecs;
  CMyComPtr<
    #ifdef EXTERNAL_CODECS
    ICompressCodecsInfo
    #else
    IUnknown
    #endif
    > compressCodecsInfo = codecs;
  HRESULT result = codecs->Load();
  if (result != S_OK)
    throw CSystemException(result);
=======
    ShowCopyrightAndHelp(g_StdStream, true);
    return 0;
  }

  commandStrings.Delete(0);

  CArcCmdLineOptions options;

  CArcCmdLineParser parser;

  parser.Parse1(commandStrings, options);


  if (options.Number_for_Out != k_OutStream_stdout)
    g_StdStream = (options.Number_for_Out == k_OutStream_stderr ? &g_StdErr : NULL);

  if (options.Number_for_Errors != k_OutStream_stderr)
    g_ErrStream = (options.Number_for_Errors == k_OutStream_stdout ? &g_StdOut : NULL);

  CStdOutStream *percentsStream = NULL;
  if (options.Number_for_Percents != k_OutStream_disabled)
    percentsStream = (options.Number_for_Percents == k_OutStream_stderr) ? &g_StdErr : &g_StdOut;;
  
  if (options.HelpMode)
  {
    ShowCopyrightAndHelp(g_StdStream, true);
    return 0;
  }

  #if defined(_WIN32) && !defined(UNDER_CE)
  NSecurity::EnablePrivilege_SymLink();
  #endif
  
  #ifdef _7ZIP_LARGE_PAGES
  if (options.LargePages)
  {
    SetLargePageSize();
    #if defined(_WIN32) && !defined(UNDER_CE)
    NSecurity::EnablePrivilege_LockMemory();
    #endif
  }
  #endif

  if (options.EnableHeaders)
    ShowCopyrightAndHelp(g_StdStream, false);

  parser.Parse2(options);

  unsigned percentsNameLevel = 1;
  if (options.LogLevel == 0 || options.Number_for_Percents != options.Number_for_Out)
    percentsNameLevel = 2;

  unsigned consoleWidth = 80;

  if (percentsStream)
  {
    #ifdef _WIN32
    
    #if !defined(UNDER_CE)
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo))
      consoleWidth = consoleInfo.dwSize.X;
    #endif
    
    #else
    
    struct winsize w;
    if (ioctl(0, TIOCGWINSZ, &w) == )
      consoleWidth = w.ws_col;
    
    #endif
  }

  CREATE_CODECS_OBJECT

  codecs->CaseSensitiveChange = options.CaseSensitiveChange;
  codecs->CaseSensitive = options.CaseSensitive;
  ThrowException_if_Error(codecs->Load());
>>>>>>> upstream/master

  bool isExtractGroupCommand = options.Command.IsFromExtractGroup();

  if (codecs->Formats.Size() == 0 &&
<<<<<<< HEAD
        (isExtractGroupCommand ||
        options.Command.CommandType == NCommandType::kList ||
        options.Command.IsFromUpdateGroup()))
    throw kNoFormats;

  CIntVector formatIndices;
  if (!codecs->FindFormatForArchiveType(options.ArcType, formatIndices))
    throw kUnsupportedArcTypeMessage;

  if (options.Command.CommandType == NCommandType::kInfo)
  {
    stdStream << endl << "Formats:" << endl;
    int i;
    for (i = 0; i < codecs->Formats.Size(); i++)
    {
      const CArcInfoEx &arc = codecs->Formats[i];
      #ifdef EXTERNAL_CODECS
      if (arc.LibIndex >= 0)
      {
        char s[16];
        ConvertUInt32ToString(arc.LibIndex, s);
        PrintString(stdStream, s, 2);
      }
      else
      #endif
        stdStream << "  ";
      stdStream << ' ';
      stdStream << (char)(arc.UpdateEnabled ? 'C' : ' ');
      stdStream << (char)(arc.KeepName ? 'K' : ' ');
      stdStream << "  ";
      PrintString(stdStream, arc.Name, 6);
      stdStream << "  ";
      UString s;
      for (int t = 0; t < arc.Exts.Size(); t++)
      {
=======
        (isExtractGroupCommand
        || options.Command.CommandType == NCommandType::kList
        || options.Command.IsFromUpdateGroup()))
  {
    #ifdef EXTERNAL_CODECS
    if (!codecs->MainDll_ErrorPath.IsEmpty())
    {
      UString s = L"Can't load module ";
      s += fs2us(codecs->MainDll_ErrorPath);
      throw s;
    }
    #endif
    
    throw kNoFormats;
  }

  CObjectVector<COpenType> types;
  if (!ParseOpenTypes(*codecs, options.ArcType, types))
    throw kUnsupportedArcTypeMessage;

  CIntVector excludedFormats;
  FOR_VECTOR (k, options.ExcludedArcTypes)
  {
    CIntVector tempIndices;
    if (!codecs->FindFormatForArchiveType(options.ExcludedArcTypes[k], tempIndices)
        || tempIndices.Size() != 1)
      throw kUnsupportedArcTypeMessage;
    excludedFormats.AddToUniqueSorted(tempIndices[0]);
    // excludedFormats.Sort();
  }

  
  #ifdef EXTERNAL_CODECS
  if (isExtractGroupCommand
      || options.Command.CommandType == NCommandType::kHash
      || options.Command.CommandType == NCommandType::kBenchmark)
    ThrowException_if_Error(__externalCodecs.Load());
  #endif

  int retCode = NExitCode::kSuccess;
  HRESULT hresultMain = S_OK;

  // bool showStat = options.ShowTime;
  
  /*
  if (!options.EnableHeaders ||
      options.TechMode)
    showStat = false;
  */
  

  if (options.Command.CommandType == NCommandType::kInfo)
  {
    CStdOutStream &so = (g_StdStream ? *g_StdStream : g_StdOut);
    unsigned i;

    #ifdef EXTERNAL_CODECS
    so << endl << "Libs:" << endl;
    for (i = 0; i < codecs->Libs.Size(); i++)
    {
      PrintLibIndex(so, i);
      so << ' ' << codecs->Libs[i].Path << endl;
    }
    #endif

    so << endl << "Formats:" << endl;
    
    const char *kArcFlags = "KSNFMGOPBELH";
    const unsigned kNumArcFlags = (unsigned)strlen(kArcFlags);
    
    for (i = 0; i < codecs->Formats.Size(); i++)
    {
      const CArcInfoEx &arc = codecs->Formats[i];

      #ifdef EXTERNAL_CODECS
      PrintLibIndex(so, arc.LibIndex);
      #else
      so << "  ";
      #endif

      so << (char)(arc.UpdateEnabled ? 'C' : ' ');
      
      for (unsigned b = 0; b < kNumArcFlags; b++)
      {
        so << (char)
          ((arc.Flags & ((UInt32)1 << b)) != 0 ? kArcFlags[b] : ' ');
      }
        
      so << ' ';
      PrintString(so, arc.Name, 8);
      so << ' ';
      UString s;
      
      FOR_VECTOR (t, arc.Exts)
      {
        if (t != 0)
          s.Add_Space();
>>>>>>> upstream/master
        const CArcExtInfo &ext = arc.Exts[t];
        s += ext.Ext;
        if (!ext.AddExt.IsEmpty())
        {
          s += L" (";
          s += ext.AddExt;
          s += L')';
        }
<<<<<<< HEAD
        s += L' ';
      }
      PrintString(stdStream, s, 14);
      stdStream << "  ";
      const CByteBuffer &sig = arc.StartSignature;
      for (size_t j = 0; j < sig.GetCapacity(); j++)
      {
        Byte b = sig[j];
        if (b > 0x20 && b < 0x80)
        {
          stdStream << (char)b;
        }
        else
        {
          stdStream << GetHex((Byte)((b >> 4) & 0xF));
          stdStream << GetHex((Byte)(b & 0xF));
        }
        stdStream << ' ';
      }
      stdStream << endl;
    }
    stdStream << endl << "Codecs:" << endl;

    #ifdef EXTERNAL_CODECS
    UInt32 numMethods;
    if (codecs->GetNumberOfMethods(&numMethods) == S_OK)
    for (UInt32 j = 0; j < numMethods; j++)
    {
      int libIndex = codecs->GetCodecLibIndex(j);
      if (libIndex >= 0)
      {
        char s[16];
        ConvertUInt32ToString(libIndex, s);
        PrintString(stdStream, s, 2);
      }
      else
        stdStream << "  ";
      stdStream << ' ';
      stdStream << (char)(codecs->GetCodecEncoderIsAssigned(j) ? 'C' : ' ');
      UInt64 id;
      stdStream << "  ";
      HRESULT res = codecs->GetCodecId(j, id);
      if (res != S_OK)
        id = (UInt64)(Int64)-1;
      char s[32];
      ConvertUInt64ToString(id, s, 16);
      PrintString(stdStream, s, 8);
      stdStream << "  ";
      PrintString(stdStream, codecs->GetCodecName(j), 11);
      stdStream << endl;
      /*
      if (res != S_OK)
        throw "incorrect Codec ID";
      */
    }
    #endif
    return S_OK;
  }
  else if (options.Command.CommandType == NCommandType::kBenchmark)
  {
    {
      HRESULT res;
      #ifdef EXTERNAL_CODECS
      CObjectVector<CCodecInfoEx> externalCodecs;
      res = LoadExternalCodecs(compressCodecsInfo, externalCodecs);
      if (res != S_OK)
        throw CSystemException(res);
      #endif
      res = BenchCon(
          #ifdef EXTERNAL_CODECS
          compressCodecsInfo, &externalCodecs,
          #endif
          options.Properties, options.NumIterations, (FILE *)stdStream);
      if (res != S_OK)
      {
        if (res == S_FALSE)
        {
          stdStream << "\nDecoding Error\n";
          return NExitCode::kFatalError;
        }
        throw CSystemException(res);
      }
    }
  }
  else if (isExtractGroupCommand || options.Command.CommandType == NCommandType::kList)
  {
=======
      }
      
      PrintString(so, s, 13);
      so << ' ';
      
      if (arc.SignatureOffset != 0)
        so << "offset=" << arc.SignatureOffset << ' ';

      FOR_VECTOR(si, arc.Signatures)
      {
        if (si != 0)
          so << "  ||  ";

        const CByteBuffer &sig = arc.Signatures[si];
        
        for (size_t j = 0; j < sig.Size(); j++)
        {
          if (j != 0)
            so << ' ';
          Byte b = sig[j];
          if (b > 0x20 && b < 0x80)
          {
            so << (char)b;
          }
          else
          {
            so << GetHex((b >> 4) & 0xF);
            so << GetHex(b & 0xF);
          }
        }
      }
      so << endl;
    }

    so << endl << "Codecs:" << endl; //  << "Lib          ID Name" << endl;

    for (i = 0; i < g_NumCodecs; i++)
    {
      const CCodecInfo &cod = *g_Codecs[i];

      PrintLibIndex(so, -1);

      if (cod.NumStreams == 1)
        so << ' ';
      else
        so << cod.NumStreams;
      
      so << (char)(cod.CreateEncoder ? 'E' : ' ');
      so << (char)(cod.CreateDecoder ? 'D' : ' ');

      so << ' ';
      PrintHexId(so, cod.Id);
      so << ' ' << cod.Name << endl;
    }


    #ifdef EXTERNAL_CODECS

    UInt32 numMethods;
    if (codecs->GetNumMethods(&numMethods) == S_OK)
    for (UInt32 j = 0; j < numMethods; j++)
    {
      PrintLibIndex(so, codecs->GetCodec_LibIndex(j));

      UInt32 numStreams = codecs->GetCodec_NumStreams(j);
      if (numStreams == 1)
        so << ' ';
      else
        so << numStreams;
      
      so << (char)(codecs->GetCodec_EncoderIsAssigned(j) ? 'E' : ' ');
      so << (char)(codecs->GetCodec_DecoderIsAssigned(j) ? 'D' : ' ');

      so << ' ';
      UInt64 id;
      HRESULT res = codecs->GetCodec_Id(j, id);
      if (res != S_OK)
        id = (UInt64)(Int64)-1;
      PrintHexId(so, id);
      so << ' ' << codecs->GetCodec_Name(j) << endl;
    }

    #endif
    

    so << endl << "Hashers:" << endl; //  << " L Size       ID Name" << endl;

    for (i = 0; i < g_NumHashers; i++)
    {
      const CHasherInfo &codec = *g_Hashers[i];
      PrintLibIndex(so, -1);
      PrintUInt32(so, codec.DigestSize, 4);
      so << ' ';
      PrintHexId(so, codec.Id);
      so << ' ' << codec.Name << endl;
    }

    #ifdef EXTERNAL_CODECS
    
    numMethods = codecs->GetNumHashers();
    for (UInt32 j = 0; j < numMethods; j++)
    {
      PrintLibIndex(so, codecs->GetHasherLibIndex(j));
      PrintUInt32(so, codecs->GetHasherDigestSize(j), 4);
      so << ' ';
      PrintHexId(so, codecs->GetHasherId(j));
      so << ' ' << codecs->GetHasherName(j) << endl;
    }

    #endif
    
  }
  else if (options.Command.CommandType == NCommandType::kBenchmark)
  {
    CStdOutStream &so = (g_StdStream ? *g_StdStream : g_StdOut);
    hresultMain = BenchCon(EXTERNAL_CODECS_VARS_L
        options.Properties, options.NumIterations, (FILE *)so);
    if (hresultMain == S_FALSE)
    {
      if (g_ErrStream)
        *g_ErrStream << "\nDecoding ERROR\n";
      retCode = NExitCode::kFatalError;
      hresultMain = S_OK;
    }
  }
  else if (isExtractGroupCommand || options.Command.CommandType == NCommandType::kList)
  {
    UStringVector ArchivePathsSorted;
    UStringVector ArchivePathsFullSorted;

    if (options.StdInMode)
    {
      ArchivePathsSorted.Add(options.ArcName_for_StdInMode);
      ArchivePathsFullSorted.Add(options.ArcName_for_StdInMode);
    }
    else
    {
      CExtractScanConsole scan;
      
      scan.Init(options.EnableHeaders ? g_StdStream : NULL, g_ErrStream, percentsStream);
      scan.SetWindowWidth(consoleWidth);

      if (g_StdStream && options.EnableHeaders)
        *g_StdStream << "Scanning the drive for archives:" << endl;

      CDirItemsStat st;

      scan.StartScanning();

      hresultMain = EnumerateDirItemsAndSort(
          options.arcCensor,
          NWildcard::k_RelatPath,
          UString(), // addPathPrefix
          ArchivePathsSorted,
          ArchivePathsFullSorted,
          st,
          &scan);

      scan.CloseScanning();

      if (hresultMain == S_OK)
      {
        if (options.EnableHeaders)
          scan.PrintStat(st);
      }
      else
      {
        /*
        if (res != E_ABORT)
        {
          throw CSystemException(res);
          // errorInfo.Message = "Scanning error";
        }
        return res;
        */
      }
    }

    if (hresultMain == S_OK)
>>>>>>> upstream/master
    if (isExtractGroupCommand)
    {
      CExtractCallbackConsole *ecs = new CExtractCallbackConsole;
      CMyComPtr<IFolderArchiveExtractCallback> extractCallback = ecs;

<<<<<<< HEAD
      ecs->OutStream = &stdStream;

=======
>>>>>>> upstream/master
      #ifndef _NO_CRYPTO
      ecs->PasswordIsDefined = options.PasswordEnabled;
      ecs->Password = options.Password;
      #endif

<<<<<<< HEAD
      ecs->Init();

      COpenCallbackConsole openCallback;
      openCallback.OutStream = &stdStream;
=======
      ecs->Init(g_StdStream, g_ErrStream, percentsStream);
      ecs->MultiArcMode = (ArchivePathsSorted.Size() > 1);

      ecs->LogLevel = options.LogLevel;
      ecs->PercentsNameLevel = percentsNameLevel;
      
      if (percentsStream)
        ecs->SetWindowWidth(consoleWidth);

      /*
      COpenCallbackConsole openCallback;
      openCallback.Init(g_StdStream, g_ErrStream);
>>>>>>> upstream/master

      #ifndef _NO_CRYPTO
      openCallback.PasswordIsDefined = options.PasswordEnabled;
      openCallback.Password = options.Password;
      #endif
<<<<<<< HEAD

      CExtractOptions eo;
      eo.StdInMode = options.StdInMode;
      eo.StdOutMode = options.StdOutMode;
      eo.PathMode = options.Command.GetPathMode();
      eo.TestMode = options.Command.IsTestMode();
      eo.OverwriteMode = options.OverwriteMode;
      eo.OutputDir = options.OutputDir;
      eo.YesToAll = options.YesToAll;
      eo.CalcCrc = options.CalcCrc;
      #if !defined(_7ZIP_ST) && !defined(_SFX)
      eo.Properties = options.Properties;
      #endif
      UString errorMessage;
      CDecompressStat stat;
      HRESULT result = DecompressArchives(
          codecs,
          formatIndices,
          options.ArchivePathsSorted,
          options.ArchivePathsFullSorted,
          options.WildcardCensor.Pairs.Front().Head,
          eo, &openCallback, ecs, errorMessage, stat);
      if (!errorMessage.IsEmpty())
      {
        stdStream << endl << "Error: " << errorMessage;
        if (result == S_OK)
          result = E_FAIL;
      }

      stdStream << endl;
      if (ecs->NumArchives > 1)
        stdStream << "Archives: " << ecs->NumArchives << endl;
      if (ecs->NumArchiveErrors != 0 || ecs->NumFileErrors != 0)
      {
        if (ecs->NumArchives > 1)
        {
          stdStream << endl;
          if (ecs->NumArchiveErrors != 0)
            stdStream << "Archive Errors: " << ecs->NumArchiveErrors << endl;
          if (ecs->NumFileErrors != 0)
            stdStream << "Sub items Errors: " << ecs->NumFileErrors << endl;
        }
        if (result != S_OK)
          throw CSystemException(result);
        return NExitCode::kFatalError;
      }
      if (result != S_OK)
        throw CSystemException(result);
      if (stat.NumFolders != 0)
        stdStream << "Folders: " << stat.NumFolders << endl;
      if (stat.NumFiles != 1 || stat.NumFolders != 0)
          stdStream << "Files: " << stat.NumFiles << endl;
      stdStream
           << "Size:       " << stat.UnpackSize << endl
           << "Compressed: " << stat.PackSize << endl;
      if (options.CalcCrc)
      {
        char s[16];
        ConvertUInt32ToHexWithZeros(stat.CrcSum, s);
        stdStream << "CRC: " << s << endl;
=======
      */

      CExtractOptions eo;
      (CExtractOptionsBase &)eo = options.ExtractOptions;
      
      eo.StdInMode = options.StdInMode;
      eo.StdOutMode = options.StdOutMode;
      eo.YesToAll = options.YesToAll;
      eo.TestMode = options.Command.IsTestCommand();
      
      #ifndef _SFX
      eo.Properties = options.Properties;
      #endif

      UString errorMessage;
      CDecompressStat stat;
      CHashBundle hb;
      IHashCalc *hashCalc = NULL;

      if (!options.HashMethods.IsEmpty())
      {
        hashCalc = &hb;
        ThrowException_if_Error(hb.SetMethods(EXTERNAL_CODECS_VARS_L options.HashMethods));
        hb.Init();
      }
      
      hresultMain = Extract(
          codecs,
          types,
          excludedFormats,
          ArchivePathsSorted,
          ArchivePathsFullSorted,
          options.Censor.Pairs.Front().Head,
          eo, ecs, ecs, hashCalc, errorMessage, stat);
      
      ecs->ClosePercents();

      if (!errorMessage.IsEmpty())
      {
        if (g_ErrStream)
          *g_ErrStream << endl << "ERROR:" << endl << errorMessage << endl;
        if (hresultMain == S_OK)
          hresultMain = E_FAIL;
      }

      CStdOutStream *so = g_StdStream;

      bool isError = false;

      if (so)
      {
        *so << endl;
        
        if (ecs->NumTryArcs > 1)
        {
          *so << "Archives: " << ecs->NumTryArcs << endl;
          *so << "OK archives: " << ecs->NumOkArcs << endl;
        }
      }

      if (ecs->NumCantOpenArcs != 0)
      {
        isError = true;
        if (so)
          *so << "Can't open as archive: " << ecs->NumCantOpenArcs << endl;
      }
      
      if (ecs->NumArcsWithError != 0)
      {
        isError = true;
        if (so)
          *so << "Archives with Errors: " << ecs->NumArcsWithError << endl;
      }
      
      if (so)
      {
        if (ecs->NumArcsWithWarnings != 0)
          *so << "Archives with Warnings: " << ecs->NumArcsWithWarnings << endl;
        
        if (ecs->NumOpenArcWarnings != 0)
        {
          *so << endl;
          if (ecs->NumOpenArcWarnings != 0)
            *so << "Warnings: " << ecs->NumOpenArcWarnings << endl;
        }
      }
      
      if (ecs->NumOpenArcErrors != 0)
      {
        isError = true;
        if (so)
        {
          *so << endl;
          if (ecs->NumOpenArcErrors != 0)
            *so << "Open Errors: " << ecs->NumOpenArcErrors << endl;
        }
      }

      if (isError)
        retCode = NExitCode::kFatalError;
      
      if (so)
      if (ecs->NumArcsWithError != 0 || ecs->NumFileErrors != 0)
      {
        // if (ecs->NumArchives > 1)
        {
          *so << endl;
          if (ecs->NumFileErrors != 0)
            *so << "Sub items Errors: " << ecs->NumFileErrors << endl;
        }
      }
      else if (hresultMain == S_OK)
      {
        if (stat.NumFolders != 0)
          *so << "Folders: " << stat.NumFolders << endl;
        if (stat.NumFiles != 1 || stat.NumFolders != 0 || stat.NumAltStreams != 0)
          *so << "Files: " << stat.NumFiles << endl;
        if (stat.NumAltStreams != 0)
        {
          *so << "Alternate Streams: " << stat.NumAltStreams << endl;
          *so << "Alternate Streams Size: " << stat.AltStreams_UnpackSize << endl;
        }
        
        *so
          << "Size:       " << stat.UnpackSize << endl
          << "Compressed: " << stat.PackSize << endl;
        if (hashCalc)
        {
          *so << endl;
          PrintHashStat(*so, hb);
        }
>>>>>>> upstream/master
      }
    }
    else
    {
      UInt64 numErrors = 0;
<<<<<<< HEAD
      HRESULT result = ListArchives(
          codecs,
          formatIndices,
          options.StdInMode,
          options.ArchivePathsSorted,
          options.ArchivePathsFullSorted,
          options.WildcardCensor.Pairs.Front().Head,
=======
      UInt64 numWarnings = 0;
      
      // options.ExtractNtOptions.StoreAltStreams = true, if -sns[-] is not definmed

      hresultMain = ListArchives(
          codecs,
          types,
          excludedFormats,
          options.StdInMode,
          ArchivePathsSorted,
          ArchivePathsFullSorted,
          options.ExtractOptions.NtOptions.AltStreams.Val,
          options.AltStreams.Val, // we don't want to show AltStreams by default
          options.Censor.Pairs.Front().Head,
>>>>>>> upstream/master
          options.EnableHeaders,
          options.TechMode,
          #ifndef _NO_CRYPTO
          options.PasswordEnabled,
          options.Password,
          #endif
<<<<<<< HEAD
          numErrors);
      if (numErrors > 0)
      {
        g_StdOut << endl << "Errors: " << numErrors << endl;
        return NExitCode::kFatalError;
      }
      if (result != S_OK)
        throw CSystemException(result);
=======
          &options.Properties,
          numErrors, numWarnings);

      if (options.EnableHeaders)
        if (numWarnings > 0)
          g_StdOut << endl << "Warnings: " << numWarnings << endl;
      
      if (numErrors > 0)
      {
        if (options.EnableHeaders)
          g_StdOut << endl << "Errors: " << numErrors << endl;
        retCode = NExitCode::kFatalError;
      }
>>>>>>> upstream/master
    }
  }
  else if (options.Command.IsFromUpdateGroup())
  {
    CUpdateOptions &uo = options.UpdateOptions;
    if (uo.SfxMode && uo.SfxModule.IsEmpty())
      uo.SfxModule = kDefaultSfxModule;

    COpenCallbackConsole openCallback;
<<<<<<< HEAD
    openCallback.OutStream = &stdStream;

    #ifndef _NO_CRYPTO
    bool passwordIsDefined =
        options.PasswordEnabled && !options.Password.IsEmpty();
=======
    openCallback.Init(g_StdStream, g_ErrStream, percentsStream);

    #ifndef _NO_CRYPTO
    bool passwordIsDefined =
        (options.PasswordEnabled && !options.Password.IsEmpty());
>>>>>>> upstream/master
    openCallback.PasswordIsDefined = passwordIsDefined;
    openCallback.Password = options.Password;
    #endif

    CUpdateCallbackConsole callback;
<<<<<<< HEAD
    callback.EnablePercents = options.EnablePercents;

    #ifndef _NO_CRYPTO
    callback.PasswordIsDefined = passwordIsDefined;
    callback.AskPassword = options.PasswordEnabled && options.Password.IsEmpty();
    callback.Password = options.Password;
    #endif
    callback.StdOutMode = uo.StdOutMode;
    callback.Init(&stdStream);

    CUpdateErrorInfo errorInfo;

    if (!uo.Init(codecs, formatIndices, options.ArchiveName))
      throw kUnsupportedArcTypeMessage;
    HRESULT result = UpdateArchive(codecs,
        options.WildcardCensor, uo,
        errorInfo, &openCallback, &callback);

    int exitCode = NExitCode::kSuccess;
    if (callback.CantFindFiles.Size() > 0)
    {
      stdStream << endl;
      stdStream << "WARNINGS for files:" << endl << endl;
      int numErrors = callback.CantFindFiles.Size();
      for (int i = 0; i < numErrors; i++)
      {
        stdStream << callback.CantFindFiles[i] << " : ";
        stdStream << NError::MyFormatMessageW(callback.CantFindCodes[i]) << endl;
      }
      stdStream << "----------------" << endl;
      stdStream << "WARNING: Cannot find " << numErrors << " file";
      if (numErrors > 1)
        stdStream << "s";
      stdStream << endl;
      exitCode = NExitCode::kWarning;
    }

    if (result != S_OK)
    {
      UString message;
      if (!errorInfo.Message.IsEmpty())
      {
        message += errorInfo.Message;
        message += L"\n";
      }
      if (!errorInfo.FileName.IsEmpty())
      {
        message += fs2us(errorInfo.FileName);
        message += L"\n";
      }
      if (!errorInfo.FileName2.IsEmpty())
      {
        message += fs2us(errorInfo.FileName2);
        message += L"\n";
      }
      if (errorInfo.SystemError != 0)
      {
        message += NError::MyFormatMessageW(errorInfo.SystemError);
        message += L"\n";
      }
      if (!message.IsEmpty())
        stdStream << L"\nError:\n" << message;
      throw CSystemException(result);
    }
    int numErrors = callback.FailedFiles.Size();
    if (numErrors == 0)
    {
      if (callback.CantFindFiles.Size() == 0)
        stdStream << kEverythingIsOk << endl;
    }
    else
    {
      stdStream << endl;
      stdStream << "WARNINGS for files:" << endl << endl;
      for (int i = 0; i < numErrors; i++)
      {
        stdStream << callback.FailedFiles[i] << " : ";
        stdStream << NError::MyFormatMessageW(callback.FailedCodes[i]) << endl;
      }
      stdStream << "----------------" << endl;
      stdStream << "WARNING: Cannot open " << numErrors << " file";
      if (numErrors > 1)
        stdStream << "s";
      stdStream << endl;
      exitCode = NExitCode::kWarning;
    }
    return exitCode;
  }
  else
    PrintHelpAndExit(stdStream);
  return 0;
=======
    callback.LogLevel = options.LogLevel;
    callback.PercentsNameLevel = percentsNameLevel;

    if (percentsStream)
      callback.SetWindowWidth(consoleWidth);

    #ifndef _NO_CRYPTO
    callback.PasswordIsDefined = passwordIsDefined;
    callback.AskPassword = (options.PasswordEnabled && options.Password.IsEmpty());
    callback.Password = options.Password;
    #endif

    callback.StdOutMode = uo.StdOutMode;
    callback.Init(
      // NULL,
      g_StdStream, g_ErrStream, percentsStream);

    CUpdateErrorInfo errorInfo;

    /*
    if (!uo.Init(codecs, types, options.ArchiveName))
      throw kUnsupportedUpdateArcType;
    */
    hresultMain = UpdateArchive(codecs,
        types,
        options.ArchiveName,
        options.Censor,
        uo,
        errorInfo, &openCallback, &callback, true);

    callback.ClosePercents2();

    CStdOutStream *se = g_StdStream;
    if (!se)
      se = g_ErrStream;

    retCode = WarningsCheck(hresultMain, callback, errorInfo,
        g_StdStream, se,
        true // options.EnableHeaders
        );
  }
  else if (options.Command.CommandType == NCommandType::kHash)
  {
    const CHashOptions &uo = options.HashOptions;

    CHashCallbackConsole callback;
    if (percentsStream)
      callback.SetWindowWidth(consoleWidth);
  
    callback.Init(g_StdStream, g_ErrStream, percentsStream);
    callback.PrintHeaders = options.EnableHeaders;

    AString errorInfoString;
    hresultMain = HashCalc(EXTERNAL_CODECS_VARS_L
        options.Censor, uo,
        errorInfoString, &callback);
    CUpdateErrorInfo errorInfo;
    errorInfo.Message = errorInfoString;
    CStdOutStream *se = g_StdStream;
    if (!se)
      se = g_ErrStream;
    retCode = WarningsCheck(hresultMain, callback, errorInfo, g_StdStream, se, options.EnableHeaders);
  }
  else
    ShowMessageAndThrowException(kUserErrorMessage, NExitCode::kUserError);

  if (options.ShowTime && g_StdStream)
    PrintStat();

  ThrowException_if_Error(hresultMain);

  return retCode;
>>>>>>> upstream/master
}
