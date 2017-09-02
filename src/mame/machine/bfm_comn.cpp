// license:BSD-3-Clause
// copyright-holders:David Haywood
/* Bellfruit Common Hardware / Functions */
#include "emu.h"


<<<<<<< HEAD
static const UINT16 AddressDecode[]=
=======
static const uint16_t AddressDecode[]=
>>>>>>> upstream/master
{
	0x0800,0x1000,0x0001,0x0004,0x0008,0x0020,0x0080,0x0200,
	0x0100,0x0040,0x0002,0x0010,0x0400,0x2000,0x4000,0x8000,
	0
};

<<<<<<< HEAD
static const UINT8 DataDecode[]=
=======
static const uint8_t DataDecode[]=
>>>>>>> upstream/master
{
	0x02,0x08,0x20,0x40,0x10,0x04,0x01,0x80,
	0
};


///////////////////////////////////////////////////////////////////////////
<<<<<<< HEAD
void bfm_decode_mainrom(running_machine &machine, const char *rom_region, UINT8* codec_data)
{
	UINT8 *rom;
=======
void bfm_decode_mainrom(running_machine &machine, const char *rom_region, uint8_t* codec_data)
{
	uint8_t *rom;
>>>>>>> upstream/master

	rom = machine.root_device().memregion(rom_region)->base();

	{
<<<<<<< HEAD
		dynamic_buffer tmp(0x10000);
=======
		std::vector<uint8_t> tmp(0x10000);
>>>>>>> upstream/master
		int i;

		memcpy(&tmp[0], rom, 0x10000);

		for ( i = 0; i < 256; i++ )
		{
<<<<<<< HEAD
			UINT8 data,pattern,newdata,*tab;
			data    = i;

			tab     = (UINT8*)DataDecode;
=======
			uint8_t data,pattern,newdata,*tab;
			data    = i;

			tab     = (uint8_t*)DataDecode;
>>>>>>> upstream/master
			pattern = 0x01;
			newdata = 0;

			do
			{
				newdata |= data & pattern ? *tab : 0;
				pattern <<= 1;
			} while ( *(++tab) );

			codec_data[i] = newdata;
		}

		for ( int address = 0; address < 0x10000; address++)
		{
			int newaddress,pattern;
<<<<<<< HEAD
			UINT16 *tab;

			tab      = (UINT16*)AddressDecode;
=======
			uint16_t *tab;

			tab      = (uint16_t*)AddressDecode;
>>>>>>> upstream/master
			pattern  = 0x0001;
			newaddress = 0;
			do
			{
				newaddress |= address & pattern ? *tab : 0;
				pattern <<= 1;
			} while ( *(++tab) );

			rom[newaddress] = codec_data[ tmp[address] ];
		}
	}
}
