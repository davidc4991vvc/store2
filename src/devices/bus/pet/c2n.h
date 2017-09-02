// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore C2N/1530/1531 Datassette emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __C2N__
#define __C2N__

#include "emu.h"
=======
#ifndef MAME_BUS_PET_C2N_H
#define MAME_BUS_PET_C2N_H

#pragma once

>>>>>>> upstream/master
#include "cass.h"
#include "formats/cbm_tap.h"
#include "imagedev/cassette.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c2n_device

class c2n_device :  public device_t,
					public device_pet_datassette_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c2n_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	c2n_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// device_pet_datassette_port_interface overrides
	virtual int datassette_read();
	virtual void datassette_write(int state);
	virtual int datassette_sense();
	virtual void datassette_motor(int state);
=======
	c2n_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	c2n_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	// device_pet_datassette_port_interface overrides
	virtual int datassette_read() override;
	virtual void datassette_write(int state) override;
	virtual int datassette_sense() override;
	virtual void datassette_motor(int state) override;
>>>>>>> upstream/master

private:
	required_device<cassette_image_device> m_cassette;

	bool m_motor;

	// timers
	emu_timer *m_read_timer;
};


// ======================> c1530_device

class c1530_device :  public c2n_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	c1530_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	c1530_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};


// ======================> c1531_device

class c1531_device :  public c2n_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	c1531_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	c1531_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type C2N;
extern const device_type C1530;
extern const device_type C1531;



#endif
=======
DECLARE_DEVICE_TYPE(C2N,   c2n_device)
DECLARE_DEVICE_TYPE(C1530, c1530_device)
DECLARE_DEVICE_TYPE(C1531, c1531_device)

#endif // MAME_BUS_PET_C2N_H
>>>>>>> upstream/master
