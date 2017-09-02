// license:BSD-3-Clause
// copyright-holders:R. Belmont
/**********************************************************************

    Commodore PET userport "CB2 sound" audio device emulation

    http://zimmers.net/cbmpics/cbm/PETx/petfaq.html

**********************************************************************/

<<<<<<< HEAD
#include "cb2snd.h"

=======
#include "emu.h"
#include "cb2snd.h"

#include "sound/volt_reg.h"
#include "speaker.h"


>>>>>>> upstream/master
//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type PET_USERPORT_CB2_SOUND_DEVICE = &device_creator<pet_userport_cb2_sound_device>;

#define DAC_TAG         "dac"

MACHINE_CONFIG_FRAGMENT( cb2snd )
	MCFG_SPEAKER_STANDARD_MONO("cb2spkr")
	MCFG_SOUND_ADD(DAC_TAG, DAC, 0)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "cb2spkr", 1.00)
MACHINE_CONFIG_END

//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor pet_userport_cb2_sound_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( cb2snd );
}
=======
DEFINE_DEVICE_TYPE(PET_USERPORT_CB2_SOUND_DEVICE, pet_userport_cb2_sound_device, "petucb2", "PET Userport 'CB2 Sound' Device")


//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( pet_userport_cb2_sound_device::device_add_mconfig )
	MCFG_SPEAKER_STANDARD_MONO("speaker")
	MCFG_SOUND_ADD("dac", DAC_1BIT, 0) MCFG_SOUND_ROUTE(ALL_OUTPUTS, "speaker", 0.99)
	MCFG_DEVICE_ADD("vref", VOLTAGE_REGULATOR, 0) MCFG_VOLTAGE_REGULATOR_OUTPUT(5.0)
	MCFG_SOUND_ROUTE_EX(0, "dac", 1.0, DAC_VREF_POS_INPUT)
MACHINE_CONFIG_END
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  pet_userport_cb2_sound_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
pet_userport_cb2_sound_device::pet_userport_cb2_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, PET_USERPORT_CB2_SOUND_DEVICE, "PET Userport 'CB2 Sound' Device", tag, owner, clock, "petucb2", __FILE__),
	device_pet_user_port_interface(mconfig, *this),
	m_dac(*this, DAC_TAG)
=======
pet_userport_cb2_sound_device::pet_userport_cb2_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, PET_USERPORT_CB2_SOUND_DEVICE, tag, owner, clock),
	device_pet_user_port_interface(mconfig, *this),
	m_dac(*this, "dac")
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void pet_userport_cb2_sound_device::device_start()
{
}

DECLARE_WRITE_LINE_MEMBER( pet_userport_cb2_sound_device::input_m )
{
<<<<<<< HEAD
	m_dac->write_unsigned8(state ? 0xff : 0x00);
=======
	m_dac->write(state);
>>>>>>> upstream/master
}
