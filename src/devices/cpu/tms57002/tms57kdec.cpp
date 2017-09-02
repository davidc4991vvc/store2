// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/***************************************************************************

    tms57kdec.c

    TMS57002 "DASP" emulator.

***************************************************************************/

#include "emu.h"
#include "debugger.h"
#include "tms57002.h"

<<<<<<< HEAD
inline int tms57002_device::xmode(UINT32 opcode, char type, cstate *cs)
=======
inline int tms57002_device::xmode(uint32_t opcode, char type, cstate *cs)
>>>>>>> upstream/master
{
	if(((opcode & 0x400) && (type == 'c')) || (!(opcode & 0x400) && (type == 'd'))) {
		if(opcode & 0x100)
			return 0;
		else if(opcode & 0x80)
			cs->inc |= type == 'c' ? INC_CA : INC_ID;

		return 1;
	}
	else if(opcode & 0x200)
		cs->inc |= type == 'c' ? INC_CA : INC_ID;

	return 1;
}

<<<<<<< HEAD
inline int tms57002_device::sfao(UINT32 st1)
=======
inline int tms57002_device::sfao(uint32_t st1)
>>>>>>> upstream/master
{
	return st1 & ST1_SFAO ? 1 : 0;
}

<<<<<<< HEAD
inline int tms57002_device::dbp(UINT32 st1)
=======
inline int tms57002_device::dbp(uint32_t st1)
>>>>>>> upstream/master
{
	return st1 & ST1_DBP ? 1 : 0;
}

<<<<<<< HEAD
inline int tms57002_device::crm(UINT32 st1)
=======
inline int tms57002_device::crm(uint32_t st1)
>>>>>>> upstream/master
{
	int crm = (st1 & ST1_CRM) >> ST1_CRM_SHIFT;
	return crm <= 2 ? crm : 0;
}

<<<<<<< HEAD
inline int tms57002_device::sfai(UINT32 st1)
=======
inline int tms57002_device::sfai(uint32_t st1)
>>>>>>> upstream/master
{
	return st1 & ST1_SFAI ? 1 : 0;
}

<<<<<<< HEAD
inline int tms57002_device::sfmo(UINT32 st1)
=======
inline int tms57002_device::sfmo(uint32_t st1)
>>>>>>> upstream/master
{
	return (st1 & ST1_SFMO) >> ST1_SFMO_SHIFT;
}

<<<<<<< HEAD
inline int tms57002_device::rnd(UINT32 st1)
=======
inline int tms57002_device::rnd(uint32_t st1)
>>>>>>> upstream/master
{
	int rnd = (st1 & ST1_RND) >> ST1_RND_SHIFT;
	return rnd <= 4 ? rnd : 0;
}

<<<<<<< HEAD
inline int tms57002_device::movm(UINT32 st1)
=======
inline int tms57002_device::movm(uint32_t st1)
>>>>>>> upstream/master
{
	return st1 & ST1_MOVM ? 1 : 0;
}

<<<<<<< HEAD
inline int tms57002_device::sfma(UINT32 st1)
=======
inline int tms57002_device::sfma(uint32_t st1)
>>>>>>> upstream/master
{
	return (st1 & ST1_SFMA) >> ST1_SFMA_SHIFT;
}

<<<<<<< HEAD
void tms57002_device::decode_error(UINT32 opcode)
{
	char buf[256];
	UINT8 opr[3];
=======
void tms57002_device::decode_error(uint32_t opcode)
{
	uint8_t opr[3];
>>>>>>> upstream/master
	if(unsupported_inst_warning)
		return;

	unsupported_inst_warning = 1;
	opr[0] = opcode;
	opr[1] = opcode >> 8;
	opr[2] = opcode >> 16;

<<<<<<< HEAD
	disasm_disassemble(buf, pc, opr, opr, 0);
	popmessage("tms57002: %s - Contact Mamedev", buf);
}

void tms57002_device::decode_cat1(UINT32 opcode, unsigned short *op, cstate *cs)
=======
	std::stringstream stream;
	disasm_disassemble(stream, pc, opr, opr, 0);
	popmessage("tms57002: %s - Contact Mamedev", stream.str());
}

void tms57002_device::decode_cat1(uint32_t opcode, unsigned short *op, cstate *cs)
>>>>>>> upstream/master
{
	switch(opcode >> 18) {
	case 0x00: // nop
		break;

#define CDEC1
<<<<<<< HEAD
#include "cpu/tms57002/tms57002.inc"
=======
#include "cpu/tms57002/tms57002.hxx"
>>>>>>> upstream/master
#undef CDEC1

	default:
		decode_error(opcode);
		break;
	}
}

<<<<<<< HEAD
void tms57002_device::decode_cat2_pre(UINT32 opcode, unsigned short *op, cstate *cs)
=======
void tms57002_device::decode_cat2_pre(uint32_t opcode, unsigned short *op, cstate *cs)
>>>>>>> upstream/master
{
	switch((opcode >> 11) & 0x7f) {
	case 0x00: // nop
		break;

#define CDEC2A
<<<<<<< HEAD
#include "cpu/tms57002/tms57002.inc"
=======
#include "cpu/tms57002/tms57002.hxx"
>>>>>>> upstream/master
#undef CDEC2A

	default:
		decode_error(opcode);
		break;
	}
}

<<<<<<< HEAD
void tms57002_device::decode_cat2_post(UINT32 opcode, unsigned short *op, cstate *cs)
=======
void tms57002_device::decode_cat2_post(uint32_t opcode, unsigned short *op, cstate *cs)
>>>>>>> upstream/master
{
	switch((opcode >> 11) & 0x7f) {
	case 0x00: // nop
		break;

#define CDEC2B
<<<<<<< HEAD
#include "cpu/tms57002/tms57002.inc"
=======
#include "cpu/tms57002/tms57002.hxx"
>>>>>>> upstream/master
#undef CDEC2B

	default:
		decode_error(opcode);
		break;
	}
}

<<<<<<< HEAD
void tms57002_device::decode_cat3(UINT32 opcode, unsigned short *op, cstate *cs)
=======
void tms57002_device::decode_cat3(uint32_t opcode, unsigned short *op, cstate *cs)
>>>>>>> upstream/master
{
	switch((opcode >> 11) & 0x7f) {
	case 0x00: // nop
		break;

#define CDEC3
<<<<<<< HEAD
#include "cpu/tms57002/tms57002.inc"
=======
#include "cpu/tms57002/tms57002.hxx"
>>>>>>> upstream/master
#undef CDEC3

	default:
		decode_error(opcode);
		break;
	}
}
