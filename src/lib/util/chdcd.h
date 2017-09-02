// license:BSD-3-Clause
// copyright-holders:R. Belmont
/***************************************************************************

    CDRDAO TOC parser for CHD compression frontend

***************************************************************************/

#pragma once

#ifndef __CHDCD_H__
#define __CHDCD_H__

#include "cdrom.h"

struct chdcd_track_input_entry
{
	chdcd_track_input_entry() { reset(); }
	void reset() { fname.clear(); offset = idx0offs = idx1offs = 0; swap = false; }

	std::string fname;      // filename for each track
<<<<<<< HEAD
	UINT32 offset;      // offset in the data file for each track
	bool swap;          // data needs to be byte swapped
	UINT32 idx0offs;
	UINT32 idx1offs;
=======
	uint32_t offset;      // offset in the data file for each track
	bool swap;          // data needs to be byte swapped
	uint32_t idx0offs;
	uint32_t idx1offs;
>>>>>>> upstream/master
};

struct chdcd_track_input_info
{
<<<<<<< HEAD
	void reset() { for (int i = 0; i < CD_MAX_TRACKS; i++) track[i].reset(); }
=======
	void reset() { for (auto & elem : track) elem.reset(); }
>>>>>>> upstream/master

	chdcd_track_input_entry track[CD_MAX_TRACKS];
};


chd_error chdcd_parse_toc(const char *tocfname, cdrom_toc &outtoc, chdcd_track_input_info &outinfo);

#endif  /* __CHDCD_H__ */
