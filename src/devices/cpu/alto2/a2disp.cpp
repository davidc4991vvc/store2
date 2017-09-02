// license:BSD-3-Clause
// copyright-holders:Juergen Buchmueller
/*****************************************************************************
 *
 *   Xerox AltoII display interface
 *
 *****************************************************************************/
<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "alto2cpu.h"
#include "a2roms.h"

/**
 * @brief PROM a38 contains the STOPWAKE' and MBEMBPTY' signals for the FIFO
<<<<<<< HEAD
 * <PRE>
 * The inputs to a38 are the UNLOAD counter RA[0-3] and the DDR<- counter
 * WA[0-3], and the designer decided to reverse the address lines :-)
 *
=======
 * The inputs to a38 are the UNLOAD counter RA[0-3] and the DDR<- counter
 * WA[0-3], and the designer decided to reverse the address lines :-)
 *
 * <PRE>
>>>>>>> upstream/master
 *  a38  counter
 *  -------------
 *   A0  RA[0]
 *   A1  RA[1]
 *   A2  RA[2]
 *   A3  RA[3]
 *   A4  WA[0]
 *   A5  WA[1]
 *   A6  WA[2]
 *   A7  WA[3]
 *
 * Only two bits of a38 are used:
 *  O1 (002) = STOPWAKE'
 *  O3 (010) = MBEMPTY'
 * </PRE>
 */

//! P3601 256x4 BPROM; display FIFO control: STOPWAKE, MBEMPTY
static const prom_load_t pl_displ_a38 =
{
	"displ.a38",
<<<<<<< HEAD
	0,
=======
	nullptr,
>>>>>>> upstream/master
	"fd30beb7",
	"65e4a19ba4ff748d525122128c514abedd55d866",
	/* size */  0400,
	/* amap */  AMAP_REVERSE_0_7,           // reverse address lines A0-A7
	/* axor */  0,
	/* dxor */  0,
	/* width */ 4,
	/* shift */ 0,
	/* dmap */  DMAP_DEFAULT,
	/* dand */  ZERO,
<<<<<<< HEAD
	/* type */  sizeof(UINT8)
};

//! PROM a38 bit O1 is STOPWAKE' (stop DWT if bit is zero)
#define FIFO_STOPWAKE(a38) (0 == (a38 & disp_a38_STOPWAKE) ? true : false)

//! PROM a38 bit O3 is MBEMPTY' (FIFO is empty if bit is zero)
#define FIFO_MBEMPTY(a38) (0 == (a38 & disp_a38_MBEMPTY) ? true : false)
=======
	/* type */  sizeof(uint8_t)
};

//! PROM a38 bit O1 is STOPWAKE' (stop DWT if bit is zero)
#define FIFO_STOPWAKE(a38) ((a38 & disp_a38_STOPWAKE) ? false : true)

//! PROM a38 bit O3 is MBEMPTY' (FIFO is empty if bit is zero)
#define FIFO_MBEMPTY(a38) ((a38 & disp_a38_MBEMPTY) ? false : true)
>>>>>>> upstream/master

/**
 * @brief emulation of PROM a63 in the display schematics page 8
 * <PRE>
 * The PROM's address lines are driven by a clock CLK, which is
 * pixel clock / 24, and an inverted half-scanline signal H[1]'.
 *
 * It is 32x8 bits and its output bits (B) are connected to the
 * signals, as well as its own address lines (A) through a latch
 * of the type SN74774 like this:
 *
 *  PROM  174   A   others
 *  ------------------------
 *  B0    D5    -   HBLANK
 *  B1    D0    -   HSYNC
 *  B2    D4    A0  -
 *  B3    D1    A1  -
 *  B4    D3    A2  -
 *  B5    D2    A3  -
 *  B6    -     -   SCANEND
 *  B7    -     -   HLCGATE
 *  ------------------------
 *  H[1]' -     A4  -
 *
 * The display_state_machine() is called at a rate of pixelclock/24.
 *
 * Decoded states of this PROM:
 *
 *  STATE  PROM   binary   HBLANK  HSYNC NEXT SCANEND HLCGATE
 *  ----------------------------------------------------------
 *    000  0007  00000111     1      1    001    0       0
 *    001  0013  00001011     1      1    002    0       0
 *    002  0015  00001101     1      0    003    0       0
 *    003  0021  00010001     1      0    004    0       0
 *    004  0024  00010100     0      0    005    0       0
 *    005  0030  00011000     0      0    006    0       0
 *    006  0034  00011100     0      0    007    0       0
 *    007  0040  00100000     0      0    010    0       0
 *    010  0044  00100100     0      0    011    0       0
 *    011  0050  00101000     0      0    012    0       0
 *    012  0054  00101100     0      0    013    0       0
 *    013  0060  00110000     0      0    014    0       0
 *    014  0064  00110100     0      0    015    0       0
 *    015  0070  00111000     0      0    016    0       0
 *    016  0074  00111100     0      0    017    0       0
 *    017  0200  10000000     0      0    000    0       1
 *    020  0004  00000100     0      0    001    0       0
 *    021  0010  00001000     0      0    002    0       0
 *    022  0014  00001100     0      0    003    0       0
 *    023  0020  00010000     0      0    004    0       0
 *    024  0024  00010100     0      0    005    0       0
 *    025  0030  00011000     0      0    006    0       0
 *    026  0034  00011100     0      0    007    0       0
 *    027  0040  00100000     0      0    010    0       0
 *    030  0044  00100100     0      0    011    0       0
 *    031  0050  00101000     0      0    012    0       0
 *    032  0054  00101100     0      0    013    0       0
 *    033  0060  00110000     0      0    014    0       0
 *    034  0064  00110100     0      0    015    0       0
 *    035  0070  00111000     0      0    016    0       0
 *    036  0175  01111101     1      0    017    1       0
 *    037  0203  10000011     1      1    000    0       1
 * </PRE>
 */

//! 82S23 32x8 BPROM; display HBLANK, HSYNC, SCANEND, HLCGATE ...
static const prom_load_t pl_displ_a63 =
{
	"displ.a63",
<<<<<<< HEAD
	0,
=======
	nullptr,
>>>>>>> upstream/master
	"82a20d60",
	"39d90703568be5419ada950e112d99227873fdea",
	/* size */  0040,
	/* amap */  AMAP_DEFAULT,
	/* axor */  0,
	/* dxor */  0,
	/* width */ 8,
	/* shift */ 0,
	/* dmap */  DMAP_DEFAULT,
	/* dand */  ZERO,
<<<<<<< HEAD
	/* type */  sizeof(UINT8)
=======
	/* type */  sizeof(uint8_t)
>>>>>>> upstream/master
};

//!< test the HBLANK (horizontal blanking) signal in PROM a63 being high
#define A63_HBLANK(a) ((a & disp_a63_HBLANK) ? true : false)

//!< test the HSYNC (horizontal synchonisation) signal in PROM a63 being high
#define A63_HSYNC(a) ((a & disp_a63_HSYNC) ? true : false)

//!< test the SCANEND (scanline end) signal in PROM a63 being high
#define A63_SCANEND(a) ((a & disp_a63_SCANEND) ? true : false)

//!< test the HLCGATE (horz. line counter gate) signal in PROM a63 being high
#define A63_HLCGATE(a) ((a & disp_a63_HLCGATE) ? true : false)

/**
 * @brief PROM a66 is a 256x4 bit (type 3601)
 * <PRE>
 * Address lines are driven by H[1] to H[128] of the horz. line counters.
 * PROM is enabled when H[256] and H[512] are both 0.
 *
<<<<<<< HEAD
 * Q1 is VSYNC for the odd field (with H1024=0)
 * Q2 is VSYNC for the even field (with H1024=1)
 * Q3 is VBLANK for the odd field (with H1024=0)
 * Q4 is VBLANK for the even field (with H1024=1)
=======
 * Q1 is VSYNC for the odd field (with H1024=1)
 * Q2 is VSYNC for the even field (with H1024=0)
 * Q3 is VBLANK for the odd field (with H1024=1)
 * Q4 is VBLANK for the even field (with H1024=0)
>>>>>>> upstream/master
 * </PRE>
 */

//! P3601 256x4 BPROM; display VSYNC and VBLANK
static const prom_load_t pl_displ_a66 =
{
	"displ.a66",
<<<<<<< HEAD
	0,
=======
	nullptr,
>>>>>>> upstream/master
	"9f91aad9",
	"69b1d4c71f4e18103112e8601850c2654e9265cf",
	/* size */  0400,
	/* amap */  AMAP_DEFAULT,
	/* axor */  0,
	/* dxor */  0,
	/* width */ 4,
	/* shift */ 0,
	/* dmap */  DMAP_DEFAULT,
	/* dand */  ZERO,
<<<<<<< HEAD
	/* type */  sizeof(UINT8)
=======
	/* type */  sizeof(uint8_t)
>>>>>>> upstream/master
};

//! test the VSYNC (vertical synchronisation) signal in PROM a66 being high
#define A66_VSYNC(a) (a & (HLC1024 ? disp_a66_VSYNC_ODD : disp_a66_VSYNC_EVEN) ? false : true)

//! test the VBLANK (vertical blanking) signal in PROM a66 being high
#define A66_VBLANK(a) (a & (HLC1024 ? disp_a66_VBLANK_ODD : disp_a66_VBLANK_EVEN) ? false : true)

/**
 * @brief double the bits for a byte (left and right of display word) to a word
 */
<<<<<<< HEAD
static const UINT16 double_bits[256] = {
=======
static const uint16_t double_bits[256] = {
>>>>>>> upstream/master
	0x0000,0x0003,0x000c,0x000f,0x0030,0x0033,0x003c,0x003f,
	0x00c0,0x00c3,0x00cc,0x00cf,0x00f0,0x00f3,0x00fc,0x00ff,
	0x0300,0x0303,0x030c,0x030f,0x0330,0x0333,0x033c,0x033f,
	0x03c0,0x03c3,0x03cc,0x03cf,0x03f0,0x03f3,0x03fc,0x03ff,
	0x0c00,0x0c03,0x0c0c,0x0c0f,0x0c30,0x0c33,0x0c3c,0x0c3f,
	0x0cc0,0x0cc3,0x0ccc,0x0ccf,0x0cf0,0x0cf3,0x0cfc,0x0cff,
	0x0f00,0x0f03,0x0f0c,0x0f0f,0x0f30,0x0f33,0x0f3c,0x0f3f,
	0x0fc0,0x0fc3,0x0fcc,0x0fcf,0x0ff0,0x0ff3,0x0ffc,0x0fff,
	0x3000,0x3003,0x300c,0x300f,0x3030,0x3033,0x303c,0x303f,
	0x30c0,0x30c3,0x30cc,0x30cf,0x30f0,0x30f3,0x30fc,0x30ff,
	0x3300,0x3303,0x330c,0x330f,0x3330,0x3333,0x333c,0x333f,
	0x33c0,0x33c3,0x33cc,0x33cf,0x33f0,0x33f3,0x33fc,0x33ff,
	0x3c00,0x3c03,0x3c0c,0x3c0f,0x3c30,0x3c33,0x3c3c,0x3c3f,
	0x3cc0,0x3cc3,0x3ccc,0x3ccf,0x3cf0,0x3cf3,0x3cfc,0x3cff,
	0x3f00,0x3f03,0x3f0c,0x3f0f,0x3f30,0x3f33,0x3f3c,0x3f3f,
	0x3fc0,0x3fc3,0x3fcc,0x3fcf,0x3ff0,0x3ff3,0x3ffc,0x3fff,
	0xc000,0xc003,0xc00c,0xc00f,0xc030,0xc033,0xc03c,0xc03f,
	0xc0c0,0xc0c3,0xc0cc,0xc0cf,0xc0f0,0xc0f3,0xc0fc,0xc0ff,
	0xc300,0xc303,0xc30c,0xc30f,0xc330,0xc333,0xc33c,0xc33f,
	0xc3c0,0xc3c3,0xc3cc,0xc3cf,0xc3f0,0xc3f3,0xc3fc,0xc3ff,
	0xcc00,0xcc03,0xcc0c,0xcc0f,0xcc30,0xcc33,0xcc3c,0xcc3f,
	0xccc0,0xccc3,0xcccc,0xcccf,0xccf0,0xccf3,0xccfc,0xccff,
	0xcf00,0xcf03,0xcf0c,0xcf0f,0xcf30,0xcf33,0xcf3c,0xcf3f,
	0xcfc0,0xcfc3,0xcfcc,0xcfcf,0xcff0,0xcff3,0xcffc,0xcfff,
	0xf000,0xf003,0xf00c,0xf00f,0xf030,0xf033,0xf03c,0xf03f,
	0xf0c0,0xf0c3,0xf0cc,0xf0cf,0xf0f0,0xf0f3,0xf0fc,0xf0ff,
	0xf300,0xf303,0xf30c,0xf30f,0xf330,0xf333,0xf33c,0xf33f,
	0xf3c0,0xf3c3,0xf3cc,0xf3cf,0xf3f0,0xf3f3,0xf3fc,0xf3ff,
	0xfc00,0xfc03,0xfc0c,0xfc0f,0xfc30,0xfc33,0xfc3c,0xfc3f,
	0xfcc0,0xfcc3,0xfccc,0xfccf,0xfcf0,0xfcf3,0xfcfc,0xfcff,
	0xff00,0xff03,0xff0c,0xff0f,0xff30,0xff33,0xff3c,0xff3f,
	0xffc0,0xffc3,0xffcc,0xffcf,0xfff0,0xfff3,0xfffc,0xffff
};

<<<<<<< HEAD
#define HLC1    ((m_dsp.hlc >>  0) & 1)     //!< horizontal line counter bit 0 (mid of the scanline)
#define HLC2    ((m_dsp.hlc >>  1) & 1)     //!< horizontal line counter bit 1
#define HLC4    ((m_dsp.hlc >>  2) & 1)     //!< horizontal line counter bit 2
#define HLC8    ((m_dsp.hlc >>  3) & 1)     //!< horizontal line counter bit 3
#define HLC16   ((m_dsp.hlc >>  4) & 1)     //!< horizontal line counter bit 4
#define HLC32   ((m_dsp.hlc >>  5) & 1)     //!< horizontal line counter bit 5
#define HLC64   ((m_dsp.hlc >>  6) & 1)     //!< horizontal line counter bit 6
#define HLC128  ((m_dsp.hlc >>  7) & 1)     //!< horizontal line counter bit 7
#define HLC256  ((m_dsp.hlc >>  8) & 1)     //!< horizontal line counter bit 8
#define HLC512  ((m_dsp.hlc >>  9) & 1)     //!< horizontal line counter bit 9
#define HLC1024 ((m_dsp.hlc >> 10) & 1)     //!< horizontal line counter bit 10 (odd/even field)
=======
#define HLC1    X_BIT(m_dsp.hlc,16,15)    //!< horizontal line counter bit 0 (mid of the scanline)
#define HLC2    X_BIT(m_dsp.hlc,16,14)    //!< horizontal line counter bit 1
#define HLC4    X_BIT(m_dsp.hlc,16,13)    //!< horizontal line counter bit 2
#define HLC8    X_BIT(m_dsp.hlc,16,12)    //!< horizontal line counter bit 3
#define HLC16   X_BIT(m_dsp.hlc,16,11)    //!< horizontal line counter bit 4
#define HLC32   X_BIT(m_dsp.hlc,16,10)    //!< horizontal line counter bit 5
#define HLC64   X_BIT(m_dsp.hlc,16, 9)    //!< horizontal line counter bit 6
#define HLC128  X_BIT(m_dsp.hlc,16, 8)    //!< horizontal line counter bit 7
#define HLC256  X_BIT(m_dsp.hlc,16, 7)    //!< horizontal line counter bit 8
#define HLC512  X_BIT(m_dsp.hlc,16, 6)    //!< horizontal line counter bit 9
#define HLC1024 X_BIT(m_dsp.hlc,16, 5)    //!< horizontal line counter bit 10 (odd/even field
>>>>>>> upstream/master

#define GET_SETMODE_SPEEDY(mode) X_RDBITS(mode,16,0,0)  //!< get the pixel clock speed from a SETMODE<- bus value
#define GET_SETMODE_INVERSE(mode) X_RDBITS(mode,16,1,1) //!< get the inverse video flag from a SETMODE<- bus value

//!< helper to extract A3-A0 from a PROM a63 value
#define A63_NEXT(n) ((n >> 2) & 017)

<<<<<<< HEAD
//! update the internal bitmap to a byte array
void alto2_cpu_device::update_bitmap_word(UINT16* bitmap, int x, int y, UINT16 word)
{
	// mixing with the cursor
	if (x == m_dsp.curxpos + 0)
		word ^= m_dsp.cursor0;
	if (x == m_dsp.curxpos + 1)
		word ^= m_dsp.cursor1;
	// no change?
	if (word == bitmap[x])
		return;
	bitmap[x] = word;
	UINT8* pix = m_dsp.scanline[y] + x * 16;
	*pix++ = (word >> 15) & 1;
	*pix++ = (word >> 14) & 1;
	*pix++ = (word >> 13) & 1;
	*pix++ = (word >> 12) & 1;
	*pix++ = (word >> 11) & 1;
	*pix++ = (word >> 10) & 1;
	*pix++ = (word >>  9) & 1;
	*pix++ = (word >>  8) & 1;
	*pix++ = (word >>  7) & 1;
	*pix++ = (word >>  6) & 1;
	*pix++ = (word >>  5) & 1;
	*pix++ = (word >>  4) & 1;
	*pix++ = (word >>  3) & 1;
	*pix++ = (word >>  2) & 1;
	*pix++ = (word >>  1) & 1;
	*pix++ = (word >>  0) & 1;
=======
//! update the internal frame buffer and draw the scanline segment if changed
void alto2_cpu_device::update_framebuf_word(uint16_t* framebuf, int x, int y, uint16_t word)
{
	if (y >= A2_DISP_TOTAL_HEIGHT)
		return;
	int xpword = (m_dsp.xpreg ^ 01777) / 16;
	// mixing with the cursor
	if (x == xpword++)
		word ^= (m_dsp.csr << (m_dsp.xpreg % 16)) >> 16;
	if (x == xpword)
		word ^= (m_dsp.csr << (m_dsp.xpreg % 16)) & 0xffff;
	// no change?
	if (word == framebuf[x])
		return;
	framebuf[x] = word;
	draw_scanline8(*m_dsp.bitmap, x * 16, y, 16, m_dsp.patterns + 16 * word, nullptr);
>>>>>>> upstream/master
}

/**
 * @brief unload the next word from the display FIFO and shift it to the screen
 */
void alto2_cpu_device::unload_word()
{
	int x = m_unload_word;
<<<<<<< HEAD
	int y = ((m_dsp.hlc - m_dsp.vblank) & ~02001) ^ HLC1024;

	if (y < 0 || y >= ALTO2_DISPLAY_HEIGHT || x >= ALTO2_DISPLAY_VISIBLE_WORDS)
	{
		m_unload_time = -1;
		return;
	}
	UINT16* bitmap = m_dsp.raw_bitmap  + y * ALTO2_DISPLAY_SCANLINE_WORDS;
	UINT16 word = m_dsp.inverse;
	UINT8 a38 = m_disp_a38[m_dsp.ra * 16 + m_dsp.wa];
=======
	int y = m_dsp.scanline;

	if (x >= A2_DISP_VISIBLE_WORDS) {
		m_unload_time = -1;
		return;
	}
	uint16_t* framebuf = m_dsp.framebuf.get() + y * A2_DISP_SCANLINE_WORDS;
	uint16_t word = m_dsp.inverse;
	uint8_t a38 = m_disp_a38[m_dsp.ra * 16 + m_dsp.wa];
>>>>>>> upstream/master
	if (FIFO_MBEMPTY(a38))
	{
		LOG((this,LOG_DISPL,1, " DSP FIFO underrun y:%d x:%d\n", y, x));
	}
	else
	{
		word ^= m_dsp.fifo[m_dsp.ra];
<<<<<<< HEAD
		m_dsp.ra = (m_dsp.ra + 1) % ALTO2_DISPLAY_FIFO;
		LOG((this,LOG_DISPL,3, " DSP pull %04x from FIFO[%02o] y:%d x:%d\n",
				word, (m_dsp.ra - 1) & (ALTO2_DISPLAY_FIFO - 1), y, x));
=======
		m_dsp.ra = (m_dsp.ra + 1) % A2_DISP_FIFO;
		LOG((this,LOG_DISPL,3, " DSP pull %04x from FIFO[%02o] y:%d x:%d\n",
				word, (m_dsp.ra - 1) & (A2_DISP_FIFO - 1), y, x));
>>>>>>> upstream/master
	}

	if (m_dsp.halfclock)
	{
<<<<<<< HEAD
		UINT16 word1 = double_bits[word / 256];
		UINT16 word2 = double_bits[word % 256];
		update_bitmap_word(bitmap, x, y, word1);
		x++;
		if (x < ALTO2_DISPLAY_VISIBLE_WORDS)
		{
			update_bitmap_word(bitmap, x, y, word2);
			x++;
		}
		m_unload_time += ALTO2_DISPLAY_BITTIME(32);
	}
	else
	{
		update_bitmap_word(bitmap, x, y, word);
		x++;
		m_unload_time += ALTO2_DISPLAY_BITTIME(16);
	}
	if (x < ALTO2_DISPLAY_VISIBLE_WORDS)
=======
		const uint16_t word1 = double_bits[word / 256];
		update_framebuf_word(framebuf, x, y, word1);
		x++;
		if (x < A2_DISP_VISIBLE_WORDS)
		{
			const uint16_t word2 = double_bits[word % 256];
			update_framebuf_word(framebuf, x, y, word2);
			x++;
		}
		m_unload_time += A2_DISP_BITTIME(32);
	}
	else
	{
		update_framebuf_word(framebuf, x, y, word);
		x++;
		m_unload_time += A2_DISP_BITTIME(16);
	}
	if (x < A2_DISP_VISIBLE_WORDS)
>>>>>>> upstream/master
		m_unload_word = x;
	else
		m_unload_time = -1;
}


/**
 * @brief function called by the CPU to enter the next display state
 *
 * There are 32 states per scanline and 875 scanlines per frame.
 */
void alto2_cpu_device::display_state_machine()
{
	LOG((this,LOG_DISPL,5,"DSP%03o:", m_dsp.state));
	if (020 == m_dsp.state)
	{
		LOG((this,LOG_DISPL,2," HLC=%d", m_dsp.hlc));
	}

<<<<<<< HEAD
	UINT8 a63 = m_disp_a63[m_dsp.state];
=======
	const uint8_t a63 = m_disp_a63[m_dsp.state];
>>>>>>> upstream/master
	if (A63_HLCGATE(a63))
	{
		// count horizontal line counters and wrap
		m_dsp.hlc += 1;
<<<<<<< HEAD
		if (m_dsp.hlc > ALTO2_DISPLAY_HLC_END)
			m_dsp.hlc = ALTO2_DISPLAY_HLC_START;
=======
		if (m_dsp.hlc > A2_DISP_HLC_END) {
			m_dsp.hlc = A2_DISP_HLC_START;
			m_dsp.scanline = 0;
		} else if (m_dsp.hlc == 1024) {
			m_dsp.scanline = 1;
		}
>>>>>>> upstream/master
		// wake up the memory refresh task _twice_ on each scanline
		m_task_wakeup |= 1 << task_mrt;
	}
	// PROM a66 is disabled, if any of HLC256 or HLC512 are high
<<<<<<< HEAD
	UINT8 a66 = (HLC256 || HLC512) ? 017 : m_disp_a66[m_dsp.hlc & 0377];

	// next address from PROM a63, use A4 from HLC1
	UINT8 next = ((HLC1 ^ 1) << 4) | A63_NEXT(a63);

	if (A66_VBLANK(a66))
	{
		// Rising edge of VBLANK: remember HLC[1-10] where the VBLANK starts
		m_dsp.vblank = m_dsp.hlc & ~02000;

		LOG((this,LOG_DISPL,1, " VBLANK"));

		// VSYNC is always within VBLANK, thus we handle it only here
		if (A66_VSYNC(a66))
		{
			if (!A66_VSYNC(m_dsp.a66))
			{
				LOG((this,LOG_DISPL,1, " VSYNC/ (wake DVT)"));
				/*
				 * The display vertical task DVT is woken once per field
				 * at the beginning of vertical retrace.
				 */
				m_task_wakeup |= 1 << task_dvt;
				// TODO: upade odd or even field of the internal bitmap now?
			}
		}
=======
	const uint8_t a66 = (HLC256 | HLC512) ? 017 : m_disp_a66[m_dsp.hlc & 0377];

	// next address from PROM a63, use A4 from HLC1
	const uint8_t next = ((HLC1 ^ 1) << 4) | A63_NEXT(a63);

	if (A66_VBLANK(a66))
	{
		LOG((this,LOG_DISPL,1, " VBLANK"));
		// Rising edge of VBLANK?
		if (!A66_VBLANK(m_dsp.a66)) {
			// synchronize on MAME video timing
			if (!m_dsp.vblank) {
				m_display_time += A2_DISP_BITTIME(1);
				return;
			}
			m_dsp.vblank = false;
		}

		// VSYNC is always within VBLANK, thus we handle it only here
		if (A66_VSYNC(a66) && !A66_VSYNC(m_dsp.a66))
		{
			LOG((this,LOG_DISPL,1, " VSYNC/ (wake DVT)"));
			/*
			 * The display vertical task DVT is woken once per field
			 * at the beginning of vertical retrace.
			 */
			m_task_wakeup |= 1 << task_dvt;
		}
		m_dsp.inverse = 0xffff;
>>>>>>> upstream/master
	}
	else
	{
		// Falling edge of VBLANK?
		if (A66_VBLANK(m_dsp.a66))
		{
			/*
			 * VBLANKPULSE:
			 * The display horizontal task DHT is woken once at the
			 * beginning of each field, and thereafter whenever the
			 * display word task blocks.
			 *
			 * The DHT can block itself, in which case neither it nor
			 * the word task can be woken until the start of the
			 * next field.
			 */
			LOG((this,LOG_DISPL,1, " VBLANKPULSE (wake DHT)"));
			m_dsp.dht_blocks = false;
			m_dsp.dwt_blocks = false;
			m_task_wakeup |= 1 << task_dht;
			/*
			 * VBLANKPULSE also resets the cursor task block flip flop,
			 * which is built from two NAND gates a40c and a40d (74H01).
			 */
			m_dsp.curt_blocks = false;
		}
		if (!A63_HBLANK(a63) && A63_HBLANK(m_dsp.a63))
		{
<<<<<<< HEAD
			// Falling edge of a63 HBLANK starts unloading of FIFO words
			LOG((this,LOG_DISPL,1, " HBLANK\\ UNLOAD"));
			m_unload_time = ALTO2_DISPLAY_BITTIME(m_dsp.halfclock ? 32 : 16);
=======
			m_dsp.scanline += 2;
			// Falling edge of a63 HBLANK starts unloading of FIFO words
			LOG((this,LOG_DISPL,1, " HBLANK\\ UNLOAD"));
			m_unload_time = A2_DISP_BITTIME(m_dsp.halfclock ? 40+32 : 40+16);
>>>>>>> upstream/master
			m_unload_word = 0;
		}
	}

	/*
	 * The wakeup request for the display word task (DWT) is controlled by
	 * the state of the 16 word FIFO. If DWT has not executed a BLOCK,
	 * if DHT is not blocked, and if the buffer is not full, DWT wakeups
	 * are generated.
	 */
<<<<<<< HEAD
	UINT8 a38 = m_disp_a38[m_dsp.ra * 16 + m_dsp.wa];
=======
	uint8_t a38 = m_disp_a38[m_dsp.ra * 16 + m_dsp.wa];
>>>>>>> upstream/master
	if (!m_dsp.dwt_blocks && !m_dsp.dht_blocks && !FIFO_STOPWAKE(a38))
	{
		m_task_wakeup |= 1 << task_dwt;
		LOG((this,LOG_DISPL,1, " (wake DWT)"));
	}

	// Stop waking up the DWT when SCANEND is active
	if (A63_SCANEND(a63))
	{
		m_task_wakeup &= ~(1 << task_dwt);
		LOG((this,LOG_DISPL,1, " SCANEND"));
	}

	LOG((this,LOG_DISPL,1, "%s", A63_HBLANK(a63) ? " HBLANK": ""));

	if (A63_HSYNC(a63))
	{
		// Active HSYNC
		if (!A63_HSYNC(m_dsp.a63))
		{
			// Rising edge of HSYNC => CLRBUF
			LOG((this,LOG_DISPL,1, " HSYNC/ (CLRBUF)"));
			/*
			 * The hardware sets the buffer empty and clears the DWT block
			 * flip-flop at the beginning of horizontal retrace for
			 * every scanline.
			 */
			m_dsp.wa = 0;
			m_dsp.ra = 0;
			m_dsp.dwt_blocks = false;
			// now take the new values from the last SETMODE<-
			m_dsp.inverse = GET_SETMODE_INVERSE(m_dsp.setmode) ? 0xffff : 0x0000;
			m_dsp.halfclock = GET_SETMODE_SPEEDY(m_dsp.setmode) ? true : false;
			// stop the CPU execution loop from calling unload_word()
			m_unload_time = -1;
		}
		else
		{
			LOG((this,LOG_DISPL,1, " HSYNC"));
		}
	}
	else
	// Falling edge of HSYNC?
	if (A63_HSYNC(m_dsp.a63))
	{
		/*
		 * CLRBUF' also resets the 2nd cursor task block flip flop,
		 * which is built from two NAND gates a30c and a30d (74H00).
		 * If both flip flops are reset, the NOR gate a20d (74S02)
		 * decodes this as WAKECURT signal.
		 */
		m_dsp.curt_wakeup = true;
		if (!m_dsp.curt_blocks)
			m_task_wakeup |= 1 << task_curt;
	}

	LOG((this,LOG_DISPL,1, " NEXT:%03o\n", next));

	m_dsp.a63 = a63;
	m_dsp.a66 = a66;
	m_dsp.state = next;
<<<<<<< HEAD
	m_dsp_time += ALTO2_DISPLAY_BITTIME(32);
=======
	m_display_time += A2_DISP_BITTIME(32);
>>>>>>> upstream/master
}

/**
 * @brief branch on evenfield
 *
 * NEXT(09) = even field ? 1 : 0
 */
void alto2_cpu_device::f2_late_evenfield()
{
<<<<<<< HEAD
	UINT16 r = HLC1024 ^ 1;
=======
	uint16_t r = HLC1024 ^ 1;
>>>>>>> upstream/master
	LOG((this,LOG_DISPL,2,"  EVENFIELD branch (%#o | %#o)\n", m_next2, r));
	m_next2 |= r;
}

/**
 * @brief initialize the display context to useful values
 *
<<<<<<< HEAD
 * Zap the display context to all 0s.
 * Allocate a bitmap array to save blitting to the screen when
 * there is no change in the data words.
=======
 * Zap the display context.
 * Allocate a framebuf array to save updating the bitmap when
 * there is no change in the data word.
>>>>>>> upstream/master
 */
void alto2_cpu_device::init_disp()
{
	memset(&m_dsp, 0, sizeof(m_dsp));
	save_item(NAME(m_dsp.state));
	save_item(NAME(m_dsp.hlc));
	save_item(NAME(m_dsp.setmode));
	save_item(NAME(m_dsp.inverse));
	save_item(NAME(m_dsp.halfclock));
	save_item(NAME(m_dsp.fifo));
	save_item(NAME(m_dsp.wa));
	save_item(NAME(m_dsp.ra));
	save_item(NAME(m_dsp.a63));
	save_item(NAME(m_dsp.a66));
	save_item(NAME(m_dsp.dht_blocks));
	save_item(NAME(m_dsp.dwt_blocks));
	save_item(NAME(m_dsp.curt_blocks));
	save_item(NAME(m_dsp.curt_wakeup));
<<<<<<< HEAD
	save_item(NAME(m_dsp.vblank));
	save_item(NAME(m_dsp.xpreg));
	save_item(NAME(m_dsp.csr));
	save_item(NAME(m_dsp.curxpos));
	save_item(NAME(m_dsp.cursor0));
	save_item(NAME(m_dsp.cursor1));
=======
	save_item(NAME(m_dsp.xpreg));
	save_item(NAME(m_dsp.csr));
>>>>>>> upstream/master

	m_disp_a38 = prom_load(machine(), &pl_displ_a38, memregion("displ_a38")->base());
	m_disp_a63 = prom_load(machine(), &pl_displ_a63, memregion("displ_a63")->base());
	m_disp_a66 = prom_load(machine(), &pl_displ_a66, memregion("displ_a66")->base());

<<<<<<< HEAD
	m_dsp.hlc = ALTO2_DISPLAY_HLC_START;

	m_dsp.raw_bitmap = auto_alloc_array(machine(), UINT16, ALTO2_DISPLAY_HEIGHT * ALTO2_DISPLAY_SCANLINE_WORDS);
	m_dsp.scanline = auto_alloc_array(machine(), UINT8*, ALTO2_DISPLAY_HEIGHT + ALTO2_FAKE_STATUS_H);
	for (int y = 0; y < ALTO2_DISPLAY_HEIGHT + ALTO2_FAKE_STATUS_H; y++)
		m_dsp.scanline[y] = auto_alloc_array(machine(), UINT8, ALTO2_DISPLAY_TOTAL_WIDTH);

	m_dsp.bitmap = auto_bitmap_ind16_alloc(machine(), ALTO2_DISPLAY_WIDTH, ALTO2_DISPLAY_HEIGHT + ALTO2_FAKE_STATUS_H);
=======
	m_dsp.hlc = A2_DISP_HLC_START;

	m_dsp.framebuf = std::make_unique<uint16_t[]>(A2_DISP_TOTAL_HEIGHT * A2_DISP_SCANLINE_WORDS);
	m_dsp.patterns = auto_alloc_array(machine(), uint8_t, 65536 * 16);
	for (int y = 0; y < 65536; y++) {
		uint8_t* dst = m_dsp.patterns + y * 16;
		for (int x = 0; x < 16; x++)
			*dst++ = (~y >> (15 - x)) & 1;
	}

	// Allocate a bitmap including the V/H blank areas
	m_dsp.bitmap = std::make_unique<bitmap_ind16>(A2_DISP_TOTAL_WIDTH, A2_DISP_TOTAL_HEIGHT);
>>>>>>> upstream/master
	m_dsp.state = 0;
}

void alto2_cpu_device::exit_disp()
{
	// nothing to do yet
}

void alto2_cpu_device::reset_disp()
{
	m_dsp.state = 0;
<<<<<<< HEAD
	m_dsp.hlc = ALTO2_DISPLAY_HLC_START;
=======
	m_dsp.hlc = A2_DISP_HLC_START;
>>>>>>> upstream/master
	m_dsp.a63 = 0;
	m_dsp.a66 = 0;
	m_dsp.setmode = 0;
	m_dsp.inverse = 0;
<<<<<<< HEAD
=======
	m_dsp.scanline = 0;
>>>>>>> upstream/master
	m_dsp.halfclock = false;
	m_dsp.wa = 0;
	m_dsp.ra = 0;
	m_dsp.dht_blocks = false;
	m_dsp.dwt_blocks = false;
	m_dsp.curt_blocks = false;
	m_dsp.curt_wakeup = false;
<<<<<<< HEAD
	m_dsp.vblank = 0;
	m_dsp.xpreg = 0;
	m_dsp.csr = 0;
	m_dsp.curxpos = 0;
	m_dsp.cursor0 = 0;
	m_dsp.cursor1 = 0;
	memset(m_dsp.raw_bitmap, 0, sizeof(UINT16) * ALTO2_DISPLAY_HEIGHT * ALTO2_DISPLAY_SCANLINE_WORDS);
	for (int y = 0; y < ALTO2_DISPLAY_HEIGHT; y++)
		memset(m_dsp.scanline[y], 0, sizeof(UINT8) * ALTO2_DISPLAY_TOTAL_WIDTH);
	m_dsp.odd_frame = false;

	for (int y = ALTO2_DISPLAY_HEIGHT; y < ALTO2_DISPLAY_HEIGHT + ALTO2_FAKE_STATUS_H; y++)
		memset(m_dsp.scanline[y], 1, sizeof(UINT8) * ALTO2_DISPLAY_TOTAL_WIDTH);
	fake_status_printf(1, "* Fake Status *");
}

/* Video update */
UINT32 alto2_cpu_device::screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	pen_t palette_bw[2];
	palette_bw[0] = screen.palette()->white_pen();
	palette_bw[1] = screen.palette()->black_pen();
	// copy even or odd field
	for (int y = m_dsp.odd_frame ? 0 : 1; y < ALTO2_DISPLAY_HEIGHT; y += 2)
		draw_scanline8(*m_dsp.bitmap, 0, y, ALTO2_DISPLAY_WIDTH, m_dsp.scanline[y], palette_bw);
	// copy fake status scanlines
	for (int y = ALTO2_DISPLAY_HEIGHT; y < ALTO2_DISPLAY_HEIGHT + ALTO2_FAKE_STATUS_H; y++)
		draw_scanline8(*m_dsp.bitmap, 0, y, ALTO2_DISPLAY_WIDTH, m_dsp.scanline[y], palette_bw);
	// copy bitmap
=======
	m_dsp.vblank = false;
	m_dsp.xpreg = 0;
	m_dsp.csr = 0;
	memset(m_dsp.framebuf.get(), 1, sizeof(uint16_t) * A2_DISP_HEIGHT * A2_DISP_SCANLINE_WORDS);
}

/* Video update */
uint32_t alto2_cpu_device::screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
>>>>>>> upstream/master
	copybitmap(bitmap, *m_dsp.bitmap, 0, 0, 0, 0, cliprect);
	return 0;
}

<<<<<<< HEAD
void alto2_cpu_device::screen_eof(screen_device &screen, bool state)
{
	if (state)
		m_dsp.odd_frame = !m_dsp.odd_frame;
}

/*****************************************************************************
 *
 *   FAKE STATUS LINE
 *
 *****************************************************************************/

typedef struct {
	UINT8 code;
	UINT8 bits[10];
} bdf_6x10_t;

/**
 * STARTFONT 2.1
 * COMMENT "$ucs-fonts: 6x10.bdf,v 1.34 2002-11-10 19:12:30+00 mgk25 Rel $"
 * COMMENT "Send bug reports to Markus Kuhn <http://www.cl.cam.ac.uk/~mgk25/>"
 * FONT -Misc-Fixed-Medium-R-Normal--10-100-75-75-C-60-ISO10646-1
 * SIZE 10 75 75
 * FONTBOUNDINGBOX 6 10 0 -2
 * STARTPROPERTIES 22
 * FONTNAME_REGISTRY ""
 * FOUNDRY "Misc"
 * FAMILY_NAME "Fixed"
 * WEIGHT_NAME "Medium"
 * SLANT "R"
 * SETWIDTH_NAME "Normal"
 * ADD_STYLE_NAME ""
 * PIXEL_SIZE 10
 * POINT_SIZE 100
 * RESOLUTION_X 75
 * RESOLUTION_Y 75
 * SPACING "C"
 * AVERAGE_WIDTH 60
 * CHARSET_REGISTRY "ISO10646"
 * CHARSET_ENCODING "1"
 * FONT_ASCENT 8
 * FONT_DESCENT 2
 * DEFAULT_CHAR 0
 * COPYRIGHT "Public domain terminal emulator font.  Share and enjoy."
 * _XMBDFED_INFO "Edited with xmbdfed 4.5."
 * CAP_HEIGHT 7
 * X_HEIGHT 5
 * ENDPROPERTIES
 * CHARS 1597
 */
static const bdf_6x10_t bdf_6x10[] = {
/* space                */ { 32,    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* exclam               */ { 33,    {0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x20, 0x00, 0x00 }},
/* quotedbl             */ { 34,    {0x00, 0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* numbersign           */ { 35,    {0x00, 0x50, 0x50, 0xF8, 0x50, 0xF8, 0x50, 0x50, 0x00, 0x00 }},
/* dollar               */ { 36,    {0x00, 0x20, 0x70, 0xA0, 0x70, 0x28, 0x70, 0x20, 0x00, 0x00 }},
/* percent              */ { 37,    {0x00, 0x48, 0xA8, 0x50, 0x20, 0x50, 0xA8, 0x90, 0x00, 0x00 }},
/* ampersand            */ { 38,    {0x00, 0x40, 0xA0, 0xA0, 0x40, 0xA8, 0x90, 0x68, 0x00, 0x00 }},
/* quotesingle          */ { 39,    {0x00, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* parenleft            */ { 40,    {0x00, 0x10, 0x20, 0x40, 0x40, 0x40, 0x20, 0x10, 0x00, 0x00 }},
/* parenright           */ { 41,    {0x00, 0x40, 0x20, 0x10, 0x10, 0x10, 0x20, 0x40, 0x00, 0x00 }},
/* asterisk             */ { 42,    {0x00, 0x00, 0x88, 0x50, 0xF8, 0x50, 0x88, 0x00, 0x00, 0x00 }},
/* plus                 */ { 43,    {0x00, 0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00, 0x00 }},
/* comma                */ { 44,    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x20, 0x40, 0x00 }},
/* hyphen               */ { 45,    {0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* period               */ { 46,    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0x20, 0x00 }},
/* slash                */ { 47,    {0x00, 0x08, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0x00, 0x00 }},
/* zero                 */ { 48,    {0x00, 0x20, 0x50, 0x88, 0x88, 0x88, 0x50, 0x20, 0x00, 0x00 }},
/* one                  */ { 49,    {0x00, 0x20, 0x60, 0xA0, 0x20, 0x20, 0x20, 0xF8, 0x00, 0x00 }},
/* two                  */ { 50,    {0x00, 0x70, 0x88, 0x08, 0x30, 0x40, 0x80, 0xF8, 0x00, 0x00 }},
/* three                */ { 51,    {0x00, 0xF8, 0x08, 0x10, 0x30, 0x08, 0x88, 0x70, 0x00, 0x00 }},
/* four                 */ { 52,    {0x00, 0x10, 0x30, 0x50, 0x90, 0xF8, 0x10, 0x10, 0x00, 0x00 }},
/* five                 */ { 53,    {0x00, 0xF8, 0x80, 0xB0, 0xC8, 0x08, 0x88, 0x70, 0x00, 0x00 }},
/* six                  */ { 54,    {0x00, 0x30, 0x40, 0x80, 0xB0, 0xC8, 0x88, 0x70, 0x00, 0x00 }},
/* seven                */ { 55,    {0x00, 0xF8, 0x08, 0x10, 0x10, 0x20, 0x40, 0x40, 0x00, 0x00 }},
/* eight                */ { 56,    {0x00, 0x70, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* nine                 */ { 57,    {0x00, 0x70, 0x88, 0x98, 0x68, 0x08, 0x10, 0x60, 0x00, 0x00 }},
/* colon                */ { 58,    {0x00, 0x00, 0x20, 0x70, 0x20, 0x00, 0x20, 0x70, 0x20, 0x00 }},
/* semicolon            */ { 59,    {0x00, 0x00, 0x20, 0x70, 0x20, 0x00, 0x30, 0x20, 0x40, 0x00 }},
/* less                 */ { 60,    {0x00, 0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08, 0x00, 0x00 }},
/* equal                */ { 61,    {0x00, 0x00, 0x00, 0xF8, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00 }},
/* greater              */ { 62,    {0x00, 0x40, 0x20, 0x10, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00 }},
/* question             */ { 63,    {0x00, 0x70, 0x88, 0x10, 0x20, 0x20, 0x00, 0x20, 0x00, 0x00 }},
/* at                   */ { 64,    {0x00, 0x70, 0x88, 0x98, 0xA8, 0xB0, 0x80, 0x70, 0x00, 0x00 }},
/* A                    */ { 65,    {0x00, 0x20, 0x50, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00, 0x00 }},
/* B                    */ { 66,    {0x00, 0xF0, 0x48, 0x48, 0x70, 0x48, 0x48, 0xF0, 0x00, 0x00 }},
/* C                    */ { 67,    {0x00, 0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70, 0x00, 0x00 }},
/* D                    */ { 68,    {0x00, 0xF0, 0x48, 0x48, 0x48, 0x48, 0x48, 0xF0, 0x00, 0x00 }},
/* E                    */ { 69,    {0x00, 0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8, 0x00, 0x00 }},
/* F                    */ { 70,    {0x00, 0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0x80, 0x00, 0x00 }},
/* G                    */ { 71,    {0x00, 0x70, 0x88, 0x80, 0x80, 0x98, 0x88, 0x70, 0x00, 0x00 }},
/* H                    */ { 72,    {0x00, 0x88, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x88, 0x00, 0x00 }},
/* I                    */ { 73,    {0x00, 0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00 }},
/* J                    */ { 74,    {0x00, 0x38, 0x10, 0x10, 0x10, 0x10, 0x90, 0x60, 0x00, 0x00 }},
/* K                    */ { 75,    {0x00, 0x88, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x88, 0x00, 0x00 }},
/* L                    */ { 76,    {0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF8, 0x00, 0x00 }},
/* M                    */ { 77,    {0x00, 0x88, 0x88, 0xD8, 0xA8, 0x88, 0x88, 0x88, 0x00, 0x00 }},
/* N                    */ { 78,    {0x00, 0x88, 0x88, 0xC8, 0xA8, 0x98, 0x88, 0x88, 0x00, 0x00 }},
/* O                    */ { 79,    {0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* P                    */ { 80,    {0x00, 0xF0, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80, 0x00, 0x00 }},
/* Q                    */ { 81,    {0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0xA8, 0x70, 0x08, 0x00 }},
/* R                    */ { 82,    {0x00, 0xF0, 0x88, 0x88, 0xF0, 0xA0, 0x90, 0x88, 0x00, 0x00 }},
/* S                    */ { 83,    {0x00, 0x70, 0x88, 0x80, 0x70, 0x08, 0x88, 0x70, 0x00, 0x00 }},
/* T                    */ { 84,    {0x00, 0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00 }},
/* U                    */ { 85,    {0x00, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* V                    */ { 86,    {0x00, 0x88, 0x88, 0x88, 0x50, 0x50, 0x50, 0x20, 0x00, 0x00 }},
/* W                    */ { 87,    {0x00, 0x88, 0x88, 0x88, 0xA8, 0xA8, 0xD8, 0x88, 0x00, 0x00 }},
/* X                    */ { 88,    {0x00, 0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88, 0x00, 0x00 }},
/* Y                    */ { 89,    {0x00, 0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00 }},
/* Z                    */ { 90,    {0x00, 0xF8, 0x08, 0x10, 0x20, 0x40, 0x80, 0xF8, 0x00, 0x00 }},
/* bracketleft          */ { 91,    {0x00, 0x70, 0x40, 0x40, 0x40, 0x40, 0x40, 0x70, 0x00, 0x00 }},
/* backslash            */ { 92,    {0x00, 0x80, 0x80, 0x40, 0x20, 0x10, 0x08, 0x08, 0x00, 0x00 }},
/* bracketright         */ { 93,    {0x00, 0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70, 0x00, 0x00 }},
/* asciicircum          */ { 94,    {0x00, 0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* underscore           */ { 95,    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00 }},
/* grave                */ { 96,    {0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* a                    */ { 97,    {0x00, 0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00, 0x00 }},
/* b                    */ { 98,    {0x00, 0x80, 0x80, 0xB0, 0xC8, 0x88, 0xC8, 0xB0, 0x00, 0x00 }},
/* c                    */ { 99,    {0x00, 0x00, 0x00, 0x70, 0x88, 0x80, 0x88, 0x70, 0x00, 0x00 }},
/* d                    */ { 100,   {0x00, 0x08, 0x08, 0x68, 0x98, 0x88, 0x98, 0x68, 0x00, 0x00 }},
/* e                    */ { 101,   {0x00, 0x00, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x70, 0x00, 0x00 }},
/* f                    */ { 102,   {0x00, 0x30, 0x48, 0x40, 0xF0, 0x40, 0x40, 0x40, 0x00, 0x00 }},
/* g                    */ { 103,   {0x00, 0x00, 0x00, 0x78, 0x88, 0x88, 0x78, 0x08, 0x88, 0x70 }},
/* h                    */ { 104,   {0x00, 0x80, 0x80, 0xB0, 0xC8, 0x88, 0x88, 0x88, 0x00, 0x00 }},
/* i                    */ { 105,   {0x00, 0x20, 0x00, 0x60, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00 }},
/* j                    */ { 106,   {0x00, 0x08, 0x00, 0x18, 0x08, 0x08, 0x08, 0x48, 0x48, 0x30 }},
/* k                    */ { 107,   {0x00, 0x80, 0x80, 0x88, 0x90, 0xE0, 0x90, 0x88, 0x00, 0x00 }},
/* l                    */ { 108,   {0x00, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00 }},
/* m                    */ { 109,   {0x00, 0x00, 0x00, 0xD0, 0xA8, 0xA8, 0xA8, 0x88, 0x00, 0x00 }},
/* n                    */ { 110,   {0x00, 0x00, 0x00, 0xB0, 0xC8, 0x88, 0x88, 0x88, 0x00, 0x00 }},
/* o                    */ { 111,   {0x00, 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* p                    */ { 112,   {0x00, 0x00, 0x00, 0xB0, 0xC8, 0x88, 0xC8, 0xB0, 0x80, 0x80 }},
/* q                    */ { 113,   {0x00, 0x00, 0x00, 0x68, 0x98, 0x88, 0x98, 0x68, 0x08, 0x08 }},
/* r                    */ { 114,   {0x00, 0x00, 0x00, 0xB0, 0xC8, 0x80, 0x80, 0x80, 0x00, 0x00 }},
/* s                    */ { 115,   {0x00, 0x00, 0x00, 0x70, 0x80, 0x70, 0x08, 0xF0, 0x00, 0x00 }},
/* t                    */ { 116,   {0x00, 0x40, 0x40, 0xF0, 0x40, 0x40, 0x48, 0x30, 0x00, 0x00 }},
/* u                    */ { 117,   {0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x98, 0x68, 0x00, 0x00 }},
/* v                    */ { 118,   {0x00, 0x00, 0x00, 0x88, 0x88, 0x50, 0x50, 0x20, 0x00, 0x00 }},
/* w                    */ { 119,   {0x00, 0x00, 0x00, 0x88, 0x88, 0xA8, 0xA8, 0x50, 0x00, 0x00 }},
/* x                    */ { 120,   {0x00, 0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, 0x00, 0x00 }},
/* y                    */ { 121,   {0x00, 0x00, 0x00, 0x88, 0x88, 0x98, 0x68, 0x08, 0x88, 0x70 }},
/* z                    */ { 122,   {0x00, 0x00, 0x00, 0xF8, 0x10, 0x20, 0x40, 0xF8, 0x00, 0x00 }},
/* braceleft            */ { 123,   {0x00, 0x18, 0x20, 0x10, 0x60, 0x10, 0x20, 0x18, 0x00, 0x00 }},
/* bar                  */ { 124,   {0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00 }},
/* braceright           */ { 125,   {0x00, 0x60, 0x10, 0x20, 0x18, 0x20, 0x10, 0x60, 0x00, 0x00 }},
/* asciitilde           */ { 126,   {0x00, 0x48, 0xA8, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* space                */ { 160,   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* exclamdown           */ { 161,   {0x00, 0x20, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00 }},
/* cent                 */ { 162,   {0x00, 0x00, 0x20, 0x78, 0xA0, 0xA0, 0xA0, 0x78, 0x20, 0x00 }},
/* sterling             */ { 163,   {0x00, 0x30, 0x48, 0x40, 0xE0, 0x40, 0x48, 0xB0, 0x00, 0x00 }},
/* currency             */ { 164,   {0x00, 0x00, 0x00, 0x88, 0x70, 0x50, 0x70, 0x88, 0x00, 0x00 }},
/* yen                  */ { 165,   {0x00, 0x88, 0x88, 0x50, 0x20, 0xF8, 0x20, 0x20, 0x20, 0x00 }},
/* brokenbar            */ { 166,   {0x00, 0x20, 0x20, 0x20, 0x00, 0x20, 0x20, 0x20, 0x00, 0x00 }},
/* section              */ { 167,   {0x00, 0x70, 0x80, 0xE0, 0x90, 0x48, 0x38, 0x08, 0x70, 0x00 }},
/* dieresis             */ { 168,   {0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* copyright            */ { 169,   {0x00, 0x70, 0x88, 0xA8, 0xC8, 0xA8, 0x88, 0x70, 0x00, 0x00 }},
/* ordfeminine          */ { 170,   {0x00, 0x38, 0x48, 0x58, 0x28, 0x00, 0x78, 0x00, 0x00, 0x00 }},
/* guillemotleft        */ { 171,   {0x00, 0x00, 0x00, 0x24, 0x48, 0x90, 0x48, 0x24, 0x00, 0x00 }},
/* logicalnot           */ { 172,   {0x00, 0x00, 0x00, 0x00, 0x78, 0x08, 0x00, 0x00, 0x00, 0x00 }},
/* hyphen               */ { 173,   {0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* registered           */ { 174,   {0x00, 0x70, 0x88, 0xE8, 0xC8, 0xC8, 0x88, 0x70, 0x00, 0x00 }},
/* macron               */ { 175,   {0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* degree               */ { 176,   {0x00, 0x20, 0x50, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* plusminus            */ { 177,   {0x00, 0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0xF8, 0x00, 0x00 }},
/* twosuperior          */ { 178,   {0x30, 0x48, 0x10, 0x20, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* threesuperior        */ { 179,   {0x70, 0x08, 0x30, 0x08, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* acute                */ { 180,   {0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* mu                   */ { 181,   {0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0xC8, 0xB0, 0x80, 0x00 }},
/* paragraph            */ { 182,   {0x00, 0x78, 0xE8, 0xE8, 0x68, 0x28, 0x28, 0x28, 0x00, 0x00 }},
/* periodcentered       */ { 183,   {0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* cedilla              */ { 184,   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20 }},
/* onesuperior          */ { 185,   {0x20, 0x60, 0x20, 0x20, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00 }},
/* ordmasculine         */ { 186,   {0x00, 0x30, 0x48, 0x48, 0x30, 0x00, 0x78, 0x00, 0x00, 0x00 }},
/* guillemotright       */ { 187,   {0x00, 0x00, 0x00, 0x90, 0x48, 0x24, 0x48, 0x90, 0x00, 0x00 }},
/* onequarter           */ { 188,   {0x40, 0xC0, 0x40, 0x40, 0xE4, 0x0C, 0x14, 0x3C, 0x04, 0x00 }},
/* onehalf              */ { 189,   {0x40, 0xC0, 0x40, 0x40, 0xE8, 0x14, 0x04, 0x08, 0x1C, 0x00 }},
/* threequarters        */ { 190,   {0xC0, 0x20, 0x40, 0x20, 0xC8, 0x18, 0x28, 0x78, 0x08, 0x00 }},
/* questiondown         */ { 191,   {0x00, 0x20, 0x00, 0x20, 0x20, 0x40, 0x88, 0x70, 0x00, 0x00 }},
/* Agrave               */ { 192,   {0x40, 0x20, 0x70, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00, 0x00 }},
/* Aacute               */ { 193,   {0x10, 0x20, 0x70, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00, 0x00 }},
/* Acircumflex          */ { 194,   {0x20, 0x50, 0x70, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00, 0x00 }},
/* Atilde               */ { 195,   {0x48, 0xB0, 0x70, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00, 0x00 }},
/* Adieresis            */ { 196,   {0x50, 0x00, 0x70, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00, 0x00 }},
/* Aring                */ { 197,   {0x20, 0x50, 0x70, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00, 0x00 }},
/* AE                   */ { 198,   {0x00, 0x3C, 0x50, 0x90, 0x9C, 0xF0, 0x90, 0x9C, 0x00, 0x00 }},
/* Ccedilla             */ { 199,   {0x00, 0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70, 0x20, 0x40 }},
/* Egrave               */ { 200,   {0x40, 0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8, 0x00, 0x00 }},
/* Eacute               */ { 201,   {0x10, 0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8, 0x00, 0x00 }},
/* Ecircumflex          */ { 202,   {0x20, 0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8, 0x00, 0x00 }},
/* Edieresis            */ { 203,   {0x50, 0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8, 0x00, 0x00 }},
/* Igrave               */ { 204,   {0x40, 0x20, 0x70, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00 }},
/* Iacute               */ { 205,   {0x10, 0x20, 0x70, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00 }},
/* Icircumflex          */ { 206,   {0x20, 0x50, 0x70, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00 }},
/* Idieresis            */ { 207,   {0x50, 0x00, 0x70, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00 }},
/* Eth                  */ { 208,   {0x00, 0xF0, 0x48, 0x48, 0xE8, 0x48, 0x48, 0xF0, 0x00, 0x00 }},
/* Ntilde               */ { 209,   {0x28, 0x50, 0x88, 0xC8, 0xA8, 0x98, 0x88, 0x88, 0x00, 0x00 }},
/* Ograve               */ { 210,   {0x40, 0x20, 0x70, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* Oacute               */ { 211,   {0x10, 0x20, 0x70, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* Ocircumflex          */ { 212,   {0x20, 0x50, 0x70, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* Otilde               */ { 213,   {0x28, 0x50, 0x70, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* Odieresis            */ { 214,   {0x50, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* multiply             */ { 215,   {0x00, 0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, 0x00, 0x00 }},
/* Oslash               */ { 216,   {0x00, 0x70, 0x98, 0x98, 0xA8, 0xC8, 0xC8, 0x70, 0x00, 0x00 }},
/* Ugrave               */ { 217,   {0x40, 0x20, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* Uacute               */ { 218,   {0x10, 0x20, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* Ucircumflex          */ { 219,   {0x20, 0x50, 0x00, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* Udieresis            */ { 220,   {0x50, 0x00, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* Yacute               */ { 221,   {0x10, 0x20, 0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x00, 0x00 }},
/* Thorn                */ { 222,   {0x00, 0x80, 0xF0, 0x88, 0xF0, 0x80, 0x80, 0x80, 0x00, 0x00 }},
/* germandbls           */ { 223,   {0x00, 0x70, 0x88, 0x90, 0xA0, 0x90, 0x88, 0xB0, 0x00, 0x00 }},
/* agrave               */ { 224,   {0x40, 0x20, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00, 0x00 }},
/* aacute               */ { 225,   {0x10, 0x20, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00, 0x00 }},
/* acircumflex          */ { 226,   {0x20, 0x50, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00, 0x00 }},
/* atilde               */ { 227,   {0x28, 0x50, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00, 0x00 }},
/* adieresis            */ { 228,   {0x00, 0x50, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00, 0x00 }},
/* aring                */ { 229,   {0x20, 0x50, 0x20, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00, 0x00 }},
/* ae                   */ { 230,   {0x00, 0x00, 0x00, 0x78, 0x14, 0x7C, 0x90, 0x7C, 0x00, 0x00 }},
/* ccedilla             */ { 231,   {0x00, 0x00, 0x00, 0x70, 0x88, 0x80, 0x88, 0x70, 0x20, 0x40 }},
/* egrave               */ { 232,   {0x40, 0x20, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x70, 0x00, 0x00 }},
/* eacute               */ { 233,   {0x10, 0x20, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x70, 0x00, 0x00 }},
/* ecircumflex          */ { 234,   {0x20, 0x50, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x70, 0x00, 0x00 }},
/* edieresis            */ { 235,   {0x00, 0x50, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x70, 0x00, 0x00 }},
/* igrave               */ { 236,   {0x40, 0x20, 0x00, 0x60, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00 }},
/* iacute               */ { 237,   {0x20, 0x40, 0x00, 0x60, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00 }},
/* icircumflex          */ { 238,   {0x20, 0x50, 0x00, 0x60, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00 }},
/* idieresis            */ { 239,   {0x00, 0x50, 0x00, 0x60, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00 }},
/* eth                  */ { 240,   {0x00, 0xC0, 0x30, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* ntilde               */ { 241,   {0x28, 0x50, 0x00, 0xB0, 0xC8, 0x88, 0x88, 0x88, 0x00, 0x00 }},
/* ograve               */ { 242,   {0x40, 0x20, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* oacute               */ { 243,   {0x10, 0x20, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* ocircumflex          */ { 244,   {0x20, 0x50, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* otilde               */ { 245,   {0x28, 0x50, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* odieresis            */ { 246,   {0x00, 0x50, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00 }},
/* divide               */ { 247,   {0x00, 0x00, 0x20, 0x00, 0xF8, 0x00, 0x20, 0x00, 0x00, 0x00 }},
/* oslash               */ { 248,   {0x00, 0x00, 0x00, 0x78, 0x98, 0xA8, 0xC8, 0xF0, 0x00, 0x00 }},
/* ugrave               */ { 249,   {0x40, 0x20, 0x00, 0x88, 0x88, 0x88, 0x98, 0x68, 0x00, 0x00 }},
/* uacute               */ { 250,   {0x10, 0x20, 0x00, 0x88, 0x88, 0x88, 0x98, 0x68, 0x00, 0x00 }},
/* ucircumflex          */ { 251,   {0x20, 0x50, 0x00, 0x88, 0x88, 0x88, 0x98, 0x68, 0x00, 0x00 }},
/* udieresis            */ { 252,   {0x00, 0x50, 0x00, 0x88, 0x88, 0x88, 0x98, 0x68, 0x00, 0x00 }},
/* yacute               */ { 253,   {0x00, 0x10, 0x20, 0x88, 0x88, 0x98, 0x68, 0x08, 0x88, 0x70 }},
/* thorn                */ { 254,   {0x00, 0x00, 0x80, 0xF0, 0x88, 0x88, 0x88, 0xF0, 0x80, 0x80 }},
/* ydieresis            */ { 255,   {0x00, 0x50, 0x00, 0x88, 0x88, 0x98, 0x68, 0x08, 0x88, 0x70 }},
/* char0                */ { 0,     {0x00, 0xA8, 0x00, 0x88, 0x00, 0x88, 0x00, 0xA8, 0x00, 0x00 }}
};

void alto2_cpu_device::fake_status_putch(int x, UINT8 ch)
{
	const bdf_6x10_t* pf = bdf_6x10;
	while (pf->code != ch && pf->code != 0)
		pf++;
	int dx = 6 * x;
	if (dx >= ALTO2_DISPLAY_WIDTH)
		return;
	for (int dy = 0; dy < 10; dy++)
	{
		UINT8* pix = m_dsp.scanline[ALTO2_DISPLAY_HEIGHT + 1 + dy] + dx;
		UINT8 bits = ~pf->bits[dy];
		pix[0] = (bits >> 7) & 1;
		pix[1] = (bits >> 6) & 1;
		pix[2] = (bits >> 5) & 1;
		pix[3] = (bits >> 4) & 1;
		pix[4] = (bits >> 3) & 1;
		pix[5] = (bits >> 2) & 1;
	}

}

void alto2_cpu_device::fake_status_printf(int x, const char* format, ...)
{
	static char buff[256];
	va_list ap;
	va_start(ap, format);
	vsnprintf(buff, sizeof(buff), format, ap);
	va_end(ap);
	char* src = buff;
	while (*src)
		fake_status_putch(x++, *src++);
=======
void alto2_cpu_device::screen_vblank()
{
	m_dsp.vblank = true;
>>>>>>> upstream/master
}
