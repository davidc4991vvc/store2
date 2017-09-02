// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    XL 80 cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __XL80__
#define __XL80__


#include "emu.h"
=======
#ifndef MAME_BUS_C64_XL80_H
#define MAME_BUS_C64_XL80_H

#pragma once


>>>>>>> upstream/master
#include "exp.h"
#include "video/mc6845.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_xl80_device

class c64_xl80_device : public device_t,
						public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_xl80_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

	// not really public
	MC6845_UPDATE_ROW( crtc_update_row );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw) { return 1; }
	virtual int c64_exrom_r(offs_t offset, int sphi2, int ba, int rw) { return 0; }

private:
	required_device<h46505_device> m_crtc;
	required_device<palette_device> m_palette;
	required_memory_region m_char_rom;
	optional_shared_ptr<UINT8> m_ram;
=======
	c64_xl80_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual void c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw) override { return 1; }
	virtual int c64_exrom_r(offs_t offset, int sphi2, int ba, int rw) override { return 0; }

private:
	MC6845_UPDATE_ROW( crtc_update_row );

	required_device<h46505_device> m_crtc;
	required_device<palette_device> m_palette;
	required_memory_region m_char_rom;
	optional_shared_ptr<uint8_t> m_ram;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_XL80;


#endif
=======
DECLARE_DEVICE_TYPE(C64_XL80, c64_xl80_device)


#endif // MAME_BUS_C64_XL80_H
>>>>>>> upstream/master
