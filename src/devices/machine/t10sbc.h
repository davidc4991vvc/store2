// license:BSD-3-Clause
// copyright-holders:smf
/***************************************************************************

t10sbc.h

***************************************************************************/

<<<<<<< HEAD
#ifndef _T10SBC_H_
#define _T10SBC_H_
=======
#ifndef MAME_MACHINE_T10SBC_H
#define MAME_MACHINE_T10SBC_H

#pragma once
>>>>>>> upstream/master

#include "t10spc.h"
#include "imagedev/harddriv.h"

class t10sbc : public virtual t10spc
{
public:
<<<<<<< HEAD
	virtual void SetDevice( void *device );
	virtual void GetDevice( void **device );
	virtual void ExecCommand();
	virtual void WriteData( UINT8 *data, int dataLength );
	virtual void ReadData( UINT8 *data, int dataLength );

protected:
	virtual void t10_start(device_t &device);
	virtual void t10_reset();

	harddisk_image_device *m_image;

	UINT32 m_lba;
	UINT32 m_blocks;
=======
	t10sbc()
		: t10spc(), m_image(nullptr), m_lba(0), m_blocks(0), m_disk(nullptr), m_device(nullptr)
	{
	}

	virtual void SetDevice( void *device ) override;
	virtual void GetDevice( void **device ) override;
	virtual void ExecCommand() override;
	virtual void WriteData( uint8_t *data, int dataLength ) override;
	virtual void ReadData( uint8_t *data, int dataLength ) override;

protected:
	virtual void t10_start(device_t &device) override;
	virtual void t10_reset() override;

	harddisk_image_device *m_image;

	uint32_t m_lba;
	uint32_t m_blocks;
>>>>>>> upstream/master

	hard_disk_file *m_disk;
	device_t *m_device;
};

<<<<<<< HEAD
#endif
=======
#endif // MAME_MACHINE_T10SBC_H
>>>>>>> upstream/master
