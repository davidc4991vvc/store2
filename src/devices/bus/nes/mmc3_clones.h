// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_MMC3_CLONES_H
#define __NES_MMC3_CLONES_H
=======
#ifndef MAME_BUS_NES_MMC3_CLONES_H
#define MAME_BUS_NES_MMC3_CLONES_H

#pragma once
>>>>>>> upstream/master

#include "mmc3.h"


// ======================> nes_nitra_device

class nes_nitra_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_nitra_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h);
=======
	nes_nitra_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
>>>>>>> upstream/master
};


// ======================> nes_ks7057_device

class nes_ks7057_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ks7057_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h);
=======
	nes_ks7057_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
>>>>>>> upstream/master
};


// ======================> nes_sbros11_device

class nes_sbros11_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sbros11_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h);
=======
	nes_sbros11_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
>>>>>>> upstream/master
};


// ======================> nes_malisb_device

class nes_malisb_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_malisb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h);
	virtual void prg_cb(int start, int bank);
	virtual void chr_cb(int start, int bank, int source);
=======
	nes_malisb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
	virtual void prg_cb(int start, int bank) override;
	virtual void chr_cb(int start, int bank, int source) override;
>>>>>>> upstream/master
};


// ======================> nes_family4646_device

class nes_family4646_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_family4646_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();
=======
	nes_family4646_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;
>>>>>>> upstream/master
};


// ======================> nes_pikay2k_device

class nes_pikay2k_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_pikay2k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_reg[2];
=======
	nes_pikay2k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg[2];
>>>>>>> upstream/master
};


// ======================> nes_8237_device

class nes_8237_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_8237_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_h);
	virtual void prg_cb(int start, int bank);
	virtual void chr_cb(int start, int bank, int source);

	virtual void pcb_reset();

private:
	UINT8 m_reg[3];
=======
	nes_8237_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
	virtual void prg_cb(int start, int bank) override;
	virtual void chr_cb(int start, int bank, int source) override;

	virtual void pcb_reset() override;

private:
	uint8_t m_reg[3];
>>>>>>> upstream/master
	int m_cd_enable;
};


// ======================> nes_sglionk_device

class nes_sglionk_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sglionk_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_reg;
=======
	nes_sglionk_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg;
>>>>>>> upstream/master
	int m_reg_enabled;
};


// ======================> nes_sgboog_device

class nes_sgboog_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sgboog_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);
	virtual void prg_cb(int start, int bank);
	virtual void chr_cb(int start, int bank, int source);

	virtual void pcb_reset();

private:
	virtual void set_prg(int prg_base, int prg_mask);
	UINT8 m_reg[3];
	UINT8 m_mode;
=======
	nes_sgboog_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
	virtual void prg_cb(int start, int bank) override;
	virtual void chr_cb(int start, int bank, int source) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	virtual void set_prg(int prg_base, int prg_mask) override;
	uint8_t m_reg[3];
	uint8_t m_mode;
>>>>>>> upstream/master
};


// ======================> nes_kasing_device

class nes_kasing_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_kasing_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual void prg_cb(int start, int bank);

	virtual void pcb_reset();

private:
	UINT8 m_reg;
=======
	nes_kasing_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual void prg_cb(int start, int bank) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg;
>>>>>>> upstream/master
};


// ======================> nes_kay_device

class nes_kay_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_kay_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_h);
	virtual void prg_cb(int start, int bank);
	virtual void chr_cb(int start, int bank, int source);

	virtual void pcb_reset();

private:
	void update_regs();
	UINT8 m_reg[8];
	UINT8 m_low_reg;
=======
	nes_kay_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
	virtual void prg_cb(int start, int bank) override;
	virtual void chr_cb(int start, int bank, int source) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	void update_regs();
	uint8_t m_reg[8];
	uint8_t m_low_reg;
>>>>>>> upstream/master
};


// ======================> nes_h2288_device

class nes_h2288_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_h2288_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_h);
	virtual void prg_cb(int start, int bank);

	virtual void pcb_reset();

private:
	UINT8 m_reg[2]; // reg 1 is unused?
=======
	nes_h2288_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
	virtual void prg_cb(int start, int bank) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg[2]; // reg 1 is unused?
>>>>>>> upstream/master
};


// ======================> nes_6035052_device

class nes_6035052_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_6035052_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_ex);
	virtual DECLARE_WRITE8_MEMBER(write_ex);
	virtual DECLARE_READ8_MEMBER(read_l) { return read_ex(space, offset, mem_mask); }
	virtual DECLARE_READ8_MEMBER(read_m) { return read_ex(space, offset, mem_mask); }
	virtual DECLARE_WRITE8_MEMBER(write_l) { write_ex(space, offset, data, mem_mask); }
	virtual DECLARE_WRITE8_MEMBER(write_m) { write_ex(space, offset, data, mem_mask); }

	virtual void pcb_reset();

private:
	UINT8 m_prot;
=======
	nes_6035052_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_ex) override;
	virtual DECLARE_WRITE8_MEMBER(write_ex) override;
	virtual DECLARE_READ8_MEMBER(read_l) override { return read_ex(space, offset, mem_mask); }
	virtual DECLARE_READ8_MEMBER(read_m) override { return read_ex(space, offset, mem_mask); }
	virtual DECLARE_WRITE8_MEMBER(write_l) override { write_ex(space, offset, data, mem_mask); }
	virtual DECLARE_WRITE8_MEMBER(write_m) override { write_ex(space, offset, data, mem_mask); }

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_prot;
>>>>>>> upstream/master
};


// ======================> nes_txc_tw_device

class nes_txc_tw_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_txc_tw_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_m) { write_l(space, offset & 0xff, data, mem_mask); }   // offset does not really count for this mapper }
	virtual void prg_cb(int start, int bank);
=======
	nes_txc_tw_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override { write_l(space, offset & 0xff, data, mem_mask); }   // offset does not really count for this mapper }
	virtual void prg_cb(int start, int bank) override;
>>>>>>> upstream/master
};


// ======================> nes_kof97_device

class nes_kof97_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_kof97_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h);
=======
	nes_kof97_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
>>>>>>> upstream/master
};


// ======================> nes_kof96_device

class nes_kof96_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_kof96_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_h);   // offset does not really count for this mapper
	virtual void prg_cb(int start, int bank);
	virtual void chr_cb(int start, int bank, int source);

	virtual void pcb_reset();

private:
	UINT8 m_reg[4];
=======
	nes_kof96_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;   // offset does not really count for this mapper
	virtual void prg_cb(int start, int bank) override;
	virtual void chr_cb(int start, int bank, int source) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg[4];
>>>>>>> upstream/master
};


// ======================> nes_sf3_device

class nes_sf3_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sf3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h);

protected:
	virtual void set_chr(UINT8 chr, int chr_base, int chr_mask);
=======
	nes_sf3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

protected:
	virtual void set_chr(uint8_t chr, int chr_base, int chr_mask) override;
>>>>>>> upstream/master
};


// ======================> nes_gouder_device

class nes_gouder_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_gouder_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual void prg_cb(int start, int bank);

	virtual void pcb_reset();

private:
	UINT8 m_reg[5];
=======
	nes_gouder_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual void prg_cb(int start, int bank) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg[5];
>>>>>>> upstream/master
};


// ======================> nes_sa9602b_device

class nes_sa9602b_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sa9602b_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);
	virtual void prg_cb(int start, int bank);

	virtual void pcb_reset();

private:
	UINT8 m_reg;
=======
	nes_sa9602b_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;
	virtual void prg_cb(int start, int bank) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg;
>>>>>>> upstream/master
	int m_prg_chip;
};


// ======================> nes_sachen_shero_device

class nes_sachen_shero_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sachen_shero_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual void chr_cb(int start, int bank, int source);

	virtual void pcb_reset();

private:
	UINT8 m_reg;
=======
	nes_sachen_shero_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual void chr_cb(int start, int bank, int source) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg;
>>>>>>> upstream/master
};

#ifdef UNUSED_FUNCTION
// ======================> nes_a9746_device

class nes_a9746_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_a9746_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	void update_banks(UINT8 value);
	UINT8 m_reg[3];
=======
	nes_a9746_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset();

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	void update_banks(uint8_t value);
	uint8_t m_reg[3];
>>>>>>> upstream/master
};
#endif


// ======================> nes_fk23c_device

class nes_fk23c_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_fk23c_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	nes_fk23c_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_h);
	virtual void prg_cb(int start, int bank);
	virtual void chr_cb(int start, int bank, int source);

	virtual void pcb_reset();

protected:
	void fk23c_set_prg();
	void fk23c_set_chr();
	UINT8 m_reg[8];
	UINT8 m_mmc_cmd1;
=======
	nes_fk23c_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
	virtual void prg_cb(int start, int bank) override;
	virtual void chr_cb(int start, int bank, int source) override;

	virtual void pcb_reset() override;

protected:
	nes_fk23c_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;

	void fk23c_set_prg();
	void fk23c_set_chr();
	uint8_t m_reg[8];
	uint8_t m_mmc_cmd1;
>>>>>>> upstream/master
};


// ======================> nes_fk23ca_device

class nes_fk23ca_device : public nes_fk23c_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_fk23ca_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual void pcb_reset();
=======
	nes_fk23ca_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void pcb_reset() override;
>>>>>>> upstream/master
};


// ======================> nes_s24in1sc03_device

class nes_s24in1sc03_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_s24in1sc03_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual void prg_cb(int start, int bank);
	virtual void chr_cb(int start, int bank, int source);

	virtual void pcb_reset();

private:
	UINT8 m_reg[3];
=======
	nes_s24in1sc03_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual void prg_cb(int start, int bank) override;
	virtual void chr_cb(int start, int bank, int source) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg[3];
>>>>>>> upstream/master
};


// ======================> nes_bmc_15in1_device

class nes_bmc_15in1_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_15in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();
=======
	nes_bmc_15in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_sbig7_device

class nes_bmc_sbig7_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_sbig7_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_bmc_sbig7_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_hik8_device

class nes_bmc_hik8_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_hik8_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();

private:
	UINT8 m_reg[4];
	UINT8 m_count;
=======
	nes_bmc_hik8_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg[4];
	uint8_t m_count;
>>>>>>> upstream/master
};


// ======================> nes_bmc_hik4_device

class nes_bmc_hik4_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_hik4_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();
=======
	nes_bmc_hik4_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;
>>>>>>> upstream/master
};


// ======================> nes_bmc_mario7in1_device

class nes_bmc_mario7in1_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_mario7in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();

private:
	UINT8 m_reg_written;
=======
	nes_bmc_mario7in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg_written;
>>>>>>> upstream/master
};


// ======================> nes_bmc_gold7in1_device

class nes_bmc_gold7in1_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_gold7in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();

private:
	UINT8 m_reg_written;
=======
	nes_bmc_gold7in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg_written;
>>>>>>> upstream/master
};


// ======================> nes_bmc_gc6in1_device

class nes_bmc_gc6in1_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_gc6in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_h);
	virtual void prg_cb(int start, int bank);
	virtual void chr_cb(int start, int bank, int source);

	virtual void pcb_reset();

private:
	UINT8 m_reg[4];
=======
	nes_bmc_gc6in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
	virtual void prg_cb(int start, int bank) override;
	virtual void chr_cb(int start, int bank, int source) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg[4];
>>>>>>> upstream/master
};


// ======================> nes_bmc_411120c_device

class nes_bmc_411120c_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_411120c_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual void prg_cb(int start, int bank);
	virtual void chr_cb(int start, int bank, int source);

	virtual void pcb_reset();

private:
	UINT8 m_reg;
=======
	nes_bmc_411120c_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual void prg_cb(int start, int bank) override;
	virtual void chr_cb(int start, int bank, int source) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg;
>>>>>>> upstream/master
};


// ======================> nes_bmc_830118c_device

class nes_bmc_830118c_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bmc_830118c_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual void prg_cb(int start, int bank);
	virtual void chr_cb(int start, int bank, int source);

	virtual void pcb_reset();

private:
	UINT8 m_reg;
=======
	nes_bmc_830118c_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual void prg_cb(int start, int bank) override;
	virtual void chr_cb(int start, int bank, int source) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg;
>>>>>>> upstream/master
};


// ======================> nes_pjoy84_device

class nes_pjoy84_device : public nes_txrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_pjoy84_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual void prg_cb(int start, int bank);
	virtual void chr_cb(int start, int bank, int source);

	virtual void pcb_reset();

private:
	inline void set_base_mask();
	UINT8 m_reg[4];
};




// device type definition
extern const device_type NES_NITRA;
extern const device_type NES_KS7057;
extern const device_type NES_SBROS11;
extern const device_type NES_MALISB;
extern const device_type NES_FAMILY4646;
extern const device_type NES_PIKAY2K;
extern const device_type NES_8237;
extern const device_type NES_SG_LIONK;
extern const device_type NES_SG_BOOG;
extern const device_type NES_KASING;
extern const device_type NES_KAY;
extern const device_type NES_H2288;
extern const device_type NES_6035052;
extern const device_type NES_TXC_TW;
extern const device_type NES_KOF97;
extern const device_type NES_KOF96;
extern const device_type NES_SF3;
extern const device_type NES_GOUDER;
extern const device_type NES_SA9602B;
extern const device_type NES_SACHEN_SHERO;
extern const device_type NES_A9746;

extern const device_type NES_FK23C;
extern const device_type NES_FK23CA;
extern const device_type NES_S24IN1SC03;
extern const device_type NES_BMC_15IN1;
extern const device_type NES_BMC_SBIG7;
extern const device_type NES_BMC_HIK8;
extern const device_type NES_BMC_HIK4;
extern const device_type NES_BMC_MARIO7IN1;
extern const device_type NES_BMC_GOLD7IN1;
extern const device_type NES_BMC_GC6IN1;
extern const device_type NES_BMC_411120C;
extern const device_type NES_BMC_830118C;
extern const device_type NES_PJOY84;

#endif
=======
	nes_pjoy84_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual void prg_cb(int start, int bank) override;
	virtual void chr_cb(int start, int bank, int source) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	inline void set_base_mask();
	uint8_t m_reg[4];
};

// ======================> nes_coolboy_device

class nes_coolboy_device : public nes_txrom_device
{
public:
	// construction/destruction
	nes_coolboy_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual void prg_cb(int start, int bank) override;
	virtual void chr_cb(int start, int bank, int source) override;

private:
	uint8_t m_reg[4];
};


// device type definition
DECLARE_DEVICE_TYPE(NES_NITRA,         nes_nitra_device)
DECLARE_DEVICE_TYPE(NES_KS7057,        nes_ks7057_device)
DECLARE_DEVICE_TYPE(NES_SBROS11,       nes_sbros11_device)
DECLARE_DEVICE_TYPE(NES_MALISB,        nes_malisb_device)
DECLARE_DEVICE_TYPE(NES_FAMILY4646,    nes_family4646_device)
DECLARE_DEVICE_TYPE(NES_PIKAY2K,       nes_pikay2k_device)
DECLARE_DEVICE_TYPE(NES_8237,          nes_8237_device)
DECLARE_DEVICE_TYPE(NES_SG_LIONK,      nes_sglionk_device)
DECLARE_DEVICE_TYPE(NES_SG_BOOG,       nes_sgboog_device)
DECLARE_DEVICE_TYPE(NES_KASING,        nes_kasing_device)
DECLARE_DEVICE_TYPE(NES_KAY,           nes_kay_device)
DECLARE_DEVICE_TYPE(NES_H2288,         nes_h2288_device)
DECLARE_DEVICE_TYPE(NES_6035052,       nes_6035052_device)
DECLARE_DEVICE_TYPE(NES_TXC_TW,        nes_txc_tw_device)
DECLARE_DEVICE_TYPE(NES_KOF97,         nes_kof97_device)
DECLARE_DEVICE_TYPE(NES_KOF96,         nes_kof96_device)
DECLARE_DEVICE_TYPE(NES_SF3,           nes_sf3_device)
DECLARE_DEVICE_TYPE(NES_GOUDER,        nes_gouder_device)
DECLARE_DEVICE_TYPE(NES_SA9602B,       nes_sa9602b_device)
DECLARE_DEVICE_TYPE(NES_SACHEN_SHERO,  nes_sachen_shero_device)
#ifdef UNUSED_FUNCTION
DECLARE_DEVICE_TYPE(NES_A9746,         nes_a9746_device)
#endif

DECLARE_DEVICE_TYPE(NES_FK23C,         nes_fk23c_device)
DECLARE_DEVICE_TYPE(NES_FK23CA,        nes_fk23ca_device)
DECLARE_DEVICE_TYPE(NES_S24IN1SC03,    nes_s24in1sc03_device)
DECLARE_DEVICE_TYPE(NES_BMC_15IN1,     nes_bmc_15in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_SBIG7,     nes_bmc_sbig7_device)
DECLARE_DEVICE_TYPE(NES_BMC_HIK8,      nes_bmc_hik8_device)
DECLARE_DEVICE_TYPE(NES_BMC_HIK4,      nes_bmc_hik4_device)
DECLARE_DEVICE_TYPE(NES_BMC_MARIO7IN1, nes_bmc_mario7in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_GOLD7IN1,  nes_bmc_gold7in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_GC6IN1,    nes_bmc_gc6in1_device)
DECLARE_DEVICE_TYPE(NES_BMC_411120C,   nes_bmc_411120c_device)
DECLARE_DEVICE_TYPE(NES_BMC_830118C,   nes_bmc_830118c_device)
DECLARE_DEVICE_TYPE(NES_PJOY84,        nes_pjoy84_device)
DECLARE_DEVICE_TYPE(NES_COOLBOY,       nes_coolboy_device)

#endif // MAME_BUS_NES_MMC3_CLONES_H
>>>>>>> upstream/master
