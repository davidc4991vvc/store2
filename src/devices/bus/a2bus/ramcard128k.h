// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    ramcard128k.h

    Implemention of the Saturn Systems 128K extended language card

*********************************************************************/

<<<<<<< HEAD
#ifndef __A2BUS_RAMCARD128K__
#define __A2BUS_RAMCARD128K__

#include "emu.h"
=======
#ifndef MAME_BUS_A2BUS_RAMCARD128K_H
#define MAME_BUS_A2BUS_RAMCARD128K_H

#pragma once

>>>>>>> upstream/master
#include "a2bus.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class a2bus_ssramcard_device:
	public device_t,
	public device_a2bus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	a2bus_ssramcard_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	a2bus_ssramcard_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual void device_start();
	virtual void device_reset();

	// overrides of standard a2bus slot functions
	virtual UINT8 read_c0nx(address_space &space, UINT8 offset);
	virtual void write_c0nx(address_space &space, UINT8 offset, UINT8 data);
	virtual UINT8 read_inh_rom(address_space &space, UINT16 offset);
	virtual void write_inh_rom(address_space &space, UINT16 offset, UINT8 data);
	virtual UINT16 inh_start() { return 0xd000; }
	virtual UINT16 inh_end() { return 0xffff; }
	virtual int inh_type();
=======
	a2bus_ssramcard_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	a2bus_ssramcard_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;

	// overrides of standard a2bus slot functions
	virtual uint8_t read_c0nx(address_space &space, uint8_t offset) override;
	virtual void write_c0nx(address_space &space, uint8_t offset, uint8_t data) override;
	virtual uint8_t read_inh_rom(address_space &space, uint16_t offset) override;
	virtual void write_inh_rom(address_space &space, uint16_t offset, uint8_t data) override;
	virtual uint16_t inh_start() override { return 0xd000; }
	virtual uint16_t inh_end() override { return 0xffff; }
	virtual int inh_type() override;
>>>>>>> upstream/master

private:
	void do_io(int offset);

	int m_inh_state;
	int m_last_offset;
	int m_dxxx_bank;
	int m_main_bank;
<<<<<<< HEAD
	UINT8 m_ram[128*1024];
};

// device type definition
extern const device_type A2BUS_RAMCARD128K;

#endif /* __A2BUS_RAMCARD128K__ */
=======
	uint8_t m_ram[128*1024];
};

// device type definition
DECLARE_DEVICE_TYPE(A2BUS_RAMCARD128K, a2bus_ssramcard_device)

#endif // MAME_BUS_A2BUS_RAMCARD128K_H
>>>>>>> upstream/master
