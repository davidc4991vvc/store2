// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    dimemory.c

    Device memory interfaces.

***************************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "validity.h"


//**************************************************************************
//  PARAMETERS
//**************************************************************************

#define DETECT_OVERLAPPING_MEMORY   (0)

=======
>>>>>>> upstream/master


//**************************************************************************
//  CONSTANTS
//**************************************************************************

//const int TRIGGER_SUSPENDTIME = -4000;



//**************************************************************************
//  ADDRESS SPACE CONFIG
//**************************************************************************

//-------------------------------------------------
//  address_space_config - constructors
//-------------------------------------------------

address_space_config::address_space_config()
	: m_name("unknown"),
		m_endianness(ENDIANNESS_NATIVE),
		m_databus_width(0),
		m_addrbus_width(0),
		m_addrbus_shift(0),
		m_logaddr_width(0),
		m_page_shift(0),
<<<<<<< HEAD
		m_internal_map(NULL),
		m_default_map(NULL)
{
}

address_space_config::address_space_config(const char *name, endianness_t endian, UINT8 datawidth, UINT8 addrwidth, INT8 addrshift, address_map_constructor internal, address_map_constructor defmap)
=======
		m_is_octal(false),
		m_internal_map(nullptr),
		m_default_map(nullptr)
{
}

/*!
 @param name
 @param endian CPU endianness
 @param datawidth CPU parallelism bits
 @param addrwidth address bits
 @param addrshift
 @param internal
 @param defmap
 */
address_space_config::address_space_config(const char *name, endianness_t endian, u8 datawidth, u8 addrwidth, s8 addrshift, address_map_constructor internal, address_map_constructor defmap)
>>>>>>> upstream/master
	: m_name(name),
		m_endianness(endian),
		m_databus_width(datawidth),
		m_addrbus_width(addrwidth),
		m_addrbus_shift(addrshift),
		m_logaddr_width(addrwidth),
		m_page_shift(0),
<<<<<<< HEAD
=======
		m_is_octal(false),
>>>>>>> upstream/master
		m_internal_map(internal),
		m_default_map(defmap)
{
}

<<<<<<< HEAD
address_space_config::address_space_config(const char *name, endianness_t endian, UINT8 datawidth, UINT8 addrwidth, INT8 addrshift, UINT8 logwidth, UINT8 pageshift, address_map_constructor internal, address_map_constructor defmap)
=======
address_space_config::address_space_config(const char *name, endianness_t endian, u8 datawidth, u8 addrwidth, s8 addrshift, u8 logwidth, u8 pageshift, address_map_constructor internal, address_map_constructor defmap)
>>>>>>> upstream/master
	: m_name(name),
		m_endianness(endian),
		m_databus_width(datawidth),
		m_addrbus_width(addrwidth),
		m_addrbus_shift(addrshift),
		m_logaddr_width(logwidth),
		m_page_shift(pageshift),
<<<<<<< HEAD
=======
		m_is_octal(false),
>>>>>>> upstream/master
		m_internal_map(internal),
		m_default_map(defmap)
{
}

<<<<<<< HEAD
address_space_config::address_space_config(const char *name, endianness_t endian, UINT8 datawidth, UINT8 addrwidth, INT8 addrshift, address_map_delegate internal, address_map_delegate defmap)
=======
address_space_config::address_space_config(const char *name, endianness_t endian, u8 datawidth, u8 addrwidth, s8 addrshift, address_map_delegate internal, address_map_delegate defmap)
>>>>>>> upstream/master
	: m_name(name),
		m_endianness(endian),
		m_databus_width(datawidth),
		m_addrbus_width(addrwidth),
		m_addrbus_shift(addrshift),
		m_logaddr_width(addrwidth),
		m_page_shift(0),
<<<<<<< HEAD
		m_internal_map(NULL),
		m_default_map(NULL),
		m_internal_map_delegate(internal),
		m_default_map_delegate(defmap)
{
}

address_space_config::address_space_config(const char *name, endianness_t endian, UINT8 datawidth, UINT8 addrwidth, INT8 addrshift, UINT8 logwidth, UINT8 pageshift, address_map_delegate internal, address_map_delegate defmap)
=======
		m_is_octal(false),
		m_internal_map(nullptr),
		m_default_map(nullptr),
		m_internal_map_delegate(std::move(internal)),
		m_default_map_delegate(std::move(defmap))
{
}

address_space_config::address_space_config(const char *name, endianness_t endian, u8 datawidth, u8 addrwidth, s8 addrshift, u8 logwidth, u8 pageshift, address_map_delegate internal, address_map_delegate defmap)
>>>>>>> upstream/master
	: m_name(name),
		m_endianness(endian),
		m_databus_width(datawidth),
		m_addrbus_width(addrwidth),
		m_addrbus_shift(addrshift),
		m_logaddr_width(logwidth),
		m_page_shift(pageshift),
<<<<<<< HEAD
		m_internal_map(NULL),
		m_default_map(NULL),
		m_internal_map_delegate(internal),
		m_default_map_delegate(defmap)
=======
		m_is_octal(false),
		m_internal_map(nullptr),
		m_default_map(nullptr),
		m_internal_map_delegate(std::move(internal)),
		m_default_map_delegate(std::move(defmap))
>>>>>>> upstream/master
{
}


//**************************************************************************
//  MEMORY DEVICE MANAGEMENT
//**************************************************************************

//-------------------------------------------------
//  device_memory_interface - constructor
//-------------------------------------------------

device_memory_interface::device_memory_interface(const machine_config &mconfig, device_t &device)
	: device_interface(device, "memory")
{
<<<<<<< HEAD
	memset(m_address_map, 0, sizeof(m_address_map));
	memset(m_addrspace, 0, sizeof(m_addrspace));

	// configure the fast accessor
	device.m_memory = this;
=======
	// configure the fast accessor
	device.interfaces().m_memory = this;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  ~device_memory_interface - destructor
//-------------------------------------------------

device_memory_interface::~device_memory_interface()
{
}


//-------------------------------------------------
//  static_set_addrmap - configuration helper
//  to connect an address map to a device
//-------------------------------------------------

<<<<<<< HEAD
void device_memory_interface::static_set_addrmap(device_t &device, address_spacenum spacenum, address_map_constructor map)
=======
void device_memory_interface::static_set_addrmap(device_t &device, int spacenum, address_map_constructor map)
>>>>>>> upstream/master
{
	device_memory_interface *memory;
	if (!device.interface(memory))
		throw emu_fatalerror("MCFG_DEVICE_ADDRESS_MAP called on device '%s' with no memory interface", device.tag());
<<<<<<< HEAD
	if (spacenum >= ARRAY_LENGTH(memory->m_address_map))
		throw emu_fatalerror("MCFG_DEVICE_ADDRESS_MAP called on device '%s' with out-of-range space number %d", device.tag(), spacenum);
	memory->m_address_map[spacenum] = map;
=======
	memory->set_addrmap(spacenum, map);
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  set_address_space - connect an address space
//  to a device
//-------------------------------------------------

void device_memory_interface::set_address_space(address_spacenum spacenum, address_space &space)
{
	assert(spacenum < ARRAY_LENGTH(m_addrspace));
	m_addrspace[spacenum] = &space;
}


//-------------------------------------------------
//  memory_translate - translate from logical to
//  phyiscal addresses; designed to be overridden
//  by the actual device implementation if address
//  translation is supported
//-------------------------------------------------

bool device_memory_interface::memory_translate(address_spacenum spacenum, int intention, offs_t &address)
{
	// by default it maps directly
	return true;
=======
//  set_addrmap - connect an address map to a device
//-------------------------------------------------

void device_memory_interface::set_addrmap(int spacenum, address_map_constructor map)
{
	if (spacenum >= int(m_address_map.size()))
		m_address_map.resize(spacenum+1, nullptr);
	m_address_map[spacenum] = map;
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  memory_read - perform internal memory
//  operations that bypass the memory system;
//  designed to be overridden by the actual device
//  implementation if internal read operations are
//  handled by bypassing the memory system
//-------------------------------------------------

bool device_memory_interface::memory_read(address_spacenum spacenum, offs_t offset, int size, UINT64 &value)
{
	// by default, we don't do anything
	return false;
=======
//  dump - dump memory tables to the given file in
//  human-readable format
//-------------------------------------------------

void device_memory_interface::dump(FILE *file) const
{
	for (auto const &space : m_addrspace)
		if (space) {
			fprintf(file,
					"\n\n"
					"====================================================\n"
					"Device '%s' %s address space read handler dump\n"
					"====================================================\n",
					device().tag(), space->name());
			space->dump_map(file, read_or_write::READ);

			fprintf(file,
					"\n\n"
					"====================================================\n"
					"Device '%s' %s address space write handler dump\n"
					"====================================================\n",
					device().tag(), space->name());
			space->dump_map(file, read_or_write::WRITE);
		}
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  memory_write - perform internal memory
//  operations that bypass the memory system;
//  designed to be overridden by the actual device
//  implementation if internal write operations are
//  handled by bypassing the memory system
//-------------------------------------------------

bool device_memory_interface::memory_write(address_spacenum spacenum, offs_t offset, int size, UINT64 value)
{
	// by default, we don't do anything
	return false;
=======
//  memory_translate - translate from logical to
//  phyiscal addresses; designed to be overridden
//  by the actual device implementation if address
//  translation is supported
//-------------------------------------------------

bool device_memory_interface::memory_translate(int spacenum, int intention, offs_t &address)
{
	// by default it maps directly
	return true;
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  memory_readop - perform internal memory
//  operations that bypass the memory system;
//  designed to be overridden by the actual device
//  implementation if internal opcode fetching
//  operations are handled by bypassing the memory
//  system
//-------------------------------------------------

bool device_memory_interface::memory_readop(offs_t offset, int size, UINT64 &value)
{
	// by default, we don't do anything
	return false;
=======
//  interface_config_complete - perform final
//  memory configuration setup
//-------------------------------------------------

void device_memory_interface::interface_config_complete()
{
	const space_config_vector r = memory_space_config();
	for (const auto &entry : r) {
		if (entry.first >= int(m_address_config.size()))
			m_address_config.resize(entry.first + 1);
		m_address_config[entry.first] = entry.second;
	}
>>>>>>> upstream/master
}


//-------------------------------------------------
//  interface_validity_check - perform validity
//  checks on the memory configuration
//-------------------------------------------------

void device_memory_interface::interface_validity_check(validity_checker &valid) const
{
<<<<<<< HEAD
	bool detected_overlap = DETECT_OVERLAPPING_MEMORY ? false : true;

	// loop over all address spaces
	for (address_spacenum spacenum = AS_0; spacenum < ADDRESS_SPACES; ++spacenum)
	{
		const address_space_config *spaceconfig = space_config(spacenum);
		if (spaceconfig != NULL)
		{
			int datawidth = spaceconfig->m_databus_width;
			int alignunit = datawidth / 8;

			// construct the maps
			::address_map *map = global_alloc(::address_map(const_cast<device_t &>(device()), spacenum));

			// if this is an empty map, just skip it
			if (map->m_entrylist.first() == NULL)
			{
				global_free(map);
				continue;
			}

			// validate the global map parameters
			if (map->m_spacenum != spacenum)
				osd_printf_error("Space %d has address space %d handlers!\n", spacenum, map->m_spacenum);
			if (map->m_databits != datawidth)
				osd_printf_error("Wrong memory handlers provided for %s space! (width = %d, memory = %08x)\n", spaceconfig->m_name, datawidth, map->m_databits);

			// loop over entries and look for errors
			for (address_map_entry *entry = map->m_entrylist.first(); entry != NULL; entry = entry->next())
			{
				UINT32 bytestart = spaceconfig->addr2byte(entry->m_addrstart);
				UINT32 byteend = spaceconfig->addr2byte_end(entry->m_addrend);

				// look for overlapping entries
				if (!detected_overlap)
				{
					address_map_entry *scan;
					for (scan = map->m_entrylist.first(); scan != entry; scan = scan->next())
						if (entry->m_addrstart <= scan->m_addrend && entry->m_addrend >= scan->m_addrstart &&
							((entry->m_read.m_type != AMH_NONE && scan->m_read.m_type != AMH_NONE) ||
								(entry->m_write.m_type != AMH_NONE && scan->m_write.m_type != AMH_NONE)))
						{
							osd_printf_warning("%s space has overlapping memory (%X-%X,%d,%d) vs (%X-%X,%d,%d)\n", spaceconfig->m_name, entry->m_addrstart, entry->m_addrend, entry->m_read.m_type, entry->m_write.m_type, scan->m_addrstart, scan->m_addrend, scan->m_read.m_type, scan->m_write.m_type);
							detected_overlap = true;
							break;
						}
				}

				// look for inverted start/end pairs
				if (byteend < bytestart)
					osd_printf_error("Wrong %s memory read handler start = %08x > end = %08x\n", spaceconfig->m_name, entry->m_addrstart, entry->m_addrend);

				// look for misaligned entries
				if ((bytestart & (alignunit - 1)) != 0 || (byteend & (alignunit - 1)) != (alignunit - 1))
					osd_printf_error("Wrong %s memory read handler start = %08x, end = %08x ALIGN = %d\n", spaceconfig->m_name, entry->m_addrstart, entry->m_addrend, alignunit);

				// if this is a program space, auto-assign implicit ROM entries
				if (entry->m_read.m_type == AMH_ROM && entry->m_region == NULL)
				{
					entry->m_region = device().tag();
					entry->m_rgnoffs = entry->m_addrstart;
				}

				// if this entry references a memory region, validate it
				if (entry->m_region != NULL && entry->m_share == 0)
				{
					// make sure we can resolve the full path to the region
					bool found = false;
					std::string entry_region = entry->m_devbase.subtag(entry->m_region);

					// look for the region
					device_iterator deviter(device().mconfig().root_device());
					for (device_t *device = deviter.first(); device != NULL; device = deviter.next())
						for (const rom_entry *romp = rom_first_region(*device); romp != NULL && !found; romp = rom_next_region(romp))
						{
							if (rom_region_name(*device, romp) == entry_region)
							{
								// verify the address range is within the region's bounds
								offs_t length = ROMREGION_GETLENGTH(romp);
								if (entry->m_rgnoffs + (byteend - bytestart + 1) > length)
									osd_printf_error("%s space memory map entry %X-%X extends beyond region '%s' size (%X)\n", spaceconfig->m_name, entry->m_addrstart, entry->m_addrend, entry->m_region, length);
								found = true;
							}
						}

					// error if not found
					if (!found)
						osd_printf_error("%s space memory map entry %X-%X references non-existant region '%s'\n", spaceconfig->m_name, entry->m_addrstart, entry->m_addrend, entry->m_region);
				}

				// make sure all devices exist
				// FIXME: This doesn't work! AMH_DEVICE_DELEGATE entries don't even set m_tag, the device tag is inside the proto-delegate
				if (entry->m_read.m_type == AMH_DEVICE_DELEGATE && entry->m_read.m_tag != NULL)
				{
					std::string temp(entry->m_read.m_tag);
					if (device().siblingdevice(temp.c_str()) == NULL)
						osd_printf_error("%s space memory map entry references nonexistant device '%s'\n", spaceconfig->m_name, entry->m_read.m_tag);
				}
				if (entry->m_write.m_type == AMH_DEVICE_DELEGATE && entry->m_write.m_tag != NULL)
				{
					std::string temp(entry->m_write.m_tag);
					if (device().siblingdevice(temp.c_str()) == NULL)
						osd_printf_error("%s space memory map entry references nonexistant device '%s'\n", spaceconfig->m_name, entry->m_write.m_tag);
				}

				// make sure ports exist
//              if ((entry->m_read.m_type == AMH_PORT && entry->m_read.m_tag != NULL && portlist.find(entry->m_read.m_tag) == NULL) ||
//                  (entry->m_write.m_type == AMH_PORT && entry->m_write.m_tag != NULL && portlist.find(entry->m_write.m_tag) == NULL))
//                  osd_printf_error("%s space memory map entry references nonexistant port tag '%s'\n", spaceconfig->m_name, entry->m_read.m_tag);

				// validate bank and share tags
				if (entry->m_read.m_type == AMH_BANK)
					valid.validate_tag(entry->m_read.m_tag);
				if (entry->m_write.m_type == AMH_BANK)
					valid.validate_tag(entry->m_write.m_tag);
				if (entry->m_share != NULL)
					valid.validate_tag(entry->m_share);
			}

			// release the address map
			global_free(map);
=======
	// loop over all address spaces
	for (int spacenum = 0; spacenum < int(m_address_config.size()); ++spacenum)
	{
		if (space_config(spacenum))
		{
			// construct the map
			::address_map addrmap(const_cast<device_t &>(device()), spacenum);

			// let the map check itself
			addrmap.map_validity_check(valid, spacenum);
>>>>>>> upstream/master
		}
	}
}
