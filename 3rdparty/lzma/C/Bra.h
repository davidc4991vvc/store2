/* Bra.h -- Branch converters for executables
<<<<<<< HEAD
2009-02-07 : Igor Pavlov : Public domain */
=======
2013-01-18 : Igor Pavlov : Public domain */
>>>>>>> upstream/master

#ifndef __BRA_H
#define __BRA_H

<<<<<<< HEAD
#include "Types.h"

#ifdef __cplusplus
extern "C" {
#endif
=======
#include "7zTypes.h"

EXTERN_C_BEGIN
>>>>>>> upstream/master

/*
These functions convert relative addresses to absolute addresses
in CALL instructions to increase the compression ratio.
  
  In:
    data     - data buffer
    size     - size of data
    ip       - current virtual Instruction Pinter (IP) value
    state    - state variable for x86 converter
    encoding - 0 (for decoding), 1 (for encoding)
  
  Out:
    state    - state variable for x86 converter

  Returns:
    The number of processed bytes. If you call these functions with multiple calls,
    you must start next call with first byte after block of processed bytes.
  
  Type   Endian  Alignment  LookAhead
  
  x86    little      1          4
  ARMT   little      2          2
  ARM    little      4          0
  PPC     big        4          0
  SPARC   big        4          0
  IA64   little     16          0

  size must be >= Alignment + LookAhead, if it's not last block.
  If (size < Alignment + LookAhead), converter returns 0.

  Example:

    UInt32 ip = 0;
    for ()
    {
      ; size must be >= Alignment + LookAhead, if it's not last block
      SizeT processed = Convert(data, size, ip, 1);
      data += processed;
      size -= processed;
      ip += processed;
    }
*/

#define x86_Convert_Init(state) { state = 0; }
SizeT x86_Convert(Byte *data, SizeT size, UInt32 ip, UInt32 *state, int encoding);
SizeT ARM_Convert(Byte *data, SizeT size, UInt32 ip, int encoding);
SizeT ARMT_Convert(Byte *data, SizeT size, UInt32 ip, int encoding);
SizeT PPC_Convert(Byte *data, SizeT size, UInt32 ip, int encoding);
SizeT SPARC_Convert(Byte *data, SizeT size, UInt32 ip, int encoding);
SizeT IA64_Convert(Byte *data, SizeT size, UInt32 ip, int encoding);

<<<<<<< HEAD
#ifdef __cplusplus
}
#endif
=======
EXTERN_C_END
>>>>>>> upstream/master

#endif
