// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
/***************************************************************************

  cassette.h - Atari 8 bit cassette player(s)


Known cassette players:
- Atari XC11
- Atari XC12 (no SIO connection for an additional device)

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __A8SIO_CASSETTE_H_
#define __A8SIO_CASSETTE_H_
=======
#ifndef MAME_BUS_A800_CASSETTE_H
#define MAME_BUS_A800_CASSETTE_H

#pragma once
>>>>>>> upstream/master


#include "a8sio.h"
#include "imagedev/cassette.h"


class a8sio_cassette_device
	: public device_t
	, public device_a8sio_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	a8sio_cassette_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	a8sio_cassette_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	virtual DECLARE_WRITE_LINE_MEMBER( motor_w );

protected:
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	a8sio_cassette_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE_LINE_MEMBER( motor_w ) override;

protected:
	a8sio_cassette_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

	required_device<cassette_image_device> m_cassette;
	emu_timer *m_read_timer;

<<<<<<< HEAD
	UINT8 m_old_cass_signal;
	UINT8 m_signal_count;
};

// device type definition
extern const device_type A8SIO_CASSETTE;


#endif
=======
	uint8_t m_old_cass_signal;
	uint8_t m_signal_count;
};

// device type definition
DECLARE_DEVICE_TYPE(A8SIO_CASSETTE, a8sio_cassette_device)


#endif // MAME_BUS_A800_CASSETTE_H
>>>>>>> upstream/master
