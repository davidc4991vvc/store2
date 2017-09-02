// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_SLOT_ROM_H
#define __MSX_SLOT_ROM_H
=======
#ifndef MAME_BUS_MSX_SLOT_ROM_H
#define MAME_BUS_MSX_SLOT_ROM_H

#pragma once
>>>>>>> upstream/master

#include "slot.h"

#define MCFG_MSX_SLOT_ROM_ADD(_tag, _startpage, _numpages, _region, _offset) \
	MCFG_MSX_INTERNAL_SLOT_ADD(_tag, MSX_SLOT_ROM, _startpage, _numpages) \
<<<<<<< HEAD
	msx_slot_rom_device::set_rom_start(*device, _region, _offset);
=======
	msx_slot_rom_device::set_rom_start(*device, "^" _region, _offset);
>>>>>>> upstream/master

class msx_slot_rom_device : public device_t,
							public msx_internal_slot_interface
{
public:
<<<<<<< HEAD
	msx_slot_rom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	msx_slot_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration helpers
	static void set_rom_start(device_t &device, const char *region, UINT32 offset);

	virtual void device_start();

	virtual DECLARE_READ8_MEMBER(read);

private:
	const char *m_region;
	UINT32 m_region_offset;
	const UINT8 *m_rom;
=======
	msx_slot_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration helpers
	static void set_rom_start(device_t &device, const char *region, uint32_t offset);

	virtual DECLARE_READ8_MEMBER(read) override;

protected:
	msx_slot_rom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;

private:
	required_memory_region m_rom_region;
	uint32_t m_region_offset;
	const uint8_t *m_rom;
>>>>>>> upstream/master
};

extern const device_type MSX_SLOT_ROM;

<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_MSX_SLOT_ROM_H
>>>>>>> upstream/master
