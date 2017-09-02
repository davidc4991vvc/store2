// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Micro Peripherals Floppy Disk Interface emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "mp_fdi.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type MICRO_PERIPHERALS_FLOPPY_DISK_INTERFACE = &device_creator<micro_peripherals_floppy_disk_interface_t>;
=======
DEFINE_DEVICE_TYPE(MICRO_PERIPHERALS_FLOPPY_DISK_INTERFACE, micro_peripherals_floppy_disk_interface_device, "ql_mpfdi", "Micro Peripherals Floppy Disk Interface")
>>>>>>> upstream/master


//-------------------------------------------------
//  ROM( micro_peripherals_floppy_disk_interface )
//-------------------------------------------------

ROM_START( micro_peripherals_floppy_disk_interface )
	ROM_REGION( 0x2000, "rom", 0 )
	ROM_DEFAULT_BIOS("v53e")
	ROM_SYSTEM_BIOS( 0, "v53e", "v5.3E" )
	ROMX_LOAD( "microp_disk system_v5.3e_1985.rom", 0x0000, 0x2000, CRC(9a8d8fa7) SHA1(f9f5e5d55f3046f63b4eae59222b81290d626e72), ROM_BIOS(1) )
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *micro_peripherals_floppy_disk_interface_t::device_rom_region() const
=======
const tiny_rom_entry *micro_peripherals_floppy_disk_interface_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( micro_peripherals_floppy_disk_interface );
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  micro_peripherals_floppy_disk_interface_t - constructor
//-------------------------------------------------

micro_peripherals_floppy_disk_interface_t::micro_peripherals_floppy_disk_interface_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, MICRO_PERIPHERALS_FLOPPY_DISK_INTERFACE, "Micro Peripherals Floppy Disk Interface", tag, owner, clock, "ql_mpfdi", __FILE__),
=======
//  micro_peripherals_floppy_disk_interface_device - constructor
//-------------------------------------------------

micro_peripherals_floppy_disk_interface_device::micro_peripherals_floppy_disk_interface_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, MICRO_PERIPHERALS_FLOPPY_DISK_INTERFACE, tag, owner, clock),
>>>>>>> upstream/master
	device_ql_expansion_card_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void micro_peripherals_floppy_disk_interface_t::device_start()
=======
void micro_peripherals_floppy_disk_interface_device::device_start()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  read -
//-------------------------------------------------

<<<<<<< HEAD
UINT8 micro_peripherals_floppy_disk_interface_t::read(address_space &space, offs_t offset, UINT8 data)
=======
uint8_t micro_peripherals_floppy_disk_interface_device::read(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	return data;
}


//-------------------------------------------------
//  write -
//-------------------------------------------------

<<<<<<< HEAD
void micro_peripherals_floppy_disk_interface_t::write(address_space &space, offs_t offset, UINT8 data)
=======
void micro_peripherals_floppy_disk_interface_device::write(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
}
