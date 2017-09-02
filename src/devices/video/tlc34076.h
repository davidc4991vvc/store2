// license:BSD-3-Clause
// copyright-holders:Philip Bennett
/***************************************************************************

    tlc34076.h

    Basic implementation of the TLC34076 palette chip and similar
    compatible chips.

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __TLC34076_H__
#define __TLC34076_H__


/***************************************************************************
    CONSTANTS
***************************************************************************/

enum tlc34076_bits
{
	TLC34076_6_BIT = 6,
	TLC34076_8_BIT = 8
};
=======
#ifndef MAME_VIDEO_TLC34076_H
#define MAME_VIDEO_TLC34076_H

#pragma once
>>>>>>> upstream/master


/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

class tlc34076_device : public device_t
{
public:
<<<<<<< HEAD
	// construction/destruction
	tlc34076_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	enum tlc34076_bits
	{
		TLC34076_6_BIT = 6,
		TLC34076_8_BIT = 8
	};

	// construction/destruction
	tlc34076_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// static configuration helpers
	static void static_set_bits(device_t &device, tlc34076_bits bits);

	// public interface
	const rgb_t *get_pens();
	DECLARE_READ8_MEMBER(read);
	DECLARE_WRITE8_MEMBER(write);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

private:
	// internal state
	UINT8 m_local_paletteram[0x300];
	UINT8 m_regs[0x10];
	UINT8 m_palettedata[3];
	UINT8 m_writeindex;
	UINT8 m_readindex;
	UINT8 m_dacbits;
=======
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	// internal state
	uint8_t m_local_paletteram[0x300];
	uint8_t m_regs[0x10];
	uint8_t m_palettedata[3];
	uint8_t m_writeindex;
	uint8_t m_readindex;
	uint8_t m_dacbits;
>>>>>>> upstream/master
	rgb_t m_pens[0x100];
};


/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

<<<<<<< HEAD
#define MCFG_TLC34076_ADD(_tag, _bits) \
	MCFG_DEVICE_ADD(_tag, TLC34076, 0) \
	tlc34076_device::static_set_bits(*device, _bits);


extern const device_type TLC34076;


#endif /* __TLC34076_H__ */
=======
#define MCFG_TLC34076_ADD(tag, bits) \
	MCFG_DEVICE_ADD((tag), TLC34076, 0) \
	tlc34076_device::static_set_bits(*device, (tlc34076_device::bits));


DECLARE_DEVICE_TYPE(TLC34076, tlc34076_device)

#endif // MAME_VIDEO_TLC34076_H
>>>>>>> upstream/master
