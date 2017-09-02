// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/***********************************************************************************************************


 Mattel Intellivision cart emulation


 ***********************************************************************************************************/


#include "emu.h"
#include "rom.h"


//-------------------------------------------------
//  intv_rom_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
const device_type INTV_ROM_STD = &device_creator<intv_rom_device>;
const device_type INTV_ROM_RAM = &device_creator<intv_ram_device>;
const device_type INTV_ROM_GFACT = &device_creator<intv_gfact_device>;
const device_type INTV_ROM_WSMLB = &device_creator<intv_wsmlb_device>;


intv_rom_device::intv_rom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source)
					: device_t(mconfig, type, name, tag, owner, clock, shortname, source),
						device_intv_cart_interface( mconfig, *this )
{
}

intv_rom_device::intv_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
					: device_t(mconfig, INTV_ROM_STD, "Intellivision Standard Carts", tag, owner, clock, "intv_rom", __FILE__),
						device_intv_cart_interface( mconfig, *this )
{
}

intv_ram_device::intv_ram_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
					: intv_rom_device(mconfig, INTV_ROM_RAM, "Intellivision Carts w/RAM", tag, owner, clock, "intv_ram", __FILE__)
{
}

intv_gfact_device::intv_gfact_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
					: intv_rom_device(mconfig, INTV_ROM_GFACT, "Intellivision Game Factory Cart", tag, owner, clock, "intv_gfact", __FILE__)
{
}

intv_wsmlb_device::intv_wsmlb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
					: intv_rom_device(mconfig, INTV_ROM_WSMLB, "Intellivision World Series Baseball Cart", tag, owner, clock, "intv_wsmlb", __FILE__)
=======
DEFINE_DEVICE_TYPE(INTV_ROM_STD,   intv_rom_device,   "intv_rom",   "Intellivision Standard Carts")
DEFINE_DEVICE_TYPE(INTV_ROM_RAM,   intv_ram_device,   "intv_ram",   "Intellivision Carts w/RAM")
DEFINE_DEVICE_TYPE(INTV_ROM_GFACT, intv_gfact_device, "intv_gfact", "Intellivision Game Factory Cart")
DEFINE_DEVICE_TYPE(INTV_ROM_WSMLB, intv_wsmlb_device, "intv_wsmlb", "Intellivision World Series Baseball Cart")


intv_rom_device::intv_rom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, type, tag, owner, clock)
	, device_intv_cart_interface(mconfig, *this)
{
}

intv_rom_device::intv_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: intv_rom_device(mconfig, INTV_ROM_STD, tag, owner, clock)
{
}

intv_ram_device::intv_ram_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: intv_rom_device(mconfig, INTV_ROM_RAM, tag, owner, clock)
{
}

intv_gfact_device::intv_gfact_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: intv_rom_device(mconfig, INTV_ROM_GFACT, tag, owner, clock)
{
}

intv_wsmlb_device::intv_wsmlb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: intv_rom_device(mconfig, INTV_ROM_WSMLB, tag, owner, clock)
>>>>>>> upstream/master
{
}
