// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    VideoBrain Standard 2K/4K cartridge emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "std.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type VB_STD = &device_creator<videobrain_standard_cartridge_device>;
=======
DEFINE_DEVICE_TYPE(VB_STD, videobrain_standard_cartridge_device, "vb_std", "VideoBrain standard cartridge")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  videobrain_standard_cartridge_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
videobrain_standard_cartridge_device::videobrain_standard_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, VB_STD, "VideoBrain standard cartridge", tag, owner, clock, "vb_std", __FILE__),
=======
videobrain_standard_cartridge_device::videobrain_standard_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, VB_STD, tag, owner, clock),
>>>>>>> upstream/master
	device_videobrain_expansion_card_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void videobrain_standard_cartridge_device::device_start()
{
}


//-------------------------------------------------
//  videobrain_bo_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 videobrain_standard_cartridge_device::videobrain_bo_r(address_space &space, offs_t offset, int cs1, int cs2)
{
	UINT8 data = 0;
=======
uint8_t videobrain_standard_cartridge_device::videobrain_bo_r(address_space &space, offs_t offset, int cs1, int cs2)
{
	uint8_t data = 0;
>>>>>>> upstream/master

	if (!cs1)
	{
		data = m_rom[offset & m_rom_mask];
	}
	else if (!cs2)
	{
		data = m_rom[offset & m_rom_mask];
	}
	return data;
}
