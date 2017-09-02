// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_MMC1_H
#define __NES_MMC1_H
=======
#ifndef MAME_BUS_NES_MMC1_H
#define MAME_BUS_NES_MMC1_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_sxrom_device

class nes_sxrom_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sxrom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	nes_sxrom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);
	virtual void update_regs(int reg);      // this is needed to simplify NES-EVENT pcb implementation, which handle differently some regs!

	virtual void pcb_reset();

protected:
	TIMER_CALLBACK_MEMBER(resync_callback);
	virtual void set_prg();
	virtual void set_chr();

	UINT8 m_reg[4];
=======
	nes_sxrom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	nes_sxrom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;

	TIMER_CALLBACK_MEMBER(resync_callback);

	virtual void update_regs(int reg);      // this is needed to simplify NES-EVENT pcb implementation, which handle differently some regs!
	virtual void set_prg();
	virtual void set_chr();

	uint8_t m_reg[4];
>>>>>>> upstream/master
	int m_reg_write_enable;
	int m_latch;
	int m_count;
};

class nes_sorom_device : public nes_sxrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sorom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();
=======
	nes_sorom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;
>>>>>>> upstream/master
};

class nes_sxrom_a_device : public nes_sxrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sxrom_a_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_m);
=======
	nes_sxrom_a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;
>>>>>>> upstream/master
};

class nes_sorom_a_device : public nes_sxrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sorom_a_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();
};




// device type definition
extern const device_type NES_SXROM;
extern const device_type NES_SOROM;
extern const device_type NES_SXROM_A;
extern const device_type NES_SOROM_A;


#endif
=======
	nes_sorom_a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;
};


// device type definition
DECLARE_DEVICE_TYPE(NES_SXROM,   nes_sxrom_device)
DECLARE_DEVICE_TYPE(NES_SOROM,   nes_sorom_device)
DECLARE_DEVICE_TYPE(NES_SXROM_A, nes_sxrom_a_device)
DECLARE_DEVICE_TYPE(NES_SOROM_A, nes_sorom_a_device)

#endif // MAME_BUS_NES_MMC1_H
>>>>>>> upstream/master
