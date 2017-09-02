// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_CART_NOMAPPER_H
#define __MSX_CART_NOMAPPER_H
=======
#ifndef MAME_BUS_MSX_CART_NOMAPPER_H
#define MAME_BUS_MSX_CART_NOMAPPER_H

#pragma once
>>>>>>> upstream/master

#include "bus/msx_cart/cartridge.h"


<<<<<<< HEAD
extern const device_type MSX_CART_NOMAPPER;


class msx_cart_nomapper : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_nomapper(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);

private:
	UINT32 m_start_address;
	UINT32 m_end_address;
};

#endif
=======
DECLARE_DEVICE_TYPE(MSX_CART_NOMAPPER, msx_cart_nomapper_device)


class msx_cart_nomapper_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_nomapper_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;

private:
	uint32_t m_start_address;
	uint32_t m_end_address;
};

#endif // MAME_BUS_MSX_CART_NOMAPPER_H
>>>>>>> upstream/master
