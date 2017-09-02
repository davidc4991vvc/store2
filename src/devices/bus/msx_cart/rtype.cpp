// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
#include "emu.h"
#include "rtype.h"

<<<<<<< HEAD
const device_type MSX_CART_RTYPE = &device_creator<msx_cart_rtype>;


msx_cart_rtype::msx_cart_rtype(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MSX_CART_RTYPE, "MSX Cartridge - R-Type", tag, owner, clock, "msx_cart_rtype", __FILE__)
	, msx_cart_interface(mconfig, *this)
	, m_selected_bank(0)
{
	for (int i = 0; i < 2; i++)
	{
		m_bank_base[i] = NULL;
=======
DEFINE_DEVICE_TYPE(MSX_CART_RTYPE, msx_cart_rtype_device, "msx_cart_rtype", "MSX Cartridge - R-Type")


msx_cart_rtype_device::msx_cart_rtype_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MSX_CART_RTYPE, tag, owner, clock)
	, msx_cart_interface(mconfig, *this)
	, m_selected_bank(0)
{
	for (auto & elem : m_bank_base)
	{
		elem = nullptr;
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
void msx_cart_rtype::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_rtype::restore_banks), this));
}


void msx_cart_rtype::restore_banks()
=======
void msx_cart_rtype_device::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_rtype_device::restore_banks), this));
}


void msx_cart_rtype_device::restore_banks()
>>>>>>> upstream/master
{
	m_bank_base[0] = get_rom_base() + 15 * 0x4000;
	if (m_selected_bank & 0x10)
	{
		m_selected_bank &= 0x17;
	}
	m_bank_base[1] = get_rom_base() + m_selected_bank * 0x4000;
}


<<<<<<< HEAD
void msx_cart_rtype::device_reset()
=======
void msx_cart_rtype_device::device_reset()
>>>>>>> upstream/master
{
	m_selected_bank = 15;
}


<<<<<<< HEAD
void msx_cart_rtype::initialize_cartridge()
=======
void msx_cart_rtype_device::initialize_cartridge()
>>>>>>> upstream/master
{
	if ( get_rom_size() != 0x80000 && get_rom_size() != 0x60000 )
	{
		fatalerror("rtype: Invalid ROM size\n");
	}

	restore_banks();
}


<<<<<<< HEAD
READ8_MEMBER(msx_cart_rtype::read_cart)
=======
READ8_MEMBER(msx_cart_rtype_device::read_cart)
>>>>>>> upstream/master
{
	if (offset >= 0x4000 && offset < 0xc000)
	{
		return m_bank_base[offset >> 15][offset & 0x3fff];
	}
	return 0xff;
}


<<<<<<< HEAD
WRITE8_MEMBER(msx_cart_rtype::write_cart)
=======
WRITE8_MEMBER(msx_cart_rtype_device::write_cart)
>>>>>>> upstream/master
{
	if (offset >= 0x7000 && offset < 0x8000)
	{
		m_selected_bank = data & 0x1f;
		if (m_selected_bank & 0x10)
		{
			m_selected_bank &= 0x17;
		}
		m_bank_base[1] = get_rom_base() + m_selected_bank * 0x4000;
	}
}
