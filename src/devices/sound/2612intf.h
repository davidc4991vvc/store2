// license:BSD-3-Clause
// copyright-holders:Ernesto Corvi
<<<<<<< HEAD
#pragma once

#ifndef __2612INTF_H__
#define __2612INTF_H__

#include "emu.h"

void ym2612_update_request(void *param);

#define MCFG_YM2612_IRQ_HANDLER(_devcb) \
	devcb = &ym2612_device::set_irq_handler(*device, DEVCB_##_devcb);

class ym2612_device : public device_t,
									public device_sound_interface
{
public:
	ym2612_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	ym2612_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// static configuration helpers
	template<class _Object> static devcb_base &set_irq_handler(device_t &device, _Object object) { return downcast<ym2612_device &>(device).m_irq_handler.set_callback(object); }
=======
#ifndef MAME_SOUND_2612INTF_H
#define MAME_SOUND_2612INTF_H

#pragma once


#define MCFG_YM2612_IRQ_HANDLER(cb) \
		devcb = &ym2612_device::set_irq_handler(*device, (DEVCB_##cb));

class ym2612_device : public device_t, public device_sound_interface
{
public:
	ym2612_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration helpers
	template <class Object> static devcb_base &set_irq_handler(device_t &device, Object &&cb) { return downcast<ym2612_device &>(device).m_irq_handler.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE8_MEMBER( write );

<<<<<<< HEAD
	void _IRQHandler(int irq);
	void _timer_handler(int c,int count,int clock);
	void _ym2612_update_request();

protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_post_load();
	virtual void device_stop();
	virtual void device_reset();

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

private:
=======
	// update request from fm.cpp
	static void update_request(device_t *param) { downcast<ym2612_device *>(param)->update_request(); }

protected:
	ym2612_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_post_load() override;
	virtual void device_stop() override;
	virtual void device_reset() override;
	virtual void device_clock_changed() override;

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

private:
	void irq_handler(int irq);
	void timer_handler(int c, int count, int clock);
	void update_request() { m_stream->update(); }

	static void static_irq_handler(device_t *param, int irq) { downcast<ym2612_device *>(param)->irq_handler(irq); }
	static void static_timer_handler(device_t *param, int c, int count, int clock) { downcast<ym2612_device *>(param)->timer_handler(c, count, clock); }

	void calculate_rates();

>>>>>>> upstream/master
	sound_stream *  m_stream;
	emu_timer *     m_timer[2];
	void *          m_chip;
	devcb_write_line m_irq_handler;
};

<<<<<<< HEAD
extern const device_type YM2612;

=======
>>>>>>> upstream/master

class ym3438_device : public ym2612_device
{
public:
<<<<<<< HEAD
	ym3438_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

extern const device_type YM3438;


#endif /* __2612INTF_H__ */
=======
	ym3438_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};


DECLARE_DEVICE_TYPE(YM2612, ym2612_device)
DECLARE_DEVICE_TYPE(YM3438, ym3438_device)

#endif // MAME_SOUND_2612INTF_H
>>>>>>> upstream/master
