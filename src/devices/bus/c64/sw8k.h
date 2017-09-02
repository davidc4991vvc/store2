// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    C64 switchable 8K cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __C64_SW8K__
#define __C64_SW8K__


#include "emu.h"
=======
#ifndef MAME_BUS_C64_SW8K_H
#define MAME_BUS_C64_SW8K_H

#pragma once


>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_switchable_8k_cartridge_device

class c64_switchable_8k_cartridge_device : public device_t,
											public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_switchable_8k_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
=======
	c64_switchable_8k_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
>>>>>>> upstream/master

private:
	required_ioport m_sw;

	int m_bank;
};


// device type definition
extern const device_type C64_SW8K;
<<<<<<< HEAD


#endif
=======
DECLARE_DEVICE_TYPE(C64_SW8K, c64_switchable_8k_cartridge_device)


#endif // MAME_BUS_C64_SW8K_H
>>>>>>> upstream/master
