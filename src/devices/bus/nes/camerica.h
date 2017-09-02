// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_CAMERICA_H
#define __NES_CAMERICA_H
=======
#ifndef MAME_BUS_NES_CAMERICA_H
#define MAME_BUS_NES_CAMERICA_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_bf9093_device

class nes_bf9093_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bf9093_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bf9093_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bf9096_device

class nes_bf9096_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bf9096_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);
	virtual DECLARE_WRITE8_MEMBER(write_m) { write_h(space, offset, data, mem_mask); }

	virtual void pcb_reset();

private:
	UINT8 m_bank_base, m_latch;
=======
	nes_bf9096_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override { write_h(space, offset, data, mem_mask); }

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_bank_base, m_latch;
>>>>>>> upstream/master
};


// ======================> nes_golden5_device

class nes_golden5_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_golden5_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_bank_base, m_latch;
};





// device type definition
extern const device_type NES_BF9093;
extern const device_type NES_BF9096;
extern const device_type NES_GOLDEN5;

#endif
=======
	nes_golden5_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_bank_base, m_latch;
};


// device type definition
DECLARE_DEVICE_TYPE(NES_BF9093,  nes_bf9093_device)
DECLARE_DEVICE_TYPE(NES_BF9096,  nes_bf9096_device)
DECLARE_DEVICE_TYPE(NES_GOLDEN5, nes_golden5_device)

#endif // MAME_BUS_NES_CAMERICA_H
>>>>>>> upstream/master
