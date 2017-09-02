// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_CART_MAJUTSUSHI_H
#define __MSX_CART_MAJUTSUSHI_H
=======
#ifndef MAME_BUS_MSX_CART_MAJUTSUSHI_H
#define MAME_BUS_MSX_CART_MAJUTSUSHI_H

#pragma once
>>>>>>> upstream/master

#include "bus/msx_cart/cartridge.h"
#include "sound/dac.h"


<<<<<<< HEAD
extern const device_type MSX_CART_MAJUTSUSHI;


class msx_cart_majutsushi : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_majutsushi(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual machine_config_constructor device_mconfig_additions() const;

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
=======
DECLARE_DEVICE_TYPE(MSX_CART_MAJUTSUSHI, msx_cart_majutsushi_device)


class msx_cart_majutsushi_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_majutsushi_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

	void restore_banks();

private:
<<<<<<< HEAD
	required_device<dac_device> m_dac;

	UINT8 m_selected_bank[4];
	UINT8 *m_bank_base[8];
};


#endif
=======
	required_device<dac_byte_interface> m_dac;

	uint8_t m_selected_bank[4];
	uint8_t *m_bank_base[8];
};


#endif // MAME_BUS_MSX_CART_MAJUTSUSHI_H
>>>>>>> upstream/master
