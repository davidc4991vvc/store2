// license:BSD-3-Clause
// copyright-holders:Curt Coder
/***************************************************************************

    dirtc.c

    Device Output interfaces.

***************************************************************************/

#include "emu.h"
<<<<<<< HEAD

=======
#include "dioutput.h"
>>>>>>> upstream/master


//**************************************************************************
//  DEVICE OUTPUT INTERFACE
//**************************************************************************

//-------------------------------------------------
//  device_output_interface - constructor
//-------------------------------------------------

device_output_interface::device_output_interface(const machine_config &mconfig, device_t &device) :
	device_interface(device, "output"),
	m_output_index(0),
<<<<<<< HEAD
	m_output_name(NULL)
=======
	m_output_name(nullptr)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_output_interface - destructor
//-------------------------------------------------

device_output_interface::~device_output_interface()
{
}

void device_output_interface::set_output_value(int value) const
{
	if (m_output_name)
<<<<<<< HEAD
		output_set_value(m_output_name, value);
=======
		device().machine().output().set_value(m_output_name, value);
>>>>>>> upstream/master
	else
		fatalerror("Output name not set!");
}

void device_output_interface::set_led_value(int value) const
{
	if (m_output_name)
<<<<<<< HEAD
		output_set_value(m_output_name, value);
	else
		output_set_led_value(m_output_index, value);
=======
		device().machine().output().set_value(m_output_name, value);
	else
		device().machine().output().set_led_value(m_output_index, value);
>>>>>>> upstream/master
}

void device_output_interface::set_lamp_value(int value) const
{
	if (m_output_name)
<<<<<<< HEAD
		output_set_value(m_output_name, value);
	else
		output_set_lamp_value(m_output_index, value);
=======
		device().machine().output().set_value(m_output_name, value);
	else
		device().machine().output().set_lamp_value(m_output_index, value);
>>>>>>> upstream/master
}

void device_output_interface::set_digit_value(int value) const
{
	if (m_output_name)
<<<<<<< HEAD
		output_set_value(m_output_name, value);
	else
		output_set_digit_value(m_output_index, value);
=======
		device().machine().output().set_value(m_output_name, value);
	else
		device().machine().output().set_digit_value(m_output_index, value);
>>>>>>> upstream/master
}
