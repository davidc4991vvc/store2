// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_CART_FMPAC_H
#define __MSX_CART_FMPAC_H

#include "bus/msx_cart/cartridge.h"
#include "sound/2413intf.h"


extern const device_type MSX_CART_FMPAC;


class msx_cart_fmpac : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_fmpac(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual machine_config_constructor device_mconfig_additions() const;

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);

	void restore_banks();

	DECLARE_WRITE8_MEMBER(write_ym2413);
=======
#ifndef MAME_BUS_MSX_CART_FMPAC_H
#define MAME_BUS_MSX_CART_FMPAC_H

#pragma once

#include "bus/msx_cart/cartridge.h"
#include "sound/ym2413.h"


DECLARE_DEVICE_TYPE(MSX_CART_FMPAC, msx_cart_fmpac_device)


class msx_cart_fmpac_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_fmpac_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

	DECLARE_WRITE8_MEMBER(write_ym2413);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;

	// device-level overrides
	virtual void device_add_mconfig(machine_config &config) override;

	void restore_banks();
>>>>>>> upstream/master

private:
	required_device<ym2413_device> m_ym2413;

<<<<<<< HEAD
	UINT8 m_selected_bank;
	UINT8 *m_bank_base;
	bool m_sram_active;
	bool m_opll_active;
	UINT8 m_1ffe;
	UINT8 m_1fff;
	UINT8 m_7ff6;
};


#endif
=======
	uint8_t m_selected_bank;
	uint8_t *m_bank_base;
	bool m_sram_active;
	bool m_opll_active;
	uint8_t m_1ffe;
	uint8_t m_1fff;
	uint8_t m_7ff6;
};


#endif // MAME_BUS_MSX_CART_FMPAC_H
>>>>>>> upstream/master
