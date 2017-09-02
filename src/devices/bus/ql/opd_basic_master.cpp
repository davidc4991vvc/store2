// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    OPD Basic Master emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "opd_basic_master.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type OPD_BASIC_MASTER = &device_creator<opd_basic_master_t>;
=======
DEFINE_DEVICE_TYPE(OPD_BASIC_MASTER, opd_basic_master_device, "ql_opdbm", "OPD Basic Master")
>>>>>>> upstream/master


//-------------------------------------------------
//  ROM( opd_basic_master )
//-------------------------------------------------

ROM_START( opd_basic_master )
	ROM_REGION( 0x10000, "rom", 0 )
	ROM_LOAD( "opd_basic_master_1984.rom", 0x00000, 0x10000, CRC(7e534c0d) SHA1(de485e89272e3b51086967333cda9de806ba3876) )
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *opd_basic_master_t::device_rom_region() const
=======
const tiny_rom_entry *opd_basic_master_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( opd_basic_master );
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  opd_basic_master_t - constructor
//-------------------------------------------------

opd_basic_master_t::opd_basic_master_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, OPD_BASIC_MASTER, "OPD Basic Master", tag, owner, clock, "ql_opdbm", __FILE__),
=======
//  opd_basic_master_device - constructor
//-------------------------------------------------

opd_basic_master_device::opd_basic_master_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, OPD_BASIC_MASTER, tag, owner, clock),
>>>>>>> upstream/master
	device_ql_expansion_card_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void opd_basic_master_t::device_start()
=======
void opd_basic_master_device::device_start()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  read -
//-------------------------------------------------

<<<<<<< HEAD
UINT8 opd_basic_master_t::read(address_space &space, offs_t offset, UINT8 data)
=======
uint8_t opd_basic_master_device::read(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	return data;
}


//-------------------------------------------------
//  write -
//-------------------------------------------------

<<<<<<< HEAD
void opd_basic_master_t::write(address_space &space, offs_t offset, UINT8 data)
=======
void opd_basic_master_device::write(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
}
