// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    midiinport.h

    MIDI In port - glues the image device to the pluggable midi port

*********************************************************************/

<<<<<<< HEAD
#ifndef _MIDIINPORT_H_
#define _MIDIINPORT_H_
=======
#ifndef MAME_BUS_MIDI_MIDIINPORT_H
#define MAME_BUS_MIDI_MIDIINPORT_H

#pragma once
>>>>>>> upstream/master

#include "midi.h"
#include "imagedev/midiin.h"

class midiin_port_device : public device_t,
	public device_midi_port_interface
{
public:
<<<<<<< HEAD
	midiin_port_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	DECLARE_WRITE_LINE_MEMBER( read ) { output_rxd(state); }

protected:
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_start() { m_owner = dynamic_cast<midi_port_device *>(owner()); }
	virtual void device_reset() { }

private:
	required_device<midiin_device> m_midiin;
};

extern const device_type MIDIIN_PORT;

#endif
=======
	midiin_port_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
	virtual void device_start() override { m_owner = dynamic_cast<midi_port_device *>(owner()); }
	virtual void device_reset() override { }

private:
	DECLARE_WRITE_LINE_MEMBER( read ) { output_rxd(state); }

	required_device<midiin_device> m_midiin;
};

DECLARE_DEVICE_TYPE(MIDIIN_PORT, midiin_port_device)

#endif // MAME_BUS_MIDI_MIDIINPORT_H
>>>>>>> upstream/master
