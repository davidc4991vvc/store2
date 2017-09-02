// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    VTech Laser/VZ I/O Expansion Slot Devices

***************************************************************************/

<<<<<<< HEAD
#include "carts.h"

SLOT_INTERFACE_START( ioexp_slot_carts )
	SLOT_INTERFACE("joystick", JOYSTICK_INTERFACE)
	SLOT_INTERFACE("printer", PRINTER_INTERFACE)
=======
#include "emu.h"
#include "carts.h"

#include "joystick.h"
#include "printer.h"


SLOT_INTERFACE_START( vtech_ioexp_slot_carts )
	SLOT_INTERFACE("joystick", VTECH_JOYSTICK_INTERFACE)
	SLOT_INTERFACE("printer", VTECH_PRINTER_INTERFACE)
>>>>>>> upstream/master
SLOT_INTERFACE_END
