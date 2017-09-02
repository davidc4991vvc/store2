// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    NeoRAM cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __NEORAM__
#define __NEORAM__


#include "emu.h"
=======
#ifndef MAME_BUS_C64_NEORAM_H
#define MAME_BUS_C64_NEORAM_H

#pragma once


>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_neoram_cartridge_device

class c64_neoram_cartridge_device : public device_t,
									public device_c64_expansion_card_interface,
									public device_nvram_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_neoram_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_nvram_interface overrides
	virtual void nvram_default() { }
	virtual void nvram_read(emu_file &file) { if (m_nvram != NULL) { file.read(m_nvram, m_nvram.bytes()); } }
	virtual void nvram_write(emu_file &file) { if (m_nvram != NULL) { file.write(m_nvram, m_nvram.bytes()); } }

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);

private:
	UINT16 m_bank;
=======
	c64_neoram_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_nvram_interface overrides
	virtual void nvram_default() override { }
	virtual void nvram_read(emu_file &file) override { if (m_nvram != nullptr) { file.read(m_nvram, m_nvram.bytes()); } }
	virtual void nvram_write(emu_file &file) override { if (m_nvram != nullptr) { file.write(m_nvram, m_nvram.bytes()); } }

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual void c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;

private:
	uint16_t m_bank;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_NEORAM;


#endif
=======
DECLARE_DEVICE_TYPE(C64_NEORAM, c64_neoram_cartridge_device)


#endif // MAME_BUS_C64_NEORAM_H
>>>>>>> upstream/master
