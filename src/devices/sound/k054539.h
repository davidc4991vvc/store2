// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/*********************************************************

    Konami 054539 PCM Sound Chip

*********************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __K054539_H__
#define __K054539_H__

typedef device_delegate<void (double left, double right)> k054539_cb_delegate;
#define K054539_CB_MEMBER(_name)   void _name(double left, double right)

#define MCFG_K054539_APAN_CB(_class, _method) \
	k054539_device::set_analog_callback(*device, k054539_cb_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));

#define MCFG_K054539_REGION_OVERRRIDE(_region) \
	k054539_device::set_override(*device, _region);

#define MCFG_K054539_TIMER_HANDLER(_devcb) \
	devcb = &k054539_device::set_timer_handler(*device, DEVCB_##_devcb);


//* control flags, may be set at DRIVER_INIT().
#define K054539_RESET_FLAGS     0
#define K054539_REVERSE_STEREO  1
#define K054539_DISABLE_REVERB  2
#define K054539_UPDATE_AT_KEYON 4

class k054539_device : public device_t,
						public device_sound_interface
{
public:
=======
#ifndef MAME_SOUND_K054539_H
#define MAME_SOUND_K054539_H

#pragma once

#define K054539_CB_MEMBER(_name)   void _name(double left, double right)

#define MCFG_K054539_APAN_CB(_class, _method) \
		k054539_device::set_analog_callback(*device, k054539_device::cb_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));

#define MCFG_K054539_REGION_OVERRRIDE(_region) \
		k054539_device::set_override(*device, "^" _region);

#define MCFG_K054539_TIMER_HANDLER(_devcb) \
		devcb = &k054539_device::set_timer_handler(*device, DEVCB_##_devcb);


class k054539_device : public device_t, public device_sound_interface
{
public:
	// control flags, may be set at DRIVER_INIT().
>>>>>>> upstream/master
	enum {
		RESET_FLAGS     = 0,
		REVERSE_STEREO  = 1,
		DISABLE_REVERB  = 2,
		UPDATE_AT_KEYON = 4
	};

<<<<<<< HEAD
	// construction/destruction
	k054539_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration helpers
	static void set_analog_callback(device_t &device, k054539_cb_delegate callback) { downcast<k054539_device &>(device).m_apan_cb = callback; }
	static void set_override(device_t &device, const char *rgnoverride) { downcast<k054539_device &>(device).m_rgnoverride = rgnoverride; }
	template<class _Object> static devcb_base &set_timer_handler(device_t &device, _Object object) { return downcast<k054539_device &>(device).m_timer_handler.set_callback(object); }
=======
	typedef device_delegate<void (double left, double right)> cb_delegate;

	// construction/destruction
	k054539_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration helpers
	static void set_analog_callback(device_t &device, cb_delegate &&cb) { downcast<k054539_device &>(device).m_apan_cb = std::move(cb); }
	static void set_override(device_t &device, const char *rgnoverride) { downcast<k054539_device &>(device).m_rom.set_tag(rgnoverride); }
	template <class Object> static devcb_base &set_timer_handler(device_t &device, Object &&cb) { return downcast<k054539_device &>(device).m_timer_handler.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master


	DECLARE_WRITE8_MEMBER(write);
	DECLARE_READ8_MEMBER(read);

	void init_flags(int flags);

	/*
	  Note that the eight PCM channels of a K054539 do not have separate
	  volume controls. Considering the global attenuation equation may not
	  be entirely accurate, k054539_set_gain() provides means to control
<<<<<<< HEAD
	  channel gain. It can be called anywhere but preferrably from
=======
	  channel gain. It can be called anywhere but preferably from
>>>>>>> upstream/master
	  DRIVER_INIT().

	  Parameters:
	      channel : 0 - 7
	      gain    : 0.0=silent, 1.0=no gain, 2.0=twice as loud, etc.
	*/
	void set_gain(int channel, double gain);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual void device_post_load();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// device_sound_interface overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

private:
	struct channel {
		UINT32 pos;
		UINT32 pfrac;
		INT32 val;
		INT32 pval;
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_post_load() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// device_sound_interface overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

private:
	struct channel {
		uint32_t pos;
		uint32_t pfrac;
		int32_t val;
		int32_t pval;
>>>>>>> upstream/master
	};

	double voltab[256];
	double pantab[0xf];

	double gain[8];
<<<<<<< HEAD
	UINT8 posreg_latch[8][3];
	int flags;

	unsigned char regs[0x230];
	unsigned char *ram;
	int reverb_pos;

	INT32 cur_ptr;
	int cur_limit;
	unsigned char *cur_zone;
	unsigned char *rom;
	UINT32 rom_size;
	UINT32 rom_mask;
=======
	uint8_t posreg_latch[8][3];
	int flags;

	unsigned char regs[0x230];
	std::unique_ptr<uint8_t[]> ram;
	int reverb_pos;

	int32_t cur_ptr;
	int cur_limit;
	unsigned char *cur_zone;
	required_region_ptr<uint8_t> m_rom;
	uint32_t rom_mask;
>>>>>>> upstream/master

	channel channels[8];
	sound_stream *stream;

	emu_timer          *m_timer;
<<<<<<< HEAD
	UINT32             m_timer_state;
	devcb_write_line   m_timer_handler;
	const char         *m_rgnoverride;
	k054539_cb_delegate m_apan_cb;
=======
	uint32_t             m_timer_state;
	devcb_write_line   m_timer_handler;
	cb_delegate m_apan_cb;
>>>>>>> upstream/master

	bool regupdate();
	void keyon(int channel);
	void keyoff(int channel);
	void init_chip();
};

<<<<<<< HEAD
extern const device_type K054539;

#endif /* __K054539_H__ */
=======
DECLARE_DEVICE_TYPE(K054539, k054539_device)

#endif // MAME_SOUND_K054539_H
>>>>>>> upstream/master
