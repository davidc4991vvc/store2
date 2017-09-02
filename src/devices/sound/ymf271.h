// license:BSD-3-Clause
// copyright-holders:Olivier Galibert, R. Belmont, hap
<<<<<<< HEAD
#pragma once

#ifndef __YMF271_H__
#define __YMF271_H__

#include "emu.h"
=======
#ifndef MAME_SOUND_YMF271_H
#define MAME_SOUND_YMF271_H

#pragma once

>>>>>>> upstream/master

#define MCFG_YMF271_IRQ_HANDLER(_devcb) \
	devcb = &ymf271_device::set_irq_handler(*device, DEVCB_##_devcb);

#define MCFG_YMF271_EXT_READ_HANDLER(_devcb) \
	devcb = &ymf271_device::set_ext_read_handler(*device, DEVCB_##_devcb);

#define MCFG_YMF271_EXT_WRITE_HANDLER(_devcb) \
	devcb = &ymf271_device::set_ext_write_handler(*device, DEVCB_##_devcb);

<<<<<<< HEAD
class ymf271_device : public device_t,
									public device_sound_interface
{
public:
	ymf271_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration helpers
	template<class _Object> static devcb_base &set_irq_handler(device_t &device, _Object object) { return downcast<ymf271_device &>(device).m_irq_handler.set_callback(object); }
	template<class _Object> static devcb_base &set_ext_read_handler(device_t &device, _Object object) { return downcast<ymf271_device &>(device).m_ext_read_handler.set_callback(object); }
	template<class _Object> static devcb_base &set_ext_write_handler(device_t &device, _Object object) { return downcast<ymf271_device &>(device).m_ext_write_handler.set_callback(object); }
=======
class ymf271_device : public device_t, public device_sound_interface
{
public:
	ymf271_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration helpers
	template <class Object> static devcb_base &set_irq_handler(device_t &device, Object &&cb) { return downcast<ymf271_device &>(device).m_irq_handler.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_ext_read_handler(device_t &device, Object &&cb) { return downcast<ymf271_device &>(device).m_ext_read_handler.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_ext_write_handler(device_t &device, Object &&cb) { return downcast<ymf271_device &>(device).m_ext_write_handler.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE8_MEMBER( write );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
private:
	struct YMF271Slot
	{
		UINT8 ext_en;
		UINT8 ext_out;
		UINT8 lfoFreq;
		UINT8 lfowave;
		UINT8 pms, ams;
		UINT8 detune;
		UINT8 multiple;
		UINT8 tl;
		UINT8 keyscale;
		UINT8 ar;
		UINT8 decay1rate, decay2rate;
		UINT8 decay1lvl;
		UINT8 relrate;
		UINT8 block;
		UINT8 fns_hi;
		UINT32 fns;
		UINT8 feedback;
		UINT8 waveform;
		UINT8 accon;
		UINT8 algorithm;
		UINT8 ch0_level, ch1_level, ch2_level, ch3_level;

		UINT32 startaddr;
		UINT32 loopaddr;
		UINT32 endaddr;
		UINT8 altloop;
		UINT8 fs;
		UINT8 srcnote, srcb;

		UINT32 step;
		UINT64 stepptr;

		UINT8 active;
		UINT8 bits;

		// envelope generator
		INT32 volume;
		INT32 env_state;
		INT32 env_attack_step;      // volume increase step in attack state
		INT32 env_decay1_step;
		INT32 env_decay2_step;
		INT32 env_release_step;

		INT64 feedback_modulation0;
		INT64 feedback_modulation1;
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	virtual void device_clock_changed() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

private:
	struct YMF271Slot
	{
		uint8_t ext_en;
		uint8_t ext_out;
		uint8_t lfoFreq;
		uint8_t lfowave;
		uint8_t pms, ams;
		uint8_t detune;
		uint8_t multiple;
		uint8_t tl;
		uint8_t keyscale;
		uint8_t ar;
		uint8_t decay1rate, decay2rate;
		uint8_t decay1lvl;
		uint8_t relrate;
		uint8_t block;
		uint8_t fns_hi;
		uint32_t fns;
		uint8_t feedback;
		uint8_t waveform;
		uint8_t accon;
		uint8_t algorithm;
		uint8_t ch0_level, ch1_level, ch2_level, ch3_level;

		uint32_t startaddr;
		uint32_t loopaddr;
		uint32_t endaddr;
		uint8_t altloop;
		uint8_t fs;
		uint8_t srcnote, srcb;

		uint32_t step;
		uint64_t stepptr;

		uint8_t active;
		uint8_t bits;

		// envelope generator
		int32_t volume;
		int32_t env_state;
		int32_t env_attack_step;      // volume increase step in attack state
		int32_t env_decay1_step;
		int32_t env_decay2_step;
		int32_t env_release_step;

		int64_t feedback_modulation0;
		int64_t feedback_modulation1;
>>>>>>> upstream/master

		int lfo_phase, lfo_step;
		int lfo_amplitude;
		double lfo_phasemod;
	};

	struct YMF271Group
	{
<<<<<<< HEAD
		UINT8 sync, pfm;
=======
		uint8_t sync, pfm;
>>>>>>> upstream/master
	};

	void init_state();
	void init_tables();
<<<<<<< HEAD
=======
	void calculate_clock_correction();
>>>>>>> upstream/master
	void calculate_step(YMF271Slot *slot);
	void update_envelope(YMF271Slot *slot);
	void init_envelope(YMF271Slot *slot);
	void init_lfo(YMF271Slot *slot);
	void update_lfo(YMF271Slot *slot);
<<<<<<< HEAD
	INT64 calculate_slot_volume(YMF271Slot *slot);
	void update_pcm(int slotnum, INT32 *mixp, int length);
	INT64 calculate_op(int slotnum, INT64 inp);
	void set_feedback(int slotnum, INT64 inp);
	void write_register(int slotnum, int reg, UINT8 data);
	void ymf271_write_fm(int bank, UINT8 address, UINT8 data);
	void ymf271_write_pcm(UINT8 address, UINT8 data);
	void ymf271_write_timer(UINT8 address, UINT8 data);
	UINT8 ymf271_read_memory(UINT32 offset);
=======
	int64_t calculate_slot_volume(YMF271Slot *slot);
	void update_pcm(int slotnum, int32_t *mixp, int length);
	int64_t calculate_op(int slotnum, int64_t inp);
	void set_feedback(int slotnum, int64_t inp);
	void write_register(int slotnum, int reg, uint8_t data);
	void ymf271_write_fm(int bank, uint8_t address, uint8_t data);
	void ymf271_write_pcm(uint8_t address, uint8_t data);
	void ymf271_write_timer(uint8_t address, uint8_t data);
	uint8_t ymf271_read_memory(uint32_t offset);
>>>>>>> upstream/master

	inline int get_keyscaled_rate(int rate, int keycode, int keyscale);
	inline int get_internal_keycode(int block, int fns);
	inline int get_external_keycode(int block, int fns);
	inline bool check_envelope_end(YMF271Slot *slot);

	// lookup tables
<<<<<<< HEAD
	INT16 *m_lut_waves[8];
	double *m_lut_plfo[4][8];
	int *m_lut_alfo[4];
=======
	std::unique_ptr<int16_t[]> m_lut_waves[8];
	std::unique_ptr<double[]> m_lut_plfo[4][8];
	std::unique_ptr<int[]> m_lut_alfo[4];
>>>>>>> upstream/master
	double m_lut_ar[64];
	double m_lut_dc[64];
	double m_lut_lfo[256];
	int m_lut_attenuation[16];
	int m_lut_total_level[128];
	int m_lut_env_volume[256];

	// internal state
	YMF271Slot m_slots[48];
	YMF271Group m_groups[12];

<<<<<<< HEAD
	UINT8 m_regs_main[0x10];

	UINT32 m_timerA;
	UINT32 m_timerB;
	UINT8 m_irqstate;
	UINT8 m_status;
	UINT8 m_enable;

	UINT32 m_ext_address;
	UINT8 m_ext_rw;
	UINT8 m_ext_readlatch;

	UINT8 *m_mem_base;
	UINT32 m_mem_size;
	UINT32 m_clock;

	emu_timer *m_timA, *m_timB;
	sound_stream *m_stream;
	INT32 *m_mix_buffer;
=======
	uint8_t m_regs_main[0x10];

	uint32_t m_timerA;
	uint32_t m_timerB;
	uint8_t m_irqstate;
	uint8_t m_status;
	uint8_t m_enable;

	uint32_t m_ext_address;
	uint8_t m_ext_rw;
	uint8_t m_ext_readlatch;

	optional_region_ptr<uint8_t> m_mem_base;
	uint32_t m_mem_size;

	emu_timer *m_timA;
	emu_timer *m_timB;
	sound_stream *m_stream;
	std::unique_ptr<int32_t[]> m_mix_buffer;
>>>>>>> upstream/master

	devcb_write_line m_irq_handler;
	devcb_read8 m_ext_read_handler;
	devcb_write8 m_ext_write_handler;
};

<<<<<<< HEAD
extern const device_type YMF271;


#endif /* __YMF271_H__ */
=======
DECLARE_DEVICE_TYPE(YMF271, ymf271_device)

#endif // MAME_SOUND_YMF271_H
>>>>>>> upstream/master
