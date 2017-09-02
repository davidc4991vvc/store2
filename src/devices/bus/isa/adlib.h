// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
<<<<<<< HEAD
#pragma once

#ifndef __ISA_ADLIB_H__
#define __ISA_ADLIB_H__

#include "emu.h"
=======
#ifndef MAME_BUS_ISA_ADLIB_H
#define MAME_BUS_ISA_ADLIB_H

#pragma once

>>>>>>> upstream/master
#include "isa.h"
#include "sound/3812intf.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> isa8_adlib_device

class isa8_adlib_device :
<<<<<<< HEAD
		public device_t,
		public device_isa8_card_interface
{
public:
		// construction/destruction
		isa8_adlib_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

		// optional information overrides
		virtual machine_config_constructor device_mconfig_additions() const;

		DECLARE_READ8_MEMBER(ym3812_16_r);
		DECLARE_WRITE8_MEMBER(ym3812_16_w);
protected:
		// device-level overrides
		virtual void device_start();
		virtual void device_reset();
private:
		// internal state
		required_device<ym3812_device> m_ym3812;
=======
	public device_t,
	public device_isa8_card_interface
{
public:
	// construction/destruction
	isa8_adlib_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ8_MEMBER(ym3812_16_r);
	DECLARE_WRITE8_MEMBER(ym3812_16_w);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

private:
	// internal state
	required_device<ym3812_device> m_ym3812;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type ISA8_ADLIB;

#endif  /* __ISA_ADLIB_H__ */
=======
DECLARE_DEVICE_TYPE(ISA8_ADLIB, isa8_adlib_device)

#endif // MAME_BUS_ISA_ADLIB_H
>>>>>>> upstream/master
