// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Compucolor Floppy Disk Drive emulation

*********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __COMPCLR_FLP__
#define __COMPCLR_FLP__
=======
#ifndef MAME_BUS_COMPUCOLOR_FLOPPY_H
#define MAME_BUS_COMPUCOLOR_FLOPPY_H

#pragma once
>>>>>>> upstream/master

#include "bus/rs232/rs232.h"
#include "formats/ccvf_dsk.h"
#include "imagedev/floppy.h"



//**************************************************************************
//  INTERFACE MACROS
//**************************************************************************

#define MCFG_COMPUCOLOR_FLOPPY_PORT_ADD(_tag, _slot_intf, _def_slot) \
	MCFG_DEVICE_ADD(_tag, COMPUCOLOR_FLOPPY_PORT, 0) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, false)



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> device_compucolor_floppy_port_interface

class device_compucolor_floppy_port_interface : public device_rs232_port_interface
{
public:
<<<<<<< HEAD
	device_compucolor_floppy_port_interface(const machine_config &mconfig, device_t &device);
	virtual ~device_compucolor_floppy_port_interface() { }

	virtual void rw_w(int state) = 0;
	virtual void stepper_w(UINT8 data) = 0;
	virtual void select_w(int state) = 0;
=======
	virtual void rw_w(int state) = 0;
	virtual void stepper_w(uint8_t data) = 0;
	virtual void select_w(int state) = 0;

protected:
	device_compucolor_floppy_port_interface(const machine_config &mconfig, device_t &device);
>>>>>>> upstream/master
};


// ======================> compucolor_floppy_port_device

class compucolor_floppy_port_device : public rs232_port_device
{
public:
<<<<<<< HEAD
	compucolor_floppy_port_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ~compucolor_floppy_port_device() { }

	DECLARE_WRITE_LINE_MEMBER( rw_w ) { if (m_dev) m_dev->rw_w(state); }
	void stepper_w(UINT8 data) { if (m_dev) m_dev->stepper_w(data); }
=======
	compucolor_floppy_port_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_WRITE_LINE_MEMBER( rw_w ) { if (m_dev) m_dev->rw_w(state); }
	void stepper_w(uint8_t data) { if (m_dev) m_dev->stepper_w(data); }
>>>>>>> upstream/master
	DECLARE_WRITE_LINE_MEMBER( select_w ) { if (m_dev) m_dev->select_w(state); }

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_config_complete();
=======
	virtual void device_start() override;
	virtual void device_config_complete() override;
>>>>>>> upstream/master

private:
	device_compucolor_floppy_port_interface *m_dev;
};


// ======================> compucolor_floppy_device

<<<<<<< HEAD
class compucolor_floppy_device : public device_t,
	public device_compucolor_floppy_port_interface
{
public:
	// construction/destruction
	compucolor_floppy_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	DECLARE_FLOPPY_FORMATS( floppy_formats );

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// device_serial_port_interface overrides
	virtual void tx(UINT8 state);

	// device_compucolor_floppy_port_interface overrides
	virtual void rw_w(int state);
	virtual void stepper_w(UINT8 data);
	virtual void select_w(int state);

private:
=======
class compucolor_floppy_device : public device_t, public device_compucolor_floppy_port_interface
{
public:
	// construction/destruction
	compucolor_floppy_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	// device_serial_port_interface overrides
	virtual void tx(uint8_t state);

	// device_compucolor_floppy_port_interface overrides
	virtual void rw_w(int state) override;
	virtual void stepper_w(uint8_t data) override;
	virtual void select_w(int state) override;

private:
	DECLARE_FLOPPY_FORMATS( floppy_formats );

>>>>>>> upstream/master
	required_device<floppy_image_device> m_floppy;

	bool read_bit();
	void write_bit(bool bit);

	int m_rw;
	int m_stp;
	int m_sel;

	attotime m_period;

	compucolor_floppy_port_device *m_owner;

	emu_timer *m_timer;
};


// device type definition
<<<<<<< HEAD
extern const device_type COMPUCOLOR_FLOPPY_PORT;
extern const device_type COMPUCOLOR_FLOPPY;
=======
DECLARE_DEVICE_TYPE(COMPUCOLOR_FLOPPY_PORT, compucolor_floppy_port_device)
DECLARE_DEVICE_TYPE(COMPUCOLOR_FLOPPY,      compucolor_floppy_device)
>>>>>>> upstream/master


// slot devices
SLOT_INTERFACE_EXTERN( compucolor_floppy_port_devices );

<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_COMPUCOLOR_FLOPPY_H
>>>>>>> upstream/master
