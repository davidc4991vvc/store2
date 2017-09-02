// DefaultName.cpp

#include "StdAfx.h"

#include "DefaultName.h"

static UString GetDefaultName3(const UString &fileName,
    const UString &extension, const UString &addSubExtension)
{
<<<<<<< HEAD
  int extLength = extension.Length();
  int fileNameLength = fileName.Length();
  if (fileNameLength > extLength + 1)
  {
    int dotPos = fileNameLength - (extLength + 1);
    if (fileName[dotPos] == '.')
      if (extension.CompareNoCase(fileName.Mid(dotPos + 1)) == 0)
        return fileName.Left(dotPos) + addSubExtension;
  }
  int dotPos = fileName.ReverseFind(L'.');
=======
  const unsigned extLen = extension.Len();
  const unsigned fileNameLen = fileName.Len();
  
  if (fileNameLen > extLen + 1)
  {
    const unsigned dotPos = fileNameLen - (extLen + 1);
    if (fileName[dotPos] == '.')
      if (extension.IsEqualTo_NoCase(fileName.Ptr(dotPos + 1)))
        return fileName.Left(dotPos) + addSubExtension;
  }
  
  int dotPos = fileName.ReverseFind_Dot();
>>>>>>> upstream/master
  if (dotPos > 0)
    return fileName.Left(dotPos) + addSubExtension;

  if (addSubExtension.IsEmpty())
<<<<<<< HEAD
    return fileName + L"~";
=======
    return fileName + L'~';
>>>>>>> upstream/master
  else
    return fileName + addSubExtension;
}

UString GetDefaultName2(const UString &fileName,
    const UString &extension, const UString &addSubExtension)
{
  UString name = GetDefaultName3(fileName, extension, addSubExtension);
  name.TrimRight();
  return name;
}
