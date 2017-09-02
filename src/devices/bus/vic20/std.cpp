// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore VIC-20 Standard 8K/16K ROM Cartridge emulation

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
const device_type VIC20_STD = &device_creator<vic20_standard_cartridge_device>;
=======
DEFINE_DEVICE_TYPE(VIC20_STD, vic20_standard_cartridge_device, "vic20_standard", "VIC-20 Standard Cartridge")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  vic20_standard_cartridge_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
vic20_standard_cartridge_device::vic20_standard_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, VIC20_STD, "VIC-20 Standard Cartridge", tag, owner, clock, "vic20_standard", __FILE__),
		device_vic20_expansion_card_interface(mconfig, *this)
=======
vic20_standard_cartridge_device::vic20_standard_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, VIC20_STD, tag, owner, clock), device_vic20_expansion_card_interface(mconfig, *this)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void vic20_standard_cartridge_device::device_start()
{
}


//-------------------------------------------------
//  vic20_cd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 vic20_standard_cartridge_device::vic20_cd_r(address_space &space, offs_t offset, UINT8 data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3)
{
	if (!blk1 && (m_blk1 != NULL))
	{
		data = m_blk1[offset];
	}
	else if (!blk2 && (m_blk2 != NULL))
	{
		data = m_blk2[offset];
	}
	else if (!blk3 && (m_blk3 != NULL))
	{
		data = m_blk3[offset];
	}
	else if (!blk5 && (m_blk5 != NULL))
=======
uint8_t vic20_standard_cartridge_device::vic20_cd_r(address_space &space, offs_t offset, uint8_t data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3)
{
	if (!blk1 && (m_blk1 != nullptr))
	{
		data = m_blk1[offset];
	}
	else if (!blk2 && (m_blk2 != nullptr))
	{
		data = m_blk2[offset];
	}
	else if (!blk3 && (m_blk3 != nullptr))
	{
		data = m_blk3[offset];
	}
	else if (!blk5 && (m_blk5 != nullptr))
>>>>>>> upstream/master
	{
		data = m_blk5[offset];
	}

	return data;
}
