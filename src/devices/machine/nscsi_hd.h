// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#ifndef __NSCSI_HD_H__
#define __NSCSI_HD_H__
=======
#ifndef MAME_MACHINE_NSCSI_HD_H
#define MAME_MACHINE_NSCSI_HD_H

#pragma once
>>>>>>> upstream/master

#include "machine/nscsi_bus.h"
#include "harddisk.h"

class nscsi_harddisk_device : public nscsi_full_device
{
public:
<<<<<<< HEAD
	nscsi_harddisk_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	nscsi_harddisk_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	virtual void device_start();
	virtual void device_reset();

	virtual void scsi_command();
	virtual UINT8 scsi_get_data(int id, int pos);
	virtual void scsi_put_data(int buf, int offset, UINT8 data);

	UINT8 block[512];
=======
	nscsi_harddisk_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	nscsi_harddisk_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

	virtual void scsi_command() override;
	virtual uint8_t scsi_get_data(int id, int pos) override;
	virtual void scsi_put_data(int buf, int offset, uint8_t data) override;

	uint8_t block[512];
>>>>>>> upstream/master
	hard_disk_file *harddisk;
	int lba, cur_lba, blocks;
	int bytes_per_sector;
};

<<<<<<< HEAD
extern const device_type NSCSI_HARDDISK;

#endif
=======
DECLARE_DEVICE_TYPE(NSCSI_HARDDISK, nscsi_harddisk_device)

#endif // MAME_MACHINE_NSCSI_HD_H
>>>>>>> upstream/master
