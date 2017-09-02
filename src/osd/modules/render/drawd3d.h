// license:BSD-3-Clause
// copyright-holders:Aaron Giles
//============================================================
//
//  drawd3d.h - Win32 Direct3D header
//
//============================================================

<<<<<<< HEAD
#ifndef __WIN_DRAWD3D__
#define __WIN_DRAWD3D__


#include "modules/render/d3d/d3dhlsl.h"

=======
#pragma once

#ifndef __WIN_DRAWD3D__
#define __WIN_DRAWD3D__

#ifdef OSD_WINDOWS

#include <windows.h>
#include <tchar.h>
#include <mmsystem.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>
#undef interface

#include "d3d/d3dcomm.h"
#include "sliderdirtynotifier.h"
#include "modules/lib/osdlib.h"
>>>>>>> upstream/master

//============================================================
//  CONSTANTS
//============================================================

#define VERTEX_BASE_FORMAT  (D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEX2)
#define VERTEX_BUFFER_SIZE  (40960*4+4)

//============================================================
//  TYPE DEFINITIONS
//============================================================

<<<<<<< HEAD
namespace d3d
{
class cache_target;
class render_target;
class renderer;

/* cache_target is a simple linked list containing only a rednerable target and texture, used for phosphor effects */
class cache_target
{
public:
	// construction/destruction
	cache_target() { }
	~cache_target();

	bool init(renderer *d3d, base *d3dintf, int width, int height, int prescale_x, int prescale_y);

	surface *last_target;
	texture *last_texture;

	int target_width;
	int target_height;

	int width;
	int height;

	int screen_index;

	cache_target *next;
	cache_target *prev;

	surface *bloom_target[11];
	texture *bloom_texture[11];
};

/* render_target is the information about a Direct3D render target chain */
class render_target
{
public:
	// construction/destruction
	render_target() { }
	~render_target();

	bool init(renderer *d3d, base *d3dintf, int width, int height, int prescale_x, int prescale_y);
	int next_index(int index) { return ++index > 1 ? 0 : index; }

	int target_width;
	int target_height;

	int prescale_x;
	int prescale_y;

	int width;
	int height;

	int screen_index;
	int page_index;

	surface *prescale_target[2];
	texture *prescale_texture[2];
	surface *native_target[2];
	texture *native_texture[2];

	render_target *next;
	render_target *prev;

	surface *bloom_target[11];
	texture *bloom_texture[11];
};

/* renderer is the information about Direct3D for the current screen */
class renderer : public osd_renderer
{
public:
	//renderer() { }
	renderer(osd_window *window);
	virtual ~renderer();

	virtual int create();
	virtual render_primitive_list *get_primitives();
	virtual int draw(const int update);
	virtual void save();
	virtual void record();
	virtual void toggle_fsfx();
	virtual void destroy();
=======
struct d3d_base
{
	// internal objects
	IDirect3D9 *d3dobj;
	bool        post_fx_available;

	osd::dynamic_module::ptr d3d9_dll;
};

class shaders;
struct hlsl_options;

/* renderer is the information about Direct3D for the current screen */
class renderer_d3d9 : public osd_renderer, public slider_dirty_notifier
{
public:
	renderer_d3d9(std::shared_ptr<osd_window> window);
	virtual ~renderer_d3d9();

	static bool init(running_machine &machine);
	static void exit();

	virtual int create() override;
	virtual render_primitive_list *get_primitives() override;
	virtual int draw(const int update) override;
	virtual void save() override;
	virtual void record() override;
	virtual void toggle_fsfx() override;
	virtual void add_audio_to_recording(const int16_t *buffer, int samples_this_frame) override;
	virtual std::vector<ui::menu_item> get_slider_list() override;
	virtual void set_sliders_dirty() override;
>>>>>>> upstream/master

	int                     initialize();

	int                     device_create(HWND device_HWND);
	int                     device_create_resources();
	void                    device_delete();
	void                    device_delete_resources();
<<<<<<< HEAD

	int                     device_verify_caps();
=======
	void                    update_presentation_parameters();
	void                    update_gamma_ramp();

	bool                    device_verify_caps();
>>>>>>> upstream/master
	int                     device_test_cooperative();

	int                     config_adapter_mode();
	void                    pick_best_mode();
	int                     get_adapter_for_monitor();

<<<<<<< HEAD
	int                     update_window_size();
=======
	bool                    update_window_size();
>>>>>>> upstream/master

	int                     pre_window_draw_check();
	void                    begin_frame();
	void                    end_frame();

<<<<<<< HEAD
	void                    draw_line(const render_primitive *prim);
	void                    draw_quad(const render_primitive *prim);
	void                    batch_vector(const render_primitive *prim, float line_time);
	void                    batch_vectors();

	vertex *                mesh_alloc(int numverts);

	void                    update_textures();

=======
	void                    draw_line(const render_primitive &prim);
	void                    draw_quad(const render_primitive &prim);
	void                    batch_vector(const render_primitive &prim);
	void                    batch_vectors(int vector_count);

	vertex *                mesh_alloc(int numverts);

>>>>>>> upstream/master
	void                    process_primitives();
	void                    primitive_flush_pending();

	void                    set_texture(texture_info *texture);
	void                    set_filter(int filter);
<<<<<<< HEAD
	void                    set_wrap(D3DTEXTUREADDRESS wrap);
	void                    set_modmode(DWORD modmode);
=======
	void                    set_wrap(unsigned int wrap);
	void                    set_modmode(int modmode);
>>>>>>> upstream/master
	void                    set_blendmode(int blendmode);
	void                    reset_render_states();

	// Setters / getters
<<<<<<< HEAD
	int                     get_adapter() { return m_adapter; }
	int                     get_width() { return m_width; }
	vec2f                   get_dims() { return vec2f(m_width, m_height); }
	int                     get_height() { return m_height; }
	int                     get_refresh() { return m_refresh; }

	device *                get_device() { return m_device; }
	present_parameters *    get_presentation() { return &m_presentation; }

	vertex_buffer *         get_vertex_buffer() { return m_vertexbuf; }
	vertex *                get_locked_buffer() { return m_lockedbuf; }
	VOID **                 get_locked_buffer_ptr() { return (VOID **)&m_lockedbuf; }
	void                    set_locked_buffer(vertex *lockedbuf) { m_lockedbuf = lockedbuf; }

	void                    set_restarting(bool restarting) { m_restarting = restarting; }
	bool                    is_mod2x_supported() { return (bool)m_mod2x_supported; }
	bool                    is_mod4x_supported() { return (bool)m_mod4x_supported; }

	D3DFORMAT               get_screen_format() { return m_screen_format; }
	D3DFORMAT               get_pixel_format() { return m_pixformat; }
	D3DDISPLAYMODE          get_origmode() { return m_origmode; }

	UINT32                  get_last_texture_flags() { return m_last_texture_flags; }

	texture_manager *       get_texture_manager() { return m_texture_manager; }
	texture_info *          get_default_texture() { return m_texture_manager->get_default_texture(); }
	texture_info *          get_vector_texture() { return m_texture_manager->get_vector_texture(); }

	shaders *               get_shaders() { return m_shaders; }
	hlsl_options *          get_shaders_options() { return m_shaders_options; }
=======
	int                     get_adapter() const { return m_adapter; }
	int                     get_width() const { return m_width; }
	vec2f                   get_dims() const { return vec2f(m_width, m_height); }
	int                     get_height() const { return m_height; }
	int                     get_refresh() const { return m_refresh; }

	IDirect3DDevice9 *      get_device() const { return m_device; }
	D3DPRESENT_PARAMETERS * get_presentation() { return &m_presentation; }

	IDirect3DVertexBuffer9 *get_vertex_buffer() const { return m_vertexbuf; }

	void                    set_toggle(bool toggle) { m_toggle = toggle; }

	D3DFORMAT               get_screen_format() const { return m_screen_format; }
	D3DFORMAT               get_pixel_format() const { return m_pixformat; }
	D3DDISPLAYMODE          get_origmode() const { return m_origmode; }

	uint32_t                  get_last_texture_flags() const { return m_last_texture_flags; }

	d3d_texture_manager *   get_texture_manager() const { return m_texture_manager; }
	texture_info *          get_default_texture();

	shaders *               get_shaders() const { return m_shaders; }
>>>>>>> upstream/master

private:
	int                     m_adapter;                  // ordinal adapter number
	int                     m_width;                    // current width
	int                     m_height;                   // current height
	int                     m_refresh;                  // current refresh rate
	int                     m_create_error_count;       // number of consecutive create errors

<<<<<<< HEAD
	device *                m_device;                   // pointer to the Direct3DDevice object
	int                     m_gamma_supported;          // is full screen gamma supported?
	present_parameters      m_presentation;             // set of presentation parameters
	D3DDISPLAYMODE          m_origmode;                 // original display mode for the adapter
	D3DFORMAT               m_pixformat;                // pixel format we are using

	vertex_buffer *         m_vertexbuf;                // pointer to the vertex buffer object
=======
	IDirect3DDevice9 *      m_device;                   // pointer to the Direct3DDevice object
	int                     m_gamma_supported;          // is full screen gamma supported?
	D3DPRESENT_PARAMETERS   m_presentation;             // set of presentation parameters
	D3DDISPLAYMODE          m_origmode;                 // original display mode for the adapter
	D3DFORMAT               m_pixformat;                // pixel format we are using

	IDirect3DVertexBuffer9 *m_vertexbuf;                // pointer to the vertex buffer object
>>>>>>> upstream/master
	vertex *                m_lockedbuf;                // pointer to the locked vertex buffer
	int                     m_numverts;                 // number of accumulated vertices

	vertex *                m_vectorbatch;              // pointer to the vector batch buffer
	int                     m_batchindex;               // current index into the vector batch

	poly_info               m_poly[VERTEX_BUFFER_SIZE/3];// array to hold polygons as they are created
	int                     m_numpolys;                 // number of accumulated polygons

<<<<<<< HEAD
	bool                    m_restarting;               // if we're restarting

	int                     m_mod2x_supported;          // is D3DTOP_MODULATE2X supported?
	int                     m_mod4x_supported;          // is D3DTOP_MODULATE4X supported?
	D3DFORMAT               m_screen_format;            // format to use for screen textures

	texture_info *          m_last_texture;             // previous texture
	UINT32                  m_last_texture_flags;       // previous texture flags
=======
	bool                    m_toggle;                   // if we're toggle fsfx

	D3DFORMAT               m_screen_format;            // format to use for screen textures

	texture_info *          m_last_texture;             // previous texture
	uint32_t                  m_last_texture_flags;       // previous texture flags
>>>>>>> upstream/master
	int                     m_last_blendenable;         // previous blendmode
	int                     m_last_blendop;             // previous blendmode
	int                     m_last_blendsrc;            // previous blendmode
	int                     m_last_blenddst;            // previous blendmode
	int                     m_last_filter;              // previous texture filter
<<<<<<< HEAD
	D3DTEXTUREADDRESS       m_last_wrap;                // previous wrap state
	DWORD                   m_last_modmode;             // previous texture modulation

	void *                  m_hlsl_buf;                 // HLSL vertex data
	shaders *               m_shaders;                  // HLSL interface
	hlsl_options *          m_shaders_options;          // HLSL options

	texture_manager *       m_texture_manager;          // texture manager

	int                     m_line_count;
};

}

#endif
=======
	uint32_t                  m_last_wrap;                // previous wrap state
	int                     m_last_modmode;             // previous texture modulation

	shaders *               m_shaders;                  // HLSL interface

	d3d_texture_manager *   m_texture_manager;          // texture manager
};

#endif // OSD_WINDOWS

#endif // __WIN_DRAWD3D__
>>>>>>> upstream/master
