// license:BSD-3-Clause
// copyright-holders:Olivier Galibert, R. Belmont
//============================================================
//
//  window.c - SDL window handling
//
//  SDLMAME by Olivier Galibert and R. Belmont
//
//============================================================

#ifdef SDLMAME_WIN32
<<<<<<< HEAD
#define WIN32_LEAN_AND_MEAN
=======
>>>>>>> upstream/master
#include <windows.h>
#endif

// standard SDL headers
<<<<<<< HEAD
#include "sdlinc.h"

#if (SDLMAME_SDL2)
#include <SDL2/SDL_thread.h>
#else
#include <SDL/SDL_thread.h>
#endif
=======
#include <SDL2/SDL.h>
>>>>>>> upstream/master

// standard C headers
#include <math.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
<<<<<<< HEAD
=======
#include <list>
#include <memory>
>>>>>>> upstream/master

// MAME headers

#include "emu.h"
#include "emuopts.h"
<<<<<<< HEAD
#include "ui/ui.h"

=======
#include "render.h"
#include "ui/uimain.h"
>>>>>>> upstream/master

// OSD headers

#include "window.h"
<<<<<<< HEAD
#include "input.h"
#include "osdsdl.h"
=======
#include "osdsdl.h"
#include "modules/render/drawbgfx.h"
#include "modules/render/drawsdl.h"
#include "modules/render/draw13.h"
#include "modules/monitor/monitor_common.h"
#if (USE_OPENGL)
#include "modules/render/drawogl.h"
#endif
>>>>>>> upstream/master

//============================================================
//  PARAMETERS
//============================================================

// these are arbitrary values since AFAIK there's no way to make X/SDL tell you
#define WINDOW_DECORATION_WIDTH (8) // should be more than plenty
#define WINDOW_DECORATION_HEIGHT (48)   // title bar + bottom drag region

<<<<<<< HEAD
#ifdef MAME_DEBUG
//#define ASSERT_USE(x) do { printf("%x %x\n", (int) SDL_ThreadID(), x); assert_always(SDL_ThreadID() == x, "Wrong Thread"); } while (0)
#define ASSERT_USE(x)   do { SDL_threadID _thid = SDL_ThreadID(); assert_always( _thid == x, "Wrong Thread"); } while (0)
#else
#define ASSERT_USE(x)   do {} while (0)
//#define ASSERT_USE(x) assert(SDL_ThreadID() == x)
#endif

#define ASSERT_REDRAW_THREAD()  ASSERT_USE(window_threadid)
#define ASSERT_WINDOW_THREAD()  ASSERT_USE(window_threadid)
#define ASSERT_MAIN_THREAD()    ASSERT_USE(main_threadid)

=======
>>>>>>> upstream/master
// minimum window dimension
#define MIN_WINDOW_DIM                  200

#ifndef SDLMAME_WIN32
#define WMSZ_TOP            (0)
#define WMSZ_BOTTOM         (1)
#define WMSZ_BOTTOMLEFT     (2)
#define WMSZ_BOTTOMRIGHT    (3)
#define WMSZ_LEFT           (4)
#define WMSZ_TOPLEFT        (5)
#define WMSZ_TOPRIGHT       (6)
#define WMSZ_RIGHT          (7)
#endif

<<<<<<< HEAD
//============================================================
//  GLOBAL VARIABLES
//============================================================

sdl_window_info *sdl_window_list;


//============================================================
//  LOCAL VARIABLES
//============================================================

static sdl_window_info **last_window_ptr;

// event handling
static int multithreading_enabled;
static osd_work_queue *work_queue;

#if !(SDLMAME_SDL2) && (!defined(SDLMAME_EMSCRIPTEN))
typedef int SDL_threadID;
#endif

static SDL_threadID main_threadid;
static SDL_threadID window_threadid;
=======
#define SDL_VERSION_EQUALS(v1, vnum2) (SDL_VERSIONNUM(v1.major, v1.minor, v1.patch) == vnum2)

class SDL_DM_Wrapper
{
public:
	SDL_DisplayMode mode;
};
>>>>>>> upstream/master

// debugger
//static int in_background;

<<<<<<< HEAD
static osd_draw_callbacks draw;

struct worker_param {
	worker_param()
	: m_window(NULL), m_list(NULL), m_resize_new_width(0), m_resize_new_height(0)
	{
	}
	worker_param(sdl_window_info *awindow, render_primitive_list &alist)
	: m_window(awindow), m_list(&alist), m_resize_new_width(0), m_resize_new_height(0)
	{
	}
	worker_param(sdl_window_info *awindow, int anew_width, int anew_height)
	: m_window(awindow), m_list(NULL), m_resize_new_width(anew_width), m_resize_new_height(anew_height)
	{
	}
	worker_param(sdl_window_info *awindow)
	: m_window(awindow), m_list(NULL), m_resize_new_width(0), m_resize_new_height(0)
	{
	}
	sdl_window_info *window() const { assert(m_window != NULL); return m_window; }
	render_primitive_list *list() const { return m_list; }
	int new_width() const { return m_resize_new_width; }
	int new_height() const { return m_resize_new_height; }
	// FIXME: only needed for window set-up which returns an error.
	void set_window(sdl_window_info *window) { m_window = window; }
private:
	sdl_window_info *m_window;
	render_primitive_list *m_list;
	int m_resize_new_width;
	int m_resize_new_height;
};

=======
>>>>>>> upstream/master

//============================================================
//  PROTOTYPES
//============================================================

<<<<<<< HEAD
static void sdlwindow_sync(void);

//============================================================
//  execute_async
//============================================================


INLINE void execute_async(osd_work_callback callback, const worker_param &wp)
{
	worker_param *wp_temp = (worker_param *) osd_malloc(sizeof(worker_param));
	*wp_temp = wp;

	if (multithreading_enabled)
	{
		osd_work_item_queue(work_queue, callback, (void *) wp_temp, WORK_ITEM_FLAG_AUTO_RELEASE);
	} else
		callback((void *) wp_temp, 0);
}

INLINE void execute_sync(osd_work_callback callback, const worker_param &wp)
{
	worker_param *wp_temp = (worker_param *) osd_malloc(sizeof(worker_param));
	*wp_temp = wp;

	callback((void *) wp_temp, 0);
}


//============================================================
//  execute_async_wait
//============================================================

INLINE void execute_async_wait(osd_work_callback callback, const worker_param &wp)
{
	execute_async(callback, wp);
	sdlwindow_sync();
}


//============================================================
//  sdlwindow_thread_id
//  (window thread)
//============================================================

static OSDWORK_CALLBACK(sdlwindow_thread_id)
{
	window_threadid = SDL_ThreadID();

	if (SDLMAME_INIT_IN_WORKER_THREAD)
	{
#if (SDLMAME_SDL2)
		if (SDL_InitSubSystem(SDL_INIT_TIMER|SDL_INIT_AUDIO| SDL_INIT_VIDEO| SDL_INIT_JOYSTICK|SDL_INIT_NOPARACHUTE))
#else
		if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO| SDL_INIT_VIDEO| SDL_INIT_JOYSTICK|SDL_INIT_NOPARACHUTE))
#endif
		{
			osd_printf_error("Could not initialize SDL: %s.\n", SDL_GetError());
			exit(-1);
		}
	}
	return NULL;
}

=======
>>>>>>> upstream/master

//============================================================
//  window_init
//  (main thread)
//============================================================

bool sdl_osd_interface::window_init()
{
	osd_printf_verbose("Enter sdlwindow_init\n");
<<<<<<< HEAD
	// determine if we are using multithreading or not
	multithreading_enabled = options().multithreading();

	// get the main thread ID before anything else
	main_threadid = SDL_ThreadID();

	// if multithreading, create a thread to run the windows
	if (multithreading_enabled)
	{
		// create a thread to run the windows from
		work_queue = osd_work_queue_alloc(WORK_QUEUE_FLAG_IO);
		if (work_queue == NULL)
			return false;
		osd_work_item_queue(work_queue, &sdlwindow_thread_id, NULL, WORK_ITEM_FLAG_AUTO_RELEASE);
		sdlwindow_sync();
	}
	else
	{
		// otherwise, treat the window thread as the main thread
		//window_threadid = main_threadid;
		sdlwindow_thread_id(NULL, 0);
	}

	// initialize the drawers
#if USE_OPENGL
	if (video_config.mode == VIDEO_MODE_OPENGL)
	{
		if (drawogl_init(machine(), &draw))
			video_config.mode = VIDEO_MODE_SOFT;
	}
#endif
#if SDLMAME_SDL2
	if (video_config.mode == VIDEO_MODE_SDL2ACCEL)
	{
		if (drawsdl2_init(machine(), &draw))
			video_config.mode = VIDEO_MODE_SOFT;
	}
#endif
#ifdef USE_BGFX
	if (video_config.mode == VIDEO_MODE_BGFX)
	{
		if (drawbgfx_init(machine(), &draw))
			video_config.mode = VIDEO_MODE_SOFT;
	}
#endif
	if (video_config.mode == VIDEO_MODE_SOFT)
	{
		if (drawsdl_init(&draw))
			return false;
	}

#if SDLMAME_SDL2
=======

	// initialize the drawers

	switch (video_config.mode)
	{
		case VIDEO_MODE_BGFX:
			renderer_bgfx::init(machine());
			break;
#if (USE_OPENGL)
		case VIDEO_MODE_OPENGL:
			renderer_ogl::init(machine());
			break;
#endif
		case VIDEO_MODE_SDL2ACCEL:
			renderer_sdl2::init(machine());
			break;
		case VIDEO_MODE_SOFT:
			renderer_sdl1::init(machine());
			break;
	}

>>>>>>> upstream/master
	/* We may want to set a number of the hints SDL2 provides.
	 * The code below will document which hints were set.
	 */
	const char * hints[] = { SDL_HINT_FRAMEBUFFER_ACCELERATION,
			SDL_HINT_RENDER_DRIVER, SDL_HINT_RENDER_OPENGL_SHADERS,
			SDL_HINT_RENDER_SCALE_QUALITY,
			SDL_HINT_RENDER_VSYNC,
			SDL_HINT_VIDEO_X11_XVIDMODE, SDL_HINT_VIDEO_X11_XINERAMA,
			SDL_HINT_VIDEO_X11_XRANDR, SDL_HINT_GRAB_KEYBOARD,
			SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, SDL_HINT_IDLE_TIMER_DISABLED,
			SDL_HINT_ORIENTATIONS,
			SDL_HINT_XINPUT_ENABLED, SDL_HINT_GAMECONTROLLERCONFIG,
			SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, SDL_HINT_ALLOW_TOPMOST,
			SDL_HINT_TIMER_RESOLUTION,
#if SDL_VERSION_ATLEAST(2, 0, 2)
			SDL_HINT_RENDER_DIRECT3D_THREADSAFE, SDL_HINT_VIDEO_ALLOW_SCREENSAVER,
			SDL_HINT_ACCELEROMETER_AS_JOYSTICK, SDL_HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK,
			SDL_HINT_VIDEO_WIN_D3DCOMPILER, SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT,
			SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES, SDL_HINT_MOUSE_RELATIVE_MODE_WARP,
#endif
#if SDL_VERSION_ATLEAST(2, 0, 3)
			SDL_HINT_RENDER_DIRECT3D11_DEBUG, SDL_HINT_VIDEO_HIGHDPI_DISABLED,
			SDL_HINT_WINRT_PRIVACY_POLICY_URL, SDL_HINT_WINRT_PRIVACY_POLICY_LABEL,
			SDL_HINT_WINRT_HANDLE_BACK_BUTTON,
#endif
<<<<<<< HEAD
			NULL
	};

	osd_printf_verbose("\nHints:\n");
	for (int i = 0; hints[i] != NULL; i++)
		osd_printf_verbose("\t%-40s %s\n", hints[i], SDL_GetHint(hints[i]));
#endif

	// set up the window list
	last_window_ptr = &sdl_window_list;
=======
			nullptr
	};

	osd_printf_verbose("\nHints:\n");
	for (int i = 0; hints[i] != nullptr; i++)
		osd_printf_verbose("\t%-40s %s\n", hints[i], SDL_GetHint(hints[i]));

	// set up the window list
>>>>>>> upstream/master
	osd_printf_verbose("Leave sdlwindow_init\n");
	return true;
}


<<<<<<< HEAD
//============================================================
//  sdlwindow_sync
//============================================================

static void sdlwindow_sync(void)
{
	if (multithreading_enabled)
	{
		// Fallback
		while (!osd_work_queue_wait(work_queue, osd_ticks_per_second()*10))
		{
			osd_printf_warning("sdlwindow_sync: Sleeping...\n");
			osd_sleep(100000);
=======
void sdl_osd_interface::update_slider_list()
{
	for (auto window : osd_common_t::s_window_list)
	{
		// check if any window has dirty sliders
		if (window->renderer().sliders_dirty())
		{
			build_slider_list();
			return;
>>>>>>> upstream/master
		}
	}
}

<<<<<<< HEAD
=======
void sdl_osd_interface::build_slider_list()
{
	m_sliders.clear();

	for (auto window : osd_common_t::s_window_list)
	{
		std::vector<ui::menu_item> window_sliders = window->renderer().get_slider_list();
		m_sliders.insert(m_sliders.end(), window_sliders.begin(), window_sliders.end());
	}
}
>>>>>>> upstream/master

//============================================================
//  sdlwindow_exit
//  (main thread)
//============================================================

<<<<<<< HEAD
static OSDWORK_CALLBACK( sdlwindow_exit_wt )
{
	if (SDLMAME_INIT_IN_WORKER_THREAD)
		SDL_Quit();

	if (param)
		osd_free(param);
	return NULL;
}


void sdl_osd_interface::window_exit()
{
	worker_param wp_dummy;

	ASSERT_MAIN_THREAD();

	osd_printf_verbose("Enter sdlwindow_exit\n");

	// free all the windows
	while (sdl_window_list != NULL)
	{
		sdl_window_info *temp = sdl_window_list;
		sdl_window_list = temp->m_next;
		temp->destroy();
		// free the window itself
		global_free(temp);
	}

	// if we're multithreaded, clean up the window thread
	if (multithreading_enabled)
	{
		sdlwindow_sync();
	}

	// kill the drawers
	(*draw.exit)();

	execute_async_wait(&sdlwindow_exit_wt, wp_dummy);

	if (multithreading_enabled)
	{
		osd_work_queue_wait(work_queue, 1000000);
		osd_work_queue_free(work_queue);
	}
	osd_printf_verbose("Leave sdlwindow_exit\n");

}


//============================================================
//  sdlwindow_blit_surface_size
//============================================================

INLINE int better_mode(int width0, int height0, int width1, int height1, float desired_aspect)
{
	float aspect0 = (float)width0 / (float)height0;
	float aspect1 = (float)width1 / (float)height1;
	return (fabs(desired_aspect - aspect0) < fabs(desired_aspect - aspect1)) ? 0 : 1;
}

osd_dim sdl_window_info::blit_surface_size()
{
	osd_dim window_dim = get_size();

	int newwidth, newheight;
	int xscale = 1, yscale = 1;
	float desired_aspect = 1.0f;
	INT32 target_width = window_dim.width();
	INT32 target_height = window_dim.height();

	// start with the minimum size
	m_target->compute_minimum_size(newwidth, newheight);

	// compute the appropriate visible area if we're trying to keepaspect
	if (video_config.keepaspect)
	{
		// make sure the monitor is up-to-date
		m_target->compute_visible_area(target_width, target_height, m_monitor->aspect(), m_target->orientation(), target_width, target_height);
		desired_aspect = (float)target_width / (float)target_height;
	}

	// non-integer scaling - often gives more pleasing results in full screen
	if (!video_config.fullstretch)
	{
		// compute maximum integral scaling to fit the window
		xscale = (target_width + 2) / newwidth;
		yscale = (target_height + 2) / newheight;

		// try a little harder to keep the aspect ratio if desired
		if (video_config.keepaspect)
		{
			// if we could stretch more in the X direction, and that makes a better fit, bump the xscale
			while (newwidth * (xscale + 1) <= window_dim.width() &&
				better_mode(newwidth * xscale, newheight * yscale, newwidth * (xscale + 1), newheight * yscale, desired_aspect))
				xscale++;

			// if we could stretch more in the Y direction, and that makes a better fit, bump the yscale
			while (newheight * (yscale + 1) <= window_dim.height() &&
				better_mode(newwidth * xscale, newheight * yscale, newwidth * xscale, newheight * (yscale + 1), desired_aspect))
				yscale++;

			// now that we've maxed out, see if backing off the maximally stretched one makes a better fit
			if (window_dim.width() - newwidth * xscale < window_dim.height() - newheight * yscale)
			{
				while (better_mode(newwidth * xscale, newheight * yscale, newwidth * (xscale - 1), newheight * yscale, desired_aspect) && (xscale >= 0))
					xscale--;
			}
			else
			{
				while (better_mode(newwidth * xscale, newheight * yscale, newwidth * xscale, newheight * (yscale - 1), desired_aspect) && (yscale >= 0))
					yscale--;
			}
		}

		// ensure at least a scale factor of 1
		if (xscale <= 0) xscale = 1;
		if (yscale <= 0) yscale = 1;

		// apply the final scale
		newwidth *= xscale;
		newheight *= yscale;
	}
	else
	{
		newwidth = target_width;
		newheight = target_height;
	}

	//FIXME: really necessary to distinguish for yuv_modes ?
	if (m_target->zoom_to_screen()
		&& (video_config.scale_mode == VIDEO_SCALE_MODE_NONE ))
		newwidth = window_dim.width();

	return osd_dim(newwidth, newheight);
=======
void sdl_osd_interface::window_exit()
{
	osd_printf_verbose("Enter sdlwindow_exit\n");

	// free all the windows
	while (!osd_common_t::s_window_list.empty())
	{
		auto window = osd_common_t::s_window_list.front();

		// Part of destroy removes the window from the list
		window->destroy();
	}

	switch(video_config.mode)
	{
		case VIDEO_MODE_SDL2ACCEL:
			renderer_sdl1::exit();
			break;
		case VIDEO_MODE_SOFT:
			renderer_sdl1::exit();
			break;
		case VIDEO_MODE_BGFX:
			renderer_bgfx::exit();
			break;
#if (USE_OPENGL)
		case VIDEO_MODE_OPENGL:
			renderer_ogl::exit();
			break;
#endif
		default:
			break;
	}
	osd_printf_verbose("Leave sdlwindow_exit\n");
}

void sdl_window_info::capture_pointer()
{
	if (!m_mouse_captured)
	{
		SDL_SetWindowGrab(platform_window(), SDL_TRUE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		m_mouse_captured = true;
	}
}

void sdl_window_info::release_pointer()
{
	if (m_mouse_captured)
	{
		SDL_SetWindowGrab(platform_window(), SDL_FALSE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
		m_mouse_captured = false;
	}
}

void sdl_window_info::hide_pointer()
{
	if (!m_mouse_hidden)
	{
		SDL_ShowCursor(SDL_DISABLE);
		m_mouse_hidden = true;
	}
}

void sdl_window_info::show_pointer()
{
	if (m_mouse_hidden)
	{
		SDL_ShowCursor(SDL_ENABLE);
		m_mouse_hidden = false;
	}
>>>>>>> upstream/master
}


//============================================================
//  sdlwindow_resize
<<<<<<< HEAD
//  (main thread)
//============================================================

OSDWORK_CALLBACK( sdl_window_info::sdlwindow_resize_wt )
{
	worker_param *      wp = (worker_param *) param;
	sdl_window_info *   window = wp->window();
	int width = wp->new_width();
	int height = wp->new_height();

	ASSERT_WINDOW_THREAD();

#if (SDLMAME_SDL2)
	SDL_SetWindowSize(window->sdl_window(), width, height);
#else
	SDL_FreeSurface(window->m_sdlsurf);

	window->m_sdlsurf = SDL_SetVideoMode(width, height, 0,
			SDL_SWSURFACE | SDL_ANYFORMAT | window->m_extra_flags);
#endif
	window->renderer().notify_changed();

	osd_free(wp);
	return NULL;
}

void sdl_window_info::resize(INT32 width, INT32 height)
{
	ASSERT_MAIN_THREAD();

	osd_dim cd = get_size();

	if (width != cd.width() || height != cd.height())
		execute_async_wait(&sdlwindow_resize_wt, worker_param(this, width, height));
=======
//============================================================

void sdl_window_info::resize(int32_t width, int32_t height)
{
	osd_dim cd = get_size();

	if (width != cd.width() || height != cd.height())
	{
		SDL_SetWindowSize(platform_window(), width, height);
		renderer().notify_changed();
	}
>>>>>>> upstream/master
}


//============================================================
//  sdlwindow_clear_surface
<<<<<<< HEAD
//  (window thread)
//============================================================

OSDWORK_CALLBACK( sdl_window_info::notify_changed_wt )
{
	worker_param *wp = (worker_param *) param;
	sdl_window_info *window = wp->window();

	ASSERT_WINDOW_THREAD();

	window->renderer().notify_changed();
	osd_free(wp);
	return NULL;
}

void sdl_window_info::notify_changed()
{
	worker_param wp;

	if (SDL_ThreadID() == main_threadid)
	{
		execute_async_wait(&notify_changed_wt, worker_param(this));
	}
	else
		execute_sync(&notify_changed_wt, worker_param(this));
=======
//============================================================

void sdl_window_info::notify_changed()
{
	renderer().notify_changed();
>>>>>>> upstream/master
}


//============================================================
//  sdlwindow_toggle_full_screen
<<<<<<< HEAD
//  (main thread)
//============================================================

OSDWORK_CALLBACK( sdl_window_info::sdlwindow_toggle_full_screen_wt )
{
	worker_param *wp = (worker_param *) param;
	sdl_window_info *window = wp->window();

	ASSERT_WINDOW_THREAD();

	// if we are in debug mode, never go full screen
	if (window->machine().debug_flags & DEBUG_FLAG_OSD_ENABLED)
		return NULL;

	// If we are going fullscreen (leaving windowed) remember our windowed size
	if (!window->fullscreen())
	{
		window->m_windowed_dim = window->get_size();
	}

	window->renderer().destroy();
	global_free(window->m_renderer);
	window->m_renderer = NULL;

#if (SDLMAME_SDL2)
=======
//============================================================

void sdl_window_info::toggle_full_screen()
{
	// if we are in debug mode, never go full screen
	if (machine().debug_flags & DEBUG_FLAG_OSD_ENABLED)
		return;

	// If we are going fullscreen (leaving windowed) remember our windowed size
	if (!fullscreen())
	{
		m_windowed_dim = get_size();
	}

	// reset UI to main menu
	machine().ui().menu_reset();
	// kill off the drawers
	renderer_reset();
//  set_platform_window(nullptr);
>>>>>>> upstream/master
	bool is_osx = false;
#ifdef SDLMAME_MACOSX
	// FIXME: This is weird behaviour and certainly a bug in SDL
	is_osx = true;
#endif
<<<<<<< HEAD
	if (window->fullscreen() && (video_config.switchres || is_osx))
	{
		SDL_SetWindowFullscreen(window->sdl_window(), 0);    // Try to set mode
		SDL_SetWindowDisplayMode(window->sdl_window(), &window->m_original_mode);    // Try to set mode
		SDL_SetWindowFullscreen(window->sdl_window(), SDL_WINDOW_FULLSCREEN);    // Try to set mode
	}
	SDL_DestroyWindow(window->sdl_window());
#else
	if (window->m_sdlsurf)
	{
		SDL_FreeSurface(window->m_sdlsurf);
		window->m_sdlsurf = NULL;
	}
#endif


	sdlinput_release_keys();

	window->set_renderer(draw.create(window));

	// toggle the window mode
	window->set_fullscreen(!window->fullscreen());

	complete_create_wt(param, 0);

	return NULL;
}

void sdl_window_info::toggle_full_screen()
{
	ASSERT_MAIN_THREAD();

	execute_async_wait(&sdlwindow_toggle_full_screen_wt, worker_param(this));
=======
	if (fullscreen() && (video_config.switchres || is_osx))
	{
		SDL_SetWindowFullscreen(platform_window(), 0);    // Try to set mode
		SDL_SetWindowDisplayMode(platform_window(), &m_original_mode->mode);    // Try to set mode
		SDL_SetWindowFullscreen(platform_window(), SDL_WINDOW_FULLSCREEN);    // Try to set mode
	}
	SDL_DestroyWindow(platform_window());

	downcast<sdl_osd_interface &>(machine().osd()).release_keys();

	set_renderer(osd_renderer::make_for_type(video_config.mode, shared_from_this()));

	// toggle the window mode
	set_fullscreen(!fullscreen());

	complete_create();
>>>>>>> upstream/master
}

void sdl_window_info::modify_prescale(int dir)
{
<<<<<<< HEAD
	worker_param wp = worker_param(this);
=======
>>>>>>> upstream/master
	int new_prescale = prescale();

	if (dir > 0 && prescale() < 3)
		new_prescale = prescale() + 1;
	if (dir < 0 && prescale() > 1)
		new_prescale = prescale() - 1;

	if (new_prescale != prescale())
	{
		if (m_fullscreen && video_config.switchres)
		{
<<<<<<< HEAD
			execute_async_wait(&sdlwindow_video_window_destroy_wt, wp);

			m_prescale = new_prescale;

			execute_async_wait(&complete_create_wt, wp);

=======
			complete_destroy();

			m_prescale = new_prescale;

			complete_create();
>>>>>>> upstream/master
		}
		else
		{
			notify_changed();
			m_prescale = new_prescale;
		}
		machine().ui().popup_time(1, "Prescale %d", prescale());
	}
}

//============================================================
//  sdlwindow_update_cursor_state
//  (main or window thread)
//============================================================

void sdl_window_info::update_cursor_state()
{
#if (USE_XINPUT)
	// Hack for wii-lightguns:
	// they stop working with a grabbed mouse;
	// even a ShowCursor(SDL_DISABLE) already does this.
	// To make the cursor disappear, we'll just set an empty cursor image.
	unsigned char data[]={0,0,0,0,0,0,0,0};
	SDL_Cursor *c;
	c=SDL_CreateCursor(data, data, 8, 8, 0, 0);
	SDL_SetCursor(c);
#else
<<<<<<< HEAD
#if (SDLMAME_SDL2)
=======
>>>>>>> upstream/master
	// do not do mouse capture if the debugger's enabled to avoid
	// the possibility of losing control
	if (!(machine().debug_flags & DEBUG_FLAG_OSD_ENABLED))
	{
<<<<<<< HEAD
		//FIXME: SDL1.3: really broken: the whole SDL code
		//       will only work correct with relative mouse movements ...
		if (!fullscreen() && !sdlinput_should_hide_mouse())
		{
			SDL_ShowCursor(SDL_ENABLE);
			if (SDL_GetWindowGrab(sdl_window() ))
				SDL_SetWindowGrab(sdl_window(), SDL_FALSE);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		else
		{
			SDL_ShowCursor(SDL_DISABLE);
			if (!SDL_GetWindowGrab(sdl_window()))
				SDL_SetWindowGrab(sdl_window(), SDL_TRUE);
			SDL_SetRelativeMouseMode(SDL_TRUE);
		}
		SDL_SetCursor(NULL); // Force an update in case the underlying driver has changed visibility
	}

#else
	// do not do mouse capture if the debugger's enabled to avoid
	// the possibility of losing control
	if (!(machine().debug_flags & DEBUG_FLAG_OSD_ENABLED))
	{
		if ( fullscreen() || sdlinput_should_hide_mouse() )
		{
			SDL_ShowCursor(SDL_DISABLE);
			if (!SDL_WM_GrabInput(SDL_GRAB_QUERY))
			{
				SDL_WM_GrabInput(SDL_GRAB_ON);
			}
		}
		else
		{
			SDL_ShowCursor(SDL_ENABLE);
			if (SDL_WM_GrabInput(SDL_GRAB_QUERY))
			{
				SDL_WM_GrabInput(SDL_GRAB_OFF);
			}
		}
	}
#endif
#endif
}

OSDWORK_CALLBACK( sdl_window_info::update_cursor_state_wt )
{
	worker_param *      wp = (worker_param *) param;
	sdl_window_info *   window = wp->window();

	window->update_cursor_state();

	osd_free(wp);
	return NULL;
=======
		bool should_hide_mouse = downcast<sdl_osd_interface&>(machine().osd()).should_hide_mouse();

		if (!fullscreen() && !should_hide_mouse)
		{
			show_pointer();
			release_pointer();
		}
		else
		{
			hide_pointer();
			capture_pointer();
		}

		SDL_SetCursor(nullptr); // Force an update in case the underlying driver has changed visibility
	}
#endif
>>>>>>> upstream/master
}

int sdl_window_info::xy_to_render_target(int x, int y, int *xt, int *yt)
{
	return renderer().xy_to_render_target(x, y, xt, yt);
}

//============================================================
//  sdlwindow_video_window_create
//  (main thread)
//============================================================

int sdl_window_info::window_init()
{
<<<<<<< HEAD
	worker_param *wp = (worker_param *) osd_malloc(sizeof(worker_param));
	int result;

	ASSERT_MAIN_THREAD();

=======
	int result;

>>>>>>> upstream/master
	// set the initial maximized state
	// FIXME: Does not belong here
	sdl_options &options = downcast<sdl_options &>(m_machine.options());
	m_startmaximized = options.maximize();

	// add us to the list
<<<<<<< HEAD
	*last_window_ptr = this;
	last_window_ptr = &this->m_next;

	set_renderer(draw.create(this));

	// create an event that we can use to skip blitting
	m_rendered_event = osd_event_alloc(FALSE, TRUE);
=======
	osd_common_t::s_window_list.push_back(std::static_pointer_cast<sdl_window_info>(shared_from_this()));

	set_renderer(osd_renderer::make_for_type(video_config.mode, static_cast<osd_window*>(this)->shared_from_this()));
>>>>>>> upstream/master

	// load the layout
	m_target = m_machine.render().target_alloc();

	// set the specific view
	set_starting_view(m_index, options.view(), options.view(m_index));

	// make the window title
	if (video_config.numscreens == 1)
<<<<<<< HEAD
		sprintf(m_title, "%s: %s [%s]", emulator_info::get_appname(), m_machine.system().description, m_machine.system().name);
	else
		sprintf(m_title, "%s: %s [%s] - Screen %d", emulator_info::get_appname(), m_machine.system().description, m_machine.system().name, m_index);

	wp->set_window(this);

	// FIXME: pass error back in a different way
	if (multithreading_enabled)
	{
		osd_work_item *wi;

		wi = osd_work_item_queue(work_queue, &sdl_window_info::complete_create_wt, (void *) wp, 0);
		sdlwindow_sync();
		result = *((int *) (osd_work_item_result)(wi));
		osd_work_item_release(wi);
	}
	else
		result = *((int *) sdl_window_info::complete_create_wt((void *) wp, 0));
=======
		sprintf(m_title, "%s: %s [%s]", emulator_info::get_appname(), m_machine.system().type.fullname(), m_machine.system().name);
	else
		sprintf(m_title, "%s: %s [%s] - Screen %d", emulator_info::get_appname(), m_machine.system().type.fullname(), m_machine.system().name, m_index);

	result = complete_create();
>>>>>>> upstream/master

	// handle error conditions
	if (result == 1)
		goto error;

	return 0;

error:
	destroy();
	return 1;
}


//============================================================
//  sdlwindow_video_window_destroy
<<<<<<< HEAD
//  (main thread)
//============================================================

OSDWORK_CALLBACK( sdl_window_info::sdlwindow_video_window_destroy_wt )
{
	worker_param *      wp = (worker_param *) param;
	sdl_window_info *   window = wp->window();

	ASSERT_WINDOW_THREAD();

	// free the textures etc
	window->renderer().destroy();

#if (SDLMAME_SDL2)
	if (window->fullscreen() && video_config.switchres)
	{
		SDL_SetWindowFullscreen(window->sdl_window(), 0);    // Try to set mode
		SDL_SetWindowDisplayMode(window->sdl_window(), &window->m_original_mode);    // Try to set mode
		SDL_SetWindowFullscreen(window->sdl_window(), SDL_WINDOW_FULLSCREEN);    // Try to set mode
	}
	SDL_DestroyWindow(window->sdl_window());
#else
	if (window->m_sdlsurf)
	{
		SDL_FreeSurface(window->m_sdlsurf);
		window->m_sdlsurf = NULL;
	}
#endif

	// release all keys ...
	sdlinput_release_keys();


	osd_free(wp);
	return NULL;
=======
//============================================================

void sdl_window_info::complete_destroy()
{
	// Release pointer grab and hide if needed
	show_pointer();
	release_pointer();

	if (fullscreen() && video_config.switchres)
	{
		SDL_SetWindowFullscreen(platform_window(), 0);    // Try to set mode
		SDL_SetWindowDisplayMode(platform_window(), &m_original_mode->mode);    // Try to set mode
		SDL_SetWindowFullscreen(platform_window(), SDL_WINDOW_FULLSCREEN);    // Try to set mode
	}

	SDL_DestroyWindow(platform_window());
	// release all keys ...
	downcast<sdl_osd_interface &>(machine().osd()).release_keys();
>>>>>>> upstream/master
}

void sdl_window_info::destroy()
{
<<<<<<< HEAD
	sdl_window_info **prevptr;

	ASSERT_MAIN_THREAD();
	if (multithreading_enabled)
	{
		sdlwindow_sync();
	}

	//osd_event_wait(window->rendered_event, osd_ticks_per_second()*10);

	// remove us from the list
	for (prevptr = &sdl_window_list; *prevptr != NULL; prevptr = &(*prevptr)->m_next)
		if (*prevptr == this)
		{
			*prevptr = this->m_next;
			break;
		}

	// free the textures etc
	execute_async_wait(&sdlwindow_video_window_destroy_wt, worker_param(this));

	// free the render target, after the textures!
	this->machine().render().target_free(m_target);

	// free the event
	osd_event_free(m_rendered_event);
=======
	//osd_event_wait(window->rendered_event, osd_ticks_per_second()*10);

	// remove us from the list
	osd_common_t::s_window_list.remove(std::static_pointer_cast<sdl_window_info>(shared_from_this()));

	// free the textures etc
	complete_destroy();

	// free the render target, after the textures!
	machine().render().target_free(m_target);
>>>>>>> upstream/master

}


//============================================================
//  pick_best_mode
//============================================================

<<<<<<< HEAD
#if SDLMAME_SDL2
=======
>>>>>>> upstream/master
osd_dim sdl_window_info::pick_best_mode()
{
	int minimum_width, minimum_height, target_width, target_height;
	int i;
	int num;
	float size_score, best_score = 0.0f;
	osd_dim ret(0,0);

	// determine the minimum width/height for the selected target
	m_target->compute_minimum_size(minimum_width, minimum_height);

	// use those as the target for now
<<<<<<< HEAD
	target_width = minimum_width * MAX(1, prescale());
	target_height = minimum_height * MAX(1, prescale());
=======
	target_width = minimum_width * std::max(1, prescale());
	target_height = minimum_height * std::max(1, prescale());
>>>>>>> upstream/master

	// if we're not stretching, allow some slop on the minimum since we can handle it
	{
		minimum_width -= 4;
		minimum_height -= 4;
	}

	// FIXME: this should be provided by monitor !
<<<<<<< HEAD
	num = SDL_GetNumDisplayModes(*((UINT64 *)m_monitor->oshandle()));
=======
	num = SDL_GetNumDisplayModes(m_monitor->oshandle());
>>>>>>> upstream/master

	if (num == 0)
	{
		osd_printf_error("SDL: No modes available?!\n");
		exit(-1);
	}
	else
	{
		for (i = 0; i < num; ++i)
		{
			SDL_DisplayMode mode;
<<<<<<< HEAD
			SDL_GetDisplayMode(*((UINT64 *)m_monitor->oshandle()), i, &mode);

			// compute initial score based on difference between target and current
			size_score = 1.0f / (1.0f + abs((INT32)mode.w - target_width) + abs((INT32)mode.h - target_height));
=======
			SDL_GetDisplayMode(m_monitor->oshandle(), i, &mode);

			// compute initial score based on difference between target and current
			size_score = 1.0f / (1.0f + abs((int32_t)mode.w - target_width) + abs((int32_t)mode.h - target_height));
>>>>>>> upstream/master

			// if the mode is too small, give a big penalty
			if (mode.w < minimum_width || mode.h < minimum_height)
				size_score *= 0.01f;

			// if mode is smaller than we'd like, it only scores up to 0.1
			if (mode.w < target_width || mode.h < target_height)
				size_score *= 0.1f;

			// if we're looking for a particular mode, that's a winner
			if (mode.w == m_win_config.width && mode.h == m_win_config.height)
				size_score = 2.0f;

			// refresh adds some points
			if (m_win_config.refresh)
				size_score *= 1.0f / (1.0f + abs(m_win_config.refresh - mode.refresh_rate) / 10.0f);

			osd_printf_verbose("%4dx%4d@%2d -> %f\n", (int)mode.w, (int)mode.h, (int) mode.refresh_rate, (double) size_score);

			// best so far?
			if (size_score > best_score)
			{
				best_score = size_score;
				ret = osd_dim(mode.w, mode.h);
			}

		}
	}
	return ret;
}
<<<<<<< HEAD
#else
osd_dim sdl_window_info::pick_best_mode()
{
	int minimum_width, minimum_height, target_width, target_height;
	int i;
	float size_score, best_score = 0.0f;
	int best_width = 0, best_height = 0;
	SDL_Rect **modes;

	// determine the minimum width/height for the selected target
	m_target->compute_minimum_size(minimum_width, minimum_height);

	// use those as the target for now
	target_width = minimum_width * MAX(1, prescale());
	target_height = minimum_height * MAX(1, prescale());

	// if we're not stretching, allow some slop on the minimum since we can handle it
	{
		minimum_width -= 4;
		minimum_height -= 4;
	}

#if 1 // defined(SDLMAME_WIN32)
	/*
	 *  We need to do this here. If SDL_ListModes is
	 * called in init_monitors, the call will crash
	 * on win32
	 */
	modes = SDL_ListModes(NULL, SDL_FULLSCREEN | SDL_DOUBLEBUF);
#else
	modes = window->m_monitor->modes;
#endif

	if (modes == (SDL_Rect **)0)
	{
		osd_printf_error("SDL: No modes available?!\n");
		exit(-1);
	}
	else if (modes == (SDL_Rect **)-1)  // all modes are possible
	{
		return osd_dim(m_win_config.width, m_win_config.height);
	}
	else
	{
		for (i = 0; modes[i]; ++i)
		{
			// compute initial score based on difference between target and current
			size_score = 1.0f / (1.0f + fabsf((INT32)modes[i]->w - target_width) + fabsf((INT32)modes[i]->h - target_height));

			// if the mode is too small, give a big penalty
			if (modes[i]->w < minimum_width || modes[i]->h < minimum_height)
				size_score *= 0.01f;

			// if mode is smaller than we'd like, it only scores up to 0.1
			if (modes[i]->w < target_width || modes[i]->h < target_height)
				size_score *= 0.1f;

			// if we're looking for a particular mode, that's a winner
			if (modes[i]->w == m_win_config.width && modes[i]->h == m_win_config.height)
				size_score = 2.0f;

			osd_printf_verbose("%4dx%4d -> %f\n", (int)modes[i]->w, (int)modes[i]->h, size_score);

			// best so far?
			if (size_score > best_score)
			{
				best_score = size_score;
				best_width = modes[i]->w;
				best_height = modes[i]->h;
			}

		}
	}
	return osd_dim(best_width, best_height);
}
#endif
=======
>>>>>>> upstream/master

//============================================================
//  sdlwindow_video_window_update
//  (main thread)
//============================================================

void sdl_window_info::update()
{
	osd_ticks_t     event_wait_ticks;
<<<<<<< HEAD
	ASSERT_MAIN_THREAD();
=======
>>>>>>> upstream/master

	// adjust the cursor state
	//sdlwindow_update_cursor_state(machine, window);

<<<<<<< HEAD
	execute_async(&update_cursor_state_wt, worker_param(this));

	// if we're visible and running and not in the middle of a resize, draw
	if (m_target != NULL)
=======
	update_cursor_state();

	// if we're visible and running and not in the middle of a resize, draw
	if (m_target != nullptr)
>>>>>>> upstream/master
	{
		int tempwidth, tempheight;

		// see if the games video mode has changed
		m_target->compute_minimum_size(tempwidth, tempheight);
		if (osd_dim(tempwidth, tempheight) != m_minimum_dim)
		{
			m_minimum_dim = osd_dim(tempwidth, tempheight);

			if (!this->m_fullscreen)
			{
				//Don't resize window without user interaction;
				//window_resize(blitwidth, blitheight);
			}
			else if (video_config.switchres)
			{
				osd_dim tmp = this->pick_best_mode();
				resize(tmp.width(), tmp.height());
			}
		}

		if (video_config.waitvsync && video_config.syncrefresh)
			event_wait_ticks = osd_ticks_per_second(); // block at most a second
		else
			event_wait_ticks = 0;

<<<<<<< HEAD
		if (osd_event_wait(m_rendered_event, event_wait_ticks))
		{
			// ensure the target bounds are up-to-date, and then get the primitives

			render_primitive_list &primlist = *m_renderer->get_primitives();

			// and redraw now

			execute_async(&draw_video_contents_wt, worker_param(this, primlist));
=======
		if (m_rendered_event.wait(event_wait_ticks))
		{
			const int update = 1;

			// ensure the target bounds are up-to-date, and then get the primitives

			render_primitive_list &primlist = *renderer().get_primitives();

			// and redraw now

			// Some configurations require events to be polled in the worker thread
			downcast< sdl_osd_interface& >(machine().osd()).process_events_buf();

			// Check whether window has vector screens

			{
				const screen_device *screen = screen_device_iterator(machine().root_device()).byindex(m_index);
				if ((screen != nullptr) && (screen->screen_type() == SCREEN_TYPE_VECTOR))
					renderer().set_flags(osd_renderer::FLAG_HAS_VECTOR_SCREEN);
				else
					renderer().clear_flags(osd_renderer::FLAG_HAS_VECTOR_SCREEN);
			}

			m_primlist = &primlist;

			// if no bitmap, just fill
			if (m_primlist == nullptr)
			{
			}
			// otherwise, render with our drawing system
			else
			{
				if( video_config.perftest )
					measure_fps(update);
				else
					renderer().draw(update);
			}

			/* all done, ready for next */
			m_rendered_event.set();
>>>>>>> upstream/master
		}
	}
}


//============================================================
//  set_starting_view
//  (main thread)
//============================================================

void sdl_window_info::set_starting_view(int index, const char *defview, const char *view)
{
	int viewindex;

<<<<<<< HEAD
	ASSERT_MAIN_THREAD();

=======
>>>>>>> upstream/master
	// choose non-auto over auto
	if (strcmp(view, "auto") == 0 && strcmp(defview, "auto") != 0)
		view = defview;

	// query the video system to help us pick a view
	viewindex = target()->configured_view(view, index, video_config.numscreens);

	// set the view
	target()->set_view(viewindex);
}


//============================================================
//  complete_create
<<<<<<< HEAD
//  (window thread)
//============================================================

OSDWORK_CALLBACK( sdl_window_info::complete_create_wt )
{
	worker_param *      wp = (worker_param *) param;
	sdl_window_info *   window = wp->window();

	osd_dim temp(0,0);
	static int result[2] = {0,1};

	ASSERT_WINDOW_THREAD();
	osd_free(wp);

	// clear out original mode. Needed on OSX
	if (window->fullscreen())
	{
		// default to the current mode exactly
		temp = window->monitor()->position_size().dim();

		// if we're allowed to switch resolutions, override with something better
		if (video_config.switchres)
			temp = window->pick_best_mode();
	}
	else if (window->m_windowed_dim.width() > 0)
	{
		// if we have a remembered size force the new window size to it
		temp = window->m_windowed_dim;
	}
	else
	{
		if (window->m_startmaximized)
		{
			temp = window->get_max_bounds(video_config.keepaspect );
		}
		else
		{
#if 0
			// Couriersud: This code never has worked with the last version of get_min_bounds
			/* Create the window directly with the correct aspect
			   instead of letting sdlwindow_blit_surface_size() resize it
			   this stops the window from "flashing" from the wrong aspect
			   size to the right one at startup. */
			tempwidth = (window->m_win_config.width != 0) ? window->m_win_config.width : 640;
			tempheight = (window->m_win_config.height != 0) ? window->m_win_config.height : 480;
#endif
			temp = window->get_min_bounds(video_config.keepaspect );
		}
	}

=======
//============================================================

int sdl_window_info::complete_create()
{
	osd_dim temp(0,0);

	// clear out original mode. Needed on OSX
	if (fullscreen())
	{
		// default to the current mode exactly
		temp = monitor()->position_size().dim();

		// if we're allowed to switch resolutions, override with something better
		if (video_config.switchres)
			temp = pick_best_mode();
	}
	else if (m_windowed_dim.width() > 0)
	{
		// if we have a remembered size force the new window size to it
		temp = m_windowed_dim;
	}
	else if (m_startmaximized)
		temp = get_max_bounds(video_config.keepaspect );
	else
		temp = get_min_bounds(video_config.keepaspect );
>>>>>>> upstream/master

	// create the window .....

	/* FIXME: On Ubuntu and potentially other Linux OS you should use
	 * to disable panning. This has to be done before every invocation of mame.
	 *
	 * xrandr --output HDMI-0 --panning 0x0+0+0 --fb 0x0
	 *
	 */
	osd_printf_verbose("Enter sdl_info::create\n");
<<<<<<< HEAD

#if (SDLMAME_SDL2)

	if (window->renderer().has_flags(osd_renderer::FLAG_NEEDS_OPENGL))
=======
	if (renderer().has_flags(osd_renderer::FLAG_NEEDS_OPENGL))
>>>>>>> upstream/master
	{
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

		/* FIXME: A reminder that gamma is wrong throughout MAME. Currently, SDL2.0 doesn't seem to
		    * support the following attribute although my hardware lists GL_ARB_framebuffer_sRGB as an extension.
		    *
		    * SDL_GL_SetAttribute( SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1 );
		    *
		    */
<<<<<<< HEAD
		window->m_extra_flags = SDL_WINDOW_OPENGL;
	}
	else
		window->m_extra_flags = 0;
=======
		m_extra_flags = SDL_WINDOW_OPENGL;
	}
	else
		m_extra_flags = 0;
>>>>>>> upstream/master

#ifdef SDLMAME_MACOSX
	/* FIMXE: On OSX, SDL_WINDOW_FULLSCREEN_DESKTOP seems to be more reliable.
	 *        It however creates issues with white borders, i.e. the screen clear
	 *        does not work. This happens both with opengl and accel.
	 */
#endif

<<<<<<< HEAD
	// create the SDL window
	// soft driver also used | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_MOUSE_FOCUS
	window->m_extra_flags |= (window->fullscreen() ?
			/*SDL_WINDOW_BORDERLESS |*/ SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE);
=======
	// We need to workaround an issue in SDL 2.0.4 for OS X where setting the
	// relative mode on the mouse in fullscreen mode makes mouse events stop
	// It is fixed in the latest revisions so we'll assume it'll be fixed
	// in the next public SDL release as well
#if defined(SDLMAME_MACOSX) && SDL_VERSION_ATLEAST(2, 0, 2) // SDL_HINT_MOUSE_RELATIVE_MODE_WARP is introduced in 2.0.2
	SDL_version linked;
	SDL_GetVersion(&linked);
	int revision = SDL_GetRevisionNumber();

	// If we're running the exact version of SDL 2.0.4 (revision 10001) from the
	// SDL web site, we need to work around this issue and send the warp mode hint
	if (SDL_VERSION_EQUALS(linked, SDL_VERSIONNUM(2, 0, 4)) && revision == 10001)
	{
		osd_printf_verbose("Using warp mode for relative mouse in OS X SDL 2.0.4\n");
		SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1");
	}
#endif

	// create the SDL window
	// soft driver also used | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_MOUSE_FOCUS
	m_extra_flags |= (fullscreen() ?
			SDL_WINDOW_BORDERLESS | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE);
>>>>>>> upstream/master

#if defined(SDLMAME_WIN32)
	SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
#endif
<<<<<<< HEAD
	// create the SDL window
	window->m_sdl_window = SDL_CreateWindow(window->m_title,
			window->monitor()->position_size().left(), window->monitor()->position_size().top(),
			temp.width(), temp.height(), window->m_extra_flags);
	//window().sdl_window() = SDL_CreateWindow(window().m_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	//      width, height, m_extra_flags);

	if  ( window->m_sdl_window == NULL )
	{
		if (window->renderer().has_flags(osd_renderer::FLAG_NEEDS_OPENGL))
			osd_printf_error("OpenGL not supported on this driver: %s\n", SDL_GetError());
		else
			osd_printf_error("Window creation failed: %s\n", SDL_GetError());
		return (void *) &result[1];
	}

	if (window->fullscreen() && video_config.switchres)
	{
		SDL_DisplayMode mode;
		//SDL_GetCurrentDisplayMode(window().monitor()->handle, &mode);
		SDL_GetWindowDisplayMode(window->sdl_window(), &mode);
		window->m_original_mode = mode;
		mode.w = temp.width();
		mode.h = temp.height();
		if (window->m_win_config.refresh)
			mode.refresh_rate = window->m_win_config.refresh;

		SDL_SetWindowDisplayMode(window->sdl_window(), &mode);    // Try to set mode
=======

	// get monitor work area for centering
	osd_rect work = monitor()->usuable_position_size();

	// create the SDL window
	auto sdlwindow = SDL_CreateWindow(m_title,
			work.left() + (work.width() - temp.width()) / 2,
			work.top() + (work.height() - temp.height()) / 2,
			temp.width(), temp.height(), m_extra_flags);
	//window().sdl_window() = SDL_CreateWindow(window().m_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	//      width, height, m_extra_flags);

	if  (sdlwindow == nullptr )
	{
		if (renderer().has_flags(osd_renderer::FLAG_NEEDS_OPENGL))
			osd_printf_error("OpenGL not supported on this driver: %s\n", SDL_GetError());
		else
			osd_printf_error("Window creation failed: %s\n", SDL_GetError());
		return 1;
	}

	set_platform_window(sdlwindow);

	if (fullscreen() && video_config.switchres)
	{
		SDL_DisplayMode mode;
		//SDL_GetCurrentDisplayMode(window().monitor()->handle, &mode);
		SDL_GetWindowDisplayMode(platform_window(), &mode);
		m_original_mode->mode = mode;
		mode.w = temp.width();
		mode.h = temp.height();
		if (m_win_config.refresh)
			mode.refresh_rate = m_win_config.refresh;

		SDL_SetWindowDisplayMode(platform_window(), &mode);    // Try to set mode
>>>>>>> upstream/master
#ifndef SDLMAME_WIN32
		/* FIXME: Warp the mouse to 0,0 in case a virtual desktop resolution
		 * is in place after the mode switch - which will most likely be the case
		 * This is a hack to work around a deficiency in SDL2
		 */
<<<<<<< HEAD
		SDL_WarpMouseInWindow(window->sdl_window(), 1, 1);
=======
		SDL_WarpMouseInWindow(platform_window(), 1, 1);
>>>>>>> upstream/master
#endif
	}
	else
	{
<<<<<<< HEAD
		//SDL_SetWindowDisplayMode(window().sdl_window(), NULL); // Use desktop
=======
		//SDL_SetWindowDisplayMode(window().sdl_window(), nullptr); // Use desktop
>>>>>>> upstream/master
	}

	// show window

<<<<<<< HEAD
	SDL_ShowWindow(window->sdl_window());
	//SDL_SetWindowFullscreen(window->sdl_window(), 0);
	//SDL_SetWindowFullscreen(window->sdl_window(), window->fullscreen());
	SDL_RaiseWindow(window->sdl_window());

#ifdef SDLMAME_WIN32
	if (window->fullscreen())
		SDL_SetWindowGrab(window->sdl_window(), SDL_TRUE);
#endif

#else
	window->m_extra_flags = (window->fullscreen() ?  SDL_FULLSCREEN : SDL_RESIZABLE);

	if (window->renderer().has_flags(osd_renderer::FLAG_NEEDS_DOUBLEBUF))
		window->m_extra_flags |= SDL_DOUBLEBUF;
	if (window->renderer().has_flags(osd_renderer::FLAG_NEEDS_ASYNCBLIT))
		window->m_extra_flags |= SDL_ASYNCBLIT;

	if (window->renderer().has_flags(osd_renderer::FLAG_NEEDS_OPENGL))
	{
		window->m_extra_flags |= SDL_DOUBLEBUF | SDL_OPENGL;
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
		#if (SDL_VERSION_ATLEAST(1,2,10)) && (!defined(SDLMAME_EMSCRIPTEN))
		SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, video_config.waitvsync ? 1 : 0);
		#endif
		//  load_gl_lib(window->machine());
	}

	// create the SDL surface (which creates the window in windowed mode)
#if 0
	window->m_sdlsurf = SDL_SetVideoMode(tempwidth, tempheight,
							0, SDL_OPENGL | SDL_FULLSCREEN);// | window->m_extra_flags);
	if (!window->m_sdlsurf)
		printf("completely failed\n");
#endif
	window->m_sdlsurf = SDL_SetVideoMode(temp.width(), temp.height(),
							0, SDL_SWSURFACE  | SDL_ANYFORMAT | window->m_extra_flags);

	if (!window->m_sdlsurf)
	{
		osd_printf_error("SDL Error: %s\n", SDL_GetError());
		return (void *) &result[1];
	}
	if ( (video_config.mode  == VIDEO_MODE_OPENGL) && !(window->m_sdlsurf->flags & SDL_OPENGL) )
	{
		osd_printf_error("OpenGL not supported on this driver!\n");
		return (void *) &result[1];
	}
	// set the window title
	SDL_WM_SetCaption(window->m_title, "SDLMAME");
#endif

	window->monitor()->refresh();
	// initialize the drawing backend
	if (window->renderer().create())
		return (void *) &result[1];
=======
	SDL_ShowWindow(platform_window());
	//SDL_SetWindowFullscreen(window->sdl_window(), 0);
	//SDL_SetWindowFullscreen(window->sdl_window(), window->fullscreen());
	SDL_RaiseWindow(platform_window());

#ifdef SDLMAME_WIN32
	if (fullscreen())
		SDL_SetWindowGrab(platform_window(), SDL_TRUE);
#endif

	// set main window
	if (m_index > 0)
	{
		for (auto w : osd_common_t::s_window_list)
		{
			if (w->m_index == 0)
			{
				set_main_window(std::dynamic_pointer_cast<osd_window>(w));
				break;
			}
		}
	}
	else
	{
		// We must be the main window
		set_main_window(shared_from_this());
	}

	// update monitor resolution after mode change to ensure proper pixel aspect
	monitor()->refresh();
	if (fullscreen() && video_config.switchres)
		monitor()->update_resolution(temp.width(), temp.height());

	// initialize the drawing backend
	if (renderer().create())
		return 1;
>>>>>>> upstream/master

	// Make sure we have a consistent state
	SDL_ShowCursor(0);
	SDL_ShowCursor(1);

<<<<<<< HEAD
	return (void *) &result[0];
=======
	return 0;
>>>>>>> upstream/master
}


//============================================================
//  draw_video_contents
//  (window thread)
//============================================================

void sdl_window_info::measure_fps(int update)
{
	const unsigned long frames_skip4fps = 100;
	static int64_t lastTime=0, sumdt=0, startTime=0;
	static unsigned long frames = 0;
	int64_t currentTime, t0;
	double dt;
	double tps;
	osd_ticks_t tps_t;

	tps_t = osd_ticks_per_second();
	tps = (double) tps_t;

	t0 = osd_ticks();

	renderer().draw(update);

	frames++;
	currentTime = osd_ticks();
	if(startTime==0||frames==frames_skip4fps)
		startTime=currentTime;
	if( frames>=frames_skip4fps )
		sumdt+=currentTime-t0;
	if( (currentTime-lastTime)>1L*osd_ticks_per_second() && frames>frames_skip4fps )
	{
		dt = (double) (currentTime-startTime) / tps; // in decimale sec.
		osd_printf_info("%6.2lfs, %4lu F, "
				"avrg game: %5.2lf FPS %.2lf ms/f, "
				"avrg video: %5.2lf FPS %.2lf ms/f, "
				"last video: %5.2lf FPS %.2lf ms/f\n",
			dt, frames-frames_skip4fps,
			(double)(frames-frames_skip4fps)/dt,                             // avrg game fps
			( (currentTime-startTime) / ((frames-frames_skip4fps)) ) * 1000.0 / osd_ticks_per_second(),
			(double)(frames-frames_skip4fps)/((double)(sumdt) / tps), // avrg vid fps
			( sumdt / ((frames-frames_skip4fps)) ) * 1000.0 / tps,
			1.0/((currentTime-t0) / osd_ticks_per_second()), // this vid fps
			(currentTime-t0) * 1000.0 / tps
		);
		lastTime = currentTime;
	}
}

<<<<<<< HEAD
OSDWORK_CALLBACK( sdl_window_info::draw_video_contents_wt )
{
	int     update =    1;
	worker_param *wp = (worker_param *) param;
	sdl_window_info *window = wp->window();

	ASSERT_REDRAW_THREAD();

	// Some configurations require events to be polled in the worker thread
	sdlinput_process_events_buf();

	// Check whether window has vector screens

	{
#if 1
		int scrnum = 0;
		int is_vector = 0;
		screen_device_iterator iter(window->machine().root_device());
		for (const screen_device *screen = iter.first(); screen != NULL; screen = iter.next())
		{
			if (scrnum == window->m_index)
			{
				is_vector = (screen->screen_type() == SCREEN_TYPE_VECTOR) ? 1 : 0;
				break;
			}
			else
			{
				scrnum++;
			}
		}
		if (is_vector)
			window->renderer().set_flags(osd_renderer::FLAG_HAS_VECTOR_SCREEN);
		else
			window->renderer().clear_flags(osd_renderer::FLAG_HAS_VECTOR_SCREEN);
#endif
	}


	window->m_primlist = wp->list();

	// if no bitmap, just fill
	if (window->m_primlist == NULL)
	{
	}
	// otherwise, render with our drawing system
	else
	{
		if( video_config.perftest )
			window->measure_fps(update);
		else
			window->renderer().draw(update);
	}

	/* all done, ready for next */
	osd_event_set(window->m_rendered_event);
	osd_free(wp);

	return NULL;
}

=======
>>>>>>> upstream/master
int sdl_window_info::wnd_extra_width()
{
	return m_fullscreen ? 0 : WINDOW_DECORATION_WIDTH;
}

int sdl_window_info::wnd_extra_height()
{
	return m_fullscreen ? 0 : WINDOW_DECORATION_HEIGHT;
}


//============================================================
//  constrain_to_aspect_ratio
//  (window thread)
//============================================================

osd_rect sdl_window_info::constrain_to_aspect_ratio(const osd_rect &rect, int adjustment)
{
<<<<<<< HEAD
	INT32 extrawidth = wnd_extra_width();
	INT32 extraheight = wnd_extra_height();
	INT32 propwidth, propheight;
	INT32 minwidth, minheight;
	INT32 maxwidth, maxheight;
	INT32 viswidth, visheight;
	INT32 adjwidth, adjheight;
	float pixel_aspect;
	osd_monitor_info *monitor = m_monitor;

	// get the pixel aspect ratio for the target monitor
	pixel_aspect = monitor->aspect();
=======
	int32_t extrawidth = wnd_extra_width();
	int32_t extraheight = wnd_extra_height();
	int32_t propwidth, propheight;
	int32_t minwidth, minheight;
	int32_t maxwidth, maxheight;
	int32_t viswidth, visheight;
	int32_t adjwidth, adjheight;
	float pixel_aspect;
	std::shared_ptr<osd_monitor_info> monitor = m_monitor;

	// do not constrain aspect ratio for integer scaled views
	if (m_target->scale_mode() != SCALE_FRACTIONAL)
		return rect;

	// get the pixel aspect ratio for the target monitor
	pixel_aspect = monitor->pixel_aspect();
>>>>>>> upstream/master

	// determine the proposed width/height
	propwidth = rect.width() - extrawidth;
	propheight = rect.height() - extraheight;

	// based on which edge we are adjusting, take either the width, height, or both as gospel
	// and scale to fit using that as our parameter
	switch (adjustment)
	{
		case WMSZ_BOTTOM:
		case WMSZ_TOP:
			m_target->compute_visible_area(10000, propheight, pixel_aspect, m_target->orientation(), propwidth, propheight);
			break;

		case WMSZ_LEFT:
		case WMSZ_RIGHT:
			m_target->compute_visible_area(propwidth, 10000, pixel_aspect, m_target->orientation(), propwidth, propheight);
			break;

		default:
			m_target->compute_visible_area(propwidth, propheight, pixel_aspect, m_target->orientation(), propwidth, propheight);
			break;
	}

	// get the minimum width/height for the current layout
	m_target->compute_minimum_size(minwidth, minheight);

	// clamp against the absolute minimum
<<<<<<< HEAD
	propwidth = MAX(propwidth, MIN_WINDOW_DIM);
	propheight = MAX(propheight, MIN_WINDOW_DIM);

	// clamp against the minimum width and height
	propwidth = MAX(propwidth, minwidth);
	propheight = MAX(propheight, minheight);
=======
	propwidth = std::max(propwidth, MIN_WINDOW_DIM);
	propheight = std::max(propheight, MIN_WINDOW_DIM);

	// clamp against the minimum width and height
	propwidth = std::max(propwidth, minwidth);
	propheight = std::max(propheight, minheight);
>>>>>>> upstream/master

	// clamp against the maximum (fit on one screen for full screen mode)
	if (m_fullscreen)
	{
		maxwidth = monitor->position_size().width() - extrawidth;
		maxheight = monitor->position_size().height() - extraheight;
	}
	else
	{
		maxwidth = monitor->usuable_position_size().width() - extrawidth;
		maxheight = monitor->usuable_position_size().height() - extraheight;

		// further clamp to the maximum width/height in the window
		if (m_win_config.width != 0)
<<<<<<< HEAD
			maxwidth = MIN(maxwidth, m_win_config.width + extrawidth);
		if (m_win_config.height != 0)
			maxheight = MIN(maxheight, m_win_config.height + extraheight);
	}

	// clamp to the maximum
	propwidth = MIN(propwidth, maxwidth);
	propheight = MIN(propheight, maxheight);
=======
			maxwidth = std::min(maxwidth, m_win_config.width + extrawidth);
		if (m_win_config.height != 0)
			maxheight = std::min(maxheight, m_win_config.height + extraheight);
	}

	// clamp to the maximum
	propwidth = std::min(propwidth, maxwidth);
	propheight = std::min(propheight, maxheight);
>>>>>>> upstream/master

	// compute the visible area based on the proposed rectangle
	m_target->compute_visible_area(propwidth, propheight, pixel_aspect, m_target->orientation(), viswidth, visheight);

	// compute the adjustments we need to make
	adjwidth = (viswidth + extrawidth) - rect.width();
	adjheight = (visheight + extraheight) - rect.height();

	// based on which corner we're adjusting, constrain in different ways
	osd_rect ret(rect);

	switch (adjustment)
	{
		case WMSZ_BOTTOM:
		case WMSZ_BOTTOMRIGHT:
		case WMSZ_RIGHT:
			ret = rect.resize(rect.width() + adjwidth, rect.height() + adjheight);
			break;

		case WMSZ_BOTTOMLEFT:
			ret = rect.move_by(-adjwidth, 0).resize(rect.width() + adjwidth, rect.height() + adjheight);
			break;

		case WMSZ_LEFT:
		case WMSZ_TOPLEFT:
		case WMSZ_TOP:
			ret = rect.move_by(-adjwidth, -adjheight).resize(rect.width() + adjwidth, rect.height() + adjheight);
			break;

		case WMSZ_TOPRIGHT:
			ret = rect.move_by(0, -adjheight).resize(rect.width() + adjwidth, rect.height() + adjheight);
			break;
}
	return ret;
}



//============================================================
//  get_min_bounds
//  (window thread)
//============================================================

osd_dim sdl_window_info::get_min_bounds(int constrain)
{
<<<<<<< HEAD
	INT32 minwidth, minheight;
=======
	int32_t minwidth, minheight;
>>>>>>> upstream/master

	//assert(GetCurrentThreadId() == window_threadid);

	// get the minimum target size
	m_target->compute_minimum_size(minwidth, minheight);

	// expand to our minimum dimensions
	if (minwidth < MIN_WINDOW_DIM)
		minwidth = MIN_WINDOW_DIM;
	if (minheight < MIN_WINDOW_DIM)
		minheight = MIN_WINDOW_DIM;

	// account for extra window stuff
	minwidth += wnd_extra_width();
	minheight += wnd_extra_height();

	// if we want it constrained, figure out which one is larger
<<<<<<< HEAD
	if (constrain)
=======
	if (constrain && m_target->scale_mode() == SCALE_FRACTIONAL)
>>>>>>> upstream/master
	{
		// first constrain with no height limit
		osd_rect test1(0,0,minwidth,10000);
		test1 = constrain_to_aspect_ratio(test1, WMSZ_BOTTOMRIGHT);

		// then constrain with no width limit
		osd_rect test2(0,0,10000,minheight);
		test2 = constrain_to_aspect_ratio(test2, WMSZ_BOTTOMRIGHT);

		// pick the larger
		if (test1.width() > test2.width())
		{
			minwidth = test1.width();
			minheight = test1.height();
		}
		else
		{
			minwidth = test2.width();
			minheight = test2.height();
		}
	}

	// remove extra window stuff
	minwidth -= wnd_extra_width();
	minheight -= wnd_extra_height();

	return osd_dim(minwidth, minheight);
}

<<<<<<< HEAD
=======
//============================================================
//  get_size
//============================================================

osd_dim sdl_window_info::get_size()
{
	int w=0; int h=0;
	SDL_GetWindowSize(platform_window(), &w, &h);
	return osd_dim(w,h);
}
>>>>>>> upstream/master


//============================================================
//  get_max_bounds
//  (window thread)
//============================================================

osd_dim sdl_window_info::get_max_bounds(int constrain)
{
	//assert(GetCurrentThreadId() == window_threadid);

	// compute the maximum client area
	// m_monitor->refresh();
	osd_rect maximum = m_monitor->usuable_position_size();

	// clamp to the window's max
	int tempw = maximum.width();
	int temph = maximum.height();
	if (m_win_config.width != 0)
	{
		int temp = m_win_config.width + wnd_extra_width();
		if (temp < maximum.width())
			tempw = temp;
	}
	if (m_win_config.height != 0)
	{
		int temp = m_win_config.height + wnd_extra_height();
		if (temp < maximum.height())
			temph = temp;
	}

	maximum = maximum.resize(tempw, temph);

	// constrain to fit
<<<<<<< HEAD
	if (constrain)
		maximum = constrain_to_aspect_ratio(maximum, WMSZ_BOTTOMRIGHT);
	else
	{
		maximum = maximum.resize(maximum.width() - wnd_extra_width(), maximum.height() - wnd_extra_height());
	}
	return maximum.dim();
}
=======
	if (constrain && m_target->scale_mode() == SCALE_FRACTIONAL)
		maximum = constrain_to_aspect_ratio(maximum, WMSZ_BOTTOMRIGHT);

	// remove extra window stuff
	maximum = maximum.resize(maximum.width() - wnd_extra_width(), maximum.height() - wnd_extra_height());

	return maximum.dim();
}

//============================================================
//  construction and destruction
//============================================================

sdl_window_info::sdl_window_info(
		running_machine &a_machine,
		int index,
		std::shared_ptr<osd_monitor_info> a_monitor,
		const osd_window_config *config)
	: osd_window_t(*config)
	, m_next(nullptr)
	, m_startmaximized(0)
	// Following three are used by input code to defer resizes
	, m_minimum_dim(0, 0)
	, m_windowed_dim(0, 0)
	, m_rendered_event(0, 1)
	, m_target(nullptr)
	, m_extra_flags(0)
	, m_machine(a_machine)
	, m_monitor(a_monitor)
	, m_fullscreen(0)
	, m_mouse_captured(false)
	, m_mouse_hidden(false)
{
	m_index = index;

	//FIXME: these should be per_window in config-> or even better a bit set
	m_fullscreen = !video_config.windowed;
	m_prescale = video_config.prescale;

	m_windowed_dim = osd_dim(config->width, config->height);
	m_original_mode = global_alloc(SDL_DM_Wrapper);
}

sdl_window_info::~sdl_window_info()
{
	global_free(m_original_mode);
}
>>>>>>> upstream/master
