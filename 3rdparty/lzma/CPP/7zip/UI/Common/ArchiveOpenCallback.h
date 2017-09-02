// ArchiveOpenCallback.h

#ifndef __ARCHIVE_OPEN_CALLBACK_H
#define __ARCHIVE_OPEN_CALLBACK_H

<<<<<<< HEAD
#include "Common/MyCom.h"
#include "Common/MyString.h"

#include "Windows/FileFind.h"
=======
#include "../../../Common/MyCom.h"

#include "../../../Windows/FileFind.h"
>>>>>>> upstream/master

#ifndef _NO_CRYPTO
#include "../../IPassword.h"
#endif
#include "../../Archive/IArchive.h"

#ifdef _NO_CRYPTO

#define INTERFACE_IOpenCallbackUI_Crypto(x)

#else

#define INTERFACE_IOpenCallbackUI_Crypto(x) \
  virtual HRESULT Open_CryptoGetTextPassword(BSTR *password) x; \
<<<<<<< HEAD
  virtual HRESULT Open_GetPasswordIfAny(UString &password) x; \
  virtual bool Open_WasPasswordAsked() x; \
  virtual void Open_ClearPasswordWasAskedFlag() x; \
=======
  /* virtual HRESULT Open_GetPasswordIfAny(bool &passwordIsDefined, UString &password) x; */ \
  /* virtual bool Open_WasPasswordAsked() x; */ \
  /* virtual void Open_Clear_PasswordWasAsked_Flag() x; */  \
>>>>>>> upstream/master
  
#endif

#define INTERFACE_IOpenCallbackUI(x) \
  virtual HRESULT Open_CheckBreak() x; \
  virtual HRESULT Open_SetTotal(const UInt64 *files, const UInt64 *bytes) x; \
  virtual HRESULT Open_SetCompleted(const UInt64 *files, const UInt64 *bytes) x; \
<<<<<<< HEAD
=======
  virtual HRESULT Open_Finished() x; \
>>>>>>> upstream/master
  INTERFACE_IOpenCallbackUI_Crypto(x)

struct IOpenCallbackUI
{
  INTERFACE_IOpenCallbackUI(=0)
};

class COpenCallbackImp:
  public IArchiveOpenCallback,
  public IArchiveOpenVolumeCallback,
  public IArchiveOpenSetSubArchiveName,
  #ifndef _NO_CRYPTO
  public ICryptoGetTextPassword,
  #endif
  public CMyUnknownImp
{
public:
<<<<<<< HEAD
  #ifndef _NO_CRYPTO
  MY_UNKNOWN_IMP3(
      IArchiveOpenVolumeCallback,
      ICryptoGetTextPassword,
      IArchiveOpenSetSubArchiveName
      )
  #else
  MY_UNKNOWN_IMP2(
      IArchiveOpenVolumeCallback,
      IArchiveOpenSetSubArchiveName
      )
  #endif
=======
  MY_QUERYINTERFACE_BEGIN2(IArchiveOpenVolumeCallback)
  MY_QUERYINTERFACE_ENTRY(IArchiveOpenSetSubArchiveName)
  #ifndef _NO_CRYPTO
  MY_QUERYINTERFACE_ENTRY(ICryptoGetTextPassword)
  #endif
  MY_QUERYINTERFACE_END
  MY_ADDREF_RELEASE
>>>>>>> upstream/master

  INTERFACE_IArchiveOpenCallback(;)
  INTERFACE_IArchiveOpenVolumeCallback(;)

  #ifndef _NO_CRYPTO
  STDMETHOD(CryptoGetTextPassword)(BSTR *password);
  #endif

  STDMETHOD(SetSubArchiveName(const wchar_t *name))
  {
    _subArchiveMode = true;
    _subArchiveName = name;
<<<<<<< HEAD
    TotalSize = 0;
    return  S_OK;
=======
    // TotalSize = 0;
    return S_OK;
>>>>>>> upstream/master
  }

private:
  FString _folderPrefix;
  NWindows::NFile::NFind::CFileInfo _fileInfo;
  bool _subArchiveMode;
  UString _subArchiveName;
<<<<<<< HEAD
public:
  UStringVector FileNames;
  IOpenCallbackUI *Callback;
  CMyComPtr<IArchiveOpenCallback> ReOpenCallback;
  UInt64 TotalSize;

  COpenCallbackImp(): Callback(NULL) {}
=======

public:
  UStringVector FileNames;
  CBoolVector FileNames_WasUsed;
  CRecordVector<UInt64> FileSizes;
  
  bool PasswordWasAsked;

  IOpenCallbackUI *Callback;
  CMyComPtr<IArchiveOpenCallback> ReOpenCallback;
  // UInt64 TotalSize;

  COpenCallbackImp(): Callback(NULL), _subArchiveMode(false) {}
  
>>>>>>> upstream/master
  void Init(const FString &folderPrefix, const FString &fileName)
  {
    _folderPrefix = folderPrefix;
    if (!_fileInfo.Find(_folderPrefix + fileName))
<<<<<<< HEAD
      throw 1;
    FileNames.Clear();
    _subArchiveMode = false;
    TotalSize = 0;
  }
  int FindName(const UString &name);
=======
      throw 20121118;
    FileNames.Clear();
    FileNames_WasUsed.Clear();
    FileSizes.Clear();
    _subArchiveMode = false;
    // TotalSize = 0;
    PasswordWasAsked = false;
  }

  bool SetSecondFileInfo(CFSTR newName)
  {
    return _fileInfo.Find(newName) && !_fileInfo.IsDir();
  }
>>>>>>> upstream/master
};

#endif
