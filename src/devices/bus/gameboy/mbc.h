// license:BSD-3-Clause
// copyright-holders:Fabio Priuli, Wilbert Pol
<<<<<<< HEAD
#ifndef __GB_MBC_H
#define __GB_MBC_H
=======
#ifndef MAME_BUS_GAMEBOY_MBC_H
#define MAME_BUS_GAMEBOY_MBC_H
>>>>>>> upstream/master

#include "gb_slot.h"


// ======================> gb_rom_mbc_device

class gb_rom_mbc_device : public device_t,
						public device_gb_cart_interface
{
public:
<<<<<<< HEAD
	// construction/destruction
	gb_rom_mbc_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// device-level overrides
	virtual void device_start() { shared_start(); };
	virtual void device_reset() { shared_reset(); };
=======
	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

protected:
	// construction/destruction
	gb_rom_mbc_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override { shared_start(); }
	virtual void device_reset() override { shared_reset(); }
>>>>>>> upstream/master

	void shared_start();
	void shared_reset();

<<<<<<< HEAD
	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);

	UINT8 m_ram_enable;
=======
	uint8_t m_ram_enable;
>>>>>>> upstream/master
};

// ======================> gb_rom_mbc1_device

class gb_rom_mbc1_device : public gb_rom_mbc_device
{
public:

<<<<<<< HEAD
=======
	// construction/destruction
	gb_rom_mbc1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

protected:
>>>>>>> upstream/master
	enum {
		MODE_16M_64k = 0, /// 16Mbit ROM, 64kBit RAM
		MODE_4M_256k = 1  /// 4Mbit ROM, 256kBit RAM
	};

<<<<<<< HEAD
	// construction/destruction
	gb_rom_mbc1_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	gb_rom_mbc1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() { shared_start(); save_item(NAME(m_mode)); };
	virtual void device_reset() { shared_reset(); m_mode = MODE_16M_64k; };
	virtual void set_additional_wirings(UINT8 mask, int shift) { m_mask = mask; m_shift = shift; }  // these get set at cart loading

	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);

	UINT8 m_mode, m_mask;
=======
	gb_rom_mbc1_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override { shared_start(); save_item(NAME(m_mode)); }
	virtual void device_reset() override { shared_reset(); m_mode = MODE_16M_64k; }
	virtual void set_additional_wirings(uint8_t mask, int shift) override { m_mask = mask; m_shift = shift; }  // these get set at cart loading

	uint8_t m_mode, m_mask;
>>>>>>> upstream/master
	int m_shift;
};

// ======================> gb_rom_mbc2_device

class gb_rom_mbc2_device : public gb_rom_mbc_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	gb_rom_mbc2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() { shared_start(); };
	virtual void device_reset() { shared_reset(); };

	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
=======
	gb_rom_mbc2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

protected:
	// device-level overrides
	virtual void device_start() override { shared_start(); }
	virtual void device_reset() override { shared_reset(); }
>>>>>>> upstream/master
};

// ======================> gb_rom_mbc3_device

class gb_rom_mbc3_device : public gb_rom_mbc_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	gb_rom_mbc3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
	UINT8 m_rtc_map[5];
=======
	gb_rom_mbc3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	void update_rtc();
	uint8_t m_rtc_regs[5];
	int m_rtc_ready;
>>>>>>> upstream/master
};

// ======================> gb_rom_mbc5_device

class gb_rom_mbc5_device : public gb_rom_mbc_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	gb_rom_mbc5_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	gb_rom_mbc5_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() { shared_start(); };
	virtual void device_reset() { shared_reset(); };

	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
=======
	gb_rom_mbc5_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

protected:
	gb_rom_mbc5_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override { shared_start(); }
	virtual void device_reset() override { shared_reset(); }
>>>>>>> upstream/master
};

// ======================> gb_rom_mbc6_device

class gb_rom_mbc6_device : public gb_rom_mbc_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	gb_rom_mbc6_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
	UINT16 m_latch1, m_latch2;
	UINT8 m_bank_4000, m_bank_6000;
=======
	gb_rom_mbc6_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	uint16_t m_latch1, m_latch2;
	uint8_t m_bank_4000, m_bank_6000;
>>>>>>> upstream/master
};

// ======================> gb_rom_mbc7_device

class gb_rom_mbc7_device : public gb_rom_mbc_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	gb_rom_mbc7_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() { shared_start(); };
	virtual void device_reset() { shared_reset(); };

	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
=======
	gb_rom_mbc7_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

protected:
	// device-level overrides
	virtual void device_start() override { shared_start(); }
	virtual void device_reset() override { shared_reset(); }
>>>>>>> upstream/master
};

// ======================> gb_rom_m161_device

class gb_rom_m161_device : public gb_rom_mbc_device
{
public:
<<<<<<< HEAD

	// construction/destruction
	gb_rom_m161_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_READ8_MEMBER(read_ram) { return 0xff; }
	virtual DECLARE_WRITE8_MEMBER(write_ram) { }

	UINT8 m_base_bank;
=======
	// construction/destruction
	gb_rom_m161_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override { return 0xff; }
	virtual DECLARE_WRITE8_MEMBER(write_ram) override { }

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_base_bank;
	uint8_t m_load_disable;
>>>>>>> upstream/master
};

// ======================> gb_rom_mmm01_device
class gb_rom_mmm01_device : public gb_rom_mbc_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	gb_rom_mmm01_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	UINT8 m_bank_mask, m_bank, m_reg;
=======
	gb_rom_mmm01_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	uint16_t m_romb;
	uint8_t  m_romb_nwe;
	uint8_t  m_ramb;
	uint8_t  m_ramb_nwe;
	uint8_t  m_mode;
	uint8_t  m_mode_nwe;
	uint8_t  m_map;
	uint8_t  m_mux;
>>>>>>> upstream/master
};

// ======================> gb_rom_sachen_mmc1_device

class gb_rom_sachen_mmc1_device : public gb_rom_mbc_device
{
public:
<<<<<<< HEAD

=======
	// construction/destruction
	gb_rom_sachen_mmc1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override { return 0xff; }
	virtual DECLARE_WRITE8_MEMBER(write_ram) override { }

protected:
>>>>>>> upstream/master
	enum {
		MODE_LOCKED,
		MODE_UNLOCKED
	};

<<<<<<< HEAD
	// construction/destruction
	gb_rom_sachen_mmc1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	gb_rom_sachen_mmc1_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_READ8_MEMBER(read_ram) { return 0xff; }
	virtual DECLARE_WRITE8_MEMBER(write_ram) { }

	UINT8 m_base_bank, m_mask, m_mode, m_unlock_cnt;
=======
	gb_rom_sachen_mmc1_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_base_bank, m_mask, m_mode, m_unlock_cnt;
>>>>>>> upstream/master
};

// ======================> gb_rom_sachen_mmc2_device

class gb_rom_sachen_mmc2_device : public gb_rom_sachen_mmc1_device
{
public:
<<<<<<< HEAD

=======
	// construction/destruction
	gb_rom_sachen_mmc2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

protected:
>>>>>>> upstream/master
	enum {
		MODE_LOCKED_DMG,
		MODE_LOCKED_CGB,
		MODE_UNLOCKED
	};

<<<<<<< HEAD
	// construction/destruction
	gb_rom_sachen_mmc2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);

=======
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master
};

// ======================> gb_rom_188in1_device
class gb_rom_188in1_device : public gb_rom_mbc1_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	gb_rom_188in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() { shared_start(); save_item(NAME(m_game_base)); };
	virtual void device_reset() { shared_reset(); m_game_base = 0; };

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);

private:
	UINT32 m_game_base;
=======
	gb_rom_188in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

protected:
	// device-level overrides
	virtual void device_start() override { shared_start(); save_item(NAME(m_game_base)); }
	virtual void device_reset() override { shared_reset(); m_game_base = 0; }

private:
	uint32_t m_game_base;
>>>>>>> upstream/master
};

// ======================> gb_rom_sintax_device
class gb_rom_sintax_device : public gb_rom_mbc_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	gb_rom_sintax_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	void set_xor_for_bank(UINT8 bank);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
	UINT8 m_bank_mask, m_bank, m_reg;

	UINT8 m_currentxor, m_xor2, m_xor3, m_xor4, m_xor5, m_sintax_mode;
=======
	gb_rom_sintax_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	void set_xor_for_bank(uint8_t bank);

	uint8_t m_bank_mask, m_bank, m_reg;

	uint8_t m_currentxor, m_xor2, m_xor3, m_xor4, m_xor5, m_sintax_mode;
>>>>>>> upstream/master
};

// ======================> gb_rom_chongwu_device

class gb_rom_chongwu_device : public gb_rom_mbc5_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	gb_rom_chongwu_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_rom);
	UINT8 m_protection_checked;
=======
	gb_rom_chongwu_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_rom) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_protection_checked;
>>>>>>> upstream/master
};

// ======================> gb_rom_licheng_device

class gb_rom_licheng_device : public gb_rom_mbc5_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	gb_rom_licheng_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_WRITE8_MEMBER(write_bank);
=======
	gb_rom_licheng_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
>>>>>>> upstream/master
};

// ======================> gb_rom_digimon_device

class gb_rom_digimon_device : public gb_rom_mbc5_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	gb_rom_digimon_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() { shared_start(); };
	virtual void device_reset() { shared_reset(); };

	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
=======
	gb_rom_digimon_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;

protected:
	// device-level overrides
	virtual void device_start() override { shared_start(); }
	virtual void device_reset() override { shared_reset(); }
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;
>>>>>>> upstream/master
};

// ======================> gb_rom_rockman8_device
class gb_rom_rockman8_device : public gb_rom_mbc_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	gb_rom_rockman8_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() { shared_start(); };
	virtual void device_reset() { shared_reset(); };

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
	UINT8 m_bank_mask, m_bank, m_reg;
=======
	gb_rom_rockman8_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

protected:
	// device-level overrides
	virtual void device_start() override { shared_start(); }
	virtual void device_reset() override { shared_reset(); }

	uint8_t m_bank_mask, m_bank, m_reg;
>>>>>>> upstream/master
};

// ======================> gb_rom_sm3sp_device
class gb_rom_sm3sp_device : public gb_rom_mbc_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	gb_rom_sm3sp_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() { shared_start(); };
	virtual void device_reset() { shared_reset(); };

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
	UINT8 m_bank_mask, m_bank, m_reg, m_mode;
=======
	gb_rom_sm3sp_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

protected:
	// device-level overrides
	virtual void device_start() override { shared_start(); }
	virtual void device_reset() override { shared_reset(); }

	uint8_t m_bank_mask, m_bank, m_reg, m_mode;
>>>>>>> upstream/master
};



// device type definition
<<<<<<< HEAD
extern const device_type GB_ROM_MBC1;
extern const device_type GB_ROM_MBC1_COL;
extern const device_type GB_ROM_MBC2;
extern const device_type GB_ROM_MBC3;
extern const device_type GB_ROM_MBC4;
extern const device_type GB_ROM_MBC5;
extern const device_type GB_ROM_MBC6;
extern const device_type GB_ROM_MBC7;
extern const device_type GB_ROM_M161_M12;
extern const device_type GB_ROM_MMM01;
extern const device_type GB_ROM_SACHEN1;
extern const device_type GB_ROM_SACHEN2;
extern const device_type GB_ROM_188IN1;
extern const device_type GB_ROM_SINTAX;
extern const device_type GB_ROM_CHONGWU;
extern const device_type GB_ROM_LICHENG;
extern const device_type GB_ROM_DIGIMON;
extern const device_type GB_ROM_ROCKMAN8;
extern const device_type GB_ROM_SM3SP;

#endif
=======
DECLARE_DEVICE_TYPE(GB_ROM_MBC1,     gb_rom_mbc1_device)
DECLARE_DEVICE_TYPE(GB_ROM_MBC2,     gb_rom_mbc2_device)
DECLARE_DEVICE_TYPE(GB_ROM_MBC3,     gb_rom_mbc3_device)
DECLARE_DEVICE_TYPE(GB_ROM_MBC5,     gb_rom_mbc5_device)
DECLARE_DEVICE_TYPE(GB_ROM_MBC6,     gb_rom_mbc6_device)
DECLARE_DEVICE_TYPE(GB_ROM_MBC7,     gb_rom_mbc7_device)
DECLARE_DEVICE_TYPE(GB_ROM_M161,     gb_rom_m161_device)
DECLARE_DEVICE_TYPE(GB_ROM_MMM01,    gb_rom_mmm01_device)
DECLARE_DEVICE_TYPE(GB_ROM_SACHEN1,  gb_rom_sachen_mmc1_device)
DECLARE_DEVICE_TYPE(GB_ROM_SACHEN2,  gb_rom_sachen_mmc2_device)
DECLARE_DEVICE_TYPE(GB_ROM_188IN1,   gb_rom_188in1_device)
DECLARE_DEVICE_TYPE(GB_ROM_SINTAX,   gb_rom_sintax_device)
DECLARE_DEVICE_TYPE(GB_ROM_CHONGWU,  gb_rom_chongwu_device)
DECLARE_DEVICE_TYPE(GB_ROM_LICHENG,  gb_rom_licheng_device)
DECLARE_DEVICE_TYPE(GB_ROM_DIGIMON,  gb_rom_digimon_device)
DECLARE_DEVICE_TYPE(GB_ROM_ROCKMAN8, gb_rom_rockman8_device)
DECLARE_DEVICE_TYPE(GB_ROM_SM3SP,    gb_rom_sm3sp_device)

#endif // MAME_BUS_GAMEBOY_MBC_H
>>>>>>> upstream/master
