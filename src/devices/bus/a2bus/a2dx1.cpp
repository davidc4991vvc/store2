// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    a2dx1.c

    Implementation of the Decillionix DX-1 sampler card

*********************************************************************/

<<<<<<< HEAD
#include "a2dx1.h"
#include "includes/apple2.h"
#include "sound/dac.h"
=======
#include "emu.h"
#include "a2dx1.h"
#include "sound/volt_reg.h"
#include "speaker.h"
>>>>>>> upstream/master

/***************************************************************************
    PARAMETERS
***************************************************************************/

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type A2BUS_DX1 = &device_creator<a2bus_dx1_device>;

#define DAC_TAG         "dac"

MACHINE_CONFIG_FRAGMENT( a2dx1 )
	MCFG_SPEAKER_STANDARD_MONO("dx1spkr")
	MCFG_SOUND_ADD(DAC_TAG, DAC, 0)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "dx1spkr", 1.00)
MACHINE_CONFIG_END
=======
DEFINE_DEVICE_TYPE(A2BUS_DX1, a2bus_dx1_device, "a2dx1", "Decillonix DX-1")
>>>>>>> upstream/master

/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor a2bus_dx1_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( a2dx1 );
}
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( a2bus_dx1_device::device_add_mconfig )
	MCFG_SPEAKER_STANDARD_MONO("speaker")
	MCFG_SOUND_ADD("dac", DAC_8BIT_R2R, 0) MCFG_SOUND_ROUTE(ALL_OUTPUTS, "speaker", 0.5) // unknown DAC
	MCFG_SOUND_ADD("dacvol", DAC_8BIT_R2R, 0) // unknown DAC
	MCFG_SOUND_ROUTE_EX(0, "dac", 1.0, DAC_VREF_POS_INPUT) MCFG_SOUND_ROUTE_EX(0, "dac", -1.0, DAC_VREF_NEG_INPUT)
	MCFG_DEVICE_ADD("vref", VOLTAGE_REGULATOR, 0) MCFG_VOLTAGE_REGULATOR_OUTPUT(5.0)
	MCFG_SOUND_ROUTE_EX(0, "dacvol", 1.0, DAC_VREF_POS_INPUT)
MACHINE_CONFIG_END
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

<<<<<<< HEAD
a2bus_dx1_device::a2bus_dx1_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source) :
	device_t(mconfig, type, name, tag, owner, clock, shortname, source),
	device_a2bus_card_interface(mconfig, *this),
	m_dac(*this, DAC_TAG), m_volume(0), m_lastdac(0)
{
}

a2bus_dx1_device::a2bus_dx1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, A2BUS_DX1, "Decillonix DX-1", tag, owner, clock, "a2dx1", __FILE__),
	device_a2bus_card_interface(mconfig, *this),
	m_dac(*this, DAC_TAG), m_volume(0), m_lastdac(0)
=======
a2bus_dx1_device::a2bus_dx1_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, type, tag, owner, clock),
	device_a2bus_card_interface(mconfig, *this),
	m_dac(*this, "dac"),
	m_dacvol(*this, "dacvol")
{
}

a2bus_dx1_device::a2bus_dx1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	a2bus_dx1_device(mconfig, A2BUS_DX1, tag, owner, clock)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void a2bus_dx1_device::device_start()
{
	// set_a2bus_device makes m_slot valid
	set_a2bus_device();
<<<<<<< HEAD

	save_item(NAME(m_volume));
	save_item(NAME(m_lastdac));
}

void a2bus_dx1_device::device_reset()
{
	m_volume = m_lastdac = 0;
}

UINT8 a2bus_dx1_device::read_c0nx(address_space &space, UINT8 offset)
=======
}

uint8_t a2bus_dx1_device::read_c0nx(address_space &space, uint8_t offset)
>>>>>>> upstream/master
{
	switch (offset)
	{
		case 1: // ADC input
			return 0;

		case 3: // busy flag
			return 0x80;    // indicate not busy

		case 7: // 1-bit ADC input (bit 7 of c0n1, probably)
			return 0;
	}

	return 0xff;
}

<<<<<<< HEAD
void a2bus_dx1_device::write_c0nx(address_space &space, UINT8 offset, UINT8 data)
{
	switch (offset)
	{
		case 5: // volume
			m_volume = data;
			m_dac->write_unsigned16(data*m_lastdac);
			break;

		case 6:
			m_lastdac = data;
			m_dac->write_unsigned16(data*m_volume);
=======
void a2bus_dx1_device::write_c0nx(address_space &space, uint8_t offset, uint8_t data)
{
	switch (offset)
	{
		case 5:
			m_dacvol->write(data);
			break;

		case 6:
			m_dac->write(data);
>>>>>>> upstream/master
			break;
	}
}

bool a2bus_dx1_device::take_c800()
{
	return false;
}
