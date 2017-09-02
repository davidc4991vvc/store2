// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Nintendo Entertainment System Four Score Adapter

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __NES_FOURSCORE__
#define __NES_FOURSCORE__


#include "emu.h"
#include "ctrl.h"

=======
#ifndef MAME_BUS_NES_CTRL_4SCORE_H
#define MAME_BUS_NES_CTRL_4SCORE_H

#pragma once

#include "ctrl.h"


>>>>>>> upstream/master
//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> nes_4score_device

class nes_4score_device : public device_t,
							public device_nes_control_port_interface
{
<<<<<<< HEAD
public:
	// construction/destruction
	nes_4score_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual UINT8 read_bit0();

protected:
	UINT32 m_latch;
=======
protected:
	// construction/destruction
	nes_4score_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual uint8_t read_bit0() override;

	uint32_t m_latch;
>>>>>>> upstream/master
};

// ======================> nes_4score_p1p3_device

class nes_4score_p1p3_device : public nes_4score_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_4score_p1p3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual ioport_constructor device_input_ports() const;

protected:
	virtual void write(UINT8 data);
=======
	nes_4score_p1p3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual ioport_constructor device_input_ports() const override;

protected:
	virtual void write(uint8_t data) override;
>>>>>>> upstream/master

private:
	required_ioport m_joypad1;
	required_ioport m_joypad3;
};

// ======================> nes_4score_p2p4_device

class nes_4score_p2p4_device : public nes_4score_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_4score_p2p4_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual ioport_constructor device_input_ports() const;

protected:
	virtual void write(UINT8 data);
=======
	nes_4score_p2p4_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual ioport_constructor device_input_ports() const override;

protected:
	virtual void write(uint8_t data) override;
>>>>>>> upstream/master

private:
	required_ioport m_joypad2;
	required_ioport m_joypad4;
};


// device type definition
<<<<<<< HEAD
extern const device_type NES_4SCORE_P1P3;
extern const device_type NES_4SCORE_P2P4;


#endif
=======
DECLARE_DEVICE_TYPE(NES_4SCORE_P1P3, nes_4score_p1p3_device)
DECLARE_DEVICE_TYPE(NES_4SCORE_P2P4, nes_4score_p2p4_device)


#endif // MAME_BUS_NES_CTRL_4SCORE_H
>>>>>>> upstream/master
