// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_CNE_H
#define __NES_CNE_H
=======
#ifndef MAME_BUS_NES_CNE_H
#define MAME_BUS_NES_CNE_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_cne_decathl_device

class nes_cne_decathl_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_cne_decathl_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_cne_decathl_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_cne_fsb_device

class nes_cne_fsb_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_cne_fsb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();
=======
	nes_cne_fsb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_cne_shlz_device

class nes_cne_shlz_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_cne_shlz_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);

	virtual void pcb_reset();
};





// device type definition
extern const device_type NES_CNE_DECATHL;
extern const device_type NES_CNE_FSB;
extern const device_type NES_CNE_SHLZ;

#endif
=======
	nes_cne_shlz_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
};


// device type definition
DECLARE_DEVICE_TYPE(NES_CNE_DECATHL, nes_cne_decathl_device)
DECLARE_DEVICE_TYPE(NES_CNE_FSB,     nes_cne_fsb_device)
DECLARE_DEVICE_TYPE(NES_CNE_SHLZ,    nes_cne_shlz_device)

#endif // MAME_BUS_NES_CNE_H
>>>>>>> upstream/master
