// license:BSD-3-Clause
// copyright-holders:Peter Trauner
<<<<<<< HEAD
#pragma once

#ifndef __SID_H__
#define __SID_H__
=======
#ifndef MAME_SOUND_SID_H
#define MAME_SOUND_SID_H

#pragma once
>>>>>>> upstream/master

/*
  approximation of the sid6581 chip
  this part is for one chip,
*/

#include "sidvoice.h"

/* private area */
struct SID6581_t
{
	device_t *device;
	sound_stream *mixer_channel; // mame stream/ mixer channel

	int type;
<<<<<<< HEAD
	UINT32 clock;

	UINT16 PCMfreq; // samplerate of the current systems soundcard/DAC
	UINT32 PCMsid, PCMsidNoise;
=======
	uint32_t clock;

	uint16_t PCMfreq; // samplerate of the current systems soundcard/DAC
	uint32_t PCMsid, PCMsidNoise;
>>>>>>> upstream/master

#if 0
	/* following depends on type */
	ptr2sidVoidFunc ModeNormalTable[16];
	ptr2sidVoidFunc ModeRingTable[16];
	// for speed reason it could be better to make them global!
<<<<<<< HEAD
	UINT8* waveform30;
	UINT8* waveform50;
	UINT8* waveform60;
	UINT8* waveform70;
=======
	uint8_t* waveform30;
	uint8_t* waveform50;
	uint8_t* waveform60;
	uint8_t* waveform70;
>>>>>>> upstream/master
#endif
	int reg[0x20];

//  bool sidKeysOn[0x20], sidKeysOff[0x20];

<<<<<<< HEAD
	UINT8 masterVolume;
	UINT16 masterVolumeAmplIndex;

=======
	uint8_t masterVolume;
	uint16_t masterVolumeAmplIndex;
>>>>>>> upstream/master

	struct
	{
		int Enabled;
<<<<<<< HEAD
		UINT8 Type, CurType;
		float Dy, ResDy;
		UINT16 Value;
=======
		uint8_t Type, CurType;
		float Dy, ResDy;
		uint16_t Value;
>>>>>>> upstream/master
	} filter;

	sidOperator optr1, optr2, optr3;
	int optr3_outputmask;
<<<<<<< HEAD
};

void sid6581_init (SID6581_t *This);

int sidEmuReset(SID6581_t *This);

int sid6581_port_r (running_machine &machine, SID6581_t *This, int offset);
void sid6581_port_w (SID6581_t *This, int offset, int data);

void sidEmuFillBuffer(SID6581_t *This, stream_sample_t *buffer, UINT32 bufferLen );

#endif /* __SID_H__ */
=======

	void init();

	bool reset();

	int port_r(running_machine &machine, int offset);
	void port_w(int offset, int data);

	void fill_buffer(stream_sample_t *buffer, uint32_t bufferLen);

private:
	void syncEm();
};

#endif // MAME_SOUND_SID_H
>>>>>>> upstream/master
