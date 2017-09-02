// Client7z.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include "Common/IntToString.h"
#include "Common/MyInitGuid.h"
#include "Common/StringConvert.h"

#include "Windows/DLL.h"
#include "Windows/FileDir.h"
#include "Windows/FileFind.h"
#include "Windows/FileName.h"
#include "Windows/NtCheck.h"
#include "Windows/PropVariant.h"
#include "Windows/PropVariantConversions.h"
=======
#include <stdio.h>

#include "../../../Common/MyWindows.h"

#include "../../../Common/Defs.h"
#include "../../../Common/MyInitGuid.h"

#include "../../../Common/IntToString.h"
#include "../../../Common/StringConvert.h"

#include "../../../Windows/DLL.h"
#include "../../../Windows/FileDir.h"
#include "../../../Windows/FileFind.h"
#include "../../../Windows/FileName.h"
#include "../../../Windows/NtCheck.h"
#include "../../../Windows/PropVariant.h"
#include "../../../Windows/PropVariantConv.h"
>>>>>>> upstream/master

#include "../../Common/FileStreams.h"

#include "../../Archive/IArchive.h"

#include "../../IPassword.h"
<<<<<<< HEAD
#include "../../MyVersion.h"
=======
#include "../../../../C/7zVersion.h"
>>>>>>> upstream/master

#ifdef _WIN32
HINSTANCE g_hInstance = 0;
#endif

<<<<<<< HEAD
// use another CLSIDs, if you want to support other formats (zip, rar, ...).
// {23170F69-40C1-278A-1000-000110070000}
DEFINE_GUID(CLSID_CFormat7z,
  0x23170F69, 0x40C1, 0x278A, 0x10, 0x00, 0x00, 0x01, 0x10, 0x07, 0x00, 0x00);

using namespace NWindows;

#define kDllName "7z.dll"

static const char *kCopyrightString = "\n" MY_7ZIP_VERSION
=======
// Tou can find the list of all GUIDs in Guid.txt file.
// use another CLSIDs, if you want to support other formats (zip, rar, ...).
// {23170F69-40C1-278A-1000-000110070000}

DEFINE_GUID(CLSID_CFormat7z,
  0x23170F69, 0x40C1, 0x278A, 0x10, 0x00, 0x00, 0x01, 0x10, 0x07, 0x00, 0x00);
DEFINE_GUID(CLSID_CFormatXz,
  0x23170F69, 0x40C1, 0x278A, 0x10, 0x00, 0x00, 0x01, 0x10, 0x0C, 0x00, 0x00);

#define CLSID_Format CLSID_CFormat7z
// #define CLSID_Format CLSID_CFormatXz

using namespace NWindows;
using namespace NFile;
using namespace NDir;

#define kDllName "7z.dll"

static const char *kCopyrightString = "\n7-Zip " MY_VERSION
>>>>>>> upstream/master
" ("  kDllName " client) "
MY_COPYRIGHT " " MY_DATE "\n";

static const char *kHelpString =
"Usage: Client7z.exe [a | l | x ] archive.7z [fileName ...]\n"
"Examples:\n"
"  Client7z.exe a archive.7z f1.txt f2.txt  : compress two files to archive.7z\n"
"  Client7z.exe l archive.7z   : List contents of archive.7z\n"
"  Client7z.exe x archive.7z   : eXtract files from archive.7z\n";


<<<<<<< HEAD
typedef UINT32 (WINAPI * CreateObjectFunc)(
    const GUID *clsID,
    const GUID *interfaceID,
    void **outObject);


=======
>>>>>>> upstream/master
static AString FStringToConsoleString(const FString &s)
{
  return GetOemString(fs2us(s));
}

static FString CmdStringToFString(const char *s)
{
  return us2fs(GetUnicodeString(s));
}

static void PrintString(const UString &s)
{
  printf("%s", (LPCSTR)GetOemString(s));
}

static void PrintString(const AString &s)
{
  printf("%s", (LPCSTR)s);
}

static void PrintNewLine()
{
  PrintString("\n");
}

static void PrintStringLn(const AString &s)
{
  PrintString(s);
  PrintNewLine();
}

static void PrintError(const char *message, const FString &name)
{
  printf("Error: %s", (LPCSTR)message);
  PrintNewLine();
  PrintString(FStringToConsoleString(name));
  PrintNewLine();
}

static void PrintError(const AString &s)
{
  PrintNewLine();
  PrintString(s);
  PrintNewLine();
}

static HRESULT IsArchiveItemProp(IInArchive *archive, UInt32 index, PROPID propID, bool &result)
{
  NCOM::CPropVariant prop;
  RINOK(archive->GetProperty(index, propID, &prop));
  if (prop.vt == VT_BOOL)
    result = VARIANT_BOOLToBool(prop.boolVal);
  else if (prop.vt == VT_EMPTY)
    result = false;
  else
    return E_FAIL;
  return S_OK;
}

static HRESULT IsArchiveItemFolder(IInArchive *archive, UInt32 index, bool &result)
{
  return IsArchiveItemProp(archive, index, kpidIsDir, result);
}


static const wchar_t *kEmptyFileAlias = L"[Content]";


//////////////////////////////////////////////////////////////
// Archive Open callback class


class CArchiveOpenCallback:
  public IArchiveOpenCallback,
  public ICryptoGetTextPassword,
  public CMyUnknownImp
{
public:
  MY_UNKNOWN_IMP1(ICryptoGetTextPassword)

  STDMETHOD(SetTotal)(const UInt64 *files, const UInt64 *bytes);
  STDMETHOD(SetCompleted)(const UInt64 *files, const UInt64 *bytes);

  STDMETHOD(CryptoGetTextPassword)(BSTR *password);

  bool PasswordIsDefined;
  UString Password;

  CArchiveOpenCallback() : PasswordIsDefined(false) {}
};

STDMETHODIMP CArchiveOpenCallback::SetTotal(const UInt64 * /* files */, const UInt64 * /* bytes */)
{
  return S_OK;
}

STDMETHODIMP CArchiveOpenCallback::SetCompleted(const UInt64 * /* files */, const UInt64 * /* bytes */)
{
  return S_OK;
}
  
STDMETHODIMP CArchiveOpenCallback::CryptoGetTextPassword(BSTR *password)
{
  if (!PasswordIsDefined)
  {
    // You can ask real password here from user
    // Password = GetPassword(OutStream);
    // PasswordIsDefined = true;
    PrintError("Password is not defined");
    return E_ABORT;
  }
  return StringToBstr(Password, password);
}


//////////////////////////////////////////////////////////////
// Archive Extracting callback class

static const char *kTestingString    =  "Testing     ";
static const char *kExtractingString =  "Extracting  ";
static const char *kSkippingString   =  "Skipping    ";

static const char *kUnsupportedMethod = "Unsupported Method";
static const char *kCRCFailed = "CRC Failed";
static const char *kDataError = "Data Error";
<<<<<<< HEAD
static const char *kUnknownError = "Unknown Error";
=======
static const char *kUnavailableData = "Unavailable data";
static const char *kUnexpectedEnd = "Unexpected end of data";
static const char *kDataAfterEnd = "There are some data after the end of the payload data";
static const char *kIsNotArc = "Is not archive";
static const char *kHeadersError = "Headers Error";
>>>>>>> upstream/master

class CArchiveExtractCallback:
  public IArchiveExtractCallback,
  public ICryptoGetTextPassword,
  public CMyUnknownImp
{
public:
  MY_UNKNOWN_IMP1(ICryptoGetTextPassword)

  // IProgress
  STDMETHOD(SetTotal)(UInt64 size);
  STDMETHOD(SetCompleted)(const UInt64 *completeValue);

  // IArchiveExtractCallback
  STDMETHOD(GetStream)(UInt32 index, ISequentialOutStream **outStream, Int32 askExtractMode);
  STDMETHOD(PrepareOperation)(Int32 askExtractMode);
  STDMETHOD(SetOperationResult)(Int32 resultEOperationResult);

  // ICryptoGetTextPassword
  STDMETHOD(CryptoGetTextPassword)(BSTR *aPassword);

private:
  CMyComPtr<IInArchive> _archiveHandler;
  FString _directoryPath;  // Output directory
  UString _filePath;       // name inside arcvhive
  FString _diskFilePath;   // full path to file on disk
  bool _extractMode;
  struct CProcessedFileInfo
  {
    FILETIME MTime;
    UInt32 Attrib;
    bool isDir;
    bool AttribDefined;
    bool MTimeDefined;
  } _processedFileInfo;

  COutFileStream *_outFileStreamSpec;
  CMyComPtr<ISequentialOutStream> _outFileStream;

public:
  void Init(IInArchive *archiveHandler, const FString &directoryPath);

  UInt64 NumErrors;
  bool PasswordIsDefined;
  UString Password;

  CArchiveExtractCallback() : PasswordIsDefined(false) {}
};

void CArchiveExtractCallback::Init(IInArchive *archiveHandler, const FString &directoryPath)
{
  NumErrors = 0;
  _archiveHandler = archiveHandler;
  _directoryPath = directoryPath;
<<<<<<< HEAD
  NFile::NName::NormalizeDirPathPrefix(_directoryPath);
=======
  NName::NormalizeDirPathPrefix(_directoryPath);
>>>>>>> upstream/master
}

STDMETHODIMP CArchiveExtractCallback::SetTotal(UInt64 /* size */)
{
  return S_OK;
}

STDMETHODIMP CArchiveExtractCallback::SetCompleted(const UInt64 * /* completeValue */)
{
  return S_OK;
}

STDMETHODIMP CArchiveExtractCallback::GetStream(UInt32 index,
    ISequentialOutStream **outStream, Int32 askExtractMode)
{
  *outStream = 0;
  _outFileStream.Release();

  {
    // Get Name
    NCOM::CPropVariant prop;
    RINOK(_archiveHandler->GetProperty(index, kpidPath, &prop));
    
    UString fullPath;
    if (prop.vt == VT_EMPTY)
      fullPath = kEmptyFileAlias;
    else
    {
      if (prop.vt != VT_BSTR)
        return E_FAIL;
      fullPath = prop.bstrVal;
    }
    _filePath = fullPath;
  }

  if (askExtractMode != NArchive::NExtract::NAskMode::kExtract)
    return S_OK;

  {
    // Get Attrib
    NCOM::CPropVariant prop;
    RINOK(_archiveHandler->GetProperty(index, kpidAttrib, &prop));
    if (prop.vt == VT_EMPTY)
    {
      _processedFileInfo.Attrib = 0;
      _processedFileInfo.AttribDefined = false;
    }
    else
    {
      if (prop.vt != VT_UI4)
        return E_FAIL;
      _processedFileInfo.Attrib = prop.ulVal;
      _processedFileInfo.AttribDefined = true;
    }
  }

  RINOK(IsArchiveItemFolder(_archiveHandler, index, _processedFileInfo.isDir));

  {
    // Get Modified Time
    NCOM::CPropVariant prop;
    RINOK(_archiveHandler->GetProperty(index, kpidMTime, &prop));
    _processedFileInfo.MTimeDefined = false;
<<<<<<< HEAD
    switch(prop.vt)
=======
    switch (prop.vt)
>>>>>>> upstream/master
    {
      case VT_EMPTY:
        // _processedFileInfo.MTime = _utcMTimeDefault;
        break;
      case VT_FILETIME:
        _processedFileInfo.MTime = prop.filetime;
        _processedFileInfo.MTimeDefined = true;
        break;
      default:
        return E_FAIL;
    }

  }
  {
    // Get Size
    NCOM::CPropVariant prop;
    RINOK(_archiveHandler->GetProperty(index, kpidSize, &prop));
<<<<<<< HEAD
    bool newFileSizeDefined = (prop.vt != VT_EMPTY);
    UInt64 newFileSize;
    if (newFileSizeDefined)
      newFileSize = ConvertPropVariantToUInt64(prop);
=======
    UInt64 newFileSize;
    /* bool newFileSizeDefined = */ ConvertPropVariantToUInt64(prop, newFileSize);
>>>>>>> upstream/master
  }

  
  {
    // Create folders for file
<<<<<<< HEAD
    int slashPos = _filePath.ReverseFind(WCHAR_PATH_SEPARATOR);
    if (slashPos >= 0)
      NFile::NDirectory::CreateComplexDirectory(_directoryPath + us2fs(_filePath.Left(slashPos)));
=======
    int slashPos = _filePath.ReverseFind_PathSepar();
    if (slashPos >= 0)
      CreateComplexDir(_directoryPath + us2fs(_filePath.Left(slashPos)));
>>>>>>> upstream/master
  }

  FString fullProcessedPath = _directoryPath + us2fs(_filePath);
  _diskFilePath = fullProcessedPath;

  if (_processedFileInfo.isDir)
  {
<<<<<<< HEAD
    NFile::NDirectory::CreateComplexDirectory(fullProcessedPath);
  }
  else
  {
    NFile::NFind::CFileInfo fi;
    if (fi.Find(fullProcessedPath))
    {
      if (!NFile::NDirectory::DeleteFileAlways(fullProcessedPath))
=======
    CreateComplexDir(fullProcessedPath);
  }
  else
  {
    NFind::CFileInfo fi;
    if (fi.Find(fullProcessedPath))
    {
      if (!DeleteFileAlways(fullProcessedPath))
>>>>>>> upstream/master
      {
        PrintError("Can not delete output file", fullProcessedPath);
        return E_ABORT;
      }
    }
    
    _outFileStreamSpec = new COutFileStream;
    CMyComPtr<ISequentialOutStream> outStreamLoc(_outFileStreamSpec);
    if (!_outFileStreamSpec->Open(fullProcessedPath, CREATE_ALWAYS))
    {
      PrintError("Can not open output file", fullProcessedPath);
      return E_ABORT;
    }
    _outFileStream = outStreamLoc;
    *outStream = outStreamLoc.Detach();
  }
  return S_OK;
}

STDMETHODIMP CArchiveExtractCallback::PrepareOperation(Int32 askExtractMode)
{
  _extractMode = false;
  switch (askExtractMode)
  {
    case NArchive::NExtract::NAskMode::kExtract:  _extractMode = true; break;
  };
  switch (askExtractMode)
  {
    case NArchive::NExtract::NAskMode::kExtract:  PrintString(kExtractingString); break;
    case NArchive::NExtract::NAskMode::kTest:  PrintString(kTestingString); break;
    case NArchive::NExtract::NAskMode::kSkip:  PrintString(kSkippingString); break;
  };
  PrintString(_filePath);
  return S_OK;
}

STDMETHODIMP CArchiveExtractCallback::SetOperationResult(Int32 operationResult)
{
<<<<<<< HEAD
  switch(operationResult)
=======
  switch (operationResult)
>>>>>>> upstream/master
  {
    case NArchive::NExtract::NOperationResult::kOK:
      break;
    default:
    {
      NumErrors++;
<<<<<<< HEAD
      PrintString("     ");
      switch(operationResult)
      {
        case NArchive::NExtract::NOperationResult::kUnSupportedMethod:
          PrintString(kUnsupportedMethod);
          break;
        case NArchive::NExtract::NOperationResult::kCRCError:
          PrintString(kCRCFailed);
          break;
        case NArchive::NExtract::NOperationResult::kDataError:
          PrintString(kDataError);
          break;
        default:
          PrintString(kUnknownError);
=======
      PrintString("  :  ");
      const char *s = NULL;
      switch (operationResult)
      {
        case NArchive::NExtract::NOperationResult::kUnsupportedMethod:
          s = kUnsupportedMethod;
          break;
        case NArchive::NExtract::NOperationResult::kCRCError:
          s = kCRCFailed;
          break;
        case NArchive::NExtract::NOperationResult::kDataError:
          s = kDataError;
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
      }
      if (s)
      {
        PrintString("Error : ");
        PrintString(s);
      }
      else
      {
        char temp[16];
        ConvertUInt32ToString(operationResult, temp);
        PrintString("Error #");
        PrintString(temp);
>>>>>>> upstream/master
      }
    }
  }

<<<<<<< HEAD
  if (_outFileStream != NULL)
=======
  if (_outFileStream)
>>>>>>> upstream/master
  {
    if (_processedFileInfo.MTimeDefined)
      _outFileStreamSpec->SetMTime(&_processedFileInfo.MTime);
    RINOK(_outFileStreamSpec->Close());
  }
  _outFileStream.Release();
  if (_extractMode && _processedFileInfo.AttribDefined)
<<<<<<< HEAD
    NFile::NDirectory::MySetFileAttributes(_diskFilePath, _processedFileInfo.Attrib);
=======
    SetFileAttrib(_diskFilePath, _processedFileInfo.Attrib);
>>>>>>> upstream/master
  PrintNewLine();
  return S_OK;
}


STDMETHODIMP CArchiveExtractCallback::CryptoGetTextPassword(BSTR *password)
{
  if (!PasswordIsDefined)
  {
    // You can ask real password here from user
    // Password = GetPassword(OutStream);
    // PasswordIsDefined = true;
    PrintError("Password is not defined");
    return E_ABORT;
  }
  return StringToBstr(Password, password);
}



//////////////////////////////////////////////////////////////
// Archive Creating callback class

struct CDirItem
{
  UInt64 Size;
  FILETIME CTime;
  FILETIME ATime;
  FILETIME MTime;
  UString Name;
  FString FullPath;
  UInt32 Attrib;

  bool isDir() const { return (Attrib & FILE_ATTRIBUTE_DIRECTORY) != 0 ; }
};

class CArchiveUpdateCallback:
  public IArchiveUpdateCallback2,
  public ICryptoGetTextPassword2,
  public CMyUnknownImp
{
public:
  MY_UNKNOWN_IMP2(IArchiveUpdateCallback2, ICryptoGetTextPassword2)

  // IProgress
  STDMETHOD(SetTotal)(UInt64 size);
  STDMETHOD(SetCompleted)(const UInt64 *completeValue);

  // IUpdateCallback2
<<<<<<< HEAD
  STDMETHOD(EnumProperties)(IEnumSTATPROPSTG **enumerator);
=======
>>>>>>> upstream/master
  STDMETHOD(GetUpdateItemInfo)(UInt32 index,
      Int32 *newData, Int32 *newProperties, UInt32 *indexInArchive);
  STDMETHOD(GetProperty)(UInt32 index, PROPID propID, PROPVARIANT *value);
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **inStream);
  STDMETHOD(SetOperationResult)(Int32 operationResult);
  STDMETHOD(GetVolumeSize)(UInt32 index, UInt64 *size);
  STDMETHOD(GetVolumeStream)(UInt32 index, ISequentialOutStream **volumeStream);

  STDMETHOD(CryptoGetTextPassword2)(Int32 *passwordIsDefined, BSTR *password);

public:
  CRecordVector<UInt64> VolumesSizes;
  UString VolName;
  UString VolExt;

  FString DirPrefix;
  const CObjectVector<CDirItem> *DirItems;

  bool PasswordIsDefined;
  UString Password;
  bool AskPassword;

  bool m_NeedBeClosed;

  FStringVector FailedFiles;
  CRecordVector<HRESULT> FailedCodes;

  CArchiveUpdateCallback(): PasswordIsDefined(false), AskPassword(false), DirItems(0) {};

  ~CArchiveUpdateCallback() { Finilize(); }
  HRESULT Finilize();

  void Init(const CObjectVector<CDirItem> *dirItems)
  {
    DirItems = dirItems;
    m_NeedBeClosed = false;
    FailedFiles.Clear();
    FailedCodes.Clear();
  }
};

STDMETHODIMP CArchiveUpdateCallback::SetTotal(UInt64 /* size */)
{
  return S_OK;
}

STDMETHODIMP CArchiveUpdateCallback::SetCompleted(const UInt64 * /* completeValue */)
{
  return S_OK;
}

<<<<<<< HEAD

STDMETHODIMP CArchiveUpdateCallback::EnumProperties(IEnumSTATPROPSTG ** /* enumerator */)
{
  return E_NOTIMPL;
}

STDMETHODIMP CArchiveUpdateCallback::GetUpdateItemInfo(UInt32 /* index */,
      Int32 *newData, Int32 *newProperties, UInt32 *indexInArchive)
{
  if (newData != NULL)
    *newData = BoolToInt(true);
  if (newProperties != NULL)
    *newProperties = BoolToInt(true);
  if (indexInArchive != NULL)
    *indexInArchive = (UInt32)-1;
=======
STDMETHODIMP CArchiveUpdateCallback::GetUpdateItemInfo(UInt32 /* index */,
      Int32 *newData, Int32 *newProperties, UInt32 *indexInArchive)
{
  if (newData)
    *newData = BoolToInt(true);
  if (newProperties)
    *newProperties = BoolToInt(true);
  if (indexInArchive)
    *indexInArchive = (UInt32)(Int32)-1;
>>>>>>> upstream/master
  return S_OK;
}

STDMETHODIMP CArchiveUpdateCallback::GetProperty(UInt32 index, PROPID propID, PROPVARIANT *value)
{
  NCOM::CPropVariant prop;
  
  if (propID == kpidIsAnti)
  {
    prop = false;
    prop.Detach(value);
    return S_OK;
  }

  {
    const CDirItem &dirItem = (*DirItems)[index];
<<<<<<< HEAD
    switch(propID)
=======
    switch (propID)
>>>>>>> upstream/master
    {
      case kpidPath:  prop = dirItem.Name; break;
      case kpidIsDir:  prop = dirItem.isDir(); break;
      case kpidSize:  prop = dirItem.Size; break;
      case kpidAttrib:  prop = dirItem.Attrib; break;
      case kpidCTime:  prop = dirItem.CTime; break;
      case kpidATime:  prop = dirItem.ATime; break;
      case kpidMTime:  prop = dirItem.MTime; break;
    }
  }
  prop.Detach(value);
  return S_OK;
}

HRESULT CArchiveUpdateCallback::Finilize()
{
  if (m_NeedBeClosed)
  {
    PrintNewLine();
    m_NeedBeClosed = false;
  }
  return S_OK;
}

static void GetStream2(const wchar_t *name)
{
  PrintString("Compressing  ");
  if (name[0] == 0)
    name = kEmptyFileAlias;
  PrintString(name);
}

STDMETHODIMP CArchiveUpdateCallback::GetStream(UInt32 index, ISequentialInStream **inStream)
{
  RINOK(Finilize());

  const CDirItem &dirItem = (*DirItems)[index];
  GetStream2(dirItem.Name);
 
  if (dirItem.isDir())
    return S_OK;

  {
    CInFileStream *inStreamSpec = new CInFileStream;
    CMyComPtr<ISequentialInStream> inStreamLoc(inStreamSpec);
    FString path = DirPrefix + dirItem.FullPath;
    if (!inStreamSpec->Open(path))
    {
      DWORD sysError = ::GetLastError();
      FailedCodes.Add(sysError);
      FailedFiles.Add(path);
      // if (systemError == ERROR_SHARING_VIOLATION)
      {
        PrintNewLine();
        PrintError("WARNING: can't open file");
        // PrintString(NError::MyFormatMessageW(systemError));
        return S_FALSE;
      }
      // return sysError;
    }
    *inStream = inStreamLoc.Detach();
  }
  return S_OK;
}

STDMETHODIMP CArchiveUpdateCallback::SetOperationResult(Int32 /* operationResult */)
{
  m_NeedBeClosed = true;
  return S_OK;
}

STDMETHODIMP CArchiveUpdateCallback::GetVolumeSize(UInt32 index, UInt64 *size)
{
  if (VolumesSizes.Size() == 0)
    return S_FALSE;
  if (index >= (UInt32)VolumesSizes.Size())
    index = VolumesSizes.Size() - 1;
  *size = VolumesSizes[index];
  return S_OK;
}

STDMETHODIMP CArchiveUpdateCallback::GetVolumeStream(UInt32 index, ISequentialOutStream **volumeStream)
{
  wchar_t temp[16];
  ConvertUInt32ToString(index + 1, temp);
  UString res = temp;
<<<<<<< HEAD
  while (res.Length() < 2)
    res = UString(L'0') + res;
=======
  while (res.Len() < 2)
    res.InsertAtFront(L'0');
>>>>>>> upstream/master
  UString fileName = VolName;
  fileName += L'.';
  fileName += res;
  fileName += VolExt;
  COutFileStream *streamSpec = new COutFileStream;
  CMyComPtr<ISequentialOutStream> streamLoc(streamSpec);
  if (!streamSpec->Create(us2fs(fileName), false))
    return ::GetLastError();
  *volumeStream = streamLoc.Detach();
  return S_OK;
}

STDMETHODIMP CArchiveUpdateCallback::CryptoGetTextPassword2(Int32 *passwordIsDefined, BSTR *password)
{
  if (!PasswordIsDefined)
  {
    if (AskPassword)
    {
      // You can ask real password here from user
      // Password = GetPassword(OutStream);
      // PasswordIsDefined = true;
      PrintError("Password is not defined");
      return E_ABORT;
    }
  }
  *passwordIsDefined = BoolToInt(PasswordIsDefined);
  return StringToBstr(Password, password);
}

<<<<<<< HEAD
//////////////////////////////////////////////////////////////////////////
=======

>>>>>>> upstream/master
// Main function

#define NT_CHECK_FAIL_ACTION PrintError("Unsupported Windows version"); return 1;

int MY_CDECL main(int numArgs, const char *args[])
{
  NT_CHECK

  PrintStringLn(kCopyrightString);

  if (numArgs < 3)
  {
    PrintStringLn(kHelpString);
    return 1;
  }
<<<<<<< HEAD
=======
  
>>>>>>> upstream/master
  NDLL::CLibrary lib;
  if (!lib.Load(NDLL::GetModuleDirPrefix() + FTEXT(kDllName)))
  {
    PrintError("Can not load 7-zip library");
    return 1;
  }
<<<<<<< HEAD
  CreateObjectFunc createObjectFunc = (CreateObjectFunc)lib.GetProc("CreateObject");
  if (createObjectFunc == 0)
=======

  Func_CreateObject createObjectFunc = (Func_CreateObject)lib.GetProc("CreateObject");
  if (!createObjectFunc)
>>>>>>> upstream/master
  {
    PrintError("Can not get CreateObject");
    return 1;
  }

  char c;
  {
    AString command = args[1];
<<<<<<< HEAD
    if (command.Length() != 1)
=======
    if (command.Len() != 1)
>>>>>>> upstream/master
    {
      PrintError("incorrect command");
      return 1;
    }
<<<<<<< HEAD
    c = (char)MyCharUpper(command[0]);
  }
  FString archiveName = CmdStringToFString(args[2]);
  if (c == 'A')
=======
    c = (char)MyCharLower_Ascii(command[0]);
  }

  FString archiveName = CmdStringToFString(args[2]);
  
  if (c == 'a')
>>>>>>> upstream/master
  {
    // create archive command
    if (numArgs < 4)
    {
      PrintStringLn(kHelpString);
      return 1;
    }
    CObjectVector<CDirItem> dirItems;
<<<<<<< HEAD
    int i;
    for (i = 3; i < numArgs; i++)
    {
      CDirItem di;
      FString name = CmdStringToFString(args[i]);
      
      NFile::NFind::CFileInfo fi;
      if (!fi.Find(name))
      {
        PrintError("Can't find file", name);
        return 1;
      }

      di.Attrib = fi.Attrib;
      di.Size = fi.Size;
      di.CTime = fi.CTime;
      di.ATime = fi.ATime;
      di.MTime = fi.MTime;
      di.Name = fs2us(name);
      di.FullPath = name;
      dirItems.Add(di);
    }
=======
    {
      int i;
      for (i = 3; i < numArgs; i++)
      {
        CDirItem di;
        FString name = CmdStringToFString(args[i]);
        
        NFind::CFileInfo fi;
        if (!fi.Find(name))
        {
          PrintError("Can't find file", name);
          return 1;
        }
        
        di.Attrib = fi.Attrib;
        di.Size = fi.Size;
        di.CTime = fi.CTime;
        di.ATime = fi.ATime;
        di.MTime = fi.MTime;
        di.Name = fs2us(name);
        di.FullPath = name;
        dirItems.Add(di);
      }
    }

>>>>>>> upstream/master
    COutFileStream *outFileStreamSpec = new COutFileStream;
    CMyComPtr<IOutStream> outFileStream = outFileStreamSpec;
    if (!outFileStreamSpec->Create(archiveName, false))
    {
      PrintError("can't create archive file");
      return 1;
    }

    CMyComPtr<IOutArchive> outArchive;
<<<<<<< HEAD
    if (createObjectFunc(&CLSID_CFormat7z, &IID_IOutArchive, (void **)&outArchive) != S_OK)
=======
    if (createObjectFunc(&CLSID_Format, &IID_IOutArchive, (void **)&outArchive) != S_OK)
>>>>>>> upstream/master
    {
      PrintError("Can not get class object");
      return 1;
    }

    CArchiveUpdateCallback *updateCallbackSpec = new CArchiveUpdateCallback;
    CMyComPtr<IArchiveUpdateCallback2> updateCallback(updateCallbackSpec);
    updateCallbackSpec->Init(&dirItems);
    // updateCallbackSpec->PasswordIsDefined = true;
    // updateCallbackSpec->Password = L"1";

    /*
    {
      const wchar_t *names[] =
      {
        L"s",
        L"x"
      };
<<<<<<< HEAD
      const int kNumProps = sizeof(names) / sizeof(names[0]);
=======
      const unsigned kNumProps = ARRAY_SIZE(names);
>>>>>>> upstream/master
      NCOM::CPropVariant values[kNumProps] =
      {
        false,    // solid mode OFF
        (UInt32)9 // compression level = 9 - ultra
      };
      CMyComPtr<ISetProperties> setProperties;
      outArchive->QueryInterface(IID_ISetProperties, (void **)&setProperties);
      if (!setProperties)
      {
        PrintError("ISetProperties unsupported");
        return 1;
      }
      RINOK(setProperties->SetProperties(names, values, kNumProps));
    }
    */
    
    HRESULT result = outArchive->UpdateItems(outFileStream, dirItems.Size(), updateCallback);
<<<<<<< HEAD
    updateCallbackSpec->Finilize();
=======
    
    updateCallbackSpec->Finilize();
    
>>>>>>> upstream/master
    if (result != S_OK)
    {
      PrintError("Update Error");
      return 1;
    }
<<<<<<< HEAD
    for (i = 0; i < updateCallbackSpec->FailedFiles.Size(); i++)
=======
    
    FOR_VECTOR (i, updateCallbackSpec->FailedFiles)
>>>>>>> upstream/master
    {
      PrintNewLine();
      PrintError("Error for file", updateCallbackSpec->FailedFiles[i]);
    }
<<<<<<< HEAD
=======
    
>>>>>>> upstream/master
    if (updateCallbackSpec->FailedFiles.Size() != 0)
      return 1;
  }
  else
  {
    if (numArgs != 3)
    {
      PrintStringLn(kHelpString);
      return 1;
    }

    bool listCommand;
<<<<<<< HEAD
    if (c == 'L')
      listCommand = true;
    else if (c == 'X')
=======
    
    if (c == 'l')
      listCommand = true;
    else if (c == 'x')
>>>>>>> upstream/master
      listCommand = false;
    else
    {
      PrintError("incorrect command");
      return 1;
    }
  
    CMyComPtr<IInArchive> archive;
<<<<<<< HEAD
    if (createObjectFunc(&CLSID_CFormat7z, &IID_IInArchive, (void **)&archive) != S_OK)
=======
    if (createObjectFunc(&CLSID_Format, &IID_IInArchive, (void **)&archive) != S_OK)
>>>>>>> upstream/master
    {
      PrintError("Can not get class object");
      return 1;
    }
    
    CInFileStream *fileSpec = new CInFileStream;
    CMyComPtr<IInStream> file = fileSpec;
    
    if (!fileSpec->Open(archiveName))
    {
      PrintError("Can not open archive file", archiveName);
      return 1;
    }

    {
      CArchiveOpenCallback *openCallbackSpec = new CArchiveOpenCallback;
      CMyComPtr<IArchiveOpenCallback> openCallback(openCallbackSpec);
      openCallbackSpec->PasswordIsDefined = false;
      // openCallbackSpec->PasswordIsDefined = true;
      // openCallbackSpec->Password = L"1";
      
<<<<<<< HEAD
      if (archive->Open(file, 0, openCallback) != S_OK)
=======
      const UInt64 scanSize = 1 << 23;
      if (archive->Open(file, &scanSize, openCallback) != S_OK)
>>>>>>> upstream/master
      {
        PrintError("Can not open file as archive", archiveName);
        return 1;
      }
    }
    
    if (listCommand)
    {
      // List command
      UInt32 numItems = 0;
      archive->GetNumberOfItems(&numItems);
      for (UInt32 i = 0; i < numItems; i++)
      {
        {
          // Get uncompressed size of file
          NCOM::CPropVariant prop;
          archive->GetProperty(i, kpidSize, &prop);
<<<<<<< HEAD
          UString s = ConvertPropVariantToString(prop);
=======
          char s[32];
          ConvertPropVariantToShortString(prop, s);
>>>>>>> upstream/master
          PrintString(s);
          PrintString("  ");
        }
        {
          // Get name of file
          NCOM::CPropVariant prop;
          archive->GetProperty(i, kpidPath, &prop);
<<<<<<< HEAD
          UString s = ConvertPropVariantToString(prop);
          PrintString(s);
=======
          if (prop.vt == VT_BSTR)
            PrintString(prop.bstrVal);
          else if (prop.vt != VT_EMPTY)
            PrintString("ERROR!");
>>>>>>> upstream/master
        }
        PrintNewLine();
      }
    }
    else
    {
      // Extract command
      CArchiveExtractCallback *extractCallbackSpec = new CArchiveExtractCallback;
      CMyComPtr<IArchiveExtractCallback> extractCallback(extractCallbackSpec);
      extractCallbackSpec->Init(archive, FTEXT("")); // second parameter is output folder path
      extractCallbackSpec->PasswordIsDefined = false;
      // extractCallbackSpec->PasswordIsDefined = true;
      // extractCallbackSpec->Password = L"1";
<<<<<<< HEAD
      HRESULT result = archive->Extract(NULL, (UInt32)(Int32)(-1), false, extractCallback);
=======

      /*
      const wchar_t *names[] =
      {
        L"mt",
        L"mtf"
      };
      const unsigned kNumProps = sizeof(names) / sizeof(names[0]);
      NCOM::CPropVariant values[kNumProps] =
      {
        (UInt32)1,
        false
      };
      CMyComPtr<ISetProperties> setProperties;
      archive->QueryInterface(IID_ISetProperties, (void **)&setProperties);
      if (setProperties)
        setProperties->SetProperties(names, values, kNumProps);
      */

      HRESULT result = archive->Extract(NULL, (UInt32)(Int32)(-1), false, extractCallback);
  
>>>>>>> upstream/master
      if (result != S_OK)
      {
        PrintError("Extract Error");
        return 1;
      }
    }
  }
<<<<<<< HEAD
=======

>>>>>>> upstream/master
  return 0;
}
