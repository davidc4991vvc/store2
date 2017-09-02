// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/***********************************************************************************************************

    Interton Electronic VC 4000 cart emulation
    (through slot devices)

 ***********************************************************************************************************/


#include "emu.h"
#include "slot.h"

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type VC4000_CART_SLOT = &device_creator<vc4000_cart_slot_device>;
=======
DEFINE_DEVICE_TYPE(VC4000_CART_SLOT, vc4000_cart_slot_device, "vc4000_cart_slot", "Interton VC 4000 Cartridge Slot")
DEFINE_DEVICE_TYPE(H21_CART_SLOT,    h21_cart_slot_device,    "h21_cart_slot",    "TRQ H-21 Cartridge Slot")
>>>>>>> upstream/master

//**************************************************************************
//    VC4000 Cartridges Interface
//**************************************************************************

//-------------------------------------------------
//  device_vc4000_cart_interface - constructor
//-------------------------------------------------

device_vc4000_cart_interface::device_vc4000_cart_interface(const machine_config &mconfig, device_t &device)
<<<<<<< HEAD
	: device_slot_card_interface(mconfig, device),
		m_rom(NULL),
		m_rom_size(0)
=======
	: device_slot_card_interface(mconfig, device)
	, m_rom(nullptr)
	, m_rom_size(0)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  ~device_vc4000_cart_interface - destructor
//-------------------------------------------------

device_vc4000_cart_interface::~device_vc4000_cart_interface()
{
}

//-------------------------------------------------
//  rom_alloc - alloc the space for the cart
//-------------------------------------------------

<<<<<<< HEAD
void device_vc4000_cart_interface::rom_alloc(UINT32 size, const char *tag)
{
	if (m_rom == NULL)
=======
void device_vc4000_cart_interface::rom_alloc(uint32_t size, const char *tag)
{
	if (m_rom == nullptr)
>>>>>>> upstream/master
	{
		m_rom = device().machine().memory().region_alloc(std::string(tag).append(VC4000SLOT_ROM_REGION_TAG).c_str(), size, 1, ENDIANNESS_LITTLE)->base();
		m_rom_size = size;
	}
}


//-------------------------------------------------
//  ram_alloc - alloc the space for the ram
//-------------------------------------------------

<<<<<<< HEAD
void device_vc4000_cart_interface::ram_alloc(UINT32 size)
=======
void device_vc4000_cart_interface::ram_alloc(uint32_t size)
>>>>>>> upstream/master
{
	m_ram.resize(size);
}


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  vc4000_cart_slot_device - constructor
//-------------------------------------------------
<<<<<<< HEAD
vc4000_cart_slot_device::vc4000_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
						device_t(mconfig, VC4000_CART_SLOT, "Interton VC 4000 Cartridge Slot", tag, owner, clock, "vc4000_cart_slot", __FILE__),
						device_image_interface(mconfig, *this),
						device_slot_interface(mconfig, *this),
						m_type(VC4000_STD), m_cart(nullptr)
=======
vc4000_cart_slot_device::vc4000_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: vc4000_cart_slot_device(mconfig, VC4000_CART_SLOT, tag, owner, clock)
{
}

vc4000_cart_slot_device::vc4000_cart_slot_device(
		const machine_config &mconfig,
		device_type type,
		const char *tag,
		device_t *owner,
		uint32_t clock)
	: device_t(mconfig, type, tag, owner, clock)
	, device_image_interface(mconfig, *this)
	, device_slot_interface(mconfig, *this)
	, m_type(VC4000_STD)
	, m_cart(nullptr)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  vc4000_cart_slot_device - destructor
//-------------------------------------------------

vc4000_cart_slot_device::~vc4000_cart_slot_device()
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void vc4000_cart_slot_device::device_start()
{
	m_cart = dynamic_cast<device_vc4000_cart_interface *>(get_card_device());
}

//-------------------------------------------------
<<<<<<< HEAD
//  device_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void vc4000_cart_slot_device::device_config_complete()
{
	// set brief and instance name
	update_names();
}

=======
//  trq h-21 slot
//-------------------------------------------------

h21_cart_slot_device::h21_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: vc4000_cart_slot_device(mconfig, H21_CART_SLOT, tag, owner, clock)
{
}

h21_cart_slot_device::~h21_cart_slot_device()
{
}
>>>>>>> upstream/master

//-------------------------------------------------
//  VC4000 PCB
//-------------------------------------------------

struct vc4000_slot
{
	int                     pcb_id;
	const char              *slot_option;
};

// Here, we take the feature attribute from .xml (i.e. the PCB name) and we assign a unique ID to it
static const vc4000_slot slot_list[] =
{
	{ VC4000_STD,     "std" },
	{ VC4000_ROM4K,   "rom4k" },
	{ VC4000_RAM1K,   "ram1k" },
	{ VC4000_CHESS2,  "chess2" }
};

static int vc4000_get_pcb_id(const char *slot)
{
<<<<<<< HEAD
	for (int i = 0; i < ARRAY_LENGTH(slot_list); i++)
	{
		if (!core_stricmp(slot_list[i].slot_option, slot))
			return slot_list[i].pcb_id;
=======
	for (auto & elem : slot_list)
	{
		if (!core_stricmp(elem.slot_option, slot))
			return elem.pcb_id;
>>>>>>> upstream/master
	}

	return 0;
}

static const char *vc4000_get_slot(int type)
{
<<<<<<< HEAD
	for (int i = 0; i < ARRAY_LENGTH(slot_list); i++)
	{
		if (slot_list[i].pcb_id == type)
			return slot_list[i].slot_option;
=======
	for (auto & elem : slot_list)
	{
		if (elem.pcb_id == type)
			return elem.slot_option;
>>>>>>> upstream/master
	}

	return "std";
}


/*-------------------------------------------------
 call load
 -------------------------------------------------*/

<<<<<<< HEAD
bool vc4000_cart_slot_device::call_load()
{
	if (m_cart)
	{
		UINT32 size = (software_entry() == NULL) ? length() : get_software_region_length("rom");
=======
image_init_result vc4000_cart_slot_device::call_load()
{
	if (m_cart)
	{
		uint32_t size = !loaded_through_softlist() ? length() : get_software_region_length("rom");
>>>>>>> upstream/master

		if (size > 0x1800)
		{
			seterror(IMAGE_ERROR_UNSPECIFIED, "Image extends beyond the expected size for a VC4000 cart");
<<<<<<< HEAD
			return IMAGE_INIT_FAIL;
=======
			return image_init_result::FAIL;
>>>>>>> upstream/master
		}

		m_cart->rom_alloc(size, tag());

<<<<<<< HEAD
		if (software_entry() == NULL)
=======
		if (!loaded_through_softlist())
>>>>>>> upstream/master
			fread(m_cart->get_rom_base(), size);
		else
			memcpy(m_cart->get_rom_base(), get_software_region("rom"), size);

<<<<<<< HEAD
		if (software_entry() == NULL)
=======
		if (!loaded_through_softlist())
>>>>>>> upstream/master
		{
			m_type = VC4000_STD;
			// attempt to identify the non-standard types
			if (size > 0x1000)  // 6k rom + 1k ram - Chess2 only
				m_type = VC4000_CHESS2;
			else if (size > 0x0800) // some 4k roms have 1k of mirrored ram (those who don't still work with RAM emulated luckily)
				m_type = VC4000_RAM1K;

			if (m_type == VC4000_RAM1K || m_type == VC4000_CHESS2)
				m_cart->ram_alloc(0x400);
		}
		else
		{
			const char *pcb_name = get_feature("slot");
			if (pcb_name)
				m_type = vc4000_get_pcb_id(pcb_name);

			if (get_software_region("ram"))
				m_cart->ram_alloc(get_software_region_length("ram"));
		}

		//printf("Type: %s\n", vc4000_get_slot(m_type));

<<<<<<< HEAD
		return IMAGE_INIT_PASS;
	}

	return IMAGE_INIT_PASS;
}


/*-------------------------------------------------
 call softlist load
 -------------------------------------------------*/

bool vc4000_cart_slot_device::call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry)
{
	load_software_part_region(*this, swlist, swname, start_entry);
	return TRUE;
=======
		return image_init_result::PASS;
	}

	return image_init_result::PASS;
>>>>>>> upstream/master
}


/*-------------------------------------------------
 get default card software
 -------------------------------------------------*/

<<<<<<< HEAD
void vc4000_cart_slot_device::get_default_card_software(std::string &result)
{
	if (open_image_file(mconfig().options()))
	{
		const char *slot_string = "std";
		UINT32 size = core_fsize(m_file);
=======
std::string vc4000_cart_slot_device::get_default_card_software(get_default_card_software_hook &hook) const
{
	if (hook.image_file())
	{
		const char *slot_string;
		uint32_t size = hook.image_file()->size();
>>>>>>> upstream/master
		int type = VC4000_STD;

		// attempt to identify the non-standard types
		if (size > 0x1000)  // 6k rom + 1k ram - Chess2 only
			type = VC4000_CHESS2;
		else if (size > 0x0800) // some 4k roms have 1k of mirrored ram
			type = VC4000_RAM1K;

		slot_string = vc4000_get_slot(type);

		//printf("type: %s\n", slot_string);
<<<<<<< HEAD
		clear();

		result.assign(slot_string);
		return;
	}

	software_get_default_slot(result, "std");
=======

		return std::string(slot_string);
	}

	return software_get_default_slot("std");
>>>>>>> upstream/master
}

/*-------------------------------------------------
 read
 -------------------------------------------------*/

READ8_MEMBER(vc4000_cart_slot_device::read_rom)
{
	if (m_cart)
		return m_cart->read_rom(space, offset);
	else
		return 0xff;
}

/*-------------------------------------------------
 read
 -------------------------------------------------*/

READ8_MEMBER(vc4000_cart_slot_device::extra_rom)
{
	if (m_cart)
		return m_cart->extra_rom(space, offset);
	else
		return 0xff;
}

/*-------------------------------------------------
 read
 -------------------------------------------------*/

READ8_MEMBER(vc4000_cart_slot_device::read_ram)
{
	if (m_cart)
		return m_cart->read_ram(space, offset);
	else
		return 0xff;
}

/*-------------------------------------------------
 write
 -------------------------------------------------*/

WRITE8_MEMBER(vc4000_cart_slot_device::write_ram)
{
	if (m_cart)
		m_cart->write_ram(space, offset, data);
}
