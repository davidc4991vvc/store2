// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __SCV_SLOT_H
#define __SCV_SLOT_H
=======
#ifndef MAME_BUS_SCV_SLOT_H
#define MAME_BUS_SCV_SLOT_H

#pragma once

#include "softlist_dev.h"

>>>>>>> upstream/master

/***************************************************************************
 TYPE DEFINITIONS
 ***************************************************************************/


/* PCB */
enum
{
	SCV_8K = 0,
	SCV_16K,
	SCV_32K,
	SCV_32K_RAM,
	SCV_64K,
	SCV_128K,
	SCV_128K_RAM
};


// ======================> device_scv_cart_interface

class device_scv_cart_interface : public device_slot_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	device_scv_cart_interface(const machine_config &mconfig, device_t &device);
=======
>>>>>>> upstream/master
	virtual ~device_scv_cart_interface();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) { return 0xff; }
<<<<<<< HEAD
	virtual DECLARE_WRITE8_MEMBER(write_cart) {}
	virtual DECLARE_WRITE8_MEMBER(write_bank) {}

	void rom_alloc(UINT32 size, const char *tag);
	void ram_alloc(UINT32 size);
	UINT8* get_rom_base() { return m_rom; }
	UINT8* get_ram_base() { return &m_ram[0]; }
	UINT32 get_rom_size() { return m_rom_size; }
	UINT32 get_ram_size() { return m_ram.size(); }
=======
	virtual DECLARE_WRITE8_MEMBER(write_cart) { }
	virtual DECLARE_WRITE8_MEMBER(write_bank) { }

	void rom_alloc(uint32_t size, const char *tag);
	void ram_alloc(uint32_t size);
	uint8_t* get_rom_base() { return m_rom; }
	uint8_t* get_ram_base() { return &m_ram[0]; }
	uint32_t get_rom_size() { return m_rom_size; }
	uint32_t get_ram_size() { return m_ram.size(); }
>>>>>>> upstream/master

	void save_ram() { device().save_item(NAME(m_ram)); }

protected:
<<<<<<< HEAD
	// internal state
	UINT8 *m_rom;
	UINT32 m_rom_size;
	dynamic_buffer m_ram;
=======
	device_scv_cart_interface(const machine_config &mconfig, device_t &device);

	// internal state
	uint8_t *m_rom;
	uint32_t m_rom_size;
	std::vector<uint8_t> m_ram;
>>>>>>> upstream/master
};


// ======================> scv_cart_slot_device

class scv_cart_slot_device : public device_t,
								public device_image_interface,
								public device_slot_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	scv_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ~scv_cart_slot_device();

	// device-level overrides
	virtual void device_start();
	virtual void device_config_complete();

	// image-level overrides
	virtual bool call_load();
	virtual void call_unload() {}
	virtual bool call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry);

	int get_type() { return m_type; }
	int get_cart_type(UINT8 *ROM, UINT32 len);

	void save_ram() { if (m_cart && m_cart->get_ram_size()) m_cart->save_ram(); }

	virtual iodevice_t image_type() const { return IO_CARTSLOT; }
	virtual bool is_readable()  const { return 1; }
	virtual bool is_writeable() const { return 0; }
	virtual bool is_creatable() const { return 0; }
	virtual bool must_be_loaded() const { return 0; }
	virtual bool is_reset_on_load() const { return 1; }
	virtual const option_guide *create_option_guide() const { return NULL; }
	virtual const char *image_interface() const { return "scv_cart"; }
	virtual const char *file_extensions() const { return "bin"; }

	// slot interface overrides
	virtual void get_default_card_software(std::string &result);
=======
	scv_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual ~scv_cart_slot_device();

	// image-level overrides
	virtual image_init_result call_load() override;
	virtual void call_unload() override {}
	virtual const software_list_loader &get_software_list_loader() const override { return rom_software_list_loader::instance(); }

	int get_type() { return m_type; }
	static int get_cart_type(const uint8_t *ROM, uint32_t len);

	void save_ram() { if (m_cart && m_cart->get_ram_size()) m_cart->save_ram(); }

	virtual iodevice_t image_type() const override { return IO_CARTSLOT; }
	virtual bool is_readable()  const override { return 1; }
	virtual bool is_writeable() const override { return 0; }
	virtual bool is_creatable() const override { return 0; }
	virtual bool must_be_loaded() const override { return 0; }
	virtual bool is_reset_on_load() const override { return 1; }
	virtual const char *image_interface() const override { return "scv_cart"; }
	virtual const char *file_extensions() const override { return "bin"; }

	// slot interface overrides
	virtual std::string get_default_card_software(get_default_card_software_hook &hook) const override;
>>>>>>> upstream/master

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
	virtual DECLARE_WRITE8_MEMBER(write_bank);

protected:
<<<<<<< HEAD
=======
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master

	int m_type;
	device_scv_cart_interface*       m_cart;
};



// device type definition
<<<<<<< HEAD
extern const device_type SCV_CART_SLOT;
=======
DECLARE_DEVICE_TYPE(SCV_CART_SLOT, scv_cart_slot_device)
>>>>>>> upstream/master


/***************************************************************************
 DEVICE CONFIGURATION MACROS
 ***************************************************************************/

#define SCVSLOT_ROM_REGION_TAG ":cart:rom"

#define MCFG_SCV_CARTRIDGE_ADD(_tag,_slot_intf,_def_slot) \
	MCFG_DEVICE_ADD(_tag, SCV_CART_SLOT, 0) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, false)
<<<<<<< HEAD
#endif
=======

#endif // MAME_BUS_SCV_SLOT_H
>>>>>>> upstream/master
