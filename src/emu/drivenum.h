// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    drivenum.h

    Driver enumeration helpers.

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __DRIVENUM_H__
#define __DRIVENUM_H__
=======
#ifndef MAME_EMU_DRIVENUM_H
#define MAME_EMU_DRIVENUM_H

#pragma once

#include <algorithm>
#include <cassert>
#include <memory>


//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

GAME_EXTERN(___empty);
>>>>>>> upstream/master


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> driver_list

// driver_list is a purely static class that wraps the global driver list
class driver_list
{
	DISABLE_COPYING(driver_list);

<<<<<<< HEAD
#ifdef DRIVER_SWITCH
	friend class driver_switch;
#endif /* DRIVER_SWITCH */

=======
>>>>>>> upstream/master
protected:
	// construction/destruction
	driver_list();

public:
	// getters
<<<<<<< HEAD
	static int total() { return s_driver_count; }

	// any item by index
	static const game_driver &driver(int index) { assert(index >= 0 && index < s_driver_count); return *s_drivers_sorted[index]; }
	static int clone(int index) { return find(driver(index).parent); }
	static int non_bios_clone(int index) { int result = find(driver(index).parent); return (result != -1 && (driver(result).flags & MACHINE_IS_BIOS_ROOT) == 0) ? result : -1; }
	static int compatible_with(int index) { return find(driver(index).compatible_with); }

	// any item by driver
	static int clone(const game_driver &driver) { int index = find(driver); assert(index != -1); return clone(index); }
	static int non_bios_clone(const game_driver &driver) { int index = find(driver); assert(index != -1); return non_bios_clone(index); }
	static int compatible_with(const game_driver &driver) { int index = find(driver); assert(index != -1); return compatible_with(index); }
=======
	static std::size_t total() { return s_driver_count; }

	// any item by index
	static const game_driver &driver(std::size_t index) { assert(index < total()); return *s_drivers_sorted[index]; }
	static int clone(std::size_t index) { return find(driver(index).parent); }
	static int non_bios_clone(std::size_t index) { int const result = find(driver(index).parent); return ((result >= 0) && !(driver(result).flags & MACHINE_IS_BIOS_ROOT)) ? result : -1; }
	static int compatible_with(std::size_t index) { return find(driver(index).compatible_with); }

	// any item by driver
	static int clone(const game_driver &driver) { int const index = find(driver); assert(index >= 0); return clone(index); }
	static int non_bios_clone(const game_driver &driver) { int const index = find(driver); assert(index >= 0); return non_bios_clone(index); }
	static int compatible_with(const game_driver &driver) { int const index = find(driver); assert(index >= 0); return compatible_with(index); }
>>>>>>> upstream/master

	// general helpers
	static int find(const char *name);
	static int find(const game_driver &driver) { return find(driver.name); }

	// static helpers
	static bool matches(const char *wildstring, const char *string);
	static int penalty_compare(const char *source, const char *target);

protected:
<<<<<<< HEAD
	// internal helpers
	static int driver_sort_callback(const void *elem1, const void *elem2);

	// internal state
	static int                          s_driver_count;
#ifdef DRIVER_SWITCH
	static const game_driver *          s_drivers_sorted[];
#else
	static const game_driver * const    s_drivers_sorted[];
#endif /* DRIVER_SWITCH */
=======
	static std::size_t const            s_driver_count;
	static game_driver const * const    s_drivers_sorted[];
>>>>>>> upstream/master
};


// ======================> driver_enumerator

// driver_enumerator enables efficient iteration through the driver list
class driver_enumerator : public driver_list
{
	DISABLE_COPYING(driver_enumerator);

public:
	// construction/destruction
	driver_enumerator(emu_options &options);
	driver_enumerator(emu_options &options, const char *filter);
	driver_enumerator(emu_options &options, const game_driver &filter);
	~driver_enumerator();

	// getters
<<<<<<< HEAD
	int count() const { return m_filtered_count; }
=======
	std::size_t count() const { return m_filtered_count; }
>>>>>>> upstream/master
	int current() const { return m_current; }
	emu_options &options() const { return m_options; }

	// current item
	const game_driver &driver() const { return driver_list::driver(m_current); }
<<<<<<< HEAD
	machine_config &config() const { return config(m_current, m_options); }
	int clone() { return driver_list::clone(m_current); }
	int non_bios_clone() { return driver_list::non_bios_clone(m_current); }
	int compatible_with() { return driver_list::compatible_with(m_current); }
=======
	std::shared_ptr<machine_config> const &config() const { return config(m_current, m_options); }
	int clone() const { return driver_list::clone(m_current); }
	int non_bios_clone() const { return driver_list::non_bios_clone(m_current); }
	int compatible_with() const { return driver_list::compatible_with(m_current); }
>>>>>>> upstream/master
	void include() { include(m_current); }
	void exclude() { exclude(m_current); }

	// any item by index
<<<<<<< HEAD
	bool included(int index) const { assert(index >= 0 && index < s_driver_count); return m_included[index]; }
	bool excluded(int index) const { assert(index >= 0 && index < s_driver_count); return !m_included[index]; }
	machine_config &config(int index) const { return config(index,m_options); }
	machine_config &config(int index, emu_options &options) const;
	void include(int index) { assert(index >= 0 && index < s_driver_count); if (!m_included[index]) { m_included[index] = true; m_filtered_count++; }  }
	void exclude(int index) { assert(index >= 0 && index < s_driver_count); if (m_included[index]) { m_included[index] = false; m_filtered_count--; } }
=======
	bool included(std::size_t index) const { assert(index < m_included.size()); return m_included[index]; }
	bool excluded(std::size_t index) const { assert(index < m_included.size()); return !m_included[index]; }
	std::shared_ptr<machine_config> const &config(std::size_t index) const { return config(index, m_options); }
	std::shared_ptr<machine_config> const &config(std::size_t index, emu_options &options) const;
	void include(std::size_t index) { assert(index < m_included.size()); if (!m_included[index]) { m_included[index] = true; m_filtered_count++; }  }
	void exclude(std::size_t index) { assert(index < m_included.size()); if (m_included[index]) { m_included[index] = false; m_filtered_count--; } }
>>>>>>> upstream/master
	using driver_list::driver;
	using driver_list::clone;
	using driver_list::non_bios_clone;
	using driver_list::compatible_with;

	// filtering/iterating
<<<<<<< HEAD
	int filter(const char *string = NULL);
	int filter(const game_driver &driver);
	void include_all();
	void exclude_all() { memset(&m_included[0], 0, sizeof(m_included[0]) * s_driver_count); m_filtered_count = 0; }
=======
	std::size_t filter(const char *string = nullptr);
	std::size_t filter(const game_driver &driver);
	void include_all();
	void exclude_all() { std::fill(m_included.begin(), m_included.end(), false); m_filtered_count = 0; }
>>>>>>> upstream/master
	void reset() { m_current = -1; }
	bool next();
	bool next_excluded();

	// general helpers
<<<<<<< HEAD
	void set_current(int index) { assert(index >= -1 && index <= s_driver_count); m_current = index; }
	void find_approximate_matches(const char *string, int count, int *results);

private:
	// internal helpers
	void release_current() const;

	// entry in the config cache
	struct config_entry
	{
		friend class simple_list<config_entry>;

	public:
		// construction/destruction
		config_entry(machine_config &config, int index) : m_next(NULL), m_config(&config), m_index(index) { }

		// getters
		config_entry *next() const { return m_next; }
		int index() const { return m_index; }
		machine_config *config() const { return m_config; }

	private:
		// internal state
		config_entry *      m_next;
		auto_pointer<machine_config> m_config;
		int                 m_index;
	};

	static const int CONFIG_CACHE_COUNT = 100;

	// internal state
	int                 m_current;
	int                 m_filtered_count;
	emu_options &       m_options;
	std::vector<UINT8> m_included;
	mutable std::vector<machine_config *> m_config;
	mutable simple_list<config_entry> m_config_cache;
};

#ifdef DRIVER_SWITCH
class driver_switch
{
protected:
	// construction/destruction
	driver_switch();
	~driver_switch();

public:
	static void init_assign_drivers();
	static void assign_drivers(emu_options &opts);

private:
	// internal state
#ifndef TINY_BUILD
	static const game_driver * const mamedrivers[];
	static const game_driver * const mameplusdrivers[];
	static const game_driver * const mamehbdrivers[];
	static const game_driver * const mamedecrypteddrivers[];
	static const game_driver * const messdrivers[];
#else
	static const game_driver * const tinydrivers[];
#endif /* !TINY_BUILD */
};
#endif /* DRIVER_SWITCH */
#endif
=======
	void set_current(std::size_t index) { assert(index < s_driver_count); m_current = index; }
	void find_approximate_matches(const char *string, std::size_t count, int *results);

private:
	static constexpr std::size_t CONFIG_CACHE_COUNT = 100;

	typedef util::lru_cache_map<std::size_t, std::shared_ptr<machine_config> > machine_config_cache;

	// internal helpers
	void release_current() const;

	// internal state
	int                             m_current;
	std::size_t                     m_filtered_count;
	emu_options &                   m_options;
	std::vector<bool>               m_included;
	mutable machine_config_cache    m_config;
};

#endif // MAME_EMU_DRIVENUM_H
>>>>>>> upstream/master
