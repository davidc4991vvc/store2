<<<<<<< HEAD
// license:???
// copyright-holders:ElSemi, kingshriek, Deunan Knute, R. Belmont
#pragma once

#ifndef __AICADSP_H__
#define __AICADSP_H__
=======
// license:BSD-3-Clause
// copyright-holders:ElSemi, Deunan Knute, R. Belmont
#ifndef MAME_SOUND_AICADSP_H
#define MAME_SOUND_AICADSP_H

#pragma once
>>>>>>> upstream/master

//the DSP Context
struct AICADSP
{
<<<<<<< HEAD
//Config
	UINT16 *AICARAM;
	UINT32 AICARAM_LENGTH;
	UINT32 RBP; //Ring buf pointer
	UINT32 RBL; //Delay ram (Ring buffer) size in words

//context

	INT16 COEF[128*2];      //16 bit signed
	UINT16 MADRS[64*2]; //offsets (in words), 16 bit
	UINT16 MPRO[128*4*2*2]; //128 steps 64 bit
	INT32 TEMP[128];    //TEMP regs,24 bit signed
	INT32 MEMS[32]; //MEMS regs,24 bit signed
	UINT32 DEC;

//input
	INT32 MIXS[16]; //MIXS, 24 bit signed
	INT16 EXTS[2];  //External inputs (CDDA)    16 bit signed

//output
	INT16 EFREG[16];    //EFREG, 16 bit signed
=======
	void init();
	void setsample(int32_t sample, int32_t SEL, int32_t MXL);
	void step();
	void start();

//Config
	uint16_t *AICARAM;
	uint32_t AICARAM_LENGTH;
	uint32_t RBP; //Ring buf pointer
	uint32_t RBL; //Delay ram (Ring buffer) size in words

//context

	int16_t COEF[128*2];      //16 bit signed
	uint16_t MADRS[64*2]; //offsets (in words), 16 bit
	uint16_t MPRO[128*4*2*2]; //128 steps 64 bit
	int32_t TEMP[128];    //TEMP regs,24 bit signed
	int32_t MEMS[32]; //MEMS regs,24 bit signed
	uint32_t DEC;

//input
	int32_t MIXS[16]; //MIXS, 24 bit signed
	int16_t EXTS[2];  //External inputs (CDDA)    16 bit signed

//output
	int16_t EFREG[16];    //EFREG, 16 bit signed
>>>>>>> upstream/master

	int Stopped;
	int LastStep;
};

<<<<<<< HEAD
void aica_dsp_init(AICADSP *DSP);
void aica_dsp_setsample(AICADSP *DSP, INT32 sample, INT32 SEL, INT32 MXL);
void aica_dsp_step(AICADSP *DSP);
void aica_dsp_start(AICADSP *DSP);

#endif /* __AICADSP_H__ */
=======
#endif // MAME_SOUND_AICADSP_H
>>>>>>> upstream/master
