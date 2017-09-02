// Common/ListFileUtils.h

#ifndef __COMMON_LIST_FILE_UTILS_H
#define __COMMON_LIST_FILE_UTILS_H

#include "MyString.h"
<<<<<<< HEAD
#include "Types.h"
=======
#include "MyTypes.h"

#define MY__CP_UTF16   1200
#define MY__CP_UTF16BE 1201
>>>>>>> upstream/master

bool ReadNamesFromListFile(CFSTR fileName, UStringVector &strings, UINT codePage = CP_OEMCP);

#endif
