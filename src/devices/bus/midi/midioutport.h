// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    midioutport.h

    MIDI Out port - glues the image device to the pluggable midi port

*********************************************************************/

<<<<<<< HEAD
#ifndef _MIDIOUTPORT_H_
#define _MIDIOUTPORT_H_
=======
#ifndef MAME_BUS_MIDI_MIDIOUTPORT_H
#define MAME_BUS_MIDI_MIDIOUTPORT_H

#pragma once
>>>>>>> upstream/master

#include "midi.h"
#include "imagedev/midiout.h"

class midiout_port_device : public device_t,
	public device_midi_port_interface
{
public:
<<<<<<< HEAD
	midiout_port_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual machine_config_constructor device_mconfig_additions() const;

	virtual DECLARE_WRITE_LINE_MEMBER( input_txd ) { if (started()) m_midiout->tx(state); }

protected:
	virtual void device_start() { }
	virtual void device_reset() { }
=======
	midiout_port_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE_LINE_MEMBER( input_txd ) override { if (started()) m_midiout->tx(state); }

protected:
	virtual void device_start() override { }
	virtual void device_reset() override { }
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

private:
	required_device<midiout_device> m_midiout;
};

<<<<<<< HEAD
extern const device_type MIDIOUT_PORT;

#endif
=======
DECLARE_DEVICE_TYPE(MIDIOUT_PORT, midiout_port_device)

#endif // MAME_BUS_MIDI_MIDIOUTPORT_H
>>>>>>> upstream/master
