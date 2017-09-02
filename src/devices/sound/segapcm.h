// license:BSD-3-Clause
// copyright-holders:Hiromitsu Shioya, Olivier Galibert
/*********************************************************/
/*    SEGA 8bit PCM                                      */
/*********************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SEGAPCM_H__
#define __SEGAPCM_H__

#define   BANK_256    (11)
#define   BANK_512    (12)
#define   BANK_12M    (13)
#define   BANK_MASK7  (0x70<<16)
#define   BANK_MASKF  (0xf0<<16)
#define   BANK_MASKF8 (0xf8<<16)
=======
#ifndef MAMESOUND_SEGAPCM_H
#define MAMESOUND_SEGAPCM_H

#pragma once
>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

<<<<<<< HEAD
#define MCFG_SEGAPCM_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, SEGAPCM, _clock)
#define MCFG_SEGAPCM_REPLACE(_tag, _clock) \
	MCFG_DEVICE_REPLACE(_tag, SEGAPCM, _clock)

#define MCFG_SEGAPCM_BANK(_bank) \
	segapcm_device::set_bank(*device, _bank);
=======
#define MCFG_SEGAPCM_ADD(tag, clock) \
		MCFG_DEVICE_ADD((tag), SEGAPCM, (clock))

#define MCFG_SEGAPCM_REPLACE(tag, clock) \
		MCFG_DEVICE_REPLACE((tag), SEGAPCM, (clock))

#define MCFG_SEGAPCM_BANK(bank) \
		segapcm_device::set_bank(*device, (segapcm_device::bank));

#define MCFG_SEGAPCM_BANK_MASK(bank, mask) \
		segapcm_device::set_bank(*device, (segapcm_device::bank) | (segapcm_device::mask));
>>>>>>> upstream/master


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class segapcm_device : public device_t,
<<<<<<< HEAD
						public device_sound_interface
{
public:
	segapcm_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~segapcm_device() { }
=======
					   public device_sound_interface,
					   public device_rom_interface
{
public:
	static constexpr int BANK_256    = 11;
	static constexpr int BANK_512    = 12;
	static constexpr int BANK_12M    = 13;
	static constexpr int BANK_MASK7  = 0x70 << 16;
	static constexpr int BANK_MASKF  = 0xf0 << 16;
	static constexpr int BANK_MASKF8 = 0xf8 << 16;

	segapcm_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// static configuration
	static void set_bank(device_t &device, int bank) { downcast<segapcm_device &>(device).m_bank = bank; }

	DECLARE_WRITE8_MEMBER( sega_pcm_w );
	DECLARE_READ8_MEMBER( sega_pcm_r );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

private:
	required_region_ptr<UINT8> m_rom;
	UINT8* m_ram;
	UINT8 m_low[16];
=======
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

	// device_rom_interface overrides
	virtual void rom_bank_updated() override;

private:
	std::unique_ptr<uint8_t[]> m_ram;
	uint8_t m_low[16];
>>>>>>> upstream/master
	int m_bank;
	int m_bankshift;
	int m_bankmask;
	sound_stream* m_stream;
};

<<<<<<< HEAD
extern const device_type SEGAPCM;


#endif /* __SEGAPCM_H__ */
=======
DECLARE_DEVICE_TYPE(SEGAPCM, segapcm_device)

#endif // MAMESOUND_SEGAPCM_H
>>>>>>> upstream/master
