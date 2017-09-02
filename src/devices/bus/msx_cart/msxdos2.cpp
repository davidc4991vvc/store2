// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
#include "emu.h"
#include "msxdos2.h"

<<<<<<< HEAD
const device_type MSX_CART_MSXDOS2 = &device_creator<msx_cart_msxdos2>;


msx_cart_msxdos2::msx_cart_msxdos2(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MSX_CART_MSXDOS2, "MSX Cartridge - MSXDOS2", tag, owner, clock, "msx_cart_msxdos2", __FILE__)
	, msx_cart_interface(mconfig, *this)
	, m_selected_bank(0)
	, m_bank_base(NULL)
=======
DEFINE_DEVICE_TYPE(MSX_CART_MSXDOS2, msx_cart_msxdos2_device, "msx_cart_msxdos2", "MSX Cartridge - MSXDOS2")


msx_cart_msxdos2_device::msx_cart_msxdos2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MSX_CART_MSXDOS2, tag, owner, clock)
	, msx_cart_interface(mconfig, *this)
	, m_selected_bank(0)
	, m_bank_base(nullptr)
>>>>>>> upstream/master
{
}


<<<<<<< HEAD
void msx_cart_msxdos2::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_msxdos2::restore_banks), this));
}


void msx_cart_msxdos2::restore_banks()
=======
void msx_cart_msxdos2_device::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_msxdos2_device::restore_banks), this));
}


void msx_cart_msxdos2_device::restore_banks()
>>>>>>> upstream/master
{
	m_bank_base = get_rom_base() + ( m_selected_bank & 0x03 ) * 0x4000;
}


<<<<<<< HEAD
void msx_cart_msxdos2::device_reset()
=======
void msx_cart_msxdos2_device::device_reset()
>>>>>>> upstream/master
{
	m_selected_bank = 0;
}


<<<<<<< HEAD
void msx_cart_msxdos2::initialize_cartridge()
=======
void msx_cart_msxdos2_device::initialize_cartridge()
>>>>>>> upstream/master
{
	if (get_rom_size() != 0x10000)
	{
		fatalerror("msxdos2: Invalid ROM size\n");
	}

	restore_banks();
}


<<<<<<< HEAD
READ8_MEMBER(msx_cart_msxdos2::read_cart)
=======
READ8_MEMBER(msx_cart_msxdos2_device::read_cart)
>>>>>>> upstream/master
{
	if (offset >= 0x4000 && offset < 0x8000)
	{
		return m_bank_base[offset & 0x3fff];
	}

	return 0xff;
}


<<<<<<< HEAD
WRITE8_MEMBER(msx_cart_msxdos2::write_cart)
=======
WRITE8_MEMBER(msx_cart_msxdos2_device::write_cart)
>>>>>>> upstream/master
{
	if (offset == 0x6000)
	{
		m_selected_bank = data;
		restore_banks();
	}
}
