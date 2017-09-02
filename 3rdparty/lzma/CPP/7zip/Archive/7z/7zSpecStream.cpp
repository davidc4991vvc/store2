// 7zSpecStream.cpp

#include "StdAfx.h"

#include "7zSpecStream.h"

STDMETHODIMP CSequentialInStreamSizeCount2::Read(void *data, UInt32 size, UInt32 *processedSize)
{
  UInt32 realProcessedSize;
  HRESULT result = _stream->Read(data, size, &realProcessedSize);
  _size += realProcessedSize;
<<<<<<< HEAD
  if (processedSize != 0)
=======
  if (processedSize)
>>>>>>> upstream/master
    *processedSize = realProcessedSize;
  return result;
}

<<<<<<< HEAD
STDMETHODIMP CSequentialInStreamSizeCount2::GetSubStreamSize(
    UInt64 subStream, UInt64 *value)
{
  if (_getSubStreamSize == NULL)
    return E_NOTIMPL;
  return  _getSubStreamSize->GetSubStreamSize(subStream, value);
}

=======
STDMETHODIMP CSequentialInStreamSizeCount2::GetSubStreamSize(UInt64 subStream, UInt64 *value)
{
  if (!_getSubStreamSize)
    return E_NOTIMPL;
  return _getSubStreamSize->GetSubStreamSize(subStream, value);
}
>>>>>>> upstream/master
