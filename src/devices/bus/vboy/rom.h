// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __VBOY_ROM_H
#define __VBOY_ROM_H
=======
#ifndef MAME_BUS_VBOY_ROM_H
#define MAME_BUS_VBOY_ROM_H

#pragma once
>>>>>>> upstream/master

#include "slot.h"


// ======================> vboy_rom_device

class vboy_rom_device : public device_t,
						public device_vboy_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vboy_rom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	vboy_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() {}

	// reading and writing
	virtual DECLARE_READ32_MEMBER(read_cart);
=======
	vboy_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ32_MEMBER(read_cart) override;

protected:
	vboy_rom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override { }
>>>>>>> upstream/master
};

// ======================> vboy_eeprom_device

class vboy_eeprom_device : public vboy_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	vboy_eeprom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ32_MEMBER(read_eeprom);
	virtual DECLARE_WRITE32_MEMBER(write_eeprom);
};



// device type definition
extern const device_type VBOY_ROM_STD;
extern const device_type VBOY_ROM_EEPROM;



#endif
=======
	vboy_eeprom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ32_MEMBER(read_eeprom) override;
	virtual DECLARE_WRITE32_MEMBER(write_eeprom) override;
};


// device type definition
DECLARE_DEVICE_TYPE(VBOY_ROM_STD,    vboy_rom_device)
DECLARE_DEVICE_TYPE(VBOY_ROM_EEPROM, vboy_eeprom_device)

#endif // MAME_BUS_VBOY_ROM_H
>>>>>>> upstream/master
