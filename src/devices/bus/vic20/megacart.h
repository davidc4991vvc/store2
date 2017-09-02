// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Mega-Cart cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VIC20_MEGACART__
#define __VIC20_MEGACART__

#include "emu.h"
=======
#ifndef MAME_BUS_VIC20_MEGACART_H
#define MAME_BUS_VIC20_MEGACART_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> vic20_megacart_device

class vic20_megacart_device :  public device_t,
								public device_vic20_expansion_card_interface,
								public device_nvram_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vic20_megacart_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_nvram_interface overrides
	virtual void nvram_default() { }
	virtual void nvram_read(emu_file &file) { file.read(m_nvram, m_nvram.bytes()); }
	virtual void nvram_write(emu_file &file) { file.write(m_nvram, m_nvram.bytes()); }

	// device_vic20_expansion_card_interface overrides
	virtual UINT8 vic20_cd_r(address_space &space, offs_t offset, UINT8 data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3);
	virtual void vic20_cd_w(address_space &space, offs_t offset, UINT8 data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3);
=======
	vic20_megacart_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	// device_nvram_interface overrides
	virtual void nvram_default() override { }
	virtual void nvram_read(emu_file &file) override { file.read(m_nvram, m_nvram.bytes()); }
	virtual void nvram_write(emu_file &file) override { file.write(m_nvram, m_nvram.bytes()); }

	// device_vic20_expansion_card_interface overrides
	virtual uint8_t vic20_cd_r(address_space &space, offs_t offset, uint8_t data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3) override;
	virtual void vic20_cd_w(address_space &space, offs_t offset, uint8_t data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3) override;
>>>>>>> upstream/master

private:
	int m_nvram_en;
};


// device type definition
<<<<<<< HEAD
extern const device_type VIC20_MEGACART;



#endif
=======
DECLARE_DEVICE_TYPE(VIC20_MEGACART, vic20_megacart_device)

#endif // MAME_BUS_VIC20_MEGACART_H
>>>>>>> upstream/master
