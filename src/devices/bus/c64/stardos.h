// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    StarPoint Software StarDOS cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __STARDOS__
#define __STARDOS__


#include "emu.h"
=======
#ifndef MAME_BUS_C4_STARDOS_H
#define MAME_BUS_C4_STARDOS_H

#pragma once


>>>>>>> upstream/master
#include "exp.h"
#include "machine/6821pia.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_stardos_cartridge_device

class c64_stardos_cartridge_device : public device_t,
										public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_stardos_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw);
	virtual int c64_exrom_r(offs_t offset, int sphi2, int ba, int rw);
=======
	c64_stardos_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual void c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw) override;
	virtual int c64_exrom_r(offs_t offset, int sphi2, int ba, int rw) override;
>>>>>>> upstream/master

private:
	inline void charge_io1_capacitor();
	inline void charge_io2_capacitor();

	int m_io1_charge;
	int m_io2_charge;
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_STARDOS;


#endif
=======
DECLARE_DEVICE_TYPE(C64_STARDOS, c64_stardos_cartridge_device)


#endif // MAME_BUS_C4_STARDOS_H
>>>>>>> upstream/master
