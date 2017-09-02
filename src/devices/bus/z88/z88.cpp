// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
/*********************************************************************

    z88.c

    Z88 cartridge slots emulation

*********************************************************************/

#include "emu.h"
#include "z88.h"
<<<<<<< HEAD
#include "emuopts.h"
=======
>>>>>>> upstream/master


/***************************************************************************
    PARAMETERS
***************************************************************************/

#define CLOSE_FLAP_TIME     attotime::from_msec(200)

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type Z88CART_SLOT = &device_creator<z88cart_slot_device>;
=======
DEFINE_DEVICE_TYPE(Z88CART_SLOT, z88cart_slot_device, "z88cart_slot", "Z88 Cartridge Slot")
>>>>>>> upstream/master


//**************************************************************************
//    Z88 cartridges Interface
//**************************************************************************

//-------------------------------------------------
//  device_z88cart_interface - constructor
//-------------------------------------------------

device_z88cart_interface::device_z88cart_interface(const machine_config &mconfig, device_t &device)
	: device_slot_card_interface(mconfig, device)
{
}


//-------------------------------------------------
//  ~device_z88cart_interface - destructor
//-------------------------------------------------

device_z88cart_interface::~device_z88cart_interface()
{
}


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  z88cart_slot_device - constructor
//-------------------------------------------------
<<<<<<< HEAD
z88cart_slot_device::z88cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
		device_t(mconfig, Z88CART_SLOT, "Z88 Cartridge Slot", tag, owner, clock, "z88cart_slot", __FILE__),
		device_image_interface(mconfig, *this),
		device_slot_interface(mconfig, *this),
		m_out_flp_cb(*this), m_cart(nullptr), m_flp_timer(nullptr)
=======
z88cart_slot_device::z88cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, Z88CART_SLOT, tag, owner, clock),
	device_image_interface(mconfig, *this),
	device_slot_interface(mconfig, *this),
	m_out_flp_cb(*this),
	m_cart(nullptr), m_flp_timer(nullptr)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  z88cart_slot_device - destructor
//-------------------------------------------------

z88cart_slot_device::~z88cart_slot_device()
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void z88cart_slot_device::device_start()
{
	m_cart = dynamic_cast<device_z88cart_interface *>(get_card_device());

	// resolve callbacks
	m_out_flp_cb.resolve_safe();

	m_flp_timer = timer_alloc(TIMER_FLP_CLEAR);
	m_flp_timer->reset();
}

<<<<<<< HEAD
//-------------------------------------------------
//  device_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void z88cart_slot_device::device_config_complete()
{
	// set brief and instance name
	update_names();
}

=======
>>>>>>> upstream/master

//-------------------------------------------------
//  device_timer - handler timer events
//-------------------------------------------------

void z88cart_slot_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	if (id == TIMER_FLP_CLEAR)
	{
		// close the flap
		m_out_flp_cb(CLEAR_LINE);
	}
}

/*-------------------------------------------------
    call load
-------------------------------------------------*/

<<<<<<< HEAD
bool z88cart_slot_device::call_load()
{
	if (m_cart)
	{
		offs_t read_length = 0;
		UINT8 *cart_base = m_cart->get_cart_base();

		if (cart_base != NULL)
		{
			if (software_entry() == NULL)
=======
image_init_result z88cart_slot_device::call_load()
{
	if (m_cart)
	{
		offs_t read_length;
		uint8_t *cart_base = m_cart->get_cart_base();

		if (cart_base != nullptr)
		{
			if (!loaded_through_softlist())
>>>>>>> upstream/master
			{
				read_length = length();
				fread(cart_base + (m_cart->get_cart_size() - read_length), read_length);
			}
			else
			{
				read_length = get_software_region_length("rom");
				memcpy(cart_base + (m_cart->get_cart_size() - read_length), get_software_region("rom"), read_length);
			}
		}
		else
<<<<<<< HEAD
			return IMAGE_INIT_FAIL;
=======
			return image_init_result::FAIL;
>>>>>>> upstream/master
	}

	// open the flap
	m_out_flp_cb(ASSERT_LINE);

	// setup the timer for close the flap
	m_flp_timer->adjust(CLOSE_FLAP_TIME);

<<<<<<< HEAD
	return IMAGE_INIT_PASS;
=======
	return image_init_result::PASS;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    call_unload
-------------------------------------------------*/

void z88cart_slot_device::call_unload()
{
	if (m_cart)
<<<<<<< HEAD
		memset(m_cart->get_cart_base(), 0xff, m_cart->get_cart_size());
=======
	{
		auto cart_size = m_cart->get_cart_size();
		if (cart_size>0)
			memset(m_cart->get_cart_base(), 0xff, cart_size);
	}
>>>>>>> upstream/master

	// open the flap
	m_out_flp_cb(ASSERT_LINE);

	// setup the timer for close the flap
	m_flp_timer->adjust(CLOSE_FLAP_TIME);
}


/*-------------------------------------------------
<<<<<<< HEAD
    call softlist load
-------------------------------------------------*/

bool z88cart_slot_device::call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry)
{
	load_software_part_region(*this, swlist, swname, start_entry );
	return TRUE;
}

/*-------------------------------------------------
    get default card software
-------------------------------------------------*/

void z88cart_slot_device::get_default_card_software(std::string &result)
{
	software_get_default_slot(result, "128krom");
=======
    get default card software
-------------------------------------------------*/

std::string z88cart_slot_device::get_default_card_software(get_default_card_software_hook &hook) const
{
	return software_get_default_slot("128krom");
>>>>>>> upstream/master
}


/*-------------------------------------------------
    read
-------------------------------------------------*/

READ8_MEMBER(z88cart_slot_device::read)
{
	if (m_cart)
		return m_cart->read(space, offset);
	else
		return 0xff;
}


/*-------------------------------------------------
    write
-------------------------------------------------*/

WRITE8_MEMBER(z88cart_slot_device::write)
{
	if (m_cart)
		m_cart->write(space, offset, data);
}
<<<<<<< HEAD
=======


/*-------------------------------------------------
    get_cart_base
-------------------------------------------------*/

uint8_t* z88cart_slot_device::get_cart_base()
{
	if (m_cart)
		return m_cart->get_cart_base();
	else
		return nullptr;
}
>>>>>>> upstream/master
