// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_CART_SUPER_SWANGI_H
#define __MSX_CART_SUPER_SWANGI_H
=======
#ifndef MAME_BUS_MSX_CART_SUPER_SWANGI_H
#define MAME_BUS_MSX_CART_SUPER_SWANGI_H

#pragma once
>>>>>>> upstream/master

#include "bus/msx_cart/cartridge.h"


<<<<<<< HEAD
extern const device_type MSX_CART_SUPER_SWANGI;


class msx_cart_super_swangi : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_super_swangi(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
=======
DECLARE_DEVICE_TYPE(MSX_CART_SUPER_SWANGI, msx_cart_super_swangi_device)


class msx_cart_super_swangi_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_super_swangi_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

	void restore_banks();

private:
<<<<<<< HEAD
	UINT8 m_selected_bank;
	UINT8 *m_bank_base[2];
};


#endif
=======
	uint8_t m_selected_bank;
	uint8_t *m_bank_base[2];
};


#endif // MAME_BUS_MSX_CART_SUPER_SWANGI_H
>>>>>>> upstream/master
