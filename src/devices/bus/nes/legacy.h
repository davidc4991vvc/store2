// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_LEGACY_H
#define __NES_LEGACY_H
=======
#ifndef MAME_BUS_NES_LEGACY_H
#define MAME_BUS_NES_LEGACY_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_ffe3_device

class nes_ffe3_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ffe3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_ffe3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_ffe4_device

class nes_ffe4_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ffe4_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	nes_ffe4_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_h);
	virtual DECLARE_READ8_MEMBER(chr_r);
	virtual DECLARE_WRITE8_MEMBER(chr_w);

	virtual void pcb_reset();

protected:
	UINT16 m_irq_count;
	int m_irq_enable;

	static const device_timer_id TIMER_IRQ = 0;
	emu_timer *irq_timer;

	UINT8 m_latch;
	int m_exram_enabled;
	int m_exram_bank;
	UINT8 m_exram[0x8000];
=======
	nes_ffe4_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
	virtual DECLARE_READ8_MEMBER(chr_r) override;
	virtual DECLARE_WRITE8_MEMBER(chr_w) override;

	virtual void pcb_reset() override;

protected:
	static constexpr device_timer_id TIMER_IRQ = 0;

	nes_ffe4_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	uint16_t m_irq_count;
	int m_irq_enable;

	emu_timer *irq_timer;

	uint8_t m_latch;
	int m_exram_enabled;
	int m_exram_bank;
	uint8_t m_exram[0x8000];
>>>>>>> upstream/master
};


// ======================> nes_ffe8_device

class nes_ffe8_device : public nes_ffe4_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ffe8_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_h) {}

	virtual void pcb_reset();
};



// device type definition
extern const device_type NES_FFE3;
extern const device_type NES_FFE4;
extern const device_type NES_FFE8;


#endif
=======
	nes_ffe8_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override {}

	virtual void pcb_reset() override;
};


// device type definition
DECLARE_DEVICE_TYPE(NES_FFE3, nes_ffe3_device)
DECLARE_DEVICE_TYPE(NES_FFE4, nes_ffe4_device)
DECLARE_DEVICE_TYPE(NES_FFE8, nes_ffe8_device)

#endif // MAME_BUS_NES_LEGACY_H
>>>>>>> upstream/master
