// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Shugart SA1403D Winchester Disk Controller emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SA1403D__
#define __SA1403D__
=======
#ifndef MAME_BUS_SCSI_SA1403D_H
#define MAME_BUS_SCSI_SA1403D_H

#pragma once
>>>>>>> upstream/master

#include "scsihd.h"
#include "imagedev/harddriv.h"

class sa1403d_device  : public scsihd_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sa1403d_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	virtual void ExecCommand();
	virtual void WriteData( UINT8 *data, int dataLength );
=======
	sa1403d_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void ExecCommand() override;
	virtual void WriteData( uint8_t *data, int dataLength ) override;

protected:
	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type SA1403D;

#endif
=======
DECLARE_DEVICE_TYPE(SA1403D, sa1403d_device)

#endif // MAME_BUS_SCSI_SA1403D_H
>>>>>>> upstream/master
