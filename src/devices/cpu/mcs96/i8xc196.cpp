// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/***************************************************************************

    i8xc196.h

    MCS96, c196 branch, the enhanced 16 bits bus version

***************************************************************************/

#include "emu.h"
#include "i8xc196.h"

<<<<<<< HEAD
i8xc196_device::i8xc196_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source) :
	mcs96_device(mconfig, type, name, tag, owner, clock, 16, shortname, source)
{
}

offs_t i8xc196_device::disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options)
{
	return disasm_generic(buffer, pc, oprom, opram, options, disasm_entries);
}

void i8xc196_device::io_w8(UINT8 adr, UINT8 data)
=======
i8xc196_device::i8xc196_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock) :
	mcs96_device(mconfig, type, tag, owner, clock, 16)
{
}

offs_t i8xc196_device::disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options)
{
	return disasm_generic(stream, pc, oprom, opram, options, disasm_entries);
}

void i8xc196_device::io_w8(uint8_t adr, uint8_t data)
>>>>>>> upstream/master
{
	switch(adr) {
	case 0:
		break;
	case 1:
		break;
	default:
		logerror("%s: io_w8 %02x, %02x (%04x)\n", tag(), adr, data, PPC);
	}
	return;
}

<<<<<<< HEAD
void i8xc196_device::io_w16(UINT8 adr, UINT16 data)
=======
void i8xc196_device::io_w16(uint8_t adr, uint16_t data)
>>>>>>> upstream/master
{
	switch(adr) {
	case 0:
		break;
	default:
		io_w8(adr, data);
		io_w8(adr+1, data>>8);
		break;
	}
	return;
}

<<<<<<< HEAD
UINT8 i8xc196_device::io_r8(UINT8 adr)
=======
uint8_t i8xc196_device::io_r8(uint8_t adr)
>>>>>>> upstream/master
{
	switch(adr) {
	case 0x00:
		return 0x00;
	case 0x01:
		return 0x00;
	}
<<<<<<< HEAD
	UINT8 data = 0x00;
=======
	uint8_t data = 0x00;
>>>>>>> upstream/master
	logerror("%s: io_r8 %02x, %02x (%04x)\n", tag(), adr, data, PPC);
	return data;
}

<<<<<<< HEAD
UINT16 i8xc196_device::io_r16(UINT8 adr)
{
	if(adr < 2)
		return 0x0000;
	UINT16 data = 0x0000;
=======
uint16_t i8xc196_device::io_r16(uint8_t adr)
{
	if(adr < 2)
		return 0x0000;
	uint16_t data = 0x0000;
>>>>>>> upstream/master
	logerror("%s: io_r16 %02x, %04x (%04x)\n", tag(), adr, data, PPC);
	return data;
}

void i8xc196_device::do_exec_partial()
{
}

<<<<<<< HEAD
#include "cpu/mcs96/i8xc196.inc"
=======
#include "cpu/mcs96/i8xc196.hxx"
>>>>>>> upstream/master
