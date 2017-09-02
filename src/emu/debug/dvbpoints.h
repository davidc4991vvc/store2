// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/*********************************************************************

    dvbpoints.h

    Breakpoint debugger view.

***************************************************************************/

<<<<<<< HEAD
#ifndef __DVBPOINTS_H__
#define __DVBPOINTS_H__
=======
#ifndef MAME_EMU_DEBUG_DVBPOINTS_H
#define MAME_EMU_DEBUG_DVBPOINTS_H

#pragma once
>>>>>>> upstream/master

#include "debugvw.h"
#include "debugcpu.h"


//**************************************************************************
//  CONSTANTS
//**************************************************************************


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// debug view for breakpoints
class debug_view_breakpoints : public debug_view
{
<<<<<<< HEAD
	friend resource_pool_object<debug_view_breakpoints>::~resource_pool_object();
=======
>>>>>>> upstream/master
	friend class debug_view_manager;

	// construction/destruction
	debug_view_breakpoints(running_machine &machine, debug_view_osd_update_func osdupdate, void *osdprivate);
	virtual ~debug_view_breakpoints();

<<<<<<< HEAD
public:
	// getters
	// setters

protected:
	// view overrides
	virtual void view_update();
	virtual void view_click(const int button, const debug_view_xy& pos);
=======
protected:
	// view overrides
	virtual void view_update() override;
	virtual void view_click(const int button, const debug_view_xy& pos) override;
>>>>>>> upstream/master

private:
	// internal helpers
	void enumerate_sources();
<<<<<<< HEAD
	void pad_astring_to_length(std::string& str, int len);
=======
	void pad_ostream_to_length(std::ostream& str, int len);
>>>>>>> upstream/master
	void gather_breakpoints();


	// internal state
	int (*m_sortType)(void const *, void const *);
	std::vector<device_debug::breakpoint *> m_buffer;
};

<<<<<<< HEAD

#endif
=======
#endif // MAME_EMU_DEBUG_DVBPOINTS_H
>>>>>>> upstream/master
