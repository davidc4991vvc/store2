// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/***********************************************************************************************************

   Generic ROM / RAM Socket and Cartslot device

   This device offers basic RAM / ROM allocation and access

   The available handlers are suited for any situation where a system opens a
   "window" over a ROM or RAM area and we want to access it during emulation.

   This device is not suited whenever the system exposes additional lines to
   the socket/slot: e.g. whenever input/output lines are present, whenever
   there are lines controlling bankswitch / paging, and whenever different
   cart configurations have to be supported (like some PCBs containing ROM
   only, and other containing both ROM and RAM)
   In the latter situations, per-system slot devices have to be created (see
   e.g. APF cart slot device for an example of a simple device with multiple
   pcbs supported)

 ***********************************************************************************************************/


#include "emu.h"
#include "slot.h"

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type GENERIC_SOCKET = &device_creator<generic_slot_device>;
=======
DEFINE_DEVICE_TYPE(GENERIC_SOCKET, generic_slot_device, "generic_socket", "Generic ROM Socket / RAM Socket / Cartridge Slot")
>>>>>>> upstream/master


//-------------------------------------------------
//  device_generic_cart_interface - constructor
//-------------------------------------------------

device_generic_cart_interface::device_generic_cart_interface(const machine_config &mconfig, device_t &device)
	: device_slot_card_interface(mconfig, device),
<<<<<<< HEAD
		m_rom(NULL),
		m_rom_size(0)
=======
		m_rom(nullptr),
		m_rom_size(0),
		m_region(*this, DEVICE_SELF)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  ~device_generic_cart_interface - destructor
//-------------------------------------------------

device_generic_cart_interface::~device_generic_cart_interface()
{
}

//-------------------------------------------------
//  rom_alloc - alloc the space for the cart
//-------------------------------------------------

void device_generic_cart_interface::rom_alloc(size_t size, int width, endianness_t endian, const char *tag)
{
<<<<<<< HEAD
	if (m_rom == NULL)
=======
	if (m_rom == nullptr)
>>>>>>> upstream/master
	{
		m_rom = device().machine().memory().region_alloc(std::string(tag).append(GENERIC_ROM_REGION_TAG).c_str(), size, width, endian)->base();
		m_rom_size = size;
	}
}


//-------------------------------------------------
//  ram_alloc - alloc the space for the ram
//-------------------------------------------------

<<<<<<< HEAD
void device_generic_cart_interface::ram_alloc(UINT32 size)
=======
void device_generic_cart_interface::ram_alloc(uint32_t size)
>>>>>>> upstream/master
{
	m_ram.resize(size);
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  generic_slot_device - constructor
//-------------------------------------------------
<<<<<<< HEAD
generic_slot_device::generic_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
						device_t(mconfig, GENERIC_SOCKET, "Generic ROM Socket / RAM Socket / Cartridge Slot", tag, owner, clock, "generic_socket", __FILE__),
						device_image_interface(mconfig, *this),
						device_slot_interface(mconfig, *this),
						m_interface(NULL),
						m_default_card("rom"),
						m_extensions("bin"),
						m_must_be_loaded(FALSE),
						m_width(GENERIC_ROM8_WIDTH),
						m_endianness(ENDIANNESS_LITTLE), m_cart(nullptr)
=======
generic_slot_device::generic_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, GENERIC_SOCKET, tag, owner, clock),
	device_image_interface(mconfig, *this),
	device_slot_interface(mconfig, *this),
	m_interface(nullptr),
	m_default_card("rom"),
	m_extensions("bin"),
	m_must_be_loaded(false),
	m_width(GENERIC_ROM8_WIDTH),
	m_endianness(ENDIANNESS_LITTLE),
	m_cart(nullptr)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  generic_slot_device - destructor
//-------------------------------------------------

generic_slot_device::~generic_slot_device()
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void generic_slot_device::device_start()
{
	m_cart = dynamic_cast<device_generic_cart_interface *>(get_card_device());
}

<<<<<<< HEAD
//-------------------------------------------------
//  device_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void generic_slot_device::device_config_complete()
{
	// set brief and instance name
	update_names();
}

=======
>>>>>>> upstream/master

/*-------------------------------------------------
 call load
 -------------------------------------------------*/

<<<<<<< HEAD
bool generic_slot_device::call_load()
=======
image_init_result generic_slot_device::call_load()
>>>>>>> upstream/master
{
	if (m_cart)
	{
		if (!m_device_image_load.isnull())
			return m_device_image_load(*this);
		else
		{
<<<<<<< HEAD
			UINT32 len = common_get_size("rom");
=======
			uint32_t len = common_get_size("rom");
>>>>>>> upstream/master

			rom_alloc(len, m_width, m_endianness);
			common_load_rom(get_rom_base(), len, "rom");

<<<<<<< HEAD
			return IMAGE_INIT_PASS;
		}
	}

	return IMAGE_INIT_PASS;
=======
			return image_init_result::PASS;
		}
	}

	return image_init_result::PASS;
>>>>>>> upstream/master
}


/*-------------------------------------------------
 call_unload
 -------------------------------------------------*/

void generic_slot_device::call_unload()
{
	if (!m_device_image_unload.isnull())
		return m_device_image_unload(*this);
}


/*-------------------------------------------------
<<<<<<< HEAD
 call softlist load
 -------------------------------------------------*/

bool generic_slot_device::call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry)
{
	load_software_part_region(*this, swlist, swname, start_entry);
	return TRUE;
}



/*-------------------------------------------------
 get default card software
 -------------------------------------------------*/

void generic_slot_device::get_default_card_software(std::string &result)
{
	software_get_default_slot(result, m_default_card);
=======
 get default card software
 -------------------------------------------------*/

std::string generic_slot_device::get_default_card_software(get_default_card_software_hook &hook) const
{
	return software_get_default_slot(m_default_card);
>>>>>>> upstream/master
}


/**************************************************

 Implementation

 **************************************************/


/*-------------------------------------------------
 common_get_size - it gets image file size both
 for fullpath and for softlist
 -------------------------------------------------*/

<<<<<<< HEAD
UINT32 generic_slot_device::common_get_size(const char *region)
{
	// if we are loading from softlist, you have to specify a region
	assert((software_entry() == NULL) || (region != NULL));

	return (software_entry() == NULL) ? length() : get_software_region_length(region);
=======
uint32_t generic_slot_device::common_get_size(const char *region)
{
	// if we are loading from softlist, you have to specify a region
	assert(!loaded_through_softlist() || (region != nullptr));

	return !loaded_through_softlist() ? length() : get_software_region_length(region);
>>>>>>> upstream/master
}

/*-------------------------------------------------
 common_load_rom - it loads from image file both
 for fullpath and for softlist
 -------------------------------------------------*/

<<<<<<< HEAD
void generic_slot_device::common_load_rom(UINT8 *ROM, UINT32 len, const char *region)
{
	// basic sanity check
	assert((ROM != NULL) && (len > 0));

	// if we are loading from softlist, you have to specify a region
	assert((software_entry() == NULL) || (region != NULL));

	if (software_entry() == NULL)
=======
void generic_slot_device::common_load_rom(uint8_t *ROM, uint32_t len, const char *region)
{
	// basic sanity check
	assert((ROM != nullptr) && (len > 0));

	// if we are loading from softlist, you have to specify a region
	assert(!loaded_through_softlist() || (region != nullptr));

	if (!loaded_through_softlist())
>>>>>>> upstream/master
		fread(ROM, len);
	else
		memcpy(ROM, get_software_region(region), len);
}

/*-------------------------------------------------
 read_rom
 -------------------------------------------------*/

READ8_MEMBER(generic_slot_device::read_rom)
{
	if (m_cart)
		return m_cart->read_rom(space, offset);
	else
		return 0xff;
}

/*-------------------------------------------------
 read16_rom
 -------------------------------------------------*/

READ16_MEMBER(generic_slot_device::read16_rom)
{
	if (m_cart)
		return m_cart->read16_rom(space, offset, mem_mask);
	else
		return 0xffff;
}

/*-------------------------------------------------
 read32_rom
 -------------------------------------------------*/

READ32_MEMBER(generic_slot_device::read32_rom)
{
	if (m_cart)
		return m_cart->read32_rom(space, offset, mem_mask);
	else
		return 0xffffffff;
}

/*-------------------------------------------------
 read_ram
 -------------------------------------------------*/

READ8_MEMBER(generic_slot_device::read_ram)
{
	if (m_cart)
		return m_cart->read_ram(space, offset);
	else
		return 0xff;
}

/*-------------------------------------------------
 write_ram
 -------------------------------------------------*/

WRITE8_MEMBER(generic_slot_device::write_ram)
{
	if (m_cart)
		m_cart->write_ram(space, offset, data);
}
