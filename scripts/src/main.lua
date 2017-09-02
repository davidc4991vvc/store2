-- license:BSD-3-Clause
-- copyright-holders:MAMEdev Team

---------------------------------------------------------------------------
--
--   main.lua
--
--   Rules for building main binary
--
---------------------------------------------------------------------------

function mainProject(_target, _subtarget)
<<<<<<< HEAD
	if (_target == _subtarget) then
		project (_target .. _OPTIONS["EXTRA_SUFFIX"])
	else
		project (_target .. _OPTIONS["EXTRA_SUFFIX"] .. _subtarget)
	end	
	uuid (os.uuid(_target .. _OPTIONS["EXTRA_SUFFIX"] .."_" .. _subtarget))
	kind "ConsoleApp"

	flags {
		"NoManifest",
		"Symbols", -- always include minimum symbols for executables 
=======
if (_OPTIONS["SOURCES"] == nil) then
	if (_target == _subtarget) then
		project (_target)
	else
		if (_subtarget=="mess") then
			project (_subtarget)
		else
			project (_target .. _subtarget)
		end
	end
else
	project (_subtarget)
end
	uuid (os.uuid(_target .."_" .. _subtarget))
	kind "ConsoleApp"

	configuration { "android*" }
		targetprefix "lib"
		targetname "main"
		targetextension ".so"
		linkoptions {
			"-shared",
			"-Wl,-soname,libmain.so"
		}
		links {
			"EGL",
			"GLESv1_CM",
			"GLESv2",
			"SDL2",
		}
	configuration { "pnacl" }
		kind "ConsoleApp"
		targetextension ".pexe"
		links {
			"ppapi",
			"ppapi_gles2",
			"pthread",
		}

	configuration { "winstore*" }
		kind "WindowedApp"

	configuration {  }

	addprojectflags()
	flags {
		"NoManifest",
		"Symbols", -- always include minimum symbols for executables
>>>>>>> upstream/master
	}

	if _OPTIONS["SYMBOLS"] then
		configuration { "mingw*" }
			postbuildcommands {
				"$(SILENT) echo Dumping symbols.",
				"$(SILENT) objdump --section=.text --line-numbers --syms --demangle $(TARGET) >$(subst .exe,.sym,$(TARGET))"
			}
	end
<<<<<<< HEAD
	
=======

>>>>>>> upstream/master
	configuration { "vs*" }
	flags {
		"Unicode",
	}
<<<<<<< HEAD
if (_OPTIONS["SOURCES"] == nil) then 
=======

	configuration { "winstore*" }
		-- Windows Required Files
		files {
			-- Manifest file
			MAME_DIR .. "scripts/resources/uwp/Package.appxmanifest",
		}

	configuration { "winstore*" }
		files {
			MAME_DIR .. "scripts/resources/uwp/assets/*.png"
		}
		configuration "**/scripts/resources/uwp/assets/*.png"
			flags { "DeploymentContent" }

	-- Effects and Shaders
	configuration { "winstore*" }
		files {
			MAME_DIR .. "artwork/*",
			MAME_DIR .. "artwork/**/*",
			MAME_DIR .. "bgfx/*",
			MAME_DIR .. "bgfx/**/*",
			MAME_DIR .. "hash/*",
			MAME_DIR .. "language/*",
			MAME_DIR .. "language/**/*",
			MAME_DIR .. "plugins/*",
			MAME_DIR .. "plugins/**/*",
		}
		configuration "**/*"
			flags { "DeploymentContent" }

>>>>>>> upstream/master
	configuration { "x64", "Release" }
		targetsuffix "64"
		if _OPTIONS["PROFILE"] then
			targetsuffix "64p"
		end

	configuration { "x64", "Debug" }
		targetsuffix "64d"
		if _OPTIONS["PROFILE"] then
			targetsuffix "64dp"
		end

	configuration { "x32", "Release" }
		targetsuffix ""
		if _OPTIONS["PROFILE"] then
			targetsuffix "p"
		end

	configuration { "x32", "Debug" }
		targetsuffix "d"
		if _OPTIONS["PROFILE"] then
			targetsuffix "dp"
		end

	configuration { "Native", "Release" }
		targetsuffix ""
		if _OPTIONS["PROFILE"] then
			targetsuffix "p"
		end

	configuration { "Native", "Debug" }
		targetsuffix "d"
		if _OPTIONS["PROFILE"] then
			targetsuffix "dp"
		end
<<<<<<< HEAD
end
	configuration { "mingw*" or "vs*" }
		targetextension ".exe"

	configuration { "asmjs" }
		targetextension ".bc"  
		if os.getenv("EMSCRIPTEN") then
			postbuildcommands {
				os.getenv("EMSCRIPTEN") .. "/emcc -O3 -s DISABLE_EXCEPTION_CATCHING=2 -s USE_SDL=2 --memory-init-file 0 -s ALLOW_MEMORY_GROWTH=0 -s TOTAL_MEMORY=268435456 -s EXCEPTION_CATCHING_WHITELIST='[\"__ZN15running_machine17start_all_devicesEv\"]' -s EXPORTED_FUNCTIONS=\"['_main', '_malloc', '__Z14js_get_machinev', '__Z9js_get_uiv', '__Z12js_get_soundv', '__ZN10ui_manager12set_show_fpsEb', '__ZNK10ui_manager8show_fpsEv', '__ZN13sound_manager4muteEbh', '_SDL_PauseAudio']\" $(TARGET) -o " .. MAME_DIR .. _OPTIONS["target"] .. _OPTIONS["subtarget"] .. ".js --post-js " .. MAME_DIR .. "src/osd/sdl/emscripten_post.js",
=======

	configuration { "mingw*" or "vs*" }
		targetextension ".exe"

	configuration { "rpi" }
		targetextension ""

	configuration { "asmjs" }
		targetextension ".bc"
		if os.getenv("EMSCRIPTEN") then
			local emccopts = ""
				.. " -O" .. _OPTIONS["OPTIMIZE"]
				.. " -s USE_SDL=2"
				.. " -s USE_SDL_TTF=2"
				.. " --memory-init-file 0"
				.. " -s ALLOW_MEMORY_GROWTH=0"
				.. " -s TOTAL_MEMORY=268435456"
				.. " -s DISABLE_EXCEPTION_CATCHING=2"
				.. " -s EXCEPTION_CATCHING_WHITELIST='[\"__ZN15running_machine17start_all_devicesEv\",\"__ZN12cli_frontend7executeEiPPc\"]'"
				.. " -s EXPORTED_FUNCTIONS=\"['_main', '_malloc', '__ZN15running_machine30emscripten_get_running_machineEv', '__ZN15running_machine17emscripten_get_uiEv', '__ZN15running_machine20emscripten_get_soundEv', '__ZN15mame_ui_manager12set_show_fpsEb', '__ZNK15mame_ui_manager8show_fpsEv', '__ZN13sound_manager4muteEbh', '_SDL_PauseAudio', '_SDL_SendKeyboardKey', '__ZN15running_machine15emscripten_saveEPKc', '__ZN15running_machine15emscripten_loadEPKc', '__ZN15running_machine21emscripten_hard_resetEv', '__ZN15running_machine21emscripten_soft_resetEv', '__ZN15running_machine15emscripten_exitEv']\""
				.. " --pre-js " .. _MAKE.esc(MAME_DIR) .. "src/osd/modules/sound/js_sound.js"
				.. " --post-js " .. _MAKE.esc(MAME_DIR) .. "scripts/resources/emscripten/emscripten_post.js"
				.. " --embed-file " .. _MAKE.esc(MAME_DIR) .. "bgfx/chains@bgfx/chains"
				.. " --embed-file " .. _MAKE.esc(MAME_DIR) .. "bgfx/effects@bgfx/effects"
				.. " --embed-file " .. _MAKE.esc(MAME_DIR) .. "bgfx/shaders/essl@bgfx/shaders/essl"
				.. " --embed-file " .. _MAKE.esc(MAME_DIR) .. "artwork/slot-mask.png@artwork/slot-mask.png"

			if _OPTIONS["SYMBOLS"]~=nil and _OPTIONS["SYMBOLS"]~="0" then
				emccopts = emccopts
					.. " -g" .. _OPTIONS["SYMLEVEL"]
					.. " -s DEMANGLE_SUPPORT=1"
			end

			if _OPTIONS["WEBASSEMBLY"] then
				emccopts = emccopts
					.. " -s BINARYEN=1"
			end

			if _OPTIONS["ARCHOPTS"] then
				emccopts = emccopts .. " " .. _OPTIONS["ARCHOPTS"]
			end

			postbuildcommands {
				os.getenv("EMSCRIPTEN") .. "/emcc " .. emccopts .. " $(TARGET) -o " .. _MAKE.esc(MAME_DIR) .. _OPTIONS["target"] .. _OPTIONS["subtarget"] .. ".js",
>>>>>>> upstream/master
			}
		end

	configuration { }

<<<<<<< HEAD
	if _OPTIONS["SEPARATE_BIN"]~="1" then 
		targetdir(MAME_DIR)
	end
	
	findfunction("linkProjects_" .. _OPTIONS["target"] .. "_" .. _OPTIONS["subtarget"])(_OPTIONS["target"], _OPTIONS["subtarget"])
	links {
		"osd_" .. _OPTIONS["osd"],
	}
	if (_OPTIONS["SOURCES"] == nil) then 
		links {
			"bus",
		}
	end
	links {
		"netlist",
		"optional",
		"emu",
		"formats",
	}
=======
	if _OPTIONS["targetos"]=="android" then
		includedirs {
			MAME_DIR .. "3rdparty/SDL2/include",
		}

		files {
			MAME_DIR .. "3rdparty/SDL2/src/main/android/SDL_android_main.c",
		}
		targetsuffix ""
		if _OPTIONS["SEPARATE_BIN"]~="1" then
			if _OPTIONS["PLATFORM"]=="arm" then
				targetdir(MAME_DIR .. "android-project/app/src/main/libs/armeabi-v7a")
			end
			if _OPTIONS["PLATFORM"]=="arm64" then
				targetdir(MAME_DIR .. "android-project/app/src/main/libs/arm64-v8a")
			end
			if _OPTIONS["PLATFORM"]=="mips" then
				targetdir(MAME_DIR .. "android-project/app/src/main/libs/mips")
			end
			if _OPTIONS["PLATFORM"]=="mips64" then
				targetdir(MAME_DIR .. "android-project/app/src/main/libs/mips64")
			end
			if _OPTIONS["PLATFORM"]=="x86" then
				targetdir(MAME_DIR .. "android-project/app/src/main/libs/x86")
			end
			if _OPTIONS["PLATFORM"]=="x64" then
				targetdir(MAME_DIR .. "android-project/app/src/main/libs/x86_64")
			end
		end
	else
		if _OPTIONS["SEPARATE_BIN"]~="1" then
			targetdir(MAME_DIR)
		end
	end

if (STANDALONE~=true) then
	findfunction("linkProjects_" .. _OPTIONS["target"] .. "_" .. _OPTIONS["subtarget"])(_OPTIONS["target"], _OPTIONS["subtarget"])
end
	links {
		"osd_" .. _OPTIONS["osd"],
	}
	links {
		"qtdbg_" .. _OPTIONS["osd"],
	}
if (STANDALONE~=true) then
	links {
		"frontend",
	}
end
if (MACHINES["NETLIST"]~=null) then
	links {
		"netlist",
	}
end
	links {
		"optional",
		"emu",
	}
--if (STANDALONE~=true) then
	links {
		"formats",
	}
--end
>>>>>>> upstream/master
if #disasm_files > 0 then
	links {
		"dasm",
	}
end
	links {
		"utils",
<<<<<<< HEAD
		"expat",
		"softfloat",
		"jpeg",
		"7z",
		"lua",
		"lsqlite3",
		"jsoncpp",
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

	if _OPTIONS["with-bundled-sqlite3"] then
		links {
			"sqllite3",
		}
	else
		links {
			"sqlite3",
		}
	end

	if _OPTIONS["NO_USE_MIDI"]~="1" then
		links {
			"portmidi",
		}
	end
	if (USE_BGFX == 1) then
		links {
			"bgfx"
		}
	end
	links{
		"ocore_" .. _OPTIONS["osd"],
	}
	
	override_resources = false;
	
	maintargetosdoptions(_target)
=======
		ext_lib("expat"),
		"softfloat",
		ext_lib("jpeg"),
		"7z",
	}
if (STANDALONE~=true) then
	links {
		ext_lib("lua"),
		"lualibs",
	}
if (_OPTIONS["osd"] ~= "uwp") then
	links {
		"linenoise",
	}
end
end
	links {
		ext_lib("zlib"),
		ext_lib("flac"),
		ext_lib("utf8proc"),
	}
if (STANDALONE~=true) then
	links {
		ext_lib("sqlite3"),
	}
end

	if _OPTIONS["NO_USE_PORTAUDIO"]~="1" then
		links {
			ext_lib("portaudio"),
		}
		if _OPTIONS["targetos"]=="windows" then
			links {
				"setupapi",
			}
		end
	end
	if _OPTIONS["NO_USE_MIDI"]~="1" then
		links {
			ext_lib("portmidi"),
		}
	end
	links {
		"bgfx",
		"bx",
		"ocore_" .. _OPTIONS["osd"],
	}

	override_resources = false;

	maintargetosdoptions(_target,_subtarget)
>>>>>>> upstream/master

	includedirs {
		MAME_DIR .. "src/osd",
		MAME_DIR .. "src/emu",
		MAME_DIR .. "src/devices",
		MAME_DIR .. "src/" .. _target,
		MAME_DIR .. "src/lib",
		MAME_DIR .. "src/lib/util",
		MAME_DIR .. "3rdparty",
		GEN_DIR  .. _target .. "/layout",
		GEN_DIR  .. "resource",
<<<<<<< HEAD
	}

	if _OPTIONS["with-bundled-zlib"] then
		includedirs {
			MAME_DIR .. "3rdparty/zlib",
		}
	end

	if _OPTIONS["targetos"]=="macosx" and (not override_resources) then
		linkoptions {
			"-sectcreate __TEXT __info_plist " .. GEN_DIR .. "/resource/" .. _target .. "-Info.plist"
		}
		custombuildtask {
			{ MAME_DIR .. "src/version.cpp" ,  GEN_DIR  .. "/resource/" .. _target .. "-Info.plist",    {  MAME_DIR .. "scripts/build/verinfo.py" }, {"@echo Emitting " .. _target .. "-Info.plist" .. "...",    PYTHON .. " $(1)  -p -b " .. _target .. " $(<) > $(@)" }},
		}
		dependency {
			{ "$(TARGET)" ,  GEN_DIR  .. "/resource/" .. _target .. "-Info.plist", true  },
		}

	end

	if _OPTIONS["targetos"]=="windows" and (not override_resources) then
		local rcfile = MAME_DIR .. "src/" .. _target .. "/osd/".._OPTIONS["osd"].."/" .. _target ..".rc"
		if not os.isfile(rcfile) then
			rcfile = MAME_DIR .. "src/" .. _target .. "/osd/windows/" .. _target ..".rc"
		end
		
=======
		ext_includedir("zlib"),
		ext_includedir("flac"),
	}


if (STANDALONE==true) then
	standalone();
end

if (STANDALONE~=true) then
	if _OPTIONS["targetos"]=="macosx" and (not override_resources) then
		linkoptions {
			"-sectcreate __TEXT __info_plist " .. _MAKE.esc(GEN_DIR) .. "resource/" .. _subtarget .. "-Info.plist"
		}
		custombuildtask {
			{ GEN_DIR .. "version.cpp" ,  GEN_DIR .. "resource/" .. _subtarget .. "-Info.plist",    {  MAME_DIR .. "scripts/build/verinfo.py" }, {"@echo Emitting " .. _subtarget .. "-Info.plist" .. "...",    PYTHON .. " $(1)  -p -b " .. _subtarget .. " $(<) > $(@)" }},
		}
		dependency {
			{ "$(TARGET)" ,  GEN_DIR  .. "resource/" .. _subtarget .. "-Info.plist", true  },
		}

	end
	local rctarget = _subtarget

	if _OPTIONS["targetos"]=="windows" and (not override_resources) then
		rcfile = MAME_DIR .. "scripts/resources/windows/" .. _subtarget .. "/" .. rctarget ..".rc"
>>>>>>> upstream/master
		if os.isfile(rcfile) then
			files {
				rcfile,
			}
			dependency {
<<<<<<< HEAD
				{ "$(OBJDIR)/".._target ..".res" ,  GEN_DIR  .. "/resource/" .. _target .. "vers.rc", true  },
			}
		else
			files {
				MAME_DIR .. "src/osd/windows/mame.rc",
			}
			dependency {
				{ "$(OBJDIR)/mame.res" ,  GEN_DIR  .. "/resource/" .. _target .. "vers.rc", true  },
			}
		end	
	end

	files {
		MAME_DIR .. "src/".._target .."/" .. _target ..".cpp",
		MAME_DIR .. "src/version.cpp",
		GEN_DIR  .. _target .. "/" .. _subtarget .."/drivlist.cpp",
	}

	--FIXME
	make_drivlist(_target, _subtarget)
	
	configuration { "mingw*" }
		custombuildtask {	
			{ MAME_DIR .. "src/version.cpp" ,  GEN_DIR  .. "/resource/" .. _target .. "vers.rc",    {  MAME_DIR .. "scripts/build/verinfo.py" }, {"@echo Emitting " .. _target .. "vers.rc" .. "...",    PYTHON .. " $(1)  -r -b " .. _target .. " $(<) > $(@)" }},
		}	
	
	configuration { "vs*" }
		prebuildcommands {	
			"mkdir " .. path.translate(GEN_DIR  .. "/resource/","\\") .. " 2>NUL",
			"@echo Emitting ".. _target .. "vers.rc...",
			PYTHON .. " " .. path.translate(MAME_DIR .. "scripts/build/verinfo.py","\\") .. " -r -b " .. _target .. " " .. path.translate(MAME_DIR .. "src/version.cpp","\\") .. " > " .. path.translate(GEN_DIR  .. "/resource/" .. _target .. "vers.rc", "\\") ,
		}	
	
	 
	configuration { }

	debugdir (MAME_DIR)
	debugargs ("-window")
end

function mainProject_with_ui(_target, _subtarget)
	if (_target == _subtarget) then
		project (_target .. _OPTIONS["EXTRA_SUFFIX"] .. "ui")
	else
		project (_target .. _OPTIONS["EXTRA_SUFFIX"] .. _subtarget .. "ui")
	end	
	uuid (os.uuid(_target .. _OPTIONS["EXTRA_SUFFIX"] .."_" .. _subtarget .. "ui"))
	kind "WindowedApp"

	options {
		"ForceCPP",
	}
	flags {
		"NoManifest",
		"Symbols", -- always include minimum symbols for executables 
	}

	if _OPTIONS["SYMBOLS"] then
		configuration { "mingw*" }
			postbuildcommands {
				"$(SILENT) echo Dumping symbols.",
				"$(SILENT) objdump --section=.text --line-numbers --syms --demangle $(TARGET) >$(subst .exe,.sym,$(TARGET))"
			}
	end

	configuration { "mingw*-gcc" }
		linkoptions {
			"-municode",
			"-lmingw32",
			"-Wl,--allow-multiple-definition",
		}

	configuration { "vs*" }
	flags {
		"Unicode",
	}

	configuration { "x64", "Release" }
		targetsuffix "64"
		if _OPTIONS["PROFILE"] then
			targetsuffix "64p"
		end

	configuration { "x64", "Debug" }
		targetsuffix "64d"
		if _OPTIONS["PROFILE"] then
			targetsuffix "64dp"
		end

	configuration { "x32", "Release" }
		targetsuffix ""
		if _OPTIONS["PROFILE"] then
			targetsuffix "p"
		end

	configuration { "x32", "Debug" }
		targetsuffix "d"
		if _OPTIONS["PROFILE"] then
			targetsuffix "dp"
		end

	configuration { "Native", "Release" }
		targetsuffix ""
		if _OPTIONS["PROFILE"] then
			targetsuffix "p"
		end

	configuration { "Native", "Debug" }
		targetsuffix "d"
		if _OPTIONS["PROFILE"] then
			targetsuffix "dp"
		end

	configuration { "mingw*" or "vs*" }
		targetextension ".exe"

	configuration { "asmjs" }
		targetextension ".bc"  

	configuration { }

	if _OPTIONS["SEPARATE_BIN"]~="1" then 
		targetdir(MAME_DIR)
	end
	
	findfunction("linkProjects_" .. _OPTIONS["target"] .. "_" .. _OPTIONS["subtarget"])(_OPTIONS["target"], _OPTIONS["subtarget"])
	if (_OPTIONS["SOURCES"] == nil) then 
		links {
			"bus",
		}
	end
	links {
		"osd_winui",
		"netlist",
		"optional",
		"emu",
		"dasm",
		"utils",
		"expat",
		"softfloat",
		"jpeg",
		"7z",
		"formats",
		"lua",
		"lsqlite3",
		"sqllite3",
		"jsoncpp",
		"mongoose",
	}
	if _OPTIONS["NO_USE_MIDI"]=="0" then
		links {
			"portmidi",
		}
	end
	if (USE_BGFX == 1) then
		links {
			"bgfx"
		}
	end
	links{
		"ocore_winui",
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

	override_resources = false;
	
	maintargetosdoptions(_target)

	includedirs {
		MAME_DIR .. "src/osd",
		MAME_DIR .. "src/emu",
		MAME_DIR .. "src/" .. _target,
		MAME_DIR .. "src/lib",
		MAME_DIR .. "src/lib/util",
		MAME_DIR .. "3rdparty",
		GEN_DIR  .. _target .. "/layout",
		GEN_DIR  .. "resource",
	}
	if _OPTIONS["with-bundled-zlib"] then
		includedirs {
			MAME_DIR .. "3rdparty/zlib",
		}
	end

	override_resources = true;
	local rcfile = MAME_DIR .. "src/osd/winui/" .. _target .. "ui.rc"

	if not os.isfile(rcfile) then
		print(string.format("***** %s not found *****",rcfile))
		os.exit();
	end

	files {
		rcfile,
	}
	dependency {
		{ "$(OBJDIR)/".._target .."ui.res" ,  GEN_DIR  .. "/resource/" .. _target .. "vers.rc", true  },
	}

	files {
		MAME_DIR .. "src/".._target .."/" .. _target ..".cpp",
		MAME_DIR .. "src/version.cpp",
		GEN_DIR  .. _target .. "/" .. _subtarget .."/drivlist.cpp",
	}

	--FIXME
	make_drivlist(_target, _subtarget)

if _OPTIONS["FORCE_VERSION_COMPILE"]=="1" then
	configuration { "gmake" }
		dependency {
			{ ".PHONY", ".FORCE", true },
			{ "$(OBJDIR)/src/version.o", ".FORCE", true },
		}
end
	configuration { "mingw*" }
		custombuildtask {	
			{ MAME_DIR .. "src/version.cpp" ,  GEN_DIR  .. "/resource/" .. _target .. "vers.rc",    {  MAME_DIR .. "scripts/build/verinfo.py" }, {"@echo Emitting " .. _target .. "vers.rc" .. "...",    PYTHON .. " $(1)  -r -b " .. _target .. " $(<) > $(@)" }},
		}	
	
	configuration { "vs*" }
		prebuildcommands {	
			"mkdir " .. path.translate(GEN_DIR  .. "/resource/","\\") .. " 2>NUL",
			"@echo Emitting ".. _target .. "vers.rc...",
			PYTHON .. " " .. path.translate(MAME_DIR .. "scripts/build/verinfo.py","\\") .. " -r -b " .. _target .. " " .. path.translate(MAME_DIR .. "src/version.cpp","\\") .. " > " .. path.translate(GEN_DIR  .. "/resource/" .. _target .. "vers.rc", "\\") ,
		}	
	
	 
	configuration { }

	debugdir (MAME_DIR)
	debugargs ("-window")
end

function make_drivlist(_target, _subtarget)
	if _subtarget=="mame" or _subtarget=="arcade" or _subtarget=="ncp" then
		DRVLIST = {}
		if _subtarget=="mame" then
			DRVLIST = { GEN_DIR .. _target .. "/" .. _subtarget .."/mamedecrypted.lst",
					  GEN_DIR .. _target .. "/" .. _subtarget .."/mamehb.lst",
					  GEN_DIR .. _target .. "/" .. _subtarget .."/mameplus.lst",
					  GEN_DIR .. _target .. "/" .. _subtarget .."/mess.lst",
					  MAME_DIR .. "scripts/build/makelist.py" }
		else
			DRVLIST = { GEN_DIR .. _target .. "/" .. _subtarget .."/mamedecrypted.lst",
					  GEN_DIR .. _target .. "/" .. _subtarget .."/mamehb.lst",
					  GEN_DIR .. _target .. "/" .. _subtarget .."/mameplus.lst",
					  MAME_DIR .. "scripts/build/makelist.py" }
		end
		custombuildtask {
			{ MAME_DIR .. "src/".._target .."/%.lst" ,  GEN_DIR  .. _target .. "/" .. _subtarget .."/%.lst",    {  MAME_DIR .. "scripts/build/makelist.py" }, {"@echo Generating $@...", "@echo #include \"$<\" > $@.h", "$(CC) $(DEFINES) -I. -E $@.h -o $@" }},
			{ GEN_DIR .. _target .. "/" .. _subtarget .."/mame.lst",  GEN_DIR  .. _target .. "/" .. _subtarget .."/drivlist.cpp",
				DRVLIST, {"@echo Building driver list...",    "echo " .. PYTHON .. " " .. MAME_DIR .. "scripts/build/makelist.py" .. " " .. _OPTIONS["USE_DRIVER_SWITCH"] .. " $^ > $@",PYTHON .. " " .. MAME_DIR .. "scripts/build/makelist.py" .. " " .. _OPTIONS["USE_DRIVER_SWITCH"] .. " $^ > $@" }},
		}
	else
		custombuildtask {
			{ MAME_DIR .. "src/".._target .."/" .. _subtarget ..".lst" ,  GEN_DIR  .. _target .. "/" .. _subtarget .."/" .. _subtarget ..".lst",    {  MAME_DIR .. "scripts/build/makelist.py" }, {"@echo Generating $@...", "@echo #include \"$<\" > $@.h", "$(CC) -I. -E $@.h -o $@" }},
			{ GEN_DIR .. _target .."/" .. _subtarget .."/" .. _subtarget ..".lst" ,  GEN_DIR  .. _target .. "/" .. _subtarget .."/drivlist.cpp",    {  MAME_DIR .. "scripts/build/makelist.py" }, {"@echo Building driver list...",    PYTHON .. " " .. MAME_DIR .. "scripts/build/makelist.py" .. " " .. _OPTIONS["USE_DRIVER_SWITCH"] .. " $^ > $@" }},
		}
	end
=======
				{ "$(OBJDIR)/".._subtarget ..".res" ,  GEN_DIR  .. "resource/" .. rctarget .. "vers.rc", true  },
			}
		else
			rctarget = "mame"
			files {
				MAME_DIR .. "scripts/resources/windows/mame/mame.rc",
			}
			dependency {
				{ "$(OBJDIR)/mame.res" ,  GEN_DIR  .. "resource/" .. rctarget .. "vers.rc", true  },
			}
		end
	end

	local mainfile = MAME_DIR .. "src/".._target .."/" .. _subtarget ..".cpp"
	if not os.isfile(mainfile) then
		mainfile = MAME_DIR .. "src/".._target .."/" .. _target ..".cpp"
	end
	files {
		mainfile,
		GEN_DIR .. "version.cpp",
		GEN_DIR  .. _target .. "/" .. _subtarget .."/drivlist.cpp",
	}

	if (_OPTIONS["SOURCES"] == nil) then

		if os.isfile(MAME_DIR .. "src/".._target .."/" .. _subtarget ..".flt") then
			dependency {
			{
				GEN_DIR  .. _target .. "/" .. _subtarget .."/drivlist.cpp",  MAME_DIR .. "src/".._target .."/" .. _target ..".lst", true },
			}
			custombuildtask {
				{ MAME_DIR .. "src/".._target .."/" .. _subtarget ..".flt" ,  GEN_DIR  .. _target .. "/" .. _subtarget .."/drivlist.cpp",    {  MAME_DIR .. "scripts/build/makelist.py", MAME_DIR .. "src/".._target .."/" .. _target ..".lst"  }, {"@echo Building driver list...",    PYTHON .. " $(1) $(2) $(<) > $(@)" }},
			}
		else
			if os.isfile(MAME_DIR .. "src/".._target .."/" .. _subtarget ..".lst") then
				custombuildtask {
					{ MAME_DIR .. "src/".._target .."/" .. _subtarget ..".lst" ,  GEN_DIR  .. _target .. "/" .. _subtarget .."/drivlist.cpp",    {  MAME_DIR .. "scripts/build/makelist.py" }, {"@echo Building driver list...",    PYTHON .. " $(1) $(<) > $(@)" }},
				}
			else
				dependency {
				{
					GEN_DIR  .. _target .. "/" .. _target .."/drivlist.cpp",  MAME_DIR .. "src/".._target .."/" .. _target ..".lst", true },
				}
				custombuildtask {
					{ MAME_DIR .. "src/".._target .."/" .. _target ..".lst" ,  GEN_DIR  .. _target .. "/" .. _target .."/drivlist.cpp",    {  MAME_DIR .. "scripts/build/makelist.py" }, {"@echo Building driver list...",    PYTHON .. " $(1) $(<) > $(@)" }},
				}
			end
		end
	end

	if (_OPTIONS["SOURCES"] ~= nil) then
			dependency {
			{
				GEN_DIR  .. _target .. "/" .. _subtarget .."/drivlist.cpp",  MAME_DIR .. "src/".._target .."/" .. _target ..".lst", true },
			}
			custombuildtask {
				{ GEN_DIR .. _target .."/" .. _subtarget ..".flt" ,  GEN_DIR  .. _target .. "/" .. _subtarget .."/drivlist.cpp",    {  MAME_DIR .. "scripts/build/makelist.py", MAME_DIR .. "src/".._target .."/" .. _target ..".lst"  }, {"@echo Building driver list...",    PYTHON .. " $(1) $(2) $(<) > $(@)" }},
			}
	end

	configuration { "mingw*" }
		custombuildtask {
			{ GEN_DIR .. "version.cpp" ,  GEN_DIR  .. "resource/" .. rctarget .. "vers.rc",    {  MAME_DIR .. "scripts/build/verinfo.py" }, {"@echo Emitting " .. rctarget .. "vers.rc" .. "...",    PYTHON .. " $(1)  -r -b " .. rctarget .. " $(<) > $(@)" }},
		}

	configuration { "vs*" }
		prebuildcommands {
			"mkdir " .. path.translate(GEN_DIR  .. "resource/","\\") .. " 2>NUL",
			"@echo Emitting ".. rctarget .. "vers.rc...",
			PYTHON .. " " .. path.translate(MAME_DIR .. "scripts/build/verinfo.py","\\") .. " -r -b " .. rctarget .. " " .. path.translate(GEN_DIR .. "version.cpp","\\") .. " > " .. path.translate(GEN_DIR  .. "resource/" .. rctarget .. "vers.rc", "\\") ,
		}
end

	configuration { }

	if _OPTIONS["DEBUG_DIR"]~=nil then
		debugdir(_OPTIONS["DEBUG_DIR"])
	else
		debugdir (MAME_DIR)
	end
	if _OPTIONS["DEBUG_ARGS"]~=nil then
		debugargs (_OPTIONS["DEBUG_ARGS"])
	else
		debugargs ("-window")
	end

>>>>>>> upstream/master
end
