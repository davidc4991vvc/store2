// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    emu.h

    Core header file to be included by most files.

    NOTE: The contents of this file are designed to meet the needs of
    drivers and devices. In addition to this file, you will also need
    to include the headers of any CPUs or other devices that are required.

    If you find yourself needing something outside of this file in a
    driver or device, think carefully about what you are doing.

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __EMU_H__
#define __EMU_H__

=======
#ifndef __EMU_H__
#define __EMU_H__

#include <list>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>
#include <unordered_set>

>>>>>>> upstream/master
// core emulator headers -- must be first
#include "emucore.h"
#include "eminline.h"
#include "profiler.h"
<<<<<<< HEAD
#include "ui/lang.h"
#ifdef UI_COLOR_DISPLAY
#include "ui/pal.h"
#endif /* UI_COLOR_DISPLAY */

// commonly-referenecd utilities imported from lib/util
#include "palette.h"
#include "unicode.h"
=======

// http interface helpers
#include "http.h"

// commonly-referenced utilities imported from lib/util
#include "palette.h"
#include "unicode.h"
#include "strformat.h"
#include "vecstream.h"
>>>>>>> upstream/master

// emulator-specific utilities
#include "attotime.h"
#include "hash.h"
#include "fileio.h"
#include "delegate.h"
#include "devdelegate.h"

// memory and address spaces
<<<<<<< HEAD
#include "memory.h"
=======
#include "emumem.h"
>>>>>>> upstream/master
#include "addrmap.h"
#include "memarray.h"

// machine-wide utilities
#include "romload.h"
#include "save.h"

// define machine_config_constructor here due to circular dependency
// between devices and the machine config
<<<<<<< HEAD
class machine_config;
typedef device_t * (*machine_config_constructor)(machine_config &config, device_t *owner, device_t *device);
=======
typedef void (*machine_config_constructor)(machine_config &config, device_t *owner, device_t *device);
>>>>>>> upstream/master

// I/O
#include "input.h"
#include "ioport.h"
#include "output.h"

// devices and callbacks
#include "device.h"
#include "devfind.h"
#include "distate.h"
#include "dimemory.h"
<<<<<<< HEAD
#include "diexec.h"
#include "opresolv.h"
#include "digfx.h"
#include "diimage.h"
#include "dioutput.h"
=======
#include "dirom.h"
#include "diexec.h"
#include "opresolv.h"
#include "dipalette.h"
#include "digfx.h"
#include "diimage.h"
>>>>>>> upstream/master
#include "diserial.h"
#include "dislot.h"
#include "disound.h"
#include "divideo.h"
#include "dinvram.h"
<<<<<<< HEAD
#include "dirtc.h"
=======
>>>>>>> upstream/master
#include "didisasm.h"
#include "schedule.h"
#include "timer.h"
#include "dinetwork.h"
<<<<<<< HEAD
#include "dipty.h"
=======
>>>>>>> upstream/master

// machine and driver configuration
#include "mconfig.h"
#include "gamedrv.h"
#include "parameters.h"

// timers, CPU and scheduling
#include "devcpu.h"

// the running machine
<<<<<<< HEAD
#include "mame.h"
=======
#include "main.h"
>>>>>>> upstream/master
#include "machine.h"
#include "driver.h"

// video-related
#include "drawgfx.h"
<<<<<<< HEAD
#include "tilemap.h"
#include "emupal.h"
#include "screen.h"
=======
#include "emupal.h"
#include "tilemap.h"
>>>>>>> upstream/master
#include "video.h"

// sound-related
#include "sound.h"
<<<<<<< HEAD
#include "speaker.h"

// generic helpers
#include "devcb.h"
#include "dispatch.h"
#include "drivers/xtal.h"
#include "machine/generic.h"
#include "video/generic.h"

=======

// generic helpers
#include "devcb.h"
#include "drivers/xtal.h"
#include "bookkeeping.h"
#include "video/generic.h"

// member templates that don't like incomplete types
#include "device.ipp"

template <class DriverClass> void game_driver::driver_init_helper_impl<DriverClass>::invoke(driver_init_helper const &helper, running_machine &machine)
{ (machine.driver_data<DriverClass>()->*static_cast<driver_init_helper_impl<DriverClass> const &>(helper).m_method)(); }

>>>>>>> upstream/master
#endif  /* __EMU_H__ */
