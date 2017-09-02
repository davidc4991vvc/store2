// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    xmlfile.c

    XML file parsing code.

***************************************************************************/

#include <assert.h>

#include "xmlfile.h"
<<<<<<< HEAD
#include <ctype.h>
#include <expat.h>

=======

#include <expat.h>

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstring>


namespace util { namespace xml {
>>>>>>> upstream/master

/***************************************************************************
    CONSTANTS
***************************************************************************/

#define TEMP_BUFFER_SIZE        4096



/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

<<<<<<< HEAD
struct xml_parse_info
{
	XML_Parser          parser;
	xml_data_node *     rootnode;
	xml_data_node *     curnode;
	UINT32              flags;
=======
struct parse_info
{
	XML_Parser      parser;
	file::ptr       rootnode;
	data_node *     curnode;
	uint32_t        flags;
>>>>>>> upstream/master
};



/***************************************************************************
    PROTOTYPES
***************************************************************************/

/* expat interfaces */
<<<<<<< HEAD
static int expat_setup_parser(xml_parse_info *parse_info, xml_parse_options *opts);
=======
static bool expat_setup_parser(parse_info &info, parse_options const *opts);
>>>>>>> upstream/master
static void expat_element_start(void *data, const XML_Char *name, const XML_Char **attributes);
static void expat_data(void *data, const XML_Char *s, int len);
static void expat_element_end(void *data, const XML_Char *name);

<<<<<<< HEAD
/* node/attributes additions */
static xml_data_node *add_child(xml_data_node *parent, const char *name, const char *value);
static xml_attribute_node *add_attribute(xml_data_node *node, const char *name, const char *value);

/* recursive tree operations */
static void write_node_recursive(xml_data_node *node, int indent, core_file *file);
static void free_node_recursive(xml_data_node *node);



/***************************************************************************
    CORE IMPLEMENTATION
***************************************************************************/

/*-------------------------------------------------
    copystring - make an allocated copy of a
    string
-------------------------------------------------*/

static const char *copystring(const char *input)
{
	char *newstr;

	/* NULL just passes through */
	if (input == NULL)
		return NULL;

	/* make a lower-case copy if the allocation worked */
	newstr = (char *)malloc(strlen(input) + 1);
	if (newstr != NULL)
		strcpy(newstr, input);

	return newstr;
}


/*-------------------------------------------------
    copystring_lower - make an allocated copy of
    a string and convert it to lowercase along
    the way
-------------------------------------------------*/

static const char *copystring_lower(const char *input)
{
	char *newstr;
	int i;

	/* NULL just passes through */
	if (input == NULL)
		return NULL;

	/* make a lower-case copy if the allocation worked */
	newstr = (char *)malloc(strlen(input) + 1);
	if (newstr != NULL)
	{
		for (i = 0; input[i] != 0; i++)
			newstr[i] = tolower((UINT8)input[i]);
		newstr[i] = 0;
	}

	return newstr;
}



/***************************************************************************
    XML FILE OBJECTS
***************************************************************************/

/*-------------------------------------------------
    xml_file_create - create a new xml file
    object
-------------------------------------------------*/

xml_data_node *xml_file_create(void)
{
	xml_data_node *rootnode;

	/* create a root node */
	rootnode = (xml_data_node *)malloc(sizeof(*rootnode));
	if (rootnode == NULL)
		return NULL;
	memset(rootnode, 0, sizeof(*rootnode));
	return rootnode;
=======


/***************************************************************************
    XML FILE OBJECTS
***************************************************************************/

file::file() { }
file::~file() { }


/*-------------------------------------------------
    create - create a new, empty XML file
-------------------------------------------------*/

file::ptr file::create()
{
	try { return ptr(new file); }
	catch (...) { return ptr(); }
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_file_read - parse an XML file into its
    nodes
-------------------------------------------------*/

xml_data_node *xml_file_read(core_file *file, xml_parse_options *opts)
{
	xml_parse_info parse_info;
	int done;

	/* set up the parser */
	if (!expat_setup_parser(&parse_info, opts))
		return NULL;
=======
    read - parse an XML file into its nodes
-------------------------------------------------*/

file::ptr file::read(util::core_file &file, parse_options const *opts)
{
	parse_info info;
	int done;

	/* set up the parser */
	if (!expat_setup_parser(info, opts))
		return ptr();
>>>>>>> upstream/master

	/* loop through the file and parse it */
	do
	{
		char tempbuf[TEMP_BUFFER_SIZE];

		/* read as much as we can */
<<<<<<< HEAD
		int bytes = core_fread(file, tempbuf, sizeof(tempbuf));
		done = core_feof(file);

		/* parse the data */
		if (XML_Parse(parse_info.parser, tempbuf, bytes, done) == XML_STATUS_ERROR)
		{
			if (opts != NULL && opts->error != NULL)
			{
				opts->error->error_message = XML_ErrorString(XML_GetErrorCode(parse_info.parser));
				opts->error->error_line = XML_GetCurrentLineNumber(parse_info.parser);
				opts->error->error_column = XML_GetCurrentColumnNumber(parse_info.parser);
			}

			xml_file_free(parse_info.rootnode);
			XML_ParserFree(parse_info.parser);
			return NULL;
		}

	} while (!done);

	/* free the parser */
	XML_ParserFree(parse_info.parser);

	/* return the root node */
	return parse_info.rootnode;
=======
		int bytes = file.read(tempbuf, sizeof(tempbuf));
		done = file.eof();

		/* parse the data */
		if (XML_Parse(info.parser, tempbuf, bytes, done) == XML_STATUS_ERROR)
		{
			if (opts != nullptr && opts->error != nullptr)
			{
				opts->error->error_message = XML_ErrorString(XML_GetErrorCode(info.parser));
				opts->error->error_line = XML_GetCurrentLineNumber(info.parser);
				opts->error->error_column = XML_GetCurrentColumnNumber(info.parser);
			}

			info.rootnode.reset();
			XML_ParserFree(info.parser);
			return ptr();
		}
	}
	while (!done);

	/* free the parser */
	XML_ParserFree(info.parser);

	/* return the root node */
	return std::move(info.rootnode);
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_string_read - parse an XML string into its
    nodes
-------------------------------------------------*/

xml_data_node *xml_string_read(const char *string, xml_parse_options *opts)
{
	xml_parse_info parse_info;
	int length = (int)strlen(string);

	/* set up the parser */
	if (!expat_setup_parser(&parse_info, opts))
		return NULL;

	/* parse the data */
	if (XML_Parse(parse_info.parser, string, length, TRUE) == XML_STATUS_ERROR)
	{
		if (opts != NULL && opts->error != NULL)
		{
			opts->error->error_message = XML_ErrorString(XML_GetErrorCode(parse_info.parser));
			opts->error->error_line = XML_GetCurrentLineNumber(parse_info.parser);
			opts->error->error_column = XML_GetCurrentColumnNumber(parse_info.parser);
		}

		xml_file_free(parse_info.rootnode);
		XML_ParserFree(parse_info.parser);
		return NULL;
	}

	/* free the parser */
	XML_ParserFree(parse_info.parser);

	/* return the root node */
	return parse_info.rootnode;
=======
    string_read - parse an XML string into its
    nodes
-------------------------------------------------*/

file::ptr file::string_read(const char *string, parse_options const *opts)
{
	parse_info info;
	int length = (int)strlen(string);

	/* set up the parser */
	if (!expat_setup_parser(info, opts))
		return ptr();

	/* parse the data */
	if (XML_Parse(info.parser, string, length, 1) == XML_STATUS_ERROR)
	{
		if (opts != nullptr && opts->error != nullptr)
		{
			opts->error->error_message = XML_ErrorString(XML_GetErrorCode(info.parser));
			opts->error->error_line = XML_GetCurrentLineNumber(info.parser);
			opts->error->error_column = XML_GetCurrentColumnNumber(info.parser);
		}

		info.rootnode.reset();
		XML_ParserFree(info.parser);
		return ptr();
	}

	/* free the parser */
	XML_ParserFree(info.parser);

	/* return the root node */
	return std::move(info.rootnode);
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_file_write - write an XML tree to a file
-------------------------------------------------*/

void xml_file_write(xml_data_node *node, core_file *file)
{
	/* ensure this is a root node */
	if (node->name != NULL)
		return;

	/* output a simple header */
	core_fprintf(file, "<?xml version=\"1.0\"?>\n");
	core_fprintf(file, "<!-- This file is autogenerated; comments and unknown tags will be stripped -->\n");

	/* loop over children of the root and output */
	for (node = node->child; node; node = node->next)
		write_node_recursive(node, 0, file);
=======
    file_write - write an XML tree to a file
-------------------------------------------------*/

void file::write(util::core_file &file) const
{
	/* ensure this is a root node */
	assert(!get_name());

	/* output a simple header */
	file.printf("<?xml version=\"1.0\"?>\n");
	file.printf("<!-- This file is autogenerated; comments and unknown tags will be stripped -->\n");

	/* loop over children of the root and output */
	write_recursive(0, file);
}



/***************************************************************************
    XML NODE MANAGEMENT
***************************************************************************/

data_node::data_node()
	: line(0)
	, m_next(nullptr)
	, m_first_child(nullptr)
	, m_name()
	, m_value()
	, m_parent(nullptr)
	, m_attributes()
{
}

data_node::data_node(data_node *parent, const char *name, const char *value)
	: line(0)
	, m_next(nullptr)
	, m_first_child(nullptr)
	, m_name(name)
	, m_value(value ? value : "")
	, m_parent(parent)
	, m_attributes()
{
	std::transform(m_name.begin(), m_name.end(), m_name.begin(), [] (char ch) { return std::tolower(uint8_t(ch)); });
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_file_free - free an XML file object
-------------------------------------------------*/

void xml_file_free(xml_data_node *node)
{
	/* ensure this is a root node */
	if (node->name != NULL)
		return;

	free_node_recursive(node);
}



/***************************************************************************
    XML NODE MANAGEMENT
***************************************************************************/

/*-------------------------------------------------
    xml_count_children - count the number of
    child nodes
-------------------------------------------------*/

int xml_count_children(xml_data_node *node)
=======
    free_node_recursive - recursively free
    the data allocated to an XML node
-------------------------------------------------*/

data_node::~data_node()
{
	free_children();
}


void data_node::free_children()
{
	for (data_node *nchild = nullptr; m_first_child; m_first_child = nchild)
	{
		/* note the next node and free this node */
		nchild = m_first_child->get_next_sibling();
		delete m_first_child;
	}
}


void data_node::set_value(char const *value)
{
	m_value.assign(value ? value : "");
}


void data_node::append_value(char const *value, int length)
{
	m_value.append(value, length);
}


void data_node::trim_whitespace()
{
	/* first strip leading spaces */
	std::string::iterator start = m_value.begin();
	while ((m_value.end() != start) && std::isspace(uint8_t(*start)))
		++start;
	m_value.replace(m_value.begin(), start, 0U, '\0');

	/* then strip trailing spaces */
	std::string::iterator end = m_value.end();
	while ((m_value.begin() != end) && std::isspace(uint8_t(*std::prev(end))))
		--end;
	m_value.replace(end, m_value.end(), 0U, '\0');
}


/*-------------------------------------------------
    data_node::count_children - count the
    number of child nodes
-------------------------------------------------*/

int data_node::count_children() const
>>>>>>> upstream/master
{
	int count = 0;

	/* loop over children and count */
<<<<<<< HEAD
	for (node = node->child; node; node = node->next)
=======
	for (data_node const *node = get_first_child(); node; node = node->get_next_sibling())
>>>>>>> upstream/master
		count++;
	return count;
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_get_sibling - find the next sibling of
    the specified node with the specified tag
-------------------------------------------------*/

xml_data_node *xml_get_sibling(xml_data_node *node, const char *name)
{
	/* loop over siblings and find a matching name */
	for ( ; node; node = node->next)
		if (strcmp(node->name, name) == 0)
			return node;
	return NULL;
=======
    data_node::get_child - find the first
    child of the specified node with the specified
    tag
-------------------------------------------------*/

data_node *data_node::get_child(const char *name)
{
	return m_first_child ? m_first_child->get_sibling(name) : nullptr;
}

data_node const *data_node::get_child(const char *name) const
{
	return m_first_child ? m_first_child->get_sibling(name) : nullptr;
}


/*-------------------------------------------------
    find_first_matching_child - find the first
    child of the specified node with the
    specified tag or attribute/value pair
-------------------------------------------------*/

data_node *data_node::find_first_matching_child(const char *name, const char *attribute, const char *matchval)
{
	return m_first_child ? m_first_child->find_matching_sibling(name, attribute, matchval) : nullptr;
}

data_node const *data_node::find_first_matching_child(const char *name, const char *attribute, const char *matchval) const
{
	return m_first_child ? m_first_child->find_matching_sibling(name, attribute, matchval) : nullptr;
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_find_matching_sibling - find the next
=======
    data_node::get_next_sibling - find the
    next sibling of the specified node with the
    specified tag
-------------------------------------------------*/

data_node *data_node::get_next_sibling(const char *name)
{
	return m_next ? m_next->get_sibling(name) : nullptr;
}

data_node const *data_node::get_next_sibling(const char *name) const
{
	return m_next ? m_next->get_sibling(name) : nullptr;
}


/*-------------------------------------------------
    find_next_matching_sibling - find the next
>>>>>>> upstream/master
    sibling of the specified node with the
    specified tag or attribute/value pair
-------------------------------------------------*/

<<<<<<< HEAD
xml_data_node *xml_find_matching_sibling(xml_data_node *node, const char *name, const char *attribute, const char *matchval)
{
	/* loop over siblings and find a matching attribute */
	for ( ; node; node = node->next)
	{
		/* can pass NULL as a wildcard for the node name */
		if (name == NULL || strcmp(name, node->name) == 0)
		{
			/* find a matching attribute */
			xml_attribute_node *attr = xml_get_attribute(node, attribute);
			if (attr != NULL && strcmp(attr->value, matchval) == 0)
				return node;
		}
	}
	return NULL;
=======
data_node *data_node::find_next_matching_sibling(const char *name, const char *attribute, const char *matchval)
{
	return m_next ? m_next->find_matching_sibling(name, attribute, matchval) : nullptr;
}

data_node const *data_node::find_next_matching_sibling(const char *name, const char *attribute, const char *matchval) const
{
	return m_next ? m_next->find_matching_sibling(name, attribute, matchval) : nullptr;
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_add_child - add a new child node to the
    given node
-------------------------------------------------*/

xml_data_node *xml_add_child(xml_data_node *node, const char *name, const char *value)
{
	/* just a standard add child */
	return add_child(node, name, value);
=======
    add_child - add a new child node to the
    given node
-------------------------------------------------*/

data_node *data_node::add_child(const char *name, const char *value)
{
	if (!name || !*name)
		return nullptr;

	/* new element: create a new node */
	data_node *node;
	try { node = new data_node(this, name, value); }
	catch (...) { return nullptr; }

	if (!node->get_name() || (!node->get_value() && value))
	{
		delete node;
		return nullptr;
	}

	/* add us to the end of the list of siblings */
	data_node **pnode;
	for (pnode = &m_first_child; *pnode; pnode = &(*pnode)->m_next) { }
	*pnode = node;

	return node;
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_get_or_add_child - find a child node of
    the specified type; if not found, add one
-------------------------------------------------*/

xml_data_node *xml_get_or_add_child(xml_data_node *node, const char *name, const char *value)
{
	xml_data_node *child;

	/* find the child first */
	child = xml_get_sibling(node->child, name);
	if (child != NULL)
		return child;

	/* if not found, do a standard add child */
	return add_child(node, name, value);
=======
    get_or_add_child - find a child node of
    the specified type; if not found, add one
-------------------------------------------------*/

data_node *data_node::get_or_add_child(const char *name, const char *value)
{
	/* find the child first */
	data_node *const child = m_first_child->get_sibling(name);
	if (child)
		return child;

	/* if not found, do a standard add child */
	return add_child(name, value);
}


// recursively copy as child of another node
data_node *data_node::copy_into(data_node &parent) const
{
	data_node *const result = parent.add_child(get_name(), get_value());
	result->m_attributes = m_attributes;

	data_node *dst = result;
	data_node const *src = get_first_child();
	while (src && (&parent != dst))
	{
		dst = dst->add_child(src->get_name(), src->get_value());
		dst->m_attributes = src->m_attributes;
		data_node const *next = src->get_first_child();
		if (next)
		{
			src = next;
		}
		else
		{
			dst = dst->get_parent();
			next = src->get_next_sibling();
			if (next)
			{
				src = next;
			}
			else
			{
				dst = dst->get_parent();
				src = src->get_parent()->get_next_sibling();
			}
		}
	}

	return result;
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_delete_node - delete a node and its
    children
-------------------------------------------------*/

void xml_delete_node(xml_data_node *node)
{
	xml_data_node **pnode;

	/* first unhook us from the list of children of our parent */
	for (pnode = &node->parent->child; *pnode; pnode = &(*pnode)->next)
		if (*pnode == node)
		{
			*pnode = node->next;
			break;
		}

	/* now free ourselves and our children */
	free_node_recursive(node);
=======
    delete_node - delete a node and its
    children
-------------------------------------------------*/

void data_node::delete_node()
{
	/* don't allow deletion of document root */
	if (m_parent)
	{
		/* first unhook us from the list of children of our parent */
		for (data_node **pnode = &m_parent->m_first_child; *pnode; pnode = &(*pnode)->m_next)
		{
			if (*pnode == this)
			{
				*pnode = this->m_next;
				break;
			}
		}

		/* now free ourselves and our children */
		delete this;
	}
	else
	{
		/* remove all children of document root */
		free_children();
	}
}


/*-------------------------------------------------
    get_next_sibling - find the next sibling of
    the specified node with the specified tag
-------------------------------------------------*/

data_node *data_node::get_sibling(const char *name)
{
	/* loop over siblings and find a matching name */
	for (data_node *node = this; node; node = node->get_next_sibling())
		if (strcmp(node->get_name(), name) == 0)
			return node;
	return nullptr;
}

data_node const *data_node::get_sibling(const char *name) const
{
	/* loop over siblings and find a matching name */
	for (data_node const *node = this; node; node = node->get_next_sibling())
		if (strcmp(node->get_name(), name) == 0)
			return node;
	return nullptr;
}


/*-------------------------------------------------
    find_matching_sibling - find the next
    sibling of the specified node with the
    specified tag or attribute/value pair
-------------------------------------------------*/

data_node *data_node::find_matching_sibling(const char *name, const char *attribute, const char *matchval)
{
	/* loop over siblings and find a matching attribute */
	for (data_node *node = this; node; node = node->get_next_sibling())
	{
		/* can pass nullptr as a wildcard for the node name */
		if (!name || !strcmp(name, node->get_name()))
		{
			/* find a matching attribute */
			attribute_node const *const attr = node->get_attribute(attribute);
			if (attr && !strcmp(attr->value.c_str(), matchval))
				return node;
		}
	}
	return nullptr;
}

data_node const *data_node::find_matching_sibling(const char *name, const char *attribute, const char *matchval) const
{
	/* loop over siblings and find a matching attribute */
	for (data_node const *node = this; node; node = node->get_next_sibling())
	{
		/* can pass nullptr as a wildcard for the node name */
		if (!name || !strcmp(name, node->get_name()))
		{
			/* find a matching attribute */
			attribute_node const *const attr = node->get_attribute(attribute);
			if (attr && !strcmp(attr->value.c_str(), matchval))
				return node;
		}
	}
	return nullptr;
>>>>>>> upstream/master
}



/***************************************************************************
    XML ATTRIBUTE MANAGEMENT
***************************************************************************/

<<<<<<< HEAD
/*-------------------------------------------------
    xml_get_attribute - get the value of the
    specified attribute, or NULL if not found
-------------------------------------------------*/

xml_attribute_node *xml_get_attribute(xml_data_node *node, const char *attribute)
{
	xml_attribute_node *anode;

	/* loop over attributes and find a match */
	for (anode = node->attribute; anode; anode = anode->next)
		if (strcmp(anode->name, attribute) == 0)
			return anode;
	return NULL;
=======
bool data_node::has_attribute(const char *attribute) const
{
	return get_attribute(attribute) != nullptr;
}


/*-------------------------------------------------
    get_attribute - get the value of the
    specified attribute, or nullptr if not found
-------------------------------------------------*/

data_node::attribute_node *data_node::get_attribute(const char *attribute)
{
	/* loop over attributes and find a match */
	for (attribute_node &anode : m_attributes)
		if (strcmp(anode.name.c_str(), attribute) == 0)
			return &anode;
	return nullptr;
}

data_node::attribute_node const *data_node::get_attribute(const char *attribute) const
{
	/* loop over attributes and find a match */
	for (attribute_node const &anode : m_attributes)
		if (strcmp(anode.name.c_str(), attribute) == 0)
			return &anode;
	return nullptr;
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_get_attribute_string - get the string
=======
    get_attribute_string - get the string
>>>>>>> upstream/master
    value of the specified attribute; if not
    found, return = the provided default
-------------------------------------------------*/

<<<<<<< HEAD
const char *xml_get_attribute_string(xml_data_node *node, const char *attribute, const char *defvalue)
{
	xml_attribute_node *attr = xml_get_attribute(node, attribute);
	return attr ? attr->value : defvalue;
=======
const char *data_node::get_attribute_string(const char *attribute, const char *defvalue) const
{
	attribute_node const *attr = get_attribute(attribute);
	return attr ? attr->value.c_str() : defvalue;
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_get_attribute_int - get the integer
=======
    get_attribute_int - get the integer
>>>>>>> upstream/master
    value of the specified attribute; if not
    found, return = the provided default
-------------------------------------------------*/

<<<<<<< HEAD
int xml_get_attribute_int(xml_data_node *node, const char *attribute, int defvalue)
{
	const char *string = xml_get_attribute_string(node, attribute, NULL);
	int value;
	unsigned int uvalue;

	if (string == NULL)
=======
int data_node::get_attribute_int(const char *attribute, int defvalue) const
{
	char const *const string = get_attribute_string(attribute, nullptr);
	int value;
	unsigned int uvalue;

	if (string == nullptr)
>>>>>>> upstream/master
		return defvalue;
	if (string[0] == '$')
		return (sscanf(&string[1], "%X", &uvalue) == 1) ? uvalue : defvalue;
	if (string[0] == '0' && string[1] == 'x')
		return (sscanf(&string[2], "%X", &uvalue) == 1) ? uvalue : defvalue;
	if (string[0] == '#')
		return (sscanf(&string[1], "%d", &value) == 1) ? value : defvalue;
	return (sscanf(&string[0], "%d", &value) == 1) ? value : defvalue;
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_get_attribute_int_format - return the
    format of the given integer attribute
-------------------------------------------------*/

int xml_get_attribute_int_format(xml_data_node *node, const char *attribute)
{
	const char *string = xml_get_attribute_string(node, attribute, NULL);

	if (string == NULL)
		return XML_INT_FORMAT_DECIMAL;
	if (string[0] == '$')
		return XML_INT_FORMAT_HEX_DOLLAR;
	if (string[0] == '0' && string[1] == 'x')
		return XML_INT_FORMAT_HEX_C;
	if (string[0] == '#')
		return XML_INT_FORMAT_DECIMAL_POUND;
	return XML_INT_FORMAT_DECIMAL;
=======
    get_attribute_int_format - return the
    format of the given integer attribute
-------------------------------------------------*/

data_node::int_format data_node::get_attribute_int_format(const char *attribute) const
{
	char const *const string = get_attribute_string(attribute, nullptr);

	if (!string)
		return int_format::DECIMAL;
	else if (string[0] == '$')
		return int_format::HEX_DOLLAR;
	else if (string[0] == '0' && string[1] == 'x')
		return int_format::HEX_C;
	if (string[0] == '#')
		return int_format::DECIMAL_HASH;
	else
		return int_format::DECIMAL;
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_get_attribute_float - get the float
=======
    get_attribute_float - get the float
>>>>>>> upstream/master
    value of the specified attribute; if not
    found, return = the provided default
-------------------------------------------------*/

<<<<<<< HEAD
float xml_get_attribute_float(xml_data_node *node, const char *attribute, float defvalue)
{
	const char *string = xml_get_attribute_string(node, attribute, NULL);
	float value;

	if (string == NULL || sscanf(string, "%f", &value) != 1)
=======
float data_node::get_attribute_float(const char *attribute, float defvalue) const
{
	char const *const string = get_attribute_string(attribute, nullptr);
	float value;

	if (string == nullptr || sscanf(string, "%f", &value) != 1)
>>>>>>> upstream/master
		return defvalue;
	return value;
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_set_attribute - set a new attribute and
    string value on the node
-------------------------------------------------*/

xml_attribute_node *xml_set_attribute(xml_data_node *node, const char *name, const char *value)
{
	xml_attribute_node *anode;

	/* first find an existing one to replace */
	anode = xml_get_attribute(node, name);

	/* if we found it, free the old value and replace it */
	if (anode != NULL)
	{
		if (anode->value != NULL)
			free((void *)anode->value);
		anode->value = copystring(value);
	}

	/* otherwise, create a new node */
	else
		anode = add_attribute(node, name, value);

	return anode;
=======
    set_attribute - set a new attribute and
    string value on the node
-------------------------------------------------*/

void data_node::set_attribute(const char *name, const char *value)
{
	attribute_node *anode;

	/* first find an existing one to replace */
	anode = get_attribute(name);

	if (anode != nullptr)
	{
		/* if we found it, free the old value and replace it */
		anode->value = value;
	}
	else
	{
		/* otherwise, create a new node */
		add_attribute(name, value);
	}
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_set_attribute_int - set a new attribute and
    integer value on the node
-------------------------------------------------*/

xml_attribute_node *xml_set_attribute_int(xml_data_node *node, const char *name, int value)
{
	char buffer[100];
	sprintf(buffer, "%d", value);
	return xml_set_attribute(node, name, buffer);
=======
    set_attribute_int - set a new attribute and
    integer value on the node
-------------------------------------------------*/

void data_node::set_attribute_int(const char *name, int value)
{
	char buffer[100];
	sprintf(buffer, "%d", value);
	set_attribute(name, buffer);
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    xml_set_attribute_int - set a new attribute and
    float value on the node
-------------------------------------------------*/

xml_attribute_node *xml_set_attribute_float(xml_data_node *node, const char *name, float value)
{
	char buffer[100];
	sprintf(buffer, "%f", (double) value);
	return xml_set_attribute(node, name, buffer);
=======
    set_attribute_int - set a new attribute and
    float value on the node
-------------------------------------------------*/

void data_node::set_attribute_float(const char *name, float value)
{
	char buffer[100];
	sprintf(buffer, "%f", (double) value);
	set_attribute(name, buffer);
>>>>>>> upstream/master
}



/***************************************************************************
    MISCELLANEOUS INTERFACES
***************************************************************************/

/*-------------------------------------------------
<<<<<<< HEAD
    xml_normalize_string - normalize a string
    to ensure it doesn't contain embedded tags
-------------------------------------------------*/

const char *xml_normalize_string(const char *string)
=======
    normalize_string - normalize a string
    to ensure it doesn't contain embedded tags
-------------------------------------------------*/

const char *normalize_string(const char *string)
>>>>>>> upstream/master
{
	static char buffer[1024];
	char *d = &buffer[0];

<<<<<<< HEAD
	if (string != NULL)
=======
	if (string != nullptr)
>>>>>>> upstream/master
	{
		while (*string)
		{
			switch (*string)
			{
				case '\"' : d += sprintf(d, "&quot;"); break;
				case '&'  : d += sprintf(d, "&amp;"); break;
				case '<'  : d += sprintf(d, "&lt;"); break;
				case '>'  : d += sprintf(d, "&gt;"); break;
				default:
					*d++ = *string;
			}
			++string;
		}
	}
	*d++ = 0;
	return buffer;
}



/***************************************************************************
    EXPAT INTERFACES
***************************************************************************/

/*-------------------------------------------------
    expat_malloc/expat_realloc/expat_free -
    wrappers for memory allocation functions so
    that they pass through out memory tracking
    systems
-------------------------------------------------*/

static void *expat_malloc(size_t size)
{
<<<<<<< HEAD
	UINT32 *result = (UINT32 *)malloc(size + 4 * sizeof(UINT32));
=======
	uint32_t *result = (uint32_t *)malloc(size + 4 * sizeof(uint32_t));
>>>>>>> upstream/master
	*result = size;
	return &result[4];
}

static void expat_free(void *ptr)
{
<<<<<<< HEAD
	if (ptr != NULL)
		free(&((UINT32 *)ptr)[-4]);
=======
	if (ptr != nullptr)
		free(&((uint32_t *)ptr)[-4]);
>>>>>>> upstream/master
}

static void *expat_realloc(void *ptr, size_t size)
{
	void *newptr = expat_malloc(size);
<<<<<<< HEAD
	if (newptr == NULL)
		return NULL;
	if (ptr != NULL)
	{
		UINT32 oldsize = ((UINT32 *)ptr)[-4];
=======
	if (newptr == nullptr)
		return nullptr;
	if (ptr != nullptr)
	{
		uint32_t oldsize = ((uint32_t *)ptr)[-4];
>>>>>>> upstream/master
		memcpy(newptr, ptr, oldsize);
		expat_free(ptr);
	}
	return newptr;
}


/*-------------------------------------------------
    expat_setup_parser - set up expat for parsing
-------------------------------------------------*/

<<<<<<< HEAD
static int expat_setup_parser(xml_parse_info *parse_info, xml_parse_options *opts)
{
	XML_Memory_Handling_Suite memcallbacks;

	/* setup parse_info structure */
	memset(parse_info, 0, sizeof(*parse_info));
	if (opts != NULL)
	{
		parse_info->flags = opts->flags;
		if (opts->error != NULL)
		{
			opts->error->error_message = NULL;
=======
static bool expat_setup_parser(parse_info &info, parse_options const *opts)
{
	XML_Memory_Handling_Suite memcallbacks;

	/* setup info structure */
	memset(&info, 0, sizeof(info));
	if (opts != nullptr)
	{
		info.flags = opts->flags;
		if (opts->error != nullptr)
		{
			opts->error->error_message = nullptr;
>>>>>>> upstream/master
			opts->error->error_line = 0;
			opts->error->error_column = 0;
		}
	}

	/* create a root node */
<<<<<<< HEAD
	parse_info->rootnode = xml_file_create();
	if (parse_info->rootnode == NULL)
		return FALSE;
	parse_info->curnode = parse_info->rootnode;
=======
	info.rootnode = file::create();
	if (!info.rootnode)
		return false;
	info.curnode = info.rootnode.get();
>>>>>>> upstream/master

	/* create the XML parser */
	memcallbacks.malloc_fcn = expat_malloc;
	memcallbacks.realloc_fcn = expat_realloc;
	memcallbacks.free_fcn = expat_free;
<<<<<<< HEAD
	parse_info->parser = XML_ParserCreate_MM(NULL, &memcallbacks, NULL);
	if (parse_info->parser == NULL)
	{
		free(parse_info->rootnode);
		return FALSE;
	}

	/* configure the parser */
	XML_SetElementHandler(parse_info->parser, expat_element_start, expat_element_end);
	XML_SetCharacterDataHandler(parse_info->parser, expat_data);
	XML_SetUserData(parse_info->parser, parse_info);

	/* optional parser initialization step */
	if (opts != NULL && opts->init_parser != NULL)
		(*opts->init_parser)(parse_info->parser);
	return TRUE;
=======
	info.parser = XML_ParserCreate_MM(nullptr, &memcallbacks, nullptr);
	if (info.parser == nullptr)
	{
		info.rootnode.reset();
		return false;
	}

	/* configure the parser */
	XML_SetElementHandler(info.parser, expat_element_start, expat_element_end);
	XML_SetCharacterDataHandler(info.parser, expat_data);
	XML_SetUserData(info.parser, &info);

	/* optional parser initialization step */
	if (opts != nullptr && opts->init_parser != nullptr)
		(*opts->init_parser)(info.parser);
	return true;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    expat_element_start - expat callback for a new
    element
-------------------------------------------------*/

static void expat_element_start(void *data, const XML_Char *name, const XML_Char **attributes)
{
<<<<<<< HEAD
	xml_parse_info *parse_info = (xml_parse_info *) data;
	xml_data_node **curnode = &parse_info->curnode;
	xml_data_node *newnode;
	int attr;

	/* add a new child node to the current node */
	newnode = add_child(*curnode, name, NULL);
	if (newnode == NULL)
		return;

	/* remember the line number */
	newnode->line = XML_GetCurrentLineNumber(parse_info->parser);

	/* add all the attributes as well */
	for (attr = 0; attributes[attr]; attr += 2)
		add_attribute(newnode, attributes[attr+0], attributes[attr+1]);
=======
	parse_info *info = (parse_info *) data;
	data_node **curnode = &info->curnode;
	data_node *newnode;
	int attr;

	/* add a new child node to the current node */
	newnode = (*curnode)->add_child(name, nullptr);
	if (newnode == nullptr)
		return;

	/* remember the line number */
	newnode->line = XML_GetCurrentLineNumber(info->parser);

	/* add all the attributes as well */
	for (attr = 0; attributes[attr]; attr += 2)
		newnode->add_attribute(attributes[attr+0], attributes[attr+1]);
>>>>>>> upstream/master

	/* set us up as the current node */
	*curnode = newnode;
}


/*-------------------------------------------------
    expat_data - expat callback for an additional
    element data
-------------------------------------------------*/

static void expat_data(void *data, const XML_Char *s, int len)
{
<<<<<<< HEAD
	xml_parse_info *parse_info = (xml_parse_info *) data;
	xml_data_node **curnode = &parse_info->curnode;
	int oldlen = 0;
	char *newdata;

	/* if no data, skip */
	if (len == 0)
		return;

	/* determine how much data we currently have */
	if ((*curnode)->value != NULL)
		oldlen = (int)strlen((*curnode)->value);

	/* realloc */
	newdata = (char *)malloc(oldlen + len + 1);
	if (newdata == NULL)
		return;
	if ((*curnode)->value != NULL)
	{
		memcpy(newdata, (*curnode)->value, oldlen);
		free((void *)(*curnode)->value);
	}
	(*curnode)->value = newdata;

	/* copy in the new data a NULL-terminate */
	memcpy(&newdata[oldlen], s, len);
	newdata[oldlen + len] = 0;
	(*curnode)->value = newdata;
=======
	parse_info *info = (parse_info *) data;
	data_node **curnode = &info->curnode;
	(*curnode)->append_value(s, len);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    expat_element_end - expat callback for the end
    of an element
-------------------------------------------------*/

static void expat_element_end(void *data, const XML_Char *name)
{
<<<<<<< HEAD
	xml_parse_info *parse_info = (xml_parse_info *) data;
	xml_data_node **curnode = &parse_info->curnode;
	char *orig;

	/* strip leading/trailing spaces from the value data */
	orig = (char *)(*curnode)->value;
	if (orig != NULL && !(parse_info->flags & XML_PARSE_FLAG_WHITESPACE_SIGNIFICANT))
	{
		char *start = orig;
		char *end = start + strlen(start);

		/* first strip leading spaces */
		while (*start && isspace((UINT8)*start))
			start++;

		/* then strip trailing spaces */
		while (end > start && isspace((UINT8)end[-1]))
			end--;

		/* if nothing left, just free it */
		if (start == end)
		{
			free(orig);
			(*curnode)->value = NULL;
		}

		/* otherwise, memmove the data */
		else
		{
			memmove(orig, start, end - start);
			orig[end - start] = 0;
		}
	}

	/* back us up a node */
	*curnode = (*curnode)->parent;
=======
	parse_info *info = (parse_info *) data;
	data_node **curnode = &info->curnode;

	/* strip leading/trailing spaces from the value data */
	if (!(info->flags & PARSE_FLAG_WHITESPACE_SIGNIFICANT))
		(*curnode)->trim_whitespace();

	/* back us up a node */
	*curnode = (*curnode)->get_parent();
>>>>>>> upstream/master
}



/***************************************************************************
    NODE/ATTRIBUTE ADDITIONS
***************************************************************************/

/*-------------------------------------------------
<<<<<<< HEAD
    add_child - add a new node to the parent
-------------------------------------------------*/

static xml_data_node *add_child(xml_data_node *parent, const char *name, const char *value)
{
	xml_data_node **pnode;
	xml_data_node *node;

	/* new element: create a new node */
	node = (xml_data_node *)malloc(sizeof(*node));
	if (node == NULL)
		return NULL;

	/* initialize the members */
	node->next = NULL;
	node->parent = parent;
	node->child = NULL;
	node->name = copystring_lower(name);
	if (node->name == NULL)
	{
		free(node);
		return NULL;
	}
	node->value = copystring(value);
	if (node->value == NULL && value != NULL)
	{
		free((void *)node->name);
		free(node);
		return NULL;
	}
	node->attribute = NULL;

	/* add us to the end of the list of siblings */
	for (pnode = &parent->child; *pnode; pnode = &(*pnode)->next) ;
	*pnode = node;

	return node;
}


/*-------------------------------------------------
=======
>>>>>>> upstream/master
    add_attribute - add a new attribute to the
    given node
-------------------------------------------------*/

<<<<<<< HEAD
static xml_attribute_node *add_attribute(xml_data_node *node, const char *name, const char *value)
{
	xml_attribute_node *anode, **panode;

	/* allocate a new attribute node */
	anode = (xml_attribute_node *)malloc(sizeof(*anode));
	if (anode == NULL)
		return NULL;

	/* fill it in */
	anode->next = NULL;
	anode->name = copystring_lower(name);
	if (anode->name == NULL)
	{
		free(anode);
		return NULL;
	}
	anode->value = copystring(value);
	if (anode->value == NULL)
	{
		free((void *)anode->name);
		free(anode);
		return NULL;
	}

	/* add us to the end of the list of attributes */
	for (panode = &node->attribute; *panode; panode = &(*panode)->next) ;
	*panode = anode;

	return anode;
=======
void data_node::add_attribute(const char *name, const char *value)
{
	try
	{
		attribute_node &anode = *m_attributes.emplace(m_attributes.end(), name, value);
		std::transform(anode.name.begin(), anode.name.end(), anode.name.begin(), [] (char ch) { return std::tolower(uint8_t(ch)); });
	}
	catch (...)
	{
	}
>>>>>>> upstream/master
}



/***************************************************************************
    RECURSIVE TREE OPERATIONS
***************************************************************************/

/*-------------------------------------------------
    write_node_recursive - recursively write
    an XML node and its children to a file
-------------------------------------------------*/

<<<<<<< HEAD
static void write_node_recursive(xml_data_node *node, int indent, core_file *file)
{
	xml_attribute_node *anode;
	xml_data_node *child;

	/* output this tag */
	core_fprintf(file, "%*s<%s", indent, "", node->name);

	/* output any attributes */
	for (anode = node->attribute; anode; anode = anode->next)
		core_fprintf(file, " %s=\"%s\"", anode->name, anode->value);

	/* if there are no children and no value, end the tag here */
	if (node->child == NULL && node->value == NULL)
		core_fprintf(file, " />\n");

	/* otherwise, close this tag and output more stuff */
	else
	{
		core_fprintf(file, ">\n");

		/* if there is a value, output that here */
		if (node->value != NULL)
			core_fprintf(file, "%*s%s\n", indent + 4, "", node->value);

		/* loop over children and output them as well */
		if (node->child != NULL)
		{
			for (child = node->child; child; child = child->next)
				write_node_recursive(child, indent + 4, file);
		}

		/* write a closing tag */
		core_fprintf(file, "%*s</%s>\n", indent, "", node->name);
	}
}


/*-------------------------------------------------
    free_node_recursive - recursively free
    the data allocated to an XML node
-------------------------------------------------*/

static void free_node_recursive(xml_data_node *node)
{
	xml_attribute_node *anode, *nanode;
	xml_data_node *child, *nchild;

	/* free name/value */
	if (node->name != NULL)
		free((void *)node->name);
	if (node->value != NULL)
		free((void *)node->value);

	/* free attributes */
	for (anode = node->attribute; anode; anode = nanode)
	{
		/* free name/value */
		if (anode->name != NULL)
			free((void *)anode->name);
		if (anode->value != NULL)
			free((void *)anode->value);

		/* note the next node and free this node */
		nanode = anode->next;
		free(anode);
	}

	/* free the children */
	for (child = node->child; child; child = nchild)
	{
		/* note the next node and free this node */
		nchild = child->next;
		free_node_recursive(child);
	}

	/* finally free ourself */
	free(node);
}
=======
void data_node::write_recursive(int indent, util::core_file &file) const
{
	if (!get_name())
	{
		/* root node doesn't generate tag */
		for (data_node const *child = this->get_first_child(); child; child = child->get_next_sibling())
			child->write_recursive(indent, file);
	}
	else
	{
		/* output this tag */
		file.printf("%*s<%s", indent, "", get_name());

		/* output any attributes */
		for (attribute_node const &anode : m_attributes)
			file.printf(" %s=\"%s\"", anode.name, anode.value);

		if (!get_first_child() && !get_value())
		{
			/* if there are no children and no value, end the tag here */
			file.printf(" />\n");
		}
		else
		{
			/* otherwise, close this tag and output more stuff */
			file.printf(">\n");

			/* if there is a value, output that here */
			if (get_value())
				file.printf("%*s%s\n", indent + 4, "", get_value());

			/* loop over children and output them as well */
			if (get_first_child())
			{
				for (data_node const *child = this->get_first_child(); child; child = child->get_next_sibling())
					child->write_recursive(indent + 4, file);
			}

			/* write a closing tag */
			file.printf("%*s</%s>\n", indent, "", get_name());
		}
	}
}


} } // namespace util::xml
>>>>>>> upstream/master
