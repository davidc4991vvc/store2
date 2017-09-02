// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __SEGA8_MGEAR_H
#define __SEGA8_MGEAR_H
=======
#ifndef MAME_BUS_SEGA8_MGEAR_H
#define MAME_BUS_SEGA8_MGEAR_H

#pragma once
>>>>>>> upstream/master

#include "sega8_slot.h"
#include "rom.h"


// ======================> sega8_mgear_device

class sega8_mgear_device : public sega8_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_mgear_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) { return m_subslot->read_cart(space, offset); }
	virtual DECLARE_WRITE8_MEMBER(write_cart) { m_subslot->write_cart(space, offset, data); }
	virtual DECLARE_WRITE8_MEMBER(write_mapper) { m_subslot->write_mapper(space, offset, data); }
	virtual int get_lphaser_xoffs() { return m_subslot->m_cart ? m_subslot->m_cart->get_lphaser_xoffs() : -1; }

	virtual machine_config_constructor device_mconfig_additions() const;

protected:
=======
	sega8_mgear_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override { return m_subslot->read_cart(space, offset); }
	virtual DECLARE_WRITE8_MEMBER(write_cart) override { m_subslot->write_cart(space, offset, data); }
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override { m_subslot->write_mapper(space, offset, data); }
	virtual int get_lphaser_xoffs() override { return m_subslot->get_lphaser_xoffs(); }

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual void device_add_mconfig(machine_config &config) override;

>>>>>>> upstream/master
	required_device<sega8_cart_slot_device> m_subslot;
};


// device type definition
<<<<<<< HEAD
extern const device_type SEGA8_ROM_MGEAR;


#endif
=======
DECLARE_DEVICE_TYPE(SEGA8_ROM_MGEAR, sega8_mgear_device)

#endif // MAME_BUS_SEGA8_MGEAR_H
>>>>>>> upstream/master
