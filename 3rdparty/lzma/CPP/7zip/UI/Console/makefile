PROG = 7z.exe
MY_CONSOLE = 1
<<<<<<< HEAD
CFLAGS = $(CFLAGS) -I ../../../  \
=======
CFLAGS = $(CFLAGS)  \
>>>>>>> upstream/master
  -DEXTERNAL_CODECS \

!IFNDEF UNDER_CE
CFLAGS = $(CFLAGS) -DWIN_LONG_PATH -D_7ZIP_LARGE_PAGES -DSUPPORT_DEVICE_FILE
!ENDIF

<<<<<<< HEAD

CONSOLE_OBJS = \
  $O\ConsoleClose.obj \
  $O\ExtractCallbackConsole.obj \
  $O\List.obj \
  $O\BenchCon.obj \
  $O\Main.obj \
  $O\MainAr.obj \
  $O\OpenCallbackConsole.obj \
  $O\PercentPrinter.obj \
  $O\UpdateCallbackConsole.obj \
  $O\UserInputUtils.obj \

=======
>>>>>>> upstream/master
COMMON_OBJS = \
  $O\CommandLineParser.obj \
  $O\CRC.obj \
  $O\IntToString.obj \
  $O\ListFileUtils.obj \
  $O\NewHandler.obj \
  $O\StdInStream.obj \
  $O\StdOutStream.obj \
  $O\MyString.obj \
  $O\StringConvert.obj \
  $O\StringToInt.obj \
  $O\UTFConvert.obj \
  $O\MyVector.obj \
  $O\Wildcard.obj \

WIN_OBJS = \
  $O\DLL.obj \
<<<<<<< HEAD
  $O\Error.obj \
  $O\FileDir.obj \
  $O\FileFind.obj \
  $O\FileIO.obj \
  $O\FileName.obj \
  $O\MemoryLock.obj \
  $O\PropVariant.obj \
  $O\PropVariantConversions.obj \
  $O\Registry.obj \
  $O\System.obj \
  $O\Time.obj \
=======
  $O\ErrorMsg.obj \
  $O\FileDir.obj \
  $O\FileFind.obj \
  $O\FileIO.obj \
  $O\FileLink.obj \
  $O\FileName.obj \
  $O\FileSystem.obj \
  $O\MemoryLock.obj \
  $O\PropVariant.obj \
  $O\PropVariantConv.obj \
  $O\Registry.obj \
  $O\System.obj \
  $O\TimeUtils.obj \
>>>>>>> upstream/master

7ZIP_COMMON_OBJS = \
  $O\CreateCoder.obj \
  $O\FilePathAutoRename.obj \
  $O\FileStreams.obj \
  $O\FilterCoder.obj \
<<<<<<< HEAD
  $O\MethodProps.obj \
  $O\ProgressUtils.obj \
  $O\StreamUtils.obj \

UI_COMMON_OBJS = \
  $O\ArchiveCommandLine.obj \
  $O\ArchiveExtractCallback.obj \
  $O\ArchiveOpenCallback.obj \
  $O\DefaultName.obj \
  $O\EnumDirItems.obj \
  $O\Extract.obj \
  $O\ExtractingFilePath.obj \
  $O\Bench.obj \
  $O\LoadCodecs.obj \
  $O\OpenArchive.obj \
  $O\PropIDUtils.obj \
  $O\SetProperties.obj \
  $O\SortUtils.obj \
  $O\TempFiles.obj \
  $O\Update.obj \
  $O\UpdateAction.obj \
  $O\UpdateCallback.obj \
  $O\UpdatePair.obj \
  $O\UpdateProduce.obj \
=======
  $O\LimitedStreams.obj \
  $O\MethodProps.obj \
  $O\ProgressUtils.obj \
  $O\PropId.obj \
  $O\StreamObjects.obj \
  $O\StreamUtils.obj \
  $O\UniqBlocks.obj \
>>>>>>> upstream/master

AR_COMMON_OBJS = \
  $O\OutStreamWithCRC.obj \

<<<<<<< HEAD
C_OBJS = \
  $O\Alloc.obj \
  $O\CpuArch.obj \
  $O\Threads.obj \

!include "../../Crc.mak"

OBJS = \
  $O\StdAfx.obj \
  $(CONSOLE_OBJS) \
  $(COMMON_OBJS) \
  $(WIN_OBJS) \
  $(7ZIP_COMMON_OBJS) \
  $(UI_COMMON_OBJS) \
  $(AR_COMMON_OBJS) \
  $O\CopyCoder.obj \
  $(C_OBJS) \
  $(ASM_OBJS) \
  $O\resource.res

!include "../../../Build.mak"

$(CONSOLE_OBJS): $(*B).cpp
	$(COMPL)
$(COMMON_OBJS): ../../../Common/$(*B).cpp
	$(COMPL)
$(WIN_OBJS): ../../../Windows/$(*B).cpp
	$(COMPL)
$(7ZIP_COMMON_OBJS): ../../Common/$(*B).cpp
	$(COMPL)
$(UI_COMMON_OBJS): ../Common/$(*B).cpp
	$(COMPL)
$(AR_COMMON_OBJS): ../../Archive/Common/$(*B).cpp
	$(COMPL)
$O\CopyCoder.obj: ../../Compress/$(*B).cpp
	$(COMPL)
$(C_OBJS): ../../../../C/$(*B).c
	$(COMPL_O2)

!include "../../Asm.mak"
=======
COMPRESS_OBJS = \
  $O\CopyCoder.obj \

C_OBJS = \
  $O\Alloc.obj \
  $O\CpuArch.obj \
  $O\Sort.obj \
  $O\Threads.obj \

!include "../../Crc.mak"
!include "Console.mak"

!include "../../7zip.mak"
>>>>>>> upstream/master
