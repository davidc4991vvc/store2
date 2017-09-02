// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/***********************************************************************************************************

    Magnavox Odyssey 2 cart emulation
    (through slot devices)

 ***********************************************************************************************************/


#include "emu.h"
#include "slot.h"

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type O2_CART_SLOT = &device_creator<o2_cart_slot_device>;
=======
DEFINE_DEVICE_TYPE(O2_CART_SLOT, o2_cart_slot_device, "o2_cart_slot", "Odyssey 2 Cartridge Slot")
>>>>>>> upstream/master

//**************************************************************************
//    Odyssey 2 Cartridges Interface
//**************************************************************************

//-------------------------------------------------
//  device_o2_cart_interface - constructor
//-------------------------------------------------

device_o2_cart_interface::device_o2_cart_interface(const machine_config &mconfig, device_t &device)
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
//  ~device_o2_cart_interface - destructor
//-------------------------------------------------

device_o2_cart_interface::~device_o2_cart_interface()
{
}

//-------------------------------------------------
//  rom_alloc - alloc the space for the cart
//-------------------------------------------------

<<<<<<< HEAD
void device_o2_cart_interface::rom_alloc(UINT32 size, const char *tag)
{
	if (m_rom == NULL)
=======
void device_o2_cart_interface::rom_alloc(uint32_t size, const char *tag)
{
	if (m_rom == nullptr)
>>>>>>> upstream/master
	{
		m_rom = device().machine().memory().region_alloc(std::string(tag).append(O2SLOT_ROM_REGION_TAG).c_str(), size, 1, ENDIANNESS_LITTLE)->base();
		m_rom_size = size;
	}
}


//-------------------------------------------------
//  ram_alloc - alloc the space for the ram
//-------------------------------------------------

<<<<<<< HEAD
void device_o2_cart_interface::ram_alloc(UINT32 size)
=======
void device_o2_cart_interface::ram_alloc(uint32_t size)
>>>>>>> upstream/master
{
	m_ram.resize(size);
}


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  o2_cart_slot_device - constructor
//-------------------------------------------------
<<<<<<< HEAD
o2_cart_slot_device::o2_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
						device_t(mconfig, O2_CART_SLOT, "Odyssey 2 Cartridge Slot", tag, owner, clock, "o2_cart_slot", __FILE__),
						device_image_interface(mconfig, *this),
						device_slot_interface(mconfig, *this),
						m_type(O2_STD), m_cart(nullptr)
=======
o2_cart_slot_device::o2_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, O2_CART_SLOT, tag, owner, clock)
	, device_image_interface(mconfig, *this)
	, device_slot_interface(mconfig, *this)
	, m_type(O2_STD), m_cart(nullptr)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  o2_cart_slot_device - destructor
//-------------------------------------------------

o2_cart_slot_device::~o2_cart_slot_device()
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void o2_cart_slot_device::device_start()
{
	m_cart = dynamic_cast<device_o2_cart_interface *>(get_card_device());
}

<<<<<<< HEAD
//-------------------------------------------------
//  device_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void o2_cart_slot_device::device_config_complete()
{
	// set brief and instance name
	update_names();
}

=======
>>>>>>> upstream/master

//-------------------------------------------------
//  O2 PCB
//-------------------------------------------------

struct o2_slot
{
	int                     pcb_id;
	const char              *slot_option;
};

// Here, we take the feature attribute from .xml (i.e. the PCB name) and we assign a unique ID to it
static const o2_slot slot_list[] =
{
	{ O2_STD,      "o2_rom" },
	{ O2_ROM12,    "o2_rom12" },
	{ O2_ROM16,    "o2_rom16" },
	{ O2_CHESS,    "o2_chess" },
	{ O2_VOICE,    "o2_voice" }
};

static int o2_get_pcb_id(const char *slot)
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

static const char *o2_get_slot(int type)
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

	return "o2_rom";
}


/*-------------------------------------------------
 call load
 -------------------------------------------------*/

<<<<<<< HEAD
bool o2_cart_slot_device::call_load()
{
	if (m_cart)
	{
		UINT32 size = (software_entry() == NULL) ? length() : get_software_region_length("rom");
		m_cart->rom_alloc(size, tag());

		if (software_entry() == NULL)
=======
image_init_result o2_cart_slot_device::call_load()
{
	if (m_cart)
	{
		uint32_t size = !loaded_through_softlist() ? length() : get_software_region_length("rom");
		m_cart->rom_alloc(size, tag());

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
			m_type = O2_STD;
			if (size == 12288)
				m_type = O2_ROM12;
			if (size == 16384)
				m_type = O2_ROM16;
		}
		else
		{
			const char *pcb_name = get_feature("slot");
			if (pcb_name)
				m_type = o2_get_pcb_id(pcb_name);
		}

		//printf("Type: %s\n", o2_get_slot(m_type));

<<<<<<< HEAD
		return IMAGE_INIT_PASS;
	}

	return IMAGE_INIT_PASS;
}


/*-------------------------------------------------
 call softlist load
 -------------------------------------------------*/

bool o2_cart_slot_device::call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry)
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
void o2_cart_slot_device::get_default_card_software(std::string &result)
{
	if (open_image_file(mconfig().options()))
	{
		const char *slot_string = "o2_rom";
		UINT32 size = core_fsize(m_file);
=======
std::string o2_cart_slot_device::get_default_card_software(get_default_card_software_hook &hook) const
{
	if (hook.image_file())
	{
		const char *slot_string;
		uint32_t size = hook.image_file()->size();
>>>>>>> upstream/master
		int type = O2_STD;

		if (size == 12288)
			type = O2_ROM12;
		if (size == 16384)
			type = O2_ROM16;

		slot_string = o2_get_slot(type);

		//printf("type: %s\n", slot_string);
<<<<<<< HEAD
		clear();

		result.assign(slot_string);
		return;
	}

	software_get_default_slot(result, "o2_rom");
=======

		return std::string(slot_string);
	}

	return software_get_default_slot("o2_rom");
>>>>>>> upstream/master
}

/*-------------------------------------------------
 read_rom**
 -------------------------------------------------*/

READ8_MEMBER(o2_cart_slot_device::read_rom04)
{
	if (m_cart)
		return m_cart->read_rom04(space, offset);
	else
		return 0xff;
}

READ8_MEMBER(o2_cart_slot_device::read_rom0c)
{
	if (m_cart)
		return m_cart->read_rom0c(space, offset);
	else
		return 0xff;
}

/*-------------------------------------------------
 io_write
 -------------------------------------------------*/

WRITE8_MEMBER(o2_cart_slot_device::io_write)
{
	if (m_cart)
		m_cart->io_write(space, offset, data);
}


#include "bus/odyssey2/rom.h"
#include "bus/odyssey2/chess.h"
#include "bus/odyssey2/voice.h"

SLOT_INTERFACE_START(o2_cart)
	SLOT_INTERFACE_INTERNAL("o2_rom",    O2_ROM_STD)
	SLOT_INTERFACE_INTERNAL("o2_rom12",  O2_ROM_12K)
	SLOT_INTERFACE_INTERNAL("o2_rom16",  O2_ROM_16K)
	SLOT_INTERFACE_INTERNAL("o2_chess",  O2_ROM_CHESS)
	SLOT_INTERFACE_INTERNAL("o2_voice",  O2_ROM_VOICE)
SLOT_INTERFACE_END
