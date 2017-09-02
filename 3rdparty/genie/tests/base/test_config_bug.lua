	T.config_bug_report = { }
	local config_bug = T.config_bug_report
<<<<<<< HEAD
	local vs10_helpers = premake.vstudio.vs10_helpers	
	
	local sln, prjA,prjB,prjC,prjD
=======
	local vs10_helpers = premake.vstudio.vs10_helpers

	local sln, prjA,prjB,prjC,prjD,prjE
>>>>>>> upstream/master
	function config_bug.teardown()
		sln = nil
		prjA = nil
		prjB = nil
		prjC = nil
		prjD = nil
<<<<<<< HEAD
=======
		prjE = nil
>>>>>>> upstream/master
	end
	
	function config_bug.setup()
	end
	


	local config_bug_updated = function ()
	
		local setCommonLibraryConfig = function()
			configuration "Debug or Release"
				kind "StaticLib"

			configuration "DebugDLL or ReleaseDLL"
				kind "SharedLib"
		end

		sln = solution "Test"
		configurations { "Debug", "Release", "DebugDLL", "ReleaseDLL" }
		language "C++"

		prjA = project "A"
			files { "a.cpp" }
			setCommonLibraryConfig()
		prjB = project "B"
			files { "b.cpp" }
			setCommonLibraryConfig()
			configuration "SharedLib"
				links { "A" }
		prjC = project "C"
			files { "c.cpp" }
			setCommonLibraryConfig()
			configuration "SharedLib"
				links { "A", "B" }
<<<<<<< HEAD
		prjD = project "Executable"
			kind "WindowedApp"
			links { "A", "B", "C" }
=======
		prjD = project "D"
			files { "d.cpp" }
			setCommonLibraryConfig()
			configuration "SharedLib"
				links { "A", "B", "C" }
		prjE = project "Executable"
			kind "WindowedApp"
			links { "A", "B", "C", "D" }
>>>>>>> upstream/master

	end

	local kindSetOnConfiguration_and_linkSetOnSharedLibProjB  = function (config_kind)
		sln = solution "DontCare"
		configurations { "DebugDLL"}
		
		configuration "DebugDLL"
			kind(config_kind)
			prjA = project "A"
			prjB = project "B"
				configuration { config_kind }
					links { "A" }
	end
	
	local sharedLibKindSetOnProject_and_linkSetOnSharedLibProjB = function ()
		sln = solution "DontCare"
		configurations { "DebugDLL" }
		project "A"
		prjB = project "B"
			configuration "DebugDLL" 
				kind "SharedLib"
			configuration "SharedLib"
				links { "A" }
				defines {"defineSet"}

	end
<<<<<<< HEAD
	
	
=======


	local kindSetOnConfiguration_and_linkSetOnBundleProjB  = function (config_kind)
		sln = solution "DontCare"
		configurations { "DebugDLL"}

		configuration "DebugDLL"
			kind(config_kind)
			prjA = project "A"
			prjB = project "B"
				configuration { config_kind }
					links { "A" }
	end

	local sharedLibKindSetOnProject_and_linkSetOnBundleProjB = function ()
		sln = solution "DontCare"
		configurations { "DebugDLL" }
		project "A"
		prjB = project "B"
			configuration "DebugDLL"
				kind "Bundle"
			configuration "Bundle"
				links { "A" }
				defines {"defineSet"}

	end


>>>>>>> upstream/master
	function kind_set_on_project_config_block()
		sln = solution "DontCare"
		configurations { "DebugDLL" }
		local A = project "A"
			configuration "DebugDLL" 
				kind "SharedLib"
				defines {"defineSet"}
		return A
	end


	function config_bug.bugUpdated_prjBLinksContainsA()
		config_bug_updated()
		premake.bake.buildconfigs()
		local conf = premake.getconfig(prjB,"DebugDLL","Native")
		test.isnotnil(conf.links.A)
	end
	

	function config_bug.kindSetOnProjectConfigBlock_projKindEqualsSharedLib()
		local proj = kind_set_on_project_config_block()
		premake.bake.buildconfigs()
		local conf = premake.getconfig(proj,"DebugDLL","Native")
		test.isequal("SharedLib",conf.kind)
	end

<<<<<<< HEAD
=======
	function config_bug.kindSetOnProjectConfigBlock_projKindEqualsBundle()
		local proj = kind_set_on_project_config_block()
		premake.bake.buildconfigs()
		local conf = premake.getconfig(proj,"DebugDLL","Native")
		test.isequal("Bundle",conf.kind)
	end

>>>>>>> upstream/master
	function config_bug.defineSetOnProjectConfigBlock_projDefineSetIsNotNil()
		local proj = kind_set_on_project_config_block()
		premake.bake.buildconfigs()
		local conf = premake.getconfig(proj,"DebugDLL","Native")
		test.isnotnil(conf.defines.defineSet)
	end
	
	function config_bug.defineSetInBlockInsideProject ()
		sharedLibKindSetOnProject_and_linkSetOnSharedLibProjB()
		premake.bake.buildconfigs()
		local conf = premake.getconfig(prjB,"DebugDLL","Native")
		test.isnotnil(conf.defines.defineSet)
	end
	
	
	function config_bug.whenKindSetOnProject_PrjBLinksContainsA()
		sharedLibKindSetOnProject_and_linkSetOnSharedLibProjB()
		premake.bake.buildconfigs()
		local conf = premake.getconfig(prjB,"DebugDLL","Native")
		test.isnotnil(conf.links.A)
	end





	function config_bug.whenKindSetOnConfiguration_prjBLinksContainsA_StaticLib()
--		sharedLibKindSetOnConfiguration_and_linkSetOnSharedLibProjB()
		kindSetOnConfiguration_and_linkSetOnSharedLibProjB("StaticLib")
		premake.bake.buildconfigs()
		local config = premake.getconfig(prjB,"DebugDLL","Native")	
		test.isnotnil(config.links.A)	
	end
	
	function config_bug.whenKindSetOnConfiguration_prjBLinksContainsA()
--		sharedLibKindSetOnConfiguration_and_linkSetOnSharedLibProjB()
		kindSetOnConfiguration_and_linkSetOnSharedLibProjB("SharedLib")
		premake.bake.buildconfigs()
<<<<<<< HEAD
		local config = premake.getconfig(prjB,"DebugDLL","Native")	
		test.isnotnil(config.links.A)	
=======
		local config = premake.getconfig(prjB,"DebugDLL","Native")
		test.isnotnil(config.links.A)
	end

	function config_bug.whenKindSetOnConfiguration_prjBLinksContainsA_bundle()
--		sharedLibKindSetOnConfiguration_and_linkSetOnBundleProjB()
		kindSetOnConfiguration_and_linkSetOnBundleProjB("Bundle")
		premake.bake.buildconfigs()
		local config = premake.getconfig(prjB,"DebugDLL","Native")
		test.isnotnil(config.links.A)
>>>>>>> upstream/master
	end
	