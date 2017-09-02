// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __INTV_SLOT_H
#define __INTV_SLOT_H
=======
#ifndef MAME_BUS_INTV_SLOT_H
#define MAME_BUS_INTV_SLOT_H

#pragma once

#include "softlist_dev.h"

>>>>>>> upstream/master

/***************************************************************************
 TYPE DEFINITIONS
 ***************************************************************************/


/* PCB */
enum
{
	INTV_STD = 0,
	INTV_RAM,
	INTV_GFACT, // has RAM too but at diff offset
	INTV_WSMLB,
	INTV_VOICE,
	INTV_ECS,
	INTV_KEYCOMP
};


#define INTV_ROM16_READ(addr) \
<<<<<<< HEAD
	(UINT16) (m_rom[(addr) << 1] | (m_rom[((addr) << 1) + 1] << 8))
=======
	(uint16_t) (m_rom[(addr) << 1] | (m_rom[((addr) << 1) + 1] << 8))
>>>>>>> upstream/master


// ======================> device_intv_cart_interface

class device_intv_cart_interface : public device_slot_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	device_intv_cart_interface(const machine_config &mconfig, device_t &device);
=======
>>>>>>> upstream/master
	virtual ~device_intv_cart_interface();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read_rom04) { return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom20) { return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom40) { return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom48) { return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom50) { return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom60) { return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom70) { return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom80) { return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom90) { return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_roma0) { return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_romb0) { return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_romc0) { return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_romd0) { return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rome0) { return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_romf0) { return 0xffff; }

	virtual DECLARE_READ16_MEMBER(read_ram) { return 0xffff; }
	virtual DECLARE_WRITE16_MEMBER(write_ram) {}

	// Used by IntelliVoice & ECS
	virtual DECLARE_READ16_MEMBER(read_ay) { return 0xffff; }
	virtual DECLARE_WRITE16_MEMBER(write_ay) {}
	virtual DECLARE_READ16_MEMBER(read_speech) { return 0xffff; }
	virtual DECLARE_WRITE16_MEMBER(write_speech) {}
	virtual DECLARE_WRITE16_MEMBER(write_d0) {}
	virtual DECLARE_WRITE16_MEMBER(write_88) {}
	virtual DECLARE_WRITE16_MEMBER(write_rom20) {}
	virtual DECLARE_WRITE16_MEMBER(write_rom70) {}
	virtual DECLARE_WRITE16_MEMBER(write_rome0) {}
	virtual DECLARE_WRITE16_MEMBER(write_romf0) {}

<<<<<<< HEAD
	void rom_alloc(UINT32 size, const char *tag);
	void ram_alloc(UINT32 size);
	UINT8* get_rom_base() { return m_rom; }
	UINT8* get_ram_base() { return &m_ram[0]; }
	UINT32 get_rom_size() { return m_rom_size; }
	UINT32 get_ram_size() { return m_ram.size(); }
=======
	void rom_alloc(uint32_t size, const char *tag);
	void ram_alloc(uint32_t size);
	uint8_t* get_rom_base() { return m_rom; }
	uint8_t* get_ram_base() { return &m_ram[0]; }
	uint32_t get_rom_size() { return m_rom_size; }
	uint32_t get_ram_size() { return m_ram.size(); }
>>>>>>> upstream/master

	void save_ram() { device().save_item(NAME(m_ram)); }
	virtual void late_subslot_setup() {}

protected:
<<<<<<< HEAD
	// internal state
	UINT8 *m_rom;
	UINT32 m_rom_size;
	dynamic_buffer m_ram;
=======
	device_intv_cart_interface(const machine_config &mconfig, device_t &device);

	// internal state
	uint8_t *m_rom;
	uint32_t m_rom_size;
	std::vector<uint8_t> m_ram;
>>>>>>> upstream/master
};


// ======================> intv_cart_slot_device

class intv_cart_slot_device : public device_t,
								public device_image_interface,
								public device_slot_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	intv_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ~intv_cart_slot_device();

	// device-level overrides
	virtual void device_start();
	virtual void device_config_complete();

	// image-level overrides
	virtual bool call_load();
	virtual void call_unload() {}
	virtual bool call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry);

	int get_type() { return m_type; }
	int load_fullpath();

	void save_ram() { if (m_cart && m_cart->get_ram_size()) m_cart->save_ram(); }

	virtual iodevice_t image_type() const { return IO_CARTSLOT; }
	virtual bool is_readable()  const { return 1; }
	virtual bool is_writeable() const { return 0; }
	virtual bool is_creatable() const { return 0; }
	virtual bool must_be_loaded() const { return 0; }
	virtual bool is_reset_on_load() const { return 1; }
	virtual const option_guide *create_option_guide() const { return NULL; }
	virtual const char *image_interface() const { return "intv_cart"; }
	virtual const char *file_extensions() const { return "bin,int,rom,itv"; }

	// slot interface overrides
	virtual void get_default_card_software(std::string &result);
=======
	intv_cart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual ~intv_cart_slot_device();

	// image-level overrides
	virtual image_init_result call_load() override;
	virtual void call_unload() override {}
	virtual const software_list_loader &get_software_list_loader() const override { return rom_software_list_loader::instance(); }

	int get_type() { return m_type; }
	image_init_result load_fullpath();

	void save_ram() { if (m_cart && m_cart->get_ram_size()) m_cart->save_ram(); }

	virtual iodevice_t image_type() const override { return IO_CARTSLOT; }
	virtual bool is_readable()  const override { return 1; }
	virtual bool is_writeable() const override { return 0; }
	virtual bool is_creatable() const override { return 0; }
	virtual bool must_be_loaded() const override { return 0; }
	virtual bool is_reset_on_load() const override { return 1; }
	virtual const char *image_interface() const override { return "intv_cart"; }
	virtual const char *file_extensions() const override { return "bin,int,rom,itv"; }

	// slot interface overrides
	virtual std::string get_default_card_software(get_default_card_software_hook &hook) const override;
>>>>>>> upstream/master

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read_rom04) { if (m_cart) return m_cart->read_rom04(space, offset, mem_mask); else return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom20) { if (m_cart) return m_cart->read_rom20(space, offset, mem_mask); else return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom40) { if (m_cart) return m_cart->read_rom40(space, offset, mem_mask); else return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom48) { if (m_cart) return m_cart->read_rom48(space, offset, mem_mask); else return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom50) { if (m_cart) return m_cart->read_rom50(space, offset, mem_mask); else return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom60) { if (m_cart) return m_cart->read_rom60(space, offset, mem_mask); else return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom70) { if (m_cart) return m_cart->read_rom70(space, offset, mem_mask); else return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom80) { if (m_cart) return m_cart->read_rom80(space, offset, mem_mask); else return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rom90) { if (m_cart) return m_cart->read_rom90(space, offset, mem_mask); else return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_roma0) { if (m_cart) return m_cart->read_roma0(space, offset, mem_mask); else return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_romb0) { if (m_cart) return m_cart->read_romb0(space, offset, mem_mask); else return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_romc0) { if (m_cart) return m_cart->read_romc0(space, offset, mem_mask); else return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_romd0) { if (m_cart) return m_cart->read_romd0(space, offset, mem_mask); else return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_rome0) { if (m_cart) return m_cart->read_rome0(space, offset, mem_mask); else return 0xffff; }
	virtual DECLARE_READ16_MEMBER(read_romf0) { if (m_cart) return m_cart->read_romf0(space, offset, mem_mask); else return 0xffff; }

	virtual DECLARE_READ16_MEMBER(read_ay);
	virtual DECLARE_WRITE16_MEMBER(write_ay);
	virtual DECLARE_READ16_MEMBER(read_speech);
	virtual DECLARE_WRITE16_MEMBER(write_speech);
	virtual DECLARE_READ16_MEMBER(read_ram) { if (m_cart) return m_cart->read_ram(space, offset, mem_mask); else return 0xffff; }
	virtual DECLARE_WRITE16_MEMBER(write_ram) { if (m_cart) m_cart->write_ram(space, offset, data, mem_mask); }

	virtual void late_subslot_setup() { if (m_cart) return m_cart->late_subslot_setup(); }

	// these RAM accessors are needed to deal with IntelliVoice and ECS mounting RAM-equipped carts
	virtual DECLARE_WRITE16_MEMBER(write_d0) { if (m_cart) m_cart->write_d0(space, offset, data, mem_mask); }
	virtual DECLARE_WRITE16_MEMBER(write_88) { if (m_cart) m_cart->write_88(space, offset, data, mem_mask); }

	// ECS paged roms need these
	virtual DECLARE_WRITE16_MEMBER(write_rom20) { if (m_cart) m_cart->write_rom20(space, offset, data, mem_mask); }
	virtual DECLARE_WRITE16_MEMBER(write_rom70) { if (m_cart) m_cart->write_rom70(space, offset, data, mem_mask); }
	virtual DECLARE_WRITE16_MEMBER(write_rome0) { if (m_cart) m_cart->write_rome0(space, offset, data, mem_mask); }
	virtual DECLARE_WRITE16_MEMBER(write_romf0) { if (m_cart) m_cart->write_romf0(space, offset, data, mem_mask); }

<<<<<<< HEAD
//protected:
=======
protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master

	int m_type;
	device_intv_cart_interface*       m_cart;
};



// device type definition
<<<<<<< HEAD
extern const device_type INTV_CART_SLOT;
=======
DECLARE_DEVICE_TYPE(INTV_CART_SLOT, intv_cart_slot_device)
>>>>>>> upstream/master


/***************************************************************************
 DEVICE CONFIGURATION MACROS
 ***************************************************************************/

#define INTVSLOT_ROM_REGION_TAG ":cart:rom"

#define MCFG_INTV_CARTRIDGE_ADD(_tag,_slot_intf,_def_slot) \
	MCFG_DEVICE_ADD(_tag, INTV_CART_SLOT, 0) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, false)

SLOT_INTERFACE_EXTERN(intv_cart);

<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_INTV_SLOT_H
>>>>>>> upstream/master
