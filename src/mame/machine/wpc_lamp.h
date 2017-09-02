// license:BSD-3-Clause
// copyright-holders:Olivier Galibert

// Williams Pinball Controller lamp control

<<<<<<< HEAD
#ifndef WPC_LAMP_H
#define WPC_LAMP_H
=======
#ifndef MAME_MACHINE_WPC_LAMP_H
#define MAME_MACHINE_WPC_LAMP_H

#pragma once
>>>>>>> upstream/master

#define MCFG_WPC_LAMP_ADD( _tag ) \
	MCFG_DEVICE_ADD( _tag, WPC_LAMP, 0 )

class wpc_lamp_device : public device_t
{
public:
<<<<<<< HEAD
	wpc_lamp_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	wpc_lamp_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
	virtual ~wpc_lamp_device();

	DECLARE_WRITE8_MEMBER(row_w);
	DECLARE_WRITE8_MEMBER(col_w);

	void set_names(const char *const *lamp_names);

protected:
<<<<<<< HEAD
	UINT8 state[64];
	UINT8 col, row;
	emu_timer *timer;
	const char *const *names;

	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	uint8_t state[64];
	uint8_t col, row;
	emu_timer *timer;
	const char *const *names;

	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
>>>>>>> upstream/master

	void update();
};

<<<<<<< HEAD
extern const device_type WPC_LAMP;

#endif
=======
DECLARE_DEVICE_TYPE(WPC_LAMP, wpc_lamp_device)

#endif // MAME_MACHINE_WPC_LAMP_H
>>>>>>> upstream/master
