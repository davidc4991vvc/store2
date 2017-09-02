// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    CBM 500/600/700 High Resolution Graphics cartridge emulation

**********************************************************************/

/*

    TODO:

    http://www.wfking.de/hires.htm

    - version A (EF9365, 512x512 interlaced, 1 page)
    - version B (EF9366, 512x256 non-interlaced, 2 pages)
<<<<<<< HEAD

*/

#include "hrg.h"
=======
    - 256KB version ROM

*/

#include "emu.h"
#include "hrg.h"
#include "screen.h"
>>>>>>> upstream/master



//**************************************************************************
//  MACROS/CONSTANTS
//**************************************************************************

#define EF9365_TAG  "ef9365"
<<<<<<< HEAD
#define EF9366_TAG  "ef9366"
=======
#define EF9366_TAG  EF9365_TAG
>>>>>>> upstream/master
#define SCREEN_TAG  "screen"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type CBM2_HRG_A = &device_creator<cbm2_graphic_cartridge_a_device>;
const device_type CBM2_HRG_B = &device_creator<cbm2_graphic_cartridge_b_device>;
=======
DEFINE_DEVICE_TYPE(CBM2_HRG_A, cbm2_hrg_a_device, "cbm2_hrga", "CBM 500/600/700 High Resolution Graphics (A)")
DEFINE_DEVICE_TYPE(CBM2_HRG_B, cbm2_hrg_b_device, "cbm2_hrgb", "CBM 500/600/700 High Resolution Graphics (B)")
>>>>>>> upstream/master


//-------------------------------------------------
//  ROM( cbm2_hrg )
//-------------------------------------------------

ROM_START( cbm2_hrg )
	ROM_REGION( 0x2000, "bank3", 0 )
	ROM_LOAD( "324688-01 sw gr 600.bin", 0x0000, 0x2000, CRC(863e9ef8) SHA1(d75ffa97b2dd4e1baefe4acaa130daae866ab0e8) )
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *cbm2_graphic_cartridge_device::device_rom_region() const
=======
const tiny_rom_entry *cbm2_hrg_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( cbm2_hrg );
}


//-------------------------------------------------
<<<<<<< HEAD
//  MACHINE_CONFIG_FRAGMENT( cbm2_hrg_a )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( cbm2_hrg_a )
/*  MCFG_SCREEN_ADD(SCREEN_TAG, RASTER)
    MCFG_SCREEN_UPDATE_DEVICE(EF9365_TAG, ef9365_device, screen_update)
    MCFG_SCREEN_SIZE(512, 512)
    MCFG_SCREEN_VISIBLE_AREA(0, 512-1, 0, 512-1)
    MCFG_SCREEN_VBLANK_TIME(ATTOSECONDS_IN_USEC(2500))
    MCFG_SCREEN_REFRESH_RATE(50)

    MCFG_EF9365_ADD(EF9365_TAG, gdp_intf)*/
MACHINE_CONFIG_END


//-------------------------------------------------
//  MACHINE_CONFIG_FRAGMENT( cbm2_hrg_b )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( cbm2_hrg_b )
/*  MCFG_SCREEN_ADD(SCREEN_TAG, RASTER)
    MCFG_SCREEN_UPDATE_DEVICE(EF9366_TAG, ef9366_device, screen_update)
    MCFG_SCREEN_SIZE(512, 256)
    MCFG_SCREEN_VISIBLE_AREA(0, 512-1, 0, 256-1)
    MCFG_SCREEN_VBLANK_TIME(ATTOSECONDS_IN_USEC(2500))
    MCFG_SCREEN_REFRESH_RATE(50)

    MCFG_EF9366_ADD(EF9366_TAG, gdp_intf)*/
MACHINE_CONFIG_END


//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor cbm2_graphic_cartridge_a_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( cbm2_hrg_a );
}

machine_config_constructor cbm2_graphic_cartridge_b_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( cbm2_hrg_b );
}
=======
//  ADDRESS_MAP( hrg_a_map )
//-------------------------------------------------

static ADDRESS_MAP_START( hrg_a_map, 0, 8, cbm2_hrg_a_device )
	ADDRESS_MAP_GLOBAL_MASK(0x7fff)
	AM_RANGE(0x0000, 0x7fff) AM_RAM
ADDRESS_MAP_END


//-------------------------------------------------
//  ADDRESS_MAP( hrg_b_map )
//-------------------------------------------------

static ADDRESS_MAP_START( hrg_b_map, 0, 8, cbm2_hrg_b_device )
	ADDRESS_MAP_GLOBAL_MASK(0x3fff)
	AM_RANGE(0x0000, 0x3fff) AM_RAM
ADDRESS_MAP_END


//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( cbm2_hrg_a_device::device_add_mconfig )
	MCFG_SCREEN_ADD_MONOCHROME(SCREEN_TAG, RASTER, rgb_t::green())
	MCFG_SCREEN_UPDATE_DEVICE(EF9365_TAG, ef9365_device, screen_update)
	MCFG_SCREEN_SIZE(512, 512)
	MCFG_SCREEN_VISIBLE_AREA(0, 512-1, 0, 512-1)
	MCFG_SCREEN_REFRESH_RATE(25)
	MCFG_PALETTE_ADD_MONOCHROME("palette")

	MCFG_DEVICE_ADD(EF9365_TAG, EF9365, 1750000)
	MCFG_VIDEO_SET_SCREEN(SCREEN_TAG)
	MCFG_DEVICE_ADDRESS_MAP(0, hrg_a_map)
	MCFG_EF936X_PALETTE("palette")
	MCFG_EF936X_BITPLANES_CNT(1);
	MCFG_EF936X_DISPLAYMODE(DISPLAY_MODE_512x512);
MACHINE_CONFIG_END

MACHINE_CONFIG_MEMBER( cbm2_hrg_b_device::device_add_mconfig )
	MCFG_SCREEN_ADD_MONOCHROME(SCREEN_TAG, RASTER, rgb_t::green())
	MCFG_SCREEN_UPDATE_DEVICE(EF9366_TAG, ef9365_device, screen_update)
	MCFG_SCREEN_SIZE(512, 256)
	MCFG_SCREEN_VISIBLE_AREA(0, 512-1, 0, 256-1)
	MCFG_SCREEN_REFRESH_RATE(50)
	MCFG_PALETTE_ADD_MONOCHROME("palette")

	MCFG_DEVICE_ADD(EF9366_TAG, EF9365, 1750000)
	MCFG_VIDEO_SET_SCREEN(SCREEN_TAG)
	MCFG_DEVICE_ADDRESS_MAP(0, hrg_b_map)
	MCFG_EF936X_PALETTE("palette")
	MCFG_EF936X_BITPLANES_CNT(1);
	MCFG_EF936X_DISPLAYMODE(DISPLAY_MODE_512x256);
MACHINE_CONFIG_END
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  cbm2_graphic_cartridge_device - constructor
//-------------------------------------------------

cbm2_graphic_cartridge_device::cbm2_graphic_cartridge_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source) :
	device_t(mconfig, type, name, tag, owner, clock, shortname, source),
	device_cbm2_expansion_card_interface(mconfig, *this),
=======
//  cbm2_hrg_device - constructor
//-------------------------------------------------

cbm2_hrg_device::cbm2_hrg_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, type, tag, owner, clock),
	device_cbm2_expansion_card_interface(mconfig, *this),
	m_gdc(*this, EF9366_TAG),
>>>>>>> upstream/master
	m_bank3(*this, "bank3")
{
}

<<<<<<< HEAD
cbm2_graphic_cartridge_a_device::cbm2_graphic_cartridge_a_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	cbm2_graphic_cartridge_device(mconfig, CBM2_HRG_A, "CBM 500/600/700 High Resolution Graphics (A)", tag, owner, clock, "cbm2_hrga", __FILE__)
	//m_gdc(*this, EF9365_TAG)
{
}

cbm2_graphic_cartridge_b_device::cbm2_graphic_cartridge_b_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	cbm2_graphic_cartridge_device(mconfig, CBM2_HRG_B, "CBM 500/600/700 High Resolution Graphics (B)", tag, owner, clock, "cbm2_hrgb", __FILE__)
	//m_gdc(*this, EF9366_TAG)
=======
cbm2_hrg_a_device::cbm2_hrg_a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	cbm2_hrg_device(mconfig, CBM2_HRG_A, tag, owner, clock)
{
}

cbm2_hrg_b_device::cbm2_hrg_b_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	cbm2_hrg_device(mconfig, CBM2_HRG_B, tag, owner, clock)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void cbm2_graphic_cartridge_device::device_start()
=======
void cbm2_hrg_device::device_start()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void cbm2_graphic_cartridge_device::device_reset()
{
	//m_gdc->reset();
=======
void cbm2_hrg_device::device_reset()
{
	m_gdc->reset();
>>>>>>> upstream/master
}


//-------------------------------------------------
//  cbm2_bd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 cbm2_graphic_cartridge_device::cbm2_bd_r(address_space &space, offs_t offset, UINT8 data, int csbank1, int csbank2, int csbank3)
=======
uint8_t cbm2_hrg_device::cbm2_bd_r(address_space &space, offs_t offset, uint8_t data, int csbank1, int csbank2, int csbank3)
>>>>>>> upstream/master
{
	if (!csbank3)
	{
		if (offset < 0x7f80)
		{
			data = m_bank3->base()[offset & 0x1fff];
		}
		else if (offset == 0x7f90)
		{
			/*

			    bit     description

			    0       light pen
			    1
			    2
			    3
			    4
			    5
			    6
			    7

			*/
		}
		else if (offset == 0x7fb0)
		{
			// hard copy
		}
		else if (offset >= 0x7ff0)
		{
<<<<<<< HEAD
			//data = m_gdc->data_r(space, offset & 0x07);
=======
			data = m_gdc->data_r(space, offset & 0x0f);
>>>>>>> upstream/master
		}
	}

	return data;
}


//-------------------------------------------------
//  cbm2_bd_w - cartridge data write
//-------------------------------------------------

<<<<<<< HEAD
void cbm2_graphic_cartridge_device::cbm2_bd_w(address_space &space, offs_t offset, UINT8 data, int csbank1, int csbank2, int csbank3)
=======
void cbm2_hrg_device::cbm2_bd_w(address_space &space, offs_t offset, uint8_t data, int csbank1, int csbank2, int csbank3)
>>>>>>> upstream/master
{
	if (!csbank3)
	{
		if (offset == 0x7f80)
		{
			/*

			    bit     description

			    0       hard copy (0=active)
			    1       operating page select (version B)
			    2
			    3       read-modify-write (1=active)
			    4       display switch (1=graphic)
			    5       display page select (version B)
			    6
			    7

			*/
		}
		else if (offset >= 0x7ff0)
		{
<<<<<<< HEAD
			//m_gdc->data_w(space, offset & 0x07, data);
=======
			m_gdc->data_w(space, offset & 0x0f, data);
>>>>>>> upstream/master
		}
	}
}
