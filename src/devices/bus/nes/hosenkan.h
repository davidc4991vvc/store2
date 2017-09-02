// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_HOSENKAN_H
#define __NES_HOSENKAN_H
=======
#ifndef MAME_BUS_NES_HOSENKAN_H
#define MAME_BUS_NES_HOSENKAN_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_hosenkan_device

class nes_hosenkan_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_hosenkan_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);


	virtual void hblank_irq(int scanline, int vblank, int blanked);
	virtual void pcb_reset();

private:
	UINT16 m_irq_count, m_irq_count_latch;
	UINT8 m_irq_clear;
	int m_irq_enable;

	UINT8 m_latch;
};



// device type definition
extern const device_type NES_HOSENKAN;


#endif
=======
	nes_hosenkan_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void hblank_irq(int scanline, int vblank, int blanked) override;
	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint16_t m_irq_count, m_irq_count_latch;
	uint8_t m_irq_clear;
	int m_irq_enable;

	uint8_t m_latch;
};

// device type definition
DECLARE_DEVICE_TYPE(NES_HOSENKAN, nes_hosenkan_device)

#endif // MAME_BUS_NES_HOSENKAN_H
>>>>>>> upstream/master
