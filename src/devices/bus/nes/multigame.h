// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_MULTIGAME_H
#define __NES_MULTIGAME_H
=======
#ifndef MAME_BUS_NES_MULTIGAME_H
#define MAME_BUS_NES_MULTIGAME_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_action52_device

class nes_action52_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_action52_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_action52_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_caltron_device

class nes_caltron_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_caltron_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_caltron_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch;
>>>>>>> upstream/master
};


// ======================> nes_rumblestat_device

class nes_rumblestat_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_rumblestat_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_prg, m_chr;
=======
	nes_rumblestat_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_prg, m_chr;
>>>>>>> upstream/master
};


// ======================> nes_svision16_device

class nes_svision16_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_svision16_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	void update_prg();
	UINT8 m_latch1, m_latch2;
=======
	nes_svision16_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	void update_prg();
	uint8_t m_latch1, m_latch2;
>>>>>>> upstream/master
};


// ======================> nes_n625092_device

class nes_n625092_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_n625092_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	void set_prg(UINT8 reg1, UINT8 reg2);
	UINT8 m_latch1, m_latch2;
=======
	nes_n625092_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	void set_prg(uint8_t reg1, uint8_t reg2);
	uint8_t m_latch1, m_latch2;
>>>>>>> upstream/master
};


// ======================> nes_a65as_device

class nes_a65as_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_a65as_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_a65as_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_t262_device

class nes_t262_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_t262_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch1, m_latch2;
=======
	nes_t262_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch1, m_latch2;
>>>>>>> upstream/master
};


// ======================> nes_novel1_device

class nes_novel1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_novel1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_novel1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_novel2_device

class nes_novel2_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_novel2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_novel2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_studyngame_device

class nes_studyngame_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_studyngame_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_studyngame_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_sgun20in1_device

class nes_sgun20in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sgun20in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_sgun20in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_vt5201_device

class nes_vt5201_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_vt5201_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch, m_dipsetting;
=======
	nes_vt5201_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch, m_dipsetting;
>>>>>>> upstream/master
};


// ======================> nes_810544c_device

class nes_810544c_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_810544c_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_810544c_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_ntd03_device

class nes_ntd03_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ntd03_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_ntd03_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_gb63_device

class nes_bmc_gb63_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_gb63_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_h);
	virtual DECLARE_WRITE8_MEMBER(chr_w);

	virtual void pcb_reset();

private:
	void update_banks();
	UINT8 m_latch, m_dipsetting;
	UINT8 m_reg[2];
=======
	nes_bmc_gb63_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
	virtual DECLARE_WRITE8_MEMBER(chr_w) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	void update_banks();
	uint8_t m_latch, m_dipsetting;
	uint8_t m_reg[2];
>>>>>>> upstream/master
	int m_vram_disable;
};

// ======================> nes_bmc_gka_device

class nes_bmc_gka_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_gka_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch1, m_latch2;
=======
	nes_bmc_gka_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch1, m_latch2;
>>>>>>> upstream/master
};


// ======================> nes_bmc_gkb_device

class nes_bmc_gkb_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_gkb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_gkb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_ws_device

class nes_bmc_ws_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_ws_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_bmc_ws_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch;
>>>>>>> upstream/master
};


// ======================> nes_bmc_11160_device

class nes_bmc_11160_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_11160_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_11160_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_g146_device

class nes_bmc_g146_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_g146_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_g146_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_8157_device

class nes_bmc_8157_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_8157_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_8157_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_hik300_device

class nes_bmc_hik300_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_hik300_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_hik300_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_s700_device

class nes_bmc_s700_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_s700_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_s700_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_ball11_device

class nes_bmc_ball11_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_ball11_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	void set_banks();
	UINT8 m_reg[2];
=======
	nes_bmc_ball11_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	void set_banks();
	uint8_t m_reg[2];
>>>>>>> upstream/master
};


// ======================> nes_bmc_22games_device

class nes_bmc_22games_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_22games_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_22games_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_64y2k_device

class nes_bmc_64y2k_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_64y2k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	void set_prg();
	UINT8 m_reg[4];
=======
	nes_bmc_64y2k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	void set_prg();
	uint8_t m_reg[4];
>>>>>>> upstream/master
};


// ======================> nes_bmc_12in1_device

class nes_bmc_12in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_12in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	void update_banks();
	UINT8 m_reg[3];
=======
	nes_bmc_12in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	void update_banks();
	uint8_t m_reg[3];
>>>>>>> upstream/master
};


// ======================> nes_bmc_20in1_device

class nes_bmc_20in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_20in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_20in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_21in1_device

class nes_bmc_21in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_21in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_21in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_31in1_device

class nes_bmc_31in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_31in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_31in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_35in1_device

class nes_bmc_35in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_35in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_35in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_36in1_device

class nes_bmc_36in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_36in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_36in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_64in1_device

class nes_bmc_64in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_64in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_64in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_70in1_device

class nes_bmc_70in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_70in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_mode;
	UINT8 m_reg[2];
=======
	nes_bmc_70in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_mode;
	uint8_t m_reg[2];
>>>>>>> upstream/master
};


// ======================> nes_bmc_72in1_device

class nes_bmc_72in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_72in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_72in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_76in1_device

class nes_bmc_76in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_76in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch1, m_latch2;
=======
	nes_bmc_76in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch1, m_latch2;
>>>>>>> upstream/master
};


// ======================> nes_bmc_110in1_device

class nes_bmc_110in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_110in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_110in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_150in1_device

class nes_bmc_150in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_150in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_150in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_190in1_device

class nes_bmc_190in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_190in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_190in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_800in1_device

class nes_bmc_800in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_800in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_mode;
	UINT8 m_reg[2];
=======
	nes_bmc_800in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_mode;
	uint8_t m_reg[2];
>>>>>>> upstream/master
};


// ======================> nes_bmc_1200in1_device

class nes_bmc_1200in1_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_1200in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);
	virtual DECLARE_WRITE8_MEMBER(chr_w);

	virtual void pcb_reset();

private:
	UINT8 m_vram_protect;
=======
	nes_bmc_1200in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;
	virtual DECLARE_WRITE8_MEMBER(chr_w) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_vram_protect;
>>>>>>> upstream/master
};


// ======================> nes_bmc_gold150_device

class nes_bmc_gold150_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_gold150_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_bmc_gold150_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

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


// ======================> nes_bmc_gold260_device

class nes_bmc_gold260_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_gold260_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_gold260_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_ch001_device

class nes_bmc_ch001_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_ch001_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_bmc_ch001_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

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


// ======================> nes_bmc_super22_device

class nes_bmc_super22_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_super22_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_super22_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_4in1reset_device

class nes_bmc_4in1reset_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_4in1reset_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void pcb_reset();
=======
	nes_bmc_4in1reset_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master

private:
	int m_latch;
};

// ======================> nes_bmc_42in1reset_device

class nes_bmc_42in1reset_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_42in1reset_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	int m_latch;
	UINT8 m_reg[2];
};



// device type definition
extern const device_type NES_ACTION52;
extern const device_type NES_CALTRON6IN1;
extern const device_type NES_RUMBLESTATION;
extern const device_type NES_SVISION16;
extern const device_type NES_N625092;
extern const device_type NES_A65AS;
extern const device_type NES_T262;
extern const device_type NES_NOVEL1;
extern const device_type NES_NOVEL2;
extern const device_type NES_STUDYNGAME;
extern const device_type NES_SUPERGUN20IN1;
extern const device_type NES_VT5201;
extern const device_type NES_810544C;
extern const device_type NES_NTD03;
extern const device_type NES_BMC_GB63;
extern const device_type NES_BMC_GKA;
extern const device_type NES_BMC_GKB;
extern const device_type NES_BMC_WS;
extern const device_type NES_BMC_11160;
extern const device_type NES_BMC_G146;
extern const device_type NES_BMC_8157;
extern const device_type NES_BMC_HIK300;
extern const device_type NES_BMC_S700;
extern const device_type NES_BMC_BALL11;
extern const device_type NES_BMC_22GAMES;
extern const device_type NES_BMC_64Y2K;
extern const device_type NES_BMC_12IN1;
extern const device_type NES_BMC_20IN1;
extern const device_type NES_BMC_21IN1;
extern const device_type NES_BMC_31IN1;
extern const device_type NES_BMC_35IN1;
extern const device_type NES_BMC_36IN1;
extern const device_type NES_BMC_64IN1;
extern const device_type NES_BMC_70IN1;
extern const device_type NES_BMC_72IN1;
extern const device_type NES_BMC_76IN1;
extern const device_type NES_BMC_110IN1;
extern const device_type NES_BMC_150IN1;
extern const device_type NES_BMC_190IN1;
extern const device_type NES_BMC_800IN1;
extern const device_type NES_BMC_1200IN1;
extern const device_type NES_BMC_GOLD150;
extern const device_type NES_BMC_GOLD260;
extern const device_type NES_BMC_CH001;
extern const device_type NES_BMC_SUPER22;
extern const device_type NES_BMC_4IN1RESET;
extern const device_type NES_BMC_42IN1RESET;


#endif
=======
	nes_bmc_42in1reset_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	int m_latch;
	uint8_t m_reg[2];
};


// device type definition
DECLARE_DEVICE_TYPE(NES_ACTION52,       nes_action52_device)
DECLARE_DEVICE_TYPE(NES_CALTRON6IN1,    nes_caltron_device)
DECLARE_DEVICE_TYPE(NES_RUMBLESTATION,  nes_rumblestat_device)
DECLARE_DEVICE_TYPE(NES_SVISION16,      nes_svision16_device)
DECLARE_DEVICE_TYPE(NES_N625092,        nes_n625092_device)
DECLARE_DEVICE_TYPE(NES_A65AS,          nes_a65as_device)
DECLARE_DEVICE_TYPE(NES_T262,           nes_t262_device)
DECLARE_DEVICE_TYPE(NES_NOVEL1,         nes_novel1_device)
DECLARE_DEVICE_TYPE(NES_NOVEL2,         nes_novel2_device)
DECLARE_DEVICE_TYPE(NES_STUDYNGAME,     nes_studyngame_device)
DECLARE_DEVICE_TYPE(NES_SUPERGUN20IN1,  nes_sgun20in1_device)
DECLARE_DEVICE_TYPE(NES_VT5201,         nes_vt5201_device)
DECLARE_DEVICE_TYPE(NES_810544C,        nes_810544c_device)
DECLARE_DEVICE_TYPE(NES_NTD03,          nes_ntd03_device)
DECLARE_DEVICE_TYPE(NES_BMC_GB63,       nes_bmc_gb63_device)
DECLARE_DEVICE_TYPE(NES_BMC_GKA,        nes_bmc_gka_device)
DECLARE_DEVICE_TYPE(NES_BMC_GKB,        nes_bmc_gkb_device)
DECLARE_DEVICE_TYPE(NES_BMC_WS,         nes_bmc_ws_device)
DECLARE_DEVICE_TYPE(NES_BMC_11160,      nes_bmc_11160_device)
DECLARE_DEVICE_TYPE(NES_BMC_G146,       nes_bmc_g146_device)
DECLARE_DEVICE_TYPE(NES_BMC_8157,       nes_bmc_8157_device)
DECLARE_DEVICE_TYPE(NES_BMC_HIK300,     nes_bmc_hik300_device)
DECLARE_DEVICE_TYPE(NES_BMC_S700,       nes_bmc_s700_device)
DECLARE_DEVICE_TYPE(NES_BMC_BALL11,     nes_bmc_ball11_device)
DECLARE_DEVICE_TYPE(NES_BMC_22GAMES,    nes_bmc_22games_device)
DECLARE_DEVICE_TYPE(NES_BMC_64Y2K,      nes_bmc_64y2k_device)
DECLARE_DEVICE_TYPE(NES_BMC_12IN1,      nes_bmc_12in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_20IN1,      nes_bmc_20in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_21IN1,      nes_bmc_21in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_31IN1,      nes_bmc_31in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_35IN1,      nes_bmc_35in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_36IN1,      nes_bmc_36in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_64IN1,      nes_bmc_64in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_70IN1,      nes_bmc_70in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_72IN1,      nes_bmc_72in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_76IN1,      nes_bmc_76in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_110IN1,     nes_bmc_110in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_150IN1,     nes_bmc_150in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_190IN1,     nes_bmc_190in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_800IN1,     nes_bmc_800in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_1200IN1,    nes_bmc_1200in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_GOLD150,    nes_bmc_gold150_device)
DECLARE_DEVICE_TYPE(NES_BMC_GOLD260,    nes_bmc_gold260_device)
DECLARE_DEVICE_TYPE(NES_BMC_CH001,      nes_bmc_ch001_device)
DECLARE_DEVICE_TYPE(NES_BMC_SUPER22,    nes_bmc_super22_device)
DECLARE_DEVICE_TYPE(NES_BMC_4IN1RESET,  nes_bmc_4in1reset_device)
DECLARE_DEVICE_TYPE(NES_BMC_42IN1RESET, nes_bmc_42in1reset_device)

#endif // MAME_BUS_NES_MULTIGAME_H
>>>>>>> upstream/master
