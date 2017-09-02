// license:BSD-3-Clause
// copyright-holders:R. Belmont,byuu
/***************************************************************************

    dasm7725.c
    Disassembler for the portable uPD7725 emulator.
    Written by byuu
    MAME conversion by R. Belmont

***************************************************************************/

#include "emu.h"
#include "upd7725.h"

<<<<<<< HEAD
CPU_DISASSEMBLE( upd7725 )
{
	static char output[256];
	UINT32 opcode = oprom[2] | (oprom[1] << 8) | (oprom[0] << 16);
	UINT32 type = (opcode >> 22);

//  printf("dasm: PC %x opcode %08x\n", pc, opcode);

	memset(output, 0, sizeof(output));

	if(type == 0 || type == 1) {  //OP,RT
		UINT8 pselect = (opcode >> 20)&0x3;  //P select
		UINT8 alu     = (opcode >> 16)&0xf;  //ALU operation mode
		UINT8 asl     = (opcode >> 15)&0x1;  //accumulator select
		UINT8 dpl     = (opcode >> 13)&0x3;  //DP low modify
		UINT8 dphm    = (opcode >>  9)&0xf;  //DP high XOR modify
		UINT8 rpdcr   = (opcode >>  8)&0x1;  //RP decrement
		UINT8 src     = (opcode >>  4)&0xf;  //move source
		UINT8 dst     = (opcode >>  0)&0xf;  //move destination

	switch(alu) {
		case  0: strcat(output, "nop  "); break;
		case  1: strcat(output, "or   "); break;
		case  2: strcat(output, "and  "); break;
		case  3: strcat(output, "xor  "); break;
		case  4: strcat(output, "sub  "); break;
		case  5: strcat(output, "add  "); break;
		case  6: strcat(output, "sbb  "); break;
		case  7: strcat(output, "adc  "); break;
		case  8: strcat(output, "dec  "); break;
		case  9: strcat(output, "inc  "); break;
		case 10: strcat(output, "cmp  "); break;
		case 11: strcat(output, "shr1 "); break;
		case 12: strcat(output, "shl1 "); break;
		case 13: strcat(output, "shl2 "); break;
		case 14: strcat(output, "shl4 "); break;
		case 15: strcat(output, "xchg "); break;
=======
CPU_DISASSEMBLE(upd7725)
{
	uint32_t opcode = oprom[2] | (oprom[1] << 8) | (oprom[0] << 16);
	uint32_t type = (opcode >> 22);

//  printf("dasm: PC %x opcode %08x\n", pc, opcode);

	if(type == 0 || type == 1) {  //OP,RT
		uint8_t pselect = (opcode >> 20)&0x3;  //P select
		uint8_t alu     = (opcode >> 16)&0xf;  //ALU operation mode
		uint8_t asl     = (opcode >> 15)&0x1;  //accumulator select
		uint8_t dpl     = (opcode >> 13)&0x3;  //DP low modify
		uint8_t dphm    = (opcode >>  9)&0xf;  //DP high XOR modify
		uint8_t rpdcr   = (opcode >>  8)&0x1;  //RP decrement
		uint8_t src     = (opcode >>  4)&0xf;  //move source
		uint8_t dst     = (opcode >>  0)&0xf;  //move destination

	switch(alu) {
		case  0: stream << "nop  "; break;
		case  1: stream << "or   "; break;
		case  2: stream << "and  "; break;
		case  3: stream << "xor  "; break;
		case  4: stream << "sub  "; break;
		case  5: stream << "add  "; break;
		case  6: stream << "sbb  "; break;
		case  7: stream << "adc  "; break;
		case  8: stream << "dec  "; break;
		case  9: stream << "inc  "; break;
		case 10: stream << "cmp  "; break;
		case 11: stream << "shr1 "; break;
		case 12: stream << "shl1 "; break;
		case 13: stream << "shl2 "; break;
		case 14: stream << "shl4 "; break;
		case 15: stream << "xchg "; break;
>>>>>>> upstream/master
	}

	if(alu < 8) {
		switch(pselect) {
<<<<<<< HEAD
		case 0: strcat(output, "ram,"); break;
		case 1: strcat(output, "idb,"); break;
		case 2: strcat(output, "m,"); break;
		case 3: strcat(output, "n,"); break;
=======
		case 0: stream << "ram,"; break;
		case 1: stream << "idb,"; break;
		case 2: stream << "m,"; break;
		case 3: stream << "n,"; break;
>>>>>>> upstream/master
		}
	}

	switch(asl) {
<<<<<<< HEAD
		case 0: strcat(output, "a"); break;
		case 1: strcat(output, "b"); break;
	}

	if(dst) {
		strcat(output, " | mov ");

		switch(src) {
		case  0: strcat(output, "trb,"); break;
		case  1: strcat(output, "a,"); break;
		case  2: strcat(output, "b,"); break;
		case  3: strcat(output, "tr,"); break;
		case  4: strcat(output, "dp,"); break;
		case  5: strcat(output, "rp,"); break;
		case  6: strcat(output, "ro,"); break;
		case  7: strcat(output, "sgn,"); break;
		case  8: strcat(output, "dr,"); break;
		case  9: strcat(output, "drnf,"); break;
		case 10: strcat(output, "sr,"); break;
		case 11: strcat(output, "sim,"); break;
		case 12: strcat(output, "sil,"); break;
		case 13: strcat(output, "k,"); break;
		case 14: strcat(output, "l,"); break;
		case 15: strcat(output, "mem,"); break;
		}

		switch(dst) {
		case  0: strcat(output, "non"); break;
		case  1: strcat(output, "a"); break;
		case  2: strcat(output, "b"); break;
		case  3: strcat(output, "tr"); break;
		case  4: strcat(output, "dp"); break;
		case  5: strcat(output, "rp"); break;
		case  6: strcat(output, "dr"); break;
		case  7: strcat(output, "sr"); break;
		case  8: strcat(output, "sol"); break;
		case  9: strcat(output, "som"); break;
		case 10: strcat(output, "k"); break;
		case 11: strcat(output, "klr"); break;
		case 12: strcat(output, "klm"); break;
		case 13: strcat(output, "l"); break;
		case 14: strcat(output, "trb"); break;
		case 15: strcat(output, "mem"); break;
=======
		case 0: stream << "a"; break;
		case 1: stream << "b"; break;
	}

	if(dst) {
		stream << " | mov ";

		switch(src) {
		case  0: stream << "trb,"; break;
		case  1: stream << "a,"; break;
		case  2: stream << "b,"; break;
		case  3: stream << "tr,"; break;
		case  4: stream << "dp,"; break;
		case  5: stream << "rp,"; break;
		case  6: stream << "ro,"; break;
		case  7: stream << "sgn,"; break;
		case  8: stream << "dr,"; break;
		case  9: stream << "drnf,"; break;
		case 10: stream << "sr,"; break;
		case 11: stream << "sim,"; break;
		case 12: stream << "sil,"; break;
		case 13: stream << "k,"; break;
		case 14: stream << "l,"; break;
		case 15: stream << "mem,"; break;
		}

		switch(dst) {
		case  0: stream << "non"; break;
		case  1: stream << "a"; break;
		case  2: stream << "b"; break;
		case  3: stream << "tr"; break;
		case  4: stream << "dp"; break;
		case  5: stream << "rp"; break;
		case  6: stream << "dr"; break;
		case  7: stream << "sr"; break;
		case  8: stream << "sol"; break;
		case  9: stream << "som"; break;
		case 10: stream << "k"; break;
		case 11: stream << "klr"; break;
		case 12: stream << "klm"; break;
		case 13: stream << "l"; break;
		case 14: stream << "trb"; break;
		case 15: stream << "mem"; break;
>>>>>>> upstream/master
		}
	}

	if(dpl) {
		switch(dpl) {
<<<<<<< HEAD
		case 0: strcat(output, " | dpnop"); break;
		case 1: strcat(output, " | dpinc"); break;
		case 2: strcat(output, " | dpdec"); break;
		case 3: strcat(output, " | dpclr"); break;
=======
		case 0: stream << " | dpnop"; break;
		case 1: stream << " | dpinc"; break;
		case 2: stream << " | dpdec"; break;
		case 3: stream << " | dpclr"; break;
>>>>>>> upstream/master
		}
	}

	if(dphm) {
		switch(dphm) {
<<<<<<< HEAD
		case  0: strcat(output, " | m0"); break;
		case  1: strcat(output, " | m1"); break;
		case  2: strcat(output, " | m2"); break;
		case  3: strcat(output, " | m3"); break;
		case  4: strcat(output, " | m4"); break;
		case  5: strcat(output, " | m5"); break;
		case  6: strcat(output, " | m6"); break;
		case  7: strcat(output, " | m7"); break;
		case  8: strcat(output, " | m8"); break;
		case  9: strcat(output, " | m9"); break;
		case 10: strcat(output, " | ma"); break;
		case 11: strcat(output, " | mb"); break;
		case 12: strcat(output, " | mc"); break;
		case 13: strcat(output, " | md"); break;
		case 14: strcat(output, " | me"); break;
		case 15: strcat(output, " | mf"); break;
=======
		case  0: stream << " | m0"; break;
		case  1: stream << " | m1"; break;
		case  2: stream << " | m2"; break;
		case  3: stream << " | m3"; break;
		case  4: stream << " | m4"; break;
		case  5: stream << " | m5"; break;
		case  6: stream << " | m6"; break;
		case  7: stream << " | m7"; break;
		case  8: stream << " | m8"; break;
		case  9: stream << " | m9"; break;
		case 10: stream << " | ma"; break;
		case 11: stream << " | mb"; break;
		case 12: stream << " | mc"; break;
		case 13: stream << " | md"; break;
		case 14: stream << " | me"; break;
		case 15: stream << " | mf"; break;
>>>>>>> upstream/master
		}
	}

	if(rpdcr == 1) {
<<<<<<< HEAD
		strcat(output, " | rpdec");
	}

	if(type == 1) {
		strcat(output, " | ret");
=======
		stream << " | rpdec";
	}

	if(type == 1) {
		stream << " | ret";
>>>>>>> upstream/master
	}
	}

	if(type == 2) {  //JP
<<<<<<< HEAD
		UINT16 brch = (opcode >> 13) & 0x1ff;  //branch
		UINT16 na  = (opcode >>  2) & 0x7ff;  //next address

	switch(brch) {
		case 0x000: strcat(output, "jmpso "); break;
		case 0x080: strcat(output, "jnca "); break;
		case 0x082: strcat(output, "jca "); break;
		case 0x084: strcat(output, "jncb "); break;
		case 0x086: strcat(output, "jcb "); break;
		case 0x088: strcat(output, "jnza "); break;
		case 0x08a: strcat(output, "jza "); break;
		case 0x08c: strcat(output, "jnzb "); break;
		case 0x08e: strcat(output, "jzb "); break;
		case 0x090: strcat(output, "jnova0 "); break;
		case 0x092: strcat(output, "jova0 "); break;
		case 0x094: strcat(output, "jnovb0 "); break;
		case 0x096: strcat(output, "jovb0 "); break;
		case 0x098: strcat(output, "jnova1 "); break;
		case 0x09a: strcat(output, "jova1 "); break;
		case 0x09c: strcat(output, "jnovb1 "); break;
		case 0x09e: strcat(output, "jovb1 "); break;
		case 0x0a0: strcat(output, "jnsa0 "); break;
		case 0x0a2: strcat(output, "jsa0 "); break;
		case 0x0a4: strcat(output, "jnsb0 "); break;
		case 0x0a6: strcat(output, "jsb0 "); break;
		case 0x0a8: strcat(output, "jnsa1 "); break;
		case 0x0aa: strcat(output, "jsa1 "); break;
		case 0x0ac: strcat(output, "jnsb1 "); break;
		case 0x0ae: strcat(output, "jsb1 "); break;
		case 0x0b0: strcat(output, "jdpl0 "); break;
		case 0x0b1: strcat(output, "jdpln0 "); break;
		case 0x0b2: strcat(output, "jdplf "); break;
		case 0x0b3: strcat(output, "jdplnf "); break;
		case 0x0b4: strcat(output, "jnsiak "); break;
		case 0x0b6: strcat(output, "jsiak "); break;
		case 0x0b8: strcat(output, "jnsoak "); break;
		case 0x0ba: strcat(output, "jsoak "); break;
		case 0x0bc: strcat(output, "jnrqm "); break;
		case 0x0be: strcat(output, "jrqm "); break;
		case 0x100: strcat(output, "ljmp "); break;
		case 0x101: strcat(output, "hjmp "); break;
		case 0x140: strcat(output, "lcall "); break;
		case 0x141: strcat(output, "hcall "); break;
		default:    strcat(output, "??????  "); break;
	}

	char temp[16];

	sprintf(temp, "$%x", na);
	strcat(output, temp);
	}

	if(type == 3) {  //LD
	strcat(output, "ld ");
	UINT16 id = opcode >> 6;
	UINT8 dst = (opcode >> 0) & 0xf;  //destination

	char temp[16];
	sprintf(temp, "$%x,", id);
	strcat(output, temp);

	switch(dst) {
		case  0: strcat(output, "non"); break;
		case  1: strcat(output, "a"); break;
		case  2: strcat(output, "b"); break;
		case  3: strcat(output, "tr"); break;
		case  4: strcat(output, "dp"); break;
		case  5: strcat(output, "rp"); break;
		case  6: strcat(output, "dr"); break;
		case  7: strcat(output, "sr"); break;
		case  8: strcat(output, "sol"); break;
		case  9: strcat(output, "som"); break;
		case 10: strcat(output, "k"); break;
		case 11: strcat(output, "klr"); break;
		case 12: strcat(output, "klm"); break;
		case 13: strcat(output, "l"); break;
		case 14: strcat(output, "trb"); break;
		case 15: strcat(output, "mem"); break;
	}
	}

	strcpy(buffer, output);

=======
		uint16_t brch = (opcode >> 13) & 0x1ff;  //branch
		uint16_t na  = (opcode >>  2) & 0x7ff;  //next address

	switch(brch) {
		case 0x000: stream << "jmpso "; break;
		case 0x080: stream << "jnca "; break;
		case 0x082: stream << "jca "; break;
		case 0x084: stream << "jncb "; break;
		case 0x086: stream << "jcb "; break;
		case 0x088: stream << "jnza "; break;
		case 0x08a: stream << "jza "; break;
		case 0x08c: stream << "jnzb "; break;
		case 0x08e: stream << "jzb "; break;
		case 0x090: stream << "jnova0 "; break;
		case 0x092: stream << "jova0 "; break;
		case 0x094: stream << "jnovb0 "; break;
		case 0x096: stream << "jovb0 "; break;
		case 0x098: stream << "jnova1 "; break;
		case 0x09a: stream << "jova1 "; break;
		case 0x09c: stream << "jnovb1 "; break;
		case 0x09e: stream << "jovb1 "; break;
		case 0x0a0: stream << "jnsa0 "; break;
		case 0x0a2: stream << "jsa0 "; break;
		case 0x0a4: stream << "jnsb0 "; break;
		case 0x0a6: stream << "jsb0 "; break;
		case 0x0a8: stream << "jnsa1 "; break;
		case 0x0aa: stream << "jsa1 "; break;
		case 0x0ac: stream << "jnsb1 "; break;
		case 0x0ae: stream << "jsb1 "; break;
		case 0x0b0: stream << "jdpl0 "; break;
		case 0x0b1: stream << "jdpln0 "; break;
		case 0x0b2: stream << "jdplf "; break;
		case 0x0b3: stream << "jdplnf "; break;
		case 0x0b4: stream << "jnsiak "; break;
		case 0x0b6: stream << "jsiak "; break;
		case 0x0b8: stream << "jnsoak "; break;
		case 0x0ba: stream << "jsoak "; break;
		case 0x0bc: stream << "jnrqm "; break;
		case 0x0be: stream << "jrqm "; break;
		case 0x100: stream << "ljmp "; break;
		case 0x101: stream << "hjmp "; break;
		case 0x140: stream << "lcall "; break;
		case 0x141: stream << "hcall "; break;
		default:    stream << "??????  "; break;
	}

	util::stream_format(stream, "$%x", na);
	}

	if(type == 3) {  //LD
	stream << "ld ";
	uint16_t id = opcode >> 6;
	uint8_t dst = (opcode >> 0) & 0xf;  //destination

	util::stream_format(stream, "$%x,", id);

	switch(dst) {
		case  0: stream << "non"; break;
		case  1: stream << "a"; break;
		case  2: stream << "b"; break;
		case  3: stream << "tr"; break;
		case  4: stream << "dp"; break;
		case  5: stream << "rp"; break;
		case  6: stream << "dr"; break;
		case  7: stream << "sr"; break;
		case  8: stream << "sol"; break;
		case  9: stream << "som"; break;
		case 10: stream << "k"; break;
		case 11: stream << "klr"; break;
		case 12: stream << "klm"; break;
		case 13: stream << "l"; break;
		case 14: stream << "trb"; break;
		case 15: stream << "mem"; break;
	}
	}

>>>>>>> upstream/master
	return 1 | DASMFLAG_SUPPORTED;
}
