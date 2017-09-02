// license:BSD-3-Clause
// copyright-holders:smf
/***************************************************************************

    Fujistu MB3773

    Power Supply Monitor with Watch Dog Timer (i.e. Reset IC)

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __MB3773_H__
#define __MB3773_H__
=======
#ifndef MAME_MACHINE_MB3773_H
#define MAME_MACHINE_MB3773_H

#pragma once
>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_MB3773_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, MB3773, 0)


// ======================> mb3773_device

<<<<<<< HEAD
class mb3773_device :
	public device_t
{
public:
	// construction/destruction
	mb3773_device( const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock );
=======
class mb3773_device : public device_t
{
public:
	// construction/destruction
	mb3773_device( const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock );
>>>>>>> upstream/master

	// I/O operations
	WRITE_LINE_MEMBER( write_line_ck );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
>>>>>>> upstream/master

private:
	void reset_timer();

	// internal state
	emu_timer *m_watchdog_timer;
	int m_ck;
};


// device type definition
<<<<<<< HEAD
extern const device_type MB3773;

#endif
=======
DECLARE_DEVICE_TYPE(MB3773, mb3773_device)

#endif // MAME_MACHINE_MB3773_H
>>>>>>> upstream/master
