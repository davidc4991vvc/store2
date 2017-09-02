// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/*********************************************************************

    debugcmd.c

    Debugger command interface engine.

*********************************************************************/

#include "emu.h"
#include "emuopts.h"
<<<<<<< HEAD
=======
#include "debugger.h"
>>>>>>> upstream/master
#include "debugcmd.h"
#include "debugcon.h"
#include "debugcpu.h"
#include "express.h"
#include "debughlp.h"
#include "debugvw.h"
<<<<<<< HEAD
#include "render.h"
#include <ctype.h>
=======
#include "natkeyboard.h"
#include "render.h"
#include <ctype.h>
#include <fstream>
>>>>>>> upstream/master



/***************************************************************************
    CONSTANTS
***************************************************************************/

<<<<<<< HEAD
#define MAX_GLOBALS     1000



/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

struct global_entry
{
	void *      base;
	UINT32      size;
};


struct cheat_map
{
	UINT64      offset;
	UINT64      first_value;
	UINT64      previous_value;
	UINT8       state:1;
	UINT8       undo:7;
};


struct cheat_system
{
	char        cpu[2];
	UINT8       width;
	std::vector<cheat_map> cheatmap;
	UINT8       undo;
	UINT8       signed_cheat;
	UINT8       swapped_cheat;
};


struct cheat_region_map
{
	UINT64      offset;
	UINT64      endoffset;
	const char *share;
	UINT8       disabled;
};



/***************************************************************************
    GLOBAL VARIABLES
***************************************************************************/

static global_entry global_array[MAX_GLOBALS];
static cheat_system cheat;



/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

static void debug_command_exit(running_machine &machine);

static UINT64 execute_min(symbol_table &table, void *ref, int params, const UINT64 *param);
static UINT64 execute_max(symbol_table &table, void *ref, int params, const UINT64 *param);
static UINT64 execute_if(symbol_table &table, void *ref, int params, const UINT64 *param);

static UINT64 global_get(symbol_table &table, void *ref);
static void global_set(symbol_table &table, void *ref, UINT64 value);

static void execute_help(running_machine &machine, int ref, int params, const char **param);
static void execute_print(running_machine &machine, int ref, int params, const char **param);
static void execute_printf(running_machine &machine, int ref, int params, const char **param);
static void execute_logerror(running_machine &machine, int ref, int params, const char **param);
static void execute_tracelog(running_machine &machine, int ref, int params, const char **param);
static void execute_quit(running_machine &machine, int ref, int params, const char **param);
static void execute_do(running_machine &machine, int ref, int params, const char **param);
static void execute_step(running_machine &machine, int ref, int params, const char **param);
static void execute_over(running_machine &machine, int ref, int params, const char **param);
static void execute_out(running_machine &machine, int ref, int params, const char **param);
static void execute_go(running_machine &machine, int ref, int params, const char **param);
static void execute_go_vblank(running_machine &machine, int ref, int params, const char **param);
static void execute_go_interrupt(running_machine &machine, int ref, int params, const char **param);
static void execute_go_time(running_machine &machine, int ref, int params, const char *param[]);
static void execute_focus(running_machine &machine, int ref, int params, const char **param);
static void execute_ignore(running_machine &machine, int ref, int params, const char **param);
static void execute_observe(running_machine &machine, int ref, int params, const char **param);
static void execute_next(running_machine &machine, int ref, int params, const char **param);
static void execute_comment(running_machine &machine, int ref, int params, const char **param);
static void execute_comment_del(running_machine &machine, int ref, int params, const char **param);
static void execute_comment_save(running_machine &machine, int ref, int params, const char **param);
static void execute_bpset(running_machine &machine, int ref, int params, const char **param);
static void execute_bpclear(running_machine &machine, int ref, int params, const char **param);
static void execute_bpdisenable(running_machine &machine, int ref, int params, const char **param);
static void execute_bplist(running_machine &machine, int ref, int params, const char **param);
static void execute_wpset(running_machine &machine, int ref, int params, const char **param);
static void execute_wpclear(running_machine &machine, int ref, int params, const char **param);
static void execute_wpdisenable(running_machine &machine, int ref, int params, const char **param);
static void execute_wplist(running_machine &machine, int ref, int params, const char **param);
static void execute_rpset(running_machine &machine, int ref, int params, const char **param);
static void execute_rpclear(running_machine &machine, int ref, int params, const char **param);
static void execute_rpdisenable(running_machine &machine, int ref, int params, const char **param);
static void execute_rplist(running_machine &machine, int ref, int params, const char **param);
static void execute_hotspot(running_machine &machine, int ref, int params, const char **param);
static void execute_statesave(running_machine &machine, int ref, int params, const char **param);
static void execute_stateload(running_machine &machine, int ref, int params, const char **param);
static void execute_save(running_machine &machine, int ref, int params, const char **param);
static void execute_load(running_machine &machine, int ref, int params, const char **param);
static void execute_dump(running_machine &machine, int ref, int params, const char **param);
static void execute_cheatinit(running_machine &machine, int ref, int params, const char **param);
static void execute_cheatnext(running_machine &machine, int ref, int params, const char **param);
static void execute_cheatlist(running_machine &machine, int ref, int params, const char **param);
static void execute_cheatundo(running_machine &machine, int ref, int params, const char **param);
static void execute_dasm(running_machine &machine, int ref, int params, const char **param);
static void execute_find(running_machine &machine, int ref, int params, const char **param);
static void execute_trace(running_machine &machine, int ref, int params, const char **param);
static void execute_traceover(running_machine &machine, int ref, int params, const char **param);
static void execute_traceflush(running_machine &machine, int ref, int params, const char **param);
static void execute_history(running_machine &machine, int ref, int params, const char **param);
static void execute_trackpc(running_machine &machine, int ref, int params, const char **param);
static void execute_trackmem(running_machine &machine, int ref, int params, const char **param);
static void execute_pcatmem(running_machine &machine, int ref, int params, const char **param);
static void execute_snap(running_machine &machine, int ref, int params, const char **param);
static void execute_source(running_machine &machine, int ref, int params, const char **param);
static void execute_map(running_machine &machine, int ref, int params, const char **param);
static void execute_memdump(running_machine &machine, int ref, int params, const char **param);
static void execute_symlist(running_machine &machine, int ref, int params, const char **param);
static void execute_softreset(running_machine &machine, int ref, int params, const char **param);
static void execute_hardreset(running_machine &machine, int ref, int params, const char **param);
static void execute_images(running_machine &machine, int ref, int params, const char **param);
static void execute_mount(running_machine &machine, int ref, int params, const char **param);
static void execute_unmount(running_machine &machine, int ref, int params, const char **param);
static void execute_input(running_machine &machine, int ref, int params, const char **param);
static void execute_dumpkbd(running_machine &machine, int ref, int params, const char **param);


/***************************************************************************
    INLINE FUNCTIONS
***************************************************************************/

/*-------------------------------------------------
    cheat_address_is_valid - return TRUE if the
    given address is valid for cheating
-------------------------------------------------*/

INLINE int cheat_address_is_valid(address_space &space, offs_t address)
{
	return debug_cpu_translate(space, TRANSLATE_READ, &address) && (space.get_write_ptr(address) != NULL);
=======
const size_t debugger_commands::MAX_GLOBALS = 1000;

/***************************************************************************
    FUNCTIONS
***************************************************************************/

/*-------------------------------------------------
    cheat_address_is_valid - return true if the
    given address is valid for cheating
-------------------------------------------------*/

bool debugger_commands::cheat_address_is_valid(address_space &space, offs_t address)
{
	return space.device().memory().translate(space.spacenum(), TRANSLATE_READ, address) && (space.get_write_ptr(address) != nullptr);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    cheat_sign_extend - sign-extend a value to
    the current cheat width, if signed
-------------------------------------------------*/

<<<<<<< HEAD
INLINE UINT64 cheat_sign_extend(const cheat_system *cheatsys, UINT64 value)
=======
u64 debugger_commands::cheat_sign_extend(const cheat_system *cheatsys, u64 value)
>>>>>>> upstream/master
{
	if (cheatsys->signed_cheat)
	{
		switch (cheatsys->width)
		{
<<<<<<< HEAD
			case 1: value = (INT8)value;    break;
			case 2: value = (INT16)value;   break;
			case 4: value = (INT32)value;   break;
=======
			case 1: value = s8(value);    break;
			case 2: value = s16(value);   break;
			case 4: value = s32(value);   break;
>>>>>>> upstream/master
		}
	}
	return value;
}
<<<<<<< HEAD
=======

>>>>>>> upstream/master
/*-------------------------------------------------
    cheat_byte_swap - swap a value
-------------------------------------------------*/

<<<<<<< HEAD
INLINE UINT64 cheat_byte_swap(const cheat_system *cheatsys, UINT64 value)
=======
u64 debugger_commands::cheat_byte_swap(const cheat_system *cheatsys, u64 value)
>>>>>>> upstream/master
{
	if (cheatsys->swapped_cheat)
	{
		switch (cheatsys->width)
		{
			case 2: value = ((value >> 8) & 0x00ff) | ((value << 8) & 0xff00);  break;
			case 4: value = ((value >> 24) & 0x000000ff) | ((value >> 8) & 0x0000ff00) | ((value << 8) & 0x00ff0000) | ((value << 24) & 0xff000000);    break;
<<<<<<< HEAD
			case 8: value = ((value >> 56) & U64(0x00000000000000ff)) | ((value >> 40) & U64(0x000000000000ff00)) | ((value >> 24) & U64(0x0000000000ff0000)) | ((value >> 8) & U64(0x00000000ff000000)) |
							((value << 8) & U64(0x000000ff00000000)) | ((value << 24) & U64(0x0000ff0000000000)) | ((value << 40) & U64(0x00ff000000000000)) | ((value << 56) & U64(0xff00000000000000));   break;
=======
			case 8: value = ((value >> 56) & 0x00000000000000ffU) | ((value >> 40) & 0x000000000000ff00U) | ((value >> 24) & 0x0000000000ff0000U) | ((value >> 8) & 0x00000000ff000000U) |
							((value << 8) & 0x000000ff00000000U) | ((value << 24) & 0x0000ff0000000000U) | ((value << 40) & 0x00ff000000000000U) | ((value << 56) & 0xff00000000000000U);   break;
>>>>>>> upstream/master
		}
	}
	return value;
}

/*-------------------------------------------------
    cheat_read_extended - read a value from memory
    in the given address space, sign-extending
    and swapping if necessary
-------------------------------------------------*/

<<<<<<< HEAD
INLINE UINT64 cheat_read_extended(const cheat_system *cheatsys, address_space &space, offs_t address)
{
	return cheat_sign_extend(cheatsys, cheat_byte_swap(cheatsys, debug_read_memory(space, address, cheatsys->width, TRUE)));
}



/***************************************************************************
    INITIALIZATION
***************************************************************************/

/*-------------------------------------------------
    debug_command_init - initializes the command
    system
-------------------------------------------------*/

void debug_command_init(running_machine &machine)
{
	symbol_table *symtable = debug_cpu_get_global_symtable(machine);
	const char *name;
	int itemnum;

	/* add a few simple global functions */
	symtable->add("min", NULL, 2, 2, execute_min);
	symtable->add("max", NULL, 2, 2, execute_max);
	symtable->add("if", NULL, 3, 3, execute_if);

	/* add all single-entry save state globals */
	for (itemnum = 0; itemnum < MAX_GLOBALS; itemnum++)
	{
		UINT32 valsize, valcount;
		void *base;

		/* stop when we run out of items */
		name = machine.save().indexed_item(itemnum, base, valsize, valcount);
		if (name == NULL)
=======
u64 debugger_commands::cheat_read_extended(const cheat_system *cheatsys, address_space &space, offs_t address)
{
	return cheat_sign_extend(cheatsys, cheat_byte_swap(cheatsys, m_cpu.read_memory(space, address, cheatsys->width, true)));
}

debugger_commands::debugger_commands(running_machine& machine, debugger_cpu& cpu, debugger_console& console)
	: m_machine(machine)
	, m_cpu(cpu)
	, m_console(console)
{
	m_global_array = auto_alloc_array_clear(m_machine, global_entry, MAX_GLOBALS);

	symbol_table *symtable = m_cpu.get_global_symtable();

	/* add a few simple global functions */
	using namespace std::placeholders;
	symtable->add("min", nullptr, 2, 2, std::bind(&debugger_commands::execute_min, this, _1, _2, _3, _4));
	symtable->add("max", nullptr, 2, 2, std::bind(&debugger_commands::execute_max, this, _1, _2, _3, _4));
	symtable->add("if", nullptr, 3, 3, std::bind(&debugger_commands::execute_if, this, _1, _2, _3, _4));

	/* add all single-entry save state globals */
	for (int itemnum = 0; itemnum < MAX_GLOBALS; itemnum++)
	{
		u32 valsize, valcount;
		void *base;

		/* stop when we run out of items */
		const char* name = m_machine.save().indexed_item(itemnum, base, valsize, valcount);
		if (name == nullptr)
>>>>>>> upstream/master
			break;

		/* if this is a single-entry global, add it */
		if (valcount == 1 && strstr(name, "/globals/"))
		{
			char symname[100];
			sprintf(symname, ".%s", strrchr(name, '/') + 1);
<<<<<<< HEAD
			global_array[itemnum].base = base;
			global_array[itemnum].size = valsize;
			symtable->add(symname, &global_array, global_get, global_set);
=======
			m_global_array[itemnum].base = base;
			m_global_array[itemnum].size = valsize;
			symtable->add(symname, &m_global_array, std::bind(&debugger_commands::global_get, this, _1, _2), std::bind(&debugger_commands::global_set, this, _1, _2, _3));
>>>>>>> upstream/master
		}
	}

	/* add all the commands */
<<<<<<< HEAD
	debug_console_register_command(machine, "help",      CMDFLAG_NONE, 0, 0, 1, execute_help);
	debug_console_register_command(machine, "print",     CMDFLAG_NONE, 0, 1, MAX_COMMAND_PARAMS, execute_print);
	debug_console_register_command(machine, "printf",    CMDFLAG_NONE, 0, 1, MAX_COMMAND_PARAMS, execute_printf);
	debug_console_register_command(machine, "logerror",  CMDFLAG_NONE, 0, 1, MAX_COMMAND_PARAMS, execute_logerror);
	debug_console_register_command(machine, "tracelog",  CMDFLAG_NONE, 0, 1, MAX_COMMAND_PARAMS, execute_tracelog);
	debug_console_register_command(machine, "quit",      CMDFLAG_NONE, 0, 0, 0, execute_quit);
	debug_console_register_command(machine, "exit",      CMDFLAG_NONE, 0, 0, 0, execute_quit);
	debug_console_register_command(machine, "do",        CMDFLAG_NONE, 0, 1, 1, execute_do);
	debug_console_register_command(machine, "step",      CMDFLAG_NONE, 0, 0, 1, execute_step);
	debug_console_register_command(machine, "s",         CMDFLAG_NONE, 0, 0, 1, execute_step);
	debug_console_register_command(machine, "over",      CMDFLAG_NONE, 0, 0, 1, execute_over);
	debug_console_register_command(machine, "o",         CMDFLAG_NONE, 0, 0, 1, execute_over);
	debug_console_register_command(machine, "out" ,      CMDFLAG_NONE, 0, 0, 0, execute_out);
	debug_console_register_command(machine, "go",        CMDFLAG_NONE, 0, 0, 1, execute_go);
	debug_console_register_command(machine, "g",         CMDFLAG_NONE, 0, 0, 1, execute_go);
	debug_console_register_command(machine, "gvblank",   CMDFLAG_NONE, 0, 0, 0, execute_go_vblank);
	debug_console_register_command(machine, "gv",        CMDFLAG_NONE, 0, 0, 0, execute_go_vblank);
	debug_console_register_command(machine, "gint",      CMDFLAG_NONE, 0, 0, 1, execute_go_interrupt);
	debug_console_register_command(machine, "gi",        CMDFLAG_NONE, 0, 0, 1, execute_go_interrupt);
	debug_console_register_command(machine, "gtime",     CMDFLAG_NONE, 0, 0, 1, execute_go_time);
	debug_console_register_command(machine, "gt",        CMDFLAG_NONE, 0, 0, 1, execute_go_time);
	debug_console_register_command(machine, "next",      CMDFLAG_NONE, 0, 0, 0, execute_next);
	debug_console_register_command(machine, "n",         CMDFLAG_NONE, 0, 0, 0, execute_next);
	debug_console_register_command(machine, "focus",     CMDFLAG_NONE, 0, 1, 1, execute_focus);
	debug_console_register_command(machine, "ignore",    CMDFLAG_NONE, 0, 0, MAX_COMMAND_PARAMS, execute_ignore);
	debug_console_register_command(machine, "observe",   CMDFLAG_NONE, 0, 0, MAX_COMMAND_PARAMS, execute_observe);

	debug_console_register_command(machine, "comadd",    CMDFLAG_NONE, 0, 1, 2, execute_comment);
	debug_console_register_command(machine, "//",        CMDFLAG_NONE, 0, 1, 2, execute_comment);
	debug_console_register_command(machine, "comdelete", CMDFLAG_NONE, 0, 1, 1, execute_comment_del);
	debug_console_register_command(machine, "comsave",   CMDFLAG_NONE, 0, 0, 0, execute_comment_save);

	debug_console_register_command(machine, "bpset",     CMDFLAG_NONE, 0, 1, 3, execute_bpset);
	debug_console_register_command(machine, "bp",        CMDFLAG_NONE, 0, 1, 3, execute_bpset);
	debug_console_register_command(machine, "bpclear",   CMDFLAG_NONE, 0, 0, 1, execute_bpclear);
	debug_console_register_command(machine, "bpdisable", CMDFLAG_NONE, 0, 0, 1, execute_bpdisenable);
	debug_console_register_command(machine, "bpenable",  CMDFLAG_NONE, 1, 0, 1, execute_bpdisenable);
	debug_console_register_command(machine, "bplist",    CMDFLAG_NONE, 0, 0, 0, execute_bplist);

	debug_console_register_command(machine, "wpset",     CMDFLAG_NONE, AS_PROGRAM, 3, 5, execute_wpset);
	debug_console_register_command(machine, "wp",        CMDFLAG_NONE, AS_PROGRAM, 3, 5, execute_wpset);
	debug_console_register_command(machine, "wpdset",    CMDFLAG_NONE, AS_DATA, 3, 5, execute_wpset);
	debug_console_register_command(machine, "wpd",       CMDFLAG_NONE, AS_DATA, 3, 5, execute_wpset);
	debug_console_register_command(machine, "wpiset",    CMDFLAG_NONE, AS_IO, 3, 5, execute_wpset);
	debug_console_register_command(machine, "wpi",       CMDFLAG_NONE, AS_IO, 3, 5, execute_wpset);
	debug_console_register_command(machine, "wpclear",   CMDFLAG_NONE, 0, 0, 1, execute_wpclear);
	debug_console_register_command(machine, "wpdisable", CMDFLAG_NONE, 0, 0, 1, execute_wpdisenable);
	debug_console_register_command(machine, "wpenable",  CMDFLAG_NONE, 1, 0, 1, execute_wpdisenable);
	debug_console_register_command(machine, "wplist",    CMDFLAG_NONE, 0, 0, 0, execute_wplist);

	debug_console_register_command(machine, "rpset",     CMDFLAG_NONE, 0, 1, 2, execute_rpset);
	debug_console_register_command(machine, "rp",        CMDFLAG_NONE, 0, 1, 2, execute_rpset);
	debug_console_register_command(machine, "rpclear",   CMDFLAG_NONE, 0, 0, 1, execute_rpclear);
	debug_console_register_command(machine, "rpdisable", CMDFLAG_NONE, 0, 0, 1, execute_rpdisenable);
	debug_console_register_command(machine, "rpenable",  CMDFLAG_NONE, 1, 0, 1, execute_rpdisenable);
	debug_console_register_command(machine, "rplist",    CMDFLAG_NONE, 0, 0, 0, execute_rplist);

	debug_console_register_command(machine, "hotspot",   CMDFLAG_NONE, 0, 0, 3, execute_hotspot);

	debug_console_register_command(machine, "statesave", CMDFLAG_NONE, 0, 1, 1, execute_statesave);
	debug_console_register_command(machine, "ss",        CMDFLAG_NONE, 0, 1, 1, execute_statesave);
	debug_console_register_command(machine, "stateload", CMDFLAG_NONE, 0, 1, 1, execute_stateload);
	debug_console_register_command(machine, "sl",        CMDFLAG_NONE, 0, 1, 1, execute_stateload);

	debug_console_register_command(machine, "save",      CMDFLAG_NONE, AS_PROGRAM, 3, 4, execute_save);
	debug_console_register_command(machine, "saved",     CMDFLAG_NONE, AS_DATA, 3, 4, execute_save);
	debug_console_register_command(machine, "savei",     CMDFLAG_NONE, AS_IO, 3, 4, execute_save);

	debug_console_register_command(machine, "load",      CMDFLAG_NONE, AS_PROGRAM, 3, 4, execute_load);
	debug_console_register_command(machine, "loadd",     CMDFLAG_NONE, AS_DATA, 3, 4, execute_load);
	debug_console_register_command(machine, "loadi",     CMDFLAG_NONE, AS_IO, 3, 4, execute_load);

	debug_console_register_command(machine, "dump",      CMDFLAG_NONE, AS_PROGRAM, 3, 6, execute_dump);
	debug_console_register_command(machine, "dumpd",     CMDFLAG_NONE, AS_DATA, 3, 6, execute_dump);
	debug_console_register_command(machine, "dumpi",     CMDFLAG_NONE, AS_IO, 3, 6, execute_dump);

	debug_console_register_command(machine, "cheatinit", CMDFLAG_NONE, 0, 0, 4, execute_cheatinit);
	debug_console_register_command(machine, "ci",        CMDFLAG_NONE, 0, 0, 4, execute_cheatinit);

	debug_console_register_command(machine, "cheatrange",CMDFLAG_NONE, 1, 2, 2, execute_cheatinit);
	debug_console_register_command(machine, "cr",        CMDFLAG_NONE, 1, 2, 2, execute_cheatinit);

	debug_console_register_command(machine, "cheatnext", CMDFLAG_NONE, 0, 1, 2, execute_cheatnext);
	debug_console_register_command(machine, "cn",        CMDFLAG_NONE, 0, 1, 2, execute_cheatnext);
	debug_console_register_command(machine, "cheatnextf",CMDFLAG_NONE, 1, 1, 2, execute_cheatnext);
	debug_console_register_command(machine, "cnf",       CMDFLAG_NONE, 1, 1, 2, execute_cheatnext);

	debug_console_register_command(machine, "cheatlist", CMDFLAG_NONE, 0, 0, 1, execute_cheatlist);
	debug_console_register_command(machine, "cl",        CMDFLAG_NONE, 0, 0, 1, execute_cheatlist);

	debug_console_register_command(machine, "cheatundo", CMDFLAG_NONE, 0, 0, 0, execute_cheatundo);
	debug_console_register_command(machine, "cu",        CMDFLAG_NONE, 0, 0, 0, execute_cheatundo);

	debug_console_register_command(machine, "f",         CMDFLAG_KEEP_QUOTES, AS_PROGRAM, 3, MAX_COMMAND_PARAMS, execute_find);
	debug_console_register_command(machine, "find",      CMDFLAG_KEEP_QUOTES, AS_PROGRAM, 3, MAX_COMMAND_PARAMS, execute_find);
	debug_console_register_command(machine, "fd",        CMDFLAG_KEEP_QUOTES, AS_DATA, 3, MAX_COMMAND_PARAMS, execute_find);
	debug_console_register_command(machine, "findd",     CMDFLAG_KEEP_QUOTES, AS_DATA, 3, MAX_COMMAND_PARAMS, execute_find);
	debug_console_register_command(machine, "fi",        CMDFLAG_KEEP_QUOTES, AS_IO, 3, MAX_COMMAND_PARAMS, execute_find);
	debug_console_register_command(machine, "findi",     CMDFLAG_KEEP_QUOTES, AS_IO, 3, MAX_COMMAND_PARAMS, execute_find);

	debug_console_register_command(machine, "dasm",      CMDFLAG_NONE, 0, 3, 5, execute_dasm);

	debug_console_register_command(machine, "trace",     CMDFLAG_NONE, 0, 1, 3, execute_trace);
	debug_console_register_command(machine, "traceover", CMDFLAG_NONE, 0, 1, 3, execute_traceover);
	debug_console_register_command(machine, "traceflush",CMDFLAG_NONE, 0, 0, 0, execute_traceflush);

	debug_console_register_command(machine, "history",   CMDFLAG_NONE, 0, 0, 2, execute_history);
	debug_console_register_command(machine, "trackpc",   CMDFLAG_NONE, 0, 0, 3, execute_trackpc);

	debug_console_register_command(machine, "trackmem",  CMDFLAG_NONE, 0, 0, 3, execute_trackmem);
	debug_console_register_command(machine, "pcatmemp",  CMDFLAG_NONE, AS_PROGRAM, 1, 2, execute_pcatmem);
	debug_console_register_command(machine, "pcatmemd",  CMDFLAG_NONE, AS_DATA,    1, 2, execute_pcatmem);
	debug_console_register_command(machine, "pcatmemi",  CMDFLAG_NONE, AS_IO,      1, 2, execute_pcatmem);

	debug_console_register_command(machine, "snap",      CMDFLAG_NONE, 0, 0, 1, execute_snap);

	debug_console_register_command(machine, "source",    CMDFLAG_NONE, 0, 1, 1, execute_source);

	debug_console_register_command(machine, "map",       CMDFLAG_NONE, AS_PROGRAM, 1, 1, execute_map);
	debug_console_register_command(machine, "mapd",      CMDFLAG_NONE, AS_DATA, 1, 1, execute_map);
	debug_console_register_command(machine, "mapi",      CMDFLAG_NONE, AS_IO, 1, 1, execute_map);
	debug_console_register_command(machine, "memdump",   CMDFLAG_NONE, 0, 0, 1, execute_memdump);

	debug_console_register_command(machine, "symlist",   CMDFLAG_NONE, 0, 0, 1, execute_symlist);

	debug_console_register_command(machine, "softreset", CMDFLAG_NONE, 0, 0, 1, execute_softreset);
	debug_console_register_command(machine, "hardreset", CMDFLAG_NONE, 0, 0, 1, execute_hardreset);

	debug_console_register_command(machine, "images",    CMDFLAG_NONE, 0, 0, 0, execute_images);
	debug_console_register_command(machine, "mount",     CMDFLAG_NONE, 0, 2, 2, execute_mount);
	debug_console_register_command(machine, "unmount",   CMDFLAG_NONE, 0, 1, 1, execute_unmount);

	debug_console_register_command(machine, "input",     CMDFLAG_NONE, 0, 1, 1, execute_input);
	debug_console_register_command(machine, "dumpkbd",   CMDFLAG_NONE, 0, 0, 1, execute_dumpkbd);

	machine.add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(FUNC(debug_command_exit), &machine));

	/* set up the initial debugscript if specified */
	name = machine.options().debug_script();
	if (name[0] != 0)
		debug_cpu_source_script(machine, name);

	cheat.cpu[0] = cheat.cpu[1] = 0;
}


/*-------------------------------------------------
    debug_command_exit - exit-time cleanup
-------------------------------------------------*/

static void debug_command_exit(running_machine &machine)
{
}



/***************************************************************************
    GLOBAL FUNCTIONS
***************************************************************************/

=======
	m_console.register_command("help",      CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_help, this, _1, _2));
	m_console.register_command("print",     CMDFLAG_NONE, 0, 1, MAX_COMMAND_PARAMS, std::bind(&debugger_commands::execute_print, this, _1, _2));
	m_console.register_command("printf",    CMDFLAG_NONE, 0, 1, MAX_COMMAND_PARAMS, std::bind(&debugger_commands::execute_printf, this, _1, _2));
	m_console.register_command("logerror",  CMDFLAG_NONE, 0, 1, MAX_COMMAND_PARAMS, std::bind(&debugger_commands::execute_logerror, this, _1, _2));
	m_console.register_command("tracelog",  CMDFLAG_NONE, 0, 1, MAX_COMMAND_PARAMS, std::bind(&debugger_commands::execute_tracelog, this, _1, _2));
	m_console.register_command("tracesym",  CMDFLAG_NONE, 0, 1, MAX_COMMAND_PARAMS, std::bind(&debugger_commands::execute_tracesym, this, _1, _2));
	m_console.register_command("quit",      CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_quit, this, _1, _2));
	m_console.register_command("exit",      CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_quit, this, _1, _2));
	m_console.register_command("do",        CMDFLAG_NONE, 0, 1, 1, std::bind(&debugger_commands::execute_do, this, _1, _2));
	m_console.register_command("step",      CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_step, this, _1, _2));
	m_console.register_command("s",         CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_step, this, _1, _2));
	m_console.register_command("over",      CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_over, this, _1, _2));
	m_console.register_command("o",         CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_over, this, _1, _2));
	m_console.register_command("out" ,      CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_out, this, _1, _2));
	m_console.register_command("go",        CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_go, this, _1, _2));
	m_console.register_command("g",         CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_go, this, _1, _2));
	m_console.register_command("gvblank",   CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_go_vblank, this, _1, _2));
	m_console.register_command("gv",        CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_go_vblank, this, _1, _2));
	m_console.register_command("gint",      CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_go_interrupt, this, _1, _2));
	m_console.register_command("gi",        CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_go_interrupt, this, _1, _2));
	m_console.register_command("gtime",     CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_go_time, this, _1, _2));
	m_console.register_command("gt",        CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_go_time, this, _1, _2));
	m_console.register_command("next",      CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_next, this, _1, _2));
	m_console.register_command("n",         CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_next, this, _1, _2));
	m_console.register_command("focus",     CMDFLAG_NONE, 0, 1, 1, std::bind(&debugger_commands::execute_focus, this, _1, _2));
	m_console.register_command("ignore",    CMDFLAG_NONE, 0, 0, MAX_COMMAND_PARAMS, std::bind(&debugger_commands::execute_ignore, this, _1, _2));
	m_console.register_command("observe",   CMDFLAG_NONE, 0, 0, MAX_COMMAND_PARAMS, std::bind(&debugger_commands::execute_observe, this, _1, _2));

	m_console.register_command("comadd",    CMDFLAG_NONE, 0, 1, 2, std::bind(&debugger_commands::execute_comment_add, this, _1, _2));
	m_console.register_command("//",        CMDFLAG_NONE, 0, 1, 2, std::bind(&debugger_commands::execute_comment_add, this, _1, _2));
	m_console.register_command("comdelete", CMDFLAG_NONE, 0, 1, 1, std::bind(&debugger_commands::execute_comment_del, this, _1, _2));
	m_console.register_command("comsave",   CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_comment_save, this, _1, _2));
	m_console.register_command("comlist",   CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_comment_list, this, _1, _2));
	m_console.register_command("commit",    CMDFLAG_NONE, 0, 1, 2, std::bind(&debugger_commands::execute_comment_commit, this, _1, _2));
	m_console.register_command("/*",        CMDFLAG_NONE, 0, 1, 2, std::bind(&debugger_commands::execute_comment_commit, this, _1, _2));

	m_console.register_command("bpset",     CMDFLAG_NONE, 0, 1, 3, std::bind(&debugger_commands::execute_bpset, this, _1, _2));
	m_console.register_command("bp",        CMDFLAG_NONE, 0, 1, 3, std::bind(&debugger_commands::execute_bpset, this, _1, _2));
	m_console.register_command("bpclear",   CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_bpclear, this, _1, _2));
	m_console.register_command("bpdisable", CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_bpdisenable, this, _1, _2));
	m_console.register_command("bpenable",  CMDFLAG_NONE, 1, 0, 1, std::bind(&debugger_commands::execute_bpdisenable, this, _1, _2));
	m_console.register_command("bplist",    CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_bplist, this, _1, _2));

	m_console.register_command("wpset",     CMDFLAG_NONE, AS_PROGRAM, 3, 5, std::bind(&debugger_commands::execute_wpset, this, _1, _2));
	m_console.register_command("wp",        CMDFLAG_NONE, AS_PROGRAM, 3, 5, std::bind(&debugger_commands::execute_wpset, this, _1, _2));
	m_console.register_command("wpdset",    CMDFLAG_NONE, AS_DATA, 3, 5, std::bind(&debugger_commands::execute_wpset, this, _1, _2));
	m_console.register_command("wpd",       CMDFLAG_NONE, AS_DATA, 3, 5, std::bind(&debugger_commands::execute_wpset, this, _1, _2));
	m_console.register_command("wpiset",    CMDFLAG_NONE, AS_IO, 3, 5, std::bind(&debugger_commands::execute_wpset, this, _1, _2));
	m_console.register_command("wpi",       CMDFLAG_NONE, AS_IO, 3, 5, std::bind(&debugger_commands::execute_wpset, this, _1, _2));
	m_console.register_command("wposet",    CMDFLAG_NONE, AS_OPCODES, 3, 5, std::bind(&debugger_commands::execute_wpset, this, _1, _2));
	m_console.register_command("wpo",       CMDFLAG_NONE, AS_OPCODES, 3, 5, std::bind(&debugger_commands::execute_wpset, this, _1, _2));
	m_console.register_command("wpclear",   CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_wpclear, this, _1, _2));
	m_console.register_command("wpdisable", CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_wpdisenable, this, _1, _2));
	m_console.register_command("wpenable",  CMDFLAG_NONE, 1, 0, 1, std::bind(&debugger_commands::execute_wpdisenable, this, _1, _2));
	m_console.register_command("wplist",    CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_wplist, this, _1, _2));

	m_console.register_command("rpset",     CMDFLAG_NONE, 0, 1, 2, std::bind(&debugger_commands::execute_rpset, this, _1, _2));
	m_console.register_command("rp",        CMDFLAG_NONE, 0, 1, 2, std::bind(&debugger_commands::execute_rpset, this, _1, _2));
	m_console.register_command("rpclear",   CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_rpclear, this, _1, _2));
	m_console.register_command("rpdisable", CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_rpdisenable, this, _1, _2));
	m_console.register_command("rpenable",  CMDFLAG_NONE, 1, 0, 1, std::bind(&debugger_commands::execute_rpdisenable, this, _1, _2));
	m_console.register_command("rplist",    CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_rplist, this, _1, _2));

	m_console.register_command("hotspot",   CMDFLAG_NONE, 0, 0, 3, std::bind(&debugger_commands::execute_hotspot, this, _1, _2));

	m_console.register_command("statesave", CMDFLAG_NONE, 0, 1, 1, std::bind(&debugger_commands::execute_statesave, this, _1, _2));
	m_console.register_command("ss",        CMDFLAG_NONE, 0, 1, 1, std::bind(&debugger_commands::execute_statesave, this, _1, _2));
	m_console.register_command("stateload", CMDFLAG_NONE, 0, 1, 1, std::bind(&debugger_commands::execute_stateload, this, _1, _2));
	m_console.register_command("sl",        CMDFLAG_NONE, 0, 1, 1, std::bind(&debugger_commands::execute_stateload, this, _1, _2));

	m_console.register_command("save",      CMDFLAG_NONE, AS_PROGRAM, 3, 4, std::bind(&debugger_commands::execute_save, this, _1, _2));
	m_console.register_command("saved",     CMDFLAG_NONE, AS_DATA, 3, 4, std::bind(&debugger_commands::execute_save, this, _1, _2));
	m_console.register_command("savei",     CMDFLAG_NONE, AS_IO, 3, 4, std::bind(&debugger_commands::execute_save, this, _1, _2));
	m_console.register_command("saveo",     CMDFLAG_NONE, AS_OPCODES, 3, 4, std::bind(&debugger_commands::execute_save, this, _1, _2));

	m_console.register_command("load",      CMDFLAG_NONE, AS_PROGRAM, 2, 4, std::bind(&debugger_commands::execute_load, this, _1, _2));
	m_console.register_command("loadd",     CMDFLAG_NONE, AS_DATA, 2, 4, std::bind(&debugger_commands::execute_load, this, _1, _2));
	m_console.register_command("loadi",     CMDFLAG_NONE, AS_IO, 2, 4, std::bind(&debugger_commands::execute_load, this, _1, _2));
	m_console.register_command("loado",     CMDFLAG_NONE, AS_OPCODES, 2, 4, std::bind(&debugger_commands::execute_load, this, _1, _2));

	m_console.register_command("dump",      CMDFLAG_NONE, AS_PROGRAM, 3, 7, std::bind(&debugger_commands::execute_dump, this, _1, _2));
	m_console.register_command("dumpd",     CMDFLAG_NONE, AS_DATA, 3, 7, std::bind(&debugger_commands::execute_dump, this, _1, _2));
	m_console.register_command("dumpi",     CMDFLAG_NONE, AS_IO, 3, 7, std::bind(&debugger_commands::execute_dump, this, _1, _2));
	m_console.register_command("dumpo",     CMDFLAG_NONE, AS_OPCODES, 3, 7, std::bind(&debugger_commands::execute_dump, this, _1, _2));

	m_console.register_command("cheatinit", CMDFLAG_NONE, 0, 0, 4, std::bind(&debugger_commands::execute_cheatinit, this, _1, _2));
	m_console.register_command("ci",        CMDFLAG_NONE, 0, 0, 4, std::bind(&debugger_commands::execute_cheatinit, this, _1, _2));

	m_console.register_command("cheatrange",CMDFLAG_NONE, 1, 2, 2, std::bind(&debugger_commands::execute_cheatinit, this, _1, _2));
	m_console.register_command("cr",        CMDFLAG_NONE, 1, 2, 2, std::bind(&debugger_commands::execute_cheatinit, this, _1, _2));

	m_console.register_command("cheatnext", CMDFLAG_NONE, 0, 1, 2, std::bind(&debugger_commands::execute_cheatnext, this, _1, _2));
	m_console.register_command("cn",        CMDFLAG_NONE, 0, 1, 2, std::bind(&debugger_commands::execute_cheatnext, this, _1, _2));
	m_console.register_command("cheatnextf",CMDFLAG_NONE, 1, 1, 2, std::bind(&debugger_commands::execute_cheatnext, this, _1, _2));
	m_console.register_command("cnf",       CMDFLAG_NONE, 1, 1, 2, std::bind(&debugger_commands::execute_cheatnext, this, _1, _2));

	m_console.register_command("cheatlist", CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_cheatlist, this, _1, _2));
	m_console.register_command("cl",        CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_cheatlist, this, _1, _2));

	m_console.register_command("cheatundo", CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_cheatundo, this, _1, _2));
	m_console.register_command("cu",        CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_cheatundo, this, _1, _2));

	m_console.register_command("f",         CMDFLAG_KEEP_QUOTES, AS_PROGRAM, 3, MAX_COMMAND_PARAMS, std::bind(&debugger_commands::execute_find, this, _1, _2));
	m_console.register_command("find",      CMDFLAG_KEEP_QUOTES, AS_PROGRAM, 3, MAX_COMMAND_PARAMS, std::bind(&debugger_commands::execute_find, this, _1, _2));
	m_console.register_command("fd",        CMDFLAG_KEEP_QUOTES, AS_DATA, 3, MAX_COMMAND_PARAMS, std::bind(&debugger_commands::execute_find, this, _1, _2));
	m_console.register_command("findd",     CMDFLAG_KEEP_QUOTES, AS_DATA, 3, MAX_COMMAND_PARAMS, std::bind(&debugger_commands::execute_find, this, _1, _2));
	m_console.register_command("fi",        CMDFLAG_KEEP_QUOTES, AS_IO, 3, MAX_COMMAND_PARAMS, std::bind(&debugger_commands::execute_find, this, _1, _2));
	m_console.register_command("findi",     CMDFLAG_KEEP_QUOTES, AS_IO, 3, MAX_COMMAND_PARAMS, std::bind(&debugger_commands::execute_find, this, _1, _2));
	m_console.register_command("fo",        CMDFLAG_KEEP_QUOTES, AS_OPCODES, 3, MAX_COMMAND_PARAMS, std::bind(&debugger_commands::execute_find, this, _1, _2));
	m_console.register_command("findo",     CMDFLAG_KEEP_QUOTES, AS_OPCODES, 3, MAX_COMMAND_PARAMS, std::bind(&debugger_commands::execute_find, this, _1, _2));

	m_console.register_command("dasm",      CMDFLAG_NONE, 0, 3, 5, std::bind(&debugger_commands::execute_dasm, this, _1, _2));

	m_console.register_command("trace",     CMDFLAG_NONE, 0, 1, 4, std::bind(&debugger_commands::execute_trace, this, _1, _2));
	m_console.register_command("traceover", CMDFLAG_NONE, 0, 1, 4, std::bind(&debugger_commands::execute_traceover, this, _1, _2));
	m_console.register_command("traceflush",CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_traceflush, this, _1, _2));

	m_console.register_command("history",   CMDFLAG_NONE, 0, 0, 2, std::bind(&debugger_commands::execute_history, this, _1, _2));
	m_console.register_command("trackpc",   CMDFLAG_NONE, 0, 0, 3, std::bind(&debugger_commands::execute_trackpc, this, _1, _2));

	m_console.register_command("trackmem",  CMDFLAG_NONE, 0, 0, 3, std::bind(&debugger_commands::execute_trackmem, this, _1, _2));
	m_console.register_command("pcatmemp",  CMDFLAG_NONE, AS_PROGRAM, 1, 2, std::bind(&debugger_commands::execute_pcatmem, this, _1, _2));
	m_console.register_command("pcatmemd",  CMDFLAG_NONE, AS_DATA,    1, 2, std::bind(&debugger_commands::execute_pcatmem, this, _1, _2));
	m_console.register_command("pcatmemi",  CMDFLAG_NONE, AS_IO,      1, 2, std::bind(&debugger_commands::execute_pcatmem, this, _1, _2));
	m_console.register_command("pcatmemo",  CMDFLAG_NONE, AS_OPCODES, 1, 2, std::bind(&debugger_commands::execute_pcatmem, this, _1, _2));

	m_console.register_command("snap",      CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_snap, this, _1, _2));

	m_console.register_command("source",    CMDFLAG_NONE, 0, 1, 1, std::bind(&debugger_commands::execute_source, this, _1, _2));

	m_console.register_command("map",       CMDFLAG_NONE, AS_PROGRAM, 1, 1, std::bind(&debugger_commands::execute_map, this, _1, _2));
	m_console.register_command("mapd",      CMDFLAG_NONE, AS_DATA, 1, 1, std::bind(&debugger_commands::execute_map, this, _1, _2));
	m_console.register_command("mapi",      CMDFLAG_NONE, AS_IO, 1, 1, std::bind(&debugger_commands::execute_map, this, _1, _2));
	m_console.register_command("mapo",      CMDFLAG_NONE, AS_OPCODES, 1, 1, std::bind(&debugger_commands::execute_map, this, _1, _2));
	m_console.register_command("memdump",   CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_memdump, this, _1, _2));

	m_console.register_command("symlist",   CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_symlist, this, _1, _2));

	m_console.register_command("softreset", CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_softreset, this, _1, _2));
	m_console.register_command("hardreset", CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_hardreset, this, _1, _2));

	m_console.register_command("images",    CMDFLAG_NONE, 0, 0, 0, std::bind(&debugger_commands::execute_images, this, _1, _2));
	m_console.register_command("mount",     CMDFLAG_NONE, 0, 2, 2, std::bind(&debugger_commands::execute_mount, this, _1, _2));
	m_console.register_command("unmount",   CMDFLAG_NONE, 0, 1, 1, std::bind(&debugger_commands::execute_unmount, this, _1, _2));

	m_console.register_command("input",     CMDFLAG_NONE, 0, 1, 1, std::bind(&debugger_commands::execute_input, this, _1, _2));
	m_console.register_command("dumpkbd",   CMDFLAG_NONE, 0, 0, 1, std::bind(&debugger_commands::execute_dumpkbd, this, _1, _2));

	/* set up the initial debugscript if specified */
	const char* name = m_machine.options().debug_script();
	if (name[0] != 0)
		m_cpu.source_script(name);

	m_cheat.cpu[0] = m_cheat.cpu[1] = 0;
}

>>>>>>> upstream/master
/*-------------------------------------------------
    execute_min - return the minimum of two values
-------------------------------------------------*/

<<<<<<< HEAD
static UINT64 execute_min(symbol_table &table, void *ref, int params, const UINT64 *param)
=======
u64 debugger_commands::execute_min(symbol_table &table, void *ref, int params, const u64 *param)
>>>>>>> upstream/master
{
	return (param[0] < param[1]) ? param[0] : param[1];
}


/*-------------------------------------------------
    execute_max - return the maximum of two values
-------------------------------------------------*/

<<<<<<< HEAD
static UINT64 execute_max(symbol_table &table, void *ref, int params, const UINT64 *param)
=======
u64 debugger_commands::execute_max(symbol_table &table, void *ref, int params, const u64 *param)
>>>>>>> upstream/master
{
	return (param[0] > param[1]) ? param[0] : param[1];
}


/*-------------------------------------------------
    execute_if - if (a) return b; else return c;
-------------------------------------------------*/

<<<<<<< HEAD
static UINT64 execute_if(symbol_table &table, void *ref, int params, const UINT64 *param)
=======
u64 debugger_commands::execute_if(symbol_table &table, void *ref, int params, const u64 *param)
>>>>>>> upstream/master
{
	return param[0] ? param[1] : param[2];
}



/***************************************************************************
    GLOBAL ACCESSORS
***************************************************************************/

/*-------------------------------------------------
    global_get - symbol table getter for globals
-------------------------------------------------*/

<<<<<<< HEAD
static UINT64 global_get(symbol_table &table, void *ref)
=======
u64 debugger_commands::global_get(symbol_table &table, void *ref)
>>>>>>> upstream/master
{
	global_entry *global = (global_entry *)ref;
	switch (global->size)
	{
<<<<<<< HEAD
		case 1:     return *(UINT8 *)global->base;
		case 2:     return *(UINT16 *)global->base;
		case 4:     return *(UINT32 *)global->base;
		case 8:     return *(UINT64 *)global->base;
=======
		case 1:     return *(u8 *)global->base;
		case 2:     return *(u16 *)global->base;
		case 4:     return *(u32 *)global->base;
		case 8:     return *(u64 *)global->base;
>>>>>>> upstream/master
	}
	return ~0;
}


/*-------------------------------------------------
    global_set - symbol table setter for globals
-------------------------------------------------*/

<<<<<<< HEAD
static void global_set(symbol_table &table, void *ref, UINT64 value)
=======
void debugger_commands::global_set(symbol_table &table, void *ref, u64 value)
>>>>>>> upstream/master
{
	global_entry *global = (global_entry *)ref;
	switch (global->size)
	{
<<<<<<< HEAD
		case 1:     *(UINT8 *)global->base = value; break;
		case 2:     *(UINT16 *)global->base = value;    break;
		case 4:     *(UINT32 *)global->base = value;    break;
		case 8:     *(UINT64 *)global->base = value;    break;
=======
		case 1:     *(u8 *)global->base = value; break;
		case 2:     *(u16 *)global->base = value;    break;
		case 4:     *(u32 *)global->base = value;    break;
		case 8:     *(u64 *)global->base = value;    break;
>>>>>>> upstream/master
	}
}



/***************************************************************************
    PARAMETER VALIDATION HELPERS
***************************************************************************/

/*-------------------------------------------------
<<<<<<< HEAD
    debug_command_parameter_number - validates a
    number parameter
-------------------------------------------------*/

int debug_command_parameter_number(running_machine &machine, const char *param, UINT64 *result)
{
	/* NULL parameter does nothing and returns no error */
	if (param == NULL)
		return TRUE;

	/* evaluate the expression; success if no error */
	try
	{
		parsed_expression expression(debug_cpu_get_visible_symtable(machine), param, result);
		return TRUE;
=======
    validate_number_parameter - validates a
    number parameter
-------------------------------------------------*/

bool debugger_commands::validate_number_parameter(const std::string &param, u64 &result)
{
	/* evaluate the expression; success if no error */
	try
	{
		parsed_expression expression(m_cpu.get_visible_symtable(), param.c_str(), &result);
		return true;
>>>>>>> upstream/master
	}
	catch (expression_error &error)
	{
		/* print an error pointing to the character that caused it */
<<<<<<< HEAD
		debug_console_printf(machine, "Error in expression: %s\n", param);
		debug_console_printf(machine, "                     %*s^", error.offset(), "");
		debug_console_printf(machine, "%s\n", error.code_string());
		return FALSE;
=======
		m_console.printf("Error in expression: %s\n", param);
		m_console.printf("                     %*s^", error.offset(), "");
		m_console.printf("%s\n", error.code_string());
		return false;
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
<<<<<<< HEAD
    debug_command_parameter_cpu - validates a
    parameter as a cpu
-------------------------------------------------*/

int debug_command_parameter_cpu(running_machine &machine, const char *param, device_t **result)
{
	UINT64 cpunum;

	/* if no parameter, use the visible CPU */
	if (param == NULL)
	{
		*result = debug_cpu_get_visible_cpu(machine);
		if (*result == NULL)
		{
			debug_console_printf(machine, "No valid CPU is currently selected\n");
			return FALSE;
		}
		return TRUE;
	}

	/* first look for a tag match */
	*result = machine.device(param);
	if (*result != NULL)
		return TRUE;

	/* then evaluate as an expression; on an error assume it was a tag */
	try
	{
		parsed_expression expression(debug_cpu_get_visible_symtable(machine), param, &cpunum);
	}
	catch (expression_error &)
	{
		debug_console_printf(machine, "Unable to find CPU '%s'\n", param);
		return FALSE;
	}

	/* if we got a valid one, return */
	const UINT64 original_cpunum = cpunum;
	execute_interface_iterator iter(machine.root_device());
	for (device_execute_interface *exec = iter.first(); exec != NULL; exec = iter.next())
	{
		if (cpunum-- == 0)
		{
			*result = &exec->device();
			return TRUE;
		}
	}

	/* if out of range, complain */
	debug_console_printf(machine, "Invalid CPU index %d\n", (UINT32)original_cpunum);
	return FALSE;
=======
    validate_boolean_parameter - validates a
    boolean parameter
-------------------------------------------------*/

bool debugger_commands::validate_boolean_parameter(const std::string &param, bool &result)
{
	/* nullptr parameter does nothing and returns no error */
	if (param.empty())
		return true;

	/* evaluate the expression; success if no error */
	bool is_true = core_stricmp(param.c_str(), "true") == 0 || param == "1";
	bool is_false = core_stricmp(param.c_str(), "false") == 0 || param == "0";

	if (!is_true && !is_false)
	{
		m_console.printf("Invalid boolean '%s'\n", param);
		return false;
	}

	result = is_true;

	return true;
}


/*-------------------------------------------------
    validate_cpu_parameter - validates a
    parameter as a cpu
-------------------------------------------------*/

bool debugger_commands::validate_cpu_parameter(const char *param, device_t *&result)
{
	/* if no parameter, use the visible CPU */
	if (param == nullptr)
	{
		result = m_cpu.get_visible_cpu();
		if (!result)
		{
			m_console.printf("No valid CPU is currently selected\n");
			return false;
		}
		return true;
	}

	/* first look for a tag match */
	result = m_machine.device(param);
	if (result)
		return true;

	/* then evaluate as an expression; on an error assume it was a tag */
	u64 cpunum;
	try
	{
		parsed_expression expression(m_cpu.get_visible_symtable(), param, &cpunum);
	}
	catch (expression_error &)
	{
		m_console.printf("Unable to find CPU '%s'\n", param);
		return false;
	}

	/* if we got a valid one, return */
	device_execute_interface *exec = execute_interface_iterator(m_machine.root_device()).byindex(cpunum);
	if (exec != nullptr)
	{
		result = &exec->device();
		return true;
	}

	/* if out of range, complain */
	m_console.printf("Invalid CPU index %d\n", (int)cpunum);
	return false;
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    debug_command_parameter_cpu_space - validates
=======
    validate_cpu_space_parameter - validates
>>>>>>> upstream/master
    a parameter as a cpu and retrieves the given
    address space
-------------------------------------------------*/

<<<<<<< HEAD
int debug_command_parameter_cpu_space(running_machine &machine, const char *param, int spacenum, address_space *&result)
{
	device_t *cpu;

	/* first do the standard CPU thing */
	if (!debug_command_parameter_cpu(machine, param, &cpu))
		return FALSE;
=======
bool debugger_commands::validate_cpu_space_parameter(const char *param, int spacenum, address_space *&result)
{
	/* first do the standard CPU thing */
	device_t *cpu;
	if (!validate_cpu_parameter(param, cpu))
		return false;
>>>>>>> upstream/master

	/* fetch the space pointer */
	if (!cpu->memory().has_space(spacenum))
	{
<<<<<<< HEAD
		debug_console_printf(machine, "No matching memory space found for CPU '%s'\n", cpu->tag());
		return FALSE;
	}
	result = &cpu->memory().space(spacenum);
	return TRUE;
=======
		m_console.printf("No matching memory space found for CPU '%s'\n", cpu->tag());
		return false;
	}
	result = &cpu->memory().space(spacenum);
	return true;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    debug_command_parameter_expression - validates
    an expression parameter
-------------------------------------------------*/

<<<<<<< HEAD
static int debug_command_parameter_expression(running_machine &machine, const char *param, parsed_expression &result)
{
	/* NULL parameter does nothing and returns no error */
	if (param == NULL)
		return TRUE;

	/* parse the expression; success if no error */
	try
	{
		result.parse(param);
		return TRUE;
=======
bool debugger_commands::debug_command_parameter_expression(const std::string &param, parsed_expression &result)
{
	/* parse the expression; success if no error */
	try
	{
		result.parse(param.c_str());
		return true;
>>>>>>> upstream/master
	}
	catch (expression_error &err)
	{
		/* output an error */
<<<<<<< HEAD
		debug_console_printf(machine, "Error in expression: %s\n", param);
		debug_console_printf(machine, "                     %*s^", err.offset(), "");
		debug_console_printf(machine, "%s\n", err.code_string());
		return FALSE;
=======
		m_console.printf("Error in expression: %s\n", param);
		m_console.printf("                     %*s^", err.offset(), "");
		m_console.printf("%s\n", err.code_string());
		return false;
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
    debug_command_parameter_command - validates a
    command parameter
-------------------------------------------------*/

<<<<<<< HEAD
static int debug_command_parameter_command(running_machine &machine, const char *param)
{
	CMDERR err;

	/* NULL parameter does nothing and returns no error */
	if (param == NULL)
		return TRUE;

	/* validate the comment; success if no error */
	err = debug_console_validate_command(machine, param);
	if (err == CMDERR_NONE)
		return TRUE;

	/* output an error */
	debug_console_printf(machine, "Error in command: %s\n", param);
	debug_console_printf(machine, "                  %*s^", CMDERR_ERROR_OFFSET(err), "");
	debug_console_printf(machine, "%s\n", debug_cmderr_to_string(err));
	return 0;
}



/***************************************************************************
    COMMAND HELPERS
***************************************************************************/

=======
bool debugger_commands::debug_command_parameter_command(const char *param)
{
	/* nullptr parameter does nothing and returns no error */
	if (param == nullptr)
		return true;

	/* validate the comment; success if no error */
	CMDERR err = m_console.validate_command(param);
	if (err == CMDERR_NONE)
		return true;

	/* output an error */
	m_console.printf("Error in command: %s\n", param);
	m_console.printf("                  %*s^", CMDERR_ERROR_OFFSET(err), "");
	m_console.printf("%s\n", debugger_console::cmderr_to_string(err));
	return 0;
}

>>>>>>> upstream/master
/*-------------------------------------------------
    execute_help - execute the help command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_help(running_machine &machine, int ref, int params, const char *param[])
{
	if (params == 0)
		debug_console_printf_wrap(machine, 80, "%s\n", debug_get_help(""));
	else
		debug_console_printf_wrap(machine, 80, "%s\n", debug_get_help(param[0]));
=======
void debugger_commands::execute_help(int ref, const std::vector<std::string> &params)
{
	if (params.size() == 0)
		m_console.printf_wrap(80, "%s\n", debug_get_help(""));
	else
		m_console.printf_wrap(80, "%s\n", debug_get_help(params[0].c_str()));
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_print - execute the print command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_print(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 values[MAX_COMMAND_PARAMS];
	int i;

	/* validate the other parameters */
	for (i = 0; i < params; i++)
		if (!debug_command_parameter_number(machine, param[i], &values[i]))
			return;

	/* then print each one */
	for (i = 0; i < params; i++)
		debug_console_printf(machine, "%s", core_i64_hex_format(values[i], 0));
	debug_console_printf(machine, "\n");
=======
void debugger_commands::execute_print(int ref, const std::vector<std::string> &params)
{
	/* validate the other parameters */
	u64 values[MAX_COMMAND_PARAMS];
	for (int i = 0; i < params.size(); i++)
		if (!validate_number_parameter(params[i], values[i]))
			return;

	/* then print each one */
	for (int i = 0; i < params.size(); i++)
		m_console.printf("%X", values[i]);
	m_console.printf("\n");
>>>>>>> upstream/master
}


/*-------------------------------------------------
    mini_printf - safe printf to a buffer
-------------------------------------------------*/

<<<<<<< HEAD
static int mini_printf(running_machine &machine, char *buffer, const char *format, int params, UINT64 *param)
=======
int debugger_commands::mini_printf(char *buffer, const char *format, int params, u64 *param)
>>>>>>> upstream/master
{
	const char *f = format;
	char *p = buffer;

	/* parse the string looking for % signs */
	for (;;)
	{
		char c = *f++;
		if (!c) break;

		/* escape sequences */
		if (c == '\\')
		{
			c = *f++;
			if (!c) break;
			switch (c)
			{
				case '\\':  *p++ = c;       break;
				case 'n':   *p++ = '\n';    break;
				default:                    break;
			}
			continue;
		}

		/* formatting */
		else if (c == '%')
		{
			int width = 0;
			int zerofill = 0;

			/* parse out the width */
			for (;;)
			{
				c = *f++;
				if (!c || c < '0' || c > '9') break;
				if (c == '0' && width == 0)
					zerofill = 1;
				width = width * 10 + (c - '0');
			}
			if (!c) break;

			/* get the format */
			switch (c)
			{
				case '%':
					*p++ = c;
					break;

				case 'X':
				case 'x':
					if (params == 0)
					{
<<<<<<< HEAD
						debug_console_printf(machine, "Not enough parameters for format!\n");
						return 0;
					}
					if ((UINT32)(*param >> 32) != 0)
						p += sprintf(p, zerofill ? "%0*X" : "%*X", (width <= 8) ? 1 : width - 8, (UINT32)(*param >> 32));
					else if (width > 8)
						p += sprintf(p, zerofill ? "%0*X" : "%*X", width - 8, 0);
					p += sprintf(p, zerofill ? "%0*X" : "%*X", (width < 8) ? width : 8, (UINT32)*param);
=======
						m_console.printf("Not enough parameters for format!\n");
						return 0;
					}
					if (u32(*param >> 32) != 0)
						p += sprintf(p, zerofill ? "%0*X" : "%*X", (width <= 8) ? 1 : width - 8, u32(*param >> 32));
					else if (width > 8)
						p += sprintf(p, zerofill ? "%0*X" : "%*X", width - 8, 0);
					p += sprintf(p, zerofill ? "%0*X" : "%*X", (width < 8) ? width : 8, u32(*param));
>>>>>>> upstream/master
					param++;
					params--;
					break;

				case 'D':
				case 'd':
					if (params == 0)
					{
<<<<<<< HEAD
						debug_console_printf(machine, "Not enough parameters for format!\n");
						return 0;
					}
					p += sprintf(p, zerofill ? "%0*d" : "%*d", width, (UINT32)*param);
=======
						m_console.printf("Not enough parameters for format!\n");
						return 0;
					}
					p += sprintf(p, zerofill ? "%0*d" : "%*d", width, u32(*param));
>>>>>>> upstream/master
					param++;
					params--;
					break;
			}
		}

		/* normal stuff */
		else
			*p++ = c;
	}

	/* NULL-terminate and exit */
	*p = 0;
	return 1;
}


/*-------------------------------------------------
    execute_printf - execute the printf command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_printf(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 values[MAX_COMMAND_PARAMS];
	char buffer[1024];
	int i;

	/* validate the other parameters */
	for (i = 1; i < params; i++)
		if (!debug_command_parameter_number(machine, param[i], &values[i]))
			return;

	/* then do a printf */
	if (mini_printf(machine, buffer, param[0], params - 1, &values[1]))
		debug_console_printf(machine, "%s\n", buffer);
=======
void debugger_commands::execute_printf(int ref, const std::vector<std::string> &params)
{
	/* validate the other parameters */
	u64 values[MAX_COMMAND_PARAMS];
	for (int i = 1; i < params.size(); i++)
		if (!validate_number_parameter(params[i], values[i]))
			return;

	/* then do a printf */
	char buffer[1024];
	if (mini_printf(buffer, params[0].c_str(), params.size() - 1, &values[1]))
		m_console.printf("%s\n", buffer);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_logerror - execute the logerror command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_logerror(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 values[MAX_COMMAND_PARAMS];
	char buffer[1024];
	int i;

	/* validate the other parameters */
	for (i = 1; i < params; i++)
		if (!debug_command_parameter_number(machine, param[i], &values[i]))
			return;

	/* then do a printf */
	if (mini_printf(machine, buffer, param[0], params - 1, &values[1]))
		machine.logerror("%s", buffer);
=======
void debugger_commands::execute_logerror(int ref, const std::vector<std::string> &params)
{
	/* validate the other parameters */
	u64 values[MAX_COMMAND_PARAMS];
	for (int i = 1; i < params.size(); i++)
		if (!validate_number_parameter(params[i], values[i]))
			return;

	/* then do a printf */
	char buffer[1024];
	if (mini_printf(buffer, params[0].c_str(), params.size() - 1, &values[1]))
		m_machine.logerror("%s", buffer);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_tracelog - execute the tracelog command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_tracelog(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 values[MAX_COMMAND_PARAMS];
	char buffer[1024];
	int i;

	/* validate the other parameters */
	for (i = 1; i < params; i++)
		if (!debug_command_parameter_number(machine, param[i], &values[i]))
			return;

	/* then do a printf */
	if (mini_printf(machine, buffer, param[0], params - 1, &values[1]))
		debug_cpu_get_visible_cpu(machine)->debug()->trace_printf("%s", buffer);
=======
void debugger_commands::execute_tracelog(int ref, const std::vector<std::string> &params)
{
	/* validate the other parameters */
	u64 values[MAX_COMMAND_PARAMS];
	for (int i = 1; i < params.size(); i++)
		if (!validate_number_parameter(params[i], values[i]))
			return;

	/* then do a printf */
	char buffer[1024];
	if (mini_printf(buffer, params[0].c_str(), params.size() - 1, &values[1]))
		m_cpu.get_visible_cpu()->debug()->trace_printf("%s", buffer);
}


/*-------------------------------------------------
    execute_tracesym - execute the tracesym command
-------------------------------------------------*/

void debugger_commands::execute_tracesym(int ref, const std::vector<std::string> &params)
{
	// build a format string appropriate for the parameters and validate them
	std::stringstream format;
	u64 values[MAX_COMMAND_PARAMS];
	for (int i = 0; i < params.size(); i++)
	{
		// find this symbol
		symbol_entry *sym = m_cpu.get_visible_symtable()->find(params[i].c_str());
		if (!sym)
		{
			m_console.printf("Unknown symbol: %s\n", params[i].c_str());
			return;
		}

		// build the format string
		util::stream_format(format, "%s=%s ",
			params[i],
			sym->format().empty() ? "%16X" : sym->format());

		// validate the parameter
		if (!validate_number_parameter(params[i], values[i]))
			return;
	}

	// then do a printf
	char buffer[1024];
	if (mini_printf(buffer, format.str().c_str(), params.size(), values))
		m_cpu.get_visible_cpu()->debug()->trace_printf("%s", buffer);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_quit - execute the quit command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_quit(running_machine &machine, int ref, int params, const char *param[])
{
	osd_printf_error("Exited via the debugger\n");
	machine.schedule_exit();
=======
void debugger_commands::execute_quit(int ref, const std::vector<std::string> &params)
{
	osd_printf_error("Exited via the debugger\n");
	m_machine.schedule_exit();
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_do - execute the do command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_do(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 dummy;
	debug_command_parameter_number(machine, param[0], &dummy);
=======
void debugger_commands::execute_do(int ref, const std::vector<std::string> &params)
{
	u64 dummy;
	validate_number_parameter(params[0], dummy);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_step - execute the step command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_step(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 steps = 1;

	/* if we have a parameter, use it instead */
	if (!debug_command_parameter_number(machine, param[0], &steps))
		return;

	debug_cpu_get_visible_cpu(machine)->debug()->single_step(steps);
=======
void debugger_commands::execute_step(int ref, const std::vector<std::string> &params)
{
	/* if we have a parameter, use it */
	u64 steps = 1;
	if (params.size() > 0 && !validate_number_parameter(params[0], steps))
		return;

	m_cpu.get_visible_cpu()->debug()->single_step(steps);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_over - execute the over command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_over(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 steps = 1;

	/* if we have a parameter, use it instead */
	if (!debug_command_parameter_number(machine, param[0], &steps))
		return;

	debug_cpu_get_visible_cpu(machine)->debug()->single_step_over(steps);
=======
void debugger_commands::execute_over(int ref, const std::vector<std::string> &params)
{
	/* if we have a parameter, use it */
	u64 steps = 1;
	if (params.size() > 0 && !validate_number_parameter(params[0], steps))
		return;

	m_cpu.get_visible_cpu()->debug()->single_step_over(steps);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_out - execute the out command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_out(running_machine &machine, int ref, int params, const char *param[])
{
	debug_cpu_get_visible_cpu(machine)->debug()->single_step_out();
=======
void debugger_commands::execute_out(int ref, const std::vector<std::string> &params)
{
	m_cpu.get_visible_cpu()->debug()->single_step_out();
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_go - execute the go command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_go(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 addr = ~0;

	/* if we have a parameter, use it instead */
	if (!debug_command_parameter_number(machine, param[0], &addr))
		return;

	debug_cpu_get_visible_cpu(machine)->debug()->go(addr);
=======
void debugger_commands::execute_go(int ref, const std::vector<std::string> &params)
{
	u64 addr = ~0;

	/* if we have a parameter, use it instead */
	if (params.size() > 0 && !validate_number_parameter(params[0], addr))
		return;

	m_cpu.get_visible_cpu()->debug()->go(addr);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_go_vblank - execute the govblank
    command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_go_vblank(running_machine &machine, int ref, int params, const char *param[])
{
	debug_cpu_get_visible_cpu(machine)->debug()->go_vblank();
=======
void debugger_commands::execute_go_vblank(int ref, const std::vector<std::string> &params)
{
	m_cpu.get_visible_cpu()->debug()->go_vblank();
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_go_interrupt - execute the goint command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_go_interrupt(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 irqline = -1;

	/* if we have a parameter, use it instead */
	if (!debug_command_parameter_number(machine, param[0], &irqline))
		return;

	debug_cpu_get_visible_cpu(machine)->debug()->go_interrupt(irqline);
=======
void debugger_commands::execute_go_interrupt(int ref, const std::vector<std::string> &params)
{
	u64 irqline = -1;

	/* if we have a parameter, use it instead */
	if (params.size() > 0 && !validate_number_parameter(params[0], irqline))
		return;

	m_cpu.get_visible_cpu()->debug()->go_interrupt(irqline);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_go_time - execute the gtime command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_go_time(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 milliseconds = -1;

	/* if we have a parameter, use it instead */
	if (!debug_command_parameter_number(machine, param[0], &milliseconds))
		return;

	debug_cpu_get_visible_cpu(machine)->debug()->go_milliseconds(milliseconds);
=======
void debugger_commands::execute_go_time(int ref, const std::vector<std::string> &params)
{
	u64 milliseconds = -1;

	/* if we have a parameter, use it instead */
	if (params.size() > 0 && !validate_number_parameter(params[0], milliseconds))
		return;

	m_cpu.get_visible_cpu()->debug()->go_milliseconds(milliseconds);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_next - execute the next command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_next(running_machine &machine, int ref, int params, const char *param[])
{
	debug_cpu_get_visible_cpu(machine)->debug()->go_next_device();
=======
void debugger_commands::execute_next(int ref, const std::vector<std::string> &params)
{
	m_cpu.get_visible_cpu()->debug()->go_next_device();
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_focus - execute the focus command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_focus(running_machine &machine, int ref, int params, const char *param[])
{
	/* validate params */
	device_t *cpu;
	if (!debug_command_parameter_cpu(machine, param[0], &cpu))
=======
void debugger_commands::execute_focus(int ref, const std::vector<std::string> &params)
{
	/* validate params */
	device_t *cpu;
	if (!validate_cpu_parameter(params[0].c_str(), cpu))
>>>>>>> upstream/master
		return;

	/* first clear the ignore flag on the focused CPU */
	cpu->debug()->ignore(false);

	/* then loop over CPUs and set the ignore flags on all other CPUs */
<<<<<<< HEAD
	execute_interface_iterator iter(machine.root_device());
	for (device_execute_interface *exec = iter.first(); exec != NULL; exec = iter.next())
		if (&exec->device() != cpu)
			exec->device().debug()->ignore(true);
	debug_console_printf(machine, "Now focused on CPU '%s'\n", cpu->tag());
=======
	for (device_execute_interface &exec : execute_interface_iterator(m_machine.root_device()))
		if (&exec.device() != cpu)
			exec.device().debug()->ignore(true);
	m_console.printf("Now focused on CPU '%s'\n", cpu->tag());
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_ignore - execute the ignore command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_ignore(running_machine &machine, int ref, int params, const char *param[])
{
	/* if there are no parameters, dump the ignore list */
	if (params == 0)
=======
void debugger_commands::execute_ignore(int ref, const std::vector<std::string> &params)
{
	/* if there are no parameters, dump the ignore list */
	if (params.empty())
>>>>>>> upstream/master
	{
		std::string buffer;

		/* loop over all executable devices */
<<<<<<< HEAD
		execute_interface_iterator iter(machine.root_device());
		for (device_execute_interface *exec = iter.first(); exec != NULL; exec = iter.next())

			/* build up a comma-separated list */
			if (!exec->device().debug()->observing())
			{
				if (buffer.empty())
					strprintf(buffer, "Currently ignoring device '%s'", exec->device().tag());
				else
					strcatprintf(buffer, ", '%s'", exec->device().tag());
=======
		for (device_execute_interface &exec : execute_interface_iterator(m_machine.root_device()))

			/* build up a comma-separated list */
			if (!exec.device().debug()->observing())
			{
				if (buffer.empty())
					buffer = string_format("Currently ignoring device '%s'", exec.device().tag());
				else
					buffer.append(string_format(", '%s'", exec.device().tag()));
>>>>>>> upstream/master
			}

		/* special message for none */
		if (buffer.empty())
<<<<<<< HEAD
			strprintf(buffer, "Not currently ignoring any devices");
		debug_console_printf(machine, "%s\n", buffer.c_str());
=======
			buffer = string_format("Not currently ignoring any devices");
		m_console.printf("%s\n", buffer.c_str());
>>>>>>> upstream/master
	}

	/* otherwise clear the ignore flag on all requested CPUs */
	else
	{
		device_t *devicelist[MAX_COMMAND_PARAMS];

		/* validate parameters */
<<<<<<< HEAD
		for (int paramnum = 0; paramnum < params; paramnum++)
			if (!debug_command_parameter_cpu(machine, param[paramnum], &devicelist[paramnum]))
				return;

		/* set the ignore flags */
		for (int paramnum = 0; paramnum < params; paramnum++)
		{
			/* make sure this isn't the last live CPU */
			execute_interface_iterator iter(machine.root_device());
			bool gotone = false;
			for (device_execute_interface *exec = iter.first(); exec != NULL; exec = iter.next())
				if (&exec->device() != devicelist[paramnum] && exec->device().debug()->observing())
=======
		for (int paramnum = 0; paramnum < params.size(); paramnum++)
			if (!validate_cpu_parameter(params[paramnum].c_str(), devicelist[paramnum]))
				return;

		/* set the ignore flags */
		for (int paramnum = 0; paramnum < params.size(); paramnum++)
		{
			/* make sure this isn't the last live CPU */
			bool gotone = false;
			for (device_execute_interface &exec : execute_interface_iterator(m_machine.root_device()))
				if (&exec.device() != devicelist[paramnum] && exec.device().debug()->observing())
>>>>>>> upstream/master
				{
					gotone = true;
					break;
				}
			if (!gotone)
			{
<<<<<<< HEAD
				debug_console_printf(machine, "Can't ignore all devices!\n");
=======
				m_console.printf("Can't ignore all devices!\n");
>>>>>>> upstream/master
				return;
			}

			devicelist[paramnum]->debug()->ignore(true);
<<<<<<< HEAD
			debug_console_printf(machine, "Now ignoring device '%s'\n", devicelist[paramnum]->tag());
=======
			m_console.printf("Now ignoring device '%s'\n", devicelist[paramnum]->tag());
>>>>>>> upstream/master
		}
	}
}


/*-------------------------------------------------
    execute_observe - execute the observe command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_observe(running_machine &machine, int ref, int params, const char *param[])
{
	/* if there are no parameters, dump the ignore list */
	if (params == 0)
=======
void debugger_commands::execute_observe(int ref, const std::vector<std::string> &params)
{
	/* if there are no parameters, dump the ignore list */
	if (params.empty())
>>>>>>> upstream/master
	{
		std::string buffer;

		/* loop over all executable devices */
<<<<<<< HEAD
		execute_interface_iterator iter(machine.root_device());
		for (device_execute_interface *exec = iter.first(); exec != NULL; exec = iter.next())

			/* build up a comma-separated list */
			if (exec->device().debug()->observing())
			{
				if (buffer.empty())
					strprintf(buffer, "Currently observing CPU '%s'", exec->device().tag());
				else
					strcatprintf(buffer, ", '%s'", exec->device().tag());
=======
		for (device_execute_interface &exec : execute_interface_iterator(m_machine.root_device()))

			/* build up a comma-separated list */
			if (exec.device().debug()->observing())
			{
				if (buffer.empty())
					buffer = string_format("Currently observing CPU '%s'", exec.device().tag());
				else
					buffer.append(string_format(", '%s'", exec.device().tag()));
>>>>>>> upstream/master
			}

		/* special message for none */
		if (buffer.empty())
<<<<<<< HEAD
			strprintf(buffer, "Not currently observing any devices");
		debug_console_printf(machine, "%s\n", buffer.c_str());
=======
			buffer = string_format("Not currently observing any devices");
		m_console.printf("%s\n", buffer.c_str());
>>>>>>> upstream/master
	}

	/* otherwise set the ignore flag on all requested CPUs */
	else
	{
		device_t *devicelist[MAX_COMMAND_PARAMS];

		/* validate parameters */
<<<<<<< HEAD
		for (int paramnum = 0; paramnum < params; paramnum++)
			if (!debug_command_parameter_cpu(machine, param[paramnum], &devicelist[paramnum]))
				return;

		/* clear the ignore flags */
		for (int paramnum = 0; paramnum < params; paramnum++)
		{
			devicelist[paramnum]->debug()->ignore(false);
			debug_console_printf(machine, "Now observing device '%s'\n", devicelist[paramnum]->tag());
=======
		for (int paramnum = 0; paramnum < params.size(); paramnum++)
			if (!validate_cpu_parameter(params[paramnum].c_str(), devicelist[paramnum]))
				return;

		/* clear the ignore flags */
		for (int paramnum = 0; paramnum < params.size(); paramnum++)
		{
			devicelist[paramnum]->debug()->ignore(false);
			m_console.printf("Now observing device '%s'\n", devicelist[paramnum]->tag());
>>>>>>> upstream/master
		}
	}
}


/*-------------------------------------------------
    execute_comment - add a comment to a line
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_comment(running_machine &machine, int ref, int params, const char *param[])
{
	device_t *cpu;
	UINT64 address;

	/* param 1 is the address for the comment */
	if (!debug_command_parameter_number(machine, param[0], &address))
		return;

	/* CPU parameter is implicit */
	if (!debug_command_parameter_cpu(machine, NULL, &cpu))
		return;

	/* make sure param 2 exists */
	if (strlen(param[1]) == 0)
	{
		debug_console_printf(machine, "Error : comment text empty\n");
=======
void debugger_commands::execute_comment_add(int ref, const std::vector<std::string> &params)
{
	device_t *cpu;
	u64 address;

	/* param 1 is the address for the comment */
	if (!validate_number_parameter(params[0], address))
		return;

	/* CPU parameter is implicit */
	if (!validate_cpu_parameter(nullptr, cpu))
		return;

	/* make sure param 2 exists */
	if (params[1].empty())
	{
		m_console.printf("Error : comment text empty\n");
>>>>>>> upstream/master
		return;
	}

	/* Now try adding the comment */
<<<<<<< HEAD
	cpu->debug()->comment_add(address, param[1], 0x00ff0000);
=======
	cpu->debug()->comment_add(address, params[1].c_str(), 0x00ff0000);
>>>>>>> upstream/master
	cpu->machine().debug_view().update_all(DVT_DISASSEMBLY);
}


/*------------------------------------------------------
    execute_comment_del - remove a comment from an addr
--------------------------------------------------------*/

<<<<<<< HEAD
static void execute_comment_del(running_machine &machine, int ref, int params, const char *param[])
{
	device_t *cpu;
	UINT64 address;

	/* param 1 can either be a command or the address for the comment */
	if (!debug_command_parameter_number(machine, param[0], &address))
		return;

	/* CPU parameter is implicit */
	if (!debug_command_parameter_cpu(machine, NULL, &cpu))
=======
void debugger_commands::execute_comment_del(int ref, const std::vector<std::string> &params)
{
	device_t *cpu;
	u64 address;

	/* param 1 can either be a command or the address for the comment */
	if (!validate_number_parameter(params[0], address))
		return;

	/* CPU parameter is implicit */
	if (!validate_cpu_parameter(nullptr, cpu))
>>>>>>> upstream/master
		return;

	/* If it's a number, it must be an address */
	/* The bankoff and cbn will be pulled from what's currently active */
	cpu->debug()->comment_remove(address);
	cpu->machine().debug_view().update_all(DVT_DISASSEMBLY);
}

<<<<<<< HEAD
=======
/**
 * @fn void execute_comment_list(running_machine &machine, int ref, int params, const char *param[])
 * @brief Print current list of comments in debugger
 *
 *
 */

void debugger_commands::execute_comment_list(int ref, const std::vector<std::string> &params)
{
	if (!m_machine.debugger().cpu().comment_load(false))
		m_console.printf("Error while parsing XML file\n");
}

/**
 * @fn void execute_comment_commit(running_machine &machine, int ref, int params, const char *param[])
 * @brief Add and Save current list of comments in debugger
 *
 */

void debugger_commands::execute_comment_commit(int ref, const std::vector<std::string> &params)
{
	execute_comment_add(ref, params);
	execute_comment_save(ref, params);
}
>>>>>>> upstream/master

/*-------------------------------------------------
    execute_comment - add a comment to a line
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_comment_save(running_machine &machine, int ref, int params, const char *param[])
{
	if (debug_comment_save(machine))
		debug_console_printf(machine, "Comments successfully saved\n");
	else
		debug_console_printf(machine, "Comments not saved\n");
}

=======
void debugger_commands::execute_comment_save(int ref, const std::vector<std::string> &params)
{
	if (m_cpu.comment_save())
		m_console.printf("Comment successfully saved\n");
	else
		m_console.printf("Comment not saved\n");
}

// TODO: add color hex editing capabilities for comments, see below for more info
/**
 * @fn void execute_comment_color(running_machine &machine, int ref, int params, const char *param[])
 * @brief Modifies comment given at address $xx with given color
 * Useful for marking comment with a different color scheme (for example by marking start and end of a given function visually).
 * @param[in] "address,color" First is the comment address in the current context, color can be hexadecimal or shorthanded to common 1bpp RGB names.
 *
 * @todo check if the comment exists in the first place, bail out with error if not.
 * @todo add shorthand for color modify and save
 *
 */


>>>>>>> upstream/master

/*-------------------------------------------------
    execute_bpset - execute the breakpoint set
    command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_bpset(running_machine &machine, int ref, int params, const char *param[])
{
	device_t *cpu;
	const char *action = NULL;
	UINT64 address;
	int bpnum;

	/* CPU is implicit */
	if (!debug_command_parameter_cpu(machine, NULL, &cpu))
		return;

	/* param 1 is the address */
	if (!debug_command_parameter_number(machine, param[0], &address))
=======
void debugger_commands::execute_bpset(int ref, const std::vector<std::string> &params)
{
	device_t *cpu;
	u64 address;
	int bpnum;
	const char *action = nullptr;

	/* CPU is implicit */
	if (!validate_cpu_parameter(nullptr, cpu))
		return;

	/* param 1 is the address */
	if (!validate_number_parameter(params[0], address))
>>>>>>> upstream/master
		return;

	/* param 2 is the condition */
	parsed_expression condition(&cpu->debug()->symtable());
<<<<<<< HEAD
	if (!debug_command_parameter_expression(machine, param[1], condition))
		return;

	/* param 3 is the action */
	if (!debug_command_parameter_command(machine, action = param[2]))
		return;

	/* set the breakpoint */
	bpnum = cpu->debug()->breakpoint_set(address, (condition.is_empty()) ? NULL : condition.original_string(), action);
	debug_console_printf(machine, "Breakpoint %X set\n", bpnum);
=======
	if (params.size() > 1 && !debug_command_parameter_expression(params[1], condition))
		return;

	/* param 3 is the action */
	if (params.size() > 2 && !debug_command_parameter_command(action = params[2].c_str()))
		return;

	/* set the breakpoint */
	bpnum = cpu->debug()->breakpoint_set(address, (condition.is_empty()) ? nullptr : condition.original_string(), action);
	m_console.printf("Breakpoint %X set\n", bpnum);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_bpclear - execute the breakpoint
    clear command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_bpclear(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 bpindex;

	/* if 0 parameters, clear all */
	if (params == 0)
	{
		device_iterator iter(machine.root_device());
		for (device_t *device = iter.first(); device != NULL; device = iter.next())
			device->debug()->breakpoint_clear_all();
		debug_console_printf(machine, "Cleared all breakpoints\n");
	}

	/* otherwise, clear the specific one */
	else if (!debug_command_parameter_number(machine, param[0], &bpindex))
		return;
	else
	{
		device_iterator iter(machine.root_device());
		bool found = false;
		for (device_t *device = iter.first(); device != NULL; device = iter.next())
			if (device->debug()->breakpoint_clear(bpindex))
				found = true;
		if (found)
			debug_console_printf(machine, "Breakpoint %X cleared\n", (UINT32)bpindex);
		else
			debug_console_printf(machine, "Invalid breakpoint number %X\n", (UINT32)bpindex);
=======
void debugger_commands::execute_bpclear(int ref, const std::vector<std::string> &params)
{
	u64 bpindex;

	/* if 0 parameters, clear all */
	if (params.empty())
	{
		for (device_t &device : device_iterator(m_machine.root_device()))
			device.debug()->breakpoint_clear_all();
		m_console.printf("Cleared all breakpoints\n");
	}

	/* otherwise, clear the specific one */
	else if (!validate_number_parameter(params[0], bpindex))
		return;
	else
	{
		bool found = false;
		for (device_t &device : device_iterator(m_machine.root_device()))
			if (device.debug()->breakpoint_clear(bpindex))
				found = true;
		if (found)
			m_console.printf("Breakpoint %X cleared\n", u32(bpindex));
		else
			m_console.printf("Invalid breakpoint number %X\n", u32(bpindex));
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
    execute_bpdisenable - execute the breakpoint
    disable/enable commands
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_bpdisenable(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 bpindex;

	/* if 0 parameters, clear all */
	if (params == 0)
	{
		device_iterator iter(machine.root_device());
		for (device_t *device = iter.first(); device != NULL; device = iter.next())
			device->debug()->breakpoint_enable_all(ref);
		if (ref == 0)
			debug_console_printf(machine, "Disabled all breakpoints\n");
		else
			debug_console_printf(machine, "Enabled all breakpoints\n");
	}

	/* otherwise, clear the specific one */
	else if (!debug_command_parameter_number(machine, param[0], &bpindex))
		return;
	else
	{
		device_iterator iter(machine.root_device());
		bool found = false;
		for (device_t *device = iter.first(); device != NULL; device = iter.next())
			if (device->debug()->breakpoint_enable(bpindex, ref))
				found = true;
		if (found)
			debug_console_printf(machine, "Breakpoint %X %s\n", (UINT32)bpindex, ref ? "enabled" : "disabled");
		else
			debug_console_printf(machine, "Invalid breakpoint number %X\n", (UINT32)bpindex);
=======
void debugger_commands::execute_bpdisenable(int ref, const std::vector<std::string> &params)
{
	u64 bpindex;

	/* if 0 parameters, clear all */
	if (params.empty())
	{
		for (device_t &device : device_iterator(m_machine.root_device()))
			device.debug()->breakpoint_enable_all(ref);
		if (ref == 0)
			m_console.printf("Disabled all breakpoints\n");
		else
			m_console.printf("Enabled all breakpoints\n");
	}

	/* otherwise, clear the specific one */
	else if (!validate_number_parameter(params[0], bpindex))
		return;
	else
	{
		bool found = false;
		for (device_t &device : device_iterator(m_machine.root_device()))
			if (device.debug()->breakpoint_enable(bpindex, ref))
				found = true;
		if (found)
			m_console.printf("Breakpoint %X %s\n", u32(bpindex), ref ? "enabled" : "disabled");
		else
			m_console.printf("Invalid breakpoint number %X\n", u32(bpindex));
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
    execute_bplist - execute the breakpoint list
    command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_bplist(running_machine &machine, int ref, int params, const char *param[])
=======
void debugger_commands::execute_bplist(int ref, const std::vector<std::string> &params)
>>>>>>> upstream/master
{
	int printed = 0;
	std::string buffer;

	/* loop over all CPUs */
<<<<<<< HEAD
	device_iterator iter(machine.root_device());
	for (device_t *device = iter.first(); device != NULL; device = iter.next())
		if (device->debug()->breakpoint_first() != NULL)
		{
			debug_console_printf(machine, "Device '%s' breakpoints:\n", device->tag());

			/* loop over the breakpoints */
			for (device_debug::breakpoint *bp = device->debug()->breakpoint_first(); bp != NULL; bp = bp->next())
			{
				strprintf(buffer, "%c%4X @ %s", bp->enabled() ? ' ' : 'D', bp->index(), core_i64_hex_format(bp->address(), device->debug()->logaddrchars()));
				if (std::string(bp->condition()).compare("1") != 0)
					strcatprintf(buffer, " if %s", bp->condition());
				if (std::string(bp->action()).compare("") != 0)
					strcatprintf(buffer, " do %s", bp->action());
				debug_console_printf(machine, "%s\n", buffer.c_str());
=======
	for (device_t &device : device_iterator(m_machine.root_device()))
		if (device.debug()->breakpoint_first() != nullptr)
		{
			m_console.printf("Device '%s' breakpoints:\n", device.tag());

			/* loop over the breakpoints */
			for (device_debug::breakpoint *bp = device.debug()->breakpoint_first(); bp != nullptr; bp = bp->next())
			{
				buffer = string_format("%c%4X @ %0*X", bp->enabled() ? ' ' : 'D', bp->index(), device.debug()->logaddrchars(), bp->address());
				if (std::string(bp->condition()).compare("1") != 0)
					buffer.append(string_format(" if %s", bp->condition()));
				if (std::string(bp->action()).compare("") != 0)
					buffer.append(string_format(" do %s", bp->action()));
				m_console.printf("%s\n", buffer.c_str());
>>>>>>> upstream/master
				printed++;
			}
		}

	if (printed == 0)
<<<<<<< HEAD
		debug_console_printf(machine, "No breakpoints currently installed\n");
=======
		m_console.printf("No breakpoints currently installed\n");
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_wpset - execute the watchpoint set
    command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_wpset(running_machine &machine, int ref, int params, const char *param[])
{
	address_space *space;
	const char *action = NULL;
	UINT64 address, length;
=======
void debugger_commands::execute_wpset(int ref, const std::vector<std::string> &params)
{
	address_space *space;
	const char *action = nullptr;
	u64 address, length;
>>>>>>> upstream/master
	int type;
	int wpnum;

	/* CPU is implicit */
<<<<<<< HEAD
	if (!debug_command_parameter_cpu_space(machine, NULL, ref, space))
		return;

	/* param 1 is the address */
	if (!debug_command_parameter_number(machine, param[0], &address))
		return;

	/* param 2 is the length */
	if (!debug_command_parameter_number(machine, param[1], &length))
		return;

	/* param 3 is the type */
	if (!strcmp(param[2], "r"))
		type = WATCHPOINT_READ;
	else if (!strcmp(param[2], "w"))
		type = WATCHPOINT_WRITE;
	else if (!strcmp(param[2], "rw") || !strcmp(param[2], "wr"))
		type = WATCHPOINT_READWRITE;
	else
	{
		debug_console_printf(machine, "Invalid watchpoint type: expected r, w, or rw\n");
=======
	if (!validate_cpu_space_parameter(nullptr, ref, space))
		return;

	/* param 1 is the address */
	if (!validate_number_parameter(params[0], address))
		return;

	/* param 2 is the length */
	if (!validate_number_parameter(params[1], length))
		return;

	/* param 3 is the type */
	if (params[2] == "r")
		type = WATCHPOINT_READ;
	else if (params[2] == "w")
		type = WATCHPOINT_WRITE;
	else if (params[2] == "rw" || params[2] == "wr")
		type = WATCHPOINT_READWRITE;
	else
	{
		m_console.printf("Invalid watchpoint type: expected r, w, or rw\n");
>>>>>>> upstream/master
		return;
	}

	/* param 4 is the condition */
	parsed_expression condition(&space->device().debug()->symtable());
<<<<<<< HEAD
	if (!debug_command_parameter_expression(machine, param[3], condition))
		return;

	/* param 5 is the action */
	if (!debug_command_parameter_command(machine, action = param[4]))
		return;

	/* set the watchpoint */
	wpnum = space->device().debug()->watchpoint_set(*space, type, address, length, (condition.is_empty()) ? NULL : condition.original_string(), action);
	debug_console_printf(machine, "Watchpoint %X set\n", wpnum);
=======
	if (params.size() > 3 && !debug_command_parameter_expression(params[3], condition))
		return;

	/* param 5 is the action */
	if (params.size() > 4 && !debug_command_parameter_command(action = params[4].c_str()))
		return;

	/* set the watchpoint */
	wpnum = space->device().debug()->watchpoint_set(*space, type, address, length, (condition.is_empty()) ? nullptr : condition.original_string(), action);
	m_console.printf("Watchpoint %X set\n", wpnum);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_wpclear - execute the watchpoint
    clear command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_wpclear(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 wpindex;

	/* if 0 parameters, clear all */
	if (params == 0)
	{
		device_iterator iter(machine.root_device());
		for (device_t *device = iter.first(); device != NULL; device = iter.next())
			device->debug()->watchpoint_clear_all();
		debug_console_printf(machine, "Cleared all watchpoints\n");
	}

	/* otherwise, clear the specific one */
	else if (!debug_command_parameter_number(machine, param[0], &wpindex))
		return;
	else
	{
		device_iterator iter(machine.root_device());
		bool found = false;
		for (device_t *device = iter.first(); device != NULL; device = iter.next())
			if (device->debug()->watchpoint_clear(wpindex))
				found = true;
		if (found)
			debug_console_printf(machine, "Watchpoint %X cleared\n", (UINT32)wpindex);
		else
			debug_console_printf(machine, "Invalid watchpoint number %X\n", (UINT32)wpindex);
=======
void debugger_commands::execute_wpclear(int ref, const std::vector<std::string> &params)
{
	u64 wpindex;

	/* if 0 parameters, clear all */
	if (params.empty())
	{
		for (device_t &device : device_iterator(m_machine.root_device()))
			device.debug()->watchpoint_clear_all();
		m_console.printf("Cleared all watchpoints\n");
	}

	/* otherwise, clear the specific one */
	else if (!validate_number_parameter(params[0], wpindex))
		return;
	else
	{
		bool found = false;
		for (device_t &device : device_iterator(m_machine.root_device()))
			if (device.debug()->watchpoint_clear(wpindex))
				found = true;
		if (found)
			m_console.printf("Watchpoint %X cleared\n", u32(wpindex));
		else
			m_console.printf("Invalid watchpoint number %X\n", u32(wpindex));
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
    execute_wpdisenable - execute the watchpoint
    disable/enable commands
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_wpdisenable(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 wpindex;

	/* if 0 parameters, clear all */
	if (params == 0)
	{
		device_iterator iter(machine.root_device());
		for (device_t *device = iter.first(); device != NULL; device = iter.next())
			device->debug()->watchpoint_enable_all(ref);
		if (ref == 0)
			debug_console_printf(machine, "Disabled all watchpoints\n");
		else
			debug_console_printf(machine, "Enabled all watchpoints\n");
	}

	/* otherwise, clear the specific one */
	else if (!debug_command_parameter_number(machine, param[0], &wpindex))
		return;
	else
	{
		device_iterator iter(machine.root_device());
		bool found = false;
		for (device_t *device = iter.first(); device != NULL; device = iter.next())
			if (device->debug()->watchpoint_enable(wpindex, ref))
				found = true;
		if (found)
			debug_console_printf(machine, "Watchpoint %X %s\n", (UINT32)wpindex, ref ? "enabled" : "disabled");
		else
			debug_console_printf(machine, "Invalid watchpoint number %X\n", (UINT32)wpindex);
=======
void debugger_commands::execute_wpdisenable(int ref, const std::vector<std::string> &params)
{
	u64 wpindex;

	/* if 0 parameters, clear all */
	if (params.empty())
	{
		for (device_t &device : device_iterator(m_machine.root_device()))
			device.debug()->watchpoint_enable_all(ref);
		if (ref == 0)
			m_console.printf("Disabled all watchpoints\n");
		else
			m_console.printf("Enabled all watchpoints\n");
	}

	/* otherwise, clear the specific one */
	else if (!validate_number_parameter(params[0], wpindex))
		return;
	else
	{
		bool found = false;
		for (device_t &device : device_iterator(m_machine.root_device()))
			if (device.debug()->watchpoint_enable(wpindex, ref))
				found = true;
		if (found)
			m_console.printf("Watchpoint %X %s\n", u32(wpindex), ref ? "enabled" : "disabled");
		else
			m_console.printf("Invalid watchpoint number %X\n", u32(wpindex));
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
    execute_wplist - execute the watchpoint list
    command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_wplist(running_machine &machine, int ref, int params, const char *param[])
=======
void debugger_commands::execute_wplist(int ref, const std::vector<std::string> &params)
>>>>>>> upstream/master
{
	int printed = 0;
	std::string buffer;

	/* loop over all CPUs */
<<<<<<< HEAD
	device_iterator iter(machine.root_device());
	for (device_t *device = iter.first(); device != NULL; device = iter.next())
		for (address_spacenum spacenum = AS_0; spacenum < ADDRESS_SPACES; ++spacenum)
			if (device->debug()->watchpoint_first(spacenum) != NULL)
			{
				static const char *const types[] = { "unkn ", "read ", "write", "r/w  " };

				debug_console_printf(machine, "Device '%s' %s space watchpoints:\n", device->tag(),
																						device->debug()->watchpoint_first(spacenum)->space().name());

				/* loop over the watchpoints */
				for (device_debug::watchpoint *wp = device->debug()->watchpoint_first(spacenum); wp != NULL; wp = wp->next())
				{
					strprintf(buffer, "%c%4X @ %s-%s %s", wp->enabled() ? ' ' : 'D', wp->index(),
							core_i64_hex_format(wp->space().byte_to_address(wp->address()), wp->space().addrchars()),
							core_i64_hex_format(wp->space().byte_to_address_end(wp->address() + wp->length()) - 1, wp->space().addrchars()),
							types[wp->type() & 3]);
					if (std::string(wp->condition()).compare("1") != 0)
						strcatprintf(buffer, " if %s", wp->condition());
					if (std::string(wp->action()).compare("") != 0)
						strcatprintf(buffer, " do %s", wp->action());
					debug_console_printf(machine, "%s\n", buffer.c_str());
=======
	for (device_t &device : device_iterator(m_machine.root_device()))
		for (int spacenum = 0; spacenum < device.debug()->watchpoint_space_count(); ++spacenum)
			if (device.debug()->watchpoint_first(spacenum) != nullptr)
			{
				static const char *const types[] = { "unkn ", "read ", "write", "r/w  " };

				m_console.printf("Device '%s' %s space watchpoints:\n", device.tag(),
																						device.debug()->watchpoint_first(spacenum)->space().name());

				/* loop over the watchpoints */
				for (device_debug::watchpoint *wp = device.debug()->watchpoint_first(spacenum); wp != nullptr; wp = wp->next())
				{
					buffer = string_format("%c%4X @ %0*X-%0*X %s", wp->enabled() ? ' ' : 'D', wp->index(),
							wp->space().addrchars(), wp->space().byte_to_address(wp->address()),
							wp->space().addrchars(), wp->space().byte_to_address_end(wp->address() + wp->length()) - 1,
							types[wp->type() & 3]);
					if (std::string(wp->condition()).compare("1") != 0)
						buffer.append(string_format(" if %s", wp->condition()));
					if (std::string(wp->action()).compare("") != 0)
						buffer.append(string_format(" do %s", wp->action()));
					m_console.printf("%s\n", buffer.c_str());
>>>>>>> upstream/master
					printed++;
				}
			}

	if (printed == 0)
<<<<<<< HEAD
		debug_console_printf(machine, "No watchpoints currently installed\n");
=======
		m_console.printf("No watchpoints currently installed\n");
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_rpset - execute the registerpoint set
    command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_rpset(running_machine &machine, int ref, int params, const char *param[])
{
	device_t *cpu;
	const char *action = NULL;
	int bpnum;

	/* CPU is implicit */
	if (!debug_command_parameter_cpu(machine, NULL, &cpu))
=======
void debugger_commands::execute_rpset(int ref, const std::vector<std::string> &params)
{
	device_t *cpu;
	const char *action = nullptr;
	int bpnum;

	/* CPU is implicit */
	if (!validate_cpu_parameter(nullptr, cpu))
>>>>>>> upstream/master
		return;

	/* param 1 is the condition */
	parsed_expression condition(&cpu->debug()->symtable());
<<<<<<< HEAD
	if (!debug_command_parameter_expression(machine, param[0], condition))
		return;

	/* param 2 is the action */
	if (!debug_command_parameter_command(machine, action = param[1]))
=======
	if (params.size() > 0 && !debug_command_parameter_expression(params[0], condition))
		return;

	/* param 2 is the action */
	if (params.size() > 1 && !debug_command_parameter_command(action = params[1].c_str()))
>>>>>>> upstream/master
		return;

	/* set the breakpoint */
	bpnum = cpu->debug()->registerpoint_set(condition.original_string(), action);
<<<<<<< HEAD
	debug_console_printf(machine, "Registerpoint %X set\n", bpnum);
=======
	m_console.printf("Registerpoint %X set\n", bpnum);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_rpclear - execute the registerpoint
    clear command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_rpclear(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 rpindex;

	/* if 0 parameters, clear all */
	if (params == 0)
	{
		device_iterator iter(machine.root_device());
		for (device_t *device = iter.first(); device != NULL; device = iter.next())
			device->debug()->registerpoint_clear_all();
		debug_console_printf(machine, "Cleared all registerpoints\n");
	}

	/* otherwise, clear the specific one */
	else if (!debug_command_parameter_number(machine, param[0], &rpindex))
		return;
	else
	{
		device_iterator iter(machine.root_device());
		bool found = false;
		for (device_t *device = iter.first(); device != NULL; device = iter.next())
			if (device->debug()->registerpoint_clear(rpindex))
				found = true;
		if (found)
			debug_console_printf(machine, "Registerpoint %X cleared\n", (UINT32)rpindex);
		else
			debug_console_printf(machine, "Invalid registerpoint number %X\n", (UINT32)rpindex);
=======
void debugger_commands::execute_rpclear(int ref, const std::vector<std::string> &params)
{
	u64 rpindex;

	/* if 0 parameters, clear all */
	if (params.empty())
	{
		for (device_t &device : device_iterator(m_machine.root_device()))
			device.debug()->registerpoint_clear_all();
		m_console.printf("Cleared all registerpoints\n");
	}

	/* otherwise, clear the specific one */
	else if (!validate_number_parameter(params[0], rpindex))
		return;
	else
	{
		bool found = false;
		for (device_t &device : device_iterator(m_machine.root_device()))
			if (device.debug()->registerpoint_clear(rpindex))
				found = true;
		if (found)
			m_console.printf("Registerpoint %X cleared\n", u32(rpindex));
		else
			m_console.printf("Invalid registerpoint number %X\n", u32(rpindex));
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
    execute_rpdisenable - execute the registerpoint
    disable/enable commands
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_rpdisenable(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 rpindex;

	/* if 0 parameters, clear all */
	if (params == 0)
	{
		device_iterator iter(machine.root_device());
		for (device_t *device = iter.first(); device != NULL; device = iter.next())
			device->debug()->registerpoint_enable_all(ref);
		if (ref == 0)
			debug_console_printf(machine, "Disabled all registerpoints\n");
		else
			debug_console_printf(machine, "Enabled all registeroints\n");
	}

	/* otherwise, clear the specific one */
	else if (!debug_command_parameter_number(machine, param[0], &rpindex))
		return;
	else
	{
		device_iterator iter(machine.root_device());
		bool found = false;
		for (device_t *device = iter.first(); device != NULL; device = iter.next())
			if (device->debug()->registerpoint_enable(rpindex, ref))
				found = true;
		if (found)
			debug_console_printf(machine, "Registerpoint %X %s\n", (UINT32)rpindex, ref ? "enabled" : "disabled");
		else
			debug_console_printf(machine, "Invalid registerpoint number %X\n", (UINT32)rpindex);
=======
void debugger_commands::execute_rpdisenable(int ref, const std::vector<std::string> &params)
{
	u64 rpindex;

	/* if 0 parameters, clear all */
	if (params.empty())
	{
		for (device_t &device : device_iterator(m_machine.root_device()))
			device.debug()->registerpoint_enable_all(ref);
		if (ref == 0)
			m_console.printf("Disabled all registerpoints\n");
		else
			m_console.printf("Enabled all registeroints\n");
	}

	/* otherwise, clear the specific one */
	else if (!validate_number_parameter(params[0], rpindex))
		return;
	else
	{
		bool found = false;
		for (device_t &device : device_iterator(m_machine.root_device()))
			if (device.debug()->registerpoint_enable(rpindex, ref))
				found = true;
		if (found)
			m_console.printf("Registerpoint %X %s\n", u32(rpindex), ref ? "enabled" : "disabled");
		else
			m_console.printf("Invalid registerpoint number %X\n", u32(rpindex));
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
    execute_rplist - execute the registerpoint list
    command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_rplist(running_machine &machine, int ref, int params, const char *param[])
=======
void debugger_commands::execute_rplist(int ref, const std::vector<std::string> &params)
>>>>>>> upstream/master
{
	int printed = 0;
	std::string buffer;

	/* loop over all CPUs */
<<<<<<< HEAD
	device_iterator iter(machine.root_device());
	for (device_t *device = iter.first(); device != NULL; device = iter.next())
		if (device->debug()->registerpoint_first() != NULL)
		{
			debug_console_printf(machine, "Device '%s' registerpoints:\n", device->tag());

			/* loop over the breakpoints */
			for (device_debug::registerpoint *rp = device->debug()->registerpoint_first(); rp != NULL; rp = rp->next())
			{
				strprintf(buffer, "%c%4X ", rp->enabled() ? ' ' : 'D', rp->index());
				strcatprintf(buffer, "if %s", rp->condition());
				if (rp->action() != NULL)
					strcatprintf(buffer, " do %s", rp->action());
				debug_console_printf(machine, "%s\n", buffer.c_str());
=======
	for (device_t &device : device_iterator(m_machine.root_device()))
		if (device.debug()->registerpoint_first() != nullptr)
		{
			m_console.printf("Device '%s' registerpoints:\n", device.tag());

			/* loop over the breakpoints */
			for (device_debug::registerpoint *rp = device.debug()->registerpoint_first(); rp != nullptr; rp = rp->next())
			{
				buffer = string_format("%c%4X if %s", rp->enabled() ? ' ' : 'D', rp->index(), rp->condition());
				if (rp->action() != nullptr)
					buffer.append(string_format(" do %s", rp->action()));
				m_console.printf("%s\n", buffer.c_str());
>>>>>>> upstream/master
				printed++;
			}
		}

	if (printed == 0)
<<<<<<< HEAD
		debug_console_printf(machine, "No registerpoints currently installed\n");
=======
		m_console.printf("No registerpoints currently installed\n");
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_hotspot - execute the hotspot
    command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_hotspot(running_machine &machine, int ref, int params, const char *param[])
{
	/* if no params, and there are live hotspots, clear them */
	if (params == 0)
=======
void debugger_commands::execute_hotspot(int ref, const std::vector<std::string> &params)
{
	/* if no params, and there are live hotspots, clear them */
	if (params.empty())
>>>>>>> upstream/master
	{
		bool cleared = false;

		/* loop over CPUs and find live spots */
<<<<<<< HEAD
		device_iterator iter(machine.root_device());
		for (device_t *device = iter.first(); device != NULL; device = iter.next())
			if (device->debug()->hotspot_tracking_enabled())
			{
				device->debug()->hotspot_track(0, 0);
				debug_console_printf(machine, "Cleared hotspot tracking on CPU '%s'\n", device->tag());
=======
		for (device_t &device : device_iterator(m_machine.root_device()))
			if (device.debug()->hotspot_tracking_enabled())
			{
				device.debug()->hotspot_track(0, 0);
				m_console.printf("Cleared hotspot tracking on CPU '%s'\n", device.tag());
>>>>>>> upstream/master
				cleared = true;
			}

		/* if we cleared, we're done */
		if (cleared)
			return;
	}

	/* extract parameters */
<<<<<<< HEAD
	device_t *device = NULL;
	if (!debug_command_parameter_cpu(machine, (params > 0) ? param[0] : NULL, &device))
		return;
	UINT64 count = 64;
	if (!debug_command_parameter_number(machine, param[1], &count))
		return;
	UINT64 threshhold = 250;
	if (!debug_command_parameter_number(machine, param[2], &threshhold))
=======
	device_t *device = nullptr;
	if (!validate_cpu_parameter(!params.empty() ? params[0].c_str() : nullptr, device))
		return;
	u64 count = 64;
	if (params.size() > 1 && !validate_number_parameter(params[1], count))
		return;
	u64 threshhold = 250;
	if (params.size() > 2 && !validate_number_parameter(params[2], threshhold))
>>>>>>> upstream/master
		return;

	/* attempt to install */
	device->debug()->hotspot_track(count, threshhold);
<<<<<<< HEAD
	debug_console_printf(machine, "Now tracking hotspots on CPU '%s' using %d slots with a threshhold of %d\n", device->tag(), (int)count, (int)threshhold);
=======
	m_console.printf("Now tracking hotspots on CPU '%s' using %d slots with a threshold of %d\n", device->tag(), (int)count, (int)threshhold);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_statesave - execute the statesave command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_statesave(running_machine &machine, int ref, int params, const char *param[])
{
	std::string filename(param[0]);
	machine.immediate_save(filename.c_str());
	debug_console_printf(machine, "State save attempted.  Please refer to window message popup for results.\n");
=======
void debugger_commands::execute_statesave(int ref, const std::vector<std::string> &params)
{
	const std::string &filename(params[0]);
	m_machine.immediate_save(filename.c_str());
	m_console.printf("State save attempted.  Please refer to window message popup for results.\n");
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_stateload - execute the stateload command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_stateload(running_machine &machine, int ref, int params, const char *param[])
{
	std::string filename(param[0]);
	machine.immediate_load(filename.c_str());

	// Clear all PC & memory tracks
	device_iterator iter(machine.root_device());
	for (device_t *device = iter.first(); device != NULL; device = iter.next())
	{
		device->debug()->track_pc_data_clear();
		device->debug()->track_mem_data_clear();
	}
	debug_console_printf(machine, "State load attempted.  Please refer to window message popup for results.\n");
=======
void debugger_commands::execute_stateload(int ref, const std::vector<std::string> &params)
{
	const std::string &filename(params[0]);
	m_machine.immediate_load(filename.c_str());

	// Clear all PC & memory tracks
	for (device_t &device : device_iterator(m_machine.root_device()))
	{
		device.debug()->track_pc_data_clear();
		device.debug()->track_mem_data_clear();
	}
	m_console.printf("State load attempted.  Please refer to window message popup for results.\n");
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_save - execute the save command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_save(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 offset, endoffset, length;
	address_space *space;
	FILE *f;
	UINT64 i;

	/* validate parameters */
	if (!debug_command_parameter_number(machine, param[1], &offset))
		return;
	if (!debug_command_parameter_number(machine, param[2], &length))
		return;
	if (!debug_command_parameter_cpu_space(machine, (params > 3) ? param[3] : NULL, ref, space))
=======
void debugger_commands::execute_save(int ref, const std::vector<std::string> &params)
{
	u64 offset, endoffset, length;
	address_space *space;
	FILE *f;
	u64 i;

	/* validate parameters */
	if (!validate_number_parameter(params[1], offset))
		return;
	if (!validate_number_parameter(params[2], length))
		return;
	if (!validate_cpu_space_parameter(params.size() > 3 ? params[3].c_str() : nullptr, ref, space))
>>>>>>> upstream/master
		return;

	/* determine the addresses to write */
	endoffset = space->address_to_byte(offset + length - 1) & space->bytemask();
	offset = space->address_to_byte(offset) & space->bytemask();

	/* open the file */
<<<<<<< HEAD
	f = fopen(param[0], "wb");
	if (!f)
	{
		debug_console_printf(machine, "Error opening file '%s'\n", param[0]);
=======
	f = fopen(params[0].c_str(), "wb");
	if (!f)
	{
		m_console.printf("Error opening file '%s'\n", params[0].c_str());
>>>>>>> upstream/master
		return;
	}

	/* now write the data out */
	for (i = offset; i <= endoffset; i++)
	{
<<<<<<< HEAD
		UINT8 byte = debug_read_byte(*space, i, TRUE);
=======
		u8 byte = m_cpu.read_byte(*space, i, true);
>>>>>>> upstream/master
		fwrite(&byte, 1, 1, f);
	}

	/* close the file */
	fclose(f);
<<<<<<< HEAD
	debug_console_printf(machine, "Data saved successfully\n");
=======
	m_console.printf("Data saved successfully\n");
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_load - execute the load command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_load(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 offset, endoffset, length;
	address_space *space;
	FILE *f;
	UINT64 i;

	/* validate parameters */
	if (!debug_command_parameter_number(machine, param[1], &offset))
		return;
	if (!debug_command_parameter_number(machine, param[2], &length))
		return;
	if (!debug_command_parameter_cpu_space(machine, (params > 3) ? param[3] : NULL, ref, space))
		return;

	/* determine the addresses to read */
	endoffset = space->address_to_byte(offset + length - 1) & space->bytemask();
	offset = space->address_to_byte(offset) & space->bytemask();

	/* open the file */
	f = fopen(param[0], "rb");
	if (!f)
	{
		debug_console_printf(machine, "Error opening file '%s'\n", param[0]);
		return;
	}

	/* now read the data in, ignore endoffset and load entire file if length has been set to zero (offset-1) */
	UINT8 byte;
	for (i = offset; i <= endoffset || endoffset == offset - 1 ; i++)
	{
		fread(&byte, 1, 1, f);
		/* check if end of file has been reached and stop loading if it has */
		if (feof(f))
			break;
		debug_write_byte(*space, i, byte, TRUE);
	}
	/* close the file */
	fclose(f);
	if ( i == offset)
		debug_console_printf(machine, "Length specified too large, load failed\n");
	else
		debug_console_printf(machine, "Data loaded successfully to memory : 0x%s to 0x%s\n", core_i64_hex_format(offset,0), core_i64_hex_format(i-1,0));
=======
void debugger_commands::execute_load(int ref, const std::vector<std::string> &params)
{
	u64 offset, endoffset, length = 0;
	address_space *space;
	u64 i;

	// validate parameters
	if (!validate_number_parameter(params[1], offset))
		return;
	if (params.size() > 2 && !validate_number_parameter(params[2], length))
		return;
	if (!validate_cpu_space_parameter((params.size() > 3) ? params[3].c_str() : nullptr, ref, space))
		return;

	// open the file
	std::ifstream f;
	f.open(params[0], std::ifstream::in | std::ifstream::binary);
	if (f.fail())
	{
		m_console.printf("Error opening file '%s'\n", params[0].c_str());
		return;
	}

	// determine the file size, if not specified
	if (params.size() <= 2)
	{
		f.seekg(0, std::ios::end);
		length = f.tellg();
		f.seekg(0);
	}

	// determine the addresses to read
	endoffset = space->address_to_byte(offset + length - 1) & space->bytemask();
	offset = space->address_to_byte(offset) & space->bytemask();

	// now read the data in, ignore endoffset and load entire file if length has been set to zero (offset-1)
	for (i = offset; f.good() && (i <= endoffset || endoffset == offset - 1); i++)
	{
		char byte;
		f.read(&byte, 1);
		if (f)
			m_cpu.write_byte(*space, i, byte, true);
	}

	if (!f.good())
		m_console.printf("I/O error, load failed\n");
	else if (i == offset)
		m_console.printf("Length specified too large, load failed\n");
	else
		m_console.printf("Data loaded successfully to memory : 0x%X to 0x%X\n", offset, i-1);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_dump - execute the dump command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_dump(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 offset, endoffset, length, width = 0, ascii = 1;
	address_space *space;
	FILE *f;
	UINT64 i, j;

	/* validate parameters */
	if (!debug_command_parameter_number(machine, param[1], &offset))
		return;
	if (!debug_command_parameter_number(machine, param[2], &length))
		return;
	if (!debug_command_parameter_number(machine, param[3], &width))
		return;
	if (!debug_command_parameter_number(machine, param[4], &ascii))
		return;
	if (!debug_command_parameter_cpu_space(machine, (params > 5) ? param[5] : NULL, ref, space))
=======
void debugger_commands::execute_dump(int ref, const std::vector<std::string> &params)
{
	/* validate parameters */
	u64 offset;
	if (!validate_number_parameter(params[1], offset))
		return;

	u64 length;
	if (!validate_number_parameter(params[2], length))
		return;

	u64 width = 0;
	if (params.size() > 3 && !validate_number_parameter(params[3], width))
		return;

	u64 ascii = 1;
	if (params.size() > 4 && !validate_number_parameter(params[4], ascii))
		return;

	u64 rowsize = 16;
	if (params.size() > 5 && !validate_number_parameter(params[5], rowsize))
		return;

	address_space *space;
	if (!validate_cpu_space_parameter((params.size() > 6) ? params[6].c_str() : nullptr, ref, space))
>>>>>>> upstream/master
		return;

	/* further validation */
	if (width == 0)
		width = space->data_width() / 8;
	if (width < space->address_to_byte(1))
		width = space->address_to_byte(1);
	if (width != 1 && width != 2 && width != 4 && width != 8)
	{
<<<<<<< HEAD
		debug_console_printf(machine, "Invalid width! (must be 1,2,4 or 8)\n");
		return;
	}
	endoffset = space->address_to_byte(offset + length - 1) & space->bytemask();
	offset = space->address_to_byte(offset) & space->bytemask();

	/* open the file */
	f = fopen(param[0], "w");
	if (!f)
	{
		debug_console_printf(machine, "Error opening file '%s'\n", param[0]);
=======
		m_console.printf("Invalid width! (must be 1,2,4 or 8)\n");
		return;
	}
	if (rowsize == 0 || (rowsize % width) != 0)
	{
		m_console.printf("Invalid row size! (must be a positive multiple of %d)\n", width);
		return;
	}

	u64 endoffset = space->address_to_byte(offset + length - 1) & space->bytemask();
	offset = space->address_to_byte(offset) & space->bytemask();

	/* open the file */
	FILE* f = fopen(params[0].c_str(), "w");
	if (!f)
	{
		m_console.printf("Error opening file '%s'\n", params[0].c_str());
>>>>>>> upstream/master
		return;
	}

	/* now write the data out */
<<<<<<< HEAD
	for (i = offset; i <= endoffset; i += 16)
	{
		char output[200];
		int outdex = 0;

		/* print the address */
		outdex += sprintf(&output[outdex], "%s: ", core_i64_hex_format((UINT32)space->byte_to_address(i), space->logaddrchars()));

		/* print the bytes */
		for (j = 0; j < 16; j += width)
=======
	util::ovectorstream output;
	output.reserve(200);
	for (u64 i = offset; i <= endoffset; i += rowsize)
	{
		output.clear();
		output.rdbuf()->clear();

		/* print the address */
		util::stream_format(output, "%0*X: ", space->logaddrchars(), u32(space->byte_to_address(i)));

		/* print the bytes */
		for (u64 j = 0; j < rowsize; j += width)
>>>>>>> upstream/master
		{
			if (i + j <= endoffset)
			{
				offs_t curaddr = i + j;
<<<<<<< HEAD
				if (debug_cpu_translate(*space, TRANSLATE_READ_DEBUG, &curaddr))
				{
					UINT64 value = debug_read_memory(*space, i + j, width, TRUE);
					outdex += sprintf(&output[outdex], " %s", core_i64_hex_format(value, width * 2));
				}
				else
					outdex += sprintf(&output[outdex], " %.*s", (int)width * 2, "****************");
			}
			else
				outdex += sprintf(&output[outdex], " %*s", (int)width * 2, "");
=======
				if (space->device().memory().translate(space->spacenum(), TRANSLATE_READ_DEBUG, curaddr))
				{
					u64 value = m_cpu.read_memory(*space, i + j, width, true);
					util::stream_format(output, " %0*X", width * 2, value);
				}
				else
				{
					util::stream_format(output, " %.*s", width * 2, "****************");
				}
			}
			else
				util::stream_format(output, " %*s", width * 2, "");
>>>>>>> upstream/master
		}

		/* print the ASCII */
		if (ascii)
		{
<<<<<<< HEAD
			outdex += sprintf(&output[outdex], "  ");
			for (j = 0; j < 16 && (i + j) <= endoffset; j++)
			{
				offs_t curaddr = i + j;
				if (debug_cpu_translate(*space, TRANSLATE_READ_DEBUG, &curaddr))
				{
					UINT8 byte = debug_read_byte(*space, i + j, TRUE);
					outdex += sprintf(&output[outdex], "%c", (byte >= 32 && byte < 127) ? byte : '.');
				}
				else
					outdex += sprintf(&output[outdex], " ");
=======
			util::stream_format(output, "  ");
			for (u64 j = 0; j < rowsize && (i + j) <= endoffset; j++)
			{
				offs_t curaddr = i + j;
				if (space->device().memory().translate(space->spacenum(), TRANSLATE_READ_DEBUG, curaddr))
				{
					u8 byte = m_cpu.read_byte(*space, i + j, true);
					util::stream_format(output, "%c", (byte >= 32 && byte < 127) ? byte : '.');
				}
				else
				{
					util::stream_format(output, " ");
				}
>>>>>>> upstream/master
			}
		}

		/* output the result */
<<<<<<< HEAD
		fprintf(f, "%s\n", output);
=======
		auto const &text = output.vec();
		fprintf(f, "%.*s\n", int(unsigned(text.size())), &text[0]);
>>>>>>> upstream/master
	}

	/* close the file */
	fclose(f);
<<<<<<< HEAD
	debug_console_printf(machine, "Data dumped successfully\n");
=======
	m_console.printf("Data dumped successfully\n");
>>>>>>> upstream/master
}


/*-------------------------------------------------
   execute_cheatinit - initialize the cheat system
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_cheatinit(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 offset, length = 0, real_length = 0;
	address_space *space;
	UINT32 active_cheat = 0;
	UINT64 curaddr;
	UINT8 i, region_count = 0;

	address_map_entry *entry;
=======
void debugger_commands::execute_cheatinit(int ref, const std::vector<std::string> &params)
{
	u64 offset, length = 0, real_length = 0;
	address_space *space;
	u32 active_cheat = 0;
	u64 curaddr;
	u8 i, region_count = 0;

>>>>>>> upstream/master
	cheat_region_map cheat_region[100];

	memset(cheat_region, 0, sizeof(cheat_region));

	/* validate parameters */
<<<<<<< HEAD
	if (!debug_command_parameter_cpu_space(machine, (params > 3) ? param[3] : NULL, AS_PROGRAM, space))
=======
	if (!validate_cpu_space_parameter((params.size() > 3) ? params[3].c_str() : nullptr, AS_PROGRAM, space))
>>>>>>> upstream/master
		return;

	if (ref == 0)
	{
<<<<<<< HEAD
		cheat.width = 1;
		cheat.signed_cheat = FALSE;
		cheat.swapped_cheat = FALSE;
		if (params > 0)
		{
			char *srtpnt = (char*)param[0];

			if (*srtpnt == 's')
				cheat.signed_cheat = TRUE;
			else if (*srtpnt == 'u')
				cheat.signed_cheat = FALSE;
			else
			{
				debug_console_printf(machine, "Invalid sign: expected s or u\n");
=======
		m_cheat.width = 1;
		m_cheat.signed_cheat = false;
		m_cheat.swapped_cheat = false;
		if (!params.empty())
		{
			char *srtpnt = (char*)params[0].c_str();

			if (*srtpnt == 's')
				m_cheat.signed_cheat = true;
			else if (*srtpnt == 'u')
				m_cheat.signed_cheat = false;
			else
			{
				m_console.printf("Invalid sign: expected s or u\n");
>>>>>>> upstream/master
				return;
			}

			if (*(++srtpnt) == 'b')
<<<<<<< HEAD
				cheat.width = 1;
			else if (*srtpnt == 'w')
				cheat.width = 2;
			else if (*srtpnt == 'd')
				cheat.width = 4;
			else if (*srtpnt == 'q')
				cheat.width = 8;
			else
			{
				debug_console_printf(machine, "Invalid width: expected b, w, d or q\n");
=======
				m_cheat.width = 1;
			else if (*srtpnt == 'w')
				m_cheat.width = 2;
			else if (*srtpnt == 'd')
				m_cheat.width = 4;
			else if (*srtpnt == 'q')
				m_cheat.width = 8;
			else
			{
				m_console.printf("Invalid width: expected b, w, d or q\n");
>>>>>>> upstream/master
				return;
			}

			if (*(++srtpnt) == 's')
<<<<<<< HEAD
				cheat.swapped_cheat = TRUE;
			else
				cheat.swapped_cheat = FALSE;
=======
				m_cheat.swapped_cheat = true;
			else
				m_cheat.swapped_cheat = false;
>>>>>>> upstream/master
		}
	}

	/* initialize entire memory by default */
<<<<<<< HEAD
	if (params <= 1)
	{
		for (entry = space->map()->m_entrylist.first(); entry != NULL; entry = entry->next())
		{
			cheat_region[region_count].offset = space->address_to_byte(entry->m_addrstart) & space->bytemask();
			cheat_region[region_count].endoffset = space->address_to_byte(entry->m_addrend) & space->bytemask();
			cheat_region[region_count].share = entry->m_share;
			cheat_region[region_count].disabled = (entry->m_write.m_type == AMH_RAM) ? FALSE : TRUE;

			/* disable double share regions */
			if (entry->m_share != NULL)
				for (i = 0; i < region_count; i++)
					if (cheat_region[i].share != NULL)
						if (strcmp(cheat_region[i].share, entry->m_share) == 0)
							cheat_region[region_count].disabled = TRUE;
=======
	if (params.size() <= 1)
	{
		for (address_map_entry &entry : space->map()->m_entrylist)
		{
			cheat_region[region_count].offset = space->address_to_byte(entry.m_addrstart) & space->bytemask();
			cheat_region[region_count].endoffset = space->address_to_byte(entry.m_addrend) & space->bytemask();
			cheat_region[region_count].share = entry.m_share;
			cheat_region[region_count].disabled = (entry.m_write.m_type == AMH_RAM) ? false : true;

			/* disable double share regions */
			if (entry.m_share != nullptr)
				for (i = 0; i < region_count; i++)
					if (cheat_region[i].share != nullptr)
						if (strcmp(cheat_region[i].share, entry.m_share) == 0)
							cheat_region[region_count].disabled = true;
>>>>>>> upstream/master

			region_count++;
		}
	}
	else
	{
		/* validate parameters */
<<<<<<< HEAD
		if (!debug_command_parameter_number(machine, param[(ref == 0) ? 1 : 0], &offset))
			return;
		if (!debug_command_parameter_number(machine, param[(ref == 0) ? 2 : 1], &length))
=======
		if (!validate_number_parameter(params[(ref == 0) ? 1 : 0], offset))
			return;
		if (!validate_number_parameter(params[(ref == 0) ? 2 : 1], length))
>>>>>>> upstream/master
			return;

		/* force region to the specified range */
		cheat_region[region_count].offset = space->address_to_byte(offset) & space->bytemask();
		cheat_region[region_count].endoffset = space->address_to_byte(offset + length - 1) & space->bytemask();
<<<<<<< HEAD
		cheat_region[region_count].share = NULL;
		cheat_region[region_count].disabled = FALSE;
=======
		cheat_region[region_count].share = nullptr;
		cheat_region[region_count].disabled = false;
>>>>>>> upstream/master
		region_count++;
	}

	/* determine the writable extent of each region in total */
	for (i = 0; i < region_count; i++)
		if (!cheat_region[i].disabled)
<<<<<<< HEAD
			for (curaddr = cheat_region[i].offset; curaddr <= cheat_region[i].endoffset; curaddr += cheat.width)
=======
			for (curaddr = cheat_region[i].offset; curaddr <= cheat_region[i].endoffset; curaddr += m_cheat.width)
>>>>>>> upstream/master
				if (cheat_address_is_valid(*space, curaddr))
					real_length++;

	if (real_length == 0)
	{
<<<<<<< HEAD
		debug_console_printf(machine, "No writable bytes found in this area\n");
=======
		m_console.printf("No writable bytes found in this area\n");
>>>>>>> upstream/master
		return;
	}

	if (ref == 0)
	{
		/* initialize new cheat system */
<<<<<<< HEAD
		cheat.cheatmap.resize(real_length);
		cheat.undo = 0;
		cheat.cpu[0] = (params > 3) ? *param[3] : '0';
=======
		m_cheat.cheatmap.resize(real_length);
		m_cheat.undo = 0;
		m_cheat.cpu[0] = params.size() > 3 ? params[3][0] : '0';
>>>>>>> upstream/master
	}
	else
	{
		/* add range to cheat system */
<<<<<<< HEAD
		if (cheat.cpu[0] == 0)
		{
			debug_console_printf(machine, "Use cheatinit before cheatrange\n");
			return;
		}

		if (!debug_command_parameter_cpu_space(machine, cheat.cpu, AS_PROGRAM, space))
			return;

		active_cheat = cheat.cheatmap.size();
		cheat.cheatmap.resize(cheat.cheatmap.size() + real_length);
=======
		if (m_cheat.cpu[0] == 0)
		{
			m_console.printf("Use cheatinit before cheatrange\n");
			return;
		}

		if (!validate_cpu_space_parameter(m_cheat.cpu, AS_PROGRAM, space))
			return;

		active_cheat = m_cheat.cheatmap.size();
		m_cheat.cheatmap.resize(m_cheat.cheatmap.size() + real_length);
>>>>>>> upstream/master
	}

	/* initialize cheatmap in the selected space */
	for (i = 0; i < region_count; i++)
		if (!cheat_region[i].disabled)
<<<<<<< HEAD
			for (curaddr = cheat_region[i].offset; curaddr <= cheat_region[i].endoffset; curaddr += cheat.width)
				if (cheat_address_is_valid(*space, curaddr))
				{
					cheat.cheatmap[active_cheat].previous_value = cheat_read_extended(&cheat, *space, curaddr);
					cheat.cheatmap[active_cheat].first_value = cheat.cheatmap[active_cheat].previous_value;
					cheat.cheatmap[active_cheat].offset = curaddr;
					cheat.cheatmap[active_cheat].state = 1;
					cheat.cheatmap[active_cheat].undo = 0;
=======
			for (curaddr = cheat_region[i].offset; curaddr <= cheat_region[i].endoffset; curaddr += m_cheat.width)
				if (cheat_address_is_valid(*space, curaddr))
				{
					m_cheat.cheatmap[active_cheat].previous_value = cheat_read_extended(&m_cheat, *space, curaddr);
					m_cheat.cheatmap[active_cheat].first_value = m_cheat.cheatmap[active_cheat].previous_value;
					m_cheat.cheatmap[active_cheat].offset = curaddr;
					m_cheat.cheatmap[active_cheat].state = 1;
					m_cheat.cheatmap[active_cheat].undo = 0;
>>>>>>> upstream/master
					active_cheat++;
				}

	/* give a detailed init message to avoid searches being mistakingly carried out on the wrong CPU */
<<<<<<< HEAD
	device_t *cpu = NULL;
	debug_command_parameter_cpu(machine, cheat.cpu, &cpu);
	debug_console_printf(machine, "%u cheat initialized for CPU index %s ( aka %s )\n", active_cheat, cheat.cpu, cpu->tag());
=======
	device_t *cpu = nullptr;
	validate_cpu_parameter(m_cheat.cpu, cpu);
	m_console.printf("%u cheat initialized for CPU index %s ( aka %s )\n", active_cheat, m_cheat.cpu, cpu->tag());
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_cheatnext - execute the search
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_cheatnext(running_machine &machine, int ref, int params, const char *param[])
{
	address_space *space;
	UINT64 cheatindex;
	UINT32 active_cheat = 0;
	UINT8 condition;
	UINT64 comp_value = 0;
=======
void debugger_commands::execute_cheatnext(int ref, const std::vector<std::string> &params)
{
	address_space *space;
	u64 cheatindex;
	u32 active_cheat = 0;
	u8 condition;
	u64 comp_value = 0;
>>>>>>> upstream/master

	enum
	{
		CHEAT_ALL = 0,
		CHEAT_EQUAL,
		CHEAT_NOTEQUAL,
		CHEAT_EQUALTO,
		CHEAT_NOTEQUALTO,
		CHEAT_DECREASE,
		CHEAT_INCREASE,
		CHEAT_DECREASE_OR_EQUAL,
		CHEAT_INCREASE_OR_EQUAL,
		CHEAT_DECREASEOF,
		CHEAT_INCREASEOF,
		CHEAT_SMALLEROF,
		CHEAT_GREATEROF,
		CHEAT_CHANGEDBY
	};

<<<<<<< HEAD
	if (cheat.cpu[0] == 0)
	{
		debug_console_printf(machine, "Use cheatinit before cheatnext\n");
		return;
	}

	if (!debug_command_parameter_cpu_space(machine, cheat.cpu, AS_PROGRAM, space))
		return;

	if (params > 1 && !debug_command_parameter_number(machine, param[1], &comp_value))
		return;
	comp_value = cheat_sign_extend(&cheat, comp_value);

	/* decode contidion */
	if (!strcmp(param[0], "all"))
		condition = CHEAT_ALL;
	else if (!strcmp(param[0], "equal") || !strcmp(param[0], "eq"))
		condition = (params > 1) ? CHEAT_EQUALTO : CHEAT_EQUAL;
	else if (!strcmp(param[0], "notequal") || !strcmp(param[0], "ne"))
		condition = (params > 1) ? CHEAT_NOTEQUALTO : CHEAT_NOTEQUAL;
	else if (!strcmp(param[0], "decrease") || !strcmp(param[0], "de") || !strcmp(param[0], "-"))
		condition = (params > 1) ? CHEAT_DECREASEOF : CHEAT_DECREASE;
	else if (!strcmp(param[0], "increase") || !strcmp(param[0], "in") || !strcmp(param[0], "+"))
		condition = (params > 1) ? CHEAT_INCREASEOF : CHEAT_INCREASE;
	else if (!strcmp(param[0], "decreaseorequal") || !strcmp(param[0], "deeq"))
		condition = CHEAT_DECREASE_OR_EQUAL;
	else if (!strcmp(param[0], "increaseorequal") || !strcmp(param[0], "ineq"))
		condition = CHEAT_INCREASE_OR_EQUAL;
	else if (!strcmp(param[0], "smallerof") || !strcmp(param[0], "lt") || !strcmp(param[0], "<"))
		condition = CHEAT_SMALLEROF;
	else if (!strcmp(param[0], "greaterof") || !strcmp(param[0], "gt") || !strcmp(param[0], ">"))
		condition = CHEAT_GREATEROF;
	else if (!strcmp(param[0], "changedby") || !strcmp(param[0], "ch") || !strcmp(param[0], "~"))
		condition = CHEAT_CHANGEDBY;
	else
	{
		debug_console_printf(machine, "Invalid condition type\n");
		return;
	}

	cheat.undo++;

	/* execute the search */
	for (cheatindex = 0; cheatindex < cheat.cheatmap.size(); cheatindex += 1)
		if (cheat.cheatmap[cheatindex].state == 1)
		{
			UINT64 cheat_value = cheat_read_extended(&cheat, *space, cheat.cheatmap[cheatindex].offset);
			UINT64 comp_byte = (ref == 0) ? cheat.cheatmap[cheatindex].previous_value : cheat.cheatmap[cheatindex].first_value;
			UINT8 disable_byte = FALSE;
=======
	if (m_cheat.cpu[0] == 0)
	{
		m_console.printf("Use cheatinit before cheatnext\n");
		return;
	}

	if (!validate_cpu_space_parameter(m_cheat.cpu, AS_PROGRAM, space))
		return;

	if (params.size() > 1 && !validate_number_parameter(params[1], comp_value))
		return;
	comp_value = cheat_sign_extend(&m_cheat, comp_value);

	/* decode condition */
	if (params[0] == "all")
		condition = CHEAT_ALL;
	else if (params[0] == "equal" || params[0] == "eq")
		condition = (params.size() > 1) ? CHEAT_EQUALTO : CHEAT_EQUAL;
	else if (params[0] == "notequal" || params[0] == "ne")
		condition = (params.size() > 1) ? CHEAT_NOTEQUALTO : CHEAT_NOTEQUAL;
	else if (params[0] == "decrease" || params[0] == "de" || params[0] == "-")
		condition = (params.size() > 1) ? CHEAT_DECREASEOF : CHEAT_DECREASE;
	else if (params[0] == "increase" || params[0] == "in" || params[0] == "+")
		condition = (params.size() > 1) ? CHEAT_INCREASEOF : CHEAT_INCREASE;
	else if (params[0] == "decreaseorequal" || params[0] == "deeq")
		condition = CHEAT_DECREASE_OR_EQUAL;
	else if (params[0] == "increaseorequal" || params[0] == "ineq")
		condition = CHEAT_INCREASE_OR_EQUAL;
	else if (params[0] == "smallerof" || params[0] == "lt" || params[0] == "<")
		condition = CHEAT_SMALLEROF;
	else if (params[0] == "greaterof" || params[0] == "gt" || params[0] == ">")
		condition = CHEAT_GREATEROF;
	else if (params[0] == "changedby" || params[0] == "ch" || params[0] == "~")
		condition = CHEAT_CHANGEDBY;
	else
	{
		m_console.printf("Invalid condition type\n");
		return;
	}

	m_cheat.undo++;

	/* execute the search */
	for (cheatindex = 0; cheatindex < m_cheat.cheatmap.size(); cheatindex += 1)
		if (m_cheat.cheatmap[cheatindex].state == 1)
		{
			u64 cheat_value = cheat_read_extended(&m_cheat, *space, m_cheat.cheatmap[cheatindex].offset);
			u64 comp_byte = (ref == 0) ? m_cheat.cheatmap[cheatindex].previous_value : m_cheat.cheatmap[cheatindex].first_value;
			u8 disable_byte = false;
>>>>>>> upstream/master

			switch (condition)
			{
				case CHEAT_ALL:
					break;

				case CHEAT_EQUAL:
					disable_byte = (cheat_value != comp_byte);
					break;

				case CHEAT_NOTEQUAL:
					disable_byte = (cheat_value == comp_byte);
					break;

				case CHEAT_EQUALTO:
					disable_byte = (cheat_value != comp_value);
					break;

				case CHEAT_NOTEQUALTO:
					disable_byte = (cheat_value == comp_value);
					break;

				case CHEAT_DECREASE:
<<<<<<< HEAD
					if (cheat.signed_cheat)
						disable_byte = ((INT64)cheat_value >= (INT64)comp_byte);
					else
						disable_byte = ((UINT64)cheat_value >= (UINT64)comp_byte);
					break;

				case CHEAT_INCREASE:
					if (cheat.signed_cheat)
						disable_byte = ((INT64)cheat_value <= (INT64)comp_byte);
					else
						disable_byte = ((UINT64)cheat_value <= (UINT64)comp_byte);
					break;

				case CHEAT_DECREASE_OR_EQUAL:
					if (cheat.signed_cheat)
						disable_byte = ((INT64)cheat_value > (INT64)comp_byte);
					else
						disable_byte = ((UINT64)cheat_value > (UINT64)comp_byte);
					break;

				case CHEAT_INCREASE_OR_EQUAL:
					if (cheat.signed_cheat)
						disable_byte = ((INT64)cheat_value < (INT64)comp_byte);
					else
						disable_byte = ((UINT64)cheat_value < (UINT64)comp_byte);
=======
					if (m_cheat.signed_cheat)
						disable_byte = (s64(cheat_value) >= s64(comp_byte));
					else
						disable_byte = (u64(cheat_value) >= u64(comp_byte));
					break;

				case CHEAT_INCREASE:
					if (m_cheat.signed_cheat)
						disable_byte = (s64(cheat_value) <= s64(comp_byte));
					else
						disable_byte = (u64(cheat_value) <= u64(comp_byte));
					break;

				case CHEAT_DECREASE_OR_EQUAL:
					if (m_cheat.signed_cheat)
						disable_byte = (s64(cheat_value) > s64(comp_byte));
					else
						disable_byte = (u64(cheat_value) > u64(comp_byte));
					break;

				case CHEAT_INCREASE_OR_EQUAL:
					if (m_cheat.signed_cheat)
						disable_byte = (s64(cheat_value) < s64(comp_byte));
					else
						disable_byte = (u64(cheat_value) < u64(comp_byte));
>>>>>>> upstream/master
					break;

				case CHEAT_DECREASEOF:
					disable_byte = (cheat_value != comp_byte - comp_value);
					break;

				case CHEAT_INCREASEOF:
					disable_byte = (cheat_value != comp_byte + comp_value);
					break;

				case CHEAT_SMALLEROF:
<<<<<<< HEAD
					if (cheat.signed_cheat)
						disable_byte = ((INT64)cheat_value >= (INT64)comp_value);
					else
						disable_byte = ((UINT64)cheat_value >= (UINT64)comp_value);
					break;

				case CHEAT_GREATEROF:
					if (cheat.signed_cheat)
						disable_byte = ((INT64)cheat_value <= (INT64)comp_value);
					else
						disable_byte = ((UINT64)cheat_value <= (UINT64)comp_value);
=======
					if (m_cheat.signed_cheat)
						disable_byte = (s64(cheat_value) >= s64(comp_value));
					else
						disable_byte = (u64(cheat_value) >= u64(comp_value));
					break;

				case CHEAT_GREATEROF:
					if (m_cheat.signed_cheat)
						disable_byte = (s64(cheat_value) <= s64(comp_value));
					else
						disable_byte = (u64(cheat_value) <= u64(comp_value));
>>>>>>> upstream/master
					break;
				case CHEAT_CHANGEDBY:
					if (cheat_value > comp_byte)
						disable_byte = (cheat_value != comp_byte + comp_value);
					else
						disable_byte = (cheat_value != comp_byte - comp_value);
					break;
			}

			if (disable_byte)
			{
<<<<<<< HEAD
				cheat.cheatmap[cheatindex].state = 0;
				cheat.cheatmap[cheatindex].undo = cheat.undo;
=======
				m_cheat.cheatmap[cheatindex].state = 0;
				m_cheat.cheatmap[cheatindex].undo = m_cheat.undo;
>>>>>>> upstream/master
			}
			else
				active_cheat++;

			/* update previous value */
<<<<<<< HEAD
			cheat.cheatmap[cheatindex].previous_value = cheat_value;
		}

	if (active_cheat <= 5)
		execute_cheatlist(machine, 0, 0, NULL);

	debug_console_printf(machine, "%u cheats found\n", active_cheat);
=======
			m_cheat.cheatmap[cheatindex].previous_value = cheat_value;
		}

	if (active_cheat <= 5)
		execute_cheatlist(0, std::vector<std::string>());

	m_console.printf("%u cheats found\n", active_cheat);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_cheatlist - show a list of active cheat
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_cheatlist(running_machine &machine, int ref, int params, const char *param[])
=======
void debugger_commands::execute_cheatlist(int ref, const std::vector<std::string> &params)
>>>>>>> upstream/master
{
	char spaceletter, sizeletter;
	address_space *space;
	device_t *cpu;
<<<<<<< HEAD
	UINT32 active_cheat = 0;
	UINT64 cheatindex;
	UINT64 sizemask;
	FILE *f = NULL;

	if (!debug_command_parameter_cpu_space(machine, cheat.cpu, AS_PROGRAM, space))
		return;

	if (!debug_command_parameter_cpu(machine, cheat.cpu, &cpu))
		return;

	if (params > 0)
		f = fopen(param[0], "w");
=======
	u32 active_cheat = 0;
	u64 cheatindex;
	u64 sizemask;
	FILE *f = nullptr;

	if (!validate_cpu_space_parameter(m_cheat.cpu, AS_PROGRAM, space))
		return;

	if (!validate_cpu_parameter(m_cheat.cpu, cpu))
		return;

	if (params.size() > 0)
		f = fopen(params[0].c_str(), "w");
>>>>>>> upstream/master

	switch (space->spacenum())
	{
		default:
		case AS_PROGRAM:    spaceletter = 'p';  break;
		case AS_DATA:   spaceletter = 'd';  break;
		case AS_IO:     spaceletter = 'i';  break;
<<<<<<< HEAD
	}

	switch (cheat.width)
	{
		default:
		case 1:                     sizeletter = 'b';   sizemask = 0xff;                    break;
		case 2:                     sizeletter = 'w';   sizemask = 0xffff;                  break;
		case 4:                     sizeletter = 'd';   sizemask = 0xffffffff;              break;
		case 8:                     sizeletter = 'q';   sizemask = U64(0xffffffffffffffff); break;
	}

	/* write the cheat list */
	for (cheatindex = 0; cheatindex < cheat.cheatmap.size(); cheatindex += 1)
	{
		if (cheat.cheatmap[cheatindex].state == 1)
		{
			UINT64 value = cheat_byte_swap(&cheat, cheat_read_extended(&cheat, *space, cheat.cheatmap[cheatindex].offset)) & sizemask;
			offs_t address = space->byte_to_address(cheat.cheatmap[cheatindex].offset);

			if (params > 0)
			{
				active_cheat++;
				fprintf(f, "  <cheat desc=\"Possibility %d : %s (%s)\">\n", active_cheat, core_i64_hex_format(address, space->logaddrchars()), core_i64_hex_format(value, cheat.width * 2));
				fprintf(f, "    <script state=\"run\">\n");
				fprintf(f, "      <action>%s.p%c%c@%s=%s</action>\n", cpu->tag(), spaceletter, sizeletter, core_i64_hex_format(address, space->logaddrchars()), core_i64_hex_format(cheat_byte_swap(&cheat, cheat.cheatmap[cheatindex].first_value) & sizemask, cheat.width * 2));
				fprintf(f, "    </script>\n");
				fprintf(f, "  </cheat>\n\n");
			}
			else
				debug_console_printf(machine, "Address=%s Start=%s Current=%s\n", core_i64_hex_format(address, space->logaddrchars()), core_i64_hex_format(cheat_byte_swap(&cheat, cheat.cheatmap[cheatindex].first_value) & sizemask, cheat.width * 2), core_i64_hex_format(value, cheat.width * 2));
		}
	}
	if (params > 0)
=======
		case AS_OPCODES: spaceletter = 'o'; break;
	}

	switch (m_cheat.width)
	{
		default:
		case 1:                     sizeletter = 'b';   sizemask = 0xffU;               break;
		case 2:                     sizeletter = 'w';   sizemask = 0xffffU;             break;
		case 4:                     sizeletter = 'd';   sizemask = 0xffffffffU;         break;
		case 8:                     sizeletter = 'q';   sizemask = 0xffffffffffffffffU; break;
	}

	/* write the cheat list */
	util::ovectorstream output;
	for (cheatindex = 0; cheatindex < m_cheat.cheatmap.size(); cheatindex += 1)
	{
		if (m_cheat.cheatmap[cheatindex].state == 1)
		{
			u64 value = cheat_byte_swap(&m_cheat, cheat_read_extended(&m_cheat, *space, m_cheat.cheatmap[cheatindex].offset)) & sizemask;
			offs_t address = space->byte_to_address(m_cheat.cheatmap[cheatindex].offset);

			if (!params.empty())
			{
				active_cheat++;
				output.clear();
				output.rdbuf()->clear();
				stream_format(
						output,
						"  <cheat desc=\"Possibility %d : %0*X (%0*X)\">\n"
						"    <script state=\"run\">\n"
						"      <action>%s.p%c%c@%0*X=%0*X</action>\n"
						"    </script>\n"
						"  </cheat>\n\n",
						active_cheat, space->logaddrchars(), address, m_cheat.width * 2, value,
						cpu->tag(), spaceletter, sizeletter, space->logaddrchars(), address, m_cheat.width * 2, cheat_byte_swap(&m_cheat, m_cheat.cheatmap[cheatindex].first_value) & sizemask);
				auto const &text(output.vec());
				fprintf(f, "%.*s", int(unsigned(text.size())), &text[0]);
			}
			else
			{
				m_console.printf(
						"Address=%0*X Start=%0*X Current=%0*X\n",
						space->logaddrchars(), address,
						m_cheat.width * 2, cheat_byte_swap(&m_cheat, m_cheat.cheatmap[cheatindex].first_value) & sizemask,
						m_cheat.width * 2, value);
			}
		}
	}
	if (params.size() > 0)
>>>>>>> upstream/master
		fclose(f);
}


/*-------------------------------------------------
    execute_cheatundo - undo the last search
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_cheatundo(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 cheatindex;
	UINT32 undo_count = 0;

	if (cheat.undo > 0)
	{
		for (cheatindex = 0; cheatindex < cheat.cheatmap.size(); cheatindex += 1)
		{
			if (cheat.cheatmap[cheatindex].undo == cheat.undo)
			{
				cheat.cheatmap[cheatindex].state = 1;
				cheat.cheatmap[cheatindex].undo = 0;
=======
void debugger_commands::execute_cheatundo(int ref, const std::vector<std::string> &params)
{
	u64 cheatindex;
	u32 undo_count = 0;

	if (m_cheat.undo > 0)
	{
		for (cheatindex = 0; cheatindex < m_cheat.cheatmap.size(); cheatindex += 1)
		{
			if (m_cheat.cheatmap[cheatindex].undo == m_cheat.undo)
			{
				m_cheat.cheatmap[cheatindex].state = 1;
				m_cheat.cheatmap[cheatindex].undo = 0;
>>>>>>> upstream/master
				undo_count++;
			}
		}

<<<<<<< HEAD
		cheat.undo--;
		debug_console_printf(machine, "%u cheat reactivated\n", undo_count);
	}
	else
		debug_console_printf(machine, "Maximum undo reached\n");
=======
		m_cheat.undo--;
		m_console.printf("%u cheat reactivated\n", undo_count);
	}
	else
		m_console.printf("Maximum undo reached\n");
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_find - execute the find command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_find(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 offset, endoffset, length;
	address_space *space;
	UINT64 data_to_find[256];
	UINT8 data_size[256];
=======
void debugger_commands::execute_find(int ref, const std::vector<std::string> &params)
{
	u64 offset, endoffset, length;
	address_space *space;
	u64 data_to_find[256];
	u8 data_size[256];
>>>>>>> upstream/master
	int cur_data_size;
	int data_count = 0;
	int found = 0;
	int j;

	/* validate parameters */
<<<<<<< HEAD
	if (!debug_command_parameter_number(machine, param[0], &offset))
		return;
	if (!debug_command_parameter_number(machine, param[1], &length))
		return;
	if (!debug_command_parameter_cpu_space(machine, NULL, ref, space))
=======
	if (!validate_number_parameter(params[0], offset))
		return;
	if (!validate_number_parameter(params[1], length))
		return;
	if (!validate_cpu_space_parameter(nullptr, ref, space))
>>>>>>> upstream/master
		return;

	/* further validation */
	endoffset = space->address_to_byte(offset + length - 1) & space->bytemask();
	offset = space->address_to_byte(offset) & space->bytemask();
	cur_data_size = space->address_to_byte(1);
	if (cur_data_size == 0)
		cur_data_size = 1;

	/* parse the data parameters */
<<<<<<< HEAD
	for (int i = 2; i < params; i++)
	{
		const char *pdata = param[i];

		/* check for a string */
		if (pdata[0] == '"' && pdata[strlen(pdata) - 1] == '"')
		{
			for (j = 1; j < strlen(pdata) - 1; j++)
=======
	for (int i = 2; i < params.size(); i++)
	{
		const char *pdata = params[i].c_str();
		size_t pdatalen = strlen(pdata) - 1;

		/* check for a string */
		if (pdata[0] == '"' && pdata[pdatalen] == '"')
		{
			for (j = 1; j < pdatalen; j++)
>>>>>>> upstream/master
			{
				data_to_find[data_count] = pdata[j];
				data_size[data_count++] = 1;
			}
		}

		/* otherwise, validate as a number */
		else
		{
			/* check for a 'b','w','d',or 'q' prefix */
			data_size[data_count] = cur_data_size;
<<<<<<< HEAD
			if (tolower((UINT8)pdata[0]) == 'b' && pdata[1] == '.') { data_size[data_count] = cur_data_size = 1; pdata += 2; }
			if (tolower((UINT8)pdata[0]) == 'w' && pdata[1] == '.') { data_size[data_count] = cur_data_size = 2; pdata += 2; }
			if (tolower((UINT8)pdata[0]) == 'd' && pdata[1] == '.') { data_size[data_count] = cur_data_size = 4; pdata += 2; }
			if (tolower((UINT8)pdata[0]) == 'q' && pdata[1] == '.') { data_size[data_count] = cur_data_size = 8; pdata += 2; }
=======
			if (tolower(u8(pdata[0])) == 'b' && pdata[1] == '.') { data_size[data_count] = cur_data_size = 1; pdata += 2; }
			if (tolower(u8(pdata[0])) == 'w' && pdata[1] == '.') { data_size[data_count] = cur_data_size = 2; pdata += 2; }
			if (tolower(u8(pdata[0])) == 'd' && pdata[1] == '.') { data_size[data_count] = cur_data_size = 4; pdata += 2; }
			if (tolower(u8(pdata[0])) == 'q' && pdata[1] == '.') { data_size[data_count] = cur_data_size = 8; pdata += 2; }
>>>>>>> upstream/master

			/* look for a wildcard */
			if (!strcmp(pdata, "?"))
				data_size[data_count++] |= 0x10;

			/* otherwise, validate as a number */
<<<<<<< HEAD
			else if (!debug_command_parameter_number(machine, pdata, &data_to_find[data_count++]))
=======
			else if (!validate_number_parameter(pdata, data_to_find[data_count++]))
>>>>>>> upstream/master
				return;
		}
	}

	/* now search */
<<<<<<< HEAD
	for (UINT64 i = offset; i <= endoffset; i += data_size[0])
=======
	for (u64 i = offset; i <= endoffset; i += data_size[0])
>>>>>>> upstream/master
	{
		int suboffset = 0;
		int match = 1;

		/* find the entire string */
		for (j = 0; j < data_count && match; j++)
		{
			switch (data_size[j])
			{
<<<<<<< HEAD
				case 1: match = ((UINT8)debug_read_byte(*space, i + suboffset, TRUE) == (UINT8)data_to_find[j]);    break;
				case 2: match = ((UINT16)debug_read_word(*space, i + suboffset, TRUE) == (UINT16)data_to_find[j]);  break;
				case 4: match = ((UINT32)debug_read_dword(*space, i + suboffset, TRUE) == (UINT32)data_to_find[j]); break;
				case 8: match = ((UINT64)debug_read_qword(*space, i + suboffset, TRUE) == (UINT64)data_to_find[j]); break;
=======
				case 1: match = (u8(m_cpu.read_byte(*space, i + suboffset, true)) == u8(data_to_find[j]));    break;
				case 2: match = (u16(m_cpu.read_word(*space, i + suboffset, true)) == u16(data_to_find[j]));  break;
				case 4: match = (u32(m_cpu.read_dword(*space, i + suboffset, true)) == u32(data_to_find[j])); break;
				case 8: match = (u64(m_cpu.read_qword(*space, i + suboffset, true)) == u64(data_to_find[j])); break;
>>>>>>> upstream/master
				default:    /* all other cases are wildcards */     break;
			}
			suboffset += data_size[j] & 0x0f;
		}

		/* did we find it? */
		if (match)
		{
			found++;
<<<<<<< HEAD
			debug_console_printf(machine, "Found at %s\n", core_i64_hex_format((UINT32)space->byte_to_address(i), space->addrchars()));
=======
			m_console.printf("Found at %0*X\n", space->addrchars(), u32(space->byte_to_address(i)));
>>>>>>> upstream/master
		}
	}

	/* print something if not found */
	if (found == 0)
<<<<<<< HEAD
		debug_console_printf(machine, "Not found\n");
=======
		m_console.printf("Not found\n");
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_dasm - execute the dasm command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_dasm(running_machine &machine, int ref, int params, const char *param[])
{
	UINT64 offset, length, bytes = 1;
=======
void debugger_commands::execute_dasm(int ref, const std::vector<std::string> &params)
{
	u64 offset, length, bytes = 1;
>>>>>>> upstream/master
	int minbytes, maxbytes, byteswidth;
	address_space *space, *decrypted_space;
	FILE *f;
	int j;

	/* validate parameters */
<<<<<<< HEAD
	if (!debug_command_parameter_number(machine, param[1], &offset))
		return;
	if (!debug_command_parameter_number(machine, param[2], &length))
		return;
	if (!debug_command_parameter_number(machine, param[3], &bytes))
		return;
	if (!debug_command_parameter_cpu_space(machine, (params > 4) ? param[4] : NULL, AS_PROGRAM, space))
		return;
	if (!debug_command_parameter_cpu_space(machine, (params > 4) ? param[4] : NULL, AS_DECRYPTED_OPCODES, decrypted_space))
		decrypted_space = space;

	/* determine the width of the bytes */
	cpu_device *cpudevice = downcast<cpu_device *>(&space->device());
	minbytes = cpudevice->min_opcode_bytes();
	maxbytes = cpudevice->max_opcode_bytes();
=======
	if (!validate_number_parameter(params[1], offset))
		return;
	if (!validate_number_parameter(params[2], length))
		return;
	if (params.size() > 3 && !validate_number_parameter(params[3], bytes))
		return;
	if (!validate_cpu_space_parameter(params.size() > 4 ? params[4].c_str() : nullptr, AS_PROGRAM, space))
		return;
	if (space->device().memory().has_space(AS_OPCODES))
		decrypted_space = &space->device().memory().space(AS_OPCODES);
	else
		decrypted_space = space;

	/* determine the width of the bytes */
	device_disasm_interface *dasmintf;
	if (!space->device().interface(dasmintf))
	{
		m_console.printf("No disassembler available for %s\n", space->device().name());
		return;
	}
	minbytes = dasmintf->min_opcode_bytes();
	maxbytes = dasmintf->max_opcode_bytes();
>>>>>>> upstream/master
	byteswidth = 0;
	if (bytes)
	{
		byteswidth = (maxbytes + (minbytes - 1)) / minbytes;
		byteswidth *= (2 * minbytes) + 1;
	}

	/* open the file */
<<<<<<< HEAD
	f = fopen(param[0], "w");
	if (!f)
	{
		debug_console_printf(machine, "Error opening file '%s'\n", param[0]);
=======
	f = fopen(params[0].c_str(), "w");
	if (!f)
	{
		m_console.printf("Error opening file '%s'\n", params[0].c_str());
>>>>>>> upstream/master
		return;
	}

	/* now write the data out */
<<<<<<< HEAD
	for (UINT64 i = 0; i < length; )
	{
		int pcbyte = space->address_to_byte(offset + i) & space->bytemask();
		char output[512], disasm[200];
		const char *comment;
		offs_t tempaddr;
		int outdex = 0;
		int numbytes = 0;

		/* print the address */
		outdex += sprintf(&output[outdex], "%s: ", core_i64_hex_format((UINT32)space->byte_to_address(pcbyte), space->logaddrchars()));

		/* make sure we can translate the address */
		tempaddr = pcbyte;
		if (debug_cpu_translate(*space, TRANSLATE_FETCH_DEBUG, &tempaddr))
		{
			UINT8 opbuf[64], argbuf[64];

			/* fetch the bytes up to the maximum */
			for (numbytes = 0; numbytes < maxbytes; numbytes++)
			{
				opbuf[numbytes] = debug_read_opcode(*decrypted_space, pcbyte + numbytes, 1);
				argbuf[numbytes] = debug_read_opcode(*space, pcbyte + numbytes, 1);
			}

			/* disassemble the result */
			i += numbytes = space->device().debug()->disassemble(disasm, offset + i, opbuf, argbuf) & DASMFLAG_LENGTHMASK;
		}

		/* print the bytes */
		if (bytes)
		{
			int startdex = outdex;
			numbytes = space->address_to_byte(numbytes);
			for (j = 0; j < numbytes; j += minbytes)
				outdex += sprintf(&output[outdex], "%s ", core_i64_hex_format(debug_read_opcode(*decrypted_space, pcbyte + j, minbytes), minbytes * 2));
			if (outdex - startdex < byteswidth)
				outdex += sprintf(&output[outdex], "%*s", byteswidth - (outdex - startdex), "");
			outdex += sprintf(&output[outdex], "  ");
		}

		/* add the disassembly */
		sprintf(&output[outdex], "%s", disasm);

		/* attempt to add the comment */
		comment = space->device().debug()->comment_text(tempaddr);
		if (comment != NULL)
		{
			/* somewhat arbitrary guess as to how long most disassembly lines will be [column 60] */
			if (strlen(output) < 60)
			{
				/* pad the comment space out to 60 characters and null-terminate */
				for (outdex = (int)strlen(output); outdex < 60; outdex++)
					output[outdex] = ' ' ;
				output[outdex] = 0 ;

				sprintf(&output[strlen(output)], "// %s", comment) ;
			}
			else
				sprintf(&output[strlen(output)], "\t// %s", comment) ;
		}

		/* output the result */
		fprintf(f, "%s\n", output);
=======
	util::ovectorstream output;
	util::ovectorstream disasm;
	output.reserve(512);
	for (u64 i = 0; i < length; )
	{
		int pcbyte = space->address_to_byte(offset + i) & space->bytemask();
		const char *comment;
		offs_t tempaddr;
		int numbytes = 0;
		output.clear();
		output.rdbuf()->clear();
		disasm.clear();
		disasm.seekp(0);

		/* print the address */
		stream_format(output, "%0*X: ", space->logaddrchars(), u32(space->byte_to_address(pcbyte)));

		/* make sure we can translate the address */
		tempaddr = pcbyte;
		if (space->device().memory().translate(space->spacenum(), TRANSLATE_FETCH_DEBUG, tempaddr))
		{
			{
				u8 opbuf[64], argbuf[64];

				/* fetch the bytes up to the maximum */
				for (numbytes = 0; numbytes < maxbytes; numbytes++)
				{
					opbuf[numbytes] = m_cpu.read_opcode(*decrypted_space, pcbyte + numbytes, 1);
					argbuf[numbytes] = m_cpu.read_opcode(*space, pcbyte + numbytes, 1);
				}

				/* disassemble the result */
				i += numbytes = dasmintf->disassemble(disasm, offset + i, opbuf, argbuf) & DASMFLAG_LENGTHMASK;
			}

			/* print the bytes */
			if (bytes)
			{
				auto const startdex = output.tellp();
				numbytes = space->address_to_byte(numbytes);
				for (j = 0; j < numbytes; j += minbytes)
					stream_format(output, "%0*X ", minbytes * 2, m_cpu.read_opcode(*decrypted_space, pcbyte + j, minbytes));
				if ((output.tellp() - startdex) < byteswidth)
					stream_format(output, "%*s", byteswidth - (output.tellp() - startdex), "");
				stream_format(output, "  ");
			}
		}
		else
		{
			disasm << "<unmapped>";
			i += minbytes;
		}

		/* add the disassembly */
		disasm.put('\0');
		stream_format(output, "%s", &disasm.vec()[0]);

		/* attempt to add the comment */
		comment = space->device().debug()->comment_text(tempaddr);
		if (comment != nullptr)
		{
			/* somewhat arbitrary guess as to how long most disassembly lines will be [column 60] */
			if (output.tellp() < 60)
			{
				/* pad the comment space out to 60 characters and null-terminate */
				while (output.tellp() < 60) output.put(' ');

				stream_format(output, "// %s", comment);
			}
			else
				stream_format(output, "\t// %s", comment);
		}

		/* output the result */
		auto const &text(output.vec());
		fprintf(f, "%.*s\n", int(unsigned(text.size())), &text[0]);
>>>>>>> upstream/master
	}

	/* close the file */
	fclose(f);
<<<<<<< HEAD
	debug_console_printf(machine, "Data dumped successfully\n");
=======
	m_console.printf("Data dumped successfully\n");
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_trace_internal - functionality for
    trace over and trace info
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_trace_internal(running_machine &machine, int ref, int params, const char *param[], int trace_over)
{
	const char *action = NULL;
	device_t *cpu;
	FILE *f = NULL;
	const char *mode;
	std::string filename = param[0];

	/* replace macros */
	strreplace(filename, "{game}", machine.basename());

	/* validate parameters */
	if (!debug_command_parameter_cpu(machine, (params > 1) ? param[1] : NULL, &cpu))
		return;
	if (!debug_command_parameter_command(machine, action = param[2]))
=======
void debugger_commands::execute_trace_internal(int ref, const std::vector<std::string> &params, bool trace_over)
{
	const char *action = nullptr;
	bool detect_loops = true;
	bool logerror = false;
	device_t *cpu;
	FILE *f = nullptr;
	const char *mode;
	std::string filename = params[0];

	/* replace macros */
	strreplace(filename, "{game}", m_machine.basename());

	/* validate parameters */
	if (!validate_cpu_parameter(params.size() > 1 ? params[1].c_str() : nullptr, cpu))
		return;
	if (params.size() > 2)
	{
		std::stringstream stream;
		stream.str(params[2]);

		std::string flag;
		while (std::getline(stream, flag, '|'))
		{
			if (!core_stricmp(flag.c_str(), "noloop"))
				detect_loops = false;
			else if (!core_stricmp(flag.c_str(), "logerror"))
				logerror = true;
			else
			{
				m_console.printf("Invalid flag '%s'\n", flag.c_str());
				return;
			}
		}
	}
	if (!debug_command_parameter_command(action = (params.size() > 3) ? params[3].c_str() : nullptr))
>>>>>>> upstream/master
		return;

	/* open the file */
	if (core_stricmp(filename.c_str(), "off") != 0)
	{
		mode = "w";

		/* opening for append? */
		if ((filename[0] == '>') && (filename[1] == '>'))
		{
			mode = "a";
			filename = filename.substr(2);
		}

		f = fopen(filename.c_str(), mode);
		if (!f)
		{
<<<<<<< HEAD
			debug_console_printf(machine, "Error opening file '%s'\n", param[0]);
=======
			m_console.printf("Error opening file '%s'\n", params[0].c_str());
>>>>>>> upstream/master
			return;
		}
	}

	/* do it */
<<<<<<< HEAD
	cpu->debug()->trace(f, trace_over, action);
	if (f)
		debug_console_printf(machine, "Tracing CPU '%s' to file %s\n", cpu->tag(), filename.c_str());
	else
		debug_console_printf(machine, "Stopped tracing on CPU '%s'\n", cpu->tag());
=======
	cpu->debug()->trace(f, trace_over, detect_loops, logerror, action);
	if (f)
		m_console.printf("Tracing CPU '%s' to file %s\n", cpu->tag(), filename.c_str());
	else
		m_console.printf("Stopped tracing on CPU '%s'\n", cpu->tag());
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_trace - execute the trace command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_trace(running_machine &machine, int ref, int params, const char *param[])
{
	execute_trace_internal(machine, ref, params, param, 0);
=======
void debugger_commands::execute_trace(int ref, const std::vector<std::string> &params)
{
	execute_trace_internal(ref, params, false);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_traceover - execute the trace over command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_traceover(running_machine &machine, int ref, int params, const char *param[])
{
	execute_trace_internal(machine, ref, params, param, 1);
=======
void debugger_commands::execute_traceover(int ref, const std::vector<std::string> &params)
{
	execute_trace_internal(ref, params, true);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_traceflush - execute the trace flush command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_traceflush(running_machine &machine, int ref, int params, const char *param[])
{
	debug_cpu_flush_traces(machine);
=======
void debugger_commands::execute_traceflush(int ref, const std::vector<std::string> &params)
{
	m_cpu.flush_traces();
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_history - execute the history command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_history(running_machine &machine, int ref, int params, const char *param[])
{
	/* validate parameters */
	address_space *space, *decrypted_space;
	if (!debug_command_parameter_cpu_space(machine, (params > 0) ? param[0] : NULL, AS_PROGRAM, space))
		return;
	if (!debug_command_parameter_cpu_space(machine, (params > 0) ? param[0] : NULL, AS_DECRYPTED_OPCODES, decrypted_space))
		decrypted_space = space;

	UINT64 count = device_debug::HISTORY_SIZE;
	if (!debug_command_parameter_number(machine, param[1], &count))
=======
void debugger_commands::execute_history(int ref, const std::vector<std::string> &params)
{
	/* validate parameters */
	address_space *space, *decrypted_space;
	if (!validate_cpu_space_parameter(!params.empty() ? params[0].c_str() : nullptr, AS_PROGRAM, space))
		return;
	if (space->device().memory().has_space(AS_OPCODES))
		decrypted_space = &space->device().memory().space(AS_OPCODES);
	else
		decrypted_space = space;

	u64 count = device_debug::HISTORY_SIZE;
	if (params.size() > 1 && !validate_number_parameter(params[1], count))
>>>>>>> upstream/master
		return;

	/* further validation */
	if (count > device_debug::HISTORY_SIZE)
		count = device_debug::HISTORY_SIZE;

	device_debug *debug = space->device().debug();

	/* loop over lines */
<<<<<<< HEAD
	int maxbytes = debug->max_opcode_bytes();
=======
	device_disasm_interface *dasmintf;
	if (!space->device().interface(dasmintf))
	{
		m_console.printf("No disassembler available for %s\n", space->device().name());
		return;
	}
	int maxbytes = dasmintf->max_opcode_bytes();
>>>>>>> upstream/master
	for (int index = 0; index < (int) count; index++)
	{
		offs_t pc = debug->history_pc(-index);

		/* fetch the bytes up to the maximum */
		offs_t pcbyte = space->address_to_byte(pc) & space->bytemask();
<<<<<<< HEAD
		UINT8 opbuf[64], argbuf[64];
		for (int numbytes = 0; numbytes < maxbytes; numbytes++)
		{
			opbuf[numbytes] = debug_read_opcode(*decrypted_space, pcbyte + numbytes, 1);
			argbuf[numbytes] = debug_read_opcode(*space, pcbyte + numbytes, 1);
		}

		char buffer[200];
		debug->disassemble(buffer, pc, opbuf, argbuf);

		debug_console_printf(machine, "%s: %s\n", core_i64_hex_format(pc, space->logaddrchars()), buffer);
=======
		u8 opbuf[64], argbuf[64];
		for (int numbytes = 0; numbytes < maxbytes; numbytes++)
		{
			opbuf[numbytes] = m_cpu.read_opcode(*decrypted_space, pcbyte + numbytes, 1);
			argbuf[numbytes] = m_cpu.read_opcode(*space, pcbyte + numbytes, 1);
		}

		util::ovectorstream buffer;
		dasmintf->disassemble(buffer, pc, opbuf, argbuf);
		buffer.put('\0');

		m_console.printf("%0*X: %s\n", space->logaddrchars(), pc, &buffer.vec()[0]);
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
    execute_trackpc - execute the trackpc command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_trackpc(running_machine &machine, int ref, int params, const char *param[])
{
	// Gather the on/off switch (if present)
	UINT64 turnOn = true;
	if (!debug_command_parameter_number(machine, param[0], &turnOn))
		return;

	// Gather the cpu id (if present)
	device_t *cpu = NULL;
	if (!debug_command_parameter_cpu(machine, (params > 1) ? param[1] : NULL, &cpu))
		return;

	// Should we clear the existing data?
	UINT64 clear = false;
	if (!debug_command_parameter_number(machine, param[2], &clear))
=======
void debugger_commands::execute_trackpc(int ref, const std::vector<std::string> &params)
{
	// Gather the on/off switch (if present)
	bool turnOn = true;
	if (params.size() > 0 && !validate_boolean_parameter(params[0], turnOn))
		return;

	// Gather the cpu id (if present)
	device_t *cpu = nullptr;
	if (!validate_cpu_parameter((params.size() > 1) ? params[1].c_str() : nullptr, cpu))
		return;

	// Should we clear the existing data?
	bool clear = false;
	if (params.size() > 2 && !validate_boolean_parameter(params[2], clear))
>>>>>>> upstream/master
		return;

	cpu->debug()->set_track_pc((bool)turnOn);
	if (turnOn)
	{
		// Insert current pc
<<<<<<< HEAD
		if (debug_cpu_get_visible_cpu(machine) == cpu)
		{
			const offs_t pc = cpu->debug()->pc();
			cpu->debug()->set_track_pc_visited(pc);
		}
		debug_console_printf(machine, "PC tracking enabled\n");
	}
	else
	{
		debug_console_printf(machine, "PC tracking disabled\n");
=======
		if (m_cpu.get_visible_cpu() == cpu)
		{
			const offs_t pc = cpu->safe_pcbase();
			cpu->debug()->set_track_pc_visited(pc);
		}
		m_console.printf("PC tracking enabled\n");
	}
	else
	{
		m_console.printf("PC tracking disabled\n");
>>>>>>> upstream/master
	}

	if (clear)
		cpu->debug()->track_pc_data_clear();
}


/*-------------------------------------------------
    execute_trackmem - execute the trackmem command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_trackmem(running_machine &machine, int ref, int params, const char *param[])
{
	// Gather the on/off switch (if present)
	UINT64 turnOn = true;
	if (!debug_command_parameter_number(machine, param[0], &turnOn))
		return;

	// Gather the cpu id (if present)
	device_t *cpu = NULL;
	if (!debug_command_parameter_cpu(machine, (params > 1) ? param[1] : NULL, &cpu))
		return;

	// Should we clear the existing data?
	UINT64 clear = false;
	if (!debug_command_parameter_number(machine, param[2], &clear))
=======
void debugger_commands::execute_trackmem(int ref, const std::vector<std::string> &params)
{
	// Gather the on/off switch (if present)
	bool turnOn = true;
	if (params.size() > 0 && !validate_boolean_parameter(params[0], turnOn))
		return;

	// Gather the cpu id (if present)
	device_t *cpu = nullptr;
	if (!validate_cpu_parameter((params.size() > 1) ? params[1].c_str() : nullptr, cpu))
		return;

	// Should we clear the existing data?
	bool clear = false;
	if (params.size() > 2 && !validate_boolean_parameter(params[2], clear))
>>>>>>> upstream/master
		return;

	// Get the address space for the given cpu
	address_space *space;
<<<<<<< HEAD
	if (!debug_command_parameter_cpu_space(machine, (params > 1) ? param[1] : NULL, AS_PROGRAM, space))
=======
	if (!validate_cpu_space_parameter((params.size() > 1) ? params[1].c_str() : nullptr, AS_PROGRAM, space))
>>>>>>> upstream/master
		return;

	// Inform the CPU it's time to start tracking memory writes
	cpu->debug()->set_track_mem(turnOn);

	// Use the watchpoint system to catch memory writes
	space->enable_write_watchpoints(true);

	// Clear out the existing data if requested
	if (clear)
		space->device().debug()->track_mem_data_clear();
}


/*-------------------------------------------------
    execute_pcatmem - execute the pcatmem command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_pcatmem(running_machine &machine, int ref, int params, const char *param[])
{
	// Gather the required address parameter
	UINT64 address;
	if (!debug_command_parameter_number(machine, param[0], &address))
		return;

	// Gather the cpu id (if present)
	device_t *cpu = NULL;
	if (!debug_command_parameter_cpu(machine, (params > 1) ? param[1] : NULL, &cpu))
=======
void debugger_commands::execute_pcatmem(int ref, const std::vector<std::string> &params)
{
	// Gather the required address parameter
	u64 address;
	if (!validate_number_parameter(params[0], address))
		return;

	// Gather the cpu id (if present)
	device_t *cpu = nullptr;
	if (!validate_cpu_parameter((params.size() > 1) ? params[1].c_str() : nullptr, cpu))
>>>>>>> upstream/master
		return;

	// Get the address space for the given cpu
	address_space *space;
<<<<<<< HEAD
	if (!debug_command_parameter_cpu_space(machine, (params > 1) ? param[1] : NULL, ref, space))
		return;

	// Get the value of memory at the address
	const int nativeDataWidth = space->data_width() / 8;
	const UINT64 data = debug_read_memory(*space,
											space->address_to_byte(address),
											nativeDataWidth,
											true);

	// Recover the pc & print
	const address_spacenum spaceNum = (address_spacenum)ref;
	const offs_t result = space->device().debug()->track_mem_pc_from_space_address_data(spaceNum, address, data);
	if (result != (offs_t)(-1))
		debug_console_printf(machine, "%02x\n", result);
	else
		debug_console_printf(machine, "UNKNOWN PC\n");
=======
	if (!validate_cpu_space_parameter((params.size() > 1) ? params[1].c_str() : nullptr, ref, space))
		return;

	// Get the value of memory at the address
	const int native_data_width = space->data_width() / 8;
	const u64 data = m_cpu.read_memory(*space, space->address_to_byte(address), native_data_width, true);

	// Recover the pc & print
	const int space_num = (int)ref;
	const offs_t result = space->device().debug()->track_mem_pc_from_space_address_data(space_num, address, data);
	if (result != (offs_t)(-1))
		m_console.printf("%02x\n", result);
	else
		m_console.printf("UNKNOWN PC\n");
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_snap - execute the snapshot command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_snap(running_machine &machine, int ref, int params, const char *param[])
{
	/* if no params, use the default behavior */
	if (params == 0)
	{
		machine.video().save_active_screen_snapshots();
		debug_console_printf(machine, "Saved snapshot\n");
=======
void debugger_commands::execute_snap(int ref, const std::vector<std::string> &params)
{
	/* if no params, use the default behavior */
	if (params.empty())
	{
		m_machine.video().save_active_screen_snapshots();
		m_console.printf("Saved snapshot\n");
>>>>>>> upstream/master
	}

	/* otherwise, we have to open the file ourselves */
	else
	{
<<<<<<< HEAD
		const char *filename = param[0];
		int scrnum = (params > 1) ? atoi(param[1]) : 0;

		screen_device_iterator iter(machine.root_device());
		screen_device *screen = iter.byindex(scrnum);

		if ((screen == NULL) || !machine.render().is_live(*screen))
		{
			debug_console_printf(machine, "Invalid screen number '%d'\n", scrnum);
=======
		const char *filename = params[0].c_str();
		int scrnum = (params.size() > 1) ? atoi(params[1].c_str()) : 0;

		screen_device_iterator iter(m_machine.root_device());
		screen_device *screen = iter.byindex(scrnum);

		if ((screen == nullptr) || !m_machine.render().is_live(*screen))
		{
			m_console.printf("Invalid screen number '%d'\n", scrnum);
>>>>>>> upstream/master
			return;
		}

		std::string fname(filename);
		if (fname.find(".png") == -1)
			fname.append(".png");
<<<<<<< HEAD
		emu_file file(machine.options().snapshot_directory(), OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS);
		file_error filerr = file.open(fname.c_str());

		if (filerr != FILERR_NONE)
		{
			debug_console_printf(machine, "Error creating file '%s'\n", filename);
=======
		emu_file file(m_machine.options().snapshot_directory(), OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS);
		osd_file::error filerr = file.open(fname.c_str());

		if (filerr != osd_file::error::NONE)
		{
			m_console.printf("Error creating file '%s'\n", filename);
>>>>>>> upstream/master
			return;
		}

		screen->machine().video().save_snapshot(screen, file);
<<<<<<< HEAD
		debug_console_printf(machine, "Saved screen #%d snapshot as '%s'\n", scrnum, filename);
=======
		m_console.printf("Saved screen #%d snapshot as '%s'\n", scrnum, filename);
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
    execute_source - execute the source command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_source(running_machine &machine, int ref, int params, const char *param[])
{
	debug_cpu_source_script(machine, param[0]);
=======
void debugger_commands::execute_source(int ref, const std::vector<std::string> &params)
{
	m_cpu.source_script(params[0].c_str());
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_map - execute the map command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_map(running_machine &machine, int ref, int params, const char *param[])
{
	address_space *space;
	offs_t taddress;
	UINT64 address;
	int intention;

	/* validate parameters */
	if (!debug_command_parameter_number(machine, param[0], &address))
		return;

	/* CPU is implicit */
	if (!debug_command_parameter_cpu_space(machine, NULL, ref, space))
=======
void debugger_commands::execute_map(int ref, const std::vector<std::string> &params)
{
	address_space *space;
	offs_t taddress;
	u64 address;
	int intention;

	/* validate parameters */
	if (!validate_number_parameter(params[0], address))
		return;

	/* CPU is implicit */
	if (!validate_cpu_space_parameter(nullptr, ref, space))
>>>>>>> upstream/master
		return;

	/* do the translation first */
	for (intention = TRANSLATE_READ_DEBUG; intention <= TRANSLATE_FETCH_DEBUG; intention++)
	{
		static const char *const intnames[] = { "Read", "Write", "Fetch" };
		taddress = space->address_to_byte(address) & space->bytemask();
<<<<<<< HEAD
		if (debug_cpu_translate(*space, intention, &taddress))
		{
			const char *mapname = space->get_handler_string((intention == TRANSLATE_WRITE_DEBUG) ? ROW_WRITE : ROW_READ, taddress);
			debug_console_printf(machine, "%7s: %s logical == %s physical -> %s\n", intnames[intention & 3], core_i64_hex_format(address, space->logaddrchars()), core_i64_hex_format(space->byte_to_address(taddress), space->addrchars()), mapname);
		}
		else
			debug_console_printf(machine, "%7s: %s logical is unmapped\n", intnames[intention & 3], core_i64_hex_format(address, space->logaddrchars()));
=======
		if (space->device().memory().translate(space->spacenum(), intention, taddress))
		{
			const char *mapname = space->get_handler_string((intention == TRANSLATE_WRITE_DEBUG) ? read_or_write::WRITE : read_or_write::READ, taddress);
			m_console.printf(
					"%7s: %0*X logical == %0*X physical -> %s\n",
					intnames[intention & 3],
					space->logaddrchars(), address,
					space->addrchars(), space->byte_to_address(taddress),
					mapname);
		}
		else
			m_console.printf("%7s: %0*X logical is unmapped\n", intnames[intention & 3], space->logaddrchars(), address);
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
    execute_memdump - execute the memdump command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_memdump(running_machine &machine, int ref, int params, const char **param)
=======
void debugger_commands::execute_memdump(int ref, const std::vector<std::string> &params)
>>>>>>> upstream/master
{
	FILE *file;
	const char *filename;

<<<<<<< HEAD
	filename = (params == 0) ? "memdump.log" : param[0];

	debug_console_printf(machine, "Dumping memory to %s\n", filename);
=======
	filename = params.empty() ? "memdump.log" : params[0].c_str();

	m_console.printf("Dumping memory to %s\n", filename);
>>>>>>> upstream/master

	file = fopen(filename, "w");
	if (file)
	{
<<<<<<< HEAD
		machine.memory().dump(file);
=======
		memory_interface_iterator iter(m_machine.root_device());
		for (device_memory_interface &memory : iter)
			memory.dump(file);
>>>>>>> upstream/master
		fclose(file);
	}
}


/*-------------------------------------------------
    execute_symlist - execute the symlist command
-------------------------------------------------*/

static int CLIB_DECL symbol_sort_compare(const void *item1, const void *item2)
{
	const char *str1 = *(const char **)item1;
	const char *str2 = *(const char **)item2;
	return strcmp(str1, str2);
}

<<<<<<< HEAD
static void execute_symlist(running_machine &machine, int ref, int params, const char **param)
{
	device_t *cpu = NULL;
=======
void debugger_commands::execute_symlist(int ref, const std::vector<std::string> &params)
{
	device_t *cpu = nullptr;
>>>>>>> upstream/master
	const char *namelist[1000];
	symbol_table *symtable;
	int symnum, count = 0;

<<<<<<< HEAD

	if (param[0] != NULL)
	{
		/* validate parameters */
		if (!debug_command_parameter_cpu(machine, param[0], &cpu))
			return;
		symtable = &cpu->debug()->symtable();
		debug_console_printf(machine, "CPU '%s' symbols:\n", cpu->tag());
	}
	else
	{
		symtable = debug_cpu_get_global_symtable(machine);
		debug_console_printf(machine, "Global symbols:\n");
	}

	/* gather names for all symbols */
	for (symbol_entry *entry = symtable->first(); entry != NULL; entry = entry->next())
	{
		/* only display "register" type symbols */
		if (!entry->is_function())
		{
			namelist[count++] = entry->name();
=======
	if (!params.empty())
	{
		/* validate parameters */
		if (!validate_cpu_parameter(params[0].c_str(), cpu))
			return;
		symtable = &cpu->debug()->symtable();
		m_console.printf("CPU '%s' symbols:\n", cpu->tag());
	}
	else
	{
		symtable = m_cpu.get_global_symtable();
		m_console.printf("Global symbols:\n");
	}

	/* gather names for all symbols */
	for (auto &entry : symtable->entries())
	{
		/* only display "register" type symbols */
		if (!entry.second->is_function())
		{
			namelist[count++] = entry.second->name();
>>>>>>> upstream/master
			if (count >= ARRAY_LENGTH(namelist))
				break;
		}
	}

	/* sort the symbols */
	if (count > 1)
		qsort((void *)namelist, count, sizeof(namelist[0]), symbol_sort_compare);

	/* iterate over symbols and print out relevant ones */
	for (symnum = 0; symnum < count; symnum++)
	{
		const symbol_entry *entry = symtable->find(namelist[symnum]);
<<<<<<< HEAD
		assert(entry != NULL);
		UINT64 value = entry->value();

		/* only display "register" type symbols */
		debug_console_printf(machine, "%s = %s", namelist[symnum], core_i64_hex_format(value, 0));
		if (!entry->is_lval())
			debug_console_printf(machine, "  (read-only)");
		debug_console_printf(machine, "\n");
=======
		assert(entry != nullptr);
		u64 value = entry->value();

		/* only display "register" type symbols */
		m_console.printf("%s = %X", namelist[symnum], value);
		if (!entry->is_lval())
			m_console.printf("  (read-only)");
		m_console.printf("\n");
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
    execute_softreset - execute the softreset command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_softreset(running_machine &machine, int ref, int params, const char **param)
{
	machine.schedule_soft_reset();
=======
void debugger_commands::execute_softreset(int ref, const std::vector<std::string> &params)
{
	m_machine.schedule_soft_reset();
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_hardreset - execute the hardreset command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_hardreset(running_machine &machine, int ref, int params, const char **param)
{
	machine.schedule_hard_reset();
=======
void debugger_commands::execute_hardreset(int ref, const std::vector<std::string> &params)
{
	m_machine.schedule_hard_reset();
>>>>>>> upstream/master
}

/*-------------------------------------------------
    execute_images - lists all image devices with
    mounted files
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_images(running_machine &machine, int ref, int params, const char **param)
{
	image_interface_iterator iter(machine.root_device());
	for (device_image_interface *img = iter.first(); img != NULL; img = iter.next())
	{
		debug_console_printf(machine, "%s: %s\n",img->brief_instance_name(),img->exists() ? img->filename() : "[empty slot]");
	}
	if (iter.first() == NULL) {
		debug_console_printf(machine, "No image devices in this driver\n");
	}
=======
void debugger_commands::execute_images(int ref, const std::vector<std::string> &params)
{
	image_interface_iterator iter(m_machine.root_device());
	for (device_image_interface &img : iter)
		m_console.printf("%s: %s\n", img.brief_instance_name(), img.exists() ? img.filename() : "[empty slot]");
	if (iter.first() == nullptr)
		m_console.printf("No image devices in this driver\n");
>>>>>>> upstream/master
}

/*-------------------------------------------------
    execute_mount - execute the image mount command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_mount(running_machine &machine, int ref, int params, const char **param)
{
	image_interface_iterator iter(machine.root_device());
	bool done = false;
	for (device_image_interface *img = iter.first(); img != NULL; img = iter.next())
	{
		if (strcmp(img->brief_instance_name(),param[0])==0) {
			if (img->load(param[1])==IMAGE_INIT_FAIL) {
				debug_console_printf(machine, "Unable to mount file %s on %s\n",param[1],param[0]);
			} else {
				debug_console_printf(machine, "File %s mounted on %s\n",param[1],param[0]);
			}
=======
void debugger_commands::execute_mount(int ref, const std::vector<std::string> &params)
{
	bool done = false;
	for (device_image_interface &img : image_interface_iterator(m_machine.root_device()))
	{
		if (img.brief_instance_name() == params[0])
		{
			if (img.load(params[1]) != image_init_result::PASS)
				m_console.printf("Unable to mount file %s on %s\n", params[1], params[0]);
			else
				m_console.printf("File %s mounted on %s\n", params[1], params[0]);
>>>>>>> upstream/master
			done = true;
			break;
		}
	}
	if (!done)
<<<<<<< HEAD
		debug_console_printf(machine, "There is no image device :%s\n",param[0]);
=======
		m_console.printf("There is no image device :%s\n", params[0].c_str());
>>>>>>> upstream/master
}

/*-------------------------------------------------
    execute_unmount - execute the image unmount command
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_unmount(running_machine &machine, int ref, int params, const char **param)
{
	image_interface_iterator iter(machine.root_device());
	bool done = false;
	for (device_image_interface *img = iter.first(); img != NULL; img = iter.next())
	{
		if (strcmp(img->brief_instance_name(),param[0])==0) {
			img->unload();
			debug_console_printf(machine, "Unmounted file from : %s\n",param[0]);
=======
void debugger_commands::execute_unmount(int ref, const std::vector<std::string> &params)
{
	bool done = false;
	for (device_image_interface &img : image_interface_iterator(m_machine.root_device()))
	{
		if (img.brief_instance_name() == params[0])
		{
			img.unload();
			m_console.printf("Unmounted file from : %s\n", params[0]);
>>>>>>> upstream/master
			done = true;
			break;
		}
	}
	if (!done)
<<<<<<< HEAD
		debug_console_printf(machine, "There is no image device :%s\n",param[0]);
=======
		m_console.printf("There is no image device :%s\n", params[0]);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_input - debugger command to enter
    natural keyboard input
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_input(running_machine &machine, int ref, int params, const char **param)
{
	machine.ioport().natkeyboard().post_coded(param[0]);
=======
void debugger_commands::execute_input(int ref, const std::vector<std::string> &params)
{
	m_machine.ioport().natkeyboard().post_coded(params[0].c_str());
>>>>>>> upstream/master
}


/*-------------------------------------------------
    execute_dumpkbd - debugger command to natural
    keyboard codes
-------------------------------------------------*/

<<<<<<< HEAD
static void execute_dumpkbd(running_machine &machine, int ref, int params, const char **param)
{
	// was there a file specified?
	const char *filename = (params > 0) ? param[0] : NULL;
	FILE *file = NULL;
	if (filename != NULL)
	{
		// if so, open it
		file = fopen(filename, "w");
		if (file == NULL)
		{
			debug_console_printf(machine, "Cannot open \"%s\"\n", filename);
=======
void debugger_commands::execute_dumpkbd(int ref, const std::vector<std::string> &params)
{
	// was there a file specified?
	const char *filename = !params.empty() ? params[0].c_str() : nullptr;
	FILE *file = nullptr;
	if (filename != nullptr)
	{
		// if so, open it
		file = fopen(filename, "w");
		if (file == nullptr)
		{
			m_console.printf("Cannot open \"%s\"\n", filename);
>>>>>>> upstream/master
			return;
		}
	}

	// loop through all codes
<<<<<<< HEAD
	std::string buffer = machine.ioport().natkeyboard().dump();

	// and output it as appropriate
	if (file != NULL)
		fprintf(file, "%s\n", buffer.c_str());
	else
		debug_console_printf(machine, "%s\n", buffer.c_str());

	// cleanup
	if (file != NULL)
=======
	std::string buffer = m_machine.ioport().natkeyboard().dump();

	// and output it as appropriate
	if (file != nullptr)
		fprintf(file, "%s\n", buffer.c_str());
	else
		m_console.printf("%s\n", buffer.c_str());

	// cleanup
	if (file != nullptr)
>>>>>>> upstream/master
		fclose(file);
}
