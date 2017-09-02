// ArchiveName.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include "Windows/FileDir.h"
#include "Windows/FileFind.h"

#include "ExtractingFilePath.h"

using namespace NWindows;

static FString CreateArchiveName2(const FString &srcName, bool fromPrev, bool keepName)
=======
#include "../../../Windows/FileDir.h"
#include "../../../Windows/FileName.h"

#include "ExtractingFilePath.h"
#include "ArchiveName.h"

using namespace NWindows;
using namespace NFile;

UString CreateArchiveName(const NFind::CFileInfo &fi, bool keepName)
{
  FString resultName = fi.Name;
  if (!fi.IsDir() && !keepName)
  {
    int dotPos = resultName.ReverseFind_Dot();
    if (dotPos > 0)
    {
      FString archiveName2 = resultName.Left(dotPos);
      if (archiveName2.ReverseFind_Dot() < 0)
        resultName = archiveName2;
    }
  }
  return Get_Correct_FsFile_Name(fs2us(resultName));
}

static FString CreateArchiveName2(const FString &path, bool fromPrev, bool keepName)
>>>>>>> upstream/master
{
  FString resultName = FTEXT("Archive");
  if (fromPrev)
  {
    FString dirPrefix;
<<<<<<< HEAD
    if (NFile::NDirectory::GetOnlyDirPrefix(srcName, dirPrefix))
    {
      if (dirPrefix.Length() > 0)
        if (dirPrefix.Back() == FCHAR_PATH_SEPARATOR)
        {
          dirPrefix.DeleteBack();
          NFile::NFind::CFileInfo fileInfo;
          if (fileInfo.Find(dirPrefix))
            resultName = fileInfo.Name;
        }
=======
    if (NDir::GetOnlyDirPrefix(path, dirPrefix))
    {
      if (!dirPrefix.IsEmpty() && IsPathSepar(dirPrefix.Back()))
      {
        #if defined(_WIN32) && !defined(UNDER_CE)
        if (NName::IsDriveRootPath_SuperAllowed(dirPrefix))
          resultName = dirPrefix[dirPrefix.Len() - 3]; // only letter
        else
        #endif
        {
          dirPrefix.DeleteBack();
          NFind::CFileInfo fi;
          if (fi.Find(dirPrefix))
            resultName = fi.Name;
        }
      }
>>>>>>> upstream/master
    }
  }
  else
  {
<<<<<<< HEAD
    NFile::NFind::CFileInfo fileInfo;
    if (!fileInfo.Find(srcName))
      // return resultName;
      return srcName;
    resultName = fileInfo.Name;
    if (!fileInfo.IsDir() && !keepName)
    {
      int dotPos = resultName.ReverseFind('.');
      if (dotPos > 0)
      {
        FString archiveName2 = resultName.Left(dotPos);
        if (archiveName2.ReverseFind(FTEXT('.')) < 0)
          resultName = archiveName2;
=======
    NFind::CFileInfo fi;
    if (fi.Find(path))
    {
      resultName = fi.Name;
      if (!fi.IsDir() && !keepName)
      {
        int dotPos = resultName.ReverseFind_Dot();
        if (dotPos > 0)
        {
          FString name2 = resultName.Left(dotPos);
          if (name2.ReverseFind_Dot() < 0)
            resultName = name2;
        }
>>>>>>> upstream/master
      }
    }
  }
  return resultName;
}

<<<<<<< HEAD
UString CreateArchiveName(const UString &srcName, bool fromPrev, bool keepName)
{
  return GetCorrectFsPath(fs2us(CreateArchiveName2(us2fs(srcName), fromPrev, keepName)));
=======
UString CreateArchiveName(const UString &path, bool fromPrev, bool keepName)
{
  return Get_Correct_FsFile_Name(fs2us(CreateArchiveName2(us2fs(path), fromPrev, keepName)));
>>>>>>> upstream/master
}
