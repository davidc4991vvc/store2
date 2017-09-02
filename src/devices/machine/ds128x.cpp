// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "ds128x.h"

/// TODO: Only DV2/DV1/DV0 == 0/1/0 is supported as the chip only has a 15 stage divider and not 22.

<<<<<<< HEAD
const device_type DS12885 = &device_creator<ds12885_device>;
=======
DEFINE_DEVICE_TYPE(DS12885, ds12885_device, "ds12885", "DS12885 RTC/NVRAM")
>>>>>>> upstream/master

//-------------------------------------------------
//  ds12885_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
ds12885_device::ds12885_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: mc146818_device(mconfig, DS12885, "DS12885", tag, owner, clock, "ds12885", __FILE__)
=======
ds12885_device::ds12885_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: mc146818_device(mconfig, DS12885, tag, owner, clock)
>>>>>>> upstream/master
{
}
