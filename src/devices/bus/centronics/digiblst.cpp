// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
/*
 * digiblst.c
 *
 *  Created on: 23/08/2014
 */

#include "emu.h"
<<<<<<< HEAD
#include "sound/dac.h"
#include "digiblst.h"
=======
#include "digiblst.h"
#include "sound/volt_reg.h"
#include "speaker.h"
>>>>>>> upstream/master

//**************************************************************************
//  COVOX DEVICE
//**************************************************************************

// device type definition
<<<<<<< HEAD
const device_type CENTRONICS_DIGIBLASTER = &device_creator<centronics_digiblaster_device>;

static MACHINE_CONFIG_FRAGMENT( digiblst )
	/* sound hardware */
	MCFG_SPEAKER_STANDARD_MONO("mono")

	MCFG_SOUND_ADD("dac", DAC, 0)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 1.0)
MACHINE_CONFIG_END
=======
DEFINE_DEVICE_TYPE(CENTRONICS_DIGIBLASTER, centronics_digiblaster_device, "digiblst", "Digiblaster (DIY)")
>>>>>>> upstream/master


/***************************************************************************
    IMPLEMENTATION
***************************************************************************/
//-------------------------------------------------
//  centronics_covox_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
centronics_digiblaster_device::centronics_digiblaster_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, CENTRONICS_DIGIBLASTER, "Digiblaster (DIY)", tag, owner, clock, "digiblst", __FILE__),
=======
centronics_digiblaster_device::centronics_digiblaster_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, CENTRONICS_DIGIBLASTER, tag, owner, clock),
>>>>>>> upstream/master
	device_centronics_peripheral_interface( mconfig, *this ),
	m_dac(*this, "dac"),
	m_data(0)
{
}

//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor centronics_digiblaster_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( digiblst );
}
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( centronics_digiblaster_device::device_add_mconfig )
	/* sound hardware */
	MCFG_SPEAKER_STANDARD_MONO("speaker")
	MCFG_SOUND_ADD("dac", DAC_8BIT_R2R, 0) MCFG_SOUND_ROUTE(ALL_OUTPUTS, "speaker", 0.5) // unknown DAC
	MCFG_DEVICE_ADD("vref", VOLTAGE_REGULATOR, 0) MCFG_VOLTAGE_REGULATOR_OUTPUT(5.0)
	MCFG_SOUND_ROUTE_EX(0, "dac", 1.0, DAC_VREF_POS_INPUT) MCFG_SOUND_ROUTE_EX(0, "dac", -1.0, DAC_VREF_NEG_INPUT)
MACHINE_CONFIG_END
>>>>>>> upstream/master

void centronics_digiblaster_device::device_start()
{
	save_item(NAME(m_data));
}

void centronics_digiblaster_device::update_dac()
{
	if (started())
<<<<<<< HEAD
		m_dac->write_unsigned8(m_data);
=======
		m_dac->write(m_data);
>>>>>>> upstream/master
}
