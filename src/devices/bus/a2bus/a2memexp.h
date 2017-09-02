// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    a2memexp.h

    Implementation of the Apple II Memory Expansion Card

*********************************************************************/

<<<<<<< HEAD
#ifndef __A2BUS_MEMEXP__
#define __A2BUS_MEMEXP__

#include "emu.h"
=======
#ifndef MAME_BUS_A2BUS_A2MEMEXP_H
#define MAME_BUS_A2BUS_A2MEMEXP_H

#pragma once

>>>>>>> upstream/master
#include "a2bus.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class a2bus_memexp_device:
	public device_t,
	public device_a2bus_card_interface
{
public:
<<<<<<< HEAD
	// construction/destruction
	a2bus_memexp_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;

	bool m_isramfactor;
	UINT8 m_bankhior;
	int m_addrmask;

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
	UINT8 m_regs[0x10];
	UINT8 m_ram[8*1024*1024];
=======
	bool m_isramfactor;
	uint8_t m_bankhior;
	int m_addrmask;

protected:
	// construction/destruction
	a2bus_memexp_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

	// overrides of standard a2bus slot functions
	virtual uint8_t read_c0nx(address_space &space, uint8_t offset) override;
	virtual void write_c0nx(address_space &space, uint8_t offset, uint8_t data) override;
	virtual uint8_t read_cnxx(address_space &space, uint8_t offset) override;
	virtual uint8_t read_c800(address_space &space, uint16_t offset) override;

private:
	uint8_t *m_rom;
	uint8_t m_regs[0x10];
	uint8_t m_ram[8*1024*1024];
>>>>>>> upstream/master
	int m_wptr, m_liveptr;
};

class a2bus_memexpapple_device : public a2bus_memexp_device
{
public:
<<<<<<< HEAD
	a2bus_memexpapple_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	a2bus_memexpapple_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class a2bus_ramfactor_device : public a2bus_memexp_device
{
public:
<<<<<<< HEAD
	a2bus_ramfactor_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual const rom_entry *device_rom_region() const;
};

// device type definition
extern const device_type A2BUS_MEMEXP;
extern const device_type A2BUS_RAMFACTOR;

#endif /* __A2BUS_MEMEXP__ */
=======
	a2bus_ramfactor_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual const tiny_rom_entry *device_rom_region() const override;
};

// device type definition
DECLARE_DEVICE_TYPE(A2BUS_MEMEXP,    a2bus_memexpapple_device)
DECLARE_DEVICE_TYPE(A2BUS_RAMFACTOR, a2bus_ramfactor_device)

#endif // MAME_BUS_A2BUS_A2MEMEXP_H
>>>>>>> upstream/master
