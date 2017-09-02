// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Nintendo Super Famicom - Epoch Barcode Battler

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SNES_BCBATTLE__
#define __SNES_BCBATTLE__


#include "emu.h"
=======
#ifndef MAME_BUS_SNES_CTRL_BCBATTLE_H
#define MAME_BUS_SNES_CTRL_BCBATTLE_H

#pragma once


>>>>>>> upstream/master
#include "ctrl.h"
#include "machine/bcreader.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> snes_bcbattle_device

class snes_bcbattle_device : public device_t,
							public device_snes_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	snes_bcbattle_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual UINT8 read_pin4();
	virtual void write_strobe(UINT8 data);
	virtual void port_poll();
=======
	snes_bcbattle_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	virtual void device_add_mconfig(machine_config &config) override;

	virtual uint8_t read_pin4() override;
	virtual void write_strobe(uint8_t data) override;
	virtual void port_poll() override;
>>>>>>> upstream/master

	int read_current_bit();

private:
<<<<<<< HEAD

	static const device_timer_id TIMER_BATTLER = 1;
	required_device<barcode_reader_device> m_reader;
	UINT8 m_current_barcode[20];
=======
	static constexpr device_timer_id TIMER_BATTLER = 1;

	required_device<barcode_reader_device> m_reader;
	uint8_t m_current_barcode[20];
>>>>>>> upstream/master
	int m_pending_code, m_new_code, m_transmitting, m_cur_bit, m_cur_byte;
	emu_timer *battler_timer;

	int m_strobe, m_idx;
};

// device type definition
<<<<<<< HEAD
extern const device_type SNES_BARCODE_BATTLER;

#endif
=======
DECLARE_DEVICE_TYPE(SNES_BARCODE_BATTLER, snes_bcbattle_device)

#endif // MAME_BUS_SNES_CTRL_BCBATTLE_H
>>>>>>> upstream/master
