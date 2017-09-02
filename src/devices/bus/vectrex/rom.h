// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __VECTREX_ROM_H
#define __VECTREX_ROM_H
=======
#ifndef MAME_BUS_VECTREX_ROM_H
#define MAME_BUS_VECTREX_ROM_H

#pragma once
>>>>>>> upstream/master

#include "slot.h"


// ======================> vectrex_rom_device

class vectrex_rom_device : public device_t,
						public device_vectrex_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vectrex_rom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	vectrex_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() {}
	virtual void device_reset() {}

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
=======
	vectrex_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;

protected:
	vectrex_rom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override { }
	virtual void device_reset() override { }
>>>>>>> upstream/master
};

// ======================> vectrex_rom64k_device

class vectrex_rom64k_device : public vectrex_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	vectrex_rom64k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
=======
	vectrex_rom64k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	int m_bank;
};

// ======================> vectrex_sram_device

class vectrex_sram_device : public vectrex_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	vectrex_sram_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_WRITE8_MEMBER(write_ram);
=======
	vectrex_sram_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;
>>>>>>> upstream/master
};



// device type definition
<<<<<<< HEAD
extern const device_type VECTREX_ROM_STD;
extern const device_type VECTREX_ROM_64K;
extern const device_type VECTREX_ROM_SRAM;


#endif
=======
DECLARE_DEVICE_TYPE(VECTREX_ROM_STD,  vectrex_rom_device)
DECLARE_DEVICE_TYPE(VECTREX_ROM_64K,  vectrex_rom64k_device)
DECLARE_DEVICE_TYPE(VECTREX_ROM_SRAM, vectrex_sram_device)

#endif // MAME_BUS_VECTREX_ROM_H
>>>>>>> upstream/master
