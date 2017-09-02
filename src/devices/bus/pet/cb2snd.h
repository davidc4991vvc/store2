// license:BSD-3-Clause
// copyright-holders:R. Belmont
/**********************************************************************

    Commodore PET userport "CB2 sound" audio device emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __PETUSER_CB2__
#define __PETUSER_CB2__

#include "emu.h"
=======
#ifndef MAME_BUS_PET_CB2SND_H
#define MAME_BUS_PET_CB2SND_H

#pragma once

>>>>>>> upstream/master
#include "user.h"
#include "sound/dac.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class pet_userport_cb2_sound_device : public device_t,
	public device_pet_user_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	pet_userport_cb2_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual machine_config_constructor device_mconfig_additions() const;

	virtual DECLARE_WRITE_LINE_MEMBER( input_m );

	required_device<dac_device> m_dac;

protected:
	// device-level overrides
	virtual void device_start();
=======
	pet_userport_cb2_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE_LINE_MEMBER( input_m ) override;

protected:
	// device-level overrides
	virtual void device_start() override;

	virtual void device_add_mconfig(machine_config &config) override;

	required_device<dac_bit_interface> m_dac;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type PET_USERPORT_CB2_SOUND_DEVICE;

#endif
=======
DECLARE_DEVICE_TYPE(PET_USERPORT_CB2_SOUND_DEVICE, pet_userport_cb2_sound_device)

#endif // MAME_BUS_PET_CB2SND_H
>>>>>>> upstream/master
