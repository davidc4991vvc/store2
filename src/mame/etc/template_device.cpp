// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Angelo Salese
/***************************************************************************

Template for skeleton device
=======
// copyright-holders:<author_name>
/***************************************************************************

Template for squeleton device
>>>>>>> upstream/master

***************************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "machine/xxx.h"
=======
#include "xxx.h"
>>>>>>> upstream/master



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

// device type definition
<<<<<<< HEAD
const device_type XXX = &device_creator<xxx_device>;
=======
DEFINE_DEVICE_TYPE(XXX, xxx_device, "xxx", "XXX Device")
>>>>>>> upstream/master


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  xxx_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
xxx_device::xxx_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, XXX, "xxx_longname", tag, owner, clock, "xxx", __FILE__)
=======
xxx_device::xxx_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, XXX, tag, owner, clock)
>>>>>>> upstream/master
{
}


<<<<<<< HEAD
//-------------------------------------------------
//  device_validity_check - perform validity checks
//  on this device
//-------------------------------------------------

void xxx_device::device_validity_check(validity_checker &valid) const
{
}
=======


//-------------------------------------------------
//  device_add_mconfig - device-specific machine
//  configuration addiitons
//-------------------------------------------------

MACHINE_CONFIG_MEMBER(xxx_device::device_add_mconfig)
	//MCFG_CPU_ADD(...)
MACHINE_CONFIG_END
>>>>>>> upstream/master


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void xxx_device::device_start()
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void xxx_device::device_reset()
{
}


//**************************************************************************
//  READ/WRITE HANDLERS
//**************************************************************************

READ8_MEMBER( xxx_device::read )
{
	return 0;
}

WRITE8_MEMBER( xxx_device::write )
{
}
