// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_CART_YAMAHA_H
#define __MSX_CART_YAMAHA_H

#include "bus/msx_cart/cartridge.h"
#include "sound/2151intf.h"
=======
#ifndef MAME_BUS_MSX_CART_YAMAHA_H
#define MAME_BUS_MSX_CART_YAMAHA_H

#pragma once

#include "bus/msx_cart/cartridge.h"
#include "sound/ym2151.h"
>>>>>>> upstream/master
#include "bus/msx_cart/msx_audio_kb.h"
#include "machine/ym2148.h"


<<<<<<< HEAD
extern const device_type MSX_CART_SFG01;
extern const device_type MSX_CART_SFG05;


class msx_cart_sfg : public device_t
					, public msx_cart_interface
{
public:
	msx_cart_sfg(const machine_config &mconfig, const device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname);

	// device-level overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_start();

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);

	DECLARE_WRITE_LINE_MEMBER(ym2151_irq_w);
	DECLARE_WRITE_LINE_MEMBER(ym2148_irq_w);

	IRQ_CALLBACK_MEMBER(irq_callback);

private:
=======
DECLARE_DEVICE_TYPE(MSX_CART_SFG01, msx_cart_sfg01_device)
DECLARE_DEVICE_TYPE(MSX_CART_SFG05, msx_cart_sfg05_device)


class msx_cart_sfg_device : public device_t, public msx_cart_interface
{
public:
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
protected:
	msx_cart_sfg_device(const machine_config &mconfig, const device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;

	// device-level overrides
	virtual void device_add_mconfig(machine_config &config) override;

	IRQ_CALLBACK_MEMBER(irq_callback);

private:
	DECLARE_WRITE_LINE_MEMBER(ym2151_irq_w);
	DECLARE_WRITE_LINE_MEMBER(ym2148_irq_w);

>>>>>>> upstream/master
	required_memory_region m_region_sfg;
	required_device<ym2151_device> m_ym2151;
	required_device<msx_audio_kbdc_port_device> m_kbdc;
	required_device<ym2148_device> m_ym2148;
	int m_ym2151_irq_state;
	int m_ym2148_irq_state;
<<<<<<< HEAD
	UINT32 m_rom_mask;
=======
	uint32_t m_rom_mask;
>>>>>>> upstream/master

	void check_irq();
};


<<<<<<< HEAD
class msx_cart_sfg01 : public msx_cart_sfg
{
public:
	msx_cart_sfg01(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual const rom_entry *device_rom_region() const;
};


class msx_cart_sfg05 : public msx_cart_sfg
{
public:
	msx_cart_sfg05(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual const rom_entry *device_rom_region() const;
};

#endif
=======
class msx_cart_sfg01_device : public msx_cart_sfg_device
{
public:
	msx_cart_sfg01_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual const tiny_rom_entry *device_rom_region() const override;
};


class msx_cart_sfg05_device : public msx_cart_sfg_device
{
public:
	msx_cart_sfg05_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual const tiny_rom_entry *device_rom_region() const override;
};

#endif // MAME_BUS_MSX_CART_YAMAHA_H
>>>>>>> upstream/master
