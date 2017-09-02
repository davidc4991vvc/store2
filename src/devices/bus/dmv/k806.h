// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
<<<<<<< HEAD
#pragma once

#ifndef __DMV_K806_H__
#define __DMV_K806_H__

#include "emu.h"
=======
#ifndef MAME_BUS_DMV_K806_H
#define MAME_BUS_DMV_K806_H

#pragma once

>>>>>>> upstream/master
#include "dmvbus.h"
#include "cpu/mcs48/mcs48.h"


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> dmv_k806_device

class dmv_k806_device :
		public device_t,
		public device_dmvslot_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	dmv_k806_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual ioport_constructor device_input_ports() const;
	virtual machine_config_constructor device_mconfig_additions() const;

	DECLARE_READ8_MEMBER(portt1_r);
=======
	dmv_k806_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual ioport_constructor device_input_ports() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	virtual void io_read(address_space &space, int ifsel, offs_t offset, uint8_t &data) override;
	virtual void io_write(address_space &space, int ifsel, offs_t offset, uint8_t data) override;

private:
	DECLARE_READ_LINE_MEMBER(portt1_r);
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(port1_r);
	DECLARE_WRITE8_MEMBER(port2_w);

	TIMER_DEVICE_CALLBACK_MEMBER(mouse_timer);

<<<<<<< HEAD
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void io_read(address_space &space, int ifsel, offs_t offset, UINT8 &data);
	virtual void io_write(address_space &space, int ifsel, offs_t offset, UINT8 data);

private:
=======
>>>>>>> upstream/master
	required_device<upi41_cpu_device> m_mcu;
	required_ioport m_jumpers;
	required_ioport m_mouse_buttons;
	required_ioport m_mouse_x;
	required_ioport m_mouse_y;
	dmvcart_slot_device * m_bus;

	struct
	{
		int phase;
		int x;
		int y;
		int prev_x;
		int prev_y;
		int xa;
		int xb;
		int ya;
		int yb;
	} m_mouse;
};


// device type definition
<<<<<<< HEAD
extern const device_type DMV_K806;

#endif  /* __DMV_K806_H__ */
=======
DECLARE_DEVICE_TYPE(DMV_K806, dmv_k806_device)

#endif // MAME_BUS_DMV_K806_H
>>>>>>> upstream/master
