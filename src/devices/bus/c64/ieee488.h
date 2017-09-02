// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore IEEE-488 cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __C64_IEEE488__
#define __C64_IEEE488__

#include "emu.h"
#include "bus/ieee488/ieee488.h"
#include "machine/6525tpi.h"
#include "exp.h"
=======
#ifndef MAME_BUS_C64_IEEE488_H
#define MAME_BUS_C64_IEEE488_H

#pragma once

#include "exp.h"
#include "bus/ieee488/ieee488.h"
#include "machine/6525tpi.h"
>>>>>>> upstream/master



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_ieee488_device

class c64_ieee488_device : public device_t,
							public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_ieee488_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	// not really public
=======
	c64_ieee488_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual void c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw) override;

private:
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER( tpi_pa_r );
	DECLARE_WRITE8_MEMBER( tpi_pa_w );
	DECLARE_READ8_MEMBER( tpi_pc_r );
	DECLARE_WRITE8_MEMBER( tpi_pc_w );

<<<<<<< HEAD
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw);

private:
=======
>>>>>>> upstream/master
	required_device<tpi6525_device> m_tpi;
	required_device<ieee488_device> m_bus;
	required_device<c64_expansion_slot_device> m_exp;

	int m_roml_sel;
};


<<<<<<< HEAD

// device type definition
extern const device_type C64_IEEE488;


#endif
=======
// device type definition
DECLARE_DEVICE_TYPE(C64_IEEE488, c64_ieee488_device)


#endif // MAME_BUS_C64_IEEE488_H
>>>>>>> upstream/master
