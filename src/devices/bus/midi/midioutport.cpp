// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

<<<<<<< HEAD
    midioutport.c
=======
    midioutport.cpp
>>>>>>> upstream/master

    MIDI Out serial port - glues the image device to the pluggable serial port

*********************************************************************/

<<<<<<< HEAD
#include "midioutport.h"

const device_type MIDIOUT_PORT = &device_creator<midiout_port_device>;

midiout_port_device::midiout_port_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MIDIOUT_PORT, "MIDI Out port", tag, owner, clock, "midiout_port", __FILE__),
=======
#include "emu.h"
#include "midioutport.h"

DEFINE_DEVICE_TYPE(MIDIOUT_PORT, midiout_port_device, "midiout_port", "MIDI Out port")

midiout_port_device::midiout_port_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MIDIOUT_PORT, tag, owner, clock),
>>>>>>> upstream/master
	device_midi_port_interface(mconfig, *this),
	m_midiout(*this, "midioutimg")
{
}

<<<<<<< HEAD
static MACHINE_CONFIG_FRAGMENT(midiout_port_config)
	MCFG_MIDIOUT_ADD("midioutimg")
MACHINE_CONFIG_END

machine_config_constructor midiout_port_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME(midiout_port_config);
}
=======
MACHINE_CONFIG_MEMBER(midiout_port_device::device_add_mconfig)
	MCFG_MIDIOUT_ADD("midioutimg")
MACHINE_CONFIG_END
>>>>>>> upstream/master
