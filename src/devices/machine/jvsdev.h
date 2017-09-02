// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#ifndef __JVSDEV_H__
#define __JVSDEV_H__

#include "emu.h"
=======
#ifndef MAME_MACHINE_JVSDEV_H
#define MAME_MACHINE_JVSDEV_H

#pragma once

>>>>>>> upstream/master

#define MCFG_JVS_DEVICE_ADD(_tag, _type, _host) \
	MCFG_DEVICE_ADD(_tag, _type, 0) \
	jvs_device::static_set_jvs_host_tag(*device, _host);
<<<<<<< HEAD
=======

>>>>>>> upstream/master
class jvs_host;

class jvs_device : public device_t
{
public:
<<<<<<< HEAD
	jvs_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	static void static_set_jvs_host_tag(device_t &device, const char *jvs_host_tag);

	void chain(jvs_device *dev);
	void message(UINT8 dest, const UINT8 *send_buffer, UINT32 send_size, UINT8 *recv_buffer, UINT32 &recv_size);
	bool get_address_set_line();

protected:
	UINT32 jvs_outputs;

	void handle_output(ioport_port *port, UINT8 id, UINT8 val);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// JVS device overrides
	virtual const char *device_id();
	virtual UINT8 command_format_version();
	virtual UINT8 jvs_standard_version();
	virtual UINT8 comm_method_version();
	virtual void function_list(UINT8 *&buf);
	virtual bool switches(UINT8 *&buf, UINT8 count_players, UINT8 bytes_per_switch);
	virtual bool coin_counters(UINT8 *&buf, UINT8 count);
	virtual bool coin_add(UINT8 slot, INT32 count);
	virtual bool analogs(UINT8 *&buf, UINT8 count);
	virtual bool swoutputs(UINT8 count, const UINT8 *vals);
	virtual bool swoutputs(UINT8 id, UINT8 val);
=======
	static void static_set_jvs_host_tag(device_t &device, const char *jvs_host_tag);

	void chain(jvs_device *dev);
	void message(uint8_t dest, const uint8_t *send_buffer, uint32_t send_size, uint8_t *recv_buffer, uint32_t &recv_size);
	bool get_address_set_line();

protected:
	uint32_t jvs_outputs;

	void handle_output(ioport_port *port, uint8_t id, uint8_t val);

	jvs_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// JVS device overrides
	virtual const char *device_id();
	virtual uint8_t command_format_version();
	virtual uint8_t jvs_standard_version();
	virtual uint8_t comm_method_version();
	virtual void function_list(uint8_t *&buf);
	virtual bool switches(uint8_t *&buf, uint8_t count_players, uint8_t bytes_per_switch);
	virtual bool coin_counters(uint8_t *&buf, uint8_t count);
	virtual bool coin_add(uint8_t slot, int32_t count);
	virtual bool analogs(uint8_t *&buf, uint8_t count);
	virtual bool swoutputs(uint8_t count, const uint8_t *vals);
	virtual bool swoutputs(uint8_t id, uint8_t val);
>>>>>>> upstream/master

private:
	const char *jvs_host_tag;
	jvs_device *next_device;
<<<<<<< HEAD
	UINT8 jvs_address;
	UINT32 jvs_reset_counter;

	int handle_message(const UINT8 *send_buffer, UINT32 send_size, UINT8 *&recv_buffer);
};

#endif
=======
	uint8_t jvs_address;
	uint32_t jvs_reset_counter;

	int handle_message(const uint8_t *send_buffer, uint32_t send_size, uint8_t *&recv_buffer);
};

#endif // MAME_MACHINE_JVSDEV_H
>>>>>>> upstream/master
