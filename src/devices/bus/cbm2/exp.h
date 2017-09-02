// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore CBM-II Expansion Port emulation

**********************************************************************

                     A0       1      A       BD0
                     A1       2      B       BD1
                     A2       3      C       BD2
                     A3       4      D       BD3
                     A4       5      E       BD4
                     A5       6      F       BD5
                     A6       7      H       BD6
                     A7       8      J       BD7
                     A8       9      K       GND
                     A9      10      L       GND
                    A10      11      M       SR/_W
                    A11      12      N       Sphi2
                    A12      13      P       _CSBANK1
                    +5V      14      R       _CSBANK2
                    +5V      15      S       _CSBANK2

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __CBM2_EXPANSION_SLOT__
#define __CBM2_EXPANSION_SLOT__

#include "emu.h"
=======
#ifndef MAME_BUS_CBM2_EXP_H
#define MAME_BUS_CBM2_EXP_H

#pragma once

#include "softlist_dev.h"
>>>>>>> upstream/master



//**************************************************************************
//  CONSTANTS
//**************************************************************************

#define CBM2_EXPANSION_SLOT_TAG     "exp"



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_CBM2_EXPANSION_SLOT_ADD(_tag, _clock, _slot_intf, _def_slot) \
	MCFG_DEVICE_ADD(_tag, CBM2_EXPANSION_SLOT, _clock) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, false)



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> cbm2_expansion_slot_device

class device_cbm2_expansion_card_interface;

class cbm2_expansion_slot_device : public device_t,
									public device_slot_interface,
									public device_image_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	cbm2_expansion_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// computer interface
	UINT8 read(address_space &space, offs_t offset, UINT8 data, int csbank1, int csbank2, int csbank3);
	void write(address_space &space, offs_t offset, UINT8 data, int csbank1, int csbank2, int csbank3);
=======
	cbm2_expansion_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// computer interface
	uint8_t read(address_space &space, offs_t offset, uint8_t data, int csbank1, int csbank2, int csbank3);
	void write(address_space &space, offs_t offset, uint8_t data, int csbank1, int csbank2, int csbank3);
>>>>>>> upstream/master

	// cartridge interface
	int phi2() { return clock(); }

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_config_complete() { update_names(); }
	virtual void device_start();
	virtual void device_reset();

	// image-level overrides
	virtual bool call_load();
	virtual bool call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry);

	virtual iodevice_t image_type() const { return IO_CARTSLOT; }

	virtual bool is_readable()  const { return 1; }
	virtual bool is_writeable() const { return 0; }
	virtual bool is_creatable() const { return 0; }
	virtual bool must_be_loaded() const { return 0; }
	virtual bool is_reset_on_load() const { return 1; }
	virtual const char *image_interface() const { return "cbm2_cart"; }
	virtual const char *file_extensions() const { return "20,40,60"; }
	virtual const option_guide *create_option_guide() const { return NULL; }

	// slot interface overrides
	virtual void get_default_card_software(std::string &result);
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	// image-level overrides
	virtual image_init_result call_load() override;
	virtual const software_list_loader &get_software_list_loader() const override { return rom_software_list_loader::instance(); }

	virtual iodevice_t image_type() const override { return IO_CARTSLOT; }

	virtual bool is_readable()  const override { return 1; }
	virtual bool is_writeable() const override { return 0; }
	virtual bool is_creatable() const override { return 0; }
	virtual bool must_be_loaded() const override { return 0; }
	virtual bool is_reset_on_load() const override { return 1; }
	virtual const char *image_interface() const override { return "cbm2_cart"; }
	virtual const char *file_extensions() const override { return "20,40,60"; }

	// slot interface overrides
	virtual std::string get_default_card_software(get_default_card_software_hook &hook) const override;
>>>>>>> upstream/master

	device_cbm2_expansion_card_interface *m_card;
};


// ======================> device_cbm2_expansion_card_interface

class device_cbm2_expansion_card_interface : public device_slot_card_interface
{
	friend class cbm2_expansion_slot_device;

public:
	// construction/destruction
<<<<<<< HEAD
	device_cbm2_expansion_card_interface(const machine_config &mconfig, device_t &device);
	virtual ~device_cbm2_expansion_card_interface();

	virtual UINT8 cbm2_bd_r(address_space &space, offs_t offset, UINT8 data, int csbank1, int csbank2, int csbank3) { return data; };
	virtual void cbm2_bd_w(address_space &space, offs_t offset, UINT8 data, int csbank1, int csbank2, int csbank3) { };

protected:
	optional_shared_ptr<UINT8> m_bank1;
	optional_shared_ptr<UINT8> m_bank2;
	optional_shared_ptr<UINT8> m_bank3;
=======
	virtual ~device_cbm2_expansion_card_interface();

	virtual uint8_t cbm2_bd_r(address_space &space, offs_t offset, uint8_t data, int csbank1, int csbank2, int csbank3) { return data; };
	virtual void cbm2_bd_w(address_space &space, offs_t offset, uint8_t data, int csbank1, int csbank2, int csbank3) { };

protected:
	device_cbm2_expansion_card_interface(const machine_config &mconfig, device_t &device);

	optional_shared_ptr<uint8_t> m_bank1;
	optional_shared_ptr<uint8_t> m_bank2;
	optional_shared_ptr<uint8_t> m_bank3;
>>>>>>> upstream/master

	cbm2_expansion_slot_device *m_slot;
};


// device type definition
<<<<<<< HEAD
extern const device_type CBM2_EXPANSION_SLOT;
=======
DECLARE_DEVICE_TYPE(CBM2_EXPANSION_SLOT, cbm2_expansion_slot_device)
>>>>>>> upstream/master


SLOT_INTERFACE_EXTERN( cbm2_expansion_cards );


<<<<<<< HEAD

#endif
=======
#endif // MAME_BUS_CBM2_EXP_H
>>>>>>> upstream/master
