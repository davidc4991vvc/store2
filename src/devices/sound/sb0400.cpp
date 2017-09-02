// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#include "sb0400.h"

const device_type SB0400 = &device_creator<sb0400_device>;
=======
#include "emu.h"
#include "sb0400.h"

DEFINE_DEVICE_TYPE(SB0400, sb0400_device, "sb0400", "Creative Labs SB0400 Audigy2 Value")
>>>>>>> upstream/master

DEVICE_ADDRESS_MAP_START(map, 32, sb0400_device)
ADDRESS_MAP_END

<<<<<<< HEAD
sb0400_device::sb0400_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: pci_device(mconfig, SB0400, "Creative Labs SB0400 Audigy2 Value", tag, owner, clock, "sb0400", __FILE__)
=======
sb0400_device::sb0400_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: pci_device(mconfig, SB0400, tag, owner, clock)
>>>>>>> upstream/master
{
}

void sb0400_device::device_start()
{
	pci_device::device_start();
	add_map(64, M_IO, FUNC(sb0400_device::map));
}

void sb0400_device::device_reset()
{
	pci_device::device_reset();
}
