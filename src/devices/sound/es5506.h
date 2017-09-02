// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/**********************************************************************************************
 *
 *   Ensoniq ES5505/6 driver
 *   by Aaron Giles
 *
 **********************************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __ES5506_H__
#define __ES5506_H__

#define MAKE_WAVS               0
=======
#ifndef MAME_SOUND_ES5506_H
#define MAME_SOUND_ES5506_H

#pragma once

#define ES5506_MAKE_WAVS 0
>>>>>>> upstream/master

#define MCFG_ES5506_REGION0(_region) \
	es5506_device::set_region0(*device, _region);

#define MCFG_ES5506_REGION1(_region) \
	es5506_device::set_region1(*device, _region);

#define MCFG_ES5506_REGION2(_region) \
	es5506_device::set_region2(*device, _region);

#define MCFG_ES5506_REGION3(_region) \
	es5506_device::set_region3(*device, _region);

#define MCFG_ES5506_CHANNELS(_chan) \
	es5506_device::set_channels(*device, _chan);

#define MCFG_ES5506_IRQ_CB(_devcb) \
	devcb = &es5506_device::set_irq_callback(*device, DEVCB_##_devcb);

#define MCFG_ES5506_READ_PORT_CB(_devcb) \
	devcb = &es5506_device::set_read_port_callback(*device, DEVCB_##_devcb);


#define MCFG_ES5505_REGION0(_region) \
	es5505_device::set_region0(*device, _region);

#define MCFG_ES5505_REGION1(_region) \
	es5505_device::set_region1(*device, _region);

#define MCFG_ES5505_CHANNELS(_chan) \
	es5505_device::set_channels(*device, _chan);

#define MCFG_ES5505_IRQ_CB(_devcb) \
	devcb = &es5505_device::set_irq_callback(*device, DEVCB_##_devcb);

#define MCFG_ES5505_READ_PORT_CB(_devcb) \
	devcb = &es5505_device::set_read_port_callback(*device, DEVCB_##_devcb);


<<<<<<< HEAD
/* struct describing a single playing voice */

struct es550x_voice
{
		es550x_voice():
		control(0),
		freqcount(0),
		start(0),
		lvol(0),
		end(0),
		lvramp(0),
		accum(0),
		rvol(0),
		rvramp(0),
		ecount(0),
		k2(0),
		k2ramp(0),
		k1(0),
		k1ramp(0),
		o4n1(0),
		o3n1(0),
		o3n2(0),
		o2n1(0),
		o2n2(0),
		o1n1(0),
		exbank(0),
		index(0),
		filtcount(0),
		accum_mask(0) {}

	/* external state */
	UINT32      control;                /* control register */
	UINT32      freqcount;              /* frequency count register */
	UINT32      start;                  /* start register */
	UINT32      lvol;                   /* left volume register */
	UINT32      end;                    /* end register */
	UINT32      lvramp;                 /* left volume ramp register */
	UINT32      accum;                  /* accumulator register */
	UINT32      rvol;                   /* right volume register */
	UINT32      rvramp;                 /* right volume ramp register */
	UINT32      ecount;                 /* envelope count register */
	UINT32      k2;                     /* k2 register */
	UINT32      k2ramp;                 /* k2 ramp register */
	UINT32      k1;                     /* k1 register */
	UINT32      k1ramp;                 /* k1 ramp register */
	INT32       o4n1;                   /* filter storage O4(n-1) */
	INT32       o3n1;                   /* filter storage O3(n-1) */
	INT32       o3n2;                   /* filter storage O3(n-2) */
	INT32       o2n1;                   /* filter storage O2(n-1) */
	INT32       o2n2;                   /* filter storage O2(n-2) */
	INT32       o1n1;                   /* filter storage O1(n-1) */
	UINT32      exbank;                 /* external address bank */

	/* internal state */
	UINT8       index;                  /* index of this voice */
	UINT8       filtcount;              /* filter count */
	UINT32      accum_mask;
};

class es550x_device : public device_t,
									public device_sound_interface
{
public:
	es550x_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	~es550x_device() {}

=======
class es550x_device : public device_t, public device_sound_interface
{
public:
>>>>>>> upstream/master
	static void set_region0(device_t &device, const char *region0) { downcast<es550x_device &>(device).m_region0 = region0; }
	static void set_region1(device_t &device, const char *region1) { downcast<es550x_device &>(device).m_region1 = region1; }
	static void set_region2(device_t &device, const char *region2) { downcast<es550x_device &>(device).m_region2 = region2; }
	static void set_region3(device_t &device, const char *region3) { downcast<es550x_device &>(device).m_region3 = region3; }
	static void set_channels(device_t &device, int channels) { downcast<es550x_device &>(device).m_channels = channels; }
<<<<<<< HEAD
	template<class _Object> static devcb_base &set_irq_callback(device_t &device, _Object object) { return downcast<es550x_device &>(device).m_irq_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_read_port_callback(device_t &device, _Object object) { return downcast<es550x_device &>(device).m_read_port_cb.set_callback(object); }


protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_stop();
	virtual void device_reset();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
=======
	template <class Object> static devcb_base &set_irq_callback(device_t &device, Object &&cb) { return downcast<es550x_device &>(device).m_irq_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_read_port_callback(device_t &device, Object &&cb) { return downcast<es550x_device &>(device).m_read_port_cb.set_callback(std::forward<Object>(cb)); }

protected:
	// struct describing a single playing voice
	struct es550x_voice
	{
		es550x_voice() { }

		// external state
		uint32_t      control   = 0;          // control register
		uint32_t      freqcount = 0;          // frequency count register
		uint32_t      start     = 0;          // start register
		uint32_t      lvol      = 0;          // left volume register
		uint32_t      end       = 0;          // end register
		uint32_t      lvramp    = 0;          // left volume ramp register
		uint32_t      accum     = 0;          // accumulator register
		uint32_t      rvol      = 0;          // right volume register
		uint32_t      rvramp    = 0;          // right volume ramp register
		uint32_t      ecount    = 0;          // envelope count register
		uint32_t      k2        = 0;          // k2 register
		uint32_t      k2ramp    = 0;          // k2 ramp register
		uint32_t      k1        = 0;          // k1 register
		uint32_t      k1ramp    = 0;          // k1 ramp register
		int32_t       o4n1      = 0;          // filter storage O4(n-1)
		int32_t       o3n1      = 0;          // filter storage O3(n-1)
		int32_t       o3n2      = 0;          // filter storage O3(n-2)
		int32_t       o2n1      = 0;          // filter storage O2(n-1)
		int32_t       o2n2      = 0;          // filter storage O2(n-2)
		int32_t       o1n1      = 0;          // filter storage O1(n-1)
		uint32_t      exbank    = 0;          // external address bank

		// internal state
		uint8_t       index      = 0;         // index of this voice
		uint8_t       filtcount  = 0;         // filter count
		uint32_t      accum_mask = 0;
	};

	es550x_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_stop() override;
	virtual void device_reset() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

	void update_irq_state();
	void update_internal_irq_state();
	void compute_tables();

	void generate_dummy(es550x_voice *voice, uint16_t *base, int32_t *lbuffer, int32_t *rbuffer, int samples);
	void generate_ulaw(es550x_voice *voice, uint16_t *base, int32_t *lbuffer, int32_t *rbuffer, int samples);
	void generate_pcm(es550x_voice *voice, uint16_t *base, int32_t *lbuffer, int32_t *rbuffer, int samples);
>>>>>>> upstream/master

	// internal state
	sound_stream *m_stream;               /* which stream are we using */
	int         m_sample_rate;            /* current sample rate */
<<<<<<< HEAD
	UINT16 *    m_region_base[4];         /* pointer to the base of the region */
	UINT32      m_write_latch;            /* currently accumulated data for write */
	UINT32      m_read_latch;             /* currently accumulated data for read */
	UINT32      m_master_clock;           /* master clock frequency */

	UINT8       m_current_page;           /* current register page */
	UINT8       m_active_voices;          /* number of active voices */
	UINT8       m_mode;                   /* MODE register */
	UINT8       m_wst;                    /* W_ST register */
	UINT8       m_wend;                   /* W_END register */
	UINT8       m_lrend;                  /* LR_END register */
	UINT8       m_irqv;                   /* IRQV register */

	es550x_voice m_voice[32];             /* the 32 voices */

	INT32 *     m_scratch;

	INT16 *     m_ulaw_lookup;
	UINT16 *    m_volume_lookup;

	#if MAKE_WAVS
	void *      m_wavraw;                 /* raw waveform */
	#endif

	FILE *m_eslog;
=======
	uint16_t *    m_region_base[4];         /* pointer to the base of the region */
	uint32_t      m_write_latch;            /* currently accumulated data for write */
	uint32_t      m_read_latch;             /* currently accumulated data for read */
	uint32_t      m_master_clock;           /* master clock frequency */

	uint8_t       m_current_page;           /* current register page */
	uint8_t       m_active_voices;          /* number of active voices */
	uint8_t       m_mode;                   /* MODE register */
	uint8_t       m_wst;                    /* W_ST register */
	uint8_t       m_wend;                   /* W_END register */
	uint8_t       m_lrend;                  /* LR_END register */
	uint8_t       m_irqv;                   /* IRQV register */

	es550x_voice m_voice[32];             /* the 32 voices */

	std::unique_ptr<int32_t[]>     m_scratch;

	std::unique_ptr<int16_t[]>     m_ulaw_lookup;
	std::unique_ptr<uint16_t[]>    m_volume_lookup;

#if ES5506_MAKE_WAVS
	void *      m_wavraw;                 /* raw waveform */
#endif
>>>>>>> upstream/master

	const char * m_region0;                       /* memory region where the sample ROM lives */
	const char * m_region1;                       /* memory region where the sample ROM lives */
	const char * m_region2;                       /* memory region where the sample ROM lives */
	const char * m_region3;                       /* memory region where the sample ROM lives */
	int m_channels;                               /* number of output channels: 1 .. 6 */
	devcb_write_line m_irq_cb;  /* irq callback */
	devcb_read16 m_read_port_cb;          /* input port read */
<<<<<<< HEAD

	void update_irq_state();
	void update_internal_irq_state();
	void compute_tables();

	void generate_dummy(es550x_voice *voice, UINT16 *base, INT32 *lbuffer, INT32 *rbuffer, int samples);
	void generate_ulaw(es550x_voice *voice, UINT16 *base, INT32 *lbuffer, INT32 *rbuffer, int samples);
	void generate_pcm(es550x_voice *voice, UINT16 *base, INT32 *lbuffer, INT32 *rbuffer, int samples);
=======
>>>>>>> upstream/master
};


class es5506_device : public es550x_device
{
public:
<<<<<<< HEAD
	es5506_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	es5506_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
	~es5506_device() {}

	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE8_MEMBER( write );
	void voice_bank_w(int voice, int bank);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);


	void generate_samples(INT32 **outputs, int offset, int samples);

private:
	inline void reg_write_low(es550x_voice *voice, offs_t offset, UINT32 data);
	inline void reg_write_high(es550x_voice *voice, offs_t offset, UINT32 data);
	inline void reg_write_test(es550x_voice *voice, offs_t offset, UINT32 data);
	inline UINT32 reg_read_low(es550x_voice *voice, offs_t offset);
	inline UINT32 reg_read_high(es550x_voice *voice, offs_t offset);
	inline UINT32 reg_read_test(es550x_voice *voice, offs_t offset);
};

extern const device_type ES5506;
=======
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;


	void generate_samples(int32_t **outputs, int offset, int samples);

private:
	inline void reg_write_low(es550x_voice *voice, offs_t offset, uint32_t data);
	inline void reg_write_high(es550x_voice *voice, offs_t offset, uint32_t data);
	inline void reg_write_test(es550x_voice *voice, offs_t offset, uint32_t data);
	inline uint32_t reg_read_low(es550x_voice *voice, offs_t offset);
	inline uint32_t reg_read_high(es550x_voice *voice, offs_t offset);
	inline uint32_t reg_read_test(es550x_voice *voice, offs_t offset);
};

DECLARE_DEVICE_TYPE(ES5506, es5506_device)
>>>>>>> upstream/master


class es5505_device : public es550x_device
{
public:
<<<<<<< HEAD
	es5505_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	es5505_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ16_MEMBER( read );
	DECLARE_WRITE16_MEMBER( write );
	void voice_bank_w(int voice, int bank);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();

	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

	void generate_samples(INT32 **outputs, int offset, int samples);

private:
	// internal state
	inline void reg_write_low(es550x_voice *voice, offs_t offset, UINT16 data, UINT16 mem_mask);
	inline void reg_write_high(es550x_voice *voice, offs_t offset, UINT16 data, UINT16 mem_mask);
	inline void reg_write_test(es550x_voice *voice, offs_t offset, UINT16 data, UINT16 mem_mask);
	inline UINT16 reg_read_low(es550x_voice *voice, offs_t offset);
	inline UINT16 reg_read_high(es550x_voice *voice, offs_t offset);
	inline UINT16 reg_read_test(es550x_voice *voice, offs_t offset);
};

extern const device_type ES5505;


#endif /* __ES5506_H__ */
=======
	virtual void device_start() override;

	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

	void generate_samples(int32_t **outputs, int offset, int samples);

private:
	// internal state
	inline void reg_write_low(es550x_voice *voice, offs_t offset, uint16_t data, uint16_t mem_mask);
	inline void reg_write_high(es550x_voice *voice, offs_t offset, uint16_t data, uint16_t mem_mask);
	inline void reg_write_test(es550x_voice *voice, offs_t offset, uint16_t data, uint16_t mem_mask);
	inline uint16_t reg_read_low(es550x_voice *voice, offs_t offset);
	inline uint16_t reg_read_high(es550x_voice *voice, offs_t offset);
	inline uint16_t reg_read_test(es550x_voice *voice, offs_t offset);
};

DECLARE_DEVICE_TYPE(ES5505, es5505_device)


#endif // MAME_SOUND_ES5506_H
>>>>>>> upstream/master
