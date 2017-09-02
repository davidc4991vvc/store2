// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/***************************************************************************

    h8_port.h

    H8 8 bits digital port


***************************************************************************/

<<<<<<< HEAD
#ifndef __H8_PORT_H__
#define __H8_PORT_H__
=======
#ifndef MAME_CPU_H8_H8_PORT_H
#define MAME_CPU_H8_H8_PORT_H

#pragma once
>>>>>>> upstream/master

#include "h8.h"

#define MCFG_H8_PORT_ADD( _tag, address, ddr, mask )    \
	MCFG_DEVICE_ADD( _tag, H8_PORT, 0 ) \
	downcast<h8_port_device *>(device)->set_info(address, ddr, mask);

class h8_port_device : public device_t {
public:
<<<<<<< HEAD
	h8_port_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	void set_info(int address, UINT8 default_ddr, UINT8 mask);
=======
	h8_port_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	void set_info(int address, uint8_t default_ddr, uint8_t mask);
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER(ddr_w);
	DECLARE_WRITE8_MEMBER(dr_w);
	DECLARE_READ8_MEMBER(dr_r);
	DECLARE_READ8_MEMBER(port_r);
	DECLARE_WRITE8_MEMBER(pcr_w);
	DECLARE_READ8_MEMBER(pcr_r);
	DECLARE_WRITE8_MEMBER(odr_w);
	DECLARE_READ8_MEMBER(odr_r);

protected:
	required_device<h8_device> cpu;
	address_space *io;

	int address;
<<<<<<< HEAD
	UINT8 default_ddr, ddr, pcr, odr;
	UINT8 mask;
	UINT8 dr;
	UINT8 last_output;

	virtual void device_start();
	virtual void device_reset();
	void update_output();
};

extern const device_type H8_PORT;

#endif
=======
	uint8_t default_ddr, ddr, pcr, odr;
	uint8_t mask;
	uint8_t dr;
	uint8_t last_output;

	virtual void device_start() override;
	virtual void device_reset() override;
	void update_output();
};

DECLARE_DEVICE_TYPE(H8_PORT, h8_port_device)

#endif // MAME_CPU_H8_H8_PORT_H
>>>>>>> upstream/master
