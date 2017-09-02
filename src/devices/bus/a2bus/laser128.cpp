// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    laser128.c

    Helper to implement the Laser 128's built-in slot peripherals

*********************************************************************/

<<<<<<< HEAD
#include "laser128.h"
#include "includes/apple2.h"
=======
#include "emu.h"
#include "laser128.h"
>>>>>>> upstream/master

/***************************************************************************
    PARAMETERS
***************************************************************************/

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type A2BUS_LASER128 = &device_creator<a2bus_laser128_device>;

MACHINE_CONFIG_FRAGMENT( a2laser128 )
MACHINE_CONFIG_END
=======
DEFINE_DEVICE_TYPE(A2BUS_LASER128, a2bus_laser128_device, "a2laser128", "VTech Laser 128 Internal Device")
>>>>>>> upstream/master

/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor a2bus_laser128_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( a2laser128 );
}
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( a2bus_laser128_device::device_add_mconfig )
MACHINE_CONFIG_END
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

<<<<<<< HEAD
a2bus_laser128_device::a2bus_laser128_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source) :
	device_t(mconfig, type, name, tag, owner, clock, shortname, source),
=======
a2bus_laser128_device::a2bus_laser128_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, type, tag, owner, clock),
>>>>>>> upstream/master
	device_a2bus_card_interface(mconfig, *this), m_rom(nullptr), m_slot7_bank(0), m_slot7_ram_bank(0)

{
}

<<<<<<< HEAD
a2bus_laser128_device::a2bus_laser128_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, A2BUS_LASER128, "VTech Laser 128 Internal Device", tag, owner, clock, "a2laser128", __FILE__),
	device_a2bus_card_interface(mconfig, *this), m_rom(nullptr), m_slot7_bank(0), m_slot7_ram_bank(0)
=======
a2bus_laser128_device::a2bus_laser128_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	a2bus_laser128_device(mconfig, A2BUS_LASER128, tag, owner, clock)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void a2bus_laser128_device::device_start()
{
	// set_a2bus_device makes m_slot valid
	set_a2bus_device();

	save_item(NAME(m_slot7_bank));
	save_item(NAME(m_slot7_ram_bank));
}

void a2bus_laser128_device::device_reset()
{
	m_rom = device().machine().root_device().memregion("maincpu")->base();
	m_slot7_bank = 0;
	m_slot7_ram_bank = 0;
}

<<<<<<< HEAD
UINT8 a2bus_laser128_device::read_c0nx(address_space &space, UINT8 offset)
=======
uint8_t a2bus_laser128_device::read_c0nx(address_space &space, uint8_t offset)
>>>>>>> upstream/master
{
	return 0x00;
}

<<<<<<< HEAD
void a2bus_laser128_device::write_c0nx(address_space &space, UINT8 offset, UINT8 data)
{
}

UINT8 a2bus_laser128_device::read_cnxx(address_space &space, UINT8 offset)
=======
void a2bus_laser128_device::write_c0nx(address_space &space, uint8_t offset, uint8_t data)
{
}

uint8_t a2bus_laser128_device::read_cnxx(address_space &space, uint8_t offset)
>>>>>>> upstream/master
{
	return m_rom[offset + (m_slot * 0x100) + 0x4000];
}

<<<<<<< HEAD
UINT8 a2bus_laser128_device::read_c800(address_space &space, UINT16 offset)
=======
uint8_t a2bus_laser128_device::read_c800(address_space &space, uint16_t offset)
>>>>>>> upstream/master
{
	switch (m_slot)
	{
		case 1:
			return m_rom[(offset & 0x7ff) + 0x4800];

		case 2:
			return m_rom[(offset & 0x7ff) + 0x5800];

		case 5:
			return m_rom[(offset & 0x7ff) + 0x5000];

		case 6:
			return m_rom[(offset & 0x7ff) + 0x7800];

		case 7:
			if (offset < 0x400)
			{
				return m_slot7_ram[offset];
			}
			return m_rom[(offset & 0x3ff) + 0x6000 + m_slot7_bank];
	}

	return 0xff;
}

<<<<<<< HEAD
void a2bus_laser128_device::write_c800(address_space &space, UINT16 offset, UINT8 data)
=======
void a2bus_laser128_device::write_c800(address_space &space, uint16_t offset, uint8_t data)
>>>>>>> upstream/master
{
	if ((m_slot == 7) && (offset < 0x400))
	{
		m_slot7_ram[offset] = data;
	}

	// UDCREG
	if ((m_slot == 7) && (offset == 0x7f8))
	{
//      printf("%02x to UDCREG\n", data);

		m_slot7_ram_bank = (data & 0x8) ? 0x400 : 0;
		m_slot7_bank = (((data >> 4) & 0x7) * 0x400);

//      printf("\tRAM bank %x, ROM bank %x\n", m_slot7_ram_bank, m_slot7_bank);
	}
}

bool a2bus_laser128_device::take_c800()
{
	if ((m_slot == 1) || (m_slot == 2) || (m_slot == 5) || (m_slot == 6) || (m_slot == 7))
	{
		return true;
	}

	return false;
}
