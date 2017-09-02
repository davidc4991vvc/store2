// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    CST QL Disc Interface emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "cst_qdisc.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type CST_QL_DISC_INTERFACE = &device_creator<cst_ql_disc_interface_t>;
=======
DEFINE_DEVICE_TYPE(CST_QL_DISC_INTERFACE, cst_ql_disc_interface_device, "ql_qldisc", "CST QL Disc Interface")
>>>>>>> upstream/master


//-------------------------------------------------
//  ROM( cst_ql_disc_interface )
//-------------------------------------------------

ROM_START( cst_ql_disc_interface )
	ROM_REGION( 0x2000, "rom", 0 )
	ROM_DEFAULT_BIOS("v116")
	ROM_SYSTEM_BIOS( 0, "v113", "v1.13" )
	ROMX_LOAD( "cst_qdisc_controller_v1.13_1984.rom", 0x0000, 0x2000, CRC(e08d9b5b) SHA1(ec981e60db0269412c518930ca6b5187b20a44f5), ROM_BIOS(1) )
	ROM_SYSTEM_BIOS( 1, "v116", "v1.16" )
	ROMX_LOAD( "cst_qdisc_controller_v1.16_1984.rom", 0x0000, 0x2000, CRC(05a73b00) SHA1(de8c5a4257107a4a41bc94c532cbfb7c65bfb472), ROM_BIOS(2) )
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *cst_ql_disc_interface_t::device_rom_region() const
=======
const tiny_rom_entry *cst_ql_disc_interface_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( cst_ql_disc_interface );
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  cst_ql_disc_interface_t - constructor
//-------------------------------------------------

cst_ql_disc_interface_t::cst_ql_disc_interface_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, CST_QL_DISC_INTERFACE, "CST QL Disc Interface", tag, owner, clock, "ql_qdisc", __FILE__),
=======
//  cst_ql_disc_interface_device - constructor
//-------------------------------------------------

cst_ql_disc_interface_device::cst_ql_disc_interface_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, CST_QL_DISC_INTERFACE, tag, owner, clock),
>>>>>>> upstream/master
	device_ql_expansion_card_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void cst_ql_disc_interface_t::device_start()
=======
void cst_ql_disc_interface_device::device_start()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  read -
//-------------------------------------------------

<<<<<<< HEAD
UINT8 cst_ql_disc_interface_t::read(address_space &space, offs_t offset, UINT8 data)
=======
uint8_t cst_ql_disc_interface_device::read(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	return data;
}


//-------------------------------------------------
//  write -
//-------------------------------------------------

<<<<<<< HEAD
void cst_ql_disc_interface_t::write(address_space &space, offs_t offset, UINT8 data)
=======
void cst_ql_disc_interface_device::write(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
}
