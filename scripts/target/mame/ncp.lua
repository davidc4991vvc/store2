---------------------------------------------------------------------------
--
--   ncp.lua
--
--   Small driver-specific example makefile
--   Use make SUBTARGET=ncp to build
--
--   Copyright Nicola Salmoria and the MAME Team.
--   Visit  http://mamedev.org for licensing and usage restrictions.
--
---------------------------------------------------------------------------


--------------------------------------------------
-- Specify all the CPU cores necessary for the
-- drivers referenced in tiny.c.
--------------------------------------------------

CPUS["Z80"] = true
CPUS["I386"] = true
CPUS["MCS48"] = true
CPUS["M680X0"] = true
CPUS["ARM7"] = true
CPUS["SH2"] = true
CPUS["PIC16C5X"] = true
CPUS["DSP16A"] = true

--------------------------------------------------
-- Specify all the sound cores necessary for the
-- drivers referenced in tiny.c.
--------------------------------------------------

SOUNDS["YM2151"] = true
SOUNDS["YM2203"] = true
SOUNDS["YM2608"] = true
SOUNDS["YM2610"] = true
SOUNDS["MSM5205"] = true
SOUNDS["OKIM6295"] = true
SOUNDS["QSOUND"] = true
SOUNDS["CDDA"] = true
SOUNDS["ICS2115"] = true
SOUNDS["YMZ770"] = true
if _OPTIONS["WINUI"] == "1" then
SOUNDS["VLM5030"] = true
end

--------------------------------------------------
-- specify available video cores
--------------------------------------------------

VIDEOS["BUFSPRITE"] = true
VIDEOS["EPIC12"] = true

--------------------------------------------------
-- specify available machine cores
--------------------------------------------------

MACHINES["EEPROMDEV"] = true
MACHINES["INTELFLASH"] = true
MACHINES["WD33C93"] = true
MACHINES["TIMEKPR"] = true
MACHINES["SCSI"] = true
MACHINES["V3021"] = true
MACHINES["PD4990A_OLD"] = true
MACHINES["UPD1990A"] = true
MACHINES["Z80CTC"] = true
MACHINES["I8255"] = true

--------------------------------------------------
-- specify available bus cores
--------------------------------------------------

BUSES["SCSI"] = true
BUSES["NEOGEO"] = true

--------------------------------------------------
-- This is the list of files that are necessary
-- for building all of the drivers referenced
-- in tiny.c
--------------------------------------------------

function createMAMEProjects(_target, _subtarget, _name)
	project (_name)
	targetsubdir(_target .."_" .. _subtarget)
	kind "StaticLib"
	uuid (os.uuid("drv-" .. _target .."_" .. _subtarget .. "_" .._name))

	includedirs {
		MAME_DIR .. "src/osd",
		MAME_DIR .. "src/emu",
		MAME_DIR .. "src/mame",
		MAME_DIR .. "src/lib",
		MAME_DIR .. "src/lib/util",
		MAME_DIR .. "3rdparty",
		MAME_DIR .. "3rdparty/zlib",
		GEN_DIR  .. "mame/layout",
	}
end

function createProjects_mame_ncp(_target, _subtarget)
	project ("mame_ncp")
	targetsubdir(_target .."_" .. _subtarget)
	kind "StaticLib"
	uuid (os.uuid("drv-mame-ncp"))
	
	options {
		"ForceCPP",
	}
	
	includedirs {
		MAME_DIR .. "src/osd",
		MAME_DIR .. "src/emu",
		MAME_DIR .. "src/mame",
		MAME_DIR .. "src/lib",
		MAME_DIR .. "src/lib/util",
		MAME_DIR .. "3rdparty",
		MAME_DIR .. "3rdparty/zlib",
		GEN_DIR  .. "mame/layout",
	}	

createMAMEProjects(_target, _subtarget, "capcom")
files {
	MAME_DIR .. "src/mame/drivers/cps1.cpp",
	MAME_DIR .. "src/mame/video/cps1.cpp",
	MAME_DIR .. "src/mame/drivers/kenseim.cpp",
	MAME_DIR .. "src/mame/drivers/cps2.cpp",
	MAME_DIR .. "src/mame/machine/cps2crpt.cpp",
	MAME_DIR .. "src/mame/drivers/cps3.cpp",
	MAME_DIR .. "src/mame/audio/cps3.cpp",
	MAME_DIR .. "src/mame/drivers/fcrash.cpp",
	MAME_DIR .. "src/mame/machine/kabuki.cpp",
}

createMAMEProjects(_target, _subtarget, "igs")
files {
	MAME_DIR .. "src/mame/drivers/pgm.cpp",
	MAME_DIR .. "src/mame/video/pgm.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs027a_type1.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs027a_type2.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs027a_type3.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs025_igs012.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs025_igs022.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs025_igs028.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_orlegend.cpp",
	MAME_DIR .. "src/mame/drivers/pgm2.cpp",
	MAME_DIR .. "src/mame/machine/igs036crypt.cpp",
	MAME_DIR .. "src/mame/machine/pgmcrypt.cpp",
	MAME_DIR .. "src/mame/machine/igs025.cpp",
	MAME_DIR .. "src/mame/machine/igs022.cpp",
	MAME_DIR .. "src/mame/machine/igs028.cpp",
}

createMAMEProjects(_target, _subtarget, "neogeo")
files {
	MAME_DIR .. "src/mame/drivers/neogeo.cpp",
	MAME_DIR .. "src/mame/video/neogeo.cpp",
	MAME_DIR .. "src/mame/drivers/neogeo_noslot.cpp",
	MAME_DIR .. "src/mame/video/neogeo_spr.cpp",
	MAME_DIR .. "src/mame/machine/neocrypt.cpp",
	MAME_DIR .. "src/mame/machine/ng_memcard.cpp",
}

	--------------------------------------------------
	-- layout dependencies
	--------------------------------------------------

	dependency {
		{ MAME_DIR .. "src/mame/drivers/neogeo.cpp", GEN_DIR .. "mame/layout/neogeo.lh" },
		{ MAME_DIR .. "src/mame/drivers/cps3.cpp", GEN_DIR .. "mame/layout/sfiii2.lh" },
		{ MAME_DIR .. "src/mame/drivers/kenseim.cpp", GEN_DIR .. "mame/layout/kenseim.lh" },
	}

	custombuildtask {
		layoutbuildtask("mame/layout", "neogeo"),
		layoutbuildtask("mame/layout", "sfiii2"),
		layoutbuildtask("mame/layout", "kenseim"),
	}	
end

function linkProjects_mame_ncp(_target, _subtarget)
	links {
		"mame_ncp",
		"capcom",
		"igs",
		"neogeo",
	}
end
