// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    MOS Technology 6702 Mystery Device emulation

**********************************************************************/

<<<<<<< HEAD
#include "mos6702.h"



//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define LOG 0
=======
#include "emu.h"
#include "mos6702.h"

//#define VERBOSE 1
#include "logmacro.h"
>>>>>>> upstream/master



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type MOS6702 = &device_creator<mos6702_device>;
=======
DEFINE_DEVICE_TYPE(MOS6702, mos6702_device, "mos6702", "MOS 6702")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  mos6702_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
mos6702_device::mos6702_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MOS6702, "MOS6702", tag, owner, clock, "mos6702", __FILE__)
=======
mos6702_device::mos6702_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MOS6702, tag, owner, clock)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void mos6702_device::device_start()
{
}


//-------------------------------------------------
//  read -
//-------------------------------------------------

READ8_MEMBER( mos6702_device::read )
{
	return 0;
}


//-------------------------------------------------
//  write -
//-------------------------------------------------

WRITE8_MEMBER( mos6702_device::write )
{
}
