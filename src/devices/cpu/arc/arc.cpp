// license:BSD-3-Clause
// copyright-holders:David Haywood
/*********************************\

 ARCtangent (A4) core
 ARC == Argonaut RISC Core

 (this is a skeleton core)

\*********************************/

#include "emu.h"
#include "debugger.h"
#include "arc.h"


<<<<<<< HEAD
const device_type ARC = &device_creator<arc_device>;


arc_device::arc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: cpu_device(mconfig, ARC, "ARCtangent A4", tag, owner, clock, "arc", __FILE__)
	, m_program_config("program", ENDIANNESS_BIG, 32, 24, 0), m_pc(0), m_program(nullptr), m_icount(0), m_debugger_temp(0)
=======
DEFINE_DEVICE_TYPE(ARC, arc_cpu_device, "arc_a4", "ARCtangent A4")


arc_cpu_device::arc_cpu_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: cpu_device(mconfig, ARC, tag, owner, clock)
	, m_program_config("program", ENDIANNESS_BIG, 32, 24, 0)
	, m_pc(0), m_program(nullptr), m_icount(0), m_debugger_temp(0)
>>>>>>> upstream/master
// some docs describe these as 'middle endian'?!
{
}


<<<<<<< HEAD
offs_t arc_device::disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options)
{
	extern CPU_DISASSEMBLE( arc );
	return CPU_DISASSEMBLE_NAME(arc)(this, buffer, pc, oprom, opram, options);
=======
offs_t arc_cpu_device::disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options)
{
	extern CPU_DISASSEMBLE( arc );
	return CPU_DISASSEMBLE_NAME(arc)(this, stream, pc, oprom, opram, options);
>>>>>>> upstream/master
}


/*****************************************************************************/

/*****************************************************************************/

<<<<<<< HEAD
void arc_device::unimplemented_opcode(UINT16 op)
=======
void arc_cpu_device::unimplemented_opcode(uint16_t op)
>>>>>>> upstream/master
{
	fatalerror("arc: unknown opcode %04x at %04x\n", op, m_pc << 2);
}

/*****************************************************************************/

<<<<<<< HEAD
UINT32 arc_device::READ32(UINT32 address)
=======
uint32_t arc_cpu_device::READ32(uint32_t address)
>>>>>>> upstream/master
{
	return m_program->read_dword(address << 2);
}

<<<<<<< HEAD
void arc_device::WRITE32(UINT32 address, UINT32 data)
=======
void arc_cpu_device::WRITE32(uint32_t address, uint32_t data)
>>>>>>> upstream/master
{
	m_program->write_dword(address << 2, data);
}

/*****************************************************************************/

<<<<<<< HEAD
void arc_device::device_start()
=======
void arc_cpu_device::device_start()
>>>>>>> upstream/master
{
	m_pc = 0;

	m_debugger_temp = 0;

	m_program = &space(AS_PROGRAM);

<<<<<<< HEAD
	state_add( 0,  "PC", m_debugger_temp).callimport().callexport().formatstr("%08X");
	state_add(STATE_GENPC, "GENPC", m_debugger_temp).callexport().noshow();
=======
	state_add(ARC_PC,  "PC", m_debugger_temp).callimport().callexport().formatstr("%08X");
	state_add(STATE_GENPCBASE, "CURPC", m_debugger_temp).callimport().callexport().noshow();
>>>>>>> upstream/master

	m_icountptr = &m_icount;
}

<<<<<<< HEAD
void arc_device::state_export(const device_state_entry &entry)
{
	switch (entry.index())
	{
		case 0:
			m_debugger_temp = m_pc << 2;
			break;

		case STATE_GENPC:
=======

//-------------------------------------------------
//  state_export - export state from the device,
//  to a known location where it can be read
//-------------------------------------------------

void arc_cpu_device::state_export(const device_state_entry &entry)
{
	switch (entry.index())
	{
		case ARC_PC:
		case STATE_GENPCBASE:
>>>>>>> upstream/master
			m_debugger_temp = m_pc << 2;
			break;
	}
}

<<<<<<< HEAD
void arc_device::state_import(const device_state_entry &entry)
{
	switch (entry.index())
	{
		case 0:
=======

//-------------------------------------------------
//  state_import - import state into the device,
//  after it has been set
//-------------------------------------------------

void arc_cpu_device::state_import(const device_state_entry &entry)
{
	switch (entry.index())
	{
		case ARC_PC:
		case STATE_GENPCBASE:
>>>>>>> upstream/master
			m_pc = (m_debugger_temp & 0xfffffffc) >> 2;
			break;
	}
}

<<<<<<< HEAD
void arc_device::device_reset()
=======
void arc_cpu_device::device_reset()
>>>>>>> upstream/master
{
	m_pc = 0x00000000;
}

/*****************************************************************************/

<<<<<<< HEAD
void arc_device::execute_set_input(int irqline, int state)
=======
void arc_cpu_device::execute_set_input(int irqline, int state)
>>>>>>> upstream/master
{
}


<<<<<<< HEAD
void arc_device::execute_run()
{
	//UINT32 lres;
=======
void arc_cpu_device::execute_run()
{
	//uint32_t lres;
>>>>>>> upstream/master
	//lres = 0;

	while (m_icount > 0)
	{
		debugger_instruction_hook(this, m_pc<<2);

<<<<<<< HEAD
		//UINT32 op = READ32(m_pc);
=======
		//uint32_t op = READ32(m_pc);
>>>>>>> upstream/master

		m_pc++;

		m_icount--;
	}

}
