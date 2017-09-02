// license:BSD-3-Clause
// copyright-holders:Tatsuyuki Satoh
<<<<<<< HEAD
#pragma once

#ifndef __VLM5030_H__
#define __VLM5030_H__

	class vlm5030_device : public device_t,
									public device_sound_interface
	{
	public:
	vlm5030_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~vlm5030_device() {}

	/* set speech rom address */
	void set_rom(void *speech_rom);
=======
#ifndef MAME_SOUND_VLM5030_H
#define MAME_SOUND_VLM5030_H

#pragma once

class vlm5030_device : public device_t, public device_sound_interface, public device_rom_interface
{
public:
	vlm5030_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	/* get BSY pin level */
	DECLARE_READ_LINE_MEMBER( bsy );

	/* latch contoll data */
	DECLARE_WRITE8_MEMBER( data_w );

	/* set RST pin level : reset / set table address A8-A15 */
	DECLARE_WRITE_LINE_MEMBER( rst );

	/* set VCU pin level : ?? unknown */
	DECLARE_WRITE_LINE_MEMBER( vcu );

	/* set ST pin level  : set table address A0-A7 / start speech */
	DECLARE_WRITE_LINE_MEMBER( st );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

private:
	// internal state
	sound_stream * m_channel;
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

	// device_rom_interface overrides
	virtual void rom_bank_updated() override;

private:
	// configuration state
	const address_space_config m_space_config;

	// internal state
	sound_stream *m_channel;
>>>>>>> upstream/master

	/* coefficient tables */
	const struct tms5100_coeffs *m_coeff;

	/* need to save state */

<<<<<<< HEAD
	UINT8 *m_rom;
	int m_address_mask;
	UINT16 m_address;
	UINT8 m_pin_BSY;
	UINT8 m_pin_ST;
	UINT8 m_pin_VCU;
	UINT8 m_pin_RST;
	UINT8 m_latch_data;
	UINT16 m_vcu_addr_h;
	UINT8 m_parameter;
	UINT8 m_phase;

	/* state of option paramter */
	int m_frame_size;
	int m_pitch_offset;
	UINT8 m_interp_step;

	UINT8 m_interp_count;       /* number of interp periods    */
	UINT8 m_sample_count;       /* sample number within interp */
	UINT8 m_pitch_count;

	/* these contain data describing the current and previous voice frames */
	UINT16 m_old_energy;
	UINT8 m_old_pitch;
	INT16  m_old_k[10];
	UINT16 m_target_energy;
	UINT8 m_target_pitch;
	INT16 m_target_k[10];

	UINT16 m_new_energy;
	UINT8 m_new_pitch;
	INT16 m_new_k[10];
=======
	uint16_t m_address;
	uint8_t m_pin_BSY;
	uint8_t m_pin_ST;
	uint8_t m_pin_VCU;
	uint8_t m_pin_RST;
	uint8_t m_latch_data;
	uint16_t m_vcu_addr_h;
	uint8_t m_parameter;
	uint8_t m_phase;

	/* state of option parameter */
	int m_frame_size;
	int m_pitch_offset;
	uint8_t m_interp_step;

	uint8_t m_interp_count;       /* number of interp periods    */
	uint8_t m_sample_count;       /* sample number within interp */
	uint8_t m_pitch_count;

	/* these contain data describing the current and previous voice frames */
	uint16_t m_old_energy;
	uint8_t m_old_pitch;
	int16_t  m_old_k[10];
	uint16_t m_target_energy;
	uint8_t m_target_pitch;
	int16_t m_target_k[10];

	uint16_t m_new_energy;
	uint8_t m_new_pitch;
	int16_t m_new_k[10];
>>>>>>> upstream/master

	/* these are all used to contain the current state of the sound generation */
	unsigned int m_current_energy;
	unsigned int m_current_pitch;
	int m_current_k[10];

<<<<<<< HEAD
	INT32 m_x[10];
=======
	int32_t m_x[10];
>>>>>>> upstream/master

	int get_bits(int sbit,int bits);
	int parse_frame();
	void update();
<<<<<<< HEAD
	void setup_parameter(UINT8 param);
	void restore_state();
};

extern const device_type VLM5030;


#endif /* __VLM5030_H__ */
=======
	void setup_parameter(uint8_t param);
	void restore_state();
};

DECLARE_DEVICE_TYPE(VLM5030, vlm5030_device)

#endif // MAME_SOUND_VLM5030_H
>>>>>>> upstream/master
