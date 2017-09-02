// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
#include "emu.h"
#include "rom.h"


<<<<<<< HEAD
const device_type MSX_SLOT_ROM = &device_creator<msx_slot_rom_device>;


msx_slot_rom_device::msx_slot_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MSX_SLOT_ROM, "MSX Internal ROM", tag, owner, clock, "msx_slot_rom", __FILE__)
	, msx_internal_slot_interface()
	, m_region(NULL)
	, m_region_offset(0)
	, m_rom(NULL)
=======
DEFINE_DEVICE_TYPE(MSX_SLOT_ROM, msx_slot_rom_device, "msx_slot_rom", "MSX Internal ROM")


msx_slot_rom_device::msx_slot_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: msx_slot_rom_device(mconfig, MSX_SLOT_ROM, tag, owner, clock)
>>>>>>> upstream/master
{
}


<<<<<<< HEAD
msx_slot_rom_device::msx_slot_rom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source)
	: device_t(mconfig, type, name, tag, owner, clock, shortname, source)
	, msx_internal_slot_interface()
	, m_region(NULL)
	, m_region_offset(0)
	, m_rom(NULL)
=======
msx_slot_rom_device::msx_slot_rom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, type, tag, owner, clock)
	, msx_internal_slot_interface()
	, m_rom_region(*this, finder_base::DUMMY_TAG)
	, m_region_offset(0)
	, m_rom(nullptr)
>>>>>>> upstream/master
{
}


<<<<<<< HEAD
void msx_slot_rom_device::set_rom_start(device_t &device, const char *region, UINT32 offset)
{
	msx_slot_rom_device &dev = downcast<msx_slot_rom_device &>(device);

	dev.m_region = region;
=======
void msx_slot_rom_device::set_rom_start(device_t &device, const char *region, uint32_t offset)
{
	msx_slot_rom_device &dev = downcast<msx_slot_rom_device &>(device);

	dev.m_rom_region.set_tag(region);
>>>>>>> upstream/master
	dev.m_region_offset = offset;
}


void msx_slot_rom_device::device_start()
{
<<<<<<< HEAD
	assert(m_region != NULL );

	memory_region *m_rom_region = owner()->memregion(m_region);

	// Sanity checks
	if (m_rom_region == NULL )
	{
		fatalerror("Rom slot '%s': Unable to find memory region '%s'\n", tag(), m_region);
	}
	if (m_rom_region->bytes() < m_region_offset + m_size)
	{
		fatalerror("Memory region '%s' is too small for rom slot '%s'\n", m_region, tag());
=======
	// Sanity checks
	if (m_rom_region->bytes() < m_region_offset + m_size)
	{
		fatalerror("Memory region '%s' is too small for rom slot '%s'\n", m_rom_region.finder_tag(), tag());
>>>>>>> upstream/master
	}

	m_rom = m_rom_region->base() + m_region_offset;
}


READ8_MEMBER(msx_slot_rom_device::read)
{
	if ( offset >= m_start_address && offset < m_end_address )
	{
		return m_rom[ offset - m_start_address ];
	}
	return 0xFF;
}
