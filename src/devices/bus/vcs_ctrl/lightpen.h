// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Atari Video Computer System lightpen emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VCS_LIGHTPEN__
#define __VCS_LIGHTPEN__

#include "emu.h"
=======
#ifndef MAME_BUS_VCS_CTRL_LIGHTPEN_H
#define MAME_BUS_VCS_CTRL_LIGHTPEN_H

#pragma once

>>>>>>> upstream/master
#include "ctrl.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> vcs_lightpen_device

class vcs_lightpen_device : public device_t,
							public device_vcs_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vcs_lightpen_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;
=======
	vcs_lightpen_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;
>>>>>>> upstream/master

	DECLARE_INPUT_CHANGED_MEMBER( trigger );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();

	// device_vcs_control_port_interface overrides
	virtual UINT8 vcs_joy_r();
=======
	virtual void device_start() override;

	// device_vcs_control_port_interface overrides
	virtual uint8_t vcs_joy_r() override;
>>>>>>> upstream/master

private:
	required_ioport m_joy;
	required_ioport m_lightx;
	required_ioport m_lighty;
};


// device type definition
<<<<<<< HEAD
extern const device_type VCS_LIGHTPEN;


#endif
=======
DECLARE_DEVICE_TYPE(VCS_LIGHTPEN, vcs_lightpen_device)

#endif // MAME_BUS_VCS_CTRL_LIGHTPEN_H
>>>>>>> upstream/master
