// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Mullard SAA5050 Teletext Character Generator emulation

**********************************************************************
                            _____   _____
                   Vss   1 |*    \_/     | 28  DE
                   _SI   2 |             | 27  PO
                 _DATA   3 |             | 26  LOSE
                    D1   4 |   SAA5050   | 25  BLAN
                    D2   5 |   SAA5051   | 24  R
                    D3   6 |   SAA5052   | 23  G
                    D4   7 |   SAA5053   | 22  B
                    D5   8 |   SAA5054   | 21  Y
                    D6   9 |   SAA5055   | 20  F1
                    D7  10 |   SAA5056   | 19  TR6
                  DLIM  11 |   SAA5057   | 18  Vdd
                  _GLR  12 |             | 17  N/C
                   DEW  13 |             | 16  _TLC
                   CRS  14 |_____________| 15  _BCS

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SAA5050__
#define __SAA5050__

#include "emu.h"
=======
#ifndef MAME_VIDEO_SAA5050_H
#define MAME_VIDEO_SAA5050_H

#pragma once

>>>>>>> upstream/master



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_SAA5050_D_CALLBACK(_read) \
	devcb = &saa5050_device::set_d_rd_callback(*device, DEVCB_##_read);


#define MCFG_SAA5050_SCREEN_SIZE(_cols, _rows, _size) \
	saa5050_device::static_set_screen_size(*device, _cols, _rows, _size);



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> saa5050_device

class saa5050_device :  public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	saa5050_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	saa5050_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	static void static_set_screen_size(device_t &device, int cols, int rows, int size) { downcast<saa5050_device &>(device).m_cols = cols; downcast<saa5050_device &>(device).m_rows = rows; downcast<saa5050_device &>(device).m_size = size; }

	template<class _Object> static devcb_base &set_d_rd_callback(device_t &device, _Object object) { return downcast<saa5050_device &>(device).m_read_d.set_callback(object); }

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
=======
	saa5050_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	static void static_set_screen_size(device_t &device, int cols, int rows, int size) { downcast<saa5050_device &>(device).m_cols = cols; downcast<saa5050_device &>(device).m_rows = rows; downcast<saa5050_device &>(device).m_size = size; }

	template <class Object> static devcb_base &set_d_rd_callback(device_t &device, Object &&cb) { return downcast<saa5050_device &>(device).m_read_d.set_callback(std::forward<Object>(cb)); }

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master

	DECLARE_WRITE_LINE_MEMBER( crs_w );
	DECLARE_WRITE_LINE_MEMBER( dew_w );
	DECLARE_WRITE_LINE_MEMBER( lose_w );
<<<<<<< HEAD
	void write(UINT8 data);
=======
	void write(uint8_t data);
>>>>>>> upstream/master
	DECLARE_WRITE_LINE_MEMBER( f1_w );
	DECLARE_WRITE_LINE_MEMBER( tr6_w );
	int get_rgb();

	// NOTE: the following are provided for convenience only, SAA5050 is not a display controller
	// this emulates the common setup where bit 7 of data inverts the display, and the
	// bottom half of a double height row gets the same character data as the top half
<<<<<<< HEAD
	UINT32 screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
=======
	uint32_t screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);

protected:
	saa5050_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	enum
	{
		NUL = 0,
		ALPHA_RED,
		ALPHA_GREEN,
		ALPHA_YELLOW,
		ALPHA_BLUE,
		ALPHA_MAGENTA,
		ALPHA_CYAN,
		ALPHA_WHITE,
		FLASH,
		STEADY,
		END_BOX,
		START_BOX,
		NORMAL_HEIGHT,
		DOUBLE_HEIGHT,
		S0,
		S1,
		DLE,
		GRAPHICS_RED,
		GRAPHICS_GREEN,
		GRAPHICS_YELLOW,
		GRAPHICS_BLUE,
		GRAPHICS_MAGENTA,
		GRAPHICS_CYAN,
		GRAPHICS_WHITE,
		CONCEAL_DISPLAY,
		CONTIGUOUS_GFX,
		SEPARATED_GFX,
		ESC,
		BLACK_BACKGROUND,
		NEW_BACKGROUND,
		HOLD_GRAPHICS,
		RELEASE_GRAPHICS
	};

<<<<<<< HEAD
	void process_control_character(UINT8 data);
	void set_next_chartype();
	UINT16 get_gfx_data(UINT8 data, offs_t row, bool separated);
	UINT16 get_rom_data(UINT8 data, offs_t row);
	UINT16 character_rounding(UINT16 a, UINT16 b);
	void get_character_data(UINT8 data);

	required_region_ptr<UINT8> m_char_rom;

	devcb_read8    m_read_d;

	UINT8 m_code;
	UINT8 m_held_char;
	UINT8 m_next_chartype;
	UINT8 m_curr_chartype;
	UINT8 m_held_chartype;
	UINT16 m_char_data;
=======
	void process_control_character(uint8_t data);
	void set_next_chartype();
	uint16_t get_gfx_data(uint8_t data, offs_t row, bool separated);
	uint16_t get_rom_data(uint8_t data, offs_t row);
	uint16_t character_rounding(uint16_t a, uint16_t b);
	void get_character_data(uint8_t data);

	required_region_ptr<uint8_t> m_char_rom;

	devcb_read8    m_read_d;

	uint8_t m_code;
	uint8_t m_held_char;
	uint8_t m_next_chartype;
	uint8_t m_curr_chartype;
	uint8_t m_held_chartype;
	uint16_t m_char_data;
>>>>>>> upstream/master
	int m_bit;
	rgb_t m_color;
	int m_crs;
	int m_ra;
	int m_bg;
	int m_fg;
	int m_prev_col;
	bool m_graphics;
	bool m_separated;
	bool m_flash;
	bool m_boxed;
	bool m_double_height;
	bool m_double_height_old;
	bool m_double_height_bottom_row;
	bool m_double_height_prev_row;
	bool m_hold_char;
	bool m_hold_clear;
	bool m_hold_off;
	int m_frame_count;

	int m_cols;
	int m_rows;
	int m_size;
};


// ======================> saa5051_device

class saa5051_device :  public saa5050_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	saa5051_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
=======
	saa5051_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};


// ======================> saa5052_device

class saa5052_device :  public saa5050_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	saa5052_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
=======
	saa5052_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};


// ======================> saa5053_device

class saa5053_device :  public saa5050_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	saa5053_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
=======
	saa5053_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};


// ======================> saa5054_device

class saa5054_device :  public saa5050_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	saa5054_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
=======
	saa5054_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};


// ======================> saa5055_device

class saa5055_device :  public saa5050_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	saa5055_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
=======
	saa5055_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};


// ======================> saa5056_device

class saa5056_device :  public saa5050_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	saa5056_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
=======
	saa5056_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};


// ======================> saa5057_device

class saa5057_device :  public saa5050_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	saa5057_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
=======
	saa5057_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type SAA5050; // English
extern const device_type SAA5051; // German
extern const device_type SAA5052; // Swedish/Finnish
extern const device_type SAA5053; // Italian
extern const device_type SAA5054; // Belgian
extern const device_type SAA5055; // US ASCII
extern const device_type SAA5056; // Hebrew
extern const device_type SAA5057; // Cyrillic



#endif
=======
DECLARE_DEVICE_TYPE(SAA5050, saa5050_device) // English
DECLARE_DEVICE_TYPE(SAA5051, saa5051_device) // German
DECLARE_DEVICE_TYPE(SAA5052, saa5052_device) // Swedish/Finnish
DECLARE_DEVICE_TYPE(SAA5053, saa5053_device) // Italian
DECLARE_DEVICE_TYPE(SAA5054, saa5054_device) // Belgian
DECLARE_DEVICE_TYPE(SAA5055, saa5055_device) // US ASCII
DECLARE_DEVICE_TYPE(SAA5056, saa5056_device) // Hebrew
DECLARE_DEVICE_TYPE(SAA5057, saa5057_device) // Cyrillic

#endif // MAME_VIDEO_SAA5050_H
>>>>>>> upstream/master
