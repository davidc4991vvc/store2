// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

<<<<<<< HEAD
    options.c
=======
    options.cpp
>>>>>>> upstream/master

    Core options code code

***************************************************************************/

#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "options.h"
#include "corestr.h"
#include <string>
<<<<<<< HEAD
#include "../../emu/ui/lang.h"


=======


const int core_options::MAX_UNADORNED_OPTIONS;
>>>>>>> upstream/master

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

const char *const core_options::s_option_unadorned[MAX_UNADORNED_OPTIONS] =
{
	"<UNADORNED0>",
	"<UNADORNED1>",
	"<UNADORNED2>",
	"<UNADORNED3>",
	"<UNADORNED4>",
	"<UNADORNED5>",
	"<UNADORNED6>",
	"<UNADORNED7>",
	"<UNADORNED8>",
	"<UNADORNED9>",
	"<UNADORNED10>",
	"<UNADORNED11>",
	"<UNADORNED12>",
	"<UNADORNED13>",
	"<UNADORNED14>",
	"<UNADORNED15>"
};


<<<<<<< HEAD

//**************************************************************************
//  CORE OPTIONS ENTRY
=======
//**************************************************************************
//  UTILITY
//**************************************************************************

namespace
{
	void trim_spaces_and_quotes(std::string &data)
	{
		// trim any whitespace
		strtrimspace(data);

		// trim quotes
		if (data.find_first_of('"') == 0 && data.find_last_of('"') == data.length() - 1)
		{
			data.erase(0, 1);
			data.erase(data.length() - 1, 1);
		}
	}
};

//**************************************************************************
//  OPTIONS EXCEPTION CLASS
//**************************************************************************

//-------------------------------------------------
//  options_exception - constructor
//-------------------------------------------------

options_exception::options_exception(std::string &&message)
	: m_message(std::move(message))
{
}


//-------------------------------------------------
//  options_warning_exception - constructor
//-------------------------------------------------

options_warning_exception::options_warning_exception(std::string &&message)
	: options_exception(std::move(message))
{
}


//-------------------------------------------------
//  options_error_exception - constructor
//-------------------------------------------------

options_error_exception::options_error_exception(std::string &&message)
	: options_exception(std::move(message))
{
}


//**************************************************************************
//  CORE OPTIONS ENTRY BASE CLASS
>>>>>>> upstream/master
//**************************************************************************

//-------------------------------------------------
//  entry - constructor
//-------------------------------------------------

<<<<<<< HEAD
core_options::entry::entry(const char *name, const char *description, UINT32 flags, const char *defvalue)
	: m_next(NULL),
		m_flags(flags),
		m_seqid(0),
		m_error_reported(false),
		m_priority(OPTION_PRIORITY_DEFAULT),
		m_description(description)
{
	// copy in the name(s) as appropriate
	if (name != NULL)
	{
		// first extract any range
		std::string namestr(name);
		int lparen = namestr.find_first_of('(',0);
		int dash = namestr.find_first_of('-',lparen + 1);
		int rparen = namestr.find_first_of(')',dash + 1);
		if (lparen != -1 && dash != -1 && rparen != -1)
		{
			strtrimspace(m_minimum.assign(namestr.substr(lparen + 1, dash - (lparen + 1))));
			strtrimspace(m_maximum.assign(namestr.substr(dash + 1, rparen - (dash + 1))));
			namestr.erase(lparen, rparen + 1 - lparen);
		}

		// then chop up any semicolon-separated names
		int semi;
		int nameindex = 0;
		while ((semi = namestr.find_first_of(';')) != -1 && nameindex < ARRAY_LENGTH(m_name))
		{
			m_name[nameindex++].assign(namestr.substr(0, semi));
			namestr.erase(0, semi + 1);
		}

		// finally add the last item
		if (nameindex < ARRAY_LENGTH(m_name))
			m_name[nameindex++] = namestr;
	}

	// set the default value
	if (defvalue != NULL)
		m_defdata = defvalue;
	m_data = m_defdata;
=======
core_options::entry::entry(std::vector<std::string> &&names, core_options::option_type type, const char *description)
	: m_names(std::move(names))
	, m_priority(OPTION_PRIORITY_DEFAULT)
	, m_type(type)
	, m_description(description)
{
	assert(m_names.empty() == (m_type == option_type::HEADER));
}

core_options::entry::entry(std::string &&name, core_options::option_type type, const char *description)
	: entry(std::vector<std::string>({ std::move(name) }), type, description)
{
}


//-------------------------------------------------
//  entry - destructor
//-------------------------------------------------

core_options::entry::~entry()
{
}


//-------------------------------------------------
//  entry::value
//-------------------------------------------------

const char *core_options::entry::value() const
{
	// returning 'nullptr' from here signifies a value entry that is essentially "write only"
	// and cannot be meaningfully persisted (e.g. - a command or the software name)
	return nullptr;
}


//-------------------------------------------------
//  entry::set_value
//-------------------------------------------------

void core_options::entry::set_value(std::string &&newvalue, int priority_value, bool always_override)
{
	// it is invalid to set the value on a header
	assert(type() != option_type::HEADER);

	// only set the value if we have priority
	if (always_override || priority_value >= priority())
	{
		internal_set_value(std::move(newvalue));
		m_priority = priority_value;

		// invoke the value changed handler, if appropriate
		if (m_value_changed_handler)
			m_value_changed_handler(value());
	}
}


//-------------------------------------------------
//  entry::set_default_value
//-------------------------------------------------

void core_options::entry::set_default_value(std::string &&newvalue)
{
	// set_default_value() is not necessarily supported for all entry types
	throw false;
}


//-------------------------------------------------
//  entry::validate
//-------------------------------------------------

void core_options::entry::validate(const std::string &data)
{
	float fval;
	int ival;

	switch (type())
	{
	case option_type::BOOLEAN:
		// booleans must be 0 or 1
		if (sscanf(data.c_str(), "%d", &ival) != 1 || ival < 0 || ival > 1)
			throw options_warning_exception("Illegal boolean value for %s: \"%s\"; reverting to %s\n", name(), data, value());
		break;

	case option_type::INTEGER:
		// integers must be integral
		if (sscanf(data.c_str(), "%d", &ival) != 1)
			throw options_warning_exception("Illegal integer value for %s: \"%s\"; reverting to %s\n", name(), data, value());

		// range checking
		if (has_range())
		{
			int minimum_integer = atoi(minimum());
			int maximum_integer = atoi(maximum());
			if (ival < minimum_integer || ival > maximum_integer)
				throw options_warning_exception("Out-of-range integer value for %s: \"%s\" (must be between %d and %d); reverting to %s\n", name(), data, minimum_integer, maximum_integer, value());
		}
		break;

	case option_type::FLOAT:
		if (sscanf(data.c_str(), "%f", &fval) != 1)
			throw options_warning_exception("Illegal float value for %s: \"%s\"; reverting to %s\n", name(), data, value());

		// range checking
		if (has_range())
		{
			float minimum_float = atof(minimum());
			float maximum_float = atof(maximum());
			if (fval < minimum_float || fval > maximum_float)
				throw options_warning_exception("Out-of-range float value for %s: \"%s\" (must be between %f and %f); reverting to %s\n", name(), data, minimum_float, maximum_float, value());
		}
		break;

	case OPTION_STRING:
		// strings can be anything
		break;

	case OPTION_INVALID:
	case OPTION_HEADER:
	default:
		// anything else is invalid
		throw options_error_exception("Attempted to set invalid option %s\n", name());
	}
}


//-------------------------------------------------
//  entry::minimum
//-------------------------------------------------

const char *core_options::entry::minimum() const
{
	return nullptr;
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  set_value - update our data value
//-------------------------------------------------

void core_options::entry::set_value(const char *newdata, int priority)
{
	// ignore if we don't have priority
	if (priority < m_priority)
		return;

	// set the data and priority, then bump the sequence
	m_data = newdata;
	m_priority = priority;
	m_seqid++;
=======
//  entry::maximum
//-------------------------------------------------

const char *core_options::entry::maximum() const
{
	return nullptr;
}


//-------------------------------------------------
//  entry::has_range
//-------------------------------------------------

bool core_options::entry::has_range() const
{
	return minimum() && maximum();
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  set_default_value - set the default value of
//  an option, and reset the current value to it
//-------------------------------------------------

void core_options::entry::set_default_value(const char *defvalue)
{
	m_data = defvalue;
	m_defdata = defvalue;
	m_priority = OPTION_PRIORITY_DEFAULT;
}


//-------------------------------------------------
//  set_description - set the description of
//  an option
//-------------------------------------------------

void core_options::entry::set_description(const char *description)
{
	m_description = description;
}


void core_options::entry::set_flag(UINT32 mask, UINT32 flag)
{
	m_flags = ( m_flags & mask ) | flag;
=======
//  entry::default_value
//-------------------------------------------------

const std::string &core_options::entry::default_value() const
{
	// I don't really want this generally available, but MewUI seems to need it.  Please
	// do not use
	throw false;
}


//**************************************************************************
//  CORE OPTIONS SIMPLE ENTRYCLASS
//**************************************************************************

//-------------------------------------------------
//  simple_entry - constructor
//-------------------------------------------------

core_options::simple_entry::simple_entry(std::vector<std::string> &&names, const char *description, core_options::option_type type, std::string &&defdata, std::string &&minimum, std::string &&maximum)
	: entry(std::move(names), type, description)
	, m_defdata(std::move(defdata))
	, m_minimum(std::move(minimum))
	, m_maximum(std::move(maximum))
{
	m_data = m_defdata;
}


//-------------------------------------------------
//  simple_entry - destructor
//-------------------------------------------------

core_options::simple_entry::~simple_entry()
{
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  revert - revert back to our default if we are
//  at or below the given priority
//-------------------------------------------------

void core_options::entry::revert(int priority)
{
	// if our priority is low enough, revert to the default
	if (m_priority <= priority)
	{
		m_data = m_defdata;
		m_priority = OPTION_PRIORITY_DEFAULT;
	}
}



//**************************************************************************
//  CORE OPTIONS
//**************************************************************************

//-------------------------------------------------
//  core_options - constructor
//-------------------------------------------------

core_options::core_options()
{
}

core_options::core_options(const options_entry *entrylist)
{
	add_entries(entrylist);
}

core_options::core_options(const options_entry *entrylist1, const options_entry *entrylist2)
{
	add_entries(entrylist1);
	add_entries(entrylist2);
}

core_options::core_options(const options_entry *entrylist1, const options_entry *entrylist2, const options_entry *entrylist3)
{
	add_entries(entrylist1);
	add_entries(entrylist2);
	add_entries(entrylist3);
}

core_options::core_options(const core_options &src)
{
	copyfrom(src);
}


//-------------------------------------------------
//  ~core_options - destructor
//-------------------------------------------------

core_options::~core_options()
=======
//  simple_entry::value
//-------------------------------------------------

const char *core_options::simple_entry::value() const
{
	const char *result;
	switch (type())
	{
	case core_options::option_type::BOOLEAN:
	case core_options::option_type::INTEGER:
	case core_options::option_type::FLOAT:
	case core_options::option_type::STRING:
		result = m_data.c_str();
		break;

	default:
		// this is an option type for which returning a value is
		// a meaningless operation (e.g. - core_options::option_type::COMMAND)
		result = nullptr;
		break;
	}
	return result;
}


//-------------------------------------------------
//  simple_entry::default_value
//-------------------------------------------------

const std::string &core_options::simple_entry::default_value() const
{
	// only MewUI seems to need this; please don't use
	return m_defdata;
}


//-------------------------------------------------
//  internal_set_value
//-------------------------------------------------

void core_options::simple_entry::internal_set_value(std::string &&newvalue)
{
	m_data = std::move(newvalue);
}


//-------------------------------------------------
//  set_default_value
//-------------------------------------------------

void core_options::simple_entry::set_default_value(std::string &&newvalue)
{
	m_data = m_defdata = std::move(newvalue);
}


//-------------------------------------------------
//  minimum
//-------------------------------------------------

const char *core_options::simple_entry::minimum() const
{
	return m_minimum.c_str();
}


//-------------------------------------------------
//  maximum
//-------------------------------------------------

const char *core_options::simple_entry::maximum() const
{
	return m_maximum.c_str();
}


//**************************************************************************
//  CORE OPTIONS
//**************************************************************************

//-------------------------------------------------
//  core_options - constructor
//-------------------------------------------------

core_options::core_options()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
<<<<<<< HEAD
//  operator= - assignment operator
//-------------------------------------------------

core_options &core_options::operator=(const core_options &rhs)
{
	// ignore self-assignment
	if (this != &rhs)
		copyfrom(rhs);
	return *this;
=======
//  ~core_options - destructor
//-------------------------------------------------

core_options::~core_options()
{
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  operator== - compare two sets of options
//-------------------------------------------------

bool core_options::operator==(const core_options &rhs)
{
	// iterate over options in the first list
	for (entry *curentry = m_entrylist.first(); curentry != NULL; curentry = curentry->next())
		if (!curentry->is_header())
		{
			// if the values differ, return false
			if (strcmp(curentry->value(), rhs.value(curentry->name())) != 0)
				return false;
		}

	return true;
=======
//  add_entry - adds an entry
//-------------------------------------------------

void core_options::add_entry(entry::shared_ptr &&entry, const char *after_header)
{
	// update the entry map
	for (const std::string &name : entry->names())
	{
		// append the entry
		add_to_entry_map(std::string(name), entry);

		// for booleans, add the "-noXYZ" option as well
		if (entry->type() == option_type::BOOLEAN)
			add_to_entry_map(std::string("no") + name, entry);
	}

	// and add the entry to the vector
	m_entries.emplace_back(std::move(entry));
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  operator!= - compare two sets of options
//-------------------------------------------------

bool core_options::operator!=(const core_options &rhs)
{
	return !operator==(rhs);
=======
//  add_to_entry_map - adds an entry to the entry
//  map
//-------------------------------------------------

void core_options::add_to_entry_map(std::string &&name, entry::shared_ptr &entry)
{
	// it is illegal to call this method for something that already ex0ists
	assert(m_entrymap.find(name) == m_entrymap.end());

	// append the entry
	m_entrymap.emplace(std::make_pair(name, entry::weak_ptr(entry)));
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  add_entry - add an entry to the current
//  options set
//-------------------------------------------------

void core_options::add_entry(const char *name, const char *description, UINT32 flags, const char *defvalue, bool override_existing)
{
	// allocate a new entry
	entry *newentry = global_alloc(entry(name, description, flags, defvalue));
	if (newentry->name() != NULL)
	{
		// see if we match an existing entry
		entry *existing = m_entrymap.find(newentry->name());
		if (existing != NULL)
		{
			// if we're overriding existing entries, then remove the old one
			if (override_existing)
				m_entrylist.remove(*existing);

			// otherwise, just override the default and current values and throw out the new entry
			else
			{
				existing->set_default_value(newentry->value());
				global_free(newentry);
				return;
			}
		}
	}

	// add us to the list and maps
	append_entry(*newentry);
=======
//  add_entry - adds an entry based on an
//  options_entry
//-------------------------------------------------

void core_options::add_entry(const options_entry &opt, bool override_existing)
{
	std::vector<std::string> names;
	std::string minimum, maximum;

	// copy in the name(s) as appropriate
	if (opt.name)
	{
		// first extract any range
		std::string namestr(opt.name);
		int lparen = namestr.find_first_of('(', 0);
		int dash = namestr.find_first_of('-', lparen + 1);
		int rparen = namestr.find_first_of(')', dash + 1);
		if (lparen != -1 && dash != -1 && rparen != -1)
		{
			strtrimspace(minimum.assign(namestr.substr(lparen + 1, dash - (lparen + 1))));
			strtrimspace(maximum.assign(namestr.substr(dash + 1, rparen - (dash + 1))));
			namestr.erase(lparen, rparen + 1 - lparen);
		}

		// then chop up any semicolon-separated names
		size_t semi;
		while ((semi = namestr.find_first_of(';')) != std::string::npos)
		{
			names.push_back(namestr.substr(0, semi));
			namestr.erase(0, semi + 1);
		}

		// finally add the last item
		names.push_back(std::move(namestr));
	}

	// we might be called with an existing entry
	entry::shared_ptr existing_entry;
	do
	{
		for (const std::string &name : names)
		{
			existing_entry = get_entry(name.c_str());
			if (existing_entry)
				break;
		}

		if (existing_entry)
		{
			if (override_existing)
				remove_entry(*existing_entry);
			else
				return;
		}
	} while (existing_entry);

	// set the default value
	std::string defdata = opt.defvalue ? opt.defvalue : "";

	// create and add the entry
	add_entry(
			std::move(names),
			opt.description,
			opt.type,
			std::move(defdata),
			std::move(minimum),
			std::move(maximum));
}


//-------------------------------------------------
//  add_entry
//-------------------------------------------------

void core_options::add_entry(std::vector<std::string> &&names, const char *description, option_type type, std::string &&default_value, std::string &&minimum, std::string &&maximum)
{
	// create the entry
	entry::shared_ptr new_entry = std::make_shared<simple_entry>(
			std::move(names),
			description,
			type,
			std::move(default_value),
			std::move(minimum),
			std::move(maximum));

	// and add it
	add_entry(std::move(new_entry));
}


//-------------------------------------------------
//  add_header
//-------------------------------------------------

void core_options::add_header(const char *description)
{
	add_entry(std::vector<std::string>(), description, option_type::HEADER);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  add_entries - add entries to the current
//  options sets
//-------------------------------------------------

void core_options::add_entries(const options_entry *entrylist, bool override_existing)
{
<<<<<<< HEAD
	// loop over entries until we hit a NULL name
	for ( ; entrylist->name != NULL || (entrylist->flags & OPTION_HEADER) != 0; entrylist++)
		add_entry(*entrylist, override_existing);
=======
	// loop over entries until we hit a nullptr name
	for (int i = 0; entrylist[i].name || entrylist[i].type == option_type::HEADER; i++)
		add_entry(entrylist[i], override_existing);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  set_default_value - change the default value
//  of an option
//-------------------------------------------------

void core_options::set_default_value(const char *name, const char *defvalue)
{
<<<<<<< HEAD
	// find the entry and bail if we can't
	entry *curentry = m_entrymap.find(name);
	if (curentry == NULL)
		return;

	// update the data and default data
	curentry->set_default_value(defvalue);
=======
	// update the data and default data
	get_entry(name)->set_default_value(defvalue);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  set_description - change the description
//  of an option
//-------------------------------------------------

void core_options::set_description(const char *name, const char *description)
{
<<<<<<< HEAD
	// find the entry and bail if we can't
	entry *curentry = m_entrymap.find(name);
	if (curentry == NULL)
		return;

	// update the data and default data
	curentry->set_description(description);
=======
	// update the data and default data
	get_entry(name)->set_description(description);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  parse_command_line - parse a series of
//  command line arguments
//-------------------------------------------------

<<<<<<< HEAD
bool core_options::parse_command_line(int argc, char **argv, int priority, std::string &error_string)
{
	// reset the errors and the command
	error_string.clear();
	m_command.clear();

	// iterate through arguments
	int unadorned_index = 0;
	bool retval = true;
	for (int arg = 1; arg < argc; arg++)
	{
		// determine the entry name to search for
		const char *curarg = argv[arg];
		bool is_unadorned = (curarg[0] != '-');
		const char *optionname = is_unadorned ? core_options::unadorned(unadorned_index++) : &curarg[1];

		// find our entry; if not found, indicate invalid option
		entry *curentry = m_entrymap.find(optionname);
		if (curentry == NULL)
		{
			strcatprintf(error_string, "Error: unknown option: %s\n", curarg);
			retval = false;
			if (!is_unadorned) arg++;
			continue;
		}

		// process commands first
		if (curentry->type() == OPTION_COMMAND)
		{
			// can only have one command
			if (!m_command.empty())
			{
				strcatprintf(error_string,"Error: multiple commands specified -%s and %s\n", m_command.c_str(), curarg);
				return false;
			}
			m_command = curentry->name();
			continue;
		}

		// get the data for this argument, special casing booleans
		const char *newdata;
		if (curentry->type() == OPTION_BOOLEAN)
			newdata = (strncmp(&curarg[1], "no", 2) == 0) ? "0" : "1";
		else if (is_unadorned)
			newdata = curarg;
		else if (arg + 1 < argc)
			newdata = argv[++arg];
		else
		{
			strcatprintf(error_string, "Error: option %s expected a parameter\n", curarg);
			return false;
		}

		// set the new data
		validate_and_set_data(*curentry, newdata, priority, error_string);
	}
	return retval;
=======
void core_options::parse_command_line(const std::vector<std::string> &args, int priority, bool ignore_unknown_options)
{
	std::ostringstream error_stream;
	condition_type condition = condition_type::NONE;

	// reset the errors and the command
	m_command.clear();

	// we want to identify commands first
	for (size_t arg = 1; arg < args.size(); arg++)
	{
		if (!args[arg].empty() && args[arg][0] == '-')
		{
			auto curentry = get_entry(&args[arg][1]);
			if (curentry && curentry->type() == OPTION_COMMAND)
			{
				// can only have one command
				if (!m_command.empty())
					throw options_error_exception("Error: multiple commands specified -%s and %s\n", m_command, args[arg]);

				m_command = curentry->name();
			}
		}
	}

	// iterate through arguments
	int unadorned_index = 0;
	for (size_t arg = 1; arg < args.size(); arg++)
	{
		// determine the entry name to search for
		const char *curarg = args[arg].c_str();
		bool is_unadorned = (curarg[0] != '-');
		const char *optionname = is_unadorned ? core_options::unadorned(unadorned_index++) : &curarg[1];

		// special case - collect unadorned arguments after commands into a special place
		if (is_unadorned && !m_command.empty())
		{
			m_command_arguments.push_back(std::move(args[arg]));
			command_argument_processed();
			continue;
		}

		// find our entry; if not found, continue
		auto curentry = get_entry(optionname);
		if (!curentry)
		{
			if (!ignore_unknown_options)
				throw options_error_exception("Error: unknown option: -%s\n", optionname);
			continue;
		}

		// at this point, we've already processed commands
		if (curentry->type() == OPTION_COMMAND)
			continue;

		// get the data for this argument, special casing booleans
		std::string newdata;
		if (curentry->type() == option_type::BOOLEAN)
		{
			newdata = (strncmp(&curarg[1], "no", 2) == 0) ? "0" : "1";
		}
		else if (is_unadorned)
		{
			newdata = curarg;
		}
		else if (arg + 1 < args.size())
		{
			newdata = args[++arg];
		}
		else
		{
			throw options_error_exception("Error: option %s expected a parameter\n", curarg);
		}

		// set the new data
		do_set_value(*curentry, std::move(newdata), priority, error_stream, condition);
	}

	// did we have any errors that may need to be aggregated?
	throw_options_exception_if_appropriate(condition, error_stream);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  parse_ini_file - parse a series of entries in
//  an INI file
//-------------------------------------------------

<<<<<<< HEAD
bool core_options::parse_ini_file(core_file &inifile, int priority, int ignore_priority, std::string &error_string)
{
	// loop over lines in the file
	char buffer[4096];
	while (core_fgets(buffer, ARRAY_LENGTH(buffer), &inifile) != NULL)
=======
void core_options::parse_ini_file(util::core_file &inifile, int priority, bool ignore_unknown_options, bool always_override)
{
	std::ostringstream error_stream;
	condition_type condition = condition_type::NONE;

	// loop over lines in the file
	char buffer[4096];
	while (inifile.gets(buffer, ARRAY_LENGTH(buffer)) != nullptr)
>>>>>>> upstream/master
	{
		// find the extent of the name
		char *optionname;
		for (optionname = buffer; *optionname != 0; optionname++)
<<<<<<< HEAD
			if (!isspace((UINT8)*optionname))
=======
			if (!isspace((uint8_t)*optionname))
>>>>>>> upstream/master
				break;

		// skip comments
		if (*optionname == 0 || *optionname == '#')
			continue;

		// scan forward to find the first space
		char *temp;
		for (temp = optionname; *temp != 0; temp++)
<<<<<<< HEAD
			if (isspace((UINT8)*temp))
=======
			if (isspace((uint8_t)*temp))
>>>>>>> upstream/master
				break;

		// if we hit the end early, print a warning and continue
		if (*temp == 0)
		{
<<<<<<< HEAD
			strcatprintf(error_string,"Warning: invalid line in INI: %s", buffer);
=======
			condition = std::max(condition, condition_type::WARN);
			util::stream_format(error_stream, "Warning: invalid line in INI: %s", buffer);
>>>>>>> upstream/master
			continue;
		}

		// NULL-terminate
		*temp++ = 0;
		char *optiondata = temp;

		// scan the data, stopping when we hit a comment
		bool inquotes = false;
		for (temp = optiondata; *temp != 0; temp++)
		{
			if (*temp == '"')
				inquotes = !inquotes;
			if (*temp == '#' && !inquotes)
				break;
		}
		*temp = 0;

		// find our entry
<<<<<<< HEAD
		entry *curentry = m_entrymap.find(optionname);
		if (curentry == NULL)
		{
			if (priority >= ignore_priority)
				strcatprintf(error_string, "Warning: unknown option in INI: %s\n", optionname);
=======
		entry::shared_ptr curentry = get_entry(optionname);
		if (!curentry)
		{
			if (!ignore_unknown_options)
			{
				condition = std::max(condition, condition_type::WARN);
				util::stream_format(error_stream, "Warning: unknown option in INI: %s\n", optionname);
			}
>>>>>>> upstream/master
			continue;
		}

		// set the new data
<<<<<<< HEAD
		validate_and_set_data(*curentry, optiondata, priority, error_string);
	}
	return true;
=======
		std::string data = optiondata;
		trim_spaces_and_quotes(data);
		do_set_value(*curentry, std::move(data), priority, error_stream, condition);
	}

	// did we have any errors that may need to be aggregated?
	throw_options_exception_if_appropriate(condition, error_stream);
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  revert - revert options at or below a certain
//  priority back to their defaults
//-------------------------------------------------

void core_options::revert(int priority)
{
	// iterate over options and revert to defaults if below the given priority
	for (entry *curentry = m_entrylist.first(); curentry != NULL; curentry = curentry->next())
		curentry->revert(priority);
}

/*-------------------------------------------------
    translate_description - translate description
    by UI_MSG_MAME or UI_MSG_OSD0
-------------------------------------------------*/

const char *core_options::translate_description(const char *description)
{
	const char *desc = _(description);

	// osd/windows
	if (desc == description)
		desc = lang_message(UI_MSG_OSD0, desc);

	// osd/winui
	if (desc == description)
		return lang_message(UI_MSG_OSD1, desc);

	return desc;
}

=======
//  throw_options_exception_if_appropriate
//-------------------------------------------------

void core_options::throw_options_exception_if_appropriate(core_options::condition_type condition, std::ostringstream &error_stream)
{
	switch(condition)
	{
	case condition_type::NONE:
		// do nothing
		break;

	case condition_type::WARN:
		throw options_warning_exception(error_stream.str());

	case condition_type::ERR:
		throw options_error_exception(error_stream.str());

	default:
		// should not get here
		throw false;
	}
}


//-------------------------------------------------
//  copy_from
//-------------------------------------------------

void core_options::copy_from(const core_options &that)
{
	for (auto &dest_entry : m_entries)
	{
		if (dest_entry->names().size() > 0)
		{
			// identify the source entry
			const entry::shared_ptr source_entry = that.get_entry(dest_entry->name());
			if (source_entry)
			{
				const char *value = source_entry->value();
				if (value)
					dest_entry->set_value(value, source_entry->priority(), true);
			}
		}
	}
}


>>>>>>> upstream/master
//-------------------------------------------------
//  output_ini - output the options in INI format,
//  only outputting entries that different from
//  the optional diff
//-------------------------------------------------

<<<<<<< HEAD
const char *core_options::output_ini(std::string &buffer, const core_options *diff)
{
	// INI files are complete, so always start with a blank buffer
	buffer.clear();

	int num_valid_headers = 0;
	int unadorned_index = 0;
	const char *last_header = NULL;

	// loop over all items
	for (entry *curentry = m_entrylist.first(); curentry != NULL; curentry = curentry->next())
	{
		const char *name = curentry->name();
		const char *value = curentry->value();
		bool is_unadorned = false;

		// check if it's unadorned
		if (name && strlen(name) && !strcmp(name, core_options::unadorned(unadorned_index)))
		{
			unadorned_index++;
			is_unadorned = true;
		}

		// header: record description
		if (curentry->is_header())
			last_header = translate_description(curentry->description());

		// otherwise, output entries for all non-command items
		else if (!curentry->is_command())
		{
			if ( !curentry->is_internal() )
			{
				// look up counterpart in diff, if diff is specified
				if (diff == NULL || strcmp(value, diff->value(name)) != 0)
				{
					// output header, if we have one
					if (last_header != NULL)
					{
						if (num_valid_headers++)
							strcatprintf(buffer,"\n");
						strcatprintf(buffer, "#\n# %s\n#\n", last_header);
						last_header = NULL;
=======
std::string core_options::output_ini(const core_options *diff) const
{
	// INI files are complete, so always start with a blank buffer
	std::ostringstream buffer;

	int num_valid_headers = 0;
	int unadorned_index = 0;
	const char *last_header = nullptr;
	std::string overridden_value;

	// loop over all items
	for (auto &curentry : m_entries)
	{
		if (curentry->type() == option_type::HEADER)
		{
			// header: record description
			last_header = curentry->description();
		}
		else
		{
			const std::string &name(curentry->name());
			const char *value(curentry->value());

			// check if it's unadorned
			bool is_unadorned = false;
			if (name == core_options::unadorned(unadorned_index))
			{
				unadorned_index++;
				is_unadorned = true;
			}

			// output entries for all non-command items (items with value)
			if (value)
			{
				// look up counterpart in diff, if diff is specified
				if (!diff || strcmp(value, diff->value(name.c_str())))
				{
					// output header, if we have one
					if (last_header)
					{
						if (num_valid_headers++)
							buffer << '\n';
						util::stream_format(buffer, "#\n# %s\n#\n", last_header);
						last_header = nullptr;
>>>>>>> upstream/master
					}

					// and finally output the data, skip if unadorned
					if (!is_unadorned)
					{
<<<<<<< HEAD
						if (strchr(value, ' ') != NULL)
							strcatprintf(buffer,"%-25s \"%s\"\n", name, value);
						else
							strcatprintf(buffer,"%-25s %s\n", name, value);
=======
						if (strchr(value, ' '))
							util::stream_format(buffer, "%-25s \"%s\"\n", name, value);
						else
							util::stream_format(buffer, "%-25s %s\n", name, value);
>>>>>>> upstream/master
					}
				}
			}
		}
	}
<<<<<<< HEAD
	return buffer.c_str();
=======
	return buffer.str();
>>>>>>> upstream/master
}


//-------------------------------------------------
//  output_help - output option help to a string
//-------------------------------------------------

<<<<<<< HEAD
const char *core_options::output_help(std::string &buffer)
{
	// start empty
	buffer.clear();

	// loop over all items
	for (entry *curentry = m_entrylist.first(); curentry != NULL; curentry = curentry->next())
	{
		// header: just print
		if (curentry->is_header())
			strcatprintf(buffer,"\n#\n# %s\n#\n", translate_description(curentry->description()));

		// otherwise, output entries for all non-deprecated items
		else if (curentry->description() != NULL)
			strcatprintf(buffer,"-%-20s%s\n", curentry->name(), translate_description(curentry->description()));
	}
	return buffer.c_str();
=======
std::string core_options::output_help() const
{
	// start empty
	std::ostringstream buffer;

	// loop over all items
	for (auto &curentry : m_entries)
	{
		// header: just print
		if (curentry->type() == option_type::HEADER)
			util::stream_format(buffer, "\n#\n# %s\n#\n", curentry->description());

		// otherwise, output entries for all non-deprecated items
		else if (curentry->description() != nullptr)
			util::stream_format(buffer, "-%-20s%s\n", curentry->name(), curentry->description());
	}
	return buffer.str();
>>>>>>> upstream/master
}


//-------------------------------------------------
//  value - return the raw option value
//-------------------------------------------------

<<<<<<< HEAD
const char *core_options::value(const char *name) const
{
	entry *curentry = m_entrymap.find(name);
	return (curentry != NULL) ? curentry->value() : "";
=======
const char *core_options::value(const char *option) const
{
	return get_entry(option)->value();
>>>>>>> upstream/master
}


//-------------------------------------------------
//  description - return description of option
//-------------------------------------------------

<<<<<<< HEAD
const char *core_options::description(const char *name) const
{
	entry *curentry = m_entrymap.find(name);
	return (curentry != NULL) ? curentry->description() : "";
}


//-------------------------------------------------
//  priority - return the priority of option
//-------------------------------------------------

int core_options::priority(const char *name) const
{
	entry *curentry = m_entrymap.find(name);
	return (curentry != NULL) ? curentry->priority() : 0;
}


//-------------------------------------------------
//  seqid - return the seqid for a given option
//-------------------------------------------------

UINT32 core_options::seqid(const char *name) const
{
	entry *curentry = m_entrymap.find(name);
	return (curentry != NULL) ? curentry->seqid() : 0;
}

//-------------------------------------------------
//  exists - return if option exists in list
//-------------------------------------------------

bool core_options::exists(const char *name) const
{
	entry *curentry = m_entrymap.find(name);
	return (curentry != NULL);
}
=======
const char *core_options::description(const char *option) const
{
	return get_entry(option)->description();
}


//**************************************************************************
//  LEGACY
//**************************************************************************
>>>>>>> upstream/master

//-------------------------------------------------
//  set_value - set the raw option value
//-------------------------------------------------

<<<<<<< HEAD
bool core_options::set_value(const char *name, const char *value, int priority, std::string &error_string)
{
	// find the entry first
	entry *curentry = m_entrymap.find(name);
	if (curentry == NULL)
	{
		strcatprintf(error_string, "Attempted to set unknown option %s\n", name);
		return false;
	}

	// validate and set the item normally
	return validate_and_set_data(*curentry, value, priority, error_string);
}

bool core_options::set_value(const char *name, int value, int priority, std::string &error_string)
{
	std::string tempstr;
	strprintf(tempstr,"%d", value);
	return set_value(name, tempstr.c_str(), priority, error_string);
}

bool core_options::set_value(const char *name, float value, int priority, std::string &error_string)
{
	std::string tempstr;
	strprintf(tempstr, "%f", (double) value);
	return set_value(name, tempstr.c_str(), priority, error_string);
}


void core_options::set_flag(const char *name, UINT32 mask, UINT32 flag)
{
	// find the entry first
	entry *curentry = m_entrymap.find(name);
	if ( curentry == NULL )
	{
		return;
	}
	curentry->set_flag(mask, flag);
=======
void core_options::set_value(const std::string &name, const std::string &value, int priority)
{
	set_value(name, std::string(value), priority);
}

void core_options::set_value(const std::string &name, std::string &&value, int priority)
{
	get_entry(name)->set_value(std::move(value), priority);
}

void core_options::set_value(const std::string &name, int value, int priority)
{
	set_value(name, string_format("%d", value), priority);
}

void core_options::set_value(const std::string &name, float value, int priority)
{
	set_value(name, string_format("%f", value), priority);
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  reset - reset the options state, removing
//  everything
//-------------------------------------------------

void core_options::reset()
{
	m_entrylist.reset();
	m_entrymap.reset();
=======
//  remove_entry - remove an entry from our list
//  and map
//-------------------------------------------------

void core_options::remove_entry(core_options::entry &delentry)
{
	// find this in m_entries
	auto iter = std::find_if(
			m_entries.begin(),
			m_entries.end(),
			[&delentry](const auto &x) { return &*x == &delentry; });
	assert(iter != m_entries.end());

	// erase each of the items out of the entry map
	for (const std::string &name : delentry.names())
		m_entrymap.erase(name);

	// finally erase it
	m_entries.erase(iter);
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  append_entry - append an entry to our list
//  and index it in the map
//-------------------------------------------------

void core_options::append_entry(core_options::entry &newentry)
{
	m_entrylist.append(newentry);

	// if we have names, add them to the map
	for (int name = 0; name < ARRAY_LENGTH(newentry.m_name); name++)
		if (newentry.name(name) != NULL)
		{
			m_entrymap.add(newentry.name(name), &newentry);

			// for boolean options add a "no" variant as well
			if (newentry.type() == OPTION_BOOLEAN)
				m_entrymap.add(std::string("no").append(newentry.name(name)).c_str(), &newentry);
		}
=======
//  do_set_value
//-------------------------------------------------

void core_options::do_set_value(entry &curentry, std::string &&data, int priority, std::ostream &error_stream, condition_type &condition)
{
	// this is called when parsing a command line or an INI - we want to catch the option_exception and write
	// any exception messages to the error stream
	try
	{
		curentry.set_value(std::move(data), priority);
	}
	catch (options_warning_exception &ex)
	{
		// we want to aggregate option exceptions
		error_stream << ex.message();
		condition = std::max(condition, condition_type::WARN);
	}
	catch (options_error_exception &ex)
	{
		// we want to aggregate option exceptions
		error_stream << ex.message();
		condition = std::max(condition, condition_type::ERR);
	}
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  remove_entry - remove an entry from our list
//  and map
//-------------------------------------------------

void core_options::remove_entry(core_options::entry &delentry)
{
	// remove all names from the map
	for (int name = 0; name < ARRAY_LENGTH(delentry.m_name); name++)
		if (!delentry.m_name[name].empty())
			m_entrymap.remove(delentry.m_name[name].c_str());

	// remove the entry from the list
	m_entrylist.remove(delentry);
=======
//  get_entry
//-------------------------------------------------

const core_options::entry::shared_ptr core_options::get_entry(const std::string &name) const
{
	auto curentry = m_entrymap.find(name);
	return (curentry != m_entrymap.end()) ? curentry->second.lock() : nullptr;
}

core_options::entry::shared_ptr core_options::get_entry(const std::string &name)
{
	auto curentry = m_entrymap.find(name);
	return (curentry != m_entrymap.end()) ? curentry->second.lock() : nullptr;
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  copyfrom - copy options from another set
//-------------------------------------------------

void core_options::copyfrom(const core_options &src)
{
	// reset ourselves first
	reset();

	// iterate through the src options and make our own
	for (entry *curentry = src.m_entrylist.first(); curentry != NULL; curentry = curentry->next())
		append_entry(*global_alloc(entry(curentry->name(), curentry->description(), curentry->flags(), curentry->default_value())));
=======
//  set_value_changed_handler
//-------------------------------------------------

void core_options::set_value_changed_handler(const std::string &name, std::function<void(const char *)> &&handler)
{
	get_entry(name)->set_value_changed_handler(std::move(handler));
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  validate_and_set_data - make sure the data is
//  of the appropriate type and within range,
//  then set it
//-------------------------------------------------

bool core_options::validate_and_set_data(core_options::entry &curentry, const char *newdata, int priority, std::string &error_string)
{
	// trim any whitespace
	std::string data(newdata);
	strtrimspace(data);


	// trim quotes
	if (data.find_first_of('"') == 0 && data.find_last_of('"') == data.length() - 1)
	{
		data.erase(0, 1);
		data.erase(data.length() - 1, 1);
	}

	// validate the type of data and optionally the range
	float fval;
	int ival;
	switch (curentry.type())
	{
		// booleans must be 0 or 1
		case OPTION_BOOLEAN:
			if (sscanf(data.c_str(), "%d", &ival) != 1 || ival < 0 || ival > 1)
			{
				strcatprintf(error_string, "Illegal boolean value for %s: \"%s\"; reverting to %s\n", curentry.name(), data.c_str(), curentry.value());
				return false;
			}
			break;

		// integers must be integral
		case OPTION_INTEGER:
			if (sscanf(data.c_str(), "%d", &ival) != 1)
			{
				strcatprintf(error_string, "Illegal integer value for %s: \"%s\"; reverting to %s\n", curentry.name(), data.c_str(), curentry.value());
				return false;
			}
			if (curentry.has_range() && (ival < atoi(curentry.minimum()) || ival > atoi(curentry.maximum())))
			{
				strcatprintf(error_string, "Out-of-range integer value for %s: \"%s\" (must be between %s and %s); reverting to %s\n", curentry.name(), data.c_str(), curentry.minimum(), curentry.maximum(), curentry.value());
				return false;
			}
			break;

		// floating-point values must be numeric
		case OPTION_FLOAT:
			if (sscanf(data.c_str(), "%f", &fval) != 1)
			{
				strcatprintf(error_string, "Illegal float value for %s: \"%s\"; reverting to %s\n", curentry.name(), data.c_str(), curentry.value());
				return false;
			}
			if (curentry.has_range() && ((double) fval < atof(curentry.minimum()) || (double) fval > atof(curentry.maximum())))
			{
				strcatprintf(error_string, "Out-of-range float value for %s: \"%s\" (must be between %s and %s); reverting to %s\n", curentry.name(), data.c_str(), curentry.minimum(), curentry.maximum(), curentry.value());
				return false;
			}
			break;

		// strings can be anything
		case OPTION_STRING:
			break;

		// anything else is invalid
		case OPTION_INVALID:
		case OPTION_HEADER:
		default:
			strcatprintf(error_string, "Attempted to set invalid option %s\n", curentry.name());
			return false;
	}

	// set the data
	curentry.set_value(data.c_str(), priority);
	return true;
=======
//  header_exists
//-------------------------------------------------

bool core_options::header_exists(const char *description) const
{
	auto iter = std::find_if(
		m_entries.begin(),
		m_entries.end(),
		[description](const auto &entry)
		{
			return entry->type() == option_type::HEADER
					&& entry->description()
					&& !strcmp(entry->description(), description);
		});

	return iter != m_entries.end();
>>>>>>> upstream/master
}
