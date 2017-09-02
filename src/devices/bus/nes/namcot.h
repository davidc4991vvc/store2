// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_NAMCOT_H
#define __NES_NAMCOT_H
=======
#ifndef MAME_BUS_NES_NAMCOT_H
#define MAME_BUS_NES_NAMCOT_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_namcot3433_device

class nes_namcot3433_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_namcot3433_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	nes_namcot3433_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(dxrom_write);
	virtual DECLARE_WRITE8_MEMBER(write_h) { dxrom_write(space, offset, data, mem_mask); }

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_namcot3433_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(dxrom_write);
	virtual DECLARE_WRITE8_MEMBER(write_h) override { dxrom_write(space, offset, data, mem_mask); }

	virtual void pcb_reset() override;

protected:
	nes_namcot3433_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch;
>>>>>>> upstream/master
};


// ======================> nes_namcot3446_device

class nes_namcot3446_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_namcot3446_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_namcot3446_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch;
>>>>>>> upstream/master
};


// ======================> nes_namcot3425_device

class nes_namcot3425_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_namcot3425_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
	UINT8 m_reg[4];
=======
	nes_namcot3425_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch;
	uint8_t m_reg[4];
>>>>>>> upstream/master
};


// ======================> nes_namcot340_device

class nes_namcot340_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_namcot340_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	nes_namcot340_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_READ8_MEMBER(n340_loread);
	virtual DECLARE_WRITE8_MEMBER(n340_lowrite);
	virtual DECLARE_WRITE8_MEMBER(n340_hiwrite);
	virtual DECLARE_READ8_MEMBER(read_l) { return n340_loread(space, offset, mem_mask); }
	virtual DECLARE_WRITE8_MEMBER(write_l) { n340_lowrite(space, offset, data, mem_mask); }
	virtual DECLARE_WRITE8_MEMBER(write_h) { n340_hiwrite(space, offset, data, mem_mask); }

	virtual void pcb_reset();

protected:
	UINT16 m_irq_count;
	int m_irq_enable;

	static const device_timer_id TIMER_IRQ = 0;
=======
	nes_namcot340_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(n340_loread);
	virtual DECLARE_WRITE8_MEMBER(n340_lowrite);
	virtual DECLARE_WRITE8_MEMBER(n340_hiwrite);
	virtual DECLARE_READ8_MEMBER(read_l) override { return n340_loread(space, offset, mem_mask); }
	virtual DECLARE_WRITE8_MEMBER(write_l) override { n340_lowrite(space, offset, data, mem_mask); }
	virtual DECLARE_WRITE8_MEMBER(write_h) override { n340_hiwrite(space, offset, data, mem_mask); }

	virtual void pcb_reset() override;

protected:
	static constexpr device_timer_id TIMER_IRQ = 0;

	nes_namcot340_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	uint16_t m_irq_count;
	int m_irq_enable;

>>>>>>> upstream/master
	emu_timer *irq_timer;

	// Namcot-163 chip contains 8K of internal ram, possibly battery backed up (not emulated yet)
	// was it also present in 175 & 340 chips?
<<<<<<< HEAD
	UINT8 m_n163_ram[0x2000];
=======
	uint8_t m_n163_ram[0x2000];
>>>>>>> upstream/master
};


// ======================> nes_namcot175_device

class nes_namcot175_device : public nes_namcot340_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_namcot175_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_wram_protect;
=======
	nes_namcot175_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

private:
	uint8_t m_wram_protect;
>>>>>>> upstream/master
};


// ======================> nes_namcot163_device

class nes_namcot163_device : public nes_namcot340_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_namcot163_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	// we have to overwrite these to allow CIRAM to be used for VRAM, even if it's not clear which game(s) use this
	virtual DECLARE_READ8_MEMBER(chr_r);
	virtual DECLARE_WRITE8_MEMBER(chr_w);

	virtual void pcb_reset();

private:
	void set_mirror(UINT8 page, UINT8 data);

	UINT8 m_wram_protect, m_latch, m_chr_bank;
=======
	nes_namcot163_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	// we have to overwrite these to allow CIRAM to be used for VRAM, even if it's not clear which game(s) use this
	virtual DECLARE_READ8_MEMBER(chr_r) override;
	virtual DECLARE_WRITE8_MEMBER(chr_w) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	void set_mirror(uint8_t page, uint8_t data);

	uint8_t m_wram_protect, m_latch, m_chr_bank;
>>>>>>> upstream/master
	// TODO: add emulation of the sound part of the chip
};


<<<<<<< HEAD

// device type definition
extern const device_type NES_NAMCOT3433;
extern const device_type NES_NAMCOT3446;
extern const device_type NES_NAMCOT3425;
extern const device_type NES_NAMCOT175;
extern const device_type NES_NAMCOT340;
extern const device_type NES_NAMCOT163;

#endif
=======
// device type definition
DECLARE_DEVICE_TYPE(NES_NAMCOT3433, nes_namcot3433_device)
DECLARE_DEVICE_TYPE(NES_NAMCOT3446, nes_namcot3446_device)
DECLARE_DEVICE_TYPE(NES_NAMCOT3425, nes_namcot3425_device)
DECLARE_DEVICE_TYPE(NES_NAMCOT340,  nes_namcot340_device)
DECLARE_DEVICE_TYPE(NES_NAMCOT175,  nes_namcot175_device)
DECLARE_DEVICE_TYPE(NES_NAMCOT163,  nes_namcot163_device)

#endif // MAME_BUS_NES_NAMCOT_H
>>>>>>> upstream/master
