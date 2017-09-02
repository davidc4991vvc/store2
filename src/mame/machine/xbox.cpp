// license:BSD-3-Clause
// copyright-holders:Samuele Zannoli

#include "emu.h"
<<<<<<< HEAD
#include "cpu/i386/i386.h"
#include "machine/lpci.h"
#include "machine/pic8259.h"
#include "machine/pit8253.h"
#include "machine/idectrl.h"
#include "machine/idehd.h"
#include "video/poly.h"
#include "bitmap.h"
#include "debug/debugcon.h"
#include "debug/debugcmd.h"
#include "debug/debugcpu.h"
#include "includes/chihiro.h"
#include "includes/xbox.h"

#define LOG_PCI
//#define LOG_OHCI
//#define USB_ENABLED

static void dump_string_command(running_machine &machine, int ref, int params, const char **param)
{
	xbox_base_state *state = machine.driver_data<xbox_base_state>();
	address_space &space = state->m_maincpu->space();
	UINT64  addr;
	offs_t address;
	UINT32 length, maximumlength;
	offs_t buffer;

	if (params < 1)
		return;
	if (!debug_command_parameter_number(machine, param[0], &addr))
		return;
	address = (offs_t)addr;
	if (!debug_cpu_translate(space, TRANSLATE_READ_DEBUG, &address))
	{
		debug_console_printf(machine, "Address is unmapped.\n");
		return;
	}
	length = space.read_word_unaligned(address);
	maximumlength = space.read_word_unaligned(address + 2);
	buffer = space.read_dword_unaligned(address + 4);
	debug_console_printf(machine, "Length %d word\n", length);
	debug_console_printf(machine, "MaximumLength %d word\n", maximumlength);
	debug_console_printf(machine, "Buffer %08X byte* ", buffer);
	if (!debug_cpu_translate(space, TRANSLATE_READ_DEBUG, &buffer))
	{
		debug_console_printf(machine, "\nBuffer is unmapped.\n");
		return;
	}
	if (length > 256)
		length = 256;
	for (int a = 0; a < length; a++)
	{
		UINT8 c = space.read_byte(buffer + a);
		debug_console_printf(machine, "%c", c);
	}
	debug_console_printf(machine, "\n");
}

static void dump_process_command(running_machine &machine, int ref, int params, const char **param)
{
	xbox_base_state *state = machine.driver_data<xbox_base_state>();
	address_space &space = state->m_maincpu->space();
	UINT64 addr;
	offs_t address;

	if (params < 1)
		return;
	if (!debug_command_parameter_number(machine, param[0], &addr))
		return;
	address = (offs_t)addr;
	if (!debug_cpu_translate(space, TRANSLATE_READ_DEBUG, &address))
	{
		debug_console_printf(machine, "Address is unmapped.\n");
		return;
	}
	debug_console_printf(machine, "ReadyListHead {%08X,%08X} _LIST_ENTRY\n", space.read_dword_unaligned(address), space.read_dword_unaligned(address + 4));
	debug_console_printf(machine, "ThreadListHead {%08X,%08X} _LIST_ENTRY\n", space.read_dword_unaligned(address + 8), space.read_dword_unaligned(address + 12));
	debug_console_printf(machine, "StackCount %d dword\n", space.read_dword_unaligned(address + 16));
	debug_console_printf(machine, "ThreadQuantum %d dword\n", space.read_dword_unaligned(address + 20));
	debug_console_printf(machine, "BasePriority %d byte\n", space.read_byte(address + 24));
	debug_console_printf(machine, "DisableBoost %d byte\n", space.read_byte(address + 25));
	debug_console_printf(machine, "DisableQuantum %d byte\n", space.read_byte(address + 26));
	debug_console_printf(machine, "_padding %d byte\n", space.read_byte(address + 27));
}

static void dump_list_command(running_machine &machine, int ref, int params, const char **param)
{
	xbox_base_state *state = machine.driver_data<xbox_base_state>();
	address_space &space = state->m_maincpu->space();
	UINT64 addr, offs, start, old;
	offs_t address, offset;

	if (params < 1)
		return;
	if (!debug_command_parameter_number(machine, param[0], &addr))
		return;
	offs = 0;
	offset = 0;
	if (params >= 2)
	{
		if (!debug_command_parameter_number(machine, param[1], &offs))
			return;
		offset = (offs_t)offs;
	}
	start = addr;
	address = (offs_t)addr;
	if (!debug_cpu_translate(space, TRANSLATE_READ_DEBUG, &address))
	{
		debug_console_printf(machine, "Address is unmapped.\n");
		return;
	}
	if (params >= 2)
		debug_console_printf(machine, "Entry    Object\n");
	else
		debug_console_printf(machine, "Entry\n");
	for (int num = 0; num < 32; num++)
	{
		if (params >= 2)
			debug_console_printf(machine, "%08X %08X\n", (UINT32)addr, (offs_t)addr - offset);
		else
			debug_console_printf(machine, "%08X\n", (UINT32)addr);
		old = addr;
		addr = space.read_dword_unaligned(address);
=======
#include "includes/xbox.h"
#include "includes/xbox_pci.h"

#include "cpu/i386/i386.h"
#include "machine/pit8253.h"
#include "debug/debugcon.h"
#include "debug/debugcmd.h"

#include "debugger.h"

#include <functional>

const xbox_base_state::debugger_constants xbox_base_state::debugp[] = {
	{ 0x66232714, {0x8003aae0, 0x5c, 0x1c, 0x28, 0x210, 8, 0x28, 0x1c} },
	{ 0x49d8055a, {0x8003aae0, 0x5c, 0x1c, 0x28, 0x210, 8, 0x28, 0x1c} }
};

int xbox_base_state::find_bios_index(running_machine &mach)
{
	u8 sb = mach.driver_data()->system_bios();
	return sb;
}

bool xbox_base_state::find_bios_hash(running_machine &mach, int bios, uint32_t &crc32)
{
	uint32_t crc = 0;
	const std::vector<rom_entry> &rev = mach.root_device().rom_region_vector();

	for (rom_entry re : rev)
	{
		if ((re.flags() & ROMENTRY_TYPEMASK) == ROMENTRYTYPE_ROM)
		{
			if ((re.flags() & ROM_BIOSFLAGSMASK) == ROM_BIOS(bios + 1))
			{
				const std::string &h = re.hashdata();
				util::hash_collection hc(h.c_str());
				if (hc.crc(crc) == true)
				{
					crc32 = crc;
					return true;
				}
			}
		}
	}
	return false;
}

void xbox_base_state::find_debug_params(running_machine &mach)
{
	uint32_t crc;
	int sb;

	sb = (int)find_bios_index(machine());
	debugc_bios = debugp;
	if (find_bios_hash(machine(), sb - 1, crc) == true)
	{
		for (int n = 0; n < 2; n++)
			if (debugp[n].id == crc)
			{
				debugc_bios = &debugp[n];
				break;
			}
	}
}

void xbox_base_state::dump_string_command(int ref, const std::vector<std::string> &params)
{
	debugger_cpu &cpu = machine().debugger().cpu();
	debugger_console &con = machine().debugger().console();
	address_space &space = m_maincpu->space();
	uint64_t addr;
	offs_t address;

	if (params.size() < 2)
		return;

	if (!machine().debugger().commands().validate_number_parameter(params[1], addr))
		return;

	address = (offs_t)addr;
	if (!m_maincpu->translate(AS_PROGRAM, TRANSLATE_READ_DEBUG, address))
	{
		con.printf("Address is unmapped.\n");
		return;
	}
	address = (offs_t)addr;

	uint32_t length = cpu.read_word(space, address, true);
	uint32_t maximumlength = cpu.read_word(space, address + 2, true);
	offs_t buffer = cpu.read_dword(space, address + 4, true);
	con.printf("Length %d word\n", length);
	con.printf("MaximumLength %d word\n", maximumlength);
	con.printf("Buffer %08X byte* ", buffer);

	// limit the number of characters to avoid flooding
	if (length > 256)
		length = 256;

	for (int a = 0; a < length; a++)
	{
		uint8_t c = cpu.read_byte(space, buffer + a, true);
		con.printf("%c", c);
	}
	con.printf("\n");
}

void xbox_base_state::dump_process_command(int ref, const std::vector<std::string> &params)
{
	debugger_cpu &cpu = machine().debugger().cpu();
	debugger_console &con = machine().debugger().console();
	address_space &space = m_maincpu->space();
	uint64_t addr;
	offs_t address;

	if (params.size() < 2)
		return;

	if (!machine().debugger().commands().validate_number_parameter(params[1], addr))
		return;

	address = (offs_t)addr;
	if (!m_maincpu->translate(AS_PROGRAM, TRANSLATE_READ_DEBUG, address))
	{
		con.printf("Address is unmapped.\n");
		return;
	}
	address = (offs_t)addr;

	con.printf("ReadyListHead {%08X,%08X} _LIST_ENTRY\n", cpu.read_dword(space, address, true), cpu.read_dword(space, address + 4, true));
	con.printf("ThreadListHead {%08X,%08X} _LIST_ENTRY\n", cpu.read_dword(space, address + 8, true), cpu.read_dword(space, address + 12, true));
	con.printf("StackCount %d dword\n", cpu.read_dword(space, address + 16, true));
	con.printf("ThreadQuantum %d dword\n", cpu.read_dword(space, address + 20, true));
	con.printf("BasePriority %d byte\n", cpu.read_byte(space, address + 24, true));
	con.printf("DisableBoost %d byte\n", cpu.read_byte(space, address + 25, true));
	con.printf("DisableQuantum %d byte\n", cpu.read_byte(space, address + 26, true));
	con.printf("_padding %d byte\n", cpu.read_byte(space, address + 27, true));
}

void xbox_base_state::dump_list_command(int ref, const std::vector<std::string> &params)
{
	debugger_cpu &cpu = machine().debugger().cpu();
	debugger_console &con = machine().debugger().console();
	address_space &space = m_maincpu->space();
	uint64_t addr;
	offs_t address;

	if (params.size() < 2)
		return;

	if (!machine().debugger().commands().validate_number_parameter(params[1], addr))
		return;

	uint64_t offs = 0;
	offs_t offset = 0;
	if (params.size() >= 3)
	{
		if (!machine().debugger().commands().validate_number_parameter(params[2], offs))
			return;
		offset = (offs_t)offs;
	}

	uint64_t start = addr;
	address = (offs_t)addr;
	if (!m_maincpu->translate(AS_PROGRAM, TRANSLATE_READ_DEBUG, address))
	{
		con.printf("Address is unmapped.\n");
		return;
	}
	address = (offs_t)addr;
	if (params.size() >= 3)
		con.printf("Entry    Object\n");
	else
		con.printf("Entry\n");

	uint64_t old;
	for (int num = 0; num < 32; num++)
	{
		if (params.size() >= 3)
			con.printf("%08X %08X\n", (uint32_t)addr, (offs_t)addr - offset);
		else
			con.printf("%08X\n", (uint32_t)addr);
		old = addr;
		addr = cpu.read_dword(space, address, true);
>>>>>>> upstream/master
		if (addr == start)
			break;
		if (addr == old)
			break;
		address = (offs_t)addr;
<<<<<<< HEAD
		if (!debug_cpu_translate(space, TRANSLATE_READ_DEBUG, &address))
			break;
	}
}

static void dump_dpc_command(running_machine &machine, int ref, int params, const char **param)
{
	xbox_base_state *state = machine.driver_data<xbox_base_state>();
	address_space &space = state->m_maincpu->space();
	UINT64 addr;
	offs_t address;

	if (params < 1)
		return;
	if (!debug_command_parameter_number(machine, param[0], &addr))
		return;
	address = (offs_t)addr;
	if (!debug_cpu_translate(space, TRANSLATE_READ_DEBUG, &address))
	{
		debug_console_printf(machine, "Address is unmapped.\n");
		return;
	}
	debug_console_printf(machine, "Type %d word\n", space.read_word_unaligned(address));
	debug_console_printf(machine, "Inserted %d byte\n", space.read_byte(address + 2));
	debug_console_printf(machine, "Padding %d byte\n", space.read_byte(address + 3));
	debug_console_printf(machine, "DpcListEntry {%08X,%08X} _LIST_ENTRY\n", space.read_dword_unaligned(address + 4), space.read_dword_unaligned(address + 8));
	debug_console_printf(machine, "DeferredRoutine %08X dword\n", space.read_dword_unaligned(address + 12));
	debug_console_printf(machine, "DeferredContext %08X dword\n", space.read_dword_unaligned(address + 16));
	debug_console_printf(machine, "SystemArgument1 %08X dword\n", space.read_dword_unaligned(address + 20));
	debug_console_printf(machine, "SystemArgument2 %08X dword\n", space.read_dword_unaligned(address + 24));
}

static void dump_timer_command(running_machine &machine, int ref, int params, const char **param)
{
	xbox_base_state *state = machine.driver_data<xbox_base_state>();
	address_space &space = state->m_maincpu->space();
	UINT64 addr;
	offs_t address;

	if (params < 1)
		return;
	if (!debug_command_parameter_number(machine, param[0], &addr))
		return;
	address = (offs_t)addr;
	if (!debug_cpu_translate(space, TRANSLATE_READ_DEBUG, &address))
	{
		debug_console_printf(machine, "Address is unmapped.\n");
		return;
	}
	debug_console_printf(machine, "Header.Type %d byte\n", space.read_byte(address));
	debug_console_printf(machine, "Header.Absolute %d byte\n", space.read_byte(address + 1));
	debug_console_printf(machine, "Header.Size %d byte\n", space.read_byte(address + 2));
	debug_console_printf(machine, "Header.Inserted %d byte\n", space.read_byte(address + 3));
	debug_console_printf(machine, "Header.SignalState %08X dword\n", space.read_dword_unaligned(address + 4));
	debug_console_printf(machine, "Header.WaitListEntry {%08X,%08X} _LIST_ENTRY\n", space.read_dword_unaligned(address + 8), space.read_dword_unaligned(address + 12));
	debug_console_printf(machine, "DueTime %" I64FMT "x qword\n", (INT64)space.read_qword_unaligned(address + 16));
	debug_console_printf(machine, "TimerListEntry {%08X,%08X} _LIST_ENTRY\n", space.read_dword_unaligned(address + 24), space.read_dword_unaligned(address + 28));
	debug_console_printf(machine, "Dpc %08X dword\n", space.read_dword_unaligned(address + 32));
	debug_console_printf(machine, "Period %d dword\n", space.read_dword_unaligned(address + 36));
}

static void curthread_command(running_machine &machine, int ref, int params, const char **param)
{
	xbox_base_state *state = machine.driver_data<xbox_base_state>();
	address_space &space = state->m_maincpu->space();
	UINT64 fsbase;
	UINT32 kthrd, topstack, tlsdata;
	offs_t address;

	fsbase = state->m_maincpu->state_int(44);
	address = (offs_t)fsbase + 0x28;
	if (!debug_cpu_translate(space, TRANSLATE_READ_DEBUG, &address))
	{
		debug_console_printf(machine, "Address is unmapped.\n");
		return;
	}
	kthrd = space.read_dword_unaligned(address);
	debug_console_printf(machine, "Current thread is %08X\n", kthrd);
	address = (offs_t)kthrd + 0x1c;
	if (!debug_cpu_translate(space, TRANSLATE_READ_DEBUG, &address))
		return;
	topstack = space.read_dword_unaligned(address);
	debug_console_printf(machine, "Current thread stack top is %08X\n", topstack);
	address = (offs_t)kthrd + 0x28;
	if (!debug_cpu_translate(space, TRANSLATE_READ_DEBUG, &address))
		return;
	tlsdata = space.read_dword_unaligned(address);
	if (tlsdata == 0)
		address = (offs_t)topstack - 0x210 - 8;
	else
		address = (offs_t)tlsdata - 8;
	if (!debug_cpu_translate(space, TRANSLATE_READ_DEBUG, &address))
		return;
	debug_console_printf(machine, "Current thread function is %08X\n", space.read_dword_unaligned(address));
}

static void generate_irq_command(running_machine &machine, int ref, int params, const char **param)
{
	UINT64 irq;
	xbox_base_state *chst = machine.driver_data<xbox_base_state>();

	if (params < 1)
		return;
	if (!debug_command_parameter_number(machine, param[0], &irq))
=======
		if (!m_maincpu->translate(AS_PROGRAM, TRANSLATE_READ_DEBUG, address))
			break;
		address = (offs_t)addr;
	}
}

void xbox_base_state::dump_dpc_command(int ref, const std::vector<std::string> &params)
{
	debugger_cpu &cpu = machine().debugger().cpu();
	debugger_console &con = machine().debugger().console();
	address_space &space = m_maincpu->space();
	uint64_t addr;
	offs_t address;

	if (params.size() < 2)
		return;

	if (!machine().debugger().commands().validate_number_parameter(params[1], addr))
		return;

	address = (offs_t)addr;
	if (!m_maincpu->translate(AS_PROGRAM, TRANSLATE_READ_DEBUG, address))
	{
		con.printf("Address is unmapped.\n");
		return;
	}
	address = (offs_t)addr;
	con.printf("Type %d word\n", cpu.read_word(space, address, true));
	con.printf("Inserted %d byte\n", cpu.read_byte(space, address + 2, true));
	con.printf("Padding %d byte\n", cpu.read_byte(space, address + 3, true));
	con.printf("DpcListEntry {%08X,%08X} _LIST_ENTRY\n", cpu.read_dword(space, address + 4, true), cpu.read_dword(space, address + 8, true));
	con.printf("DeferredRoutine %08X dword\n", cpu.read_dword(space, address + 12, true));
	con.printf("DeferredContext %08X dword\n", cpu.read_dword(space, address + 16, true));
	con.printf("SystemArgument1 %08X dword\n", cpu.read_dword(space, address + 20, true));
	con.printf("SystemArgument2 %08X dword\n", cpu.read_dword(space, address + 24, true));
}

void xbox_base_state::dump_timer_command(int ref, const std::vector<std::string> &params)
{
	debugger_cpu &cpu = machine().debugger().cpu();
	debugger_console &con = machine().debugger().console();
	address_space &space = m_maincpu->space();
	uint64_t addr;
	offs_t address;

	if (params.size() < 2)
		return;

	if (!machine().debugger().commands().validate_number_parameter(params[1], addr))
		return;

	address = (offs_t)addr;
	if (!m_maincpu->translate(AS_PROGRAM, TRANSLATE_READ_DEBUG, address))
	{
		con.printf("Address is unmapped.\n");
		return;
	}
	address = (offs_t)addr;
	con.printf("Header.Type %d byte\n", cpu.read_byte(space, address, true));
	con.printf("Header.Absolute %d byte\n", cpu.read_byte(space, address + 1, true));
	con.printf("Header.Size %d byte\n", cpu.read_byte(space, address + 2, true));
	con.printf("Header.Inserted %d byte\n", cpu.read_byte(space, address + 3, true));
	con.printf("Header.SignalState %08X dword\n", cpu.read_dword(space, address + 4, true));
	con.printf("Header.WaitListEntry {%08X,%08X} _LIST_ENTRY\n", cpu.read_dword(space, address + 8, true), cpu.read_dword(space, address + 12, true));
	con.printf("%s", string_format("DueTime %x qword\n", (int64_t)cpu.read_qword(space, address + 16, true)).c_str());
	con.printf("TimerListEntry {%08X,%08X} _LIST_ENTRY\n", cpu.read_dword(space, address + 24, true), cpu.read_dword(space, address + 28, true));
	con.printf("Dpc %08X dword\n", cpu.read_dword(space, address + 32, true));
	con.printf("Period %d dword\n", cpu.read_dword(space, address + 36, true));
}

void xbox_base_state::curthread_command(int ref, const std::vector<std::string> &params)
{
	debugger_cpu &cpu = machine().debugger().cpu();
	debugger_console &con = machine().debugger().console();
	address_space &space = m_maincpu->space();
	offs_t address;

	uint64_t fsbase = m_maincpu->state_int(44); // base of FS register
	address = (offs_t)fsbase + (offs_t)debugc_bios->parameter[7-1];
	if (!m_maincpu->translate(AS_PROGRAM, TRANSLATE_READ_DEBUG, address))
	{
		con.printf("Address is unmapped.\n");
		return;
	}
	address = (offs_t)fsbase + (offs_t)debugc_bios->parameter[7-1];

	uint32_t kthrd = cpu.read_dword(space, address, true);
	con.printf("Current thread is %08X\n", kthrd);
	address = (offs_t)(kthrd + debugc_bios->parameter[8-1]);
	uint32_t topstack = cpu.read_dword(space, address, true);
	con.printf("Current thread stack top is %08X\n", topstack);
	address = (offs_t)(kthrd + debugc_bios->parameter[4-1]);
	uint32_t tlsdata = cpu.read_dword(space, address, true);
	if (tlsdata == 0)
		address = (offs_t)(topstack - debugc_bios->parameter[5-1] - debugc_bios->parameter[6-1]);
	else
		address = (offs_t)(tlsdata - debugc_bios->parameter[6-1]);
	con.printf("Current thread function is %08X\n", cpu.read_dword(space, address, true));
}

void xbox_base_state::threadlist_command(int ref, const std::vector<std::string> &params)
{
	address_space &space = m_maincpu->space();
	debugger_cpu &cpu = machine().debugger().cpu();
	debugger_console &con = machine().debugger().console();

	con.printf("Pri. _KTHREAD   Stack  Function\n");
	con.printf("-------------------------------\n");
	for (int pri = 0; pri < 16; pri++)
	{
		uint32_t curr = debugc_bios->parameter[1 - 1] + pri * 8;
		uint32_t next = cpu.read_dword(space, curr, true);

		while ((next != curr) && (next != 0))
		{
			uint32_t kthrd = next - debugc_bios->parameter[2 - 1];
			uint32_t topstack = cpu.read_dword(space, kthrd + debugc_bios->parameter[3 - 1], true);
			uint32_t tlsdata = cpu.read_dword(space, kthrd + debugc_bios->parameter[4 - 1], true);
			uint32_t function;
			if (tlsdata == 0)
				function = cpu.read_dword(space, topstack - debugc_bios->parameter[5 - 1] - debugc_bios->parameter[6 - 1], true);
			else
				function = cpu.read_dword(space, tlsdata - debugc_bios->parameter[6 - 1], true);
			con.printf(" %02d  %08x %08x %08x\n", pri, kthrd, topstack, function);
			next = cpu.read_dword(space, next, true);
		}
	}
}

void xbox_base_state::generate_irq_command(int ref, const std::vector<std::string> &params)
{
	uint64_t irq;

	if (params.size() < 2)
		return;
	if (!machine().debugger().commands().validate_number_parameter(params[1], irq))
>>>>>>> upstream/master
		return;
	if (irq > 15)
		return;
	if (irq == 2)
		return;
<<<<<<< HEAD
	chst->debug_generate_irq((int)irq, true);
}

static void nv2a_combiners_command(running_machine &machine, int ref, int params, const char **param)
{
	int en;

	xbox_base_state *chst = machine.driver_data<xbox_base_state>();
	en = chst->nvidia_nv2a->toggle_register_combiners_usage();
	if (en != 0)
		debug_console_printf(machine, "Register combiners enabled\n");
	else
		debug_console_printf(machine, "Register combiners disabled\n");
}

static void waitvblank_command(running_machine &machine, int ref, int params, const char **param)
{
	int en;

	xbox_base_state *chst = machine.driver_data<xbox_base_state>();
	en = chst->nvidia_nv2a->toggle_wait_vblank_support();
	if (en != 0)
		debug_console_printf(machine, "Vblank method enabled\n");
	else
		debug_console_printf(machine, "Vblank method disabled\n");
}

static void grab_texture_command(running_machine &machine, int ref, int params, const char **param)
{
	UINT64 type;
	xbox_base_state *chst = machine.driver_data<xbox_base_state>();

	if (params < 2)
		return;
	if (!debug_command_parameter_number(machine, param[0], &type))
		return;
	if ((param[1][0] == 0) || (strlen(param[1]) > 127))
		return;
	chst->nvidia_nv2a->debug_grab_texture((int)type, param[1]);
}

static void grab_vprog_command(running_machine &machine, int ref, int params, const char **param)
{
	xbox_base_state *chst = machine.driver_data<xbox_base_state>();
	UINT32 instruction[4];
	FILE *fil;

	if (params < 1)
		return;
	if ((param[0][0] == 0) || (strlen(param[0]) > 127))
		return;
	if ((fil = fopen(param[0], "wb")) == NULL)
		return;
	for (int n = 0; n < 136; n++) {
		chst->nvidia_nv2a->debug_grab_vertex_program_slot(n, instruction);
		fwrite(instruction, sizeof(UINT32), 4, fil);
=======
	debug_generate_irq((int)irq, true);
}

void xbox_base_state::nv2a_combiners_command(int ref, const std::vector<std::string> &params)
{
	debugger_console &con = machine().debugger().console();
	bool en = nvidia_nv2a->toggle_register_combiners_usage();
	if (en == true)
		con.printf("Register combiners enabled\n");
	else
		con.printf("Register combiners disabled\n");
}

void xbox_base_state::nv2a_wclipping_command(int ref, const std::vector<std::string> &params)
{
	debugger_console &con = machine().debugger().console();
	bool en = nvidia_nv2a->toggle_clipping_w_support();
	if (en == true)
		con.printf("W clipping enabled\n");
	else
		con.printf("W clipping disabled\n");
}

void xbox_base_state::waitvblank_command(int ref, const std::vector<std::string> &params)
{
	debugger_console &con = machine().debugger().console();
	bool en = nvidia_nv2a->toggle_wait_vblank_support();
	if (en == true)
		con.printf("Vblank method enabled\n");
	else
		con.printf("Vblank method disabled\n");
}

void xbox_base_state::grab_texture_command(int ref, const std::vector<std::string> &params)
{
	uint64_t type;

	if (params.size() < 3)
		return;
	if (!machine().debugger().commands().validate_number_parameter(params[1], type))
		return;
	if (params[2].empty() || params[2].length() > 127)
		return;
	nvidia_nv2a->debug_grab_texture((int)type, params[2].c_str());
}

void xbox_base_state::grab_vprog_command(int ref, const std::vector<std::string> &params)
{
	uint32_t instruction[4];
	FILE *fil;

	if (params.size() < 2)
		return;
	if (params[1].empty() || params[1].length() > 127)
		return;
	if ((fil = fopen(params[1].c_str(), "wb")) == nullptr)
		return;
	for (int n = 0; n < 136; n++) {
		nvidia_nv2a->debug_grab_vertex_program_slot(n, instruction);
		fwrite(instruction, sizeof(uint32_t), 4, fil);
>>>>>>> upstream/master
	}
	fclose(fil);
}

<<<<<<< HEAD
static void vprogdis_command(running_machine &machine, int ref, int params, const char **param)
{
	UINT64 address, length, type;
	UINT32 instruction[4];
	offs_t addr;
	vertex_program_disassembler vd;
	char line[64];
	xbox_base_state *chst = machine.driver_data<xbox_base_state>();
	address_space &space = chst->m_maincpu->space();

	if (params < 2)
		return;
	if (!debug_command_parameter_number(machine, param[0], &address))
		return;
	if (!debug_command_parameter_number(machine, param[1], &length))
		return;
	type = 0;
	if (params > 2)
		if (!debug_command_parameter_number(machine, param[2], &type))
			return;
	while (length > 0) {
		if (type == 1) {
			addr = (offs_t)address;
			if (!debug_cpu_translate(space, TRANSLATE_READ_DEBUG, &addr))
=======
void xbox_base_state::vprogdis_command(int ref, const std::vector<std::string> &params)
{
	address_space &space = m_maincpu->space();

	if (params.size() < 3)
		return;

	uint64_t address;
	if (!machine().debugger().commands().validate_number_parameter(params[1], address))
		return;

	uint64_t length;
	if (!machine().debugger().commands().validate_number_parameter(params[2], length))
		return;

	uint64_t type = 0;
	if (params.size() > 3)
		if (!machine().debugger().commands().validate_number_parameter(params[3], type))
			return;

	vertex_program_disassembler vd;
	while (length > 0)
	{
		uint32_t instruction[4];
		if (type == 1)
		{
			offs_t addr = (offs_t)address;
			if (!m_maincpu->translate(AS_PROGRAM, TRANSLATE_READ_DEBUG, addr))
>>>>>>> upstream/master
				return;
			instruction[0] = space.read_dword_unaligned(address);
			instruction[1] = space.read_dword_unaligned(address + 4);
			instruction[2] = space.read_dword_unaligned(address + 8);
			instruction[3] = space.read_dword_unaligned(address + 12);
		}
		else
<<<<<<< HEAD
			chst->nvidia_nv2a->debug_grab_vertex_program_slot((int)address, instruction);
		while (vd.disassemble(instruction, line) != 0)
			debug_console_printf(machine, "%s\n", line);
=======
		{
			nvidia_nv2a->debug_grab_vertex_program_slot((int)address, instruction);
		}

		char line[64];
		while (vd.disassemble(instruction, line) != 0)
			machine().debugger().console().printf("%s\n", line);

>>>>>>> upstream/master
		if (type == 1)
			address = address + 4 * 4;
		else
			address++;
<<<<<<< HEAD
=======

>>>>>>> upstream/master
		length--;
	}
}

<<<<<<< HEAD
static void help_command(running_machine &machine, int ref, int params, const char **param)
{
	debug_console_printf(machine, "Available Xbox commands:\n");
	debug_console_printf(machine, "  xbox dump_string,<address> -- Dump _STRING object at <address>\n");
	debug_console_printf(machine, "  xbox dump_process,<address> -- Dump _PROCESS object at <address>\n");
	debug_console_printf(machine, "  xbox dump_list,<address>[,<offset>] -- Dump _LIST_ENTRY chain starting at <address>\n");
	debug_console_printf(machine, "  xbox dump_dpc,<address> -- Dump _KDPC object at <address>\n");
	debug_console_printf(machine, "  xbox dump_timer,<address> -- Dump _KTIMER object at <address>\n");
	debug_console_printf(machine, "  xbox curthread -- Print information about current thread\n");
	debug_console_printf(machine, "  xbox irq,<number> -- Generate interrupt with irq number 0-15\n");
	debug_console_printf(machine, "  xbox nv2a_combiners -- Toggle use of register combiners\n");
	debug_console_printf(machine, "  xbox waitvblank -- Toggle support for wait vblank method\n");
	debug_console_printf(machine, "  xbox grab_texture,<type>,<filename> -- Save to <filename> the next used texture of type <type>\n");
	debug_console_printf(machine, "  xbox grab_vprog,<filename> -- save current vertex program instruction slots to <filename>\n");
	debug_console_printf(machine, "  xbox vprogdis,<address>,<length>[,<type>] -- disassemble <lenght> vertex program instructions at <address> of <type>\n");
	debug_console_printf(machine, "  xbox help -- this list\n");
}

static void xbox_debug_commands(running_machine &machine, int ref, int params, const char **param)
{
	if (params < 1)
		return;
	if (strcmp("dump_string", param[0]) == 0)
		dump_string_command(machine, ref, params - 1, param + 1);
	else if (strcmp("dump_process", param[0]) == 0)
		dump_process_command(machine, ref, params - 1, param + 1);
	else if (strcmp("dump_list", param[0]) == 0)
		dump_list_command(machine, ref, params - 1, param + 1);
	else if (strcmp("dump_dpc", param[0]) == 0)
		dump_dpc_command(machine, ref, params - 1, param + 1);
	else if (strcmp("dump_timer", param[0]) == 0)
		dump_timer_command(machine, ref, params - 1, param + 1);
	else if (strcmp("curthread", param[0]) == 0)
		curthread_command(machine, ref, params - 1, param + 1);
	else if (strcmp("irq", param[0]) == 0)
		generate_irq_command(machine, ref, params - 1, param + 1);
	else if (strcmp("nv2a_combiners", param[0]) == 0)
		nv2a_combiners_command(machine, ref, params - 1, param + 1);
	else if (strcmp("waitvblank", param[0]) == 0)
		waitvblank_command(machine, ref, params - 1, param + 1);
	else if (strcmp("grab_texture", param[0]) == 0)
		grab_texture_command(machine, ref, params - 1, param + 1);
	else if (strcmp("grab_vprog", param[0]) == 0)
		grab_vprog_command(machine, ref, params - 1, param + 1);
	else if (strcmp("vprogdis", param[0]) == 0)
		vprogdis_command(machine, ref, params - 1, param + 1);
	else
		help_command(machine, ref, params - 1, param + 1);
=======
void xbox_base_state::help_command(int ref, const std::vector<std::string> &params)
{
	debugger_console &con = machine().debugger().console();

	con.printf("Available Xbox commands:\n");
	con.printf("  xbox dump_string,<address> -- Dump _STRING object at <address>\n");
	con.printf("  xbox dump_process,<address> -- Dump _PROCESS object at <address>\n");
	con.printf("  xbox dump_list,<address>[,<offset>] -- Dump _LIST_ENTRY chain starting at <address>\n");
	con.printf("  xbox dump_dpc,<address> -- Dump _KDPC object at <address>\n");
	con.printf("  xbox dump_timer,<address> -- Dump _KTIMER object at <address>\n");
	con.printf("  xbox curthread -- Print information about current thread\n");
	con.printf("  xbox threadlist -- list of currently active threads\n");
	con.printf("  xbox irq,<number> -- Generate interrupt with irq number 0-15\n");
	con.printf("  xbox nv2a_combiners -- Toggle use of register combiners\n");
	con.printf("  xbox nv2a_wclipping -- Toggle use of negative w vertex clipping\n");
	con.printf("  xbox waitvblank -- Toggle support for wait vblank method\n");
	con.printf("  xbox grab_texture,<type>,<filename> -- Save to <filename> the next used texture of type <type>\n");
	con.printf("  xbox grab_vprog,<filename> -- save current vertex program instruction slots to <filename>\n");
	con.printf("  xbox vprogdis,<address>,<length>[,<type>] -- disassemble <lenght> vertex program instructions at <address> of <type>\n");
	con.printf("  xbox help -- this list\n");
}

void xbox_base_state::xbox_debug_commands(int ref, const std::vector<std::string> &params)
{
	if (params.size() < 1)
		return;
	if (params[0] == "dump_string")
		dump_string_command(ref, params);
	else if (params[0] == "dump_process")
		dump_process_command(ref, params);
	else if (params[0] == "dump_list")
		dump_list_command(ref, params);
	else if (params[0] == "dump_dpc")
		dump_dpc_command(ref, params);
	else if (params[0] == "dump_timer")
		dump_timer_command(ref, params);
	else if (params[0] == "curthread")
		curthread_command(ref, params);
	else if (params[0] == "threadlist")
		threadlist_command(ref, params);
	else if (params[0] == "irq")
		generate_irq_command(ref, params);
	else if (params[0] == "nv2a_combiners")
		nv2a_combiners_command(ref, params);
	else if (params[0] == "nv2a_wclipping")
		nv2a_wclipping_command(ref, params);
	else if (params[0] == "waitvblank")
		waitvblank_command(ref, params);
	else if (params[0] == "grab_texture")
		grab_texture_command(ref, params);
	else if (params[0] == "grab_vprog")
		grab_vprog_command(ref, params);
	else if (params[0] == "vprogdis")
		vprogdis_command(ref, params);
	else
		help_command(ref, params);
>>>>>>> upstream/master
}

void xbox_base_state::debug_generate_irq(int irq, bool active)
{
	int state;

	if (active)
	{
		debug_irq_active = true;
		debug_irq_number = irq;
		state = 1;
	}
	else
	{
		debug_irq_active = false;
		state = 0;
	}
	switch (irq)
	{
	case 0:
		xbox_base_devs.pic8259_1->ir0_w(state);
		break;
	case 1:
		xbox_base_devs.pic8259_1->ir1_w(state);
		break;
	case 3:
		xbox_base_devs.pic8259_1->ir3_w(state);
		break;
	case 4:
		xbox_base_devs.pic8259_1->ir4_w(state);
		break;
	case 5:
		xbox_base_devs.pic8259_1->ir5_w(state);
		break;
	case 6:
		xbox_base_devs.pic8259_1->ir6_w(state);
		break;
	case 7:
		xbox_base_devs.pic8259_1->ir7_w(state);
		break;
	case 8:
		xbox_base_devs.pic8259_2->ir0_w(state);
		break;
	case 9:
		xbox_base_devs.pic8259_2->ir1_w(state);
		break;
	case 10:
		xbox_base_devs.pic8259_2->ir2_w(state);
		break;
	case 11:
		xbox_base_devs.pic8259_2->ir3_w(state);
		break;
	case 12:
		xbox_base_devs.pic8259_2->ir4_w(state);
		break;
	case 13:
		xbox_base_devs.pic8259_2->ir5_w(state);
		break;
	case 14:
		xbox_base_devs.pic8259_2->ir6_w(state);
		break;
	case 15:
		xbox_base_devs.pic8259_2->ir7_w(state);
		break;
	}
}

<<<<<<< HEAD
void xbox_base_state::vblank_callback(screen_device &screen, bool state)
{
	nvidia_nv2a->vblank_callback(screen, state);
}

UINT32 xbox_base_state::screen_update_callback(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect)
=======
WRITE_LINE_MEMBER(xbox_base_state::vblank_callback)
{
	nvidia_nv2a->vblank_callback(state);
}

uint32_t xbox_base_state::screen_update_callback(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect)
>>>>>>> upstream/master
{
	return nvidia_nv2a->screen_update_callback(screen, bitmap, cliprect);
}

<<<<<<< HEAD
READ32_MEMBER(xbox_base_state::geforce_r)
{
	return nvidia_nv2a->geforce_r(space, offset, mem_mask);
}

WRITE32_MEMBER(xbox_base_state::geforce_w)
{
	nvidia_nv2a->geforce_w(space, offset, data, mem_mask);
}

static UINT32 geforce_pci_r(device_t *busdevice, device_t *device, int function, int reg, UINT32 mem_mask)
{
#ifdef LOG_PCI
	//  logerror("  bus:1 device:NV_2A function:%d register:%d mask:%08X\n",function,reg,mem_mask);
#endif
	return 0;
}

static void geforce_pci_w(device_t *busdevice, device_t *device, int function, int reg, UINT32 data, UINT32 mem_mask)
{
#ifdef LOG_PCI
	//  logerror("  bus:1 device:NV_2A function:%d register:%d data:%08X mask:%08X\n",function,reg,data,mem_mask);
#endif
}

/*
 * ohci usb controller (placeholder for now)
 */

#ifdef LOG_OHCI
static const char *const usbregnames[] = {
	"HcRevision",
	"HcControl",
	"HcCommandStatus",
	"HcInterruptStatus",
	"HcInterruptEnable",
	"HcInterruptDisable",
	"HcHCCA",
	"HcPeriodCurrentED",
	"HcControlHeadED",
	"HcControlCurrentED",
	"HcBulkHeadED",
	"HcBulkCurrentED",
	"HcDoneHead",
	"HcFmInterval",
	"HcFmRemaining",
	"HcFmNumber",
	"HcPeriodicStart",
	"HcLSThreshold",
	"HcRhDescriptorA",
	"HcRhDescriptorB",
	"HcRhStatus",
	"HcRhPortStatus[1]"
};
#endif

READ32_MEMBER(xbox_base_state::usbctrl_r)
{
	UINT32 ret;

#ifdef LOG_OHCI
	if (offset >= 0x54 / 4)
		logerror("usb controller 0 register HcRhPortStatus[%d] read\n", (offset - 0x54 / 4) + 1);
	else
		logerror("usb controller 0 register %s read\n", usbregnames[offset]);
#endif
	ret=ohcist.hc_regs[offset];
	if (offset == 0) { /* hacks needed until usb (and jvs) is implemented */
#ifndef USB_ENABLED
		hack_usb();
#endif
	}
	return ret;
}

WRITE32_MEMBER(xbox_base_state::usbctrl_w)
{
#ifdef USB_ENABLED
	UINT32 old = ohcist.hc_regs[offset];
#endif

#ifdef LOG_OHCI
	if (offset >= 0x54 / 4)
		logerror("usb controller 0 register HcRhPortStatus[%d] write %08X\n", (offset - 0x54 / 4) + 1, data);
	else
		logerror("usb controller 0 register %s write %08X\n", usbregnames[offset], data);
#endif
#ifdef USB_ENABLED
	if (offset == HcRhStatus) {
		if (data & 0x80000000)
			ohcist.hc_regs[HcRhStatus] &= ~0x8000;
		if (data & 0x00020000)
			ohcist.hc_regs[HcRhStatus] &= ~0x0002;
		if (data & 0x00010000)
			ohcist.hc_regs[HcRhStatus] &= ~0x0001;
		return;
	}
	if (offset == HcControl) {
		int hcfs;

		hcfs = (data >> 6) & 3;
		if (hcfs == UsbOperational) {
			ohcist.timer->enable();
			ohcist.timer->adjust(attotime::from_msec(1), 0, attotime::from_msec(1));
			ohcist.writebackdonehadcounter = 7;
		}
		else
			ohcist.timer->enable(false);
		ohcist.state = hcfs;
		ohcist.interruptbulkratio = (data & 3) + 1;
	}
	if (offset == HcCommandStatus) {
		if (data & 1)
			ohcist.hc_regs[HcControl] |= 3 << 6;
		ohcist.hc_regs[HcCommandStatus] |= data;
		return;
	}
	if (offset == HcInterruptStatus) {
		ohcist.hc_regs[HcInterruptStatus] &= ~data;
		usb_ohci_interrupts();
		return;
	}
	if (offset == HcInterruptEnable) {
		ohcist.hc_regs[HcInterruptEnable] |= data;
		usb_ohci_interrupts();
		return;
	}
	if (offset == HcInterruptDisable) {
		ohcist.hc_regs[HcInterruptEnable] &= ~data;
		usb_ohci_interrupts();
		return;
	}
	if (offset >= HcRhPortStatus1) {
		int port = offset - HcRhPortStatus1 + 1; // port 0 not used
		// bit 0 ClearPortEnable: 1 clears PortEnableStatus
		// bit 1 SetPortEnable: 1 sets PortEnableStatus
		// bit 2 SetPortSuspend: 1 sets PortSuspendStatus
		// bit 3 ClearSuspendStatus: 1 clears PortSuspendStatus
		// bit 4 SetPortReset: 1 sets PortResetStatus
		if (data & 0x10) {
			ohcist.hc_regs[offset] |= 0x10;
			ohcist.ports[port].function->execute_reset();
			// after 10ms set PortResetStatusChange and clear PortResetStatus and set PortEnableStatus
			ohcist.ports[port].delay = 10;
		}
		// bit 8 SetPortPower: 1 sets PortPowerStatus
		// bit 9 ClearPortPower: 1 clears PortPowerStatus
		// bit 16 1 clears ConnectStatusChange
		// bit 17 1 clears PortEnableStatusChange
		// bit 18 1 clears PortSuspendStatusChange
		// bit 19 1 clears PortOverCurrentIndicatorChange
		// bit 20 1 clears PortResetStatusChange
		if (ohcist.hc_regs[offset] != old)
			ohcist.hc_regs[HcInterruptStatus] |= RootHubStatusChange;
		usb_ohci_interrupts();
		return;
	}
#endif
	ohcist.hc_regs[offset] = data;
}

TIMER_CALLBACK_MEMBER(xbox_base_state::usb_ohci_timer)
{
	UINT32 hcca;
	int changed = 0;
	int list = 1;
	bool cont = false;
	int pid, remain, mps;

	hcca = ohcist.hc_regs[HcHCCA];
	if (ohcist.state == UsbOperational) {
		// increment frame number
		ohcist.framenumber = (ohcist.framenumber + 1) & 0xffff;
		ohcist.space->write_dword(hcca + 0x80, ohcist.framenumber);
		ohcist.hc_regs[HcFmNumber] = ohcist.framenumber;
	}
	// port reset delay
	for (int p = 1; p <= 4; p++) {
		if (ohcist.ports[p].delay > 0) {
			ohcist.ports[p].delay--;
			if (ohcist.ports[p].delay == 0) {
				ohcist.hc_regs[HcRhPortStatus1 + p - 1] = (ohcist.hc_regs[HcRhPortStatus1 + p - 1] & ~(1 << 4)) | (1 << 20) | (1 << 1); // bit 1 PortEnableStatus
				changed = 1;
			}
		}
	}
	if (ohcist.state == UsbOperational) {
		while (list >= 0)
		{
			// select list, do transfer
			if (list == 0) {
				if (ohcist.hc_regs[HcControl] & (1 << 2)) {
					// periodic
					if (ohcist.hc_regs[HcControl] & (1 << 3)) {
						// isochronous
					}
				}
				list = -1;
			}
			if (list == 1) {
				// control
				if (ohcist.hc_regs[HcControl] & (1 << 4)) {
					cont = true;
					while (cont == true) {
						// if current endpoint descriptor is not 0 use it, otherwise ...
						if (ohcist.hc_regs[HcControlCurrentED] == 0) {
							// ... check the filled bit ...
							if (ohcist.hc_regs[HcCommandStatus] & (1 << 1)) {
								// ... if 1 start processing from the head of the list
								ohcist.hc_regs[HcControlCurrentED] = ohcist.hc_regs[HcControlHeadED];
								ohcist.hc_regs[HcCommandStatus] &= ~(1 << 1);
								// but if the list is empty, go to the next list
								if (ohcist.hc_regs[HcControlCurrentED] == 0)
									cont = false;
							}
							else
								cont = false;
						}
						if (cont == true) {
							// service endpoint descriptor
							usb_ohci_read_endpoint_descriptor(ohcist.hc_regs[HcControlCurrentED]);
							// only if it is not halted and not to be skipped
							if (!(ohcist.endpoint_descriptor.h | ohcist.endpoint_descriptor.k)) {
								// compare the Endpoint Descriptor?s TailPointer and NextTransferDescriptor fields.
								if (ohcist.endpoint_descriptor.headp != ohcist.endpoint_descriptor.tailp) {
									UINT32 a, b;
									// service transfer descriptor
									usb_ohci_read_transfer_descriptor(ohcist.endpoint_descriptor.headp);
									// get pid
									if (ohcist.endpoint_descriptor.d == 1)
										pid=OutPid; // out
									else if (ohcist.endpoint_descriptor.d == 2)
										pid=InPid; // in
									else {
										pid = ohcist.transfer_descriptor.dp; // 0 setup 1 out 2 in
									}
									// determine how much data to transfer
									// setup pid must be 8 bytes
									a = ohcist.transfer_descriptor.be & 0xfff;
									b = ohcist.transfer_descriptor.cbp & 0xfff;
									if ((ohcist.transfer_descriptor.be ^ ohcist.transfer_descriptor.cbp) & 0xfffff000)
										a |= 0x1000;
									remain = a - b + 1;
									if (pid == InPid) {
										mps = ohcist.endpoint_descriptor.mps;
										if (remain < mps)
											mps = remain;
									}
									else {
										mps = ohcist.endpoint_descriptor.mps;
									}
									if (ohcist.transfer_descriptor.cbp == 0)
										mps = 0;
									b = ohcist.transfer_descriptor.cbp;
									// if sending ...
									if (pid != InPid) {
										// ... get mps bytes
										for (int c = 0; c < mps; c++) {
											ohcist.buffer[c] = ohcist.space->read_byte(b);
											b++;
											if ((b & 0xfff) == 0)
												b = ohcist.transfer_descriptor.be & 0xfffff000;
										}
									}
									// should check for time available
									// execute transaction
									mps=ohcist.ports[1].function->execute_transfer(ohcist.endpoint_descriptor.fa, ohcist.endpoint_descriptor.en, pid, ohcist.buffer, mps);
									// if receiving ...
									if (pid == InPid) {
										// ... store mps bytes
										for (int c = 0; c < mps; c++) {
											ohcist.space->write_byte(b,ohcist.buffer[c]);
											b++;
											if ((b & 0xfff) == 0)
												b = ohcist.transfer_descriptor.be & 0xfffff000;
										}
									}
									// status writeback (CompletionCode field, DataToggleControl field, CurrentBufferPointer field, ErrorCount field)
									ohcist.transfer_descriptor.cc = NoError;
									ohcist.transfer_descriptor.t = (ohcist.transfer_descriptor.t ^ 1) | 2;
									ohcist.transfer_descriptor.cbp = b;
									ohcist.transfer_descriptor.ec = 0;
									if ((remain == mps) || (mps == 0)) {
										// retire transfer descriptor
										a = ohcist.endpoint_descriptor.headp;
										ohcist.endpoint_descriptor.headp = ohcist.transfer_descriptor.nexttd;
										ohcist.transfer_descriptor.nexttd = ohcist.hc_regs[HcDoneHead];
										ohcist.hc_regs[HcDoneHead] = a;
										ohcist.endpoint_descriptor.c = ohcist.transfer_descriptor.t & 1;
										if (ohcist.transfer_descriptor.di != 7) {
											if (ohcist.transfer_descriptor.di < ohcist.writebackdonehadcounter)
												ohcist.writebackdonehadcounter = ohcist.transfer_descriptor.di;
										}
										usb_ohci_writeback_transfer_descriptor(a);
										usb_ohci_writeback_endpoint_descriptor(ohcist.hc_regs[HcControlCurrentED]);
									} else {
										usb_ohci_writeback_transfer_descriptor(ohcist.endpoint_descriptor.headp);
									}
								} else
									ohcist.hc_regs[HcControlCurrentED] = ohcist.endpoint_descriptor.nexted;
							} else
								ohcist.hc_regs[HcControlCurrentED] = ohcist.endpoint_descriptor.nexted;
							// one bulk every n control transfers
							ohcist.interruptbulkratio--;
							if (ohcist.interruptbulkratio <= 0) {
								ohcist.interruptbulkratio = (ohcist.hc_regs[HcControl] & 3) + 1;
								cont = false;
							}
						}
					}
				}
				list = 2;
			}
			if (list == 2) {
				// bulk
				if (ohcist.hc_regs[HcControl] & (1 << 5)) {
					ohcist.hc_regs[HcCommandStatus] &= ~(1 << 2);
					if (ohcist.hc_regs[HcControlCurrentED] == 0)
						list = 0;
					else if (ohcist.hc_regs[HcControl] & (1 << 4))
						list = 1;
					else
						list = 0;
				}
			}
		}
		if (ohcist.framenumber == 0)
			ohcist.hc_regs[HcInterruptStatus] |= FrameNumberOverflow;
		ohcist.hc_regs[HcInterruptStatus] |= StartofFrame;
		if ((ohcist.writebackdonehadcounter != 0) && (ohcist.writebackdonehadcounter != 7))
			ohcist.writebackdonehadcounter--;
		if ((ohcist.writebackdonehadcounter == 0) && ((ohcist.hc_regs[HcInterruptStatus] & WritebackDoneHead) == 0)) {
			UINT32 b = 0;

			if ((ohcist.hc_regs[HcInterruptStatus] & ohcist.hc_regs[HcInterruptEnable]) != WritebackDoneHead)
				b = 1;
			ohcist.hc_regs[HcInterruptStatus] |= WritebackDoneHead;
			ohcist.space->write_dword(hcca + 0x84, ohcist.hc_regs[HcDoneHead] | b);
			ohcist.hc_regs[HcDoneHead] = 0;
			ohcist.writebackdonehadcounter = 7;
		}
	}
	if (changed != 0) {
		ohcist.hc_regs[HcInterruptStatus] |= RootHubStatusChange;
	}
	usb_ohci_interrupts();
}

void xbox_base_state::usb_ohci_plug(int port, ohci_function_device *function)
{
	if ((port > 0) && (port <= 4)) {
		ohcist.ports[port].function = function;
		ohcist.hc_regs[HcRhPortStatus1+port-1] = 1;
	}
}

static USBStandardDeviceDscriptor devdesc = {18,1,0x201,0xff,0x34,0x56,64,0x100,0x101,0x301,0,0,0,1};

ohci_function_device::ohci_function_device()
{
	address = 0;
	controldir = 0;
	remain = 0;
	position = NULL;
}

void ohci_function_device::execute_reset()
{
	address = 0;
}

int ohci_function_device::execute_transfer(int address, int endpoint, int pid, UINT8 *buffer, int size)
{
	if (endpoint == 0) {
		if (pid == SetupPid) {
			struct USBSetupPacket *p=(struct USBSetupPacket *)buffer;
			// define direction
			controldir = p->bmRequestType & 128;
			// case !=0, in data stage and out status stage
			// case ==0, out data stage and in status stage
			position = NULL;
			remain = p->wLength;
			if ((p->bmRequestType & 0x60) == 0) {
				switch (p->bRequest) {
				case GET_DESCRIPTOR:
					if ((p->wValue >> 8) == 1) { // device descriptor
						//p->wValue & 255;
						position = (UINT8 *)&devdesc;
						remain = sizeof(devdesc);
					}
					break;
				case SET_ADDRESS:
					//p->wValue;
					break;
				default:
					break;
				}
			}
		}
		else if (pid == InPid) {
			// case !=0, give data
			// case ==0, nothing
			if (size > remain)
				size = remain;
			if (controldir != 0) {
				if (position != NULL)
					memcpy(buffer, position, size);
				position = position + size;
				remain = remain - size;
			}
		}
		else if (pid == OutPid) {
			// case !=0, nothing
			// case ==0, give data
			if (size > remain)
				size = remain;
			if (controldir == 0) {
				if (position != NULL)
					memcpy(position, buffer, size);
				position = position + size;
				remain = remain - size;
			}
		}
	}
	return size;
}

void xbox_base_state::usb_ohci_interrupts()
{
	if (((ohcist.hc_regs[HcInterruptStatus] & ohcist.hc_regs[HcInterruptEnable]) != 0) && ((ohcist.hc_regs[HcInterruptEnable] & MasterInterruptEnable) != 0))
		xbox_base_devs.pic8259_1->ir1_w(1);
	else
		xbox_base_devs.pic8259_1->ir1_w(0);
}

void xbox_base_state::usb_ohci_read_endpoint_descriptor(UINT32 address)
{
	UINT32 w;

	w = ohcist.space->read_dword(address);
	ohcist.endpoint_descriptor.word0 = w;
	ohcist.endpoint_descriptor.fa = w & 0x7f;
	ohcist.endpoint_descriptor.en = (w >> 7) & 15;
	ohcist.endpoint_descriptor.d = (w >> 11) & 3;
	ohcist.endpoint_descriptor.s = (w >> 13) & 1;
	ohcist.endpoint_descriptor.k = (w >> 14) & 1;
	ohcist.endpoint_descriptor.f = (w >> 15) & 1;
	ohcist.endpoint_descriptor.mps = (w >> 16) & 0x7ff;
	ohcist.endpoint_descriptor.tailp = ohcist.space->read_dword(address + 4);
	w = ohcist.space->read_dword(address + 8);
	ohcist.endpoint_descriptor.headp = w & 0xfffffffc;
	ohcist.endpoint_descriptor.h = w & 1;
	ohcist.endpoint_descriptor.c = (w >> 1) & 1;
	ohcist.endpoint_descriptor.nexted = ohcist.space->read_dword(address + 12);
}

void xbox_base_state::usb_ohci_writeback_endpoint_descriptor(UINT32 address)
{
	UINT32 w;

	w = ohcist.endpoint_descriptor.word0 & 0xf8000000;
	w = w | (ohcist.endpoint_descriptor.mps << 16) | (ohcist.endpoint_descriptor.f << 15) | (ohcist.endpoint_descriptor.k << 14) | (ohcist.endpoint_descriptor.s << 13) | (ohcist.endpoint_descriptor.d << 11) | (ohcist.endpoint_descriptor.en << 7) | ohcist.endpoint_descriptor.fa;
	ohcist.space->write_dword(address, w);
	w = ohcist.endpoint_descriptor.headp | (ohcist.endpoint_descriptor.c << 1) | ohcist.endpoint_descriptor.h;
	ohcist.space->write_dword(address + 8, w);
}

void xbox_base_state::usb_ohci_read_transfer_descriptor(UINT32 address)
{
	UINT32 w;

	w = ohcist.space->read_dword(address);
	ohcist.transfer_descriptor.word0 = w;
	ohcist.transfer_descriptor.cc = (w >> 28) & 15;
	ohcist.transfer_descriptor.ec= (w >> 26) & 3;
	ohcist.transfer_descriptor.t= (w >> 24) & 3;
	ohcist.transfer_descriptor.di= (w >> 21) & 7;
	ohcist.transfer_descriptor.dp= (w >> 19) & 3;
	ohcist.transfer_descriptor.r = (w >> 18) & 1;
	ohcist.transfer_descriptor.cbp = ohcist.space->read_dword(address + 4);
	ohcist.transfer_descriptor.nexttd = ohcist.space->read_dword(address + 8);
	ohcist.transfer_descriptor.be = ohcist.space->read_dword(address + 12);
}

void xbox_base_state::usb_ohci_writeback_transfer_descriptor(UINT32 address)
{
	UINT32 w;

	w = ohcist.transfer_descriptor.word0 & 0x0003ffff;
	w = w | (ohcist.transfer_descriptor.cc << 28) | (ohcist.transfer_descriptor.ec << 26) | (ohcist.transfer_descriptor.t << 24) | (ohcist.transfer_descriptor.di << 21) | (ohcist.transfer_descriptor.dp << 19) | (ohcist.transfer_descriptor.r << 18);
	ohcist.space->write_dword(address, w);
	ohcist.space->write_dword(address + 4, ohcist.transfer_descriptor.cbp);
	ohcist.space->write_dword(address + 8, ohcist.transfer_descriptor.nexttd);
}

void xbox_base_state::usb_ohci_read_isochronous_transfer_descriptor(UINT32 address)
{
	UINT32 w;

	w = ohcist.space->read_dword(address);
	ohcist.isochronous_transfer_descriptor.cc = (w >> 28) & 15;
	ohcist.isochronous_transfer_descriptor.fc = (w >> 24) & 7;
	ohcist.isochronous_transfer_descriptor.di = (w >> 21) & 7;
	ohcist.isochronous_transfer_descriptor.sf = w & 0xffff;
	ohcist.isochronous_transfer_descriptor.bp0 = ohcist.space->read_dword(address + 4) & 0xfffff000;
	ohcist.isochronous_transfer_descriptor.nexttd = ohcist.space->read_dword(address + 8);
	ohcist.isochronous_transfer_descriptor.be = ohcist.space->read_dword(address + 12);
	w = ohcist.space->read_dword(address + 16);
	ohcist.isochronous_transfer_descriptor.offset[0] = w & 0xffff;
	ohcist.isochronous_transfer_descriptor.offset[1] = (w >> 16) & 0xffff;
	w = ohcist.space->read_dword(address + 20);
	ohcist.isochronous_transfer_descriptor.offset[2] = w & 0xffff;
	ohcist.isochronous_transfer_descriptor.offset[3] = (w >> 16) & 0xffff;
	w = ohcist.space->read_dword(address + 24);
	ohcist.isochronous_transfer_descriptor.offset[4] = w & 0xffff;
	ohcist.isochronous_transfer_descriptor.offset[5] = (w >> 16) & 0xffff;
	w = ohcist.space->read_dword(address + 28);
	ohcist.isochronous_transfer_descriptor.offset[6] = w & 0xffff;
	ohcist.isochronous_transfer_descriptor.offset[7] = (w >> 16) & 0xffff;
}

/*
 * Audio
 */

READ32_MEMBER(xbox_base_state::audio_apu_r)
{
	logerror("Audio_APU: read from %08X mask %08X\n", 0xfe800000 + offset * 4, mem_mask);
	if (offset == 0x20010 / 4) // some kind of internal counter or state value
		return 0x20 + 4 + 8 + 0x48 + 0x80;
	return apust.memory[offset];
}

WRITE32_MEMBER(xbox_base_state::audio_apu_w)
{
	//UINT32 old;
	UINT32 v;

	logerror("Audio_APU: write at %08X mask %08X value %08X\n", 0xfe800000 + offset * 4, mem_mask, data);
	//old = apust.memory[offset];
	apust.memory[offset] = data;
	if (offset == 0x02040 / 4) // address of memory area with scatter-gather info (gpdsp scratch dma)
		apust.gpdsp_sgaddress = data;
	if (offset == 0x020d4 / 4) { // block count (gpdsp)
		apust.gpdsp_sgblocks = data;
		apust.gpdsp_address = apust.space->read_dword(apust.gpdsp_sgaddress); // memory address of first block
		apust.timer->enable();
		apust.timer->adjust(attotime::from_msec(1), 0, attotime::from_msec(1));
	}
	if (offset == 0x02048 / 4) // (epdsp scratch dma)
		apust.epdsp_sgaddress = data;
	if (offset == 0x020dc / 4) // (epdsp)
		apust.epdsp_sgblocks = data;
	if (offset == 0x0204c / 4) // address of memory area with information about blocks
		apust.unknown_sgaddress = data;
	if (offset == 0x020e0 / 4) // block count - 1
		apust.unknown_sgblocks = data;
	if (offset == 0x0202c / 4) { // address of memory area with 0x80 bytes for each voice
		apust.voicedata_address = data;
		return;
	}
	if (offset == 0x04024 / 4) // offset in memory area indicated by 0x204c (analog output ?)
		return;
	if (offset == 0x04034 / 4) // size
		return;
	if (offset == 0x04028 / 4) // offset in memory area indicated by 0x204c (digital output ?)
		return;
	if (offset == 0x04038 / 4) // size
		return;
	if (offset == 0x20804 / 4) { // block number for scatter-gather heap that stores sampled audio to be played
		if (data >= 1024) {
			logerror("Audio_APU: sg block number too high, increase size of voices_heap_blockaddr\n");
			apust.memory[offset] = 1023;
		}
		return;
	}
	if (offset == 0x20808 / 4) { // block address for scatter-gather heap that stores sampled audio to be played
		apust.voices_heap_blockaddr[apust.memory[0x20804 / 4]] = data;
		return;
	}
	if (offset == 0x202f8 / 4) { // voice number for parameters ?
		apust.voice_number = data;
		return;
	}
	if (offset == 0x202fc / 4) // 1 when accessing voice parameters 0 otherwise
		return;
	if (offset == 0x20304 / 4) { // format
		/*
		bits 28-31 sample format:
		0  8-bit pcm
		5  16-bit pcm
		10 adpcm ?
		14 24-bit pcm
		15 32-bit pcm
		bits 16-20 number of channels - 1:
		0  mono
		1  stereo
		*/
		return;
	}
	if (offset == 0x2037c / 4) { // value related to sample rate
		INT16 v = (INT16)(data >> 16); // upper 16 bits as a signed 16 bit value
		float vv = ((float)v) / 4096.0f; // divide by 4096
		float vvv = powf(2, vv); // two to the vv
		int f = vvv*48000.0f; // sample rate
		apust.voices_frequency[apust.voice_number] = f;
		return;
	}
	if (offset == 0x203a0 / 4) // start offset of data in scatter-gather heap
		return;
	if (offset == 0x203a4 / 4) { // first sample to play
		apust.voices_position_start[apust.voice_number] = data * 1000;
		return;
	}
	if (offset == 0x203dc / 4) { // last sample to play
		apust.voices_position_end[apust.voice_number] = data * 1000;
		return;
	}
	if (offset == 0x2010c / 4) // voice processor 0 idle 1 not idle ?
		return;
	if (offset == 0x20124 / 4) { // voice number to activate ?
		v = apust.voice_number;
		apust.voices_active[v >> 6] |= ((UINT64)1 << (v & 63));
		apust.voices_position[v] = apust.voices_position_start[apust.voice_number];
		apust.voices_position_increment[apust.voice_number] = apust.voices_frequency[apust.voice_number];
		return;
	}
	if (offset == 0x20128 / 4) { // voice number to deactivate ?
		v = apust.voice_number;
		apust.voices_active[v >> 6] &= ~(1 << (v & 63));
		return;
	}
	if (offset == 0x20140 / 4) // voice number to ?
		return;
	if ((offset >= 0x20200 / 4) && (offset < 0x20280 / 4)) // headroom for each of the 32 mixbins
		return;
	if (offset == 0x20280 / 4) // hrtf headroom ?
		return;
}

READ32_MEMBER(xbox_base_state::audio_ac93_r)
{
	UINT32 ret = 0;

	logerror("Audio_AC3: read from %08X mask %08X\n", 0xfec00000 + offset * 4, mem_mask);
	if (offset < 0x80 / 4)
	{
		ret = ac97st.mixer_regs[offset];
	}
	if ((offset >= 0x100 / 4) && (offset <= 0x138 / 4))
	{
		offset = offset - 0x100 / 4;
		if (offset == 0x18 / 4)
		{
			ac97st.controller_regs[offset] &= ~0x02000000; // REGRST: register reset
		}
		if (offset == 0x30 / 4)
		{
			ac97st.controller_regs[offset] |= 0x100; // PCRDY: primary codec ready
		}
		if (offset == 0x34 / 4)
		{
			ac97st.controller_regs[offset] &= ~1; // CAS: codec access semaphore
		}
		ret = ac97st.controller_regs[offset];
	}
	return ret;
}

WRITE32_MEMBER(xbox_base_state::audio_ac93_w)
{
	logerror("Audio_AC3: write at %08X mask %08X value %08X\n", 0xfec00000 + offset * 4, mem_mask, data);
	if (offset < 0x80 / 4)
	{
		COMBINE_DATA(ac97st.mixer_regs + offset);
	}
	if ((offset >= 0x100 / 4) && (offset <= 0x138 / 4))
	{
		offset = offset - 0x100 / 4;
		COMBINE_DATA(ac97st.controller_regs + offset);
	}
}

TIMER_CALLBACK_MEMBER(xbox_base_state::audio_apu_timer)
{
	int cmd;
	int bb, b, v;
	UINT64 bv;
	UINT32 phys;

	cmd = apust.space->read_dword(apust.gpdsp_address + 0x800 + 0x10);
	if (cmd == 3)
		apust.space->write_dword(apust.gpdsp_address + 0x800 + 0x10, 0);
	/*else
	logerror("Audio_APU: unexpected value at address %d\n",apust.gpdsp_address+0x800+0x10);*/
	for (b = 0; b < 4; b++) {
		bv = 1;
		for (bb = 0; bb < 64; bb++) {
			if (apust.voices_active[b] & bv) {
				v = bb + (b << 6);
				apust.voices_position[v] += apust.voices_position_increment[v];
				while (apust.voices_position[v] >= apust.voices_position_end[v])
					apust.voices_position[v] = apust.voices_position_start[v] + apust.voices_position[v] - apust.voices_position_end[v] - 1000;
				phys = apust.voicedata_address + 0x80 * v;
				apust.space->write_dword(phys + 0x58, apust.voices_position[v] / 1000);
			}
			bv = bv << 1;
		}
	}
}

static UINT32 hubintiasbridg_pci_r(device_t *busdevice, device_t *device, int function, int reg, UINT32 mem_mask)
{
#ifdef LOG_PCI
	//  logerror("  bus:0 function:%d register:%d mask:%08X\n",function,reg,mem_mask);
#endif
	if ((function == 0) && (reg == 8))
		return 0xb4; // 0:1:0 revision id must be at least 0xb4, otherwise usb will require a hub
	return 0;
}

static void hubintiasbridg_pci_w(device_t *busdevice, device_t *device, int function, int reg, UINT32 data, UINT32 mem_mask)
{
#ifdef LOG_PCI
	if (reg >= 16) busdevice->logerror("  bus:0 function:%d register:%d data:%08X mask:%08X\n", function, reg, data, mem_mask);
#endif
}

/*
 * dummy for non connected devices
 */

static UINT32 dummy_pci_r(device_t *busdevice, device_t *device, int function, int reg, UINT32 mem_mask)
{
#ifdef LOG_PCI
	//  logerror("  bus:0 function:%d register:%d mask:%08X\n",function,reg,mem_mask);
#endif
	return 0;
}

static void dummy_pci_w(device_t *busdevice, device_t *device, int function, int reg, UINT32 data, UINT32 mem_mask)
{
#ifdef LOG_PCI
	if (reg >= 16) busdevice->logerror("  bus:0 function:%d register:%d data:%08X mask:%08X\n", function, reg, data, mem_mask);
#endif
}

READ32_MEMBER(xbox_base_state::dummy_r)
{
	return 0;
}

WRITE32_MEMBER(xbox_base_state::dummy_w)
{
}

=======
>>>>>>> upstream/master
/*
 * PIC & PIT
 */

WRITE_LINE_MEMBER(xbox_base_state::xbox_pic8259_1_set_int_line)
{
	m_maincpu->set_input_line(0, state ? HOLD_LINE : CLEAR_LINE);
}

READ8_MEMBER(xbox_base_state::get_slave_ack)
{
	if (offset == 2) { // IRQ = 2
		return xbox_base_devs.pic8259_2->acknowledge();
	}
	return 0x00;
}

IRQ_CALLBACK_MEMBER(xbox_base_state::irq_callback)
{
	int r = 0;
<<<<<<< HEAD
	r = xbox_base_devs.pic8259_2->acknowledge();
	if (r == 0)
	{
		r = xbox_base_devs.pic8259_1->acknowledge();
	}
=======
	r = xbox_base_devs.pic8259_1->acknowledge();
>>>>>>> upstream/master
	if (debug_irq_active)
		debug_generate_irq(debug_irq_number, false);
	return r;
}

WRITE_LINE_MEMBER(xbox_base_state::xbox_pit8254_out0_changed)
{
	if (xbox_base_devs.pic8259_1)
	{
		xbox_base_devs.pic8259_1->ir0_w(state);
	}
}

WRITE_LINE_MEMBER(xbox_base_state::xbox_pit8254_out2_changed)
{
	//xbox_speaker_set_input( state ? 1 : 0 );
}

<<<<<<< HEAD
/*
 * SMbus devices
 */

int smbus_callback_pic16lc(xbox_base_state &chs, int command, int rw, int data)
{
	return chs.smbus_pic16lc(command, rw, data);
}

=======
WRITE_LINE_MEMBER(xbox_base_state::xbox_ohci_usb_interrupt_changed)
{
	xbox_base_devs.pic8259_1->ir1_w(state);
}

WRITE_LINE_MEMBER(xbox_base_state::xbox_smbus_interrupt_changed)
{
	xbox_base_devs.pic8259_2->ir3_w(state);
}

WRITE_LINE_MEMBER(xbox_base_state::xbox_nv2a_interrupt_changed)
{
	xbox_base_devs.pic8259_1->ir3_w(state);
}

/*
 * SMbus devices
 */

>>>>>>> upstream/master
int xbox_base_state::smbus_pic16lc(int command, int rw, int data)
{
	if (rw == 1) { // read
		if (command == 0) {
			if (pic16lc_buffer[0] == 'D')
				pic16lc_buffer[0] = 'X';
			else if (pic16lc_buffer[0] == 'X')
				pic16lc_buffer[0] = 'B';
			else if (pic16lc_buffer[0] == 'B')
				pic16lc_buffer[0] = 'D';
		}
		logerror("pic16lc: %d %d %d\n", command, rw, pic16lc_buffer[command]);
		return pic16lc_buffer[command];
	}
	else
		if (command == 0)
			pic16lc_buffer[0] = 'B';
		else
<<<<<<< HEAD
			pic16lc_buffer[command] = (UINT8)data;
=======
			pic16lc_buffer[command] = (uint8_t)data;
>>>>>>> upstream/master
	logerror("pic16lc: %d %d %d\n", command, rw, data);
	return 0;
}

<<<<<<< HEAD
int smbus_callback_cx25871(xbox_base_state &chs, int command, int rw, int data)
{
	return chs.smbus_cx25871(command, rw, data);
}

=======
>>>>>>> upstream/master
int xbox_base_state::smbus_cx25871(int command, int rw, int data)
{
	logerror("cx25871: %d %d %d\n", command, rw, data);
	return 0;
}

<<<<<<< HEAD
// let's try to fake the missing eeprom
static int dummyeeprom[256] = { 0x94,0x18,0x10,0x59,0x83,0x58,0x15,0xDA,0xDF,0xCC,0x1D,0x78,0x20,0x8A,0x61,0xB8,0x08,0xB4,0xD6,0xA8,
0x9E,0x77,0x9C,0xEB,0xEA,0xF8,0x93,0x6E,0x3E,0xD6,0x9C,0x49,0x6B,0xB5,0x6E,0xAB,0x6D,0xBC,0xB8,0x80,0x68,0x9D,0xAA,0xCD,0x0B,0x83,
0x17,0xEC,0x2E,0xCE,0x35,0xA8,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x61,0x62,0x63,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,0x00,0x00,
0x4F,0x6E,0x6C,0x69,0x6E,0x65,0x6B,0x65,0x79,0x69,0x6E,0x76,0x61,0x6C,0x69,0x64,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,
0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

int smbus_callback_eeprom(xbox_base_state &chs, int command, int rw, int data)
{
	return chs.smbus_eeprom(command, rw, data);
}
=======
// let's try to fake the missing eeprom, make sure its ntsc, otherwise chihiro will show an error
static int dummyeeprom[256] = {
	0x39, 0xe3, 0xcc, 0x81, 0xb0, 0xa9, 0x97, 0x09, 0x57, 0xac, 0x57, 0x12, 0xf7, 0xc2, 0xc0, 0x21, 0xce, 0x0d, 0x0a, 0xdb, 0x20, 0x7a, 0xf3, 0xff,
	0xdf, 0x67, 0xed, 0xf4, 0xf8, 0x95, 0x5c, 0xd0, 0x9b, 0xef, 0x7b, 0x81, 0xda, 0xd5, 0x98, 0xc1, 0xb1, 0xb3, 0x74, 0x18, 0x86, 0x05, 0xe2, 0x7c,
	0xd1, 0xad, 0xc9, 0x90, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x00, 0x00,
	0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0xab, 0xcd, 0xef, 0xba, 0xdc, 0xfe, 0xa1, 0xb2, 0xc3, 0xd3, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
>>>>>>> upstream/master

int xbox_base_state::smbus_eeprom(int command, int rw, int data)
{
	if (command >= 112)
		return 0;
	if (rw == 1) { // if reading
		// hack to avoid hanging if eeprom contents are not correct
		// this would need dumping the serial eeprom on the xbox board
		if (command == 0) {
			hack_eeprom();
		}
		data = dummyeeprom[command] + dummyeeprom[command + 1] * 256;
		logerror("eeprom: %d %d %d\n", command, rw, data);
		return data;
	}
	logerror("eeprom: %d %d %d\n", command, rw, data);
	dummyeeprom[command] = data;
	return 0;
}

/*
<<<<<<< HEAD
 * SMbus controller
 */

void xbox_base_state::smbus_register_device(int address, int(*handler)(xbox_base_state &chs, int command, int rw, int data))
{
	if (address < 128)
		smbusst.devices[address] = handler;
}

READ32_MEMBER(xbox_base_state::smbus_r)
{
	if ((offset == 0) && (mem_mask == 0xff)) // 0 smbus status
		smbusst.words[offset] = (smbusst.words[offset] & ~mem_mask) | ((smbusst.status << 0) & mem_mask);
	if ((offset == 1) && ((mem_mask == 0x00ff0000) || (mem_mask == 0xffff0000))) // 6 smbus data
		smbusst.words[offset] = (smbusst.words[offset] & ~mem_mask) | ((smbusst.data << 16) & mem_mask);
	return smbusst.words[offset];
}

WRITE32_MEMBER(xbox_base_state::smbus_w)
{
	COMBINE_DATA(smbusst.words);
	if ((offset == 0) && (mem_mask == 0xff)) // 0 smbus status
	{
		if (!((smbusst.status ^ data) & 0x10)) // clearing interrupt
			xbox_base_devs.pic8259_2->ir3_w(0); // IRQ 11
		smbusst.status &= ~data;
	}
	if ((offset == 0) && (mem_mask == 0xff0000)) // 2 smbus control
	{
		data = data >> 16;
		smbusst.control = data;
		int cycletype = smbusst.control & 7;
		if (smbusst.control & 8) { // start
			if ((cycletype & 6) == 2)
			{
				if (smbusst.devices[smbusst.address])
					if (smbusst.rw == 0)
						smbusst.devices[smbusst.address](*this, smbusst.command, smbusst.rw, smbusst.data);
					else
						smbusst.data = smbusst.devices[smbusst.address](*this, smbusst.command, smbusst.rw, smbusst.data);
				else
					logerror("SMBUS: access to missing device at address %d\n", smbusst.address);
				smbusst.status |= 0x10;
				if (smbusst.control & 0x10)
				{
					xbox_base_devs.pic8259_2->ir3_w(1); // IRQ 11
				}
			}
		}
	}
	if ((offset == 1) && (mem_mask == 0xff)) // 4 smbus address
	{
		smbusst.address = data >> 1;
		smbusst.rw = data & 1;
	}
	if ((offset == 1) && ((mem_mask == 0x00ff0000) || (mem_mask == 0xffff0000))) // 6 smbus data
	{
		data = data >> 16;
		smbusst.data = data;
	}
	if ((offset == 2) && (mem_mask == 0xff)) // 8 smbus command
		smbusst.command = data;
}

ADDRESS_MAP_START(xbox_base_map, AS_PROGRAM, 32, xbox_base_state)
	AM_RANGE(0x00000000, 0x07ffffff) AM_RAM AM_SHARE("nv2a_share") // 128 megabytes
	AM_RANGE(0xf0000000, 0xf7ffffff) AM_RAM AM_SHARE("nv2a_share") // 3d accelerator wants this
	AM_RANGE(0xfd000000, 0xfdffffff) AM_RAM AM_READWRITE(geforce_r, geforce_w)
	AM_RANGE(0xfed00000, 0xfed003ff) AM_READWRITE(usbctrl_r, usbctrl_w)
	AM_RANGE(0xfe800000, 0xfe85ffff) AM_READWRITE(audio_apu_r, audio_apu_w)
	AM_RANGE(0xfec00000, 0xfec001ff) AM_READWRITE(audio_ac93_r, audio_ac93_w)
	AM_RANGE(0xff000000, 0xff0fffff) AM_ROM AM_REGION("bios", 0) AM_MIRROR(0x00f80000)
ADDRESS_MAP_END

ADDRESS_MAP_START(xbox_base_map_io, AS_IO, 32, xbox_base_state)
	AM_RANGE(0x0020, 0x0023) AM_DEVREADWRITE8("pic8259_1", pic8259_device, read, write, 0xffffffff)
	AM_RANGE(0x0040, 0x0043) AM_DEVREADWRITE8("pit8254", pit8254_device, read, write, 0xffffffff)
	AM_RANGE(0x00a0, 0x00a3) AM_DEVREADWRITE8("pic8259_2", pic8259_device, read, write, 0xffffffff)
	AM_RANGE(0x01f0, 0x01f7) AM_DEVREADWRITE("ide", bus_master_ide_controller_device, read_cs0, write_cs0)
	AM_RANGE(0x0cf8, 0x0cff) AM_DEVREADWRITE("pcibus", pci_bus_legacy_device, read, write)
	AM_RANGE(0x8000, 0x80ff) AM_READWRITE(dummy_r, dummy_w)
	AM_RANGE(0xc000, 0xc0ff) AM_READWRITE(smbus_r, smbus_w)
	AM_RANGE(0xff60, 0xff67) AM_DEVREADWRITE("ide", bus_master_ide_controller_device, bmdma_r, bmdma_w)
ADDRESS_MAP_END

void xbox_base_state::machine_start()
{
	nvidia_nv2a = auto_alloc(machine(), nv2a_renderer(machine()));
	memset(pic16lc_buffer, 0, sizeof(pic16lc_buffer));
	pic16lc_buffer[0] = 'B';
	pic16lc_buffer[4] = 0; // A/V connector, 2=vga
	smbus_register_device(0x10, smbus_callback_pic16lc);
	smbus_register_device(0x45, smbus_callback_cx25871);
	smbus_register_device(0x54, smbus_callback_eeprom);
	xbox_base_devs.pic8259_1 = machine().device<pic8259_device>("pic8259_1");
	xbox_base_devs.pic8259_2 = machine().device<pic8259_device>("pic8259_2");
	xbox_base_devs.ide = machine().device<bus_master_ide_controller_device>("ide");
	memset(apust.memory, 0, sizeof(apust.memory));
	memset(apust.voices_heap_blockaddr, 0, sizeof(apust.voices_heap_blockaddr));
	memset(apust.voices_active, 0, sizeof(apust.voices_active));
	memset(apust.voices_position, 0, sizeof(apust.voices_position));
	memset(apust.voices_position_start, 0, sizeof(apust.voices_position_start));
	memset(apust.voices_position_end, 0, sizeof(apust.voices_position_end));
	memset(apust.voices_position_increment, 0, sizeof(apust.voices_position_increment));
	apust.space = &m_maincpu->space();
	apust.timer = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(xbox_base_state::audio_apu_timer), this), (void *)"APU Timer");
	apust.timer->enable(false);
	if (machine().debug_flags & DEBUG_FLAG_ENABLED)
		debug_console_register_command(machine(), "xbox", CMDFLAG_NONE, 0, 1, 4, xbox_debug_commands);
	memset(&ohcist, 0, sizeof(ohcist));
=======
 * SuperIO
 */

READ8_MEMBER(xbox_base_state::superio_read)
{
	if (superiost.configuration_mode == false)
		return 0;
	if (offset == 0) // index port 0x2e
		return superiost.index;
	if (offset == 1)
	{
		// data port 0x2f
		if (superiost.index < 0x30)
			return superiost.registers[0][superiost.index];
		return superiost.registers[superiost.selected][superiost.index];
	}
	return 0;
}

WRITE8_MEMBER(xbox_base_state::superio_write)
{
	if (superiost.configuration_mode == false)
	{
		// config port 0x2e
		if ((offset == 0) && (data == 0x55))
			superiost.configuration_mode = true;
		return;
	}
	if ((offset == 0) && (data == 0xaa))
	{
		// config port 0x2e
		superiost.configuration_mode = false;
		return;
	}
	if (offset == 0)
	{
		// index port 0x2e
		superiost.index = data;
	}
	if (offset == 1)
	{
		// data port 0x2f
		if (superiost.index < 0x30)
		{
			superiost.registers[0][superiost.index] = data;
			superiost.selected = superiost.registers[0][7];
		} else
		{
			superiost.registers[superiost.selected][superiost.index] = data;
			//if ((superiost.selected == 4) && (superiost.index == 0x30) && (data != 0))
			//  ; // add handlers 0x3f8- +7
		}
	}
}

READ8_MEMBER(xbox_base_state::superiors232_read)
{
	if (offset == 5)
		return 0x20;
	return 0;
}

WRITE8_MEMBER(xbox_base_state::superiors232_write)
{
	if (offset == 0)
	{
		printf("%c", data);
	}
}

void xbox_base_state::machine_start()
{
	find_debug_params(machine());
	nvidia_nv2a = machine().device<nv2a_gpu_device>(":pci:1e.0:00.0")->debug_get_renderer();
	memset(pic16lc_buffer, 0, sizeof(pic16lc_buffer));
	pic16lc_buffer[0] = 'B';
	pic16lc_buffer[4] = 0; // A/V connector, 0=scart 2=vga 4=svideo 7=none
>>>>>>> upstream/master
	// PIC challenge handshake data
	pic16lc_buffer[0x1c] = 0x0c;
	pic16lc_buffer[0x1d] = 0x0d;
	pic16lc_buffer[0x1e] = 0x0e;
	pic16lc_buffer[0x1f] = 0x0f;
<<<<<<< HEAD
#ifdef USB_ENABLED
	ohcist.hc_regs[HcRevision] = 0x10;
	ohcist.hc_regs[HcFmInterval] = 0x2edf;
	ohcist.hc_regs[HcLSThreshold] = 0x628;
	ohcist.hc_regs[HcRhDescriptorA] = 4;
	ohcist.interruptbulkratio = 1;
	ohcist.writebackdonehadcounter = 7;
	ohcist.space = &m_maincpu->space();
	ohcist.timer = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(xbox_base_state::usb_ohci_timer), this), (void *)"USB OHCI Timer");
	ohcist.timer->enable(false);
	usb_ohci_plug(1, new ohci_function_device()); // test connect
#endif
	// savestates
	save_item(NAME(debug_irq_active));
	save_item(NAME(debug_irq_number));
	save_item(NAME(smbusst.status));
	save_item(NAME(smbusst.control));
	save_item(NAME(smbusst.address));
	save_item(NAME(smbusst.data));
	save_item(NAME(smbusst.command));
	save_item(NAME(smbusst.rw));
	save_item(NAME(smbusst.words));
	save_item(NAME(pic16lc_buffer));
	nvidia_nv2a->set_interrupt_device(xbox_base_devs.pic8259_1);
	nvidia_nv2a->start(&m_maincpu->space());
	nvidia_nv2a->savestate_items();
}

MACHINE_CONFIG_START(xbox_base, xbox_base_state)

=======
	mcpx_smbus_device *smbus = machine().device<mcpx_smbus_device>(":pci:01.1");
	smbus->register_device(0x10,
		[&](int command, int rw, int data)
	{
		return smbus_pic16lc(command, rw, data);
	}
	);
	smbus->register_device(0x45,
		[&](int command, int rw, int data)
	{
		return smbus_cx25871(command, rw, data);
	}
	);
	smbus->register_device(0x54,
		[&](int command, int rw, int data)
	{
		return smbus_eeprom(command, rw, data);
	}
	);
	xbox_base_devs.pic8259_1 = machine().device<pic8259_device>("pic8259_1");
	xbox_base_devs.pic8259_2 = machine().device<pic8259_device>("pic8259_2");
	xbox_base_devs.ide = machine().device<bus_master_ide_controller_device>("ide");
	if (machine().debug_flags & DEBUG_FLAG_ENABLED)
	{
		using namespace std::placeholders;
		machine().debugger().console().register_command("xbox", CMDFLAG_NONE, 0, 1, 4, std::bind(&xbox_base_state::xbox_debug_commands, this, _1, _2));
	}
	machine().device<mcpx_ohci_device>(":pci:02.0")->set_hack_callback(
		[&](void)
	{
		hack_usb();
	}
	);
	// super-io
	memset(&superiost, 0, sizeof(superiost));
	superiost.configuration_mode = false;
	superiost.registers[0][0x26] = 0x2e; // Configuration port address byte 0
										 // savestates
	save_item(NAME(debug_irq_active));
	save_item(NAME(debug_irq_number));
	save_item(NAME(pic16lc_buffer));
}

ADDRESS_MAP_START(xbox_base_map, AS_PROGRAM, 32, xbox_base_state)
	AM_RANGE(0x00000000, 0x07ffffff) AM_RAM // 128 megabytes
#if 0
	AM_RANGE(0xf0000000, 0xf7ffffff) AM_RAM AM_SHARE("nv2a_share") // 3d accelerator wants this
	AM_RANGE(0xfd000000, 0xfdffffff) AM_RAM AM_READWRITE(geforce_r, geforce_w)
	AM_RANGE(0xfed00000, 0xfed003ff) AM_READWRITE(ohci_usb_r, ohci_usb_w)
	AM_RANGE(0xfed08000, 0xfed083ff) AM_READWRITE(ohci_usb2_r, ohci_usb2_w)
	AM_RANGE(0xfe800000, 0xfe87ffff) AM_READWRITE(audio_apu_r, audio_apu_w)
	AM_RANGE(0xfec00000, 0xfec00fff) AM_READWRITE(audio_ac93_r, audio_ac93_w)
	AM_RANGE(0xfef00000, 0xfef003ff) AM_READWRITE(network_r, network_w)
#endif
ADDRESS_MAP_END

ADDRESS_MAP_START(xbox_base_map_io, AS_IO, 32, xbox_base_state)
	AM_RANGE(0x0020, 0x0023) AM_DEVREADWRITE8("pic8259_1", pic8259_device, read, write, 0xffffffff)
	AM_RANGE(0x002c, 0x002f) AM_READWRITE8(superio_read, superio_write, 0xffff0000)
	AM_RANGE(0x0040, 0x0043) AM_DEVREADWRITE8("pit8254", pit8254_device, read, write, 0xffffffff)
	AM_RANGE(0x00a0, 0x00a3) AM_DEVREADWRITE8("pic8259_2", pic8259_device, read, write, 0xffffffff)
	AM_RANGE(0x01f0, 0x01f7) AM_DEVREADWRITE(":pci:09.0:ide", bus_master_ide_controller_device, read_cs0, write_cs0)
	AM_RANGE(0x03f8, 0x03ff) AM_READWRITE8(superiors232_read, superiors232_write, 0xffffffff)
#if 0
	AM_RANGE(0x0cf8, 0x0cff) AM_DEVREADWRITE("pcibus", pci_bus_legacy_device, read, write)
	AM_RANGE(0x8000, 0x80ff) AM_READWRITE(dummy_r, dummy_w) // lpc bridge
	AM_RANGE(0xc000, 0xc00f) AM_READWRITE(smbus_r, smbus_w)
	AM_RANGE(0xc200, 0xc21f) AM_READWRITE(smbus2_r, smbus2_w)
	AM_RANGE(0xd000, 0xd0ff) AM_NOP // ac97
	AM_RANGE(0xd200, 0xd27f) AM_NOP // ac97
	AM_RANGE(0xe000, 0xe007) AM_READWRITE(networkio_r, networkio_w)
	AM_RANGE(0xff60, 0xff6f) AM_DEVREADWRITE("ide", bus_master_ide_controller_device, bmdma_r, bmdma_w)
#endif
ADDRESS_MAP_END

MACHINE_CONFIG_START(xbox_base)
>>>>>>> upstream/master
	/* basic machine hardware */
	MCFG_CPU_ADD("maincpu", PENTIUM3, 733333333) /* Wrong! family 6 model 8 stepping 10 */
	MCFG_CPU_PROGRAM_MAP(xbox_base_map)
	MCFG_CPU_IO_MAP(xbox_base_map_io)
	MCFG_CPU_IRQ_ACKNOWLEDGE_DRIVER(xbox_base_state, irq_callback)

	MCFG_QUANTUM_TIME(attotime::from_hz(6000))

<<<<<<< HEAD
	MCFG_PCI_BUS_LEGACY_ADD("pcibus", 0)
	MCFG_PCI_BUS_LEGACY_DEVICE(0, "PCI Bridge Device - Host Bridge", dummy_pci_r, dummy_pci_w)
	MCFG_PCI_BUS_LEGACY_DEVICE(1, "HUB Interface - ISA Bridge", hubintiasbridg_pci_r, hubintiasbridg_pci_w)
	MCFG_PCI_BUS_LEGACY_DEVICE(2, "OHCI USB Controller 1", dummy_pci_r, dummy_pci_w)
	MCFG_PCI_BUS_LEGACY_DEVICE(3, "OHCI USB Controller 2", dummy_pci_r, dummy_pci_w)
	MCFG_PCI_BUS_LEGACY_DEVICE(4, "MCP Networking Adapter", dummy_pci_r, dummy_pci_w)
	MCFG_PCI_BUS_LEGACY_DEVICE(5, "MCP APU", dummy_pci_r, dummy_pci_w)
	MCFG_PCI_BUS_LEGACY_DEVICE(6, "AC`97 Audio Codec Interface", dummy_pci_r, dummy_pci_w)
	MCFG_PCI_BUS_LEGACY_DEVICE(9, "IDE Controller", dummy_pci_r, dummy_pci_w)
	MCFG_PCI_BUS_LEGACY_DEVICE(30, "AGP Host to PCI Bridge", dummy_pci_r, dummy_pci_w)
	MCFG_PCI_BUS_LEGACY_ADD("agpbus", 1)
	MCFG_PCI_BUS_LEGACY_SIBLING("pcibus")
	MCFG_PCI_BUS_LEGACY_DEVICE(0, "NV2A GeForce 3MX Integrated GPU/Northbridge", geforce_pci_r, geforce_pci_w)
	MCFG_PIC8259_ADD("pic8259_1", WRITELINE(xbox_base_state, xbox_pic8259_1_set_int_line), VCC, READ8(xbox_base_state, get_slave_ack))
	MCFG_PIC8259_ADD("pic8259_2", DEVWRITELINE("pic8259_1", pic8259_device, ir2_w), GND, NULL)
=======
	MCFG_PCI_ROOT_ADD(  ":pci")
	MCFG_NV2A_HOST_ADD( ":pci:00.0", "maincpu")
	MCFG_PCI_DEVICE_ADD(":pci:00.3", NV2A_RAM, 0x10de02a6, 0, 0, 0)
	MCFG_PCI_DEVICE_ADD(":pci:01.0", MCPX_LPC, 0x10de01b2, 0xb4, 0, 0) // revision id must be at least 0xb4, otherwise usb will require a hub
	MCFG_PCI_DEVICE_ADD(":pci:01.1", MCPX_SMBUS, 0x10de01b4, 0, 0, 0)
	MCFG_MCPX_SMBUS_INTERRUPT_HANDLER(DEVWRITELINE(":", xbox_base_state, xbox_smbus_interrupt_changed))
	MCFG_PCI_DEVICE_ADD(":pci:02.0", MCPX_OHCI, 0x10de01c2, 0, 0, 0)
	MCFG_MCPX_OHCI_INTERRUPT_HANDLER(DEVWRITELINE(":", xbox_base_state, xbox_ohci_usb_interrupt_changed))
	MCFG_PCI_DEVICE_ADD(":pci:03.0", MCPX_OHCI, 0x10de01c2, 0, 0, 0)
	MCFG_PCI_DEVICE_ADD(":pci:04.0", MCPX_ETH, 0x10de01c3, 0, 0, 0)
	MCFG_MCPX_APU_ADD(  ":pci:05.0", "maincpu")
	MCFG_PCI_DEVICE_ADD(":pci:06.0", MCPX_AC97_AUDIO, 0x10de01b1, 0, 0, 0)
	MCFG_PCI_DEVICE_ADD(":pci:06.1", MCPX_AC97_MODEM, 0x10de01c1, 0, 0, 0)
	MCFG_PCI_BRIDGE_ADD(":pci:08.0", 0x10de01b8, 0)
	MCFG_PCI_DEVICE_ADD(":pci:09.0", MCPX_IDE, 0x10de01bc, 0, 0, 0)
	MCFG_MCPX_IDE_INTERRUPT_HANDLER(DEVWRITELINE(":pic8259_2", pic8259_device, ir6_w))
	MCFG_AGP_BRIDGE_ADD(":pci:1e.0", NV2A_AGP, 0x10de01b7, 0)
	MCFG_PCI_DEVICE_ADD(":pci:1e.0:00.0", NV2A_GPU, 0x10de02a0, 0, 0, 0)
	MCFG_MCPX_NV2A_GPU_CPU("maincpu")
	MCFG_MCPX_NV2A_GPU_INTERRUPT_HANDLER(DEVWRITELINE(":", xbox_base_state, xbox_nv2a_interrupt_changed))
	MCFG_PIC8259_ADD("pic8259_1", WRITELINE(xbox_base_state, xbox_pic8259_1_set_int_line), VCC, READ8(xbox_base_state, get_slave_ack))
	MCFG_PIC8259_ADD("pic8259_2", DEVWRITELINE("pic8259_1", pic8259_device, ir2_w), GND, NOOP)
>>>>>>> upstream/master

	MCFG_DEVICE_ADD("pit8254", PIT8254, 0)
	MCFG_PIT8253_CLK0(1125000) /* heartbeat IRQ */
	MCFG_PIT8253_OUT0_HANDLER(WRITELINE(xbox_base_state, xbox_pit8254_out0_changed))
	MCFG_PIT8253_CLK1(1125000) /* (unused) dram refresh */
	MCFG_PIT8253_CLK2(1125000) /* (unused) pio port c pin 4, and speaker polling enough */
	MCFG_PIT8253_OUT2_HANDLER(WRITELINE(xbox_base_state, xbox_pit8254_out2_changed))

<<<<<<< HEAD
	MCFG_DEVICE_ADD("ide", BUS_MASTER_IDE_CONTROLLER, 0)
	MCFG_ATA_INTERFACE_IRQ_HANDLER(DEVWRITELINE("pic8259_2", pic8259_device, ir6_w))
	MCFG_BUS_MASTER_IDE_CONTROLLER_SPACE("maincpu", AS_PROGRAM)

=======
>>>>>>> upstream/master
	/* video hardware */
	MCFG_SCREEN_ADD("screen", RASTER)
	MCFG_SCREEN_REFRESH_RATE(60)
	MCFG_SCREEN_VBLANK_TIME(ATTOSECONDS_IN_USEC(2500))  /* not accurate */
	MCFG_SCREEN_SIZE(640, 480)
	MCFG_SCREEN_VISIBLE_AREA(0, 639, 0, 479)
	MCFG_SCREEN_UPDATE_DRIVER(xbox_base_state, screen_update_callback)
<<<<<<< HEAD
	MCFG_SCREEN_VBLANK_DRIVER(xbox_base_state, vblank_callback)
=======
	MCFG_SCREEN_VBLANK_CALLBACK(WRITELINE(xbox_base_state, vblank_callback))
>>>>>>> upstream/master
MACHINE_CONFIG_END
