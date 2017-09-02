// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "jvsdev.h"
#include "jvshost.h"

void jvs_device::static_set_jvs_host_tag(device_t &device, const char *jvs_host_tag)
{
	jvs_device &jvsdev = downcast<jvs_device &>(device);
	jvsdev.jvs_host_tag = jvs_host_tag;
}

<<<<<<< HEAD
jvs_device::jvs_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source)
	: device_t(mconfig, type, name, tag, owner, clock, shortname, source), jvs_outputs(0), jvs_address(0), jvs_reset_counter(0)
{
	jvs_host_tag = 0;
	next_device = 0;
=======
jvs_device::jvs_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, type, tag, owner, clock), jvs_outputs(0), jvs_address(0), jvs_reset_counter(0)
{
	jvs_host_tag = nullptr;
	next_device = nullptr;
>>>>>>> upstream/master
}

const char *jvs_device::device_id()
{
	return "";
}

<<<<<<< HEAD
UINT8 jvs_device::command_format_version()
=======
uint8_t jvs_device::command_format_version()
>>>>>>> upstream/master
{
	return 0x13;
}

<<<<<<< HEAD
UINT8 jvs_device::jvs_standard_version()
=======
uint8_t jvs_device::jvs_standard_version()
>>>>>>> upstream/master
{
	return 0x30;
}

<<<<<<< HEAD
UINT8 jvs_device::comm_method_version()
=======
uint8_t jvs_device::comm_method_version()
>>>>>>> upstream/master
{
	return 0x10;
}

void jvs_device::chain(jvs_device *dev)
{
	if(next_device)
		next_device->chain(dev);
	else
		next_device = dev;
}

<<<<<<< HEAD
void jvs_device::message(UINT8 dest, const UINT8 *send_buffer, UINT32 send_size, UINT8 *recv_buffer, UINT32 &recv_size)
=======
void jvs_device::message(uint8_t dest, const uint8_t *send_buffer, uint32_t send_size, uint8_t *recv_buffer, uint32_t &recv_size)
>>>>>>> upstream/master
{
	recv_size = 0;

	// Set Address special case
	if(send_size == 2 && send_buffer[0] == 0xf1) {
		if(next_device && !next_device->get_address_set_line())
			next_device->message(dest, send_buffer, send_size, recv_buffer, recv_size);
		else {
			jvs_address = send_buffer[1];
			recv_size = 2;
			recv_buffer[0] = 0x01;
			recv_buffer[1] = 0x01;
		}
		return;
	}

	// dest=0xff is broadcast
	if(dest == 0xff || dest == jvs_address) {
<<<<<<< HEAD
		const UINT8 *s = send_buffer;
		UINT8 *d = recv_buffer;
=======
		const uint8_t *s = send_buffer;
		uint8_t *d = recv_buffer;
>>>>>>> upstream/master
		*d++ = 0x01;
		while(s < send_buffer + send_size) {
			int len = handle_message(s, send_size-(s-send_buffer), d);
			if(len == -1) {
				// Unknown command
				recv_size = 1;
				recv_buffer[0] = 0x02;
				return;
			} else if(len == 0) {
				// Incorrect parameter
				*d++ = 0x02;
				break;
			} else
				s += len;
		}
		recv_size = d - recv_buffer;
	}

	// Pass along the message if the device hasn't replied
	// Should we cumulate answers instead?
	if(next_device && !recv_size)
		next_device->message(dest, send_buffer, send_size, recv_buffer, recv_size);
}

<<<<<<< HEAD
int jvs_device::handle_message(const UINT8 *send_buffer, UINT32 send_size, UINT8 *&recv_buffer)
{
	UINT32 old_reset_counter = jvs_reset_counter;
=======
int jvs_device::handle_message(const uint8_t *send_buffer, uint32_t send_size, uint8_t *&recv_buffer)
{
	uint32_t old_reset_counter = jvs_reset_counter;
>>>>>>> upstream/master
	jvs_reset_counter = 0;

	switch(send_buffer[0]) {
	case 0xf0:
		if(send_size < 2 || send_buffer[1] != 0xd9)
			return 0;

		// Reset, must be sent twice
		jvs_reset_counter = old_reset_counter+1;
		if(jvs_reset_counter == 2)
			device_reset();
		return 2;

	case 0x10: {
		const char *id = device_id();
		int len = strlen(id)+1;
		*recv_buffer++ = 0x01;
		memcpy(recv_buffer, id, len);
		recv_buffer += len;
		return 1;
	}

	case 0x11:
		*recv_buffer++ = 0x01;
		*recv_buffer++ = command_format_version();
		return 1;

	case 0x12:
		*recv_buffer++ = 0x01;
		*recv_buffer++ = jvs_standard_version();
		return 1;

	case 0x13:
		*recv_buffer++ = 0x01;
		*recv_buffer++ = comm_method_version();
		return 1;

	case 0x14:
		*recv_buffer++ = 0x01;
		function_list(recv_buffer);
		*recv_buffer++ = 0x00;
		return 1;

	case 0x20:
		if(send_size < 3)
			return 0;
		*recv_buffer++ = 0x01;
		return switches(recv_buffer, send_buffer[1], send_buffer[2]) ? 3 : 0;

	case 0x21:
		if(send_size < 2)
			return 0;
		*recv_buffer++ = 0x01;
		return coin_counters(recv_buffer, send_buffer[1]) ? 2 : 0;

	case 0x22:
		if(send_size < 2)
			return 0;
		*recv_buffer++ = 0x01;
		return analogs(recv_buffer, send_buffer[1]) ? 2 : 0;

	case 0x30:
		if(send_size < 4)
			return 0;
		*recv_buffer++ = 0x01;
		return coin_add(send_buffer[1], -((send_buffer[2] << 8) | send_buffer[3])) ? 4 : 0;

	case 0x31:
		if(send_size < 4)
			return 0;
		*recv_buffer++ = 0x01;
		return coin_add(send_buffer[1],  ((send_buffer[2] << 8) | send_buffer[3])) ? 4 : 0;

	case 0x32:
		if(send_size < 2 || send_size < 2+send_buffer[1])
			return 0;
		*recv_buffer++ = 0x01;
		return swoutputs(send_buffer[1], send_buffer+2) ? 2+send_buffer[1] : 0;

	case 0x38:
		if(send_size < 3)
			return 0;
		*recv_buffer++ = 0x01;
		return swoutputs(send_buffer[1], send_buffer[2]) ? 3 : 0;

	default:
		logerror("JVSDEV: unhandled command %02x\n", send_buffer[0]);
		return 0;
	}

	// never executed
	//return -1;
}

bool jvs_device::get_address_set_line()
{
	return jvs_address != 0xff && (!next_device || next_device->get_address_set_line());
}

void jvs_device::device_start()
{
	jvs_host *host = machine().device<jvs_host>(jvs_host_tag);
	if(!host)
		fatalerror("JVS device %s could not find JVS host %s\n", tag(), jvs_host_tag);
	host->add_device(this);

	save_item(NAME(jvs_address));
	save_item(NAME(jvs_reset_counter));
}

void jvs_device::device_reset()
{
	jvs_address = 0xff;
	jvs_reset_counter = 0;
	jvs_outputs = 0;
}

<<<<<<< HEAD
void jvs_device::function_list(UINT8 *&buf)
{
}

bool jvs_device::coin_counters(UINT8 *&buf, UINT8 count)
=======
void jvs_device::function_list(uint8_t *&buf)
{
}

bool jvs_device::coin_counters(uint8_t *&buf, uint8_t count)
>>>>>>> upstream/master
{
	return false;
}

<<<<<<< HEAD
bool jvs_device::coin_add(UINT8 slot, INT32 count)
=======
bool jvs_device::coin_add(uint8_t slot, int32_t count)
>>>>>>> upstream/master
{
	return false;
}


<<<<<<< HEAD
bool jvs_device::switches(UINT8 *&buf, UINT8 count_players, UINT8 bytes_per_switch)
=======
bool jvs_device::switches(uint8_t *&buf, uint8_t count_players, uint8_t bytes_per_switch)
>>>>>>> upstream/master
{
	return false;
}

<<<<<<< HEAD
bool jvs_device::analogs(UINT8 *&buf, UINT8 count)
=======
bool jvs_device::analogs(uint8_t *&buf, uint8_t count)
>>>>>>> upstream/master
{
	return false;
}

<<<<<<< HEAD
bool jvs_device::swoutputs(UINT8 count, const UINT8 *vals)
=======
bool jvs_device::swoutputs(uint8_t count, const uint8_t *vals)
>>>>>>> upstream/master
{
	return false;
}

<<<<<<< HEAD
bool jvs_device::swoutputs(UINT8 id, UINT8 val)
=======
bool jvs_device::swoutputs(uint8_t id, uint8_t val)
>>>>>>> upstream/master
{
	return false;
}

<<<<<<< HEAD
void jvs_device::handle_output(ioport_port *port, UINT8 id, UINT8 val)
{
	UINT32 m = 1 << id;
=======
void jvs_device::handle_output(ioport_port *port, uint8_t id, uint8_t val)
{
	uint32_t m = 1 << id;
>>>>>>> upstream/master
	switch(val) {
	case 0: jvs_outputs &= ~m; break;
	case 1: jvs_outputs |=  m;  break;
	case 2: jvs_outputs ^=  m;  break;
	}

	if (port)
	{
		port->write(jvs_outputs, m);
	}
}
