// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/***************************************************************************

    deco16.c

    6502, reverse-engineered DECO variant

***************************************************************************/

#include "emu.h"
#include "deco16.h"

#define DECO16_VERBOSE 1

<<<<<<< HEAD
const device_type DECO16 = &device_creator<deco16_device>;

deco16_device::deco16_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	m6502_device(mconfig, DECO16, "DECO16", tag, owner, clock, "deco16", __FILE__),
	io(NULL),
=======
DEFINE_DEVICE_TYPE(DECO16, deco16_device, "deco16", "DECO16")

deco16_device::deco16_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	m6502_device(mconfig, DECO16, tag, owner, clock),
	io(nullptr),
>>>>>>> upstream/master
	io_config("io", ENDIANNESS_LITTLE, 8, 16)
{
}

<<<<<<< HEAD
offs_t deco16_device::disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options)
{
	return disassemble_generic(buffer, pc, oprom, opram, options, disasm_entries);
=======
offs_t deco16_device::disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options)
{
	return disassemble_generic(stream, pc, oprom, opram, options, disasm_entries);
>>>>>>> upstream/master
}


void deco16_device::device_start()
{
	if(direct_disabled)
		mintf = new mi_default_nd;
	else
		mintf = new mi_default_normal;

	init();

	io = &space(AS_IO);
}

<<<<<<< HEAD
const address_space_config *deco16_device::memory_space_config(address_spacenum spacenum) const
{
	switch(spacenum)
	{
	case AS_PROGRAM:           return &program_config;
	case AS_IO:                return &io_config;
	case AS_DECRYPTED_OPCODES: return has_configured_map(AS_DECRYPTED_OPCODES) ? &sprogram_config : NULL;
	default:                   return NULL;
	}
}

#include "cpu/m6502/deco16.inc"
=======
device_memory_interface::space_config_vector deco16_device::memory_space_config() const
{
	if(has_configured_map(AS_OPCODES))
		return space_config_vector {
			std::make_pair(AS_PROGRAM, &program_config),
			std::make_pair(AS_OPCODES, &sprogram_config),
			std::make_pair(AS_IO,      &io_config)
		};
	else
		return space_config_vector {
			std::make_pair(AS_PROGRAM, &program_config),
			std::make_pair(AS_IO,      &io_config)
		};
}

#include "cpu/m6502/deco16.hxx"
>>>>>>> upstream/master
