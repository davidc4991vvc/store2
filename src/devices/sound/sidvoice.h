// license:BSD-3-Clause
// copyright-holders:Peter Trauner
<<<<<<< HEAD
#pragma once

#ifndef __SIDVOICE_H__
#define __SIDVOICE_H__
=======
#ifndef MAME_SOUND_SIDVOICE_H
#define MAME_SOUND_SIDVOICE_H

#pragma once
>>>>>>> upstream/master


/*
  approximation of the sid6581 chip
  this part is for 1 (of the 3) voices of a chip
*/
<<<<<<< HEAD
#include "sound/mos6581.h"

struct sw_storage
{
	UINT16 len;
#if defined(DIRECT_FIXPOINT)
	UINT32 stp;
#else
	UINT32 pnt;
	INT16 stp;
#endif
};

struct SID6581_t;

struct sidOperator
{
	SID6581_t *sid;
	UINT8 reg[7];
	UINT32 SIDfreq;
	UINT16 SIDpulseWidth;
	UINT8 SIDctrl;
	UINT8 SIDAD, SIDSR;
=======
struct SID6581_t;

struct sidOperator
{
	struct sw_storage
	{
		uint16_t len;
#if defined(DIRECT_FIXPOINT)
		uint32_t stp;
#else
		uint32_t pnt;
		int16_t stp;
#endif
	};

	SID6581_t *sid;
	uint8_t reg[7];
	uint32_t SIDfreq;
	uint16_t SIDpulseWidth;
	uint8_t SIDctrl;
	uint8_t SIDAD, SIDSR;
>>>>>>> upstream/master

	sidOperator* carrier;
	sidOperator* modulator;
	int sync;

<<<<<<< HEAD
	UINT16 pulseIndex, newPulseIndex;
	UINT16 curSIDfreq;
	UINT16 curNoiseFreq;

	UINT8 output;//, outputMask;
=======
	uint16_t pulseIndex, newPulseIndex;
	uint16_t curSIDfreq;
	uint16_t curNoiseFreq;

	uint8_t output;//, outputMask;
>>>>>>> upstream/master

	char filtVoiceMask;
	int filtEnabled;
	float filtLow, filtRef;
<<<<<<< HEAD
	INT8 filtIO;

	INT32 cycleLenCount;
#if defined(DIRECT_FIXPOINT)
	cpuLword cycleLen, cycleAddLen;
#else
	UINT32 cycleAddLenPnt;
	UINT16 cycleLen, cycleLenPnt;
#endif

	INT8(*outProc)(sidOperator *);
	void(*waveProc)(sidOperator *);
=======
	int8_t filtIO;

	int32_t cycleLenCount;
#if defined(DIRECT_FIXPOINT)
	cpuLword cycleLen, cycleAddLen;
#else
	uint32_t cycleAddLenPnt;
	uint16_t cycleLen, cycleLenPnt;
#endif

	int8_t (*outProc)(sidOperator *);
	void (*waveProc)(sidOperator *);
>>>>>>> upstream/master

#if defined(DIRECT_FIXPOINT)
	cpuLword waveStep, waveStepAdd;
#else
<<<<<<< HEAD
	UINT16 waveStep, waveStepAdd;
	UINT32 waveStepPnt, waveStepAddPnt;
#endif
	UINT16 waveStepOld;
	struct sw_storage wavePre[2];
=======
	uint16_t waveStep, waveStepAdd;
	uint32_t waveStepPnt, waveStepAddPnt;
#endif
	uint16_t waveStepOld;
	sw_storage wavePre[2];
>>>>>>> upstream/master

#if defined(DIRECT_FIXPOINT) && defined(LARGE_NOISE_TABLE)
	cpuLword noiseReg;
#elif defined(DIRECT_FIXPOINT)
	cpuLBword noiseReg;
#else
<<<<<<< HEAD
	UINT32 noiseReg;
#endif
	UINT32 noiseStep, noiseStepAdd;
	UINT8 noiseOutput;
	int noiseIsLocked;

	UINT8 ADSRctrl;
//  int gateOnCtrl, gateOffCtrl;
	UINT16 (*ADSRproc)(sidOperator *);

#ifdef SID_FPUENVE
	float fenveStep, fenveStepAdd;
	UINT32 enveStep;
#elif defined(DIRECT_FIXPOINT)
	cpuLword enveStep, enveStepAdd;
#else
	UINT16 enveStep, enveStepAdd;
	UINT32 enveStepPnt, enveStepAddPnt;
#endif
	UINT8 enveVol, enveSusVol;
	UINT16 enveShortAttackCount;
};

typedef INT8 (*ptr2sidFunc)(sidOperator *);
typedef UINT16 (*ptr2sidUwordFunc)(sidOperator *);
typedef void (*ptr2sidVoidFunc)(sidOperator *);

void sidClearOperator( sidOperator* pVoice );

void sidEmuSet(sidOperator* pVoice);
void sidEmuSet2(sidOperator* pVoice);
INT8 sidWaveCalcNormal(sidOperator* pVoice);
=======
	uint32_t noiseReg;
#endif
	uint32_t noiseStep, noiseStepAdd;
	uint8_t noiseOutput;
	int noiseIsLocked;

	uint8_t ADSRctrl;
//  int gateOnCtrl, gateOffCtrl;
	uint16_t (*ADSRproc)(sidOperator *);

#ifdef SID_FPUENVE
	float fenveStep, fenveStepAdd;
	uint32_t enveStep;
#elif defined(DIRECT_FIXPOINT)
	cpuLword enveStep, enveStepAdd;
#else
	uint16_t enveStep, enveStepAdd;
	uint32_t enveStepPnt, enveStepAddPnt;
#endif
	uint8_t enveVol, enveSusVol;
	uint16_t enveShortAttackCount;

	void clear();

	void set();
	void set2();
	static int8_t wave_calc_normal(sidOperator *pVoice);

private:
	void wave_calc_cycle_len();
};

typedef int8_t (*ptr2sidFunc)(sidOperator *);
typedef uint16_t (*ptr2sidUwordFunc)(sidOperator *);
typedef void (*ptr2sidVoidFunc)(sidOperator *);
>>>>>>> upstream/master

void sidInitWaveformTables(int type);
void sidInitMixerEngine(running_machine &machine);

#if 0
extern ptr2sidVoidFunc sid6581ModeNormalTable[16];
extern ptr2sidVoidFunc sid6581ModeRingTable[16];
extern ptr2sidVoidFunc sid8580ModeNormalTable[16];
extern ptr2sidVoidFunc sid8580ModeRingTable[16];
#endif

<<<<<<< HEAD
#endif /* __SIDVOICE_H__ */
=======
#endif // MAME_SOUND_SIDVOICE_H
>>>>>>> upstream/master
