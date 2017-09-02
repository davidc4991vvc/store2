// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    a2cffa.h

    Implementation of Rich Dreher's IDE/CompactFlash board for
    the Apple II

*********************************************************************/

<<<<<<< HEAD
#ifndef __A2BUS_CFFA2__
#define __A2BUS_CFFA2__

#include "emu.h"
=======
#ifndef MAME_BUS_A2BUS_A2CFFA_H
#define MAME_BUS_A2BUS_A2CFFA_H

#pragma once

>>>>>>> upstream/master
#include "a2bus.h"
#include "machine/ataintf.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class a2bus_cffa2000_device:
	public device_t,
	public device_a2bus_card_interface
{
<<<<<<< HEAD
public:
	// construction/destruction
	a2bus_cffa2000_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;

protected:
	virtual void device_start();
	virtual void device_reset();

	// overrides of standard a2bus slot functions
	virtual UINT8 read_c0nx(address_space &space, UINT8 offset);
	virtual void write_c0nx(address_space &space, UINT8 offset, UINT8 data);
	virtual UINT8 read_cnxx(address_space &space, UINT8 offset);
	virtual UINT8 read_c800(address_space &space, UINT16 offset);
	virtual void write_c800(address_space &space, UINT16 offset, UINT8 data);

	required_device<ata_interface_device> m_ata;

	UINT8 *m_rom;
	UINT8 m_eeprom[0x1000];

private:
	UINT16 m_lastdata, m_lastreaddata;
=======
protected:
	// construction/destruction
	a2bus_cffa2000_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

	// overrides of standard a2bus slot functions
	virtual uint8_t read_c0nx(address_space &space, uint8_t offset) override;
	virtual void write_c0nx(address_space &space, uint8_t offset, uint8_t data) override;
	virtual uint8_t read_cnxx(address_space &space, uint8_t offset) override;
	virtual uint8_t read_c800(address_space &space, uint16_t offset) override;
	virtual void write_c800(address_space &space, uint16_t offset, uint8_t data) override;

	required_device<ata_interface_device> m_ata;

	uint8_t *m_rom;
	uint8_t m_eeprom[0x1000];

private:
	uint16_t m_lastdata, m_lastreaddata;
>>>>>>> upstream/master
	bool m_writeprotect;
	bool m_inwritecycle;
};

class a2bus_cffa2_device : public a2bus_cffa2000_device, public device_nvram_interface
{
public:
<<<<<<< HEAD
	a2bus_cffa2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device_config_nvram_interface overrides
	virtual void nvram_default();
	virtual void nvram_read(emu_file &file);
	virtual void nvram_write(emu_file &file);
=======
	a2bus_cffa2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device_config_nvram_interface overrides
	virtual void nvram_default() override;
	virtual void nvram_read(emu_file &file) override;
	virtual void nvram_write(emu_file &file) override;
>>>>>>> upstream/master
};

class a2bus_cffa2_6502_device : public a2bus_cffa2000_device, public device_nvram_interface
{
public:
<<<<<<< HEAD
	a2bus_cffa2_6502_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual const rom_entry *device_rom_region() const;

protected:
	// device_config_nvram_interface overrides
	virtual void nvram_default();
	virtual void nvram_read(emu_file &file);
	virtual void nvram_write(emu_file &file);
};

// device type definition
extern const device_type A2BUS_CFFA2;
extern const device_type A2BUS_CFFA2_6502;

#endif /* __A2BUS_CFFA2__ */
=======
	a2bus_cffa2_6502_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	// device_config_nvram_interface overrides
	virtual void nvram_default() override;
	virtual void nvram_read(emu_file &file) override;
	virtual void nvram_write(emu_file &file) override;
};

// device type definition
DECLARE_DEVICE_TYPE(A2BUS_CFFA2,      a2bus_cffa2_device)
DECLARE_DEVICE_TYPE(A2BUS_CFFA2_6502, a2bus_cffa2_6502_device)

#endif // MAME_BUS_A2BUS_A2CFFA_H
>>>>>>> upstream/master
