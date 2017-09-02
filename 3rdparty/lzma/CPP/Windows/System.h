// Windows/System.h

#ifndef __WINDOWS_SYSTEM_H
#define __WINDOWS_SYSTEM_H

<<<<<<< HEAD
#include "../Common/Types.h"
=======
#include "../Common/MyTypes.h"
>>>>>>> upstream/master

namespace NWindows {
namespace NSystem {

UInt32 GetNumberOfProcessors();
<<<<<<< HEAD
UInt64 GetRamSize();
=======

bool GetRamSize(UInt64 &size); // returns false, if unknown ram size
>>>>>>> upstream/master

}}

#endif
