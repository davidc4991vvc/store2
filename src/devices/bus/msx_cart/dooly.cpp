// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
#include "emu.h"
#include "dooly.h"


<<<<<<< HEAD
const device_type MSX_CART_DOOLY = &device_creator<msx_cart_dooly>;


msx_cart_dooly::msx_cart_dooly(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MSX_CART_DOOLY, "MSX Cartridge - Dooly", tag, owner, clock, "msx_cart_dooly", __FILE__)
=======
DEFINE_DEVICE_TYPE(MSX_CART_DOOLY, msx_cart_dooly_device, "msx_cart_dooly", "MSX Cartridge - Dooly")


msx_cart_dooly_device::msx_cart_dooly_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MSX_CART_DOOLY, tag, owner, clock)
>>>>>>> upstream/master
	, msx_cart_interface(mconfig, *this)
	, m_prot(0)
{
}


<<<<<<< HEAD
void msx_cart_dooly::device_start()
=======
void msx_cart_dooly_device::device_start()
>>>>>>> upstream/master
{
	save_item(NAME(m_prot));
}


<<<<<<< HEAD
void msx_cart_dooly::device_reset()
=======
void msx_cart_dooly_device::device_reset()
>>>>>>> upstream/master
{
	m_prot = 0;
}


<<<<<<< HEAD
void msx_cart_dooly::initialize_cartridge()
=======
void msx_cart_dooly_device::initialize_cartridge()
>>>>>>> upstream/master
{
	if (get_rom_size() != 0x8000)
	{
		fatalerror("dooly: Invalid ROM size\n");
	}
}


<<<<<<< HEAD
READ8_MEMBER(msx_cart_dooly::read_cart)
{
	if (offset >= 0x4000 && offset < 0xc000)
	{
		UINT8 data = get_rom_base()[offset - 0x4000];
=======
READ8_MEMBER(msx_cart_dooly_device::read_cart)
{
	if (offset >= 0x4000 && offset < 0xc000)
	{
		uint8_t data = get_rom_base()[offset - 0x4000];
>>>>>>> upstream/master

		switch (m_prot)
		{
			case 0x04:
				data = BITSWAP8(data, 7, 6, 5, 4, 3, 1, 0, 2);
				break;
		}
		return data;
	}
	return 0xff;
}


<<<<<<< HEAD
WRITE8_MEMBER(msx_cart_dooly::write_cart)
=======
WRITE8_MEMBER(msx_cart_dooly_device::write_cart)
>>>>>>> upstream/master
{
	if (offset >= 0x4000 && offset < 0xc000)
	{
		m_prot = data & 0x07;
		if (m_prot != 0 && m_prot != 4)
		{
<<<<<<< HEAD
			logerror("msx_cart_dooly: unhandled write %02x to %04x\n", data, offset);
=======
			logerror("msx_cart_dooly_device: unhandled write %02x to %04x\n", data, offset);
>>>>>>> upstream/master
		}
	}
}
