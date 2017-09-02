// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    PS-64 speech cartridge emulation

**********************************************************************/

/*

    PCB Layout
    ----------

    |===========================|
    |=|                         |
    |=|                      SW1|
    |=|       SC02              |
    |=|                         |
    |=|                      CN1|
    |=|       ROM        LF347  |
    |=|                         |
    |=|                         |
    |===========================|

    SC02  - Votrax SSI-263AP Speech Synthesizer
    ROM   - Hynix Semiconductor HY27C64D-20 8Kx8 EPROM
    LF347 - National Instruments LF347N JFET Operational Amplifier
    SW1   - Module on/off switch
    CN1   - connector to C64 video/audio port

*/

/*

    TODO:

    - Votrax SC02 emulation
    - route sound to SID audio input
    - on/off switch

*/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "ps64.h"



//**************************************************************************
//  MACROS/CONSTANTS
//**************************************************************************

#define SSI263_TAG      "ssi263"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type C64_PS64 = &device_creator<c64_ps64_cartridge_device>;
=======
DEFINE_DEVICE_TYPE(C64_PS64, c64_ps64_cartridge_device, "c64_ps64", "C64 PS-64")
>>>>>>> upstream/master


//-------------------------------------------------
//  votrax_sc02_interface votrax_intf
//-------------------------------------------------
/*
static struct votrax_sc02_interface votrax_intf =
{
<<<<<<< HEAD
    DEVCB_NULL
};
*/

//-------------------------------------------------
//  MACHINE_CONFIG_FRAGMENT( c64_ps64 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( c64_ps64 )
=======
    DEVCB_NOOP
};
*/


//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( c64_ps64_cartridge_device::device_add_mconfig )
>>>>>>> upstream/master
	//MCFG_SPEAKER_STANDARD_MONO("mono")
	//MCFG_VOTRAX_SC02_ADD(SSI263_TAG, 2000000, votrax_intf)
	//MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 1.00)
MACHINE_CONFIG_END


<<<<<<< HEAD
//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor c64_ps64_cartridge_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( c64_ps64 );
}


=======
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  c64_ps64_cartridge_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
c64_ps64_cartridge_device::c64_ps64_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, C64_PS64, "C64 PS-64", tag, owner, clock, "c64_ps64", __FILE__),
=======
c64_ps64_cartridge_device::c64_ps64_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, C64_PS64, tag, owner, clock),
>>>>>>> upstream/master
	device_c64_expansion_card_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void c64_ps64_cartridge_device::device_start()
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void c64_ps64_cartridge_device::device_reset()
{
}


//-------------------------------------------------
//  c64_cd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 c64_ps64_cartridge_device::c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2)
=======
uint8_t c64_ps64_cartridge_device::c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2)
>>>>>>> upstream/master
{
	if (!roml)
	{
		data = m_roml[offset & 0x1fff];
	}
	else if (!io1)
	{
		//sc02->read(offset & 0x07);
	}

	return data;
}


//-------------------------------------------------
//  c64_cd_w - cartridge data write
//-------------------------------------------------

<<<<<<< HEAD
void c64_ps64_cartridge_device::c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2)
=======
void c64_ps64_cartridge_device::c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2)
>>>>>>> upstream/master
{
	if (!io1)
	{
		// sc02->write(offset & 0x07, data);
	}
}
