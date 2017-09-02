// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    cclimber.h

    Functions to emulate the cclimber audio boards

***************************************************************************/
<<<<<<< HEAD

#pragma once

#ifndef __CCLIMBER_AUDIO__
#define __CCLIMBER_AUDIO__

#include "emu.h"
#include "sound/samples.h"
=======
#ifndef MAME_AUDIO_CCLIMBER_H
#define MAME_AUDIO_CCLIMBER_H

#pragma once

#include "sound/samples.h"

>>>>>>> upstream/master
//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
extern const device_type CCLIMBER_AUDIO;
=======
DECLARE_DEVICE_TYPE(CCLIMBER_AUDIO, cclimber_audio_device)
>>>>>>> upstream/master

//**************************************************************************
//  DEVICE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_CCLIMBER_AUDIO_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, CCLIMBER_AUDIO, 0)


// ======================> cclimber_audio_device

class cclimber_audio_device : public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	cclimber_audio_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	DECLARE_WRITE8_MEMBER( sample_trigger_w );
	DECLARE_WRITE8_MEMBER( sample_rate_w );
	DECLARE_WRITE8_MEMBER( sample_volume_w );
	DECLARE_WRITE8_MEMBER( sample_select_w );

	SAMPLES_START_CB_MEMBER( sh_start );

protected:
	// device level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	cclimber_audio_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_WRITE_LINE_MEMBER(sample_trigger_w);
	DECLARE_WRITE8_MEMBER(sample_trigger_w);
	DECLARE_WRITE8_MEMBER(sample_rate_w);
	DECLARE_WRITE8_MEMBER(sample_volume_w);

protected:
	// device level overrides
	virtual void device_start() override;
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

	void play_sample(int start,int freq,int volume);

private:
<<<<<<< HEAD
	INT16 *m_sample_buf;    /* buffer to decode samples at run time */
	int m_sample_num;
	int m_sample_freq;
	int m_sample_volume;
	required_device<samples_device> m_samples;
};


#endif
=======
	std::unique_ptr<int16_t[]> m_sample_buf;    /* buffer to decode samples at run time */
	int m_sample_num;
	int m_sample_freq;
	int m_sample_volume;
	optional_device<samples_device> m_samples;
	optional_region_ptr<uint8_t> m_samples_region;

	DECLARE_WRITE8_MEMBER( sample_select_w );

	SAMPLES_START_CB_MEMBER( sh_start );
};


#endif // MAME_AUDIO_CCLIMBER_H
>>>>>>> upstream/master
