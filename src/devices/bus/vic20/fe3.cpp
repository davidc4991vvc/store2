// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Final Expansion v3 cartridge emulation

**********************************************************************/

/*

    TODO:

    - fe3diag register error#2 hp=5592 (same error in VICE)
    - SD card
    - RTC

*/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "fe3.h"



//**************************************************************************
//  MACROS/CONSTANTS
//**************************************************************************

#define AM29F040_TAG    "ic1"
#define ATMEGA1284_TAG  "ic5"
#define ATF1504AS_TAG   "ic4"

#define REG1_BANK \
	((m_reg1 & 0x7f) << 15)

#define LORAM_HIDDEN \
	(m_reg2 & REG2_BLK0)

#define BLK1_HIDDEN \
	(m_reg2 & REG2_BLK1)

#define BLK2_HIDDEN \
	(m_reg2 & REG2_BLK2)

#define BLK3_HIDDEN \
	(m_reg2 & REG2_BLK3)

#define BLK5_HIDDEN \
	(m_reg2 & REG2_BLK5)

#define REGISTERS_HIDDEN \
	((m_lockbit && ((m_reg1 & REG1_MODE_MASK) == REG1_START)) || (m_reg2 & REG2_IO3))



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type VIC20_FE3 = &device_creator<vic20_final_expansion_3_t>;
=======
DEFINE_DEVICE_TYPE(VIC20_FE3, vic20_final_expansion_3_device, "vic20_fe3", "Final Expansion v3")
>>>>>>> upstream/master


//-------------------------------------------------
//  ROM( vic20_fe3 )
//-------------------------------------------------

ROM_START( vic20_fe3 )
	ROM_REGION( 0x80000, AM29F040_TAG, 0 )
	ROM_LOAD( "fe3r022d.ic1", 0x00000, 0x80000, CRC(f4ff4aee) SHA1(1a389120159dee09c0f03ecb8fcd51ea2a2d2306) )

	ROM_REGION( 0x10b6, ATF1504AS_TAG, 0 )
	ROM_LOAD( "vc20final-v3-2.ic4", 0x000, 0x10b6, CRC(975b7197) SHA1(e64d69870b757a409abeb5f19e34866eef37ab18) )
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *vic20_final_expansion_3_t::device_rom_region() const
=======
const tiny_rom_entry *vic20_final_expansion_3_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( vic20_fe3 );
}


//-------------------------------------------------
<<<<<<< HEAD
//  MACHINE_DRIVER( vic20_fe3 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( vic20_fe3 )
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( vic20_final_expansion_3_device::device_add_mconfig )
>>>>>>> upstream/master
	MCFG_AMD_29F040_ADD(AM29F040_TAG)
MACHINE_CONFIG_END


<<<<<<< HEAD
//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor vic20_final_expansion_3_t::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( vic20_fe3 );
}


=======
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  vic20_final_expansion_3_t - constructor
//-------------------------------------------------

vic20_final_expansion_3_t::vic20_final_expansion_3_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, VIC20_FE3, "Final Expansion v3", tag, owner, clock, "vic20_fe3", __FILE__),
=======
//  vic20_final_expansion_3_device - constructor
//-------------------------------------------------

vic20_final_expansion_3_device::vic20_final_expansion_3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, VIC20_FE3, tag, owner, clock),
>>>>>>> upstream/master
	device_vic20_expansion_card_interface(mconfig, *this),
	m_flash_rom(*this, AM29F040_TAG),
	m_ram(*this, "sram"), m_reg1(0), m_reg2(0), m_lockbit(0)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void vic20_final_expansion_3_t::device_start()
=======
void vic20_final_expansion_3_device::device_start()
>>>>>>> upstream/master
{
	m_ram.allocate(0x80000);

	// state saving
	save_item(NAME(m_reg1));
	save_item(NAME(m_reg2));
	save_item(NAME(m_lockbit));
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void vic20_final_expansion_3_t::device_reset()
=======
void vic20_final_expansion_3_device::device_reset()
>>>>>>> upstream/master
{
	m_reg1 = 0;
	m_reg2 = 0;
}


//-------------------------------------------------
//  vic20_cd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 vic20_final_expansion_3_t::vic20_cd_r(address_space &space, offs_t offset, UINT8 data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3)
=======
uint8_t vic20_final_expansion_3_device::vic20_cd_r(address_space &space, offs_t offset, uint8_t data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3)
>>>>>>> upstream/master
{
	switch (m_reg1 & REG1_MODE_MASK)
	{
	case REG1_START:
		// read from ROM
		if (!blk5)
		{
			data = m_flash_rom->read(get_address(0, 3, offset));

			m_lockbit = 1;
		}

		// read from registers
		if (!io3 && !REGISTERS_HIDDEN && BIT(offset, 1))
		{
			data = read_register(BIT(offset, 0));
		}
		break;

	case REG1_SUPER_ROM:
		// read from RAM bank 0
		if ((!ram1 || !ram2 || !ram3) && !LORAM_HIDDEN)
		{
			data = m_ram[get_address(0, 0, offset)];
		}

		// read from ROM
		if (!blk1 && !BLK1_HIDDEN)
		{
			data = m_flash_rom->read(get_address(REG1_BANK, 0, offset));
		}
		if (!blk2 && !BLK2_HIDDEN)
		{
			data = m_flash_rom->read(get_address(REG1_BANK, 1, offset));
		}
		if (!blk3 && !BLK3_HIDDEN)
		{
			data = m_flash_rom->read(get_address(REG1_BANK, 2, offset));
		}
		if (!blk5 && !BLK5_HIDDEN)
		{
			data = m_flash_rom->read(get_address(REG1_BANK, 3, offset));
		}

		// read from registers
		if (!io3 && !REGISTERS_HIDDEN && BIT(offset, 1))
		{
			data = read_register(BIT(offset, 0));
		}
		break;

	case REG1_RAM_1:
		// read from RAM bank 0
		if ((!ram1 || !ram2 || !ram3) && !LORAM_HIDDEN)
		{
			data = m_ram[get_address(0, 0, offset)];
		}

		// read from RAM bank 1
		if (!blk1 && !BLK1_HIDDEN)
		{
			data = m_ram[get_address(1, 0, offset)];
		}
		if (!blk2 && !BLK2_HIDDEN)
		{
			data = m_ram[get_address(1, 1, offset)];
		}
		if (!blk3 && !BLK3_HIDDEN)
		{
			data = m_ram[get_address(1, 2, offset)];
		}
		if (!blk5 && !BLK5_HIDDEN)
		{
			data = m_ram[get_address(1, 3, offset)];
		}

		// read from registers
		if (!io3 && !REGISTERS_HIDDEN && BIT(offset, 1))
		{
			data = read_register(BIT(offset, 0));
		}
		break;

	case REG1_RAM_2:
		// read from RAM bank 0
		if ((!ram1 || !ram2 || !ram3) && !LORAM_HIDDEN)
		{
			data = m_ram[get_address(0, 0, offset)];
		}

		// read from RAM bank 1 or 2
		if (!blk1 && !BLK1_HIDDEN)
		{
			data = m_ram[get_address((m_reg1 & REG1_BLK1) ? 2 : 1, 0, offset)];
		}
		if (!blk2 && !BLK2_HIDDEN)
		{
			data = m_ram[get_address((m_reg1 & REG1_BLK2) ? 2 : 1, 1, offset)];
		}
		if (!blk3 && !BLK3_HIDDEN)
		{
			data = m_ram[get_address((m_reg1 & REG1_BLK3) ? 2 : 1, 2, offset)];
		}
		if (!blk5 && !BLK5_HIDDEN)
		{
			data = m_ram[get_address((m_reg1 & REG1_BLK5) ? 2 : 1, 3, offset)];
		}

		// read from registers
		if (!io3 && !REGISTERS_HIDDEN && BIT(offset, 1))
		{
			data = read_register(BIT(offset, 0));
		}
		break;

	case REG1_SUPER_RAM:
		// read from RAM bank 0
		if ((!ram1 || !ram2 || !ram3) && !LORAM_HIDDEN)
		{
			data = m_ram[get_address(0, 0, offset)];
		}

		// read from any RAM bank
		if (!blk1 && !BLK1_HIDDEN)
		{
			data = m_ram[get_address(REG1_BANK, 0, offset)];
		}
		if (!blk2 && !BLK2_HIDDEN)
		{
			data = m_ram[get_address(REG1_BANK, 1, offset)];
		}
		if (!blk3 && !BLK3_HIDDEN)
		{
			data = m_ram[get_address(REG1_BANK, 2, offset)];
		}
		if (!blk5 && !BLK5_HIDDEN)
		{
			data = m_ram[get_address(REG1_BANK, 3, offset)];
		}

		// read from registers
		if (!io3 && !REGISTERS_HIDDEN && BIT(offset, 1))
		{
			data = read_register(BIT(offset, 0));
		}
		break;

	case REG1_RAM_ROM:
		// read from RAM bank 0
		if ((!ram1 || !ram2 || !ram3) && !LORAM_HIDDEN)
		{
			data = m_ram[get_address(0, 0, offset)];
		}

		// read from ROM bank 0 or RAM bank 1
		if (!blk1 && !BLK1_HIDDEN)
		{
			data = (m_reg1 & REG1_BLK1) ? m_flash_rom->read(get_address(0, 0, offset)) : m_ram[get_address(1, 0, offset)];
		}
		if (!blk2 && !BLK2_HIDDEN)
		{
			data = (m_reg1 & REG1_BLK2) ? m_flash_rom->read(get_address(0, 1, offset)) : m_ram[get_address(1, 1, offset)];
		}
		if (!blk3 && !BLK3_HIDDEN)
		{
			data = (m_reg1 & REG1_BLK3) ? m_flash_rom->read(get_address(0, 2, offset)) : m_ram[get_address(1, 2, offset)];
		}
		if (!blk5 && !BLK5_HIDDEN)
		{
			data = (m_reg1 & REG1_BLK5) ? m_flash_rom->read(get_address(0, 3, offset)) : m_ram[get_address(1, 3, offset)];
		}

		// read from registers
		if (!io3 && !REGISTERS_HIDDEN && BIT(offset, 1))
		{
			data = read_register(BIT(offset, 0));
		}
		break;

	case REG1_FLASH:
		// read from RAM bank 0
		if ((!ram1 || !ram2 || !ram3) && !LORAM_HIDDEN)
		{
			data = m_ram[get_address(0, 0, offset)];
		}

		// read from ROM
		if (!blk1 && !BLK1_HIDDEN)
		{
			data = m_flash_rom->read(get_address(REG1_BANK, 0, offset));
		}
		if (!blk2 && !BLK2_HIDDEN)
		{
			data = m_flash_rom->read(get_address(REG1_BANK, 1, offset));
		}
		if (!blk3 && !BLK3_HIDDEN)
		{
			data = m_flash_rom->read(get_address(REG1_BANK, 2, offset));
		}
		if (!blk5 && !BLK5_HIDDEN)
		{
			data = m_flash_rom->read(get_address(REG1_BANK, 3, offset));
		}

		// read from registers
		if (!io3 && !REGISTERS_HIDDEN && BIT(offset, 1))
		{
			data = read_register(BIT(offset, 0));
		}
		break;
	}

	return data;
}


//-------------------------------------------------
//  vic20_cd_w - cartridge data write
//-------------------------------------------------

<<<<<<< HEAD
void vic20_final_expansion_3_t::vic20_cd_w(address_space &space, offs_t offset, UINT8 data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3)
=======
void vic20_final_expansion_3_device::vic20_cd_w(address_space &space, offs_t offset, uint8_t data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3)
>>>>>>> upstream/master
{
	switch (m_reg1 & REG1_MODE_MASK)
	{
	case REG1_START:
		// write to RAM bank 1
		if (!blk5)
		{
			m_ram[get_address(1, 3, offset)] = data;

			m_lockbit = 0;
		}

		// write to registers
		if (!io3 && !REGISTERS_HIDDEN && BIT(offset, 1))
		{
			write_register(BIT(offset, 0), data);
		}
		break;

	case REG1_SUPER_ROM:
		// write to RAM bank 0
		if ((!ram1 || !ram2 || !ram3) && !LORAM_HIDDEN)
		{
			m_ram[get_address(0, 0, offset)] = data;
		}

		// write to RAM bank 1
		if (!blk1 && !BLK1_HIDDEN)
		{
			m_ram[get_address(1, 0, offset)] = data;
		}
		if (!blk2 && !BLK2_HIDDEN)
		{
			m_ram[get_address(1, 1, offset)] = data;
		}
		if (!blk3 && !BLK3_HIDDEN)
		{
			m_ram[get_address(1, 2, offset)] = data;
		}
		if (!blk5 && !BLK5_HIDDEN)
		{
			m_ram[get_address(1, 3, offset)] = data;
		}

		// write to registers
		if (!io3 && !REGISTERS_HIDDEN && BIT(offset, 1))
		{
			write_register(BIT(offset, 0), data);
		}
		break;

	case REG1_RAM_1:
		// write to RAM bank 0
		if ((!ram1 || !ram2 || !ram3) && !LORAM_HIDDEN && REG1_BLK0)
		{
			m_ram[get_address(0, 0, offset)] = data;
		}

		// write to RAM bank 1 or 2
		if (!blk1 && !BLK1_HIDDEN)
		{
			m_ram[get_address((m_reg1 & REG1_BLK1) ? 2 : 1, 0, offset)] = data;
		}
		if (!blk2 && !BLK2_HIDDEN)
		{
			m_ram[get_address((m_reg1 & REG1_BLK2) ? 2 : 1, 1, offset)] = data;
		}
		if (!blk3 && !BLK3_HIDDEN)
		{
			m_ram[get_address((m_reg1 & REG1_BLK3) ? 2 : 1, 2, offset)] = data;
		}
		if (!blk5 && !BLK5_HIDDEN)
		{
			m_ram[get_address((m_reg1 & REG1_BLK5) ? 2 : 1, 3, offset)] = data;
		}

		// write to registers
		if (!io3 && !REGISTERS_HIDDEN && BIT(offset, 1))
		{
			write_register(BIT(offset, 0), data);
		}
		break;

	case REG1_RAM_2:
		// write to RAM bank 0
		if ((!ram1 || !ram2 || !ram3) && !LORAM_HIDDEN && REG1_BLK0)
		{
			m_ram[get_address(0, 0, offset)] = data;
		}

		// write to RAM bank 1
		if (!blk1 && !BLK1_HIDDEN)
		{
			m_ram[get_address(1, 0, offset)] = data;
		}
		if (!blk2 && !BLK2_HIDDEN)
		{
			m_ram[get_address(1, 1, offset)] = data;
		}
		if (!blk3 && !BLK3_HIDDEN)
		{
			m_ram[get_address(1, 2, offset)] = data;
		}
		if (!blk5 && !BLK5_HIDDEN)
		{
			m_ram[get_address(1, 3, offset)] = data;
		}

		// write to registers
		if (!io3 && !REGISTERS_HIDDEN && BIT(offset, 1))
		{
			write_register(BIT(offset, 0), data);
		}
		break;

	case REG1_SUPER_RAM:
		// write to RAM bank 0
		if ((!ram1 || !ram2 || !ram3) && !LORAM_HIDDEN)
		{
			m_ram[get_address(0, 0, offset)] = data;
		}

		// write whole RAM
		if (!blk1 && !BLK1_HIDDEN)
		{
			m_ram[get_address(REG1_BANK, 0, offset)] = data;
		}
		if (!blk2 && !BLK2_HIDDEN)
		{
			m_ram[get_address(REG1_BANK, 1, offset)] = data;
		}
		if (!blk3 && !BLK3_HIDDEN)
		{
			m_ram[get_address(REG1_BANK, 2, offset)] = data;
		}
		if (!blk5 && !BLK5_HIDDEN)
		{
			m_ram[get_address(REG1_BANK, 3, offset)] = data;
		}

		// write to registers
		if (!io3 && !REGISTERS_HIDDEN && BIT(offset, 1))
		{
			write_register(BIT(offset, 0), data);
		}
		break;

	case REG1_RAM_ROM:
		// write to RAM bank 0
		if ((!ram1 || !ram2 || !ram3) && !LORAM_HIDDEN && REG1_BLK0)
		{
			m_ram[get_address(0, 0, offset)] = data;
		}

		// write to RAM bank 1 or 2
		if (!blk1 && !BLK1_HIDDEN)
		{
			m_ram[get_address((m_reg1 & REG1_BLK1) ? 2 : 1, 0, offset)] = data;
		}
		if (!blk2 && !BLK2_HIDDEN)
		{
			m_ram[get_address((m_reg1 & REG1_BLK2) ? 2 : 1, 1, offset)] = data;
		}
		if (!blk3 && !BLK3_HIDDEN)
		{
			m_ram[get_address((m_reg1 & REG1_BLK3) ? 2 : 1, 2, offset)] = data;
		}
		if (!blk5 && !BLK5_HIDDEN)
		{
			m_ram[get_address((m_reg1 & REG1_BLK5) ? 2 : 1, 3, offset)] = data;
		}

		// write to registers
		if (!io3 && !REGISTERS_HIDDEN && BIT(offset, 1))
		{
			write_register(BIT(offset, 0), data);
		}
		break;

	case REG1_FLASH:
		// write to RAM bank 0
		if ((!ram1 || !ram2 || !ram3) && !LORAM_HIDDEN)
		{
			m_ram[get_address(0, 0, offset)] = data;
		}

		// write to ROM
		if (!blk1 && !BLK1_HIDDEN)
		{
			m_flash_rom->write(get_address(REG1_BANK, 0, offset), data);
		}
		if (!blk2 && !BLK2_HIDDEN)
		{
			m_flash_rom->write(get_address(REG1_BANK, 1, offset), data);
		}
		if (!blk3 && !BLK3_HIDDEN)
		{
			m_flash_rom->write(get_address(REG1_BANK, 2, offset), data);
		}
		if (!blk5 && !BLK5_HIDDEN)
		{
			m_flash_rom->write(get_address(REG1_BANK, 3, offset), data);
		}

		// write to registers
		if (!io3 && !REGISTERS_HIDDEN && BIT(offset, 1))
		{
			write_register(BIT(offset, 0), data);
		}
	}
}


//-------------------------------------------------
//  get_address -
//-------------------------------------------------

<<<<<<< HEAD
offs_t vic20_final_expansion_3_t::get_address(int bank, int block, offs_t offset)
=======
offs_t vic20_final_expansion_3_device::get_address(int bank, int block, offs_t offset)
>>>>>>> upstream/master
{
	block ^= (m_reg2 >> 5) & 0x03;

	return bank << 15 | block << 13 | offset;
}


//-------------------------------------------------
//  read_register -
//-------------------------------------------------

<<<<<<< HEAD
UINT8 vic20_final_expansion_3_t::read_register(offs_t offset)
{
	UINT8 data = 0;
=======
uint8_t vic20_final_expansion_3_device::read_register(offs_t offset)
{
	uint8_t data = 0;
>>>>>>> upstream/master

	switch (offset)
	{
	case 0:
		data = m_reg1;
		break;

	case 1:
		data = m_reg2;
		break;
	}

	return data;
}


//-------------------------------------------------
//  write_register -
//-------------------------------------------------

<<<<<<< HEAD
void vic20_final_expansion_3_t::write_register(offs_t offset, UINT8 data)
=======
void vic20_final_expansion_3_device::write_register(offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	switch (offset)
	{
	case 0:
		m_reg1 = data;
		break;

	case 1:
		m_reg2 = data;
		break;
	}
}
