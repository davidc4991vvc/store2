--
<<<<<<< HEAD
-- Copyright 2010-2015 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--
 
project "bx"
	uuid "4db0b09e-d6df-11e1-a0ec-65ccdd6a022f"
	kind "StaticLib"

	configuration { "osx or ios" }
		-- OSX ar doesn't like creating archive without object files
		-- here is object file...
		prebuildcommands {
			"@echo \"void dummy() {}\" > /tmp/dummy.cpp",
		}
		files {
			"/tmp/dummy.cpp",
=======
-- Copyright 2010-2017 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bx#license-bsd-2-clause
--

project "bx"
	kind "StaticLib"

	includedirs {
		path.join(BX_DIR, "include"),
	}

	files {
		path.join(BX_DIR, "include/**.h"),
		path.join(BX_DIR, "include/**.inl"),
		path.join(BX_DIR, "src/**.cpp"),
	}

	configuration { "linux-*" }
		buildoptions {
			"-fPIC",
>>>>>>> upstream/master
		}

	configuration {}

<<<<<<< HEAD
	files {
		"../include/**.h",
	}
=======
	if _OPTIONS["with-amalgamated"] then
		excludes {
			path.join(BX_DIR, "src/commandline.cpp"),
			path.join(BX_DIR, "src/crt.cpp"),
			path.join(BX_DIR, "src/crtimpl.cpp"),
			path.join(BX_DIR, "src/debug.cpp"),
			path.join(BX_DIR, "src/dtoa.cpp"),
			path.join(BX_DIR, "src/fpumath.cpp"),
			path.join(BX_DIR, "src/mutex.cpp"),
			path.join(BX_DIR, "src/os.cpp"),
			path.join(BX_DIR, "src/sem.cpp"),
			path.join(BX_DIR, "src/sort.cpp"),
			path.join(BX_DIR, "src/string.cpp"),
			path.join(BX_DIR, "src/thread.cpp"),
			path.join(BX_DIR, "src/timer.cpp"),
		}
	else
		excludes {
			path.join(BX_DIR, "src/amalgamated.**"),
		}
	end

	configuration {}
>>>>>>> upstream/master
