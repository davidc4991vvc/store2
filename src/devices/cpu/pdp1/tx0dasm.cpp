// license:BSD-3-Clause
// copyright-holders:Raphael Nabet
#include "emu.h"
#include "cpu/pdp1/tx0.h"

<<<<<<< HEAD
CPU_DISASSEMBLE( tx0_64kw )
=======
CPU_DISASSEMBLE(tx0_64kw)
>>>>>>> upstream/master
{
	int md;
	int x;

	md = oprom[0] << 24 | oprom[1] << 16 | oprom[2] << 8 | oprom[3];

	x = md & 0177777;
	switch (md >> 16)
	{
	case 0:
<<<<<<< HEAD
		sprintf (buffer, "sto 0%06o", x);
		break;
	case 1:
		sprintf (buffer, "add 0%06o", x);
		break;
	case 2:
		sprintf (buffer, "trn 0%06o", x);
		break;
	case 3:
		sprintf (buffer, "opr 0%06o", x);
=======
		util::stream_format(stream, "sto 0%06o", x);
		break;
	case 1:
		util::stream_format(stream, "add 0%06o", x);
		break;
	case 2:
		util::stream_format(stream, "trn 0%06o", x);
		break;
	case 3:
		util::stream_format(stream, "opr 0%06o", x);
>>>>>>> upstream/master
		break;
	}
	return 1;
}

<<<<<<< HEAD
CPU_DISASSEMBLE( tx0_8kw )
=======
CPU_DISASSEMBLE(tx0_8kw)
>>>>>>> upstream/master
{
	int md;
	int x;

	md = oprom[0] << 24 | oprom[1] << 16 | oprom[2] << 8 | oprom[3];

	x = md & 0017777;
	switch (md >> 13)
	{
	case 0:
<<<<<<< HEAD
		sprintf (buffer, "sto 0%05o", x);
		break;
	case 1:
		sprintf (buffer, "stx 0%05o", x);
		break;
	case 2:
		sprintf (buffer, "sxa 0%05o", x);
		break;
	case 3:
		sprintf (buffer, "ado 0%05o", x);
		break;
	case 4:
		sprintf (buffer, "slr 0%05o", x);
		break;
	case 5:
		sprintf (buffer, "slx 0%05o", x);
		break;
	case 6:
		sprintf (buffer, "stz 0%05o", x);
		break;
	case 8:
		sprintf (buffer, "add 0%05o", x);
		break;
	case 9:
		sprintf (buffer, "adx 0%05o", x);
		break;
	case 10:
		sprintf (buffer, "ldx 0%05o", x);
		break;
	case 11:
		sprintf (buffer, "aux 0%05o", x);
		break;
	case 12:
		sprintf (buffer, "llr 0%05o", x);
		break;
	case 13:
		sprintf (buffer, "llx 0%05o", x);
		break;
	case 14:
		sprintf (buffer, "lda 0%05o", x);
		break;
	case 15:
		sprintf (buffer, "lax 0%05o", x);
		break;
	case 16:
		sprintf (buffer, "trn 0%05o", x);
		break;
	case 17:
		sprintf (buffer, "tze 0%05o", x);
		break;
	case 18:
		sprintf (buffer, "tsx 0%05o", x);
		break;
	case 19:
		sprintf (buffer, "tix 0%05o", x);
		break;
	case 20:
		sprintf (buffer, "tra 0%05o", x);
		break;
	case 21:
		sprintf (buffer, "trx 0%05o", x);
		break;
	case 22:
		sprintf (buffer, "tlv 0%05o", x);
=======
		util::stream_format(stream, "sto 0%05o", x);
		break;
	case 1:
		util::stream_format(stream, "stx 0%05o", x);
		break;
	case 2:
		util::stream_format(stream, "sxa 0%05o", x);
		break;
	case 3:
		util::stream_format(stream, "ado 0%05o", x);
		break;
	case 4:
		util::stream_format(stream, "slr 0%05o", x);
		break;
	case 5:
		util::stream_format(stream, "slx 0%05o", x);
		break;
	case 6:
		util::stream_format(stream, "stz 0%05o", x);
		break;
	case 8:
		util::stream_format(stream, "add 0%05o", x);
		break;
	case 9:
		util::stream_format(stream, "adx 0%05o", x);
		break;
	case 10:
		util::stream_format(stream, "ldx 0%05o", x);
		break;
	case 11:
		util::stream_format(stream, "aux 0%05o", x);
		break;
	case 12:
		util::stream_format(stream, "llr 0%05o", x);
		break;
	case 13:
		util::stream_format(stream, "llx 0%05o", x);
		break;
	case 14:
		util::stream_format(stream, "lda 0%05o", x);
		break;
	case 15:
		util::stream_format(stream, "lax 0%05o", x);
		break;
	case 16:
		util::stream_format(stream, "trn 0%05o", x);
		break;
	case 17:
		util::stream_format(stream, "tze 0%05o", x);
		break;
	case 18:
		util::stream_format(stream, "tsx 0%05o", x);
		break;
	case 19:
		util::stream_format(stream, "tix 0%05o", x);
		break;
	case 20:
		util::stream_format(stream, "tra 0%05o", x);
		break;
	case 21:
		util::stream_format(stream, "trx 0%05o", x);
		break;
	case 22:
		util::stream_format(stream, "tlv 0%05o", x);
>>>>>>> upstream/master
		break;
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
<<<<<<< HEAD
		sprintf (buffer, "opr 0%06o", md & 0177777);
		break;
	default:
		sprintf (buffer, "illegal");
=======
		util::stream_format(stream, "opr 0%06o", md & 0177777);
		break;
	default:
		util::stream_format(stream, "illegal");
>>>>>>> upstream/master
		break;
	}
	return 1;
}
