// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    ccpudasm.c
    Core implementation for the portable Cinematronics CPU disassembler.

    Written by Aaron Giles
    Special thanks to Zonn Moore for his detailed documentation.

***************************************************************************/

#include "emu.h"
#include "ccpu.h"


<<<<<<< HEAD
CPU_DISASSEMBLE( ccpu )
{
	unsigned startpc = pc;
	UINT8 opcode = oprom[pc++ - startpc];
	UINT8 tempval;
=======
CPU_DISASSEMBLE(ccpu)
{
	unsigned startpc = pc;
	uint8_t opcode = oprom[pc++ - startpc];
	uint8_t tempval;
>>>>>>> upstream/master

	switch (opcode)
	{
		/* LDAI */
		case 0x00:  case 0x01:  case 0x02:  case 0x03:
		case 0x04:  case 0x05:  case 0x06:  case 0x07:
		case 0x08:  case 0x09:  case 0x0a:  case 0x0b:
		case 0x0c:  case 0x0d:  case 0x0e:  case 0x0f:
<<<<<<< HEAD
			sprintf(buffer, "LDAI $%X", opcode & 0x0f);
=======
			util::stream_format(stream, "LDAI $%X", opcode & 0x0f);
>>>>>>> upstream/master
			break;

		/* INP */
		case 0x10:  case 0x11:  case 0x12:  case 0x13:
		case 0x14:  case 0x15:  case 0x16:  case 0x17:
		case 0x18:  case 0x19:  case 0x1a:  case 0x1b:
		case 0x1c:  case 0x1d:  case 0x1e:  case 0x1f:
<<<<<<< HEAD
			sprintf(buffer, "INP  $%X", opcode & 0x0f);
=======
			util::stream_format(stream, "INP  $%X", opcode & 0x0f);
>>>>>>> upstream/master
			break;

		/* A8I */
		case 0x20:
<<<<<<< HEAD
			sprintf(buffer, "A8I  $%X", oprom[pc++ - startpc]);
=======
			util::stream_format(stream, "A8I  $%X", oprom[pc++ - startpc]);
>>>>>>> upstream/master
			break;

		/* A4I */
		case 0x21:  case 0x22:  case 0x23:
		case 0x24:  case 0x25:  case 0x26:  case 0x27:
		case 0x28:  case 0x29:  case 0x2a:  case 0x2b:
		case 0x2c:  case 0x2d:  case 0x2e:  case 0x2f:
<<<<<<< HEAD
			sprintf(buffer, "A4I  $%X", opcode & 0x0f);
=======
			util::stream_format(stream, "A4I  $%X", opcode & 0x0f);
>>>>>>> upstream/master
			break;

		/* S8I */
		case 0x30:
<<<<<<< HEAD
			sprintf(buffer, "S8I  $%X", oprom[pc++ - startpc]);
=======
			util::stream_format(stream, "S8I  $%X", oprom[pc++ - startpc]);
>>>>>>> upstream/master
			break;

		/* S4I */
		case 0x31:  case 0x32:  case 0x33:
		case 0x34:  case 0x35:  case 0x36:  case 0x37:
		case 0x38:  case 0x39:  case 0x3a:  case 0x3b:
		case 0x3c:  case 0x3d:  case 0x3e:  case 0x3f:
<<<<<<< HEAD
			sprintf(buffer, "S4I  $%X", opcode & 0x0f);
=======
			util::stream_format(stream, "S4I  $%X", opcode & 0x0f);
>>>>>>> upstream/master
			break;

		/* LPAI */
		case 0x40:  case 0x41:  case 0x42:  case 0x43:
		case 0x44:  case 0x45:  case 0x46:  case 0x47:
		case 0x48:  case 0x49:  case 0x4a:  case 0x4b:
		case 0x4c:  case 0x4d:  case 0x4e:  case 0x4f:
			tempval = oprom[pc++ - startpc];
<<<<<<< HEAD
			sprintf(buffer, "LPAI $%03X", (opcode & 0x0f) + (tempval & 0xf0) + ((tempval & 0x0f) << 8));
=======
			util::stream_format(stream, "LPAI $%03X", (opcode & 0x0f) + (tempval & 0xf0) + ((tempval & 0x0f) << 8));
>>>>>>> upstream/master
			break;

		/* T4K */
		case 0x50:
<<<<<<< HEAD
			sprintf(buffer, "T4K");
=======
			util::stream_format(stream, "T4K");
>>>>>>> upstream/master
			break;

		/* JMIB/JEHB */
		case 0x51:
<<<<<<< HEAD
			sprintf(buffer, "JMIB/JEHB");
=======
			util::stream_format(stream, "JMIB/JEHB");
>>>>>>> upstream/master
			break;

		/* JVNB */
		case 0x52:
<<<<<<< HEAD
			sprintf(buffer, "JVNB");
=======
			util::stream_format(stream, "JVNB");
>>>>>>> upstream/master
			break;

		/* JLTB */
		case 0x53:
<<<<<<< HEAD
			sprintf(buffer, "JLTB");
=======
			util::stream_format(stream, "JLTB");
>>>>>>> upstream/master
			break;

		/* JEQB */
		case 0x54:
<<<<<<< HEAD
			sprintf(buffer, "JEQB");
=======
			util::stream_format(stream, "JEQB");
>>>>>>> upstream/master
			break;

		/* JCZB */
		case 0x55:
<<<<<<< HEAD
			sprintf(buffer, "JCZB");
=======
			util::stream_format(stream, "JCZB");
>>>>>>> upstream/master
			break;

		/* JOSB */
		case 0x56:
<<<<<<< HEAD
			sprintf(buffer, "JOSB");
=======
			util::stream_format(stream, "JOSB");
>>>>>>> upstream/master
			break;

		/* SSA */
		case 0x57:
<<<<<<< HEAD
			sprintf(buffer, "SSA");
=======
			util::stream_format(stream, "SSA");
>>>>>>> upstream/master
			break;

		/* JMP */
		case 0x58:
<<<<<<< HEAD
			sprintf(buffer, "JMP");
=======
			util::stream_format(stream, "JMP");
>>>>>>> upstream/master
			break;

		/* JMI/JEH */
		case 0x59:
<<<<<<< HEAD
			sprintf(buffer, "JMI/JEH");
=======
			util::stream_format(stream, "JMI/JEH");
>>>>>>> upstream/master
			break;

		/* JVN */
		case 0x5a:
<<<<<<< HEAD
			sprintf(buffer, "JVN");
=======
			util::stream_format(stream, "JVN");
>>>>>>> upstream/master
			break;

		/* JLT */
		case 0x5b:
<<<<<<< HEAD
			sprintf(buffer, "JLT");
=======
			util::stream_format(stream, "JLT");
>>>>>>> upstream/master
			break;

		/* JEQ */
		case 0x5c:
<<<<<<< HEAD
			sprintf(buffer, "JEQ");
=======
			util::stream_format(stream, "JEQ");
>>>>>>> upstream/master
			break;

		/* JCZ */
		case 0x5d:
<<<<<<< HEAD
			sprintf(buffer, "JCZ");
=======
			util::stream_format(stream, "JCZ");
>>>>>>> upstream/master
			break;

		/* JOS */
		case 0x5e:
<<<<<<< HEAD
			sprintf(buffer, "JOS");
=======
			util::stream_format(stream, "JOS");
>>>>>>> upstream/master
			break;

		/* NOP */
		case 0x5f:
<<<<<<< HEAD
			sprintf(buffer, "NOP");
=======
			util::stream_format(stream, "NOP");
>>>>>>> upstream/master
			break;

		/* ADD */
		case 0x60:  case 0x61:  case 0x62:  case 0x63:
		case 0x64:  case 0x65:  case 0x66:  case 0x67:
		case 0x68:  case 0x69:  case 0x6a:  case 0x6b:
		case 0x6c:  case 0x6d:  case 0x6e:  case 0x6f:
<<<<<<< HEAD
			sprintf(buffer, "ADD  $%X", opcode & 0x0f);
=======
			util::stream_format(stream, "ADD  $%X", opcode & 0x0f);
>>>>>>> upstream/master
			break;

		/* SUB n */
		case 0x70:  case 0x71:  case 0x72:  case 0x73:
		case 0x74:  case 0x75:  case 0x76:  case 0x77:
		case 0x78:  case 0x79:  case 0x7a:  case 0x7b:
		case 0x7c:  case 0x7d:  case 0x7e:  case 0x7f:
<<<<<<< HEAD
			sprintf(buffer, "SUB  $%X", opcode & 0x0f);
=======
			util::stream_format(stream, "SUB  $%X", opcode & 0x0f);
>>>>>>> upstream/master
			break;

		/* SETP n */
		case 0x80:  case 0x81:  case 0x82:  case 0x83:
		case 0x84:  case 0x85:  case 0x86:  case 0x87:
		case 0x88:  case 0x89:  case 0x8a:  case 0x8b:
		case 0x8c:  case 0x8d:  case 0x8e:  case 0x8f:
<<<<<<< HEAD
			sprintf(buffer, "SETP $%X", opcode & 0x0f);
=======
			util::stream_format(stream, "SETP $%X", opcode & 0x0f);
>>>>>>> upstream/master
			break;

		/* OUT */
		case 0x90:  case 0x91:  case 0x92:  case 0x93:
		case 0x94:  case 0x95:  case 0x96:  case 0x97:
		case 0x98:  case 0x99:  case 0x9a:  case 0x9b:
		case 0x9c:  case 0x9d:  case 0x9e:  case 0x9f:
<<<<<<< HEAD
			sprintf(buffer, "OUT  $%X", opcode & 0x0f);
=======
			util::stream_format(stream, "OUT  $%X", opcode & 0x0f);
>>>>>>> upstream/master
			break;

		/* LDA */
		case 0xa0:  case 0xa1:  case 0xa2:  case 0xa3:
		case 0xa4:  case 0xa5:  case 0xa6:  case 0xa7:
		case 0xa8:  case 0xa9:  case 0xaa:  case 0xab:
		case 0xac:  case 0xad:  case 0xae:  case 0xaf:
<<<<<<< HEAD
			sprintf(buffer, "LDA  $%X", opcode & 0x0f);
=======
			util::stream_format(stream, "LDA  $%X", opcode & 0x0f);
>>>>>>> upstream/master
			break;

		/* CMP */
		case 0xb0:  case 0xb1:  case 0xb2:  case 0xb3:
		case 0xb4:  case 0xb5:  case 0xb6:  case 0xb7:
		case 0xb8:  case 0xb9:  case 0xba:  case 0xbb:
		case 0xbc:  case 0xbd:  case 0xbe:  case 0xbf:
<<<<<<< HEAD
			sprintf(buffer, "TST  $%X", opcode & 0x0f);
=======
			util::stream_format(stream, "TST  $%X", opcode & 0x0f);
>>>>>>> upstream/master
			break;

		/* WS */
		case 0xc0:  case 0xc1:  case 0xc2:  case 0xc3:
		case 0xc4:  case 0xc5:  case 0xc6:  case 0xc7:
		case 0xc8:  case 0xc9:  case 0xca:  case 0xcb:
		case 0xcc:  case 0xcd:  case 0xce:  case 0xcf:
<<<<<<< HEAD
			sprintf(buffer, "WS   $%X", opcode & 0x0f);
=======
			util::stream_format(stream, "WS   $%X", opcode & 0x0f);
>>>>>>> upstream/master
			break;

		/* STA n */
		case 0xd0:  case 0xd1:  case 0xd2:  case 0xd3:
		case 0xd4:  case 0xd5:  case 0xd6:  case 0xd7:
		case 0xd8:  case 0xd9:  case 0xda:  case 0xdb:
		case 0xdc:  case 0xdd:  case 0xde:  case 0xdf:
<<<<<<< HEAD
			sprintf(buffer, "STA  $%X", opcode & 0x0f);
=======
			util::stream_format(stream, "STA  $%X", opcode & 0x0f);
>>>>>>> upstream/master
			break;

		/* DV */
		case 0xe0:
<<<<<<< HEAD
			sprintf(buffer, "DV");
=======
			util::stream_format(stream, "DV");
>>>>>>> upstream/master
			break;

		/* LPAP */
		case 0xe1:
<<<<<<< HEAD
			sprintf(buffer, "LPAP");
=======
			util::stream_format(stream, "LPAP");
>>>>>>> upstream/master
			break;

		/* WSP */
		case 0xf1:
<<<<<<< HEAD
			sprintf(buffer, "WSP");
=======
			util::stream_format(stream, "WSP");
>>>>>>> upstream/master
			break;

		/* LKP */
		case 0xe2:
		case 0xf2:
<<<<<<< HEAD
			sprintf(buffer, "LKP");
=======
			util::stream_format(stream, "LKP");
>>>>>>> upstream/master
			break;

		/* MUL */
		case 0xe3:
		case 0xf3:
<<<<<<< HEAD
			sprintf(buffer, "MUL");
=======
			util::stream_format(stream, "MUL");
>>>>>>> upstream/master
			break;

		/* NV */
		case 0xe4:
		case 0xf4:
<<<<<<< HEAD
			sprintf(buffer, "NV");
=======
			util::stream_format(stream, "NV");
>>>>>>> upstream/master
			break;

		/* FRM */
		case 0xe5:
		case 0xf5:
<<<<<<< HEAD
			sprintf(buffer, "FRM");
=======
			util::stream_format(stream, "FRM");
>>>>>>> upstream/master
			break;

		/* STAP */
		case 0xe6:
		case 0xf6:
<<<<<<< HEAD
			sprintf(buffer, "STAP");
=======
			util::stream_format(stream, "STAP");
>>>>>>> upstream/master
			break;

		/* CST */
		case 0xf7:
<<<<<<< HEAD
			sprintf(buffer, "CST");
=======
			util::stream_format(stream, "CST");
>>>>>>> upstream/master
			break;

		/* ADDP */
		case 0xe7:
<<<<<<< HEAD
			sprintf(buffer, "ADDP");
=======
			util::stream_format(stream, "ADDP");
>>>>>>> upstream/master
			break;

		/* SUBP */
		case 0xe8:
		case 0xf8:
<<<<<<< HEAD
			sprintf(buffer, "SUBP");
=======
			util::stream_format(stream, "SUBP");
>>>>>>> upstream/master
			break;

		/* ANDP */
		case 0xe9:
		case 0xf9:
<<<<<<< HEAD
			sprintf(buffer, "ANDP");
=======
			util::stream_format(stream, "ANDP");
>>>>>>> upstream/master
			break;

		/* LDAP */
		case 0xea:
		case 0xfa:
<<<<<<< HEAD
			sprintf(buffer, "LDAP");
=======
			util::stream_format(stream, "LDAP");
>>>>>>> upstream/master
			break;

		/* SHR */
		case 0xeb:
		case 0xfb:
<<<<<<< HEAD
			sprintf(buffer, "SHR");
=======
			util::stream_format(stream, "SHR");
>>>>>>> upstream/master
			break;

		/* SHL */
		case 0xec:
		case 0xfc:
<<<<<<< HEAD
			sprintf(buffer, "SHL");
=======
			util::stream_format(stream, "SHL");
>>>>>>> upstream/master
			break;

		/* ASR */
		case 0xed:
		case 0xfd:
<<<<<<< HEAD
			sprintf(buffer, "ASR");
=======
			util::stream_format(stream, "ASR");
>>>>>>> upstream/master
			break;

		/* SHRB */
		case 0xee:
		case 0xfe:
<<<<<<< HEAD
			sprintf(buffer, "SHRB");
=======
			util::stream_format(stream, "SHRB");
>>>>>>> upstream/master
			break;

		/* SHLB */
		case 0xef:
		case 0xff:
<<<<<<< HEAD
			sprintf(buffer, "SHLB");
=======
			util::stream_format(stream, "SHLB");
>>>>>>> upstream/master
			break;

		/* IV */
		case 0xf0:
<<<<<<< HEAD
			sprintf(buffer, "IV");
=======
			util::stream_format(stream, "IV");
>>>>>>> upstream/master
			break;
	}

	return (pc - startpc) | DASMFLAG_SUPPORTED;
}
