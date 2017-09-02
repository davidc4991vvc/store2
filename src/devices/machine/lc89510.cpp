// license:BSD-3-Clause
// copyright-holders:David Haywood
/* LC89510 CD Controller
<<<<<<< HEAD
 based off old NeoCD emulator code, adapted to SegaCD, needs reworking to work with NeoCD again
=======
 completely empty placeholder - should be populated or removed
>>>>>>> upstream/master

*/


#include "emu.h"
#include "lc89510.h"

<<<<<<< HEAD
const device_type LC89510 = &device_creator<lc89510_device>;

lc89510_device::lc89510_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, LC89510, "lc89510_device", tag, owner, clock, "lc89510", __FILE__)
=======
DEFINE_DEVICE_TYPE(LC89510, lc89510_device, "lc89510", "LC89510 CD Controller")

lc89510_device::lc89510_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, LC89510, tag, owner, clock)
>>>>>>> upstream/master
{
}


void lc89510_device::device_start()
{
}

void lc89510_device::device_reset()
{
}
