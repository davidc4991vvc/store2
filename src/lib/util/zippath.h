// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/***************************************************************************

    zippath.h

    File/directory/path operations that work with ZIP files

***************************************************************************/

#pragma once

<<<<<<< HEAD
#ifndef __ZIPPATH_H__
#define __ZIPPATH_H__
=======
#ifndef MAME_LIB_UTIL_ZIPPATH_H
#define MAME_LIB_UTIL_ZIPPATH_H
>>>>>>> upstream/master

#include "corefile.h"
#include <string>
#include "unzip.h"


<<<<<<< HEAD
=======
namespace util {
>>>>>>> upstream/master
/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

class zippath_directory;



/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

<<<<<<< HEAD
/* ----- path operations ----- */

/* retrieves the parent directory */
std::string &zippath_parent(std::string &dst, const char *path);

/* retrieves the parent directory basename */
std::string &zippath_parent_basename(std::string &dst, const char *path);

/* combines two paths */
std::string &zippath_combine(std::string &dst, const char *path1, const char *path2);


/* ----- file operations ----- */

/* opens a zip path file */
file_error zippath_fopen(const char *filename, UINT32 openflags, core_file *&file, std::string &revised_path);


/* ----- directory operations ----- */

/* opens a directory */
file_error zippath_opendir(const char *path, zippath_directory **directory);

/* closes a directory */
void zippath_closedir(zippath_directory *directory);

/* reads a directory entry */
const osd_directory_entry *zippath_readdir(zippath_directory *directory);

/* returns TRUE if this path is a ZIP path or FALSE if not */
int zippath_is_zip(zippath_directory *directory);



#endif /* __ZIPPATH_H__ */
=======
// ----- path operations -----

// retrieves the parent directory
std::string &zippath_parent(std::string &dst, const std::string &path);
std::string zippath_parent(const std::string &path);

// retrieves the parent directory basename
std::string &zippath_parent_basename(std::string &dst, const std::string &path);
std::string zippath_parent_basename(const std::string &path);

// combines two paths
std::string &zippath_combine(std::string &dst, const std::string &path1, const std::string &path2);
std::string zippath_combine(const std::string &path1, const std::string &path2);


// ----- file operations -----

// opens a zip path file
osd_file::error zippath_fopen(const std::string &filename, uint32_t openflags, util::core_file::ptr &file, std::string &revised_path);


// ----- directory operations ----- */

// opens a directory
osd_file::error zippath_opendir(const std::string &path, zippath_directory **directory);

// closes a directory
void zippath_closedir(zippath_directory *directory);

// reads a directory entry
const osd::directory::entry *zippath_readdir(zippath_directory *directory);

// returns true if this path is a ZIP path or false if not
bool zippath_is_zip(zippath_directory *directory);

} // namespace util


#endif // MAME_LIB_UTIL_ZIPPATH_H
>>>>>>> upstream/master
