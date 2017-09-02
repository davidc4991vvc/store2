// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
/***************************************************************************

        Hitachi HD44780 LCD controller

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __HD44780_H__
#define __HD44780_H__
=======
#ifndef MAME_VIDEO_HD44780_H
#define MAME_VIDEO_HD44780_H

#pragma once
>>>>>>> upstream/master


#define MCFG_HD44780_ADD( _tag ) \
	MCFG_DEVICE_ADD( _tag, HD44780, 0 )

#define MCFG_KS0066_F05_ADD( _tag ) \
	MCFG_DEVICE_ADD( _tag, KS0066_F05, 0 )

#define MCFG_HD44780_LCD_SIZE(_lines, _chars) \
	hd44780_device::static_set_lcd_size(*device, _lines, _chars);

<<<<<<< HEAD
#define MCFG_HD44780_PIXEL_UPDATE_CB(_cb) \
	hd44780_device::static_set_pixel_update_cb(*device, _cb);
=======
#define MCFG_HD44780_PIXEL_UPDATE_CB(_class, _method) \
	hd44780_device::static_set_pixel_update_cb(*device, hd44780_device::pixel_update_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
typedef void (*hd44780_pixel_update_func)(device_t &device, bitmap_ind16 &bitmap, UINT8 line, UINT8 pos, UINT8 y, UINT8 x, int state);
#define HD44780_PIXEL_UPDATE(name) void name(device_t &device, bitmap_ind16 &bitmap, UINT8 line, UINT8 pos, UINT8 y, UINT8 x, int state)
=======
#define HD44780_PIXEL_UPDATE(name) void name(bitmap_ind16 &bitmap, uint8_t line, uint8_t pos, uint8_t y, uint8_t x, int state)
>>>>>>> upstream/master


// ======================> hd44780_device

<<<<<<< HEAD
class hd44780_device :  public device_t
{
public:
	// construction/destruction
	hd44780_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	hd44780_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// static configuration helpers
	static void static_set_lcd_size(device_t &device, int _lines, int _chars) { hd44780_device &dev=downcast<hd44780_device &>(device); dev.m_lines = _lines; dev.m_chars = _chars; }
	static void static_set_pixel_update_cb(device_t &device, hd44780_pixel_update_func _cb) { downcast<hd44780_device &>(device).m_pixel_update_func = _cb; }
=======
class hd44780_device : public device_t
{
public:
	typedef device_delegate<void (bitmap_ind16 &bitmap, uint8_t line, uint8_t pos, uint8_t y, uint8_t x, int state)> pixel_update_delegate;

	// construction/destruction
	hd44780_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration helpers
	static void static_set_lcd_size(device_t &device, int _lines, int _chars) { hd44780_device &dev=downcast<hd44780_device &>(device); dev.m_lines = _lines; dev.m_chars = _chars; }
	static void static_set_pixel_update_cb(device_t &device, pixel_update_delegate &&cb) { downcast<hd44780_device &>(device).m_pixel_update_cb = std::move(cb); }
>>>>>>> upstream/master

	// device interface
	virtual DECLARE_WRITE8_MEMBER(write);
	virtual DECLARE_READ8_MEMBER(read);
	virtual DECLARE_WRITE8_MEMBER(control_write);
	virtual DECLARE_READ8_MEMBER(control_read);
	virtual DECLARE_WRITE8_MEMBER(data_write);
	virtual DECLARE_READ8_MEMBER(data_read);

<<<<<<< HEAD
	const UINT8 *render();
	virtual UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
=======
	const uint8_t *render();
	virtual uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

protected:
	hd44780_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master

	// charset
	enum
	{
		CHARSET_HD44780_A00,
		CHARSET_KS0066_F05 /*,
<<<<<<< HEAD
        CHARSET_HD44780_A01,
        CHARSET_HD44780_A02,
        CHARSET_KS0066_F00,
        CHARSET_KS0066_F03,
        CHARSET_KS0066_F04,
        CHARSET_KS0066_F06,
        CHARSET_KS0066_F59
        */
=======
		CHARSET_HD44780_A01,
		CHARSET_HD44780_A02,
		CHARSET_KS0066_F00,
		CHARSET_KS0066_F03,
		CHARSET_KS0066_F04,
		CHARSET_KS0066_F06,
		CHARSET_KS0066_F59
		*/
>>>>>>> upstream/master
	};

	void set_charset_type(int type);

private:
	// internal helper
<<<<<<< HEAD
	void set_busy_flag(UINT16 usec);
=======
	void set_busy_flag(uint16_t usec);
>>>>>>> upstream/master
	void correct_ac();
	void update_ac(int direction);
	void update_nibble(int rs, int rw);
	void shift_display(int direction);
<<<<<<< HEAD
	void pixel_update(bitmap_ind16 &bitmap, UINT8 line, UINT8 pos, UINT8 y, UINT8 x, int state);

	// internal state
	static const device_timer_id TIMER_BUSY = 0;
	static const device_timer_id TIMER_BLINKING = 1;
=======
	void pixel_update(bitmap_ind16 &bitmap, uint8_t line, uint8_t pos, uint8_t y, uint8_t x, int state);

	// internal state
	static constexpr device_timer_id TIMER_BUSY = 0;
	static constexpr device_timer_id TIMER_BLINKING = 1;
>>>>>>> upstream/master

	emu_timer * m_blink_timer;
	emu_timer * m_busy_timer;

<<<<<<< HEAD
	UINT8       m_lines;          // number of lines
	UINT8       m_chars;          // chars for line
	hd44780_pixel_update_func m_pixel_update_func; // pixel update callback

	bool        m_busy_flag;      // busy flag
	UINT8       m_ddram[0x80];    // internal display data RAM
	UINT8       m_cgram[0x40];    // internal chargen RAM
	UINT8 *     m_cgrom;          // internal chargen ROM
	int         m_ac;             // address counter
	UINT8       m_dr;             // data register
	UINT8       m_ir;             // instruction register
	UINT8       m_active_ram;     // DDRAM or CGRAM
=======
	uint8_t       m_lines;          // number of lines
	uint8_t       m_chars;          // chars for line
	pixel_update_delegate m_pixel_update_cb; // pixel update callback

	bool        m_busy_flag;      // busy flag
	uint8_t       m_ddram[0x80];    // internal display data RAM
	uint8_t       m_cgram[0x40];    // internal chargen RAM
	uint8_t const *m_cgrom;
	optional_region_ptr<uint8_t> m_cgrom_region; // internal chargen ROM
	int         m_ac;             // address counter
	uint8_t       m_dr;             // data register
	uint8_t       m_ir;             // instruction register
	uint8_t       m_active_ram;     // DDRAM or CGRAM
>>>>>>> upstream/master
	bool        m_display_on;     // display on/off
	bool        m_cursor_on;      // cursor on/off
	bool        m_blink_on;       // blink on/off
	bool        m_shift_on;       // shift on/off
	int         m_disp_shift;     // display shift
	int         m_direction;      // auto increment/decrement (-1 or +1)
<<<<<<< HEAD
	UINT8       m_data_len;       // interface data length 4 or 8 bit
	UINT8       m_num_line;       // number of lines
	UINT8       m_char_size;      // char size 5x8 or 5x10
=======
	uint8_t       m_data_len;       // interface data length 4 or 8 bit
	uint8_t       m_num_line;       // number of lines
	uint8_t       m_char_size;      // char size 5x8 or 5x10
>>>>>>> upstream/master
	bool        m_blink;
	bool        m_first_cmd;
	int         m_rs_state;
	int         m_rw_state;
	bool        m_nibble;
	int         m_charset_type;
<<<<<<< HEAD
	UINT8       m_render_buf[80 * 16];
=======
	uint8_t       m_render_buf[80 * 16];
>>>>>>> upstream/master

	enum        { DDRAM, CGRAM };
};

// ======================> ks0066_f05_device

class ks0066_f05_device :  public hd44780_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	ks0066_f05_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

// device type definition
extern const device_type HD44780;
extern const device_type KS0066_F05;

#endif
=======
	ks0066_f05_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

// device type definition
DECLARE_DEVICE_TYPE(HD44780,    hd44780_device)
DECLARE_DEVICE_TYPE(KS0066_F05, ks0066_f05_device)

#endif // MAME_VIDEO_HD44780_H
>>>>>>> upstream/master
