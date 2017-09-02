// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    Gottlieb hardware

***************************************************************************/

<<<<<<< HEAD
#include "emu.h"
#include "cpu/m6502/m6502.h"
#include "machine/mos6530.h"
#include "machine/6532riot.h"
#include "sound/dac.h"
=======
#include "cpu/m6502/m6502.h"
#include "machine/mos6530.h"
#include "machine/6532riot.h"
>>>>>>> upstream/master
#include "sound/ay8910.h"
#include "sound/sp0250.h"
#include "sound/votrax.h"


<<<<<<< HEAD
// set to 0 to enable Votrax device and disable samples
#define USE_FAKE_VOTRAX         (1)



=======
>>>>>>> upstream/master
//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
extern const device_type GOTTLIEB_SOUND_REV0;
extern const device_type GOTTLIEB_SOUND_REV1;
extern const device_type GOTTLIEB_SOUND_REV1_WITH_VOTRAX;
extern const device_type GOTTLIEB_SOUND_REV2;
=======
DECLARE_DEVICE_TYPE(GOTTLIEB_SOUND_REV0,        gottlieb_sound_r0_device)
DECLARE_DEVICE_TYPE(GOTTLIEB_SOUND_REV1,        gottlieb_sound_r1_device)
DECLARE_DEVICE_TYPE(GOTTLIEB_SOUND_REV1_VOTRAX, gottlieb_sound_r1_with_votrax_device)
DECLARE_DEVICE_TYPE(GOTTLIEB_SOUND_REV2,        gottlieb_sound_r2_device)
>>>>>>> upstream/master



//**************************************************************************
//  DEVICE CONFIGURATION MACROS
//**************************************************************************

<<<<<<< HEAD
#define MCFG_GOTTLIEB_SOUND_R0_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, GOTTLIEB_SOUND_REV0, 0)

#define MCFG_GOTTLIEB_SOUND_R1_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, GOTTLIEB_SOUND_REV1, 0)
#define MCFG_GOTTLIEB_SOUND_R1_ADD_VOTRAX(_tag) \
	MCFG_DEVICE_ADD(_tag, GOTTLIEB_SOUND_REV1_WITH_VOTRAX, 0)

#define MCFG_GOTTLIEB_SOUND_R2_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, GOTTLIEB_SOUND_REV2, 0)
#define MCFG_GOTTLIEB_SOUND_R2_ADD_COBRAM3(_tag) \
	MCFG_DEVICE_ADD(_tag, GOTTLIEB_SOUND_REV2, 0) \
=======
#define MCFG_GOTTLIEB_ENABLE_COBRAM3_MODS() \
>>>>>>> upstream/master
	gottlieb_sound_r2_device::static_enable_cobram3_mods(*device);


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> gottlieb_sound_r0_device

// rev 0 sound board
class gottlieb_sound_r0_device : public device_t, public device_mixer_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	gottlieb_sound_r0_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	gottlieb_sound_r0_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// read/write
	DECLARE_WRITE8_MEMBER( write );

	// internal communications
<<<<<<< HEAD
	DECLARE_READ8_MEMBER( r6530b_r );
=======
>>>>>>> upstream/master
	DECLARE_INPUT_CHANGED_MEMBER(audio_nmi);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;
	virtual void device_start();
=======
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;
	virtual void device_start() override;
>>>>>>> upstream/master

private:
	// devices
	required_device<m6502_device>       m_audiocpu;
	required_device<mos6530_device>     m_r6530;
<<<<<<< HEAD
	required_device<dac_device>         m_dac;

	UINT8 m_sndcmd;
=======

	uint8_t m_sndcmd;

	DECLARE_READ8_MEMBER( r6530b_r );
>>>>>>> upstream/master
};

// ======================> gottlieb_sound_r1_device

// rev 1 sound board, with unpopulated VOTRAX
class gottlieb_sound_r1_device : public device_t, public device_mixer_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	gottlieb_sound_r1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	gottlieb_sound_r1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock, bool populate_votrax);
=======
	gottlieb_sound_r1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// read/write
	DECLARE_WRITE8_MEMBER( write );

	// internal communications
<<<<<<< HEAD
	DECLARE_WRITE_LINE_MEMBER( snd_interrupt );
	DECLARE_WRITE8_MEMBER( r6532_portb_w );
=======
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER( votrax_data_w );
	DECLARE_WRITE8_MEMBER( speech_clock_dac_w );
	DECLARE_WRITE_LINE_MEMBER( votrax_request );

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;
	virtual void device_start();
=======
	gottlieb_sound_r1_device(
			const machine_config &mconfig,
			device_type type,
			const char *tag,
			device_t *owner,
			uint32_t clock);

	// device-level overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;
	virtual void device_start() override;
>>>>>>> upstream/master

private:
	// devices
	required_device<m6502_device>       m_audiocpu;
	required_device<riot6532_device>    m_riot;
<<<<<<< HEAD
	required_device<dac_device>         m_dac;
=======
>>>>>>> upstream/master
	optional_device<votrax_sc01_device> m_votrax;

	// internal state
	//bool            m_populate_votrax;
<<<<<<< HEAD
	UINT8           m_last_speech_clock;

#if USE_FAKE_VOTRAX
protected:
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
private:
	void fake_votrax_data_w(UINT8 data);
	void trigger_sample(UINT8 data);
	optional_device<samples_device> m_samples;
	UINT8 m_score_sample;
	UINT8 m_random_offset;
	UINT8 m_votrax_queue[100];
	UINT8 m_votrax_queuepos;
#endif
=======
	uint8_t           m_last_speech_clock;

	DECLARE_WRITE_LINE_MEMBER( snd_interrupt );
	DECLARE_WRITE8_MEMBER( r6532_portb_w );
>>>>>>> upstream/master
};

// fully populated rev 1 sound board
class gottlieb_sound_r1_with_votrax_device : public gottlieb_sound_r1_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	gottlieb_sound_r1_with_votrax_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;
=======
	gottlieb_sound_r1_with_votrax_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;
>>>>>>> upstream/master
};


// ======================> gottlieb_sound_r2_device

// fully populated rev 2 sound board
class gottlieb_sound_r2_device : public device_t, public device_mixer_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	gottlieb_sound_r2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	gottlieb_sound_r2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// static configuration helpers
	static void static_enable_cobram3_mods(device_t &device);

	// read/write
	DECLARE_WRITE8_MEMBER( write );

	// internal communications
	DECLARE_READ8_MEMBER( speech_data_r );
	DECLARE_READ8_MEMBER( audio_data_r );
	DECLARE_WRITE8_MEMBER( signal_audio_nmi_w );
	DECLARE_WRITE8_MEMBER( nmi_rate_w );
	CUSTOM_INPUT_MEMBER( speech_drq_custom_r );
<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER( dac_w );
=======
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER( speech_control_w );
	DECLARE_WRITE8_MEMBER( sp0250_latch_w );
	DECLARE_WRITE8_MEMBER( psg_latch_w );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
>>>>>>> upstream/master

private:
	// internal helpers
	void nmi_timer_adjust();
	void nmi_state_update();

	// timer IDs
	enum
	{
		TID_NMI_GENERATE,
		TID_NMI_CLEAR,
		TID_SOUND_LATCH_WRITE
	};

	// devices
	required_device<m6502_device>   m_audiocpu;
	required_device<m6502_device>   m_speechcpu;
<<<<<<< HEAD
	required_device<dac_device>     m_dac;
=======
>>>>>>> upstream/master
	required_device<ay8913_device>  m_ay1;
	required_device<ay8913_device>  m_ay2;
	optional_device<sp0250_device>  m_sp0250;

	// internal state
	bool        m_cobram3_mod;
	emu_timer * m_nmi_timer;
<<<<<<< HEAD
	UINT8       m_nmi_rate;
	UINT8       m_nmi_state;
	UINT8       m_audiocpu_latch;
	UINT8       m_speechcpu_latch;
	UINT8       m_speech_control;
	UINT8       m_last_command;
	UINT8       m_dac_data[2];
	UINT8       m_psg_latch;
	UINT8       m_psg_data_latch;
	UINT8       m_sp0250_latch;
};


/*----------- defined in audio/gottlieb.c -----------*/

#if USE_FAKE_VOTRAX
MACHINE_CONFIG_EXTERN( reactor_samples );
MACHINE_CONFIG_EXTERN( qbert_samples );
#endif
=======
	uint8_t       m_nmi_rate;
	uint8_t       m_nmi_state;
	uint8_t       m_audiocpu_latch;
	uint8_t       m_speechcpu_latch;
	uint8_t       m_speech_control;
	uint8_t       m_last_command;
	uint8_t       m_psg_latch;
	uint8_t       m_psg_data_latch;
	uint8_t       m_sp0250_latch;
};

>>>>>>> upstream/master
