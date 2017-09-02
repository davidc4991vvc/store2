--
<<<<<<< HEAD
-- Copyright 2010-2015 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

=======
-- Copyright 2010-2017 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
--

function filesexist(_srcPath, _dstPath, _files)
	for _, file in ipairs(_files) do
		file = path.getrelative(_srcPath, file)
		local filePath = path.join(_dstPath, file)
		if not os.isfile(filePath) then return false end
	end

	return true
end

function overridefiles(_srcPath, _dstPath, _files)

	local remove = {}
	local add = {}
	for _, file in ipairs(_files) do
		file = path.getrelative(_srcPath, file)
		local filePath = path.join(_dstPath, file)
		if not os.isfile(filePath) then return end

		table.insert(remove, path.join(_srcPath, file))
		table.insert(add, filePath)
	end

	removefiles {
		remove,
	}

	files {
		add,
	}
end

>>>>>>> upstream/master
function bgfxProject(_name, _kind, _defines)

	project ("bgfx" .. _name)
		uuid (os.uuid("bgfx" .. _name))
		kind (_kind)

		if _kind == "SharedLib" then
			defines {
				"BGFX_SHARED_LIB_BUILD=1",
			}

<<<<<<< HEAD
=======
			links {
				"bx",
			}

>>>>>>> upstream/master
			configuration { "vs20* or mingw*" }
				links {
					"gdi32",
					"psapi",
				}

			configuration { "mingw*" }
				linkoptions {
					"-shared",
				}

			configuration { "linux-*" }
				buildoptions {
					"-fPIC",
				}

			configuration {}
		end

		includedirs {
			path.join(BGFX_DIR, "3rdparty"),
			path.join(BGFX_DIR, "3rdparty/dxsdk/include"),
<<<<<<< HEAD
			path.join(BGFX_DIR, "../bx/include"),
=======
			path.join(BX_DIR,   "include"),
>>>>>>> upstream/master
		}

		defines {
			_defines,
		}

<<<<<<< HEAD
=======
		links {
			"bx",
		}

>>>>>>> upstream/master
		if _OPTIONS["with-glfw"] then
			defines {
				"BGFX_CONFIG_MULTITHREADED=0",
			}
		end

		if _OPTIONS["with-ovr"] then
			defines {
<<<<<<< HEAD
=======
--				"BGFX_CONFIG_MULTITHREADED=0",
>>>>>>> upstream/master
				"BGFX_CONFIG_USE_OVR=1",
			}
			includedirs {
				"$(OVR_DIR)/LibOVR/Include",
			}
<<<<<<< HEAD
=======

			configuration { "x32" }
				libdirs { path.join("$(OVR_DIR)/LibOVR/Lib/Windows/Win32/Release", _ACTION) }

			configuration { "x64" }
				libdirs { path.join("$(OVR_DIR)/LibOVR/Lib/Windows/x64/Release", _ACTION) }

			configuration { "x32 or x64" }
				links { "libovr" }

			configuration {}
>>>>>>> upstream/master
		end

		configuration { "Debug" }
			defines {
				"BGFX_CONFIG_DEBUG=1",
			}

		configuration { "android*" }
			links {
				"EGL",
				"GLESv2",
			}

		configuration { "winphone8* or winstore8*" }
			linkoptions {
				"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
			}

		configuration { "*clang*" }
			buildoptions {
				"-Wno-microsoft-enum-value", -- enumerator value is not representable in the underlying type 'int'
				"-Wno-microsoft-const-init", -- default initialization of an object of const type '' without a user-provided default constructor is a Microsoft extension
			}

		configuration { "osx" }
			linkoptions {
				"-framework Cocoa",
<<<<<<< HEAD
				"-framework Metal",
				"-framework QuartzCore",
				"-framework OpenGL",
			}

		configuration { "not nacl" }
			includedirs {
				--nacl has GLES2 headers modified...
				path.join(BGFX_DIR, "3rdparty/khronos"),
			}

=======
				"-framework QuartzCore",
				"-framework OpenGL",
				"-weak_framework Metal",
				"-weak_framework MetalKit",
			}

		configuration { "not nacl", "not linux-steamlink" }
			includedirs {
				--nacl has GLES2 headers modified...
				--steamlink has EGL headers modified...
				path.join(BGFX_DIR, "3rdparty/khronos"),
			}

		configuration { "linux-steamlink" }
			defines {
				"EGL_API_FB",
			}

>>>>>>> upstream/master
		configuration {}

		includedirs {
			path.join(BGFX_DIR, "include"),
		}

		files {
			path.join(BGFX_DIR, "include/**.h"),
			path.join(BGFX_DIR, "src/**.cpp"),
			path.join(BGFX_DIR, "src/**.h"),
		}

		removefiles {
			path.join(BGFX_DIR, "src/**.bin.h"),
		}

<<<<<<< HEAD
		if _OPTIONS["with-amalgamated"] then
			excludes {
				path.join(BGFX_DIR, "src/bgfx.cpp"),
				path.join(BGFX_DIR, "src/glcontext_egl.cpp"),
				path.join(BGFX_DIR, "src/glcontext_glx.cpp"),
				path.join(BGFX_DIR, "src/glcontext_ppapi.cpp"),
				path.join(BGFX_DIR, "src/glcontext_wgl.cpp"),
				path.join(BGFX_DIR, "src/image.cpp"),
				path.join(BGFX_DIR, "src/ovr.cpp"),
				path.join(BGFX_DIR, "src/renderdoc.cpp"),
				path.join(BGFX_DIR, "src/renderer_d3d9.cpp"),
				path.join(BGFX_DIR, "src/renderer_d3d11.cpp"),
				path.join(BGFX_DIR, "src/renderer_d3d12.cpp"),
				path.join(BGFX_DIR, "src/renderer_null.cpp"),
				path.join(BGFX_DIR, "src/renderer_gl.cpp"),
				path.join(BGFX_DIR, "src/renderer_vk.cpp"),
				path.join(BGFX_DIR, "src/shader_dx9bc.cpp"),
				path.join(BGFX_DIR, "src/shader_dxbc.cpp"),
				path.join(BGFX_DIR, "src/shader_spirv.cpp"),
=======
		overridefiles(BGFX_DIR, path.join(BGFX_DIR, "../bgfx-ext"), {
			path.join(BGFX_DIR, "src/renderer_gnm.cpp"),
			path.join(BGFX_DIR, "src/renderer_gnm.h"),
		})

		if _OPTIONS["with-amalgamated"] then
			excludes {
				path.join(BGFX_DIR, "src/bgfx.cpp"),
				path.join(BGFX_DIR, "src/debug_**.cpp"),
				path.join(BGFX_DIR, "src/glcontext_**.cpp"),
				path.join(BGFX_DIR, "src/image.cpp"),
				path.join(BGFX_DIR, "src/hmd**.cpp"),
				path.join(BGFX_DIR, "src/renderer_**.cpp"),
				path.join(BGFX_DIR, "src/shader**.cpp"),
				path.join(BGFX_DIR, "src/topology.cpp"),
>>>>>>> upstream/master
				path.join(BGFX_DIR, "src/vertexdecl.cpp"),
			}

			configuration { "xcode* or osx or ios*" }
				files {
					path.join(BGFX_DIR, "src/amalgamated.mm"),
				}

				excludes {
<<<<<<< HEAD
					path.join(BGFX_DIR, "src/glcontext_eagl.mm"),
					path.join(BGFX_DIR, "src/glcontext_nsgl.mm"),
					path.join(BGFX_DIR, "src/renderer_mtl.mm"),
					path.join(BGFX_DIR, "src/amalgamated.cpp"),
				}

=======
					path.join(BGFX_DIR, "src/glcontext_**.mm"),
					path.join(BGFX_DIR, "src/renderer_**.mm"),
					path.join(BGFX_DIR, "src/amalgamated.cpp"),
				}

			configuration { "not (xcode* or osx or ios*)" }
				excludes {
					path.join(BGFX_DIR, "src/**.mm"),
				}

>>>>>>> upstream/master
			configuration {}

		else
			configuration { "xcode* or osx or ios*" }
				files {
<<<<<<< HEAD
					path.join(BGFX_DIR, "src/glcontext_eagl.mm"),
					path.join(BGFX_DIR, "src/glcontext_nsgl.mm"),
					path.join(BGFX_DIR, "src/renderer_mtl.mm"),
=======
					path.join(BGFX_DIR, "src/glcontext_**.mm"),
					path.join(BGFX_DIR, "src/renderer_**.mm"),
>>>>>>> upstream/master
				}

			configuration {}

			excludes {
				path.join(BGFX_DIR, "src/amalgamated.**"),
			}
		end

		configuration {}

		copyLib()
end
