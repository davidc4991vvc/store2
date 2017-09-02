// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    a2alfam2.h

    Implementation of the ALF Apple Music II card and compatibles

*********************************************************************/

<<<<<<< HEAD
#ifndef __A2BUS_ALFAM2__
#define __A2BUS_ALFAM2__

#include "emu.h"
=======
#ifndef MAME_BUS_A2BUS_A2ALFAM2_H
#define MAME_BUS_A2BUS_A2ALFAM2_H

#pragma once

>>>>>>> upstream/master
#include "a2bus.h"
#include "sound/sn76496.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class a2bus_sn76489_device:
	public device_t,
	public device_a2bus_card_interface
{
<<<<<<< HEAD
public:
	// construction/destruction
	a2bus_sn76489_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
=======
protected:
	// construction/destruction
	a2bus_sn76489_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

	// overrides of standard a2bus slot functions
	virtual uint8_t read_c0nx(address_space &space, uint8_t offset) override;
	virtual void write_c0nx(address_space &space, uint8_t offset, uint8_t data) override;
	virtual bool take_c800() override;
>>>>>>> upstream/master

	required_device<sn76489_device> m_sn1;
	required_device<sn76489_device> m_sn2;
	required_device<sn76489_device> m_sn3;
	optional_device<sn76489_device> m_sn4;

<<<<<<< HEAD
protected:
	virtual void device_start();
	virtual void device_reset();

	// overrides of standard a2bus slot functions
	virtual UINT8 read_c0nx(address_space &space, UINT8 offset);
	virtual void write_c0nx(address_space &space, UINT8 offset, UINT8 data);
	virtual bool take_c800();

private:
	UINT8 m_latch0, m_latch1, m_latch2, m_latch3;
=======
private:
	uint8_t m_latch0, m_latch1, m_latch2, m_latch3;
>>>>>>> upstream/master

protected:
	bool m_has4thsn;
};

class a2bus_alfam2_device : public a2bus_sn76489_device
{
public:
<<<<<<< HEAD
	a2bus_alfam2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	a2bus_alfam2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class a2bus_aesms_device : public a2bus_sn76489_device
{
public:
<<<<<<< HEAD
	a2bus_aesms_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual machine_config_constructor device_mconfig_additions() const;
};

// device type definition
extern const device_type A2BUS_ALFAM2;
extern const device_type A2BUS_AESMS;

#endif /* __A2BUS_ALFAM2__ */
=======
	a2bus_aesms_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
};

// device type definition
DECLARE_DEVICE_TYPE(A2BUS_ALFAM2, a2bus_alfam2_device)
DECLARE_DEVICE_TYPE(A2BUS_AESMS, a2bus_aesms_device)

#endif // MAME_BUS_A2BUS_A2ALFAM2_H
>>>>>>> upstream/master
