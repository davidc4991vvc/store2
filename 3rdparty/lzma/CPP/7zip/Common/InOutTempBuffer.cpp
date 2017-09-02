// InOutTempBuffer.cpp

#include "StdAfx.h"

#include "../../../C/7zCrc.h"

<<<<<<< HEAD
=======
#include "../../Common/Defs.h"

>>>>>>> upstream/master
#include "InOutTempBuffer.h"
#include "StreamUtils.h"

using namespace NWindows;
using namespace NFile;
<<<<<<< HEAD
using namespace NDirectory;

static const UInt32 kTempBufSize = (1 << 20);
=======
using namespace NDir;

static const size_t kTempBufSize = (1 << 20);
>>>>>>> upstream/master

static CFSTR kTempFilePrefixString = FTEXT("7zt");

CInOutTempBuffer::CInOutTempBuffer(): _buf(NULL) { }

void CInOutTempBuffer::Create()
{
  if (!_buf)
    _buf = new Byte[kTempBufSize];
}

CInOutTempBuffer::~CInOutTempBuffer()
{
  delete []_buf;
}

void CInOutTempBuffer::InitWriting()
{
  _bufPos = 0;
  _tempFileCreated = false;
  _size = 0;
  _crc = CRC_INIT_VAL;
}

bool CInOutTempBuffer::WriteToFile(const void *data, UInt32 size)
{
  if (size == 0)
    return true;
  if (!_tempFileCreated)
  {
    if (!_tempFile.CreateRandomInTempFolder(kTempFilePrefixString, &_outFile))
      return false;
    _tempFileCreated = true;
  }
  UInt32 processed;
  if (!_outFile.Write(data, size, processed))
    return false;
  _crc = CrcUpdate(_crc, data, processed);
  _size += processed;
  return (processed == size);
}

bool CInOutTempBuffer::Write(const void *data, UInt32 size)
{
<<<<<<< HEAD
  if (_bufPos < kTempBufSize)
  {
    UInt32 cur = MyMin(kTempBufSize - _bufPos, size);
    memcpy(_buf + _bufPos, data, cur);
    _crc = CrcUpdate(_crc, data, cur);
    _bufPos += cur;
    size -= cur;
    data = ((const Byte *)data) + cur;
    _size += cur;
=======
  if (size == 0)
    return true;
  size_t cur = kTempBufSize - _bufPos;
  if (cur != 0)
  {
    if (cur > size)
      cur = size;
    memcpy(_buf + _bufPos, data, cur);
    _crc = CrcUpdate(_crc, data, cur);
    _bufPos += cur;
    _size += cur;
    size -= (UInt32)cur;
    data = ((const Byte *)data) + cur;
>>>>>>> upstream/master
  }
  return WriteToFile(data, size);
}

HRESULT CInOutTempBuffer::WriteToStream(ISequentialOutStream *stream)
{
  if (!_outFile.Close())
    return E_FAIL;

  UInt64 size = 0;
  UInt32 crc = CRC_INIT_VAL;

<<<<<<< HEAD
  if (_bufPos > 0)
=======
  if (_bufPos != 0)
>>>>>>> upstream/master
  {
    RINOK(WriteStream(stream, _buf, _bufPos));
    crc = CrcUpdate(crc, _buf, _bufPos);
    size += _bufPos;
  }
<<<<<<< HEAD
=======
  
>>>>>>> upstream/master
  if (_tempFileCreated)
  {
    NIO::CInFile inFile;
    if (!inFile.Open(_tempFile.GetPath()))
      return E_FAIL;
    while (size < _size)
    {
      UInt32 processed;
      if (!inFile.ReadPart(_buf, kTempBufSize, processed))
        return E_FAIL;
      if (processed == 0)
        break;
      RINOK(WriteStream(stream, _buf, processed));
      crc = CrcUpdate(crc, _buf, processed);
      size += processed;
    }
  }
<<<<<<< HEAD
  return (_crc == crc && size == _size) ? S_OK : E_FAIL;
}

=======
  
  return (_crc == crc && size == _size) ? S_OK : E_FAIL;
}

/*
>>>>>>> upstream/master
STDMETHODIMP CSequentialOutTempBufferImp::Write(const void *data, UInt32 size, UInt32 *processed)
{
  if (!_buf->Write(data, size))
  {
<<<<<<< HEAD
    if (processed != NULL)
      *processed = 0;
    return E_FAIL;
  }
  if (processed != NULL)
    *processed = size;
  return S_OK;
}
=======
    if (processed)
      *processed = 0;
    return E_FAIL;
  }
  if (processed)
    *processed = size;
  return S_OK;
}
*/
>>>>>>> upstream/master
