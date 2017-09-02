// license:BSD-3-Clause
// copyright-holders:smf, Angelo Salese
/***************************************************************************

 gdrom.h

***************************************************************************/

<<<<<<< HEAD
#ifndef _GDROM_H_
#define _GDROM_H_
=======
#ifndef MAME_MACHINE_GDROM_H
#define MAME_MACHINE_GDROM_H

#pragma once
>>>>>>> upstream/master

#include "machine/atapicdr.h"

class gdrom_device : public atapi_cdrom_device
{
public:
<<<<<<< HEAD
	gdrom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// Sega GD-ROM handler

	virtual void ExecCommand();
	virtual void WriteData( UINT8 *data, int dataLength );
	virtual void ReadData( UINT8 *data, int dataLength );

protected:
	virtual void process_buffer();

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

private:
	UINT8 GDROM_Cmd11_Reply[32];
	UINT32 read_type;   // for command 0x30 only
	UINT32 data_select; // for command 0x30 only
	UINT32 transferOffset;
};

// device type definition
extern const device_type GDROM;

#endif
=======
	gdrom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// Sega GD-ROM handler

	virtual void ExecCommand() override;
	virtual void WriteData( uint8_t *data, int dataLength ) override;
	virtual void ReadData( uint8_t *data, int dataLength ) override;

protected:
	virtual void process_buffer() override;

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t GDROM_Cmd11_Reply[32];
	uint32_t read_type;   // for command 0x30 only
	uint32_t data_select; // for command 0x30 only
	uint32_t transferOffset;
};

DECLARE_DEVICE_TYPE(GDROM, gdrom_device)

#endif // MAME_MACHINE_GDROM_H
>>>>>>> upstream/master
