// license:BSD-3-Clause
// copyright-holders:Aaron Giles
//============================================================
//
//  winmain.h - Win32 main program and core headers
//
//============================================================

#ifndef __WINDOWS_WINMAIN_H__
#define __WINDOWS_WINMAIN_H__

<<<<<<< HEAD
#include "clifront.h"
=======
#include <winapifamily.h>
>>>>>>> upstream/master
#include "osdepend.h"
#include "modules/lib/osdobj_common.h"


//============================================================
//  CONSTANTS
//============================================================

// performance options
#define WINOPTION_PRIORITY              "priority"
#define WINOPTION_PROFILE               "profile"

// video options
#define WINOPTION_MENU                  "menu"

<<<<<<< HEAD
// DirectDraw-specific options
#define WINOPTION_HWSTRETCH             "hwstretch"

// core post-processing options
#define WINOPTION_HLSL_ENABLE               "hlsl_enable"
#define WINOPTION_HLSLPATH                  "hlslpath"
#define WINOPTION_HLSL_PRESCALE_X           "hlsl_prescale_x"
#define WINOPTION_HLSL_PRESCALE_Y           "hlsl_prescale_y"
#define WINOPTION_HLSL_WRITE                "hlsl_write"
#define WINOPTION_HLSL_SNAP_WIDTH           "hlsl_snap_width"
#define WINOPTION_HLSL_SNAP_HEIGHT          "hlsl_snap_height"
=======
// core post-processing options
#define WINOPTION_HLSLPATH                  "hlslpath"
#define WINOPTION_HLSL_ENABLE               "hlsl_enable"
#define WINOPTION_HLSL_OVERSAMPLING         "hlsl_oversampling"
#define WINOPTION_HLSL_WRITE                "hlsl_write"
#define WINOPTION_HLSL_SNAP_WIDTH           "hlsl_snap_width"
#define WINOPTION_HLSL_SNAP_HEIGHT          "hlsl_snap_height"
#define WINOPTION_SHADOW_MASK_TILE_MODE     "shadow_mask_tile_mode"
>>>>>>> upstream/master
#define WINOPTION_SHADOW_MASK_ALPHA         "shadow_mask_alpha"
#define WINOPTION_SHADOW_MASK_TEXTURE       "shadow_mask_texture"
#define WINOPTION_SHADOW_MASK_COUNT_X       "shadow_mask_x_count"
#define WINOPTION_SHADOW_MASK_COUNT_Y       "shadow_mask_y_count"
#define WINOPTION_SHADOW_MASK_USIZE         "shadow_mask_usize"
#define WINOPTION_SHADOW_MASK_VSIZE         "shadow_mask_vsize"
#define WINOPTION_SHADOW_MASK_UOFFSET       "shadow_mask_uoffset"
#define WINOPTION_SHADOW_MASK_VOFFSET       "shadow_mask_voffset"
#define WINOPTION_REFLECTION                "reflection"
<<<<<<< HEAD
#define WINOPTION_CURVATURE                 "curvature"
=======
#define WINOPTION_DISTORTION                "distortion"
#define WINOPTION_CUBIC_DISTORTION          "cubic_distortion"
#define WINOPTION_DISTORT_CORNER            "distort_corner"
>>>>>>> upstream/master
#define WINOPTION_ROUND_CORNER              "round_corner"
#define WINOPTION_SMOOTH_BORDER             "smooth_border"
#define WINOPTION_VIGNETTING                "vignetting"
#define WINOPTION_SCANLINE_AMOUNT           "scanline_alpha"
#define WINOPTION_SCANLINE_SCALE            "scanline_size"
#define WINOPTION_SCANLINE_HEIGHT           "scanline_height"
<<<<<<< HEAD
#define WINOPTION_SCANLINE_BRIGHT_SCALE     "scanline_bright_scale"
#define WINOPTION_SCANLINE_BRIGHT_OFFSET    "scanline_bright_offset"
#define WINOPTION_SCANLINE_OFFSET           "scanline_jitter"
=======
#define WINOPTION_SCANLINE_VARIATION        "scanline_variation"
#define WINOPTION_SCANLINE_BRIGHT_SCALE     "scanline_bright_scale"
#define WINOPTION_SCANLINE_BRIGHT_OFFSET    "scanline_bright_offset"
#define WINOPTION_SCANLINE_JITTER           "scanline_jitter"
#define WINOPTION_HUM_BAR_ALPHA             "hum_bar_alpha"
>>>>>>> upstream/master
#define WINOPTION_DEFOCUS                   "defocus"
#define WINOPTION_CONVERGE_X                "converge_x"
#define WINOPTION_CONVERGE_Y                "converge_y"
#define WINOPTION_RADIAL_CONVERGE_X         "radial_converge_x"
#define WINOPTION_RADIAL_CONVERGE_Y         "radial_converge_y"
#define WINOPTION_RED_RATIO                 "red_ratio"
#define WINOPTION_GRN_RATIO                 "grn_ratio"
#define WINOPTION_BLU_RATIO                 "blu_ratio"
#define WINOPTION_OFFSET                    "offset"
#define WINOPTION_SCALE                     "scale"
#define WINOPTION_POWER                     "power"
#define WINOPTION_FLOOR                     "floor"
#define WINOPTION_PHOSPHOR                  "phosphor_life"
#define WINOPTION_SATURATION                "saturation"
#define WINOPTION_YIQ_ENABLE                "yiq_enable"
<<<<<<< HEAD
=======
#define WINOPTION_YIQ_JITTER                "yiq_jitter"
>>>>>>> upstream/master
#define WINOPTION_YIQ_CCVALUE               "yiq_cc"
#define WINOPTION_YIQ_AVALUE                "yiq_a"
#define WINOPTION_YIQ_BVALUE                "yiq_b"
#define WINOPTION_YIQ_OVALUE                "yiq_o"
#define WINOPTION_YIQ_PVALUE                "yiq_p"
#define WINOPTION_YIQ_NVALUE                "yiq_n"
#define WINOPTION_YIQ_YVALUE                "yiq_y"
#define WINOPTION_YIQ_IVALUE                "yiq_i"
#define WINOPTION_YIQ_QVALUE                "yiq_q"
#define WINOPTION_YIQ_SCAN_TIME             "yiq_scan_time"
#define WINOPTION_YIQ_PHASE_COUNT           "yiq_phase_count"
<<<<<<< HEAD
#define WINOPTION_VECTOR_LENGTH_SCALE       "vector_length_scale"
#define WINOPTION_VECTOR_LENGTH_RATIO       "vector_length_ratio"
#define WINOPTION_VECTOR_TIME_PERIOD        "vector_time_period"
=======
#define WINOPTION_VECTOR_BEAM_SMOOTH        "vector_beam_smooth"
#define WINOPTION_VECTOR_LENGTH_SCALE       "vector_length_scale"
#define WINOPTION_VECTOR_LENGTH_RATIO       "vector_length_ratio"
#define WINOPTION_BLOOM_BLEND_MODE          "bloom_blend_mode"
>>>>>>> upstream/master
#define WINOPTION_BLOOM_SCALE               "bloom_scale"
#define WINOPTION_BLOOM_OVERDRIVE           "bloom_overdrive"
#define WINOPTION_BLOOM_LEVEL0_WEIGHT       "bloom_lvl0_weight"
#define WINOPTION_BLOOM_LEVEL1_WEIGHT       "bloom_lvl1_weight"
#define WINOPTION_BLOOM_LEVEL2_WEIGHT       "bloom_lvl2_weight"
#define WINOPTION_BLOOM_LEVEL3_WEIGHT       "bloom_lvl3_weight"
#define WINOPTION_BLOOM_LEVEL4_WEIGHT       "bloom_lvl4_weight"
#define WINOPTION_BLOOM_LEVEL5_WEIGHT       "bloom_lvl5_weight"
#define WINOPTION_BLOOM_LEVEL6_WEIGHT       "bloom_lvl6_weight"
#define WINOPTION_BLOOM_LEVEL7_WEIGHT       "bloom_lvl7_weight"
#define WINOPTION_BLOOM_LEVEL8_WEIGHT       "bloom_lvl8_weight"
<<<<<<< HEAD
#define WINOPTION_BLOOM_LEVEL9_WEIGHT       "bloom_lvl9_weight"
#define WINOPTION_BLOOM_LEVEL10_WEIGHT      "bloom_lvl10_weight"
=======
>>>>>>> upstream/master

// full screen options
#define WINOPTION_TRIPLEBUFFER          "triplebuffer"
#define WINOPTION_FULLSCREENBRIGHTNESS  "full_screen_brightness"
#define WINOPTION_FULLSCREENCONTRAST    "full_screen_contrast"
#define WINOPTION_FULLSCREENGAMMA       "full_screen_gamma"

<<<<<<< HEAD
#ifdef USE_AUDIO_SYNC
#define WINOPTION_AUDIO_SYNC            "audio_sync"
#endif /* USE_AUDIO_SYNC */

=======
>>>>>>> upstream/master
// input options
#define WINOPTION_GLOBAL_INPUTS         "global_inputs"
#define WINOPTION_DUAL_LIGHTGUN         "dual_lightgun"

<<<<<<< HEAD
#ifdef JOYSTICK_ID
#define WINOPTION_JOYID1                "joyid1"
#define WINOPTION_JOYID2                "joyid2"
#define WINOPTION_JOYID3                "joyid3"
#define WINOPTION_JOYID4                "joyid4"
#define WINOPTION_JOYID5                "joyid5"
#define WINOPTION_JOYID6                "joyid6"
#define WINOPTION_JOYID7                "joyid7"
#define WINOPTION_JOYID8                "joyid8"
#endif /* JOYSTICK_ID */



=======
>>>>>>> upstream/master
//============================================================
//  TYPE DEFINITIONS
//============================================================

class windows_options : public osd_options
{
public:
	// construction/destruction
	windows_options();

	// performance options
	int priority() const { return int_value(WINOPTION_PRIORITY); }
	int profile() const { return int_value(WINOPTION_PROFILE); }

	// video options
	bool menu() const { return bool_value(WINOPTION_MENU); }

<<<<<<< HEAD
	// DirectDraw-specific options
	bool hwstretch() const { return bool_value(WINOPTION_HWSTRETCH); }

	// core post-processing options
	const char *screen_post_fx_dir() const { return value(WINOPTION_HLSLPATH); }
	bool d3d_hlsl_enable() const { return bool_value(WINOPTION_HLSL_ENABLE); }
	const char *d3d_hlsl_write() const { return value(WINOPTION_HLSL_WRITE); }
	int d3d_hlsl_prescale_x() const { return int_value(WINOPTION_HLSL_PRESCALE_X); }
	int d3d_hlsl_prescale_y() const { return int_value(WINOPTION_HLSL_PRESCALE_Y); }
	int d3d_snap_width() const { return int_value(WINOPTION_HLSL_SNAP_WIDTH); }
	int d3d_snap_height() const { return int_value(WINOPTION_HLSL_SNAP_HEIGHT); }
=======
	// core post-processing options
	const char *screen_post_fx_dir() const { return value(WINOPTION_HLSLPATH); }
	bool d3d_hlsl_enable() const { return bool_value(WINOPTION_HLSL_ENABLE); }
	bool d3d_hlsl_oversampling() const { return bool_value(WINOPTION_HLSL_OVERSAMPLING); }
	const char *d3d_hlsl_write() const { return value(WINOPTION_HLSL_WRITE); }
	int d3d_snap_width() const { return int_value(WINOPTION_HLSL_SNAP_WIDTH); }
	int d3d_snap_height() const { return int_value(WINOPTION_HLSL_SNAP_HEIGHT); }
	int screen_shadow_mask_tile_mode() const { return int_value(WINOPTION_SHADOW_MASK_TILE_MODE); }
>>>>>>> upstream/master
	float screen_shadow_mask_alpha() const { return float_value(WINOPTION_SHADOW_MASK_ALPHA); }
	const char *screen_shadow_mask_texture() const { return value(WINOPTION_SHADOW_MASK_TEXTURE); }
	int screen_shadow_mask_count_x() const { return int_value(WINOPTION_SHADOW_MASK_COUNT_X); }
	int screen_shadow_mask_count_y() const { return int_value(WINOPTION_SHADOW_MASK_COUNT_Y); }
	float screen_shadow_mask_u_size() const { return float_value(WINOPTION_SHADOW_MASK_USIZE); }
	float screen_shadow_mask_v_size() const { return float_value(WINOPTION_SHADOW_MASK_VSIZE); }
	float screen_shadow_mask_u_offset() const { return float_value(WINOPTION_SHADOW_MASK_UOFFSET); }
	float screen_shadow_mask_v_offset() const { return float_value(WINOPTION_SHADOW_MASK_VOFFSET); }
	float screen_scanline_amount() const { return float_value(WINOPTION_SCANLINE_AMOUNT); }
	float screen_scanline_scale() const { return float_value(WINOPTION_SCANLINE_SCALE); }
	float screen_scanline_height() const { return float_value(WINOPTION_SCANLINE_HEIGHT); }
<<<<<<< HEAD
	float screen_scanline_bright_scale() const { return float_value(WINOPTION_SCANLINE_BRIGHT_SCALE); }
	float screen_scanline_bright_offset() const { return float_value(WINOPTION_SCANLINE_BRIGHT_OFFSET); }
	float screen_scanline_offset() const { return float_value(WINOPTION_SCANLINE_OFFSET); }
	float screen_reflection() const { return float_value(WINOPTION_REFLECTION); }
	float screen_curvature() const { return float_value(WINOPTION_CURVATURE); }
=======
	float screen_scanline_variation() const { return float_value(WINOPTION_SCANLINE_VARIATION); }
	float screen_scanline_bright_scale() const { return float_value(WINOPTION_SCANLINE_BRIGHT_SCALE); }
	float screen_scanline_bright_offset() const { return float_value(WINOPTION_SCANLINE_BRIGHT_OFFSET); }
	float screen_scanline_jitter() const { return float_value(WINOPTION_SCANLINE_JITTER); }
	float screen_hum_bar_alpha() const { return float_value(WINOPTION_HUM_BAR_ALPHA); }
	float screen_reflection() const { return float_value(WINOPTION_REFLECTION); }
	float screen_distortion() const { return float_value(WINOPTION_DISTORTION); }
	float screen_cubic_distortion() const { return float_value(WINOPTION_CUBIC_DISTORTION); }
	float screen_distort_corner() const { return float_value(WINOPTION_DISTORT_CORNER); }
>>>>>>> upstream/master
	float screen_round_corner() const { return float_value(WINOPTION_ROUND_CORNER); }
	float screen_smooth_border() const { return float_value(WINOPTION_SMOOTH_BORDER); }
	float screen_vignetting() const { return float_value(WINOPTION_VIGNETTING); }
	const char *screen_defocus() const { return value(WINOPTION_DEFOCUS); }
	const char *screen_converge_x() const { return value(WINOPTION_CONVERGE_X); }
	const char *screen_converge_y() const { return value(WINOPTION_CONVERGE_Y); }
	const char *screen_radial_converge_x() const { return value(WINOPTION_RADIAL_CONVERGE_X); }
	const char *screen_radial_converge_y() const { return value(WINOPTION_RADIAL_CONVERGE_Y); }
	const char *screen_red_ratio() const { return value(WINOPTION_RED_RATIO); }
	const char *screen_grn_ratio() const { return value(WINOPTION_GRN_RATIO); }
	const char *screen_blu_ratio() const { return value(WINOPTION_BLU_RATIO); }
	bool screen_yiq_enable() const { return bool_value(WINOPTION_YIQ_ENABLE); }
<<<<<<< HEAD
=======
	float screen_yiq_jitter() const { return float_value(WINOPTION_YIQ_JITTER); }
>>>>>>> upstream/master
	float screen_yiq_cc() const { return float_value(WINOPTION_YIQ_CCVALUE); }
	float screen_yiq_a() const { return float_value(WINOPTION_YIQ_AVALUE); }
	float screen_yiq_b() const { return float_value(WINOPTION_YIQ_BVALUE); }
	float screen_yiq_o() const { return float_value(WINOPTION_YIQ_OVALUE); }
	float screen_yiq_p() const { return float_value(WINOPTION_YIQ_PVALUE); }
	float screen_yiq_n() const { return float_value(WINOPTION_YIQ_NVALUE); }
	float screen_yiq_y() const { return float_value(WINOPTION_YIQ_YVALUE); }
	float screen_yiq_i() const { return float_value(WINOPTION_YIQ_IVALUE); }
	float screen_yiq_q() const { return float_value(WINOPTION_YIQ_QVALUE); }
	float screen_yiq_scan_time() const { return float_value(WINOPTION_YIQ_SCAN_TIME); }
	int screen_yiq_phase_count() const { return int_value(WINOPTION_YIQ_PHASE_COUNT); }
<<<<<<< HEAD
	float screen_vector_length_scale() const { return float_value(WINOPTION_VECTOR_LENGTH_SCALE); }
	float screen_vector_length_ratio() const { return float_value(WINOPTION_VECTOR_LENGTH_RATIO); }
	float screen_vector_time_period() const { return float_value(WINOPTION_VECTOR_TIME_PERIOD); }
=======
	float screen_vector_beam_smooth() const { return float_value(WINOPTION_VECTOR_BEAM_SMOOTH); }
	float screen_vector_length_scale() const { return float_value(WINOPTION_VECTOR_LENGTH_SCALE); }
	float screen_vector_length_ratio() const { return float_value(WINOPTION_VECTOR_LENGTH_RATIO); }
	int screen_bloom_blend_mode() const { return int_value(WINOPTION_BLOOM_BLEND_MODE); }
>>>>>>> upstream/master
	float screen_bloom_scale() const { return float_value(WINOPTION_BLOOM_SCALE); }
	const char *screen_bloom_overdrive() const { return value(WINOPTION_BLOOM_OVERDRIVE); }
	float screen_bloom_lvl0_weight() const { return float_value(WINOPTION_BLOOM_LEVEL0_WEIGHT); }
	float screen_bloom_lvl1_weight() const { return float_value(WINOPTION_BLOOM_LEVEL1_WEIGHT); }
	float screen_bloom_lvl2_weight() const { return float_value(WINOPTION_BLOOM_LEVEL2_WEIGHT); }
	float screen_bloom_lvl3_weight() const { return float_value(WINOPTION_BLOOM_LEVEL3_WEIGHT); }
	float screen_bloom_lvl4_weight() const { return float_value(WINOPTION_BLOOM_LEVEL4_WEIGHT); }
	float screen_bloom_lvl5_weight() const { return float_value(WINOPTION_BLOOM_LEVEL5_WEIGHT); }
	float screen_bloom_lvl6_weight() const { return float_value(WINOPTION_BLOOM_LEVEL6_WEIGHT); }
	float screen_bloom_lvl7_weight() const { return float_value(WINOPTION_BLOOM_LEVEL7_WEIGHT); }
	float screen_bloom_lvl8_weight() const { return float_value(WINOPTION_BLOOM_LEVEL8_WEIGHT); }
<<<<<<< HEAD
	float screen_bloom_lvl9_weight() const { return float_value(WINOPTION_BLOOM_LEVEL9_WEIGHT); }
	float screen_bloom_lvl10_weight() const { return float_value(WINOPTION_BLOOM_LEVEL10_WEIGHT); }
=======
>>>>>>> upstream/master
	const char *screen_offset() const { return value(WINOPTION_OFFSET); }
	const char *screen_scale() const { return value(WINOPTION_SCALE); }
	const char *screen_power() const { return value(WINOPTION_POWER); }
	const char *screen_floor() const { return value(WINOPTION_FLOOR); }
	const char *screen_phosphor() const { return value(WINOPTION_PHOSPHOR); }
	float screen_saturation() const { return float_value(WINOPTION_SATURATION); }

	// full screen options
	bool triple_buffer() const { return bool_value(WINOPTION_TRIPLEBUFFER); }
	float full_screen_brightness() const { return float_value(WINOPTION_FULLSCREENBRIGHTNESS); }
	float full_screen_contrast() const { return float_value(WINOPTION_FULLSCREENCONTRAST); }
	float full_screen_gamma() const { return float_value(WINOPTION_FULLSCREENGAMMA); }

	// input options
	bool global_inputs() const { return bool_value(WINOPTION_GLOBAL_INPUTS); }
	bool dual_lightgun() const { return bool_value(WINOPTION_DUAL_LIGHTGUN); }

private:
	static const options_entry s_option_entries[];
};

<<<<<<< HEAD


=======
>>>>>>> upstream/master
//============================================================
//  MACROS
//============================================================

#ifdef __cplusplus
#define WRAP_REFIID(x)      x
#else
#define WRAP_REFIID(x)      &x
#endif



//============================================================
//  TYPE DEFINITIONS
//============================================================

<<<<<<< HEAD
class windows_osd_interface : public osd_common_t
{
=======
enum input_event
{
	INPUT_EVENT_KEYDOWN,
	INPUT_EVENT_KEYUP,
	INPUT_EVENT_RAWINPUT,
	INPUT_EVENT_MOUSE_BUTTON
};

struct KeyPressEventArgs
{
	input_event event_id;
	uint8_t vkey;
	uint8_t scancode;
};

struct MouseButtonEventArgs
{
	int button;
	int keydown;
	int xpos;
	int ypos;
};

// Forward declarations
struct _EXCEPTION_POINTERS;

class windows_osd_interface : public osd_common_t
{
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
	// Access to exception filter static method
	friend int main(int argc, char *argv[]);
#endif

>>>>>>> upstream/master
public:
	// construction/destruction
	windows_osd_interface(windows_options &options);
	virtual ~windows_osd_interface();

	// general overridables
<<<<<<< HEAD
	virtual void init(running_machine &machine);
	virtual void update(bool skip_redraw);

	// video overridables
	virtual void *get_slider_list();

	// input overridables
	virtual void customize_input_type_list(simple_list<input_type_entry> &typelist);

	virtual void video_register();

	virtual bool video_init();
	virtual bool window_init();
	virtual bool input_init();
	virtual void input_pause();
	virtual void input_resume();
	virtual bool output_init();

	virtual void video_exit();
	virtual void window_exit();
	virtual void input_exit();
	virtual void output_exit();

	void extract_video_config();

	windows_options &options() { return m_options; }

private:
	void osd_exit();
	windows_options &m_options;
=======
	virtual void init(running_machine &machine) override;
	virtual void update(bool skip_redraw) override;

	// input overrideables
	virtual void customize_input_type_list(simple_list<input_type_entry> &typelist) override;

	// video overridables
	virtual void add_audio_to_recording(const int16_t *buffer, int samples_this_frame) override;

	virtual void video_register() override;

	virtual bool video_init() override;
	virtual bool window_init() override;

	virtual void video_exit() override;
	virtual void window_exit() override;

	void extract_video_config();

	// windows osd specific
	bool handle_input_event(input_event eventid, void *eventdata) const;
	bool should_hide_mouse() const;
	void poll_input(running_machine &machine) const;

	virtual windows_options &options() override { return m_options; }

	int window_count();

protected:
	virtual void build_slider_list() override;
	virtual void update_slider_list() override;

	void check_osd_inputs();

private:
	virtual void osd_exit() override;
	void output_oslog(const char *buffer);

	windows_options &   m_options;
>>>>>>> upstream/master

	static const int DEFAULT_FONT_HEIGHT = 200;
};

<<<<<<< HEAD

=======
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ref class MameMainApp sealed : public Windows::ApplicationModel::Core::IFrameworkView
{
private:
	std::unique_ptr<windows_options>        m_options;
	std::unique_ptr<windows_osd_interface>  m_osd;

public:
	MameMainApp();

	// IFrameworkView Methods.
	virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView);
	virtual void SetWindow(Windows::UI::Core::CoreWindow^ window);
	virtual void Load(Platform::String^ entryPoint);
	virtual void Run();
	virtual void Uninitialize();
};

ref class MameViewSource sealed : Windows::ApplicationModel::Core::IFrameworkViewSource
{
public:
	virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView();
};

#endif
>>>>>>> upstream/master

//============================================================
//  GLOBAL VARIABLES
//============================================================

extern const options_entry mame_win_options[];

// defined in winwork.c
extern int osd_num_processors;


<<<<<<< HEAD

//============================================================
//  FUNCTION PROTOTYPES
//============================================================

// use this to ping the watchdog
void winmain_watchdog_ping(void);
void winmain_dump_stack();

#endif
=======
#endif
>>>>>>> upstream/master
