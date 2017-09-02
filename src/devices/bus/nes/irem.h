// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_IREM_H
#define __NES_IREM_H
=======
#ifndef MAME_BUS_NES_IREM_H
#define MAME_BUS_NES_IREM_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_lrog017_device

class nes_lrog017_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_lrog017_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_lrog017_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_holydivr_device

class nes_holydivr_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_holydivr_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_holydivr_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_tam_s1_device

class nes_tam_s1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_tam_s1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_tam_s1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_g101_device

class nes_g101_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_g101_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

protected:
	UINT8     m_latch;
=======
	nes_g101_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

	uint8_t     m_latch;
>>>>>>> upstream/master
};


// ======================> nes_h3001_device

class nes_h3001_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_h3001_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

protected:
	UINT16     m_irq_count, m_irq_count_latch;
=======
	nes_h3001_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	uint16_t     m_irq_count, m_irq_count_latch;
>>>>>>> upstream/master
	int        m_irq_enable;

	static const device_timer_id TIMER_IRQ = 0;
	emu_timer *irq_timer;
};

<<<<<<< HEAD


// device type definition
extern const device_type NES_LROG017;
extern const device_type NES_HOLYDIVR;
extern const device_type NES_TAM_S1;
extern const device_type NES_G101;
extern const device_type NES_H3001;

#endif
=======
// device type definition
DECLARE_DEVICE_TYPE(NES_LROG017,  nes_lrog017_device)
DECLARE_DEVICE_TYPE(NES_HOLYDIVR, nes_holydivr_device)
DECLARE_DEVICE_TYPE(NES_TAM_S1,   nes_tam_s1_device)
DECLARE_DEVICE_TYPE(NES_G101,     nes_g101_device)
DECLARE_DEVICE_TYPE(NES_H3001,    nes_h3001_device)

#endif // MAME_BUS_NES_IREM_H
>>>>>>> upstream/master
