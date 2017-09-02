// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/***********************************************************************************************************

    GCE Vectrex cart emulation
    (through slot devices)

 ***********************************************************************************************************/


#include "emu.h"
#include "slot.h"

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type VECTREX_CART_SLOT = &device_creator<vectrex_cart_slot_device>;
=======
DEFINE_DEVICE_TYPE(VECTREX_CART_SLOT, vectrex_cart_slot_device, "vectrex_cart_slot", "GCE Vectrex Cartridge Slot")
>>>>>>> upstream/master

//**************************************************************************
//    Vectrex Cartridges Interface
//**************************************************************************

//-------------------------------------------------
//  device_vectrex_cart_interface - constructor
//-------------------------------------------------

device_vectrex_cart_interface::device_vectrex_cart_interface(const machine_config &mconfig, device_t &device)
	: device_slot_card_interface(mconfig, device),
<<<<<<< HEAD
		m_rom(NULL),
=======
		m_rom(nullptr),
>>>>>>> upstream/master
		m_rom_size(0)
{
}


//-------------------------------------------------
//  ~device_vectrex_cart_interface - destructor
//-------------------------------------------------

device_vectrex_cart_interface::~device_vectrex_cart_interface()
{
}

//-------------------------------------------------
//  rom_alloc - alloc the space for the cart
//-------------------------------------------------

<<<<<<< HEAD
void device_vectrex_cart_interface::rom_alloc(UINT32 size, const char *tag)
{
	if (m_rom == NULL)
=======
void device_vectrex_cart_interface::rom_alloc(uint32_t size, const char *tag)
{
	if (m_rom == nullptr)
>>>>>>> upstream/master
	{
		m_rom = device().machine().memory().region_alloc(std::string(tag).append(VECSLOT_ROM_REGION_TAG).c_str(), size, 1, ENDIANNESS_LITTLE)->base();
		m_rom_size = size;
	}
}


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  vectrex_cart_slot_device - constructor
//-------------------------------------------------
<<<<<<< HEAD
vectrex_cart_slot_device::vectrex_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
						device_t(mconfig, VECTREX_CART_SLOT, "GCE Vectrex Cartridge Slot", tag, owner, clock, "vectrex_cart_slot", __FILE__),
						device_image_interface(mconfig, *this),
						device_slot_interface(mconfig, *this),
						m_type(VECTREX_STD),
						m_vec3d(VEC3D_NONE), m_cart(nullptr)
=======
vectrex_cart_slot_device::vectrex_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, VECTREX_CART_SLOT, tag, owner, clock),
	device_image_interface(mconfig, *this),
	device_slot_interface(mconfig, *this),
	m_type(VECTREX_STD),
	m_vec3d(VEC3D_NONE),
	m_cart(nullptr)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  vectrex_cart_slot_device - destructor
//-------------------------------------------------

vectrex_cart_slot_device::~vectrex_cart_slot_device()
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void vectrex_cart_slot_device::device_start()
{
	m_cart = dynamic_cast<device_vectrex_cart_interface *>(get_card_device());
}

<<<<<<< HEAD
//-------------------------------------------------
//  device_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void vectrex_cart_slot_device::device_config_complete()
{
	// set brief and instance name
	update_names();
}

=======
>>>>>>> upstream/master

//-------------------------------------------------
//  Vectrex PCB
//-------------------------------------------------

struct vectrex_slot
{
	int                     pcb_id;
	const char              *slot_option;
};

// Here, we take the feature attribute from .xml (i.e. the PCB name) and we assign a unique ID to it
static const vectrex_slot slot_list[] =
{
	{ VECTREX_STD,    "vec_rom" },
	{ VECTREX_64K,    "vec_rom64k" },
	{ VECTREX_SRAM,   "vec_sram" }
};

#if 0
static int vectrex_get_pcb_id(const char *slot)
{
	for (int i = 0; i < ARRAY_LENGTH(slot_list); i++)
	{
		if (!core_stricmp(slot_list[i].slot_option, slot))
			return slot_list[i].pcb_id;
	}

	return 0;
}
#endif

static const char *vectrex_get_slot(int type)
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

	return "vec_rom";
}

/*-------------------------------------------------
 call load
 -------------------------------------------------*/

<<<<<<< HEAD
bool vectrex_cart_slot_device::call_load()
{
	if (m_cart)
	{
		UINT32 size = (software_entry() == NULL) ? length() : get_software_region_length("rom");
		UINT8 *ROM;
=======
image_init_result vectrex_cart_slot_device::call_load()
{
	if (m_cart)
	{
		uint32_t size = !loaded_through_softlist() ? length() : get_software_region_length("rom");
		uint8_t *ROM;
>>>>>>> upstream/master

		if (size > 0x10000)
		{
			seterror(IMAGE_ERROR_UNSPECIFIED, "Unsupported cartridge size");
<<<<<<< HEAD
			return IMAGE_INIT_FAIL;
=======
			return image_init_result::FAIL;
>>>>>>> upstream/master
		}

		m_cart->rom_alloc((size < 0x1000) ? 0x1000 : size, tag());
		ROM = m_cart->get_rom_base();

<<<<<<< HEAD
		if (software_entry() == NULL)
=======
		if (!loaded_through_softlist())
>>>>>>> upstream/master
			fread(ROM, size);
		else
			memcpy(ROM, get_software_region("rom"), size);

		// Verify the file is accepted by the Vectrex bios
		if (memcmp(ROM, "g GCE", 5))
		{
			seterror(IMAGE_ERROR_UNSPECIFIED, "Invalid image");
<<<<<<< HEAD
			return IMAGE_INIT_FAIL;
=======
			return image_init_result::FAIL;
>>>>>>> upstream/master
		}

		// determine type
		m_type = VECTREX_STD;
		if (!memcmp(ROM + 0x06, "SRAM", 4))
			m_type = VECTREX_SRAM;
		if (size > 0x8000)
			m_type = VECTREX_64K;

		//printf("Type: %s\n", vectrex_get_slot(m_type));

		// determine 3D setup (to help video setup at machine_start)
		if (!memcmp(ROM + 0x11, "NARROW", 6) && (ROM[0x39] == 0x0c))
			m_vec3d = VEC3D_NARROW;

		if (!memcmp(ROM + 0x11, "CRAZY COASTER", 13))
			m_vec3d = VEC3D_CCOAST;

		if (!memcmp(ROM + 0x11, "3D MINE STORM", 13))
			m_vec3d = VEC3D_MINEST;

<<<<<<< HEAD
		return IMAGE_INIT_PASS;
	}

	return IMAGE_INIT_PASS;
}


/*-------------------------------------------------
 call softlist load
 -------------------------------------------------*/

bool vectrex_cart_slot_device::call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry)
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
void vectrex_cart_slot_device::get_default_card_software(std::string &result)
{
	if (open_image_file(mconfig().options()))
	{
		const char *slot_string = "vec_rom";
		UINT32 size = core_fsize(m_file);
		dynamic_buffer rom(size);
		int type = VECTREX_STD;

		core_fread(m_file, &rom[0], size);
=======
std::string vectrex_cart_slot_device::get_default_card_software(get_default_card_software_hook &hook) const
{
	if (hook.image_file())
	{
		const char *slot_string;
		uint32_t size = hook.image_file()->size();
		std::vector<uint8_t> rom(size);
		int type = VECTREX_STD;

		hook.image_file()->read(&rom[0], size);
>>>>>>> upstream/master

		if (!memcmp(&rom[0x06], "SRAM", 4))
			type = VECTREX_SRAM;
		if (size > 0x8000)
			type = VECTREX_64K;

		slot_string = vectrex_get_slot(type);

		//printf("type: %s\n", slot_string);
<<<<<<< HEAD
		clear();

		result.assign(slot_string);
		return;
	}

	software_get_default_slot(result, "vec_rom");
=======

		return std::string(slot_string);
	}

	return software_get_default_slot("vec_rom");
>>>>>>> upstream/master
}

/*-------------------------------------------------
 read_rom
 -------------------------------------------------*/

READ8_MEMBER(vectrex_cart_slot_device::read_rom)
{
	if (m_cart)
		return m_cart->read_rom(space, offset);
	else
		return 0xff;
}

/*-------------------------------------------------
 write_ram
 -------------------------------------------------*/

WRITE8_MEMBER(vectrex_cart_slot_device::write_ram)
{
	if (m_cart)
		m_cart->write_ram(space, offset, data);
}

/*-------------------------------------------------
 write_bank
 -------------------------------------------------*/

WRITE8_MEMBER(vectrex_cart_slot_device::write_bank)
{
	if (m_cart)
		m_cart->write_bank(space, offset, data);
}
