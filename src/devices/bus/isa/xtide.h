// license:BSD-3-Clause
// copyright-holders:Phill Harvey-Smith
<<<<<<< HEAD
#pragma once

#ifndef __XTIDE_H__
#define __XTIDE_H__

#include "emu.h"
#include "machine/ataintf.h"
#include "machine/eeprompar.h"
#include "isa.h"
=======
#ifndef MAME_BUS_ISA_XTIDE_H
#define MAME_BUS_ISA_XTIDE_H

#pragma once

#include "isa.h"
#include "machine/ataintf.h"
#include "machine/eeprompar.h"
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
class xtide_device : public device_t,
	public device_isa8_card_interface
{
public:
	// construction/destruction
	xtide_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;
	virtual const rom_entry *device_rom_region() const;

	DECLARE_READ8_MEMBER(read);
	DECLARE_WRITE8_MEMBER(write);
	DECLARE_WRITE_LINE_MEMBER(ide_interrupt);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_config_complete() { m_shortname = "xtide"; }

private:
	required_device<ata_interface_device> m_ata;
	required_device<eeprom_parallel_28xx_device> m_eeprom;

	UINT8 m_irq_number;
	UINT8 m_d8_d15_latch;
=======
class xtide_device : public device_t, public device_isa8_card_interface
{
public:
	// construction/destruction
	xtide_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ8_MEMBER(read);
	DECLARE_WRITE8_MEMBER(write);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;
	virtual const tiny_rom_entry *device_rom_region() const override;

private:
	DECLARE_WRITE_LINE_MEMBER(ide_interrupt);

	required_device<ata_interface_device> m_ata;
	required_device<eeprom_parallel_28xx_device> m_eeprom;

	uint8_t m_irq_number;
	uint8_t m_d8_d15_latch;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type ISA8_XTIDE;

#endif  /* __XTIDE__ */
=======
DECLARE_DEVICE_TYPE(ISA8_XTIDE, xtide_device)

#endif // MAME_BUS_ISA_XTIDE_H
>>>>>>> upstream/master
