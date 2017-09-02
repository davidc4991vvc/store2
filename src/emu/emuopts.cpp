// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

<<<<<<< HEAD
    emuopts.c
=======
    emuopts.cpp
>>>>>>> upstream/master

    Options file and command line management.

***************************************************************************/

#include "emu.h"
#include "emuopts.h"
#include "drivenum.h"
<<<<<<< HEAD
#include "clifront.h"

#include <ctype.h>

=======
#include "softlist_dev.h"
#include "hashfile.h"

#include <stack>
>>>>>>> upstream/master


//**************************************************************************
//  CORE EMULATOR OPTIONS
//**************************************************************************

const options_entry emu_options::s_option_entries[] =
{
	// unadorned options - only a single one supported at the moment
<<<<<<< HEAD
	{ OPTION_SYSTEMNAME,                                 NULL,        OPTION_STRING,     NULL },
	{ OPTION_SOFTWARENAME,                               NULL,        OPTION_STRING,     NULL },

	// config options
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE CONFIGURATION OPTIONS" },
	{ OPTION_READCONFIG ";rc",                           "1",         OPTION_BOOLEAN,    "enable loading of configuration files" },
	{ OPTION_WRITECONFIG ";wc",                          "0",         OPTION_BOOLEAN,    "writes configuration to (driver).ini on exit" },
#ifdef DRIVER_SWITCH
	{ OPTION_DRIVER_CONFIG,                              "all",       OPTION_STRING,     "switch drivers"},
	{ OPTION_DISABLE_MECHANICAL_DRIVER,                  "0",         OPTION_BOOLEAN,    "disable mechanical drivers"},
#endif /* DRIVER_SWITCH */

	// seach path options
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE SEARCH PATH OPTIONS" },
=======
	{ OPTION_SYSTEMNAME,                                 nullptr,     OPTION_STRING,     nullptr },
	{ OPTION_SOFTWARENAME,                               nullptr,     OPTION_STRING,     nullptr },

	// config options
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE CONFIGURATION OPTIONS" },
	{ OPTION_READCONFIG ";rc",                           "1",         OPTION_BOOLEAN,    "enable loading of configuration files" },
	{ OPTION_WRITECONFIG ";wc",                          "0",         OPTION_BOOLEAN,    "writes configuration to (driver).ini on exit" },

	// search path options
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE SEARCH PATH OPTIONS" },
	{ OPTION_HOMEPATH,                                   ".",         OPTION_STRING,     "path to home directory (read/write) location" },
>>>>>>> upstream/master
	{ OPTION_MEDIAPATH ";rp;biospath;bp",                "roms",      OPTION_STRING,     "path to ROMsets and hard disk images" },
	{ OPTION_HASHPATH ";hash_directory;hash",            "hash",      OPTION_STRING,     "path to hash files" },
	{ OPTION_SAMPLEPATH ";sp",                           "samples",   OPTION_STRING,     "path to samplesets" },
	{ OPTION_ARTPATH,                                    "artwork",   OPTION_STRING,     "path to artwork files" },
	{ OPTION_CTRLRPATH,                                  "ctrlr",     OPTION_STRING,     "path to controller definitions" },
<<<<<<< HEAD
	{ OPTION_INIPATH,                                    "ini",       OPTION_STRING,     "path to ini files" },
	{ OPTION_FONTPATH,                                   ".",         OPTION_STRING,     "path to font files" },
	{ OPTION_CHEATPATH,                                  "cheat",     OPTION_STRING,     "path to cheat files" },
	{ OPTION_CROSSHAIRPATH,                              "crosshair", OPTION_STRING,     "path to crosshair files" },
	{ OPTION_LANGPATH,                                   "lang",      OPTION_STRING,     "path to localized languages and datafiles" },
#ifdef USE_IPS
	{ OPTION_IPSPATH,                                    "ips",       OPTION_STRING,     "path to ips files" },
#endif /* USE_IPS */

	// output directory options
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE OUTPUT DIRECTORY OPTIONS" },
=======
	{ OPTION_INIPATH,                                    ".;ini;ini/presets",     OPTION_STRING,     "path to ini files" },
	{ OPTION_FONTPATH,                                   ".",         OPTION_STRING,     "path to font files" },
	{ OPTION_CHEATPATH,                                  "cheat",     OPTION_STRING,     "path to cheat files" },
	{ OPTION_CROSSHAIRPATH,                              "crosshair", OPTION_STRING,     "path to crosshair files" },
	{ OPTION_PLUGINSPATH,                                "plugins",   OPTION_STRING,     "path to plugin files" },
	{ OPTION_LANGUAGEPATH,                               "language",  OPTION_STRING,     "path to language files" },
	{ OPTION_SWPATH,                                     "software",  OPTION_STRING,     "path to loose software" },

	// output directory options
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE OUTPUT DIRECTORY OPTIONS" },
>>>>>>> upstream/master
	{ OPTION_CFG_DIRECTORY,                              "cfg",       OPTION_STRING,     "directory to save configurations" },
	{ OPTION_NVRAM_DIRECTORY,                            "nvram",     OPTION_STRING,     "directory to save nvram contents" },
	{ OPTION_INPUT_DIRECTORY,                            "inp",       OPTION_STRING,     "directory to save input device logs" },
	{ OPTION_STATE_DIRECTORY,                            "sta",       OPTION_STRING,     "directory to save states" },
<<<<<<< HEAD
	{ OPTION_SNAPSHOT_DIRECTORY,                         "snap",      OPTION_STRING,     "directory to save screenshots" },
	{ OPTION_DIFF_DIRECTORY,                             "diff",      OPTION_STRING,     "directory to save hard drive image difference files" },
	{ OPTION_COMMENT_DIRECTORY,                          "comments",  OPTION_STRING,     "directory to save debugger comments" },
#ifdef USE_HISCORE
	{ "hiscore_directory",                               "hi",        OPTION_STRING,     "directory to save hiscores" },
#endif /* USE_HISCORE */
#ifdef CMD_LIST
	{ OPTION_COMMAND_FILE,                               "command.dat",OPTION_STRING,    "command list database name" },
#endif /* CMD_LIST */
#ifdef USE_HISCORE
	{ OPTION_HISCORE_FILE,                               "hiscore.dat",OPTION_STRING,    "high score database name" },
#endif /* USE_HISCORE */

	// state/playback options
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE STATE/PLAYBACK OPTIONS" },
	{ OPTION_STATE,                                      NULL,        OPTION_STRING,     "saved state to load" },
	{ OPTION_AUTOSAVE,                                   "0",         OPTION_BOOLEAN,    "enable automatic restore at startup, and automatic save at exit time" },
	{ OPTION_PLAYBACK ";pb",                             NULL,        OPTION_STRING,     "playback an input file" },
	{ OPTION_RECORD ";rec",                              NULL,        OPTION_STRING,     "record an input file" },
	{ OPTION_MNGWRITE,                                   NULL,        OPTION_STRING,     "optional filename to write a MNG movie of the current session" },
	{ OPTION_AVIWRITE,                                   NULL,        OPTION_STRING,     "optional filename to write an AVI movie of the current session" },
#ifdef MAME_DEBUG
	{ OPTION_DUMMYWRITE,                                 "0",         OPTION_BOOLEAN,    "indicates if a snapshot should be created if each frame" },
#endif
	{ OPTION_WAVWRITE,                                   NULL,        OPTION_STRING,     "optional filename to write a WAV file of the current session" },
=======
	{ OPTION_SNAPSHOT_DIRECTORY,                         "snap",      OPTION_STRING,     "directory to save/load screenshots" },
	{ OPTION_DIFF_DIRECTORY,                             "diff",      OPTION_STRING,     "directory to save hard drive image difference files" },
	{ OPTION_COMMENT_DIRECTORY,                          "comments",  OPTION_STRING,     "directory to save debugger comments" },

	// state/playback options
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE STATE/PLAYBACK OPTIONS" },
	{ OPTION_STATE,                                      nullptr,     OPTION_STRING,     "saved state to load" },
	{ OPTION_AUTOSAVE,                                   "0",         OPTION_BOOLEAN,    "enable automatic restore at startup, and automatic save at exit time" },
	{ OPTION_PLAYBACK ";pb",                             nullptr,     OPTION_STRING,     "playback an input file" },
	{ OPTION_RECORD ";rec",                              nullptr,     OPTION_STRING,     "record an input file" },
	{ OPTION_RECORD_TIMECODE,                            "0",         OPTION_BOOLEAN,    "record an input timecode file (requires -record option)" },
	{ OPTION_EXIT_AFTER_PLAYBACK,                        "0",         OPTION_BOOLEAN,    "close the program at the end of playback" },

	{ OPTION_MNGWRITE,                                   nullptr,     OPTION_STRING,     "optional filename to write a MNG movie of the current session" },
	{ OPTION_AVIWRITE,                                   nullptr,     OPTION_STRING,     "optional filename to write an AVI movie of the current session" },
	{ OPTION_WAVWRITE,                                   nullptr,     OPTION_STRING,     "optional filename to write a WAV file of the current session" },
>>>>>>> upstream/master
	{ OPTION_SNAPNAME,                                   "%g/%i",     OPTION_STRING,     "override of the default snapshot/movie naming; %g == gamename, %i == index" },
	{ OPTION_SNAPSIZE,                                   "auto",      OPTION_STRING,     "specify snapshot/movie resolution (<width>x<height>) or 'auto' to use minimal size " },
	{ OPTION_SNAPVIEW,                                   "internal",  OPTION_STRING,     "specify snapshot/movie view or 'internal' to use internal pixel-aspect views" },
	{ OPTION_SNAPBILINEAR,                               "1",         OPTION_BOOLEAN,    "specify if the snapshot/movie should have bilinear filtering applied" },
	{ OPTION_STATENAME,                                  "%g",        OPTION_STRING,     "override of the default state subfolder naming; %g == gamename" },
	{ OPTION_BURNIN,                                     "0",         OPTION_BOOLEAN,    "create burn-in snapshots for each screen" },

	// performance options
<<<<<<< HEAD
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE PERFORMANCE OPTIONS" },
=======
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE PERFORMANCE OPTIONS" },
>>>>>>> upstream/master
	{ OPTION_AUTOFRAMESKIP ";afs",                       "0",         OPTION_BOOLEAN,    "enable automatic frameskip selection" },
	{ OPTION_FRAMESKIP ";fs(0-10)",                      "0",         OPTION_INTEGER,    "set frameskip to fixed value, 0-10 (autoframeskip must be disabled)" },
	{ OPTION_SECONDS_TO_RUN ";str",                      "0",         OPTION_INTEGER,    "number of emulated seconds to run before automatically exiting" },
	{ OPTION_THROTTLE,                                   "1",         OPTION_BOOLEAN,    "enable throttling to keep game running in sync with real time" },
	{ OPTION_SLEEP,                                      "1",         OPTION_BOOLEAN,    "enable sleeping, which gives time back to other applications when idle" },
	{ OPTION_SPEED "(0.01-100)",                         "1.0",       OPTION_FLOAT,      "controls the speed of gameplay, relative to realtime; smaller numbers are slower" },
	{ OPTION_REFRESHSPEED ";rs",                         "0",         OPTION_BOOLEAN,    "automatically adjusts the speed of gameplay to keep the refresh rate lower than the screen" },

<<<<<<< HEAD
	// rotation options
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE ROTATION OPTIONS" },
=======
	// render options
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE RENDER OPTIONS" },
	{ OPTION_KEEPASPECT ";ka",                           "1",         OPTION_BOOLEAN,    "constrain to the proper aspect ratio" },
	{ OPTION_UNEVENSTRETCH ";ues",                       "1",         OPTION_BOOLEAN,    "allow non-integer stretch factors" },
	{ OPTION_UNEVENSTRETCHX ";uesx",                     "0",         OPTION_BOOLEAN,    "allow non-integer stretch factors only on horizontal axis"},
	{ OPTION_UNEVENSTRETCHY ";uesy",                     "0",         OPTION_BOOLEAN,    "allow non-integer stretch factors only on vertical axis"},
	{ OPTION_AUTOSTRETCHXY ";asxy",                      "0",         OPTION_BOOLEAN,    "automatically apply -unevenstretchx/y based on source native orientation"},
	{ OPTION_INTOVERSCAN ";ios",                         "0",         OPTION_BOOLEAN,    "allow overscan on integer scaled targets"},
	{ OPTION_INTSCALEX ";sx",                            "0",         OPTION_INTEGER,    "set horizontal integer scale factor."},
	{ OPTION_INTSCALEY ";sy",                            "0",         OPTION_INTEGER,    "set vertical integer scale."},

	// rotation options
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE ROTATION OPTIONS" },
>>>>>>> upstream/master
	{ OPTION_ROTATE,                                     "1",         OPTION_BOOLEAN,    "rotate the game screen according to the game's orientation needs it" },
	{ OPTION_ROR,                                        "0",         OPTION_BOOLEAN,    "rotate screen clockwise 90 degrees" },
	{ OPTION_ROL,                                        "0",         OPTION_BOOLEAN,    "rotate screen counterclockwise 90 degrees" },
	{ OPTION_AUTOROR,                                    "0",         OPTION_BOOLEAN,    "automatically rotate screen clockwise 90 degrees if vertical" },
	{ OPTION_AUTOROL,                                    "0",         OPTION_BOOLEAN,    "automatically rotate screen counterclockwise 90 degrees if vertical" },
	{ OPTION_FLIPX,                                      "0",         OPTION_BOOLEAN,    "flip screen left-right" },
	{ OPTION_FLIPY,                                      "0",         OPTION_BOOLEAN,    "flip screen upside-down" },

	// artwork options
<<<<<<< HEAD
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE ARTWORK OPTIONS" },
=======
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE ARTWORK OPTIONS" },
>>>>>>> upstream/master
	{ OPTION_ARTWORK_CROP ";artcrop",                    "0",         OPTION_BOOLEAN,    "crop artwork to game screen size" },
	{ OPTION_USE_BACKDROPS ";backdrop",                  "1",         OPTION_BOOLEAN,    "enable backdrops if artwork is enabled and available" },
	{ OPTION_USE_OVERLAYS ";overlay",                    "1",         OPTION_BOOLEAN,    "enable overlays if artwork is enabled and available" },
	{ OPTION_USE_BEZELS ";bezel",                        "1",         OPTION_BOOLEAN,    "enable bezels if artwork is enabled and available" },
	{ OPTION_USE_CPANELS ";cpanel",                      "1",         OPTION_BOOLEAN,    "enable cpanels if artwork is enabled and available" },
	{ OPTION_USE_MARQUEES ";marquee",                    "1",         OPTION_BOOLEAN,    "enable marquees if artwork is enabled and available" },

	// screen options
<<<<<<< HEAD
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE SCREEN OPTIONS" },
=======
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE SCREEN OPTIONS" },
>>>>>>> upstream/master
	{ OPTION_BRIGHTNESS "(0.1-2.0)",                     "1.0",       OPTION_FLOAT,      "default game screen brightness correction" },
	{ OPTION_CONTRAST "(0.1-2.0)",                       "1.0",       OPTION_FLOAT,      "default game screen contrast correction" },
	{ OPTION_GAMMA "(0.1-3.0)",                          "1.0",       OPTION_FLOAT,      "default game screen gamma correction" },
	{ OPTION_PAUSE_BRIGHTNESS "(0.0-1.0)",               "0.65",      OPTION_FLOAT,      "amount to scale the screen brightness when paused" },
	{ OPTION_EFFECT,                                     "none",      OPTION_STRING,     "name of a PNG file to use for visual effects, or 'none'" },
<<<<<<< HEAD
#ifdef USE_SCALE_EFFECTS
	{ OPTION_SCALE_EFFECT,                               "none",      OPTION_STRING,     "image enhancement effect" },
#endif /* USE_SCALE_EFFECTS */

	// vector options
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE VECTOR OPTIONS" },
	{ OPTION_ANTIALIAS ";aa",                            "1",         OPTION_BOOLEAN,    "use antialiasing when drawing vectors" },
=======

	// vector options
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE VECTOR OPTIONS" },
>>>>>>> upstream/master
	{ OPTION_BEAM_WIDTH_MIN,                             "1.0",       OPTION_FLOAT,      "set vector beam width minimum" },
	{ OPTION_BEAM_WIDTH_MAX,                             "1.0",       OPTION_FLOAT,      "set vector beam width maximum" },
	{ OPTION_BEAM_INTENSITY_WEIGHT,                      "0",         OPTION_FLOAT,      "set vector beam intensity weight " },
	{ OPTION_FLICKER,                                    "0",         OPTION_FLOAT,      "set vector flicker effect" },

	// sound options
<<<<<<< HEAD
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE SOUND OPTIONS" },
=======
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE SOUND OPTIONS" },
>>>>>>> upstream/master
	{ OPTION_SAMPLERATE ";sr(1000-1000000)",             "48000",     OPTION_INTEGER,    "set sound output sample rate" },
	{ OPTION_SAMPLES,                                    "1",         OPTION_BOOLEAN,    "enable the use of external samples if available" },
	{ OPTION_VOLUME ";vol",                              "0",         OPTION_INTEGER,    "sound volume in decibels (-32 min, 0 max)" },

	// input options
<<<<<<< HEAD
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE INPUT OPTIONS" },
	{ OPTION_COIN_LOCKOUT ";coinlock",                   "1",         OPTION_BOOLEAN,    "enable coin lockouts to actually lock out coins" },
	{ OPTION_CTRLR,                                      NULL,        OPTION_STRING,     "preconfigure for specified controller" },
=======
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE INPUT OPTIONS" },
	{ OPTION_COIN_LOCKOUT ";coinlock",                   "1",         OPTION_BOOLEAN,    "enable coin lockouts to actually lock out coins" },
	{ OPTION_CTRLR,                                      nullptr,     OPTION_STRING,     "preconfigure for specified controller" },
>>>>>>> upstream/master
	{ OPTION_MOUSE,                                      "0",         OPTION_BOOLEAN,    "enable mouse input" },
	{ OPTION_JOYSTICK ";joy",                            "1",         OPTION_BOOLEAN,    "enable joystick input" },
	{ OPTION_LIGHTGUN ";gun",                            "0",         OPTION_BOOLEAN,    "enable lightgun input" },
	{ OPTION_MULTIKEYBOARD ";multikey",                  "0",         OPTION_BOOLEAN,    "enable separate input from each keyboard device (if present)" },
	{ OPTION_MULTIMOUSE,                                 "0",         OPTION_BOOLEAN,    "enable separate input from each mouse device (if present)" },
	{ OPTION_STEADYKEY ";steady",                        "0",         OPTION_BOOLEAN,    "enable steadykey support" },
	{ OPTION_UI_ACTIVE,                                  "0",         OPTION_BOOLEAN,    "enable user interface on top of emulated keyboard (if present)" },
	{ OPTION_OFFSCREEN_RELOAD ";reload",                 "0",         OPTION_BOOLEAN,    "convert lightgun button 2 into offscreen reload" },
	{ OPTION_JOYSTICK_MAP ";joymap",                     "auto",      OPTION_STRING,     "explicit joystick map, or auto to auto-select" },
<<<<<<< HEAD
	{ OPTION_JOYSTICK_DEADZONE ";joy_deadzone;jdz",      "0.3",       OPTION_FLOAT,      "center deadzone range for joystick where change is ignored (0.0 center, 1.0 end)" },
	{ OPTION_JOYSTICK_SATURATION ";joy_saturation;jsat", "0.85",      OPTION_FLOAT,      "end of axis saturation range for joystick where change is ignored (0.0 center, 1.0 end)" },
=======
	{ OPTION_JOYSTICK_DEADZONE ";joy_deadzone;jdz(0.00-1)",      "0.3",       OPTION_FLOAT,      "center deadzone range for joystick where change is ignored (0.0 center, 1.0 end)" },
	{ OPTION_JOYSTICK_SATURATION ";joy_saturation;jsat(0.00-1)", "0.85",      OPTION_FLOAT,      "end of axis saturation range for joystick where change is ignored (0.0 center, 1.0 end)" },
>>>>>>> upstream/master
	{ OPTION_NATURAL_KEYBOARD ";nat",                    "0",         OPTION_BOOLEAN,    "specifies whether to use a natural keyboard or not" },
	{ OPTION_JOYSTICK_CONTRADICTORY ";joy_contradictory","0",         OPTION_BOOLEAN,    "enable contradictory direction digital joystick input at the same time" },
	{ OPTION_COIN_IMPULSE,                               "0",         OPTION_INTEGER,    "set coin impulse time (n<0 disable impulse, n==0 obey driver, 0<n set time n)" },

	// input autoenable options
<<<<<<< HEAD
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE INPUT AUTOMATIC ENABLE OPTIONS" },
=======
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE INPUT AUTOMATIC ENABLE OPTIONS" },
>>>>>>> upstream/master
	{ OPTION_PADDLE_DEVICE ";paddle",                    "keyboard",  OPTION_STRING,     "enable (none|keyboard|mouse|lightgun|joystick) if a paddle control is present" },
	{ OPTION_ADSTICK_DEVICE ";adstick",                  "keyboard",  OPTION_STRING,     "enable (none|keyboard|mouse|lightgun|joystick) if an analog joystick control is present" },
	{ OPTION_PEDAL_DEVICE ";pedal",                      "keyboard",  OPTION_STRING,     "enable (none|keyboard|mouse|lightgun|joystick) if a pedal control is present" },
	{ OPTION_DIAL_DEVICE ";dial",                        "keyboard",  OPTION_STRING,     "enable (none|keyboard|mouse|lightgun|joystick) if a dial control is present" },
	{ OPTION_TRACKBALL_DEVICE ";trackball",              "keyboard",  OPTION_STRING,     "enable (none|keyboard|mouse|lightgun|joystick) if a trackball control is present" },
	{ OPTION_LIGHTGUN_DEVICE,                            "keyboard",  OPTION_STRING,     "enable (none|keyboard|mouse|lightgun|joystick) if a lightgun control is present" },
	{ OPTION_POSITIONAL_DEVICE,                          "keyboard",  OPTION_STRING,     "enable (none|keyboard|mouse|lightgun|joystick) if a positional control is present" },
	{ OPTION_MOUSE_DEVICE,                               "mouse",     OPTION_STRING,     "enable (none|keyboard|mouse|lightgun|joystick) if a mouse control is present" },

	// debugging options
<<<<<<< HEAD
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE DEBUGGING OPTIONS" },
=======
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE DEBUGGING OPTIONS" },
>>>>>>> upstream/master
	{ OPTION_VERBOSE ";v",                               "0",         OPTION_BOOLEAN,    "display additional diagnostic information" },
	{ OPTION_LOG,                                        "0",         OPTION_BOOLEAN,    "generate an error.log file" },
	{ OPTION_OSLOG,                                      "0",         OPTION_BOOLEAN,    "output error.log data to the system debugger" },
	{ OPTION_DEBUG ";d",                                 "0",         OPTION_BOOLEAN,    "enable/disable debugger" },
	{ OPTION_UPDATEINPAUSE,                              "0",         OPTION_BOOLEAN,    "keep calling video updates while in pause" },
<<<<<<< HEAD
	{ OPTION_DEBUGSCRIPT,                                NULL,        OPTION_STRING,     "script for debugger" },

	// comm options
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE COMM OPTIONS" },
=======
	{ OPTION_DEBUGSCRIPT,                                nullptr,     OPTION_STRING,     "script for debugger" },

	// comm options
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE COMM OPTIONS" },
>>>>>>> upstream/master
	{ OPTION_COMM_LOCAL_HOST,                            "0.0.0.0",   OPTION_STRING,     "local address to bind to" },
	{ OPTION_COMM_LOCAL_PORT,                            "15112",     OPTION_STRING,     "local port to bind to" },
	{ OPTION_COMM_REMOTE_HOST,                           "127.0.0.1", OPTION_STRING,     "remote address to connect to" },
	{ OPTION_COMM_REMOTE_PORT,                           "15112",     OPTION_STRING,     "remote port to connect to" },

	// misc options
<<<<<<< HEAD
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE MISC OPTIONS" },
=======
	{ nullptr,                                           nullptr,     OPTION_HEADER,     "CORE MISC OPTIONS" },
>>>>>>> upstream/master
	{ OPTION_DRC,                                        "1",         OPTION_BOOLEAN,    "enable DRC cpu core if available" },
	{ OPTION_DRC_USE_C,                                  "0",         OPTION_BOOLEAN,    "force DRC use C backend" },
	{ OPTION_DRC_LOG_UML,                                "0",         OPTION_BOOLEAN,    "write DRC UML disassembly log" },
	{ OPTION_DRC_LOG_NATIVE,                             "0",         OPTION_BOOLEAN,    "write DRC native disassembly log" },
<<<<<<< HEAD
	{ OPTION_BIOS,                                       NULL,        OPTION_STRING,     "select the system BIOS to use" },
	{ OPTION_CHEAT ";c",                                 "0",         OPTION_BOOLEAN,    "enable cheat subsystem" },
	{ OPTION_SKIP_GAMEINFO,                              "0",         OPTION_BOOLEAN,    "skip displaying the information screen at startup" },
	{ OPTION_UI_FONT,                                    "default",   OPTION_STRING,     "specify a font to use" },
	{ OPTION_RAMSIZE ";ram",                             NULL,        OPTION_STRING,     "size of RAM (if supported by driver)" },
	{ OPTION_CONFIRM_QUIT,                               "1",         OPTION_BOOLEAN,    "display confirm quit screen on exit" },
	{ OPTION_UI_MOUSE,                                   "0",         OPTION_BOOLEAN,    "display ui mouse cursor" },
	{ OPTION_AUTOBOOT_COMMAND ";ab",                     NULL,        OPTION_STRING,     "command to execute after machine boot" },
	{ OPTION_AUTOBOOT_DELAY,                             "2",         OPTION_INTEGER,    "timer delay in sec to trigger command execution on autoboot" },
	{ OPTION_AUTOBOOT_SCRIPT ";script",                  NULL,        OPTION_STRING,     "lua script to execute after machine boot" },
#ifdef PLAYBACK_END_PAUSE
	{ OPTION_PLAYBACK_END_PAUSE,                         "0",         OPTION_BOOLEAN,    "automatic pause when playback ended" },
#endif /* PLAYBACK_END_PAUSE */
#ifdef TRANS_UI
	{ OPTION_UI_TRANSPARENCY,                            "215",       OPTION_INTEGER,    "transparency in-game UI [0-255]" },
#endif /* TRANS_UI */
#ifdef USE_IPS
	{ OPTION_IPS,                                        NULL,        OPTION_STRING,     "ips datafile name"},
#endif /* USE_IPS */

#ifdef UI_COLOR_DISPLAY
	// palette options
	{ NULL,                                              NULL,        OPTION_HEADER,     "CORE PALETTE OPTIONS" },
	{ OPTION_SYSTEM_BACKGROUND,                         "16,16,48",   OPTION_STRING,     "main background color" },
	{ OPTION_CURSOR_SELECTED_TEXT,                      "255,255,255",OPTION_STRING,     "cursor text color (selected)" },
	{ OPTION_CURSOR_SELECTED_BG,                        "60,120,240", OPTION_STRING,     "cursor background color (selected)" },
	{ OPTION_CURSOR_HOVER_TEXT,                         "120,180,240",OPTION_STRING,     "cursor text color (floating)" },
	{ OPTION_CURSOR_HOVER_BG,                           "32,32,0",    OPTION_STRING,     "cursor background color (floating)" },
	{ OPTION_BUTTON_RED,                                "255,64,64",  OPTION_STRING,     "button color (red)" },
	{ OPTION_BUTTON_YELLOW,                             "255,238,0",  OPTION_STRING,     "button color (yellow)" },
	{ OPTION_BUTTON_GREEN,                              "0,255,64",   OPTION_STRING,     "button color (green)" },
	{ OPTION_BUTTON_BLUE,                               "0,170,255",  OPTION_STRING,     "button color (blue)" },
	{ OPTION_BUTTON_PURPLE,                             "170,0,255",  OPTION_STRING,     "button color (purple)" },
	{ OPTION_BUTTON_PINK,                               "255,0,170",  OPTION_STRING,     "button color (pink)" },
	{ OPTION_BUTTON_AQUA,                               "0,255,204",  OPTION_STRING,     "button color (aqua)" },
	{ OPTION_BUTTON_SILVER,                             "255,0,255",  OPTION_STRING,     "button color (silver)" },
	{ OPTION_BUTTON_NAVY,                               "255,160,0",  OPTION_STRING,     "button color (navy)" },
	{ OPTION_BUTTON_LIME,                               "190,190,190",OPTION_STRING,     "button color (lime)" },
#endif /* UI_COLOR_DISPLAY */

	// language options
	{ NULL,                                             NULL,         OPTION_HEADER,     "CORE LANGUAGE OPTIONS" },
	{ OPTION_LANGUAGE ";lang",                          "auto",       OPTION_STRING,     "select translation language" },
	{ OPTION_USE_LANG_LIST,                             "1",          OPTION_BOOLEAN,    "enable/disable local language game list" },

	{ NULL }
=======
	{ OPTION_BIOS,                                       nullptr,     OPTION_STRING,     "select the system BIOS to use" },
	{ OPTION_CHEAT ";c",                                 "0",         OPTION_BOOLEAN,    "enable cheat subsystem" },
	{ OPTION_SKIP_GAMEINFO,                              "0",         OPTION_BOOLEAN,    "skip displaying the information screen at startup" },
	{ OPTION_UI_FONT,                                    "default",   OPTION_STRING,     "specify a font to use" },
	{ OPTION_UI,                                         "cabinet",   OPTION_STRING,     "type of UI (simple|cabinet)" },
	{ OPTION_RAMSIZE ";ram",                             nullptr,     OPTION_STRING,     "size of RAM (if supported by driver)" },
	{ OPTION_CONFIRM_QUIT,                               "0",         OPTION_BOOLEAN,    "display confirm quit screen on exit" },
	{ OPTION_UI_MOUSE,                                   "1",         OPTION_BOOLEAN,    "display ui mouse cursor" },
	{ OPTION_AUTOBOOT_COMMAND ";ab",                     nullptr,     OPTION_STRING,     "command to execute after machine boot" },
	{ OPTION_AUTOBOOT_DELAY,                             "0",         OPTION_INTEGER,    "timer delay in sec to trigger command execution on autoboot" },
	{ OPTION_AUTOBOOT_SCRIPT ";script",                  nullptr,     OPTION_STRING,     "lua script to execute after machine boot" },
	{ OPTION_CONSOLE,                                    "0",         OPTION_BOOLEAN,    "enable emulator LUA console" },
	{ OPTION_PLUGINS,                                    "1",         OPTION_BOOLEAN,    "enable LUA plugin support" },
	{ OPTION_PLUGIN,                                     nullptr,     OPTION_STRING,     "list of plugins to enable" },
	{ OPTION_NO_PLUGIN,                                  nullptr,     OPTION_STRING,     "list of plugins to disable" },
	{ OPTION_LANGUAGE ";lang",                           "English",   OPTION_STRING,     "display language" },

	{ nullptr,                                           nullptr,     OPTION_HEADER,     "HTTP SERVER OPTIONS" },
	{ OPTION_HTTP,                                       "0",         OPTION_BOOLEAN,    "HTTP server enable" },
	{ OPTION_HTTP_PORT,                                  "8080",      OPTION_INTEGER,    "HTTP server port" },
	{ OPTION_HTTP_ROOT,                                  "web",       OPTION_STRING,     "HTTP server document root" },

	{ nullptr }
>>>>>>> upstream/master
};



//**************************************************************************
<<<<<<< HEAD
=======
//  CUSTOM OPTION ENTRIES AND SUPPORT CLASSES
//**************************************************************************

namespace
{
	// custom option entry for the system name
	class system_name_option_entry : public core_options::entry
	{
	public:
		system_name_option_entry(emu_options &host)
			: entry(OPTION_SYSTEMNAME)
			, m_host(host)
		{
		}

		virtual const char *value() const override
		{
			// This is returning an empty string instead of nullptr to signify that
			// specifying the value is a meaningful operation.  The option types that
			// return nullptr are option types that cannot have a value (e.g. - commands)
			//
			// See comments in core_options::entry::value() and core_options::simple_entry::value()
			return m_host.system() ? m_host.system()->name : "";
		}

	protected:
		virtual void internal_set_value(std::string &&newvalue) override
		{
			m_host.set_system_name(std::move(newvalue));
		}

	private:
		emu_options &m_host;
	};

	// custom option entry for the software name
	class software_name_option_entry : public core_options::entry
	{
	public:
		software_name_option_entry(emu_options &host)
			: entry(OPTION_SOFTWARENAME)
			, m_host(host)
		{
		}

	protected:
		virtual void internal_set_value(std::string &&newvalue) override
		{
			m_host.set_software(std::move(newvalue));
		}

	private:
		emu_options &m_host;
	};

	// custom option entry for slots
	class slot_option_entry : public core_options::entry
	{
	public:
		slot_option_entry(const char *name, slot_option &host)
			: entry(name)
			, m_host(host)
		{
		}

		virtual const char *value() const override
		{
			const char *result = nullptr;
			if (m_host.specified())
			{
				// m_temp is a temporary variable used to keep the specified value
				// so the result can be returned as 'const char *'.  Obviously, this
				// value will be trampled upon if value() is called again.  This doesn't
				// happen in practice
				//
				// In reality, I want to really return std::optional<std::string> here
				m_temp = m_host.specified_value();
				result = m_temp.c_str();
			}
			return result;
		}

	protected:
		virtual void internal_set_value(std::string &&newvalue) override
		{
			m_host.specify(std::move(newvalue), false);
		}

	private:
		slot_option &       m_host;
		mutable std::string m_temp;
	};

	// custom option entry for images
	class image_option_entry : public core_options::entry
	{
	public:
		image_option_entry(std::vector<std::string> &&names, image_option &host)
			: entry(std::move(names))
			, m_host(host)
		{
		}

		virtual const char *value() const override
		{
			return m_host.value().c_str();
		}

	protected:
		virtual void internal_set_value(std::string &&newvalue) override
		{
			m_host.specify(std::move(newvalue), false);
		}

	private:
		image_option &m_host;
	};

	// existing option tracker class; used by slot/image calculus to identify existing
	// options for later purging
	template<typename T>
	class existing_option_tracker
	{
	public:
		existing_option_tracker(const std::unordered_map<std::string, T> &map)
		{
			m_vec.reserve(map.size());
			for (const auto &entry : map)
				m_vec.push_back(&entry.first);
		}

		template<typename TStr>
		void remove(const TStr &str)
		{
			auto iter = std::find_if(
				m_vec.begin(),
				m_vec.end(),
				[&str](const auto &x) { return *x == str; });
			if (iter != m_vec.end())
				m_vec.erase(iter);
		}

		std::vector<const std::string *>::iterator begin() { return m_vec.begin(); }
		std::vector<const std::string *>::iterator end() { return m_vec.end(); }

	private:
		std::vector<const std::string *> m_vec;
	};


	//-------------------------------------------------
	//  get_full_option_names
	//-------------------------------------------------

	std::vector<std::string> get_full_option_names(const device_image_interface &image)
	{
		std::vector<std::string> result;

		result.push_back(image.instance_name());
		result.push_back(image.brief_instance_name());

		if (strcmp(image.device_typename(image.image_type()), image.instance_name().c_str()) == 0)
		{
			result.push_back(image.instance_name() + "1");
			result.push_back(image.brief_instance_name() + "1");
		}
		return result;
	}


	//-------------------------------------------------
	//  conditionally_peg_priority
	//-------------------------------------------------

	void conditionally_peg_priority(core_options::entry::weak_ptr &entry, bool peg_priority)
	{
		// if the [image|slot] entry was specified outside of the context of the options sytem, we need
		// to peg the priority of any associated core_options::entry at the maximum priority
		if (peg_priority && !entry.expired())
			entry.lock()->set_priority(OPTION_PRIORITY_MAXIMUM);
	}
}


//**************************************************************************
>>>>>>> upstream/master
//  EMU OPTIONS
//**************************************************************************

//-------------------------------------------------
//  emu_options - constructor
//-------------------------------------------------

<<<<<<< HEAD
emu_options::emu_options()
: core_options()
, m_coin_impulse(0)
, m_joystick_contradictory(false)
, m_sleep(true)
, m_refresh_speed(false)
{
	add_entries(emu_options::s_option_entries);
=======
emu_options::emu_options(option_support support)
	: m_support(support)
	, m_system(nullptr)
	, m_coin_impulse(0)
	, m_joystick_contradictory(false)
	, m_sleep(true)
	, m_refresh_speed(false)
	, m_ui(UI_CABINET)
{
	// add entries
	if (support == option_support::FULL || support == option_support::GENERAL_AND_SYSTEM)
		add_entry(std::make_shared<system_name_option_entry>(*this));
	if (support == option_support::FULL)
		add_entry(std::make_shared<software_name_option_entry>(*this));
	add_entries(emu_options::s_option_entries);

	// adding handlers to keep copies of frequently requested options in member variables
	set_value_changed_handler(OPTION_COIN_IMPULSE,              [this](const char *value) { m_coin_impulse = int_value(OPTION_COIN_IMPULSE); });
	set_value_changed_handler(OPTION_JOYSTICK_CONTRADICTORY,    [this](const char *value) { m_joystick_contradictory = bool_value(OPTION_JOYSTICK_CONTRADICTORY); });
	set_value_changed_handler(OPTION_SLEEP,                     [this](const char *value) { m_sleep = bool_value(OPTION_SLEEP); });
	set_value_changed_handler(OPTION_REFRESHSPEED,              [this](const char *value) { m_refresh_speed = bool_value(OPTION_REFRESHSPEED); });
	set_value_changed_handler(OPTION_UI, [this](const std::string &value)
	{
		if (value == "simple")
			m_ui = UI_SIMPLE;
		else
			m_ui = UI_CABINET;
	});
}


//-------------------------------------------------
//  emu_options - destructor
//-------------------------------------------------

emu_options::~emu_options()
{
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  add_slot_options - add all of the slot
//  options for the configured system
//-------------------------------------------------

bool emu_options::add_slot_options(bool isfirstpass)
{
	// look up the system configured by name; if no match, do nothing
	const game_driver *cursystem = system();
	if (cursystem == NULL)
		return false;
	machine_config config(*cursystem, *this);

	// iterate through all slot devices
	bool first = true;

	// create the configuration
	int starting_count = options_count();
	slot_interface_iterator iter(config.root_device());
	for (const device_slot_interface *slot = iter.first(); slot != NULL; slot = iter.next())
	{
		// skip fixed slots
		if (slot->fixed())
			continue;

		// first device? add the header as to be pretty
		if (isfirstpass && first)
			add_entry(NULL, "SLOT DEVICES", OPTION_HEADER | OPTION_FLAG_DEVICE);
		first = false;

		// retrieve info about the device instance
		const char *name = slot->device().tag() + 1;
		if (!exists(name))
		{
			// add the option
			UINT32 flags = OPTION_STRING | OPTION_FLAG_DEVICE;
			const char *defvalue = slot->default_option();
			if (defvalue != NULL)
			{
				const device_slot_option *option = slot->option(defvalue);
				if (option != NULL && !option->selectable())
					flags |= OPTION_FLAG_INTERNAL;
			}
			add_entry(name, NULL, flags, defvalue, true);
		}
	}
	return (options_count() != starting_count);
=======
//  system_name
//-------------------------------------------------

const char *emu_options::system_name() const
{
	return m_system ? m_system->name : "";
}


//-------------------------------------------------
//  set_system_name - called to set the system
//  name; will adjust slot/image options as appropriate
//-------------------------------------------------

void emu_options::set_system_name(std::string &&new_system_name)
{
	const game_driver *new_system = nullptr;

	// we are making an attempt - record what we're attempting
	m_attempted_system_name = std::move(new_system_name);

	// was a system name specified?
	if (!m_attempted_system_name.empty())
	{
		// if so, first extract the base name (the reason for this is drag-and-drop on Windows; a side
		// effect is a command line like 'mame pacman.foo' will work correctly, but so be it)
		std::string new_system_base_name = core_filename_extract_base(m_attempted_system_name, true);

		// perform the lookup (and error if it cannot be found)
		int index = driver_list::find(new_system_base_name.c_str());
		if (index < 0)
			throw options_error_exception("Unknown system '%s'", m_attempted_system_name);
		new_system = &driver_list::driver(index);
	}

	// did we change anything?
	if (new_system != m_system)
	{
		// if so, specify the new system and update (if we're fully supporting slot/image options)
		m_system = new_system;
		m_software_name.clear();
		if (m_support == option_support::FULL)
			update_slot_and_image_options();
	}
}


//-------------------------------------------------
//  set_system_name - called to set the system
//  name; will adjust slot/image options as appropriate
//-------------------------------------------------

void emu_options::set_system_name(const std::string &new_system_name)
{
	set_system_name(std::string(new_system_name));
}


//-------------------------------------------------
//  update_slot_and_image_options
//-------------------------------------------------

void emu_options::update_slot_and_image_options()
{
	bool changed;
	do
	{
		changed = false;

		// first we add and remove slot options depending on what has been configured in the
		// device, bringing m_slot_options up to a state where it matches machine_config
		if (add_and_remove_slot_options())
			changed = true;

		// second, we perform an analgous operation with m_image_options
		if (add_and_remove_image_options())
			changed = true;

		// if we changed anything, we should reevaluate existing options
		if (changed)
			reevaluate_default_card_software();
	} while (changed);
}


//-------------------------------------------------
//  add_and_remove_slot_options - add any missing
//  and/or purge extraneous slot options
//-------------------------------------------------

bool emu_options::add_and_remove_slot_options()
{
	bool changed = false;

	// first, create a list of existing slot options; this is so we can purge
	// any stray slot options that are no longer pertinent when we're done
	existing_option_tracker<::slot_option> existing(m_slot_options);

	// it is perfectly legal for this to be called without a system; we
	// need to check for that condition!
	if (m_system)
	{
		// create the configuration
		machine_config config(*m_system, *this);

		for (const device_slot_interface &slot : slot_interface_iterator(config.root_device()))
		{
			// come up with the cannonical name of the slot
			const char *slot_option_name = slot.slot_name();

			// erase this option from existing (so we don't purge it later)
			existing.remove(slot_option_name);

			// do we need to add this option?
			if (!has_slot_option(slot_option_name))
			{
				// we do - add it to m_slot_options
				auto pair = std::make_pair(slot_option_name, ::slot_option(*this, slot.default_option()));
				::slot_option &new_option(m_slot_options.emplace(std::move(pair)).first->second);
				changed = true;

				// for non-fixed slots, this slot needs representation in the options collection
				if (!slot.fixed())
				{
					// first device? add the header as to be pretty
					const char *header = "SLOT DEVICES";
					if (!header_exists(header))
						add_header(header);

					// create a new entry in the options
					auto new_entry = new_option.setup_option_entry(slot_option_name);

					// and add it
					add_entry(std::move(new_entry), header);
				}
			}

		}
	}

	// at this point we need to purge stray slot options that may no longer be pertinent
	for (auto &opt_name : existing)
	{
		auto iter = m_slot_options.find(*opt_name);
		assert(iter != m_slot_options.end());

		// if this is represented in core_options, remove it
		if (iter->second.option_entry())
			remove_entry(*iter->second.option_entry());

		// remove this option
		m_slot_options.erase(iter);
		changed = true;
	}

	return changed;
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  update_slot_options - update slot values
//  depending of image mounted
//-------------------------------------------------

void emu_options::update_slot_options()
{
	// look up the system configured by name; if no match, do nothing
	const game_driver *cursystem = system();
	if (cursystem == NULL)
		return;
	machine_config config(*cursystem, *this);

	// iterate through all slot devices
	slot_interface_iterator iter(config.root_device());
	for (device_slot_interface *slot = iter.first(); slot != NULL; slot = iter.next())
	{
		// retrieve info about the device instance
		const char *name = slot->device().tag() + 1;
		if (exists(name) && slot->first_option() != NULL)
		{
			std::string defvalue;
			slot->get_default_card_software(defvalue);
			if (defvalue.length() > 0)
			{
				set_default_value(name, defvalue.c_str());
				const device_slot_option *option = slot->option(defvalue.c_str());
				set_flag(name, ~OPTION_FLAG_INTERNAL, (option != NULL && !option->selectable()) ? OPTION_FLAG_INTERNAL : 0);
			}
		}
	}
	while (add_slot_options(false)) { }
	add_device_options(false);
=======
//  add_and_remove_slot_options - add any missing
//  and/or purge extraneous slot options
//-------------------------------------------------

bool emu_options::add_and_remove_image_options()
{
	// The logic for image options is superficially similar to the logic for slot options, but
	// there is one larger piece of complexity.  The image instance names (returned by the
	// image_instance() call and surfaced in the UI) may change simply because we've added more
	// devices.  This is because the instance_name() for a singular cartridge device might be
	// "cartridge" starting out, but become "cartridge1" when another cartridge device is added.
	//
	// To get around this behavior, our internal data structures work in terms of what is
	// returned by cannonical_instance_name(), which will be something like "cartridge1" both
	// for a singular cartridge device and the first cartridge in a multi cartridge system.
	//
	// The need for this behavior was identified by Tafoid when the following command line
	// regressed:
	//
	//      mame snes bsxsore -cart2 bszelda
	//
	// Before we were accounting for this behavior, 'bsxsore' got stored in "cartridge" and
	// the association got lost when the second cartridge was added.

	bool changed = false;

	// first, create a list of existing image options; this is so we can purge
	// any stray slot options that are no longer pertinent when we're done; we
	// have to do this for both "flavors" of name
	existing_option_tracker<::image_option> existing(m_image_options_cannonical);

	// wipe the non-cannonical image options; we're going to rebuild it
	m_image_options.clear();

	// it is perfectly legal for this to be called without a system; we
	// need to check for that condition!
	if (m_system)
	{
		// create the configuration
		machine_config config(*m_system, *this);

		// iterate through all image devices
		for (device_image_interface &image : image_interface_iterator(config.root_device()))
		{
			const std::string &cannonical_name(image.cannonical_instance_name());

			// erase this option from existing (so we don't purge it later)
			existing.remove(cannonical_name);

			// do we need to add this option?
			auto iter = m_image_options_cannonical.find(cannonical_name);
			::image_option *this_option = iter != m_image_options_cannonical.end() ? &iter->second : nullptr;
			if (!this_option)
			{
				// we do - add it to both m_image_options_cannonical and m_image_options
				auto pair = std::make_pair(cannonical_name, ::image_option(*this, image.cannonical_instance_name()));
				this_option = &m_image_options_cannonical.emplace(std::move(pair)).first->second;
				changed = true;

				// if this image is user loadable, we have to surface it in the core_options
				if (image.user_loadable())
				{
					// first device? add the header as to be pretty
					const char *header = "IMAGE DEVICES";
					if (!header_exists(header))
						add_header(header);

					// name this options
					auto names = get_full_option_names(image);

					// create a new entry in the options
					auto new_entry = this_option->setup_option_entry(std::move(names));

					// and add it
					add_entry(std::move(new_entry), header);
				}
			}

			// whether we added it or we didn't, we have to add it to the m_image_option map
			m_image_options[image.instance_name()] = this_option;
		}
	}

	// at this point we need to purge stray image options that may no longer be pertinent
	for (auto &opt_name : existing)
	{
		auto iter = m_image_options_cannonical.find(*opt_name);
		assert(iter != m_image_options_cannonical.end());

		// if this is represented in core_options, remove it
		if (iter->second.option_entry())
			remove_entry(*iter->second.option_entry());

		// remove this option
		m_image_options_cannonical.erase(iter);
		changed = true;
	}

	return changed;
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  add_device_options - add all of the device
//  options for the configured system
//-------------------------------------------------

void emu_options::add_device_options(bool isfirstpass)
{
	// look up the system configured by name; if no match, do nothing
	const game_driver *cursystem = system();
	if (cursystem == NULL)
		return;
	machine_config config(*cursystem, *this);

	// iterate through all image devices
	bool first = true;
	image_interface_iterator iter(config.root_device());
	for (const device_image_interface *image = iter.first(); image != NULL; image = iter.next())
	{
		// first device? add the header as to be pretty
		if (first && isfirstpass)
			add_entry(NULL, "IMAGE DEVICES", OPTION_HEADER | OPTION_FLAG_DEVICE);
		first = false;

		// retrieve info about the device instance
		std::string option_name;
		strprintf(option_name, "%s;%s", image->instance_name(), image->brief_instance_name());
		if (strcmp(image->device_typename(image->image_type()), image->instance_name()) == 0)
			strcatprintf(option_name, ";%s1;%s1", image->instance_name(), image->brief_instance_name());

		// add the option
		if (!exists(image->instance_name()))
			add_entry(option_name.c_str(), NULL, OPTION_STRING | OPTION_FLAG_DEVICE, NULL, true);
	}
=======
//  reevaluate_default_card_software - based on recent
//  changes in what images are mounted, give drivers
//  a chance to specify new default slot options
//-------------------------------------------------

void emu_options::reevaluate_default_card_software()
{
	// if we don't have a system specified, this is
	// a meaningless operation
	if (!m_system)
		return;

	bool found;
	do
	{
		// set up the machine_config
		machine_config config(*m_system, *this);
		found = false;

		// iterate through all slot devices
		for (device_slot_interface &slot : slot_interface_iterator(config.root_device()))
		{
			// retrieve info about the device instance
			auto &slot_opt(slot_option(slot.slot_name()));

			// device_slot_interface::get_default_card_software() is essentially a hook
			// that lets devices provide a feedback loop to force a specified software
			// list entry to be loaded
			//
			// In the repeated cycle of adding slots and slot devices, this gives a chance
			// for devices to "plug in" default software list items.  Of course, the fact
			// that this is all shuffling options is brittle and roundabout, but such is
			// the nature of software lists.
			//
			// In reality, having some sort of hook into the pipeline of slot/device evaluation
			// makes sense, but the fact that it is joined at the hip to device_image_interface
			// and device_slot_interface is unfortunate
			std::string default_card_software = get_default_card_software(slot);
			if (slot_opt.default_card_software() != default_card_software)
			{
				slot_opt.set_default_card_software(std::move(default_card_software));

				// calling set_default_card_software() can cause a cascade of slot/image
				// evaluations; we need to bail out of this loop because the iterator
				// may be bad
				found = true;
				break;
			}
		}
	} while (found);
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  remove_device_options - remove device options
//-------------------------------------------------

void emu_options::remove_device_options()
{
	// iterate through options and remove interesting ones
	entry *nextentry;
	for (entry *curentry = first(); curentry != NULL; curentry = nextentry)
	{
		// pre-fetch the next entry in case we delete this one
		nextentry = curentry->next();

		// if this is a device option, nuke it
		if ((curentry->flags() & OPTION_FLAG_DEVICE) != 0)
			remove_entry(*curentry);
	}
=======
//  get_default_card_software
//-------------------------------------------------

std::string emu_options::get_default_card_software(device_slot_interface &slot)
{
	std::string image_path;
	std::function<bool(util::core_file &, std::string&)> get_hashfile_extrainfo;

	// figure out if an image option has been specified, and if so, get the image path out of the options
	device_image_interface *image = dynamic_cast<device_image_interface *>(&slot);
	if (image)
	{
		image_path = image_option(image->instance_name()).value();

		get_hashfile_extrainfo = [image, this](util::core_file &file, std::string &extrainfo)
		{
			util::hash_collection hashes = image->calculate_hash_on_file(file);

			return hashfile_extrainfo(
				hash_path(),
				image->device().mconfig().gamedrv(),
				hashes,
				extrainfo);
		};
	}

	// create the hook
	get_default_card_software_hook hook(image_path, std::move(get_hashfile_extrainfo));

	// and invoke the slot's implementation of get_default_card_software()
	return slot.get_default_card_software(hook);
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  parse_slot_devices - parse the command line
//  and update slot and image devices
//-------------------------------------------------

bool emu_options::parse_slot_devices(int argc, char *argv[], std::string &error_string, const char *name, const char *value)
{
	// an initial parse to capture the initial set of values
	bool result;

	core_options::parse_command_line(argc, argv, OPTION_PRIORITY_CMDLINE, error_string);

	// keep adding slot options until we stop seeing new stuff
	bool isfirstpass = true;
	while (add_slot_options(isfirstpass))
	{
		core_options::parse_command_line(argc, argv, OPTION_PRIORITY_CMDLINE, error_string);
		isfirstpass = false;
	}

	// add device options and reparse
	add_device_options(true);
	if (name != NULL && exists(name))
		set_value(name, value, OPTION_PRIORITY_CMDLINE, error_string);
	core_options::parse_command_line(argc, argv, OPTION_PRIORITY_CMDLINE, error_string);

	int num;
	do {
		num = options_count();
		update_slot_options();
		result = core_options::parse_command_line(argc, argv, OPTION_PRIORITY_CMDLINE, error_string);
	} while (num != options_count());

	update_cached_options();

	return result;
}


//-------------------------------------------------
//  parse_command_line - parse the command line
//  and update the devices
//-------------------------------------------------

bool emu_options::parse_command_line(int argc, char *argv[], std::string &error_string)
{
	// parse as normal
	core_options::parse_command_line(argc, argv, OPTION_PRIORITY_CMDLINE, error_string);
	bool result = parse_slot_devices(argc, argv, error_string, NULL, NULL);
	update_cached_options();
	return result;
=======
//  set_software - called to load "unqualified"
//  software out of a software list (e.g. - "mame nes 'zelda'")
//-------------------------------------------------

void emu_options::set_software(std::string &&new_software)
{
	// identify any options as a result of softlists
	software_options softlist_opts = evaluate_initial_softlist_options(new_software);

	while (!softlist_opts.slot.empty() || !softlist_opts.image.empty())
	{
		// track how many options we have
		size_t before_size = softlist_opts.slot.size() + softlist_opts.image.size();

		// keep a list of deferred options, in case anything is applied
		// out of order
		software_options deferred_opts;

		// distribute slot options
		for (auto &slot_opt : softlist_opts.slot)
		{
			auto iter = m_slot_options.find(slot_opt.first);
			if (iter != m_slot_options.end())
				iter->second.specify(std::move(slot_opt.second));
			else
				deferred_opts.slot[slot_opt.first] = std::move(slot_opt.second);
		}

		// distribute image options
		for (auto &image_opt : softlist_opts.image)
		{
			auto iter = m_image_options.find(image_opt.first);
			if (iter != m_image_options.end())
				iter->second->specify(std::move(image_opt.second));
			else
				deferred_opts.image[image_opt.first] = std::move(image_opt.second);
		}

		// keep any deferred options for the next round
		softlist_opts = std::move(deferred_opts);

		// do we have any pending options after failing to distribute any?
		size_t after_size = softlist_opts.slot.size() + softlist_opts.image.size();
		if ((after_size > 0) && after_size >= before_size)
			throw options_error_exception("Could not assign software option");
	}

	// we've succeeded; update the set name
	m_software_name = std::move(new_software);
}


//-------------------------------------------------
//  evaluate_initial_softlist_options
//-------------------------------------------------

emu_options::software_options emu_options::evaluate_initial_softlist_options(const std::string &software_identifier)
{
	software_options results;

	// load software specified at the command line (if any of course)
	if (!software_identifier.empty())
	{
		// we have software; first identify the proper game_driver
		if (!m_system)
			throw options_error_exception("Cannot specify software without specifying system");

		// and set up a configuration
		machine_config config(*m_system, *this);
		software_list_device_iterator iter(config.root_device());
		if (iter.count() == 0)
			throw emu_fatalerror(EMU_ERR_FATALERROR, "Error: unknown option: %s\n", software_identifier.c_str());

		// and finally set up the stack
		std::stack<std::string> software_identifier_stack;
		software_identifier_stack.push(software_identifier);

		// we need to keep evaluating softlist identifiers until the stack is empty
		while (!software_identifier_stack.empty())
		{
			// pop the identifier
			std::string current_software_identifier = std::move(software_identifier_stack.top());
			software_identifier_stack.pop();

			// and parse it
			std::string list_name, software_name;
			auto colon_pos = current_software_identifier.find_first_of(':');
			if (colon_pos != std::string::npos)
			{
				list_name = current_software_identifier.substr(0, colon_pos);
				software_name = current_software_identifier.substr(colon_pos + 1);
			}
			else
			{
				software_name = current_software_identifier;
			}

			// loop through all softlist devices, and try to find one capable of handling the requested software
			bool found = false;
			bool compatible = false;
			for (software_list_device &swlistdev : iter)
			{
				if (list_name.empty() || (list_name == swlistdev.list_name()))
				{
					const software_info *swinfo = swlistdev.find(software_name);
					if (swinfo != nullptr)
					{
						// loop through all parts
						for (const software_part &swpart : swinfo->parts())
						{
							// only load compatible software this way
							if (swlistdev.is_compatible(swpart) == SOFTWARE_IS_COMPATIBLE)
							{
								// we need to find a mountable image slot, but we need to ensure it is a slot
								// for which we have not already distributed a part to
								device_image_interface *image = software_list_device::find_mountable_image(
									config,
									swpart,
									[&results](const device_image_interface &candidate) { return results.image.count(candidate.instance_name()) == 0; });

								// did we find a slot to put this part into?
								if (image != nullptr)
								{
									// we've resolved this software
									results.image[image->instance_name()] = string_format("%s:%s:%s", swlistdev.list_name(), software_name, swpart.name());

									// does this software part have a requirement on another part?
									const char *requirement = swpart.feature("requirement");
									if (requirement)
										software_identifier_stack.push(requirement);
								}
								compatible = true;
							}
							found = true;
						}

						// identify other shared features specified as '<<slot name>>_default'
						//
						// example from SMS:
						//
						//  <software name = "alexbmx">
						//      ...
						//      <sharedfeat name = "ctrl1_default" value = "paddle" />
						//  </software>
						for (const feature_list_item &fi : swinfo->shared_info())
						{
							const std::string default_suffix = "_default";
							if (fi.name().size() > default_suffix.size()
								&& fi.name().compare(fi.name().size() - default_suffix.size(), default_suffix.size(), default_suffix) == 0)
							{
								std::string slot_name = fi.name().substr(0, fi.name().size() - default_suffix.size());
								results.slot[slot_name] = fi.value();
							}
						}
					}
				}
				if (compatible)
					break;
			}

			if (!compatible)
			{
				software_list_device::display_matches(config, nullptr, software_name);

				// The text of this options_error_exception() is then passed to osd_printf_error() in cli_frontend::execute().  Therefore, it needs
				// to be human readable text.  We want to snake through a message about software incompatibility while being silent if that is not
				// the case.
				//
				// Arguably, anything related to user-visible text should really be done within src/frontend.  The invocation of
				// software_list_device::display_matches() should really be done there as well
				if (!found)
					throw options_error_exception("");
				else
					throw options_error_exception("Software '%s' is incompatible with system '%s'\n", software_name, m_system->name);
			}
		}
	}
	return results;
}


//-------------------------------------------------
//  find_slot_option
//-------------------------------------------------

const slot_option *emu_options::find_slot_option(const std::string &device_name) const
{
	auto iter = m_slot_options.find(device_name);
	return iter != m_slot_options.end() ? &iter->second : nullptr;
}

slot_option *emu_options::find_slot_option(const std::string &device_name)
{
	auto iter = m_slot_options.find(device_name);
	return iter != m_slot_options.end() ? &iter->second : nullptr;
}



//-------------------------------------------------
//  slot_option
//-------------------------------------------------

const slot_option &emu_options::slot_option(const std::string &device_name) const
{
	const ::slot_option *opt = find_slot_option(device_name);
	assert(opt && "Attempt to access non-existent slot option");
	return *opt;
}

slot_option &emu_options::slot_option(const std::string &device_name)
{
	::slot_option *opt = find_slot_option(device_name);
	assert(opt && "Attempt to access non-existent slot option");
	return *opt;
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  parse_standard_inis - parse the standard set
//  of INI files
//-------------------------------------------------

void emu_options::parse_standard_inis(std::string &error_string)
{
	// start with an empty string
	error_string.clear();

	// parse the INI file defined by the platform (e.g., "mame.ini")
	std::string error;
	set_value(OPTION_INIPATH, ".", OPTION_PRIORITY_INI, error);
	assert(error.empty());
	// we do this twice so that the first file can change the INI path
	parse_one_ini(emulator_info::get_configname(), OPTION_PRIORITY_MAME_INI);
	parse_one_ini(emulator_info::get_configname(), OPTION_PRIORITY_MAME_INI, &error_string);

	setup_language(*this);

	// debug mode: parse "debug.ini" as well
	if (debug())
		parse_one_ini("debug", OPTION_PRIORITY_DEBUG_INI, &error_string);

	// if we have a valid system driver, parse system-specific INI files
	const game_driver *cursystem = system();
	if (cursystem == NULL)
		return;

	// parse "vertical.ini" or "horizont.ini"
	if (cursystem->flags & ORIENTATION_SWAP_XY)
		parse_one_ini("vertical", OPTION_PRIORITY_ORIENTATION_INI, &error_string);
	else
		parse_one_ini("horizont", OPTION_PRIORITY_ORIENTATION_INI, &error_string);

	if (cursystem->flags & MACHINE_TYPE_ARCADE)
		parse_one_ini("arcade", OPTION_PRIORITY_SYSTYPE_INI, &error_string);
	else if (cursystem->flags & MACHINE_TYPE_CONSOLE)
		parse_one_ini("console", OPTION_PRIORITY_SYSTYPE_INI, &error_string);
	else if (cursystem->flags & MACHINE_TYPE_COMPUTER)
		parse_one_ini("computer", OPTION_PRIORITY_SYSTYPE_INI, &error_string);
	else if (cursystem->flags & MACHINE_TYPE_OTHER)
		parse_one_ini("othersys", OPTION_PRIORITY_SYSTYPE_INI, &error_string);

	machine_config config(*cursystem, *this);
	screen_device_iterator iter(config.root_device());
	for (const screen_device *device = iter.first(); device != NULL; device = iter.next())
	{
		// parse "raster.ini" for raster games
		if (device->screen_type() == SCREEN_TYPE_RASTER)
		{
			parse_one_ini("raster", OPTION_PRIORITY_SCREEN_INI, &error_string);
			break;
		}
		// parse "vector.ini" for vector games
		if (device->screen_type() == SCREEN_TYPE_VECTOR)
		{
			parse_one_ini("vector", OPTION_PRIORITY_SCREEN_INI, &error_string);
			break;
		}
		// parse "lcd.ini" for lcd games
		if (device->screen_type() == SCREEN_TYPE_LCD)
		{
			parse_one_ini("lcd", OPTION_PRIORITY_SCREEN_INI, &error_string);
			break;
		}
	}

	// next parse "source/<sourcefile>.ini"; if that doesn't exist, try <sourcefile>.ini
	std::string sourcename;
	core_filename_extract_base(sourcename, cursystem->source_file, true).insert(0, "source" PATH_SEPARATOR);
	if (!parse_one_ini(sourcename.c_str(), OPTION_PRIORITY_SOURCE_INI, &error_string))
	{
		core_filename_extract_base(sourcename, cursystem->source_file, true);
		parse_one_ini(sourcename.c_str(), OPTION_PRIORITY_SOURCE_INI, &error_string);
	}

	// then parse the grandparent, parent, and system-specific INIs
	int parent = driver_list::clone(*cursystem);
	int gparent = (parent != -1) ? driver_list::clone(parent) : -1;
	if (gparent != -1)
		parse_one_ini(driver_list::driver(gparent).name, OPTION_PRIORITY_GPARENT_INI, &error_string);
	if (parent != -1)
		parse_one_ini(driver_list::driver(parent).name, OPTION_PRIORITY_PARENT_INI, &error_string);

#ifdef USE_IPS
	//mamep: hack, DO NOT INHERIT IPS CONFIGURATION
	set_value(OPTION_IPS, "", OPTION_PRIORITY_INI, error);
	assert(error.empty());
#endif /* USE_IPS */

	parse_one_ini(cursystem->name, OPTION_PRIORITY_DRIVER_INI, &error_string);

	// Re-evaluate slot options after loading ini files
	update_slot_options();

	update_cached_options();
=======
//  image_option
//-------------------------------------------------

const image_option &emu_options::image_option(const std::string &device_name) const
{
	auto iter = m_image_options.find(device_name);
	assert(iter != m_image_options.end() && "Attempt to access non-existent image option");
	return *iter->second;
}

image_option &emu_options::image_option(const std::string &device_name)
{
	auto iter = m_image_options.find(device_name);
	assert(iter != m_image_options.end() && "Attempt to access non-existent image option");
	return *iter->second;
}


//-------------------------------------------------
//  command_argument_processed
//-------------------------------------------------

void emu_options::command_argument_processed()
{
	// some command line arguments require that the system name be set, so we can get slot options
	if (command_arguments().size() == 1 && !core_iswildstr(command_arguments()[0].c_str()) &&
		(command() == "listdevices" || (command() == "listslots") || (command() == "listmedia")))
	{
		set_system_name(command_arguments()[0]);
	}
}


//**************************************************************************
//  SLOT OPTIONS
//**************************************************************************

//-------------------------------------------------
//  slot_option ctor
//-------------------------------------------------

slot_option::slot_option(emu_options &host, const char *default_value)
	: m_host(host)
	, m_specified(false)
	, m_default_value(default_value ? default_value : "")
{
}


//-------------------------------------------------
//  slot_option::value
//-------------------------------------------------

const std::string &slot_option::value() const
{
	// There are a number of ways that the value can be determined; there
	// is a specific order of precedence:
	//
	//  1.  Highest priority is whatever may have been specified by the user (whether it
	//      was specified at the command line, an INI file, or in the UI).  We keep track
	//      of whether these values were specified this way
	//
	//      Take note that slots have a notion of being "selectable".  Slots that are not
	//      marked as selectable cannot be specified with this technique
	//
	//  2.  Next highest is what is returned from get_default_card_software()
	//
	//  3.  Last in priority is what was specified as the slot default.  This comes from
	//      device setup
	if (m_specified)
		return m_specified_value;
	else if (!m_default_card_software.empty())
		return m_default_card_software;
	else
		return m_default_value;
}


//-------------------------------------------------
//  slot_option::specified_value
//-------------------------------------------------

std::string slot_option::specified_value() const
{
	std::string result;
	if (m_specified)
	{
		result = m_specified_bios.empty()
			? m_specified_value
			: util::string_format("%s,bios=%s", m_specified_value, m_specified_bios);
	}
	return result;
}


//-------------------------------------------------
//  slot_option::specify
//-------------------------------------------------

void slot_option::specify(std::string &&text, bool peg_priority)
{
	// record the old value; we may need to trigger an update
	const std::string old_value = value();

	// we need to do some elementary parsing here
	const char *bios_arg = ",bios=";
	const size_t pos = text.find(bios_arg);
	if (pos != std::string::npos)
	{
		m_specified = true;
		m_specified_value = text.substr(0, pos);
		m_specified_bios = text.substr(pos + strlen(bios_arg));
	}
	else
	{
		m_specified = true;
		m_specified_value = std::move(text);
		m_specified_bios = "";
	}

	conditionally_peg_priority(m_entry, peg_priority);

	// we may have changed
	possibly_changed(old_value);
}


//-------------------------------------------------
//  slot_option::specify
//-------------------------------------------------

void slot_option::specify(const std::string &text, bool peg_priority)
{
	specify(std::string(text), peg_priority);
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  system - return a pointer to the specified
//  system driver, or NULL if no match
//-------------------------------------------------

const game_driver *emu_options::system() const
{
	std::string tempstr;
	int index = driver_list::find(core_filename_extract_base(tempstr, system_name(), true).c_str());
	return (index != -1) ? &driver_list::driver(index) : NULL;
=======
//  slot_option::set_default_card_software
//-------------------------------------------------

void slot_option::set_default_card_software(std::string &&s)
{
	// record the old value; we may need to trigger an update
	const std::string old_value = value();

	// update the default card software
	m_default_card_software = std::move(s);

	// we may have changed
	possibly_changed(old_value);
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  set_system_name - set a new system name
//-------------------------------------------------

void emu_options::set_system_name(const char *name)
{
	// remember the original system name
	std::string old_system_name(system_name());

	// if the system name changed, fix up the device options
	if (old_system_name.compare(name)!=0)
	{
		// first set the new name
		std::string error;
		set_value(OPTION_SYSTEMNAME, name, OPTION_PRIORITY_CMDLINE, error);
		assert(error.empty());

		// remove any existing device options and then add them afresh
		remove_device_options();
		if (add_slot_options(true))
			while (add_slot_options(false)) { }

		// then add the options
		add_device_options(true);
		int num;
		do {
			num = options_count();
			update_slot_options();
		} while(num != options_count());
	}
}

//-------------------------------------------------
//  parse_one_ini - parse a single INI file
//-------------------------------------------------

bool emu_options::parse_one_ini(const char *basename, int priority, std::string *error_string)
{
	// don't parse if it has been disabled
	if (!read_config())
		return false;

	// open the file; if we fail, that's ok
	emu_file file(ini_path(), OPEN_FLAG_READ);
	file_error filerr = file.open(basename, ".ini");
	if (filerr != FILERR_NONE)
		return false;

	// parse the file
	osd_printf_verbose("Parsing %s.ini\n", basename);
	std::string error;
	bool result = parse_ini_file(file, priority, OPTION_PRIORITY_DRIVER_INI, error);

	// append errors if requested
	if (!error.empty() && error_string != NULL)
		strcatprintf(*error_string, "While parsing %s:\n%s\n", file.fullpath(), error.c_str());

	return result;
}


const char *emu_options::main_value(std::string &buffer, const char *name) const
{
	buffer = value(name);
	int pos = buffer.find_first_of(',');
	if (pos != -1)
		buffer = buffer.substr(0, pos);
	return buffer.c_str();
}

const char *emu_options::sub_value(std::string &buffer, const char *name, const char *subname) const
{
	std::string tmp = std::string(",").append(subname).append("=");
	buffer = value(name);
	int pos = buffer.find(tmp);
	if (pos != -1)
	{
		int endpos = buffer.find_first_of(',', pos + 1);
		if (endpos == -1)
			endpos = buffer.length();
		buffer = buffer.substr(pos + tmp.length(), endpos - pos - tmp.length());
	}
	else
		buffer.clear();
	return buffer.c_str();
=======
//  slot_option::possibly_changed
//-------------------------------------------------

void slot_option::possibly_changed(const std::string &old_value)
{
	if (value() != old_value)
		m_host.update_slot_and_image_options();
}


//-------------------------------------------------
//  slot_option::set_bios
//-------------------------------------------------

void slot_option::set_bios(std::string &&text)
{
	if (!m_specified)
	{
		m_specified = true;
		m_specified_value = value();
	}
	m_specified_bios = std::move(text);
}


//-------------------------------------------------
//  slot_option::setup_option_entry
//-------------------------------------------------

core_options::entry::shared_ptr slot_option::setup_option_entry(const char *name)
{
	// this should only be called once
	assert(m_entry.expired());

	// create the entry and return it
	core_options::entry::shared_ptr entry = std::make_shared<slot_option_entry>(name, *this);
	m_entry = entry;
	return entry;
}


//**************************************************************************
//  IMAGE OPTIONS
//**************************************************************************

//-------------------------------------------------
//  image_option ctor
//-------------------------------------------------

image_option::image_option(emu_options &host, const std::string &cannonical_instance_name)
	: m_host(host)
	, m_canonical_instance_name(cannonical_instance_name)
{
}


//-------------------------------------------------
//  image_option::specify
//-------------------------------------------------

void image_option::specify(const std::string &value, bool peg_priority)
{
	if (value != m_value)
	{
		m_value = value;
		m_host.reevaluate_default_card_software();
	}
	conditionally_peg_priority(m_entry, peg_priority);
}

void image_option::specify(std::string &&value, bool peg_priority)
{
	if (value != m_value)
	{
		m_value = std::move(value);
		m_host.reevaluate_default_card_software();
	}
	conditionally_peg_priority(m_entry, peg_priority);
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  update_cached_options - to prevent tagmap
//    lookups keep copies of frequently requested
//    options in member variables.
//-------------------------------------------------

void emu_options::update_cached_options()
{
	m_coin_impulse = int_value(OPTION_COIN_IMPULSE);
	m_joystick_contradictory = bool_value(OPTION_JOYSTICK_CONTRADICTORY);
	m_sleep = bool_value(OPTION_SLEEP);
	m_refresh_speed = bool_value(OPTION_REFRESHSPEED);
=======
//  image_option::setup_option_entry
//-------------------------------------------------

core_options::entry::shared_ptr image_option::setup_option_entry(std::vector<std::string> &&names)
{
	// this should only be called once
	assert(m_entry.expired());

	// create the entry and return it
	core_options::entry::shared_ptr entry = std::make_shared<image_option_entry>(std::move(names), *this);
	m_entry = entry;
	return entry;
>>>>>>> upstream/master
}
