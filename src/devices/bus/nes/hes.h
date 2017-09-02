// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_HES_H
#define __NES_HES_H
=======
#ifndef MAME_BUS_NES_HES_H
#define MAME_BUS_NES_HES_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_hes_device

class nes_hes_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_hes_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);

	virtual void pcb_reset();
=======
	nes_hes_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type NES_HES;

#endif
=======
DECLARE_DEVICE_TYPE(NES_HES, nes_hes_device)

#endif // MAME_BUS_NES_HES_H
>>>>>>> upstream/master
