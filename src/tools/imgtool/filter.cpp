// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/***************************************************************************

    filter.c

    Imgtool filters

***************************************************************************/

#include <string.h>

#include "imgtool.h"

/* ----------------------------------------------------------------------- */

<<<<<<< HEAD
INT64 filter_get_info_int(filter_getinfoproc get_info, UINT32 state)
=======
int64_t filter_get_info_int(filter_getinfoproc get_info, uint32_t state)
>>>>>>> upstream/master
{
	union filterinfo info;
	info.i = 0;
	get_info(state, &info);
	return info.i;
}

<<<<<<< HEAD
void *filter_get_info_ptr(filter_getinfoproc get_info, UINT32 state)
{
	union filterinfo info;
	info.p = NULL;
=======
void *filter_get_info_ptr(filter_getinfoproc get_info, uint32_t state)
{
	union filterinfo info;
	info.p = nullptr;
>>>>>>> upstream/master
	get_info(state, &info);
	return info.p;
}

<<<<<<< HEAD
void *filter_get_info_fct(filter_getinfoproc get_info, UINT32 state)
{
	union filterinfo info;
	info.f = NULL;
=======
void *filter_get_info_fct(filter_getinfoproc get_info, uint32_t state)
{
	union filterinfo info;
	info.f = nullptr;
>>>>>>> upstream/master
	get_info(state, &info);
	return info.f;
}

<<<<<<< HEAD
const char *filter_get_info_string(filter_getinfoproc get_info, UINT32 state)
{
	union filterinfo info;
	info.s = NULL;
=======
const char *filter_get_info_string(filter_getinfoproc get_info, uint32_t state)
{
	union filterinfo info;
	info.s = nullptr;
>>>>>>> upstream/master
	get_info(state, &info);
	return info.s;
}

/* ----------------------------------------------------------------------- */

const filter_getinfoproc filters[] =
{
	filter_eoln_getinfo,
	filter_cocobas_getinfo,
	filter_dragonbas_getinfo,
	filter_macbinary_getinfo,
	filter_vzsnapshot_getinfo,
	filter_vzbas_getinfo,
	filter_thombas5_getinfo,
	filter_thombas7_getinfo,
	filter_thombas128_getinfo,
	filter_thomcrypt_getinfo,
	filter_bml3bas_getinfo,
<<<<<<< HEAD
	NULL
=======
		filter_hp9845data_getinfo,
	nullptr
>>>>>>> upstream/master
};



filter_getinfoproc filter_lookup(const char *name)
{
	int i;
	const char *filter_name;

	for (i = 0; filters[i]; i++)
	{
		filter_name = filter_get_info_string(filters[i], FILTINFO_STR_NAME);
		if (!strcmp(name, filter_name))
			return filters[i];
	}

<<<<<<< HEAD
	return NULL;
=======
	return nullptr;
>>>>>>> upstream/master
}
