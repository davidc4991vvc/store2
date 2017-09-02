// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/***************************************************************************

    zippath.c

    File/directory/path operations that work with ZIP files

***************************************************************************/

<<<<<<< HEAD
#include <ctype.h>
#include <stdlib.h>
#include <new>
#include <assert.h>
=======
>>>>>>> upstream/master
#include "zippath.h"
#include "unzip.h"
#include "corestr.h"
#include "osdcore.h"

<<<<<<< HEAD

=======
#include <stdlib.h>

#include <cassert>
#include <cctype>
#include <forward_list>
#include <new>


namespace util {
>>>>>>> upstream/master
/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

<<<<<<< HEAD
struct zippath_returned_directory
{
	zippath_returned_directory *next;
	std::string name;
};


=======
/**
 * @class   zippath_directory
 *
 * @brief   A zippath directory.
 */
>>>>>>> upstream/master

class zippath_directory
{
public:
	zippath_directory()
<<<<<<< HEAD
		: returned_parent(false),
			directory(NULL),
			called_zip_first(false),
			zipfile(NULL),
			returned_dirlist(NULL) { }

	/* common */
	bool returned_parent;
	osd_directory_entry returned_entry;

	/* specific to normal directories */
	osd_directory *directory;

	/* specific to ZIP directories */
	bool called_zip_first;
	zip_file *zipfile;
	std::string zipprefix;
	zippath_returned_directory *returned_dirlist;
=======
		: returned_parent(false)
		, directory()
		, called_zip_first(false)
		, zipfile()
		, returned_dirlist()
	{
	}

	/* common */
	/** @brief  true to returned parent. */
	bool returned_parent;
	/** @brief  The returned entry. */
	osd::directory::entry returned_entry;

	/* specific to normal directories */
	/** @brief  Pathname of the directory. */
	osd::directory::ptr directory;

	/* specific to ZIP directories */
	/** @brief  true to called zip first. */
	bool called_zip_first;
	/** @brief  The zipfile. */
	archive_file::ptr zipfile;
	/** @brief  The zipprefix. */
	std::string zipprefix;
	/** @brief  The returned dirlist. */
	std::forward_list<std::string> returned_dirlist;
>>>>>>> upstream/master
};


/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

<<<<<<< HEAD
static const zip_file_header *zippath_find_sub_path(zip_file *zipfile, const char *subpath, osd_dir_entry_type *type);
static int is_zip_file(const char *path);
static int is_zip_file_separator(char c);
static int is_7z_file(const char *path);
=======
static int zippath_find_sub_path(archive_file &zipfile, std::string const &subpath, osd::directory::entry::entry_type &type);
static bool is_zip_file(std::string const &path);
static bool is_zip_file_separator(char c);
static bool is_7z_file(std::string const &path);
>>>>>>> upstream/master


/***************************************************************************
    PATH OPERATIONS
***************************************************************************/

<<<<<<< HEAD
//============================================================
//  is_path_separator
//============================================================
=======
/**
 * @fn  int is_path_separator(char c)
 *
 * @brief   ============================================================
 *            is_path_separator
 *          ============================================================.
 *
 * @param   c   The character.
 *
 * @return  An int.
 */
>>>>>>> upstream/master

int is_path_separator(char c)
{
	return (c == '/') || (c == '\\');
}

<<<<<<< HEAD
/*-------------------------------------------------
    parse_parent_path - parses out the parent path
-------------------------------------------------*/

static void parse_parent_path(const char *path, int *beginpos, int *endpos)
{
	int length = strlen(path);
	int pos;

	/* skip over trailing path separators */
	pos = length - 1;
	while((pos > 0) && is_path_separator(path[pos]))
		pos--;

	/* return endpos */
	if (endpos != NULL)
		*endpos = pos;

	/* now skip until we find a path separator */
	while((pos >= 0) && !is_path_separator(path[pos]))
		pos--;

	/* return beginpos */
	if (beginpos != NULL)
=======
// -------------------------------------------------
//  parse_parent_path - parses out the parent path
// -------------------------------------------------

/**
 * @fn  static void parse_parent_path(const std::string &path, std::string::size_type *beginpos, std::string::size_type *endpos)
 *
 * @brief   Parse parent path.
 *
 * @param   path                Full pathname of the file.
 * @param [in,out]  beginpos    If non-null, the beginpos.
 * @param [in,out]  endpos      If non-null, the endpos.
 */

static void parse_parent_path(const std::string &path, std::string::size_type *beginpos, std::string::size_type *endpos)
{
	std::string::size_type length = path.length();
	std::string::size_type pos;

	// skip over trailing path separators
	pos = length ? (length - 1) : std::string::npos;
	while ((pos > 0) && (pos != std::string::npos) && is_path_separator(path[pos]))
		pos--;

	// return endpos
	if (endpos != nullptr)
		*endpos = pos;

	// now skip until we find a path separator
	while ((pos != std::string::npos) && !is_path_separator(path[pos]))
		pos = (pos > 0) ? pos - 1 : std::string::npos;

	// return beginpos
	if (beginpos != nullptr)
>>>>>>> upstream/master
		*beginpos = pos;
}



<<<<<<< HEAD
/*-------------------------------------------------
    zippath_parent - retrieves the parent directory
-------------------------------------------------*/

std::string &zippath_parent(std::string &dst, const char *path)
{
	int pos;
	parse_parent_path(path, &pos, NULL);

	/* return the result */
	if (pos >= 0) {
		dst.assign(path, pos + 1);
	}
	else {
		dst.clear();
	}
=======
// -------------------------------------------------
//  zippath_parent - retrieves the parent directory
// -------------------------------------------------

std::string &zippath_parent(std::string &dst, const std::string &path)
{
	std::string::size_type pos;
	parse_parent_path(path, &pos, nullptr);

	if (pos != std::string::npos)
		dst = path.substr(0, pos + 1);
	else
		dst.clear();
>>>>>>> upstream/master
	return dst;
}



<<<<<<< HEAD
/*-------------------------------------------------
    zippath_parent_basename - retrieves the parent
    directory basename
-------------------------------------------------*/

std::string &zippath_parent_basename(std::string &dst, const char *path)
{
	int beginpos, endpos;
	parse_parent_path(path, &beginpos, &endpos);
	dst.copy((char*)(path + beginpos + 1), endpos - beginpos);
=======
// -------------------------------------------------
//  zippath_parent - retrieves the parent directory
// -------------------------------------------------

std::string zippath_parent(const std::string &path)
{
	std::string result;
	zippath_parent(result, path);
	return result;
}



// -------------------------------------------------
//  zippath_parent_basename - retrieves the parent
//  directory basename
// -------------------------------------------------

/**
 * @fn  std::string &zippath_parent_basename(std::string &dst, const std::string &path)
 *
 * @brief   Zippath parent basename.
 *
 * @param [in,out]  dst Destination for the.
 * @param   path        Full pathname of the file.
 *
 * @return  A std::string&amp;
 */

std::string &zippath_parent_basename(std::string &dst, const std::string &path)
{
	std::string::size_type beginpos, endpos;
	parse_parent_path(path, &beginpos, &endpos);
	dst.copy((char*)(path.c_str() + beginpos + 1), endpos - beginpos);
>>>>>>> upstream/master
	return dst;
}



<<<<<<< HEAD
/*-------------------------------------------------
    zippath_combine - combines two paths
-------------------------------------------------*/

std::string &zippath_combine(std::string &dst, const char *path1, const char *path2)
{
	if (!strcmp(path2, "."))
	{
		dst.assign(path1);
	}
	else if (!strcmp(path2, ".."))
	{
		zippath_parent(dst, path1);
=======
// -------------------------------------------------
//  zippath_parent_basename - retrieves the parent
//  directory basename
// -------------------------------------------------

std::string zippath_parent_basename(const std::string &path)
{
	std::string result;
	zippath_parent_basename(result, path);
	return result;
}



// -------------------------------------------------
//  zippath_combine - combines two paths
// -------------------------------------------------

/**
 * @fn  std::string &zippath_combine(std::string &dst, const char *path1, const char *path2)
 *
 * @brief   Zippath combine.
 *
 * @param [in,out]  dst Destination for the.
 * @param   path1       The first path.
 * @param   path2       The second path.
 *
 * @return  A std::string&amp;
 */

std::string &zippath_combine(std::string &dst, const std::string &path1, const std::string &path2)
{
	if (path2 == ".")
	{
		dst.assign(path1);
	}
	else if (path2 == "..")
	{
		dst = zippath_parent(path1);
>>>>>>> upstream/master
	}
	else if (osd_is_absolute_path(path2))
	{
		dst.assign(path2);
	}
<<<<<<< HEAD
	else if ((path1[0] != '\0') && !is_path_separator(path1[strlen(path1) - 1]))
=======
	else if (!path1.empty() && !is_path_separator(*path1.rbegin()))
>>>>>>> upstream/master
	{
		dst.assign(path1).append(PATH_SEPARATOR).append(path2);
	}
	else
	{
		dst.assign(path1).append(path2);
	}
	return dst;
}



<<<<<<< HEAD
=======
// -------------------------------------------------
//  zippath_combine - combines two paths
// -------------------------------------------------

std::string zippath_combine(const std::string &path1, const std::string &path2)
{
	std::string result;
	zippath_combine(result, path1, path2);
	return result;
}



>>>>>>> upstream/master
/***************************************************************************
    FILE OPERATIONS
***************************************************************************/

<<<<<<< HEAD
/*-------------------------------------------------
    file_error_from_zip_error - translates a
    file_error to a zip_error
-------------------------------------------------*/

static file_error file_error_from_zip_error(zip_error ziperr)
{
	file_error filerr;
	switch(ziperr)
	{
		case ZIPERR_NONE:
			filerr = FILERR_NONE;
			break;
		case ZIPERR_OUT_OF_MEMORY:
			filerr = FILERR_OUT_OF_MEMORY;
			break;
		case ZIPERR_BAD_SIGNATURE:
		case ZIPERR_DECOMPRESS_ERROR:
		case ZIPERR_FILE_TRUNCATED:
		case ZIPERR_FILE_CORRUPT:
		case ZIPERR_UNSUPPORTED:
		case ZIPERR_FILE_ERROR:
			filerr = FILERR_INVALID_DATA;
			break;
		case ZIPERR_BUFFER_TOO_SMALL:
		default:
			filerr = FILERR_FAILURE;
			break;
=======
// -------------------------------------------------
//  file_error_from_zip_error - translates a
//  osd_file::error to a zip_error
// -------------------------------------------------

/**
 * @fn  static osd_file::error file_error_from_zip_error(archive_file::error ziperr)
 *
 * @brief   File error from zip error.
 *
 * @param   ziperr  The ziperr.
 *
 * @return  A osd_file::error.
 */

static osd_file::error file_error_from_zip_error(archive_file::error ziperr)
{
	osd_file::error filerr;
	switch(ziperr)
	{
	case archive_file::error::NONE:
		filerr = osd_file::error::NONE;
		break;
	case archive_file::error::OUT_OF_MEMORY:
		filerr = osd_file::error::OUT_OF_MEMORY;
		break;
	case archive_file::error::BAD_SIGNATURE:
	case archive_file::error::DECOMPRESS_ERROR:
	case archive_file::error::FILE_TRUNCATED:
	case archive_file::error::FILE_CORRUPT:
	case archive_file::error::UNSUPPORTED:
	case archive_file::error::FILE_ERROR:
		filerr = osd_file::error::INVALID_DATA;
		break;
	case archive_file::error::BUFFER_TOO_SMALL:
	default:
		filerr = osd_file::error::FAILURE;
		break;
>>>>>>> upstream/master
	}
	return filerr;
}


<<<<<<< HEAD
/*-------------------------------------------------
    create_core_file_from_zip - creates a core_file
    from a zip file entry
-------------------------------------------------*/

static file_error create_core_file_from_zip(zip_file *zip, const zip_file_header *header, core_file *&file)
{
	file_error filerr;
	zip_error ziperr;
	void *ptr;

	ptr = malloc(header->uncompressed_length);
	if (ptr == NULL)
	{
		filerr = FILERR_OUT_OF_MEMORY;
		goto done;
	}

	ziperr = zip_file_decompress(zip, ptr, header->uncompressed_length);
	if (ziperr != ZIPERR_NONE)
=======
// -------------------------------------------------
//  create_core_file_from_zip - creates a core_file
//  from a zip file entry
// -------------------------------------------------

/**
 * @fn  static osd_file::error create_core_file_from_zip(archive_file *zip, util::core_file::ptr &file)
 *
 * @brief   Creates core file from zip.
 *
 * @param [in,out]  zip     If non-null, the zip.
 * @param   header          The header.
 * @param [in,out]  file    [in,out] If non-null, the file.
 *
 * @return  The new core file from zip.
 */

static osd_file::error create_core_file_from_zip(archive_file &zip, util::core_file::ptr &file)
{
	osd_file::error filerr;
	archive_file::error ziperr;
	void *ptr;

	ptr = malloc(zip.current_uncompressed_length());
	if (ptr == nullptr)
	{
		filerr = osd_file::error::OUT_OF_MEMORY;
		goto done;
	}

	ziperr = zip.decompress(ptr, zip.current_uncompressed_length());
	if (ziperr != archive_file::error::NONE)
>>>>>>> upstream/master
	{
		filerr = file_error_from_zip_error(ziperr);
		goto done;
	}

<<<<<<< HEAD
	filerr = core_fopen_ram_copy(ptr, header->uncompressed_length, OPEN_FLAG_READ, &file);
	if (filerr != FILERR_NONE)
		goto done;

done:
	if (ptr != NULL)
=======
	filerr = util::core_file::open_ram_copy(ptr, zip.current_uncompressed_length(), OPEN_FLAG_READ, file);
	if (filerr != osd_file::error::NONE)
		goto done;

done:
	if (ptr != nullptr)
>>>>>>> upstream/master
		free(ptr);
	return filerr;
}


<<<<<<< HEAD
/*-------------------------------------------------
    zippath_fopen - opens a zip path file
-------------------------------------------------*/

file_error zippath_fopen(const char *filename, UINT32 openflags, core_file *&file, std::string &revised_path)
{
	file_error filerr = FILERR_NOT_FOUND;
	zip_error ziperr;
	zip_file *zip = NULL;
	const zip_file_header *header;
	osd_dir_entry_type entry_type;
	char *alloc_fullpath = NULL;
=======
// -------------------------------------------------
//  zippath_fopen - opens a zip path file
// -------------------------------------------------

/**
 * @fn  osd_file::error zippath_fopen(const std::string &filename, uint32_t openflags, util::core_file::ptr &file, std::string &revised_path)
 *
 * @brief   Zippath fopen.
 *
 * @param   filename                Filename of the file.
 * @param   openflags               The openflags.
 * @param [in,out]  file            [in,out] If non-null, the file.
 * @param [in,out]  revised_path    Full pathname of the revised file.
 *
 * @return  A osd_file::error.
 */

osd_file::error zippath_fopen(const std::string &filename, uint32_t openflags, util::core_file::ptr &file, std::string &revised_path)
{
	osd_file::error filerr = osd_file::error::NOT_FOUND;
	archive_file::error ziperr;
	archive_file::ptr zip;
	int header;
	osd::directory::entry::entry_type entry_type;
>>>>>>> upstream/master
	int len;

	/* first, set up the two types of paths */
	std::string mainpath(filename);
	std::string subpath;
<<<<<<< HEAD
	file = NULL;

	/* loop through */
	while((file == NULL) && (mainpath.length() > 0)
		&& ((openflags == OPEN_FLAG_READ) || (subpath.length() == 0)))
	{
		/* is the mainpath a ZIP path? */
		if (is_zip_file(mainpath.c_str()))
		{
			/* this file might be a zip file - lets take a look */
			ziperr = zip_file_open(mainpath.c_str(), &zip);
			if (ziperr == ZIPERR_NONE)
=======
	file = nullptr;

	/* loop through */
	while((file == nullptr) && (mainpath.length() > 0)
		&& ((openflags == OPEN_FLAG_READ) || (subpath.length() == 0)))
	{
		/* is the mainpath a ZIP path? */
		if (is_zip_file(mainpath) || is_7z_file(mainpath))
		{
			/* this file might be a zip file - lets take a look */
			ziperr = is_zip_file(mainpath) ? archive_file::open_zip(mainpath, zip) : archive_file::open_7z(mainpath, zip);
			if (ziperr == archive_file::error::NONE)
>>>>>>> upstream/master
			{
				/* it is a zip file - error if we're not opening for reading */
				if (openflags != OPEN_FLAG_READ)
				{
<<<<<<< HEAD
					filerr = FILERR_ACCESS_DENIED;
=======
					filerr = osd_file::error::ACCESS_DENIED;
>>>>>>> upstream/master
					goto done;
				}

				if (subpath.length() > 0)
<<<<<<< HEAD
					header = zippath_find_sub_path(zip, subpath.c_str(), &entry_type);
				else
					header = zip_file_first_file(zip);

				if (header == NULL)
				{
					filerr = FILERR_NOT_FOUND;
=======
					header = zippath_find_sub_path(*zip, subpath, entry_type);
				else
					header = zip->first_file();

				if (header < 0)
				{
					filerr = osd_file::error::NOT_FOUND;
>>>>>>> upstream/master
					goto done;
				}

				/* attempt to read the file */
<<<<<<< HEAD
				filerr = create_core_file_from_zip(zip, header, file);
				if (filerr != FILERR_NONE)
=======
				filerr = create_core_file_from_zip(*zip, file);
				if (filerr != osd_file::error::NONE)
>>>>>>> upstream/master
					goto done;

				/* update subpath, if appropriate */
				if (subpath.length() == 0)
<<<<<<< HEAD
					subpath.assign(header->filename);
=======
					subpath.assign(zip->current_name());
>>>>>>> upstream/master

				/* we're done */
				goto done;
			}
		}
<<<<<<< HEAD
		else if (is_7z_file(mainpath.c_str()))
		{
			filerr = FILERR_INVALID_DATA;
			goto done;
		}

		if (subpath.length() == 0)
			filerr = core_fopen(filename, openflags, &file);
		else
			filerr = FILERR_NOT_FOUND;

		/* if we errored, then go up a directory */
		if (filerr != FILERR_NONE)
		{
			/* go up a directory */
			std::string temp;
			zippath_parent(temp, mainpath.c_str());
=======

		if (subpath.length() == 0)
			filerr = util::core_file::open(filename, openflags, file);
		else
			filerr = osd_file::error::NOT_FOUND;

		/* if we errored, then go up a directory */
		if (filerr != osd_file::error::NONE)
		{
			/* go up a directory */
			auto temp = zippath_parent(mainpath);
>>>>>>> upstream/master

			/* append to the sub path */
			if (subpath.length() > 0)
			{
				std::string temp2;
				mainpath = mainpath.substr(temp.length());
				temp2.assign(mainpath).append(PATH_SEPARATOR).append(subpath);
				subpath.assign(temp2);
			}
			else
			{
				mainpath = mainpath.substr(temp.length());
				subpath.assign(mainpath);
			}
			/* get the new main path, truncating path separators */
			len = temp.length();
			while (len > 0 && is_zip_file_separator(temp[len - 1]))
				len--;
			temp = temp.substr(0, len);
			mainpath.assign(temp);
		}
	}

done:
	/* store the revised path */
	revised_path.clear();
<<<<<<< HEAD
	if (filerr == FILERR_NONE)
	{
		/* cannonicalize mainpath */
		filerr = osd_get_full_path(&alloc_fullpath, mainpath.c_str());
		if (filerr == FILERR_NONE)
		{
			if (subpath.length() > 0)
				revised_path.assign(alloc_fullpath).append(PATH_SEPARATOR).append(subpath);
			else
				revised_path.assign(alloc_fullpath);
		}
	}

	if (zip != NULL)
		zip_file_close(zip);
	if (alloc_fullpath != NULL)
		osd_free(alloc_fullpath);
=======
	if (filerr == osd_file::error::NONE)
	{
		/* cannonicalize mainpath */
		std::string alloc_fullpath;
		filerr = osd_get_full_path(alloc_fullpath, mainpath);
		if (filerr == osd_file::error::NONE)
		{
			revised_path = alloc_fullpath;
			if (subpath.length() > 0)
				revised_path.append(PATH_SEPARATOR).append(subpath);
		}
	}

>>>>>>> upstream/master
	return filerr;
}


/***************************************************************************
    DIRECTORY OPERATIONS
***************************************************************************/

<<<<<<< HEAD
/*-------------------------------------------------
    is_root - tests to see if this path is the root
-------------------------------------------------*/
=======
// -------------------------------------------------
//  is_root - tests to see if this path is the root
// -------------------------------------------------

/**
 * @fn  static int is_root(const char *path)
 *
 * @brief   Is root.
 *
 * @param   path    Full pathname of the file.
 *
 * @return  An int.
 */
>>>>>>> upstream/master

static int is_root(const char *path)
{
	int i = 0;

	/* skip drive letter */
	if (isalpha(path[i]) && (path[i + 1] == ':'))
		i += 2;

	/* skip path separators */
	while (is_path_separator(path[i]))
		i++;

	return path[i] == '\0';
}



<<<<<<< HEAD
/*-------------------------------------------------
    is_7z_file - tests to see if this file is a
    7-zip file
-------------------------------------------------*/

static int is_7z_file(const char *path)
{
	const char *s = strrchr(path, '.');
	return (s != NULL) && !core_stricmp(s, ".7z");
}


/*-------------------------------------------------
    is_zip_file - tests to see if this file is a
    ZIP file
-------------------------------------------------*/

static int is_zip_file(const char *path)
{
	const char *s = strrchr(path, '.');
	return (s != NULL) && !core_stricmp(s, ".zip");
=======
// -------------------------------------------------
//  is_7z_file - tests to see if this file is a
//  7-zip file
// -------------------------------------------------

/**
 * @fn  static int is_7z_file(const char *path)
 *
 * @brief   Is 7z file.
 *
 * @param   path    Full pathname of the file.
 *
 * @return  An int.
 */

static bool is_7z_file(std::string const &path)
{
	auto const s = path.rfind('.');
	return (std::string::npos != s) && !core_stricmp(path.c_str() + s, ".7z");
}


// -------------------------------------------------
//  is_zip_file - tests to see if this file is a
//  ZIP file
// -------------------------------------------------

static bool is_zip_file(std::string const &path)
{
	auto const s = path.rfind('.');
	return (std::string::npos != s) && !core_stricmp(path.c_str() + s, ".zip");
>>>>>>> upstream/master
}



<<<<<<< HEAD
/*-------------------------------------------------
    is_zip_file_separator - returns whether this
    character is a path separator within a ZIP file
-------------------------------------------------*/

static int is_zip_file_separator(char c)
=======
// -------------------------------------------------
//  is_zip_file_separator - returns whether this
//  character is a path separator within a ZIP file
// -------------------------------------------------

/**
 * @fn  static int is_zip_file_separator(char c)
 *
 * @brief   Is zip file separator.
 *
 * @param   c   The character.
 *
 * @return  An int.
 */

static bool is_zip_file_separator(char c)
>>>>>>> upstream/master
{
	return (c == '/') || (c == '\\');
}



<<<<<<< HEAD
/*-------------------------------------------------
    is_zip_path_separator - returns whether this
    character is a path separator within a ZIP path
-------------------------------------------------*/

static int is_zip_path_separator(char c)
=======
// -------------------------------------------------
//  is_zip_path_separator - returns whether this
//  character is a path separator within a ZIP path
// -------------------------------------------------

/**
 * @fn  static int is_zip_path_separator(char c)
 *
 * @brief   Is zip path separator.
 *
 * @param   c   The character.
 *
 * @return  An int.
 */

static bool is_zip_path_separator(char c)
>>>>>>> upstream/master
{
	return is_zip_file_separator(c) || is_path_separator(c);
}



<<<<<<< HEAD
/*-------------------------------------------------
    next_path_char - lexes out the next path
    character, normalizing separators as '/'
-------------------------------------------------*/

static char next_path_char(const char *s, int *pos)
{
	char result;

	/* skip over any initial separators */
	if (*pos == 0)
	{
		while(is_zip_file_separator(s[*pos]))
			(*pos)++;
	}

	/* are we at a path separator? */
	if (is_zip_file_separator(s[*pos]))
	{
		/* skip over path separators */
		while(is_zip_file_separator(s[*pos]))
			(*pos)++;

		/* normalize as '/' */
		result = '/';
	}
	else if (s[*pos] != '\0')
	{
		/* return character */
		result = tolower(s[(*pos)++]);
	}
	else
	{
		/* return NUL */
		result = '\0';
	}
	return result;
=======
// -------------------------------------------------
//  next_path_char - lexes out the next path
//  character, normalizing separators as '/'
// -------------------------------------------------

/**
 * @fn  static char next_path_char(const char *s, int *pos)
 *
 * @brief   Next path character.
 *
 * @param   s           The const char * to process.
 * @param [in,out]  pos If non-null, the position.
 *
 * @return  A char.
 */

static char next_path_char(std::string const &s, std::string::size_type &pos)
{
	// skip over any initial separators
	if (pos == 0)
	{
		while ((pos < s.length()) && is_zip_file_separator(s[pos]))
			pos++;
	}

	// are we at a path separator?
	if (pos == s.length())
	{
		// return NUL
		return '\0';
	}
	else if (is_zip_file_separator(s[pos]))
	{
		// skip over path separators
		while((pos < s.length()) && is_zip_file_separator(s[pos]))
			pos++;

		// normalize as '/'
		return '/';
	}
	else
	{
		// return character
		return std::tolower(s[pos++]);
	}
>>>>>>> upstream/master
}




<<<<<<< HEAD
/*-------------------------------------------------
    zippath_find_sub_path - attempts to identify the
    type of a sub path in a zip file
-------------------------------------------------*/

static const zip_file_header *zippath_find_sub_path(zip_file *zipfile, const char *subpath, osd_dir_entry_type *type)
{
	int i, j;
	char c1, c2, last_char;
	const zip_file_header *header;

	for (header = zip_file_first_file(zipfile); header != NULL; header = zip_file_next_file(zipfile))
	{
		/* special case */
		if (subpath == NULL)
		{
			if (type != NULL)
				*type = ENTTYPE_FILE;
			return header;
		}

		i = 0;
		j = 0;
		last_char = '/';
				while(((c1 = next_path_char(header->filename, &i)) == (c2 = next_path_char(subpath, &j))) &&
						( c1 != '\0' && c2 != '\0' ))
						last_char = c2;


		if (c2 == '\0')
		{
			if (c1 == '\0')
			{
				if (type != NULL)
					*type = ENTTYPE_FILE;
				return header;
			}
			else if ((last_char == '/') || (c1 == '/'))
			{
				if (type != NULL)
					*type = ENTTYPE_DIR;
=======
// -------------------------------------------------
//  zippath_find_sub_path - attempts to identify the
//  type of a sub path in a zip file
// -------------------------------------------------

/**
 * @fn  static const zip_file_header *zippath_find_sub_path(archive_file *zipfile, const char *subpath, osd::directory::entry::entry_type *type)
 *
 * @brief   Zippath find sub path.
 *
 * @param [in,out]  zipfile If non-null, the zipfile.
 * @param   subpath         The subpath.
 * @param [in,out]  type    If non-null, the type.
 *
 * @return  null if it fails, else a zip_file_header*.
 */

static int zippath_find_sub_path(archive_file &zipfile, std::string const &subpath, osd::directory::entry::entry_type &type)
{
	for (int header = zipfile.first_file(); header >= 0; header = zipfile.next_file())
	{
		std::string::size_type i = 0, j = 0;
		char c1, c2;
		do
		{
			c1 = next_path_char(zipfile.current_name(), i);
			c2 = next_path_char(subpath, j);
		}
		while ((c1 == c2) && c1 && c2);

		if (!c2 || ((c2 == '/') && !(c2 = next_path_char(subpath, j))))
		{
			if (!c1)
			{
				type = zipfile.current_is_directory() ? osd::directory::entry::entry_type::DIR : osd::directory::entry::entry_type::FILE;
				return header;
			}
			else if ((c1 == '/') || (i <= 1U))
			{
				type = osd::directory::entry::entry_type::DIR;
>>>>>>> upstream/master
				return header;
			}
		}
	}

<<<<<<< HEAD
	if (type != NULL)
		*type = ENTTYPE_NONE;
	return NULL;
=======
	type = osd::directory::entry::entry_type::NONE;
	return -1;
>>>>>>> upstream/master
}



<<<<<<< HEAD
/*-------------------------------------------------
    zippath_resolve - separates a ZIP path out into
    true path and ZIP entry components
-------------------------------------------------*/

static file_error zippath_resolve(const char *path, osd_dir_entry_type &entry_type, zip_file *&zipfile, std::string &newpath)
{
	file_error err;
	osd_directory_entry *current_entry = NULL;
	osd_dir_entry_type current_entry_type;
	int went_up = FALSE;
	int i;

	newpath.clear();

	/* be conservative */
	entry_type = ENTTYPE_NONE;
	zipfile = NULL;

	std::string apath(path);
	std::string apath_trimmed;
	do
	{
		/* trim the path of trailing path separators */
		i = apath.length();
		while (i > 1 && is_path_separator(apath[i - 1]))
			i--;
		apath = apath.substr(0, i);
		apath_trimmed.assign(apath);

		/* stat the path */
		current_entry = osd_stat(apath_trimmed.c_str());

		/* did we find anything? */
		if (current_entry != NULL)
		{
			/* get the entry type and free the stat entry */
			current_entry_type = current_entry->type;
			osd_free(current_entry);
			current_entry = NULL;
		}
		else
		{
			/* if we have not found the file or directory, go up */
			current_entry_type = ENTTYPE_NONE;
			went_up = TRUE;
			std::string parent;
			apath.assign(zippath_parent(parent, apath.c_str()));
		}
	}
	while (current_entry_type == ENTTYPE_NONE && !is_root(apath.c_str()));

	/* if we did not find anything, then error out */
	if (current_entry_type == ENTTYPE_NONE)
	{
		err = FILERR_NOT_FOUND;
		goto done;
	}

	/* is this file a ZIP file? */
	if ((current_entry_type == ENTTYPE_FILE) && is_zip_file(apath_trimmed.c_str())
		&& (zip_file_open(apath_trimmed.c_str(), &zipfile) == ZIPERR_NONE))
	{
		i = strlen(path + apath.length());
		while (i > 0 && is_zip_path_separator(path[apath.length() + i - 1]))
			i--;
		newpath.assign(path + apath.length(), i);

		/* this was a true ZIP path - attempt to identify the type of path */
		zippath_find_sub_path(zipfile, newpath.c_str(), &current_entry_type);
		if (current_entry_type == ENTTYPE_NONE)
		{
			err = FILERR_NOT_FOUND;
			goto done;
		}
	}
	else
	{
		/* this was a normal path */
		if (went_up)
		{
			err = FILERR_NOT_FOUND;
			goto done;
		}
		newpath.assign(path);
	}

	/* success! */
	entry_type = current_entry_type;
	err = FILERR_NONE;

done:
	return err;
}


/*-------------------------------------------------
    zippath_opendir - opens a directory
-------------------------------------------------*/

file_error zippath_opendir(const char *path, zippath_directory **directory)
{
	file_error err;

	/* allocate a directory */
	zippath_directory *result = NULL;
=======
// -------------------------------------------------
//  zippath_resolve - separates a ZIP path out into
//  true path and ZIP entry components
// -------------------------------------------------

/**
 * @fn  static osd_file::error zippath_resolve(const char *path, osd::directory::entry::entry_type &entry_type, archive_file *&zipfile, std::string &newpath)
 *
 * @brief   Zippath resolve.
 *
 * @param   path                Full pathname of the file.
 * @param [in,out]  entry_type  Type of the entry.
 * @param [in,out]  zipfile     [in,out] If non-null, the zipfile.
 * @param [in,out]  newpath     The newpath.
 *
 * @return  A osd_file::error.
 */

static osd_file::error zippath_resolve(const char *path, osd::directory::entry::entry_type &entry_type, archive_file::ptr &zipfile, std::string &newpath)
{
	newpath.clear();

	// be conservative
	entry_type = osd::directory::entry::entry_type::NONE;
	zipfile.reset();

	std::string apath(path);
	std::string apath_trimmed;
	osd::directory::entry::entry_type current_entry_type;
	bool went_up = false;
	do
	{
		// trim the path of trailing path separators
		auto i = apath.length();
		while ((i > 1) && is_path_separator(apath[i - 1]))
			i--;
		apath.resize(i);
		apath_trimmed = apath;

		// stat the path
		auto current_entry = osd_stat(apath_trimmed);

		// did we find anything?
		if (current_entry)
		{
			// get the entry type and free the stat entry
			current_entry_type = current_entry->type;
		}
		else
		{
			// if we have not found the file or directory, go up
			current_entry_type = osd::directory::entry::entry_type::NONE;
			went_up = true;
			apath = zippath_parent(apath);
		}
	}
	while ((current_entry_type == osd::directory::entry::entry_type::NONE) && !is_root(apath.c_str()));

	// if we did not find anything, then error out
	if (current_entry_type == osd::directory::entry::entry_type::NONE)
		return osd_file::error::NOT_FOUND;

	// is this file a ZIP file?
	if ((current_entry_type == osd::directory::entry::entry_type::FILE) &&
		((is_zip_file(apath_trimmed) && (archive_file::open_zip(apath_trimmed, zipfile) == archive_file::error::NONE)) ||
			(is_7z_file(apath_trimmed) && (archive_file::open_7z(apath_trimmed, zipfile) == archive_file::error::NONE))))
	{
		auto i = strlen(path + apath.length());
		while ((i > 0) && is_zip_path_separator(path[apath.length() + i - 1]))
			i--;
		newpath.assign(path + apath.length(), i);

		// this was a true ZIP path - attempt to identify the type of path
		zippath_find_sub_path(*zipfile, newpath, current_entry_type);
		if (current_entry_type == osd::directory::entry::entry_type::NONE)
			return osd_file::error::NOT_FOUND;
	}
	else
	{
		// this was a normal path
		if (went_up)
			return osd_file::error::NOT_FOUND;

		newpath = path;
	}

	// success!
	entry_type = current_entry_type;
	return osd_file::error::NONE;
}


// -------------------------------------------------
//  zippath_opendir - opens a directory
// -------------------------------------------------

/**
 * @fn  osd_file::error zippath_opendir(const std::string &path, zippath_directory **directory)
 *
 * @brief   Zippath opendir.
 *
 * @param   path                Full pathname of the file.
 * @param [in,out]  directory   If non-null, pathname of the directory.
 *
 * @return  A osd_file::error.
 */

osd_file::error zippath_opendir(const std::string &path, zippath_directory **directory)
{
	osd_file::error err;

	/* allocate a directory */
	zippath_directory *result = nullptr;
>>>>>>> upstream/master
	try
	{
		result = new zippath_directory;
	}
	catch (std::bad_alloc &)
	{
<<<<<<< HEAD
		err = FILERR_OUT_OF_MEMORY;
		goto done;
	}
	/* resolve the path */
	osd_dir_entry_type entry_type;
	err = zippath_resolve(path, entry_type, result->zipfile, result->zipprefix);
	if (err != FILERR_NONE)
		goto done;

	/* we have to be a directory */
	if (entry_type != ENTTYPE_DIR)
	{
		err = FILERR_NOT_FOUND;
=======
		err = osd_file::error::OUT_OF_MEMORY;
		goto done;
	}
	/* resolve the path */
	osd::directory::entry::entry_type entry_type;
	err = zippath_resolve(path.c_str(), entry_type, result->zipfile, result->zipprefix);
	if (err != osd_file::error::NONE)
		goto done;

	/* we have to be a directory */
	if (entry_type != osd::directory::entry::entry_type::DIR)
	{
		err = osd_file::error::NOT_FOUND;
>>>>>>> upstream/master
		goto done;
	}

	/* was the result a ZIP? */
<<<<<<< HEAD
	if (result->zipfile == NULL)
	{
		/* a conventional directory */
		result->directory = osd_opendir(path);
		if (result->directory == NULL)
		{
			err = FILERR_FAILURE;
=======
	if (!result->zipfile)
	{
		/* a conventional directory */
		result->directory = osd::directory::open(path);
		if (!result->directory)
		{
			err = osd_file::error::FAILURE;
>>>>>>> upstream/master
			goto done;
		}

		/* is this path the root? if so, pretend we've already returned the parent */
<<<<<<< HEAD
		if (is_root(path))
=======
		if (is_root(path.c_str()))
>>>>>>> upstream/master
			result->returned_parent = true;
	}

done:
<<<<<<< HEAD
	if ((directory == NULL || err != FILERR_NONE) && result != NULL)
	{
		zippath_closedir(result);
		result = NULL;
	}
	if (directory != NULL)
=======
	if ((directory == nullptr || err != osd_file::error::NONE) && result != nullptr)
	{
		zippath_closedir(result);
		result = nullptr;
	}
	if (directory != nullptr)
>>>>>>> upstream/master
		*directory = result;
	return err;
}


<<<<<<< HEAD
/*-------------------------------------------------
    zippath_closedir - closes a directory
-------------------------------------------------*/

void zippath_closedir(zippath_directory *directory)
{
	if (directory->directory != NULL)
		osd_closedir(directory->directory);

	if (directory->zipfile != NULL)
		zip_file_close(directory->zipfile);

	while (directory->returned_dirlist != NULL)
	{
		zippath_returned_directory *dirlist = directory->returned_dirlist;
		directory->returned_dirlist = directory->returned_dirlist->next;
		delete dirlist;
	}
=======
// -------------------------------------------------
//  zippath_closedir - closes a directory
// -------------------------------------------------

/**
 * @fn  void zippath_closedir(zippath_directory *directory)
 *
 * @brief   Zippath closedir.
 *
 * @param [in,out]  directory   If non-null, pathname of the directory.
 */

void zippath_closedir(zippath_directory *directory)
{
	if (directory->directory != nullptr)
		directory->directory.reset();

	if (directory->zipfile != nullptr)
		directory->zipfile.reset();

	directory->returned_dirlist.clear();
>>>>>>> upstream/master

	delete directory;
}


<<<<<<< HEAD
/*-------------------------------------------------
    get_relative_path - checks to see if a specified
    header is in the zippath_directory, and if so
    returns the relative path
-------------------------------------------------*/

static const char *get_relative_path(zippath_directory *directory, const zip_file_header *header)
{
	const char *result = NULL;
	int len = directory->zipprefix.length();

	if ((len <= strlen(header->filename))
		&& !strncmp(directory->zipprefix.c_str(), header->filename, len))
	{
		result = &header->filename[len];
		while(is_zip_file_separator(*result))
			result++;
	}

	return result;
}


/*-------------------------------------------------
    zippath_readdir - reads a directory
-------------------------------------------------*/

const osd_directory_entry *zippath_readdir(zippath_directory *directory)
{
	const osd_directory_entry *result = NULL;
	const zip_file_header *header;
	const char *relpath;
	const char *separator;
	const char *s;
	zippath_returned_directory *rdent;
=======
// -------------------------------------------------
//  get_relative_path - checks to see if a specified
//  header is in the zippath_directory, and if so
//  returns the relative path
// -------------------------------------------------

/**
 * @fn  static const char *get_relative_path(zippath_directory *directory, const zip_file_header *header)
 *
 * @brief   Gets relative path.
 *
 * @param [in,out]  directory   If non-null, pathname of the directory.
 * @param   header              The header.
 *
 * @return  null if it fails, else the relative path.
 */

static const char *get_relative_path(zippath_directory const &directory)
{
	auto len = directory.zipprefix.length();
	char const *prefix = directory.zipprefix.c_str();
	while (is_zip_file_separator(*prefix))
	{
		len--;
		prefix++;
	}

	std::string const &current(directory.zipfile->current_name());
	char const *result = directory.zipfile->current_name().c_str() + len;
	if ((current.length() >= len) &&
		!strncmp(prefix, current.c_str(), len) &&
		(!*prefix || is_zip_file_separator(*result) || is_zip_file_separator(directory.zipprefix.back())))
	{
		while (is_zip_file_separator(*result))
			result++;

		return *result ? result : nullptr;
	}
	else
	{
		return nullptr;
	}
}


// -------------------------------------------------
//  zippath_readdir - reads a directory
// -------------------------------------------------

/**
 * @fn  const osd::directory::entry *zippath_readdir(zippath_directory *directory)
 *
 * @brief   Zippath readdir.
 *
 * @param [in,out]  directory   If non-null, pathname of the directory.
 *
 * @return  null if it fails, else an osd::directory::entry*.
 */

const osd::directory::entry *zippath_readdir(zippath_directory *directory)
{
	const osd::directory::entry *result = nullptr;
>>>>>>> upstream/master

	if (!directory->returned_parent)
	{
		/* first thing's first - return parent directory */
		directory->returned_parent = true;
<<<<<<< HEAD
		memset(&directory->returned_entry, 0, sizeof(directory->returned_entry));
		directory->returned_entry.name = "..";
		directory->returned_entry.type = ENTTYPE_DIR;
		result = &directory->returned_entry;
	}
	else if (directory->directory != NULL)
=======
		directory->returned_entry.name = "..";
		directory->returned_entry.type = osd::directory::entry::entry_type::DIR;
		directory->returned_entry.size = 0; // FIXME: what would stat say?
		// FIXME: modified time?
		result = &directory->returned_entry;
	}
	else if (directory->directory)
>>>>>>> upstream/master
	{
		/* a normal directory read */
		do
		{
<<<<<<< HEAD
			result = osd_readdir(directory->directory);
		}
		while((result != NULL) && (!strcmp(result->name, ".") || !strcmp(result->name, "..")));

		/* special case - is this entry a ZIP file?  if so we need to return it as a "directory" */
		if ((result != NULL) && is_zip_file(result->name))
		{
			/* copy; but change the entry type */
			directory->returned_entry = *result;
			directory->returned_entry.type = ENTTYPE_DIR;
			result = &directory->returned_entry;
		}
	}
	else if (directory->zipfile != NULL)
	{
		do
		{
			/* a zip file read */
			do
			{
				if (!directory->called_zip_first)
					header = zip_file_first_file(directory->zipfile);
				else
					header = zip_file_next_file(directory->zipfile);
				directory->called_zip_first = true;
				relpath = NULL;
			}
			while((header != NULL) && ((relpath = get_relative_path(directory, header)) == NULL));

			if (relpath != NULL)
			{
				/* we've found a ZIP entry; but this may be an entry deep within the target directory */
				for (s = relpath; *s && !is_zip_file_separator(*s); s++)
					;
				separator = *s ? s : NULL;

				if (separator != NULL)
				{
					/* a nested entry; loop through returned_dirlist to see if we've returned the parent directory */
					for (rdent = directory->returned_dirlist; rdent != NULL; rdent = rdent->next)
					{
						if (!core_strnicmp(rdent->name.c_str(), relpath, separator - relpath))
							break;
					}

					if (rdent == NULL)
					{
						/* we've found a new directory; add this to returned_dirlist */
						rdent = new zippath_returned_directory;
						rdent->next = directory->returned_dirlist;
						rdent->name.assign(relpath, separator - relpath);
						directory->returned_dirlist = rdent;

						/* ...and return it */
						memset(&directory->returned_entry, 0, sizeof(directory->returned_entry));
						directory->returned_entry.name = rdent->name.c_str();
						directory->returned_entry.type = ENTTYPE_DIR;
=======
			result = directory->directory->read();
		}
		while (result && (!strcmp(result->name, ".") || !strcmp(result->name, "..")));

		/* special case - is this entry a ZIP file?  if so we need to return it as a "directory" */
		if (result && (is_zip_file(result->name) || is_7z_file(result->name)))
		{
			/* copy; but change the entry type */
			directory->returned_entry = *result;
			directory->returned_entry.type = osd::directory::entry::entry_type::DIR;
			directory->returned_entry.size = 0; // FIXME: what would stat say?
			// FIXME: modified time?
			result = &directory->returned_entry;
		}
	}
	else if (directory->zipfile)
	{
		char const *relpath;
		do
		{
			/* a zip file read */
			int header;
			do
			{
				header = directory->called_zip_first ? directory->zipfile->next_file() : directory->zipfile->first_file();
				directory->called_zip_first = true;
				relpath = nullptr;
			}
			while ((header >= 0) && ((relpath = get_relative_path(*directory)) == nullptr));

			if (relpath)
			{
				/* we've found a ZIP entry; but this may be an entry deep within the target directory */
				char const *separator = relpath;
				while (*separator && !is_zip_file_separator(*separator)) separator++;

				if (*separator || directory->zipfile->current_is_directory())
				{
					/* a nested entry; loop through returned_dirlist to see if we've returned the parent directory */
					auto const len(separator - relpath);
					auto rdent = directory->returned_dirlist.begin();
					while (directory->returned_dirlist.end() != rdent)
					{
						if ((rdent->length() == len) && !core_strnicmp(rdent->c_str(), relpath, len))
							break;
						else
							++rdent;
					}

					if (directory->returned_dirlist.end() == rdent)
					{
						/* we've found a new directory; add this to returned_dirlist */
						directory->returned_dirlist.emplace_front(relpath, separator - relpath);

						/* ...and return it */
						directory->returned_entry.name = directory->returned_dirlist.front().c_str();
						directory->returned_entry.type = osd::directory::entry::entry_type::DIR;
						directory->returned_entry.size = 0; // FIXME: what would stat say?
						// FIXME: modified time?
>>>>>>> upstream/master
						result = &directory->returned_entry;
					}
				}
				else
				{
					/* a real file */
<<<<<<< HEAD
					memset(&directory->returned_entry, 0, sizeof(directory->returned_entry));
					directory->returned_entry.name = relpath;
					directory->returned_entry.type = ENTTYPE_FILE;
					directory->returned_entry.size = header->uncompressed_length;
=======
					directory->returned_entry.name = relpath;
					directory->returned_entry.type = osd::directory::entry::entry_type::FILE;
					directory->returned_entry.size = directory->zipfile->current_uncompressed_length();
					directory->returned_entry.last_modified = directory->zipfile->current_last_modified();
>>>>>>> upstream/master
					result = &directory->returned_entry;
				}
			}
		}
<<<<<<< HEAD
		while((relpath != NULL) && (result == NULL));
=======
		while (relpath && !result);
>>>>>>> upstream/master
	}
	return result;
}



<<<<<<< HEAD
/*-------------------------------------------------
    zippath_is_zip - returns TRUE if this path is
    a ZIP path or FALSE if not
-------------------------------------------------*/

int zippath_is_zip(zippath_directory *directory)
{
	return directory->zipfile != NULL;
}
=======
// -------------------------------------------------
//  zippath_is_zip - returns true if this path is
//  a ZIP path or false if not
// -------------------------------------------------

/**
 * @fn  int zippath_is_zip(zippath_directory *directory)
 *
 * @brief   Zippath is zip.
 *
 * @param [in,out]  directory   If non-null, pathname of the directory.
 *
 * @return  An int.
 */

bool zippath_is_zip(zippath_directory *directory)
{
	return directory->zipfile != nullptr;
}

} // namespace util
>>>>>>> upstream/master
