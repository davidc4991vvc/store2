--
-- cmdline.lua
-- Functions to define and handle command line actions and options.
-- Copyright (c) 2002-2011 Jason Perkins and the Premake project
--


--
-- Built-in command line options
--

<<<<<<< HEAD
	newoption 
=======
	newoption
>>>>>>> upstream/master
	{
		trigger     = "cc",
		value       = "VALUE",
		description = "Choose a C/C++ compiler set",
		allowed = {
			{ "gcc", "GNU GCC (gcc/g++)" },
			{ "ow",  "OpenWatcom"        },
<<<<<<< HEAD
=======
			{ "ghs", "Green Hills Software" },
>>>>>>> upstream/master
		}
	}

	newoption
	{
		trigger     = "dotnet",
		value       = "VALUE",
		description = "Choose a .NET compiler set",
		allowed = {
			{ "msnet",   "Microsoft .NET (csc)" },
			{ "mono",    "Novell Mono (mcs)"    },
			{ "pnet",    "Portable.NET (cscc)"  },
		}
	}

	newoption
	{
		trigger     = "file",
		value       = "FILE",
		description = "Read FILE as a Premake script; default is 'premake4.lua'"
	}
<<<<<<< HEAD
	
=======

>>>>>>> upstream/master
	newoption
	{
		trigger     = "help",
		description = "Display this information"
	}
<<<<<<< HEAD
		
=======

>>>>>>> upstream/master
	newoption
	{
		trigger     = "os",
		value       = "VALUE",
		description = "Generate files for a different operating system",
		allowed = {
			{ "bsd",      "OpenBSD, NetBSD, or FreeBSD" },
			{ "linux",    "Linux" },
			{ "macosx",   "Apple Mac OS X" },
			{ "solaris",  "Solaris" },
			{ "windows",  "Microsoft Windows" },
		}
	}

	newoption
	{
		trigger     = "platform",
		value       = "VALUE",
		description = "Add target architecture (if supported by action)",
		allowed = {
			{ "x32",         "32-bit" },
			{ "x64",         "64-bit" },
			{ "universal",   "Mac OS X Universal, 32- and 64-bit" },
			{ "universal32", "Mac OS X Universal, 32-bit only" },
			{ "universal64", "Mac OS X Universal, 64-bit only" },
<<<<<<< HEAD
			{ "ps3",         "Playstation 3 (experimental)" },
			{ "orbis",       "Playstation 4" },
			{ "xbox360",     "Xbox 360 (experimental)" },
			{ "ARM",         "ARM (Microsoft)" },
		}
	}
	
=======
			{ "ps3",         "Playstation 3" },
			{ "orbis",       "Playstation 4" },
			{ "xbox360",     "Xbox 360" },
			{ "durango",     "Xbox One" },
			{ "ARM",         "ARM" },
			{ "PowerPC",     "PowerPC" },
		}
	}

>>>>>>> upstream/master
	newoption
	{
		trigger     = "scripts",
		value       = "path",
		description = "Search for additional scripts on the given path"
	}
<<<<<<< HEAD
	
=======

	newoption
	{
		trigger     = "debug-profiler",
		description = "GENie script generation profiler."
	}

>>>>>>> upstream/master
	newoption
	{
		trigger     = "version",
		description = "Display version information"
	}
<<<<<<< HEAD
	
=======
>>>>>>> upstream/master
