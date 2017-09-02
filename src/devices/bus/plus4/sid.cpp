// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore Plus/4 SID cartridge emulation

    http://solder.dyndns.info/cgi-bin/showdir.pl?dir=files/commodore/plus4/hardware/SID-Card

**********************************************************************/

/*

    TODO:

    - GAL16V8 dump
    - get SID clock from expansion port

*/

<<<<<<< HEAD
#include "sid.h"

=======
#include "emu.h"
#include "sid.h"

#include "speaker.h"

>>>>>>> upstream/master


//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define MOS8580_TAG     "mos8580"
#define CONTROL1_TAG    "joy1"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type PLUS4_SID = &device_creator<plus4_sid_cartridge_device>;
=======
DEFINE_DEVICE_TYPE(PLUS4_SID, plus4_sid_cartridge_device, "plus4_sid", "Plus/4 SID cartridge")
>>>>>>> upstream/master


//-------------------------------------------------
//  ROM( plus4_sid )
//-------------------------------------------------

ROM_START( plus4_sid )
	ROM_REGION( 0x100, "pld", 0 )
	ROM_LOAD( "gal16v8", 0x000, 0x100, NO_DUMP )
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *plus4_sid_cartridge_device::device_rom_region() const
=======
const tiny_rom_entry *plus4_sid_cartridge_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( plus4_sid );
}


//-------------------------------------------------
<<<<<<< HEAD
//  MACHINE_CONFIG_FRAGMENT( plus4_sid )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( plus4_sid )
	MCFG_SPEAKER_STANDARD_MONO("mono")
	MCFG_SOUND_ADD(MOS8580_TAG, MOS8580, XTAL_17_73447MHz/20)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 1.00)
	MCFG_SOUND_ADD("dac", DAC, 0)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.25)

	MCFG_VCS_CONTROL_PORT_ADD(CONTROL1_TAG, vcs_control_port_devices, NULL)
MACHINE_CONFIG_END


//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor plus4_sid_cartridge_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( plus4_sid );
}


=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( plus4_sid_cartridge_device::device_add_mconfig )
	MCFG_SPEAKER_STANDARD_MONO("speaker")
	MCFG_SOUND_ADD(MOS8580_TAG, MOS8580, XTAL_17_73447MHz/20)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "speaker", 1.0)

	MCFG_VCS_CONTROL_PORT_ADD(CONTROL1_TAG, vcs_control_port_devices, nullptr)
MACHINE_CONFIG_END


>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  plus4_sid_cartridge_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
plus4_sid_cartridge_device::plus4_sid_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, PLUS4_SID, "Plus/4 SID cartridge", tag, owner, clock, "plus4_sid", __FILE__),
=======
plus4_sid_cartridge_device::plus4_sid_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, PLUS4_SID, tag, owner, clock),
>>>>>>> upstream/master
	device_plus4_expansion_card_interface(mconfig, *this),
	m_sid(*this, MOS8580_TAG),
	m_joy(*this, CONTROL1_TAG)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void plus4_sid_cartridge_device::device_start()
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void plus4_sid_cartridge_device::device_reset()
{
	m_sid->reset();
}


//-------------------------------------------------
//  plus4_cd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 plus4_sid_cartridge_device::plus4_cd_r(address_space &space, offs_t offset, UINT8 data, int ba, int cs0, int c1l, int c2l, int cs1, int c1h, int c2h)
=======
uint8_t plus4_sid_cartridge_device::plus4_cd_r(address_space &space, offs_t offset, uint8_t data, int ba, int cs0, int c1l, int c2l, int cs1, int c1h, int c2h)
>>>>>>> upstream/master
{
	if ((offset >= 0xfe80 && offset < 0xfea0) || (offset >= 0xfd40 && offset < 0xfd60))
	{
		data = m_sid->read(space, offset & 0x1f);
	}
	else if (offset >= 0xfd80 && offset < 0xfd90)
	{
		data = m_joy->joy_r(space, 0);
	}

	return data;
}


//-------------------------------------------------
//  plus4_cd_w - cartridge data write
//-------------------------------------------------

<<<<<<< HEAD
void plus4_sid_cartridge_device::plus4_cd_w(address_space &space, offs_t offset, UINT8 data, int ba, int cs0, int c1l, int c2l, int cs1, int c1h, int c2h)
=======
void plus4_sid_cartridge_device::plus4_cd_w(address_space &space, offs_t offset, uint8_t data, int ba, int cs0, int c1l, int c2l, int cs1, int c1h, int c2h)
>>>>>>> upstream/master
{
	if ((offset >= 0xfe80 && offset < 0xfea0) || (offset >= 0xfd40 && offset < 0xfd60))
	{
		m_sid->write(space, offset & 0x1f, data);
	}
}


//-------------------------------------------------
//  plus4_breset_w - buffered reset write
//-------------------------------------------------

void plus4_sid_cartridge_device::plus4_breset_w(int state)
{
	if (state == ASSERT_LINE)
	{
		device_reset();
	}
}
