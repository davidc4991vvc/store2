// license:BSD-3-Clause
// copyright-holders:Raphael Nabet
#include "emu.h"
#include "cpu/pdp1/pdp1.h"

/* PDP1 registers */
static int ib;
static int y;

<<<<<<< HEAD
INLINE void ea (void)
=======
static inline void ea (void)
>>>>>>> upstream/master
{
/*  while (1)
    {
        if (ib == 0)
            return;
        ib = (READ_PDP_18BIT (y) >> 12) & 1;
        y = READ_PDP_18BIT (y) & 07777;
    }*/
}

<<<<<<< HEAD
#define IN if (ib) sprintf(buffer+strlen(buffer)," i")

CPU_DISASSEMBLE( pdp1 )
=======
#define IN if (ib) util::stream_format(stream, " i")

CPU_DISASSEMBLE(pdp1)
>>>>>>> upstream/master
{
	int md;
	//int etime = 0;

	md = oprom[0] << 24 | oprom[1] << 16 | oprom[2] << 8 | oprom[3];

	y = md & 07777;
	ib = (md >> 12) & 1;               /* */
	switch (md >> 13)
	{
<<<<<<< HEAD
	case AND:
		ea ();
		sprintf (buffer, "AND (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case IOR:
		ea ();
		sprintf (buffer, "IOR (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case XOR:
		ea ();
		sprintf (buffer, "XOR (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case XCT:
		ea ();
		sprintf (buffer, "XCT (0%06o)", y);
		IN;
		//etime = 5;
		break;
	case CALJDA:
		{
			if (ib == 1)
				sprintf (buffer, "JDA 0%06o  ", y);
			if (ib == 0)
				sprintf (buffer, "CAL         ");
			//etime = 10;
			break;
		}
	case LAC:
		ea ();
		sprintf (buffer, "LAC (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case LIO:
		ea ();
		sprintf (buffer, "LIO (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case DAC:
		ea ();
		sprintf (buffer, "DAC 0%06o  ", y);
		IN;
		//etime = 10;
		break;
	case DAP:
		ea ();
		sprintf (buffer, "DAP 0%06o  ", y);
		IN;
		//etime = 10;
		break;
	case DIP:
		ea ();
		sprintf (buffer, "DIP 0%06o  ", y);
		IN;
		//etime = 10;
		break;
	case DIO:
		ea ();
		sprintf (buffer, "DIO 0%06o  ", y);
		IN;
		//etime = 10;
		break;
	case DZM:
		ea ();
		sprintf (buffer, "DZM 0%06o  ", y);
		IN;
		//etime = 10;
		break;
	case ADD:
		ea ();
		sprintf (buffer, "ADD (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case SUB:
		ea ();
		sprintf (buffer, "SUB (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case IDX:
		ea ();
		sprintf (buffer, "IDX (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case ISP:
		ea ();
		sprintf (buffer, "ISP (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case SAD:
		ea ();
		sprintf (buffer, "SAD (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case SAS:
		ea ();
		sprintf (buffer, "SAS (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case MUS_MUL:
		ea ();
		sprintf (buffer, "MUS (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case DIS_DIV:
		ea ();
		sprintf (buffer, "DIS (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case JMP:
		ea ();
		sprintf (buffer, "JMP 0%06o  ", y);
		IN;
		//etime = 5;
		break;
	case JSP:
		ea ();
		sprintf (buffer, "JSP 0%06o  ", y);
		IN;
		//etime = 5;
		break;
	case SKP:
		{
			buffer[0] = 0;
			if ((y & 0100) == 0100)
				sprintf (buffer, "SZA ");
			if ((y & 0200) == 0200)
				sprintf (buffer + strlen (buffer), "SPA ");
			if ((y & 0400) == 0400)
				sprintf (buffer + strlen (buffer), "SMA ");
			if ((y & 01000) == 01000)
				sprintf (buffer + strlen (buffer), "SZO ");
			if ((y & 02000) == 02000)
				sprintf (buffer + strlen (buffer), "SPI ");
			if (y & 070)
				sprintf (buffer + strlen (buffer), "SZS 0%01o ", (y & 070));
			if (y & 7)
				sprintf (buffer + strlen (buffer), "SZF 0%01o ", (y & 7));
=======
	case pdp1_device::AND:
		ea ();
		util::stream_format(stream, "AND (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::IOR:
		ea ();
		util::stream_format(stream, "IOR (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::XOR:
		ea ();
		util::stream_format(stream, "XOR (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::XCT:
		ea ();
		util::stream_format(stream, "XCT (0%06o)", y);
		IN;
		//etime = 5;
		break;
	case pdp1_device::CALJDA:
		{
			if (ib == 1)
				util::stream_format(stream, "JDA 0%06o  ", y);
			if (ib == 0)
				util::stream_format(stream, "CAL         ");
			//etime = 10;
			break;
		}
	case pdp1_device::LAC:
		ea ();
		util::stream_format(stream, "LAC (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::LIO:
		ea ();
		util::stream_format(stream, "LIO (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::DAC:
		ea ();
		util::stream_format(stream, "DAC 0%06o  ", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::DAP:
		ea ();
		util::stream_format(stream, "DAP 0%06o  ", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::DIP:
		ea ();
		util::stream_format(stream, "DIP 0%06o  ", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::DIO:
		ea ();
		util::stream_format(stream, "DIO 0%06o  ", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::DZM:
		ea ();
		util::stream_format(stream, "DZM 0%06o  ", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::ADD:
		ea ();
		util::stream_format(stream, "ADD (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::SUB:
		ea ();
		util::stream_format(stream, "SUB (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::IDX:
		ea ();
		util::stream_format(stream, "IDX (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::ISP:
		ea ();
		util::stream_format(stream, "ISP (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::SAD:
		ea ();
		util::stream_format(stream, "SAD (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::SAS:
		ea ();
		util::stream_format(stream, "SAS (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::MUS_MUL:
		ea ();
		util::stream_format(stream, "MUS (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::DIS_DIV:
		ea ();
		util::stream_format(stream, "DIS (0%06o)", y);
		IN;
		//etime = 10;
		break;
	case pdp1_device::JMP:
		ea ();
		util::stream_format(stream, "JMP 0%06o  ", y);
		IN;
		//etime = 5;
		break;
	case pdp1_device::JSP:
		ea ();
		util::stream_format(stream, "JSP 0%06o  ", y);
		IN;
		//etime = 5;
		break;
	case pdp1_device::SKP:
		{
			if ((y & 0100) == 0100)
				util::stream_format(stream, "SZA ");
			if ((y & 0200) == 0200)
				util::stream_format(stream, "SPA ");
			if ((y & 0400) == 0400)
				util::stream_format(stream, "SMA ");
			if ((y & 01000) == 01000)
				util::stream_format(stream, "SZO ");
			if ((y & 02000) == 02000)
				util::stream_format(stream, "SPI ");
			if (y & 070)
				util::stream_format(stream, "SZS 0%01o ", (y & 070));
			if (y & 7)
				util::stream_format(stream, "SZF 0%01o ", (y & 7));
>>>>>>> upstream/master
			IN;
			//etime = 5;
			break;
		}
<<<<<<< HEAD
	case SFT:
=======
	case pdp1_device::SFT:
>>>>>>> upstream/master
		{
			int nshift = 0;
			int mask = md & 0777;

			while (mask != 0)
			{
				nshift += mask & 1;
				mask = mask >> 1;
			}
			switch ((md >> 9) & 017)
			{
			case 1:
<<<<<<< HEAD
				sprintf (buffer, "RAL 0%02o", nshift);
				//etime = 5;
				break;
			case 2:
				sprintf (buffer, "RIL 0%02o", nshift);
				//etime = 5;
				break;
			case 3:
				sprintf (buffer, "RCL 0%02o", nshift);
				//etime = 5;
				break;
			case 5:
				sprintf (buffer, "SAL 0%02o", nshift);
				//etime = 5;
				break;
			case 6:
				sprintf (buffer, "SIL 0%02o", nshift);
				//etime = 5;
				break;
			case 7:
				sprintf (buffer, "SCL 0%02o", nshift);
				//etime = 5;
				break;
			case 9:
				sprintf (buffer, "RAR 0%02o", nshift);
				//etime = 5;
				break;
			case 10:
				sprintf (buffer, "RIR 0%02o", nshift);
				//etime = 5;
				break;
			case 11:
				sprintf (buffer, "RCR 0%02o", nshift);
				//etime = 5;
				break;
			case 13:
				sprintf (buffer, "SAR 0%02o", nshift);
				//etime = 5;
				break;
			case 14:
				sprintf (buffer, "SIR 0%02o", nshift);
				//etime = 5;
				break;
			case 15:
				sprintf (buffer, "SCR 0%02o", nshift);
				//etime = 5;
				break;
			default:
				sprintf (buffer, "SKP ???");
=======
				util::stream_format(stream, "RAL 0%02o", nshift);
				//etime = 5;
				break;
			case 2:
				util::stream_format(stream, "RIL 0%02o", nshift);
				//etime = 5;
				break;
			case 3:
				util::stream_format(stream, "RCL 0%02o", nshift);
				//etime = 5;
				break;
			case 5:
				util::stream_format(stream, "SAL 0%02o", nshift);
				//etime = 5;
				break;
			case 6:
				util::stream_format(stream, "SIL 0%02o", nshift);
				//etime = 5;
				break;
			case 7:
				util::stream_format(stream, "SCL 0%02o", nshift);
				//etime = 5;
				break;
			case 9:
				util::stream_format(stream, "RAR 0%02o", nshift);
				//etime = 5;
				break;
			case 10:
				util::stream_format(stream, "RIR 0%02o", nshift);
				//etime = 5;
				break;
			case 11:
				util::stream_format(stream, "RCR 0%02o", nshift);
				//etime = 5;
				break;
			case 13:
				util::stream_format(stream, "SAR 0%02o", nshift);
				//etime = 5;
				break;
			case 14:
				util::stream_format(stream, "SIR 0%02o", nshift);
				//etime = 5;
				break;
			case 15:
				util::stream_format(stream, "SCR 0%02o", nshift);
				//etime = 5;
				break;
			default:
				util::stream_format(stream, "SKP ???");
>>>>>>> upstream/master
				//etime = 5;
				break;
			}
			break;
		}
<<<<<<< HEAD
	case LAW:
		sprintf (buffer, "LAW 0%06o", y);
		IN;
		//etime = 5;
		break;
	case IOT:
		sprintf (buffer, "IOT 0%06o", md);
		//etime = 10;
		break;
	case OPR:
		{
			buffer[0] = 0;
			if ((y & 04000) == 04000)
				sprintf (buffer + strlen (buffer), "CLI ");
			if ((y & 02000) == 02000)
				sprintf (buffer + strlen (buffer), "LAT ");
			if ((y & 01000) == 01000)
				sprintf (buffer + strlen (buffer), "CMA ");
			if ((y & 0400) == 0400)
				sprintf (buffer + strlen (buffer), "HLT ");
			if ((y & 0100) == 0100)
				sprintf (buffer + strlen (buffer), "LAP ");
			if ((y & 010) && (y & 7))
				sprintf (buffer + strlen (buffer), "STF 0%01o ", (y & 7));
			if ((!(y & 010)) && (y & 7))
				sprintf (buffer + strlen (buffer), "CLF 0%01o ", (y & 7));
			if (!(y))
				sprintf (buffer + strlen (buffer), "NOP ");
=======
	case pdp1_device::LAW:
		util::stream_format(stream, "LAW 0%06o", y);
		IN;
		//etime = 5;
		break;
	case pdp1_device::IOT:
		util::stream_format(stream, "IOT 0%06o", md);
		//etime = 10;
		break;
	case pdp1_device::OPR:
		{
			if ((y & 04000) == 04000)
				util::stream_format(stream, "CLI ");
			if ((y & 02000) == 02000)
				util::stream_format(stream, "LAT ");
			if ((y & 01000) == 01000)
				util::stream_format(stream, "CMA ");
			if ((y & 0400) == 0400)
				util::stream_format(stream, "HLT ");
			if ((y & 0100) == 0100)
				util::stream_format(stream, "LAP ");
			if ((y & 010) && (y & 7))
				util::stream_format(stream, "STF 0%01o ", (y & 7));
			if ((!(y & 010)) && (y & 7))
				util::stream_format(stream, "CLF 0%01o ", (y & 7));
			if (!(y))
				util::stream_format(stream, "NOP ");
>>>>>>> upstream/master
			//etime = 5;
			break;
		}
	default:
<<<<<<< HEAD
		sprintf (buffer, "ILLEGAL");
=======
		util::stream_format(stream, "ILLEGAL");
>>>>>>> upstream/master
		//etime = 5;
		break;
	}
	return 4;
}
