// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
/***************************************************************************

  ISA 8 bit Adlib Sound Card

***************************************************************************/

#include "emu.h"
#include "adlib.h"
<<<<<<< HEAD
#include "sound/speaker.h"

#define ym3812_StdClock 3579545

static MACHINE_CONFIG_FRAGMENT( adlib_config )
	MCFG_SPEAKER_STANDARD_MONO("mono")
	MCFG_SOUND_ADD("ym3812", YM3812, ym3812_StdClock)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 3.00)
MACHINE_CONFIG_END

READ8_MEMBER( isa8_adlib_device::ym3812_16_r )
{
	UINT8 retVal = 0xff;
=======

#include "sound/spkrdev.h"
#include "speaker.h"


#define ym3812_StdClock 3579545

READ8_MEMBER( isa8_adlib_device::ym3812_16_r )
{
	uint8_t retVal = 0xff;
>>>>>>> upstream/master
	switch(offset)
	{
		case 0 : retVal = m_ym3812->status_port_r( space, offset ); break;
	}
	return retVal;
}

WRITE8_MEMBER( isa8_adlib_device::ym3812_16_w )
{
	switch(offset)
	{
		case 0 : m_ym3812->control_port_w( space, offset, data ); break;
		case 1 : m_ym3812->write_port_w( space, offset, data ); break;
	}
}

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type ISA8_ADLIB = &device_creator<isa8_adlib_device>;

//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor isa8_adlib_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( adlib_config );
}
=======
DEFINE_DEVICE_TYPE(ISA8_ADLIB, isa8_adlib_device, "isa_adlib", "Ad Lib Sound Card")

//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( isa8_adlib_device::device_add_mconfig )
	MCFG_SPEAKER_STANDARD_MONO("mono")
	MCFG_SOUND_ADD("ym3812", YM3812, ym3812_StdClock)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 3.00)
MACHINE_CONFIG_END
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  isa8_adlib_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
isa8_adlib_device::isa8_adlib_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: device_t(mconfig, ISA8_ADLIB, "Ad Lib Sound Card", tag, owner, clock, "isa_adlib", __FILE__),
		device_isa8_card_interface( mconfig, *this ),
		m_ym3812(*this, "ym3812")
=======
isa8_adlib_device::isa8_adlib_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, ISA8_ADLIB, tag, owner, clock)
	, device_isa8_card_interface(mconfig, *this)
	, m_ym3812(*this, "ym3812")
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void isa8_adlib_device::device_start()
{
	set_isa_device();
<<<<<<< HEAD
	m_isa->install_device(0x0388, 0x0389, 0, 0, read8_delegate( FUNC(isa8_adlib_device::ym3812_16_r), this ), write8_delegate( FUNC(isa8_adlib_device::ym3812_16_w), this ) );
=======
	m_isa->install_device(0x0388, 0x0389, read8_delegate( FUNC(isa8_adlib_device::ym3812_16_r), this ), write8_delegate( FUNC(isa8_adlib_device::ym3812_16_w), this ) );
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void isa8_adlib_device::device_reset()
{
}
