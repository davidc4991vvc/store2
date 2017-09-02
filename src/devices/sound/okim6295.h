// license:BSD-3-Clause
// copyright-holders:Mirko Buffoni,Aaron Giles
/***************************************************************************

    okim6295.h

    OKIM 6295 ADCPM sound chip.

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __OKIM6295_H__
#define __OKIM6295_H__
=======
#ifndef MAME_SOUND_OKIM6295_H
#define MAME_SOUND_OKIM6295_H

#pragma once
>>>>>>> upstream/master

#include "sound/okiadpcm.h"



//**************************************************************************
<<<<<<< HEAD
//  CONSTANTS
//**************************************************************************

enum
{
	OKIM6295_PIN7_LOW = 0,
	OKIM6295_PIN7_HIGH = 1
};



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_OKIM6295_ADD(_tag, _clock, _pin7) \
	MCFG_DEVICE_ADD(_tag, OKIM6295, _clock) \
	MCFG_OKIM6295_PIN7(_pin7)

#define MCFG_OKIM6295_REPLACE(_tag, _clock, _pin7) \
	MCFG_DEVICE_REPLACE(_tag, OKIM6295, _clock) \
	MCFG_OKIM6295_PIN7(_pin7)

#define MCFG_OKIM6295_PIN7(_pin7) \
	okim6295_device::static_set_pin7(*device, _pin7);
=======
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_OKIM6295_ADD(tag, clock, pin7) \
		MCFG_DEVICE_ADD((tag), OKIM6295, (clock)) \
		MCFG_OKIM6295_PIN7(pin7)

#define MCFG_OKIM6295_REPLACE(tag, clock, pin7) \
		MCFG_DEVICE_REPLACE((tag), OKIM6295, (clock)) \
		MCFG_OKIM6295_PIN7(pin7)

#define MCFG_OKIM6295_PIN7(pin7) \
		okim6295_device::static_set_pin7(*device, (okim6295_device::pin7));
>>>>>>> upstream/master


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************


// ======================> okim6295_device

class okim6295_device : public device_t,
						public device_sound_interface,
<<<<<<< HEAD
						public device_memory_interface
{
public:
	// construction/destruction
	okim6295_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
						public device_rom_interface
{
public:
	enum
	{
		PIN7_LOW = 0,
		PIN7_HIGH = 1
	};

	// construction/destruction
	okim6295_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// inline configuration helpers
	static void static_set_pin7(device_t &device, int pin7);

	// runtime configuration
<<<<<<< HEAD
	void set_bank_base(offs_t base, bool bDontUpdateStream = false);
	void set_pin7(int pin7);

	UINT8 read_status();
	void write_command(UINT8 command);
=======
	void set_pin7(int pin7);

	uint8_t read_status();
	void write_command(uint8_t command);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE8_MEMBER( write );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual void device_post_load();
	virtual void device_clock_changed();

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;

	// device_sound_interface overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_post_load() override;
	virtual void device_clock_changed() override;

	// device_sound_interface overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

	// device_rom_interface overrides
	virtual void rom_bank_updated() override;
>>>>>>> upstream/master

	// a single voice
	class okim_voice
	{
	public:
		okim_voice();
<<<<<<< HEAD
		void generate_adpcm(direct_read_data &direct, stream_sample_t *buffer, int samples);
=======
		void generate_adpcm(device_rom_interface &rom, stream_sample_t *buffer, int samples);
>>>>>>> upstream/master

		oki_adpcm_state m_adpcm;        // current ADPCM state
		bool            m_playing;
		offs_t          m_base_offset;  // pointer to the base memory location
<<<<<<< HEAD
		UINT32          m_sample;       // current sample number
		UINT32          m_count;        // total samples to play
		INT8            m_volume;       // output volume
	};

	// configuration state
	const address_space_config  m_space_config;

	// internal state
	static const int OKIM6295_VOICES = 4;

	okim_voice          m_voice[OKIM6295_VOICES];
	INT32               m_command;
	bool                m_bank_installed;
	offs_t              m_bank_offs;
	sound_stream *      m_stream;
	UINT8               m_pin7_state;
	direct_read_data *  m_direct;

	static const UINT8 s_volume_table[16];
=======
		uint32_t          m_sample;       // current sample number
		uint32_t          m_count;        // total samples to play
		int8_t            m_volume;       // output volume
	};

	// configuration state
	optional_memory_region  m_region;

	// internal state
	static constexpr int OKIM6295_VOICES = 4;

	okim_voice          m_voice[OKIM6295_VOICES];
	int32_t               m_command;
	sound_stream *      m_stream;
	uint8_t               m_pin7_state;

	static const uint8_t s_volume_table[16];
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type OKIM6295;


#endif /* __OKIM6295_H__ */
=======
DECLARE_DEVICE_TYPE(OKIM6295, okim6295_device)


#endif // MAME_SOUND_OKIM6295_H
>>>>>>> upstream/master
