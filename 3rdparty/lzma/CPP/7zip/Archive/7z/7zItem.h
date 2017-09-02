// 7zItem.h

#ifndef __7Z_ITEM_H
#define __7Z_ITEM_H

<<<<<<< HEAD
#include "../../../Common/Buffer.h"
=======
#include "../../../Common/MyBuffer.h"
>>>>>>> upstream/master
#include "../../../Common/MyString.h"

#include "../../Common/MethodId.h"

#include "7zHeader.h"

namespace NArchive {
namespace N7z {

<<<<<<< HEAD
const UInt64 k_AES = 0x06F10701;

=======
>>>>>>> upstream/master
typedef UInt32 CNum;
const CNum kNumMax     = 0x7FFFFFFF;
const CNum kNumNoIndex = 0xFFFFFFFF;

struct CCoderInfo
{
  CMethodId MethodID;
  CByteBuffer Props;
<<<<<<< HEAD
  CNum NumInStreams;
  CNum NumOutStreams;
  bool IsSimpleCoder() const { return (NumInStreams == 1) && (NumOutStreams == 1); }
};

struct CBindPair
{
  CNum InIndex;
  CNum OutIndex;
=======
  UInt32 NumStreams;
  
  bool IsSimpleCoder() const { return NumStreams == 1; }
};

struct CBond
{
  UInt32 PackIndex;
  UInt32 UnpackIndex;
>>>>>>> upstream/master
};

struct CFolder
{
<<<<<<< HEAD
  CObjectVector<CCoderInfo> Coders;
  CRecordVector<CBindPair> BindPairs;
  CRecordVector<CNum> PackStreams;
  CRecordVector<UInt64> UnpackSizes;
  UInt32 UnpackCRC;
  bool UnpackCRCDefined;

  CFolder(): UnpackCRCDefined(false) {}

  UInt64 GetUnpackSize() const // test it
  {
    if (UnpackSizes.IsEmpty())
      return 0;
    for (int i = UnpackSizes.Size() - 1; i >= 0; i--)
      if (FindBindPairForOutStream(i) < 0)
        return UnpackSizes[i];
    throw 1;
  }

  CNum GetNumOutStreams() const
  {
    CNum result = 0;
    for (int i = 0; i < Coders.Size(); i++)
      result += Coders[i].NumOutStreams;
    return result;
  }

  int FindBindPairForInStream(CNum inStreamIndex) const
  {
    for(int i = 0; i < BindPairs.Size(); i++)
      if (BindPairs[i].InIndex == inStreamIndex)
        return i;
    return -1;
  }
  int FindBindPairForOutStream(CNum outStreamIndex) const
  {
    for(int i = 0; i < BindPairs.Size(); i++)
      if (BindPairs[i].OutIndex == outStreamIndex)
        return i;
    return -1;
  }
  int FindPackStreamArrayIndex(CNum inStreamIndex) const
  {
    for(int i = 0; i < PackStreams.Size(); i++)
      if (PackStreams[i] == inStreamIndex)
        return i;
    return -1;
  }

  bool IsEncrypted() const
  {
    for (int i = Coders.Size() - 1; i >= 0; i--)
=======
  CLASS_NO_COPY(CFolder)
public:
  CObjArray2<CCoderInfo> Coders;
  CObjArray2<CBond> Bonds;
  CObjArray2<UInt32> PackStreams;

  CFolder() {}

  bool IsDecodingSupported() const { return Coders.Size() <= 32; }

  int Find_in_PackStreams(UInt32 packStream) const
  {
    FOR_VECTOR(i, PackStreams)
      if (PackStreams[i] == packStream)
        return i;
    return -1;
  }

  int FindBond_for_PackStream(UInt32 packStream) const
  {
    FOR_VECTOR(i, Bonds)
      if (Bonds[i].PackIndex == packStream)
        return i;
    return -1;
  }
  
  /*
  int FindBond_for_UnpackStream(UInt32 unpackStream) const
  {
    FOR_VECTOR(i, Bonds)
      if (Bonds[i].UnpackIndex == unpackStream)
        return i;
    return -1;
  }

  int FindOutCoder() const
  {
    for (int i = (int)Coders.Size() - 1; i >= 0; i--)
      if (FindBond_for_UnpackStream(i) < 0)
        return i;
    return -1;
  }
  */

  bool IsEncrypted() const
  {
    FOR_VECTOR(i, Coders)
>>>>>>> upstream/master
      if (Coders[i].MethodID == k_AES)
        return true;
    return false;
  }
<<<<<<< HEAD

  bool CheckStructure() const;
=======
};

struct CUInt32DefVector
{
  CBoolVector Defs;
  CRecordVector<UInt32> Vals;

  void ClearAndSetSize(unsigned newSize)
  {
    Defs.ClearAndSetSize(newSize);
    Vals.ClearAndSetSize(newSize);
  }

  void Clear()
  {
    Defs.Clear();
    Vals.Clear();
  }

  void ReserveDown()
  {
    Defs.ReserveDown();
    Vals.ReserveDown();
  }

  bool ValidAndDefined(unsigned i) const { return i < Defs.Size() && Defs[i]; }
>>>>>>> upstream/master
};

struct CUInt64DefVector
{
<<<<<<< HEAD
  CRecordVector<UInt64> Values;
  CRecordVector<bool> Defined;
  
  void Clear()
  {
    Values.Clear();
    Defined.Clear();
=======
  CBoolVector Defs;
  CRecordVector<UInt64> Vals;
  
  void Clear()
  {
    Defs.Clear();
    Vals.Clear();
>>>>>>> upstream/master
  }
  
  void ReserveDown()
  {
<<<<<<< HEAD
    Values.ReserveDown();
    Values.ReserveDown();
  }

  bool GetItem(int index, UInt64 &value) const
  {
    if (index < Defined.Size() && Defined[index])
    {
      value = Values[index];
=======
    Defs.ReserveDown();
    Vals.ReserveDown();
  }

  bool GetItem(unsigned index, UInt64 &value) const
  {
    if (index < Defs.Size() && Defs[index])
    {
      value = Vals[index];
>>>>>>> upstream/master
      return true;
    }
    value = 0;
    return false;
  }
  
<<<<<<< HEAD
  void SetItem(int index, bool defined, UInt64 value)
  {
    while (index >= Defined.Size())
      Defined.Add(false);
    Defined[index] = defined;
    if (!defined)
      return;
    while (index >= Values.Size())
      Values.Add(0);
    Values[index] = value;
  }

  bool CheckSize(int size) const { return Defined.Size() == size || Defined.Size() == 0; }
=======
  void SetItem(unsigned index, bool defined, UInt64 value);

  bool CheckSize(unsigned size) const { return Defs.Size() == size || Defs.Size() == 0; }
>>>>>>> upstream/master
};

struct CFileItem
{
  UInt64 Size;
  UInt32 Attrib;
  UInt32 Crc;
<<<<<<< HEAD
  UString Name;

=======
  /*
  int Parent;
  bool IsAltStream;
  */
>>>>>>> upstream/master
  bool HasStream; // Test it !!! it means that there is
                  // stream in some folder. It can be empty stream
  bool IsDir;
  bool CrcDefined;
  bool AttribDefined;

  CFileItem():
<<<<<<< HEAD
=======
    /*
    Parent(-1),
    IsAltStream(false),
    */
>>>>>>> upstream/master
    HasStream(true),
    IsDir(false),
    CrcDefined(false),
    AttribDefined(false)
      {}
  void SetAttrib(UInt32 attrib)
  {
    AttribDefined = true;
    Attrib = attrib;
  }
};

<<<<<<< HEAD
struct CFileItem2
{
  UInt64 CTime;
  UInt64 ATime;
  UInt64 MTime;
  UInt64 StartPos;
  bool CTimeDefined;
  bool ATimeDefined;
  bool MTimeDefined;
  bool StartPosDefined;
  bool IsAnti;
};

struct CArchiveDatabase
{
  CRecordVector<UInt64> PackSizes;
  CRecordVector<bool> PackCRCsDefined;
  CRecordVector<UInt32> PackCRCs;
  CObjectVector<CFolder> Folders;
  CRecordVector<CNum> NumUnpackStreamsVector;
  CObjectVector<CFileItem> Files;

  CUInt64DefVector CTime;
  CUInt64DefVector ATime;
  CUInt64DefVector MTime;
  CUInt64DefVector StartPos;
  CRecordVector<bool> IsAnti;

  void Clear()
  {
    PackSizes.Clear();
    PackCRCsDefined.Clear();
    PackCRCs.Clear();
    Folders.Clear();
    NumUnpackStreamsVector.Clear();
    Files.Clear();
    CTime.Clear();
    ATime.Clear();
    MTime.Clear();
    StartPos.Clear();
    IsAnti.Clear();
  }

  void ReserveDown()
  {
    PackSizes.ReserveDown();
    PackCRCsDefined.ReserveDown();
    PackCRCs.ReserveDown();
    Folders.ReserveDown();
    NumUnpackStreamsVector.ReserveDown();
    Files.ReserveDown();
    CTime.ReserveDown();
    ATime.ReserveDown();
    MTime.ReserveDown();
    StartPos.ReserveDown();
    IsAnti.ReserveDown();
  }

  bool IsEmpty() const
  {
    return (PackSizes.IsEmpty() &&
      PackCRCsDefined.IsEmpty() &&
      PackCRCs.IsEmpty() &&
      Folders.IsEmpty() &&
      NumUnpackStreamsVector.IsEmpty() &&
      Files.IsEmpty());
  }

  bool CheckNumFiles() const
  {
    int size = Files.Size();
    return (
      CTime.CheckSize(size) &&
      ATime.CheckSize(size) &&
      MTime.CheckSize(size) &&
      StartPos.CheckSize(size) &&
      (size == IsAnti.Size() || IsAnti.Size() == 0));
  }

  bool IsSolid() const
  {
    for (int i = 0; i < NumUnpackStreamsVector.Size(); i++)
      if (NumUnpackStreamsVector[i] > 1)
        return true;
    return false;
  }
  bool IsItemAnti(int index) const { return (index < IsAnti.Size() && IsAnti[index]); }
  void SetItemAnti(int index, bool isAnti)
  {
    while (index >= IsAnti.Size())
      IsAnti.Add(false);
    IsAnti[index] = isAnti;
  }

  void GetFile(int index, CFileItem &file, CFileItem2 &file2) const;
  void AddFile(const CFileItem &file, const CFileItem2 &file2);
};

=======
>>>>>>> upstream/master
}}

#endif
