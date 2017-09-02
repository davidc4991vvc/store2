// license:BSD-3-Clause
// copyright-holders:David Haywood
/***************************************************************************

    Kawasaki LSI
    KL5C80A12 CPU (KL5C80A12CFP on hng64.c)

    Binary compatible with Z80, significantly faster opcode timings, operating at up to 10Mhz
<<<<<<< HEAD
    Timers / Counters, Parrallel / Serial ports/ MMU, Interrupt Controller
=======
    Timers / Counters, Parallel / Serial ports/ MMU, Interrupt Controller
>>>>>>> upstream/master

    (is this different enough to need it's own core?)
    (todo: everything, some code currently lives in machine/hng64_net.c but not much)

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __KL5C80A12__
#define __KL5C80A12__

#include "emu.h"
=======
#ifndef MAME_CPU_Z80_KL5C80A12_H
#define MAME_CPU_Z80_KL5C80A12_H

#pragma once

>>>>>>> upstream/master
#include "z80.h"
#include "machine/z80ctc.h"


/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/


/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

class kl5c80a12_device : public z80_device
{
public:
<<<<<<< HEAD
	kl5c80a12_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32);
=======
	kl5c80a12_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t);
>>>>>>> upstream/master

	// static configuration helpers

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_start();
	virtual void device_reset();


private:
	// devices/pointers

	// internal state

	// callbacks
=======
	virtual void device_add_mconfig(machine_config &config) override;
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type KL5C80A12;


#endif /// __KL5C80A12__
=======
DECLARE_DEVICE_TYPE(KL5C80A12, kl5c80a12_device)

#endif // MAME_CPU_Z80_KL5C80A12_H
>>>>>>> upstream/master
