// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#ifndef _MAPLEDEV_H_
#define _MAPLEDEV_H_
=======
#ifndef MAME_MACHINE_MAPLEDEV_H
#define MAME_MACHINE_MAPLEDEV_H
>>>>>>> upstream/master

#define MCFG_MAPLE_DEVICE_ADD(_tag, _type, _clock, _host_tag, _host_port) \
	MCFG_DEVICE_ADD(_tag, _type, _clock) \
	maple_device::static_set_host(*device, _host_tag, _host_port);

class maple_device : public device_t
{
public:
<<<<<<< HEAD
	maple_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	static void static_set_host(device_t &device, const char *_host_tag, int _host_port);
	virtual void maple_w(const UINT32 *data, UINT32 in_size) = 0;
	void maple_r(UINT32 *data, UINT32 &out_size, bool &partial);
=======
	static void static_set_host(device_t &device, const char *_host_tag, int _host_port);
	virtual void maple_w(const uint32_t *data, uint32_t in_size) = 0;
	void maple_r(uint32_t *data, uint32_t &out_size, bool &partial);
>>>>>>> upstream/master
	virtual void maple_reset();

protected:
	enum { TIMER_ID = 1000 };

<<<<<<< HEAD
	UINT32 reply_size;
	bool reply_partial;
	UINT32 reply_buffer[256];

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	maple_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	uint32_t reply_size;
	bool reply_partial;
	uint32_t reply_buffer[256];

	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
>>>>>>> upstream/master

	void reply_ready();
	void reply_ready_with_delay();

	// Copy a string and complete it with spaces up to size len
<<<<<<< HEAD
	void copy_with_spaces(UINT8 *dest, const char *source, int len);

	// Setup the first UINT32 of reply with the type, source and length.
	// Also setup reply_size and clear reply_partial
	void reply_start(UINT8 code, UINT8 source, UINT8 size);
=======
	void copy_with_spaces(uint8_t *dest, const char *source, int len);

	// Setup the first uint32_t of reply with the type, source and length.
	// Also setup reply_size and clear reply_partial
	void reply_start(uint8_t code, uint8_t source, uint8_t size);
>>>>>>> upstream/master

	// Configuration
	class maple_dc_device *host;
	const char *host_tag;
	int host_port;

private:
	emu_timer *timer;
};

<<<<<<< HEAD
#endif // _MAPLEDEV_H_
=======
#endif // MAME_MACHINE_MAPLEDEV_H
>>>>>>> upstream/master
