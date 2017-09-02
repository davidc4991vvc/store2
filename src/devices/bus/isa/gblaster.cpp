// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
/***************************************************************************

  ISA 8 bit Creative Labs Game Blaster Sound Card

***************************************************************************/

#include "emu.h"
#include "gblaster.h"
<<<<<<< HEAD
#include "sound/speaker.h"
=======

#include "sound/spkrdev.h"
#include "speaker.h"
>>>>>>> upstream/master

/*
  creative labs game blaster (CMS creative music system)
  2 x saa1099 chips
  also on sound blaster 1.0
  option on sound blaster 1.5

  jumperable? normally 0x220
*/
<<<<<<< HEAD
static MACHINE_CONFIG_FRAGMENT( game_blaster_config )
	MCFG_SPEAKER_STANDARD_STEREO("lspeaker", "rspeaker")
	MCFG_SAA1099_ADD("saa1099.1", 7159090)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "lspeaker", 0.50)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "rspeaker", 0.50)
	MCFG_SAA1099_ADD("saa1099.2", 7159090)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "lspeaker", 0.50)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "rspeaker", 0.50)
MACHINE_CONFIG_END
=======

>>>>>>> upstream/master

READ8_MEMBER( isa8_gblaster_device::saa1099_16_r )
{
	return 0xff;
}

WRITE8_MEMBER( isa8_gblaster_device::saa1099_1_16_w )
{
<<<<<<< HEAD
	switch(offset)
	{
		case 0 : m_saa1099_1->data_w( space, offset, data ); break;
		case 1 : m_saa1099_1->control_w( space, offset, data ); break;
	}
=======
	m_saa1099_1->write(space, offset, data);
>>>>>>> upstream/master
}

WRITE8_MEMBER( isa8_gblaster_device::saa1099_2_16_w )
{
<<<<<<< HEAD
	switch(offset)
	{
		case 0 : m_saa1099_2->data_w( space, offset, data ); break;
		case 1 : m_saa1099_2->control_w( space, offset, data ); break;
	}
=======
	m_saa1099_2->write(space, offset, data);
>>>>>>> upstream/master
}

READ8_MEMBER( isa8_gblaster_device::detect_r )
{
	switch(offset)
	{
		case 0:
		case 1: return 0x7f; break;  // this register reportedly returns 0x3f on a Tandy 1000 TL, and 0x7f on a generic 486 PC.
		case 6:
		case 7: return detect_reg; break;
		default: return 0xff;
	}
}

WRITE8_MEMBER( isa8_gblaster_device::detect_w )
{
	switch(offset)
	{
		case 2:
		case 3: detect_reg = (data & 0xff); break;
	}
}

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type ISA8_GAME_BLASTER = &device_creator<isa8_gblaster_device>;

//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor isa8_gblaster_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( game_blaster_config );
}
=======
DEFINE_DEVICE_TYPE(ISA8_GAME_BLASTER, isa8_gblaster_device, "isa_gblaster", "Game Blaster Sound Card")

//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( isa8_gblaster_device::device_add_mconfig )
	MCFG_SPEAKER_STANDARD_STEREO("lspeaker", "rspeaker")
	MCFG_SAA1099_ADD("saa1099.1", 7159090)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "lspeaker", 0.50)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "rspeaker", 0.50)
	MCFG_SAA1099_ADD("saa1099.2", 7159090)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "lspeaker", 0.50)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "rspeaker", 0.50)
MACHINE_CONFIG_END
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  isa8_gblaster_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
isa8_gblaster_device::isa8_gblaster_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
		device_t(mconfig, ISA8_GAME_BLASTER, "Game Blaster Sound Card", tag, owner, clock, "isa_gblaster", __FILE__),
		device_isa8_card_interface(mconfig, *this),
		m_saa1099_1(*this, "saa1099.1"),
		m_saa1099_2(*this, "saa1099.2"),
		detect_reg(0xFF)
=======
isa8_gblaster_device::isa8_gblaster_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, ISA8_GAME_BLASTER, tag, owner, clock),
	device_isa8_card_interface(mconfig, *this),
	m_saa1099_1(*this, "saa1099.1"),
	m_saa1099_2(*this, "saa1099.2"),
	detect_reg(0xFF)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void isa8_gblaster_device::device_start()
{
	set_isa_device();
<<<<<<< HEAD
	m_isa->install_device(0x0220, 0x0221, 0, 0, read8_delegate( FUNC(isa8_gblaster_device::saa1099_16_r), this ), write8_delegate( FUNC(isa8_gblaster_device::saa1099_1_16_w), this ) );
	m_isa->install_device(0x0222, 0x0223, 0, 0, read8_delegate( FUNC(isa8_gblaster_device::saa1099_16_r), this ), write8_delegate( FUNC(isa8_gblaster_device::saa1099_2_16_w), this ) );
	m_isa->install_device(0x0224, 0x022F, 0, 0, read8_delegate( FUNC(isa8_gblaster_device::detect_r), this ), write8_delegate( FUNC(isa8_gblaster_device::detect_w), this ) );
=======
	m_isa->install_device(0x0220, 0x0221, read8_delegate( FUNC(isa8_gblaster_device::saa1099_16_r), this ), write8_delegate( FUNC(isa8_gblaster_device::saa1099_1_16_w), this ) );
	m_isa->install_device(0x0222, 0x0223, read8_delegate( FUNC(isa8_gblaster_device::saa1099_16_r), this ), write8_delegate( FUNC(isa8_gblaster_device::saa1099_2_16_w), this ) );
	m_isa->install_device(0x0224, 0x022F, read8_delegate( FUNC(isa8_gblaster_device::detect_r), this ), write8_delegate( FUNC(isa8_gblaster_device::detect_w), this ) );
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void isa8_gblaster_device::device_reset()
{
}
