// license:BSD-3-Clause
// copyright-holders:Nathan Woods, Miodrag Milanovic
/***************************************************************************

    image.h

    Core image interface functions and definitions.

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __IMAGE_H__
#define __IMAGE_H__

void image_init(running_machine &machine);
void image_postdevice_init(running_machine &machine);
std::string &image_mandatory_scan(running_machine &machine, std::string &mandatory);

extern struct io_procs image_ioprocs;

void image_battery_load_by_name(emu_options &options, const char *filename, void *buffer, int length, int fill);
void image_battery_load_by_name(emu_options &options, const char *filename, void *buffer, int length, void *def_buffer);
void image_battery_save_by_name(emu_options &options, const char *filename, const void *buffer, int length);

#endif /* __IMAGE_H__ */
=======
#ifndef MAME_EMU_IMAGE_H
#define MAME_EMU_IMAGE_H

#pragma once

// ======================> image_manager

class image_manager
{
public:
	// construction/destruction
	image_manager(running_machine &machine);

	void unload_all();
	void postdevice_init();

	// getters
	running_machine &machine() const { return m_machine; }
private:
	void config_load(config_type cfg_type, util::xml::data_node const *parentnode);
	void config_save(config_type cfg_type, util::xml::data_node *parentnode);

	void options_extract();
	int write_config(emu_options &options, const char *filename, const game_driver *gamedrv);

	// internal state
	running_machine &   m_machine;                  // reference to our machine
};

#endif /* MAME_EMU_IMAGE_H */
>>>>>>> upstream/master
