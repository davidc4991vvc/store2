// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore 64 16KB EPROM cartridge emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "16kb.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type C64_16KB = &device_creator<c64_16kb_cartridge_device>;


//-------------------------------------------------
//  MACHINE_CONFIG_FRAGMENT( c64_16kb )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( c64_16kb )
	MCFG_GENERIC_CARTSLOT_ADD("roml", generic_linear_slot, NULL)
	MCFG_GENERIC_EXTENSIONS("rom,bin,80")

	MCFG_GENERIC_CARTSLOT_ADD("romh", generic_linear_slot, NULL)
=======
DEFINE_DEVICE_TYPE(C64_16KB, c64_16kb_cartridge_device, "c64_16kb", "C64 16KB EPROM cartridge")


//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( c64_16kb_cartridge_device::device_add_mconfig )
	MCFG_GENERIC_CARTSLOT_ADD("roml", generic_linear_slot, nullptr)
	MCFG_GENERIC_EXTENSIONS("rom,bin,80")

	MCFG_GENERIC_CARTSLOT_ADD("romh", generic_linear_slot, nullptr)
>>>>>>> upstream/master
	MCFG_GENERIC_EXTENSIONS("rom,bin,a0,e0")
MACHINE_CONFIG_END


//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor c64_16kb_cartridge_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( c64_16kb );
}


//-------------------------------------------------
=======
>>>>>>> upstream/master
//  INPUT_PORTS( c64_16kb )
//-------------------------------------------------

static INPUT_PORTS_START( c64_16kb )
	PORT_START("SW1")
	PORT_DIPNAME( 0x03, 0x00, "Mode" )
	PORT_DIPSETTING(    0x03, "Off" )
	PORT_DIPSETTING(    0x02, "8 KB" )
	PORT_DIPSETTING(    0x00, "16 KB" )
	PORT_DIPSETTING(    0x01, "Ultimax" )
INPUT_PORTS_END


//-------------------------------------------------
//  input_ports - device-specific input ports
//-------------------------------------------------

ioport_constructor c64_16kb_cartridge_device::device_input_ports() const
{
	return INPUT_PORTS_NAME( c64_16kb );
}


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  c64_16kb_cartridge_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
c64_16kb_cartridge_device::c64_16kb_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, C64_16KB, "C64 16KB EPROM cartridge", tag, owner, clock, "c64_16kb", __FILE__),
=======
c64_16kb_cartridge_device::c64_16kb_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, C64_16KB, tag, owner, clock),
>>>>>>> upstream/master
	device_c64_expansion_card_interface(mconfig, *this),
	m_sw1(*this, "SW1"),
	m_low(*this, "roml"),
	m_high(*this, "romh")
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void c64_16kb_cartridge_device::device_start()
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void c64_16kb_cartridge_device::device_reset()
{
<<<<<<< HEAD
	UINT8 mode = m_sw1->read();
=======
	uint8_t mode = m_sw1->read();
>>>>>>> upstream/master

	m_exrom = BIT(mode, 0);
	m_game = BIT(mode, 1);
}


//-------------------------------------------------
//  c64_cd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 c64_16kb_cartridge_device::c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2)
=======
uint8_t c64_16kb_cartridge_device::c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2)
>>>>>>> upstream/master
{
	if (!roml)
	{
		data = m_low->read_rom(space, offset & 0x1fff);
	}
	else if (!romh)
	{
		data = m_high->read_rom(space, offset & 0x1fff);
	}

	return data;
}
