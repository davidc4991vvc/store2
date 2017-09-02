// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    VideoBrain Timeshare cartridge emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "timeshare.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type VB_TIMESHARE = &device_creator<videobrain_timeshare_cartridge_device>;
=======
DEFINE_DEVICE_TYPE(VB_TIMESHARE, videobrain_timeshare_cartridge_device, "vb_timeshare", "VideoBrain Timeshare cartridge")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  videobrain_timeshare_cartridge_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
videobrain_timeshare_cartridge_device::videobrain_timeshare_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, VB_TIMESHARE, "VideoBrain Timeshare cartridge", tag, owner, clock, "vb_timeshare", __FILE__),
=======
videobrain_timeshare_cartridge_device::videobrain_timeshare_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, VB_TIMESHARE, tag, owner, clock),
>>>>>>> upstream/master
	device_videobrain_expansion_card_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void videobrain_timeshare_cartridge_device::device_start()
{
}


//-------------------------------------------------
//  videobrain_bo_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 videobrain_timeshare_cartridge_device::videobrain_bo_r(address_space &space, offs_t offset, int cs1, int cs2)
{
	UINT8 data = 0;
=======
uint8_t videobrain_timeshare_cartridge_device::videobrain_bo_r(address_space &space, offs_t offset, int cs1, int cs2)
{
	uint8_t data = 0;
>>>>>>> upstream/master

	if (!cs1)
	{
		data = m_rom[offset & m_rom_mask];
	}
	else if (!cs2)
	{
		data = m_ram[offset & m_ram_mask];
	}
	return data;
}


//-------------------------------------------------
//  videobrain_bo_w - cartridge data write
//-------------------------------------------------

<<<<<<< HEAD
void videobrain_timeshare_cartridge_device::videobrain_bo_w(address_space &space, offs_t offset, UINT8 data, int cs1, int cs2)
=======
void videobrain_timeshare_cartridge_device::videobrain_bo_w(address_space &space, offs_t offset, uint8_t data, int cs1, int cs2)
>>>>>>> upstream/master
{
	if (!cs2)
	{
		m_ram[offset & m_ram_mask] = data;
	}
}
