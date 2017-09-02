// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#pragma once

#ifndef __RF5C296_H__
#define __RF5C296_H__
=======
#ifndef MAME_MACHINE_RF5C296_H
#define MAME_MACHINE_RF5C296_H

#pragma once
>>>>>>> upstream/master

#include "pccard.h"

#define MCFG_RF5C296_SLOT(name) \
	rf5c296_device::set_pccard_name(*device, name);

class rf5c296_device : public device_t
{
public:
<<<<<<< HEAD
	rf5c296_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	rf5c296_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// static configuration helpers
	static void set_pccard_name(device_t &device, const char *name) { downcast<rf5c296_device &>(device).m_pccard_name = name; }

	DECLARE_WRITE16_MEMBER(io_w);
	DECLARE_READ16_MEMBER(io_r);
	DECLARE_READ16_MEMBER(mem_r);
	DECLARE_WRITE16_MEMBER(mem_w);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();

private:
	private:
	void reg_w(ATTR_UNUSED UINT8 reg, UINT8 data);
	UINT8 reg_r(ATTR_UNUSED UINT8 reg);
=======
	virtual void device_start() override;

private:
	void reg_w(ATTR_UNUSED uint8_t reg, uint8_t data);
	uint8_t reg_r(ATTR_UNUSED uint8_t reg);
>>>>>>> upstream/master

	unsigned char m_rf5c296_reg;
	pccard_slot_device *m_pccard;
	const char *m_pccard_name;
};

<<<<<<< HEAD
extern const device_type RF5C296;

#endif
=======
DECLARE_DEVICE_TYPE(RF5C296, rf5c296_device)

#endif // MAME_MACHINE_RF5C296_H
>>>>>>> upstream/master
