/* Alloc.h -- Memory allocation functions
<<<<<<< HEAD
2009-02-07 : Igor Pavlov : Public domain */
=======
2015-02-21 : Igor Pavlov : Public domain */
>>>>>>> upstream/master

#ifndef __COMMON_ALLOC_H
#define __COMMON_ALLOC_H

<<<<<<< HEAD
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
=======
#include "7zTypes.h"

EXTERN_C_BEGIN
>>>>>>> upstream/master

void *MyAlloc(size_t size);
void MyFree(void *address);

<<<<<<< HEAD
#ifdef _WIN32_7Z
=======
#ifdef _WIN32
>>>>>>> upstream/master

void SetLargePageSize();

void *MidAlloc(size_t size);
void MidFree(void *address);
void *BigAlloc(size_t size);
void BigFree(void *address);

#else

#define MidAlloc(size) MyAlloc(size)
#define MidFree(address) MyFree(address)
#define BigAlloc(size) MyAlloc(size)
#define BigFree(address) MyFree(address)

#endif

<<<<<<< HEAD
#ifdef __cplusplus
}
#endif
=======
extern ISzAlloc g_Alloc;
extern ISzAlloc g_BigAlloc;

EXTERN_C_END
>>>>>>> upstream/master

#endif
