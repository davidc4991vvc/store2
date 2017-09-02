// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

 Generic ROM / RAM socket slots

 **********************************************************************/


<<<<<<< HEAD
#include "carts.h"
=======
#include "emu.h"
#include "carts.h"
#include "rom.h"
#include "ram.h"

>>>>>>> upstream/master

SLOT_INTERFACE_START(generic_plain_slot)
	SLOT_INTERFACE_INTERNAL("rom", GENERIC_ROM_PLAIN)
SLOT_INTERFACE_END

SLOT_INTERFACE_START(generic_linear_slot)
	SLOT_INTERFACE_INTERNAL("rom", GENERIC_ROM_LINEAR)
SLOT_INTERFACE_END

SLOT_INTERFACE_START(generic_romram_plain_slot)
	SLOT_INTERFACE_INTERNAL("rom", GENERIC_ROMRAM_PLAIN)
SLOT_INTERFACE_END
