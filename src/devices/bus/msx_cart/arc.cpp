// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
#include "emu.h"
#include "arc.h"


<<<<<<< HEAD
const device_type MSX_CART_ARC = &device_creator<msx_cart_arc>;


msx_cart_arc::msx_cart_arc(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MSX_CART_ARC, "MSX Cartridge - Arc", tag, owner, clock, "msx_cart_arc", __FILE__)
=======
DEFINE_DEVICE_TYPE(MSX_CART_ARC, msx_cart_arc_device, "msx_cart_arc", "MSX Cartridge - Arc")


msx_cart_arc_device::msx_cart_arc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MSX_CART_ARC, tag, owner, clock)
>>>>>>> upstream/master
	, msx_cart_interface(mconfig, *this)
	, m_7f(0)
{
}


<<<<<<< HEAD
void msx_cart_arc::device_start()
{
	// Install IO read/write handlers
	address_space &space = machine().device<cpu_device>("maincpu")->space(AS_IO);
	space.install_write_handler(0x7f, 0x7f, write8_delegate(FUNC(msx_cart_arc::io_7f_w), this));
	space.install_read_handler(0x7f, 0x7f, read8_delegate(FUNC(msx_cart_arc::io_7f_r), this));
}


void msx_cart_arc::device_reset()
=======
void msx_cart_arc_device::device_start()
{
	// Install IO read/write handlers
	address_space &space = machine().device<cpu_device>("maincpu")->space(AS_IO);
	space.install_write_handler(0x7f, 0x7f, write8_delegate(FUNC(msx_cart_arc_device::io_7f_w), this));
	space.install_read_handler(0x7f, 0x7f, read8_delegate(FUNC(msx_cart_arc_device::io_7f_r), this));
}


void msx_cart_arc_device::device_reset()
>>>>>>> upstream/master
{
	m_7f = 0;
}


<<<<<<< HEAD
void msx_cart_arc::initialize_cartridge()
=======
void msx_cart_arc_device::initialize_cartridge()
>>>>>>> upstream/master
{
	if (get_rom_size() != 0x8000)
	{
		fatalerror("arc: Invalid ROM size\n");
	}
}


<<<<<<< HEAD
READ8_MEMBER(msx_cart_arc::read_cart)
=======
READ8_MEMBER(msx_cart_arc_device::read_cart)
>>>>>>> upstream/master
{
	if (offset >= 0x4000 && offset < 0xc000)
	{
		return get_rom_base()[offset - 0x4000];
	}
	return 0xff;
}


<<<<<<< HEAD
WRITE8_MEMBER(msx_cart_arc::io_7f_w)
=======
WRITE8_MEMBER(msx_cart_arc_device::io_7f_w)
>>>>>>> upstream/master
{
	if (data == 0x35)
	{
		m_7f++;
	}
}


<<<<<<< HEAD
READ8_MEMBER(msx_cart_arc::io_7f_r)
=======
READ8_MEMBER(msx_cart_arc_device::io_7f_r)
>>>>>>> upstream/master
{
	return ((m_7f & 0x03) == 0x03) ? 0xda : 0xff;
}
