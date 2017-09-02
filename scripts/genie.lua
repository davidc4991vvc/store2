-- license:BSD-3-Clause
-- copyright-holders:MAMEdev Team
<<<<<<< HEAD

newoption {
    trigger = 'build-dir',
    description = 'Build directory name',
=======
STANDALONE = false

-- Big project specific
premake.make.makefile_ignore = true
premake._checkgenerate = false

newoption {
	trigger = 'build-dir',
	description = 'Build directory name',
>>>>>>> upstream/master
}

premake.check_paths = true
premake.make.override = { "TARGET" }
<<<<<<< HEAD
MAME_DIR = (path.getabsolute("..") .. "/")
MAME_DIR = string.gsub(MAME_DIR, "(%s)", "\\%1")
local MAME_BUILD_DIR = (MAME_DIR .. _OPTIONS["build-dir"] .. "/")
local naclToolchain = ""

=======

premake.xcode.parameters = { 'CLANG_CXX_LANGUAGE_STANDARD = "c++14"', 'CLANG_CXX_LIBRARY = "libc++"' }

MAME_DIR = (path.getabsolute("..") .. "/")
--MAME_DIR = string.gsub(MAME_DIR, "(%s)", "\\%1")
local MAME_BUILD_DIR = (MAME_DIR .. _OPTIONS["build-dir"] .. "/")
local naclToolchain = ""

newoption {
	trigger = "precompile",
	description = "Precompiled headers generation.",
	allowed = {
		{ "0",   "Disabled"     },
		{ "1",   "Enabled"      },
	}
}
>>>>>>> upstream/master

function backtick(cmd)
	result = string.gsub(string.gsub(os.outputof(cmd), "\r?\n$", ""), " $", "")
	return result
end

function str_to_version(str)
	local val = 0
	if (str == nil or str == '') then
		return val
	end
	local cnt = 10000
	for word in string.gmatch(str, '([^.]+)') do
		val = val + tonumber(word) * cnt
		cnt = cnt / 100
	end
<<<<<<< HEAD
    return val
end

function findfunction(x)
  assert(type(x) == "string")
  local f=_G
  for v in x:gmatch("[^%.]+") do
    if type(f) ~= "table" then
       return nil, "looking for '"..v.."' expected table, not "..type(f)
    end
    f=f[v]
  end
  if type(f) == "function" then
    return f
  else
    return nil, "expected function, not "..type(f)
  end
=======
	return val
end

function findfunction(x)
	assert(type(x) == "string")
	local f=_G
	for v in x:gmatch("[^%.]+") do
	if type(f) ~= "table" then
		return nil, "looking for '"..v.."' expected table, not "..type(f)
	end
	f=f[v]
	end
	if type(f) == "function" then
	return f
	else
	return nil, "expected function, not "..type(f)
	end
>>>>>>> upstream/master
end

function layoutbuildtask(_folder, _name)
	return { MAME_DIR .. "src/".._folder.."/".. _name ..".lay" ,    GEN_DIR .. _folder .. "/".._name..".lh",
<<<<<<< HEAD
		{  MAME_DIR .. "scripts/build/file2str.py" }, {"@echo Converting src/".._folder.."/".._name..".lay...",    PYTHON .. " $(1) $(<) $(@) layout_".._name }};
=======
		{  MAME_DIR .. "scripts/build/complay.py" }, {"@echo Compressing src/".._folder.."/".._name..".lay...",    PYTHON .. " $(1) $(<) $(@) layout_".._name }};
end

function precompiledheaders()
	if _OPTIONS["precompile"]==nil or (_OPTIONS["precompile"]~=nil and _OPTIONS["precompile"]=="1") then
		configuration { "not xcode4" }
			pchheader("emu.h")
		configuration { }
	end
end

function addprojectflags()
	local version = str_to_version(_OPTIONS["gcc_version"])
	if _OPTIONS["gcc"]~=nil and string.find(_OPTIONS["gcc"], "gcc") then
		if version >= 50100 then
			buildoptions_cpp {
				"-Wsuggest-override",
			}
		end
		if version >= 60000 then
			buildoptions_cpp {
				"-flifetime-dse=1",
			}
		end
	end
>>>>>>> upstream/master
end

CPUS = {}
SOUNDS  = {}
MACHINES  = {}
VIDEOS = {}
BUSES  = {}
<<<<<<< HEAD
=======
FORMATS  = {}
>>>>>>> upstream/master

newoption {
	trigger = "with-tools",
	description = "Enable building tools.",
}

newoption {
	trigger = "with-tests",
	description = "Enable building tests.",
}

newoption {
<<<<<<< HEAD
=======
	trigger = "with-benchmarks",
	description = "Enable building benchmarks.",
}

newoption {
>>>>>>> upstream/master
	trigger = "osd",
	description = "Choose OSD layer implementation",
}

newoption {
	trigger = "targetos",
	description = "Choose target OS",
	allowed = {
<<<<<<< HEAD
		{ "android-arm",   "Android - ARM"          },
		{ "android-mips",  "Android - MIPS"         },
		{ "android-x86",   "Android - x86"          },
=======
		{ "android",       "Android"                },
>>>>>>> upstream/master
		{ "asmjs",         "Emscripten/asm.js"      },
		{ "freebsd",       "FreeBSD"                },
		{ "netbsd",        "NetBSD"                 },
		{ "openbsd",       "OpenBSD"                },
<<<<<<< HEAD
		{ "nacl",          "Native Client"          },
		{ "nacl-arm",      "Native Client - ARM"    },
		{ "pnacl",         "Native Client - PNaCl"  },
		{ "linux",     	   "Linux"                  },
		{ "ios",           "iOS"                    },
		{ "macosx",        "OSX"                    },
		{ "windows",       "Windows"                },
		{ "os2",           "OS/2 eComStation"       },
		{ "haiku",         "Haiku"                  },
		{ "solaris",       "Solaris SunOS"          },
=======
		{ "pnacl",         "Native Client - PNaCl"  },
		{ "linux",         "Linux"                  },
		{ "ios",           "iOS"                    },
		{ "macosx",        "OSX"                    },
		{ "windows",       "Windows"                },
		{ "haiku",         "Haiku"                  },
		{ "solaris",       "Solaris SunOS"          },
		{ "steamlink",     "Steam Link"             },
		{ "rpi",           "Raspberry Pi"           },
		{ "ci20",          "Creator-Ci20"           },
>>>>>>> upstream/master
	},
}

newoption {
<<<<<<< HEAD
    trigger = 'with-bundled-expat',
    description = 'Build bundled Expat library',
}

newoption {
    trigger = 'with-bundled-zlib',
    description = 'Build bundled Zlib library',
}

newoption {
    trigger = 'with-bundled-jpeg',
    description = 'Build bundled JPEG library',
}

newoption {
    trigger = 'with-bundled-flac',
    description = 'Build bundled FLAC library',
}

newoption {
    trigger = 'with-bundled-lua',
    description = 'Build bundled LUA library',
}

newoption {
    trigger = 'with-bundled-sqlite3',
    description = 'Build bundled SQLite library',
}

newoption {
    trigger = 'with-bundled-portmidi',
    description = 'Build bundled PortMidi library',
}

newoption {
    trigger = 'with-bundled-portaudio',
    description = 'Build bundled PortAudio library',
=======
	trigger = 'with-bundled-sdl2',
	description = 'Build bundled SDL2 library',
>>>>>>> upstream/master
}

newoption {
	trigger = "distro",
	description = "Choose distribution",
	allowed = {
<<<<<<< HEAD
		{ "generic", 		   "generic"         	},
=======
		{ "generic",           "generic"            },
>>>>>>> upstream/master
		{ "debian-stable",     "debian-stable"      },
		{ "ubuntu-intrepid",   "ubuntu-intrepid"    },
	},
}

newoption {
	trigger = "target",
	description = "Building target",
}

newoption {
	trigger = "subtarget",
	description = "Building subtarget",
}

newoption {
	trigger = "gcc_version",
	description = "GCC compiler version",
}

newoption {
	trigger = "CC",
	description = "CC replacement",
}

newoption {
	trigger = "CXX",
	description = "CXX replacement",
}

newoption {
	trigger = "LD",
	description = "LD replacement",
}

newoption {
<<<<<<< HEAD
=======
	trigger = "TOOLCHAIN",
	description = "Toolchain prefix"
}

newoption {
>>>>>>> upstream/master
	trigger = "PROFILE",
	description = "Enable profiling.",
}

newoption {
	trigger = "SYMBOLS",
	description = "Enable symbols.",
}

newoption {
	trigger = "SYMLEVEL",
	description = "Symbols level.",
}

newoption {
	trigger = "PROFILER",
	description = "Include the internal profiler.",
}

newoption {
	trigger = "OPTIMIZE",
	description = "Optimization level.",
}

newoption {
	trigger = "ARCHOPTS",
	description = "ARCHOPTS.",
}

newoption {
	trigger = "OPT_FLAGS",
	description = "OPT_FLAGS.",
}

newoption {
	trigger = "LDOPTS",
	description = "Additional linker options",
}

newoption {
	trigger = "MAP",
	description = "Generate a link map.",
}

newoption {
	trigger = "NOASM",
	description = "Disable implementations based on assembler code",
	allowed = {
		{ "0",  "Enable assembler code"   },
		{ "1",  "Disable assembler code"  },
	},
}

newoption {
	trigger = "BIGENDIAN",
	description = "Build for big endian target",
	allowed = {
		{ "0",  "Little endian target"   },
		{ "1",  "Big endian target"  },
	},
}

newoption {
	trigger = "FORCE_DRC_C_BACKEND",
	description = "Force DRC C backend.",
}

newoption {
	trigger = "NOWERROR",
	description = "NOWERROR",
}

newoption {
<<<<<<< HEAD
	trigger = "USE_BGFX",
	description = "Use of BGFX.",
	allowed = {
		{ "0",   "Disabled" 	},
		{ "1",   "Enabled"      },
	}
}

newoption {
	trigger = "DEPRECATED",
	description = "Generate deprecation warnings during compilation.",
	allowed = {
		{ "0",   "Disabled" 	},
=======
	trigger = "DEPRECATED",
	description = "Generate deprecation warnings during compilation.",
	allowed = {
		{ "0",   "Disabled"     },
>>>>>>> upstream/master
		{ "1",   "Enabled"      },
	}
}

newoption {
	trigger = "LTO",
	description = "Clang link time optimization.",
	allowed = {
<<<<<<< HEAD
		{ "0",   "Disabled" 	},
=======
		{ "0",   "Disabled"     },
>>>>>>> upstream/master
		{ "1",   "Enabled"      },
	}
}

newoption {
	trigger = "SSE2",
	description = "SSE2 optimized code and SSE2 code generation.",
	allowed = {
<<<<<<< HEAD
		{ "0",   "Disabled" 	},
=======
		{ "0",   "Disabled"     },
>>>>>>> upstream/master
		{ "1",   "Enabled"      },
	}
}

newoption {
	trigger = "SSE3",
	description = "SSE3 optimized code and SSE3 code generation.",
	allowed = {
<<<<<<< HEAD
		{ "0",   "Disabled" 	},
=======
		{ "0",   "Disabled"     },
>>>>>>> upstream/master
		{ "1",   "Enabled"      },
	}
}

newoption {
	trigger = "OPENMP",
	description = "OpenMP optimized code.",
	allowed = {
<<<<<<< HEAD
		{ "0",   "Disabled" 	},
		{ "1",   "Enabled"      },
	}
}

newoption {
	trigger = "CPP11",
	description = "Compile c++ code as C++11.",
	allowed = {
		{ "0",   "Disabled" 	},
=======
		{ "0",   "Disabled"     },
>>>>>>> upstream/master
		{ "1",   "Enabled"      },
	}
}

newoption {
	trigger = "FASTDEBUG",
	description = "Fast DEBUG.",
	allowed = {
<<<<<<< HEAD
		{ "0",   "Disabled" 	},
		{ "1",   "Enabled"      },
	}
}

newoption {
	trigger = "FILTER_DEPS",
	description = "Filter dependency files.",
	allowed = {
		{ "0",   "Disabled" 	},
=======
		{ "0",   "Disabled"     },
>>>>>>> upstream/master
		{ "1",   "Enabled"      },
	}
}

newoption {
	trigger = "SEPARATE_BIN",
	description = "Use separate bin folders.",
	allowed = {
<<<<<<< HEAD
		{ "0",   "Disabled" 	},
=======
		{ "0",   "Disabled"     },
>>>>>>> upstream/master
		{ "1",   "Enabled"      },
	}
}

newoption {
	trigger = "PYTHON_EXECUTABLE",
	description = "Python executable.",
}

newoption {
	trigger = "SHADOW_CHECK",
	description = "Shadow checks.",
	allowed = {
<<<<<<< HEAD
		{ "0",   "Disabled" 	},
=======
		{ "0",   "Disabled"     },
>>>>>>> upstream/master
		{ "1",   "Enabled"      },
	}
}

newoption {
	trigger = "STRIP_SYMBOLS",
	description = "Symbols stripping.",
	allowed = {
<<<<<<< HEAD
		{ "0",   "Disabled" 	},
=======
		{ "0",   "Disabled"     },
>>>>>>> upstream/master
		{ "1",   "Enabled"      },
	}
}


newoption {
	trigger = "SHLIB",
	description = "Generate shared libs.",
	allowed = {
<<<<<<< HEAD
		{ "0",   "Static libs" 	},
=======
		{ "0",   "Static libs"  },
>>>>>>> upstream/master
		{ "1",   "Shared libs"  },
	}
}

newoption {
	trigger = "SOURCES",
	description = "List of sources to compile.",
}

newoption {
<<<<<<< HEAD
	trigger = "FORCE_VERSION_COMPILE",
	description = "Force compiling of version.c file.",
	allowed = {
		{ "0",   "Disabled" 	},
		{ "1",   "Enabled"      },
	}
}

newoption {
	trigger = "ARCHITECTURE",
	description = "Processer architecture",
	value = "",
}

newoption {
	trigger = "EXTRA_SUFFIX",
	description = "Execute file suffix",
	value = "",
}

newoption {
	trigger = "USE_SCALE_EFFECTS",
	description = "Enhanced graphics filter",
}

newoption {
	trigger = "USE_UI_COLOR_DISPLAY",
	description = "Extra color table",
}

newoption {
	trigger = "USE_TRANS_UI",
	description = "Transparency in-game UI",
}

newoption {
	trigger = "USE_JOYSTICK_ID",
	description = "Joystick ID",
}

newoption {
	trigger = "USE_AUTOFIRE",
	description = "Autofire",
}

newoption {
	trigger = "USE_CUSTOM_BUTTON",
	description = "Custom button",
}

newoption {
	trigger = "USE_INP_CAPTION",
	description = "Extra caption in game playback",
}

newoption {
	trigger = "USE_SHOW_TIME",
	description = "Clock in game",
}

newoption {
	trigger = "USE_SHOW_INPUT_LOG",
	description = "Display joystick input",
}

newoption {
	trigger = "USE_PLAYBACK_END_PAUSE",
	description = "Automatic pause when playback ended",
}

newoption {
	trigger = "USE_AUDIO_SYNC",
	description = "",
}

newoption {
	trigger = "USE_IPS",
	description = "IPS",
}


newoption {
	trigger = "USE_DRIVER_SWITCH",
	description = "Switching drivers",
}

newoption {
	trigger = "USE_CMD_LIST",
	description = "Command list",
}

newoption {
	trigger = "USE_HISCORE",
	description = "Save hiscore",
}

newoption {
	trigger = "WINUI",
	description = "",
}

newoption {
	trigger = "USE_MORE_FOLDER_INFO",
	description = "",
}

newoption {
	trigger = "USE_STORY_DATAFILE",
	description = "",
}

newoption {
	trigger = "USE_SHOW_SPLASH_SCREEN",
	description = "",
}

newoption {
	trigger = "USE_VIEW_PCBINFO",
	description = "",
}

newoption {
	trigger = "USE_TREE_SHEET",
	description = "",
}

newoption {
	trigger = "USE_EXPORT_GAMELIST",
	description = "",
}

newoption {
	trigger = "USE_SHOW_UNAVAILABLE_FOLDER",
	description = "",
}
=======
	trigger = "PLATFORM",
	description = "Target machine platform (x86,arm,...)",
}

newoption {
	trigger = "DEBUG_DIR",
	description = "Default directory for debugger.",
}

newoption {
	trigger = "DEBUG_ARGS",
	description = "Arguments for running debug build.",
}

newoption {
	trigger = "WEBASSEMBLY",
	description = "Produce WebAssembly output when building with Emscripten.",
}

newoption {
	trigger = "PROJECT",
	description = "Select projects to be built. Will look into project folder for files.",
}

dofile ("extlib.lua")
>>>>>>> upstream/master

if _OPTIONS["SHLIB"]=="1" then
	LIBTYPE = "SharedLib"
else
	LIBTYPE = "StaticLib"
end

PYTHON = "python"

if _OPTIONS["PYTHON_EXECUTABLE"]~=nil then
	PYTHON = _OPTIONS["PYTHON_EXECUTABLE"]
end

if not _OPTIONS["BIGENDIAN"] then
	_OPTIONS["BIGENDIAN"] = "0"
end

if not _OPTIONS["NOASM"] then
	if _OPTIONS["targetos"]=="emscripten" then
		_OPTIONS["NOASM"] = "1"
	else
		_OPTIONS["NOASM"] = "0"
	end
end

if _OPTIONS["NOASM"]=="1" and not _OPTIONS["FORCE_DRC_C_BACKEND"] then
	_OPTIONS["FORCE_DRC_C_BACKEND"] = "1"
end

<<<<<<< HEAD
USE_BGFX = 1
if(_OPTIONS["USE_BGFX"]~=nil) then
	USE_BGFX = tonumber(_OPTIONS["USE_BGFX"])
=======
if(_OPTIONS["TOOLCHAIN"] == nil) then
	_OPTIONS['TOOLCHAIN'] = ""
>>>>>>> upstream/master
end

GEN_DIR = MAME_BUILD_DIR .. "generated/"

if (_OPTIONS["target"] == nil) then return false end
if (_OPTIONS["subtarget"] == nil) then return false end

if (_OPTIONS["target"] == _OPTIONS["subtarget"]) then
	solution (_OPTIONS["target"])
else
<<<<<<< HEAD
	solution (_OPTIONS["target"] .. _OPTIONS["subtarget"])
end

=======
	if (_OPTIONS["subtarget"]=="mess") then
		solution (_OPTIONS["subtarget"])
	else
		solution (_OPTIONS["target"] .. _OPTIONS["subtarget"])
	end
end


>>>>>>> upstream/master
configurations {
	"Debug",
	"Release",
}

<<<<<<< HEAD
platforms {
	"x32",
	"x64",
	"Native", -- for targets where bitness is not specified
}
=======
if _ACTION == "xcode4" then
	platforms {
		"x64",
	}
else
	platforms {
		"x32",
		"x64",
		"Native", -- for targets where bitness is not specified
	}
end
>>>>>>> upstream/master

language "C++"

flags {
	"StaticRuntime",
<<<<<<< HEAD
	"NoPCH",
}

configuration { "vs*" }
	flags {
		"ExtraWarnings",
		"NoEditAndContinue",
		"EnableMinimalRebuild",
=======
}

configuration { "vs*" }
	buildoptions {
		"/bigobj",
	}
	flags {
		"NoPCH",
		"ExtraWarnings",
		"NoEditAndContinue",
>>>>>>> upstream/master
	}
	if not _OPTIONS["NOWERROR"] then
		flags{
			"FatalWarnings",
		}
	end


configuration { "Debug", "vs*" }
	flags {
		"Symbols",
<<<<<<< HEAD
=======
		"NoIncrementalLink",
>>>>>>> upstream/master
	}

configuration { "Release", "vs*" }
	flags {
		"Optimize",
	}

<<<<<<< HEAD
configuration {}

local AWK = ""
if (os.is("windows")) then
	AWK_TEST = backtick("awk --version 2> NUL")
	if (AWK_TEST~='') then
		AWK = "awk"
	else
		AWK_TEST = backtick("gawk --version 2> NUL")
		if (AWK_TEST~='') then
			AWK = "gawk"
		end
	end
else
	AWK_TEST = backtick("awk --version 2> /dev/null")
	if (AWK_TEST~='') then
		AWK = "awk"
	else
		AWK_TEST = backtick("gawk --version 2> /dev/null")
		if (AWK_TEST~='') then
			AWK = "gawk"
		end
	end
end

if (_OPTIONS["FILTER_DEPS"]=="1") and (AWK~='') then
	postcompiletasks {
		AWK .. " -f ../../../../../scripts/depfilter.awk $(@:%.o=%.d) > $(@:%.o=%.dep)",
		"mv $(@:%.o=%.dep) $(@:%.o=%.d)",
	}
=======
-- Force VS2015/17 targets to use bundled SDL2
if string.sub(_ACTION,1,4) == "vs20" and _OPTIONS["osd"]=="sdl" then
	if _OPTIONS["with-bundled-sdl2"]==nil then
		_OPTIONS["with-bundled-sdl2"] = "1"
	end
end
-- Build SDL2 for Android
if _OPTIONS["targetos"] == "android" then
	_OPTIONS["with-bundled-sdl2"] = "1"
end

configuration {}

if _OPTIONS["osd"] == "uwp" then
	windowstargetplatformversion("10.0.14393.0")
	windowstargetplatformminversion("10.0.14393.0")
	premake._filelevelconfig = true
>>>>>>> upstream/master
end

msgcompile ("Compiling $(subst ../,,$<)...")

msgcompile_objc ("Objective-C compiling $(subst ../,,$<)...")

msgresource ("Compiling resources $(subst ../,,$<)...")

msglinking ("Linking $(notdir $@)...")

msgarchiving ("Archiving $(notdir $@)...")

<<<<<<< HEAD
messageskip { "SkipCreatingMessage", "SkipBuildingMessage", "SkipCleaningMessage" }

if (_OPTIONS["SOURCES"] == nil) then
=======
msgprecompile ("Precompiling $(subst ../,,$<)...")

messageskip { "SkipCreatingMessage", "SkipBuildingMessage", "SkipCleaningMessage" }

if (_OPTIONS["PROJECT"] ~= nil) then
	PROJECT_DIR = path.join(path.getabsolute(".."),"projects",_OPTIONS["PROJECT"]) .. "/"
	if (not os.isfile(path.join("..", "projects", _OPTIONS["PROJECT"], "scripts", "target", _OPTIONS["target"],_OPTIONS["subtarget"] .. ".lua"))) then
		error("File definition for TARGET=" .. _OPTIONS["target"] .. " SUBTARGET=" .. _OPTIONS["subtarget"] .. " does not exist")
	end
	dofile (path.join(".." ,"projects", _OPTIONS["PROJECT"], "scripts", "target", _OPTIONS["target"],_OPTIONS["subtarget"] .. ".lua"))
end
if (_OPTIONS["SOURCES"] == nil and _OPTIONS["PROJECT"] == nil) then
>>>>>>> upstream/master
	if (not os.isfile(path.join("target", _OPTIONS["target"],_OPTIONS["subtarget"] .. ".lua"))) then
		error("File definition for TARGET=" .. _OPTIONS["target"] .. " SUBTARGET=" .. _OPTIONS["subtarget"] .. " does not exist")
	end
	dofile (path.join("target", _OPTIONS["target"],_OPTIONS["subtarget"] .. ".lua"))
<<<<<<< HEAD
else
	OUT_STR = os.outputof( PYTHON .. " " .. MAME_DIR .. "scripts/build/makedep.py " .. MAME_DIR .. " " .. _OPTIONS["SOURCES"] .. " target " .. _OPTIONS["subtarget"])
	load(OUT_STR)()
	os.outputof( PYTHON .. " " .. MAME_DIR .. "scripts/build/makedep.py " .. MAME_DIR .. " " .. _OPTIONS["SOURCES"] .. " drivers " .. _OPTIONS["subtarget"] .. " > ".. GEN_DIR  .. _OPTIONS["target"] .. "/" .. _OPTIONS["subtarget"].."/drivlist.cpp")
end
configuration { "gmake" }
if _OPTIONS["CPP11"]~="1" then
	defines {
		"nullptr=NULL" -- getting ready for C++11
	}
end
=======
end

configuration { "gmake or ninja" }
>>>>>>> upstream/master
	flags {
		"SingleOutputDir",
	}

dofile ("toolchain.lua")

<<<<<<< HEAD

=======
>>>>>>> upstream/master
if _OPTIONS["targetos"]=="windows" then
	configuration { "x64" }
		defines {
			"X64_WINDOWS_ABI",
		}
	configuration { }
end

-- Avoid error when invoking genie --help.
if (_ACTION == nil) then return false end

-- define PTR64 if we are a 64-bit target
<<<<<<< HEAD
configuration { "x64" }
	defines { "PTR64=1" }

-- map the INLINE to something digestible by GCC
configuration { "gmake" }
	buildoptions_cpp {
		"-DINLINE=\"static inline\"",
	}
	buildoptions_objc {
		"-DINLINE=\"static inline\"",
	}
configuration { "xcode4*" }
	buildoptions {
		"-DINLINE=\"static inline\"",
	}

configuration { "vs*" }
	defines {
		"INLINE=static inline",
	}

=======
configuration { "x64 or android-*64"}
	defines { "PTR64=1" }

>>>>>>> upstream/master
-- define MAME_DEBUG if we are a debugging build
configuration { "Debug" }
	defines {
		"MAME_DEBUG",
		"MAME_PROFILER",
<<<<<<< HEAD
	}
=======
--      "BGFX_CONFIG_DEBUG=1",
	}

>>>>>>> upstream/master
if _OPTIONS["FASTDEBUG"]=="1" then
	defines {
		"MAME_DEBUG_FAST"
	}
end

configuration { }

if _OPTIONS["PROFILER"]=="1" then
	defines{
		"MAME_PROFILER", -- define MAME_PROFILER if we are a profiling build
	}
end

configuration { "Release" }
	defines {
		"NDEBUG",
	}

configuration { }

<<<<<<< HEAD
-- CR/LF setup: use both on win32/os2, CR only on everything else
if _OPTIONS["targetos"]=="windows" or _OPTIONS["targetos"]=="os2" then
=======
-- CR/LF setup: use on win32, CR only on everything else
if _OPTIONS["targetos"]=="windows" then
>>>>>>> upstream/master
	defines {
		"CRLF=3",
	}
else
	defines {
		"CRLF=2",
	}
end


if _OPTIONS["BIGENDIAN"]=="1" then
	if _OPTIONS["targetos"]=="macosx" then
		defines {
			"OSX_PPC",
		}
		buildoptions {
			"-Wno-unused-label",
			"-flax-vector-conversions",
		}
		if _OPTIONS["SYMBOLS"] then
			buildoptions {
				"-mlong-branch",
			}
		end
		configuration { "x64" }
			buildoptions {
				"-arch ppc64",
			}
			linkoptions {
				"-arch ppc64",
			}
		configuration { "x32" }
			buildoptions {
				"-arch ppc",
			}
			linkoptions {
				"-arch ppc",
			}
		configuration { }
	end
else
	defines {
		"LSB_FIRST",
	}
	if _OPTIONS["targetos"]=="macosx" then
		configuration { "x64" }
			buildoptions {
				"-arch x86_64",
			}
			linkoptions {
				"-arch x86_64",
			}
		configuration { "x32" }
			buildoptions {
				"-arch i386",
			}
			linkoptions {
				"-arch i386",
			}
		configuration { }
	end
end

<<<<<<< HEAD
-- need to ensure FLAC functions are statically linked
if _OPTIONS["with-bundled-flac"] then
	defines {
		"FLAC__NO_DLL",
	}
	end

if not _OPTIONS["with-bundled-jpeg"] then
	defines {
		"USE_SYSTEM_JPEGLIB",
	}
	end

if not _OPTIONS["with-bundled-portmidi"] then
	defines {
		"USE_SYSTEM_PORTMIDI",
	}
	end

if not _OPTIONS["with-bundled-sqlite3"] then
	defines {
		"USE_SYSTEM_SQLITE",
	}
	end
=======
if _OPTIONS["with-system-jpeg"]~=nil then
	defines {
		"XMD_H",
	}
end

if not _OPTIONS["with-system-flac"]~=nil then
	defines {
		"FLAC__NO_DLL",
	}
end
>>>>>>> upstream/master

if _OPTIONS["NOASM"]=="1" then
	defines {
		"MAME_NOASM"
	}
end

if not _OPTIONS["FORCE_DRC_C_BACKEND"] then
	if _OPTIONS["BIGENDIAN"]~="1" then
		configuration { "x64" }
			defines {
				"NATIVE_DRC=drcbe_x64",
			}
		configuration { "x32" }
			defines {
				"NATIVE_DRC=drcbe_x86",
			}
		configuration {  }
	end
end

<<<<<<< HEAD
-- define USE_SYSTEM_JPEGLIB if library shipped with MAME is not used
--ifneq ($(BUILD_JPEGLIB),1)
--DEFS += -DUSE_SYSTEM_JPEGLIB
--endif

	--To support casting in Lua 5.3
	defines {
		"LUA_COMPAT_APIINTCASTS",
	}

	if _ACTION == "gmake" then

	--we compile C-only to C89 standard with GNU extensions
if (_OPTIONS["targetos"]=="solaris") then
	buildoptions_c {
		"-std=gnu99",
	}
else
	buildoptions_c {
--		"-std=gnu99",
		"-std=gnu89",
--		"-Wpedantic",
--		"-pedantic",
--		"-Wno-variadic-macros",
--		"-Wno-long-long",
	}
end


if _OPTIONS["CPP11"]=="1" then
	buildoptions_cpp {
		"-x c++",
		"-std=gnu++11",
--		"-std=c++11",
--		"-Wpedantic",
--		"-pedantic",
--		"-Wno-variadic-macros",
--		"-Wno-long-long",

	}
else
	--we compile C++ code to C++98 standard with GNU extensions
	buildoptions_cpp {
		"-x c++",
--		"-Wpedantic",
--		"-pedantic",
		"-std=gnu++98",
		"-Wno-variadic-macros",
		"-Wno-long-long",
		"-Wno-variadic-macros",
--		"-std=c++98",
	}
end

	buildoptions_objc {
		"-x objective-c++",
	}


-- this speeds it up a bit by piping between the preprocessor/compiler/assembler
	if not ("pnacl" == _OPTIONS["gcc"]) then
		buildoptions {
			"--pipe",
=======
	defines {
		"LUA_COMPAT_ALL",
		"LUA_COMPAT_5_1",
		"LUA_COMPAT_5_2",
	}

	if _ACTION == "gmake" or _ACTION == "ninja" then

	--we compile C-only to C99 standard with GNU extensions

	buildoptions_c {
		"-std=gnu99",
	}

local version = str_to_version(_OPTIONS["gcc_version"])
if string.find(_OPTIONS["gcc"], "clang") and ((version < 30500) or (_OPTIONS["targetos"]=="macosx" and (version <= 60000))) then
	buildoptions_cpp {
		"-x c++",
		"-std=c++1y",
	}

	buildoptions_objcpp {
		"-x objective-c++",
		"-std=c++1y",
	}
else
	buildoptions_cpp {
		"-x c++",
		"-std=c++14",
	}

	buildoptions_objcpp {
		"-x objective-c++",
		"-std=c++14",
	}
end
-- this speeds it up a bit by piping between the preprocessor/compiler/assembler
	if not ("pnacl" == _OPTIONS["gcc"]) then
		buildoptions {
			"-pipe",
>>>>>>> upstream/master
		}
	end
-- add -g if we need symbols, and ensure we have frame pointers
if _OPTIONS["SYMBOLS"]~=nil and _OPTIONS["SYMBOLS"]~="0" then
	buildoptions {
		"-g" .. _OPTIONS["SYMLEVEL"],
		"-fno-omit-frame-pointer",
		"-fno-optimize-sibling-calls",
	}
end

--# we need to disable some additional implicit optimizations for profiling
if _OPTIONS["PROFILE"] then
	buildoptions {
		"-mno-omit-leaf-frame-pointer",
	}
end
-- add -v if we need verbose build information
if _OPTIONS["VERBOSE"] then
	buildoptions {
		"-v",
	}
end

-- only show shadow warnings when enabled
if (_OPTIONS["SHADOW_CHECK"]=="1") then
	buildoptions {
		"-Wshadow"
	}
end

-- only show deprecation warnings when enabled
if _OPTIONS["DEPRECATED"]~="1" then
	buildoptions {
		"-Wno-deprecated-declarations"
	}
end

-- add profiling information for the compiler
if _OPTIONS["PROFILE"] then
	buildoptions {
		"-pg",
	}
	linkoptions {
		"-pg",
	}
end

if _OPTIONS["SYMBOLS"]~=nil and _OPTIONS["SYMBOLS"]~="0" then
	flags {
		"Symbols",
	}
end

<<<<<<< HEAD
--# add the optimization flag
	buildoptions {
		"-O".. _OPTIONS["OPTIMIZE"],
		"-fno-strict-aliasing"
	}

	-- add the error warning flag
=======
-- add the error warning flag
>>>>>>> upstream/master
if _OPTIONS["NOWERROR"]==nil then
	buildoptions {
		"-Werror",
	}
end

-- if we are optimizing, include optimization options
if _OPTIONS["OPTIMIZE"] then
	buildoptions {
<<<<<<< HEAD
		"-fno-strict-aliasing"
	}
	if _OPTIONS["ARCHOPTS"] then
		buildoptions {
			_OPTIONS["ARCHOPTS"]
		}
	end
=======
		"-O".. _OPTIONS["OPTIMIZE"],
		"-fno-strict-aliasing"
	}
>>>>>>> upstream/master
	if _OPTIONS["OPT_FLAGS"] then
		buildoptions {
			_OPTIONS["OPT_FLAGS"]
		}
	end
	if _OPTIONS["LTO"]=="1" then
		buildoptions {
<<<<<<< HEAD
-- windows native mingw GCC 5.2 fails with -flto=x with x > 1. bug unfixed as of this date
			"-flto=1",
			"-fuse-linker-plugin",
-- these next flags allow MAME to compile in GCC 5.2. odr warnings should be fixed as LTO randomly crashes otherwise
-- some GCC 4.9.x on Windows do not have -Wodr and -flto-odr-type-merging enabled. adjust accordingly...
-- -ffat-lto-objects lets you link non-lto version without rebuilding all .o/.a
			"-ffat-lto-objects",
			"-flto-odr-type-merging",
			"-Wodr",
			"-flto-compression-level=9", -- lto didn't work with anything <9  on linux with < 12G RAM
--			"-flto-report", -- if you get an error in lto after [WPA] stage, but before [LTRANS] stage, you need more memory!
--			"-fmem-report-wpa","-fmem-report","-fpre-ipa-mem-report","-fpost-ipa-mem-report","-flto-report-wpa","-fmem-report",
		}
-- same flags are needed by linker
		linkoptions {
			"-Wl,-no-keep-memory",
			"-flto=1",
			"-fuse-linker-plugin",
			"-ffat-lto-objects",
			"-flto-odr-type-merging",
			"-Wodr",
			"-flto-compression-level=9", -- lto didn't work with anything < 9 on linux with < 12G RAM
--			"-flto-report", -- if you get an error in lto after [WPA] stage, but before [LTRANS] stage, you need more memory!
--			"-fmem-report-wpa","-fmem-report","-fpre-ipa-mem-report","-fpost-ipa-mem-report","-flto-report-wpa","-fmem-report",
=======
-- windows native mingw GCC 5.2 fails with -flto=x with x > 1. bug unfixed as of this commit
			"-flto=1",
-- if ld fails, just buy more RAM or uncomment this!
--          "-Wl,-no-keep-memory",
			"-Wl,-v",
-- silence redefine warnings from discrete.c.
			"-Wl,-allow-multiple-definition",
			"-fuse-linker-plugin",
-- these next flags allow MAME to compile in GCC 5.2. odr warnings should be fixed as LTO randomly crashes otherwise
-- some GCC 4.9.x on Windows do not have -Wodr and -flto-odr-type-merging enabled. adjust accordingly...
-- no-fat-lto-objects is faster to compile and uses less memory, but you can't mix with a non-lto .o/.a without rebuilding
			"-fno-fat-lto-objects",
			"-flto-odr-type-merging",
			"-Wodr",
			"-flto-compression-level=0", -- lto doesn't work with anything <9 on linux with < 12G RAM, much slower if <> 0
--          "-flto-report", -- if you get an error in lto after [WPA] stage, but before [LTRANS] stage, you need more memory!
--          "-fmem-report-wpa","-fmem-report","-fpre-ipa-mem-report","-fpost-ipa-mem-report","-flto-report-wpa","-fmem-report",
-- this six flag combo lets MAME compile with LTO=1 on linux with no errors and ~2% speed boost, but compile time is much longer
-- if you are going to wait on lto, you might as well enable these for GCC
--          "-fdevirtualize-at-ltrans","-fgcse-sm","-fgcse-las",
--          "-fipa-pta","-fipa-icf","-fvariable-expansion-in-unroller",
		}
-- same flags are needed by linker
		linkoptions {
			"-flto=1",
--          "-Wl,-no-keep-memory",
			"-Wl,-v",
			"-Wl,-allow-multiple-definition",
			"-fuse-linker-plugin",
			"-fno-fat-lto-objects",
			"-flto-odr-type-merging",
			"-Wodr",
			"-flto-compression-level=0", -- lto doesn't work with anything <9 on linux with < 12G RAM, much slower if <> 0
--          "-flto-report", -- if you get an error in lto after [WPA] stage, but before [LTRANS] stage, you need more memory!
--          "-fmem-report-wpa","-fmem-report","-fpre-ipa-mem-report","-fpost-ipa-mem-report","-flto-report-wpa","-fmem-report",
-- this six flag combo lets MAME compile with LTO=1 on linux with no errors and ~2% speed boost, but compile time is much longer
-- if you are going to wait on lto, you might as well enable these for GCC
--          "-fdevirtualize-at-ltrans","-fgcse-sm","-fgcse-las",
--          "-fipa-pta","-fipa-icf","-fvariable-expansion-in-unroller",

>>>>>>> upstream/master
		}

	end
end

<<<<<<< HEAD
=======
configuration { "mingw-clang" }
	buildoptions {
		"-O1", -- without this executable crash often
	}
configuration {  }

if _OPTIONS["ARCHOPTS"] then
	buildoptions {
		_OPTIONS["ARCHOPTS"]
	}
	linkoptions {
		_OPTIONS["ARCHOPTS"]
	}
end

>>>>>>> upstream/master
if _OPTIONS["SHLIB"] then
	buildoptions {
		"-fPIC"
	}
end

if _OPTIONS["SSE2"]=="1" then
	buildoptions {
		"-msse",
		"-msse2"
	}
end

if _OPTIONS["SSE3"]=="1" then
	buildoptions {
		"-msse",
		"-msse2",
		"-msse3"
	}
end


if _OPTIONS["OPENMP"]=="1" then
	buildoptions {
		"-fopenmp",
	}
	linkoptions {
		"-fopenmp"
	}
	defines {
		"USE_OPENMP=1",
	}

else
	buildoptions {
		"-Wno-unknown-pragmas",
	}
end

if _OPTIONS["LDOPTS"] then
	linkoptions {
		_OPTIONS["LDOPTS"]
	}
end

if _OPTIONS["MAP"] then
	if (_OPTIONS["target"] == _OPTIONS["subtarget"]) then
		linkoptions {
			"-Wl,-Map," .. "../../../../" .. _OPTIONS["target"] .. ".map"
		}
	else
		linkoptions {
			"-Wl,-Map," .. "../../../../"  .. _OPTIONS["target"] .. _OPTIONS["subtarget"] .. ".map"
		}

	end
end

<<<<<<< HEAD
-- mamep additional defines
if _OPTIONS["USE_SCALE_EFFECTS"]=="1" then
	defines {
		"USE_SCALE_EFFECTS",
	}
end
if _OPTIONS["USE_UI_COLOR_DISPLAY"]=="1" then
	defines {
		"UI_COLOR_DISPLAY",
	}
end
if _OPTIONS["USE_TRANS_UI"]=="1" then
	defines {
		"TRANS_UI",
	}
end
if _OPTIONS["USE_JOYSTICK_ID"]=="1" then
	defines {
		"JOYSTICK_ID",
	}
end
if _OPTIONS["USE_AUTOFIRE"]=="1" then
	defines {
		"USE_AUTOFIRE",
	}
end
if _OPTIONS["USE_CUSTOM_BUTTON"]=="1" then
	defines {
		"USE_CUSTOM_BUTTON",
	}
end
if _OPTIONS["USE_INP_CAPTION"]=="1" then
	defines {
		"DINP_CAPTION",
	}
end
if _OPTIONS["USE_SHOW_TIME"]=="1" then
	defines {
		"USE_SHOW_TIME",
	}
end
if _OPTIONS["USE_SHOW_INPUT_LOG"]=="1" then
	defines {
		"USE_SHOW_INPUT_LOG",
	}
end
if _OPTIONS["USE_PLAYBACK_END_PAUSE"]=="1" then
	defines {
		"USE_PLAYBACK_END_PAUSE",
	}
end
if _OPTIONS["USE_AUDIO_SYNC"]=="1" then
	defines {
		"USE_AUDIO_SYNC",
	}
end
if _OPTIONS["USE_IPS"]=="1" then
	defines {
		"USE_IPS",
	}
end
if _OPTIONS["USE_DRIVER_SWITCH"]=="1" then
	defines {
		"DRIVER_SWITCH",
	}
end
if _OPTIONS["USE_CMD_LIST"]=="1" then
	defines {
		"CMD_LIST",
	}
end
if _OPTIONS["USE_HISCORE"]=="1" then
	defines {
		"USE_HISCORE",
	}
end
if _OPTIONS["WINUI"]=="1" then
	defines {
		"WINUI",
	}
end
if _OPTIONS["USE_MORE_FOLDER_INFO"]=="1" then
	defines {
		"USE_MORE_FOLDER_INFO",
	}
end
if _OPTIONS["USE_STORY_DATAFILE"]=="1" then
	defines {
		"USE_STORY_DATAFILE",
	}
end
if _OPTIONS["USE_SHOW_SPLASH_SCREEN"]=="1" then
	defines {
		"USE_SHOW_SPLASH_SCREEN",
	}
end
if _OPTIONS["USE_VIEW_PCBINFO"]=="1" then
	defines {
		"USE_VIEW_PCBINFO",
	}
end
if _OPTIONS["USE_TREE_SHEET"]=="1" then
	defines {
		"USE_TREE_SHEET",
	}
end
if _OPTIONS["USE_EXPORT_GAMELIST"]=="1" then
	defines {
		"USE_EXPORT_GAMELIST",
	}
end
if _OPTIONS["USE_SHOW_UNAVAILABLE_FOLDER"]=="1" then
	defines {
		"USE_SHOW_UNAVAILABLE_FOLDER",
	}
end
if _OPTIONS["subtarget"]=="tiny" then
	defines {
		"TINY_BUILD",
	}
end
if _OPTIONS["subtarget"]=="ncp" then
	defines {
		"NCP",
	}
end

=======
>>>>>>> upstream/master

-- add a basic set of warnings
	buildoptions {
		"-Wall",
		"-Wcast-align",
		"-Wundef",
		"-Wformat-security",
		"-Wwrite-strings",
		"-Wno-sign-compare",
		"-Wno-conversion",
	}
-- warnings only applicable to C compiles
	buildoptions_c {
		"-Wpointer-arith",
		"-Wstrict-prototypes",
	}

if _OPTIONS["targetos"]~="freebsd" then
	buildoptions_c {
		"-Wbad-function-cast",
	}
end

-- warnings only applicable to OBJ-C compiles
<<<<<<< HEAD
	buildoptions_objc {
=======
	buildoptions_objcpp {
>>>>>>> upstream/master
		"-Wpointer-arith",
	}

-- warnings only applicable to C++ compiles
	buildoptions_cpp {
		"-Woverloaded-virtual",
	}

--ifdef SANITIZE
--CCOMFLAGS += -fsanitize=$(SANITIZE)

--ifneq (,$(findstring thread,$(SANITIZE)))
--CCOMFLAGS += -fPIE
--endif
--endif



		local version = str_to_version(_OPTIONS["gcc_version"])
<<<<<<< HEAD
		if string.find(_OPTIONS["gcc"], "clang") then
			buildoptions {
				"-Wno-cast-align",
				"-Wno-tautological-compare",
				"-Wno-dynamic-class-memaccess",
			}
			if (version >= 30200) then
				buildoptions {
					"-Wno-unused-value",
				}
			end
			if (version >= 30400) then
				buildoptions {
					"-Wno-inline-new-delete",
					"-Wno-constant-logical-operand",
				}
			end
			if (version >= 30500) then
				buildoptions {
					"-Wno-absolute-value",
					"-Wno-unknown-warning-option",
					"-Wno-extern-c-compat",
				}
			end
			if (version >= 70000) then
				buildoptions {
					"-Wno-tautological-undefined-compare",
				}
			end
		else
			if (version == 40201) then
				buildoptions {
					"-Wno-cast-align"
				}
			end
			if (version >= 40400) then
				buildoptions {
					"-Wno-unused-result",
				}
			end

			if (version >= 40700) then
				buildoptions {
					"-Wno-narrowing",
					"-Wno-attributes"
				}
			end
			if (version >= 40800) then
-- grr.. array-bounds works on GCC5.2 linux, but fails in sqllite3.c on MingW GCC 5.1.1 for now
--				if (version < 50000) then
--					-- array bounds checking seems to be buggy in 4.8.1 (try it on video/stvvdp1.c and video/model1.c without -Wno-array-bounds)
					buildoptions {
						"-Wno-array-bounds"
					}
--				end
			end
			if (version >= 50000) then
				buildoptions {
--					"-D__USE_MINGW_ANSI_STDIO=1", -- required or lua won't compile linux ignores this but Windows needs it
					"-freport-bug",
					"-D_GLIBCXX_USE_CXX11_ABI=0", -- does not seem to matter in linux, mingw needs to link printf,etc
--					"-DNO_MEM_TRACKING",          -- must comment out for mingw GCC 5.2 pedantic or get new/delete redef error
-- next two should work, but compiler complains about end conditions that are int when loop variable is unsigned. maybe these can be fixed
--					"-funsafe-loop-optimizations",
--					"-Wunsafe-loop-optimizations",
-- this six flag combo lets MAME compile with LTO=1 on linux with no errors and ~2% speed boost, but compile time is much longer
--					"-fdevirtualize-at-ltrans","-fgcse-sm","-fgcse-las",
--					"-fipa-pta","-fipa-icf","-fvariable-expansion-in-unroller",

				}
			end
		end
	end
--ifeq ($(findstring arm,$(UNAME)),arm)
--	CCOMFLAGS += -Wno-cast-align
--endif
=======
		if string.find(_OPTIONS["gcc"], "clang") or string.find(_OPTIONS["gcc"], "pnacl") or string.find(_OPTIONS["gcc"], "asmjs") or string.find(_OPTIONS["gcc"], "android") then
			if (version < 30400) then
				print("Clang version 3.4 or later needed")
				os.exit(-1)
			end
			buildoptions {
				"-Wno-cast-align",
				"-Wno-tautological-compare",
				"-Wno-unused-value",
				"-Wno-constant-logical-operand",
				"-Wno-missing-braces", -- clang is not as permissive as GCC about std::array initialization
				"-fdiagnostics-show-note-include-stack",
			}
			if (version >= 30500) then
				buildoptions {
					"-Wno-unknown-warning-option",
					"-Wno-extern-c-compat",
					"-Wno-unknown-attributes",
					"-Wno-ignored-qualifiers"
				}
			end
		else
			if (version < 50000) then
				print("GCC version 5.0 or later needed")
				os.exit(-1)
			end
				buildoptions {
					"-Wno-unused-result", -- needed for fgets,fread on linux
					-- array bounds checking seems to be buggy in 4.8.1 (try it on video/stvvdp1.c and video/model1.c without -Wno-array-bounds)
					"-Wno-array-bounds",
				}
		end
	end

if (_OPTIONS["PLATFORM"]=="alpha") then
	defines {
		"PTR64=1",
	}
end

if (_OPTIONS["PLATFORM"]=="arm") then
	buildoptions {
		"-Wno-cast-align",
	}
end

if (_OPTIONS["PLATFORM"]=="arm64") then
	buildoptions {
		"-Wno-cast-align",
	}
	defines {
		"PTR64=1",
	}
end

if (_OPTIONS["PLATFORM"]=="mips64") then
	defines {
		"PTR64=1",
	}
end
>>>>>>> upstream/master

local subdir
if (_OPTIONS["target"] == _OPTIONS["subtarget"]) then
	subdir = _OPTIONS["osd"] .. "/" .. _OPTIONS["target"]
else
	subdir = _OPTIONS["osd"] .. "/" .. _OPTIONS["target"] .. _OPTIONS["subtarget"]
end

if not toolchain(MAME_BUILD_DIR, subdir) then
	return -- no action specified
end

configuration { "asmjs" }
	buildoptions {
		"-std=gnu89",
		"-Wno-implicit-function-declaration",
<<<<<<< HEAD
	}
	buildoptions_cpp {
		"-x c++",
		"-std=gnu++98",
=======
		"-s USE_SDL_TTF=2",
	}
	buildoptions_cpp {
		"-x c++",
		"-std=c++14",
>>>>>>> upstream/master
	}
	archivesplit_size "20"

configuration { "android*" }
	buildoptions {
		"-Wno-undef",
<<<<<<< HEAD
	}
	buildoptions_cpp {
		"-x c++",
		"-std=gnu++98",
	}
	archivesplit_size "20"

=======
		"-Wno-typedef-redefinition",
		"-Wno-unknown-warning-option",
		"-Wno-incompatible-ms-struct",
	}
	buildoptions_cpp {
		"-x c++",
		"-std=c++14",
		"-Wno-extern-c-compat",
		"-Wno-tautological-constant-out-of-range-compare",
		"-Wno-tautological-pointer-compare",
	}
	archivesplit_size "20"

configuration { "android-arm64" }
	buildoptions {
		"-Wno-asm-operand-widths",
	}

>>>>>>> upstream/master
configuration { "pnacl" }
	buildoptions {
		"-std=gnu89",
		"-Wno-inline-new-delete",
	}
	buildoptions_cpp {
		"-x c++",
<<<<<<< HEAD
		"-std=gnu++98",
	}
	archivesplit_size "20"

configuration { "nacl*" }
	buildoptions_cpp {
		"-x c++",
		"-std=gnu++98",
	}
	archivesplit_size "20"

configuration { "linux-*" }
		links {
			"dl",
=======
		"-std=c++14",
	}
	archivesplit_size "20"

configuration { "linux-* or rpi or ci20"}
		links {
			"dl",
			"rt",
>>>>>>> upstream/master
		}
		if _OPTIONS["distro"]=="debian-stable" then
			defines
			{
				"NO_AFFINITY_NP",
			}
		end


<<<<<<< HEAD
configuration { "osx*" }
=======

configuration { "steamlink" }
	links {
		"dl",
		"EGL",
		"GLESv2",
		"SDL2",
	}
	defines {
		"EGL_API_FB",
	}

configuration { "rpi" }
	links {
		"SDL2",
		"fontconfig",
		"X11",
		"GLESv2",
		"EGL",
		"bcm_host",
		"vcos",
		"vchiq_arm",
		"pthread",
	}


configuration { "ci20" }
	links {
		"SDL2",
		"asound",
		"fontconfig",
		"freetype",
		"pthread",
	}


configuration { "osx* or xcode4" }
>>>>>>> upstream/master
		links {
			"pthread",
		}

configuration { "mingw*" }
<<<<<<< HEAD
		buildoptions {
			"-Wno-format-security",
			"-Wno-unused-but-set-variable",
			"-Wno-int-to-pointer-cast",
			"-Wno-unused-variable",
		}
		linkoptions {
			"-static-libgcc",
			"-static-libstdc++",
=======
		local version = str_to_version(_OPTIONS["gcc_version"])
		if not (_OPTIONS["gcc"]~=nil and string.find(_OPTIONS["gcc"], "clang")) or version < 40000
		then
			linkoptions {
				"-static",
			}
		end
		linkoptions {
			"-Wl,--start-group",
>>>>>>> upstream/master
		}
		links {
			"user32",
			"winmm",
			"advapi32",
			"shlwapi",
			"wsock32",
<<<<<<< HEAD
		}

=======
			"ws2_32",
			"psapi",
			"iphlpapi",
			"shell32",
			"userenv",
		}

configuration { "mingw-clang" }
	local version = str_to_version(_OPTIONS["gcc_version"])
	if _OPTIONS["gcc"]~=nil and string.find(_OPTIONS["gcc"], "clang") and ((version < 30900)) then
		linkoptions {
			"-pthread",
		}
	end


>>>>>>> upstream/master
configuration { "vs*" }
		defines {
			"XML_STATIC",
			"WIN32",
			"_WIN32",
			"_CRT_NONSTDC_NO_DEPRECATE",
			"_CRT_SECURE_NO_DEPRECATE",
<<<<<<< HEAD
		}
=======
			"_CRT_STDIO_LEGACY_WIDE_SPECIFIERS",
		}
-- Windows Store/Phone projects already link against the available libraries.
if _OPTIONS["vs"]==nil or not (string.startswith(_OPTIONS["vs"], "winstore8") or string.startswith(_OPTIONS["vs"], "winphone8")) then
>>>>>>> upstream/master
		links {
			"user32",
			"winmm",
			"advapi32",
			"shlwapi",
			"wsock32",
<<<<<<< HEAD
		}

		buildoptions {
=======
			"ws2_32",
			"psapi",
			"iphlpapi",
			"shell32",
			"userenv",
		}
end

		buildoptions {
			"/WX",     -- Treats all compiler warnings as errors.
>>>>>>> upstream/master
			"/wd4025", -- warning C4025: 'number' : based pointer passed to function with variable arguments: parameter number
			"/wd4003", -- warning C4003: not enough actual parameters for macro 'xxx'
			"/wd4018", -- warning C4018: 'x' : signed/unsigned mismatch
			"/wd4061", -- warning C4061: enumerator 'xxx' in switch of enum 'xxx' is not explicitly handled by a case label
			"/wd4100", -- warning C4100: 'xxx' : unreferenced formal parameter
			"/wd4127", -- warning C4127: conditional expression is constant
			"/wd4131", -- warning C4131: 'xxx' : uses old-style declarator
			"/wd4141", -- warning C4141: 'xxx' : used more than once
			"/wd4146", -- warning C4146: unary minus operator applied to unsigned type, result still unsigned
			"/wd4150", -- warning C4150: deletion of pointer to incomplete type 'xxx'; no destructor called
			"/wd4189", -- warning C4189: 'xxx' : local variable is initialized but not referenced
			"/wd4191", -- warning C4191: 'type cast' : unsafe conversion from 'xxx' to 'xxx' // 64-bit only
			"/wd4201", -- warning C4201: nonstandard extension used : nameless struct/union
			"/wd4232", -- warning C4232: nonstandard extension used : 'xxx' : address of dllimport 'xxx' is not static, identity not guaranteed
			"/wd4242", -- warning C4242: 'x' : conversion from 'xxx' to 'xxx', possible loss of data
			"/wd4244", -- warning C4244: 'argument' : conversion from 'xxx' to 'xxx', possible loss of data
			"/wd4250", -- warning C4250: 'xxx' : inherits 'xxx' via dominance
			"/wd4255", -- warning C4255: 'xxx' : no function prototype given: converting '()' to '(void)'
			"/wd4296", -- warning C4296: 'x' : expression is always false
			"/wd4306", -- warning C4306: 'xxx': conversion from 'type1' to 'type2' of greater size // 64-bit only
			"/wd4310", -- warning C4310: cast truncates constant value
			"/wd4312", -- warning C4312: 'type cast' : conversion from 'xxx' to 'xxx' of greater size
			"/wd4324", -- warning C4324: 'xxx' : structure was padded due to __declspec(align())
			"/wd4347", -- warning C4347: behavior change: 'xxx' is called instead of 'xxx' // obsolete VS2005 - VS2010 only
			"/wd4435", -- warning C4435: 'xxx' : Object layout under /vd2 will change due to virtual base 'xxx'
			"/wd4510", -- warning C4510: 'xxx' : default constructor could not be generated
			"/wd4512", -- warning C4512: 'xxx' : assignment operator could not be generated
			"/wd4514", -- warning C4514: 'xxx' : unreferenced inline function has been removed
			"/wd4571", -- warning C4611: interaction between '_setjmp' and C++ object destruction is non-portable
			"/wd4610", -- warning C4619: #pragma warning : there is no warning number 'xxx'
			"/wd4611", -- warning C4571: Informational: catch(...) semantics changed since Visual C++ 7.1; structured exceptions (SEH) are no longer caught
			"/wd4619", -- warning C4610: struct 'xxx' can never be instantiated - user defined constructor required
			"/wd4625", -- warning C4625: 'xxx' : copy constructor could not be generated because a base class copy constructor is inaccessible or deleted
			"/wd4626", -- warning C4626: 'xxx' : assignment operator could not be generated because a base class assignment operator is inaccessible or deleted
			"/wd4640", -- warning C4640: 'xxx' : construction of local static object is not thread-safe
			"/wd4668", -- warning C4668: 'xxx' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
			"/wd4702", -- warning C4702: unreachable code
			"/wd4706", -- warning C4706: assignment within conditional expression
			"/wd4710", -- warning C4710: 'xxx' : function not inlined
			"/wd4711", -- warning C4711: function 'xxx' selected for automatic inline expansion // optimized only
			"/wd4805", -- warning C4805: 'x' : unsafe mix of type 'xxx' and type 'xxx' in operation
			"/wd4820", -- warning C4820: 'xxx' : 'x' bytes padding added after data member 'xxx'
			"/wd4826", -- warning C4826: Conversion from 'type1 ' to 'type_2' is sign-extended. This may cause unexpected runtime behavior. // 32-bit only
			"/wd4365", -- warning C4365: 'action' : conversion from 'type_1' to 'type_2', signed/unsigned mismatch
			"/wd4389", -- warning C4389: 'operator' : signed/unsigned mismatch
			"/wd4245", -- warning C4245: 'conversion' : conversion from 'type1' to 'type2', signed/unsigned mismatch
<<<<<<< HEAD
			"/wd4388", -- warning C4388:
=======
			"/wd4388", -- warning C4388: signed/unsigned mismatch
>>>>>>> upstream/master
			"/wd4267", -- warning C4267: 'var' : conversion from 'size_t' to 'type', possible loss of data
			"/wd4005", -- warning C4005: The macro identifier is defined twice. The compiler uses the second macro definition
			"/wd4350", -- warning C4350: behavior change: 'member1' called instead of 'member2'
			"/wd4996", -- warning C4996: 'function': was declared deprecated
			"/wd4191", -- warning C4191: 'operator/operation' : unsafe conversion from 'type of expression' to 'type required'
			"/wd4060", -- warning C4060: switch statement contains no 'case' or 'default' labels
			"/wd4065", -- warning C4065: switch statement contains 'default' but no 'case' labels
			"/wd4640", -- warning C4640: 'instance' : construction of local static object is not thread-safe
<<<<<<< HEAD
			"/wd4290", -- warning C4290:
			"/wd4355", -- warning C4355: 'this' : used in base member initializer list
			"/wd4800", -- warning C4800: 'type' : forcing value to bool 'true' or 'false' (performance warning)
			"/wd4371", -- warning C4371:
=======
			"/wd4290", -- warning C4290: C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
			"/wd4355", -- warning C4355: 'this' : used in base member initializer list
			"/wd4800", -- warning C4800: 'type' : forcing value to bool 'true' or 'false' (performance warning)
			"/wd4371", -- warning C4371: layout of class may have changed from a previous version of the compiler due to better packing of member 'member'
>>>>>>> upstream/master
			"/wd4548", -- warning C4548: expression before comma has no effect; expected expression with side-effect
		}
if _OPTIONS["vs"]=="intel-15" then
		buildoptions {
<<<<<<< HEAD
			"/Qwd9",    			-- remark #9: nested comment is not allowed
			"/Qwd82",   			-- remark #82: storage class is not first
			"/Qwd111",  			-- remark #111: statement is unreachable
			"/Qwd128",  			-- remark #128: loop is not reachable
			"/Qwd177",  			-- remark #177: function "xxx" was declared but never referenced
			"/Qwd181",  			-- remark #181: argument of type "UINT32={unsigned int}" is incompatible with format "%d", expecting argument of type "int"
			"/Qwd185",  			-- remark #185: dynamic initialization in unreachable code
			"/Qwd280",  			-- remark #280: selector expression is constant
			"/Qwd344",  			-- remark #344: typedef name has already been declared (with same type)
			"/Qwd411",  			-- remark #411: class "xxx" defines no constructor to initialize the following
			"/Qwd869",  			-- remark #869: parameter "xxx" was never referenced
			"/Qwd2545", 			-- remark #2545: empty dependent statement in "else" clause of if - statement
			"/Qwd2553", 			-- remark #2553: nonstandard second parameter "TCHAR={WCHAR = { __wchar_t } } **" of "main", expected "char *[]" or "char **" extern "C" int _tmain(int argc, TCHAR **argv)
			"/Qwd2557", 			-- remark #2557: comparison between signed and unsigned operands
			"/Qwd3280", 			-- remark #3280: declaration hides member "attotime::seconds" (declared at line 126) static attotime from_seconds(INT32 seconds) { return attotime(seconds, 0); }

			"/Qwd170",  			-- error #170: pointer points outside of underlying object
			"/Qwd188",  			-- error #188: enumerated type mixed with another type

			"/Qwd63",   			-- warning #63: shift count is too large
			"/Qwd177",  			-- warning #177: label "xxx" was declared but never referenced
			"/Qwd186",  			-- warning #186: pointless comparison of unsigned integer with zero
			"/Qwd488",  			-- warning #488: template parameter "_FunctionClass" is not used in declaring the parameter types of function template "device_delegate<_Signature>::device_delegate<_FunctionClass>(delegate<_Signature>:
			"/Qwd1478", 			-- warning #1478: function "xxx" (declared at line yyy of "zzz") was declared deprecated
			"/Qwd1879", 			-- warning #1879: unimplemented pragma ignored
			"/Qwd3291", 			-- warning #3291: invalid narrowing conversion from "double" to "int"
			"/Qwd1195", 			-- error #1195: conversion from integer to smaller pointer
			"/Qwd47",			-- error #47: incompatible redefinition of macro "xxx"
			"/Qwd265",			-- error #265: floating-point operation result is out of range
			-- these occur on a release build, while we can increase the size limits instead some of the files do require extreme amounts
			"/Qwd11074",			-- remark #11074: Inlining inhibited by limit max-size  / remark #11074: Inlining inhibited by limit max-total-size
			"/Qwd11075",			-- remark #11075: To get full report use -Qopt-report:4 -Qopt-report-phase ipo
=======
			"/Qwd9",                -- remark #9: nested comment is not allowed
			"/Qwd82",               -- remark #82: storage class is not first
			"/Qwd111",              -- remark #111: statement is unreachable
			"/Qwd128",              -- remark #128: loop is not reachable
			"/Qwd177",              -- remark #177: function "xxx" was declared but never referenced
			"/Qwd181",              -- remark #181: argument of type "UINT32={unsigned int}" is incompatible with format "%d", expecting argument of type "int"
			"/Qwd185",              -- remark #185: dynamic initialization in unreachable code
			"/Qwd280",              -- remark #280: selector expression is constant
			"/Qwd344",              -- remark #344: typedef name has already been declared (with same type)
			"/Qwd411",              -- remark #411: class "xxx" defines no constructor to initialize the following
			"/Qwd869",              -- remark #869: parameter "xxx" was never referenced
			"/Qwd2545",             -- remark #2545: empty dependent statement in "else" clause of if - statement
			"/Qwd2553",             -- remark #2553: nonstandard second parameter "TCHAR={WCHAR = { __wchar_t } } **" of "main", expected "char *[]" or "char **" extern "C" int _tmain(int argc, TCHAR **argv)
			"/Qwd2557",             -- remark #2557: comparison between signed and unsigned operands
			"/Qwd3280",             -- remark #3280: declaration hides member "attotime::seconds" (declared at line 126) static attotime from_seconds(INT32 seconds) { return attotime(seconds, 0); }

			"/Qwd170",              -- error #170: pointer points outside of underlying object
			"/Qwd188",              -- error #188: enumerated type mixed with another type

			"/Qwd63",               -- warning #63: shift count is too large
			"/Qwd177",              -- warning #177: label "xxx" was declared but never referenced
			"/Qwd186",              -- warning #186: pointless comparison of unsigned integer with zero
			"/Qwd488",              -- warning #488: template parameter "_FunctionClass" is not used in declaring the parameter types of function template "device_delegate<_Signature>::device_delegate<_FunctionClass>(delegate<_Signature>:
			"/Qwd1478",             -- warning #1478: function "xxx" (declared at line yyy of "zzz") was declared deprecated
			"/Qwd1879",             -- warning #1879: unimplemented pragma ignored
			"/Qwd3291",             -- warning #3291: invalid narrowing conversion from "double" to "int"
			"/Qwd1195",             -- error #1195: conversion from integer to smaller pointer
			"/Qwd47",               -- error #47: incompatible redefinition of macro "xxx"
			"/Qwd265",              -- error #265: floating-point operation result is out of range
			-- these occur on a release build, while we can increase the size limits instead some of the files do require extreme amounts
			"/Qwd11074",            -- remark #11074: Inlining inhibited by limit max-size  / remark #11074: Inlining inhibited by limit max-total-size
			"/Qwd11075",            -- remark #11075: To get full report use -Qopt-report:4 -Qopt-report-phase ipo
>>>>>>> upstream/master
		}
end

		linkoptions {
			"/ignore:4221", -- LNK4221: This object file does not define any previously undefined public symbols, so it will not be used by any link operation that consumes this library
		}
		includedirs {
			MAME_DIR .. "3rdparty/dxsdk/Include"
		}
<<<<<<< HEAD
configuration { "vs2015" }
		buildoptions {
=======
configuration { "vs201*" }
		buildoptions {
			"/wd4334", -- warning C4334: '<<': result of 32-bit shift implicitly converted to 64 bits (was 64-bit shift intended?)
>>>>>>> upstream/master
			"/wd4456", -- warning C4456: declaration of 'xxx' hides previous local declaration
			"/wd4457", -- warning C4457: declaration of 'xxx' hides function parameter
			"/wd4458", -- warning C4458: declaration of 'xxx' hides class member
			"/wd4459", -- warning C4459: declaration of 'xxx' hides global declaration
			"/wd4838", -- warning C4838: conversion from 'xxx' to 'yyy' requires a narrowing conversion
			"/wd4091", -- warning C4091: 'typedef ': ignored on left of '' when no variable is declared
			"/wd4463", -- warning C4463: overflow; assigning 1 to bit-field that can only hold values from -1 to 0
			"/wd4297", -- warning C4297: 'xxx::~xxx': function assumed not to throw an exception but does
			"/wd4319", -- warning C4319: 'operator' : zero extending 'type' to 'type' of greater size
<<<<<<< HEAD
		}
configuration { "vs2010" }
		buildoptions {
			"/wd4481", -- warning C4481: nonstandard extension used: override specifier 'override'
		}

configuration { "winphone8* or winstore8*" }
	removelinks {
		"DelayImp",
		"gdi32",
		"psapi"
	}
	links {
		"d3d11",
		"dxgi"
	}
=======
			"/wd4592", -- warning C4592: symbol will be dynamically initialized (implementation limitation)
		}
configuration { "winphone8* or winstore8*" }
>>>>>>> upstream/master
	linkoptions {
		"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
	}


<<<<<<< HEAD
configuration { }

=======
-- adding this till we sort out asserts in debug mode
configuration { "Debug", "gmake" }
	buildoptions_cpp {
		"-Wno-terminate",
	}

configuration { }

if (_OPTIONS["SOURCES"] ~= nil) then
	local str = _OPTIONS["SOURCES"]
	for word in string.gmatch(str, '([^,]+)') do
		if (not os.isfile(path.join(MAME_DIR ,word))) then
			print("File " .. word.. " does not exist")
			os.exit()
		end
	end
	OUT_STR = os.outputof( PYTHON .. " " .. MAME_DIR .. "scripts/build/makedep.py " .. MAME_DIR .. " " .. _OPTIONS["SOURCES"] .. " target " .. _OPTIONS["subtarget"])
	load(OUT_STR)()
	os.outputof( PYTHON .. " " .. MAME_DIR .. "scripts/build/makedep.py " .. MAME_DIR .. " " .. _OPTIONS["SOURCES"] .. " drivers " .. _OPTIONS["subtarget"] .. " > ".. GEN_DIR  .. _OPTIONS["target"] .. "/" .. _OPTIONS["subtarget"]..".flt")
end
>>>>>>> upstream/master

group "libs"

if (not os.isfile(path.join("src", "osd",  _OPTIONS["osd"] .. ".lua"))) then
	error("Unsupported value '" .. _OPTIONS["osd"] .. "' for OSD")
end
dofile(path.join("src", "osd", _OPTIONS["osd"] .. ".lua"))
<<<<<<< HEAD
if _OPTIONS["osd"] == "windows" and _OPTIONS["WINUI"] == "1" then
	dofile(path.join("src", "osd", "winui.lua"))
end
dofile(path.join("src", "lib.lua"))
=======
dofile(path.join("src", "lib.lua"))
if (MACHINES["NETLIST"]~=null or _OPTIONS["with-tools"]) then
dofile(path.join("src", "netlist.lua"))
end
--if (STANDALONE~=true) then
dofile(path.join("src", "formats.lua"))
formatsProject(_OPTIONS["target"],_OPTIONS["subtarget"])
--end
>>>>>>> upstream/master

group "3rdparty"
dofile(path.join("src", "3rdparty.lua"))


group "core"

dofile(path.join("src", "emu.lua"))

<<<<<<< HEAD
=======
if (STANDALONE~=true) then
	dofile(path.join("src", "mame", "frontend.lua"))
end

>>>>>>> upstream/master
group "devices"
dofile(path.join("src", "devices.lua"))
devicesProject(_OPTIONS["target"],_OPTIONS["subtarget"])

<<<<<<< HEAD
group "drivers"
findfunction("createProjects_" .. _OPTIONS["target"] .. "_" .. _OPTIONS["subtarget"])(_OPTIONS["target"], _OPTIONS["subtarget"])

group "emulator"
dofile(path.join("src", "main.lua"))
if (_OPTIONS["target"] == _OPTIONS["subtarget"]) then
	startproject (_OPTIONS["target"])
else
	startproject (_OPTIONS["target"] .. _OPTIONS["subtarget"])
end
mainProject(_OPTIONS["target"],_OPTIONS["subtarget"])
if _OPTIONS["osd"] == "windows" and _OPTIONS["WINUI"] == "1" then
	mainProject_with_ui(_OPTIONS["target"],_OPTIONS["subtarget"])
end

if (_OPTIONS["STRIP_SYMBOLS"]=="1") then
	strip()
end
=======
if (STANDALONE~=true) then
	group "drivers"
	findfunction("createProjects_" .. _OPTIONS["target"] .. "_" .. _OPTIONS["subtarget"])(_OPTIONS["target"], _OPTIONS["subtarget"])
end

group "emulator"
dofile(path.join("src", "main.lua"))
if (_OPTIONS["SOURCES"] == nil) then
	if (_OPTIONS["target"] == _OPTIONS["subtarget"]) then
		startproject (_OPTIONS["target"])
	else
		if (_OPTIONS["subtarget"]=="mess") then
			startproject (_OPTIONS["subtarget"])
		else
			startproject (_OPTIONS["target"] .. _OPTIONS["subtarget"])
		end
	end
else
	startproject (_OPTIONS["subtarget"])
end
mainProject(_OPTIONS["target"],_OPTIONS["subtarget"])
strip()
>>>>>>> upstream/master

if _OPTIONS["with-tools"] then
	group "tools"
	dofile(path.join("src", "tools.lua"))
end

if _OPTIONS["with-tests"] then
	group "tests"
	dofile(path.join("src", "tests.lua"))
end
<<<<<<< HEAD
=======

if _OPTIONS["with-benchmarks"] then
	group "benchmarks"
	dofile(path.join("src", "benchmarks.lua"))
end
>>>>>>> upstream/master
