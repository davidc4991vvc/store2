// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_CART_SUPERLODERUNNER_H
#define __MSX_CART_SUPERLODERUNNER_H
=======
#ifndef MAME_BUS_MSX_CART_SUPERLODERUNNER_H
#define MAME_BUS_MSX_CART_SUPERLODERUNNER_H

#pragma once
>>>>>>> upstream/master

#include "bus/msx_cart/cartridge.h"


<<<<<<< HEAD
extern const device_type MSX_CART_SUPERLODERUNNER;


class msx_cart_superloderunner : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_superloderunner(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);

	DECLARE_WRITE8_MEMBER(banking);

	void restore_banks();

private:
	UINT8 m_selected_bank;
	UINT8 *m_bank_base;
};


#endif
=======
DECLARE_DEVICE_TYPE(MSX_CART_SUPERLODERUNNER, msx_cart_superloderunner_device)


class msx_cart_superloderunner_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_superloderunner_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;

	DECLARE_WRITE8_MEMBER(banking);

protected:
	// device-level overrides
	virtual void device_start() override;

	void restore_banks();

private:
	uint8_t m_selected_bank;
	uint8_t *m_bank_base;
};


#endif // MAME_BUS_MSX_CART_SUPERLODERUNNER_H
>>>>>>> upstream/master
