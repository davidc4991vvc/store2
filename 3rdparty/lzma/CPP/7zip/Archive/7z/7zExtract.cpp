// 7zExtract.cpp

#include "StdAfx.h"

<<<<<<< HEAD
=======
#include "../../../../C/7zCrc.h"

>>>>>>> upstream/master
#include "../../../Common/ComTry.h"

#include "../../Common/ProgressUtils.h"

#include "7zDecode.h"
<<<<<<< HEAD
// #include "7z1Decode.h"
#include "7zFolderOutStream.h"
#include "7zHandler.h"

namespace NArchive {
namespace N7z {

struct CExtractFolderInfo
{
  #ifdef _7Z_VOL
  int VolumeIndex;
  #endif
  CNum FileIndex;
  CNum FolderIndex;
  CBoolVector ExtractStatuses;
  UInt64 UnpackSize;
  CExtractFolderInfo(
    #ifdef _7Z_VOL
    int volumeIndex,
    #endif
    CNum fileIndex, CNum folderIndex):
    #ifdef _7Z_VOL
    VolumeIndex(volumeIndex),
    #endif
    FileIndex(fileIndex),
    FolderIndex(folderIndex),
    UnpackSize(0)
  {
    if (fileIndex != kNumNoIndex)
    {
      ExtractStatuses.Reserve(1);
      ExtractStatuses.Add(true);
    }
  };
};
=======
#include "7zHandler.h"

// EXTERN_g_ExternalCodecs

namespace NArchive {
namespace N7z {

class CFolderOutStream:
  public ISequentialOutStream,
  public CMyUnknownImp
{
  CMyComPtr<ISequentialOutStream> _stream;
public:
  bool TestMode;
  bool CheckCrc;
private:
  bool _fileIsOpen;
  bool _calcCrc;
  UInt32 _crc;
  UInt64 _rem;

  const UInt32 *_indexes;
  unsigned _numFiles;
  unsigned _fileIndex;

  HRESULT OpenFile(bool isCorrupted = false);
  HRESULT CloseFile_and_SetResult(Int32 res);
  HRESULT CloseFile();
  HRESULT ProcessEmptyFiles();

public:
  MY_UNKNOWN_IMP1(ISequentialOutStream)

  const CDbEx *_db;
  CMyComPtr<IArchiveExtractCallback> ExtractCallback;

  bool ExtraWriteWasCut;

  CFolderOutStream():
      TestMode(false),
      CheckCrc(true)
      {}

  STDMETHOD(Write)(const void *data, UInt32 size, UInt32 *processedSize);

  HRESULT Init(unsigned startIndex, const UInt32 *indexes, unsigned numFiles);
  HRESULT FlushCorrupted(Int32 callbackOperationResult);

  bool WasWritingFinished() const { return _numFiles == 0; }
};


HRESULT CFolderOutStream::Init(unsigned startIndex, const UInt32 *indexes, unsigned numFiles)
{
  _fileIndex = startIndex;
  _indexes = indexes;
  _numFiles = numFiles;
  
  _fileIsOpen = false;
  ExtraWriteWasCut = false;
  
  return ProcessEmptyFiles();
}

HRESULT CFolderOutStream::OpenFile(bool isCorrupted)
{
  const CFileItem &fi = _db->Files[_fileIndex];
  UInt32 nextFileIndex = (_indexes ? *_indexes : _fileIndex);
  Int32 askMode = (_fileIndex == nextFileIndex) ?
        (TestMode ?
        NExtract::NAskMode::kTest :
        NExtract::NAskMode::kExtract) :
      NExtract::NAskMode::kSkip;

  if (isCorrupted
      && askMode == NExtract::NAskMode::kExtract
      && !_db->IsItemAnti(_fileIndex)
      && !fi.IsDir)
    askMode = NExtract::NAskMode::kTest;
  
  CMyComPtr<ISequentialOutStream> realOutStream;
  RINOK(ExtractCallback->GetStream(_fileIndex, &realOutStream, askMode));
  
  _stream = realOutStream;
  _crc = CRC_INIT_VAL;
  _calcCrc = (CheckCrc && fi.CrcDefined && !fi.IsDir);

  _fileIsOpen = true;
  _rem = fi.Size;
  
  if (askMode == NExtract::NAskMode::kExtract
      && !realOutStream
      && !_db->IsItemAnti(_fileIndex)
      && !fi.IsDir)
    askMode = NExtract::NAskMode::kSkip;
  return ExtractCallback->PrepareOperation(askMode);
}

HRESULT CFolderOutStream::CloseFile_and_SetResult(Int32 res)
{
  _stream.Release();
  _fileIsOpen = false;
  
  if (!_indexes)
    _numFiles--;
  else if (*_indexes == _fileIndex)
  {
    _indexes++;
    _numFiles--;
  }

  _fileIndex++;
  return ExtractCallback->SetOperationResult(res);
}

HRESULT CFolderOutStream::CloseFile()
{
  const CFileItem &fi = _db->Files[_fileIndex];
  return CloseFile_and_SetResult((!_calcCrc || fi.Crc == CRC_GET_DIGEST(_crc)) ?
      NExtract::NOperationResult::kOK :
      NExtract::NOperationResult::kCRCError);
}

HRESULT CFolderOutStream::ProcessEmptyFiles()
{
  while (_numFiles != 0 && _db->Files[_fileIndex].Size == 0)
  {
    RINOK(OpenFile());
    RINOK(CloseFile());
  }
  return S_OK;
}

STDMETHODIMP CFolderOutStream::Write(const void *data, UInt32 size, UInt32 *processedSize)
{
  if (processedSize)
    *processedSize = 0;
  
  while (size != 0)
  {
    if (_fileIsOpen)
    {
      UInt32 cur = (size < _rem ? size : (UInt32)_rem);
      HRESULT result = S_OK;
      if (_stream)
        result = _stream->Write(data, cur, &cur);
      if (_calcCrc)
        _crc = CrcUpdate(_crc, data, cur);
      if (processedSize)
        *processedSize += cur;
      data = (const Byte *)data + cur;
      size -= cur;
      _rem -= cur;
      if (_rem == 0)
      {
        RINOK(CloseFile());
        RINOK(ProcessEmptyFiles());
      }
      RINOK(result);
      if (cur == 0)
        break;
      continue;
    }
  
    RINOK(ProcessEmptyFiles());
    if (_numFiles == 0)
    {
      // we support partial extracting
      /*
      if (processedSize)
        *processedSize += size;
      break;
      */
      ExtraWriteWasCut = true;
      // return S_FALSE;
      return k_My_HRESULT_WritingWasCut;
    }
    RINOK(OpenFile());
  }
  
  return S_OK;
}

HRESULT CFolderOutStream::FlushCorrupted(Int32 callbackOperationResult)
{
  while (_numFiles != 0)
  {
    if (_fileIsOpen)
    {
      RINOK(CloseFile_and_SetResult(callbackOperationResult));
    }
    else
    {
      RINOK(OpenFile(true));
    }
  }
  return S_OK;
}
>>>>>>> upstream/master

STDMETHODIMP CHandler::Extract(const UInt32 *indices, UInt32 numItems,
    Int32 testModeSpec, IArchiveExtractCallback *extractCallbackSpec)
{
  COM_TRY_BEGIN
<<<<<<< HEAD
  bool testMode = (testModeSpec != 0);
  CMyComPtr<IArchiveExtractCallback> extractCallback = extractCallbackSpec;
  UInt64 importantTotalUnpacked = 0;

  bool allFilesMode = (numItems == (UInt32)-1);
  if (allFilesMode)
    numItems =
    #ifdef _7Z_VOL
    _refs.Size();
    #else
    _db.Files.Size();
    #endif

  if(numItems == 0)
    return S_OK;

  /*
  if(_volumes.Size() != 1)
    return E_FAIL;
  const CVolume &volume = _volumes.Front();
  const CArchiveDatabaseEx &_db = volume.Database;
  IInStream *_inStream = volume.Stream;
  */
  
  CObjectVector<CExtractFolderInfo> extractFolderInfoVector;
  for (UInt32 ii = 0; ii < numItems; ii++)
  {
    // UInt32 fileIndex = allFilesMode ? indexIndex : indices[indexIndex];
    UInt32 ref2Index = allFilesMode ? ii : indices[ii];
    // const CRef2 &ref2 = _refs[ref2Index];

    // for (UInt32 ri = 0; ri < ref2.Refs.Size(); ri++)
    {
      #ifdef _7Z_VOL
      // const CRef &ref = ref2.Refs[ri];
      const CRef &ref = _refs[ref2Index];

      int volumeIndex = ref.VolumeIndex;
      const CVolume &volume = _volumes[volumeIndex];
      const CArchiveDatabaseEx &db = volume.Database;
      UInt32 fileIndex = ref.ItemIndex;
      #else
      const CArchiveDatabaseEx &db = _db;
      UInt32 fileIndex = ref2Index;
      #endif

      CNum folderIndex = db.FileIndexToFolderIndexMap[fileIndex];
      if (folderIndex == kNumNoIndex)
      {
        extractFolderInfoVector.Add(CExtractFolderInfo(
            #ifdef _7Z_VOL
            volumeIndex,
            #endif
            fileIndex, kNumNoIndex));
        continue;
      }
      if (extractFolderInfoVector.IsEmpty() ||
        folderIndex != extractFolderInfoVector.Back().FolderIndex
        #ifdef _7Z_VOL
        || volumeIndex != extractFolderInfoVector.Back().VolumeIndex
        #endif
        )
      {
        extractFolderInfoVector.Add(CExtractFolderInfo(
            #ifdef _7Z_VOL
            volumeIndex,
            #endif
            kNumNoIndex, folderIndex));
        const CFolder &folderInfo = db.Folders[folderIndex];
        UInt64 unpackSize = folderInfo.GetUnpackSize();
        importantTotalUnpacked += unpackSize;
        extractFolderInfoVector.Back().UnpackSize = unpackSize;
      }
      
      CExtractFolderInfo &efi = extractFolderInfoVector.Back();
      
      // const CFolderInfo &folderInfo = m_dam_Folders[folderIndex];
      CNum startIndex = db.FolderStartFileIndex[folderIndex];
      for (CNum index = efi.ExtractStatuses.Size();
          index <= fileIndex - startIndex; index++)
      {
        // UInt64 unpackSize = _db.Files[startIndex + index].UnpackSize;
        // Count partial_folder_size
        // efi.UnpackSize += unpackSize;
        // importantTotalUnpacked += unpackSize;
        efi.ExtractStatuses.Add(index == fileIndex - startIndex);
      }
=======
  
  CMyComPtr<IArchiveExtractCallback> extractCallback = extractCallbackSpec;
  
  UInt64 importantTotalUnpacked = 0;

  // numItems = (UInt32)(Int32)-1;

  bool allFilesMode = (numItems == (UInt32)(Int32)-1);
  if (allFilesMode)
    numItems = _db.Files.Size();

  if (numItems == 0)
    return S_OK;

  {
    CNum prevFolder = kNumNoIndex;
    UInt32 nextFile = 0;
    
    UInt32 i;
    
    for (i = 0; i < numItems; i++)
    {
      UInt32 fileIndex = allFilesMode ? i : indices[i];
      CNum folderIndex = _db.FileIndexToFolderIndexMap[fileIndex];
      if (folderIndex == kNumNoIndex)
        continue;
      if (folderIndex != prevFolder || fileIndex < nextFile)
        nextFile = _db.FolderStartFileIndex[folderIndex];
      for (CNum index = nextFile; index <= fileIndex; index++)
        importantTotalUnpacked += _db.Files[index].Size;
      nextFile = fileIndex + 1;
      prevFolder = folderIndex;
>>>>>>> upstream/master
    }
  }

  RINOK(extractCallback->SetTotal(importantTotalUnpacked));

<<<<<<< HEAD
  CDecoder decoder(
    #ifdef _ST_MODE
    false
    #else
    true
    #endif
    );
  // CDecoder1 decoder;

  UInt64 totalPacked = 0;
  UInt64 totalUnpacked = 0;
  UInt64 curPacked, curUnpacked;

  CLocalProgress *lps = new CLocalProgress;
  CMyComPtr<ICompressProgressInfo> progress = lps;
  lps->Init(extractCallback, false);

  for (int i = 0;; i++, totalUnpacked += curUnpacked, totalPacked += curPacked)
  {
    lps->OutSize = totalUnpacked;
    lps->InSize = totalPacked;
    RINOK(lps->SetCur());

    if (i >= extractFolderInfoVector.Size())
      break;
    
    const CExtractFolderInfo &efi = extractFolderInfoVector[i];
    curUnpacked = efi.UnpackSize;
    curPacked = 0;

    CFolderOutStream *folderOutStream = new CFolderOutStream;
    CMyComPtr<ISequentialOutStream> outStream(folderOutStream);

    #ifdef _7Z_VOL
    const CVolume &volume = _volumes[efi.VolumeIndex];
    const CArchiveDatabaseEx &db = volume.Database;
    #else
    const CArchiveDatabaseEx &db = _db;
    #endif

    CNum startIndex;
    if (efi.FileIndex != kNumNoIndex)
      startIndex = efi.FileIndex;
    else
      startIndex = db.FolderStartFileIndex[efi.FolderIndex];

    HRESULT result = folderOutStream->Init(&db,
        #ifdef _7Z_VOL
        volume.StartRef2Index,
        #else
        0,
        #endif
        startIndex,
        &efi.ExtractStatuses, extractCallback, testMode, _crcSize != 0);

    RINOK(result);

    if (efi.FileIndex != kNumNoIndex)
      continue;

    CNum folderIndex = efi.FolderIndex;
    const CFolder &folderInfo = db.Folders[folderIndex];

    curPacked = _db.GetFolderFullPackSize(folderIndex);

    CNum packStreamIndex = db.FolderStartPackStreamIndex[folderIndex];
    UInt64 folderStartPackPos = db.GetFolderStreamPos(folderIndex, 0);
=======
  CLocalProgress *lps = new CLocalProgress;
  CMyComPtr<ICompressProgressInfo> progress = lps;
  lps->Init(extractCallback, false);

  CDecoder decoder(
    #if !defined(USE_MIXER_MT)
      false
    #elif !defined(USE_MIXER_ST)
      true
    #elif !defined(__7Z_SET_PROPERTIES)
      #ifdef _7ZIP_ST
        false
      #else
        true
      #endif
    #else
      _useMultiThreadMixer
    #endif
    );

  UInt64 curPacked, curUnpacked;

  CMyComPtr<IArchiveExtractCallbackMessage> callbackMessage;
  extractCallback.QueryInterface(IID_IArchiveExtractCallbackMessage, &callbackMessage);

  CFolderOutStream *folderOutStream = new CFolderOutStream;
  CMyComPtr<ISequentialOutStream> outStream(folderOutStream);

  folderOutStream->_db = &_db;
  folderOutStream->ExtractCallback = extractCallback;
  folderOutStream->TestMode = (testModeSpec != 0);
  folderOutStream->CheckCrc = (_crcSize != 0);

  for (UInt32 i = 0;; lps->OutSize += curUnpacked, lps->InSize += curPacked)
  {
    RINOK(lps->SetCur());

    if (i >= numItems)
      break;

    curUnpacked = 0;
    curPacked = 0;

    UInt32 fileIndex = allFilesMode ? i : indices[i];
    CNum folderIndex = _db.FileIndexToFolderIndexMap[fileIndex];

    UInt32 numSolidFiles = 1;

    if (folderIndex != kNumNoIndex)
    {
      curPacked = _db.GetFolderFullPackSize(folderIndex);
      UInt32 nextFile = fileIndex + 1;
      fileIndex = _db.FolderStartFileIndex[folderIndex];
      UInt32 k;

      for (k = i + 1; k < numItems; k++)
      {
        UInt32 fileIndex2 = allFilesMode ? k : indices[k];
        if (_db.FileIndexToFolderIndexMap[fileIndex2] != folderIndex
            || fileIndex2 < nextFile)
          break;
        nextFile = fileIndex2 + 1;
      }
      
      numSolidFiles = k - i;
      
      for (k = fileIndex; k < nextFile; k++)
        curUnpacked += _db.Files[k].Size;
    }

    {
      HRESULT result = folderOutStream->Init(fileIndex,
          allFilesMode ? NULL : indices + i,
          numSolidFiles);

      i += numSolidFiles;

      RINOK(result);
    }

    // to test solid block with zero unpacked size we disable that code
    if (folderOutStream->WasWritingFinished())
      continue;
>>>>>>> upstream/master

    #ifndef _NO_CRYPTO
    CMyComPtr<ICryptoGetTextPassword> getTextPassword;
    if (extractCallback)
      extractCallback.QueryInterface(IID_ICryptoGetTextPassword, &getTextPassword);
    #endif

    try
    {
      #ifndef _NO_CRYPTO
<<<<<<< HEAD
      bool passwordIsDefined;
      #endif

      HRESULT result = decoder.Decode(
          EXTERNAL_CODECS_VARS
          #ifdef _7Z_VOL
          volume.Stream,
          #else
          _inStream,
          #endif
          folderStartPackPos,
          &db.PackSizes[packStreamIndex],
          folderInfo,
          outStream,
          progress
          #ifndef _NO_CRYPTO
          , getTextPassword, passwordIsDefined
          #endif
          #if !defined(_7ZIP_ST) && !defined(_SFX)
          , true, _numThreads
          #endif
          );

      if (result == S_FALSE)
      {
        RINOK(folderOutStream->FlushCorrupted(NExtract::NOperationResult::kDataError));
        continue;
      }
      if (result == E_NOTIMPL)
      {
        RINOK(folderOutStream->FlushCorrupted(NExtract::NOperationResult::kUnSupportedMethod));
        continue;
      }
      if (result != S_OK)
        return result;
      if (folderOutStream->WasWritingFinished() != S_OK)
      {
        RINOK(folderOutStream->FlushCorrupted(NExtract::NOperationResult::kDataError));
        continue;
      }
=======
        bool isEncrypted = false;
        bool passwordIsDefined = false;
        UString password;
      #endif


      HRESULT result = decoder.Decode(
          EXTERNAL_CODECS_VARS
          _inStream,
          _db.ArcInfo.DataStartPosition,
          _db, folderIndex,
          &curUnpacked,

          outStream,
          progress,
          NULL // *inStreamMainRes
          
          _7Z_DECODER_CRYPRO_VARS
          #if !defined(_7ZIP_ST) && !defined(_SFX)
            , true, _numThreads
          #endif
          );

      if (result == S_FALSE || result == E_NOTIMPL)
      {
        bool wasFinished = folderOutStream->WasWritingFinished();
      
        int resOp = (result == S_FALSE ?
            NExtract::NOperationResult::kDataError :
            NExtract::NOperationResult::kUnsupportedMethod);

        RINOK(folderOutStream->FlushCorrupted(resOp));

        if (wasFinished)
        {
          // we don't show error, if it's after required files
          if (/* !folderOutStream->ExtraWriteWasCut && */ callbackMessage)
          {
            RINOK(callbackMessage->ReportExtractResult(NEventIndexType::kBlockIndex, folderIndex, resOp));
          }
        }
        continue;
      }
      
      if (result != S_OK)
        return result;

      RINOK(folderOutStream->FlushCorrupted(NExtract::NOperationResult::kDataError));
      continue;
>>>>>>> upstream/master
    }
    catch(...)
    {
      RINOK(folderOutStream->FlushCorrupted(NExtract::NOperationResult::kDataError));
<<<<<<< HEAD
      continue;
    }
  }
  return S_OK;
=======
      // continue;
      return E_FAIL;
    }
  }

  return S_OK;

>>>>>>> upstream/master
  COM_TRY_END
}

}}
