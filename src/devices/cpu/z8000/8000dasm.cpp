// license:BSD-3-Clause
// copyright-holders:Juergen Buchmueller,Ernesto Corvi
/*****************************************************************************
 *
 *   8000dasm.c
 *   Portable Z8000(2) emulator
 *   Z8000 disassembler; requires the z8000_exec table to be initialized
 *
 *****************************************************************************/

#include "emu.h"
#include "z8000.h"
#include "z8000cpu.h"
<<<<<<< HEAD
=======

>>>>>>> upstream/master
#include "debugger.h"
#include "debug/debugvw.h"
#include "debug/debugcon.h"

<<<<<<< HEAD
=======

>>>>>>> upstream/master
static int n[16];   /* opcode nibbles */
static int b[8];    /* opcode bytes */
static int w[4];    /* opcode words */

<<<<<<< HEAD
static void GET_OP(const UINT8 *oprom, int i, unsigned offset)
{
	UINT16 opcode = (oprom[offset] << 8) | oprom[offset + 1];
=======
static void GET_OP(const uint8_t *oprom, int i, unsigned offset)
{
	uint16_t opcode = (oprom[offset] << 8) | oprom[offset + 1];
>>>>>>> upstream/master
	w[i] = opcode;
	b[i*2+0] = opcode >> 8;
	b[i*2+1] = opcode & 0xff;
	n[i*4+0] = (opcode >> 12) & 0x0f;
	n[i*4+1] = (opcode >> 8) & 0x0f;
	n[i*4+2] = (opcode >> 4) & 0x0f;
	n[i*4+3] = opcode & 0x0f;
}

static const char *const cc[16] = {
	"n",   "lt",  "le",  "ule",  "pe/ov",   "mi",  "eq/z",   "c/ult",
	"a",   "ge",  "gt",  "ugt",  "po/nov",  "pl",  "ne/nz",  "nc/uge"
};

static const char *const flg[16] = {
	"",    "p/v",  "s",   "p/v,s",   "z",   "p/v,z",  "s,z",  "p/v,s,z",
	"c",   "p/v,c","s,c", "p/v,s,c", "z,c", "p/v,z,c","s,z,c","p/v,s,z,c"
};

static const char *const ints[4] = {
	"",    "vi",  "nvi",   "vi,nvi"
};

int z8k_segm;                               /* Current disassembler mode: 0 - non-segmented, 1 - segmented */
int z8k_segm_mode = Z8K_SEGM_MODE_AUTO;     /* User disassembler mode setting: segmented, non-segmented, auto */

<<<<<<< HEAD
void z8k_disass_mode(running_machine &machine, int ref, int params, const char *param[])
{
	size_t len;
	if (params == 1)
	{
		len = strlen(param[0]);
		if (!core_strnicmp(param[0], "segmented", len) || !core_stricmp(param[0], "z8001")) {
			z8k_segm = true;
			z8k_segm_mode = Z8K_SEGM_MODE_SEG;
			debug_console_printf(machine, "Disassembler mode set to Z8001/segmented\n");
		}
		else if (!core_strnicmp(param[0], "non-segmented", len) || !core_stricmp(param[0], "z8002")) {
			z8k_segm = false;
			z8k_segm_mode = Z8K_SEGM_MODE_NONSEG;
			debug_console_printf(machine, "Disassembler mode set to Z8002/non-segmented\n");
		}
		else if (!core_strnicmp(param[0], "automatic", len)) {
			z8k_segm_mode = Z8K_SEGM_MODE_AUTO;
			debug_console_printf(machine, "Disassembler mode set to automatic\n");
		}
		else
			goto usage;
	}
	else if (params > 1) {
	usage:
		debug_console_printf(machine, "Usage: z8k_disass_mode <mode>\n");
		debug_console_printf(machine, "       set disassembler mode\n");
		debug_console_printf(machine, "       mode: \"segmented\" or \"z8001\"     - Z8001 mode\n");
		debug_console_printf(machine, "             \"non-segmented\" or \"z8002\" - Z8002 mode\n");
		debug_console_printf(machine, "             \"automatic\"                  - automatic mode\n");
	}
	else {
		debug_console_printf(machine, "Current disassembler mode: ");
		if (z8k_segm_mode == Z8K_SEGM_MODE_AUTO)
			debug_console_printf(machine, "automatic, currently ");
		debug_console_printf(machine, "%s\n", z8k_segm ? "Z8001/segmented" : "Z8002/non-segmented");
	}
}

CPU_DISASSEMBLE( z8000 )
{
	int new_pc = pc, i, j, tmp;
	char *dst = buffer;
	const char *src;
	Z8000_exec *o;
	UINT32 flags = 0;
	UINT32 old_w;

	/* already initialized? */
	if(z8000_exec == NULL)
		z8000_init_tables();
=======
CPU_DISASSEMBLE(z8000)
{
	int new_pc = pc, i, j, tmp;
	const char *src;
	z8002_device::Z8000_dasm o;
	uint32_t flags = 0;
	uint32_t old_w;

	z8002_device::init_tables();
>>>>>>> upstream/master

	GET_OP(oprom, 0, new_pc - pc);
	new_pc += 2;
	switch (pc)
	{
		case 0x0000:
<<<<<<< HEAD
			dst += sprintf(dst, ".word   #%%%04x ;RST", w[0]);
			break;
		case 0x0002:
			dst += sprintf(dst, ".word   #%%%04x ;RST FCW", w[0]);
			break;
		case 0x0004:
			dst += sprintf(dst, ".word   #%%%04x ;RST PC", w[0]);
			break;
		default:
			o = &z8000_exec[w[0]];
			if (o->size > 1) { GET_OP(oprom, 1, new_pc - pc); new_pc += 2; }
			if (o->size > 2) { GET_OP(oprom, 2, new_pc - pc); new_pc += 2; }
			src = o->dasm;
			flags = o->dasmflags;
=======
			util::stream_format(stream, ".word   #%%%04x ;RST", w[0]);
			break;
		case 0x0002:
			util::stream_format(stream, ".word   #%%%04x ;RST FCW", w[0]);
			break;
		case 0x0004:
			util::stream_format(stream, ".word   #%%%04x ;RST PC", w[0]);
			break;
		default:
			o = z8002_device::dasm(w[0]);
			if (o.size > 1) { GET_OP(oprom, 1, new_pc - pc); new_pc += 2; }
			if (o.size > 2) { GET_OP(oprom, 2, new_pc - pc); new_pc += 2; }
			src = o.dasm;
			flags = o.flags;
>>>>>>> upstream/master

			while (*src)
			{
				if (*src == '%')
				{
					src++;
					switch (*src) {
					case '0': case '1': case '2': case '3':
					case '4': case '5': case '6': case '7':
						/* nibble number */
						i = *src++ - '0';
<<<<<<< HEAD
						dst += sprintf(dst, "%d", n[i]);
=======
						util::stream_format(stream, "%d", n[i]);
>>>>>>> upstream/master
						break;
					case '#':
						/* immediate */
						src++;
						switch (*src++) {
							case 'b': /* imm8 (byte) */
								i = *src++ - '0';
<<<<<<< HEAD
								dst += sprintf(dst, "#%%%02x", b[i]);
								break;
							case 'w': /* imm16 (word) */
								i = *src++ - '0';
								dst += sprintf(dst, "#%%%04x", w[i]);
								break;
							case 'l': /* imm32 (long) */
								i = *src++ - '0';
								dst += sprintf(dst, "#%%%04x%04x", w[i], w[i+1]);
=======
								util::stream_format(stream, "#%%%02x", b[i]);
								break;
							case 'w': /* imm16 (word) */
								i = *src++ - '0';
								util::stream_format(stream, "#%%%04x", w[i]);
								break;
							case 'l': /* imm32 (long) */
								i = *src++ - '0';
								util::stream_format(stream, "#%%%04x%04x", w[i], w[i+1]);
>>>>>>> upstream/master
								break;
						}
						break;
					case '$':
						/* absolute immediate 8bit (rl/rr) */
						src++;
						i = *src++ - '0';
<<<<<<< HEAD
						dst += sprintf(dst, "#%d", ((INT8)b[i]<0) ? -(INT8)b[i] : b[i]);
=======
						util::stream_format(stream, "#%d", ((int8_t)b[i]<0) ? -(int8_t)b[i] : b[i]);
>>>>>>> upstream/master
						break;
					case '+':
						/* imm4m1 (inc/dec value) */
						src++;
						i = *src++ - '0';
<<<<<<< HEAD
						dst += sprintf(dst, "%i", n[i] + 1);
=======
						util::stream_format(stream, "%i", n[i] + 1);
>>>>>>> upstream/master
						break;
					case '*':
						/* left/right (rotate/shift) */
						src++;
<<<<<<< HEAD
						dst += sprintf(dst, "%c", b[2] ? 'r' : 'l');
=======
						util::stream_format(stream, "%c", b[2] ? 'r' : 'l');
>>>>>>> upstream/master
						break;
					case '?':
						/* imm1or2 (shift/rotate once or twice) */
						src++;
						i = *src++ - '0';
<<<<<<< HEAD
						dst += sprintf(dst, "%c", (n[i] & 2) ? '2' : '1');
=======
						util::stream_format(stream, "%c", (n[i] & 2) ? '2' : '1');
>>>>>>> upstream/master
						break;
					case 'R':
						src++;
						//tmp = ((n[1] & 0x01) << 16) + (n[3] << 8) + (n[7] & 0x08);
						tmp = ((n[1] & 0x01) << 8) + (n[3] << 4) + (n[7] & 0x08);
						switch (tmp)
						{
<<<<<<< HEAD
							case 0x000: dst += sprintf(dst, "inirb "); flags = DASMFLAG_STEP_OVER; break;
							case 0x008: dst += sprintf(dst, "inib  "); break;
							case 0x010: dst += sprintf(dst, "sinirb"); flags = DASMFLAG_STEP_OVER; break;
							case 0x018: dst += sprintf(dst, "sinib "); break;
							case 0x020: dst += sprintf(dst, "otirb "); flags = DASMFLAG_STEP_OVER; break;
							case 0x028: dst += sprintf(dst, "outib "); break;
							case 0x030: dst += sprintf(dst, "soutib"); break;
							case 0x038: dst += sprintf(dst, "sotirb"); flags = DASMFLAG_STEP_OVER; break;
							case 0x040: dst += sprintf(dst, "inb   "); break;
							case 0x048: dst += sprintf(dst, "inb   "); break;
							case 0x050: dst += sprintf(dst, "sinb  "); break;
							case 0x058: dst += sprintf(dst, "sinb  "); break;
							case 0x060: dst += sprintf(dst, "outb  "); break;
							case 0x068: dst += sprintf(dst, "outb  "); break;
							case 0x070: dst += sprintf(dst, "soutb "); break;
							case 0x078: dst += sprintf(dst, "soutb "); break;
							case 0x080: dst += sprintf(dst, "indrb "); flags = DASMFLAG_STEP_OVER; break;
							case 0x088: dst += sprintf(dst, "indb  "); break;
							case 0x090: dst += sprintf(dst, "sindrb"); flags = DASMFLAG_STEP_OVER; break;
							case 0x098: dst += sprintf(dst, "sindb "); break;
							case 0x0a0: dst += sprintf(dst, "otdrb "); flags = DASMFLAG_STEP_OVER; break;
							case 0x0a8: dst += sprintf(dst, "outdb "); break;
							case 0x0b0: dst += sprintf(dst, "soutdb"); break;
							case 0x0b8: dst += sprintf(dst, "sotdrb"); flags = DASMFLAG_STEP_OVER; break;
							case 0x100: dst += sprintf(dst, "inir  "); flags = DASMFLAG_STEP_OVER; break;
							case 0x108: dst += sprintf(dst, "ini   "); break;
							case 0x110: dst += sprintf(dst, "sinir "); flags = DASMFLAG_STEP_OVER; break;
							case 0x118: dst += sprintf(dst, "sini  "); break;
							case 0x120: dst += sprintf(dst, "otir  "); flags = DASMFLAG_STEP_OVER; break;
							case 0x128: dst += sprintf(dst, "outi  "); break;
							case 0x130: dst += sprintf(dst, "souti "); break;
							case 0x138: dst += sprintf(dst, "sotir "); flags = DASMFLAG_STEP_OVER; break;
							case 0x140: dst += sprintf(dst, "in    "); break;
							case 0x148: dst += sprintf(dst, "in    "); break;
							case 0x150: dst += sprintf(dst, "sin   "); break;
							case 0x158: dst += sprintf(dst, "sin   "); break;
							case 0x160: dst += sprintf(dst, "out   "); break;
							case 0x168: dst += sprintf(dst, "out   "); break;
							case 0x170: dst += sprintf(dst, "sout  "); break;
							case 0x178: dst += sprintf(dst, "sout  "); break;
							case 0x180: dst += sprintf(dst, "indr  "); flags = DASMFLAG_STEP_OVER; break;
							case 0x188: dst += sprintf(dst, "ind   "); break;
							case 0x190: dst += sprintf(dst, "sindr "); flags = DASMFLAG_STEP_OVER; break;
							case 0x198: dst += sprintf(dst, "sind  "); break;
							case 0x1a0: dst += sprintf(dst, "otdr  "); flags = DASMFLAG_STEP_OVER; break;
							case 0x1a8: dst += sprintf(dst, "outd  "); break;
							case 0x1b0: dst += sprintf(dst, "soutd "); break;
							case 0x1b8: dst += sprintf(dst, "sotdr "); flags = DASMFLAG_STEP_OVER; break;
							default:
								dst += sprintf(dst, "unk(0x%x)", tmp);
=======
							case 0x000: util::stream_format(stream, "inirb "); flags = DASMFLAG_STEP_OVER; break;
							case 0x008: util::stream_format(stream, "inib  "); break;
							case 0x010: util::stream_format(stream, "sinirb"); flags = DASMFLAG_STEP_OVER; break;
							case 0x018: util::stream_format(stream, "sinib "); break;
							case 0x020: util::stream_format(stream, "otirb "); flags = DASMFLAG_STEP_OVER; break;
							case 0x028: util::stream_format(stream, "outib "); break;
							case 0x030: util::stream_format(stream, "soutib"); break;
							case 0x038: util::stream_format(stream, "sotirb"); flags = DASMFLAG_STEP_OVER; break;
							case 0x040: util::stream_format(stream, "inb   "); break;
							case 0x048: util::stream_format(stream, "inb   "); break;
							case 0x050: util::stream_format(stream, "sinb  "); break;
							case 0x058: util::stream_format(stream, "sinb  "); break;
							case 0x060: util::stream_format(stream, "outb  "); break;
							case 0x068: util::stream_format(stream, "outb  "); break;
							case 0x070: util::stream_format(stream, "soutb "); break;
							case 0x078: util::stream_format(stream, "soutb "); break;
							case 0x080: util::stream_format(stream, "indrb "); flags = DASMFLAG_STEP_OVER; break;
							case 0x088: util::stream_format(stream, "indb  "); break;
							case 0x090: util::stream_format(stream, "sindrb"); flags = DASMFLAG_STEP_OVER; break;
							case 0x098: util::stream_format(stream, "sindb "); break;
							case 0x0a0: util::stream_format(stream, "otdrb "); flags = DASMFLAG_STEP_OVER; break;
							case 0x0a8: util::stream_format(stream, "outdb "); break;
							case 0x0b0: util::stream_format(stream, "soutdb"); break;
							case 0x0b8: util::stream_format(stream, "sotdrb"); flags = DASMFLAG_STEP_OVER; break;
							case 0x100: util::stream_format(stream, "inir  "); flags = DASMFLAG_STEP_OVER; break;
							case 0x108: util::stream_format(stream, "ini   "); break;
							case 0x110: util::stream_format(stream, "sinir "); flags = DASMFLAG_STEP_OVER; break;
							case 0x118: util::stream_format(stream, "sini  "); break;
							case 0x120: util::stream_format(stream, "otir  "); flags = DASMFLAG_STEP_OVER; break;
							case 0x128: util::stream_format(stream, "outi  "); break;
							case 0x130: util::stream_format(stream, "souti "); break;
							case 0x138: util::stream_format(stream, "sotir "); flags = DASMFLAG_STEP_OVER; break;
							case 0x140: util::stream_format(stream, "in    "); break;
							case 0x148: util::stream_format(stream, "in    "); break;
							case 0x150: util::stream_format(stream, "sin   "); break;
							case 0x158: util::stream_format(stream, "sin   "); break;
							case 0x160: util::stream_format(stream, "out   "); break;
							case 0x168: util::stream_format(stream, "out   "); break;
							case 0x170: util::stream_format(stream, "sout  "); break;
							case 0x178: util::stream_format(stream, "sout  "); break;
							case 0x180: util::stream_format(stream, "indr  "); flags = DASMFLAG_STEP_OVER; break;
							case 0x188: util::stream_format(stream, "ind   "); break;
							case 0x190: util::stream_format(stream, "sindr "); flags = DASMFLAG_STEP_OVER; break;
							case 0x198: util::stream_format(stream, "sind  "); break;
							case 0x1a0: util::stream_format(stream, "otdr  "); flags = DASMFLAG_STEP_OVER; break;
							case 0x1a8: util::stream_format(stream, "outd  "); break;
							case 0x1b0: util::stream_format(stream, "soutd "); break;
							case 0x1b8: util::stream_format(stream, "sotdr "); flags = DASMFLAG_STEP_OVER; break;
							default:
								util::stream_format(stream, "unk(0x%x)", tmp);
>>>>>>> upstream/master
						}
						break;
					case 'a':
						/* address */
						src++;
						i = *src++ - '0';
						if (z8k_segm) {
							if (w[i] & 0x8000) {
								old_w = w[i];
<<<<<<< HEAD
								for (j = i; j < o->size; j++)
									w[j] = w[j + 1];
								GET_OP(oprom, o->size - 1, new_pc - pc);
=======
								for (j = i; j < o.size; j++)
									w[j] = w[j + 1];
								GET_OP(oprom, o.size - 1, new_pc - pc);
>>>>>>> upstream/master
								new_pc += 2;
								w[i] = ((old_w & 0x7f00) << 16) | (w[i] & 0xffff);
							}
							else {
								w[i] = ((w[i] & 0x7f00) << 16) | (w[i] & 0xff);
							}
<<<<<<< HEAD
							dst += sprintf(dst, "<%%%02X>%%%04X", (w[i] >> 24) & 0xff, w[i] & 0xffff);
						}
						else dst += sprintf(dst, "%%%04x", w[i]);
=======
							util::stream_format(stream, "<%%%02X>%%%04X", (w[i] >> 24) & 0xff, w[i] & 0xffff);
						}
						else util::stream_format(stream, "%%%04x", w[i]);
>>>>>>> upstream/master
						break;
					case 'c':
						/* condition code */
						src++;
						i = *src++ - '0';
						if (n[i] == 8) {    /* always? */
							/* skip following comma */
							if (*src == ',')
								src++;
						}
<<<<<<< HEAD
						else dst += sprintf(dst, "%s", cc[n[i]]);
=======
						else util::stream_format(stream, "%s", cc[n[i]]);
>>>>>>> upstream/master
						break;
					case 'd':
						/* displacement */
						src++;
						i = *src++ - '0';
						switch (i) {
							case 0: /* disp7 */
								tmp = new_pc - 2 * (w[0] & 0x7f);
								break;
							case 1: /* disp8 */
<<<<<<< HEAD
								tmp = new_pc + 2 * (INT8)(w[0] & 0xff);
=======
								tmp = new_pc + 2 * (int8_t)(w[0] & 0xff);
>>>>>>> upstream/master
								break;
							case 2: /* disp12 */
								tmp = w[0] & 0x7ff;
								if (w[0] & 0x800)
									tmp = new_pc + 0x1000 -2 * tmp;
								else
									tmp = new_pc + -2 * tmp;
								break;
							default:
								tmp = 0;
								abort();
						}
						if (z8k_segm)
<<<<<<< HEAD
							dst += sprintf(dst, "<%%%02X>%%%04X", (tmp >> 16) & 0xff, tmp & 0xffff);
						else
							dst += sprintf(dst, "%%%04x", tmp);
=======
							util::stream_format(stream, "<%%%02X>%%%04X", (tmp >> 16) & 0xff, tmp & 0xffff);
						else
							util::stream_format(stream, "%%%04x", tmp);
>>>>>>> upstream/master
						break;
					case 'f':
						/* flag (setflg/resflg/comflg) */
						src++;
						i = *src++ - '0';
<<<<<<< HEAD
						dst += sprintf(dst, "%s", flg[n[i]]);
=======
						util::stream_format(stream, "%s", flg[n[i]]);
>>>>>>> upstream/master
						break;
					case 'i':
						/* interrupts */
						src++;
						i = *src++ - '0';
<<<<<<< HEAD
						dst += sprintf(dst, "%s", ints[n[i] & 3]);
=======
						util::stream_format(stream, "%s", ints[n[i] & 3]);
>>>>>>> upstream/master
						break;
					case 'n':
						/* register count for ldm */
						src++;
<<<<<<< HEAD
						dst += sprintf(dst, "%d", n[7] + 1);
=======
						util::stream_format(stream, "%d", n[7] + 1);
>>>>>>> upstream/master
						break;
					case 'p':
						/* disp16 (pc relative) */
						src++;
						i = *src++ - '0';
<<<<<<< HEAD
						dst += sprintf(dst, "%%%04x", new_pc + w[i]);
=======
						util::stream_format(stream, "%%%04x", new_pc + w[i]);
>>>>>>> upstream/master
						break;
					case 'r':
						/* register */
						src++;
						switch (*src++) {
							case 'b':
								/* byte */
								i = *src++ - '0';
								if (n[i] & 8)
<<<<<<< HEAD
									dst += sprintf(dst, "rl%d", n[i] & 7);
								else
									dst += sprintf(dst, "rh%d", n[i]);
=======
									util::stream_format(stream, "rl%d", n[i] & 7);
								else
									util::stream_format(stream, "rh%d", n[i]);
>>>>>>> upstream/master
								break;
							case 'w':
								/* word */
								i = *src++ - '0';
<<<<<<< HEAD
								dst += sprintf(dst, "r%d", n[i]);
=======
								util::stream_format(stream, "r%d", n[i]);
>>>>>>> upstream/master
								break;
							case 'l':
								/* long */
								i = *src++ - '0';
<<<<<<< HEAD
								dst += sprintf(dst, "rr%d", n[i]);
=======
								util::stream_format(stream, "rr%d", n[i]);
>>>>>>> upstream/master
								break;
							case 'q':
								/* quad word (long long) */
								i = *src++ - '0';
<<<<<<< HEAD
								dst += sprintf(dst, "rq%d", n[i]);
=======
								util::stream_format(stream, "rq%d", n[i]);
>>>>>>> upstream/master
								break;
						}
						break;
					default:
<<<<<<< HEAD
						*dst++ = '%';
						*dst++ = *src++;
						break;
					}
				} else *dst++ = *src++;
			}
			*dst = '\0';
=======
						stream << '%' << *src++;
						break;
					}
				} else stream << *src++;
			}
>>>>>>> upstream/master
			break;
	}
	return (new_pc - pc) | flags | DASMFLAG_SUPPORTED;
}
