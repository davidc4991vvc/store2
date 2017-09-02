// license:BSD-3-Clause
// copyright-holders:Darkstar
/**********************************************************************
 *
 *    Adaptec AHA-1542{,C,CF} SCSI Controller
 *
 **********************************************************************



 **********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __AHA1542__
#define __AHA1542__


#include "emu.h"
=======
#ifndef MAME_BUS_AHA1542_H
#define MAME_BUS_AHA1542_H

#pragma once


>>>>>>> upstream/master
#include "isa.h"

//*********************************************************************
//   TYPE DEFINITIONS
//*********************************************************************

// ====================> aha1542_device

class aha1542_device : public device_t,
						public device_isa16_card_interface
{
public:
<<<<<<< HEAD
	// construction/destruction
	aha1542_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	static constexpr feature_type unemulated_features() { return feature::DISK; }
	// construction/destruction
	aha1542_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( aha1542_r );
	DECLARE_WRITE8_MEMBER( aha1542_w );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	// device_isa16_card_interface

private:
	// internal state
};

// device type definition

extern const device_type AHA1542;

#endif
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

};

// device type definition
DECLARE_DEVICE_TYPE(AHA1542, aha1542_device)

#endif // MAME_BUS_AHA1542_H
>>>>>>> upstream/master
