// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/*** m6809: Portable 6809 emulator ******************************************

    Copyright John Butler

    References:

        6809 Simulator V09, By L.C. Benschop, Eindhoven The Netherlands.

        m6809: Portable 6809 emulator, DS (6809 code in MAME, derived from
            the 6809 Simulator V09)

        6809 Microcomputer Programming & Interfacing with Experiments"
            by Andrew C. Staugaard, Jr.; Howard W. Sams & Co., Inc.

<<<<<<< HEAD
    System dependencies:    UINT16 must be 16 bit unsigned int
                            UINT8 must be 8 bit unsigned int
                            UINT32 must be more than 16 bits
=======
    System dependencies:    uint16_t must be 16 bit unsigned int
                            uint8_t must be 8 bit unsigned int
                            uint32_t must be more than 16 bits
>>>>>>> upstream/master
                            arrays up to 65536 bytes must be supported
                            machine must be twos complement

    History:

<<<<<<< HEAD
=======
July 2016 ErikGav:
    Unify with 6309 pairs and quads (A+B=D, E+F=W, D+W=Q)

>>>>>>> upstream/master
March 2013 NPW:
    Rewrite of 6809/6309/Konami CPU; attempted to make cycle exact.

991026 HJB:
    Fixed missing calls to cpu_changepc() for the TFR and EXG ocpodes.
    Replaced m6809_slapstic checks by a macro (CHANGE_PC). ESB still
    needs the tweaks.

991024 HJB:
    Tried to improve speed: Using bit7 of cycles1/2 as flag for multi
    byte opcodes is gone, those opcodes now call fetch_effective_address().
    Got rid of the slow/fast flags for stack (S and U) memory accesses.
    Minor changes to use 32 bit values as arguments to memory functions
    and added defines for that purpose (e.g. X = 16bit XD = 32bit).

990312 HJB:
    Added bugfixes according to Aaron's findings.
    Reset only sets CC_II and CC_IF, DP to zero and PC from reset vector.
990311 HJB:
    Added _info functions. Now uses static m6808_Regs struct instead
    of single statics. Changed the 16 bit registers to use the generic
    PAIR union. Registers defined using macros. Split the core into
    four execution loops for M6802, M6803, M6808 and HD63701.
    TST, TSTA and TSTB opcodes reset carry flag.
    Modified the read/write stack handlers to push LSB first then MSB
    and pull MSB first then LSB.

990228 HJB:
    Changed the interrupt handling again. Now interrupts are taken
    either right at the moment the lines are asserted or whenever
    an interrupt is enabled and the corresponding line is still
    asserted. That way the pending_interrupts checks are not
    needed anymore. However, the CWAI and SYNC flags still need
    some flags, so I changed the name to 'int_state'.
    This core also has the code for the old interrupt system removed.

990225 HJB:
    Cleaned up the code here and there, added some comments.
    Slightly changed the SAR opcodes (similiar to other CPU cores).
    Added symbolic names for the flag bits.
    Changed the way CWAI/Interrupt() handle CPU state saving.
    A new flag M6809_STATE in pending_interrupts is used to determine
    if a state save is needed on interrupt entry or already done by CWAI.
    Added M6809_IRQ_LINE and M6809_FIRQ_LINE defines to m6809.h
    Moved the internal interrupt_pending flags from m6809.h to m6809.c
    Changed CWAI cycles2[0x3c] to be 2 (plus all or at least 19 if
    CWAI actually pushes the entire state).
    Implemented undocumented TFR/EXG for undefined source and mixed 8/16
    bit transfers (they should transfer/exchange the constant $ff).
    Removed unused jmp/jsr _slap functions from 6809ops.c,
    m6809_slapstick check moved into the opcode functions.

*****************************************************************************/

#include "emu.h"
#include "debugger.h"
#include "m6809.h"
#include "m6809inl.h"


//**************************************************************************
//  PARAMETERS
//**************************************************************************

#define LOG_INTERRUPTS  0

// turn off 'unreferenced label' errors
<<<<<<< HEAD
// this pragma doesn't work on older GCCs, so cut off at 4.2
#if defined(__GNUC__) && __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)
=======
#if defined(__GNUC__)
>>>>>>> upstream/master
#pragma GCC diagnostic ignored "-Wunused-label"
#endif
#ifdef _MSC_VER
#pragma warning( disable : 4102 )
#endif

//**************************************************************************
//  DEVICE INTERFACE
//**************************************************************************

<<<<<<< HEAD
const device_type M6809 = &device_creator<m6809_device>;
const device_type M6809E = &device_creator<m6809e_device>;
=======
DEFINE_DEVICE_TYPE(M6809, m6809_device, "m6809", "M6809")
DEFINE_DEVICE_TYPE(M6809E, m6809e_device, "m6809e", "M6809E")
>>>>>>> upstream/master


//-------------------------------------------------
//  m6809_base_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
m6809_base_device::m6809_base_device(const machine_config &mconfig, const char *name, const char *tag, device_t *owner, UINT32 clock, const device_type type, int divider, const char *shortname, const char *source)
	: cpu_device(mconfig, type, name, tag, owner, clock, shortname, source),
=======
m6809_base_device::m6809_base_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock, const device_type type, int divider)
	: cpu_device(mconfig, type, tag, owner, clock),
>>>>>>> upstream/master
	m_lic_func(*this),
	m_program_config("program", ENDIANNESS_BIG, 8, 16),
	m_sprogram_config("decrypted_opcodes", ENDIANNESS_BIG, 8, 16),
	m_clock_divider(divider)
{
<<<<<<< HEAD
	m_mintf = NULL;
}


=======
	m_mintf = nullptr;
}

>>>>>>> upstream/master
//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void m6809_base_device::device_start()
{
	if (!m_mintf)
		m_mintf = new mi_default;

	m_mintf->m_program  = &space(AS_PROGRAM);
<<<<<<< HEAD
	m_mintf->m_sprogram = has_space(AS_DECRYPTED_OPCODES) ? &space(AS_DECRYPTED_OPCODES) : m_mintf->m_program;
=======
	m_mintf->m_sprogram = has_space(AS_OPCODES) ? &space(AS_OPCODES) : m_mintf->m_program;
>>>>>>> upstream/master

	m_mintf->m_direct  = &m_mintf->m_program->direct();
	m_mintf->m_sdirect = &m_mintf->m_sprogram->direct();

	m_lic_func.resolve_safe();

	// register our state for the debugger
<<<<<<< HEAD
	state_add(STATE_GENPC,     "GENPC",     m_pc.w).noshow();
	state_add(STATE_GENPCBASE, "GENPCBASE", m_ppc.w).noshow();
	state_add(STATE_GENFLAGS,  "GENFLAGS",  m_cc).callimport().callexport().formatstr("%8s").noshow();
	state_add(M6809_PC,        "PC",        m_pc.w).mask(0xffff);
	state_add(M6809_S,         "S",         m_s.w).mask(0xffff);
	state_add(M6809_CC,        "CC",        m_cc).mask(0xff);
	state_add(M6809_U,         "U",         m_u.w).mask(0xffff);
	state_add(M6809_A,         "A",         m_d.b.h).mask(0xff);
	state_add(M6809_B,         "B",         m_d.b.l).mask(0xff);
	state_add(M6809_X,         "X",         m_x.w).mask(0xffff);
	state_add(M6809_Y,         "Y",         m_y.w).mask(0xffff);
	state_add(M6809_DP,        "DP",        m_dp).mask(0xff);

=======
	state_add(STATE_GENPCBASE, "CURPC",     m_ppc.w).callimport().noshow();
	state_add(STATE_GENFLAGS,  "CURFLAGS",  m_cc).formatstr("%8s").noshow();
	state_add(M6809_PC,        "PC",        m_pc.w).callimport().mask(0xffff);
	state_add(M6809_S,         "S",         m_s.w).mask(0xffff);
	state_add(M6809_CC,        "CC",        m_cc).mask(0xff);
	state_add(M6809_DP,        "DP",        m_dp).mask(0xff);

	if (is_6809())
	{
		state_add(M6809_A,     "A",         m_q.r.a).mask(0xff);
		state_add(M6809_B,     "B",         m_q.r.b).mask(0xff);
		state_add(M6809_D,     "D",         m_q.r.d).mask(0xffff);
		state_add(M6809_X,     "X",         m_x.w).mask(0xffff);
		state_add(M6809_Y,     "Y",         m_y.w).mask(0xffff);
		state_add(M6809_U,     "U",         m_u.w).mask(0xffff);
	}

>>>>>>> upstream/master
	// initialize variables
	m_cc = 0;
	m_pc.w = 0;
	m_s.w = 0;
	m_u.w = 0;
<<<<<<< HEAD
	m_d.w = 0;
=======
	m_q.q = 0;
>>>>>>> upstream/master
	m_x.w = 0;
	m_y.w = 0;
	m_dp = 0;
	m_reg = 0;
<<<<<<< HEAD
	m_reg8 = NULL;
	m_reg16 = NULL;
=======
	m_reg8 = nullptr;
	m_reg16 = nullptr;
>>>>>>> upstream/master

	// setup regtable
	save_item(NAME(m_pc.w));
	save_item(NAME(m_ppc.w));
<<<<<<< HEAD
	save_item(NAME(m_d.w));
=======
	save_item(NAME(m_q.q));
>>>>>>> upstream/master
	save_item(NAME(m_dp));
	save_item(NAME(m_u.w));
	save_item(NAME(m_s.w));
	save_item(NAME(m_x.w));
	save_item(NAME(m_y.w));
	save_item(NAME(m_cc));
	save_item(NAME(m_temp.w));
	save_item(NAME(m_opcode));
	save_item(NAME(m_nmi_asserted));
	save_item(NAME(m_nmi_line));
	save_item(NAME(m_firq_line));
	save_item(NAME(m_irq_line));
	save_item(NAME(m_lds_encountered));
	save_item(NAME(m_state));
	save_item(NAME(m_ea.w));
	save_item(NAME(m_addressing_mode));
	save_item(NAME(m_reg));
	save_item(NAME(m_cond));

	// set our instruction counter
	m_icountptr = &m_icount;
	m_icount = 0;
}



//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void m6809_base_device::device_reset()
{
	m_nmi_line = false;
	m_nmi_asserted = false;
	m_firq_line = false;
	m_irq_line = false;
	m_lds_encountered = false;

	m_dp = 0x00;        // reset direct page register

	m_cc |= CC_I;       // IRQ disabled
	m_cc |= CC_F;       // FIRQ disabled

<<<<<<< HEAD
	m_pc.b.h = m_addrspace[AS_PROGRAM]->read_byte(VECTOR_RESET_FFFE + 0);
	m_pc.b.l = m_addrspace[AS_PROGRAM]->read_byte(VECTOR_RESET_FFFE + 1);
=======
	m_pc.b.h = space(AS_PROGRAM).read_byte(VECTOR_RESET_FFFE + 0);
	m_pc.b.l = space(AS_PROGRAM).read_byte(VECTOR_RESET_FFFE + 1);
>>>>>>> upstream/master

	// reset sub-instruction state
	reset_state();
}



//-------------------------------------------------
//  device_pre_save - device-specific pre-save
//-------------------------------------------------

void m6809_base_device::device_pre_save()
{
<<<<<<< HEAD
	if (m_reg8 == &m_d.b.h)
		m_reg = M6809_A;
	else if (m_reg8 == &m_d.b.l)
		m_reg = M6809_B;
	else if (m_reg16 == &m_d)
=======
	if (m_reg8 == &m_q.r.a)
		m_reg = M6809_A;
	else if (m_reg8 == &m_q.r.b)
		m_reg = M6809_B;
	else if (m_reg16 == &m_q.p.d)
>>>>>>> upstream/master
		m_reg = M6809_D;
	else if (m_reg16 == &m_x)
		m_reg = M6809_X;
	else if (m_reg16 == &m_y)
		m_reg = M6809_Y;
	else if (m_reg16 == &m_u)
		m_reg = M6809_U;
	else if (m_reg16 == &m_s)
		m_reg = M6809_S;
	else
		m_reg = 0;
}


//-------------------------------------------------
//  device_post_load - device-specific post-load
//-------------------------------------------------

void m6809_base_device::device_post_load()
{
<<<<<<< HEAD
	m_reg8 = NULL;
	m_reg16 = NULL;
=======
	m_reg8 = nullptr;
	m_reg16 = nullptr;
>>>>>>> upstream/master

	switch(m_reg)
	{
		case M6809_A:
<<<<<<< HEAD
			set_regop8(m_d.b.h);
			break;
		case M6809_B:
			set_regop8(m_d.b.l);
			break;
		case M6809_D:
			set_regop16(m_d);
=======
			set_regop8(m_q.r.a);
			break;
		case M6809_B:
			set_regop8(m_q.r.b);
			break;
		case M6809_D:
			set_regop16(m_q.p.d);
>>>>>>> upstream/master
			break;
		case M6809_X:
			set_regop16(m_x);
			break;
		case M6809_Y:
			set_regop16(m_y);
			break;
		case M6809_U:
			set_regop16(m_u);
			break;
		case M6809_S:
			set_regop16(m_s);
			break;
	}
}


//-------------------------------------------------
//  memory_space_config - return the configuration
<<<<<<< HEAD
//  of the specified address space, or NULL if
//  the space doesn't exist
//-------------------------------------------------

const address_space_config *m6809_base_device::memory_space_config(address_spacenum spacenum) const
{
	switch(spacenum)
	{
	case AS_PROGRAM:           return &m_program_config;
	case AS_DECRYPTED_OPCODES: return has_configured_map(AS_DECRYPTED_OPCODES) ? &m_sprogram_config : NULL;
	default:                   return NULL;
	}
}


=======
//  of the specified address space, or nullptr if
//  the space doesn't exist
//-------------------------------------------------

device_memory_interface::space_config_vector m6809_base_device::memory_space_config() const
{
	if(has_configured_map(AS_OPCODES))
		return space_config_vector {
			std::make_pair(AS_PROGRAM, &m_program_config),
			std::make_pair(AS_OPCODES, &m_sprogram_config)
		};
	else
		return space_config_vector {
			std::make_pair(AS_PROGRAM, &m_program_config)
		};
}


//-------------------------------------------------
//  state_import - import state into the device,
//  after it has been set
//-------------------------------------------------

void m6809_base_device::state_import(const device_state_entry &entry)
{
	switch (entry.index())
	{
	case M6809_PC:
		m_ppc.w = m_pc.w;
		break;

	case STATE_GENPCBASE:
		m_pc.w = m_ppc.w;
		break;
	}
}

>>>>>>> upstream/master
//-------------------------------------------------
//  state_string_export - export state as a string
//  for the debugger
//-------------------------------------------------

<<<<<<< HEAD
void m6809_base_device::state_string_export(const device_state_entry &entry, std::string &str)
=======
void m6809_base_device::state_string_export(const device_state_entry &entry, std::string &str) const
>>>>>>> upstream/master
{
	switch (entry.index())
	{
		case STATE_GENFLAGS:
<<<<<<< HEAD
			strprintf(str, "%c%c%c%c%c%c%c%c",
=======
			str = string_format("%c%c%c%c%c%c%c%c",
>>>>>>> upstream/master
				(m_cc & 0x80) ? 'E' : '.',
				(m_cc & 0x40) ? 'F' : '.',
				(m_cc & 0x20) ? 'H' : '.',
				(m_cc & 0x10) ? 'I' : '.',
				(m_cc & 0x08) ? 'N' : '.',
				(m_cc & 0x04) ? 'Z' : '.',
				(m_cc & 0x02) ? 'V' : '.',
				(m_cc & 0x01) ? 'C' : '.');
			break;
	}
}


//-------------------------------------------------
//  disasm_min_opcode_bytes - return the length
//  of the shortest instruction, in bytes
//-------------------------------------------------

<<<<<<< HEAD
UINT32 m6809_base_device::disasm_min_opcode_bytes() const
=======
uint32_t m6809_base_device::disasm_min_opcode_bytes() const
>>>>>>> upstream/master
{
	return 1;
}


//-------------------------------------------------
//  disasm_max_opcode_bytes - return the length
//  of the longest instruction, in bytes
//-------------------------------------------------

<<<<<<< HEAD
UINT32 m6809_base_device::disasm_max_opcode_bytes() const
=======
uint32_t m6809_base_device::disasm_max_opcode_bytes() const
>>>>>>> upstream/master
{
	return 5;
}


//-------------------------------------------------
//  disasm_disassemble - call the disassembly
//  helper function
//-------------------------------------------------

<<<<<<< HEAD
offs_t m6809_base_device::disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options)
{
	extern CPU_DISASSEMBLE( m6809 );
	return CPU_DISASSEMBLE_NAME(m6809)(this, buffer, pc, oprom, opram, options);
=======
offs_t m6809_base_device::disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options)
{
	extern CPU_DISASSEMBLE( m6809 );
	return CPU_DISASSEMBLE_NAME(m6809)(this, stream, pc, oprom, opram, options);
>>>>>>> upstream/master
}


//**************************************************************************
//  CORE EXECUTION LOOP
//**************************************************************************

//-------------------------------------------------
//  execute_clocks_to_cycles - convert the raw
//  clock into cycles per second
//-------------------------------------------------

<<<<<<< HEAD
UINT64 m6809_base_device::execute_clocks_to_cycles(UINT64 clocks) const
=======
uint64_t m6809_base_device::execute_clocks_to_cycles(uint64_t clocks) const
>>>>>>> upstream/master
{
	return (clocks + m_clock_divider - 1) / m_clock_divider;
}


//-------------------------------------------------
//  execute_cycles_to_clocks - convert a cycle
//  count back to raw clocks
//-------------------------------------------------

<<<<<<< HEAD
UINT64 m6809_base_device::execute_cycles_to_clocks(UINT64 cycles) const
=======
uint64_t m6809_base_device::execute_cycles_to_clocks(uint64_t cycles) const
>>>>>>> upstream/master
{
	return cycles * m_clock_divider;
}


//-------------------------------------------------
//  execute_min_cycles - return minimum number of
//  cycles it takes for one instruction to execute
//-------------------------------------------------

<<<<<<< HEAD
UINT32 m6809_base_device::execute_min_cycles() const
=======
uint32_t m6809_base_device::execute_min_cycles() const
>>>>>>> upstream/master
{
	return 1;
}


//-------------------------------------------------
//  execute_max_cycles - return maximum number of
//  cycles it takes for one instruction to execute
//-------------------------------------------------

<<<<<<< HEAD
UINT32 m6809_base_device::execute_max_cycles() const
=======
uint32_t m6809_base_device::execute_max_cycles() const
>>>>>>> upstream/master
{
	return 19;
}


//-------------------------------------------------
//  execute_input_lines - return the number of
//  input/interrupt lines
//-------------------------------------------------

<<<<<<< HEAD
UINT32 m6809_base_device::execute_input_lines() const
=======
uint32_t m6809_base_device::execute_input_lines() const
>>>>>>> upstream/master
{
	return 3;
}


//-------------------------------------------------
//  execute_set_input - act on a changed input/
//  interrupt line
//-------------------------------------------------

void m6809_base_device::execute_set_input(int inputnum, int state)
{
	if (LOG_INTERRUPTS)
		logerror("%s: inputnum=%s state=%d totalcycles=%d\n", machine().describe_context(), inputnum_string(inputnum), state, (int) attotime_to_clocks(machine().time()));

	switch(inputnum)
	{
		case INPUT_LINE_NMI:
			// NMI is edge triggered
			m_nmi_asserted = m_nmi_asserted || ((state != CLEAR_LINE) && !m_nmi_line && m_lds_encountered);
			m_nmi_line = (state != CLEAR_LINE);
			break;

		case M6809_FIRQ_LINE:
			// FIRQ is line triggered
			m_firq_line = (state != CLEAR_LINE);
			break;

		case M6809_IRQ_LINE:
			// IRQ is line triggered
			m_irq_line = (state != CLEAR_LINE);
			break;
	}
}


//-------------------------------------------------
//  inputnum_string
//-------------------------------------------------

const char *m6809_base_device::inputnum_string(int inputnum)
{
	switch(inputnum)
	{
		case INPUT_LINE_NMI:    return "NMI";
		case M6809_FIRQ_LINE:   return "FIRQ";
		case M6809_IRQ_LINE:    return "IRQ";
		default:                return "???";
	}
}


//-------------------------------------------------
//  read_exgtfr_register
//-------------------------------------------------

<<<<<<< HEAD
m6809_base_device::exgtfr_register m6809_base_device::read_exgtfr_register(UINT8 reg)
=======
m6809_base_device::exgtfr_register m6809_base_device::read_exgtfr_register(uint8_t reg)
>>>>>>> upstream/master
{
	exgtfr_register result;
	result.byte_value = 0xFF;
	result.word_value = 0x00FF;

	switch(reg & 0x0F)
	{
<<<<<<< HEAD
		case  0: result.word_value = m_d.w;     break;  // D
=======
		case  0: result.word_value = m_q.r.d;   break;  // D
>>>>>>> upstream/master
		case  1: result.word_value = m_x.w;     break;  // X
		case  2: result.word_value = m_y.w;     break;  // Y
		case  3: result.word_value = m_u.w;     break;  // U
		case  4: result.word_value = m_s.w;     break;  // S
		case  5: result.word_value = m_pc.w;    break;  // PC
<<<<<<< HEAD
		case  8: result.byte_value = m_d.b.h;   break;  // A
		case  9: result.byte_value = m_d.b.l;   break;  // B
=======
		case  8: result.byte_value = m_q.r.a;   break;  // A
		case  9: result.byte_value = m_q.r.b;   break;  // B
>>>>>>> upstream/master
		case 10: result.byte_value = m_cc;      break;  // CC
		case 11: result.byte_value = m_dp;      break;  // DP
	}
	return result;
}


//-------------------------------------------------
//  write_exgtfr_register
//-------------------------------------------------

<<<<<<< HEAD
void m6809_base_device::write_exgtfr_register(UINT8 reg, m6809_base_device::exgtfr_register value)
{
	switch(reg & 0x0F)
	{
		case  0: m_d.w   = value.word_value;    break;  // D
=======
void m6809_base_device::write_exgtfr_register(uint8_t reg, m6809_base_device::exgtfr_register value)
{
	switch(reg & 0x0F)
	{
		case  0: m_q.r.d = value.word_value;    break;  // D
>>>>>>> upstream/master
		case  1: m_x.w   = value.word_value;    break;  // X
		case  2: m_y.w   = value.word_value;    break;  // Y
		case  3: m_u.w   = value.word_value;    break;  // U
		case  4: m_s.w   = value.word_value;    break;  // S
		case  5: m_pc.w  = value.word_value;    break;  // PC
<<<<<<< HEAD
		case  8: m_d.b.h = value.byte_value;    break;  // A
		case  9: m_d.b.l = value.byte_value;    break;  // B
=======
		case  8: m_q.r.a = value.byte_value;    break;  // A
		case  9: m_q.r.b = value.byte_value;    break;  // B
>>>>>>> upstream/master
		case 10: m_cc    = value.byte_value;    break;  // CC
		case 11: m_dp    = value.byte_value;    break;  // DP
	}
}


//-------------------------------------------------
//  log_illegal - used to log hits to illegal
//  instructions (except for HD6309 which traps)
//-------------------------------------------------

void m6809_base_device::log_illegal()
{
	logerror("%s: illegal opcode at %04x\n", machine().describe_context(), (unsigned) m_pc.w);
}


//-------------------------------------------------
//  execute_one - try to execute a single instruction
//-------------------------------------------------

void m6809_base_device::execute_one()
{
	switch(pop_state())
	{
<<<<<<< HEAD
#include "cpu/m6809/m6809.inc"
=======
#include "cpu/m6809/m6809.hxx"
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  execute_run - execute a timeslice's worth of
//  opcodes
//-------------------------------------------------

void m6809_base_device::execute_run()
{
	do
	{
		execute_one();
	} while(m_icount > 0);
}


<<<<<<< HEAD
UINT8 m6809_base_device::mi_default::read(UINT16 adr)
=======
uint8_t m6809_base_device::mi_default::read(uint16_t adr)
>>>>>>> upstream/master
{
	return m_program->read_byte(adr);
}

<<<<<<< HEAD
UINT8 m6809_base_device::mi_default::read_opcode(UINT16 adr)
=======
uint8_t m6809_base_device::mi_default::read_opcode(uint16_t adr)
>>>>>>> upstream/master
{
	return m_sdirect->read_byte(adr);
}

<<<<<<< HEAD
UINT8 m6809_base_device::mi_default::read_opcode_arg(UINT16 adr)
=======
uint8_t m6809_base_device::mi_default::read_opcode_arg(uint16_t adr)
>>>>>>> upstream/master
{
	return m_direct->read_byte(adr);
}


<<<<<<< HEAD
void m6809_base_device::mi_default::write(UINT16 adr, UINT8 val)
=======
void m6809_base_device::mi_default::write(uint16_t adr, uint8_t val)
>>>>>>> upstream/master
{
	m_program->write_byte(adr, val);
}



//-------------------------------------------------
//  m6809_device
//-------------------------------------------------

<<<<<<< HEAD
m6809_device::m6809_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: m6809_base_device(mconfig, "M6809", tag, owner, clock, M6809, 1, "m6809", __FILE__)
=======
m6809_device::m6809_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: m6809_base_device(mconfig, tag, owner, clock, M6809, 1)
>>>>>>> upstream/master
{
}



//-------------------------------------------------
//  m6809e_device
//-------------------------------------------------

<<<<<<< HEAD
m6809e_device::m6809e_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: m6809_base_device(mconfig, "M6809E", tag, owner, clock, M6809E, 4, "m6809e", __FILE__)
{
}

WRITE_LINE_MEMBER( m6809_base_device::irq_line )
{
	set_input_line( M6809_IRQ_LINE, state );
}

WRITE_LINE_MEMBER( m6809_base_device::firq_line )
{
	set_input_line( M6809_FIRQ_LINE, state );
}

WRITE_LINE_MEMBER( m6809_base_device::nmi_line )
{
	set_input_line( INPUT_LINE_NMI, state );
=======
m6809e_device::m6809e_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
		: m6809_base_device(mconfig, tag, owner, clock, M6809E, 4)
{
>>>>>>> upstream/master
}
