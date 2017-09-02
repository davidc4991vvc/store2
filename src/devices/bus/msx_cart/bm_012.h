// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_CART_BM_012_H
#define __MSX_CART_BM_012_H
=======
#ifndef MAME_BUS_MSX_CART_BM_012_H
#define MAME_BUS_MSX_CART_BM_012_H

#pragma once
>>>>>>> upstream/master

#include "bus/msx_cart/cartridge.h"
#include "cpu/z80/tmpz84c015.h"
#include "bus/midi/midi.h"


<<<<<<< HEAD
extern const device_type MSX_CART_BM_012;


class msx_cart_bm_012 : public device_t
					, public msx_cart_interface
{
public:
	msx_cart_bm_012(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;
	virtual void device_start();

	DECLARE_WRITE_LINE_MEMBER(midi_in);

private:
=======
DECLARE_DEVICE_TYPE(MSX_CART_BM_012, msx_cart_bm_012_device)


class msx_cart_bm_012_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_bm_012_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;

	// device-level overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

private:
	DECLARE_WRITE_LINE_MEMBER(midi_in);

>>>>>>> upstream/master
	required_device<tmpz84c015_device> m_tmpz84c015af;
	required_device<z80pio_device> m_bm012_pio;
	required_device<midi_port_device> m_mdthru;
};


<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_MSX_CART_BM_012_H
>>>>>>> upstream/master
