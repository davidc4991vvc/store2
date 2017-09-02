// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    a2corvus.h

    Implementation of the Corvus flat-cable hard disk interface
    for the Apple II.

*********************************************************************/

<<<<<<< HEAD
#ifndef __A2BUS_CORVUS__
#define __A2BUS_CORVUS__

#include "emu.h"
=======
#ifndef MAME_A2BUS_A2CORVUS_H
#define MAME_A2BUS_A2CORVUS_H

#pragma once

>>>>>>> upstream/master
#include "a2bus.h"
#include "machine/corvushd.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class a2bus_corvus_device:
	public device_t,
	public device_a2bus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	a2bus_corvus_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	a2bus_corvus_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;

	required_device<corvus_hdc_t> m_corvushd;

protected:
	virtual void device_start();
	virtual void device_reset();

	// overrides of standard a2bus slot functions
	virtual UINT8 read_c0nx(address_space &space, UINT8 offset);
	virtual void write_c0nx(address_space &space, UINT8 offset, UINT8 data);
	virtual UINT8 read_cnxx(address_space &space, UINT8 offset);
	virtual UINT8 read_c800(address_space &space, UINT16 offset);

private:
	UINT8 *m_rom;
};

// device type definition
extern const device_type A2BUS_CORVUS;

#endif /* __A2BUS_CORVUS__ */
=======
	a2bus_corvus_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	a2bus_corvus_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

	// overrides of standard a2bus slot functions
	virtual uint8_t read_c0nx(address_space &space, uint8_t offset) override;
	virtual void write_c0nx(address_space &space, uint8_t offset, uint8_t data) override;
	virtual uint8_t read_cnxx(address_space &space, uint8_t offset) override;
	virtual uint8_t read_c800(address_space &space, uint16_t offset) override;

	required_device<corvus_hdc_device> m_corvushd;

private:
	uint8_t *m_rom;
};

// device type definition
DECLARE_DEVICE_TYPE(A2BUS_CORVUS, a2bus_corvus_device)

#endif // MAME_A2BUS_A2CORVUS_H
>>>>>>> upstream/master
