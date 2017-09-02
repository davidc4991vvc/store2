// license:BSD-3-Clause
// copyright-holders:smf
/**********************************************************************

    Commodore PET userport joystick adapter emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __PETUJA__
#define __PETUJA__


#include "emu.h"
=======
#ifndef MAME_BUS_PET_PETUJA_H
#define MAME_BUS_PET_PETUJA_H

#pragma once


>>>>>>> upstream/master
#include "user.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> pet_userport_joystick_adapter_device

class pet_userport_joystick_adapter_device : public device_t,
	public device_pet_user_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	pet_userport_joystick_adapter_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;
=======
	pet_userport_joystick_adapter_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;
>>>>>>> upstream/master

	// device_pet_user_port_interface overrides
	WRITE_LINE_MEMBER( write_up1 ) { m_up1 = state; update_port1(); }
	WRITE_LINE_MEMBER( write_down1 ) { m_down1 = state; update_port1(); }
	WRITE_LINE_MEMBER( write_fire1 ) { m_fire1 = state; update_port1(); }
	WRITE_LINE_MEMBER( write_up2 ) { m_up2 = state; update_port2(); }
	WRITE_LINE_MEMBER( write_down2 ) { m_down2 = state; update_port2(); }
	WRITE_LINE_MEMBER( write_fire2 ) { m_fire2 = state; update_port2(); }

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
=======
	virtual void device_start() override;
>>>>>>> upstream/master

	void update_port1();
	void update_port2();
	int m_up1;
	int m_down1;
	int m_fire1;
	int m_up2;
	int m_down2;
	int m_fire2;
};


// device type definition
<<<<<<< HEAD
extern const device_type PET_USERPORT_JOYSTICK_ADAPTER;


#endif
=======
DECLARE_DEVICE_TYPE(PET_USERPORT_JOYSTICK_ADAPTER, pet_userport_joystick_adapter_device)


#endif // MAME_BUS_PET_PETUJA_H
>>>>>>> upstream/master
