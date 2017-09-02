// license:BSD-3-Clause
// copyright-holders:Carl
<<<<<<< HEAD
#ifndef __SSI2001__
#define __SSI2001__

#include "emu.h"
=======
#ifndef MAME_BUS_ISA_SSI2001_H
#define MAME_BUS_ISA_SSI2001_H

#pragma once

>>>>>>> upstream/master
#include "isa.h"
#include "sound/mos6581.h"
#include "bus/pc_joy/pc_joy.h"

//*********************************************************************
//   TYPE DEFINITIONS
//*********************************************************************

// ====================> ssi2001_device

class ssi2001_device : public device_t,
						public device_isa8_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	ssi2001_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	required_device<pc_joy_device> m_joy;
	required_device<mos6581_device> m_sid;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
=======
	ssi2001_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	required_device<pc_joy_device> m_joy;
	required_device<mos6581_device> m_sid;
>>>>>>> upstream/master
};

// device type definition

<<<<<<< HEAD
extern const device_type ISA8_SSI2001;

#endif
=======
DECLARE_DEVICE_TYPE(ISA8_SSI2001, ssi2001_device)

#endif // MAME_BUS_ISA_SSI2001_H
>>>>>>> upstream/master
