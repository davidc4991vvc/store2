// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    Buddha

    Zorro-II IDE controller

<<<<<<< HEAD
***************************************************************************/

=======
    The 'speed' register is used to select the IDE timing according to
    the following table (bits 7-5 are used):

    0    497ns   7c  to select, IOR/IOW after 172ns  2c
    1    639ns   9c  to select, IOR/IOW after 243ns  3c
    2    781ns  11c  to select, IOR/IOW after 314ns  4c
    3    355ns   5c  to select, IOR/IOW after 101ns  1c
    4    355ns   5c  to select, IOR/IOW after 172ns  2c
    5    355ns   5c  to select, IOR/IOW after 243ns  3c
    6   1065ns  15c  to select, IOR/IOW after 314ns  4c
    7    355ns   5c  to select, IOR/IOW after 101ns  1c

    c = clock cycles. This isn't emulated.

***************************************************************************/

#include "emu.h"
>>>>>>> upstream/master
#include "buddha.h"

//**************************************************************************
//  CONSTANTS / MACROS
//**************************************************************************

#define VERBOSE 1


//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type BUDDHA = &device_creator<buddha_device>;

//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( buddha )
	MCFG_ATA_INTERFACE_ADD("ata_0", ata_devices, NULL, NULL, false)
	MCFG_ATA_INTERFACE_IRQ_HANDLER(WRITELINE(buddha_device, ide_0_interrupt_w))
	MCFG_ATA_INTERFACE_ADD("ata_1", ata_devices, NULL, NULL, false)
	MCFG_ATA_INTERFACE_IRQ_HANDLER(WRITELINE(buddha_device, ide_1_interrupt_w))
MACHINE_CONFIG_END

machine_config_constructor buddha_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( buddha );
}

=======
DEFINE_DEVICE_TYPE(BUDDHA, buddha_device, "buddha", "Buddha IDE controller")

//-------------------------------------------------
//  mmio_map - device-specific memory mapped I/O
//-------------------------------------------------

DEVICE_ADDRESS_MAP_START( mmio_map, 16, buddha_device )
	AM_RANGE(0x7fe, 0x7ff) AM_READWRITE(speed_r, speed_w)
	AM_RANGE(0x800, 0x8ff) AM_READWRITE(ide_0_cs0_r, ide_0_cs0_w)
	AM_RANGE(0x900, 0x9ff) AM_READWRITE(ide_0_cs1_r, ide_0_cs1_w)
	AM_RANGE(0xa00, 0xaff) AM_READWRITE(ide_1_cs0_r, ide_1_cs0_w)
	AM_RANGE(0xb00, 0xbff) AM_READWRITE(ide_1_cs1_r, ide_1_cs1_w)
	AM_RANGE(0xf00, 0xf3f) AM_READ(ide_0_interrupt_r)
	AM_RANGE(0xf40, 0xf7f) AM_READ(ide_1_interrupt_r)
	AM_RANGE(0xfc0, 0xfff) AM_WRITE(ide_interrupt_enable_w)
ADDRESS_MAP_END

//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( buddha_device::device_add_mconfig )
	MCFG_ATA_INTERFACE_ADD("ata_0", ata_devices, nullptr, nullptr, false)
	MCFG_ATA_INTERFACE_IRQ_HANDLER(WRITELINE(buddha_device, ide_0_interrupt_w))
	MCFG_ATA_INTERFACE_ADD("ata_1", ata_devices, nullptr, nullptr, false)
	MCFG_ATA_INTERFACE_IRQ_HANDLER(WRITELINE(buddha_device, ide_1_interrupt_w))
MACHINE_CONFIG_END

>>>>>>> upstream/master
//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

ROM_START( buddha )
<<<<<<< HEAD
	ROM_REGION16_BE(0x10000, "bootrom", 0)
	ROM_DEFAULT_BIOS("v103-17")
	ROM_SYSTEM_BIOS(0, "v103-8", "Version 103.8")
	ROMX_LOAD("buddha_103-8.rom", 0x0000, 0x8000, CRC(44f81426) SHA1(95555c6690b5c697e1cdca2726e47c1c6c194d7c), ROM_SKIP(1) | ROM_BIOS(1))
=======
	ROM_REGION16_BE(0x10000, "bootrom", ROMREGION_ERASEFF)
	ROM_DEFAULT_BIOS("v103-17")
	ROM_SYSTEM_BIOS(0, "v103-8", "Version 103.8")
	ROMX_LOAD("buddha_103-8.rom",  0x0000, 0x8000, CRC(44f81426) SHA1(95555c6690b5c697e1cdca2726e47c1c6c194d7c), ROM_SKIP(1) | ROM_BIOS(1))
>>>>>>> upstream/master
	ROM_SYSTEM_BIOS(1, "v103-17", "Version 103.17")
	ROMX_LOAD("buddha_103-17.rom", 0x0000, 0x8000, CRC(2b7b24e0) SHA1(ec17a58962c373a2892090ec9b1722d2c326d631), ROM_SKIP(1) | ROM_BIOS(2))
ROM_END

<<<<<<< HEAD
const rom_entry *buddha_device::device_rom_region() const
=======
const tiny_rom_entry *buddha_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( buddha );
}


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  buddha_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
buddha_device::buddha_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, BUDDHA, "Buddha IDE controller", tag, owner, clock, "buddha", __FILE__),
=======
buddha_device::buddha_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, BUDDHA, tag, owner, clock),
>>>>>>> upstream/master
	device_zorro2_card_interface(mconfig, *this),
	m_ata_0(*this, "ata_0"),
	m_ata_1(*this, "ata_1"),
	m_ide_interrupts_enabled(false),
	m_ide_0_interrupt(0),
	m_ide_1_interrupt(0)
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void buddha_device::device_start()
{
	set_zorro_device();
<<<<<<< HEAD
=======

	save_item(NAME(m_ide_interrupts_enabled));
	save_item(NAME(m_ide_0_interrupt));
	save_item(NAME(m_ide_1_interrupt));
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void buddha_device::device_reset()
{
<<<<<<< HEAD
=======
	m_ide_interrupts_enabled = false;
	m_ide_0_interrupt = 0;
	m_ide_1_interrupt = 0;
>>>>>>> upstream/master
}


//**************************************************************************
//  IMPLEMENTATION
//**************************************************************************

void buddha_device::autoconfig_base_address(offs_t address)
{
	if (VERBOSE)
<<<<<<< HEAD
		logerror("%s('%s'): autoconfig_base_address received: 0x%06x\n", shortname(), basetag(), address);
=======
		logerror("autoconfig_base_address received: 0x%06x\n", address);
>>>>>>> upstream/master

	if (VERBOSE)
		logerror("-> installing buddha\n");

	// stop responding to default autoconfig
	m_slot->m_space->unmap_readwrite(0xe80000, 0xe8007f);

<<<<<<< HEAD
=======
	// buddha registers
	m_slot->m_space->install_device(address, address + 0xfff, *this, &buddha_device::mmio_map);

>>>>>>> upstream/master
	// install autoconfig handler to new location
	m_slot->m_space->install_readwrite_handler(address, address + 0x7f,
		read16_delegate(FUNC(amiga_autoconfig::autoconfig_read), static_cast<amiga_autoconfig *>(this)),
		write16_delegate(FUNC(amiga_autoconfig::autoconfig_write), static_cast<amiga_autoconfig *>(this)), 0xffff);

<<<<<<< HEAD
	// buddha registers
	m_slot->m_space->install_readwrite_handler(address + 0x7fe, address + 0x7ff,
		read16_delegate(FUNC(buddha_device::speed_r), this),
		write16_delegate(FUNC(buddha_device::speed_w), this), 0xffff);

	m_slot->m_space->install_readwrite_handler(address + 0x800, address + 0x8ff,
		read16_delegate(FUNC(buddha_device::ide_0_cs0_r), this),
		write16_delegate(FUNC(buddha_device::ide_0_cs0_w), this), 0xffff);

	m_slot->m_space->install_readwrite_handler(address + 0x900, address + 0x9ff,
		read16_delegate(FUNC(buddha_device::ide_0_cs1_r), this),
		write16_delegate(FUNC(buddha_device::ide_0_cs1_w), this), 0xffff);

	m_slot->m_space->install_readwrite_handler(address + 0xa00, address + 0xaff,
		read16_delegate(FUNC(buddha_device::ide_0_cs0_r), this),
		write16_delegate(FUNC(buddha_device::ide_0_cs0_w), this), 0xffff);

	m_slot->m_space->install_readwrite_handler(address + 0xb00, address + 0xbff,
		read16_delegate(FUNC(buddha_device::ide_0_cs1_r), this),
		write16_delegate(FUNC(buddha_device::ide_0_cs1_w), this), 0xffff);

	m_slot->m_space->install_read_handler(address + 0xf00, address + 0xf3f,
		read16_delegate(FUNC(buddha_device::ide_0_interrupt_r), this), 0xffff);

	m_slot->m_space->install_read_handler(address + 0xf40, address + 0xf7f,
		read16_delegate(FUNC(buddha_device::ide_1_interrupt_r), this), 0xffff);

	m_slot->m_space->install_write_handler(address + 0xfc0, address + 0xfff,
		write16_delegate(FUNC(buddha_device::ide_interrupt_enable_w), this), 0xffff);

=======
>>>>>>> upstream/master
	// install access to the rom space
	m_slot->m_space->install_rom(address + 0x1000, address + 0xffff, memregion("bootrom")->base() + 0x1000);

	// we're done
	m_slot->cfgout_w(0);
}

WRITE_LINE_MEMBER( buddha_device::cfgin_w )
{
	if (VERBOSE)
<<<<<<< HEAD
		logerror("%s('%s'): configin_w (%d)\n", shortname(), basetag(), state);
=======
		logerror("configin_w (%d)\n", state);
>>>>>>> upstream/master

	if (state == 0)
	{
		// setup autoconfig
		autoconfig_board_type(BOARD_TYPE_ZORRO2);
		autoconfig_board_size(BOARD_SIZE_64K);
		autoconfig_link_into_memory(false);
		autoconfig_rom_vector_valid(true);
		autoconfig_multi_device(false);
		autoconfig_8meg_preferred(false);
		autoconfig_can_shutup(true);
		autoconfig_product(0x00);
		autoconfig_manufacturer(0x1212);
		autoconfig_serial(0x00000000);
		autoconfig_rom_vector(0x1000);

		// install autoconfig handler
		m_slot->m_space->install_readwrite_handler(0xe80000, 0xe8007f,
			read16_delegate(FUNC(amiga_autoconfig::autoconfig_read), static_cast<amiga_autoconfig *>(this)),
			write16_delegate(FUNC(amiga_autoconfig::autoconfig_write), static_cast<amiga_autoconfig *>(this)), 0xffff);
	}
}

READ16_MEMBER( buddha_device::speed_r )
{
<<<<<<< HEAD
	UINT16 data = 0xffff;

	if (VERBOSE)
		logerror("%s('%s'): ide_0_interrupt_r %04x [mask = %04x]\n", shortname(), basetag(), data, mem_mask);
=======
	uint16_t data = 0xffff;

	if (VERBOSE)
		logerror("speed_r %04x [mask = %04x]\n", data, mem_mask);
>>>>>>> upstream/master

	return data;
}

WRITE16_MEMBER( buddha_device::speed_w )
{
	if (VERBOSE)
<<<<<<< HEAD
		logerror("%s('%s'): speed_w %04x [mask = %04x]\n", shortname(), basetag(), data, mem_mask);
=======
		logerror("speed_w %04x [mask = %04x]\n", data, mem_mask);
>>>>>>> upstream/master
}

WRITE_LINE_MEMBER( buddha_device::ide_0_interrupt_w)
{
	if (VERBOSE)
<<<<<<< HEAD
		logerror("%s('%s'): ide_0_interrupt_w (%d)\n", shortname(), basetag(), state);
=======
		logerror("ide_0_interrupt_w (%d)\n", state);
>>>>>>> upstream/master

	m_ide_0_interrupt = state;

	if (m_ide_interrupts_enabled)
		m_slot->int2_w(state);
}

WRITE_LINE_MEMBER( buddha_device::ide_1_interrupt_w)
{
	if (VERBOSE)
<<<<<<< HEAD
		logerror("%s('%s'): ide_1_interrupt_w (%d)\n", shortname(), basetag(), state);
=======
		logerror("ide_1_interrupt_w (%d)\n", state);
>>>>>>> upstream/master

	m_ide_1_interrupt = state;

	if (m_ide_interrupts_enabled)
		m_slot->int2_w(state);
}

READ16_MEMBER( buddha_device::ide_0_interrupt_r )
{
<<<<<<< HEAD
	UINT16 data = 0xffff;

	data = m_ide_0_interrupt << 15;

	if (VERBOSE)
		logerror("%s('%s'): ide_0_interrupt_r %04x [mask = %04x]\n", shortname(), basetag(), data, mem_mask);

	logerror("%s\n", device().machine().describe_context());
=======
	uint16_t data;

	data = m_ide_0_interrupt << 15;

	if (VERBOSE && 0)
		logerror("ide_0_interrupt_r %04x [mask = %04x]\n", data, mem_mask);
>>>>>>> upstream/master

	return data;
}

READ16_MEMBER( buddha_device::ide_1_interrupt_r )
{
<<<<<<< HEAD
	UINT16 data = 0xffff;

	data = m_ide_1_interrupt << 15;

	if (VERBOSE)
		logerror("%s('%s'): ide_1_interrupt_r %04x [mask = %04x]\n", shortname(), basetag(), data, mem_mask);
=======
	uint16_t data;

	data = m_ide_1_interrupt << 15;

	if (VERBOSE && 0)
		logerror("ide_1_interrupt_r %04x [mask = %04x]\n", data, mem_mask);
>>>>>>> upstream/master

	return data;
}

WRITE16_MEMBER( buddha_device::ide_interrupt_enable_w )
{
	if (VERBOSE)
<<<<<<< HEAD
		logerror("%s('%s'): ide_interrupt_enable_w %04x [mask = %04x]\n", shortname(), basetag(), data, mem_mask);
=======
		logerror("ide_interrupt_enable_w %04x [mask = %04x]\n", data, mem_mask);
>>>>>>> upstream/master

	// writing any value here enables ide interrupts to the zorro slot
	m_ide_interrupts_enabled = true;
}

READ16_MEMBER( buddha_device::ide_0_cs0_r )
{
<<<<<<< HEAD
	UINT16 data = 0xffff;

	mem_mask = (mem_mask << 8) | (mem_mask >> 8);
	data = m_ata_0->read_cs0(space, (offset >> 1) & 0x07, mem_mask);

	if (VERBOSE)
		logerror("%s('%s'): ide_0_cs0_r(%04x) %04x [mask = %04x]\n", shortname(), basetag(), offset, data, mem_mask);

	return (data << 8) | (data >> 8);
=======
	uint16_t data = m_ata_0->read_cs0(space, (offset >> 1) & 0x07, (mem_mask << 8) | (mem_mask >> 8));
	data = (data << 8) | (data >> 8);

	if (VERBOSE)
		logerror("ide_0_cs0_r(%04x) %04x [mask = %04x]\n", offset, data, mem_mask);

	return data;
>>>>>>> upstream/master
}

WRITE16_MEMBER( buddha_device::ide_0_cs0_w )
{
	if (VERBOSE)
<<<<<<< HEAD
		logerror("%s('%s'): ide_0_cs0_w(%04x) %04x [mask = %04x]\n", shortname(), basetag(), offset, data, mem_mask);
=======
		logerror("ide_0_cs0_w(%04x) %04x [mask = %04x]\n", offset, data, mem_mask);
>>>>>>> upstream/master

	mem_mask = (mem_mask << 8) | (mem_mask >> 8);
	data = (data << 8) | (data >> 8);

	m_ata_0->write_cs0(space, (offset >> 1) & 0x07, data, mem_mask);
}

READ16_MEMBER( buddha_device::ide_0_cs1_r )
{
<<<<<<< HEAD
	UINT16 data = 0xffff;

	mem_mask = (mem_mask << 8) | (mem_mask >> 8);
	data = m_ata_0->read_cs1(space, (offset >> 1) & 0x07, mem_mask);

	if (VERBOSE)
		logerror("%s('%s'): ide_0_cs1_r(%04x) %04x [mask = %04x]\n", shortname(), basetag(), offset, data, mem_mask);

	return (data << 8) | (data >> 8);
=======
	uint16_t data = m_ata_0->read_cs1(space, (offset >> 1) & 0x07, (mem_mask << 8) | (mem_mask >> 8));
	data = (data << 8) | (data >> 8);

	if (VERBOSE)
		logerror("ide_0_cs1_r(%04x) %04x [mask = %04x]\n", offset, data, mem_mask);

	return data;
>>>>>>> upstream/master
}

WRITE16_MEMBER( buddha_device::ide_0_cs1_w )
{
	if (VERBOSE)
<<<<<<< HEAD
		logerror("%s('%s'): ide_0_cs1_w(%04x) %04x [mask = %04x]\n", shortname(), basetag(), offset, data, mem_mask);
=======
		logerror("ide_0_cs1_w(%04x) %04x [mask = %04x]\n", offset, data, mem_mask);
>>>>>>> upstream/master

	mem_mask = (mem_mask << 8) | (mem_mask >> 8);
	data = (data << 8) | (data >> 8);

	m_ata_0->write_cs1(space, (offset >> 1) & 0x07, data, mem_mask);
}

READ16_MEMBER( buddha_device::ide_1_cs0_r )
{
<<<<<<< HEAD
	UINT16 data = 0xffff;

	mem_mask = (mem_mask << 8) | (mem_mask >> 8);
	data = m_ata_1->read_cs0(space, (offset >> 1) & 0x07, mem_mask);

	if (VERBOSE)
		logerror("%s('%s'): ide_1_cs0_r(%04x) %04x [mask = %04x]\n", shortname(), basetag(), offset, data, mem_mask);

	return (data << 8) | (data >> 8);
=======
	uint16_t data = m_ata_1->read_cs0(space, (offset >> 1) & 0x07, (mem_mask << 8) | (mem_mask >> 8));
	data = (data << 8) | (data >> 8);

	if (VERBOSE)
		logerror("ide_1_cs0_r(%04x) %04x [mask = %04x]\n", offset, data, mem_mask);

	return data;
>>>>>>> upstream/master
}

WRITE16_MEMBER( buddha_device::ide_1_cs0_w )
{
	if (VERBOSE)
<<<<<<< HEAD
		logerror("%s('%s'): ide_1_cs0_w(%04x) %04x [mask = %04x]\n", shortname(), basetag(), offset, data, mem_mask);
=======
		logerror("ide_1_cs0_w(%04x) %04x [mask = %04x]\n", offset, data, mem_mask);
>>>>>>> upstream/master

	mem_mask = (mem_mask << 8) | (mem_mask >> 8);
	data = (data << 8) | (data >> 8);

	m_ata_1->write_cs0(space, (offset >> 1) & 0x07, data, mem_mask);
}

READ16_MEMBER( buddha_device::ide_1_cs1_r )
{
<<<<<<< HEAD
	UINT16 data = 0xffff;

	mem_mask = (mem_mask << 8) | (mem_mask >> 8);
	data = m_ata_1->read_cs1(space, (offset >> 1) & 0x07, mem_mask);

	if (VERBOSE)
		logerror("%s('%s'): ide_1_cs1_r(%04x) %04x [mask = %04x]\n", shortname(), basetag(), offset, data, mem_mask);

	return (data << 8) | (data >> 8);
=======
	uint16_t data = m_ata_1->read_cs1(space, (offset >> 1) & 0x07, (mem_mask << 8) | (mem_mask >> 8));
	data = (data << 8) | (data >> 8);

	if (VERBOSE)
		logerror("ide_1_cs1_r(%04x) %04x [mask = %04x]\n", offset, data, mem_mask);

	return data;
>>>>>>> upstream/master
}

WRITE16_MEMBER( buddha_device::ide_1_cs1_w )
{
	if (VERBOSE)
<<<<<<< HEAD
		logerror("%s('%s'): ide_1_cs1_w(%04x) %04x [mask = %04x]\n", shortname(), basetag(), offset, data, mem_mask);
=======
		logerror("ide_1_cs1_w(%04x) %04x [mask = %04x]\n", offset, data, mem_mask);
>>>>>>> upstream/master

	mem_mask = (mem_mask << 8) | (mem_mask >> 8);
	data = (data << 8) | (data >> 8);

	m_ata_1->write_cs1(space, (offset >> 1) & 0x07, data, mem_mask);
}
