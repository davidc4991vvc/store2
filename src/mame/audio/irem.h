// license:BSD-3-Clause
// copyright-holders:Couriersud
<<<<<<< HEAD
#include "sound/ay8910.h"
#include "sound/msm5205.h"
#include "machine/netlist.h"
=======
#ifndef MAME_AUDIO_IREM_H
#define MAME_AUDIO_IREM_H

#pragma once

#include "sound/ay8910.h"
#include "sound/msm5205.h"
#include "machine/netlist.h"
#include "audio/nl_kidniki.h"
>>>>>>> upstream/master

class irem_audio_device : public device_t
{
public:
<<<<<<< HEAD
	irem_audio_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	~irem_audio_device() {}

=======
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER( cmd_w );
	DECLARE_WRITE8_MEMBER( m6803_port1_w );
	DECLARE_WRITE8_MEMBER( m6803_port2_w );
	DECLARE_READ8_MEMBER( m6803_port1_r );
	DECLARE_READ8_MEMBER( m6803_port2_r );
<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER( ay8910_45M_portb_w );
	DECLARE_WRITE8_MEMBER( ay8910_45L_porta_w );
=======
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER( sound_irq_ack_w );
	DECLARE_WRITE8_MEMBER( m52_adpcm_w );
	DECLARE_WRITE8_MEMBER( m62_adpcm_w );

<<<<<<< HEAD
	void adpcm_int(int st);

	netlist_mame_logic_input_t * m_audio_SINH;

protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();

private:
	// internal state
	UINT8           m_port1;
	UINT8           m_port2;

	/* FIXME: using required / optional device would be better */
	// required_device<ay8910_device> m_ay_45L;
	// required_device<ay8910_device> m_ay_45M;
	ay8910_device *m_ay_45L;
	ay8910_device *m_ay_45M;
	msm5205_device *m_adpcm1;
	msm5205_device *m_adpcm2;

	netlist_mame_logic_input_t * m_audio_BD;
	netlist_mame_logic_input_t * m_audio_SD;
	netlist_mame_logic_input_t * m_audio_OH;
	netlist_mame_logic_input_t * m_audio_CH;
=======
	netlist_mame_logic_input_device * m_audio_SINH;

	DECLARE_READ8_MEMBER( soundlatch_r );
	DECLARE_WRITE8_MEMBER( ay8910_45M_portb_w );
	DECLARE_WRITE8_MEMBER( ay8910_45L_porta_w );

protected:
	irem_audio_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	// internal state
	uint8_t           m_port1;
	uint8_t           m_port2;

	uint8_t           m_soundlatch;

	required_device<cpu_device> m_cpu;
	required_device<ay8910_device> m_ay_45L;
	required_device<ay8910_device> m_ay_45M;
	required_device<msm5205_device> m_adpcm1;
	optional_device<msm5205_device> m_adpcm2;
	optional_device<netlist_mame_logic_input_device> m_audio_BD;
	optional_device<netlist_mame_logic_input_device> m_audio_SD;
	optional_device<netlist_mame_logic_input_device> m_audio_OH;
	optional_device<netlist_mame_logic_input_device> m_audio_CH;
>>>>>>> upstream/master
};

class m62_audio_device : public irem_audio_device
{
public:
<<<<<<< HEAD
	m62_audio_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	m62_audio_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master
};

class m52_soundc_audio_device : public irem_audio_device
{
public:
<<<<<<< HEAD
	m52_soundc_audio_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	m52_soundc_audio_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master
};

class m52_large_audio_device : public irem_audio_device
{
public:
<<<<<<< HEAD
	m52_large_audio_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual machine_config_constructor device_mconfig_additions() const;
};

//MACHINE_CONFIG_EXTERN( m52_sound_c_audio );
//MACHINE_CONFIG_EXTERN( m52_large_audio );
//MACHINE_CONFIG_EXTERN( m62_audio );

extern const device_type IREM_M62_AUDIO;
extern const device_type IREM_M52_SOUNDC_AUDIO;
extern const device_type IREM_M52_LARGE_AUDIO;
=======
	m52_large_audio_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
};


DECLARE_DEVICE_TYPE(IREM_M62_AUDIO,        m62_audio_device)
DECLARE_DEVICE_TYPE(IREM_M52_SOUNDC_AUDIO, m52_soundc_audio_device)
DECLARE_DEVICE_TYPE(IREM_M52_LARGE_AUDIO,  m52_large_audio_device)

#endif // MAME_AUDIO_IREM_H
>>>>>>> upstream/master
