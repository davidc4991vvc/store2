// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    a1cassette.h

    Apple I Cassette Interface

*********************************************************************/

<<<<<<< HEAD
#ifndef __A1BUS_CASSETTE__
#define __A1BUS_CASSETTE__
=======
#ifndef MAME_BUS_A1BUS_A1CASSETTE_H
#define MAME_BUS_A1BUS_A1CASSETTE_H

#pragma once
>>>>>>> upstream/master

#include "a1bus.h"
#include "imagedev/cassette.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class a1bus_cassette_device:
	public device_t,
	public device_a1bus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	a1bus_cassette_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	a1bus_cassette_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;

	optional_device<cassette_image_device> m_cassette;
=======
	a1bus_cassette_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(cassette_r);
	DECLARE_WRITE8_MEMBER(cassette_w);

protected:
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	void cassette_toggle_output();

private:
	UINT8 *m_rom;
=======
	a1bus_cassette_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;
	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;


	void cassette_toggle_output();

	optional_device<cassette_image_device> m_cassette;

private:
	uint8_t *m_rom;
>>>>>>> upstream/master
	int m_cassette_output_flipflop;
};

// device type definition
<<<<<<< HEAD
extern const device_type A1BUS_CASSETTE;

#endif  /* __A1BUS_CASSETTE__ */
=======
DECLARE_DEVICE_TYPE(A1BUS_CASSETTE, a1bus_cassette_device)

#endif  // MAME_BUS_A1BUS_A1CASSETTE_H
>>>>>>> upstream/master
