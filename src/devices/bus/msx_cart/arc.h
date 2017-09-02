// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_CART_ARC_H
#define __MSX_CART_ARC_H
=======
#ifndef MAME_BUS_MSX_CART_ARC_H
#define MAME_BUS_MSX_CART_ARC_H

#pragma once
>>>>>>> upstream/master

#include "bus/msx_cart/cartridge.h"


<<<<<<< HEAD
extern const device_type MSX_CART_ARC;


class msx_cart_arc : public device_t
					, public msx_cart_interface
{
public:
	msx_cart_arc(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);
=======
DECLARE_DEVICE_TYPE(MSX_CART_ARC, msx_cart_arc_device)


class msx_cart_arc_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_arc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER(io_7f_w);
	DECLARE_READ8_MEMBER(io_7f_r);

<<<<<<< HEAD
private:
	UINT8 m_7f;
};


#endif
=======
protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t m_7f;
};

#endif // MAME_BUS_MSX_CART_ARC_H
>>>>>>> upstream/master
