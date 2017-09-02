// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    CMD SuperCPU v2 + SuperRAM emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SUPERCPU__
#define __SUPERCPU__

#include "emu.h"
=======
#ifndef MAME_BUS_C64_SUPERCPU_H
#define MAME_BUS_C64_SUPERCPU_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"
#include "cpu/g65816/g65816.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_supercpu_device

class c64_supercpu_device : public device_t,
							public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_supercpu_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw);
	virtual int c64_exrom_r(offs_t offset, int sphi2, int ba, int rw);
=======
	c64_supercpu_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual void c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw) override;
	virtual int c64_exrom_r(offs_t offset, int sphi2, int ba, int rw) override;
>>>>>>> upstream/master

private:
	required_device<cpu_device> m_maincpu;
	required_device<c64_expansion_slot_device> m_exp;

<<<<<<< HEAD
	required_shared_ptr<UINT8> m_sram;
	required_shared_ptr<UINT8> m_dimm;
=======
	required_shared_ptr<uint8_t> m_sram;
	required_shared_ptr<uint8_t> m_dimm;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_SUPERCPU;



#endif
=======
DECLARE_DEVICE_TYPE(C64_SUPERCPU, c64_supercpu_device)


#endif // MAME_BUS_C64_SUPERCPU_H
>>>>>>> upstream/master
