// Update.h

#ifndef __COMMON_UPDATE_H
#define __COMMON_UPDATE_H

<<<<<<< HEAD
#include "Common/Wildcard.h"

#include "ArchiveOpenCallback.h"
#include "LoadCodecs.h"
=======
#include "../../../Common/Wildcard.h"

#include "ArchiveOpenCallback.h"
#include "LoadCodecs.h"
#include "OpenArchive.h"
>>>>>>> upstream/master
#include "Property.h"
#include "UpdateAction.h"
#include "UpdateCallback.h"

<<<<<<< HEAD
=======
#include "DirItem.h"

enum EArcNameMode
{
  k_ArcNameMode_Smart,
  k_ArcNameMode_Exact,
  k_ArcNameMode_Add,
};

>>>>>>> upstream/master
struct CArchivePath
{
  UString OriginalPath;

  UString Prefix;   // path(folder) prefix including slash
  UString Name; // base name
  UString BaseExtension; // archive type extension or "exe" extension
  UString VolExtension;  // archive type extension for volumes

  bool Temp;
  FString TempPrefix;  // path(folder) for temp location
  FString TempPostfix;

  CArchivePath(): Temp(false) {};
  
<<<<<<< HEAD
  void ParseFromPath(const UString &path)
  {
    OriginalPath = path;

    SplitPathToParts(path, Prefix, Name);
    int dotPos = Name.ReverseFind(L'.');
    if (dotPos < 0)
      return;
    if (dotPos == Name.Length() - 1)
    {
      Name = Name.Left(dotPos);
      BaseExtension.Empty();
      return;
    }
    if (BaseExtension.CompareNoCase(Name.Mid(dotPos + 1)) == 0)
    {
      BaseExtension = Name.Mid(dotPos + 1);
      Name = Name.Left(dotPos);
    }
    else
      BaseExtension.Empty();
  }

  UString GetPathWithoutExt() const
  {
    return Prefix + Name;
  }

  UString GetFinalPath() const
  {
    UString path = GetPathWithoutExt();
    if (!BaseExtension.IsEmpty())
      path += UString(L'.') + BaseExtension;
    return path;
  }

  
  FString GetTempPath() const
  {
    FString path = TempPrefix + us2fs(Name);
    if (!BaseExtension.IsEmpty())
      path += FString(FTEXT('.')) + us2fs(BaseExtension);
    path += FTEXT(".tmp");
    path += TempPostfix;
    return path;
  }
=======
  void ParseFromPath(const UString &path, EArcNameMode mode);
  UString GetPathWithoutExt() const { return Prefix + Name; }
  UString GetFinalPath() const;
  UString GetFinalVolPath() const;
  FString GetTempPath() const;
>>>>>>> upstream/master
};

struct CUpdateArchiveCommand
{
  UString UserArchivePath;
  CArchivePath ArchivePath;
  NUpdateArchive::CActionSet ActionSet;
};

struct CCompressionMethodMode
{
<<<<<<< HEAD
  int FormatIndex;
  CObjectVector<CProperty> Properties;
  CCompressionMethodMode(): FormatIndex(-1) {}
=======
  bool Type_Defined;
  COpenType Type;
  CObjectVector<CProperty> Properties;
  
  CCompressionMethodMode(): Type_Defined(false) {}
};

namespace NRecursedType { enum EEnum
{
  kRecursed,
  kWildcardOnlyRecursed,
  kNonRecursed
};}

struct CRenamePair
{
  UString OldName;
  UString NewName;
  bool WildcardParsing;
  NRecursedType::EEnum RecursedType;
  
  CRenamePair(): WildcardParsing(true), RecursedType(NRecursedType::kNonRecursed) {}

  bool Prepare();
  bool GetNewPath(bool isFolder, const UString &src, UString &dest) const;
>>>>>>> upstream/master
};

struct CUpdateOptions
{
  CCompressionMethodMode MethodMode;

  CObjectVector<CUpdateArchiveCommand> Commands;
  bool UpdateArchiveItself;
  CArchivePath ArchivePath;
<<<<<<< HEAD
  
=======
  EArcNameMode ArcNameMode;

>>>>>>> upstream/master
  bool SfxMode;
  FString SfxModule;
  
  bool OpenShareForWrite;

  bool StdInMode;
  UString StdInFileName;
  bool StdOutMode;
  
  bool EMailMode;
  bool EMailRemoveAfter;
  UString EMailAddress;

  FString WorkingDir;
<<<<<<< HEAD

  bool Init(const CCodecs *codecs, const CIntVector &formatIndices, const UString &arcPath);
=======
  NWildcard::ECensorPathMode PathMode;
  UString AddPathPrefix;

  CBoolPair NtSecurity;
  CBoolPair AltStreams;
  CBoolPair HardLinks;
  CBoolPair SymLinks;

  bool DeleteAfterCompressing;

  bool SetArcMTime;

  CObjectVector<CRenamePair> RenamePairs;

  bool InitFormatIndex(const CCodecs *codecs, const CObjectVector<COpenType> &types, const UString &arcPath);
  bool SetArcPath(const CCodecs *codecs, const UString &arcPath);
>>>>>>> upstream/master

  CUpdateOptions():
    UpdateArchiveItself(true),
    SfxMode(false),
    StdInMode(false),
    StdOutMode(false),
    EMailMode(false),
    EMailRemoveAfter(false),
<<<<<<< HEAD
    OpenShareForWrite(false)
      {};

  void SetAddActionCommand()
  {
    Commands.Clear();
    CUpdateArchiveCommand c;
    c.ActionSet = NUpdateArchive::kAddActionSet;
=======
    OpenShareForWrite(false),
    ArcNameMode(k_ArcNameMode_Smart),
    PathMode(NWildcard::k_RelatPath),
    
    DeleteAfterCompressing(false),
    SetArcMTime(false)

      {};

  void SetActionCommand_Add()
  {
    Commands.Clear();
    CUpdateArchiveCommand c;
    c.ActionSet = NUpdateArchive::k_ActionSet_Add;
>>>>>>> upstream/master
    Commands.Add(c);
  }

  CRecordVector<UInt64> VolumesSizes;
};

<<<<<<< HEAD
struct CErrorInfo
{
  DWORD SystemError;
  FString FileName;
  FString FileName2;
  UString Message;
  // UStringVector ErrorPaths;
  // CRecordVector<DWORD> ErrorCodes;
  CErrorInfo(): SystemError(0) {};
};

struct CUpdateErrorInfo: public CErrorInfo
{
=======
struct CUpdateErrorInfo
{
  DWORD SystemError;
  AString Message;
  FStringVector FileNames;

  bool ThereIsError() const { return SystemError != 0 || !Message.IsEmpty() || !FileNames.IsEmpty(); }
  HRESULT Get_HRESULT_Error() const { return SystemError == 0 ? E_FAIL : HRESULT_FROM_WIN32(SystemError); }
  void SetFromLastError(const char *message);
  HRESULT SetFromLastError(const char *message, const FString &fileName);

  CUpdateErrorInfo(): SystemError(0) {};
};

struct CFinishArchiveStat
{
  UInt64 OutArcFileSize;

  CFinishArchiveStat(): OutArcFileSize(0) {}
>>>>>>> upstream/master
};

#define INTERFACE_IUpdateCallbackUI2(x) \
  INTERFACE_IUpdateCallbackUI(x) \
<<<<<<< HEAD
  virtual HRESULT OpenResult(const wchar_t *name, HRESULT result) x; \
  virtual HRESULT StartScanning() x; \
  virtual HRESULT ScanProgress(UInt64 numFolders, UInt64 numFiles, const wchar_t *path) x; \
  virtual HRESULT CanNotFindError(const wchar_t *name, DWORD systemError) x; \
  virtual HRESULT FinishScanning() x; \
  virtual HRESULT StartArchive(const wchar_t *name, bool updating) x; \
  virtual HRESULT FinishArchive() x; \

struct IUpdateCallbackUI2: public IUpdateCallbackUI
=======
  INTERFACE_IDirItemsCallback(x) \
  virtual HRESULT OpenResult(const CCodecs *codecs, const CArchiveLink &arcLink, const wchar_t *name, HRESULT result) x; \
  virtual HRESULT StartScanning() x; \
  virtual HRESULT FinishScanning(const CDirItemsStat &st) x; \
  virtual HRESULT StartOpenArchive(const wchar_t *name) x; \
  virtual HRESULT StartArchive(const wchar_t *name, bool updating) x; \
  virtual HRESULT FinishArchive(const CFinishArchiveStat &st) x; \
  virtual HRESULT DeletingAfterArchiving(const FString &path, bool isDir) x; \
  virtual HRESULT FinishDeletingAfterArchiving() x; \

struct IUpdateCallbackUI2: public IUpdateCallbackUI, public IDirItemsCallback
>>>>>>> upstream/master
{
  INTERFACE_IUpdateCallbackUI2(=0)
};

HRESULT UpdateArchive(
    CCodecs *codecs,
<<<<<<< HEAD
    const NWildcard::CCensor &censor,
    CUpdateOptions &options,
    CUpdateErrorInfo &errorInfo,
    IOpenCallbackUI *openCallback,
    IUpdateCallbackUI2 *callback);
=======
    const CObjectVector<COpenType> &types,
    const UString &cmdArcPath2,
    NWildcard::CCensor &censor,
    CUpdateOptions &options,
    CUpdateErrorInfo &errorInfo,
    IOpenCallbackUI *openCallback,
    IUpdateCallbackUI2 *callback,
    bool needSetPath);
>>>>>>> upstream/master

#endif
