###########################################################################
#
#   makefile
#
#   Core makefile for building MAME and derivatives
#
###########################################################################



###########################################################################
#################   BEGIN USER-CONFIGURABLE OPTIONS   #####################
###########################################################################

<<<<<<< HEAD
include config.def

# REGENIE = 1
# VERBOSE = 1
# NOWERROR = 1
=======
# REGENIE = 1
# VERBOSE = 1
# NOWERROR = 1
# IGNORE_GIT = 1
>>>>>>> upstream/master

# TARGET = mame
# SUBTARGET = tiny
# TOOLS = 1
# TESTS = 1
<<<<<<< HEAD
# OSD = sdl

# USE_BGFX = 1
# NO_OPENGL = 1
# USE_DISPATCH_GL = 0
=======
# BENCHMARKS = 1
# OSD = sdl

# USE_DISPATCH_GL = 0
# MODERN_WIN_API = 0
>>>>>>> upstream/master
# DIRECTINPUT = 7
# USE_SDL = 1
# SDL_INI_PATH = .;$HOME/.mame/;ini;
# SDL2_MULTIAPI = 1
# NO_USE_MIDI = 1
<<<<<<< HEAD
=======
# NO_USE_PORTAUDIO = 1
>>>>>>> upstream/master
# DONT_USE_NETWORK = 1
# USE_QTDEBUG = 1
# NO_X11 = 1
# NO_USE_XINPUT = 0
# FORCE_DRC_C_BACKEND = 1

# DEBUG = 1
# PROFILER = 1
# SANITIZE = 1

# PTR64 = 1
# BIGENDIAN = 1
# NOASM = 1

# OPTIMIZE = 3
# SYMBOLS = 1
# SYMLEVEL = 2
# MAP = 1
# PROFILE = 1
# ARCHOPTS =
# OPT_FLAGS =
# LDOPTS =

# USE_SYSTEM_LIB_EXPAT = 1
# USE_SYSTEM_LIB_ZLIB = 1
# USE_SYSTEM_LIB_JPEG = 1
# USE_SYSTEM_LIB_FLAC = 1
# USE_SYSTEM_LIB_LUA = 1
# USE_SYSTEM_LIB_SQLITE3 = 1
# USE_SYSTEM_LIB_PORTMIDI = 1
# USE_SYSTEM_LIB_PORTAUDIO = 1
<<<<<<< HEAD
=======
# USE_BUNDLED_LIB_SDL2 = 1
# USE_SYSTEM_LIB_UTF8PROC = 1
>>>>>>> upstream/master

# MESA_INSTALL_ROOT = /opt/mesa
# SDL_INSTALL_ROOT = /opt/sdl2
# SDL_FRAMEWORK_PATH = $(HOME)/Library/Frameworks
<<<<<<< HEAD
# SDL_LIBVER = sdl
# MACOSX_USE_LIBSDL = 1
=======
# USE_LIBSDL = 1
>>>>>>> upstream/master
# CYGWIN_BUILD = 1

# BUILDDIR = build
# TARGETOS = windows
# CROSS_BUILD = 1
<<<<<<< HEAD
=======
# TOOLCHAIN =
>>>>>>> upstream/master
# OVERRIDE_CC = cc
# OVERRIDE_CXX = c++
# OVERRIDE_LD = ld

# DEPRECATED = 1
# LTO = 1
# SSE2 = 1
# OPENMP = 1
<<<<<<< HEAD
# CPP11 = 1
# FASTDEBUG = 1

# FILTER_DEPS = 1
=======
# FASTDEBUG = 1

>>>>>>> upstream/master
# SEPARATE_BIN = 1
# PYTHON_EXECUTABLE = python3
# SHADOW_CHECK = 1
# STRIP_SYMBOLS = 0

# QT_HOME = /usr/lib64/qt48/

<<<<<<< HEAD
# SOURCES = src/mame/drivers/asteroid.c,src/mame/audio/llander.c

# FORCE_VERSION_COMPILE = 1

=======
# SOURCES = src/mame/drivers/asteroid.cpp,src/mame/audio/llander.cpp

# FORCE_VERSION_COMPILE = 1

# MSBUILD = 1
# IGNORE_BAD_LOCALISATION=1
# PRECOMPILE = 0

# DEBUG_DIR=c:\test\location
# DEBUG_ARGS= -window -video bgfx

>>>>>>> upstream/master
ifdef PREFIX_MAKEFILE
include $(PREFIX_MAKEFILE)
else
-include useroptions.mak
endif

###########################################################################
##################   END USER-CONFIGURABLE OPTIONS   ######################
###########################################################################

<<<<<<< HEAD
=======

ifndef MAKETYPE
MAKETYPE := gmake
endif

>>>>>>> upstream/master
MAKEPARAMS := -R

#
# Determine running OS
#

ifeq ($(OS),Windows_NT)
OS := windows
GENIEOS := windows
<<<<<<< HEAD
else
UNAME := $(shell uname -mps)
GENIEOS := linux
=======
PLATFORM := x86
else
UNAME := $(shell uname -mps)
UNAME_M := $(shell uname -m)
UNAME_P := $(shell uname -p)
GENIEOS := linux
PLATFORM := unknown
ifneq ($(filter x86_64,$(UNAME_P)),)
PLATFORM := x86
endif
ifneq ($(filter %86,$(UNAME_P)),)
PLATFORM := x86
endif
ifneq ($(filter alpha,$(UNAME_M)),)
PLATFORM := alpha
endif
ifneq ($(filter alpha,$(UNAME_P)),)
PLATFORM := alpha
endif
ifneq ($(filter arm%,$(UNAME_M)),)
PLATFORM := arm
endif
ifneq ($(filter arm%,$(UNAME_P)),)
PLATFORM := arm
endif
ifneq ($(filter aarch64%,$(UNAME_M)),)
PLATFORM := arm64
endif
ifneq ($(filter aarch64%,$(UNAME_P)),)
PLATFORM := arm64
endif
ifneq ($(filter powerpc,$(UNAME_P)),)
PLATFORM := powerpc
endif
ifneq ($(filter mips64%,$(UNAME_M)),)
ifeq ($(shell getconf LONG_BIT),64)
PLATFORM := mips64
endif
endif
>>>>>>> upstream/master
ifeq ($(firstword $(filter Linux,$(UNAME))),Linux)
OS := linux
endif
ifeq ($(firstword $(filter Solaris,$(UNAME))),Solaris)
OS := solaris
GENIEOS := solaris
endif
ifeq ($(firstword $(filter SunOS,$(UNAME))),SunOS)
OS := solaris
GENIEOS := solaris
endif
ifeq ($(firstword $(filter FreeBSD,$(UNAME))),FreeBSD)
OS := freebsd
<<<<<<< HEAD
GENIEOS := bsd
endif
ifeq ($(firstword $(filter GNU/kFreeBSD,$(UNAME))),GNU/kFreeBSD)
OS := freebsd
GENIEOS := bsd
endif
ifeq ($(firstword $(filter NetBSD,$(UNAME))),NetBSD)
OS := netbsd
GENIEOS := bsd
endif
ifeq ($(firstword $(filter OpenBSD,$(UNAME))),OpenBSD)
OS := openbsd
GENIEOS := bsd
=======
GENIEOS := freebsd
endif
ifeq ($(firstword $(filter GNU/kFreeBSD,$(UNAME))),GNU/kFreeBSD)
OS := freebsd
GENIEOS := freebsd
endif
ifeq ($(firstword $(filter NetBSD,$(UNAME))),NetBSD)
OS := netbsd
GENIEOS := freebsd
endif
ifeq ($(firstword $(filter OpenBSD,$(UNAME))),OpenBSD)
OS := openbsd
GENIEOS := freebsd
>>>>>>> upstream/master
endif
ifeq ($(firstword $(filter Darwin,$(UNAME))),Darwin)
OS := macosx
GENIEOS := darwin
endif
ifeq ($(firstword $(filter Haiku,$(UNAME))),Haiku)
OS := haiku
endif
<<<<<<< HEAD
ifeq ($(firstword $(filter OS/2,$(UNAME))),OS/2)
OS := os2
GENIEOS := os2
endif
=======
>>>>>>> upstream/master
ifndef OS
$(error Unable to detect OS from uname -a: $(UNAME))
endif
endif

<<<<<<< HEAD
#-------------------------------------------------
# specify core target: mame, etc.
# specify subtarget: mame, tiny, etc.
# build rules will be included from
# src/$(TARGET)/$(SUBTARGET).mak
#-------------------------------------------------
=======
MINGW:=
ifdef MINGW64
	MINGW := $(MINGW64)
else
	MINGW := $(MINGW32)
endif

#-------------------------------------------------
# specify core target: mame, ldplayer
# specify subtarget: mame, arcade, mess, tiny, etc.
# build scripts will be run from
# scripts/target/$(TARGET)/$(SUBTARGET).lua
#-------------------------------------------------
ifdef PROJECT
PARAMS += --PROJECT='$(PROJECT)'
TARGET := $(PROJECT)
endif
>>>>>>> upstream/master

ifndef TARGET
TARGET := mame
endif

ifndef SUBTARGET
SUBTARGET := $(TARGET)
endif

<<<<<<< HEAD
CONFIG = release
ifdef DEBUG
CONFIG := debug
endif
=======
SUBTARGET_FULL := $(subst -,_,$(SUBTARGET))


CONFIG = release
ifdef DEBUG
ifneq '$(DEBUG)' '0'
CONFIG := debug
endif
endif
>>>>>>> upstream/master

ifdef VERBOSE
MAKEPARAMS += verbose=1
else
SILENT := @
MAKEPARAMS += --no-print-directory
endif

ifndef BUILDDIR
BUILDDIR := build
endif

#-------------------------------------------------
# specify OS target, which further differentiates
# the underlying OS; supported values are:
<<<<<<< HEAD
# win32, unix, macosx, os2
=======
# win32, unix, macosx
>>>>>>> upstream/master
#-------------------------------------------------

ifndef TARGETOS

ifeq ($(OS),windows)
TARGETOS := windows
ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
ARCHITECTURE := _x64
endif
ifeq ($(PROCESSOR_ARCHITECTURE),x86)
ARCHITECTURE := _x64
ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
else
ARCHITECTURE := _x86
endif
endif
else
UNAME    := $(shell uname -mps)
TARGETOS := $(OS)

ARCHITECTURE := _x86

ifeq ($(firstword $(filter x86_64,$(UNAME))),x86_64)
ARCHITECTURE := _x64
endif
ifeq ($(firstword $(filter amd64,$(UNAME))),amd64)
ARCHITECTURE := _x64
endif
ifeq ($(firstword $(filter ppc64,$(UNAME))),ppc64)
ARCHITECTURE := _x64
endif
<<<<<<< HEAD
=======
ifeq ($(firstword $(filter ppc64le,$(UNAME))),ppc64le)
ARCHITECTURE := _x64
endif
ifeq ($(firstword $(filter s390x,$(UNAME))),s390x)
ARCHITECTURE := _x64
endif
>>>>>>> upstream/master
endif

else
CROSS_BUILD := 1
endif # TARGET_OS

ifdef PTR64
ifeq ($(PTR64),1)
ARCHITECTURE := _x64
else
ARCHITECTURE := _x86
endif
endif

ifeq ($(OS),windows)
<<<<<<< HEAD
=======
ifndef MINGW64
ARCHITECTURE := _x86
endif
>>>>>>> upstream/master
ifeq ($(ARCHITECTURE),_x64)
WINDRES  := $(MINGW64)/bin/windres
else
WINDRES  := $(MINGW32)/bin/windres
endif
else
ifeq ($(ARCHITECTURE),_x64)
<<<<<<< HEAD
WINDRES  := x86_64-w64-mingw32-windres
else
WINDRES  := i686-w64-mingw32-windres
=======
WINDRES  := $(word 1,$(TOOLCHAIN) x86_64-w64-mingw32-)windres
else
WINDRES  := $(word 1,$(TOOLCHAIN) i686-w64-mingw32-)windres
>>>>>>> upstream/master
endif
endif

ifeq ($(findstring arm,$(UNAME)),arm)
ARCHITECTURE :=
ifndef NOASM
	NOASM := 1
endif
endif

<<<<<<< HEAD
=======
ifeq ($(findstring aarch64,$(UNAME)),aarch64)
ARCHITECTURE :=
ifndef NOASM
	NOASM := 1
endif
endif

ifeq ($(findstring s390x,$(UNAME)),s390x)
ifndef NOASM
	NOASM := 1
endif
endif

>>>>>>> upstream/master
# Emscripten
ifeq ($(findstring emcc,$(CC)),emcc)
TARGETOS := asmjs
ARCHITECTURE :=
ifndef NOASM
	NOASM := 1
endif
endif

# Autodetect BIGENDIAN
# MacOSX
ifndef BIGENDIAN
ifneq (,$(findstring Power,$(UNAME)))
BIGENDIAN := 1
endif
# Linux
ifneq (,$(findstring ppc,$(UNAME)))
<<<<<<< HEAD
=======
ifneq (,$(findstring ppc64le,$(UNAME)))
BIGENDIAN := 0
else
BIGENDIAN := 1
endif
endif
ifneq (,$(findstring s390x,$(UNAME)))
>>>>>>> upstream/master
BIGENDIAN := 1
endif
endif # BIGENDIAN

ifndef PYTHON_EXECUTABLE
PYTHON := python
else
PYTHON := $(PYTHON_EXECUTABLE)
endif
CC := $(SILENT)gcc
LD := $(SILENT)g++
<<<<<<< HEAD

#-------------------------------------------------
# specify OSD layer: windows, sdl, etc.
# build rules will be included from
# src/osd/$(OSD)/$(OSD).mak
=======
CXX:= $(SILENT)g++

#-------------------------------------------------
# specify OSD layer: windows, sdl, etc.
# build scripts will be run from
# scripts/src/osd/$(OSD).lua
>>>>>>> upstream/master
#-------------------------------------------------

ifndef OSD

<<<<<<< HEAD
OSD := osdmini
=======
OSD := sdl
>>>>>>> upstream/master

ifeq ($(TARGETOS),windows)
OSD := windows
endif

ifeq ($(TARGETOS),linux)
OSD := sdl
endif

ifeq ($(TARGETOS),freebsd)
OSD := sdl
endif

ifeq ($(TARGETOS),netbsd)
OSD := sdl
endif

<<<<<<< HEAD
=======
ifeq ($(TARGETOS),openbsd)
OSD := sdl
endif

>>>>>>> upstream/master
ifeq ($(TARGETOS),solaris)
OSD := sdl
endif

ifeq ($(TARGETOS),macosx)
OSD := sdl
endif

<<<<<<< HEAD
ifeq ($(TARGETOS),os2)
=======
ifeq ($(TARGETOS),asmjs)
>>>>>>> upstream/master
OSD := sdl
endif
endif

#-------------------------------------------------
# which 3rdparty library to build;
#  link against system (common) library otherwise
#-------------------------------------------------
<<<<<<< HEAD
ifndef USE_SYSTEM_LIB_EXPAT
PARAMS += --with-bundled-expat
endif

ifndef USE_SYSTEM_LIB_ZLIB
PARAMS += --with-bundled-zlib
endif

ifndef USE_SYSTEM_LIB_JPEG
PARAMS += --with-bundled-jpeg
endif

ifndef USE_SYSTEM_LIB_FLAC
PARAMS += --with-bundled-flac
endif

ifndef USE_SYSTEM_LIB_LUA
PARAMS += --with-bundled-lua
endif

ifndef USE_SYSTEM_LIB_SQLITE3
PARAMS += --with-bundled-sqlite3
endif

ifndef USE_SYSTEM_LIB_PORTMIDI
PARAMS += --with-bundled-portmidi
endif

ifndef USE_SYSTEM_LIB_PORTAUDIO
PARAMS += --with-bundled-portaudio
=======
ifdef USE_SYSTEM_LIB_EXPAT
PARAMS += --with-system-expat='$(USE_SYSTEM_LIB_EXPAT)'
endif

ifdef USE_SYSTEM_LIB_ZLIB
PARAMS += --with-system-zlib='$(USE_SYSTEM_LIB_ZLIB)'
endif

ifdef USE_SYSTEM_LIB_JPEG
PARAMS += --with-system-jpeg='$(USE_SYSTEM_LIB_JPEG)'
endif

ifdef USE_SYSTEM_LIB_FLAC
PARAMS += --with-system-flac='$(USE_SYSTEM_LIB_FLAC)'
endif

ifdef USE_SYSTEM_LIB_LUA
PARAMS += --with-system-lua='$(USE_SYSTEM_LIB_LUA)'
endif

ifdef USE_SYSTEM_LIB_SQLITE3
PARAMS += --with-system-sqlite3='$(USE_SYSTEM_LIB_SQLITE3)'
endif

ifdef USE_SYSTEM_LIB_PORTMIDI
PARAMS += --with-system-portmidi='$(USE_SYSTEM_LIB_PORTMIDI)'
endif

ifdef USE_SYSTEM_LIB_PORTAUDIO
PARAMS += --with-system-portaudio='$(USE_SYSTEM_LIB_PORTAUDIO)'
endif

ifdef USE_SYSTEM_LIB_UTF8PROC
PARAMS += --with-system-utf8proc='$(USE_SYSTEM_LIB_UTF8PROC)'
endif

# reverse logic for this one

ifdef USE_BUNDLED_LIB_SDL2
PARAMS += --with-bundled-sdl2
>>>>>>> upstream/master
endif

#-------------------------------------------------
# distribution may change things
#-------------------------------------------------

ifeq ($(DISTRO),)
DISTRO := generic
else
ifeq ($(DISTRO),debian-stable)
else
$(error DISTRO $(DISTRO) unknown)
endif
endif

PARAMS+= --distro=$(DISTRO)

<<<<<<< HEAD
=======
ifdef TOOLCHAIN
PARAMS += --TOOLCHAIN='$(TOOLCHAIN)'
endif
>>>>>>> upstream/master
ifdef OVERRIDE_CC
PARAMS += --CC='$(OVERRIDE_CC)'
ifndef CROSS_BUILD
CC := $(OVERRIDE_CC)
endif
endif
ifdef OVERRIDE_CXX
PARAMS += --CXX='$(OVERRIDE_CXX)'
ifndef CROSS_BUILD
CXX := $(OVERRIDE_CXX)
endif
endif
ifdef OVERRIDE_LD
PARAMS += --LD='$(OVERRIDE_LD)'
ifndef CROSS_BUILD
LD := $(OVERRIDE_LD)
endif
endif

#-------------------------------------------------
# sanity check the configuration
#-------------------------------------------------

# enable symbols as it is useless without them
ifdef SANITIZE
SYMBOLS = 1
endif

# profiler defaults to on for DEBUG builds
ifdef DEBUG
<<<<<<< HEAD
=======
ifneq '$(DEBUG)' '0'
>>>>>>> upstream/master
ifndef PROFILER
PROFILER = 1
endif
endif
<<<<<<< HEAD
=======
endif
>>>>>>> upstream/master

# allow gprof profiling as well, which overrides the internal PROFILER
# also enable symbols as it is useless without them
ifdef PROFILE
PROFILER =
SYMBOLS = 1
<<<<<<< HEAD
ifndef SYMLEVEL
SYMLEVEL = 1
endif
=======
>>>>>>> upstream/master
endif

# specify a default optimization level if none explicitly stated
ifndef OPTIMIZE
OPTIMIZE = 3
endif

# set the symbols level
ifdef SYMBOLS
<<<<<<< HEAD
ifndef SYMLEVEL
SYMLEVEL = 2
=======
PARAMS += --SYMBOLS='$(SYMBOLS)'
ifneq '$(SYMBOLS)' '0'
ifndef SYMLEVEL
ifdef SOURCES
SYMLEVEL = 2
else
SYMLEVEL = 1
endif
endif
>>>>>>> upstream/master
endif
endif

ifdef TOOLS
<<<<<<< HEAD
PARAMS += --with-tools
endif

ifdef TESTS
PARAMS += --with-tests
endif

ifdef SYMBOLS
PARAMS += --SYMBOLS='$(SYMBOLS)'
=======
ifneq '$(TOOLS)' '0'
PARAMS += --with-tools
endif
endif

ifdef TESTS
ifneq '$(TESTS)' '0'
PARAMS += --with-tests
endif
endif

ifdef BENCHMARKS
ifneq '$(BENCHMARKS)' '0'
PARAMS += --with-benchmarks
endif
>>>>>>> upstream/master
endif

ifdef SYMLEVEL
PARAMS += --SYMLEVEL='$(SYMLEVEL)'
endif

ifdef PROFILER
PARAMS += --PROFILER='$(PROFILER)'
endif

ifdef PROFILE
PARAMS += --PROFILE='$(PROFILE)'
endif

ifdef OPTIMIZE
PARAMS += --OPTIMIZE=$(OPTIMIZE)
endif

ifdef SHLIB
PARAMS += --SHLIB=$(SHLIB)
endif

ifdef ARCHOPTS
PARAMS += --ARCHOPTS='$(ARCHOPTS)'
endif

ifdef OPT_FLAGS
PARAMS += --OPT_FLAGS='$(OPT_FLAGS)'
endif

ifdef MAP
PARAMS += --MAP='$(MAP)'
endif

<<<<<<< HEAD
ifdef USE_BGFX
PARAMS += --USE_BGFX='$(USE_BGFX)'
endif

ifdef NOASM
PARAMS += --NOASM='$(NOASM)'
=======
ifdef NOASM
TARGET_PARAMS += --NOASM='$(NOASM)'
>>>>>>> upstream/master
endif

ifdef BIGENDIAN
PARAMS += --BIGENDIAN='$(BIGENDIAN)'
endif

ifdef FORCE_DRC_C_BACKEND
PARAMS += --FORCE_DRC_C_BACKEND='$(FORCE_DRC_C_BACKEND)'
endif

ifdef NOWERROR
PARAMS += --NOWERROR='$(NOWERROR)'
endif

ifdef TARGET
PARAMS += --target='$(TARGET)'
endif

<<<<<<< HEAD
ifdef SUBTARGET
PARAMS += --subtarget='$(SUBTARGET)'
endif

ifdef OSD
PARAMS += --osd='$(OSD)'
=======
ifdef SUBTARGET_FULL
PARAMS += --subtarget='$(SUBTARGET_FULL)'
endif

ifdef OSD
TARGET_PARAMS += --osd='$(OSD)'
>>>>>>> upstream/master
endif

ifdef BUILDDIR
PARAMS += --build-dir='$(BUILDDIR)'
endif

ifdef TARGETOS
<<<<<<< HEAD
PARAMS += --targetos='$(TARGETOS)'
=======
TARGET_PARAMS += --targetos='$(TARGETOS)'
>>>>>>> upstream/master
endif

ifdef DONT_USE_NETWORK
PARAMS += --DONT_USE_NETWORK='$(DONT_USE_NETWORK)'
endif

<<<<<<< HEAD
ifdef NO_OPENGL
PARAMS += --NO_OPENGL='$(NO_OPENGL)'
endif

=======
>>>>>>> upstream/master
ifdef USE_DISPATCH_GL
PARAMS += --USE_DISPATCH_GL='$(USE_DISPATCH_GL)'
endif

ifdef NO_USE_MIDI
PARAMS += --NO_USE_MIDI='$(NO_USE_MIDI)'
endif

<<<<<<< HEAD
=======
ifdef NO_USE_PORTAUDIO
PARAMS += --NO_USE_PORTAUDIO='$(NO_USE_PORTAUDIO)'
endif

>>>>>>> upstream/master
ifdef USE_QTDEBUG
PARAMS += --USE_QTDEBUG='$(USE_QTDEBUG)'
endif

<<<<<<< HEAD
=======
ifdef MODERN_WIN_API
PARAMS += --MODERN_WIN_API='$(MODERN_WIN_API)'
endif

>>>>>>> upstream/master
ifdef DIRECTINPUT
PARAMS += --DIRECTINPUT='$(DIRECTINPUT)'
endif

ifdef USE_SDL
PARAMS += --USE_SDL='$(USE_SDL)'
endif

ifdef SDL_INI_PATH
PARAMS += --SDL_INI_PATH='$(SDL_INI_PATH)'
endif

ifdef CYGWIN_BUILD
PARAMS += --CYGWIN_BUILD='$(CYGWIN_BUILD)'
endif

ifdef MESA_INSTALL_ROOT
PARAMS += --MESA_INSTALL_ROOT='$(MESA_INSTALL_ROOT)'
endif

ifdef NO_X11
PARAMS += --NO_X11='$(NO_X11)'
endif

ifdef NO_USE_XINPUT
PARAMS += --NO_USE_XINPUT='$(NO_USE_XINPUT)'
endif

ifdef SDL_LIBVER
PARAMS += --SDL_LIBVER='$(SDL_LIBVER)'
endif

ifdef SDL2_MULTIAPI
PARAMS += --SDL2_MULTIAPI='$(SDL2_MULTIAPI)'
endif

ifdef SDL_INSTALL_ROOT
PARAMS += --SDL_INSTALL_ROOT='$(SDL_INSTALL_ROOT)'
endif

ifdef SDL_FRAMEWORK_PATH
PARAMS += --SDL_FRAMEWORK_PATH='$(SDL_FRAMEWORK_PATH)'
endif

<<<<<<< HEAD
ifdef MACOSX_USE_LIBSDL
PARAMS += --MACOSX_USE_LIBSDL='$(MACOSX_USE_LIBSDL)'
=======
ifdef USE_LIBSDL
PARAMS += --USE_LIBSDL='$(USE_LIBSDL)'
>>>>>>> upstream/master
endif

ifdef LDOPTS
PARAMS += --LDOPTS='$(LDOPTS)'
endif

ifdef LTO
PARAMS += --LTO='$(LTO)'
endif

ifdef DEPRECATED
PARAMS += --DEPRECATED='$(DEPRECATED)'
endif

ifdef SSE2
PARAMS += --SSE2='$(SSE2)'
endif

ifdef OPENMP
PARAMS += --OPENMP='$(OPENMP)'
endif

<<<<<<< HEAD
ifdef CPP11
PARAMS += --CPP11='$(CPP11)'
endif

=======
>>>>>>> upstream/master
ifdef FASTDEBUG
PARAMS += --FASTDEBUG='$(FASTDEBUG)'
endif

<<<<<<< HEAD
ifdef FILTER_DEPS
PARAMS += --FILTER_DEPS='$(FILTER_DEPS)'
endif

=======
>>>>>>> upstream/master
ifdef SEPARATE_BIN
PARAMS += --SEPARATE_BIN='$(SEPARATE_BIN)'
endif

ifdef PYTHON_EXECUTABLE
PARAMS += --PYTHON_EXECUTABLE='$(PYTHON_EXECUTABLE)'
endif

ifdef SHADOW_CHECK
PARAMS += --SHADOW_CHECK='$(SHADOW_CHECK)'
endif

ifdef STRIP_SYMBOLS
PARAMS += --STRIP_SYMBOLS='$(STRIP_SYMBOLS)'
endif

ifdef QT_HOME
PARAMS += --QT_HOME='$(QT_HOME)'
endif

ifdef SOURCES
PARAMS += --SOURCES='$(SOURCES)'
endif

ifdef FORCE_VERSION_COMPILE
PARAMS += --FORCE_VERSION_COMPILE='$(FORCE_VERSION_COMPILE)'
endif

<<<<<<< HEAD
ifneq ($(EXTRA_SUFFIX),)
PARAMS += --EXTRA_SUFFIX=$(EXTRA_SUFFIX)
endif

ifneq ($(USE_SCALE_EFFECTS),)
PARAMS += --USE_SCALE_EFFECTS=1
endif

ifneq ($(USE_UI_COLOR_DISPLAY),)
PARAMS += --USE_UI_COLOR_DISPLAY=1
endif

ifneq ($(USE_TRANS_UI),)
PARAMS += --USE_TRANS_UI=1
endif

ifneq ($(USE_JOYSTICK_ID),)
PARAMS += --USE_JOYSTICK_ID=1
endif

ifneq ($(USE_AUTOFIRE),)
PARAMS += --USE_AUTOFIRE=1
endif

ifneq ($(USE_CUSTOM_BUTTON),)
PARAMS += --USE_CUSTOM_BUTTON=1
endif

ifneq ($(USE_INP_CAPTION),)
PARAMS += --USE_INP_CAPTION=1
endif

ifneq ($(USE_SHOW_TIME),)
PARAMS += --USE_SHOW_TIME=1
endif

ifneq ($(USE_SHOW_INPUT_LOG),)
PARAMS += --USE_SHOW_INPUT_LOG=1
endif

ifneq ($(USE_PLAYBACK_END_PAUSE),)
PARAMS += --USE_PLAYBACK_END_PAUSE=1
endif

ifneq ($(USE_AUDIO_SYNC),)
PARAMS += --USE_AUDIO_SYNC=1
endif

ifneq ($(USE_IPS),)
PARAMS += --USE_IPS=1
endif

ifneq ($(USE_DRIVER_SWITCH),)
DRIVER_SWITCH = 1
PARAMS += --USE_DRIVER_SWITCH=$(DRIVER_SWITCH)
else
DRIVER_SWITCH=0
endif

ifneq ($(USE_CMD_LIST),)
PARAMS += --USE_CMD_LIST=1
endif

ifneq ($(USE_HISCORE),)
PARAMS += --USE_HISCORE=1
endif

ifneq ($(WINUI),)
PARAMS += --WINUI=1
endif

ifneq ($(USE_MORE_FOLDER_INFO),)
PARAMS += --USE_MORE_FOLDER_INFO=1
endif

ifneq ($(USE_STORY_DATAFILE),)
PARAMS += --USE_STORY_DATAFILE=1
endif

ifneq ($(USE_SHOW_SPLASH_SCREEN),)
PARAMS += --USE_SHOW_SPLASH_SCREEN=1
endif

ifneq ($(USE_VIEW_PCBINFO),)
PARAMS += --USE_VIEW_PCBINFO=1
endif

ifneq ($(USE_TREE_SHEET),)
PARAMS += --USE_TREE_SHEET=1
endif

ifneq ($(USE_EXPORT_GAMELIST),)
PARAMS += --USE_EXPORT_GAMELIST=1
endif

ifneq ($(USE_SHOW_UNAVAILABLE_FOLDER),)
PARAMS += --USE_SHOW_UNAVAILABLE_FOLDER=1
endif



=======
ifdef PLATFORM
TARGET_PARAMS += --PLATFORM='$(PLATFORM)'
endif

ifdef PRECOMPILE
PARAMS += --precompile='$(PRECOMPILE)'
endif

ifdef DEBUG_DIR
PARAMS += --DEBUG_DIR='$(DEBUG_DIR)'
endif

ifdef DEBUG_ARGS
PARAMS += --DEBUG_ARGS='$(DEBUG_ARGS)'
endif

ifdef WEBASSEMBLY
PARAMS += --WEBASSEMBLY='$(WEBASSEMBLY)'
endif
>>>>>>> upstream/master
#-------------------------------------------------
# All scripts
#-------------------------------------------------


SCRIPTS = scripts/genie.lua \
	scripts/src/lib.lua \
	scripts/src/emu.lua \
	scripts/src/machine.lua \
	scripts/src/main.lua \
	scripts/src/3rdparty.lua \
	scripts/src/cpu.lua \
<<<<<<< HEAD
=======
	scripts/src/mame/frontend.lua \
>>>>>>> upstream/master
	scripts/src/osd/modules.lua \
	$(wildcard scripts/src/osd/$(OSD)*.lua) \
	scripts/src/sound.lua \
	scripts/src/tools.lua \
	scripts/src/tests.lua \
<<<<<<< HEAD
	scripts/src/video.lua \
	scripts/src/bus.lua \
	scripts/src/netlist.lua \
	scripts/toolchain.lua \
	scripts/src/osd/modules.lua \
	$(wildcard src/osd/$(OSD)/$(OSD).mak) \
	$(wildcard src/$(TARGET)/$(SUBTARGET).mak)

ifndef SOURCES
SCRIPTS += scripts/target/$(TARGET)/$(SUBTARGET).lua
=======
	scripts/src/benchmarks.lua \
	scripts/src/video.lua \
	scripts/src/bus.lua \
	scripts/src/netlist.lua \
	scripts/src/formats.lua \
	scripts/toolchain.lua \
	scripts/src/osd/modules.lua \
	$(wildcard src/osd/$(OSD)/$(OSD).mak) \
	$(wildcard src/$(TARGET)/$(SUBTARGET_FULL).mak)

ifeq ($(SUBTARGET_FULL),mame)
SCRIPTS += scripts/target/$(TARGET)/arcade.lua
SCRIPTS += scripts/target/$(TARGET)/mess.lua
endif

ifndef SOURCES
ifdef PROJECT
SCRIPTS += projects/$(PROJECT)/scripts/target/$(TARGET)/$(SUBTARGET_FULL).lua
else
SCRIPTS += scripts/target/$(TARGET)/$(SUBTARGET_FULL).lua
endif
>>>>>>> upstream/master
endif

ifdef REGENIE
SCRIPTS+= regenie
endif

#-------------------------------------------------
# Dependent stuff
#-------------------------------------------------

# extension for executables
EXE :=

ifeq ($(OS),windows)
EXE := .exe
endif
<<<<<<< HEAD
ifeq ($(OS),os2)
EXE := .exe
endif
=======
>>>>>>> upstream/master

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(MAKESHELL)))
  SHELLTYPE := posix
endif

ifeq (posix,$(SHELLTYPE))
  MKDIR = $(SILENT) mkdir -p "$(1)"
  COPY  = $(SILENT) cp -fR "$(1)" "$(2)"
else
  MKDIR = $(SILENT) mkdir "$(subst /,\\,$(1))" 2> nul || exit 0
<<<<<<< HEAD
  COPY  = $(SILENT) copy /Y "$(subst /,\\,$(1))" "$(subst /,\\,$(2))"
=======
  COPY  = $(SILENT) copy /Y "$(subst /,\\,$(1))" "$(subst /,\\,$(2))" > nul || exit 0
>>>>>>> upstream/master
endif

GENDIR = $(BUILDDIR)/generated

# all sources are under the src/ directory
SRC = src

# all 3rd party sources are under the 3rdparty/ directory
3RDPARTY = 3rdparty
<<<<<<< HEAD

ifeq ($(OS),windows)
GCC_VERSION      := $(shell gcc -dumpversion 2> NUL)
CLANG_VERSION    := $(shell %CLANG%\bin\clang --version 2> NUL| head -n 1 | sed "s/[^0-9,.]//g")
PYTHON_AVAILABLE := $(shell $(PYTHON) --version > NUL 2>&1 && echo python)
CHECK_CLANG      :=
else
GCC_VERSION      := $(shell $(subst @,,$(CC)) -dumpversion 2> /dev/null)
ifneq ($(OS),solaris)
CLANG_VERSION    := $(shell clang --version  2> /dev/null | head -n 1 | grep -e 'version [0-9]\.[0-9]\(\.[0-9]\)\?' -o | grep -e '[0-9]\.[0-9]\(\.[0-9]\)\?' -o | tail -n 1)
endif
PYTHON_AVAILABLE := $(shell $(PYTHON) --version > /dev/null 2>&1 && echo python)
CHECK_CLANG      := $(shell gcc --version  2> /dev/null | grep 'clang' | head -n 1)
endif

ifeq ($(TARGETOS),macosx)
=======
ifeq ($(SUBTARGET_FULL),mame)
PROJECT_NAME := $(SUBTARGET_FULL)
else ifeq ($(SUBTARGET_FULL),mess)
PROJECT_NAME := $(SUBTARGET_FULL)
else
PROJECT_NAME := $(TARGET)$(SUBTARGET_FULL)
endif


ifeq ($(OS),windows)
ifeq (posix,$(SHELLTYPE))
GCC_VERSION      := $(shell $(TOOLCHAIN)$(subst @,,$(CC)) -dumpversion 2> /dev/null)
CLANG_VERSION    := $(shell $(TOOLCHAIN)$(subst @,,$(CC)) --version 2> /dev/null| head -n 1 | grep clang | sed "s/^.*[^0-9]\([0-9]*\.[0-9]*\.[0-9]*\).*$$/\1/" | head -n 1)
PYTHON_AVAILABLE := $(shell $(PYTHON) --version > /dev/null 2>&1 && echo python)
GIT_AVAILABLE    := $(shell git --version > /dev/null 2>&1 && echo git)
else
GCC_VERSION      := $(shell $(TOOLCHAIN)$(subst @,,$(CC)) -dumpversion 2> NUL)
CLANG_VERSION    := $(shell $(TOOLCHAIN)$(subst @,,$(CC)) --version 2> NUL| head -n 1 | grep clang | sed "s/^.*[^0-9]\([0-9]*\.[0-9]*\.[0-9]*\).*$$/\1/" | head -n 1)
PYTHON_AVAILABLE := $(shell $(PYTHON) --version > NUL 2>&1 && echo python)
GIT_AVAILABLE    := $(shell git --version > NUL 2>&1 && echo git)
endif
ifdef MSBUILD
MSBUILD_PARAMS   := /v:minimal /m:$(NUMBER_OF_PROCESSORS)
ifeq ($(CONFIG),debug)
MSBUILD_PARAMS += /p:Configuration=Debug
else
MSBUILD_PARAMS += /p:Configuration=Release
endif
ifeq ($(ARCHITECTURE),_x64)
MSBUILD_PARAMS += /p:Platform=x64
else
MSBUILD_PARAMS += /p:Platform=win32
endif
ifeq (posix,$(SHELLTYPE))
MSBUILD_PARAMS := $(subst /,-,$(MSBUILD_PARAMS))
endif
endif
ifdef FASTBUILD
FASTBUILD_PARAMS := -j$(NUMBER_OF_PROCESSORS)
ifeq ($(CONFIG),debug)
FASTBUILD_TARGET := all-Debug
else
FASTBUILD_TARGET := all-Release
endif
ifeq ($(ARCHITECTURE),_x64)
FASTBUILD_PARAMS += $(FASTBUILD_TARGET)-x64
else
FASTBUILD_PARAMS += $(FASTBUILD_TARGET)-x32
endif
endif
else
GCC_VERSION      := $(shell $(TOOLCHAIN)$(subst @,,$(CC)) -dumpversion 2> /dev/null)
ifneq ($(OS),solaris)
CLANG_VERSION    := $(shell $(TOOLCHAIN)$(subst @,,$(CC))  --version  2> /dev/null | head -n 1 | grep -e 'version [0-9]\.[0-9]\(\.[0-9]\)\?' -o | grep -e '[0-9]\.[0-9]\(\.[0-9]\)\?' -o | tail -n 1)
endif
PYTHON_AVAILABLE := $(shell $(PYTHON) --version > /dev/null 2>&1 && echo python)
GIT_AVAILABLE := $(shell git --version > /dev/null 2>&1 && echo git)
endif

ifeq ($(CLANG_VERSION),)
$(info GCC $(GCC_VERSION) detected)
else
$(info Clang $(CLANG_VERSION) detected)
ifneq ($(TARGETOS),asmjs)
>>>>>>> upstream/master
ifeq ($(ARCHITECTURE),_x64)
ARCHITECTURE := _x64_clang
else
ARCHITECTURE := _x86_clang
endif
endif
<<<<<<< HEAD
=======
endif
>>>>>>> upstream/master

ifneq ($(PYTHON_AVAILABLE),python)
$(error Python is not available in path)
endif

<<<<<<< HEAD
GENIE := 3rdparty/genie/bin/$(GENIEOS)/genie$(EXE)

ifeq ($(TARGET),$(SUBTARGET))
SUBDIR := $(OSD)/$(TARGET)
else
SUBDIR := $(OSD)/$(TARGET)$(SUBTARGET)
endif
PROJECTDIR := $(BUILDDIR)/projects/$(SUBDIR)
=======
ifneq ($(GIT_AVAILABLE),git)
	IGNORE_GIT := 1
endif
ifeq ($(wildcard .git/*),)
	IGNORE_GIT := 1
endif

ifeq (posix,$(SHELLTYPE))
OLD_GIT_VERSION := $(shell cat $(GENDIR)/git_desc 2> /dev/null)
else
OLD_GIT_VERSION := $(shell cat $(GENDIR)/git_desc 2> NUL)
endif
ifneq ($(IGNORE_GIT),1)
NEW_GIT_VERSION := $(shell git describe --dirty)
else
NEW_GIT_VERSION := unknown
endif
ifeq ($(NEW_GIT_VERSION),)
NEW_GIT_VERSION := unknown
endif

GENIE := 3rdparty/genie/bin/$(GENIEOS)/genie$(EXE)

ifeq ($(TARGET),$(SUBTARGET_FULL))
FULLTARGET := $(TARGET)
else
FULLTARGET := $(TARGET)$(SUBTARGET_FULL)
endif
PROJECTDIR := $(BUILDDIR)/projects/$(OSD)/$(FULLTARGET)
PROJECTDIR_SDL := $(BUILDDIR)/projects/sdl/$(FULLTARGET)
PROJECTDIR_WIN := $(BUILDDIR)/projects/windows/$(FULLTARGET)
>>>>>>> upstream/master

.PHONY: all clean regenie generate
all: $(GENIE) $(TARGETOS)$(ARCHITECTURE)
regenie:

#-------------------------------------------------
# gmake-mingw64-gcc
#-------------------------------------------------

<<<<<<< HEAD
$(PROJECTDIR)/gmake-mingw64-gcc/Makefile: makefile $(SCRIPTS) $(GENIE)
ifndef MINGW64
	$(error MINGW64 is not set)
endif
	$(SILENT) $(GENIE) $(PARAMS) --gcc=mingw64-gcc --gcc_version=$(GCC_VERSION) gmake

.PHONY: windows_x64
windows_x64: generate $(PROJECTDIR)/gmake-mingw64-gcc/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-mingw64-gcc config=$(CONFIG)64 WINDRES=$(WINDRES)
=======
$(PROJECTDIR)/$(MAKETYPE)-mingw64-gcc/Makefile: makefile $(SCRIPTS) $(GENIE)
ifndef MINGW64
	$(error MINGW64 is not set)
endif
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --gcc=mingw64-gcc --gcc_version=$(GCC_VERSION) $(MAKETYPE)

.PHONY: windows_x64
windows_x64: generate $(PROJECTDIR)/$(MAKETYPE)-mingw64-gcc/Makefile
ifndef MINGW64
	$(error MINGW64 is not set)
endif
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-mingw64-gcc config=$(CONFIG)64 WINDRES=$(WINDRES) precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-mingw64-gcc config=$(CONFIG)64 WINDRES=$(WINDRES)
>>>>>>> upstream/master

#-------------------------------------------------
# gmake-mingw32-gcc
#-------------------------------------------------

.PHONY: windows
windows: windows_x86

<<<<<<< HEAD
$(PROJECTDIR)/gmake-mingw32-gcc/Makefile: makefile $(SCRIPTS) $(GENIE)
ifndef MINGW32
	$(error MINGW32 is not set)
endif
	$(SILENT) $(GENIE) $(PARAMS) --gcc=mingw32-gcc --gcc_version=$(GCC_VERSION) gmake

.PHONY: windows_x86
windows_x86: generate $(PROJECTDIR)/gmake-mingw32-gcc/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-mingw32-gcc config=$(CONFIG)32 WINDRES=$(WINDRES)
=======
$(PROJECTDIR)/$(MAKETYPE)-mingw32-gcc/Makefile: makefile $(SCRIPTS) $(GENIE)
ifndef MINGW32
	$(error MINGW32 is not set)
endif
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --gcc=mingw32-gcc --gcc_version=$(GCC_VERSION) $(MAKETYPE)

.PHONY: windows_x86
windows_x86: generate $(PROJECTDIR)/$(MAKETYPE)-mingw32-gcc/Makefile
ifndef MINGW32
	$(error MINGW32 is not set)
endif
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-mingw32-gcc config=$(CONFIG)32 WINDRES=$(WINDRES) precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-mingw32-gcc config=$(CONFIG)32 WINDRES=$(WINDRES)
>>>>>>> upstream/master

#-------------------------------------------------
# gmake-mingw-clang
#-------------------------------------------------

<<<<<<< HEAD
$(PROJECTDIR)/gmake-mingw-clang/Makefile: makefile $(SCRIPTS) $(GENIE)
ifndef CLANG
	$(error CLANG is not set)
endif
	$(SILENT) $(GENIE) $(PARAMS) --gcc=mingw-clang --gcc_version=$(CLANG_VERSION) gmake

.PHONY: windows_x64_clang
windows_x64_clang: generate $(PROJECTDIR)/gmake-mingw-clang/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-mingw-clang config=$(CONFIG)64 WINDRES=$(WINDRES)

.PHONY: windows_x86_clang
windows_x86_clang: generate $(PROJECTDIR)/gmake-mingw-clang/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-mingw-clang config=$(CONFIG)32 WINDRES=$(WINDRES)

vs2010: generate
	$(SILENT) $(GENIE) $(PARAMS) vs2010

vs2012: generate
	$(SILENT) $(GENIE) $(PARAMS) vs2012

vs2012_intel: generate
	$(SILENT) $(GENIE) $(PARAMS) --vs=intel-15 vs2012

vs2012_xp: generate
	$(SILENT) $(GENIE) $(PARAMS) --vs=vs2012-xp vs2012

vs2013: generate
	$(SILENT) $(GENIE) $(PARAMS) vs2013

vs2013_intel: generate
	$(SILENT) $(GENIE) $(PARAMS) --vs=intel-15 vs2013

vs2013_xp: generate
	$(SILENT) $(GENIE) $(PARAMS) --vs=vs2013-xp vs2013

vs2013_clang: generate
	$(SILENT) $(GENIE) $(PARAMS) --vs=vs2013-clang vs2013

vs2013_winrt: generate
	$(SILENT) $(GENIE) $(PARAMS) --vs=winstore81 vs2013

vs2015: generate
	$(SILENT) $(GENIE) $(PARAMS) vs2015

android-arm: generate
ifndef ANDROID_NDK_ARM
	$(error ANDROID_NDK_ARM is not set)
endif
ifndef ANDROID_NDK_ROOT
	$(error ANDROID_NDK_ROOT is not set)
endif
ifndef COMPILE
	$(SILENT) $(GENIE) $(PARAMS) --gcc=android-arm --gcc_version=4.8 gmake
endif
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-android-arm config=$(CONFIG)

android-mips: generate
ifndef ANDROID_NDK_MIPS
	$(error ANDROID_NDK_MIPS is not set)
endif
ifndef ANDROID_NDK_ROOT
	$(error ANDROID_NDK_ROOT is not set)
endif
ifndef COMPILE
	$(SILENT) $(GENIE) $(PARAMS) --gcc=android-mips --gcc_version=4.8 gmake
endif
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-android-mips config=$(CONFIG)

android-x86: generate
ifndef ANDROID_NDK_X86
	$(error ANDROID_NDK_X86 is not set)
=======
$(PROJECTDIR)/$(MAKETYPE)-mingw-clang/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --gcc=mingw-clang --gcc_version=$(CLANG_VERSION) $(MAKETYPE)

.PHONY: windows_x64_clang
windows_x64_clang: generate $(PROJECTDIR)/$(MAKETYPE)-mingw-clang/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-mingw-clang config=$(CONFIG)64 WINDRES=$(WINDRES) precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-mingw-clang config=$(CONFIG)64 WINDRES=$(WINDRES)

.PHONY: windows_x86_clang
windows_x86_clang: generate $(PROJECTDIR)/$(MAKETYPE)-mingw-clang/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-mingw-clang config=$(CONFIG)32 WINDRES=$(WINDRES) precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-mingw-clang config=$(CONFIG)32 WINDRES=$(WINDRES)

#-------------------------------------------------
# Visual Studio 2015
#-------------------------------------------------

.PHONY: vs2015
vs2015: generate
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) vs2015
ifdef MSBUILD
	$(SILENT) msbuild.exe $(PROJECTDIR_WIN)/vs2015/$(PROJECT_NAME).sln $(MSBUILD_PARAMS)
endif

.PHONY: vs2015_intel
vs2015_intel: generate
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --vs=intel-15 vs2015
ifdef MSBUILD
	$(SILENT) msbuild.exe $(PROJECTDIR_WIN)/vs2015-intel/$(PROJECT_NAME).sln $(MSBUILD_PARAMS)
endif

.PHONY: vs2015_xp
vs2015_xp: generate
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --vs=vs2015-xp vs2015
ifdef MSBUILD
	$(SILENT) msbuild.exe $(PROJECTDIR_WIN)/vs2015-xp/$(PROJECT_NAME).sln $(MSBUILD_PARAMS)
endif

.PHONY: vs2015_uwp
vs2015_uwp: generate
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --vs=winstore82 --osd=uwp --NO_USE_MIDI=1 --NO_OPENGL=1 --USE_QTDEBUG=0 --NO_USE_PORTAUDIO=1 --MODERN_WIN_API=1 vs2015
ifdef MSBUILD
	$(SILENT) msbuild.exe $(PROJECTDIR_WIN)/vs2015-winstore82/$(PROJECT_NAME).sln $(MSBUILD_PARAMS)
endif

.PHONY: vs2015_fastbuild
vs2015_fastbuild: generate
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) vs2015-fastbuild
ifdef FASTBUILD
	$(SILENT) fbuild.exe -config $(PROJECTDIR_WIN)/vs2015-fastbuild/ftbuild.bff $(FASTBUILD_PARAMS)
endif

#-------------------------------------------------
# Visual Studio 2017
#-------------------------------------------------

.PHONY: vs2017
vs2017: generate
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) vs2017
ifdef MSBUILD
	$(SILENT) msbuild.exe $(PROJECTDIR_WIN)/vs2017/$(PROJECT_NAME).sln $(MSBUILD_PARAMS)
endif

.PHONY: vs2017_intel
vs2017_intel: generate
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --vs=intel-15 vs2017
ifdef MSBUILD
	$(SILENT) msbuild.exe $(PROJECTDIR_WIN)/vs2017-intel/$(PROJECT_NAME).sln $(MSBUILD_PARAMS)
endif

.PHONY: vs2017_xp
vs2017_xp: generate
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --vs=vs2017-xp vs2017
ifdef MSBUILD
	$(SILENT) msbuild.exe $(PROJECTDIR_WIN)/vs2017-xp/$(PROJECT_NAME).sln $(MSBUILD_PARAMS)
endif

.PHONY: vs2017_uwp
vs2017_uwp: generate
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --vs=winstore82 --osd=uwp --NO_USE_MIDI=1 --NO_OPENGL=1 --USE_QTDEBUG=0 --NO_USE_PORTAUDIO=1 --MODERN_WIN_API=1 vs2015
ifdef MSBUILD
	$(SILENT) msbuild.exe $(PROJECTDIR_WIN)/vs2017-winstore82/$(PROJECT_NAME).sln $(MSBUILD_PARAMS)
endif

.PHONY: vs2017_fastbuild
vs2017_fastbuild: generate
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) vs2017-fastbuild
ifdef FASTBUILD
	$(SILENT) fbuild.exe -config $(PROJECTDIR_WIN)/vs2017-fastbuild/ftbuild.bff $(FASTBUILD_PARAMS)
endif

#-------------------------------------------------
# android-ndk
#-------------------------------------------------

.PHONY: android-ndk
android-ndk:
ifndef ANDROID_NDK_LLVM
	$(error ANDROID_NDK_LLVM is not set)
>>>>>>> upstream/master
endif
ifndef ANDROID_NDK_ROOT
	$(error ANDROID_NDK_ROOT is not set)
endif
<<<<<<< HEAD
ifndef COMPILE
	$(SILENT) $(GENIE) $(PARAMS) --gcc=android-x86 --gcc_version=4.8 gmake
endif
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-android-x86 config=$(CONFIG)

asmjs: generate
ifndef EMSCRIPTEN
	$(error EMSCRIPTEN is not set)
endif
ifndef COMPILE
	$(SILENT) $(GENIE) $(PARAMS) --gcc=asmjs --gcc_version=4.8 gmake
endif
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-asmjs config=$(CONFIG)


nacl: nacl_x86

nacl_x64: generate
ifndef NACL_SDK_ROOT
	$(error NACL_SDK_ROOT is not set)
endif
ifndef COMPILE
	$(SILENT) $(GENIE) $(PARAMS) --gcc=nacl --gcc_version=4.8 gmake
endif
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-nacl config=$(CONFIG)64

nacl_x86: generate
ifndef NACL_SDK_ROOT
	$(error NACL_SDK_ROOT is not set)
endif
ifndef COMPILE
	$(SILENT) $(GENIE) $(PARAMS) --gcc=nacl --gcc_version=4.8 gmake
endif
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-nacl config=$(CONFIG)32

nacl-arm: generate
ifndef NACL_SDK_ROOT
	$(error NACL_SDK_ROOT is not set)
endif
ifndef COMPILE
	$(SILENT) $(GENIE) $(PARAMS) --gcc=nacl-arm --gcc_version=4.8 gmake
endif
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-nacl-arm config=$(CONFIG)

pnacl: generate
ifndef NACL_SDK_ROOT
	$(error NACL_SDK_ROOT is not set)
endif
ifndef COMPILE
	$(SILENT) $(GENIE) $(PARAMS) --gcc=pnacl --gcc_version=4.8 gmake
endif
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-pnacl config=$(CONFIG)
=======

#-------------------------------------------------
# android-arm
#-------------------------------------------------

$(PROJECTDIR_SDL)/$(MAKETYPE)-android-arm/Makefile: makefile $(SCRIPTS) $(GENIE)
ifndef ANDROID_NDK_ARM
	$(error ANDROID_NDK_ARM is not set)
endif
	$(SILENT) $(GENIE) $(PARAMS) --gcc=android-arm --gcc_version=3.8.0 --osd=sdl --targetos=android --PLATFORM=arm --NO_USE_MIDI=1 --NO_OPENGL=1 --USE_QTDEBUG=0 --NO_X11=1 --DONT_USE_NETWORK=1 --NOASM=1 $(MAKETYPE)

.PHONY: android-arm
android-arm: android-ndk generate $(PROJECTDIR_SDL)/$(MAKETYPE)-android-arm/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-android-arm config=$(CONFIG) precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-android-arm config=$(CONFIG)

#-------------------------------------------------
# android-arm64
#-------------------------------------------------

$(PROJECTDIR_SDL)/$(MAKETYPE)-android-arm64/Makefile: makefile $(SCRIPTS) $(GENIE)
ifndef ANDROID_NDK_ARM64
	$(error ANDROID_NDK_ARM64 is not set)
endif
	$(SILENT) $(GENIE) $(PARAMS) --gcc=android-arm64 --gcc_version=3.8.0 --osd=sdl --targetos=android --PLATFORM=arm64 --NO_USE_MIDI=1 --NO_OPENGL=1 --USE_QTDEBUG=0 --NO_X11=1 --DONT_USE_NETWORK=1 --NOASM=1 $(MAKETYPE)

.PHONY: android-arm64
android-arm64: android-ndk generate $(PROJECTDIR_SDL)/$(MAKETYPE)-android-arm64/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-android-arm64 config=$(CONFIG) precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-android-arm64 config=$(CONFIG)

#-------------------------------------------------
# android-mips
#-------------------------------------------------

$(PROJECTDIR_SDL)/$(MAKETYPE)-android-mips/Makefile: makefile $(SCRIPTS) $(GENIE)
ifndef ANDROID_NDK_MIPS
	$(error ANDROID_NDK_MIPS is not set)
endif
	$(SILENT) $(GENIE) $(PARAMS) --gcc=android-mips --gcc_version=3.8.0 --osd=sdl --targetos=android --PLATFORM=mips --NO_USE_MIDI=1 --NO_OPENGL=1 --USE_QTDEBUG=0 --NO_X11=1 --DONT_USE_NETWORK=1 --NOASM=1 $(MAKETYPE)

.PHONY: android-mips
android-mips: android-ndk generate $(PROJECTDIR_SDL)/$(MAKETYPE)-android-mips/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-android-mips config=$(CONFIG) precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-android-mips config=$(CONFIG)

#-------------------------------------------------
# android-mips64
#-------------------------------------------------

$(PROJECTDIR_SDL)/$(MAKETYPE)-android-mips64/Makefile: makefile $(SCRIPTS) $(GENIE)
ifndef ANDROID_NDK_MIPS64
	$(error ANDROID_NDK_MIPS64 is not set)
endif
	$(SILENT) $(GENIE) $(PARAMS) --gcc=android-mips64 --gcc_version=3.8.0 --osd=sdl --targetos=android --PLATFORM=mips64 --NO_USE_MIDI=1 --NO_OPENGL=1 --USE_QTDEBUG=0 --NO_X11=1 --DONT_USE_NETWORK=1 --NOASM=1 $(MAKETYPE)

.PHONY: android-mips64
android-mips64: android-ndk generate $(PROJECTDIR_SDL)/$(MAKETYPE)-android-mips64/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-android-mips64 config=$(CONFIG) precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-android-mips64 config=$(CONFIG)

#-------------------------------------------------
# android-x86
#-------------------------------------------------

$(PROJECTDIR_SDL)/$(MAKETYPE)-android-x86/Makefile: makefile $(SCRIPTS) $(GENIE)
ifndef ANDROID_NDK_X86
	$(error ANDROID_NDK_X86 is not set)
endif
	$(SILENT) $(GENIE) $(PARAMS) --gcc=android-x86 --gcc_version=3.8.0 --osd=sdl --targetos=android --PLATFORM=x86 --NO_USE_MIDI=1 --NO_OPENGL=1 --USE_QTDEBUG=0 --NO_X11=1 --DONT_USE_NETWORK=1 $(MAKETYPE)

.PHONY: android-x86
android-x86: android-ndk generate $(PROJECTDIR_SDL)/$(MAKETYPE)-android-x86/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-android-x86 config=$(CONFIG) precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-android-x86 config=$(CONFIG)

#-------------------------------------------------
# android-x64
#-------------------------------------------------

$(PROJECTDIR_SDL)/$(MAKETYPE)-android-x64/Makefile: makefile $(SCRIPTS) $(GENIE)
ifndef ANDROID_NDK_X64
	$(error ANDROID_NDK_X64 is not set)
endif
	$(SILENT) $(GENIE) $(PARAMS) --gcc=android-x64 --gcc_version=3.8.0 --osd=sdl --targetos=android --PLATFORM=x64 --NO_USE_MIDI=1 --NO_OPENGL=1 --USE_QTDEBUG=0 --NO_X11=1 --DONT_USE_NETWORK=1 $(MAKETYPE)

.PHONY: android-x64
android-x64: android-ndk generate $(PROJECTDIR_SDL)/$(MAKETYPE)-android-x64/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-android-x64 config=$(CONFIG) precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-android-x64 config=$(CONFIG)

#-------------------------------------------------
# asmjs / Emscripten
#-------------------------------------------------

$(PROJECTDIR)/$(MAKETYPE)-asmjs/Makefile: makefile $(SCRIPTS) $(GENIE)
ifndef EMSCRIPTEN
	$(error EMSCRIPTEN is not set)
endif
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --gcc=asmjs --gcc_version=3.7.0 $(MAKETYPE)

.PHONY: asmjs
asmjs: generate $(PROJECTDIR)/$(MAKETYPE)-asmjs/Makefile
ifndef EMSCRIPTEN
	$(error EMSCRIPTEN is not set)
endif
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-asmjs config=$(CONFIG) precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-asmjs config=$(CONFIG)
>>>>>>> upstream/master

#-------------------------------------------------
# gmake-linux
#-------------------------------------------------

<<<<<<< HEAD
$(PROJECTDIR)/gmake-linux/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) --gcc=linux-gcc --gcc_version=$(GCC_VERSION) gmake

.PHONY: linux_x64
linux_x64: generate $(PROJECTDIR)/gmake-linux/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-linux config=$(CONFIG)64

.PHONY: linux_x86
linux_x86: generate $(PROJECTDIR)/gmake-linux/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-linux config=$(CONFIG)32

.PHONY: linux
linux: generate $(PROJECTDIR)/gmake-linux/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-linux config=$(CONFIG)
=======
$(PROJECTDIR)/$(MAKETYPE)-linux/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --gcc=linux-gcc --gcc_version=$(GCC_VERSION) $(MAKETYPE)

.PHONY: linux_x64
linux_x64: generate $(PROJECTDIR)/$(MAKETYPE)-linux/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-linux config=$(CONFIG)64 precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-linux config=$(CONFIG)64

.PHONY: linux_x86
linux_x86: generate $(PROJECTDIR)/$(MAKETYPE)-linux/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-linux config=$(CONFIG)32 precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-linux config=$(CONFIG)32

.PHONY: linux
linux: generate $(PROJECTDIR)/$(MAKETYPE)-linux/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-linux config=$(CONFIG) precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-linux config=$(CONFIG)
>>>>>>> upstream/master

#-------------------------------------------------
# gmake-linux-clang
#-------------------------------------------------

<<<<<<< HEAD
$(PROJECTDIR)/gmake-linux-clang/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) --gcc=linux-clang --gcc_version=$(CLANG_VERSION) gmake

.PHONY: linux_x64_clang
linux_x64_clang: generate $(PROJECTDIR)/gmake-linux-clang/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-linux-clang config=$(CONFIG)64

.PHONY: linux_x86_clang
linux_x86_clang: generate $(PROJECTDIR)/gmake-linux-clang/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-linux-clang config=$(CONFIG)32
=======
$(PROJECTDIR)/$(MAKETYPE)-linux-clang/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --gcc=linux-clang --gcc_version=$(CLANG_VERSION) $(MAKETYPE)

.PHONY: linux_x64_clang
linux_x64_clang: generate $(PROJECTDIR)/$(MAKETYPE)-linux-clang/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-linux-clang config=$(CONFIG)64 precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-linux-clang config=$(CONFIG)64

.PHONY: linux_x86_clang
linux_x86_clang: generate $(PROJECTDIR)/$(MAKETYPE)-linux-clang/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-linux-clang config=$(CONFIG)32 precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-linux-clang config=$(CONFIG)32
>>>>>>> upstream/master

#-------------------------------------------------
# gmake-osx
#-------------------------------------------------

<<<<<<< HEAD
$(PROJECTDIR)/gmake-osx/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) --gcc=osx --gcc_version=$(GCC_VERSION) gmake

.PHONY: macosx_x64
macosx_x64: generate $(PROJECTDIR)/gmake-osx/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-osx config=$(CONFIG)64
=======
$(PROJECTDIR)/$(MAKETYPE)-osx/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --gcc=osx --gcc_version=$(GCC_VERSION) $(MAKETYPE)

.PHONY: macosx_x64
macosx_x64: generate $(PROJECTDIR)/$(MAKETYPE)-osx/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-osx config=$(CONFIG)64 precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-osx config=$(CONFIG)64
>>>>>>> upstream/master

.PHONY: macosx
macosx: macosx_x86

.PHONY: macosx_x86
<<<<<<< HEAD
macosx_x86: generate $(PROJECTDIR)/gmake-osx/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-osx config=$(CONFIG)32
=======
macosx_x86: generate $(PROJECTDIR)/$(MAKETYPE)-osx/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-osx config=$(CONFIG)32 precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-osx config=$(CONFIG)32
>>>>>>> upstream/master

#-------------------------------------------------
# gmake-osx-clang
#-------------------------------------------------

<<<<<<< HEAD
$(PROJECTDIR)/gmake-osx-clang/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) --gcc=osx-clang --gcc_version=$(CLANG_VERSION) gmake

.PHONY: macosx_x64_clang
macosx_x64_clang: generate $(PROJECTDIR)/gmake-osx-clang/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-osx-clang config=$(CONFIG)64

.PHONY: macosx_x86_clang
macosx_x86_clang: generate $(PROJECTDIR)/gmake-osx-clang/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/gmake-osx-clang config=$(CONFIG)32

xcode4: generate
	$(SILENT) $(GENIE) $(PARAMS) --targetos=macosx --xcode=osx xcode4

xcode4-ios: generate
	$(SILENT) $(GENIE) $(PARAMS) --targetos=macosx --xcode=ios xcode4
=======
$(PROJECTDIR)/$(MAKETYPE)-osx-clang/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --gcc=osx-clang --gcc_version=$(CLANG_VERSION) $(MAKETYPE)

.PHONY: macosx_x64_clang
macosx_x64_clang: generate $(PROJECTDIR)/$(MAKETYPE)-osx-clang/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-osx-clang config=$(CONFIG)64 precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-osx-clang config=$(CONFIG)64

.PHONY: macosx_x86_clang
macosx_x86_clang: generate $(PROJECTDIR)/$(MAKETYPE)-osx-clang/Makefile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-osx-clang config=$(CONFIG)32 precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-osx-clang config=$(CONFIG)32

.PHONY: xcode4
xcode4: generate
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --targetos=macosx --xcode=osx xcode4

.PHONY: xcode4-ios
xcode4-ios: generate
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --targetos=macosx --xcode=ios xcode4
>>>>>>> upstream/master

#-------------------------------------------------
# gmake-solaris
#-------------------------------------------------


<<<<<<< HEAD
$(PROJECTDIR)/gmake-solaris/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) --gcc=solaris --gcc_version=$(GCC_VERSION) gmake

.PHONY: solaris_x64
solaris_x64: generate $(PROJECTDIR)/gmake-solaris/Makefile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/gmake-solaris config=$(CONFIG)64
=======
$(PROJECTDIR)/$(MAKETYPE)-solaris/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --gcc=solaris --gcc_version=$(GCC_VERSION) $(MAKETYPE)

.PHONY: solaris_x64
solaris_x64: generate $(PROJECTDIR)/$(MAKETYPE)-solaris/Makefile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-solaris config=$(CONFIG)64 precompile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-solaris config=$(CONFIG)64
>>>>>>> upstream/master

.PHONY: solaris
solaris: solaris_x86

.PHONY: solaris_x86
<<<<<<< HEAD
solaris_x86: generate $(PROJECTDIR)/gmake-solaris/Makefile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/gmake-solaris config=$(CONFIG)32
=======
solaris_x86: generate $(PROJECTDIR)/$(MAKETYPE)-solaris/Makefile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-solaris config=$(CONFIG)32 precompile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-solaris config=$(CONFIG)32
>>>>>>> upstream/master


#-------------------------------------------------
# gmake-freebsd
#-------------------------------------------------

<<<<<<< HEAD

$(PROJECTDIR)/gmake-freebsd/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) --gcc=freebsd --gcc_version=$(GCC_VERSION) gmake

.PHONY: freebsd_x64
freebsd_x64: generate $(PROJECTDIR)/gmake-freebsd/Makefile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/gmake-freebsd config=$(CONFIG)64
=======
$(PROJECTDIR)/$(MAKETYPE)-freebsd/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --gcc=freebsd --gcc_version=$(GCC_VERSION) $(MAKETYPE)

.PHONY: freebsd_x64
freebsd_x64: generate $(PROJECTDIR)/$(MAKETYPE)-freebsd/Makefile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-freebsd config=$(CONFIG)64 precompile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-freebsd config=$(CONFIG)64
>>>>>>> upstream/master

.PHONY: freebsd
freebsd: freebsd_x86

.PHONY: freebsd_x86
<<<<<<< HEAD
freebsd_x86: generate $(PROJECTDIR)/gmake-freebsd/Makefile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/gmake-freebsd config=$(CONFIG)32

=======
freebsd_x86: generate $(PROJECTDIR)/$(MAKETYPE)-freebsd/Makefile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-freebsd config=$(CONFIG)32 precompile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-freebsd config=$(CONFIG)32
>>>>>>> upstream/master

#-------------------------------------------------
# gmake-netbsd
#-------------------------------------------------

<<<<<<< HEAD

$(PROJECTDIR)/gmake-netbsd/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) --gcc=netbsd --gcc_version=$(GCC_VERSION) gmake

.PHONY: netbsd_x64
netbsd_x64: generate $(PROJECTDIR)/gmake-netbsd/Makefile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/gmake-netbsd config=$(CONFIG)64
=======
$(PROJECTDIR)/$(MAKETYPE)-netbsd/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --gcc=netbsd --gcc_version=$(GCC_VERSION) $(MAKETYPE)

.PHONY: netbsd_x64
netbsd_x64: generate $(PROJECTDIR)/$(MAKETYPE)-netbsd/Makefile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-netbsd config=$(CONFIG)64 precompile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-netbsd config=$(CONFIG)64
>>>>>>> upstream/master

.PHONY: netbsd
netbsd: netbsd_x86

.PHONY: netbsd_x86
<<<<<<< HEAD
netbsd_x86: generate $(PROJECTDIR)/gmake-netbsd/Makefile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/gmake-netbsd config=$(CONFIG)32


#-------------------------------------------------
# gmake-os2
#-------------------------------------------------


$(PROJECTDIR)/gmake-os2/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) --gcc=os2 --gcc_version=$(GCC_VERSION) gmake

.PHONY: os2
os2: os2_x86

.PHONY: os2_x86
os2_x86: generate $(PROJECTDIR)/gmake-os2/Makefile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/gmake-os2 config=$(CONFIG)32

=======
netbsd_x86: generate $(PROJECTDIR)/$(MAKETYPE)-netbsd/Makefile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-netbsd config=$(CONFIG)32 precompile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-netbsd config=$(CONFIG)32

#-------------------------------------------------
# gmake-openbsd
#-------------------------------------------------

$(PROJECTDIR)/$(MAKETYPE)-openbsd/Makefile: makefile $(SCRIPTS) $(GENIE)
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --gcc=openbsd --gcc_version=$(GCC_VERSION) $(MAKETYPE)

.PHONY: openbsd_x64
openbsd_x64: generate $(PROJECTDIR)/$(MAKETYPE)-openbsd/Makefile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-openbsd config=$(CONFIG)64 precompile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-openbsd config=$(CONFIG)64

.PHONY: openbsd
openbsd: openbsd_x86

.PHONY: openbsd_x86
openbsd_x86: generate $(PROJECTDIR)/$(MAKETYPE)-openbsd/Makefile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-openbsd config=$(CONFIG)32 precompile
	$(SILENT) $(MAKE) -C $(PROJECTDIR)/$(MAKETYPE)-openbsd config=$(CONFIG)32

#-------------------------------------------------
# gmake-steamlink
#-------------------------------------------------

$(PROJECTDIR)/$(MAKETYPE)-steamlink/Makefile: makefile $(SCRIPTS) $(GENIE)
ifndef MARVELL_SDK_PATH
	$(error MARVELL_SDK_PATH is not set)
endif
ifndef MARVELL_ROOTFS
	$(error MARVELL_ROOTFS is not set)
endif
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) --gcc=steamlink --gcc_version=$(GCC_VERSION) --NO_OPENGL=1 --NO_USE_MIDI=1 --NO_X11=1 --NOASM=1 --SDL_INSTALL_ROOT=$(MARVELL_ROOTFS)/usr  $(MAKETYPE)

.PHONY: steamlink
steamlink: generate $(PROJECTDIR)/$(MAKETYPE)-steamlink/Makefile
ifndef MARVELL_SDK_PATH
	$(error MARVELL_SDK_PATH is not set)
endif
ifndef MARVELL_ROOTFS
	$(error MARVELL_ROOTFS is not set)
endif
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-steamlink config=$(CONFIG) precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR)/$(MAKETYPE)-steamlink config=$(CONFIG)

#-------------------------------------------------
# gmake-rpi
#-------------------------------------------------

$(PROJECTDIR_SDL)/$(MAKETYPE)-rpi/Makefile: makefile $(SCRIPTS) $(GENIE)
ifndef RASPBERRY_SDK_PATH
	$(error RASPBERRY_SDK_PATH is not set)
endif
ifndef RASPBERRY_SYSROOT
	$(error RASPBERRY_SYSROOT is not set)
endif
	$(SILENT) $(GENIE) $(PARAMS) --gcc=rpi --gcc_version=4.9.2 --osd=sdl --targetos=rpi --targetos=rpi --NO_USE_MIDI=1 --PLATFORM=arm --NOASM=1 --USE_QTDEBUG=0 --SDL_INSTALL_ROOT=$(RASPBERRY_SYSROOT)/usr  $(MAKETYPE)

.PHONY: rpi
rpi: generate $(PROJECTDIR_SDL)/$(MAKETYPE)-rpi/Makefile
ifndef RASPBERRY_SDK_PATH
	$(error RASPBERRY_SDK_PATH is not set)
endif
ifndef RASPBERRY_SYSROOT
	$(error RASPBERRY_SYSROOT is not set)
endif
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-rpi config=$(CONFIG) precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-rpi config=$(CONFIG)

#-------------------------------------------------
# gmake-ci20
#-------------------------------------------------

$(PROJECTDIR_SDL)/$(MAKETYPE)-ci20/Makefile: makefile $(SCRIPTS) $(GENIE)
ifndef MIPS_LINUXGNU_ROOT
	$(error MIPS_LINUXGNU_ROOT is not set)
endif
ifndef CI20_SYSROOT
	$(error CI20_SYSROOT is not set)
endif
	$(SILENT) $(GENIE) $(PARAMS) --gcc=ci20 --gcc_version=4.9.2 --osd=sdl --targetos=ci20 --targetos=ci20 --NO_USE_MIDI=1  --PLATFORM=arm --NOASM=1 --USE_QTDEBUG=0 --SDL_INSTALL_ROOT=$(RASPBERRY_SYSROOT)/usr  $(MAKETYPE)

.PHONY: ci20
ci20: generate $(PROJECTDIR_SDL)/$(MAKETYPE)-ci20/Makefile
ifndef MIPS_LINUXGNU_ROOT
	$(error MIPS_LINUXGNU_ROOT is not set)
endif
ifndef CI20_SYSROOT
	$(error CI20_SYSROOT is not set)
endif
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-ci20 config=$(CONFIG) precompile
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C $(PROJECTDIR_SDL)/$(MAKETYPE)-ci20 config=$(CONFIG)
>>>>>>> upstream/master

#-------------------------------------------------
# cmake
#-------------------------------------------------
<<<<<<< HEAD
cmake: generate
	$(SILENT) $(GENIE) $(PARAMS) cmake
ifeq ($(OS),windows)
	$(SILENT)echo cmake_minimum_required(VERSION 2.8.4) > CMakeLists.txt 
	$(SILENT)echo add_subdirectory($(PROJECTDIR)/cmake) >> CMakeLists.txt 
else
	$(SILENT)echo "cmake_minimum_required(VERSION 2.8.4)" > CMakeLists.txt 
	$(SILENT)echo "add_subdirectory($(PROJECTDIR)/cmake)" >> CMakeLists.txt 
endif

	
=======
.PHONY: cmake
cmake: generate
	$(SILENT) $(GENIE) $(PARAMS) $(TARGET_PARAMS) cmake
ifneq (posix,$(SHELLTYPE))
	$(SILENT)echo cmake_minimum_required(VERSION 2.8.4) > CMakeLists.txt
	$(SILENT)echo add_subdirectory($(PROJECTDIR)/cmake) >> CMakeLists.txt
else
	$(SILENT)echo "cmake_minimum_required(VERSION 2.8.4)" > CMakeLists.txt
	$(SILENT)echo "add_subdirectory($(PROJECTDIR)/cmake)" >> CMakeLists.txt
endif

>>>>>>> upstream/master
#-------------------------------------------------
# Clean/bootstrap
#-------------------------------------------------

GENIE_SRC=$(wildcard 3rdparty/genie/src/host/*.c)

$(GENIE): $(GENIE_SRC)
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C 3rdparty/genie/build/gmake.$(GENIEOS) -f genie.make

3rdparty/genie/src/hosts/%.c:

<<<<<<< HEAD
clean:
	@echo Cleaning...
	-@rm -rf $(BUILDDIR)
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C 3rdparty/genie/build/gmake.$(GENIEOS) -f genie.make clean

GEN_FOLDERS := $(GENDIR)/$(TARGET)/layout/ $(GENDIR)/$(TARGET)/$(SUBTARGET)/

=======
.PHONY: genieclean
genieclean:
	$(SILENT) $(MAKE) $(MAKEPARAMS) -C 3rdparty/genie/build/gmake.$(GENIEOS) -f genie.make clean

clean: genieclean
	@echo Cleaning...
	-@rm -rf $(BUILDDIR)
	$(SILENT) $(MAKE) -C $(SRC)/devices/cpu/m68000 clean
	-@rm -rf 3rdparty/bgfx/.build

GEN_FOLDERS := $(GENDIR)/$(TARGET)/layout/ $(GENDIR)/$(TARGET)/$(SUBTARGET_FULL)/ $(GENDIR)/mame/drivers/

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
>>>>>>> upstream/master
LAYOUTS=$(wildcard $(SRC)/$(TARGET)/layout/*.lay)

ifneq (,$(wildcard src/osd/$(OSD)/$(OSD).mak))
include src/osd/$(OSD)/$(OSD).mak
endif

ifneq (,$(wildcard src/$(TARGET)/$(TARGET).mak))
include src/$(TARGET)/$(TARGET).mak
endif

$(GEN_FOLDERS):
	-$(call MKDIR,$@)

<<<<<<< HEAD
generate: \
		$(GENIE) \
		$(GEN_FOLDERS) \
		$(patsubst $(SRC)/%.lay,$(GENDIR)/%.lh,$(LAYOUTS))

$(GENDIR)/%.lh: $(SRC)/%.lay scripts/build/file2str.py
	@echo Converting $<...
	$(SILENT)$(PYTHON) scripts/build/file2str.py $< $@ layout_$(basename $(notdir $<))

	
=======
genie: $(GENIE)

generate: \
		genie \
		$(GEN_FOLDERS) \
		$(GENDIR)/version.cpp \
		$(patsubst %.po,%.mo,$(call rwildcard, language/, *.po)) \
		$(patsubst $(SRC)/%.lay,$(GENDIR)/%.lh,$(LAYOUTS)) \
		$(GENDIR)/mame/drivers/ymmu100.hxx \
		$(SRC)/devices/cpu/m68000/m68kops.cpp \
		$(GENDIR)/includes/SDL2

$(GENDIR)/includes/SDL2:
	-$(call MKDIR,$@)
	-$(call COPY,3rdparty/SDL2/include,$(GENDIR)/includes/SDL2)

ifneq ($(NEW_GIT_VERSION),$(OLD_GIT_VERSION))
stale:

.PHONY: stale

$(GENDIR)/git_desc: stale | $(GEN_FOLDERS)
	@echo $(NEW_GIT_VERSION) > $@
endif

ifeq (posix,$(SHELLTYPE))
$(GENDIR)/version.cpp: $(GENDIR)/git_desc | $(GEN_FOLDERS)
	@echo '#define BARE_BUILD_VERSION "0.189"' > $@
	@echo 'extern const char bare_build_version[];' >> $@
	@echo 'extern const char build_version[];' >> $@
	@echo 'const char bare_build_version[] = BARE_BUILD_VERSION;' >> $@
	@echo 'const char build_version[] = BARE_BUILD_VERSION " ($(NEW_GIT_VERSION))";' >> $@
else
$(GENDIR)/version.cpp: $(GENDIR)/git_desc
	@echo #define BARE_BUILD_VERSION "0.189" > $@
	@echo extern const char bare_build_version[]; >> $@
	@echo extern const char build_version[]; >> $@
	@echo const char bare_build_version[] = BARE_BUILD_VERSION; >> $@
	@echo const char build_version[] = BARE_BUILD_VERSION " ($(NEW_GIT_VERSION))"; >> $@
endif


$(GENDIR)/%.lh: $(SRC)/%.lay scripts/build/complay.py | $(GEN_FOLDERS)
	@echo Compressing $<...
	$(SILENT)$(PYTHON) scripts/build/complay.py $< $@ layout_$(basename $(notdir $<))

$(GENDIR)/mame/drivers/ymmu100.hxx: $(SRC)/mame/drivers/ymmu100.ppm scripts/build/file2str.py
	@echo Converting $<...
	$(SILENT)$(PYTHON) scripts/build/file2str.py $< $@ ymmu100_bkg uint8_t

$(SRC)/devices/cpu/m68000/m68kops.cpp: $(SRC)/devices/cpu/m68000/m68k_in.cpp $(SRC)/devices/cpu/m68000/m68kmake.cpp
ifeq ($(TARGETOS),asmjs)
	$(SILENT) $(MAKE) -C $(SRC)/devices/cpu/m68000
else
	$(SILENT) $(MAKE) -C $(SRC)/devices/cpu/m68000 CC="$(CC)" CXX="$(CXX)"
endif

%.mo: %.po
	@echo Converting translation $<...
ifdef IGNORE_BAD_LOCALISATION
	$(SILENT)$(PYTHON) scripts/build/msgfmt.py --output-file $@ $< || exit 0
else
	$(SILENT)$(PYTHON) scripts/build/msgfmt.py --output-file $@ $<
endif
>>>>>>> upstream/master
#-------------------------------------------------
# Regression tests
#-------------------------------------------------

include regtests/regtests.mak

.PHONY: tests

tests: $(REGTESTS)

#-------------------------------------------------
# Source cleanup
#-------------------------------------------------

.PHONY: cleansrc

cleansrc:
	@echo Cleaning up tabs/spaces/end of lines....
ifeq ($(OS),windows)
	$(shell for /r src %%i in (*.c) do srcclean %%i >&2 )
	$(shell for /r src %%i in (*.h) do srcclean %%i >&2 )
	$(shell for /r src %%i in (*.mak) do srcclean %%i >&2 )
	$(shell for /r src %%i in (*.lst) do srcclean %%i >&2 )
	$(shell for /r src %%i in (*.lay) do srcclean %%i >&2 )
<<<<<<< HEAD
	$(shell for /r src %%i in (*.inc) do srcclean %%i >&2 )
=======
	$(shell for /r src %%i in (*.hxx) do srcclean %%i >&2 )
>>>>>>> upstream/master
	$(shell for /r hash %%i in (*.xml) do srcclean %%i >&2 )
else
	$(shell find src/ -name *.c -exec ./srcclean {} >&2 ;)
	$(shell find src/ -name *.h -exec ./srcclean {}  >&2 ;)
	$(shell find src/ -name *.mak -exec ./srcclean {} >&2 ;)
	$(shell find src/ -name *.lst -exec ./srcclean {} >&2 ;)
	$(shell find src/ -name *.lay -exec ./srcclean {} >&2 ;)
<<<<<<< HEAD
	$(shell find src/ -name *.inc -exec ./srcclean {} >&2 ;)
=======
	$(shell find src/ -name *.hxx -exec ./srcclean {} >&2 ;)
>>>>>>> upstream/master
	$(shell find hash/ -name *.xml -exec ./srcclean {} >&2 ;)
endif

#-------------------------------------------------
# Doxygen documentation
#-------------------------------------------------

.PHONY: doxygen

doxygen:
	@echo Generate Doxygen documentation
<<<<<<< HEAD
	doxygen mame.doxygen
=======
	doxygen doxygen/doxygen.config
>>>>>>> upstream/master

#-------------------------------------------------
# CppCheck analysis
#-------------------------------------------------

.PHONY: cppcheck

CPPCHECK_PARAMS  = -Isrc/osd
CPPCHECK_PARAMS += -Isrc/emu
CPPCHECK_PARAMS += -Isrc/lib
CPPCHECK_PARAMS += -Isrc/lib/util
CPPCHECK_PARAMS += -Isrc/mame
CPPCHECK_PARAMS += -Isrc/osd/modules/render
CPPCHECK_PARAMS += -Isrc/osd/windows
CPPCHECK_PARAMS += -Isrc/emu/cpu/m68000
CPPCHECK_PARAMS += -I3rdparty
ifndef USE_SYSTEM_LIB_LUA
CPPCHECK_PARAMS += -I3rdparty/lua/src
endif
ifndef USE_SYSTEM_LIB_ZLIB
CPPCHECK_PARAMS += -I3rdparty/zlib
endif
CPPCHECK_PARAMS += -I3rdparty/bgfx/include
CPPCHECK_PARAMS += -I3rdparty/bx/include
CPPCHECK_PARAMS += -I$(BUILDDIR)/generated/emu
CPPCHECK_PARAMS += -I$(BUILDDIR)/generated/emu/layout
CPPCHECK_PARAMS += -I$(BUILDDIR)/generated/mame/layout
CPPCHECK_PARAMS += -DX64_WINDOWS_ABI
CPPCHECK_PARAMS += -DPTR64=1
CPPCHECK_PARAMS += -DMAME_DEBUG
CPPCHECK_PARAMS += -DMAME_PROFILER
CPPCHECK_PARAMS += -DCRLF=3
CPPCHECK_PARAMS += -DLSB_FIRST
ifndef USE_SYSTEM_LIB_FLAC
CPPCHECK_PARAMS += -DFLAC__NO_DLL
endif
CPPCHECK_PARAMS += -DNATIVE_DRC=drcbe_x64
CPPCHECK_PARAMS += -DLUA_COMPAT_APIINTCASTS
CPPCHECK_PARAMS += -DWIN32
CPPCHECK_PARAMS += -D__GNUC__
CPPCHECK_PARAMS += -D__x86_64__
ifndef VERBOSE
CPPCHECK_PARAMS += --quiet
endif

cppcheck:
	@echo Generate CppCheck analysis report
	cppcheck --enable=all src/ $(CPPCHECK_PARAMS) -j9
<<<<<<< HEAD
	
=======

#-------------------------------------------------
# BGFX shaders
#
# to build all just use : make shaders
#
# to build specific chain use for example : make shaders CHAIN=eagle
# data for chain is taken from src/osd/modules/render/bgfx/shaders/chains/
# subfolder named in CHAIN
# NOTE: shaders can be only built on Windows for now
# due to restrictions of way how hlsl shaders are compiled
#-------------------------------------------------

.PHONY: shaders bgfx-tools

bgfx-tools:
	$(SILENT) $(MAKE) -C 3rdparty/bgfx -f makefile shaderc CC="$(CC)" CXX="$(CXX)" MINGW="$(MINGW)"

shaders: bgfx-tools
	-$(call MKDIR,build/shaders/dx11)
	-$(call MKDIR,build/shaders/dx9)
	-$(call MKDIR,build/shaders/pssl)
	-$(call MKDIR,build/shaders/metal)
	-$(call MKDIR,build/shaders/essl)
	-$(call MKDIR,build/shaders/glsl)
	-$(call MKDIR,build/shaders/spirv)
	$(SILENT) $(MAKE) -C $(SRC)/osd/modules/render/bgfx/shaders rebuild CHAIN="$(CHAIN)"

#-------------------------------------------------
# Translation
#-------------------------------------------------

.PHONY: translation

translation:
	$(SILENT) echo Generating mame.pot
	$(SILENT) find src -iname "*.cpp" | xargs xgettext --from-code=UTF-8 -k_ -k__ -o mame.pot
	$(SILENT) find language -iname "*.po" | xargs -n 1 -I %% msgmerge -U -N %% mame.pot
	$(SILENT) find language -iname "*.po" | xargs -n 1 -I %% msgattrib --clear-fuzzy --empty %% -o %%

>>>>>>> upstream/master
