[GENie](https://github.com/bkaradzic/genie#what-is-it) - Project generator tool
===============================================================================

What is it?
-----------

<<<<<<< HEAD
**GENie** is project generator tool. It automagically generates project from Lua
script, making applying the same settings for multiple projects easy.

Supported project generators:
 * Visual Studio 2008, 2010, 2012, 2013, 2015
 * GNU Makefile

Who is using it?
----------------

https://github.com/bkaradzic/bgfx bgfx - Cross-platform, graphics API
agnostic, "Bring Your Own Engine/Framework" style rendering library.

https://github.com/Psybrus/Psybrus Psybrus Engine & Toolchain

https://github.com/dariomanesku/cmftstudio cmftStudio - cubemap filtering tool

https://github.com/mamedev/mame MAME - Multiple Arcade Machine Emulator

http://sol.gfxile.net/soloud SoLoud is an easy to use, free, 
portable c/c++ audio engine for games.

https://github.com/andr3wmac/Torque6 Torque 6 is an MIT licensed 3D engine
loosely based on Torque2D. Being neither Torque2D or Torque3D it is the 6th
derivative of the original Torque Engine.
=======
**GENie** (pronounced as Jenny) is project generator tool. It automagically
generates project from Lua script, making applying the same settings for
multiple projects easy.

Supported project generators:
 * FASTBuild (experimental)
 * GNU Makefile
 * Ninja (experimental)
 * Qbs / QtCreator (experimental)
 * Visual Studio 2008, 2010, 2012, 2013, 2015, 2017
 * XCode
>>>>>>> upstream/master

Download (stable)
-----------------

<<<<<<< HEAD
[![Build Status](https://travis-ci.org/bkaradzic/genie.svg?branch=master)](https://travis-ci.org/bkaradzic/genie)

	version 331 (commit 3653d092d054d5725cab272b6a5fd55edfd9a4ba)
=======
[![Build Status](https://travis-ci.org/bkaradzic/GENie.svg?branch=master)](https://travis-ci.org/bkaradzic/GENie)

	version 807 (commit 83efdca3c3c63cb47bd1b4daa8b73d526841f900)
>>>>>>> upstream/master

Linux:  
https://github.com/bkaradzic/bx/raw/master/tools/bin/linux/genie

OSX:  
https://github.com/bkaradzic/bx/raw/master/tools/bin/darwin/genie

Windows:  
https://github.com/bkaradzic/bx/raw/master/tools/bin/windows/genie.exe

Building (dev)
--------------

	$ git clone https://github.com/bkaradzic/genie
	$ cd genie
	$ make

Documentation
-------------

<<<<<<< HEAD
[Scripting Reference](https://github.com/bkaradzic/genie/blob/master/docs/scripting-reference.md#scripting-reference)
=======
[Scripting Reference](https://github.com/bkaradzic/genie/blob/master/docs/scripting-reference.md#scripting-reference)  
[Introduction to GENie - CppCon 2016](https://onedrive.live.com/view.aspx?cid=171ee76e679935c8&page=view&resid=171EE76E679935C8!139573&parId=171EE76E679935C8!18835&authkey=!AKv_SGrgJwxDGDg&app=PowerPoint)
>>>>>>> upstream/master

History
-------

Initial version of **GENie** is fork of Premake 4.4 beta 5, and there is no
intention to keep it compatible with it.

## Changelog (since fork)

 - Added vs2013 support.
 - Added hash UUID support. `os.uuid(<string>)` should produce consistent UUID.
 - Added search for default script. Default script name is changed to genie.lua
   (solution.lua and premake4.lua are also allowed), and it can be located in
   `scripts` directory.
 - Updated Lua from 5.1.4 to 5.3.0.
 - Disabled `SmallerTypeCheck` VS option when `ExtraWarnings` is set (need to
   move it into separate option).
 - New versioning scheme based on revision number from git.
 - Added `startproject "<project name>"` to set default project in VS.
 - Removed `NoMinimalRebuild` and added reversed logic to `EnableMinimalRebuild`.
 - Added `NoMultiProcessorCompilation` flag to disable multiprocessor
   compilation in MSVC.
 - Added ability to configure Visual Studio toolset from GENie script.
 - Added `UnsignedChar` flag to force char to be unsigned.
 - Removed vs2002, vs2003, vs2005, Solaris, and Haiku support.
 - Allow source files in the same project to have the same name. Added 
   `SingleOutputDir` flag to use single output directory (original behaviour).
 - Added WinRT support (Windows Phone 8.1, Windows Store, Universal Apps).
 - Added `removeflags`, `removelinks`.
 - Added vs2015 support.
 - Added `targetsubdir`.
 - Added support for solution folders `group`.
 - Added `options` section (and `ForceCpp` to enforce C++ compile even if
   extension is for C files)
 - Added `msgcompile`, `msgresource`, `msglinking` and `msgarchiving` as
   overrides for make messages.
 - Added `messageskip` list to disable some of compiler messages.
<<<<<<< HEAD
 - Added `buildoptions_c`, `buildoptions_cpp`, `buildoptions_objc` for
=======
 - Added `buildoptions_c`, `buildoptions_cpp`, `buildoptions_objc`,
   `buildoptions_objcpp`, `buildoptions_asm`, `buildoptions_swift` for
>>>>>>> upstream/master
   configuring language specific build options.
 - Split functionality of `excludes` in `removefiles` and `excludes`. With VS
   `excludes` will exclude files from build but files will be added to project
   file. `removefiles` removes files completely from project.
 - Added support for generating PS4/Orbis projects.
<<<<<<< HEAD

## Why fork?

At the time of writing this, September 2014, Premake project is on long hiatus.
The last official release 4.3 is released in November 2010, 4.4 beta 5 was
released in November 2013, and the main developer is focusing on Premake 5.

Multiple requests for releasing new version end up with this type of [answer](http://industriousone.com/topic/premake-release-neglect-becoming-critical):

	Then help fix the bugs marked 4.4 in the SourceForge tracker so that we can
	make a release. Or review and improve the patches so that I may get them
	applied more quickly. Or pay me to do it so that I can spend more time on
	it, instead of doing other work that you value less (but which actually, you
	know, pays me).

So author has high expectations for release, but he is not working on it, but
rather working on completely different... Pay me to finish this sentence...
You get the point. :)

This long period between releases where multiple versions are in flight cause
confusion for users who are not familiar with Premake, and they just need to
use Premake to generate project files for project they are interested in.

I've been using Premake for [a while](https://web.archive.org/web/20120119020903/http://carbongames.com/2011/08/Premake),
I really like it's simplicity, and that it does one thing really well.

I was considering replacing Premake with other build systems that also could
generate project files, but all these projects fail at being simple and doing
only one thing. I don't need build system, or package manager, etc. just a
simple project generator.

In conclusion, forking it and maintaining it is not much different from current
state of Premake, it's just acknowledging the problem, and dealing with it.
=======
 - Fixed PCH race when using concurrent Makefile build.
 - Added Green Hills Software compiler support.
 - Added edit & continue support for 64-bit builds in VS2013 upwards.
 - Added `windowstargetplatformversion` to specify VS Windows target version.
 - Added `NoWinRT` flag to disable WinRT CX builds.
 - Added `NoBufferSecurityCheck` flag to disable security checks in VS.
 - Added `nopch` file list to exclude files from using PCH.
 - Added `EnableAVX` and `EnableAVX2` flags to enable enhanced instruction set.
 - Added FASTBuild (.bff) project generator.
 - Added Vala language support.
 - Added MASM support for Visual Studio projects.
 - Added `userincludedirs` for include header with angle brackets and quotes
   search path control.
 - Detect when generated project files are not changing, and skip writing over
   existing project files.
 - Added Ninja project generator.
 - Added ability to specify MSVC "Old Style" debug info format with
   `C7DebugInfo`.
 - Added some support for per-configuration `files` lists.
 - Removed `clean` action.
 - Added support for QtCreator via Qbs build tool.
 - Added .natvis file type support for Visual Studio.
 - Added Swift language support for make and ninja build generators.
 - Removed CodeBlocks and CodeLite support.
 - Added vs2017 support.
 - Removed vs2008 support.
 - Added `removeplatforms` that removes VS build target platforms.

Debugging GENie scripts
-----------------------

It is possible to debug build scripts using [ZeroBrane Studio][zbs]. You must
compile GENie in debug mode

    $ make config=debug

This ensures the core lua scripts are loaded from disk rather than compiled
into the GENie binary. Create a file named `debug.lua` as a sibling to your
main `genie.lua` script with the following content:

    local zb_path = <path to ZeroBraneStudio>
    local cpaths = {
        string.format("%s/bin/lib?.dylib;%s/bin/clibs53/?.dylib;", zb_path, zb_path),
        package.cpath,
    }
    package.cpath = table.concat(cpaths, ';')

    local paths = {
        string.format('%s/lualibs/?.lua;%s/lualibs/?/?.lua', zb_path, zb_path),
        string.format('%s/lualibs/?/init.lua;%s/lualibs/?/?/?.lua', zb_path, zb_path),
        string.format('%s/lualibs/?/?/init.lua', zb),
        package.path,
    }
    package.path = table.concat(paths, ';')

    require('mobdebug').start()

**NOTE:** update `zb_path` to refer to the root of your ZeroBrane Studio
install. For reference, you should find `lualibs` in you `zb_path` folder

To debug, make sure ZBS is listening for debug connections and add
`dofile("debug.lua")` to `genie.lua`

Who is using it?
----------------

https://github.com/bkaradzic/bgfx bgfx - Cross-platform, graphics API
agnostic, "Bring Your Own Engine/Framework" style rendering library.

https://github.com/Psybrus/Psybrus Psybrus Engine & Toolchain

https://github.com/dariomanesku/cmftstudio cmftStudio - cubemap filtering tool

https://github.com/mamedev/mame MAME - Multiple Arcade Machine Emulator

http://sol.gfxile.net/soloud SoLoud is an easy to use, free, 
portable c/c++ audio engine for games.

https://github.com/andr3wmac/Torque6 Torque 6 is an MIT licensed 3D engine
loosely based on Torque2D. Being neither Torque2D or Torque3D it is the 6th
derivative of the original Torque Engine.

http://mtuner.net/ is a memory profiler and memory leak finder for Windows, PS4,
PS3.
>>>>>>> upstream/master

[License](https://github.com/bkaradzic/genie/blob/master/LICENSE)
-----------------------------------------------------------------

	GENie
<<<<<<< HEAD
	Copyright (c) 2014-2015 Branimir Karadžić, Neil Richardson, Mike Popoloski,
	Drew Solomon, Ted de Munnik, Miodrag Milanović, Brett Vickers,
	Terry Hendrix II.
=======
	Copyright (c) 2014-2016 Branimir Karadžić, Neil Richardson, Mike Popoloski,
	Drew Solomon, Ted de Munnik, Miodrag Milanović, Brett Vickers, Bill Freist,
	Terry Hendrix II, Ryan Juckett, Andrew Johnson, Johan Sköld,
	Alastair Murray, Patrick Munns, Jan-Eric Duden, Phil Stevens, Stuart Carnie,
	Nikolay Aleksiev, Jon Olson.
>>>>>>> upstream/master
	All rights reserved.

	https://github.com/bkaradzic/genie
	
	Redistribution and use in source and binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	
	1. Redistributions of source code must retain the above copyright notice,
		this list of conditions and the following disclaimer.
	
	2. Redistributions in binary form must reproduce the above copyright notice,
		this list of conditions and the following disclaimer in the documentation
		and/or other materials provided with the distribution.
	
	3. Neither the name of the GENie nor the names of its contributors may be 
		used to endorse or promote products derived from this software without
		specific prior written permission.
	
	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
<<<<<<< HEAD
=======

  [zbs]: https://studio.zerobrane.com
>>>>>>> upstream/master
