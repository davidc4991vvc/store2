// ArchiveCommandLine.cpp

#include "StdAfx.h"
<<<<<<< HEAD
=======
#undef printf
#undef sprintf
>>>>>>> upstream/master

#ifdef _WIN32
#ifndef UNDER_CE
#include <io.h>
#endif
#endif
#include <stdio.h>

<<<<<<< HEAD
#include "Common/ListFileUtils.h"
#include "Common/StringConvert.h"
#include "Common/StringToInt.h"

#include "Windows/FileDir.h"
#include "Windows/FileName.h"
#ifdef _WIN32
#include "Windows/FileMapping.h"
#include "Windows/Synchronization.h"
=======
#include "../../../Common/ListFileUtils.h"
#include "../../../Common/StringConvert.h"
#include "../../../Common/StringToInt.h"

#include "../../../Windows/FileDir.h"
#include "../../../Windows/FileName.h"
#ifdef _WIN32
#include "../../../Windows/FileMapping.h"
#include "../../../Windows/Synchronization.h"
>>>>>>> upstream/master
#endif

#include "ArchiveCommandLine.h"
#include "EnumDirItems.h"
#include "SortUtils.h"
#include "Update.h"
#include "UpdateAction.h"

extern bool g_CaseSensitive;

#ifdef UNDER_CE

#define MY_IS_TERMINAL(x) false;

#else

#if _MSC_VER >= 1400
#define MY_isatty_fileno(x) _isatty(_fileno(x))
#else
#define MY_isatty_fileno(x) isatty(fileno(x))
#endif

#define MY_IS_TERMINAL(x) (MY_isatty_fileno(x) != 0);

#endif

using namespace NCommandLineParser;
using namespace NWindows;
using namespace NFile;

<<<<<<< HEAD
=======
static bool StringToUInt32(const wchar_t *s, UInt32 &v)
{
  if (*s == 0)
    return false;
  const wchar_t *end;
  v = ConvertStringToUInt32(s, &end);
  return *end == 0;
}

CArcCmdLineException::CArcCmdLineException(const char *a, const wchar_t *u)
{
  (*this) += MultiByteToUnicodeString(a);
  if (u)
  {
    this->Add_LF();
    (*this) += u;
  }
}

>>>>>>> upstream/master
int g_CodePage = -1;

namespace NKey {
enum Enum
{
  kHelp1 = 0,
  kHelp2,
  kHelp3,
<<<<<<< HEAD
  kDisableHeaders,
  kDisablePercents,
  kArchiveType,
  kYes,
  #ifndef _NO_CRYPTO
  kPassword,
  #endif
  kProperty,
  kOutputDir,
  kWorkingDir,
=======
  
  kDisableHeaders,
  kDisablePercents,
  kShowTime,
  kLogLevel,

  kOutStream,
  kErrStream,
  kPercentStream,

  kYes,

  kShowDialog,
  kOverwrite,

  kArchiveType,
  kExcludedArcType,

  kProperty,
  kOutputDir,
  kWorkingDir,
  
>>>>>>> upstream/master
  kInclude,
  kExclude,
  kArInclude,
  kArExclude,
  kNoArName,
<<<<<<< HEAD
  kUpdate,
  kVolume,
  kRecursed,
  kSfx,
  kStdIn,
  kStdOut,
  kOverwrite,
  kEmail,
  kShowDialog,
=======

  kUpdate,
  kVolume,
  kRecursed,

  kAffinity,
  kSfx,
  kEmail,
  kHash,
 
  kStdIn,
  kStdOut,

>>>>>>> upstream/master
  kLargePages,
  kListfileCharSet,
  kConsoleCharSet,
  kTechMode,
<<<<<<< HEAD
  kShareForWrite,
  kCaseSensitive,
  kCalcCrc
=======
  
  kShareForWrite,
  kCaseSensitive,
  kArcNameMode,

  kDisableWildcardParsing,
  kElimDup,
  kFullPathMode,
  
  kHardLinks,
  kSymLinks,
  kNtSecurity,
  kAltStreams,
  kReplaceColonForAltStream,
  kWriteToAltStreamIfColon,

  kDeleteAfterCompressing,
  kSetArcMTime

  #ifndef _NO_CRYPTO
  , kPassword
  #endif
>>>>>>> upstream/master
};

}


<<<<<<< HEAD
static const wchar_t kRecursedIDChar = 'R';
static const wchar_t *kRecursedPostCharSet = L"0-";
=======
static const wchar_t kRecursedIDChar = 'r';
static const char *kRecursedPostCharSet = "0-";

static const char *k_ArcNameMode_PostCharSet = "sea";

static const char *k_Stream_PostCharSet = "012";

static inline const EArcNameMode ParseArcNameMode(int postCharIndex)
{
  switch (postCharIndex)
  {
    case 1: return k_ArcNameMode_Exact;
    case 2: return k_ArcNameMode_Add;
    default: return k_ArcNameMode_Smart;
  }
}
>>>>>>> upstream/master

namespace NRecursedPostCharIndex {
  enum EEnum
  {
<<<<<<< HEAD
    kWildCardRecursionOnly = 0,
=======
    kWildcardRecursionOnly = 0,
>>>>>>> upstream/master
    kNoRecursion = 1
  };
}

static const char kImmediateNameID = '!';
static const char kMapNameID = '#';
static const char kFileListID = '@';

static const char kSomeCludePostStringMinSize = 2; // at least <@|!><N>ame must be
static const char kSomeCludeAfterRecursedPostStringMinSize = 2; // at least <@|!><N>ame must be

<<<<<<< HEAD
static const wchar_t *kOverwritePostCharSet = L"asut";

NExtract::NOverwriteMode::EEnum k_OverwriteModes[] =
{
  NExtract::NOverwriteMode::kWithoutPrompt,
  NExtract::NOverwriteMode::kSkipExisting,
  NExtract::NOverwriteMode::kAutoRename,
  NExtract::NOverwriteMode::kAutoRenameExisting
};

static const CSwitchForm kSwitchForms[] =
  {
    { L"?",  NSwitchType::kSimple, false },
    { L"H",  NSwitchType::kSimple, false },
    { L"-HELP",  NSwitchType::kSimple, false },
    { L"BA", NSwitchType::kSimple, false },
    { L"BD", NSwitchType::kSimple, false },
    { L"T",  NSwitchType::kUnLimitedPostString, false, 1 },
    { L"Y",  NSwitchType::kSimple, false },
    #ifndef _NO_CRYPTO
    { L"P",  NSwitchType::kUnLimitedPostString, false, 0 },
    #endif
    { L"M",  NSwitchType::kUnLimitedPostString, true, 1 },
    { L"O",  NSwitchType::kUnLimitedPostString, false, 1 },
    { L"W",  NSwitchType::kUnLimitedPostString, false, 0 },
    { L"I",  NSwitchType::kUnLimitedPostString, true, kSomeCludePostStringMinSize},
    { L"X",  NSwitchType::kUnLimitedPostString, true, kSomeCludePostStringMinSize},
    { L"AI", NSwitchType::kUnLimitedPostString, true, kSomeCludePostStringMinSize},
    { L"AX", NSwitchType::kUnLimitedPostString, true, kSomeCludePostStringMinSize},
    { L"AN", NSwitchType::kSimple, false },
    { L"U",  NSwitchType::kUnLimitedPostString, true, 1},
    { L"V",  NSwitchType::kUnLimitedPostString, true, 1},
    { L"R",  NSwitchType::kPostChar, false, 0, 0, kRecursedPostCharSet },
    { L"SFX", NSwitchType::kUnLimitedPostString, false, 0 },
    { L"SI", NSwitchType::kUnLimitedPostString, false, 0 },
    { L"SO", NSwitchType::kSimple, false, 0 },
    { L"AO", NSwitchType::kPostChar, false, 1, 1, kOverwritePostCharSet},
    { L"SEML", NSwitchType::kUnLimitedPostString, false, 0},
    { L"AD",  NSwitchType::kSimple, false },
    { L"SLP", NSwitchType::kUnLimitedPostString, false, 0},
    { L"SCS", NSwitchType::kUnLimitedPostString, false, 0},
    { L"SCC", NSwitchType::kUnLimitedPostString, false, 0},
    { L"SLT", NSwitchType::kSimple, false },
    { L"SSW", NSwitchType::kSimple, false },
    { L"SSC", NSwitchType::kPostChar, false, 0, 0, L"-" },
    { L"SCRC", NSwitchType::kSimple, false }
  };

static const CCommandForm g_CommandForms[] =
{
  { L"A", false },
  { L"U", false },
  { L"D", false },
  { L"T", false },
  { L"E", false },
  { L"X", false },
  { L"L", false },
  { L"B", false },
  { L"I", false }
};

static const int kNumCommandForms = sizeof(g_CommandForms) /  sizeof(g_CommandForms[0]);

static const wchar_t *kUniversalWildcard = L"*";
static const int kMinNonSwitchWords = 1;
static const int kCommandIndex = 0;

// ---------------------------
// exception messages

static const char *kUserErrorMessage  = "Incorrect command line";
static const char *kCannotFindListFile = "Cannot find listfile";
static const char *kIncorrectListFile = "Incorrect item in listfile.\nCheck charset encoding and -scs switch.";
static const char *kIncorrectWildCardInListFile = "Incorrect wildcard in listfile";
static const char *kIncorrectWildCardInCommandLine  = "Incorrect wildcard in command line";
static const char *kTerminalOutError = "I won't write compressed data to a terminal";
static const char *kSameTerminalError = "I won't write data and program's messages to same terminal";
static const char *kEmptyFilePath = "Empty file path";

static void ThrowException(const char *errorMessage)
{
  throw CArchiveCommandLineException(errorMessage);
}

static void ThrowUserErrorException()
{
  ThrowException(kUserErrorMessage);
}

// ---------------------------

bool CArchiveCommand::IsFromExtractGroup() const
{
  switch(CommandType)
  {
    case NCommandType::kTest:
    case NCommandType::kExtract:
    case NCommandType::kFullExtract:
      return true;
    default:
      return false;
  }
}

NExtract::NPathMode::EEnum CArchiveCommand::GetPathMode() const
{
  switch(CommandType)
  {
    case NCommandType::kTest:
    case NCommandType::kFullExtract:
      return NExtract::NPathMode::kFullPathnames;
    default:
      return NExtract::NPathMode::kNoPathnames;
  }
}

bool CArchiveCommand::IsFromUpdateGroup() const
{
  return (CommandType == NCommandType::kAdd ||
    CommandType == NCommandType::kUpdate ||
    CommandType == NCommandType::kDelete);
=======
static const char *kOverwritePostCharSet = "asut";

static const NExtract::NOverwriteMode::EEnum k_OverwriteModes[] =
{
  NExtract::NOverwriteMode::kOverwrite,
  NExtract::NOverwriteMode::kSkip,
  NExtract::NOverwriteMode::kRename,
  NExtract::NOverwriteMode::kRenameExisting
};

static const CSwitchForm kSwitchForms[] =
{
  { "?" },
  { "h" },
  { "-help" },
  
  { "ba" },
  { "bd" },
  { "bt" },
  { "bb", NSwitchType::kString, false, 0 },

  { "bso", NSwitchType::kChar, false, 1, k_Stream_PostCharSet },
  { "bse", NSwitchType::kChar, false, 1, k_Stream_PostCharSet },
  { "bsp", NSwitchType::kChar, false, 1, k_Stream_PostCharSet },
  
  { "y" },
  
  { "ad" },
  { "ao", NSwitchType::kChar, false, 1, kOverwritePostCharSet},

  { "t",  NSwitchType::kString, false, 1 },
  { "stx", NSwitchType::kString, true, 1 },
  
  { "m",  NSwitchType::kString, true, 1 },
  { "o",  NSwitchType::kString, false, 1 },
  { "w",  NSwitchType::kString },

  { "i",  NSwitchType::kString, true, kSomeCludePostStringMinSize},
  { "x",  NSwitchType::kString, true, kSomeCludePostStringMinSize},
  { "ai", NSwitchType::kString, true, kSomeCludePostStringMinSize},
  { "ax", NSwitchType::kString, true, kSomeCludePostStringMinSize},
  { "an" },
  
  { "u",  NSwitchType::kString, true, 1},
  { "v",  NSwitchType::kString, true, 1},
  { "r",  NSwitchType::kChar, false, 0, kRecursedPostCharSet },
  
  { "stm", NSwitchType::kString },
  { "sfx", NSwitchType::kString },
  { "seml", NSwitchType::kString, false, 0},
  { "scrc", NSwitchType::kString, true, 0 },
  
  { "si", NSwitchType::kString },
  { "so" },

  { "slp", NSwitchType::kMinus },
  { "scs", NSwitchType::kString },
  { "scc", NSwitchType::kString },
  { "slt" },

  { "ssw" },
  { "ssc", NSwitchType::kMinus },
  { "sa",  NSwitchType::kChar, false, 1, k_ArcNameMode_PostCharSet },
  
  { "spd" },
  { "spe", NSwitchType::kMinus },
  { "spf", NSwitchType::kString, false, 0 },
  
  { "snh", NSwitchType::kMinus },
  { "snl", NSwitchType::kMinus },
  { "sni" },
  { "sns", NSwitchType::kMinus },
  { "snr" },
  { "snc" },
  
  { "sdel" },
  { "stl" }

  #ifndef _NO_CRYPTO
  , { "p",  NSwitchType::kString }
  #endif
};

static const wchar_t *kUniversalWildcard = L"*";
static const unsigned kMinNonSwitchWords = 1;
static const unsigned kCommandIndex = 0;

// static const char *kUserErrorMessage  = "Incorrect command line";
static const char *kCannotFindListFile = "Cannot find listfile";
static const char *kIncorrectListFile = "Incorrect item in listfile.\nCheck charset encoding and -scs switch.";
static const char *kTerminalOutError = "I won't write compressed data to a terminal";
static const char *kSameTerminalError = "I won't write data and program's messages to same stream";
static const char *kEmptyFilePath = "Empty file path";
static const char *kCannotFindArchive = "Cannot find archive";

bool CArcCommand::IsFromExtractGroup() const
{
  switch (CommandType)
  {
    case NCommandType::kTest:
    case NCommandType::kExtract:
    case NCommandType::kExtractFull:
      return true;
  }
  return false;
}

NExtract::NPathMode::EEnum CArcCommand::GetPathMode() const
{
  switch (CommandType)
  {
    case NCommandType::kTest:
    case NCommandType::kExtractFull:
      return NExtract::NPathMode::kFullPaths;
  }
  return NExtract::NPathMode::kNoPaths;
}

bool CArcCommand::IsFromUpdateGroup() const
{
  switch (CommandType)
  {
    case NCommandType::kAdd:
    case NCommandType::kUpdate:
    case NCommandType::kDelete:
    case NCommandType::kRename:
      return true;
  }
  return false;
>>>>>>> upstream/master
}

static NRecursedType::EEnum GetRecursedTypeFromIndex(int index)
{
  switch (index)
  {
<<<<<<< HEAD
    case NRecursedPostCharIndex::kWildCardRecursionOnly:
      return NRecursedType::kWildCardOnlyRecursed;
=======
    case NRecursedPostCharIndex::kWildcardRecursionOnly:
      return NRecursedType::kWildcardOnlyRecursed;
>>>>>>> upstream/master
    case NRecursedPostCharIndex::kNoRecursion:
      return NRecursedType::kNonRecursed;
    default:
      return NRecursedType::kRecursed;
  }
}

<<<<<<< HEAD
static bool ParseArchiveCommand(const UString &commandString, CArchiveCommand &command)
{
  UString commandStringUpper = commandString;
  commandStringUpper.MakeUpper();
  UString postString;
  int commandIndex = ParseCommand(kNumCommandForms, g_CommandForms, commandStringUpper,
      postString) ;
  if (commandIndex < 0)
    return false;
  command.CommandType = (NCommandType::EEnum)commandIndex;
  return true;
=======
static const char *g_Commands = "audtexlbih";

static bool ParseArchiveCommand(const UString &commandString, CArcCommand &command)
{
  UString s = commandString;
  s.MakeLower_Ascii();
  if (s.Len() == 1)
  {
    if (s[0] > 0x7F)
      return false;
    int index = FindCharPosInString(g_Commands, (char)s[0]);
    if (index < 0)
      return false;
    command.CommandType = (NCommandType::EEnum)index;
    return true;
  }
  if (s.Len() == 2 && s[0] == 'r' && s[1] == 'n')
  {
    command.CommandType = (NCommandType::kRename);
    return true;
  }
  return false;
>>>>>>> upstream/master
}

// ------------------------------------------------------------------
// filenames functions

<<<<<<< HEAD
static void AddNameToCensor(NWildcard::CCensor &wildcardCensor,
    const UString &name, bool include, NRecursedType::EEnum type)
=======
static void AddNameToCensor(NWildcard::CCensor &censor,
    const UString &name, bool include, NRecursedType::EEnum type, bool wildcardMatching)
>>>>>>> upstream/master
{
  bool recursed = false;

  switch (type)
  {
<<<<<<< HEAD
    case NRecursedType::kWildCardOnlyRecursed:
      recursed = DoesNameContainWildCard(name);
=======
    case NRecursedType::kWildcardOnlyRecursed:
      recursed = DoesNameContainWildcard(name);
>>>>>>> upstream/master
      break;
    case NRecursedType::kRecursed:
      recursed = true;
      break;
  }
<<<<<<< HEAD
  wildcardCensor.AddItem(include, name, recursed);
}

static void AddToCensorFromListFile(NWildcard::CCensor &wildcardCensor,
    LPCWSTR fileName, bool include, NRecursedType::EEnum type, UINT codePage)
{
  UStringVector names;
  if (!NFind::DoesFileExist(us2fs(fileName)))
    throw kCannotFindListFile;
  if (!ReadNamesFromListFile(us2fs(fileName), names, codePage))
    throw kIncorrectListFile;
  for (int i = 0; i < names.Size(); i++)
    AddNameToCensor(wildcardCensor, names[i], include, type);
}

static void AddToCensorFromNonSwitchesStrings(
    int startIndex,
    NWildcard::CCensor &wildcardCensor,
    const UStringVector &nonSwitchStrings, NRecursedType::EEnum type,
    bool thereAreSwitchIncludes, UINT codePage)
{
  if (nonSwitchStrings.Size() == startIndex && (!thereAreSwitchIncludes))
    AddNameToCensor(wildcardCensor, kUniversalWildcard, true, type);
  for (int i = startIndex; i < nonSwitchStrings.Size(); i++)
  {
    const UString &s = nonSwitchStrings[i];
    if (s.IsEmpty())
      throw kEmptyFilePath;
    if (s[0] == kFileListID)
      AddToCensorFromListFile(wildcardCensor, s.Mid(1), true, type, codePage);
    else
      AddNameToCensor(wildcardCensor, s, true, type);
  }
}

#ifdef _WIN32
static void ParseMapWithPaths(NWildcard::CCensor &wildcardCensor,
    const UString &switchParam, bool include,
    NRecursedType::EEnum commonRecursedType)
{
  int splitPos = switchParam.Find(L':');
  if (splitPos < 0)
    ThrowUserErrorException();
  UString mappingName = switchParam.Left(splitPos);
  
  UString switchParam2 = switchParam.Mid(splitPos + 1);
  splitPos = switchParam2.Find(L':');
  if (splitPos < 0)
    ThrowUserErrorException();
  
  UString mappingSize = switchParam2.Left(splitPos);
  UString eventName = switchParam2.Mid(splitPos + 1);
  
  UInt64 dataSize64 = ConvertStringToUInt64(mappingSize, NULL);
  UInt32 dataSize = (UInt32)dataSize64;
  {
    CFileMapping fileMapping;
    if (fileMapping.Open(FILE_MAP_READ, GetSystemString(mappingName)) != 0)
      ThrowException("Can not open mapping");
    LPVOID data = fileMapping.Map(FILE_MAP_READ, 0, dataSize);
    if (data == NULL)
      ThrowException("MapViewOfFile error");
    try
    {
      const wchar_t *curData = (const wchar_t *)data;
      if (*curData != 0)
        ThrowException("Incorrect mapping data");
      UInt32 numChars = dataSize / sizeof(wchar_t);
      UString name;
      for (UInt32 i = 1; i < numChars; i++)
      {
        wchar_t c = curData[i];
        if (c == L'\0')
        {
          AddNameToCensor(wildcardCensor, name, include, commonRecursedType);
          name.Empty();
        }
        else
          name += c;
      }
      if (!name.IsEmpty())
        ThrowException("data error");
    }
    catch(...)
    {
      UnmapViewOfFile(data);
      throw;
    }
    UnmapViewOfFile(data);
  }
  
  {
    NSynchronization::CManualResetEvent event;
    if (event.Open(EVENT_MODIFY_STATE, false, GetSystemString(eventName)) == S_OK)
      event.Set();
  }
}
#endif

static void AddSwitchWildCardsToCensor(NWildcard::CCensor &wildcardCensor,
    const UStringVector &strings, bool include,
    NRecursedType::EEnum commonRecursedType, UINT codePage)
{
  for (int i = 0; i < strings.Size(); i++)
  {
    const UString &name = strings[i];
    NRecursedType::EEnum recursedType;
    int pos = 0;
    if (name.Length() < kSomeCludePostStringMinSize)
      ThrowUserErrorException();
    if (::MyCharUpper(name[pos]) == kRecursedIDChar)
    {
      pos++;
      int index = UString(kRecursedPostCharSet).Find(name[pos]);
=======
  censor.AddPreItem(include, name, recursed, wildcardMatching);
}

static void AddRenamePair(CObjectVector<CRenamePair> *renamePairs,
    const UString &oldName, const UString &newName, NRecursedType::EEnum type,
    bool wildcardMatching)
{
  CRenamePair &pair = renamePairs->AddNew();
  pair.OldName = oldName;
  pair.NewName = newName;
  pair.RecursedType = type;
  pair.WildcardParsing = wildcardMatching;

  if (!pair.Prepare())
  {
    UString val;
    val += pair.OldName;
    val.Add_LF();
    val += pair.NewName;
    val.Add_LF();
    if (type == NRecursedType::kRecursed)
      val.AddAscii("-r");
    else if (type == NRecursedType::kWildcardOnlyRecursed)
      val.AddAscii("-r0");
    throw CArcCmdLineException("Unsupported rename command:", val);
  }
}

static void AddToCensorFromListFile(
    CObjectVector<CRenamePair> *renamePairs,
    NWildcard::CCensor &censor,
    LPCWSTR fileName, bool include, NRecursedType::EEnum type, bool wildcardMatching, Int32 codePage)
{
  UStringVector names;
  if (!NFind::DoesFileExist(us2fs(fileName)))
    throw CArcCmdLineException(kCannotFindListFile, fileName);
  if (!ReadNamesFromListFile(us2fs(fileName), names, codePage))
    throw CArcCmdLineException(kIncorrectListFile, fileName);
  if (renamePairs)
  {
    if ((names.Size() & 1) != 0)
      throw CArcCmdLineException(kIncorrectListFile, fileName);
    for (unsigned i = 0; i < names.Size(); i += 2)
    {
      // change type !!!!
      AddRenamePair(renamePairs, names[i], names[i + 1], type, wildcardMatching);
    }
  }
  else
    FOR_VECTOR (i, names)
      AddNameToCensor(censor, names[i], include, type, wildcardMatching);
}

static void AddToCensorFromNonSwitchesStrings(
    CObjectVector<CRenamePair> *renamePairs,
    unsigned startIndex,
    NWildcard::CCensor &censor,
    const UStringVector &nonSwitchStrings, NRecursedType::EEnum type,
    bool wildcardMatching,
    bool thereAreSwitchIncludes, Int32 codePage)
{
  if ((renamePairs || nonSwitchStrings.Size() == startIndex) && !thereAreSwitchIncludes)
    AddNameToCensor(censor, kUniversalWildcard, true, type,
        true // wildcardMatching
        );

  int oldIndex = -1;
  
  for (unsigned i = startIndex; i < nonSwitchStrings.Size(); i++)
  {
    const UString &s = nonSwitchStrings[i];
    if (s.IsEmpty())
      throw CArcCmdLineException(kEmptyFilePath);
    if (s[0] == kFileListID)
      AddToCensorFromListFile(renamePairs, censor, s.Ptr(1), true, type, wildcardMatching, codePage);
    else if (renamePairs)
    {
      if (oldIndex == -1)
        oldIndex = i;
      else
      {
        // NRecursedType::EEnum type is used for global wildcard (-i! switches)
        AddRenamePair(renamePairs, nonSwitchStrings[oldIndex], s, NRecursedType::kNonRecursed, wildcardMatching);
        // AddRenamePair(renamePairs, nonSwitchStrings[oldIndex], s, type);
        oldIndex = -1;
      }
    }
    else
      AddNameToCensor(censor, s, true, type, wildcardMatching);
  }
  
  if (oldIndex != -1)
  {
    throw CArcCmdLineException("There is no second file name for rename pair:", nonSwitchStrings[oldIndex]);
  }
}

#ifdef _WIN32

struct CEventSetEnd
{
  UString Name;
  
  CEventSetEnd(const wchar_t *name): Name(name) {}
  ~CEventSetEnd()
  {
    NSynchronization::CManualResetEvent event;
    if (event.Open(EVENT_MODIFY_STATE, false, GetSystemString(Name)) == 0)
      event.Set();
  }
};

const char *k_IncorrectMapCommand = "Incorrect Map command";

static const char *ParseMapWithPaths(
    NWildcard::CCensor &censor,
    const UString &s2, bool include,
    NRecursedType::EEnum commonRecursedType,
    bool wildcardMatching)
{
  UString s = s2;
  int pos = s.Find(L':');
  if (pos < 0)
    return k_IncorrectMapCommand;
  int pos2 = s.Find(L':', pos + 1);
  if (pos2 < 0)
    return k_IncorrectMapCommand;

  CEventSetEnd eventSetEnd((const wchar_t *)s + ((unsigned)pos2 + 1));
  s.DeleteFrom(pos2);
  UInt32 size;
  if (!StringToUInt32(s.Ptr(pos + 1), size)
      || size < sizeof(wchar_t)
      || size > ((UInt32)1 << 31)
      || size % sizeof(wchar_t) != 0)
    return "Unsupported Map data size";

  s.DeleteFrom(pos);
  CFileMapping map;
  if (map.Open(FILE_MAP_READ, GetSystemString(s)) != 0)
    return "Can not open mapping";
  LPVOID data = map.Map(FILE_MAP_READ, 0, size);
  if (!data)
    return "MapViewOfFile error";
  CFileUnmapper unmapper(data);

  UString name;
  const wchar_t *p = (const wchar_t *)data;
  if (*p != 0) // data format marker
    return "Unsupported Map data";
  UInt32 numChars = size / sizeof(wchar_t);
  for (UInt32 i = 1; i < numChars; i++)
  {
    wchar_t c = p[i];
    if (c == 0)
    {
      // MessageBoxW(0, name, L"7-Zip", 0);
      AddNameToCensor(censor, name, include, commonRecursedType, wildcardMatching);
      name.Empty();
    }
    else
      name += c;
  }
  if (!name.IsEmpty())
    return "Map data error";

  return NULL;
}

#endif

static void AddSwitchWildcardsToCensor(
    NWildcard::CCensor &censor,
    const UStringVector &strings, bool include,
    NRecursedType::EEnum commonRecursedType,
    bool wildcardMatching,
    Int32 codePage)
{
  const char *errorMessage = NULL;
  unsigned i;
  for (i = 0; i < strings.Size(); i++)
  {
    const UString &name = strings[i];
    NRecursedType::EEnum recursedType;
    unsigned pos = 0;
    
    if (name.Len() < kSomeCludePostStringMinSize)
    {
      errorMessage = "Too short switch";
      break;
    }
    
    if (::MyCharLower_Ascii(name[pos]) == kRecursedIDChar)
    {
      pos++;
      wchar_t c = name[pos];
      int index = -1;
      if (c <= 0x7F)
        index = FindCharPosInString(kRecursedPostCharSet, (char)c);
>>>>>>> upstream/master
      recursedType = GetRecursedTypeFromIndex(index);
      if (index >= 0)
        pos++;
    }
    else
      recursedType = commonRecursedType;
<<<<<<< HEAD
    if (name.Length() < pos + kSomeCludeAfterRecursedPostStringMinSize)
      ThrowUserErrorException();
    UString tail = name.Mid(pos + 1);
    if (name[pos] == kImmediateNameID)
      AddNameToCensor(wildcardCensor, tail, include, recursedType);
    else if (name[pos] == kFileListID)
      AddToCensorFromListFile(wildcardCensor, tail, include, recursedType, codePage);
    #ifdef _WIN32
    else if (name[pos] == kMapNameID)
      ParseMapWithPaths(wildcardCensor, tail, include, recursedType);
    #endif
    else
      ThrowUserErrorException();
  }
=======
    
    if (name.Len() < pos + kSomeCludeAfterRecursedPostStringMinSize)
    {
      errorMessage = "Too short switch";
      break;
    }
    
    UString tail = name.Ptr(pos + 1);
    
    if (name[pos] == kImmediateNameID)
      AddNameToCensor(censor, tail, include, recursedType, wildcardMatching);
    else if (name[pos] == kFileListID)
      AddToCensorFromListFile(NULL, censor, tail, include, recursedType, wildcardMatching, codePage);
    #ifdef _WIN32
    else if (name[pos] == kMapNameID)
    {
      errorMessage = ParseMapWithPaths(censor, tail, include, recursedType, wildcardMatching);
      if (errorMessage)
        break;
    }
    #endif
    else
    {
      errorMessage = "Incorrect wildcard type marker";
      break;
    }
  }
  if (i != strings.Size())
    throw CArcCmdLineException(errorMessage, strings[i]);
>>>>>>> upstream/master
}

#ifdef _WIN32

// This code converts all short file names to long file names.

static void ConvertToLongName(const UString &prefix, UString &name)
{
<<<<<<< HEAD
  if (name.IsEmpty() || DoesNameContainWildCard(name))
    return;
  NFind::CFileInfo fi;
  if (fi.Find(us2fs(prefix + name)))
=======
  if (name.IsEmpty() || DoesNameContainWildcard(name))
    return;
  NFind::CFileInfo fi;
  const FString path = us2fs(prefix + name);
  #ifndef UNDER_CE
  if (NFile::NName::IsDevicePath(path))
    return;
  #endif
  if (fi.Find(path))
>>>>>>> upstream/master
    name = fs2us(fi.Name);
}

static void ConvertToLongNames(const UString &prefix, CObjectVector<NWildcard::CItem> &items)
{
<<<<<<< HEAD
  for (int i = 0; i < items.Size(); i++)
=======
  FOR_VECTOR (i, items)
>>>>>>> upstream/master
  {
    NWildcard::CItem &item = items[i];
    if (item.Recursive || item.PathParts.Size() != 1)
      continue;
<<<<<<< HEAD
=======
    if (prefix.IsEmpty() && item.IsDriveItem())
      continue;
>>>>>>> upstream/master
    ConvertToLongName(prefix, item.PathParts.Front());
  }
}

static void ConvertToLongNames(const UString &prefix, NWildcard::CCensorNode &node)
{
  ConvertToLongNames(prefix, node.IncludeItems);
  ConvertToLongNames(prefix, node.ExcludeItems);
<<<<<<< HEAD
  int i;
  for (i = 0; i < node.SubNodes.Size(); i++)
    ConvertToLongName(prefix, node.SubNodes[i].Name);
=======
  unsigned i;
  for (i = 0; i < node.SubNodes.Size(); i++)
  {
    UString &name = node.SubNodes[i].Name;
    if (prefix.IsEmpty() && NWildcard::IsDriveColonName(name))
      continue;
    ConvertToLongName(prefix, name);
  }
>>>>>>> upstream/master
  // mix folders with same name
  for (i = 0; i < node.SubNodes.Size(); i++)
  {
    NWildcard::CCensorNode &nextNode1 = node.SubNodes[i];
<<<<<<< HEAD
    for (int j = i + 1; j < node.SubNodes.Size();)
    {
      const NWildcard::CCensorNode &nextNode2 = node.SubNodes[j];
      if (nextNode1.Name.CompareNoCase(nextNode2.Name) == 0)
=======
    for (unsigned j = i + 1; j < node.SubNodes.Size();)
    {
      const NWildcard::CCensorNode &nextNode2 = node.SubNodes[j];
      if (nextNode1.Name.IsEqualTo_NoCase(nextNode2.Name))
>>>>>>> upstream/master
      {
        nextNode1.IncludeItems += nextNode2.IncludeItems;
        nextNode1.ExcludeItems += nextNode2.ExcludeItems;
        node.SubNodes.Delete(j);
      }
      else
        j++;
    }
  }
  for (i = 0; i < node.SubNodes.Size(); i++)
  {
    NWildcard::CCensorNode &nextNode = node.SubNodes[i];
    ConvertToLongNames(prefix + nextNode.Name + WCHAR_PATH_SEPARATOR, nextNode);
  }
}

<<<<<<< HEAD
static void ConvertToLongNames(NWildcard::CCensor &censor)
{
  for (int i = 0; i < censor.Pairs.Size(); i++)
=======
void ConvertToLongNames(NWildcard::CCensor &censor)
{
  FOR_VECTOR (i, censor.Pairs)
>>>>>>> upstream/master
  {
    NWildcard::CPair &pair = censor.Pairs[i];
    ConvertToLongNames(pair.Prefix, pair.Head);
  }
}

#endif

<<<<<<< HEAD
static NUpdateArchive::NPairAction::EEnum GetUpdatePairActionType(int i)
{
  switch(i)
=======
/*
static NUpdateArchive::NPairAction::EEnum GetUpdatePairActionType(int i)
{
  switch (i)
>>>>>>> upstream/master
  {
    case NUpdateArchive::NPairAction::kIgnore: return NUpdateArchive::NPairAction::kIgnore;
    case NUpdateArchive::NPairAction::kCopy: return NUpdateArchive::NPairAction::kCopy;
    case NUpdateArchive::NPairAction::kCompress: return NUpdateArchive::NPairAction::kCompress;
    case NUpdateArchive::NPairAction::kCompressAsAnti: return NUpdateArchive::NPairAction::kCompressAsAnti;
  }
  throw 98111603;
}
<<<<<<< HEAD

const UString kUpdatePairStateIDSet = L"PQRXYZW";
const int kUpdatePairStateNotSupportedActions[] = {2, 2, 1, -1, -1, -1, -1};

const UString kUpdatePairActionIDSet = L"0123"; //Ignore, Copy, Compress, Create Anti

const wchar_t *kUpdateIgnoreItselfPostStringID = L"-";
const wchar_t kUpdateNewArchivePostCharID = '!';
=======
*/

static const wchar_t *kUpdatePairStateIDSet = L"pqrxyzw";
static const int kUpdatePairStateNotSupportedActions[] = {2, 2, 1, -1, -1, -1, -1};

static const unsigned kNumUpdatePairActions = 4;
static const char *kUpdateIgnoreItselfPostStringID = "-";
static const wchar_t kUpdateNewArchivePostCharID = '!';
>>>>>>> upstream/master


static bool ParseUpdateCommandString2(const UString &command,
    NUpdateArchive::CActionSet &actionSet, UString &postString)
{
<<<<<<< HEAD
  for (int i = 0; i < command.Length();)
  {
    wchar_t c = MyCharUpper(command[i]);
    int statePos = kUpdatePairStateIDSet.Find(c);
    if (statePos < 0)
    {
      postString = command.Mid(i);
      return true;
    }
    i++;
    if (i >= command.Length())
      return false;
    int actionPos = kUpdatePairActionIDSet.Find(::MyCharUpper(command[i]));
    if (actionPos < 0)
      return false;
    actionSet.StateActions[statePos] = GetUpdatePairActionType(actionPos);
    if (kUpdatePairStateNotSupportedActions[statePos] == actionPos)
=======
  for (unsigned i = 0; i < command.Len();)
  {
    wchar_t c = MyCharLower_Ascii(command[i]);
    int statePos = FindCharPosInString(kUpdatePairStateIDSet, c);
    if (statePos < 0)
    {
      postString = command.Ptr(i);
      return true;
    }
    i++;
    if (i >= command.Len())
      return false;
    c = command[i];
    if (c < '0' || c >= '0' + kNumUpdatePairActions)
      return false;
    unsigned actionPos = c - '0';
    actionSet.StateActions[(unsigned)statePos] = (NUpdateArchive::NPairAction::EEnum)(actionPos);
    if (kUpdatePairStateNotSupportedActions[(unsigned)statePos] == (int)actionPos)
>>>>>>> upstream/master
      return false;
    i++;
  }
  postString.Empty();
  return true;
}

static void ParseUpdateCommandString(CUpdateOptions &options,
    const UStringVector &updatePostStrings,
    const NUpdateArchive::CActionSet &defaultActionSet)
{
<<<<<<< HEAD
  for (int i = 0; i < updatePostStrings.Size(); i++)
  {
    const UString &updateString = updatePostStrings[i];
    if (updateString.CompareNoCase(kUpdateIgnoreItselfPostStringID) == 0)
=======
  const char *errorMessage = "incorrect update switch command";
  unsigned i;
  for (i = 0; i < updatePostStrings.Size(); i++)
  {
    const UString &updateString = updatePostStrings[i];
    if (updateString.IsEqualTo(kUpdateIgnoreItselfPostStringID))
>>>>>>> upstream/master
    {
      if (options.UpdateArchiveItself)
      {
        options.UpdateArchiveItself = false;
        options.Commands.Delete(0);
      }
    }
    else
    {
      NUpdateArchive::CActionSet actionSet = defaultActionSet;

      UString postString;
      if (!ParseUpdateCommandString2(updateString, actionSet, postString))
<<<<<<< HEAD
        ThrowUserErrorException();
=======
        break;
>>>>>>> upstream/master
      if (postString.IsEmpty())
      {
        if (options.UpdateArchiveItself)
          options.Commands[0].ActionSet = actionSet;
      }
      else
      {
<<<<<<< HEAD
        if (MyCharUpper(postString[0]) != kUpdateNewArchivePostCharID)
          ThrowUserErrorException();
        CUpdateArchiveCommand uc;
        UString archivePath = postString.Mid(1);
        if (archivePath.IsEmpty())
          ThrowUserErrorException();
=======
        if (postString[0] != kUpdateNewArchivePostCharID)
          break;
        CUpdateArchiveCommand uc;
        UString archivePath = postString.Ptr(1);
        if (archivePath.IsEmpty())
          break;
>>>>>>> upstream/master
        uc.UserArchivePath = archivePath;
        uc.ActionSet = actionSet;
        options.Commands.Add(uc);
      }
    }
  }
<<<<<<< HEAD
}

static const char kByteSymbol = 'B';
static const char kKiloSymbol = 'K';
static const char kMegaSymbol = 'M';
static const char kGigaSymbol = 'G';

static bool ParseComplexSize(const UString &src, UInt64 &result)
{
  UString s = src;
  s.MakeUpper();

  const wchar_t *start = s;
  const wchar_t *end;
  UInt64 number = ConvertStringToUInt64(start, &end);
  int numDigits = (int)(end - start);
  if (numDigits == 0 || s.Length() > numDigits + 1)
    return false;
  if (s.Length() == numDigits)
  {
    result = number;
    return true;
  }
  int numBits;
  switch (s[numDigits])
  {
    case kByteSymbol:
      result = number;
      return true;
    case kKiloSymbol:
      numBits = 10;
      break;
    case kMegaSymbol:
      numBits = 20;
      break;
    case kGigaSymbol:
      numBits = 30;
      break;
    default:
      return false;
  }
  if (number >= ((UInt64)1 << (64 - numBits)))
    return false;
  result = number << numBits;
  return true;
}
=======
  if (i != updatePostStrings.Size())
    throw CArcCmdLineException(errorMessage, updatePostStrings[i]);
}

bool ParseComplexSize(const wchar_t *s, UInt64 &result);
>>>>>>> upstream/master

static void SetAddCommandOptions(
    NCommandType::EEnum commandType,
    const CParser &parser,
    CUpdateOptions &options)
{
  NUpdateArchive::CActionSet defaultActionSet;
<<<<<<< HEAD
  switch(commandType)
  {
    case NCommandType::kAdd:
      defaultActionSet = NUpdateArchive::kAddActionSet;
      break;
    case NCommandType::kDelete:
      defaultActionSet = NUpdateArchive::kDeleteActionSet;
      break;
    default:
      defaultActionSet = NUpdateArchive::kUpdateActionSet;
=======
  switch (commandType)
  {
    case NCommandType::kAdd:
      defaultActionSet = NUpdateArchive::k_ActionSet_Add;
      break;
    case NCommandType::kDelete:
      defaultActionSet = NUpdateArchive::k_ActionSet_Delete;
      break;
    default:
      defaultActionSet = NUpdateArchive::k_ActionSet_Update;
>>>>>>> upstream/master
  }
  
  options.UpdateArchiveItself = true;
  
  options.Commands.Clear();
  CUpdateArchiveCommand updateMainCommand;
  updateMainCommand.ActionSet = defaultActionSet;
  options.Commands.Add(updateMainCommand);
  if (parser[NKey::kUpdate].ThereIs)
    ParseUpdateCommandString(options, parser[NKey::kUpdate].PostStrings,
        defaultActionSet);
  if (parser[NKey::kWorkingDir].ThereIs)
  {
    const UString &postString = parser[NKey::kWorkingDir].PostStrings[0];
    if (postString.IsEmpty())
<<<<<<< HEAD
      NDirectory::MyGetTempPath(options.WorkingDir);
=======
      NDir::MyGetTempPath(options.WorkingDir);
>>>>>>> upstream/master
    else
      options.WorkingDir = us2fs(postString);
  }
  options.SfxMode = parser[NKey::kSfx].ThereIs;
  if (options.SfxMode)
    options.SfxModule = us2fs(parser[NKey::kSfx].PostStrings[0]);

  if (parser[NKey::kVolume].ThereIs)
  {
    const UStringVector &sv = parser[NKey::kVolume].PostStrings;
<<<<<<< HEAD
    for (int i = 0; i < sv.Size(); i++)
    {
      UInt64 size;
      if (!ParseComplexSize(sv[i], size))
        ThrowException("Incorrect volume size");
=======
    FOR_VECTOR (i, sv)
    {
      UInt64 size;
      if (!ParseComplexSize(sv[i], size) || size == 0)
        throw CArcCmdLineException("Incorrect volume size:", sv[i]);
>>>>>>> upstream/master
      options.VolumesSizes.Add(size);
    }
  }
}

static void SetMethodOptions(const CParser &parser, CObjectVector<CProperty> &properties)
{
  if (parser[NKey::kProperty].ThereIs)
  {
<<<<<<< HEAD
    for (int i = 0; i < parser[NKey::kProperty].PostStrings.Size(); i++)
    {
      CProperty property;
      const UString &postString = parser[NKey::kProperty].PostStrings[i];
      int index = postString.Find(L'=');
      if (index < 0)
        property.Name = postString;
      else
      {
        property.Name = postString.Left(index);
        property.Value = postString.Mid(index + 1);
      }
      properties.Add(property);
=======
    FOR_VECTOR (i, parser[NKey::kProperty].PostStrings)
    {
      CProperty prop;
      prop.Name = parser[NKey::kProperty].PostStrings[i];
      int index = prop.Name.Find(L'=');
      if (index >= 0)
      {
        prop.Value = prop.Name.Ptr(index + 1);
        prop.Name.DeleteFrom(index);
      }
      properties.Add(prop);
>>>>>>> upstream/master
    }
  }
}

<<<<<<< HEAD
CArchiveCommandLineParser::CArchiveCommandLineParser():
  parser(sizeof(kSwitchForms) / sizeof(kSwitchForms[0])) {}

void CArchiveCommandLineParser::Parse1(const UStringVector &commandStrings,
    CArchiveCommandLineOptions &options)
{
  try
  {
    parser.ParseStrings(kSwitchForms, commandStrings);
  }
  catch(...)
  {
    ThrowUserErrorException();
  }
=======
CArcCmdLineParser::CArcCmdLineParser(): parser(ARRAY_SIZE(kSwitchForms)) {}

static inline void SetStreamMode(const CSwitchResult &sw, unsigned &res)
{
  if (sw.ThereIs)
    res = sw.PostCharIndex;
}

void CArcCmdLineParser::Parse1(const UStringVector &commandStrings,
    CArcCmdLineOptions &options)
{
  if (!parser.ParseStrings(kSwitchForms, commandStrings))
    throw CArcCmdLineException(parser.ErrorMessage, parser.ErrorLine);
>>>>>>> upstream/master

  options.IsInTerminal = MY_IS_TERMINAL(stdin);
  options.IsStdOutTerminal = MY_IS_TERMINAL(stdout);
  options.IsStdErrTerminal = MY_IS_TERMINAL(stderr);
<<<<<<< HEAD
  options.StdInMode = parser[NKey::kStdIn].ThereIs;
  options.StdOutMode = parser[NKey::kStdOut].ThereIs;
  options.EnableHeaders = !parser[NKey::kDisableHeaders].ThereIs;
  options.HelpMode = parser[NKey::kHelp1].ThereIs || parser[NKey::kHelp2].ThereIs  || parser[NKey::kHelp3].ThereIs;

  #ifdef _WIN32
  options.LargePages = false;
  if (parser[NKey::kLargePages].ThereIs)
  {
    const UString &postString = parser[NKey::kLargePages].PostStrings.Front();
    if (postString.IsEmpty())
      options.LargePages = true;
  }
=======

  options.HelpMode = parser[NKey::kHelp1].ThereIs || parser[NKey::kHelp2].ThereIs  || parser[NKey::kHelp3].ThereIs;

  options.StdInMode = parser[NKey::kStdIn].ThereIs;
  options.StdOutMode = parser[NKey::kStdOut].ThereIs;
  options.EnableHeaders = !parser[NKey::kDisableHeaders].ThereIs;
  options.TechMode = parser[NKey::kTechMode].ThereIs;
  options.ShowTime = parser[NKey::kShowTime].ThereIs;

  if (parser[NKey::kDisablePercents].ThereIs
      || options.StdOutMode
      || !options.IsStdOutTerminal)
    options.Number_for_Percents = k_OutStream_disabled;

  if (options.StdOutMode)
    options.Number_for_Out = k_OutStream_disabled;

  SetStreamMode(parser[NKey::kOutStream], options.Number_for_Out);
  SetStreamMode(parser[NKey::kErrStream], options.Number_for_Errors);
  SetStreamMode(parser[NKey::kPercentStream], options.Number_for_Percents);

  if (parser[NKey::kLogLevel].ThereIs)
  {
    const UString &s = parser[NKey::kLogLevel].PostStrings[0];
    if (s.IsEmpty())
      options.LogLevel = 1;
    else
    {
      UInt32 v;
      if (!StringToUInt32(s, v))
        throw CArcCmdLineException("Unsupported switch postfix -bb", s);
      options.LogLevel = (unsigned)v;
    }
  }

  if (parser[NKey::kCaseSensitive].ThereIs)
  {
    g_CaseSensitive = !parser[NKey::kCaseSensitive].WithMinus;
    options.CaseSensitiveChange = true;
    options.CaseSensitive = g_CaseSensitive;
  }

  options.LargePages = false;
  if (parser[NKey::kLargePages].ThereIs)
    options.LargePages = !parser[NKey::kLargePages].WithMinus;


  #ifndef UNDER_CE

  if (parser[NKey::kAffinity].ThereIs)
  {
    const UString &s = parser[NKey::kAffinity].PostStrings[0];
    if (!s.IsEmpty())
    {
      UInt32 v = 0;
      AString a;
      a.SetFromWStr_if_Ascii(s);
      if (!a.IsEmpty())
      {
        const char *end;
        v = ConvertHexStringToUInt32(a, &end);
        if (*end != 0)
          a.Empty();
      }
      if (a.IsEmpty())
        throw CArcCmdLineException("Unsupported switch postfix -stm", s);
      
      #ifdef _WIN32
      SetProcessAffinityMask(GetCurrentProcess(), v);
      #endif
    }
  }

>>>>>>> upstream/master
  #endif
}

struct CCodePagePair
{
<<<<<<< HEAD
  const wchar_t *Name;
  UINT CodePage;
};

static CCodePagePair g_CodePagePairs[] =
{
  { L"UTF-8", CP_UTF8 },
  { L"WIN", CP_ACP },
  { L"DOS", CP_OEMCP }
};

static int FindCharset(const NCommandLineParser::CParser &parser, int keyIndex, int defaultVal)
=======
  const char *Name;
  Int32 CodePage;
};

static const unsigned kNumByteOnlyCodePages = 3;

static const CCodePagePair g_CodePagePairs[] =
{
  { "utf-8", CP_UTF8 },
  { "win", CP_ACP },
  { "dos", CP_OEMCP },
  { "utf-16le", MY__CP_UTF16 },
  { "utf-16be", MY__CP_UTF16BE }
};

static Int32 FindCharset(const NCommandLineParser::CParser &parser, unsigned keyIndex,
    bool byteOnlyCodePages, Int32 defaultVal)
>>>>>>> upstream/master
{
  if (!parser[keyIndex].ThereIs)
    return defaultVal;

  UString name = parser[keyIndex].PostStrings.Back();
<<<<<<< HEAD
  name.MakeUpper();
  int i;
  for (i = 0; i < sizeof(g_CodePagePairs) / sizeof(g_CodePagePairs[0]); i++)
  {
    const CCodePagePair &pair = g_CodePagePairs[i];
    if (name.Compare(pair.Name) == 0)
      return pair.CodePage;
  }
  if (i == sizeof(g_CodePagePairs) / sizeof(g_CodePagePairs[0]))
    ThrowUserErrorException();
  return -1;
}

static bool ConvertStringToUInt32(const wchar_t *s, UInt32 &v)
{
  const wchar_t *end;
  UInt64 number = ConvertStringToUInt64(s, &end);
  if (*end != 0)
    return false;
  if (number > (UInt32)0xFFFFFFFF)
    return false;
  v = (UInt32)number;
  return true;
}

void EnumerateDirItemsAndSort(NWildcard::CCensor &wildcardCensor,
    UStringVector &sortedPaths,
    UStringVector &sortedFullPaths)
{
  UStringVector paths;
  {
    CDirItems dirItems;
    {
      FStringVector errorPaths;
      CRecordVector<DWORD> errorCodes;
      HRESULT res = EnumerateItems(wildcardCensor, dirItems, NULL, errorPaths, errorCodes);
      if (res != S_OK || errorPaths.Size() > 0)
        throw "cannot find archive";
    }
    for (int i = 0; i < dirItems.Items.Size(); i++)
=======
  UInt32 v;
  if (StringToUInt32(name, v))
    if (v < ((UInt32)1 << 16))
      return (Int32)v;
  name.MakeLower_Ascii();
  unsigned num = byteOnlyCodePages ? kNumByteOnlyCodePages : ARRAY_SIZE(g_CodePagePairs);
  for (unsigned i = 0;; i++)
  {
    if (i == num) // to disable warnings from different compilers
      throw CArcCmdLineException("Unsupported charset:", name);
    const CCodePagePair &pair = g_CodePagePairs[i];
    if (name.IsEqualTo(pair.Name))
      return pair.CodePage;
  }
}

HRESULT EnumerateDirItemsAndSort(
    NWildcard::CCensor &censor,
    NWildcard::ECensorPathMode censorPathMode,
    const UString &addPathPrefix,
    UStringVector &sortedPaths,
    UStringVector &sortedFullPaths,
    CDirItemsStat &st,
    IDirItemsCallback *callback)
{
  FStringVector paths;
  
  {
    CDirItems dirItems;
    dirItems.Callback = callback;
    {
      HRESULT res = EnumerateItems(censor, censorPathMode, addPathPrefix, dirItems);
      st = dirItems.Stat;
      RINOK(res);
    }
  
    FOR_VECTOR (i, dirItems.Items)
>>>>>>> upstream/master
    {
      const CDirItem &dirItem = dirItems.Items[i];
      if (!dirItem.IsDir())
        paths.Add(dirItems.GetPhyPath(i));
    }
  }
  
  if (paths.Size() == 0)
<<<<<<< HEAD
    throw "there is no such archive";
  
  UStringVector fullPaths;
  
  int i;
  for (i = 0; i < paths.Size(); i++)
  {
    FString fullPath;
    NFile::NDirectory::MyGetFullPathName(us2fs(paths[i]), fullPath);
    fullPaths.Add(fs2us(fullPath));
  }
  CIntVector indices;
  SortFileNames(fullPaths, indices);
  sortedPaths.Reserve(indices.Size());
  sortedFullPaths.Reserve(indices.Size());
  for (i = 0; i < indices.Size(); i++)
  {
    int index = indices[i];
    sortedPaths.Add(paths[index]);
    sortedFullPaths.Add(fullPaths[index]);
  }
}

void CArchiveCommandLineParser::Parse2(CArchiveCommandLineOptions &options)
{
  const UStringVector &nonSwitchStrings = parser.NonSwitchStrings;
  int numNonSwitchStrings = nonSwitchStrings.Size();
  if (numNonSwitchStrings < kMinNonSwitchWords)
    ThrowUserErrorException();

  if (!ParseArchiveCommand(nonSwitchStrings[kCommandIndex], options.Command))
    ThrowUserErrorException();

  options.TechMode = parser[NKey::kTechMode].ThereIs;
  options.CalcCrc = parser[NKey::kCalcCrc].ThereIs;

  if (parser[NKey::kCaseSensitive].ThereIs)
    g_CaseSensitive = (parser[NKey::kCaseSensitive].PostCharIndex < 0);
=======
    throw CArcCmdLineException(kCannotFindArchive);
  
  UStringVector fullPaths;
  
  unsigned i;
  
  for (i = 0; i < paths.Size(); i++)
  {
    FString fullPath;
    NFile::NDir::MyGetFullPathName(paths[i], fullPath);
    fullPaths.Add(fs2us(fullPath));
  }
  
  CUIntVector indices;
  SortFileNames(fullPaths, indices);
  sortedPaths.ClearAndReserve(indices.Size());
  sortedFullPaths.ClearAndReserve(indices.Size());

  for (i = 0; i < indices.Size(); i++)
  {
    unsigned index = indices[i];
    sortedPaths.AddInReserved(fs2us(paths[index]));
    sortedFullPaths.AddInReserved(fullPaths[index]);
    if (i > 0 && CompareFileNames(sortedFullPaths[i], sortedFullPaths[i - 1]) == 0)
      throw CArcCmdLineException("Duplicate archive path:", sortedFullPaths[i]);
  }

  return S_OK;
}

static void SetBoolPair(NCommandLineParser::CParser &parser, unsigned switchID, CBoolPair &bp)
{
  bp.Def = parser[switchID].ThereIs;
  if (bp.Def)
    bp.Val = !parser[switchID].WithMinus;
}

void CArcCmdLineParser::Parse2(CArcCmdLineOptions &options)
{
  const UStringVector &nonSwitchStrings = parser.NonSwitchStrings;
  unsigned numNonSwitchStrings = nonSwitchStrings.Size();
  if (numNonSwitchStrings < kMinNonSwitchWords)
    throw CArcCmdLineException("The command must be specified");

  if (!ParseArchiveCommand(nonSwitchStrings[kCommandIndex], options.Command))
    throw CArcCmdLineException("Unsupported command:", nonSwitchStrings[kCommandIndex]);

  if (parser[NKey::kHash].ThereIs)
    options.HashMethods = parser[NKey::kHash].PostStrings;
  
  if (parser[NKey::kElimDup].ThereIs)
  {
    options.ExtractOptions.ElimDup.Def = true;
    options.ExtractOptions.ElimDup.Val = !parser[NKey::kElimDup].WithMinus;
  }
  
  NWildcard::ECensorPathMode censorPathMode = NWildcard::k_RelatPath;
  bool fullPathMode = parser[NKey::kFullPathMode].ThereIs;
  if (fullPathMode)
  {
    censorPathMode = NWildcard::k_AbsPath;
    const UString &s = parser[NKey::kFullPathMode].PostStrings[0];
    if (!s.IsEmpty())
    {
      if (s == L"2")
        censorPathMode = NWildcard::k_FullPath;
      else
        throw CArcCmdLineException("Unsupported -spf:", s);
    }
  }
>>>>>>> upstream/master

  NRecursedType::EEnum recursedType;
  if (parser[NKey::kRecursed].ThereIs)
    recursedType = GetRecursedTypeFromIndex(parser[NKey::kRecursed].PostCharIndex);
  else
    recursedType = NRecursedType::kNonRecursed;

<<<<<<< HEAD
  g_CodePage = FindCharset(parser, NKey::kConsoleCharSet, -1);
  UINT codePage = FindCharset(parser, NKey::kListfileCharSet, CP_UTF8);

  bool thereAreSwitchIncludes = false;
  if (parser[NKey::kInclude].ThereIs)
  {
    thereAreSwitchIncludes = true;
    AddSwitchWildCardsToCensor(options.WildcardCensor,
        parser[NKey::kInclude].PostStrings, true, recursedType, codePage);
  }
  if (parser[NKey::kExclude].ThereIs)
    AddSwitchWildCardsToCensor(options.WildcardCensor,
        parser[NKey::kExclude].PostStrings, false, recursedType, codePage);
 
  int curCommandIndex = kCommandIndex + 1;
  bool thereIsArchiveName = !parser[NKey::kNoArName].ThereIs &&
      options.Command.CommandType != NCommandType::kBenchmark &&
      options.Command.CommandType != NCommandType::kInfo;

  bool isExtractGroupCommand = options.Command.IsFromExtractGroup();
  bool isExtractOrList = isExtractGroupCommand || options.Command.CommandType == NCommandType::kList;

  if (isExtractOrList && options.StdInMode)
    thereIsArchiveName = false;

  if (thereIsArchiveName)
  {
    if (curCommandIndex >= numNonSwitchStrings)
      ThrowUserErrorException();
    options.ArchiveName = nonSwitchStrings[curCommandIndex++];
    if (options.ArchiveName.IsEmpty())
      ThrowUserErrorException();
  }

  AddToCensorFromNonSwitchesStrings(
      curCommandIndex, options.WildcardCensor,
      nonSwitchStrings, recursedType, thereAreSwitchIncludes, codePage);
=======
  bool wildcardMatching = true;
  if (parser[NKey::kDisableWildcardParsing].ThereIs)
    wildcardMatching = false;

  g_CodePage = FindCharset(parser, NKey::kConsoleCharSet, true, -1);
  Int32 codePage = FindCharset(parser, NKey::kListfileCharSet, false, CP_UTF8);

  bool thereAreSwitchIncludes = false;
  
  if (parser[NKey::kInclude].ThereIs)
  {
    thereAreSwitchIncludes = true;
    AddSwitchWildcardsToCensor(options.Censor,
        parser[NKey::kInclude].PostStrings, true, recursedType, wildcardMatching, codePage);
  }

  if (parser[NKey::kExclude].ThereIs)
    AddSwitchWildcardsToCensor(options.Censor,
        parser[NKey::kExclude].PostStrings, false, recursedType, wildcardMatching, codePage);
 
  unsigned curCommandIndex = kCommandIndex + 1;
  bool thereIsArchiveName = !parser[NKey::kNoArName].ThereIs &&
      options.Command.CommandType != NCommandType::kBenchmark &&
      options.Command.CommandType != NCommandType::kInfo &&
      options.Command.CommandType != NCommandType::kHash;

  bool isExtractGroupCommand = options.Command.IsFromExtractGroup();
  bool isExtractOrList = isExtractGroupCommand || options.Command.CommandType == NCommandType::kList;
  bool isRename = options.Command.CommandType == NCommandType::kRename;

  if ((isExtractOrList || isRename) && options.StdInMode)
    thereIsArchiveName = false;

  if (parser[NKey::kArcNameMode].ThereIs)
    options.UpdateOptions.ArcNameMode = ParseArcNameMode(parser[NKey::kArcNameMode].PostCharIndex);

  if (thereIsArchiveName)
  {
    if (curCommandIndex >= numNonSwitchStrings)
      throw CArcCmdLineException("Cannot find archive name");
    options.ArchiveName = nonSwitchStrings[curCommandIndex++];
    if (options.ArchiveName.IsEmpty())
      throw CArcCmdLineException("Archive name cannot by empty");
    #ifdef _WIN32
    // options.ArchiveName.Replace(L'/', WCHAR_PATH_SEPARATOR);
    #endif
  }

  AddToCensorFromNonSwitchesStrings(isRename ? &options.UpdateOptions.RenamePairs : NULL,
      curCommandIndex, options.Censor,
      nonSwitchStrings, recursedType, wildcardMatching,
      thereAreSwitchIncludes, codePage);
>>>>>>> upstream/master

  options.YesToAll = parser[NKey::kYes].ThereIs;


  #ifndef _NO_CRYPTO
  options.PasswordEnabled = parser[NKey::kPassword].ThereIs;
  if (options.PasswordEnabled)
    options.Password = parser[NKey::kPassword].PostStrings[0];
  #endif

  options.ShowDialog = parser[NKey::kShowDialog].ThereIs;

  if (parser[NKey::kArchiveType].ThereIs)
    options.ArcType = parser[NKey::kArchiveType].PostStrings[0];

<<<<<<< HEAD
  SetMethodOptions(parser, options.Properties);

  if (isExtractOrList)
  {
    if (!options.WildcardCensor.AllAreRelative())
      ThrowException("Cannot use absolute pathnames for this command");

    NWildcard::CCensor archiveWildcardCensor;

    if (parser[NKey::kArInclude].ThereIs)
      AddSwitchWildCardsToCensor(archiveWildcardCensor,
          parser[NKey::kArInclude].PostStrings, true, NRecursedType::kNonRecursed, codePage);
    if (parser[NKey::kArExclude].ThereIs)
      AddSwitchWildCardsToCensor(archiveWildcardCensor,
          parser[NKey::kArExclude].PostStrings, false, NRecursedType::kNonRecursed, codePage);

    if (thereIsArchiveName)
      AddNameToCensor(archiveWildcardCensor, options.ArchiveName, true, NRecursedType::kNonRecursed);

    #ifdef _WIN32
    ConvertToLongNames(archiveWildcardCensor);
    #endif

    archiveWildcardCensor.ExtendExclude();

    if (options.StdInMode)
    {
      UString arcName = parser[NKey::kStdIn].PostStrings.Front();
      options.ArchivePathsSorted.Add(arcName);
      options.ArchivePathsFullSorted.Add(arcName);
    }
    else
    {
      EnumerateDirItemsAndSort(archiveWildcardCensor,
        options.ArchivePathsSorted,
        options.ArchivePathsFullSorted);
    }
    
    if (isExtractGroupCommand)
    {
      if (options.StdOutMode && options.IsStdOutTerminal && options.IsStdErrTerminal)
        throw kSameTerminalError;
      if (parser[NKey::kOutputDir].ThereIs)
      {
        options.OutputDir = us2fs(parser[NKey::kOutputDir].PostStrings[0]);
        NFile::NName::NormalizeDirPathPrefix(options.OutputDir);
      }

      options.OverwriteMode = NExtract::NOverwriteMode::kAskBefore;
      if (parser[NKey::kOverwrite].ThereIs)
        options.OverwriteMode = k_OverwriteModes[parser[NKey::kOverwrite].PostCharIndex];
      else if (options.YesToAll)
        options.OverwriteMode = NExtract::NOverwriteMode::kWithoutPrompt;
=======
  options.ExcludedArcTypes = parser[NKey::kExcludedArcType].PostStrings;

  SetMethodOptions(parser, options.Properties);

  if (parser[NKey::kNtSecurity].ThereIs) options.NtSecurity.SetTrueTrue();

  SetBoolPair(parser, NKey::kAltStreams, options.AltStreams);
  SetBoolPair(parser, NKey::kHardLinks, options.HardLinks);
  SetBoolPair(parser, NKey::kSymLinks, options.SymLinks);

  if (isExtractOrList)
  {
    CExtractOptionsBase &eo = options.ExtractOptions;

    {
      CExtractNtOptions &nt = eo.NtOptions;
      nt.NtSecurity = options.NtSecurity;

      nt.AltStreams = options.AltStreams;
      if (!options.AltStreams.Def)
        nt.AltStreams.Val = true;

      nt.HardLinks = options.HardLinks;
      if (!options.HardLinks.Def)
        nt.HardLinks.Val = true;

      nt.SymLinks = options.SymLinks;
      if (!options.SymLinks.Def)
        nt.SymLinks.Val = true;

      nt.ReplaceColonForAltStream = parser[NKey::kReplaceColonForAltStream].ThereIs;
      nt.WriteToAltStreamIfColon = parser[NKey::kWriteToAltStreamIfColon].ThereIs;
    }
      
    options.Censor.AddPathsToCensor(NWildcard::k_AbsPath);
    options.Censor.ExtendExclude();

    // are there paths that look as non-relative (!Prefix.IsEmpty())
    if (!options.Censor.AllAreRelative())
      throw CArcCmdLineException("Cannot use absolute pathnames for this command");

    NWildcard::CCensor &arcCensor = options.arcCensor;

    if (parser[NKey::kArInclude].ThereIs)
      AddSwitchWildcardsToCensor(arcCensor, parser[NKey::kArInclude].PostStrings, true, NRecursedType::kNonRecursed, wildcardMatching, codePage);
    if (parser[NKey::kArExclude].ThereIs)
      AddSwitchWildcardsToCensor(arcCensor, parser[NKey::kArExclude].PostStrings, false, NRecursedType::kNonRecursed, wildcardMatching, codePage);

    if (thereIsArchiveName)
      AddNameToCensor(arcCensor, options.ArchiveName, true, NRecursedType::kNonRecursed, wildcardMatching);

    arcCensor.AddPathsToCensor(NWildcard::k_RelatPath);

    #ifdef _WIN32
    ConvertToLongNames(arcCensor);
    #endif

    arcCensor.ExtendExclude();

    if (options.StdInMode)
      options.ArcName_for_StdInMode = parser[NKey::kStdIn].PostStrings.Front();
    
    if (isExtractGroupCommand)
    {
      if (options.StdOutMode)
      {
        if (
                  options.Number_for_Percents == k_OutStream_stdout
            // || options.Number_for_Out      == k_OutStream_stdout
            // || options.Number_for_Errors   == k_OutStream_stdout
            ||
            (
              (options.IsStdOutTerminal && options.IsStdErrTerminal)
              &&
              (
                      options.Number_for_Percents != k_OutStream_disabled
                // || options.Number_for_Out      != k_OutStream_disabled
                // || options.Number_for_Errors   != k_OutStream_disabled
              )
            )
           )
          throw CArcCmdLineException(kSameTerminalError);
      }
      
      if (parser[NKey::kOutputDir].ThereIs)
      {
        eo.OutputDir = us2fs(parser[NKey::kOutputDir].PostStrings[0]);
        NFile::NName::NormalizeDirPathPrefix(eo.OutputDir);
      }

      eo.OverwriteMode = NExtract::NOverwriteMode::kAsk;
      if (parser[NKey::kOverwrite].ThereIs)
      {
        eo.OverwriteMode = k_OverwriteModes[(unsigned)parser[NKey::kOverwrite].PostCharIndex];
        eo.OverwriteMode_Force = true;
      }
      else if (options.YesToAll)
      {
        eo.OverwriteMode = NExtract::NOverwriteMode::kOverwrite;
        eo.OverwriteMode_Force = true;
      }
    }

    eo.PathMode = options.Command.GetPathMode();
    if (censorPathMode == NWildcard::k_AbsPath)
    {
      eo.PathMode = NExtract::NPathMode::kAbsPaths;
      eo.PathMode_Force = true;
    }
    else if (censorPathMode == NWildcard::k_FullPath)
    {
      eo.PathMode = NExtract::NPathMode::kFullPaths;
      eo.PathMode_Force = true;
>>>>>>> upstream/master
    }
  }
  else if (options.Command.IsFromUpdateGroup())
  {
<<<<<<< HEAD
=======
    if (parser[NKey::kArInclude].ThereIs)
      throw CArcCmdLineException("-ai switch is not supported for this command");

>>>>>>> upstream/master
    CUpdateOptions &updateOptions = options.UpdateOptions;

    SetAddCommandOptions(options.Command.CommandType, parser, updateOptions);
    
    updateOptions.MethodMode.Properties = options.Properties;

    if (parser[NKey::kShareForWrite].ThereIs)
      updateOptions.OpenShareForWrite = true;

<<<<<<< HEAD
    options.EnablePercents = !parser[NKey::kDisablePercents].ThereIs;

    if (options.EnablePercents)
    {
      if ((options.StdOutMode && !options.IsStdErrTerminal) ||
         (!options.StdOutMode && !options.IsStdOutTerminal))
        options.EnablePercents = false;
    }
=======
    updateOptions.PathMode = censorPathMode;

    updateOptions.AltStreams = options.AltStreams;
    updateOptions.NtSecurity = options.NtSecurity;
    updateOptions.HardLinks = options.HardLinks;
    updateOptions.SymLinks = options.SymLinks;
>>>>>>> upstream/master

    updateOptions.EMailMode = parser[NKey::kEmail].ThereIs;
    if (updateOptions.EMailMode)
    {
      updateOptions.EMailAddress = parser[NKey::kEmail].PostStrings.Front();
<<<<<<< HEAD
      if (updateOptions.EMailAddress.Length() > 0)
=======
      if (updateOptions.EMailAddress.Len() > 0)
>>>>>>> upstream/master
        if (updateOptions.EMailAddress[0] == L'.')
        {
          updateOptions.EMailRemoveAfter = true;
          updateOptions.EMailAddress.Delete(0);
        }
    }

    updateOptions.StdOutMode = options.StdOutMode;
    updateOptions.StdInMode = options.StdInMode;

<<<<<<< HEAD
    if (updateOptions.StdOutMode && updateOptions.EMailMode)
      throw "stdout mode and email mode cannot be combined";
    if (updateOptions.StdOutMode && options.IsStdOutTerminal)
      throw kTerminalOutError;
    if (updateOptions.StdInMode)
      updateOptions.StdInFileName = parser[NKey::kStdIn].PostStrings.Front();

    #ifdef _WIN32
    ConvertToLongNames(options.WildcardCensor);
    #endif
=======
    updateOptions.DeleteAfterCompressing = parser[NKey::kDeleteAfterCompressing].ThereIs;
    updateOptions.SetArcMTime = parser[NKey::kSetArcMTime].ThereIs;

    if (updateOptions.StdOutMode && updateOptions.EMailMode)
      throw CArcCmdLineException("stdout mode and email mode cannot be combined");
    
    if (updateOptions.StdOutMode)
    {
      if (options.IsStdOutTerminal)
        throw CArcCmdLineException(kTerminalOutError);
      
      if (options.Number_for_Percents == k_OutStream_stdout
          || options.Number_for_Out == k_OutStream_stdout
          || options.Number_for_Errors == k_OutStream_stdout)
        throw CArcCmdLineException(kSameTerminalError);
    }
    
    if (updateOptions.StdInMode)
      updateOptions.StdInFileName = parser[NKey::kStdIn].PostStrings.Front();

    if (options.Command.CommandType == NCommandType::kRename)
      if (updateOptions.Commands.Size() != 1)
        throw CArcCmdLineException("Only one archive can be created with rename command");
>>>>>>> upstream/master
  }
  else if (options.Command.CommandType == NCommandType::kBenchmark)
  {
    options.NumIterations = 1;
    if (curCommandIndex < numNonSwitchStrings)
    {
<<<<<<< HEAD
      if (!ConvertStringToUInt32(nonSwitchStrings[curCommandIndex++], options.NumIterations))
        ThrowUserErrorException();
    }
  }
=======
      if (!StringToUInt32(nonSwitchStrings[curCommandIndex], options.NumIterations))
        throw CArcCmdLineException("Incorrect Number of benmchmark iterations", nonSwitchStrings[curCommandIndex]);
      curCommandIndex++;
    }
  }
  else if (options.Command.CommandType == NCommandType::kHash)
  {
    options.Censor.AddPathsToCensor(censorPathMode);
    options.Censor.ExtendExclude();

    CHashOptions &hashOptions = options.HashOptions;
    hashOptions.PathMode = censorPathMode;
    hashOptions.Methods = options.HashMethods;
    if (parser[NKey::kShareForWrite].ThereIs)
      hashOptions.OpenShareForWrite = true;
    hashOptions.StdInMode = options.StdInMode;
    hashOptions.AltStreamsMode = options.AltStreams.Val;
  }
>>>>>>> upstream/master
  else if (options.Command.CommandType == NCommandType::kInfo)
  {
  }
  else
<<<<<<< HEAD
    ThrowUserErrorException();
  options.WildcardCensor.ExtendExclude();
=======
    throw 20150919;
>>>>>>> upstream/master
}
