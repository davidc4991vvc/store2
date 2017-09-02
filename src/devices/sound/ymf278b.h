// license:BSD-3-Clause
// copyright-holders:R. Belmont, Olivier Galibert, hap
<<<<<<< HEAD
#pragma once

#ifndef __YMF278B_H__
#define __YMF278B_H__

#include "emu.h"
=======
#ifndef MAME_SOUND_YMF278B_H
#define MAME_SOUND_YMF278B_H

#pragma once

>>>>>>> upstream/master

#define YMF278B_STD_CLOCK (33868800)            /* standard clock for OPL4 */

#define MCFG_YMF278B_IRQ_HANDLER(_devcb) \
	devcb = &ymf278b_device::set_irq_handler(*device, DEVCB_##_devcb);

<<<<<<< HEAD
class ymf278b_device : public device_t,
						public device_sound_interface,
						public device_memory_interface
{
public:
	ymf278b_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration helpers
	template<class _Object> static devcb_base &set_irq_handler(device_t &device, _Object object) { return downcast<ymf278b_device &>(device).m_irq_handler.set_callback(object); }
=======
class ymf278b_device : public device_t, public device_sound_interface, public device_rom_interface
{
public:
	ymf278b_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration helpers
	template <class Object> static devcb_base &set_irq_handler(device_t &device, Object &&cb) { return downcast<ymf278b_device &>(device).m_irq_handler.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE8_MEMBER( write );

<<<<<<< HEAD
	void ymf262_update_request();

protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();
	virtual void device_stop();

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const { return (spacenum == AS_0) ? &m_space_config : NULL; }

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
=======
protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_stop() override;

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

	// device_rom_interface overrides
	virtual void rom_bank_updated() override;
>>>>>>> upstream/master

private:
	struct YMF278BSlot
	{
<<<<<<< HEAD
		INT16 wave;     /* wavetable number */
		INT16 F_NUMBER; /* frequency */
		INT8 octave;    /* octave */
		INT8 preverb;   /* pseudo-reverb */
		INT8 DAMP;      /* damping */
		INT8 CH;        /* output channel */
		INT8 LD;        /* level direct */
		INT8 TL;        /* total level */
		INT8 pan;       /* panpot */
		INT8 LFO;       /* LFO */
		INT8 VIB;       /* vibrato */
		INT8 AM;        /* tremolo */

		INT8 AR;        /* attack rate */
		INT8 D1R;       /* decay 1 rate */
		INT8 DL;        /* decay level */
		INT8 D2R;       /* decay 2 rate */
		INT8 RC;        /* rate correction */
		INT8 RR;        /* release rate */

		UINT32 step;    /* fixed-point frequency step */
		UINT64 stepptr; /* fixed-point pointer into the sample */

		INT8 active;    /* channel is playing */
		INT8 KEY_ON;    /* slot keyed on */
		INT8 bits;      /* width of the samples */
		UINT32 startaddr;
		UINT32 loopaddr;
		UINT32 endaddr;

		int env_step;
		UINT32 env_vol;
		UINT32 env_vol_step;
		UINT32 env_vol_lim;
		INT8 env_preverb;
=======
		int16_t wave;     /* wavetable number */
		int16_t F_NUMBER; /* frequency */
		int8_t octave;    /* octave */
		int8_t preverb;   /* pseudo-reverb */
		int8_t DAMP;      /* damping */
		int8_t CH;        /* output channel */
		int8_t LD;        /* level direct */
		int8_t TL;        /* total level */
		int8_t pan;       /* panpot */
		int8_t LFO;       /* LFO */
		int8_t VIB;       /* vibrato */
		int8_t AM;        /* tremolo */

		int8_t AR;        /* attack rate */
		int8_t D1R;       /* decay 1 rate */
		int8_t DL;        /* decay level */
		int8_t D2R;       /* decay 2 rate */
		int8_t RC;        /* rate correction */
		int8_t RR;        /* release rate */

		uint32_t step;    /* fixed-point frequency step */
		uint64_t stepptr; /* fixed-point pointer into the sample */

		int8_t active;    /* channel is playing */
		int8_t KEY_ON;    /* slot keyed on */
		int8_t bits;      /* width of the samples */
		uint32_t startaddr;
		uint32_t loopaddr;
		uint32_t endaddr;

		int env_step;
		uint32_t env_vol;
		uint32_t env_vol_step;
		uint32_t env_vol_lim;
		int8_t env_preverb;
>>>>>>> upstream/master

		int num;        /* slot number (for debug only) */
	};

	int compute_rate(YMF278BSlot *slot, int val);
<<<<<<< HEAD
	UINT32 compute_decay_env_vol_step(YMF278BSlot *slot, int val);
	void compute_freq_step(YMF278BSlot *slot);
	void compute_envelope(YMF278BSlot *slot);
	void irq_check();
	void A_w(UINT8 reg, UINT8 data);
	void B_w(UINT8 reg, UINT8 data);
	void retrigger_note(YMF278BSlot *slot);
	void C_w(UINT8 reg, UINT8 data);
=======
	uint32_t compute_decay_env_vol_step(YMF278BSlot *slot, int val);
	void compute_freq_step(YMF278BSlot *slot);
	void compute_envelope(YMF278BSlot *slot);
	void irq_check();
	void A_w(uint8_t reg, uint8_t data);
	void B_w(uint8_t reg, uint8_t data);
	void retrigger_note(YMF278BSlot *slot);
	void C_w(uint8_t reg, uint8_t data);
>>>>>>> upstream/master
	void timer_busy_start(int is_pcm);
	void precompute_rate_tables();
	void register_save_state();

<<<<<<< HEAD
	// internal state
	UINT8 m_pcmregs[256];
	YMF278BSlot m_slots[24];
	INT8 m_wavetblhdr;
	INT8 m_memmode;
	INT32 m_memadr;

	UINT8 m_status_busy, m_status_ld;
	emu_timer *m_timer_busy;
	emu_timer *m_timer_ld;
	UINT8 m_exp;

	INT32 m_fm_l, m_fm_r;
	INT32 m_pcm_l, m_pcm_r;

	attotime m_timer_base;
	UINT8 m_timer_a_count, m_timer_b_count;
	UINT8 m_enable, m_current_irq;
	int m_irq_line;

	UINT8 m_port_C, m_port_AB, m_lastport;

	// precomputed tables
	UINT32 m_lut_ar[64];              // attack rate
	UINT32 m_lut_dr[64];              // decay rate
	INT32 m_volume[256*4];            // precalculated attenuation values with some margin for envelope and pan levels
	int m_pan_left[16],m_pan_right[16]; // pan volume offsets
	INT32 m_mix_level[8];
=======
	void update_request() { m_stream_ymf262->update(); }

	static void static_irq_handler(device_t *param, int irq) { }
	static void static_timer_handler(device_t *param, int c, const attotime &period) { }
	static void static_update_request(device_t *param, int interval) { downcast<ymf278b_device *>(param)->update_request(); }

	// internal state
	uint8_t m_pcmregs[256];
	YMF278BSlot m_slots[24];
	int8_t m_wavetblhdr;
	int8_t m_memmode;
	int32_t m_memadr;

	uint8_t m_status_busy, m_status_ld;
	emu_timer *m_timer_busy;
	emu_timer *m_timer_ld;
	uint8_t m_exp;

	int32_t m_fm_l, m_fm_r;
	int32_t m_pcm_l, m_pcm_r;

	attotime m_timer_base;
	uint8_t m_timer_a_count, m_timer_b_count;
	uint8_t m_enable, m_current_irq;
	int m_irq_line;

	uint8_t m_port_C, m_port_AB, m_lastport;

	// precomputed tables
	uint32_t m_lut_ar[64];              // attack rate
	uint32_t m_lut_dr[64];              // decay rate
	int32_t m_volume[256*4];            // precalculated attenuation values with some margin for envelope and pan levels
	int m_pan_left[16],m_pan_right[16]; // pan volume offsets
	int32_t m_mix_level[8];
>>>>>>> upstream/master

	emu_timer *m_timer_a, *m_timer_b;
	int m_clock;

	sound_stream * m_stream;
<<<<<<< HEAD
	INT32 *m_mix_buffer;
	direct_read_data * m_direct;
	const address_space_config m_space_config;
	devcb_write_line m_irq_handler;
	UINT8 m_last_fm_data;
=======
	std::unique_ptr<int32_t[]> m_mix_buffer;
	devcb_write_line m_irq_handler;
	uint8_t m_last_fm_data;
>>>>>>> upstream/master

	// ymf262
	void *m_ymf262;
	sound_stream * m_stream_ymf262;
};

<<<<<<< HEAD
extern const device_type YMF278B;


#endif /* __YMF278B_H__ */
=======
DECLARE_DEVICE_TYPE(YMF278B, ymf278b_device)

#endif // MAME_SOUND_YMF278B_H
>>>>>>> upstream/master
