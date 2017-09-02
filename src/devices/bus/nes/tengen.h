// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_TENGEN_H
#define __NES_TENGEN_H
=======
#ifndef MAME_BUS_NES_TENGEN_H
#define MAME_BUS_NES_TENGEN_H
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_tengen008_device

class nes_tengen008_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_tengen008_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_tengen008_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_tengen032_device

class nes_tengen032_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_tengen032_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	nes_tengen032_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_WRITE8_MEMBER(tengen032_write);
	virtual DECLARE_WRITE8_MEMBER(write_h) { tengen032_write(space, offset, data, mem_mask); }
	virtual void chr_cb(int start, int bank, int source);

	virtual void hblank_irq(int scanline, int vblank, int blanked);
	virtual void pcb_reset();

protected:
=======
	nes_tengen032_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(tengen032_write);
	virtual DECLARE_WRITE8_MEMBER(write_h) override { tengen032_write(space, offset, data, mem_mask); }

	virtual void hblank_irq(int scanline, int vblank, int blanked) override;
	virtual void pcb_reset() override;

protected:
	nes_tengen032_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	virtual void chr_cb(int start, int bank, int source);

>>>>>>> upstream/master
	void set_prg();
	void set_chr();
	void irq_clock(int blanked);

<<<<<<< HEAD
	UINT16 m_irq_count, m_irq_count_latch;
	UINT8 m_irq_mode, m_irq_reset;
	int m_irq_enable;

	UINT8 m_latch;
	UINT8 m_mmc_prg_bank[3];
	UINT8 m_mmc_vrom_bank[8];
=======
	uint16_t m_irq_count, m_irq_count_latch;
	uint8_t m_irq_mode, m_irq_reset;
	int m_irq_enable;

	uint8_t m_latch;
	uint8_t m_mmc_prg_bank[3];
	uint8_t m_mmc_vrom_bank[8];
>>>>>>> upstream/master

	static const device_timer_id TIMER_IRQ = 0;
	emu_timer *irq_timer;
	attotime timer_freq;
};


// ======================> nes_tengen037_device

class nes_tengen037_device : public nes_tengen032_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_tengen037_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h);
	virtual void chr_cb(int start, int bank, int source);
=======
	nes_tengen037_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
	virtual void chr_cb(int start, int bank, int source) override;
>>>>>>> upstream/master

protected:
	void set_mirror();
};


<<<<<<< HEAD



// device type definition
extern const device_type NES_TENGEN_800008;
extern const device_type NES_TENGEN_800032;
extern const device_type NES_TENGEN_800037;

#endif
=======
// device type definition
DECLARE_DEVICE_TYPE(NES_TENGEN_800008, nes_tengen008_device)
DECLARE_DEVICE_TYPE(NES_TENGEN_800032, nes_tengen032_device)
DECLARE_DEVICE_TYPE(NES_TENGEN_800037, nes_tengen037_device)

#endif // MAME_BUS_NES_TENGEN_H
>>>>>>> upstream/master
