**************
* WASAPI API *
**************

<<<<<<< HEAD
----------------------------------------
Microsoft Visual Studio 2005SP1/2008/10
----------------------------------------
No specific actions are needed to compile WASAPI API under Visual Studio.
You are only required to install min. Windows Vista SDK (v6.0A) prior
compilation.

----------------------------------------
MinGW (GCC 32-bit)/ MinGW64 (GCC 64-bit)
----------------------------------------
To compile under MinGW you are required to include 'mingw-include' directory
which contains necessary files with WASAPI API. These files are modified
in order to be compiled by MinGW compiler. These files are taken from 
Windows Vista SDK (v6.0A). MinGW compilation is tested and proved to be
fully working under 32-bit and 64-bit modes.
MinGW   (32-bit) tested: gcc version 4.4.0 (GCC)
MinGW64 (64-bit) tested: gcc version 4.4.4 20100226 (prerelease) (GCC)

PortAudio
/Dmitry Kostjuchenko/
04.03.2010
=======
-------------------------------------------
Microsoft Visual Studio 2005 SP1 and higher
-------------------------------------------
No specific action is required to compile WASAPI API under Visual Studio.
You are only required to install min. Windows Vista SDK (v6.0A) prior
the compilation. To compile with WASAPI specific functionality for Windows 8
and higher the min. Windows 8 SDK is required.

----------------------------------------
MinGW (GCC 32/64-bit)
----------------------------------------
To compile with MinGW you are required to include 'mingw-include' directory
which contains necessary files with WASAPI API. These files are modified
for the compatibility with MinGW compiler. These files are taken from 
the Windows Vista SDK (v6.0A). MinGW compilation is tested and proved to be
fully working.
MinGW   (32-bit) tested min. version: gcc version 4.4.0 (GCC)
MinGW64 (64-bit) tested min. version: gcc version 4.4.4 20100226 (prerelease) (GCC)
>>>>>>> upstream/master
