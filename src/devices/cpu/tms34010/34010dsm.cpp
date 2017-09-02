// license:BSD-3-Clause
// copyright-holders:Zsolt Vasvari
/*
 *   A TMS34010 disassembler
 *
 *   This code written by Zsolt Vasvari for the MAME project
 *
 */

#include "emu.h"

#ifdef STANDALONE
#define PC __pc + (offset << 3)
#define OP_WORD(v) { v = filebuf[_pc>>3]; _pc += 8; v = v | (filebuf[_pc>>3] << 8); _pc += 8;}
#define PARAM_WORD(v) { v = filebuf[_pc>>3]; _pc += 8; v = v | (filebuf[_pc>>3] << 8); _pc += 8;}
#define PARAM_LONG(v) { int v1, v2; PARAM_WORD(v1); PARAM_WORD(v2); v = v1 | (v2 << 16); }
#else
#define PC __pc
#define OP_WORD(v) { v = rombase[(__pc - pcbase) >> 3] | (rombase[(__pc + 8 - pcbase) >> 3] << 8); _pc += 16; }
#define PARAM_WORD(v) { v = rambase[(__pc + 16 - pcbase) >> 3] | (rambase[(__pc + 24 - pcbase) >> 3] << 8); _pc += 16; }
#define PARAM_LONG(v) { v = rambase[(__pc + 16 - pcbase) >> 3] | (rambase[(__pc + 24 - pcbase) >> 3] << 8) | (rambase[(__pc + 32 - pcbase) >> 3] << 16) | (rambase[(__pc + 40 - pcbase) >> 3] << 24); _pc += 32; }
<<<<<<< HEAD
#endif

static UINT8 rf;
static UINT32 __pc, _pc;
static UINT16 op,rs,rd;

static char *buffer;
static char temp[20];

static const UINT8 *rombase;
static const UINT8 *rambase;
static offs_t pcbase;


static void print_reg(UINT8 reg)
{
	if (reg != 0x0f)
	{
		sprintf(temp, "%c%d", rf, reg);
		strcat(buffer, temp);
	}
	else
	{
		strcat(buffer, "SP");
	}
}

static void print_src_reg(void)
{
	print_reg(rs);
}

static void print_des_reg(void)
{
	print_reg(rd);
}

static void print_src_des_reg(void)
{
	print_src_reg();
	strcat(buffer, ",");
	print_des_reg();
}

static void print_word_parm(void)
{
	UINT16 w;

	PARAM_WORD(w);

	sprintf(temp, "%Xh", w);
	strcat(buffer, temp);
}

static void print_word_parm_1s_comp(void)
{
	UINT16 w;

	PARAM_WORD(w);
	w = ~w;
	sprintf(temp, "%Xh", w);
	strcat(buffer, temp);
}

static void print_long_parm(void)
{
	UINT32 l;

	PARAM_LONG(l);
	sprintf(temp, "%Xh", l);
	strcat(buffer, temp);
}

static void print_long_parm_1s_comp(void)
{
	UINT32 l;

	PARAM_LONG(l);
	sprintf(temp, "%Xh", ~l);
	strcat(buffer, temp);
}

static void print_constant(void)
{
	UINT8 constant = (op >> 5) & 0x1f;

	sprintf(temp, "%Xh", constant);
	strcat(buffer, temp);
}

static void print_constant_1_32(void)
{
	UINT8 constant = (op >> 5) & 0x1f;
	if (!constant) constant = 0x20;

	sprintf(temp, "%Xh", constant);
	strcat(buffer, temp);
}

static void print_constant_1s_comp(void)
{
	UINT8 constant = (~op >> 5) & 0x1f;

	sprintf(temp, "%Xh", constant);
	strcat(buffer, temp);
}

static void print_constant_2s_comp(void)
{
	UINT8 constant = 32 - ((op >> 5) & 0x1f);

	sprintf(temp, "%Xh", constant);
	strcat(buffer, temp);
}

static void print_relative(void)
{
	UINT16 l;
	INT16 ls;

	PARAM_WORD(l);
	ls = (INT16)l;

	sprintf(temp, "%Xh", PC + 32 + (ls << 4));
	strcat(buffer, temp);
}

static void print_relative_8bit(void)
{
	INT8 ls = (INT8)op;

	sprintf(temp, "%Xh", PC + 16 + (ls << 4));
	strcat(buffer, temp);
}

static void print_relative_5bit(void)
{
	INT8 ls = (INT8)((op >> 5) & 0x1f);
	if (op & 0x0400) ls = -ls;

	sprintf(temp, "%Xh", PC + 16 + (ls << 4));
	strcat(buffer, temp);
}

static void print_field(void)
{
	sprintf(temp, "%c", (op & 0x200) ? '1' : '0');
	strcat(buffer, temp);
}

static void print_condition_code(void)
{
	switch (op & 0x0f00)
	{
	case 0x0000: strcat(buffer, "  "); break;  /* This is really UC (Unconditional) */
	case 0x0100: strcat(buffer, "P "); break;
	case 0x0200: strcat(buffer, "LS"); break;
	case 0x0300: strcat(buffer, "HI"); break;
	case 0x0400: strcat(buffer, "LT"); break;
	case 0x0500: strcat(buffer, "GE"); break;
	case 0x0600: strcat(buffer, "LE"); break;
	case 0x0700: strcat(buffer, "GT"); break;
	case 0x0800: strcat(buffer, "C "); break;
	case 0x0900: strcat(buffer, "NC"); break;
	case 0x0a00: strcat(buffer, "EQ"); break;
	case 0x0b00: strcat(buffer, "NE"); break;
	case 0x0c00: strcat(buffer, "V "); break;
	case 0x0d00: strcat(buffer, "NV"); break;
	case 0x0e00: strcat(buffer, "N "); break;
	case 0x0f00: strcat(buffer, "NN"); break;
	}
}

static void print_reg_list_range(INT8 first, INT8 last)
=======
#define PARM2_LONG(v) { v = rambase[(__pc + 48 - pcbase) >> 3] | (rambase[(__pc + 56 - pcbase) >> 3] << 8) | (rambase[(__pc + 64 - pcbase) >> 3] << 16) | (rambase[(__pc + 72 - pcbase) >> 3] << 24); _pc += 32; }
#endif

static uint8_t rf;
static uint32_t __pc, _pc;
static uint16_t op,rs,rd;

static const uint8_t *rombase;
static const uint8_t *rambase;
static offs_t pcbase;


static void print_reg(std::ostream &stream, uint8_t reg)
{
	if (reg != 0x0f)
	{
		util::stream_format(stream, "%c%d", rf, reg);
	}
	else
	{
		stream << "SP";
	}
}

static void print_src_reg(std::ostream &stream)
{
	print_reg(stream, rs);
}

static void print_des_reg(std::ostream &stream)
{
	print_reg(stream, rd);
}

static void print_src_des_reg(std::ostream &stream)
{
	print_src_reg(stream);
	stream << ",";
	print_des_reg(stream);
}

static void print_word_parm(std::ostream &stream)
{
	uint16_t w;

	PARAM_WORD(w);

	util::stream_format(stream, "%Xh", w);
}

static void print_word_parm_1s_comp(std::ostream &stream)
{
	uint16_t w;

	PARAM_WORD(w);
	w = ~w;
	util::stream_format(stream, "%Xh", w);
}

static void print_long_parm(std::ostream &stream)
{
	uint32_t l;

	PARAM_LONG(l);
	util::stream_format(stream, "%Xh", l);
}

static void print_long_parm2(std::ostream &stream)
{
	uint32_t l;

	PARM2_LONG(l);
	util::stream_format(stream, "%Xh", l);
}

static void print_long_parm_1s_comp(std::ostream &stream)
{
	uint32_t l;

	PARAM_LONG(l);
	util::stream_format(stream, "%Xh", ~l);
}

static void print_constant(std::ostream &stream)
{
	uint8_t constant = (op >> 5) & 0x1f;

	util::stream_format(stream, "%Xh", constant);
}

static void print_constant_1_32(std::ostream &stream)
{
	uint8_t constant = (op >> 5) & 0x1f;
	if (!constant) constant = 0x20;

	util::stream_format(stream, "%Xh", constant);
}

static void print_constant_1s_comp(std::ostream &stream)
{
	uint8_t constant = (~op >> 5) & 0x1f;

	util::stream_format(stream, "%Xh", constant);
}

static void print_constant_2s_comp(std::ostream &stream)
{
	uint8_t constant = 32 - ((op >> 5) & 0x1f);

	util::stream_format(stream, "%Xh", constant);
}

static void print_relative(std::ostream &stream)
{
	uint16_t l;
	int16_t ls;

	PARAM_WORD(l);
	ls = (int16_t)l;

	util::stream_format(stream, "%Xh", PC + 32 + (ls << 4));
}

static void print_relative_8bit(std::ostream &stream)
{
	int8_t ls = (int8_t)op;

	util::stream_format(stream, "%Xh", PC + 16 + (ls << 4));
}

static void print_relative_5bit(std::ostream &stream)
{
	int8_t ls = (int8_t)((op >> 5) & 0x1f);
	if (op & 0x0400) ls = -ls;

	util::stream_format(stream, "%Xh", PC + 16 + (ls << 4));
}

static void print_field(std::ostream &stream)
{
	util::stream_format(stream, "%c", (op & 0x200) ? '1' : '0');
}

static void print_condition_code(std::ostream &stream)
{
	switch (op & 0x0f00)
	{
	case 0x0000: stream << "  "; break;  /* This is really UC (Unconditional) */
	case 0x0100: stream << "P "; break;
	case 0x0200: stream << "LS"; break;
	case 0x0300: stream << "HI"; break;
	case 0x0400: stream << "LT"; break;
	case 0x0500: stream << "GE"; break;
	case 0x0600: stream << "LE"; break;
	case 0x0700: stream << "GT"; break;
	case 0x0800: stream << "C "; break;
	case 0x0900: stream << "NC"; break;
	case 0x0a00: stream << "EQ"; break;
	case 0x0b00: stream << "NE"; break;
	case 0x0c00: stream << "V "; break;
	case 0x0d00: stream << "NV"; break;
	case 0x0e00: stream << "N "; break;
	case 0x0f00: stream << "NN"; break;
	}
}

static void print_reg_list_range(std::ostream &stream, int8_t first, int8_t last)
>>>>>>> upstream/master
{
	if ((first != -1 ) && (first != last))
	{
		if ((last - first) == 1)
<<<<<<< HEAD
			strcat(buffer, ",");
		else
			strcat(buffer, "-");
		print_reg(last);
	}
}

static void print_reg_list(UINT16 rev)
{
	UINT16 l;
	UINT8 i;
	INT8 first = -1, last = 0;
=======
			stream << ",";
		else
			stream << "-";
		print_reg(stream, last);
	}
}

static void print_reg_list(std::ostream &stream, uint16_t rev)
{
	uint16_t l;
	uint8_t i;
	int8_t first = -1, last = 0;
>>>>>>> upstream/master

	PARAM_WORD(l);

	for (i = 0; i  < 16; i++)
	{
		int moved;

		if (rev)
		{
			moved = l & 0x8000;
			l <<= 1;
		}
		else
		{
			moved = l & 0x01;
			l >>= 1;
		}

		if (moved)
		{
			if (first == -1)
			{
<<<<<<< HEAD
				strcat(buffer, ",");
				print_reg(i);
=======
				stream << ",";
				print_reg(stream, i);
>>>>>>> upstream/master
				first = i;
			}
			last = i;
		}
		else
		{
<<<<<<< HEAD
			print_reg_list_range(first, last);
=======
			print_reg_list_range(stream, first, last);
>>>>>>> upstream/master
			first = -1;
		}
	}

<<<<<<< HEAD
	print_reg_list_range(first, last);
}


static unsigned Dasm340x0(char *buff, UINT32 pc, int is_34020)
{
	int flags = 0;
	UINT8 bad = 0;
	UINT16 subop;

	__pc = _pc = pc;
	buffer = buff;
=======
	print_reg_list_range(stream, first, last);
}


static unsigned Dasm340x0(std::ostream &stream, uint32_t pc, bool is_34020)
{
	int flags = 0;
	uint8_t bad = 0;
	uint16_t subop;

	__pc = _pc = pc;
>>>>>>> upstream/master

	OP_WORD(op);

	subop = (op & 0x01e0);
	rs = (op >> 5) & 0x0f;          /* Source register */
	rd =  op & 0x0f;                /* Destination register */
	rf = ((op & 0x10) ? 'B' : 'A'); /* Register file */

	switch (op & 0xfe00)
	{
	case 0x0000:
		switch (subop)
		{
		case 0x0020:
<<<<<<< HEAD
			sprintf (buffer, "REV    ");
			print_des_reg();
=======
			util::stream_format(stream, "REV    ");
			print_des_reg(stream);
>>>>>>> upstream/master
			break;

		case 0x0040:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "IDLE   ");
=======
				util::stream_format(stream, "IDLE   ");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x0080:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "MWAIT  ");
=======
				util::stream_format(stream, "MWAIT  ");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x00e0:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "BLMOVE %d,%d", (op >> 1) & 1, op & 1);
=======
				util::stream_format(stream, "BLMOVE %d,%d", (op >> 1) & 1, op & 1);
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x0100:
<<<<<<< HEAD
			sprintf (buffer, "EMU    ");
			break;

		case 0x0120:
			sprintf (buffer, "EXGPC  ");
			print_des_reg();
			break;

		case 0x0140:
			sprintf (buffer, "GETPC  ");
			print_des_reg();
			break;

		case 0x0160:
			sprintf (buffer, "JUMP   ");
			print_des_reg();
			break;

		case 0x0180:
			sprintf (buffer, "GETST  ");
			print_des_reg();
			break;

		case 0x01a0:
			sprintf (buffer, "PUTST  ");
			print_des_reg();
			break;

		case 0x01c0:
			sprintf (buffer, "POPST  ");
			break;

		case 0x01e0:
			sprintf (buffer, "PUSHST ");
=======
			util::stream_format(stream, "EMU    ");
			break;

		case 0x0120:
			util::stream_format(stream, "EXGPC  ");
			print_des_reg(stream);
			break;

		case 0x0140:
			util::stream_format(stream, "GETPC  ");
			print_des_reg(stream);
			break;

		case 0x0160:
			util::stream_format(stream, "JUMP   ");
			print_des_reg(stream);
			break;

		case 0x0180:
			util::stream_format(stream, "GETST  ");
			print_des_reg(stream);
			break;

		case 0x01a0:
			util::stream_format(stream, "PUTST  ");
			print_des_reg(stream);
			break;

		case 0x01c0:
			util::stream_format(stream, "POPST  ");
			break;

		case 0x01e0:
			util::stream_format(stream, "PUSHST ");
>>>>>>> upstream/master
			break;

		default:
			bad = 1;
		}
		break;


	case 0x0200:
		switch (subop)
		{
		case 0x0040:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "SETCSP ");
=======
				util::stream_format(stream, "SETCSP ");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x0060:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "SETCDP ");
=======
				util::stream_format(stream, "SETCDP ");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x0080:
			if (is_34020)
			{
<<<<<<< HEAD
				sprintf (buffer, "RPIX   ");
				print_des_reg();
=======
				util::stream_format(stream, "RPIX   ");
				print_des_reg(stream);
>>>>>>> upstream/master
			}
			else
				bad = 1;
			break;

		case 0x00a0:
			if (is_34020)
			{
<<<<<<< HEAD
				sprintf (buffer, "EXGPS  ");
				print_des_reg();
=======
				util::stream_format(stream, "EXGPS  ");
				print_des_reg(stream);
>>>>>>> upstream/master
			}
			else
				bad = 1;
			break;

		case 0x00c0:
			if (is_34020)
			{
<<<<<<< HEAD
				sprintf (buffer, "GETPS  ");
				print_des_reg();
=======
				util::stream_format(stream, "GETPS  ");
				print_des_reg(stream);
>>>>>>> upstream/master
			}
			else
				bad = 1;
			break;

		case 0x00e0:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "SETCMP ");
=======
				util::stream_format(stream, "SETCMP ");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x0100:
<<<<<<< HEAD
			sprintf (buffer, "NOP    ");
			break;

		case 0x0120:
			sprintf (buffer, "CLRC   ");
			break;

		case 0x0140:
			sprintf (buffer, "MOVB   @");
			print_long_parm();
			strcat(buffer, ",@");
			print_long_parm();
			break;

		case 0x0160:
			sprintf (buffer, "DINT   ");
			break;

		case 0x0180:
			sprintf (buffer, "ABS    ");
			print_des_reg();
			break;

		case 0x01a0:
			sprintf (buffer, "NEG    ");
			print_des_reg();
			break;

		case 0x01c0:
			sprintf (buffer, "NEGB   ");
			print_des_reg();
			break;

		case 0x01e0:
			sprintf (buffer, "NOT    ");
			print_des_reg();
=======
			util::stream_format(stream, "NOP    ");
			break;

		case 0x0120:
			util::stream_format(stream, "CLRC   ");
			break;

		case 0x0140:
			util::stream_format(stream, "MOVB   @");
			print_long_parm(stream);
			stream << ",@";
			print_long_parm2(stream);
			break;

		case 0x0160:
			util::stream_format(stream, "DINT   ");
			break;

		case 0x0180:
			util::stream_format(stream, "ABS    ");
			print_des_reg(stream);
			break;

		case 0x01a0:
			util::stream_format(stream, "NEG    ");
			print_des_reg(stream);
			break;

		case 0x01c0:
			util::stream_format(stream, "NEGB   ");
			print_des_reg(stream);
			break;

		case 0x01e0:
			util::stream_format(stream, "NOT    ");
			print_des_reg(stream);
>>>>>>> upstream/master
			break;

		default:
			bad = 1;
		}
		break;


	case 0x0400:
	case 0x0600:
		switch (subop)
		{
		case 0x0000:
			if (is_34020 && (op & 0xfe00) == 0x0600)
			{
<<<<<<< HEAD
				UINT32 x;
				PARAM_LONG(x);
				sprintf(buffer, "CEXEC  %d,%06X,%d", (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
=======
				uint32_t x;
				PARAM_LONG(x);
				util::stream_format(stream, "CEXEC  %d,%06X,%d", (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
>>>>>>> upstream/master
			}
			else
				bad = 1;
			break;

		case 0x0020:
			if (is_34020 && (op & 0xfe00) == 0x0600)
			{
<<<<<<< HEAD
				UINT32 x;
				PARAM_LONG(x);
				sprintf(buffer, "CMOVGC ");
				print_des_reg();
				sprintf(temp, ",%06X,%d", (x >> 8) & 0x1fffff, (x >> 29) & 7);
				strcat(buffer, temp);
=======
				uint32_t x;
				PARAM_LONG(x);
				util::stream_format(stream, "CMOVGC ");
				print_des_reg(stream);
				util::stream_format(stream, ",%06X,%d", (x >> 8) & 0x1fffff, (x >> 29) & 7);
>>>>>>> upstream/master
			}
			else
				bad = 1;
			break;

		case 0x0040:
			if (is_34020 && (op & 0xfe00) == 0x0600)
			{
<<<<<<< HEAD
				UINT32 x;
				PARAM_LONG(x);
				sprintf(buffer, "CMOVGC ");
				print_des_reg();
				strcat(buffer, ",");
				rf = (x & 0x10) ? 'B' : 'A';
				print_reg(x & 0x0f);
				sprintf(temp, ",%d,%06X,%d", (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
				strcat(buffer, temp);
=======
				uint32_t x;
				PARAM_LONG(x);
				util::stream_format(stream, "CMOVGC ");
				print_des_reg(stream);
				stream << ",";
				rf = (x & 0x10) ? 'B' : 'A';
				print_reg(stream, x & 0x0f);
				util::stream_format(stream, ",%d,%06X,%d", (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
>>>>>>> upstream/master
			}
			else
				bad = 1;
			break;

		case 0x0060:
			if (is_34020 && (op & 0xfe00) == 0x0600)
			{
<<<<<<< HEAD
				UINT32 x;
=======
				uint32_t x;
>>>>>>> upstream/master
				PARAM_LONG(x);

				if (op == 0x0660 && (x & 0xff) == 0x01)
				{
<<<<<<< HEAD
					sprintf(buffer, "CMOVCS ");
					sprintf(temp, ",%06X,%d", (x >> 8) & 0x1fffff, (x >> 29) & 7);
					strcat(buffer, temp);
				}
				else
				{
					sprintf(buffer, "CMOVCG ");
					print_des_reg();
					strcat(buffer, ",");
					rf = (x & 0x10) ? 'B' : 'A';
					print_reg(x & 0x0f);
					sprintf(temp, ",%d,%06X,%d", (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
					strcat(buffer, temp);
=======
					util::stream_format(stream, "CMOVCS ");
					util::stream_format(stream, ",%06X,%d", (x >> 8) & 0x1fffff, (x >> 29) & 7);
				}
				else
				{
					util::stream_format(stream, "CMOVCG ");
					print_des_reg(stream);
					stream << ",";
					rf = (x & 0x10) ? 'B' : 'A';
					print_reg(stream, x & 0x0f);
					util::stream_format(stream, ",%d,%06X,%d", (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
>>>>>>> upstream/master
				}
			}
			else
				bad = 1;
			break;

		case 0x0080:
			if (is_34020 && (op & 0xfe00) == 0x0600)
			{
<<<<<<< HEAD
				UINT32 x;
				PARAM_LONG(x);
				sprintf(buffer, "CMOVMC *");
				rf = (x & 0x10) ? 'B' : 'A';
				print_reg(x & 0x0f);
				sprintf(temp, "+,%d,%d,%06X,%d", op & 0x1f, (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
				strcat(buffer, temp);
=======
				uint32_t x;
				PARAM_LONG(x);
				util::stream_format(stream, "CMOVMC *");
				rf = (x & 0x10) ? 'B' : 'A';
				print_reg(stream, x & 0x0f);
				util::stream_format(stream, "+,%d,%d,%06X,%d", op & 0x1f, (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
>>>>>>> upstream/master
			}
			else
				bad = 1;
			break;

		case 0x00a0:
			if (is_34020 && (op & 0xfe00) == 0x0600)
			{
<<<<<<< HEAD
				UINT32 x;
				PARAM_LONG(x);
				sprintf(buffer, "CMOVCM *");
				print_des_reg();
				sprintf(temp, "+,%d,%d,%06X,%d", x & 0x1f, (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
				strcat(buffer, temp);
=======
				uint32_t x;
				PARAM_LONG(x);
				util::stream_format(stream, "CMOVCM *");
				print_des_reg(stream);
				util::stream_format(stream, "+,%d,%d,%06X,%d", x & 0x1f, (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
>>>>>>> upstream/master
			}
			else
				bad = 1;
			break;

		case 0x00c0:
			if (is_34020 && (op & 0xfe00) == 0x0600)
			{
<<<<<<< HEAD
				UINT32 x;
				PARAM_LONG(x);
				sprintf(buffer, "CMOVCM *-");
				print_des_reg();
				sprintf(temp, ",%d,%d,%06X,%d", x & 0x1f, (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
				strcat(buffer, temp);
=======
				uint32_t x;
				PARAM_LONG(x);
				util::stream_format(stream, "CMOVCM *-");
				print_des_reg(stream);
				util::stream_format(stream, ",%d,%d,%06X,%d", x & 0x1f, (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
>>>>>>> upstream/master
			}
			else
				bad = 1;
			break;

		case 0x00e0:
			if (is_34020 && (op & 0xfe00) == 0x0600)
			{
<<<<<<< HEAD
				UINT32 x;
				PARAM_LONG(x);
				sprintf(buffer, "CMOVMC *");
				rf = (x & 0x10) ? 'B' : 'A';
				print_reg(x & 0x0f);
				strcat(buffer, "+,");
				rf = (op & 0x10) ? 'B' : 'A';
				print_reg(op & 0x0f);
				sprintf(temp, ",%d,%06X,%d", (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
				strcat(buffer, temp);
=======
				uint32_t x;
				PARAM_LONG(x);
				util::stream_format(stream, "CMOVMC *");
				rf = (x & 0x10) ? 'B' : 'A';
				print_reg(stream, x & 0x0f);
				stream << "+,";
				rf = (op & 0x10) ? 'B' : 'A';
				print_reg(stream, op & 0x0f);
				util::stream_format(stream, ",%d,%06X,%d", (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
>>>>>>> upstream/master
			}
			else
				bad = 1;
			break;

		case 0x0100:
<<<<<<< HEAD
			sprintf (buffer, "SEXT   ");
			print_des_reg();
			strcat(buffer, ",");
			print_field();
			break;

		case 0x0120:
			sprintf (buffer, "ZEXT   ");
			print_des_reg();
			strcat(buffer, ",");
			print_field();
=======
			util::stream_format(stream, "SEXT   ");
			print_des_reg(stream);
			stream << ",";
			print_field(stream);
			break;

		case 0x0120:
			util::stream_format(stream, "ZEXT   ");
			print_des_reg(stream);
			stream << ",";
			print_field(stream);
>>>>>>> upstream/master
			break;

		case 0x0140:
		case 0x0160:
<<<<<<< HEAD
			sprintf (buffer, "SETF   %Xh,%X,",
						(op & 0x1f) ? op & 0x1f : 0x20,
						(op >> 5) & 1);
			print_field();
			break;

		case 0x0180:
			sprintf (buffer, "MOVE   ");
			print_des_reg();
			strcat(buffer, ",@");
			print_long_parm();
			strcat(buffer, ",");
			print_field();
			break;

		case 0x01a0:
			sprintf (buffer, "MOVE   @");
			print_long_parm();
			strcat(buffer, ",");
			print_des_reg();
			strcat(buffer, ",");
			print_field();
			break;

		case 0x01c0:
			sprintf (buffer, "MOVE   @");
			print_long_parm();
			strcat(buffer, ",@");
			print_long_parm();
			strcat(buffer, ",");
			print_field();
=======
			util::stream_format(stream, "SETF   %Xh,%X,",
						(op & 0x1f) ? op & 0x1f : 0x20,
						(op >> 5) & 1);
			print_field(stream);
			break;

		case 0x0180:
			util::stream_format(stream, "MOVE   ");
			print_des_reg(stream);
			stream << ",@";
			print_long_parm(stream);
			stream << ",";
			print_field(stream);
			break;

		case 0x01a0:
			util::stream_format(stream, "MOVE   @");
			print_long_parm(stream);
			stream << ",";
			print_des_reg(stream);
			stream << ",";
			print_field(stream);
			break;

		case 0x01c0:
			util::stream_format(stream, "MOVE   @");
			print_long_parm(stream);
			stream << ",@";
			print_long_parm2(stream);
			stream << ",";
			print_field(stream);
>>>>>>> upstream/master
			break;

		case 0x01e0:
			if (op & 0x200)
			{
<<<<<<< HEAD
				sprintf (buffer, "MOVE   @");
				print_long_parm();
				strcat(buffer, ",");
				print_des_reg();
			}
			else
			{
				sprintf (buffer, "MOVB   ");
				print_des_reg();
				strcat(buffer, ",@");
				print_long_parm();
=======
				util::stream_format(stream, "MOVE   @");
				print_long_parm(stream);
				stream << ",";
				print_des_reg(stream);
			}
			else
			{
				util::stream_format(stream, "MOVB   ");
				print_des_reg(stream);
				stream << ",@";
				print_long_parm(stream);
>>>>>>> upstream/master
			}
			break;

		default:
			bad = 1;
		}
		break;


	case 0x0800:
		switch (subop)
		{
		case 0x0000:
			if (is_34020)
			{
<<<<<<< HEAD
				sprintf (buffer, "TRAPL  ");
=======
				util::stream_format(stream, "TRAPL  ");
>>>>>>> upstream/master
				flags = DASMFLAG_STEP_OVER;
			}
			else
				bad = 1;
			break;

		case 0x0020:
			if (is_34020)
			{
<<<<<<< HEAD
				UINT32 x;
				PARAM_LONG(x);
				sprintf(buffer, "CMOVMC *-");
				rf = (x & 0x10) ? 'B' : 'A';
				print_reg(x & 0x0f);
				sprintf(temp, ",%d,%d,%06X,%d", op & 0x1f, (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
				strcat(buffer, temp);
=======
				uint32_t x;
				PARAM_LONG(x);
				util::stream_format(stream, "CMOVMC *-");
				rf = (x & 0x10) ? 'B' : 'A';
				print_reg(stream, x & 0x0f);
				util::stream_format(stream, ",%d,%d,%06X,%d", op & 0x1f, (x >> 7) & 1, (x >> 8) & 0x1fffff, (x >> 29) & 7);
>>>>>>> upstream/master
			}
			else
				bad = 1;
			break;

		case 0x0040:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "VBLT   B,L");
=======
				util::stream_format(stream, "VBLT   B,L");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x0060:
			if (is_34020)
			{
<<<<<<< HEAD
				sprintf(buffer, "RETM   ");
=======
				util::stream_format(stream, "RETM   ");
>>>>>>> upstream/master
				flags = DASMFLAG_STEP_OUT;
			}
			else
				bad = 1;
			break;

		case 0x00e0:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "CLIP   ");
=======
				util::stream_format(stream, "CLIP   ");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x0100:
<<<<<<< HEAD
			sprintf (buffer, "TRAP   %Xh", op & 0x1f);
=======
			util::stream_format(stream, "TRAP   %Xh", op & 0x1f);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER;
			break;

		case 0x0120:
<<<<<<< HEAD
			sprintf (buffer, "CALL   ");
			print_des_reg();
=======
			util::stream_format(stream, "CALL   ");
			print_des_reg(stream);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER;
			break;

		case 0x0140:
<<<<<<< HEAD
			sprintf (buffer, "RETI   ");
=======
			util::stream_format(stream, "RETI   ");
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OUT;
			break;

		case 0x0160:
<<<<<<< HEAD
			sprintf (buffer, "RETS   ");
			flags = DASMFLAG_STEP_OUT;
			if (op & 0x1f)
			{
				sprintf(temp, "%Xh", op & 0x1f);
				strcat(buffer, temp);
=======
			util::stream_format(stream, "RETS   ");
			flags = DASMFLAG_STEP_OUT;
			if (op & 0x1f)
			{
				util::stream_format(stream, "%Xh", op & 0x1f);
>>>>>>> upstream/master
			}
			break;

		case 0x0180:
<<<<<<< HEAD
			sprintf (buffer, "MMTM   ");
			print_des_reg();
			print_reg_list(1);
			break;

		case 0x01a0:
			sprintf (buffer, "MMFM   ");
			print_des_reg();
			print_reg_list(0);
			break;

		case 0x01c0:
			sprintf (buffer, "MOVI   ");
			print_word_parm();
			strcat(buffer, ",");
			print_des_reg();
			break;

		case 0x01e0:
			sprintf (buffer, "MOVI   ");
			print_long_parm();
			strcat(buffer, ",");
			print_des_reg();
=======
			util::stream_format(stream, "MMTM   ");
			print_des_reg(stream);
			print_reg_list(stream, 1);
			break;

		case 0x01a0:
			util::stream_format(stream, "MMFM   ");
			print_des_reg(stream);
			print_reg_list(stream, 0);
			break;

		case 0x01c0:
			util::stream_format(stream, "MOVI   ");
			print_word_parm(stream);
			stream << ",";
			print_des_reg(stream);
			break;

		case 0x01e0:
			util::stream_format(stream, "MOVI   ");
			print_long_parm(stream);
			stream << ",";
			print_des_reg(stream);
>>>>>>> upstream/master
			break;

		default:
			bad = 1;
		}
		break;


	case 0x0a00:
		switch (subop)
		{
		case 0x0000:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "VLCOL  ");
=======
				util::stream_format(stream, "VLCOL  ");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x0020:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "PFILL  XY");
=======
				util::stream_format(stream, "PFILL  XY");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x0040:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "VFILL  L");
=======
				util::stream_format(stream, "VFILL  L");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x0060:
			if (is_34020)
			{
<<<<<<< HEAD
				sprintf (buffer, "CVMXYL ");
				print_des_reg();
=======
				util::stream_format(stream, "CVMXYL ");
				print_des_reg(stream);
>>>>>>> upstream/master
			}
			else
				bad = 1;
			break;

		case 0x0080:
			if (is_34020)
			{
<<<<<<< HEAD
				sprintf (buffer, "CVDXYL ");
				print_des_reg();
=======
				util::stream_format(stream, "CVDXYL ");
				print_des_reg(stream);
>>>>>>> upstream/master
			}
			else
				bad = 1;
			break;

		case 0x00a0:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "FPIXEQ ");
=======
				util::stream_format(stream, "FPIXEQ ");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x00c0:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "FPIXNE ");
=======
				util::stream_format(stream, "FPIXNE ");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x0100:
<<<<<<< HEAD
			sprintf (buffer, "ADDI   ");
			print_word_parm();
			strcat(buffer, ",");
			print_des_reg();
			break;

		case 0x0120:
			sprintf (buffer, "ADDI   ");
			print_long_parm();
			strcat(buffer, ",");
			print_des_reg();
			break;

		case 0x0140:
			sprintf (buffer, "CMPI   ");
			print_word_parm_1s_comp();
			strcat(buffer, ",");
			print_des_reg();
			break;

		case 0x0160:
			sprintf (buffer, "CMPI   ");
			print_long_parm_1s_comp();
			strcat(buffer, ",");
			print_des_reg();
			break;

		case 0x0180:
			sprintf (buffer, "ANDI   ");
			print_long_parm_1s_comp();
			strcat(buffer, ",");
			print_des_reg();
			break;

		case 0x01a0:
			sprintf (buffer, "ORI    ");
			print_long_parm();
			strcat(buffer, ",");
			print_des_reg();
			break;

		case 0x01c0:
			sprintf (buffer, "XORI   ");
			print_long_parm();
			strcat(buffer, ",");
			print_des_reg();
			break;

		case 0x01e0:
			sprintf (buffer, "SUBI   ");
			print_word_parm_1s_comp();
			strcat(buffer, ",");
			print_des_reg();
=======
			util::stream_format(stream, "ADDI   ");
			print_word_parm(stream);
			stream << ",";
			print_des_reg(stream);
			break;

		case 0x0120:
			util::stream_format(stream, "ADDI   ");
			print_long_parm(stream);
			stream << ",";
			print_des_reg(stream);
			break;

		case 0x0140:
			util::stream_format(stream, "CMPI   ");
			print_word_parm_1s_comp(stream);
			stream << ",";
			print_des_reg(stream);
			break;

		case 0x0160:
			util::stream_format(stream, "CMPI   ");
			print_long_parm_1s_comp(stream);
			stream << ",";
			print_des_reg(stream);
			break;

		case 0x0180:
			util::stream_format(stream, "ANDI   ");
			print_long_parm_1s_comp(stream);
			stream << ",";
			print_des_reg(stream);
			break;

		case 0x01a0:
			util::stream_format(stream, "ORI    ");
			print_long_parm(stream);
			stream << ",";
			print_des_reg(stream);
			break;

		case 0x01c0:
			util::stream_format(stream, "XORI   ");
			print_long_parm(stream);
			stream << ",";
			print_des_reg(stream);
			break;

		case 0x01e0:
			util::stream_format(stream, "SUBI   ");
			print_word_parm_1s_comp(stream);
			stream << ",";
			print_des_reg(stream);
>>>>>>> upstream/master
			break;

		default:
			bad = 1;
		}
		break;


	case 0x0c00:
		switch (subop)
		{
		case 0x0000:
			if (is_34020)
			{
<<<<<<< HEAD
				sprintf (buffer, "ADDXYI ");
				print_long_parm();
				strcat(buffer, ",");
				print_des_reg();
=======
				util::stream_format(stream, "ADDXYI ");
				print_long_parm(stream);
				stream << ",";
				print_des_reg(stream);
>>>>>>> upstream/master
			}
			else
				bad = 1;
			break;

		case 0x0040:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "LINIT  ");
=======
				util::stream_format(stream, "LINIT  ");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x0100:
<<<<<<< HEAD
			sprintf (buffer, "SUBI   ");
			print_long_parm_1s_comp();
			strcat(buffer, ",");
			print_des_reg();
			break;

		case 0x0120:
			sprintf (buffer, "CALLR  ");
			print_relative();
=======
			util::stream_format(stream, "SUBI   ");
			print_long_parm_1s_comp(stream);
			stream << ",";
			print_des_reg(stream);
			break;

		case 0x0120:
			util::stream_format(stream, "CALLR  ");
			print_relative(stream);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER;
			break;

		case 0x0140:
<<<<<<< HEAD
			sprintf (buffer, "CALLA  ");
			print_long_parm();
=======
			util::stream_format(stream, "CALLA  ");
			print_long_parm(stream);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER;
			break;

		case 0x0160:
<<<<<<< HEAD
			sprintf (buffer, "EINT   ");
			break;

		case 0x0180:
			sprintf (buffer, "DSJ    ");
			print_des_reg();
			strcat(buffer, ",");
			print_relative();
=======
			util::stream_format(stream, "EINT   ");
			break;

		case 0x0180:
			util::stream_format(stream, "DSJ    ");
			print_des_reg(stream);
			stream << ",";
			print_relative(stream);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER;
			break;

		case 0x01a0:
<<<<<<< HEAD
			sprintf (buffer, "DSJEQ  ");
			print_des_reg();
			strcat(buffer, ",");
			print_relative();
=======
			util::stream_format(stream, "DSJEQ  ");
			print_des_reg(stream);
			stream << ",";
			print_relative(stream);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER;
			break;

		case 0x01c0:
<<<<<<< HEAD
			sprintf (buffer, "DSJNE  ");
			print_des_reg();
			strcat(buffer, ",");
			print_relative();
=======
			util::stream_format(stream, "DSJNE  ");
			print_des_reg(stream);
			stream << ",";
			print_relative(stream);
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OVER;
			break;

		case 0x01e0:
<<<<<<< HEAD
			sprintf (buffer, "SETC   ");
=======
			util::stream_format(stream, "SETC   ");
>>>>>>> upstream/master
			break;

		default:
			bad = 1;
		}
		break;


	case 0x0e00:
		flags = DASMFLAG_STEP_OVER;
		switch (subop)
		{
		case 0x0000:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "PIXBLT L,M,L");
=======
				util::stream_format(stream, "PIXBLT L,M,L");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x00e0:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "TFILL  XY");
=======
				util::stream_format(stream, "TFILL  XY");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x0100:
<<<<<<< HEAD
			sprintf (buffer, "PIXBLT L,L");
			break;

		case 0x0120:
			sprintf (buffer, "PIXBLT L,XY");
			break;

		case 0x0140:
			sprintf (buffer, "PIXBLT XY,L");
			break;

		case 0x0160:
			sprintf (buffer, "PIXBLT XY,XY");
			break;

		case 0x0180:
			sprintf (buffer, "PIXBLT B,L");
			break;

		case 0x01a0:
			sprintf (buffer, "PIXBLT B,XY");
			break;

		case 0x01c0:
			sprintf (buffer, "FILL   L");
			break;

		case 0x01e0:
			sprintf (buffer, "FILL   XY");
=======
			util::stream_format(stream, "PIXBLT L,L");
			break;

		case 0x0120:
			util::stream_format(stream, "PIXBLT L,XY");
			break;

		case 0x0140:
			util::stream_format(stream, "PIXBLT XY,L");
			break;

		case 0x0160:
			util::stream_format(stream, "PIXBLT XY,XY");
			break;

		case 0x0180:
			util::stream_format(stream, "PIXBLT B,L");
			break;

		case 0x01a0:
			util::stream_format(stream, "PIXBLT B,XY");
			break;

		case 0x01c0:
			util::stream_format(stream, "FILL   L");
			break;

		case 0x01e0:
			util::stream_format(stream, "FILL   XY");
>>>>>>> upstream/master
			break;

		default:
			bad = 1;
		}
		break;


	case 0x1000:
	case 0x1200:
		if ((op & 0x03e0) != 0x0020)
		{
<<<<<<< HEAD
			sprintf (buffer, "ADDK   ");
			print_constant_1_32();
			strcat(buffer, ",");
		}
		else
		{
			sprintf (buffer, "INC    ");
		}
		print_des_reg();
=======
			util::stream_format(stream, "ADDK   ");
			print_constant_1_32(stream);
			stream << ",";
		}
		else
		{
			util::stream_format(stream, "INC    ");
		}
		print_des_reg(stream);
>>>>>>> upstream/master

		break;


	case 0x1400:
	case 0x1600:
		if ((op & 0x03e0) != 0x0020)
		{
<<<<<<< HEAD
			sprintf (buffer, "SUBK   ");
			print_constant_1_32();
			strcat(buffer, ",");
		}
		else
		{
			sprintf (buffer, "DEC    ");
		}
		print_des_reg();
=======
			util::stream_format(stream, "SUBK   ");
			print_constant_1_32(stream);
			stream << ",";
		}
		else
		{
			util::stream_format(stream, "DEC    ");
		}
		print_des_reg(stream);
>>>>>>> upstream/master

		break;


	case 0x1800:
	case 0x1a00:
<<<<<<< HEAD
		sprintf (buffer, "MOVK   ");
		print_constant_1_32();
		strcat(buffer, ",");
		print_des_reg();
=======
		util::stream_format(stream, "MOVK   ");
		print_constant_1_32(stream);
		stream << ",";
		print_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x1c00:
	case 0x1e00:
<<<<<<< HEAD
		sprintf (buffer, "BTST   ");
		print_constant_1s_comp();
		strcat(buffer, ",");
		print_des_reg();
=======
		util::stream_format(stream, "BTST   ");
		print_constant_1s_comp(stream);
		stream << ",";
		print_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x2000:
	case 0x2200:
<<<<<<< HEAD
		sprintf (buffer, "SLA    ");
		print_constant();
		strcat(buffer, ",");
		print_des_reg();
=======
		util::stream_format(stream, "SLA    ");
		print_constant(stream);
		stream << ",";
		print_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x2400:
	case 0x2600:
<<<<<<< HEAD
		sprintf (buffer, "SLL    ");
		print_constant();
		strcat(buffer, ",");
		print_des_reg();
=======
		util::stream_format(stream, "SLL    ");
		print_constant(stream);
		stream << ",";
		print_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x2800:
	case 0x2a00:
<<<<<<< HEAD
		sprintf (buffer, "SRA    ");
		print_constant_2s_comp();
		strcat(buffer, ",");
		print_des_reg();
=======
		util::stream_format(stream, "SRA    ");
		print_constant_2s_comp(stream);
		stream << ",";
		print_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x2c00:
	case 0x2e00:
<<<<<<< HEAD
		sprintf (buffer, "SRL    ");
		print_constant_2s_comp();
		strcat(buffer, ",");
		print_des_reg();
=======
		util::stream_format(stream, "SRL    ");
		print_constant_2s_comp(stream);
		stream << ",";
		print_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x3000:
	case 0x3200:
<<<<<<< HEAD
		sprintf (buffer, "RL     ");
		print_constant();
		strcat(buffer, ",");
		print_des_reg();
=======
		util::stream_format(stream, "RL     ");
		print_constant(stream);
		stream << ",";
		print_des_reg(stream);
>>>>>>> upstream/master
		break;

	case 0x3400:
	case 0x3600:
		if (is_34020)
		{
<<<<<<< HEAD
			sprintf (buffer, "CMPK   ");
			print_constant_1_32();
			strcat(buffer, ",");
			print_des_reg();
=======
			util::stream_format(stream, "CMPK   ");
			print_constant_1_32(stream);
			stream << ",";
			print_des_reg(stream);
>>>>>>> upstream/master
		}
		else
			bad = 1;
		break;

	case 0x3800:
	case 0x3a00:
	case 0x3c00:
	case 0x3e00:
<<<<<<< HEAD
		sprintf (buffer, "DSJS   ");
		print_des_reg();
		strcat(buffer, ",");
		print_relative_5bit();
=======
		util::stream_format(stream, "DSJS   ");
		print_des_reg(stream);
		stream << ",";
		print_relative_5bit(stream);
>>>>>>> upstream/master
		flags = DASMFLAG_STEP_OVER;
		break;


	case 0x4000:
<<<<<<< HEAD
		sprintf (buffer, "ADD    ");
		print_src_des_reg();
=======
		util::stream_format(stream, "ADD    ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x4200:
<<<<<<< HEAD
		sprintf (buffer, "ADDC   ");
		print_src_des_reg();
=======
		util::stream_format(stream, "ADDC   ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x4400:
<<<<<<< HEAD
		sprintf (buffer, "SUB    ");
		print_src_des_reg();
=======
		util::stream_format(stream, "SUB    ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x4600:
<<<<<<< HEAD
		sprintf (buffer, "SUBB   ");
		print_src_des_reg();
=======
		util::stream_format(stream, "SUBB   ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x4800:
<<<<<<< HEAD
		sprintf (buffer, "CMP    ");
		print_src_des_reg();
=======
		util::stream_format(stream, "CMP    ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x4a00:
<<<<<<< HEAD
		sprintf (buffer, "BTST   ");
		print_src_des_reg();
=======
		util::stream_format(stream, "BTST   ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x4c00:
	case 0x4e00:
<<<<<<< HEAD
		sprintf (buffer, "MOVE   ");

		if (!(op & 0x0200))
		{
			print_src_des_reg();
		}
		else
		{
			print_src_reg();
			strcat(buffer, ",");
=======
		util::stream_format(stream, "MOVE   ");

		if (!(op & 0x0200))
		{
			print_src_des_reg(stream);
		}
		else
		{
			print_src_reg(stream);
			stream << ",";
>>>>>>> upstream/master

			if (rf == 'A')
			{
				rf = 'B';
			}
			else
			{
				rf = 'A';
			}

<<<<<<< HEAD
			print_des_reg();
=======
			print_des_reg(stream);
>>>>>>> upstream/master
		}
		break;


	case 0x5000:
<<<<<<< HEAD
		sprintf (buffer, "AND    ");
		print_src_des_reg();
=======
		util::stream_format(stream, "AND    ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x5200:
<<<<<<< HEAD
		sprintf (buffer, "ANDN   ");
		print_src_des_reg();
=======
		util::stream_format(stream, "ANDN   ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x5400:
<<<<<<< HEAD
		sprintf (buffer, "OR     ");
		print_src_des_reg();
=======
		util::stream_format(stream, "OR     ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x5600:
		if (rs != rd)
		{
<<<<<<< HEAD
			sprintf (buffer, "XOR    ");
			print_src_des_reg();
		}
		else
		{
			sprintf (buffer, "CLR    ");
			print_des_reg();
=======
			util::stream_format(stream, "XOR    ");
			print_src_des_reg(stream);
		}
		else
		{
			util::stream_format(stream, "CLR    ");
			print_des_reg(stream);
>>>>>>> upstream/master
		}
		break;


	case 0x5800:
<<<<<<< HEAD
		sprintf (buffer, "DIVS   ");
		print_src_des_reg();
=======
		util::stream_format(stream, "DIVS   ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x5a00:
<<<<<<< HEAD
		sprintf (buffer, "DIVU   ");
		print_src_des_reg();
=======
		util::stream_format(stream, "DIVU   ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x5c00:
<<<<<<< HEAD
		sprintf (buffer, "MPYS   ");
		print_src_des_reg();
=======
		util::stream_format(stream, "MPYS   ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x5e00:
<<<<<<< HEAD
		sprintf (buffer, "MPYU   ");
		print_src_des_reg();
=======
		util::stream_format(stream, "MPYU   ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x6000:
<<<<<<< HEAD
		sprintf (buffer, "SLA    ");
		print_src_des_reg();
=======
		util::stream_format(stream, "SLA    ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x6200:
<<<<<<< HEAD
		sprintf (buffer, "SLL    ");
		print_src_des_reg();
=======
		util::stream_format(stream, "SLL    ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x6400:
<<<<<<< HEAD
		sprintf (buffer, "SRA    ");
		print_src_des_reg();
=======
		util::stream_format(stream, "SRA    ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x6600:
<<<<<<< HEAD
		sprintf (buffer, "SRL    ");
		print_src_des_reg();
=======
		util::stream_format(stream, "SRL    ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x6800:
<<<<<<< HEAD
		sprintf (buffer, "RL     ");
		print_src_des_reg();
=======
		util::stream_format(stream, "RL     ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x6a00:
<<<<<<< HEAD
		sprintf (buffer, "LMO    ");
		print_src_des_reg();
=======
		util::stream_format(stream, "LMO    ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x6c00:
<<<<<<< HEAD
		sprintf (buffer, "MODS   ");
		print_src_des_reg();
=======
		util::stream_format(stream, "MODS   ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x6e00:
<<<<<<< HEAD
		sprintf (buffer, "MODU   ");
		print_src_des_reg();
=======
		util::stream_format(stream, "MODU   ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x7a00:
		if (is_34020)
		{
<<<<<<< HEAD
			sprintf (buffer, "RMO    ");
			print_src_des_reg();
=======
			util::stream_format(stream, "RMO    ");
			print_src_des_reg(stream);
>>>>>>> upstream/master
		}
		else
			bad = 1;
		break;

	case 0x7e00:
		if (is_34020)
		{
<<<<<<< HEAD
			sprintf (buffer, "SWAPF  *");
			print_src_des_reg();
			strcat(buffer, ",0");
=======
			util::stream_format(stream, "SWAPF  *");
			print_src_des_reg(stream);
			stream << ",0";
>>>>>>> upstream/master
		}
		else
			bad = 1;
		break;


	case 0x8000:
	case 0x8200:
<<<<<<< HEAD
		sprintf (buffer, "MOVE   ");
		print_src_reg();
		strcat(buffer, ",*");
		print_des_reg();
		strcat(buffer, ",");
		print_field();
=======
		util::stream_format(stream, "MOVE   ");
		print_src_reg(stream);
		stream << ",*";
		print_des_reg(stream);
		stream << ",";
		print_field(stream);
>>>>>>> upstream/master
		break;


	case 0x8400:
	case 0x8600:
<<<<<<< HEAD
		sprintf (buffer, "MOVE   *");
		print_src_des_reg();
		strcat(buffer, ",");
		print_field();
=======
		util::stream_format(stream, "MOVE   *");
		print_src_des_reg(stream);
		stream << ",";
		print_field(stream);
>>>>>>> upstream/master
		break;


	case 0x8800:
	case 0x8a00:
<<<<<<< HEAD
		sprintf (buffer, "MOVE   *");
		print_src_reg();
		strcat(buffer, ",*");
		print_des_reg();
		strcat(buffer, ",");
		print_field();
=======
		util::stream_format(stream, "MOVE   *");
		print_src_reg(stream);
		stream << ",*";
		print_des_reg(stream);
		stream << ",";
		print_field(stream);
>>>>>>> upstream/master
		break;


	case 0x8c00:
<<<<<<< HEAD
		sprintf (buffer, "MOVB   ");
		print_src_reg();
		strcat(buffer, ",*");
		print_des_reg();
=======
		util::stream_format(stream, "MOVB   ");
		print_src_reg(stream);
		stream << ",*";
		print_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x8e00:
<<<<<<< HEAD
		sprintf (buffer, "MOVB   *");
		print_src_des_reg();
=======
		util::stream_format(stream, "MOVB   *");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0x9000:
	case 0x9200:
<<<<<<< HEAD
		sprintf (buffer, "MOVE   ");
		print_src_reg();
		strcat(buffer, ",*");
		print_des_reg();
		strcat(buffer, "+,");
		print_field();
=======
		util::stream_format(stream, "MOVE   ");
		print_src_reg(stream);
		stream << ",*";
		print_des_reg(stream);
		stream << "+,";
		print_field(stream);
>>>>>>> upstream/master
		break;


	case 0x9400:
	case 0x9600:
<<<<<<< HEAD
		sprintf (buffer, "MOVE   *");
		print_src_reg();
		strcat(buffer, "+,");
		print_des_reg();
		strcat(buffer, ",");
		print_field();
=======
		util::stream_format(stream, "MOVE   *");
		print_src_reg(stream);
		stream << "+,";
		print_des_reg(stream);
		stream << ",";
		print_field(stream);
>>>>>>> upstream/master
		break;


	case 0x9800:
	case 0x9a00:
<<<<<<< HEAD
		sprintf (buffer, "MOVE   *");
		print_src_reg();
		strcat(buffer, "+,*");
		print_des_reg();
		strcat(buffer, "+,");
		print_field();
=======
		util::stream_format(stream, "MOVE   *");
		print_src_reg(stream);
		stream << "+,*";
		print_des_reg(stream);
		stream << "+,";
		print_field(stream);
>>>>>>> upstream/master
		break;


	case 0x9c00:
<<<<<<< HEAD
		sprintf (buffer, "MOVB   *");
		print_src_reg();
		strcat(buffer, ",*");
		print_des_reg();
=======
		util::stream_format(stream, "MOVB   *");
		print_src_reg(stream);
		stream << ",*";
		print_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0xa000:
	case 0xa200:
<<<<<<< HEAD
		sprintf (buffer, "MOVE   ");
		print_src_reg();
		strcat(buffer, ",-*");
		print_des_reg();
		strcat(buffer, ",");
		print_field();
=======
		util::stream_format(stream, "MOVE   ");
		print_src_reg(stream);
		stream << ",-*";
		print_des_reg(stream);
		stream << ",";
		print_field(stream);
>>>>>>> upstream/master
		break;


	case 0xa400:
	case 0xa600:
<<<<<<< HEAD
		sprintf (buffer, "MOVE   -*");
		print_src_des_reg();
		strcat(buffer, ",");
		print_field();
=======
		util::stream_format(stream, "MOVE   -*");
		print_src_des_reg(stream);
		stream << ",";
		print_field(stream);
>>>>>>> upstream/master
		break;


	case 0xa800:
	case 0xaa00:
<<<<<<< HEAD
		sprintf (buffer, "MOVE   -*");
		print_src_reg();
		strcat(buffer, ",-*");
		print_des_reg();
		strcat(buffer, ",");
		print_field();
=======
		util::stream_format(stream, "MOVE   -*");
		print_src_reg(stream);
		stream << ",-*";
		print_des_reg(stream);
		stream << ",";
		print_field(stream);
>>>>>>> upstream/master
		break;


	case 0xac00:
<<<<<<< HEAD
		sprintf (buffer, "MOVB   ");
		print_src_reg();
		strcat(buffer, ",*");
		print_des_reg();
		strcat(buffer, "(");
		print_word_parm();
		strcat(buffer, ")");
=======
		util::stream_format(stream, "MOVB   ");
		print_src_reg(stream);
		stream << ",*";
		print_des_reg(stream);
		stream << "(";
		print_word_parm(stream);
		stream << ")";
>>>>>>> upstream/master
		break;


	case 0xae00:
<<<<<<< HEAD
		sprintf (buffer, "MOVB   *");
		print_src_reg();
		strcat(buffer, "(");
		print_word_parm();
		strcat(buffer, "),");
		print_des_reg();
=======
		util::stream_format(stream, "MOVB   *");
		print_src_reg(stream);
		stream << "(";
		print_word_parm(stream);
		stream << "),";
		print_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0xb000:
	case 0xb200:
<<<<<<< HEAD
		sprintf (buffer, "MOVE   ");
		print_src_reg();
		strcat(buffer, ",*");
		print_des_reg();
		strcat(buffer, "(");
		print_word_parm();
		strcat(buffer, "),");
		print_field();
=======
		util::stream_format(stream, "MOVE   ");
		print_src_reg(stream);
		stream << ",*";
		print_des_reg(stream);
		stream << "(";
		print_word_parm(stream);
		stream << "),";
		print_field(stream);
>>>>>>> upstream/master
		break;


	case 0xb400:
	case 0xb600:
<<<<<<< HEAD
		sprintf (buffer, "MOVE   *");
		print_src_reg();
		strcat(buffer, "(");
		print_word_parm();
		strcat(buffer, "),");
		print_des_reg();
		strcat(buffer, ",");
		print_field();
=======
		util::stream_format(stream, "MOVE   *");
		print_src_reg(stream);
		stream << "(";
		print_word_parm(stream);
		stream << "),";
		print_des_reg(stream);
		stream << ",";
		print_field(stream);
>>>>>>> upstream/master
		break;


	case 0xb800:
	case 0xba00:
<<<<<<< HEAD
		sprintf (buffer, "MOVE   *");
		print_src_reg();
		strcat(buffer, "(");
		print_word_parm();
		strcat(buffer, "),*");
		print_des_reg();
		strcat(buffer, "(");
		print_word_parm();
		strcat(buffer, "),");
		print_field();
=======
		util::stream_format(stream, "MOVE   *");
		print_src_reg(stream);
		stream << "(";
		print_word_parm(stream);
		stream << "),*";
		print_des_reg(stream);
		stream << "(";
		print_word_parm(stream);
		stream << "),";
		print_field(stream);
>>>>>>> upstream/master
		break;


	case 0xbc00:
<<<<<<< HEAD
		sprintf (buffer, "MOVB   *");
		print_src_reg();
		strcat(buffer, "(");
		print_word_parm();
		strcat(buffer, "),*");
		print_des_reg();
		strcat(buffer, "(");
		print_word_parm();
		strcat(buffer, ")");
=======
		util::stream_format(stream, "MOVB   *");
		print_src_reg(stream);
		stream << "(";
		print_word_parm(stream);
		stream << "),*";
		print_des_reg(stream);
		stream << "(";
		print_word_parm(stream);
		stream << ")";
>>>>>>> upstream/master
		break;


	case 0xc000:
	case 0xc200:
	case 0xc400:
	case 0xc600:
	case 0xc800:
	case 0xca00:
	case 0xcc00:
	case 0xce00:
		if ((op & 0x00ff) == 0x80)
		{
<<<<<<< HEAD
			sprintf (buffer, "JA");
		}
		else
		{
			sprintf (buffer, "JR");
		}

		print_condition_code();
		strcat (buffer, "   ");
=======
			util::stream_format(stream, "JA");
		}
		else
		{
			util::stream_format(stream, "JR");
		}

		print_condition_code(stream);
		stream << "   ";
>>>>>>> upstream/master

		switch (op & 0x00ff)
		{
		case 0x00:
<<<<<<< HEAD
			print_relative();
			break;

		case 0x80:
			print_long_parm();
			break;

		default:
			print_relative_8bit();
=======
			print_relative(stream);
			break;

		case 0x80:
			print_long_parm(stream);
			break;

		default:
			print_relative_8bit(stream);
>>>>>>> upstream/master
		}
		break;


	case 0xd000:
	case 0xd200:
<<<<<<< HEAD
		sprintf (buffer, "MOVE   *");
		print_src_reg();
		strcat(buffer, "(");
		print_word_parm();
		strcat(buffer, "),*");
		print_des_reg();
		strcat(buffer, "+,");
		print_field();
=======
		util::stream_format(stream, "MOVE   *");
		print_src_reg(stream);
		stream << "(";
		print_word_parm(stream);
		stream << "),*";
		print_des_reg(stream);
		stream << "+,";
		print_field(stream);
>>>>>>> upstream/master
		break;


	case 0xd400:
	case 0xd600:
		switch (subop)
		{
		case 0x0000:
<<<<<<< HEAD
			sprintf (buffer, "MOVE   @");
			print_long_parm();
			strcat(buffer, ",*");
			print_des_reg();
			strcat(buffer, "+,");
			print_field();
			break;

		case 0x0100:
			sprintf (buffer, "EXGF   ");
			print_des_reg();
			strcat(buffer, ",");
			print_field();
=======
			util::stream_format(stream, "MOVE   @");
			print_long_parm(stream);
			stream << ",*";
			print_des_reg(stream);
			stream << "+,";
			print_field(stream);
			break;

		case 0x0100:
			util::stream_format(stream, "EXGF   ");
			print_des_reg(stream);
			stream << ",";
			print_field(stream);
>>>>>>> upstream/master
			break;

		default:
			bad = 1;
		}
		break;

	case 0xd800:
		if (is_34020)
		{
<<<<<<< HEAD
			UINT32 x;
			PARAM_WORD(x);
			sprintf(buffer, "CEXEC  %d,%06X,%d", op & 1, ((x << 5) & 0x1fffe0) | ((op >> 1) & 0x1f), (x >> 13) & 7);
=======
			uint32_t x;
			PARAM_WORD(x);
			util::stream_format(stream, "CEXEC  %d,%06X,%d", op & 1, ((x << 5) & 0x1fffe0) | ((op >> 1) & 0x1f), (x >> 13) & 7);
>>>>>>> upstream/master
		}
		else
			bad = 1;
		break;


	case 0xde00:
		switch (subop)
		{
		case 0x0000:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "FLINE   0");
=======
				util::stream_format(stream, "FLINE   0");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x0080:
			if (is_34020)
<<<<<<< HEAD
				sprintf (buffer, "FLINE   1");
=======
				util::stream_format(stream, "FLINE   1");
>>>>>>> upstream/master
			else
				bad = 1;
			break;

		case 0x0100:
<<<<<<< HEAD
			sprintf (buffer, "LINE   0");
			break;

		case 0x0180:
			sprintf (buffer, "LINE   1");
=======
			util::stream_format(stream, "LINE   0");
			break;

		case 0x0180:
			util::stream_format(stream, "LINE   1");
>>>>>>> upstream/master
			break;

		default:
			bad = 1;
		}
		break;

	case 0xe000:
<<<<<<< HEAD
		sprintf (buffer, "ADDXY  ");
		print_src_des_reg();
=======
		util::stream_format(stream, "ADDXY  ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0xe200:
<<<<<<< HEAD
		sprintf (buffer, "SUBXY  ");
		print_src_des_reg();
=======
		util::stream_format(stream, "SUBXY  ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0xe400:
<<<<<<< HEAD
		sprintf (buffer, "CMPXY  ");
		print_src_des_reg();
=======
		util::stream_format(stream, "CMPXY  ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0xe600:
<<<<<<< HEAD
		sprintf (buffer, "CPW    ");
		print_src_des_reg();
=======
		util::stream_format(stream, "CPW    ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0xe800:
<<<<<<< HEAD
		sprintf (buffer, "CVXYL  ");
		print_src_des_reg();
=======
		util::stream_format(stream, "CVXYL  ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0xea00:
		if (is_34020)
		{
<<<<<<< HEAD
			sprintf (buffer, "CVSXYL ");
			print_src_des_reg();
=======
			util::stream_format(stream, "CVSXYL ");
			print_src_des_reg(stream);
>>>>>>> upstream/master
		}
		else
			bad = 1;
		break;


	case 0xec00:
<<<<<<< HEAD
		sprintf (buffer, "MOVX   ");
		print_src_des_reg();
=======
		util::stream_format(stream, "MOVX   ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0xee00:
<<<<<<< HEAD
		sprintf (buffer, "MOVY   ");
		print_src_des_reg();
=======
		util::stream_format(stream, "MOVY   ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0xf000:
<<<<<<< HEAD
		sprintf (buffer, "PIXT   ");
		print_src_reg();
		strcat(buffer, ",*");
		print_des_reg();
		strcat(buffer, ",XY");
=======
		util::stream_format(stream, "PIXT   ");
		print_src_reg(stream);
		stream << ",*";
		print_des_reg(stream);
		stream << ",XY";
>>>>>>> upstream/master
		break;


	case 0xf200:
<<<<<<< HEAD
		sprintf (buffer, "PIXT   *");
		print_src_reg();
		strcat(buffer, ",XY,");
		print_des_reg();
=======
		util::stream_format(stream, "PIXT   *");
		print_src_reg(stream);
		stream << ",XY,";
		print_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0xf400:
<<<<<<< HEAD
		sprintf (buffer, "PIXT   *");
		print_src_reg();
		strcat(buffer, ",XY,*");
		print_des_reg();
		strcat(buffer, ",XY");
=======
		util::stream_format(stream, "PIXT   *");
		print_src_reg(stream);
		stream << ",XY,*";
		print_des_reg(stream);
		stream << ",XY";
>>>>>>> upstream/master
		break;


	case 0xf600:
<<<<<<< HEAD
		sprintf (buffer, "DRAV   ");
		print_src_des_reg();
=======
		util::stream_format(stream, "DRAV   ");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0xf800:
<<<<<<< HEAD
		sprintf (buffer, "PIXT   ");
		print_src_reg();
		strcat(buffer, ",*");
		print_des_reg();
=======
		util::stream_format(stream, "PIXT   ");
		print_src_reg(stream);
		stream << ",*";
		print_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0xfa00:
<<<<<<< HEAD
		sprintf (buffer, "PIXT   *");
		print_src_des_reg();
=======
		util::stream_format(stream, "PIXT   *");
		print_src_des_reg(stream);
>>>>>>> upstream/master
		break;


	case 0xfc00:
<<<<<<< HEAD
		sprintf (buffer, "PIXT   *");
		print_src_reg();
		strcat(buffer, ",*");
		print_des_reg();
=======
		util::stream_format(stream, "PIXT   *");
		print_src_reg(stream);
		stream << ",*";
		print_des_reg(stream);
>>>>>>> upstream/master
		break;

	default:
		bad = 1;
	}

	if (bad)
	{
<<<<<<< HEAD
		sprintf (buffer, "DW     %04Xh", op & 0xffff);
=======
		util::stream_format(stream, "DW     %04Xh", op & 0xffff);
>>>>>>> upstream/master
	}

	return (_pc - __pc) | flags | DASMFLAG_SUPPORTED;
}

CPU_DISASSEMBLE( tms34010 )
{
	rombase = oprom;
	rambase = opram;
	pcbase = pc;
<<<<<<< HEAD
	return Dasm340x0(buffer, pc, 0);
=======
	return Dasm340x0(stream, pc, false);
>>>>>>> upstream/master
}

CPU_DISASSEMBLE( tms34020 )
{
	rombase = oprom;
	rambase = opram;
	pcbase = pc;
<<<<<<< HEAD
	return Dasm340x0(buffer, pc, 1);
=======
	return Dasm340x0(stream, pc, true);
>>>>>>> upstream/master
}
