// EnumDirItems.h

#ifndef __ENUM_DIR_ITEMS_H
#define __ENUM_DIR_ITEMS_H

<<<<<<< HEAD
#include "Common/Wildcard.h"
#include "Windows/FileFind.h"
#include "DirItem.h"

void AddDirFileInfo(int phyParent, int logParent,
    const NWindows::NFile::NFind::CFileInfo &fi, CObjectVector<CDirItem> &dirItems);

struct IEnumDirItemCallback
{
  virtual HRESULT ScanProgress(UInt64 numFolders, UInt64 numFiles, const wchar_t *path) = 0;
};

HRESULT EnumerateItems(
    const NWildcard::CCensor &censor,
    CDirItems &dirItems,
    IEnumDirItemCallback *callback,
    FStringVector &errorPaths,
    CRecordVector<DWORD> &errorCodes);
=======
#include "../../../Common/Wildcard.h"

#include "../../../Windows/FileFind.h"

#include "DirItem.h"

void AddDirFileInfo(int phyParent, int logParent, int secureIndex,
    const NWindows::NFile::NFind::CFileInfo &fi, CObjectVector<CDirItem> &dirItems);

HRESULT EnumerateItems(
    const NWildcard::CCensor &censor,
    NWildcard::ECensorPathMode pathMode,
    const UString &addPathPrefix,
    CDirItems &dirItems);
>>>>>>> upstream/master

#endif
