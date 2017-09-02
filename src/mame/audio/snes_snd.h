// license:LGPL-2.1+
// copyright-holders:R. Belmont, Brad Martin
/*****************************************************************************
 *
 * audio/snes_spc.h
 *
 ****************************************************************************/

<<<<<<< HEAD
#ifndef __SNES_SPC_H__
#define __SNES_SPC_H__


#define SNES_SPCRAM_SIZE      0x10000
=======
#ifndef MAME_AUDIO_SNES_SND_H
#define MAME_AUDIO_SNES_SND_H
>>>>>>> upstream/master


/***************************************************************************
 TYPE DEFINITIONS
 ***************************************************************************/

<<<<<<< HEAD
enum env_state_t32                        /* ADSR state type              */
{
	ATTACK,
	DECAY,
	SUSTAIN,
	RELEASE
};

ALLOW_SAVE_TYPE(env_state_t32);

struct voice_state_type                      /* Voice state type             */
{
	UINT16          mem_ptr;        /* Sample data memory pointer   */
	int             end;            /* End or loop after block      */
	int             envcnt;         /* Counts to envelope update    */
	env_state_t32   envstate;       /* Current envelope state       */
	int             envx;           /* Last env height (0-0x7FFF)   */
	int             filter;         /* Last header's filter         */
	int             half;           /* Active nybble of BRR         */
	int             header_cnt;     /* Bytes before new header (0-8)*/
	int             mixfrac;        /* Fractional part of smpl pstn */
	int             on_cnt;         /* Is it time to turn on yet?   */
	int             pitch;          /* Sample pitch (4096->32000Hz) */
	int             range;          /* Last header's range          */
	UINT32          samp_id;        /* Sample ID#                   */
	int             sampptr;        /* Where in sampbuf we are      */
	INT32           smp1;           /* Last sample (for BRR filter) */
	INT32           smp2;           /* Second-to-last sample decoded*/
	short           sampbuf[4];   /* Buffer for Gaussian interp   */
};

struct src_dir_type                      /* Source directory entry       */
{
	UINT16  vptr;           /* Ptr to start of sample data  */
	UINT16  lptr;           /* Loop pointer in sample data  */
};


/***************************************************************************
 DEVICE CONFIGURATION MACROS
 ***************************************************************************/

=======
>>>>>>> upstream/master
class snes_sound_device : public device_t,
							public device_sound_interface
{
public:
<<<<<<< HEAD
	snes_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~snes_sound_device() {}
=======
	snes_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	void set_volume(int volume);

	DECLARE_READ8_MEMBER( spc_io_r );
	DECLARE_READ8_MEMBER( spc_ram_r );
	DECLARE_READ8_MEMBER( spc_port_out );
	DECLARE_WRITE8_MEMBER( spc_io_w );
	DECLARE_WRITE8_MEMBER( spc_ram_w );
	DECLARE_WRITE8_MEMBER( spc_port_in );

<<<<<<< HEAD
//  UINT8 *spc_get_ram() { return m_ram; }

protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

private:
=======
//  uint8_t *spc_get_ram() { return m_ram; }

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

private:
	enum class env_state_t32 : u8
	{
		ATTACK,
		DECAY,
		SUSTAIN,
		RELEASE
	};


	static constexpr unsigned SNES_SPCRAM_SIZE = 0x10000;


	struct voice_state_type                      /* Voice state type             */
	{
		uint16_t          mem_ptr;        /* Sample data memory pointer   */
		int             end;            /* End or loop after block      */
		int             envcnt;         /* Counts to envelope update    */
		env_state_t32   envstate;       /* Current envelope state       */
		int             envx;           /* Last env height (0-0x7FFF)   */
		int             filter;         /* Last header's filter         */
		int             half;           /* Active nybble of BRR         */
		int             header_cnt;     /* Bytes before new header (0-8)*/
		int             mixfrac;        /* Fractional part of smpl pstn */
		int             on_cnt;         /* Is it time to turn on yet?   */
		int             pitch;          /* Sample pitch (4096->32000Hz) */
		int             range;          /* Last header's range          */
		uint32_t          samp_id;        /* Sample ID#                   */
		int             sampptr;        /* Where in sampbuf we are      */
		int32_t           smp1;           /* Last sample (for BRR filter) */
		int32_t           smp2;           /* Second-to-last sample decoded*/
		short           sampbuf[4];   /* Buffer for Gaussian interp   */
	};

	struct src_dir_type                      /* Source directory entry       */
	{
		uint16_t  vptr;           /* Ptr to start of sample data  */
		uint16_t  lptr;           /* Loop pointer in sample data  */
	};

>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(dsp_io_r);
	DECLARE_WRITE8_MEMBER(dsp_io_w);
	TIMER_CALLBACK_MEMBER(spc_timer);
	void dsp_reset();
	void dsp_update(short *sound_ptr);
	int advance_envelope(int v);
	void state_register();

	// internal state
<<<<<<< HEAD
	UINT8                   *m_ram;
	sound_stream            *m_channel;
	UINT8                   m_dsp_regs[256];      /* DSP registers */
	UINT8                   m_ipl_region[64];     /* SPC top 64 bytes */
=======
	std::unique_ptr<uint8_t[]>                   m_ram;
	sound_stream            *m_channel;
	uint8_t                   m_dsp_regs[256];      /* DSP registers */
	uint8_t                   m_ipl_region[64];     /* SPC top 64 bytes */
>>>>>>> upstream/master

	int                     m_keyed_on;
	int                     m_keys;               /* 8-bits for 8 voices */
	voice_state_type        m_voice_state[8];

	/* Noise stuff */
	int                     m_noise_cnt;
	int                     m_noise_lev;

	/* These are for the FIR echo filter */
#ifndef NO_ECHO
	short                   m_fir_lbuf[8];
	short                   m_fir_rbuf[8];
	int                     m_fir_ptr;
	int                     m_echo_ptr;
#endif

	/* timers */
	emu_timer               *m_timer[3];
<<<<<<< HEAD
	UINT8                   m_enabled[3];
	UINT16                  m_counter[3];

	/* IO ports */
	UINT8                   m_port_in[4];         /* SPC input ports */
	UINT8                   m_port_out[4];        /* SPC output ports */
};

extern const device_type SNES;


#endif /* __SNES_SPC_H__ */
=======
	uint8_t                   m_enabled[3];
	uint16_t                  m_counter[3];

	/* IO ports */
	uint8_t                   m_port_in[4];         /* SPC input ports */
	uint8_t                   m_port_out[4];        /* SPC output ports */
};

DECLARE_DEVICE_TYPE(SNES, snes_sound_device)


#endif // MAME_AUDIO_SNES_SND_H
>>>>>>> upstream/master
