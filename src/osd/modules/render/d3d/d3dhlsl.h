// license:BSD-3-Clause
// copyright-holders:Aaron Giles
//============================================================
//
//  drawd3d.c - Win32 Direct3D HLSL-specific header
//
//============================================================

#ifndef __WIN_D3DHLSL__
#define __WIN_D3DHLSL__

<<<<<<< HEAD
#include "aviio.h"

//============================================================
//  CONSTANTS
//============================================================

=======
#include <vector>
#include "../frontend/mame/ui/menuitem.h"
#include "../frontend/mame/ui/slider.h"
#include "modules/lib/osdlib.h"
>>>>>>> upstream/master

//============================================================
//  TYPE DEFINITIONS
//============================================================

<<<<<<< HEAD
struct slider_state;

namespace d3d
{
=======
// Typedefs for dynamically loaded functions
typedef HRESULT (WINAPI *d3dx_create_effect_from_file_fn)(LPDIRECT3DDEVICE9, LPCTSTR, const D3DXMACRO *, LPD3DXINCLUDE, DWORD, LPD3DXEFFECTPOOL, LPD3DXEFFECT *, LPD3DXBUFFER *);

>>>>>>> upstream/master
class effect;
class shaders;

class uniform
{
public:
	typedef enum
	{
		UT_VEC4,
		UT_VEC3,
		UT_VEC2,
		UT_FLOAT,
		UT_INT,
<<<<<<< HEAD
=======
		UT_BOOL,
>>>>>>> upstream/master
		UT_MATRIX,
		UT_SAMPLER
	} uniform_type;

	enum
	{
		CU_SCREEN_DIMS = 0,
<<<<<<< HEAD
		CU_SOURCE_DIMS,
		CU_SOURCE_RECT,
		CU_TARGET_DIMS,
		CU_QUAD_DIMS,

=======
		CU_SCREEN_COUNT,
		CU_SOURCE_DIMS,
		CU_TARGET_DIMS,
		CU_TARGET_SCALE,
		CU_QUAD_DIMS,

		CU_SWAP_XY,
		CU_VECTOR_SCREEN,

>>>>>>> upstream/master
		CU_NTSC_CCFREQ,
		CU_NTSC_A,
		CU_NTSC_B,
		CU_NTSC_O,
		CU_NTSC_P,
		CU_NTSC_NOTCH,
		CU_NTSC_YFREQ,
		CU_NTSC_IFREQ,
		CU_NTSC_QFREQ,
		CU_NTSC_HTIME,
		CU_NTSC_ENABLE,

		CU_COLOR_RED_RATIOS,
		CU_COLOR_GRN_RATIOS,
		CU_COLOR_BLU_RATIOS,
		CU_COLOR_OFFSET,
		CU_COLOR_SCALE,
		CU_COLOR_SATURATION,

		CU_CONVERGE_LINEAR_X,
		CU_CONVERGE_LINEAR_Y,
		CU_CONVERGE_RADIAL_X,
		CU_CONVERGE_RADIAL_Y,

		CU_FOCUS_SIZE,

		CU_PHOSPHOR_LIFE,
<<<<<<< HEAD
		CU_PHOSPHOR_IGNORE,

		CU_POST_VIGNETTING,
		CU_POST_CURVATURE,
=======

		CU_POST_VIGNETTING,
		CU_POST_DISTORTION,
		CU_POST_CUBIC_DISTORTION,
		CU_POST_DISTORT_CORNER,
>>>>>>> upstream/master
		CU_POST_ROUND_CORNER,
		CU_POST_SMOOTH_BORDER,
		CU_POST_REFLECTION,
		CU_POST_SHADOW_ALPHA,
		CU_POST_SHADOW_COUNT,
		CU_POST_SHADOW_UV,
		CU_POST_SHADOW_UV_OFFSET,
		CU_POST_SHADOW_DIMS,
		CU_POST_SCANLINE_ALPHA,
		CU_POST_SCANLINE_SCALE,
		CU_POST_SCANLINE_HEIGHT,
<<<<<<< HEAD
=======
		CU_POST_SCANLINE_VARIATION,
>>>>>>> upstream/master
		CU_POST_SCANLINE_BRIGHT_SCALE,
		CU_POST_SCANLINE_BRIGHT_OFFSET,
		CU_POST_POWER,
		CU_POST_FLOOR,

<<<<<<< HEAD
		CU_BLOOM_RESCALE,
		CU_BLOOM_LVL0123_WEIGHTS,
		CU_BLOOM_LVL4567_WEIGHTS,
		CU_BLOOM_LVL89A_WEIGHTS,

=======
>>>>>>> upstream/master
		CU_COUNT
	};

	uniform(effect *shader, const char *name, uniform_type type, int id);

<<<<<<< HEAD
	void        set_next(uniform *next);
	uniform *   get_next() { return m_next; }

	void        set(float x, float y, float z, float w);
	void        set(float x, float y, float z);
	void        set(float x, float y);
	void        set(float x);
	void        set(int x);
	void        set(matrix *mat);
	void        set(texture *tex);

	void        upload();
	void        update();

protected:
	uniform     *m_next;

	float       m_vec[4];
	int         m_ival;
	matrix      *m_mval;
	texture     *m_texture;
	int         m_count;
	uniform_type    m_type;
=======
	void        update();

protected:
	uniform_type m_type;
>>>>>>> upstream/master
	int         m_id;

	effect      *m_shader;
	D3DXHANDLE  m_handle;
};

class effect
{
	friend class uniform;

public:
<<<<<<< HEAD
	effect(shaders *shadersys, device *dev, const char *name, const char *path);
=======
	effect(shaders *shadersys, IDirect3DDevice9 *dev, const char *name, const char *path);
>>>>>>> upstream/master
	~effect();

	void        begin(UINT *passes, DWORD flags);
	void        begin_pass(UINT pass);

	void        end();
	void        end_pass();

	void        set_technique(const char *name);

	void        set_vector(D3DXHANDLE param, int count, float *vector);
	void        set_float(D3DXHANDLE param, float value);
	void        set_int(D3DXHANDLE param, int value);
	void        set_bool(D3DXHANDLE param, bool value);
<<<<<<< HEAD
	void        set_matrix(D3DXHANDLE param, matrix *matrix);
	void        set_texture(D3DXHANDLE param, texture *tex);
=======
	void        set_matrix(D3DXHANDLE param, D3DXMATRIX *matrix);
	void        set_texture(D3DXHANDLE param, IDirect3DTexture9 *tex);
>>>>>>> upstream/master

	void        add_uniform(const char *name, uniform::uniform_type type, int id);
	void        update_uniforms();

	D3DXHANDLE  get_parameter(D3DXHANDLE param, const char *name);

<<<<<<< HEAD
	ULONG       release();

=======
>>>>>>> upstream/master
	shaders*    get_shaders() { return m_shaders; }

	bool        is_valid() { return m_valid; }

private:
<<<<<<< HEAD
	uniform     *m_uniform_head;
	uniform     *m_uniform_tail;
=======
	std::vector<std::unique_ptr<uniform>> m_uniform_list;

>>>>>>> upstream/master
	ID3DXEffect *m_effect;
	shaders     *m_shaders;

	bool        m_valid;
};

<<<<<<< HEAD
class render_target;
class cache_target;
class renderer;
=======
class d3d_render_target;
class cache_target;
class renderer_d3d9;
class movie_recorder;
>>>>>>> upstream/master

/* hlsl_options is the information about runtime-mutable Direct3D HLSL options */
/* in the future this will be moved into an OSD/emu shared buffer */
struct hlsl_options
{
	bool                    params_init;
	bool                    params_dirty;
<<<<<<< HEAD
=======
	int                     shadow_mask_tile_mode;
>>>>>>> upstream/master
	float                   shadow_mask_alpha;
	char                    shadow_mask_texture[1024];
	int                     shadow_mask_count_x;
	int                     shadow_mask_count_y;
	float                   shadow_mask_u_size;
	float                   shadow_mask_v_size;
	float                   shadow_mask_u_offset;
	float                   shadow_mask_v_offset;
<<<<<<< HEAD
	float                   curvature;
=======
	float                   distortion;
	float                   cubic_distortion;
	float                   distort_corner;
>>>>>>> upstream/master
	float                   round_corner;
	float                   smooth_border;
	float                   reflection;
	float                   vignetting;
	float                   scanline_alpha;
	float                   scanline_scale;
	float                   scanline_height;
<<<<<<< HEAD
	float                   scanline_bright_scale;
	float                   scanline_bright_offset;
	float                   scanline_offset;
=======
	float                   scanline_variation;
	float                   scanline_bright_scale;
	float                   scanline_bright_offset;
	float                   scanline_jitter;
	float                   hum_bar_alpha;
>>>>>>> upstream/master
	float                   defocus[2];
	float                   converge_x[3];
	float                   converge_y[3];
	float                   radial_converge_x[3];
	float                   radial_converge_y[3];
	float                   red_ratio[3];
	float                   grn_ratio[3];
	float                   blu_ratio[3];
	float                   offset[3];
	float                   scale[3];
	float                   power[3];
	float                   floor[3];
	float                   phosphor[3];
	float                   saturation;

	// NTSC
<<<<<<< HEAD
	bool                    yiq_enable;
=======
	int                     yiq_enable;
	float                   yiq_jitter;
>>>>>>> upstream/master
	float                   yiq_cc;
	float                   yiq_a;
	float                   yiq_b;
	float                   yiq_o;
	float                   yiq_p;
	float                   yiq_n;
	float                   yiq_y;
	float                   yiq_i;
	float                   yiq_q;
	float                   yiq_scan_time;
	int                     yiq_phase_count;

	// Vectors
<<<<<<< HEAD
=======
	float                   vector_beam_smooth;
>>>>>>> upstream/master
	float                   vector_length_scale;
	float                   vector_length_ratio;

	// Bloom
<<<<<<< HEAD
=======
	int                     bloom_blend_mode;
>>>>>>> upstream/master
	float                   bloom_scale;
	float                   bloom_overdrive[3];
	float                   bloom_level0_weight;
	float                   bloom_level1_weight;
	float                   bloom_level2_weight;
	float                   bloom_level3_weight;
	float                   bloom_level4_weight;
	float                   bloom_level5_weight;
	float                   bloom_level6_weight;
	float                   bloom_level7_weight;
	float                   bloom_level8_weight;
<<<<<<< HEAD
	float                   bloom_level9_weight;
	float                   bloom_level10_weight;
};

class shaders
=======
};

struct slider_desc
{
	const char *                name;
	int                         minval;
	int                         defval;
	int                         maxval;
	int                         step;
	int                         slider_type;
	int                         screen_type;
	int                         id;
	float                       scale;
	const char *                format;
	std::vector<const char *>   strings;
};

class slider
{
public:
	slider(slider_desc *desc, void *value, bool *dirty) : m_desc(desc), m_value(value) { }

	int32_t update(std::string *str, int32_t newval);

private:
	slider_desc *   m_desc;
	void *          m_value;
};

class shaders : public slider_changed_notifier
>>>>>>> upstream/master
{
	friend class effect;
	friend class uniform;

public:
	// construction/destruction
	shaders();
	~shaders();

<<<<<<< HEAD
	void init(base *d3dintf, running_machine *machine, d3d::renderer *renderer);

	bool enabled() { return master_enable; }
	void toggle();

	bool vector_enabled() { return master_enable && vector_enable; }
	render_target* get_vector_target();
	void create_vector_target(render_primitive *prim);

	void begin_frame();
	void end_frame();
=======
	bool init(d3d_base *d3dintf, running_machine *machine, renderer_d3d9 *renderer);

	bool enabled() { return post_fx_enable && d3dintf->post_fx_available; }
	void toggle() { post_fx_enable = initialized && !post_fx_enable; }
>>>>>>> upstream/master

	void begin_draw();
	void end_draw();

<<<<<<< HEAD
	void init_effect_info(poly_info *poly);
	void render_quad(poly_info *poly, int vertnum);

	bool register_texture(texture_info *texture);
	bool register_prescaled_texture(texture_info *texture);
	bool add_render_target(renderer* d3d, texture_info* info, int width, int height, int xprescale, int yprescale);
	bool add_cache_target(renderer* d3d, texture_info* info, int width, int height, int xprescale, int yprescale, int screen_index);

	void window_save();
	void window_record();
	bool recording() { return avi_output_file != NULL; }

	void avi_update_snap(surface *surface);
	void render_snapshot(surface *surface);
	void record_texture();
	void init_fsfx_quad(void *vertbuf);

	void                    set_texture(texture_info *texture);
	render_target *         find_render_target(texture_info *info);
	void                    remove_render_target(texture_info *texture);
	void                    remove_render_target(int width, int height, UINT32 screen_index, UINT32 page_index);
	void                    remove_render_target(render_target *rt);

	int create_resources(bool reset);
	void delete_resources(bool reset);

	// slider-related functions
	slider_state *init_slider_list();

	enum slider_screen_type
	{
		SLIDER_SCREEN_TYPE_NONE = 0,
		SLIDER_SCREEN_TYPE_RASTER = 1,
		SLIDER_SCREEN_TYPE_VECTOR = 2,
		SLIDER_SCREEN_TYPE_LCD = 4
	};

	struct slider_desc
	{
		const char *        name;
		int                 minval;
		int                 defval;
		int                 maxval;
		int                 step;
		int                 screen_type;
		INT32(*adjustor)(running_machine &, void *, std::string *, INT32);
	};

private:
	void                    blit(surface *dst, bool clear_dst, D3DPRIMITIVETYPE prim_type, UINT32 prim_index, UINT32 prim_count);
	void                    enumerate_screens();

	void                    end_avi_recording();
	void                    begin_avi_recording(const char *name);

	bool                    register_texture(texture_info *texture, int width, int height, int xscale, int yscale);

	render_target*          find_render_target(int width, int height, UINT32 screen_index, UINT32 page_index);
	cache_target *          find_cache_target(UINT32 screen_index, int width, int height);
	void                    remove_cache_target(cache_target *cache);

	// Shader passes
	int                     ntsc_pass(render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     color_convolution_pass(render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     prescale_pass(render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     deconverge_pass(render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     defocus_pass(render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     phosphor_pass(render_target *rt, cache_target *ct, int source_index, poly_info *poly, int vertnum);
	int                     post_pass(render_target *rt, int source_index, poly_info *poly, int vertnum, bool prepare_bloom);
	int                     downsample_pass(render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     bloom_pass(render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     distortion_pass(render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     vector_pass(render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     vector_buffer_pass(render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     screen_pass(render_target *rt, int source_index, poly_info *poly, int vertnum);
	void                    menu_pass(poly_info *poly, int vertnum);

	base *                  d3dintf;                    // D3D interface

	running_machine *       machine;
	d3d::renderer *         d3d;                        // D3D renderer

	bool                    master_enable;              // overall enable flag
	bool                    vector_enable;              // vector post-processing enable flag
	bool                    paused;                     // whether or not rendering is currently paused
	int                     num_screens;                // number of emulated physical screens
	int                     curr_screen;                // current screen for render target operations
	int                     curr_frame;                 // current frame (0/1) of a screen for render target operations
	int                     lastidx;                    // index of the last-encountered target
	bool                    write_ini;                  // enable external ini saving
	bool                    read_ini;                   // enable external ini loading
	int                     hlsl_prescale_x;            // hlsl prescale x
	int                     hlsl_prescale_y;            // hlsl prescale y
	float                   bloom_dims[11][2];          // bloom texture dimensions
	int                     bloom_count;                // count of used bloom textures
	int                     preset;                     // preset, if relevant
	bitmap_argb32           shadow_bitmap;              // shadow mask bitmap for post-processing shader
	texture_info *          shadow_texture;             // shadow mask texture for post-processing shader
	hlsl_options *          options;                    // current options
	D3DPRIMITIVETYPE        vecbuf_type;
	UINT32                  vecbuf_index;
	UINT32                  vecbuf_count;

	avi_file *              avi_output_file;            // AVI file
	bitmap_rgb32            avi_snap;                   // AVI snapshot
	int                     avi_frame;                  // AVI frame
	attotime                avi_frame_period;           // AVI frame period
	attotime                avi_next_frame_time;        // AVI next frame time
	surface *               avi_copy_surface;           // AVI destination surface in system memory
	texture *               avi_copy_texture;           // AVI destination texture in system memory
	surface *               avi_final_target;           // AVI upscaled surface
	texture *               avi_final_texture;          // AVI upscaled texture

	surface *               black_surface;              // black dummy surface
	texture *               black_texture;              // black dummy texture

	bool                    render_snap;                // whether or not to take HLSL post-render snapshot
	bool                    snap_rendered;              // whether we just rendered our HLSL post-render shot or not
	surface *               snap_copy_target;           // snapshot destination surface in system memory
	texture *               snap_copy_texture;          // snapshot destination surface in system memory
	surface *               snap_target;                // snapshot upscaled surface
	texture *               snap_texture;               // snapshot upscaled texture
	int                     snap_width;                 // snapshot width
	int                     snap_height;                // snapshot height
	bool                    lines_pending;              // whether or not we have lines to flush on the next quad

	bool                    initialized;                // whether or not we're initialize

	// HLSL effects
	surface *               backbuffer;                 // pointer to our device's backbuffer
=======
	void render_quad(poly_info *poly, int vertnum);

	bool create_vector_target(render_primitive *prim, int screen);
	d3d_render_target* get_vector_target(render_primitive *prim, int screen);
	bool create_texture_target(render_primitive *prim, int width, int height, int screen);
	d3d_render_target* get_texture_target(render_primitive *prim, int width, int height, int screen);
	bool add_render_target(renderer_d3d9* d3d, render_primitive *prim, int source_width, int source_height, int source_screen, int target_width, int target_height);

	void save_snapshot();
	void record_movie();
	void record_audio(const int16_t *buffer, int samples_this_frame);

	void init_fsfx_quad();

	void set_texture(texture_info *info);
	void remove_render_target(int source_width, int source_height, uint32_t screen_index);
	void remove_render_target(d3d_render_target *rt);

	int create_resources();
	void delete_resources();

	// slider-related functions
	virtual int32_t slider_changed(running_machine &machine, void *arg, int /*id*/, std::string *str, int32_t newval) override;
	slider_state* slider_alloc(running_machine &machine, int id, const char *title, int32_t minval, int32_t defval, int32_t maxval, int32_t incval, void *arg);
	void init_slider_list();
	std::vector<ui::menu_item> get_slider_list() { return m_sliders; }
	void *get_slider_option(int id, int index = 0);

private:
	void                    blit(IDirect3DSurface9 *dst, bool clear_dst, D3DPRIMITIVETYPE prim_type, uint32_t prim_index, uint32_t prim_count);
	void                    enumerate_screens();

	void                    render_snapshot(IDirect3DSurface9 *surface);
	// Time since last call, only updates once per render of all screens
	double                  delta_time() { return delta_t; }
	d3d_render_target*      find_render_target(int source_width, int source_height, uint32_t screen_index);

	rgb_t                   apply_color_convolution(rgb_t color);

	// Shader passes
	int                     ntsc_pass(d3d_render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     color_convolution_pass(d3d_render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     prescale_pass(d3d_render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     deconverge_pass(d3d_render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     defocus_pass(d3d_render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     phosphor_pass(d3d_render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     post_pass(d3d_render_target *rt, int source_index, poly_info *poly, int vertnum, bool prepare_bloom);
	int                     downsample_pass(d3d_render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     bloom_pass(d3d_render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     distortion_pass(d3d_render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     vector_pass(d3d_render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     vector_buffer_pass(d3d_render_target *rt, int source_index, poly_info *poly, int vertnum);
	int                     screen_pass(d3d_render_target *rt, int source_index, poly_info *poly, int vertnum);
	void                    ui_pass(poly_info *poly, int vertnum);

	d3d_base *              d3dintf;                    // D3D interface

	running_machine *       machine;
	renderer_d3d9 *         d3d;                        // D3D renderer

	bool                    post_fx_enable;             // overall enable flag
	bool                    oversampling_enable;        // oversampling enable flag
	int                     num_screens;                // number of emulated physical screens
	int                     curr_screen;                // current screen for render target operations
	double                  acc_t;                      // accumulated machine time
	double                  delta_t;                    // data for delta_time
	bitmap_argb32           shadow_bitmap;              // shadow mask bitmap for post-processing shader
	texture_info *          shadow_texture;             // shadow mask texture for post-processing shader
	hlsl_options *          options;                    // current options

	IDirect3DSurface9 *     black_surface;              // black dummy surface
	IDirect3DTexture9 *     black_texture;              // black dummy texture

	bool                    recording_movie;            // ongoing movie recording
	std::unique_ptr<movie_recorder> recorder;           // HLSL post-render movie recorder

	bool                    render_snap;                // whether or not to take HLSL post-render snapshot
	IDirect3DSurface9 *     snap_copy_target;           // snapshot destination surface in system memory
	IDirect3DTexture9 *     snap_copy_texture;          // snapshot destination surface in system memory
	IDirect3DSurface9 *     snap_target;                // snapshot upscaled surface
	IDirect3DTexture9 *     snap_texture;               // snapshot upscaled texture
	int                     snap_width;                 // snapshot width
	int                     snap_height;                // snapshot height

	bool                    initialized;                // whether or not we're initialized

	// HLSL effects
	IDirect3DSurface9 *     backbuffer;                 // pointer to our device's backbuffer
>>>>>>> upstream/master
	effect *                curr_effect;                // pointer to the currently active effect object
	effect *                default_effect;             // pointer to the primary-effect object
	effect *                prescale_effect;            // pointer to the prescale-effect object
	effect *                post_effect;                // pointer to the post-effect object
	effect *                distortion_effect;          // pointer to the distortion-effect object
	effect *                focus_effect;               // pointer to the focus-effect object
	effect *                phosphor_effect;            // pointer to the phosphor-effect object
	effect *                deconverge_effect;          // pointer to the deconvergence-effect object
	effect *                color_effect;               // pointer to the color-effect object
<<<<<<< HEAD
	effect *                yiq_encode_effect;          // pointer to the YIQ encoder effect object
	effect *                yiq_decode_effect;          // pointer to the YIQ decoder effect object
	effect *                bloom_effect;               // pointer to the bloom composite effect
	effect *                downsample_effect;          // pointer to the bloom downsample effect
	effect *                vector_effect;              // pointer to the vector-effect object
	vertex *                fsfx_vertices;              // pointer to our full-screen-quad object

	texture_info *          curr_texture;
	render_target *         curr_render_target;
	poly_info *             curr_poly;
	render_target *         targethead;
	cache_target *          cachehead;

	static slider_desc      s_sliders[];
	static hlsl_options     last_options;               // last used options
};

}
=======
	effect *                ntsc_effect;                // pointer to the NTSC effect object
	effect *                bloom_effect;               // pointer to the bloom composite effect
	effect *                downsample_effect;          // pointer to the bloom downsample effect
	effect *                vector_effect;              // pointer to the vector-effect object

	texture_info *          curr_texture;
	d3d_render_target *     curr_render_target;
	poly_info *             curr_poly;

	std::vector<std::unique_ptr<d3d_render_target>> m_render_target_list;

	std::vector<slider*>    internal_sliders;
	std::vector<ui::menu_item> m_sliders;

	static slider_desc      s_sliders[];
	static hlsl_options     last_options;               // last used options
	static char             last_system_name[16];       // last used system

	osd::dynamic_module::ptr d3dx9_dll;
	d3dx_create_effect_from_file_fn d3dx_create_effect_from_file_ptr;
};
>>>>>>> upstream/master

#endif
