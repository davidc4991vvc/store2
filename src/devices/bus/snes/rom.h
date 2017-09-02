// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __SNS_ROM_H
#define __SNS_ROM_H
=======
#ifndef MAME_BUS_SNES_ROM_H
#define MAME_BUS_SNES_ROM_H

#pragma once
>>>>>>> upstream/master

#include "snes_slot.h"


// ======================> sns_rom_device

<<<<<<< HEAD
class sns_rom_device : public device_t,
						public device_sns_cart_interface
{
public:
	// construction/destruction
	sns_rom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	sns_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_READ8_MEMBER(read_h);
=======
class sns_rom_device : public device_t, public device_sns_cart_interface
{
public:
	// construction/destruction
	sns_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;

protected:
	sns_rom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};

// ======================> sns_rom_obc1_device

class sns_rom_obc1_device : public sns_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_obc1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(chip_read);
	virtual DECLARE_WRITE8_MEMBER(chip_write);
=======
	sns_rom_obc1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(chip_read) override;
	virtual DECLARE_WRITE8_MEMBER(chip_write) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

	int m_address;
	int m_offset;
	int m_shift;
<<<<<<< HEAD
	UINT8 m_ram[0x2000];
=======
	uint8_t m_ram[0x2000];
>>>>>>> upstream/master
};



// ======================> sns_rom_pokemon_device

class sns_rom_pokemon_device : public sns_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_pokemon_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(chip_read);    // protection device
	virtual DECLARE_WRITE8_MEMBER(chip_write);  // protection device
	UINT8 m_latch;
=======
	sns_rom_pokemon_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(chip_read) override;    // protection device
	virtual DECLARE_WRITE8_MEMBER(chip_write) override;  // protection device

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_latch;
>>>>>>> upstream/master
};

// ======================> sns_rom_tekken2_device

class sns_rom_tekken2_device : public sns_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_tekken2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(chip_read);    // protection device
	virtual DECLARE_WRITE8_MEMBER(chip_write);  // protection device

	void update_prot(UINT32 offset);

	// bit0-3 prot value, bit4 direction, bit5 function
	// reads must return (prot value) +1/-1/<<1/>>1 depending on bit4 & bit5
	UINT8 m_prot;
=======
	sns_rom_tekken2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(chip_read) override;    // protection device
	virtual DECLARE_WRITE8_MEMBER(chip_write) override;  // protection device

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	void update_prot(uint32_t offset);

	// bit0-3 prot value, bit4 direction, bit5 function
	// reads must return (prot value) +1/-1/<<1/>>1 depending on bit4 & bit5
	uint8_t m_prot;
>>>>>>> upstream/master
};

// ======================> sns_rom_soulblad_device

class sns_rom_soulblad_device : public sns_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_soulblad_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(chip_read);    // protection device
=======
	sns_rom_soulblad_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(chip_read) override;    // protection device
>>>>>>> upstream/master
};

// ======================> sns_rom_mcpirate1_device

class sns_rom_mcpirate1_device : public sns_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_mcpirate1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(chip_write);  // bankswitch device
	UINT8 m_base_bank;
=======
	sns_rom_mcpirate1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(chip_write) override;  // bankswitch device

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_base_bank;
>>>>>>> upstream/master
};

// ======================> sns_rom_mcpirate2_device

class sns_rom_mcpirate2_device : public sns_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_mcpirate2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(chip_write);  // bankswitch device
	UINT8 m_base_bank;
=======
	sns_rom_mcpirate2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(chip_write) override;  // bankswitch device

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_base_bank;
>>>>>>> upstream/master
};

// ======================> sns_rom_20col_device

class sns_rom_20col_device : public sns_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_20col_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(chip_write);  // bankswitch device
	UINT8 m_base_bank;
=======
	sns_rom_20col_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(chip_write) override;  // bankswitch device

protected:
	// device-level overrides
	virtual void device_start() override;

	uint8_t m_base_bank;
>>>>>>> upstream/master
};

// ======================> sns_rom_banana_device

class sns_rom_banana_device : public sns_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_banana_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

=======
	sns_rom_banana_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(chip_read) override;    // protection device
	virtual DECLARE_WRITE8_MEMBER(chip_write) override;  // protection device

protected:
>>>>>>> upstream/master
	// device-level overrides
//  virtual void device_start();
//  virtual void device_reset();

<<<<<<< HEAD
	// reading and writing
	virtual DECLARE_READ8_MEMBER(chip_read);    // protection device
	virtual DECLARE_WRITE8_MEMBER(chip_write);  // protection device
	UINT8 m_latch[16];
=======
	uint8_t m_latch[16];
>>>>>>> upstream/master
};

// ======================> sns_rom_bugs_device

class sns_rom_bugs_device : public sns_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_bugs_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(chip_read);    // protection device
	virtual DECLARE_WRITE8_MEMBER(chip_write);  // protection device
	UINT8 m_latch[0x800];
=======
	sns_rom_bugs_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(chip_read) override;    // protection device
	virtual DECLARE_WRITE8_MEMBER(chip_write) override;  // protection device

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_latch[0x800];
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type SNS_LOROM;
extern const device_type SNS_LOROM_OBC1;
extern const device_type SNS_LOROM_POKEMON;
extern const device_type SNS_LOROM_TEKKEN2;
extern const device_type SNS_LOROM_SOULBLAD;
extern const device_type SNS_LOROM_MCPIR1;
extern const device_type SNS_LOROM_MCPIR2;
extern const device_type SNS_LOROM_20COL;
extern const device_type SNS_LOROM_BANANA;
extern const device_type SNS_LOROM_BUGSLIFE;

#endif
=======
DECLARE_DEVICE_TYPE(SNS_LOROM,          sns_rom_device)
DECLARE_DEVICE_TYPE(SNS_LOROM_OBC1,     sns_rom_obc1_device)
DECLARE_DEVICE_TYPE(SNS_LOROM_POKEMON,  sns_rom_pokemon_device)
DECLARE_DEVICE_TYPE(SNS_LOROM_TEKKEN2,  sns_rom_tekken2_device)
DECLARE_DEVICE_TYPE(SNS_LOROM_SOULBLAD, sns_rom_soulblad_device)
DECLARE_DEVICE_TYPE(SNS_LOROM_MCPIR1,   sns_rom_mcpirate1_device)
DECLARE_DEVICE_TYPE(SNS_LOROM_MCPIR2,   sns_rom_mcpirate2_device)
DECLARE_DEVICE_TYPE(SNS_LOROM_20COL,    sns_rom_20col_device)
DECLARE_DEVICE_TYPE(SNS_LOROM_BANANA,   sns_rom_banana_device)
DECLARE_DEVICE_TYPE(SNS_LOROM_BUGSLIFE, sns_rom_bugs_device)

#endif // MAME_BUS_SNES_ROM_H
>>>>>>> upstream/master
