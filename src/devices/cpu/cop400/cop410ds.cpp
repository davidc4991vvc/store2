// license:BSD-3-Clause
// copyright-holders:Curt Coder
/***************************************************************************

    cop410ds.c

    National Semiconductor COP410 Emulator.

***************************************************************************/

#include "emu.h"

<<<<<<< HEAD
CPU_DISASSEMBLE( cop410 )
{
	UINT8 opcode = oprom[0];
	UINT8 next_opcode = oprom[1];
	UINT16 address;
	UINT32 flags = 0;
=======
CPU_DISASSEMBLE(cop410)
{
	uint8_t opcode = oprom[0];
	uint8_t next_opcode = oprom[1];
	uint16_t address;
	uint32_t flags = 0;
>>>>>>> upstream/master
	int bytes = 1;

	if ((opcode >= 0x80 && opcode <= 0xBE) || (opcode >= 0xC0 && opcode <= 0xFE))
	{
<<<<<<< HEAD
		if ((pc & 0x3E0) >= 0x80 && (pc & 0x3E0) < 0x100) //JP pages 2,3
		{
			address = (UINT16)((pc & 0x380) | (opcode & 0x7F));
			sprintf(buffer, "JP %x", address);
=======
		int page = pc >> 6;

		if (page == 2 || page == 3) //JP pages 2,3
		{
			address = (uint16_t)((pc & 0x180) | (opcode & 0x7F));
			util::stream_format(stream, "JP %03X", address);
>>>>>>> upstream/master
		}
		else
		{
			if ((opcode & 0xC0) == 0xC0) //JP other pages
			{
<<<<<<< HEAD
				address = (UINT16)((pc & 0x3C0) | (opcode & 0x3F));
				sprintf(buffer, "JP %x", address);
			}
			else                    //JSRP
			{
				address = (UINT16)(0x80 | (opcode & 0x3F));
				sprintf(buffer, "JSRP %x", address);
=======
				address = (uint16_t)((pc & 0x1C0) | (opcode & 0x3F));
				util::stream_format(stream, "JP %03X", address);
			}
			else                    //JSRP
			{
				address = (uint16_t)(0x80 | (opcode & 0x3F));
				util::stream_format(stream, "JSRP %03X", address);
>>>>>>> upstream/master
				flags = DASMFLAG_STEP_OVER;
			}
		}
	}
	else if (opcode >= 0x08 && opcode <= 0x0F)
	{
<<<<<<< HEAD
		sprintf(buffer, "LBI 0,%u", ((opcode & 0xF) + 1) & 0xF);
	}
	else if (opcode >= 0x18 && opcode <= 0x1F)
	{
		sprintf(buffer, "LBI 1,%u", ((opcode & 0xF) + 1) & 0xF);
	}
	else if (opcode >= 0x28 && opcode <= 0x2F)
	{
		sprintf(buffer, "LBI 2,%u", ((opcode & 0xF) + 1) & 0xF);
	}
	else if (opcode >= 0x38 && opcode <= 0x3F)
	{
		sprintf(buffer, "LBI 3,%u", ((opcode & 0xF) + 1) & 0xF);
	}
	else if (opcode >= 0x51 && opcode <= 0x5F)
	{
		sprintf(buffer, "AISC %u", opcode & 0xF);
=======
		util::stream_format(stream, "LBI 0,%u", ((opcode & 0xF) + 1) & 0xF);
	}
	else if (opcode >= 0x18 && opcode <= 0x1F)
	{
		util::stream_format(stream, "LBI 1,%u", ((opcode & 0xF) + 1) & 0xF);
	}
	else if (opcode >= 0x28 && opcode <= 0x2F)
	{
		util::stream_format(stream, "LBI 2,%u", ((opcode & 0xF) + 1) & 0xF);
	}
	else if (opcode >= 0x38 && opcode <= 0x3F)
	{
		util::stream_format(stream, "LBI 3,%u", ((opcode & 0xF) + 1) & 0xF);
	}
	else if (opcode >= 0x51 && opcode <= 0x5F)
	{
		util::stream_format(stream, "AISC %u", opcode & 0xF);
>>>>>>> upstream/master
	}
	else if (opcode >= 0x60 && opcode <= 0x61)
	{
		address = ((opcode & 0x01) << 8) | next_opcode;
<<<<<<< HEAD
		sprintf(buffer, "JMP %x", address);
=======
		util::stream_format(stream, "JMP %03X", address);
>>>>>>> upstream/master
		bytes = 2;
	}
	else if (opcode >= 0x68 && opcode <= 0x69)
	{
		address = ((opcode & 0x01) << 8) | next_opcode;
<<<<<<< HEAD
		sprintf(buffer, "JSR %x", address);
=======
		util::stream_format(stream, "JSR %03X", address);
>>>>>>> upstream/master
		flags = DASMFLAG_STEP_OVER;
		bytes = 2;
	}
	else if (opcode >= 0x70 && opcode <= 0x7F)
	{
<<<<<<< HEAD
		sprintf(buffer, "STII %u", opcode & 0xF);
=======
		util::stream_format(stream, "STII %u", opcode & 0xF);
>>>>>>> upstream/master
	}
	else
	{
		switch (opcode)
		{
		case 0:
<<<<<<< HEAD
			sprintf(buffer, "CLRA");
			break;

		case 1:
			sprintf(buffer, "SKMBZ 0");
			break;

		case 2:
			sprintf(buffer, "XOR");
			break;

		case 3:
			sprintf(buffer, "SKMBZ 2");
			break;

		case 4:
			sprintf(buffer, "XIS 0");
			break;

		case 5:
			sprintf(buffer, "LD 0");
			break;

		case 6:
			sprintf(buffer, "X 0");
			break;

		case 7:
			sprintf(buffer, "XDS 0");
			break;

		case 0x11:
			sprintf(buffer, "SKMBZ 1");
			break;

		case 0x13:
			sprintf(buffer, "SKMBZ 3");
			break;

		case 0x14:
			sprintf(buffer, "XIS 1");
			break;

		case 0x15:
			sprintf(buffer, "LD 1");
			break;

		case 0x16:
			sprintf(buffer, "X 1");
			break;

		case 0x17:
			sprintf(buffer, "XDS 1");
			break;

		case 0x20:
			sprintf(buffer, "SKC");
			break;

		case 0x21:
			sprintf(buffer, "SKE");
			break;

		case 0x22:
			sprintf(buffer, "SC");
=======
			util::stream_format(stream, "CLRA");
			break;

		case 1:
			util::stream_format(stream, "SKMBZ 0");
			break;

		case 2:
			util::stream_format(stream, "XOR");
			break;

		case 3:
			util::stream_format(stream, "SKMBZ 2");
			break;

		case 4:
			util::stream_format(stream, "XIS 0");
			break;

		case 5:
			util::stream_format(stream, "LD 0");
			break;

		case 6:
			util::stream_format(stream, "X 0");
			break;

		case 7:
			util::stream_format(stream, "XDS 0");
			break;

		case 0x11:
			util::stream_format(stream, "SKMBZ 1");
			break;

		case 0x13:
			util::stream_format(stream, "SKMBZ 3");
			break;

		case 0x14:
			util::stream_format(stream, "XIS 1");
			break;

		case 0x15:
			util::stream_format(stream, "LD 1");
			break;

		case 0x16:
			util::stream_format(stream, "X 1");
			break;

		case 0x17:
			util::stream_format(stream, "XDS 1");
			break;

		case 0x20:
			util::stream_format(stream, "SKC");
			break;

		case 0x21:
			util::stream_format(stream, "SKE");
			break;

		case 0x22:
			util::stream_format(stream, "SC");
>>>>>>> upstream/master
			break;

		case 0x23:
			bytes = 2;

			if (next_opcode >= 0x80 && next_opcode <= 0xbf)
			{
<<<<<<< HEAD
				address = (UINT16)(next_opcode & 0x3F);
				sprintf(buffer, "XAD %x,%x", ((address & 0x30) >> 4),address & 0x0F);
			}
			else
			{
				sprintf(buffer, "Invalid");
=======
				address = (uint16_t)(next_opcode & 0x3F);
				util::stream_format(stream, "XAD %u,%u", ((address & 0x30) >> 4),address & 0x0F);
			}
			else
			{
				util::stream_format(stream, "Invalid");
>>>>>>> upstream/master
			}
			break;

		case 0x24:
<<<<<<< HEAD
			sprintf(buffer, "XIS 2");
			break;

		case 0x25:
			sprintf(buffer, "LD 2");
			break;

		case 0x26:
			sprintf(buffer, "X 2");
			break;

		case 0x27:
			sprintf(buffer, "XDS 2");
			break;

		case 0x30:
			sprintf(buffer, "ASC");
			break;

		case 0x31:
			sprintf(buffer, "ADD");
			break;

		case 0x32:
			sprintf(buffer, "RC");
=======
			util::stream_format(stream, "XIS 2");
			break;

		case 0x25:
			util::stream_format(stream, "LD 2");
			break;

		case 0x26:
			util::stream_format(stream, "X 2");
			break;

		case 0x27:
			util::stream_format(stream, "XDS 2");
			break;

		case 0x30:
			util::stream_format(stream, "ASC");
			break;

		case 0x31:
			util::stream_format(stream, "ADD");
			break;

		case 0x32:
			util::stream_format(stream, "RC");
>>>>>>> upstream/master
			break;

		case 0x33:
			bytes = 2;

			if (next_opcode >= 0x60 && next_opcode <= 0x6F)
			{
<<<<<<< HEAD
				sprintf(buffer, "LEI %x", next_opcode & 0xF);
=======
				util::stream_format(stream, "LEI %x", next_opcode & 0xF);
>>>>>>> upstream/master
			}
			else
			{
				switch (next_opcode)
				{
				case 0x01:
<<<<<<< HEAD
					sprintf(buffer, "SKGBZ 0");
					break;

				case 0x03:
					sprintf(buffer, "SKGBZ 2");
					break;

				case 0x11:
					sprintf(buffer, "SKGBZ 1");
					break;

				case 0x13:
					sprintf(buffer, "SKGBZ 3");
					break;

				case 0x21:
					sprintf(buffer, "SKGZ");
					break;

				case 0x2A:
					sprintf(buffer, "ING");
					break;

				case 0x2E:
					sprintf(buffer, "INL");
					break;

				case 0x38:
					sprintf(buffer, "HALT");
					break;

				case 0x3A:
					sprintf(buffer, "OMG");
					break;

				case 0x3C:
					sprintf(buffer, "CAMQ");
					break;

				case 0x3E:
					sprintf(buffer, "OBD");
					break;

				default:
					sprintf(buffer, "Invalid");
=======
					util::stream_format(stream, "SKGBZ 0");
					break;

				case 0x03:
					util::stream_format(stream, "SKGBZ 2");
					break;

				case 0x11:
					util::stream_format(stream, "SKGBZ 1");
					break;

				case 0x13:
					util::stream_format(stream, "SKGBZ 3");
					break;

				case 0x21:
					util::stream_format(stream, "SKGZ");
					break;

				case 0x2A:
					util::stream_format(stream, "ING");
					break;

				case 0x2E:
					util::stream_format(stream, "INL");
					break;

				case 0x38:
					util::stream_format(stream, "HALT");
					break;

				case 0x3A:
					util::stream_format(stream, "OMG");
					break;

				case 0x3C:
					util::stream_format(stream, "CAMQ");
					break;

				case 0x3E:
					util::stream_format(stream, "OBD");
					break;

				default:
					util::stream_format(stream, "Invalid");
>>>>>>> upstream/master
					break;
				}
				break;
			}
<<<<<<< HEAD

		case 0x34:
			sprintf(buffer, "XIS 3");
			break;

		case 0x35:
			sprintf(buffer, "LD 3");
			break;

		case 0x36:
			sprintf(buffer, "X 3");
			break;

		case 0x37:
			sprintf(buffer, "XDS 3");
			break;

		case 0x40:
			sprintf(buffer, "COMP");
			break;

		case 0x42:
			sprintf(buffer, "RMB 2");
			break;

		case 0x43:
			sprintf(buffer, "RMB 3");
			break;

		case 0x44:
			sprintf(buffer, "NOP");
			break;

		case 0x45:
			sprintf(buffer, "RMB 1");
			break;

		case 0x46:
			sprintf(buffer, "SMB 2");
			break;

		case 0x47:
			sprintf(buffer, "SMB 1");
			break;

		case 0x48:
			sprintf(buffer, "RET");
=======
			break;

		case 0x34:
			util::stream_format(stream, "XIS 3");
			break;

		case 0x35:
			util::stream_format(stream, "LD 3");
			break;

		case 0x36:
			util::stream_format(stream, "X 3");
			break;

		case 0x37:
			util::stream_format(stream, "XDS 3");
			break;

		case 0x40:
			util::stream_format(stream, "COMP");
			break;

		case 0x42:
			util::stream_format(stream, "RMB 2");
			break;

		case 0x43:
			util::stream_format(stream, "RMB 3");
			break;

		case 0x44:
			util::stream_format(stream, "NOP");
			break;

		case 0x45:
			util::stream_format(stream, "RMB 1");
			break;

		case 0x46:
			util::stream_format(stream, "SMB 2");
			break;

		case 0x47:
			util::stream_format(stream, "SMB 1");
			break;

		case 0x48:
			util::stream_format(stream, "RET");
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OUT;
			break;

		case 0x49:
<<<<<<< HEAD
			sprintf(buffer, "RETSK");
=======
			util::stream_format(stream, "RETSK");
>>>>>>> upstream/master
			flags = DASMFLAG_STEP_OUT;
			break;

		case 0x4B:
<<<<<<< HEAD
			sprintf(buffer, "SMB 3");
			break;

		case 0x4C:
			sprintf(buffer, "RMB 0");
			break;

		case 0x4D:
			sprintf(buffer, "SMB 0");
			break;

		case 0x4E:
			sprintf(buffer, "CBA");
			break;

		case 0x4F:
			sprintf(buffer, "XAS");
			break;

		case 0x50:
			sprintf(buffer, "CAB");
			break;

		case 0xBF:
			sprintf(buffer, "LQID");
			break;

		case 0xFF:
			sprintf(buffer, "JID");
			break;

		default:
			sprintf(buffer, "Invalid");
=======
			util::stream_format(stream, "SMB 3");
			break;

		case 0x4C:
			util::stream_format(stream, "RMB 0");
			break;

		case 0x4D:
			util::stream_format(stream, "SMB 0");
			break;

		case 0x4E:
			util::stream_format(stream, "CBA");
			break;

		case 0x4F:
			util::stream_format(stream, "XAS");
			break;

		case 0x50:
			util::stream_format(stream, "CAB");
			break;

		case 0xBF:
			util::stream_format(stream, "LQID");
			break;

		case 0xFF:
			util::stream_format(stream, "JID");
			break;

		default:
			util::stream_format(stream, "Invalid");
>>>>>>> upstream/master
			break;
		}
	}

	return bytes | flags | DASMFLAG_SUPPORTED;
}
