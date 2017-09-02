// 7zSpecStream.h

#ifndef __7Z_SPEC_STREAM_H
#define __7Z_SPEC_STREAM_H

<<<<<<< HEAD
#include "../../IStream.h"
#include "../../ICoder.h"
#include "../../../Common/MyCom.h"

=======
#include "../../../Common/MyCom.h"

#include "../../ICoder.h"

>>>>>>> upstream/master
class CSequentialInStreamSizeCount2:
  public ISequentialInStream,
  public ICompressGetSubStreamSize,
  public CMyUnknownImp
{
  CMyComPtr<ISequentialInStream> _stream;
  CMyComPtr<ICompressGetSubStreamSize> _getSubStreamSize;
  UInt64 _size;
public:
  void Init(ISequentialInStream *stream)
  {
<<<<<<< HEAD
    _stream = stream;
    _getSubStreamSize = 0;
    _stream.QueryInterface(IID_ICompressGetSubStreamSize, &_getSubStreamSize);
    _size = 0;
  }
  UInt64 GetSize() const { return _size; }

  MY_UNKNOWN_IMP1(ICompressGetSubStreamSize)
=======
    _size = 0;
    _getSubStreamSize.Release();
    _stream = stream;
    _stream.QueryInterface(IID_ICompressGetSubStreamSize, &_getSubStreamSize);
  }
  UInt64 GetSize() const { return _size; }

  MY_UNKNOWN_IMP2(ISequentialInStream, ICompressGetSubStreamSize)
>>>>>>> upstream/master

  STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);

  STDMETHOD(GetSubStreamSize)(UInt64 subStream, UInt64 *value);
};

#endif
