// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    ABC 80 16 KB RAM expansion card emulation

*********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "ram.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type ABC80_16KB_RAM_CARD = &device_creator<abc80_16kb_ram_card_t>;
=======
DEFINE_DEVICE_TYPE(ABC80_16KB_RAM_CARD, abc80_16kb_ram_card_device, "abc80_16kb", "ABC 80 16KB RAM card")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  abc80_16kb_ram_card_t - constructor
//-------------------------------------------------

abc80_16kb_ram_card_t::abc80_16kb_ram_card_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, ABC80_16KB_RAM_CARD, "ABC 80 16KB RAM card", tag, owner, clock, "abc80_16kb", __FILE__),
=======
//  abc80_16kb_ram_card_device - constructor
//-------------------------------------------------

abc80_16kb_ram_card_device::abc80_16kb_ram_card_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, ABC80_16KB_RAM_CARD, tag, owner, clock),
>>>>>>> upstream/master
	device_abcbus_card_interface(mconfig, *this),
	m_ram(*this, "ram")
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void abc80_16kb_ram_card_t::device_start()
=======
void abc80_16kb_ram_card_device::device_start()
>>>>>>> upstream/master
{
	m_ram.allocate(0x4000);
}



//**************************************************************************
//  ABC BUS INTERFACE
//**************************************************************************

//-------------------------------------------------
//  abcbus_xmemfl -
//-------------------------------------------------

<<<<<<< HEAD
UINT8 abc80_16kb_ram_card_t::abcbus_xmemfl(offs_t offset)
{
	UINT8 data = 0xff;
=======
uint8_t abc80_16kb_ram_card_device::abcbus_xmemfl(offs_t offset)
{
	uint8_t data = 0xff;
>>>>>>> upstream/master

	if (offset >= 0x8000 && offset < 0xc000)
	{
		data = m_ram[offset & 0x3fff];
	}

	return data;
}


//-------------------------------------------------
//  abcbus_xmemw -
//-------------------------------------------------

<<<<<<< HEAD
void abc80_16kb_ram_card_t::abcbus_xmemw(offs_t offset, UINT8 data)
=======
void abc80_16kb_ram_card_device::abcbus_xmemw(offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	if (offset >= 0x8000 && offset < 0xc000)
	{
		m_ram[offset & 0x3fff] = data;
	}
}
