// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria, Aaron Giles
/*********************************************************************

    drawgfx.c

    Generic graphic functions.
*********************************************************************/

#include "emu.h"
#include "drawgfxm.h"


/***************************************************************************
    GLOBAL VARIABLES
***************************************************************************/

// if this line errors during compile, the size of NO_PRIORITY is wrong and I need to use something else
<<<<<<< HEAD
UINT8 no_priority_size_is_wrong[2 * (sizeof(NO_PRIORITY) == 3) - 1];
=======
u8 no_priority_size_is_wrong[2 * (sizeof(NO_PRIORITY) == 3) - 1];
>>>>>>> upstream/master

bitmap_ind8 drawgfx_dummy_priority_bitmap;



/***************************************************************************
    INLINE FUNCTIONS
***************************************************************************/

/*-------------------------------------------------
    readbit - read a single bit from a base
    offset
-------------------------------------------------*/

<<<<<<< HEAD
static inline int readbit(const UINT8 *src, unsigned int bitnum)
=======
static inline int readbit(const u8 *src, unsigned int bitnum)
>>>>>>> upstream/master
{
	return src[bitnum / 8] & (0x80 >> (bitnum % 8));
}


/*-------------------------------------------------
    normalize_xscroll - normalize an X scroll
    value for a bitmap to be positive and less
    than the width
-------------------------------------------------*/

<<<<<<< HEAD
static inline INT32 normalize_xscroll(bitmap_t &bitmap, INT32 xscroll)
=======
static inline s32 normalize_xscroll(const bitmap_t &bitmap, s32 xscroll)
>>>>>>> upstream/master
{
	return (xscroll >= 0) ? xscroll % bitmap.width() : (bitmap.width() - (-xscroll) % bitmap.width());
}


/*-------------------------------------------------
    normalize_yscroll - normalize a Y scroll
    value for a bitmap to be positive and less
    than the height
-------------------------------------------------*/

<<<<<<< HEAD
static inline INT32 normalize_yscroll(bitmap_t &bitmap, INT32 yscroll)
=======
static inline s32 normalize_yscroll(const bitmap_t &bitmap, s32 yscroll)
>>>>>>> upstream/master
{
	return (yscroll >= 0) ? yscroll % bitmap.height() : (bitmap.height() - (-yscroll) % bitmap.height());
}



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type GFXDECODE = &device_creator<gfxdecode_device>;

gfxdecode_device::gfxdecode_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, GFXDECODE, "gfxdecode", tag, owner, clock, "gfxdecode", __FILE__),
=======
DEFINE_DEVICE_TYPE(GFXDECODE, gfxdecode_device, "gfxdecode", "gfxdecode")

gfxdecode_device::gfxdecode_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock) :
	device_t(mconfig, GFXDECODE, tag, owner, clock),
>>>>>>> upstream/master
	device_gfx_interface(mconfig, *this)
{
}




/***************************************************************************
    GRAPHICS ELEMENTS
***************************************************************************/


//-------------------------------------------------
//  gfx_element - constructor
//-------------------------------------------------

<<<<<<< HEAD
gfx_element::gfx_element()
	: m_palette(NULL),
		m_width(0),
		m_height(0),
		m_startx(0),
		m_starty(0),
		m_origwidth(0),
		m_origheight(0),
		m_total_elements(0),
		m_color_base(0),
		m_color_depth(0),
		m_color_granularity(0),
		m_total_colors(0),
		m_line_modulo(0),
		m_char_modulo(0),
		m_srcdata(NULL),
		m_dirtyseq(1),
		m_gfxdata(NULL),
		m_layout_is_raw(false),
		m_layout_planes(0),
		m_layout_xormask(0),
		m_layout_charincrement(0)
{
}

gfx_element::gfx_element(palette_device *palette, UINT8 *base, UINT32 width, UINT32 height, UINT32 rowbytes, UINT32 total_colors, UINT32 color_base, UINT32 color_granularity)
=======
gfx_element::gfx_element(device_palette_interface *palette, u8 *base, u16 width, u16 height, u32 rowbytes, u32 total_colors, u32 color_base, u32 color_granularity)
>>>>>>> upstream/master
	: m_palette(palette),
		m_width(width),
		m_height(height),
		m_startx(0),
		m_starty(0),
		m_origwidth(width),
		m_origheight(height),
		m_total_elements(1),
		m_color_base(color_base),
		m_color_depth(color_granularity),
		m_color_granularity(color_granularity),
		m_total_colors((total_colors - color_base) / color_granularity),
		m_line_modulo(rowbytes),
		m_char_modulo(0),
		m_srcdata(base),
		m_dirtyseq(1),
		m_gfxdata(base),
		m_layout_is_raw(true),
		m_layout_planes(0),
		m_layout_xormask(0),
		m_layout_charincrement(0)
{
}

<<<<<<< HEAD
gfx_element::gfx_element(palette_device *palette, const gfx_layout &gl, const UINT8 *srcdata, UINT32 xormask, UINT32 total_colors, UINT32 color_base)
=======
gfx_element::gfx_element(device_palette_interface *palette, const gfx_layout &gl, const u8 *srcdata, u32 xormask, u32 total_colors, u32 color_base)
>>>>>>> upstream/master
	: m_palette(palette),
		m_width(0),
		m_height(0),
		m_startx(0),
		m_starty(0),
		m_origwidth(0),
		m_origheight(0),
		m_total_elements(0),
		m_color_base(color_base),
		m_color_depth(0),
		m_color_granularity(0),
		m_total_colors(total_colors),
		m_line_modulo(0),
		m_char_modulo(0),
<<<<<<< HEAD
		m_srcdata(NULL),
		m_dirtyseq(1),
		m_gfxdata(NULL),
=======
		m_srcdata(nullptr),
		m_dirtyseq(1),
		m_gfxdata(nullptr),
>>>>>>> upstream/master
		m_layout_is_raw(false),
		m_layout_planes(0),
		m_layout_xormask(xormask),
		m_layout_charincrement(0)
{
	// set the layout
	set_layout(gl, srcdata);
}


//-------------------------------------------------
//  set_layout - set the layout for a gfx_element
//-------------------------------------------------

<<<<<<< HEAD
void gfx_element::set_layout(const gfx_layout &gl, const UINT8 *srcdata)
=======
void gfx_element::set_layout(const gfx_layout &gl, const u8 *srcdata)
>>>>>>> upstream/master
{
	m_srcdata = srcdata;

	// configure ourselves
	m_width = m_origwidth = gl.width;
	m_height = m_origheight = gl.height;
	m_startx = m_starty = 0;
	m_total_elements = gl.total;
	m_color_depth = m_color_granularity = 1 << gl.planes;

	// copy data from the layout
	m_layout_is_raw = (gl.planeoffset[0] == GFX_RAW);
	m_layout_planes = gl.planes;
	m_layout_charincrement = gl.charincrement;

	// raw graphics case
	if (m_layout_is_raw)
	{
		// RAW layouts don't need these arrays
		m_layout_planeoffset.clear();
		m_layout_xoffset.clear();
		m_layout_yoffset.clear();
		m_gfxdata_allocated.clear();

		// modulos are determined for us by the layout
		m_line_modulo = gl.yoffs(0) / 8;
		m_char_modulo = gl.charincrement / 8;

		// RAW graphics must have a pointer up front
<<<<<<< HEAD
		assert(srcdata != NULL);
		m_gfxdata = const_cast<UINT8 *>(srcdata);
=======
		assert(srcdata != nullptr);
		m_gfxdata = const_cast<u8 *>(srcdata);
>>>>>>> upstream/master
	}

	// decoded graphics case
	else
	{
		// copy offsets
		m_layout_planeoffset.resize(m_layout_planes);
		m_layout_xoffset.resize(m_width);
		m_layout_yoffset.resize(m_height);

		for (int p = 0; p < m_layout_planes; p++)
			m_layout_planeoffset[p] = gl.planeoffset[p];
		for (int y = 0; y < m_height; y++)
			m_layout_yoffset[y] = gl.yoffs(y);
		for (int x = 0; x < m_width; x++)
			m_layout_xoffset[x] = gl.xoffs(x);

		// we get to pick our own modulos
		m_line_modulo = m_origwidth;
		m_char_modulo = m_line_modulo * m_origheight;

		// allocate memory for the data
		m_gfxdata_allocated.resize(m_total_elements * m_char_modulo);
		m_gfxdata = &m_gfxdata_allocated[0];
	}

	// mark everything dirty
	m_dirty.resize(m_total_elements);
	memset(&m_dirty[0], 1, m_total_elements);

	// allocate a pen usage array for entries with 32 pens or less
	if (m_color_depth <= 32)
		m_pen_usage.resize(m_total_elements);
	else
		m_pen_usage.clear();
}


//-------------------------------------------------
//  set_raw_layout - set the layout for a gfx_element
//-------------------------------------------------

<<<<<<< HEAD
void gfx_element::set_raw_layout(const UINT8 *srcdata, UINT32 width, UINT32 height, UINT32 total, UINT32 linemod, UINT32 charmod)
=======
void gfx_element::set_raw_layout(const u8 *srcdata, u32 width, u32 height, u32 total, u32 linemod, u32 charmod)
>>>>>>> upstream/master
{
	gfx_layout layout = { 0 };
	layout.width = width;
	layout.height = height;
	layout.total = total;
	layout.planes = 8;
	layout.planeoffset[0] = GFX_RAW;
	layout.yoffset[0] = linemod;
	layout.charincrement = charmod;
	set_layout(layout, srcdata);
}


//-------------------------------------------------
// set_source - set the source data for a gfx_element
//-------------------------------------------------

<<<<<<< HEAD
void gfx_element::set_source(const UINT8 *source)
{
	m_srcdata = source;
	memset(&m_dirty[0], 1, elements());
	if (m_layout_is_raw) m_gfxdata = const_cast<UINT8 *>(source);
=======
void gfx_element::set_source(const u8 *source)
{
	m_srcdata = source;
	memset(&m_dirty[0], 1, elements());
	if (m_layout_is_raw) m_gfxdata = const_cast<u8 *>(source);
>>>>>>> upstream/master
}


//-------------------------------------------------
// set_source_and_total - set the source data
// and total elements for a gfx_element
//-------------------------------------------------

<<<<<<< HEAD
void gfx_element::set_source_and_total(const UINT8 *source, UINT32 total)
=======
void gfx_element::set_source_and_total(const u8 *source, u32 total)
>>>>>>> upstream/master
{
	m_srcdata = source;
	m_total_elements = total;

	// mark everything dirty
	m_dirty.resize(m_total_elements);
	memset(&m_dirty[0], 1, m_total_elements);

	// allocate a pen usage array for entries with 32 pens or less
	if (m_color_depth <= 32)
		m_pen_usage.resize(m_total_elements);

	if (m_layout_is_raw)
	{
<<<<<<< HEAD
		m_gfxdata = const_cast<UINT8 *>(source);
=======
		m_gfxdata = const_cast<u8 *>(source);
>>>>>>> upstream/master
	}
	else
	{
		// allocate memory for the data
		m_gfxdata_allocated.resize(m_total_elements * m_char_modulo);
		m_gfxdata = &m_gfxdata_allocated[0];
	}
}


//-------------------------------------------------
//  set_source_clip - set a source clipping rect
//-------------------------------------------------

<<<<<<< HEAD
void gfx_element::set_source_clip(UINT32 xoffs, UINT32 width, UINT32 yoffs, UINT32 height)
=======
void gfx_element::set_source_clip(u32 xoffs, u32 width, u32 yoffs, u32 height)
>>>>>>> upstream/master
{
	assert(xoffs < m_origwidth);
	assert(yoffs < m_origheight);
	assert(xoffs + width <= m_origwidth);
	assert(yoffs + height <= m_origheight);

	m_width = width;
	m_height = height;
	m_startx = xoffs;
	m_starty = yoffs;
}


//-------------------------------------------------
//  decode - decode a single character
//-------------------------------------------------

<<<<<<< HEAD
void gfx_element::decode(UINT32 code)
=======
void gfx_element::decode(u32 code)
>>>>>>> upstream/master
{
	// don't decode GFX_RAW
	if (!m_layout_is_raw)
	{
		// zap the data to 0
<<<<<<< HEAD
		UINT8 *decode_base = m_gfxdata + code * m_char_modulo;
=======
		u8 *decode_base = m_gfxdata + code * m_char_modulo;
>>>>>>> upstream/master
		memset(decode_base, 0, m_char_modulo);

		// iterate over planes
		int plane, planebit;
		for (plane = 0, planebit = 1 << (m_layout_planes - 1);
				plane < m_layout_planes;
				plane++, planebit >>= 1)
		{
			int planeoffs = code * m_layout_charincrement + m_layout_planeoffset[plane];

			// iterate over rows
			for (int y = 0; y < m_origheight; y++)
			{
				int yoffs = planeoffs + m_layout_yoffset[y];
<<<<<<< HEAD
				UINT8 *dp = decode_base + y * m_line_modulo;
=======
				u8 *dp = decode_base + y * m_line_modulo;
>>>>>>> upstream/master

				// iterate over columns
				for (int x = 0; x < m_origwidth; x++)
					if (readbit(m_srcdata, (yoffs + m_layout_xoffset[x]) ^ m_layout_xormask))
						dp[x] |= planebit;
			}
		}
	}

	// (re)compute pen usage
	if (code < m_pen_usage.size())
	{
		// iterate over data, creating a bitmask of live pens
<<<<<<< HEAD
		const UINT8 *dp = m_gfxdata + code * m_char_modulo;
		UINT32 usage = 0;
=======
		const u8 *dp = m_gfxdata + code * m_char_modulo;
		u32 usage = 0;
>>>>>>> upstream/master
		for (int y = 0; y < m_origheight; y++)
		{
			for (int x = 0; x < m_origwidth; x++)
				usage |= 1 << dp[x];
			dp += m_line_modulo;
		}

		// store the final result
		m_pen_usage[code] = usage;
	}

	// no longer dirty
	m_dirty[code] = 0;
}



/***************************************************************************
    DRAWGFX IMPLEMENTATIONS
***************************************************************************/

/*-------------------------------------------------
    opaque - render a gfx element with
    no transparency
-------------------------------------------------*/

void gfx_element::opaque(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty)
>>>>>>> upstream/master
{
	color = colorbase() + granularity() * (color % colors());
	code %= elements();
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFX_CORE(UINT16, PIXEL_OP_REBASE_OPAQUE, NO_PRIORITY);
}

void gfx_element::opaque(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty)
=======
	DRAWGFX_CORE(u16, PIXEL_OP_REBASE_OPAQUE, NO_PRIORITY);
}

void gfx_element::opaque(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty)
>>>>>>> upstream/master
{
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
	code %= elements();
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFX_CORE(UINT32, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);
=======
	DRAWGFX_CORE(u32, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    transpen - render a gfx element with
    a single transparent pen
-------------------------------------------------*/

void gfx_element::transpen(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 trans_pen)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 trans_pen)
>>>>>>> upstream/master
{
	// special case invalid pens to opaque
	if (trans_pen > 0xff)
		return opaque(dest, cliprect, code, color, flipx, flipy, destx, desty);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~(1 << trans_pen)) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & (1 << trans_pen)) == 0)
			return opaque(dest, cliprect, code, color, flipx, flipy, destx, desty);
	}

	// render
	color = colorbase() + granularity() * (color % colors());
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFX_CORE(UINT16, PIXEL_OP_REBASE_TRANSPEN, NO_PRIORITY);
}

void gfx_element::transpen(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 trans_pen)
=======
	DRAWGFX_CORE(u16, PIXEL_OP_REBASE_TRANSPEN, NO_PRIORITY);
}

void gfx_element::transpen(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 trans_pen)
>>>>>>> upstream/master
{
	// special case invalid pens to opaque
	if (trans_pen > 0xff)
		return opaque(dest, cliprect, code, color, flipx, flipy, destx, desty);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~(1 << trans_pen)) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & (1 << trans_pen)) == 0)
			return opaque(dest, cliprect, code, color, flipx, flipy, destx, desty);
	}

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFX_CORE(UINT32, PIXEL_OP_REMAP_TRANSPEN, NO_PRIORITY);
=======
	DRAWGFX_CORE(u32, PIXEL_OP_REMAP_TRANSPEN, NO_PRIORITY);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    transpen_raw - render a gfx element
    with a single transparent pen and no color
    lookups
-------------------------------------------------*/

void gfx_element::transpen_raw(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 trans_pen)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 trans_pen)
>>>>>>> upstream/master
{
	// early out if completely transparent
	code %= elements();
	if (has_pen_usage() && (pen_usage(code) & ~(1 << trans_pen)) == 0)
		return;

	// render
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFX_CORE(UINT16, PIXEL_OP_REBASE_TRANSPEN, NO_PRIORITY);
}

void gfx_element::transpen_raw(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 trans_pen)
=======
	DRAWGFX_CORE(u16, PIXEL_OP_REBASE_TRANSPEN, NO_PRIORITY);
}

void gfx_element::transpen_raw(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 trans_pen)
>>>>>>> upstream/master
{
	// early out if completely transparent
	code %= elements();
	if (has_pen_usage() && (pen_usage(code) & ~(1 << trans_pen)) == 0)
		return;

	// render
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFX_CORE(UINT32, PIXEL_OP_REBASE_TRANSPEN, NO_PRIORITY);
=======
	DRAWGFX_CORE(u32, PIXEL_OP_REBASE_TRANSPEN, NO_PRIORITY);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    transmask - render a gfx element
    with a multiple transparent pens provided as
    a mask
-------------------------------------------------*/

void gfx_element::transmask(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 trans_mask)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 trans_mask)
>>>>>>> upstream/master
{
	// special case 0 mask to opaque
	if (trans_mask == 0)
		return opaque(dest, cliprect, code, color, flipx, flipy, destx, desty);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~trans_mask) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & trans_mask) == 0)
			return opaque(dest, cliprect, code, color, flipx, flipy, destx, desty);
	}

	// render
	color = colorbase() + granularity() * (color % colors());
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFX_CORE(UINT16, PIXEL_OP_REBASE_TRANSMASK, NO_PRIORITY);
}

void gfx_element::transmask(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 trans_mask)
=======
	DRAWGFX_CORE(u16, PIXEL_OP_REBASE_TRANSMASK, NO_PRIORITY);
}

void gfx_element::transmask(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 trans_mask)
>>>>>>> upstream/master
{
	// special case 0 mask to opaque
	if (trans_mask == 0)
		return opaque(dest, cliprect, code, color, flipx, flipy, destx, desty);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~trans_mask) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & trans_mask) == 0)
			return opaque(dest, cliprect, code, color, flipx, flipy, destx, desty);
	}

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFX_CORE(UINT32, PIXEL_OP_REMAP_TRANSMASK, NO_PRIORITY);
=======
	DRAWGFX_CORE(u32, PIXEL_OP_REMAP_TRANSMASK, NO_PRIORITY);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    transtable - render a gfx element
    using a table to look up which pens are
    transparent, opaque, or shadowing
-------------------------------------------------*/

void gfx_element::transtable(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		const UINT8 *pentable)
{
	assert(pentable != NULL);
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		const u8 *pentable)
{
	assert(pentable != nullptr);
>>>>>>> upstream/master

	// render
	color = colorbase() + granularity() * (color % colors());
	const pen_t *shadowtable = m_palette->shadow_table();
	code %= elements();
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFX_CORE(UINT16, PIXEL_OP_REBASE_TRANSTABLE16, NO_PRIORITY);
}

void gfx_element::transtable(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		const UINT8 *pentable)
{
	assert(pentable != NULL);
=======
	DRAWGFX_CORE(u16, PIXEL_OP_REBASE_TRANSTABLE16, NO_PRIORITY);
}

void gfx_element::transtable(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		const u8 *pentable)
{
	assert(pentable != nullptr);
>>>>>>> upstream/master

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
	const pen_t *shadowtable = m_palette->shadow_table();
	code %= elements();
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFX_CORE(UINT32, PIXEL_OP_REMAP_TRANSTABLE32, NO_PRIORITY);
=======
	DRAWGFX_CORE(u32, PIXEL_OP_REMAP_TRANSTABLE32, NO_PRIORITY);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    alpha - render a gfx element with
    a single transparent pen, alpha blending the
    remaining pixels with a fixed alpha value
-------------------------------------------------*/

void gfx_element::alpha(bitmap_rgb32 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 trans_pen, UINT8 alpha_val)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 trans_pen, u8 alpha_val)
>>>>>>> upstream/master
{
	// special case alpha = 0xff
	if (alpha_val == 0xff)
		return transpen(dest, cliprect, code, color, flipx, flipy, destx, desty, trans_pen);

	// early out if completely transparent
	code %= elements();
	if (has_pen_usage() && (pen_usage(code) & ~(1 << trans_pen)) == 0)
		return;

	// get final code and color, and grab lookup tables
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFX_CORE(UINT32, PIXEL_OP_REMAP_TRANSPEN_ALPHA32, NO_PRIORITY);
=======
	DRAWGFX_CORE(u32, PIXEL_OP_REMAP_TRANSPEN_ALPHA32, NO_PRIORITY);
>>>>>>> upstream/master
}



/***************************************************************************
    DRAWGFXZOOM IMPLEMENTATIONS
***************************************************************************/

/*-------------------------------------------------
    zoom_opaque - render a scaled gfx
    element with no transparency
-------------------------------------------------*/

void gfx_element::zoom_opaque(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return opaque(dest, cliprect, code, color, flipx, flipy, destx, desty);

	// render
	color = colorbase() + granularity() * (color % colors());
	code %= elements();
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT16, PIXEL_OP_REBASE_OPAQUE, NO_PRIORITY);
}

void gfx_element::zoom_opaque(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley)
=======
	DRAWGFXZOOM_CORE(u16, PIXEL_OP_REBASE_OPAQUE, NO_PRIORITY);
}

void gfx_element::zoom_opaque(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return opaque(dest, cliprect, code, color, flipx, flipy, destx, desty);

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
	code %= elements();
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT32, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);
=======
	DRAWGFXZOOM_CORE(u32, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    zoom_transpen - render a scaled gfx
    element with a single transparent pen
-------------------------------------------------*/

void gfx_element::zoom_transpen(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, UINT32 trans_pen)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, u32 trans_pen)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return transpen(dest, cliprect, code, color, flipx, flipy, destx, desty, trans_pen);

	// special case invalid pens to opaque
	if (trans_pen > 0xff)
		return zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~(1 << trans_pen)) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & (1 << trans_pen)) == 0)
			return zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley);
	}

	// render
	color = colorbase() + granularity() * (color % colors());
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT16, PIXEL_OP_REBASE_TRANSPEN, NO_PRIORITY);
}

void gfx_element::zoom_transpen(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, UINT32 trans_pen)
=======
	DRAWGFXZOOM_CORE(u16, PIXEL_OP_REBASE_TRANSPEN, NO_PRIORITY);
}

void gfx_element::zoom_transpen(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, u32 trans_pen)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return transpen(dest, cliprect, code, color, flipx, flipy, destx, desty, trans_pen);

	// special case invalid pens to opaque
	if (trans_pen > 0xff)
		return zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~(1 << trans_pen)) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & (1 << trans_pen)) == 0)
			return zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley);
	}

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT32, PIXEL_OP_REMAP_TRANSPEN, NO_PRIORITY);
=======
	DRAWGFXZOOM_CORE(u32, PIXEL_OP_REMAP_TRANSPEN, NO_PRIORITY);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    zoom_transpen_raw - render a scaled gfx
    element with a single transparent pen and no
    color lookups
-------------------------------------------------*/

void gfx_element::zoom_transpen_raw(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, UINT32 trans_pen)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, u32 trans_pen)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return transpen_raw(dest, cliprect, code, color, flipx, flipy, destx, desty, trans_pen);

	// early out if completely transparent
	code %= elements();
	if (has_pen_usage() && (pen_usage(code) & ~(1 << trans_pen)) == 0)
		return;

	// render
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT16, PIXEL_OP_REBASE_TRANSPEN, NO_PRIORITY);
}

void gfx_element::zoom_transpen_raw(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, UINT32 trans_pen)
=======
	DRAWGFXZOOM_CORE(u16, PIXEL_OP_REBASE_TRANSPEN, NO_PRIORITY);
}

void gfx_element::zoom_transpen_raw(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, u32 trans_pen)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return transpen_raw(dest, cliprect, code, color, flipx, flipy, destx, desty, trans_pen);

	// early out if completely transparent
	code %= elements();
	if (has_pen_usage() && (pen_usage(code) & ~(1 << trans_pen)) == 0)
		return;

	// render
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT32, PIXEL_OP_REBASE_TRANSPEN, NO_PRIORITY);
=======
	DRAWGFXZOOM_CORE(u32, PIXEL_OP_REBASE_TRANSPEN, NO_PRIORITY);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    zoom_transmask - render a scaled gfx
    element with a multiple transparent pens
    provided as a mask
-------------------------------------------------*/

void gfx_element::zoom_transmask(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, UINT32 trans_mask)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, u32 trans_mask)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return transmask(dest, cliprect, code, color, flipx, flipy, destx, desty, trans_mask);

	// special case 0 mask to opaque
	if (trans_mask == 0)
		return zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~trans_mask) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & trans_mask) == 0)
			return zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley);
	}

	// render
	color = colorbase() + granularity() * (color % colors());
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT16, PIXEL_OP_REBASE_TRANSMASK, NO_PRIORITY);
}

void gfx_element::zoom_transmask(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, UINT32 trans_mask)
=======
	DRAWGFXZOOM_CORE(u16, PIXEL_OP_REBASE_TRANSMASK, NO_PRIORITY);
}

void gfx_element::zoom_transmask(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, u32 trans_mask)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return transmask(dest, cliprect, code, color, flipx, flipy, destx, desty, trans_mask);

	// special case 0 mask to opaque
	if (trans_mask == 0)
		return zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~trans_mask) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & trans_mask) == 0)
			return zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley);
	}

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT32, PIXEL_OP_REMAP_TRANSMASK, NO_PRIORITY);
=======
	DRAWGFXZOOM_CORE(u32, PIXEL_OP_REMAP_TRANSMASK, NO_PRIORITY);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    zoom_transtable - render a scaled gfx
    element using a table to look up which pens
    are transparent, opaque, or shadowing
-------------------------------------------------*/

void gfx_element::zoom_transtable(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, const UINT8 *pentable)
{
	assert(pentable != NULL);
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, const u8 *pentable)
{
	assert(pentable != nullptr);
>>>>>>> upstream/master

	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return transtable(dest, cliprect, code, color, flipx, flipy, destx, desty, pentable);

	// render
	color = colorbase() + granularity() * (color % colors());
	const pen_t *shadowtable = m_palette->shadow_table();
	code %= elements();
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT16, PIXEL_OP_REBASE_TRANSTABLE16, NO_PRIORITY);
}

void gfx_element::zoom_transtable(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, const UINT8 *pentable)
{
	assert(pentable != NULL);
=======
	DRAWGFXZOOM_CORE(u16, PIXEL_OP_REBASE_TRANSTABLE16, NO_PRIORITY);
}

void gfx_element::zoom_transtable(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, const u8 *pentable)
{
	assert(pentable != nullptr);
>>>>>>> upstream/master

	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return transtable(dest, cliprect, code, color, flipx, flipy, destx, desty, pentable);

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
	const pen_t *shadowtable = m_palette->shadow_table();
	code %= elements();
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT32, PIXEL_OP_REMAP_TRANSTABLE32, NO_PRIORITY);
=======
	DRAWGFXZOOM_CORE(u32, PIXEL_OP_REMAP_TRANSTABLE32, NO_PRIORITY);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    zoom_alpha - render a scaled gfx element
    with a single transparent pen, alpha blending
    the remaining pixels with a fixed alpha value
-------------------------------------------------*/

void gfx_element::zoom_alpha(bitmap_rgb32 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, UINT32 trans_pen, UINT8 alpha_val)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, u32 trans_pen, u8 alpha_val)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return alpha(dest, cliprect, code, color, flipx, flipy, destx, desty, trans_pen, alpha_val);

	// special case alpha_val = 0xff
	if (alpha_val == 0xff)
		return zoom_transpen(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley, trans_pen);

	// early out if completely transparent
	code %= elements();
	if (has_pen_usage() && (pen_usage(code) & ~(1 << trans_pen)) == 0)
		return;

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
	DECLARE_NO_PRIORITY;
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT32, PIXEL_OP_REMAP_TRANSPEN_ALPHA32, NO_PRIORITY);
=======
	DRAWGFXZOOM_CORE(u32, PIXEL_OP_REMAP_TRANSPEN_ALPHA32, NO_PRIORITY);
>>>>>>> upstream/master
}



/***************************************************************************
    PDRAWGFX IMPLEMENTATIONS
***************************************************************************/

/*-------------------------------------------------
    prio_opaque - render a gfx element with
    no transparency, checking against the priority
    bitmap
-------------------------------------------------*/

void gfx_element::prio_opaque(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		bitmap_ind8 &priority, UINT32 pmask)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		bitmap_ind8 &priority, u32 pmask)
>>>>>>> upstream/master
{
	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	color = colorbase() + granularity() * (color % colors());
	code %= elements();
<<<<<<< HEAD
	DRAWGFX_CORE(UINT16, PIXEL_OP_REBASE_OPAQUE_PRIORITY, UINT8);
}

void gfx_element::prio_opaque(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		bitmap_ind8 &priority, UINT32 pmask)
=======
	DRAWGFX_CORE(u16, PIXEL_OP_REBASE_OPAQUE_PRIORITY, u8);
}

void gfx_element::prio_opaque(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		bitmap_ind8 &priority, u32 pmask)
>>>>>>> upstream/master
{
	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
	code %= elements();
<<<<<<< HEAD
	DRAWGFX_CORE(UINT32, PIXEL_OP_REMAP_OPAQUE_PRIORITY, UINT8);
=======
	DRAWGFX_CORE(u32, PIXEL_OP_REMAP_OPAQUE_PRIORITY, u8);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    prio_transpen - render a gfx element with
    a single transparent pen, checking against the
    priority bitmap
-------------------------------------------------*/

void gfx_element::prio_transpen(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		bitmap_ind8 &priority, UINT32 pmask, UINT32 trans_pen)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		bitmap_ind8 &priority, u32 pmask, u32 trans_pen)
>>>>>>> upstream/master
{
	// special case invalid pens to opaque
	if (trans_pen > 0xff)
		return prio_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~(1 << trans_pen)) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & (1 << trans_pen)) == 0)
			return prio_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask);
	}

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	color = colorbase() + granularity() * (color % colors());
<<<<<<< HEAD
	DRAWGFX_CORE(UINT16, PIXEL_OP_REBASE_TRANSPEN_PRIORITY, UINT8);
}

void gfx_element::prio_transpen(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		bitmap_ind8 &priority, UINT32 pmask, UINT32 trans_pen)
=======
	DRAWGFX_CORE(u16, PIXEL_OP_REBASE_TRANSPEN_PRIORITY, u8);
}

void gfx_element::prio_transpen(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		bitmap_ind8 &priority, u32 pmask, u32 trans_pen)
>>>>>>> upstream/master
{
	// special case invalid pens to opaque
	if (trans_pen > 0xff)
		return prio_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~(1 << trans_pen)) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & (1 << trans_pen)) == 0)
			return prio_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask);
	}

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
<<<<<<< HEAD
	DRAWGFX_CORE(UINT32, PIXEL_OP_REMAP_TRANSPEN_PRIORITY, UINT8);
=======
	DRAWGFX_CORE(u32, PIXEL_OP_REMAP_TRANSPEN_PRIORITY, u8);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    priotranspen_raw - render a gfx element
    with a single transparent pen and no color
    lookups, checking against the priority bitmap
-------------------------------------------------*/

void gfx_element::prio_transpen_raw(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		bitmap_ind8 &priority, UINT32 pmask, UINT32 trans_pen)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		bitmap_ind8 &priority, u32 pmask, u32 trans_pen)
>>>>>>> upstream/master
{
	// early out if completely transparent
	code %= elements();
	if (has_pen_usage() && (pen_usage(code) & ~(1 << trans_pen)) == 0)
		return;

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
<<<<<<< HEAD
	DRAWGFX_CORE(UINT16, PIXEL_OP_REBASE_TRANSPEN_PRIORITY, UINT8);
}

void gfx_element::prio_transpen_raw(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		bitmap_ind8 &priority, UINT32 pmask, UINT32 trans_pen)
=======
	DRAWGFX_CORE(u16, PIXEL_OP_REBASE_TRANSPEN_PRIORITY, u8);
}

void gfx_element::prio_transpen_raw(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		bitmap_ind8 &priority, u32 pmask, u32 trans_pen)
>>>>>>> upstream/master
{
	// early out if completely transparent
	code %= elements();
	if (has_pen_usage() && (pen_usage(code) & ~(1 << trans_pen)) == 0)
		return;

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
<<<<<<< HEAD
	DRAWGFX_CORE(UINT32, PIXEL_OP_REBASE_TRANSPEN_PRIORITY, UINT8);
=======
	DRAWGFX_CORE(u32, PIXEL_OP_REBASE_TRANSPEN_PRIORITY, u8);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    prio_transmask - render a gfx element
    with a multiple transparent pens provided as
    a mask, checking against the priority bitmap
-------------------------------------------------*/

void gfx_element::prio_transmask(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		bitmap_ind8 &priority, UINT32 pmask, UINT32 trans_mask)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		bitmap_ind8 &priority, u32 pmask, u32 trans_mask)
>>>>>>> upstream/master
{
	// special case 0 mask to opaque
	if (trans_mask == 0)
		return prio_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~trans_mask) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & trans_mask) == 0)
			return prio_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask);
	}

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	color = colorbase() + granularity() * (color % colors());
<<<<<<< HEAD
	DRAWGFX_CORE(UINT16, PIXEL_OP_REBASE_TRANSMASK_PRIORITY, UINT8);
}

void gfx_element::prio_transmask(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		bitmap_ind8 &priority, UINT32 pmask, UINT32 trans_mask)
=======
	DRAWGFX_CORE(u16, PIXEL_OP_REBASE_TRANSMASK_PRIORITY, u8);
}

void gfx_element::prio_transmask(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		bitmap_ind8 &priority, u32 pmask, u32 trans_mask)
>>>>>>> upstream/master
{
	// special case 0 mask to opaque
	if (trans_mask == 0)
		return prio_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~trans_mask) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & trans_mask) == 0)
			return prio_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask);
	}

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
<<<<<<< HEAD
	DRAWGFX_CORE(UINT32, PIXEL_OP_REMAP_TRANSMASK_PRIORITY, UINT8);
=======
	DRAWGFX_CORE(u32, PIXEL_OP_REMAP_TRANSMASK_PRIORITY, u8);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    prio_transtable - render a gfx element
    using a table to look up which pens are
    transparent, opaque, or shadowing, checking
    against the priority bitmap
-------------------------------------------------*/

void gfx_element::prio_transtable(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		bitmap_ind8 &priority, UINT32 pmask, const UINT8 *pentable)
{
	assert(pentable != NULL);
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		bitmap_ind8 &priority, u32 pmask, const u8 *pentable)
{
	assert(pentable != nullptr);
>>>>>>> upstream/master

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	color = colorbase() + granularity() * (color % colors());
	const pen_t *shadowtable = m_palette->shadow_table();
	code %= elements();
<<<<<<< HEAD
	DRAWGFX_CORE(UINT16, PIXEL_OP_REBASE_TRANSTABLE16_PRIORITY, UINT8);
}

void gfx_element::prio_transtable(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		bitmap_ind8 &priority, UINT32 pmask, const UINT8 *pentable)
{
	assert(pentable != NULL);
=======
	DRAWGFX_CORE(u16, PIXEL_OP_REBASE_TRANSTABLE16_PRIORITY, u8);
}

void gfx_element::prio_transtable(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		bitmap_ind8 &priority, u32 pmask, const u8 *pentable)
{
	assert(pentable != nullptr);
>>>>>>> upstream/master

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
	const pen_t *shadowtable = m_palette->shadow_table();
	code %= elements();
<<<<<<< HEAD
	DRAWGFX_CORE(UINT32, PIXEL_OP_REMAP_TRANSTABLE32_PRIORITY, UINT8);
=======
	DRAWGFX_CORE(u32, PIXEL_OP_REMAP_TRANSTABLE32_PRIORITY, u8);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    prio_alpha - render a gfx element with
    a single transparent pen, alpha blending the
    remaining pixels with a fixed alpha value,
    checking against the priority bitmap
-------------------------------------------------*/

void gfx_element::prio_alpha(bitmap_rgb32 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		bitmap_ind8 &priority, UINT32 pmask, UINT32 trans_pen, UINT8 alpha_val)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		bitmap_ind8 &priority, u32 pmask, u32 trans_pen, u8 alpha_val)
>>>>>>> upstream/master
{
	// special case alpha = 0xff
	if (alpha_val == 0xff)
		return prio_transpen(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask, trans_pen);

	// early out if completely transparent
	code %= elements();
	if (has_pen_usage() && (pen_usage(code) & ~(1 << trans_pen)) == 0)
		return;

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
<<<<<<< HEAD
	DRAWGFX_CORE(UINT32, PIXEL_OP_REMAP_TRANSPEN_ALPHA32_PRIORITY, UINT8);
=======
	DRAWGFX_CORE(u32, PIXEL_OP_REMAP_TRANSPEN_ALPHA32_PRIORITY, u8);
>>>>>>> upstream/master
}



/***************************************************************************
    PDRAWGFXZOOM IMPLEMENTATIONS
***************************************************************************/

/*-------------------------------------------------
    prio_zoom_opaque - render a scaled gfx
    element with no transparency, checking against
    the priority bitmap
-------------------------------------------------*/

void gfx_element::prio_zoom_opaque(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, bitmap_ind8 &priority, UINT32 pmask)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, bitmap_ind8 &priority, u32 pmask)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return prio_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask);

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	color = colorbase() + granularity() * (color % colors());
	code %= elements();
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT16, PIXEL_OP_REBASE_OPAQUE_PRIORITY, UINT8);
}

void gfx_element::prio_zoom_opaque(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, bitmap_ind8 &priority, UINT32 pmask)
=======
	DRAWGFXZOOM_CORE(u16, PIXEL_OP_REBASE_OPAQUE_PRIORITY, u8);
}

void gfx_element::prio_zoom_opaque(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, bitmap_ind8 &priority, u32 pmask)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return prio_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask);

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
	code %= elements();
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT32, PIXEL_OP_REMAP_OPAQUE_PRIORITY, UINT8);
=======
	DRAWGFXZOOM_CORE(u32, PIXEL_OP_REMAP_OPAQUE_PRIORITY, u8);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    prio_zoom_transpen - render a scaled gfx
    element with a single transparent pen,
    checking against the priority bitmap
-------------------------------------------------*/

void gfx_element::prio_zoom_transpen(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, bitmap_ind8 &priority, UINT32 pmask,
		UINT32 trans_pen)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, bitmap_ind8 &priority, u32 pmask,
		u32 trans_pen)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return prio_transpen(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask, trans_pen);

	// special case invalid pens to opaque
	if (trans_pen > 0xff)
		return prio_zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley, priority, pmask);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~(1 << trans_pen)) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & (1 << trans_pen)) == 0)
			return prio_zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley, priority, pmask);
	}

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	color = colorbase() + granularity() * (color % colors());
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT16, PIXEL_OP_REBASE_TRANSPEN_PRIORITY, UINT8);
}

void gfx_element::prio_zoom_transpen(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, bitmap_ind8 &priority, UINT32 pmask,
		UINT32 trans_pen)
=======
	DRAWGFXZOOM_CORE(u16, PIXEL_OP_REBASE_TRANSPEN_PRIORITY, u8);
}

void gfx_element::prio_zoom_transpen(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, bitmap_ind8 &priority, u32 pmask,
		u32 trans_pen)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return prio_transpen(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask, trans_pen);

	// special case invalid pens to opaque
	if (trans_pen > 0xff)
		return prio_zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley, priority, pmask);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~(1 << trans_pen)) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & (1 << trans_pen)) == 0)
			return prio_zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley, priority, pmask);
	}

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT32, PIXEL_OP_REMAP_TRANSPEN_PRIORITY, UINT8);
=======
	DRAWGFXZOOM_CORE(u32, PIXEL_OP_REMAP_TRANSPEN_PRIORITY, u8);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    prio_zoom_transpen_raw - render a scaled gfx
    element with a single transparent pen and no
    color lookups, checking against the priority
    bitmap
-------------------------------------------------*/

void gfx_element::prio_zoom_transpen_raw(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, bitmap_ind8 &priority, UINT32 pmask,
		UINT32 trans_pen)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, bitmap_ind8 &priority, u32 pmask,
		u32 trans_pen)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return prio_transpen_raw(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask, trans_pen);

	// early out if completely transparent
	code %= elements();
	if (has_pen_usage() && (pen_usage(code) & ~(1 << trans_pen)) == 0)
		return;

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT16, PIXEL_OP_REBASE_TRANSPEN_PRIORITY, UINT8);
}

void gfx_element::prio_zoom_transpen_raw(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, bitmap_ind8 &priority, UINT32 pmask,
		UINT32 trans_pen)
=======
	DRAWGFXZOOM_CORE(u16, PIXEL_OP_REBASE_TRANSPEN_PRIORITY, u8);
}

void gfx_element::prio_zoom_transpen_raw(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, bitmap_ind8 &priority, u32 pmask,
		u32 trans_pen)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return prio_transpen_raw(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask, trans_pen);

	// early out if completely transparent
	code %= elements();
	if (has_pen_usage() && (pen_usage(code) & ~(1 << trans_pen)) == 0)
		return;

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT32, PIXEL_OP_REBASE_TRANSPEN_PRIORITY, UINT8);
=======
	DRAWGFXZOOM_CORE(u32, PIXEL_OP_REBASE_TRANSPEN_PRIORITY, u8);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    prio_zoom_transmask - render a scaled gfx
    element with a multiple transparent pens
    provided as a mask, checking against the
    priority bitmap
-------------------------------------------------*/

void gfx_element::prio_zoom_transmask(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, bitmap_ind8 &priority, UINT32 pmask,
		UINT32 trans_mask)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, bitmap_ind8 &priority, u32 pmask,
		u32 trans_mask)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return prio_transmask(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask, trans_mask);

	// special case 0 mask to opaque
	if (trans_mask == 0)
		return prio_zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley, priority, pmask);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~trans_mask) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & trans_mask) == 0)
			return prio_zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley, priority, pmask);
	}

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	color = colorbase() + granularity() * (color % colors());
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT16, PIXEL_OP_REBASE_TRANSMASK_PRIORITY, UINT8);
}

void gfx_element::prio_zoom_transmask(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, bitmap_ind8 &priority, UINT32 pmask,
		UINT32 trans_mask)
=======
	DRAWGFXZOOM_CORE(u16, PIXEL_OP_REBASE_TRANSMASK_PRIORITY, u8);
}

void gfx_element::prio_zoom_transmask(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, bitmap_ind8 &priority, u32 pmask,
		u32 trans_mask)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return prio_transmask(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask, trans_mask);

	// special case 0 mask to opaque
	if (trans_mask == 0)
		return prio_zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley, priority, pmask);

	// use pen usage to optimize
	code %= elements();
	if (has_pen_usage())
	{
		// fully transparent; do nothing
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master
		if ((usage & ~trans_mask) == 0)
			return;

		// fully opaque; draw as such
		if ((usage & trans_mask) == 0)
			return prio_zoom_opaque(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley, priority, pmask);
	}

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT32, PIXEL_OP_REMAP_TRANSMASK_PRIORITY, UINT8);
=======
	DRAWGFXZOOM_CORE(u32, PIXEL_OP_REMAP_TRANSMASK_PRIORITY, u8);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    prio_zoom_transtable - render a scaled gfx
    element using a table to look up which pens
    are transparent, opaque, or shadowing,
    checking against the priority bitmap
-------------------------------------------------*/

void gfx_element::prio_zoom_transtable(bitmap_ind16 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, bitmap_ind8 &priority, UINT32 pmask,
		const UINT8 *pentable)
{
	assert(pentable != NULL);
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, bitmap_ind8 &priority, u32 pmask,
		const u8 *pentable)
{
	assert(pentable != nullptr);
>>>>>>> upstream/master

	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return prio_transtable(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask, pentable);

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	color = colorbase() + granularity() * (color % colors());
	const pen_t *shadowtable = m_palette->shadow_table();
	code %= elements();
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT16, PIXEL_OP_REBASE_TRANSTABLE16_PRIORITY, UINT8);
}

void gfx_element::prio_zoom_transtable(bitmap_rgb32 &dest, const rectangle &cliprect,
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, bitmap_ind8 &priority, UINT32 pmask,
		const UINT8 *pentable)
{
	assert(pentable != NULL);
=======
	DRAWGFXZOOM_CORE(u16, PIXEL_OP_REBASE_TRANSTABLE16_PRIORITY, u8);
}

void gfx_element::prio_zoom_transtable(bitmap_rgb32 &dest, const rectangle &cliprect,
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, bitmap_ind8 &priority, u32 pmask,
		const u8 *pentable)
{
	assert(pentable != nullptr);
>>>>>>> upstream/master

	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return prio_transtable(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask, pentable);

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
	const pen_t *shadowtable = m_palette->shadow_table();
	code %= elements();
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT32, PIXEL_OP_REMAP_TRANSTABLE32_PRIORITY, UINT8);
=======
	DRAWGFXZOOM_CORE(u32, PIXEL_OP_REMAP_TRANSTABLE32_PRIORITY, u8);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    prio_zoom_alpha - render a scaled gfx
    element with a single transparent pen, alpha
    blending the remaining pixels with a fixed
    alpha value, checking against the priority
    bitmap
-------------------------------------------------*/

void gfx_element::prio_zoom_alpha(bitmap_rgb32 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, bitmap_ind8 &priority, UINT32 pmask,
		UINT32 trans_pen, UINT8 alpha_val)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, bitmap_ind8 &priority, u32 pmask,
		u32 trans_pen, u8 alpha_val)
>>>>>>> upstream/master
{
	// non-zoom case
	if (scalex == 0x10000 && scaley == 0x10000)
		return prio_alpha(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask, trans_pen, alpha_val);

	// special case alpha_val = 0xff
	if (alpha_val == 0xff)
		return prio_zoom_transpen(dest, cliprect, code, color, flipx, flipy, destx, desty, scalex, scaley, priority, pmask, trans_pen);

	// early out if completely transparent
	code %= elements();
	if (has_pen_usage() && (pen_usage(code) & ~(1 << trans_pen)) == 0)
		return;

	// high bit of the mask is implicitly on
	pmask |= 1 << 31;

	// render
	const pen_t *paldata = m_palette->pens() + colorbase() + granularity() * (color % colors());
<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT32, PIXEL_OP_REMAP_TRANSPEN_ALPHA32_PRIORITY, UINT8);
}


#define PIXEL_OP_REMAP_TRANSPEN_PRIORITY_ADDIIVE32(DEST, PRIORITY, SOURCE)                  \
do                                                                                  \
{                                                                                   \
	UINT32 srcdata = (SOURCE);                                                      \
	if (srcdata != trans_pen)                                                        \
	{                                                                               \
		if (((1 << ((PRIORITY) & 0x1f)) & pmask) == 0)                              \
		{                                                                           \
			UINT32 srcdata2 = paldata[srcdata];                                     \
																					\
			UINT32 add;                                                             \
=======
	DRAWGFXZOOM_CORE(u32, PIXEL_OP_REMAP_TRANSPEN_ALPHA32_PRIORITY, u8);
}


#define PIXEL_OP_REMAP_TRANSPEN_PRIORITY_ADDIIVE32(DEST, PRIORITY, SOURCE)          \
do                                                                                  \
{                                                                                   \
	u32 srcdata = (SOURCE);                                                         \
	if (srcdata != trans_pen)                                                       \
	{                                                                               \
		if (((1 << ((PRIORITY) & 0x1f)) & pmask) == 0)                              \
		{                                                                           \
			u32 srcdata2 = paldata[srcdata];                                        \
																					\
			u32 add;                                                                \
>>>>>>> upstream/master
			add = (srcdata2 & 0x00ff0000) + (DEST & 0x00ff0000);                    \
			if (add & 0x01000000) DEST = (DEST & 0xff00ffff) | (0x00ff0000);        \
			else DEST = (DEST & 0xff00ffff) | (add & 0x00ff0000);                   \
			add = (srcdata2 & 0x000000ff) + (DEST & 0x000000ff);                    \
			if (add & 0x00000100) DEST = (DEST & 0xffffff00) | (0x000000ff);        \
			else DEST = (DEST & 0xffffff00) | (add & 0x000000ff);                   \
			add = (srcdata2 & 0x0000ff00) + (DEST & 0x0000ff00);                    \
			if (add & 0x00010000) DEST = (DEST & 0xffff00ff) | (0x0000ff00);        \
			else DEST = (DEST & 0xffff00ff) | (add & 0x0000ff00);                   \
		}                                                                           \
		(PRIORITY) = 31;                                                            \
	}                                                                               \
}                                                                                   \
while (0)

void gfx_element::prio_transpen_additive(bitmap_rgb32 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		bitmap_ind8 &priority, UINT32 pmask, UINT32 trans_pen)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		bitmap_ind8 &priority, u32 pmask, u32 trans_pen)
>>>>>>> upstream/master
{
	const pen_t *paldata;

	assert(dest.valid());
	assert(dest.bpp() == 32);

	/* get final code and color, and grab lookup tables */
	code %= elements();
	color %= colors();
	paldata = m_palette->pens() + colorbase() + granularity() * color;

	/* use pen usage to optimize */
	if (has_pen_usage())
	{
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master

		/* fully transparent; do nothing */
		if ((usage & ~(1 << trans_pen)) == 0)
			return;
	}

	/* high bit of the mask is implicitly on */
	pmask |= 1 << 31;

	/* render based on dest bitmap depth */
<<<<<<< HEAD
	DRAWGFX_CORE(UINT32, PIXEL_OP_REMAP_TRANSPEN_PRIORITY_ADDIIVE32, UINT8);
=======
	DRAWGFX_CORE(u32, PIXEL_OP_REMAP_TRANSPEN_PRIORITY_ADDIIVE32, u8);
>>>>>>> upstream/master
}


void gfx_element::prio_zoom_transpen_additive(bitmap_rgb32 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		UINT32 scalex, UINT32 scaley, bitmap_ind8 &priority, UINT32 pmask,
		UINT32 trans_pen)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		u32 scalex, u32 scaley, bitmap_ind8 &priority, u32 pmask,
		u32 trans_pen)
>>>>>>> upstream/master
{
	const pen_t *paldata;

	/* non-zoom case */

	if (scalex == 0x10000 && scaley == 0x10000)
	{
		prio_transpen_additive(dest, cliprect, code, color, flipx, flipy, destx, desty, priority, pmask, trans_pen);
		return;
	}

	assert(dest.valid());
	assert(dest.bpp() == 32);

	/* get final code and color, and grab lookup tables */
	code %= elements();
	color %= colors();
	paldata = m_palette->pens() + colorbase() + granularity() * color;

	/* use pen usage to optimize */
	if (has_pen_usage())
	{
<<<<<<< HEAD
		UINT32 usage = pen_usage(code);
=======
		u32 usage = pen_usage(code);
>>>>>>> upstream/master

		/* fully transparent; do nothing */
		if ((usage & ~(1 << trans_pen)) == 0)
			return;
	}

	/* high bit of the mask is implicitly on */
	pmask |= 1 << 31;

<<<<<<< HEAD
	DRAWGFXZOOM_CORE(UINT32, PIXEL_OP_REMAP_TRANSPEN_PRIORITY_ADDIIVE32, UINT8);
=======
	DRAWGFXZOOM_CORE(u32, PIXEL_OP_REMAP_TRANSPEN_PRIORITY_ADDIIVE32, u8);
>>>>>>> upstream/master
}

//#define MAKE_ARGB_RGB(a, rgb) rgb_t(a, rgb.r(), rgb.g(), rgb.b())
#define MAKE_ARGB_RGB(a, rgb)   rgb_t(rgb).set_a(a)

// combine in 'alpha' when copying to store in ARGB
#define PIXEL_OP_REMAP_TRANS0_ALPHASTORE32(DEST, PRIORITY, SOURCE)                                  \
do                                                                                                  \
{                                                                                                   \
<<<<<<< HEAD
	UINT32 srcdata = (SOURCE);                                                                      \
=======
	u32 srcdata = (SOURCE);                                                                         \
>>>>>>> upstream/master
	if (srcdata != 0)                                                                               \
		(DEST) = MAKE_ARGB_RGB(alpha,paldata[srcdata]);                                             \
}                                                                                                   \
while (0)
// combine in 'alphatable' value to store in ARGB
#define PIXEL_OP_REMAP_TRANS0_ALPHATABLESTORE32(DEST, PRIORITY, SOURCE)                             \
do                                                                                                  \
{                                                                                                   \
<<<<<<< HEAD
	UINT32 srcdata = (SOURCE);                                                                      \
=======
	u32 srcdata = (SOURCE);                                                                         \
>>>>>>> upstream/master
	if (srcdata != 0)                                                                               \
		(DEST) = MAKE_ARGB_RGB(alphatable[srcdata], paldata[srcdata]);                              \
}                                                                                                   \
while (0)
// drawgfxm.h macro to render alpha into 32-bit buffer
#define PIXEL_OP_REMAP_TRANS0_ALPHATABLE32(DEST, PRIORITY, SOURCE)                                  \
do                                                                                                  \
{                                                                                                   \
<<<<<<< HEAD
	UINT32 srcdata = (SOURCE);                                                                      \
=======
	u32 srcdata = (SOURCE);                                                                         \
>>>>>>> upstream/master
	if (srcdata != 0)                                                                               \
		(DEST) = alpha_blend_r32((DEST), paldata[srcdata], alphatable[srcdata]);                    \
}                                                                                                   \
while (0)

/*-------------------------------------------------
    alphastore - render a gfx element with
    a single transparent pen, storing the alpha value
    in alpha field of ARGB32, negative alpha implies alphatable
-------------------------------------------------*/
void gfx_element::alphastore(bitmap_rgb32 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		int fixedalpha, UINT8 *alphatable)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		int fixedalpha, u8 *alphatable)
>>>>>>> upstream/master
{
	DECLARE_NO_PRIORITY;
	const pen_t *paldata;

<<<<<<< HEAD
	assert(dest.bpp() == 32);
	assert(dest.format() == BITMAP_FORMAT_ARGB32);
	assert(alphatable != NULL);
=======
	assert(alphatable != nullptr);
>>>>>>> upstream/master

	/* if we have a fixed alpha, call the standard drawgfx_transpen */
	if (fixedalpha == 0xff)
	{
		transpen(dest, cliprect, code, color, flipx, flipy, destx, desty, 0);
		return;
	}

	/* get final code and color, and grab lookup tables */
	code %= elements();
	color %= colors();
	paldata = m_palette->pens() + colorbase() + granularity() * color;

	/* early out if completely transparent */
	if (has_pen_usage() && (pen_usage(code) & ~(1 << 0)) == 0)
		return;

	if (fixedalpha >= 0)
	{
<<<<<<< HEAD
		UINT8 alpha = fixedalpha;
		DRAWGFX_CORE(UINT32, PIXEL_OP_REMAP_TRANS0_ALPHASTORE32, NO_PRIORITY);
	}
	else
	{
		DRAWGFX_CORE(UINT32, PIXEL_OP_REMAP_TRANS0_ALPHATABLESTORE32, NO_PRIORITY);
=======
		u8 alpha = fixedalpha;
		DRAWGFX_CORE(u32, PIXEL_OP_REMAP_TRANS0_ALPHASTORE32, NO_PRIORITY);
	}
	else
	{
		DRAWGFX_CORE(u32, PIXEL_OP_REMAP_TRANS0_ALPHATABLESTORE32, NO_PRIORITY);
>>>>>>> upstream/master
	}
}

/*-------------------------------------------------
    alphatable - render a sprite with either
    a fixed alpha value, or if alpha==-1 then uses
    the per-pen alphatable[] array
 -------------------------------------------------*/
void gfx_element::alphatable(bitmap_rgb32 &dest, const rectangle &cliprect,
<<<<<<< HEAD
		UINT32 code, UINT32 color, int flipx, int flipy, INT32 destx, INT32 desty,
		int fixedalpha ,UINT8 *alphatable)
=======
		u32 code, u32 color, int flipx, int flipy, s32 destx, s32 desty,
		int fixedalpha ,u8 *alphatable)
>>>>>>> upstream/master
{
	DECLARE_NO_PRIORITY;

	const pen_t *paldata;

	/* if we have a fixed alpha, call the standard drawgfx_alpha */
	if (fixedalpha >= 0)
	{
		alpha(dest, cliprect, code, color, flipx, flipy, destx, desty, 0, fixedalpha);
		return;
	}

	assert(dest.bpp() == 32);
<<<<<<< HEAD
	assert(alphatable != NULL);
=======
	assert(alphatable != nullptr);
>>>>>>> upstream/master

	/* get final code and color, and grab lookup tables */
	code %= elements();
	color %= colors();
	paldata = m_palette->pens() + colorbase() + granularity() * color;

	/* early out if completely transparent */
	if (has_pen_usage() && (pen_usage(code) & ~(1 << 0)) == 0)
		return;

<<<<<<< HEAD
	DRAWGFX_CORE(UINT32, PIXEL_OP_REMAP_TRANS0_ALPHATABLE32, NO_PRIORITY);
=======
	DRAWGFX_CORE(u32, PIXEL_OP_REMAP_TRANS0_ALPHATABLE32, NO_PRIORITY);
>>>>>>> upstream/master
}


/***************************************************************************
    DRAW_SCANLINE IMPLEMENTATIONS
***************************************************************************/

/*-------------------------------------------------
    draw_scanline8 - copy pixels from an 8bpp
    buffer to a single scanline of a bitmap
-------------------------------------------------*/

<<<<<<< HEAD
void draw_scanline8(bitmap_ind16 &bitmap, INT32 destx, INT32 desty, INT32 length, const UINT8 *srcptr, const pen_t *paldata)
=======
void draw_scanline8(bitmap_ind16 &bitmap, s32 destx, s32 desty, s32 length, const u8 *srcptr, const pen_t *paldata)
>>>>>>> upstream/master
{
	DECLARE_NO_PRIORITY;

	// palette lookup case
<<<<<<< HEAD
	if (paldata != NULL)
		DRAWSCANLINE_CORE(UINT16, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);

	// raw copy case
	else
		DRAWSCANLINE_CORE(UINT16, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
}

void draw_scanline8(bitmap_rgb32 &bitmap, INT32 destx, INT32 desty, INT32 length, const UINT8 *srcptr, const pen_t *paldata)
=======
	if (paldata != nullptr)
		DRAWSCANLINE_CORE(u16, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);

	// raw copy case
	else
		DRAWSCANLINE_CORE(u16, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
}

void draw_scanline8(bitmap_rgb32 &bitmap, s32 destx, s32 desty, s32 length, const u8 *srcptr, const pen_t *paldata)
>>>>>>> upstream/master
{
	DECLARE_NO_PRIORITY;

	// palette lookup case
<<<<<<< HEAD
	if (paldata != NULL)
		DRAWSCANLINE_CORE(UINT32, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);

	// raw copy case
	else
		DRAWSCANLINE_CORE(UINT32, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
=======
	if (paldata != nullptr)
		DRAWSCANLINE_CORE(u32, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);

	// raw copy case
	else
		DRAWSCANLINE_CORE(u32, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    draw_scanline16 - copy pixels from a 16bpp
    buffer to a single scanline of a bitmap
-------------------------------------------------*/

<<<<<<< HEAD
void draw_scanline16(bitmap_ind16 &bitmap, INT32 destx, INT32 desty, INT32 length, const UINT16 *srcptr, const pen_t *paldata)
=======
void draw_scanline16(bitmap_ind16 &bitmap, s32 destx, s32 desty, s32 length, const u16 *srcptr, const pen_t *paldata)
>>>>>>> upstream/master
{
	DECLARE_NO_PRIORITY;

	// palette lookup case
<<<<<<< HEAD
	if (paldata != NULL)
		DRAWSCANLINE_CORE(UINT16, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);

	// raw copy case
	else
		DRAWSCANLINE_CORE(UINT16, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
}

void draw_scanline16(bitmap_rgb32 &bitmap, INT32 destx, INT32 desty, INT32 length, const UINT16 *srcptr, const pen_t *paldata)
=======
	if (paldata != nullptr)
		DRAWSCANLINE_CORE(u16, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);

	// raw copy case
	else
		DRAWSCANLINE_CORE(u16, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
}

void draw_scanline16(bitmap_rgb32 &bitmap, s32 destx, s32 desty, s32 length, const u16 *srcptr, const pen_t *paldata)
>>>>>>> upstream/master
{
	DECLARE_NO_PRIORITY;

	// palette lookup case
<<<<<<< HEAD
	if (paldata != NULL)
		DRAWSCANLINE_CORE(UINT32, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);

	// raw copy case
	else
		DRAWSCANLINE_CORE(UINT32, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
=======
	if (paldata != nullptr)
		DRAWSCANLINE_CORE(u32, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);

	// raw copy case
	else
		DRAWSCANLINE_CORE(u32, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    draw_scanline32 - copy pixels from a 32bpp
    buffer to a single scanline of a bitmap
-------------------------------------------------*/

<<<<<<< HEAD
void draw_scanline32(bitmap_ind16 &bitmap, INT32 destx, INT32 desty, INT32 length, const UINT32 *srcptr, const pen_t *paldata)
=======
void draw_scanline32(bitmap_ind16 &bitmap, s32 destx, s32 desty, s32 length, const u32 *srcptr, const pen_t *paldata)
>>>>>>> upstream/master
{
	DECLARE_NO_PRIORITY;

	// palette lookup case
<<<<<<< HEAD
	if (paldata != NULL)
		DRAWSCANLINE_CORE(UINT16, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);

	// raw copy case
	else
		DRAWSCANLINE_CORE(UINT16, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
}

void draw_scanline32(bitmap_rgb32 &bitmap, INT32 destx, INT32 desty, INT32 length, const UINT32 *srcptr, const pen_t *paldata)
=======
	if (paldata != nullptr)
		DRAWSCANLINE_CORE(u16, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);

	// raw copy case
	else
		DRAWSCANLINE_CORE(u16, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
}

void draw_scanline32(bitmap_rgb32 &bitmap, s32 destx, s32 desty, s32 length, const u32 *srcptr, const pen_t *paldata)
>>>>>>> upstream/master
{
	DECLARE_NO_PRIORITY;

	// palette lookup case
<<<<<<< HEAD
	if (paldata != NULL)
		DRAWSCANLINE_CORE(UINT32, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);

	// raw copy case
	else
		DRAWSCANLINE_CORE(UINT32, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
=======
	if (paldata != nullptr)
		DRAWSCANLINE_CORE(u32, PIXEL_OP_REMAP_OPAQUE, NO_PRIORITY);

	// raw copy case
	else
		DRAWSCANLINE_CORE(u32, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
>>>>>>> upstream/master
}



/***************************************************************************
    EXTRACT_SCANLINE IMPLEMENTATIONS
***************************************************************************/

/*-------------------------------------------------
    extract_scanline8 - copy pixels from a single
    scanline of a bitmap to an 8bpp buffer
-------------------------------------------------*/

<<<<<<< HEAD
void extract_scanline8(bitmap_ind16 &bitmap, INT32 srcx, INT32 srcy, INT32 length, UINT8 *destptr)
{
	EXTRACTSCANLINE_CORE(UINT16);
}

void extract_scanline8(bitmap_rgb32 &bitmap, INT32 srcx, INT32 srcy, INT32 length, UINT8 *destptr)
{
	EXTRACTSCANLINE_CORE(UINT32);
=======
void extract_scanline8(const bitmap_ind16 &bitmap, s32 srcx, s32 srcy, s32 length, u8 *destptr)
{
	EXTRACTSCANLINE_CORE(u16);
}

void extract_scanline8(const bitmap_rgb32 &bitmap, s32 srcx, s32 srcy, s32 length, u8 *destptr)
{
	EXTRACTSCANLINE_CORE(u32);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    extract_scanline16 - copy pixels from a single
    scanline of a bitmap to a 16bpp buffer
-------------------------------------------------*/

<<<<<<< HEAD
void extract_scanline16(bitmap_ind16 &bitmap, INT32 srcx, INT32 srcy, INT32 length, UINT16 *destptr)
{
	EXTRACTSCANLINE_CORE(UINT16);
}

void extract_scanline16(bitmap_rgb32 &bitmap, INT32 srcx, INT32 srcy, INT32 length, UINT16 *destptr)
{
	EXTRACTSCANLINE_CORE(UINT32);
=======
void extract_scanline16(const bitmap_ind16 &bitmap, s32 srcx, s32 srcy, s32 length, u16 *destptr)
{
	EXTRACTSCANLINE_CORE(u16);
}

void extract_scanline16(const bitmap_rgb32 &bitmap, s32 srcx, s32 srcy, s32 length, u16 *destptr)
{
	EXTRACTSCANLINE_CORE(u32);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    extract_scanline32 - copy pixels from a single
    scanline of a bitmap to a 32bpp buffer
-------------------------------------------------*/

<<<<<<< HEAD
void extract_scanline32(bitmap_ind16 &bitmap, INT32 srcx, INT32 srcy, INT32 length, UINT32 *destptr)
{
	EXTRACTSCANLINE_CORE(UINT16);
}

void extract_scanline32(bitmap_rgb32 &bitmap, INT32 srcx, INT32 srcy, INT32 length, UINT32 *destptr)
{
	EXTRACTSCANLINE_CORE(UINT32);
=======
void extract_scanline32(const bitmap_ind16 &bitmap, s32 srcx, s32 srcy, s32 length, u32 *destptr)
{
	EXTRACTSCANLINE_CORE(u16);
}

void extract_scanline32(const bitmap_rgb32 &bitmap, s32 srcx, s32 srcy, s32 length, u32 *destptr)
{
	EXTRACTSCANLINE_CORE(u32);
>>>>>>> upstream/master
}



/***************************************************************************
    COPYBITMAP IMPLEMENTATIONS
***************************************************************************/

/*-------------------------------------------------
    copybitmap - copy from one bitmap to another,
    copying all unclipped pixels
-------------------------------------------------*/

<<<<<<< HEAD
void copybitmap(bitmap_ind16 &dest, bitmap_ind16 &src, int flipx, int flipy, INT32 destx, INT32 desty, const rectangle &cliprect)
{
	DECLARE_NO_PRIORITY;
	COPYBITMAP_CORE(UINT16, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
}

void copybitmap(bitmap_rgb32 &dest, bitmap_rgb32 &src, int flipx, int flipy, INT32 destx, INT32 desty, const rectangle &cliprect)
{
	DECLARE_NO_PRIORITY;
	COPYBITMAP_CORE(UINT32, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
=======
void copybitmap(bitmap_ind16 &dest, const bitmap_ind16 &src, int flipx, int flipy, s32 destx, s32 desty, const rectangle &cliprect)
{
	DECLARE_NO_PRIORITY;
	COPYBITMAP_CORE(u16, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
}

void copybitmap(bitmap_rgb32 &dest, const bitmap_rgb32 &src, int flipx, int flipy, s32 destx, s32 desty, const rectangle &cliprect)
{
	DECLARE_NO_PRIORITY;
	COPYBITMAP_CORE(u32, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    copybitmap_trans - copy from one bitmap to
    another, copying all unclipped pixels except
    those that match transpen
-------------------------------------------------*/

<<<<<<< HEAD
void copybitmap_trans(bitmap_ind16 &dest, bitmap_ind16 &src, int flipx, int flipy, INT32 destx, INT32 desty, const rectangle &cliprect, UINT32 trans_pen)
=======
void copybitmap_trans(bitmap_ind16 &dest, const bitmap_ind16 &src, int flipx, int flipy, s32 destx, s32 desty, const rectangle &cliprect, u32 trans_pen)
>>>>>>> upstream/master
{
	DECLARE_NO_PRIORITY;
	if (trans_pen > 0xffff)
		copybitmap(dest, src, flipx, flipy, destx, desty, cliprect);
	else
<<<<<<< HEAD
		COPYBITMAP_CORE(UINT16, PIXEL_OP_COPY_TRANSPEN, NO_PRIORITY);
}

void copybitmap_trans(bitmap_rgb32 &dest, bitmap_rgb32 &src, int flipx, int flipy, INT32 destx, INT32 desty, const rectangle &cliprect, UINT32 trans_pen)
=======
		COPYBITMAP_CORE(u16, PIXEL_OP_COPY_TRANSPEN, NO_PRIORITY);
}

void copybitmap_trans(bitmap_rgb32 &dest, const bitmap_rgb32 &src, int flipx, int flipy, s32 destx, s32 desty, const rectangle &cliprect, u32 trans_pen)
>>>>>>> upstream/master
{
	DECLARE_NO_PRIORITY;
	if (trans_pen == 0xffffffff)
		copybitmap(dest, src, flipx, flipy, destx, desty, cliprect);
	else
<<<<<<< HEAD
		COPYBITMAP_CORE(UINT32, PIXEL_OP_COPY_TRANSPEN, NO_PRIORITY);
=======
		COPYBITMAP_CORE(u32, PIXEL_OP_COPY_TRANSPEN, NO_PRIORITY);
>>>>>>> upstream/master
}



/***************************************************************************
    COPYSCROLLBITMAP IMPLEMENTATIONS
***************************************************************************/

/*-------------------------------------------------
    copyscrollbitmap - copy from one bitmap to
    another, copying all unclipped pixels, and
    applying scrolling to one or more rows/columns
-------------------------------------------------*/

<<<<<<< HEAD
void copyscrollbitmap(bitmap_ind16 &dest, bitmap_ind16 &src, UINT32 numrows, const INT32 *rowscroll, UINT32 numcols, const INT32 *colscroll, const rectangle &cliprect)
=======
void copyscrollbitmap(bitmap_ind16 &dest, const bitmap_ind16 &src, u32 numrows, const s32 *rowscroll, u32 numcols, const s32 *colscroll, const rectangle &cliprect)
>>>>>>> upstream/master
{
	// just call through to the transparent case as the underlying copybitmap will
	// optimize for pen == 0xffffffff
	copyscrollbitmap_trans(dest, src, numrows, rowscroll, numcols, colscroll, cliprect, 0xffffffff);
}

<<<<<<< HEAD
void copyscrollbitmap(bitmap_rgb32 &dest, bitmap_rgb32 &src, UINT32 numrows, const INT32 *rowscroll, UINT32 numcols, const INT32 *colscroll, const rectangle &cliprect)
=======
void copyscrollbitmap(bitmap_rgb32 &dest, const bitmap_rgb32 &src, u32 numrows, const s32 *rowscroll, u32 numcols, const s32 *colscroll, const rectangle &cliprect)
>>>>>>> upstream/master
{
	// just call through to the transparent case as the underlying copybitmap will
	// optimize for pen == 0xffffffff
	copyscrollbitmap_trans(dest, src, numrows, rowscroll, numcols, colscroll, cliprect, 0xffffffff);
}


/*-------------------------------------------------
    copyscrollbitmap_trans - copy from one bitmap
    to another, copying all unclipped pixels
    except those that match transpen, and applying
    scrolling to one or more rows/columns
-------------------------------------------------*/

template<class _BitmapClass>
<<<<<<< HEAD
static inline void copyscrollbitmap_trans_common(_BitmapClass &dest, _BitmapClass &src, UINT32 numrows, const INT32 *rowscroll, UINT32 numcols, const INT32 *colscroll, const rectangle &cliprect, UINT32 trans_pen)
=======
static inline void copyscrollbitmap_trans_common(_BitmapClass &dest, const _BitmapClass &src, u32 numrows, const s32 *rowscroll, u32 numcols, const s32 *colscroll, const rectangle &cliprect, u32 trans_pen)
>>>>>>> upstream/master
{
	// no rowscroll and no colscroll means no scroll
	if (numrows == 0 && numcols == 0)
		return copybitmap_trans(dest, src, 0, 0, 0, 0, cliprect, trans_pen);

<<<<<<< HEAD
	assert(numrows != 0 || rowscroll == NULL);
	assert(numrows == 0 || rowscroll != NULL);
	assert(numcols != 0 || colscroll == NULL);
	assert(numcols == 0 || colscroll != NULL);
=======
	assert(numrows != 0 || rowscroll == nullptr);
	assert(numrows == 0 || rowscroll != nullptr);
	assert(numcols != 0 || colscroll == nullptr);
	assert(numcols == 0 || colscroll != nullptr);
>>>>>>> upstream/master

	// fully scrolling X,Y playfield
	if (numrows <= 1 && numcols <= 1)
	{
<<<<<<< HEAD
		INT32 xscroll = normalize_xscroll(src, (numrows == 0) ? 0 : rowscroll[0]);
		INT32 yscroll = normalize_yscroll(src, (numcols == 0) ? 0 : colscroll[0]);

		// iterate over all portions of the scroll that overlap the destination
		for (INT32 sx = xscroll - src.width(); sx < dest.width(); sx += src.width())
			for (INT32 sy = yscroll - src.height(); sy < dest.height(); sy += src.height())
=======
		s32 xscroll = normalize_xscroll(src, (numrows == 0) ? 0 : rowscroll[0]);
		s32 yscroll = normalize_yscroll(src, (numcols == 0) ? 0 : colscroll[0]);

		// iterate over all portions of the scroll that overlap the destination
		for (s32 sx = xscroll - src.width(); sx < dest.width(); sx += src.width())
			for (s32 sy = yscroll - src.height(); sy < dest.height(); sy += src.height())
>>>>>>> upstream/master
				copybitmap_trans(dest, src, 0, 0, sx, sy, cliprect, trans_pen);
	}

	// scrolling columns plus horizontal scroll
	else if (numrows <= 1)
	{
<<<<<<< HEAD
		INT32 xscroll = normalize_xscroll(src, (numrows == 0) ? 0 : rowscroll[0]);
=======
		s32 xscroll = normalize_xscroll(src, (numrows == 0) ? 0 : rowscroll[0]);
>>>>>>> upstream/master
		rectangle subclip = cliprect;

		// determine width of each column
		int colwidth = src.width() / numcols;
		assert(src.width() % colwidth == 0);

		// iterate over each column
		int groupcols;
		for (int col = 0; col < numcols; col += groupcols)
		{
<<<<<<< HEAD
			INT32 yscroll = colscroll[col];
=======
			s32 yscroll = colscroll[col];
>>>>>>> upstream/master

			// count consecutive columns scrolled by the same amount
			for (groupcols = 1; col + groupcols < numcols; groupcols++)
					if (colscroll[col + groupcols] != yscroll)
					break;

			// iterate over reps of the columns in question
			yscroll = normalize_yscroll(src, yscroll);
<<<<<<< HEAD
			for (INT32 sx = xscroll - src.width(); sx < dest.width(); sx += src.width())
=======
			for (s32 sx = xscroll - src.width(); sx < dest.width(); sx += src.width())
>>>>>>> upstream/master
			{
				// compute the cliprect for this group
				subclip.min_x = col * colwidth + sx;
				subclip.max_x = (col + groupcols) * colwidth - 1 + sx;
				subclip &= cliprect;

				// iterate over all portions of the scroll that overlap the destination
<<<<<<< HEAD
				for (INT32 sy = yscroll - src.height(); sy < dest.height(); sy += src.height())
=======
				for (s32 sy = yscroll - src.height(); sy < dest.height(); sy += src.height())
>>>>>>> upstream/master
					copybitmap_trans(dest, src, 0, 0, sx, sy, subclip, trans_pen);
			}
		}
	}

	// scrolling rows plus vertical scroll
	else if (numcols <= 1)
	{
<<<<<<< HEAD
		INT32 yscroll = normalize_yscroll(src, (numcols == 0) ? 0 : colscroll[0]);
=======
		s32 yscroll = normalize_yscroll(src, (numcols == 0) ? 0 : colscroll[0]);
>>>>>>> upstream/master
		rectangle subclip = cliprect;

		// determine width of each rows
		int rowheight = src.height() / numrows;
		assert(src.height() % rowheight == 0);

		// iterate over each row
		int grouprows;
		for (int row = 0; row < numrows; row += grouprows)
		{
<<<<<<< HEAD
			INT32 xscroll = rowscroll[row];
=======
			s32 xscroll = rowscroll[row];
>>>>>>> upstream/master

			// count consecutive rows scrolled by the same amount
			for (grouprows = 1; row + grouprows < numrows; grouprows++)
					if (rowscroll[row + grouprows] != xscroll)
					break;

			// iterate over reps of the rows in question
			xscroll = normalize_xscroll(src, xscroll);
<<<<<<< HEAD
			for (INT32 sy = yscroll - src.height(); sy < dest.height(); sy += src.height())
=======
			for (s32 sy = yscroll - src.height(); sy < dest.height(); sy += src.height())
>>>>>>> upstream/master
			{
				// compute the cliprect for this group
				subclip.min_y = row * rowheight + sy;
				subclip.max_y = (row + grouprows) * rowheight - 1 + sy;
				subclip &= cliprect;

				// iterate over all portions of the scroll that overlap the destination
<<<<<<< HEAD
				for (INT32 sx = xscroll - src.width(); sx < dest.width(); sx += src.width())
=======
				for (s32 sx = xscroll - src.width(); sx < dest.width(); sx += src.width())
>>>>>>> upstream/master
					copybitmap_trans(dest, src, 0, 0, sx, sy, subclip, trans_pen);
			}
		}
	}
}

<<<<<<< HEAD
void copyscrollbitmap_trans(bitmap_ind16 &dest, bitmap_ind16 &src, UINT32 numrows, const INT32 *rowscroll, UINT32 numcols, const INT32 *colscroll, const rectangle &cliprect, UINT32 trans_pen)
{ copyscrollbitmap_trans_common(dest, src, numrows, rowscroll, numcols, colscroll, cliprect, trans_pen); }

void copyscrollbitmap_trans(bitmap_rgb32 &dest, bitmap_rgb32 &src, UINT32 numrows, const INT32 *rowscroll, UINT32 numcols, const INT32 *colscroll, const rectangle &cliprect, UINT32 trans_pen)
=======
void copyscrollbitmap_trans(bitmap_ind16 &dest, const bitmap_ind16 &src, u32 numrows, const s32 *rowscroll, u32 numcols, const s32 *colscroll, const rectangle &cliprect, u32 trans_pen)
{ copyscrollbitmap_trans_common(dest, src, numrows, rowscroll, numcols, colscroll, cliprect, trans_pen); }

void copyscrollbitmap_trans(bitmap_rgb32 &dest, const bitmap_rgb32 &src, u32 numrows, const s32 *rowscroll, u32 numcols, const s32 *colscroll, const rectangle &cliprect, u32 trans_pen)
>>>>>>> upstream/master
{ copyscrollbitmap_trans_common(dest, src, numrows, rowscroll, numcols, colscroll, cliprect, trans_pen); }



/***************************************************************************
    COPYROZBITMAP IMPLEMENTATIONS
***************************************************************************/

/*-------------------------------------------------
    copyrozbitmap - copy from one bitmap to another,
    with zoom and rotation, copying all unclipped
    pixels
-------------------------------------------------*/

<<<<<<< HEAD
void copyrozbitmap(bitmap_ind16 &dest, const rectangle &cliprect, bitmap_ind16 &src, INT32 startx, INT32 starty, INT32 incxx, INT32 incxy, INT32 incyx, INT32 incyy, int wraparound)
{
	DECLARE_NO_PRIORITY;
	COPYROZBITMAP_CORE(UINT16, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
}

void copyrozbitmap(bitmap_rgb32 &dest, const rectangle &cliprect, bitmap_rgb32 &src, INT32 startx, INT32 starty, INT32 incxx, INT32 incxy, INT32 incyx, INT32 incyy, int wraparound)
{
	DECLARE_NO_PRIORITY;
	COPYROZBITMAP_CORE(UINT32, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
=======
void copyrozbitmap(bitmap_ind16 &dest, const rectangle &cliprect, const bitmap_ind16 &src, s32 startx, s32 starty, s32 incxx, s32 incxy, s32 incyx, s32 incyy, int wraparound)
{
	DECLARE_NO_PRIORITY;
	COPYROZBITMAP_CORE(u16, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
}

void copyrozbitmap(bitmap_rgb32 &dest, const rectangle &cliprect, const bitmap_rgb32 &src, s32 startx, s32 starty, s32 incxx, s32 incxy, s32 incyx, s32 incyy, int wraparound)
{
	DECLARE_NO_PRIORITY;
	COPYROZBITMAP_CORE(u32, PIXEL_OP_COPY_OPAQUE, NO_PRIORITY);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    copyrozbitmap_trans - copy from one bitmap to
    another, with zoom and rotation, copying all
    unclipped pixels whose values do not match
    transpen
-------------------------------------------------*/

<<<<<<< HEAD
void copyrozbitmap_trans(bitmap_ind16 &dest, const rectangle &cliprect, bitmap_ind16 &src, INT32 startx, INT32 starty, INT32 incxx, INT32 incxy, INT32 incyx, INT32 incyy, int wraparound, UINT32 trans_pen)
{
	DECLARE_NO_PRIORITY;
	COPYROZBITMAP_CORE(UINT16, PIXEL_OP_COPY_TRANSPEN, NO_PRIORITY);
}

void copyrozbitmap_trans(bitmap_rgb32 &dest, const rectangle &cliprect, bitmap_rgb32 &src, INT32 startx, INT32 starty, INT32 incxx, INT32 incxy, INT32 incyx, INT32 incyy, int wraparound, UINT32 trans_pen)
{
	DECLARE_NO_PRIORITY;
	COPYROZBITMAP_CORE(UINT32, PIXEL_OP_COPY_TRANSPEN, NO_PRIORITY);
=======
void copyrozbitmap_trans(bitmap_ind16 &dest, const rectangle &cliprect, const bitmap_ind16 &src, s32 startx, s32 starty, s32 incxx, s32 incxy, s32 incyx, s32 incyy, int wraparound, u32 trans_pen)
{
	DECLARE_NO_PRIORITY;
	COPYROZBITMAP_CORE(u16, PIXEL_OP_COPY_TRANSPEN, NO_PRIORITY);
}

void copyrozbitmap_trans(bitmap_rgb32 &dest, const rectangle &cliprect, const bitmap_rgb32 &src, s32 startx, s32 starty, s32 incxx, s32 incxy, s32 incyx, s32 incyy, int wraparound, u32 trans_pen)
{
	DECLARE_NO_PRIORITY;
	COPYROZBITMAP_CORE(u32, PIXEL_OP_COPY_TRANSPEN, NO_PRIORITY);
>>>>>>> upstream/master
}

GFXDECODE_START( empty )
GFXDECODE_END
