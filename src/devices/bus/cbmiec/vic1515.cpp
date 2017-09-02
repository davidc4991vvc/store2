// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore VIC-1515 Printer emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "vic1515.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type VIC1515 = &device_creator<vic1515_t>;
=======
DEFINE_DEVICE_TYPE(VIC1515, vic1515_device, "vic1515", "VIC-1515 Graphic Printer")
>>>>>>> upstream/master


//-------------------------------------------------
//  ROM( vic1515 )
//-------------------------------------------------

ROM_START( vic1515 )
	ROM_REGION( 0x1000, "rom", 0 )
	ROM_LOAD( "805-5.p4", 0x0000, 0x1000, CRC(05a99a5a) SHA1(035c23dc83923eea34feea260445356a909fbd98) )
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *vic1515_t::device_rom_region() const
=======
const tiny_rom_entry *vic1515_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( vic1515 );
}


//-------------------------------------------------
//  ADDRESS_MAP( vic1515_mem )
//-------------------------------------------------

<<<<<<< HEAD
static ADDRESS_MAP_START( vic1515_mem, AS_PROGRAM, 8, vic1515_t )
=======
static ADDRESS_MAP_START( vic1515_mem, AS_PROGRAM, 8, vic1515_device )
>>>>>>> upstream/master
	AM_RANGE(0x0000, 0x0fff) AM_ROM AM_REGION("rom", 0)
ADDRESS_MAP_END


//-------------------------------------------------
//  ADDRESS_MAP( vic1515_io )
//-------------------------------------------------

<<<<<<< HEAD
static ADDRESS_MAP_START( vic1515_io, AS_IO, 8, vic1515_t )
=======
static ADDRESS_MAP_START( vic1515_io, AS_IO, 8, vic1515_device )
>>>>>>> upstream/master
ADDRESS_MAP_END


//-------------------------------------------------
<<<<<<< HEAD
//  MACHINE_DRIVER( vic1515 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( vic1515 )
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( vic1515_device::device_add_mconfig )
>>>>>>> upstream/master
	MCFG_CPU_ADD("maincpu", I8039, XTAL_6MHz)
	MCFG_CPU_PROGRAM_MAP(vic1515_mem)
	MCFG_CPU_IO_MAP(vic1515_io)
MACHINE_CONFIG_END


//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor vic1515_t::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( vic1515 );
}


//-------------------------------------------------
=======
>>>>>>> upstream/master
//  INPUT_PORTS( vic1515 )
//-------------------------------------------------

static INPUT_PORTS_START( vic1515 )
	PORT_START("ADDRESS")
	PORT_DIPNAME( 0x03, 0x00, "Device Address" )
	PORT_DIPSETTING(    0x00, "4" )
	PORT_DIPSETTING(    0x01, "5" )
	PORT_DIPSETTING(    0x02, "T" )
INPUT_PORTS_END


//-------------------------------------------------
//  input_ports - device-specific input ports
//-------------------------------------------------

<<<<<<< HEAD
ioport_constructor vic1515_t::device_input_ports() const
=======
ioport_constructor vic1515_device::device_input_ports() const
>>>>>>> upstream/master
{
	return INPUT_PORTS_NAME( vic1515 );
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  vic1515_t - constructor
//-------------------------------------------------

vic1515_t::vic1515_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, VIC1515, "VIC-1515", tag, owner, clock, "vic1515", __FILE__),
=======
//  vic1515_device - constructor
//-------------------------------------------------

vic1515_device::vic1515_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, VIC1515, tag, owner, clock),
>>>>>>> upstream/master
	device_cbm_iec_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void vic1515_t::device_start()
=======
void vic1515_device::device_start()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void vic1515_t::device_reset()
=======
void vic1515_device::device_reset()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  cbm_iec_atn -
//-------------------------------------------------

<<<<<<< HEAD
void vic1515_t::cbm_iec_atn(int state)
=======
void vic1515_device::cbm_iec_atn(int state)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  cbm_iec_data -
//-------------------------------------------------

<<<<<<< HEAD
void vic1515_t::cbm_iec_data(int state)
=======
void vic1515_device::cbm_iec_data(int state)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  cbm_iec_reset -
//-------------------------------------------------

<<<<<<< HEAD
void vic1515_t::cbm_iec_reset(int state)
=======
void vic1515_device::cbm_iec_reset(int state)
>>>>>>> upstream/master
{
	if (!state)
	{
		device_reset();
	}
}
