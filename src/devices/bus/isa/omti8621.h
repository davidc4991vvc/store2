// license:BSD-3-Clause
// copyright-holders:Hans Ostermeyer,R. Belmont
/*
 * omti8621.h - SMS OMTI 8621 disk controller
 *
 *  Created on: August 30, 2010
 *      Author: Hans Ostermeyer
 *
 *  Converted to ISA device March 3, 2014 by R. Belmont
 *
 */

<<<<<<< HEAD
#pragma once

#ifndef ISA_OMTI8621_H_
#define ISA_OMTI8621_H_

#include "emu.h"
#include "isa.h"
#include "machine/pc_fdc.h"

#define OMTI_MAX_LUN 1
#define CDB_SIZE 10

=======
#ifndef MAME_BUS_ISA_OMTI8621_H
#define MAME_BUS_ISA_OMTI8621_H

#pragma once

#include "isa.h"
#include "machine/pc_fdc.h"

>>>>>>> upstream/master
/***************************************************************************
 FUNCTION PROTOTYPES
 ***************************************************************************/

class omti_disk_image_device;

/* ----- device interface ----- */

class omti8621_device : public device_t, public device_isa16_card_interface
{
public:
<<<<<<< HEAD
	omti8621_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~omti8621_device() {}

=======
>>>>>>> upstream/master
	DECLARE_READ16_MEMBER(read);
	DECLARE_WRITE16_MEMBER(write);

	static void set_verbose(int on_off);

<<<<<<< HEAD
	// get sector diskaddr of logical unit lun into data_buffer
	static UINT32 get_sector(INT32 diskaddr, UINT8 *data_buffer, UINT32 length, UINT8 lun);
=======
protected:
	static constexpr unsigned OMTI_MAX_LUN = 1;
	static constexpr unsigned CDB_SIZE = 10;

	omti8621_device(
			const machine_config &mconfig,
			device_type type,
			const char *tag,
			device_t *owner,
			uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	virtual uint8_t dack_r(int line) override;
	virtual void dack_w(int line, uint8_t data) override;
	virtual void eop_w(int state) override;

	void set_interrupt(enum line_state line_state);
>>>>>>> upstream/master

	required_device<pc_fdc_interface> m_fdc;
	required_ioport m_iobase;
	required_ioport m_biosopts;

<<<<<<< HEAD
=======
	omti_disk_image_device *our_disks[OMTI_MAX_LUN+1];

private:
>>>>>>> upstream/master
	DECLARE_WRITE_LINE_MEMBER( fdc_irq_w );
	DECLARE_WRITE_LINE_MEMBER( fdc_drq_w );
	DECLARE_FLOPPY_FORMATS( floppy_formats );

<<<<<<< HEAD
protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();
	virtual const rom_entry *device_rom_region() const;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	virtual UINT8 dack_r(int line);
	virtual void dack_w(int line, UINT8 data);
	virtual void eop_w(int state);

	void set_interrupt(enum line_state line_state);

private:
	omti_disk_image_device *our_disks[OMTI_MAX_LUN+1];

	UINT16 jumper;

	UINT8 omti_state;

	UINT8 status_port;
	UINT8 config_port;
	UINT8 mask_port;

	// command descriptor block
	UINT8 command_buffer[CDB_SIZE];
=======
	uint16_t jumper;

	uint8_t omti_state;

	uint8_t status_port;
	uint8_t config_port;
	uint8_t mask_port;

	// command descriptor block
	uint8_t command_buffer[CDB_SIZE];
>>>>>>> upstream/master
	int command_length;
	int command_index;
	int command_status;

	// data buffer
<<<<<<< HEAD
	dynamic_buffer sector_buffer;
	UINT8 *data_buffer;
=======
	std::vector<uint8_t> sector_buffer;
	uint8_t *data_buffer;
>>>>>>> upstream/master
	int data_length;
	int data_index;

	// sense data
<<<<<<< HEAD
	UINT8 sense_data[4];

	// these are used only to satisfy dex
	UINT32 diskaddr_ecc_error;
	UINT32 diskaddr_format_bad_track;
	UINT8 alternate_track_buffer[4];
	UINT32 alternate_track_address[2];
=======
	uint8_t sense_data[4];

	// these are used only to satisfy dex
	uint32_t diskaddr_ecc_error;
	uint32_t diskaddr_format_bad_track;
	uint8_t alternate_track_buffer[4];
	uint32_t alternate_track_address[2];
>>>>>>> upstream/master

	emu_timer *m_timer;

	bool m_installed;

	void clear_sense_data();
<<<<<<< HEAD
	void set_sense_data(UINT8 code, const UINT8 * cdb);
	void set_configuration_data(UINT8 lun);
	UINT8 get_lun(const UINT8 * cdb);
	UINT8 check_disk_address(const UINT8 *cdb);
	UINT32 get_disk_track(const UINT8 * cdb);
	UINT32 get_disk_address(const UINT8 * cdb);
	void set_data_transfer(UINT8 *data, UINT16 length);
	void read_sectors_from_disk(INT32 diskaddr, UINT8 count, UINT8 lun);
	void write_sectors_to_disk(INT32 diskaddr, UINT8 count, UINT8 lun);
	void copy_sectors(INT32 dst_addr, INT32 src_addr, UINT8 count, UINT8 lun);
	void format_track(const UINT8 * cdb);
	void set_esdi_defect_list(UINT8 lun, UINT8 head);
	void log_command(const UINT8 cdb[], const UINT16 cdb_length);
	void log_data();
	void do_command(const UINT8 cdb[], const UINT16 cdb_length);
	UINT8 get_command_length(UINT8 command_byte);
	UINT16 get_data();
	void set_data(UINT16 data);
	void set_jumper(UINT16 disk_type);
=======
	void set_sense_data(uint8_t code, const uint8_t * cdb);
	void set_configuration_data(uint8_t lun);
	uint8_t get_lun(const uint8_t * cdb);
	uint8_t check_disk_address(const uint8_t *cdb);
	uint32_t get_disk_track(const uint8_t * cdb);
	uint32_t get_disk_address(const uint8_t * cdb);
	void set_data_transfer(uint8_t *data, uint16_t length);
	void read_sectors_from_disk(int32_t diskaddr, uint8_t count, uint8_t lun);
	void write_sectors_to_disk(int32_t diskaddr, uint8_t count, uint8_t lun);
	void copy_sectors(int32_t dst_addr, int32_t src_addr, uint8_t count, uint8_t lun);
	void format_track(const uint8_t * cdb);
	void set_esdi_defect_list(uint8_t lun, uint8_t head);

	template <typename Format, typename... Params> void logerror(Format &&fmt, Params &&... args) const;

	void log_command(const uint8_t cdb[], const uint16_t cdb_length);
	void log_data();
	void do_command(const uint8_t cdb[], const uint16_t cdb_length);
	uint8_t get_command_length(uint8_t command_byte);
	uint16_t get_data();
	void set_data(uint16_t data);
	void set_jumper(uint16_t disk_type);
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(read8);
	DECLARE_WRITE8_MEMBER(write8);
};

<<<<<<< HEAD
extern const device_type ISA16_OMTI8621;

//###############################################################

#endif /* OMTI8621_H_ */
=======
/* ----- omti8621 for PC device interface ----- */

class omti8621_pc_device : public omti8621_device
{
public:
	omti8621_pc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

DECLARE_DEVICE_TYPE(ISA16_OMTI8621, omti8621_pc_device)

/* ----- omti8621 for apollo device interface ----- */

class omti8621_apollo_device : public omti8621_device
{
public:
	omti8621_apollo_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// get sector diskaddr of logical unit lun into data_buffer
	uint32_t get_sector(int32_t diskaddr, uint8_t *data_buffer, uint32_t length, uint8_t lun);
protected:
	virtual const tiny_rom_entry *device_rom_region() const override;
};

DECLARE_DEVICE_TYPE(ISA16_OMTI8621_APOLLO, omti8621_apollo_device)

//###############################################################

#endif // MAME_BUS_ISA_OMTI8621_H
>>>>>>> upstream/master
