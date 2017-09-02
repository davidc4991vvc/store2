// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    a1cffa.h

    Rich Dreher's Compact Flash for Apple I

*********************************************************************/

<<<<<<< HEAD
#ifndef __A1BUS_CFFA__
#define __A1BUS_CFFA__

#include "emu.h"
=======
#ifndef MAME_BUS_A1BUS_A1CFFA_H
#define MAME_BUS_A1BUS_A1CFFA_H

#pragma once

>>>>>>> upstream/master
#include "a1bus.h"
#include "machine/ataintf.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class a1bus_cffa_device:
	public device_t,
	public device_a1bus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	a1bus_cffa_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	a1bus_cffa_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;

	required_device<ata_interface_device> m_ata;
=======
	a1bus_cffa_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(cffa_r);
	DECLARE_WRITE8_MEMBER(cffa_w);

protected:
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

private:
	UINT8 *m_rom;
	UINT16 m_lastdata;
=======
	a1bus_cffa_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;
	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

	required_device<ata_interface_device> m_ata;

private:
	uint8_t *m_rom;
	uint16_t m_lastdata;
>>>>>>> upstream/master
	bool m_writeprotect;
};

// device type definition
extern const device_type A1BUS_CFFA;

<<<<<<< HEAD
#endif  /* __A1BUS_CFFA__ */
=======
#endif  // MAME_BUS_A1BUS_A1CFFA_H
>>>>>>> upstream/master
