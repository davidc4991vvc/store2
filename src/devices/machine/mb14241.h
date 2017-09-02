// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/*****************************************************************************

    MB14241 shifter IC emulation

 *****************************************************************************/

<<<<<<< HEAD
#ifndef __MB14241_H__
#define __MB14241_H__
=======
#ifndef MAME_MACHINE_MB14241_H
#define MAME_MACHINE_MB14241_H

#pragma once
>>>>>>> upstream/master


class mb14241_device : public device_t
{
public:
<<<<<<< HEAD
	mb14241_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	DECLARE_WRITE8_MEMBER ( shift_count_w );
	DECLARE_WRITE8_MEMBER ( shift_data_w );
=======
	mb14241_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_WRITE8_MEMBER( shift_count_w );
	DECLARE_WRITE8_MEMBER( shift_data_w );
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER( shift_result_r );

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

<<<<<<< HEAD
	UINT16 m_shift_data;  /* 15 bits only */
	UINT8 m_shift_count;  /* 3 bits */
};

extern const device_type MB14241;
=======
	uint16_t m_shift_data;  /* 15 bits only */
	uint8_t m_shift_count;  /* 3 bits */
};

DECLARE_DEVICE_TYPE(MB14241, mb14241_device)
>>>>>>> upstream/master


/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

#define MCFG_MB14241_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, MB14241, 0)

<<<<<<< HEAD
#endif /* __MB14241_H__ */
=======
#endif // MAME_MACHINE_MB14241_H
>>>>>>> upstream/master
