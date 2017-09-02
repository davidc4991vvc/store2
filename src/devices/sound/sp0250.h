// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#pragma once

#ifndef __SP0250_H__
#define __SP0250_H__

class sp0250_device : public device_t,
									public device_sound_interface
{
public:
	sp0250_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~sp0250_device() {}

	template<class _Object> static devcb_base &set_drq_callback(device_t &device, _Object object) { return downcast<sp0250_device &>(device).m_drq.set_callback(object); }

	DECLARE_WRITE8_MEMBER( write );
	UINT8 drq_r();

protected:
	// device-level overrides
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

private:
	// internal state
	INT16 m_amp;
	UINT8 m_pitch;
	UINT8 m_repeat;
	int m_pcount, m_rcount;
	int m_playing;
	UINT32 m_RNG;
	sound_stream * m_stream;
	int m_voiced;
	UINT8 m_fifo[15];
=======
#ifndef MAME_SOUND_SP0250_H
#define MAME_SOUND_SP0250_H

#pragma once

class sp0250_device : public device_t, public device_sound_interface
{
public:
	sp0250_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static devcb_base &set_drq_callback(device_t &device, Object &&cb) { return downcast<sp0250_device &>(device).m_drq.set_callback(std::forward<Object>(cb)); }

	DECLARE_WRITE8_MEMBER( write );
	uint8_t drq_r();

protected:
	// device-level overrides
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

private:
	// internal state
	int16_t m_amp;
	uint8_t m_pitch;
	uint8_t m_repeat;
	int m_pcount, m_rcount;
	int m_playing;
	uint32_t m_RNG;
	sound_stream * m_stream;
	int m_voiced;
	uint8_t m_fifo[15];
>>>>>>> upstream/master
	int m_fifo_pos;
	devcb_write_line m_drq;

	struct
	{
<<<<<<< HEAD
		INT16 F, B;
		INT16 z1, z2;
=======
		int16_t F, B;
		int16_t z1, z2;
>>>>>>> upstream/master
	} m_filter[6];

	void load_values();
	TIMER_CALLBACK_MEMBER( timer_tick );
<<<<<<< HEAD
};

extern const device_type SP0250;
=======
	emu_timer * m_tick_timer;
};

DECLARE_DEVICE_TYPE(SP0250, sp0250_device)
>>>>>>> upstream/master

#define MCFG_SP0250_DRQ_CALLBACK(_write) \
	devcb = &sp0250_device::set_drq_callback(*device, DEVCB_##_write);

<<<<<<< HEAD


#endif /* __SP0250_H__ */
=======
#endif // MAME_SOUND_SP0250_H
>>>>>>> upstream/master
