configuration { "x32" }
	defines {
		"USE_MMX_INTERP_SCALE",
	}

configuration { }

includedirs {
	MAME_DIR .. "src/osd/windows/scale",
}
files {
	MAME_DIR .. "src/osd/windows/scale/scale.cpp",
	MAME_DIR .. "src/osd/windows/scale/2xpm.cpp",
	MAME_DIR .. "src/osd/windows/scale/2xsai.cpp",
	MAME_DIR .. "src/osd/windows/scale/hq2x.cpp",
	MAME_DIR .. "src/osd/windows/scale/hq2x.dat",
	MAME_DIR .. "src/osd/windows/scale/hq2x.h",
	MAME_DIR .. "src/osd/windows/scale/hq3x.cpp",
	MAME_DIR .. "src/osd/windows/scale/hq3x.dat",
	MAME_DIR .. "src/osd/windows/scale/interp.h",
	MAME_DIR .. "src/osd/windows/scale/port.h",
	MAME_DIR .. "src/osd/windows/scale/scale2x.cpp",
	MAME_DIR .. "src/osd/windows/scale/scale3x.cpp",
	MAME_DIR .. "src/osd/windows/scale/scanline.cpp",
	MAME_DIR .. "src/osd/windows/scale/snes9x_render.cpp*",
	MAME_DIR .. "src/osd/windows/scale/vba_hq2x.cpp",
	MAME_DIR .. "src/osd/windows/scale/vba_hq2x.h",
	MAME_DIR .. "src/osd/windows/scale/vba_interp.h",
	MAME_DIR .. "src/osd/windows/scale/xbrz.cpp",
	MAME_DIR .. "src/osd/windows/scale/xbrz.h",
	MAME_DIR .. "src/osd/windows/scale/xbrz_config.h",
}
