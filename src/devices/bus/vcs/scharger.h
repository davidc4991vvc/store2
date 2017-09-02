// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __VCS_SCHARGER_H
#define __VCS_SCHARGER_H
=======
#ifndef MAME_BUS_VCS_SCHARGER_H
#define MAME_BUS_VCS_SCHARGER_H

#pragma once
>>>>>>> upstream/master

#include "rom.h"
#include "imagedev/cassette.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> a26_rom_ss_device

class a26_rom_ss_device : public a26_rom_f6_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_ss_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_reset();

	required_device<cassette_image_device> m_cassette;

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);

private:
	cpu_device   *m_maincpu;
	inline UINT8 read_byte(UINT32 offset);

	int m_base_banks[2];
	UINT8 m_reg;
	UINT8 m_write_delay, m_ram_write_enabled, m_rom_enabled;
	UINT32 m_byte_started;
	UINT16 m_last_address;
	UINT32 m_diff_adjust;
=======
	a26_rom_ss_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;

private:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual void device_add_mconfig(machine_config &config) override;

	required_device<cassette_image_device> m_cassette;

	cpu_device   *m_maincpu;
	inline uint8_t read_byte(uint32_t offset);

	int m_base_banks[2];
	uint8_t m_reg;
	uint8_t m_write_delay, m_ram_write_enabled, m_rom_enabled;
	uint32_t m_byte_started;
	uint16_t m_last_address;
	uint32_t m_diff_adjust;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type A26_ROM_SUPERCHARGER;

#endif
=======
DECLARE_DEVICE_TYPE(A26_ROM_SUPERCHARGER, a26_rom_ss_device)

#endif // MAME_BUS_VCS_SCHARGER_H
>>>>>>> upstream/master
