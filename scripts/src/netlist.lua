-- license:BSD-3-Clause
-- copyright-holders:MAMEdev Team

---------------------------------------------------------------------------
--
--   netlist.lua
--
--   Rules for building netlist cores
--
---------------------------------------------------------------------------

project "netlist"
	uuid "665ef8ac-2a4c-4c3e-a05f-fd1e5db11de9"
	kind (LIBTYPE)

<<<<<<< HEAD
	includedirs {
		MAME_DIR .. "src/lib/netlist",
		MAME_DIR .. "src/osd",
		MAME_DIR .. "src/lib/util",
	}
	--	if _OPTIONS["with-bundled-expat"] then
	--	includedirs {
	--		MAME_DIR .. "3rdparty/expat/lib",
	--	}
	--end


	files {
		MAME_DIR .. "src/lib/netlist/nl_config.h",
		MAME_DIR .. "src/lib/netlist/nl_dice_compat.h",
		MAME_DIR .. "src/lib/netlist/nl_lists.h",
		MAME_DIR .. "src/lib/netlist/nl_time.h",
		MAME_DIR .. "src/lib/netlist/nl_util.h",
		MAME_DIR .. "src/lib/netlist/nl_base.cpp",
		MAME_DIR .. "src/lib/netlist/nl_base.h",
=======
  if _OPTIONS["targetos"]=="windows" then
	configuration { "mingw* or vs*" }
	  defines {
		"UNICODE",
		"_UNICODE",
		"_WIN32_WINNT=0x0501",
		"WIN32_LEAN_AND_MEAN",
		"NOMINMAX",
	  }
  end

	addprojectflags()

	defines {
		"__STDC_CONSTANT_MACROS",
	}

	includedirs {
		MAME_DIR .. "src/lib",
	}

	files {
		MAME_DIR .. "src/lib/netlist/nl_base.cpp",
		MAME_DIR .. "src/lib/netlist/nl_base.h",
		MAME_DIR .. "src/lib/netlist/nl_config.h",
		MAME_DIR .. "src/lib/netlist/nl_errstr.h",
		MAME_DIR .. "src/lib/netlist/nl_dice_compat.h",
		MAME_DIR .. "src/lib/netlist/nl_factory.cpp",
		MAME_DIR .. "src/lib/netlist/nl_factory.h",
		MAME_DIR .. "src/lib/netlist/nl_lists.h",
>>>>>>> upstream/master
		MAME_DIR .. "src/lib/netlist/nl_parser.cpp",
		MAME_DIR .. "src/lib/netlist/nl_parser.h",
		MAME_DIR .. "src/lib/netlist/nl_setup.cpp",
		MAME_DIR .. "src/lib/netlist/nl_setup.h",
<<<<<<< HEAD
		MAME_DIR .. "src/lib/netlist/nl_factory.cpp",
		MAME_DIR .. "src/lib/netlist/nl_factory.h",
		MAME_DIR .. "src/lib/netlist/plib/pconfig.h",
		MAME_DIR .. "src/lib/netlist/plib/palloc.cpp",
		MAME_DIR .. "src/lib/netlist/plib/palloc.h",
		MAME_DIR .. "src/lib/netlist/plib/pfmtlog.cpp",
		MAME_DIR .. "src/lib/netlist/plib/pfmtlog.h",
		MAME_DIR .. "src/lib/netlist/plib/plists.h",
		MAME_DIR .. "src/lib/netlist/plib/poptions.h",
		MAME_DIR .. "src/lib/netlist/plib/pparser.cpp",
		MAME_DIR .. "src/lib/netlist/plib/pparser.h",
=======
		MAME_DIR .. "src/lib/netlist/nl_time.h",
		MAME_DIR .. "src/lib/netlist/plib/pconfig.h",
		MAME_DIR .. "src/lib/netlist/plib/palloc.cpp",
		MAME_DIR .. "src/lib/netlist/plib/palloc.h",
		MAME_DIR .. "src/lib/netlist/plib/pchrono.cpp",
		MAME_DIR .. "src/lib/netlist/plib/pchrono.h",
		MAME_DIR .. "src/lib/netlist/plib/pexception.cpp",
		MAME_DIR .. "src/lib/netlist/plib/pexception.h",
		MAME_DIR .. "src/lib/netlist/plib/pfunction.cpp",
		MAME_DIR .. "src/lib/netlist/plib/pfunction.h",
		MAME_DIR .. "src/lib/netlist/plib/pfmtlog.cpp",
		MAME_DIR .. "src/lib/netlist/plib/pfmtlog.h",
		MAME_DIR .. "src/lib/netlist/plib/plists.h",
		MAME_DIR .. "src/lib/netlist/plib/pdynlib.cpp",
		MAME_DIR .. "src/lib/netlist/plib/pdynlib.h",
		MAME_DIR .. "src/lib/netlist/plib/pmain.cpp",
		MAME_DIR .. "src/lib/netlist/plib/pmain.h",
		MAME_DIR .. "src/lib/netlist/plib/pomp.h",
		MAME_DIR .. "src/lib/netlist/plib/poptions.cpp",
		MAME_DIR .. "src/lib/netlist/plib/poptions.h",
		MAME_DIR .. "src/lib/netlist/plib/pparser.cpp",
		MAME_DIR .. "src/lib/netlist/plib/pparser.h",
		MAME_DIR .. "src/lib/netlist/plib/ppmf.h",
>>>>>>> upstream/master
		MAME_DIR .. "src/lib/netlist/plib/pstate.cpp",
		MAME_DIR .. "src/lib/netlist/plib/pstate.h",
		MAME_DIR .. "src/lib/netlist/plib/pstring.cpp",
		MAME_DIR .. "src/lib/netlist/plib/pstring.h",
		MAME_DIR .. "src/lib/netlist/plib/pstring.cpp",
		MAME_DIR .. "src/lib/netlist/plib/pstring.h",
		MAME_DIR .. "src/lib/netlist/plib/pstream.cpp",
		MAME_DIR .. "src/lib/netlist/plib/pstream.h",
		MAME_DIR .. "src/lib/netlist/plib/ptypes.h",
<<<<<<< HEAD
=======
		MAME_DIR .. "src/lib/netlist/plib/putil.cpp",
		MAME_DIR .. "src/lib/netlist/plib/putil.h",
>>>>>>> upstream/master
		MAME_DIR .. "src/lib/netlist/tools/nl_convert.cpp",
		MAME_DIR .. "src/lib/netlist/tools/nl_convert.h",
		MAME_DIR .. "src/lib/netlist/analog/nld_bjt.cpp",
		MAME_DIR .. "src/lib/netlist/analog/nld_bjt.h",
<<<<<<< HEAD
		MAME_DIR .. "src/lib/netlist/analog/nld_fourterm.cpp",
		MAME_DIR .. "src/lib/netlist/analog/nld_fourterm.h",
		MAME_DIR .. "src/lib/netlist/analog/nld_switches.cpp",
		MAME_DIR .. "src/lib/netlist/analog/nld_switches.h",
		MAME_DIR .. "src/lib/netlist/analog/nld_twoterm.cpp",
=======
		MAME_DIR .. "src/lib/netlist/analog/nlid_fourterm.cpp",
		MAME_DIR .. "src/lib/netlist/analog/nlid_fourterm.h",
		MAME_DIR .. "src/lib/netlist/analog/nld_fourterm.h",
		MAME_DIR .. "src/lib/netlist/analog/nld_switches.cpp",
		MAME_DIR .. "src/lib/netlist/analog/nld_switches.h",
		MAME_DIR .. "src/lib/netlist/analog/nlid_twoterm.cpp",
		MAME_DIR .. "src/lib/netlist/analog/nlid_twoterm.h",
>>>>>>> upstream/master
		MAME_DIR .. "src/lib/netlist/analog/nld_twoterm.h",
		MAME_DIR .. "src/lib/netlist/analog/nld_opamps.cpp",
		MAME_DIR .. "src/lib/netlist/analog/nld_opamps.h",
		MAME_DIR .. "src/lib/netlist/solver/nld_solver.cpp",
		MAME_DIR .. "src/lib/netlist/solver/nld_solver.h",
<<<<<<< HEAD
=======
		MAME_DIR .. "src/lib/netlist/solver/nld_matrix_solver.cpp",
		MAME_DIR .. "src/lib/netlist/solver/nld_matrix_solver.h",
>>>>>>> upstream/master
		MAME_DIR .. "src/lib/netlist/solver/nld_ms_direct.h",
		MAME_DIR .. "src/lib/netlist/solver/nld_ms_direct1.h",
		MAME_DIR .. "src/lib/netlist/solver/nld_ms_direct2.h",
		MAME_DIR .. "src/lib/netlist/solver/nld_ms_sor.h",
		MAME_DIR .. "src/lib/netlist/solver/nld_ms_sor_mat.h",
		MAME_DIR .. "src/lib/netlist/solver/nld_ms_gmres.h",
		MAME_DIR .. "src/lib/netlist/solver/mat_cr.h",
<<<<<<< HEAD
		MAME_DIR .. "src/lib/netlist/solver/nld_ms_direct_lu.h",
		MAME_DIR .. "src/lib/netlist/solver/vector_base.h",		
=======
		MAME_DIR .. "src/lib/netlist/solver/nld_ms_sm.h",
		MAME_DIR .. "src/lib/netlist/solver/nld_ms_w.h",
		MAME_DIR .. "src/lib/netlist/solver/nld_ms_direct_lu.h",
		MAME_DIR .. "src/lib/netlist/solver/vector_base.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_2102A.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_2102A.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_2716.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_2716.h",
>>>>>>> upstream/master
		MAME_DIR .. "src/lib/netlist/devices/nld_4020.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_4020.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_4066.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_4066.h",
<<<<<<< HEAD
		MAME_DIR .. "src/lib/netlist/devices/nld_7400.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7400.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7402.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7402.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7404.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7404.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7408.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7408.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7410.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7410.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7411.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7411.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7420.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7420.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7425.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7425.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7427.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7427.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7430.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7430.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7432.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7432.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7437.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7437.h",
=======
		MAME_DIR .. "src/lib/netlist/devices/nld_4316.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_4316.h",
>>>>>>> upstream/master
		MAME_DIR .. "src/lib/netlist/devices/nld_7448.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7448.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7450.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7450.h",
<<<<<<< HEAD
		MAME_DIR .. "src/lib/netlist/devices/nld_7474.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7474.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7483.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7483.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7486.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7486.h",
=======
		MAME_DIR .. "src/lib/netlist/devices/nld_7473.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7473.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7474.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7474.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7475.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7475.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7483.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7483.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7485.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7485.h",
>>>>>>> upstream/master
		MAME_DIR .. "src/lib/netlist/devices/nld_7490.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7490.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_7493.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_7493.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_74107.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_74107.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_74123.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_74123.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_74153.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_74153.h",
<<<<<<< HEAD
=======
		MAME_DIR .. "src/lib/netlist/devices/nld_74161.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_74161.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_74164.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_74164.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_74165.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_74165.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_74166.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_74166.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_74174.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_74174.h",
>>>>>>> upstream/master
		MAME_DIR .. "src/lib/netlist/devices/nld_74175.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_74175.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_74192.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_74192.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_74193.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_74193.h",
<<<<<<< HEAD
		MAME_DIR .. "src/lib/netlist/devices/nld_74279.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_74279.h",
=======
		MAME_DIR .. "src/lib/netlist/devices/nld_74194.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_74194.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_74365.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_74365.h",
>>>>>>> upstream/master
		MAME_DIR .. "src/lib/netlist/devices/nld_74ls629.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_74ls629.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_82S16.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_82S16.h",
<<<<<<< HEAD
		MAME_DIR .. "src/lib/netlist/devices/nld_9310.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_9310.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_9312.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_9312.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_9316.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_9316.h",
=======
		MAME_DIR .. "src/lib/netlist/devices/nld_82S115.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_82S115.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_82S123.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_82S123.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_82S126.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_82S126.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_9310.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_9310.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_9316.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_9316.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_9322.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_9322.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_am2847.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_am2847.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_dm9334.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_dm9334.h",
>>>>>>> upstream/master
		MAME_DIR .. "src/lib/netlist/devices/nld_ne555.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_ne555.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_mm5837.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_mm5837.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_r2r_dac.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_r2r_dac.h",
<<<<<<< HEAD
=======
		MAME_DIR .. "src/lib/netlist/devices/nld_tristate.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_tristate.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_schmitt.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_schmitt.h",
>>>>>>> upstream/master
		MAME_DIR .. "src/lib/netlist/devices/nld_legacy.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_legacy.h",
		MAME_DIR .. "src/lib/netlist/devices/net_lib.cpp",
		MAME_DIR .. "src/lib/netlist/devices/net_lib.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_log.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_log.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_system.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_system.h",
<<<<<<< HEAD
		MAME_DIR .. "src/lib/netlist/devices/nld_cmos.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_signal.h",
		MAME_DIR .. "src/lib/netlist/devices/nld_truthtable.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nld_truthtable.h",
=======
		MAME_DIR .. "src/lib/netlist/devices/nlid_truthtable.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nlid_truthtable.h",
		MAME_DIR .. "src/lib/netlist/devices/nlid_cmos.h",
		MAME_DIR .. "src/lib/netlist/devices/nlid_system.h",
		MAME_DIR .. "src/lib/netlist/devices/nlid_proxy.cpp",
		MAME_DIR .. "src/lib/netlist/devices/nlid_proxy.h",
		MAME_DIR .. "src/lib/netlist/macro/nlm_base.cpp",
		MAME_DIR .. "src/lib/netlist/macro/nlm_base.h",
>>>>>>> upstream/master
		MAME_DIR .. "src/lib/netlist/macro/nlm_ttl74xx.cpp",
		MAME_DIR .. "src/lib/netlist/macro/nlm_ttl74xx.h",
		MAME_DIR .. "src/lib/netlist/macro/nlm_cd4xxx.cpp",
		MAME_DIR .. "src/lib/netlist/macro/nlm_cd4xxx.h",
		MAME_DIR .. "src/lib/netlist/macro/nlm_opamp.cpp",
		MAME_DIR .. "src/lib/netlist/macro/nlm_opamp.h",
		MAME_DIR .. "src/lib/netlist/macro/nlm_other.cpp",
		MAME_DIR .. "src/lib/netlist/macro/nlm_other.h",
}
