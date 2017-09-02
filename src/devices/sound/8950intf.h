// license:BSD-3-Clause
// copyright-holders:Ernesto Corvi
<<<<<<< HEAD
#pragma once

#ifndef __8950INTF_H__
#define __8950INTF_H__

#include "emu.h"

#define MCFG_Y8950_IRQ_HANDLER(_devcb) \
	devcb = &y8950_device::set_irq_handler(*device, DEVCB_##_devcb);

#define MCFG_Y8950_KEYBOARD_READ_HANDLER(_devcb) \
	devcb = &y8950_device::set_keyboard_read_handler(*device, DEVCB_##_devcb);

#define MCFG_Y8950_KEYBOARD_WRITE_HANDLER(_devcb) \
	devcb = &y8950_device::set_keyboard_write_handler(*device, DEVCB_##_devcb);

#define MCFG_Y8950_IO_READ_HANDLER(_devcb) \
	devcb = &y8950_device::set_io_read_handler(*device, DEVCB_##_devcb);

#define MCFG_Y8950_IO_WRITE_HANDLER(_devcb) \
	devcb = &y8950_device::set_io_write_handler(*device, DEVCB_##_devcb);

class y8950_device : public device_t,
						public device_sound_interface
{
public:
	y8950_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration helpers
	template<class _Object> static devcb_base &set_irq_handler(device_t &device, _Object object) { return downcast<y8950_device &>(device).m_irq_handler.set_callback(object); }
	template<class _Object> static devcb_base &set_keyboard_read_handler(device_t &device, _Object object) { return downcast<y8950_device &>(device).m_keyboard_read_handler.set_callback(object); }
	template<class _Object> static devcb_base &set_keyboard_write_handler(device_t &device, _Object object) { return downcast<y8950_device &>(device).m_keyboard_write_handler.set_callback(object); }
	template<class _Object> static devcb_base &set_io_read_handler(device_t &device, _Object object) { return downcast<y8950_device &>(device).m_io_read_handler.set_callback(object); }
	template<class _Object> static devcb_base &set_io_write_handler(device_t &device, _Object object) { return downcast<y8950_device &>(device).m_io_write_handler.set_callback(object); }
=======
#ifndef MAME_SOUND_8950INTF_H
#define MAME_SOUND_8950INTF_H

#pragma once


#define MCFG_Y8950_IRQ_HANDLER(cb) \
		devcb = &y8950_device::set_irq_handler(*device, (DEVCB_##cb));

#define MCFG_Y8950_KEYBOARD_READ_HANDLER(cb) \
		devcb = &y8950_device::set_keyboard_read_handler(*device, (DEVCB_##cb));

#define MCFG_Y8950_KEYBOARD_WRITE_HANDLER(cb) \
		devcb = &y8950_device::set_keyboard_write_handler(*device, (DEVCB_##cb));

#define MCFG_Y8950_IO_READ_HANDLER(cb) \
		devcb = &y8950_device::set_io_read_handler(*device, (DEVCB_##cb));

#define MCFG_Y8950_IO_WRITE_HANDLER(cb) \
		devcb = &y8950_device::set_io_write_handler(*device, (DEVCB_##cb));

class y8950_device : public device_t, public device_sound_interface
{
public:
	y8950_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration helpers
	template <class Object> static devcb_base &set_irq_handler(device_t &device, Object &&cb) { return downcast<y8950_device &>(device).m_irq_handler.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_keyboard_read_handler(device_t &device, Object &&cb) { return downcast<y8950_device &>(device).m_keyboard_read_handler.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_keyboard_write_handler(device_t &device, Object &&cb) { return downcast<y8950_device &>(device).m_keyboard_write_handler.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_io_read_handler(device_t &device, Object &&cb) { return downcast<y8950_device &>(device).m_io_read_handler.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_io_write_handler(device_t &device, Object &&cb) { return downcast<y8950_device &>(device).m_io_write_handler.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE8_MEMBER( write );

	DECLARE_READ8_MEMBER( status_port_r );
	DECLARE_READ8_MEMBER( read_port_r );
	DECLARE_WRITE8_MEMBER( control_port_w );
	DECLARE_WRITE8_MEMBER( write_port_w );

<<<<<<< HEAD
	void _IRQHandler(int irq);
	void _timer_handler(int c, const attotime &period);
	void _y8950_update_request();
	unsigned char _Y8950PortHandler_r();
	void _Y8950PortHandler_w(unsigned char data);
	unsigned char _Y8950KeyboardHandler_r();
	void _Y8950KeyboardHandler_w(unsigned char data);

protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_stop();
	virtual void device_reset();

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

private:
=======
protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_stop() override;
	virtual void device_reset() override;

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

private:
	void irq_handler(int irq);
	void timer_handler(int c, const attotime &period);
	void update_request() { m_stream->update(); }

	unsigned char port_handler_r() { return m_io_read_handler(0); }
	void port_handler_w(unsigned char data) { m_io_write_handler(offs_t(0), data); }
	unsigned char keyboard_handler_r() { return m_keyboard_read_handler(0); }
	void keyboard_handler_w(unsigned char data) { m_keyboard_write_handler(offs_t(0), data); }

	static void static_irq_handler(device_t *param, int irq) { downcast<y8950_device *>(param)->irq_handler(irq); }
	static void static_timer_handler(device_t *param, int c, const attotime &period) { downcast<y8950_device *>(param)->timer_handler(c, period); }
	static void static_update_request(device_t *param, int interval) { downcast<y8950_device *>(param)->update_request(); }

	static unsigned char static_port_handler_r(device_t *param) { return downcast<y8950_device *>(param)->port_handler_r(); }
	static void static_port_handler_w(device_t *param, unsigned char data) { downcast<y8950_device *>(param)->port_handler_w(data); }
	static unsigned char static_keyboard_handler_r(device_t *param) { return downcast<y8950_device *>(param)->keyboard_handler_r(); }
	static void static_keyboard_handler_w(device_t *param, unsigned char data) { downcast<y8950_device *>(param)->keyboard_handler_w(data); }

>>>>>>> upstream/master
	// internal state
	sound_stream *  m_stream;
	emu_timer *     m_timer[2];
	void *          m_chip;
	devcb_write_line m_irq_handler;
	devcb_read8 m_keyboard_read_handler;
	devcb_write8 m_keyboard_write_handler;
	devcb_read8 m_io_read_handler;
	devcb_write8 m_io_write_handler;
<<<<<<< HEAD
};

extern const device_type Y8950;


#endif /* __8950INTF_H__ */
=======
	required_memory_region m_region;
};

DECLARE_DEVICE_TYPE(Y8950, y8950_device)

#endif // MAME_SOUND_8950INTF_H
>>>>>>> upstream/master
