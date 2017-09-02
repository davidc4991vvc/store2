// license:BSD-3-Clause
// copyright-holders:Olivier Galibert, Aaron Giles
/***************************************************************************

    parameters.c

    Per-game parameters handling.

***************************************************************************/

#include "emu.h"

parameters_manager::parameters_manager(running_machine &machine)
	: m_machine(machine)
{
}

std::string parameters_manager::lookup(std::string tag) const
{
<<<<<<< HEAD
	return m_parameters.find(tag.c_str());
=======
	auto search = m_parameters.find(tag);
	return (search!=m_parameters.end()) ? search->second : "";
>>>>>>> upstream/master
}

void parameters_manager::add(std::string tag, std::string value)
{
<<<<<<< HEAD
	m_parameters.add(tag.c_str(), value);
=======
	m_parameters.insert(std::make_pair(tag, value));
>>>>>>> upstream/master
}
