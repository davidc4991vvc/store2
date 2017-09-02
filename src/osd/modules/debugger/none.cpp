// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
//============================================================
//
//  none.c - stubs for linking when NO_DEBUGGER is defined
//
//============================================================

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "debug_module.h"
#include "modules/osdmodule.h"

#include "debug/debugcpu.h"
<<<<<<< HEAD
=======
#include "debugger.h"
>>>>>>> upstream/master

class debug_none : public osd_module, public debug_module
{
public:
	debug_none()
	: osd_module(OSD_DEBUG_PROVIDER, "none"), debug_module(),
<<<<<<< HEAD
		m_machine(NULL)
=======
		m_machine(nullptr)
>>>>>>> upstream/master
	{
	}

	virtual ~debug_none() { }

<<<<<<< HEAD
	virtual int init(const osd_options &options) { return 0; }
	virtual void exit() { }

	virtual void init_debugger(running_machine &machine);
	virtual void wait_for_debugger(device_t &device, bool firststop);
	virtual void debugger_update();
=======
	virtual int init(const osd_options &options) override { return 0; }
	virtual void exit() override { }

	virtual void init_debugger(running_machine &machine) override;
	virtual void wait_for_debugger(device_t &device, bool firststop) override;
	virtual void debugger_update() override;
>>>>>>> upstream/master

private:
	running_machine *m_machine;
};

void debug_none::init_debugger(running_machine &machine)
{
	m_machine = &machine;
}

void debug_none::wait_for_debugger(device_t &device, bool firststop)
{
<<<<<<< HEAD
	debug_cpu_get_visible_cpu(*m_machine)->debug()->go();
=======
	m_machine->debugger().cpu().get_visible_cpu()->debug()->go();
>>>>>>> upstream/master
}

void debug_none::debugger_update()
{
}

MODULE_DEFINITION(DEBUG_NONE, debug_none)
