// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
#include "emu.h"
#include "h8h.h"

<<<<<<< HEAD
h8h_device::h8h_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source, address_map_delegate map_delegate) :
	h8_device(mconfig, type, name, tag, owner, clock, shortname, source, false, map_delegate)
=======
h8h_device::h8h_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, address_map_delegate map_delegate) :
	h8_device(mconfig, type, tag, owner, clock, false, map_delegate)
>>>>>>> upstream/master
{
	supports_advanced = true;
	mode_advanced = true;
}

<<<<<<< HEAD
offs_t h8h_device::disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options)
{
	return disassemble_generic(buffer, pc, oprom, opram, options, disasm_entries);
}

#include "cpu/h8/h8h.inc"
=======
offs_t h8h_device::disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options)
{
	return disassemble_generic(stream, pc, oprom, opram, options, disasm_entries);
}

#include "cpu/h8/h8h.hxx"
>>>>>>> upstream/master
