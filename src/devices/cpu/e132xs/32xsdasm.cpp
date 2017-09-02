// license:BSD-3-Clause
// copyright-holders:Pierpaolo Prazzoli
/*

 Hyperstone disassembler
 written by Pierpaolo Prazzoli

*/

#include "emu.h"
<<<<<<< HEAD
#include "debugger.h"
#include "e132xs.h"
=======
#include "e132xs.h"
#include "debugger.h"

#include "32xsdefs.h"

>>>>>>> upstream/master

static const char *const L_REG[] =
{
	"L0",  "L1",  "L2",  "L3",  "L4",  "L5",  "L6",  "L7",  "L8",  "L9",
	"L10", "L11", "L12", "L13", "L14", "L15", "L16", "L17", "L18", "L19",
	"L20", "L21", "L22", "L23", "L24", "L25", "L26", "L27", "L28", "L29",
	"L30", "L31", "L32", "L33", "L34", "L35", "L36", "L37", "L38", "L39",
	"L40", "L41", "L42", "L43", "L44", "L45", "L46", "L47", "L48", "L49",
	"L50", "L51", "L52", "L53", "L54", "L55", "L56", "L57", "L58", "L59",
	"L60", "L61", "L62", "L63"
};

static const char *const G_REG[] =
{
	"PC",  "SR",  "FER", "G03", "G04", "G05", "G06", "G07", "G08", "G09",
	"G10", "G11", "G12", "G13", "G14", "G15", "G16", "G17", "SP",  "UB",
	"BCR", "TPR", "TCR", "TR",  "WCR", "ISR", "FCR", "MCR", "G28", "G29",
	"G30", "G31"
};

static const char *const SETxx[] =
{
	"SETADR",   "Reserved", "SET1",   "SET0",     "SETLE",  "SETGT",  "SETLT",  "SETGE",
	"SETSE",    "SETHT",    "SETST",  "SETHE",    "SETE",   "SETNE",  "SETV",   "SETNV",
	"Reserved", "Reserved", "SET1M",  "Reserved", "SETLEM", "SETGTM", "SETLTM", "SETGEM",
	"SETSEM",   "SETTHM",   "SETSTM", "SETHEM",   "SETEM",  "SETNEM", "SETVM",  "SETNVM"
};

#define DESTCODE(op)            ((op & 0x00f0) >> 4)
#define SOURCECODE(op)          (op & 0x000f)

#define SOURCEBIT(op)           ((op & 0x100) >> 8)
#define DESTBIT(op)             ((op & 0x200) >> 9)

#define N_VALUE(op)             ((((op & 0x100) >> 8) << 4 ) | (op & 0x0f))

static int size, global_fp;

static offs_t base_pc;
<<<<<<< HEAD
static const UINT8 *base_oprom;
#define READ_OP_DASM(p)         ((base_oprom[(p) - base_pc] << 8) | base_oprom[(p) + 1 - base_pc])


static void LL_format(char *source, char *dest, UINT16 op)
=======
static const uint8_t *base_oprom;
#define READ_OP_DASM(p)         ((base_oprom[(p) - base_pc] << 8) | base_oprom[(p) + 1 - base_pc])


static void LL_format(char *source, char *dest, uint16_t op)
>>>>>>> upstream/master
{
	strcpy(source, L_REG[(SOURCECODE(op)+global_fp)%64]);
	strcpy(dest, L_REG[(DESTCODE(op)+global_fp)%64]);
}

<<<<<<< HEAD
static void LR_format(char *source, char *dest, UINT16 op)
=======
static void LR_format(char *source, char *dest, uint16_t op)
>>>>>>> upstream/master
{
	if( SOURCEBIT(op) )
	{
		strcpy(source, L_REG[(SOURCECODE(op)+global_fp)%64]);
	}
	else
	{
		strcpy(source, G_REG[SOURCECODE(op)]);
	}

	strcpy(dest, L_REG[(DESTCODE(op)+global_fp)%64]);
}

<<<<<<< HEAD
static void RR_format(char *source, char *dest, UINT16 op, unsigned h_flag)
=======
static void RR_format(char *source, char *dest, uint16_t op, unsigned h_flag)
>>>>>>> upstream/master
{
	if( SOURCEBIT(op) )
	{
		strcpy(source, L_REG[(SOURCECODE(op)+global_fp)%64]);
	}
	else
	{
		strcpy(source, G_REG[SOURCECODE(op) + h_flag * 16]);
	}

	if( DESTBIT(op) )
	{
		strcpy(dest, L_REG[(DESTCODE(op)+global_fp)%64]);
	}
	else
	{
		strcpy(dest, G_REG[DESTCODE(op) + h_flag * 16]);
	}
}

<<<<<<< HEAD
static UINT32 LRconst_format(char *source, char *dest, UINT16 op, unsigned *pc)
{
	UINT16 next_op;
	UINT32 const_val;
=======
static uint32_t LRconst_format(char *source, char *dest, uint16_t op, unsigned *pc)
{
	uint16_t next_op;
	uint32_t const_val;
>>>>>>> upstream/master

	if( SOURCEBIT(op) )
	{
		strcpy(source, L_REG[(SOURCECODE(op)+global_fp)%64]);
	}
	else
	{
		strcpy(source, G_REG[SOURCECODE(op)]);
	}

	strcpy(dest, L_REG[(DESTCODE(op)+global_fp)%64]);

	size = 4;

	*pc += 2;
	next_op = READ_OP_DASM(*pc);

	if( E_BIT(next_op) )
	{
<<<<<<< HEAD
		UINT16 next_op2;
=======
		uint16_t next_op2;
>>>>>>> upstream/master

		size = 6;

		*pc += 2;
		next_op2 = READ_OP_DASM(*pc);
		const_val = next_op2;
		const_val |= ((next_op & 0x3fff) << 16 );

		if( S_BIT_CONST(next_op) )
		{
			const_val |= 0xc0000000;
		}
	}
	else
	{
		const_val = next_op & 0x3fff;

		if( S_BIT_CONST(next_op) )
		{
			const_val |= 0xffffc000;
		}
	}

	return const_val;
}

<<<<<<< HEAD
static UINT32 RRconst_format(char *source, char *dest, UINT16 op, unsigned *pc)
{
	UINT16 next_op;
	UINT32 const_val;
=======
static uint32_t RRconst_format(char *source, char *dest, uint16_t op, unsigned *pc)
{
	uint16_t next_op;
	uint32_t const_val;
>>>>>>> upstream/master

	if( SOURCEBIT(op) )
	{
		strcpy(source, L_REG[(SOURCECODE(op)+global_fp)%64]);
	}
	else
	{
		strcpy(source, G_REG[SOURCECODE(op)]);
	}

	if( DESTBIT(op) )
	{
		strcpy(dest, L_REG[(DESTCODE(op)+global_fp)%64]);
	}
	else
	{
		strcpy(dest, G_REG[DESTCODE(op)]);
	}

	size = 4;

	*pc += 2;
	next_op = READ_OP_DASM(*pc);

	if( E_BIT(next_op) )
	{
<<<<<<< HEAD
		UINT16 next_op2;
=======
		uint16_t next_op2;
>>>>>>> upstream/master

		size = 6;

		*pc += 2;
		next_op2 = READ_OP_DASM(*pc);
		const_val = next_op2;
		const_val |= ((next_op & 0x3fff) << 16 );

		if( S_BIT_CONST(next_op) )
		{
			const_val |= 0xc0000000;
		}
	}
	else
	{
		const_val = next_op & 0x3fff;

		if( S_BIT_CONST(next_op) )
		{
			const_val |= 0xffffc000;
		}
	}

	return const_val;
}

<<<<<<< HEAD
static INT32 Rimm_format(char *dest, UINT16 op, unsigned *pc, unsigned h_flag)
{
	UINT16 imm1, imm2;
	INT32 ret;
=======
static int32_t Rimm_format(char *dest, uint16_t op, unsigned *pc, unsigned h_flag)
{
	uint16_t imm1, imm2;
	int32_t ret;
>>>>>>> upstream/master

	int n = N_VALUE(op);

	if( DESTBIT(op) )
	{
		strcpy(dest, L_REG[(DESTCODE(op)+global_fp)%64]);
	}
	else
	{
		strcpy(dest, G_REG[DESTCODE(op) + h_flag * 16]);
	}

	switch( n )
	{
		case 0: case 1:  case 2:  case 3:  case 4:  case 5:  case 6:  case 7: case 8:
		case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16:
			return n;

		case 17:
			*pc += 2;
			imm1 = READ_OP_DASM(*pc);
			*pc += 2;
			imm2 = READ_OP_DASM(*pc);
			ret = (imm1 << 16) | imm2;

			size = 6;
			return ret;


		case 18:
			*pc += 2;
			ret = READ_OP_DASM(*pc);

			size = 4;
			return ret;

		case 19:
			*pc += 2;
<<<<<<< HEAD
			ret = (INT32) (0xffff0000 | READ_OP_DASM(*pc));
=======
			ret = (int32_t) (0xffff0000 | READ_OP_DASM(*pc));
>>>>>>> upstream/master

			size = 4;
			return ret;

		case 20:
			return 32;  //bit 5 = 1, others = 0

		case 21:
			return 64;  //bit 6 = 1, others = 0

		case 22:
			return 128; //bit 7 = 1, others = 0

		case 23:
			return 0x80000000; //bit 31 = 1, others = 0 (2 at the power of 31)

		case 24:
			return -8;

		case 25:
			return -7;

		case 26:
			return -6;

		case 27:
			return -5;

		case 28:
			return -4;

		case 29:
			return -3;

		case 30:
			return -2;

		case 31:
			return -1;

		default:
			return 0; //should never goes here
	}
}

<<<<<<< HEAD
static UINT8 Ln_format(char *dest, UINT16 op)
=======
static uint8_t Ln_format(char *dest, uint16_t op)
>>>>>>> upstream/master
{
	strcpy(dest, L_REG[(DESTCODE(op)+global_fp)%64]);

	return N_VALUE(op);
}

<<<<<<< HEAD
static UINT8 Rn_format(char *dest, UINT16 op)
=======
static uint8_t Rn_format(char *dest, uint16_t op)
>>>>>>> upstream/master
{
	if( DESTBIT(op) )
	{
		strcpy(dest, L_REG[(DESTCODE(op)+global_fp)%64]);
	}
	else
	{
		strcpy(dest, G_REG[DESTCODE(op)]);
	}

	return N_VALUE(op);
}

<<<<<<< HEAD
static INT32 PCrel_format(UINT16 op, unsigned pc)
{
	INT32 ret;

	if( op & 0x80 ) //bit 7 = 1
	{
		UINT16 next;
=======
static int32_t PCrel_format(uint16_t op, unsigned pc)
{
	int32_t ret;

	if( op & 0x80 ) //bit 7 = 1
	{
		uint16_t next;
>>>>>>> upstream/master

		size = 4;

		pc += 2;

		next = READ_OP_DASM(pc);

		ret = (op & 0x7f) << 16;

		ret |= (next & 0xfffe);

		if( next & 1 )
			ret |= 0xff800000; //ok?
	}
	else
	{
		ret = op & 0x7e;

		if( op & 1 )
			ret |= 0xffffff80; //ok?
	}

	return (pc + ret);
}

<<<<<<< HEAD
static UINT32 RRdis_format(char *source, char *dest, UINT16 op, UINT16 next_op, unsigned pc)
{
	UINT32 ret;
=======
static uint32_t RRdis_format(char *source, char *dest, uint16_t op, uint16_t next_op, unsigned pc)
{
	uint32_t ret;
>>>>>>> upstream/master

	if( SOURCEBIT(op) )
	{
		strcpy(source, L_REG[(SOURCECODE(op)+global_fp)%64]);
	}
	else
	{
		strcpy(source, G_REG[SOURCECODE(op)]);
	}

	if( DESTBIT(op) )
	{
		strcpy(dest, L_REG[(DESTCODE(op)+global_fp)%64]);
	}
	else
	{
		strcpy(dest, G_REG[DESTCODE(op)]);
	}

	if( E_BIT(next_op) )
	{
<<<<<<< HEAD
		UINT16 next;
=======
		uint16_t next;
>>>>>>> upstream/master

		size = 6;

		next = READ_OP_DASM(pc + 4);

		ret = next;
		ret |= ( ( next_op & 0xfff ) << 16 );

		if( S_BIT_CONST(next_op) )
		{
			ret |= 0xf0000000;
		}
	}
	else
	{
		ret = next_op & 0xfff;
		if( S_BIT_CONST(next_op) )
		{
			ret |= 0xfffff000;
		}
	}

	return ret;
}

<<<<<<< HEAD
unsigned dasm_hyperstone(char *buffer, unsigned pc, const UINT8 *oprom, unsigned h_flag, int private_fp)
{
	UINT16 op = 0;
	UINT8 op_num;

	UINT8 source_code, dest_code, source_bit, dest_bit;

	char source[5] = "\0", dest[5] = "\0";
	UINT32 flags = 0;
=======
unsigned dasm_hyperstone(std::ostream &stream, unsigned pc, const uint8_t *oprom, unsigned h_flag, int private_fp)
{
	uint16_t op;
	uint8_t op_num;

	uint8_t source_code, dest_code, source_bit, dest_bit;

	char source[5] = "\0", dest[5] = "\0";
	uint32_t flags = 0;
>>>>>>> upstream/master

	base_pc = pc;
	base_oprom = oprom;

	op = READ_OP_DASM(pc);

	size = 2;

	source_code = SOURCECODE(op);
	dest_code = DESTCODE(op);
	source_bit = SOURCEBIT(op);
	dest_bit = DESTBIT(op);

	global_fp = private_fp;

	op_num = (op & 0xff00) >> 8;

	switch( op_num )
	{
		// CHK - CHKZ - NOP
		case 0x00: case 0x01: case 0x02: case 0x03:

			if( source_bit && dest_bit && source_code == 0 && dest_code == 0 )
			{
<<<<<<< HEAD
				sprintf(buffer, "NOP");
=======
				util::stream_format(stream, "NOP");
>>>>>>> upstream/master
			}
			else
			{
				RR_format(source, dest, op, 0);

				if( !source_bit && source_code == SR_REGISTER )
				{
<<<<<<< HEAD
					sprintf(buffer, "CHKZ %s, 0", dest);
				}
				else
				{
					sprintf(buffer, "CHK %s, %s", dest, source);
=======
					util::stream_format(stream, "CHKZ %s, 0", dest);
				}
				else
				{
					util::stream_format(stream, "CHK %s, %s", dest, source);
>>>>>>> upstream/master
				}
			}

			break;

		// MOVD - RET
		case 0x04: case 0x05: case 0x06: case 0x07:

			RR_format(source, dest, op, 0);

			if( dest_code == PC_REGISTER && !dest_bit )
			{
				global_fp = 0;
				RR_format(source, dest, op, 0);
<<<<<<< HEAD
				sprintf(buffer, "RET PC, %s", source);
=======
				util::stream_format(stream, "RET PC, %s", source);
>>>>>>> upstream/master
				flags = DASMFLAG_STEP_OUT;
			}
			else if( source_code == SR_REGISTER && !source_bit )
			{
<<<<<<< HEAD
				sprintf(buffer, "MOVD %s, 0", dest);
			}
			else
			{
				sprintf(buffer, "MOVD %s, %s", dest, source);
=======
				util::stream_format(stream, "MOVD %s, 0", dest);
			}
			else
			{
				util::stream_format(stream, "MOVD %s, %s", dest, source);
>>>>>>> upstream/master
			}

			break;

		// DIVU
		case 0x08: case 0x09: case 0x0a: case 0x0b:

			RR_format(source, dest, op, 0);
<<<<<<< HEAD
			sprintf(buffer, "DIVU %s, %s", dest, source);
=======
			util::stream_format(stream, "DIVU %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// DIVS
		case 0x0c: case 0x0d: case 0x0e: case 0x0f:

			RR_format(source, dest, op, 0);
<<<<<<< HEAD
			sprintf(buffer, "DIVS %s, %s", dest, source);
=======
			util::stream_format(stream, "DIVS %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// XMx - XXx
		case 0x10: case 0x11: case 0x12: case 0x13:
		{
			int xcode;

			RR_format(source, dest, op, 0);

			size = 4;

			pc += 2;
			op = READ_OP_DASM(pc);

			xcode = X_CODE(op);

			if( xcode < 4 )
			{
<<<<<<< HEAD
				UINT16 lim;

				if( E_BIT(op) )
				{
					UINT16 next_op;
=======
				uint16_t lim;

				if( E_BIT(op) )
				{
					uint16_t next_op;
>>>>>>> upstream/master

					size = 6;

					pc += 2;
					next_op = READ_OP_DASM(pc);

					lim = ((op & 0xfff) << 16) | next_op;
				}
				else
				{
					lim = op & 0xfff;
				}

<<<<<<< HEAD
				sprintf(buffer, "XM%x %s, %s, $%x", (UINT8)(float) pow(2.0, xcode), dest, source, lim);
=======
				util::stream_format(stream, "XM%x %s, %s, $%x", (uint8_t)(float) pow(2.0, xcode), dest, source, lim);
>>>>>>> upstream/master

			}
			else
			{
<<<<<<< HEAD
				sprintf(buffer, "XX%x %s, %s, 0", (UINT8)(float) pow(2.0, (xcode - 4)), dest, source);
=======
				util::stream_format(stream, "XX%x %s, %s, 0", (uint8_t)(float) pow(2.0, (xcode - 4)), dest, source);
>>>>>>> upstream/master
			}

			break;
		}

		// MASK
		case 0x14: case 0x15: case 0x16: case 0x17:
		{
<<<<<<< HEAD
			UINT32 const_val = RRconst_format(source, dest, op, &pc);

			sprintf(buffer, "MASK %s, %s, $%x", dest, source, const_val);
=======
			uint32_t const_val = RRconst_format(source, dest, op, &pc);

			util::stream_format(stream, "MASK %s, %s, $%x", dest, source, const_val);
>>>>>>> upstream/master

			break;
		}

		// SUM
		case 0x18: case 0x19: case 0x1a: case 0x1b:
		{
<<<<<<< HEAD
			UINT32 const_val = RRconst_format(source, dest, op, &pc);

			if( source_code == SR_REGISTER && !source_bit )
			{
				sprintf(buffer, "SUM %s, C, $%x", dest, const_val);
			}
			else
			{
				sprintf(buffer, "SUM %s, %s, $%x", dest, source, const_val);
=======
			uint32_t const_val = RRconst_format(source, dest, op, &pc);

			if( source_code == SR_REGISTER && !source_bit )
			{
				util::stream_format(stream, "SUM %s, C, $%x", dest, const_val);
			}
			else
			{
				util::stream_format(stream, "SUM %s, %s, $%x", dest, source, const_val);
>>>>>>> upstream/master
			}

			break;
		}

		// SUMS
		case 0x1c: case 0x1d: case 0x1e: case 0x1f:
		{
<<<<<<< HEAD
			UINT32 const_val = RRconst_format(source, dest, op, &pc);

			if( source_code == SR_REGISTER && !source_bit )
			{
				sprintf(buffer, "SUMS %s, C, $%x", dest, const_val);
			}
			else
			{
				sprintf(buffer, "SUMS %s, %s, $%x", dest, source, const_val);
=======
			uint32_t const_val = RRconst_format(source, dest, op, &pc);

			if( source_code == SR_REGISTER && !source_bit )
			{
				util::stream_format(stream, "SUMS %s, C, $%x", dest, const_val);
			}
			else
			{
				util::stream_format(stream, "SUMS %s, %s, $%x", dest, source, const_val);
>>>>>>> upstream/master
			}

			break;
		}

		// CMP
		case 0x20: case 0x21: case 0x22: case 0x23:

			RR_format(source, dest, op, 0);

			if( source_code == SR_REGISTER && !source_bit )
			{
<<<<<<< HEAD
				sprintf(buffer, "CMP %s, C", dest);
			}
			else
			{
				sprintf(buffer, "CMP %s, %s", dest, source);
=======
				util::stream_format(stream, "CMP %s, C", dest);
			}
			else
			{
				util::stream_format(stream, "CMP %s, %s", dest, source);
>>>>>>> upstream/master
			}

			break;

		// MOV
		case 0x24: case 0x25: case 0x26: case 0x27:

			RR_format(source, dest, op, h_flag);
<<<<<<< HEAD
			sprintf(buffer, "MOV %s, %s", dest, source);
=======
			util::stream_format(stream, "MOV %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// ADD
		case 0x28: case 0x29: case 0x2a: case 0x2b:

			RR_format(source, dest, op, 0);

			if( source_code == SR_REGISTER && !source_bit )
			{
<<<<<<< HEAD
				sprintf(buffer, "ADD %s, C", dest);
			}
			else
			{
				sprintf(buffer, "ADD %s, %s", dest, source);
=======
				util::stream_format(stream, "ADD %s, C", dest);
			}
			else
			{
				util::stream_format(stream, "ADD %s, %s", dest, source);
>>>>>>> upstream/master
			}

			break;

		// ADDS
		case 0x2c: case 0x2d: case 0x2e: case 0x2f:

			RR_format(source, dest, op, 0);

			if( source_code == SR_REGISTER && !source_bit )
			{
<<<<<<< HEAD
				sprintf(buffer, "ADDS %s, C", dest);
			}
			else
			{
				sprintf(buffer, "ADDS %s, %s", dest, source);
=======
				util::stream_format(stream, "ADDS %s, C", dest);
			}
			else
			{
				util::stream_format(stream, "ADDS %s, %s", dest, source);
>>>>>>> upstream/master
			}

			break;

		// CMPB
		case 0x30: case 0x31: case 0x32: case 0x33:

			RR_format(source, dest, op, 0);
<<<<<<< HEAD
			sprintf(buffer, "CMPB %s, %s", dest, source);
=======
			util::stream_format(stream, "CMPB %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// ANDN
		case 0x34: case 0x35: case 0x36: case 0x37:

			RR_format(source, dest, op, 0);
<<<<<<< HEAD
			sprintf(buffer, "ANDN %s, %s", dest, source);
=======
			util::stream_format(stream, "ANDN %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// OR
		case 0x38: case 0x39: case 0x3a: case 0x3b:

			RR_format(source, dest, op, 0);
<<<<<<< HEAD
			sprintf(buffer, "OR %s, %s", dest, source);
=======
			util::stream_format(stream, "OR %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// XOR
		case 0x3c: case 0x3d: case 0x3e: case 0x3f:

			RR_format(source, dest, op, 0);
<<<<<<< HEAD
			sprintf(buffer, "XOR %s, %s", dest, source);
=======
			util::stream_format(stream, "XOR %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// SUBC
		case 0x40: case 0x41: case 0x42: case 0x43:

			RR_format(source, dest, op, 0);

			if( source_code == SR_REGISTER && !source_bit )
			{
<<<<<<< HEAD
				sprintf(buffer, "SUBC %s, C", dest);
			}
			else
			{
				sprintf(buffer, "SUBC %s, %s", dest, source);
=======
				util::stream_format(stream, "SUBC %s, C", dest);
			}
			else
			{
				util::stream_format(stream, "SUBC %s, %s", dest, source);
>>>>>>> upstream/master
			}

			break;

		// NOT
		case 0x44: case 0x45: case 0x46: case 0x47:

			RR_format(source, dest, op, 0);

<<<<<<< HEAD
			sprintf(buffer, "NOT %s, %s", dest, source);
=======
			util::stream_format(stream, "NOT %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// SUB
		case 0x48: case 0x49: case 0x4a: case 0x4b:

			RR_format(source, dest, op, 0);

			if( source_code == SR_REGISTER && !source_bit )
			{
<<<<<<< HEAD
				sprintf(buffer, "SUB %s, C", dest);
			}
			else
			{
				sprintf(buffer, "SUB %s, %s", dest, source);
=======
				util::stream_format(stream, "SUB %s, C", dest);
			}
			else
			{
				util::stream_format(stream, "SUB %s, %s", dest, source);
>>>>>>> upstream/master
			}

			break;

		// SUBS
		case 0x4c: case 0x4d: case 0x4e: case 0x4f:

			RR_format(source, dest, op, 0);

			if( source_code == SR_REGISTER && !source_bit )
			{
<<<<<<< HEAD
				sprintf(buffer, "SUBS %s, C", dest);
			}
			else
			{
				sprintf(buffer, "SUBS %s, %s", dest, source);
=======
				util::stream_format(stream, "SUBS %s, C", dest);
			}
			else
			{
				util::stream_format(stream, "SUBS %s, %s", dest, source);
>>>>>>> upstream/master
			}

			break;

		// ADDC
		case 0x50: case 0x51: case 0x52: case 0x53:

			RR_format(source, dest, op, 0);

			if( source_code == SR_REGISTER && !source_bit )
			{
<<<<<<< HEAD
				sprintf(buffer, "ADDC %s, C", dest);
			}
			else
			{
				sprintf(buffer, "ADDC %s, %s", dest, source);
=======
				util::stream_format(stream, "ADDC %s, C", dest);
			}
			else
			{
				util::stream_format(stream, "ADDC %s, %s", dest, source);
>>>>>>> upstream/master
			}

			break;

		// AND
		case 0x54: case 0x55: case 0x56: case 0x57:

			RR_format(source, dest, op, 0);
<<<<<<< HEAD
			sprintf(buffer, "AND %s, %s", dest, source);
=======
			util::stream_format(stream, "AND %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// NEG
		case 0x58: case 0x59: case 0x5a: case 0x5b:

			RR_format(source, dest, op, 0);

			if( source_code == SR_REGISTER && !source_bit )
			{
<<<<<<< HEAD
				sprintf(buffer, "NEG %s, C", dest);
			}
			else
			{
				sprintf(buffer, "NEG %s, %s", dest, source);
=======
				util::stream_format(stream, "NEG %s, C", dest);
			}
			else
			{
				util::stream_format(stream, "NEG %s, %s", dest, source);
>>>>>>> upstream/master
			}

			break;

		// NEGS
		case 0x5c: case 0x5d: case 0x5e: case 0x5f:

			RR_format(source, dest, op, 0);

			if( source_code == SR_REGISTER && !source_bit )
			{
<<<<<<< HEAD
				sprintf(buffer, "NEGS %s, C", dest);
			}
			else
			{
				sprintf(buffer, "NEGS %s, %s", dest, source);
=======
				util::stream_format(stream, "NEGS %s, C", dest);
			}
			else
			{
				util::stream_format(stream, "NEGS %s, %s", dest, source);
>>>>>>> upstream/master
			}

			break;

		// CMPI
		case 0x60: case 0x61: case 0x62: case 0x63:
		{
<<<<<<< HEAD
			UINT32 imm = Rimm_format(dest, op, &pc, 0);

			sprintf(buffer, "CMPI %s, $%x", dest, imm);
=======
			uint32_t imm = Rimm_format(dest, op, &pc, 0);

			util::stream_format(stream, "CMPI %s, $%x", dest, imm);
>>>>>>> upstream/master

			break;
		}

		// MOVI
		case 0x64: case 0x65: case 0x66: case 0x67:
		{
<<<<<<< HEAD
			UINT32 imm = Rimm_format(dest, op, &pc, h_flag);

			sprintf(buffer, "MOVI %s, $%x", dest, imm);
=======
			uint32_t imm = Rimm_format(dest, op, &pc, h_flag);

			util::stream_format(stream, "MOVI %s, $%x", dest, imm);
>>>>>>> upstream/master

			break;
		}

		// ADDI
		case 0x68: case 0x69: case 0x6a: case 0x6b:
		{
<<<<<<< HEAD
			UINT32 imm = Rimm_format(dest, op, &pc, 0);

			if( !N_VALUE(op) )
			{
				sprintf(buffer, "ADDI %s, CZ", dest);
			}
			else
			{
				sprintf(buffer, "ADDI %s, $%x", dest, imm);
=======
			uint32_t imm = Rimm_format(dest, op, &pc, 0);

			if( !N_VALUE(op) )
			{
				util::stream_format(stream, "ADDI %s, CZ", dest);
			}
			else
			{
				util::stream_format(stream, "ADDI %s, $%x", dest, imm);
>>>>>>> upstream/master
			}

			break;
		}

		// ADDSI
		case 0x6c: case 0x6d: case 0x6e: case 0x6f:
		{
<<<<<<< HEAD
			UINT32 imm = Rimm_format(dest, op, &pc, 0);

			if( !N_VALUE(op) )
			{
				sprintf(buffer, "ADDSI %s, CZ", dest);
			}
			else
			{
				sprintf(buffer, "ADDSI %s, $%x", dest, imm);
=======
			uint32_t imm = Rimm_format(dest, op, &pc, 0);

			if( !N_VALUE(op) )
			{
				util::stream_format(stream, "ADDSI %s, CZ", dest);
			}
			else
			{
				util::stream_format(stream, "ADDSI %s, $%x", dest, imm);
>>>>>>> upstream/master
			}

			break;
		}

		// CMPBI
		case 0x70: case 0x71: case 0x72: case 0x73:
		{
<<<<<<< HEAD
			UINT32 imm = Rimm_format(dest, op, &pc, 0);

			if( !N_VALUE(op) )
			{
				sprintf(buffer, "CMPBI %s, ANYBZ", dest);
=======
			uint32_t imm = Rimm_format(dest, op, &pc, 0);

			if( !N_VALUE(op) )
			{
				util::stream_format(stream, "CMPBI %s, ANYBZ", dest);
>>>>>>> upstream/master
			}
			else
			{
				if( N_VALUE(op) == 31 )
					imm = 0x7fffffff; //bit 31 = 0, others = 1

<<<<<<< HEAD
				sprintf(buffer, "CMPBI %s, $%x", dest, imm);
=======
				util::stream_format(stream, "CMPBI %s, $%x", dest, imm);
>>>>>>> upstream/master
			}

			break;
		}

		// ANDNI
		case 0x74: case 0x75: case 0x76: case 0x77:
		{
<<<<<<< HEAD
			UINT32 imm = Rimm_format(dest, op, &pc, 0);
=======
			uint32_t imm = Rimm_format(dest, op, &pc, 0);
>>>>>>> upstream/master

			if( N_VALUE(op) == 31 )
				imm = 0x7fffffff; //bit 31 = 0, others = 1

<<<<<<< HEAD
			sprintf(buffer, "ANDNI %s, $%x", dest, imm);
=======
			util::stream_format(stream, "ANDNI %s, $%x", dest, imm);
>>>>>>> upstream/master

			break;
		}

		// ORI
		case 0x78: case 0x79: case 0x7a: case 0x7b:
		{
<<<<<<< HEAD
			UINT32 imm = Rimm_format(dest, op, &pc, 0);

			sprintf(buffer, "ORI %s, $%x", dest, imm);
=======
			uint32_t imm = Rimm_format(dest, op, &pc, 0);

			util::stream_format(stream, "ORI %s, $%x", dest, imm);
>>>>>>> upstream/master

			break;
		}

		// XORI
		case 0x7c: case 0x7d: case 0x7e: case 0x7f:
		{
<<<<<<< HEAD
			UINT32 imm = Rimm_format(dest, op, &pc, 0);

			sprintf(buffer, "XORI %s, $%x", dest, imm);
=======
			uint32_t imm = Rimm_format(dest, op, &pc, 0);

			util::stream_format(stream, "XORI %s, $%x", dest, imm);
>>>>>>> upstream/master

			break;
		}

		// SHRDI
		case 0x80: case 0x81:
		{
<<<<<<< HEAD
			UINT8 n = Ln_format(dest, op);

			sprintf(buffer, "SHRDI %s, $%x", dest, n);
=======
			uint8_t n = Ln_format(dest, op);

			util::stream_format(stream, "SHRDI %s, $%x", dest, n);
>>>>>>> upstream/master

			break;
		}

		// SHRD
		case 0x82:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "SHRD %s, %s", dest, source);
=======
			util::stream_format(stream, "SHRD %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// SHR
		case 0x83:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "SHR %s, %s", dest, source);
=======
			util::stream_format(stream, "SHR %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// SARDI
		case 0x84: case 0x85:
		{
<<<<<<< HEAD
			UINT8 n = Ln_format(dest, op);

			sprintf(buffer, "SARDI %s, $%x", dest, n);
=======
			uint8_t n = Ln_format(dest, op);

			util::stream_format(stream, "SARDI %s, $%x", dest, n);
>>>>>>> upstream/master

			break;
		}

		// SARD
		case 0x86:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "SARD %s, %s", dest, source);
=======
			util::stream_format(stream, "SARD %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// SAR
		case 0x87:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "SAR %s, %s", dest, source);
=======
			util::stream_format(stream, "SAR %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// SHLDI
		case 0x88: case 0x89:
		{
<<<<<<< HEAD
			UINT8 n = Ln_format(dest, op);

			sprintf(buffer, "SHLDI %s, $%x", dest, n);
=======
			uint8_t n = Ln_format(dest, op);

			util::stream_format(stream, "SHLDI %s, $%x", dest, n);
>>>>>>> upstream/master

			break;
		}

		// SHLD
		case 0x8a:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "SHLD %s, %s", dest, source);
=======
			util::stream_format(stream, "SHLD %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// SHL
		case 0x8b:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "SHL %s, %s", dest, source);
=======
			util::stream_format(stream, "SHL %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// RESERVED
		case 0x8c: case 0x8d:
		case 0xac: case 0xad: case 0xae: case 0xaf:

<<<<<<< HEAD
			sprintf(buffer, "Reserved");
=======
			util::stream_format(stream, "Reserved");
>>>>>>> upstream/master

			break;

		// TESTLZ
		case 0x8e:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "TESTLZ %s, %s", dest, source);
=======
			util::stream_format(stream, "TESTLZ %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// ROL
		case 0x8f:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "ROL %s, %s", dest, source);
=======
			util::stream_format(stream, "ROL %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// LDxx.D/A/IOD/IOA
		case 0x90: case 0x91: case 0x92: case 0x93:
		{
<<<<<<< HEAD
			UINT16 next_op = READ_OP_DASM(pc + 2);
			UINT32 dis = RRdis_format(source, dest, op, next_op, pc);
=======
			uint16_t next_op = READ_OP_DASM(pc + 2);
			uint32_t dis = RRdis_format(source, dest, op, next_op, pc);
>>>>>>> upstream/master

			if( size == 2 )
				size = 4;

			if( dest_code == SR_REGISTER && !dest_bit )
			{
				switch( DD( next_op ) )
				{
					case 0:
						// LDBS.A
<<<<<<< HEAD
						sprintf(buffer, "LDBS.A 0, %s, $%x", source, dis);
=======
						util::stream_format(stream, "LDBS.A 0, %s, $%x", source, dis);
>>>>>>> upstream/master
						break;

					case 1:
						// LDBU.A
<<<<<<< HEAD
						sprintf(buffer, "LDBU.A 0, %s, $%x", source, dis);
=======
						util::stream_format(stream, "LDBU.A 0, %s, $%x", source, dis);
>>>>>>> upstream/master
						break;

					case 2:
						// LDHS.A
						if( dis & 1 )
						{
<<<<<<< HEAD
							sprintf(buffer, "LDHS.A 0, %s, $%x", source, dis & ~1);
=======
							util::stream_format(stream, "LDHS.A 0, %s, $%x", source, dis & ~1);
>>>>>>> upstream/master
						}
						// LDHU.A
						else
						{
<<<<<<< HEAD
							sprintf(buffer, "LDHU.A 0, %s, $%x", source, dis & ~1);
=======
							util::stream_format(stream, "LDHU.A 0, %s, $%x", source, dis & ~1);
>>>>>>> upstream/master
						}

						break;

					case 3:
						// LDD.IOA
						if( (dis & 3) == 3 )
						{
<<<<<<< HEAD
							sprintf(buffer, "LDD.IOA 0, %s, $%x", source, dis & ~3);
=======
							util::stream_format(stream, "LDD.IOA 0, %s, $%x", source, dis & ~3);
>>>>>>> upstream/master
						}
						// LDW.IOA
						else if( (dis & 3) == 2 )
						{
<<<<<<< HEAD
							sprintf(buffer, "LDW.IOA 0, %s, $%x", source, dis & ~3);
=======
							util::stream_format(stream, "LDW.IOA 0, %s, $%x", source, dis & ~3);
>>>>>>> upstream/master
						}
						// LDD.A
						else if( (dis & 3) == 1 )
						{
<<<<<<< HEAD
							sprintf(buffer, "LDD.A 0, %s, $%x", source, dis & ~1);
=======
							util::stream_format(stream, "LDD.A 0, %s, $%x", source, dis & ~1);
>>>>>>> upstream/master
						}
						// LDW.A
						else
						{
<<<<<<< HEAD
							sprintf(buffer, "LDW.A 0, %s, $%x", source, dis & ~1);
=======
							util::stream_format(stream, "LDW.A 0, %s, $%x", source, dis & ~1);
>>>>>>> upstream/master
						}

						break;
				}
			}
			else
			{
				switch( DD( next_op ) )
				{
					case 0:
						// LDBS.D
<<<<<<< HEAD
						sprintf(buffer, "LDBS.D %s, %s, $%x", dest, source, dis);
=======
						util::stream_format(stream, "LDBS.D %s, %s, $%x", dest, source, dis);
>>>>>>> upstream/master
						break;

					case 1:
						// LDBU.D
<<<<<<< HEAD
						sprintf(buffer, "LDBU.D %s, %s, $%x", dest, source, dis);
=======
						util::stream_format(stream, "LDBU.D %s, %s, $%x", dest, source, dis);
>>>>>>> upstream/master
						break;

					case 2:
						// LDHS.D
						if( dis & 1 )
						{
<<<<<<< HEAD
							sprintf(buffer, "LDHS.D %s, %s, $%x", dest, source, dis & ~1);
=======
							util::stream_format(stream, "LDHS.D %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
						}
						// LDHU.D
						else
						{
<<<<<<< HEAD
							sprintf(buffer, "LDHU.D %s, %s, $%x", dest, source, dis & ~1);
=======
							util::stream_format(stream, "LDHU.D %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
						}
						break;

					case 3:
						// LDD.IOD
						if( (dis & 3) == 3 )
						{
<<<<<<< HEAD
							sprintf(buffer, "LDD.IOD %s, %s, $%x", dest, source, dis & ~3);
=======
							util::stream_format(stream, "LDD.IOD %s, %s, $%x", dest, source, dis & ~3);
>>>>>>> upstream/master
						}
						// LDW.IOD
						else if( (dis & 3) == 2 )
						{
<<<<<<< HEAD
							sprintf(buffer, "LDW.IOD %s, %s, $%x", dest, source, dis & ~3);
=======
							util::stream_format(stream, "LDW.IOD %s, %s, $%x", dest, source, dis & ~3);
>>>>>>> upstream/master
						}
						// LDD.D
						else if( (dis & 3) == 1 )
						{
<<<<<<< HEAD
							sprintf(buffer, "LDD.D %s, %s, $%x", dest, source, dis & ~1);
=======
							util::stream_format(stream, "LDD.D %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
						}
						// LDW.D
						else
						{
<<<<<<< HEAD
							sprintf(buffer, "LDW.D %s, %s, $%x", dest, source, dis & ~1);
=======
							util::stream_format(stream, "LDW.D %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
						}

						break;
				}
			}

			break;
		}

		// LDxx.N/S
		case 0x94: case 0x95: case 0x96: case 0x97:
		{
<<<<<<< HEAD
			UINT16 next_op = READ_OP_DASM(pc + 2);
			UINT32 dis = RRdis_format(source, dest, op, next_op, pc);
=======
			uint16_t next_op = READ_OP_DASM(pc + 2);
			uint32_t dis = RRdis_format(source, dest, op, next_op, pc);
>>>>>>> upstream/master

			if( size == 2 )
				size = 4;

			if( (dest_code == PC_REGISTER && !dest_bit) || (dest_code == SR_REGISTER && !dest_bit) )
			{
<<<<<<< HEAD
				sprintf(buffer, "Reserved");
=======
				util::stream_format(stream, "Reserved");
>>>>>>> upstream/master
				break;
			}

			switch( DD( next_op ) )
			{
				case 0:
					// LDBS.N
<<<<<<< HEAD
					sprintf(buffer, "LDBS.N %s, %s, $%x", dest, source, dis);
=======
					util::stream_format(stream, "LDBS.N %s, %s, $%x", dest, source, dis);
>>>>>>> upstream/master
					break;

				case 1:
					// LDBU.N
<<<<<<< HEAD
					sprintf(buffer, "LDBU.N %s, %s, $%x", dest, source, dis);
=======
					util::stream_format(stream, "LDBU.N %s, %s, $%x", dest, source, dis);
>>>>>>> upstream/master
					break;

				case 2:
					// LDHS.N
					if( dis & 1 )
					{
<<<<<<< HEAD
						sprintf(buffer, "LDHS.N %s, %s, $%x", dest, source, dis & ~1);
=======
						util::stream_format(stream, "LDHS.N %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
					}
					// LDHU.N
					else
					{
<<<<<<< HEAD
						sprintf(buffer, "LDHU.N %s, %s, $%x", dest, source, dis & ~1);
=======
						util::stream_format(stream, "LDHU.N %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
					}

					break;

				case 3:
					// LDW.S
					if( (dis & 3) == 3 )
					{
<<<<<<< HEAD
						sprintf(buffer, "LDW.S %s, %s, $%x", dest, source, dis & ~3);
=======
						util::stream_format(stream, "LDW.S %s, %s, $%x", dest, source, dis & ~3);
>>>>>>> upstream/master
					}
					// Reserved
					else if( (dis & 3) == 2 )
					{
<<<<<<< HEAD
						sprintf(buffer, "Reserved");
=======
						util::stream_format(stream, "Reserved");
>>>>>>> upstream/master
					}
					// LDD.N
					else if( (dis & 3) == 1 )
					{
<<<<<<< HEAD
						sprintf(buffer, "LDD.N %s, %s, $%x", dest, source, dis & ~1);
=======
						util::stream_format(stream, "LDD.N %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
					}
					// LDW.N
					else
					{
<<<<<<< HEAD
						sprintf(buffer, "LDW.N %s, %s, $%x", dest, source, dis & ~1);
=======
						util::stream_format(stream, "LDW.N %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
					}

					break;
			}

			break;
		}

		// STxx.D/A/IOD/IOA
		case 0x98: case 0x99: case 0x9a: case 0x9b:
		{
<<<<<<< HEAD
			UINT16 next_op = READ_OP_DASM(pc + 2);
			UINT32 dis = RRdis_format(source, dest, op, next_op, pc);
=======
			uint16_t next_op = READ_OP_DASM(pc + 2);
			uint32_t dis = RRdis_format(source, dest, op, next_op, pc);
>>>>>>> upstream/master

			if( size == 2 )
				size = 4;

			if( source_code == SR_REGISTER && !source_bit )
				strcpy(source,"0");

			if( dest_code == SR_REGISTER && !dest_bit )
			{
				switch( DD( next_op ) )
				{
					case 0:
						// STBS.A
<<<<<<< HEAD
						sprintf(buffer, "STBS.A 0, %s, $%x", source, dis);
=======
						util::stream_format(stream, "STBS.A 0, %s, $%x", source, dis);
>>>>>>> upstream/master
						break;

					case 1:
						// STBU.A
<<<<<<< HEAD
						sprintf(buffer, "STBU.A 0, %s, $%x", source, dis);
=======
						util::stream_format(stream, "STBU.A 0, %s, $%x", source, dis);
>>>>>>> upstream/master
						break;

					case 2:
						// STHS.A
						if( dis & 1 )
						{
<<<<<<< HEAD
							sprintf(buffer, "STHS.A 0, %s, $%x", source, dis & ~1);
=======
							util::stream_format(stream, "STHS.A 0, %s, $%x", source, dis & ~1);
>>>>>>> upstream/master
						}
						// STHU.A
						else
						{
<<<<<<< HEAD
							sprintf(buffer, "STHU.A 0, %s, $%x", source, dis & ~1);
=======
							util::stream_format(stream, "STHU.A 0, %s, $%x", source, dis & ~1);
>>>>>>> upstream/master
						}

						break;

					case 3:
						// STD.IOA
						if( (dis & 3) == 3 )
						{
<<<<<<< HEAD
							sprintf(buffer, "STD.IOA 0, %s, $%x", source, dis & ~3);
=======
							util::stream_format(stream, "STD.IOA 0, %s, $%x", source, dis & ~3);
>>>>>>> upstream/master
						}
						// STW.IOA
						else if( (dis & 3) == 2 )
						{
<<<<<<< HEAD
							sprintf(buffer, "STW.IOA 0, %s, $%x", source, dis & ~3);
=======
							util::stream_format(stream, "STW.IOA 0, %s, $%x", source, dis & ~3);
>>>>>>> upstream/master
						}
						// STD.A
						else if( (dis & 3) == 1 )
						{
<<<<<<< HEAD
							sprintf(buffer, "STD.A 0, %s, $%x", source, dis & ~1);
=======
							util::stream_format(stream, "STD.A 0, %s, $%x", source, dis & ~1);
>>>>>>> upstream/master
						}
						// STW.A
						else
						{
<<<<<<< HEAD
							sprintf(buffer, "STW.A 0, %s, $%x", source, dis & ~1);
=======
							util::stream_format(stream, "STW.A 0, %s, $%x", source, dis & ~1);
>>>>>>> upstream/master
						}

						break;
				}
			}
			else
			{
				switch( DD( next_op ) )
				{
					case 0:
						// STBS.D
<<<<<<< HEAD
						sprintf(buffer, "STBS.D %s, %s, $%x", dest, source, dis);
=======
						util::stream_format(stream, "STBS.D %s, %s, $%x", dest, source, dis);
>>>>>>> upstream/master
						break;

					case 1:
						// STBU.D
<<<<<<< HEAD
						sprintf(buffer, "STBU.D %s, %s, $%x", dest, source, dis);
=======
						util::stream_format(stream, "STBU.D %s, %s, $%x", dest, source, dis);
>>>>>>> upstream/master
						break;

					case 2:
						// STHS.D
						if( dis & 1 )
						{
<<<<<<< HEAD
							sprintf(buffer, "STHS.D %s, %s, $%x", dest, source, dis & ~1);
=======
							util::stream_format(stream, "STHS.D %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
						}
						// STHU.D
						else
						{
<<<<<<< HEAD
							sprintf(buffer, "STHU.D %s, %s, $%x", dest, source, dis & ~1);
=======
							util::stream_format(stream, "STHU.D %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
						}
						break;

					case 3:
						// STD.IOD
						if( (dis & 3) == 3 )
						{
<<<<<<< HEAD
							sprintf(buffer, "STD.IOD %s, %s, $%x", dest, source, dis & ~3);
=======
							util::stream_format(stream, "STD.IOD %s, %s, $%x", dest, source, dis & ~3);
>>>>>>> upstream/master
						}
						// STW.IOD
						else if( (dis & 3) == 2 )
						{
<<<<<<< HEAD
							sprintf(buffer, "STW.IOD %s, %s, $%x", dest, source, dis & ~3);
=======
							util::stream_format(stream, "STW.IOD %s, %s, $%x", dest, source, dis & ~3);
>>>>>>> upstream/master
						}
						// STD.D
						else if( (dis & 3) == 1 )
						{
<<<<<<< HEAD
							sprintf(buffer, "STD.D %s, %s, $%x", dest, source, dis & ~1);
=======
							util::stream_format(stream, "STD.D %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
						}
						// STW.D
						else
						{
<<<<<<< HEAD
							sprintf(buffer, "STW.D %s, %s, $%x", dest, source, dis & ~1);
=======
							util::stream_format(stream, "STW.D %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
						}

						break;
				}
			}

			break;
		}

		// STxx.N/S
		case 0x9c: case 0x9d: case 0x9e: case 0x9f:
		{
<<<<<<< HEAD
			UINT16 next_op = READ_OP_DASM(pc + 2);
			UINT32 dis = RRdis_format(source, dest, op, next_op, pc);
=======
			uint16_t next_op = READ_OP_DASM(pc + 2);
			uint32_t dis = RRdis_format(source, dest, op, next_op, pc);
>>>>>>> upstream/master

			if( size == 2 )
				size = 4;

			if( source_code == SR_REGISTER && !source_bit )
				strcpy(source,"0");

			if( (dest_code == PC_REGISTER && !dest_bit) || (dest_code == SR_REGISTER && !dest_bit) )
			{
<<<<<<< HEAD
				sprintf(buffer, "Reserved");
=======
				util::stream_format(stream, "Reserved");
>>>>>>> upstream/master
				break;
			}

			switch( DD( next_op ) )
			{
				case 0:
					// STBS.N
<<<<<<< HEAD
					sprintf(buffer, "STBS.N %s, %s, $%x", dest, source, dis);
=======
					util::stream_format(stream, "STBS.N %s, %s, $%x", dest, source, dis);
>>>>>>> upstream/master
					break;

				case 1:
					// STBU.N
<<<<<<< HEAD
					sprintf(buffer, "STBU.N %s, %s, $%x", dest, source, dis);
=======
					util::stream_format(stream, "STBU.N %s, %s, $%x", dest, source, dis);
>>>>>>> upstream/master
					break;

				case 2:
					// STHS.N
					if( dis & 1 )
					{
<<<<<<< HEAD
						sprintf(buffer, "STHS.N %s, %s, $%x", dest, source, dis & ~1);
=======
						util::stream_format(stream, "STHS.N %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
					}
					// STHU.N
					else
					{
<<<<<<< HEAD
						sprintf(buffer, "STHU.N %s, %s, $%x", dest, source, dis & ~1);
=======
						util::stream_format(stream, "STHU.N %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
					}

					break;

				case 3:
					// STW.S
					if( (dis & 3) == 3 )
					{
<<<<<<< HEAD
						sprintf(buffer, "STW.S %s, %s, $%x", dest, source, dis & ~3);
=======
						util::stream_format(stream, "STW.S %s, %s, $%x", dest, source, dis & ~3);
>>>>>>> upstream/master
					}
					// Reserved
					else if( (dis & 3) == 2 )
					{
<<<<<<< HEAD
						sprintf(buffer, "Reserved");
=======
						util::stream_format(stream, "Reserved");
>>>>>>> upstream/master
					}
					// STD.N
					else if( (dis & 3) == 1 )
					{
<<<<<<< HEAD
						sprintf(buffer, "STD.N %s, %s, $%x", dest, source, dis & ~1);
=======
						util::stream_format(stream, "STD.N %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
					}
					// STW.N
					else
					{
<<<<<<< HEAD
						sprintf(buffer, "STW.N %s, %s, $%x", dest, source, dis & ~1);
=======
						util::stream_format(stream, "STW.N %s, %s, $%x", dest, source, dis & ~1);
>>>>>>> upstream/master
					}

					break;
			}

			break;
		}

		// SHRI
		case 0xa0: case 0xa1: case 0xa2: case 0xa3:
		{
<<<<<<< HEAD
			UINT8 n = Rn_format(dest, op);

			sprintf(buffer, "SHRI %s, $%x", dest, n);
=======
			uint8_t n = Rn_format(dest, op);

			util::stream_format(stream, "SHRI %s, $%x", dest, n);
>>>>>>> upstream/master

			break;
		}

		// SARI
		case 0xa4: case 0xa5: case 0xa6: case 0xa7:
		{
<<<<<<< HEAD
			UINT8 n = Rn_format(dest, op);

			sprintf(buffer, "SARI %s, $%x", dest, n);
=======
			uint8_t n = Rn_format(dest, op);

			util::stream_format(stream, "SARI %s, $%x", dest, n);
>>>>>>> upstream/master

			break;
		}

		// SHLI
		case 0xa8: case 0xa9: case 0xaa: case 0xab:
		{
<<<<<<< HEAD
			UINT8 n = Rn_format(dest, op);

			sprintf(buffer, "SHLI %s, $%x", dest, n);
=======
			uint8_t n = Rn_format(dest, op);

			util::stream_format(stream, "SHLI %s, $%x", dest, n);
>>>>>>> upstream/master

			break;
		}

		// MULU
		case 0xb0: case 0xb1: case 0xb2: case 0xb3:

			RR_format(source, dest, op, 0);

<<<<<<< HEAD
			sprintf(buffer, "MULU %s, %s", dest, source);
=======
			util::stream_format(stream, "MULU %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// MULS
		case 0xb4: case 0xb5: case 0xb6: case 0xb7:

			RR_format(source, dest, op, 0);

<<<<<<< HEAD
			sprintf(buffer, "MULS %s, %s", dest, source);
=======
			util::stream_format(stream, "MULS %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// SETxx - SETADR - FETCH
		case 0xb8: case 0xb9: case 0xba: case 0xbb:
		{
<<<<<<< HEAD
			UINT8 n = Rn_format(dest, op);

			if( dest_code == PC_REGISTER && !dest_bit )
			{
				sprintf(buffer, "Illegal PC: $%x OP: $%x", pc, op);
			}
			else if( dest_code == SR_REGISTER && !dest_bit )
			{
				sprintf(buffer, "FETCH $%x", (n / 2) + 1);
			}
			else
			{
				sprintf(buffer, "%s %s", SETxx[n], dest);
=======
			uint8_t n = Rn_format(dest, op);

			if( dest_code == PC_REGISTER && !dest_bit )
			{
				util::stream_format(stream, "Illegal PC: $%x OP: $%x", pc, op);
			}
			else if( dest_code == SR_REGISTER && !dest_bit )
			{
				util::stream_format(stream, "FETCH $%x", (n / 2) + 1);
			}
			else
			{
				util::stream_format(stream, "%s %s", SETxx[n], dest);
>>>>>>> upstream/master
			}

			break;
		}

		// MUL
		case 0xbc: case 0xbd: case 0xbe: case 0xbf:

			RR_format(source, dest, op, 0);

<<<<<<< HEAD
			sprintf(buffer, "MUL %s, %s", dest, source);
=======
			util::stream_format(stream, "MUL %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// FADD
		case 0xc0:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "FADD %s, %s", dest, source);
=======
			util::stream_format(stream, "FADD %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// FADDD
		case 0xc1:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "FADDD %s, %s", dest, source);
=======
			util::stream_format(stream, "FADDD %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// FSUB
		case 0xc2:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "FSUB %s, %s", dest, source);
=======
			util::stream_format(stream, "FSUB %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// FSUBD
		case 0xc3:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "FSUBD %s, %s", dest, source);
=======
			util::stream_format(stream, "FSUBD %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// FMUL
		case 0xc4:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "FMUL %s, %s", dest, source);
=======
			util::stream_format(stream, "FMUL %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// FMULD
		case 0xc5:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "FMULD %s, %s", dest, source);
=======
			util::stream_format(stream, "FMULD %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// FDIV
		case 0xc6:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "FDIV %s, %s", dest, source);
=======
			util::stream_format(stream, "FDIV %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// FDIVD
		case 0xc7:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "FDIVD %s, %s", dest, source);
=======
			util::stream_format(stream, "FDIVD %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// FCMP
		case 0xc8:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "FCMP %s, %s", dest, source);
=======
			util::stream_format(stream, "FCMP %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// FCMPD
		case 0xc9:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "FCMPD %s, %s", dest, source);
=======
			util::stream_format(stream, "FCMPD %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// FCMPU
		case 0xca:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "FCMPU %s, %s", dest, source);
=======
			util::stream_format(stream, "FCMPU %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// FCMPUD
		case 0xcb:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "FCMPUD %s, %s", dest, source);
=======
			util::stream_format(stream, "FCMPUD %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// FCVT
		case 0xcc:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "FCVT %s, %s", dest, source);
=======
			util::stream_format(stream, "FCVT %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// FCVTD
		case 0xcd:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "FCVTD %s, %s", dest, source);
=======
			util::stream_format(stream, "FCVTD %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// EXTEND
		case 0xce:
		{
<<<<<<< HEAD
			UINT16 extended_op;
=======
			uint16_t extended_op;
>>>>>>> upstream/master

			LL_format(source, dest, op);

			pc += 2;
			extended_op = READ_OP_DASM(pc);

			size = 4;

			switch( extended_op )
			{
			case 0x100:
			case EMUL:
<<<<<<< HEAD
				sprintf(buffer, "EMUL %s, %s", dest, source);
				break;

			case EMULU:
				sprintf(buffer, "EMULU %s, %s", dest, source);
				break;

			case EMULS:
				sprintf(buffer, "EMULS %s, %s", dest, source);
				break;

			case EMAC:
				sprintf(buffer, "EMAC %s, %s", dest, source);
				break;

			case EMACD:
				sprintf(buffer, "EMACD %s, %s", dest, source);
				break;

			case EMSUB:
				sprintf(buffer, "EMSUB %s, %s", dest, source);
				break;

			case EMSUBD:
				sprintf(buffer, "EMSUBD %s, %s", dest, source);
				break;

			case EHMAC:
				sprintf(buffer, "EHMAC %s, %s", dest, source);
				break;

			case EHMACD:
				sprintf(buffer, "EHMACD %s, %s", dest, source);
				break;

			case EHCMULD:
				sprintf(buffer, "EHCMULD %s, %s", dest, source);
				break;

			case EHCMACD:
				sprintf(buffer, "EHCMACD %s, %s", dest, source);
				break;

			case EHCSUMD:
				sprintf(buffer, "EHCSUMD %s, %s", dest, source);
				break;

			case EHCFFTD:
				sprintf(buffer, "EHCFFTD %s, %s", dest, source);
				break;

			case EHCFFTSD:
				sprintf(buffer, "EHCFFTSD %s, %s", dest, source);
				break;

			default:
				sprintf(buffer, "Ext. OP $%X @ %X\n", extended_op, pc);
				osd_printf_verbose(buffer, "Illegal Extended Opcode: %X @ %X\n", extended_op, pc);
=======
				util::stream_format(stream, "EMUL %s, %s", dest, source);
				break;

			case EMULU:
				util::stream_format(stream, "EMULU %s, %s", dest, source);
				break;

			case EMULS:
				util::stream_format(stream, "EMULS %s, %s", dest, source);
				break;

			case EMAC:
				util::stream_format(stream, "EMAC %s, %s", dest, source);
				break;

			case EMACD:
				util::stream_format(stream, "EMACD %s, %s", dest, source);
				break;

			case EMSUB:
				util::stream_format(stream, "EMSUB %s, %s", dest, source);
				break;

			case EMSUBD:
				util::stream_format(stream, "EMSUBD %s, %s", dest, source);
				break;

			case EHMAC:
				util::stream_format(stream, "EHMAC %s, %s", dest, source);
				break;

			case EHMACD:
				util::stream_format(stream, "EHMACD %s, %s", dest, source);
				break;

			case EHCMULD:
				util::stream_format(stream, "EHCMULD %s, %s", dest, source);
				break;

			case EHCMACD:
				util::stream_format(stream, "EHCMACD %s, %s", dest, source);
				break;

			case EHCSUMD:
				util::stream_format(stream, "EHCSUMD %s, %s", dest, source);
				break;

			case EHCFFTD:
				util::stream_format(stream, "EHCFFTD %s, %s", dest, source);
				break;

			case EHCFFTSD:
				util::stream_format(stream, "EHCFFTSD %s, %s", dest, source);
				break;

			default:
				util::stream_format(stream, "Ext. OP $%X @ %X\n", extended_op, pc);
				osd_printf_verbose("Illegal Extended Opcode: %X @ %X\n", extended_op, pc);
>>>>>>> upstream/master
				break;
			}

			break;
		}

		// DO
		case 0xcf:

			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "DO %s, %s", dest, source);
=======
			util::stream_format(stream, "DO %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// LDW.R
		case 0xd0: case 0xd1:

			LR_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "LDW.R %s, %s", dest, source);
=======
			util::stream_format(stream, "LDW.R %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// LDD.R
		case 0xd2: case 0xd3:

			LR_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "LDD.R %s, %s", dest, source);
=======
			util::stream_format(stream, "LDD.R %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// LDW.P
		case 0xd4: case 0xd5:

			LR_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "LDW.P %s, %s", dest, source);
=======
			util::stream_format(stream, "LDW.P %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// LDD.P
		case 0xd6: case 0xd7:

			LR_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "LDD.P %s, %s", dest, source);
=======
			util::stream_format(stream, "LDD.P %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// STW.R
		case 0xd8: case 0xd9:

			LR_format(source, dest, op);

			if( source_code == SR_REGISTER && !source_bit )
				strcpy(source,"0");

<<<<<<< HEAD
			sprintf(buffer, "STW.R %s, %s", dest, source);
=======
			util::stream_format(stream, "STW.R %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// STD.R
		case 0xda: case 0xdb:

			LR_format(source, dest, op);

			if( source_code == SR_REGISTER && !source_bit )
				strcpy(source,"0");

<<<<<<< HEAD
			sprintf(buffer, "STD.R %s, %s", dest, source);
=======
			util::stream_format(stream, "STD.R %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// STW.P
		case 0xdc: case 0xdd:

			LR_format(source, dest, op);

			if( source_code == SR_REGISTER && !source_bit )
				strcpy(source,"0");

<<<<<<< HEAD
			sprintf(buffer, "STW.P %s, %s", dest, source);
=======
			util::stream_format(stream, "STW.P %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// STD.P
		case 0xde: case 0xdf:

			LR_format(source, dest, op);

			if( source_code == SR_REGISTER && !source_bit )
				strcpy(source,"0");

<<<<<<< HEAD
			sprintf(buffer, "STD.P %s, %s", dest, source);
=======
			util::stream_format(stream, "STD.P %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// DBV
		case 0xe0:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "DBV $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "DBV $%x", rel);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1);

			break;
		}

		// DBNV
		case 0xe1:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "DBNV $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "DBNV $%x", rel);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1);

			break;
		}

		// DBE
		case 0xe2:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "DBE $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "DBE $%x", rel);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1);

			break;
		}

		// DBNE
		case 0xe3:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "DBNE $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "DBNE $%x", rel);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1);

			break;
		}

		// DBC
		case 0xe4:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "DBC $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "DBC $%x", rel);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1);

			break;
		}

		// DBNC
		case 0xe5:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "DBNC $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "DBNC $%x", rel);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1);

			break;
		}

		// DBSE
		case 0xe6:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "DBSE $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "DBSE $%x", rel);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1);

			break;
		}

		// DBHT
		case 0xe7:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "DBHT $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "DBHT $%x", rel);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1);

			break;
		}

		// DBN
		case 0xe8:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "DBN $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "DBN $%x", rel);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1);

			break;
		}

		// DBNN
		case 0xe9:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "DBNN $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "DBNN $%x", rel);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1);

			break;
		}

		// DBLE
		case 0xea:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "DBLE $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "DBLE $%x", rel);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1);

			break;
		}

		// DBGT
		case 0xeb:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "DBGT $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "DBGT $%x", rel);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1);

			break;
		}

		// DBR
		case 0xec:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "DBR $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "DBR $%x", rel);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1);

			break;
		}

		// FRAME
		case 0xed:

			global_fp = 0;
			LL_format(source, dest, op);

<<<<<<< HEAD
			sprintf(buffer, "FRAME %s, %s", dest, source);
=======
			util::stream_format(stream, "FRAME %s, %s", dest, source);
>>>>>>> upstream/master

			break;

		// CALL
		case 0xee: case 0xef:
		{
<<<<<<< HEAD
			UINT32 const_val = LRconst_format(source, dest, op, &pc);

			if( source_code == SR_REGISTER && !source_bit )
			{
				sprintf(buffer, "CALL %s, 0, $%x", dest, const_val);
=======
			uint32_t const_val = LRconst_format(source, dest, op, &pc);

			if( source_code == SR_REGISTER && !source_bit )
			{
				util::stream_format(stream, "CALL %s, 0, $%x", dest, const_val);
>>>>>>> upstream/master
				flags = DASMFLAG_STEP_OVER;
			}
			else
			{
<<<<<<< HEAD
				sprintf(buffer, "CALL %s, %s, $%x", dest, source, const_val);
=======
				util::stream_format(stream, "CALL %s, %s, $%x", dest, source, const_val);
>>>>>>> upstream/master
				flags = DASMFLAG_STEP_OVER;
			}

			break;
		}

		// BV
		case 0xf0:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "BV $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "BV $%x", rel);
>>>>>>> upstream/master

			break;
		}

		// BNV
		case 0xf1:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "BNV $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "BNV $%x", rel);
>>>>>>> upstream/master

			break;
		}

		// BE
		case 0xf2:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "BE $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "BE $%x", rel);
>>>>>>> upstream/master

			break;
		}

		// BNE
		case 0xf3:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "BNE $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "BNE $%x", rel);
>>>>>>> upstream/master

			break;
		}

		// BC
		case 0xf4:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "BC $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "BC $%x", rel);
>>>>>>> upstream/master

			break;
		}

		// BNC
		case 0xf5:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "BNC $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "BNC $%x", rel);
>>>>>>> upstream/master

			break;
		}

		// BSE
		case 0xf6:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "BSE $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "BSE $%x", rel);
>>>>>>> upstream/master

			break;
		}

		// BHT
		case 0xf7:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "BHT $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "BHT $%x", rel);
>>>>>>> upstream/master

			break;
		}

		// BN
		case 0xf8:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "BN $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "BN $%x", rel);
>>>>>>> upstream/master

			break;
		}

		// BNN
		case 0xf9:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "BNN $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "BNN $%x", rel);
>>>>>>> upstream/master

			break;
		}

		// BLE
		case 0xfa:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "BLE $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "BLE $%x", rel);
>>>>>>> upstream/master

			break;
		}

		// BGT
		case 0xfb:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "BGT $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "BGT $%x", rel);
>>>>>>> upstream/master

			break;
		}

		// BR
		case 0xfc:
		{
<<<<<<< HEAD
			INT32 rel = PCrel_format(op, pc) + 2;

			sprintf(buffer, "BR $%x", rel);
=======
			int32_t rel = PCrel_format(op, pc) + 2;

			util::stream_format(stream, "BR $%x", rel);
>>>>>>> upstream/master

			break;
		}

		// TRAPxx - TRAP
		case 0xfd: case 0xfe: case 0xff:
		{
<<<<<<< HEAD
			UINT8 code = ((op & 0x300) >> 6) | (op & 0x03);
			UINT8 trapno = (op & 0xfc) >> 2;
=======
			uint8_t code = ((op & 0x300) >> 6) | (op & 0x03);
			uint8_t trapno = (op & 0xfc) >> 2;
>>>>>>> upstream/master

			switch( code )
			{
				case TRAPLE:
<<<<<<< HEAD
					sprintf(buffer, "TRAPLE %d", trapno);
=======
					util::stream_format(stream, "TRAPLE %d", trapno);
>>>>>>> upstream/master
					flags = DASMFLAG_STEP_OVER;

					break;

				case TRAPGT:
<<<<<<< HEAD
					sprintf(buffer, "TRAPGT %d", trapno);
=======
					util::stream_format(stream, "TRAPGT %d", trapno);
>>>>>>> upstream/master
					flags = DASMFLAG_STEP_OVER;

					break;

				case TRAPLT:
<<<<<<< HEAD
					sprintf(buffer, "TRAPLT %d", trapno);
=======
					util::stream_format(stream, "TRAPLT %d", trapno);
>>>>>>> upstream/master
					flags = DASMFLAG_STEP_OVER;

					break;

				case TRAPGE:
<<<<<<< HEAD
					sprintf(buffer, "TRAPGE %d", trapno);
=======
					util::stream_format(stream, "TRAPGE %d", trapno);
>>>>>>> upstream/master
					flags = DASMFLAG_STEP_OVER;

					break;

				case TRAPSE:
<<<<<<< HEAD
					sprintf(buffer, "TRAPSE %d", trapno);
=======
					util::stream_format(stream, "TRAPSE %d", trapno);
>>>>>>> upstream/master
					flags = DASMFLAG_STEP_OVER;

					break;

				case TRAPHT:
<<<<<<< HEAD
					sprintf(buffer, "TRAPHT %d", trapno);
=======
					util::stream_format(stream, "TRAPHT %d", trapno);
>>>>>>> upstream/master
					flags = DASMFLAG_STEP_OVER;

					break;

				case TRAPST:
<<<<<<< HEAD
					sprintf(buffer, "TRAPST %d", trapno);
=======
					util::stream_format(stream, "TRAPST %d", trapno);
>>>>>>> upstream/master
					flags = DASMFLAG_STEP_OVER;

					break;

				case TRAPHE:
<<<<<<< HEAD
					sprintf(buffer, "TRAPHE %d", trapno);
=======
					util::stream_format(stream, "TRAPHE %d", trapno);
>>>>>>> upstream/master
					flags = DASMFLAG_STEP_OVER;

					break;

				case TRAPE:
<<<<<<< HEAD
					sprintf(buffer, "TRAPE %d", trapno);
=======
					util::stream_format(stream, "TRAPE %d", trapno);
>>>>>>> upstream/master
					flags = DASMFLAG_STEP_OVER;

					break;

				case TRAPNE:
<<<<<<< HEAD
					sprintf(buffer, "TRAPNE %d", trapno);
=======
					util::stream_format(stream, "TRAPNE %d", trapno);
>>>>>>> upstream/master
					flags = DASMFLAG_STEP_OVER;

					break;

				case TRAPV:
<<<<<<< HEAD
					sprintf(buffer, "TRAPV %d", trapno);
=======
					util::stream_format(stream, "TRAPV %d", trapno);
>>>>>>> upstream/master
					flags = DASMFLAG_STEP_OVER;

					break;

				case TRAP:
<<<<<<< HEAD
					sprintf(buffer, "TRAP %d", trapno);
=======
					util::stream_format(stream, "TRAP %d", trapno);
>>>>>>> upstream/master
					flags = DASMFLAG_STEP_OVER;

					break;
			}

			break;
		}
	}

	return size | flags | DASMFLAG_SUPPORTED;
}

CPU_DISASSEMBLE( hyperstone_generic )
{
<<<<<<< HEAD
	return dasm_hyperstone( buffer, pc, oprom, 0, 0 );
=======
	return dasm_hyperstone( stream, pc, oprom, 0, 0 );
>>>>>>> upstream/master
}
