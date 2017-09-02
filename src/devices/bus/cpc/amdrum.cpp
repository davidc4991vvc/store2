// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
/*
<<<<<<< HEAD
 * amdrum.c
=======
 * amdrum.cpp
>>>>>>> upstream/master
 *
 *  Created on: 23/08/2014
 */

#include "emu.h"
#include "amdrum.h"
<<<<<<< HEAD
#include "includes/amstrad.h"
=======

#include "sound/volt_reg.h"
#include "speaker.h"
>>>>>>> upstream/master


//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type CPC_AMDRUM = &device_creator<cpc_amdrum_device>;


static MACHINE_CONFIG_FRAGMENT( cpc_amdrum )
	MCFG_SPEAKER_STANDARD_MONO("mono")
	MCFG_DAC_ADD("dac")
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 1.00)
	// no pass-through
MACHINE_CONFIG_END

machine_config_constructor cpc_amdrum_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( cpc_amdrum );
}
=======
DEFINE_DEVICE_TYPE(CPC_AMDRUM, cpc_amdrum_device, "cpc_amdrum", "Amdrum")


MACHINE_CONFIG_MEMBER( cpc_amdrum_device::device_add_mconfig )
	MCFG_SPEAKER_STANDARD_MONO("speaker")
	MCFG_SOUND_ADD("dac", DAC_8BIT_R2R, 0) MCFG_SOUND_ROUTE(ALL_OUTPUTS, "speaker", 0.5) // unknown DAC
	MCFG_DEVICE_ADD("vref", VOLTAGE_REGULATOR, 0) MCFG_VOLTAGE_REGULATOR_OUTPUT(5.0)
	MCFG_SOUND_ROUTE_EX(0, "dac", 1.0, DAC_VREF_POS_INPUT) MCFG_SOUND_ROUTE_EX(0, "dac", -1.0, DAC_VREF_NEG_INPUT)
	// no pass-through
MACHINE_CONFIG_END

>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

<<<<<<< HEAD
cpc_amdrum_device::cpc_amdrum_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, CPC_AMDRUM, "Amdrum", tag, owner, clock, "cpc_amdrum", __FILE__),
=======
cpc_amdrum_device::cpc_amdrum_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, CPC_AMDRUM, tag, owner, clock),
>>>>>>> upstream/master
	device_cpc_expansion_card_interface(mconfig, *this),
	m_slot(nullptr),
	m_dac(*this,"dac")
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void cpc_amdrum_device::device_start()
{
	device_t* cpu = machine().device("maincpu");
	address_space& space = cpu->memory().space(AS_IO);
	m_slot = dynamic_cast<cpc_expansion_slot_device *>(owner());

<<<<<<< HEAD
	space.install_write_handler(0xff00,0xffff,0,0,write8_delegate(FUNC(cpc_amdrum_device::dac_w),this));
=======
	space.install_write_handler(0xff00,0xffff,write8_delegate(FUNC(cpc_amdrum_device::dac_w),this));
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void cpc_amdrum_device::device_reset()
{
	// TODO
}

WRITE8_MEMBER(cpc_amdrum_device::dac_w)
{
<<<<<<< HEAD
	m_dac->write_unsigned8(data);
=======
	m_dac->write(data);
>>>>>>> upstream/master
}
