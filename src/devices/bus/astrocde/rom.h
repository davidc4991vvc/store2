// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __ASTROCADE_ROM_H
#define __ASTROCADE_ROM_H
=======
#ifndef MAME_BUS_ASTROCADE_ROM_H
#define MAME_BUS_ASTROCADE_ROM_H

#pragma once
>>>>>>> upstream/master

#include "slot.h"


// ======================> astrocade_rom_device

class astrocade_rom_device : public device_t,
						public device_astrocade_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	astrocade_rom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	astrocade_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() {}
	virtual void device_reset() {}

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
=======
	astrocade_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;

protected:
	astrocade_rom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override { }
	virtual void device_reset() override { }
>>>>>>> upstream/master
};

// ======================> astrocade_rom_256k_device

class astrocade_rom_256k_device : public astrocade_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	astrocade_rom_256k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);

private:
	UINT8 m_base_bank;
=======
	astrocade_rom_256k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;

private:
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_base_bank;
>>>>>>> upstream/master
};

// ======================> astrocade_rom_512k_device

class astrocade_rom_512k_device : public astrocade_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	astrocade_rom_512k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);

private:
	UINT8 m_base_bank;
};





// device type definition
extern const device_type ASTROCADE_ROM_STD;
extern const device_type ASTROCADE_ROM_256K;
extern const device_type ASTROCADE_ROM_512K;


#endif
=======
	astrocade_rom_512k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;

private:
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_base_bank;
};


// device type definition
DECLARE_DEVICE_TYPE(ASTROCADE_ROM_STD,  astrocade_rom_device)
DECLARE_DEVICE_TYPE(ASTROCADE_ROM_256K, astrocade_rom_256k_device)
DECLARE_DEVICE_TYPE(ASTROCADE_ROM_512K, astrocade_rom_512k_device)

#endif // MAME_BUS_ASTROCADE_ROM_H
>>>>>>> upstream/master
