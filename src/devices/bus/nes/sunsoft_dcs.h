// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_SUNSOFT_DCS_H
#define __NES_SUNSOFT_DCS_H

#include "sunsoft.h"
=======
#ifndef MAME_BUS_NES_SUNSOFT_DCS_H
#define MAME_BUS_NES_SUNSOFT_DCS_H

#pragma once

#include "sunsoft.h"
#include "softlist_dev.h"
>>>>>>> upstream/master


//-----------------------------------------------
//
//  Nantettate!! Baseball Cartslot implementation
//
//-----------------------------------------------

// ======================> ntb_cart_interface

class ntb_cart_interface : public device_slot_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	ntb_cart_interface(const machine_config &mconfig, device_t &device);
=======
>>>>>>> upstream/master
	virtual ~ntb_cart_interface();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read) { return m_rom[offset]; }

<<<<<<< HEAD
	UINT8 *get_cart_base() { return m_rom; }

protected:
	// internal state
	UINT8 *m_rom;
=======
	uint8_t *get_cart_base() { return m_rom; }

protected:
	ntb_cart_interface(const machine_config &mconfig, device_t &device);

	// internal state
	uint8_t *m_rom;
>>>>>>> upstream/master
};

// ======================> nes_ntb_slot_device

<<<<<<< HEAD
=======
class nes_sunsoft_dcs_device;

>>>>>>> upstream/master
class nes_ntb_slot_device : public device_t,
								public device_image_interface,
								public device_slot_interface
{
<<<<<<< HEAD
public:
	// construction/destruction
	nes_ntb_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ~nes_ntb_slot_device();

	// device-level overrides
	virtual void device_start();
	virtual void device_config_complete() { update_names(); }

	// image-level overrides
	virtual bool call_load();
	virtual bool call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry);

	virtual iodevice_t image_type() const { return IO_CARTSLOT; }
	virtual bool is_readable()  const { return 1; }
	virtual bool is_writeable() const { return 0; }
	virtual bool is_creatable() const { return 0; }
	virtual bool must_be_loaded() const { return 0; }
	virtual bool is_reset_on_load() const { return 1; }
	virtual const char *image_interface() const { return "ntb_cart"; }
	virtual const char *file_extensions() const { return "bin"; }
	virtual const option_guide *create_option_guide() const { return NULL; }

	// slot interface overrides
	virtual void get_default_card_software(std::string &result);

	virtual DECLARE_READ8_MEMBER(read);

=======
	friend class nes_sunsoft_dcs_device;
public:
	// construction/destruction
	nes_ntb_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual ~nes_ntb_slot_device();

	// device-level overrides
	virtual void device_start() override;

	// image-level overrides
	virtual image_init_result call_load() override;
	virtual const software_list_loader &get_software_list_loader() const override { return rom_software_list_loader::instance(); }

	virtual iodevice_t image_type() const override { return IO_CARTSLOT; }
	virtual bool is_readable()  const override { return 1; }
	virtual bool is_writeable() const override { return 0; }
	virtual bool is_creatable() const override { return 0; }
	virtual bool must_be_loaded() const override { return 0; }
	virtual bool is_reset_on_load() const override { return 1; }
	virtual const char *image_interface() const override { return "ntb_cart"; }
	virtual const char *file_extensions() const override { return "bin"; }

	// slot interface overrides
	virtual std::string get_default_card_software(get_default_card_software_hook &hook) const override;

	virtual DECLARE_READ8_MEMBER(read);

protected:
>>>>>>> upstream/master
	ntb_cart_interface*      m_cart;
};

// device type definition
<<<<<<< HEAD
extern const device_type NES_NTB_SLOT;
=======
DECLARE_DEVICE_TYPE(NES_NTB_SLOT, nes_ntb_slot_device)
>>>>>>> upstream/master


#define MCFG_NTB_MINICART_ADD(_tag, _slot_intf) \
		MCFG_DEVICE_ADD(_tag, NES_NTB_SLOT, 0) \
<<<<<<< HEAD
		MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, NULL, false)
=======
		MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, nullptr, false)
>>>>>>> upstream/master


//-----------------------------------------------
//
//  Nantettate!! Baseball Minicart implementation
//
//-----------------------------------------------

// ======================> nes_ntb_rom_device

class nes_ntb_rom_device : public device_t,
							public ntb_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ntb_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual UINT8* get_cart_base();

protected:
	// device-level overrides
	virtual void device_start();
};

// device type definition
extern const device_type NES_NTB_ROM;
=======
	nes_ntb_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual uint8_t* get_cart_base();

protected:
	// device-level overrides
	virtual void device_start() override;
};

// device type definition
DECLARE_DEVICE_TYPE(NES_NTB_ROM, nes_ntb_rom_device)
>>>>>>> upstream/master



//------------------------------------------------
//
//  Nantettate!! Baseball base cart implementation
//  a.k.a. Sunsoft Dual Cassette System
//  (variant of Sunsoft-4 PCB)
//
//------------------------------------------------

// ======================> nes_sunsoft_dcs_device

class nes_sunsoft_dcs_device : public nes_sunsoft_4_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_sunsoft_dcs_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual DECLARE_READ8_MEMBER(read_m);
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_m);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	int m_timer_on, m_exrom_enable;
	required_device<nes_ntb_slot_device> m_subslot;

	static const device_timer_id TIMER_PROTECT = 0;
=======
	nes_sunsoft_dcs_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_m) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_m) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	virtual void device_add_mconfig(machine_config &config) override;

private:
	static constexpr device_timer_id TIMER_PROTECT = 0;

	int m_timer_on, m_exrom_enable;
	required_device<nes_ntb_slot_device> m_subslot;

>>>>>>> upstream/master
	emu_timer *ntb_enable_timer;
	attotime timer_freq;
};


<<<<<<< HEAD

// device type definition
extern const device_type NES_SUNSOFT_DCS;

#endif
=======
// device type definition
DECLARE_DEVICE_TYPE(NES_SUNSOFT_DCS, nes_sunsoft_dcs_device)

#endif // MAME_BUS_NES_SUNSOFT_DCS_H
>>>>>>> upstream/master
