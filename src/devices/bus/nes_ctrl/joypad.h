// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Nintendo Family Computer & Entertainment System Joypads

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __NES_JOYPAD__
#define __NES_JOYPAD__


#include "emu.h"
#include "ctrl.h"

=======
#ifndef MAME_BUS_NES_CTRL_JOYPAD_H
#define MAME_BUS_NES_CTRL_JOYPAD_H

#pragma once

#include "ctrl.h"


>>>>>>> upstream/master
//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> nes_joypad_device

class nes_joypad_device : public device_t,
							public device_nes_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_joypad_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	nes_joypad_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual UINT8 read_bit0();
	virtual void write(UINT8 data);

	required_ioport m_joypad;
	UINT32 m_latch;
=======
	nes_joypad_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual ioport_constructor device_input_ports() const override;

protected:
	nes_joypad_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual uint8_t read_bit0() override;
	virtual void write(uint8_t data) override;

	required_ioport m_joypad;
	uint32_t m_latch;
>>>>>>> upstream/master
};

// ======================> nes_fcpad2_device

class nes_fcpad2_device : public nes_joypad_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_fcpad2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual ioport_constructor device_input_ports() const;

protected:
	virtual UINT8 read_exp(offs_t offset);
	virtual void write(UINT8 data);
=======
	nes_fcpad2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual ioport_constructor device_input_ports() const override;

protected:
	virtual uint8_t read_exp(offs_t offset) override;
	virtual void write(uint8_t data) override;
>>>>>>> upstream/master
};

// ======================> nes_ccpadl_device

class nes_ccpadl_device : public nes_joypad_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ccpadl_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual ioport_constructor device_input_ports() const;
=======
	nes_ccpadl_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual ioport_constructor device_input_ports() const override;
>>>>>>> upstream/master
};

// ======================> nes_ccpadr_device

class nes_ccpadr_device : public nes_joypad_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ccpadr_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual ioport_constructor device_input_ports() const;
=======
	nes_ccpadr_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual ioport_constructor device_input_ports() const override;
>>>>>>> upstream/master
};

// ======================> nes_arcstick_device

class nes_arcstick_device : public nes_joypad_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_arcstick_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual ioport_constructor device_input_ports() const;
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	virtual UINT8 read_bit0() { return 0; }
	virtual UINT8 read_exp(offs_t offset);
	virtual void write(UINT8 data);
=======
	nes_arcstick_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual ioport_constructor device_input_ports() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	virtual uint8_t read_bit0() override { return 0; }
	virtual uint8_t read_exp(offs_t offset) override;
	virtual void write(uint8_t data) override;
>>>>>>> upstream/master

	required_device<nes_control_port_device> m_daisychain;
	required_ioport m_cfg;
};


// device type definition
<<<<<<< HEAD
extern const device_type NES_JOYPAD;
extern const device_type NES_FCPAD_P2;
extern const device_type NES_CCPAD_LEFT;
extern const device_type NES_CCPAD_RIGHT;
extern const device_type NES_ARCSTICK;

#endif
=======
DECLARE_DEVICE_TYPE(NES_JOYPAD,      nes_joypad_device)
DECLARE_DEVICE_TYPE(NES_FCPAD_P2,    nes_fcpad2_device)
DECLARE_DEVICE_TYPE(NES_CCPAD_LEFT,  nes_ccpadl_device)
DECLARE_DEVICE_TYPE(NES_CCPAD_RIGHT, nes_ccpadr_device)
DECLARE_DEVICE_TYPE(NES_ARCSTICK,    nes_arcstick_device)

#endif // MAME_BUS_NES_CTRL_JOYPAD_H
>>>>>>> upstream/master
