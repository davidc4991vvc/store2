// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    EACA Colour Genie Joystick Interface EG2013

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __CGENIE_PARALLEL_JOYSTICK_H__
#define __CGENIE_PARALLEL_JOYSTICK_H__

#include "emu.h"
=======
#ifndef MAME_BUS_CGENIE_PARALLEL_JOYSTICK_H
#define MAME_BUS_CGENIE_PARALLEL_JOYSTICK_H

#pragma once

>>>>>>> upstream/master
#include "parallel.h"


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> cgenie_joystick_device

<<<<<<< HEAD
class cgenie_joystick_device : public device_t, public device_parallel_interface
{
public:
	// construction/destruction
	cgenie_joystick_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual void device_start();
	virtual void device_reset();
	virtual ioport_constructor device_input_ports() const;

	virtual void pa_w(UINT8 data);
	virtual UINT8 pb_r();
=======
class cgenie_joystick_device : public device_t, public device_cg_parallel_interface
{
public:
	// construction/destruction
	cgenie_joystick_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual ioport_constructor device_input_ports() const override;

	virtual void pa_w(uint8_t data) override;
	virtual uint8_t pb_r() override;
>>>>>>> upstream/master

private:
	required_ioport_array<4> m_joy;
	required_ioport_array<6> m_keypad;

<<<<<<< HEAD
	UINT8 m_select;
};

// device type definition
extern const device_type CGENIE_JOYSTICK;

#endif // __CGENIE_PARALLEL_JOYSTICK_H__
=======
	uint8_t m_select;
};

// device type definition
DECLARE_DEVICE_TYPE(CGENIE_JOYSTICK, cgenie_joystick_device)

#endif // MAME_BUS_CGENIE_PARALLEL_JOYSTICK_H
>>>>>>> upstream/master
