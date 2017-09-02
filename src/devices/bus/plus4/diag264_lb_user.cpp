// license:BSD-3-Clause
// copyright-holders:smf
/**********************************************************************

    Diag264 User Port Loop Back Connector emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "diag264_lb_user.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type DIAG264_USER_PORT_LOOPBACK = &device_creator<diag264_user_port_loopback_device>;
=======
DEFINE_DEVICE_TYPE(DIAG264_USER_PORT_LOOPBACK, diag264_user_port_loopback_device, "diag264_user_port_loopback", "Diag264 User Port Loopback")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  diag264_user_port_loopback_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
diag264_user_port_loopback_device::diag264_user_port_loopback_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, DIAG264_USER_PORT_LOOPBACK, "Diag264 User Port Loopback", tag, owner, clock, "diag264_user_port_loopback", __FILE__),
	device_pet_user_port_interface(mconfig, *this)
=======
diag264_user_port_loopback_device::diag264_user_port_loopback_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, DIAG264_USER_PORT_LOOPBACK, tag, owner, clock)
	, device_pet_user_port_interface(mconfig, *this)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void diag264_user_port_loopback_device::device_start()
{
}
