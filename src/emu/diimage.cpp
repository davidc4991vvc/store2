// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
/***************************************************************************

    diimage.c

    Device image interfaces.

***************************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "emuopts.h"
#include "drivenum.h"
#include "ui/ui.h"
#include "ui/menu.h"
#include "zippath.h"
#include "ui/imgcntrl.h"
#include "softlist.h"
#include "image.h"
=======

#include "emuopts.h"
#include "drivenum.h"
#include "ui/uimain.h"
#include "zippath.h"
#include "softlist.h"
#include "softlist_dev.h"
#include "formats/ioprocs.h"

#include <regex>

>>>>>>> upstream/master

//**************************************************************************
//  DEVICE CONFIG IMAGE INTERFACE
//**************************************************************************
const image_device_type_info device_image_interface::m_device_info_array[] =
	{
		{ IO_UNKNOWN,   "unknown",      "unkn" },
		{ IO_CARTSLOT,  "cartridge",    "cart" }, /*  0 */
		{ IO_FLOPPY,    "floppydisk",   "flop" }, /*  1 */
		{ IO_HARDDISK,  "harddisk",     "hard" }, /*  2 */
		{ IO_CYLINDER,  "cylinder",     "cyln" }, /*  3 */
		{ IO_CASSETTE,  "cassette",     "cass" }, /*  4 */
		{ IO_PUNCHCARD, "punchcard",    "pcrd" }, /*  5 */
		{ IO_PUNCHTAPE, "punchtape",    "ptap" }, /*  6 */
<<<<<<< HEAD
		{ IO_PRINTER,   "printer",      "prin" }, /*  7 */
=======
		{ IO_PRINTER,   "printout",     "prin" }, /*  7 */
>>>>>>> upstream/master
		{ IO_SERIAL,    "serial",       "serl" }, /*  8 */
		{ IO_PARALLEL,  "parallel",     "parl" }, /*  9 */
		{ IO_SNAPSHOT,  "snapshot",     "dump" }, /* 10 */
		{ IO_QUICKLOAD, "quickload",    "quik" }, /* 11 */
		{ IO_MEMCARD,   "memcard",      "memc" }, /* 12 */
		{ IO_CDROM,     "cdrom",        "cdrm" }, /* 13 */
		{ IO_MAGTAPE,   "magtape",      "magt" }, /* 14 */
		{ IO_ROM,       "romimage",     "rom"  }, /* 15 */
		{ IO_MIDIIN,    "midiin",       "min"  }, /* 16 */
		{ IO_MIDIOUT,   "midiout",      "mout" }  /* 17 */
	};


//**************************************************************************
<<<<<<< HEAD
=======
//  IMAGE DEVICE FORMAT
//**************************************************************************

//-------------------------------------------------
//  ctor
//-------------------------------------------------

image_device_format::image_device_format(const std::string &name, const std::string &description, const std::string &extensions, const std::string &optspec)
	: m_name(name), m_description(description), m_optspec(optspec)
{
	std::regex comma_regex("\\,");
	std::copy(
		std::sregex_token_iterator(extensions.begin(), extensions.end(), comma_regex, -1),
		std::sregex_token_iterator(),
		std::back_inserter(m_extensions));
}


//-------------------------------------------------
//  dtor
//-------------------------------------------------

image_device_format::~image_device_format()
{
}


//**************************************************************************
>>>>>>> upstream/master
//  DEVICE IMAGE INTERFACE
//**************************************************************************

//-------------------------------------------------
//  device_image_interface - constructor
//-------------------------------------------------

device_image_interface::device_image_interface(const machine_config &mconfig, device_t &device)
	: device_interface(device, "image"),
		m_err(),
<<<<<<< HEAD
		m_file(NULL),
		m_mame_file(NULL),
		m_software_info_ptr(NULL),
		m_software_part_ptr(NULL),
		m_supported(0),
		m_readonly(false),
		m_created(false),
		m_init_phase(false),
		m_from_swlist(false),
		m_create_format(0),
		m_create_args(NULL),
		m_is_loading(FALSE)
=======
		m_file(),
		m_mame_file(),
		m_software_part_ptr(nullptr),
		m_supported(0),
		m_readonly(false),
		m_created(false),
		m_create_format(0),
		m_create_args(nullptr),
		m_user_loadable(true),
		m_is_loading(false),
		m_is_reset_and_loading(false)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  ~device_image_interface - destructor
//-------------------------------------------------

device_image_interface::~device_image_interface()
{
}

<<<<<<< HEAD
=======

//-------------------------------------------------
//  interface_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void device_image_interface::interface_config_complete()
{
	// set brief and instance name
	update_names();
}


>>>>>>> upstream/master
//-------------------------------------------------
//  find_device_type - search trough list of
//  device types to extract data
//-------------------------------------------------

const image_device_type_info *device_image_interface::find_device_type(iodevice_t type)
{
	int i;
	for (i = 0; i < ARRAY_LENGTH(device_image_interface::m_device_info_array); i++)
	{
		if (m_device_info_array[i].m_type == type)
			return &m_device_info_array[i];
	}
<<<<<<< HEAD
	return NULL;
=======
	return nullptr;
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_typename - retrieves device type name
//-------------------------------------------------

const char *device_image_interface::device_typename(iodevice_t type)
{
	const image_device_type_info *info = find_device_type(type);
<<<<<<< HEAD
	return (info != NULL) ? info->m_name : NULL;
=======
	return (info != nullptr) ? info->m_name : "unknown";
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_brieftypename - retrieves device
//  brief type name
//-------------------------------------------------

const char *device_image_interface::device_brieftypename(iodevice_t type)
{
	const image_device_type_info *info = find_device_type(type);
<<<<<<< HEAD
	return (info != NULL) ? info->m_shortname : NULL;
=======
	return (info != nullptr) ? info->m_shortname : "unk";
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_typeid - retrieves device type id
//-------------------------------------------------

iodevice_t device_image_interface::device_typeid(const char *name)
{
	int i;
	for (i = 0; i < ARRAY_LENGTH(device_image_interface::m_device_info_array); i++)
	{
		if (!core_stricmp(name, m_device_info_array[i].m_name) || !core_stricmp(name, m_device_info_array[i].m_shortname))
			return m_device_info_array[i].m_type;
	}
	return (iodevice_t)-1;
}

<<<<<<< HEAD
/*-------------------------------------------------
    device_compute_hash - compute a hash,
    using this device's partial hash if appropriate
-------------------------------------------------*/

void device_image_interface::device_compute_hash(hash_collection &hashes, const void *data, size_t length, const char *types) const
{
	/* retrieve the partial hash func */
	device_image_partialhash_func partialhash = get_partial_hash();

	/* compute the hash */
	if (partialhash)
		partialhash(hashes, (const unsigned char*)data, length, types);
	else
		hashes.compute(reinterpret_cast<const UINT8 *>(data), length, types);
}

/*-------------------------------------------------
    set_image_filename - specifies the filename of
    an image
-------------------------------------------------*/

image_error_t device_image_interface::set_image_filename(const char *filename)
{
	m_image_name = filename;
	zippath_parent(m_working_directory, filename);
	m_basename.assign(m_image_name);

	int loc1 = m_image_name.find_last_of('\\');
	int loc2 = m_image_name.find_last_of('/');
	int loc3 = m_image_name.find_last_of(':');
	int loc = MAX(loc1,MAX(loc2,loc3));
	if (loc!=-1) {
		if (loc == loc3)
		{
			// temp workaround for softlists now that m_image_name contains the part name too (e.g. list:gamename:cart)
			m_basename = m_basename.substr(0, loc);
			std::string tmpstr = std::string(m_basename);
			int tmploc = tmpstr.find_last_of(':');
			m_basename = m_basename.substr(tmploc + 1,loc-tmploc);
		}
		else
			m_basename = m_basename.substr(loc + 1, m_basename.length() - loc);
	}
	m_basename_noext = m_basename.assign(m_basename);
	m_filetype = "";
	loc = m_basename_noext.find_last_of('.');
	if (loc!=-1) {
		m_basename_noext = m_basename_noext.substr(0,loc);
		m_filetype = m_basename.assign(m_basename);
		m_filetype = m_filetype.substr(loc + 1, m_filetype.length() - loc);
	}

	return IMAGE_ERROR_SUCCESS;
}

=======
//-------------------------------------------------
//  set_image_filename - specifies the filename of
//  an image
//-------------------------------------------------

void device_image_interface::set_image_filename(const std::string &filename)
{
	m_image_name = filename;
	util::zippath_parent(m_working_directory, filename);
	m_basename.assign(m_image_name);

	// find the last "path separator"
	auto iter = std::find_if(
		m_image_name.rbegin(),
		m_image_name.rend(),
		[](char c) { return (c == '\\') || (c == '/') || (c == ':'); });

	if (iter != m_image_name.rend())
		m_basename.assign(iter.base(), m_image_name.end());

	m_basename_noext = m_basename;
	auto loc = m_basename_noext.find_last_of('.');
	if (loc != std::string::npos)
		m_basename_noext = m_basename_noext.substr(0, loc);

	m_filetype = core_filename_extract_extension(m_basename, true);
}


>>>>>>> upstream/master
/****************************************************************************
    CREATION FORMATS
****************************************************************************/

<<<<<<< HEAD
/*-------------------------------------------------
    device_get_named_creatable_format -
    accesses a specific image format available for
    image creation by name
-------------------------------------------------*/

const image_device_format *device_image_interface::device_get_named_creatable_format(const char *format_name)
{
	for (const image_device_format *format = m_formatlist.first(); format != NULL; format = format->next())
		if (strcmp(format->name(), format_name) == 0)
			return format;
	return NULL;
}

=======
//-------------------------------------------------
//  device_get_named_creatable_format -
//  accesses a specific image format available for
//  image creation by name
//-------------------------------------------------

const image_device_format *device_image_interface::device_get_named_creatable_format(const std::string &format_name)
{
	for (auto &format : m_formatlist)
		if (format->name() == format_name)
			return format.get();
	return nullptr;
}


//-------------------------------------------------
//  add_format
//-------------------------------------------------

void device_image_interface::add_format(std::unique_ptr<image_device_format> &&format)
{
	m_formatlist.push_back(std::move(format));
}


//-------------------------------------------------
//  add_format
//-------------------------------------------------

void device_image_interface::add_format(std::string &&name, std::string &&description, std::string &&extensions, std::string &&optspec)
{
	auto format = std::make_unique<image_device_format>(std::move(name), std::move(description), std::move(extensions), std::move(optspec));
	add_format(std::move(format));
}


>>>>>>> upstream/master
/****************************************************************************
    ERROR HANDLING
****************************************************************************/

<<<<<<< HEAD
/*-------------------------------------------------
    image_clear_error - clear out any specified
    error
-------------------------------------------------*/
=======
//-------------------------------------------------
//  image_clear_error - clear out any specified
//  error
//-------------------------------------------------
>>>>>>> upstream/master

void device_image_interface::clear_error()
{
	m_err = IMAGE_ERROR_SUCCESS;
	if (!m_err_message.empty())
	{
		m_err_message.clear();
	}
}



<<<<<<< HEAD
/*-------------------------------------------------
    error - returns the error text for an image
    error
-------------------------------------------------*/
=======
//-------------------------------------------------
//  error - returns the error text for an image
//  error
//-------------------------------------------------

>>>>>>> upstream/master
static const char *const messages[] =
{
	"",
	"Internal error",
	"Unsupported operation",
	"Out of memory",
	"File not found",
	"Invalid image",
	"File already open",
	"Unspecified error"
};

const char *device_image_interface::error()
{
	return (!m_err_message.empty()) ? m_err_message.c_str() : messages[m_err];
}



<<<<<<< HEAD
/*-------------------------------------------------
    seterror - specifies an error on an image
-------------------------------------------------*/
=======
//-------------------------------------------------
//  seterror - specifies an error on an image
//-------------------------------------------------
>>>>>>> upstream/master

void device_image_interface::seterror(image_error_t err, const char *message)
{
	clear_error();
	m_err = err;
<<<<<<< HEAD
	if (message != NULL)
=======
	if (message != nullptr)
>>>>>>> upstream/master
	{
		m_err_message = message;
	}
}



<<<<<<< HEAD
/*-------------------------------------------------
    message - used to display a message while
    loading
-------------------------------------------------*/
=======
//-------------------------------------------------
//  message - used to display a message while
//  loading
//-------------------------------------------------
>>>>>>> upstream/master

void device_image_interface::message(const char *format, ...)
{
	va_list args;
	char buffer[256];

	/* format the message */
	va_start(args, format);
	vsnprintf(buffer, ARRAY_LENGTH(buffer), format, args);
	va_end(args);

	/* display the popup for a standard amount of time */
	device().machine().ui().popup_time(5, "%s: %s",
		basename(),
		buffer);
}


/***************************************************************************
    WORKING DIRECTORIES
***************************************************************************/

<<<<<<< HEAD
/*-------------------------------------------------
    try_change_working_directory - tries to change
    the working directory, but only if the directory
    actually exists
-------------------------------------------------*/
bool device_image_interface::try_change_working_directory(const char *subdir)
{
	osd_directory *directory;
	const osd_directory_entry *entry;
	bool success = FALSE;
	bool done = FALSE;

	directory = osd_opendir(m_working_directory.c_str());
	if (directory != NULL)
	{
		while(!done && (entry = osd_readdir(directory)) != NULL)
		{
			if (!core_stricmp(subdir, entry->name))
			{
				done = TRUE;
				success = entry->type == ENTTYPE_DIR;
			}
		}

		osd_closedir(directory);
	}

	/* did we successfully identify the directory? */
	if (success)
		zippath_combine(m_working_directory, m_working_directory.c_str(), subdir);

	return success;
}
/*-------------------------------------------------
    setup_working_directory - sets up the working
    directory according to a few defaults
-------------------------------------------------*/

void device_image_interface::setup_working_directory()
{
	char *dst = NULL;

	osd_get_full_path(&dst,".");
	/* first set up the working directory to be the starting directory */
	m_working_directory = dst;

	/* now try browsing down to "software" */
	if (try_change_working_directory("software"))
	{
		/* now down to a directory for this computer */
=======
//-------------------------------------------------
//  try_change_working_directory - tries to change
//  the working directory, but only if the directory
//  actually exists
//-------------------------------------------------

bool device_image_interface::try_change_working_directory(const std::string &subdir)
{
	const osd::directory::entry *entry;
	bool success = false;
	bool done = false;

	auto directory = osd::directory::open(m_working_directory);
	if (directory)
	{
		while (!done && (entry = directory->read()) != nullptr)
		{
			if (!core_stricmp(subdir.c_str(), entry->name))
			{
				done = true;
				success = entry->type == osd::directory::entry::entry_type::DIR;
			}
		}

		directory.reset();
	}

	// did we successfully identify the directory?
	if (success)
		m_working_directory = util::zippath_combine(m_working_directory, subdir);

	return success;
}


//-------------------------------------------------
//  setup_working_directory - sets up the working
//  directory according to a few defaults
//-------------------------------------------------

void device_image_interface::setup_working_directory()
{
	bool success = false;
	// get user-specified directory and make sure it exists
	m_working_directory = device().mconfig().options().sw_path();
	// if multipath, get first
	size_t i = m_working_directory.find_first_of(";");
	if (i != std::string::npos)
		m_working_directory.resize(i);
	// validate directory
	if (!m_working_directory.empty())
		if (osd::directory::open(m_working_directory))
			success = true;

	// if not exist, use previous method
	if (!success)
	{
		// first set up the working directory to be the starting directory
		osd_get_full_path(m_working_directory, ".");
		// now try browsing down to "software"
		if (try_change_working_directory("software"))
			success = true;
	}

	if (success)
	{
		// now down to a directory for this computer
>>>>>>> upstream/master
		int gamedrv = driver_list::find(device().machine().system());
		while(gamedrv != -1 && !try_change_working_directory(driver_list::driver(gamedrv).name))
		{
			gamedrv = driver_list::compatible_with(gamedrv);
		}
	}
<<<<<<< HEAD
	osd_free(dst);
}

=======
}


>>>>>>> upstream/master
//-------------------------------------------------
//  working_directory - returns the working
//  directory to use for this image; this is
//  valid even if not mounted
//-------------------------------------------------

<<<<<<< HEAD
const char * device_image_interface::working_directory()
{
	/* check to see if we've never initialized the working directory */
	if (m_working_directory.empty())
		setup_working_directory();

	return m_working_directory.c_str();
}


/*-------------------------------------------------
    get_software_region
-------------------------------------------------*/

UINT8 *device_image_interface::get_software_region(const char *tag)
{
	char full_tag[256];

	if ( m_software_info_ptr == NULL || m_software_part_ptr == NULL )
		return NULL;

	sprintf( full_tag, "%s:%s", device().tag(), tag );
	return device().machine().root_device().memregion( full_tag )->base();
}


/*-------------------------------------------------
    image_get_software_region_length
-------------------------------------------------*/

UINT32 device_image_interface::get_software_region_length(const char *tag)
{
	char full_tag[256];

	sprintf( full_tag, "%s:%s", device().tag(), tag );
	return device().machine().root_device().memregion( full_tag )->bytes();
}


/*-------------------------------------------------
 image_get_feature
 -------------------------------------------------*/

const char *device_image_interface::get_feature(const char *feature_name)
{
	return (m_software_part_ptr == NULL) ? NULL : m_software_part_ptr->feature(feature_name);
=======
const std::string &device_image_interface::working_directory()
{
	// check to see if we've never initialized the working directory
	if (m_working_directory.empty())
		setup_working_directory();

	return m_working_directory;
}


//-------------------------------------------------
//  software_entry - return a pointer to the
//  software_info structure from the softlist
//-------------------------------------------------

const software_info *device_image_interface::software_entry() const
{
	return (m_software_part_ptr == nullptr) ? nullptr : &m_software_part_ptr->info();
}


//-------------------------------------------------
//  get_software_region
//-------------------------------------------------

u8 *device_image_interface::get_software_region(const char *tag)
{
	if (!loaded_through_softlist())
		return nullptr;

	std::string full_tag = util::string_format("%s:%s", device().tag(), tag);
	memory_region *region = device().machine().root_device().memregion(full_tag.c_str());
	return region != nullptr ? region->base() : nullptr;
}


//-------------------------------------------------
//  image_get_software_region_length
//-------------------------------------------------

u32 device_image_interface::get_software_region_length(const char *tag)
{
	std::string full_tag = util::string_format("%s:%s", device().tag(), tag);
	memory_region *region = device().machine().root_device().memregion(full_tag.c_str());
	return region != nullptr ? region->bytes() : 0;
}


//-------------------------------------------------
//  image_get_feature
//-------------------------------------------------

const char *device_image_interface::get_feature(const char *feature_name)
{
	return (m_software_part_ptr == nullptr) ? nullptr : m_software_part_ptr->feature(feature_name);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  load_software_region -
//-------------------------------------------------

<<<<<<< HEAD
bool device_image_interface::load_software_region(const char *tag, optional_shared_ptr<UINT8> &ptr)
=======
bool device_image_interface::load_software_region(const char *tag, optional_shared_ptr<u8> &ptr)
>>>>>>> upstream/master
{
	size_t size = get_software_region_length(tag);

	if (size)
	{
		ptr.allocate(size);

		memcpy(ptr, get_software_region(tag), size);
	}

	return size > 0;
}

<<<<<<< HEAD
/****************************************************************************
  Hash info loading

  If the hash is not checked and the relevant info not loaded, force that info
  to be loaded
****************************************************************************/

void device_image_interface::run_hash(void (*partialhash)(hash_collection &, const unsigned char *, unsigned long, const char *),
	hash_collection &hashes, const char *types)
{
	UINT32 size;
	dynamic_buffer buf;

	hashes.reset();
	size = (UINT32) length();

	buf.resize(size);
	memset(&buf[0], 0, size);

	/* read the file */
	fseek(0, SEEK_SET);
	fread(&buf[0], size);

	if (partialhash)
		partialhash(hashes, &buf[0], size, types);
	else
		hashes.compute(&buf[0], size, types);

	/* cleanup */
	fseek(0, SEEK_SET);
=======

// ****************************************************************************
// Hash info loading
//
// If the hash is not checked and the relevant info not loaded, force that info
// to be loaded
// ****************************************************************************

bool device_image_interface::run_hash(util::core_file &file, u32 skip_bytes, util::hash_collection &hashes, const char *types)
{
	// reset the hash; we want to override existing data
	hashes.reset();

	// figure out the size, and "cap" the skip bytes
	u64 size = file.size();
	skip_bytes = (u32) std::min((u64) skip_bytes, size);

	// seek to the beginning
	file.seek(skip_bytes, SEEK_SET);
	u64 position = skip_bytes;

	// keep on reading hashes
	hashes.begin(types);
	while (position < size)
	{
		uint8_t buffer[8192];

		// read bytes
		const u32 count = (u32) std::min(size - position, (u64) sizeof(buffer));
		const u32 actual_count = file.read(buffer, count);
		if (actual_count == 0)
			return false;
		position += actual_count;

		// and compute the hashes
		hashes.buffer(buffer, actual_count);
	}
	hashes.end();

	// cleanup
	file.seek(0, SEEK_SET);
	return true;
>>>>>>> upstream/master
}



<<<<<<< HEAD
void device_image_interface::image_checkhash()
{
	device_image_partialhash_func partialhash;

	/* only calculate CRC if it hasn't been calculated, and the open_mode is read only */
	UINT32 crcval;
	if (!m_hash.crc(crcval) && m_readonly && !m_created)
	{
		/* do not cause a linear read of 600 megs please */
		/* TODO: use SHA1 in the CHD header as the hash */
		if (image_type() == IO_CDROM)
			return;

		/* Skip calculating the hash when we have an image mounted through a software list */
		if ( m_software_info_ptr )
			return;

		/* retrieve the partial hash func */
		partialhash = get_partial_hash();

		run_hash(partialhash, m_hash, hash_collection::HASH_TYPES_ALL);
	}
	return;
}

UINT32 device_image_interface::crc()
{
	UINT32 crc = 0;
=======
bool device_image_interface::image_checkhash()
{
	// only calculate CRC if it hasn't been calculated, and the open_mode is read only
	u32 crcval;
	if (!m_hash.crc(crcval) && is_readonly() && !m_created)
	{
		// do not cause a linear read of 600 megs please
		// TODO: use SHA1 in the CHD header as the hash
		if (image_type() == IO_CDROM)
			return true;

		// Skip calculating the hash when we have an image mounted through a software list
		if (loaded_through_softlist())
			return true;

		// run the hash
		if (!run_hash(*m_file, unhashed_header_length(), m_hash, util::hash_collection::HASH_TYPES_ALL))
			return false;
	}
	return true;
}


util::hash_collection device_image_interface::calculate_hash_on_file(util::core_file &file) const
{
	// calculate the hash
	util::hash_collection hash;
	if (!run_hash(file, unhashed_header_length(), hash, util::hash_collection::HASH_TYPES_ALL))
		hash.reset();
	return hash;
}


u32 device_image_interface::crc()
{
	u32 crc = 0;
>>>>>>> upstream/master

	image_checkhash();
	m_hash.crc(crc);

	return crc;
}

<<<<<<< HEAD
/****************************************************************************
  Battery functions

  These functions provide transparent access to battery-backed RAM on an
  image; typically for cartridges.
****************************************************************************/


/*-------------------------------------------------
    battery_load - retrieves the battery
    backed RAM for an image. The file name is
    created from the machine driver name and the
    image name.
-------------------------------------------------*/
void device_image_interface::battery_load(void *buffer, int length, int fill)
{
	std::string fname = std::string(device().machine().system().name).append(PATH_SEPARATOR).append(m_basename_noext.c_str()).append(".nv");
	image_battery_load_by_name(device().machine().options(), fname.c_str(), buffer, length, fill);
=======

//-------------------------------------------------
//  support_command_line_image_creation - do we
//  want to support image creation from the front
//  end command line?
//-------------------------------------------------

bool device_image_interface::support_command_line_image_creation() const
{
	bool result;
	switch (image_type())
	{
	case IO_PRINTER:
	case IO_SERIAL:
	case IO_PARALLEL:
		// going by the assumption that these device image types should support this
		// behavior; ideally we'd get rid of IO_* and just push this to the specific
		// devices
		result = true;
		break;
	default:
		result = false;
		break;
	}
	return result;
}


// ****************************************************************************
// Battery functions
//
// These functions provide transparent access to battery-backed RAM on an
// image; typically for cartridges.
// ****************************************************************************


//-------------------------------------------------
//  battery_load - retrieves the battery
//  backed RAM for an image. The file name is
//  created from the machine driver name and the
//  image name.
//-------------------------------------------------

void device_image_interface::battery_load(void *buffer, int length, int fill)
{
	assert_always(buffer && (length > 0), "Must specify sensical buffer/length");

	osd_file::error filerr;
	int bytes_read = 0;
	std::string fname = std::string(device().machine().system().name).append(PATH_SEPARATOR).append(m_basename_noext.c_str()).append(".nv");

	/* try to open the battery file and read it in, if possible */
	emu_file file(device().machine().options().nvram_directory(), OPEN_FLAG_READ);
	filerr = file.open(fname);
	if (filerr == osd_file::error::NONE)
		bytes_read = file.read(buffer, length);

	// fill remaining bytes (if necessary)
	memset(((char *)buffer) + bytes_read, fill, length - bytes_read);
>>>>>>> upstream/master
}

void device_image_interface::battery_load(void *buffer, int length, void *def_buffer)
{
<<<<<<< HEAD
	std::string fname = std::string(device().machine().system().name).append(PATH_SEPARATOR).append(m_basename_noext.c_str()).append(".nv");
	image_battery_load_by_name(device().machine().options(), fname.c_str(), buffer, length, def_buffer);
}

/*-------------------------------------------------
    battery_save - stores the battery
    backed RAM for an image. The file name is
    created from the machine driver name and the
    image name.
-------------------------------------------------*/
void device_image_interface::battery_save(const void *buffer, int length)
{
	std::string fname = std::string(device().machine().system().name).append(PATH_SEPARATOR).append(m_basename_noext.c_str()).append(".nv");

	image_battery_save_by_name(device().machine().options(), fname.c_str(), buffer, length);
}

=======
	assert_always(buffer && (length > 0), "Must specify sensical buffer/length");

	osd_file::error filerr;
	int bytes_read = 0;
	std::string fname = std::string(device().machine().system().name).append(PATH_SEPARATOR).append(m_basename_noext.c_str()).append(".nv");

	// try to open the battery file and read it in, if possible
	emu_file file(device().machine().options().nvram_directory(), OPEN_FLAG_READ);
	filerr = file.open(fname);
	if (filerr == osd_file::error::NONE)
		bytes_read = file.read(buffer, length);

	// if no file was present, copy the default battery
	if (bytes_read == 0 && def_buffer)
		memcpy((char *)buffer, (char *)def_buffer, length);
}


//-------------------------------------------------
//  battery_save - stores the battery
//  backed RAM for an image. The file name is
//  created from the machine driver name and the
//  image name.
//-------------------------------------------------

void device_image_interface::battery_save(const void *buffer, int length)
{
	assert_always(buffer && (length > 0), "Must specify sensical buffer/length");
	std::string fname = std::string(device().machine().system().name).append(PATH_SEPARATOR).append(m_basename_noext.c_str()).append(".nv");

	// try to open the battery file and write it out, if possible
	emu_file file(device().machine().options().nvram_directory(), OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS);
	osd_file::error filerr = file.open(fname);
	if (filerr == osd_file::error::NONE)
		file.write(buffer, length);
}


>>>>>>> upstream/master
//-------------------------------------------------
//  uses_file_extension - update configuration
//  based on completed device setup
//-------------------------------------------------

bool device_image_interface::uses_file_extension(const char *file_extension) const
{
<<<<<<< HEAD
	bool result = FALSE;
=======
	bool result = false;
>>>>>>> upstream/master

	if (file_extension[0] == '.')
		file_extension++;

	/* find the extensions */
	std::string extensions(file_extensions());
	char *ext = strtok((char*)extensions.c_str(),",");
<<<<<<< HEAD
	while (ext != NULL)
	{
		if (!core_stricmp(ext, file_extension))
		{
			result = TRUE;
			break;
		}
		ext = strtok (NULL, ",");
=======
	while (ext != nullptr)
	{
		if (!core_stricmp(ext, file_extension))
		{
			result = true;
			break;
		}
		ext = strtok (nullptr, ",");
>>>>>>> upstream/master
	}
	return result;
}

<<<<<<< HEAD
/****************************************************************************
    IMAGE LOADING
****************************************************************************/

/*-------------------------------------------------
    is_loaded - quick check to determine whether an
    image is loaded
-------------------------------------------------*/

bool device_image_interface::is_loaded()
{
	return (m_file != NULL);
}

/*-------------------------------------------------
    load_image_by_path - loads an image with a
    specific path
-------------------------------------------------*/

image_error_t device_image_interface::load_image_by_path(UINT32 open_flags, const char *path)
{
	file_error filerr;
	image_error_t err;
	std::string revised_path;

	/* attempt to read the file */
	filerr = zippath_fopen(path, open_flags, m_file, revised_path);

	/* did the open succeed? */
	switch(filerr)
	{
		case FILERR_NONE:
			/* success! */
			m_readonly = (open_flags & OPEN_FLAG_WRITE) ? 0 : 1;
			m_created = (open_flags & OPEN_FLAG_CREATE) ? 1 : 0;
			err = IMAGE_ERROR_SUCCESS;
			break;

		case FILERR_NOT_FOUND:
		case FILERR_ACCESS_DENIED:
			/* file not found (or otherwise cannot open); continue */
			err = IMAGE_ERROR_FILENOTFOUND;
			break;

		case FILERR_OUT_OF_MEMORY:
			/* out of memory */
			err = IMAGE_ERROR_OUTOFMEMORY;
			break;

		case FILERR_ALREADY_OPEN:
			/* this shouldn't happen */
			err = IMAGE_ERROR_ALREADYOPEN;
			break;

		case FILERR_FAILURE:
		case FILERR_TOO_MANY_FILES:
		case FILERR_INVALID_DATA:
		default:
			/* other errors */
			err = IMAGE_ERROR_INTERNAL;
			break;
	}

	/* if successful, set the file name */
	if (filerr == FILERR_NONE)
		set_image_filename(revised_path.c_str());

	return err;
}

int device_image_interface::reopen_for_write(const char *path)
{
	if(m_file)
		core_fclose(m_file);

	file_error filerr;
	image_error_t err;
	std::string revised_path;

	/* attempt to open the file for writing*/
	filerr = zippath_fopen(path, OPEN_FLAG_READ|OPEN_FLAG_WRITE|OPEN_FLAG_CREATE, m_file, revised_path);

	/* did the open succeed? */
	switch(filerr)
	{
		case FILERR_NONE:
			/* success! */
			m_readonly = 0;
			m_created = 1;
			err = IMAGE_ERROR_SUCCESS;
			break;

		case FILERR_NOT_FOUND:
		case FILERR_ACCESS_DENIED:
			/* file not found (or otherwise cannot open); continue */
			err = IMAGE_ERROR_FILENOTFOUND;
			break;

		case FILERR_OUT_OF_MEMORY:
			/* out of memory */
			err = IMAGE_ERROR_OUTOFMEMORY;
			break;

		case FILERR_ALREADY_OPEN:
			/* this shouldn't happen */
			err = IMAGE_ERROR_ALREADYOPEN;
			break;

		case FILERR_FAILURE:
		case FILERR_TOO_MANY_FILES:
		case FILERR_INVALID_DATA:
		default:
			/* other errors */
			err = IMAGE_ERROR_INTERNAL;
			break;
	}

	/* if successful, set the file name */
	if (filerr == FILERR_NONE)
		set_image_filename(revised_path.c_str());

	return err;
}

/*-------------------------------------------------
    determine_open_plan - determines which open
    flags to use, and in what order
-------------------------------------------------*/

void device_image_interface::determine_open_plan(int is_create, UINT32 *open_plan)
{
	int i = 0;

	/* emit flags */
	if (!is_create && is_readable() && is_writeable())
		open_plan[i++] = OPEN_FLAG_READ | OPEN_FLAG_WRITE;
	if (!is_create && !is_readable() && is_writeable())
		open_plan[i++] = OPEN_FLAG_WRITE;
	if (!is_create && is_readable())
		open_plan[i++] = OPEN_FLAG_READ;
	if (is_writeable() && is_creatable())
		open_plan[i++] = OPEN_FLAG_READ | OPEN_FLAG_WRITE | OPEN_FLAG_CREATE;
	open_plan[i] = 0;
}

/*-------------------------------------------------
    dump_wrong_and_correct_checksums - dump an
    error message containing the wrong and the
    correct checksums for a given software item
-------------------------------------------------*/

static void dump_wrong_and_correct_checksums(const hash_collection &hashes, const hash_collection &acthashes)
{
	std::string tempstr;
	osd_printf_error("    EXPECTED: %s\n", hashes.macro_string(tempstr));
	osd_printf_error("       FOUND: %s\n", acthashes.macro_string(tempstr));
}

/*-------------------------------------------------
    verify_length_and_hash - verify the length
    and hash signatures of a file
-------------------------------------------------*/

static int verify_length_and_hash(emu_file *file, const char *name, UINT32 explength, const hash_collection &hashes)
{
	int retVal = 0;
	if (file==NULL) return 0;

	/* verify length */
	UINT32 actlength = file->size();
=======

// ***************************************************************************
// IMAGE LOADING
// ***************************************************************************

//-------------------------------------------------
//  is_loaded - quick check to determine whether an
//  image is loaded
//-------------------------------------------------

bool device_image_interface::is_loaded()
{
	return (m_file != nullptr);
}

//-------------------------------------------------
//  image_error_from_file_error - converts an image
//  error to a file error
//-------------------------------------------------

image_error_t device_image_interface::image_error_from_file_error(osd_file::error filerr)
{
	switch (filerr)
	{
	case osd_file::error::NONE:
		return IMAGE_ERROR_SUCCESS;

	case osd_file::error::NOT_FOUND:
	case osd_file::error::ACCESS_DENIED:
		// file not found (or otherwise cannot open)
		return IMAGE_ERROR_FILENOTFOUND;

	case osd_file::error::OUT_OF_MEMORY:
		// out of memory
		return IMAGE_ERROR_OUTOFMEMORY;

	case osd_file::error::ALREADY_OPEN:
		// this shouldn't happen
		return IMAGE_ERROR_ALREADYOPEN;

	case osd_file::error::FAILURE:
	case osd_file::error::TOO_MANY_FILES:
	case osd_file::error::INVALID_DATA:
	default:
		// other errors
		return IMAGE_ERROR_INTERNAL;
	}
}


//-------------------------------------------------
//  load_image_by_path - loads an image with a
//  specific path
//-------------------------------------------------

image_error_t device_image_interface::load_image_by_path(u32 open_flags, const std::string &path)
{
	std::string revised_path;

	// attempt to read the file
	auto const filerr = util::zippath_fopen(path, open_flags, m_file, revised_path);
	if (filerr != osd_file::error::NONE)
		return image_error_from_file_error(filerr);

	m_readonly = (open_flags & OPEN_FLAG_WRITE) ? 0 : 1;
	m_created = (open_flags & OPEN_FLAG_CREATE) ? 1 : 0;
	set_image_filename(revised_path);
	return IMAGE_ERROR_SUCCESS;
}


//-------------------------------------------------
//  reopen_for_write
//-------------------------------------------------

int device_image_interface::reopen_for_write(const std::string &path)
{
	m_file.reset();

	std::string revised_path;

	// attempt to open the file for writing
	auto const filerr = util::zippath_fopen(path, OPEN_FLAG_READ|OPEN_FLAG_WRITE|OPEN_FLAG_CREATE, m_file, revised_path);
	if (filerr != osd_file::error::NONE)
		return image_error_from_file_error(filerr);

	// success!
	m_readonly = 0;
	m_created = 1;
	set_image_filename(revised_path);

	return IMAGE_ERROR_SUCCESS;
}


//-------------------------------------------------
//  determine_open_plan - determines which open
//  flags to use, and in what order
//-------------------------------------------------

std::vector<u32> device_image_interface::determine_open_plan(bool is_create)
{
	std::vector<u32> open_plan;

	// emit flags into a vector
	if (!is_create && is_readable() && is_writeable())
		open_plan.push_back(OPEN_FLAG_READ | OPEN_FLAG_WRITE);
	if (!is_create && !is_readable() && is_writeable())
		open_plan.push_back(OPEN_FLAG_WRITE);
	if (!is_create && is_readable())
		open_plan.push_back(OPEN_FLAG_READ);
	if (is_create && is_writeable() && is_creatable())
		open_plan.push_back(OPEN_FLAG_READ | OPEN_FLAG_WRITE | OPEN_FLAG_CREATE);

	return open_plan;
}


//-------------------------------------------------
//  dump_wrong_and_correct_checksums - dump an
//  error message containing the wrong and the
//  correct checksums for a given software item
//-------------------------------------------------

static void dump_wrong_and_correct_checksums(const util::hash_collection &hashes, const util::hash_collection &acthashes)
{
	osd_printf_error("    EXPECTED: %s\n", hashes.macro_string().c_str());
	osd_printf_error("       FOUND: %s\n", acthashes.macro_string().c_str());
}


//-------------------------------------------------
//  verify_length_and_hash - verify the length
//  and hash signatures of a file
//-------------------------------------------------

static int verify_length_and_hash(emu_file *file, const char *name, u32 explength, const util::hash_collection &hashes)
{
	int retVal = 0;
	if (file==nullptr) return 0;

	// verify length
	u32 actlength = file->size();
>>>>>>> upstream/master
	if (explength != actlength)
	{
		osd_printf_error("%s WRONG LENGTH (expected: %d found: %d)\n", name, explength, actlength);
		retVal++;
	}

<<<<<<< HEAD
	/* If there is no good dump known, write it */
	std::string tempstr;
	hash_collection &acthashes = file->hashes(hashes.hash_types(tempstr));
	if (hashes.flag(hash_collection::FLAG_NO_DUMP))
	{
		osd_printf_error("%s NO GOOD DUMP KNOWN\n", name);
	}
	/* verify checksums */
	else if (hashes != acthashes)
	{
		/* otherwise, it's just bad */
=======
	// If there is no good dump known, write it
	util::hash_collection &acthashes = file->hashes(hashes.hash_types().c_str());
	if (hashes.flag(util::hash_collection::FLAG_NO_DUMP))
	{
		osd_printf_error("%s NO GOOD DUMP KNOWN\n", name);
	}
	// verify checksums
	else if (hashes != acthashes)
	{
		// otherwise, it's just bad
>>>>>>> upstream/master
		osd_printf_error("%s WRONG CHECKSUMS:\n", name);
		dump_wrong_and_correct_checksums(hashes, acthashes);
		retVal++;
	}
<<<<<<< HEAD
	/* If it matches, but it is actually a bad dump, write it */
	else if (hashes.flag(hash_collection::FLAG_BAD_DUMP))
=======
	// If it matches, but it is actually a bad dump, write it
	else if (hashes.flag(util::hash_collection::FLAG_BAD_DUMP))
>>>>>>> upstream/master
	{
		osd_printf_error("%s NEEDS REDUMP\n",name);
	}
	return retVal;
}

<<<<<<< HEAD
/*-------------------------------------------------
    load_software - software image loading
-------------------------------------------------*/
=======

//-------------------------------------------------
//  load_software - software image loading
//-------------------------------------------------
>>>>>>> upstream/master

bool device_image_interface::load_software(software_list_device &swlist, const char *swname, const rom_entry *start)
{
	std::string locationtag, breakstr("%");
	const rom_entry *region;
<<<<<<< HEAD
	bool retVal = FALSE;
	int warningcount = 0;
	for (region = start; region != NULL; region = rom_next_region(region))
	{
		/* loop until we hit the end of this region */
		const rom_entry *romp = region + 1;
		while (!ROMENTRY_ISREGIONEND(romp))
		{
			/* handle files */
			if (ROMENTRY_ISFILE(romp))
			{
				file_error filerr = FILERR_NOT_FOUND;

				UINT32 crc = 0;
				bool has_crc = hash_collection(ROM_GETHASHDATA(romp)).crc(crc);

				software_info *swinfo = swlist.find(swname);
				if (swinfo == NULL)
					return false;

				UINT32 supported = swinfo->supported();
				if (supported == SOFTWARE_SUPPORTED_PARTIAL)
					osd_printf_error("WARNING: support for software %s (in list %s) is only partial\n", swname, swlist.list_name());
				if (supported == SOFTWARE_SUPPORTED_NO)
					osd_printf_error("WARNING: support for software %s (in list %s) is only preliminary\n", swname, swlist.list_name());
=======
	bool retVal = false;
	int warningcount = 0;
	for (region = start; region != nullptr; region = rom_next_region(region))
	{
		// loop until we hit the end of this region
		const rom_entry *romp = region + 1;
		while (!ROMENTRY_ISREGIONEND(romp))
		{
			// handle files
			if (ROMENTRY_ISFILE(romp))
			{
				osd_file::error filerr = osd_file::error::NOT_FOUND;

				u32 crc = 0;
				bool has_crc = util::hash_collection(ROM_GETHASHDATA(romp)).crc(crc);

				const software_info *swinfo = swlist.find(swname);
				if (swinfo == nullptr)
					return false;

				u32 supported = swinfo->supported();
				if (supported == SOFTWARE_SUPPORTED_PARTIAL)
					osd_printf_error("WARNING: support for software %s (in list %s) is only partial\n", swname, swlist.list_name().c_str());
				if (supported == SOFTWARE_SUPPORTED_NO)
					osd_printf_error("WARNING: support for software %s (in list %s) is only preliminary\n", swname, swlist.list_name().c_str());
>>>>>>> upstream/master

				// attempt reading up the chain through the parents and create a locationtag std::string in the format
				// " swlist % clonename % parentname "
				// below, we have the code to split the elements and to create paths to load from

<<<<<<< HEAD
				while (swinfo != NULL)
				{
					locationtag.append(swinfo->shortname()).append(breakstr);
					const char *parentname = swinfo->parentname();
					swinfo = (parentname != NULL) ? swlist.find(parentname) : NULL;
=======
				while (swinfo != nullptr)
				{
					locationtag.append(swinfo->shortname()).append(breakstr);
					swinfo = !swinfo->parentname().empty() ? swlist.find(swinfo->parentname().c_str()) : nullptr;
>>>>>>> upstream/master
				}
				// strip the final '%'
				locationtag.erase(locationtag.length() - 1, 1);


				// check if locationtag actually contains two locations separated by '%'
				// (i.e. check if we are dealing with a clone in softwarelist)
				std::string tag2, tag3, tag4(locationtag), tag5;
				int separator = tag4.find_first_of('%');
				if (separator != -1)
				{
					// we are loading a clone through softlists, split the setname from the parentname
					tag5.assign(tag4.substr(separator + 1, tag4.length() - separator + 1));
					tag4.erase(separator, tag4.length() - separator);
				}

				// prepare locations where we have to load from: list/parentname & list/clonename
				std::string tag1(swlist.list_name());
				tag1.append(PATH_SEPARATOR);
				tag2.assign(tag1.append(tag4));
				tag1.assign(swlist.list_name());
				tag1.append(PATH_SEPARATOR);
				tag3.assign(tag1.append(tag5));

				if (tag5.find_first_of('%') != -1)
					fatalerror("We do not support clones of clones!\n");

				// try to load from the available location(s):
				// - if we are not using lists, we have regiontag only;
				// - if we are using lists, we have: list/clonename, list/parentname, clonename, parentname
				// try to load from list/setname
<<<<<<< HEAD
				if ((m_mame_file == NULL) && (tag2.c_str() != NULL))
					filerr = common_process_file(device().machine().options(), tag2.c_str(), has_crc, crc, romp, &m_mame_file);
				// try to load from list/parentname
				if ((m_mame_file == NULL) && (tag3.c_str() != NULL))
					filerr = common_process_file(device().machine().options(), tag3.c_str(), has_crc, crc, romp, &m_mame_file);
				// try to load from setname
				if ((m_mame_file == NULL) && (tag4.c_str() != NULL))
					filerr = common_process_file(device().machine().options(), tag4.c_str(), has_crc, crc, romp, &m_mame_file);
				// try to load from parentname
				if ((m_mame_file == NULL) && (tag5.c_str() != NULL))
					filerr = common_process_file(device().machine().options(), tag5.c_str(), has_crc, crc, romp, &m_mame_file);

				warningcount += verify_length_and_hash(m_mame_file,ROM_GETNAME(romp),ROM_GETLENGTH(romp),hash_collection(ROM_GETHASHDATA(romp)));

				if (filerr == FILERR_NONE)
				{
					m_file = *m_mame_file;
					retVal = TRUE;
				}
=======
				if ((m_mame_file == nullptr) && (tag2.c_str() != nullptr))
					m_mame_file = common_process_file(device().machine().options(), tag2.c_str(), has_crc, crc, romp, filerr);
				// try to load from list/parentname
				if ((m_mame_file == nullptr) && (tag3.c_str() != nullptr))
					m_mame_file = common_process_file(device().machine().options(), tag3.c_str(), has_crc, crc, romp, filerr);
				// try to load from setname
				if ((m_mame_file == nullptr) && (tag4.c_str() != nullptr))
					m_mame_file = common_process_file(device().machine().options(), tag4.c_str(), has_crc, crc, romp, filerr);
				// try to load from parentname
				if ((m_mame_file == nullptr) && (tag5.c_str() != nullptr))
					m_mame_file = common_process_file(device().machine().options(), tag5.c_str(), has_crc, crc, romp, filerr);

				warningcount += verify_length_and_hash(m_mame_file.get(),ROM_GETNAME(romp),ROM_GETLENGTH(romp), util::hash_collection(ROM_GETHASHDATA(romp)));

				if (filerr == osd_file::error::NONE)
					filerr = util::core_file::open_proxy(*m_mame_file, m_file);
				if (filerr == osd_file::error::NONE)
					retVal = true;
>>>>>>> upstream/master

				break; // load first item for start
			}
			romp++; /* something else; skip */
		}
	}
	if (warningcount > 0)
	{
		osd_printf_error("WARNING: the software item might not run correctly.\n");
	}
	return retVal;
}

<<<<<<< HEAD
/*-------------------------------------------------
    load_internal - core image loading
-------------------------------------------------*/

bool device_image_interface::load_internal(const char *path, bool is_create, int create_format, option_resolution *create_args, bool just_load)
{
	UINT32 open_plan[4];
	int i;
	bool softload = FALSE;
	m_from_swlist = FALSE;

	// if the path contains no period, we are using softlists, so we won't create an image
	std::string pathstr(path);
	bool filename_has_period = (pathstr.find_last_of('.') != -1) ? TRUE : FALSE;

	/* first unload the image */
	unload();

	/* clear any possible error messages */
	clear_error();

	/* we are now loading */
	m_is_loading = TRUE;

	/* record the filename */
	m_err = set_image_filename(path);

	if (m_err)
		goto done;

	if (core_opens_image_file())
	{
		/* Check if there's a software list defined for this device and use that if we're not creating an image */
		if (!filename_has_period && !just_load)
		{
			softload = load_software_part(path, m_software_part_ptr);
			if (softload)
			{
				m_software_info_ptr = &m_software_part_ptr->info();
				m_software_list_name.assign(m_software_info_ptr->list().list_name());
				m_full_software_name.assign(m_software_part_ptr->info().shortname());

				// if we had launched from softlist with a specified part, e.g. "shortname:part"
				// we would have recorded the wrong name, so record it again based on software_info
				if (m_software_info_ptr && !m_full_software_name.empty())
					m_err = set_image_filename(m_full_software_name.c_str());

				// check if image should be read-only
				const char *read_only = get_feature("read_only");
				if (read_only && !strcmp(read_only, "true")) {
					make_readonly();
				}

				m_from_swlist = TRUE;
			}
		}

		if (is_create || filename_has_period)
		{
			/* determine open plan */
			determine_open_plan(is_create, open_plan);

			/* attempt to open the file in various ways */
			for (i = 0; !m_file && open_plan[i]; i++)
			{
				/* open the file */
				m_err = load_image_by_path(open_plan[i], path);
				if (m_err && (m_err != IMAGE_ERROR_FILENOTFOUND))
					goto done;
			}
		}

		/* Copy some image information when we have been loaded through a software list */
		if ( m_software_info_ptr )
		{
			// sanitize
			if (m_software_info_ptr->longname() == NULL || m_software_info_ptr->publisher() == NULL || m_software_info_ptr->year() == NULL)
				fatalerror("Each entry in an XML list must have all of the following fields: description, publisher, year!\n");

			// store
			m_longname = m_software_info_ptr->longname();
			m_manufacturer = m_software_info_ptr->publisher();
			m_year = m_software_info_ptr->year();
			//m_playable = m_software_info_ptr->supported();
		}

		/* did we fail to find the file? */
		if (!is_loaded() && !softload)
=======

//-------------------------------------------------
//  load_internal - core image loading
//-------------------------------------------------

image_init_result device_image_interface::load_internal(const std::string &path, bool is_create, int create_format, util::option_resolution *create_args)
{
	// first unload the image
	unload();

	// clear any possible error messages
	clear_error();

	// we are now loading
	m_is_loading = true;

	// record the filename
	set_image_filename(path);

	if (core_opens_image_file())
	{
		// determine open plan
		std::vector<u32> open_plan = determine_open_plan(is_create);

		// attempt to open the file in various ways
		for (auto iter = open_plan.cbegin(); !m_file && iter != open_plan.cend(); iter++)
		{
			// open the file
			m_err = load_image_by_path(*iter, path);
			if (m_err && (m_err != IMAGE_ERROR_FILENOTFOUND))
				goto done;
		}

		// did we fail to find the file?
		if (!is_loaded())
>>>>>>> upstream/master
		{
			m_err = IMAGE_ERROR_FILENOTFOUND;
			goto done;
		}
	}

<<<<<<< HEAD
	/* call device load or create */
	m_create_format = create_format;
	m_create_args = create_args;

	if (m_init_phase==FALSE) {
		m_err = (image_error_t)finish_load();
		if (m_err)
			goto done;
	}
	/* success! */

done:
	if (just_load) {
		if(m_err) clear();
		return m_err ? IMAGE_INIT_FAIL : IMAGE_INIT_PASS;
	}
	if (m_err!=0) {
		if (!m_init_phase)
		{
			if (device().machine().phase() == MACHINE_PHASE_RUNNING)
				device().popmessage("Error: Unable to %s image '%s': %s", is_create ? "create" : "load", path, error());
			else
				osd_printf_error("Error: Unable to %s image '%s': %s\n", is_create ? "create" : "load", path, error());
		}
		clear();
	}
	else {
		/* do we need to reset the CPU? only schedule it if load/create is successful */
		if (device().machine().time() > attotime::zero && is_reset_on_load())
			device().machine().schedule_hard_reset();
		else
		{
			if (!m_init_phase)
			{
				if (device().machine().phase() == MACHINE_PHASE_RUNNING)
					device().popmessage("Image '%s' was successfully %s.", path, is_create ? "created" : "loaded");
				else
					osd_printf_info("Image '%s' was successfully %s.\n", path, is_create ? "created" : "loaded");
			}
		}
	}
	return m_err ? IMAGE_INIT_FAIL : IMAGE_INIT_PASS;
}



/*-------------------------------------------------
    load - load an image into MESS
-------------------------------------------------*/

bool device_image_interface::load(const char *path)
{
	return load_internal(path, FALSE, 0, NULL, FALSE);
}

/*-------------------------------------------------
    open_image_file - opening plain image file
-------------------------------------------------*/

bool device_image_interface::open_image_file(emu_options &options)
{
	const char* path = options.value(instance_name());
	if (*path != 0)
	{
		set_init_phase();
		if (load_internal(path, FALSE, 0, NULL, TRUE)==IMAGE_INIT_PASS)
		{
			if (software_entry()==NULL) return true;
		}
	}
	return false;
}

/*-------------------------------------------------
    image_finish_load - special call - only use
    from core
-------------------------------------------------*/

bool device_image_interface::finish_load()
{
	bool err = IMAGE_INIT_PASS;

	if (m_is_loading)
	{
		image_checkhash();

		if (has_been_created())
		{
			err = call_create(m_create_format, m_create_args);
			if (err)
			{
				if (!m_err)
					m_err = IMAGE_ERROR_UNSPECIFIED;
			}
		}
		else
		{
			/* using device load */
			err = call_load();
			if (err)
			{
				if (!m_err)
					m_err = IMAGE_ERROR_UNSPECIFIED;
			}
		}
	}
	m_is_loading = FALSE;
	m_create_format = 0;
	m_create_args = NULL;
	m_init_phase = FALSE;
	return err;
}

/*-------------------------------------------------
    create - create a image
-------------------------------------------------*/

bool device_image_interface::create(const char *path, const image_device_format *create_format, option_resolution *create_args)
{
	int format_index = (create_format != NULL) ? m_formatlist.indexof(*create_format) : 0;
	return load_internal(path, TRUE, format_index, create_args, FALSE);
}


/*-------------------------------------------------
    clear - clear all internal data pertaining
    to an image
-------------------------------------------------*/

void device_image_interface::clear()
{
	if (m_mame_file)
	{
		global_free(m_mame_file);
		m_mame_file = NULL;
		m_file = NULL;
	} else {
		if (m_file)
		{
			core_fclose(m_file);
			m_file = NULL;
		}
	}
=======
	// call device load or create
	m_create_format = create_format;
	m_create_args = create_args;

	if (init_phase()==false) {
		m_err = (finish_load() == image_init_result::PASS) ? IMAGE_ERROR_SUCCESS : IMAGE_ERROR_INTERNAL;
		if (m_err)
			goto done;
	}
	// success!

done:
	if (m_err!=0) {
		if (!init_phase())
		{
			if (device().machine().phase() == machine_phase::RUNNING)
				device().popmessage("Error: Unable to %s image '%s': %s", is_create ? "create" : "load", path, error());
			else
				osd_printf_error("Error: Unable to %s image '%s': %s\n", is_create ? "create" : "load", path.c_str(), error());
		}
		clear();
	}
	return m_err ? image_init_result::FAIL : image_init_result::PASS;
}


//-------------------------------------------------
//  load - load an image into MAME
//-------------------------------------------------

image_init_result device_image_interface::load(const std::string &path)
{
	// is this a reset on load item?
	if (is_reset_on_load() && !init_phase())
	{
		reset_and_load(path);
		return image_init_result::PASS;
	}

	return load_internal(path, false, 0, nullptr);
}


//-------------------------------------------------
//  load_software - loads a softlist item by name
//-------------------------------------------------

image_init_result device_image_interface::load_software(const std::string &software_identifier)
{
	// Is this a software part that forces a reset and we're at runtime?  If so, get this loaded through reset_and_load
	if (is_reset_on_load() && !init_phase())
	{
		reset_and_load(software_identifier);
		return image_init_result::PASS;
	}

	// Prepare to load
	unload();
	clear_error();
	m_is_loading = true;

	// Check if there's a software list defined for this device and use that if we're not creating an image
	bool softload = load_software_part(software_identifier);
	if (!softload)
	{
		m_is_loading = false;
		return image_init_result::FAIL;
	}

	// set up softlist stuff
	m_full_software_name = m_software_part_ptr->info().shortname();

	// specify image name with softlist-derived names
	m_image_name = m_full_software_name;
	m_basename = m_full_software_name;
	m_basename_noext = m_full_software_name;
	m_filetype = use_software_list_file_extension_for_filetype() && m_mame_file != nullptr
		? core_filename_extract_extension(m_mame_file->filename(), true)
		: "";

	// Copy some image information when we have been loaded through a software list
	software_info &swinfo = m_software_part_ptr->info();

	// sanitize
	if (swinfo.longname().empty() || swinfo.publisher().empty() || swinfo.year().empty())
		fatalerror("Each entry in an XML list must have all of the following fields: description, publisher, year!\n");

	// store
	m_longname = swinfo.longname();
	m_manufacturer = swinfo.publisher();
	m_year = swinfo.year();

	// set file type
	std::string filename = (m_mame_file != nullptr) && (m_mame_file->filename() != nullptr)
			? m_mame_file->filename()
			: "";
	m_filetype = core_filename_extract_extension(filename, true);

	// call finish_load if necessary
	if (init_phase() == false && (finish_load() != image_init_result::PASS))
		return image_init_result::FAIL;

	return image_init_result::PASS;
}


//-------------------------------------------------
//  image_finish_load - special call - only use
//  from core
//-------------------------------------------------

image_init_result device_image_interface::finish_load()
{
	image_init_result err = image_init_result::PASS;

	if (m_is_loading)
	{
		if (!image_checkhash())
		{
			m_err = IMAGE_ERROR_INVALIDIMAGE;
			err = image_init_result::FAIL;
		}

		if (err == image_init_result::PASS)
		{
			if (m_created)
			{
				err = call_create(m_create_format, m_create_args);
				if (err != image_init_result::PASS)
				{
					if (!m_err)
						m_err = IMAGE_ERROR_UNSPECIFIED;
				}
			}
			else
			{
				// using device load
				err = call_load();
				if (err != image_init_result::PASS)
				{
					if (!m_err)
						m_err = IMAGE_ERROR_UNSPECIFIED;
				}
			}
		}
	}
	m_is_loading = false;
	m_create_format = 0;
	m_create_args = nullptr;
	return err;
}


//-------------------------------------------------
//  create - create a image
//-------------------------------------------------

image_init_result device_image_interface::create(const std::string &path)
{
	return create(path, nullptr, nullptr);
}


//-------------------------------------------------
//  create - create a image
//-------------------------------------------------

image_init_result device_image_interface::create(const std::string &path, const image_device_format *create_format, util::option_resolution *create_args)
{
	int format_index = 0;
	int cnt = 0;
	for (auto &format : m_formatlist)
	{
		if (create_format == format.get()) {
			format_index = cnt;
			break;
		}
		cnt++;
	}
	return load_internal(path, true, format_index, create_args);
}


//-------------------------------------------------
//  reset_and_load - called internally when we try
//  to load an is_reset_on_load() item; will reset
//  the emulation and record this image to be loaded
//-------------------------------------------------

void device_image_interface::reset_and_load(const std::string &path)
{
	// first make sure the reset is scheduled
	device().machine().schedule_hard_reset();

	// and record the new load
	device().machine().options().image_option(instance_name()).specify(path);

	// record that we're reset and loading
	m_is_reset_and_loading = true;
}


//-------------------------------------------------
//  clear - clear all internal data pertaining
//  to an image
//-------------------------------------------------

void device_image_interface::clear()
{
	m_mame_file.reset();
	m_file.reset();
>>>>>>> upstream/master

	m_image_name.clear();
	m_readonly = false;
	m_created = false;
<<<<<<< HEAD
=======
	m_create_format = 0;
	m_create_args = nullptr;
>>>>>>> upstream/master

	m_longname.clear();
	m_manufacturer.clear();
	m_year.clear();
	m_basename.clear();
	m_basename_noext.clear();
	m_filetype.clear();

	m_full_software_name.clear();
<<<<<<< HEAD
	m_software_info_ptr = NULL;
	m_software_part_ptr = NULL;
	m_software_list_name.clear();
}

/*-------------------------------------------------
    unload - main call to unload an image
-------------------------------------------------*/

void device_image_interface::unload()
{
	if (is_loaded() || m_software_info_ptr)
=======
	m_software_part_ptr = nullptr;
	m_software_list_name.clear();
}


//-------------------------------------------------
//  unload - main call to unload an image
//-------------------------------------------------

void device_image_interface::unload()
{
	if (is_loaded() || loaded_through_softlist())
>>>>>>> upstream/master
	{
		call_unload();
	}
	clear();
	clear_error();
}

<<<<<<< HEAD
/*-------------------------------------------------
    update_names - update brief and instance names
-------------------------------------------------*/

void device_image_interface::update_names(const device_type device_type, const char *inst, const char *brief)
{
	image_interface_iterator iter(device().mconfig().root_device());
	int count = 0;
	int index = -1;
	for (const device_image_interface *image = iter.first(); image != NULL; image = iter.next())
	{
		if (this == image)
			index = count;
		if ((image->image_type() == image_type() && device_type==NULL) || (device_type==image->device().type()))
			count++;
	}
	const char *inst_name = (device_type!=NULL) ? inst : device_typename(image_type());
	const char *brief_name = (device_type!=NULL) ? brief : device_brieftypename(image_type());
	if (count > 1)
	{
		strprintf(m_instance_name,"%s%d", inst_name, index + 1);
		strprintf(m_brief_instance_name, "%s%d", brief_name, index + 1);
=======

//-------------------------------------------------
//  create_option_guide
//-------------------------------------------------

OPTION_GUIDE_START(null_option_guide)
OPTION_GUIDE_END

const util::option_guide &device_image_interface::create_option_guide() const
{
	return null_option_guide;
}

//-------------------------------------------------
//  update_names - update brief and instance names
//-------------------------------------------------

void device_image_interface::update_names()
{
	const char *inst_name = custom_instance_name();
	const char *brief_name = custom_brief_instance_name();
	if (inst_name == nullptr)
		inst_name = device_typename(image_type());
	if (brief_name == nullptr)
		brief_name = device_brieftypename(image_type());

	// count instances of the general image type, or device type if custom
	int count = 0;
	int index = -1;
	for (const device_image_interface &image : image_interface_iterator(device().mconfig().root_device()))
	{
		if (this == &image)
			index = count;
		const char *other_name = image.custom_instance_name();
		if (!other_name)
			other_name = device_typename(image.image_type());

		if (other_name == inst_name || !strcmp(other_name, inst_name))
			count++;
	}

	m_canonical_instance_name = string_format("%s%d", inst_name, index + 1);
	if (count > 1)
	{
		m_instance_name = m_canonical_instance_name;
		m_brief_instance_name = string_format("%s%d", brief_name, index + 1);
>>>>>>> upstream/master
	}
	else
	{
		m_instance_name = inst_name;
		m_brief_instance_name = brief_name;
	}
}

//-------------------------------------------------
<<<<<<< HEAD
//  software_name_split - helper that splits a
//  software_list:software:part string into
//  separate software_list, software, and part
//  strings.
//
//  str1:str2:str3  => swlist_name - str1, swname - str2, swpart - str3
//  str1:str2       => swlist_name - NULL, swname - str1, swpart - str2
//  str1            => swlist_name - NULL, swname - str1, swpart - NULL
//
//  Notice however that we could also have been
//  passed a string swlist_name:swname, and thus
//  some special check has to be performed in this
//  case.
//-------------------------------------------------

void device_image_interface::software_name_split(const char *swlist_swname, std::string &swlist_name, std::string &swname, std::string &swpart)
{
	// reset all output parameters
	swlist_name.clear();
	swname.clear();
	swpart.clear();

	// if no colon, this is the swname by itself
	const char *split1 = strchr(swlist_swname, ':');
	if (split1 == NULL)
	{
		swname.assign(swlist_swname);
		return;
	}

	// if one colon, it is the swname and swpart alone
	const char *split2 = strchr(split1 + 1, ':');
	if (split2 == NULL)
	{
		swname.assign(swlist_swname, split1 - swlist_swname);
		swpart.assign(split1 + 1);
		return;
	}

	// if two colons present, split into 3 parts
	swlist_name.assign(swlist_swname, split1 - swlist_swname);
	swname.assign(split1 + 1, split2 - (split1 + 1));
	swpart.assign(split2 + 1);
}


software_part *device_image_interface::find_software_item(const char *path, bool restrict_to_interface)
{
	// split full software name into software list name and short software name
	std::string swlist_name, swinfo_name, swpart_name;
	software_name_split(path, swlist_name, swinfo_name, swpart_name);

	// determine interface
	const char *interface = NULL;
	if (restrict_to_interface)
		interface = image_interface();

	// find the software list if explicitly specified
	software_list_device_iterator deviter(device().mconfig().root_device());
	for (software_list_device *swlistdev = deviter.first(); swlistdev != NULL; swlistdev = deviter.next())
	{
		if (swlist_name.compare(swlistdev->list_name())==0 || !(swlist_name.length() > 0))
		{
			software_info *info = swlistdev->find(swinfo_name.c_str());
			if (info != NULL)
			{
				software_part *part = info->find_part(swpart_name.c_str(), interface);
				if (part != NULL)
					return part;
			}
		}

		if (swinfo_name == swlistdev->list_name())
=======
//  find_software_item
//-------------------------------------------------

const software_part *device_image_interface::find_software_item(const std::string &identifier, bool restrict_to_interface, software_list_device **dev) const
{
	// split full software name into software list name and short software name
	std::string list_name, software_name, part_name;
	if (!software_name_parse(identifier, &list_name, &software_name, &part_name))
		return nullptr;

	// determine interface
	const char *interface = restrict_to_interface
		? image_interface()
		: nullptr;

	// find the software list if explicitly specified
	for (software_list_device &swlistdev : software_list_device_iterator(device().mconfig().root_device()))
	{
		if (list_name.empty() || (list_name == swlistdev.list_name()))
		{
			const software_info *info = swlistdev.find(software_name);
			if (info != nullptr)
			{
				const software_part *part = info->find_part(part_name, interface);
				if (part != nullptr)
				{
					if (dev != nullptr)
						*dev = &swlistdev;
					return part;
				}
			}
		}

		if (software_name == swlistdev.list_name())
>>>>>>> upstream/master
		{
			// ad hoc handling for the case path = swlist_name:swinfo_name (e.g.
			// gameboy:sml) which is not handled properly by software_name_split
			// since the function cannot distinguish between this and the case
			// path = swinfo_name:swpart_name
<<<<<<< HEAD
			software_info *info = swlistdev->find(swpart_name.c_str());
			if (info != NULL)
			{
				software_part *part = info->find_part(NULL, interface);
				if (part != NULL)
					return part;
=======
			const software_info *info = swlistdev.find(part_name);
			if (info != nullptr)
			{
				const software_part *part = info->find_part("", interface);
				if (part != nullptr)
				{
					if (dev != nullptr)
						*dev = &swlistdev;
					return part;
				}
>>>>>>> upstream/master
			}
		}
	}

	// if explicitly specified and not found, just error here
<<<<<<< HEAD
	return NULL;
=======
	if (dev != nullptr)
		*dev = nullptr;
	return nullptr;
}


//-------------------------------------------------
//  get_software_list_loader
//-------------------------------------------------

const software_list_loader &device_image_interface::get_software_list_loader() const
{
	return false_software_list_loader::instance();
>>>>>>> upstream/master
}


//-------------------------------------------------
//  load_software_part
//
//  Load a software part for a device. The part to
//  load is determined by the "path", software lists
//  configured for a driver, and the interface
//  supported by the device.
//
//  returns true if the software could be loaded,
//  false otherwise. If the software could be loaded
//  sw_info and sw_part are also set.
//-------------------------------------------------

<<<<<<< HEAD
bool device_image_interface::load_software_part(const char *path, software_part *&swpart)
{
	// if no match has been found, we suggest similar shortnames
	swpart = find_software_item(path, true);
	if (swpart == NULL)
	{
		software_list_device::display_matches(device().machine().config(), image_interface(), path);
=======
bool device_image_interface::load_software_part(const std::string &identifier)
{
	// if no match has been found, we suggest similar shortnames
	software_list_device *swlist;
	m_software_part_ptr = find_software_item(identifier, true, &swlist);
	if (m_software_part_ptr == nullptr)
	{
		software_list_device::display_matches(device().machine().config(), image_interface(), identifier);
>>>>>>> upstream/master
		return false;
	}

	// Load the software part
<<<<<<< HEAD
	bool result = call_softlist_load(swpart->info().list(), swpart->info().shortname(), swpart->romdata());

	// Tell the world which part we actually loaded
	std::string full_sw_name;
	strprintf(full_sw_name,"%s:%s:%s", swpart->info().list().list_name(), swpart->info().shortname(), swpart->name());

	// check compatibility
	if (!swpart->is_compatible(swpart->info().list()))
		osd_printf_warning("WARNING! the set %s might not work on this system due to missing filter(s) '%s'\n", swpart->info().shortname(), swpart->info().list().filter());

	// check requirements and load those images
	const char *requirement = swpart->feature("requirement");
	if (requirement != NULL)
	{
		software_part *req_swpart = find_software_item(requirement, false);
		if (req_swpart != NULL)
		{
			image_interface_iterator imgiter(device().machine().root_device());
			for (device_image_interface *req_image = imgiter.first(); req_image != NULL; req_image = imgiter.next())
			{
				const char *interface = req_image->image_interface();
				if (interface != NULL)
				{
					if (req_swpart->matches_interface(interface))
					{
						const char *option = device().mconfig().options().value(req_image->brief_instance_name());
						// mount only if not already mounted
						if (strlen(option) == 0 && !req_image->filename())
						{
							req_image->set_init_phase();
							req_image->load(requirement);
						}
						break;
					}
				}
			}
		}
	}
=======
	const char *swname = m_software_part_ptr->info().shortname().c_str();
	const rom_entry *start_entry = m_software_part_ptr->romdata().data();
	const software_list_loader &loader = get_software_list_loader();
	bool result = loader.load_software(*this, *swlist, swname, start_entry);

	// check compatibility
	switch (swlist->is_compatible(*m_software_part_ptr))
	{
		case SOFTWARE_IS_COMPATIBLE:
			break;

		case SOFTWARE_IS_INCOMPATIBLE:
			swlist->popmessage("WARNING! the set %s might not work on this system due to incompatible filter(s) '%s'\n", m_software_part_ptr->info().shortname(), swlist->filter());
			break;

		case SOFTWARE_NOT_COMPATIBLE:
			swlist->popmessage("WARNING! the set %s might not work on this system due to missing filter(s) '%s'\n", m_software_part_ptr->info().shortname(), swlist->filter());
			break;
	}

	// check requirements and load those images
	const char *requirement = m_software_part_ptr->feature("requirement");
	if (requirement != nullptr)
	{
		const software_part *req_swpart = find_software_item(requirement, false);
		if (req_swpart != nullptr)
		{
			device_image_interface *req_image = software_list_device::find_mountable_image(device().mconfig(), *req_swpart);
			if (req_image != nullptr)
				req_image->load_software(requirement);
		}
	}

	m_software_list_name = swlist->list_name();
>>>>>>> upstream/master
	return result;
}

//-------------------------------------------------
//  software_get_default_slot
//-------------------------------------------------

<<<<<<< HEAD
void device_image_interface::software_get_default_slot(std::string &result, const char *default_card_slot)
{
	const char *path = device().mconfig().options().value(instance_name());
	result.clear();
	if (strlen(path) > 0)
	{
		result.assign(default_card_slot);
		software_part *swpart = find_software_item(path, true);
		if (swpart != NULL)
		{
			const char *slot = swpart->feature("slot");
			if (slot != NULL)
				result.assign(slot);
		}
	}
}

/*-------------------------------------------------
    get_selection_menu - create the menu stack
    for ui-level image selection
-------------------------------------------------*/

ui_menu *device_image_interface::get_selection_menu(running_machine &machine, render_container *container)
{
	return auto_alloc_clear(machine, ui_menu_control_device_image(machine, container, this));
}
=======
std::string device_image_interface::software_get_default_slot(const char *default_card_slot) const
{
	std::string result;

	const std::string &image_name(device().mconfig().options().image_option(instance_name()).value());
	if (!image_name.empty())
	{
		result.assign(default_card_slot);
		const software_part *swpart = find_software_item(image_name, true);
		if (swpart != nullptr)
		{
			const char *slot = swpart->feature("slot");
			if (slot != nullptr)
				result.assign(slot);
		}
	}
	return result;
}


//-------------------------------------------------
//  init_phase
//-------------------------------------------------

bool device_image_interface::init_phase() const
{
	// diimage.cpp has quite a bit of logic that randomly decides to behave
	// differently at startup; this is an enc[r]apsulation of the "logic"
	// that switches these behaviors
	return !device().has_running_machine()
		|| device().machine().phase() == machine_phase::INIT;
}


//----------------------------------------------------------------------------

static int image_fseek_thunk(void *file, s64 offset, int whence)
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

static u64 image_fsize_thunk(void *file)
{
	device_image_interface *image = (device_image_interface *) file;
	return image->length();
}

//----------------------------------------------------------------------------

struct io_procs image_ioprocs =
{
	nullptr,
	image_fseek_thunk,
	image_fread_thunk,
	image_fwrite_thunk,
	image_fsize_thunk
};
>>>>>>> upstream/master
