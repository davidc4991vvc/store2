// license:BSD-3-Clause
// copyright-holders:Eric Smith
/*
 * mathbox.h: math box simulation (Battlezone/Red Baron/Tempest)
 *
 * Copyright Eric Smith
 *
 */
<<<<<<< HEAD
=======
#ifndef MAME_MACHINE_MATHBOX_H
#define MAME_MACHINE_MATHBOX_H

#pragma once
>>>>>>> upstream/master

/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

#define MCFG_MATHBOX_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, MATHBOX, 0)


/* ----- device interface ----- */
class mathbox_device : public device_t
{
public:
<<<<<<< HEAD
	mathbox_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	mathbox_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER( go_w );
	DECLARE_READ8_MEMBER( status_r );
	DECLARE_READ8_MEMBER( lo_r );
	DECLARE_READ8_MEMBER( hi_r );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();
=======
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

	private:
	// internal state

	/* math box scratch registers */
<<<<<<< HEAD
	INT16 m_reg[16];

	/* math box result */
	INT16 m_result;
};

extern const device_type MATHBOX;
=======
	int16_t m_reg[16];

	/* math box result */
	int16_t m_result;
};

DECLARE_DEVICE_TYPE(MATHBOX, mathbox_device)

#endif // MAME_MACHINE_MATHBOX_H
>>>>>>> upstream/master
