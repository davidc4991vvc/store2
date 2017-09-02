// license:BSD-3-Clause
// copyright-holders:Sergey Svishchev
/**********************************************************************

    ISA bus cards for ex-USSR PC clones

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __XSU_CARDS_H__
#define __XSU_CARDS_H__

#include "emu.h"

#include "cga.h"
// storage
#include "mc1502_fdc.h"
#include "p1_fdc.h"
#include "p1_hdc.h"

// misc
#include "mc1502_rom.h"
#include "p1_rom.h"

// non-native
#include "com.h"
#include "xtide.h"
#include "lpt.h"
=======
#ifndef MAME_BUS_ISA_XSU_CARDS_H
#define MAME_BUS_ISA_XSU_CARDS_H

#pragma once

>>>>>>> upstream/master

// supported devices
SLOT_INTERFACE_EXTERN( p1_isa8_cards );
SLOT_INTERFACE_EXTERN( mc1502_isa8_cards );
SLOT_INTERFACE_EXTERN( ec184x_isa8_cards );
SLOT_INTERFACE_EXTERN( iskr103x_isa8_cards );

<<<<<<< HEAD
#endif // __XSU_CARDS_H__
=======
#endif // MAME_BUS_ISA_XSU_CARDS_H
>>>>>>> upstream/master
