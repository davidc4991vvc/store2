// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
#include "emu.h"
#include "halnote.h"


<<<<<<< HEAD
const device_type MSX_CART_HALNOTE = &device_creator<msx_cart_halnote>;


msx_cart_halnote::msx_cart_halnote(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MSX_CART_HALNOTE, "MSX Cartridge - Halnote", tag, owner, clock, "msx_cart_halnote", __FILE__)
	, msx_cart_interface(mconfig, *this)
{
	for (int i = 0; i < 8; i++)
	{
		m_selected_bank[i] = 0;
		m_bank_base[i] = NULL;
	}
}


void msx_cart_halnote::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_halnote::restore_banks), this));
}


void msx_cart_halnote::map_bank(int bank)
=======
DEFINE_DEVICE_TYPE(MSX_CART_HALNOTE, msx_cart_halnote_device, "msx_cart_halnote", "MSX Cartridge - Halnote")


msx_cart_halnote_device::msx_cart_halnote_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MSX_CART_HALNOTE, tag, owner, clock)
	, msx_cart_interface(mconfig, *this)
	, m_selected_bank{ 0, 0, 0, 0, 0, 0, 0, 0 }
	, m_bank_base{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr }
{
}


void msx_cart_halnote_device::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_halnote_device::restore_banks), this));
}


void msx_cart_halnote_device::map_bank(int bank)
>>>>>>> upstream/master
{
	if (bank < 2)
	{
		return;
	}

	// Special banks
	if (bank == 6 || bank == 7)
	{
		m_bank_base[bank] = get_rom_base() + 0x80000 + (m_selected_bank[bank] * 0x800);
		return;
	}

	m_bank_base[bank] = get_rom_base() + ((m_selected_bank[bank] * 0x2000) & 0xFFFFF);
	if (bank == 2)
	{
		if (m_selected_bank[bank] & 0x80)
		{
			m_bank_base[0] = get_sram_base();
			m_bank_base[1] = get_sram_base() + 0x2000;
		}
		else
		{
<<<<<<< HEAD
			m_bank_base[0] = NULL;
			m_bank_base[1] = NULL;
=======
			m_bank_base[0] = nullptr;
			m_bank_base[1] = nullptr;
>>>>>>> upstream/master
		}
	}
}


<<<<<<< HEAD
void msx_cart_halnote::restore_banks()
=======
void msx_cart_halnote_device::restore_banks()
>>>>>>> upstream/master
{
	for (int i = 0; i < 8; i++)
	{
		map_bank(i);
	}
}


<<<<<<< HEAD
void msx_cart_halnote::device_reset()
{
	for (int i = 0; i < 8; i++)
	{
		m_selected_bank[i] = 0;
=======
void msx_cart_halnote_device::device_reset()
{
	for (auto & elem : m_selected_bank)
	{
		elem = 0;
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
void msx_cart_halnote::initialize_cartridge()
=======
void msx_cart_halnote_device::initialize_cartridge()
>>>>>>> upstream/master
{
	if (get_rom_size() != 0x100000)
	{
		fatalerror("halnote: Invalid ROM size\n");
	}

	restore_banks();
}


<<<<<<< HEAD
READ8_MEMBER(msx_cart_halnote::read_cart)
=======
READ8_MEMBER(msx_cart_halnote_device::read_cart)
>>>>>>> upstream/master
{
	if (offset >= 0xc000)
	{
		return 0xFF;
	}

	if ((offset & 0xf000) == 0x7000 && (m_selected_bank[3] & 0x80))
	{
		return m_bank_base[6 + ((offset >> 11) & 0x01)][offset & 0x7ff];
	}

<<<<<<< HEAD
	const UINT8 *mem = m_bank_base[offset >> 13];
=======
	const uint8_t *mem = m_bank_base[offset >> 13];
>>>>>>> upstream/master

	if (mem)
	{
		return mem[offset & 0x1fff];
	}
	return 0xff;
}


<<<<<<< HEAD
WRITE8_MEMBER(msx_cart_halnote::write_cart)
{
	if (offset < 0x4000)
	{
		if (m_bank_base[0] != NULL)
=======
WRITE8_MEMBER(msx_cart_halnote_device::write_cart)
{
	if (offset < 0x4000)
	{
		if (m_bank_base[0] != nullptr)
>>>>>>> upstream/master
		{
			m_sram[offset & 0x3fff] = data;
			return;
		}
	}

	switch (offset)
	{
		case 0x4FFF:
			m_selected_bank[2] = data;
			map_bank(2);
			break;

		case 0x6FFF:     // 6000-7FFF
			m_selected_bank[3] = data;
			map_bank(3);
			break;

		case 0x77FF:
			m_selected_bank[6] = data;
			map_bank(6);
			break;

		case 0x7FFF:
			m_selected_bank[7] = data;
			map_bank(7);
			break;

		case 0x8FFF:
			m_selected_bank[4] = data;
			map_bank(4);
			break;

		case 0xAFFF:
			m_selected_bank[5] = data;
			map_bank(5);
			break;

		default:
<<<<<<< HEAD
			logerror("msx_cart_halnote: Unhandled write %02x to %04x\n", data, offset);
=======
			logerror("msx_cart_halnote_device: Unhandled write %02x to %04x\n", data, offset);
>>>>>>> upstream/master
			break;
	}
}
