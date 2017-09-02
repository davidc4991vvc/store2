PROG = 7zS2.sfx
<<<<<<< HEAD
LIBS = $(LIBS) 
CFLAGS = $(CFLAGS) -DUNICODE -D_UNICODE -D_CRT_SECURE_NO_WARNINGS

C_OBJS = \
  $O\7zAlloc.obj \
=======

C_OBJS = \
  $O\7zAlloc.obj \
  $O\7zArcIn.obj \
>>>>>>> upstream/master
  $O\7zBuf.obj \
  $O\7zBuf2.obj \
  $O\7zCrc.obj \
  $O\7zCrcOpt.obj \
  $O\7zFile.obj \
  $O\7zDec.obj \
<<<<<<< HEAD
  $O\7zIn.obj \
=======
>>>>>>> upstream/master
  $O\7zStream.obj \
  $O\Bcj2.obj \
  $O\Bra.obj \
  $O\Bra86.obj \
<<<<<<< HEAD
  $O\CpuArch.obj \
=======
  $O\BraIA64.obj \
  $O\CpuArch.obj \
  $O\Delta.obj \
  $O\DllSecur.obj \
>>>>>>> upstream/master
  $O\Lzma2Dec.obj \
  $O\LzmaDec.obj \

7Z_OBJS = \
  $O\SfxSetup.obj \

OBJS = \
  $(7Z_OBJS) \
  $(C_OBJS) \
  $O\resource.res

!include "../../../CPP/Build.mak"

$(7Z_OBJS): $(*B).c
	$(COMPL_O1)
$(C_OBJS): ../../$(*B).c
	$(COMPL_O1)
