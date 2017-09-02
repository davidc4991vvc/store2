// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Nintendo Family Computer - Bandai Family Trainer Mat

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __NES_FTRAINER__
#define __NES_FTRAINER__


#include "emu.h"
#include "ctrl.h"

=======
#ifndef MAME_BUS_NES_CTRL_FTRAINER_H
#define MAME_BUS_NES_CTRL_FTRAINER_H

#pragma once

#include "ctrl.h"


>>>>>>> upstream/master
//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> nes_ftrainer_device

class nes_ftrainer_device : public device_t,
							public device_nes_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ftrainer_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual UINT8 read_exp(offs_t offset);
	virtual void write(UINT8 data);

private:
	required_ioport_array<4> m_trainer;
	UINT8 m_row_scan;
=======
	nes_ftrainer_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual ioport_constructor device_input_ports() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual uint8_t read_exp(offs_t offset) override;
	virtual void write(uint8_t data) override;

private:
	required_ioport_array<4> m_trainer;
	uint8_t m_row_scan;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type NES_FTRAINER;


#endif
=======
DECLARE_DEVICE_TYPE(NES_FTRAINER, nes_ftrainer_device)


#endif // MAME_BUS_NES_CTRL_FTRAINER_H
>>>>>>> upstream/master
