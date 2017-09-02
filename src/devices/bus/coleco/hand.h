// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    ColecoVision Hand Controller emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __COLECO_HAND_CONTROLLER__
#define __COLECO_HAND_CONTROLLER__

#include "emu.h"
=======
#ifndef MAME_BUS_COLECO_HAND_H
#define MAME_BUS_COLECO_HAND_H

#pragma once

>>>>>>> upstream/master
#include "ctrl.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> coleco_hand_controller_t

class coleco_hand_controller_t : public device_t,
=======
// ======================> coleco_hand_controller_device

class coleco_hand_controller_device : public device_t,
>>>>>>> upstream/master
									public device_colecovision_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	coleco_hand_controller_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;
=======
	coleco_hand_controller_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;
>>>>>>> upstream/master

	DECLARE_CUSTOM_INPUT_MEMBER( keypad_r );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();

	// device_vcs_control_port_interface overrides
	virtual UINT8 joy_r();
=======
	virtual void device_start() override;

	// device_vcs_control_port_interface overrides
	virtual uint8_t joy_r() override;
>>>>>>> upstream/master

private:
	required_ioport m_io_common0;
	required_ioport m_io_common1;
	required_ioport m_io_keypad;
};


// device type definition
<<<<<<< HEAD
extern const device_type COLECO_HAND_CONTROLLER;


#endif
=======
DECLARE_DEVICE_TYPE(COLECO_HAND_CONTROLLER, coleco_hand_controller_device)


#endif // MAME_BUS_COLECO_HAND_H
>>>>>>> upstream/master
