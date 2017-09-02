// license:BSD-3-Clause
// copyright-holders:smf
/*
 * Konami 573 Multi Session Unit
 *
 */
<<<<<<< HEAD

#pragma once

#ifndef __K573MSU_H__
#define __K573MSU_H__

#include "emu.h"

extern const device_type KONAMI_573_MULTI_SESSION_UNIT;
=======
#ifndef MAME_MACHINE_K573MSU_H
#define MAME_MACHINE_K573MSU_H

#pragma once



DECLARE_DEVICE_TYPE(KONAMI_573_MULTI_SESSION_UNIT, k573msu_device)
>>>>>>> upstream/master

class k573msu_device : public device_t
{
public:
<<<<<<< HEAD
	k573msu_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual void device_start();

	virtual const rom_entry *device_rom_region() const;
};

#endif
=======
	k573msu_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;

	virtual const tiny_rom_entry *device_rom_region() const override;
};

#endif // MAME_MACHINE_K573MSU_H
>>>>>>> upstream/master
