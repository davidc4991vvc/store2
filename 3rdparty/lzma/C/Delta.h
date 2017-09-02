/* Delta.h -- Delta converter
<<<<<<< HEAD
2009-04-15 : Igor Pavlov : Public domain */
=======
2013-01-18 : Igor Pavlov : Public domain */
>>>>>>> upstream/master

#ifndef __DELTA_H
#define __DELTA_H

<<<<<<< HEAD
#include "Types.h"

#ifdef __cplusplus
extern "C" {
#endif
=======
#include "7zTypes.h"

EXTERN_C_BEGIN
>>>>>>> upstream/master

#define DELTA_STATE_SIZE 256

void Delta_Init(Byte *state);
void Delta_Encode(Byte *state, unsigned delta, Byte *data, SizeT size);
void Delta_Decode(Byte *state, unsigned delta, Byte *data, SizeT size);

<<<<<<< HEAD
#ifdef __cplusplus
}
#endif
=======
EXTERN_C_END
>>>>>>> upstream/master

#endif
