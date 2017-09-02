<<<<<<< HEAD
// license:???
=======
// license:BSD-3-Clause
>>>>>>> upstream/master
// copyright-holders:Martin Buchholz
/***************************************************************************

  Poly-Play
  (c) 1985 by VEB Polytechnik Karl-Marx-Stadt

  sound hardware

  driver written by Martin Buchholz (buchholz@mail.uni-greifswald.de)

***************************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "sound/samples.h"
#include "includes/polyplay.h"

#define LFO_VOLUME 25
#define SAMPLE_AMPLITUDE 0x4000



SAMPLES_START_CB_MEMBER(polyplay_state::sh_start)
{
	int i;

	for (i = 0; i < SAMPLE_LENGTH / 2; i++) {
		m_backgroundwave[i] = + SAMPLE_AMPLITUDE;
	}
	for (i = SAMPLE_LENGTH / 2; i < SAMPLE_LENGTH; i++) {
		m_backgroundwave[i] = - SAMPLE_AMPLITUDE;
	}
	m_freq1 = m_freq2 = 110;
	m_channel_playing1 = 0;
	m_channel_playing2 = 0;
}

void polyplay_state::set_channel1(int active)
{
	m_channel_playing1 = active;
}

void polyplay_state::set_channel2(int active)
{
	m_channel_playing2 = active;
}

void polyplay_state::play_channel1(int data)
{
	if (data) {
		m_freq1 = 2457600 / 16 / data / 8;
		m_samples->set_volume(0, m_channel_playing1 * 1.0);
		m_samples->start_raw(0, m_backgroundwave, ARRAY_LENGTH(m_backgroundwave), sizeof(m_backgroundwave)*m_freq1,true);
	}
	else {
		m_samples->stop(0);
		m_samples->stop(1);
	}
}

void polyplay_state::play_channel2(int data)
{
	if (data) {
		m_freq2 = 2457600 / 16 / data / 8;
		m_samples->set_volume(1, m_channel_playing2 * 1.0);
		m_samples->start_raw(1, m_backgroundwave, ARRAY_LENGTH(m_backgroundwave), sizeof(m_backgroundwave)*m_freq2,true);
	}
	else {
		m_samples->stop(0);
		m_samples->stop(1);
=======
#include "includes/polyplay.h"

WRITE_LINE_MEMBER(polyplay_state::ctc_zc0_w)
{
	if (state)
	{
		m_flipflop1 = ~m_flipflop1;
		m_speaker1->level_w(m_flipflop1);
	}
}

WRITE_LINE_MEMBER(polyplay_state::ctc_zc1_w)
{
	if (state)
	{
		m_flipflop2 = ~m_flipflop2;
		m_speaker2->level_w(m_flipflop2);
>>>>>>> upstream/master
	}
}
