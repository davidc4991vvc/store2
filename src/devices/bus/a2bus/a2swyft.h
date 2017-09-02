// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    a2swyft.h

    IAI SwyftCard

*********************************************************************/

<<<<<<< HEAD
#ifndef __A2BUS_SWYFT__
#define __A2BUS_SWYFT__

#include "emu.h"
=======
#ifndef MAME_BUS_A2BUS_A2SWYFT_H
#define MAME_BUS_A2BUS_A2SWYFT_H

#pragma once

>>>>>>> upstream/master
#include "a2bus.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class a2bus_swyft_device:
	public device_t,
	public device_a2bus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	a2bus_swyft_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	a2bus_swyft_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	virtual const rom_entry *device_rom_region() const;

protected:
	virtual void device_start();
	virtual void device_reset();

	virtual UINT8 read_c0nx(address_space &space, UINT8 offset);
	virtual void write_c0nx(address_space &space, UINT8 offset, UINT8 data);
	virtual UINT8 read_inh_rom(address_space &space, UINT16 offset);
	virtual UINT16 inh_start() { return 0xd000; }
	virtual UINT16 inh_end() { return 0xffff; }
	virtual int inh_type();

private:
	UINT8 *m_rom;
=======
	a2bus_swyft_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	a2bus_swyft_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;

	virtual uint8_t read_c0nx(address_space &space, uint8_t offset) override;
	virtual void write_c0nx(address_space &space, uint8_t offset, uint8_t data) override;
	virtual uint8_t read_inh_rom(address_space &space, uint16_t offset) override;
	virtual uint16_t inh_start() override { return 0xd000; }
	virtual uint16_t inh_end() override { return 0xffff; }
	virtual int inh_type() override;

private:
	uint8_t *m_rom;
>>>>>>> upstream/master
	int m_rombank;
	int m_inh_state;
};

// device type definition
<<<<<<< HEAD
extern const device_type A2BUS_SWYFT;

#endif  /* __A2BUS_SWYFT__ */
=======
DECLARE_DEVICE_TYPE(A2BUS_SWYFT, a2bus_swyft_device)

#endif // MAME_BUS_A2BUS_A2SWYFT_H
>>>>>>> upstream/master
