// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria, Aaron Giles
/***************************************************************************

    config.c

    Configuration file I/O.
***************************************************************************/

#include "emu.h"
#include "emuopts.h"
#include "drivenum.h"
#include "config.h"
#include "xmlfile.h"

<<<<<<< HEAD

#define DEBUG_CONFIG        0



/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

struct config_type
{
	config_type *           next;               /* next in line */
	const char *            name;               /* node name */
	config_saveload_delegate load;              /* load callback */
	config_saveload_delegate save;              /* save callback */
};



/***************************************************************************
    GLOBAL VARIABLES
***************************************************************************/

static config_type *typelist;



/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

static int config_load_xml(running_machine &machine, emu_file &file, int type);
static int config_save_xml(running_machine &machine, emu_file &file, int type);



/***************************************************************************
    CORE IMPLEMENTATION
***************************************************************************/

/*************************************
 *
 *  Reset the configuration callbacks
 *
 *************************************/

void config_init(running_machine &machine)
{
	typelist = NULL;
}



=======
#define DEBUG_CONFIG        0

//**************************************************************************
//  CONFIGURATION MANAGER
//**************************************************************************

//-------------------------------------------------
//  configuration_manager - constructor
//-------------------------------------------------


configuration_manager::configuration_manager(running_machine &machine)
	: m_machine(machine)
{
}

>>>>>>> upstream/master
/*************************************
 *
 *  Register to be involved in config
 *  save/load
 *
 *************************************/

<<<<<<< HEAD
void config_register(running_machine &machine, const char *nodename, config_saveload_delegate load, config_saveload_delegate save)
{
	config_type *newtype;
	config_type **ptype;

	/* allocate a new type */
	newtype = auto_alloc(machine, config_type);
	newtype->next = NULL;
	newtype->name = nodename;
	newtype->load = load;
	newtype->save = save;

	/* add us to the end */
	for (ptype = &typelist; *ptype; ptype = &(*ptype)->next) { }
	*ptype = newtype;
=======
void configuration_manager::config_register(const char* nodename, config_load_delegate load, config_save_delegate save)
{
	config_element element;
	element.name = nodename;
	element.load = load;
	element.save = save;

	m_typelist.push_back(element);
>>>>>>> upstream/master
}



/*************************************
 *
 *  Settings save/load frontend
 *
 *************************************/

<<<<<<< HEAD
int config_load_settings(running_machine &machine)
{
	const char *controller = machine.options().ctrlr();
	config_type *type;
	int loaded = 0;

	/* loop over all registrants and call their init function */
	for (type = typelist; type; type = type->next)
		type->load(CONFIG_TYPE_INIT, NULL);
=======
int configuration_manager::load_settings()
{
	const char *controller = machine().options().ctrlr();
	int loaded = 0;

	/* loop over all registrants and call their init function */
	for (auto type : m_typelist)
		type.load(config_type::INIT, nullptr);
>>>>>>> upstream/master

	/* now load the controller file */
	if (controller[0] != 0)
	{
		/* open the config file */
<<<<<<< HEAD
		emu_file file(machine.options().ctrlr_path(), OPEN_FLAG_READ);
		file_error filerr = file.open(controller, ".cfg");

		if (filerr != FILERR_NONE)
			throw emu_fatalerror(_("Could not load controller file %s.cfg"), controller);

		/* load the XML */
		if (!config_load_xml(machine, file, CONFIG_TYPE_CONTROLLER))
			throw emu_fatalerror(_("Could not load controller file %s.cfg"), controller);
	}

	/* next load the defaults file */
	emu_file file(machine.options().cfg_directory(), OPEN_FLAG_READ);
	file_error filerr = file.open("default.cfg");
	if (filerr == FILERR_NONE)
		config_load_xml(machine, file, CONFIG_TYPE_DEFAULT);

	/* finally, load the game-specific file */
	filerr = file.open(machine.basename(), ".cfg");
	if (filerr == FILERR_NONE)
		loaded = config_load_xml(machine, file, CONFIG_TYPE_GAME);

	/* loop over all registrants and call their final function */
	for (type = typelist; type; type = type->next)
		type->load(CONFIG_TYPE_FINAL, NULL);
=======
		emu_file file(machine().options().ctrlr_path(), OPEN_FLAG_READ);
		osd_file::error filerr = file.open(controller, ".cfg");

		if (filerr != osd_file::error::NONE)
			throw emu_fatalerror("Could not load controller file %s.cfg", controller);

		/* load the XML */
		if (!load_xml(file, config_type::CONTROLLER))
			throw emu_fatalerror("Could not load controller file %s.cfg", controller);
	}

	/* next load the defaults file */
	emu_file file(machine().options().cfg_directory(), OPEN_FLAG_READ);
	osd_file::error filerr = file.open("default.cfg");
	if (filerr == osd_file::error::NONE)
		load_xml(file, config_type::DEFAULT);

	/* finally, load the game-specific file */
	filerr = file.open(machine().basename(), ".cfg");
	if (filerr == osd_file::error::NONE)
		loaded = load_xml(file, config_type::GAME);

	/* loop over all registrants and call their final function */
	for (auto type : m_typelist)
		type.load(config_type::FINAL, nullptr);
>>>>>>> upstream/master

	/* if we didn't find a saved config, return 0 so the main core knows that it */
	/* is the first time the game is run and it should diplay the disclaimer. */
	return loaded;
}


<<<<<<< HEAD
void config_save_settings(running_machine &machine)
{
	config_type *type;

	/* loop over all registrants and call their init function */
	for (type = typelist; type; type = type->next)
		type->save(CONFIG_TYPE_INIT, NULL);

	/* save the defaults file */
	emu_file file(machine.options().cfg_directory(), OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS);
	file_error filerr = file.open("default.cfg");
	if (filerr == FILERR_NONE)
		config_save_xml(machine, file, CONFIG_TYPE_DEFAULT);

	/* finally, save the game-specific file */
	filerr = file.open(machine.basename(), ".cfg");
	if (filerr == FILERR_NONE)
		config_save_xml(machine, file, CONFIG_TYPE_GAME);

	/* loop over all registrants and call their final function */
	for (type = typelist; type; type = type->next)
		type->save(CONFIG_TYPE_FINAL, NULL);
=======
void configuration_manager::save_settings()
{
	/* loop over all registrants and call their init function */
	for (auto type : m_typelist)
		type.save(config_type::INIT, nullptr);

	/* save the defaults file */
	emu_file file(machine().options().cfg_directory(), OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS);
	osd_file::error filerr = file.open("default.cfg");
	if (filerr == osd_file::error::NONE)
		save_xml(file, config_type::DEFAULT);

	/* finally, save the game-specific file */
	filerr = file.open(machine().basename(), ".cfg");
	if (filerr == osd_file::error::NONE)
		save_xml(file, config_type::GAME);

	/* loop over all registrants and call their final function */
	for (auto type : m_typelist)
		type.save(config_type::FINAL, nullptr);
>>>>>>> upstream/master
}



/*************************************
 *
 *  XML file load
 *
 *************************************/

<<<<<<< HEAD
static int config_load_xml(running_machine &machine, emu_file &file, int which_type)
{
	xml_data_node *root, *confignode, *systemnode;
	config_type *type;
	const char *srcfile;
	int version, count;

	/* read the file */
	root = xml_file_read(file, NULL);
	if (!root)
		goto error;

	/* find the config node */
	confignode = xml_get_sibling(root->child, "mameconfig");
	if (!confignode)
		goto error;

	/* validate the config data version */
	version = xml_get_attribute_int(confignode, "version", 0);
	if (version != CONFIG_VERSION)
		goto error;

	/* strip off all the path crap from the source filename */
	srcfile = strrchr(machine.system().source_file, '/');
	if (!srcfile)
		srcfile = strrchr(machine.system().source_file, '\\');
	if (!srcfile)
		srcfile = strrchr(machine.system().source_file, ':');
	if (!srcfile)
		srcfile = machine.system().source_file;
=======
int configuration_manager::load_xml(emu_file &file, config_type which_type)
{
	/* read the file */
	util::xml::file::ptr const root(util::xml::file::read(file, nullptr));
	if (!root)
		return 0;

	/* find the config node */
	util::xml::data_node const *const confignode = root->get_child("mameconfig");
	if (!confignode)
		return 0;

	/* validate the config data version */
	int const version = confignode->get_attribute_int("version", 0);
	if (version != CONFIG_VERSION)
		return 0;

	/* strip off all the path crap from the source filename */
	const char *srcfile = strrchr(machine().system().type.source(), '/');
	if (!srcfile)
		srcfile = strrchr(machine().system().type.source(), '\\');
	if (!srcfile)
		srcfile = strrchr(machine().system().type.source(), ':');
	if (!srcfile)
		srcfile = machine().system().type.source();
>>>>>>> upstream/master
	else
		srcfile++;

	/* loop over all system nodes in the file */
<<<<<<< HEAD
	count = 0;
	for (systemnode = xml_get_sibling(confignode->child, "system"); systemnode; systemnode = xml_get_sibling(systemnode->next, "system"))
	{
		/* look up the name of the system here; skip if none */
		const char *name = xml_get_attribute_string(systemnode, "name", "");
=======
	int count = 0;
	for (util::xml::data_node const *systemnode = confignode->get_child("system"); systemnode; systemnode = systemnode->get_next_sibling("system"))
	{
		/* look up the name of the system here; skip if none */
		const char *name = systemnode->get_attribute_string("name", "");
>>>>>>> upstream/master

		/* based on the file type, determine whether we have a match */
		switch (which_type)
		{
<<<<<<< HEAD
			case CONFIG_TYPE_GAME:
				/* only match on the specific game name */
				if (strcmp(name, machine.system().name) != 0)
					continue;
				break;

			case CONFIG_TYPE_DEFAULT:
				/* only match on default */
				if (strcmp(name, "default") != 0)
					continue;
				break;

			case CONFIG_TYPE_CONTROLLER:
=======
		case config_type::GAME:
			/* only match on the specific game name */
			if (strcmp(name, machine().system().name) != 0)
				continue;
			break;

		case config_type::DEFAULT:
			/* only match on default */
			if (strcmp(name, "default") != 0)
				continue;
			break;

		case config_type::CONTROLLER:
>>>>>>> upstream/master
			{
				int clone_of;
				/* match on: default, game name, source file name, parent name, grandparent name */
				if (strcmp(name, "default") != 0 &&
<<<<<<< HEAD
					strcmp(name, machine.system().name) != 0 &&
					strcmp(name, srcfile) != 0 &&
					((clone_of = driver_list::clone(machine.system())) == -1 || strcmp(name, driver_list::driver(clone_of).name) != 0) &&
=======
					strcmp(name, machine().system().name) != 0 &&
					strcmp(name, srcfile) != 0 &&
					((clone_of = driver_list::clone(machine().system())) == -1 || strcmp(name, driver_list::driver(clone_of).name) != 0) &&
>>>>>>> upstream/master
					(clone_of == -1 || ((clone_of = driver_list::clone(clone_of)) == -1) || strcmp(name, driver_list::driver(clone_of).name) != 0))
					continue;
				break;
			}
<<<<<<< HEAD
=======

		default:
			break;
>>>>>>> upstream/master
		}

		/* log that we are processing this entry */
		if (DEBUG_CONFIG)
			osd_printf_debug("Entry: %s -- processing\n", name);

		/* loop over all registrants and call their load function */
<<<<<<< HEAD
		for (type = typelist; type; type = type->next)
			type->load(which_type, xml_get_sibling(systemnode->child, type->name));
=======
		for (auto type : m_typelist)
			type.load(which_type, systemnode->get_child(type.name.c_str()));
>>>>>>> upstream/master
		count++;
	}

	/* error if this isn't a valid game match */
	if (count == 0)
<<<<<<< HEAD
		goto error;

	/* free the parser */
	xml_file_free(root);
	return 1;

error:
	if (root)
		xml_file_free(root);
	return 0;
=======
		return 0;

	return 1;
>>>>>>> upstream/master
}



/*************************************
 *
 *  XML file save
 *
 *************************************/

<<<<<<< HEAD
static int config_save_xml(running_machine &machine, emu_file &file, int which_type)
{
	xml_data_node *root = xml_file_create();
	xml_data_node *confignode, *systemnode;
	config_type *type;
=======
int configuration_manager::save_xml(emu_file &file, config_type which_type)
{
	util::xml::file::ptr root(util::xml::file::create());
>>>>>>> upstream/master

	/* if we don't have a root, bail */
	if (!root)
		return 0;

	/* create a config node */
<<<<<<< HEAD
	confignode = xml_add_child(root, "mameconfig", NULL);
	if (!confignode)
		goto error;
	xml_set_attribute_int(confignode, "version", CONFIG_VERSION);

	/* create a system node */
	systemnode = xml_add_child(confignode, "system", NULL);
	if (!systemnode)
		goto error;
	xml_set_attribute(systemnode, "name", (which_type == CONFIG_TYPE_DEFAULT) ? "default" : machine.system().name);

	/* create the input node and write it out */
	/* loop over all registrants and call their save function */
	for (type = typelist; type; type = type->next)
	{
		xml_data_node *curnode = xml_add_child(systemnode, type->name, NULL);
		if (!curnode)
			goto error;
		type->save(which_type, curnode);

		/* if nothing was added, just nuke the node */
		if (!curnode->value && !curnode->child)
			xml_delete_node(curnode);
	}

	/* flush the file */
	xml_file_write(root, file);

	/* free and get out of here */
	xml_file_free(root);
	return 1;

error:
	xml_file_free(root);
	return 0;
=======
	util::xml::data_node *const confignode = root->add_child("mameconfig", nullptr);
	if (!confignode)
		return 0;
	confignode->set_attribute_int("version", CONFIG_VERSION);

	/* create a system node */
	util::xml::data_node *const systemnode = confignode->add_child("system", nullptr);
	if (!systemnode)
		return 0;
	systemnode->set_attribute("name", (which_type == config_type::DEFAULT) ? "default" : machine().system().name);

	/* create the input node and write it out */
	/* loop over all registrants and call their save function */
	for (auto type : m_typelist)
	{
		util::xml::data_node *const curnode = systemnode->add_child(type.name.c_str(), nullptr);
		if (!curnode)
			return 0;
		type.save(which_type, curnode);

		/* if nothing was added, just nuke the node */
		if (!curnode->get_value() && !curnode->get_first_child())
			curnode->delete_node();
	}

	/* flush the file */
	root->write(file);

	/* free and get out of here */
	return 1;
>>>>>>> upstream/master
}
