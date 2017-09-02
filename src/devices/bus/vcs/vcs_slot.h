// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __VCS_SLOT_H
#define __VCS_SLOT_H
=======
#ifndef MAME_BUS_VCS_VCS_SLOT_H
#define MAME_BUS_VCS_VCS_SLOT_H

#pragma once

#include "softlist_dev.h"
>>>>>>> upstream/master


/***************************************************************************
 TYPE DEFINITIONS
 ***************************************************************************/


/* PCB */
enum
{
	A26_2K = 0,
	A26_4K,
	A26_F4,
	A26_F6,
	A26_F8,
	A26_F8SW,
	A26_FA,
	A26_FE,
	A26_3E,     // to test
	A26_3F,
	A26_E0,
	A26_E7,
	A26_UA,
	A26_DC,
	A26_CV,
	A26_FV,
	A26_JVP,    // to test
	A26_32IN1,
	A26_8IN1,
	A26_4IN1,
	A26_DPC,
	A26_SS,
	A26_CM,
	A26_X07,
	A26_HARMONY,
};


// ======================> device_vcs_cart_interface

class device_vcs_cart_interface : public device_slot_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	device_vcs_cart_interface(const machine_config &mconfig, device_t &device);
=======
>>>>>>> upstream/master
	virtual ~device_vcs_cart_interface();

	// reading from ROM
	virtual DECLARE_READ8_MEMBER(read_rom) { return 0xff; }
	// writing to RAM chips (sometimes it is in a different range than write_bank!)
<<<<<<< HEAD
	virtual DECLARE_WRITE8_MEMBER(write_ram) {}

	// read/write to bankswitch address
	virtual DECLARE_READ8_MEMBER(read_bank) { return 0xff; }
	virtual DECLARE_WRITE8_MEMBER(write_bank) {}

	// direct update handler
	virtual DECLARE_DIRECT_UPDATE_MEMBER(cart_opbase) { return address; }

	virtual void setup_addon_ptr(UINT8 *ptr) {}

	void rom_alloc(UINT32 size, const char *tag);
	void ram_alloc(UINT32 size);
	UINT8* get_rom_base() { return m_rom; }
	UINT8*  get_ram_base() { return &m_ram[0]; }
	UINT32  get_rom_size() { return m_rom_size; }
	UINT32  get_ram_size() { return m_ram.size(); }

protected:
	// internal state
	UINT8 *m_rom;
	UINT32 m_rom_size;
	dynamic_buffer m_ram;
=======
	virtual DECLARE_WRITE8_MEMBER(write_ram) { }

	// read/write to bankswitch address
	virtual DECLARE_READ8_MEMBER(read_bank) { return 0xff; }
	virtual DECLARE_WRITE8_MEMBER(write_bank) { }

	virtual void setup_addon_ptr(uint8_t *ptr) { }

	void rom_alloc(uint32_t size, const char *tag);
	void ram_alloc(uint32_t size);
	uint8_t* get_rom_base() { return m_rom; }
	uint8_t*  get_ram_base() { return &m_ram[0]; }
	uint32_t  get_rom_size() { return m_rom_size; }
	uint32_t  get_ram_size() { return m_ram.size(); }

protected:
	device_vcs_cart_interface(const machine_config &mconfig, device_t &device);

	// internal state
	uint8_t *m_rom;
	uint32_t m_rom_size;
	std::vector<uint8_t> m_ram;
>>>>>>> upstream/master
};


// ======================> vcs_cart_slot_device

class vcs_cart_slot_device : public device_t,
								public device_image_interface,
								public device_slot_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vcs_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ~vcs_cart_slot_device();

	// device-level overrides
	virtual void device_start();
	virtual void device_config_complete();

	// image-level overrides
	virtual bool call_load();
	virtual void call_unload();
	virtual bool call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry);

	int get_cart_type() { return m_type; };
	int identify_cart_type(UINT8 *ROM, UINT32 len);

	virtual iodevice_t image_type() const { return IO_CARTSLOT; }
	virtual bool is_readable()  const { return 1; }
	virtual bool is_writeable() const { return 0; }
	virtual bool is_creatable() const { return 0; }
	virtual bool must_be_loaded() const { return 1; }
	virtual bool is_reset_on_load() const { return 1; }
	virtual const option_guide *create_option_guide() const { return NULL; }
	virtual const char *image_interface() const { return "a2600_cart"; }
	virtual const char *file_extensions() const { return "bin,a26"; }

	// slot interface overrides
	virtual void get_default_card_software(std::string &result);
=======
	vcs_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual ~vcs_cart_slot_device();

	// image-level overrides
	virtual image_init_result call_load() override;
	virtual void call_unload() override;
	virtual const software_list_loader &get_software_list_loader() const override { return rom_software_list_loader::instance(); }

	int get_cart_type() { return m_type; };
	static int identify_cart_type(const uint8_t *ROM, uint32_t len);

	virtual iodevice_t image_type() const override { return IO_CARTSLOT; }
	virtual bool is_readable()  const override { return 1; }
	virtual bool is_writeable() const override { return 0; }
	virtual bool is_creatable() const override { return 0; }
	virtual bool must_be_loaded() const override { return 1; }
	virtual bool is_reset_on_load() const override { return 1; }
	virtual const char *image_interface() const override { return "a2600_cart"; }
	virtual const char *file_extensions() const override { return "bin,a26"; }

	// slot interface overrides
	virtual std::string get_default_card_software(get_default_card_software_hook &hook) const override;
>>>>>>> upstream/master

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_READ8_MEMBER(read_bank);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
<<<<<<< HEAD
	virtual DECLARE_DIRECT_UPDATE_MEMBER(cart_opbase);

private:
	device_vcs_cart_interface*       m_cart;
	int m_type;

	int detect_snowhite(UINT8 *cart, UINT32 len);
	int detect_modeDC(UINT8 *cart, UINT32 len);
	int detect_modeF6(UINT8 *cart, UINT32 len);
	int detect_mode3E(UINT8 *cart, UINT32 len);
	int detect_modeSS(UINT8 *cart, UINT32 len);
	int detect_modeFE(UINT8 *cart, UINT32 len);
	int detect_modeE0(UINT8 *cart, UINT32 len);
	int detect_modeCV(UINT8 *cart, UINT32 len);
	int detect_modeFV(UINT8 *cart, UINT32 len);
	int detect_modeJVP(UINT8 *cart, UINT32 len);
	int detect_modeE7(UINT8 *cart, UINT32 len);
	int detect_modeUA(UINT8 *cart, UINT32 len);
	int detect_8K_mode3F(UINT8 *cart, UINT32 len);
	int detect_32K_mode3F(UINT8 *cart, UINT32 len);
	int detect_super_chip(UINT8 *cart, UINT32 len);
=======

private:
	// device-level overrides
	virtual void device_start() override;

	device_vcs_cart_interface*       m_cart;
	int m_type;

	static bool detect_snowhite(const uint8_t *cart, uint32_t len);
	static bool detect_modeDC(const uint8_t *cart, uint32_t len);
	static bool detect_modeF6(const uint8_t *cart, uint32_t len);
	static bool detect_mode3E(const uint8_t *cart, uint32_t len);
	static bool detect_modeSS(const uint8_t *cart, uint32_t len);
	static bool detect_modeFE(const uint8_t *cart, uint32_t len);
	static bool detect_modeE0(const uint8_t *cart, uint32_t len);
	static bool detect_modeCV(const uint8_t *cart, uint32_t len);
	static bool detect_modeFV(const uint8_t *cart, uint32_t len);
	static bool detect_modeJVP(const uint8_t *cart, uint32_t len);
	static bool detect_modeE7(const uint8_t *cart, uint32_t len);
	static bool detect_modeUA(const uint8_t *cart, uint32_t len);
	static bool detect_8K_mode3F(const uint8_t *cart, uint32_t len);
	static bool detect_32K_mode3F(const uint8_t *cart, uint32_t len);
	static bool detect_super_chip(const uint8_t *cart, uint32_t len);
>>>>>>> upstream/master
};


// device type definition
extern const device_type VCS_CART_SLOT;


/***************************************************************************
 DEVICE CONFIGURATION MACROS
 ***************************************************************************/

#define A26SLOT_ROM_REGION_TAG ":cart:rom"


#define MCFG_VCS_CARTRIDGE_ADD(_tag,_slot_intf,_def_slot) \
	MCFG_DEVICE_ADD(_tag, VCS_CART_SLOT, 0)  \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, false)


<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_VCS_VCS_SLOT_H
>>>>>>> upstream/master
