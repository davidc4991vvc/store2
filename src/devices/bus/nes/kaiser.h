// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_KAISER_H
#define __NES_KAISER_H
=======
#ifndef MAME_BUS_NES_KAISER_H
#define MAME_BUS_NES_KAISER_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_ks7058_device

class nes_ks7058_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ks7058_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_ks7058_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_ks7022_device

class nes_ks7022_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ks7022_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_ks7022_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch;
>>>>>>> upstream/master
};


// ======================> nes_ks7032_device

class nes_ks7032_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ks7032_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	nes_ks7032_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(ks7032_write);
	virtual DECLARE_WRITE8_MEMBER(write_h) { ks7032_write(space, offset, data, mem_mask); }

	virtual void pcb_reset();

protected:
	void prg_update();

	UINT8 m_latch;
	UINT8 m_reg[8];

	UINT16 m_irq_count;
=======
	nes_ks7032_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(ks7032_write);
	virtual DECLARE_WRITE8_MEMBER(write_h) override { ks7032_write(space, offset, data, mem_mask); }

	virtual void pcb_reset() override;

protected:
	nes_ks7032_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	void prg_update();

	uint8_t m_latch;
	uint8_t m_reg[8];

	uint16_t m_irq_count;
>>>>>>> upstream/master
	int m_irq_enable;

	static const device_timer_id TIMER_IRQ = 0;
	emu_timer *irq_timer;
};


// ======================> nes_ks202_device

class nes_ks202_device : public nes_ks7032_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ks202_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);
=======
	nes_ks202_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
>>>>>>> upstream/master
};


// ======================> nes_ks7017_device

class nes_ks7017_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ks7017_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_READ8_MEMBER(read_ex);
	virtual DECLARE_WRITE8_MEMBER(write_ex);
	virtual DECLARE_WRITE8_MEMBER(write_l);

	virtual void pcb_reset();

private:
	UINT8 m_latch;

	UINT16 m_irq_count;
	UINT8 m_irq_status;
=======
	nes_ks7017_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_ex) override;
	virtual DECLARE_WRITE8_MEMBER(write_ex) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

private:
	uint8_t m_latch;

	uint16_t m_irq_count;
	uint8_t m_irq_status;
>>>>>>> upstream/master
	int m_irq_enable;

	static const device_timer_id TIMER_IRQ = 0;
	emu_timer *irq_timer;
};


// ======================> nes_ks7012_device

class nes_ks7012_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ks7012_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_ks7012_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};

// ======================> nes_ks7013b_device

class nes_ks7013b_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ks7013b_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_ks7013b_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_ks7031_device

class nes_ks7031_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ks7031_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_reg[4];
};



// device type definition
extern const device_type NES_KS7058;
extern const device_type NES_KS7022;
extern const device_type NES_KS7032;
extern const device_type NES_KS202;
extern const device_type NES_KS7017;
extern const device_type NES_KS7012;
extern const device_type NES_KS7013B;
extern const device_type NES_KS7031;

#endif
=======
	nes_ks7031_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg[4];
};


// ======================> nes_ks7016_device

class nes_ks7016_device : public nes_nrom_device
{
public:
	// construction/destruction
	nes_ks7016_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg;
};

// ======================> nes_ks7037_device

class nes_ks7037_device : public nes_nrom_device
{
public:
	// construction/destruction
	nes_ks7037_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	void update_prg();
	uint8_t m_latch;
	uint8_t m_reg[8];
};


// device type definition
DECLARE_DEVICE_TYPE(NES_KS7058,  nes_ks7058_device)
DECLARE_DEVICE_TYPE(NES_KS7022,  nes_ks7022_device)
DECLARE_DEVICE_TYPE(NES_KS7032,  nes_ks7032_device)
DECLARE_DEVICE_TYPE(NES_KS202,   nes_ks202_device)
DECLARE_DEVICE_TYPE(NES_KS7017,  nes_ks7017_device)
DECLARE_DEVICE_TYPE(NES_KS7012,  nes_ks7012_device)
DECLARE_DEVICE_TYPE(NES_KS7013B, nes_ks7013b_device)
DECLARE_DEVICE_TYPE(NES_KS7031,  nes_ks7031_device)
DECLARE_DEVICE_TYPE(NES_KS7016,  nes_ks7016_device)
DECLARE_DEVICE_TYPE(NES_KS7037,  nes_ks7037_device)

#endif // MAME_BUS_NES_KAISER_H
>>>>>>> upstream/master
