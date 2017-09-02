<<<<<<< HEAD
PROG = 7z.exe
MY_CONSOLE = 1
CFLAGS = $(CFLAGS) -I ../../../

CONSOLE_OBJS = \
=======
PROG = 7zcl.exe
MY_CONSOLE = 1

CURRENT_OBJS = \
>>>>>>> upstream/master
  $O\Client7z.obj \

COMMON_OBJS = \
  $O\IntToString.obj \
  $O\NewHandler.obj \
  $O\MyString.obj \
  $O\StringConvert.obj \
  $O\StringToInt.obj \
  $O\MyVector.obj \
  $O\Wildcard.obj \

WIN_OBJS = \
  $O\DLL.obj \
  $O\FileDir.obj \
  $O\FileFind.obj \
  $O\FileIO.obj \
  $O\FileName.obj \
  $O\PropVariant.obj \
<<<<<<< HEAD
  $O\PropVariantConversions.obj \
=======
  $O\PropVariantConv.obj \
>>>>>>> upstream/master

7ZIP_COMMON_OBJS = \
  $O\FileStreams.obj \

<<<<<<< HEAD
OBJS = \
  $O\StdAfx.obj \
  $(CONSOLE_OBJS) \
  $(COMMON_OBJS) \
  $(WIN_OBJS) \
  $(7ZIP_COMMON_OBJS) \

!include "../../../Build.mak"

$(CONSOLE_OBJS): $(*B).cpp
	$(COMPL)
$(COMMON_OBJS): ../../../Common/$(*B).cpp
	$(COMPL)
$(WIN_OBJS): ../../../Windows/$(*B).cpp
	$(COMPL)
$(7ZIP_COMMON_OBJS): ../../Common/$(*B).cpp
	$(COMPL)
=======
!include "../../7zip.mak"
>>>>>>> upstream/master
