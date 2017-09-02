// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#ifndef __RS232_TERMINAL_H__
#define __RS232_TERMINAL_H__
=======
#ifndef MAME_BUS_RS232_TERMINAL_H
#define MAME_BUS_RS232_TERMINAL_H
>>>>>>> upstream/master

#include "rs232.h"
#include "machine/terminal.h"


class serial_terminal_device : public generic_terminal_device,
<<<<<<< HEAD
	public device_serial_interface,
	public device_rs232_port_interface
{
public:
	serial_terminal_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_WRITE_LINE_MEMBER( input_txd ) { device_serial_interface::rx_w(state); }
=======
	public device_buffered_serial_interface<16U>,
	public device_rs232_port_interface
{
public:
	serial_terminal_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE_LINE_MEMBER( input_txd ) override { device_buffered_serial_interface::rx_w(state); }
>>>>>>> upstream/master

	DECLARE_WRITE_LINE_MEMBER(update_serial);

protected:
<<<<<<< HEAD
	virtual ioport_constructor device_input_ports() const;
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	virtual void tra_callback();
	virtual void tra_complete();
	virtual void rcv_complete();
	virtual void send_key(UINT8 code);

private:
=======
	virtual ioport_constructor device_input_ports() const override;
	virtual void device_reset() override;

	virtual void tra_callback() override;
	virtual void send_key(uint8_t code) override;

private:
	virtual void received_byte(uint8_t byte) override;

>>>>>>> upstream/master
	required_ioport m_rs232_txbaud;
	required_ioport m_rs232_rxbaud;
	required_ioport m_rs232_startbits;
	required_ioport m_rs232_databits;
	required_ioport m_rs232_parity;
	required_ioport m_rs232_stopbits;
<<<<<<< HEAD

	UINT8 m_curr_key;
	bool m_key_valid;
};

extern const device_type SERIAL_TERMINAL;

#endif /* __RS232_TERMINAL_H__ */
=======
};

DECLARE_DEVICE_TYPE(SERIAL_TERMINAL, serial_terminal_device)

#endif // MAME_BUS_RS232_TERMINAL_H
>>>>>>> upstream/master
