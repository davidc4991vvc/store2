// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
/*********************************************************************

    ace_tap.h

    Format code for Jupiter Ace cassette files

*********************************************************************/

#ifndef ACE_TAP_H
#define ACE_TAP_H

#include "cassimg.h"

#if 0
struct ace_tape_t
{
<<<<<<< HEAD
	UINT8 hdr_type;
	UINT8 hdr_name[10];
	UINT16 hdr_len;
	UINT16 hdr_addr;
	UINT8 hdr_vars[8];
	UINT8 hdr_3c4c;
	UINT8 hdr_3c4d;
	UINT16 dat_len;
=======
	uint8_t hdr_type;
	uint8_t hdr_name[10];
	uint16_t hdr_len;
	uint16_t hdr_addr;
	uint8_t hdr_vars[8];
	uint8_t hdr_3c4c;
	uint8_t hdr_3c4d;
	uint16_t dat_len;
>>>>>>> upstream/master
};
#endif

CASSETTE_FORMATLIST_EXTERN(ace_cassette_formats);

#endif /* ACE_TAP_H */
