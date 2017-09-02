// license:BSD-3-Clause
// copyright-holders:R. Belmont,Kevin Horton
<<<<<<< HEAD
#pragma once

#ifndef __ISA_MPU401_H__
#define __ISA_MPU401_H__

#include "emu.h"
=======
#ifndef MAME_BUS_ISA_MPU401_H
#define MAME_BUS_ISA_MPU401_H

#pragma once

>>>>>>> upstream/master
#include "isa.h"
#include "machine/mpu401.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> isa8_mpu401_device

class isa8_mpu401_device :
		public device_t,
		public device_isa8_card_interface
{
public:
<<<<<<< HEAD
		// construction/destruction
		isa8_mpu401_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

		required_device<mpu401_device> m_mpu401;

		// called back by the MPU401 core to set the IRQ line state
		DECLARE_WRITE_LINE_MEMBER(mpu_irq_out);

		// optional information overrides
protected:
		// device-level overrides
		virtual void device_start();
		virtual void device_reset();
		virtual machine_config_constructor device_mconfig_additions() const;

private:
		// internal state
=======
	// construction/destruction
	isa8_mpu401_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

private:
	// called back by the MPU401 core to set the IRQ line state
	DECLARE_WRITE_LINE_MEMBER(mpu_irq_out);

	required_device<mpu401_device> m_mpu401;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type ISA8_MPU401;

#endif  /* __ISA_MPU401_H__ */
=======
DECLARE_DEVICE_TYPE(ISA8_MPU401, isa8_mpu401_device)

#endif // MAME_BUS_ISA_MPU401_H
>>>>>>> upstream/master
