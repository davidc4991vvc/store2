// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#ifndef __NSCSI_CD_H__
#define __NSCSI_CD_H__
=======
#ifndef MAME_MACHINE_NSCSI_CD_H
#define MAME_MACHINE_NSCSI_CD_H

#pragma once
>>>>>>> upstream/master

#include "machine/nscsi_bus.h"
#include "cdrom.h"

class nscsi_cdrom_device : public nscsi_full_device
{
public:
<<<<<<< HEAD
	nscsi_cdrom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	virtual void device_start();
	virtual void device_reset();

	virtual void scsi_command();
	virtual UINT8 scsi_get_data(int id, int pos);

private:
	UINT8 block[2048];
=======
	nscsi_cdrom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

	virtual void scsi_command() override;
	virtual uint8_t scsi_get_data(int id, int pos) override;

private:
	uint8_t block[2048];
>>>>>>> upstream/master
	cdrom_file *cdrom;
	int bytes_per_sector;
	int lba, cur_lba, blocks;

	void return_no_cd();
};

<<<<<<< HEAD
extern const device_type NSCSI_CDROM;

#endif
=======
DECLARE_DEVICE_TYPE(NSCSI_CDROM, nscsi_cdrom_device)

#endif // MAME_MACHINE_NSCSI_CD_H
>>>>>>> upstream/master
