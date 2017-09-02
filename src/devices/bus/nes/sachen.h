// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_SACHEN_H
#define __NES_SACHEN_H
=======
#ifndef MAME_BUS_NES_SACHEN_H
#define MAME_BUS_NES_SACHEN_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_sachen_sa009_device

class nes_sachen_sa009_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sachen_sa009_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);

	virtual void pcb_reset();
=======
	nes_sachen_sa009_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_sachen_sa0036_device

class nes_sachen_sa0036_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sachen_sa0036_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_sachen_sa0036_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_sachen_sa0037_device

class nes_sachen_sa0037_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sachen_sa0037_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_sachen_sa0037_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_sachen_sa72007_device

class nes_sachen_sa72007_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sachen_sa72007_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);

	virtual void pcb_reset();
=======
	nes_sachen_sa72007_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_sachen_sa72008_device

class nes_sachen_sa72008_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sachen_sa72008_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);

	virtual void pcb_reset();
=======
	nes_sachen_sa72008_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_sachen_tca01_device

class nes_sachen_tca01_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sachen_tca01_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_l);

	virtual void pcb_reset();
=======
	nes_sachen_tca01_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_l) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_sachen_tcu01_device

class nes_sachen_tcu01_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sachen_tcu01_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_m) { write_l(space, (offset + 0x100) & 0xfff, data, mem_mask); }
	virtual DECLARE_WRITE8_MEMBER(write_h) { write_l(space, (offset + 0x100) & 0xfff, data, mem_mask); }

	virtual void pcb_reset();
=======
	nes_sachen_tcu01_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override { write_l(space, (offset + 0x100) & 0xfff, data, mem_mask); }
	virtual DECLARE_WRITE8_MEMBER(write_h) override { write_l(space, (offset + 0x100) & 0xfff, data, mem_mask); }

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_sachen_tcu02_device

class nes_sachen_tcu02_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sachen_tcu02_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_WRITE8_MEMBER(write_l);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_sachen_tcu02_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch;
>>>>>>> upstream/master
};


// ======================> nes_sachen_74x374_device

class nes_sachen_74x374_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sachen_74x374_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	nes_sachen_74x374_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_WRITE8_MEMBER(write_l);

	virtual void pcb_reset();

protected:
	void set_mirror(UINT8 nt);
	UINT8 m_latch, m_mmc_vrom_bank;
=======
	nes_sachen_74x374_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;

	virtual void pcb_reset() override;

protected:
	nes_sachen_74x374_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;

	void set_mirror(uint8_t nt);
	uint8_t m_latch, m_mmc_vrom_bank;
>>>>>>> upstream/master
};


// ======================> nes_sachen_74x374_alt_device

class nes_sachen_74x374_alt_device : public nes_sachen_74x374_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sachen_74x374_alt_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual DECLARE_READ8_MEMBER(read_l) { return 0xff; }   // no read_l here
	virtual DECLARE_WRITE8_MEMBER(write_l);
=======
	nes_sachen_74x374_alt_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_READ8_MEMBER(read_l) override { return 0xff; }   // no read_l here
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
>>>>>>> upstream/master
};


// ======================> nes_sachen_8259a_device

class nes_sachen_8259a_device : public nes_sachen_74x374_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sachen_8259a_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	nes_sachen_8259a_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_m) { write_l(space, (offset + 0x100) & 0xfff, data, mem_mask); }

	virtual void pcb_reset();

protected:
	virtual void chr_update();
	UINT8 m_reg[8];
=======
	nes_sachen_8259a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override { write_l(space, (offset + 0x100) & 0xfff, data, mem_mask); }

	virtual void pcb_reset() override;

protected:
	nes_sachen_8259a_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;

	virtual void chr_update();
	uint8_t m_reg[8];
>>>>>>> upstream/master
};


// ======================> nes_sachen_8259b_device

class nes_sachen_8259b_device : public nes_sachen_8259a_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sachen_8259b_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual void chr_update();
=======
	nes_sachen_8259b_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void chr_update() override;
>>>>>>> upstream/master
};


// ======================> nes_sachen_8259c_device

class nes_sachen_8259c_device : public nes_sachen_8259a_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sachen_8259c_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual void chr_update();
=======
	nes_sachen_8259c_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void chr_update() override;
>>>>>>> upstream/master
};


// ======================> nes_sachen_8259d_device

class nes_sachen_8259d_device : public nes_sachen_8259a_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sachen_8259d_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual void pcb_reset();

protected:
	virtual void chr_update();
};





// device type definition
extern const device_type NES_SACHEN_SA009;
extern const device_type NES_SACHEN_SA0036;
extern const device_type NES_SACHEN_SA0037;
extern const device_type NES_SACHEN_SA72007;
extern const device_type NES_SACHEN_SA72008;
extern const device_type NES_SACHEN_TCA01;
extern const device_type NES_SACHEN_TCU01;
extern const device_type NES_SACHEN_TCU02;
extern const device_type NES_SACHEN_74X374;
extern const device_type NES_SACHEN_74X374_ALT;
extern const device_type NES_SACHEN_8259A;
extern const device_type NES_SACHEN_8259B;
extern const device_type NES_SACHEN_8259C;
extern const device_type NES_SACHEN_8259D;

#endif
=======
	nes_sachen_8259d_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void pcb_reset() override;

protected:
	virtual void chr_update() override;
};


// device type definition
DECLARE_DEVICE_TYPE(NES_SACHEN_SA009,      nes_sachen_sa009_device)
DECLARE_DEVICE_TYPE(NES_SACHEN_SA0036,     nes_sachen_sa0036_device)
DECLARE_DEVICE_TYPE(NES_SACHEN_SA0037,     nes_sachen_sa0037_device)
DECLARE_DEVICE_TYPE(NES_SACHEN_SA72007,    nes_sachen_sa72007_device)
DECLARE_DEVICE_TYPE(NES_SACHEN_SA72008,    nes_sachen_sa72008_device)
DECLARE_DEVICE_TYPE(NES_SACHEN_TCA01,      nes_sachen_tca01_device)
DECLARE_DEVICE_TYPE(NES_SACHEN_TCU01,      nes_sachen_tcu01_device)
DECLARE_DEVICE_TYPE(NES_SACHEN_TCU02,      nes_sachen_tcu02_device)
DECLARE_DEVICE_TYPE(NES_SACHEN_74X374,     nes_sachen_74x374_device)
DECLARE_DEVICE_TYPE(NES_SACHEN_74X374_ALT, nes_sachen_74x374_alt_device)
DECLARE_DEVICE_TYPE(NES_SACHEN_8259A,      nes_sachen_8259a_device)
DECLARE_DEVICE_TYPE(NES_SACHEN_8259B,      nes_sachen_8259b_device)
DECLARE_DEVICE_TYPE(NES_SACHEN_8259C,      nes_sachen_8259c_device)
DECLARE_DEVICE_TYPE(NES_SACHEN_8259D,      nes_sachen_8259d_device)

#endif // MAME_BUS_NES_SACHEN_H
>>>>>>> upstream/master
