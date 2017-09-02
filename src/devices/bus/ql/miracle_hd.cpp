// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Miracle Hard Disk emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "miracle_hd.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type MIRACLE_HARD_DISK = &device_creator<miracle_hard_disk_t>;
=======
DEFINE_DEVICE_TYPE(MIRACLE_HARD_DISK, miracle_hard_disk_device, "ql_mhd", "Miracle Hard Disk")
>>>>>>> upstream/master


//-------------------------------------------------
//  ROM( miracle_hard_disk )
//-------------------------------------------------

ROM_START( miracle_hard_disk )
	ROM_REGION( 0x2000, "rom", 0 )
	ROM_DEFAULT_BIOS("v202")
	ROM_SYSTEM_BIOS( 0, "v202", "v2.02" )
	ROMX_LOAD( "miraculous_winny_v2.02_1989_qjump.rom", 0x0000, 0x2000, CRC(10982b35) SHA1(1beb87a207ecd0f47a43ed4b1bcc81d89ac75ffc), ROM_BIOS(1) )
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *miracle_hard_disk_t::device_rom_region() const
=======
const tiny_rom_entry *miracle_hard_disk_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( miracle_hard_disk );
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  miracle_hard_disk_t - constructor
//-------------------------------------------------

miracle_hard_disk_t::miracle_hard_disk_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, MIRACLE_HARD_DISK, "Miracle Hard Disk", tag, owner, clock, "ql_mhd", __FILE__),
=======
//  miracle_hard_disk_device - constructor
//-------------------------------------------------

miracle_hard_disk_device::miracle_hard_disk_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, MIRACLE_HARD_DISK, tag, owner, clock),
>>>>>>> upstream/master
	device_ql_rom_cartridge_card_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void miracle_hard_disk_t::device_start()
=======
void miracle_hard_disk_device::device_start()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  read -
//-------------------------------------------------

<<<<<<< HEAD
UINT8 miracle_hard_disk_t::read(address_space &space, offs_t offset, UINT8 data)
=======
uint8_t miracle_hard_disk_device::read(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	return data;
}


//-------------------------------------------------
//  write -
//-------------------------------------------------

<<<<<<< HEAD
void miracle_hard_disk_t::write(address_space &space, offs_t offset, UINT8 data)
=======
void miracle_hard_disk_device::write(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
}
