// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __O2_SLOT_H
#define __O2_SLOT_H
=======
#ifndef MAME_BUS_ODYSSEY2_SLOT_H
#define MAME_BUS_ODYSSEY2_SLOT_H

#pragma once

#include "softlist_dev.h"

>>>>>>> upstream/master

/***************************************************************************
 TYPE DEFINITIONS
 ***************************************************************************/


/* PCB */
enum
{
	O2_STD = 0,
	O2_ROM12,
	O2_ROM16,
	O2_CHESS,
	O2_VOICE
};


// ======================> device_o2_cart_interface

class device_o2_cart_interface : public device_slot_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	device_o2_cart_interface(const machine_config &mconfig, device_t &device);
=======
>>>>>>> upstream/master
	virtual ~device_o2_cart_interface();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom04) { return 0xff; }
	virtual DECLARE_READ8_MEMBER(read_rom0c) { return 0xff; }
<<<<<<< HEAD
	virtual void write_bank(int bank) {}

	virtual DECLARE_WRITE8_MEMBER(io_write) {}
	virtual DECLARE_READ8_MEMBER(t0_read) { return 0; }

	void rom_alloc(UINT32 size, const char *tag);
	void ram_alloc(UINT32 size);
	UINT8* get_rom_base() { return m_rom; }
	UINT8* get_ram_base() { return &m_ram[0]; }
	UINT32 get_rom_size() { return m_rom_size; }
	UINT32 get_ram_size() { return m_ram.size(); }

protected:
	// internal state
	UINT8 *m_rom;
	UINT32 m_rom_size;
	dynamic_buffer m_ram;
=======
	virtual void write_bank(int bank) { }

	virtual DECLARE_WRITE8_MEMBER(io_write) { }
	virtual DECLARE_READ_LINE_MEMBER(t0_read) { return 0; }

	void rom_alloc(uint32_t size, const char *tag);
	void ram_alloc(uint32_t size);
	uint8_t* get_rom_base() { return m_rom; }
	uint8_t* get_ram_base() { return &m_ram[0]; }
	uint32_t get_rom_size() { return m_rom_size; }
	uint32_t get_ram_size() { return m_ram.size(); }

protected:
	device_o2_cart_interface(const machine_config &mconfig, device_t &device);

	// internal state
	uint8_t *m_rom;
	uint32_t m_rom_size;
	std::vector<uint8_t> m_ram;
>>>>>>> upstream/master
};


// ======================> o2_cart_slot_device

class o2_cart_slot_device : public device_t,
								public device_image_interface,
								public device_slot_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	o2_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ~o2_cart_slot_device();

	// device-level overrides
	virtual void device_start();
	virtual void device_config_complete();

	// image-level overrides
	virtual bool call_load();
	virtual void call_unload() {}
	virtual bool call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry);

	int get_type() { return m_type; }

	virtual iodevice_t image_type() const { return IO_CARTSLOT; }
	virtual bool is_readable()  const { return 1; }
	virtual bool is_writeable() const { return 0; }
	virtual bool is_creatable() const { return 0; }
	virtual bool must_be_loaded() const { return 0; }
	virtual bool is_reset_on_load() const { return 1; }
	virtual const option_guide *create_option_guide() const { return NULL; }
	virtual const char *image_interface() const { return "odyssey_cart"; }
	virtual const char *file_extensions() const { return "bin,rom"; }

	// slot interface overrides
	virtual void get_default_card_software(std::string &result);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom04);
	virtual DECLARE_READ8_MEMBER(read_rom0c);
	virtual DECLARE_WRITE8_MEMBER(io_write);
	virtual DECLARE_READ8_MEMBER(t0_read) { if (m_cart) return m_cart->t0_read(space, offset); else return 0; }

	virtual void write_bank(int bank)   { if (m_cart) m_cart->write_bank(bank); }
=======
	o2_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual ~o2_cart_slot_device();

	// device-level overrides
	virtual void device_start() override;

	// image-level overrides
	virtual image_init_result call_load() override;
	virtual void call_unload() override { }
	virtual const software_list_loader &get_software_list_loader() const override { return rom_software_list_loader::instance(); }

	int get_type() { return m_type; }

	virtual iodevice_t image_type() const override { return IO_CARTSLOT; }
	virtual bool is_readable()  const override { return 1; }
	virtual bool is_writeable() const override { return 0; }
	virtual bool is_creatable() const override { return 0; }
	virtual bool must_be_loaded() const override { return 0; }
	virtual bool is_reset_on_load() const override { return 1; }
	virtual const char *image_interface() const override { return "odyssey_cart"; }
	virtual const char *file_extensions() const override { return "bin,rom"; }

	// slot interface overrides
	virtual std::string get_default_card_software(get_default_card_software_hook &hook) const override;

	// reading and writing
	DECLARE_READ8_MEMBER(read_rom04);
	DECLARE_READ8_MEMBER(read_rom0c);
	DECLARE_WRITE8_MEMBER(io_write);
	DECLARE_READ_LINE_MEMBER(t0_read) { if (m_cart) return m_cart->t0_read(); else return 0; }

	void write_bank(int bank)   { if (m_cart) m_cart->write_bank(bank); }
>>>>>>> upstream/master

protected:

	int m_type;
<<<<<<< HEAD
	device_o2_cart_interface*       m_cart;
};



// device type definition
extern const device_type O2_CART_SLOT;
=======
	device_o2_cart_interface* m_cart;
};

// device type definition
DECLARE_DEVICE_TYPE(O2_CART_SLOT, o2_cart_slot_device)
>>>>>>> upstream/master


/***************************************************************************
 DEVICE CONFIGURATION MACROS
 ***************************************************************************/

#define O2SLOT_ROM_REGION_TAG ":cart:rom"

#define MCFG_O2_CARTRIDGE_ADD(_tag,_slot_intf,_def_slot) \
	MCFG_DEVICE_ADD(_tag, O2_CART_SLOT, 0) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, false)

SLOT_INTERFACE_EXTERN(o2_cart);

<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_ODYSSEY2_SLOT_H
>>>>>>> upstream/master
