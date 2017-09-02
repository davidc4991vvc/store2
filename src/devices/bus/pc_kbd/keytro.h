// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
/***************************************************************************

    Keytronic Keyboard

***************************************************************************/

<<<<<<< HEAD
#ifndef __KB_KEYTRO_H__
#define __KB_KEYTRO_H__
=======
#ifndef MAME_BUS_PC_KBD_KEYTRO_H
#define MAME_BUS_PC_KBD_KEYTRO_H

#pragma once
>>>>>>> upstream/master

#include "pc_kbdc.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> pc_kbd_keytronic_pc3270_device

class pc_kbd_keytronic_pc3270_device :  public device_t,
										public device_pc_kbd_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	pc_kbd_keytronic_pc3270_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	required_device<cpu_device> m_cpu;

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;
	virtual const rom_entry *device_rom_region() const;

	virtual DECLARE_WRITE_LINE_MEMBER(clock_write);
	virtual DECLARE_WRITE_LINE_MEMBER(data_write);
=======
	pc_kbd_keytronic_pc3270_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	required_device<cpu_device> m_cpu;

	virtual DECLARE_WRITE_LINE_MEMBER(clock_write) override;
	virtual DECLARE_WRITE_LINE_MEMBER(data_write) override;
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( internal_data_read );
	DECLARE_WRITE8_MEMBER( internal_data_write );
	DECLARE_READ8_MEMBER( p1_read );
	DECLARE_WRITE8_MEMBER( p1_write );
	DECLARE_READ8_MEMBER( p2_read );
	DECLARE_WRITE8_MEMBER( p2_write );
	DECLARE_READ8_MEMBER( p3_read );
	DECLARE_WRITE8_MEMBER( p3_write );

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	UINT8   m_p1;
	UINT8   m_p1_data;
	UINT8   m_p2;
	UINT8   m_p3;
	UINT16  m_last_write_addr;
=======
	pc_kbd_keytronic_pc3270_device(
			machine_config const &mconfig,
			device_type type,
			char const *tag,
			device_t *owner,
			uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;
	virtual const tiny_rom_entry *device_rom_region() const override;

	uint8_t   m_p1;
	uint8_t   m_p1_data;
	uint8_t   m_p2;
	uint8_t   m_p3;
	uint16_t  m_last_write_addr;
>>>>>>> upstream/master
};


class pc_kbd_keytronic_pc3270_at_device : public pc_kbd_keytronic_pc3270_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	pc_kbd_keytronic_pc3270_at_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: pc_kbd_keytronic_pc3270_device(mconfig, tag, owner, clock)
	{
	}

	virtual ioport_constructor device_input_ports() const;
=======
	pc_kbd_keytronic_pc3270_at_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual ioport_constructor device_input_ports() const override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type PC_KBD_KEYTRONIC_PC3270;
extern const device_type PC_KBD_KEYTRONIC_PC3270_AT;

#endif  /* __KB_KEYTRO_H__ */
=======
DECLARE_DEVICE_TYPE(PC_KBD_KEYTRONIC_PC3270,    pc_kbd_keytronic_pc3270_device)
DECLARE_DEVICE_TYPE(PC_KBD_KEYTRONIC_PC3270_AT, pc_kbd_keytronic_pc3270_at_device)

#endif // MAME_BUS_PC_KBD_KEYTRO_H
>>>>>>> upstream/master
