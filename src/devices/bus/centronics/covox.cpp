// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
/***************************************************************************

    Covox Speech Thing

***************************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "sound/dac.h"
#include "covox.h"
=======
#include "covox.h"
#include "sound/volt_reg.h"
#include "speaker.h"
>>>>>>> upstream/master

//**************************************************************************
//  COVOX DEVICE
//**************************************************************************

// device type definition
<<<<<<< HEAD
const device_type CENTRONICS_COVOX = &device_creator<centronics_covox_device>;

static MACHINE_CONFIG_FRAGMENT( covox )
	/* sound hardware */
	MCFG_SPEAKER_STANDARD_MONO("mono")

	MCFG_SOUND_ADD("dac", DAC, 0)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 1.0)
MACHINE_CONFIG_END
=======
DEFINE_DEVICE_TYPE(CENTRONICS_COVOX, centronics_covox_device, "covox", "Covox Speech Thing")
>>>>>>> upstream/master


/***************************************************************************
    IMPLEMENTATION
***************************************************************************/
//-------------------------------------------------
//  centronics_covox_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
centronics_covox_device::centronics_covox_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, CENTRONICS_COVOX, "Covox Speech Thing", tag, owner, clock, "covox", __FILE__),
=======
centronics_covox_device::centronics_covox_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, CENTRONICS_COVOX, tag, owner, clock),
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

machine_config_constructor centronics_covox_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( covox );
}
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( centronics_covox_device::device_add_mconfig )
	/* sound hardware */
	MCFG_SPEAKER_STANDARD_MONO("speaker")
	MCFG_SOUND_ADD("dac", DAC_8BIT_R2R, 0) MCFG_SOUND_ROUTE(ALL_OUTPUTS, "speaker", 0.5) // unknown DAC
	MCFG_DEVICE_ADD("vref", VOLTAGE_REGULATOR, 0) MCFG_VOLTAGE_REGULATOR_OUTPUT(5.0)
	MCFG_SOUND_ROUTE_EX(0, "dac", 1.0, DAC_VREF_POS_INPUT) MCFG_SOUND_ROUTE_EX(0, "dac", -1.0, DAC_VREF_NEG_INPUT)
MACHINE_CONFIG_END
>>>>>>> upstream/master

void centronics_covox_device::device_start()
{
	save_item(NAME(m_data));
}

void centronics_covox_device::update_dac()
{
	if (started())
<<<<<<< HEAD
		m_dac->write_unsigned8(m_data);
=======
		m_dac->write(m_data);
>>>>>>> upstream/master
}

//**************************************************************************
//  COVOX STEREO DEVICE
//**************************************************************************

// device type definition
<<<<<<< HEAD
const device_type CENTRONICS_COVOX_STEREO = &device_creator<centronics_covox_stereo_device>;

static MACHINE_CONFIG_FRAGMENT( covox_stereo )
	/* sound hardware */
	MCFG_SPEAKER_STANDARD_STEREO("lspeaker", "rspeaker")

	MCFG_SOUND_ADD("dac_left", DAC, 0)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "lspeaker", 1.0)

	MCFG_SOUND_ADD("dac_right", DAC, 0)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "rspeaker", 1.0)
MACHINE_CONFIG_END
=======
DEFINE_DEVICE_TYPE(CENTRONICS_COVOX_STEREO, centronics_covox_stereo_device, "covox_stereo", "Covox (Stereo-in-1)")
>>>>>>> upstream/master


/***************************************************************************
    IMPLEMENTATION
***************************************************************************/
//-------------------------------------------------
//  centronics_covox_stereo_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
centronics_covox_stereo_device::centronics_covox_stereo_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, CENTRONICS_COVOX_STEREO, "Covox (Stereo-in-1)", tag, owner, clock, "covox_stereo", __FILE__),
	device_centronics_peripheral_interface( mconfig, *this ),
	m_dac_left(*this, "dac_left"),
	m_dac_right(*this, "dac_right"), m_strobe(0),
	m_data(0), m_autofd(0)
=======
centronics_covox_stereo_device::centronics_covox_stereo_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, CENTRONICS_COVOX_STEREO, tag, owner, clock),
	device_centronics_peripheral_interface( mconfig, *this ),
	m_ldac(*this, "ldac"),
	m_rdac(*this, "rdac"),
	m_strobe(0),
	m_data(0),
	m_autofd(0)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor centronics_covox_stereo_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( covox_stereo );
}
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( centronics_covox_stereo_device::device_add_mconfig )
	/* sound hardware */
	MCFG_SPEAKER_STANDARD_STEREO("lspeaker", "rspeaker")
	MCFG_SOUND_ADD("ldac", DAC_8BIT_R2R, 0) MCFG_SOUND_ROUTE(ALL_OUTPUTS, "lspeaker", 0.5) // unknown DAC
	MCFG_SOUND_ADD("rdac", DAC_8BIT_R2R, 0) MCFG_SOUND_ROUTE(ALL_OUTPUTS, "rspeaker", 0.5) // unknown DAC
	MCFG_DEVICE_ADD("vref", VOLTAGE_REGULATOR, 0) MCFG_VOLTAGE_REGULATOR_OUTPUT(5.0)
	MCFG_SOUND_ROUTE_EX(0, "ldac", 1.0, DAC_VREF_POS_INPUT) MCFG_SOUND_ROUTE_EX(0, "ldac", -1.0, DAC_VREF_NEG_INPUT)
	MCFG_SOUND_ROUTE_EX(0, "rdac", 1.0, DAC_VREF_POS_INPUT) MCFG_SOUND_ROUTE_EX(0, "rdac", -1.0, DAC_VREF_NEG_INPUT)
MACHINE_CONFIG_END
>>>>>>> upstream/master

void centronics_covox_stereo_device::device_start()
{
	save_item(NAME(m_data));
	save_item(NAME(m_strobe));
	save_item(NAME(m_autofd));
}

void centronics_covox_stereo_device::update_dac()
{
	if (started())
	{
		if (m_strobe)
<<<<<<< HEAD
			m_dac_left->write_unsigned8(m_data);

		if (m_autofd)
			m_dac_right->write_unsigned8(m_data);
=======
			m_ldac->write(m_data);

		if (m_autofd)
			m_rdac->write(m_data);
>>>>>>> upstream/master
	}
}
