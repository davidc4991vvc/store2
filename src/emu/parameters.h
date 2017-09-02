// license:BSD-3-Clause
// copyright-holders:Olivier Galibert,Aaron Giles
/***************************************************************************

    parameters.h

    Per-game parameters handling.

***************************************************************************/

#pragma once

#ifndef __EMU_H__
#error Dont include this file directly; include emu.h instead.
#endif

<<<<<<< HEAD
#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__
=======
#ifndef MAME_EMU_PARAMETERS_H
#define MAME_EMU_PARAMETERS_H
>>>>>>> upstream/master


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> parameters_manager

class parameters_manager
{
	DISABLE_COPYING(parameters_manager);

public:
	// construction/destruction
	parameters_manager(running_machine &machine);

	// getters
	running_machine &machine() const { return m_machine; }
	std::string lookup(std::string tag) const;

	// setters
	void add(std::string tag, std::string value);

private:
	// internal state
	running_machine &       m_machine;              // reference to owning machine
<<<<<<< HEAD
	tagmap_t<std::string>       m_parameters;
};

#endif  // __INPTPORT_H__ */
=======
	std::unordered_map<std::string,std::string>       m_parameters;
};

#endif  // MAME_EMU_PARAMETERS_H
>>>>>>> upstream/master
