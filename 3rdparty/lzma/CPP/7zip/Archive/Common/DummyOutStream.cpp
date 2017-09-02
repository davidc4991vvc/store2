// DummyOutStream.cpp

#include "StdAfx.h"

#include "DummyOutStream.h"

<<<<<<< HEAD
STDMETHODIMP CDummyOutStream::Write(const void *data,  UInt32 size, UInt32 *processedSize)
{
  UInt32 realProcessedSize;
  HRESULT result;
  if(!_stream)
  {
    realProcessedSize = size;
    result = S_OK;
  }
  else
    result = _stream->Write(data, size, &realProcessedSize);
  _size += realProcessedSize;
  if(processedSize != NULL)
    *processedSize = realProcessedSize;
  return result;
=======
STDMETHODIMP CDummyOutStream::Write(const void *data, UInt32 size, UInt32 *processedSize)
{
  UInt32 realProcessedSize = size;
  HRESULT res = S_OK;
  if (_stream)
    res = _stream->Write(data, size, &realProcessedSize);
  _size += realProcessedSize;
  if (processedSize)
    *processedSize = realProcessedSize;
  return res;
>>>>>>> upstream/master
}
