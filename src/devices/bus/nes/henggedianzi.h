// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_HENGGEDIANZI_H
#define __NES_HENGGEDIANZI_H
=======
#ifndef MAME_BUS_NES_HENGGEDIANZI_H
#define MAME_BUS_NES_HENGGEDIANZI_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_hengg_srich_device

class nes_hengg_srich_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_hengg_srich_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_hengg_srich_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_hengg_xhzs_device

class nes_hengg_xhzs_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_hengg_xhzs_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_hengg_xhzs_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_hengg_shjy3_device

class nes_hengg_shjy3_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_hengg_shjy3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void hblank_irq(int scanline, int vblank, int blanked);
	virtual void pcb_reset();
=======
	nes_hengg_shjy3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void hblank_irq(int scanline, int vblank, int blanked) override;
	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master

private:
	void update_banks();

<<<<<<< HEAD
	UINT16 m_irq_count, m_irq_count_latch;
	int m_irq_enable;

	int m_chr_mode;
	UINT8 m_mmc_prg_bank[2];
	UINT8 m_mmc_vrom_bank[8];
	UINT8 m_mmc_extra_bank[8];
};





// device type definition
extern const device_type NES_HENGG_SRICH;
extern const device_type NES_HENGG_XHZS;
extern const device_type NES_HENGG_SHJY3;

#endif
=======
	uint16_t m_irq_count, m_irq_count_latch;
	int m_irq_enable;

	int m_chr_mode;
	uint8_t m_mmc_prg_bank[2];
	uint8_t m_mmc_vrom_bank[8];
	uint8_t m_mmc_extra_bank[8];
};

// device type definition
DECLARE_DEVICE_TYPE(NES_HENGG_SRICH, nes_hengg_srich_device)
DECLARE_DEVICE_TYPE(NES_HENGG_XHZS,  nes_hengg_xhzs_device)
DECLARE_DEVICE_TYPE(NES_HENGG_SHJY3, nes_hengg_shjy3_device)

#endif // MAME_BUS_NES_HENGGEDIANZI_H
>>>>>>> upstream/master
