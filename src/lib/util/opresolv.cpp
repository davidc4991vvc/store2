// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/****************************************************************************

<<<<<<< HEAD
    opresolv.h
=======
    opresolv.cpp
>>>>>>> upstream/master

    Extensible ranged option resolution handling

****************************************************************************/

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "pool.h"
#include "corestr.h"
#include "opresolv.h"

<<<<<<< HEAD
enum resolution_entry_state
{
	RESOLUTION_ENTRY_STATE_UNSPECIFIED,
	RESOLUTION_ENTRY_STATE_SPECIFIED
};

struct option_resolution_entry
{
	const option_guide *guide_entry;
	enum resolution_entry_state state;
	union
	{
		int int_value;
		const char *str_value;
	} u;
};

struct option_resolution
{
	object_pool *pool;
	const char *specification;
	size_t option_count;
	struct option_resolution_entry *entries;
};

static optreserr_t resolve_single_param(const char *specification, int *param_value,
	struct OptionRange *range, size_t range_count)
{
	int FLAG_IN_RANGE           = 0x01;
	int FLAG_IN_DEFAULT         = 0x02;
	int FLAG_DEFAULT_SPECIFIED  = 0x04;
	int FLAG_HALF_RANGE         = 0x08;

	int last_value = 0;
	int value = 0;
	int flags = 0;
	const char *s = specification;

	while(*s && !isalpha(*s))
	{
		if (*s == '-')
		{
			/* range specifier */
			if (flags & (FLAG_IN_RANGE|FLAG_IN_DEFAULT))
			{
				return OPTIONRESOLUTION_ERROR_SYNTAX;
			}
			flags |= FLAG_IN_RANGE;
			s++;

			if (range)
			{
				range->max = -1;
				if ((flags & FLAG_HALF_RANGE) == 0)
				{
					range->min = -1;
					flags |= FLAG_HALF_RANGE;
				}
			}
		}
		else if (*s == '[')
		{
			/* begin default value */
			if (flags & (FLAG_IN_DEFAULT|FLAG_DEFAULT_SPECIFIED))
			{
				return OPTIONRESOLUTION_ERROR_SYNTAX;
			}
			flags |= FLAG_IN_DEFAULT;
			s++;
		}
		else if (*s == ']')
		{
			/* end default value */
			if ((flags & FLAG_IN_DEFAULT) == 0)
			{
				return OPTIONRESOLUTION_ERROR_SYNTAX;
			}
			flags &= ~FLAG_IN_DEFAULT;
			flags |= FLAG_DEFAULT_SPECIFIED;
			s++;

			if (param_value && *param_value == -1)
				*param_value = value;
		}
		else if (*s == '/')
		{
			/* value separator */
			if (flags & (FLAG_IN_DEFAULT|FLAG_IN_RANGE))
			{
				return OPTIONRESOLUTION_ERROR_SYNTAX;
			}
			s++;

			/* if we are spitting out ranges, complete the range */
			if (range && (flags & FLAG_HALF_RANGE))
			{
				range++;
				flags &= ~FLAG_HALF_RANGE;
				if (--range_count == 0)
					range = NULL;
			}
		}
		else if (*s == ';')
		{
			/* basic separator */
			s++;
		}
		else if (isdigit(*s))
		{
			/* numeric value */
			last_value = value;
			value = 0;
			do
			{
				value *= 10;
				value += *s - '0';
				s++;
			}
			while(isdigit(*s));

			if (range)
			{
				if ((flags & FLAG_HALF_RANGE) == 0)
				{
					range->min = value;
					flags |= FLAG_HALF_RANGE;
				}
				range->max = value;
			}

			/* if we have a value; check to see if it is out of range */
			if (param_value && (*param_value != -1) && (*param_value != value))
			{
				if ((last_value < *param_value) && (*param_value < value))
				{
					if ((flags & FLAG_IN_RANGE) == 0)
						return OPTIONRESOLUTION_ERROR_PARAMOUTOFRANGE;
				}
			}
			flags &= ~FLAG_IN_RANGE;
		}
		else
		{
			return OPTIONRESOLUTION_ERROR_SYNTAX;
		}
	}

	/* we can't have zero length guidelines strings */
	if (s == specification)
	{
		return OPTIONRESOLUTION_ERROR_SYNTAX;
	}

	return OPTIONRESOLUTION_ERROR_SUCCESS;
}



static const char *lookup_in_specification(const char *specification, const option_guide *option)
{
	const char *s;
	s = strchr(specification, option->parameter);
	return s ? s + 1 : NULL;
}



option_resolution *option_resolution_create(const option_guide *guide, const char *specification)
{
	option_resolution *resolution = NULL;
	const option_guide *guide_entry;
	int option_count;
	int opt = -1;
	object_pool *pool;

	assert(guide);

	/* first count the number of options specified in the guide */
	option_count = option_resolution_countoptions(guide, specification);

	/* create a memory pool for this structure */
	pool = pool_alloc_lib(NULL);
	if (!pool)
		goto outofmemory;

	/* allocate the main structure */
	resolution = (option_resolution *)pool_malloc_lib(pool, sizeof(option_resolution));
	if (!resolution)
		goto outofmemory;
	memset(resolution, 0, sizeof(*resolution));
	resolution->pool = pool;

	/* set up the entries list */
	resolution->option_count = option_count;
	resolution->specification = specification;
	resolution->entries = (option_resolution_entry *)pool_malloc_lib(resolution->pool, sizeof(struct option_resolution_entry) * option_count);
	if (!resolution->entries)
		goto outofmemory;
	memset(resolution->entries, 0, sizeof(struct option_resolution_entry) * option_count);

	/* initialize each of the entries */
	opt = 0;
	guide_entry = guide;
	while(guide_entry->option_type != OPTIONTYPE_END)
	{
		switch(guide_entry->option_type) {
		case OPTIONTYPE_INT:
		case OPTIONTYPE_ENUM_BEGIN:
		case OPTIONTYPE_STRING:
			if (lookup_in_specification(specification, guide_entry))
				resolution->entries[opt++].guide_entry = guide_entry;
			break;
		case OPTIONTYPE_ENUM_VALUE:
			break;
		default:
			goto unexpected;
		}
		guide_entry++;
	}
	assert(opt == option_count);
	return resolution;

unexpected:
	assert(FALSE);
outofmemory:
	if (resolution)
		option_resolution_close(resolution);
	return NULL;
}



optreserr_t option_resolution_add_param(option_resolution *resolution, const char *param, const char *value)
{
	int i;
	int must_resolve;
	optreserr_t err;
	const char *option_specification;
	struct option_resolution_entry *entry = NULL;

	for (i = 0; i < resolution->option_count; i++)
	{
		if (!strcmp(param, resolution->entries[i].guide_entry->identifier))
		{
			entry = &resolution->entries[i];
			break;
		}
	}
	if (!entry)
		return OPTIONRESOLUTION_ERROR_PARAMNOTFOUND;

	if (entry->state != RESOLUTION_ENTRY_STATE_UNSPECIFIED)
		return OPTIONRESOLUTION_ERROR_PARAMALREADYSPECIFIED;

	switch(entry->guide_entry->option_type) {
	case OPTIONTYPE_INT:
		entry->u.int_value = atoi(value);
		entry->state = RESOLUTION_ENTRY_STATE_SPECIFIED;
		must_resolve = TRUE;
		break;

	case OPTIONTYPE_STRING:
		entry->u.str_value = pool_strdup_lib(resolution->pool, value);
		if (!entry->u.str_value)
		{
			err = OPTIONRESOLUTION_ERROR_OUTOFMEMORY;
			goto done;
		}
		entry->state = RESOLUTION_ENTRY_STATE_SPECIFIED;
		must_resolve = FALSE;
		break;

	case OPTIONTYPE_ENUM_BEGIN:
		for (i = 1; entry->guide_entry[i].option_type == OPTIONTYPE_ENUM_VALUE; i++)
		{
			if (!core_stricmp(value, entry->guide_entry[i].identifier))
			{
				entry->u.int_value = entry->guide_entry[i].parameter;
				entry->state = RESOLUTION_ENTRY_STATE_SPECIFIED;
				break;
			}
		}
		if (entry->state != RESOLUTION_ENTRY_STATE_SPECIFIED)
		{
			err = OPTIONRESOLUTION_ERROR_BADPARAM;
			goto done;
		}
		must_resolve = TRUE;
		break;

	default:
		err = OPTIONRESOLTUION_ERROR_INTERNAL;
		assert(0);
		goto done;
	}

	/* do a resolution step if necessary */
	if (must_resolve)
	{
		option_specification = lookup_in_specification(resolution->specification, entry->guide_entry);
		err = resolve_single_param(option_specification, &entry->u.int_value, NULL, 0);
		if (err)
			goto done;

		/* did we not get a real value? */
		if (entry->u.int_value < 0)
		{
			err = OPTIONRESOLUTION_ERROR_PARAMNOTSPECIFIED;
			goto done;
		}
	}

	err = OPTIONRESOLUTION_ERROR_SUCCESS;

done:
	return err;
}



void option_resolution_close(option_resolution *resolution)
{
	pool_free_lib(resolution->pool);
}



optreserr_t option_resolution_finish(option_resolution *resolution)
{
	int i;
	optreserr_t err;
	struct option_resolution_entry *entry;
	const char *option_specification;

	for (i = 0; i < resolution->option_count; i++)
	{
		entry = &resolution->entries[i];

		if (entry->state == RESOLUTION_ENTRY_STATE_UNSPECIFIED)
		{
			switch(entry->guide_entry->option_type) {
			case OPTIONTYPE_INT:
			case OPTIONTYPE_ENUM_BEGIN:
				option_specification = lookup_in_specification(resolution->specification, entry->guide_entry);
				assert(option_specification);
				entry->u.int_value = -1;
				err = resolve_single_param(option_specification, &entry->u.int_value, NULL, 0);
				if (err)
					return err;
				break;

			case OPTIONTYPE_STRING:
				entry->u.str_value = "";
				break;

			default:
				assert(FALSE);
				return OPTIONRESOLTUION_ERROR_INTERNAL;
			}
			entry->state = RESOLUTION_ENTRY_STATE_SPECIFIED;
		}
	}
	return OPTIONRESOLUTION_ERROR_SUCCESS;
}



static const struct option_resolution_entry *option_resolution_lookup_entry(option_resolution *resolution, int option_char)
{
	size_t i;
	const struct option_resolution_entry *entry;

	for (i = 0; i < resolution->option_count; i++)
	{
		entry = &resolution->entries[i];

		switch(entry->guide_entry->option_type) {
		case OPTIONTYPE_INT:
		case OPTIONTYPE_STRING:
		case OPTIONTYPE_ENUM_BEGIN:
			if (entry->guide_entry->parameter == option_char)
				return entry;
			break;

		default:
			assert(FALSE);
			return NULL;
		}
	}
	return NULL;
}



int option_resolution_lookup_int(option_resolution *resolution, int option_char)
{
	const struct option_resolution_entry *entry;
	entry = option_resolution_lookup_entry(resolution, option_char);
	return entry ? entry->u.int_value : -1;
}



const char *option_resolution_lookup_string(option_resolution *resolution, int option_char)
{
	const struct option_resolution_entry *entry;
	entry = option_resolution_lookup_entry(resolution, option_char);
	return entry ? entry->u.str_value : NULL;
}



const char *option_resolution_specification(option_resolution *resolution)
{
	return resolution->specification;
}



const option_guide *option_resolution_find_option(option_resolution *resolution, int option_char)
{
	const struct option_resolution_entry *entry;
	entry = option_resolution_lookup_entry(resolution, option_char);
	return entry ? entry->guide_entry : NULL;
}



const option_guide *option_resolution_index_option(option_resolution *resolution, int indx)
{
	if ((indx < 0) || (indx >= resolution->option_count))
		return NULL;
	return resolution->entries[indx].guide_entry;
}



int option_resolution_countoptions(const option_guide *guide, const char *specification)
{
	int option_count = 0;

	while(guide->option_type != OPTIONTYPE_END)
	{
		switch(guide->option_type) {
		case OPTIONTYPE_INT:
		case OPTIONTYPE_STRING:
		case OPTIONTYPE_ENUM_BEGIN:
			if (lookup_in_specification(specification, guide))
				option_count++;
			break;
		case OPTIONTYPE_ENUM_VALUE:
			break;
		default:
			assert(FALSE);
			return 0;
		}
		guide++;
	}
	return option_count;
}



optreserr_t option_resolution_listranges(const char *specification, int option_char,
	struct OptionRange *range, size_t range_count)
{
	assert(range_count > 0);

	/* clear out range */
	memset(range, -1, sizeof(*range) * range_count);
	range_count--;

	specification = strchr(specification, option_char);
	if (!specification)
	{
		return OPTIONRESOLUTION_ERROR_SYNTAX;
	}

	return resolve_single_param(specification + 1, NULL, range, range_count);
}



optreserr_t option_resolution_getdefault(const char *specification, int option_char, int *val)
{
	assert(val);

	/* clear out default */
	*val = -1;

	specification = strchr(specification, option_char);
	if (!specification)
	{
		return OPTIONRESOLUTION_ERROR_SYNTAX;
	}

	return resolve_single_param(specification + 1, val, NULL, 0);
}



optreserr_t option_resolution_isvalidvalue(const char *specification, int option_char, int val)
{
	optreserr_t err;
	struct OptionRange ranges[256];
	int i;

	err = option_resolution_listranges(specification, option_char, ranges, ARRAY_LENGTH(ranges));
	if (err)
		return err;

	for (i = 0; (ranges[i].min >= 0) && (ranges[i].max >= 0); i++)
	{
		if ((ranges[i].min <= val) && (ranges[i].max >= val))
			return OPTIONRESOLUTION_ERROR_SUCCESS;
	}
	return OPTIONRESOLUTION_ERROR_PARAMOUTOFRANGE;
}



int option_resolution_contains(const char *specification, int option_char)
{
	return strchr(specification, option_char) != NULL;
}



const char *option_resolution_error_string(optreserr_t err)
{
	static const char *const errors[] =
	{
		"The operation completed successfully",     /* OPTIONRESOLUTION_ERROR_SUCCESS */
		"Out of memory",                            /* OPTIONRESOLUTION_ERROR_OUTOFMEMORY */
		"Parameter out of range",                   /* OPTIONRESOLUTION_ERROR_PARAMOUTOFRANGE */
		"Parameter not specified",                  /* OPTIONRESOLUTION_ERROR_PARAMNOTSPECIFIED */
		"Unknown parameter",                        /* OPTIONRESOLUTION_ERROR_PARAMNOTFOUND */
		"Parameter specified multiple times",       /* OPTIONRESOLUTION_ERROR_PARAMALREADYSPECIFIED */
		"Invalid parameter",                        /* OPTIONRESOLUTION_ERROR_BADPARAM */
		"Syntax error",                             /* OPTIONRESOLUTION_ERROR_SYNTAX */
		"Internal error"                            /* OPTIONRESOLTUION_ERROR_INTERNAL */
	};

	if ((err < 0) || (err >= ARRAY_LENGTH(errors)))
		return NULL;
	return errors[err];
}
=======

namespace util {

/***************************************************************************
    option_resolution
***************************************************************************/

// -------------------------------------------------
//  ctor
// -------------------------------------------------

option_resolution::option_resolution(const option_guide &guide)
{
	// reserve space for entries
	m_entries.reserve(guide.entries().size());

	// initialize each of the entries; can't use foreach because we need to scan the
	// ENUM_VALUE entries
	for (auto iter = guide.entries().begin(); iter != guide.entries().end(); iter++)
	{
		// create the entry
		m_entries.emplace_back(*iter);
		entry &entry(m_entries.back());

		// if this is an enumeration, identify the values
		if (iter->type() == option_guide::entry::option_type::ENUM_BEGIN)
		{
			// enum values begin after the ENUM_BEGIN
			auto enum_value_begin = iter + 1;
			auto enum_value_end = enum_value_begin;

			// and identify all entries of type ENUM_VALUE
			while (enum_value_end != guide.entries().end() && enum_value_end->type() == option_guide::entry::option_type::ENUM_VALUE)
			{
				iter++;
				enum_value_end++;
			}

			// set the range
			entry.set_enum_value_range(enum_value_begin, enum_value_end);
		}
	}
}


// -------------------------------------------------
//  dtor
// -------------------------------------------------

option_resolution::~option_resolution()
{
}


// -------------------------------------------------
//  lookup_in_specification
// -------------------------------------------------

const char *option_resolution::lookup_in_specification(const char *specification, const option_guide::entry &option)
{
	const char *s;
	s = strchr(specification, option.parameter());
	return s ? s + 1 : nullptr;
}


// -------------------------------------------------
//  set_specification - sets the option specification
//  and mutates values accordingly
// -------------------------------------------------

void option_resolution::set_specification(const std::string &specification)
{
	for (auto &entry : m_entries)
	{
		// find this entry's info in the specification
		auto entry_specification = lookup_in_specification(specification.c_str(), entry.m_guide_entry);

		// parse this entry's specification (e.g. - set up ranges and defaults)
		entry.parse_specification(entry_specification);

		// is this a range typed that needs to be defaulted for the first time?
		if (entry.is_pertinent() && entry.is_ranged() && entry.value().empty())
		{
			entry.set_value(entry.default_value());
		}
	}
}


// -------------------------------------------------
//  find
// -------------------------------------------------

option_resolution::entry *option_resolution::find(int parameter)
{
	auto iter = std::find_if(
		m_entries.begin(),
		m_entries.end(),
		[parameter](const entry &e) { return e.parameter() == parameter; });

	return iter != m_entries.end()
		? &*iter
		: nullptr;
}


// -------------------------------------------------
//  find
// -------------------------------------------------

option_resolution::entry *option_resolution::find(const std::string &identifier)
{
	auto iter = std::find_if(
		m_entries.begin(),
		m_entries.end(),
		[&](const entry &e) { return !strcmp(e.identifier(), identifier.c_str()); });

	return iter != m_entries.end()
		? &*iter
		: nullptr;
}


// -------------------------------------------------
//  lookup_int
// -------------------------------------------------

int option_resolution::lookup_int(int parameter)
{
	auto entry = find(parameter);
	assert(entry != nullptr);
	return entry->value_int();
}


// -------------------------------------------------
//  lookup_string
// -------------------------------------------------

const std::string &option_resolution::lookup_string(int parameter)
{
	auto entry = find(parameter);
	assert(entry != nullptr);
	return entry->value();
}


// -------------------------------------------------
//  error_string
// -------------------------------------------------

option_resolution::error option_resolution::get_default(const char *specification, int option_char, int *val)
{
	// NYI
	return error::INTERNAL;
}


// -------------------------------------------------
//  error_string
// -------------------------------------------------

const char *option_resolution::error_string(option_resolution::error err)
{
	switch (err)
	{
	case error::SUCCESS:                return "The operation completed successfully";
	case error::OUTOFMEMORY:            return "Out of memory";
	case error::PARAMOUTOFRANGE:        return "Parameter out of range";
	case error::PARAMNOTSPECIFIED:      return "Parameter not specified";
	case error::PARAMNOTFOUND:          return "Unknown parameter";
	case error::PARAMALREADYSPECIFIED:  return "Parameter specified multiple times";
	case error::BADPARAM:               return "Invalid parameter";
	case error::SYNTAX:                 return "Syntax error";
	case error::INTERNAL:               return "Internal error";
	}
	return nullptr;
}


// -------------------------------------------------
//  entry::ctor
// -------------------------------------------------

option_resolution::entry::entry(const option_guide::entry &guide_entry)
	: m_guide_entry(guide_entry), m_is_pertinent(false)
{
}


// -------------------------------------------------
//  entry::set_enum_value_range
// -------------------------------------------------

void option_resolution::entry::set_enum_value_range(const option_guide::entry *begin, const option_guide::entry *end)
{
	m_enum_value_begin = begin;
	m_enum_value_end = end;
}


// -------------------------------------------------
//  entry::parse_specification
// -------------------------------------------------

void option_resolution::entry::parse_specification(const char *specification)
{
	// clear some items out
	m_ranges.clear();
	m_default_value.clear();

	// is this even pertinent?
	m_is_pertinent = (specification != nullptr) && (specification[0] != '\0');
	if (m_is_pertinent)
	{
		int value = 0;
		bool in_range = false;
		bool in_default = false;
		bool default_specified = false;
		bool half_range = false;
		size_t pos = 0;

		m_ranges.emplace_back();

		while (specification[pos] && !isalpha(specification[pos]))
		{
			if (specification[pos] == '-')
			{
				// range specifier
				assert(!in_range && !in_default && "Syntax error in specification");

				in_range = true;
				pos++;

				m_ranges.back().max = -1;
				if (!half_range)
				{
					m_ranges.back().min = -1;
					half_range = true;
				}
			}
			else if (specification[pos] == '[')
			{
				// begin default value
				assert(!in_default && !default_specified && "Syntax error in specification");

				in_default = true;
				pos++;
			}
			else if (specification[pos] == ']')
			{
				// end default value
				assert(in_default && "Syntax error in specification");

				in_default = false;
				default_specified = true;
				pos++;

				m_default_value = numeric_value(value);
			}
			else if (specification[pos] == '/')
			{
				// value separator
				assert(!in_default && !in_range && "Syntax error in specification");
				pos++;

				// if we are spitting out ranges, complete the range
				if (half_range)
				{
					m_ranges.emplace_back();
					half_range = false;
				}
			}
			else if (specification[pos] == ';')
			{
				// basic separator
				pos++;
			}
			else if (isdigit(specification[pos]))
			{
				// numeric value */
				value = 0;
				do
				{
					value *= 10;
					value += specification[pos++] - '0';
				} while (isdigit(specification[pos]));

				if (!half_range)
				{
					m_ranges.back().min = value;
					half_range = true;
				}
				m_ranges.back().max = value;
				in_range = false;
			}
			else
			{
				// invalid character - abort because we cannot recover from this syntax error
				throw false;
			}
		}

		// we can't have zero length guidelines strings
		assert(pos > 0);

		// appease compiler for scenarios where assert() has been preprocessed out
		(void)(in_range && in_default && default_specified);
	}
}


// -------------------------------------------------
//  entry::numeric_value
// -------------------------------------------------

std::string option_resolution::entry::numeric_value(int value)
{
	return string_format("%d", value);
}


// -------------------------------------------------
//  entry::value
// -------------------------------------------------

const std::string &option_resolution::entry::value() const
{
	static std::string empty_string;
	return is_pertinent() ? m_value : empty_string;
}


// -------------------------------------------------
//  entry::value_int
// -------------------------------------------------

int option_resolution::entry::value_int() const
{
	return is_pertinent() ? atoi(m_value.c_str()) : -1;
}


// -------------------------------------------------
//  entry::set_value
// -------------------------------------------------

bool option_resolution::entry::set_value(const std::string &value)
{
	// reject the value if this isn't pertinent
	if (!is_pertinent())
		return false;

	// if this is ranged, check against the ranges
	if (is_ranged() && find_in_ranges(std::atoi(value.c_str())) == m_ranges.cend())
		return false;

	// looks good!  change the value
	m_value = value;
	return true;
}


// -------------------------------------------------
//  entry::can_bump_lower
// -------------------------------------------------

bool option_resolution::entry::can_bump_lower() const
{
	return !m_ranges.empty()
		&& value_int() > m_ranges.front().min;
}


// -------------------------------------------------
//  entry::can_bump_higher
// -------------------------------------------------

bool option_resolution::entry::can_bump_higher() const
{
	return !m_ranges.empty()
		&& value_int() < m_ranges.back().max;
}


// -------------------------------------------------
//  entry::bump_lower
// -------------------------------------------------

bool option_resolution::entry::bump_lower()
{
	auto old_value = value_int();
	auto current_range = find_in_ranges(old_value);
	assert(current_range != m_ranges.end());

	int new_value;
	if (old_value > current_range->min)
	{
		// decrement within current range
		new_value = old_value - 1;
	}
	else if (current_range != m_ranges.begin())
	{
		// go to the top of the previous range
		new_value = (current_range - 1)->max;
	}
	else
	{
		// at the minimum; don't bump
		new_value = old_value;
	}

	set_value(new_value);
	return new_value != old_value;
}


// -------------------------------------------------
//  entry::bump_higher
// -------------------------------------------------

bool option_resolution::entry::bump_higher()
{
	auto old_value = value_int();
	auto current_range = find_in_ranges(old_value);
	assert(current_range != m_ranges.end());

	int new_value;
	if (old_value < current_range->max)
	{
		// increment within current range
		new_value = old_value + 1;
	}
	else if (current_range != (m_ranges.end() - 1))
	{
		// go to the bottom of the next range
		new_value = (current_range + 1)->min;
	}
	else
	{
		// at the minimum; don't bump
		new_value = old_value;
	}

	set_value(new_value);
	return new_value != old_value;
}


// -------------------------------------------------
//  entry::find_in_ranges
// -------------------------------------------------

option_resolution::entry::rangelist::const_iterator option_resolution::entry::find_in_ranges(int value) const
{
	return std::find_if(
		m_ranges.begin(),
		m_ranges.end(),
		[&](const auto &r) { return r.min <= value && value <= r.max; });
}


} // namespace util
>>>>>>> upstream/master
