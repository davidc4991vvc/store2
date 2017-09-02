// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    VTech Laser Joystick Interface

    VTech Laser JS 20
    Dick Smith Electronics X-7315

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VTECH_IOEXP_JOYSTICK_H__
#define __VTECH_IOEXP_JOYSTICK_H__

#include "emu.h"
=======
#ifndef MAME_BUS_VTECH_IOEXP_JOYSTICK_H
#define MAME_BUS_VTECH_IOEXP_JOYSTICK_H

#pragma once

>>>>>>> upstream/master
#include "ioexp.h"


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> joystick_interface_device

<<<<<<< HEAD
class joystick_interface_device : public device_t, public device_ioexp_interface
{
public:
	// construction/destruction
	joystick_interface_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
class vtech_joystick_interface_device : public device_t, public device_vtech_ioexp_interface
{
public:
	// construction/destruction
	vtech_joystick_interface_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( joystick_r );

protected:
<<<<<<< HEAD
	virtual ioport_constructor device_input_ports() const;
	virtual void device_start();
	virtual void device_reset();
=======
	virtual ioport_constructor device_input_ports() const override;
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	required_ioport m_joy0;
	required_ioport m_joy0_arm;
	required_ioport m_joy1;
	required_ioport m_joy1_arm;
};

// device type definition
<<<<<<< HEAD
extern const device_type JOYSTICK_INTERFACE;

#endif // __VTECH_IOEXP_JOYSTICK_H__
=======
DECLARE_DEVICE_TYPE(VTECH_JOYSTICK_INTERFACE, vtech_joystick_interface_device)

#endif // MAME_BUS_VTECH_IOEXP_JOYSTICK_H
>>>>>>> upstream/master
