// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Aaron Giles
=======
// copyright-holders:Olivier Galibert
>>>>>>> upstream/master
/***************************************************************************

    votrax.h

<<<<<<< HEAD
    Simple VOTRAX SC-01 simulator based on sample fragments.

***************************************************************************/

#pragma once

#ifndef __VOTRAX_H__
#define __VOTRAX_H__

#include "sound/samples.h"


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_VOTRAX_SC01_REQUEST_CB(_devcb) \
	devcb = &votrax_sc01_device::set_request_callback(*device, DEVCB_##_devcb);


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> votrax_sc01_device
=======
    Votrax SC01A simulation

***************************************************************************/
#ifndef MAME_SOUND_VOTRAX_H
#define MAME_SOUND_VOTRAX_H

#pragma once


#define MCFG_VOTRAX_SC01_REQUEST_CB(_devcb) \
	devcb = &downcast<votrax_sc01_device *>(device)->set_ar_callback(DEVCB_##_devcb);
>>>>>>> upstream/master

class votrax_sc01_device :  public device_t,
							public device_sound_interface
{
public:
<<<<<<< HEAD
	// construction/destruction
	votrax_sc01_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	template<class _Object> static devcb_base &set_request_callback(device_t &device, _Object object) { return downcast<votrax_sc01_device &>(device).m_request_cb.set_callback(object); }

	// writers
	DECLARE_WRITE8_MEMBER( write );
	DECLARE_WRITE8_MEMBER( inflection_w );
	DECLARE_READ_LINE_MEMBER( request ) { return m_request_state; }

protected:
	// device-level overrides
	virtual const rom_entry *device_rom_region() const;
	virtual void device_start();
	virtual void device_reset();
	virtual void device_clock_changed();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// device_sound_interface overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

private:
	// internal helpers
	void update_subphoneme_clock_period();
	static double bits_to_caps(UINT32 value, int caps_count, const double *caps_values);
	static void shift_hist(double val, double *hist_array, int hist_size);
	static void filter_s_to_z(const double *k, double fs, double *a, double *b);
	static double apply_filter(const double *x, const double *y, const double *a, const double *b);

	// internal state
	sound_stream *              m_stream;               // output stream
	emu_timer *                 m_phoneme_timer;        // phoneme timer
	const UINT8 *               m_rom;                  // pointer to our ROM

	// inputs
	UINT8                       m_inflection;           // 2-bit inflection value
	UINT8                       m_phoneme;              // 6-bit phoneme value

	// outputs
	devcb_write_line           m_request_cb;           // callback for request
	UINT8                       m_request_state;        // request as seen to the outside world
	UINT8                       m_internal_request;     // request managed by stream timing

	// timing circuit
	UINT32                      m_master_clock_freq;    // frequency of the master clock
	UINT8                       m_master_clock;         // master clock
	UINT16                      m_counter_34;           // ripple counter @ 34
	UINT8                       m_latch_70;             // 4-bit latch @ 70
	UINT8                       m_latch_72;             // 4-bit latch @ 72
	UINT8                       m_beta1;                // beta1 clock state
	UINT8                       m_p2;                   // P2 clock state
	UINT8                       m_p1;                   // P1 clock state
	UINT8                       m_phi2;                 // phi2 clock state
	UINT8                       m_phi1;                 // phi1 clock state
	UINT8                       m_phi2_20;              // alternate phi2 clock state (20kHz)
	UINT8                       m_phi1_20;              // alternate phi1 clock state (20kHz)
	UINT32                      m_subphoneme_period;    // period of the subphoneme timer
	UINT32                      m_subphoneme_count;     // number of ticks executed already
	UINT8                       m_clock_88;             // subphoneme clock output @ 88
	UINT8                       m_latch_42;             // D flip-flop @ 42
	UINT8                       m_counter_84;           // 4-bit phoneme counter @ 84
	UINT8                       m_latch_92;             // 2-bit latch @ 92

	// low parameter clocking
	bool                        m_srff_132;             // S/R flip-flop @ 132
	bool                        m_srff_114;             // S/R flip-flop @ 114
	bool                        m_srff_112;             // S/R flip-flop @ 112
	bool                        m_srff_142;             // S/R flip-flop @ 142
	UINT8                       m_latch_80;             // phoneme timing latch @ 80

	// glottal circuit
	UINT8                       m_counter_220;          // 4-bit counter @ 220
	UINT8                       m_counter_222;          // 4-bit counter @ 222
	UINT8                       m_counter_224;          // 4-bit counter @ 224
	UINT8                       m_counter_234;          // 4-bit counter @ 234
	UINT8                       m_counter_236;          // 4-bit counter @ 236
	UINT8                       m_fgate;                // FGATE signal
	UINT8                       m_glottal_sync;         // Glottal Sync signal

	// transition circuit
	UINT8                       m_0625_clock;           // state of 0.625kHz clock
	UINT8                       m_counter_46;           // 4-bit counter in block @ 46
	UINT8                       m_latch_46;             // 4-bit latch in block @ 46
	UINT8                       m_ram[8];               // RAM to hold parameters
	UINT8                       m_latch_168;            // 4-bit latch @ 168
	UINT8                       m_latch_170;            // 4-bit latch @ 170
	UINT8                       m_f1;                   // latched 4-bit F1 value
	UINT8                       m_f2;                   // latched 5-bit F2 value
	UINT8                       m_fc;                   // latched 4-bit FC value
	UINT8                       m_f3;                   // latched 4-bit F3 value
	UINT8                       m_f2q;                  // latched 4-bit F2Q value
	UINT8                       m_va;                   // latched 4-bit VA value
	UINT8                       m_fa;                   // latched 4-bit FA value

	// noise generator circuit
	UINT8                       m_noise_clock;          // clock input to noise generator
	UINT32                      m_shift_252;            // shift register @ 252
	UINT8                       m_counter_250;          // 4-bit counter @ 250

	// stages outputs history
	double                      m_ni_hist[4];
	double                      m_no_hist[4];
	double                      m_va_hist[4];
	double                      m_s1_hist[4];
	double                      m_s2g_hist[4];
	double                      m_s2ni_hist[4];
	double                      m_s2n_hist[4];
	double                      m_s2_hist[4];
	double                      m_s3_hist[4];
	double                      m_s4i_hist[4];
	double                      m_s4_hist[4];

	// static tables
	static const char *const s_phoneme_table[64];
	static const double s_glottal_wave[16];
};



=======
	static constexpr feature_type imperfect_features() { return feature::SOUND; }

	// construction/destruction
	votrax_sc01_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> devcb_base &set_ar_callback(Object &&cb) { return m_ar_cb.set_callback(std::forward<Object>(cb)); }

	DECLARE_WRITE8_MEMBER(write);
	DECLARE_WRITE8_MEMBER(inflection_w);
	DECLARE_READ_LINE_MEMBER(request) { m_stream->update(); return m_ar_state; }

protected:
	// device-level overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_clock_changed() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// device_sound_interface overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

private:
	// Possible timer parameters
	enum {
		T_COMMIT_PHONE,
		T_END_OF_PHONE
	};

	static const char *const s_phone_table[64];
	static const double s_glottal_wave[9];

	sound_stream *m_stream;                         // Output stream
	emu_timer *m_timer;                             // General timer
	required_memory_region m_rom;                   // Internal ROM
	u32 m_mainclock;                                // Current main clock
	double m_sclock;                                // Stream sample clock (40KHz, main/18)
	double m_cclock;                                // 20KHz capacitor switching clock (main/36)
	u32 m_sample_count;                             // Sample counter, to cadence chip updates

	// Inputs
	u8 m_inflection;                                // 2-bit inflection value
	u8 m_phone;                                     // 6-bit phone value

	// Outputs
	devcb_write_line m_ar_cb;                       // Callback for ar
	bool m_ar_state;                                // Current ar state

	// "Unpacked" current rom values
	u8 m_rom_duration;                              // Duration in 5KHz units (main/144) of one tick, 16 ticks per phone, 7 bits
	u8 m_rom_vd, m_rom_cld;                         // Duration in ticks of the "voice" and "closure" delays, 4 bits
	u8 m_rom_fa, m_rom_fc, m_rom_va;                // Analog parameters, noise volume, noise freq cutoff and voice volume, 4 bits each
	u8 m_rom_f1, m_rom_f2, m_rom_f2q, m_rom_f3;     // Analog parameters, formant frequencies and Q, 4 bits each
	bool m_rom_closure;                             // Closure bit, true = silence at cld
	bool m_rom_pause;                               // Pause bit

	// Current interpolated values (8 bits each)
	u8 m_cur_fa, m_cur_fc, m_cur_va;
	u8 m_cur_f1, m_cur_f2, m_cur_f2q, m_cur_f3;

	// Current committed values
	u8 m_filt_fa, m_filt_fc, m_filt_va;             // Analog parameters, noise volume, noise freq cutoff and voice volume, 4 bits each
	u8 m_filt_f1, m_filt_f2, m_filt_f2q, m_filt_f3; // Analog parameters, formant frequencies/Q on 4 bits except f2 on 5 bits

	// Internal counters
	u16 m_phonetick;                                // 9-bits phone tick duration counter
	u8  m_ticks;                                    // 5-bits tick counter
	u8  m_pitch;                                    // 7-bits pitch counter
	u8  m_closure;                                  // 5-bits glottal closure counter
	u8  m_update_counter;                           // 6-bits counter for the 625Hz (main/1152) and 208Hz (main/3456) update timing generators

	// Internal state
	bool m_cur_closure;                             // Current internal closure state
	u16 m_noise;                                    // 15-bit noise shift register
	bool m_cur_noise;                               // Current noise output

	// Filter coefficients and level histories
	double m_voice_1[4];
	double m_voice_2[4];
	double m_voice_3[4];

	double m_noise_1[3];
	double m_noise_2[3];
	double m_noise_3[2];
	double m_noise_4[2];

	double m_vn_1[4];
	double m_vn_2[4];
	double m_vn_3[4];
	double m_vn_4[4];
	double m_vn_5[2];
	double m_vn_6[2];

	double m_f1_a[4],  m_f1_b[4];                   // F1 filtering
	double m_f2v_a[4], m_f2v_b[4];                  // F2 voice filtering
	double m_f2n_a[2], m_f2n_b[2];                  // F2 noise filtering
	double m_f3_a[4],  m_f3_b[4];                   // F3 filtering
	double m_f4_a[4],  m_f4_b[4];                   // F4 filtering
	double m_fx_a[1],  m_fx_b[2];                   // Final filtering
	double m_fn_a[3],  m_fn_b[3];                   // Noise shaping

	// Compute a total capacitor value based on which bits are currently active
	static double bits_to_caps(u32 value, std::initializer_list<double> caps_values) {
		double total = 0;
		for(double d : caps_values) {
			if(value & 1)
				total += d;
			value >>= 1;
		}
		return total;
	}

	// Shift a history of values by one and insert the new value at the front
	template<u32 N> static void shift_hist(double val, double (&hist_array)[N]) {
		for(u32 i=N-1; i>0; i--)
			hist_array[i] = hist_array[i-1];
		hist_array[0] = val;
	}

	// Apply a filter and compute the result. 'a' is applied to x (inputs) and 'b' to y (outputs)
	template<u32 Nx, u32 Ny, u32 Na, u32 Nb> static double apply_filter(const double (&x)[Nx], const double (&y)[Ny], const double (&a)[Na], const double (&b)[Nb]) {
		double total = 0;
		for(u32 i=0; i<Na; i++)
			total += x[i] * a[i];
		for(u32 i=1; i<Nb; i++)
			total -= y[i-1] * b[i];
		return total / b[0];
	}

	void build_standard_filter(double *a, double *b,
							   double c1t, // Unswitched cap, input, top
							   double c1b, // Switched cap, input, bottom
							   double c2t, // Unswitched cap, over first amp-op, top
							   double c2b, // Switched cap, over first amp-op, bottom
							   double c3,  // Cap between the two op-amps
							   double c4); // Cap over second op-amp

	void build_noise_shaper_filter(double *a, double *b,
								   double c1,  // Cap over first amp-op
								   double c2t, // Unswitched cap between amp-ops, input, top
								   double c2b, // Switched cap between amp-ops, input, bottom
								   double c3,  // Cap over second amp-op
								   double c4); // Switched cap after second amp-op

	void build_lowpass_filter(double *a, double *b,
							  double c1t,  // Unswitched cap, over amp-op, top
							  double c1b); // Switched cap, over amp-op, bottom

	void build_injection_filter(double *a, double *b,
								double c1b, // Switched cap, input, bottom
								double c2t, // Unswitched cap, over first amp-op, top
								double c2b, // Switched cap, over first amp-op, bottom
								double c3,  // Cap between the two op-amps
								double c4); // Cap over second op-amp


	static void interpolate(u8 &reg, u8 target);    // Do one interpolation step
	void chip_update();                             // Global update called at 20KHz (main/36)
	void filters_commit(bool force);                // Commit the currently computed interpolation values to the filters
	void phone_commit();                            // Commit the current phone id
	stream_sample_t analog_calc();                  // Compute one more sample
};


>>>>>>> upstream/master
//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

// device type definition
<<<<<<< HEAD
extern const device_type VOTRAX_SC01;


#endif /* __VOTRAX_H__ */
=======
DECLARE_DEVICE_TYPE(VOTRAX_SC01, votrax_sc01_device)

#endif // MAME_SOUND_VOTRAX_H
>>>>>>> upstream/master
