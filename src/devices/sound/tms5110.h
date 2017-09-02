<<<<<<< HEAD
// license:???
// copyright-holders:Frank Palazzolo, Jarek Burczynski, Aaron Giles, Jonathan Gevaryahu, Couriersud
#pragma once

#ifndef __TMS5110_H__
#define __TMS5110_H__

#include "emu.h"

/* HACK: if defined, uses impossibly perfect 'straight line' interpolation */
#undef PERFECT_INTERPOLATION_HACK

/* TMS5110 commands */
										/* CTL8  CTL4  CTL2  CTL1  |   PDC's  */
										/* (MSB)             (LSB) | required */
#define TMS5110_CMD_RESET        (0) /*    0     0     0     x  |     1    */
#define TMS5110_CMD_LOAD_ADDRESS (2) /*    0     0     1     x  |     2    */
#define TMS5110_CMD_OUTPUT       (4) /*    0     1     0     x  |     3    */
#define TMS5110_CMD_SPKSLOW      (6) /*    0     1     1     x  |     1    | Note: this command is undocumented on the datasheets, it only appears on the patents. It might not actually work properly on some of the real chips as manufactured. Acts the same as CMD_SPEAK, but makes the interpolator take three A cycles whereever it would normally only take one, effectively making speech of any given word take twice as long as normal. */
#define TMS5110_CMD_READ_BIT     (8) /*    1     0     0     x  |     1    */
#define TMS5110_CMD_SPEAK       (10) /*    1     0     1     x  |     1    */
#define TMS5110_CMD_READ_BRANCH (12) /*    1     1     0     x  |     1    */
#define TMS5110_CMD_TEST_TALK   (14) /*    1     1     1     x  |     3    */
=======
// license:BSD-3-Clause
// copyright-holders:Frank Palazzolo, Jarek Burczynski, Aaron Giles, Jonathan Gevaryahu, Couriersud
#ifndef MAME_SOUND_TMS5110_H
#define MAME_SOUND_TMS5110_H

#pragma once


/* HACK: if defined, uses impossibly perfect 'straight line' interpolation */
#undef TMS5110_PERFECT_INTERPOLATION_HACK
>>>>>>> upstream/master

/* clock rate = 80 * output sample rate,     */
/* usually 640000 for 8000 Hz sample rate or */
/* usually 800000 for 10000 Hz sample rate.  */

#define MCFG_TMS5110_M0_CB(_devcb) \
	devcb = &tms5110_device::set_m0_callback(*device, DEVCB_##_devcb);

#define MCFG_TMS5110_M1_CB(_devcb) \
	devcb = &tms5110_device::set_m1_callback(*device, DEVCB_##_devcb);

#define MCFG_TMS5110_ADDR_CB(_devcb) \
	devcb = &tms5110_device::set_addr_callback(*device, DEVCB_##_devcb);

#define MCFG_TMS5110_DATA_CB(_devcb) \
	devcb = &tms5110_device::set_data_callback(*device, DEVCB_##_devcb);

#define MCFG_TMS5110_ROMCLK_CB(_devcb) \
	devcb = &tms5110_device::set_romclk_callback(*device, DEVCB_##_devcb);


<<<<<<< HEAD
class tms5110_device : public device_t,
						public device_sound_interface
{
public:
	tms5110_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	tms5110_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	template<class _Object> static devcb_base &set_m0_callback(device_t &device, _Object object) { return downcast<tms5110_device &>(device).m_m0_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_m1_callback(device_t &device, _Object object) { return downcast<tms5110_device &>(device).m_m1_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_addr_callback(device_t &device, _Object object) { return downcast<tms5110_device &>(device).m_addr_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_data_callback(device_t &device, _Object object) { return downcast<tms5110_device &>(device).m_data_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_romclk_callback(device_t &device, _Object object) { return downcast<tms5110_device &>(device).m_romclk_cb.set_callback(object); }
=======
class tms5110_device : public device_t, public device_sound_interface
{
public:
	/* TMS5110 commands */
													/* CTL8  CTL4  CTL2  CTL1  |   PDC's  */
													/* (MSB)             (LSB) | required */
	static constexpr uint8_t CMD_RESET        = 0;  /*    0     0     0     x  |     1    */
	static constexpr uint8_t CMD_LOAD_ADDRESS = 2;  /*    0     0     1     x  |     2    */
	static constexpr uint8_t CMD_OUTPUT       = 4;  /*    0     1     0     x  |     3    */
	static constexpr uint8_t CMD_SPKSLOW      = 6;  /*    0     1     1     x  |     1    */
	/* Note: TMS5110_CMD_SPKSLOW is undocumented on the datasheets, it only appears
	   on the patents. It might not actually work properly on some of the real
	   chips as manufactured. Acts the same as CMD_SPEAK, but makes the
	   interpolator take two A cycles wherever it would normally only take one,
	   effectively making speech of any given word take 1.5x as long as normal. */
	static constexpr uint8_t CMD_READ_BIT    =  8;  /*    1     0     0     x  |     1    */
	static constexpr uint8_t CMD_SPEAK       = 10;  /*    1     0     1     x  |     1    */
	static constexpr uint8_t CMD_READ_BRANCH = 12;  /*    1     1     0     x  |     1    */
	static constexpr uint8_t CMD_TEST_TALK   = 14;  /*    1     1     1     x  |     3    */

	tms5110_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static devcb_base &set_m0_callback(device_t &device, Object &&cb) { return downcast<tms5110_device &>(device).m_m0_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_m1_callback(device_t &device, Object &&cb) { return downcast<tms5110_device &>(device).m_m1_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_addr_callback(device_t &device, Object &&cb) { return downcast<tms5110_device &>(device).m_addr_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_data_callback(device_t &device, Object &&cb) { return downcast<tms5110_device &>(device).m_data_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_romclk_callback(device_t &device, Object &&cb) { return downcast<tms5110_device &>(device).m_romclk_cb.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER( ctl_w );
	DECLARE_READ8_MEMBER( ctl_r );
	DECLARE_WRITE_LINE_MEMBER( pdc_w );

<<<<<<< HEAD
	/* this is only used by cvs.c
	 * it is not related at all to the speech generation
	 * and conflicts with the new rom controller interface.
	 */
	DECLARE_READ8_MEMBER( romclk_hack_r );

	void set_frequency(int frequency);

	int _speech_rom_read_bit();
	void _speech_rom_set_addr(int addr);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

	void set_variant(int variant);

	UINT8 m_SPEN;             /* set on speak command, cleared on stop command or reset command */
	UINT8 m_TALK;             /* set on SPEN & RESETL4(pc12->pc0 transition), cleared on stop command or reset command */
#define TALK_STATUS (m_SPEN|m_TALKD)
	UINT8 m_TALKD;            /* TALK(TCON) value, latched every RESETL4 */
	sound_stream *m_stream;

private:
	void new_int_write(UINT8 rc, UINT8 m0, UINT8 m1, UINT8 addr);
	void new_int_write_addr(UINT8 addr);
	UINT8 new_int_read();
	void register_for_save_states();
	int extract_bits(int count);
	void perform_dummy_read();
	INT32 lattice_filter();
	void process(INT16 *buffer, unsigned int size);
	void PDC_set(int data);
	void parse_frame();

	// internal state
	/* coefficient tables */
	int m_variant;                /* Variant of the 5110 - see tms5110.h */
=======
	// this is only used by cvs.c
	// it is not related at all to the speech generation and conflicts with the new ROM controller interface.
	DECLARE_READ_LINE_MEMBER( romclk_hack_r );

protected:
	tms5110_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, int variant);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_clock_changed() override;

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

	uint8_t TALK_STATUS() const { return m_SPEN | m_TALKD; }

	uint8_t m_SPEN;             /* set on speak command, cleared on stop command or reset command */
	uint8_t m_TALK;             /* set on SPEN & RESETL4(pc12->pc0 transition), cleared on stop command or reset command */
	uint8_t m_TALKD;            /* TALK(TCON) value, latched every RESETL4 */
	sound_stream *m_stream;

private:
	void new_int_write(uint8_t rc, uint8_t m0, uint8_t m1, uint8_t addr);
	void new_int_write_addr(uint8_t addr);
	uint8_t new_int_read();
	void register_for_save_states();
	int extract_bits(int count);
	void perform_dummy_read();
	int32_t lattice_filter();
	void process(int16_t *buffer, unsigned int size);
	void PDC_set(int data);
	void parse_frame();

	uint8_t &OLD_FRAME_SILENCE_FLAG() { return m_OLDE; } // 1 if E=0, 0 otherwise.
	uint8_t &OLD_FRAME_UNVOICED_FLAG() { return m_OLDP; } // 1 if P=0 (unvoiced), 0 if voiced

	bool NEW_FRAME_STOP_FLAG() const { return m_new_frame_energy_idx == 0x0F; } // 1 if this is a stop (Energy = 0x0F) frame
	bool NEW_FRAME_SILENCE_FLAG() const { return m_new_frame_energy_idx == 0; } // ditto as above
	bool NEW_FRAME_UNVOICED_FLAG() const { return m_new_frame_pitch_idx == 0; } // ditto as above

	// internal state
	/* table */
	optional_region_ptr<uint8_t> m_table;

	/* coefficient tables */
	const int m_variant;                /* Variant of the 5110 - see tms5110.h */
>>>>>>> upstream/master

	/* coefficient tables */
	const struct tms5100_coeffs *m_coeff;

	/* these contain global status bits */
<<<<<<< HEAD
	UINT8 m_PDC;
	UINT8 m_CTL_pins;
	UINT8 m_state;

	/* Rom interface */
	UINT32 m_address;
	UINT8  m_next_is_address;
	UINT8  m_schedule_dummy_read;
	UINT8  m_addr_bit;
	/* read byte */
	UINT8  m_CTL_buffer;
=======
	uint8_t m_PDC;
	uint8_t m_CTL_pins;
	uint8_t m_state;

	/* Rom interface */
	uint32_t m_address;
	uint8_t  m_next_is_address;
	uint8_t  m_schedule_dummy_read;
	uint8_t  m_addr_bit;
	/* read byte */
	uint8_t  m_CTL_buffer;
>>>>>>> upstream/master

	/* callbacks */
	devcb_write_line   m_m0_cb;      // the M0 line
	devcb_write_line   m_m1_cb;      // the M1 line
	devcb_write8       m_addr_cb;    // Write to ADD1,2,4,8 - 4 address bits
	devcb_read_line    m_data_cb;    // Read one bit from ADD8/Data - voice data
	// On a real chip rom_clk is running all the time
	// Here, we only use it to properly emulate the protocol.
	// Do not rely on it to be a timed signal.
	devcb_write_line   m_romclk_cb;  // rom clock - Only used to drive the data lines

	/* these contain data describing the current and previous voice frames */
<<<<<<< HEAD
#define OLD_FRAME_SILENCE_FLAG m_OLDE // 1 if E=0, 0 otherwise.
#define OLD_FRAME_UNVOICED_FLAG m_OLDP // 1 if P=0 (unvoiced), 0 if voiced
	UINT8 m_OLDE;
	UINT8 m_OLDP;

#define NEW_FRAME_STOP_FLAG (m_new_frame_energy_idx == 0xF) // 1 if this is a stop (Energy = 0xF) frame
#define NEW_FRAME_SILENCE_FLAG (m_new_frame_energy_idx == 0) // ditto as above
#define NEW_FRAME_UNVOICED_FLAG (m_new_frame_pitch_idx == 0) // ditto as above
	UINT8 m_new_frame_energy_idx;
	UINT8 m_new_frame_pitch_idx;
	UINT8 m_new_frame_k_idx[10];


	/* these are all used to contain the current state of the sound generation */
#ifndef PERFECT_INTERPOLATION_HACK
	INT16 m_current_energy;
	INT16 m_current_pitch;
	INT16 m_current_k[10];
#else
	UINT8 m_old_frame_energy_idx;
	UINT8 m_old_frame_pitch_idx;
	UINT8 m_old_frame_k_idx[10];
	UINT8 m_old_zpar;
	UINT8 m_old_uv_zpar;

	INT32 m_current_energy;
	INT32 m_current_pitch;
	INT32 m_current_k[10];
#endif

	UINT16 m_previous_energy; /* needed for lattice filter to match patent */

	UINT8 m_subcycle;         /* contains the current subcycle for a given PC: 0 is A' (only used on SPKSLOW mode on 51xx), 1 is A, 2 is B */
	UINT8 m_subc_reload;      /* contains 1 for normal speech, 0 when SPKSLOW is active */
	UINT8 m_PC;               /* current parameter counter (what param is being interpolated), ranges from 0 to 12 */
	/* NOTE: the interpolation period counts 1,2,3,4,5,6,7,0 for divide by 8,8,8,4,4,2,2,1 */
	UINT8 m_IP;               /* the current interpolation period */
	UINT8 m_inhibit;          /* If 1, interpolation is inhibited until the DIV1 period */
	UINT8 m_uv_zpar;          /* If 1, zero k5 thru k10 coefficients */
	UINT8 m_zpar;             /* If 1, zero ALL parameters. */
	UINT8 m_pitch_zero;       /* circuit 412; pitch is forced to zero under certain circumstances */
	UINT16 m_pitch_count;     /* pitch counter; provides chirp rom address */

	INT32 m_u[11];
	INT32 m_x[10];

	UINT16 m_RNG;             /* the random noise generator configuration is: 1 + x + x^3 + x^4 + x^13 TODO: no it isn't */
	INT16 m_excitation_data;
=======
	uint8_t m_OLDE;
	uint8_t m_OLDP;

	uint8_t m_new_frame_energy_idx;
	uint8_t m_new_frame_pitch_idx;
	uint8_t m_new_frame_k_idx[10];


	/* these are all used to contain the current state of the sound generation */
#ifndef TMS5110_PERFECT_INTERPOLATION_HACK
	int16_t m_current_energy;
	int16_t m_current_pitch;
	int16_t m_current_k[10];
#else
	uint8_t m_old_frame_energy_idx;
	uint8_t m_old_frame_pitch_idx;
	uint8_t m_old_frame_k_idx[10];
	uint8_t m_old_zpar;
	uint8_t m_old_uv_zpar;

	int32_t m_current_energy;
	int32_t m_current_pitch;
	int32_t m_current_k[10];
#endif

	uint16_t m_previous_energy; /* needed for lattice filter to match patent */

	uint8_t m_subcycle;         /* contains the current subcycle for a given PC: 0 is A' (only used on SPKSLOW mode on 51xx), 1 is A, 2 is B */
	uint8_t m_subc_reload;      /* contains 1 for normal speech, 0 when SPKSLOW is active */
	uint8_t m_PC;               /* current parameter counter (what param is being interpolated), ranges from 0 to 12 */
	/* NOTE: the interpolation period counts 1,2,3,4,5,6,7,0 for divide by 8,8,8,4,4,2,2,1 */
	uint8_t m_IP;               /* the current interpolation period */
	uint8_t m_inhibit;          /* If 1, interpolation is inhibited until the DIV1 period */
	uint8_t m_uv_zpar;          /* If 1, zero k5 thru k10 coefficients */
	uint8_t m_zpar;             /* If 1, zero ALL parameters. */
	uint8_t m_pitch_zero;       /* circuit 412; pitch is forced to zero under certain circumstances */
	uint16_t m_pitch_count;     /* pitch counter; provides chirp rom address */

	int32_t m_u[11];
	int32_t m_x[10];

	uint16_t m_RNG;             /* the random noise generator configuration is: 1 + x + x^3 + x^4 + x^13 TODO: no it isn't */
	int16_t m_excitation_data;
>>>>>>> upstream/master

	/* The TMS51xx has two different ways of providing output data: the
	   analog speaker pins (which were usually used) and the Digital I/O pin.
	   The internal DAC used to feed the analog pins is only 8 bits, and has the
	   funny clipping/clamping logic, while the digital pin gives full 10 bit
	   resolution of the output data.
	   TODO: add a way to set/reset this other than the FORCE_DIGITAL define
	 */
<<<<<<< HEAD
	UINT8 m_digital_select;

	INT32 m_speech_rom_bitnum;

	UINT8 m_romclk_hack_timer_started;
	UINT8 m_romclk_hack_state;

	emu_timer *m_romclk_hack_timer;
	const UINT8 *m_table;
};

extern const device_type TMS5110;
=======
	uint8_t m_digital_select;

	int32_t m_speech_rom_bitnum;

	uint8_t m_romclk_hack_timer_started;
	uint8_t m_romclk_hack_state;

	emu_timer *m_romclk_hack_timer;
};

>>>>>>> upstream/master

class tms5100_device : public tms5110_device
{
public:
<<<<<<< HEAD
	tms5100_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	// device-level overrides
	virtual void device_start();
};

extern const device_type TMS5100;
=======
	tms5100_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

>>>>>>> upstream/master

class tmc0281_device : public tms5110_device
{
public:
<<<<<<< HEAD
	tmc0281_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	// device-level overrides
	virtual void device_start();
};

extern const device_type TMC0281;
=======
	tmc0281_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

>>>>>>> upstream/master

class tms5100a_device : public tms5110_device
{
public:
<<<<<<< HEAD
	tms5100a_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	// device-level overrides
	virtual void device_start();
};

extern const device_type TMS5100A;
=======
	tms5100a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

>>>>>>> upstream/master

class tmc0281d_device : public tms5110_device
{
public:
<<<<<<< HEAD
	tmc0281d_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	// device-level overrides
	virtual void device_start();
};

extern const device_type TMC0281D;
=======
	tmc0281d_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

>>>>>>> upstream/master

class cd2801_device : public tms5110_device
{
public:
<<<<<<< HEAD
	cd2801_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	// device-level overrides
	virtual void device_start();
};

extern const device_type CD2801;
=======
	cd2801_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

>>>>>>> upstream/master

class cd2802_device : public tms5110_device
{
public:
<<<<<<< HEAD
	cd2802_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	// device-level overrides
	virtual void device_start();
};

extern const device_type CD2802;
=======
	cd2802_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

>>>>>>> upstream/master

class tms5110a_device : public tms5110_device
{
public:
<<<<<<< HEAD
	tms5110a_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	// device-level overrides
	virtual void device_start();
};

extern const device_type TMS5110A;
=======
	tms5110a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

>>>>>>> upstream/master

class m58817_device : public tms5110_device
{
public:
<<<<<<< HEAD
	m58817_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	DECLARE_READ8_MEMBER( status_r );

protected:
	// device-level overrides
	virtual void device_start();
};

extern const device_type M58817;
=======
	m58817_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ8_MEMBER( status_r );
};


DECLARE_DEVICE_TYPE(TMS5110,  tms5110_device)
DECLARE_DEVICE_TYPE(TMS5100,  tms5100_device)
DECLARE_DEVICE_TYPE(TMC0281,  tmc0281_device)
DECLARE_DEVICE_TYPE(TMS5100A, tms5100a_device)
DECLARE_DEVICE_TYPE(TMC0281D, tmc0281d_device)
DECLARE_DEVICE_TYPE(CD2801,   cd2801_device)
DECLARE_DEVICE_TYPE(CD2802,   cd2802_device)
DECLARE_DEVICE_TYPE(TMS5110A, tms5110a_device)
DECLARE_DEVICE_TYPE(M58817,   m58817_device)
>>>>>>> upstream/master



/* PROM controlled TMS5110 interface */

class tmsprom_device : public device_t
{
public:
<<<<<<< HEAD
	tmsprom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	static void set_region(device_t &device, const char *region) { downcast<tmsprom_device &>(device).m_prom_region = region; }
	static void set_rom_size(device_t &device, UINT32 rom_size) { downcast<tmsprom_device &>(device).m_rom_size = rom_size; }
	static void set_pdc_bit(device_t &device, UINT8 pdc_bit) { downcast<tmsprom_device &>(device).m_pdc_bit = pdc_bit; }
	static void set_ctl1_bit(device_t &device, UINT8 ctl1_bit) { downcast<tmsprom_device &>(device).m_ctl1_bit = ctl1_bit; }
	static void set_ctl2_bit(device_t &device, UINT8 ctl2_bit) { downcast<tmsprom_device &>(device).m_ctl2_bit = ctl2_bit; }
	static void set_ctl4_bit(device_t &device, UINT8 ctl4_bit) { downcast<tmsprom_device &>(device).m_ctl4_bit = ctl4_bit; }
	static void set_ctl8_bit(device_t &device, UINT8 ctl8_bit) { downcast<tmsprom_device &>(device).m_ctl8_bit = ctl8_bit; }
	static void set_reset_bit(device_t &device, UINT8 reset_bit) { downcast<tmsprom_device &>(device).m_reset_bit = reset_bit; }
	static void set_stop_bit(device_t &device, UINT8 stop_bit) { downcast<tmsprom_device &>(device).m_stop_bit = stop_bit; }
=======
	tmsprom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	static void set_region(device_t &device, const char *region) { downcast<tmsprom_device &>(device).m_prom.set_tag(region); }
	static void set_rom_size(device_t &device, uint32_t rom_size) { downcast<tmsprom_device &>(device).m_rom_size = rom_size; }
	static void set_pdc_bit(device_t &device, uint8_t pdc_bit) { downcast<tmsprom_device &>(device).m_pdc_bit = pdc_bit; }
	static void set_ctl1_bit(device_t &device, uint8_t ctl1_bit) { downcast<tmsprom_device &>(device).m_ctl1_bit = ctl1_bit; }
	static void set_ctl2_bit(device_t &device, uint8_t ctl2_bit) { downcast<tmsprom_device &>(device).m_ctl2_bit = ctl2_bit; }
	static void set_ctl4_bit(device_t &device, uint8_t ctl4_bit) { downcast<tmsprom_device &>(device).m_ctl4_bit = ctl4_bit; }
	static void set_ctl8_bit(device_t &device, uint8_t ctl8_bit) { downcast<tmsprom_device &>(device).m_ctl8_bit = ctl8_bit; }
	static void set_reset_bit(device_t &device, uint8_t reset_bit) { downcast<tmsprom_device &>(device).m_reset_bit = reset_bit; }
	static void set_stop_bit(device_t &device, uint8_t stop_bit) { downcast<tmsprom_device &>(device).m_stop_bit = stop_bit; }
>>>>>>> upstream/master
	template<class _Object> static devcb_base &set_pdc_callback(device_t &device, _Object object) { return downcast<tmsprom_device &>(device).m_pdc_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_ctl_callback(device_t &device, _Object object) { return downcast<tmsprom_device &>(device).m_ctl_cb.set_callback(object); }

	DECLARE_WRITE_LINE_MEMBER( m0_w );
	DECLARE_READ_LINE_MEMBER( data_r );

	/* offset is rom # */
	DECLARE_WRITE8_MEMBER( rom_csq_w );
	DECLARE_WRITE8_MEMBER( bit_w );
	DECLARE_WRITE_LINE_MEMBER( enable_w );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	virtual void device_start() override;

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
>>>>>>> upstream/master

private:
	void register_for_save_states();
	void update_prom_cnt();

	// internal state
	/* Rom interface */
<<<<<<< HEAD
	UINT32 m_address;
	/* ctl lines */
	UINT8  m_m0;
	UINT8  m_enable;
	UINT32  m_base_address;
	UINT8  m_bit;

	int m_prom_cnt;

	const char *m_prom_region;        /* prom memory region - sound region is automatically assigned */
	UINT32 m_rom_size;                /* individual rom_size */
	UINT8 m_pdc_bit;                  /* bit # of pdc line */
	/* virtual bit 8: constant 0, virtual bit 9:constant 1 */
	UINT8 m_ctl1_bit;                 /* bit # of ctl1 line */
	UINT8 m_ctl2_bit;                 /* bit # of ctl2 line */
	UINT8 m_ctl4_bit;                 /* bit # of ctl4 line */
	UINT8 m_ctl8_bit;                 /* bit # of ctl8 line */
	UINT8 m_reset_bit;                /* bit # of rom reset */
	UINT8 m_stop_bit;                 /* bit # of stop */
=======
	uint32_t m_address;
	/* ctl lines */
	uint8_t  m_m0;
	uint8_t  m_enable;
	uint32_t  m_base_address;
	uint8_t  m_bit;

	int m_prom_cnt;

	required_region_ptr<uint8_t> m_rom;
	required_region_ptr<uint8_t> m_prom;
	uint32_t m_rom_size;                /* individual rom_size */
	uint8_t m_pdc_bit;                  /* bit # of pdc line */
	/* virtual bit 8: constant 0, virtual bit 9:constant 1 */
	uint8_t m_ctl1_bit;                 /* bit # of ctl1 line */
	uint8_t m_ctl2_bit;                 /* bit # of ctl2 line */
	uint8_t m_ctl4_bit;                 /* bit # of ctl4 line */
	uint8_t m_ctl8_bit;                 /* bit # of ctl8 line */
	uint8_t m_reset_bit;                /* bit # of rom reset */
	uint8_t m_stop_bit;                 /* bit # of stop */
>>>>>>> upstream/master
	devcb_write_line m_pdc_cb;      /* tms pdc func */
	devcb_write8 m_ctl_cb;          /* tms ctl func */

	emu_timer *m_romclk_timer;
<<<<<<< HEAD
	const UINT8 *m_rom;
	const UINT8 *m_prom;
};

extern const device_type TMSPROM;

#define MCFG_TMSPROM_REGION(_region) \
	tmsprom_device::set_region(*device, _region);
=======
};

DECLARE_DEVICE_TYPE(TMSPROM, tmsprom_device)

#define MCFG_TMSPROM_REGION(_region) \
	tmsprom_device::set_region(*device, "^" _region);
>>>>>>> upstream/master

#define MCFG_TMSPROM_ROM_SIZE(_size) \
	tmsprom_device::set_rom_size(*device, _size);

#define MCFG_TMSPROM_PDC_BIT(_bit) \
	tmsprom_device::set_pdc_bit(*device, _bit);

#define MCFG_TMSPROM_CTL1_BIT(_bit) \
	tmsprom_device::set_ctl1_bit(*device, _bit);

#define MCFG_TMSPROM_CTL2_BIT(_bit) \
	tmsprom_device::set_ctl2_bit(*device, _bit);

#define MCFG_TMSPROM_CTL4_BIT(_bit) \
	tmsprom_device::set_ctl4_bit(*device, _bit);

#define MCFG_TMSPROM_CTL8_BIT(_bit) \
	tmsprom_device::set_ctl8_bit(*device, _bit);

#define MCFG_TMSPROM_RESET_BIT(_bit) \
	tmsprom_device::set_reset_bit(*device, _bit);

#define MCFG_TMSPROM_STOP_BIT(_bit) \
	tmsprom_device::set_stop_bit(*device, _bit);

#define MCFG_TMSPROM_PDC_CB(_devcb) \
	devcb = &tmsprom_device::set_pdc_callback(*device, DEVCB_##_devcb);

#define MCFG_TMSPROM_CTL_CB(_devcb) \
	devcb = &tmsprom_device::set_ctl_callback(*device, DEVCB_##_devcb);

<<<<<<< HEAD
#endif /* __TMS5110_H__ */
=======
#endif // MAME_SOUND_TMS5110_H
>>>>>>> upstream/master
