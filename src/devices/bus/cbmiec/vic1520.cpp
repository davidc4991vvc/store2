// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore VIC-1520 Plotter emulation

**********************************************************************/

/*
PA0 ATN
PA1 _CLK
PA5 ATTN ACK
PA6 NRFD
PA7 _DATA IN

PB0 IEEE SELECT
PB1 IEEE SELECT
PB2 IEEE SELECT
PB4 LED
PB5 REMOVE
PB6 CHANGE
PB7 FEED

PC0 _DN
PC1 _UP
PC7 COLOR SENSOR SW

PD0 X MOTOR COM A
PD1 X MOTOR COM B
PD2 X MOTOR COM C
PD3 X MOTOR COM D
PD4 Y MOTOR COM A
PD5 Y MOTOR COM B
PD6 Y MOTOR COM C
PD7 Y MOTOR COM D
*/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "vic1520.h"



//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define M6500_1_TAG "u1"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type VIC1520 = &device_creator<vic1520_t>;
=======
DEFINE_DEVICE_TYPE(VIC1520, vic1520_device, "vic1520", "VIC-1520 Color Printer Plotter")
>>>>>>> upstream/master


//-------------------------------------------------
//  ROM( vic1520 )
//-------------------------------------------------

ROM_START( vic1520 )
	ROM_REGION( 0x800, M6500_1_TAG, 0 )
	ROM_SYSTEM_BIOS( 0, "r01", "325340-01" )
	ROMX_LOAD( "325340-01.u1", 0x000, 0x800, CRC(3757da6f) SHA1(8ab43603f74b0f269bbe890d1939a9ae31307eb1), ROM_BIOS(1) )
	ROM_SYSTEM_BIOS( 1, "r03", "325340-03" )
	ROMX_LOAD( "325340-03.u1", 0x000, 0x800, CRC(f72ea2b6) SHA1(74c15b2cc1f7632bffa37439609cbdb50b82ea92), ROM_BIOS(2) )
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *vic1520_t::device_rom_region() const
=======
const tiny_rom_entry *vic1520_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( vic1520 );
}


//-------------------------------------------------
//  ADDRESS_MAP( vic1520_mem )
//-------------------------------------------------

<<<<<<< HEAD
static ADDRESS_MAP_START( vic1520_mem, AS_PROGRAM, 8, vic1520_t )
=======
static ADDRESS_MAP_START( vic1520_mem, AS_PROGRAM, 8, vic1520_device )
>>>>>>> upstream/master
	ADDRESS_MAP_GLOBAL_MASK(0xfff)
	AM_RANGE(0x000, 0x03f) AM_RAM
	AM_RANGE(0x800, 0xfff) AM_ROM AM_REGION(M6500_1_TAG, 0)
ADDRESS_MAP_END


//-------------------------------------------------
<<<<<<< HEAD
//  MACHINE_DRIVER( vic1520 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( vic1520 )
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( vic1520_device::device_add_mconfig )
>>>>>>> upstream/master
	MCFG_CPU_ADD(M6500_1_TAG, M6502, XTAL_2MHz) // M6500/1
	MCFG_CPU_PROGRAM_MAP(vic1520_mem)
MACHINE_CONFIG_END


//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor vic1520_t::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( vic1520 );
}


//-------------------------------------------------
=======
>>>>>>> upstream/master
//  INPUT_PORTS( vic1520 )
//-------------------------------------------------

static INPUT_PORTS_START( vic1520 )
INPUT_PORTS_END


//-------------------------------------------------
//  input_ports - device-specific input ports
//-------------------------------------------------

<<<<<<< HEAD
ioport_constructor vic1520_t::device_input_ports() const
=======
ioport_constructor vic1520_device::device_input_ports() const
>>>>>>> upstream/master
{
	return INPUT_PORTS_NAME( vic1520 );
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  vic1520_t - constructor
//-------------------------------------------------

vic1520_t::vic1520_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, VIC1520, "VIC-1520", tag, owner, clock, "vic1520", __FILE__),
=======
//  vic1520_device - constructor
//-------------------------------------------------

vic1520_device::vic1520_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, VIC1520, tag, owner, clock),
>>>>>>> upstream/master
	device_cbm_iec_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void vic1520_t::device_start()
=======
void vic1520_device::device_start()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void vic1520_t::device_reset()
=======
void vic1520_device::device_reset()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  cbm_iec_atn -
//-------------------------------------------------

<<<<<<< HEAD
void vic1520_t::cbm_iec_atn(int state)
=======
void vic1520_device::cbm_iec_atn(int state)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  cbm_iec_data -
//-------------------------------------------------

<<<<<<< HEAD
void vic1520_t::cbm_iec_data(int state)
=======
void vic1520_device::cbm_iec_data(int state)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  cbm_iec_reset -
//-------------------------------------------------

<<<<<<< HEAD
void vic1520_t::cbm_iec_reset(int state)
=======
void vic1520_device::cbm_iec_reset(int state)
>>>>>>> upstream/master
{
	if (!state)
	{
		device_reset();
	}
}
