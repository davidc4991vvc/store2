// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_BTL_H
#define __NES_BTL_H
=======
#ifndef MAME_BUS_NES_BOOTLEG_H
#define MAME_BUS_NES_BOOTLEG_H
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_ax5705_device

class nes_ax5705_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ax5705_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	void set_prg();
	UINT8 m_mmc_prg_bank[2];
	UINT8 m_mmc_vrom_bank[8];
=======
	nes_ax5705_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	void set_prg();
	uint8_t m_mmc_prg_bank[2];
	uint8_t m_mmc_vrom_bank[8];
>>>>>>> upstream/master
};


// ======================> nes_sc127_device

class nes_sc127_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sc127_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void hblank_irq(int scanline, int vblank, int blanked);
	virtual void pcb_reset();

private:
	UINT16 m_irq_count;
=======
	nes_sc127_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void hblank_irq(int scanline, int vblank, int blanked) override;
	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint16_t m_irq_count;
>>>>>>> upstream/master
	int m_irq_enable;
};


// ======================> nes_mbaby_device

class nes_mbaby_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_mbaby_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
	int m_irq_enable;

	static const device_timer_id TIMER_IRQ = 0;
=======
	nes_mbaby_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

private:
	static constexpr device_timer_id TIMER_IRQ = 0;

	uint8_t m_latch;
	int m_irq_enable;

>>>>>>> upstream/master
	emu_timer *irq_timer;
	attotime timer_freq;
};


// ======================> nes_asn_device

class nes_asn_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_asn_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_asn_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch;
>>>>>>> upstream/master
};


// ======================> nes_smb3p_device

class nes_smb3p_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_smb3p_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT16 m_irq_count;
=======
	nes_smb3p_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

private:
	uint16_t m_irq_count;
>>>>>>> upstream/master
	int m_irq_enable;

	static const device_timer_id TIMER_IRQ = 0;
	emu_timer *irq_timer;
};


// ======================> nes_btl_dn_device

class nes_btl_dn_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_btl_dn_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void hblank_irq(int scanline, int vblank, int blanked);
	virtual void pcb_reset();

private:
	UINT16 m_irq_count;
=======
	nes_btl_dn_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void hblank_irq(int scanline, int vblank, int blanked) override;
	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint16_t m_irq_count;
>>>>>>> upstream/master
};


// ======================> nes_whirl2706_device

class nes_whirl2706_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_whirl2706_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_whirl2706_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch;
>>>>>>> upstream/master
};


// ======================> nes_smb2j_device

class nes_smb2j_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_smb2j_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_ex);
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT16 m_irq_count;
=======
	nes_smb2j_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_ex) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

private:
	uint16_t m_irq_count;
>>>>>>> upstream/master
	int m_irq_enable;

	static const device_timer_id TIMER_IRQ = 0;
	emu_timer *irq_timer;
};


// ======================> nes_smb2ja_device

class nes_smb2ja_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_smb2ja_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT16 m_irq_count;
=======
	nes_smb2ja_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

private:
	uint16_t m_irq_count;
>>>>>>> upstream/master
	int m_irq_enable;

	static const device_timer_id TIMER_IRQ = 0;
	emu_timer *irq_timer;
};


// ======================> nes_smb2jb_device

class nes_smb2jb_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_smb2jb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_ex);

	virtual void pcb_reset();

private:
	UINT16 m_irq_count;
=======
	nes_smb2jb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_ex) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

private:
	uint16_t m_irq_count;
>>>>>>> upstream/master
	int m_irq_enable;

	static const device_timer_id TIMER_IRQ = 0;
	emu_timer *irq_timer;
};


// ======================> nes_09034a_device

class nes_09034a_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_09034a_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_ex);
	virtual DECLARE_READ8_MEMBER(read_m);

	virtual void pcb_reset();

private:
	UINT8 m_reg;
=======
	nes_09034a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_ex) override;
	virtual DECLARE_READ8_MEMBER(read_m) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg;
>>>>>>> upstream/master
};


// ======================> nes_tobidase_device

class nes_tobidase_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_tobidase_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_l);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_tobidase_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch;
>>>>>>> upstream/master
};


// ======================> nes_lh32_device

class nes_lh32_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_lh32_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_lh32_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;
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


// ======================> nes_lh10_device

class nes_lh10_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_lh10_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	void update_prg();
	UINT8 m_latch;
	UINT8 m_reg[8];
=======
	nes_lh10_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	void update_prg();
	uint8_t m_latch;
	uint8_t m_reg[8];
>>>>>>> upstream/master
};


// ======================> nes_lh53_device

class nes_lh53_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_lh53_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_m) {}
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT16 m_irq_count;
	int m_irq_enable;
	UINT8 m_reg;
=======
	nes_lh53_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override {}
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

private:
	uint16_t m_irq_count;
	int m_irq_enable;
	uint8_t m_reg;
>>>>>>> upstream/master

	static const device_timer_id TIMER_IRQ = 0;
	emu_timer *irq_timer;
	attotime timer_freq;
};


// ======================> nes_2708_device

class nes_2708_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_2708_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_reg[2];
=======
	nes_2708_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;
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

// ======================> nes_ac08_device

class nes_ac08_device : public nes_nrom_device
{
public:
	// nes_ac08_device/destruction
<<<<<<< HEAD
	nes_ac08_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_ex);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_ac08_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_ex) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch;
>>>>>>> upstream/master
};

// ======================> nes_unl_bb_device

class nes_unl_bb_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_unl_bb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_reg[2];
=======
	nes_unl_bb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg[2];
>>>>>>> upstream/master
};

// ======================> nes_mmalee_device

class nes_mmalee_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_mmalee_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();
=======
	nes_mmalee_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};

// ======================> nes_shuiguan_device

class nes_shuiguan_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_shuiguan_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT16 m_irq_count;
	int m_irq_enable;
	UINT8 m_mmc_vrom_bank[8];
=======
	nes_shuiguan_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

private:
	uint16_t m_irq_count;
	int m_irq_enable;
	uint8_t m_mmc_vrom_bank[8];
>>>>>>> upstream/master

	static const device_timer_id TIMER_IRQ = 0;
	emu_timer *irq_timer;
};


<<<<<<< HEAD

// device type definition
extern const device_type NES_AX5705;
extern const device_type NES_SC127;
extern const device_type NES_MARIOBABY;
extern const device_type NES_ASN;
extern const device_type NES_SMB3PIRATE;
extern const device_type NES_BTL_DNINJA;
extern const device_type NES_WHIRLWIND_2706;
extern const device_type NES_SMB2J;
extern const device_type NES_SMB2JA;
extern const device_type NES_SMB2JB;
extern const device_type NES_09034A;
extern const device_type NES_TOBIDASE;
extern const device_type NES_LH32;
extern const device_type NES_LH10;
extern const device_type NES_LH53;
extern const device_type NES_2708;
extern const device_type NES_AC08;
extern const device_type NES_UNL_BB;
extern const device_type NES_MMALEE;
extern const device_type NES_SHUIGUAN;


#endif
=======
// ======================> nes_rt01_device

class nes_rt01_device : public nes_nrom_device
{
public:
	// construction/destruction
	nes_rt01_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
};



// device type definition
DECLARE_DEVICE_TYPE(NES_AX5705,         nes_ax5705_device)
DECLARE_DEVICE_TYPE(NES_SC127,          nes_sc127_device)
DECLARE_DEVICE_TYPE(NES_MARIOBABY,      nes_mbaby_device)
DECLARE_DEVICE_TYPE(NES_ASN,            nes_asn_device)
DECLARE_DEVICE_TYPE(NES_SMB3PIRATE,     nes_smb3p_device)
DECLARE_DEVICE_TYPE(NES_BTL_DNINJA,     nes_btl_dn_device)
DECLARE_DEVICE_TYPE(NES_WHIRLWIND_2706, nes_whirl2706_device)
DECLARE_DEVICE_TYPE(NES_SMB2J,          nes_smb2j_device)
DECLARE_DEVICE_TYPE(NES_SMB2JA,         nes_smb2ja_device)
DECLARE_DEVICE_TYPE(NES_SMB2JB,         nes_smb2jb_device)
DECLARE_DEVICE_TYPE(NES_09034A,         nes_09034a_device)
DECLARE_DEVICE_TYPE(NES_TOBIDASE,       nes_tobidase_device)
DECLARE_DEVICE_TYPE(NES_LH32,           nes_lh32_device)
DECLARE_DEVICE_TYPE(NES_LH10,           nes_lh10_device)
DECLARE_DEVICE_TYPE(NES_LH53,           nes_lh53_device)
DECLARE_DEVICE_TYPE(NES_2708,           nes_2708_device)
DECLARE_DEVICE_TYPE(NES_AC08,           nes_ac08_device)
DECLARE_DEVICE_TYPE(NES_UNL_BB,         nes_unl_bb_device)
DECLARE_DEVICE_TYPE(NES_MMALEE,         nes_mmalee_device)
DECLARE_DEVICE_TYPE(NES_SHUIGUAN,       nes_shuiguan_device)
DECLARE_DEVICE_TYPE(NES_RT01,           nes_rt01_device)


#endif // MAME_BUS_NES_BOOTLEG_H
>>>>>>> upstream/master
