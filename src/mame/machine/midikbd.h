// license:BSD-3-Clause
// copyright-holders:Carl
<<<<<<< HEAD
#ifndef MIDIKBD_H_
#define MIDIKBD_H_

#include "emu.h"
=======
#ifndef MAME_MACHINE_MIDIKBD_H
#define MAME_MACHINE_MIDIKBD_H

#pragma once

>>>>>>> upstream/master

#define MCFG_MIDI_KBD_ADD(_tag, _devcb, _clock) \
	MCFG_DEVICE_ADD(_tag, MIDI_KBD, _clock) \
	devcb = &midi_keyboard_device::static_set_tx_callback(*device, DEVCB_##_devcb);

<<<<<<< HEAD
class midi_keyboard_device : public device_t,
								public device_serial_interface
{
public:
	midi_keyboard_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	ioport_constructor device_input_ports() const;

	template<class _Object> static devcb_base &static_set_tx_callback(device_t &device, _Object object) { return downcast<midi_keyboard_device &>(device).m_out_tx_func.set_callback(object); }

protected:
	void device_start();
	void tra_callback();
	void tra_complete();
	void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

private:
	void push_tx(UINT8 data) { ++m_head %= 16; m_buffer[m_head] = data; }
=======
class midi_keyboard_device : public device_t, public device_serial_interface
{
public:
	midi_keyboard_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	ioport_constructor device_input_ports() const override;

	template <class Object> static devcb_base &static_set_tx_callback(device_t &device, Object &&cb) { return downcast<midi_keyboard_device &>(device).m_out_tx_func.set_callback(std::forward<Object>(cb)); }

protected:
	void device_start() override;
	void tra_callback() override;
	void tra_complete() override;
	void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

private:
	void push_tx(uint8_t data) { ++m_head %= 16; m_buffer[m_head] = data; }
>>>>>>> upstream/master

	devcb_write_line m_out_tx_func;
	emu_timer *m_keyboard_timer;
	required_ioport m_keyboard;
<<<<<<< HEAD
	UINT32 m_keyboard_state;
	UINT8 m_buffer[16];
	UINT8 m_head, m_tail;
};

extern const device_type MIDI_KBD;

#endif /* MIDIKBD_H_ */
=======
	uint32_t m_keyboard_state;
	uint8_t m_buffer[16];
	uint8_t m_head, m_tail;
};

DECLARE_DEVICE_TYPE(MIDI_KBD, midi_keyboard_device)

#endif // MAME_MACHINE_MIDIKBD_H
>>>>>>> upstream/master
