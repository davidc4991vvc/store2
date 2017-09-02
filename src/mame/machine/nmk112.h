// license:BSD-3-Clause
// copyright-holders:Alex W. Jackson
/*************************************************************************

    nmk112.h

**************************************************************************/

<<<<<<< HEAD
#ifndef __NMK112_H__
#define __NMK112_H__
=======
#ifndef MAME_MACHINE_NMK112_H
#define MAME_MACHINE_NMK112_H

#pragma once
>>>>>>> upstream/master

/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

class nmk112_device : public device_t
{
public:
<<<<<<< HEAD
	nmk112_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~nmk112_device() {}
=======
	nmk112_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// static configuration
	static void set_rom0_tag(device_t &device, const char *tag) { downcast<nmk112_device &>(device).m_tag0 = tag; }
	static void set_rom1_tag(device_t &device, const char *tag) { downcast<nmk112_device &>(device).m_tag1 = tag; }
<<<<<<< HEAD
	static void set_page_mask(device_t &device, UINT8 mask) { downcast<nmk112_device &>(device).m_page_mask = ~mask; }
=======
	static void set_page_mask(device_t &device, uint8_t mask) { downcast<nmk112_device &>(device).m_page_mask = ~mask; }
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER( okibank_w );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
=======
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	void do_bankswitch( int offset, int data );
	void postload_bankswitch();

	// internal state

	/* which chips have their sample address table divided into pages */
<<<<<<< HEAD
	UINT8 m_page_mask;

	UINT8 m_current_bank[8];

	const char *m_tag0, *m_tag1;
	UINT8 *m_rom0, *m_rom1;
	int   m_size0, m_size1;
};

extern const device_type NMK112;
=======
	uint8_t m_page_mask;

	uint8_t m_current_bank[8];

	const char *m_tag0, *m_tag1;
	uint8_t *m_rom0, *m_rom1;
	int   m_size0, m_size1;
};

DECLARE_DEVICE_TYPE(NMK112, nmk112_device)
>>>>>>> upstream/master


/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

#define MCFG_NMK112_ROM0(_tag) \
	nmk112_device::set_rom0_tag(*device, _tag);

#define MCFG_NMK112_ROM1(_tag) \
	nmk112_device::set_rom1_tag(*device, _tag);

#define MCFG_NMK112_DISABLE_PAGEMASK(_mask) \
	nmk112_device::set_page_mask(*device, _mask);


<<<<<<< HEAD
#endif /* __NMK112_H__ */
=======
#endif // MAME_MACHINE_NMK112_H
>>>>>>> upstream/master
