// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/****************************************************************************

<<<<<<< HEAD
    library.c

    Code relevant to the Imgtool library; analgous to the MESS/MAME driver
=======
    library.cpp

    Code relevant to the Imgtool library; analogous to the MESS/MAME driver
>>>>>>> upstream/master
    list.

****************************************************************************/

#include <string.h>
<<<<<<< HEAD
=======
#include <algorithm>
>>>>>>> upstream/master

#include "imgtool.h"
#include "library.h"
#include "pool.h"

<<<<<<< HEAD
struct imgtool_library
{
	object_pool *pool;
	imgtool_module *first;
	imgtool_module *last;
};



imgtool_library *imgtool_library_create(void)
{
	imgtool_library *library;
	object_pool *pool;

	/* create a memory pool */
	pool = pool_alloc_lib(NULL);
	if (!pool)
		goto error;

	/* allocate the main structure */
	library = (imgtool_library *)pool_malloc_lib(pool, sizeof(imgtool_library));
	if (!library)
		goto error;

	/* initialize the structure */
	memset(library, 0, sizeof(*library));
	library->pool = pool;

	return library;

error:
	if (pool)
		pool_free_lib(pool);
	return NULL;
}



void imgtool_library_close(imgtool_library *library)
{
	pool_free_lib(library->pool);
}



static void imgtool_library_add_class(imgtool_library *library, const imgtool_class *imgclass)
{
	imgtool_module *module;
	char *s1, *s2;

	/* allocate the module and place it in the chain */
	module = (imgtool_module *)imgtool_library_malloc(library, sizeof(*module));
	memset(module, 0, sizeof(*module));
	module->previous = library->last;
	if (library->last)
		library->last->next = module;
	else
		library->first = module;
	library->last = module;

	/* extensions have a weird format */
	s1 = imgtool_get_info_string(imgclass, IMGTOOLINFO_STR_FILE_EXTENSIONS);
	s2 = (char*)imgtool_library_malloc(library, strlen(s1) + 1);
=======
namespace imgtool {


//-------------------------------------------------
//  ctor
//-------------------------------------------------

library::library()
{
	m_pool = pool_alloc_lib(nullptr);
	if (!m_pool)
		throw std::bad_alloc();
}


//-------------------------------------------------
//  dtor
//-------------------------------------------------

library::~library()
{
	pool_free_lib(m_pool);
}


//-------------------------------------------------
//  add_class
//-------------------------------------------------

void library::add_class(const imgtool_class *imgclass)
{
	char *s1, *s2;

	// allocate the module and place it in the chain
	m_modules.emplace_back(std::make_unique<imgtool_module>());
	imgtool_module *module = m_modules.back().get();
	memset(module, 0, sizeof(*module));

	// extensions have a weird format
	s1 = imgtool_get_info_string(imgclass, IMGTOOLINFO_STR_FILE_EXTENSIONS);
	s2 = (char*)imgtool_library_malloc(strlen(s1) + 1);
>>>>>>> upstream/master
	strcpy(s2, s1);
	module->extensions = s2;

	module->imgclass                    = *imgclass;
<<<<<<< HEAD
	module->name                        = imgtool_library_strdup(library, imgtool_get_info_string(imgclass, IMGTOOLINFO_STR_NAME));
	module->description                 = imgtool_library_strdup(library, imgtool_get_info_string(imgclass, IMGTOOLINFO_STR_DESCRIPTION));
	module->eoln                        = imgtool_library_strdup_allow_null(library, imgtool_get_info_string(imgclass, IMGTOOLINFO_STR_EOLN));
=======
	module->name                        = imgtool_library_strdup(imgtool_get_info_string(imgclass, IMGTOOLINFO_STR_NAME));
	module->description                 = imgtool_library_strdup(imgtool_get_info_string(imgclass, IMGTOOLINFO_STR_DESCRIPTION));
	module->eoln                        = imgtool_library_strdup_allow_null(imgtool_get_info_string(imgclass, IMGTOOLINFO_STR_EOLN));
>>>>>>> upstream/master
	module->initial_path_separator      = imgtool_get_info_int(imgclass, IMGTOOLINFO_INT_INITIAL_PATH_SEPARATOR) ? 1 : 0;
	module->open_is_strict              = imgtool_get_info_int(imgclass, IMGTOOLINFO_INT_OPEN_IS_STRICT) ? 1 : 0;
	module->tracks_are_called_cylinders = imgtool_get_info_int(imgclass, IMGTOOLINFO_INT_TRACKS_ARE_CALLED_CYLINDERS) ? 1 : 0;
	module->writing_untested            = imgtool_get_info_int(imgclass, IMGTOOLINFO_INT_WRITING_UNTESTED) ? 1 : 0;
	module->creation_untested           = imgtool_get_info_int(imgclass, IMGTOOLINFO_INT_CREATION_UNTESTED) ? 1 : 0;
<<<<<<< HEAD
	module->open                        = (imgtoolerr_t (*)(imgtool_image *, imgtool_stream *)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_OPEN);
	module->create                      = (imgtoolerr_t (*)(imgtool_image *, imgtool_stream *, option_resolution *)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_CREATE);
	module->close                       = (void (*)(imgtool_image *)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_CLOSE);
	module->info                        = (void (*)(imgtool_image *, char *, size_t)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_INFO);
	module->read_sector                 = (imgtoolerr_t (*)(imgtool_image *, UINT32, UINT32, UINT32, void *, size_t)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_READ_SECTOR);
	module->write_sector                = (imgtoolerr_t (*)(imgtool_image *, UINT32, UINT32, UINT32, const void *, size_t)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_WRITE_SECTOR);
	module->get_geometry                = (imgtoolerr_t (*)(imgtool_image *, UINT32 *, UINT32 *, UINT32 *))imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_GET_GEOMETRY);
	module->get_sector_size             = (imgtoolerr_t (*)(imgtool_image *, UINT32, UINT32, UINT32, UINT32 *))imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_GET_SECTOR_SIZE);
	module->read_block                  = (imgtoolerr_t (*)(imgtool_image *, void *, UINT64)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_READ_BLOCK);
	module->write_block                 = (imgtoolerr_t (*)(imgtool_image *, const void *, UINT64)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_WRITE_BLOCK);
	module->list_partitions             = (imgtoolerr_t (*)(imgtool_image *, imgtool_partition_info *, size_t)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_LIST_PARTITIONS);
	module->block_size                  = imgtool_get_info_int(imgclass, IMGTOOLINFO_INT_BLOCK_SIZE);
	module->createimage_optguide        = (const option_guide *) imgtool_get_info_ptr(imgclass, IMGTOOLINFO_PTR_CREATEIMAGE_OPTGUIDE);
	module->createimage_optspec         = imgtool_library_strdup_allow_null(library, (const char*)imgtool_get_info_ptr(imgclass, IMGTOOLINFO_STR_CREATEIMAGE_OPTSPEC));
=======
	module->open                        = (imgtoolerr_t (*)(imgtool::image &, imgtool::stream::ptr &&)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_OPEN);
	module->create                      = (imgtoolerr_t (*)(imgtool::image &, imgtool::stream::ptr &&, util::option_resolution *)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_CREATE);
	module->close                       = (void (*)(imgtool::image &)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_CLOSE);
	module->info                        = (void (*)(imgtool::image &, std::ostream &)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_INFO);
	module->read_sector                 = (imgtoolerr_t (*)(imgtool::image &, uint32_t, uint32_t, uint32_t, std::vector<uint8_t> &)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_READ_SECTOR);
	module->write_sector                = (imgtoolerr_t (*)(imgtool::image &, uint32_t, uint32_t, uint32_t, const void *, size_t)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_WRITE_SECTOR);
	module->get_geometry                = (imgtoolerr_t (*)(imgtool::image &, uint32_t *, uint32_t *, uint32_t *))imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_GET_GEOMETRY);
	module->read_block                  = (imgtoolerr_t (*)(imgtool::image &, void *, uint64_t)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_READ_BLOCK);
	module->write_block                 = (imgtoolerr_t (*)(imgtool::image &, const void *, uint64_t)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_WRITE_BLOCK);
	module->list_partitions             = (imgtoolerr_t (*)(imgtool::image &, std::vector<imgtool::partition_info> &)) imgtool_get_info_fct(imgclass, IMGTOOLINFO_PTR_LIST_PARTITIONS);
	module->block_size                  = imgtool_get_info_int(imgclass, IMGTOOLINFO_INT_BLOCK_SIZE);
	module->createimage_optguide        = (const util::option_guide *) imgtool_get_info_ptr(imgclass, IMGTOOLINFO_PTR_CREATEIMAGE_OPTGUIDE);
	module->createimage_optspec         = imgtool_library_strdup_allow_null((const char*)imgtool_get_info_ptr(imgclass, IMGTOOLINFO_STR_CREATEIMAGE_OPTSPEC));
>>>>>>> upstream/master
	module->image_extra_bytes           += imgtool_get_info_int(imgclass, IMGTOOLINFO_INT_IMAGE_EXTRA_BYTES);
}


<<<<<<< HEAD

void imgtool_library_add(imgtool_library *library, imgtool_get_info get_info)
=======
//-------------------------------------------------
//  add
//-------------------------------------------------

void library::add(imgtool_get_info get_info)
>>>>>>> upstream/master
{
	int (*make_class)(int index, imgtool_class *imgclass);
	imgtool_class imgclass;
	int i, result;

<<<<<<< HEAD
	/* try this class */
	memset(&imgclass, 0, sizeof(imgclass));
	imgclass.get_info = get_info;

	/* do we have derived getinfo functions? */
=======
	// try this class
	memset(&imgclass, 0, sizeof(imgclass));
	imgclass.get_info = get_info;

	// do we have derived getinfo functions?
>>>>>>> upstream/master
	make_class = (int (*)(int index, imgtool_class *imgclass))
		imgtool_get_info_fct(&imgclass, IMGTOOLINFO_PTR_MAKE_CLASS);

	if (make_class)
	{
		i = 0;
		do
		{
<<<<<<< HEAD
			/* clear out the class */
			memset(&imgclass, 0, sizeof(imgclass));
			imgclass.get_info = get_info;

			/* make the class */
			result = make_class(i++, &imgclass);
			if (result)
				imgtool_library_add_class(library, &imgclass);
=======
			// clear out the class
			memset(&imgclass, 0, sizeof(imgclass));
			imgclass.get_info = get_info;

			// make the class
			result = make_class(i++, &imgclass);
			if (result)
				add_class(&imgclass);
>>>>>>> upstream/master
		}
		while(result);
	}
	else
	{
<<<<<<< HEAD
		imgtool_library_add_class(library, &imgclass);
=======
		add_class(&imgclass);
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD

const imgtool_module *imgtool_library_unlink(imgtool_library *library,
	const char *module)
{
	imgtool_module *m;
	imgtool_module **previous;
	imgtool_module **next;

	for (m = library->first; m; m = m->next)
	{
		if (!core_stricmp(m->name, module))
		{
			previous = m->previous ? &m->previous->next : &library->first;
			next = m->next ? &m->next->previous : &library->last;
			*previous = m->next;
			*next = m->previous;
			m->previous = NULL;
			m->next = NULL;
			return m;
		}
	}
	return NULL;
}



static int module_compare(const imgtool_module *m1,
	const imgtool_module *m2, imgtool_libsort_t sort)
=======
//-------------------------------------------------
//  unlink
//-------------------------------------------------

void library::unlink(const std::string &module_name)
{
	const modulelist::iterator iter = find(module_name);
	if (iter != m_modules.end())
		m_modules.erase(iter);
}


//-------------------------------------------------
//  module_compare
//-------------------------------------------------

int library::module_compare(const imgtool_module *m1, const imgtool_module *m2, sort_type sort)
>>>>>>> upstream/master
{
	int rc = 0;
	switch(sort)
	{
<<<<<<< HEAD
		case ITLS_NAME:
			rc = strcmp(m1->name, m2->name);
			break;
		case ITLS_DESCRIPTION:
			rc = core_stricmp(m1->name, m2->name);
			break;
=======
	case sort_type::NAME:
		rc = strcmp(m1->name, m2->name);
		break;
	case sort_type::DESCRIPTION:
		rc = core_stricmp(m1->description, m2->description);
		break;
>>>>>>> upstream/master
	}
	return rc;
}


<<<<<<< HEAD

void imgtool_library_sort(imgtool_library *library, imgtool_libsort_t sort)
{
	imgtool_module *m1;
	imgtool_module *m2;
	imgtool_module *target;
	imgtool_module **before;
	imgtool_module **after;

	for (m1 = library->first; m1; m1 = m1->next)
	{
		target = m1;
		for (m2 = m1->next; m2; m2 = m2->next)
		{
			while(module_compare(target, m2, sort) > 0)
				target = m2;
		}

		if (target != m1)
		{
			/* unlink the target */
			before = target->previous ? &target->previous->next : &library->first;
			after = target->next ? &target->next->previous : &library->last;
			*before = target->next;
			*after = target->previous;

			/* now place the target before m1 */
			target->previous = m1->previous;
			target->next = m1;
			before = m1->previous ? &m1->previous->next : &library->first;
			*before = target;
			m1->previous = target;

			/* since we changed the order, we have to replace ourselves */
			m1 = target;
		}
	}
}



const imgtool_module *imgtool_library_findmodule(
	imgtool_library *library, const char *module_name)
{
	const imgtool_module *module;

	assert(library);
	module = library->first;
	while(module && module_name && strcmp(module->name, module_name))
		module = module->next;
	return module;
}



imgtool_module *imgtool_library_iterate(imgtool_library *library, const imgtool_module *module)
{
	return module ? module->next : library->first;
}



imgtool_module *imgtool_library_index(imgtool_library *library, int i)
{
	imgtool_module *module;
	module = library->first;
	while(module && i--)
		module = module->next;
	return module;
}



void *imgtool_library_malloc(imgtool_library *library, size_t mem)
{
	return pool_malloc_lib(library->pool, mem);
}



char *imgtool_library_strdup(imgtool_library *library, const char *s)
{
	return pool_strdup_lib(library->pool, s);
}



char *imgtool_library_strdup_allow_null(imgtool_library *library, const char *s)
{
	return s ? imgtool_library_strdup(library, s) : NULL;
}
=======
//-------------------------------------------------
//  sort
//-------------------------------------------------

void library::sort(sort_type sort)
{
	auto compare = [this, sort](const std::unique_ptr<imgtool_module> &a, const std::unique_ptr<imgtool_module> &b)
	{
		return module_compare(a.get(), b.get(), sort) < 0;
	};
	m_modules.sort(compare);
}


//-------------------------------------------------
//  find
//-------------------------------------------------

library::modulelist::iterator library::find(const std::string &module_name)
{
	return std::find_if(
		m_modules.begin(),
		m_modules.end(),
		[this, module_name](std::unique_ptr<imgtool_module> &module) { return !module_name.compare(module->name); });
}


//-------------------------------------------------
//  findmodule
//-------------------------------------------------

const imgtool_module *library::findmodule(const std::string &module_name)
{
	modulelist::iterator iter = find(module_name);
	return iter != m_modules.end()
		? iter->get()
		: nullptr;
}


//-------------------------------------------------
//  imgtool_library_malloc
//-------------------------------------------------

void *library::imgtool_library_malloc(size_t mem)
{
	return pool_malloc_lib(m_pool, mem);
}


//-------------------------------------------------
//  imgtool_library_malloc
//-------------------------------------------------

char *library::imgtool_library_strdup(const char *s)
{
	return pool_strdup_lib(m_pool, s);
}


//-------------------------------------------------
//  imgtool_library_strdup_allow_null
//-------------------------------------------------

char *library::imgtool_library_strdup_allow_null(const char *s)
{
	return s ? imgtool_library_strdup(s) : nullptr;
}


} // namespace imgtool
>>>>>>> upstream/master
