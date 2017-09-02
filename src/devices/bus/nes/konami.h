// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_KONAMI_H
#define __NES_KONAMI_H

#include "nxrom.h"
#include "sound/vrc6.h"
#include "sound/2413intf.h"
=======
#ifndef MAME_BUS_NES_KONAMI_H
#define MAME_BUS_NES_KONAMI_H

#pragma once

#include "nxrom.h"
#include "sound/vrc6.h"
#include "sound/ym2413.h"
>>>>>>> upstream/master


// ======================> nes_konami_vrc1_device

class nes_konami_vrc1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_konami_vrc1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_mmc_vrom_bank[2];
=======
	nes_konami_vrc1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_mmc_vrom_bank[2];
>>>>>>> upstream/master
};


// ======================> nes_konami_vrc2_device

class nes_konami_vrc2_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_konami_vrc2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_mmc_vrom_bank[8];
	UINT8 m_latch;
=======
	nes_konami_vrc2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_mmc_vrom_bank[8];
	uint8_t m_latch;
>>>>>>> upstream/master
};


// ======================> nes_konami_vrc3_device

class nes_konami_vrc3_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_konami_vrc3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT16 m_irq_count, m_irq_count_latch;
	int m_irq_enable, m_irq_enable_latch;
	int m_irq_mode;

	static const device_timer_id TIMER_IRQ = 0;
=======
	nes_konami_vrc3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

private:
	static constexpr device_timer_id TIMER_IRQ = 0;

	uint16_t m_irq_count, m_irq_count_latch;
	int m_irq_enable, m_irq_enable_latch;
	int m_irq_mode;

>>>>>>> upstream/master
	emu_timer *irq_timer;
};


// ======================> nes_konami_vrc4_device

class nes_konami_vrc4_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_konami_vrc4_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	nes_konami_vrc4_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

protected:
	void set_prg();
	UINT8 m_mmc_vrom_bank[8];
	UINT8 m_latch, m_mmc_prg_bank;

	void irq_tick();
	UINT16 m_irq_count, m_irq_count_latch;
=======
	nes_konami_vrc4_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	static constexpr device_timer_id TIMER_IRQ = 0;

	nes_konami_vrc4_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	void set_prg();
	uint8_t m_mmc_vrom_bank[8];
	uint8_t m_latch, m_mmc_prg_bank;

	void irq_tick();
	uint16_t m_irq_count, m_irq_count_latch;
>>>>>>> upstream/master
	int m_irq_enable, m_irq_enable_latch;
	int m_irq_mode;
	int m_irq_prescale;

<<<<<<< HEAD
	static const device_timer_id TIMER_IRQ = 0;
=======
>>>>>>> upstream/master
	emu_timer *irq_timer;
};


// ======================> nes_konami_vrc6_device

class nes_konami_vrc6_device : public nes_konami_vrc4_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_konami_vrc6_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual DECLARE_WRITE8_MEMBER(write_h);
=======
	nes_konami_vrc6_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

protected:
	// device-level overrides
	virtual void device_start() override;

	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

	required_device<vrc6snd_device> m_vrc6snd;
};


// ======================> nes_konami_vrc7_device

class nes_konami_vrc7_device : public nes_konami_vrc4_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_konami_vrc7_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_konami_vrc7_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

private:
	required_device<ym2413_device> m_ym2413;
};


<<<<<<< HEAD

// device type definition
extern const device_type NES_VRC1;
extern const device_type NES_VRC2;
extern const device_type NES_VRC3;
extern const device_type NES_VRC4;
extern const device_type NES_VRC6;
extern const device_type NES_VRC7;

#endif
=======
// device type definition
DECLARE_DEVICE_TYPE(NES_VRC1, nes_konami_vrc1_device)
DECLARE_DEVICE_TYPE(NES_VRC2, nes_konami_vrc2_device)
DECLARE_DEVICE_TYPE(NES_VRC3, nes_konami_vrc3_device)
DECLARE_DEVICE_TYPE(NES_VRC4, nes_konami_vrc4_device)
DECLARE_DEVICE_TYPE(NES_VRC6, nes_konami_vrc6_device)
DECLARE_DEVICE_TYPE(NES_VRC7, nes_konami_vrc7_device)

#endif // MAME_BUS_NES_KONAMI_H
>>>>>>> upstream/master
