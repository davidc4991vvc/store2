// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_SYSTEMFLAGS_H
#define __MSX_SYSTEMFLAGS_H
=======
#ifndef MAME_MACHINE_MSX_SYSTEMFLAGS_H
#define MAME_MACHINE_MSX_SYSTEMFLAGS_H
>>>>>>> upstream/master

/*
Some MSX2+ and TurboR machines have a 'system flags' I/O port ($F4).
The value in this register is cleared on power up, but it keeps it's
value during a reset of the system.
*/

<<<<<<< HEAD
extern const device_type MSX_SYSTEMFLAGS;
=======
DECLARE_DEVICE_TYPE(MSX_SYSTEMFLAGS, msx_systemflags_device)
>>>>>>> upstream/master


#define MCFG_MSX_SYSTEMFLAGS_ADD(_tag, _initial_value) \
	MCFG_DEVICE_ADD(_tag, MSX_SYSTEMFLAGS, 0) \
	msx_systemflags_device::set_initial_value(*device, _initial_value);


class msx_systemflags_device : public device_t
{
public:
<<<<<<< HEAD
	msx_systemflags_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration helpers
	static void set_initial_value(device_t &device, UINT8 initial_value) { dynamic_cast<msx_systemflags_device &>(device).m_initial_value = initial_value; }
=======
	msx_systemflags_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration helpers
	static void set_initial_value(device_t &device, uint8_t initial_value) { dynamic_cast<msx_systemflags_device &>(device).m_initial_value = initial_value; }
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(read);
	DECLARE_WRITE8_MEMBER(write);

protected:
<<<<<<< HEAD
	virtual void device_start();

private:
	UINT8 m_initial_value;
	UINT8 m_system_flags;
};

#endif
=======
	virtual void device_start() override;

private:
	uint8_t m_initial_value;
	uint8_t m_system_flags;
};

#endif // MAME_MACHINE_MSX_SYSTEMFLAGS_H
>>>>>>> upstream/master
