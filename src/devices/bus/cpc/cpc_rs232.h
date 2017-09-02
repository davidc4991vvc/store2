// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
/*
 * cpc_rs232.h
 *
 *  Created on: 22/04/2014
 */

<<<<<<< HEAD
#ifndef CPC_RS232_H_
#define CPC_RS232_H_

#include "emu.h"
#include "machine/z80dart.h"
#include "machine/pit8253.h"
#include "bus/rs232/rs232.h"
#include "cpcexp.h"

class cpc_rs232_device : public device_t,
							public device_cpc_expansion_card_interface
{
public:
	// construction/destruction
	cpc_rs232_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	cpc_rs232_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

			// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	DECLARE_WRITE_LINE_MEMBER(pit_out0_w);
	DECLARE_WRITE_LINE_MEMBER(pit_out1_w);
	DECLARE_WRITE_LINE_MEMBER(pit_out2_w);
=======
#ifndef MAME_BUS_CPC_CPC_RS232_H
#define MAME_BUS_CPC_CPC_RS232_H

#pragma once

#include "cpcexp.h"
#include "machine/z80dart.h"
#include "machine/pit8253.h"
#include "bus/rs232/rs232.h"

class cpc_rs232_device : public device_t, public device_cpc_expansion_card_interface
{
public:
	// construction/destruction
	cpc_rs232_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(dart_r);
	DECLARE_WRITE8_MEMBER(dart_w);
	DECLARE_READ8_MEMBER(pit_r);
	DECLARE_WRITE8_MEMBER(pit_w);

<<<<<<< HEAD
	required_device<pit8253_device> m_pit;
	required_device<z80dart_device> m_dart;
	required_device<rs232_port_device> m_rs232;
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual const rom_entry *device_rom_region() const;

private:
=======
protected:
	cpc_rs232_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual const tiny_rom_entry *device_rom_region() const override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	required_device<pit8253_device> m_pit;
	required_device<z80dart_device> m_dart;
	required_device<rs232_port_device> m_rs232;

private:
	DECLARE_WRITE_LINE_MEMBER(pit_out0_w);
	DECLARE_WRITE_LINE_MEMBER(pit_out1_w);
	DECLARE_WRITE_LINE_MEMBER(pit_out2_w);

>>>>>>> upstream/master
	cpc_expansion_slot_device *m_slot;
};

class cpc_ams_rs232_device : public cpc_rs232_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	cpc_ams_rs232_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual const rom_entry *device_rom_region() const;
};

// device type definition
extern const device_type CPC_RS232;
extern const device_type CPC_RS232_AMS;

#endif /* CPC_RS232_H_ */
=======
	cpc_ams_rs232_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual const tiny_rom_entry *device_rom_region() const override;
};

// device type definition
DECLARE_DEVICE_TYPE(CPC_RS232,     cpc_rs232_device)
DECLARE_DEVICE_TYPE(CPC_RS232_AMS, cpc_ams_rs232_device)

#endif // MAME_BUS_CPC_CPC_RS232_H
>>>>>>> upstream/master
