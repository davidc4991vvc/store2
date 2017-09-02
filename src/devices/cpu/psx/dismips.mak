<<<<<<< HEAD
..\..\..\..\dismips.exe: dismips.c psxdasm.c ..\mips\r3kdasm.c ..\mips\mips3dsm.c ../../../lib/util/corestr.c
	gcc -O3 -x c++ -Wall -Wno-sign-compare -I../../../emu -I../../../osd -I../../../lib/util -I../../../lib/expat -DINLINE="static __inline__" -DSTANDALONE -DLSB_FIRST dismips.c psxdasm.c ..\mips\r3kdasm.c ..\mips\mips3dsm.c ../../../lib/util/corestr.c -o../../../../dismips
=======
..\..\..\..\dismips.exe: dismips.cpp psxdasm.cpp ..\mips\r3kdasm.cpp ..\mips\mips3dsm.cpp ../../../lib/util/corestr.cpp
	g++ -O3 -x c++ -Wall -Wno-sign-compare -I../.. -I../../../emu -I../../../osd -I../../../lib/util -I../../../lib/expat -DINLINE="static __inline__" -DSTANDALONE -DLSB_FIRST dismips.cpp psxdasm.cpp ..\mips\r3kdasm.cpp ..\mips\mips3dsm.cpp ../../../lib/util/corestr.cpp -o../../../../dismips
>>>>>>> upstream/master
