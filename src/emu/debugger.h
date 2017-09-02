// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria, Aaron Giles
/****************************************************************************

    debugger.h

    General debugging interfaces
****************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __DEBUGGER_H__
#define __DEBUGGER_H__

#include "debug/debugcpu.h"


/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

/* ----- core debugger functions ----- */

/* initialize the debugger */
void debugger_init(running_machine &machine);

/* redraw the current video display */
void debugger_refresh_display(running_machine &machine);

/* OSD can call this to safely flush all traces in the event of a crash */
void debugger_flush_all_traces_on_abnormal_exit(void);



/***************************************************************************
    CPU CORE INLINE FUNCTIONS
***************************************************************************/

/*-------------------------------------------------
    debugger_instruction_hook - CPU cores call
    this once per instruction from CPU cores
-------------------------------------------------*/

INLINE void debugger_instruction_hook(device_t *device, offs_t curpc)
{
#ifndef MAME_DEBUG_FAST
	if ((device->machine().debug_flags & DEBUG_FLAG_CALL_HOOK) != 0)
		device->debug()->instruction_hook(curpc);
#endif
}


/*-------------------------------------------------
    debugger_exception_hook - CPU cores call this
    anytime an exception is generated
-------------------------------------------------*/

INLINE void debugger_exception_hook(device_t *device, int exception)
{
	if ((device->machine().debug_flags & DEBUG_FLAG_ENABLED) != 0)
		device->debug()->exception_hook(exception);
}
=======
#ifndef MAME_EMU_DEBUGGER_H
#define MAME_EMU_DEBUGGER_H

#pragma once


// ======================> debugger_manager

class debugger_manager
{
public:
	// construction/destruction
	debugger_manager(running_machine &machine);
	~debugger_manager();

	// break into the debugger
	void debug_break();

	bool within_instruction_hook();

	// redraw the current video display
	void refresh_display();

	// getters
	running_machine &machine() const { return m_machine; }
	debugger_commands &commands() const { return *m_commands; }
	debugger_cpu &cpu() const { return *m_cpu; }
	debugger_console &console() const { return *m_console; }

private:
	running_machine &   m_machine;

	std::unique_ptr<debugger_commands> m_commands;
	std::unique_ptr<debugger_cpu> m_cpu;
	std::unique_ptr<debugger_console> m_console;
};


/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

/* OSD can call this to safely flush all traces in the event of a crash */
void debugger_flush_all_traces_on_abnormal_exit();
>>>>>>> upstream/master



/***************************************************************************
<<<<<<< HEAD
    CPU EXECUTION SYSTEM INLINE FUNCTIONS
***************************************************************************/

/*-------------------------------------------------
    debugger_start_cpu_hook - the CPU execution
    system calls this hook before beginning
    execution for the given CPU
-------------------------------------------------*/

INLINE void debugger_start_cpu_hook(device_t *device, const attotime &endtime)
{
	if ((device->machine().debug_flags & DEBUG_FLAG_ENABLED) != 0)
		device->debug()->start_hook(endtime);
}


/*-------------------------------------------------
    debugger_stop_cpu_hook - the CPU execution
    system calls this hook when ending execution
    for the given CPU
-------------------------------------------------*/

INLINE void debugger_stop_cpu_hook(device_t *device)
{
	if ((device->machine().debug_flags & DEBUG_FLAG_ENABLED) != 0)
		device->debug()->stop_hook();
}


/*-------------------------------------------------
    debugger_interrupt_hook - the CPU execution
    system calls this hook when an interrupt is
    acknowledged
-------------------------------------------------*/

INLINE void debugger_interrupt_hook(device_t *device, int irqline)
{
	if ((device->machine().debug_flags & DEBUG_FLAG_ENABLED) != 0)
		device->debug()->interrupt_hook(irqline);
}
=======
    CPU CORE STATIC FUNCTIONS
***************************************************************************/

void debugger_instruction_hook(device_t *device, offs_t curpc);
void debugger_exception_hook(device_t *device, int exception);
>>>>>>> upstream/master



/***************************************************************************
<<<<<<< HEAD
    GENERAL INLINE FUNCTIONS
***************************************************************************/

/*-------------------------------------------------
    debugger_break - stop in the debugger at the
    next opportunity
-------------------------------------------------*/

INLINE void debugger_break(running_machine &machine)
{
	if ((machine.debug_flags & DEBUG_FLAG_ENABLED) != 0)
		debug_cpu_get_visible_cpu(machine)->debug()->halt_on_next_instruction("Internal breakpoint\n");
}


/*-------------------------------------------------
    debugger_within_instruction_hook - call this
    to determine if the debugger is currently
    halted within the instruction hook
-------------------------------------------------*/

INLINE int debugger_within_instruction_hook(running_machine &machine)
{
	if ((machine.debug_flags & DEBUG_FLAG_ENABLED) != 0)
		return debug_cpu_within_instruction_hook(machine);
	return FALSE;
}


#endif  /* __DEBUGGER_H__ */
=======
    CPU EXECUTION SYSTEM STATIC FUNCTIONS
***************************************************************************/

void debugger_start_cpu_hook(device_t *device, const attotime &endtime);
void debugger_stop_cpu_hook(device_t *device);
void debugger_interrupt_hook(device_t *device, int irqline);


#endif // MAME_EMU_DEBUGGER_H
>>>>>>> upstream/master
