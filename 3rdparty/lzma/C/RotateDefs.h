/* RotateDefs.h -- Rotate functions
<<<<<<< HEAD
2009-02-07 : Igor Pavlov : Public domain */
=======
2015-03-25 : Igor Pavlov : Public domain */
>>>>>>> upstream/master

#ifndef __ROTATE_DEFS_H
#define __ROTATE_DEFS_H

#ifdef _MSC_VER

#include <stdlib.h>
<<<<<<< HEAD
=======

/* don't use _rotl with MINGW. It can insert slow call to function. */
 
/* #if (_MSC_VER >= 1200) */
#pragma intrinsic(_rotl)
#pragma intrinsic(_rotr)
/* #endif */

>>>>>>> upstream/master
#define rotlFixed(x, n) _rotl((x), (n))
#define rotrFixed(x, n) _rotr((x), (n))

#else

<<<<<<< HEAD
=======
/* new compilers can translate these macros to fast commands. */

>>>>>>> upstream/master
#define rotlFixed(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define rotrFixed(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

#endif

#endif
