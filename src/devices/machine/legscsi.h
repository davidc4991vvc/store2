// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#ifndef _LEGSCSI_H_
#define _LEGSCSI_H_
=======
#ifndef MAME_MACHINE_LEGSCSI_H
#define MAME_MACHINE_LEGSCSI_H
>>>>>>> upstream/master

#pragma once

#include "bus/scsi/scsihle.h"

#define MCFG_LEGACY_SCSI_PORT(_tag) \
	legacy_scsi_host_adapter::set_scsi_port(*device, "^" _tag);

class legacy_scsi_host_adapter : public device_t
{
public:
<<<<<<< HEAD
	legacy_scsi_host_adapter(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	static void set_scsi_port(device_t &device, const char *tag) { downcast<legacy_scsi_host_adapter &>(device).m_scsi_port.set_tag(tag); }

protected:
	virtual void device_start();

	void reset_bus();
	bool select(int id);
	void send_command(UINT8 *data, int bytes);
	int get_length();
	int get_phase();
	void read_data(UINT8 *data, int bytes);
	void write_data(UINT8 *data, int bytes);
	UINT8 get_status();
=======
	static void set_scsi_port(device_t &device, const char *tag) { downcast<legacy_scsi_host_adapter &>(device).m_scsi_port.set_tag(tag); }

protected:
	legacy_scsi_host_adapter(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;

	void reset_bus();
	bool select(int id);
	void send_command(uint8_t *data, int bytes);
	int get_length();
	int get_phase();
	void read_data(uint8_t *data, int bytes);
	void write_data(uint8_t *data, int bytes);
	uint8_t get_status();
>>>>>>> upstream/master

private:
	int m_selected;
	scsihle_device *get_device(int id);

<<<<<<< HEAD
	required_device<SCSI_PORT_DEVICE> m_scsi_port;
};

#endif
=======
	required_device<scsi_port_device> m_scsi_port;
};

#endif // MAME_MACHINE_LEGSCSI_H
>>>>>>> upstream/master
