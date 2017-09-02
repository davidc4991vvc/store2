// TempFiles.h

#ifndef __TEMP_FILES_H
#define __TEMP_FILES_H

<<<<<<< HEAD
#include "Common/MyString.h"
=======
#include "../../../Common/MyString.h"
>>>>>>> upstream/master

class CTempFiles
{
  void Clear();
public:
  FStringVector Paths;
  ~CTempFiles() { Clear(); }
};

#endif
