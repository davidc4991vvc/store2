// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Luxor ABC-800 keyboard emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __ABC800_KEYBOARD__
#define __ABC800_KEYBOARD__


#include "emu.h"
=======
#ifndef MAME_BUS_ABCKB_ABC800KB_H
#define MAME_BUS_ABCKB_ABC800KB_H

#pragma once


>>>>>>> upstream/master
#include "cpu/mcs48/mcs48.h"
#include "abckb.h"
#include "sound/discrete.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> abc800_keyboard_device

class abc800_keyboard_device :  public device_t,
								public abc_keyboard_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	abc800_keyboard_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	// abc_keyboard_interface overrides
	virtual void txd_w(int state);

	// not really public
	DECLARE_READ8_MEMBER( kb_p1_r );
	DECLARE_WRITE8_MEMBER( kb_p1_w );
	DECLARE_WRITE8_MEMBER( kb_p2_w );
	DECLARE_READ8_MEMBER( kb_t1_r );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	abc800_keyboard_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// abc_keyboard_interface overrides
	virtual void txd_w(int state) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;
>>>>>>> upstream/master

private:
	inline void serial_output(int state);
	inline void serial_clock();
	inline void key_down(int state);

<<<<<<< HEAD
	required_device<cpu_device> m_maincpu;
	required_ioport m_x0;
	required_ioport m_x1;
	required_ioport m_x2;
	required_ioport m_x3;
	required_ioport m_x4;
	required_ioport m_x5;
	required_ioport m_x6;
	required_ioport m_x7;
	required_ioport m_x8;
	required_ioport m_x9;
	required_ioport m_x10;
	required_ioport m_x11;
=======
	DECLARE_READ8_MEMBER( kb_p1_r );
	DECLARE_WRITE8_MEMBER( kb_p1_w );
	DECLARE_WRITE8_MEMBER( kb_p2_w );
	DECLARE_READ_LINE_MEMBER( kb_t1_r );

	required_device<cpu_device> m_maincpu;
	required_ioport_array<12> m_x;
>>>>>>> upstream/master

	int m_row;
	int m_txd;
	int m_clk;
	int m_stb;
	int m_keydown;

	// timers
	emu_timer *m_serial_timer;
};


// device type definition
<<<<<<< HEAD
extern const device_type ABC800_KEYBOARD;



#endif
=======
DECLARE_DEVICE_TYPE(ABC800_KEYBOARD, abc800_keyboard_device)

#endif // MAME_BUS_ABCKB_ABC800KB_H
>>>>>>> upstream/master
