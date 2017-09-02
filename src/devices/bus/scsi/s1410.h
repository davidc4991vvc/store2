// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Xebec S1410 5.25" Winchester Disk Controller emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __S1410__
#define __S1410__

#include "scsihd.h"

class s1410_device  : public scsihd_device
{
public:
	// construction/destruction
	s1410_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

	virtual void ExecCommand();
	virtual void WriteData( UINT8 *data, int dataLength );
	virtual void ReadData( UINT8 *data, int dataLength );
=======
#ifndef MAME_BUS_SCSI_S1410_H
#define MAME_BUS_SCSI_S1410_H

#pragma once

#include "scsihd.h"

class s1410_device : public scsihd_device
{
public:
	// construction/destruction
	s1410_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void ExecCommand() override;
	virtual void WriteData( uint8_t *data, int dataLength ) override;
	virtual void ReadData( uint8_t *data, int dataLength ) override;

protected:
	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type S1410;

#endif
=======
DECLARE_DEVICE_TYPE(S1410, s1410_device)

#endif // MAME_BUS_SCSI_S1410_H
>>>>>>> upstream/master
