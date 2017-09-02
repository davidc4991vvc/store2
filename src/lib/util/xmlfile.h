// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    xmlfile.h

    XML file parsing code.

***************************************************************************/

#pragma once

<<<<<<< HEAD
#ifndef __XMLFILE_H__
#define __XMLFILE_H__
=======
#ifndef MAME_LIB_UTIL_XMLFILE_H
#define MAME_LIB_UTIL_XMLFILE_H
>>>>>>> upstream/master

#include "osdcore.h"
#include "corefile.h"

<<<<<<< HEAD
=======
#include <list>
#include <string>
#include <utility>


// forward type declarations
struct XML_ParserStruct;


namespace util { namespace xml {
>>>>>>> upstream/master

/***************************************************************************
    CONSTANTS
***************************************************************************/

enum
{
<<<<<<< HEAD
	XML_PARSE_FLAG_WHITESPACE_SIGNIFICANT = 1
};


enum
{
	XML_INT_FORMAT_DECIMAL,
	XML_INT_FORMAT_DECIMAL_POUND,
	XML_INT_FORMAT_HEX_DOLLAR,
	XML_INT_FORMAT_HEX_C
=======
	PARSE_FLAG_WHITESPACE_SIGNIFICANT = 1
>>>>>>> upstream/master
};



/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

<<<<<<< HEAD
/* forward type declarations */
struct XML_ParserStruct;


/* a node representing an attribute */
struct xml_attribute_node
{
	xml_attribute_node *    next;           /* pointer to next attribute node */
	const char *            name;           /* pointer to copy of tag name */
	const char *            value;          /* pointer to copy of value string */
};


/* a node representing a data item and its relationships */
struct xml_data_node
{
	xml_data_node *         next;           /* pointer to next sibling node */
	xml_data_node *         parent;         /* pointer to parent node */
	xml_data_node *         child;          /* pointer to first child node */
	const char *            name;           /* pointer to copy of tag name */
	const char *            value;          /* pointer to copy of value string */
	xml_attribute_node *    attribute;      /* pointer to array of attribute nodes */
	int                     line;           /* line number for this node's start */
};


/* extended error information from parsing */
struct xml_parse_error
{
	const char *            error_message;
	int                     error_line;
	int                     error_column;
};


/* parsing options */
struct xml_parse_options
{
	xml_parse_error *       error;
	void                    (*init_parser)(struct XML_ParserStruct *parser);
	UINT32                  flags;
};



/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/


/* ----- XML file objects ----- */

/* create a new empty xml file object */
xml_data_node *xml_file_create(void);

/* parse an XML file into its nodes */
xml_data_node *xml_file_read(core_file *file, xml_parse_options *opts);

/* parse an XML string into its nodes */
xml_data_node *xml_string_read(const char *string, xml_parse_options *opts);

/* write an XML tree to a file */
void xml_file_write(xml_data_node *node, core_file *file);

/* free an XML file object */
void xml_file_free(xml_data_node *node);



/* ----- XML node management ----- */

/* count the number of child nodes */
int xml_count_children(xml_data_node *node);

/* find the next sibling with the given tag */
xml_data_node *xml_get_sibling(xml_data_node *node, const char *name);

/* find the next sibling with the given tag and/or attribute/value pair */
xml_data_node *xml_find_matching_sibling(xml_data_node *node, const char *name, const char *attribute, const char *matchval);

/* add a new child node */
xml_data_node *xml_add_child(xml_data_node *node, const char *name, const char *value);

/* either return an existing child node or create one if it doesn't exist */
xml_data_node *xml_get_or_add_child(xml_data_node *node, const char *name, const char *value);

/* delete a node and its children */
void xml_delete_node(xml_data_node *node);



/* ----- XML attribute management ----- */

/* find an attribute node with the specified tag */
xml_attribute_node *xml_get_attribute(xml_data_node *node, const char *attribute);

/* return the string value of an attribute, or the specified default if not present */
const char *xml_get_attribute_string(xml_data_node *node, const char *attribute, const char *defvalue);

/* return the integer value of an attribute, or the specified default if not present */
int xml_get_attribute_int(xml_data_node *node, const char *attribute, int defvalue);

/* return the format of the given integer attribute */
int xml_get_attribute_int_format(xml_data_node *node, const char *attribute);

/* return the float value of an attribute, or the specified default if not present */
float xml_get_attribute_float(xml_data_node *node, const char *attribute, float defvalue);

/* set the string value of an attribute */
xml_attribute_node *xml_set_attribute(xml_data_node *node, const char *name, const char *value);

/* set the integer value of an attribute */
xml_attribute_node *xml_set_attribute_int(xml_data_node *node, const char *name, int value);

/* set the float value of an attribute */
xml_attribute_node *xml_set_attribute_float(xml_data_node *node, const char *name, float value);


=======
/* extended error information from parsing */
struct parse_error
{
	const char *            error_message;
	int                     error_line;
	int                     error_column;
};


// parsing options
struct parse_options
{
	parse_error *       error;
	void                (*init_parser)(XML_ParserStruct *parser);
	uint32_t            flags;
};


// a node representing a data item and its relationships
class data_node
{
public:
	enum class int_format
	{
		DECIMAL,
		DECIMAL_HASH,
		HEX_DOLLAR,
		HEX_C
	};


	/* ----- XML node management ----- */

	char const *get_name() const { return m_name.empty() ? nullptr : m_name.c_str(); }

	char const *get_value() const { return m_value.empty() ? nullptr : m_value.c_str(); }
	void set_value(char const *value);
	void append_value(char const *value, int length);
	void trim_whitespace();

	data_node *get_parent() { return m_parent; }
	data_node const *get_parent() const { return m_parent; }

	// count the number of child nodes
	int count_children() const;

	// get the first child
	data_node *get_first_child() { return m_first_child; }
	data_node const *get_first_child() const { return m_first_child; }

	// find the first child with the given tag
	data_node *get_child(const char *name);
	data_node const *get_child(const char *name) const;

	// find the first child with the given tag and/or attribute/value pair
	data_node *find_first_matching_child(const char *name, const char *attribute, const char *matchval);
	data_node const *find_first_matching_child(const char *name, const char *attribute, const char *matchval) const;

	// get the next sibling
	data_node *get_next_sibling() { return m_next; }
	data_node const *get_next_sibling() const { return m_next; }

	// find the next sibling with the given tag
	data_node *get_next_sibling(const char *name);
	data_node const *get_next_sibling(const char *name) const;

	// find the next sibling with the given tag and/or attribute/value pair
	data_node *find_next_matching_sibling(const char *name, const char *attribute, const char *matchval);
	data_node const *find_next_matching_sibling(const char *name, const char *attribute, const char *matchval) const;

	// add a new child node
	data_node *add_child(const char *name, const char *value);

	// either return an existing child node or create one if it doesn't exist
	data_node *get_or_add_child(const char *name, const char *value);

	// recursively copy as child of another node
	data_node *copy_into(data_node &parent) const;

	// delete a node and its children
	void delete_node();


	/* ----- XML attribute management ----- */

	// return whether a node has the specified attribute
	bool has_attribute(const char *attribute) const;

	// return the string value of an attribute, or the specified default if not present
	const char *get_attribute_string(const char *attribute, const char *defvalue) const;

	// return the integer value of an attribute, or the specified default if not present
	int get_attribute_int(const char *attribute, int defvalue) const;

	// return the format of the given integer attribute
	int_format get_attribute_int_format(const char *attribute) const;

	// return the float value of an attribute, or the specified default if not present
	float get_attribute_float(const char *attribute, float defvalue) const;

	// set the string value of an attribute
	void set_attribute(const char *name, const char *value);

	// set the integer value of an attribute
	void set_attribute_int(const char *name, int value);

	// set the float value of an attribute
	void set_attribute_float(const char *name, float value);

	// add an attribute even if an attribute with the same name already exists
	void add_attribute(const char *name, const char *value);



	int                     line;           /* line number for this node's start */


protected:
	data_node();
	~data_node();

	void write_recursive(int indent, util::core_file &file) const;


private:
	// a node representing an attribute
	struct attribute_node
	{
		template <typename T, typename U> attribute_node(T &&name, U &&value) : name(std::forward<T>(name)), value(std::forward<U>(value)) { }

		std::string name;
		std::string value;
	};


	data_node(data_node *parent, const char *name, const char *value);

	data_node(data_node const &) = delete;
	data_node(data_node &&) = delete;
	data_node &operator=(data_node &&) = delete;
	data_node &operator=(data_node const &) = delete;

	data_node *get_sibling(const char *name);
	data_node const *get_sibling(const char *name) const;
	data_node *find_matching_sibling(const char *name, const char *attribute, const char *matchval);
	data_node const *find_matching_sibling(const char *name, const char *attribute, const char *matchval) const;

	attribute_node *get_attribute(const char *attribute);
	attribute_node const *get_attribute(const char *attribute) const;

	void free_children();


	data_node *                 m_next;
	data_node *                 m_first_child;
	std::string                 m_name;
	std::string                 m_value;
	data_node *                 m_parent;
	std::list<attribute_node>   m_attributes;
};


// a node representing the root of a document
class file : public data_node
{
public:
	using ptr = std::unique_ptr<file>;


	~file();

	// create a new, empty XML file
	static ptr create();

	// parse an XML file into its nodes
	static ptr read(util::core_file &file, parse_options const *opts);

	// parse an XML string into its nodes
	static ptr string_read(const char *string, parse_options const *opts);

	// write an XML tree to a file
	void write(util::core_file &file) const;


private:
	file();
};



/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/
>>>>>>> upstream/master

/* ----- miscellaneous interfaces ----- */

/* normalize a string into something that can be written to an XML file */
<<<<<<< HEAD
const char *xml_normalize_string(const char *string);

#endif  /* __XMLFILE_H__ */
=======
const char *normalize_string(const char *string);

} } // namespace util::xml

#endif  /* MAME_LIB_UTIL_XMLFILE_H */
>>>>>>> upstream/master
