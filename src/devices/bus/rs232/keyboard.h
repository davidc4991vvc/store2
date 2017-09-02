// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#ifndef __RS232_KEYBOARD_H__
#define __RS232_KEYBOARD_H__
=======
#ifndef MAME_BUS_RS232_KEYBOARD_H
#define MAME_BUS_RS232_KEYBOARD_H

#pragma once
>>>>>>> upstream/master

#pragma once

#include "rs232.h"
#include "machine/keyboard.h"

<<<<<<< HEAD
class serial_keyboard_device :
	public generic_keyboard_device,
	public device_serial_interface,
	public device_rs232_port_interface
{
public:
	serial_keyboard_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	serial_keyboard_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	virtual DECLARE_WRITE_LINE_MEMBER( input_txd ) { device_serial_interface::rx_w(state); }
	DECLARE_READ_LINE_MEMBER(tx_r);

	virtual ioport_constructor device_input_ports() const;
=======
class serial_keyboard_device
	: public generic_keyboard_device
	, public device_buffered_serial_interface<16U>
	, public device_rs232_port_interface
{
public:
	serial_keyboard_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual ioport_constructor device_input_ports() const override;

	virtual DECLARE_WRITE_LINE_MEMBER( input_txd ) override;
>>>>>>> upstream/master

	DECLARE_WRITE_LINE_MEMBER(update_serial);

protected:
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual void tra_callback();
	virtual void tra_complete();
	virtual void send_key(UINT8 code);

private:
	UINT8 m_curr_key;
	bool m_key_valid;
=======
	serial_keyboard_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_reset() override;
	virtual void tra_callback() override;
	virtual void send_key(uint8_t code) override;

private:
	virtual void received_byte(uint8_t byte) override;
>>>>>>> upstream/master

	required_ioport m_rs232_txbaud;
	required_ioport m_rs232_startbits;
	required_ioport m_rs232_databits;
	required_ioport m_rs232_parity;
	required_ioport m_rs232_stopbits;
};

<<<<<<< HEAD
extern const device_type SERIAL_KEYBOARD;

#endif /* __RS232_KEYBOARD_H__ */
=======
DECLARE_DEVICE_TYPE(SERIAL_KEYBOARD, serial_keyboard_device)

#endif // MAME_BUS_RS232_KEYBOARD_H
>>>>>>> upstream/master
