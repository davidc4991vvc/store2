// license:BSD-3-Clause
// copyright-holders:Luca Elia, David Haywood, Angelo Salese, Roberto Fresca
/***************************************************************************

Subsino XOR + Bitswap Encryption
by David Haywood

***************************************************************************/

#include "emu.h"

// XORs:

<<<<<<< HEAD
extern const UINT8 crsbingo_xors[8] = { 0xbb, 0xcc, 0xcc, 0xdd, 0xaa, 0x11, 0x44, 0xee };
extern const UINT8 sharkpy_xors [8] = { 0xcc, 0xaa, 0x66, 0xaa, 0xee, 0x33, 0xff, 0xff };
extern const UINT8 victor5_xors [8] = { 0x99, 0x99, 0x33, 0x44, 0xbb, 0x88, 0x88, 0xbb };
extern const UINT8 victor21_xors[8] = { 0x44, 0xbb, 0x66, 0x44, 0xaa, 0x55, 0x88, 0x22 };

// Bitswaps:

void crsbingo_bitswaps(UINT8 *decrypt, int i)
=======
extern const uint8_t crsbingo_xors[8] = { 0xbb, 0xcc, 0xcc, 0xdd, 0xaa, 0x11, 0x44, 0xee };
extern const uint8_t sharkpy_xors [8] = { 0xcc, 0xaa, 0x66, 0xaa, 0xee, 0x33, 0xff, 0xff };
extern const uint8_t victor5_xors [8] = { 0x99, 0x99, 0x33, 0x44, 0xbb, 0x88, 0x88, 0xbb };
extern const uint8_t victor21_xors[8] = { 0x44, 0xbb, 0x66, 0x44, 0xaa, 0x55, 0x88, 0x22 };

// Bitswaps:

void crsbingo_bitswaps(uint8_t *decrypt, int i)
>>>>>>> upstream/master
{
	if ((i&7) == 0) decrypt[i] = BITSWAP8(decrypt[i], 7,2,5,4,3,6,1,0 );
	if ((i&7) == 1) decrypt[i] = BITSWAP8(decrypt[i], 7,2,1,0,3,6,5,4 );
	if ((i&7) == 2) decrypt[i] = BITSWAP8(decrypt[i], 3,2,5,0,7,6,1,4 );
	if ((i&7) == 3) decrypt[i] = BITSWAP8(decrypt[i], 7,2,5,0,3,6,1,4 );
	if ((i&7) == 4) decrypt[i] = BITSWAP8(decrypt[i], 7,6,5,0,3,2,1,4 );
	if ((i&7) == 5) decrypt[i] = BITSWAP8(decrypt[i], 7,2,1,4,3,6,5,0 );
	if ((i&7) == 6) decrypt[i] = BITSWAP8(decrypt[i], 7,2,1,0,3,6,5,4 );
	if ((i&7) == 7) decrypt[i] = BITSWAP8(decrypt[i], 3,2,1,0,7,6,5,4 );
}

<<<<<<< HEAD
void sharkpy_bitswaps(UINT8 *decrypt, int i)
=======
void sharkpy_bitswaps(uint8_t *decrypt, int i)
>>>>>>> upstream/master
{
	if ((i&7) == 0) decrypt[i] = BITSWAP8(decrypt[i], 3,2,1,0,7,6,5,4 );
	if ((i&7) == 1) decrypt[i] = BITSWAP8(decrypt[i], 7,2,5,4,3,6,1,0 );
	if ((i&7) == 2) decrypt[i] = BITSWAP8(decrypt[i], 7,2,1,4,3,6,5,0 );
	if ((i&7) == 3) decrypt[i] = BITSWAP8(decrypt[i], 3,6,1,0,7,2,5,4 );
	if ((i&7) == 4) decrypt[i] = BITSWAP8(decrypt[i], 7,2,5,4,3,6,1,0 );
	if ((i&7) == 5) decrypt[i] = BITSWAP8(decrypt[i], 3,2,5,4,7,6,1,0 );
	if ((i&7) == 6) decrypt[i] = BITSWAP8(decrypt[i], 7,6,1,4,3,2,5,0 );
	if ((i&7) == 7) decrypt[i] = BITSWAP8(decrypt[i], 3,6,1,4,7,2,5,0 );
}

<<<<<<< HEAD
void victor5_bitswaps(UINT8 *decrypt, int i)
=======
void victor5_bitswaps(uint8_t *decrypt, int i)
>>>>>>> upstream/master
{
	if ((i&7) == 0) decrypt[i] = BITSWAP8(decrypt[i], 7,2,5,4,3,6,1,0 );
	if ((i&7) == 1) decrypt[i] = BITSWAP8(decrypt[i], 7,6,5,0,3,2,1,4 );
	if ((i&7) == 2) decrypt[i] = BITSWAP8(decrypt[i], 7,2,1,0,3,6,5,4 );
	if ((i&7) == 3) decrypt[i] = BITSWAP8(decrypt[i], 7,2,1,0,3,6,5,4 );
	if ((i&7) == 4) decrypt[i] = BITSWAP8(decrypt[i], 3,2,1,0,7,6,5,4 );
	if ((i&7) == 5) decrypt[i] = BITSWAP8(decrypt[i], 7,6,5,0,3,2,1,4 );
	if ((i&7) == 6) decrypt[i] = BITSWAP8(decrypt[i], 3,6,1,0,7,2,5,4 );
	if ((i&7) == 7) decrypt[i] = BITSWAP8(decrypt[i], 7,2,1,4,3,6,5,0 );
}

<<<<<<< HEAD
void victor21_bitswaps(UINT8 *decrypt, int i)
=======
void victor21_bitswaps(uint8_t *decrypt, int i)
>>>>>>> upstream/master
{
	if ((i&7) == 0) decrypt[i] = BITSWAP8(decrypt[i], 7,2,1,0,3,6,5,4 );
	if ((i&7) == 1) decrypt[i] = BITSWAP8(decrypt[i], 3,6,1,4,7,2,5,0 );
	if ((i&7) == 2) decrypt[i] = BITSWAP8(decrypt[i], 3,2,1,4,7,6,5,0 );
	if ((i&7) == 3) decrypt[i] = BITSWAP8(decrypt[i], 7,2,5,4,3,6,1,0 );
	if ((i&7) == 4) decrypt[i] = BITSWAP8(decrypt[i], 7,2,5,4,3,6,1,0 );
	if ((i&7) == 5) decrypt[i] = BITSWAP8(decrypt[i], 3,6,5,0,7,2,1,4 );
	if ((i&7) == 6) decrypt[i] = BITSWAP8(decrypt[i], 7,6,5,4,3,2,1,0 );
	if ((i&7) == 7) decrypt[i] = BITSWAP8(decrypt[i], 3,2,1,4,7,6,5,0 );
}

// Decrypt:

#if 0
<<<<<<< HEAD
void dump_decrypted(running_machine& machine, UINT8* decrypt)
=======
void dump_decrypted(running_machine& machine, uint8_t* decrypt)
>>>>>>> upstream/master
{
	FILE *fp;
	char filename[256];
	sprintf(filename,"dat_%s", machine.system().name);
	fp=fopen(filename, "w+b");
	if (fp)
	{
		fwrite(decrypt, 0x10000, 1, fp);
		fclose(fp);
	}
}
#endif

<<<<<<< HEAD
void subsino_decrypt(running_machine& machine, void (*bitswaps)(UINT8 *decrypt, int i), const UINT8 *xors, int size)
{
	int i;
	UINT8 *decrypt = auto_alloc_array(machine, UINT8, 0x10000);
	UINT8* region = machine.root_device().memregion("maincpu")->base();
=======
void subsino_decrypt(running_machine& machine, void (*bitswaps)(uint8_t *decrypt, int i), const uint8_t *xors, int size)
{
	int i;
	std::unique_ptr<uint8_t[]> decrypt = std::make_unique<uint8_t[]>(0x10000);
	uint8_t* region = machine.root_device().memregion("maincpu")->base();
>>>>>>> upstream/master

	for (i=0;i<0x10000;i++)
	{
		if (i<size)
		{
			decrypt[i] = region[i]^xors[i&7];
<<<<<<< HEAD
			bitswaps(decrypt, i);
=======
			bitswaps(decrypt.get(), i);
>>>>>>> upstream/master
		}
		else
		{
			decrypt[i] = region[i];
		}
	}
//  dump_decrypted(machine, decrypt);
<<<<<<< HEAD
	memcpy(region, decrypt, 0x10000);
=======
	memcpy(region, decrypt.get(), 0x10000);
>>>>>>> upstream/master
}
