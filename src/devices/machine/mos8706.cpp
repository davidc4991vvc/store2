// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    MOS 8706 Speech Glue Logic ASIC emulation

**********************************************************************/

<<<<<<< HEAD
#include "mos8706.h"



//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define LOG 0
=======
#include "emu.h"
#include "mos8706.h"

//#define VERBOSE 1
#include "logmacro.h"
>>>>>>> upstream/master



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

// device type definition
<<<<<<< HEAD
const device_type MOS8706 = &device_creator<mos8706_device>;
=======
DEFINE_DEVICE_TYPE(MOS8706, mos8706_device, "mos8706", "MOS 8706")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  mos8706_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
mos8706_device::mos8706_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MOS8706, "MOS8706", tag, owner, clock, "mos8706", __FILE__)
=======
mos8706_device::mos8706_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MOS8706, tag, owner, clock)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void mos8706_device::device_start()
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void mos8706_device::device_reset()
{
}


//-------------------------------------------------
//  read -
//-------------------------------------------------

READ8_MEMBER( mos8706_device::read )
{
	return 0;
}


//-------------------------------------------------
//  write -
//-------------------------------------------------

WRITE8_MEMBER( mos8706_device::write )
{
}
