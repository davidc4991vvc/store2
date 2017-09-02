// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    SMC CRT9007 CRT Video Processor and Controller (VPAC) emulation

**********************************************************************/

/*

    TODO:

    - cursor timer
    - interrupts
        - light pen
        - frame timer
    - non-DMA mode
    - DMA mode
    - cursor/blank skew
    - sequential breaks
    - interlaced mode
    - smooth scroll
    - page blank
    - double height cursor
    - row attributes
    - pin configuration
    - operation modes 0,4,7
    - address modes 1,2,3
    - light pen
    - state saving

*/

#include "emu.h"
#include "crt9007.h"

<<<<<<< HEAD
=======
#include "screen.h"

//#define VERBOSE 1
#include "logmacro.h"

>>>>>>> upstream/master


//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type CRT9007 = &device_creator<crt9007_t>;
=======
DEFINE_DEVICE_TYPE(CRT9007, crt9007_device, "crt9007", "SMC SRT9007 VPAC")
>>>>>>> upstream/master



//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

<<<<<<< HEAD
#define LOG 0

=======
>>>>>>> upstream/master
#define HAS_VALID_PARAMETERS \
	(m_reg[0x00] && m_reg[0x01] && m_reg[0x07] && m_reg[0x08] && m_reg[0x09])

#define CHARACTERS_PER_HORIZONTAL_PERIOD \
	m_reg[0x00]

#define CHARACTERS_PER_DATA_ROW \
	(m_reg[0x01] + 1)

#define HORIZONTAL_DELAY \
	m_reg[0x02]

#define HORIZONTAL_SYNC_WIDTH \
	m_reg[0x03]

#define VERTICAL_SYNC_WIDTH \
	m_reg[0x04]

#define VERTICAL_DELAY \
	(m_reg[0x05] - 1)

#define PIN_CONFIGURATION \
	(m_reg[0x06] >> 6)

#define CURSOR_SKEW \
	((m_reg[0x06] >> 3) & 0x07)

#define BLANK_SKEW \
	(m_reg[0x06] & 0x07)

#define VISIBLE_DATA_ROWS_PER_FRAME \
	(m_reg[0x07] + 1)

#define SCAN_LINES_PER_DATA_ROW \
	((m_reg[0x08] & 0x1f) + 1)

#define SCAN_LINES_PER_FRAME \
	(((m_reg[0x08] << 3) & 0x0700) | m_reg[0x09])

#define DMA_BURST_COUNT \
	((m_reg[0x0a] & 0x0f) + 1)

#define DMA_BURST_DELAY \
	((((m_reg[0x0a] >> 4) & 0x07) + 1) % 8)

#define DMA_DISABLE \
	BIT(m_reg[0x0a], 7)

#define SINGLE_HEIGHT_CURSOR \
	BIT(m_reg[0x0b], 0)

#define OPERATION_MODE \
	((m_reg[0x0b] >> 1) & 0x07)

#define INTERLACE_MODE \
	((m_reg[0x0b] >> 4) & 0x03)

#define PAGE_BLANK \
	BIT(m_reg[0x0b], 6)

#define TABLE_START \
	(((m_reg[0x0d] << 8) & 0x3f00) | m_reg[0x0c])

#define ADDRESS_MODE \
	((m_reg[0x0d] >> 6) & 0x03)

#define AUXILIARY_ADDRESS_1 \
	(((m_reg[0x0f] << 8) & 0x3f00) | m_reg[0x0e])

#define ROW_ATTRIBUTES_1 \
	((m_reg[0x0f] >> 6) & 0x03)

#define SEQUENTIAL_BREAK_1 \
	m_reg[0x10]

#define SEQUENTIAL_BREAK_2 \
	m_reg[0x12]

#define DATA_ROW_START \
	m_reg[0x11]

#define DATA_ROW_END \
	m_reg[0x12]

#define AUXILIARY_ADDRESS_2 \
	(((m_reg[0x14] << 8) & 0x3f00) | m_reg[0x13])

#define ROW_ATTRIBUTES_2 \
	((m_reg[0x14] >> 6) & 0x03)

#define SMOOTH_SCROLL_OFFSET \
	((m_reg[0x17] >> 1) & 0x3f)

#define SMOOTH_SCROLL_OFFSET_OVERFLOW \
	BIT(m_reg[0x17], 7)

#define VERTICAL_CURSOR \
	m_reg[0x18]

#define HORIZONTAL_CURSOR \
	m_reg[0x19]

#define INTERRUPT_ENABLE \
	m_reg[0x1a]

#define FRAME_TIMER \
	BIT(m_reg[0x1a], 0)

#define LIGHT_PEN_INTERRUPT \
	BIT(m_reg[0x1a], 5)

#define VERTICAL_RETRACE_INTERRUPT \
	BIT(m_reg[0x1a], 6)

#define VERTICAL_LIGHT_PEN \
	m_reg[0x3b]

#define HORIZONTAL_LIGHT_PEN \
	m_reg[0x3c]


// interlace
enum
{
	NON_INTERLACED = 0,
	ENHANCED_VIDEO_INTERFACE,
	NORMAL_VIDEO_INTERFACE
};


// operation modes
enum
{
	OPERATION_MODE_REPETITIVE_MEMORY_ADDRESSING = 0,    // not implemented
	OPERATION_MODE_DOUBLE_ROW_BUFFER = 1,
	OPERATION_MODE_SINGLE_ROW_BUFFER = 4,               // not implemented
	OPERATION_MODE_ATTRIBUTE_ASSEMBLE = 7               // not implemented
};


// addressing modes
enum
{
	ADDRESS_MODE_SEQUENTIAL_ADDRESSING = 0,
	ADDRESS_MODE_SEQUENTIAL_ROLL_ADDRESSING,            // not implemented
	ADDRESS_MODE_CONTIGUOUS_ROW_TABLE,                  // not implemented
	ADDRESS_MODE_LINKED_LIST_ROW_TABLE                  // not implemented
};


// interrupt enable register bits
const int IE_VERTICAL_RETRACE           = 0x40;
//const int IE_LIGHT_PEN                  = 0x20;
//const int IE_FRAME_TIMER                = 0x01;

// status register bits
const int STATUS_INTERRUPT_PENDING      = 0x80;
//const int STATUS_VERTICAL_RETRACE       = 0x40;
const int STATUS_LIGHT_PEN_UPDATE       = 0x20;
//const int STATUS_ODD_EVEN               = 0x04;
//const int STATUS_FRAME_TIMER_OCCURRED   = 0x01;



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

// default address map
<<<<<<< HEAD
static ADDRESS_MAP_START( crt9007, AS_0, 8, crt9007_t )
=======
static ADDRESS_MAP_START( crt9007, 0, 8, crt9007_device )
>>>>>>> upstream/master
	AM_RANGE(0x0000, 0x3fff) AM_RAM
ADDRESS_MAP_END



//**************************************************************************
//  INLINE HELPERS
//**************************************************************************

//-------------------------------------------------
//  readbyte - read a byte at the given address
//-------------------------------------------------

<<<<<<< HEAD
inline UINT8 crt9007_t::readbyte(offs_t address)
=======
inline uint8_t crt9007_device::readbyte(offs_t address)
>>>>>>> upstream/master
{
	return space().read_byte(address);
}


//-------------------------------------------------
//  trigger_interrupt -
//-------------------------------------------------

<<<<<<< HEAD
inline void crt9007_t::trigger_interrupt(int line)
=======
inline void crt9007_device::trigger_interrupt(int line)
>>>>>>> upstream/master
{
	if (INTERRUPT_ENABLE & line)
	{
		int status = m_status;

		m_status |= STATUS_INTERRUPT_PENDING | line;

		if (!(status & STATUS_INTERRUPT_PENDING))
		{
<<<<<<< HEAD
			if (LOG) logerror("CRT9007 '%s' INT 1\n", tag());
=======
			LOG("CRT9007 INT 1\n");
>>>>>>> upstream/master
			m_write_int(ASSERT_LINE);
		}
	}
}


//-------------------------------------------------
//  update_cblank_line -
//-------------------------------------------------

<<<<<<< HEAD
inline void crt9007_t::update_cblank_line()
=======
inline void crt9007_device::update_cblank_line()
>>>>>>> upstream/master
{
	int x = m_screen->hpos();
	int y = m_screen->vpos();

	// composite blank
	int cblank = !(m_hs & m_vs);

	if (m_cblank != cblank)
	{
		m_cblank = cblank;

<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' y %03u x %04u : CBLANK %u\n", tag(), y, x, m_cblank);
=======
		LOG("CRT9007 y %03u x %04u : CBLANK %u\n", y, x, m_cblank);
>>>>>>> upstream/master

		m_write_cblank(m_cblank);
	}
}


//-------------------------------------------------
//  update_hsync_timer -
//-------------------------------------------------

<<<<<<< HEAD
inline void crt9007_t::update_hsync_timer(int state)
=======
inline void crt9007_device::update_hsync_timer(int state)
>>>>>>> upstream/master
{
	int y = m_screen->vpos();

	int next_x = state ? m_hsync_start : m_hsync_end;
	int next_y = state ? (y + 1) % SCAN_LINES_PER_FRAME : y;

	attotime duration = m_screen->time_until_pos(next_y, next_x);

	m_hsync_timer->adjust(duration, !state);
}


//-------------------------------------------------
//  update_vsync_timer -
//-------------------------------------------------

<<<<<<< HEAD
inline void crt9007_t::update_vsync_timer(int state)
=======
inline void crt9007_device::update_vsync_timer(int state)
>>>>>>> upstream/master
{
	int next_y = state ? m_vsync_start : m_vsync_end;

	attotime duration = m_screen->time_until_pos(next_y, 0);

	m_vsync_timer->adjust(duration, !state);
}


//-------------------------------------------------
//  update_vlt_timer -
//-------------------------------------------------

<<<<<<< HEAD
inline void crt9007_t::update_vlt_timer(int state)
=======
inline void crt9007_device::update_vlt_timer(int state)
>>>>>>> upstream/master
{
	// this signal is active during all visible scan lines and during the horizontal trace at vertical retrace
	int y = m_screen->vpos();

	int next_x = state ? m_vlt_end : m_vlt_start;
	int next_y = state ? y : ((y == m_vlt_bottom) ? 0 : (y + 1));

	attotime duration = m_screen->time_until_pos(next_y, next_x);

	m_vlt_timer->adjust(duration, !state);
}


//-------------------------------------------------
//  update_curs_timer -
//-------------------------------------------------

<<<<<<< HEAD
inline void crt9007_t::update_curs_timer(int state)
=======
inline void crt9007_device::update_curs_timer(int state)
>>>>>>> upstream/master
{
	// this signal is active for 1 character time for all scanlines within the data row
	// TODO
}


//-------------------------------------------------
//  update_drb_timer -
//-------------------------------------------------

<<<<<<< HEAD
inline void crt9007_t::update_drb_timer(int state)
=======
inline void crt9007_device::update_drb_timer(int state)
>>>>>>> upstream/master
{
	// this signal is active for 1 full scan line (VLT edge to edge) at the top scan line of each new row
	// there is 1 extra DRB signal during the 1st scanline of the vertical retrace interval
	int y = m_screen->vpos();

	int next_x = m_vlt_end;
	int next_y = y ? y + 1 : y;

	if (state)
	{
		if (y == 0)
		{
			next_y = VERTICAL_DELAY - 1;
		}
		else if (y == m_drb_bottom)
		{
			next_x = 0;
			next_y = 0;
		}
		else
		{
			next_y = y + SCAN_LINES_PER_DATA_ROW - 1;
		}
	}

	attotime duration = m_screen->time_until_pos(next_y, next_x);

	m_drb_timer->adjust(duration, !state);
}


//-------------------------------------------------
//  update_dma_timer -
//-------------------------------------------------

<<<<<<< HEAD
inline void crt9007_t::update_dma_timer()
=======
inline void crt9007_device::update_dma_timer()
>>>>>>> upstream/master
{
	// TODO
}


//-------------------------------------------------
//  recompute_parameters -
//-------------------------------------------------

<<<<<<< HEAD
inline void crt9007_t::recompute_parameters()
=======
inline void crt9007_device::recompute_parameters()
>>>>>>> upstream/master
{
	// check that necessary registers have been loaded
	if (!HAS_VALID_PARAMETERS) return;

	// screen dimensions
	//int horiz_pix_total = CHARACTERS_PER_HORIZONTAL_PERIOD * m_hpixels_per_column;
	//int vert_pix_total = SCAN_LINES_PER_FRAME;

	// refresh rate
	//attoseconds_t refresh = HZ_TO_ATTOSECONDS(clock()) * horiz_pix_total * vert_pix_total;

	// horizontal sync
	m_hsync_start = 0;
	m_hsync_end = HORIZONTAL_SYNC_WIDTH * m_hpixels_per_column;

	// visible line time
	m_vlt_start = HORIZONTAL_DELAY * m_hpixels_per_column;
	m_vlt_end = (HORIZONTAL_DELAY + CHARACTERS_PER_DATA_ROW) * m_hpixels_per_column;
	m_vlt_bottom = VERTICAL_DELAY + (VISIBLE_DATA_ROWS_PER_FRAME * SCAN_LINES_PER_DATA_ROW) - 1;

	// data row boundary
	m_drb_bottom = VERTICAL_DELAY + (VISIBLE_DATA_ROWS_PER_FRAME * SCAN_LINES_PER_DATA_ROW) - SCAN_LINES_PER_DATA_ROW;

	// vertical sync
	m_vsync_start = 0;
	m_vsync_end = VERTICAL_SYNC_WIDTH;

	// visible area
	//rectangle visarea;

	//visarea.set(m_hsync_end, horiz_pix_total - 1, m_vsync_end, vert_pix_total - 1);

<<<<<<< HEAD
	//if (LOG)
	//{
	//  logerror("CRT9007 '%s' Screen: %u x %u @ %f Hz\n", tag(), horiz_pix_total, vert_pix_total, 1 / ATTOSECONDS_TO_DOUBLE(refresh));
	//  logerror("CRT9007 '%s' Visible Area: (%u, %u) - (%u, %u)\n", tag(), visarea.min_x, visarea.min_y, visarea.max_x, visarea.max_y);
	//}
=======
	//LOG("CRT9007 Screen: %u x %u @ %f Hz\n", horiz_pix_total, vert_pix_total, 1 / ATTOSECONDS_TO_DOUBLE(refresh));
	//LOG("CRT9007 Visible Area: (%u, %u) - (%u, %u)\n", visarea.min_x, visarea.min_y, visarea.max_x, visarea.max_y);
>>>>>>> upstream/master

	//m_screen->configure(horiz_pix_total, vert_pix_total, visarea, refresh);

	m_hsync_timer->adjust(m_screen->time_until_pos(0, 0));
	m_vsync_timer->adjust(m_screen->time_until_pos(0, 0));
	m_vlt_timer->adjust(m_screen->time_until_pos(0, m_vlt_start), 1);
	m_drb_timer->adjust(m_screen->time_until_pos(0, 0));
}


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  crt9007_t - constructor
//-------------------------------------------------

crt9007_t::crt9007_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, CRT9007, "SMC CRT9007", tag, owner, clock, "crt9007", __FILE__),
	device_memory_interface(mconfig, *this),
	device_video_interface(mconfig, *this),
	m_space_config("videoram", ENDIANNESS_LITTLE, 8, 14, 0, NULL, *ADDRESS_MAP_NAME(crt9007)),
=======
//  crt9007_device - constructor
//-------------------------------------------------

crt9007_device::crt9007_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, CRT9007, tag, owner, clock),
	device_memory_interface(mconfig, *this),
	device_video_interface(mconfig, *this),
	m_space_config("videoram", ENDIANNESS_LITTLE, 8, 14, 0, nullptr, *ADDRESS_MAP_NAME(crt9007)),
>>>>>>> upstream/master
	m_write_int(*this),
	m_write_dmar(*this),
	m_write_hs(*this),
	m_write_vs(*this),
	m_write_vlt(*this),
	m_write_curs(*this),
	m_write_drb(*this),
	m_write_wben(*this),
	m_write_cblank(*this),
	m_write_slg(*this),
	m_write_sld(*this)
{
<<<<<<< HEAD
	for (int i = 0; i < 0x3d; i++)
		m_reg[i] = 0;
=======
	for (auto & elem : m_reg)
		elem = 0;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void crt9007_t::device_start()
=======
void crt9007_device::device_start()
>>>>>>> upstream/master
{
	// allocate timers
	m_hsync_timer = timer_alloc(TIMER_HSYNC);
	m_vsync_timer = timer_alloc(TIMER_VSYNC);
	m_vlt_timer = timer_alloc(TIMER_VLT);
	m_curs_timer = timer_alloc(TIMER_CURS);
	m_drb_timer = timer_alloc(TIMER_DRB);
	m_dma_timer = timer_alloc(TIMER_DMA);

	// resolve callbacks
	m_write_int.resolve_safe();
	m_write_dmar.resolve_safe();
	m_write_hs.resolve_safe();
	m_write_vs.resolve_safe();
	m_write_vlt.resolve_safe();
	m_write_curs.resolve_safe();
	m_write_drb.resolve_safe();
	m_write_wben.resolve_safe();
	m_write_cblank.resolve_safe();
	m_write_slg.resolve_safe();
	m_write_sld.resolve_safe();
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void crt9007_t::device_reset()
=======
void crt9007_device::device_reset()
>>>>>>> upstream/master
{
	m_disp = 0;
	m_vs = 0;
	m_cblank = 0;

	// HS = 1
	m_write_hs(1);

	// VS = 1
	m_write_vs(1);

	// CBLANK = 1
	m_write_cblank(0);

	// CURS = 0
	m_write_curs(0);

	// VLT = 0
	m_write_vlt(0);

	// DRB = 1
	m_write_drb(1);

	// INT = 0
	m_write_int(CLEAR_LINE);

	// 28 (DMAR) = 0
	m_write_dmar(CLEAR_LINE);

	// 29 (WBEN) = 0
	m_write_wben(1); // HACK

	// 30 (SLG) = 0
	m_write_slg(0);

	// 31 (SLD) = 0
	m_write_sld(0);

	// 32 (LPSTB) = 0
}


//-------------------------------------------------
//  device_clock_changed - handle clock change
//-------------------------------------------------

<<<<<<< HEAD
void crt9007_t::device_clock_changed()
=======
void crt9007_device::device_clock_changed()
>>>>>>> upstream/master
{
	recompute_parameters();
}


//-------------------------------------------------
//  device_timer - handle timer events
//-------------------------------------------------

<<<<<<< HEAD
void crt9007_t::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
=======
void crt9007_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
>>>>>>> upstream/master
{
	int x = m_screen->hpos();
	int y = m_screen->vpos();

	switch (id)
	{
	case TIMER_HSYNC:
		m_hs = param;

<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' y %03u x %04u : HS %u\n", tag(), y, x, m_hs);
=======
		LOG("CRT9007 y %03u x %04u : HS %u\n", y, x, m_hs);
>>>>>>> upstream/master

		m_write_hs(m_hs);

		update_cblank_line();

		update_hsync_timer(param);
		break;

	case TIMER_VSYNC:
		m_vs = param;

<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' y %03u x %04u : VS %u\n", tag(), y, x, m_vs);
=======
		LOG("CRT9007 y %03u x %04u : VS %u\n", y, x, m_vs);
>>>>>>> upstream/master

		m_write_vs(param);

		if (m_vs)
		{
			// reset all other bits except Light Pen Update to logic 0
			m_status &= STATUS_LIGHT_PEN_UPDATE;
		}
		else
		{
			trigger_interrupt(IE_VERTICAL_RETRACE);

			update_cblank_line();
		}

		update_vsync_timer(param);
		break;

	case TIMER_VLT:
		m_vlt = param;

<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' y %03u x %04u : VLT %u\n", tag(), y, x, m_vlt);
=======
		LOG("CRT9007 y %03u x %04u : VLT %u\n", y, x, m_vlt);
>>>>>>> upstream/master

		m_write_vlt(param);

		update_vlt_timer(param);
		break;

	case TIMER_CURS:
<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' y %03u x %04u : CURS %u\n", tag(), y, x, param);
=======
		LOG("CRT9007 y %03u x %04u : CURS %u\n", y, x, param);
>>>>>>> upstream/master

		m_write_curs(param);

		update_curs_timer(param);
		break;

	case TIMER_DRB:
		m_drb = param;

<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' y %03u x %04u : DRB %u\n", tag(), y, x, m_drb);
=======
		LOG("CRT9007 y %03u x %04u : DRB %u\n", y, x, m_drb);
>>>>>>> upstream/master

		m_write_drb(param);

		if (!m_drb && !DMA_DISABLE)
		{
			// start DMA burst sequence
			m_dma_count = CHARACTERS_PER_DATA_ROW;
			m_dma_burst = DMA_BURST_COUNT ? (DMA_BURST_COUNT * 4) : CHARACTERS_PER_DATA_ROW;
			m_dma_delay = DMA_BURST_DELAY;
			m_dmar = 1;

<<<<<<< HEAD
			if (LOG) logerror("CRT9007 '%s' DMAR 1\n", tag());
=======
			LOG("CRT9007 DMAR 1\n");
>>>>>>> upstream/master
			m_write_dmar(ASSERT_LINE);
		}

		update_drb_timer(param);
		break;

	case TIMER_DMA:
		readbyte(AUXILIARY_ADDRESS_2);

		update_dma_timer();
		break;
	}
}


//-------------------------------------------------
//  memory_space_config - return a description of
//  any address spaces owned by this device
//-------------------------------------------------

<<<<<<< HEAD
const address_space_config *crt9007_t::memory_space_config(address_spacenum spacenum) const
{
	return (spacenum == AS_0) ? &m_space_config : NULL;
=======
device_memory_interface::space_config_vector crt9007_device::memory_space_config() const
{
	return space_config_vector {
		std::make_pair(0, &m_space_config)
	};
>>>>>>> upstream/master
}


//-------------------------------------------------
//  read - register read
//-------------------------------------------------

<<<<<<< HEAD
READ8_MEMBER( crt9007_t::read )
{
	UINT8 data = 0;
=======
READ8_MEMBER( crt9007_device::read )
{
	uint8_t data = 0;
>>>>>>> upstream/master

	switch (offset)
	{
	case 0x15:
<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' Start\n", tag());
=======
		LOG("CRT9007 Start\n");
>>>>>>> upstream/master
		m_disp = 1;
		break;

	case 0x16:
<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' Reset\n", tag());
=======
		LOG("CRT9007 Reset\n");
>>>>>>> upstream/master
		device_reset();
		break;

	case 0x38:
		data = VERTICAL_CURSOR;
		break;

	case 0x39:
		data = HORIZONTAL_CURSOR;
		break;

	case 0x3a:
		data = m_status;

		// reset interrupt pending bit
		m_status &= ~STATUS_INTERRUPT_PENDING;
<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' INT 0\n", tag());
=======
		LOG("CRT9007 INT 0\n");
>>>>>>> upstream/master
		m_write_int(CLEAR_LINE);
		break;

	case 0x3b:
		data = VERTICAL_LIGHT_PEN;
		break;

	case 0x3c:
		data = HORIZONTAL_LIGHT_PEN;

		// reset light pen update bit
		m_status &= ~STATUS_LIGHT_PEN_UPDATE;
		break;

	default:
<<<<<<< HEAD
		logerror("CRT9007 '%s' Read from Invalid Register: %02x!\n", tag(), offset);
=======
		logerror("CRT9007 Read from Invalid Register: %02x!\n", offset);
>>>>>>> upstream/master
	}

	return data;
}


//-------------------------------------------------
//  write - register write
//-------------------------------------------------

<<<<<<< HEAD
WRITE8_MEMBER( crt9007_t::write )
=======
WRITE8_MEMBER( crt9007_device::write )
>>>>>>> upstream/master
{
	m_reg[offset] = data;

	switch (offset)
	{
	case 0x00:
		recompute_parameters();
<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' Characters per Horizontal Period: %u\n", tag(), CHARACTERS_PER_HORIZONTAL_PERIOD);
=======
		LOG("CRT9007 Characters per Horizontal Period: %u\n", CHARACTERS_PER_HORIZONTAL_PERIOD);
>>>>>>> upstream/master
		break;

	case 0x01:
		recompute_parameters();
<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' Characters per Data Row: %u\n", tag(), CHARACTERS_PER_DATA_ROW);
=======
		LOG("CRT9007 Characters per Data Row: %u\n", CHARACTERS_PER_DATA_ROW);
>>>>>>> upstream/master
		break;

	case 0x02:
		recompute_parameters();
<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' Horizontal Delay: %u\n", tag(), HORIZONTAL_DELAY);
=======
		LOG("CRT9007 Horizontal Delay: %u\n", HORIZONTAL_DELAY);
>>>>>>> upstream/master
		break;

	case 0x03:
		recompute_parameters();
<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' Horizontal Sync Width: %u\n", tag(), HORIZONTAL_SYNC_WIDTH);
=======
		LOG("CRT9007 Horizontal Sync Width: %u\n", HORIZONTAL_SYNC_WIDTH);
>>>>>>> upstream/master
		break;

	case 0x04:
		recompute_parameters();
<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' Vertical Sync Width: %u\n", tag(), VERTICAL_SYNC_WIDTH);
=======
		LOG("CRT9007 Vertical Sync Width: %u\n", VERTICAL_SYNC_WIDTH);
>>>>>>> upstream/master
		break;

	case 0x05:
		recompute_parameters();
<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' Vertical Delay: %u\n", tag(), VERTICAL_DELAY);
=======
		LOG("CRT9007 Vertical Delay: %u\n", VERTICAL_DELAY);
>>>>>>> upstream/master
		break;

	case 0x06:
		recompute_parameters();
<<<<<<< HEAD
		if (LOG)
		{
			logerror("CRT9007 '%s' Pin Configuration: %u\n", tag(), PIN_CONFIGURATION);
			logerror("CRT9007 '%s' Cursor Skew: %u\n", tag(), CURSOR_SKEW);
			logerror("CRT9007 '%s' Blank Skew: %u\n", tag(), BLANK_SKEW);
		}
=======
		LOG("CRT9007 Pin Configuration: %u\n", PIN_CONFIGURATION);
		LOG("CRT9007 Cursor Skew: %u\n", CURSOR_SKEW);
		LOG("CRT9007 Blank Skew: %u\n", BLANK_SKEW);
>>>>>>> upstream/master
		break;

	case 0x07:
		recompute_parameters();
<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' Visible Data Rows per Frame: %u\n", tag(), VISIBLE_DATA_ROWS_PER_FRAME);
=======
		LOG("CRT9007 Visible Data Rows per Frame: %u\n", VISIBLE_DATA_ROWS_PER_FRAME);
>>>>>>> upstream/master
		break;

	case 0x08:
		recompute_parameters();
<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' Scan Lines per Data Row: %u\n", tag(), SCAN_LINES_PER_DATA_ROW);
=======
		LOG("CRT9007 Scan Lines per Data Row: %u\n", SCAN_LINES_PER_DATA_ROW);
>>>>>>> upstream/master
		break;

	case 0x09:
		recompute_parameters();
<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' Scan Lines per Frame: %u\n", tag(), SCAN_LINES_PER_FRAME);
		break;

	case 0x0a:
		if (LOG)
		{
			logerror("CRT9007 '%s' DMA Burst Count: %u\n", tag(), DMA_BURST_COUNT);
			logerror("CRT9007 '%s' DMA Burst Delay: %u\n", tag(), DMA_BURST_DELAY);
			logerror("CRT9007 '%s' DMA Disable: %u\n", tag(), DMA_DISABLE);
		}
		break;

	case 0x0b:
		if (LOG)
		{
			logerror("CRT9007 '%s' %s Height Cursor\n", tag(), SINGLE_HEIGHT_CURSOR ? "Single" : "Double");
			logerror("CRT9007 '%s' Operation Mode: %u\n", tag(), OPERATION_MODE);
			logerror("CRT9007 '%s' Interlace Mode: %u\n", tag(), INTERLACE_MODE);
			logerror("CRT9007 '%s' %s Mechanism\n", tag(), PAGE_BLANK ? "Page Blank" : "Smooth Scroll");
		}
=======
		LOG("CRT9007 Scan Lines per Frame: %u\n", SCAN_LINES_PER_FRAME);
		break;

	case 0x0a:
		LOG("CRT9007 DMA Burst Count: %u\n", DMA_BURST_COUNT);
		LOG("CRT9007 DMA Burst Delay: %u\n", DMA_BURST_DELAY);
		LOG("CRT9007 DMA Disable: %u\n", DMA_DISABLE);
		break;

	case 0x0b:
		LOG("CRT9007 %s Height Cursor\n", SINGLE_HEIGHT_CURSOR ? "Single" : "Double");
		LOG("CRT9007 Operation Mode: %u\n", OPERATION_MODE);
		LOG("CRT9007 Interlace Mode: %u\n", INTERLACE_MODE);
		LOG("CRT9007 %s Mechanism\n", PAGE_BLANK ? "Page Blank" : "Smooth Scroll");
>>>>>>> upstream/master
		break;

	case 0x0c:
		break;

	case 0x0d:
<<<<<<< HEAD
		if (LOG)
		{
			logerror("CRT9007 '%s' Table Start Register: %04x\n", tag(), TABLE_START);
			logerror("CRT9007 '%s' Address Mode: %u\n", tag(), ADDRESS_MODE);
		}
=======
		LOG("CRT9007 Table Start Register: %04x\n", TABLE_START);
		LOG("CRT9007 Address Mode: %u\n", ADDRESS_MODE);
>>>>>>> upstream/master
		break;

	case 0x0e:
		break;

	case 0x0f:
<<<<<<< HEAD
		if (LOG)
		{
			logerror("CRT9007 '%s' Auxialiary Address Register 1: %04x\n", tag(), AUXILIARY_ADDRESS_1);
			logerror("CRT9007 '%s' Row Attributes: %u\n", tag(), ROW_ATTRIBUTES_1);
		}
		break;

	case 0x10:
		if (LOG) logerror("CRT9007 '%s' Sequential Break Register 1: %u\n", tag(), SEQUENTIAL_BREAK_1);
		break;

	case 0x11:
		if (LOG) logerror("CRT9007 '%s' Data Row Start Register: %u\n", tag(), DATA_ROW_START);
		break;

	case 0x12:
		if (LOG) logerror("CRT9007 '%s' Data Row End/Sequential Break Register 2: %u\n", tag(), SEQUENTIAL_BREAK_2);
=======
		LOG("CRT9007 Auxialiary Address Register 1: %04x\n", AUXILIARY_ADDRESS_1);
		LOG("CRT9007 Row Attributes: %u\n", ROW_ATTRIBUTES_1);
		break;

	case 0x10:
		LOG("CRT9007 Sequential Break Register 1: %u\n", SEQUENTIAL_BREAK_1);
		break;

	case 0x11:
		LOG("CRT9007 Data Row Start Register: %u\n", DATA_ROW_START);
		break;

	case 0x12:
		LOG("CRT9007 Data Row End/Sequential Break Register 2: %u\n", SEQUENTIAL_BREAK_2);
>>>>>>> upstream/master
		break;

	case 0x13:
		break;

	case 0x14:
<<<<<<< HEAD
		if (LOG)
		{
			logerror("CRT9007 '%s' Auxiliary Address Register 2: %04x\n", tag(), AUXILIARY_ADDRESS_2);
			logerror("CRT9007 '%s' Row Attributes: %u\n", tag(), ROW_ATTRIBUTES_2);
		}
		break;

	case 0x15:
		if (LOG) logerror("CRT9007 '%s' Start\n", tag());
=======
		LOG("CRT9007 Auxiliary Address Register 2: %04x\n", AUXILIARY_ADDRESS_2);
		LOG("CRT9007 Row Attributes: %u\n", ROW_ATTRIBUTES_2);
		break;

	case 0x15:
		LOG("CRT9007 Start\n");
>>>>>>> upstream/master
		m_disp = 1;
		break;

	case 0x16:
<<<<<<< HEAD
		if (LOG) logerror("CRT9007 '%s' Reset\n", tag());
=======
		LOG("CRT9007 Reset\n");
>>>>>>> upstream/master
		device_reset();
		break;

	case 0x17:
<<<<<<< HEAD
		if (LOG)
		{
			logerror("CRT9007 '%s' Smooth Scroll Offset: %u\n", tag(), SMOOTH_SCROLL_OFFSET);
			logerror("CRT9007 '%s' Smooth Scroll Offset Overflow: %u\n", tag(), SMOOTH_SCROLL_OFFSET_OVERFLOW);
		}
		break;

	case 0x18:
		if (LOG) logerror("CRT9007 '%s' Vertical Cursor Register: %u\n", tag(), VERTICAL_CURSOR);
		break;

	case 0x19:
		if (LOG) logerror("CRT9007 '%s' Horizontal Cursor Register: %u\n", tag(), HORIZONTAL_CURSOR);
		break;

	case 0x1a:
		if (LOG)
		{
			logerror("CRT9007 '%s' Frame Timer: %u\n", tag(), FRAME_TIMER);
			logerror("CRT9007 '%s' Light Pen Interrupt: %u\n", tag(), LIGHT_PEN_INTERRUPT);
			logerror("CRT9007 '%s' Vertical Retrace Interrupt: %u\n", tag(), VERTICAL_RETRACE_INTERRUPT);
		}
		break;

	default:
		logerror("CRT9007 '%s' Write to Invalid Register: %02x!\n", tag(), offset);
=======
		LOG("CRT9007 Smooth Scroll Offset: %u\n", SMOOTH_SCROLL_OFFSET);
		LOG("CRT9007 Smooth Scroll Offset Overflow: %u\n", SMOOTH_SCROLL_OFFSET_OVERFLOW);
		break;

	case 0x18:
		LOG("CRT9007 Vertical Cursor Register: %u\n", VERTICAL_CURSOR);
		break;

	case 0x19:
		LOG("CRT9007 Horizontal Cursor Register: %u\n", HORIZONTAL_CURSOR);
		break;

	case 0x1a:
		LOG("CRT9007 Frame Timer: %u\n", FRAME_TIMER);
		LOG("CRT9007 Light Pen Interrupt: %u\n", LIGHT_PEN_INTERRUPT);
		LOG("CRT9007 Vertical Retrace Interrupt: %u\n", VERTICAL_RETRACE_INTERRUPT);
		break;

	default:
		logerror("CRT9007 Write to Invalid Register: %02x!\n", offset);
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  ack_w - DMA acknowledge
//-------------------------------------------------

<<<<<<< HEAD
WRITE_LINE_MEMBER( crt9007_t::ack_w )
{
	if (LOG) logerror("CRT9007 '%s' ACK: %u\n", tag(), state);
=======
WRITE_LINE_MEMBER( crt9007_device::ack_w )
{
	LOG("CRT9007 ACK: %u\n", state);
>>>>>>> upstream/master

	if (m_dmar && !m_ack && state)
	{
		// start DMA transfer
		m_dma_timer->adjust(attotime::from_hz(clock()));
	}

	m_ack = state;
}


//-------------------------------------------------
//  lpstb_w - light pen strobe
//-------------------------------------------------

<<<<<<< HEAD
WRITE_LINE_MEMBER( crt9007_t::lpstb_w )
{
	if (LOG) logerror("CRT9007 '%s' LPSTB: %u\n", tag(), state);
=======
WRITE_LINE_MEMBER( crt9007_device::lpstb_w )
{
	LOG("CRT9007 LPSTB: %u\n", state);
>>>>>>> upstream/master

	if (!m_lpstb && state)
	{
		// TODO latch current row/column position
	}

	m_lpstb = state;
}


//-------------------------------------------------
//  set_character_width -
//-------------------------------------------------

<<<<<<< HEAD
void crt9007_t::set_character_width(int value)
=======
void crt9007_device::set_character_width(int value)
>>>>>>> upstream/master
{
	m_hpixels_per_column = value;

	recompute_parameters();
}
