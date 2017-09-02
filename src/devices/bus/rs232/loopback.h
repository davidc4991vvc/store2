// license:BSD-3-Clause
// copyright-holders:smf

<<<<<<< HEAD
#ifndef RS232_LOOPBACK_H_
#define RS232_LOOPBACK_H_
=======
#ifndef MAME_BUS_RS232_LOOPBACK_H
#define MAME_BUS_RS232_LOOPBACK_H

#pragma once
>>>>>>> upstream/master

#include "rs232.h"

class rs232_loopback_device : public device_t,
	public device_rs232_port_interface
{
public:
<<<<<<< HEAD
	rs232_loopback_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual WRITE_LINE_MEMBER( input_txd );
	virtual WRITE_LINE_MEMBER( input_rts );
	virtual WRITE_LINE_MEMBER( input_dtr );

protected:
	virtual void device_start();
=======
	rs232_loopback_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual WRITE_LINE_MEMBER( input_txd ) override;
	virtual WRITE_LINE_MEMBER( input_rts ) override;
	virtual WRITE_LINE_MEMBER( input_dtr ) override;

protected:
	virtual void device_start() override;
>>>>>>> upstream/master
};

extern const device_type RS232_LOOPBACK;

<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_RS232_LOOPBACK_H
>>>>>>> upstream/master
