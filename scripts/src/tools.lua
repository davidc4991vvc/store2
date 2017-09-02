-- license:BSD-3-Clause
-- copyright-holders:MAMEdev Team

---------------------------------------------------------------------------
--
--   tools.lua
--
--   Rules for the building of tools
--
---------------------------------------------------------------------------

--------------------------------------------------
-- romcmp
--------------------------------------------------

project("romcmp")
uuid ("1b40275b-194c-497b-8abd-9338775a21b8")
<<<<<<< HEAD
kind "ConsoleApp"	

flags {
	"Symbols", -- always include minimum symbols for executables 	
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
>>>>>>> upstream/master
	targetdir(MAME_DIR)
end

links {
	"utils",
<<<<<<< HEAD
	"expat",
	"ocore_" .. _OPTIONS["osd"],
}

if _OPTIONS["with-bundled-zlib"] then
	links {
		"zlib",
	}
else
	links {
		"z",
	}
end

=======
	ext_lib("expat"),
	"7z",
	"ocore_" .. _OPTIONS["osd"],
	ext_lib("zlib"),
	ext_lib("utf8proc"),
}

>>>>>>> upstream/master
includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib/util",
}

files {
	MAME_DIR .. "src/tools/romcmp.cpp",
<<<<<<< HEAD
}

=======
	MAME_DIR .. "src/emu/emucore.cpp",
}

configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()

>>>>>>> upstream/master
--------------------------------------------------
-- chdman
--------------------------------------------------

project("chdman")
uuid ("7d948868-42db-432a-9bb5-70ce5c5f4620")
<<<<<<< HEAD
kind "ConsoleApp"	

flags {
	"Symbols", -- always include minimum symbols for executables 	
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
>>>>>>> upstream/master
	targetdir(MAME_DIR)
end

links {
	"utils",
<<<<<<< HEAD
	"expat",
	"7z",
	"ocore_" .. _OPTIONS["osd"],
}

if _OPTIONS["with-bundled-zlib"] then
	links {
		"zlib",
	}
else
	links {
		"z",
	}
end

if _OPTIONS["with-bundled-flac"] then
	links {
		"flac",
	}
else
	links {
		"FLAC",
	}
end

=======
	ext_lib("expat"),
	"7z",
	"ocore_" .. _OPTIONS["osd"],
	ext_lib("zlib"),
	ext_lib("flac"),
	ext_lib("utf8proc"),
}

>>>>>>> upstream/master
includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib/util",
	MAME_DIR .. "3rdparty",
}
<<<<<<< HEAD

files {
	MAME_DIR .. "src/tools/chdman.cpp",
	MAME_DIR .. "src/version.cpp",
}

=======
includedirs {
	ext_includedir("flac"),
}

files {
	MAME_DIR .. "src/tools/chdman.cpp",
	MAME_DIR .. "src/emu/emucore.cpp",
	GEN_DIR .. "version.cpp",
}

configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()

>>>>>>> upstream/master
--------------------------------------------------
-- jedutil
--------------------------------------------------

project("jedutil")
uuid ("bda60edb-f7f5-489f-b232-23d33c43dda1")
<<<<<<< HEAD
kind "ConsoleApp"	

flags {
	"Symbols", -- always include minimum symbols for executables 	
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
>>>>>>> upstream/master
	targetdir(MAME_DIR)
end

links {
	"utils",
<<<<<<< HEAD
	"expat",
	"ocore_" .. _OPTIONS["osd"],
}

if _OPTIONS["with-bundled-zlib"] then
	links {
		"zlib",
	}
else
	links {
		"z",
	}
end

=======
	ext_lib("expat"),
	"ocore_" .. _OPTIONS["osd"],
	ext_lib("zlib"),
	ext_lib("utf8proc"),
}

>>>>>>> upstream/master
includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib/util",
}

files {
	MAME_DIR .. "src/tools/jedutil.cpp",
<<<<<<< HEAD
}

=======
	MAME_DIR .. "src/emu/emucore.cpp",
}

configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()

>>>>>>> upstream/master
--------------------------------------------------
-- unidasm
--------------------------------------------------

project("unidasm")
uuid ("65f81d3b-299a-4b08-a3fa-d5241afa9fd1")
<<<<<<< HEAD
kind "ConsoleApp"	

flags {
	"Symbols", -- always include minimum symbols for executables 	
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
>>>>>>> upstream/master
	targetdir(MAME_DIR)
end

links {
	"dasm",
	"utils",
<<<<<<< HEAD
	"expat",
	"7z",	
	"ocore_" .. _OPTIONS["osd"],
}

if _OPTIONS["with-bundled-zlib"] then
	links {
		"zlib",
	}
else
	links {
		"z",
	}
end

if _OPTIONS["with-bundled-flac"] then
	links {
		"flac",
	}
else
	links {
		"FLAC",
	}
end

includedirs {
	MAME_DIR .. "src/osd",
=======
	ext_lib("expat"),
	"7z",
	"ocore_" .. _OPTIONS["osd"],
	ext_lib("zlib"),
	ext_lib("flac"),
	ext_lib("utf8proc"),
}

includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/devices",
>>>>>>> upstream/master
	MAME_DIR .. "src/emu",
	MAME_DIR .. "src/lib/util",
	MAME_DIR .. "3rdparty",
}

files {
	MAME_DIR .. "src/tools/unidasm.cpp",
	MAME_DIR .. "src/emu/emucore.cpp",
}

<<<<<<< HEAD
=======
configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()
>>>>>>> upstream/master

--------------------------------------------------
-- ldresample
--------------------------------------------------

project("ldresample")
uuid ("3401561a-4407-4e13-9c6d-c0801330f7cc")
<<<<<<< HEAD
kind "ConsoleApp"	

flags {
	"Symbols", -- always include minimum symbols for executables 	
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
>>>>>>> upstream/master
	targetdir(MAME_DIR)
end

links {
	"utils",
<<<<<<< HEAD
	"expat",
	"7z",	
	"ocore_" .. _OPTIONS["osd"],
}

if _OPTIONS["with-bundled-zlib"] then
	links {
		"zlib",
	}
else
	links {
		"z",
	}
end

if _OPTIONS["with-bundled-flac"] then
	links {
		"flac",
	}
else
	links {
		"FLAC",
	}
end

=======
	ext_lib("expat"),
	"7z",
	"ocore_" .. _OPTIONS["osd"],
	ext_lib("zlib"),
	ext_lib("flac"),
	ext_lib("utf8proc"),
}

>>>>>>> upstream/master
includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib/util",
	MAME_DIR .. "3rdparty",
}
<<<<<<< HEAD

files {
	MAME_DIR .. "src/tools/ldresample.cpp",
}

=======
includedirs {
	ext_includedir("flac"),
}

files {
	MAME_DIR .. "src/tools/ldresample.cpp",
	MAME_DIR .. "src/emu/emucore.cpp",
}

configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()

>>>>>>> upstream/master
--------------------------------------------------
-- ldverify
--------------------------------------------------

project("ldverify")
uuid ("3e66560d-b928-4227-928b-eadd0a10f00a")
<<<<<<< HEAD
kind "ConsoleApp"	

flags {
	"Symbols", -- always include minimum symbols for executables 	
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
>>>>>>> upstream/master
	targetdir(MAME_DIR)
end

links {
	"utils",
<<<<<<< HEAD
	"expat",
	"7z",	
	"ocore_" .. _OPTIONS["osd"],
}

if _OPTIONS["with-bundled-zlib"] then
	links {
		"zlib",
	}
else
	links {
		"z",
	}
end

if _OPTIONS["with-bundled-flac"] then
	links {
		"flac",
	}
else
	links {
		"FLAC",
	}
end

=======
	ext_lib("expat"),
	"7z",
	"ocore_" .. _OPTIONS["osd"],
	ext_lib("zlib"),
	ext_lib("flac"),
	ext_lib("utf8proc"),
}

>>>>>>> upstream/master
includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib/util",
	MAME_DIR .. "3rdparty",
}
<<<<<<< HEAD

files {
	MAME_DIR .. "src/tools/ldverify.cpp",
}

=======
includedirs {
	ext_includedir("flac"),
}

files {
	MAME_DIR .. "src/tools/ldverify.cpp",
	MAME_DIR .. "src/emu/emucore.cpp",
}

configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()

>>>>>>> upstream/master
--------------------------------------------------
-- regrep
--------------------------------------------------

project("regrep")
uuid ("7f6de580-d800-4e8d-bed6-9fc86829584d")
<<<<<<< HEAD
kind "ConsoleApp"	

flags {
	"Symbols", -- always include minimum symbols for executables 	
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
>>>>>>> upstream/master
	targetdir(MAME_DIR)
end

links {
	"utils",
<<<<<<< HEAD
	"expat",
	"ocore_" .. _OPTIONS["osd"],
}

if _OPTIONS["with-bundled-zlib"] then
	links {
		"zlib",
	}
else
	links {
		"z",
	}
end

=======
	ext_lib("expat"),
	"ocore_" .. _OPTIONS["osd"],
	ext_lib("zlib"),
	ext_lib("utf8proc"),
}

>>>>>>> upstream/master
includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib/util",
}

files {
	MAME_DIR .. "src/tools/regrep.cpp",
<<<<<<< HEAD
}

=======
	MAME_DIR .. "src/emu/emucore.cpp",
}

configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()

>>>>>>> upstream/master
--------------------------------------------------
-- srcclean
---------------------------------------------------

project("srcclean")
uuid ("4dd58139-313a-42c5-965d-f378bdeed220")
<<<<<<< HEAD
kind "ConsoleApp"	

flags {
	"Symbols", -- always include minimum symbols for executables 	
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
>>>>>>> upstream/master
	targetdir(MAME_DIR)
end

links {
	"utils",
<<<<<<< HEAD
	"expat",
	"ocore_" .. _OPTIONS["osd"],
}

if _OPTIONS["with-bundled-zlib"] then
	links {
		"zlib",
	}
else
	links {
		"z",
	}
end

=======
	ext_lib("expat"),
	"ocore_" .. _OPTIONS["osd"],
	ext_lib("zlib"),
	ext_lib("utf8proc"),
}

>>>>>>> upstream/master
includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib/util",
}

files {
	MAME_DIR .. "src/tools/srcclean.cpp",
<<<<<<< HEAD
}

=======
	MAME_DIR .. "src/emu/emucore.cpp",
}

configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()

>>>>>>> upstream/master
--------------------------------------------------
-- src2html
--------------------------------------------------

project("src2html")
uuid ("b31e963a-09ef-4696-acbd-e663e35ce6f7")
<<<<<<< HEAD
kind "ConsoleApp"	

flags {
	"Symbols", -- always include minimum symbols for executables 	
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
>>>>>>> upstream/master
	targetdir(MAME_DIR)
end

links {
	"utils",
<<<<<<< HEAD
	"expat",
	"ocore_" .. _OPTIONS["osd"],
}

if _OPTIONS["with-bundled-zlib"] then
	links {
		"zlib",
	}
else
	links {
		"z",
	}
end

=======
	ext_lib("expat"),
	"ocore_" .. _OPTIONS["osd"],
	ext_lib("zlib"),
	ext_lib("utf8proc"),
}

>>>>>>> upstream/master
includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib/util",
}

files {
	MAME_DIR .. "src/tools/src2html.cpp",
<<<<<<< HEAD
}

=======
	MAME_DIR .. "src/emu/emucore.cpp",
}

configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()

>>>>>>> upstream/master
--------------------------------------------------
-- split
--------------------------------------------------

project("split")
uuid ("8ef6ff18-3199-4cc2-afd0-d64033070faa")
<<<<<<< HEAD
kind "ConsoleApp"	

flags {
	"Symbols", -- always include minimum symbols for executables 	
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
>>>>>>> upstream/master
	targetdir(MAME_DIR)
end

links {
	"utils",
<<<<<<< HEAD
	"expat",
	"7z",
	"ocore_" .. _OPTIONS["osd"],
}

if _OPTIONS["with-bundled-zlib"] then
	links {
		"zlib",
	}
else
	links {
		"z",
	}
end

if _OPTIONS["with-bundled-flac"] then
	links {
		"flac",
	}
else
	links {
		"FLAC",
	}
end

=======
	ext_lib("expat"),
	"7z",
	"ocore_" .. _OPTIONS["osd"],
	ext_lib("zlib"),
	ext_lib("flac"),
	ext_lib("utf8proc"),
}

>>>>>>> upstream/master
includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib/util",
}

files {
	MAME_DIR .. "src/tools/split.cpp",
<<<<<<< HEAD
}

=======
	MAME_DIR .. "src/emu/emucore.cpp",
}

configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()

>>>>>>> upstream/master
--------------------------------------------------
-- pngcmp
--------------------------------------------------

project("pngcmp")
uuid ("61f647d9-b129-409b-9c62-8acf98ed39be")
<<<<<<< HEAD
kind "ConsoleApp"	

flags {
	"Symbols", -- always include minimum symbols for executables 	
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
>>>>>>> upstream/master
	targetdir(MAME_DIR)
end

links {
	"utils",
<<<<<<< HEAD
	"expat",
	"ocore_" .. _OPTIONS["osd"],
}

if _OPTIONS["with-bundled-zlib"] then
	links {
		"zlib",
	}
else
	links {
		"z",
	}
end

=======
	ext_lib("expat"),
	"ocore_" .. _OPTIONS["osd"],
	ext_lib("zlib"),
	ext_lib("utf8proc"),
}

>>>>>>> upstream/master
includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib/util",
}

files {
	MAME_DIR .. "src/tools/pngcmp.cpp",
<<<<<<< HEAD
}

=======
	MAME_DIR .. "src/emu/emucore.cpp",
}

configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()

>>>>>>> upstream/master
--------------------------------------------------
-- nltool
--------------------------------------------------

project("nltool")
uuid ("853a03b7-fa37-41a8-8250-0dc23dd935d6")
<<<<<<< HEAD
kind "ConsoleApp"	

flags {
	"Symbols", -- always include minimum symbols for executables 	
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
>>>>>>> upstream/master
	targetdir(MAME_DIR)
end

links {
<<<<<<< HEAD
	"utils",
	"expat",
	"7z",
	"ocore_" .. _OPTIONS["osd"],
	"netlist",
}

if _OPTIONS["with-bundled-zlib"] then
	links {
		"zlib",
	}
else
	links {
		"z",
	}
end

if _OPTIONS["with-bundled-flac"] then
	links {
		"flac",
	}
else
	links {
		"FLAC",
	}
end

includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib/util",
	MAME_DIR .. "src/lib/netlist",
=======
	"netlist",
}

includedirs {
	MAME_DIR .. "src/lib",
>>>>>>> upstream/master
}

files {
	MAME_DIR .. "src/lib/netlist/prg/nltool.cpp",
}

<<<<<<< HEAD
=======
configuration { "mingw*" }
  linkoptions{
	"-municode",
  }
configuration { "vs*" }
  flags {
	"Unicode",
  }

configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()

>>>>>>> upstream/master
--------------------------------------------------
-- nlwav
--------------------------------------------------

project("nlwav")
uuid ("7c5396d1-2a1a-4c93-bed6-6b8fa182054a")
<<<<<<< HEAD
kind "ConsoleApp" 

flags {
  "Symbols", -- always include minimum symbols for executables  
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
  targetdir(MAME_DIR)
end

links {
  "utils",
  "ocore_" .. _OPTIONS["osd"],
  "netlist",
}

includedirs {
  MAME_DIR .. "src/osd",
  MAME_DIR .. "src/lib/util",
  MAME_DIR .. "src/lib/netlist",
}

files {
  MAME_DIR .. "src/lib/netlist/prg/nlwav.cpp",
}

=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
	targetdir(MAME_DIR)
end

links {
	"netlist",
}

includedirs {
	MAME_DIR .. "src/lib",
}

files {
	MAME_DIR .. "src/lib/netlist/prg/nlwav.cpp",
}

configuration { "mingw*" }
  linkoptions{
	"-municode",
  }
configuration { "vs*" }
  flags {
	"Unicode",
  }

configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()

>>>>>>> upstream/master
--------------------------------------------------
-- castool
--------------------------------------------------

project("castool")
uuid ("7d9ed428-e2ba-4448-832d-d882a64d5c22")
<<<<<<< HEAD
kind "ConsoleApp"	

flags {
	"Symbols", -- always include minimum symbols for executables 	
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
>>>>>>> upstream/master
	targetdir(MAME_DIR)
end

links {
	"formats",
	"utils",
<<<<<<< HEAD
	"expat",
	"7z",
	"ocore_" .. _OPTIONS["osd"],
}

if _OPTIONS["with-bundled-zlib"] then
	links {
		"zlib",
	}
else
	links {
		"z",
	}
end

if _OPTIONS["with-bundled-flac"] then
	links {
		"flac",
	}
else
	links {
		"FLAC",
	}
end

includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib",	
=======
	ext_lib("expat"),
	"7z",
	"ocore_" .. _OPTIONS["osd"],
	ext_lib("zlib"),
	ext_lib("flac"),
	ext_lib("utf8proc"),
}

includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib",
>>>>>>> upstream/master
	MAME_DIR .. "src/lib/util",
}

files {
	MAME_DIR .. "src/tools/castool.cpp",
<<<<<<< HEAD
}

=======
	MAME_DIR .. "src/emu/emucore.cpp",
}

configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()

>>>>>>> upstream/master
--------------------------------------------------
-- floptool
--------------------------------------------------

project("floptool")
uuid ("85d8e3a6-1661-4ac9-8c21-281d20cbaf5b")
<<<<<<< HEAD
kind "ConsoleApp"	

flags {
	"Symbols", -- always include minimum symbols for executables 	
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
>>>>>>> upstream/master
	targetdir(MAME_DIR)
end

links {
	"formats",
	"emu",
	"utils",
<<<<<<< HEAD
	"expat",
	"7z",
	"ocore_" .. _OPTIONS["osd"],
}

if _OPTIONS["with-bundled-zlib"] then
	links {
		"zlib",
	}
else
	links {
		"z",
	}
end

if _OPTIONS["with-bundled-flac"] then
	links {
		"flac",
	}
else
	links {
		"FLAC",
	}
end

includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib",	
=======
	ext_lib("expat"),
	"7z",
	"ocore_" .. _OPTIONS["osd"],
	ext_lib("zlib"),
	ext_lib("flac"),
	ext_lib("utf8proc"),
}

includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib",
>>>>>>> upstream/master
	MAME_DIR .. "src/lib/util",
}

files {
	MAME_DIR .. "src/tools/floptool.cpp",
<<<<<<< HEAD
}

=======
	MAME_DIR .. "src/emu/emucore.cpp",
}

configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()

>>>>>>> upstream/master
--------------------------------------------------
-- imgtool
--------------------------------------------------

project("imgtool")
uuid ("f3707807-e587-4297-a5d8-bc98f3d0b1ca")
<<<<<<< HEAD
kind "ConsoleApp"	

flags {
	"Symbols", -- always include minimum symbols for executables 	
}

if _OPTIONS["SEPARATE_BIN"]~="1" then 
=======
kind "ConsoleApp"

flags {
	"Symbols", -- always include minimum symbols for executables
}

if _OPTIONS["SEPARATE_BIN"]~="1" then
>>>>>>> upstream/master
	targetdir(MAME_DIR)
end

links {
	"formats",
	"emu",
	"utils",
<<<<<<< HEAD
	"expat",
	"7z",
	"ocore_" .. _OPTIONS["osd"],
}

if _OPTIONS["with-bundled-zlib"] then
	links {
		"zlib",
	}
else
	links {
		"z",
	}
end

if _OPTIONS["with-bundled-flac"] then
	links {
		"flac",
	}
else
	links {
		"FLAC",
	}
end

includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib",	
	MAME_DIR .. "src/lib/util",
	MAME_DIR .. "3rdparty/zlib",
	MAME_DIR .. "src/tools/imgtool",	
=======
	ext_lib("expat"),
	"7z",
	"ocore_" .. _OPTIONS["osd"],
	ext_lib("zlib"),
	ext_lib("flac"),
	ext_lib("utf8proc"),
}

includedirs {
	MAME_DIR .. "src/osd",
	MAME_DIR .. "src/lib",
	MAME_DIR .. "src/lib/util",
	ext_includedir("zlib"),
	MAME_DIR .. "src/tools/imgtool",
>>>>>>> upstream/master
}

files {
	MAME_DIR .. "src/tools/imgtool/main.cpp",
	MAME_DIR .. "src/tools/imgtool/main.h",
	MAME_DIR .. "src/tools/imgtool/stream.cpp",
	MAME_DIR .. "src/tools/imgtool/stream.h",
	MAME_DIR .. "src/tools/imgtool/library.cpp",
	MAME_DIR .. "src/tools/imgtool/library.h",
	MAME_DIR .. "src/tools/imgtool/modules.cpp",
	MAME_DIR .. "src/tools/imgtool/modules.h",
	MAME_DIR .. "src/tools/imgtool/iflopimg.cpp",
	MAME_DIR .. "src/tools/imgtool/iflopimg.h",
	MAME_DIR .. "src/tools/imgtool/filter.cpp",
	MAME_DIR .. "src/tools/imgtool/filter.h",
	MAME_DIR .. "src/tools/imgtool/filteoln.cpp",
	MAME_DIR .. "src/tools/imgtool/filtbas.cpp",
	MAME_DIR .. "src/tools/imgtool/imgtool.cpp",
	MAME_DIR .. "src/tools/imgtool/imgtool.h",
	MAME_DIR .. "src/tools/imgtool/imgterrs.cpp",
<<<<<<< HEAD
	MAME_DIR .. "src/tools/imgtool/imgterrs.h",	
	MAME_DIR .. "src/tools/imgtool/imghd.cpp", 
=======
	MAME_DIR .. "src/tools/imgtool/imgterrs.h",
	MAME_DIR .. "src/tools/imgtool/imghd.cpp",
>>>>>>> upstream/master
	MAME_DIR .. "src/tools/imgtool/imghd.h",
	MAME_DIR .. "src/tools/imgtool/charconv.cpp",
	MAME_DIR .. "src/tools/imgtool/charconv.h",
	MAME_DIR .. "src/tools/imgtool/formats/vt_dsk.cpp",
	MAME_DIR .. "src/tools/imgtool/formats/vt_dsk.h",
	MAME_DIR .. "src/tools/imgtool/formats/coco_dsk.cpp",
<<<<<<< HEAD
	MAME_DIR .. "src/tools/imgtool/formats/coco_dsk.h",	
=======
	MAME_DIR .. "src/tools/imgtool/formats/coco_dsk.h",
>>>>>>> upstream/master
	MAME_DIR .. "src/tools/imgtool/modules/amiga.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/macbin.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/rsdos.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/os9.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/mac.cpp",
<<<<<<< HEAD
	MAME_DIR .. "src/tools/imgtool/modules/ti99.cpp", 
=======
	MAME_DIR .. "src/tools/imgtool/modules/ti99.cpp",
>>>>>>> upstream/master
	MAME_DIR .. "src/tools/imgtool/modules/ti990hd.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/concept.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/fat.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/fat.h",
	MAME_DIR .. "src/tools/imgtool/modules/pc_flop.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/pc_hard.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/prodos.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/vzdos.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/thomson.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/macutil.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/macutil.h",
	MAME_DIR .. "src/tools/imgtool/modules/cybiko.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/cybikoxt.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/psion.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/bml3.cpp",
	MAME_DIR .. "src/tools/imgtool/modules/hp48.cpp",
<<<<<<< HEAD
}
=======
		MAME_DIR .. "src/tools/imgtool/modules/hp9845_tape.cpp",
}

configuration { "mingw*" or "vs*" }
	targetextension ".exe"

configuration { }

strip()

--------------------------------------------------
-- aueffectutil
--------------------------------------------------

if _OPTIONS["targetos"] == "macosx" then
	project("aueffectutil")
		uuid ("3db8316d-fad7-4f5b-b46a-99373c91550e")
		kind "ConsoleApp"

		flags {
			"Symbols", -- always include minimum symbols for executables
		}

		if _OPTIONS["SEPARATE_BIN"]~="1" then
			targetdir(MAME_DIR)
		end

		linkoptions {
			"-sectcreate __TEXT __info_plist " .. _MAKE.esc(MAME_DIR) .. "src/tools/aueffectutil-Info.plist",
		}

		dependency {
			{ "aueffectutil",  MAME_DIR .. "src/tools/aueffectutil-Info.plist", true  },
		}

		links {
			"AudioUnit.framework",
			"AudioToolbox.framework",
			"CoreAudio.framework",
			"CoreAudioKit.framework",
			"CoreServices.framework",
		}

		files {
			MAME_DIR .. "src/tools/aueffectutil.mm",
		}

		configuration { }

		strip()
end
>>>>>>> upstream/master
