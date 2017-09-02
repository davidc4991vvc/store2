// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_NANJING_H
#define __NES_NANJING_H
=======
#ifndef MAME_BUS_NES_NANJING_H
#define MAME_BUS_NES_NANJING_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_nanjing_device

class nes_nanjing_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_nanjing_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_WRITE8_MEMBER(write_l);

	virtual void hblank_irq(int scanline, int vblank, int blanked);
	virtual void pcb_reset();

private:
	UINT8 m_count;
	UINT8 m_reg[2];
	UINT8 m_latch1, m_latch2;
};





// device type definition
extern const device_type NES_NANJING;

#endif
=======
	nes_nanjing_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;

	virtual void hblank_irq(int scanline, int vblank, int blanked) override;
	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_count;
	uint8_t m_reg[2];
	uint8_t m_latch1, m_latch2;
};


// device type definition
DECLARE_DEVICE_TYPE(NES_NANJING, nes_nanjing_device)

#endif // MAME_BUS_NES_NANJING_H
>>>>>>> upstream/master
