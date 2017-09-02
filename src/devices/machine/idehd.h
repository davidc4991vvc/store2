// license:BSD-3-Clause
// copyright-holders:smf
/***************************************************************************

    idehd.h

    IDE Harddisk

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __IDEHD_H__
#define __IDEHD_H__
=======
#ifndef MAME_MACHINE_IDEHD_H
#define MAME_MACHINE_IDEHD_H

#pragma once
>>>>>>> upstream/master

#include "atahle.h"
#include "harddisk.h"
#include "imagedev/harddriv.h"

class ata_mass_storage_device : public ata_hle_device
{
public:
<<<<<<< HEAD
	ata_mass_storage_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock,const char *shortname, const char *source);

	UINT16 *identify_device_buffer() { return m_identify_buffer; }

	void set_master_password(const UINT8 *password)
	{
		m_master_password = password;
		m_master_password_enable = (password != NULL);
	}

	void set_user_password(const UINT8 *password)
	{
		m_user_password = password;
		m_user_password_enable = (password != NULL);
	}

protected:
	virtual void device_start();

	virtual int read_sector(UINT32 lba, void *buffer) = 0;
	virtual int write_sector(UINT32 lba, const void *buffer) = 0;
=======
	uint16_t *identify_device_buffer() { return m_identify_buffer; }

	void set_master_password(const uint8_t *password)
	{
		m_master_password = password;
		m_master_password_enable = (password != nullptr);
	}

	void set_user_password(const uint8_t *password)
	{
		m_user_password = password;
		m_user_password_enable = (password != nullptr);
	}

protected:
	ata_mass_storage_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;

	virtual int read_sector(uint32_t lba, void *buffer) = 0;
	virtual int write_sector(uint32_t lba, const void *buffer) = 0;
>>>>>>> upstream/master
	virtual attotime seek_time();

	void ide_build_identify_device();

	static const int IDE_DISK_SECTOR_SIZE = 512;
<<<<<<< HEAD
	virtual int sector_length() { return IDE_DISK_SECTOR_SIZE; }
	virtual void process_buffer();
	virtual void fill_buffer();
	virtual bool is_ready() { return true; }
	virtual void process_command();
	virtual void finished_command();
	virtual void perform_diagnostic();
	virtual void signature();

	int m_can_identify_device;
	UINT16          m_num_cylinders;
	UINT8           m_num_sectors;
	UINT8           m_num_heads;

	virtual UINT32 lba_address();

private:
	void set_geometry(UINT8 sectors, UINT8 heads) { m_num_sectors = sectors; m_num_heads = heads; }
=======
	virtual int sector_length() override { return IDE_DISK_SECTOR_SIZE; }
	virtual void process_buffer() override;
	virtual void fill_buffer() override;
	virtual bool is_ready() override { return true; }
	virtual void process_command() override;
	virtual void finished_command() override;
	virtual void perform_diagnostic() override;
	virtual void signature() override;

	int m_can_identify_device;
	uint16_t          m_num_cylinders;
	uint8_t           m_num_sectors;
	uint8_t           m_num_heads;

	virtual uint32_t lba_address();

private:
	void set_geometry(uint8_t sectors, uint8_t heads) { m_num_sectors = sectors; m_num_heads = heads; }
>>>>>>> upstream/master
	void finished_read();
	void finished_write();
	void next_sector();
	void security_error();
	void read_first_sector();
<<<<<<< HEAD
	void soft_reset();

	UINT32          m_cur_lba;
	UINT16          m_block_count;
	UINT16          m_sectors_until_int;

	UINT8           m_master_password_enable;
	UINT8           m_user_password_enable;
	const UINT8 *   m_master_password;
	const UINT8 *   m_user_password;
=======
	void soft_reset() override;

	uint32_t          m_cur_lba;
	uint16_t          m_block_count;
	uint16_t          m_sectors_until_int;

	uint8_t           m_master_password_enable;
	uint8_t           m_user_password_enable;
	const uint8_t *   m_master_password;
	const uint8_t *   m_user_password;
>>>>>>> upstream/master
};

// ======================> ide_hdd_device

class ide_hdd_device : public ata_mass_storage_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	ide_hdd_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	ide_hdd_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	virtual int read_sector(UINT32 lba, void *buffer) { if (m_disk == NULL) return 0; return hard_disk_read(m_disk, lba, buffer); }
	virtual int write_sector(UINT32 lba, const void *buffer) { if (m_disk == NULL) return 0; return hard_disk_write(m_disk, lba, buffer); }
	virtual UINT8 calculate_status();
=======
	ide_hdd_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	ide_hdd_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	virtual int read_sector(uint32_t lba, void *buffer) override { return !m_disk ? 0 : hard_disk_read(m_disk, lba, buffer); }
	virtual int write_sector(uint32_t lba, const void *buffer) override { return !m_disk ? 0 : hard_disk_write(m_disk, lba, buffer); }
	virtual uint8_t calculate_status() override;
>>>>>>> upstream/master

	chd_file       *m_handle;
	hard_disk_file *m_disk;

	enum
	{
		TID_NULL = TID_BUSY + 1
	};

private:
	required_device<harddisk_image_device> m_image;

	emu_timer *     m_last_status_timer;
};

// device type definition
<<<<<<< HEAD
extern const device_type IDE_HARDDISK;

#endif
=======
DECLARE_DEVICE_TYPE(IDE_HARDDISK, ide_hdd_device)

#endif // MAME_MACHINE_IDEHD_H
>>>>>>> upstream/master
