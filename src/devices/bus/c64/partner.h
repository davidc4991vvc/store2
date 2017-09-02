// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Timeworks PARTNER 64 cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __PARTNER__
#define __PARTNER__

#include "emu.h"
=======
#ifndef MAME_BUS_C64_PARTNER_H
#define MAME_BUS_C64_PARTNER_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_partner_cartridge_device

class c64_partner_cartridge_device : public device_t,
										public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_partner_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;
=======
	c64_partner_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;
>>>>>>> upstream/master

	DECLARE_WRITE_LINE_MEMBER( nmi_w );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw);

private:
	optional_shared_ptr<UINT8> m_ram;
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual void c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw) override;

private:
	optional_shared_ptr<uint8_t> m_ram;
>>>>>>> upstream/master

	int m_a0;
	int m_a6;
	int m_nmi;
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_PARTNER;


#endif
=======
DECLARE_DEVICE_TYPE(C64_PARTNER, c64_partner_cartridge_device)


#endif // MAME_BUS_C64_PARTNER_H
>>>>>>> upstream/master
