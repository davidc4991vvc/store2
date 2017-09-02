// Windows/FileDir.h

#ifndef __WINDOWS_FILE_DIR_H
#define __WINDOWS_FILE_DIR_H

#include "../Common/MyString.h"
<<<<<<< HEAD
=======

>>>>>>> upstream/master
#include "FileIO.h"

namespace NWindows {
namespace NFile {
<<<<<<< HEAD
namespace NDirectory {

#ifdef WIN_LONG_PATH
bool GetLongPaths(CFSTR s1, CFSTR s2, UString &d1, UString &d2);
#endif

bool MyGetWindowsDirectory(FString &path);
bool MyGetSystemDirectory(FString &path);

bool SetDirTime(CFSTR fileName, const FILETIME *cTime, const FILETIME *aTime, const FILETIME *mTime);
bool MySetFileAttributes(CFSTR fileName, DWORD fileAttributes);
bool MyMoveFile(CFSTR existFileName, CFSTR newFileName);
bool MyRemoveDirectory(CFSTR path);
bool MyCreateDirectory(CFSTR path);
bool CreateComplexDirectory(CFSTR path);
bool DeleteFileAlways(CFSTR name);
bool RemoveDirectoryWithSubItems(const FString &path);
=======
namespace NDir {

bool GetWindowsDir(FString &path);
bool GetSystemDir(FString &path);

bool SetDirTime(CFSTR path, const FILETIME *cTime, const FILETIME *aTime, const FILETIME *mTime);
bool SetFileAttrib(CFSTR path, DWORD attrib);
bool MyMoveFile(CFSTR existFileName, CFSTR newFileName);

#ifndef UNDER_CE
bool MyCreateHardLink(CFSTR newFileName, CFSTR existFileName);
#endif

bool RemoveDir(CFSTR path);
bool CreateDir(CFSTR path);

/* CreateComplexDir returns true, if directory can contain files after the call (two cases):
    1) the directory already exists (network shares and drive paths are supported)
    2) the directory was created
  path can be WITH or WITHOUT trailing path separator. */

bool CreateComplexDir(CFSTR path);

bool DeleteFileAlways(CFSTR name);
bool RemoveDirWithSubItems(const FString &path);
>>>>>>> upstream/master

bool MyGetFullPathName(CFSTR path, FString &resFullPath);
bool GetFullPathAndSplit(CFSTR path, FString &resDirPrefix, FString &resFileName);
bool GetOnlyDirPrefix(CFSTR path, FString &resDirPrefix);

#ifndef UNDER_CE

<<<<<<< HEAD
bool MySetCurrentDirectory(CFSTR path);
bool MyGetCurrentDirectory(FString &resultPath);
=======
bool SetCurrentDir(CFSTR path);
bool GetCurrentDir(FString &resultPath);
>>>>>>> upstream/master

#endif

bool MyGetTempPath(FString &resultPath);

class CTempFile
{
  bool _mustBeDeleted;
  FString _path;
  void DisableDeleting() { _mustBeDeleted = false; }
public:
  CTempFile(): _mustBeDeleted(false) {}
  ~CTempFile() { Remove(); }
  const FString &GetPath() const { return _path; }
  bool Create(CFSTR pathPrefix, NIO::COutFile *outFile); // pathPrefix is not folder prefix
  bool CreateRandomInTempFolder(CFSTR namePrefix, NIO::COutFile *outFile);
  bool Remove();
  bool MoveTo(CFSTR name, bool deleteDestBefore);
};

class CTempDir
{
  bool _mustBeDeleted;
  FString _path;
public:
  CTempDir(): _mustBeDeleted(false) {}
  ~CTempDir() { Remove();  }
  const FString &GetPath() const { return _path; }
  void DisableDeleting() { _mustBeDeleted = false; }
  bool Create(CFSTR namePrefix) ;
  bool Remove();
};

<<<<<<< HEAD
=======
#if !defined(UNDER_CE)
class CCurrentDirRestorer
{
  FString _path;
public:
  bool NeedRestore;

  CCurrentDirRestorer(): NeedRestore(true)
  {
    GetCurrentDir(_path);
  }
  ~CCurrentDirRestorer()
  {
    if (!NeedRestore)
      return;
    FString s;
    if (GetCurrentDir(s))
      if (s != _path)
        SetCurrentDir(_path);
  }
};
#endif

>>>>>>> upstream/master
}}}

#endif
