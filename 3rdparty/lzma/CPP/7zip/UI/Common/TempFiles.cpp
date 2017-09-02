// TempFiles.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include "TempFiles.h"

#include "Windows/FileDir.h"
=======
#include "../../../Windows/FileDir.h"

#include "TempFiles.h"
>>>>>>> upstream/master

using namespace NWindows;
using namespace NFile;

void CTempFiles::Clear()
{
  while (!Paths.IsEmpty())
  {
<<<<<<< HEAD
    NDirectory::DeleteFileAlways(Paths.Back());
    Paths.DeleteBack();
  }
}


=======
    NDir::DeleteFileAlways(Paths.Back());
    Paths.DeleteBack();
  }
}
>>>>>>> upstream/master
