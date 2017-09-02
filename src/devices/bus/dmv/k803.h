// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
<<<<<<< HEAD
#pragma once

#ifndef __DMV_K803_H__
#define __DMV_K803_H__

#include "emu.h"
=======
#ifndef MAME_BUS_DMV_K803_H
#define MAME_BUS_DMV_K803_H

#pragma once

>>>>>>> upstream/master
#include "dmvbus.h"
#include "machine/mm58167.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> dmv_k803_device

class dmv_k803_device :
		public device_t,
		public device_dmvslot_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	dmv_k803_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;
	virtual machine_config_constructor device_mconfig_additions() const;

	DECLARE_WRITE_LINE_MEMBER(rtc_irq_w);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void io_read(address_space &space, int ifsel, offs_t offset, UINT8 &data);
	virtual void io_write(address_space &space, int ifsel, offs_t offset, UINT8 data);
=======
	dmv_k803_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	virtual void io_read(address_space &space, int ifsel, offs_t offset, uint8_t &data) override;
	virtual void io_write(address_space &space, int ifsel, offs_t offset, uint8_t data) override;
>>>>>>> upstream/master

	void update_int();

private:
<<<<<<< HEAD
	required_device<mm58167_device> m_rtc;
	required_ioport m_dsw;
	dmvcart_slot_device * m_bus;
	UINT8   m_latch;
=======
	DECLARE_WRITE_LINE_MEMBER(rtc_irq_w);

	required_device<mm58167_device> m_rtc;
	required_ioport m_dsw;
	dmvcart_slot_device * m_bus;
	uint8_t   m_latch;
>>>>>>> upstream/master
	int     m_rtc_int;
};


// device type definition
<<<<<<< HEAD
extern const device_type DMV_K803;

#endif  /* __DMV_K803_H__ */
=======
DECLARE_DEVICE_TYPE(DMV_K803, dmv_k803_device)

#endif // MAME_BUS_DMV_K803_H
>>>>>>> upstream/master
