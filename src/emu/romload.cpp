// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria,Paul Priest,Aaron Giles
/*********************************************************************

<<<<<<< HEAD
    romload.c
=======
    romload.cpp
>>>>>>> upstream/master

    ROM loading functions.
*********************************************************************/

#include "emu.h"
#include "emuopts.h"
#include "drivenum.h"
<<<<<<< HEAD
#include "chd.h"
#include "softlist.h"
#include "ui/ui.h"
#ifdef USE_IPS
#include "ips.h"
#endif /* USE_IPS */


#define LOG_LOAD 0
#define LOG(x) do { if (LOG_LOAD) debugload x; } while(0)
=======
#include "softlist_dev.h"
#include "ui/uimain.h"


#define LOG_LOAD 0
#define LOG(...) do { if (LOG_LOAD) debugload(__VA_ARGS__); } while(0)
>>>>>>> upstream/master


/***************************************************************************
    CONSTANTS
***************************************************************************/

#define TEMPBUFFER_MAX_SIZE     (1024 * 1024 * 1024)

<<<<<<< HEAD


/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

#if 0 //mamep: moved to romload.h
class open_chd
{
	friend class simple_list<open_chd>;

public:
	open_chd(const char *region)
		: m_next(NULL),
			m_region(region) { }

	open_chd *next() const { return m_next; }
	const char *region() const { return m_region.c_str(); }
	chd_file &chd() { return m_diffchd.opened() ? m_diffchd : m_origchd; }
	chd_file &orig_chd() { return m_origchd; }
	chd_file &diff_chd() { return m_diffchd; }

private:
	open_chd *          m_next;                 /* pointer to next in the list */
	std::string         m_region;               /* disk region we came from */
	chd_file            m_origchd;              /* handle to the original CHD */
	chd_file            m_diffchd;              /* handle to the diff CHD */
};


struct romload_private
{
	running_machine &machine() const { assert(m_machine != NULL); return *m_machine; }

	running_machine *m_machine;         /* machine object where needed */

	int             warnings;           /* warning count during processing */
	int             knownbad;           /* BAD_DUMP/NO_DUMP count during processing */
	int             errors;             /* error count during processing */

	int             romsloaded;         /* current ROMs loaded count */
	int             romstotal;          /* total number of ROMs to read */
	UINT32          romsloadedsize;     /* total size of ROMs loaded so far */
	UINT32          romstotalsize;      /* total size of ROMs to read */

	emu_file *      file;               /* current file */
#ifdef USE_IPS
	void *          patch;              /* current ips */
#endif /* USE_IPS */
	simple_list<open_chd> chd_list;     /* disks */

	memory_region * region;             /* info about current region */

	std::string     errorstring;        /* error string */
	std::string     softwarningstring;  /* software warning string */
};
#endif


/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

static void rom_exit(running_machine &machine);

/***************************************************************************
    HELPERS (also used by devimage.c)
 ***************************************************************************/

file_error common_process_file(emu_options &options, const char *location, const char *ext, const rom_entry *romp, emu_file &image_file)
{
	file_error filerr;

	if (location != NULL && strcmp(location, "") != 0)
=======
/***************************************************************************
    HELPERS (also used by diimage.cpp)
 ***************************************************************************/

static osd_file::error common_process_file(emu_options &options, const char *location, const char *ext, const rom_entry *romp, emu_file &image_file)
{
	osd_file::error filerr;

	if (location != nullptr && strcmp(location, "") != 0)
>>>>>>> upstream/master
		filerr = image_file.open(location, PATH_SEPARATOR, ROM_GETNAME(romp), ext);
	else
		filerr = image_file.open(ROM_GETNAME(romp), ext);

	return filerr;
}

<<<<<<< HEAD
file_error common_process_file(emu_options &options, const char *location, bool has_crc, UINT32 crc, const rom_entry *romp, emu_file **image_file)
{
	*image_file = global_alloc(emu_file(options.media_path(), OPEN_FLAG_READ));
	file_error filerr;

	if (has_crc)
		filerr = (*image_file)->open(location, PATH_SEPARATOR, ROM_GETNAME(romp), crc);
	else
		filerr = (*image_file)->open(location, PATH_SEPARATOR, ROM_GETNAME(romp));

	if (filerr != FILERR_NONE)
	{
		global_free(*image_file);
		*image_file = NULL;
	}
	return filerr;
}


/***************************************************************************
    HARD DISK HANDLING
***************************************************************************/

/*-------------------------------------------------
    get_disk_handle - return a pointer to the
    CHD file associated with the given region
-------------------------------------------------*/

chd_file *get_disk_handle(running_machine &machine, const char *region)
{
	for (open_chd *curdisk = machine.romload_data->chd_list.first(); curdisk != NULL; curdisk = curdisk->next())
		if (strcmp(curdisk->region(), region) == 0)
			return &curdisk->chd();
	return NULL;
}


/*-------------------------------------------------
    set_disk_handle - set a pointer to the CHD
    file associated with the given region
-------------------------------------------------*/

int set_disk_handle(running_machine &machine, const char *region, const char *fullpath)
{
	open_chd *chd = global_alloc(open_chd(region));
	chd_error err = chd->orig_chd().open(fullpath);
	if (err == CHDERR_NONE)
		machine.romload_data->chd_list.append(*chd);
	else
		global_free(chd);
	return err;
}



=======
std::unique_ptr<emu_file> common_process_file(emu_options &options, const char *location, bool has_crc, u32 crc, const rom_entry *romp, osd_file::error &filerr)
{
	auto image_file = std::make_unique<emu_file>(options.media_path(), OPEN_FLAG_READ);

	if (has_crc)
		filerr = image_file->open(location, PATH_SEPARATOR, ROM_GETNAME(romp), crc);
	else
		filerr = image_file->open(location, PATH_SEPARATOR, ROM_GETNAME(romp));

	if (filerr != osd_file::error::NONE)
	{
		image_file = nullptr;
	}
	return image_file;
}

>>>>>>> upstream/master
/***************************************************************************
    ROM LOADING
***************************************************************************/

/*-------------------------------------------------
    rom_first_region - return pointer to first ROM
    region
-------------------------------------------------*/

const rom_entry *rom_first_region(const device_t &device)
{
	const rom_entry *romp = device.rom_region();
	while (romp && ROMENTRY_ISPARAMETER(romp))
		romp++;
<<<<<<< HEAD
	return (romp != NULL && !ROMENTRY_ISEND(romp)) ? romp : NULL;
=======
	return (romp != nullptr && !ROMENTRY_ISEND(romp)) ? romp : nullptr;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    rom_next_region - return pointer to next ROM
    region
-------------------------------------------------*/

const rom_entry *rom_next_region(const rom_entry *romp)
{
	romp++;
	while (!ROMENTRY_ISREGIONEND(romp))
		romp++;
	while (ROMENTRY_ISPARAMETER(romp))
		romp++;
<<<<<<< HEAD
	return ROMENTRY_ISEND(romp) ? NULL : romp;
=======
	return ROMENTRY_ISEND(romp) ? nullptr : romp;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    rom_first_file - return pointer to first ROM
    file
-------------------------------------------------*/

const rom_entry *rom_first_file(const rom_entry *romp)
{
	romp++;
	while (!ROMENTRY_ISFILE(romp) && !ROMENTRY_ISREGIONEND(romp))
		romp++;
<<<<<<< HEAD
	return ROMENTRY_ISREGIONEND(romp) ? NULL : romp;
=======
	return ROMENTRY_ISREGIONEND(romp) ? nullptr : romp;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    rom_next_file - return pointer to next ROM
    file
-------------------------------------------------*/

const rom_entry *rom_next_file(const rom_entry *romp)
{
	romp++;
	while (!ROMENTRY_ISFILE(romp) && !ROMENTRY_ISREGIONEND(romp))
		romp++;
<<<<<<< HEAD
	return ROMENTRY_ISREGIONEND(romp) ? NULL : romp;
=======
	return ROMENTRY_ISREGIONEND(romp) ? nullptr : romp;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    rom_first_parameter - return pointer to the first
    per-game parameter
-------------------------------------------------*/

const rom_entry *rom_first_parameter(const device_t &device)
{
	const rom_entry *romp = device.rom_region();
	while (romp && !ROMENTRY_ISEND(romp) && !ROMENTRY_ISPARAMETER(romp))
		romp++;
<<<<<<< HEAD
	return (romp != NULL && !ROMENTRY_ISEND(romp)) ? romp : NULL;
=======
	return (romp != nullptr && !ROMENTRY_ISEND(romp)) ? romp : nullptr;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    rom_next_parameter - return pointer to the next
    per-game parameter
-------------------------------------------------*/

const rom_entry *rom_next_parameter(const rom_entry *romp)
{
	romp++;
	while (!ROMENTRY_ISREGIONEND(romp) && !ROMENTRY_ISPARAMETER(romp))
		romp++;
<<<<<<< HEAD
	return ROMENTRY_ISEND(romp) ? NULL : romp;
=======
	return ROMENTRY_ISEND(romp) ? nullptr : romp;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    rom_region_name - return the appropriate name
    for a rom region
-------------------------------------------------*/

std::string rom_region_name(const device_t &device, const rom_entry *romp)
{
	return device.subtag(ROM_GETNAME(romp));
}


/*-------------------------------------------------
    rom_parameter_name - return the appropriate name
    for a per-game parameter
-------------------------------------------------*/

std::string rom_parameter_name(const device_t &device, const rom_entry *romp)
{
<<<<<<< HEAD
	return device.subtag(romp->_name);
=======
	return device.subtag(romp->name().c_str());
>>>>>>> upstream/master
}


/*-------------------------------------------------
    rom_parameter_name - return the value for a
    per-game parameter
-------------------------------------------------*/

std::string rom_parameter_value(const rom_entry *romp)
{
<<<<<<< HEAD
	return std::string(romp->_hashdata);
=======
	return romp->hashdata();
>>>>>>> upstream/master
}


/*-------------------------------------------------
    rom_file_size - return the expected size of a
    file given the ROM description
-------------------------------------------------*/

<<<<<<< HEAD
UINT32 rom_file_size(const rom_entry *romp)
{
	UINT32 maxlength = 0;
=======
u32 rom_file_size(const rom_entry *romp)
{
	u32 maxlength = 0;
>>>>>>> upstream/master

	/* loop until we run out of reloads */
	do
	{
<<<<<<< HEAD
		UINT32 curlength;
=======
		u32 curlength;
>>>>>>> upstream/master

		/* loop until we run out of continues/ignores */
		curlength = ROM_GETLENGTH(romp++);
		while (ROMENTRY_ISCONTINUE(romp) || ROMENTRY_ISIGNORE(romp))
			curlength += ROM_GETLENGTH(romp++);

		/* track the maximum length */
<<<<<<< HEAD
		maxlength = MAX(maxlength, curlength);
=======
		maxlength = std::max(maxlength, curlength);
>>>>>>> upstream/master
	}
	while (ROMENTRY_ISRELOAD(romp));

	return maxlength;
}


/*-------------------------------------------------
    debugload - log data to a file
-------------------------------------------------*/

static void CLIB_DECL ATTR_PRINTF(1,2) debugload(const char *string, ...)
{
	static int opened;
	va_list arg;
	FILE *f;

	f = fopen("romload.log", opened++ ? "a" : "w");
	if (f)
	{
		va_start(arg, string);
		vfprintf(f, string, arg);
		va_end(arg);
		fclose(f);
	}
}


<<<<<<< HEAD
=======
/***************************************************************************
    HARD DISK HANDLING
***************************************************************************/

/*-------------------------------------------------
    get_disk_handle - return a pointer to the
    CHD file associated with the given region
-------------------------------------------------*/

chd_file *rom_load_manager::get_disk_handle(const char *region)
{
	for (auto &curdisk : m_chd_list)
		if (strcmp(curdisk->region(), region) == 0)
			return &curdisk->chd();
	return nullptr;
}


/*-------------------------------------------------
    set_disk_handle - set a pointer to the CHD
    file associated with the given region
-------------------------------------------------*/

int rom_load_manager::set_disk_handle(const char *region, const char *fullpath)
{
	auto chd = std::make_unique<open_chd>(region);
	auto err = chd->orig_chd().open(fullpath);
	if (err == CHDERR_NONE)
		m_chd_list.push_back(std::move(chd));
	return err;
}

>>>>>>> upstream/master
/*-------------------------------------------------
    determine_bios_rom - determine system_bios
    from SystemBios structure and OPTION_BIOS
-------------------------------------------------*/

<<<<<<< HEAD
static void determine_bios_rom(romload_private *romdata, device_t *device, const char *specbios)
{
	const char *defaultname = NULL;
	const rom_entry *rom;
	int default_no = 1;
	int bios_count = 0;

	device->set_system_bios(0);

	/* first determine the default BIOS name */
	for (rom = device->rom_region(); !ROMENTRY_ISEND(rom); rom++)
		if (ROMENTRY_ISDEFAULT_BIOS(rom))
			defaultname = ROM_GETNAME(rom);

	/* look for a BIOS with a matching name */
	for (rom = device->rom_region(); !ROMENTRY_ISEND(rom); rom++)
		if (ROMENTRY_ISSYSTEM_BIOS(rom))
		{
			const char *biosname = ROM_GETNAME(rom);
			int bios_flags = ROM_GETBIOSFLAGS(rom);
=======
void rom_load_manager::determine_bios_rom(device_t &device, const char *specbios)
{
	device.set_system_bios(0);

	/* first determine the default BIOS name */
	char const *defaultname(nullptr);
	for (const rom_entry &rom : device.rom_region_vector())
	{
		if (ROMENTRY_ISDEFAULT_BIOS(&rom))
		{
			defaultname = ROM_GETNAME(&rom);
			break;
		}
	}

	/* look for a BIOS with a matching name */
	int bios_count = 0, default_no = 1;
	for (const rom_entry &rom : device.rom_region_vector())
	{
		if (ROMENTRY_ISSYSTEM_BIOS(&rom))
		{
			char const *const biosname = ROM_GETNAME(&rom);
			int const bios_flags = ROM_GETBIOSFLAGS(&rom);
>>>>>>> upstream/master
			char bios_number[20];

			/* Allow '-bios n' to still be used */
			sprintf(bios_number, "%d", bios_flags - 1);
<<<<<<< HEAD
			if (core_stricmp(bios_number, specbios) == 0 || core_stricmp(biosname, specbios) == 0)
				device->set_system_bios(bios_flags);
			if (defaultname != NULL && core_stricmp(biosname, defaultname) == 0)
				default_no = bios_flags;
			bios_count++;
		}

	/* if none found, use the default */
	if (device->system_bios() == 0 && bios_count > 0)
	{
		/* if we got neither an empty string nor 'default' then warn the user */
		if (specbios[0] != 0 && strcmp(specbios, "default") != 0 && romdata != NULL)
		{
			strcatprintf(romdata->errorstring, "%s: invalid bios\n", specbios);
			romdata->errors++;
		}

		/* set to default */
		device->set_system_bios(default_no);
	}
	device->set_default_bios(default_no);
	LOG(("For \"%s\" using System BIOS: %d\n", device->tag(), device->system_bios()));
=======
			if (!core_stricmp(bios_number, specbios) || !core_stricmp(biosname, specbios))
				device.set_system_bios(bios_flags);
			if (defaultname && !core_stricmp(biosname, defaultname))
				default_no = bios_flags;
			bios_count++;
		}
	}

	/* if none found, use the default */
	if (device.system_bios() == 0 && bios_count > 0)
	{
		/* if we got neither an empty string nor 'default' then warn the user */
		if (specbios[0] && !core_stricmp(specbios, "default"))
		{
			m_errorstring.append(string_format("%s: invalid bios, reverting to default\n", specbios));
			m_warnings++;
		}

		/* set to default */
		device.set_system_bios(default_no);
	}
	device.set_default_bios(default_no);
	LOG("For \"%s\" using System BIOS: %d\n", device.tag(), device.system_bios());
>>>>>>> upstream/master
}


/*-------------------------------------------------
    count_roms - counts the total number of ROMs
    that will need to be loaded
-------------------------------------------------*/

<<<<<<< HEAD
static void count_roms(romload_private *romdata)
=======
void rom_load_manager::count_roms()
>>>>>>> upstream/master
{
	const rom_entry *region, *rom;

	/* start with 0 */
<<<<<<< HEAD
	romdata->romstotal = 0;
	romdata->romstotalsize = 0;

	/* loop over regions, then over files */
	device_iterator deviter(romdata->machine().config().root_device());
	for (device_t *device = deviter.first(); device != NULL; device = deviter.next())
		for (region = rom_first_region(*device); region != NULL; region = rom_next_region(region))
			for (rom = rom_first_file(region); rom != NULL; rom = rom_next_file(rom))
				if (ROM_GETBIOSFLAGS(rom) == 0 || ROM_GETBIOSFLAGS(rom) == device->system_bios())
				{
					romdata->romstotal++;
					romdata->romstotalsize += rom_file_size(rom);
=======
	m_romstotal = 0;
	m_romstotalsize = 0;

	/* loop over regions, then over files */
	for (device_t &device : device_iterator(machine().config().root_device()))
		for (region = rom_first_region(device); region != nullptr; region = rom_next_region(region))
			for (rom = rom_first_file(region); rom != nullptr; rom = rom_next_file(rom))
				if (ROM_GETBIOSFLAGS(rom) == 0 || ROM_GETBIOSFLAGS(rom) == device.system_bios())
				{
					m_romstotal++;
					m_romstotalsize += rom_file_size(rom);
>>>>>>> upstream/master
				}
}


/*-------------------------------------------------
    fill_random - fills an area of memory with
    random data
-------------------------------------------------*/

<<<<<<< HEAD
static void fill_random(running_machine &machine, UINT8 *base, UINT32 length)
{
	while (length--)
		*base++ = machine.rand();
=======
void rom_load_manager::fill_random(u8 *base, u32 length)
{
	while (length--)
		*base++ = machine().rand();
>>>>>>> upstream/master
}


/*-------------------------------------------------
    handle_missing_file - handles error generation
    for missing files
-------------------------------------------------*/

<<<<<<< HEAD
static void handle_missing_file(romload_private *romdata, const rom_entry *romp, std::string tried_file_names, chd_error chderr)
=======
void rom_load_manager::handle_missing_file(const rom_entry *romp, std::string tried_file_names, chd_error chderr)
>>>>>>> upstream/master
{
	if(tried_file_names.length() != 0)
		tried_file_names = " (tried in " + tried_file_names + ")";

	std::string name(ROM_GETNAME(romp));

	bool is_chd = (chderr != CHDERR_NONE);
	if (is_chd)
		name += ".chd";

	bool is_chd_error = (is_chd && chderr != CHDERR_FILE_NOT_FOUND);
	if (is_chd_error)
<<<<<<< HEAD
		strcatprintf(romdata->errorstring, "%s CHD ERROR: %s\n", name.c_str(), chd_file::error_string(chderr));
=======
		m_errorstring.append(string_format("%s CHD ERROR: %s\n", name.c_str(), chd_file::error_string(chderr)));
>>>>>>> upstream/master

	/* optional files are okay */
	if (ROM_ISOPTIONAL(romp))
	{
		if (!is_chd_error)
<<<<<<< HEAD
			strcatprintf(romdata->errorstring, "OPTIONAL %s NOT FOUND%s\n", name.c_str(), tried_file_names.c_str());
		romdata->warnings++;
	}

	/* no good dumps are okay */
	else if (hash_collection(ROM_GETHASHDATA(romp)).flag(hash_collection::FLAG_NO_DUMP))
	{
		if (!is_chd_error)
			strcatprintf(romdata->errorstring, "%s NOT FOUND (NO GOOD DUMP KNOWN)%s\n", name.c_str(), tried_file_names.c_str());
		romdata->knownbad++;
=======
			m_errorstring.append(string_format("OPTIONAL %s NOT FOUND%s\n", name.c_str(), tried_file_names.c_str()));
		m_warnings++;
	}

	/* no good dumps are okay */
	else if (util::hash_collection(ROM_GETHASHDATA(romp)).flag(util::hash_collection::FLAG_NO_DUMP))
	{
		if (!is_chd_error)
			m_errorstring.append(string_format("%s NOT FOUND (NO GOOD DUMP KNOWN)%s\n", name, tried_file_names));
		m_knownbad++;
>>>>>>> upstream/master
	}

	/* anything else is bad */
	else
	{
		if (!is_chd_error)
<<<<<<< HEAD
			strcatprintf(romdata->errorstring, "%s NOT FOUND%s\n", name.c_str(), tried_file_names.c_str());
		romdata->errors++;
=======
			m_errorstring.append(string_format("%s NOT FOUND%s\n", name.c_str(), tried_file_names));
		m_errors++;
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
    dump_wrong_and_correct_checksums - dump an
    error message containing the wrong and the
    correct checksums for a given ROM
-------------------------------------------------*/

<<<<<<< HEAD
static void dump_wrong_and_correct_checksums(romload_private *romdata, const hash_collection &hashes, const hash_collection &acthashes)
{
	std::string tempstr;
	strcatprintf(romdata->errorstring, "    EXPECTED: %s\n", hashes.macro_string(tempstr));
	strcatprintf(romdata->errorstring, "       FOUND: %s\n", acthashes.macro_string(tempstr));
=======
void rom_load_manager::dump_wrong_and_correct_checksums(const util::hash_collection &hashes, const util::hash_collection &acthashes)
{
	m_errorstring.append(string_format("    EXPECTED: %s\n", hashes.macro_string().c_str()));
	m_errorstring.append(string_format("       FOUND: %s\n", acthashes.macro_string().c_str()));
>>>>>>> upstream/master
}


/*-------------------------------------------------
    verify_length_and_hash - verify the length
    and hash signatures of a file
-------------------------------------------------*/

<<<<<<< HEAD
static void verify_length_and_hash(romload_private *romdata, const char *name, UINT32 explength, const hash_collection &hashes)
{
	/* we've already complained if there is no file */
	if (romdata->file == NULL)
		return;

	/* verify length */
	UINT32 actlength = romdata->file->size();
	if (explength != actlength)
	{
		strcatprintf(romdata->errorstring, _("%s WRONG LENGTH (expected: %08x found: %08x)\n"), name, explength, actlength);
		romdata->warnings++;
	}

	/* If there is no good dump known, write it */
	std::string tempstr;
	hash_collection &acthashes = romdata->file->hashes(hashes.hash_types(tempstr));
	if (hashes.flag(hash_collection::FLAG_NO_DUMP))
	{
		strcatprintf(romdata->errorstring, _("%s NO GOOD DUMP KNOWN\n"), name);
		romdata->knownbad++;
=======
void rom_load_manager::verify_length_and_hash(const char *name, u32 explength, const util::hash_collection &hashes)
{
	/* we've already complained if there is no file */
	if (m_file == nullptr)
		return;

	/* verify length */
	u32 actlength = m_file->size();
	if (explength != actlength)
	{
		m_errorstring.append(string_format("%s WRONG LENGTH (expected: %08x found: %08x)\n", name, explength, actlength));
		m_warnings++;
	}

	/* If there is no good dump known, write it */
	util::hash_collection &acthashes = m_file->hashes(hashes.hash_types().c_str());
	if (hashes.flag(util::hash_collection::FLAG_NO_DUMP))
	{
		m_errorstring.append(string_format("%s NO GOOD DUMP KNOWN\n", name));
		m_knownbad++;
>>>>>>> upstream/master
	}
	/* verify checksums */
	else if (hashes != acthashes)
	{
		/* otherwise, it's just bad */
<<<<<<< HEAD
		strcatprintf(romdata->errorstring, _("%s WRONG CHECKSUMS:\n"), name);
		dump_wrong_and_correct_checksums(romdata, hashes, acthashes);
		romdata->warnings++;
	}
	/* If it matches, but it is actually a bad dump, write it */
	else if (hashes.flag(hash_collection::FLAG_BAD_DUMP))
	{
		strcatprintf(romdata->errorstring, _("%s ROM NEEDS REDUMP\n"),name);
		romdata->knownbad++;
=======
		util::hash_collection &all_acthashes = acthashes.hash_types() == util::hash_collection::HASH_TYPES_ALL
			? acthashes
			: m_file->hashes(util::hash_collection::HASH_TYPES_ALL);
		m_errorstring.append(string_format("%s WRONG CHECKSUMS:\n", name));
		dump_wrong_and_correct_checksums(hashes, all_acthashes);
		m_warnings++;
	}
	/* If it matches, but it is actually a bad dump, write it */
	else if (hashes.flag(util::hash_collection::FLAG_BAD_DUMP))
	{
		m_errorstring.append(string_format("%s ROM NEEDS REDUMP\n", name));
		m_knownbad++;
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
    display_loading_rom_message - display
    messages about ROM loading to the user
-------------------------------------------------*/

<<<<<<< HEAD
static void display_loading_rom_message(romload_private *romdata, const char *name, bool from_list)
{
	char buffer[200];

	if (name != NULL)
		sprintf(buffer, _("Loading %s (%d%%)"), from_list ? _("Software") : emulator_info::get_capstartgamenoun(), (UINT32)(100 * (UINT64)romdata->romsloadedsize / (UINT64)romdata->romstotalsize));
	else
		sprintf(buffer, _("Loading Complete"));

	if (!romdata->machine().ui().is_menu_active())
		romdata->machine().ui().set_startup_text(buffer, false);
=======
void rom_load_manager::display_loading_rom_message(const char *name, bool from_list)
{
	char buffer[200];

	if (name != nullptr)
		sprintf(buffer, "%s (%d%%)", from_list ? "Loading Software" : "Loading Machine", u32(100 * u64(m_romsloadedsize) / u64(m_romstotalsize)));
	else
		sprintf(buffer, "Loading Complete");

	if (!machine().ui().is_menu_active())
		machine().ui().set_startup_text(buffer, false);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    display_rom_load_results - display the final
    results of ROM loading
-------------------------------------------------*/

<<<<<<< HEAD
static void display_rom_load_results(romload_private *romdata, bool from_list)
{
	/* final status display */
	display_loading_rom_message(romdata, NULL, from_list);

	/* if we had errors, they are fatal */
	if (romdata->errors != 0)
	{
		/* create the error message and exit fatally */
		osd_printf_error("%s", romdata->errorstring.c_str());
		fatalerror_exitcode(romdata->machine(), MAMERR_MISSING_FILES, _("Required files are missing, the %s cannot be run."),emulator_info::get_gamenoun());
	}

	/* if we had warnings, output them, but continue */
	if ((romdata-> warnings) || (romdata->knownbad))
	{
		romdata->errorstring.append(_("WARNING: the "));
		romdata->errorstring.append(emulator_info::get_gamenoun());
		romdata->errorstring.append(_(" might not run correctly."));
		osd_printf_warning("%s\n", romdata->errorstring.c_str());
=======
void rom_load_manager::display_rom_load_results(bool from_list)
{
	/* final status display */
	display_loading_rom_message(nullptr, from_list);

	/* if we had errors, they are fatal */
	if (m_errors != 0)
	{
		/* create the error message and exit fatally */
		osd_printf_error("%s", m_errorstring.c_str());
		fatalerror_exitcode(machine(), EMU_ERR_MISSING_FILES, "Required files are missing, the machine cannot be run.");
	}

	/* if we had warnings, output them, but continue */
	if ((m_warnings) || (m_knownbad))
	{
		m_errorstring.append("WARNING: the machine might not run correctly.");
		osd_printf_warning("%s\n", m_errorstring.c_str());
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
    region_post_process - post-process a region,
    byte swapping and inverting data as necessary
-------------------------------------------------*/

<<<<<<< HEAD
static void region_post_process(romload_private *romdata, const char *rgntag, bool invert)
{
	memory_region *region = romdata->machine().root_device().memregion(rgntag);
	UINT8 *base;
	int i, j;

	// do nothing if no region
	if (region == NULL)
		return;

	LOG(("+ datawidth=%dbit endian=%s\n", region->bitwidth(),
			region->endianness() == ENDIANNESS_LITTLE ? "little" : "big"));
=======
void rom_load_manager::region_post_process(const char *rgntag, bool invert)
{
	memory_region *region = machine().root_device().memregion(rgntag);
	u8 *base;
	int i, j;

	// do nothing if no region
	if (region == nullptr)
		return;

	LOG("+ datawidth=%dbit endian=%s\n", region->bitwidth(),
			region->endianness() == ENDIANNESS_LITTLE ? "little" : "big");
>>>>>>> upstream/master

	/* if the region is inverted, do that now */
	if (invert)
	{
<<<<<<< HEAD
		LOG(("+ Inverting region\n"));
=======
		LOG("+ Inverting region\n");
>>>>>>> upstream/master
		for (i = 0, base = region->base(); i < region->bytes(); i++)
			*base++ ^= 0xff;
	}

	/* swap the endianness if we need to */
	if (region->bytewidth() > 1 && region->endianness() != ENDIANNESS_NATIVE)
	{
<<<<<<< HEAD
		LOG(("+ Byte swapping region\n"));
		int datawidth = region->bytewidth();
		for (i = 0, base = region->base(); i < region->bytes(); i += datawidth)
		{
			UINT8 temp[8];
=======
		LOG("+ Byte swapping region\n");
		int datawidth = region->bytewidth();
		for (i = 0, base = region->base(); i < region->bytes(); i += datawidth)
		{
			u8 temp[8];
>>>>>>> upstream/master
			memcpy(temp, base, datawidth);
			for (j = datawidth - 1; j >= 0; j--)
				*base++ = temp[j];
		}
	}
}


/*-------------------------------------------------
    open_rom_file - open a ROM file, searching
    up the parent and loading by checksum
-------------------------------------------------*/

<<<<<<< HEAD
static int open_rom_file(romload_private *romdata, const char *regiontag, const rom_entry *romp, std::string &tried_file_names, bool from_list)
{
	file_error filerr = FILERR_NOT_FOUND;
	UINT32 romsize = rom_file_size(romp);
	tried_file_names = "";

	/* update status display */
	display_loading_rom_message(romdata, ROM_GETNAME(romp), from_list);

	/* extract CRC to use for searching */
	UINT32 crc = 0;
	bool has_crc = hash_collection(ROM_GETHASHDATA(romp)).crc(crc);

	/* attempt reading up the chain through the parents. It automatically also
	 attempts any kind of load by checksum supported by the archives. */
	romdata->file = NULL;
	for (int drv = driver_list::find(romdata->machine().system()); romdata->file == NULL && drv != -1; drv = driver_list::clone(drv)) {
		if (tried_file_names.length() != 0)
			tried_file_names += " ";
		tried_file_names += driver_list::driver(drv).name;
		filerr = common_process_file(romdata->machine().options(), driver_list::driver(drv).name, has_crc, crc, romp, &romdata->file);
#ifdef USE_IPS
		romdata->patch = assign_ips_patch(romp);
		if (romdata->patch)
			LOG(("ROM %s: has ips\n", ROM_GETNAME(romp)));
#endif /* USE_IPS */
	}

	/* if the region is load by name, load the ROM from there */
	if (romdata->file == NULL && regiontag != NULL)
=======
int rom_load_manager::open_rom_file(const char *regiontag, const rom_entry *romp, std::string &tried_file_names, bool from_list)
{
	osd_file::error filerr = osd_file::error::NOT_FOUND;
	u32 romsize = rom_file_size(romp);
	tried_file_names = "";

	/* update status display */
	display_loading_rom_message(ROM_GETNAME(romp), from_list);

	/* extract CRC to use for searching */
	u32 crc = 0;
	bool has_crc = util::hash_collection(ROM_GETHASHDATA(romp)).crc(crc);

	/* attempt reading up the chain through the parents. It automatically also
	 attempts any kind of load by checksum supported by the archives. */
	m_file = nullptr;
	for (int drv = driver_list::find(machine().system()); m_file == nullptr && drv != -1; drv = driver_list::clone(drv)) {
		if (tried_file_names.length() != 0)
			tried_file_names += " ";
		tried_file_names += driver_list::driver(drv).name;
		m_file = common_process_file(machine().options(), driver_list::driver(drv).name, has_crc, crc, romp, filerr);
	}

	/* if the region is load by name, load the ROM from there */
	if (m_file == nullptr && regiontag != nullptr)
>>>>>>> upstream/master
	{
		// check if we are dealing with softwarelists. if so, locationtag
		// is actually a concatenation of: listname + setname + parentname
		// separated by '%' (parentname being present only for clones)
		std::string tag1(regiontag), tag2, tag3, tag4, tag5;
<<<<<<< HEAD
		bool is_list = FALSE;
		bool has_parent = FALSE;
=======
		bool is_list = false;
		bool has_parent = false;
>>>>>>> upstream/master

		int separator1 = tag1.find_first_of('%');
		if (separator1 != -1)
		{
<<<<<<< HEAD
			is_list = TRUE;
=======
			is_list = true;
>>>>>>> upstream/master

			// we are loading through softlists, split the listname from the regiontag
			tag4.assign(tag1.substr(separator1 + 1, tag1.length() - separator1 + 1));
			tag1.erase(separator1, tag1.length() - separator1);
			tag1.append(PATH_SEPARATOR);

			// check if we are loading a clone (if this is the case also tag1 have a separator '%')
			int separator2 = tag4.find_first_of('%');
			if (separator2 != -1)
			{
<<<<<<< HEAD
				has_parent = TRUE;
=======
				has_parent = true;
>>>>>>> upstream/master

				// we are loading a clone through softlists, split the setname from the parentname
				tag5.assign(tag4.substr(separator2 + 1, tag4.length() - separator2 + 1));
				tag4.erase(separator2, tag4.length() - separator2);
			}

			// prepare locations where we have to load from: list/parentname & list/clonename
			std::string swlist(tag1);
			tag2.assign(swlist.append(tag4));
			if (has_parent)
			{
				swlist.assign(tag1);
				tag3.assign(swlist.append(tag5));
			}
		}

		if (tag5.find_first_of('%') != -1)
			fatalerror("We do not support clones of clones!\n");

		// try to load from the available location(s):
		// - if we are not using lists, we have regiontag only;
		// - if we are using lists, we have: list/clonename, list/parentname, clonename, parentname
		if (!is_list)
		{
			tried_file_names += " " + tag1;
<<<<<<< HEAD
			filerr = common_process_file(romdata->machine().options(), tag1.c_str(), has_crc, crc, romp, &romdata->file);
=======
			m_file = common_process_file(machine().options(), tag1.c_str(), has_crc, crc, romp, filerr);
>>>>>>> upstream/master
		}
		else
		{
			// try to load from list/setname
<<<<<<< HEAD
			if ((romdata->file == NULL) && (tag2.c_str() != NULL))
			{
				tried_file_names += " " + tag2;
				filerr = common_process_file(romdata->machine().options(), tag2.c_str(), has_crc, crc, romp, &romdata->file);
			}
			// try to load from list/parentname
			if ((romdata->file == NULL) && has_parent && (tag3.c_str() != NULL))
			{
				tried_file_names += " " + tag3;
				filerr = common_process_file(romdata->machine().options(), tag3.c_str(), has_crc, crc, romp, &romdata->file);
			}
			// try to load from setname
			if ((romdata->file == NULL) && (tag4.c_str() != NULL))
			{
				tried_file_names += " " + tag4;
				filerr = common_process_file(romdata->machine().options(), tag4.c_str(), has_crc, crc, romp, &romdata->file);
			}
			// try to load from parentname
			if ((romdata->file == NULL) && has_parent && (tag5.c_str() != NULL))
			{
				tried_file_names += " " + tag5;
				filerr = common_process_file(romdata->machine().options(), tag5.c_str(), has_crc, crc, romp, &romdata->file);
=======
			if ((m_file == nullptr) && (tag2.c_str() != nullptr))
			{
				tried_file_names += " " + tag2;
				m_file = common_process_file(machine().options(), tag2.c_str(), has_crc, crc, romp, filerr);
			}
			// try to load from list/parentname
			if ((m_file == nullptr) && has_parent && (tag3.c_str() != nullptr))
			{
				tried_file_names += " " + tag3;
				m_file = common_process_file(machine().options(), tag3.c_str(), has_crc, crc, romp, filerr);
			}
			// try to load from setname
			if ((m_file == nullptr) && (tag4.c_str() != nullptr))
			{
				tried_file_names += " " + tag4;
				m_file = common_process_file(machine().options(), tag4.c_str(), has_crc, crc, romp, filerr);
			}
			// try to load from parentname
			if ((m_file == nullptr) && has_parent && (tag5.c_str() != nullptr))
			{
				tried_file_names += " " + tag5;
				m_file = common_process_file(machine().options(), tag5.c_str(), has_crc, crc, romp, filerr);
>>>>>>> upstream/master
			}
		}
	}

	/* update counters */
<<<<<<< HEAD
	romdata->romsloaded++;
	romdata->romsloadedsize += romsize;

	/* return the result */
	return (filerr == FILERR_NONE);
=======
	m_romsloaded++;
	m_romsloadedsize += romsize;

	/* return the result */
	return (filerr == osd_file::error::NONE);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    rom_fread - cheesy fread that fills with
<<<<<<< HEAD
    random data for a NULL file
-------------------------------------------------*/

static int rom_fread(romload_private *romdata, UINT8 *buffer, int length, const rom_entry *parent_region)
{
	int result = length;

	/* files just pass through */
	if (romdata->file != NULL)
		result = romdata->file->read(buffer, length);

	/* otherwise, fill with randomness unless it was already specifically erased */
	else if (!ROMREGION_ISERASE(parent_region))
		fill_random(romdata->machine(), buffer, length);

#ifdef USE_IPS
	if (romdata->patch)
		apply_ips_patch(romdata->patch, buffer, length);
#endif /* USE_IPS */

	return result;
=======
    random data for a nullptr file
-------------------------------------------------*/

int rom_load_manager::rom_fread(u8 *buffer, int length, const rom_entry *parent_region)
{
	/* files just pass through */
	if (m_file != nullptr)
		return m_file->read(buffer, length);

	/* otherwise, fill with randomness unless it was already specifically erased */
	else if (!ROMREGION_ISERASE(parent_region))
		fill_random(buffer, length);

	return length;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    read_rom_data - read ROM data for a single
    entry
-------------------------------------------------*/

<<<<<<< HEAD
static int read_rom_data(romload_private *romdata, const rom_entry *parent_region, const rom_entry *romp)
=======
int rom_load_manager::read_rom_data(const rom_entry *parent_region, const rom_entry *romp)
>>>>>>> upstream/master
{
	int datashift = ROM_GETBITSHIFT(romp);
	int datamask = ((1 << ROM_GETBITWIDTH(romp)) - 1) << datashift;
	int numbytes = ROM_GETLENGTH(romp);
	int groupsize = ROM_GETGROUPSIZE(romp);
	int skip = ROM_GETSKIPCOUNT(romp);
	int reversed = ROM_ISREVERSED(romp);
	int numgroups = (numbytes + groupsize - 1) / groupsize;
<<<<<<< HEAD
	UINT8 *base = romdata->region->base() + ROM_GETOFFSET(romp);
	UINT32 tempbufsize;
	int i;

	LOG(("Loading ROM data: offs=%X len=%X mask=%02X group=%d skip=%d reverse=%d\n", ROM_GETOFFSET(romp), numbytes, datamask, groupsize, skip, reversed));
=======
	u8 *base = m_region->base() + ROM_GETOFFSET(romp);
	u32 tempbufsize;
	int i;

	LOG("Loading ROM data: offs=%X len=%X mask=%02X group=%d skip=%d reverse=%d\n", ROM_GETOFFSET(romp), numbytes, datamask, groupsize, skip, reversed);
>>>>>>> upstream/master

	/* make sure the length was an even multiple of the group size */
	if (numbytes % groupsize != 0)
		osd_printf_warning("Warning in RomModule definition: %s length not an even multiple of group size\n", ROM_GETNAME(romp));

	/* make sure we only fill within the region space */
<<<<<<< HEAD
	if (ROM_GETOFFSET(romp) + numgroups * groupsize + (numgroups - 1) * skip > romdata->region->bytes())
=======
	if (ROM_GETOFFSET(romp) + numgroups * groupsize + (numgroups - 1) * skip > m_region->bytes())
>>>>>>> upstream/master
		fatalerror("Error in RomModule definition: %s out of memory region space\n", ROM_GETNAME(romp));

	/* make sure the length was valid */
	if (numbytes == 0)
		fatalerror("Error in RomModule definition: %s has an invalid length\n", ROM_GETNAME(romp));

	/* special case for simple loads */
	if (datamask == 0xff && (groupsize == 1 || !reversed) && skip == 0)
<<<<<<< HEAD
		return rom_fread(romdata, base, numbytes, parent_region);

	/* use a temporary buffer for complex loads */
	tempbufsize = MIN(TEMPBUFFER_MAX_SIZE, numbytes);
	dynamic_buffer tempbuf(tempbufsize);
=======
		return rom_fread(base, numbytes, parent_region);

	/* use a temporary buffer for complex loads */
	tempbufsize = std::min(TEMPBUFFER_MAX_SIZE, numbytes);
	std::vector<u8> tempbuf(tempbufsize);
>>>>>>> upstream/master

	/* chunky reads for complex loads */
	skip += groupsize;
	while (numbytes > 0)
	{
		int evengroupcount = (tempbufsize / groupsize) * groupsize;
		int bytesleft = (numbytes > evengroupcount) ? evengroupcount : numbytes;
<<<<<<< HEAD
		UINT8 *bufptr = &tempbuf[0];

		/* read as much as we can */
		LOG(("  Reading %X bytes into buffer\n", bytesleft));
		if (rom_fread(romdata, bufptr, bytesleft, parent_region) != bytesleft)
			return 0;
		numbytes -= bytesleft;

		LOG(("  Copying to %p\n", base));
=======
		u8 *bufptr = &tempbuf[0];

		/* read as much as we can */
		LOG("  Reading %X bytes into buffer\n", bytesleft);
		if (rom_fread(bufptr, bytesleft, parent_region) != bytesleft)
			return 0;
		numbytes -= bytesleft;

		LOG("  Copying to %p\n", base);
>>>>>>> upstream/master

		/* unmasked cases */
		if (datamask == 0xff)
		{
			/* non-grouped data */
			if (groupsize == 1)
				for (i = 0; i < bytesleft; i++, base += skip)
					*base = *bufptr++;

			/* grouped data -- non-reversed case */
			else if (!reversed)
				while (bytesleft)
				{
					for (i = 0; i < groupsize && bytesleft; i++, bytesleft--)
						base[i] = *bufptr++;
					base += skip;
				}

			/* grouped data -- reversed case */
			else
				while (bytesleft)
				{
					for (i = groupsize - 1; i >= 0 && bytesleft; i--, bytesleft--)
						base[i] = *bufptr++;
					base += skip;
				}
		}

		/* masked cases */
		else
		{
			/* non-grouped data */
			if (groupsize == 1)
				for (i = 0; i < bytesleft; i++, base += skip)
					*base = (*base & ~datamask) | ((*bufptr++ << datashift) & datamask);

			/* grouped data -- non-reversed case */
			else if (!reversed)
				while (bytesleft)
				{
					for (i = 0; i < groupsize && bytesleft; i++, bytesleft--)
						base[i] = (base[i] & ~datamask) | ((*bufptr++ << datashift) & datamask);
					base += skip;
				}

			/* grouped data -- reversed case */
			else
				while (bytesleft)
				{
					for (i = groupsize - 1; i >= 0 && bytesleft; i--, bytesleft--)
						base[i] = (base[i] & ~datamask) | ((*bufptr++ << datashift) & datamask);
					base += skip;
				}
		}
	}

<<<<<<< HEAD
	LOG(("  All done\n"));
=======
	LOG("  All done\n");
>>>>>>> upstream/master
	return ROM_GETLENGTH(romp);
}


/*-------------------------------------------------
    fill_rom_data - fill a region of ROM space
-------------------------------------------------*/

<<<<<<< HEAD
static void fill_rom_data(romload_private *romdata, const rom_entry *romp)
{
	UINT32 numbytes = ROM_GETLENGTH(romp);
	UINT8 *base = romdata->region->base() + ROM_GETOFFSET(romp);

	/* make sure we fill within the region space */
	if (ROM_GETOFFSET(romp) + numbytes > romdata->region->bytes())
		fatalerror("Error in RomModule definition: FILL out of memory region space\n");

	/* make sure the length was valid */
	if (numbytes == 0)
		fatalerror("Error in RomModule definition: FILL has an invalid length\n");

	/* fill the data (filling value is stored in place of the hashdata) */
	memset(base, (FPTR)ROM_GETHASHDATA(romp) & 0xff, numbytes);
=======
void rom_load_manager::fill_rom_data(const rom_entry *romp)
{
	u32 numbytes = ROM_GETLENGTH(romp);
	int skip = ROM_GETSKIPCOUNT(romp);
	u8 *base = m_region->base() + ROM_GETOFFSET(romp);

	// make sure we fill within the region space
	if (ROM_GETOFFSET(romp) + numbytes > m_region->bytes())
		fatalerror("Error in RomModule definition: FILL out of memory region space\n");

	// make sure the length was valid
	if (numbytes == 0)
		fatalerror("Error in RomModule definition: FILL has an invalid length\n");

	// for fill bytes, the byte that gets filled is the first byte of the hashdata string
	u8 fill_byte = u8(strtol(ROM_GETHASHDATA(romp), nullptr, 0));

	// fill the data (filling value is stored in place of the hashdata)
	if(skip != 0)
	{
		for (int i = 0; i < numbytes; i+= skip + 1)
			base[i] = fill_byte;
	}
	else
		memset(base, fill_byte, numbytes);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    copy_rom_data - copy a region of ROM space
-------------------------------------------------*/

<<<<<<< HEAD
static void copy_rom_data(romload_private *romdata, const rom_entry *romp)
{
	UINT8 *base = romdata->region->base() + ROM_GETOFFSET(romp);
	const char *srcrgntag = ROM_GETNAME(romp);
	UINT32 numbytes = ROM_GETLENGTH(romp);
	UINT32 srcoffs = (FPTR)ROM_GETHASHDATA(romp);  /* srcoffset in place of hashdata */

	/* make sure we copy within the region space */
	if (ROM_GETOFFSET(romp) + numbytes > romdata->region->bytes())
=======
void rom_load_manager::copy_rom_data(const rom_entry *romp)
{
	u8 *base = m_region->base() + ROM_GETOFFSET(romp);
	const char *srcrgntag = ROM_GETNAME(romp);
	u32 numbytes = ROM_GETLENGTH(romp);
	u32 srcoffs = u32(strtol(ROM_GETHASHDATA(romp), nullptr, 0));  /* srcoffset in place of hashdata */

	/* make sure we copy within the region space */
	if (ROM_GETOFFSET(romp) + numbytes > m_region->bytes())
>>>>>>> upstream/master
		fatalerror("Error in RomModule definition: COPY out of target memory region space\n");

	/* make sure the length was valid */
	if (numbytes == 0)
		fatalerror("Error in RomModule definition: COPY has an invalid length\n");

	/* make sure the source was valid */
<<<<<<< HEAD
	memory_region *region = romdata->machine().root_device().memregion(srcrgntag);
	if (region == NULL)
=======
	memory_region *region = machine().root_device().memregion(srcrgntag);
	if (region == nullptr)
>>>>>>> upstream/master
		fatalerror("Error in RomModule definition: COPY from an invalid region\n");

	/* make sure we find within the region space */
	if (srcoffs + numbytes > region->bytes())
		fatalerror("Error in RomModule definition: COPY out of source memory region space\n");

	/* fill the data */
	memcpy(base, region->base() + srcoffs, numbytes);
}


/*-------------------------------------------------
    process_rom_entries - process all ROM entries
    for a region
-------------------------------------------------*/

<<<<<<< HEAD
static void process_rom_entries(romload_private *romdata, const char *regiontag, const rom_entry *parent_region, const rom_entry *romp, device_t *device, bool from_list)
{
	UINT32 lastflags = 0;
=======
void rom_load_manager::process_rom_entries(const char *regiontag, const rom_entry *parent_region, const rom_entry *romp, device_t *device, bool from_list)
{
	u32 lastflags = 0;
>>>>>>> upstream/master

	/* loop until we hit the end of this region */
	while (!ROMENTRY_ISREGIONEND(romp))
	{
		/* if this is a continue entry, it's invalid */
		if (ROMENTRY_ISCONTINUE(romp))
			fatalerror("Error in RomModule definition: ROM_CONTINUE not preceded by ROM_LOAD\n");

		/* if this is an ignore entry, it's invalid */
		if (ROMENTRY_ISIGNORE(romp))
			fatalerror("Error in RomModule definition: ROM_IGNORE not preceded by ROM_LOAD\n");

		/* if this is a reload entry, it's invalid */
		if (ROMENTRY_ISRELOAD(romp))
			fatalerror("Error in RomModule definition: ROM_RELOAD not preceded by ROM_LOAD\n");

		/* handle fills */
		if (ROMENTRY_ISFILL(romp))
<<<<<<< HEAD
			fill_rom_data(romdata, romp++);

		/* handle copies */
		else if (ROMENTRY_ISCOPY(romp))
			copy_rom_data(romdata, romp++);
=======
			fill_rom_data(romp++);

		/* handle copies */
		else if (ROMENTRY_ISCOPY(romp))
			copy_rom_data(romp++);
>>>>>>> upstream/master

		/* handle files */
		else if (ROMENTRY_ISFILE(romp))
		{
			int irrelevantbios = (ROM_GETBIOSFLAGS(romp) != 0 && ROM_GETBIOSFLAGS(romp) != device->system_bios());
			const rom_entry *baserom = romp;
			int explength = 0;

			/* open the file if it is a non-BIOS or matches the current BIOS */
<<<<<<< HEAD
			LOG(("Opening ROM file: %s\n", ROM_GETNAME(romp)));
			std::string tried_file_names;
			if (!irrelevantbios && !open_rom_file(romdata, regiontag, romp, tried_file_names, from_list))
				handle_missing_file(romdata, romp, tried_file_names, CHDERR_NONE);
=======
			LOG("Opening ROM file: %s\n", ROM_GETNAME(romp));
			std::string tried_file_names;
			if (!irrelevantbios && !open_rom_file(regiontag, romp, tried_file_names, from_list))
				handle_missing_file(romp, tried_file_names, CHDERR_NONE);
>>>>>>> upstream/master

			/* loop until we run out of reloads */
			do
			{
				/* loop until we run out of continues/ignores */
				do
				{
					rom_entry modified_romp = *romp++;
					//int readresult;

					/* handle flag inheritance */
					if (!ROM_INHERITSFLAGS(&modified_romp))
<<<<<<< HEAD
						lastflags = modified_romp._flags;
					else
						modified_romp._flags = (modified_romp._flags & ~ROM_INHERITEDFLAGS) | lastflags;
=======
						lastflags = modified_romp.flags();
					else
						modified_romp.set_flags((modified_romp.flags() & ~ROM_INHERITEDFLAGS) | lastflags);
>>>>>>> upstream/master

					explength += ROM_GETLENGTH(&modified_romp);

					/* attempt to read using the modified entry */
					if (!ROMENTRY_ISIGNORE(&modified_romp) && !irrelevantbios)
<<<<<<< HEAD
						/*readresult = */read_rom_data(romdata, parent_region, &modified_romp);
=======
						/*readresult = */read_rom_data(parent_region, &modified_romp);
>>>>>>> upstream/master
				}
				while (ROMENTRY_ISCONTINUE(romp) || ROMENTRY_ISIGNORE(romp));

				/* if this was the first use of this file, verify the length and CRC */
				if (baserom)
				{
<<<<<<< HEAD
					LOG(("Verifying length (%X) and checksums\n", explength));
					verify_length_and_hash(romdata, ROM_GETNAME(baserom), explength, hash_collection(ROM_GETHASHDATA(baserom)));
					LOG(("Verify finished\n"));
				}

				/* reseek to the start and clear the baserom so we don't reverify */
				if (romdata->file != NULL)
					romdata->file->seek(0, SEEK_SET);
				baserom = NULL;
=======
					LOG("Verifying length (%X) and checksums\n", explength);
					verify_length_and_hash(ROM_GETNAME(baserom), explength, util::hash_collection(ROM_GETHASHDATA(baserom)));
					LOG("Verify finished\n");
				}

				/* reseek to the start and clear the baserom so we don't reverify */
				if (m_file != nullptr)
					m_file->seek(0, SEEK_SET);
				baserom = nullptr;
>>>>>>> upstream/master
				explength = 0;
			}
			while (ROMENTRY_ISRELOAD(romp));

			/* close the file */
<<<<<<< HEAD
			if (romdata->file != NULL)
			{
				LOG(("Closing ROM file\n"));
				global_free(romdata->file);
				romdata->file = NULL;
=======
			if (m_file != nullptr)
			{
				LOG("Closing ROM file\n");
				m_file = nullptr;
>>>>>>> upstream/master
			}
		}
		else
		{
			romp++; /* something else; skip */
		}
	}
}


/*-------------------------------------------------
    open_disk_image - open a disk image,
    searching up the parent and loading by
    checksum
-------------------------------------------------*/

int open_disk_image(emu_options &options, const game_driver *gamedrv, const rom_entry *romp, chd_file &image_chd, const char *locationtag)
{
	emu_file image_file(options.media_path(), OPEN_FLAG_READ);
	const rom_entry *region, *rom;
<<<<<<< HEAD
	file_error filerr;
	chd_error err;

	/* attempt to open the properly named file, scanning up through parent directories */
	filerr = FILERR_NOT_FOUND;
	for (int searchdrv = driver_list::find(*gamedrv); searchdrv != -1 && filerr != FILERR_NONE; searchdrv = driver_list::clone(searchdrv))
		filerr = common_process_file(options, driver_list::driver(searchdrv).name, ".chd", romp, image_file);

	if (filerr != FILERR_NONE)
		filerr = common_process_file(options, NULL, ".chd", romp, image_file);

	/* look for the disk in the locationtag too */
	if (filerr != FILERR_NONE && locationtag != NULL)
=======
	osd_file::error filerr;
	chd_error err;

	/* attempt to open the properly named file, scanning up through parent directories */
	filerr = osd_file::error::NOT_FOUND;
	for (int searchdrv = driver_list::find(*gamedrv); searchdrv != -1 && filerr != osd_file::error::NONE; searchdrv = driver_list::clone(searchdrv))
		filerr = common_process_file(options, driver_list::driver(searchdrv).name, ".chd", romp, image_file);

	if (filerr != osd_file::error::NONE)
		filerr = common_process_file(options, nullptr, ".chd", romp, image_file);

	/* look for the disk in the locationtag too */
	if (filerr != osd_file::error::NONE && locationtag != nullptr)
>>>>>>> upstream/master
	{
		// check if we are dealing with softwarelists. if so, locationtag
		// is actually a concatenation of: listname + setname + parentname
		// separated by '%' (parentname being present only for clones)
		std::string tag1(locationtag), tag2, tag3, tag4, tag5;
<<<<<<< HEAD
		bool is_list = FALSE;
		bool has_parent = FALSE;
=======
		bool is_list = false;
		bool has_parent = false;
>>>>>>> upstream/master

		int separator1 = tag1.find_first_of('%');
		if (separator1 != -1)
		{
<<<<<<< HEAD
			is_list = TRUE;
=======
			is_list = true;
>>>>>>> upstream/master

			// we are loading through softlists, split the listname from the regiontag
			tag4.assign(tag1.substr(separator1 + 1, tag1.length() - separator1 + 1));
			tag1.erase(separator1, tag1.length() - separator1);
			tag1.append(PATH_SEPARATOR);

			// check if we are loading a clone (if this is the case also tag1 have a separator '%')
			int separator2 = tag4.find_first_of('%');
			if (separator2 != -1)
			{
<<<<<<< HEAD
				has_parent = TRUE;
=======
				has_parent = true;
>>>>>>> upstream/master

				// we are loading a clone through softlists, split the setname from the parentname
				tag5.assign(tag4.substr(separator2 + 1, tag4.length() - separator2 + 1));
				tag4.erase(separator2, tag4.length() - separator2);
			}

			// prepare locations where we have to load from: list/parentname (if any) & list/clonename
			std::string swlist(tag1);
			tag2.assign(swlist.append(tag4));
			if (has_parent)
			{
				swlist.assign(tag1);
				tag3.assign(swlist.append(tag5));
			}
		}

		if (tag5.find_first_of('%') != -1)
			fatalerror("We do not support clones of clones!\n");

		// try to load from the available location(s):
		// - if we are not using lists, we have locationtag only;
		// - if we are using lists, we have: list/clonename, list/parentname, clonename, parentname
		if (!is_list)
			filerr = common_process_file(options, locationtag, ".chd", romp, image_file);
		else
		{
			// try to load from list/setname
<<<<<<< HEAD
			if ((filerr != FILERR_NONE) && (tag2.c_str() != NULL))
				filerr = common_process_file(options, tag2.c_str(), ".chd", romp, image_file);
			// try to load from list/parentname (if any)
			if ((filerr != FILERR_NONE) && has_parent && (tag3.c_str() != NULL))
				filerr = common_process_file(options, tag3.c_str(), ".chd", romp, image_file);
			// try to load from setname
			if ((filerr != FILERR_NONE) && (tag4.c_str() != NULL))
				filerr = common_process_file(options, tag4.c_str(), ".chd", romp, image_file);
			// try to load from parentname (if any)
			if ((filerr != FILERR_NONE) && has_parent && (tag5.c_str() != NULL))
				filerr = common_process_file(options, tag5.c_str(), ".chd", romp, image_file);
			// only for CHD we also try to load from list/
			if ((filerr != FILERR_NONE) && (tag1.c_str() != NULL))
=======
			if ((filerr != osd_file::error::NONE) && (tag2.c_str() != nullptr))
				filerr = common_process_file(options, tag2.c_str(), ".chd", romp, image_file);
			// try to load from list/parentname (if any)
			if ((filerr != osd_file::error::NONE) && has_parent && (tag3.c_str() != nullptr))
				filerr = common_process_file(options, tag3.c_str(), ".chd", romp, image_file);
			// try to load from setname
			if ((filerr != osd_file::error::NONE) && (tag4.c_str() != nullptr))
				filerr = common_process_file(options, tag4.c_str(), ".chd", romp, image_file);
			// try to load from parentname (if any)
			if ((filerr != osd_file::error::NONE) && has_parent && (tag5.c_str() != nullptr))
				filerr = common_process_file(options, tag5.c_str(), ".chd", romp, image_file);
			// only for CHD we also try to load from list/
			if ((filerr != osd_file::error::NONE) && (tag1.c_str() != nullptr))
>>>>>>> upstream/master
			{
				tag1.erase(tag1.length() - 1, 1);    // remove the PATH_SEPARATOR
				filerr = common_process_file(options, tag1.c_str(), ".chd", romp, image_file);
			}
		}
	}

	/* did the file open succeed? */
<<<<<<< HEAD
	if (filerr == FILERR_NONE)
=======
	if (filerr == osd_file::error::NONE)
>>>>>>> upstream/master
	{
		std::string fullpath(image_file.fullpath());
		image_file.close();

		/* try to open the CHD */
		err = image_chd.open(fullpath.c_str());
		if (err == CHDERR_NONE)
			return err;
	}
	else
		err = CHDERR_FILE_NOT_FOUND;

<<<<<<< HEAD
	/* otherwise, look at our parents for a CHD with an identical checksum */
	/* and try to open that */
	hash_collection romphashes(ROM_GETHASHDATA(romp));
	for (int drv = driver_list::find(*gamedrv); drv != -1; drv = driver_list::clone(drv))
	{
		machine_config config(driver_list::driver(drv), options);
		device_iterator deviter(config.root_device());
		for (device_t *device = deviter.first(); device != NULL; device = deviter.next())
			for (region = rom_first_region(*device); region != NULL; region = rom_next_region(region))
				if (ROMREGION_ISDISKDATA(region))
					for (rom = rom_first_file(region); rom != NULL; rom = rom_next_file(rom))

						/* look for a differing name but with the same hash data */
						if (strcmp(ROM_GETNAME(romp), ROM_GETNAME(rom)) != 0 &&
							romphashes == hash_collection(ROM_GETHASHDATA(rom)))
						{
							/* attempt to open the properly named file, scanning up through parent directories */
							filerr = FILERR_NOT_FOUND;
							for (int searchdrv = drv; searchdrv != -1 && filerr != FILERR_NONE; searchdrv = driver_list::clone(searchdrv))
								filerr = common_process_file(options, driver_list::driver(searchdrv).name, ".chd", rom, image_file);

							if (filerr != FILERR_NONE)
								filerr = common_process_file(options, NULL, ".chd", rom, image_file);

							/* did the file open succeed? */
							if (filerr == FILERR_NONE)
=======
	// Otherwise, look at our parents for a CHD with an identical checksum
	// and try to open that
	//
	// An example of a system that requires this is src/mame/drivers/ksys673.cpp, that has declarations like this:
	//      ...
	//      DISK_IMAGE_READONLY("889aa", 0, BAD_DUMP SHA1(0b567bf2f03ee8089e0b021ea502a53b3f6fe7ac))
	//      ...
	//      DISK_IMAGE_READONLY("889ea", 0, BAD_DUMP SHA1(0b567bf2f03ee8089e0b021ea502a53b3f6fe7ac))
	//      ...
	//      DISK_IMAGE_READONLY("889ja", 0, BAD_DUMP SHA1(0b567bf2f03ee8089e0b021ea502a53b3f6fe7ac))
	//      ...
	//      DISK_IMAGE_READONLY("889ua", 0, BAD_DUMP SHA1(0b567bf2f03ee8089e0b021ea502a53b3f6fe7ac))
	//      ...
	util::hash_collection romphashes(ROM_GETHASHDATA(romp));
	for (int drv = driver_list::find(*gamedrv); drv != -1; drv = driver_list::clone(drv))
	{
		const game_driver &current_driver(driver_list::driver(drv));

		// Create a single use emu_option structure for the purposes of this lookup, just
		// carrying forward the options that are necessary for CHD lookup.  This is because the
		// options passed to us may have slot/image configurations that are "poisonous" for these
		// other drivers
		//
		// A side effect of this approach is that the "dragnet" to find CHDs with identical hashes
		// will only find CHDs for the default configuration.  I believe that this in practice will
		// be acceptable.
		emu_options driver_specific_options;
		driver_specific_options.set_system_name(current_driver.name);
		driver_specific_options.set_value(OPTION_MEDIAPATH, options.media_path(), OPTION_PRIORITY_DEFAULT);
		driver_specific_options.set_value(OPTION_DIFF_DIRECTORY, options.diff_directory(), OPTION_PRIORITY_DEFAULT);

		// Now that we have an emu_options structure properly set up, we can create a machine_config
		machine_config config(current_driver, driver_specific_options);

		for (device_t &device : device_iterator(config.root_device()))
			for (region = rom_first_region(device); region != nullptr; region = rom_next_region(region))
				if (ROMREGION_ISDISKDATA(region))
					for (rom = rom_first_file(region); rom != nullptr; rom = rom_next_file(rom))

						// Look for a differing name but with the same hash data
						if (strcmp(ROM_GETNAME(romp), ROM_GETNAME(rom)) != 0 &&
							romphashes == util::hash_collection(ROM_GETHASHDATA(rom)))
						{
							// Attempt to open the properly named file, scanning up through parent directories
							filerr = osd_file::error::NOT_FOUND;
							for (int searchdrv = drv; searchdrv != -1 && filerr != osd_file::error::NONE; searchdrv = driver_list::clone(searchdrv))
								filerr = common_process_file(driver_specific_options, driver_list::driver(searchdrv).name, ".chd", rom, image_file);

							if (filerr != osd_file::error::NONE)
								filerr = common_process_file(driver_specific_options, nullptr, ".chd", rom, image_file);

							// Did the file open succeed?
							if (filerr == osd_file::error::NONE)
>>>>>>> upstream/master
							{
								std::string fullpath(image_file.fullpath());
								image_file.close();

<<<<<<< HEAD
								/* try to open the CHD */
=======
								// try to open the CHD
>>>>>>> upstream/master
								err = image_chd.open(fullpath.c_str());
								if (err == CHDERR_NONE)
									return err;
							}
						}
	}
	return err;
}


/*-------------------------------------------------
    open_disk_diff - open a DISK diff file
-------------------------------------------------*/

<<<<<<< HEAD
static chd_error open_disk_diff(emu_options &options, const rom_entry *romp, chd_file &source, chd_file &diff_chd)
=======
chd_error rom_load_manager::open_disk_diff(emu_options &options, const rom_entry *romp, chd_file &source, chd_file &diff_chd)
>>>>>>> upstream/master
{
	std::string fname = std::string(ROM_GETNAME(romp)).append(".dif");

	/* try to open the diff */
<<<<<<< HEAD
	LOG(("Opening differencing image file: %s\n", fname.c_str()));
	emu_file diff_file(options.diff_directory(), OPEN_FLAG_READ | OPEN_FLAG_WRITE);
	file_error filerr = diff_file.open(fname.c_str());
	if (filerr == FILERR_NONE)
=======
	LOG("Opening differencing image file: %s\n", fname.c_str());
	emu_file diff_file(options.diff_directory(), OPEN_FLAG_READ | OPEN_FLAG_WRITE);
	osd_file::error filerr = diff_file.open(fname.c_str());
	if (filerr == osd_file::error::NONE)
>>>>>>> upstream/master
	{
		std::string fullpath(diff_file.fullpath());
		diff_file.close();

<<<<<<< HEAD
		LOG(("Opening differencing image file: %s\n", fullpath.c_str()));
=======
		LOG("Opening differencing image file: %s\n", fullpath.c_str());
>>>>>>> upstream/master
		return diff_chd.open(fullpath.c_str(), true, &source);
	}

	/* didn't work; try creating it instead */
<<<<<<< HEAD
	LOG(("Creating differencing image: %s\n", fname.c_str()));
	diff_file.set_openflags(OPEN_FLAG_READ | OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS);
	filerr = diff_file.open(fname.c_str());
	if (filerr == FILERR_NONE)
=======
	LOG("Creating differencing image: %s\n", fname.c_str());
	diff_file.set_openflags(OPEN_FLAG_READ | OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS);
	filerr = diff_file.open(fname.c_str());
	if (filerr == osd_file::error::NONE)
>>>>>>> upstream/master
	{
		std::string fullpath(diff_file.fullpath());
		diff_file.close();

		/* create the CHD */
<<<<<<< HEAD
		LOG(("Creating differencing image file: %s\n", fullpath.c_str()));
=======
		LOG("Creating differencing image file: %s\n", fullpath.c_str());
>>>>>>> upstream/master
		chd_codec_type compression[4] = { CHD_CODEC_NONE };
		chd_error err = diff_chd.create(fullpath.c_str(), source.logical_bytes(), source.hunk_bytes(), compression, source);
		if (err != CHDERR_NONE)
			return err;

		return diff_chd.clone_all_metadata(source);
	}

	return CHDERR_FILE_NOT_FOUND;
}


/*-------------------------------------------------
    process_disk_entries - process all disk entries
    for a region
-------------------------------------------------*/

<<<<<<< HEAD
static void process_disk_entries(romload_private *romdata, const char *regiontag, const rom_entry *parent_region, const rom_entry *romp, const char *locationtag)
=======
void rom_load_manager::process_disk_entries(const char *regiontag, const rom_entry *parent_region, const rom_entry *romp, const char *locationtag)
>>>>>>> upstream/master
{
	/* loop until we hit the end of this region */
	for ( ; !ROMENTRY_ISREGIONEND(romp); romp++)
	{
		/* handle files */
		if (ROMENTRY_ISFILE(romp))
		{
<<<<<<< HEAD
			open_chd *chd = global_alloc(open_chd(regiontag));

			hash_collection hashes(ROM_GETHASHDATA(romp));
=======
			auto chd = std::make_unique<open_chd>(regiontag);

			util::hash_collection hashes(ROM_GETHASHDATA(romp));
>>>>>>> upstream/master
			chd_error err;

			/* make the filename of the source */
			std::string filename = std::string(ROM_GETNAME(romp)).append(".chd");

			/* first open the source drive */
<<<<<<< HEAD
			LOG(("Opening disk image: %s\n", filename.c_str()));
			err = chd_error(open_disk_image(romdata->machine().options(), &romdata->machine().system(), romp, chd->orig_chd(), locationtag));
			if (err != CHDERR_NONE)
			{
				handle_missing_file(romdata, romp, std::string(), err);
				global_free(chd);
=======
			LOG("Opening disk image: %s\n", filename.c_str());
			err = chd_error(open_disk_image(machine().options(), &machine().system(), romp, chd->orig_chd(), locationtag));
			if (err != CHDERR_NONE)
			{
				handle_missing_file(romp, std::string(), err);
				chd = nullptr;
>>>>>>> upstream/master
				continue;
			}

			/* get the header and extract the SHA1 */
<<<<<<< HEAD
			hash_collection acthashes;
=======
			util::hash_collection acthashes;
>>>>>>> upstream/master
			acthashes.add_sha1(chd->orig_chd().sha1());

			/* verify the hash */
			if (hashes != acthashes)
			{
<<<<<<< HEAD
				strcatprintf(romdata->errorstring, _("%s WRONG CHECKSUMS:\n"), filename.c_str());
				dump_wrong_and_correct_checksums(romdata, hashes, acthashes);
				romdata->warnings++;
			}
			else if (hashes.flag(hash_collection::FLAG_BAD_DUMP))
			{
				strcatprintf(romdata->errorstring, _("%s CHD NEEDS REDUMP\n"), filename.c_str());
				romdata->knownbad++;
=======
				m_errorstring.append(string_format("%s WRONG CHECKSUMS:\n", filename));
				dump_wrong_and_correct_checksums(hashes, acthashes);
				m_warnings++;
			}
			else if (hashes.flag(util::hash_collection::FLAG_BAD_DUMP))
			{
				m_errorstring.append(string_format("%s CHD NEEDS REDUMP\n", filename));
				m_knownbad++;
>>>>>>> upstream/master
			}

			/* if not read-only, make the diff file */
			if (!DISK_ISREADONLY(romp))
			{
				/* try to open or create the diff */
<<<<<<< HEAD
				err = open_disk_diff(romdata->machine().options(), romp, chd->orig_chd(), chd->diff_chd());
				if (err != CHDERR_NONE)
				{
					strcatprintf(romdata->errorstring, _("%s DIFF CHD ERROR: %s\n"), filename.c_str(), chd_file::error_string(err));
					romdata->errors++;
					global_free(chd);
=======
				err = open_disk_diff(machine().options(), romp, chd->orig_chd(), chd->diff_chd());
				if (err != CHDERR_NONE)
				{
					m_errorstring.append(string_format("%s DIFF CHD ERROR: %s\n", filename, chd_file::error_string(err)));
					m_errors++;
					chd = nullptr;
>>>>>>> upstream/master
					continue;
				}
			}

			/* we're okay, add to the list of disks */
<<<<<<< HEAD
			LOG(("Assigning to handle %d\n", DISK_GETINDEX(romp)));
			romdata->machine().romload_data->chd_list.append(*chd);
=======
			LOG("Assigning to handle %d\n", DISK_GETINDEX(romp));
			m_chd_list.push_back(std::move(chd));
>>>>>>> upstream/master
		}
	}
}


/*-------------------------------------------------
    normalize_flags_for_device - modify the region
    flags for the given device
-------------------------------------------------*/

<<<<<<< HEAD
static void normalize_flags_for_device(running_machine &machine, const char *rgntag, UINT8 &width, endianness_t &endian)
=======
void rom_load_manager::normalize_flags_for_device(running_machine &machine, const char *rgntag, u8 &width, endianness_t &endian)
>>>>>>> upstream/master
{
	device_t *device = machine.device(rgntag);
	device_memory_interface *memory;
	if (device->interface(memory))
	{
		const address_space_config *spaceconfig = memory->space_config();
<<<<<<< HEAD
		if (spaceconfig != NULL)
=======
		if (spaceconfig != nullptr)
>>>>>>> upstream/master
		{
			int buswidth;

			/* set the endianness */
			if (spaceconfig->m_endianness == ENDIANNESS_LITTLE)
				endian = ENDIANNESS_LITTLE;
			else
				endian = ENDIANNESS_BIG;

			/* set the width */
			buswidth = spaceconfig->m_databus_width;
			if (buswidth <= 8)
				width = 1;
			else if (buswidth <= 16)
				width = 2;
			else if (buswidth <= 32)
				width = 4;
			else
				width = 8;
		}
	}
}


/*-------------------------------------------------
    load_software_part_region - load a software part

    This is used by MESS when loading a piece of
    software. The code should be merged with
    process_region_list or updated to use a slight
    more general process_region_list.
-------------------------------------------------*/

<<<<<<< HEAD
void load_software_part_region(device_t &device, software_list_device &swlist, const char *swname, const rom_entry *start_region)
{
	std::string locationtag(swlist.list_name()), breakstr("%");
	romload_private *romdata = device.machine().romload_data;
	const rom_entry *region;
	std::string regiontag;

	romdata->errorstring.clear();
	romdata->softwarningstring.clear();

	romdata->romstotal = 0;
	romdata->romstotalsize = 0;
	romdata->romsloadedsize = 0;

	software_info *swinfo = swlist.find(swname);
	if (swinfo != NULL)
	{
		UINT32 supported = swinfo->supported();
		if (supported == SOFTWARE_SUPPORTED_PARTIAL)
		{
			strcatprintf(romdata->errorstring, "WARNING: support for software %s (in list %s) is only partial\n", swname, swlist.list_name());
			strcatprintf(romdata->softwarningstring, "Support for software %s (in list %s) is only partial\n", swname, swlist.list_name());
		}
		if (supported == SOFTWARE_SUPPORTED_NO)
		{
			strcatprintf(romdata->errorstring, "WARNING: support for software %s (in list %s) is only preliminary\n", swname, swlist.list_name());
			strcatprintf(romdata->softwarningstring, "Support for software %s (in list %s) is only preliminary\n", swname, swlist.list_name());
=======
void rom_load_manager::load_software_part_region(device_t &device, software_list_device &swlist, const char *swname, const rom_entry *start_region)
{
	std::string locationtag(swlist.list_name()), breakstr("%");
	const rom_entry *region;
	std::string regiontag;

	m_errorstring.clear();
	m_softwarningstring.clear();

	m_romstotal = 0;
	m_romstotalsize = 0;
	m_romsloadedsize = 0;

	const software_info *swinfo = swlist.find(swname);
	if (swinfo != nullptr)
	{
		u32 supported = swinfo->supported();
		if (supported == SOFTWARE_SUPPORTED_PARTIAL)
		{
			m_errorstring.append(string_format("WARNING: support for software %s (in list %s) is only partial\n", swname, swlist.list_name()));
			m_softwarningstring.append(string_format("Support for software %s (in list %s) is only partial\n", swname, swlist.list_name()));
		}
		if (supported == SOFTWARE_SUPPORTED_NO)
		{
			m_errorstring.append(string_format("WARNING: support for software %s (in list %s) is only preliminary\n", swname, swlist.list_name()));
			m_softwarningstring.append(string_format("Support for software %s (in list %s) is only preliminary\n", swname, swlist.list_name()));
>>>>>>> upstream/master
		}

		// attempt reading up the chain through the parents and create a locationtag std::string in the format
		// " swlist % clonename % parentname "
		// open_rom_file contains the code to split the elements and to create paths to load from

		locationtag.append(breakstr);

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
	}


	/* loop until we hit the end */
<<<<<<< HEAD
	for (region = start_region; region != NULL; region = rom_next_region(region))
	{
		UINT32 regionlength = ROMREGION_GETLENGTH(region);

		regiontag = device.subtag(ROMREGION_GETTAG(region));
		LOG(("Processing region \"%s\" (length=%X)\n", regiontag.c_str(), regionlength));
=======
	for (region = start_region; region != nullptr; region = rom_next_region(region))
	{
		u32 regionlength = ROMREGION_GETLENGTH(region);

		regiontag = device.subtag(ROMREGION_GETTAG(region));
		LOG("Processing region \"%s\" (length=%X)\n", regiontag.c_str(), regionlength);
>>>>>>> upstream/master

		/* the first entry must be a region */
		assert(ROMENTRY_ISREGION(region));

		/* if this is a device region, override with the device width and endianness */
		endianness_t endianness = ROMREGION_ISBIGENDIAN(region) ? ENDIANNESS_BIG : ENDIANNESS_LITTLE;
<<<<<<< HEAD
		UINT8 width = ROMREGION_GETWIDTH(region) / 8;
		memory_region *memregion = romdata->machine().root_device().memregion(regiontag.c_str());
		if (memregion != NULL)
		{
			if (romdata->machine().device(regiontag.c_str()) != NULL)
				normalize_flags_for_device(romdata->machine(), regiontag.c_str(), width, endianness);

			/* clear old region (todo: should be moved to an image unload function) */
			romdata->machine().memory().region_free(memregion->name());
		}

		/* remember the base and length */
		romdata->region = romdata->machine().memory().region_alloc(regiontag.c_str(), regionlength, width, endianness);
		LOG(("Allocated %X bytes @ %p\n", romdata->region->bytes(), romdata->region->base()));

		/* clear the region if it's requested */
		if (ROMREGION_ISERASE(region))
			memset(romdata->region->base(), ROMREGION_GETERASEVAL(region), romdata->region->bytes());

		/* or if it's sufficiently small (<= 4MB) */
		else if (romdata->region->bytes() <= 0x400000)
			memset(romdata->region->base(), 0, romdata->region->bytes());
=======
		u8 width = ROMREGION_GETWIDTH(region) / 8;
		memory_region *memregion = machine().root_device().memregion(regiontag.c_str());
		if (memregion != nullptr)
		{
			if (machine().device(regiontag.c_str()) != nullptr)
				normalize_flags_for_device(machine(), regiontag.c_str(), width, endianness);

			/* clear old region (todo: should be moved to an image unload function) */
			machine().memory().region_free(memregion->name());
		}

		/* remember the base and length */
		m_region = machine().memory().region_alloc(regiontag.c_str(), regionlength, width, endianness);
		LOG("Allocated %X bytes @ %p\n", m_region->bytes(), m_region->base());

		/* clear the region if it's requested */
		if (ROMREGION_ISERASE(region))
			memset(m_region->base(), ROMREGION_GETERASEVAL(region), m_region->bytes());

		/* or if it's sufficiently small (<= 4MB) */
		else if (m_region->bytes() <= 0x400000)
			memset(m_region->base(), 0, m_region->bytes());
>>>>>>> upstream/master

#ifdef MAME_DEBUG
		/* if we're debugging, fill region with random data to catch errors */
		else
<<<<<<< HEAD
			fill_random(romdata->machine(), romdata->region->base(), romdata->region->bytes());
#endif

		/* update total number of roms */
		for (const rom_entry *rom = rom_first_file(region); rom != NULL; rom = rom_next_file(rom))
		{
			romdata->romstotal++;
			romdata->romstotalsize += rom_file_size(rom);
=======
			fill_random(m_region->base(), m_region->bytes());
#endif

		/* update total number of roms */
		for (const rom_entry *rom = rom_first_file(region); rom != nullptr; rom = rom_next_file(rom))
		{
			m_romstotal++;
			m_romstotalsize += rom_file_size(rom);
>>>>>>> upstream/master
		}

		/* now process the entries in the region */
		if (ROMREGION_ISROMDATA(region))
<<<<<<< HEAD
			process_rom_entries(romdata, locationtag.c_str(), region, region + 1, &device, TRUE);
		else if (ROMREGION_ISDISKDATA(region))
			process_disk_entries(romdata, regiontag.c_str(), region, region + 1, locationtag.c_str());
	}

	/* now go back and post-process all the regions */
	for (region = start_region; region != NULL; region = rom_next_region(region))
	{
		regiontag = device.subtag(ROMREGION_GETTAG(region));
		region_post_process(romdata, regiontag.c_str(), ROMREGION_ISINVERTED(region));
	}

	/* display the results and exit */
	display_rom_load_results(romdata, TRUE);
=======
			process_rom_entries(locationtag.c_str(), region, region + 1, &device, true);
		else if (ROMREGION_ISDISKDATA(region))
			process_disk_entries(regiontag.c_str(), region, region + 1, locationtag.c_str());
	}

	/* now go back and post-process all the regions */
	for (region = start_region; region != nullptr; region = rom_next_region(region))
	{
		regiontag = device.subtag(ROMREGION_GETTAG(region));
		region_post_process(regiontag.c_str(), ROMREGION_ISINVERTED(region));
	}

	/* display the results and exit */
	display_rom_load_results(true);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    process_region_list - process a region list
-------------------------------------------------*/

<<<<<<< HEAD
static void process_region_list(romload_private *romdata)
=======
void rom_load_manager::process_region_list()
>>>>>>> upstream/master
{
	std::string regiontag;

	/* loop until we hit the end */
<<<<<<< HEAD
	device_iterator deviter(romdata->machine().root_device());
	for (device_t *device = deviter.first(); device != NULL; device = deviter.next())
		for (const rom_entry *region = rom_first_region(*device); region != NULL; region = rom_next_region(region))
		{
			UINT32 regionlength = ROMREGION_GETLENGTH(region);

			regiontag = rom_region_name(*device, region);
			LOG(("Processing region \"%s\" (length=%X)\n", regiontag.c_str(), regionlength));
=======
	device_iterator deviter(machine().root_device());
	for (device_t &device : deviter)
		for (const rom_entry *region = rom_first_region(device); region != nullptr; region = rom_next_region(region))
		{
			u32 regionlength = ROMREGION_GETLENGTH(region);

			regiontag = rom_region_name(device, region);
			LOG("Processing region \"%s\" (length=%X)\n", regiontag.c_str(), regionlength);
>>>>>>> upstream/master

			/* the first entry must be a region */
			assert(ROMENTRY_ISREGION(region));

			if (ROMREGION_ISROMDATA(region))
			{
				/* if this is a device region, override with the device width and endianness */
<<<<<<< HEAD
				UINT8 width = ROMREGION_GETWIDTH(region) / 8;
				endianness_t endianness = ROMREGION_ISBIGENDIAN(region) ? ENDIANNESS_BIG : ENDIANNESS_LITTLE;
				if (romdata->machine().device(regiontag.c_str()) != NULL)
					normalize_flags_for_device(romdata->machine(), regiontag.c_str(), width, endianness);

				/* remember the base and length */
				romdata->region = romdata->machine().memory().region_alloc(regiontag.c_str(), regionlength, width, endianness);
				LOG(("Allocated %X bytes @ %p\n", romdata->region->bytes(), romdata->region->base()));

				/* clear the region if it's requested */
				if (ROMREGION_ISERASE(region))
					memset(romdata->region->base(), ROMREGION_GETERASEVAL(region), romdata->region->bytes());

				/* or if it's sufficiently small (<= 4MB) */
				else if (romdata->region->bytes() <= 0x400000)
					memset(romdata->region->base(), 0, romdata->region->bytes());
=======
				u8 width = ROMREGION_GETWIDTH(region) / 8;
				endianness_t endianness = ROMREGION_ISBIGENDIAN(region) ? ENDIANNESS_BIG : ENDIANNESS_LITTLE;
				if (machine().device(regiontag.c_str()) != nullptr)
					normalize_flags_for_device(machine(), regiontag.c_str(), width, endianness);

				/* remember the base and length */
				m_region = machine().memory().region_alloc(regiontag.c_str(), regionlength, width, endianness);
				LOG("Allocated %X bytes @ %p\n", m_region->bytes(), m_region->base());

				/* clear the region if it's requested */
				if (ROMREGION_ISERASE(region))
					memset(m_region->base(), ROMREGION_GETERASEVAL(region), m_region->bytes());

				/* or if it's sufficiently small (<= 4MB) */
				else if (m_region->bytes() <= 0x400000)
					memset(m_region->base(), 0, m_region->bytes());
>>>>>>> upstream/master

#ifdef MAME_DEBUG
				/* if we're debugging, fill region with random data to catch errors */
				else
<<<<<<< HEAD
					fill_random(romdata->machine(), romdata->region->base(), romdata->region->bytes());
#endif

				/* now process the entries in the region */
				process_rom_entries(romdata, device->shortname(), region, region + 1, device, FALSE);
			}
			else if (ROMREGION_ISDISKDATA(region))
				process_disk_entries(romdata, regiontag.c_str(), region, region + 1, NULL);
		}

	/* now go back and post-process all the regions */
	for (device_t *device = deviter.first(); device != NULL; device = deviter.next())
		for (const rom_entry *region = rom_first_region(*device); region != NULL; region = rom_next_region(region))
		{
			regiontag = rom_region_name(*device, region);
			region_post_process(romdata, regiontag.c_str(), ROMREGION_ISINVERTED(region));
		}

	/* and finally register all per-game parameters */
	for (device_t *device = deviter.first(); device != NULL; device = deviter.next())
		for (const rom_entry *param = rom_first_parameter(*device); param != NULL; param = rom_next_parameter(param))
		{
			regiontag = rom_parameter_name(*device, param);
			romdata->machine().parameters().add(regiontag, rom_parameter_value(param));
=======
					fill_random(m_region->base(), m_region->bytes());
#endif

				/* now process the entries in the region */
				process_rom_entries(device.shortname(), region, region + 1, &device, false);
			}
			else if (ROMREGION_ISDISKDATA(region))
				process_disk_entries(regiontag.c_str(), region, region + 1, nullptr);
		}

	/* now go back and post-process all the regions */
	for (device_t &device : deviter)
		for (const rom_entry *region = rom_first_region(device); region != nullptr; region = rom_next_region(region))
		{
			regiontag = rom_region_name(device, region);
			region_post_process(regiontag.c_str(), ROMREGION_ISINVERTED(region));
		}

	/* and finally register all per-game parameters */
	for (device_t &device : deviter)
		for (const rom_entry *param = rom_first_parameter(device); param != nullptr; param = rom_next_parameter(param))
		{
			regiontag = rom_parameter_name(device, param);
			machine().parameters().add(regiontag, rom_parameter_value(param));
>>>>>>> upstream/master
		}
}


/*-------------------------------------------------
    rom_init - load the ROMs and open the disk
    images associated with the given machine
-------------------------------------------------*/

<<<<<<< HEAD
void rom_init(running_machine &machine)
{
	romload_private *romdata;
#ifdef USE_IPS
	const char *patchname = machine.options().value(OPTION_IPS);
#endif /* USE_IPS */

	/* allocate private data */
	machine.romload_data = romdata = auto_alloc_clear(machine, romload_private);

	/* make sure we get called back on the way out */
	machine.add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(FUNC(rom_exit), &machine));

	/* reset the romdata struct */
	romdata->m_machine = &machine;

	/* figure out which BIOS we are using */
	device_iterator deviter(romdata->machine().config().root_device());
	for (device_t *device = deviter.first(); device != NULL; device = deviter.next()) {
		if (device->rom_region()) {
			const char *specbios;
			std::string temp;
			if (strcmp(device->tag(),":")==0) {
				specbios = romdata->machine().options().bios();
			} else {
				specbios = romdata->machine().options().sub_value(temp,device->owner()->tag()+1,"bios");
				if (strlen(specbios) == 0) {
					specbios = device->default_bios_tag().c_str();
				}
			}
			determine_bios_rom(romdata, device, specbios);
=======
rom_load_manager::rom_load_manager(running_machine &machine)
	: m_machine(machine)
{
	/* figure out which BIOS we are using */
	std::map<std::string, std::string> card_bios;
	for (device_t &device : device_iterator(machine.config().root_device()))
	{
		device_slot_interface const *const slot(dynamic_cast<device_slot_interface *>(&device));
		if (slot)
		{
			device_t const *const card(slot->get_card_device());
			slot_option const &slot_opt(machine.options().slot_option(slot->slot_name()));
			if (card && !slot_opt.bios().empty())
				card_bios.emplace(std::make_pair(std::string(card->tag()), slot_opt.bios()));
		}

		if (device.rom_region())
		{
			std::string specbios;
			if (!device.owner())
			{
				specbios = machine.options().bios();
			}
			else
			{
				auto const found(card_bios.find(device.tag()));
				if (card_bios.end() != found)
				{
					specbios = std::move(found->second);
					card_bios.erase(found);
				}
			}
			determine_bios_rom(device, specbios.c_str());
>>>>>>> upstream/master
		}
	}

	/* count the total number of ROMs */
<<<<<<< HEAD
	count_roms(romdata);

	/* reset the disk list */
	romdata->chd_list.reset();

#ifdef USE_IPS
	if (patchname && *patchname)
	{
		if (!open_ips_entry(machine, patchname, romdata, machine.system().rom))
		{
			display_rom_load_results(romdata, FALSE);
//			return;
		}
	}
#endif /* USE_IPS */

	/* process the ROM entries we were passed */
	process_region_list(romdata);

#ifdef USE_IPS
	if (patchname && *patchname)
	{
		if (!close_ips_entry(romdata))
		{
			display_rom_load_results(romdata, FALSE);
			return;
		}
	}
#endif /* USE_IPS */

	/* display the results and exit */
	display_rom_load_results(romdata, FALSE);
}


/*-------------------------------------------------
    rom_exit - clean up after ourselves
-------------------------------------------------*/

static void rom_exit(running_machine &machine)
{
}


/*-------------------------------------------------
    rom_load_warnings - return the number of
    warnings we generated
-------------------------------------------------*/

int rom_load_warnings(running_machine &machine)
{
	return machine.romload_data->warnings;
}


/*-------------------------------------------------
    software_load_warnings_message - return the
    software load warnings we generated
-------------------------------------------------*/

std::string& software_load_warnings_message(running_machine &machine)
{
	return machine.romload_data->softwarningstring;
}

/*-------------------------------------------------
    rom_load_knownbad - return the number of
    BAD_DUMP/NO_DUMP warnings we generated
-------------------------------------------------*/

int rom_load_knownbad(running_machine &machine)
{
	return machine.romload_data->knownbad;
=======
	count_roms();

	/* reset the disk list */
	m_chd_list.clear();

	/* process the ROM entries we were passed */
	process_region_list();

	/* display the results and exit */
	display_rom_load_results(false);
}


// -------------------------------------------------
// rom_build_entries - builds a rom_entry vector
// from a tiny_rom_entry array
// -------------------------------------------------

std::vector<rom_entry> rom_build_entries(const tiny_rom_entry *tinyentries)
{
	std::vector<rom_entry> result;

	if (tinyentries != nullptr)
	{
		int i = 0;
		do
		{
			result.emplace_back(tinyentries[i]);
		} while ((tinyentries[i++].flags & ROMENTRY_TYPEMASK) != ROMENTRYTYPE_END);
	}
	else
	{
		const tiny_rom_entry end_entry = { nullptr, nullptr, 0, 0, ROMENTRYTYPE_END };
		result.emplace_back(end_entry);
	}
	return result;
>>>>>>> upstream/master
}
