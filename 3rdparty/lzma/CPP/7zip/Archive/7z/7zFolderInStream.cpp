// 7zFolderInStream.cpp

#include "StdAfx.h"

#include "7zFolderInStream.h"

namespace NArchive {
namespace N7z {

<<<<<<< HEAD
CFolderInStream::CFolderInStream()
{
  _inStreamWithHashSpec = new CSequentialInStreamWithCRC;
  _inStreamWithHash = _inStreamWithHashSpec;
}

void CFolderInStream::Init(IArchiveUpdateCallback *updateCallback,
    const UInt32 *fileIndices, UInt32 numFiles)
{
  _updateCallback = updateCallback;
  _numFiles = numFiles;
  _fileIndex = 0;
  _fileIndices = fileIndices;
  Processed.Clear();
  CRCs.Clear();
  Sizes.Clear();
  _fileIsOpen = false;
  _currentSizeIsDefined = false;
=======
void CFolderInStream::Init(IArchiveUpdateCallback *updateCallback,
    const UInt32 *indexes, unsigned numFiles)
{
  _updateCallback = updateCallback;
  _indexes = indexes;
  _numFiles = numFiles;
  _index = 0;
  
  Processed.ClearAndReserve(numFiles);
  CRCs.ClearAndReserve(numFiles);
  Sizes.ClearAndReserve(numFiles);
  
  _pos = 0;
  _crc = CRC_INIT_VAL;
  _size_Defined = false;
  _size = 0;

  _stream.Release();
>>>>>>> upstream/master
}

HRESULT CFolderInStream::OpenStream()
{
<<<<<<< HEAD
  _filePos = 0;
  while (_fileIndex < _numFiles)
  {
    CMyComPtr<ISequentialInStream> stream;
    HRESULT result = _updateCallback->GetStream(_fileIndices[_fileIndex], &stream);
    if (result != S_OK && result != S_FALSE)
      return result;
    _fileIndex++;
    _inStreamWithHashSpec->SetStream(stream);
    _inStreamWithHashSpec->Init();
    if (stream)
    {
      _fileIsOpen = true;
=======
  _pos = 0;
  _crc = CRC_INIT_VAL;
  _size_Defined = false;
  _size = 0;

  while (_index < _numFiles)
  {
    CMyComPtr<ISequentialInStream> stream;
    HRESULT result = _updateCallback->GetStream(_indexes[_index], &stream);
    if (result != S_OK)
    {
      if (result != S_FALSE)
        return result;
    }

    _stream = stream;
    
    if (stream)
    {
>>>>>>> upstream/master
      CMyComPtr<IStreamGetSize> streamGetSize;
      stream.QueryInterface(IID_IStreamGetSize, &streamGetSize);
      if (streamGetSize)
      {
<<<<<<< HEAD
        RINOK(streamGetSize->GetSize(&_currentSize));
        _currentSizeIsDefined = true;
      }
      return S_OK;
    }
    RINOK(_updateCallback->SetOperationResult(NArchive::NUpdate::NOperationResult::kOK));
    Sizes.Add(0);
    Processed.Add(result == S_OK);
    AddDigest();
=======
        if (streamGetSize->GetSize(&_size) == S_OK)
          _size_Defined = true;
      }
      return S_OK;
    }
    
    _index++;
    RINOK(_updateCallback->SetOperationResult(NArchive::NUpdate::NOperationResult::kOK));
    AddFileInfo(result == S_OK);
>>>>>>> upstream/master
  }
  return S_OK;
}

<<<<<<< HEAD
void CFolderInStream::AddDigest()
{
  CRCs.Add(_inStreamWithHashSpec->GetCRC());
}

HRESULT CFolderInStream::CloseStream()
{
  RINOK(_updateCallback->SetOperationResult(NArchive::NUpdate::NOperationResult::kOK));
  _inStreamWithHashSpec->ReleaseStream();
  _fileIsOpen = false;
  _currentSizeIsDefined = false;
  Processed.Add(true);
  Sizes.Add(_filePos);
  AddDigest();
  return S_OK;
=======
void CFolderInStream::AddFileInfo(bool isProcessed)
{
  Processed.Add(isProcessed);
  Sizes.Add(_pos);
  CRCs.Add(CRC_GET_DIGEST(_crc));
>>>>>>> upstream/master
}

STDMETHODIMP CFolderInStream::Read(void *data, UInt32 size, UInt32 *processedSize)
{
<<<<<<< HEAD
  if (processedSize != 0)
    *processedSize = 0;
  while (size > 0)
  {
    if (_fileIsOpen)
    {
      UInt32 processed2;
      RINOK(_inStreamWithHash->Read(data, size, &processed2));
      if (processed2 == 0)
      {
        RINOK(CloseStream());
        continue;
      }
      if (processedSize != 0)
        *processedSize = processed2;
      _filePos += processed2;
      break;
    }
    if (_fileIndex >= _numFiles)
=======
  if (processedSize)
    *processedSize = 0;
  while (size != 0)
  {
    if (_stream)
    {
      UInt32 processed2;
      RINOK(_stream->Read(data, size, &processed2));
      if (processed2 != 0)
      {
        _crc = CrcUpdate(_crc, data, processed2);
        _pos += processed2;
        if (processedSize)
          *processedSize = processed2;
        return S_OK;
      }
      
      _stream.Release();
      _index++;
      AddFileInfo(true);

      _pos = 0;
      _crc = CRC_INIT_VAL;
      _size_Defined = false;
      _size = 0;

      RINOK(_updateCallback->SetOperationResult(NArchive::NUpdate::NOperationResult::kOK));
    }
    
    if (_index >= _numFiles)
>>>>>>> upstream/master
      break;
    RINOK(OpenStream());
  }
  return S_OK;
}

STDMETHODIMP CFolderInStream::GetSubStreamSize(UInt64 subStream, UInt64 *value)
{
  *value = 0;
<<<<<<< HEAD
  int index2 = (int)subStream;
  if (index2 < 0 || subStream > Sizes.Size())
    return E_FAIL;
  if (index2 < Sizes.Size())
  {
    *value = Sizes[index2];
    return S_OK;
  }
  if (!_currentSizeIsDefined)
    return S_FALSE;
  *value = _currentSize;
=======
  if (subStream > Sizes.Size())
    return S_FALSE; // E_FAIL;
  
  unsigned index = (unsigned)subStream;
  if (index < Sizes.Size())
  {
    *value = Sizes[index];
    return S_OK;
  }
  
  if (!_size_Defined)
  {
    *value = _pos;
    return S_FALSE;
  }
  
  *value = (_pos > _size ? _pos : _size);
>>>>>>> upstream/master
  return S_OK;
}

}}
