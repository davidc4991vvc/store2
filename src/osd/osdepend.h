// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    osdepend.h

    OS-dependent code interface.

*******************************************************************c********/

#pragma once

<<<<<<< HEAD
#ifndef __OSDEPEND_H__
#define __OSDEPEND_H__
=======
#ifndef MAME_OSD_OSDEPEND_H
#define MAME_OSD_OSDEPEND_H
>>>>>>> upstream/master

#include "emucore.h"
#include "osdcore.h"
#include "unicode.h"
<<<<<<< HEAD
#include "cliopts.h"
=======
#include "../frontend/mame/ui/menuitem.h"

#include <memory>
#include <string>
#include <vector>
>>>>>>> upstream/master


// forward references
class input_type_entry;     // FIXME: including emu.h does not work because emu.h includes osdepend.h


//============================================================
//  TYPE DEFINITIONS
//============================================================

// ======================> osd_font interface

class osd_font
{
public:
<<<<<<< HEAD
	virtual ~osd_font() {}

	virtual bool open(const char *font_path, const char *name, int &height) = 0;
	virtual void close() = 0;
	virtual bool get_bitmap(unicode_char chnum, bitmap_argb32 &bitmap, INT32 &width, INT32 &xoffs, INT32 &yoffs) = 0;
=======
	typedef std::unique_ptr<osd_font> ptr;

	virtual ~osd_font() { }

	/** attempt to "open" a handle to the font with the given name */
	virtual bool open(std::string const &font_path, std::string const &name, int &height) = 0;

	/** release resources associated with a given OSD font */
	virtual void close() = 0;

	/*!
	 * allocate and populate a BITMAP_FORMAT_ARGB32 bitmap containing
	 * the pixel values rgb_t(0xff,0xff,0xff,0xff) or
	 * rgb_t(0x00,0xff,0xff,0xff) for each pixel of a black & white font
	 */
	virtual bool get_bitmap(char32_t chnum, bitmap_argb32 &bitmap, std::int32_t &width, std::int32_t &xoffs, std::int32_t &yoffs) = 0;
>>>>>>> upstream/master
};

// ======================> osd_interface

// description of the currently-running machine
class osd_interface
{
public:

	// general overridables
	virtual void init(running_machine &machine) = 0;
	virtual void update(bool skip_redraw) = 0;

	// debugger overridables
	virtual void init_debugger() = 0;
	virtual void wait_for_debugger(device_t &device, bool firststop) = 0;

	// audio overridables
<<<<<<< HEAD
	virtual void update_audio_stream(const INT16 *buffer, int samples_this_frame) = 0;
=======
	virtual void update_audio_stream(const int16_t *buffer, int samples_this_frame) = 0;
>>>>>>> upstream/master
	virtual void set_mastervolume(int attenuation) = 0;
	virtual bool no_sound() = 0;

	// input overridables
	virtual void customize_input_type_list(simple_list<input_type_entry> &typelist) = 0;

	// video overridables
<<<<<<< HEAD
	virtual void *get_slider_list() = 0; // FIXME: returns slider_state *

	// font interface
	virtual osd_font *font_alloc() = 0;
=======
	virtual void add_audio_to_recording(const int16_t *buffer, int samples_this_frame) = 0;
	virtual std::vector<ui::menu_item> get_slider_list() = 0;

	// font interface
	virtual osd_font::ptr font_alloc() = 0;
	virtual bool get_font_families(std::string const &font_path, std::vector<std::pair<std::string, std::string> > &result) = 0;
>>>>>>> upstream/master

	// command option overrides
	virtual bool execute_command(const char *command) = 0;

	// midi interface
	virtual osd_midi_device *create_midi_device() = 0;

protected:
	virtual ~osd_interface() { }
};

<<<<<<< HEAD
#endif  /* __OSDEPEND_H__ */
=======
#endif  // MAME_OSD_OSDEPEND_H
>>>>>>> upstream/master
