// license:BSD-3-Clause
// copyright-holders:Sergey Svishchev
/**********************************************************************

    EC-1841 92-key keyboard emulation

*********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __PC_KBD_EC_1841__
#define __PC_KBD_EC_1841__

#include "emu.h"
#include "cpu/mcs48/mcs48.h"
#include "pc_kbdc.h"
=======
#ifndef MAME_BUS_PC_KBD_EC1841_H
#define MAME_BUS_PC_KBD_EC1841_H

#pragma once

#include "pc_kbdc.h"
#include "cpu/mcs48/mcs48.h"
>>>>>>> upstream/master



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> ec_1841_keyboard_device

<<<<<<< HEAD
class ec_1841_keyboard_device :  public device_t,
										public device_pc_kbd_interface
{
public:
	// construction/destruction
	ec_1841_keyboard_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

=======
class ec_1841_keyboard_device : public device_t, public device_pc_kbd_interface
{
public:
	// construction/destruction
	ec_1841_keyboard_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	// device_pc_kbd_interface overrides
	virtual DECLARE_WRITE_LINE_MEMBER( clock_write ) override;
	virtual DECLARE_WRITE_LINE_MEMBER( data_write ) override;

private:
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER( bus_w );
	DECLARE_READ8_MEMBER( p1_r );
	DECLARE_WRITE8_MEMBER( p1_w );
	DECLARE_WRITE8_MEMBER( p2_w );
<<<<<<< HEAD
	DECLARE_READ8_MEMBER( t1_r );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_pc_kbd_interface overrides
	virtual DECLARE_WRITE_LINE_MEMBER( clock_write );
	virtual DECLARE_WRITE_LINE_MEMBER( data_write );

private:
	required_device<cpu_device> m_maincpu;
	required_ioport m_md00;
	required_ioport m_md01;
	required_ioport m_md02;
	required_ioport m_md03;
	required_ioport m_md04;
	required_ioport m_md05;
	required_ioport m_md06;
	required_ioport m_md07;
	required_ioport m_md08;
	required_ioport m_md09;
	required_ioport m_md10;
	required_ioport m_md11;
	required_ioport m_md12;
	required_ioport m_md13;
	required_ioport m_md14;
	required_ioport m_md15;

	UINT8 m_bus;
	UINT8 m_p1;
	UINT8 m_p2;
=======
	DECLARE_READ_LINE_MEMBER( t1_r );

	required_device<cpu_device> m_maincpu;
	required_ioport_array<16> m_kbd;

	uint8_t m_bus;
	uint8_t m_p1;
	uint8_t m_p2;
>>>>>>> upstream/master
	int m_q;
};


// device type definition
<<<<<<< HEAD
extern const device_type PC_KBD_EC_1841;

#endif
=======
DECLARE_DEVICE_TYPE(PC_KBD_EC_1841, ec_1841_keyboard_device)

#endif // MAME_BUS_PC_KBD_EC1841_H
>>>>>>> upstream/master
