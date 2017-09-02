// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
/*********************************************************************

    softlist.h

<<<<<<< HEAD
    Software and software list information.

*********************************************************************/

#ifndef __SOFTLIST_H_
#define __SOFTLIST_H_

#include "cstrpool.h"


=======
    Software list file format.

*********************************************************************/

#ifndef MAME_EMU_SOFTLIST_H
#define MAME_EMU_SOFTLIST_H

#pragma once


#include "emucore.h"
#include "romentry.h"
#include "corefile.h"

#include <list>

>>>>>>> upstream/master

//**************************************************************************
//  CONSTANTS
//**************************************************************************

#define SOFTWARE_SUPPORTED_YES      0
#define SOFTWARE_SUPPORTED_PARTIAL  1
#define SOFTWARE_SUPPORTED_NO       2

<<<<<<< HEAD
enum softlist_type
{
	SOFTWARE_LIST_ORIGINAL_SYSTEM,
	SOFTWARE_LIST_COMPATIBLE_SYSTEM
};



//**************************************************************************
//  MACROS
//**************************************************************************

#define MCFG_SOFTWARE_LIST_CONFIG(_list,_list_type) \
	software_list_device::static_set_type(*device, _list, _list_type);

#define MCFG_SOFTWARE_LIST_ADD( _tag, _list ) \
	MCFG_DEVICE_ADD( _tag, SOFTWARE_LIST, 0 ) \
	MCFG_SOFTWARE_LIST_CONFIG(_list, SOFTWARE_LIST_ORIGINAL_SYSTEM)

#define MCFG_SOFTWARE_LIST_COMPATIBLE_ADD( _tag, _list ) \
	MCFG_DEVICE_ADD( _tag, SOFTWARE_LIST, 0 ) \
	MCFG_SOFTWARE_LIST_CONFIG(_list, SOFTWARE_LIST_COMPATIBLE_SYSTEM)

#define MCFG_SOFTWARE_LIST_MODIFY( _tag, _list ) \
	MCFG_DEVICE_MODIFY( _tag ) \
	MCFG_SOFTWARE_LIST_CONFIG(_list, SOFTWARE_LIST_ORIGINAL_SYSTEM)

#define MCFG_SOFTWARE_LIST_COMPATIBLE_MODIFY( _tag, _list ) \
	MCFG_DEVICE_MODIFY( _tag ) \
	MCFG_SOFTWARE_LIST_CONFIG(_list, SOFTWARE_LIST_COMPATIBLE_SYSTEM)

#define MCFG_SOFTWARE_LIST_FILTER( _tag, _filter ) \
	MCFG_DEVICE_MODIFY( _tag ) \
	software_list_device::static_set_filter(*device, _filter);

#define MCFG_SOFTWARE_LIST_REMOVE( _tag ) \
	MCFG_DEVICE_REMOVE( _tag )


=======
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> feature_list_item

// an item in a list of name/value pairs
class feature_list_item
{
<<<<<<< HEAD
	friend class simple_list<feature_list_item>;

public:
	// construction/destruction
	feature_list_item(const char *name = NULL, const char *value = NULL)
		: m_next(NULL),
			m_name(name),
			m_value(value) { }

	// getters
	feature_list_item *next() const { return m_next; }
	const char *name() const { return m_name; }
	const char *value() const { return m_value; }
=======
public:
	// construction/destruction
	feature_list_item(std::string &&name, std::string &&value);
	feature_list_item(const std::string &name, const std::string &value);
	feature_list_item(feature_list_item const &) = delete;
	feature_list_item(feature_list_item &&) = delete;
	feature_list_item& operator=(feature_list_item const &) = delete;
	feature_list_item& operator=(feature_list_item &&) = delete;

	// getters
	feature_list_item *next() const { return m_next; }
	const std::string &name() const { return m_name; }
	const std::string &value() const { return m_value; }
>>>>>>> upstream/master

private:
	// internal state
	feature_list_item * m_next;
<<<<<<< HEAD
	const char *        m_name;
	const char *        m_value;
=======
	std::string         m_name;
	std::string         m_value;
>>>>>>> upstream/master
};


// ======================> software_part

// a single part of a software item
class software_part
{
	friend class softlist_parser;
<<<<<<< HEAD
	friend class simple_list<software_part>;

public:
	// construction/destruction
	software_part(software_info &info, const char *name = NULL, const char *interface = NULL);
=======

public:
	// construction/destruction
	software_part(software_info &info, std::string &&name, std::string &&interface);
	software_part(software_part const &) = delete;
	software_part(software_part &&) = delete;
	software_part& operator=(software_part const &) = delete;
	software_part& operator=(software_part &&) = delete;
>>>>>>> upstream/master

	// getters
	software_part *next() const { return m_next; }
	software_info &info() const { return m_info; }
<<<<<<< HEAD
	const char *name() const { return m_name; }
	const char *interface() const { return m_interface; }
	feature_list_item *featurelist() const { return m_featurelist.first(); }
	rom_entry *romdata(unsigned int index = 0) { return (index < m_romdata.size()) ? &m_romdata[index] : NULL; }

	// helpers
	bool is_compatible(const software_list_device &swlist) const;
	bool matches_interface(const char *interface) const;
	const char *feature(const char *feature_name) const;

private:
	// internal state
	software_part *     m_next;
	software_info &     m_info;
	const char *        m_name;
	const char *        m_interface;
	simple_list<feature_list_item> m_featurelist;
	std::vector<rom_entry>   m_romdata;
=======
	const std::string &name() const { return m_name; }
	const std::string &interface() const { return m_interface; }
	const std::list<feature_list_item> &featurelist() const { return m_featurelist; }
	const std::vector<rom_entry> &romdata() const { return m_romdata; }

	// helpers
	bool matches_interface(const char *interface) const;
	const char *feature(const std::string &feature_name) const;

private:
	// internal state
	software_part *                 m_next;
	software_info &                 m_info;
	std::string                     m_name;
	std::string                     m_interface;
	std::list<feature_list_item>    m_featurelist;
	std::vector<rom_entry>          m_romdata;
>>>>>>> upstream/master
};


// ======================> software_info

// a single software item
class software_info
{
	friend class softlist_parser;
<<<<<<< HEAD
	friend class simple_list<software_info>;

public:
	// construction/destruction
	software_info(software_list_device &list, const char *name, const char *parent, const char *supported);

	// getters
	software_info *next() const { return m_next; }
	software_list_device &list() const { return m_list; }
	const char *shortname() const { return m_shortname; }
	const char *longname() const { return m_longname; }
	const char *parentname() const { return m_parentname; }
	const char *year() const { return m_year; }
	const char *publisher() const { return m_publisher; }
	feature_list_item *other_info() const { return m_other_info.first(); }
	feature_list_item *shared_info() const { return m_shared_info.first(); }
	UINT32 supported() const { return m_supported; }
	int num_parts() const { return m_partdata.count(); }
	software_part *first_part() const { return m_partdata.first(); }
	software_part *last_part() const { return m_partdata.last(); }

	// additional operations
	software_part *find_part(const char *partname, const char *interface = NULL);
=======

public:
	// construction/destruction
	software_info(std::string &&name, std::string &&parent, const std::string &supported);
	software_info(software_info const &) = delete;
	software_info(software_info &&) = delete;
	software_info& operator=(software_info const &) = delete;
	software_info& operator=(software_info &&) = delete;

	// getters
	const std::string &shortname() const { return m_shortname; }
	const std::string &longname() const { return m_longname; }
	const std::string &parentname() const { return m_parentname; }
	const std::string &year() const { return m_year; }
	const std::string &publisher() const { return m_publisher; }
	const std::list<feature_list_item> &other_info() const { return m_other_info; }
	const std::list<feature_list_item> &shared_info() const { return m_shared_info; }
	u32 supported() const { return m_supported; }
	const std::list<software_part> &parts() const { return m_partdata; }

	// additional operations
	const software_part *find_part(const std::string &part_name, const char *interface = nullptr) const;
>>>>>>> upstream/master
	bool has_multiple_parts(const char *interface) const;

private:
	// internal state
<<<<<<< HEAD
	software_info *         m_next;
	software_list_device &  m_list;
	UINT32                  m_supported;
	const char *            m_shortname;
	const char *            m_longname;
	const char *            m_parentname;
	const char *            m_year;           // Copyright year on title screen, actual release dates can be tracked in external resources
	const char *            m_publisher;
	simple_list<feature_list_item> m_other_info;   // Here we store info like developer, serial #, etc. which belong to the software entry as a whole
	simple_list<feature_list_item> m_shared_info;  // Here we store info like TV standard compatibility, or add-on requirements, etc. which get inherited
												// by each part of this software entry (after loading these are stored in partdata->featurelist)
	simple_list<software_part> m_partdata;
};


// ======================> software_list_device

// device representing a software list
class software_list_device : public device_t
{
	friend class softlist_parser;

public:
	// construction/destruction
	software_list_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// inline configuration helpers
	static void static_set_type(device_t &device, const char *list, softlist_type list_type);
	static void static_set_filter(device_t &device, const char *filter);

	// getters
	const char *list_name() const { return m_list_name.c_str(); }
	softlist_type list_type() const { return m_list_type; }
	const char *filter() const { return m_filter; }
	const char *filename() { return m_file.filename(); }

	// getters that may trigger a parse
	const char *description() { if (!m_parsed) parse(); return m_description; }
	bool valid() { if (!m_parsed) parse(); return m_infolist.count() > 0; }
	const char *errors_string() { if (!m_parsed) parse(); return m_errors.c_str(); }

	// operations
	software_info *find(const char *look_for, software_info *prev = NULL);
	software_info *first_software_info() { if (!m_parsed) parse(); return m_infolist.first(); }
	void find_approx_matches(const char *name, int matches, software_info **list, const char *interface);
	void release();

	// string pool helpers
	const char *add_string(const char *string) { return m_stringpool.add(string); }
	bool string_pool_contains(const char *string) { return m_stringpool.contains(string); }

	// static helpers
	static software_list_device *find_by_name(const machine_config &mconfig, const char *name);
	static void display_matches(const machine_config &config, const char *interface, const char *name);

protected:
	// internal helpers
	void parse();
	void internal_validity_check(validity_checker &valid) ATTR_COLD;

	// device-level overrides
	virtual void device_start();
	virtual void device_validity_check(validity_checker &valid) const ATTR_COLD;

	// configuration state
	std::string                 m_list_name;
	softlist_type               m_list_type;
	const char *                m_filter;

	// internal state
	bool                        m_parsed;
	emu_file                    m_file;
	const char *                m_description;
	std::string                 m_errors;
	simple_list<software_info>  m_infolist;
	const_string_pool           m_stringpool;
};


// device type definition
extern const device_type SOFTWARE_LIST;

// device type iterator
typedef device_type_iterator<&device_creator<software_list_device>, software_list_device> software_list_device_iterator;


#endif
=======
	u32                     m_supported;
	std::string             m_shortname;
	std::string             m_longname;
	std::string             m_parentname;
	std::string             m_year;           // Copyright year on title screen, actual release dates can be tracked in external resources
	std::string             m_publisher;
	std::list<feature_list_item> m_other_info;   // Here we store info like developer, serial #, etc. which belong to the software entry as a whole
	std::list<feature_list_item> m_shared_info;  // Here we store info like TV standard compatibility, or add-on requirements, etc. which get inherited
												// by each part of this software entry (after loading these are stored in partdata->featurelist)
	std::list<software_part> m_partdata;
};


// ======================> softlist_parser

class softlist_parser
{
public:
	// construction (== execution)
	softlist_parser(util::core_file &file, const std::string &filename, std::string &description, std::list<software_info> &infolist, std::ostringstream &errors);

private:
	enum parse_position
	{
		POS_ROOT,
		POS_MAIN,
		POS_SOFT,
		POS_PART,
		POS_DATA
	};

	// internal parsing helpers
	const char *infoname() const { return (m_current_info != nullptr) ? m_current_info->shortname().c_str() : "???"; }
	int line() const;
	int column() const;
	const char *parser_error() const;

	// internal error helpers
	template <typename Format, typename... Params> void parse_error(Format &&fmt, Params &&... args);
	void unknown_tag(const char *tagname) { parse_error("Unknown tag: %s", tagname); }
	void unknown_attribute(const char *attrname) { parse_error("Unknown attribute: %s", attrname); }

	// internal helpers
	template <typename T> std::vector<std::string> parse_attributes(const char **attributes, const T &attrlist);
	bool parse_name_and_value(const char **attributes, std::string &name, std::string &value);
	void add_rom_entry(std::string &&name, std::string &&hashdata, u32 offset, u32 length, u32 flags);

	// expat callbacks
	static void start_handler(void *data, const char *tagname, const char **attributes);
	static void data_handler(void *data, const char *s, int len);
	static void end_handler(void *data, const char *name);

	// internal parsing
	void parse_root_start(const char *tagname, const char **attributes);
	void parse_main_start(const char *tagname, const char **attributes);
	void parse_soft_start(const char *tagname, const char **attributes);
	void parse_part_start(const char *tagname, const char **attributes);
	void parse_data_start(const char *tagname, const char **attributes);
	void parse_soft_end(const char *name);

	// internal parsing state
	util::core_file &                   m_file;
	std::string                         m_filename;
	std::list<software_info> &  m_infolist;
	std::ostringstream &        m_errors;
	struct XML_ParserStruct *   m_parser;
	bool                        m_done;
	std::string &               m_description;
	bool                    m_data_accum_expected;
	std::string             m_data_accum;
	software_info *         m_current_info;
	software_part *         m_current_part;
	parse_position          m_pos;
};


// ----- Helpers -----

// parses a software identifier (e.g. - 'apple2e:agentusa:flop1') into its constituent parts (returns false if cannot parse)
bool software_name_parse(const std::string &identifier, std::string *list_name = nullptr, std::string *software_name = nullptr, std::string *part_name = nullptr);

#endif // MAME_EMU_SOFTLIST_H
>>>>>>> upstream/master
