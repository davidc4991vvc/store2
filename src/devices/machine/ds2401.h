// license:BSD-3-Clause
// copyright-holders:smf
/*
 * DS2401
 *
 * Dallas Semiconductor
 * Silicon Serial Number
 *
 */

<<<<<<< HEAD
#ifndef __DS2401_H__
#define __DS2401_H__
=======
#ifndef MAME_MACHINE_DS2401_H
#define MAME_MACHINE_DS2401_H

#pragma once
>>>>>>> upstream/master

#define MCFG_DS2401_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, DS2401, 0)

<<<<<<< HEAD
#include "emu.h"
=======
>>>>>>> upstream/master

class ds2401_device : public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	ds2401_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	DECLARE_WRITE_LINE_MEMBER( write );
	DECLARE_READ_LINE_MEMBER( read );
	UINT8 direct_read(int index);
=======
	ds2401_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_WRITE_LINE_MEMBER( write );
	DECLARE_READ_LINE_MEMBER( read );
	uint8_t direct_read(int index);
>>>>>>> upstream/master

protected:
	enum {
		SIZE_DATA = 8,

<<<<<<< HEAD
		COMMAND_READROM = 0x33
=======
		COMMAND_READROM = 0x33,
		COMMAND_READROM_COMPAT = 0x0f
>>>>>>> upstream/master
	};

	enum {
		STATE_IDLE,
		STATE_RESET,
		STATE_RESET1,
		STATE_RESET2,
		STATE_COMMAND,
		STATE_READROM
	};

	enum {
		TIMER_MAIN,
		TIMER_RESET
	};

	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// internal state
	int m_state, m_bit, m_shift;
	UINT8 m_byte;
	bool m_rx, m_tx;
	UINT8 m_data[SIZE_DATA];
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// internal state
	int m_state, m_bit, m_shift;
	uint8_t m_byte;
	bool m_rx, m_tx;
	uint8_t m_data[SIZE_DATA];
>>>>>>> upstream/master
	emu_timer *m_timer_main, *m_timer_reset;
	attotime t_samp, t_rdv, t_rstl, t_pdh, t_pdl;

private:
	inline void verboselog(int n_level, const char *s_fmt, ...) ATTR_PRINTF(3,4);
};


// device type definition
<<<<<<< HEAD
extern const device_type DS2401;

#endif
=======
DECLARE_DEVICE_TYPE(DS2401, ds2401_device)

#endif // MAME_MACHINE_DS2401_H
>>>>>>> upstream/master
