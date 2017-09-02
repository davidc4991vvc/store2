// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_BENSHIENG_H
#define __NES_BENSHIENG_H
=======
#ifndef MAME_BUS_NES_BENSHIENG_H
#define MAME_BUS_NES_BENSHIENG_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_benshieng_device

class nes_benshieng_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_benshieng_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	void update_banks();
	UINT8 m_dipsetting;
	UINT8 m_mmc_prg_bank[4];
	UINT8 m_mmc_vrom_bank[4];
=======
	nes_benshieng_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	void update_banks();
	uint8_t m_dipsetting;
	uint8_t m_mmc_prg_bank[4];
	uint8_t m_mmc_vrom_bank[4];
>>>>>>> upstream/master
};


// device type definition
extern const device_type NES_BENSHIENG;

<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_NES_BENSHIENG_H
>>>>>>> upstream/master
