--
<<<<<<< HEAD
-- Copyright 2010-2015 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
=======
-- Copyright 2010-2017 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
>>>>>>> upstream/master
--

newoption {
	trigger = "with-amalgamated",
	description = "Enable amalgamated build.",
}

newoption {
	trigger = "with-ovr",
	description = "Enable OculusVR integration.",
}

newoption {
	trigger = "with-sdl",
	description = "Enable SDL entry.",
}

newoption {
	trigger = "with-glfw",
	description = "Enable GLFW entry.",
}

newoption {
<<<<<<< HEAD
=======
	trigger = "with-profiler",
	description = "Enable build with intrusive profiler.",
}

newoption {
>>>>>>> upstream/master
	trigger = "with-scintilla",
	description = "Enable building with Scintilla editor.",
}

newoption {
	trigger = "with-shared-lib",
	description = "Enable building shared library.",
}

newoption {
	trigger = "with-tools",
	description = "Enable building tools.",
}

<<<<<<< HEAD
=======
newoption {
	trigger = "with-examples",
	description = "Enable building examples.",
}

>>>>>>> upstream/master
solution "bgfx"
	configurations {
		"Debug",
		"Release",
	}

	if _ACTION == "xcode4" then
		platforms {
			"Universal",
		}
	else
		platforms {
			"x32",
			"x64",
--			"Xbox360",
			"Native", -- for targets where bitness is not specified
		}
	end

	language "C++"
	startproject "example-00-helloworld"

<<<<<<< HEAD
BGFX_DIR = path.getabsolute("..")
local BGFX_BUILD_DIR = path.join(BGFX_DIR, ".build")
local BGFX_THIRD_PARTY_DIR = path.join(BGFX_DIR, "3rdparty")
BX_DIR = path.getabsolute(path.join(BGFX_DIR, "../bx"))

defines {
	"BX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS=1"
}
=======
MODULE_DIR = path.getabsolute("../")
BGFX_DIR   = path.getabsolute("..")
BX_DIR     = os.getenv("BX_DIR")

local BGFX_BUILD_DIR = path.join(BGFX_DIR, ".build")
local BGFX_THIRD_PARTY_DIR = path.join(BGFX_DIR, "3rdparty")
if not BX_DIR then
	BX_DIR = path.getabsolute(path.join(BGFX_DIR, "../bx"))
end

if not os.isdir(BX_DIR) then
	print("bx not found at " .. BX_DIR)
	print("For more info see: https://bkaradzic.github.io/bgfx/build.html")
	os.exit()
end
>>>>>>> upstream/master

dofile (path.join(BX_DIR, "scripts/toolchain.lua"))
if not toolchain(BGFX_BUILD_DIR, BGFX_THIRD_PARTY_DIR) then
	return -- no action specified
end

function copyLib()
end

if _OPTIONS["with-sdl"] then
	if os.is("windows") then
		if not os.getenv("SDL2_DIR") then
			print("Set SDL2_DIR enviroment variable.")
		end
	end
end

<<<<<<< HEAD
=======
if _OPTIONS["with-profiler"] then
	defines {
		"ENTRY_CONFIG_PROFILER=1",
		"BGFX_CONFIG_PROFILER_REMOTERY=1",
        "_WINSOCKAPI_"
	}
end

>>>>>>> upstream/master
function exampleProject(_name)

	project ("example-" .. _name)
		uuid (os.uuid("example-" .. _name))
		kind "WindowedApp"

	configuration {}

	debugdir (path.join(BGFX_DIR, "examples/runtime"))

	includedirs {
		path.join(BX_DIR,   "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BGFX_DIR, "examples/common"),
	}

	files {
		path.join(BGFX_DIR, "examples", _name, "**.c"),
		path.join(BGFX_DIR, "examples", _name, "**.cpp"),
		path.join(BGFX_DIR, "examples", _name, "**.h"),
	}

	removefiles {
		path.join(BGFX_DIR, "examples", _name, "**.bin.h"),
	}

<<<<<<< HEAD
	links {
		"bgfx",
		"example-common",
=======
	flags {
		"FatalWarnings",
	}

	links {
		"example-common",
		"bgfx",
		"bx",
>>>>>>> upstream/master
	}

	if _OPTIONS["with-sdl"] then
		defines { "ENTRY_CONFIG_USE_SDL=1" }
		links   { "SDL2" }

<<<<<<< HEAD
		configuration { "x32", "windows" }
			libdirs { "$(SDL2_DIR)/lib/x86" }

		configuration { "x64", "windows" }
			libdirs { "$(SDL2_DIR)/lib/x64" }
=======
		configuration { "osx" }
			libdirs { "$(SDL2_DIR)/lib" }
>>>>>>> upstream/master

		configuration {}
	end

	if _OPTIONS["with-glfw"] then
		defines { "ENTRY_CONFIG_USE_GLFW=1" }
<<<<<<< HEAD
		links   {
			"glfw3"
		}
=======
		links   { "glfw3" }
>>>>>>> upstream/master

		configuration { "linux or freebsd" }
			links {
				"Xrandr",
				"Xinerama",
				"Xi",
				"Xxf86vm",
				"Xcursor",
			}

		configuration { "osx" }
			linkoptions {
				"-framework CoreVideo",
				"-framework IOKit",
			}

		configuration {}
	end

	if _OPTIONS["with-ovr"] then
<<<<<<< HEAD
		links   {
			"winmm",
			"ws2_32",
		}

		-- Check for LibOVR 5.0+
		if os.isdir(path.join(os.getenv("OVR_DIR"), "LibOVR/Lib/Windows/Win32/Debug/VS2012")) then

			configuration { "x32", "Debug" }
				libdirs { path.join("$(OVR_DIR)/LibOVR/Lib/Windows/Win32/Debug", _ACTION) }

			configuration { "x32", "Release" }
				libdirs { path.join("$(OVR_DIR)/LibOVR/Lib/Windows/Win32/Release", _ACTION) }

			configuration { "x64", "Debug" }
				libdirs { path.join("$(OVR_DIR)/LibOVR/Lib/Windows/x64/Debug", _ACTION) }

			configuration { "x64", "Release" }
				libdirs { path.join("$(OVR_DIR)/LibOVR/Lib/Windows/x64/Release", _ACTION) }

			configuration { "x32 or x64" }
				links { "libovr" }
		else
			configuration { "x32" }
				libdirs { path.join("$(OVR_DIR)/LibOVR/Lib/Win32", _ACTION) }

			configuration { "x64" }
				libdirs { path.join("$(OVR_DIR)/LibOVR/Lib/x64", _ACTION) }

			configuration { "x32", "Debug" }
				links { "libovrd" }

			configuration { "x32", "Release" }
				links { "libovr" }

			configuration { "x64", "Debug" }
				links { "libovr64d" }

			configuration { "x64", "Release" }
				links { "libovr64" }
		end
=======
		configuration { "x32" }
			libdirs { path.join("$(OVR_DIR)/LibOVR/Lib/Windows/Win32/Release", _ACTION) }

		configuration { "x64" }
			libdirs { path.join("$(OVR_DIR)/LibOVR/Lib/Windows/x64/Release", _ACTION) }

		configuration { "x32 or x64" }
			links { "libovr" }
>>>>>>> upstream/master

		configuration {}
	end

<<<<<<< HEAD
	configuration { "vs*" }
=======
	configuration { "vs*", "x32 or x64" }
>>>>>>> upstream/master
		linkoptions {
			"/ignore:4199", -- LNK4199: /DELAYLOAD:*.dll ignored; no imports found from *.dll
		}
		links { -- this is needed only for testing with GLES2/3 on Windows with VS2008
			"DelayImp",
		}

<<<<<<< HEAD
	configuration { "vs201*" }
=======
	configuration { "vs201*", "x32 or x64" }
>>>>>>> upstream/master
		linkoptions { -- this is needed only for testing with GLES2/3 on Windows with VS201x
			"/DELAYLOAD:\"libEGL.dll\"",
			"/DELAYLOAD:\"libGLESv2.dll\"",
		}

	configuration { "mingw*" }
		targetextension ".exe"
<<<<<<< HEAD

	configuration { "vs20* or mingw*" }
=======
		links {
			"gdi32",
			"psapi",
		}

	configuration { "vs20*", "x32 or x64" }
>>>>>>> upstream/master
		links {
			"gdi32",
			"psapi",
		}

<<<<<<< HEAD
=======
	configuration { "durango" }
		links {
			"d3d11_x",
			"d3d12_x",
			"combase",
			"kernelx",
		}

>>>>>>> upstream/master
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
		linkoptions {
			"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
		}

	-- WinRT targets need their own output directories or build files stomp over each other
	configuration { "x32", "winphone8* or winstore8*" }
		targetdir (path.join(BGFX_BUILD_DIR, "win32_" .. _ACTION, "bin", _name))
		objdir (path.join(BGFX_BUILD_DIR, "win32_" .. _ACTION, "obj", _name))

	configuration { "x64", "winphone8* or winstore8*" }
		targetdir (path.join(BGFX_BUILD_DIR, "win64_" .. _ACTION, "bin", _name))
		objdir (path.join(BGFX_BUILD_DIR, "win64_" .. _ACTION, "obj", _name))

	configuration { "ARM", "winphone8* or winstore8*" }
		targetdir (path.join(BGFX_BUILD_DIR, "arm_" .. _ACTION, "bin", _name))
		objdir (path.join(BGFX_BUILD_DIR, "arm_" .. _ACTION, "obj", _name))

	configuration { "mingw-clang" }
		kind "ConsoleApp"

	configuration { "android*" }
		kind "ConsoleApp"
		targetextension ".so"
		linkoptions {
			"-shared",
		}
		links {
			"EGL",
			"GLESv2",
		}

	configuration { "nacl*" }
		kind "ConsoleApp"
		targetextension ".nexe"
		links {
			"ppapi",
			"ppapi_gles2",
			"pthread",
		}

	configuration { "pnacl" }
		kind "ConsoleApp"
		targetextension ".pexe"
		links {
			"ppapi",
			"ppapi_gles2",
			"pthread",
		}

	configuration { "asmjs" }
		kind "ConsoleApp"
		targetextension ".bc"

<<<<<<< HEAD
	configuration { "linux-* or freebsd" }
=======
	configuration { "linux-* or freebsd", "not linux-steamlink" }
>>>>>>> upstream/master
		links {
			"X11",
			"GL",
			"pthread",
		}

<<<<<<< HEAD
=======
	configuration { "linux-steamlink" }
		links {
			"EGL",
			"GLESv2",
			"SDL2",
			"pthread",
		}

>>>>>>> upstream/master
	configuration { "rpi" }
		links {
			"X11",
			"GLESv2",
			"EGL",
			"bcm_host",
			"vcos",
			"vchiq_arm",
			"pthread",
		}

	configuration { "osx" }
		linkoptions {
			"-framework Cocoa",
<<<<<<< HEAD
			"-framework Metal",
			"-framework QuartzCore",
			"-framework OpenGL",
=======
			"-framework QuartzCore",
			"-framework OpenGL",
			"-weak_framework Metal",
>>>>>>> upstream/master
		}

	configuration { "ios* or tvos*" }
		kind "ConsoleApp"
		linkoptions {
			"-framework CoreFoundation",
			"-framework Foundation",
<<<<<<< HEAD
			"-framework Metal",
			"-framework OpenGLES",
			"-framework UIKit",
			"-framework QuartzCore",
=======
			"-framework OpenGLES",
			"-framework UIKit",
			"-framework QuartzCore",
			"-weak_framework Metal",
>>>>>>> upstream/master
		}

	configuration { "xcode4", "ios" }
		kind "WindowedApp"
		files {
			path.join(BGFX_DIR, "examples/runtime/iOS-Info.plist"),
		}

	configuration { "xcode4", "tvos" }
		kind "WindowedApp"
		files {
			path.join(BGFX_DIR, "examples/runtime/tvOS-Info.plist"),
		}

	configuration { "qnx*" }
		targetextension ""
		links {
			"EGL",
			"GLESv2",
		}

	configuration {}

	strip()
end

dofile "bgfx.lua"

<<<<<<< HEAD
group "examples"
dofile "example-common.lua"

group "libs"
bgfxProject("", "StaticLib", {})

group "examples"
exampleProject("00-helloworld")
exampleProject("01-cubes")
exampleProject("02-metaballs")
exampleProject("03-raymarch")
exampleProject("04-mesh")
exampleProject("05-instancing")
exampleProject("06-bump")
exampleProject("07-callback")
exampleProject("08-update")
exampleProject("09-hdr")
exampleProject("10-font")
exampleProject("11-fontsdf")
exampleProject("12-lod")
exampleProject("13-stencil")
exampleProject("14-shadowvolumes")
exampleProject("15-shadowmaps-simple")
exampleProject("16-shadowmaps")
exampleProject("17-drawstress")
exampleProject("18-ibl")
exampleProject("19-oit")
exampleProject("20-nanovg")
exampleProject("21-deferred")
exampleProject("22-windows")
exampleProject("23-vectordisplay")
exampleProject("24-nbody")

-- C99 source doesn't compile under WinRT settings
if not premake.vstudio.iswinrt() then
	exampleProject("25-c99")
=======
group "libs"
bgfxProject("", "StaticLib", {})

dofile(path.join(BX_DIR, "scripts/bx.lua"))

if _OPTIONS["with-examples"] or _OPTIONS["with-tools"] then
	group "examples"
	dofile "example-common.lua"
end

if _OPTIONS["with-examples"] then
	group "examples"
	exampleProject("00-helloworld")
	exampleProject("01-cubes")
	exampleProject("02-metaballs")
	exampleProject("03-raymarch")
	exampleProject("04-mesh")
	exampleProject("05-instancing")
	exampleProject("06-bump")
	exampleProject("07-callback")
	exampleProject("08-update")
	exampleProject("09-hdr")
	exampleProject("10-font")
	exampleProject("11-fontsdf")
	exampleProject("12-lod")
	exampleProject("13-stencil")
	exampleProject("14-shadowvolumes")
	exampleProject("15-shadowmaps-simple")
	exampleProject("16-shadowmaps")
	exampleProject("17-drawstress")
	exampleProject("18-ibl")
	exampleProject("19-oit")
	exampleProject("20-nanovg")
	exampleProject("21-deferred")
	exampleProject("22-windows")
	exampleProject("23-vectordisplay")
	exampleProject("24-nbody")
	exampleProject("26-occlusion")
	exampleProject("27-terrain")
	exampleProject("28-wireframe")
	exampleProject("29-debugdraw")
	exampleProject("30-picking")
	exampleProject("31-rsm")
	exampleProject("32-particles")

	-- C99 source doesn't compile under WinRT settings
	if not premake.vstudio.iswinrt() then
		exampleProject("25-c99")
	end
>>>>>>> upstream/master
end

if _OPTIONS["with-shared-lib"] then
	group "libs"
	bgfxProject("-shared-lib", "SharedLib", {})
end

if _OPTIONS["with-tools"] then
	group "tools"
<<<<<<< HEAD
	dofile "makedisttex.lua"
	dofile "shaderc.lua"
	dofile "texturec.lua"
=======
	dofile "shaderc.lua"
	dofile "texturec.lua"
	dofile "texturev.lua"
>>>>>>> upstream/master
	dofile "geometryc.lua"
end
