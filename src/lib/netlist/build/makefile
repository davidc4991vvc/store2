###########################################################################
#
#   makefile
#
#   Core makefile for building MAME and derivatives
#
#   Copyright (c) Nicola Salmoria and the MAME Team.
#   Visit http://mamedev.org for licensing and usage restrictions.
#
###########################################################################

<<<<<<< HEAD
OBJ = obj
SRC = ..
=======
SRC = ..
VSBUILD = $(SRC)/buildVS
DOC = $(SRC)/documentation

ifeq ($(subst Windows_NT,windows,$(OS)),windows)
OBJ = obj/mingw
else
OBJ = obj/nix
endif
>>>>>>> upstream/master

#-fuse-ld=gold -Wpedantic -march=native -march=native

# LTO = -flto=4  -fuse-linker-plugin -flto-partition=balanced -Wodr

<<<<<<< HEAD
CDEFS = -DPSTANDALONE=1 -DPTR64=1
#-Werror
CFLAGS =  $(LTO) -g -O3 -std=c++98  -march=native -msse4.2 -Wall -Wpedantic -Wsign-compare -Wextra -Wno-long-long -Wno-unused-parameter -Wno-unused-result -Wno-variadic-macros -I..
LDFLAGS = $(LTO) -g -O3 -std=c++98 
#CFLAGS =  $(LTO) -g -O3 -std=c++11   -Wall -Wpedantic -Wsign-compare -Wextra -Isrc
#LDFLAGS = $(LTO) -g -O3 -std=c++11 	

CC = @g++-5
LD = @g++-5
MD = @mkdir
RM = @rm
=======
CFLAGS =  $(LTO) -g -O3 -std=c++11 -march=native -I../.. -Wall -Wpedantic -Wsign-compare -Wextra -Wno-unused-parameter $(CEXTRAFLAGS)
LDFLAGS = $(LTO) -g -O3 -std=c++11 $(LDEXTRAFLAGS)
LIBS = -lpthread -ldl

CC = g++
LD = @g++
MD = @mkdir
RM = @rm
DOXYGEN = @doxygen
>>>>>>> upstream/master

TARGETS = nltool nlwav

NLOBJ = $(OBJ)
POBJ = $(OBJ)/plib

OBJDIRS = $(OBJ) \
<<<<<<< HEAD
		  $(OBJ)/analog \
		  $(OBJ)/solver \
		  $(OBJ)/devices \
		  $(OBJ)/plib \
		  $(OBJ)/devices \
		  $(OBJ)/macro \
		  $(OBJ)/tools \
		  $(OBJ)/prg \
		  
=======
			$(OBJ)/analog \
			$(OBJ)/solver \
			$(OBJ)/devices \
			$(OBJ)/plib \
			$(OBJ)/devices \
			$(OBJ)/macro \
			$(OBJ)/tools \
			$(OBJ)/prg \

>>>>>>> upstream/master

OBJS = $(POBJS) $(NLOBJS)

POBJS := \
	$(POBJ)/pstring.o \
	$(POBJ)/palloc.o \
<<<<<<< HEAD
	$(POBJ)/pparser.o \
	$(POBJ)/pstate.o \
	$(POBJ)/pstream.o \
=======
	$(POBJ)/pchrono.o \
	$(POBJ)/pdynlib.o \
	$(POBJ)/pexception.o \
	$(POBJ)/pfunction.o \
	$(POBJ)/pfmtlog.o \
	$(POBJ)/poptions.o \
	$(POBJ)/pparser.o \
	$(POBJ)/pstate.o \
	$(POBJ)/pstream.o \
	$(POBJ)/putil.o \

PMAIN := $(POBJ)/pmain.o
>>>>>>> upstream/master

NLOBJS := \
	$(NLOBJ)/nl_base.o \
	$(NLOBJ)/nl_parser.o \
	$(NLOBJ)/nl_setup.o \
	$(NLOBJ)/nl_factory.o \
	$(NLOBJ)/analog/nld_bjt.o \
<<<<<<< HEAD
	$(NLOBJ)/analog/nld_fourterm.o \
	$(NLOBJ)/analog/nld_switches.o \
	$(NLOBJ)/analog/nld_twoterm.o \
	$(NLOBJ)/analog/nld_opamps.o \
	$(NLOBJ)/devices/nld_4020.o \
	$(NLOBJ)/devices/nld_4066.o \
	$(NLOBJ)/devices/nld_7400.o \
	$(NLOBJ)/devices/nld_7402.o \
	$(NLOBJ)/devices/nld_7404.o \
	$(NLOBJ)/devices/nld_7408.o \
	$(NLOBJ)/devices/nld_7410.o \
	$(NLOBJ)/devices/nld_7411.o \
	$(NLOBJ)/devices/nld_7420.o \
	$(NLOBJ)/devices/nld_7425.o \
	$(NLOBJ)/devices/nld_7427.o \
	$(NLOBJ)/devices/nld_7430.o \
	$(NLOBJ)/devices/nld_7432.o \
	$(NLOBJ)/devices/nld_7437.o \
	$(NLOBJ)/devices/nld_7448.o \
	$(NLOBJ)/devices/nld_7450.o \
	$(NLOBJ)/devices/nld_7474.o \
	$(NLOBJ)/devices/nld_7483.o \
	$(NLOBJ)/devices/nld_7486.o \
=======
	$(NLOBJ)/analog/nlid_fourterm.o \
	$(NLOBJ)/analog/nld_switches.o \
	$(NLOBJ)/analog/nlid_twoterm.o \
	$(NLOBJ)/analog/nld_opamps.o \
	$(NLOBJ)/devices/nld_2102A.o \
	$(NLOBJ)/devices/nld_2716.o \
	$(NLOBJ)/devices/nld_4020.o \
	$(NLOBJ)/devices/nld_4066.o \
	$(NLOBJ)/devices/nld_4316.o \
	$(NLOBJ)/devices/nld_7448.o \
	$(NLOBJ)/devices/nld_7450.o \
	$(NLOBJ)/devices/nld_7473.o \
	$(NLOBJ)/devices/nld_7474.o \
	$(NLOBJ)/devices/nld_7475.o \
	$(NLOBJ)/devices/nld_7483.o \
	$(NLOBJ)/devices/nld_7485.o \
>>>>>>> upstream/master
	$(NLOBJ)/devices/nld_7490.o \
	$(NLOBJ)/devices/nld_7493.o \
	$(NLOBJ)/devices/nld_74107.o \
	$(NLOBJ)/devices/nld_74123.o \
	$(NLOBJ)/devices/nld_74153.o \
<<<<<<< HEAD
	$(NLOBJ)/devices/nld_74175.o \
	$(NLOBJ)/devices/nld_74192.o \
	$(NLOBJ)/devices/nld_74193.o \
	$(NLOBJ)/devices/nld_74279.o \
	$(NLOBJ)/devices/nld_74ls629.o \
	$(NLOBJ)/devices/nld_82S16.o \
	$(NLOBJ)/devices/nld_9310.o \
	$(NLOBJ)/devices/nld_9312.o \
	$(NLOBJ)/devices/nld_9316.o \
	$(NLOBJ)/devices/nld_mm5837.o \
	$(NLOBJ)/devices/nld_ne555.o \
	$(NLOBJ)/devices/nld_r2r_dac.o \
	$(NLOBJ)/devices/nld_legacy.o \
	$(NLOBJ)/devices/net_lib.o \
	$(NLOBJ)/devices/nld_log.o \
	$(NLOBJ)/devices/nld_system.o \
	$(NLOBJ)/devices/nld_truthtable.o \
=======
	$(NLOBJ)/devices/nld_74161.o \
	$(NLOBJ)/devices/nld_74164.o \
	$(NLOBJ)/devices/nld_74165.o \
	$(NLOBJ)/devices/nld_74166.o \
	$(NLOBJ)/devices/nld_74174.o \
	$(NLOBJ)/devices/nld_74175.o \
	$(NLOBJ)/devices/nld_74192.o \
	$(NLOBJ)/devices/nld_74193.o \
	$(NLOBJ)/devices/nld_74194.o \
	$(NLOBJ)/devices/nld_74365.o \
	$(NLOBJ)/devices/nld_74ls629.o \
	$(NLOBJ)/devices/nld_82S16.o \
	$(NLOBJ)/devices/nld_82S115.o \
	$(NLOBJ)/devices/nld_82S123.o \
	$(NLOBJ)/devices/nld_82S126.o \
	$(NLOBJ)/devices/nld_9310.o \
	$(NLOBJ)/devices/nld_9316.o \
	$(NLOBJ)/devices/nld_9322.o \
	$(NLOBJ)/devices/nld_am2847.o \
	$(NLOBJ)/devices/nld_dm9334.o \
	$(NLOBJ)/devices/nld_mm5837.o \
	$(NLOBJ)/devices/nld_ne555.o \
	$(NLOBJ)/devices/nld_r2r_dac.o \
	$(NLOBJ)/devices/nld_tristate.o \
	$(NLOBJ)/devices/nld_legacy.o \
	$(NLOBJ)/devices/net_lib.o \
	$(NLOBJ)/devices/nld_log.o \
	$(NLOBJ)/devices/nlid_proxy.o \
	$(NLOBJ)/devices/nld_system.o \
	$(NLOBJ)/devices/nlid_truthtable.o \
	$(NLOBJ)/macro/nlm_base.o \
>>>>>>> upstream/master
	$(NLOBJ)/macro/nlm_cd4xxx.o \
	$(NLOBJ)/macro/nlm_opamp.o \
	$(NLOBJ)/macro/nlm_other.o \
	$(NLOBJ)/macro/nlm_ttl74xx.o \
	$(NLOBJ)/solver/nld_solver.o \
<<<<<<< HEAD
	$(NLOBJ)/tools/nl_convert.o \

all:	maketree $(TARGETS)
=======
	$(NLOBJ)/solver/nld_matrix_solver.o \
	$(NLOBJ)/tools/nl_convert.o \
	
VSBUILDS = \
	$(VSBUILD/netlistlib.vcxproj) \
	$(VSBUILD/netlistlib.vcxproj.user \
	$(VSBUILD/nltool.vcxproj \
	$(VSBUILD/netlistlib.vcxproj.filters  \
	$(VSBUILD/nltool.vcxproj.filters \
	$(VSBUILD/netlist.sln \

DOCS = \
	doxygen.conf \
	$(DOC)/doc.css \
	$(DOC)/mainpage.dox.h \
	$(DOC)/primer_1.dox.h \
	$(DOC)/structure.dox.h \
	$(DOC)/test1-50r.svg \

ALL_OBJS = $(OBJS) $(PMAIN) $(NLOBJ)/prg/nltool.o $(NLOBJ)/prg/nlwav.o
SOURCES = $(patsubst $(OBJ)%, $(SRC)%, $(ALL_OBJS:.o=.cpp))
ALLFILES = $(SOURCES) $(VSBUILDS) $(DOCS)

MAKEFILE_TARGETS_WITHOUT_INCLUDE := clean doc clang mingw


# git archive HEAD --prefix=project-name-version/ \
#     --format=zip -o project-name-version.zip

#-------------------------------------------------
# all
#-------------------------------------------------

all:    maketree depend $(TARGETS)
>>>>>>> upstream/master

#-------------------------------------------------
# clean
#-------------------------------------------------

clean:
<<<<<<< HEAD
	$(RM) -rf $(OBJS) $(TARGETS)
=======
	$(RM) -rf $(OBJS) $(TARGETS) $(OBJ)/prg/nltool.o $(OBJ)/prg/nlwav.o .depend
>>>>>>> upstream/master

#-------------------------------------------------
# nltool
#-------------------------------------------------

<<<<<<< HEAD
nltool: $(OBJ)/prg/nltool.o $(OBJS)
	@echo Linking $@...
	$(LD) -o $@ $(LDFLAGS) $^ $(LIBS)

nlwav: $(OBJ)/prg/nlwav.o $(OBJS)
=======
nltool: $(OBJ)/prg/nltool.o $(PMAIN) $(OBJS)
	@echo Linking $@...
	$(LD) -o $@ $(LDFLAGS) $^ $(LIBS)

nlwav: $(OBJ)/prg/nlwav.o $(PMAIN) $(OBJS)
>>>>>>> upstream/master
	@echo Linking $@...
	$(LD) -o $@ $(LDFLAGS) $^ $(LIBS)

#-------------------------------------------------
# directories
#-------------------------------------------------

$(sort $(OBJDIRS)):
	$(MD) -p $@

maketree: $(sort $(OBJDIRS))

<<<<<<< HEAD
=======
#-------------------------------------------------
# Special targets
#-------------------------------------------------

.PHONY: clang clang-5 mingw doc

clang:
	$(MAKE) CC=clang++ LD=clang++ CEXTRAFLAGS="-march=native -Weverything -Werror -override -Wno-unreachable-code -Wno-padded -Wno-weak-vtables -Wno-missing-variable-declarations -Wconversion -Wno-c++98-compat -Wno-float-equal -Wno-global-constructors -Wno-c++98-compat-pedantic -Wno-format-nonliteral -Wno-weak-template-vtables -Wno-exit-time-destructors"

clang-5:
	$(MAKE) CC=clang++-5.0 LD=clang++-5.0 CEXTRAFLAGS="-march=native -Weverything -Werror -Wno-inconsistent-missing-destructor-override -Wno-unreachable-code -Wno-padded -Wno-weak-vtables -Wno-missing-variable-declarations -Wconversion -Wno-c++98-compat -Wno-float-equal -Wno-global-constructors -Wno-c++98-compat-pedantic -Wno-format-nonliteral -Wno-weak-template-vtables -Wno-exit-time-destructors"

#
# Mostly done: -Wno-weak-vtables -Wno-cast-align
# FIXME:  -Wno-weak-vtables -Wno-missing-variable-declarations -Wno-conversion -Wno-exit-time-destructors
# FIXME: -Winconsistent-missing-destructor-override : c++ community has diverging opinions on this https://github.com/isocpp/CppCoreGuidelines/issues/721
# FIXME: -Wunreachable-code : False warnings, this a documented clang bug: https://llvm.org/bugs/show_bug.cgi?id=28994

mingw:
	$(MAKE) CEXTRAFLAGS="-DUNICODE -D_UNICODE -D_WIN32_WINNT=0x0501 -DWIN32_LEAN_AND_MEAN" \
		LDEXTRAFLAGS="-Wl,--subsystem,console -municode" LIBS= MD=@mkdir.exe SHELL=sh.exe

#
# FIXME: Unicode
#     CEXTRAFLAGS = -DUNICODE -D_UNICODE -municode
#     LDEXTRAFLAGS = -municode
#


doc: nltool
	./nltool -c docheader > ../documentation/devsyn.dox.h
	$(DOXYGEN) doxygen.conf

#-------------------------------------------------
# depends
#-------------------------------------------------

.depend: $(SOURCES)
	@echo creating .depend
	@rm -f ./.depend
	@for i in $(SOURCES); do \
		$(CC) $(CFLAGS) -MM $$i -MT `echo $$i | sed -e 's+$(SRC)+$(OBJ)+' -e 's+.cpp+.o+' ` >>./.depend; \
	done

depend: .depend

# Include only if the goal needs it
ifeq ($(filter $(MAKECMDGOALS),$(MAKEFILE_TARGETS_WITHOUT_INCLUDE)),)
-include .depend
endif
>>>>>>> upstream/master

#-------------------------------------------------
# generic rules
#-------------------------------------------------

$(OBJ)/%.o: $(SRC)/%.cpp
	@echo Compiling $<...
<<<<<<< HEAD
	$(CC) $(CDEFS) $(CFLAGS) -c $< -o $@

$(OBJ)/%.pp: $(SRC)/%.cpp | $(OSPREBUILD)
	@echo Compiling $<...
	$(CC) $(CDEFS) $(CFLAGS) -E $< -o $@

$(OBJ)/%.s: $(SRC)/%.cpp | $(OSPREBUILD)
	@echo Compiling $<...
	$(CC) $(CDEFS) $(CFLAGS) -S $< -o $@
=======
	@$(CC) $(CDEFS) $(CFLAGS) -c $< -o $@

$(OBJ)/%.pp: $(SRC)/%.cpp
	@echo Compiling $<...
	@$(CC) $(CDEFS) $(CFLAGS) -E $< -o $@

$(OBJ)/%.s: $(SRC)/%.cpp
	@echo Compiling $<...
	@$(CC) $(CDEFS) $(CFLAGS) -S $< -o $@
>>>>>>> upstream/master

$(OBJ)/%.a:
	@echo Archiving $@...
	$(RM) $@
	$(AR) $(ARFLAGS) $@ $^

<<<<<<< HEAD

=======
>>>>>>> upstream/master
