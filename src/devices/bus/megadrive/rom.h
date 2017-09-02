// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __MD_ROM_H
#define __MD_ROM_H
=======
#ifndef MAME_BUS_MEGADRIVE_ROM_H
#define MAME_BUS_MEGADRIVE_ROM_H

#pragma once
>>>>>>> upstream/master

#include "md_slot.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> md_std_rom_device

class md_std_rom_device : public device_t,
						public device_md_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_std_rom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	md_std_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() {};

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) { if (offset < 0x400000/2) return m_rom[MD_ADDR(offset)]; else return 0xffff; };
	virtual DECLARE_WRITE16_MEMBER(write) { };
=======
	md_std_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override { if (offset < 0x400000/2) return m_rom[MD_ADDR(offset)]; else return 0xffff; }
	virtual DECLARE_WRITE16_MEMBER(write) override { }

protected:
	md_std_rom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override { }
>>>>>>> upstream/master
};

// ======================> md_rom_sram_device

class md_rom_sram_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_sram_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_WRITE16_MEMBER(write);
	virtual DECLARE_WRITE16_MEMBER(write_a13);
=======
	md_rom_sram_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write) override;
	virtual DECLARE_WRITE16_MEMBER(write_a13) override;
>>>>>>> upstream/master
};

// ======================> md_rom_fram_device

class md_rom_fram_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_fram_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_WRITE16_MEMBER(write);
	virtual DECLARE_READ16_MEMBER(read_a13);
	virtual DECLARE_WRITE16_MEMBER(write_a13);
=======
	md_rom_fram_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write) override;
	virtual DECLARE_READ16_MEMBER(read_a13) override;
	virtual DECLARE_WRITE16_MEMBER(write_a13) override;
>>>>>>> upstream/master
};

// ======================> md_rom_ssf2_device

class md_rom_ssf2_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_ssf2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_WRITE16_MEMBER(write_a13);

private:
	UINT8 m_bank[16];
=======
	md_rom_ssf2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write_a13) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t m_bank[16];
>>>>>>> upstream/master
	int m_lastoff, m_lastdata;
};

// ======================> md_rom_cm2in1_device

class md_rom_cm2in1_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_cm2in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
=======
	md_rom_cm2in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	int m_base;
};


// ======================> md_rom_mcpirate_device

class md_rom_mcpirate_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_mcpirate_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_WRITE16_MEMBER(write_a13);

private:
	UINT8 m_bank;
=======
	md_rom_mcpirate_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write_a13) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t m_bank;
>>>>>>> upstream/master
};


// ======================> md_rom_bugslife_device

class md_rom_bugslife_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_bugslife_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read_a13);
=======
	md_rom_bugslife_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read_a13) override;
>>>>>>> upstream/master
};

// ======================> md_rom_chinf3_device

class md_rom_chinf3_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_chinf3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_WRITE16_MEMBER(write);
=======
	md_rom_chinf3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	int m_bank;
};

// ======================> md_rom_16mj2_device

class md_rom_16mj2_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_16mj2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
=======
	md_rom_16mj2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
>>>>>>> upstream/master
};

// ======================> md_rom_elfwor_device

class md_rom_elfwor_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_elfwor_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
=======
	md_rom_elfwor_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
>>>>>>> upstream/master
};

// ======================> md_rom_yasech_device

class md_rom_yasech_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_yasech_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
=======
	md_rom_yasech_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
>>>>>>> upstream/master
};

// ======================> md_rom_kof98_device

class md_rom_kof98_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_kof98_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
=======
	md_rom_kof98_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
>>>>>>> upstream/master
};

// ======================> md_rom_kof99_device

class md_rom_kof99_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_kof99_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read_a13);
=======
	md_rom_kof99_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read_a13) override;
>>>>>>> upstream/master
};

// ======================> md_rom_lion2_device

class md_rom_lion2_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_lion2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_WRITE16_MEMBER(write);

private:
	UINT16 m_prot1_data, m_prot2_data;
=======
	md_rom_lion2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint16_t m_prot1_data, m_prot2_data;
>>>>>>> upstream/master
};

// ======================> md_rom_lion3_device

class md_rom_lion3_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_lion3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_WRITE16_MEMBER(write);

private:
	UINT8 m_reg[3];
	UINT16 m_bank;
=======
	md_rom_lion3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t m_reg[3];
	uint16_t m_bank;
>>>>>>> upstream/master
};

// ======================> md_rom_mjlov_device

class md_rom_mjlov_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_mjlov_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
=======
	md_rom_mjlov_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
};

// ======================> md_rom_cjmjclub_device

class md_rom_cjmjclub_device : public md_std_rom_device
{
public:
	// construction/destruction
	md_rom_cjmjclub_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
>>>>>>> upstream/master
};

// ======================> md_rom_pokea_device

class md_rom_pokea_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_pokea_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read_a13);
=======
	md_rom_pokea_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read_a13) override;
>>>>>>> upstream/master
};

// ======================> md_rom_pokestad_device

class md_rom_pokestad_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_pokestad_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_WRITE16_MEMBER(write);

private:
	UINT8 m_bank;
=======
	md_rom_pokestad_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t m_bank;
>>>>>>> upstream/master
};

// ======================> md_rom_realtec_device

class md_rom_realtec_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_realtec_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_WRITE16_MEMBER(write);

private:
	UINT16 m_bank_addr, m_bank_size, m_old_bank_addr;
=======
	md_rom_realtec_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint16_t m_bank_addr, m_bank_size, m_old_bank_addr;
>>>>>>> upstream/master
};

// ======================> md_rom_redcl_device

class md_rom_redcl_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_redcl_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
=======
	md_rom_redcl_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
>>>>>>> upstream/master
};

// ======================> md_rom_rx3_device

class md_rom_rx3_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_rx3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read_a13);
=======
	md_rom_rx3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read_a13) override;
>>>>>>> upstream/master
};

// ======================> md_rom_sbubl_device

class md_rom_sbubl_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_sbubl_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
=======
	md_rom_sbubl_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
>>>>>>> upstream/master
};

// ======================> md_rom_smb_device

class md_rom_smb_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_smb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read_a13);
=======
	md_rom_smb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read_a13) override;
>>>>>>> upstream/master
};

// ======================> md_rom_smb2_device

class md_rom_smb2_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_smb2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read_a13);
=======
	md_rom_smb2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read_a13) override;
>>>>>>> upstream/master
};

// ======================> md_rom_smw64_device

class md_rom_smw64_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_smw64_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_WRITE16_MEMBER(write);

private:
	UINT32 m_latch0, m_latch1;
	UINT16 m_reg[6];
	UINT16 m_ctrl[3];
=======
	md_rom_smw64_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint32_t m_latch0, m_latch1;
	uint16_t m_reg[6];
	uint16_t m_ctrl[3];
>>>>>>> upstream/master
};

// ======================> md_rom_smouse_device

class md_rom_smouse_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_smouse_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
=======
	md_rom_smouse_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
>>>>>>> upstream/master
};


// ======================> md_rom_soulb_device

class md_rom_soulb_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_soulb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
=======
	md_rom_soulb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
>>>>>>> upstream/master
};

// ======================> md_rom_squir_device

class md_rom_squir_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_squir_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_WRITE16_MEMBER(write);

private:
	UINT16 m_latch;
=======
	md_rom_squir_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint16_t m_latch;
>>>>>>> upstream/master
};

// ======================> md_rom_tekkensp_device

class md_rom_tekkensp_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_tekkensp_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_WRITE16_MEMBER(write);

private:
	UINT16 m_reg;
=======
	md_rom_tekkensp_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint16_t m_reg;
>>>>>>> upstream/master
};

// ======================> md_rom_topf_device

class md_rom_topf_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_topf_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_WRITE16_MEMBER(write);

private:
	UINT16 m_latch;
	UINT8 m_bank[3];
=======
	md_rom_topf_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint16_t m_latch;
	uint8_t m_bank[3];
>>>>>>> upstream/master
};

// ======================> md_rom_radica_device

class md_rom_radica_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_radica_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_READ16_MEMBER(read_a13);

private:
	UINT8 m_bank;
=======
	md_rom_radica_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_READ16_MEMBER(read_a13) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t m_bank;
>>>>>>> upstream/master
};

// ======================> md_rom_beggarp_device

class md_rom_beggarp_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_beggarp_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_WRITE16_MEMBER(write);
	virtual DECLARE_WRITE16_MEMBER(write_a13);

private:
	UINT8 m_mode, m_lock;
=======
	md_rom_beggarp_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write) override;
	virtual DECLARE_WRITE16_MEMBER(write_a13) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t m_mode, m_lock;
>>>>>>> upstream/master
};

// ======================> md_rom_wukong_device

class md_rom_wukong_device : public md_std_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	md_rom_wukong_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_WRITE16_MEMBER(write);
	virtual DECLARE_WRITE16_MEMBER(write_a13);

private:
	UINT8 m_mode;
=======
	md_rom_wukong_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write) override;
	virtual DECLARE_WRITE16_MEMBER(write_a13) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t m_mode;
};

// ======================> md_rom_starodys_device

class md_rom_starodys_device : public md_std_rom_device
{
public:
	// construction/destruction
	md_rom_starodys_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_WRITE16_MEMBER(write) override;
	virtual DECLARE_READ16_MEMBER(read_a13) override;
	virtual DECLARE_WRITE16_MEMBER(write_a13) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t m_mode, m_lock, m_ram_enable, m_base;
>>>>>>> upstream/master
};



// device type definition
<<<<<<< HEAD
extern const device_type MD_STD_ROM;
extern const device_type MD_ROM_SRAM;
extern const device_type MD_ROM_FRAM;
extern const device_type MD_ROM_CM2IN1;
extern const device_type MD_ROM_16MJ2;
extern const device_type MD_ROM_BUGSLIFE;
extern const device_type MD_ROM_CHINF3;
extern const device_type MD_ROM_ELFWOR;
extern const device_type MD_ROM_YASECH;
extern const device_type MD_ROM_KOF98;
extern const device_type MD_ROM_KOF99;
extern const device_type MD_ROM_LION2;
extern const device_type MD_ROM_LION3;
extern const device_type MD_ROM_MCPIR;
extern const device_type MD_ROM_MJLOV;
extern const device_type MD_ROM_POKEA;
extern const device_type MD_ROM_POKESTAD;
extern const device_type MD_ROM_REALTEC;
extern const device_type MD_ROM_REDCL;
extern const device_type MD_ROM_RX3;
extern const device_type MD_ROM_SBUBL;
extern const device_type MD_ROM_SMB;
extern const device_type MD_ROM_SMB2;
extern const device_type MD_ROM_SMW64;
extern const device_type MD_ROM_SMOUSE;
extern const device_type MD_ROM_SOULB;
extern const device_type MD_ROM_SSF2;
extern const device_type MD_ROM_SQUIR;
extern const device_type MD_ROM_TEKKENSP;
extern const device_type MD_ROM_TOPF;
extern const device_type MD_ROM_RADICA;
extern const device_type MD_ROM_BEGGARP;
extern const device_type MD_ROM_WUKONG;

#endif
=======
DECLARE_DEVICE_TYPE(MD_STD_ROM,      md_std_rom_device)
DECLARE_DEVICE_TYPE(MD_ROM_SRAM,     md_rom_sram_device)
DECLARE_DEVICE_TYPE(MD_ROM_FRAM,     md_rom_fram_device)
DECLARE_DEVICE_TYPE(MD_ROM_CM2IN1,   md_rom_cm2in1_device)
DECLARE_DEVICE_TYPE(MD_ROM_SSF2,     md_rom_ssf2_device)
DECLARE_DEVICE_TYPE(MD_ROM_BUGSLIFE, md_rom_bugslife_device)
DECLARE_DEVICE_TYPE(MD_ROM_SMOUSE,   md_rom_smouse_device)
DECLARE_DEVICE_TYPE(MD_ROM_SMW64,    md_rom_smw64_device)
DECLARE_DEVICE_TYPE(MD_ROM_SMB,      md_rom_smb_device)
DECLARE_DEVICE_TYPE(MD_ROM_SMB2,     md_rom_smb2_device)
DECLARE_DEVICE_TYPE(MD_ROM_SBUBL,    md_rom_sbubl_device)
DECLARE_DEVICE_TYPE(MD_ROM_RX3,      md_rom_rx3_device)
DECLARE_DEVICE_TYPE(MD_ROM_MJLOV,    md_rom_mjlov_device)
DECLARE_DEVICE_TYPE(MD_ROM_CJMJCLUB, md_rom_cjmjclub_device)
DECLARE_DEVICE_TYPE(MD_ROM_KOF98,    md_rom_kof98_device)
DECLARE_DEVICE_TYPE(MD_ROM_KOF99,    md_rom_kof99_device)
DECLARE_DEVICE_TYPE(MD_ROM_SOULB,    md_rom_soulb_device)
DECLARE_DEVICE_TYPE(MD_ROM_CHINF3,   md_rom_chinf3_device)
DECLARE_DEVICE_TYPE(MD_ROM_16MJ2,    md_rom_16mj2_device)
DECLARE_DEVICE_TYPE(MD_ROM_ELFWOR,   md_rom_elfwor_device)
DECLARE_DEVICE_TYPE(MD_ROM_YASECH,   md_rom_yasech_device)
DECLARE_DEVICE_TYPE(MD_ROM_LION2,    md_rom_lion2_device)
DECLARE_DEVICE_TYPE(MD_ROM_LION3,    md_rom_lion3_device)
DECLARE_DEVICE_TYPE(MD_ROM_MCPIR,    md_rom_mcpirate_device)
DECLARE_DEVICE_TYPE(MD_ROM_POKEA,    md_rom_pokea_device)
DECLARE_DEVICE_TYPE(MD_ROM_POKESTAD, md_rom_pokestad_device)
DECLARE_DEVICE_TYPE(MD_ROM_REALTEC,  md_rom_realtec_device)
DECLARE_DEVICE_TYPE(MD_ROM_REDCL,    md_rom_redcl_device)
DECLARE_DEVICE_TYPE(MD_ROM_SQUIR,    md_rom_squir_device)
DECLARE_DEVICE_TYPE(MD_ROM_TEKKENSP, md_rom_tekkensp_device)
DECLARE_DEVICE_TYPE(MD_ROM_TOPF,     md_rom_topf_device)
DECLARE_DEVICE_TYPE(MD_ROM_RADICA,   md_rom_radica_device)
DECLARE_DEVICE_TYPE(MD_ROM_BEGGARP,  md_rom_beggarp_device)
DECLARE_DEVICE_TYPE(MD_ROM_WUKONG,   md_rom_wukong_device)
DECLARE_DEVICE_TYPE(MD_ROM_STARODYS, md_rom_starodys_device)

#endif // MAME_BUS_MEGADRIVE_ROM_H
>>>>>>> upstream/master
