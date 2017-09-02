// license:BSD-3-Clause
// copyright-holders:smf
/*
 * MB89371
 *
 * Fujitsu
 * Dual Serial UART
 *
 */

<<<<<<< HEAD
#ifndef __MB89371_H__
#define __MB89371_H__

#include "emu.h"
=======
#ifndef MAME_MACHINE_MB89371_H
#define MAME_MACHINE_MB89371_H

#pragma once

>>>>>>> upstream/master

class mb89371_device : public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	mb89371_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	mb89371_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER( write );
	DECLARE_READ8_MEMBER( read );

protected:
<<<<<<< HEAD

	// device-level overrides
	virtual void device_start();
=======
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type MB89371;

#endif
=======
DECLARE_DEVICE_TYPE(MB89371, mb89371_device)

#endif // MAME_MACHINE_MB89371_H
>>>>>>> upstream/master
