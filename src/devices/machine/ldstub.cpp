// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/*************************************************************************

    ldstub.c

    Laserdisc player stubs.

*************************************************************************/

#include "emu.h"
#include "ldstub.h"


//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

// device type definition
<<<<<<< HEAD
const device_type SONY_LDP1450 = &device_creator<sony_ldp1450_device>;
const device_type PIONEER_PR7820 = &device_creator<pioneer_pr7820_device>;
const device_type PHILLIPS_22VP932 = &device_creator<phillips_22vp932_device>;
=======
DEFINE_DEVICE_TYPE(PIONEER_PR7820,   pioneer_pr7820_device,   "pr7820",  "Pioneer PR-7820")
DEFINE_DEVICE_TYPE(PHILLIPS_22VP932, phillips_22vp932_device, "22vp932", "Phillips 22VP932")


pioneer_pr7820_device::pioneer_pr7820_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: laserdisc_device(mconfig, PIONEER_PR7820, tag, owner, clock)
{
}


phillips_22vp932_device::phillips_22vp932_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: laserdisc_device(mconfig, PHILLIPS_22VP932, tag, owner, clock)
{
}
>>>>>>> upstream/master
