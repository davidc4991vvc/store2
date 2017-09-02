// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Sinclair QL ROM cartridge port emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "rom.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type QL_ROM_CARTRIDGE_SLOT = &device_creator<ql_rom_cartridge_slot_t>;
=======
DEFINE_DEVICE_TYPE(QL_ROM_CARTRIDGE_SLOT, ql_rom_cartridge_slot_device, "ql_rom_cartridge_slot", "QL ROM cartridge slot")
>>>>>>> upstream/master



//**************************************************************************
//  CARD INTERFACE
//**************************************************************************

//-------------------------------------------------
//  device_ql_rom_cartridge_card_interface - constructor
//-------------------------------------------------

device_ql_rom_cartridge_card_interface::device_ql_rom_cartridge_card_interface(const machine_config &mconfig, device_t &device) :
	device_slot_card_interface(mconfig, device),
	m_rom(*this, "rom"),
	m_romoeh(0)
{
<<<<<<< HEAD
	m_slot = dynamic_cast<ql_rom_cartridge_slot_t *>(device.owner());
=======
	m_slot = dynamic_cast<ql_rom_cartridge_slot_device *>(device.owner());
>>>>>>> upstream/master
}


//-------------------------------------------------
//  ~device_ql_rom_cartridge_card_interface - destructor
//-------------------------------------------------

device_ql_rom_cartridge_card_interface::~device_ql_rom_cartridge_card_interface()
{
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  ql_rom_cartridge_slot_t - constructor
//-------------------------------------------------

ql_rom_cartridge_slot_t::ql_rom_cartridge_slot_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, QL_ROM_CARTRIDGE_SLOT, "QL ROM cartridge slot", tag, owner, clock, "ql_rom_cartridge_slot", __FILE__),
=======
//  ql_rom_cartridge_slot_device - constructor
//-------------------------------------------------

ql_rom_cartridge_slot_device::ql_rom_cartridge_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, QL_ROM_CARTRIDGE_SLOT, tag, owner, clock),
>>>>>>> upstream/master
	device_slot_interface(mconfig, *this),
	device_image_interface(mconfig, *this), m_card(nullptr)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void ql_rom_cartridge_slot_t::device_start()
=======
void ql_rom_cartridge_slot_device::device_start()
>>>>>>> upstream/master
{
	m_card = dynamic_cast<device_ql_rom_cartridge_card_interface *>(get_card_device());
}


//-------------------------------------------------
//  call_load -
//-------------------------------------------------

<<<<<<< HEAD
bool ql_rom_cartridge_slot_t::call_load()
{
	if (m_card)
	{
		size_t size = 0;

		if (software_entry() == NULL)
=======
image_init_result ql_rom_cartridge_slot_device::call_load()
{
	if (m_card)
	{
		size_t size;

		if (!loaded_through_softlist())
>>>>>>> upstream/master
		{
			size = length();

			m_card->m_rom.allocate(size);
			fread(m_card->m_rom, size);
		}
		else
		{
			load_software_region("rom", m_card->m_rom);
		}
	}

<<<<<<< HEAD
	return IMAGE_INIT_PASS;
}


//-------------------------------------------------
//  call_softlist_load -
//-------------------------------------------------

bool ql_rom_cartridge_slot_t::call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry)
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
void ql_rom_cartridge_slot_t::get_default_card_software(std::string &result)
{
	software_get_default_slot(result, "standard");
=======
std::string ql_rom_cartridge_slot_device::get_default_card_software(get_default_card_software_hook &hook) const
{
	return software_get_default_slot("standard");
>>>>>>> upstream/master
}


//-------------------------------------------------
//  SLOT_INTERFACE( ql_rom_cartridge_cards )
//-------------------------------------------------

// slot devices
#include "miracle_hd.h"
#include "std.h"

SLOT_INTERFACE_START( ql_rom_cartridge_cards )
	SLOT_INTERFACE("mhd", MIRACLE_HARD_DISK)

	// the following need ROMs from the software list
	SLOT_INTERFACE_INTERNAL("standard", QL_STANDARD_ROM_CARTRIDGE)
SLOT_INTERFACE_END
