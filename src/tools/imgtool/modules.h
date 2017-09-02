// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/****************************************************************************

    modules.h

    Code that creates the "canonical" Imgtool library

****************************************************************************/

#ifndef MODULES_H
#define MODULES_H

#include "library.h"

<<<<<<< HEAD
imgtoolerr_t imgtool_create_cannonical_library(int omit_untested, imgtool_library **library);
=======
imgtoolerr_t imgtool_create_cannonical_library(bool omit_untested, std::unique_ptr<imgtool::library> &library);
>>>>>>> upstream/master

#endif /* MODULES_H */
