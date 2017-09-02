// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore VIC-10 Expansion Port emulation

**********************************************************************/

#include "emu.h"
#include "emuopts.h"
#include "exp.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type VIC10_EXPANSION_SLOT = &device_creator<vic10_expansion_slot_device>;
=======
DEFINE_DEVICE_TYPE(VIC10_EXPANSION_SLOT, vic10_expansion_slot_device, "vic10_expansion_slot", "VIC-10 expansion port")
>>>>>>> upstream/master



//**************************************************************************
//  DEVICE VIC10_EXPANSION CARD INTERFACE
//**************************************************************************

//-------------------------------------------------
//  device_vic10_expansion_card_interface - constructor
//-------------------------------------------------

device_vic10_expansion_card_interface::device_vic10_expansion_card_interface(const machine_config &mconfig, device_t &device)
	: device_slot_card_interface(mconfig,device),
		m_lorom(*this, "lorom"),
		m_exram(*this, "exram"),
		m_uprom(*this, "uprom")
{
	m_slot = dynamic_cast<vic10_expansion_slot_device *>(device.owner());
}


//-------------------------------------------------
//  ~device_vic10_expansion_card_interface - destructor
//-------------------------------------------------

device_vic10_expansion_card_interface::~device_vic10_expansion_card_interface()
{
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  vic10_expansion_slot_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
vic10_expansion_slot_device::vic10_expansion_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
		device_t(mconfig, VIC10_EXPANSION_SLOT, "VIC-10 expansion port", tag, owner, clock, "vic10_expansion_slot", __FILE__),
		device_slot_interface(mconfig, *this),
		device_image_interface(mconfig, *this),
		m_write_irq(*this),
		m_write_res(*this),
		m_write_cnt(*this),
		m_write_sp(*this), m_card(nullptr)
=======
vic10_expansion_slot_device::vic10_expansion_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, VIC10_EXPANSION_SLOT, tag, owner, clock),
	device_slot_interface(mconfig, *this),
	device_image_interface(mconfig, *this),
	m_write_irq(*this),
	m_write_res(*this),
	m_write_cnt(*this),
	m_write_sp(*this),
	m_card(nullptr)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void vic10_expansion_slot_device::device_start()
{
	m_card = dynamic_cast<device_vic10_expansion_card_interface *>(get_card_device());

	// resolve callbacks
	m_write_irq.resolve_safe();
	m_write_res.resolve_safe();
	m_write_cnt.resolve_safe();
	m_write_sp.resolve_safe();

	// inherit bus clock
	if (clock() == 0)
	{
		vic10_expansion_slot_device *root = machine().device<vic10_expansion_slot_device>(VIC10_EXPANSION_SLOT_TAG);
		assert(root);
		set_unscaled_clock(root->clock());
	}
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void vic10_expansion_slot_device::device_reset()
{
	if (get_card_device())
	{
		get_card_device()->reset();
	}
}


//-------------------------------------------------
//  call_load -
//-------------------------------------------------

<<<<<<< HEAD
bool vic10_expansion_slot_device::call_load()
{
	if (m_card)
	{
		size_t size = 0;

		if (software_entry() == NULL)
		{
			size = length();

			if (!core_stricmp(filetype(), "80"))
=======
image_init_result vic10_expansion_slot_device::call_load()
{
	if (m_card)
	{
		size_t size;

		if (!loaded_through_softlist())
		{
			size = length();

			if (is_filetype("80"))
>>>>>>> upstream/master
			{
				fread(m_card->m_lorom, 0x2000);

				if (size == 0x4000)
				{
					fread(m_card->m_uprom, 0x2000);
				}
			}
<<<<<<< HEAD
			else if (!core_stricmp(filetype(), "e0"))
			{
				fread(m_card->m_uprom, size);
			}
			else if (!core_stricmp(filetype(), "crt"))
=======
			else if (is_filetype("e0"))
			{
				fread(m_card->m_uprom, size);
			}
			else if (is_filetype("crt"))
>>>>>>> upstream/master
			{
				size_t roml_size = 0;
				size_t romh_size = 0;
				int exrom = 1;
				int game = 1;

<<<<<<< HEAD
				if (cbm_crt_read_header(m_file, &roml_size, &romh_size, &exrom, &game))
				{
					UINT8 *roml = NULL;
					UINT8 *romh = NULL;
=======
				if (cbm_crt_read_header(image_core_file(), &roml_size, &romh_size, &exrom, &game))
				{
					uint8_t *roml = nullptr;
					uint8_t *romh = nullptr;
>>>>>>> upstream/master

					m_card->m_lorom.allocate(roml_size);
					m_card->m_uprom.allocate(romh_size);

					if (roml_size) roml = m_card->m_lorom;
					if (romh_size) romh = m_card->m_lorom;

<<<<<<< HEAD
					cbm_crt_read_data(m_file, roml, romh);
=======
					cbm_crt_read_data(image_core_file(), roml, romh);
>>>>>>> upstream/master
				}
			}
		}
		else
		{
			load_software_region("lorom", m_card->m_lorom);
			load_software_region("exram", m_card->m_exram);
			load_software_region("uprom", m_card->m_uprom);
		}
	}

<<<<<<< HEAD
	return IMAGE_INIT_PASS;
}


//-------------------------------------------------
//  call_softlist_load -
//-------------------------------------------------

bool vic10_expansion_slot_device::call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry)
{
	load_software_part_region(*this, swlist, swname, start_entry);

	return true;
=======
	return image_init_result::PASS;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  get_default_card_software -
//-------------------------------------------------

<<<<<<< HEAD
void vic10_expansion_slot_device::get_default_card_software(std::string &result)
{
	if (open_image_file(mconfig().options()))
	{
		if (!core_stricmp(filetype(), "crt"))
		{
			cbm_crt_get_card(result, m_file);
			return;
		}

		clear();
	}

	software_get_default_slot(result, "standard");
=======
std::string vic10_expansion_slot_device::get_default_card_software(get_default_card_software_hook &hook) const
{
	if (hook.image_file())
	{
		if (hook.is_filetype("crt"))
			return cbm_crt_get_card(*hook.image_file());
	}

	return software_get_default_slot("standard");
>>>>>>> upstream/master
}


//-------------------------------------------------
//  cd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 vic10_expansion_slot_device::cd_r(address_space &space, offs_t offset, UINT8 data, int lorom, int uprom, int exram)
{
	if (m_card != NULL)
=======
uint8_t vic10_expansion_slot_device::cd_r(address_space &space, offs_t offset, uint8_t data, int lorom, int uprom, int exram)
{
	if (m_card != nullptr)
>>>>>>> upstream/master
	{
		data = m_card->vic10_cd_r(space, offset, data, lorom, uprom, exram);
	}

	return data;
}


//-------------------------------------------------
//  cd_w - cartridge data write
//-------------------------------------------------

<<<<<<< HEAD
void vic10_expansion_slot_device::cd_w(address_space &space, offs_t offset, UINT8 data, int lorom, int uprom, int exram)
{
	if (m_card != NULL)
=======
void vic10_expansion_slot_device::cd_w(address_space &space, offs_t offset, uint8_t data, int lorom, int uprom, int exram)
{
	if (m_card != nullptr)
>>>>>>> upstream/master
	{
		m_card->vic10_cd_w(space, offset, data, lorom, uprom, exram);
	}
}

<<<<<<< HEAD
READ_LINE_MEMBER( vic10_expansion_slot_device::p0_r ) { int state = 0; if (m_card != NULL) state = m_card->vic10_p0_r(); return state; }
WRITE_LINE_MEMBER( vic10_expansion_slot_device::p0_w ) { if (m_card != NULL) m_card->vic10_p0_w(state); }
=======
READ_LINE_MEMBER( vic10_expansion_slot_device::p0_r ) { int state = 0; if (m_card != nullptr) state = m_card->vic10_p0_r(); return state; }
WRITE_LINE_MEMBER( vic10_expansion_slot_device::p0_w ) { if (m_card != nullptr) m_card->vic10_p0_w(state); }
>>>>>>> upstream/master


//-------------------------------------------------
//  SLOT_INTERFACE( vic10_expansion_cards )
//-------------------------------------------------

// slot devices
#include "std.h"

SLOT_INTERFACE_START( vic10_expansion_cards )
	// the following need ROMs from the software list
	SLOT_INTERFACE_INTERNAL("standard", VIC10_STD)
SLOT_INTERFACE_END
