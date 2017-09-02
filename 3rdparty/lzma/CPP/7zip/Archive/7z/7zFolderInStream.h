// 7zFolderInStream.h

#ifndef __7Z_FOLDER_IN_STREAM_H
#define __7Z_FOLDER_IN_STREAM_H

<<<<<<< HEAD
#include "../../ICoder.h"
#include "../IArchive.h"
#include "../Common/InStreamWithCRC.h"

#include "7zItem.h"
=======
#include "../../../../C/7zCrc.h"

#include "../../../Common/MyCom.h"
#include "../../../Common/MyVector.h"

#include "../../ICoder.h"
#include "../IArchive.h"
>>>>>>> upstream/master

namespace NArchive {
namespace N7z {

class CFolderInStream:
  public ISequentialInStream,
  public ICompressGetSubStreamSize,
  public CMyUnknownImp
{
<<<<<<< HEAD
  CSequentialInStreamWithCRC *_inStreamWithHashSpec;
  CMyComPtr<ISequentialInStream> _inStreamWithHash;
  CMyComPtr<IArchiveUpdateCallback> _updateCallback;

  bool _currentSizeIsDefined;
  bool _fileIsOpen;
  UInt64 _currentSize;
  UInt64 _filePos;
  const UInt32 *_fileIndices;
  UInt32 _numFiles;
  UInt32 _fileIndex;

  HRESULT OpenStream();
  HRESULT CloseStream();
  void AddDigest();
=======
  CMyComPtr<ISequentialInStream> _stream;
  UInt64 _pos;
  UInt32 _crc;
  bool _size_Defined;
  UInt64 _size;

  const UInt32 *_indexes;
  unsigned _numFiles;
  unsigned _index;

  CMyComPtr<IArchiveUpdateCallback> _updateCallback;

  HRESULT OpenStream();
  void AddFileInfo(bool isProcessed);
>>>>>>> upstream/master

public:
  CRecordVector<bool> Processed;
  CRecordVector<UInt32> CRCs;
  CRecordVector<UInt64> Sizes;

<<<<<<< HEAD
  MY_UNKNOWN_IMP1(ICompressGetSubStreamSize)
  STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);
  STDMETHOD(GetSubStreamSize)(UInt64 subStream, UInt64 *value);

  CFolderInStream();
  void Init(IArchiveUpdateCallback *updateCallback, const UInt32 *fileIndices, UInt32 numFiles);
  UInt64 GetFullSize() const
  {
    UInt64 size = 0;
    for (int i = 0; i < Sizes.Size(); i++)
=======
  MY_UNKNOWN_IMP2(ISequentialInStream, ICompressGetSubStreamSize)
  STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);
  STDMETHOD(GetSubStreamSize)(UInt64 subStream, UInt64 *value);

  void Init(IArchiveUpdateCallback *updateCallback, const UInt32 *indexes, unsigned numFiles);

  bool WasFinished() const { return _index == _numFiles; }

  UInt64 GetFullSize() const
  {
    UInt64 size = 0;
    FOR_VECTOR (i, Sizes)
>>>>>>> upstream/master
      size += Sizes[i];
    return size;
  }
};

}}

#endif
