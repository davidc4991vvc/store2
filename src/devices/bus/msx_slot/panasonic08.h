// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_SLOT_PANASONIC08_H
#define __MSX_SLOT_PANASONIC08_H
=======
#ifndef MAME_BUS_MSX_SLOT_PANASONIC08_H
#define MAME_BUS_MSX_SLOT_PANASONIC08_H

#pragma once
>>>>>>> upstream/master

#include "slot.h"
#include "machine/nvram.h"


<<<<<<< HEAD
extern const device_type MSX_SLOT_PANASONIC08;
=======
DECLARE_DEVICE_TYPE(MSX_SLOT_PANASONIC08, msx_slot_panasonic08_device)
>>>>>>> upstream/master


#define MCFG_MSX_SLOT_PANASONIC08_ADD(_tag, _startpage, _numpages, _region, _offset) \
	MCFG_MSX_INTERNAL_SLOT_ADD(_tag, MSX_SLOT_PANASONIC08, _startpage, _numpages) \
<<<<<<< HEAD
	msx_slot_panasonic08_device::set_rom_start(*device, _region, _offset);

class msx_slot_panasonic08_device : public device_t,
							public msx_internal_slot_interface
{
public:
	msx_slot_panasonic08_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration helpers
	static void set_rom_start(device_t &device, const char *region, UINT32 offset);

	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;

	virtual DECLARE_READ8_MEMBER(read);
	virtual DECLARE_WRITE8_MEMBER(write);

	void restore_banks();

private:
	required_device<nvram_device> m_nvram;
	const char *m_region;
	UINT32 m_region_offset;
	const UINT8 *m_rom;
	UINT8 m_selected_bank[8];
	const UINT8 *m_bank_base[8];
	UINT8 m_control;
	dynamic_buffer m_sram;

	void map_bank(int bank);
};


#endif
=======
	msx_slot_panasonic08_device::set_rom_start(*device, "^" _region, _offset);

class msx_slot_panasonic08_device : public device_t, public msx_internal_slot_interface
{
public:
	msx_slot_panasonic08_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration helpers
	static void set_rom_start(device_t &device, const char *region, uint32_t offset);

	virtual DECLARE_READ8_MEMBER(read) override;
	virtual DECLARE_WRITE8_MEMBER(write) override;

protected:
	virtual void device_start() override;

	virtual void device_add_mconfig(machine_config &config) override;

private:
	void restore_banks();
	void map_bank(int bank);

	required_device<nvram_device> m_nvram;
	required_memory_region m_rom_region;
	uint32_t m_region_offset;
	const uint8_t *m_rom;
	uint8_t m_selected_bank[8];
	const uint8_t *m_bank_base[8];
	uint8_t m_control;
	std::vector<uint8_t> m_sram;
};


#endif // MAME_BUS_MSX_SLOT_PANASONIC08_H
>>>>>>> upstream/master
