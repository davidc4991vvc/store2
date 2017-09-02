// ArchiveName.h

<<<<<<< HEAD
#ifndef __ARCHIVENAME_H
#define __ARCHIVENAME_H

#include "Common/MyString.h"

UString CreateArchiveName(const UString &srcName, bool fromPrev, bool keepName);
=======
#ifndef __ARCHIVE_NAME_H
#define __ARCHIVE_NAME_H

#include "../../../Common/MyString.h"

#include "../../../Windows/FileFind.h"

UString CreateArchiveName(const UString &path, bool fromPrev, bool keepName);
UString CreateArchiveName(const NWindows::NFile::NFind::CFileInfo &fileInfo, bool keepName);
>>>>>>> upstream/master

#endif
