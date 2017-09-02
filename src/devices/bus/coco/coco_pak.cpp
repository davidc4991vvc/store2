// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/***************************************************************************

<<<<<<< HEAD
    coco_pak.c
=======
    coco_pak.cpp
>>>>>>> upstream/master

    Code for emulating standard CoCo cartridges

***************************************************************************/

#include "emu.h"
#include "coco_pak.h"
<<<<<<< HEAD
#include "includes/coco.h"

#define CARTSLOT_TAG            "cart"
=======

#define CARTSLOT_TAG            "cart"
#define CART_AUTOSTART_TAG      "cart_autostart"

>>>>>>> upstream/master

/***************************************************************************
    IMPLEMENTATION
***************************************************************************/

<<<<<<< HEAD
static MACHINE_CONFIG_FRAGMENT(coco_pak)
MACHINE_CONFIG_END

=======
>>>>>>> upstream/master
ROM_START( coco_pak )
	ROM_REGION(0x8000, CARTSLOT_TAG, ROMREGION_ERASE00)
	// this region is filled by cococart_slot_device::call_load()
ROM_END

<<<<<<< HEAD
=======

//-------------------------------------------------
//  INPUT_PORTS( coco_cart_autostart )
//-------------------------------------------------

static INPUT_PORTS_START( coco_cart_autostart )
	PORT_START(CART_AUTOSTART_TAG)
	PORT_CONFNAME( 0x01, 0x01, "Cart Auto-Start" )
	PORT_CONFSETTING(    0x00, DEF_STR( Off ))
	PORT_CONFSETTING(    0x01, DEF_STR( On ))
INPUT_PORTS_END


>>>>>>> upstream/master
//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type COCO_PAK = &device_creator<coco_pak_device>;
=======
DEFINE_DEVICE_TYPE(COCO_PAK, coco_pak_device, "cocopak", "CoCo Program PAK")
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  coco_pak_device - constructor
//-------------------------------------------------
<<<<<<< HEAD
coco_pak_device::coco_pak_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source)
	: device_t(mconfig, type, name, tag, owner, clock, shortname, source),
		device_cococart_interface( mconfig, *this ), m_cart(nullptr), m_owner(nullptr)
{
}

coco_pak_device::coco_pak_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: device_t(mconfig, COCO_PAK, "CoCo Program PAK", tag, owner, clock, "cocopak", __FILE__),
		device_cococart_interface( mconfig, *this ), m_cart(nullptr), m_owner(nullptr)
	{
=======
coco_pak_device::coco_pak_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, type, tag, owner, clock)
	, device_cococart_interface(mconfig, *this)
	, m_cart(nullptr), m_autostart(*this, CART_AUTOSTART_TAG)
{
}

coco_pak_device::coco_pak_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: coco_pak_device(mconfig, COCO_PAK, tag, owner, clock)
{
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void coco_pak_device::device_start()
{
	m_cart = dynamic_cast<device_image_interface *>(owner());
<<<<<<< HEAD
	m_owner = dynamic_cast<cococart_slot_device *>(owner());
}

//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor coco_pak_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( coco_pak );
=======
}


//-------------------------------------------------
//  input_ports - device-specific input ports
//-------------------------------------------------

ioport_constructor coco_pak_device::device_input_ports() const
{
	return INPUT_PORTS_NAME( coco_cart_autostart );
>>>>>>> upstream/master
}

//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *coco_pak_device::device_rom_region() const
=======
const tiny_rom_entry *coco_pak_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( coco_pak );
}

/*-------------------------------------------------
    device_reset - device-specific startup
-------------------------------------------------*/

void coco_pak_device::device_reset()
{
<<<<<<< HEAD
	if (m_cart->exists()) {
		cococart_line_value cart_line;

		cart_line = read_safe(machine().root_device().ioport(CART_AUTOSTART_TAG), 0x01)
			? COCOCART_LINE_VALUE_Q
			: COCOCART_LINE_VALUE_CLEAR;

		/* normal CoCo PAKs tie their CART line to Q - the system clock */
		m_owner->cart_set_line(COCOCART_LINE_CART,cart_line);
=======
	if (m_cart->exists())
	{
		auto cart_line = m_autostart.read_safe(0x01)
			? line_value::Q
			: line_value::CLEAR;

		// normal CoCo PAKs tie their CART line to Q - the system clock
		set_line_value(line::CART, cart_line);
>>>>>>> upstream/master
	}
}

/*-------------------------------------------------
    get_cart_base
-------------------------------------------------*/

<<<<<<< HEAD
UINT8* coco_pak_device::get_cart_base()
=======
uint8_t* coco_pak_device::get_cart_base()
>>>>>>> upstream/master
{
	return memregion(CARTSLOT_TAG)->base();
}

/***************************************************************************
    BANKED CARTRIDGES
***************************************************************************/

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type COCO_PAK_BANKED = &device_creator<coco_pak_banked_device>;
=======
DEFINE_DEVICE_TYPE(COCO_PAK_BANKED, coco_pak_banked_device, "cocopak_banked", "CoCo Program PAK (Banked)")
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  coco_pak_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
coco_pak_banked_device::coco_pak_banked_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: coco_pak_device(mconfig, COCO_PAK_BANKED, "CoCo Program PAK (Banked)", tag, owner, clock, "cocopak_banked", __FILE__)
=======
coco_pak_banked_device::coco_pak_banked_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock)
	: coco_pak_device(mconfig, type, tag, owner, clock)
{
}
coco_pak_banked_device::coco_pak_banked_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: coco_pak_banked_device(mconfig, COCO_PAK_BANKED, tag, owner, clock)
>>>>>>> upstream/master
{
}

/*-------------------------------------------------
    device_reset - device-specific startup
-------------------------------------------------*/

void coco_pak_banked_device::device_reset()
{
	coco_pak_device::device_reset();

	banked_pak_set_bank(0);
}

/*-------------------------------------------------
    banked_pak_set_bank - function to set the bank
-------------------------------------------------*/

<<<<<<< HEAD
void coco_pak_banked_device::banked_pak_set_bank(UINT32 bank)
{
	UINT64 pos;
	UINT32 i;
	UINT8 *rom = memregion(CARTSLOT_TAG)->base();
	UINT32 rom_length = memregion(CARTSLOT_TAG)->bytes();
=======
void coco_pak_banked_device::banked_pak_set_bank(uint32_t bank)
{
	uint64_t pos;
	uint32_t i;
	uint8_t *rom = memregion(CARTSLOT_TAG)->base();
	uint32_t rom_length = memregion(CARTSLOT_TAG)->bytes();
>>>>>>> upstream/master

	if (m_cart->exists()) {
		pos = (bank * 0x4000) % m_cart->length();

		for (i = 0; i < rom_length / 0x4000; i++)
		{
			m_cart->fseek(pos, SEEK_SET);
			m_cart->fread(&rom[i * 0x4000], 0x4000);
		}
	}
}

<<<<<<< HEAD
/*-------------------------------------------------
    write
-------------------------------------------------*/

WRITE8_MEMBER(coco_pak_banked_device::write)
=======

//-------------------------------------------------
//  scs_write
//-------------------------------------------------

WRITE8_MEMBER(coco_pak_banked_device::scs_write)
>>>>>>> upstream/master
{
	switch(offset)
	{
		case 0:
<<<<<<< HEAD
			/* set the bank */
=======
			// set the bank
>>>>>>> upstream/master
			banked_pak_set_bank(data);
			break;
	}
}
