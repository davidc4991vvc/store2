// ArchiveExtractCallback.h

#ifndef __ARCHIVE_EXTRACT_CALLBACK_H
#define __ARCHIVE_EXTRACT_CALLBACK_H

<<<<<<< HEAD
#include "Common/MyCom.h"
#include "Common/Wildcard.h"
=======
#include "../../../Common/MyCom.h"
#include "../../../Common/Wildcard.h"
>>>>>>> upstream/master

#include "../../IPassword.h"

#include "../../Common/FileStreams.h"
#include "../../Common/ProgressUtils.h"

#include "../../Archive/IArchive.h"

<<<<<<< HEAD
#include "../../Archive/Common/OutStreamWithCRC.h"

=======
>>>>>>> upstream/master
#include "ExtractMode.h"
#include "IFileExtractCallback.h"
#include "OpenArchive.h"

<<<<<<< HEAD
class CArchiveExtractCallback:
  public IArchiveExtractCallback,
  // public IArchiveVolumeExtractCallback,
=======
#include "HashCalc.h"

#ifndef _SFX

class COutStreamWithHash:
  public ISequentialOutStream,
  public CMyUnknownImp
{
  CMyComPtr<ISequentialOutStream> _stream;
  UInt64 _size;
  bool _calculate;
public:
  IHashCalc *_hash;

  MY_UNKNOWN_IMP
  STDMETHOD(Write)(const void *data, UInt32 size, UInt32 *processedSize);
  void SetStream(ISequentialOutStream *stream) { _stream = stream; }
  void ReleaseStream() { _stream.Release(); }
  void Init(bool calculate = true)
  {
    InitCRC();
    _size = 0;
    _calculate = calculate;
  }
  void EnableCalc(bool calculate) { _calculate = calculate; }
  void InitCRC() { _hash->InitForNewFile(); }
  UInt64 GetSize() const { return _size; }
};

#endif

struct CExtractNtOptions
{
  CBoolPair NtSecurity;
  CBoolPair SymLinks;
  CBoolPair HardLinks;
  CBoolPair AltStreams;
  bool ReplaceColonForAltStream;
  bool WriteToAltStreamIfColon;

  CExtractNtOptions():
      ReplaceColonForAltStream(false),
      WriteToAltStreamIfColon(false)
  {
    SymLinks.Val = true;
    HardLinks.Val = true;
    AltStreams.Val = true;
  }
};

#ifndef _SFX

class CGetProp:
  public IGetProp,
  public CMyUnknownImp
{
public:
  const CArc *Arc;
  UInt32 IndexInArc;
  // UString Name; // relative path

  MY_UNKNOWN_IMP1(IGetProp)
  INTERFACE_IGetProp(;)
};

#endif

#ifndef _SFX
#ifndef UNDER_CE

#define SUPPORT_LINKS

#endif
#endif


#ifdef SUPPORT_LINKS

struct CHardLinkNode
{
  UInt64 StreamId;
  UInt64 INode;

  int Compare(const CHardLinkNode &a) const;
};

class CHardLinks
{
public:
  CRecordVector<CHardLinkNode> IDs;
  CObjectVector<FString> Links;

  void Clear()
  {
    IDs.Clear();
    Links.Clear();
  }

  void PrepareLinks()
  {
    while (Links.Size() < IDs.Size())
      Links.AddNew();
  }
};

#endif

#ifdef SUPPORT_ALT_STREAMS

struct CIndexToPathPair
{
  UInt32 Index;
  FString Path;

  CIndexToPathPair(UInt32 index): Index(index) {}
  CIndexToPathPair(UInt32 index, const FString &path): Index(index), Path(path) {}

  int Compare(const CIndexToPathPair &pair) const
  {
    return MyCompare(Index, pair.Index);
  }
};

#endif

class CArchiveExtractCallback:
  public IArchiveExtractCallback,
  public IArchiveExtractCallbackMessage,
>>>>>>> upstream/master
  public ICryptoGetTextPassword,
  public ICompressProgressInfo,
  public CMyUnknownImp
{
  const CArc *_arc;
<<<<<<< HEAD
  const NWildcard::CCensorNode *_wildcardCensor;
  CMyComPtr<IFolderArchiveExtractCallback> _extractCallback2;
  CMyComPtr<ICompressProgressInfo> _compressProgress;
  CMyComPtr<ICryptoGetTextPassword> _cryptoGetTextPassword;
  FString _directoryPath;
  NExtract::NPathMode::EEnum _pathMode;
  NExtract::NOverwriteMode::EEnum _overwriteMode;

  FString _diskFilePath;
  UString _filePath;
=======
  CExtractNtOptions _ntOptions;

  const NWildcard::CCensorNode *_wildcardCensor; // we need wildcard for single pass mode (stdin)
  CMyComPtr<IFolderArchiveExtractCallback> _extractCallback2;
  CMyComPtr<ICompressProgressInfo> _compressProgress;
  CMyComPtr<ICryptoGetTextPassword> _cryptoGetTextPassword;
  CMyComPtr<IArchiveExtractCallbackMessage> _callbackMessage;
  CMyComPtr<IFolderArchiveExtractCallback2> _folderArchiveExtractCallback2;

  FString _dirPathPrefix;
  FString _dirPathPrefix_Full;
  NExtract::NPathMode::EEnum _pathMode;
  NExtract::NOverwriteMode::EEnum _overwriteMode;

  #ifndef _SFX

  CMyComPtr<IFolderExtractToStreamCallback> ExtractToStreamCallback;
  CGetProp *GetProp_Spec;
  CMyComPtr<IGetProp> GetProp;
  
  #endif

  CReadArcItem _item;
  FString _diskFilePath;
>>>>>>> upstream/master
  UInt64 _position;
  bool _isSplit;

  bool _extractMode;

  bool WriteCTime;
  bool WriteATime;
  bool WriteMTime;

  bool _encrypted;

  struct CProcessedFileInfo
  {
    FILETIME CTime;
    FILETIME ATime;
    FILETIME MTime;
    UInt32 Attrib;
  
    bool CTimeDefined;
    bool ATimeDefined;
    bool MTimeDefined;
    bool AttribDefined;
<<<<<<< HEAD

    bool IsDir;
=======
>>>>>>> upstream/master
  } _fi;

  UInt32 _index;
  UInt64 _curSize;
  bool _curSizeDefined;
  COutFileStream *_outFileStreamSpec;
  CMyComPtr<ISequentialOutStream> _outFileStream;

<<<<<<< HEAD
  COutStreamWithCRC *_crcStreamSpec;
  CMyComPtr<ISequentialOutStream> _crcStream;

  UStringVector _removePathParts;

  bool _stdOutMode;
  bool _testMode;
  bool _crcMode;
=======
  #ifndef _SFX
  
  COutStreamWithHash *_hashStreamSpec;
  CMyComPtr<ISequentialOutStream> _hashStream;
  bool _hashStreamWasUsed;
  
  #endif

  bool _removePartsForAltStreams;
  UStringVector _removePathParts;
  
  #ifndef _SFX
  bool _use_baseParentFolder_mode;
  UInt32 _baseParentFolder;
  #endif

  bool _stdOutMode;
  bool _testMode;
>>>>>>> upstream/master
  bool _multiArchives;

  CMyComPtr<ICompressProgressInfo> _localProgress;
  UInt64 _packTotal;
<<<<<<< HEAD
  UInt64 _unpTotal;
=======
  
  UInt64 _progressTotal;
  bool _progressTotal_Defined;

  FStringVector _extractedFolderPaths;
  CRecordVector<UInt32> _extractedFolderIndices;

  #if defined(_WIN32) && !defined(UNDER_CE) && !defined(_SFX)
  bool _saclEnabled;
  #endif
>>>>>>> upstream/master

  void CreateComplexDirectory(const UStringVector &dirPathParts, FString &fullPath);
  HRESULT GetTime(int index, PROPID propID, FILETIME &filetime, bool &filetimeIsDefined);
  HRESULT GetUnpackSize();

  HRESULT SendMessageError(const char *message, const FString &path);
<<<<<<< HEAD
=======
  HRESULT SendMessageError_with_LastError(const char *message, const FString &path);
  HRESULT SendMessageError2(const char *message, const FString &path1, const FString &path2);
>>>>>>> upstream/master

public:

  CLocalProgress *LocalProgressSpec;

  UInt64 NumFolders;
  UInt64 NumFiles;
<<<<<<< HEAD
  UInt64 UnpackSize;
  UInt32 CrcSum;
  
  MY_UNKNOWN_IMP2(ICryptoGetTextPassword, ICompressProgressInfo)
  // COM_INTERFACE_ENTRY(IArchiveVolumeExtractCallback)

  INTERFACE_IArchiveExtractCallback(;)

  STDMETHOD(SetRatioInfo)(const UInt64 *inSize, const UInt64 *outSize);

  // IArchiveVolumeExtractCallback
  // STDMETHOD(GetInStream)(const wchar_t *name, ISequentialInStream **inStream);

  STDMETHOD(CryptoGetTextPassword)(BSTR *password);

  CArchiveExtractCallback():
      WriteCTime(true),
      WriteATime(true),
      WriteMTime(true),
      _multiArchives(false)
  {
    LocalProgressSpec = new CLocalProgress();
    _localProgress = LocalProgressSpec;
  }
=======
  UInt64 NumAltStreams;
  UInt64 UnpackSize;
  UInt64 AltStreams_UnpackSize;
  
  MY_UNKNOWN_IMP3(IArchiveExtractCallbackMessage, ICryptoGetTextPassword, ICompressProgressInfo)

  INTERFACE_IArchiveExtractCallback(;)
  INTERFACE_IArchiveExtractCallbackMessage(;)

  STDMETHOD(SetRatioInfo)(const UInt64 *inSize, const UInt64 *outSize);

  STDMETHOD(CryptoGetTextPassword)(BSTR *password);

  CArchiveExtractCallback();
>>>>>>> upstream/master

  void InitForMulti(bool multiArchives,
      NExtract::NPathMode::EEnum pathMode,
      NExtract::NOverwriteMode::EEnum overwriteMode)
  {
    _multiArchives = multiArchives;
    _pathMode = pathMode;
    _overwriteMode = overwriteMode;
<<<<<<< HEAD
    NumFolders = NumFiles = UnpackSize = 0;
    CrcSum = 0;
  }

  void Init(
      const NWildcard::CCensorNode *wildcardCensor,
      const CArc *arc,
      IFolderArchiveExtractCallback *extractCallback2,
      bool stdOutMode, bool testMode, bool crcMode,
      const FString &directoryPath,
      const UStringVector &removePathParts,
      UInt64 packSize);

};

=======
    NumFolders = NumFiles = NumAltStreams = UnpackSize = AltStreams_UnpackSize = 0;
  }

  #ifndef _SFX

  void SetHashMethods(IHashCalc *hash)
  {
    if (!hash)
      return;
    _hashStreamSpec = new COutStreamWithHash;
    _hashStream = _hashStreamSpec;
    _hashStreamSpec->_hash = hash;
  }

  #endif

  void Init(
      const CExtractNtOptions &ntOptions,
      const NWildcard::CCensorNode *wildcardCensor,
      const CArc *arc,
      IFolderArchiveExtractCallback *extractCallback2,
      bool stdOutMode, bool testMode,
      const FString &directoryPath,
      const UStringVector &removePathParts, bool removePartsForAltStreams,
      UInt64 packSize);


  #ifdef SUPPORT_LINKS

private:
  CHardLinks _hardLinks;
  UString linkPath;

  // FString _CopyFile_Path;
  // HRESULT MyCopyFile(ISequentialOutStream *outStream);

public:
  // call PrepareHardLinks() after Init()
  HRESULT PrepareHardLinks(const CRecordVector<UInt32> *realIndices);  // NULL means all items

  #endif


  #ifdef SUPPORT_ALT_STREAMS
  CObjectVector<CIndexToPathPair> _renamedFiles;
  #endif

  // call it after Init()

  #ifndef _SFX
  void SetBaseParentFolderIndex(UInt32 indexInArc)
  {
    _baseParentFolder = indexInArc;
    _use_baseParentFolder_mode = true;
  }
  #endif

  HRESULT SetDirsTimes();
};

bool CensorNode_CheckPath(const NWildcard::CCensorNode &node, const CReadArcItem &item);

>>>>>>> upstream/master
#endif
