// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
/*
<<<<<<< HEAD
 * cpc_pds.c  --  CPC interface hardware for the Programmers Development System
=======
 * cpc_pds.cpp  --  CPC interface hardware for the Programmers Development System
>>>>>>> upstream/master
 *
 *  Created on: 10/02/2014
 */

#include "emu.h"
#include "cpc_pds.h"
<<<<<<< HEAD
#include "includes/amstrad.h"
=======
>>>>>>> upstream/master


//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type CPC_PDS = &device_creator<cpc_pds_device>;


static MACHINE_CONFIG_FRAGMENT( cpc_pds )
=======
DEFINE_DEVICE_TYPE(CPC_PDS, cpc_pds_device, "cpc_pds", "Programmers Development System (CPC Target)")


MACHINE_CONFIG_MEMBER( cpc_pds_device::device_add_mconfig )
>>>>>>> upstream/master
	MCFG_DEVICE_ADD("pio", Z80PIO, XTAL_4MHz)   // no clock on the PCB, so will presume that it uses the CPC's clock

	// no pass-through seen on remake PCBs, unknown if actual hardware had a pass-through port or not
MACHINE_CONFIG_END


<<<<<<< HEAD
machine_config_constructor cpc_pds_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( cpc_pds );
}


=======
>>>>>>> upstream/master
//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

<<<<<<< HEAD
cpc_pds_device::cpc_pds_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, CPC_PDS, "Programmers Development System (CPC Target)", tag, owner, clock, "cpc_pds", __FILE__),
	device_cpc_expansion_card_interface(mconfig, *this), m_slot(nullptr),
=======
cpc_pds_device::cpc_pds_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, CPC_PDS, tag, owner, clock),
	device_cpc_expansion_card_interface(mconfig, *this),
	m_slot(nullptr),
>>>>>>> upstream/master
	m_pio(*this,"pio")
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void cpc_pds_device::device_start()
{
	device_t* cpu = machine().device("maincpu");
	address_space& space = cpu->memory().space(AS_IO);
	m_slot = dynamic_cast<cpc_expansion_slot_device *>(owner());

<<<<<<< HEAD
	space.install_readwrite_handler(0xfbec,0xfbef,0,0,read8_delegate(FUNC(cpc_pds_device::pio_r),this),write8_delegate(FUNC(cpc_pds_device::pio_w),this));
=======
	space.install_readwrite_handler(0xfbec,0xfbef,read8_delegate(FUNC(cpc_pds_device::pio_r),this),write8_delegate(FUNC(cpc_pds_device::pio_w),this));
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void cpc_pds_device::device_reset()
{
	// TODO
}


READ8_MEMBER(cpc_pds_device::pio_r)
{
	return m_pio->read(space,offset);
}

WRITE8_MEMBER(cpc_pds_device::pio_w)
{
	m_pio->write(space,offset,data);
}
