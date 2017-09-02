// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Nintendo Family Computer Mahjong Panel

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __NES_MJPANEL__
#define __NES_MJPANEL__


#include "emu.h"
#include "ctrl.h"

=======
#ifndef MAME_BUS_NES_CTRL_MJPANEL_H
#define MAME_BUS_NES_CTRL_MJPANEL_H

#pragma once

#include "ctrl.h"


>>>>>>> upstream/master
//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> nes_mjpanel_device

class nes_mjpanel_device : public device_t,
							public device_nes_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_mjpanel_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual UINT8 read_exp(offs_t offset);
	virtual void write(UINT8 data);

private:
	required_ioport_array<4> m_panel;
	UINT32 m_latch;
=======
	nes_mjpanel_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual ioport_constructor device_input_ports() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual uint8_t read_exp(offs_t offset) override;
	virtual void write(uint8_t data) override;

private:
	required_ioport_array<4> m_panel;
	uint32_t m_latch;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type NES_MJPANEL;


#endif
=======
DECLARE_DEVICE_TYPE(NES_MJPANEL, nes_mjpanel_device)


#endif // MAME_BUS_NES_CTRL_MJPANEL_H
>>>>>>> upstream/master
