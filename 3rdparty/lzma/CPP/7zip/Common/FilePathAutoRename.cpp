// FilePathAutoRename.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include "Common/Defs.h"
#include "Common/IntToString.h"

#include "Windows/FileFind.h"
=======
#include "../../Common/Defs.h"
#include "../../Common/IntToString.h"

#include "../../Windows/FileFind.h"
>>>>>>> upstream/master

#include "FilePathAutoRename.h"

using namespace NWindows;

static bool MakeAutoName(const FString &name,
<<<<<<< HEAD
    const FString &extension, unsigned value, FString &path)
{
  FChar number[16];
  ConvertUInt32ToString(value, number);
  path = name;
  path += number;
=======
    const FString &extension, UInt32 value, FString &path)
{
  char temp[16];
  ConvertUInt32ToString(value, temp);
  path = name;
  path.AddAscii(temp);
>>>>>>> upstream/master
  path += extension;
  return NFile::NFind::DoesFileOrDirExist(path);
}

<<<<<<< HEAD
bool AutoRenamePath(FString &fullProcessedPath)
{
  FString path;
  int dotPos = fullProcessedPath.ReverseFind(FTEXT('.'));

  int slashPos = fullProcessedPath.ReverseFind(FTEXT('/'));
  #ifdef _WIN32
  int slash1Pos = fullProcessedPath.ReverseFind(FTEXT('\\'));
  slashPos = MyMax(slashPos, slash1Pos);
  #endif

  FString name, extension;
  if (dotPos > slashPos && dotPos > 0)
  {
    name = fullProcessedPath.Left(dotPos);
    extension = fullProcessedPath.Mid(dotPos);
  }
  else
    name = fullProcessedPath;
  name += L'_';
  unsigned left = 1, right = (1 << 30);
  while (left != right)
  {
    unsigned mid = (left + right) / 2;
    if (MakeAutoName(name, extension, mid, path))
=======
bool AutoRenamePath(FString &path)
{
  int dotPos = path.ReverseFind_Dot();
  int slashPos = path.ReverseFind_PathSepar();

  FString name = path;
  FString extension;
  if (dotPos > slashPos + 1)
  {
    name.DeleteFrom(dotPos);
    extension = path.Ptr(dotPos);
  }
  name += FTEXT('_');
  
  FString temp;

  UInt32 left = 1, right = ((UInt32)1 << 30);
  while (left != right)
  {
    UInt32 mid = (left + right) / 2;
    if (MakeAutoName(name, extension, mid, temp))
>>>>>>> upstream/master
      left = mid + 1;
    else
      right = mid;
  }
<<<<<<< HEAD
  return !MakeAutoName(name, extension, right, fullProcessedPath);
=======
  return !MakeAutoName(name, extension, right, path);
>>>>>>> upstream/master
}
