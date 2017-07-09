-- license:BSD-3-Clause
-- copyright-holders:MAMEdev Team

---------------------------------------------------------------------------
--
--   mess.lua
--
--   MESS target makefile
--
---------------------------------------------------------------------------

--------------------------------------------------
-- specify available sound cores; some of these are
-- only for MAME and so aren't included
--------------------------------------------------

SOUNDS["VRC6"] = true

--------------------------------------------------
-- specify available machine cores
--------------------------------------------------

MACHINES["YM2148"] = true

--------------------------------------------------
-- specify available bus cores
--------------------------------------------------

BUSES["A7800"] = true
BUSES["A800"] = true
BUSES["ABCBUS"] = true
BUSES["GAMEBOY"] = true
BUSES["GAMEGEAR"] = true
BUSES["GBA"] = true
BUSES["GENERIC"] = true
BUSES["MIDI"] = true
BUSES["MEGADRIVE"] = true
BUSES["MSX_SLOT"] = true
BUSES["NEOGEO"] = true
BUSES["NES"] = true
BUSES["NES_CTRL"] = true
BUSES["PCE"] = true
BUSES["PSX_CONTROLLER"] = true
BUSES["SATURN"] = true
BUSES["SEGA8"] = true
BUSES["SMS_CTRL"] = true
BUSES["SMS_EXP"] = true
BUSES["SNES"] = true
BUSES["SNES_CTRL"] = true
BUSES["VCS"] = true
BUSES["VCS_CTRL"] = true
BUSES["WSWAN"] = true

--------------------------------------------------
-- this is the list of driver libraries that
-- comprise MESS plus messdriv.*", which contains
-- the list of drivers
--------------------------------------------------
function linkProjects_mame_mess(_target, _subtarget)
	links {
		"ascii",
		"atari",
		"bandai",
		"funtech",
		"nec",
		"nintendo",
		"sega",
		"snk",
		"sony",
	}
end

function createMESSProjects(_target, _subtarget, _name)
	project (_name)
	targetsubdir(_target .."_" .. _subtarget)
	kind (LIBTYPE)
	uuid (os.uuid("drv-" .. _target .."_" .. _subtarget .. "_" .._name))

	includedirs {
		MAME_DIR .. "src/osd",
		MAME_DIR .. "src/emu",
		MAME_DIR .. "src/devices",
		MAME_DIR .. "src/mame",
		MAME_DIR .. "src/lib",
		MAME_DIR .. "src/lib/util",
		MAME_DIR .. "src/lib/netlist",
		MAME_DIR .. "3rdparty",
		GEN_DIR  .. "mame/layout",
	}
end

function createProjects_mame_mess(_target, _subtarget)

createMESSProjects(_target, _subtarget, "ascii")
files {
	MAME_DIR .. "src/mame/drivers/msx.cpp",
	MAME_DIR .. "src/mame/includes/msx.h",
	MAME_DIR .. "src/mame/machine/msx.cpp",
	MAME_DIR .. "src/mame/machine/msx_matsushita.cpp",
	MAME_DIR .. "src/mame/machine/msx_matsushita.h",
	MAME_DIR .. "src/mame/machine/msx_s1985.cpp",
	MAME_DIR .. "src/mame/machine/msx_s1985.h",
	MAME_DIR .. "src/mame/machine/msx_switched.cpp",
	MAME_DIR .. "src/mame/machine/msx_switched.h",
	MAME_DIR .. "src/mame/machine/msx_systemflags.cpp",
	MAME_DIR .. "src/mame/machine/msx_systemflags.h",
}

createMESSProjects(_target, _subtarget, "atari")
files {
	MAME_DIR .. "src/mame/drivers/a2600.cpp",
	MAME_DIR .. "src/mame/drivers/a7800.cpp",
	MAME_DIR .. "src/mame/video/maria.cpp",
	MAME_DIR .. "src/mame/video/maria.h",
	MAME_DIR .. "src/mame/drivers/atari400.cpp",
	MAME_DIR .. "src/mame/machine/atarifdc.cpp",
	MAME_DIR .. "src/mame/machine/atarifdc.h",
}

createMESSProjects(_target, _subtarget, "bandai")
files {
	MAME_DIR .. "src/mame/drivers/wswan.cpp",
	MAME_DIR .. "src/mame/includes/wswan.h",
	MAME_DIR .. "src/mame/audio/wswan_snd.cpp",
	MAME_DIR .. "src/mame/audio/wswan_snd.h",
	MAME_DIR .. "src/mame/machine/wswan.cpp",
	MAME_DIR .. "src/mame/video/wswan_video.cpp",
	MAME_DIR .. "src/mame/video/wswan_video.h",
}
	
	--------------------------------------------------
	-- layout dependencies
	--------------------------------------------------

	dependency {
		{ MAME_DIR .. "src/mame/drivers/wswan.cpp", GEN_DIR .. "mame/layout/wswan.lh" },
	}

	custombuildtask {
		layoutbuildtask("mame/layout", "wswan"),
	}

createMESSProjects(_target, _subtarget, "funtech")
files {
	MAME_DIR .. "src/mame/drivers/supracan.cpp",
}

createMESSProjects(_target, _subtarget, "nec")
files {
	MAME_DIR .. "src/mame/drivers/pce.cpp",
	MAME_DIR .. "src/mame/includes/pce.h",
	MAME_DIR .. "src/mame/machine/pce.cpp",
	MAME_DIR .. "src/mame/machine/pce_cd.cpp",
	MAME_DIR .. "src/mame/machine/pce_cd.h",
}

createMESSProjects(_target, _subtarget, "nintendo")
files {
	MAME_DIR .. "src/mame/drivers/gb.cpp",
	MAME_DIR .. "src/mame/includes/gb.h",
	MAME_DIR .. "src/mame/audio/gb.cpp",
	MAME_DIR .. "src/mame/audio/gb.h",
	MAME_DIR .. "src/mame/machine/gb.cpp",
	MAME_DIR .. "src/mame/video/gb_lcd.cpp",
	MAME_DIR .. "src/mame/video/gb_lcd.h",
	MAME_DIR .. "src/mame/drivers/gba.cpp",
	MAME_DIR .. "src/mame/includes/gba.h",
	MAME_DIR .. "src/mame/video/gba.cpp",
	MAME_DIR .. "src/mame/drivers/n64.cpp",
	MAME_DIR .. "src/mame/includes/n64.h",
	MAME_DIR .. "src/mame/drivers/nes.cpp",
	MAME_DIR .. "src/mame/includes/nes.h",
	MAME_DIR .. "src/mame/machine/nes.cpp",
	MAME_DIR .. "src/mame/video/nes.cpp",
	MAME_DIR .. "src/mame/drivers/snes.cpp",
	MAME_DIR .. "src/mame/includes/snes.h",
	MAME_DIR .. "src/mame/machine/snescx4.cpp",
	MAME_DIR .. "src/mame/machine/snescx4.h",
}

createMESSProjects(_target, _subtarget, "sega")
files {
	MAME_DIR .. "src/mame/drivers/megadriv.cpp",
	MAME_DIR .. "src/mame/includes/megadriv.h",
	MAME_DIR .. "src/mame/drivers/saturn.cpp",
	MAME_DIR .. "src/mame/drivers/segapico.cpp",
	MAME_DIR .. "src/mame/drivers/sms.cpp",
	MAME_DIR .. "src/mame/includes/sms.h",
	MAME_DIR .. "src/mame/machine/sms.cpp",
	MAME_DIR .. "src/mame/machine/mega32x.cpp",
	MAME_DIR .. "src/mame/machine/mega32x.h",
	MAME_DIR .. "src/mame/machine/megacd.cpp",
	MAME_DIR .. "src/mame/machine/megacd.h",
	MAME_DIR .. "src/mame/machine/megacdcd.cpp",
	MAME_DIR .. "src/mame/machine/megacdcd.h",
}
	
	--------------------------------------------------
	-- layout dependencies
	--------------------------------------------------

	dependency {
		{ MAME_DIR .. "src/mame/drivers/sms.cpp", GEN_DIR .. "mame/layout/sms1.lh" },
		{ MAME_DIR .. "src/mame/machine/megacd.cpp", GEN_DIR .. "mame/layout/megacd.lh" },
	}

	custombuildtask {
		layoutbuildtask("mame/layout", "sms1"),
		layoutbuildtask("mame/layout", "megacd"),
	}

createMESSProjects(_target, _subtarget, "snk")
files {
	MAME_DIR .. "src/mame/drivers/ng_aes.cpp",
	MAME_DIR .. "src/mame/drivers/ngp.cpp",
	MAME_DIR .. "src/mame/video/k1ge.cpp",
	MAME_DIR .. "src/mame/video/k1ge.h",
}

createMESSProjects(_target, _subtarget, "sony")
files {
	MAME_DIR .. "src/mame/drivers/pockstat.cpp",
	MAME_DIR .. "src/mame/drivers/psx.cpp",
	MAME_DIR .. "src/mame/machine/psxcd.cpp",
	MAME_DIR .. "src/mame/machine/psxcd.h",
}

end
