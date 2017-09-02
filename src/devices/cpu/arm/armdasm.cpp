// license:BSD-3-Clause
// copyright-holders:Bryan McPhail,Phil Stroffolino
/*
    ARM 2/3 disassembler

    (c) 2002-2006 Bryan McPhail (bmcphail@tendril.co.uk) and Phil Stroffolino
*/

#include "emu.h"
#include "arm.h"

<<<<<<< HEAD
static char *WriteImmediateOperand( char *pBuf, UINT32 opcode )
{
	/* rrrrbbbbbbbb */
	UINT32 imm;
=======
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

	/* Register Op2 */
	if (printOp2)
		pBuf += sprintf(pBuf,"R%d, ", (opcode>>0)&0xf);

	pBuf += sprintf(pBuf, "%s ", pRegOp[(opcode>>5)&3] );

	if( opcode&0x10 ) /* Shift amount specified in bottom bits of RS */
	{
		pBuf += sprintf( pBuf, "R%d", (opcode>>8)&0xf );
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

	/* Register Op2 */
	if (printOp2)
		util::stream_format(stream, "R%d, ", (opcode>>0)&0xf);

	util::stream_format(stream, "%s ", pRegOp[(opcode>>5)&3]);

	if( opcode&0x10 ) /* Shift amount specified in bottom bits of RS */
	{
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
		", R%d %s ", /* Operand 1 register, Operand 2 register, shift type */
		(opcode>> 0)&0xf,
		pRegOp[(opcode>>5)&3] );

	if( opcode&0x10 ) /* Shift amount specified in bottom bits of RS */
	{
		pBuf += sprintf( pBuf, "R%d", (opcode>>7)&0xf );
=======
	util::stream_format(
		stream,
		", R%d %s ", /* Operand 1 register, Operand 2 register, shift type */
		(opcode>> 0)&0xf,
		pRegOp[(opcode>>5)&3]);

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
=======
		util::stream_format( stream, "#%d", c );
	}
} /* WriteRegisterOperand */


static void WriteBranchAddress( std::ostream &stream, uint32_t pc, uint32_t opcode )
>>>>>>> upstream/master
{
	opcode &= 0x00ffffff;
	if( opcode&0x00800000 )
	{
		opcode |= 0xff000000; /* sign-extend */
	}
	pc += 8+4*opcode;
<<<<<<< HEAD
	sprintf( pBuf, "$%x", pc );
	return pBuf;
} /* WriteBranchAddress */

static char *WritePadding( char *pBuf, const char *pBuf0 )
{
	pBuf0 += 8;
	while( pBuf<pBuf0 )
	{
		*pBuf++ = ' ';
	}
	return pBuf;
}

static UINT32 arm_disasm( char *pBuf, UINT32 pc, UINT32 opcode )
{
	const char *pBuf0;

=======
	util::stream_format( stream, "$%x", pc );
} /* WriteBranchAddress */

static void WritePadding(std::ostream &stream, std::streampos start_position)
{
	std::streamoff difference = stream.tellp() - start_position;
	for (std::streamoff i = difference; i < 8; i++)
		stream << ' ';
}

static uint32_t arm_disasm( std::ostream &stream, uint32_t pc, uint32_t opcode )
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
=======
	uint32_t dasmflags = 0;
	std::streampos start_position = stream.tellp();

	pConditionCode= pConditionCodeTable[opcode>>28];
>>>>>>> upstream/master

	if( (opcode&0x0fc000f0)==0x00000090u )
	{
		/* multiply */
		/* xxxx0000 00ASdddd nnnnssss 1001mmmm */
		if( opcode&0x00200000 )
		{
<<<<<<< HEAD
			pBuf += sprintf( pBuf, "MLA" );
		}
		else
		{
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
			util::stream_format( stream, "MLA" );
		}
		else
		{
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
	else if( (opcode&0x0c000000)==0 )
	{
		int op=(opcode>>21)&0xf;

		/* Data Processing */
		/* xxxx001a aaaSnnnn ddddrrrr bbbbbbbb */
		/* xxxx000a aaaSnnnn ddddcccc ctttmmmm */

<<<<<<< HEAD
		pBuf += sprintf(
			pBuf, "%s%s",
			pOperation[op],
			pConditionCode );

		if( (opcode&0x01000000) )
		{
			*pBuf++ = 'S';
		}

		pBuf = WritePadding( pBuf, pBuf0 );
=======
		util::stream_format(stream,
			"%s%s",
			pOperation[op],
			pConditionCode);

		if( (opcode&0x01000000) )
		{
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
	else if( (opcode&0x0c000000)==0x04000000 )
	{
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

		if( opcode&0x02000000 )
		{
			/* register form */
<<<<<<< HEAD
			pBuf = WriteRegisterOperand1( pBuf, opcode );
			pBuf += sprintf( pBuf, "]" );
=======
			WriteRegisterOperand1( stream, opcode );
			util::stream_format( stream, "]" );
>>>>>>> upstream/master
		}
		else
		{
			/* immediate form */
<<<<<<< HEAD
			pBuf += sprintf( pBuf, "]" );
			if( opcode&0x00800000 )
			{
				pBuf += sprintf( pBuf, ", #$%x", opcode&0xfff );
			}
			else
			{
				pBuf += sprintf( pBuf, ", -#$%x", opcode&0xfff );
=======
			util::stream_format( stream, "]" );
			if( opcode&0x00800000 )
			{
				util::stream_format( stream, ", #$%x", opcode&0xfff );
			}
			else
			{
				util::stream_format( stream, ", -#$%x", opcode&0xfff );
>>>>>>> upstream/master
			}
		}
	}
	else if( (opcode&0x0e000000) == 0x08000000 )
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
		util::stream_format( stream, "[R%d], {",(opcode>>16)&0xf);
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
						util::stream_format( stream, " R%d,",last);
					else
						util::stream_format( stream, " R%d-R%d,",last,j-1);
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
				util::stream_format( stream, " R15,");
			else if (found)
				util::stream_format( stream, " R%d-R%d,",last,15);
		}

		stream.seekp(-1, std::ios_base::cur);
		util::stream_format( stream, " }");
>>>>>>> upstream/master
	}
	else if( (opcode&0x0e000000)==0x0a000000 )
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

		WriteBranchAddress( stream, pc, opcode );
>>>>>>> upstream/master
	}
	else if( (opcode&0x0f000000) == 0x0e000000 )
	{
		/* co-processor */
		/* xxxx1110 oooLNNNN ddddpppp qqq1MMMM MRC/MCR */
		if( (opcode&0x0f100000)==0x0e100000 )
		{
			if( (opcode&0x0f100010)==0x0e100010 )
			{
<<<<<<< HEAD
				pBuf += sprintf( pBuf, "MRC" );
			}
			else if( (opcode&0x0f100010)==0x0e000010 )
			{
				pBuf += sprintf( pBuf, "MCR" );
			}
			else
			{
				pBuf += sprintf( pBuf, "???" );
			}

			pBuf += sprintf( pBuf, "%s", pConditionCode );
			pBuf = WritePadding( pBuf, pBuf0 );
			pBuf += sprintf( pBuf, "R%d, CR%d {CRM%d, q%d}",(opcode>>12)&0xf, (opcode>>16)&0xf, (opcode>>0)&0xf, (opcode>>5)&0x7);
=======
				util::stream_format( stream, "MRC" );
			}
			else if( (opcode&0x0f100010)==0x0e000010 )
			{
				util::stream_format( stream, "MCR" );
			}
			else
			{
				util::stream_format( stream, "???" );
			}

			util::stream_format( stream, "%s", pConditionCode );
			WritePadding(stream, start_position);
			util::stream_format( stream, "R%d, CR%d {CRM%d, q%d}",(opcode>>12)&0xf, (opcode>>16)&0xf, (opcode>>0)&0xf, (opcode>>5)&0x7);
>>>>>>> upstream/master
			/* Nb:  full form should be o, p, R, CR, CRM, q */
		}
		else if( (opcode&0x0f000010)==0x0e000000 )
		{
<<<<<<< HEAD
			pBuf += sprintf( pBuf, "CDP" );
			pBuf += sprintf( pBuf, "%s", pConditionCode );
			pBuf = WritePadding( pBuf, pBuf0 );
			pBuf += sprintf( pBuf, "%08x", opcode );
		}
		else
		{
			pBuf += sprintf( pBuf, "???" );
=======
			util::stream_format( stream, "CDP" );
			util::stream_format( stream, "%s", pConditionCode );
			WritePadding(stream, start_position);
			util::stream_format( stream, "%08x", opcode );
		}
		else
		{
			util::stream_format( stream, "???" );
>>>>>>> upstream/master
		}
	}
	else if( (opcode&0x0f000000) == 0x0f000000 )
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

CPU_DISASSEMBLE( arm )
{
<<<<<<< HEAD
	UINT32 opcode = oprom[0] | (oprom[1] << 8) | (oprom[2] << 16) | (oprom[3] << 24);
	return 4 | arm_disasm(buffer, pc, opcode);
=======
	uint32_t opcode = oprom[0] | (oprom[1] << 8) | (oprom[2] << 16) | (oprom[3] << 24);
	return 4 | arm_disasm(stream, pc, opcode);
>>>>>>> upstream/master
}

CPU_DISASSEMBLE( arm_be )
{
<<<<<<< HEAD
	UINT32 opcode = oprom[3] | (oprom[2] << 8) | (oprom[1] << 16) | (oprom[0] << 24);
	return 4 | arm_disasm(buffer, pc, opcode);
=======
	uint32_t opcode = oprom[3] | (oprom[2] << 8) | (oprom[1] << 16) | (oprom[0] << 24);
	return 4 | arm_disasm(stream, pc, opcode);
>>>>>>> upstream/master
}
