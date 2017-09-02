<<<<<<< HEAD
// license:GPL-2.0+
// copyright-holders:Dirk Best
=======
// license:BSD-3-Clause
// copyright-holders: Dirk Best
>>>>>>> upstream/master
/*************************************************************************

    RAM device

    Provides a configurable amount of RAM to drivers

**************************************************************************/

<<<<<<< HEAD
#include <stdio.h>
#include <ctype.h>

#include "emu.h"
#include "emuopts.h"
#include "ram.h"
=======
#include "emu.h"
#include "ram.h"
#include "emuopts.h"

#include <stdio.h>
#include <ctype.h>
#include <algorithm>


namespace {

//-------------------------------------------------
//  parse_string - convert a ram string to an
//  integer value
//-------------------------------------------------

uint32_t parse_string(const char *s)
{
	static const struct
	{
		const char *suffix;
		unsigned multiple;
	} s_suffixes[] =
	{
		{ "",       1 },
		{ "k",      1024 },
		{ "kb",     1024 },
		{ "kib",    1024 },
		{ "m",      1024 * 1024 },
		{ "mb",     1024 * 1024 },
		{ "mib",    1024 * 1024 }
	};

	// parse the string
	unsigned ram = 0;
	char suffix[8] = { 0, };
	sscanf(s, "%u%7s", &ram, suffix);

	// perform the lookup
	auto iter = std::find_if(
		std::begin(s_suffixes),
		std::end(s_suffixes),
		[&suffix](const auto &potential_suffix) { return !core_stricmp(suffix, potential_suffix.suffix); });

	// identify the multiplier (or 0 if not recognized, signalling a parse failure)
	unsigned multiple = iter != std::end(s_suffixes)
		? iter->multiple
		: 0;

	// return the result
	return ram * multiple;
}


//-------------------------------------------------
//  calculate_extra_options
//-------------------------------------------------

std::vector<uint32_t> calculate_extra_options(const char *extra_options_string, std::string *bad_option)
{
	std::vector<uint32_t> result;
	std::string options(extra_options_string);

	bool done = false;
	for (std::string::size_type start = 0, end = options.find_first_of(','); !done; start = end + 1, end = options.find_first_of(',', start))
	{
		// parse the option
		const std::string ram_option_string = options.substr(start, (end == -1) ? -1 : end - start);
		const uint32_t ram_option = parse_string(ram_option_string.c_str());
		if (ram_option == 0)
		{
			if (bad_option)
				*bad_option = std::move(ram_option_string);
			return result;
		}

		// and add it to the results
		result.push_back(ram_option);
		done = end == std::string::npos;
	}
	return result;
}

};
>>>>>>> upstream/master


/*****************************************************************************
    LIVE DEVICE
*****************************************************************************/

// device type definition
<<<<<<< HEAD
const device_type RAM = &device_creator<ram_device>;

=======
DEFINE_DEVICE_TYPE(RAM, ram_device, "ram", "RAM")
>>>>>>> upstream/master


//-------------------------------------------------
//  ram_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
ram_device::ram_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, RAM, "RAM", tag, owner, clock, "ram", __FILE__)
{
	m_size = 0;
	m_default_size = NULL;
	m_extra_options = NULL;
	m_default_value = 0xCD;
}



=======
ram_device::ram_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, RAM, tag, owner, clock)
	, m_size(0)
	, m_default_size(0)
	, m_default_value(0xCD)
	, m_extra_options_string(nullptr)
{
}


>>>>>>> upstream/master
//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void ram_device::device_start()
{
<<<<<<< HEAD
	/* the device named 'ram' can get ram options from command line */
=======
	// the device named 'ram' can get ram options from command line
>>>>>>> upstream/master
	m_size = 0;
	if (strcmp(tag(), ":" RAM_TAG) == 0)
	{
		const char *ramsize_string = machine().options().ram_size();
<<<<<<< HEAD
		if ((ramsize_string != NULL) && (ramsize_string[0] != '\0'))
			m_size = parse_string(ramsize_string);
	}

	/* if we didn't get a size yet, use the default */
	if (m_size == 0)
		m_size = default_size();

	/* allocate space for the ram */
	m_pointer.resize(m_size);
	memset(&m_pointer[0], m_default_value, m_size);

	/* register for state saving */
=======
		if (ramsize_string && *ramsize_string)
		{
			m_size = parse_string(ramsize_string);
			if (!is_valid_size(m_size))
			{
				std::ostringstream output;
				util::stream_format(output, "Cannot recognize the RAM option %s", ramsize_string);
				util::stream_format(output, " (valid options are %s", m_default_size);

				if (m_extra_options_string)
					util::stream_format(output, ",%s).\n", m_extra_options_string);
				else
					util::stream_format(output, ").\n");

				osd_printf_error("%s", output.str().c_str());

				osd_printf_warning("Setting value to default %s\n", m_default_size);

				m_size = 0;
			}
		}
	}

	// if we didn't get a size yet, use the default
	if (m_size == 0)
		m_size = default_size();

	// allocate space for the ram
	m_pointer.resize(m_size);
	memset(&m_pointer[0], m_default_value, m_size);

	// register for state saving
>>>>>>> upstream/master
	save_item(NAME(m_size));
	save_item(NAME(m_pointer));
}


//-------------------------------------------------
//  device_validity_check - device-specific validity
//  checks
//-------------------------------------------------

void ram_device::device_validity_check(validity_checker &valid) const
{
<<<<<<< HEAD
	const char *ramsize_string = NULL;
	int is_valid = FALSE;
	UINT32 specified_ram;
	const char *gamename_option;

	/* verify default ram value */
	if (default_size() == 0)
		osd_printf_error("Invalid default RAM option: %s\n", m_default_size);

	/* command line options are only parsed for the device named RAM_TAG */
	if (tag() != NULL && strcmp(tag(), ":" RAM_TAG) == 0)
	{
		/* verify command line ram option */
		ramsize_string = mconfig().options().ram_size();
		gamename_option = mconfig().options().system_name();

		if ((ramsize_string != NULL) && (ramsize_string[0] != '\0'))
		{
			specified_ram = parse_string(ramsize_string);

			if (specified_ram == 0)
				osd_printf_error("Cannot recognize the RAM option %s\n", ramsize_string);

			if (gamename_option != NULL && *gamename_option != 0 && strcmp(gamename_option, mconfig().gamedrv().name) == 0)
			{
				/* compare command line option to default value */
				if (default_size() == specified_ram)
					is_valid = TRUE;

				/* verify extra ram options */
				if (m_extra_options != NULL)
				{
					int j;
					int size = strlen(m_extra_options);
					char * const s = core_strdup(m_extra_options);
					char * const e = s + size;
					char *p = s;
					for (j=0;j<size;j++) {
						if (p[j]==',') p[j]=0;
					}

					/* try to parse each option */
					while(p <= e)
					{
						UINT32 option_ram_size = parse_string(p);

						if (option_ram_size == 0)
							osd_printf_error("Invalid RAM option: %s\n", p);

						if (option_ram_size == specified_ram)
							is_valid = TRUE;

						p += strlen(p);
						if (p == e)
							break;
						p += 1;
					}

					osd_free(s);
				}

			} else {
				/* if not for this driver then return ok */
				is_valid = TRUE;
			}
		}
		else
		{
			/* not specifying the ramsize on the command line is valid as well */
			is_valid = TRUE;
		}
	}
	else
		is_valid = TRUE;

	if (!is_valid)
	{
		std::string output;
		strcatprintf(output, "Cannot recognize the RAM option %s", ramsize_string);
		strcatprintf(output, " (valid options are %s", m_default_size);

		if (m_extra_options != NULL)
			strcatprintf(output, ",%s).\n", m_extra_options);
		else
			strcatprintf(output, ").\n");

		osd_printf_error("%s", output.c_str());

		osd_printf_warning("Setting value to default %s\n",m_default_size);
		std::string error;
		mconfig().options().set_value(OPTION_RAMSIZE, m_default_size, OPTION_PRIORITY_CMDLINE, error);
		assert(error.empty());
	}
}



//-------------------------------------------------
//  parse_string - convert a ram string to an
//  integer value
//-------------------------------------------------

UINT32 ram_device::parse_string(const char *s)
{
	UINT32 ram;
	char suffix = '\0';

	sscanf(s, "%u%c", &ram, &suffix);

	switch(tolower(suffix))
	{
		case 'k':
			/* kilobytes */
			ram *= 1024;
			break;

		case 'm':
			/* megabytes */
			ram *= 1024*1024;
			break;

		case '\0':
			/* no suffix */
			break;

		default:
			/* parse failure */
			ram = 0;
			break;
	}

	return ram;
}



//-------------------------------------------------
//  default_size
//-------------------------------------------------

UINT32 ram_device::default_size(void) const
{
	return parse_string(m_default_size);
=======
	// verify default ram value
	if (default_size() == 0)
		osd_printf_error("Invalid default RAM option: %s\n", m_default_size);

	// calculate any extra options
	std::vector<uint32_t> extra_options;
	std::string bad_option;
	if (m_extra_options_string)
		extra_options = calculate_extra_options(m_extra_options_string, &bad_option);

	// report any errors
	if (!bad_option.empty())
		osd_printf_error("Invalid RAM option: %s\n", bad_option.c_str());
}


//-------------------------------------------------
//  is_valid_size
//-------------------------------------------------

bool ram_device::is_valid_size(uint32_t size) const
{
	return size == default_size()
		|| std::find(extra_options().begin(), extra_options().end(), size) != extra_options().end();
}


//-------------------------------------------------
//  default_size
//-------------------------------------------------

uint32_t ram_device::default_size(void) const
{
	return parse_string(m_default_size);
}


//-------------------------------------------------
//  extra_options
//-------------------------------------------------

const std::vector<uint32_t> &ram_device::extra_options(void) const
{
	if (m_extra_options_string && m_extra_options.empty())
		m_extra_options = calculate_extra_options(m_extra_options_string, nullptr);
	return m_extra_options;
>>>>>>> upstream/master
}
