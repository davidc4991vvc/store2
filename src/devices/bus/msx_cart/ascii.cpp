// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
#include "emu.h"
#include "ascii.h"


<<<<<<< HEAD
const device_type MSX_CART_ASCII8 = &device_creator<msx_cart_ascii8>;
const device_type MSX_CART_ASCII16 = &device_creator<msx_cart_ascii16>;
const device_type MSX_CART_ASCII8_SRAM = &device_creator<msx_cart_ascii8_sram>;
const device_type MSX_CART_ASCII16_SRAM = &device_creator<msx_cart_ascii16_sram>;
const device_type MSX_CART_MSXWRITE = &device_creator<msx_cart_msxwrite>;


msx_cart_ascii8::msx_cart_ascii8(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MSX_CART_ASCII8, "MSX Cartridge - ASCII8", tag, owner, clock, "msx_cart_ascii8", __FILE__)
=======
DEFINE_DEVICE_TYPE(MSX_CART_ASCII8,       msx_cart_ascii8_device,       "msx_cart_ascii8",       "MSX Cartridge - ASCII8")
DEFINE_DEVICE_TYPE(MSX_CART_ASCII16,      msx_cart_ascii16_device,      "msx_cart_ascii16",      "MSX Cartridge - ASCII16")
DEFINE_DEVICE_TYPE(MSX_CART_ASCII8_SRAM,  msx_cart_ascii8_sram_device,  "msx_cart_ascii8_sram",  "MSX Cartridge - ASCII8 w/SRAM")
DEFINE_DEVICE_TYPE(MSX_CART_ASCII16_SRAM, msx_cart_ascii16_sram_device, "msx_cart_ascii16_sram", "MSX Cartridge - ASCII16 w/SRAM")
DEFINE_DEVICE_TYPE(MSX_CART_MSXWRITE,     msx_cart_msxwrite_device,     "msx_cart_msxwrite",     "MSX Cartridge - MSXWRITE")


msx_cart_ascii8_device::msx_cart_ascii8_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MSX_CART_ASCII8, tag, owner, clock)
>>>>>>> upstream/master
	, msx_cart_interface(mconfig, *this)
	, m_bank_mask(0)
{
	for (int i = 0; i < 4; i++)
	{
		m_selected_bank[i] = 0;
<<<<<<< HEAD
		m_bank_base[i] = NULL;
=======
		m_bank_base[i] = nullptr;
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
void msx_cart_ascii8::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_ascii8::restore_banks), this));
}


void msx_cart_ascii8::restore_banks()
=======
void msx_cart_ascii8_device::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_ascii8_device::restore_banks), this));
}


void msx_cart_ascii8_device::restore_banks()
>>>>>>> upstream/master
{
	for (int i = 0; i < 4; i++)
	{
		m_bank_base[i] = get_rom_base() + (m_selected_bank[i] & m_bank_mask ) * 0x2000;
	}
}


<<<<<<< HEAD
void msx_cart_ascii8::device_reset()
{
	for (int i = 0; i < 4; i++)
	{
		m_selected_bank[i] = 0;
=======
void msx_cart_ascii8_device::device_reset()
{
	for (auto & elem : m_selected_bank)
	{
		elem = 0;
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
void msx_cart_ascii8::initialize_cartridge()
{
	UINT32 size = get_rom_size();
=======
void msx_cart_ascii8_device::initialize_cartridge()
{
	uint32_t size = get_rom_size();
>>>>>>> upstream/master

	if ( size > 256 * 0x2000 )
	{
		fatalerror("ascii8: ROM is too big\n");
	}

<<<<<<< HEAD
	UINT16 banks = size / 0x2000;
=======
	uint16_t banks = size / 0x2000;
>>>>>>> upstream/master

	if (size != banks * 0x2000 || (~(banks - 1) % banks))
	{
		fatalerror("ascii8: Invalid ROM size\n");
	}

	m_bank_mask = banks - 1;

	restore_banks();
}


<<<<<<< HEAD
READ8_MEMBER(msx_cart_ascii8::read_cart)
=======
READ8_MEMBER(msx_cart_ascii8_device::read_cart)
>>>>>>> upstream/master
{
	if ( offset >= 0x4000 && offset < 0xC000 )
	{
		return m_bank_base[(offset - 0x4000) >> 13][offset & 0x1fff];
	}
	return 0xff;
}


<<<<<<< HEAD
WRITE8_MEMBER(msx_cart_ascii8::write_cart)
{
	if (offset >= 0x6000 && offset < 0x8000)
	{
		UINT8 bank = (offset / 0x800) & 0x03;
=======
WRITE8_MEMBER(msx_cart_ascii8_device::write_cart)
{
	if (offset >= 0x6000 && offset < 0x8000)
	{
		uint8_t bank = (offset / 0x800) & 0x03;
>>>>>>> upstream/master

		m_selected_bank[bank] = data;
		m_bank_base[bank] = get_rom_base() + (m_selected_bank[bank] & m_bank_mask ) * 0x2000;
	}
}



<<<<<<< HEAD
msx_cart_ascii16::msx_cart_ascii16(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MSX_CART_ASCII16, "MSX Cartridge - ASCII16", tag, owner, clock, "msx_cart_ascii16", __FILE__)
=======
msx_cart_ascii16_device::msx_cart_ascii16_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MSX_CART_ASCII16, tag, owner, clock)
>>>>>>> upstream/master
	, msx_cart_interface(mconfig, *this)
	, m_bank_mask(0)
{
	for (int i = 0; i < 2; i++)
	{
		m_selected_bank[i] = 0;
<<<<<<< HEAD
		m_bank_base[i] = NULL;
=======
		m_bank_base[i] = nullptr;
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
void msx_cart_ascii16::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_ascii16::restore_banks), this));
}


void msx_cart_ascii16::restore_banks()
=======
void msx_cart_ascii16_device::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_ascii16_device::restore_banks), this));
}


void msx_cart_ascii16_device::restore_banks()
>>>>>>> upstream/master
{
	for (int i = 0; i < 2; i++)
	{
		m_bank_base[i] = get_rom_base() + (m_selected_bank[i] & m_bank_mask) * 0x4000;
	}
}


<<<<<<< HEAD
void msx_cart_ascii16::device_reset()
{
	for (int i = 0; i < 2; i++)
	{
		m_selected_bank[i] = 0;
=======
void msx_cart_ascii16_device::device_reset()
{
	for (auto & elem : m_selected_bank)
	{
		elem = 0;
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
void msx_cart_ascii16::initialize_cartridge()
{
	UINT32 size = get_rom_size();
=======
void msx_cart_ascii16_device::initialize_cartridge()
{
	uint32_t size = get_rom_size();
>>>>>>> upstream/master

	if ( size > 256 * 0x4000 )
	{
		fatalerror("ascii16: ROM is too big\n");
	}

<<<<<<< HEAD
	UINT16 banks = size / 0x4000;
=======
	uint16_t banks = size / 0x4000;
>>>>>>> upstream/master

	if (size != banks * 0x4000 || (~(banks - 1) % banks))
	{
		fatalerror("ascii16: Invalid ROM size\n");
	}

	m_bank_mask = banks - 1;

	restore_banks();
}


<<<<<<< HEAD
READ8_MEMBER(msx_cart_ascii16::read_cart)
=======
READ8_MEMBER(msx_cart_ascii16_device::read_cart)
>>>>>>> upstream/master
{
	if ( offset >= 0x4000 && offset < 0xC000 )
	{
		return m_bank_base[offset >> 15][offset & 0x3fff];
	}
	return 0xff;
}


<<<<<<< HEAD
WRITE8_MEMBER(msx_cart_ascii16::write_cart)
=======
WRITE8_MEMBER(msx_cart_ascii16_device::write_cart)
>>>>>>> upstream/master
{
	if (offset >= 0x6000 && offset < 0x6800)
	{
		m_selected_bank[0] = data;
		m_bank_base[0] = get_rom_base() + (m_selected_bank[0] & m_bank_mask) * 0x4000;
	}

	if (offset >= 0x7000 && offset < 0x7800)
	{
		m_selected_bank[1] = data;
		m_bank_base[1] = get_rom_base() + (m_selected_bank[1] & m_bank_mask) * 0x4000;
	}
}





<<<<<<< HEAD
msx_cart_ascii8_sram::msx_cart_ascii8_sram(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MSX_CART_ASCII8_SRAM, "MSX Cartridge - ASCII8 w/SRAM", tag, owner, clock, "msx_cart_ascii8_sram", __FILE__)
=======
msx_cart_ascii8_sram_device::msx_cart_ascii8_sram_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MSX_CART_ASCII8_SRAM, tag, owner, clock)
>>>>>>> upstream/master
	, msx_cart_interface(mconfig, *this)
	, m_bank_mask(0)
	, m_sram_select_mask(0)
{
	for (int i = 0; i < 4; i++)
	{
		m_selected_bank[i] = 0;
<<<<<<< HEAD
		m_bank_base[i] = NULL;
=======
		m_bank_base[i] = nullptr;
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
void msx_cart_ascii8_sram::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_ascii8_sram::restore_banks), this));
}


void msx_cart_ascii8_sram::setup_bank(UINT8 bank)
=======
void msx_cart_ascii8_sram_device::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_ascii8_sram_device::restore_banks), this));
}


void msx_cart_ascii8_sram_device::setup_bank(uint8_t bank)
>>>>>>> upstream/master
{
	if (m_selected_bank[bank] & ~(m_sram_select_mask | m_bank_mask))
	{
		// Nothing is mapped
<<<<<<< HEAD
		m_bank_base[bank] = NULL;
=======
		m_bank_base[bank] = nullptr;
>>>>>>> upstream/master
	}
	else if (m_selected_bank[bank] & m_sram_select_mask)
	{
		// SRAM is selected
		m_bank_base[bank] = get_sram_base();
	}
	else
	{
		m_bank_base[bank] = get_rom_base() + (m_selected_bank[bank] & m_bank_mask ) * 0x2000;
	}
}


<<<<<<< HEAD
void msx_cart_ascii8_sram::restore_banks()
=======
void msx_cart_ascii8_sram_device::restore_banks()
>>>>>>> upstream/master
{
	for (int i = 0; i < 4; i++)
	{
		setup_bank(i);
	}
}


<<<<<<< HEAD
void msx_cart_ascii8_sram::device_reset()
{
	for (int i = 0; i < 4; i++)
	{
		m_selected_bank[i] = 0;
=======
void msx_cart_ascii8_sram_device::device_reset()
{
	for (auto & elem : m_selected_bank)
	{
		elem = 0;
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
void msx_cart_ascii8_sram::initialize_cartridge()
{
	UINT32 size = get_rom_size();
=======
void msx_cart_ascii8_sram_device::initialize_cartridge()
{
	uint32_t size = get_rom_size();
>>>>>>> upstream/master

	if ( size > 128 * 0x2000 )
	{
		fatalerror("ascii8_sram: ROM is too big\n");
	}

<<<<<<< HEAD
	UINT16 banks = size / 0x2000;
=======
	uint16_t banks = size / 0x2000;
>>>>>>> upstream/master

	if (size != banks * 0x2000 || (~(banks - 1) % banks))
	{
		fatalerror("ascii8_sram: Invalid ROM size\n");
	}

	if (get_sram_size() != 0x2000)
	{
		fatalerror("ascii8_sram: Unsupported SRAM size\n");
	}

	m_bank_mask = banks - 1;
	m_sram_select_mask = banks;

	restore_banks();
}


<<<<<<< HEAD
READ8_MEMBER(msx_cart_ascii8_sram::read_cart)
{
	if ( offset >= 0x4000 && offset < 0xC000 )
	{
		UINT8 *bank_base = m_bank_base[(offset - 0x4000) >> 13];

		if (bank_base != NULL)
=======
READ8_MEMBER(msx_cart_ascii8_sram_device::read_cart)
{
	if ( offset >= 0x4000 && offset < 0xC000 )
	{
		uint8_t *bank_base = m_bank_base[(offset - 0x4000) >> 13];

		if (bank_base != nullptr)
>>>>>>> upstream/master
		{
			return bank_base[offset & 0x1fff];
		}
	}
	return 0xff;
}


<<<<<<< HEAD
WRITE8_MEMBER(msx_cart_ascii8_sram::write_cart)
{
	if (offset >= 0x6000 && offset < 0x8000)
	{
		UINT8 bank = (offset / 0x800) & 0x03;
=======
WRITE8_MEMBER(msx_cart_ascii8_sram_device::write_cart)
{
	if (offset >= 0x6000 && offset < 0x8000)
	{
		uint8_t bank = (offset / 0x800) & 0x03;
>>>>>>> upstream/master

		m_selected_bank[bank] = data;
		setup_bank(bank);
	}
	else if (offset >= 0x8000 && offset < 0xc000)
	{
<<<<<<< HEAD
		UINT8 bank = (offset & 0x2000) ? 3 : 2;
=======
		uint8_t bank = (offset & 0x2000) ? 3 : 2;
>>>>>>> upstream/master

		if ((m_selected_bank[bank] & m_sram_select_mask) && !(m_selected_bank[bank] & ~(m_sram_select_mask | m_bank_mask)))
		{
			// Write to SRAM
			m_bank_base[bank][offset & 0x1fff] = data;
		}
	}
}



<<<<<<< HEAD
msx_cart_ascii16_sram::msx_cart_ascii16_sram(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MSX_CART_ASCII16_SRAM, "MSX Cartridge - ASCII16 w/SRAM", tag, owner, clock, "msx_cart_ascii16_sram", __FILE__)
=======
msx_cart_ascii16_sram_device::msx_cart_ascii16_sram_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MSX_CART_ASCII16_SRAM, tag, owner, clock)
>>>>>>> upstream/master
	, msx_cart_interface(mconfig, *this)
	, m_bank_mask(0)
	, m_sram_select_mask(0)
{
	for (int i = 0; i < 2; i++)
	{
		m_selected_bank[i] = 0;
<<<<<<< HEAD
		m_bank_base[i] = NULL;
=======
		m_bank_base[i] = nullptr;
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
void msx_cart_ascii16_sram::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_ascii16_sram::restore_banks), this));
}


void msx_cart_ascii16_sram::setup_bank(UINT8 bank)
=======
void msx_cart_ascii16_sram_device::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_ascii16_sram_device::restore_banks), this));
}


void msx_cart_ascii16_sram_device::setup_bank(uint8_t bank)
>>>>>>> upstream/master
{
	if (m_selected_bank[bank] & ~(m_sram_select_mask | m_bank_mask))
	{
		// Nothing is mapped
<<<<<<< HEAD
		m_bank_base[bank] = NULL;
=======
		m_bank_base[bank] = nullptr;
>>>>>>> upstream/master
	}
	else if (m_selected_bank[bank] & m_sram_select_mask)
	{
		// SRAM is selected
		m_bank_base[bank] = get_sram_base();
	}
	else
	{
		m_bank_base[bank] = get_rom_base() + (m_selected_bank[bank] & m_bank_mask) * 0x4000;
	}
}


<<<<<<< HEAD
void msx_cart_ascii16_sram::restore_banks()
=======
void msx_cart_ascii16_sram_device::restore_banks()
>>>>>>> upstream/master
{
	for (int i = 0; i < 2; i++)
	{
		setup_bank(i);
	}
}


<<<<<<< HEAD
void msx_cart_ascii16_sram::device_reset()
{
	for (int i = 0; i < 2; i++)
	{
		m_selected_bank[i] = 0;
=======
void msx_cart_ascii16_sram_device::device_reset()
{
	for (auto & elem : m_selected_bank)
	{
		elem = 0;
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
void msx_cart_ascii16_sram::initialize_cartridge()
{
	UINT32 size = get_rom_size();
=======
void msx_cart_ascii16_sram_device::initialize_cartridge()
{
	uint32_t size = get_rom_size();
>>>>>>> upstream/master

	if ( size > 128 * 0x4000 )
	{
		fatalerror("ascii16_sram: ROM is too big\n");
	}

<<<<<<< HEAD
	UINT16 banks = size / 0x4000;
=======
	uint16_t banks = size / 0x4000;
>>>>>>> upstream/master

	if (size != banks * 0x4000 || (~(banks - 1) % banks))
	{
		fatalerror("ascii16_sram: Invalid ROM size\n");
	}

	if (get_sram_size() != 0x800)
	{
		fatalerror("ascii16_sram: Unsupported SRAM size\n");
	}

	m_bank_mask = banks - 1;
	m_sram_select_mask = banks;

	restore_banks();
}


<<<<<<< HEAD
READ8_MEMBER(msx_cart_ascii16_sram::read_cart)
{
	if ( offset >= 0x4000 && offset < 0xC000 )
	{
		UINT8 bank = offset >> 15;

		if (m_bank_base[bank] != NULL)
=======
READ8_MEMBER(msx_cart_ascii16_sram_device::read_cart)
{
	if ( offset >= 0x4000 && offset < 0xC000 )
	{
		uint8_t bank = offset >> 15;

		if (m_bank_base[bank] != nullptr)
>>>>>>> upstream/master
		{
			if (m_selected_bank[bank] & m_sram_select_mask)
			{
				return m_bank_base[bank][offset & 0x7ff];
			}
			else
			{
				return m_bank_base[bank][offset & 0x3fff];
			}
		}
	}
	return 0xff;
}


<<<<<<< HEAD
WRITE8_MEMBER(msx_cart_ascii16_sram::write_cart)
=======
WRITE8_MEMBER(msx_cart_ascii16_sram_device::write_cart)
>>>>>>> upstream/master
{
	if (offset >= 0x6000 && offset < 0x6800)
	{
		m_selected_bank[0] = data;
		setup_bank(0);
	}

	if (offset >= 0x7000 && offset < 0x7800)
	{
		m_selected_bank[1] = data;
		setup_bank(1);
	}

	if (offset >= 0x8000 && offset < 0xc000)
	{
		if ((m_selected_bank[1] & m_sram_select_mask) && !(m_selected_bank[1] & ~(m_sram_select_mask | m_bank_mask)))
		{
			// Write to SRAM
			m_bank_base[1][offset & 0x7ff] = data;
		}
	}
}



<<<<<<< HEAD
msx_cart_msxwrite::msx_cart_msxwrite(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MSX_CART_MSXWRITE, "MSX Cartridge - MSXWRITE", tag, owner, clock, "msx_cart_msxwrite", __FILE__)
=======
msx_cart_msxwrite_device::msx_cart_msxwrite_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MSX_CART_MSXWRITE, tag, owner, clock)
>>>>>>> upstream/master
	, msx_cart_interface(mconfig, *this)
	, m_bank_mask(0)
{
	for (int i = 0; i < 2; i++)
	{
		m_selected_bank[i] = 0;
<<<<<<< HEAD
		m_bank_base[i] = NULL;
=======
		m_bank_base[i] = nullptr;
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
void msx_cart_msxwrite::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_msxwrite::restore_banks), this));
}


void msx_cart_msxwrite::restore_banks()
=======
void msx_cart_msxwrite_device::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_msxwrite_device::restore_banks), this));
}


void msx_cart_msxwrite_device::restore_banks()
>>>>>>> upstream/master
{
	for (int i = 0; i < 2; i++)
	{
		m_bank_base[i] = get_rom_base() + (m_selected_bank[i] & m_bank_mask) * 0x4000;
	}
}


<<<<<<< HEAD
void msx_cart_msxwrite::device_reset()
{
	for (int i = 0; i < 2; i++)
	{
		m_selected_bank[i] = 0;
=======
void msx_cart_msxwrite_device::device_reset()
{
	for (auto & elem : m_selected_bank)
	{
		elem = 0;
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
void msx_cart_msxwrite::initialize_cartridge()
{
	UINT32 size = get_rom_size();
=======
void msx_cart_msxwrite_device::initialize_cartridge()
{
	uint32_t size = get_rom_size();
>>>>>>> upstream/master

	if ( size > 256 * 0x4000 )
	{
		fatalerror("msxwrite: ROM is too big\n");
	}

<<<<<<< HEAD
	UINT16 banks = size / 0x4000;
=======
	uint16_t banks = size / 0x4000;
>>>>>>> upstream/master

	if (size != banks * 0x4000 || (~(banks - 1) % banks))
	{
		fatalerror("msxwrite: Invalid ROM size\n");
	}

	m_bank_mask = banks - 1;

	restore_banks();
}


<<<<<<< HEAD
READ8_MEMBER(msx_cart_msxwrite::read_cart)
=======
READ8_MEMBER(msx_cart_msxwrite_device::read_cart)
>>>>>>> upstream/master
{
	if ( offset >= 0x4000 && offset < 0xC000 )
	{
		return m_bank_base[offset >> 15][offset & 0x3fff];
	}
	return 0xff;
}


<<<<<<< HEAD
WRITE8_MEMBER(msx_cart_msxwrite::write_cart)
=======
WRITE8_MEMBER(msx_cart_msxwrite_device::write_cart)
>>>>>>> upstream/master
{
	// The rom writes to 6fff and 7fff for banking, unknown whether
	// other locations also trigger banking.
	switch (offset)
	{
		case 0x6fff:
			m_selected_bank[0] = data;
			m_bank_base[0] = get_rom_base() + (m_selected_bank[0] & m_bank_mask) * 0x4000;
			break;

		case 0x7fff:
			m_selected_bank[1] = data;
			m_bank_base[1] = get_rom_base() + (m_selected_bank[1] & m_bank_mask) * 0x4000;
			break;
	}
}
