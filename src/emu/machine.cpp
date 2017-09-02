// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    machine.c

    Controls execution of the core MAME system.

****************************************************************************

    Since there has been confusion in the past over the order of
    initialization and other such things, here it is, all spelled out
    as of January, 2008:

    main()
        - does platform-specific init
        - calls mame_execute() [mame.c]

        mame_execute() [mame.c]
            - calls mame_validitychecks() [validity.c] to perform validity checks on all compiled drivers
            - begins resource tracking (level 1)
            - calls create_machine [mame.c] to initialize the running_machine structure
            - calls init_machine() [mame.c]

            init_machine() [mame.c]
                - calls fileio_init() [fileio.c] to initialize file I/O info
                - calls config_init() [config.c] to initialize configuration system
                - calls input_init() [input.c] to initialize the input system
                - calls output_init() [output.c] to initialize the output system
                - calls state_init() [state.c] to initialize save state system
                - calls state_save_allow_registration() [state.c] to allow registrations
                - calls palette_init() [palette.c] to initialize palette system
                - calls render_init() [render.c] to initialize the rendering system
                - calls ui_init() [ui.c] to initialize the user interface
                - calls generic_machine_init() [machine/generic.c] to initialize generic machine structures
                - calls timer_init() [timer.c] to reset the timer system
                - calls osd_init() [osdepend.h] to do platform-specific initialization
                - calls input_port_init() [inptport.c] to set up the input ports
                - calls rom_init() [romload.c] to load the game's ROMs
                - calls memory_init() [memory.c] to process the game's memory maps
                - calls the driver's DRIVER_INIT callback
                - calls device_list_start() [devintrf.c] to start any devices
                - calls video_init() [video.c] to start the video system
                - calls tilemap_init() [tilemap.c] to start the tilemap system
                - calls crosshair_init() [crsshair.c] to configure the crosshairs
                - calls sound_init() [sound.c] to start the audio system
                - calls debugger_init() [debugger.c] to set up the debugger
                - calls the driver's MACHINE_START, SOUND_START, and VIDEO_START callbacks
                - calls cheat_init() [cheat.c] to initialize the cheat system
                - calls image_init() [image.c] to initialize the image system

            - calls config_load_settings() [config.c] to load the configuration file
            - calls nvram_load [machine/generic.c] to load NVRAM
            - calls ui_display_startup_screens() [ui.c] to display the startup screens
            - begins resource tracking (level 2)
            - calls soft_reset() [mame.c] to reset all systems

                -------------------( at this point, we're up and running )----------------------

            - calls scheduler->timeslice() [schedule.c] over and over until we exit
            - ends resource tracking (level 2), freeing all auto_mallocs and timers
            - calls the nvram_save() [machine/generic.c] to save NVRAM
            - calls config_save_settings() [config.c] to save the game's configuration
            - calls all registered exit routines [mame.c]
            - ends resource tracking (level 1), freeing all auto_mallocs and timers

        - exits the program

***************************************************************************/

#include "emu.h"
#include "emuopts.h"
#include "osdepend.h"
#include "config.h"
#include "debugger.h"
#include "render.h"
<<<<<<< HEAD
#include "cheat.h"
=======
>>>>>>> upstream/master
#include "uiinput.h"
#include "crsshair.h"
#include "unzip.h"
#include "debug/debugvw.h"
<<<<<<< HEAD
#include "image.h"
#include "luaengine.h"
#include "network.h"
#ifdef USE_HISCORE
#include "hiscore.h"
#endif /* USE_HISCORE */

#include <time.h>

#if defined(EMSCRIPTEN)
#include <emscripten.h>

void js_set_main_loop(running_machine * machine);
=======
#include "debug/debugcpu.h"
#include "dirtc.h"
#include "image.h"
#include "network.h"
#include "ui/uimain.h"
#include <time.h>
#include "rapidjson/include/rapidjson/writer.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"

#if defined(EMSCRIPTEN)
#include <emscripten.h>
>>>>>>> upstream/master
#endif



//**************************************************************************
<<<<<<< HEAD
//  GLOBAL VARIABLES
//**************************************************************************

// a giant string buffer for temporary strings
static char giant_string_buffer[65536] = { 0 };



//**************************************************************************
=======
>>>>>>> upstream/master
//  RUNNING MACHINE
//**************************************************************************

osd_interface &running_machine::osd() const
{
	return m_manager.osd();
}

//-------------------------------------------------
//  running_machine - constructor
//-------------------------------------------------

running_machine::running_machine(const machine_config &_config, machine_manager &manager)
<<<<<<< HEAD
	: firstcpu(NULL),
		primary_screen(NULL),
		debug_flags(0),
		romload_data(NULL),
		ui_input_data(NULL),
		debugcpu_data(NULL),
		generic_machine_data(NULL),
		m_config(_config),
		m_system(_config.gamedrv()),
		m_manager(manager),
		m_current_phase(MACHINE_PHASE_PREINIT),
		m_paused(false),
		m_hard_reset_pending(false),
		m_exit_pending(false),
		m_soft_reset_timer(NULL),
=======
	: firstcpu(nullptr),
		primary_screen(nullptr),
		m_side_effect_disabled(0),
		debug_flags(0),
		m_config(_config),
		m_system(_config.gamedrv()),
		m_manager(manager),
		m_current_phase(machine_phase::PREINIT),
		m_paused(false),
		m_hard_reset_pending(false),
		m_exit_pending(false),
		m_soft_reset_timer(nullptr),
>>>>>>> upstream/master
		m_rand_seed(0x9d14abd7),
		m_ui_active(_config.options().ui_active()),
		m_basename(_config.gamedrv().name),
		m_sample_rate(_config.options().sample_rate()),
<<<<<<< HEAD
		m_saveload_schedule(SLS_NONE),
		m_saveload_schedule_time(attotime::zero),
		m_saveload_searchpath(NULL),
=======
		m_saveload_schedule(saveload_schedule::NONE),
		m_saveload_schedule_time(attotime::zero),
		m_saveload_searchpath(nullptr),
>>>>>>> upstream/master

		m_save(*this),
		m_memory(*this),
		m_ioport(*this),
		m_parameters(*this),
<<<<<<< HEAD
		m_scheduler(*this)
{
	memset(&m_base_time, 0, sizeof(m_base_time));

	// set the machine on all devices
	device_iterator iter(root_device());
	for (device_t *device = iter.first(); device != NULL; device = iter.next())
		device->set_machine(*this);

	// find devices
	for (device_t *device = iter.first(); device != NULL; device = iter.next())
		if (dynamic_cast<cpu_device *>(device) != NULL)
		{
			firstcpu = downcast<cpu_device *>(device);
			break;
		}
#ifdef USE_HISCORE
	int cpunum = 0;
	execute_interface_iterator execiter(root_device());
	for (device_execute_interface *device = execiter.first(); device != NULL; device = execiter.next())
		if (cpunum < 8)
			cpu[cpunum++] = &device->device();
#endif /* USE_HISCORE */

	screen_device_iterator screeniter(root_device());
	primary_screen = screeniter.first();
=======
		m_scheduler(*this),
		m_dummy_space(_config, "dummy_space", &root_device(), 0)
{
	memset(&m_base_time, 0, sizeof(m_base_time));

	m_dummy_space.set_machine(*this);
	m_dummy_space.config_complete();

	// set the machine on all devices
	device_iterator iter(root_device());
	for (device_t &device : iter)
		device.set_machine(*this);

	// find devices
	for (device_t &device : iter)
		if (dynamic_cast<cpu_device *>(&device) != nullptr)
		{
			firstcpu = downcast<cpu_device *>(&device);
			break;
		}
	primary_screen = screen_device_iterator(root_device()).first();
>>>>>>> upstream/master

	// fetch core options
	if (options().debug())
		debug_flags = (DEBUG_FLAG_ENABLED | DEBUG_FLAG_CALL_HOOK) | (DEBUG_FLAG_OSD_ENABLED);
}


//-------------------------------------------------
//  ~running_machine - destructor
//-------------------------------------------------

running_machine::~running_machine()
{
}


//-------------------------------------------------
//  describe_context - return a string describing
//  which device is currently executing and its
//  PC
//-------------------------------------------------

<<<<<<< HEAD
const char *running_machine::describe_context()
{
	device_execute_interface *executing = m_scheduler.currently_executing();
	if (executing != NULL)
	{
		cpu_device *cpu = dynamic_cast<cpu_device *>(&executing->device());
		if (cpu != NULL)
			strprintf(m_context, "'%s' (%s)", cpu->tag(), core_i64_format(cpu->pc(), cpu->space(AS_PROGRAM).logaddrchars(), cpu->is_octal()));
	}
	else
		m_context.assign("(no context)");

	return m_context.c_str();
}

TIMER_CALLBACK_MEMBER(running_machine::autoboot_callback)
{
	if (strlen(options().autoboot_script())!=0) {
		manager().lua()->load_script(options().autoboot_script());
	}
	else if (strlen(options().autoboot_command())!=0) {
		std::string cmd = std::string(options().autoboot_command());
		strreplace(cmd, "'", "\\'");
		std::string val = std::string("emu.keypost('").append(cmd).append("')");
		manager().lua()->load_string(val.c_str());
	}
}
=======
std::string running_machine::describe_context() const
{
	device_execute_interface *executing = m_scheduler.currently_executing();
	if (executing != nullptr)
	{
		cpu_device *cpu = dynamic_cast<cpu_device *>(&executing->device());
		if (cpu != nullptr)
		{
			address_space &prg = cpu->space(AS_PROGRAM);
			return string_format(prg.is_octal() ? "'%s' (%0*o)" :  "'%s' (%0*X)", cpu->tag(), prg.logaddrchars(), cpu->pc());
		}
	}

	return std::string("(no context)");
}

>>>>>>> upstream/master

//-------------------------------------------------
//  start - initialize the emulated machine
//-------------------------------------------------

void running_machine::start()
{
	// initialize basic can't-fail systems here
<<<<<<< HEAD
	config_init(*this);
	m_input.reset(global_alloc(input_manager(*this)));
	output_init(*this);
	m_render.reset(global_alloc(render_manager(*this)));
	generic_machine_init(*this);
=======
	m_configuration = std::make_unique<configuration_manager>(*this);
	m_input = std::make_unique<input_manager>(*this);
	m_output = std::make_unique<output_manager>(*this);
	m_render = std::make_unique<render_manager>(*this);
	m_bookkeeping = std::make_unique<bookkeeping_manager>(*this);
>>>>>>> upstream/master

	// allocate a soft_reset timer
	m_soft_reset_timer = m_scheduler.timer_alloc(timer_expired_delegate(FUNC(running_machine::soft_reset), this));

<<<<<<< HEAD
=======
	// initialize UI input
	m_ui_input = make_unique_clear<ui_input_manager>(*this);

>>>>>>> upstream/master
	// init the osd layer
	m_manager.osd().init(*this);

	// create the video manager
<<<<<<< HEAD
	m_video.reset(global_alloc(video_manager(*this)));
	m_ui.reset(global_alloc(ui_manager(*this)));
=======
	m_video = std::make_unique<video_manager>(*this);
	m_ui = manager().create_ui(*this);
>>>>>>> upstream/master

	// initialize the base time (needed for doing record/playback)
	::time(&m_base_time);

	// initialize the input system and input ports for the game
	// this must be done before memory_init in order to allow specifying
	// callbacks based on input port tags
	time_t newbase = m_ioport.initialize();
	if (newbase != 0)
		m_base_time = newbase;

<<<<<<< HEAD
	// intialize UI input
	ui_input_init(*this);

	// initialize the streams engine before the sound devices start
	m_sound.reset(global_alloc(sound_manager(*this)));

	// first load ROMs, then populate memory, and finally initialize CPUs
	// these operations must proceed in this order
	rom_init(*this);
	m_memory.initialize();

	// initialize the watchdog
	m_watchdog_counter = 0;
	m_watchdog_timer = m_scheduler.timer_alloc(timer_expired_delegate(FUNC(running_machine::watchdog_fired), this));
	if (config().m_watchdog_vblank_count != 0 && primary_screen != NULL)
		primary_screen->register_vblank_callback(vblank_state_delegate(FUNC(running_machine::watchdog_vblank), this));
	save().save_item(NAME(m_watchdog_enabled));
	save().save_item(NAME(m_watchdog_counter));

=======
	// initialize the streams engine before the sound devices start
	m_sound = std::make_unique<sound_manager>(*this);

	// configure the address spaces, load ROMs (which needs
	// width/endianess of the spaces), then populate memory (which
	// needs rom bases), and finally initialize CPUs (which needs
	// complete address spaces).  These operations must proceed in this
	// order
	m_rom_load = make_unique_clear<rom_load_manager>(*this);
	m_memory.initialize();

>>>>>>> upstream/master
	// save the random seed or save states might be broken in drivers that use the rand() method
	save().save_item(NAME(m_rand_seed));

	// initialize image devices
<<<<<<< HEAD
	image_init(*this);
	m_tilemap.reset(global_alloc(tilemap_manager(*this)));
	crosshair_init(*this);
	network_init(*this);

	// initialize the debugger
	if ((debug_flags & DEBUG_FLAG_ENABLED) != 0)
		debugger_init(*this);

	m_render->resolve_tags();

	// call the game driver's init function
	// this is where decryption is done and memory maps are altered
	// so this location in the init order is important
	ui().set_startup_text(_("Initializing..."), true);

	// register callbacks for the devices, then start them
	add_notifier(MACHINE_NOTIFY_RESET, machine_notify_delegate(FUNC(running_machine::reset_all_devices), this));
	add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(FUNC(running_machine::stop_all_devices), this));
	save().register_presave(save_prepost_delegate(FUNC(running_machine::presave_all_devices), this));
	start_all_devices();
	save().register_postload(save_prepost_delegate(FUNC(running_machine::postload_all_devices), this));
=======
	m_image = std::make_unique<image_manager>(*this);
	m_tilemap = std::make_unique<tilemap_manager>(*this);
	m_crosshair = make_unique_clear<crosshair_manager>(*this);
	m_network = std::make_unique<network_manager>(*this);

	// initialize the debugger
	if ((debug_flags & DEBUG_FLAG_ENABLED) != 0)
	{
		m_debug_view = std::make_unique<debug_view_manager>(*this);
		m_debugger = std::make_unique<debugger_manager>(*this);
	}

	m_render->resolve_tags();

	manager().create_custom(*this);

	// register callbacks for the devices, then start them
	add_notifier(MACHINE_NOTIFY_RESET, machine_notify_delegate(&running_machine::reset_all_devices, this));
	add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(&running_machine::stop_all_devices, this));
	save().register_presave(save_prepost_delegate(FUNC(running_machine::presave_all_devices), this));
	start_all_devices();
	save().register_postload(save_prepost_delegate(FUNC(running_machine::postload_all_devices), this));
	manager().load_cheatfiles(*this);
>>>>>>> upstream/master

	// if we're coming in with a savegame request, process it now
	const char *savegame = options().state();
	if (savegame[0] != 0)
		schedule_load(savegame);

	// if we're in autosave mode, schedule a load
	else if (options().autosave() && (m_system.flags & MACHINE_SUPPORTS_SAVE) != 0)
		schedule_load("auto");

<<<<<<< HEAD
	// set up the cheat engine
	m_cheat.reset(global_alloc(cheat_manager(*this)));

	// allocate autoboot timer
	m_autoboot_timer = scheduler().timer_alloc(timer_expired_delegate(FUNC(running_machine::autoboot_callback), this));

#ifdef USE_HISCORE
	//MKCHAMP - INITIALIZING THE HISCORE ENGINE
 	hiscore_init(*this);
#endif /* USE_HISCORE */

=======
>>>>>>> upstream/master
	manager().update_machine();
}


//-------------------------------------------------
//  run - execute the machine
//-------------------------------------------------

<<<<<<< HEAD
int running_machine::run(bool firstrun)
{
	int error = MAMERR_NONE;
=======
int running_machine::run(bool quiet)
{
	int error = EMU_ERR_NONE;
>>>>>>> upstream/master

	// use try/catch for deep error recovery
	try
	{
<<<<<<< HEAD
		// move to the init phase
		m_current_phase = MACHINE_PHASE_INIT;

		// if we have a logfile, set up the callback
		if (options().log() && &system() != &GAME_NAME(___empty))
		{
			m_logfile.reset(global_alloc(emu_file(OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS)));
			file_error filerr = m_logfile->open("error.log");
			assert_always(filerr == FILERR_NONE, "unable to open log file");
			add_logerror_callback(logfile_callback);
=======
		m_manager.http()->clear();

		// move to the init phase
		m_current_phase = machine_phase::INIT;

		// if we have a logfile, set up the callback
		if (options().log() && !quiet)
		{
			m_logfile = std::make_unique<emu_file>(OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS);
			osd_file::error filerr = m_logfile->open("error.log");
			assert_always(filerr == osd_file::error::NONE, "unable to open log file");

			using namespace std::placeholders;
			add_logerror_callback(std::bind(&running_machine::logfile_callback, this, _1));
>>>>>>> upstream/master
		}

		// then finish setting up our local machine
		start();

<<<<<<< HEAD
		// load the configuration settings and NVRAM
		config_load_settings(*this);
=======
		// load the configuration settings
		m_configuration->load_settings();
>>>>>>> upstream/master

		// disallow save state registrations starting here.
		// Don't do it earlier, config load can create network
		// devices with timers.
		m_save.allow_registration(false);

<<<<<<< HEAD
		nvram_load();
		sound().ui_mute(false);

		// initialize ui lists
		ui().initialize(*this);

		// display the startup screens
		ui().display_startup_screens(firstrun, false);
=======
		// load the NVRAM
		nvram_load();

		// set the time on RTCs (this may overwrite parts of NVRAM)
		set_rtc_datetime(system_time(m_base_time));

		sound().ui_mute(false);
		if (!quiet)
			sound().start_recording();

		// initialize ui lists
		// display the startup screens
		manager().ui_initialize(*this);
>>>>>>> upstream/master

		// perform a soft reset -- this takes us to the running phase
		soft_reset();

<<<<<<< HEAD
#ifdef MAME_DEBUG
		g_tagmap_finds = 0;
		if (strcmp(config().m_gamedrv.name, "___empty") != 0)
			g_tagmap_counter_enabled = true;
#endif
		// handle initial load
		if (m_saveload_schedule != SLS_NONE)
			handle_saveload();

		// run the CPUs until a reset or exit
		m_hard_reset_pending = false;
		while ((!m_hard_reset_pending && !m_exit_pending) || m_saveload_schedule != SLS_NONE)
		{
			g_profiler.start(PROFILER_EXTRA);

#if defined(EMSCRIPTEN)
			//break out to our async javascript loop and halt
			js_set_main_loop(this);
#endif

			// execute CPUs if not paused
			if (!m_paused)
				m_scheduler.timeslice();

=======
		// handle initial load
		if (m_saveload_schedule != saveload_schedule::NONE)
			handle_saveload();

		export_http_api();

		m_hard_reset_pending = false;

#if defined(EMSCRIPTEN)
		// break out to our async javascript loop and halt
		emscripten_set_running_machine(this);
#endif

		// run the CPUs until a reset or exit
		while ((!m_hard_reset_pending && !m_exit_pending) || m_saveload_schedule != saveload_schedule::NONE)
		{
			g_profiler.start(PROFILER_EXTRA);

			// execute CPUs if not paused
			if (!m_paused)
				m_scheduler.timeslice();
>>>>>>> upstream/master
			// otherwise, just pump video updates through
			else
				m_video->frame_update();

			// handle save/load
<<<<<<< HEAD
			if (m_saveload_schedule != SLS_NONE)
=======
			if (m_saveload_schedule != saveload_schedule::NONE)
>>>>>>> upstream/master
				handle_saveload();

			g_profiler.stop();
		}
<<<<<<< HEAD

		// and out via the exit phase
		m_current_phase = MACHINE_PHASE_EXIT;

#ifdef MAME_DEBUG
		if (g_tagmap_counter_enabled)
		{
			g_tagmap_counter_enabled = false;
			if (*(options().command()) == 0)
				osd_printf_info("%d tagmap lookups\n", g_tagmap_finds);
		}
#endif
=======
		m_manager.http()->clear();

		// and out via the exit phase
		m_current_phase = machine_phase::EXIT;
>>>>>>> upstream/master

		// save the NVRAM and configuration
		sound().ui_mute(true);
		nvram_save();
<<<<<<< HEAD
		// mamep: dont save settings during playback
		if (!ioport().has_playback_file())
			config_save_settings(*this);
	}
	catch (emu_fatalerror &fatal)
	{
		osd_printf_error("FATALERROR: %s\n", fatal.string());
		error = MAMERR_FATALERROR;
=======
		m_configuration->save_settings();
	}
	catch (emu_fatalerror &fatal)
	{
		osd_printf_error("Fatal error: %s\n", fatal.string());
		error = EMU_ERR_FATALERROR;
>>>>>>> upstream/master
		if (fatal.exitcode() != 0)
			error = fatal.exitcode();
	}
	catch (emu_exception &)
	{
		osd_printf_error("Caught unhandled emulator exception\n");
<<<<<<< HEAD
		error = MAMERR_FATALERROR;
=======
		error = EMU_ERR_FATALERROR;
>>>>>>> upstream/master
	}
	catch (binding_type_exception &btex)
	{
		osd_printf_error("Error performing a late bind of type %s to %s\n", btex.m_actual_type.name(), btex.m_target_type.name());
<<<<<<< HEAD
		error = MAMERR_FATALERROR;
	}
	catch (add_exception &aex)
	{
		osd_printf_error("Tag '%s' already exists in tagged_list\n", aex.tag());
		error = MAMERR_FATALERROR;
=======
		error = EMU_ERR_FATALERROR;
	}
	catch (tag_add_exception &aex)
	{
		osd_printf_error("Tag '%s' already exists in tagged map\n", aex.tag());
		error = EMU_ERR_FATALERROR;
>>>>>>> upstream/master
	}
	catch (std::exception &ex)
	{
		osd_printf_error("Caught unhandled %s exception: %s\n", typeid(ex).name(), ex.what());
<<<<<<< HEAD
		error = MAMERR_FATALERROR;
=======
		error = EMU_ERR_FATALERROR;
>>>>>>> upstream/master
	}
	catch (...)
	{
		osd_printf_error("Caught unhandled exception\n");
<<<<<<< HEAD
		error = MAMERR_FATALERROR;
=======
		error = EMU_ERR_FATALERROR;
>>>>>>> upstream/master
	}

	// make sure our phase is set properly before cleaning up,
	// in case we got here via exception
<<<<<<< HEAD
	m_current_phase = MACHINE_PHASE_EXIT;

#ifdef MAME_DEBUG
	if (g_tagmap_counter_enabled)
	{
		g_tagmap_counter_enabled = false;
		if (*(options().command()) == 0)
			osd_printf_info("%d tagmap lookups\n", g_tagmap_finds);
	}
#endif

	// call all exit callbacks registered
	call_notifiers(MACHINE_NOTIFY_EXIT);
	zip_file_cache_clear();
=======
	m_current_phase = machine_phase::EXIT;

	// call all exit callbacks registered
	call_notifiers(MACHINE_NOTIFY_EXIT);
	util::archive_file::cache_clear();
>>>>>>> upstream/master

	// close the logfile
	m_logfile.reset();
	return error;
}

<<<<<<< HEAD

=======
>>>>>>> upstream/master
//-------------------------------------------------
//  schedule_exit - schedule a clean exit
//-------------------------------------------------

void running_machine::schedule_exit()
{
	m_exit_pending = true;

	// if we're executing, abort out immediately
	m_scheduler.eat_all_cycles();

<<<<<<< HEAD
#ifdef MAME_DEBUG
	if (g_tagmap_counter_enabled)
	{
		g_tagmap_counter_enabled = false;
		if (*(options().command()) == 0)
			osd_printf_info("%d tagmap lookups\n", g_tagmap_finds);
	}
#endif

=======
>>>>>>> upstream/master
	// if we're autosaving on exit, schedule a save as well
	if (options().autosave() && (m_system.flags & MACHINE_SUPPORTS_SAVE) && this->time() > attotime::zero)
		schedule_save("auto");
}


//-------------------------------------------------
//  schedule_hard_reset - schedule a hard-reset of
//  the machine
//-------------------------------------------------

void running_machine::schedule_hard_reset()
{
	m_hard_reset_pending = true;

	// if we're executing, abort out immediately
	m_scheduler.eat_all_cycles();
}


//-------------------------------------------------
//  schedule_soft_reset - schedule a soft-reset of
//  the system
//-------------------------------------------------

void running_machine::schedule_soft_reset()
{
	m_soft_reset_timer->adjust(attotime::zero);

	// we can't be paused since the timer needs to fire
	resume();

	// if we're executing, abort out immediately
	m_scheduler.eat_all_cycles();
}


//-------------------------------------------------
//  get_statename - allow to specify a subfolder of
//  the state directory for state loading/saving,
//  very useful for MESS and consoles or computers
//  where you can have separate folders for diff
//  software
//-------------------------------------------------

<<<<<<< HEAD
std::string running_machine::get_statename(const char *option)
{
	std::string statename_str("");
	if (option == NULL || option[0] == 0)
=======
std::string running_machine::get_statename(const char *option) const
{
	std::string statename_str("");
	if (option == nullptr || option[0] == 0)
>>>>>>> upstream/master
		statename_str.assign("%g");
	else
		statename_str.assign(option);

	// strip any extension in the provided statename
	int index = statename_str.find_last_of('.');
	if (index != -1)
		statename_str = statename_str.substr(0, index);

	// handle %d in the template (for image devices)
	std::string statename_dev("%d_");
	int pos = statename_str.find(statename_dev);

	if (pos != -1)
	{
		// if more %d are found, revert to default and ignore them all
		if (statename_str.find(statename_dev.c_str(), pos + 3) != -1)
			statename_str.assign("%g");
		// else if there is a single %d, try to create the correct snapname
		else
		{
			int name_found = 0;

			// find length of the device name
			int end1 = statename_str.find("/", pos + 3);
			int end2 = statename_str.find("%", pos + 3);
			int end;

			if ((end1 != -1) && (end2 != -1))
<<<<<<< HEAD
				end = MIN(end1, end2);
=======
				end = std::min(end1, end2);
>>>>>>> upstream/master
			else if (end1 != -1)
				end = end1;
			else if (end2 != -1)
				end = end2;
			else
				end = statename_str.length();

			if (end - pos < 3)
				fatalerror("Something very wrong is going on!!!\n");

			// copy the device name to an std::string
			std::string devname_str;
			devname_str.assign(statename_str.substr(pos + 3, end - pos - 3));
			//printf("check template: %s\n", devname_str.c_str());

			// verify that there is such a device for this system
<<<<<<< HEAD
			image_interface_iterator iter(root_device());
			for (device_image_interface *image = iter.first(); image != NULL; image = iter.next())
			{
				// get the device name
				std::string tempdevname(image->brief_instance_name());
=======
			for (device_image_interface &image : image_interface_iterator(root_device()))
			{
				// get the device name
				std::string tempdevname(image.brief_instance_name());
>>>>>>> upstream/master
				//printf("check device: %s\n", tempdevname.c_str());

				if (devname_str.compare(tempdevname) == 0)
				{
					// verify that such a device has an image mounted
<<<<<<< HEAD
					if (image->basename_noext() != NULL)
					{
						std::string filename(image->basename_noext());
=======
					if (image.basename_noext() != nullptr)
					{
						std::string filename(image.basename_noext());
>>>>>>> upstream/master

						// setup snapname and remove the %d_
						strreplace(statename_str, devname_str.c_str(), filename.c_str());
						statename_str.erase(pos, 3);
						//printf("check image: %s\n", filename.c_str());

						name_found = 1;
					}
				}
			}

			// or fallback to default
			if (name_found == 0)
				statename_str.assign("%g");
		}
	}

	// substitute path and gamename up front
	strreplace(statename_str, "/", PATH_SEPARATOR);
	strreplace(statename_str, "%g", basename());

	return statename_str;
}

<<<<<<< HEAD
//-------------------------------------------------
//  set_saveload_filename - specifies the filename
//  for state loading/saving
//-------------------------------------------------

void running_machine::set_saveload_filename(const char *filename)
{
	// free any existing request and allocate a copy of the requested name
	if (osd_is_absolute_path(filename))
	{
		m_saveload_searchpath = NULL;
		m_saveload_pending_file.assign(filename);
	}
	else
	{
		m_saveload_searchpath = options().state_directory();
		// take into account the statename option
		const char *stateopt = options().state_name();
		std::string statename = get_statename(stateopt);
		m_saveload_pending_file.assign(statename.c_str()).append(PATH_SEPARATOR).append(filename).append(".sta");
	}
=======

//-------------------------------------------------
//  compose_saveload_filename - composes a filename
//  for state loading/saving
//-------------------------------------------------

std::string running_machine::compose_saveload_filename(std::string &&filename, const char **searchpath)
{
	std::string result;

	// is this an absolute path?
	if (osd_is_absolute_path(filename))
	{
		// if so, this is easy
		if (searchpath != nullptr)
			*searchpath = nullptr;
		result = std::move(filename);
	}
	else
	{
		// this is a relative path; first specify the search path
		if (searchpath != nullptr)
			*searchpath = options().state_directory();

		// take into account the statename option
		const char *stateopt = options().state_name();
		std::string statename = get_statename(stateopt);
		result = string_format("%s%s%s.sta", statename, PATH_SEPARATOR, filename);
	}
	return result;
}


//-------------------------------------------------
//  set_saveload_filename - specifies the filename
//  for state loading/saving
//-------------------------------------------------

void running_machine::set_saveload_filename(std::string &&filename)
{
	// compose the save/load filename and persist it
	m_saveload_pending_file = compose_saveload_filename(std::move(filename), &m_saveload_searchpath);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  schedule_save - schedule a save to occur as
//  soon as possible
//-------------------------------------------------

<<<<<<< HEAD
void running_machine::schedule_save(const char *filename)
{
	// specify the filename to save or load
	set_saveload_filename(filename);

	// note the start time and set a timer for the next timeslice to actually schedule it
	m_saveload_schedule = SLS_SAVE;
=======
void running_machine::schedule_save(std::string &&filename)
{
	// specify the filename to save or load
	set_saveload_filename(std::move(filename));

	// note the start time and set a timer for the next timeslice to actually schedule it
	m_saveload_schedule = saveload_schedule::SAVE;
>>>>>>> upstream/master
	m_saveload_schedule_time = this->time();

	// we can't be paused since we need to clear out anonymous timers
	resume();
}


//-------------------------------------------------
//  immediate_save - save state.
//-------------------------------------------------

void running_machine::immediate_save(const char *filename)
{
	// specify the filename to save or load
	set_saveload_filename(filename);

	// set up some parameters for handle_saveload()
<<<<<<< HEAD
	m_saveload_schedule = SLS_SAVE;
=======
	m_saveload_schedule = saveload_schedule::SAVE;
>>>>>>> upstream/master
	m_saveload_schedule_time = this->time();

	// jump right into the save, anonymous timers can't hurt us!
	handle_saveload();
}


//-------------------------------------------------
//  schedule_load - schedule a load to occur as
//  soon as possible
//-------------------------------------------------

<<<<<<< HEAD
void running_machine::schedule_load(const char *filename)
{
	// specify the filename to save or load
	set_saveload_filename(filename);

	// note the start time and set a timer for the next timeslice to actually schedule it
	m_saveload_schedule = SLS_LOAD;
=======
void running_machine::schedule_load(std::string &&filename)
{
	// specify the filename to save or load
	set_saveload_filename(std::move(filename));

	// note the start time and set a timer for the next timeslice to actually schedule it
	m_saveload_schedule = saveload_schedule::LOAD;
>>>>>>> upstream/master
	m_saveload_schedule_time = this->time();

	// we can't be paused since we need to clear out anonymous timers
	resume();
}


//-------------------------------------------------
//  immediate_load - load state.
//-------------------------------------------------

void running_machine::immediate_load(const char *filename)
{
	// specify the filename to save or load
	set_saveload_filename(filename);

	// set up some parameters for handle_saveload()
<<<<<<< HEAD
	m_saveload_schedule = SLS_LOAD;
=======
	m_saveload_schedule = saveload_schedule::LOAD;
>>>>>>> upstream/master
	m_saveload_schedule_time = this->time();

	// jump right into the load, anonymous timers can't hurt us
	handle_saveload();
}


//-------------------------------------------------
//  pause - pause the system
//-------------------------------------------------

void running_machine::pause()
{
	// ignore if nothing has changed
	if (m_paused)
		return;
	m_paused = true;

	// call the callbacks
	call_notifiers(MACHINE_NOTIFY_PAUSE);
}


//-------------------------------------------------
//  resume - resume the system
//-------------------------------------------------

void running_machine::resume()
{
	// ignore if nothing has changed
	if (!m_paused)
		return;
	m_paused = false;

	// call the callbacks
	call_notifiers(MACHINE_NOTIFY_RESUME);
}


//-------------------------------------------------
//  toggle_pause - toggles the pause state
//-------------------------------------------------

void running_machine::toggle_pause()
{
	if (paused())
		resume();
	else
		pause();
}


//-------------------------------------------------
//  add_notifier - add a notifier of the
//  given type
//-------------------------------------------------

<<<<<<< HEAD
void running_machine::add_notifier(machine_notification event, machine_notify_delegate callback)
{
	assert_always(m_current_phase == MACHINE_PHASE_INIT, "Can only call add_notifier at init time!");

	// exit notifiers are added to the head, and executed in reverse order
	if (event == MACHINE_NOTIFY_EXIT)
		m_notifier_list[event].prepend(*global_alloc(notifier_callback_item(callback)));

	// all other notifiers are added to the tail, and executed in the order registered
	else
		m_notifier_list[event].append(*global_alloc(notifier_callback_item(callback)));
=======
void running_machine::add_notifier(machine_notification event, machine_notify_delegate callback, bool first)
{
	assert_always(m_current_phase == machine_phase::INIT, "Can only call add_notifier at init time!");

	if(first)
		m_notifier_list[event].push_front(std::make_unique<notifier_callback_item>(callback));

	// exit notifiers are added to the head, and executed in reverse order
	else if (event == MACHINE_NOTIFY_EXIT)
		m_notifier_list[event].push_front(std::make_unique<notifier_callback_item>(callback));

	// all other notifiers are added to the tail, and executed in the order registered
	else
		m_notifier_list[event].push_back(std::make_unique<notifier_callback_item>(callback));
>>>>>>> upstream/master
}


//-------------------------------------------------
//  add_logerror_callback - adds a callback to be
//  called on logerror()
//-------------------------------------------------

void running_machine::add_logerror_callback(logerror_callback callback)
{
<<<<<<< HEAD
	assert_always(m_current_phase == MACHINE_PHASE_INIT, "Can only call add_logerror_callback at init time!");
	m_logerror_list.append(*global_alloc(logerror_callback_item(callback)));
}

/*-------------------------------------------------
    popmessage - pop up a user-visible message
-------------------------------------------------*/

void running_machine::popmessage(const char *format, ...) const
{
	// if the format is NULL, it is a signal to clear the popmessage
	if (format == NULL)
		ui().popup_time(0, " ");

	// otherwise, generate the buffer and call the UI to display the message
	else
	{
		std::string temp;
		va_list arg;

		// dump to the buffer
		va_start(arg, format);
		strvprintf(temp,format, arg);
		va_end(arg);

		// pop it in the UI
		ui().popup_time(temp.length() / 40 + 2, "%s", temp.c_str());
	}
}


/*-------------------------------------------------
    logerror - log to the debugger and any other
    OSD-defined output streams
-------------------------------------------------*/

void running_machine::logerror(const char *format, ...) const
{
	va_list arg;
	va_start(arg, format);
	vlogerror(format, arg);
	va_end(arg);
=======
	assert_always(m_current_phase == machine_phase::INIT, "Can only call add_logerror_callback at init time!");
		m_string_buffer.reserve(1024);
	m_logerror_list.push_back(std::make_unique<logerror_callback_item>(callback));
}


//-------------------------------------------------
//  strlog - send an error logging string to the
//  debugger and any OSD-defined output streams
//-------------------------------------------------

void running_machine::strlog(const char *str) const
{
	// log to all callbacks
	for (auto &cb : m_logerror_list)
		cb->m_func(str);
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  vlogerror - vprintf-style error logging
//-------------------------------------------------

void running_machine::vlogerror(const char *format, va_list args) const
{
	// process only if there is a target
	if (m_logerror_list.first() != NULL)
	{
		g_profiler.start(PROFILER_LOGERROR);

		// dump to the buffer
		vsnprintf(giant_string_buffer, ARRAY_LENGTH(giant_string_buffer), format, args);

		// log to all callbacks
		for (logerror_callback_item *cb = m_logerror_list.first(); cb != NULL; cb = cb->next())
			(*cb->m_func)(*this, giant_string_buffer);

		g_profiler.stop();
	}
}


=======
//  debug_break - breaks into the debugger, if
//  enabled
//-------------------------------------------------

void running_machine::debug_break()
{
	if ((debug_flags & DEBUG_FLAG_ENABLED) != 0)
		debugger().debug_break();
}

>>>>>>> upstream/master
//-------------------------------------------------
//  base_datetime - retrieve the time of the host
//  system; useful for RTC implementations
//-------------------------------------------------

void running_machine::base_datetime(system_time &systime)
{
	systime.set(m_base_time);
}


//-------------------------------------------------
//  current_datetime - retrieve the current time
//  (offset by the base); useful for RTC
//  implementations
//-------------------------------------------------

void running_machine::current_datetime(system_time &systime)
{
	systime.set(m_base_time + this->time().seconds());
}


//-------------------------------------------------
<<<<<<< HEAD
//  rand - standardized random numbers
//-------------------------------------------------

UINT32 running_machine::rand()
=======
//  set_rtc_datetime - set the current time on
//  battery-backed RTCs
//-------------------------------------------------

void running_machine::set_rtc_datetime(const system_time &systime)
{
	for (device_rtc_interface &rtc : rtc_interface_iterator(root_device()))
		if (rtc.has_battery())
			rtc.set_current_time(systime);
}


//-------------------------------------------------
//  rand - standardized random numbers
//-------------------------------------------------

u32 running_machine::rand()
>>>>>>> upstream/master
{
	m_rand_seed = 1664525 * m_rand_seed + 1013904223;

	// return rotated by 16 bits; the low bits have a short period
	// and are frequently used
	return (m_rand_seed >> 16) | (m_rand_seed << 16);
}


//-------------------------------------------------
//  call_notifiers - call notifiers of the given
//  type
//-------------------------------------------------

void running_machine::call_notifiers(machine_notification which)
{
<<<<<<< HEAD
	for (notifier_callback_item *cb = m_notifier_list[which].first(); cb != NULL; cb = cb->next())
=======
	for (auto& cb : m_notifier_list[which])
>>>>>>> upstream/master
		cb->m_func();
}


//-------------------------------------------------
//  handle_saveload - attempt to perform a save
//  or load
//-------------------------------------------------

void running_machine::handle_saveload()
{
<<<<<<< HEAD
	UINT32 openflags = (m_saveload_schedule == SLS_LOAD) ? OPEN_FLAG_READ : (OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS);
	const char *opnamed = (m_saveload_schedule == SLS_LOAD) ? _("loaded") : _("saved");
	const char *opname = (m_saveload_schedule == SLS_LOAD) ? _("load") : _("save");
	file_error filerr = FILERR_NONE;

	// if no name, bail
	emu_file file(m_saveload_searchpath, openflags);
	if (m_saveload_pending_file.empty())
		goto cancel;

	// if there are anonymous timers, we can't save just yet, and we can't load yet either
	// because the timers might overwrite data we have loaded
	if (!m_scheduler.can_save())
	{
		// if more than a second has passed, we're probably screwed
		if ((this->time() - m_saveload_schedule_time) > attotime::from_seconds(1))
		{
			popmessage(_("Unable to %s due to pending anonymous timers. See error.log for details."), opname);
			goto cancel;
		}
		return;
	}

	// open the file
	filerr = file.open(m_saveload_pending_file.c_str());
	if (filerr == FILERR_NONE)
	{
		// read/write the save state
		save_error saverr = (m_saveload_schedule == SLS_LOAD) ? m_save.read_file(file) : m_save.write_file(file);

		// handle the result
		switch (saverr)
		{
			case STATERR_ILLEGAL_REGISTRATIONS:
				popmessage(_("Error: Unable to %s state due to illegal registrations. See error.log for details."), opname);
				break;

			case STATERR_INVALID_HEADER:
				popmessage(_("Error: Unable to %s state due to an invalid header. Make sure the save state is correct for this game."), opname);
				break;

			case STATERR_READ_ERROR:
				popmessage(_("Error: Unable to %s state due to a read error (file is likely corrupt)."), opname);
				break;

			case STATERR_WRITE_ERROR:
				popmessage(_("Error: Unable to %s state due to a write error. Verify there is enough disk space."), opname);
				break;

			case STATERR_NONE:
				if (!(m_system.flags & MACHINE_SUPPORTS_SAVE))
					popmessage(_("State successfully %s.\nWarning: Save states are not officially supported for this game."), opnamed);
				else
					popmessage(_("State successfully %s."), opnamed);
				break;

			default:
				popmessage(_("Error: Unknown error during state %s."), opnamed);
				break;
		}

		// close and perhaps delete the file
		if (saverr != STATERR_NONE && m_saveload_schedule == SLS_SAVE)
			file.remove_on_close();
	}
	else
		popmessage(_("Error: Failed to open file for %s operation."), opname);

	// unschedule the operation
cancel:
	m_saveload_pending_file.clear();
	m_saveload_searchpath = NULL;
	m_saveload_schedule = SLS_NONE;
=======
	// if no name, bail
	if (!m_saveload_pending_file.empty())
	{
		const char *const opname = (m_saveload_schedule == saveload_schedule::LOAD) ? "load" : "save";

		// if there are anonymous timers, we can't save just yet, and we can't load yet either
		// because the timers might overwrite data we have loaded
		if (!m_scheduler.can_save())
		{
			// if more than a second has passed, we're probably screwed
			if ((this->time() - m_saveload_schedule_time) > attotime::from_seconds(1))
				popmessage("Unable to %s due to pending anonymous timers. See error.log for details.", opname);
			else
				return; // return without cancelling the operation
		}
		else
		{
			u32 const openflags = (m_saveload_schedule == saveload_schedule::LOAD) ? OPEN_FLAG_READ : (OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS);

			// open the file
			emu_file file(m_saveload_searchpath, openflags);
			auto const filerr = file.open(m_saveload_pending_file);
			if (filerr == osd_file::error::NONE)
			{
				const char *const opnamed = (m_saveload_schedule == saveload_schedule::LOAD) ? "loaded" : "saved";

				// read/write the save state
				save_error saverr = (m_saveload_schedule == saveload_schedule::LOAD) ? m_save.read_file(file) : m_save.write_file(file);

				// handle the result
				switch (saverr)
				{
				case STATERR_ILLEGAL_REGISTRATIONS:
					popmessage("Error: Unable to %s state due to illegal registrations. See error.log for details.", opname);
					break;

				case STATERR_INVALID_HEADER:
					popmessage("Error: Unable to %s state due to an invalid header. Make sure the save state is correct for this machine.", opname);
					break;

				case STATERR_READ_ERROR:
					popmessage("Error: Unable to %s state due to a read error (file is likely corrupt).", opname);
					break;

				case STATERR_WRITE_ERROR:
					popmessage("Error: Unable to %s state due to a write error. Verify there is enough disk space.", opname);
					break;

				case STATERR_NONE:
					if (!(m_system.flags & MACHINE_SUPPORTS_SAVE))
						popmessage("State successfully %s.\nWarning: Save states are not officially supported for this machine.", opnamed);
					else
						popmessage("State successfully %s.", opnamed);
					break;

				default:
					popmessage("Error: Unknown error during state %s.", opnamed);
					break;
				}

				// close and perhaps delete the file
				if (saverr != STATERR_NONE && m_saveload_schedule == saveload_schedule::SAVE)
					file.remove_on_close();
			}
			else
				popmessage("Error: Failed to open file for %s operation.", opname);
		}
	}

	// unschedule the operation
	m_saveload_pending_file.clear();
	m_saveload_searchpath = nullptr;
	m_saveload_schedule = saveload_schedule::NONE;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  soft_reset - actually perform a soft-reset
//  of the system
//-------------------------------------------------

<<<<<<< HEAD
void running_machine::soft_reset(void *ptr, INT32 param)
=======
void running_machine::soft_reset(void *ptr, s32 param)
>>>>>>> upstream/master
{
	logerror("Soft reset\n");

	// temporarily in the reset phase
<<<<<<< HEAD
	m_current_phase = MACHINE_PHASE_RESET;

	// set up the watchdog timer; only start off enabled if explicitly configured
	m_watchdog_enabled = (config().m_watchdog_vblank_count != 0 || config().m_watchdog_time != attotime::zero);
	watchdog_reset();
	m_watchdog_enabled = true;
=======
	m_current_phase = machine_phase::RESET;
>>>>>>> upstream/master

	// call all registered reset callbacks
	call_notifiers(MACHINE_NOTIFY_RESET);

<<<<<<< HEAD
	// setup autoboot if needed
	m_autoboot_timer->adjust(attotime(options().autoboot_delay(),0),0);

	// now we're running
	m_current_phase = MACHINE_PHASE_RUNNING;
}


//-------------------------------------------------
//  watchdog_reset - reset the watchdog timer
//-------------------------------------------------

void running_machine::watchdog_reset()
{
	// if we're not enabled, skip it
	if (!m_watchdog_enabled)
		m_watchdog_timer->adjust(attotime::never);

	// VBLANK-based watchdog?
	else if (config().m_watchdog_vblank_count != 0)
		m_watchdog_counter = config().m_watchdog_vblank_count;

	// timer-based watchdog?
	else if (config().m_watchdog_time != attotime::zero)
		m_watchdog_timer->adjust(config().m_watchdog_time);

	// default to an obscene amount of time (3 seconds)
	else
		m_watchdog_timer->adjust(attotime::from_seconds(3));
}


//-------------------------------------------------
//  watchdog_enable - reset the watchdog timer
//-------------------------------------------------

void running_machine::watchdog_enable(bool enable)
{
	// when re-enabled, we reset our state
	if (m_watchdog_enabled != enable)
	{
		m_watchdog_enabled = enable;
		watchdog_reset();
	}
}


//-------------------------------------------------
//  watchdog_fired - watchdog timer callback
//-------------------------------------------------

void running_machine::watchdog_fired(void *ptr, INT32 param)
{
	logerror("Reset caused by the watchdog!!!\n");

	bool verbose = options().verbose();
#ifdef MAME_DEBUG
	verbose = true;
#endif
	if (verbose)
		popmessage("Reset caused by the watchdog!!!\n");

	schedule_soft_reset();
}


//-------------------------------------------------
//  watchdog_vblank - VBLANK state callback for
//  watchdog timers
//-------------------------------------------------

void running_machine::watchdog_vblank(screen_device &screen, bool vblank_state)
{
	// VBLANK starting
	if (vblank_state && m_watchdog_enabled)
	{
		// check the watchdog
		if (config().m_watchdog_vblank_count != 0)
			if (--m_watchdog_counter == 0)
				watchdog_fired();
	}
=======
	// now we're running
	m_current_phase = machine_phase::RUNNING;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  logfile_callback - callback for logging to
//  logfile
//-------------------------------------------------

<<<<<<< HEAD
void running_machine::logfile_callback(const running_machine &machine, const char *buffer)
{
	if (machine.m_logfile != NULL)
		machine.m_logfile->puts(buffer);
=======
void running_machine::logfile_callback(const char *buffer)
{
	if (m_logfile != nullptr)
	{
		m_logfile->puts(buffer);
		m_logfile->flush();
	}
>>>>>>> upstream/master
}


//-------------------------------------------------
//  start_all_devices - start any unstarted devices
//-------------------------------------------------

void running_machine::start_all_devices()
{
<<<<<<< HEAD
=======
	m_dummy_space.start();

>>>>>>> upstream/master
	// iterate through the devices
	int last_failed_starts = -1;
	while (last_failed_starts != 0)
	{
		// iterate over all devices
		int failed_starts = 0;
<<<<<<< HEAD
		device_iterator iter(root_device());
		for (device_t *device = iter.first(); device != NULL; device = iter.next())
			if (!device->started())
=======
		for (device_t &device : device_iterator(root_device()))
			if (!device.started())
>>>>>>> upstream/master
			{
				// attempt to start the device, catching any expected exceptions
				try
				{
					// if the device doesn't have a machine yet, set it first
<<<<<<< HEAD
					if (device->m_machine == NULL)
						device->set_machine(*this);

					// now start the device
					osd_printf_verbose("Starting %s '%s'\n", device->name(), device->tag());
					device->start();
=======
					if (device.m_machine == nullptr)
						device.set_machine(*this);

					// now start the device
					osd_printf_verbose("Starting %s '%s'\n", device.name(), device.tag());
					device.start();
>>>>>>> upstream/master
				}

				// handle missing dependencies by moving the device to the end
				catch (device_missing_dependencies &)
				{
					// if we're the end, fail
					osd_printf_verbose("  (missing dependencies; rescheduling)\n");
					failed_starts++;
				}
			}

		// each iteration should reduce the number of failed starts; error if
		// this doesn't happen
		if (failed_starts == last_failed_starts)
			throw emu_fatalerror("Circular dependency in device startup!");
		last_failed_starts = failed_starts;
	}
}


//-------------------------------------------------
//  reset_all_devices - reset all devices in the
//  hierarchy
//-------------------------------------------------

void running_machine::reset_all_devices()
{
	// reset the root and it will reset children
	root_device().reset();
}


//-------------------------------------------------
//  stop_all_devices - stop all the devices in the
//  hierarchy
//-------------------------------------------------

void running_machine::stop_all_devices()
{
	// first let the debugger save comments
	if ((debug_flags & DEBUG_FLAG_ENABLED) != 0)
<<<<<<< HEAD
		debug_comment_save(*this);

	// iterate over devices and stop them
	device_iterator iter(root_device());
	for (device_t *device = iter.first(); device != NULL; device = iter.next())
		device->stop();
=======
		debugger().cpu().comment_save();

	// iterate over devices and stop them
	for (device_t &device : device_iterator(root_device()))
		device.stop();
>>>>>>> upstream/master
}


//-------------------------------------------------
//  presave_all_devices - tell all the devices we
//  are about to save
//-------------------------------------------------

void running_machine::presave_all_devices()
{
<<<<<<< HEAD
	device_iterator iter(root_device());
	for (device_t *device = iter.first(); device != NULL; device = iter.next())
		device->pre_save();
=======
	for (device_t &device : device_iterator(root_device()))
		device.pre_save();
>>>>>>> upstream/master
}


//-------------------------------------------------
//  postload_all_devices - tell all the devices we
//  just completed a load
//-------------------------------------------------

void running_machine::postload_all_devices()
{
<<<<<<< HEAD
	device_iterator iter(root_device());
	for (device_t *device = iter.first(); device != NULL; device = iter.next())
		device->post_load();
=======
	for (device_t &device : device_iterator(root_device()))
		device.post_load();
>>>>>>> upstream/master
}


/***************************************************************************
    NVRAM MANAGEMENT
***************************************************************************/

<<<<<<< HEAD
const char *running_machine::image_parent_basename(device_t *device)
{
	device_t *dev = device;
	while(dev != &root_device())
	{
		device_image_interface *intf = NULL;
		if (dev!=NULL && dev->interface(intf))
		{
			return intf->basename_noext();
		}
		dev = dev->owner();
	}
	return NULL;
}

=======
>>>>>>> upstream/master
/*-------------------------------------------------
    nvram_filename - returns filename of system's
    NVRAM depending of selected BIOS
-------------------------------------------------*/

<<<<<<< HEAD
std::string &running_machine::nvram_filename(std::string &result, device_t &device)
{
	// start with either basename or basename_biosnum
	result.assign(basename());
	if (root_device().system_bios() != 0 && root_device().default_bios() != root_device().system_bios())
		strcatprintf(result, "_%d", root_device().system_bios() - 1);

	// device-based NVRAM gets its own name in a subdirectory
	if (&device != &root_device())
	{
		// add per software nvrams into one folder
		const char *software = image_parent_basename(&device);
		if (software!=NULL && strlen(software)>0)
		{
			result.append(PATH_SEPARATOR).append(software);
		}
		std::string tag(device.tag());
		tag.erase(0, 1);
		strreplacechr(tag,':', '_');
		result.append(PATH_SEPARATOR).append(tag);
	}
	return result;
=======
std::string running_machine::nvram_filename(device_t &device) const
{
	// start with either basename or basename_biosnum
	std::ostringstream result;
	result << basename();
	if (root_device().system_bios() != 0 && root_device().default_bios() != root_device().system_bios())
		util::stream_format(result, "_%d", root_device().system_bios() - 1);

	// device-based NVRAM gets its own name in a subdirectory
	if (device.owner() != nullptr)
	{
		// add per software nvrams into one folder
		const char *software = nullptr;
		for (device_t *dev = &device; dev->owner() != nullptr; dev = dev->owner())
		{
			device_image_interface *intf;
			if (dev->interface(intf))
			{
				software = intf->basename_noext();
				break;
			}
		}
		if (software != nullptr && *software != '\0')
			result << PATH_SEPARATOR << software;

		std::string tag(device.tag());
		tag.erase(0, 1);
		strreplacechr(tag,':', '_');
		result << PATH_SEPARATOR << tag;
	}
	return result.str();
>>>>>>> upstream/master
}

/*-------------------------------------------------
    nvram_load - load a system's NVRAM
-------------------------------------------------*/

void running_machine::nvram_load()
{
<<<<<<< HEAD
	nvram_interface_iterator iter(root_device());
	for (device_nvram_interface *nvram = iter.first(); nvram != NULL; nvram = iter.next())
	{
		std::string filename;
		emu_file file(options().nvram_directory(), OPEN_FLAG_READ);
		if (file.open(nvram_filename(filename, nvram->device()).c_str()) == FILERR_NONE)
		{
			nvram->nvram_load(file);
			file.close();
		}
		else
			nvram->nvram_reset();
=======
	for (device_nvram_interface &nvram : nvram_interface_iterator(root_device()))
	{
		emu_file file(options().nvram_directory(), OPEN_FLAG_READ);
		if (file.open(nvram_filename(nvram.device())) == osd_file::error::NONE)
		{
			nvram.nvram_load(file);
			file.close();
		}
		else
			nvram.nvram_reset();
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
    nvram_save - save a system's NVRAM
-------------------------------------------------*/

void running_machine::nvram_save()
{
<<<<<<< HEAD
	// mamep: dont save nvram during playback
	if (ioport().has_playback_file())
		return;

	nvram_interface_iterator iter(root_device());
	for (device_nvram_interface *nvram = iter.first(); nvram != NULL; nvram = iter.next())
	{
		std::string filename;
		emu_file file(options().nvram_directory(), OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS);
		if (file.open(nvram_filename(filename, nvram->device()).c_str()) == FILERR_NONE)
		{
			nvram->nvram_save(file);
=======
	for (device_nvram_interface &nvram : nvram_interface_iterator(root_device()))
	{
		emu_file file(options().nvram_directory(), OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS);
		if (file.open(nvram_filename(nvram.device())) == osd_file::error::NONE)
		{
			nvram.nvram_save(file);
>>>>>>> upstream/master
			file.close();
		}
	}
}

<<<<<<< HEAD
=======

//**************************************************************************
//  OUTPUT
//**************************************************************************

void running_machine::popup_clear() const
{
	ui().popup_time(0, " ");
}

void running_machine::popup_message(util::format_argument_pack<std::ostream> const &args) const
{
	std::string const temp(string_format(args));
	ui().popup_time(temp.length() / 40 + 2, "%s", temp);
}


>>>>>>> upstream/master
//**************************************************************************
//  CALLBACK ITEMS
//**************************************************************************

//-------------------------------------------------
//  notifier_callback_item - constructor
//-------------------------------------------------

running_machine::notifier_callback_item::notifier_callback_item(machine_notify_delegate func)
<<<<<<< HEAD
	: m_next(NULL),
		m_func(func)
=======
	: m_func(std::move(func))
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  logerror_callback_item - constructor
//-------------------------------------------------

running_machine::logerror_callback_item::logerror_callback_item(logerror_callback func)
<<<<<<< HEAD
	: m_next(NULL),
		m_func(func)
{
}


=======
	: m_func(func)
{
}

void running_machine::export_http_api()
{
	if (m_manager.http()->is_active()) {
		m_manager.http()->add_http_handler("/api/machine", [this](http_manager::http_request_ptr request, http_manager::http_response_ptr response)
		{
			rapidjson::StringBuffer s;
			rapidjson::Writer<rapidjson::StringBuffer> writer(s);
			writer.StartObject();
			writer.Key("name");
			writer.String(m_basename.c_str());

			writer.Key("devices");
			writer.StartArray();

			device_iterator iter(this->root_device());
			for (device_t &device : iter)
				writer.String(device.tag());

			writer.EndArray();
			writer.EndObject();

			response->set_status(200);
			response->set_content_type("application/json");
			response->set_body(s.GetString());
		});
	}
}
>>>>>>> upstream/master

//**************************************************************************
//  SYSTEM TIME
//**************************************************************************

//-------------------------------------------------
//  system_time - constructor
//-------------------------------------------------

system_time::system_time()
{
	set(0);
}

<<<<<<< HEAD
=======
system_time::system_time(time_t t)
{
	set(t);
}

>>>>>>> upstream/master

//-------------------------------------------------
//  set - fills out a system_time structure
//-------------------------------------------------

void system_time::set(time_t t)
{
	time = t;
	local_time.set(*localtime(&t));
	utc_time.set(*gmtime(&t));
}


//-------------------------------------------------
//  get_tm_time - converts a tm struction to a
//  MAME mame_system_tm structure
//-------------------------------------------------

void system_time::full_time::set(struct tm &t)
{
	second  = t.tm_sec;
	minute  = t.tm_min;
	hour    = t.tm_hour;
	mday    = t.tm_mday;
	month   = t.tm_mon;
	year    = t.tm_year + 1900;
	weekday = t.tm_wday;
<<<<<<< HEAD
	day     = t.tm_yday;
=======
	day  = t.tm_yday;
>>>>>>> upstream/master
	is_dst  = t.tm_isdst;
}



//**************************************************************************
<<<<<<< HEAD
=======
//  DUMMY ADDRESS SPACE
//**************************************************************************

READ8_MEMBER(dummy_space_device::read)
{
	throw emu_fatalerror("Attempted to read from generic address space (offs %X)\n", offset);
}

WRITE8_MEMBER(dummy_space_device::write)
{
	throw emu_fatalerror("Attempted to write to generic address space (offs %X = %02X)\n", offset, data);
}

static ADDRESS_MAP_START(dummy, 0, 8, dummy_space_device)
	AM_RANGE(0x00000000, 0xffffffff) AM_READWRITE(read, write)
ADDRESS_MAP_END

DEFINE_DEVICE_TYPE(DUMMY_SPACE, dummy_space_device, "dummy_space", "Dummy Space")

dummy_space_device::dummy_space_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock) :
	device_t(mconfig, DUMMY_SPACE, tag, owner, clock),
	device_memory_interface(mconfig, *this),
	m_space_config("dummy", ENDIANNESS_LITTLE, 8, 32, 0, nullptr, *ADDRESS_MAP_NAME(dummy))
{
}

void dummy_space_device::device_start()
{
}

//-------------------------------------------------
//  memory_space_config - return a description of
//  any address spaces owned by this device
//-------------------------------------------------

device_memory_interface::space_config_vector dummy_space_device::memory_space_config() const
{
	return space_config_vector {
		std::make_pair(0, &m_space_config)
	};
}


//**************************************************************************
>>>>>>> upstream/master
//  JAVASCRIPT PORT-SPECIFIC
//**************************************************************************

#if defined(EMSCRIPTEN)

<<<<<<< HEAD
static running_machine * jsmess_machine;

void js_main_loop()
{
	device_scheduler * scheduler;
	scheduler = &(jsmess_machine->scheduler());
	attotime stoptime(scheduler->time() + attotime(0,HZ_TO_ATTOSECONDS(60)));
	while (scheduler->time() < stoptime) {
		scheduler->timeslice();
	}
}

void js_set_main_loop(running_machine * machine) {
	jsmess_machine = machine;
	EM_ASM (
		JSMESS.running = true;
	);
	emscripten_set_main_loop(&js_main_loop, 0, 1);
}

running_machine * js_get_machine() {
	return jsmess_machine;
}

ui_manager * js_get_ui() {
	return &(jsmess_machine->ui());
}

sound_manager * js_get_sound() {
	return &(jsmess_machine->sound());
=======
running_machine * running_machine::emscripten_running_machine;

void running_machine::emscripten_main_loop()
{
	running_machine *machine = emscripten_running_machine;

	g_profiler.start(PROFILER_EXTRA);

	// execute CPUs if not paused
	if (!machine->m_paused)
	{
		device_scheduler * scheduler;
		scheduler = &(machine->scheduler());

		// Emscripten will call this function at 60Hz, so step the simulation
		// forward for the amount of time that has passed since the last frame
		const attotime frametime(0,HZ_TO_ATTOSECONDS(60));
		const attotime stoptime(scheduler->time() + frametime);

		while (!machine->m_paused && !machine->scheduled_event_pending() && scheduler->time() < stoptime)
		{
			scheduler->timeslice();
			// handle save/load
			if (machine->m_saveload_schedule != saveload_schedule::NONE)
			{
				machine->handle_saveload();
				break;
			}
		}
	}
	// otherwise, just pump video updates through
	else
		machine->m_video->frame_update();

	// cancel the emscripten loop if the system has been told to exit
	if (machine->exit_pending())
	{
		emscripten_cancel_main_loop();
	}

	g_profiler.stop();
}

void running_machine::emscripten_set_running_machine(running_machine *machine)
{
	emscripten_running_machine = machine;
	EM_ASM (
		JSMESS.running = true;
	);
	emscripten_set_main_loop(&(emscripten_main_loop), 0, 1);
}

running_machine * running_machine::emscripten_get_running_machine()
{
	return emscripten_running_machine;
}

ui_manager * running_machine::emscripten_get_ui()
{
	return &(emscripten_running_machine->ui());
}

sound_manager * running_machine::emscripten_get_sound()
{
	return &(emscripten_running_machine->sound());
}

void running_machine::emscripten_soft_reset() {
	emscripten_running_machine->schedule_soft_reset();
}
void running_machine::emscripten_hard_reset() {
	emscripten_running_machine->schedule_hard_reset();
}
void running_machine::emscripten_exit() {
	emscripten_running_machine->schedule_exit();
}
void running_machine::emscripten_save(const char *name) {
	emscripten_running_machine->schedule_save(name);
}
void running_machine::emscripten_load(const char *name) {
	emscripten_running_machine->schedule_load(name);
>>>>>>> upstream/master
}

#endif /* defined(EMSCRIPTEN) */
