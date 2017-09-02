/* 7zAlloc.h -- Allocation functions
<<<<<<< HEAD
2010-10-29 : Igor Pavlov : Public domain */
=======
2013-03-25 : Igor Pavlov : Public domain */
>>>>>>> upstream/master

#ifndef __7Z_ALLOC_H
#define __7Z_ALLOC_H

#include <stdlib.h>

<<<<<<< HEAD
=======
#ifdef __cplusplus
extern "C" {
#endif

>>>>>>> upstream/master
void *SzAlloc(void *p, size_t size);
void SzFree(void *p, void *address);

void *SzAllocTemp(void *p, size_t size);
void SzFreeTemp(void *p, void *address);

<<<<<<< HEAD
=======
#ifdef __cplusplus
}
#endif

>>>>>>> upstream/master
#endif
