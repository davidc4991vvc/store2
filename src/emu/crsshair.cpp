// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    crsshair.c

    Crosshair handling.
***************************************************************************/

#include "emu.h"
#include "emuopts.h"
#include "rendutil.h"
#include "config.h"
#include "xmlfile.h"
#include "crsshair.h"



/***************************************************************************
    CONSTANTS
***************************************************************************/

#define CROSSHAIR_RAW_SIZE      100
#define CROSSHAIR_RAW_ROWBYTES  ((CROSSHAIR_RAW_SIZE + 7) / 8)


/***************************************************************************
<<<<<<< HEAD
    TYPE DEFINITIONS
***************************************************************************/

struct crosshair_global
{
	UINT8               usage;                  /* true if any crosshairs are used */
	UINT8               used[MAX_PLAYERS];      /* usage per player */
	UINT8               mode[MAX_PLAYERS];      /* visibility mode per player */
	UINT8               visible[MAX_PLAYERS];   /* visibility per player */
	bitmap_argb32 *     bitmap[MAX_PLAYERS];    /* bitmap per player */
	render_texture *    texture[MAX_PLAYERS];   /* texture per player */
	screen_device *     screen[MAX_PLAYERS];    /* the screen on which this player's crosshair is drawn */
	float               x[MAX_PLAYERS];         /* current X position */
	float               y[MAX_PLAYERS];         /* current Y position */
	float               last_x[MAX_PLAYERS];    /* last X position */
	float               last_y[MAX_PLAYERS];    /* last Y position */
	UINT8               fade;                   /* color fading factor */
	UINT8               animation_counter;      /* animation frame index */
	UINT16              auto_time;              /* time in seconds to turn invisible */
	UINT16              time[MAX_PLAYERS];      /* time since last movement */
	char                name[MAX_PLAYERS][CROSSHAIR_PIC_NAME_LENGTH + 1];   /* name of crosshair png file */
};


/***************************************************************************
    GLOBAL VARIABLES
***************************************************************************/

/* global state */
static crosshair_global global;

/* raw bitmap */
static const UINT8 crosshair_raw_top[] =
=======
    GLOBAL VARIABLES
***************************************************************************/

/* raw bitmap */
static const u8 crosshair_raw_top[] =
>>>>>>> upstream/master
{
	0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,
	0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0x00,
	0x00,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xf0,0x00,
	0x01,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xf8,0x00,
	0x03,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xfc,0x00,
	0x07,0xfe,0x00,0x00,0x00,0x0f,0xfe,0x00,0x00,0x00,0x07,0xfe,0x00,
	0x0f,0xff,0x00,0x00,0x01,0xff,0xff,0xf0,0x00,0x00,0x0f,0xff,0x00,
	0x1f,0xff,0x80,0x00,0x1f,0xff,0xff,0xff,0x00,0x00,0x1f,0xff,0x80,
	0x3f,0xff,0x80,0x00,0xff,0xff,0xff,0xff,0xe0,0x00,0x1f,0xff,0xc0,
	0x7f,0xff,0xc0,0x03,0xff,0xff,0xff,0xff,0xf8,0x00,0x3f,0xff,0xe0,
	0xff,0xff,0xe0,0x07,0xff,0xff,0xff,0xff,0xfc,0x00,0x7f,0xff,0xf0,
	0x7f,0xff,0xf0,0x1f,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xe0,
	0x3f,0xff,0xf8,0x7f,0xff,0xff,0xff,0xff,0xff,0xc1,0xff,0xff,0xc0,
	0x0f,0xff,0xf8,0xff,0xff,0xff,0xff,0xff,0xff,0xe1,0xff,0xff,0x00,
	0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfb,0xff,0xfe,0x00,
	0x03,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,
	0x01,0xff,0xff,0xff,0xff,0xf0,0x01,0xff,0xff,0xff,0xff,0xf8,0x00,
	0x00,0x7f,0xff,0xff,0xff,0x00,0x00,0x1f,0xff,0xff,0xff,0xe0,0x00,
	0x00,0x3f,0xff,0xff,0xf8,0x00,0x00,0x03,0xff,0xff,0xff,0xc0,0x00,
	0x00,0x1f,0xff,0xff,0xe0,0x00,0x00,0x00,0xff,0xff,0xff,0x80,0x00,
	0x00,0x0f,0xff,0xff,0x80,0x00,0x00,0x00,0x3f,0xff,0xff,0x00,0x00,
	0x00,0x03,0xff,0xfe,0x00,0x00,0x00,0x00,0x0f,0xff,0xfc,0x00,0x00,
	0x00,0x01,0xff,0xfc,0x00,0x00,0x00,0x00,0x07,0xff,0xf8,0x00,0x00,
	0x00,0x03,0xff,0xf8,0x00,0x00,0x00,0x00,0x01,0xff,0xf8,0x00,0x00,
	0x00,0x07,0xff,0xfc,0x00,0x00,0x00,0x00,0x03,0xff,0xfc,0x00,0x00,
	0x00,0x0f,0xff,0xfe,0x00,0x00,0x00,0x00,0x07,0xff,0xfe,0x00,0x00,
	0x00,0x0f,0xff,0xff,0x00,0x00,0x00,0x00,0x0f,0xff,0xfe,0x00,0x00,
	0x00,0x1f,0xff,0xff,0x80,0x00,0x00,0x00,0x1f,0xff,0xff,0x00,0x00,
	0x00,0x1f,0xff,0xff,0x80,0x00,0x00,0x00,0x1f,0xff,0xff,0x00,0x00,
	0x00,0x3f,0xfe,0xff,0xc0,0x00,0x00,0x00,0x3f,0xff,0xff,0x80,0x00,
	0x00,0x7f,0xfc,0x7f,0xe0,0x00,0x00,0x00,0x7f,0xe7,0xff,0xc0,0x00,
	0x00,0x7f,0xf8,0x3f,0xf0,0x00,0x00,0x00,0xff,0xc3,0xff,0xc0,0x00,
	0x00,0xff,0xf8,0x1f,0xf8,0x00,0x00,0x01,0xff,0x83,0xff,0xe0,0x00,
	0x00,0xff,0xf0,0x07,0xf8,0x00,0x00,0x01,0xfe,0x01,0xff,0xe0,0x00,
	0x00,0xff,0xf0,0x03,0xfc,0x00,0x00,0x03,0xfc,0x01,0xff,0xe0,0x00,
	0x01,0xff,0xe0,0x01,0xfe,0x00,0x00,0x07,0xf8,0x00,0xff,0xf0,0x00,
	0x01,0xff,0xe0,0x00,0xff,0x00,0x00,0x0f,0xf0,0x00,0xff,0xf0,0x00,
	0x01,0xff,0xc0,0x00,0x3f,0x80,0x00,0x1f,0xc0,0x00,0x7f,0xf0,0x00,
	0x01,0xff,0xc0,0x00,0x1f,0x80,0x00,0x1f,0x80,0x00,0x7f,0xf0,0x00,
	0x03,0xff,0xc0,0x00,0x0f,0xc0,0x00,0x3f,0x00,0x00,0x7f,0xf8,0x00,
	0x03,0xff,0x80,0x00,0x07,0xe0,0x00,0x7e,0x00,0x00,0x3f,0xf8,0x00,
	0x03,0xff,0x80,0x00,0x01,0xf0,0x00,0xf8,0x00,0x00,0x3f,0xf8,0x00,
	0x03,0xff,0x80,0x00,0x00,0xf8,0x01,0xf0,0x00,0x00,0x3f,0xf8,0x00,
	0x03,0xff,0x80,0x00,0x00,0x78,0x01,0xe0,0x00,0x00,0x3f,0xf8,0x00,
	0x07,0xff,0x00,0x00,0x00,0x3c,0x03,0xc0,0x00,0x00,0x3f,0xfc,0x00,
	0x07,0xff,0x00,0x00,0x00,0x0e,0x07,0x00,0x00,0x00,0x1f,0xfc,0x00,
	0x07,0xff,0x00,0x00,0x00,0x07,0x0e,0x00,0x00,0x00,0x1f,0xfc,0x00,
	0x07,0xff,0x00,0x00,0x00,0x03,0x9c,0x00,0x00,0x00,0x1f,0xfc,0x00,
	0x07,0xff,0x00,0x00,0x00,0x01,0x98,0x00,0x00,0x00,0x1f,0xfc,0x00,
	0x07,0xff,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x1f,0xfc,0x00
};

/* per-player colors */
static const rgb_t crosshair_colors[] =
{
	rgb_t(0x40,0x40,0xff),
	rgb_t(0xff,0x40,0x40),
	rgb_t(0x40,0xff,0x40),
	rgb_t(0xff,0xff,0x40),
	rgb_t(0xff,0x40,0xff),
	rgb_t(0x40,0xff,0xff),
	rgb_t(0xff,0xff,0xff)
};


<<<<<<< HEAD
/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

static void crosshair_exit(running_machine &machine);
static void crosshair_load(running_machine &machine, int config_type, xml_data_node *parentnode);
static void crosshair_save(running_machine &machine, int config_type, xml_data_node *parentnode);

static void animate(running_machine &machine, screen_device &device, bool vblank_state);


/***************************************************************************
    CORE IMPLEMENTATION
***************************************************************************/


/*-------------------------------------------------
    create_bitmap - create the rendering
    structures for the given player
-------------------------------------------------*/

static void create_bitmap(running_machine &machine, int player)
{
	int x, y;
	char filename[20];
	rgb_t color = crosshair_colors[player];

	/* if we have a bitmap and texture for this player, kill it */
	if (global.bitmap[player] == NULL) {
		global.bitmap[player] = global_alloc(bitmap_argb32);
		global.texture[player] = machine.render().texture_alloc(render_texture::hq_scale);
	}

	emu_file crossfile(machine.options().crosshair_path(), OPEN_FLAG_READ);
	if (global.name[player][0] != 0)
	{
		/* look for user specified file */
		sprintf(filename, "%s.png", global.name[player]);
		render_load_png(*global.bitmap[player], crossfile, NULL, filename);
	}
	else
	{
		/* look for default cross?.png in crsshair\game dir */
		sprintf(filename, "cross%d.png", player + 1);
		render_load_png(*global.bitmap[player], crossfile, machine.system().name, filename);

		/* look for default cross?.png in crsshair dir */
		if (!global.bitmap[player]->valid())
			render_load_png(*global.bitmap[player], crossfile, NULL, filename);
	}

	/* if that didn't work, use the built-in one */
	if (!global.bitmap[player]->valid())
	{
		/* allocate a blank bitmap to start with */
		global.bitmap[player]->allocate(CROSSHAIR_RAW_SIZE, CROSSHAIR_RAW_SIZE);
		global.bitmap[player]->fill(rgb_t(0x00,0xff,0xff,0xff));
=======
//**************************************************************************
//  RENDER CROSSHAIR
//**************************************************************************

//-------------------------------------------------
//  render_crosshair - constructor
//-------------------------------------------------

render_crosshair::render_crosshair(running_machine &machine, int player)
	: m_machine(machine)
	, m_player(player)
	, m_used(false)
	, m_mode(CROSSHAIR_VISIBILITY_OFF)
	, m_visible(false)
	, m_texture(nullptr)
	, m_x(0.0f)
	, m_y(0.0f)
	, m_last_x(0.0f)
	, m_last_y(0.0f)
	, m_time(0)
{
	// for now, use the main screen
	m_screen = machine.first_screen();
}


//-------------------------------------------------
//  render_crosshair - destructor
//-------------------------------------------------

render_crosshair::~render_crosshair()
{
	m_machine.render().texture_free(m_texture);
}


//-------------------------------------------------
//  set_bitmap_name - change the bitmap name
//-------------------------------------------------

void render_crosshair::set_bitmap_name(const char *name)
{
	// update bitmap if name has changed
	bool changed = name != m_name;
	m_name = name;
	if (changed)
		create_bitmap();
}


//-------------------------------------------------
//  set_default_bitmap - reset to default bitmap
//-------------------------------------------------

void render_crosshair::set_default_bitmap()
{
	// update bitmap if name has changed
	bool changed = !m_name.empty();
	m_name.clear();
	if (changed || m_bitmap == nullptr)
		create_bitmap();
}


//-------------------------------------------------
//  create_bitmap - create the rendering
//  structures for the given player
//-------------------------------------------------

void render_crosshair::create_bitmap()
{
	int x, y;
	rgb_t color = m_player < ARRAY_LENGTH(crosshair_colors) ? crosshair_colors[m_player] : rgb_t::white();

	// if we have a bitmap and texture for this player, kill it
	if (m_bitmap == nullptr)
	{
		m_bitmap = std::make_unique<bitmap_argb32>();
		m_texture = m_machine.render().texture_alloc(render_texture::hq_scale);
	}

	emu_file crossfile(m_machine.options().crosshair_path(), OPEN_FLAG_READ);
	if (!m_name.empty())
	{
		// look for user specified file
		std::string filename = m_name + ".png";
		render_load_png(*m_bitmap, crossfile, nullptr, filename.c_str());
	}
	else
	{
		// look for default cross?.png in crsshair/game dir
		std::string filename = string_format("cross%d.png", m_player + 1);
		render_load_png(*m_bitmap, crossfile, m_machine.system().name, filename.c_str());

		// look for default cross?.png in crsshair dir
		if (!m_bitmap->valid())
			render_load_png(*m_bitmap, crossfile, nullptr, filename.c_str());
	}

	/* if that didn't work, use the built-in one */
	if (!m_bitmap->valid())
	{
		/* allocate a blank bitmap to start with */
		m_bitmap->allocate(CROSSHAIR_RAW_SIZE, CROSSHAIR_RAW_SIZE);
		m_bitmap->fill(rgb_t(0x00,0xff,0xff,0xff));
>>>>>>> upstream/master

		/* extract the raw source data to it */
		for (y = 0; y < CROSSHAIR_RAW_SIZE / 2; y++)
		{
			/* assume it is mirrored vertically */
<<<<<<< HEAD
			UINT32 *dest0 = &global.bitmap[player]->pix32(y);
			UINT32 *dest1 = &global.bitmap[player]->pix32(CROSSHAIR_RAW_SIZE - 1 - y);
=======
			u32 *dest0 = &m_bitmap->pix32(y);
			u32 *dest1 = &m_bitmap->pix32(CROSSHAIR_RAW_SIZE - 1 - y);
>>>>>>> upstream/master

			/* extract to two rows simultaneously */
			for (x = 0; x < CROSSHAIR_RAW_SIZE; x++)
				if ((crosshair_raw_top[y * CROSSHAIR_RAW_ROWBYTES + x / 8] << (x % 8)) & 0x80)
					dest0[x] = dest1[x] = rgb_t(0xff,0x00,0x00,0x00) | color;
		}
	}

	/* reference the new bitmap */
<<<<<<< HEAD
	global.texture[player]->set_bitmap(*global.bitmap[player], global.bitmap[player]->cliprect(), TEXFORMAT_ARGB32);
}


/*-------------------------------------------------
    crosshair_init - initialize the crosshair
    bitmaps and such
-------------------------------------------------*/

void crosshair_init(running_machine &machine)
{
	/* request a callback upon exiting */
	machine.add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(FUNC(crosshair_exit), &machine));

	/* clear all the globals */
	memset(&global, 0, sizeof(global));

	/* setup the default auto visibility time */
	global.auto_time = CROSSHAIR_VISIBILITY_AUTOTIME_DEFAULT;

	/* determine who needs crosshairs */
	for (ioport_port *port = machine.ioport().first_port(); port != NULL; port = port->next())
		for (ioport_field *field = port->first_field(); field != NULL; field = field->next())
			if (field->crosshair_axis() != CROSSHAIR_AXIS_NONE)
			{
				int player = field->player();
=======
	m_texture->set_bitmap(*m_bitmap, m_bitmap->cliprect(), TEXFORMAT_ARGB32);
}


//-------------------------------------------------
//  animate - update the crosshair state
//-------------------------------------------------

void render_crosshair::animate(u16 auto_time)
{
	// read all the port values
	if (m_used)
		m_machine.ioport().crosshair_position(m_player, m_x, m_y);

	// auto visibility
	if (m_mode == CROSSHAIR_VISIBILITY_AUTO)
	{
		if ((m_x != m_last_x) || (m_y != m_last_y))
		{
			// crosshair has moved, keep crosshair visible
			m_visible = true;
			m_last_x = m_x;
			m_last_y = m_y;
			m_time = 0;
		}
		else
		{
			// see if the player has been motionless for time specified
			// slightly confusing formula, but the effect is:
			// auto_time = 0 makes the crosshair barely visible while moved
			// every increment in auto_time is about .2s at 60Hz
			if (m_time > auto_time * 12 + 2)
				// time exceeded so turn crosshair invisible
				m_visible = false;

			// increment player visibility time
			m_time++;
		}
	}
}


//-------------------------------------------------
//  draw - render the crosshair to the container
//-------------------------------------------------

void render_crosshair::draw(render_container &container, u8 fade)
{
	// add a quad assuming a 4:3 screen (this is not perfect)
	container.add_quad(m_x - 0.03f, m_y - 0.04f, m_x + 0.03f, m_y + 0.04f,
						rgb_t(0xc0, fade, fade, fade),
						m_texture, PRIMFLAG_BLENDMODE(BLENDMODE_ALPHA));
}


//**************************************************************************
//  CROSSHAIR MANAGER
//**************************************************************************

//-------------------------------------------------
//  crosshair_manager - constructor
//-------------------------------------------------

crosshair_manager::crosshair_manager(running_machine &machine)
	: m_machine(machine)
	, m_usage(false)
	, m_animation_counter(0)
	, m_auto_time(CROSSHAIR_VISIBILITY_AUTOTIME_DEFAULT)
{
	/* request a callback upon exiting */
	machine.add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(&crosshair_manager::exit, this));

	for (int player = 0; player < MAX_PLAYERS; player++)
		m_crosshair[player] = std::make_unique<render_crosshair>(machine, player);

	/* determine who needs crosshairs */
	for (auto &port : machine.ioport().ports())
		for (ioport_field &field : port.second->fields())
			if (field.crosshair_axis() != CROSSHAIR_AXIS_NONE)
			{
				int player = field.player();
>>>>>>> upstream/master

				assert(player < MAX_PLAYERS);

				/* mark as used and set the default visibility and mode */
<<<<<<< HEAD
				global.usage = TRUE;
				global.used[player] = TRUE;
				global.mode[player] = CROSSHAIR_VISIBILITY_DEFAULT;
				global.visible[player] = (CROSSHAIR_VISIBILITY_DEFAULT == CROSSHAIR_VISIBILITY_OFF) ? FALSE : TRUE;

				/* for now, use the main screen */
				global.screen[player] = machine.first_screen();

				create_bitmap(machine, player);
			}

	/* register callbacks for when we load/save configurations */
	if (global.usage)
		config_register(machine, "crosshairs", config_saveload_delegate(FUNC(crosshair_load), &machine), config_saveload_delegate(FUNC(crosshair_save), &machine));

	/* register the animation callback */
	if (machine.first_screen() != NULL)
		machine.first_screen()->register_vblank_callback(vblank_state_delegate(FUNC(animate), &machine));
}


/*-------------------------------------------------
    crosshair_exit - free memory allocated for
    the crosshairs
-------------------------------------------------*/

static void crosshair_exit(running_machine &machine)
{
	/* free bitmaps and textures for each player */
	for (int player = 0; player < MAX_PLAYERS; player++)
	{
		machine.render().texture_free(global.texture[player]);
		global.texture[player] = NULL;

		global_free(global.bitmap[player]);
		global.bitmap[player] = NULL;
	}
}


/*-------------------------------------------------
    crosshair_get_usage - return TRUE
    if any crosshairs are used
-------------------------------------------------*/

int crosshair_get_usage(running_machine &machine)
{
	return global.usage;
}


/*-------------------------------------------------
    crosshair_get_user_settings - return the
    current crosshair settings for a player
    Note: auto_time is common for all players
-------------------------------------------------*/

void crosshair_get_user_settings(running_machine &machine, UINT8 player, crosshair_user_settings *settings)
{
	settings->auto_time = global.auto_time;
	settings->used = global.used[player];
	settings->mode = global.mode[player];
	strcpy(settings->name, global.name[player]);
}


/*-------------------------------------------------
    crosshair_set_user_settings - modify the
    current crosshair settings for a player
    Note: auto_time is common for all players
-------------------------------------------------*/

void crosshair_set_user_settings(running_machine &machine, UINT8 player, crosshair_user_settings *settings)
{
	global.auto_time = settings->auto_time;
	global.used[player] = settings->used;
	global.mode[player] = settings->mode;

	/* set visibility as specified by mode */
	/* auto mode starts with visibility off */
	global.visible[player] = (settings->mode == CROSSHAIR_VISIBILITY_ON) ? TRUE : FALSE;

	/* update bitmap if name has changed */
	int changed = strcmp(settings->name, global.name[player]);
	strcpy(global.name[player], settings->name);
	if (changed != 0)
		create_bitmap(machine, player);
=======
				m_usage = true;
				m_crosshair[player]->set_used(true);
				m_crosshair[player]->set_mode(CROSSHAIR_VISIBILITY_DEFAULT);
				m_crosshair[player]->set_visible(CROSSHAIR_VISIBILITY_DEFAULT != CROSSHAIR_VISIBILITY_OFF);
				m_crosshair[player]->set_default_bitmap();
			}

	/* register callbacks for when we load/save configurations */
	if (m_usage)
		machine.configuration().config_register("crosshairs", config_load_delegate(&crosshair_manager::config_load, this), config_save_delegate(&crosshair_manager::config_save, this));

	/* register the animation callback */
	if (machine.first_screen() != nullptr)
		machine.first_screen()->register_vblank_callback(vblank_state_delegate(&crosshair_manager::animate, this));
}

/*-------------------------------------------------
exit - free memory allocated for
the crosshairs
-------------------------------------------------*/

void crosshair_manager::exit()
{
	/* free bitmaps and textures for each player */
	for (int player = 0; player < MAX_PLAYERS; player++)
		m_crosshair[player] = nullptr;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    animate - animates the crosshair once a frame
-------------------------------------------------*/

<<<<<<< HEAD
static void animate(running_machine &machine, screen_device &device, bool vblank_state)
=======
void crosshair_manager::animate(screen_device &device, bool vblank_state)
>>>>>>> upstream/master
{
	int player;

	/* only animate once per frame, when vblank_state is 1 */
	if (!vblank_state)
		return;

	/* increment animation counter */
<<<<<<< HEAD
	global.animation_counter += 0x08;

	/* compute a fade factor from the current animation value */
	if (global.animation_counter < 0x80)
		global.fade = 0xa0 + (0x60 * ( global.animation_counter & 0x7f) / 0x80);
	else
		global.fade = 0xa0 + (0x60 * (~global.animation_counter & 0x7f) / 0x80);

	for (player = 0; player < MAX_PLAYERS; player++)
	{
		/* read all the lightgun values */
		if (global.used[player])
			device.machine().ioport().crosshair_position(player, global.x[player], global.y[player]);

		/* auto visibility */
		if (global.mode[player] == CROSSHAIR_VISIBILITY_AUTO)
		{
			if ((global.x[player] != global.last_x[player]) || (global.y[player] != global.last_y[player]))
			{
				/* crosshair has moved, keep crosshair visible */
				global.visible[player] = TRUE;
				global.last_x[player] = global.x[player];
				global.last_y[player] = global.y[player];
				global.time[player] = 0;
			}
			else
			{
				/* see if the player has been motionless for time specified */
				/* slightly confusing formula, but the effect is: */
				/* auto_time = 0 makes the crosshair barely visible while moved */
				/* every increment in auto_time is about .2s at 60Hz */
				if (global.time[player] > global.auto_time * 12 + 2)
					/* time exceeded so turn crosshair invisible */
					global.visible[player] = FALSE;

				/* increment player visibility time */
				global.time[player]++;
			}
		}
	}
=======
	m_animation_counter += 0x08;

	/* compute a fade factor from the current animation value */
	if (m_animation_counter < 0x80)
		m_fade = 0xa0 + (0x60 * ( m_animation_counter & 0x7f) / 0x80);
	else
		m_fade = 0xa0 + (0x60 * (~m_animation_counter & 0x7f) / 0x80);

	for (player = 0; player < MAX_PLAYERS; player++)
		m_crosshair[player]->animate(m_auto_time);
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    crosshair_render - render the crosshairs
    for the given screen
-------------------------------------------------*/

void crosshair_render(screen_device &screen)
=======
    render - render the crosshairs
    for the given screen
-------------------------------------------------*/

void crosshair_manager::render(screen_device &screen)
>>>>>>> upstream/master
{
	int player;

	for (player = 0; player < MAX_PLAYERS; player++)
<<<<<<< HEAD
		/* draw if visible and the right screen */
		if (global.visible[player] &&
			((global.screen[player] == &screen) || (global.screen[player] == CROSSHAIR_SCREEN_ALL)))
		{
			/* add a quad assuming a 4:3 screen (this is not perfect) */
			screen.container().add_quad(global.x[player] - 0.03f, global.y[player] - 0.04f,
										global.x[player] + 0.03f, global.y[player] + 0.04f,
										rgb_t(0xc0, global.fade, global.fade, global.fade),
										global.texture[player], PRIMFLAG_BLENDMODE(BLENDMODE_ALPHA));
		}
}


/*-------------------------------------------------
    crosshair_set_screen - sets the screen(s) for a
    given player's crosshair
-------------------------------------------------*/

void crosshair_set_screen(running_machine &machine, int player, screen_device *screen)
{
	global.screen[player] = screen;
}


/*-------------------------------------------------
    crosshair_load - read and apply data from the
    configuration file
-------------------------------------------------*/

static void crosshair_load(running_machine &machine, int config_type, xml_data_node *parentnode)
{
	/* Note: crosshair_load() is only registered if croshairs are used */

	xml_data_node *crosshairnode;
	int auto_time;

	/* we only care about game files */
	if (config_type != CONFIG_TYPE_GAME)
		return;

	/* might not have any data */
	if (parentnode == NULL)
		return;

	/* loop and get player crosshair info */
	for (crosshairnode = xml_get_sibling(parentnode->child, "crosshair"); crosshairnode; crosshairnode = xml_get_sibling(crosshairnode->next, "crosshair"))
	{
		int  player, mode;

		player = xml_get_attribute_int(crosshairnode, "player", -1);

		/* check to make sure we have a valid player */
		/* also check if the player really uses a crosshair */
		if (player >=0 && player < MAX_PLAYERS && global.used[player])
		{
			/* get, check, and store visibility mode */
			mode = xml_get_attribute_int(crosshairnode, "mode", CROSSHAIR_VISIBILITY_DEFAULT);
			if (mode >= CROSSHAIR_VISIBILITY_OFF && mode <= CROSSHAIR_VISIBILITY_AUTO)
			{
				global.mode[player] = (UINT8)mode;
				/* set visibility as specified by mode */
				/* auto mode starts with visibility off */
				global.visible[player] = (mode == CROSSHAIR_VISIBILITY_ON) ? TRUE : FALSE;
			}

			/* get and store crosshair pic name, truncate name to max length */
			strncpy(global.name[player], xml_get_attribute_string(crosshairnode, "pic", ""), CROSSHAIR_PIC_NAME_LENGTH);
			/* update bitmap */
			create_bitmap(machine, player);
=======
	{
		render_crosshair &crosshair = *m_crosshair[player];

		// draw if visible and the right screen
		if (crosshair.is_visible() && ((crosshair.screen() == &screen) || (crosshair.screen() == CROSSHAIR_SCREEN_ALL)))
			crosshair.draw(screen.container(), m_fade);
	}
}

/*-------------------------------------------------
    config_load - read and apply data from the
    configuration file
-------------------------------------------------*/

void crosshair_manager::config_load(config_type cfg_type, util::xml::data_node const *parentnode)
{
	/* Note: crosshair_load() is only registered if croshairs are used */

	/* we only care about game files */
	if (cfg_type != config_type::GAME)
		return;

	/* might not have any data */
	if (parentnode == nullptr)
		return;

	/* loop and get player crosshair info */
	for (util::xml::data_node const *crosshairnode = parentnode->get_child("crosshair"); crosshairnode; crosshairnode = crosshairnode->get_next_sibling("crosshair"))
	{
		int const player = crosshairnode->get_attribute_int("player", -1);

		// check to make sure we have a valid player
		if (player >= 0 && player < MAX_PLAYERS)
		{
			// check if the player really uses a crosshair
			render_crosshair &crosshair = *m_crosshair[player];
			if (crosshair.is_used())
			{
				// get, check, and store visibility mode
				int const mode = crosshairnode->get_attribute_int("mode", CROSSHAIR_VISIBILITY_DEFAULT);
				if (mode >= CROSSHAIR_VISIBILITY_OFF && mode <= CROSSHAIR_VISIBILITY_AUTO)
				{
					crosshair.set_mode(u8(mode));
					/* set visibility as specified by mode */
					/* auto mode starts with visibility off */
					crosshair.set_visible(mode == CROSSHAIR_VISIBILITY_ON);
				}

				// get and store crosshair pic name
				crosshair.set_bitmap_name(crosshairnode->get_attribute_string("pic", ""));
			}
>>>>>>> upstream/master
		}
	}

	/* get, check, and store auto visibility time */
<<<<<<< HEAD
	crosshairnode = xml_get_sibling(parentnode->child, "autotime");
	if (crosshairnode != NULL)
	{
		auto_time = xml_get_attribute_int(crosshairnode, "val", CROSSHAIR_VISIBILITY_AUTOTIME_DEFAULT);
		if ((auto_time >= CROSSHAIR_VISIBILITY_AUTOTIME_MIN) && (auto_time <= CROSSHAIR_VISIBILITY_AUTOTIME_MAX))
			global.auto_time = (UINT8)auto_time;
=======
	util::xml::data_node const *crosshairnode = parentnode->get_child("autotime");
	if (crosshairnode)
	{
		int const auto_time = crosshairnode->get_attribute_int("val", CROSSHAIR_VISIBILITY_AUTOTIME_DEFAULT);
		if ((auto_time >= CROSSHAIR_VISIBILITY_AUTOTIME_MIN) && (auto_time <= CROSSHAIR_VISIBILITY_AUTOTIME_MAX))
			m_auto_time = u8(auto_time);
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
<<<<<<< HEAD
    crosshair_save -  save data to the
    configuration file
-------------------------------------------------*/

static void crosshair_save(running_machine &machine, int config_type, xml_data_node *parentnode)
{
	/* Note: crosshair_save() is only registered if crosshairs are used */

	xml_data_node *crosshairnode;
	int player;

	/* we only care about game files */
	if (config_type != CONFIG_TYPE_GAME)
		return;

	for (player = 0; player < MAX_PLAYERS; player++)
	{
		if (global.used[player])
		{
			/* create a node */
			crosshairnode = xml_add_child(parentnode, "crosshair", NULL);

			if (crosshairnode != NULL)
			{
				int changed = FALSE;

				xml_set_attribute_int(crosshairnode, "player", player);

				if (global.visible[player] != CROSSHAIR_VISIBILITY_DEFAULT)
				{
					xml_set_attribute_int(crosshairnode, "mode", global.mode[player]);
					changed = TRUE;
				}

				/* the default graphic name is "", so only save if not */
				if (*(global.name[player]) != 0)
				{
					xml_set_attribute(crosshairnode, "pic", global.name[player]);
					changed = TRUE;
=======
    config_save -  save data to the
    configuration file
-------------------------------------------------*/

void crosshair_manager::config_save(config_type cfg_type, util::xml::data_node *parentnode)
{
	/* Note: crosshair_save() is only registered if crosshairs are used */

	/* we only care about game files */
	if (cfg_type != config_type::GAME)
		return;

	for (int player = 0; player < MAX_PLAYERS; player++)
	{
		const render_crosshair &crosshair = *m_crosshair[player];

		if (crosshair.is_used())
		{
			/* create a node */
			util::xml::data_node *const crosshairnode = parentnode->add_child("crosshair", nullptr);

			if (crosshairnode != nullptr)
			{
				bool changed = false;

				crosshairnode->set_attribute_int("player", player);

				if (crosshair.mode() != CROSSHAIR_VISIBILITY_DEFAULT)
				{
					crosshairnode->set_attribute_int("mode", crosshair.mode());
					changed = true;
				}

				// only save graphic name if not the default
				if (*crosshair.bitmap_name() != '\0')
				{
					crosshairnode->set_attribute("pic", crosshair.bitmap_name());
					changed = true;
>>>>>>> upstream/master
				}

				/* if nothing changed, kill the node */
				if (!changed)
<<<<<<< HEAD
					xml_delete_node(crosshairnode);
=======
					crosshairnode->delete_node();
>>>>>>> upstream/master
			}
		}
	}

	/* always store autotime so that it stays at the user value if it is needed */
<<<<<<< HEAD
	if (global.auto_time != CROSSHAIR_VISIBILITY_AUTOTIME_DEFAULT)
	{
		/* create a node */
		crosshairnode = xml_add_child(parentnode, "autotime", NULL);

		if (crosshairnode != NULL)
			xml_set_attribute_int(crosshairnode, "val", global.auto_time);
=======
	if (m_auto_time != CROSSHAIR_VISIBILITY_AUTOTIME_DEFAULT)
	{
		/* create a node */
		util::xml::data_node *const crosshairnode = parentnode->add_child("autotime", nullptr);

		if (crosshairnode != nullptr)
			crosshairnode->set_attribute_int("val", m_auto_time);
>>>>>>> upstream/master
	}

}
