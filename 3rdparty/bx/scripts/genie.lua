--
<<<<<<< HEAD
-- Copyright 2010-2015 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

=======
-- Copyright 2010-2017 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bx#license-bsd-2-clause
--

newoption {
	trigger = "with-amalgamated",
	description = "Enable amalgamated build.",
}

newoption {
	trigger = "with-crtnone",
	description = "Enable build without CRT.",
}

>>>>>>> upstream/master
solution "bx"
	configurations {
		"Debug",
		"Release",
	}

	platforms {
		"x32",
		"x64",
		"Native", -- for targets where bitness is not specified
	}

	language "C++"

BX_DIR = path.getabsolute("..")
local BX_BUILD_DIR = path.join(BX_DIR, ".build")
local BX_THIRD_PARTY_DIR = path.join(BX_DIR, "3rdparty")

<<<<<<< HEAD
defines {
	"BX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS=1"
}

=======
>>>>>>> upstream/master
dofile "toolchain.lua"
toolchain(BX_BUILD_DIR, BX_THIRD_PARTY_DIR)

function copyLib()
end

dofile "bx.lua"
<<<<<<< HEAD
dofile "unittest++.lua"
=======
>>>>>>> upstream/master
dofile "bin2c.lua"

project "bx.test"
	kind "ConsoleApp"

	debugdir (path.join(BX_DIR, "tests"))

	removeflags {
		"NoExceptions",
	}

	includedirs {
		path.join(BX_DIR, "include"),
<<<<<<< HEAD
		path.join(BX_THIRD_PARTY_DIR, "UnitTest++/src"),
	}

	links {
		"UnitTest++",
	}

	files {
		path.join(BX_DIR, "tests/**.cpp"),
		path.join(BX_DIR, "tests/**.H"),
	}

	configuration { "vs*" }

	configuration { "android*" }
		kind "ConsoleApp"
=======
		BX_THIRD_PARTY_DIR,
	}

	files {
		path.join(BX_DIR, "tests/*_test.cpp"),
		path.join(BX_DIR, "tests/*.h"),
		path.join(BX_DIR, "tests/dbg.*"),
	}

	links {
		"bx",
	}

	configuration { "vs* or mingw*" }
		links {
			"psapi",
		}

	configuration { "android*" }
		targetextension ".so"
		linkoptions {
			"-shared",
		}

	configuration { "nacl or nacl-arm" }
		targetextension ".nexe"
		links {
			"ppapi",
			"pthread",
		}

	configuration { "pnacl" }
		targetextension ".pexe"
		links {
			"ppapi",
			"pthread",
		}

	configuration { "linux-*" }
		links {
			"pthread",
		}

	configuration { "osx" }
		links {
			"Cocoa.framework",
		}

	configuration {}

	strip()

project "bx.bench"
	kind "ConsoleApp"

	debugdir (path.join(BX_DIR, "tests"))

	includedirs {
		path.join(BX_DIR, "include"),
		BX_THIRD_PARTY_DIR,
	}

	files {
		path.join(BX_DIR, "tests/*_bench.cpp"),
		path.join(BX_DIR, "tests/*_bench.h"),
		path.join(BX_DIR, "tests/dbg.*"),
	}

	links {
		"bx",
	}

	configuration { "vs* or mingw*" }
		links {
			"psapi",
		}

	configuration { "android*" }
>>>>>>> upstream/master
		targetextension ".so"
		linkoptions {
			"-shared",
		}

	configuration { "nacl or nacl-arm" }
<<<<<<< HEAD
		kind "ConsoleApp"
=======
>>>>>>> upstream/master
		targetextension ".nexe"
		links {
			"ppapi",
			"pthread",
		}

	configuration { "pnacl" }
<<<<<<< HEAD
		kind "ConsoleApp"
=======
>>>>>>> upstream/master
		targetextension ".pexe"
		links {
			"ppapi",
			"pthread",
		}

	configuration { "linux-*" }
		links {
			"pthread",
		}

	configuration { "osx" }
		links {
			"Cocoa.framework",
		}

	configuration {}

	strip()
