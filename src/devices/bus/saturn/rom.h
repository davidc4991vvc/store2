// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __SAT_ROM_H
#define __SAT_ROM_H
=======
#ifndef MAME_BUS_SATURN_ROM_H
#define MAME_BUS_SATURN_ROM_H
>>>>>>> upstream/master

#include "sat_slot.h"


// ======================> saturn_rom_device

<<<<<<< HEAD
class saturn_rom_device : public device_t,
						public device_sat_cart_interface
{
public:
	// construction/destruction
	saturn_rom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	saturn_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ32_MEMBER(read_rom);
};



// device type definition
extern const device_type SATURN_ROM;


#endif
=======
class saturn_rom_device : public device_t, public device_sat_cart_interface
{
public:
	// construction/destruction
	saturn_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ32_MEMBER(read_rom) override;

protected:
	saturn_rom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, int cart_type);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
};


// device type definition
DECLARE_DEVICE_TYPE(SATURN_ROM, saturn_rom_device)

#endif // MAME_BUS_SATURN_ROM_H
>>>>>>> upstream/master
