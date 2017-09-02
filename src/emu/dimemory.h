// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    dimemory.h

    Device memory interfaces.

***************************************************************************/

#pragma once

#ifndef __EMU_H__
#error Dont include this file directly; include emu.h instead.
#endif

<<<<<<< HEAD
#ifndef __DIMEMORY_H__
#define __DIMEMORY_H__
=======
#ifndef MAME_EMU_DIMEMORY_H
#define MAME_EMU_DIMEMORY_H
>>>>>>> upstream/master


//**************************************************************************
//  CONSTANTS
//**************************************************************************

// Translation intentions
<<<<<<< HEAD
const int TRANSLATE_TYPE_MASK       = 0x03;     // read write or fetch
const int TRANSLATE_USER_MASK       = 0x04;     // user mode or fully privileged
const int TRANSLATE_DEBUG_MASK      = 0x08;     // debug mode (no side effects)

const int TRANSLATE_READ            = 0;        // translate for read
const int TRANSLATE_WRITE           = 1;        // translate for write
const int TRANSLATE_FETCH           = 2;        // translate for instruction fetch
const int TRANSLATE_READ_USER       = (TRANSLATE_READ | TRANSLATE_USER_MASK);
const int TRANSLATE_WRITE_USER      = (TRANSLATE_WRITE | TRANSLATE_USER_MASK);
const int TRANSLATE_FETCH_USER      = (TRANSLATE_FETCH | TRANSLATE_USER_MASK);
const int TRANSLATE_READ_DEBUG      = (TRANSLATE_READ | TRANSLATE_DEBUG_MASK);
const int TRANSLATE_WRITE_DEBUG     = (TRANSLATE_WRITE | TRANSLATE_DEBUG_MASK);
const int TRANSLATE_FETCH_DEBUG     = (TRANSLATE_FETCH | TRANSLATE_DEBUG_MASK);
=======
constexpr int TRANSLATE_TYPE_MASK       = 0x03;     // read write or fetch
constexpr int TRANSLATE_USER_MASK       = 0x04;     // user mode or fully privileged
constexpr int TRANSLATE_DEBUG_MASK      = 0x08;     // debug mode (no side effects)

constexpr int TRANSLATE_READ            = 0;        // translate for read
constexpr int TRANSLATE_WRITE           = 1;        // translate for write
constexpr int TRANSLATE_FETCH           = 2;        // translate for instruction fetch
constexpr int TRANSLATE_READ_USER       = (TRANSLATE_READ | TRANSLATE_USER_MASK);
constexpr int TRANSLATE_WRITE_USER      = (TRANSLATE_WRITE | TRANSLATE_USER_MASK);
constexpr int TRANSLATE_FETCH_USER      = (TRANSLATE_FETCH | TRANSLATE_USER_MASK);
constexpr int TRANSLATE_READ_DEBUG      = (TRANSLATE_READ | TRANSLATE_DEBUG_MASK);
constexpr int TRANSLATE_WRITE_DEBUG     = (TRANSLATE_WRITE | TRANSLATE_DEBUG_MASK);
constexpr int TRANSLATE_FETCH_DEBUG     = (TRANSLATE_FETCH | TRANSLATE_DEBUG_MASK);
>>>>>>> upstream/master



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_DEVICE_ADDRESS_MAP(_space, _map) \
	device_memory_interface::static_set_addrmap(*device, _space, ADDRESS_MAP_NAME(_map));

#define MCFG_DEVICE_REMOVE_ADDRESS_MAP(_space) \
<<<<<<< HEAD
	device_memory_interface::static_set_addrmap(*device, _space, NULL);
=======
	device_memory_interface::static_set_addrmap(*device, _space, nullptr);
>>>>>>> upstream/master

#define MCFG_DEVICE_PROGRAM_MAP(_map) \
	MCFG_DEVICE_ADDRESS_MAP(AS_PROGRAM, _map)

#define MCFG_DEVICE_DATA_MAP(_map) \
	MCFG_DEVICE_ADDRESS_MAP(AS_DATA, _map)

#define MCFG_DEVICE_IO_MAP(_map) \
	MCFG_DEVICE_ADDRESS_MAP(AS_IO, _map)

#define MCFG_DEVICE_DECRYPTED_OPCODES_MAP(_map) \
<<<<<<< HEAD
	MCFG_DEVICE_ADDRESS_MAP(AS_DECRYPTED_OPCODES, _map)
=======
	MCFG_DEVICE_ADDRESS_MAP(AS_OPCODES, _map)
>>>>>>> upstream/master



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> device_memory_interface

class device_memory_interface : public device_interface
{
	friend class device_scheduler;

public:
	// construction/destruction
	device_memory_interface(const machine_config &mconfig, device_t &device);
	virtual ~device_memory_interface();

	// configuration access
<<<<<<< HEAD
	address_map_constructor address_map(address_spacenum spacenum = AS_0) const { return (spacenum < ARRAY_LENGTH(m_address_map)) ? m_address_map[spacenum] : NULL; }
	const address_space_config *space_config(address_spacenum spacenum = AS_0) const { return memory_space_config(spacenum); }

	// static inline configuration helpers
	static void static_set_addrmap(device_t &device, address_spacenum spacenum, address_map_constructor map);

	// basic information getters
	bool has_space(int index = 0) const { return (m_addrspace[index] != NULL); }
	bool has_space(address_spacenum index) const { return (m_addrspace[int(index)] != NULL); }
	bool has_configured_map(int index = 0) const { return (m_address_map[index] != NULL); }
	bool has_configured_map(address_spacenum index) const { return (m_address_map[int(index)] != NULL); }
	address_space &space(int index = 0) const { assert(m_addrspace[index] != NULL); return *m_addrspace[index]; }
	address_space &space(address_spacenum index) const { assert(m_addrspace[int(index)] != NULL); return *m_addrspace[int(index)]; }

	// address space accessors
	void set_address_space(address_spacenum spacenum, address_space &space);

	// address translation
	bool translate(address_spacenum spacenum, int intention, offs_t &address) { return memory_translate(spacenum, intention, address); }

	// read/write access
	bool read(address_spacenum spacenum, offs_t offset, int size, UINT64 &value) { return memory_read(spacenum, offset, size, value); }
	bool write(address_spacenum spacenum, offs_t offset, int size, UINT64 value) { return memory_write(spacenum, offset, size, value); }
	bool readop(offs_t offset, int size, UINT64 &value) { return memory_readop(offset, size, value); }
=======
	address_map_constructor address_map(int spacenum = 0) const { return spacenum >= 0 && spacenum < int(m_address_map.size()) ? m_address_map[spacenum] : nullptr; }
	const address_space_config *space_config(int spacenum = 0) const { return spacenum >= 0 && spacenum < int(m_address_config.size()) ? m_address_config[spacenum] : nullptr; }
	int max_space_count() const { return m_address_config.size(); }

	// static inline configuration helpers
	static void static_set_addrmap(device_t &device, int spacenum, address_map_constructor map);
	void set_addrmap(int spacenum, address_map_constructor map);

	// basic information getters
	bool has_space(int index = 0) const { return index >= 0 && index < int(m_addrspace.size()) && m_addrspace[index]; }
	bool has_configured_map(int index = 0) const { return index >= 0 && index < int(m_address_map.size()) && m_address_map[index]; }
	address_space &space(int index = 0) const { assert(index >= 0 && index < int(m_addrspace.size()) && m_addrspace[index]); return *m_addrspace[index]; }

	// address translation
	bool translate(int spacenum, int intention, offs_t &address) { return memory_translate(spacenum, intention, address); }
>>>>>>> upstream/master

	// deliberately ambiguous functions; if you have the memory interface
	// just use it
	device_memory_interface &memory() { return *this; }

<<<<<<< HEAD
protected:
	// required overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum) const = 0;

	// optional operation overrides
	virtual bool memory_translate(address_spacenum spacenum, int intention, offs_t &address);
	virtual bool memory_read(address_spacenum spacenum, offs_t offset, int size, UINT64 &value);
	virtual bool memory_write(address_spacenum spacenum, offs_t offset, int size, UINT64 value);
	virtual bool memory_readop(offs_t offset, int size, UINT64 &value);

	// interface-level overrides
	virtual void interface_validity_check(validity_checker &valid) const;

	// configuration
	address_map_constructor m_address_map[ADDRESS_SPACES]; // address maps for each address space
	address_space *     m_addrspace[ADDRESS_SPACES]; // reported address spaces
=======
	// setup functions - these are called in sequence for all device_memory_interface by the memory manager
	template <typename Space> void allocate(memory_manager &manager, int spacenum)
	{
		assert((0 <= spacenum) && (max_space_count() > spacenum));
		m_addrspace.resize(std::max<std::size_t>(m_addrspace.size(), spacenum + 1));
		assert(!m_addrspace[spacenum]);
		m_addrspace[spacenum] = std::make_unique<Space>(manager, *this, spacenum);
	}
	void prepare_maps() { for (auto const &space : m_addrspace) { if (space) { space->prepare_map(); } } }
	void populate_from_maps() { for (auto const &space : m_addrspace) { if (space) { space->populate_from_map(); } } }
	void allocate_memory() { for (auto const &space : m_addrspace) { if (space) { space->allocate_memory(); } } }
	void locate_memory() { for (auto const &space : m_addrspace) { if (space) { space->locate_memory(); } } }
	void set_log_unmap(bool log) { for (auto const &space : m_addrspace) { if (space) { space->set_log_unmap(log); } } }

	// diagnostic functions
	void dump(FILE *file) const;

protected:
	using space_config_vector = std::vector<std::pair<int, const address_space_config *>>;

	// required overrides
	virtual space_config_vector memory_space_config() const = 0;

	// optional operation overrides
	virtual bool memory_translate(int spacenum, int intention, offs_t &address);

	// interface-level overrides
	virtual void interface_config_complete() override;
	virtual void interface_validity_check(validity_checker &valid) const override;

	// configuration
	std::vector<address_map_constructor> m_address_map; // address maps for each address space

private:
	// internal state
	std::vector<const address_space_config *>   m_address_config; // configuration for each space
	std::vector<std::unique_ptr<address_space>> m_addrspace; // reported address spaces
>>>>>>> upstream/master
};

// iterator
typedef device_interface_iterator<device_memory_interface> memory_interface_iterator;



<<<<<<< HEAD
//**************************************************************************
//  INLINE HELPERS
//**************************************************************************

//-------------------------------------------------
//  device_get_space_config - return a pointer
//  to sthe given address space's configuration
//-------------------------------------------------

inline const address_space_config *device_get_space_config(const device_t &device, address_spacenum spacenum = AS_0)
{
	const device_memory_interface *intf;
	if (!device.interface(intf))
		throw emu_fatalerror("Device '%s' does not have memory interface", device.tag());
	return intf->space_config(spacenum);
}


#endif  /* __DIMEMORY_H__ */
=======
#endif  /* MAME_EMU_DIMEMORY_H */
>>>>>>> upstream/master
