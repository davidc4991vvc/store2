// ArchiveCommandLine.h

#ifndef __ARCHIVE_COMMAND_LINE_H
#define __ARCHIVE_COMMAND_LINE_H

<<<<<<< HEAD
#include "Common/CommandLineParser.h"
#include "Common/Wildcard.h"

#include "Extract.h"
#include "Update.h"

struct CArchiveCommandLineException: public AString
{
  CArchiveCommandLineException(const char *errorMessage): AString(errorMessage) {}
=======
#include "../../../Common/CommandLineParser.h"
#include "../../../Common/Wildcard.h"

#include "Extract.h"
#include "HashCalc.h"
#include "Update.h"

struct CArcCmdLineException: public UString
{
  CArcCmdLineException(const char *a, const wchar_t *u = NULL);
>>>>>>> upstream/master
};

namespace NCommandType { enum EEnum
{
  kAdd = 0,
  kUpdate,
  kDelete,
  kTest,
  kExtract,
<<<<<<< HEAD
  kFullExtract,
  kList,
  kBenchmark,
  kInfo
};}

namespace NRecursedType { enum EEnum
{
  kRecursed,
  kWildCardOnlyRecursed,
  kNonRecursed
};}

struct CArchiveCommand
{
  NCommandType::EEnum CommandType;
  bool IsFromExtractGroup() const;
  bool IsFromUpdateGroup() const;
  bool IsTestMode() const { return CommandType == NCommandType::kTest; }
  NExtract::NPathMode::EEnum GetPathMode() const;
};

struct CArchiveCommandLineOptions
{
  bool HelpMode;

  #ifdef _WIN32
  bool LargePages;
  #endif
=======
  kExtractFull,
  kList,
  kBenchmark,
  kInfo,
  kHash,
  kRename
};}

struct CArcCommand
{
  NCommandType::EEnum CommandType;

  bool IsFromExtractGroup() const;
  bool IsFromUpdateGroup() const;
  bool IsTestCommand() const { return CommandType == NCommandType::kTest; }
  NExtract::NPathMode::EEnum GetPathMode() const;
};

enum
{
  k_OutStream_disabled = 0,
  k_OutStream_stdout = 1,
  k_OutStream_stderr = 2
};

struct CArcCmdLineOptions
{
  bool HelpMode;

  bool LargePages;
  bool CaseSensitiveChange;
  bool CaseSensitive;
>>>>>>> upstream/master

  bool IsInTerminal;
  bool IsStdOutTerminal;
  bool IsStdErrTerminal;
  bool StdInMode;
  bool StdOutMode;
  bool EnableHeaders;

  bool YesToAll;
  bool ShowDialog;
<<<<<<< HEAD
  // NWildcard::CCensor ArchiveWildcardCensor;
  NWildcard::CCensor WildcardCensor;

  CArchiveCommand Command;
=======
  NWildcard::CCensor Censor;

  CArcCommand Command;
>>>>>>> upstream/master
  UString ArchiveName;

  #ifndef _NO_CRYPTO
  bool PasswordEnabled;
  UString Password;
  #endif

  bool TechMode;
<<<<<<< HEAD
  // Extract
  bool CalcCrc;
  bool AppendName;
  FString OutputDir;
  NExtract::NOverwriteMode::EEnum OverwriteMode;
  UStringVector ArchivePathsSorted;
  UStringVector ArchivePathsFullSorted;
  CObjectVector<CProperty> Properties;

  CUpdateOptions UpdateOptions;
  UString ArcType;
  bool EnablePercents;
=======
  bool ShowTime;
  
  UStringVector HashMethods;

  bool AppendName;
  // UStringVector ArchivePathsSorted;
  // UStringVector ArchivePathsFullSorted;
  NWildcard::CCensor arcCensor;
  UString ArcName_for_StdInMode;

  CObjectVector<CProperty> Properties;

  CExtractOptionsBase ExtractOptions;

  CBoolPair NtSecurity;
  CBoolPair AltStreams;
  CBoolPair HardLinks;
  CBoolPair SymLinks;

  CUpdateOptions UpdateOptions;
  CHashOptions HashOptions;
  UString ArcType;
  UStringVector ExcludedArcTypes;
  
  unsigned Number_for_Out;
  unsigned Number_for_Errors;
  unsigned Number_for_Percents;
  unsigned LogLevel;

  // bool IsOutAllowed() const { return Number_for_Out != k_OutStream_disabled; }
>>>>>>> upstream/master

  // Benchmark
  UInt32 NumIterations;

<<<<<<< HEAD
  CArchiveCommandLineOptions(): StdInMode(false), StdOutMode(false) {};
};

class CArchiveCommandLineParser
{
  NCommandLineParser::CParser parser;
public:
  CArchiveCommandLineParser();
  void Parse1(const UStringVector &commandStrings, CArchiveCommandLineOptions &options);
  void Parse2(CArchiveCommandLineOptions &options);
};

void EnumerateDirItemsAndSort(NWildcard::CCensor &wildcardCensor,
    UStringVector &sortedPaths,
    UStringVector &sortedFullPaths);
=======
  CArcCmdLineOptions():
      LargePages(false),
      CaseSensitiveChange(false),
      CaseSensitive(false),

      StdInMode(false),
      StdOutMode(false),

      Number_for_Out(k_OutStream_stdout),
      Number_for_Errors(k_OutStream_stderr),
      Number_for_Percents(k_OutStream_stdout),

      LogLevel(0)
  {
  };
};

class CArcCmdLineParser
{
  NCommandLineParser::CParser parser;
public:
  CArcCmdLineParser();
  void Parse1(const UStringVector &commandStrings, CArcCmdLineOptions &options);
  void Parse2(CArcCmdLineOptions &options);
};

HRESULT EnumerateDirItemsAndSort(
    NWildcard::CCensor &censor,
    NWildcard::ECensorPathMode pathMode,
    const UString &addPathPrefix,
    UStringVector &sortedPaths,
    UStringVector &sortedFullPaths,
    CDirItemsStat &st,
    IDirItemsCallback *callback);
>>>>>>> upstream/master

#endif
