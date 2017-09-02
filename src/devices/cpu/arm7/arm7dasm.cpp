// license:BSD-3-Clause
// copyright-holders:Steve Ellenoff,R. Belmont,Ryan Holtz
/*****************************************************************************
 *
 *   arm7dasm.c
 *   Portable ARM7TDMI Core Emulator - Disassembler
 *
 *   Copyright Steve Ellenoff, all rights reserved.
 *
 *  This work is based on:
 *  #1) 'Atmel Corporation ARM7TDMI (Thumb) Datasheet - January 1999'
 *  #2) Arm 2/3/6 emulator By Bryan McPhail (bmcphail@tendril.co.uk) and Phil Stroffolino (MAME CORE 0.76)
 *
 *****************************************************************************/
/******************************************************************************
 *  Notes:
 *
 *  Because Co-Processor functions are highly specialized to the actual co-proc
 *  implementation being used, I've setup callback handlers to allow for custom
 *  dasm display of the co-proc functions so that the implementation specific
 *  commands/interpretation can be used. If not used, the default handlers which
 *  implement the ARM7TDMI guideline format is used
 ******************************************************************************/

#include "emu.h"
#include "arm7core.h"

<<<<<<< HEAD
static char *WritePadding( char *pBuf, const char *pBuf0 )
{
	pBuf0 += 8;
	while( pBuf<pBuf0 )
	{
		*pBuf++ = ' ';
	}
	return pBuf;
}

static char *DasmCoProc_RT( char *pBuf, UINT32 opcode, const char *pConditionCode, const char *pBuf0)
=======
static void WritePadding(std::ostream &stream, std::streampos start_position)
{
	std::streamoff difference = stream.tellp() - start_position;
	for (std::streamoff i = difference; i < 8; i++)
		stream << ' ';
}

static void DasmCoProc_RT(std::ostream &stream, uint32_t opcode, const char *pConditionCode, std::streampos start_position)
>>>>>>> upstream/master
{
	/* co processor register transfer */
	/* xxxx 1110 oooL nnnn dddd cccc ppp1 mmmm */
	if( opcode&0x00100000 )     //Bit 20 = Load or Store
	{
<<<<<<< HEAD
		pBuf += sprintf( pBuf, "MRC" );
	}
	else
	{
		pBuf += sprintf( pBuf, "MCR" );
	}
	pBuf += sprintf( pBuf, "%s", pConditionCode );
	pBuf = WritePadding( pBuf, pBuf0 );
	pBuf += sprintf( pBuf, "p%d, %d, R%d, c%d, c%d",
					(opcode>>8)&0xf, (opcode>>21)&7, (opcode>>12)&0xf, (opcode>>16)&0xf, opcode&0xf );
	if((opcode>>5)&7) pBuf += sprintf( pBuf, ", %d",(opcode>>5)&7);
	return pBuf;
}

static char *DasmCoProc_DT( char *pBuf, UINT32 opcode, const char *pConditionCode, const char *pBuf0 )
=======
		util::stream_format( stream, "MRC" );
	}
	else
	{
		util::stream_format( stream, "MCR" );
	}
	util::stream_format( stream, "%s", pConditionCode );
	WritePadding(stream, start_position);
	util::stream_format( stream, "p%d, %d, R%d, c%d, c%d",
					(opcode>>8)&0xf, (opcode>>21)&7, (opcode>>12)&0xf, (opcode>>16)&0xf, opcode&0xf );
	if((opcode>>5)&7) util::stream_format( stream, ", %d",(opcode>>5)&7);
}

static void DasmCoProc_DT(std::ostream &stream, uint32_t opcode, const char *pConditionCode, std::streampos start_position)
>>>>>>> upstream/master
{
	/* co processor data transfer */
	/* xxxx 111P UNWL nnnn dddd pppp oooooooo */
	//todo: test this on valid instructions

<<<<<<< HEAD
	pBuf += sprintf(pBuf, "%s%s",(opcode&0x00100000)?"LDC":"STC",pConditionCode);   //Bit 20 = 1 for Load, 0 for Store
	//Long Operation
	if(opcode & 0x400000)   pBuf += sprintf(pBuf, "L");
	pBuf = WritePadding( pBuf, pBuf0 );

	//P# & CD #
	pBuf += sprintf(pBuf, "p%d, c%d, ",(opcode>>8)&0x0f,(opcode>>12)&0x0f);

	//Base Register (Rn)
	pBuf += sprintf(pBuf, "[R%d%s",(opcode>>16)&0x0f,(opcode&0x1000000)?"":"]");    //If Bit 24 = 1, Pre-increment, otherwise, Post increment so close brace

	//immediate value ( 8 bit value is << 2 according to manual )
	if(opcode & 0xff)   pBuf += sprintf(pBuf, ",%s#$%x",(opcode&0x800000)?"":"-",(opcode & 0xff)<<2);

	//Pre-Inc brace & Write back
	pBuf += sprintf(pBuf, "%s%s",(opcode&0x1000000)?"]":"",(opcode&0x200000)?"{!}":"");
	return pBuf;
}

static char *DasmCoProc_DO( char *pBuf, UINT32 opcode, const char *pConditionCode, const char *pBuf0 )
{
	/* co processor data operation */
	/* xxxx 1110 oooo nnnn dddd cccc ppp0 mmmm */
	pBuf += sprintf( pBuf, "CDP" );
	pBuf += sprintf( pBuf, "%s", pConditionCode );
	pBuf = WritePadding( pBuf, pBuf0 );
	//p#,CPOpc,cd,cn,cm
	pBuf += sprintf( pBuf, "p%d, %d, c%d, c%d, c%d",
		(opcode>>8)&0xf, (opcode>>20)&0xf, (opcode>>12)&0xf, (opcode>>16)&0xf, opcode&0xf );
	if((opcode>>5)&7) pBuf += sprintf( pBuf, ", %d",(opcode>>5)&7);
	return pBuf;
}

static char *WriteImmediateOperand( char *pBuf, UINT32 opcode )
{
	/* rrrrbbbbbbbb */
	UINT32 imm;
=======
	util::stream_format(stream, "%s%s",(opcode&0x00100000)?"LDC":"STC",pConditionCode);   //Bit 20 = 1 for Load, 0 for Store
	//Long Operation
	if(opcode & 0x400000)   util::stream_format(stream, "L");
	WritePadding(stream, start_position);

	//P# & CD #
	util::stream_format(stream, "p%d, c%d, ",(opcode>>8)&0x0f,(opcode>>12)&0x0f);

	//Base Register (Rn)
	util::stream_format(stream, "[R%d%s",(opcode>>16)&0x0f,(opcode&0x1000000)?"":"]");    //If Bit 24 = 1, Pre-increment, otherwise, Post increment so close brace

	//immediate value ( 8 bit value is << 2 according to manual )
	if(opcode & 0xff)   util::stream_format(stream, ",%s#$%x",(opcode&0x800000)?"":"-",(opcode & 0xff)<<2);

	//Pre-Inc brace & Write back
	util::stream_format(stream, "%s%s",(opcode&0x1000000)?"]":"",(opcode&0x200000)?"{!}":"");
}

static void DasmCoProc_DO(std::ostream &stream, uint32_t opcode, const char *pConditionCode, std::streampos start_position)
{
	/* co processor data operation */
	/* xxxx 1110 oooo nnnn dddd cccc ppp0 mmmm */
	util::stream_format( stream, "CDP" );
	util::stream_format( stream, "%s", pConditionCode );
	WritePadding(stream, start_position);
	//p#,CPOpc,cd,cn,cm
	util::stream_format( stream, "p%d, %d, c%d, c%d, c%d",
		(opcode>>8)&0xf, (opcode>>20)&0xf, (opcode>>12)&0xf, (opcode>>16)&0xf, opcode&0xf );
	if((opcode>>5)&7) util::stream_format(stream, ", %d",(opcode>>5)&7);
}

static void WriteImmediateOperand( std::ostream &stream, uint32_t opcode )
{
	/* rrrrbbbbbbbb */
	uint32_t imm;
>>>>>>> upstream/master
	int r;

	imm = opcode&0xff;
	r = ((opcode>>8)&0xf)*2;
	imm = (imm>>r)|(r?(imm<<(32-r)):0);
<<<<<<< HEAD
	pBuf += sprintf( pBuf, ", #$%x", imm );
	return pBuf;
}

static char *WriteDataProcessingOperand( char *pBuf, UINT32 opcode, int printOp0, int printOp1, int printOp2 )
=======
	util::stream_format( stream, ", #$%x", imm );
}

static void WriteDataProcessingOperand( std::ostream &stream, uint32_t opcode, int printOp0, int printOp1, int printOp2 )
>>>>>>> upstream/master
{
	/* ccccctttmmmm */
	static const char *const pRegOp[4] = { "LSL","LSR","ASR","ROR" };

	if (printOp0)
<<<<<<< HEAD
		pBuf += sprintf(pBuf,"R%d, ", (opcode>>12)&0xf);
	if (printOp1)
		pBuf += sprintf(pBuf,"R%d, ", (opcode>>16)&0xf);

	/* Immediate Op2 */
	if( opcode&0x02000000 )
		return WriteImmediateOperand(pBuf-2,opcode);
=======
		util::stream_format(stream, "R%d, ", (opcode>>12)&0xf);
	if (printOp1)
		util::stream_format(stream, "R%d, ", (opcode>>16)&0xf);

	/* Immediate Op2 */
	if (opcode & 0x02000000)
	{
		stream.seekp(-2, std::ios_base::cur);
		WriteImmediateOperand(stream, opcode);
		return;
	}
>>>>>>> upstream/master

	/* Register Op2 */
	if (printOp2)
//SJE:  pBuf += sprintf(pBuf,"R%d, ", (opcode>>0)&0xf);
<<<<<<< HEAD
		pBuf += sprintf(pBuf,"R%d ", (opcode>>0)&0xf);

	//SJE: ignore if LSL#0 for register shift
	if( ((opcode&0x2000000) == 0) && (((opcode>>4) & 0xff)==0) )
		return pBuf;

	pBuf += sprintf(pBuf, ",%s ", pRegOp[(opcode>>5)&3] );
=======
		util::stream_format(stream, "R%d ", (opcode>>0)&0xf);

	//SJE: ignore if LSL#0 for register shift
	if( ((opcode&0x2000000) == 0) && (((opcode>>4) & 0xff)==0) )
		return;

	util::stream_format(stream, ",%s ", pRegOp[(opcode>>5)&3]);
>>>>>>> upstream/master
	//SJE: pBuf += sprintf(pBuf, "%s ", pRegOp[(opcode>>5)&3] );

	if( opcode&0x10 ) /* Shift amount specified in bottom bits of RS */
	{
<<<<<<< HEAD
		pBuf += sprintf( pBuf, "R%d", (opcode>>8)&0xf );
=======
		util::stream_format( stream, "R%d", (opcode>>8)&0xf );
>>>>>>> upstream/master
	}
	else /* Shift amount immediate 5 bit unsigned integer */
	{
		int c=(opcode>>7)&0x1f;
		if( c==0 ) c = 32;
<<<<<<< HEAD
		pBuf += sprintf( pBuf, "#%d", c );
	}
	return pBuf;
}

static char *WriteRegisterOperand1( char *pBuf, UINT32 opcode )
=======
		util::stream_format( stream, "#%d", c );
	}
}

static void WriteRegisterOperand1( std::ostream &stream, uint32_t opcode )
>>>>>>> upstream/master
{
	/* ccccctttmmmm */
	static const char *const pRegOp[4] = { "LSL","LSR","ASR","ROR" };

<<<<<<< HEAD
	pBuf += sprintf(
		pBuf,
		", R%d", /* Operand 1 register, Operand 2 register, shift type */
		(opcode>> 0)&0xf);

	//check for LSL 0
	if( (((opcode>>5)&3)==0) && (((opcode>>7)&0xf)==0) )
		return pBuf;
	else
	//Add rotation type
		pBuf += sprintf(pBuf," %s ",pRegOp[(opcode>>5)&3]);

	if( opcode&0x10 ) /* Shift amount specified in bottom bits of RS */
	{
		pBuf += sprintf( pBuf, "R%d", (opcode>>7)&0xf );
=======
	util::stream_format(
		stream,
		", R%d", /* Operand 1 register, Operand 2 register, shift type */
		(opcode >> 0) & 0xf);

	//check for LSL 0
	if ((((opcode >> 5) & 3) == 0) && (((opcode >> 7) & 0xf) == 0))
		return;
	else
		//Add rotation type
		util::stream_format(stream, " %s ", pRegOp[(opcode >> 5) & 3]);

	if( opcode&0x10 ) /* Shift amount specified in bottom bits of RS */
	{
		util::stream_format( stream, "R%d", (opcode>>7)&0xf );
>>>>>>> upstream/master
	}
	else /* Shift amount immediate 5 bit unsigned integer */
	{
		int c=(opcode>>7)&0x1f;
		if( c==0 ) c = 32;
<<<<<<< HEAD
		pBuf += sprintf( pBuf, "#%d", c );
	}
	return pBuf;
} /* WriteRegisterOperand */


static char *WriteBranchAddress( char *pBuf, UINT32 pc, UINT32 opcode )
{
	opcode &= 0x00ffffff;
	if( opcode&0x00800000 )
	{
		opcode |= 0xff000000; /* sign-extend */
	}
	pc += 8+4*opcode;
	sprintf( pBuf, "$%x", pc );
	return pBuf;
} /* WriteBranchAddress */

static UINT32 arm7_disasm( char *pBuf, UINT32 pc, UINT32 opcode )
{
	const char *pBuf0;

=======
		util::stream_format( stream, "#%d", c );
	}
} /* WriteRegisterOperand */


static void WriteBranchAddress( std::ostream &stream, uint32_t pc, uint32_t opcode, bool h_bit )
{
	opcode <<= 2;
	if (h_bit && (opcode & 0x04000000))
	{
		opcode |= 2;
	}
	opcode &= 0x03fffffe;
	if( opcode & 0x02000000 )
	{
		opcode |= 0xfc000000; /* sign-extend */
	}
	pc += 8+opcode;
	util::stream_format( stream, "$%x", pc );
} /* WriteBranchAddress */

static uint32_t arm7_disasm( std::ostream &stream, uint32_t pc, uint32_t opcode )
{
>>>>>>> upstream/master
	static const char *const pConditionCodeTable[16] =
	{
		"EQ","NE","CS","CC",
		"MI","PL","VS","VC",
		"HI","LS","GE","LT",
		"GT","LE","","NV"
	};
	static const char *const pOperation[16] =
	{
		"AND","EOR","SUB","RSB",
		"ADD","ADC","SBC","RSC",
		"TST","TEQ","CMP","CMN",
		"ORR","MOV","BIC","MVN"
	};
	const char *pConditionCode;
<<<<<<< HEAD
	UINT32 dasmflags = 0;

	pConditionCode= pConditionCodeTable[opcode>>28];
	pBuf0 = pBuf;

	if( (opcode&0x0ffffff0)==0x012fff10 ) { //bits 27-4 == 000100101111111111110001
		/* Branch and Exchange (BX) */
		pBuf += sprintf( pBuf, "B");
		pBuf += sprintf( pBuf, "%sX", pConditionCode );
		pBuf = WritePadding( pBuf, pBuf0 );
		pBuf += sprintf( pBuf, "R%d",(opcode&0xf));
		if ((opcode & 0x0f) == 14)
			dasmflags = DASMFLAG_STEP_OUT;
	}
		else if ((opcode & 0x0ff000f0) == 0x01600010)   // CLZ - v5
	{
		pBuf += sprintf(pBuf, "CLZ");
		pBuf = WritePadding( pBuf, pBuf0 );
		pBuf += sprintf(pBuf, "R%d, R%d", (opcode>>12)&0xf, opcode&0xf);
	}
		else if ((opcode & 0x0ff000f0) == 0x01000050)   // QADD - v5
	{
		pBuf += sprintf(pBuf, "QADD");
		pBuf = WritePadding( pBuf, pBuf0 );
		pBuf += sprintf(pBuf, "R%d, R%d, R%d", (opcode>>12)&0xf, opcode&0xf, (opcode>>16)&0xf);
	}
		else if ((opcode & 0x0ff000f0) == 0x01400050)   // QDADD - v5
	{
		pBuf += sprintf(pBuf, "QDADD");
		pBuf = WritePadding( pBuf, pBuf0 );
		pBuf += sprintf(pBuf, "R%d, R%d, R%d", (opcode>>12)&0xf, opcode&0xf, (opcode>>16)&0xf);
	}
		else if ((opcode & 0x0ff000f0) == 0x01200050)   // QSUB - v5
	{
		pBuf += sprintf(pBuf, "QSUB");
		pBuf = WritePadding( pBuf, pBuf0 );
		pBuf += sprintf(pBuf, "R%d, R%d, R%d", (opcode>>12)&0xf, opcode&0xf, (opcode>>16)&0xf);
	}
		else if ((opcode & 0x0ff000f0) == 0x01600050)   // QDSUB - v5
	{
		pBuf += sprintf(pBuf, "QDSUB");
		pBuf = WritePadding( pBuf, pBuf0 );
		pBuf += sprintf(pBuf, "R%d, R%d, R%d", (opcode>>12)&0xf, opcode&0xf, (opcode>>16)&0xf);
	}
		else if ((opcode & 0x0ff00090) == 0x01000080)   // SMLAxy - v5
	{
		pBuf += sprintf(pBuf, "SMLA%c%c", (opcode&0x20) ? 'T' : 'B', (opcode&0x40) ? 'T' : 'B');
		pBuf = WritePadding( pBuf, pBuf0 );
		pBuf += sprintf(pBuf, "R%d, R%d, R%d, R%d", (opcode>>16)&0xf, (opcode>>12)&0xf, opcode&0xf, (opcode>>8)&0xf);
	}
		else if ((opcode & 0x0ff00090) == 0x01400080)   // SMLALxy - v5
	{
		pBuf += sprintf(pBuf, "SMLAL%c%c", (opcode&0x20) ? 'T' : 'B', (opcode&0x40) ? 'T' : 'B');
		pBuf = WritePadding( pBuf, pBuf0 );
		pBuf += sprintf(pBuf, "R%d, R%d, R%d, R%d", (opcode>>16)&0xf, (opcode>>12)&0xf, opcode&0xf, (opcode>>8)&0xf);
	}
		else if ((opcode & 0x0ff00090) == 0x01600080)   // SMULxy - v5
	{
		pBuf += sprintf(pBuf, "SMUL%c%c", (opcode&0x20) ? 'T' : 'B', (opcode&0x40) ? 'T' : 'B');
		pBuf = WritePadding( pBuf, pBuf0 );
		pBuf += sprintf(pBuf, "R%d, R%d, R%d", (opcode>>16)&0xf, opcode&0xf, (opcode>>12)&0xf);
	}
		else if ((opcode & 0x0ff000b0) == 0x012000a0)   // SMULWy - v5
	{
		pBuf += sprintf(pBuf, "SMULW%c", (opcode&0x40) ? 'T' : 'B');
		pBuf = WritePadding( pBuf, pBuf0 );
		pBuf += sprintf(pBuf, "R%d, R%d, R%d", (opcode>>16)&0xf, opcode&0xf, (opcode>>8)&0xf);
	}
		else if ((opcode & 0x0ff000b0) == 0x01200080)   // SMLAWy - v5
	{
		pBuf += sprintf(pBuf, "SMLAW%c", (opcode&0x40) ? 'T' : 'B');
		pBuf = WritePadding( pBuf, pBuf0 );
		pBuf += sprintf(pBuf, "R%d, R%d, R%d, R%d", (opcode>>16)&0xf, opcode&0xf, (opcode>>8)&0xf, (opcode>>12)&0xf);
=======
	uint32_t dasmflags = 0;
	std::streampos start_position = stream.tellp();

	pConditionCode= pConditionCodeTable[opcode>>28];

	if( (opcode&0xfe000000)==0xfa000000 ) //bits 31-25 == 1111 101 (BLX - v5)
	{
		/* BLX */
		util::stream_format( stream, "BLX" );
		dasmflags = DASMFLAG_STEP_OVER;

		WritePadding(stream, start_position);

		WriteBranchAddress( stream, pc, opcode, true );
	}
	else if( (opcode&0x0ffffff0)==0x012fff10 ) //bits 27-4 == 000100101111111111110001
	{
		/* Branch and Exchange (BX) */
		util::stream_format( stream, "B");
		util::stream_format( stream, "%sX", pConditionCode );
		WritePadding(stream, start_position);
		util::stream_format( stream, "R%d",(opcode&0xf));
		if ((opcode & 0x0f) == 14)
			dasmflags = DASMFLAG_STEP_OUT;
	}
	else if ((opcode & 0x0ff000f0) == 0x01600010)   // CLZ - v5
	{
		util::stream_format(stream, "CLZ");
		WritePadding(stream, start_position);
		util::stream_format(stream, "R%d, R%d", (opcode>>12)&0xf, opcode&0xf);
	}
	else if ((opcode & 0x0ff000f0) == 0x01000050)   // QADD - v5
	{
		util::stream_format(stream, "QADD");
		WritePadding(stream, start_position);
		util::stream_format(stream, "R%d, R%d, R%d", (opcode>>12)&0xf, opcode&0xf, (opcode>>16)&0xf);
	}
	else if ((opcode & 0x0ff000f0) == 0x01400050)   // QDADD - v5
	{
		util::stream_format(stream, "QDADD");
		WritePadding(stream, start_position);
		util::stream_format(stream, "R%d, R%d, R%d", (opcode>>12)&0xf, opcode&0xf, (opcode>>16)&0xf);
	}
	else if ((opcode & 0x0ff000f0) == 0x01200050)   // QSUB - v5
	{
		util::stream_format(stream, "QSUB");
		WritePadding(stream, start_position);
		util::stream_format(stream, "R%d, R%d, R%d", (opcode>>12)&0xf, opcode&0xf, (opcode>>16)&0xf);
	}
	else if ((opcode & 0x0ff000f0) == 0x01600050)   // QDSUB - v5
	{
		util::stream_format(stream, "QDSUB");
		WritePadding(stream, start_position);
		util::stream_format(stream, "R%d, R%d, R%d", (opcode>>12)&0xf, opcode&0xf, (opcode>>16)&0xf);
	}
	else if ((opcode & 0x0ff00090) == 0x01000080)   // SMLAxy - v5
	{
		util::stream_format(stream, "SMLA%c%c", (opcode&0x20) ? 'T' : 'B', (opcode&0x40) ? 'T' : 'B');
		WritePadding(stream, start_position);
		util::stream_format(stream, "R%d, R%d, R%d, R%d", (opcode>>16)&0xf, (opcode>>12)&0xf, opcode&0xf, (opcode>>8)&0xf);
	}
	else if ((opcode & 0x0ff00090) == 0x01400080)   // SMLALxy - v5
	{
		util::stream_format(stream, "SMLAL%c%c", (opcode&0x20) ? 'T' : 'B', (opcode&0x40) ? 'T' : 'B');
		WritePadding(stream, start_position);
		util::stream_format(stream, "R%d, R%d, R%d, R%d", (opcode>>16)&0xf, (opcode>>12)&0xf, opcode&0xf, (opcode>>8)&0xf);
	}
	else if ((opcode & 0x0ff00090) == 0x01600080)   // SMULxy - v5
	{
		util::stream_format(stream, "SMUL%c%c", (opcode&0x20) ? 'T' : 'B', (opcode&0x40) ? 'T' : 'B');
		WritePadding(stream, start_position);
		util::stream_format(stream, "R%d, R%d, R%d", (opcode>>16)&0xf, opcode&0xf, (opcode>>12)&0xf);
	}
	else if ((opcode & 0x0ff000b0) == 0x012000a0)   // SMULWy - v5
	{
		util::stream_format(stream, "SMULW%c", (opcode&0x40) ? 'T' : 'B');
		WritePadding(stream, start_position);
		util::stream_format(stream, "R%d, R%d, R%d", (opcode>>16)&0xf, opcode&0xf, (opcode>>8)&0xf);
	}
	else if ((opcode & 0x0ff000b0) == 0x01200080)   // SMLAWy - v5
	{
		util::stream_format(stream, "SMLAW%c", (opcode&0x40) ? 'T' : 'B');
		WritePadding(stream, start_position);
		util::stream_format(stream, "R%d, R%d, R%d, R%d", (opcode>>16)&0xf, opcode&0xf, (opcode>>8)&0xf, (opcode>>12)&0xf);
>>>>>>> upstream/master
	}
	else if( (opcode&0x0e000000)==0 && (opcode&0x80) && (opcode&0x10) ) //bits 27-25 == 000, bit 7=1, bit 4=1
	{
		/* multiply or swap or half word data transfer */
		if(opcode&0x60)
		{   //bits = 6-5 != 00
			/* half word data transfer */
			if (((opcode & 0x60) == 0x40) && !(opcode & 0x100000))  // bit 20 = 0, bits 5&6 = 10 is ARMv5 LDRD
			{
<<<<<<< HEAD
				pBuf += sprintf(pBuf, "LDRD%s", pConditionCode);
			}
			else if (((opcode & 0x60) == 0x60) && !(opcode & 0x100000)) // bit 20 = 0, bits 5&6 = 11 is ARMv5 STRD
			{
				pBuf += sprintf(pBuf, "STRD%s", pConditionCode);
			}
			else
			{
				pBuf += sprintf(pBuf, "%s%s",(opcode&0x00100000)?"LDR":"STR",pConditionCode);   //Bit 20 = 1 for Load, 0 for Store
=======
				util::stream_format(stream, "LDRD%s", pConditionCode);
			}
			else if (((opcode & 0x60) == 0x60) && !(opcode & 0x100000)) // bit 20 = 0, bits 5&6 = 11 is ARMv5 STRD
			{
				util::stream_format(stream, "STRD%s", pConditionCode);
			}
			else
			{
				util::stream_format(stream, "%s%s",(opcode&0x00100000)?"LDR":"STR",pConditionCode);   //Bit 20 = 1 for Load, 0 for Store
>>>>>>> upstream/master

				//Signed? (if not, always unsigned half word)
				if(opcode&0x40)
				{
<<<<<<< HEAD
					pBuf += sprintf(pBuf, "%s",(opcode&0x20)?"SH":"SB");    //Bit 5 = 1 for Half Word, 0 for Byte
				}
				else
				{
					pBuf += sprintf(pBuf, "H");
				}
			}

			pBuf = WritePadding( pBuf, pBuf0 );

			//Dest Register
			pBuf += sprintf(pBuf, "R%d, ",(opcode>>12)&0x0f);
			//Base Register
			pBuf += sprintf(pBuf, "[R%d%s",(opcode>>16)&0x0f,(opcode&0x1000000)?"":"]");    //If Bit 24 = 1, Pre-increment, otherwise, Post increment so close brace
=======
					util::stream_format(stream, "%s",(opcode&0x20)?"SH":"SB");    //Bit 5 = 1 for Half Word, 0 for Byte
				}
				else
				{
					util::stream_format(stream, "H");
				}
			}

			WritePadding(stream, start_position);

			//Dest Register
			util::stream_format(stream, "R%d, ",(opcode>>12)&0x0f);
			//Base Register
			util::stream_format(stream, "[R%d%s",(opcode>>16)&0x0f,(opcode&0x1000000)?"":"]");    //If Bit 24 = 1, Pre-increment, otherwise, Post increment so close brace
>>>>>>> upstream/master

			//Immediate or Register Offset?
			if(opcode&0x400000) {           //Bit 22 - 1 = immediate, 0 = register
				//immediate         ( imm. value in high nibble (bits 8-11) and lo nibble (bit 0-3) )
<<<<<<< HEAD
				pBuf += sprintf(pBuf, ",%s#$%x",(opcode&0x800000)?"":"-",( (((opcode>>8)&0x0f)<<4) | (opcode&0x0f)));
			}
			else {
				//register
				pBuf += sprintf(pBuf, ",%sR%d",(opcode&0x800000)?"":"-",(opcode & 0x0f));
			}

			//Pre-Inc brace & Write back
			pBuf += sprintf(pBuf, "%s%s",(opcode&0x1000000)?"]":"",(opcode&0x200000)?"{!}":"");
=======
				util::stream_format(stream, ",%s#$%x",(opcode&0x800000)?"":"-",( (((opcode>>8)&0x0f)<<4) | (opcode&0x0f)));
			}
			else {
				//register
				util::stream_format(stream, ",%sR%d",(opcode&0x800000)?"":"-",(opcode & 0x0f));
			}

			//Pre-Inc brace & Write back
			util::stream_format(stream, "%s%s",(opcode&0x1000000)?"]":"",(opcode&0x200000)?"{!}":"");
>>>>>>> upstream/master
		}
		else {
			if(opcode&0x01000000) {     //bit 24 = 1
			/* swap */
			//todo: Test on valid instructions
				/* xxxx 0001 0B00 nnnn dddd 0000 1001 mmmm */
<<<<<<< HEAD
				pBuf += sprintf( pBuf, "SWP" );
				pBuf += sprintf( pBuf, "%s%s", pConditionCode, (opcode & 0x400000)?"B":"" );    //Bit 22 = Byte/Word selection
				//Rd, Rm, [Rn]
				pBuf += sprintf( pBuf, "R%d, R%d, [R%d]",
=======
				util::stream_format( stream, "SWP" );
				util::stream_format( stream, "%s%s", pConditionCode, (opcode & 0x400000)?"B":"" );    //Bit 22 = Byte/Word selection
				//Rd, Rm, [Rn]
				util::stream_format( stream, "R%d, R%d, [R%d]",
>>>>>>> upstream/master
								(opcode>>12)&0xf, opcode&0xf, (opcode>>16)&0xf );
			}
			else {
				/* multiply or multiply long */

				if( opcode&0x800000 )   //Bit 23 = 1 for Multiply Long
				{
					/* Multiply Long */
					/* xxxx0001 UAShhhhllllnnnn1001mmmm */

					/* Signed? */
					if( opcode&0x00400000 )
<<<<<<< HEAD
						pBuf += sprintf( pBuf, "S" );
					else
						pBuf += sprintf( pBuf, "U" );
=======
						util::stream_format( stream, "S" );
					else
						util::stream_format( stream, "U" );
>>>>>>> upstream/master

					/* Multiply & Accumulate? */
					if( opcode&0x00200000 )
					{
<<<<<<< HEAD
						pBuf += sprintf( pBuf, "MLAL" );
					}
					else
					{
						pBuf += sprintf( pBuf, "MULL" );
					}
					pBuf += sprintf( pBuf, "%s", pConditionCode );
=======
						util::stream_format( stream, "MLAL" );
					}
					else
					{
						util::stream_format( stream, "MULL" );
					}
					util::stream_format( stream, "%s", pConditionCode );
>>>>>>> upstream/master

					/* Set Status Flags */
					if( opcode&0x00100000 )
					{
<<<<<<< HEAD
						*pBuf++ = 'S';
					}
					pBuf = WritePadding( pBuf, pBuf0 );

					//Format is RLo,RHi,Rm,Rs
					pBuf += sprintf( pBuf,
=======
						stream << 'S';
					}
					WritePadding(stream, start_position);

					//Format is RLo,RHi,Rm,Rs
					util::stream_format(stream,
>>>>>>> upstream/master
						"R%d, R%d, R%d, R%d",
						(opcode>>12)&0xf,
						(opcode>>16)&0xf,
						(opcode&0xf),
						(opcode>>8)&0xf);
				}
				else
				{
					/* Multiply */
					/* xxxx0000 00ASdddd nnnnssss 1001mmmm */

					/* Multiply & Accumulate? */
					if( opcode&0x00200000 )
					{
<<<<<<< HEAD
						pBuf += sprintf( pBuf, "MLA" );
=======
						util::stream_format( stream, "MLA" );
>>>>>>> upstream/master
					}
					/* Multiply */
					else
					{
<<<<<<< HEAD
						pBuf += sprintf( pBuf, "MUL" );
					}
					pBuf += sprintf( pBuf, "%s", pConditionCode );
					if( opcode&0x00100000 )
					{
						*pBuf++ = 'S';
					}
					pBuf = WritePadding( pBuf, pBuf0 );

					pBuf += sprintf( pBuf,
						"R%d, R%d, R%d",
						(opcode>>16)&0xf,
						(opcode&0xf),
						(opcode>>8)&0xf );

					if( opcode&0x00200000 )
					{
						pBuf += sprintf( pBuf, ", R%d", (opcode>>12)&0xf );
=======
						util::stream_format( stream, "MUL" );
					}
					util::stream_format( stream, "%s", pConditionCode );
					if( opcode&0x00100000 )
					{
						stream << 'S';
					}
					WritePadding(stream, start_position);

					util::stream_format(stream,
						"R%d, R%d, R%d",
						(opcode>>16)&0xf,
						(opcode&0xf),
						(opcode>>8)&0xf);

					if( opcode&0x00200000 )
					{
						util::stream_format( stream, ", R%d", (opcode>>12)&0xf );
>>>>>>> upstream/master
					}
				}
			}
		}
	}
	else if( (opcode&0x0c000000)==0 )       //bits 27-26 == 00 - This check can only exist properly after Multiplication check above
	{
		/* Data Processing OR PSR Transfer */

		//SJE: check for MRS & MSR ( S bit must be clear, and bit 24,23 = 10 )
		if( ((opcode&0x00100000)==0) && ((opcode&0x01800000)==0x01000000) ) {
<<<<<<< HEAD
			char strpsr[6];
			sprintf(strpsr, "%s",(opcode&0x400000)?"SPSR":"CPSR");

			//MSR ( bit 21 set )
			if( (opcode&0x00200000) ) {
				pBuf += sprintf(pBuf, "MSR%s",pConditionCode );
				//Flag Bits Only? (Bit 16 Clear)
				if( (opcode&0x10000)==0)    pBuf += sprintf(pBuf, "F");
				pBuf = WritePadding( pBuf, pBuf0 );
				pBuf += sprintf(pBuf, "%s,",strpsr);
				WriteDataProcessingOperand(pBuf, opcode, (opcode&0x02000000)?1:0, 0, 1);
			}
			//MRS ( bit 21 clear )
			else {
				pBuf += sprintf(pBuf, "MRS%s",pConditionCode );
				pBuf = WritePadding( pBuf, pBuf0 );
				pBuf += sprintf(pBuf, "R%d,",(opcode>>12)&0x0f);
				pBuf += sprintf(pBuf, "%s",strpsr);
=======
			std::string strpsr = util::string_format("%s",(opcode&0x400000)?"SPSR":"CPSR");

			//MSR ( bit 21 set )
			if( (opcode&0x00200000) ) {
				util::stream_format(stream, "MSR%s",pConditionCode );
				//Flag Bits Only? (Bit 16 Clear)
				if( (opcode&0x10000)==0)    util::stream_format(stream, "F");
				WritePadding(stream, start_position);
				util::stream_format(stream, "%s,", strpsr);
				WriteDataProcessingOperand(stream, opcode, (opcode&0x02000000)?1:0, 0, 1);
			}
			//MRS ( bit 21 clear )
			else {
				util::stream_format(stream, "MRS%s", pConditionCode );
				WritePadding(stream, start_position);
				util::stream_format(stream, "R%d,", (opcode>>12)&0x0f);
				util::stream_format(stream, "%s", strpsr);
>>>>>>> upstream/master
			}
		}
		else {
			/* Data Processing */
			/* xxxx001a aaaSnnnn ddddrrrr bbbbbbbb */
			/* xxxx000a aaaSnnnn ddddcccc ctttmmmm */
			int op=(opcode>>21)&0xf;
<<<<<<< HEAD
			pBuf += sprintf(
				pBuf, "%s%s",
				pOperation[op],
				pConditionCode );
=======
			util::stream_format(
				stream, "%s%s",
				pOperation[op],
				pConditionCode);
>>>>>>> upstream/master

			//SJE: corrected S-Bit bug here
			//if( (opcode&0x01000000) )
			if( (opcode&0x0100000) )
			{
<<<<<<< HEAD
				*pBuf++ = 'S';
			}

			pBuf = WritePadding( pBuf, pBuf0 );
=======
				stream << 'S';
			}

			WritePadding(stream, start_position);
>>>>>>> upstream/master

			switch (op) {
			case 0x00:
			case 0x01:
			case 0x02:
			case 0x03:
			case 0x04:
			case 0x05:
			case 0x06:
			case 0x07:
			case 0x0c:
			case 0x0e:
<<<<<<< HEAD
				WriteDataProcessingOperand(pBuf, opcode, 1, 1, 1);
=======
				WriteDataProcessingOperand(stream, opcode, 1, 1, 1);
>>>>>>> upstream/master
				break;
			case 0x08:
			case 0x09:
			case 0x0a:
			case 0x0b:
<<<<<<< HEAD
				WriteDataProcessingOperand(pBuf, opcode, 0, 1, 1);
=======
				WriteDataProcessingOperand(stream, opcode, 0, 1, 1);
>>>>>>> upstream/master
				break;
			case 0x0d:
				/* look for mov pc,lr */
				if (((opcode >> 12) & 0x0f) == 15 && ((opcode >> 0) & 0x0f) == 14 && (opcode & 0x02000000) == 0)
					dasmflags = DASMFLAG_STEP_OUT;
			case 0x0f:
<<<<<<< HEAD
				WriteDataProcessingOperand(pBuf, opcode, 1, 0, 1);
=======
				WriteDataProcessingOperand(stream, opcode, 1, 0, 1);
>>>>>>> upstream/master
				break;
			}
		}
	}
	else if( (opcode&0x0c000000)==0x04000000 )      //bits 27-26 == 01
	{
<<<<<<< HEAD
		UINT32 rn = 0;
		UINT32 rnv = 0;
=======
		uint32_t rn;
		uint32_t rnv = 0;
>>>>>>> upstream/master

		/* Data Transfer */

		/* xxxx010P UBWLnnnn ddddoooo oooooooo  Immediate form */
		/* xxxx011P UBWLnnnn ddddcccc ctt0mmmm  Register form */
		if( opcode&0x00100000 )
		{
<<<<<<< HEAD
			pBuf += sprintf( pBuf, "LDR" );
		}
		else
		{
			pBuf += sprintf( pBuf, "STR" );
		}
		pBuf += sprintf( pBuf, "%s", pConditionCode );

		if( opcode&0x00400000 )
		{
			pBuf += sprintf( pBuf, "B" );
=======
			util::stream_format( stream, "LDR" );
		}
		else
		{
			util::stream_format( stream, "STR" );
		}
		util::stream_format( stream, "%s", pConditionCode );

		if( opcode&0x00400000 )
		{
			util::stream_format( stream, "B" );
>>>>>>> upstream/master
		}

		if( opcode&0x00200000 )
		{
			/* writeback addr */
			if( opcode&0x01000000 )
			{
				/* pre-indexed addressing */
<<<<<<< HEAD
				pBuf += sprintf( pBuf, "!" );
=======
				util::stream_format( stream, "!" );
>>>>>>> upstream/master
			}
			else
			{
				/* post-indexed addressing */
<<<<<<< HEAD
				pBuf += sprintf( pBuf, "T" );
			}
		}

		pBuf = WritePadding( pBuf, pBuf0 );
		pBuf += sprintf( pBuf, "R%d, [R%d",
=======
				util::stream_format( stream, "T" );
			}
		}

		WritePadding(stream, start_position);
		util::stream_format( stream, "R%d, [R%d",
>>>>>>> upstream/master
			(opcode>>12)&0xf, (opcode>>16)&0xf );

		//grab value of pc if used as base register
		rn = (opcode>>16)&0xf;
		if(rn==15) rnv = pc+8;

		if( opcode&0x02000000 )
		{
			/* register form */
<<<<<<< HEAD
			pBuf += sprintf( pBuf, "%s",(opcode&0x01000000)?"":"]" );
			pBuf = WriteRegisterOperand1( pBuf, opcode );
			pBuf += sprintf( pBuf, "%s",(opcode&0x01000000)?"]":"" );
=======
			util::stream_format( stream, "%s",(opcode&0x01000000)?"":"]" );
			WriteRegisterOperand1(stream, opcode);
			util::stream_format( stream, "%s",(opcode&0x01000000)?"]":"" );
>>>>>>> upstream/master
		}
		else
		{
			/* immediate form */
<<<<<<< HEAD
			pBuf += sprintf( pBuf, "%s",(opcode&0x01000000)?"":"]" );
=======
			util::stream_format( stream, "%s",(opcode&0x01000000)?"":"]" );
>>>>>>> upstream/master
			//hide zero offsets
			if(opcode&0xfff) {
				if( opcode&0x00800000 )
				{
<<<<<<< HEAD
					pBuf += sprintf( pBuf, ", #$%x", opcode&0xfff );
=======
					util::stream_format( stream, ", #$%x", opcode&0xfff );
>>>>>>> upstream/master
					rnv += (rnv)?opcode&0xfff:0;
				}
				else
				{
<<<<<<< HEAD
					pBuf += sprintf( pBuf, ", -#$%x", opcode&0xfff );
					rnv -= (rnv)?opcode&0xfff:0;
				}
			}
			pBuf += sprintf( pBuf, "%s",(opcode&0x01000000)?"]":"" );
			//show where the read will occur if we found a value
			if(rnv) pBuf += sprintf( pBuf, " (%x)",rnv);
=======
					util::stream_format( stream, ", -#$%x", opcode&0xfff );
					rnv -= (rnv)?opcode&0xfff:0;
				}
			}
			util::stream_format( stream, "%s",(opcode&0x01000000)?"]":"" );
			//show where the read will occur if we found a value
			if(rnv) util::stream_format( stream, " (%x)",rnv);
>>>>>>> upstream/master
		}
	}
	else if( (opcode&0x0e000000) == 0x08000000 )        //bits 27-25 == 100
	{
		/* xxxx100P USWLnnnn llllllll llllllll */
		/* Block Data Transfer */

		if( opcode&0x00100000 )
		{
<<<<<<< HEAD
			pBuf += sprintf( pBuf, "LDM" );
		}
		else
		{
			pBuf += sprintf( pBuf, "STM" );
		}
		pBuf += sprintf( pBuf, "%s", pConditionCode );

		if( opcode&0x01000000 )
		{
			pBuf += sprintf( pBuf, "P" );
		}
		if( opcode&0x00800000 )
		{
			pBuf += sprintf( pBuf, "U" );
		}
		if( opcode&0x00400000 )
		{
			pBuf += sprintf( pBuf, "^" );
		}
		if( opcode&0x00200000 )
		{
			pBuf += sprintf( pBuf, "W" );
		}

		pBuf = WritePadding( pBuf, pBuf0 );
		pBuf += sprintf( pBuf, "[R%d], {",(opcode>>16)&0xf);
=======
			util::stream_format( stream, "LDM" );
		}
		else
		{
			util::stream_format( stream, "STM" );
		}
		util::stream_format( stream, "%s", pConditionCode );

		if( opcode&0x01000000 )
		{
			util::stream_format( stream, "P" );
		}
		if( opcode&0x00800000 )
		{
			util::stream_format( stream, "U" );
		}
		if( opcode&0x00400000 )
		{
			util::stream_format( stream, "^" );
		}
		if( opcode&0x00200000 )
		{
			util::stream_format( stream, "W" );
		}

		WritePadding(stream, start_position);
		util::stream_format(stream, "[R%d], {",(opcode>>16)&0xf);
>>>>>>> upstream/master

		{
			int j=0,last=0,found=0;
			for (j=0; j<16; j++) {
				if (opcode&(1<<j) && found==0) {
					found=1;
					last=j;
				}
				else if ((opcode&(1<<j))==0 && found) {
					if (last==j-1)
<<<<<<< HEAD
						pBuf += sprintf( pBuf, " R%d,",last);
					else
						pBuf += sprintf( pBuf, " R%d-R%d,",last,j-1);
=======
						util::stream_format(stream, " R%d,",last);
					else
						util::stream_format(stream, " R%d-R%d,",last,j-1);
>>>>>>> upstream/master
					found=0;
				}
			}
			if (found && last==15)
<<<<<<< HEAD
				pBuf += sprintf( pBuf, " R15,");
			else if (found)
				pBuf += sprintf( pBuf, " R%d-R%d,",last,15);
		}

		pBuf--;
		pBuf += sprintf( pBuf, " }");
=======
				util::stream_format(stream, " R15,");
			else if (found)
				util::stream_format(stream, " R%d-R%d,",last,15);
		}

		stream.seekp(-1, std::ios::cur);
		util::stream_format(stream, " }");
>>>>>>> upstream/master
	}
	else if( (opcode&0x0e000000)==0x0a000000 )      //bits 27-25 == 101
	{
		/* branch instruction */
		/* xxxx101L oooooooo oooooooo oooooooo */
		if( opcode&0x01000000 )
		{
<<<<<<< HEAD
			pBuf += sprintf( pBuf, "BL" );
=======
			util::stream_format( stream, "BL" );
>>>>>>> upstream/master
			dasmflags = DASMFLAG_STEP_OVER;
		}
		else
		{
<<<<<<< HEAD
			pBuf += sprintf( pBuf, "B" );
		}

		pBuf += sprintf( pBuf, "%s", pConditionCode );

		pBuf = WritePadding( pBuf, pBuf0 );

		pBuf = WriteBranchAddress( pBuf, pc, opcode );
=======
			util::stream_format( stream, "B" );
		}

		util::stream_format( stream, "%s", pConditionCode );

		WritePadding(stream, start_position);

		WriteBranchAddress( stream, pc, opcode, false );
>>>>>>> upstream/master
	}
	else if( (opcode&0x0e000000)==0x0c000000 )      //bits 27-25 == 110
	{
		/* co processor data transfer */
<<<<<<< HEAD
		DasmCoProc_DT(pBuf,opcode,(char*)pConditionCode,(char*)pBuf0);
=======
		DasmCoProc_DT(stream, opcode, (char*)pConditionCode, start_position);
>>>>>>> upstream/master
	}
	else if( (opcode&0x0f000000)==0x0e000000 )      //bits 27-24 == 1110
	{
		/* co processor data operation or register transfer */

		//Register Transfer
		if(opcode&0x10)
		{
<<<<<<< HEAD
			DasmCoProc_RT(pBuf,opcode,pConditionCode,pBuf0);
=======
			DasmCoProc_RT(stream, opcode, pConditionCode, start_position);
>>>>>>> upstream/master
		}
		//Data Op
		else
		{
<<<<<<< HEAD
			DasmCoProc_DO(pBuf,opcode,pConditionCode,pBuf0);
=======
			DasmCoProc_DO(stream, opcode, pConditionCode, start_position);
>>>>>>> upstream/master
		}
	}
	else if( (opcode&0x0f000000) == 0x0f000000 )    //bits 27-24 == 1111
	{
		/* Software Interrupt */
<<<<<<< HEAD
		pBuf += sprintf( pBuf, "SWI%s $%x",
=======
		util::stream_format( stream, "SWI%s $%x",
>>>>>>> upstream/master
			pConditionCode,
			opcode&0x00ffffff );
		dasmflags = DASMFLAG_STEP_OVER;
	}
	else
	{
<<<<<<< HEAD
		pBuf += sprintf( pBuf, "Undefined" );
=======
		util::stream_format( stream, "Undefined" );
>>>>>>> upstream/master
	}
	return dasmflags | DASMFLAG_SUPPORTED;
}

<<<<<<< HEAD
static UINT32 thumb_disasm( char *pBuf, UINT32 pc, UINT16 opcode )
{
	const char *pBuf0;
	UINT32 dasmflags = 0;

//      UINT32 readword;
		UINT32 addr;
		UINT32 rm, rn, rs, rd, op2, imm;//, rrs;
		INT32 offs;

	pBuf0 = pBuf;
	pBuf = WritePadding( pBuf, pBuf0 );
=======
static uint32_t thumb_disasm(std::ostream &stream, uint32_t pc, uint16_t opcode)
{
	std::streampos start_position = stream.tellp();
	uint32_t dasmflags = 0;

//      uint32_t readword;
		uint32_t addr;
		uint32_t rm, rn, rs, rd, op2, imm;//, rrs;
		int32_t offs;

	WritePadding(stream, start_position);
>>>>>>> upstream/master


		switch( ( opcode & THUMB_INSN_TYPE ) >> THUMB_INSN_TYPE_SHIFT )
		{
			case 0x0: /* Logical shifting */
				if( opcode & THUMB_SHIFT_R ) /* Shift right */
				{
					rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
					rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
					offs = ( opcode & THUMB_SHIFT_AMT ) >> THUMB_SHIFT_AMT_SHIFT;
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "LSR R%d, R%d, %d", rd, rs, offs);
=======
					util::stream_format( stream, "LSR R%d, R%d, %d", rd, rs, offs);
>>>>>>> upstream/master
				}
				else /* Shift left */
				{
					rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
					rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
					offs = ( opcode & THUMB_SHIFT_AMT ) >> THUMB_SHIFT_AMT_SHIFT;
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "LSL R%d, R%d, %d", rd, rs, offs);
=======
					util::stream_format( stream, "LSL R%d, R%d, %d", rd, rs, offs);
>>>>>>> upstream/master
				}
				break;
			case 0x1: /* Arithmetic */
				if( opcode & THUMB_INSN_ADDSUB )
				{
					switch( ( opcode & THUMB_ADDSUB_TYPE ) >> THUMB_ADDSUB_TYPE_SHIFT )
					{
						case 0x0: /* ADD Rd, Rs, Rn */
							rn = ( opcode & THUMB_ADDSUB_RNIMM ) >> THUMB_ADDSUB_RNIMM_SHIFT;
							rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
							rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
							pBuf += sprintf( pBuf, "ADD R%d, R%d, R%d", rd, rs, rn );
=======
							util::stream_format( stream, "ADD R%d, R%d, R%d", rd, rs, rn );
>>>>>>> upstream/master
							break;
						case 0x1: /* SUB Rd, Rs, Rn */
							rn = ( opcode & THUMB_ADDSUB_RNIMM ) >> THUMB_ADDSUB_RNIMM_SHIFT;
							rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
							rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
							pBuf += sprintf( pBuf, "SUB R%d, R%d, R%d", rd, rs, rn );
=======
							util::stream_format( stream, "SUB R%d, R%d, R%d", rd, rs, rn );
>>>>>>> upstream/master
							break;
						case 0x2: /* ADD Rd, Rs, #imm */
							imm = ( opcode & THUMB_ADDSUB_RNIMM ) >> THUMB_ADDSUB_RNIMM_SHIFT;
							rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
							rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
							pBuf += sprintf( pBuf, "ADD R%d, R%d, #%d", rd, rs, imm );
=======
							util::stream_format( stream, "ADD R%d, R%d, #%d", rd, rs, imm );
>>>>>>> upstream/master
							break;
						case 0x3: /* SUB Rd, Rs, #imm */
							imm = ( opcode & THUMB_ADDSUB_RNIMM ) >> THUMB_ADDSUB_RNIMM_SHIFT;
							rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
							rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
							pBuf += sprintf( pBuf, "SUB R%d, R%d, #%d", rd, rs, imm );
							break;
						default:
							sprintf( pBuf, "INVALID %04x", opcode);
=======
							util::stream_format( stream, "SUB R%d, R%d, #%d", rd, rs, imm );
							break;
						default:
							util::stream_format(stream, "INVALID %04x", opcode);
>>>>>>> upstream/master
							break;
					}
				}
				else
				{
					rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
					rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
					offs = ( opcode & THUMB_SHIFT_AMT ) >> THUMB_SHIFT_AMT_SHIFT;
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "ASR R%d, R%d, %d", rd, rs, offs);
=======
					util::stream_format( stream, "ASR R%d, R%d, %d", rd, rs, offs);
>>>>>>> upstream/master
				}
				break;
			case 0x2: /* CMP / MOV */
				if( opcode & THUMB_INSN_CMP )
				{
					rn = ( opcode & THUMB_INSN_IMM_RD ) >> THUMB_INSN_IMM_RD_SHIFT;
					op2 = ( opcode & THUMB_INSN_IMM );
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "CMP R%d, %02x", rn, op2 );
=======
					util::stream_format( stream, "CMP R%d, %02x", rn, op2 );
>>>>>>> upstream/master
				}
				else
				{
					rd = ( opcode & THUMB_INSN_IMM_RD ) >> THUMB_INSN_IMM_RD_SHIFT;
					op2 = ( opcode & THUMB_INSN_IMM );
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "MOV R%d, %02x", rd, op2 );
=======
					util::stream_format( stream, "MOV R%d, %02x", rd, op2 );
>>>>>>> upstream/master
				}
				break;
			case 0x3: /* ADD/SUB immediate */
				if( opcode & THUMB_INSN_SUB ) /* SUB Rd, #Offset8 */
				{
					rn = ( opcode & THUMB_INSN_IMM_RD ) >> THUMB_INSN_IMM_RD_SHIFT;
					op2 = ( opcode & THUMB_INSN_IMM );
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "SUB R%d, %02x", rn, op2 ); // fixed, rd -> rn
=======
					util::stream_format( stream, "SUB R%d, %02x", rn, op2 ); // fixed, rd -> rn
>>>>>>> upstream/master
				}
				else /* ADD Rd, #Offset8 */
				{
					rn = ( opcode & THUMB_INSN_IMM_RD ) >> THUMB_INSN_IMM_RD_SHIFT;
					op2 = opcode & THUMB_INSN_IMM;
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "ADD R%d, %02x", rn, op2 );
=======
					util::stream_format( stream, "ADD R%d, %02x", rn, op2 );
>>>>>>> upstream/master
				}
				break;
			case 0x4: /* Rd & Rm instructions */
				switch( ( opcode & THUMB_GROUP4_TYPE ) >> THUMB_GROUP4_TYPE_SHIFT )
				{
					case 0x0:
						switch( ( opcode & THUMB_ALUOP_TYPE ) >> THUMB_ALUOP_TYPE_SHIFT )
						{
							case 0x0: /* AND Rd, Rs */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "AND R%d, R%d", rd, rs );
=======
								util::stream_format( stream, "AND R%d, R%d", rd, rs );
>>>>>>> upstream/master
								break;
							case 0x1: /* EOR Rd, Rs */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "EOR R%d, R%d", rd, rs );
=======
								util::stream_format( stream, "EOR R%d, R%d", rd, rs );
>>>>>>> upstream/master
								break;
							case 0x2: /* LSL Rd, Rs */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "LSL R%d, R%d", rd, rs );
=======
								util::stream_format( stream, "LSL R%d, R%d", rd, rs );
>>>>>>> upstream/master
								break;
							case 0x3: /* LSR Rd, Rs */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "LSR R%d, R%d", rd, rs );
=======
								util::stream_format( stream, "LSR R%d, R%d", rd, rs );
>>>>>>> upstream/master
								break;
							case 0x4: /* ASR Rd, Rs */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "ASR R%d, R%d", rd, rs );
=======
								util::stream_format( stream, "ASR R%d, R%d", rd, rs );
>>>>>>> upstream/master
								break;
							case 0x5: /* ADC Rd, Rs */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "ADC R%d, R%d", rd, rs );
=======
								util::stream_format( stream, "ADC R%d, R%d", rd, rs );
>>>>>>> upstream/master
								break;
							case 0x6: /* SBC Rd, Rs */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "SBC R%d, R%d", rd, rs );
=======
								util::stream_format( stream, "SBC R%d, R%d", rd, rs );
>>>>>>> upstream/master
								break;
							case 0x7: /* ROR Rd, Rs */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "ROR R%d, R%d", rd, rs );
=======
								util::stream_format( stream, "ROR R%d, R%d", rd, rs );
>>>>>>> upstream/master
								break;
							case 0x8: /* TST Rd, Rs */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "TST R%d, R%d", rd, rs );
=======
								util::stream_format( stream, "TST R%d, R%d", rd, rs );
>>>>>>> upstream/master
								break;
							case 0x9: /* NEG Rd, Rs */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "NEG R%d, R%d", rd, rs );
=======
								util::stream_format( stream, "NEG R%d, R%d", rd, rs );
>>>>>>> upstream/master
								break;
							case 0xa: /* CMP Rd, Rs */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "CMP R%d, R%d", rd, rs );
=======
								util::stream_format( stream, "CMP R%d, R%d", rd, rs );
>>>>>>> upstream/master
								break;
							case 0xb: /* CMN Rd, Rs - check flags, add dasm */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "CMN R%d, R%d", rd, rs );
=======
								util::stream_format( stream, "CMN R%d, R%d", rd, rs );
>>>>>>> upstream/master
								break;
							case 0xc: /* ORR Rd, Rs */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "ORR R%d, R%d", rd, rs );
=======
								util::stream_format( stream, "ORR R%d, R%d", rd, rs );
>>>>>>> upstream/master
								break;
							case 0xd: /* MUL Rd, Rs */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "MUL R%d, R%d", rd, rs );
=======
								util::stream_format( stream, "MUL R%d, R%d", rd, rs );
>>>>>>> upstream/master
								break;
							case 0xe: /* MUL Rd, Rs */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "BIC R%d, R%d", rd, rs );
=======
								util::stream_format( stream, "BIC R%d, R%d", rd, rs );
>>>>>>> upstream/master
								break;
							case 0xf: /* MVN Rd, Rs */
								rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
								rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "MVN R%d, R%d", rd, rs );
								break;
							default:
								sprintf( pBuf, "INVALID %04x", opcode);
=======
								util::stream_format( stream, "MVN R%d, R%d", rd, rs );
								break;
							default:
								util::stream_format(stream, "INVALID %04x", opcode);
>>>>>>> upstream/master
								break;
						}
						break;
					case 0x1:
						switch( ( opcode & THUMB_HIREG_OP ) >> THUMB_HIREG_OP_SHIFT )
						{
							case 0x0: /* ADD Rd, Rs */
								rs = ( opcode & THUMB_HIREG_RS ) >> THUMB_HIREG_RS_SHIFT;
								rd = opcode & THUMB_HIREG_RD;
								switch( ( opcode & THUMB_HIREG_H ) >> THUMB_HIREG_H_SHIFT )
								{
									case 0x1: /* ADD Rd, HRs */
<<<<<<< HEAD
										pBuf += sprintf( pBuf, "ADD R%d, R%d", rd, rs + 8 );
										break;
									case 0x2: /* ADD HRd, Rs */
										pBuf += sprintf( pBuf, "ADD R%d, R%d", rd + 8, rs );
										break;
									case 0x3: /* ADD HRd, HRs */
										pBuf += sprintf( pBuf, "ADD R%d, R%d", rd + 8, rs + 8 );
										break;
									default:
										sprintf( pBuf, "INVALID %04x", opcode);
=======
										util::stream_format( stream, "ADD R%d, R%d", rd, rs + 8 );
										break;
									case 0x2: /* ADD HRd, Rs */
										util::stream_format( stream, "ADD R%d, R%d", rd + 8, rs );
										break;
									case 0x3: /* ADD HRd, HRs */
										util::stream_format( stream, "ADD R%d, R%d", rd + 8, rs + 8 );
										break;
									default:
										util::stream_format(stream, "INVALID %04x", opcode);
>>>>>>> upstream/master
										break;
								}
								break;
							case 0x1: /* CMP */
								switch( ( opcode & THUMB_HIREG_H ) >> THUMB_HIREG_H_SHIFT )
								{
									case 0x0: /* CMP Rd, Rs */
										rs = ( opcode & THUMB_HIREG_RS ) >> THUMB_HIREG_RS_SHIFT;
										rd = opcode & THUMB_HIREG_RD;
<<<<<<< HEAD
										pBuf += sprintf( pBuf, "CMP R%d, R%d", rd, rs );
=======
										util::stream_format( stream, "CMP R%d, R%d", rd, rs );
>>>>>>> upstream/master
										break;
									case 0x1: /* CMP Rd, HRs */
										rs = ( opcode & THUMB_HIREG_RS ) >> THUMB_HIREG_RS_SHIFT;
										rd = opcode & THUMB_HIREG_RD;
<<<<<<< HEAD
										pBuf += sprintf( pBuf, "CMP R%d, R%d", rd, rs + 8 );
=======
										util::stream_format( stream, "CMP R%d, R%d", rd, rs + 8 );
>>>>>>> upstream/master
										break;
									case 0x2: /* CMP Hd, Rs */
										rs = ( opcode & THUMB_HIREG_RS ) >> THUMB_HIREG_RS_SHIFT;
										rd = opcode & THUMB_HIREG_RD;
<<<<<<< HEAD
										pBuf += sprintf( pBuf, "CMP R%d, R%d", rd + 8, rs );
=======
										util::stream_format( stream, "CMP R%d, R%d", rd + 8, rs );
>>>>>>> upstream/master
										break;
									case 0x3: /* CMP Hd, Hs */
										rs = ( opcode & THUMB_HIREG_RS ) >> THUMB_HIREG_RS_SHIFT;
										rd = opcode & THUMB_HIREG_RD;
<<<<<<< HEAD
										pBuf += sprintf( pBuf, "CMP R%d, R%d", rd + 8, rs + 8 );
										break;
									default:
										sprintf( pBuf, "INVALID %04x", opcode);
=======
										util::stream_format( stream, "CMP R%d, R%d", rd + 8, rs + 8 );
										break;
									default:
										util::stream_format(stream, "INVALID %04x", opcode);
>>>>>>> upstream/master
										break;
								}
								break;
							case 0x2: /* MOV */
								switch( ( opcode & THUMB_HIREG_H ) >> THUMB_HIREG_H_SHIFT )
								{
									case 0x0:
										rs = ( opcode & THUMB_HIREG_RS ) >> THUMB_HIREG_RS_SHIFT;
										rd = opcode & THUMB_HIREG_RD;
<<<<<<< HEAD
										pBuf += sprintf( pBuf, "MOV R%d, R%d", rd, rs );
=======
										util::stream_format( stream, "MOV R%d, R%d", rd, rs );
>>>>>>> upstream/master
										break;
									case 0x1:
										rs = ( opcode & THUMB_HIREG_RS ) >> THUMB_HIREG_RS_SHIFT;
										rd = opcode & THUMB_HIREG_RD;
<<<<<<< HEAD
										pBuf += sprintf( pBuf, "MOV R%d, R%d", rd, rs + 8 );
=======
										util::stream_format( stream, "MOV R%d, R%d", rd, rs + 8 );
>>>>>>> upstream/master
										break;
									case 0x2:
										rs = ( opcode & THUMB_HIREG_RS ) >> THUMB_HIREG_RS_SHIFT;
										rd = opcode & THUMB_HIREG_RD;
<<<<<<< HEAD
										pBuf += sprintf( pBuf, "MOV R%d, R%d", rd + 8, rs );
=======
										util::stream_format( stream, "MOV R%d, R%d", rd + 8, rs );
>>>>>>> upstream/master
										break;
									case 0x3:
										rs = ( opcode & THUMB_HIREG_RS ) >> THUMB_HIREG_RS_SHIFT;
										rd = opcode & THUMB_HIREG_RD;
<<<<<<< HEAD
										pBuf += sprintf( pBuf, "MOV R%d, R%d", rd + 8, rs + 8 );
										break;
									default:
										sprintf( pBuf, "INVALID %04x", opcode);
=======
										util::stream_format( stream, "MOV R%d, R%d", rd + 8, rs + 8 );
										break;
									default:
										util::stream_format(stream, "INVALID %04x", opcode);
>>>>>>> upstream/master
										break;
								}
								break;
							case 0x3:
								switch( ( opcode & THUMB_HIREG_H ) >> THUMB_HIREG_H_SHIFT )
								{
									case 0x0:
										rd = ( opcode & THUMB_HIREG_RS ) >> THUMB_HIREG_RS_SHIFT;
<<<<<<< HEAD
										pBuf += sprintf( pBuf, "BX R%d", rd );
										break;
									case 0x1:
										rd = ( ( opcode & THUMB_HIREG_RS ) >> THUMB_HIREG_RS_SHIFT ) + 8;
										pBuf += sprintf( pBuf, "BX R%d", rd );
=======
										util::stream_format( stream, "BX R%d", rd );
										break;
									case 0x1:
										rd = ( ( opcode & THUMB_HIREG_RS ) >> THUMB_HIREG_RS_SHIFT ) + 8;
										util::stream_format( stream, "BX R%d", rd );
>>>>>>> upstream/master
										if (rd == 14)
											dasmflags = DASMFLAG_STEP_OUT;
										break;
									case 0x2:
										rd = ( opcode & THUMB_HIREG_RS ) >> THUMB_HIREG_RS_SHIFT;
<<<<<<< HEAD
										pBuf += sprintf( pBuf, "BLX R%d", rd );
										break;
									default:
										sprintf( pBuf, "INVALID %04x", opcode);
=======
										util::stream_format( stream, "BLX R%d", rd );
										break;
									default:
										util::stream_format(stream, "INVALID %04x", opcode);
>>>>>>> upstream/master
										break;
								}
								break;
							default:
<<<<<<< HEAD
								sprintf( pBuf, "INVALID %04x", opcode);
=======
								util::stream_format(stream, "INVALID %04x", opcode);
>>>>>>> upstream/master
								break;
						}
						break;
					case 0x2:
					case 0x3:
						rd = ( opcode & THUMB_INSN_IMM_RD ) >> THUMB_INSN_IMM_RD_SHIFT;
						addr = ( opcode & THUMB_INSN_IMM ) << 2;
<<<<<<< HEAD
						pBuf += sprintf( pBuf, "LDR R%d, [PC, #%03x]", rd, addr );
						break;
					default:
						sprintf( pBuf, "INVALID %04x", opcode);
=======
						util::stream_format( stream, "LDR R%d, [PC, #%03x]", rd, addr );
						break;
					default:
						util::stream_format(stream, "INVALID %04x", opcode);
>>>>>>> upstream/master
						break;
				}
				break;
			case 0x5: /* LDR* STR* */
				switch( ( opcode & THUMB_GROUP5_TYPE ) >> THUMB_GROUP5_TYPE_SHIFT )
				{
					case 0x0: /* STR Rd, [Rn, Rm] */
						rm = ( opcode & THUMB_GROUP5_RM ) >> THUMB_GROUP5_RM_SHIFT;
						rn = ( opcode & THUMB_GROUP5_RN ) >> THUMB_GROUP5_RN_SHIFT;
						rd = ( opcode & THUMB_GROUP5_RD ) >> THUMB_GROUP5_RD_SHIFT;
<<<<<<< HEAD
						pBuf += sprintf( pBuf, "STR R%d, [R%d, R%d]", rd, rn, rm );
=======
						util::stream_format( stream, "STR R%d, [R%d, R%d]", rd, rn, rm );
>>>>>>> upstream/master
						break;
					case 0x1: /* STRH Rd, [Rn, Rm] */
						rm = ( opcode & THUMB_GROUP5_RM ) >> THUMB_GROUP5_RM_SHIFT;
						rn = ( opcode & THUMB_GROUP5_RN ) >> THUMB_GROUP5_RN_SHIFT;
						rd = ( opcode & THUMB_GROUP5_RD ) >> THUMB_GROUP5_RD_SHIFT;
<<<<<<< HEAD
						pBuf += sprintf( pBuf, "STRH R%d, [R%d, R%d]", rd, rn, rm );
=======
						util::stream_format( stream, "STRH R%d, [R%d, R%d]", rd, rn, rm );
>>>>>>> upstream/master
						break;
					case 0x2: /* STRB Rd, [Rn, Rm] */ /* check */
						rm = ( opcode & THUMB_GROUP5_RM ) >> THUMB_GROUP5_RM_SHIFT;
						rn = ( opcode & THUMB_GROUP5_RN ) >> THUMB_GROUP5_RN_SHIFT;
						rd = ( opcode & THUMB_GROUP5_RD ) >> THUMB_GROUP5_RD_SHIFT;
<<<<<<< HEAD
						pBuf += sprintf( pBuf, "STRB R%d, [R%d, R%d]", rd, rn, rm );
=======
						util::stream_format( stream, "STRB R%d, [R%d, R%d]", rd, rn, rm );
>>>>>>> upstream/master
						break;
					case 0x3: /* LDRSB Rd, [Rn, Rm] */
						rm = ( opcode & THUMB_GROUP5_RM ) >> THUMB_GROUP5_RM_SHIFT;
						rn = ( opcode & THUMB_GROUP5_RN ) >> THUMB_GROUP5_RN_SHIFT;
						rd = ( opcode & THUMB_GROUP5_RD ) >> THUMB_GROUP5_RD_SHIFT;
<<<<<<< HEAD
						pBuf += sprintf( pBuf, "LDRSB R%d, [R%d, R%d]", rd, rn, rm );
=======
						util::stream_format( stream, "LDRSB R%d, [R%d, R%d]", rd, rn, rm );
>>>>>>> upstream/master
						break;
					case 0x4: /* LDR Rd, [Rn, Rm] */ /* check */
						rm = ( opcode & THUMB_GROUP5_RM ) >> THUMB_GROUP5_RM_SHIFT;
						rn = ( opcode & THUMB_GROUP5_RN ) >> THUMB_GROUP5_RN_SHIFT;
						rd = ( opcode & THUMB_GROUP5_RD ) >> THUMB_GROUP5_RD_SHIFT;
<<<<<<< HEAD
						pBuf += sprintf( pBuf, "LDR R%d, [R%d, R%d]", rd, rn, rm );
=======
						util::stream_format( stream, "LDR R%d, [R%d, R%d]", rd, rn, rm );
>>>>>>> upstream/master
						break;
					case 0x5: /* LDRH Rd, [Rn, Rm] */
						rm = ( opcode & THUMB_GROUP5_RM ) >> THUMB_GROUP5_RM_SHIFT;
						rn = ( opcode & THUMB_GROUP5_RN ) >> THUMB_GROUP5_RN_SHIFT;
						rd = ( opcode & THUMB_GROUP5_RD ) >> THUMB_GROUP5_RD_SHIFT;
<<<<<<< HEAD
						pBuf += sprintf( pBuf, "LDRH R%d, [R%d, R%d]", rd, rn, rm );
=======
						util::stream_format( stream, "LDRH R%d, [R%d, R%d]", rd, rn, rm );
>>>>>>> upstream/master
						break;

					case 0x6: /* LDRB Rd, [Rn, Rm] */
						rm = ( opcode & THUMB_GROUP5_RM ) >> THUMB_GROUP5_RM_SHIFT;
						rn = ( opcode & THUMB_GROUP5_RN ) >> THUMB_GROUP5_RN_SHIFT;
						rd = ( opcode & THUMB_GROUP5_RD ) >> THUMB_GROUP5_RD_SHIFT;
<<<<<<< HEAD
						pBuf += sprintf( pBuf, "LDRB R%d, [R%d, R%d]", rd, rn, rm );
=======
						util::stream_format( stream, "LDRB R%d, [R%d, R%d]", rd, rn, rm );
>>>>>>> upstream/master
						break;
					case 0x7: /* LDSH Rd, [Rn, Rm] */
						rm = ( opcode & THUMB_GROUP5_RM ) >> THUMB_GROUP5_RM_SHIFT;
						rn = ( opcode & THUMB_GROUP5_RN ) >> THUMB_GROUP5_RN_SHIFT;
						rd = ( opcode & THUMB_GROUP5_RD ) >> THUMB_GROUP5_RD_SHIFT;
<<<<<<< HEAD
						pBuf += sprintf( pBuf, "LDSH R%d, [R%d, R%d]", rd, rn, rm );
						break;
					default:
						sprintf( pBuf, "INVALID %04x", opcode);
=======
						util::stream_format( stream, "LDSH R%d, [R%d, R%d]", rd, rn, rm );
						break;
					default:
						util::stream_format(stream, "INVALID %04x", opcode);
>>>>>>> upstream/master
						break;
				}
				break;
			case 0x6: /* Word Store w/ Immediate Offset */
				if( opcode & THUMB_LSOP_L ) /* Load */
				{
					rn = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
					rd = opcode & THUMB_ADDSUB_RD;
					offs = ( ( opcode & THUMB_LSOP_OFFS ) >> THUMB_LSOP_OFFS_SHIFT ) << 2;
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "LDR R%d [R%d + #%02x]", rd, rn, offs );
=======
					util::stream_format( stream, "LDR R%d [R%d + #%02x]", rd, rn, offs );
>>>>>>> upstream/master
				}
				else /* Store */
				{
					rn = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
					rd = opcode & THUMB_ADDSUB_RD;
					offs = ( ( opcode & THUMB_LSOP_OFFS ) >> THUMB_LSOP_OFFS_SHIFT ) << 2;
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "STR R%d, [R%d + #%02x] ", rd, rn, offs );
=======
					util::stream_format( stream, "STR R%d, [R%d + #%02x] ", rd, rn, offs );
>>>>>>> upstream/master
				}
				break;
			case 0x7: /* Byte Store w/ Immeidate Offset */
				if( opcode & THUMB_LSOP_L ) /* Load */
				{
					rn = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
					rd = opcode & THUMB_ADDSUB_RD;
					offs = ( opcode & THUMB_LSOP_OFFS ) >> THUMB_LSOP_OFFS_SHIFT;
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "LDRB R%d, [R%d + #%02x]", rd, rn, offs );
=======
					util::stream_format( stream, "LDRB R%d, [R%d + #%02x]", rd, rn, offs );
>>>>>>> upstream/master
				}
				else /* Store */
				{
					rn = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
					rd = opcode & THUMB_ADDSUB_RD;
					offs = ( opcode & THUMB_LSOP_OFFS ) >> THUMB_LSOP_OFFS_SHIFT;
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "STRB R%d, [R%d + #%02x] ", rd, rn, offs );
=======
					util::stream_format( stream, "STRB R%d, [R%d + #%02x] ", rd, rn, offs );
>>>>>>> upstream/master
				}
				break;
			case 0x8: /* Load/Store Halfword */
				if( opcode & THUMB_HALFOP_L ) /* Load */
				{
					imm = ( opcode & THUMB_HALFOP_OFFS ) >> THUMB_HALFOP_OFFS_SHIFT;
					rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
					rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "LDRH R%d, [R%d, #%03x]", rd, rs, imm << 1 );
=======
					util::stream_format( stream, "LDRH R%d, [R%d, #%03x]", rd, rs, imm << 1 );
>>>>>>> upstream/master
				}
				else /* Store */
				{
					imm = ( opcode & THUMB_HALFOP_OFFS ) >> THUMB_HALFOP_OFFS_SHIFT;
					rs = ( opcode & THUMB_ADDSUB_RS ) >> THUMB_ADDSUB_RS_SHIFT;
					rd = ( opcode & THUMB_ADDSUB_RD ) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "STRH R%d, [R%d, #%03x]", rd, rs, imm << 1 );
=======
					util::stream_format( stream, "STRH R%d, [R%d, #%03x]", rd, rs, imm << 1 );
>>>>>>> upstream/master
				}
				break;
			case 0x9: /* Stack-Relative Load/Store */
				if( opcode & THUMB_STACKOP_L )
				{
					rd = ( opcode & THUMB_STACKOP_RD ) >> THUMB_STACKOP_RD_SHIFT;
<<<<<<< HEAD
					offs = (UINT8)( opcode & THUMB_INSN_IMM );
					pBuf += sprintf( pBuf, "LDR R%d, [SP, #%03x]", rd, offs << 2 );
=======
					offs = (uint8_t)( opcode & THUMB_INSN_IMM );
					util::stream_format( stream, "LDR R%d, [SP, #%03x]", rd, offs << 2 );
>>>>>>> upstream/master
				}
				else
				{
					rd = ( opcode & THUMB_STACKOP_RD ) >> THUMB_STACKOP_RD_SHIFT;
<<<<<<< HEAD
					offs = (UINT8)( opcode & THUMB_INSN_IMM );
					pBuf += sprintf( pBuf, "STR R%d, [SP, #%03x]", rd, offs << 2 );
=======
					offs = (uint8_t)( opcode & THUMB_INSN_IMM );
					util::stream_format( stream, "STR R%d, [SP, #%03x]", rd, offs << 2 );
>>>>>>> upstream/master
				}
				break;
			case 0xa: /* Get relative address */
				if( opcode & THUMB_RELADDR_SP ) /* ADD Rd, SP, #nn */
				{
					rd = ( opcode & THUMB_RELADDR_RD ) >> THUMB_RELADDR_RD_SHIFT;
<<<<<<< HEAD
					offs = (UINT8)( opcode & THUMB_INSN_IMM ) << 2;
					pBuf += sprintf( pBuf, "ADD R%d, SP, #%03x", rd, offs );
=======
					offs = (uint8_t)( opcode & THUMB_INSN_IMM ) << 2;
					util::stream_format( stream, "ADD R%d, SP, #%03x", rd, offs );
>>>>>>> upstream/master
				}
				else /* ADD Rd, PC, #nn */
				{
					rd = ( opcode & THUMB_RELADDR_RD ) >> THUMB_RELADDR_RD_SHIFT;
<<<<<<< HEAD
					offs = (UINT8)( opcode & THUMB_INSN_IMM ) << 2;
					pBuf += sprintf( pBuf, "ADD R%d, PC, #%03x", rd, offs );
=======
					offs = (uint8_t)( opcode & THUMB_INSN_IMM ) << 2;
					util::stream_format( stream, "ADD R%d, PC, #%03x", rd, offs );
>>>>>>> upstream/master
				}
				break;
			case 0xb: /* Stack-Related Opcodes */
				switch( ( opcode & THUMB_STACKOP_TYPE ) >> THUMB_STACKOP_TYPE_SHIFT )
				{
					case 0x0: /* ADD SP, #imm */
						addr = ( opcode & THUMB_INSN_IMM );
						addr &= ~THUMB_INSN_IMM_S;
<<<<<<< HEAD
						pBuf += sprintf( pBuf, "ADD SP, #");
						if( opcode & THUMB_INSN_IMM_S )
						{
							pBuf += sprintf( pBuf, "-");
						}
						pBuf += sprintf( pBuf, "%03x", addr << 2);
						break;
					case 0x5: /* PUSH {Rlist}{LR} */
						pBuf += sprintf( pBuf, "PUSH {LR, ");
=======
						util::stream_format( stream, "ADD SP, #");
						if( opcode & THUMB_INSN_IMM_S )
						{
							util::stream_format( stream, "-");
						}
						util::stream_format( stream, "%03x", addr << 2);
						break;
					case 0x5: /* PUSH {Rlist}{LR} */
						util::stream_format( stream, "PUSH {LR, ");
>>>>>>> upstream/master
						for( offs = 7; offs >= 0; offs-- )
						{
							if( opcode & ( 1 << offs ) )
							{
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "R%d, ", offs);
							}
						}
						pBuf += sprintf( pBuf, "}");
						break;
					case 0x4: /* PUSH {Rlist} */
						pBuf += sprintf( pBuf, "PUSH {");
=======
								util::stream_format( stream, "R%d, ", offs);
							}
						}
						util::stream_format( stream, "}");
						break;
					case 0x4: /* PUSH {Rlist} */
						util::stream_format( stream, "PUSH {");
>>>>>>> upstream/master
						for( offs = 7; offs >= 0; offs-- )
						{
							if( opcode & ( 1 << offs ) )
							{
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "R%d, ", offs);
							}
						}
						pBuf += sprintf( pBuf, "}");
						break;
					case 0xc: /* POP {Rlist} */
						pBuf += sprintf( pBuf, "POP {");
=======
								util::stream_format( stream, "R%d, ", offs);
							}
						}
						util::stream_format( stream, "}");
						break;
					case 0xc: /* POP {Rlist} */
						util::stream_format( stream, "POP {");
>>>>>>> upstream/master
						for( offs = 0; offs < 8; offs++ )
						{
							if( opcode & ( 1 << offs ) )
							{
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "R%d, ", offs);
							}
						}
						pBuf += sprintf( pBuf, "}");
						break;
					case 0xd: /* POP {Rlist}{PC} */
						pBuf += sprintf( pBuf, "POP {");
=======
								util::stream_format( stream, "R%d, ", offs);
							}
						}
						util::stream_format( stream, "}");
						break;
					case 0xd: /* POP {Rlist}{PC} */
						util::stream_format( stream, "POP {");
>>>>>>> upstream/master
						for( offs = 0; offs < 8; offs++ )
						{
							if( opcode & ( 1 << offs ) )
							{
<<<<<<< HEAD
								pBuf += sprintf( pBuf, "R%d, ", offs);
							}
						}
						pBuf += sprintf( pBuf, "PC}");
						break;
					default:
						sprintf( pBuf, "INVALID %04x", opcode);
=======
								util::stream_format( stream, "R%d, ", offs);
							}
						}
						util::stream_format( stream, "PC}");
						break;
					default:
						util::stream_format(stream, "INVALID %04x", opcode);
>>>>>>> upstream/master
						break;
				}
				break;
			case 0xc: /* Multiple Load/Store */
				if( opcode & THUMB_MULTLS ) /* Load */
				{
					rd = ( opcode & THUMB_MULTLS_BASE ) >> THUMB_MULTLS_BASE_SHIFT;
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "LDMIA R%d!,{", rd);
=======
					util::stream_format( stream, "LDMIA R%d!,{", rd);
>>>>>>> upstream/master
					for( offs = 0; offs < 8; offs++ )
					{
						if( opcode & ( 1 << offs ) )
						{
<<<<<<< HEAD
							pBuf += sprintf( pBuf, "R%d, ", offs);
						}
					}
					pBuf += sprintf( pBuf, "}");
=======
							util::stream_format( stream, "R%d, ", offs);
						}
					}
					util::stream_format( stream, "}");
>>>>>>> upstream/master
				}
				else /* Store */
				{
					rd = ( opcode & THUMB_MULTLS_BASE ) >> THUMB_MULTLS_BASE_SHIFT;
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "STMIA R%d!,{", rd);
=======
					util::stream_format( stream, "STMIA R%d!,{", rd);
>>>>>>> upstream/master
					for( offs = 7; offs >= 0; offs-- )
					{
						if( opcode & ( 1 << offs ) )
						{
<<<<<<< HEAD
							pBuf += sprintf( pBuf, "R%d, ", offs);
						}
					}
					pBuf += sprintf( pBuf, "}");
				}
				break;
			case 0xd: /* Conditional Branch */
				offs = (INT8)( opcode & THUMB_INSN_IMM );
				switch( ( opcode & THUMB_COND_TYPE ) >> THUMB_COND_TYPE_SHIFT )
				{
					case COND_EQ:
						pBuf += sprintf( pBuf, "BEQ %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_NE:
						pBuf += sprintf( pBuf, "BNE %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_CS:
						pBuf += sprintf( pBuf, "BCS %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_CC:
						pBuf += sprintf( pBuf, "BCC %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_MI:
						pBuf += sprintf( pBuf, "BMI %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_PL:
						pBuf += sprintf( pBuf, "BPL %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_VS:
						pBuf += sprintf( pBuf, "BVS %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_VC:
						pBuf += sprintf( pBuf, "BVC %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_HI:
						pBuf += sprintf( pBuf, "BHI %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_LS:
						pBuf += sprintf( pBuf, "BLS %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_GE:
						pBuf += sprintf( pBuf, "BGE %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_LT:
						pBuf += sprintf( pBuf, "BLT %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_GT:
						pBuf += sprintf( pBuf, "BGT %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_LE:
						pBuf += sprintf( pBuf, "BLE %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_AL:
						pBuf += sprintf( pBuf, "INVALID");
						break;
					case COND_NV:
						pBuf += sprintf( pBuf, "SWI %02x\n", opcode & 0xff);
=======
							util::stream_format( stream, "R%d, ", offs);
						}
					}
					util::stream_format( stream, "}");
				}
				break;
			case 0xd: /* Conditional Branch */
				offs = (int8_t)( opcode & THUMB_INSN_IMM );
				switch( ( opcode & THUMB_COND_TYPE ) >> THUMB_COND_TYPE_SHIFT )
				{
					case COND_EQ:
						util::stream_format( stream, "BEQ %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_NE:
						util::stream_format( stream, "BNE %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_CS:
						util::stream_format( stream, "BCS %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_CC:
						util::stream_format( stream, "BCC %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_MI:
						util::stream_format( stream, "BMI %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_PL:
						util::stream_format( stream, "BPL %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_VS:
						util::stream_format( stream, "BVS %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_VC:
						util::stream_format( stream, "BVC %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_HI:
						util::stream_format( stream, "BHI %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_LS:
						util::stream_format( stream, "BLS %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_GE:
						util::stream_format( stream, "BGE %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_LT:
						util::stream_format( stream, "BLT %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_GT:
						util::stream_format( stream, "BGT %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_LE:
						util::stream_format( stream, "BLE %08x (%02x)", pc + 4 + (offs << 1), offs << 1);
						break;
					case COND_AL:
						util::stream_format( stream, "INVALID");
						break;
					case COND_NV:
						util::stream_format( stream, "SWI %02x\n", opcode & 0xff);
>>>>>>> upstream/master
						break;
				}
				break;
			case 0xe: /* B #offs */
				if( opcode  & THUMB_BLOP_LO )
				{
					addr = ( ( opcode & THUMB_BLOP_OFFS ) << 1 ) & 0xfffc;
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "BLX (LO) %08x", addr );
=======
					util::stream_format( stream, "BLX (LO) %08x", addr );
>>>>>>> upstream/master
					dasmflags = DASMFLAG_STEP_OVER;
				}
				else
				{
					offs = ( opcode & THUMB_BRANCH_OFFS ) << 1;
					if( offs & 0x00000800 )
					{
						offs |= 0xfffff800;
					}
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "B #%08x (%08x)", offs, pc + 4 + offs);
=======
					util::stream_format( stream, "B #%08x (%08x)", offs, pc + 4 + offs);
>>>>>>> upstream/master
				}
				break;
			case 0xf: /* BL */
				if( opcode & THUMB_BLOP_LO )
				{
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "BL (LO) %08x", ( opcode & THUMB_BLOP_OFFS ) << 1 );
=======
					util::stream_format( stream, "BL (LO) %08x", ( opcode & THUMB_BLOP_OFFS ) << 1 );
>>>>>>> upstream/master
					dasmflags = DASMFLAG_STEP_OVER;
				}
				else
				{
					addr = ( opcode & THUMB_BLOP_OFFS ) << 12;
					if( addr & ( 1 << 22 ) )
					{
						addr |= 0xff800000;
					}
<<<<<<< HEAD
					pBuf += sprintf( pBuf, "BL (HI) %08x", addr );
=======
					util::stream_format( stream, "BL (HI) %08x", addr );
>>>>>>> upstream/master
					dasmflags = DASMFLAG_STEP_OVER;
				}
				break;
			default:
<<<<<<< HEAD
				sprintf( pBuf, "INVALID %04x", opcode);
=======
				util::stream_format(stream, "INVALID %04x", opcode);
>>>>>>> upstream/master
				break;
		}

	return dasmflags | DASMFLAG_SUPPORTED;
}

CPU_DISASSEMBLE( arm7arm )
{
<<<<<<< HEAD
	return arm7_disasm(buffer, pc, oprom[0] | (oprom[1] << 8) | (oprom[2] << 16) | (oprom[3] << 24)) | 4;
=======
	return arm7_disasm(stream, pc, oprom[0] | (oprom[1] << 8) | (oprom[2] << 16) | (oprom[3] << 24)) | 4;
>>>>>>> upstream/master
}

CPU_DISASSEMBLE( arm7arm_be )
{
<<<<<<< HEAD
	return arm7_disasm(buffer, pc, oprom[3] | (oprom[2] << 8) | (oprom[1] << 16) | (oprom[0] << 24)) | 4;
=======
	return arm7_disasm(stream, pc, oprom[3] | (oprom[2] << 8) | (oprom[1] << 16) | (oprom[0] << 24)) | 4;
>>>>>>> upstream/master
}

CPU_DISASSEMBLE( arm7thumb )
{
<<<<<<< HEAD
	return thumb_disasm(buffer, pc, oprom[0] | (oprom[1] << 8)) | 2;
=======
	return thumb_disasm(stream, pc, oprom[0] | (oprom[1] << 8)) | 2;
>>>>>>> upstream/master
}

CPU_DISASSEMBLE( arm7thumb_be )
{
<<<<<<< HEAD
	return thumb_disasm(buffer, pc, oprom[1] | (oprom[0] << 8)) | 2;
=======
	return thumb_disasm(stream, pc, oprom[1] | (oprom[0] << 8)) | 2;
>>>>>>> upstream/master
}
