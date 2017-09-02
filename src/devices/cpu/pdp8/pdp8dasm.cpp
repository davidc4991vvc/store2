// license:BSD-3-Clause
// copyright-holders:Ryan Holtz
/*
    First-gen DEC PDP-8 disassembler

    Written by Ryan Holtz
*/

#include "emu.h"

<<<<<<< HEAD
static char *output;

offs_t pdp8_dasm_one(char *buffer, offs_t pc, UINT16 op)
{
	UINT8 opcode = (op >> 011) & 07;
	UINT16 current_page = pc & 07600;
	UINT16 zero_addr = op & 0177;
	UINT16 current_addr = current_page | zero_addr;
	bool indirect = (op & 0400) ? true : false;
	bool zero_page = (op & 0200) ? false : true;

	output = buffer;

	switch (opcode)
	{
		case 0:
			output += sprintf(buffer, "AND %c %05o", indirect ? 'I' : ' ', zero_page ? zero_addr : current_addr);
			break;
		case 1:
			output += sprintf(buffer, "TAD %c %05o", indirect ? 'I' : ' ', zero_page ? zero_addr : current_addr);
			break;
		case 2:
			output += sprintf(buffer, "ISZ %c %05o", indirect ? 'I' : ' ', zero_page ? zero_addr : current_addr);
			break;
		case 3:
			output += sprintf(buffer, "DCA %c %05o", indirect ? 'I' : ' ', zero_page ? zero_addr : current_addr);
			break;
		case 4:
			output += sprintf(buffer, "JMS %c %05o", indirect ? 'I' : ' ', zero_page ? zero_addr : current_addr);
			break;
		case 5:
			output += sprintf(buffer, "JMP %c %05o", indirect ? 'I' : ' ', zero_page ? zero_addr : current_addr);
			break;
		case 6:
			output += sprintf(buffer, "IOT %03o %01o", (op >> 03) & 077, op & 07);
=======
static offs_t pdp8_dasm_one(std::ostream &stream, offs_t pc, uint16_t op)
{
	uint8_t opcode = (op >> 011) & 07;
	uint16_t current_page = pc & 07600;
	uint16_t zero_addr = op & 0177;
	uint16_t current_addr = current_page | zero_addr;
	bool indirect = (op & 0400) ? true : false;
	bool zero_page = (op & 0200) ? false : true;

	switch (opcode)
	{
		case 0:
			util::stream_format(stream, "AND %c %05o", indirect ? 'I' : ' ', zero_page ? zero_addr : current_addr);
			break;
		case 1:
			util::stream_format(stream, "TAD %c %05o", indirect ? 'I' : ' ', zero_page ? zero_addr : current_addr);
			break;
		case 2:
			util::stream_format(stream, "ISZ %c %05o", indirect ? 'I' : ' ', zero_page ? zero_addr : current_addr);
			break;
		case 3:
			util::stream_format(stream, "DCA %c %05o", indirect ? 'I' : ' ', zero_page ? zero_addr : current_addr);
			break;
		case 4:
			util::stream_format(stream, "JMS %c %05o", indirect ? 'I' : ' ', zero_page ? zero_addr : current_addr);
			break;
		case 5:
			util::stream_format(stream, "JMP %c %05o", indirect ? 'I' : ' ', zero_page ? zero_addr : current_addr);
			break;
		case 6:
			util::stream_format(stream, "IOT %03o %01o", (op >> 03) & 077, op & 07);
>>>>>>> upstream/master
			break;
		case 7:
		{
			bool group2 = ((op & 0401) == 0400);
			if (!group2)
			{
				if (!(op & 0377))
				{
<<<<<<< HEAD
					output += sprintf(buffer, "NOP ");
=======
					util::stream_format(stream, "NOP ");
>>>>>>> upstream/master
				}
				else
				{
					if (op & 0200)
					{
<<<<<<< HEAD
						output += sprintf(buffer, "CLA ");
					}
					if (op & 0100)
					{
						output += sprintf(buffer, "CLL ");
					}
					if (op & 040)
					{
						output += sprintf(buffer, "CMA ");
					}
					if (op & 020)
					{
						output += sprintf(buffer, "CML ");
					}
					if (op & 01)
					{
						output += sprintf(buffer, "IAC ");
=======
						util::stream_format(stream, "CLA ");
					}
					if (op & 0100)
					{
						util::stream_format(stream, "CLL ");
					}
					if (op & 040)
					{
						util::stream_format(stream, "CMA ");
					}
					if (op & 020)
					{
						util::stream_format(stream, "CML ");
					}
					if (op & 01)
					{
						util::stream_format(stream, "IAC ");
>>>>>>> upstream/master
					}
					if (op & 010)
					{
						if (op & 02)
						{
<<<<<<< HEAD
							output += sprintf(buffer, "RTR ");
						}
						else
						{
							output += sprintf(buffer, "RAR ");
=======
							util::stream_format(stream, "RTR ");
						}
						else
						{
							util::stream_format(stream, "RAR ");
>>>>>>> upstream/master
						}
					}
					if (op & 04)
					{
						if (op & 02)
						{
<<<<<<< HEAD
							output += sprintf(buffer, "RTL ");
						}
						else
						{
							output += sprintf(buffer, "RAL ");
=======
							util::stream_format(stream, "RTL ");
						}
						else
						{
							util::stream_format(stream, "RAL ");
>>>>>>> upstream/master
						}
					}
				}
			}
			else
			{
				if (!(op & 0377))
				{
<<<<<<< HEAD
					output += sprintf(buffer, "NOP ");
=======
					util::stream_format(stream, "NOP ");
>>>>>>> upstream/master
				}
				else
				{
					if (op & 010)
					{
						if (!(op & 0160))
						{
<<<<<<< HEAD
							output += sprintf(buffer, "SKP ");
=======
							util::stream_format(stream, "SKP ");
>>>>>>> upstream/master
						}
						else
						{
							if (op & 0100)
							{
<<<<<<< HEAD
								output += sprintf(buffer, "SPA ");
							}
							if (op & 040)
							{
								output += sprintf(buffer, "SNA ");
							}
							if (op & 020)
							{
								output += sprintf(buffer, "SZL ");
=======
								util::stream_format(stream, "SPA ");
							}
							if (op & 040)
							{
								util::stream_format(stream, "SNA ");
							}
							if (op & 020)
							{
								util::stream_format(stream, "SZL ");
>>>>>>> upstream/master
							}
						}
					}
					else
					{
						if (op & 0100)
						{
<<<<<<< HEAD
							output += sprintf(buffer, "SMA ");
						}
						if (op & 040)
						{
							output += sprintf(buffer, "SZA ");
						}
						if (op & 020)
						{
							output += sprintf(buffer, "SNL ");
=======
							util::stream_format(stream, "SMA ");
						}
						if (op & 040)
						{
							util::stream_format(stream, "SZA ");
						}
						if (op & 020)
						{
							util::stream_format(stream, "SNL ");
>>>>>>> upstream/master
						}
					}
					if (op & 0200)
					{
<<<<<<< HEAD
						output += sprintf(buffer, "CLA ");
					}
					if (op & 04)
					{
						output += sprintf(buffer, "OSR ");
					}
					if (op & 02)
					{
						output += sprintf(buffer, "HLT ");
=======
						util::stream_format(stream, "CLA ");
					}
					if (op & 04)
					{
						util::stream_format(stream, "OSR ");
					}
					if (op & 02)
					{
						util::stream_format(stream, "HLT ");
>>>>>>> upstream/master
					}
				}
			}
		}
	}

	return 2 | DASMFLAG_SUPPORTED;
}

<<<<<<< HEAD
=======

>>>>>>> upstream/master
/*****************************************************************************/

CPU_DISASSEMBLE( pdp8 )
{
<<<<<<< HEAD
	UINT16 op = (*(UINT8 *)(opram + 0) << 8) |
				(*(UINT8 *)(opram + 1) << 0);
	return pdp8_dasm_one(buffer, pc, op);
=======
	uint16_t op = (*(uint8_t *)(opram + 0) << 8) |
				(*(uint8_t *)(opram + 1) << 0);
	return pdp8_dasm_one(stream, pc, op);
>>>>>>> upstream/master
}
