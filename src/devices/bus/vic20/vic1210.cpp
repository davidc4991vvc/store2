// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore VIC-1210 3K RAM Expansion Cartridge emulation
    Commodore VIC-1211A Super Expander with 3K RAM Cartridge emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "vic1210.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type VIC1210 = &device_creator<vic1210_device>;
=======
DEFINE_DEVICE_TYPE(VIC1210, vic1210_device, "vic1210", "VIC-1210 3K RAM Expansion")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  vic1210_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
vic1210_device::vic1210_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, VIC1210, "VIC1210", tag, owner, clock, "vic1210", __FILE__),
		device_vic20_expansion_card_interface(mconfig, *this),
		m_ram(*this, "ram")
=======
vic1210_device::vic1210_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, VIC1210, tag, owner, clock)
	, device_vic20_expansion_card_interface(mconfig, *this)
	, m_ram(*this, "ram")
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void vic1210_device::device_start()
{
	// allocate memory
	m_ram.allocate(0xc00);
}


//-------------------------------------------------
//  vic20_cd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 vic1210_device::vic20_cd_r(address_space &space, offs_t offset, UINT8 data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3)
=======
uint8_t vic1210_device::vic20_cd_r(address_space &space, offs_t offset, uint8_t data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3)
>>>>>>> upstream/master
{
	if (!ram1 || !ram2 || !ram3)
	{
		data = m_ram[offset & 0xbff];
	}
	else if (!blk5 && m_blk5)
	{
		data = m_blk5[offset & 0xfff];
	}

	return data;
}


//-------------------------------------------------
//  vic20_cd_w - cartridge data write
//-------------------------------------------------

<<<<<<< HEAD
void vic1210_device::vic20_cd_w(address_space &space, offs_t offset, UINT8 data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3)
=======
void vic1210_device::vic20_cd_w(address_space &space, offs_t offset, uint8_t data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3)
>>>>>>> upstream/master
{
	if (!ram1 || !ram2 || !ram3)
	{
		m_ram[offset & 0xbff] = data;
	}
}
