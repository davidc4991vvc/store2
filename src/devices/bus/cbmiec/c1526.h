// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore 1526/MPS-802/4023 Printer emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __C1526__
#define __C1526__

#include "emu.h"
=======
#ifndef MAME_BUS_CBMIEC_C1626_H
#define MAME_BUS_CBMIEC_C1626_H

#pragma once

>>>>>>> upstream/master
#include "cbmiec.h"
#include "bus/ieee488/ieee488.h"
#include "cpu/m6502/m6504.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> c1526_base_t

class c1526_base_t :  public device_t
{
public:
	// construction/destruction
	c1526_base_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
};


// ======================> c1526_t

class c1526_t :  public c1526_base_t,
					public device_cbm_iec_interface
{
public:
	// construction/destruction
	c1526_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;
	virtual const rom_entry *device_rom_region() const;

protected:
	// device_cbm_iec_interface overrides
	void cbm_iec_atn(int state);
	void cbm_iec_data(int state);
	void cbm_iec_reset(int state);
};


// ======================> c4023_t

class c4023_t :  public c1526_base_t,
					public device_ieee488_interface
{
public:
	// construction/destruction
	c4023_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;
	virtual const rom_entry *device_rom_region() const;

protected:
	// device_ieee488_interface overrides
	virtual void ieee488_atn(int state);
	virtual void ieee488_ifc(int state);
=======
// ======================> c1526_device_base

class c1526_device_base : public device_t
{
protected:
	// construction/destruction
	c1526_device_base(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
};


// ======================> c1526_device

class c1526_device : public c1526_device_base, public device_cbm_iec_interface
{
public:
	// construction/destruction
	c1526_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;
	virtual const tiny_rom_entry *device_rom_region() const override;

	// device_cbm_iec_interface overrides
	void cbm_iec_atn(int state) override;
	void cbm_iec_data(int state) override;
	void cbm_iec_reset(int state) override;
};


// ======================> c4023_device

class c4023_device : public c1526_device_base, public device_ieee488_interface
{
public:
	// construction/destruction
	c4023_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;
	virtual const tiny_rom_entry *device_rom_region() const override;

	// device_ieee488_interface overrides
	virtual void ieee488_atn(int state) override;
	virtual void ieee488_ifc(int state) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type C1526;
extern const device_type MPS802;
extern const device_type C4023;



#endif
=======
DECLARE_DEVICE_TYPE(C1526, c1526_device)
DECLARE_DEVICE_TYPE(C4023, c4023_device)


#endif // MAME_BUS_CBMIEC_C1626_H
>>>>>>> upstream/master
