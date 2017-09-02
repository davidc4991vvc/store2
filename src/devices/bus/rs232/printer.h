// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#ifndef __RS232_PRINTER_H__
#define __RS232_PRINTER_H__
=======
#ifndef MAME_BUS_RS232_PRINTER_H
#define MAME_BUS_RS232_PRINTER_H
>>>>>>> upstream/master

#pragma once

#include "rs232.h"
#include "imagedev/printer.h"

class serial_printer_device : public device_t,
	public device_serial_interface,
	public device_rs232_port_interface
{
public:
<<<<<<< HEAD
	serial_printer_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_WRITE_LINE_MEMBER( input_txd ) { device_serial_interface::rx_w(state); }

	DECLARE_WRITE_LINE_MEMBER(update_serial);
	DECLARE_WRITE_LINE_MEMBER(printer_online);

protected:
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	virtual void rcv_complete();

private:
=======
	serial_printer_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE_LINE_MEMBER( input_txd ) override { device_serial_interface::rx_w(state); }

	DECLARE_WRITE_LINE_MEMBER(update_serial);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual void rcv_complete() override;

private:
	DECLARE_WRITE_LINE_MEMBER(printer_online);

>>>>>>> upstream/master
	required_device<printer_image_device> m_printer;

	required_ioport m_rs232_rxbaud;
	required_ioport m_rs232_startbits;
	required_ioport m_rs232_databits;
	required_ioport m_rs232_parity;
	required_ioport m_rs232_stopbits;
};

<<<<<<< HEAD
extern const device_type SERIAL_PRINTER;

#endif
=======
DECLARE_DEVICE_TYPE(SERIAL_PRINTER, serial_printer_device)

#endif // MAME_BUS_RS232_PRINTER_H
>>>>>>> upstream/master
