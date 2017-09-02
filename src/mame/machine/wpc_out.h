// license:BSD-3-Clause
// copyright-holders:Olivier Galibert

// Williams Pinball Controller outputs control (solenoids, flashers, generic logic, global illumination, coin counter, cpu led)

<<<<<<< HEAD
#ifndef WPC_OUT_H
#define WPC_OUT_H
=======
#ifndef MAME_MACHINE_WPC_OUT_H
#define MAME_MACHINE_WPC_OUT_H

#pragma once
>>>>>>> upstream/master

#define MCFG_WPC_OUT_ADD( _tag, _count )    \
	MCFG_DEVICE_ADD( _tag, WPC_OUT, 0 )     \
		downcast<wpc_out_device *>(device)->set_gi_count(_count);

class wpc_out_device : public device_t
{
public:
	typedef delegate<bool (int, bool)> handler_t;

<<<<<<< HEAD
	wpc_out_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	wpc_out_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
	virtual ~wpc_out_device();

	DECLARE_WRITE8_MEMBER(out_w);
	DECLARE_WRITE8_MEMBER(out4_w); // fixed offset 4
	DECLARE_WRITE8_MEMBER(gi_w);
	DECLARE_WRITE8_MEMBER(led_w);

	void set_names(const char *const *names);
	void set_handler(handler_t cb);
	void set_gi_count(int _count);

protected:
<<<<<<< HEAD
	UINT8 state[6], gi;
	bool first_after_led;
	attotime previous_gi_update;
	int gi_count;
	UINT32 gi_time[5];
=======
	uint8_t state[6], gi;
	bool first_after_led;
	attotime previous_gi_update;
	int gi_count;
	uint32_t gi_time[5];
>>>>>>> upstream/master
	emu_timer *timer;
	const char *const *names;
	handler_t handler_cb;

	void send_output(int sid, int state);

<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
>>>>>>> upstream/master

	void gi_update();
};

<<<<<<< HEAD
extern const device_type WPC_OUT;

#endif
=======
DECLARE_DEVICE_TYPE(WPC_OUT, wpc_out_device)

#endif // MAME_MACHINE_WPC_OUT_H
>>>>>>> upstream/master
