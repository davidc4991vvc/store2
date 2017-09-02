// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_PIR_H
#define __NES_PIR_H
=======
#ifndef MAME_BUS_NES_PIRATE_H
#define MAME_BUS_NES_PIRATE_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_agci_device

class nes_agci_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_agci_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_agci_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_dreamtech_device

class nes_dreamtech_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_dreamtech_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);

	virtual void pcb_reset();
=======
	nes_dreamtech_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_fukutake_device

class nes_fukutake_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_fukutake_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
	UINT8 m_ram[0xb00];
=======
	nes_fukutake_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch;
	uint8_t m_ram[0xb00];
>>>>>>> upstream/master
};


// ======================> nes_futuremedia_device

class nes_futuremedia_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_futuremedia_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void hblank_irq(int scanline, int vblank, int blanked);
	virtual void pcb_reset();

private:
	UINT16 m_irq_count, m_irq_count_latch;
	UINT8 m_irq_clear;
=======
	nes_futuremedia_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void hblank_irq(int scanline, int vblank, int blanked) override;
	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint16_t m_irq_count, m_irq_count_latch;
	uint8_t m_irq_clear;
>>>>>>> upstream/master
	int m_irq_enable;
};


// ======================> nes_magseries_device

class nes_magseries_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_magseries_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_magseries_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_daou306_device

class nes_daou306_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_daou306_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_reg[16];
};


// ======================> nes_subor0_device

class nes_subor0_device : public nes_nrom_device
{
public:
	// construction/destruction
	nes_subor0_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_reg[4];
};


// ======================> nes_subor1_device

class nes_subor1_device : public nes_nrom_device
{
public:
	// construction/destruction
	nes_subor1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_reg[4];
=======
	nes_daou306_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg[16];
>>>>>>> upstream/master
};


// ======================> nes_cc21_device

class nes_cc21_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_cc21_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_cc21_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_xiaozy_device

class nes_xiaozy_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_xiaozy_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);

	virtual void pcb_reset();
=======
	nes_xiaozy_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_edu2k_device

class nes_edu2k_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_edu2k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_edu2k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
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


// ======================> nes_t230_device

class nes_t230_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_t230_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void hblank_irq(int scanline, int vblank, int blanked);
	virtual void pcb_reset();

private:
	UINT16 m_irq_count, m_irq_count_latch;
	UINT8 m_irq_mode;
	int m_irq_enable, m_irq_enable_latch;

	UINT8 m_mmc_vrom_bank[8];
=======
	nes_t230_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void hblank_irq(int scanline, int vblank, int blanked) override;
	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint16_t m_irq_count, m_irq_count_latch;
	uint8_t m_irq_mode;
	int m_irq_enable, m_irq_enable_latch;

	uint8_t m_mmc_vrom_bank[8];
>>>>>>> upstream/master
};


// ======================> nes_mk2_device

class nes_mk2_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_mk2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void hblank_irq(int scanline, int vblank, int blanked);
	virtual void pcb_reset();

private:
	UINT16 m_irq_count, m_irq_count_latch;
	UINT8 m_irq_clear;
=======
	nes_mk2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void hblank_irq(int scanline, int vblank, int blanked) override;
	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint16_t m_irq_count, m_irq_count_latch;
	uint8_t m_irq_clear;
>>>>>>> upstream/master
	int m_irq_enable;
};


// ======================> nes_whero_device

class nes_whero_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_whero_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void hblank_irq(int scanline, int vblank, int blanked);
	virtual void pcb_reset();

private:
	UINT8 m_reg;
	UINT8 m_mmc_vrom_bank[8];

	UINT16 m_irq_count, m_irq_count_latch;
=======
	nes_whero_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void hblank_irq(int scanline, int vblank, int blanked) override;
	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg;
	uint8_t m_mmc_vrom_bank[8];

	uint16_t m_irq_count, m_irq_count_latch;
>>>>>>> upstream/master
	int m_irq_enable, m_irq_enable_latch;
//  int m_irq_mode;
};


// ======================> nes_43272_device

class nes_43272_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_43272_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT16 m_latch;
=======
	nes_43272_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint16_t m_latch;
>>>>>>> upstream/master
};


// ======================> nes_tf1201_device

class nes_tf1201_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_tf1201_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void hblank_irq(int scanline, int vblank, int blanked);
	virtual void pcb_reset();

private:
	void update_prg();
	UINT8 m_prg, m_swap;
	UINT16 m_irq_count;
	int m_irq_enable, m_irq_enable_latch;

	UINT8 m_mmc_vrom_bank[8];
=======
	nes_tf1201_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void hblank_irq(int scanline, int vblank, int blanked) override;
	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	void update_prg();
	uint8_t m_prg, m_swap;
	uint16_t m_irq_count;
	int m_irq_enable, m_irq_enable_latch;

	uint8_t m_mmc_vrom_bank[8];
>>>>>>> upstream/master
};


// ======================> nes_cityfight_device

class nes_cityfight_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_cityfight_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	void update_prg();
	UINT8 m_prg_reg, m_prg_mode;
	UINT16 m_irq_count;
	int m_irq_enable;

	static const device_timer_id TIMER_IRQ = 0;
	emu_timer *irq_timer;

	UINT8 m_mmc_vrom_bank[8];
=======
	nes_cityfight_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

private:
	static constexpr device_timer_id TIMER_IRQ = 0;

	void update_prg();

	uint8_t m_prg_reg, m_prg_mode;
	uint16_t m_irq_count;
	int m_irq_enable;

	emu_timer *irq_timer;

	uint8_t m_mmc_vrom_bank[8];
>>>>>>> upstream/master
};



#ifdef UNUSED_FUNCTION
// ======================> nes_fujiya_device

class nes_fujiya_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_fujiya_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_fujiya_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch;
>>>>>>> upstream/master
};
#endif


// device type definition
<<<<<<< HEAD
extern const device_type NES_AGCI_50282;
extern const device_type NES_DREAMTECH01;
extern const device_type NES_FUKUTAKE;
extern const device_type NES_FUTUREMEDIA;
extern const device_type NES_MAGSERIES;
extern const device_type NES_DAOU306;
extern const device_type NES_SUBOR0;
extern const device_type NES_SUBOR1;
extern const device_type NES_CC21;
extern const device_type NES_XIAOZY;
extern const device_type NES_EDU2K;
extern const device_type NES_T230;
extern const device_type NES_MK2;
extern const device_type NES_WHERO;
extern const device_type NES_43272;
extern const device_type NES_TF1201;
extern const device_type NES_CITYFIGHT;
extern const device_type NES_FUJIYA;

#endif
=======
DECLARE_DEVICE_TYPE(NES_AGCI_50282,  nes_agci_device)
DECLARE_DEVICE_TYPE(NES_DREAMTECH01, nes_dreamtech_device)
DECLARE_DEVICE_TYPE(NES_FUKUTAKE,    nes_fukutake_device)
DECLARE_DEVICE_TYPE(NES_FUTUREMEDIA, nes_futuremedia_device)
DECLARE_DEVICE_TYPE(NES_MAGSERIES,   nes_magseries_device)
DECLARE_DEVICE_TYPE(NES_DAOU306,     nes_daou306_device)
DECLARE_DEVICE_TYPE(NES_CC21,        nes_cc21_device)
DECLARE_DEVICE_TYPE(NES_XIAOZY,      nes_xiaozy_device)
DECLARE_DEVICE_TYPE(NES_EDU2K,       nes_edu2k_device)
DECLARE_DEVICE_TYPE(NES_T230,        nes_t230_device)
DECLARE_DEVICE_TYPE(NES_MK2,         nes_mk2_device)
DECLARE_DEVICE_TYPE(NES_WHERO,       nes_whero_device)
DECLARE_DEVICE_TYPE(NES_43272,       nes_43272_device)
DECLARE_DEVICE_TYPE(NES_TF1201,      nes_tf1201_device)
DECLARE_DEVICE_TYPE(NES_CITYFIGHT,   nes_cityfight_device)
//DECLARE_DEVICE_TYPE(NES_FUJIYA,      nes_fujiya_device)

#endif // MAME_BUS_NES_PIRATE_H
>>>>>>> upstream/master
