// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:smf
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "emu.h"
=======
// copyright-holders:Vas Crabb
#ifndef MAME_MACHINE_KEYBOARD_H
#define MAME_MACHINE_KEYBOARD_H

#pragma once

>>>>>>> upstream/master

/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

<<<<<<< HEAD
#define MCFG_GENERIC_KEYBOARD_CB(_devcb) \
	devcb = &generic_keyboard_device::set_keyboard_callback(*device, DEVCB_##_devcb);

/***************************************************************************
    FUNCTION PROTOTYPES
=======
#define KEYBOARDCB_PUT(cls, fnc)          generic_keyboard_device::output_delegate((&cls::fnc), (#cls "::" #fnc), DEVICE_SELF, ((cls *)nullptr))
#define KEYBOARDCB_DEVPUT(tag, cls, fnc)  generic_keyboard_device::output_delegate((&cls::fnc), (#cls "::" #fnc), (tag), ((cls *)nullptr))

#define MCFG_GENERIC_KEYBOARD_CB(cb) \
		generic_keyboard_device::set_keyboard_callback(*device, (KEYBOARDCB_##cb));



/***************************************************************************
    DEVICE TYPE GLOBALS
***************************************************************************/

DECLARE_DEVICE_TYPE(GENERIC_KEYBOARD, generic_keyboard_device)



/***************************************************************************
    REUSABLE I/O PORTS
>>>>>>> upstream/master
***************************************************************************/

INPUT_PORTS_EXTERN( generic_keyboard );

<<<<<<< HEAD
class generic_keyboard_device : public device_t
{
public:
	generic_keyboard_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	generic_keyboard_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	template<class _Object> static devcb_base &set_keyboard_callback(device_t &device, _Object object) { return downcast<generic_keyboard_device &>(device).m_keyboard_cb.set_callback(object); }

	virtual ioport_constructor device_input_ports() const;
	virtual machine_config_constructor device_mconfig_additions() const;
protected:
	required_ioport m_io_kbd0;
	required_ioport m_io_kbd1;
	required_ioport m_io_kbd2;
	required_ioport m_io_kbd3;
	required_ioport m_io_kbd4;
	required_ioport m_io_kbd5;
	required_ioport m_io_kbd6;
	required_ioport m_io_kbd7;
	required_ioport m_io_kbd8;
	required_ioport m_io_kbd9;
	required_ioport m_io_kbdc;

	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual void send_key(UINT8 code) { m_keyboard_cb((offs_t)0, code); }
	emu_timer *m_timer;
private:
	virtual UINT8 keyboard_handler(UINT8 last_code, UINT8 *scan_line);
	UINT8 row_number(UINT8 code);
	UINT8 m_last_code;
	UINT8 m_scan_line;

	devcb_write8 m_keyboard_cb;
};

extern const device_type GENERIC_KEYBOARD;

#endif /* __KEYBOARD_H__ */
=======


/***************************************************************************
    TYPE DECLARATIONS
***************************************************************************/

template <uint8_t ROW_COUNT>
class device_matrix_keyboard_interface : public device_interface
{
protected:
	template <typename... T>
	device_matrix_keyboard_interface(machine_config const &mconfig, device_t &device, T &&... tags);

	virtual void interface_pre_start() override;
	virtual void interface_post_start() override;

	void start_processing(const attotime &period);
	void stop_processing();
	void reset_key_state();

	void typematic_start(u8 row, u8 column, attotime const &delay, attotime const &interval);
	void typematic_restart(attotime const &delay, attotime const &interval);
	void typematic_stop();
	bool typematic_is(u8 row, u8 column) const { return (m_typematic_row == row) && (m_typematic_column == column); }

	virtual void key_make(u8 row, u8 column) = 0;
	virtual void key_repeat(u8 row, u8 column);
	virtual void key_break(u8 row, u8 column);
	virtual void will_scan_row(u8 row);

	bool are_all_keys_up();

private:
	TIMER_CALLBACK_MEMBER(scan_row);
	TIMER_CALLBACK_MEMBER(typematic);

	emu_timer       *m_scan_timer;
	emu_timer       *m_typematic_timer;
	required_ioport m_key_rows[ROW_COUNT];
	ioport_value    m_key_states[ROW_COUNT];
	u8              m_next_row;
	u8              m_processing;
	u8              m_typematic_row;
	u8              m_typematic_column;
};


class generic_keyboard_device : public device_t, protected device_matrix_keyboard_interface<4U>
{
public:
	typedef device_delegate<void (u8 character)> output_delegate;

	generic_keyboard_device(
			const machine_config &mconfig,
			const char *tag,
			device_t *owner,
			u32 clock);

	template <class Object> static void set_keyboard_callback(device_t &device, Object &&cb) { downcast<generic_keyboard_device &>(device).m_keyboard_cb = std::forward<Object>(cb); }

	virtual ioport_constructor device_input_ports() const override;

protected:
	generic_keyboard_device(
			const machine_config &mconfig,
			device_type type,
			char const *tag,
			device_t *owner,
			u32 clock);
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void key_make(u8 row, u8 column) override;
	virtual void key_repeat(u8 row, u8 column) override;
	virtual void send_key(u8 code);
	virtual bool translate(u8 code, u8 &translated) const;

	required_ioport m_config;
	required_ioport m_modifiers;

private:
	virtual void will_scan_row(u8 row) override;

	void typematic();
	void send_translated(u8 code);
	attotime typematic_delay() const;
	attotime typematic_period() const;

	u16             m_last_modifiers;
	output_delegate m_keyboard_cb;
};

#endif // MAME_MACHINE_KEYBOARD_H
>>>>>>> upstream/master
