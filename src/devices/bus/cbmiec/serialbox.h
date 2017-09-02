// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Serial Box 64K Serial Port Buffer emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SERIAL_BOX__
#define __SERIAL_BOX__

#include "emu.h"
=======
#ifndef MAME_BUS_CBMIEC_SERIALBOX_H
#define MAME_BUS_CBMIEC_SERIALBOX_H

#pragma once

>>>>>>> upstream/master
#include "cpu/m6502/m65c02.h"
#include "bus/cbmiec/cbmiec.h"



//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define SERIAL_BOX_TAG          "serialbox"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> serial_box_device

<<<<<<< HEAD
class serial_box_device :  public device_t,
							public device_cbm_iec_interface
{
public:
	// construction/destruction
	serial_box_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_cbm_iec_interface overrides
	void cbm_iec_atn(int state);
	void cbm_iec_data(int state);
	void cbm_iec_reset(int state);
=======
class serial_box_device : public device_t, public device_cbm_iec_interface
{
public:
	// construction/destruction
	serial_box_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_cbm_iec_interface overrides
	void cbm_iec_atn(int state) override;
	void cbm_iec_data(int state) override;
	void cbm_iec_reset(int state) override;
>>>>>>> upstream/master

private:
	required_device<m65c02_device> m_maincpu;
};


// device type definition
<<<<<<< HEAD
extern const device_type SERIAL_BOX;



#endif
=======
DECLARE_DEVICE_TYPE(SERIAL_BOX, serial_box_device)


#endif // MAME_BUS_CBMIEC_SERIALBOX_H
>>>>>>> upstream/master
