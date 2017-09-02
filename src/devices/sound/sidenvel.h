// license:BSD-3-Clause
// copyright-holders:Peter Trauner
//
// /home/ms/source/sidplay/libsidplay/emu/RCS/envelope.h,v
//

<<<<<<< HEAD
#pragma once

#ifndef __SIDENVEL_H__
#define __SIDENVEL_H__


extern void enveEmuInit(UINT32 updateFreq, int measuredValues);
=======
#ifndef MAME_SOUND_SIDENVEL_H
#define MAME_SOUND_SIDENVEL_H

#pragma once

#include "sidvoice.h"


extern void enveEmuInit(uint32_t updateFreq, int measuredValues);
>>>>>>> upstream/master
void enveEmuResetOperator(sidOperator* pVoice);


extern const ptr2sidUwordFunc enveModeTable[];   // -> envelope.cpp
<<<<<<< HEAD
extern const UINT8 masterVolumeLevels[16];  // -> envelope.cpp
=======
extern const uint8_t masterVolumeLevels[16];  // -> envelope.cpp
>>>>>>> upstream/master

enum
{
	ENVE_STARTATTACK = 0,
	ENVE_STARTRELEASE = 2,

	ENVE_ATTACK = 4,
	ENVE_DECAY = 6,
	ENVE_SUSTAIN = 8,
	ENVE_RELEASE = 10,
	ENVE_SUSTAINDECAY = 12,
	ENVE_MUTE = 14,

	ENVE_STARTSHORTATTACK = 16,
	ENVE_SHORTATTACK = 16,

	ENVE_ALTER = 32
};


<<<<<<< HEAD
#endif /* __SIDENVEL_H__ */
=======
#endif // MAME_SOUND_SIDENVEL_H
>>>>>>> upstream/master
