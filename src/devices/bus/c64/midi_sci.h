// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Sequential Circuits MIDI Interface cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __C64_MIDI_SCI__
#define __C64_MIDI_SCI__
=======
#ifndef MAME_BUS_C64_MIDI_SCI_H
#define MAME_BUS_C64_MIDI_SCI_H

#pragma once
>>>>>>> upstream/master

#include "exp.h"
#include "machine/6850acia.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_sequential_midi_cartridge_device

class c64_sequential_midi_cartridge_device : public device_t,
	public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_sequential_midi_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	DECLARE_WRITE_LINE_MEMBER( acia_irq_w );
	DECLARE_WRITE_LINE_MEMBER( write_acia_clock );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);

private:
=======
	c64_sequential_midi_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual void c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;

private:
	DECLARE_WRITE_LINE_MEMBER( acia_irq_w );
	DECLARE_WRITE_LINE_MEMBER( write_acia_clock );

>>>>>>> upstream/master
	required_device<acia6850_device> m_acia;
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_MIDI_SCI;


#endif
=======
DECLARE_DEVICE_TYPE(C64_MIDI_SCI, c64_sequential_midi_cartridge_device)


#endif // MAME_BUS_C64_MIDI_SCI_H
>>>>>>> upstream/master
