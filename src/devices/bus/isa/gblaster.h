// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
<<<<<<< HEAD
#pragma once

#ifndef __ISA_GAME_BLASTER_H__
#define __ISA_GAME_BLASTER_H__

#include "emu.h"
=======
#ifndef MAME_BUS_ISA_GBLASTER_H
#define MAME_BUS_ISA_GBLASTER_H

#pragma once

>>>>>>> upstream/master
#include "isa.h"
#include "sound/saa1099.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> isa8_gblaster_device

class isa8_gblaster_device :
		public device_t,
		public device_isa8_card_interface
{
public:
<<<<<<< HEAD
		// construction/destruction
		isa8_gblaster_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

		// optional information overrides
		virtual machine_config_constructor device_mconfig_additions() const;

		DECLARE_READ8_MEMBER(saa1099_16_r);
		DECLARE_WRITE8_MEMBER(saa1099_1_16_w);
		DECLARE_WRITE8_MEMBER(saa1099_2_16_w);
		DECLARE_READ8_MEMBER(detect_r);
		DECLARE_WRITE8_MEMBER(detect_w);
protected:
		// device-level overrides
		virtual void device_start();
		virtual void device_reset();
private:
		// internal state
		required_device<saa1099_device> m_saa1099_1;
		required_device<saa1099_device> m_saa1099_2;
		UINT8 detect_reg;
=======
	// construction/destruction
	isa8_gblaster_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ8_MEMBER(saa1099_16_r);
	DECLARE_WRITE8_MEMBER(saa1099_1_16_w);
	DECLARE_WRITE8_MEMBER(saa1099_2_16_w);
	DECLARE_READ8_MEMBER(detect_r);
	DECLARE_WRITE8_MEMBER(detect_w);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

private:
	// internal state
	required_device<saa1099_device> m_saa1099_1;
	required_device<saa1099_device> m_saa1099_2;
	uint8_t detect_reg;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type ISA8_GAME_BLASTER;

#endif  /* __ISA_GAME_BLASTER_H__ */
=======
DECLARE_DEVICE_TYPE(ISA8_GAME_BLASTER, isa8_gblaster_device)

#endif // MAME_BUS_ISA_GBLASTER_H
>>>>>>> upstream/master
