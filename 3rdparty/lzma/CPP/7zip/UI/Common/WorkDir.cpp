// WorkDir.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include "Common/StringConvert.h"
#include "Common/Wildcard.h"

#include "Windows/FileName.h"
=======
#include "../../../Common/StringConvert.h"
#include "../../../Common/Wildcard.h"

#include "../../../Windows/FileName.h"
>>>>>>> upstream/master

#include "WorkDir.h"

using namespace NWindows;
using namespace NFile;
<<<<<<< HEAD
using namespace NDirectory;
=======
using namespace NDir;
>>>>>>> upstream/master

FString GetWorkDir(const NWorkDir::CInfo &workDirInfo, const FString &path, FString &fileName)
{
  NWorkDir::NMode::EEnum mode = workDirInfo.Mode;
<<<<<<< HEAD
  #ifndef UNDER_CE
=======
  
  #if defined(_WIN32) && !defined(UNDER_CE)
>>>>>>> upstream/master
  if (workDirInfo.ForRemovableOnly)
  {
    mode = NWorkDir::NMode::kCurrent;
    FString prefix = path.Left(3);
    if (prefix[1] == FTEXT(':') && prefix[2] == FTEXT('\\'))
    {
      UINT driveType = GetDriveType(GetSystemString(prefix, ::AreFileApisANSI() ? CP_ACP : CP_OEMCP));
      if (driveType == DRIVE_CDROM || driveType == DRIVE_REMOVABLE)
        mode = workDirInfo.Mode;
    }
    /*
    CParsedPath parsedPath;
    parsedPath.ParsePath(archiveName);
    UINT driveType = GetDriveType(parsedPath.Prefix);
    if ((driveType != DRIVE_CDROM) && (driveType != DRIVE_REMOVABLE))
      mode = NZipSettings::NWorkDir::NMode::kCurrent;
    */
  }
  #endif
<<<<<<< HEAD
  int pos = path.ReverseFind(FCHAR_PATH_SEPARATOR) + 1;
  fileName = path.Mid(pos);
=======
  
  int pos = path.ReverseFind_PathSepar() + 1;
  fileName = path.Ptr(pos);
  
>>>>>>> upstream/master
  switch (mode)
  {
    case NWorkDir::NMode::kCurrent:
    {
<<<<<<< HEAD
      return path.Left(pos);;
=======
      return path.Left(pos);
>>>>>>> upstream/master
    }
    case NWorkDir::NMode::kSpecified:
    {
      FString tempDir = workDirInfo.Path;
      NName::NormalizeDirPathPrefix(tempDir);
      return tempDir;
    }
    default:
    {
      FString tempDir;
      if (!MyGetTempPath(tempDir))
        throw 141717;
      return tempDir;
    }
  }
}

HRESULT CWorkDirTempFile::CreateTempFile(const FString &originalPath)
{
  NWorkDir::CInfo workDirInfo;
  workDirInfo.Load();
  FString namePart;
  FString workDir = GetWorkDir(workDirInfo, originalPath, namePart);
<<<<<<< HEAD
  CreateComplexDirectory(workDir);
=======
  CreateComplexDir(workDir);
>>>>>>> upstream/master
  CTempFile tempFile;
  _outStreamSpec = new COutFileStream;
  OutStream = _outStreamSpec;
  if (!_tempFile.Create(workDir + namePart, &_outStreamSpec->File))
  {
    DWORD error = GetLastError();
    return error ? error : E_FAIL;
  }
  _originalPath = originalPath;
  return S_OK;
}

HRESULT CWorkDirTempFile::MoveToOriginal(bool deleteOriginal)
{
  OutStream.Release();
  if (!_tempFile.MoveTo(_originalPath, deleteOriginal))
  {
    DWORD error = GetLastError();
    return error ? error : E_FAIL;
  }
  return S_OK;
}
