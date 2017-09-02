// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Dela 256KB EPROM cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __DELA_EP256__
#define __DELA_EP256__


#include "emu.h"
=======
#ifndef MAME_BUS_C64_DELA_EP256_H
#define MAME_BUS_C64_DELA_EP256_H

#pragma once


>>>>>>> upstream/master
#include "exp.h"
#include "bus/generic/slot.h"
#include "bus/generic/carts.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_dela_ep256_cartridge_device

class c64_dela_ep256_cartridge_device : public device_t,
										public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_dela_ep256_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
=======
	c64_dela_ep256_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual void c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
>>>>>>> upstream/master

private:
	generic_slot_device *m_eproms[8];

<<<<<<< HEAD
	UINT8 m_bank, m_socket;
=======
	uint8_t m_bank, m_socket;
>>>>>>> upstream/master
	int m_reset;
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_DELA_EP256;



#endif
=======
DECLARE_DEVICE_TYPE(C64_DELA_EP256, c64_dela_ep256_cartridge_device)


#endif // MAME_BUS_C64_DELA_EP256_H
>>>>>>> upstream/master
