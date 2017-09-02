// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore 1526/MPS-802/4023 Printer emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "c1526.h"



//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define M6504_TAG "u7d"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type C1526 = &device_creator<c1526_t>;
const device_type MPS802 = &device_creator<c1526_t>;
const device_type C4023 = &device_creator<c4023_t>;
=======
DEFINE_DEVICE_TYPE(C1526, c1526_device, "c1526", "MPS802/C1526 Printer")
DEFINE_DEVICE_TYPE(C4023, c4023_device, "c4023", "C4023 Printer")
>>>>>>> upstream/master


//-------------------------------------------------
//  ROM( c1526 )
//-------------------------------------------------

ROM_START( c1526 )
	ROM_REGION( 0x2000, M6504_TAG, 0 )
	ROM_SYSTEM_BIOS( 0, "r05", "Revision 5" )
	ROMX_LOAD( "325341-05.u8d", 0x0000, 0x2000, CRC(3ef63c59) SHA1(a71be83a476d2777d33dddb0103c036a047975ba), ROM_BIOS(1) )
	ROM_SYSTEM_BIOS( 1, "r07c", "Revision 7c" )
	ROMX_LOAD( "325341-08.u8d", 0x0000, 0x2000, CRC(38f85b4a) SHA1(25880091979b21fdaf713b53ef2f1cb8063a3505), ROM_BIOS(2) )
	ROM_SYSTEM_BIOS( 2, "r07b", "Revision 7b (Swe/Fin)" )
	ROMX_LOAD( "cbm 1526 vers. 1.0 skand.gen.u8d", 0x0000, 0x2000, CRC(21051f69) SHA1(7e622fc39985ebe9333d2b546b3c85fd6ab17a53), ROM_BIOS(3) )
	ROM_SYSTEM_BIOS( 3, "grafik", "MPS802 GrafikROM II v60.12" )
	ROMX_LOAD( "mps802 grafikrom ii v60.12.u8d", 0x0000, 0x2000, CRC(9f5e6b18) SHA1(8b7f620a8f85e250b142d72b812a67fd0e292d68), ROM_BIOS(4) )
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *c1526_t::device_rom_region() const
=======
const tiny_rom_entry *c1526_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( c1526 );
}


//-------------------------------------------------
//  ROM( c4023 )
//-------------------------------------------------

ROM_START( c4023 )
	ROM_REGION( 0x2000, M6504_TAG, 0 )
	ROM_LOAD( "325360-03.u8d", 0x0000, 0x2000, CRC(c6bb0977) SHA1(7a8c43d2e205f58d83709c04bc7795602a892ddd) )
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *c4023_t::device_rom_region() const
=======
const tiny_rom_entry *c4023_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( c4023 );
}


//-------------------------------------------------
//  ADDRESS_MAP( c1526_mem )
//-------------------------------------------------

<<<<<<< HEAD
static ADDRESS_MAP_START( c1526_mem, AS_PROGRAM, 8, c1526_base_t )
	AM_RANGE(0xe000, 0xffff) AM_ROM AM_REGION(M6504_TAG, 0)
=======
static ADDRESS_MAP_START( c1526_mem, AS_PROGRAM, 8, c1526_device_base )
	AM_RANGE(0x0000, 0x1fff) AM_ROM AM_REGION(M6504_TAG, 0)
>>>>>>> upstream/master
ADDRESS_MAP_END


//-------------------------------------------------
<<<<<<< HEAD
//  MACHINE_DRIVER( c1526 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( c1526 )
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( c1526_device::device_add_mconfig )
>>>>>>> upstream/master
	MCFG_CPU_ADD(M6504_TAG, M6504, XTAL_4MHz/4)
	MCFG_CPU_PROGRAM_MAP(c1526_mem)
MACHINE_CONFIG_END


//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor c1526_t::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( c1526 );
}


//-------------------------------------------------
//  MACHINE_DRIVER( c4023 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( c4023 )
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( c4023_device::device_add_mconfig )
>>>>>>> upstream/master
	MCFG_CPU_ADD(M6504_TAG, M6504, XTAL_4MHz/4)
	MCFG_CPU_PROGRAM_MAP(c1526_mem)
MACHINE_CONFIG_END


//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor c4023_t::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( c4023 );
}


//-------------------------------------------------
=======
>>>>>>> upstream/master
//  INPUT_PORTS( c1526 )
//-------------------------------------------------

static INPUT_PORTS_START( c1526 )
INPUT_PORTS_END


//-------------------------------------------------
//  input_ports - device-specific input ports
//-------------------------------------------------

<<<<<<< HEAD
ioport_constructor c1526_t::device_input_ports() const
=======
ioport_constructor c1526_device::device_input_ports() const
>>>>>>> upstream/master
{
	return INPUT_PORTS_NAME( c1526 );
}


//-------------------------------------------------
//  INPUT_PORTS( c4023 )
//-------------------------------------------------

static INPUT_PORTS_START( c4023 )
INPUT_PORTS_END


//-------------------------------------------------
//  input_ports - device-specific input ports
//-------------------------------------------------

<<<<<<< HEAD
ioport_constructor c4023_t::device_input_ports() const
=======
ioport_constructor c4023_device::device_input_ports() const
>>>>>>> upstream/master
{
	return INPUT_PORTS_NAME( c4023 );
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  c1526_base_t - constructor
//-------------------------------------------------

c1526_base_t:: c1526_base_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source) :
	device_t(mconfig, type, name, tag, owner, clock, shortname, source)
=======
//  c1526_device_base - constructor
//-------------------------------------------------

c1526_device_base::c1526_device_base(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, type, tag, owner, clock)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
<<<<<<< HEAD
//  c1526_t - constructor
//-------------------------------------------------

c1526_t::c1526_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	c1526_base_t(mconfig, C1526, "1526", tag, owner, clock, "c1526", __FILE__),
=======
//  c1526_device - constructor
//-------------------------------------------------

c1526_device::c1526_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	c1526_device_base(mconfig, C1526, tag, owner, clock),
>>>>>>> upstream/master
	device_cbm_iec_interface(mconfig, *this)
{
}


//-------------------------------------------------
<<<<<<< HEAD
//  c4023_t - constructor
//-------------------------------------------------

c4023_t::c4023_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	c1526_base_t(mconfig, C4023, "4023", tag, owner, clock, "c4023", __FILE__),
=======
//  c4023_device - constructor
//-------------------------------------------------

c4023_device::c4023_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	c1526_device_base(mconfig, C4023, tag, owner, clock),
>>>>>>> upstream/master
	device_ieee488_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void c1526_base_t::device_start()
=======
void c1526_device_base::device_start()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void c1526_base_t::device_reset()
=======
void c1526_device_base::device_reset()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  cbm_iec_atn -
//-------------------------------------------------

<<<<<<< HEAD
void c1526_t::cbm_iec_atn(int state)
=======
void c1526_device::cbm_iec_atn(int state)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  cbm_iec_data -
//-------------------------------------------------

<<<<<<< HEAD
void c1526_t::cbm_iec_data(int state)
=======
void c1526_device::cbm_iec_data(int state)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  cbm_iec_reset -
//-------------------------------------------------

<<<<<<< HEAD
void c1526_t::cbm_iec_reset(int state)
=======
void c1526_device::cbm_iec_reset(int state)
>>>>>>> upstream/master
{
	if (!state)
	{
		device_reset();
	}
}


//-------------------------------------------------
//  ieee488_atn_w -
//-------------------------------------------------

<<<<<<< HEAD
void c4023_t::ieee488_atn(int state)
=======
void c4023_device::ieee488_atn(int state)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  ieee488_ifc_w -
//-------------------------------------------------

<<<<<<< HEAD
void c4023_t::ieee488_ifc(int state)
=======
void c4023_device::ieee488_ifc(int state)
>>>>>>> upstream/master
{
	if (!state)
	{
		device_reset();
	}
}
