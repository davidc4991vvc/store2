// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
<<<<<<< HEAD
#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include "machine/keyboard.h"

#define TERMINAL_SCREEN_TAG "terminal_screen"

=======
#ifndef MAME_MACHINE_TERMINAL_H
#define MAME_MACHINE_TERMINAL_H

#pragma once

#include "machine/keyboard.h"
#include "sound/beep.h"


#define TERMINAL_SCREEN_TAG "terminal_screen"


>>>>>>> upstream/master
/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

<<<<<<< HEAD
#define MCFG_GENERIC_TERMINAL_KEYBOARD_CB(_devcb) \
	devcb = &generic_terminal_device::set_keyboard_callback(*device, DEVCB_##_devcb);
=======
#define MCFG_GENERIC_TERMINAL_KEYBOARD_CB(cb) \
		generic_terminal_device::set_keyboard_callback(*device, (KEYBOARDCB_##cb));

>>>>>>> upstream/master

/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

<<<<<<< HEAD
#define TERMINAL_WIDTH 80
#define TERMINAL_HEIGHT 24

=======
>>>>>>> upstream/master
INPUT_PORTS_EXTERN( generic_terminal );

class generic_terminal_device : public device_t
{
public:
<<<<<<< HEAD
	generic_terminal_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	generic_terminal_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	template<class _Object> static devcb_base &set_keyboard_callback(device_t &device, _Object object) { return downcast<generic_terminal_device &>(device).m_keyboard_cb.set_callback(object); }

	DECLARE_WRITE8_MEMBER(write) { term_write(data); }
	DECLARE_WRITE8_MEMBER(kbd_put);
	UINT32 update(screen_device &device, bitmap_rgb32 &bitmap, const rectangle &cliprect);

	virtual ioport_constructor device_input_ports() const;
	virtual machine_config_constructor device_mconfig_additions() const;
protected:
	optional_device<palette_device> m_palette;
	required_ioport m_io_term_conf;

	virtual void term_write(UINT8 data);
	virtual void device_start();
	virtual void device_reset();
	virtual void send_key(UINT8 code) { m_keyboard_cb((offs_t)0, code); }
	UINT8 m_buffer[TERMINAL_WIDTH*50]; // make big enough for teleprinter
	UINT8 m_x_pos;
private:
	void scroll_line();
	void write_char(UINT8 data);
	void clear();

	UINT8 m_framecnt;
	UINT8 m_y_pos;

	devcb_write8 m_keyboard_cb;
};

extern const device_type GENERIC_TERMINAL;

#endif /* __TERMINAL_H__ */
=======
	generic_terminal_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static void set_keyboard_callback(device_t &device, Object &&cb)
	{ downcast<generic_terminal_device &>(device).m_keyboard_cb = std::forward<Object>(cb); }

	DECLARE_WRITE8_MEMBER(write) { term_write(data); }

	void kbd_put(u8 data);

protected:
	enum { BELL_TIMER_ID = 20'000 };

	generic_terminal_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, unsigned w, unsigned h);

	virtual void term_write(uint8_t data);
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	virtual ioport_constructor device_input_ports() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual void send_key(uint8_t code) { if (!m_keyboard_cb.isnull()) m_keyboard_cb(code); }

	optional_device<palette_device> m_palette;
	required_ioport m_io_term_conf;

	static constexpr unsigned TERMINAL_WIDTH = 80;
	static constexpr unsigned TERMINAL_HEIGHT = 24;

	unsigned const m_width;
	unsigned const m_height;
	std::unique_ptr<uint8_t []> m_buffer;
	uint8_t m_x_pos;

private:
	void scroll_line();
	void write_char(uint8_t data);
	void clear();
	uint32_t update(screen_device &device, bitmap_rgb32 &bitmap, const rectangle &cliprect);

	uint8_t m_framecnt;
	uint8_t m_y_pos;

	emu_timer *m_bell_timer;
	required_device<beep_device> m_beeper;
	generic_keyboard_device::output_delegate m_keyboard_cb;
};

DECLARE_DEVICE_TYPE(GENERIC_TERMINAL, generic_terminal_device)

#endif // MAME_DEVICES_TERMINAL_H
>>>>>>> upstream/master
