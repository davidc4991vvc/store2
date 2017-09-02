// Windows/FileIO.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include "FileIO.h"
=======
#ifdef SUPPORT_DEVICE_FILE
#include "../../C/Alloc.h"
#endif

#include "FileIO.h"
#include "FileName.h"
>>>>>>> upstream/master

#ifndef _UNICODE
extern bool g_IsNT;
#endif

<<<<<<< HEAD
=======
using namespace NWindows;
using namespace NFile;
using namespace NName;

>>>>>>> upstream/master
namespace NWindows {
namespace NFile {

#ifdef SUPPORT_DEVICE_FILE

<<<<<<< HEAD
bool IsDeviceName(CFSTR n)
{
  #ifdef UNDER_CE
  int len = (int)MyStringLen(n);
  if (len < 5 || len > 5 || memcmp(n, FTEXT("DSK"), 3 * sizeof(FCHAR)) != 0)
    return false;
  if (n[4] != ':')
    return false;
  // for reading use SG_REQ sg; if (DeviceIoControl(dsk, IOCTL_DISK_READ));
  #else
  if (n[0] != '\\' || n[1] != '\\' || n[2] != '.' ||  n[3] != '\\')
    return false;
  int len = (int)MyStringLen(n);
  if (len == 6 && n[5] == ':')
    return true;
  if (len < 18 || len > 22 || memcmp(n + 4, FTEXT("PhysicalDrive"), 13 * sizeof(FCHAR)) != 0)
    return false;
  for (int i = 17; i < len; i++)
    if (n[i] < '0' || n[i] > '9')
      return false;
  #endif
  return true;
}

#endif

#if defined(WIN_LONG_PATH) && defined(_UNICODE)
#define WIN_LONG_PATH2
#endif

#ifdef WIN_LONG_PATH
bool GetLongPathBase(CFSTR s, UString &res)
{
  res.Empty();
  int len = MyStringLen(s);
  FChar c = s[0];
  if (len < 1 || c == '\\' || c == '.' && (len == 1 || len == 2 && s[1] == '.'))
    return true;
  UString curDir;
  bool isAbs = false;
  if (len > 3)
    isAbs = (s[1] == ':' && s[2] == '\\' && (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'));

  if (!isAbs)
  {
    WCHAR temp[MAX_PATH + 2];
    temp[0] = 0;
    DWORD needLength = ::GetCurrentDirectoryW(MAX_PATH + 1, temp);
    if (needLength == 0 || needLength > MAX_PATH)
      return false;
    curDir = temp;
    if (curDir.Back() != L'\\')
      curDir += L'\\';
  }
  res = UString(L"\\\\?\\") + curDir + fs2us(s);
  return true;
}

bool GetLongPath(CFSTR path, UString &longPath)
{
  if (GetLongPathBase(path, longPath))
    return !longPath.IsEmpty();
  return false;
=======
namespace NSystem
{
bool MyGetDiskFreeSpace(CFSTR rootPath, UInt64 &clusterSize, UInt64 &totalSize, UInt64 &freeSize);
>>>>>>> upstream/master
}
#endif

namespace NIO {

<<<<<<< HEAD
CFileBase::~CFileBase() { Close(); }

bool CFileBase::Create(CFSTR fileName, DWORD desiredAccess,
=======
/*
WinXP-64 CreateFile():
  ""             -  ERROR_PATH_NOT_FOUND
  :stream        -  OK
  .:stream       -  ERROR_PATH_NOT_FOUND
  .\:stream      -  OK
  
  folder\:stream -  ERROR_INVALID_NAME
  folder:stream  -  OK

  c:\:stream     -  OK

  c::stream      -  ERROR_INVALID_NAME, if current dir is NOT ROOT ( c:\dir1 )
  c::stream      -  OK,                 if current dir is ROOT     ( c:\ )
*/

bool CFileBase::Create(CFSTR path, DWORD desiredAccess,
>>>>>>> upstream/master
    DWORD shareMode, DWORD creationDisposition, DWORD flagsAndAttributes)
{
  if (!Close())
    return false;

  #ifdef SUPPORT_DEVICE_FILE
  IsDeviceFile = false;
  #endif

  #ifndef _UNICODE
  if (!g_IsNT)
  {
<<<<<<< HEAD
    _handle = ::CreateFile(fs2fas(fileName), desiredAccess, shareMode,
=======
    _handle = ::CreateFile(fs2fas(path), desiredAccess, shareMode,
>>>>>>> upstream/master
        (LPSECURITY_ATTRIBUTES)NULL, creationDisposition, flagsAndAttributes, (HANDLE)NULL);
  }
  else
  #endif
  {
<<<<<<< HEAD
    _handle = ::CreateFileW(fs2us(fileName), desiredAccess, shareMode,
        (LPSECURITY_ATTRIBUTES)NULL, creationDisposition, flagsAndAttributes, (HANDLE)NULL);
    #ifdef WIN_LONG_PATH
    if (_handle == INVALID_HANDLE_VALUE)
    {
      UString longPath;
      if (GetLongPath(fileName, longPath))
        _handle = ::CreateFileW(longPath, desiredAccess, shareMode,
=======
    IF_USE_MAIN_PATH
      _handle = ::CreateFileW(fs2us(path), desiredAccess, shareMode,
        (LPSECURITY_ATTRIBUTES)NULL, creationDisposition, flagsAndAttributes, (HANDLE)NULL);
    #ifdef WIN_LONG_PATH
    if (_handle == INVALID_HANDLE_VALUE && USE_SUPER_PATH)
    {
      UString superPath;
      if (GetSuperPath(path, superPath, USE_MAIN_PATH))
        _handle = ::CreateFileW(superPath, desiredAccess, shareMode,
>>>>>>> upstream/master
            (LPSECURITY_ATTRIBUTES)NULL, creationDisposition, flagsAndAttributes, (HANDLE)NULL);
    }
    #endif
  }
  return (_handle != INVALID_HANDLE_VALUE);
}

<<<<<<< HEAD
bool CFileBase::Close()
=======
bool CFileBase::Close() throw()
>>>>>>> upstream/master
{
  if (_handle == INVALID_HANDLE_VALUE)
    return true;
  if (!::CloseHandle(_handle))
    return false;
  _handle = INVALID_HANDLE_VALUE;
  return true;
}

<<<<<<< HEAD
bool CFileBase::GetPosition(UInt64 &position) const
=======
bool CFileBase::GetPosition(UInt64 &position) const throw()
>>>>>>> upstream/master
{
  return Seek(0, FILE_CURRENT, position);
}

<<<<<<< HEAD
bool CFileBase::GetLength(UInt64 &length) const
{
  #ifdef SUPPORT_DEVICE_FILE
  if (IsDeviceFile && LengthDefined)
  {
    length = Length;
=======
bool CFileBase::GetLength(UInt64 &length) const throw()
{
  #ifdef SUPPORT_DEVICE_FILE
  if (IsDeviceFile && SizeDefined)
  {
    length = Size;
>>>>>>> upstream/master
    return true;
  }
  #endif

  DWORD sizeHigh;
  DWORD sizeLow = ::GetFileSize(_handle, &sizeHigh);
  if (sizeLow == 0xFFFFFFFF)
    if (::GetLastError() != NO_ERROR)
      return false;
  length = (((UInt64)sizeHigh) << 32) + sizeLow;
  return true;
}

<<<<<<< HEAD
bool CFileBase::Seek(Int64 distanceToMove, DWORD moveMethod, UInt64 &newPosition) const
{
  #ifdef SUPPORT_DEVICE_FILE
  if (IsDeviceFile && LengthDefined && moveMethod == FILE_END)
  {
    distanceToMove += Length;
=======
bool CFileBase::Seek(Int64 distanceToMove, DWORD moveMethod, UInt64 &newPosition) const throw()
{
  #ifdef SUPPORT_DEVICE_FILE
  if (IsDeviceFile && SizeDefined && moveMethod == FILE_END)
  {
    distanceToMove += Size;
>>>>>>> upstream/master
    moveMethod = FILE_BEGIN;
  }
  #endif

<<<<<<< HEAD
  LARGE_INTEGER value;
  value.QuadPart = distanceToMove;
  value.LowPart = ::SetFilePointer(_handle, value.LowPart, &value.HighPart, moveMethod);
  if (value.LowPart == 0xFFFFFFFF)
    if (::GetLastError() != NO_ERROR)
      return false;
  newPosition = value.QuadPart;
  return true;
}

bool CFileBase::Seek(UInt64 position, UInt64 &newPosition)
=======
  LONG high = (LONG)(distanceToMove >> 32);
  DWORD low = ::SetFilePointer(_handle, (LONG)(distanceToMove & 0xFFFFFFFF), &high, moveMethod);
  if (low == 0xFFFFFFFF)
    if (::GetLastError() != NO_ERROR)
      return false;
  newPosition = (((UInt64)(UInt32)high) << 32) + low;
  return true;
}

bool CFileBase::Seek(UInt64 position, UInt64 &newPosition) const throw()
>>>>>>> upstream/master
{
  return Seek(position, FILE_BEGIN, newPosition);
}

<<<<<<< HEAD
bool CFileBase::SeekToBegin()
=======
bool CFileBase::SeekToBegin() const throw()
>>>>>>> upstream/master
{
  UInt64 newPosition;
  return Seek(0, newPosition);
}

<<<<<<< HEAD
bool CFileBase::SeekToEnd(UInt64 &newPosition)
=======
bool CFileBase::SeekToEnd(UInt64 &newPosition) const throw()
>>>>>>> upstream/master
{
  return Seek(0, FILE_END, newPosition);
}

<<<<<<< HEAD
/*
bool CFileBase::GetFileInformation(CByHandleFileInfo &fi) const
{
  BY_HANDLE_FILE_INFORMATION wfi;
  if (!::GetFileInformationByHandle(_handle, &wfi))
    return false;
  fi.Attrib = wfi.dwFileAttributes;
  fi.CTime = wfi.ftCreationTime;
  fi.ATime = wfi.ftLastAccessTime;
  fi.MTime = wfi.ftLastWriteTime;
  fi.Size = (((UInt64)wfi.nFileSizeHigh) << 32) + wfi.nFileSizeLow;
  fi.VolumeSerialNumber = wfi.dwVolumeSerialNumber;
  fi.NumLinks = wfi.nNumberOfLinks;
  fi.FileIndex = (((UInt64)wfi.nFileIndexHigh) << 32) + wfi.nFileIndexLow;
  return true;
}
*/

/////////////////////////
// CInFile

#ifdef SUPPORT_DEVICE_FILE
void CInFile::GetDeviceLength()
{
  if (_handle != INVALID_HANDLE_VALUE && IsDeviceFile)
  {
    #ifdef UNDER_CE
    LengthDefined = true;
    Length = 128 << 20;

    #else
    PARTITION_INFORMATION partInfo;
    LengthDefined = true;
    Length = 0;

    if (GetPartitionInfo(&partInfo))
      Length = partInfo.PartitionLength.QuadPart;
    else
    {
      DISK_GEOMETRY geom;
      if (!GetGeometry(&geom))
        if (!GetCdRomGeometry(&geom))
          LengthDefined = false;
      if (LengthDefined)
        Length = geom.Cylinders.QuadPart * geom.TracksPerCylinder * geom.SectorsPerTrack * geom.BytesPerSector;
    }
    // SeekToBegin();
    #endif
  }
=======
// ---------- CInFile ---------

#ifdef SUPPORT_DEVICE_FILE

void CInFile::CorrectDeviceSize()
{
  // maybe we must decrease kClusterSize to 1 << 12, if we want correct size at tail
  static const UInt32 kClusterSize = 1 << 14;
  UInt64 pos = Size & ~(UInt64)(kClusterSize - 1);
  UInt64 realNewPosition;
  if (!Seek(pos, realNewPosition))
    return;
  Byte *buf = (Byte *)MidAlloc(kClusterSize);

  bool needbackward = true;

  for (;;)
  {
    UInt32 processed = 0;
    // up test is slow for "PhysicalDrive".
    // processed size for latest block for "PhysicalDrive0" is 0.
    if (!Read1(buf, kClusterSize, processed))
      break;
    if (processed == 0)
      break;
    needbackward = false;
    Size = pos + processed;
    if (processed != kClusterSize)
      break;
    pos += kClusterSize;
  }

  if (needbackward && pos != 0)
  {
    pos -= kClusterSize;
    for (;;)
    {
      // break;
      if (!Seek(pos, realNewPosition))
        break;
      if (!buf)
      {
        buf = (Byte *)MidAlloc(kClusterSize);
        if (!buf)
          break;
      }
      UInt32 processed = 0;
      // that code doesn't work for "PhysicalDrive0"
      if (!Read1(buf, kClusterSize, processed))
        break;
      if (processed != 0)
      {
        Size = pos + processed;
        break;
      }
      if (pos == 0)
        break;
      pos -= kClusterSize;
    }
  }
  MidFree(buf);
}


void CInFile::CalcDeviceSize(CFSTR s)
{
  SizeDefined = false;
  Size = 0;
  if (_handle == INVALID_HANDLE_VALUE || !IsDeviceFile)
    return;
  #ifdef UNDER_CE

  SizeDefined = true;
  Size = 128 << 20;
  
  #else
  
  PARTITION_INFORMATION partInfo;
  bool needCorrectSize = true;

  /*
    WinXP 64-bit:

    HDD \\.\PhysicalDrive0 (MBR):
      GetPartitionInfo == GeometryEx :  corrrect size? (includes tail)
      Geometry   :  smaller than GeometryEx (no tail, maybe correct too?)
      MyGetDiskFreeSpace : FAIL
      Size correction is slow and block size (kClusterSize) must be small?

    HDD partition \\.\N: (NTFS):
      MyGetDiskFreeSpace   :  Size of NTFS clusters. Same size can be calculated after correction
      GetPartitionInfo     :  size of partition data: NTFS clusters + TAIL; TAIL contains extra empty sectors and copy of first sector of NTFS
      Geometry / CdRomGeometry / GeometryEx :  size of HDD (not that partition)

    CD-ROM drive (ISO):
      MyGetDiskFreeSpace   :  correct size. Same size can be calculated after correction
      Geometry == CdRomGeometry  :  smaller than corrrect size
      GetPartitionInfo == GeometryEx :  larger than corrrect size

    Floppy \\.\a: (FAT):
      Geometry :  correct size.
      CdRomGeometry / GeometryEx / GetPartitionInfo / MyGetDiskFreeSpace - FAIL
      correction works OK for FAT.
      correction works OK for non-FAT, if kClusterSize = 512.
  */

  if (GetPartitionInfo(&partInfo))
  {
    Size = partInfo.PartitionLength.QuadPart;
    SizeDefined = true;
    needCorrectSize = false;
    if ((s)[0] == '\\' && (s)[1] == '\\' && (s)[2] == '.' && (s)[3] == '\\' && (s)[5] == ':' && (s)[6] == 0)
    {
      FChar path[4] = { s[4], ':', '\\', 0 };
      UInt64 clusterSize, totalSize, freeSize;
      if (NSystem::MyGetDiskFreeSpace(path, clusterSize, totalSize, freeSize))
        Size = totalSize;
      else
        needCorrectSize = true;
    }
  }
  
  if (!SizeDefined)
  {
    my_DISK_GEOMETRY_EX geomEx;
    SizeDefined = GetGeometryEx(&geomEx);
    if (SizeDefined)
      Size = geomEx.DiskSize.QuadPart;
    else
    {
      DISK_GEOMETRY geom;
      SizeDefined = GetGeometry(&geom);
      if (!SizeDefined)
        SizeDefined = GetCdRomGeometry(&geom);
      if (SizeDefined)
        Size = geom.Cylinders.QuadPart * geom.TracksPerCylinder * geom.SectorsPerTrack * geom.BytesPerSector;
    }
  }
  
  if (needCorrectSize && SizeDefined && Size != 0)
  {
    CorrectDeviceSize();
    SeekToBegin();
  }

  // SeekToBegin();
  #endif
>>>>>>> upstream/master
}

// ((desiredAccess & (FILE_WRITE_DATA | FILE_APPEND_DATA | GENERIC_WRITE)) == 0 &&

#define MY_DEVICE_EXTRA_CODE \
<<<<<<< HEAD
  IsDeviceFile = IsDeviceName(fileName); \
  GetDeviceLength();
=======
  IsDeviceFile = IsDevicePath(fileName); \
  CalcDeviceSize(fileName);
>>>>>>> upstream/master
#else
#define MY_DEVICE_EXTRA_CODE
#endif

bool CInFile::Open(CFSTR fileName, DWORD shareMode, DWORD creationDisposition, DWORD flagsAndAttributes)
{
  bool res = Create(fileName, GENERIC_READ, shareMode, creationDisposition, flagsAndAttributes);
  MY_DEVICE_EXTRA_CODE
  return res;
}

bool CInFile::OpenShared(CFSTR fileName, bool shareForWrite)
{ return Open(fileName, FILE_SHARE_READ | (shareForWrite ? FILE_SHARE_WRITE : 0), OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL); }

bool CInFile::Open(CFSTR fileName)
  { return OpenShared(fileName, false); }

// ReadFile and WriteFile functions in Windows have BUG:
// If you Read or Write 64MB or more (probably min_failure_size = 64MB - 32KB + 1)
// from/to Network file, it returns ERROR_NO_SYSTEM_RESOURCES
// (Insufficient system resources exist to complete the requested service).

// Probably in some version of Windows there are problems with other sizes:
// for 32 MB (maybe also for 16 MB).
// And message can be "Network connection was lost"

static UInt32 kChunkSizeMax = (1 << 22);

<<<<<<< HEAD
bool CInFile::Read1(void *data, UInt32 size, UInt32 &processedSize)
=======
bool CInFile::Read1(void *data, UInt32 size, UInt32 &processedSize) throw()
>>>>>>> upstream/master
{
  DWORD processedLoc = 0;
  bool res = BOOLToBool(::ReadFile(_handle, data, size, &processedLoc, NULL));
  processedSize = (UInt32)processedLoc;
  return res;
}

<<<<<<< HEAD
bool CInFile::ReadPart(void *data, UInt32 size, UInt32 &processedSize)
=======
bool CInFile::ReadPart(void *data, UInt32 size, UInt32 &processedSize) throw()
>>>>>>> upstream/master
{
  if (size > kChunkSizeMax)
    size = kChunkSizeMax;
  return Read1(data, size, processedSize);
}

<<<<<<< HEAD
bool CInFile::Read(void *data, UInt32 size, UInt32 &processedSize)
=======
bool CInFile::Read(void *data, UInt32 size, UInt32 &processedSize) throw()
>>>>>>> upstream/master
{
  processedSize = 0;
  do
  {
    UInt32 processedLoc = 0;
    bool res = ReadPart(data, size, processedLoc);
    processedSize += processedLoc;
    if (!res)
      return false;
    if (processedLoc == 0)
      return true;
    data = (void *)((unsigned char *)data + processedLoc);
    size -= processedLoc;
  }
  while (size > 0);
  return true;
}

<<<<<<< HEAD
/////////////////////////
// COutFile
=======
// ---------- COutFile ---------
>>>>>>> upstream/master

static inline DWORD GetCreationDisposition(bool createAlways)
  { return createAlways? CREATE_ALWAYS: CREATE_NEW; }

bool COutFile::Open(CFSTR fileName, DWORD shareMode, DWORD creationDisposition, DWORD flagsAndAttributes)
  { return CFileBase::Create(fileName, GENERIC_WRITE, shareMode, creationDisposition, flagsAndAttributes); }

bool COutFile::Open(CFSTR fileName, DWORD creationDisposition)
  { return Open(fileName, FILE_SHARE_READ, creationDisposition, FILE_ATTRIBUTE_NORMAL); }

bool COutFile::Create(CFSTR fileName, bool createAlways)
  { return Open(fileName, GetCreationDisposition(createAlways)); }

<<<<<<< HEAD
bool COutFile::SetTime(const FILETIME *cTime, const FILETIME *aTime, const FILETIME *mTime)
  { return BOOLToBool(::SetFileTime(_handle, cTime, aTime, mTime)); }

bool COutFile::SetMTime(const FILETIME *mTime) {  return SetTime(NULL, NULL, mTime); }

bool COutFile::WritePart(const void *data, UInt32 size, UInt32 &processedSize)
=======
bool COutFile::CreateAlways(CFSTR fileName, DWORD flagsAndAttributes)
  { return Open(fileName, FILE_SHARE_READ, GetCreationDisposition(true), flagsAndAttributes); }

bool COutFile::SetTime(const FILETIME *cTime, const FILETIME *aTime, const FILETIME *mTime) throw()
  { return BOOLToBool(::SetFileTime(_handle, cTime, aTime, mTime)); }

bool COutFile::SetMTime(const FILETIME *mTime) throw() {  return SetTime(NULL, NULL, mTime); }

bool COutFile::WritePart(const void *data, UInt32 size, UInt32 &processedSize) throw()
>>>>>>> upstream/master
{
  if (size > kChunkSizeMax)
    size = kChunkSizeMax;
  DWORD processedLoc = 0;
  bool res = BOOLToBool(::WriteFile(_handle, data, size, &processedLoc, NULL));
  processedSize = (UInt32)processedLoc;
  return res;
}

<<<<<<< HEAD
bool COutFile::Write(const void *data, UInt32 size, UInt32 &processedSize)
=======
bool COutFile::Write(const void *data, UInt32 size, UInt32 &processedSize) throw()
>>>>>>> upstream/master
{
  processedSize = 0;
  do
  {
    UInt32 processedLoc = 0;
    bool res = WritePart(data, size, processedLoc);
    processedSize += processedLoc;
    if (!res)
      return false;
    if (processedLoc == 0)
      return true;
    data = (const void *)((const unsigned char *)data + processedLoc);
    size -= processedLoc;
  }
  while (size > 0);
  return true;
}

<<<<<<< HEAD
bool COutFile::SetEndOfFile() { return BOOLToBool(::SetEndOfFile(_handle)); }

bool COutFile::SetLength(UInt64 length)
=======
bool COutFile::SetEndOfFile() throw() { return BOOLToBool(::SetEndOfFile(_handle)); }

bool COutFile::SetLength(UInt64 length) throw()
>>>>>>> upstream/master
{
  UInt64 newPosition;
  if (!Seek(length, newPosition))
    return false;
  if (newPosition != length)
    return false;
  return SetEndOfFile();
}

}}}
