--
<<<<<<< HEAD
-- Copyright 2010-2015 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

project "bin2c"
	uuid "60eaa654-7d06-11e4-be8e-880965202986"
=======
-- Copyright 2010-2017 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bx#license-bsd-2-clause
--

project "bin2c"
>>>>>>> upstream/master
	kind "ConsoleApp"

	includedirs {
		"../include",
	}

	files {
		"../tools/bin2c/**.cpp",
		"../tools/bin2c/**.h",
	}

<<<<<<< HEAD
	configuration {}
=======
	links {
		"bx",
	}

	configuration { "mingw-*" }
		targetextension ".exe"

	configuration { "linux-*" }
		links {
			"pthread",
		}

	configuration {}

	strip()
>>>>>>> upstream/master
