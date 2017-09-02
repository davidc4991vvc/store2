// license:BSD-3-Clause
// copyright-holders:smf
/***************************************************************************

    cr589.h

    Matsushita CR589

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __CR589_H__
#define __CR589_H__

#include "atapicdr.h"
#include "t10mmc.h"
=======
#ifndef MAME_MACHINE_CR589_H
#define MAME_MACHINE_CR589_H

#pragma once

#include "atapicdr.h"
>>>>>>> upstream/master

class matsushita_cr589_device : public atapi_cdrom_device,
	public device_nvram_interface
{
public:
<<<<<<< HEAD
	matsushita_cr589_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual void ExecCommand();
	virtual void WriteData( UINT8 *data, int dataLength );
	virtual void ReadData( UINT8 *data, int dataLength );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_nvram_interface overrides
	virtual void nvram_default();
	virtual void nvram_read(emu_file &file);
	virtual void nvram_write(emu_file &file);

private:
	int download;
	UINT8 buffer[ 65536 ];
=======
	matsushita_cr589_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void ExecCommand() override;
	virtual void WriteData( uint8_t *data, int dataLength ) override;
	virtual void ReadData( uint8_t *data, int dataLength ) override;
	// ksys573 changes discs without telling the cdrom_image_device
	virtual void process_buffer() override { atapi_hle_device::process_buffer(); }

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_nvram_interface overrides
	virtual void nvram_default() override;
	virtual void nvram_read(emu_file &file) override;
	virtual void nvram_write(emu_file &file) override;

private:
	int download;
	uint8_t buffer[ 65536 ];
>>>>>>> upstream/master
	int bufferOffset;
};

// device type definition
<<<<<<< HEAD
extern const device_type CR589;

#endif
=======
DECLARE_DEVICE_TYPE(CR589, matsushita_cr589_device)

#endif // MAME_MACHINE_CR589_H
>>>>>>> upstream/master
