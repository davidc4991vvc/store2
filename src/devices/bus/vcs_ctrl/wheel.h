// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Atari Video Computer System Driving Wheel emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VCS_WHEEL__
#define __VCS_WHEEL__

#include "emu.h"
=======
#ifndef MAME_BUS_VCS_CTRL_WHEEL_H
#define MAME_BUS_VCS_CTRL_WHEEL_H

#pragma once

>>>>>>> upstream/master
#include "ctrl.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> vcs_wheel_device

class vcs_wheel_device : public device_t,
							public device_vcs_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vcs_wheel_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();

	// device_vcs_control_port_interface overrides
	virtual UINT8 vcs_joy_r();
=======
	vcs_wheel_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_vcs_control_port_interface overrides
	virtual uint8_t vcs_joy_r() override;
>>>>>>> upstream/master

private:
	required_ioport m_joy;
	required_ioport m_wheel;
};


// device type definition
<<<<<<< HEAD
extern const device_type VCS_WHEEL;


#endif
=======
DECLARE_DEVICE_TYPE(VCS_WHEEL, vcs_wheel_device)

#endif // MAME_BUS_VCS_CTRL_WHEEL_H
>>>>>>> upstream/master
