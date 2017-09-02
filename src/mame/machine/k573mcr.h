// license:BSD-3-Clause
// copyright-holders:smf
/*
 * Konami 573 Memory Card Reader
 *
 */
<<<<<<< HEAD

#pragma once

#ifndef __K573MCR_H__
#define __K573MCR_H__

#include "emu.h"

extern const device_type KONAMI_573_MEMORY_CARD_READER;
=======
#ifndef MAME_MACHINE_K573_MCR_H
#define MAME_MACHINE_K573_MCR_H

#pragma once



DECLARE_DEVICE_TYPE(KONAMI_573_MEMORY_CARD_READER, k573mcr_device)
>>>>>>> upstream/master

class k573mcr_device : public device_t
{
public:
<<<<<<< HEAD
	k573mcr_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual void device_start();

	virtual const rom_entry *device_rom_region() const;
};

#endif
=======
	k573mcr_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;

	virtual const tiny_rom_entry *device_rom_region() const override;
};

#endif // MAME_MACHINE_K573_MCR_H
>>>>>>> upstream/master
