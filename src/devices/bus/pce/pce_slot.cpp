// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/***********************************************************************************************************


    PC-Engine / Turbografx-16 cart emulation
    (through slot devices)

 TODO:
   - reimplement cart mirroring in a better way

 ***********************************************************************************************************/


#include "emu.h"
#include "pce_slot.h"

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type PCE_CART_SLOT = &device_creator<pce_cart_slot_device>;
=======
DEFINE_DEVICE_TYPE(PCE_CART_SLOT, pce_cart_slot_device, "pce_cart_slot", "PCE/TG16 Cartridge Slot")
>>>>>>> upstream/master

//**************************************************************************
//    PCE cartridges Interface
//**************************************************************************

//-------------------------------------------------
//  device_pce_cart_interface - constructor
//-------------------------------------------------

device_pce_cart_interface::device_pce_cart_interface(const machine_config &mconfig, device_t &device)
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
//  ~device_pce_cart_interface - destructor
//-------------------------------------------------

device_pce_cart_interface::~device_pce_cart_interface()
{
}

//-------------------------------------------------
//  rom_alloc - alloc the space for the cart
//-------------------------------------------------

<<<<<<< HEAD
void device_pce_cart_interface::rom_alloc(UINT32 size, const char *tag)
{
	if (m_rom == NULL)
=======
void device_pce_cart_interface::rom_alloc(uint32_t size, const char *tag)
{
	if (m_rom == nullptr)
>>>>>>> upstream/master
	{
		m_rom = device().machine().memory().region_alloc(std::string(tag).append(PCESLOT_ROM_REGION_TAG).c_str(), size, 1, ENDIANNESS_LITTLE)->base();
		m_rom_size = size;
	}
}


//-------------------------------------------------
//  ram_alloc - alloc the space for the ram
//-------------------------------------------------

<<<<<<< HEAD
void device_pce_cart_interface::ram_alloc(UINT32 size)
=======
void device_pce_cart_interface::ram_alloc(uint32_t size)
>>>>>>> upstream/master
{
	m_ram.resize(size);
	device().save_item(NAME(m_ram));
}

//-------------------------------------------------
//  rom_map_setup - setup map of rom banks in 128K
//  blocks, so to simplify ROM access to mirror
//-------------------------------------------------

<<<<<<< HEAD
void device_pce_cart_interface::rom_map_setup(UINT32 size)
=======
void device_pce_cart_interface::rom_map_setup(uint32_t size)
>>>>>>> upstream/master
{
	if (size == 0x60000)
	{
		// HuCard 384K are mapped with mirrored pieces
		rom_bank_map[0] = 0;
		rom_bank_map[1] = 1;
		rom_bank_map[2] = 0;
		rom_bank_map[3] = 1;
		rom_bank_map[4] = 2;
		rom_bank_map[5] = 2;
		rom_bank_map[6] = 2;
		rom_bank_map[7] = 2;
	}
	else if (size == 0x30000)
	{
		// 192K images (some demos)
		rom_bank_map[0] = 0;
		rom_bank_map[1] = 1;
		rom_bank_map[2] = 2;
		rom_bank_map[3] = 2;
		rom_bank_map[4] = 0;
		rom_bank_map[5] = 1;
		rom_bank_map[6] = 2;
		rom_bank_map[7] = 2;
	}
	else
	{
		int i;

		// setup the rom_bank_map array to faster ROM read
		for (i = 0; i < size / 0x20000 && i < 8; i++)
			rom_bank_map[i] = i;

		// fill up remaining blocks with mirrors
		while (i % 8)
		{
			int j = 0, repeat_banks;
			while ((i % (8 >> j)) && j < 3)
				j++;
			repeat_banks = i % (8 >> (j - 1));
			for (int k = 0; k < repeat_banks; k++)
				rom_bank_map[i + k] = rom_bank_map[i + k - repeat_banks];
			i += repeat_banks;
		}
	}
	// check bank map!
//  for (i = 0; i < 8; i++)
//  {
//      printf("bank %3d = %3d\t", i, rom_bank_map[i]);
//  }
}


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  pce_cart_slot_device - constructor
//-------------------------------------------------
<<<<<<< HEAD
pce_cart_slot_device::pce_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
						device_t(mconfig, PCE_CART_SLOT, "PCE & TG16 Cartridge Slot", tag, owner, clock, "pce_cart_slot", __FILE__),
						device_image_interface(mconfig, *this),
						device_slot_interface(mconfig, *this),
						m_interface("pce_cart"),
						m_type(PCE_STD), m_cart(nullptr)
=======
pce_cart_slot_device::pce_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, PCE_CART_SLOT, tag, owner, clock),
	device_image_interface(mconfig, *this),
	device_slot_interface(mconfig, *this),
	m_interface("pce_cart"),
	m_type(PCE_STD), m_cart(nullptr)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  pce_cart_slot_device - destructor
//-------------------------------------------------

pce_cart_slot_device::~pce_cart_slot_device()
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void pce_cart_slot_device::device_start()
{
	m_cart = dynamic_cast<device_pce_cart_interface *>(get_card_device());
}

<<<<<<< HEAD
//-------------------------------------------------
//  device_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void pce_cart_slot_device::device_config_complete()
{
	// set brief and instance name
	update_names();
}

=======
>>>>>>> upstream/master

//-------------------------------------------------
//  PCE PCB
//-------------------------------------------------

struct pce_slot
{
	int                     pcb_id;
	const char              *slot_option;
};

// Here, we take the feature attribute from .xml (i.e. the PCB name) and we assign a unique ID to it
static const pce_slot slot_list[] =
{
	{ PCE_STD, "rom" },
	{ PCE_CDSYS3U, "cdsys3u" },
	{ PCE_CDSYS3J, "cdsys3j" },
	{ PCE_POPULOUS, "populous" },
	{ PCE_SF2, "sf2" },
};

static int pce_get_pcb_id(const char *slot)
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

static const char *pce_get_slot(int type)
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

	return "rom";
}


/*-------------------------------------------------
 call load
 -------------------------------------------------*/

<<<<<<< HEAD
bool pce_cart_slot_device::call_load()
{
	if (m_cart)
	{
		UINT32 offset = 0;
		UINT32 len = (software_entry() == NULL) ? length() : get_software_region_length("rom");
		UINT8 *ROM;

		// From fullpath, check for presence of a header and skip it
		if (software_entry() == NULL && (len % 0x4000) == 512)
=======
image_init_result pce_cart_slot_device::call_load()
{
	if (m_cart)
	{
		uint32_t offset;
		uint32_t len = !loaded_through_softlist() ? length() : get_software_region_length("rom");
		uint8_t *ROM;

		// From fullpath, check for presence of a header and skip it
		if (!loaded_through_softlist() && (len % 0x4000) == 512)
>>>>>>> upstream/master
		{
			logerror("Rom-header found, skipping\n");
			offset = 512;
			len -= offset;
			fseek(offset, SEEK_SET);
		}

		m_cart->rom_alloc(len, tag());
		ROM = m_cart->get_rom_base();

<<<<<<< HEAD
		if (software_entry() == NULL)
=======
		if (!loaded_through_softlist())
>>>>>>> upstream/master
			fread(ROM, len);
		else
			memcpy(ROM, get_software_region("rom"), len);

		// check for encryption (US carts)
		if (ROM[0x1fff] < 0xe0)
		{
<<<<<<< HEAD
			UINT8 decrypted[256];
=======
			uint8_t decrypted[256];
>>>>>>> upstream/master

			/* Initialize decryption table */
			for (int i = 0; i < 256; i++)
				decrypted[i] = ((i & 0x01) << 7) | ((i & 0x02) << 5) | ((i & 0x04) << 3) | ((i & 0x08) << 1) | ((i & 0x10) >> 1) | ((i & 0x20 ) >> 3) | ((i & 0x40) >> 5) | ((i & 0x80) >> 7);

			/* Decrypt ROM image */
			for (int i = 0; i < len; i++)
				ROM[i] = decrypted[ROM[i]];
		}

		m_cart->rom_map_setup(len);

<<<<<<< HEAD
		if (software_entry() == NULL)
=======
		if (!loaded_through_softlist())
>>>>>>> upstream/master
			m_type = get_cart_type(ROM, len);
		else
		{
			const char *pcb_name = get_feature("slot");
			if (pcb_name)
				m_type = pce_get_pcb_id(pcb_name);
		}
		//printf("Type: %s\n", pce_get_slot(m_type));

		if (m_type == PCE_POPULOUS)
			m_cart->ram_alloc(0x8000);
		if (m_type == PCE_CDSYS3J || m_type == PCE_CDSYS3U)
			m_cart->ram_alloc(0x30000);

<<<<<<< HEAD
		return IMAGE_INIT_PASS;
	}

	return IMAGE_INIT_PASS;
=======
		return image_init_result::PASS;
	}

	return image_init_result::PASS;
>>>>>>> upstream/master
}


/*-------------------------------------------------
 call_unload
 -------------------------------------------------*/

void pce_cart_slot_device::call_unload()
{
}


/*-------------------------------------------------
<<<<<<< HEAD
 call softlist load
 -------------------------------------------------*/

bool pce_cart_slot_device::call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry)
{
	load_software_part_region(*this, swlist, swname, start_entry);
	return TRUE;
}



/*-------------------------------------------------
=======
>>>>>>> upstream/master
 get_cart_type - code to detect NVRAM type from
 fullpath
 -------------------------------------------------*/

<<<<<<< HEAD
int pce_cart_slot_device::get_cart_type(UINT8 *ROM, UINT32 len)
=======
int pce_cart_slot_device::get_cart_type(const uint8_t *ROM, uint32_t len)
>>>>>>> upstream/master
{
	int type = PCE_STD;

	/* Check for Street fighter 2 */
	if (len == 0x280000)
		type = PCE_SF2;

	/* Check for Populous */
	if (len >= (0x1f26 + 8) && !memcmp(ROM + 0x1f26, "POPULOUS", 8))
		type = PCE_POPULOUS;

	// Check for CD system card v3 which adds on-cart RAM to the system
	if (len >= (0x3ffb6 + 23) && !memcmp(ROM + 0x3ffb6, "PC Engine CD-ROM SYSTEM", 23))
	{
		/* Check if 192KB additional system card ram should be used */
		if (!memcmp(ROM + 0x29d1, "VER. 3.", 7))         { type = PCE_CDSYS3J; } // JP version
		else if (!memcmp(ROM + 0x29c4, "VER. 3.", 7 ))   { type = PCE_CDSYS3U; } // US version
	}

	return type;
}


/*-------------------------------------------------
 get default card software
 -------------------------------------------------*/

<<<<<<< HEAD
void pce_cart_slot_device::get_default_card_software(std::string &result)
{
	if (open_image_file(mconfig().options()))
	{
		const char *slot_string = "rom";
		UINT32 len = core_fsize(m_file);
		dynamic_buffer rom(len);
		int type;

		core_fread(m_file, &rom[0], len);
=======
std::string pce_cart_slot_device::get_default_card_software(get_default_card_software_hook &hook) const
{
	if (hook.image_file())
	{
		const char *slot_string;
		uint32_t len = hook.image_file()->size();
		std::vector<uint8_t> rom(len);
		int type;

		hook.image_file()->read(&rom[0], len);
>>>>>>> upstream/master

		type = get_cart_type(&rom[0], len);
		slot_string = pce_get_slot(type);

		//printf("type: %s\n", slot_string);
<<<<<<< HEAD
		clear();

		result.assign(slot_string);
		return;
	}

	software_get_default_slot(result, "rom");
=======

		return std::string(slot_string);
	}

	return software_get_default_slot("rom");
>>>>>>> upstream/master
}

/*-------------------------------------------------
 read
 -------------------------------------------------*/

READ8_MEMBER(pce_cart_slot_device::read_cart)
{
	if (m_cart)
		return m_cart->read_cart(space, offset);
	else
		return 0xff;
}

/*-------------------------------------------------
 write
 -------------------------------------------------*/

WRITE8_MEMBER(pce_cart_slot_device::write_cart)
{
	if (m_cart)
		m_cart->write_cart(space, offset, data);
}


/*-------------------------------------------------
 Internal header logging
 -------------------------------------------------*/

<<<<<<< HEAD
void pce_cart_slot_device::internal_header_logging(UINT8 *ROM, UINT32 len)
=======
void pce_cart_slot_device::internal_header_logging(uint8_t *ROM, uint32_t len)
>>>>>>> upstream/master
{
}
