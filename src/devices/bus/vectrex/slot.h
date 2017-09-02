// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __VECTREX_SLOT_H
#define __VECTREX_SLOT_H
=======
#ifndef MAME_BUS_VECTREX_SLOT_H
#define MAME_BUS_VECTREX_SLOT_H

#pragma once

#include "softlist_dev.h"

>>>>>>> upstream/master

/***************************************************************************
 TYPE DEFINITIONS
 ***************************************************************************/


/* PCB */
enum
{
	VECTREX_STD = 0,
	VECTREX_64K,
	VECTREX_SRAM
};

// 3D setup
enum
{
	VEC3D_NONE = 0,
	VEC3D_MINEST,
	VEC3D_CCOAST,
	VEC3D_NARROW
};

// ======================> device_vectrex_cart_interface

class device_vectrex_cart_interface : public device_slot_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	device_vectrex_cart_interface(const machine_config &mconfig, device_t &device);
=======
>>>>>>> upstream/master
	virtual ~device_vectrex_cart_interface();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) { return 0xff; }
<<<<<<< HEAD
	virtual DECLARE_WRITE8_MEMBER(write_ram) {}
	virtual DECLARE_WRITE8_MEMBER(write_bank) {}

	void rom_alloc(UINT32 size, const char *tag);
	UINT8* get_rom_base() { return m_rom; }
	UINT32 get_rom_size() { return m_rom_size; }

protected:
	// internal state
	UINT8 *m_rom;
	UINT32 m_rom_size;
=======
	virtual DECLARE_WRITE8_MEMBER(write_ram) { }
	virtual DECLARE_WRITE8_MEMBER(write_bank) { }

	void rom_alloc(uint32_t size, const char *tag);
	uint8_t* get_rom_base() { return m_rom; }
	uint32_t get_rom_size() { return m_rom_size; }

protected:
	device_vectrex_cart_interface(const machine_config &mconfig, device_t &device);

	// internal state
	uint8_t *m_rom;
	uint32_t m_rom_size;
>>>>>>> upstream/master
};


// ======================> vectrex_cart_slot_device

class vectrex_cart_slot_device : public device_t,
								public device_image_interface,
								public device_slot_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vectrex_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ~vectrex_cart_slot_device();

	// device-level overrides
	virtual void device_start();
	virtual void device_config_complete();

	// image-level overrides
	virtual bool call_load();
	virtual void call_unload() {}
	virtual bool call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry);
=======
	vectrex_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual ~vectrex_cart_slot_device();

	// image-level overrides
	virtual image_init_result call_load() override;
	virtual void call_unload() override { }
	virtual const software_list_loader &get_software_list_loader() const override { return rom_software_list_loader::instance(); }
>>>>>>> upstream/master

	int get_type() { return m_type; }
	int get_vec3d() { return m_vec3d; }

<<<<<<< HEAD
	virtual iodevice_t image_type() const { return IO_CARTSLOT; }
	virtual bool is_readable()  const { return 1; }
	virtual bool is_writeable() const { return 0; }
	virtual bool is_creatable() const { return 0; }
	virtual bool must_be_loaded() const { return 0; }
	virtual bool is_reset_on_load() const { return 1; }
	virtual const option_guide *create_option_guide() const { return NULL; }
	virtual const char *image_interface() const { return "vectrex_cart"; }
	virtual const char *file_extensions() const { return "bin,gam,vec"; }

	// slot interface overrides
	virtual void get_default_card_software(std::string &result);
=======
	virtual iodevice_t image_type() const override { return IO_CARTSLOT; }
	virtual bool is_readable()  const override { return 1; }
	virtual bool is_writeable() const override { return 0; }
	virtual bool is_creatable() const override { return 0; }
	virtual bool must_be_loaded() const override { return 0; }
	virtual bool is_reset_on_load() const override { return 1; }
	virtual const char *image_interface() const override { return "vectrex_cart"; }
	virtual const char *file_extensions() const override { return "bin,gam,vec"; }

	// slot interface overrides
	virtual std::string get_default_card_software(get_default_card_software_hook &hook) const override;
>>>>>>> upstream/master

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
	virtual DECLARE_WRITE8_MEMBER(write_bank);

protected:
<<<<<<< HEAD
=======
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master

	int m_type, m_vec3d;
	device_vectrex_cart_interface*       m_cart;
};



// device type definition
<<<<<<< HEAD
extern const device_type VECTREX_CART_SLOT;
=======
DECLARE_DEVICE_TYPE(VECTREX_CART_SLOT, vectrex_cart_slot_device)
>>>>>>> upstream/master


/***************************************************************************
 DEVICE CONFIGURATION MACROS
 ***************************************************************************/

#define VECSLOT_ROM_REGION_TAG ":cart:rom"

#define MCFG_VECTREX_CARTRIDGE_ADD(_tag,_slot_intf,_def_slot) \
	MCFG_DEVICE_ADD(_tag, VECTREX_CART_SLOT, 0) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, false)
<<<<<<< HEAD
#endif
=======

#endif // MAME_BUS_VECTREX_SLOT_H
>>>>>>> upstream/master
