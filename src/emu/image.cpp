// license:BSD-3-Clause
// copyright-holders:Nathan Woods, Miodrag Milanovic
/***************************************************************************

<<<<<<< HEAD
    image.c
=======
    image.cpp
>>>>>>> upstream/master

    Core image functions and definitions.


***************************************************************************/
<<<<<<< HEAD
=======

>>>>>>> upstream/master
#include <ctype.h>

#include "emu.h"
#include "emuopts.h"
#include "image.h"
#include "config.h"
#include "xmlfile.h"
<<<<<<< HEAD
#include "formats/ioprocs.h"

/* ----------------------------------------------------------------------- */

static int image_fseek_thunk(void *file, INT64 offset, int whence)
{
	device_image_interface *image = (device_image_interface *) file;
	return image->fseek(offset, whence);
}

static size_t image_fread_thunk(void *file, void *buffer, size_t length)
{
	device_image_interface *image = (device_image_interface *) file;
	return image->fread(buffer, length);
}

static size_t image_fwrite_thunk(void *file, const void *buffer, size_t length)
{
	device_image_interface *image = (device_image_interface *) file;
	return image->fwrite(buffer, length);
}

static UINT64 image_fsize_thunk(void *file)
{
	device_image_interface *image = (device_image_interface *) file;
	return image->length();
}

/* ----------------------------------------------------------------------- */

struct io_procs image_ioprocs =
{
	NULL,
	image_fseek_thunk,
	image_fread_thunk,
	image_fwrite_thunk,
	image_fsize_thunk
};

/***************************************************************************
    INITIALIZATION HELPERS
***************************************************************************/

/*-------------------------------------------------
    image_dirs_load - loads image device directory
    configuration items
-------------------------------------------------*/

static void image_dirs_load(running_machine &machine, int config_type, xml_data_node *parentnode)
{
	xml_data_node *node;
	const char *dev_instance;
	const char *working_directory;

	if ((config_type == CONFIG_TYPE_GAME) && (parentnode != NULL))
	{
		for (node = xml_get_sibling(parentnode->child, "device"); node; node = xml_get_sibling(node->next, "device"))
		{
			dev_instance = xml_get_attribute_string(node, "instance", NULL);

			if ((dev_instance != NULL) && (dev_instance[0] != '\0'))
			{
				image_interface_iterator iter(machine.root_device());
				for (device_image_interface *image = iter.first(); image != NULL; image = iter.next())
				{
					if (!strcmp(dev_instance, image->instance_name())) {
						working_directory = xml_get_attribute_string(node, "directory", NULL);
						if (working_directory != NULL)
							image->set_working_directory(working_directory);
=======
#include "softlist.h"


//**************************************************************************
//  IMAGE MANAGER
//**************************************************************************

//-------------------------------------------------
//  image_manager - constructor
//-------------------------------------------------

image_manager::image_manager(running_machine &machine)
	: m_machine(machine)
{
	// make sure that any required devices have been allocated
	for (device_image_interface &image : image_interface_iterator(machine.root_device()))
	{
		// ignore things not user loadable
		if (!image.user_loadable())
			continue;

		// find the image option in image_options()
		const std::string &startup_image(machine.options().image_option(image.instance_name()).value());

		// is an image specified for this image?
		if (!startup_image.empty())
		{
			// we do have a startup image specified - load it
			image_init_result result = image_init_result::FAIL;

			// try as a softlist
			if (software_name_parse(startup_image))
				result = image.load_software(startup_image);

			// failing that, try as an image
			if (result != image_init_result::PASS)
				result = image.load(startup_image);

			// failing that, try creating it (if appropriate)
			if (result != image_init_result::PASS && image.support_command_line_image_creation())
				result = image.create(startup_image);

			// did the image load fail?
			if (result != image_init_result::PASS)
			{
				// retrieve image error message
				std::string image_err = std::string(image.error());

				// unload the bad image
				image.unload();

				// make sure it is removed from the ini file too
				machine.options().image_option(image.instance_name()).specify("");
				if (machine.options().write_config())
					write_config(machine.options(), nullptr, &machine.system());

				fatalerror_exitcode(machine, EMU_ERR_DEVICE, "Device %s load (%s) failed: %s",
					image.device().name(),
					startup_image.c_str(),
					image_err.c_str());
			}
		}
	}

	machine.configuration().config_register("image_directories", config_load_delegate(&image_manager::config_load, this), config_save_delegate(&image_manager::config_save, this));
}

//-------------------------------------------------
//  unload_all - unload all images and
//  extract options
//-------------------------------------------------
void image_manager::unload_all()
{
	// extract the options
	options_extract();

	for (device_image_interface &image : image_interface_iterator(machine().root_device()))
	{
		// unload this image
		image.unload();
	}
}

void image_manager::config_load(config_type cfg_type, util::xml::data_node const *parentnode)
{
	if ((cfg_type == config_type::GAME) && (parentnode != nullptr))
	{
		for (util::xml::data_node const *node = parentnode->get_child("device"); node; node = node->get_next_sibling("device"))
		{
			const char *const dev_instance = node->get_attribute_string("instance", nullptr);

			if ((dev_instance != nullptr) && (dev_instance[0] != '\0'))
			{
				for (device_image_interface &image : image_interface_iterator(machine().root_device()))
				{
					if (!strcmp(dev_instance, image.instance_name().c_str()))
					{
						const char *const working_directory = node->get_attribute_string("directory", nullptr);
						if (working_directory != nullptr)
							image.set_working_directory(working_directory);
>>>>>>> upstream/master
					}
				}
			}
		}
	}
}

<<<<<<< HEAD


/*-------------------------------------------------
    image_dirs_save - saves out image device
    directories to the configuration file
-------------------------------------------------*/

static void image_dirs_save(running_machine &machine, int config_type, xml_data_node *parentnode)
{
	xml_data_node *node;
	const char *dev_instance;

	/* only care about game-specific data */
	if (config_type == CONFIG_TYPE_GAME)
	{
		image_interface_iterator iter(machine.root_device());
		for (device_image_interface *image = iter.first(); image != NULL; image = iter.next())
		{
			dev_instance = image->instance_name();

			node = xml_add_child(parentnode, "device", NULL);
			if (node != NULL)
			{
				xml_set_attribute(node, "instance", dev_instance);
				xml_set_attribute(node, "directory", image->working_directory());
=======
/*-------------------------------------------------
    config_save - saves out image device
    directories to the configuration file
-------------------------------------------------*/

void image_manager::config_save(config_type cfg_type, util::xml::data_node *parentnode)
{
	/* only care about game-specific data */
	if (cfg_type == config_type::GAME)
	{
		for (device_image_interface &image : image_interface_iterator(machine().root_device()))
		{
			const char *const dev_instance = image.instance_name().c_str();

			util::xml::data_node *const node = parentnode->add_child("device", nullptr);
			if (node != nullptr)
			{
				node->set_attribute("instance", dev_instance);
				node->set_attribute("directory", image.working_directory().c_str());
>>>>>>> upstream/master
			}
		}
	}
}

/*-------------------------------------------------
    write_config - emit current option statuses as
    INI files
-------------------------------------------------*/

<<<<<<< HEAD
static int write_config(emu_options &options, const char *filename, const game_driver *gamedrv)
=======
int image_manager::write_config(emu_options &options, const char *filename, const game_driver *gamedrv)
>>>>>>> upstream/master
{
	char buffer[128];
	int retval = 1;

<<<<<<< HEAD
	if (gamedrv != NULL)
=======
	if (gamedrv != nullptr)
>>>>>>> upstream/master
	{
		sprintf(buffer, "%s.ini", gamedrv->name);
		filename = buffer;
	}

	emu_file file(options.ini_path(), OPEN_FLAG_WRITE | OPEN_FLAG_CREATE);
<<<<<<< HEAD
	file_error filerr = file.open(filename);
	if (filerr == FILERR_NONE)
	{
		std::string inistring;
		options.output_ini(inistring);
=======
	osd_file::error filerr = file.open(filename);
	if (filerr == osd_file::error::NONE)
	{
		std::string inistring = options.output_ini();
>>>>>>> upstream/master
		file.puts(inistring.c_str());
		retval = 0;
	}
	return retval;
}

/*-------------------------------------------------
<<<<<<< HEAD
    image_options_extract - extract device options
    out of core into the options
-------------------------------------------------*/

static void image_options_extract(running_machine &machine)
{
	/* only extract the device options if we've added them
	   no need to assert in case they are missing */
	{
		int index = 0;

		image_interface_iterator iter(machine.root_device());
		for (device_image_interface *image = iter.first(); image != NULL; image = iter.next())
		{
			const char *filename = image->filename();

			/* and set the option */
			std::string error;
			machine.options().set_value(image->instance_name(), filename ? filename : "", OPTION_PRIORITY_CMDLINE, error);

			index++;
		}
	}

	/* write the config, if appropriate */
	if (machine.options().write_config())
		write_config(machine.options(), NULL, &machine.system());
}

/*-------------------------------------------------
    image_unload_all - unload all images and
    extract options
-------------------------------------------------*/

void image_unload_all(running_machine &machine)
{
	// extract the options
	image_options_extract(machine);

	image_interface_iterator iter(machine.root_device());
	for (device_image_interface *image = iter.first(); image != NULL; image = iter.next())
	{
		// unload this image
		image->unload();
	}
}
/*-------------------------------------------------
    image_device_init - initialize devices for a specific
    running_machine
-------------------------------------------------*/

void image_device_init(running_machine &machine)
{
	const char *image_name;

	/* make sure that any required devices have been allocated */
	image_interface_iterator iter(machine.root_device());
	for (device_image_interface *image = iter.first(); image != NULL; image = iter.next())
	{
		/* is an image specified for this image */
		image_name = machine.options().value(image->instance_name());

		if ((image_name != NULL) && (image_name[0] != '\0'))
		{
			/* mark init state */
			image->set_init_phase();

			/* try to load this image */
			bool result = image->load(image_name);

			/* did the image load fail? */
			if (result)
			{
				/* retrieve image error message */
				std::string image_err = std::string(image->error());
				std::string image_basename(image_name);

				/* unload all images */
				image_unload_all(machine);

				fatalerror_exitcode(machine, MAMERR_DEVICE, "Device %s load (%s) failed: %s",
					image->device().name(),
					image_basename.c_str(),
					image_err.c_str());
			}
		}
	}
}

/*-------------------------------------------------
 image_mandatory_scan - search for devices which
 need an image to be loaded
 -------------------------------------------------*/

std::string &image_mandatory_scan(running_machine &machine, std::string &mandatory)
{
	mandatory.clear();
	// make sure that any required image has a mounted file
	image_interface_iterator iter(machine.root_device());
	for (device_image_interface *image = iter.first(); image != NULL; image = iter.next())
	{
		if (image->filename() == NULL && image->must_be_loaded())
			mandatory.append("\"").append(image->instance_name()).append("\", ");
	}
	return mandatory;
}

/*-------------------------------------------------
    image_postdevice_init - initialize devices for a specific
    running_machine
-------------------------------------------------*/

void image_postdevice_init(running_machine &machine)
{
	/* make sure that any required devices have been allocated */
	image_interface_iterator iter(machine.root_device());
	for (device_image_interface *image = iter.first(); image != NULL; image = iter.next())
	{
			int result = image->finish_load();
			/* did the image load fail? */
			if (result)
			{
				/* retrieve image error message */
				std::string image_err = std::string(image->error());

				/* unload all images */
				image_unload_all(machine);

				fatalerror_exitcode(machine, MAMERR_DEVICE, "Device %s load failed: %s",
					image->device().name(),
					image_err.c_str());
			}
	}

	/* add a callback for when we shut down */
	machine.add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(FUNC(image_unload_all), &machine));
}
/***************************************************************************
    INITIALIZATION
***************************************************************************/

/*-------------------------------------------------
    image_init - start up the image system
-------------------------------------------------*/

void image_init(running_machine &machine)
{
	image_device_init(machine);
	config_register(machine, "image_directories", config_saveload_delegate(FUNC(image_dirs_load), &machine), config_saveload_delegate(FUNC(image_dirs_save), &machine));
}


/****************************************************************************
  Battery functions

  These functions provide transparent access to battery-backed RAM on an
  image; typically for cartridges.
****************************************************************************/

/*-------------------------------------------------
    image_battery_load_by_name - retrieves the battery
    backed RAM for an image. A filename may be supplied
    to the function.

    The function comes in two flavors, depending on
    what should happen when no battery is available:
    we could fill the memory with a given value, or
    pass a default battery (for a pre-initialized
    battery from factory)
-------------------------------------------------*/

void image_battery_load_by_name(emu_options &options, const char *filename, void *buffer, int length, int fill)
{
	file_error filerr;
	int bytes_read = 0;

	assert_always(buffer && (length > 0), "Must specify sensical buffer/length");

	/* try to open the battery file and read it in, if possible */
	emu_file file(options.nvram_directory(), OPEN_FLAG_READ);
	filerr = file.open(filename);
	if (filerr == FILERR_NONE)
		bytes_read = file.read(buffer, length);

	/* fill remaining bytes (if necessary) */
	memset(((char *) buffer) + bytes_read, fill, length - bytes_read);
}

void image_battery_load_by_name(emu_options &options, const char *filename, void *buffer, int length, void *def_buffer)
{
	file_error filerr;
	int bytes_read = 0;

	assert_always(buffer && (length > 0), "Must specify sensical buffer/length");

	/* try to open the battery file and read it in, if possible */
	emu_file file(options.nvram_directory(), OPEN_FLAG_READ);
	filerr = file.open(filename);
	if (filerr == FILERR_NONE)
		bytes_read = file.read(buffer, length);

	/* if no file was present, copy the default battery */
	if (bytes_read == 0 && def_buffer)
		memcpy((char *) buffer, (char *) def_buffer, length);
}

/*-------------------------------------------------
    image_battery_save_by_name - stores the battery
    backed RAM for an image. A filename may be supplied
    to the function.
-------------------------------------------------*/
void image_battery_save_by_name(emu_options &options, const char *filename, const void *buffer, int length)
{
	assert_always(buffer && (length > 0), "Must specify sensical buffer/length");

	/* try to open the battery file and write it out, if possible */
	emu_file file(options.nvram_directory(), OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS);
	file_error filerr = file.open(filename);
	if (filerr == FILERR_NONE)
		file.write(buffer, length);
=======
    options_extract - extract device options
    out of core into the options
-------------------------------------------------*/

void image_manager::options_extract()
{
	for (device_image_interface &image : image_interface_iterator(machine().root_device()))
	{
		// There are two scenarios where we want to extract the option:
		//
		//  1.  When for the device, is_reset_on_load() is false (mounting devices for which is reset_and_load()
		//      is true forces a reset, hence the name)
		//
		//  2.  When is_reset_on_load(), and this results in a device being unmounted (unmounting is_reset_and_load()
		//      doesn't force an unmount).
		//
		//      Note that as a part of #2, we cannot extract the option when the image in question is a part of an
		//      active reset_on_load; hence the check for is_reset_and_loading() (see issue #2414)
		if (!image.is_reset_on_load()
			|| (!image.exists() && !image.is_reset_and_loading() && !machine().options().image_option(image.instance_name()).value().empty()))
		{
			// we have to assemble the image option differently for software lists and for normal images
			std::string image_opt;
			if (image.exists())
			{
				if (!image.loaded_through_softlist())
					image_opt = image.filename();
				else if (image.part_entry() && !image.part_entry()->name().empty())
					image_opt = util::string_format("%s:%s:%s", image.software_list_name(), image.full_software_name(), image.part_entry()->name());
				else
					image_opt = util::string_format("%s:%s", image.software_list_name(), image.full_software_name());
			}

			// and set the option (provided that it hasn't been removed out from under us)
			if (machine().options().exists(image.instance_name()))
				machine().options().image_option(image.instance_name()).specify(std::move(image_opt));
		}
	}

	// write the config, if appropriate
	if (machine().options().write_config())
		write_config(machine().options(), nullptr, &machine().system());
}


/*-------------------------------------------------
    postdevice_init - initialize devices for a specific
    running_machine
-------------------------------------------------*/

void image_manager::postdevice_init()
{
	/* make sure that any required devices have been allocated */
	for (device_image_interface &image : image_interface_iterator(machine().root_device()))
	{
		image_init_result result = image.finish_load();

		/* did the image load fail? */
		if (result != image_init_result::PASS)
		{
			/* retrieve image error message */
			std::string image_err = std::string(image.error());

			/* unload all images */
			unload_all();

			fatalerror_exitcode(machine(), EMU_ERR_DEVICE, "Device %s load failed: %s",
				image.device().name(),
				image_err.c_str());
		}
	}
	/* add a callback for when we shut down */
	machine().add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(&image_manager::unload_all, this));
>>>>>>> upstream/master
}
