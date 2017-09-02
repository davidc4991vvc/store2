// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    PCML Q+ Disk Interface emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "pcml_qdisk.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type PCML_Q_DISK_INTERFACE = &device_creator<pcml_q_disk_interface_t>;
=======
DEFINE_DEVICE_TYPE(PCML_Q_DISK_INTERFACE, pcml_q_disk_interface_device, "ql_pcmlqdi", "PCML Q+ Disk Interface")
>>>>>>> upstream/master


//-------------------------------------------------
//  ROM( pcml_q_disk_interface )
//-------------------------------------------------

ROM_START( pcml_q_disk_interface )
	ROM_REGION( 0x4000, "rom", 0 )
	ROM_DEFAULT_BIOS("v114")
	ROM_SYSTEM_BIOS( 0, "v114", "v1.14" )
	ROMX_LOAD( "pcml_diskram system_v1.14_1984.rom", 0x0000, 0x4000, CRC(e38b41dd) SHA1(d2038f0b1a62e8e65ec86660d03c25489ce40274), ROM_BIOS(1) )
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *pcml_q_disk_interface_t::device_rom_region() const
=======
const tiny_rom_entry *pcml_q_disk_interface_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( pcml_q_disk_interface );
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  pcml_q_disk_interface_t - constructor
//-------------------------------------------------

pcml_q_disk_interface_t::pcml_q_disk_interface_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, PCML_Q_DISK_INTERFACE, "PCML Q+ Disk Interface", tag, owner, clock, "ql_pcmlqdi", __FILE__),
=======
//  pcml_q_disk_interface_device - constructor
//-------------------------------------------------

pcml_q_disk_interface_device::pcml_q_disk_interface_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, PCML_Q_DISK_INTERFACE, tag, owner, clock),
>>>>>>> upstream/master
	device_ql_expansion_card_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void pcml_q_disk_interface_t::device_start()
=======
void pcml_q_disk_interface_device::device_start()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  read -
//-------------------------------------------------

<<<<<<< HEAD
UINT8 pcml_q_disk_interface_t::read(address_space &space, offs_t offset, UINT8 data)
=======
uint8_t pcml_q_disk_interface_device::read(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	return data;
}


//-------------------------------------------------
//  write -
//-------------------------------------------------

<<<<<<< HEAD
void pcml_q_disk_interface_t::write(address_space &space, offs_t offset, UINT8 data)
=======
void pcml_q_disk_interface_device::write(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
}
