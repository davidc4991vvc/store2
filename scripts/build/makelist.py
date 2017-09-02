#!/usr/bin/python
##
## license:BSD-3-Clause
## copyright-holders:Aaron Giles, Andrew Gardner

from __future__ import with_statement

import sys
<<<<<<< HEAD
import os

drivlist = []
extra_drivlist = []
=======

drivlist = []
sourcelist = []
filter_addlist = []
filter_removelist = []
>>>>>>> upstream/master

def parse_file(srcfile):
    try:
        fp = open(srcfile, 'rt')
    except IOError:
        sys.stderr.write("Unable to open source file '%s'\n" % srcfile)
        return 1
    in_comment = 0
    linenum = 0
<<<<<<< HEAD
=======
    curr_source = ''
>>>>>>> upstream/master
    for line in fp.readlines():
        drivname = ''
        linenum+=1
        srcptr = 0
        while srcptr < len(line):
            c = line[srcptr]
            srcptr+=1
            if c==13 or c==10:
                if c==13 and line[srcptr]==10:
                    srcptr+=1
                continue
            if c==' ' or c==9:
                continue
            if in_comment==1 and c=='*' and line[srcptr]=='/' :
                srcptr+=1
                in_comment = 0
                continue
            if in_comment:
                continue
            if c=='/' and line[srcptr]=='*' :
                srcptr+=1
                in_comment = 1
                continue
            if c=='/' and line[srcptr]=='/' :
                break
<<<<<<< HEAD
            if c=='#' and (line[srcptr]==' ' or line[srcptr]=='|') :
                break
=======
>>>>>>> upstream/master
            drivname += c
        drivname = drivname.strip()
        if len(drivname)>0:
            if drivname[0]=='#':
               sys.stderr.write("Importing drivers from '%s'\n" % drivname[1:])
               parse_file(drivname[1:])
               continue
<<<<<<< HEAD
            if not all(((c >='a' and c<='z') or (c>='0' and c<='9') or c=='_') for c in drivname):
               sys.stderr.write("%s:%d - Invalid character in driver \"%s\"\n" % (srcfile,  linenum,  drivname))
               return 1
            else:			   
               drivlist.append(drivname)
               extra_drivlist.append(drivname)
    return 0


if len(sys.argv) < 3:
    print('Usage:')
    print('  makelist <is_driver_switch> <source.lst>')
    sys.exit(0)

header_outputed = False
if sys.argv[1].isdigit() :
    is_driver_switch = int(sys.argv[1])
else:
    is_driver_switch = 0
for i in range(2, len(sys.argv)-1):
    filename = sys.argv[i]
    name, ext = os.path.splitext(os.path.basename(filename))
    extra_drivlist = []
    sys.stderr.write("%s\n" % filename)
    if parse_file(filename) :
        sys.exit(1)

    if is_driver_switch != 0 :
        # output a count
        if (len(extra_drivlist)==0) :
            sys.stderr.write("No drivers found\n")
            sys.exit(1)

        # add a reference to the ___empty driver
        extra_drivlist.append("___empty")

        # start with a header
        if not header_outputed :
            print('#include "emu.h"\n');
            print('#include "drivenum.h"\n');
            header_outputed = True

        #output the list of externs first
        for drv in sorted(extra_drivlist):
            print("GAME_EXTERN(%s);" % drv)
        print("")

        # then output the array
        print("const game_driver * const driver_switch::%sdrivers[%d] =" % (name, len(extra_drivlist)+1))
        print("{")
        for drv in sorted(extra_drivlist):
            print("\t&GAME_NAME(%s)," % drv)
        print("0");
        print("};");
        print("");
=======
            if drivname[0]=='@':
               curr_source= drivname[8:]
               continue
            if not all(((c >='a' and c<='z') or (c>='0' and c<='9') or c=='_') for c in drivname):
               sys.stderr.write("%s:%d - Invalid character in driver \"%s\"\n" % (srcfile,  linenum,  drivname))
               return 1
            else:
               if (curr_source == '') or (len(sourcelist)==0) or (curr_source in sourcelist):
                   drivlist.append(drivname)
    return 0

def parse_filter_file(srcfile):
    try:
        fp = open(srcfile, 'rt')
    except IOError:
        sys.stderr.write("Unable to open filter file '%s'\n" % srcfile)
        return 1
    in_comment = 0
    linenum = 0
    for line in fp.readlines():
        sourcename = ''
        linenum+=1
        srcptr = 0
        while srcptr < len(line):
            c = line[srcptr]
            srcptr+=1
            if c==13 or c==10:
                if c==13 and line[srcptr]==10:
                    srcptr+=1
                continue
            if c==' ' or c==9:
                continue
            if in_comment==1 and c=='*' and line[srcptr]=='/' :
                srcptr+=1
                in_comment = 0
                continue
            if in_comment:
                continue
            if c=='/' and line[srcptr]=='*' :
                srcptr+=1
                in_comment = 1
                continue
            if c=='/' and line[srcptr]=='/' :
                break
            sourcename += c
        sourcename = sourcename.strip()
        if len(sourcename)>0:
            if sourcename[0]=='#':
               sys.stderr.write("Importing drivers from '%s'\n" % sourcename[1:])
               parse_filter_file(sourcename[1:])
               continue
            if sourcename[0]=='+':
               filter_addlist.append(sourcename[1:])
               continue
            if sourcename[0]=='-':
               filter_removelist.append(sourcename[1:])
               continue
            if not all(((c >='a' and c<='z') or (c>='0' and c<='9') or c=='_' or c=='.' or c=='-') for c in sourcename):
               sys.stderr.write("%s:%d - Invalid character in driver \"%s\"\n" % (srcfile,  linenum,  sourcename))
               return 1
            else:               
               sourcelist.append(sourcename)
    return 0


if len(sys.argv) < 2 or len(sys.argv) > 3:
    print('Usage:')
    print('  makelist <source.lst> [<filter.flt>]')
    sys.exit(0)

if len(sys.argv) == 3:
    if parse_filter_file(sys.argv[2]) :
        sys.exit(1)
    sys.stderr.write("%d source file(s) found\n" % len(sourcelist))

if parse_file(sys.argv[1]) :
    sys.exit(1)
>>>>>>> upstream/master

# output a count
if len(drivlist)==0 :
    sys.stderr.write("No drivers found\n")
    sys.exit(1)

<<<<<<< HEAD
sys.stderr.write("%d drivers found\n" % len(drivlist))
=======
for x in filter_addlist:
    drivlist.append(x)

drivlist = [x for x in drivlist if (x not in filter_removelist)]

sys.stderr.write("%d driver(s) found\n" % len(drivlist))
>>>>>>> upstream/master

# add a reference to the ___empty driver
drivlist.append("___empty")

# start with a header
<<<<<<< HEAD
if not header_outputed :
    print('#include "emu.h"\n')
    print('#include "drivenum.h"\n')
    header_outputed = True
=======
print('#include "emu.h"\n')
print('#include "drivenum.h"\n')
>>>>>>> upstream/master

#output the list of externs first
for drv in sorted(drivlist):
    print("GAME_EXTERN(%s);" % drv)
print("")

# then output the array
<<<<<<< HEAD
if is_driver_switch != 0 :
    print("const game_driver * driver_list::s_drivers_sorted[%d] =" % len(drivlist))
else:
    print("const game_driver * const driver_list::s_drivers_sorted[%d] =" % len(drivlist))
=======
print("const game_driver * const driver_list::s_drivers_sorted[%d] =" % len(drivlist))
>>>>>>> upstream/master
print("{")
for drv in sorted(drivlist):
    print("\t&GAME_NAME(%s)," % drv)
print("};")
print("")

# also output a global count
<<<<<<< HEAD
print("int driver_list::s_driver_count = %d;\n" % len(drivlist))
=======
print("std::size_t const driver_list::s_driver_count = %d;\n" % len(drivlist))
>>>>>>> upstream/master
