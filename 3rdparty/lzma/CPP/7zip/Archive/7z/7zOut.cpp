// 7zOut.cpp

#include "StdAfx.h"

#include "../../../../C/7zCrc.h"

#include "../../../Common/AutoPtr.h"

#include "../../Common/StreamObjects.h"

#include "7zOut.h"

<<<<<<< HEAD
static HRESULT WriteBytes(ISequentialOutStream *stream, const void *data, size_t size)
{
  while (size > 0)
  {
    UInt32 curSize = (UInt32)MyMin(size, (size_t)0xFFFFFFFF);
    UInt32 processedSize;
    RINOK(stream->Write(data, curSize, &processedSize));
    if (processedSize == 0)
      return E_FAIL;
    data = (const void *)((const Byte *)data + processedSize);
    size -= processedSize;
  }
  return S_OK;
}

namespace NArchive {
namespace N7z {

HRESULT COutArchive::WriteDirect(const void *data, UInt32 size)
{
  return ::WriteBytes(SeqStream, data, size);
}

=======
namespace NArchive {
namespace N7z {

>>>>>>> upstream/master
HRESULT COutArchive::WriteSignature()
{
  Byte buf[8];
  memcpy(buf, kSignature, kSignatureSize);
  buf[kSignatureSize] = kMajorVersion;
<<<<<<< HEAD
  buf[kSignatureSize + 1] = 3;
=======
  buf[kSignatureSize + 1] = 4;
>>>>>>> upstream/master
  return WriteDirect(buf, 8);
}

#ifdef _7Z_VOL
HRESULT COutArchive::WriteFinishSignature()
{
  RINOK(WriteDirect(kFinishSignature, kSignatureSize));
  CArchiveVersion av;
  av.Major = kMajorVersion;
  av.Minor = 2;
  RINOK(WriteDirectByte(av.Major));
  return WriteDirectByte(av.Minor);
}
#endif

static void SetUInt32(Byte *p, UInt32 d)
{
  for (int i = 0; i < 4; i++, d >>= 8)
    p[i] = (Byte)d;
}

static void SetUInt64(Byte *p, UInt64 d)
{
  for (int i = 0; i < 8; i++, d >>= 8)
    p[i] = (Byte)d;
}

HRESULT COutArchive::WriteStartHeader(const CStartHeader &h)
{
  Byte buf[24];
  SetUInt64(buf + 4, h.NextHeaderOffset);
  SetUInt64(buf + 12, h.NextHeaderSize);
  SetUInt32(buf + 20, h.NextHeaderCRC);
  SetUInt32(buf, CrcCalc(buf + 4, 20));
  return WriteDirect(buf, 24);
}

#ifdef _7Z_VOL
HRESULT COutArchive::WriteFinishHeader(const CFinishHeader &h)
{
  CCRC crc;
  crc.UpdateUInt64(h.NextHeaderOffset);
  crc.UpdateUInt64(h.NextHeaderSize);
  crc.UpdateUInt32(h.NextHeaderCRC);
  crc.UpdateUInt64(h.ArchiveStartOffset);
  crc.UpdateUInt64(h.AdditionalStartBlockSize);
  RINOK(WriteDirectUInt32(crc.GetDigest()));
  RINOK(WriteDirectUInt64(h.NextHeaderOffset));
  RINOK(WriteDirectUInt64(h.NextHeaderSize));
  RINOK(WriteDirectUInt32(h.NextHeaderCRC));
  RINOK(WriteDirectUInt64(h.ArchiveStartOffset));
  return WriteDirectUInt64(h.AdditionalStartBlockSize);
}
#endif

HRESULT COutArchive::Create(ISequentialOutStream *stream, bool endMarker)
{
  Close();
  #ifdef _7Z_VOL
  // endMarker = false;
  _endMarker = endMarker;
  #endif
  SeqStream = stream;
  if (!endMarker)
  {
    SeqStream.QueryInterface(IID_IOutStream, &Stream);
    if (!Stream)
    {
      return E_NOTIMPL;
      // endMarker = true;
    }
  }
  #ifdef _7Z_VOL
  if (endMarker)
  {
    /*
    CStartHeader sh;
    sh.NextHeaderOffset = (UInt32)(Int32)-1;
    sh.NextHeaderSize = (UInt32)(Int32)-1;
    sh.NextHeaderCRC = 0;
    WriteStartHeader(sh);
    */
  }
  else
  #endif
  {
    if (!Stream)
      return E_FAIL;
    RINOK(WriteSignature());
    RINOK(Stream->Seek(0, STREAM_SEEK_CUR, &_prefixHeaderPos));
  }
  return S_OK;
}

void COutArchive::Close()
{
  SeqStream.Release();
  Stream.Release();
}

HRESULT COutArchive::SkipPrefixArchiveHeader()
{
  #ifdef _7Z_VOL
  if (_endMarker)
    return S_OK;
  #endif
<<<<<<< HEAD
  return Stream->Seek(24, STREAM_SEEK_CUR, NULL);
=======
  Byte buf[24];
  memset(buf, 0, 24);
  return WriteDirect(buf, 24);
>>>>>>> upstream/master
}

UInt64 COutArchive::GetPos() const
{
  if (_countMode)
    return _countSize;
  if (_writeToStream)
    return _outByte.GetProcessedSize();
  return _outByte2.GetPos();
}

void COutArchive::WriteBytes(const void *data, size_t size)
{
  if (_countMode)
    _countSize += size;
  else if (_writeToStream)
  {
    _outByte.WriteBytes(data, size);
    _crc = CrcUpdate(_crc, data, size);
  }
  else
    _outByte2.WriteBytes(data, size);
}

void COutArchive::WriteByte(Byte b)
{
  if (_countMode)
    _countSize++;
  else if (_writeToStream)
  {
    _outByte.WriteByte(b);
    _crc = CRC_UPDATE_BYTE(_crc, b);
  }
  else
    _outByte2.WriteByte(b);
}

void COutArchive::WriteUInt32(UInt32 value)
{
  for (int i = 0; i < 4; i++)
  {
    WriteByte((Byte)value);
    value >>= 8;
  }
}

void COutArchive::WriteUInt64(UInt64 value)
{
  for (int i = 0; i < 8; i++)
  {
    WriteByte((Byte)value);
    value >>= 8;
  }
}

void COutArchive::WriteNumber(UInt64 value)
{
  Byte firstByte = 0;
  Byte mask = 0x80;
  int i;
  for (i = 0; i < 8; i++)
  {
    if (value < ((UInt64(1) << ( 7  * (i + 1)))))
    {
      firstByte |= Byte(value >> (8 * i));
      break;
    }
    firstByte |= mask;
    mask >>= 1;
  }
  WriteByte(firstByte);
<<<<<<< HEAD
  for (;i > 0; i--)
=======
  for (; i > 0; i--)
>>>>>>> upstream/master
  {
    WriteByte((Byte)value);
    value >>= 8;
  }
}

static UInt32 GetBigNumberSize(UInt64 value)
{
  int i;
  for (i = 1; i < 9; i++)
    if (value < (((UInt64)1 << (i * 7))))
      break;
  return i;
}

#ifdef _7Z_VOL
UInt32 COutArchive::GetVolHeadersSize(UInt64 dataSize, int nameLength, bool props)
{
  UInt32 result = GetBigNumberSize(dataSize) * 2 + 41;
  if (nameLength != 0)
  {
    nameLength = (nameLength + 1) * 2;
    result += nameLength + GetBigNumberSize(nameLength) + 2;
  }
  if (props)
  {
    result += 20;
  }
  if (result >= 128)
    result++;
  result += kSignatureSize + 2 + kFinishHeaderSize;
  return result;
}

UInt64 COutArchive::GetVolPureSize(UInt64 volSize, int nameLength, bool props)
{
  UInt32 headersSizeBase = COutArchive::GetVolHeadersSize(1, nameLength, props);
  int testSize;
  if (volSize > headersSizeBase)
    testSize = volSize - headersSizeBase;
  else
    testSize = 1;
  UInt32 headersSize = COutArchive::GetVolHeadersSize(testSize, nameLength, props);
  UInt64 pureSize = 1;
  if (volSize > headersSize)
    pureSize = volSize - headersSize;
  return pureSize;
}
#endif

void COutArchive::WriteFolder(const CFolder &folder)
{
  WriteNumber(folder.Coders.Size());
<<<<<<< HEAD
  int i;
=======
  unsigned i;
  
>>>>>>> upstream/master
  for (i = 0; i < folder.Coders.Size(); i++)
  {
    const CCoderInfo &coder = folder.Coders[i];
    {
<<<<<<< HEAD
      size_t propsSize = coder.Props.GetCapacity();
      
      UInt64 id = coder.MethodID;
      int idSize;
      for (idSize = 1; idSize < sizeof(id); idSize++)
        if ((id >> (8 * idSize)) == 0)
          break;
      BYTE longID[15];
      for (int t = idSize - 1; t >= 0 ; t--, id >>= 8)
        longID[t] = (Byte)(id & 0xFF);
      Byte b;
      b = (Byte)(idSize & 0xF);
      bool isComplex = !coder.IsSimpleCoder();
      b |= (isComplex ? 0x10 : 0);
      b |= ((propsSize != 0) ? 0x20 : 0 );
      WriteByte(b);
      WriteBytes(longID, idSize);
      if (isComplex)
      {
        WriteNumber(coder.NumInStreams);
        WriteNumber(coder.NumOutStreams);
=======
      UInt64 id = coder.MethodID;
      unsigned idSize;
      for (idSize = 1; idSize < sizeof(id); idSize++)
        if ((id >> (8 * idSize)) == 0)
          break;
      idSize &= 0xF;
      Byte temp[16];
      for (unsigned t = idSize; t != 0; t--, id >>= 8)
        temp[t] = (Byte)(id & 0xFF);
  
      Byte b = (Byte)(idSize);
      bool isComplex = !coder.IsSimpleCoder();
      b |= (isComplex ? 0x10 : 0);

      size_t propsSize = coder.Props.Size();
      b |= ((propsSize != 0) ? 0x20 : 0);
      temp[0] = b;
      WriteBytes(temp, idSize + 1);
      if (isComplex)
      {
        WriteNumber(coder.NumStreams);
        WriteNumber(1); // NumOutStreams;
>>>>>>> upstream/master
      }
      if (propsSize == 0)
        continue;
      WriteNumber(propsSize);
      WriteBytes(coder.Props, propsSize);
    }
  }
<<<<<<< HEAD
  for (i = 0; i < folder.BindPairs.Size(); i++)
  {
    const CBindPair &bindPair = folder.BindPairs[i];
    WriteNumber(bindPair.InIndex);
    WriteNumber(bindPair.OutIndex);
  }
  if (folder.PackStreams.Size() > 1)
    for (i = 0; i < folder.PackStreams.Size(); i++)
    {
      WriteNumber(folder.PackStreams[i]);
    }
=======
  
  for (i = 0; i < folder.Bonds.Size(); i++)
  {
    const CBond &bond = folder.Bonds[i];
    WriteNumber(bond.PackIndex);
    WriteNumber(bond.UnpackIndex);
  }
  
  if (folder.PackStreams.Size() > 1)
    for (i = 0; i < folder.PackStreams.Size(); i++)
      WriteNumber(folder.PackStreams[i]);
>>>>>>> upstream/master
}

void COutArchive::WriteBoolVector(const CBoolVector &boolVector)
{
  Byte b = 0;
  Byte mask = 0x80;
<<<<<<< HEAD
  for (int i = 0; i < boolVector.Size(); i++)
=======
  FOR_VECTOR (i, boolVector)
>>>>>>> upstream/master
  {
    if (boolVector[i])
      b |= mask;
    mask >>= 1;
    if (mask == 0)
    {
      WriteByte(b);
      mask = 0x80;
      b = 0;
    }
  }
  if (mask != 0x80)
    WriteByte(b);
}

<<<<<<< HEAD

void COutArchive::WriteHashDigests(
    const CRecordVector<bool> &digestsDefined,
    const CRecordVector<UInt32> &digests)
{
  int numDefined = 0;
  int i;
  for (i = 0; i < digestsDefined.Size(); i++)
    if (digestsDefined[i])
=======
static inline unsigned Bv_GetSizeInBytes(const CBoolVector &v) { return ((unsigned)v.Size() + 7) / 8; }

void COutArchive::WritePropBoolVector(Byte id, const CBoolVector &boolVector)
{
  WriteByte(id);
  WriteNumber(Bv_GetSizeInBytes(boolVector));
  WriteBoolVector(boolVector);
}

void COutArchive::WriteHashDigests(const CUInt32DefVector &digests)
{
  unsigned numDefined = 0;
  unsigned i;
  for (i = 0; i < digests.Defs.Size(); i++)
    if (digests.Defs[i])
>>>>>>> upstream/master
      numDefined++;
  if (numDefined == 0)
    return;

  WriteByte(NID::kCRC);
<<<<<<< HEAD
  if (numDefined == digestsDefined.Size())
=======
  if (numDefined == digests.Defs.Size())
>>>>>>> upstream/master
    WriteByte(1);
  else
  {
    WriteByte(0);
<<<<<<< HEAD
    WriteBoolVector(digestsDefined);
  }
  for (i = 0; i < digests.Size(); i++)
    if (digestsDefined[i])
      WriteUInt32(digests[i]);
=======
    WriteBoolVector(digests.Defs);
  }
  for (i = 0; i < digests.Defs.Size(); i++)
    if (digests.Defs[i])
      WriteUInt32(digests.Vals[i]);
>>>>>>> upstream/master
}

void COutArchive::WritePackInfo(
    UInt64 dataOffset,
    const CRecordVector<UInt64> &packSizes,
<<<<<<< HEAD
    const CRecordVector<bool> &packCRCsDefined,
    const CRecordVector<UInt32> &packCRCs)
=======
    const CUInt32DefVector &packCRCs)
>>>>>>> upstream/master
{
  if (packSizes.IsEmpty())
    return;
  WriteByte(NID::kPackInfo);
  WriteNumber(dataOffset);
  WriteNumber(packSizes.Size());
  WriteByte(NID::kSize);
<<<<<<< HEAD
  for (int i = 0; i < packSizes.Size(); i++)
    WriteNumber(packSizes[i]);

  WriteHashDigests(packCRCsDefined, packCRCs);
=======
  FOR_VECTOR (i, packSizes)
    WriteNumber(packSizes[i]);

  WriteHashDigests(packCRCs);
>>>>>>> upstream/master
  
  WriteByte(NID::kEnd);
}

<<<<<<< HEAD
void COutArchive::WriteUnpackInfo(const CObjectVector<CFolder> &folders)
=======
void COutArchive::WriteUnpackInfo(const CObjectVector<CFolder> &folders, const COutFolders &outFolders)
>>>>>>> upstream/master
{
  if (folders.IsEmpty())
    return;

  WriteByte(NID::kUnpackInfo);

  WriteByte(NID::kFolder);
  WriteNumber(folders.Size());
  {
    WriteByte(0);
<<<<<<< HEAD
    for (int i = 0; i < folders.Size(); i++)
=======
    FOR_VECTOR (i, folders)
>>>>>>> upstream/master
      WriteFolder(folders[i]);
  }
  
  WriteByte(NID::kCodersUnpackSize);
<<<<<<< HEAD
  int i;
  for (i = 0; i < folders.Size(); i++)
  {
    const CFolder &folder = folders[i];
    for (int j = 0; j < folder.UnpackSizes.Size(); j++)
      WriteNumber(folder.UnpackSizes[j]);
  }

  CRecordVector<bool> unpackCRCsDefined;
  CRecordVector<UInt32> unpackCRCs;
  for (i = 0; i < folders.Size(); i++)
  {
    const CFolder &folder = folders[i];
    unpackCRCsDefined.Add(folder.UnpackCRCDefined);
    unpackCRCs.Add(folder.UnpackCRC);
  }
  WriteHashDigests(unpackCRCsDefined, unpackCRCs);

  WriteByte(NID::kEnd);
}

void COutArchive::WriteSubStreamsInfo(
    const CObjectVector<CFolder> &folders,
    const CRecordVector<CNum> &numUnpackStreamsInFolders,
    const CRecordVector<UInt64> &unpackSizes,
    const CRecordVector<bool> &digestsDefined,
    const CRecordVector<UInt32> &digests)
{
  WriteByte(NID::kSubStreamsInfo);

  int i;
  for (i = 0; i < numUnpackStreamsInFolders.Size(); i++)
  {
=======
  FOR_VECTOR (i, outFolders.CoderUnpackSizes)
    WriteNumber(outFolders.CoderUnpackSizes[i]);
  
  WriteHashDigests(outFolders.FolderUnpackCRCs);
  
  WriteByte(NID::kEnd);
}

void COutArchive::WriteSubStreamsInfo(const CObjectVector<CFolder> &folders,
    const COutFolders &outFolders,
    const CRecordVector<UInt64> &unpackSizes,
    const CUInt32DefVector &digests)
{
  const CRecordVector<CNum> &numUnpackStreamsInFolders = outFolders.NumUnpackStreamsVector;
  WriteByte(NID::kSubStreamsInfo);

  unsigned i;
  for (i = 0; i < numUnpackStreamsInFolders.Size(); i++)
>>>>>>> upstream/master
    if (numUnpackStreamsInFolders[i] != 1)
    {
      WriteByte(NID::kNumUnpackStream);
      for (i = 0; i < numUnpackStreamsInFolders.Size(); i++)
        WriteNumber(numUnpackStreamsInFolders[i]);
      break;
    }
<<<<<<< HEAD
  }
 

  bool needFlag = true;
  CNum index = 0;
  for (i = 0; i < numUnpackStreamsInFolders.Size(); i++)
    for (CNum j = 0; j < numUnpackStreamsInFolders[i]; j++)
    {
      if (j + 1 != numUnpackStreamsInFolders[i])
      {
        if (needFlag)
          WriteByte(NID::kSize);
        needFlag = false;
        WriteNumber(unpackSizes[index]);
      }
      index++;
    }

  CRecordVector<bool> digestsDefined2;
  CRecordVector<UInt32> digests2;

  int digestIndex = 0;
  for (i = 0; i < folders.Size(); i++)
  {
    int numSubStreams = (int)numUnpackStreamsInFolders[i];
    if (numSubStreams == 1 && folders[i].UnpackCRCDefined)
      digestIndex++;
    else
      for (int j = 0; j < numSubStreams; j++, digestIndex++)
      {
        digestsDefined2.Add(digestsDefined[digestIndex]);
        digests2.Add(digests[digestIndex]);
      }
  }
  WriteHashDigests(digestsDefined2, digests2);
  WriteByte(NID::kEnd);
}

void COutArchive::SkipAlign(unsigned /* pos */, unsigned /* alignSize */)
{
  return;
}

/*
7-Zip 4.50 - 4.58 contain BUG, so they do not support .7z archives with Unknown field.

void COutArchive::SkipAlign(unsigned pos, unsigned alignSize)
{
=======
 
  for (i = 0; i < numUnpackStreamsInFolders.Size(); i++)
    if (numUnpackStreamsInFolders[i] > 1)
    {
      WriteByte(NID::kSize);
      CNum index = 0;
      for (i = 0; i < numUnpackStreamsInFolders.Size(); i++)
      {
        CNum num = numUnpackStreamsInFolders[i];
        for (CNum j = 0; j < num; j++)
        {
          if (j + 1 != num)
            WriteNumber(unpackSizes[index]);
          index++;
        }
      }
      break;
    }

  CUInt32DefVector digests2;

  unsigned digestIndex = 0;
  for (i = 0; i < folders.Size(); i++)
  {
    unsigned numSubStreams = (unsigned)numUnpackStreamsInFolders[i];
    if (numSubStreams == 1 && outFolders.FolderUnpackCRCs.ValidAndDefined(i))
      digestIndex++;
    else
      for (unsigned j = 0; j < numSubStreams; j++, digestIndex++)
      {
        digests2.Defs.Add(digests.Defs[digestIndex]);
        digests2.Vals.Add(digests.Vals[digestIndex]);
      }
  }
  WriteHashDigests(digests2);
  WriteByte(NID::kEnd);
}

// 7-Zip 4.50 - 4.58 contain BUG, so they do not support .7z archives with Unknown field.

void COutArchive::SkipAlign(unsigned pos, unsigned alignSize)
{
  if (!_useAlign)
    return;
>>>>>>> upstream/master
  pos += (unsigned)GetPos();
  pos &= (alignSize - 1);
  if (pos == 0)
    return;
  unsigned skip = alignSize - pos;
  if (skip < 2)
    skip += alignSize;
  skip -= 2;
  WriteByte(NID::kDummy);
  WriteByte((Byte)skip);
  for (unsigned i = 0; i < skip; i++)
    WriteByte(0);
}
<<<<<<< HEAD
*/

static inline unsigned Bv_GetSizeInBytes(const CBoolVector &v) { return ((unsigned)v.Size() + 7) / 8; }

void COutArchive::WriteAlignedBoolHeader(const CBoolVector &v, int numDefined, Byte type, unsigned itemSize)
=======

void COutArchive::WriteAlignedBoolHeader(const CBoolVector &v, unsigned numDefined, Byte type, unsigned itemSize)
>>>>>>> upstream/master
{
  const unsigned bvSize = (numDefined == v.Size()) ? 0 : Bv_GetSizeInBytes(v);
  const UInt64 dataSize = (UInt64)numDefined * itemSize + bvSize + 2;
  SkipAlign(3 + (unsigned)bvSize + (unsigned)GetBigNumberSize(dataSize), itemSize);

  WriteByte(type);
  WriteNumber(dataSize);
  if (numDefined == v.Size())
    WriteByte(1);
  else
  {
    WriteByte(0);
    WriteBoolVector(v);
  }
  WriteByte(0);
}

void COutArchive::WriteUInt64DefVector(const CUInt64DefVector &v, Byte type)
{
<<<<<<< HEAD
  int numDefined = 0;

  int i;
  for (i = 0; i < v.Defined.Size(); i++)
    if (v.Defined[i])
=======
  unsigned numDefined = 0;

  unsigned i;
  for (i = 0; i < v.Defs.Size(); i++)
    if (v.Defs[i])
>>>>>>> upstream/master
      numDefined++;

  if (numDefined == 0)
    return;

<<<<<<< HEAD
  WriteAlignedBoolHeader(v.Defined, numDefined, type, 8);
  
  for (i = 0; i < v.Defined.Size(); i++)
    if (v.Defined[i])
      WriteUInt64(v.Values[i]);
=======
  WriteAlignedBoolHeader(v.Defs, numDefined, type, 8);
  
  for (i = 0; i < v.Defs.Size(); i++)
    if (v.Defs[i])
      WriteUInt64(v.Vals[i]);
>>>>>>> upstream/master
}

HRESULT COutArchive::EncodeStream(
    DECL_EXTERNAL_CODECS_LOC_VARS
    CEncoder &encoder, const CByteBuffer &data,
<<<<<<< HEAD
    CRecordVector<UInt64> &packSizes, CObjectVector<CFolder> &folders)
{
  CBufInStream *streamSpec = new CBufInStream;
  CMyComPtr<ISequentialInStream> stream = streamSpec;
  streamSpec->Init(data, data.GetCapacity());
  CFolder folderItem;
  folderItem.UnpackCRCDefined = true;
  folderItem.UnpackCRC = CrcCalc(data, data.GetCapacity());
  UInt64 dataSize64 = data.GetCapacity();
  RINOK(encoder.Encode(
      EXTERNAL_CODECS_LOC_VARS
      stream, NULL, &dataSize64, folderItem, SeqStream, packSizes, NULL))
  folders.Add(folderItem);
=======
    CRecordVector<UInt64> &packSizes, CObjectVector<CFolder> &folders, COutFolders &outFolders)
{
  CBufInStream *streamSpec = new CBufInStream;
  CMyComPtr<ISequentialInStream> stream = streamSpec;
  streamSpec->Init(data, data.Size());
  outFolders.FolderUnpackCRCs.Defs.Add(true);
  outFolders.FolderUnpackCRCs.Vals.Add(CrcCalc(data, data.Size()));
  // outFolders.NumUnpackStreamsVector.Add(1);
  UInt64 dataSize64 = data.Size();
  UInt64 unpackSize;
  RINOK(encoder.Encode(
      EXTERNAL_CODECS_LOC_VARS
      stream,
      // NULL,
      &dataSize64,
      folders.AddNew(), outFolders.CoderUnpackSizes, unpackSize, SeqStream, packSizes, NULL))
>>>>>>> upstream/master
  return S_OK;
}

void COutArchive::WriteHeader(
<<<<<<< HEAD
    const CArchiveDatabase &db,
    const CHeaderOptions &headerOptions,
    UInt64 &headerOffset)
{
  int i;
  
  UInt64 packedSize = 0;
  for (i = 0; i < db.PackSizes.Size(); i++)
    packedSize += db.PackSizes[i];

  headerOffset = packedSize;
=======
    const CArchiveDatabaseOut &db,
    // const CHeaderOptions &headerOptions,
    UInt64 &headerOffset)
{
  /*
  bool thereIsSecure = (db.SecureBuf.Size() != 0);
  */
  _useAlign = true;

  {
    UInt64 packSize = 0;
    FOR_VECTOR (i, db.PackSizes)
      packSize += db.PackSizes[i];
    headerOffset = packSize;
  }

>>>>>>> upstream/master

  WriteByte(NID::kHeader);

  // Archive Properties

  if (db.Folders.Size() > 0)
  {
    WriteByte(NID::kMainStreamsInfo);
<<<<<<< HEAD
    WritePackInfo(0, db.PackSizes,
        db.PackCRCsDefined,
        db.PackCRCs);

    WriteUnpackInfo(db.Folders);

    CRecordVector<UInt64> unpackSizes;
    CRecordVector<bool> digestsDefined;
    CRecordVector<UInt32> digests;
    for (i = 0; i < db.Files.Size(); i++)
=======
    WritePackInfo(0, db.PackSizes, db.PackCRCs);
    WriteUnpackInfo(db.Folders, (const COutFolders &)db);

    CRecordVector<UInt64> unpackSizes;
    CUInt32DefVector digests;
    FOR_VECTOR (i, db.Files)
>>>>>>> upstream/master
    {
      const CFileItem &file = db.Files[i];
      if (!file.HasStream)
        continue;
      unpackSizes.Add(file.Size);
<<<<<<< HEAD
      digestsDefined.Add(file.CrcDefined);
      digests.Add(file.Crc);
    }

    WriteSubStreamsInfo(
        db.Folders,
        db.NumUnpackStreamsVector,
        unpackSizes,
        digestsDefined,
        digests);
=======
      digests.Defs.Add(file.CrcDefined);
      digests.Vals.Add(file.Crc);
    }

    WriteSubStreamsInfo(db.Folders, (const COutFolders &)db, unpackSizes, digests);
>>>>>>> upstream/master
    WriteByte(NID::kEnd);
  }

  if (db.Files.IsEmpty())
  {
    WriteByte(NID::kEnd);
    return;
  }

  WriteByte(NID::kFilesInfo);
  WriteNumber(db.Files.Size());

  {
<<<<<<< HEAD
  /* ---------- Empty Streams ---------- */
  CBoolVector emptyStreamVector;
  emptyStreamVector.Reserve(db.Files.Size());
  int numEmptyStreams = 0;
  for (i = 0; i < db.Files.Size(); i++)
    if (db.Files[i].HasStream)
      emptyStreamVector.Add(false);
    else
    {
      emptyStreamVector.Add(true);
      numEmptyStreams++;
    }
  if (numEmptyStreams > 0)
  {
    WriteByte(NID::kEmptyStream);
    WriteNumber(Bv_GetSizeInBytes(emptyStreamVector));
    WriteBoolVector(emptyStreamVector);

    CBoolVector emptyFileVector, antiVector;
    emptyFileVector.Reserve(numEmptyStreams);
    antiVector.Reserve(numEmptyStreams);
    CNum numEmptyFiles = 0, numAntiItems = 0;
    for (i = 0; i < db.Files.Size(); i++)
    {
      const CFileItem &file = db.Files[i];
      if (!file.HasStream)
      {
        emptyFileVector.Add(!file.IsDir);
        if (!file.IsDir)
          numEmptyFiles++;
        bool isAnti = db.IsItemAnti(i);
        antiVector.Add(isAnti);
        if (isAnti)
          numAntiItems++;
      }
    }

    if (numEmptyFiles > 0)
    {
      WriteByte(NID::kEmptyFile);
      WriteNumber(Bv_GetSizeInBytes(emptyFileVector));
      WriteBoolVector(emptyFileVector);
    }

    if (numAntiItems > 0)
    {
      WriteByte(NID::kAnti);
      WriteNumber(Bv_GetSizeInBytes(antiVector));
      WriteBoolVector(antiVector);
    }
  }
  }
=======
    /* ---------- Empty Streams ---------- */
    CBoolVector emptyStreamVector;
    emptyStreamVector.ClearAndSetSize(db.Files.Size());
    unsigned numEmptyStreams = 0;
    {
      FOR_VECTOR (i, db.Files)
        if (db.Files[i].HasStream)
          emptyStreamVector[i] = false;
        else
        {
          emptyStreamVector[i] = true;
          numEmptyStreams++;
        }
    }

    if (numEmptyStreams != 0)
    {
      WritePropBoolVector(NID::kEmptyStream, emptyStreamVector);
      
      CBoolVector emptyFileVector, antiVector;
      emptyFileVector.ClearAndSetSize(numEmptyStreams);
      antiVector.ClearAndSetSize(numEmptyStreams);
      bool thereAreEmptyFiles = false, thereAreAntiItems = false;
      unsigned cur = 0;
      
      FOR_VECTOR (i, db.Files)
      {
        const CFileItem &file = db.Files[i];
        if (file.HasStream)
          continue;
        emptyFileVector[cur] = !file.IsDir;
        if (!file.IsDir)
          thereAreEmptyFiles = true;
        bool isAnti = db.IsItemAnti(i);
        antiVector[cur] = isAnti;
        if (isAnti)
          thereAreAntiItems = true;
        cur++;
      }
      
      if (thereAreEmptyFiles)
        WritePropBoolVector(NID::kEmptyFile, emptyFileVector);
      if (thereAreAntiItems)
        WritePropBoolVector(NID::kAnti, antiVector);
    }
  }
>>>>>>> upstream/master


  {
    /* ---------- Names ---------- */
    
<<<<<<< HEAD
    int numDefined = 0;
    size_t namesDataSize = 0;
    for (int i = 0; i < db.Files.Size(); i++)
    {
      const UString &name = db.Files[i].Name;
      if (!name.IsEmpty())
        numDefined++;
      namesDataSize += (name.Length() + 1) * 2;
=======
    unsigned numDefined = 0;
    size_t namesDataSize = 0;
    FOR_VECTOR (i, db.Files)
    {
      const UString &name = db.Names[i];
      if (!name.IsEmpty())
        numDefined++;
      namesDataSize += (name.Len() + 1) * 2;
>>>>>>> upstream/master
    }
    
    if (numDefined > 0)
    {
      namesDataSize++;
<<<<<<< HEAD
      SkipAlign(2 + GetBigNumberSize(namesDataSize), 2);
=======
      SkipAlign(2 + GetBigNumberSize(namesDataSize), 16);
>>>>>>> upstream/master

      WriteByte(NID::kName);
      WriteNumber(namesDataSize);
      WriteByte(0);
<<<<<<< HEAD
      for (int i = 0; i < db.Files.Size(); i++)
      {
        const UString &name = db.Files[i].Name;
        for (int t = 0; t <= name.Length(); t++)
=======
      FOR_VECTOR (i, db.Files)
      {
        const UString &name = db.Names[i];
        for (unsigned t = 0; t <= name.Len(); t++)
>>>>>>> upstream/master
        {
          wchar_t c = name[t];
          WriteByte((Byte)c);
          WriteByte((Byte)(c >> 8));
        }
      }
    }
  }

<<<<<<< HEAD
  if (headerOptions.WriteCTime) WriteUInt64DefVector(db.CTime, NID::kCTime);
  if (headerOptions.WriteATime) WriteUInt64DefVector(db.ATime, NID::kATime);
  if (headerOptions.WriteMTime) WriteUInt64DefVector(db.MTime, NID::kMTime);
=======
  /* if (headerOptions.WriteCTime) */ WriteUInt64DefVector(db.CTime, NID::kCTime);
  /* if (headerOptions.WriteATime) */ WriteUInt64DefVector(db.ATime, NID::kATime);
  /* if (headerOptions.WriteMTime) */ WriteUInt64DefVector(db.MTime, NID::kMTime);
>>>>>>> upstream/master
  WriteUInt64DefVector(db.StartPos, NID::kStartPos);
  
  {
    /* ---------- Write Attrib ---------- */
    CBoolVector boolVector;
<<<<<<< HEAD
    boolVector.Reserve(db.Files.Size());
    int numDefined = 0;
    for (i = 0; i < db.Files.Size(); i++)
    {
      bool defined = db.Files[i].AttribDefined;
      boolVector.Add(defined);
      if (defined)
        numDefined++;
    }
    if (numDefined > 0)
    {
      WriteAlignedBoolHeader(boolVector, numDefined, NID::kWinAttributes, 4);
      for (i = 0; i < db.Files.Size(); i++)
      {
        const CFileItem &file = db.Files[i];
        if (file.AttribDefined)
          WriteUInt32(file.Attrib);
=======
    boolVector.ClearAndSetSize(db.Files.Size());
    unsigned numDefined = 0;
    
    {
      FOR_VECTOR (i, db.Files)
      {
        bool defined = db.Files[i].AttribDefined;
        boolVector[i] = defined;
        if (defined)
          numDefined++;
      }
    }
    
    if (numDefined != 0)
    {
      WriteAlignedBoolHeader(boolVector, numDefined, NID::kWinAttrib, 4);
      FOR_VECTOR (i, db.Files)
      {
        const CFileItem &file = db.Files[i];
        if (file.AttribDefined)
          WriteUInt32(file.Attrib);
      }
    }
  }

  /*
  {
    // ---------- Write IsAux ----------
    unsigned numAux = 0;
    const CBoolVector &isAux = db.IsAux;
    for (i = 0; i < isAux.Size(); i++)
      if (isAux[i])
        numAux++;
    if (numAux > 0)
    {
      const unsigned bvSize = Bv_GetSizeInBytes(isAux);
      WriteByte(NID::kIsAux);
      WriteNumber(bvSize);
      WriteBoolVector(isAux);
    }
  }

  {
    // ---------- Write Parent ----------
    CBoolVector boolVector;
    boolVector.Reserve(db.Files.Size());
    unsigned numIsDir = 0;
    unsigned numParentLinks = 0;
    for (i = 0; i < db.Files.Size(); i++)
    {
      const CFileItem &file = db.Files[i];
      bool defined = !file.IsAltStream;
      boolVector.Add(defined);
      if (defined)
        numIsDir++;
      if (file.Parent >= 0)
        numParentLinks++;
    }
    if (numParentLinks > 0)
    {
      // WriteAlignedBoolHeader(boolVector, numDefined, NID::kParent, 4);
      const unsigned bvSize = (numIsDir == boolVector.Size()) ? 0 : Bv_GetSizeInBytes(boolVector);
      const UInt64 dataSize = (UInt64)db.Files.Size() * 4 + bvSize + 1;
      SkipAlign(2 + (unsigned)bvSize + (unsigned)GetBigNumberSize(dataSize), 4);
      
      WriteByte(NID::kParent);
      WriteNumber(dataSize);
      if (numIsDir == boolVector.Size())
        WriteByte(1);
      else
      {
        WriteByte(0);
        WriteBoolVector(boolVector);
      }
      for (i = 0; i < db.Files.Size(); i++)
      {
        const CFileItem &file = db.Files[i];
        // if (file.Parent >= 0)
          WriteUInt32(file.Parent);
>>>>>>> upstream/master
      }
    }
  }

<<<<<<< HEAD
=======
  if (thereIsSecure)
  {
    UInt64 secureDataSize = 1 + 4 +
       db.SecureBuf.Size() +
       db.SecureSizes.Size() * 4;
    // secureDataSize += db.SecureIDs.Size() * 4;
    for (i = 0; i < db.SecureIDs.Size(); i++)
      secureDataSize += GetBigNumberSize(db.SecureIDs[i]);
    SkipAlign(2 + GetBigNumberSize(secureDataSize), 4);
    WriteByte(NID::kNtSecure);
    WriteNumber(secureDataSize);
    WriteByte(0);
    WriteUInt32(db.SecureSizes.Size());
    for (i = 0; i < db.SecureSizes.Size(); i++)
      WriteUInt32(db.SecureSizes[i]);
    WriteBytes(db.SecureBuf, db.SecureBuf.Size());
    for (i = 0; i < db.SecureIDs.Size(); i++)
    {
      WriteNumber(db.SecureIDs[i]);
      // WriteUInt32(db.SecureIDs[i]);
    }
  }
  */

>>>>>>> upstream/master
  WriteByte(NID::kEnd); // for files
  WriteByte(NID::kEnd); // for headers
}

HRESULT COutArchive::WriteDatabase(
    DECL_EXTERNAL_CODECS_LOC_VARS
<<<<<<< HEAD
    const CArchiveDatabase &db,
=======
    const CArchiveDatabaseOut &db,
>>>>>>> upstream/master
    const CCompressionMethodMode *options,
    const CHeaderOptions &headerOptions)
{
  if (!db.CheckNumFiles())
    return E_FAIL;

  UInt64 headerOffset;
  UInt32 headerCRC;
  UInt64 headerSize;
  if (db.IsEmpty())
  {
    headerSize = 0;
    headerOffset = 0;
    headerCRC = CrcCalc(0, 0);
  }
  else
  {
    bool encodeHeaders = false;
    if (options != 0)
      if (options->IsEmpty())
        options = 0;
    if (options != 0)
      if (options->PasswordIsDefined || headerOptions.CompressMainHeader)
        encodeHeaders = true;

    _outByte.SetStream(SeqStream);
    _outByte.Init();
    _crc = CRC_INIT_VAL;
    _countMode = encodeHeaders;
    _writeToStream = true;
    _countSize = 0;
<<<<<<< HEAD
    WriteHeader(db, headerOptions, headerOffset);

    if (encodeHeaders)
    {
      CByteBuffer buf;
      buf.SetCapacity(_countSize);
=======
    WriteHeader(db, /* headerOptions, */ headerOffset);

    if (encodeHeaders)
    {
      CByteBuffer buf(_countSize);
>>>>>>> upstream/master
      _outByte2.Init((Byte *)buf, _countSize);
      
      _countMode = false;
      _writeToStream = false;
<<<<<<< HEAD
      WriteHeader(db, headerOptions, headerOffset);
=======
      WriteHeader(db, /* headerOptions, */ headerOffset);
>>>>>>> upstream/master
      
      if (_countSize != _outByte2.GetPos())
        return E_FAIL;

      CCompressionMethodMode encryptOptions;
      encryptOptions.PasswordIsDefined = options->PasswordIsDefined;
      encryptOptions.Password = options->Password;
      CEncoder encoder(headerOptions.CompressMainHeader ? *options : encryptOptions);
      CRecordVector<UInt64> packSizes;
      CObjectVector<CFolder> folders;
<<<<<<< HEAD
      RINOK(EncodeStream(
          EXTERNAL_CODECS_LOC_VARS
          encoder, buf,
          packSizes, folders));
=======
      COutFolders outFolders;

      RINOK(EncodeStream(
          EXTERNAL_CODECS_LOC_VARS
          encoder, buf,
          packSizes, folders, outFolders));
>>>>>>> upstream/master

      _writeToStream = true;
      
      if (folders.Size() == 0)
        throw 1;

      WriteID(NID::kEncodedHeader);
<<<<<<< HEAD
      WritePackInfo(headerOffset, packSizes,
        CRecordVector<bool>(), CRecordVector<UInt32>());
      WriteUnpackInfo(folders);
      WriteByte(NID::kEnd);
      for (int i = 0; i < packSizes.Size(); i++)
=======
      WritePackInfo(headerOffset, packSizes, CUInt32DefVector());
      WriteUnpackInfo(folders, outFolders);
      WriteByte(NID::kEnd);
      FOR_VECTOR (i, packSizes)
>>>>>>> upstream/master
        headerOffset += packSizes[i];
    }
    RINOK(_outByte.Flush());
    headerCRC = CRC_GET_DIGEST(_crc);
    headerSize = _outByte.GetProcessedSize();
  }
  #ifdef _7Z_VOL
  if (_endMarker)
  {
    CFinishHeader h;
    h.NextHeaderSize = headerSize;
    h.NextHeaderCRC = headerCRC;
    h.NextHeaderOffset =
        UInt64(0) - (headerSize +
        4 + kFinishHeaderSize);
    h.ArchiveStartOffset = h.NextHeaderOffset - headerOffset;
    h.AdditionalStartBlockSize = 0;
    RINOK(WriteFinishHeader(h));
    return WriteFinishSignature();
  }
  else
  #endif
  {
    CStartHeader h;
    h.NextHeaderSize = headerSize;
    h.NextHeaderCRC = headerCRC;
    h.NextHeaderOffset = headerOffset;
    RINOK(Stream->Seek(_prefixHeaderPos, STREAM_SEEK_SET, NULL));
    return WriteStartHeader(h);
  }
}

<<<<<<< HEAD
void CArchiveDatabase::GetFile(int index, CFileItem &file, CFileItem2 &file2) const
{
  file = Files[index];
  file2.CTimeDefined = CTime.GetItem(index, file2.CTime);
  file2.ATimeDefined = ATime.GetItem(index, file2.ATime);
  file2.MTimeDefined = MTime.GetItem(index, file2.MTime);
  file2.StartPosDefined = StartPos.GetItem(index, file2.StartPos);
  file2.IsAnti = IsItemAnti(index);
}

void CArchiveDatabase::AddFile(const CFileItem &file, const CFileItem2 &file2)
{
  int index = Files.Size();
=======
void CUInt64DefVector::SetItem(unsigned index, bool defined, UInt64 value)
{
  while (index >= Defs.Size())
    Defs.Add(false);
  Defs[index] = defined;
  if (!defined)
    return;
  while (index >= Vals.Size())
    Vals.Add(0);
  Vals[index] = value;
}

void CArchiveDatabaseOut::AddFile(const CFileItem &file, const CFileItem2 &file2, const UString &name)
{
  unsigned index = Files.Size();
>>>>>>> upstream/master
  CTime.SetItem(index, file2.CTimeDefined, file2.CTime);
  ATime.SetItem(index, file2.ATimeDefined, file2.ATime);
  MTime.SetItem(index, file2.MTimeDefined, file2.MTime);
  StartPos.SetItem(index, file2.StartPosDefined, file2.StartPos);
<<<<<<< HEAD
  SetItemAnti(index, file2.IsAnti);
=======
  SetItem_Anti(index, file2.IsAnti);
  // SetItem_Aux(index, file2.IsAux);
  Names.Add(name);
>>>>>>> upstream/master
  Files.Add(file);
}

}}
