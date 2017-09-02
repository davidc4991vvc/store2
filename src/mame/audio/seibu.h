// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    Seibu Sound System v1.02, games using this include:

    Cross Shooter    1987   * "START UP PROGRAM V1.02 (C)1986 SEIBU KAIHATSU INC." (YM2151 substituted for YM3812)
    Cabal            1988   * "Michel/Seibu    sound 11/04/88" (YM2151 substituted for YM3812, unknown ADPCM)
    Dead Angle       1988   * "START UP PROGRAM V1.02 (C)1986 SEIBU KAIHATSU INC." (2xYM2203 substituted for YM3812, unknown ADPCM)
    Dynamite Duke    1989   * "START UP PROGRAM V1.02 (C)1986 SEIBU KAIHATSU INC."
    Toki             1989   * "START UP PROGRAM V1.02 (C)1986 SEIBU KAIHATSU INC."
    Raiden           1990   * "START UP PROGRAM V1.02 (C)1986 SEIBU KAIHATSU INC."
    Blood Brothers   1990     "START UP PROGRAM V1.02 (C)1986 SEIBU KAIHATSU INC."
    D-Con            1992     "START UP PROGRAM V1.02 (C)1986 SEIBU KAIHATSU INC."

    Related sound programs (not implemented yet):

    Zero Team                 "START UP PROGRAM V1.02 (C)1986 SEIBU KAIHATSU INC."
<<<<<<< HEAD
    Legionaire                "START UP PROGRAM V1.02 (C)1986 SEIBU KAIHATSU INC." (YM2151 substituted for YM3812)
=======
    Legionnaire               "START UP PROGRAM V1.02 (C)1986 SEIBU KAIHATSU INC." (YM2151 substituted for YM3812)
>>>>>>> upstream/master
    Raiden 2                  "START UP PROGRAM V1.02 (C)1986 SEIBU KAIHATSU INC." (YM2151 substituted for YM3812, plus extra MSM6205)
    Raiden DX                 "START UP PROGRAM V1.02 (C)1986 SEIBU KAIHATSU INC." (YM2151 substituted for YM3812, plus extra MSM6205)
    Cup Soccer                "START UP PROGRAM V1.02 (C)1986 SEIBU KAIHATSU INC." (YM2151 substituted for YM3812, plus extra MSM6205)
    SD Gundam Psycho Salamander "Copyright by King Bee Sol 1991"
    * = encrypted

***************************************************************************/
<<<<<<< HEAD

#include "cpu/z80/z80.h"
#include "sound/3812intf.h"
#include "sound/2151intf.h"
#include "sound/2203intf.h"
#include "sound/okim6295.h"

ADDRESS_MAP_EXTERN(seibu_sound_decrypted_opcodes_map, 8);
ADDRESS_MAP_EXTERN(seibu_sound_map, 8);
ADDRESS_MAP_EXTERN(seibu2_sound_map, 8);
ADDRESS_MAP_EXTERN(seibu2_airraid_sound_map, 8);
ADDRESS_MAP_EXTERN(seibu2_raiden2_sound_map, 8);
ADDRESS_MAP_EXTERN(seibu_newzeroteam_sound_map, 8);
ADDRESS_MAP_EXTERN(seibu3_sound_map, 8);
ADDRESS_MAP_EXTERN(seibu3_adpcm_sound_map, 8);
=======
#ifndef MAME_AUDIO_SEIBU_H
#define MAME_AUDIO_SEIBU_H

#pragma once

#include "cpu/z80/z80.h"
#include "sound/okiadpcm.h"

ADDRESS_MAP_EXTERN(seibu_sound_map, 8);
>>>>>>> upstream/master

class seibu_sound_device : public device_t
{
public:
<<<<<<< HEAD
	seibu_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~seibu_sound_device() {}

	DECLARE_READ16_MEMBER( main_word_r );
	DECLARE_WRITE16_MEMBER( main_word_w );
=======
	seibu_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	~seibu_sound_device() {}

	// static configuration
	static void static_set_cpu_tag(device_t &device, const char *tag);
	static void static_set_rombank_tag(device_t &device, const char *tag);
	template<class _Object> static devcb_base &set_ym_read_callback(device_t &device, _Object object)  { return downcast<seibu_sound_device &>(device).m_ym_read_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_ym_write_callback(device_t &device, _Object object) { return downcast<seibu_sound_device &>(device).m_ym_write_cb.set_callback(object); }

	DECLARE_READ8_MEMBER( main_r );
	DECLARE_WRITE8_MEMBER( main_w );
>>>>>>> upstream/master
	DECLARE_WRITE16_MEMBER( main_mustb_w );
	DECLARE_WRITE8_MEMBER( irq_clear_w );
	DECLARE_WRITE8_MEMBER( rst10_ack_w );
	DECLARE_WRITE8_MEMBER( rst18_ack_w );
<<<<<<< HEAD
=======
	DECLARE_READ8_MEMBER( ym_r );
	DECLARE_WRITE8_MEMBER( ym_w );
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER( bank_w );
	DECLARE_WRITE8_MEMBER( coin_w );
	WRITE_LINE_MEMBER( fm_irqhandler );
	DECLARE_READ8_MEMBER( soundlatch_r );
	DECLARE_READ8_MEMBER( main_data_pending_r );
	DECLARE_WRITE8_MEMBER( main_data_w );
	DECLARE_WRITE8_MEMBER( pending_w );

<<<<<<< HEAD
	static void apply_decrypt(UINT8 *rom, UINT8 *opcodes, int length);
	void set_encryption(int mode);
	UINT8 *get_custom_decrypt();
=======
>>>>>>> upstream/master
	void update_irq_lines(int param);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	private:
	int m_encryption_mode;
	UINT8 *m_decrypted_opcodes;

	// internal state
	device_t *m_sound_cpu;
	UINT8 m_main2sub[2];
	UINT8 m_sub2main[2];
	int m_main2sub_pending;
	int m_sub2main_pending;
	UINT8 m_rst10_irq;
	UINT8 m_rst18_irq;
=======
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	// device callbacks
	devcb_read8 m_ym_read_cb;
	devcb_write8 m_ym_write_cb;

	// internal state
	required_device<cpu_device> m_sound_cpu;
	optional_region_ptr<uint8_t> m_sound_rom;
	optional_memory_bank m_rom_bank;
	uint8_t m_main2sub[2];
	uint8_t m_sub2main[2];
	int m_main2sub_pending;
	int m_sub2main_pending;
	uint8_t m_rst10_irq;
	uint8_t m_rst18_irq;
>>>>>>> upstream/master

	enum
	{
		VECTOR_INIT,
		RST10_ASSERT,
		RST10_CLEAR,
		RST18_ASSERT,
		RST18_CLEAR
	};
};

<<<<<<< HEAD
extern const device_type SEIBU_SOUND;

=======
DECLARE_DEVICE_TYPE(SEIBU_SOUND, seibu_sound_device)


// SEI80BU (Z80 program decryption)

class sei80bu_device : public device_t, public device_rom_interface
{
public:
	sei80bu_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ8_MEMBER(data_r);
	DECLARE_READ8_MEMBER(opcode_r);

protected:
	// device-level overrides
	virtual void device_start() override { }
	virtual void rom_bank_updated() override { }
};

DECLARE_DEVICE_TYPE(SEI80BU, sei80bu_device)
>>>>>>> upstream/master

// Seibu ADPCM device

class seibu_adpcm_device : public device_t,
									public device_sound_interface
{
public:
<<<<<<< HEAD
	seibu_adpcm_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~seibu_adpcm_device() {}

	static void set_adpcm_rom_tag(device_t &device, const char *tag) { downcast<seibu_adpcm_device &>(device).m_rom_tag = tag; }

	void decrypt(const char *region);
=======
	seibu_adpcm_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	~seibu_adpcm_device() {}

	void decrypt();
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER( adr_w );
	DECLARE_WRITE8_MEMBER( ctl_w );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

	private:
	// internal state
	oki_adpcm_state m_adpcm;
	sound_stream *m_stream;
	UINT32 m_current;
	UINT32 m_end;
	UINT8 m_nibble;
	UINT8 m_playing;
	const char *m_rom_tag;
	UINT8 *m_base;
};

extern const device_type SEIBU_ADPCM;

/**************************************************************************/

#define MCFG_SEIBU_ADPCM_ROMREGION(_tag) \
	seibu_adpcm_device::set_adpcm_rom_tag(*device, _tag);

=======
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

private:
	// internal state
	oki_adpcm_state m_adpcm;
	sound_stream *m_stream;
	uint32_t m_current;
	uint32_t m_end;
	uint8_t m_nibble;
	uint8_t m_playing;
	required_region_ptr<uint8_t> m_base;
};

DECLARE_DEVICE_TYPE(SEIBU_ADPCM, seibu_adpcm_device)

/**************************************************************************/

>>>>>>> upstream/master
#define SEIBU_COIN_INPUTS                                           \
	PORT_START("COIN")                                              \
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_COIN1 ) PORT_IMPULSE(4)     \
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_COIN2 ) PORT_IMPULSE(4)     \
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_UNUSED )                    \
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_UNUSED )                    \
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_UNUSED )                    \
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_UNUSED )                    \
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_UNUSED )                    \
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_UNUSED )

#define SEIBU_COIN_INPUTS_INVERT                                    \
	PORT_START("COIN")                                              \
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN1 ) PORT_IMPULSE(4)      \
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_COIN2 ) PORT_IMPULSE(4)      \
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_UNUSED )                     \
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNUSED )                     \
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNUSED )                     \
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNUSED )                     \
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNUSED )                     \
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNUSED )

<<<<<<< HEAD

#define SEIBU_SOUND_SYSTEM_CPU(freq)                                \
	MCFG_CPU_ADD("audiocpu", Z80, freq)                             \
	MCFG_CPU_PROGRAM_MAP(seibu_sound_map)                           \
	MCFG_DEVICE_ADD("seibu_sound", SEIBU_SOUND, 0)

#define SEIBU2_SOUND_SYSTEM_CPU(freq)                               \
	MCFG_CPU_ADD("audiocpu", Z80, freq)                             \
	MCFG_CPU_PROGRAM_MAP(seibu2_sound_map)                          \
	MCFG_DEVICE_ADD("seibu_sound", SEIBU_SOUND, 0)

#define SEIBU2_AIRRAID_SOUND_SYSTEM_CPU(freq)                       \
	MCFG_CPU_ADD("audiocpu", Z80, freq)                             \
	MCFG_CPU_PROGRAM_MAP(seibu2_airraid_sound_map)                  \
	MCFG_DEVICE_ADD("seibu_sound", SEIBU_SOUND, 0)

#define SEIBU2_RAIDEN2_SOUND_SYSTEM_CPU(freq)                       \
	MCFG_CPU_ADD("audiocpu",  Z80, freq)                            \
	MCFG_CPU_PROGRAM_MAP(seibu2_raiden2_sound_map)                  \
	MCFG_DEVICE_ADD("seibu_sound", SEIBU_SOUND, 0)

#define SEIBU_NEWZEROTEAM_SOUND_SYSTEM_CPU(freq)                    \
	MCFG_CPU_ADD("audiocpu", Z80, freq)                             \
	MCFG_CPU_PROGRAM_MAP(seibu_newzeroteam_sound_map)               \
	MCFG_DEVICE_ADD("seibu_sound", SEIBU_SOUND, 0)

#define SEIBU3_SOUND_SYSTEM_CPU(freq)                               \
	MCFG_CPU_ADD("audiocpu", Z80, freq)                             \
	MCFG_CPU_PROGRAM_MAP(seibu3_sound_map)                          \
	MCFG_DEVICE_ADD("seibu_sound", SEIBU_SOUND, 0)

#define SEIBU3A_SOUND_SYSTEM_CPU(freq)                              \
	MCFG_CPU_ADD("audiocpu", Z80, freq)                             \
	MCFG_CPU_PROGRAM_MAP(seibu3_adpcm_sound_map)                    \
	MCFG_DEVICE_ADD("seibu_sound", SEIBU_SOUND, 0)

#define SEIBU_SOUND_SYSTEM_ENCRYPTED_LOW()                          \
	MCFG_DEVICE_MODIFY("seibu_sound")                               \
	downcast<seibu_sound_device *>(device)->set_encryption(1);      \
	MCFG_DEVICE_MODIFY("audiocpu")                                  \
	MCFG_CPU_DECRYPTED_OPCODES_MAP(seibu_sound_decrypted_opcodes_map)

#define SEIBU_SOUND_SYSTEM_ENCRYPTED_FULL()                         \
	MCFG_DEVICE_MODIFY("seibu_sound")                               \
	downcast<seibu_sound_device *>(device)->set_encryption(2);      \
	MCFG_DEVICE_MODIFY("audiocpu")                                  \
	MCFG_CPU_DECRYPTED_OPCODES_MAP(seibu_sound_decrypted_opcodes_map)

#define SEIBU_SOUND_SYSTEM_ENCRYPTED_CUSTOM()                       \
	MCFG_DEVICE_MODIFY("seibu_sound")                               \
	downcast<seibu_sound_device *>(device)->set_encryption(3);      \
	MCFG_DEVICE_MODIFY("audiocpu")                                  \
	MCFG_CPU_DECRYPTED_OPCODES_MAP(seibu_sound_decrypted_opcodes_map)

#define SEIBU_SOUND_SYSTEM_YM3812_INTERFACE(freq1,freq2)            \
	MCFG_SPEAKER_STANDARD_MONO("mono")                              \
																	\
	MCFG_SOUND_ADD("ymsnd", YM3812, freq1)                          \
	MCFG_YM3812_IRQ_HANDLER(DEVWRITELINE("seibu_sound", seibu_sound_device, fm_irqhandler)) \
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 1.0)                      \
																	\
	MCFG_OKIM6295_ADD("oki", freq2, OKIM6295_PIN7_LOW)              \
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.40)

#define SEIBU_SOUND_SYSTEM_YM3812_RAIDEN_INTERFACE(freq1,freq2)     \
	MCFG_SPEAKER_STANDARD_MONO("mono")                              \
																	\
	MCFG_SOUND_ADD("ymsnd", YM3812, freq1)                          \
	MCFG_YM3812_IRQ_HANDLER(DEVWRITELINE("seibu_sound", seibu_sound_device, fm_irqhandler)) \
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 1.0)                      \
																	\
	MCFG_OKIM6295_ADD("oki", freq2, OKIM6295_PIN7_HIGH)             \
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 1.0)

#define SEIBU_SOUND_SYSTEM_YM2151_INTERFACE(freq1,freq2)            \
	MCFG_SPEAKER_STANDARD_MONO("mono")                              \
																	\
	MCFG_YM2151_ADD("ymsnd", freq1)                                 \
	MCFG_YM2151_IRQ_HANDLER(DEVWRITELINE("seibu_sound", seibu_sound_device, fm_irqhandler)) \
	MCFG_SOUND_ROUTE(0, "mono", 0.50)                               \
	MCFG_SOUND_ROUTE(1, "mono", 0.50)                               \
																	\
	MCFG_OKIM6295_ADD("oki", freq2, OKIM6295_PIN7_LOW)              \
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.40)

#define SEIBU_AIRRAID_SOUND_SYSTEM_YM2151_INTERFACE(freq1)          \
	MCFG_SPEAKER_STANDARD_MONO("mono")                              \
																	\
	MCFG_YM2151_ADD("ymsnd", freq1)                                 \
	MCFG_YM2151_IRQ_HANDLER(DEVWRITELINE("seibu_sound", seibu_sound_device, fm_irqhandler)) \
	MCFG_SOUND_ROUTE(0, "mono", 0.50)                               \
	MCFG_SOUND_ROUTE(1, "mono", 0.50)

#define SEIBU_SOUND_SYSTEM_YM2151_RAIDEN2_INTERFACE(freq1, freq2, regiona, regionb) \
	MCFG_SPEAKER_STANDARD_MONO("mono")                              \
																	\
	MCFG_YM2151_ADD("ymsnd", freq1)                                 \
	MCFG_YM2151_IRQ_HANDLER(DEVWRITELINE("seibu_sound", seibu_sound_device, fm_irqhandler)) \
	MCFG_SOUND_ROUTE(0, "mono", 0.50)                               \
	MCFG_SOUND_ROUTE(1, "mono", 0.50)                               \
																	\
	MCFG_OKIM6295_ADD("oki1", freq2, OKIM6295_PIN7_HIGH)            \
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.40)                     \
																	\
	MCFG_OKIM6295_ADD("oki2", freq2, OKIM6295_PIN7_HIGH)            \
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.40)

#define SEIBU_SOUND_SYSTEM_YM2203_INTERFACE(freq)                   \
	MCFG_SPEAKER_STANDARD_MONO("mono")                              \
																	\
	MCFG_SOUND_ADD("ym1", YM2203, freq)                             \
	MCFG_YM2203_IRQ_HANDLER(DEVWRITELINE("seibu_sound", seibu_sound_device, fm_irqhandler)) \
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.15)                     \
																	\
	MCFG_SOUND_ADD("ym2", YM2203, freq)                             \
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.15)

#define SEIBU_SOUND_SYSTEM_ADPCM_INTERFACE                          \
	MCFG_SOUND_ADD("adpcm1", SEIBU_ADPCM, 8000)                     \
	MCFG_SEIBU_ADPCM_ROMREGION("adpcm1")                            \
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.40)                     \
																	\
	MCFG_SOUND_ADD("adpcm2", SEIBU_ADPCM, 8000)                     \
	MCFG_SEIBU_ADPCM_ROMREGION("adpcm2")                            \
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.40)

/**************************************************************************/
=======
#define MCFG_SEIBU_SOUND_CPU(_audiocputag) \
	seibu_sound_device::static_set_cpu_tag(*device, "^" _audiocputag);

#define MCFG_SEIBU_SOUND_ROMBANK(_banktag) \
	seibu_sound_device::static_set_rombank_tag(*device, "^" _banktag);

#define MCFG_SEIBU_SOUND_YM_READ_CB(_devcb) \
	devcb = &seibu_sound_device::set_ym_read_callback(*device, DEVCB_##_devcb);

#define MCFG_SEIBU_SOUND_YM_WRITE_CB(_devcb) \
	devcb = &seibu_sound_device::set_ym_write_callback(*device, DEVCB_##_devcb);

/**************************************************************************/

#endif // MAME_AUDIO_SEIBU_H
>>>>>>> upstream/master
