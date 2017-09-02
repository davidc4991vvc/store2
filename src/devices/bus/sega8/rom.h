// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __SEGA8_ROM_H
#define __SEGA8_ROM_H
=======
#ifndef MAME_BUS_SEGA8_ROM_H
#define MAME_BUS_SEGA8_ROM_H

#pragma once
>>>>>>> upstream/master

#include "sega8_slot.h"
#include "machine/eepromser.h"

// ======================> sega8_rom_device

class sega8_rom_device : public device_t,
						public device_sega8_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_rom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	sega8_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void late_bank_setup();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
	virtual DECLARE_WRITE8_MEMBER(write_mapper);

protected:
	UINT8 m_rom_bank_base[3];
	UINT8 m_ram_base;
=======
	sega8_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void late_bank_setup() override;

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override;

protected:
	sega8_rom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_rom_bank_base[3];
	uint8_t m_ram_base;
>>>>>>> upstream/master
	int m_ram_enabled;
};




// ======================> sega8_othello_device

class sega8_othello_device : public sega8_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_othello_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
	virtual DECLARE_WRITE8_MEMBER(write_mapper) {}
=======
	sega8_othello_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override { }
>>>>>>> upstream/master
};


// ======================> sega8_castle_device

class sega8_castle_device : public sega8_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_castle_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
	virtual DECLARE_WRITE8_MEMBER(write_mapper) {}
=======
	sega8_castle_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override { }
>>>>>>> upstream/master
};


// ======================> sega8_basic_l3_device

class sega8_basic_l3_device : public sega8_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_basic_l3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
	virtual DECLARE_WRITE8_MEMBER(write_mapper) {}

	// has internal RAM which overwrites the system one!
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
=======
	sega8_basic_l3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override { }

	// has internal RAM which overwrites the system one!
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;
>>>>>>> upstream/master
};


// ======================> sega8_music_editor_device

class sega8_music_editor_device : public sega8_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_music_editor_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
	virtual DECLARE_WRITE8_MEMBER(write_mapper) {}

	// has internal RAM which overwrites the system one!
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
=======
	sega8_music_editor_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override { }

	// has internal RAM which overwrites the system one!
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;
>>>>>>> upstream/master
};


// ======================> sega8_terebi_device

class sega8_terebi_device : public sega8_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_terebi_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual ioport_constructor device_input_ports() const;
	virtual void device_reset();
=======
	sega8_terebi_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual ioport_constructor device_input_ports() const override;
>>>>>>> upstream/master

	required_ioport m_tvdraw_x;
	required_ioport m_tvdraw_y;
	required_ioport m_tvdraw_pen;

	// reading and writing
<<<<<<< HEAD
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
	virtual DECLARE_WRITE8_MEMBER(write_mapper) {}

protected:
	UINT8 m_tvdraw_data;
=======
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override { }

protected:
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_tvdraw_data;
>>>>>>> upstream/master
};


// ======================> sega8_dahjee_typea_device

class sega8_dahjee_typea_device : public sega8_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_dahjee_typea_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
	virtual DECLARE_WRITE8_MEMBER(write_mapper) {}

	// has internal RAM which overwrites the system one!
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
=======
	sega8_dahjee_typea_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override { }

	// has internal RAM which overwrites the system one!
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;
>>>>>>> upstream/master
};


// ======================> sega8_dahjee_typeb_device

class sega8_dahjee_typeb_device : public sega8_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_dahjee_typeb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart) {}
	virtual DECLARE_WRITE8_MEMBER(write_mapper) {}

	// has internal RAM which overwrites the system one!
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
=======
	sega8_dahjee_typeb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override { }
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override { }

	// has internal RAM which overwrites the system one!
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;
>>>>>>> upstream/master
};




// ======================> sega8_eeprom_device

class sega8_eeprom_device : public device_t,
							public device_sega8_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_eeprom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_reset();

	virtual void late_bank_setup();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
	virtual DECLARE_WRITE8_MEMBER(write_mapper);

protected:
	UINT8 m_rom_bank_base[3];

	required_device<eeprom_serial_93cxx_device> m_eeprom;
	int m_93c46_enabled;
	UINT8 m_93c46_lines;
=======
	sega8_eeprom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void late_bank_setup() override;

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override;

protected:
	virtual void device_start() override;
	virtual void device_reset() override;

	// device-level overrides
	virtual void device_add_mconfig(machine_config &config) override;

	uint8_t m_rom_bank_base[3];

	required_device<eeprom_serial_93cxx_device> m_eeprom;
	int m_93c46_enabled;
	uint8_t m_93c46_lines;
>>>>>>> upstream/master
};


// ======================> sega8_codemasters_device

class sega8_codemasters_device : public device_t,
								public device_sega8_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_codemasters_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void late_bank_setup();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
	// no mapper write for this!

protected:
	UINT8 m_rom_bank_base[3];
	UINT8 m_ram_base;
=======
	sega8_codemasters_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void late_bank_setup() override;

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
	// no mapper write for this!

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_rom_bank_base[3];
	uint8_t m_ram_base;
>>>>>>> upstream/master
	int m_ram_enabled;
};


// ======================> sega8_4pak_device

class sega8_4pak_device : public sega8_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_4pak_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);

private:
	UINT8 m_reg[3];
=======
	sega8_4pak_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t m_reg[3];
>>>>>>> upstream/master
};


// ======================> sega8_zemina_device

class sega8_zemina_device : public device_t,
							public device_sega8_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_zemina_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	sega8_zemina_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void late_bank_setup();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
	// no mapper write for this!

protected:
	UINT8 m_rom_bank_base[6];
	UINT8 m_ram_base;
=======
	sega8_zemina_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void late_bank_setup() override;

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
	// no mapper write for this!

protected:
	sega8_zemina_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_rom_bank_base[6];
	uint8_t m_ram_base;
>>>>>>> upstream/master
	int m_ram_enabled;
};


// ======================> sega8_nemesis_device

class sega8_nemesis_device : public sega8_zemina_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_nemesis_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual void late_bank_setup();
=======
	sega8_nemesis_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void late_bank_setup() override;
>>>>>>> upstream/master
};


// ======================> sega8_janggun_device

class sega8_janggun_device : public device_t,
							public device_sega8_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_janggun_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() { save_item(NAME(m_rom_bank_base)); }

	virtual void late_bank_setup();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
	virtual DECLARE_WRITE8_MEMBER(write_mapper);

protected:
	UINT8 m_rom_bank_base[6];
=======
	sega8_janggun_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void late_bank_setup() override;

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override;

protected:
	// device-level overrides
	virtual void device_start() override { save_item(NAME(m_rom_bank_base)); }

	uint8_t m_rom_bank_base[6];
>>>>>>> upstream/master
};


// ======================> sega8_hicom_device

class sega8_hicom_device : public sega8_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_hicom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() { save_item(NAME(m_rom_bank_base)); }

	virtual void late_bank_setup();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart) {}
	virtual DECLARE_WRITE8_MEMBER(write_mapper);

protected:
	UINT8 m_rom_bank_base;
=======
	sega8_hicom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void late_bank_setup() override;

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override {}
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override;

protected:
	// device-level overrides
	virtual void device_start() override { save_item(NAME(m_rom_bank_base)); }

	uint8_t m_rom_bank_base;
>>>>>>> upstream/master
};


// ======================> sega8_korean_device

class sega8_korean_device : public sega8_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_korean_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual void late_bank_setup();

	// reading and writing
	virtual DECLARE_WRITE8_MEMBER(write_cart);
	virtual DECLARE_WRITE8_MEMBER(write_mapper) {}
=======
	sega8_korean_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void late_bank_setup() override;

	// reading and writing
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override {}
>>>>>>> upstream/master
};


// ======================> sega8_korean_nb_device

class sega8_korean_nb_device : public sega8_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega8_korean_nb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_WRITE8_MEMBER(write_mapper) {}
};



// device type definition
extern const device_type SEGA8_ROM_STD;
extern const device_type SEGA8_ROM_OTHELLO;
extern const device_type SEGA8_ROM_CASTLE;
extern const device_type SEGA8_ROM_BASIC_L3;
extern const device_type SEGA8_ROM_MUSIC_EDITOR;
extern const device_type SEGA8_ROM_DAHJEE_TYPEA;
extern const device_type SEGA8_ROM_DAHJEE_TYPEB;
extern const device_type SEGA8_ROM_EEPROM;
extern const device_type SEGA8_ROM_TEREBI;
extern const device_type SEGA8_ROM_CODEMASTERS;
extern const device_type SEGA8_ROM_4PAK;
extern const device_type SEGA8_ROM_ZEMINA;
extern const device_type SEGA8_ROM_NEMESIS;
extern const device_type SEGA8_ROM_JANGGUN;
extern const device_type SEGA8_ROM_HICOM;
extern const device_type SEGA8_ROM_KOREAN;
extern const device_type SEGA8_ROM_KOREAN_NB;

#endif
=======
	sega8_korean_nb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override {}
};


// ======================> sega8_seojin_device

class sega8_seojin_device : public sega8_rom_device
{
public:
	// construction/destruction
	sega8_seojin_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_gamesel;
	uint8_t m_readxor;
};


// device type definition
DECLARE_DEVICE_TYPE(SEGA8_ROM_STD,          sega8_rom_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_OTHELLO,      sega8_othello_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_CASTLE,       sega8_castle_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_BASIC_L3,     sega8_basic_l3_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_MUSIC_EDITOR, sega8_music_editor_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_DAHJEE_TYPEA, sega8_dahjee_typea_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_DAHJEE_TYPEB, sega8_dahjee_typeb_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_EEPROM,       sega8_eeprom_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_TEREBI,       sega8_terebi_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_CODEMASTERS,  sega8_codemasters_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_4PAK,         sega8_4pak_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_ZEMINA,       sega8_zemina_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_NEMESIS,      sega8_nemesis_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_JANGGUN,      sega8_janggun_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_HICOM,        sega8_hicom_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_KOREAN,       sega8_korean_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_KOREAN_NB,    sega8_korean_nb_device)
DECLARE_DEVICE_TYPE(SEGA8_ROM_SEOJIN,       sega8_seojin_device)

#endif // MAME_BUS_SEGA8_ROM_H
>>>>>>> upstream/master
