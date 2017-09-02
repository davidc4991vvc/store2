// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

<<<<<<< HEAD
    drivenum.c
=======
    drivenum.cpp
>>>>>>> upstream/master

    Driver enumeration helpers.

***************************************************************************/

#include "emu.h"
#include "drivenum.h"
<<<<<<< HEAD
#include "softlist.h"
#include <ctype.h>


#ifdef DRIVER_SWITCH
#include "emuopts.h"

driver_switch::driver_switch()
{
}

driver_switch::~driver_switch()
{
}

void driver_switch::init_assign_drivers(void)
{
	//direct change protected member
	driver_list::s_drivers_sorted[0] = &GAME_NAME(___empty);
	driver_list::s_driver_count = 1;
}

void driver_switch::assign_drivers(emu_options &opts)
{
	static const struct
	{
		const char *name;
		const game_driver * const *driver;
	} drivers_table[] =
	{
#ifndef TINY_BUILD
		{ "mame",	mamedrivers },
		{ "plus",	mameplusdrivers },
		{ "homebrew",	mamehbdrivers },
		{ "decrypted",	mamedecrypteddrivers },
		{ "console",	messdrivers },
#else
		{ "mame",		tinydrivers },
#endif /* !TINY_BUILD */
		{ NULL }
	};

	UINT32 enabled = 0;
	int i, n;
	bool mechanical = opts.bool_value(OPTION_DISABLE_MECHANICAL_DRIVER);

#ifndef TINY_BUILD
	const char *drv_option = opts.value(OPTION_DRIVER_CONFIG);
	if (drv_option)
	{
		char *temp = core_strdup(drv_option);
		if (temp)
		{
			char *p = strtok(temp, ",");
 			while (p)
			{
				char *s = core_strtrim(p);	//get individual driver name
				if (s[0])
				{
					if (core_stricmp(s, "all") == 0)
					{
						enabled = (UINT32)-1;
						break;
					}

					for (i = 0; drivers_table[i].name; i++)
						if (core_stricmp(s, drivers_table[i].name) == 0)
						{
							enabled |= 1 << i;
							break;
						}

					if (!drivers_table[i].name)
						osd_printf_warning(_("Illegal value for %s = %s\n"), OPTION_DRIVER_CONFIG, s);
				}
				osd_free(s);
 				p = strtok(NULL, ",");
			}
 			osd_free(temp);
		}
	}
#endif /* !TINY_BUILD */

	if (enabled == 0)
		enabled = 1;	// default to mamedrivers

	n = 0;
	for (i = 0; drivers_table[i].name; i++)
		if (enabled & (1 << i))
		{
			for (int c = 0; drivers_table[i].driver[c]; c++)
				if (core_stricmp(drivers_table[i].driver[c]->name, "___empty"))
					if (!mechanical || !(drivers_table[i].driver[c]->flags & MACHINE_MECHANICAL))
					driver_list::s_drivers_sorted[n++] = drivers_table[i].driver[c];
		}

	// ___empty driver add once
	driver_list::s_drivers_sorted[n++] = &GAME_NAME(___empty);
	driver_list::s_driver_count = n;

	qsort(driver_list::s_drivers_sorted, n, sizeof(*driver_list::s_drivers_sorted), driver_list::driver_sort_callback);
}
#endif /* DRIVER_SWITCH */
=======
#include "softlist_dev.h"

#include <ctype.h>


>>>>>>> upstream/master

//**************************************************************************
//  DRIVER LIST
//**************************************************************************

//-------------------------------------------------
//  driver_list - constructor
//-------------------------------------------------

driver_list::driver_list()
{
}


//-------------------------------------------------
//  find - find a driver by name
//-------------------------------------------------

int driver_list::find(const char *name)
{
	// if no name, bail
<<<<<<< HEAD
	if (name == NULL)
		return -1;

	// create a dummy item for comparison purposes
	game_driver driver;
	driver.name = name;
	game_driver *driverptr = &driver;

	// binary search to find it
	const game_driver **result = reinterpret_cast<const game_driver **>(bsearch(&driverptr, s_drivers_sorted, s_driver_count, sizeof(*s_drivers_sorted), driver_sort_callback));
	return (result == NULL) ? -1 : result - s_drivers_sorted;
=======
	if (!name)
		return -1;

	// binary search to find it
	game_driver const *const *const begin = s_drivers_sorted;
	game_driver const *const *const end = begin + s_driver_count;
	auto const cmp = [] (game_driver const *driver, char const *name) { return core_stricmp(driver->name, name) < 0; };
	game_driver const *const *const result = std::lower_bound(begin, end, name, cmp);
	return ((result == end) || core_stricmp((*result)->name, name)) ? -1 : std::distance(begin, result);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  matches - true if we match, taking into
//  account wildcards in the wildstring
//-------------------------------------------------

bool driver_list::matches(const char *wildstring, const char *string)
{
	// can only match internal drivers if the wildstring starts with an underscore
<<<<<<< HEAD
	if (string[0] == '_' && (wildstring == NULL || wildstring[0] != '_'))
		return false;

	// match everything else normally
	return (wildstring == NULL || core_strwildcmp(wildstring, string) == 0);
}


//-------------------------------------------------
//  driver_sort_callback - compare two items in
//  an array of game_driver pointers
//-------------------------------------------------

int driver_list::driver_sort_callback(const void *elem1, const void *elem2)
{
	const game_driver * const *item1 = reinterpret_cast<const game_driver * const *>(elem1);
	const game_driver * const *item2 = reinterpret_cast<const game_driver * const *>(elem2);
	return core_stricmp((*item1)->name, (*item2)->name);
=======
	if (string[0] == '_' && (wildstring == nullptr || wildstring[0] != '_'))
		return false;

	// match everything else normally
	return (wildstring == nullptr || core_strwildcmp(wildstring, string) == 0);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  penalty_compare - compare two strings for
//  closeness and assign a score.
//-------------------------------------------------

int driver_list::penalty_compare(const char *source, const char *target)
{
	int gaps = 1;
	bool last = true;

	// scan the strings
	for ( ; *source && *target; target++)
	{
		// do a case insensitive match
<<<<<<< HEAD
		bool match = (tolower((UINT8)*source) == tolower((UINT8)*target));
=======
		bool const match(tolower(u8(*source)) == tolower(u8(*target)));
>>>>>>> upstream/master

		// if we matched, advance the source
		if (match)
			source++;

		// if the match state changed, count gaps
		if (match != last)
		{
			last = match;
			if (!match)
				gaps++;
		}
	}

	// penalty if short string does not completely fit in
	for ( ; *source; source++)
		gaps++;

	// if we matched perfectly, gaps == 0
	if (gaps == 1 && *source == 0 && *target == 0)
		gaps = 0;

	return gaps;
}



//**************************************************************************
//  DRIVER ENUMERATOR
//**************************************************************************

//-------------------------------------------------
//  driver_enumerator - constructor
//-------------------------------------------------

driver_enumerator::driver_enumerator(emu_options &options)
<<<<<<< HEAD
	: m_current(-1),
		m_filtered_count(0),
		m_options(options),
		m_included(s_driver_count),
		m_config(s_driver_count)
{
	memset(&m_included[0], 0, s_driver_count);
	memset(&m_config[0], 0, s_driver_count*sizeof(m_config[0]));
=======
	: m_current(-1)
	, m_filtered_count(0)
	, m_options(options)
	, m_included(s_driver_count)
	, m_config(CONFIG_CACHE_COUNT)
{
>>>>>>> upstream/master
	include_all();
}


driver_enumerator::driver_enumerator(emu_options &options, const char *string)
<<<<<<< HEAD
	: m_current(-1),
		m_filtered_count(0),
		m_options(options),
		m_included(s_driver_count),
		m_config(s_driver_count)
{
	memset(&m_included[0], 0, s_driver_count);
	memset(&m_config[0], 0, s_driver_count*sizeof(m_config[0]));
=======
	: driver_enumerator(options)
{
>>>>>>> upstream/master
	filter(string);
}


driver_enumerator::driver_enumerator(emu_options &options, const game_driver &driver)
<<<<<<< HEAD
	: m_current(-1),
		m_filtered_count(0),
		m_options(options),
		m_included(s_driver_count),
		m_config(s_driver_count)
{
	memset(&m_included[0], 0, s_driver_count);
	memset(&m_config[0], 0, s_driver_count*sizeof(m_config[0]));
=======
	: driver_enumerator(options)
{
>>>>>>> upstream/master
	filter(driver);
}


//-------------------------------------------------
//  ~driver_enumerator - destructor
//-------------------------------------------------

driver_enumerator::~driver_enumerator()
{
	// configs are freed by the cache
}


//-------------------------------------------------
//  config - return a machine_config for the given
//  driver, allocating on demand if needed
//-------------------------------------------------

<<<<<<< HEAD
machine_config &driver_enumerator::config(int index, emu_options &options) const
{
	assert(index >= 0 && index < s_driver_count);

	// if we don't have it cached, add it
	if (m_config[index] == NULL)
	{
		// if our cache is full, release the head entry
		if (m_config_cache.count() == CONFIG_CACHE_COUNT)
		{
			config_entry *first = m_config_cache.first();
			m_config[first->index()] = NULL;
			m_config_cache.remove(*first);
		}

		// allocate the config and add it to the end of the list
		machine_config *config = m_config[index] = global_alloc(machine_config(*s_drivers_sorted[index], options));
		m_config_cache.append(*global_alloc(config_entry(*config, index)));
	}
	return *m_config[index];
=======
std::shared_ptr<machine_config> const &driver_enumerator::config(std::size_t index, emu_options &options) const
{
	assert(index < s_driver_count);

	// if we don't have it cached, add it
	std::shared_ptr<machine_config> &config = m_config[index];
	if (!config)
		config = std::make_shared<machine_config>(*s_drivers_sorted[index], options);

	return config;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  filter - filter the driver list against the
//  given string
//-------------------------------------------------

<<<<<<< HEAD
int driver_enumerator::filter(const char *filterstring)
=======
std::size_t driver_enumerator::filter(const char *filterstring)
>>>>>>> upstream/master
{
	// reset the count
	exclude_all();

	// match name against each driver in the list
<<<<<<< HEAD
	for (int index = 0; index < s_driver_count; index++)
=======
	for (std::size_t index = 0; index < s_driver_count; index++)
>>>>>>> upstream/master
		if (matches(filterstring, s_drivers_sorted[index]->name))
			include(index);

	return m_filtered_count;
}


//-------------------------------------------------
//  filter - filter the driver list against the
//  given driver
//-------------------------------------------------

<<<<<<< HEAD
int driver_enumerator::filter(const game_driver &driver)
=======
std::size_t driver_enumerator::filter(const game_driver &driver)
>>>>>>> upstream/master
{
	// reset the count
	exclude_all();

	// match name against each driver in the list
<<<<<<< HEAD
	for (int index = 0; index < s_driver_count; index++)
=======
	for (std::size_t index = 0; index < s_driver_count; index++)
>>>>>>> upstream/master
		if (s_drivers_sorted[index] == &driver)
			include(index);

	return m_filtered_count;
}


//-------------------------------------------------
//  include_all - include all non-internal drivers
//-------------------------------------------------

void driver_enumerator::include_all()
{
<<<<<<< HEAD
	memset(&m_included[0], 1, sizeof(m_included[0]) * s_driver_count);
	m_filtered_count = s_driver_count;

	// always exclude the empty driver
	int empty = find("___empty");
	assert(empty != -1);
	m_included[empty] = 0;
=======
	std::fill(m_included.begin(), m_included.end(), true);
	m_filtered_count = m_included.size();

	// always exclude the empty driver
	exclude(find("___empty"));
>>>>>>> upstream/master
}


//-------------------------------------------------
//  next - get the next driver matching the given
//  filter
//-------------------------------------------------

bool driver_enumerator::next()
{
<<<<<<< HEAD
	// always advance one
	release_current();
	m_current++;

	// if we have a filter, scan forward to the next match
	while (m_current < s_driver_count)
	{
		if (m_included[m_current])
			break;
		m_current++;
	}

	// return true if we end up in range
	return (m_current >= 0 && m_current < s_driver_count);
=======
	release_current();

	// always advance one
	// if we have a filter, scan forward to the next match
	for (m_current++; (m_current < s_driver_count) && !m_included[m_current]; m_current++) { }

	// return true if we end up in range
	return (m_current >= 0) && (m_current < s_driver_count);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  next_excluded - get the next driver that is
//  not currently included in the list
//-------------------------------------------------

bool driver_enumerator::next_excluded()
{
<<<<<<< HEAD
	// always advance one
	release_current();
	m_current++;

	// if we have a filter, scan forward to the next match
	while (m_current < s_driver_count)
	{
		if (!m_included[m_current])
			break;
		m_current++;
	}

	// return true if we end up in range
	return (m_current >= 0 && m_current < s_driver_count);
=======
	release_current();

	// always advance one
	// if we have a filter, scan forward to the next match
	for (m_current++; (m_current < s_driver_count) && m_included[m_current]; m_current++) { }

	// return true if we end up in range
	return (m_current >= 0) && (m_current < s_driver_count);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  driver_sort_callback - compare two items in
//  an array of game_driver pointers
//-------------------------------------------------

<<<<<<< HEAD
void driver_enumerator::find_approximate_matches(const char *string, int count, int *results)
=======
void driver_enumerator::find_approximate_matches(const char *string, std::size_t count, int *results)
>>>>>>> upstream/master
{
#undef rand

	// if no name, pick random entries
<<<<<<< HEAD
	if (string == NULL || string[0] == 0)
=======
	if (!string || !string[0])
>>>>>>> upstream/master
	{
		// seed the RNG first
		srand(osd_ticks());

		// allocate a temporary list
		std::vector<int> templist(m_filtered_count);
		int arrayindex = 0;
		for (int index = 0; index < s_driver_count; index++)
			if (m_included[index])
				templist[arrayindex++] = index;
		assert(arrayindex == m_filtered_count);

		// shuffle
<<<<<<< HEAD
		for (int shufnum = 0; shufnum < 4 * s_driver_count; shufnum++)
=======
		for (int shufnum = 0; shufnum < (4 * s_driver_count); shufnum++)
>>>>>>> upstream/master
		{
			int item1 = rand() % m_filtered_count;
			int item2 = rand() % m_filtered_count;
			int temp = templist[item1];
			templist[item1] = templist[item2];
			templist[item2] = temp;
		}

		// copy out the first few entries
		for (int matchnum = 0; matchnum < count; matchnum++)
			results[matchnum] = templist[matchnum % m_filtered_count];
<<<<<<< HEAD
		return;
	}

	// allocate memory to track the penalty value
	std::vector<int> penalty(count);

	// initialize everyone's states
	for (int matchnum = 0; matchnum < count; matchnum++)
	{
		penalty[matchnum] = 9999;
		results[matchnum] = -1;
	}

	// scan the entire drivers array
	for (int index = 0; index < s_driver_count; index++)
		if (m_included[index])
		{
			// skip things that can't run
			if ((s_drivers_sorted[index]->flags & MACHINE_NO_STANDALONE) != 0)
				continue;

			// pick the best match between driver name and description
			int curpenalty = penalty_compare(string, s_drivers_sorted[index]->description);
			int tmp = penalty_compare(string, s_drivers_sorted[index]->name);
			curpenalty = MIN(curpenalty, tmp);

			// insert into the sorted table of matches
			for (int matchnum = count - 1; matchnum >= 0; matchnum--)
			{
				// stop if we're worse than the current entry
				if (curpenalty >= penalty[matchnum])
					break;

				// as long as this isn't the last entry, bump this one down
				if (matchnum < count - 1)
				{
					penalty[matchnum + 1] = penalty[matchnum];
					results[matchnum + 1] = results[matchnum];
				}
				results[matchnum] = index;
				penalty[matchnum] = curpenalty;
			}
		}
=======
	}
	else
	{
		// allocate memory to track the penalty value
		std::vector<int> penalty(count);

		// initialize everyone's states
		for (int matchnum = 0; matchnum < count; matchnum++)
		{
			penalty[matchnum] = 9999;
			results[matchnum] = -1;
		}

		// scan the entire drivers array
		for (int index = 0; index < s_driver_count; index++)
		{
			// skip things that can't run
			if (m_included[index])
			{
				// pick the best match between driver name and description
				int curpenalty = penalty_compare(string, s_drivers_sorted[index]->type.fullname());
				int tmp = penalty_compare(string, s_drivers_sorted[index]->name);
				curpenalty = (std::min)(curpenalty, tmp);

				// insert into the sorted table of matches
				for (int matchnum = count - 1; matchnum >= 0; matchnum--)
				{
					// stop if we're worse than the current entry
					if (curpenalty >= penalty[matchnum])
						break;

					// as long as this isn't the last entry, bump this one down
					if (matchnum < count - 1)
					{
						penalty[matchnum + 1] = penalty[matchnum];
						results[matchnum + 1] = results[matchnum];
					}
					results[matchnum] = index;
					penalty[matchnum] = curpenalty;
				}
			}
		}
	}
>>>>>>> upstream/master
}


//-------------------------------------------------
//  release_current - release bulky memory
//  structures from the current entry because
//  we're done with it
//-------------------------------------------------

void driver_enumerator::release_current() const
{
	// skip if no current entry
<<<<<<< HEAD
	if (m_current < 0 || m_current >= s_driver_count)
		return;

	// skip if we haven't cached a config
	if (m_config[m_current] == NULL)
		return;

	// iterate over software lists in this entry and reset
	software_list_device_iterator deviter(m_config[m_current]->root_device());
	for (software_list_device *swlistdev = deviter.first(); swlistdev != NULL; swlistdev = deviter.next())
		swlistdev->release();
=======
	if ((m_current >= 0) && (m_current < s_driver_count))
	{
		// skip if we haven't cached a config
		auto const cached = m_config.find(m_current);
		if (cached != m_config.end())
		{
			// iterate over software lists in this entry and reset
			for (software_list_device &swlistdev : software_list_device_iterator(cached->second->root_device()))
				swlistdev.release();
		}
	}
>>>>>>> upstream/master
}
