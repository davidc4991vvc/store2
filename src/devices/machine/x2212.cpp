// license:BSD-3-Clause
// copyright-holders:smf,Barry Rodewald
/***************************************************************************

    x2212.c

    Xicor X2212 256 x 4 bit Nonvolatile Static RAM.

***************************************************************************/

#include "emu.h"
#include "machine/x2212.h"


//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
static ADDRESS_MAP_START( x2212_sram_map, AS_0, 8, x2212_device )
	AM_RANGE(0x0000, 0x00ff) AM_RAM
ADDRESS_MAP_END

static ADDRESS_MAP_START( x2212_e2prom_map, AS_1, 8, x2212_device )
=======
static ADDRESS_MAP_START( x2212_sram_map, 0, 8, x2212_device )
	AM_RANGE(0x0000, 0x00ff) AM_RAM
ADDRESS_MAP_END

static ADDRESS_MAP_START( x2212_e2prom_map, 1, 8, x2212_device )
>>>>>>> upstream/master
	AM_RANGE(0x0000, 0x00ff) AM_RAM
ADDRESS_MAP_END



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

// device type definition
<<<<<<< HEAD
const device_type X2212 = &device_creator<x2212_device>;
const device_type X2210 = &device_creator<x2210_device>;
=======
DEFINE_DEVICE_TYPE(X2212, x2212_device, "x2212", "Xicor X2212 256x4 NVRAM")
DEFINE_DEVICE_TYPE(X2210, x2210_device, "x2210", "Xicor X2210 64x4 NVRAM")
>>>>>>> upstream/master

//-------------------------------------------------
//  x2212_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
x2212_device::x2212_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, X2212, "X2212 NVRAM", tag, owner, clock, "x2212", __FILE__),
		device_memory_interface(mconfig, *this),
		device_nvram_interface(mconfig, *this),
		m_auto_save(false),
		m_sram_space_config("SRAM", ENDIANNESS_BIG, 8, 8, 0, *ADDRESS_MAP_NAME(x2212_sram_map)),
		m_e2prom_space_config("E2PROM", ENDIANNESS_BIG, 8, 8, 0, *ADDRESS_MAP_NAME(x2212_e2prom_map)),
		m_store(false),
		m_array_recall(false)
{
}

x2212_device::x2212_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source)
	: device_t(mconfig, type, name, tag, owner, clock, shortname, source),
		device_memory_interface(mconfig, *this),
		device_nvram_interface(mconfig, *this),
		m_auto_save(false),
		m_sram_space_config("SRAM", ENDIANNESS_BIG, 8, 8, 0, *ADDRESS_MAP_NAME(x2212_sram_map)),
		m_e2prom_space_config("E2PROM", ENDIANNESS_BIG, 8, 8, 0, *ADDRESS_MAP_NAME(x2212_e2prom_map)),
		m_store(false),
		m_array_recall(false)
=======
x2212_device::x2212_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: x2212_device(mconfig, X2212, tag, owner, clock, 0x100)
{
}

x2212_device::x2212_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, int size_data)
	: device_t(mconfig, type, tag, owner, clock)
	, device_memory_interface(mconfig, *this)
	, device_nvram_interface(mconfig, *this)
	, m_auto_save(false)
	, m_sram_space_config("SRAM", ENDIANNESS_BIG, 8, 8, 0, *ADDRESS_MAP_NAME(x2212_sram_map))
	, m_e2prom_space_config("E2PROM", ENDIANNESS_BIG, 8, 8, 0, *ADDRESS_MAP_NAME(x2212_e2prom_map))
	, m_store(false)
	, m_array_recall(false)
	, m_size_data(size_data)
	, m_default_data(*this, DEVICE_SELF, size_data)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  static_set_auto_save - configuration helper
//  to set the auto-save flag
//-------------------------------------------------

void x2212_device::static_set_auto_save(device_t &device)
{
	downcast<x2212_device &>(device).m_auto_save = true;
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void x2212_device::device_start()
{
	save_item(NAME(m_store));
	save_item(NAME(m_array_recall));
<<<<<<< HEAD

	m_sram = m_addrspace[0];
	m_e2prom = m_addrspace[1];

	SIZE_DATA = 0x100;
}

void x2210_device::device_start()
{
	save_item(NAME(m_store));
	save_item(NAME(m_array_recall));

	m_sram = m_addrspace[0];
	m_e2prom = m_addrspace[1];

	SIZE_DATA = 0x40;
=======
	m_sram = &space(0);
	m_e2prom = &space(1);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  memory_space_config - return a description of
//  any address spaces owned by this device
//-------------------------------------------------

<<<<<<< HEAD
const address_space_config *x2212_device::memory_space_config(address_spacenum spacenum) const
{
	return (spacenum == 0) ? &m_sram_space_config : (spacenum == 1) ? &m_e2prom_space_config : NULL;
=======
device_memory_interface::space_config_vector x2212_device::memory_space_config() const
{
	return space_config_vector {
		std::make_pair(0, &m_sram_space_config),
		std::make_pair(1, &m_e2prom_space_config)
	};
>>>>>>> upstream/master
}


//-------------------------------------------------
//  nvram_default - called to initialize NVRAM to
//  its default state
//-------------------------------------------------

void x2212_device::nvram_default()
{
	// default to all-0xff
<<<<<<< HEAD
	for (int byte = 0; byte < SIZE_DATA; byte++)
=======
	for (int byte = 0; byte < m_size_data; byte++)
>>>>>>> upstream/master
	{
		m_sram->write_byte(byte, 0xff);
		m_e2prom->write_byte(byte, 0xff);
	}

	// populate from a memory region if present
<<<<<<< HEAD
	if (m_region != NULL)
	{
		if (m_region->bytes() != SIZE_DATA)
			fatalerror("x2212 region '%s' wrong size (expected size = 0x100)\n", tag());
		if (m_region->bytewidth() != 1)
			fatalerror("x2212 region '%s' needs to be an 8-bit region\n", tag());

		UINT8 *default_data = m_region->base();
		for (int byte = 0; byte < SIZE_DATA; byte++)
			m_e2prom->write_byte(byte, default_data[byte]);
=======
	if (m_default_data.found())
	{
		for (int byte = 0; byte < m_size_data; byte++)
			m_e2prom->write_byte(byte, m_default_data[byte]);
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  nvram_read - called to read NVRAM from the
//  .nv file
//-------------------------------------------------

void x2212_device::nvram_read(emu_file &file)
{
<<<<<<< HEAD
	UINT8 *buffer = (UINT8 *) alloca(SIZE_DATA);
	file.read(buffer, SIZE_DATA);
	for (int byte = 0; byte < SIZE_DATA; byte++)
=======
	uint8_t *buffer = (uint8_t *) alloca(m_size_data);
	file.read(buffer, m_size_data);
	for (int byte = 0; byte < m_size_data; byte++)
>>>>>>> upstream/master
	{
		m_sram->write_byte(byte, 0xff);
		m_e2prom->write_byte(byte, buffer[byte]);
	}
}


//-------------------------------------------------
//  nvram_write - called to write NVRAM to the
//  .nv file
//-------------------------------------------------

void x2212_device::nvram_write(emu_file &file)
{
	// auto-save causes an implicit store prior to exiting (writing)
	if (m_auto_save)
		store();

<<<<<<< HEAD
	UINT8 *buffer = (UINT8 *) alloca(SIZE_DATA);
	for (int byte = 0; byte < SIZE_DATA; byte++)
		buffer[byte] = m_e2prom->read_byte(byte);
	file.write(buffer, SIZE_DATA);
=======
	uint8_t *buffer = (uint8_t *) alloca(m_size_data);
	for (int byte = 0; byte < m_size_data; byte++)
		buffer[byte] = m_e2prom->read_byte(byte);
	file.write(buffer, m_size_data);
>>>>>>> upstream/master
}



//**************************************************************************
//  INTERNAL HELPERS
//**************************************************************************

//-------------------------------------------------
//  store - store data from live RAM into the
//  EEPROM
//-------------------------------------------------

void x2212_device::store()
{
<<<<<<< HEAD
	for (int byte = 0; byte < SIZE_DATA; byte++)
=======
	for (int byte = 0; byte < m_size_data; byte++)
>>>>>>> upstream/master
		m_e2prom->write_byte(byte, m_sram->read_byte(byte));
}


//-------------------------------------------------
//  recall - fetch data from the EEPROM into live
//  RAM
//-------------------------------------------------

void x2212_device::recall()
{
<<<<<<< HEAD
	for (int byte = 0; byte < SIZE_DATA; byte++)
=======
	for (int byte = 0; byte < m_size_data; byte++)
>>>>>>> upstream/master
		m_sram->write_byte(byte, m_e2prom->read_byte(byte));
}



//**************************************************************************
//  READ/WRITE HANDLERS
//**************************************************************************

//-------------------------------------------------
//  write - store to the live RAM
//-------------------------------------------------

WRITE8_MEMBER( x2212_device::write )
{
	m_sram->write_byte(offset, data & 0x0f);
}


//-------------------------------------------------
//  read - read from the live RAM
//-------------------------------------------------

READ8_MEMBER( x2212_device::read )
{
	return (m_sram->read_byte(offset) & 0x0f) | (space.unmap() & 0xf0);
}


//-------------------------------------------------
//  store - set the state of the store line
//  (active high)
//-------------------------------------------------

WRITE_LINE_MEMBER( x2212_device::store )
{
	if (state != 0 && !m_store)
		store();
	m_store = (state != 0);
}


//-------------------------------------------------
//  recall - set the state of the recall line
//  (active high)
//-------------------------------------------------

WRITE_LINE_MEMBER( x2212_device::recall )
{
	if (state != 0 && !m_array_recall)
		recall();
	m_array_recall = (state != 0);
}


<<<<<<< HEAD
x2210_device::x2210_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: x2212_device(mconfig, X2210, "X2210", tag, owner, clock, "x2210", __FILE__)
=======
x2210_device::x2210_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: x2212_device(mconfig, X2210, tag, owner, clock, 0x40)
>>>>>>> upstream/master
{
}
