// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __SNS_BSX_H
#define __SNS_BSX_H
=======
#ifndef MAME_BUS_SNES_BSX_H
#define MAME_BUS_SNES_BSX_H

#pragma once
>>>>>>> upstream/master

#include "snes_slot.h"
#include "rom.h"
#include "rom21.h"

<<<<<<< HEAD
class BSX_base
{
public:
	BSX_base(running_machine &machine);
	running_machine &machine() const { return m_machine; }

	void init();
	UINT8 read(UINT32 offset);
	void write(UINT32 offset, UINT8 data);

private:
	// regs
	UINT8 regs[0x18];       // 0x2188-0x219f

	// counter + clock
	UINT8 r2192_counter;
	UINT8 r2192_hour, r2192_minute, r2192_second;

	running_machine& m_machine;
};

// ======================> sns_rom_bsx_device

class sns_rom_bsx_device : public sns_rom_device
{
public:
	// construction/destruction
	sns_rom_bsx_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	sns_rom_bsx_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual machine_config_constructor device_mconfig_additions() const;

	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_h);
	virtual DECLARE_READ8_MEMBER(chip_read);
	virtual DECLARE_WRITE8_MEMBER(chip_write);

	// base regs
	BSX_base *m_base_unit;

	// cart regs
	UINT8 m_cart_regs[16];
	UINT8 access_00_1f; // 1 = CART, 0 = NOTHING
	UINT8 access_80_9f; // 1 = CART, 0 = NOTHING
	UINT8 access_40_4f; // 1 = NOTHING, 0 = PRAM
	UINT8 access_50_5f; // 1 = NOTHING, 0 = PRAM
	UINT8 access_60_6f; // 1 = PRAM, 0 = NOTHING
	UINT8 rom_access;   // 2 = HiROM, 1 = LoROM, 0 = PRAM
	void access_update();


	UINT8 m_pram[0x80000];
=======
// ======================> sns_rom_bsx_device

class sns_rom_bsx_device : public sns_rom_device
{
public:
	// construction/destruction
	sns_rom_bsx_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;
	virtual DECLARE_READ8_MEMBER(chip_read) override;
	virtual DECLARE_WRITE8_MEMBER(chip_write) override;

protected:
	class bsx_base
	{
	public:
		bsx_base(running_machine &machine);
		running_machine &machine() const { return m_machine; }

		void init();
		uint8_t read(uint32_t offset);
		void write(uint32_t offset, uint8_t data);

	private:
		// regs
		uint8_t regs[0x18];       // 0x2188-0x219f

		// counter + clock
		uint8_t r2192_counter;
		uint8_t r2192_hour, r2192_minute, r2192_second;

		running_machine& m_machine;
	};

	sns_rom_bsx_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual void device_add_mconfig(machine_config &config) override;

	void access_update();

	// base regs
	std::unique_ptr<bsx_base> m_base_unit;

	// cart regs
	uint8_t m_cart_regs[16];
	uint8_t access_00_1f; // 1 = CART, 0 = NOTHING
	uint8_t access_80_9f; // 1 = CART, 0 = NOTHING
	uint8_t access_40_4f; // 1 = NOTHING, 0 = PRAM
	uint8_t access_50_5f; // 1 = NOTHING, 0 = PRAM
	uint8_t access_60_6f; // 1 = PRAM, 0 = NOTHING
	uint8_t rom_access;   // 2 = HiROM, 1 = LoROM, 0 = PRAM

	uint8_t m_pram[0x80000];
>>>>>>> upstream/master

private:
	required_device<sns_bsx_cart_slot_device> m_slot;
};

// ======================> sns_rom_bsxlo_device

class sns_rom_bsxlo_device : public sns_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_bsxlo_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;

	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_READ8_MEMBER(read_h);
=======
	sns_rom_bsxlo_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;

protected:
	// device-level overrides
	virtual void device_start() override;

	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

private:
	required_device<sns_bsx_cart_slot_device> m_slot;
};

// ======================> sns_rom_bsxhi_device

class sns_rom_bsxhi_device : public sns_rom21_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_bsxhi_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;

	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_READ8_MEMBER(read_h);
=======
	sns_rom_bsxhi_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;

protected:
	// device-level overrides
	virtual void device_start() override;

	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

private:
	required_device<sns_bsx_cart_slot_device> m_slot;
};


// ======================> sns_rom_bsmempak_device

class sns_rom_bsmempak_device : public sns_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_bsmempak_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_l);
=======
	sns_rom_bsmempak_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
>>>>>>> upstream/master
//  virtual DECLARE_WRITE8_MEMBER(write_h);
//  virtual DECLARE_READ8_MEMBER(chip_read);
//  virtual DECLARE_WRITE8_MEMBER(chip_write);

<<<<<<< HEAD
	// flash regs
	UINT32 m_command;
	UINT8 m_write_old;
	UINT8 m_write_new;
=======
protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// flash regs
	uint32_t m_command;
	uint8_t m_write_old;
	uint8_t m_write_new;
>>>>>>> upstream/master

	int m_flash_enable;
	int m_read_enable;
	int m_write_enable;
};


// device type definition
<<<<<<< HEAD
extern const device_type SNS_ROM_BSX;
extern const device_type SNS_LOROM_BSX;
extern const device_type SNS_HIROM_BSX;
extern const device_type SNS_BSMEMPAK;

#endif
=======
DECLARE_DEVICE_TYPE(SNS_ROM_BSX,   sns_rom_bsx_device)
DECLARE_DEVICE_TYPE(SNS_LOROM_BSX, sns_rom_bsxlo_device)
DECLARE_DEVICE_TYPE(SNS_HIROM_BSX, sns_rom_bsxhi_device)
DECLARE_DEVICE_TYPE(SNS_BSMEMPAK,  sns_rom_bsmempak_device)

#endif // MAME_BUS_SNES_BSX_H
>>>>>>> upstream/master
