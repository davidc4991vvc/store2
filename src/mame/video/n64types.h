// license:BSD-3-Clause
// copyright-holders:Ryan Holtz

#ifndef _VIDEO_N64TYPES_H_
#define _VIDEO_N64TYPES_H_

#include "video/rgbutil.h"

struct misc_state_t
{
	misc_state_t()
	{
		m_max_level = 0;
		m_min_level = 0;
	}

<<<<<<< HEAD
	INT32 m_fb_format;          // Framebuffer pixel format index (0 - I, 1 - IA, 2 - CI, 3 - RGBA)
	INT32 m_fb_size;            // Framebuffer pixel size index (0 - 4bpp, 1 - 8bpp, 2 - 16bpp, 3 - 32bpp)
	INT32 m_fb_width;           // Framebuffer width, in pixels
	INT32 m_fb_height;          // Framebuffer height, in pixels
	UINT32 m_fb_address;        // Framebuffer source address offset (in bytes) from start of RDRAM

	UINT32 m_zb_address;        // Z-buffer source address offset (in bytes) from start of RDRAM

	INT32 m_ti_format;          // Format for Texture Interface (TI) transfers
	INT32 m_ti_size;            // Size (in bytes) of TI transfers
	INT32 m_ti_width;           // Width (in pixels) of TI transfers
	UINT32 m_ti_address;        // Destination address for TI transfers

	UINT32 m_max_level;         // Maximum LOD level for texture filtering
	UINT32 m_min_level;         // Minimum LOD level for texture filtering

	UINT16 m_primitive_z;       // Forced Z value for current primitive, if applicable
	UINT16 m_primitive_dz;      // Forced Delta-Z value for current primitive, if applicable
=======
	int32_t m_fb_format;          // Framebuffer pixel format index (0 - I, 1 - IA, 2 - CI, 3 - RGBA)
	int32_t m_fb_size;            // Framebuffer pixel size index (0 - 4bpp, 1 - 8bpp, 2 - 16bpp, 3 - 32bpp)
	int32_t m_fb_width;           // Framebuffer width, in pixels
	int32_t m_fb_height;          // Framebuffer height, in pixels
	uint32_t m_fb_address;        // Framebuffer source address offset (in bytes) from start of RDRAM

	uint32_t m_zb_address;        // Z-buffer source address offset (in bytes) from start of RDRAM

	int32_t m_ti_format;          // Format for Texture Interface (TI) transfers
	int32_t m_ti_size;            // Size (in bytes) of TI transfers
	int32_t m_ti_width;           // Width (in pixels) of TI transfers
	uint32_t m_ti_address;        // Destination address for TI transfers

	uint32_t m_max_level;         // Maximum LOD level for texture filtering
	uint32_t m_min_level;         // Minimum LOD level for texture filtering

	uint16_t m_primitive_z;       // Forced Z value for current primitive, if applicable
	uint16_t m_primitive_dz;      // Forced Delta-Z value for current primitive, if applicable
>>>>>>> upstream/master
};

#if 0
class color_t
{
	public:
		color_t()
		{
			c = 0;
		}

<<<<<<< HEAD
		color_t(UINT32 color)
=======
		color_t(uint32_t color)
>>>>>>> upstream/master
		{
			set(color);
		}

<<<<<<< HEAD
		color_t(UINT8 a, UINT8 r, UINT8 g, UINT8 b)
=======
		color_t(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
>>>>>>> upstream/master
		{
			set(a, r, g, b);
		}

		inline void set(color_t& other)
		{
			c = other.c;
		}

<<<<<<< HEAD
		inline void set(UINT32 color)
=======
		inline void set(uint32_t color)
>>>>>>> upstream/master
		{
			i.a = (color >> 24) & 0xff;
			i.r = (color >> 16) & 0xff;
			i.g = (color >>  8) & 0xff;
			i.b = color & 0xff;
		}

<<<<<<< HEAD
		void set(UINT8 a, UINT8 r, UINT8 g, UINT8 b)
=======
		void set(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
>>>>>>> upstream/master
		{
			i.a = a;
			i.r = r;
			i.g = g;
			i.b = b;
		}

<<<<<<< HEAD
		inline void set_direct(UINT32 color)
=======
		inline void set_direct(uint32_t color)
>>>>>>> upstream/master
		{
			c = color;
		}

<<<<<<< HEAD
		UINT32 get()
=======
		uint32_t get()
>>>>>>> upstream/master
		{
			return i.a << 24 | i.r << 16 | i.g << 8 | i.b;
		}

		union
		{
<<<<<<< HEAD
			UINT32 c;
#ifdef LSB_FIRST
			struct { UINT8 a, b, g, r; } i;
#else
			struct { UINT8 r, g, b, a; } i;
=======
			uint32_t c;
#ifdef LSB_FIRST
			struct { uint8_t a, b, g, r; } i;
#else
			struct { uint8_t r, g, b, a; } i;
>>>>>>> upstream/master
#endif
		};
};
#else
#define color_t rgbaint_t
#endif

enum
{
	BIT_DEPTH_32 = 0,
	BIT_DEPTH_16,

	BIT_DEPTH_COUNT
};

struct n64_tile_t
{
<<<<<<< HEAD
	INT32 format; // Image data format: RGBA, YUV, CI, IA, I
	INT32 size; // Size of texel element: 4b, 8b, 16b, 32b
	INT32 line; // Size of tile line in bytes
	INT32 tmem; // Starting tmem address for this tile in bytes
	INT32 palette; // Palette number for 4b CI texels
	INT32 ct, mt, cs, ms; // Clamp / mirror enable bits for S / T direction
	INT32 mask_t, shift_t, mask_s, shift_s; // Mask values / LOD shifts
	INT32 lshift_s, rshift_s, lshift_t, rshift_t;
	INT32 wrapped_mask_s, wrapped_mask_t;
=======
	int32_t format; // Image data format: RGBA, YUV, CI, IA, I
	int32_t size; // Size of texel element: 4b, 8b, 16b, 32b
	int32_t line; // Size of tile line in bytes
	int32_t tmem; // Starting tmem address for this tile in bytes
	int32_t palette; // Palette number for 4b CI texels
	int32_t ct, mt, cs, ms; // Clamp / mirror enable bits for S / T direction
	int32_t mask_t, shift_t, mask_s, shift_s; // Mask values / LOD shifts
	int32_t lshift_s, rshift_s, lshift_t, rshift_t;
	int32_t wrapped_mask_s, wrapped_mask_t;
>>>>>>> upstream/master
	bool clamp_s, clamp_t;
	rgbaint_t mm, invmm;
	rgbaint_t wrapped_mask;
	rgbaint_t mask;
	rgbaint_t invmask;
	rgbaint_t lshift;
	rgbaint_t rshift;
	rgbaint_t sth;
	rgbaint_t stl;
	rgbaint_t clamp_st;
<<<<<<< HEAD
	UINT16 sl, tl, sh, th;      // 10.2 fixed-point, starting and ending texel row / column
	INT32 num;
=======
	uint16_t sl, tl, sh, th;      // 10.2 fixed-point, starting and ending texel row / column
	int32_t num;
>>>>>>> upstream/master
};

struct span_base_t
{
<<<<<<< HEAD
	INT32 m_span_dr;
	INT32 m_span_dg;
	INT32 m_span_db;
	INT32 m_span_da;
	INT32 m_span_ds;
	INT32 m_span_dt;
	INT32 m_span_dw;
	INT32 m_span_dz;
	INT32 m_span_dymax;
	INT32 m_span_dzpix;
	INT32 m_span_drdy;
	INT32 m_span_dgdy;
	INT32 m_span_dbdy;
	INT32 m_span_dady;
	INT32 m_span_dzdy;
=======
	int32_t m_span_dr;
	int32_t m_span_dg;
	int32_t m_span_db;
	int32_t m_span_da;
	int32_t m_span_ds;
	int32_t m_span_dt;
	int32_t m_span_dw;
	int32_t m_span_dz;
	int32_t m_span_dymax;
	int32_t m_span_dzpix;
	int32_t m_span_drdy;
	int32_t m_span_dgdy;
	int32_t m_span_dbdy;
	int32_t m_span_dady;
	int32_t m_span_dzdy;
>>>>>>> upstream/master
};

struct combine_modes_t
{
<<<<<<< HEAD
	INT32 sub_a_rgb0;
	INT32 sub_b_rgb0;
	INT32 mul_rgb0;
	INT32 add_rgb0;
	INT32 sub_a_a0;
	INT32 sub_b_a0;
	INT32 mul_a0;
	INT32 add_a0;

	INT32 sub_a_rgb1;
	INT32 sub_b_rgb1;
	INT32 mul_rgb1;
	INT32 add_rgb1;
	INT32 sub_a_a1;
	INT32 sub_b_a1;
	INT32 mul_a1;
	INT32 add_a1;
=======
	int32_t sub_a_rgb0;
	int32_t sub_b_rgb0;
	int32_t mul_rgb0;
	int32_t add_rgb0;
	int32_t sub_a_a0;
	int32_t sub_b_a0;
	int32_t mul_a0;
	int32_t add_a0;

	int32_t sub_a_rgb1;
	int32_t sub_b_rgb1;
	int32_t mul_rgb1;
	int32_t add_rgb1;
	int32_t sub_a_a1;
	int32_t sub_b_a1;
	int32_t mul_a1;
	int32_t add_a1;
>>>>>>> upstream/master
};

struct color_inputs_t
{
	// combiner inputs
	color_t* combiner_rgbsub_a[2];
	color_t* combiner_rgbsub_b[2];
	color_t* combiner_rgbmul[2];
	color_t* combiner_rgbadd[2];

	color_t* combiner_alphasub_a[2];
	color_t* combiner_alphasub_b[2];
	color_t* combiner_alphamul[2];
	color_t* combiner_alphaadd[2];

	// blender input
	color_t* blender1a_rgb[2];
	color_t* blender1b_a[2];
	color_t* blender2a_rgb[2];
	color_t* blender2b_a[2];
};

struct other_modes_t
{
<<<<<<< HEAD
	INT32 cycle_type;
=======
	int32_t cycle_type;
>>>>>>> upstream/master
	bool persp_tex_en;
	bool detail_tex_en;
	bool sharpen_tex_en;
	bool tex_lod_en;
	bool en_tlut;
	bool tlut_type;
	bool sample_type;
	bool mid_texel;
	bool bi_lerp0;
	bool bi_lerp1;
	bool convert_one;
	bool key_en;
<<<<<<< HEAD
	INT32 rgb_dither_sel;
	INT32 alpha_dither_sel;
	INT32 blend_m1a_0;
	INT32 blend_m1a_1;
	INT32 blend_m1b_0;
	INT32 blend_m1b_1;
	INT32 blend_m2a_0;
	INT32 blend_m2a_1;
	INT32 blend_m2b_0;
	INT32 blend_m2b_1;
	INT32 tex_edge;
	INT32 force_blend;
	INT32 blend_shift;
	bool alpha_cvg_select;
	bool cvg_times_alpha;
	INT32 z_mode;
	INT32 cvg_dest;
	bool color_on_cvg;
	UINT8 image_read_en;
=======
	int32_t rgb_dither_sel;
	int32_t alpha_dither_sel;
	int32_t blend_m1a_0;
	int32_t blend_m1a_1;
	int32_t blend_m1b_0;
	int32_t blend_m1b_1;
	int32_t blend_m2a_0;
	int32_t blend_m2a_1;
	int32_t blend_m2b_0;
	int32_t blend_m2b_1;
	int32_t tex_edge;
	int32_t force_blend;
	int32_t blend_shift;
	bool alpha_cvg_select;
	bool cvg_times_alpha;
	int32_t z_mode;
	int32_t cvg_dest;
	bool color_on_cvg;
	uint8_t image_read_en;
>>>>>>> upstream/master
	bool z_update_en;
	bool z_compare_en;
	bool antialias_en;
	bool z_source_sel;
<<<<<<< HEAD
	INT32 dither_alpha_en;
	INT32 alpha_compare_en;
	INT32 alpha_dither_mode;
=======
	int32_t dither_alpha_en;
	int32_t alpha_compare_en;
	int32_t alpha_dither_mode;
>>>>>>> upstream/master
};

struct rectangle_t
{
<<<<<<< HEAD
	UINT16 m_xl;    // 10.2 fixed-point
	UINT16 m_yl;    // 10.2 fixed-point
	UINT16 m_xh;    // 10.2 fixed-point
	UINT16 m_yh;    // 10.2 fixed-point
=======
	uint16_t m_xl;    // 10.2 fixed-point
	uint16_t m_yl;    // 10.2 fixed-point
	uint16_t m_xh;    // 10.2 fixed-point
	uint16_t m_yh;    // 10.2 fixed-point
>>>>>>> upstream/master
};

struct rdp_poly_state
{
	n64_rdp*            m_rdp;                  /* pointer back to the RDP state */

	misc_state_t        m_misc_state;           /* miscellaneous rasterizer bits */
	other_modes_t       m_other_modes;          /* miscellaneous rasterizer bits (2) */
	span_base_t         m_span_base;            /* span initial values for triangle rasterization */
	rectangle_t         m_scissor;              /* screen-space scissor bounds */
<<<<<<< HEAD
	UINT32              m_fill_color;           /* poly fill color */
	n64_tile_t          m_tiles[8];             /* texture tile state */
	UINT8               m_tmem[0x1000];         /* texture cache */
	INT32               tilenum;                /* texture tile index */
=======
	uint32_t              m_fill_color;           /* poly fill color */
	n64_tile_t          m_tiles[8];             /* texture tile state */
	uint8_t               m_tmem[0x1000];         /* texture cache */
	int32_t               tilenum;                /* texture tile index */
>>>>>>> upstream/master
	bool                flip;                   /* left-major / right-major flip */
	bool                rect;                   /* primitive is rectangle (vs. triangle) */
};

#define RDP_CVG_SPAN_MAX            (1024)

// This is enormous and horrible
struct rdp_span_aux
{
<<<<<<< HEAD
	UINT32              m_unscissored_rx;
	UINT16              m_cvg[RDP_CVG_SPAN_MAX];
=======
	uint32_t              m_unscissored_rx;
	uint16_t              m_cvg[RDP_CVG_SPAN_MAX];
>>>>>>> upstream/master
	color_t             m_memory_color;
	color_t             m_pixel_color;
	color_t             m_inv_pixel_color;
	color_t             m_blended_pixel_color;

	color_t             m_combined_color;
	color_t             m_combined_alpha;
	color_t             m_texel0_color;
	color_t             m_texel0_alpha;
	color_t             m_texel1_color;
	color_t             m_texel1_alpha;
	color_t             m_next_texel_color;
	color_t             m_next_texel_alpha;
	color_t             m_blend_color;          /* constant blend color */
	color_t             m_prim_color;           /* flat primitive color */
	color_t             m_prim_alpha;           /* flat primitive alpha */
	color_t             m_env_color;            /* generic color constant ('environment') */
	color_t             m_env_alpha;            /* generic alpha constant ('environment') */
	color_t             m_fog_color;            /* generic color constant ('fog') */
	color_t             m_shade_color;          /* gouraud-shaded color */
	color_t             m_shade_alpha;          /* gouraud-shaded alpha */
	color_t             m_key_scale;            /* color-keying constant */
	color_t             m_noise_color;          /* noise */
	color_t             m_lod_fraction;         /* Z-based LOD fraction for this poly */
	color_t             m_prim_lod_fraction;    /* fixed LOD fraction for this poly */
	color_t             m_k4;
	color_t             m_k5;
	color_inputs_t      m_color_inputs;
<<<<<<< HEAD
	UINT32              m_current_pix_cvg;
	UINT32              m_current_mem_cvg;
	UINT32              m_current_cvg_bit;
	INT32               m_shift_a;
	INT32               m_shift_b;
	INT32               m_precomp_s;
	INT32               m_precomp_t;
	INT32               m_blend_enable;
	bool                m_pre_wrap;
	INT32               m_dzpix_enc;
	UINT8*              m_tmem;                /* pointer to texture cache for this polygon */
=======
	uint32_t              m_current_pix_cvg;
	uint32_t              m_current_mem_cvg;
	uint32_t              m_current_cvg_bit;
	int32_t               m_shift_a;
	int32_t               m_shift_b;
	int32_t               m_precomp_s;
	int32_t               m_precomp_t;
	int32_t               m_blend_enable;
	bool                m_pre_wrap;
	int32_t               m_dzpix_enc;
	uint8_t*              m_tmem;                /* pointer to texture cache for this polygon */
>>>>>>> upstream/master
	bool                m_start_span;
	rgbaint_t           m_clamp_diff[8];
};

struct z_decompress_entry_t
{
<<<<<<< HEAD
	UINT32 shift;
	UINT32 add;
=======
	uint32_t shift;
	uint32_t add;
>>>>>>> upstream/master
};

struct cv_mask_derivative_t
{
<<<<<<< HEAD
	UINT8 cvg;
	UINT8 cvbit;
	UINT8 xoff;
	UINT8 yoff;
=======
	uint8_t cvg;
	uint8_t cvbit;
	uint8_t xoff;
	uint8_t yoff;
>>>>>>> upstream/master
};

class span_param_t
{
	public:
		union
		{
<<<<<<< HEAD
			UINT32 w;
#ifdef LSB_FIRST
			struct { UINT16 l; INT16 h; } h;
#else
			struct { INT16 h; UINT16 l; } h;
=======
			uint32_t w;
#ifdef LSB_FIRST
			struct { uint16_t l; int16_t h; } h;
#else
			struct { int16_t h; uint16_t l; } h;
>>>>>>> upstream/master
#endif
		};
};

#endif // _VIDEO_N64TYPES_H_
