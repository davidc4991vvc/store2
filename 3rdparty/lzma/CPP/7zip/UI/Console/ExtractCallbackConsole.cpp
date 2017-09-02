<<<<<<< HEAD
// ExtractCallbackConsole.h

#include "StdAfx.h"

#include "ExtractCallbackConsole.h"
#include "UserInputUtils.h"
#include "ConsoleClose.h"

#include "Common/Wildcard.h"

#include "Windows/FileDir.h"
#include "Windows/FileFind.h"
#include "Windows/Time.h"
#include "Windows/Defs.h"
#include "Windows/PropVariant.h"
#include "Windows/Error.h"
#include "Windows/PropVariantConversions.h"
=======
// ExtractCallbackConsole.cpp

#include "StdAfx.h"

#include "../../../Common/IntToString.h"
#include "../../../Common/Wildcard.h"

#include "../../../Windows/FileDir.h"
#include "../../../Windows/FileFind.h"
#include "../../../Windows/TimeUtils.h"
#include "../../../Windows/ErrorMsg.h"
#include "../../../Windows/PropVariantConv.h"

#ifndef _7ZIP_ST
#include "../../../Windows/Synchronization.h"
#endif
>>>>>>> upstream/master

#include "../../Common/FilePathAutoRename.h"

#include "../Common/ExtractingFilePath.h"

<<<<<<< HEAD
using namespace NWindows;
using namespace NFile;
using namespace NDirectory;

static const char *kTestString    =  "Testing     ";
static const char *kExtractString =  "Extracting  ";
static const char *kSkipString   =  "Skipping    ";
=======
#include "ConsoleClose.h"
#include "ExtractCallbackConsole.h"
#include "UserInputUtils.h"

using namespace NWindows;
using namespace NFile;
using namespace NDir;

static HRESULT CheckBreak2()
{
  return NConsoleClose::TestBreakSignal() ? E_ABORT : S_OK;
}

static const char *kError = "ERROR: ";


void CExtractScanConsole::StartScanning()
{
  if (NeedPercents())
    _percent.Command = "Scan";
}

HRESULT CExtractScanConsole::ScanProgress(const CDirItemsStat &st, const FString &path, bool /* isDir */)
{
  if (NeedPercents())
  {
    _percent.Files = st.NumDirs + st.NumFiles;
    _percent.Completed = st.GetTotalBytes();
    _percent.FileName = fs2us(path);
    _percent.Print();
  }

  return CheckBreak2();
}

HRESULT CExtractScanConsole::ScanError(const FString &path, DWORD systemError)
{
  ClosePercentsAndFlush();
  
  if (_se)
  {
    *_se << endl << kError << NError::MyFormatMessage(systemError) << endl <<
        fs2us(path) << endl << endl;
    _se->Flush();
  }
  return HRESULT_FROM_WIN32(systemError);
}


void Print_UInt64_and_String(AString &s, UInt64 val, const char *name)
{
  char temp[32];
  ConvertUInt64ToString(val, temp);
  s += temp;
  s.Add_Space();
  s += name;
}

void PrintSize_bytes_Smart(AString &s, UInt64 val)
{
  Print_UInt64_and_String(s, val, "bytes");

  if (val == 0)
    return;

  unsigned numBits = 10;
  char c = 'K';
  char temp[4] = { 'K', 'i', 'B', 0 };
       if (val >= ((UInt64)10 << 30)) { numBits = 30; c = 'G'; }
  else if (val >= ((UInt64)10 << 20)) { numBits = 20; c = 'M'; }
  temp[0] = c;
  s += " (";
  Print_UInt64_and_String(s, ((val + ((UInt64)1 << numBits) - 1) >> numBits), temp);
  s += ')';
}

void Print_DirItemsStat(AString &s, const CDirItemsStat &st)
{
  if (st.NumDirs != 0)
  {
    Print_UInt64_and_String(s, st.NumDirs, st.NumDirs == 1 ? "folder" : "folders");
    s += ", ";
  }
  Print_UInt64_and_String(s, st.NumFiles, st.NumFiles == 1 ? "file" : "files");
  s += ", ";
  PrintSize_bytes_Smart(s, st.FilesSize);
  if (st.NumAltStreams != 0)
  {
    s.Add_LF();
    Print_UInt64_and_String(s, st.NumAltStreams, "alternate streams");
    s += ", ";
    PrintSize_bytes_Smart(s, st.AltStreamsSize);
  }
}

void CExtractScanConsole::PrintStat(const CDirItemsStat &st)
{
  if (_so)
  {
    AString s;
    Print_DirItemsStat(s, st);
    *_so << s << endl;
  }
}







#ifndef _7ZIP_ST
static NSynchronization::CCriticalSection g_CriticalSection;
#define MT_LOCK NSynchronization::CCriticalSectionLock lock(g_CriticalSection);
#else
#define MT_LOCK
#endif


static const char *kTestString    =  "T";
static const char *kExtractString =  "-";
static const char *kSkipString    =  ".";
>>>>>>> upstream/master

// static const char *kCantAutoRename = "can not create file with auto name\n";
// static const char *kCantRenameFile = "can not rename existing file\n";
// static const char *kCantDeleteOutputFile = "can not delete output file ";
<<<<<<< HEAD
static const char *kError = "ERROR: ";
static const char *kMemoryExceptionMessage = "Can't allocate required memory!";

static const char *kProcessing = "Processing archive: ";
=======

static const char *kMemoryExceptionMessage = "Can't allocate required memory!";

static const char *kExtracting = "Extracting archive: ";
static const char *kTesting = "Testing archive: ";

>>>>>>> upstream/master
static const char *kEverythingIsOk = "Everything is Ok";
static const char *kNoFiles = "No files to process";

static const char *kUnsupportedMethod = "Unsupported Method";
static const char *kCrcFailed = "CRC Failed";
static const char *kCrcFailedEncrypted = "CRC Failed in encrypted file. Wrong password?";
static const char *kDataError = "Data Error";
static const char *kDataErrorEncrypted = "Data Error in encrypted file. Wrong password?";
<<<<<<< HEAD
static const char *kUnknownError = "Unknown Error";

STDMETHODIMP CExtractCallbackConsole::SetTotal(UInt64)
{
  if (NConsoleClose::TestBreakSignal())
    return E_ABORT;
  return S_OK;
}

STDMETHODIMP CExtractCallbackConsole::SetCompleted(const UInt64 *)
{
  if (NConsoleClose::TestBreakSignal())
    return E_ABORT;
  return S_OK;
}

STDMETHODIMP CExtractCallbackConsole::AskOverwrite(
    const wchar_t *existName, const FILETIME *, const UInt64 *,
    const wchar_t *newName, const FILETIME *, const UInt64 *,
    Int32 *answer)
{
  (*OutStream) << "file " << existName <<
    "\nalready exists. Overwrite with " << endl;
  (*OutStream) << newName;
  
  NUserAnswerMode::EEnum overwriteAnswer = ScanUserYesNoAllQuit(OutStream);
  
  switch(overwriteAnswer)
=======
static const char *kUnavailableData = "Unavailable data";
static const char *kUnexpectedEnd = "Unexpected end of data";
static const char *kDataAfterEnd = "There are some data after the end of the payload data";
static const char *kIsNotArc = "Is not archive";
static const char *kHeadersError = "Headers Error";
static const char *kWrongPassword = "Wrong password";

static const char * const k_ErrorFlagsMessages[] =
{
    "Is not archive"
  , "Headers Error"
  , "Headers Error in encrypted archive. Wrong password?"
  , "Unavailable start of archive"
  , "Unconfirmed start of archive"
  , "Unexpected end of archive"
  , "There are data after the end of archive"
  , "Unsupported method"
  , "Unsupported feature"
  , "Data Error"
  , "CRC Error"
};

STDMETHODIMP CExtractCallbackConsole::SetTotal(UInt64 size)
{
  MT_LOCK

  if (NeedPercents())
  {
    _percent.Total = size;
    _percent.Print();
  }
  return CheckBreak2();
}

STDMETHODIMP CExtractCallbackConsole::SetCompleted(const UInt64 *completeValue)
{
  MT_LOCK

  if (NeedPercents())
  {
    if (completeValue)
      _percent.Completed = *completeValue;
    _percent.Print();
  }
  return CheckBreak2();
}

static const char *kTab = "  ";

static void PrintFileInfo(CStdOutStream *_so, const wchar_t *path, const FILETIME *ft, const UInt64 *size)
{
  *_so << kTab << "Path:     " << path << endl;
  if (size)
  {
    AString s;
    PrintSize_bytes_Smart(s, *size);
    *_so << kTab << "Size:     " << s << endl;
  }
  if (ft)
  {
    char temp[64];
    FILETIME locTime;
    if (FileTimeToLocalFileTime(ft, &locTime))
      if (ConvertFileTimeToString(locTime, temp, true, true))
        *_so << kTab << "Modified: " << temp << endl;
  }
}

STDMETHODIMP CExtractCallbackConsole::AskOverwrite(
    const wchar_t *existName, const FILETIME *existTime, const UInt64 *existSize,
    const wchar_t *newName, const FILETIME *newTime, const UInt64 *newSize,
    Int32 *answer)
{
  MT_LOCK
  
  RINOK(CheckBreak2());

  ClosePercentsAndFlush();

  if (_so)
  {
    *_so << endl << "Would you like to replace the existing file:\n";
    PrintFileInfo(_so, existName, existTime, existSize);
    *_so << "with the file from archive:\n";
    PrintFileInfo(_so, newName, newTime, newSize);
  }
  
  NUserAnswerMode::EEnum overwriteAnswer = ScanUserYesNoAllQuit(_so);
  
  switch (overwriteAnswer)
>>>>>>> upstream/master
  {
    case NUserAnswerMode::kQuit:  return E_ABORT;
    case NUserAnswerMode::kNo:     *answer = NOverwriteAnswer::kNo; break;
    case NUserAnswerMode::kNoAll:  *answer = NOverwriteAnswer::kNoToAll; break;
    case NUserAnswerMode::kYesAll: *answer = NOverwriteAnswer::kYesToAll; break;
    case NUserAnswerMode::kYes:    *answer = NOverwriteAnswer::kYes; break;
    case NUserAnswerMode::kAutoRenameAll: *answer = NOverwriteAnswer::kAutoRename; break;
    default: return E_FAIL;
  }
<<<<<<< HEAD
  return S_OK;
}

STDMETHODIMP CExtractCallbackConsole::PrepareOperation(const wchar_t *name, bool /* isFolder */, Int32 askExtractMode, const UInt64 *position)
{
  switch (askExtractMode)
  {
    case NArchive::NExtract::NAskMode::kExtract: (*OutStream) << kExtractString; break;
    case NArchive::NExtract::NAskMode::kTest:    (*OutStream) << kTestString; break;
    case NArchive::NExtract::NAskMode::kSkip:    (*OutStream) << kSkipString; break;
  };
  (*OutStream) << name;
  if (position != 0)
    (*OutStream) << " <" << *position << ">";
  return S_OK;
=======
  
  if (_so)
  {
    *_so << endl;
    if (NeedFlush)
      _so->Flush();
  }
  
  return CheckBreak2();
}

STDMETHODIMP CExtractCallbackConsole::PrepareOperation(const wchar_t *name, Int32 /* isFolder */, Int32 askExtractMode, const UInt64 *position)
{
  MT_LOCK
  
  _currentName = name;
  
  const char *s;
  unsigned requiredLevel = 1;

  switch (askExtractMode)
  {
    case NArchive::NExtract::NAskMode::kExtract: s = kExtractString; break;
    case NArchive::NExtract::NAskMode::kTest:    s = kTestString; break;
    case NArchive::NExtract::NAskMode::kSkip:    s = kSkipString; requiredLevel = 2; break;
    default: s = "???"; requiredLevel = 2;
  };

  bool show2 = (LogLevel >= requiredLevel && _so);

  if (show2)
  {
    ClosePercents_for_so();
    
    _tempA = s;
    if (name)
      _tempA.Add_Space();
    *_so << _tempA;

    _tempU.Empty();
    if (name)
      _tempU = name;
    _so->PrintUString(_tempU, _tempA);
    if (position)
      *_so << " <" << *position << ">";
    *_so << endl;
 
    if (NeedFlush)
      _so->Flush();
  }

  if (NeedPercents())
  {
    if (PercentsNameLevel >= 1)
    {
      _percent.FileName.Empty();
      _percent.Command.Empty();
      if (PercentsNameLevel > 1 || !show2)
      {
        _percent.Command = s;
        if (name)
          _percent.FileName = name;
      }
    }
    _percent.Print();
  }

  return CheckBreak2();
>>>>>>> upstream/master
}

STDMETHODIMP CExtractCallbackConsole::MessageError(const wchar_t *message)
{
<<<<<<< HEAD
  (*OutStream) << message << endl;
  NumFileErrorsInCurrentArchive++;
  NumFileErrors++;
  return S_OK;
}

STDMETHODIMP CExtractCallbackConsole::SetOperationResult(Int32 operationResult, bool encrypted)
{
  switch(operationResult)
  {
    case NArchive::NExtract::NOperationResult::kOK:
      break;
    default:
    {
      NumFileErrorsInCurrentArchive++;
      NumFileErrors++;
      (*OutStream) << "     ";
      switch(operationResult)
      {
        case NArchive::NExtract::NOperationResult::kUnSupportedMethod:
          (*OutStream) << kUnsupportedMethod;
          break;
        case NArchive::NExtract::NOperationResult::kCRCError:
          (*OutStream) << (encrypted ? kCrcFailedEncrypted: kCrcFailed);
          break;
        case NArchive::NExtract::NOperationResult::kDataError:
          (*OutStream) << (encrypted ? kDataErrorEncrypted : kDataError);
          break;
        default:
          (*OutStream) << kUnknownError;
      }
    }
  }
  (*OutStream) << endl;
  return S_OK;
}

=======
  MT_LOCK
  
  RINOK(CheckBreak2());

  NumFileErrors_in_Current++;
  NumFileErrors++;

  ClosePercentsAndFlush();
  if (_se)
  {
    *_se << kError << message << endl;
    _se->Flush();
  }

  return CheckBreak2();
}

void SetExtractErrorMessage(Int32 opRes, Int32 encrypted, AString &dest)
{
  dest.Empty();
    const char *s = NULL;
    
    switch (opRes)
    {
      case NArchive::NExtract::NOperationResult::kUnsupportedMethod:
        s = kUnsupportedMethod;
        break;
      case NArchive::NExtract::NOperationResult::kCRCError:
        s = (encrypted ? kCrcFailedEncrypted : kCrcFailed);
        break;
      case NArchive::NExtract::NOperationResult::kDataError:
        s = (encrypted ? kDataErrorEncrypted : kDataError);
        break;
      case NArchive::NExtract::NOperationResult::kUnavailable:
        s = kUnavailableData;
        break;
      case NArchive::NExtract::NOperationResult::kUnexpectedEnd:
        s = kUnexpectedEnd;
        break;
      case NArchive::NExtract::NOperationResult::kDataAfterEnd:
        s = kDataAfterEnd;
        break;
      case NArchive::NExtract::NOperationResult::kIsNotArc:
        s = kIsNotArc;
        break;
      case NArchive::NExtract::NOperationResult::kHeadersError:
        s = kHeadersError;
        break;
      case NArchive::NExtract::NOperationResult::kWrongPassword:
        s = kWrongPassword;
        break;
    }
    
    dest += kError;
    if (s)
      dest += s;
    else
    {
      char temp[16];
      ConvertUInt32ToString(opRes, temp);
      dest += "Error #";
      dest += temp;
    }
}

STDMETHODIMP CExtractCallbackConsole::SetOperationResult(Int32 opRes, Int32 encrypted)
{
  MT_LOCK
  
  if (opRes == NArchive::NExtract::NOperationResult::kOK)
  {
    if (NeedPercents())
    {
      _percent.Command.Empty();
      _percent.FileName.Empty();
      _percent.Files++;
    }
  }
  else
  {
    NumFileErrors_in_Current++;
    NumFileErrors++;
    
    if (_se)
    {
      ClosePercentsAndFlush();
      
      AString s;
      SetExtractErrorMessage(opRes, encrypted, s);
      
      *_se << s;
      if (!_currentName.IsEmpty())
        *_se << " : " << _currentName;
      *_se << endl;
      _se->Flush();
    }
  }
  
  return CheckBreak2();
}

STDMETHODIMP CExtractCallbackConsole::ReportExtractResult(Int32 opRes, Int32 encrypted, const wchar_t *name)
{
  if (opRes != NArchive::NExtract::NOperationResult::kOK)
  {
    _currentName = name;
    return SetOperationResult(opRes, encrypted);
  }

  return CheckBreak2();
}



>>>>>>> upstream/master
#ifndef _NO_CRYPTO

HRESULT CExtractCallbackConsole::SetPassword(const UString &password)
{
  PasswordIsDefined = true;
  Password = password;
  return S_OK;
}

STDMETHODIMP CExtractCallbackConsole::CryptoGetTextPassword(BSTR *password)
{
<<<<<<< HEAD
  if (!PasswordIsDefined)
  {
    Password = GetPassword(OutStream);
    PasswordIsDefined = true;
  }
  return StringToBstr(Password, password);
=======
  COM_TRY_BEGIN
  MT_LOCK
  return Open_CryptoGetTextPassword(password);
  COM_TRY_END
>>>>>>> upstream/master
}

#endif

<<<<<<< HEAD
HRESULT CExtractCallbackConsole::BeforeOpen(const wchar_t *name)
{
  NumArchives++;
  NumFileErrorsInCurrentArchive = 0;
  (*OutStream) << endl << kProcessing << name << endl;
  return S_OK;
}

HRESULT CExtractCallbackConsole::OpenResult(const wchar_t * /* name */, HRESULT result, bool encrypted)
{
  (*OutStream) << endl;
  if (result != S_OK)
  {
    (*OutStream) << "Error: ";
    if (result == S_FALSE)
    {
      (*OutStream) << (encrypted ?
        "Can not open encrypted archive. Wrong password?" :
        "Can not open file as archive");
    }
    else
    {
      if (result == E_OUTOFMEMORY)
        (*OutStream) << "Can't allocate required memory";
      else
        (*OutStream) << NError::MyFormatMessageW(result);
    }
    (*OutStream) << endl;
    NumArchiveErrors++;
  }
  return S_OK;
=======
HRESULT CExtractCallbackConsole::BeforeOpen(const wchar_t *name, bool testMode)
{
  RINOK(CheckBreak2());

  NumTryArcs++;
  ThereIsError_in_Current = false;
  ThereIsWarning_in_Current = false;
  NumFileErrors_in_Current = 0;
  
  ClosePercents_for_so();
  if (_so)
    *_so << endl << (testMode ? kTesting : kExtracting) << name << endl;

  if (NeedPercents())
    _percent.Command = "Open";
  return S_OK;
}

HRESULT Print_OpenArchive_Props(CStdOutStream &so, const CCodecs *codecs, const CArchiveLink &arcLink);
HRESULT Print_OpenArchive_Error(CStdOutStream &so, const CCodecs *codecs, const CArchiveLink &arcLink);

static AString GetOpenArcErrorMessage(UInt32 errorFlags)
{
  AString s;
  
  for (unsigned i = 0; i < ARRAY_SIZE(k_ErrorFlagsMessages); i++)
  {
    UInt32 f = (1 << i);
    if ((errorFlags & f) == 0)
      continue;
    const char *m = k_ErrorFlagsMessages[i];
    if (!s.IsEmpty())
      s.Add_LF();
    s += m;
    errorFlags &= ~f;
  }
  
  if (errorFlags != 0)
  {
    char sz[16];
    sz[0] = '0';
    sz[1] = 'x';
    ConvertUInt32ToHex(errorFlags, sz + 2);
    if (!s.IsEmpty())
      s.Add_LF();
    s += sz;
  }
  
  return s;
}

void PrintErrorFlags(CStdOutStream &so, const char *s, UInt32 errorFlags)
{
  if (errorFlags == 0)
    return;
  so << s << endl << GetOpenArcErrorMessage(errorFlags) << endl;
}

void Add_Messsage_Pre_ArcType(UString &s, const char *pre, const wchar_t *arcType)
{
  s.Add_LF();
  s.AddAscii(pre);
  s.AddAscii(" as [");
  s += arcType;
  s.AddAscii("] archive");
}

void Print_ErrorFormatIndex_Warning(CStdOutStream *_so, const CCodecs *codecs, const CArc &arc)
{
  const CArcErrorInfo &er = arc.ErrorInfo;
  
  UString s = L"WARNING:\n";
  s += arc.Path;
  if (arc.FormatIndex == er.ErrorFormatIndex)
  {
    s.Add_LF();
    s.AddAscii("The archive is open with offset");
  }
  else
  {
    Add_Messsage_Pre_ArcType(s, "Can not open the file", codecs->GetFormatNamePtr(er.ErrorFormatIndex));
    Add_Messsage_Pre_ArcType(s, "The file is open", codecs->GetFormatNamePtr(arc.FormatIndex));
  }
  
  *_so << s << endl << endl;
}
        

HRESULT CExtractCallbackConsole::OpenResult(
    const CCodecs *codecs, const CArchiveLink &arcLink,
    const wchar_t *name, HRESULT result)
{
  ClosePercents();

  if (NeedPercents())
  {
    _percent.Files = 0;
    _percent.Command.Empty();
    _percent.FileName.Empty();
  }

 
  ClosePercentsAndFlush();

  FOR_VECTOR (level, arcLink.Arcs)
  {
    const CArc &arc = arcLink.Arcs[level];
    const CArcErrorInfo &er = arc.ErrorInfo;
    
    UInt32 errorFlags = er.GetErrorFlags();

    if (errorFlags != 0 || !er.ErrorMessage.IsEmpty())
    {
      if (_se)
      {
        *_se << endl;
        if (level != 0)
          *_se << arc.Path << endl;
      }
      
      if (errorFlags != 0)
      {
        if (_se)
          PrintErrorFlags(*_se, "ERRORS:", errorFlags);
        NumOpenArcErrors++;
        ThereIsError_in_Current = true;
      }
      
      if (!er.ErrorMessage.IsEmpty())
      {
        if (_se)
          *_se << "ERRORS:" << endl << er.ErrorMessage << endl;
        NumOpenArcErrors++;
        ThereIsError_in_Current = true;
      }
      
      if (_se)
      {
        *_se << endl;
        _se->Flush();
      }
    }
    
    UInt32 warningFlags = er.GetWarningFlags();

    if (warningFlags != 0 || !er.WarningMessage.IsEmpty())
    {
      if (_so)
      {
        *_so << endl;
        if (level != 0)
          *_so << arc.Path << endl;
      }
      
      if (warningFlags != 0)
      {
        if (_so)
          PrintErrorFlags(*_so, "WARNINGS:", warningFlags);
        NumOpenArcWarnings++;
        ThereIsWarning_in_Current = true;
      }
      
      if (!er.WarningMessage.IsEmpty())
      {
        if (_so)
          *_so << "WARNINGS:" << endl << er.WarningMessage << endl;
        NumOpenArcWarnings++;
        ThereIsWarning_in_Current = true;
      }
      
      if (_so)
      {
        *_so << endl;
        if (NeedFlush)
          _so->Flush();
      }
    }

  
    if (er.ErrorFormatIndex >= 0)
    {
      if (_so)
      {
        Print_ErrorFormatIndex_Warning(_so, codecs, arc);
        if (NeedFlush)
          _so->Flush();
      }
      ThereIsWarning_in_Current = true;
    }
  }
      
  if (result == S_OK)
  {
    if (_so)
    {
      RINOK(Print_OpenArchive_Props(*_so, codecs, arcLink));
      *_so << endl;
    }
  }
  else
  {
    NumCantOpenArcs++;
    if (_so)
      _so->Flush();
    if (_se)
    {
      *_se << kError << name << endl;
      HRESULT res = Print_OpenArchive_Error(*_se, codecs, arcLink);
      RINOK(res);
      if (result == S_FALSE)
      {
      }
      else
      {
        if (result == E_OUTOFMEMORY)
          *_se << "Can't allocate required memory";
        else
          *_se << NError::MyFormatMessage(result);
        *_se << endl;
      }
      _se->Flush();
    }
  }
  
  
  return CheckBreak2();
>>>>>>> upstream/master
}
  
HRESULT CExtractCallbackConsole::ThereAreNoFiles()
{
<<<<<<< HEAD
  (*OutStream) << endl << kNoFiles << endl;
  return S_OK;
=======
  ClosePercents_for_so();

  if (_so)
  {
    *_so << endl << kNoFiles << endl;
    if (NeedFlush)
      _so->Flush();
  }
  return CheckBreak2();
>>>>>>> upstream/master
}

HRESULT CExtractCallbackConsole::ExtractResult(HRESULT result)
{
<<<<<<< HEAD
  if (result == S_OK)
  {
    (*OutStream) << endl;
    if (NumFileErrorsInCurrentArchive == 0)
      (*OutStream) << kEverythingIsOk << endl;
    else
    {
      NumArchiveErrors++;
      (*OutStream) << "Sub items Errors: " << NumFileErrorsInCurrentArchive << endl;
    }
  }
  if (result == S_OK)
    return result;
  NumArchiveErrors++;
  if (result == E_ABORT || result == ERROR_DISK_FULL)
    return result;
  (*OutStream) << endl << kError;
  if (result == E_OUTOFMEMORY)
    (*OutStream) << kMemoryExceptionMessage;
  else
    (*OutStream) << NError::MyFormatMessageW(result);
  (*OutStream) << endl;
  return S_OK;
=======
  MT_LOCK
  
  if (NeedPercents())
  {
    _percent.ClosePrint(true);
    _percent.Command.Empty();
    _percent.FileName.Empty();
  }

  if (_so)
    _so->Flush();

  if (result == S_OK)
  {
    if (NumFileErrors_in_Current == 0 && !ThereIsError_in_Current)
    {
      if (ThereIsWarning_in_Current)
        NumArcsWithWarnings++;
      else
        NumOkArcs++;
      if (_so)
        *_so << kEverythingIsOk << endl;
    }
    else
    {
      NumArcsWithError++;
      if (_so)
      {
        *_so << endl;
        if (NumFileErrors_in_Current != 0)
          *_so << "Sub items Errors: " << NumFileErrors_in_Current << endl;
      }
    }
    if (_so && NeedFlush)
      _so->Flush();
  }
  else
  {
    NumArcsWithError++;
    if (result == E_ABORT || result == ERROR_DISK_FULL)
      return result;
    
    if (_se)
    {
      *_se << endl << kError;
      if (result == E_OUTOFMEMORY)
        *_se << kMemoryExceptionMessage;
      else
        *_se << NError::MyFormatMessage(result);
      *_se << endl;
      _se->Flush();
    }
  }

  return CheckBreak2();
>>>>>>> upstream/master
}
