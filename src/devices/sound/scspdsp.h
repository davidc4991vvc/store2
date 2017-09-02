// license:BSD-3-Clause
// copyright-holders:ElSemi, R. Belmont
<<<<<<< HEAD
#pragma once

#ifndef __SCSPDSP_H__
#define __SCSPDSP_H__
=======
#ifndef MAME_SOUND_SCSPDSP_H
#define MAME_SOUND_SCSPDSP_H

#pragma once
>>>>>>> upstream/master

//the DSP Context
struct SCSPDSP
{
//Config
<<<<<<< HEAD
	UINT16 *SCSPRAM;
	UINT32 SCSPRAM_LENGTH;
	UINT32 RBP; //Ring buf pointer
	UINT32 RBL; //Delay ram (Ring buffer) size in words

//context

	INT16 COEF[64];     //16 bit signed
	UINT16 MADRS[32];   //offsets (in words), 16 bit
	UINT16 MPRO[128*4]; //128 steps 64 bit
	INT32 TEMP[128];    //TEMP regs,24 bit signed
	INT32 MEMS[32]; //MEMS regs,24 bit signed
	UINT32 DEC;

//input
	INT32 MIXS[16]; //MIXS, 24 bit signed
	INT16 EXTS[2];  //External inputs (CDDA)    16 bit signed

//output
	INT16 EFREG[16];    //EFREG, 16 bit signed

	int Stopped;
	int LastStep;
};

void SCSPDSP_Init(SCSPDSP *DSP);
void SCSPDSP_SetSample(SCSPDSP *DSP, INT32 sample, INT32 SEL, INT32 MXL);
void SCSPDSP_Step(SCSPDSP *DSP);
void SCSPDSP_Start(SCSPDSP *DSP);

#endif /* __SCSPDSP_H__ */
=======
	uint16_t *SCSPRAM;
	uint32_t SCSPRAM_LENGTH;
	uint32_t RBP; //Ring buf pointer
	uint32_t RBL; //Delay ram (Ring buffer) size in words

//context

	int16_t COEF[64];     //16 bit signed
	uint16_t MADRS[32];   //offsets (in words), 16 bit
	uint16_t MPRO[128*4]; //128 steps 64 bit
	int32_t TEMP[128];    //TEMP regs,24 bit signed
	int32_t MEMS[32]; //MEMS regs,24 bit signed
	uint32_t DEC;

//input
	int32_t MIXS[16]; //MIXS, 24 bit signed
	int16_t EXTS[2];  //External inputs (CDDA)    16 bit signed

//output
	int16_t EFREG[16];    //EFREG, 16 bit signed

	int Stopped;
	int LastStep;

	void Init();
	void SetSample(int32_t sample, int32_t SEL, int32_t MXL);
	void Step();
	void Start();
};

#endif // MAME_SOUND_SCSPDSP_H
>>>>>>> upstream/master
