// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore VIC-1111 16K RAM Expansion Cartridge emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "vic1111.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type VIC1111 = &device_creator<vic1111_device>;
=======
DEFINE_DEVICE_TYPE(VIC1111, vic1111_device, "vic1111", "VIC-1111 16K RAM Expansion")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  vic1111_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
vic1111_device::vic1111_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, VIC1111, "VIC1111", tag, owner, clock, "vic1111", __FILE__),
		device_vic20_expansion_card_interface(mconfig, *this),
		m_ram(*this, "ram")
=======
vic1111_device::vic1111_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, VIC1111, tag, owner, clock)
	, device_vic20_expansion_card_interface(mconfig, *this)
	, m_ram(*this, "ram")
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void vic1111_device::device_start()
{
	// allocate memory
	m_ram.allocate(0x4000);
}


//-------------------------------------------------
//  vic20_cd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 vic1111_device::vic20_cd_r(address_space &space, offs_t offset, UINT8 data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3)
=======
uint8_t vic1111_device::vic20_cd_r(address_space &space, offs_t offset, uint8_t data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3)
>>>>>>> upstream/master
{
	if (!blk1)
	{
		data = m_ram[offset];
	}
	else if (!blk2)
	{
		data = m_ram[0x2000 + offset];
	}

	return data;
}


//-------------------------------------------------
//  vic20_cd_w - cartridge data write
//-------------------------------------------------

<<<<<<< HEAD
void vic1111_device::vic20_cd_w(address_space &space, offs_t offset, UINT8 data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3)
=======
void vic1111_device::vic20_cd_w(address_space &space, offs_t offset, uint8_t data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3)
>>>>>>> upstream/master
{
	if (!blk1)
	{
		m_ram[offset] = data;
	}
	else if (!blk2)
	{
		m_ram[0x2000 + offset] = data;
	}
}
