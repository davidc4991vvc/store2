// license:BSD-3-Clause
// copyright-holders:Couriersud
/*
 * font_module.h
 *
 */

<<<<<<< HEAD
#ifndef FONT_MODULE_H_
#define FONT_MODULE_H_
=======
#ifndef MAME_OSD_MODULES_FONT_FONTMODULE_H
#define MAME_OSD_MODULES_FONT_FONTMODULE_H
>>>>>>> upstream/master

#include "osdepend.h"
#include "modules/osdmodule.h"

<<<<<<< HEAD
=======
#include <string>
#include <vector>


>>>>>>> upstream/master
//============================================================
//  CONSTANTS
//============================================================

#define OSD_FONT_PROVIDER   "uifontprovider"

class font_module
{
public:
	virtual ~font_module() { }
<<<<<<< HEAD
	virtual osd_font *font_alloc() = 0;
};


#endif /* FONT_MODULE_H_ */
=======

	/** attempt to allocate a font instance */
	virtual osd_font::ptr font_alloc() = 0;

	/** attempt to list available font families */
	virtual bool get_font_families(std::string const &font_path, std::vector<std::pair<std::string, std::string> > &result) = 0;
};


#endif // MAME_OSD_MODULES_FONT_FONTMODULE_H
>>>>>>> upstream/master
