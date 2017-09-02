// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/***************************************************************************

<<<<<<< HEAD
    main.c
=======
    main.cpp
>>>>>>> upstream/master

    Imgtool command line front end

***************************************************************************/

<<<<<<< HEAD
=======
#include "imgtool.h"
#include "main.h"
#include "modules.h"
#include "strformat.h"

>>>>>>> upstream/master
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
<<<<<<< HEAD

#include "imgtool.h"
#include "main.h"
#include "modules.h"
/* ---------------------------------------------------------------------- */

static void writeusage(FILE *f, int write_word_usage, const struct command *c, char *argv[])
{
	fprintf(f, "%s %s %s %s\n",
		(write_word_usage ? "Usage:" : "      "),
		imgtool_basename(argv[0]),
		c->name,
		c->usage ? c->usage : "");
}



/* ----------------------------------------------------------------------- */

static int parse_options(int argc, char *argv[], int minunnamed, int maxunnamed,
	option_resolution *resolution, filter_getinfoproc *filter, const char **fork)
=======
#include <iostream>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

// ----------------------------------------------------------------------

static void writeusage(std::wostream &output, bool write_word_usage, const struct command *c, char *argv[])
{
	std::string cmdname = core_filename_extract_base(argv[0]);

	util::stream_format(output,
		L"%s %s %s %s\n",
		(write_word_usage ? L"Usage:" : L"      "),
		wstring_from_utf8(cmdname),
		wstring_from_utf8(c->name),
		c->usage ? wstring_from_utf8(c->usage) : std::wstring());
}


// ----------------------------------------------------------------------

static int parse_options(int argc, char *argv[], int minunnamed, int maxunnamed,
	util::option_resolution *resolution, filter_getinfoproc *filter, const char **fork)
>>>>>>> upstream/master
{
	int i;
	int lastunnamed = 0;
	char *s;
<<<<<<< HEAD
	char *name = NULL;
	char *value = NULL;
	optreserr_t oerr;
	static char buf[256];

	if (filter)
		*filter = NULL;
	if (fork)
		*fork = NULL;
=======
	char *name = nullptr;
	char *value = nullptr;
	static char buf[256];

	if (filter)
		*filter = nullptr;
	if (fork)
		*fork = nullptr;
>>>>>>> upstream/master

	for (i = 0; i < argc; i++)
	{
		/* Named or unamed arg */
		if ((argv[i][0] != '-') || (argv[i][1] != '-'))
		{
			/* Unnamed */
			if (i >= maxunnamed)
				goto error; /* Too many unnamed */
			lastunnamed = i + 1;
		}
		else
		{
			/* Named */
			name = argv[i] + 2;
			s = strchr(name, '=');
			if (!s)
				goto error;
			*s = 0;
			value = s + 1;

			if (!strcmp(name, "filter"))
			{
				/* filter option */
				if (!filter)
					goto error; /* this command doesn't use filters */
				if (*filter)
					goto optionalreadyspecified;
				*filter = filter_lookup(value);
				if (!(*filter))
					goto filternotfound;

			}
			else if (!strcmp(name, "fork"))
			{
				/* fork option */
				if (!fork)
					goto error; /* this command doesn't use filters */
				if (*fork)
					goto optionalreadyspecified;

				snprintf(buf, ARRAY_LENGTH(buf), "%s", value);
				*fork = buf;
			}
			else
			{
				/* Other named option */
				if (i < minunnamed)
					goto error; /* Too few unnamed */

<<<<<<< HEAD
				oerr = option_resolution_add_param(resolution, name, value);
				if (oerr)
					goto opterror;
=======
				resolution->find(name)->set_value(value);
>>>>>>> upstream/master
			}
		}
	}
	return lastunnamed;

filternotfound:
<<<<<<< HEAD
	fprintf(stderr, "%s: Unknown filter type\n", value);
	return -1;

optionalreadyspecified:
	fprintf(stderr, "Cannot specify multiple %ss\n", name);
	return -1;

opterror:
	fprintf(stderr, "%s: %s\n", name, option_resolution_error_string(oerr));
	return -1;

error:
	fprintf(stderr, "%s: Unrecognized option\n", argv[i]);
=======
	util::stream_format(std::wcerr, L"%s: Unknown filter type\n", wstring_from_utf8(value));
	return -1;

optionalreadyspecified:
	util::stream_format(std::wcerr, L"Cannot specify multiple %ss\n", wstring_from_utf8(name));
	return -1;

error:
	util::stream_format(std::wcerr, L"%s: Unrecognized option\n", wstring_from_utf8(argv[i]));
>>>>>>> upstream/master
	return -1;
}



void reporterror(imgtoolerr_t err, const struct command *c, const char *format, const char *imagename,
<<<<<<< HEAD
	const char *filename, const char *newname, option_resolution *opts)
=======
	const char *filename, const char *newname, util::option_resolution *opts)
>>>>>>> upstream/master
{
	const char *src = "imgtool";
	const char *err_name;

	err_name = imgtool_error(err);

	switch(ERRORSOURCE(err)) {
	case IMGTOOLERR_SRC_MODULE:
		src = format;
		break;
	case IMGTOOLERR_SRC_FUNCTIONALITY:
		src = c->name;
		break;
	case IMGTOOLERR_SRC_IMAGEFILE:
		src = imagename;
		break;
	case IMGTOOLERR_SRC_FILEONIMAGE:
		src = filename;
		break;
	case IMGTOOLERR_SRC_NATIVEFILE:
		src = newname ? newname : filename;
		break;
	}
	fflush(stdout);
	fflush(stderr);

	if (!src)
		src = c->name;
<<<<<<< HEAD
	fprintf(stderr, "%s: %s\n", src, err_name);
=======
	util::stream_format(std::wcerr, L"%s: %s\n", wstring_from_utf8(src), wstring_from_utf8(err_name));
>>>>>>> upstream/master
}



static const char *interpret_filename(const char *filename)
{
	if (!strcmp(filename, "??BOOT??")
			|| !strcmp(filename, "\'??BOOT??\'")
			|| !strcmp(filename, "\"??BOOT??\""))
		filename = FILENAME_BOOTBLOCK;
	return filename;
}



<<<<<<< HEAD
/* ----------------------------------------------------------------------- */
=======
// ----------------------------------------------------------------------
>>>>>>> upstream/master

static int cmd_dir(const struct command *c, int argc, char *argv[])
{
	imgtoolerr_t err;
	int total_count, total_size, freespace_err;
<<<<<<< HEAD
	UINT64 freespace;
	imgtool_image *image = NULL;
	imgtool_partition *partition = NULL;
	imgtool_directory *imgenum = NULL;
	imgtool_dirent ent;
	char buf[512];
	char last_modified[19];
	const char *path;
	int partition_index = 0;

	/* attempt to open image */
	err = imgtool_image_open_byname(argv[0], argv[1], OSD_FOPEN_READ, &image);
=======
	uint64_t freespace;
	imgtool::image::ptr image;
	imgtool::partition::ptr partition;
	imgtool::directory::ptr imgenum;
	imgtool_dirent ent;
	char last_modified[19];
	std::string path;
	int partition_index = 0;
	std::string info;

	// build the separator
	const int columnwidth_filename = 30;
	const int columnwidth_filesize = 8;
	const int columnwidth_attributes = 15;
	const int columnwidth_lastmodified = 18;
	std::string separator = std::string(columnwidth_filename, '-') + " "
		+ std::string(columnwidth_filesize, '-') + " "
		+ std::string(columnwidth_attributes, '-') + " "
		+ std::string(columnwidth_lastmodified, '-');

	// attempt to open image
	err = imgtool::image::open(argv[0], argv[1], OSD_FOPEN_READ, image);
>>>>>>> upstream/master
	if (err)
		goto done;

	/* attempt to open partition */
<<<<<<< HEAD
	err = imgtool_partition_open(image, partition_index, &partition);
	if (err)
		goto done;

	path = argc > 2 ? argv[2] : NULL;

	err = imgtool_directory_open(partition, path, &imgenum);
=======
	err = imgtool::partition::open(*image, partition_index, partition);
	if (err)
		goto done;

	path = argc > 2 ? argv[2] : "";

	err = imgtool::directory::open(*partition, path, imgenum);
>>>>>>> upstream/master
	if (err)
		goto done;

	memset(&ent, 0, sizeof(ent));
	last_modified[0] = '\0';
	total_count = 0;
	total_size = 0;

<<<<<<< HEAD
	fprintf(stdout, "Contents of %s:%s\n", argv[1], path ? path : "");

	imgtool_image_info(image, buf, sizeof(buf));
	if (buf[0])
		fprintf(stdout, "%s\n", buf);
	fprintf(stdout, "------------------------------  --------  ---------------  ------------------\n");

	while (((err = imgtool_directory_get_next(imgenum, &ent)) == 0) && !ent.eof)
	{
		if (ent.directory)
			snprintf(buf, sizeof(buf), "<DIR>");
		else
			snprintf(buf, sizeof(buf), "%u", (unsigned int) ent.filesize);
=======
	util::stream_format(std::wcout, L"Contents of %s:%s\n", wstring_from_utf8(argv[1]), wstring_from_utf8(path));

	info = image->info();
	if (!info.empty())
		util::stream_format(std::wcout, L"%s\n", wstring_from_utf8(info));

	util::stream_format(std::wcout, L"%s\n", wstring_from_utf8(separator));

	while (((err = imgenum->get_next(ent)) == 0) && !ent.eof)
	{
		std::string filesize_string = ent.directory
			? "<DIR>"
			: string_format("%u", (unsigned int) ent.filesize);
>>>>>>> upstream/master

		if (ent.lastmodified_time != 0)
			strftime(last_modified, sizeof(last_modified), "%d-%b-%y %H:%M:%S",
				localtime(&ent.lastmodified_time));

		if (ent.hardlink)
			strcat(ent.filename, " <hl>");

<<<<<<< HEAD
		fprintf(stdout, "%-30s  %8s  %15s  %18s\n", ent.filename, buf, ent.attr, last_modified);

		if (ent.softlink && ent.softlink[0] != '\0')
			fprintf(stdout, "-> %s\n", ent.softlink);

		if (ent.comment && ent.comment[0] != '\0')
			fprintf(stdout, ": %s\n", ent.comment);
=======
		util::stream_format(std::wcout,
			L"%*s %*s %*s %*s\n",
			-columnwidth_filename, wstring_from_utf8(ent.filename),
			columnwidth_filesize, wstring_from_utf8(filesize_string),
			columnwidth_attributes, wstring_from_utf8(ent.attr),
			columnwidth_lastmodified, wstring_from_utf8(last_modified));

		if (ent.softlink && ent.softlink[0] != '\0')
			util::stream_format(std::wcout, L"-> %s\n", wstring_from_utf8(ent.softlink));

		if (ent.comment && ent.comment[0] != '\0')
			util::stream_format(std::wcout, L": %s\n", wstring_from_utf8(ent.comment));
>>>>>>> upstream/master

		total_count++;
		total_size += ent.filesize;

		memset(&ent, 0, sizeof(ent));
	}

<<<<<<< HEAD
	freespace_err = imgtool_partition_get_free_space(partition, &freespace);
=======
	freespace_err = partition->get_free_space(freespace);
>>>>>>> upstream/master

	if (err)
		goto done;

<<<<<<< HEAD
	fprintf(stdout, "------------------------  ------ ---------------\n");
	fprintf(stdout, "%8i File(s)        %8i bytes\n", total_count, total_size);
	if (!freespace_err)
		fprintf(stdout, "                        %8u bytes free\n", (unsigned int) freespace);

done:
	if (imgenum)
		imgtool_directory_close(imgenum);
	if (partition)
		imgtool_partition_close(partition);
	if (image)
		imgtool_image_close(image);
	if (err)
		reporterror(err, c, argv[0], argv[1], NULL, NULL, NULL);
=======
	util::stream_format(std::wcout, L"%s\n", wstring_from_utf8(separator));
	util::stream_format(std::wcout, L"%8i File(s)        %8i bytes", total_count, total_size);
	if (!freespace_err)
		util::stream_format(std::wcout, L"                        %8u bytes free\n", (unsigned int)freespace);

done:
	if (err)
		reporterror(err, c, argv[0], argv[1], nullptr, nullptr, nullptr);
>>>>>>> upstream/master
	return err ? -1 : 0;
}



static int cmd_get(const struct command *c, int argc, char *argv[])
{
	imgtoolerr_t err;
<<<<<<< HEAD
	imgtool_image *image = NULL;
	imgtool_partition *partition = NULL;
=======
	imgtool::image::ptr image;
	imgtool::partition::ptr partition;
>>>>>>> upstream/master
	const char *filename;
	char *new_filename;
	int unnamedargs = 0;
	filter_getinfoproc filter;
	const char *fork;
	int partition_index = 0;

<<<<<<< HEAD
	err = imgtool_image_open_byname(argv[0], argv[1], OSD_FOPEN_READ, &image);
	if (err)
		goto done;

	err = imgtool_partition_open(image, partition_index, &partition);
=======
	err = imgtool::image::open(argv[0], argv[1], OSD_FOPEN_READ, image);
	if (err)
		goto done;

	err = imgtool::partition::open(*image, partition_index, partition);
>>>>>>> upstream/master
	if (err)
		goto done;

	filename = interpret_filename(argv[2]);

<<<<<<< HEAD
	unnamedargs = parse_options(argc, argv, 3, 4, NULL, &filter, &fork);
	if (unnamedargs < 0)
		goto done;

	new_filename = (unnamedargs == 4) ? argv[3] : NULL;

	err = imgtool_partition_get_file(partition, filename, fork, new_filename, filter);
=======
	unnamedargs = parse_options(argc, argv, 3, 4, nullptr, &filter, &fork);
	if (unnamedargs < 0)
		goto done;

	new_filename = (unnamedargs == 4) ? argv[3] : nullptr;

	err = partition->get_file(filename, fork, new_filename, filter);
>>>>>>> upstream/master
	if (err)
		goto done;

	err = IMGTOOLERR_SUCCESS;

done:
	if (err)
<<<<<<< HEAD
		reporterror(err, c, argv[0], argv[1], argv[2], argv[3], NULL);
	if (partition)
		imgtool_partition_close(partition);
	if (image)
		imgtool_image_close(image);
=======
		reporterror(err, c, argv[0], argv[1], argv[2], argv[3], nullptr);
>>>>>>> upstream/master
	return (err || (unnamedargs < 0)) ? -1 : 0;
}



static int cmd_put(const struct command *c, int argc, char *argv[])
{
	imgtoolerr_t err = IMGTOOLERR_SUCCESS;
	int i;
<<<<<<< HEAD
	imgtool_image *image = NULL;
	imgtool_partition *partition = NULL;
	const char *filename = NULL;
	int unnamedargs;
	filter_getinfoproc filter;
	const imgtool_module *module;
	option_resolution *resolution = NULL;
=======
	imgtool::image::ptr image;
	imgtool::partition::ptr partition;
	const char *filename = nullptr;
	int unnamedargs;
	filter_getinfoproc filter;
	const imgtool_module *module;
	std::unique_ptr<util::option_resolution> resolution;
>>>>>>> upstream/master
	const char *fork;
	const char *new_filename;
	char **filename_list;
	int filename_count;
	int partition_index = 0;
<<<<<<< HEAD
	const option_guide *writefile_optguide;
=======
	const util::option_guide *writefile_optguide;
>>>>>>> upstream/master
	const char *writefile_optspec;

	module = imgtool_find_module(argv[0]);
	if (!module)
	{
		err = (imgtoolerr_t)(IMGTOOLERR_MODULENOTFOUND | IMGTOOLERR_SRC_MODULE);
		goto done;
	}

	/* ugh I hate the way this function is set up, this is because the
	 * arguments depend on the partition; something that requires some
	 * rudimentary parsing */
	if (argc >= 2)
	{
		/* open up the image */
<<<<<<< HEAD
		err = imgtool_image_open(module, argv[1], OSD_FOPEN_RW, &image);
=======
		err = imgtool::image::open(module, argv[1], OSD_FOPEN_RW, image);
>>>>>>> upstream/master
		if (err)
			goto done;

		/* open up the partition */
<<<<<<< HEAD
		err = imgtool_partition_open(image, partition_index, &partition);
		if (err)
			goto done;

		writefile_optguide = (const option_guide *) imgtool_partition_get_info_ptr(partition, IMGTOOLINFO_PTR_WRITEFILE_OPTGUIDE);
		writefile_optspec = (const char *)imgtool_partition_get_info_ptr(partition, IMGTOOLINFO_STR_WRITEFILE_OPTSPEC);

		if (writefile_optguide && writefile_optspec)
		{
			resolution = option_resolution_create(writefile_optguide, writefile_optspec);
			if (!resolution)
=======
		err = imgtool::partition::open(*image, partition_index, partition);
		if (err)
			goto done;

		writefile_optguide = (const util::option_guide *) partition->get_info_ptr(IMGTOOLINFO_PTR_WRITEFILE_OPTGUIDE);
		writefile_optspec = (const char *)partition->get_info_ptr(IMGTOOLINFO_STR_WRITEFILE_OPTSPEC);

		if (writefile_optguide && writefile_optspec)
		{
			try { resolution.reset(new util::option_resolution(*writefile_optguide)); }
			catch (...)
>>>>>>> upstream/master
			{
				err = IMGTOOLERR_OUTOFMEMORY;
				goto done;
			}
<<<<<<< HEAD
		}
	}

	unnamedargs = parse_options(argc, argv, 4, 0xffff, resolution, &filter, &fork);
=======
			resolution->set_specification(writefile_optspec);
		}
	}

	unnamedargs = parse_options(argc, argv, 4, 0xffff, resolution.get(), &filter, &fork);
>>>>>>> upstream/master
	if (unnamedargs < 0)
		return -1;

	/* pick out which args are filenames, and which one is the destination */
	new_filename = interpret_filename(argv[unnamedargs - 1]);
	filename_list = &argv[2];
	filename_count = unnamedargs - 3;

	/* loop through the filenames, and put them */
	for (i = 0; i < filename_count; i++)
	{
		filename = filename_list[i];
<<<<<<< HEAD
		printf("Putting file '%s'...\n", filename);
		err = imgtool_partition_put_file(partition, new_filename, fork, filename, resolution, filter);
=======
		util::stream_format(std::wcout, L"Putting file '%s'...\n", wstring_from_utf8(filename));
		err = partition->put_file(new_filename, fork, filename, resolution.get(), filter);
>>>>>>> upstream/master
		if (err)
			goto done;
	}

done:
<<<<<<< HEAD
	if (partition)
		imgtool_partition_close(partition);
	if (image)
		imgtool_image_close(image);
	if (resolution)
		option_resolution_close(resolution);
	if (err)
		reporterror(err, c, argv[0], argv[1], filename, NULL, resolution);
=======
	if (err)
		reporterror(err, c, argv[0], argv[1], filename, nullptr, resolution.get());
>>>>>>> upstream/master
	return err ? -1 : 0;
}



static int cmd_getall(const struct command *c, int argc, char *argv[])
{
	imgtoolerr_t err;
<<<<<<< HEAD
	imgtool_image *image = NULL;
	imgtool_partition *partition = NULL;
	imgtool_directory *imgenum = NULL;
	imgtool_dirent ent;
	filter_getinfoproc filter;
	int unnamedargs;
	const char *path = NULL;
	int arg;
	int partition_index = 0;

	err = imgtool_image_open_byname(argv[0], argv[1], OSD_FOPEN_READ, &image);
	if (err)
		goto done;

	err = imgtool_partition_open(image, partition_index, &partition);
=======
	imgtool::image::ptr image;
	imgtool::partition::ptr partition;
	imgtool::directory::ptr imgenum;
	imgtool_dirent ent;
	filter_getinfoproc filter;
	int unnamedargs;
	const char *path = nullptr;
	int arg;
	int partition_index = 0;

	err = imgtool::image::open(argv[0], argv[1], OSD_FOPEN_READ, image);
	if (err)
		goto done;

	err = imgtool::partition::open(*image, partition_index, partition);
>>>>>>> upstream/master
	if (err)
		goto done;

	arg = 2;
	if ((argc > 2) && (argv[2][0] != '-'))
	{
		path = argv[arg++];
	}

<<<<<<< HEAD
	unnamedargs = parse_options(argc, argv, arg, arg, NULL, &filter, NULL);
	if (unnamedargs < 0)
		goto done;

	err = imgtool_directory_open(partition, path, &imgenum);
=======
	unnamedargs = parse_options(argc, argv, arg, arg, nullptr, &filter, nullptr);
	if (unnamedargs < 0)
		goto done;

	err = imgtool::directory::open(*partition, path, imgenum);
>>>>>>> upstream/master
	if (err)
		goto done;

	memset(&ent, 0, sizeof(ent));

<<<<<<< HEAD
	while (((err = imgtool_directory_get_next(imgenum, &ent)) == 0) && !ent.eof)
	{
		fprintf(stdout, "Retrieving %s (%u bytes)\n", ent.filename, (unsigned int) ent.filesize);

		err = imgtool_partition_get_file(partition, ent.filename, NULL, NULL, filter);
=======
	while (((err = imgenum->get_next(ent)) == 0) && !ent.eof)
	{
		util::stream_format(std::wcout, L"Retrieving %s (%u bytes)\n", wstring_from_utf8(ent.filename), (unsigned int)ent.filesize);

		err = partition->get_file(ent.filename, nullptr, nullptr, filter);
>>>>>>> upstream/master
		if (err)
			goto done;
	}

done:
<<<<<<< HEAD
	if (imgenum)
		imgtool_directory_close(imgenum);
	if (partition)
		imgtool_partition_close(partition);
	if (image)
		imgtool_image_close(image);
	if (err)
		reporterror(err, c, argv[0], argv[1], NULL, NULL, NULL);
=======
	if (err)
		reporterror(err, c, argv[0], argv[1], nullptr, nullptr, nullptr);
>>>>>>> upstream/master
	return err ? -1 : 0;
}



static int cmd_del(const struct command *c, int argc, char *argv[])
{
	imgtoolerr_t err;
<<<<<<< HEAD
	imgtool_image *image = NULL;
	imgtool_partition *partition = NULL;
	int partition_index = 0;

	err = imgtool_image_open_byname(argv[0], argv[1], OSD_FOPEN_RW, &image);
	if (err)
		goto done;

	err = imgtool_partition_open(image, partition_index, &partition);
	if (err)
		goto done;

	err = imgtool_partition_delete_file(partition, argv[2]);
=======
	imgtool::image::ptr image;
	imgtool::partition::ptr partition;
	int partition_index = 0;

	err = imgtool::image::open(argv[0], argv[1], OSD_FOPEN_RW, image);
	if (err)
		goto done;

	err = imgtool::partition::open(*image, partition_index, partition);
	if (err)
		goto done;

	err = partition->delete_file(argv[2]);
>>>>>>> upstream/master
	if (err)
		goto done;

done:
<<<<<<< HEAD
	if (partition)
		imgtool_partition_close(partition);
	if (image)
		imgtool_image_close(image);
	if (err)
		reporterror(err, c, argv[0], argv[1], argv[2], NULL, NULL);
=======
	if (err)
		reporterror(err, c, argv[0], argv[1], argv[2], nullptr, nullptr);
>>>>>>> upstream/master
	return err ? -1 : 0;
}



static int cmd_mkdir(const struct command *c, int argc, char *argv[])
{
	imgtoolerr_t err;
<<<<<<< HEAD
	imgtool_image *image = NULL;
	imgtool_partition *partition = NULL;
	int partition_index = 0;

	err = imgtool_image_open_byname(argv[0], argv[1], OSD_FOPEN_RW, &image);
	if (err)
		goto done;

	err = imgtool_partition_open(image, partition_index, &partition);
	if (err)
		goto done;

	err = imgtool_partition_create_directory(partition, argv[2]);
=======
	imgtool::image::ptr image;
	imgtool::partition::ptr partition;
	int partition_index = 0;

	err = imgtool::image::open(argv[0], argv[1], OSD_FOPEN_RW, image);
	if (err)
		goto done;

	err = imgtool::partition::open(*image, partition_index, partition);
	if (err)
		goto done;

	err = partition->create_directory(argv[2]);
>>>>>>> upstream/master
	if (err)
		goto done;

done:
<<<<<<< HEAD
	if (partition)
		imgtool_partition_close(partition);
	if (image)
		imgtool_image_close(image);
	if (err)
		reporterror(err, c, argv[0], argv[1], argv[2], NULL, NULL);
=======
	if (err)
		reporterror(err, c, argv[0], argv[1], argv[2], nullptr, nullptr);
>>>>>>> upstream/master
	return err ? -1 : 0;
}



static int cmd_rmdir(const struct command *c, int argc, char *argv[])
{
	imgtoolerr_t err;
<<<<<<< HEAD
	imgtool_image *image = NULL;
	imgtool_partition *partition = NULL;
	int partition_index = 0;

	err = imgtool_image_open_byname(argv[0], argv[1], OSD_FOPEN_RW, &image);
	if (err)
		goto done;

	err = imgtool_partition_open(image, partition_index, &partition);
	if (err)
		goto done;

	err = imgtool_partition_delete_directory(partition, argv[2]);
=======
	imgtool::image::ptr image;
	imgtool::partition::ptr partition;
	int partition_index = 0;

	err = imgtool::image::open(argv[0], argv[1], OSD_FOPEN_RW, image);
	if (err)
		goto done;

	err = imgtool::partition::open(*image, partition_index, partition);
	if (err)
		goto done;

	err = partition->delete_directory(argv[2]);
>>>>>>> upstream/master
	if (err)
		goto done;

done:
<<<<<<< HEAD
	if (partition)
		imgtool_partition_close(partition);
	if (image)
		imgtool_image_close(image);
	if (err)
		reporterror(err, c, argv[0], argv[1], argv[2], NULL, NULL);
=======
	if (err)
		reporterror(err, c, argv[0], argv[1], argv[2], nullptr, nullptr);
>>>>>>> upstream/master
	return err ? -1 : 0;
}



static int cmd_identify(const struct command *c, int argc, char *argv[])
{
	imgtool_module *modules[128];
	imgtoolerr_t err;
	int i;

<<<<<<< HEAD
	err = imgtool_identify_file(argv[0], modules, ARRAY_LENGTH(modules));
	if (err)
		goto error;

	for (i = 0; modules[i]; i++)
	{
		printf("%.16s %s\n", modules[i]->name, modules[i]->description);
	}

	return 0;

error:
	reporterror(err, c, NULL, argv[0], NULL, NULL, 0);
	return -1;
=======
	err = imgtool::image::identify_file(argv[0], modules, ARRAY_LENGTH(modules));
	if (err)
	{
		reporterror(err, c, nullptr, argv[0], nullptr, nullptr, nullptr);
		return -1;
	}
	else
	{
		for (i = 0; modules[i]; i++)
		{
			util::stream_format(std::wcout, L"%.16s %s\n", wstring_from_utf8(modules[i]->name), wstring_from_utf8(modules[i]->description));
		}

		return 0;
	}
>>>>>>> upstream/master
}



static int cmd_create(const struct command *c, int argc, char *argv[])
{
	imgtoolerr_t err;
	int unnamedargs;
	const imgtool_module *module;
<<<<<<< HEAD
	option_resolution *resolution = NULL;
=======
	std::unique_ptr<util::option_resolution> resolution;
>>>>>>> upstream/master

	module = imgtool_find_module(argv[0]);
	if (!module)
	{
		err = (imgtoolerr_t)(IMGTOOLERR_MODULENOTFOUND | IMGTOOLERR_SRC_MODULE);
		goto error;
	}

	if (module->createimage_optguide && module->createimage_optspec)
	{
<<<<<<< HEAD
		resolution = option_resolution_create(module->createimage_optguide, module->createimage_optspec);
		if (!resolution)
=======
		try { resolution.reset(new util::option_resolution(*module->createimage_optguide)); }
		catch (...)
>>>>>>> upstream/master
		{
			err = IMGTOOLERR_OUTOFMEMORY;
			goto error;
		}
<<<<<<< HEAD
	}

	unnamedargs = parse_options(argc, argv, 2, 3, resolution, NULL, NULL);
	if (unnamedargs < 0)
		return -1;

	err = imgtool_image_create(module, argv[1], resolution, NULL);
	if (err)
		goto error;

	if (resolution)
		option_resolution_close(resolution);
	return 0;

error:
	if (resolution)
		option_resolution_close(resolution);
	reporterror(err, c, argv[0], argv[1], NULL, NULL, 0);
=======
		resolution->set_specification(module->createimage_optspec);
	}

	unnamedargs = parse_options(argc, argv, 2, 3, resolution.get(), nullptr, nullptr);
	if (unnamedargs < 0)
		return -1;

	err = imgtool::image::create(module, argv[1], resolution.get());
	if (err)
		goto error;

	return 0;

error:
	reporterror(err, c, argv[0], argv[1], nullptr, nullptr, nullptr);
>>>>>>> upstream/master
	return -1;
}



static int cmd_readsector(const struct command *c, int argc, char *argv[])
{
	imgtoolerr_t err;
<<<<<<< HEAD
	imgtool_image *img;
	imgtool_stream *stream = NULL;
	dynamic_buffer buffer;
	UINT32 size, track, head, sector;

	/* attempt to open image */
	err = imgtool_image_open_byname(argv[0], argv[1], OSD_FOPEN_READ, &img);
=======
	std::unique_ptr<imgtool::image> img;
	imgtool::stream::ptr stream;
	std::vector<uint8_t> buffer;
	uint32_t track, head, sector;

	/* attempt to open image */
	err = imgtool::image::open(argv[0], argv[1], OSD_FOPEN_READ, img);
>>>>>>> upstream/master
	if (err)
		goto done;

	track = atoi(argv[2]);
	head = atoi(argv[3]);
	sector = atoi(argv[4]);

<<<<<<< HEAD
	err = imgtool_image_get_sector_size(img, track, head, sector, &size);
	if (err)
		goto done;

	buffer.resize(size);

	err = imgtool_image_read_sector(img, track, head, sector, &buffer[0], size);
	if (err)
		goto done;


	stream = stream_open(argv[5], OSD_FOPEN_WRITE);
=======
	err = img->read_sector(track, head, sector, buffer);
	if (err)
		goto done;

	stream = imgtool::stream::open(argv[5], OSD_FOPEN_WRITE);
>>>>>>> upstream/master
	if (!stream)
	{
		err = (imgtoolerr_t)(IMGTOOLERR_FILENOTFOUND | IMGTOOLERR_SRC_NATIVEFILE);
		goto done;
	}

<<<<<<< HEAD
	stream_write(stream, &buffer[0], size);

done:
	if (stream)
		stream_close(stream);
	if (err)
		reporterror(err, c, argv[0], argv[1], NULL, NULL, 0);
=======
	stream->write(&buffer[0], buffer.size());

done:
	if (err)
		reporterror(err, c, argv[0], argv[1], nullptr, nullptr, nullptr);
>>>>>>> upstream/master
	return err ? -1 : 0;
}



static int cmd_writesector(const struct command *c, int argc, char *argv[])
{
	imgtoolerr_t err;
<<<<<<< HEAD
	imgtool_image *img;
	imgtool_stream *stream = NULL;
	dynamic_buffer buffer;
	UINT32 size, track, head, sector;

	/* attempt to open image */
	err = imgtool_image_open_byname(argv[0], argv[1], OSD_FOPEN_RW, &img);
=======
	std::unique_ptr<imgtool::image> img;
	imgtool::stream::ptr stream;
	std::vector<uint8_t> buffer;
	uint32_t size, track, head, sector;

	// attempt to open image
	err = imgtool::image::open(argv[0], argv[1], OSD_FOPEN_RW, img);
>>>>>>> upstream/master
	if (err)
		goto done;

	track = atoi(argv[2]);
	head = atoi(argv[3]);
	sector = atoi(argv[4]);

<<<<<<< HEAD
	stream = stream_open(argv[5], OSD_FOPEN_READ);
=======
	stream = imgtool::stream::open(argv[5], OSD_FOPEN_READ);
>>>>>>> upstream/master
	if (!stream)
	{
		err = (imgtoolerr_t)(IMGTOOLERR_FILENOTFOUND | IMGTOOLERR_SRC_NATIVEFILE);
		goto done;
	}

<<<<<<< HEAD
	size = (UINT32) stream_size(stream);

	buffer.resize(size);

	stream_read(stream, &buffer[0], size);

	err = imgtool_image_write_sector(img, track, head, sector, &buffer[0], size);
=======
	size = (uint32_t) stream->size();

	buffer.resize(size);

	stream->read(&buffer[0], size);

	err = img->write_sector(track, head, sector, &buffer[0], size);
>>>>>>> upstream/master
	if (err)
		goto done;

done:
<<<<<<< HEAD
	if (stream)
		stream_close(stream);
	if (err)
		reporterror(err, c, argv[0], argv[1], NULL, NULL, 0);
=======
	if (err)
		reporterror(err, c, argv[0], argv[1], nullptr, nullptr, nullptr);
>>>>>>> upstream/master
	return err ? -1 : 0;
}



static int cmd_listformats(const struct command *c, int argc, char *argv[])
{
<<<<<<< HEAD
	const imgtool_module *mod;

	fprintf(stdout, "Image formats supported by imgtool:\n\n");

	mod = imgtool_find_module(NULL);
	while(mod)
	{
		fprintf(stdout, "  %-25s%s\n", mod->name, mod->description);
		mod = mod->next;
=======
	util::stream_format(std::wcout, L"Image formats supported by imgtool:\n\n");

	for (const auto &module : imgtool_get_modules())
	{
		util::stream_format(std::wcout, L"  %-25s%s\n", wstring_from_utf8(module->name), wstring_from_utf8(module->description));
>>>>>>> upstream/master
	}

	return 0;
}



static int cmd_listfilters(const struct command *c, int argc, char *argv[])
{
	int i;

<<<<<<< HEAD
	fprintf(stdout, "Filters supported by imgtool:\n\n");

	for (i = 0; filters[i]; i++)
	{
		fprintf(stdout, "  %-11s%s\n",
			filter_get_info_string(filters[i], FILTINFO_STR_NAME),
			filter_get_info_string(filters[i], FILTINFO_STR_HUMANNAME));
=======
	util::stream_format(std::wcout, L"Filters supported by imgtool:\n\n");

	for (i = 0; filters[i]; i++)
	{
		util::stream_format(std::wcout, L"  %-11s%s\n",
			wstring_from_utf8(filter_get_info_string(filters[i], FILTINFO_STR_NAME)),
			wstring_from_utf8(filter_get_info_string(filters[i], FILTINFO_STR_HUMANNAME)));
>>>>>>> upstream/master
	}

	return 0;
}

<<<<<<< HEAD
static void listoptions(const option_guide *opt_guide, const char *opt_spec)
{
	char opt_name[32];
	const char *opt_desc;
	struct OptionRange range[32];
	char range_buffer[512];
	char buf[32];
	int i;

	assert(opt_guide);

	fprintf(stdout, "Option           Allowed values                 Description\n");
	fprintf(stdout, "---------------- ------------------------------ -----------\n");

	while(opt_guide->option_type != OPTIONTYPE_END)
	{
		range_buffer[0] = 0;
		snprintf(opt_name, ARRAY_LENGTH(opt_name), "--%s", opt_guide->identifier);
		opt_desc = opt_guide->display_name;

		/* is this option relevant? */
		if (!strchr(opt_spec, opt_guide->parameter))
		{
			opt_guide++;
			continue;
		}

		switch(opt_guide->option_type) {
		case OPTIONTYPE_INT:
			option_resolution_listranges(opt_spec, opt_guide->parameter,
				range, ARRAY_LENGTH(range));

			for (i = 0; range[i].max >= 0; i++)
			{
				if (range[i].min == range[i].max)
					snprintf(buf, ARRAY_LENGTH(buf), "%i", range[i].min);
				else
					snprintf(buf, ARRAY_LENGTH(buf), "%i-%i", range[i].min, range[i].max);

				if (i > 0)
					strncatz(range_buffer, "/", sizeof(range_buffer));
				strncatz(range_buffer, buf, sizeof(range_buffer));
			}
			break;

		case OPTIONTYPE_ENUM_BEGIN:
			i = 0;
			while(opt_guide[1].option_type == OPTIONTYPE_ENUM_VALUE)
			{
				if (i > 0)
					strncatz(range_buffer, "/", sizeof(range_buffer));
				strncatz(range_buffer, opt_guide[1].identifier, sizeof(range_buffer));

				opt_guide++;
				i++;
			}
			break;

		case OPTIONTYPE_STRING:
			snprintf(range_buffer, sizeof(range_buffer), "(string)");
			break;
=======
static void listoptions(const util::option_guide &opt_guide, const char *opt_spec)
{
	util::option_resolution resolution(opt_guide);
	resolution.set_specification(opt_spec);

	util::stream_format(std::wcout, L"Option           Allowed values                 Description\n");
	util::stream_format(std::wcout, L"---------------- ------------------------------ -----------\n");

	for (auto iter = resolution.entries_begin(); iter != resolution.entries_end(); iter++)
	{
		const util::option_resolution::entry &entry = *iter;
				std::stringstream description_buffer;

		std::string opt_name = string_format("--%s", entry.identifier());
		const char *opt_desc = entry.display_name();

		// is this option relevant?
		if (!strchr(opt_spec, entry.parameter()))
			continue;

		switch (entry.option_type())
		{
		case util::option_guide::entry::option_type::INT:
			for (const auto &range : entry.ranges())
			{
				if (!description_buffer.str().empty())
					description_buffer << "/";

				if (range.min == range.max)
					util::stream_format(description_buffer, "%d", range.min);
				else
					util::stream_format(description_buffer, "%d-%d", range.min, range.max);
			}
			break;

		case util::option_guide::entry::option_type::ENUM_BEGIN:
			for (auto enum_value = entry.enum_value_begin(); enum_value != entry.enum_value_end(); enum_value++)
			{
				if (!description_buffer.str().empty())
					description_buffer << '/';
				description_buffer << enum_value->identifier();
			}
			break;

		case util::option_guide::entry::option_type::STRING:
			description_buffer << "(string)";
			break;

>>>>>>> upstream/master
		default:
			assert(0);
			break;
		}

<<<<<<< HEAD
		fprintf(stdout, "%16s %-30s %s\n",
			opt_name,
			range_buffer,
			opt_desc);
		opt_guide++;
=======
		util::stream_format(std::wcout, L"%16s %-30s %s\n",
			wstring_from_utf8(opt_name),
			wstring_from_utf8(description_buffer.str()),
			wstring_from_utf8(opt_desc));
>>>>>>> upstream/master
	}
}



static int cmd_listdriveroptions(const struct command *c, int argc, char *argv[])
{
	const imgtool_module *mod;
<<<<<<< HEAD
	const option_guide *opt_guide;
=======
	const util::option_guide *opt_guide;
>>>>>>> upstream/master
	const char *opt_spec;

	mod = imgtool_find_module(argv[0]);
	if (!mod)
<<<<<<< HEAD
		goto error;

	fprintf(stdout, "Driver specific options for module '%s':\n\n", argv[0]);

	/* list write options */
	opt_guide = (const option_guide *) imgtool_get_info_ptr(&mod->imgclass, IMGTOOLINFO_PTR_WRITEFILE_OPTGUIDE);
	opt_spec = imgtool_get_info_string(&mod->imgclass, IMGTOOLINFO_STR_WRITEFILE_OPTSPEC);
	if (opt_guide)
	{
		fprintf(stdout, "Image specific file options (usable on the 'put' command):\n\n");
		listoptions(opt_guide, opt_spec);
		puts("\n");
	}
	else
	{
		fprintf(stdout, "No image specific file options\n\n");
=======
	{
		reporterror((imgtoolerr_t)(IMGTOOLERR_MODULENOTFOUND|IMGTOOLERR_SRC_MODULE), c, argv[0], nullptr, nullptr, nullptr, nullptr);
		return -1;
	}

	util::stream_format(std::wcout, L"Driver specific options for module '%s':\n\n", wstring_from_utf8(argv[0]));

	/* list write options */
	opt_guide = (const util::option_guide *) imgtool_get_info_ptr(&mod->imgclass, IMGTOOLINFO_PTR_WRITEFILE_OPTGUIDE);
	opt_spec = imgtool_get_info_string(&mod->imgclass, IMGTOOLINFO_STR_WRITEFILE_OPTSPEC);
	if (opt_guide)
	{
		util::stream_format(std::wcout, L"Image specific file options (usable on the 'put' command):\n\n");
		listoptions(*opt_guide, opt_spec);
		util::stream_format(std::wcout, L"\n");
	}
	else
	{
		util::stream_format(std::wcout, L"No image specific file options\n\n");
>>>>>>> upstream/master
	}

	/* list create options */
	opt_guide = mod->createimage_optguide;
	if (opt_guide)
	{
<<<<<<< HEAD
		fprintf(stdout, "Image specific creation options (usable on the 'create' command):\n\n");
		listoptions(opt_guide, mod->createimage_optspec);
		puts("\n");
	}
	else
	{
		fprintf(stdout, "No image specific creation options\n\n");
	}

	return 0;

error:
	reporterror((imgtoolerr_t)(IMGTOOLERR_MODULENOTFOUND|IMGTOOLERR_SRC_MODULE), c, argv[0], NULL, NULL, NULL, NULL);
	return -1;
=======
		util::stream_format(std::wcout, L"Image specific creation options (usable on the 'create' command):\n\n");
		listoptions(*opt_guide, mod->createimage_optspec);
		util::stream_format(std::wcout, L"\n");
	}
	else
	{
		util::stream_format(std::wcout, L"No image specific creation options\n\n");
	}

	return 0;
>>>>>>> upstream/master
}



/* ----------------------------------------------------------------------- */

static const struct command cmds[] =
{
	{ "create",             cmd_create,             "<format> <imagename> [--(createoption)=value]", 2, 8, 0},
	{ "dir",                cmd_dir,                "<format> <imagename> [path]", 2, 3, 0 },
	{ "get",                cmd_get,                "<format> <imagename> <filename> [newname] [--filter=filter] [--fork=fork]", 3, 4, 0 },
	{ "put",                cmd_put,                "<format> <imagename> <filename>... <destname> [--(fileoption)==value] [--filter=filter] [--fork=fork]", 3, 0xffff, 0 },
	{ "getall",             cmd_getall,             "<format> <imagename> [path] [--filter=filter]", 2, 3, 0 },
	{ "del",                cmd_del,                "<format> <imagename> <filename>...", 3, 3, 1 },
	{ "mkdir",              cmd_mkdir,              "<format> <imagename> <dirname>", 3, 3, 0 },
	{ "rmdir",              cmd_rmdir,              "<format> <imagename> <dirname>...", 3, 3, 1 },
	{ "readsector",         cmd_readsector,         "<format> <imagename> <track> <head> <sector> <filename>", 6, 6, 0 },
	{ "writesector",        cmd_writesector,        "<format> <imagename> <track> <head> <sector> <filename>", 6, 6, 0 },
	{ "identify",           cmd_identify,           "<imagename>", 1, 1 },
<<<<<<< HEAD
	{ "listformats",        cmd_listformats,        NULL, 0, 0, 0 },
	{ "listfilters",        cmd_listfilters,        NULL, 0, 0, 0 },
	{ "listdriveroptions",  cmd_listdriveroptions, "<format>", 1, 1, 0 }
};

int CLIB_DECL main(int argc, char *argv[])
=======
	{ "listformats",        cmd_listformats,        nullptr, 0, 0, 0 },
	{ "listfilters",        cmd_listfilters,        nullptr, 0, 0, 0 },
	{ "listdriveroptions",  cmd_listdriveroptions, "<format>", 1, 1, 0 }
};


// ----------------------------------------------------------------------

int main(int argc, char *argv[])
>>>>>>> upstream/master
{
	int i;
	int result;
	const struct command *c;
	const char *sample_format = "coco_jvc_rsdos";
<<<<<<< HEAD
=======
	std::string cmdname = core_filename_extract_base(argv[0]);

#ifdef _WIN32
	_setmode(_fileno(stdout), _O_U8TEXT);
#endif // _WIN32
>>>>>>> upstream/master

#ifdef MAME_DEBUG
	if (imgtool_validitychecks())
		return -1;
<<<<<<< HEAD
#endif /* MAME_DEBUG */

	putchar('\n');
=======
#endif // MAME_DEBUG

	util::stream_format(std::wcout, L"\n");
>>>>>>> upstream/master

	if (argc > 1)
	{
		/* figure out what command they are running, and run it */
		for (i = 0; i < ARRAY_LENGTH(cmds); i++)
		{
			c = &cmds[i];
			if (!core_stricmp(c->name, argv[1]))
			{
				/* check argument count */
				if (c->minargs > (argc - 2))
					goto cmderror;

				/* initialize the imgtool core */
<<<<<<< HEAD
				imgtool_init(TRUE, NULL);
=======
				imgtool_init(true, nullptr);
>>>>>>> upstream/master

				if (c->lastargrepeats && (argc > c->maxargs))
				{
					for (i = c->maxargs+1; i < argc; i++)
					{
						argv[c->maxargs+1] = argv[i];

						result = c->cmdproc(c, c->maxargs, argv + 2);
						if (result)
							goto done;
					}
					result = 0;
					goto done;
				}
				else
				{
					if ((c->maxargs > 0) && (c->maxargs < (argc - 2)))
						goto cmderror;

					result = c->cmdproc(c, argc - 2, argv + 2);
					goto done;
				}
			}
		}
	}

<<<<<<< HEAD
	/* Usage */
	fprintf(stderr, "imgtool - Generic image manipulation tool for use with MESS\n\n");
	for (i = 0; i < ARRAY_LENGTH(cmds); i++)
	{
		writeusage(stdout, (i == 0), &cmds[i], argv);
	}

	fprintf(stderr, "\n<format> is the image format, e.g. %s\n", sample_format);
	fprintf(stderr, "<imagename> is the image filename; can specify a ZIP file for image name\n");

	fprintf(stderr, "\nExample usage:\n");
	fprintf(stderr, "\t%s dir %s myimageinazip.zip\n", imgtool_basename(argv[0]), sample_format);
	fprintf(stderr, "\t%s get %s myimage.dsk myfile.bin mynewfile.txt\n", imgtool_basename(argv[0]), sample_format);
	fprintf(stderr, "\t%s getall %s myimage.dsk\n", imgtool_basename(argv[0]), sample_format);
=======
	// Usage
	util::stream_format(std::wcerr, L"imgtool - Generic image manipulation tool for use with MAME\n\n");
	for (i = 0; i < ARRAY_LENGTH(cmds); i++)
	{
		writeusage(std::wcerr, (i == 0), &cmds[i], argv);
	}
	util::stream_format(std::wcerr, L"\n<format> is the image format, e.g. %s\n", wstring_from_utf8(sample_format));
	util::stream_format(std::wcerr, L"<imagename> is the image filename; can specify a ZIP file for image name\n");

	util::stream_format(std::wcerr, L"\nExample usage:\n");
	util::stream_format(std::wcerr, L"\t%s dir %s myimageinazip.zip\n", wstring_from_utf8(cmdname), wstring_from_utf8(sample_format));
	util::stream_format(std::wcerr, L"\t%s get %s myimage.dsk myfile.bin mynewfile.txt\n", wstring_from_utf8(cmdname), wstring_from_utf8(sample_format));
	util::stream_format(std::wcerr, L"\t%s getall %s myimage.dsk\n", wstring_from_utf8(cmdname), wstring_from_utf8(sample_format));
>>>>>>> upstream/master
	result = 0;
	goto done;

cmderror:
<<<<<<< HEAD
	writeusage(stdout, 1, &cmds[i], argv);
=======
	writeusage(std::wcout, 1, &cmds[i], argv);
>>>>>>> upstream/master
	result = -1;

done:
	imgtool_exit();
	return result;
}
