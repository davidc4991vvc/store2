// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
/***************************************************************************

<<<<<<< HEAD
    uiinput.c
=======
    uiinput.cpp
>>>>>>> upstream/master

    Internal MAME user interface input state.
***************************************************************************/

#include "emu.h"
#include "uiinput.h"
#include "render.h"


/***************************************************************************
    CONSTANTS
***************************************************************************/

<<<<<<< HEAD
#define EVENT_QUEUE_SIZE        128

=======
>>>>>>> upstream/master
enum
{
	SEQ_PRESSED_FALSE = 0,      /* not pressed */
	SEQ_PRESSED_TRUE,           /* pressed */
<<<<<<< HEAD
	SEQ_PRESSED_RESET           /* reset -- converted to FALSE once detected as not pressed */
};



/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

/* private input port state */
struct ui_input_private
{
	/* pressed states; retrieved with ui_input_pressed() */
	osd_ticks_t                 next_repeat[IPT_COUNT];
	UINT8                       seqpressed[IPT_COUNT];

	/* mouse position/info */
	render_target *             current_mouse_target;
	INT32                       current_mouse_x;
	INT32                       current_mouse_y;
	bool                        current_mouse_down;

	/* popped states; ring buffer of ui_events */
	ui_event                    events[EVENT_QUEUE_SIZE];
	int                         events_start;
	int                         events_end;
};



/***************************************************************************
    FUNCTION PROTOYPES
***************************************************************************/

//static void ui_input_frame_update(running_machine &machine);



/***************************************************************************
    INITIALIZATION
***************************************************************************/

/*-------------------------------------------------
    ui_input_init - initializes the UI input
    system
-------------------------------------------------*/

void ui_input_init(running_machine &machine)
{
	/* create the private data */
	machine.ui_input_data = auto_alloc_clear(machine, ui_input_private);
	machine.ui_input_data->current_mouse_x = -1;
	machine.ui_input_data->current_mouse_y = -1;

	/* add a frame callback to poll inputs */
	machine.add_notifier(MACHINE_NOTIFY_FRAME, machine_notify_delegate(FUNC(ui_input_frame_update), &machine));
=======
	SEQ_PRESSED_RESET           /* reset -- converted to false once detected as not pressed */
};


//**************************************************************************
//  UI INPUT MANAGER
//**************************************************************************

//-------------------------------------------------
//  ui_input_manager - constructor
//-------------------------------------------------

ui_input_manager::ui_input_manager(running_machine &machine)
	: m_machine(machine),
		m_current_mouse_target(nullptr),
		m_current_mouse_down(false),
		m_current_mouse_field(nullptr),
		m_events_start(0),
		m_events_end(0)
{
	/* create the private data */
	m_current_mouse_x = -1;
	m_current_mouse_y = -1;

	/* add a frame callback to poll inputs */
	machine.add_notifier(MACHINE_NOTIFY_FRAME, machine_notify_delegate(&ui_input_manager::frame_update, this));
>>>>>>> upstream/master
}



/***************************************************************************
    EVENT HANDLING
***************************************************************************/

/*-------------------------------------------------
<<<<<<< HEAD
    ui_input_frame_update - looks through pressed
=======
    frame_update - looks through pressed
>>>>>>> upstream/master
    input as per events pushed our way and posts
    corresponding IPT_UI_* events
-------------------------------------------------*/

<<<<<<< HEAD
void ui_input_frame_update(running_machine &machine)
{
	ui_input_private *uidata = machine.ui_input_data;

	/* update the state of all the UI keys */
	for (ioport_type code = ioport_type(IPT_UI_FIRST + 1); code < IPT_UI_LAST; ++code)
	{
		bool pressed = machine.ioport().type_pressed(code);
		if (!pressed || uidata->seqpressed[code] != SEQ_PRESSED_RESET)
			uidata->seqpressed[code] = pressed;
=======
void ui_input_manager::frame_update()
{
	/* update the state of all the UI keys */
	for (ioport_type code = ioport_type(IPT_UI_FIRST + 1); code < IPT_UI_LAST; ++code)
	{
		bool pressed = machine().ioport().type_pressed(code);
		if (!pressed || m_seqpressed[code] != SEQ_PRESSED_RESET)
			m_seqpressed[code] = pressed;
	}

	// perform mouse hit testing
	ioport_field *mouse_field = m_current_mouse_down ? find_mouse_field() : nullptr;
	if (m_current_mouse_field != mouse_field)
	{
		// clear the old field if there was one
		if (m_current_mouse_field != nullptr)
			m_current_mouse_field->set_value(0);

		// set the new field if it exists and isn't already being pressed
		if (mouse_field != nullptr && !mouse_field->digital_value())
			mouse_field->set_value(1);

		// update internal state
		m_current_mouse_field = mouse_field;
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
<<<<<<< HEAD
    ui_input_push_event - pushes a single event
    onto the queue
-------------------------------------------------*/

bool ui_input_push_event(running_machine &machine, ui_event evt)
{
	ui_input_private *uidata = machine.ui_input_data;

	/* we may be called before the UI is initialized */
	if (uidata == NULL)
		return false;

	/* some pre-processing (this is an icky place to do this stuff!) */
	switch (evt.event_type)
	{
		case UI_EVENT_MOUSE_MOVE:
			uidata->current_mouse_target = evt.target;
			uidata->current_mouse_x = evt.mouse_x;
			uidata->current_mouse_y = evt.mouse_y;
			break;

		case UI_EVENT_MOUSE_LEAVE:
			if (uidata->current_mouse_target == evt.target)
			{
				uidata->current_mouse_target = NULL;
				uidata->current_mouse_x = -1;
				uidata->current_mouse_y = -1;
			}
			break;

		case UI_EVENT_MOUSE_DOWN:
			uidata->current_mouse_down = true;
			break;

		case UI_EVENT_MOUSE_UP:
			uidata->current_mouse_down = false;
=======
    push_event - pushes a single event
    onto the queue
-------------------------------------------------*/

bool ui_input_manager::push_event(ui_event evt)
{
	/* some pre-processing (this is an icky place to do this stuff!) */
	switch (evt.event_type)
	{
		case ui_event::MOUSE_MOVE:
			m_current_mouse_target = evt.target;
			m_current_mouse_x = evt.mouse_x;
			m_current_mouse_y = evt.mouse_y;
			break;

		case ui_event::MOUSE_LEAVE:
			if (m_current_mouse_target == evt.target)
			{
				m_current_mouse_target = nullptr;
				m_current_mouse_x = -1;
				m_current_mouse_y = -1;
			}
			break;

		case ui_event::MOUSE_DOWN:
			m_current_mouse_down = true;
			break;

		case ui_event::MOUSE_UP:
			m_current_mouse_down = false;
>>>>>>> upstream/master
			break;

		default:
			/* do nothing */
			break;
	}

	/* is the queue filled up? */
<<<<<<< HEAD
	if ((uidata->events_end + 1) % ARRAY_LENGTH(uidata->events) == uidata->events_start)
		return false;

	uidata->events[uidata->events_end++] = evt;
	uidata->events_end %= ARRAY_LENGTH(uidata->events);
=======
	if ((m_events_end + 1) % ARRAY_LENGTH(m_events) == m_events_start)
		return false;

	m_events[m_events_end++] = evt;
	m_events_end %= ARRAY_LENGTH(m_events);
>>>>>>> upstream/master
	return true;
}


/*-------------------------------------------------
<<<<<<< HEAD
    ui_input_pop_event - pops an event off of the queue
-------------------------------------------------*/

bool ui_input_pop_event(running_machine &machine, ui_event *evt)
{
	ui_input_private *uidata = machine.ui_input_data;
	bool result;

	if (uidata->events_start != uidata->events_end)
	{
		*evt = uidata->events[uidata->events_start++];
		uidata->events_start %= ARRAY_LENGTH(uidata->events);
		result = true;
=======
    pop_event - pops an event off of the queue
-------------------------------------------------*/

bool ui_input_manager::pop_event(ui_event *evt)
{
	if (m_events_start != m_events_end)
	{
		*evt = m_events[m_events_start++];
		m_events_start %= ARRAY_LENGTH(m_events);
		return true;
>>>>>>> upstream/master
	}
	else
	{
		memset(evt, 0, sizeof(*evt));
<<<<<<< HEAD
		result = false;
	}
	return result;
=======
		return false;
	}
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    ui_input_reset - clears all outstanding events
    and resets the sequence states
-------------------------------------------------*/

void ui_input_reset(running_machine &machine)
{
	ui_input_private *uidata = machine.ui_input_data;
	int code;

	uidata->events_start = 0;
	uidata->events_end = 0;
	for (code = IPT_UI_FIRST + 1; code < IPT_UI_LAST; code++)
	{
		uidata->seqpressed[code] = SEQ_PRESSED_RESET;
		uidata->next_repeat[code] = 0;
=======
    reset - clears all outstanding events
    and resets the sequence states
-------------------------------------------------*/

void ui_input_manager::reset()
{
	int code;

	m_events_start = 0;
	m_events_end = 0;
	for (code = IPT_UI_FIRST + 1; code < IPT_UI_LAST; code++)
	{
		m_seqpressed[code] = SEQ_PRESSED_RESET;
		m_next_repeat[code] = 0;
>>>>>>> upstream/master
	}
}


/*-------------------------------------------------
<<<<<<< HEAD
    ui_input_find_mouse - retrieves the current
    location of the mouse
-------------------------------------------------*/

render_target *ui_input_find_mouse(running_machine &machine, INT32 *x, INT32 *y, bool *button)
{
	ui_input_private *uidata = machine.ui_input_data;
	if (x != NULL)
		*x = uidata->current_mouse_x;
	if (y != NULL)
		*y = uidata->current_mouse_y;
	if (button != NULL)
		*button = uidata->current_mouse_down;
	return uidata->current_mouse_target;
=======
    find_mouse - retrieves the current
    location of the mouse
-------------------------------------------------*/

render_target *ui_input_manager::find_mouse(s32 *x, s32 *y, bool *button) const
{
	if (x != nullptr)
		*x = m_current_mouse_x;
	if (y != nullptr)
		*y = m_current_mouse_y;
	if (button != nullptr)
		*button = m_current_mouse_down;
	return m_current_mouse_target;
}


/*-------------------------------------------------
    find_mouse_field - retrieves the input field
    the mouse is currently pointing at
-------------------------------------------------*/

ioport_field *ui_input_manager::find_mouse_field() const
{
	// map the point and determine what was hit
	if (m_current_mouse_target != nullptr)
	{
		ioport_port *port = nullptr;
		ioport_value mask;
		float x, y;
		if (m_current_mouse_target->map_point_input(m_current_mouse_x, m_current_mouse_y, port, mask, x, y))
		{
			if (port != nullptr)
				return port->field(mask);
		}
	}
	return nullptr;
>>>>>>> upstream/master
}



/***************************************************************************
    USER INTERFACE SEQUENCE READING
***************************************************************************/

/*-------------------------------------------------
<<<<<<< HEAD
    ui_input_pressed - return TRUE if a key down
=======
    pressed - return true if a key down
>>>>>>> upstream/master
    for the given user interface sequence is
    detected
-------------------------------------------------*/

<<<<<<< HEAD
bool ui_input_pressed(running_machine &machine, int code)
{
	return ui_input_pressed_repeat(machine, code, 0);
=======
bool ui_input_manager::pressed(int code)
{
	return pressed_repeat(code, 0);
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    ui_input_pressed_repeat - return TRUE if a key
=======
    pressed_repeat - return true if a key
>>>>>>> upstream/master
    down for the given user interface sequence is
    detected, or if autorepeat at the given speed
    is triggered
-------------------------------------------------*/

<<<<<<< HEAD
bool ui_input_pressed_repeat(running_machine &machine, int code, int speed)
{
	ui_input_private *uidata = machine.ui_input_data;
	int pressed;
=======
bool ui_input_manager::pressed_repeat(int code, int speed)
{
	bool pressed;
>>>>>>> upstream/master

g_profiler.start(PROFILER_INPUT);

	/* get the status of this key (assumed to be only in the defaults) */
	assert(code >= IPT_UI_CONFIGURE && code <= IPT_OSD_16);
<<<<<<< HEAD
	pressed = (uidata->seqpressed[code] == SEQ_PRESSED_TRUE);
=======
	pressed = (m_seqpressed[code] == SEQ_PRESSED_TRUE);
>>>>>>> upstream/master

	/* if down, handle it specially */
	if (pressed)
	{
		osd_ticks_t tps = osd_ticks_per_second();

		/* if this is the first press, set a 3x delay and leave pressed = 1 */
<<<<<<< HEAD
		if (uidata->next_repeat[code] == 0)
			uidata->next_repeat[code] = osd_ticks() + 3 * speed * tps / 60;

		/* if this is an autorepeat case, set a 1x delay and leave pressed = 1 */
		else if (speed > 0 && (osd_ticks() + tps - uidata->next_repeat[code]) >= tps)
			uidata->next_repeat[code] += 1 * speed * tps / 60;
=======
		if (m_next_repeat[code] == 0)
			m_next_repeat[code] = osd_ticks() + 3 * speed * tps / 60;

		/* if this is an autorepeat case, set a 1x delay and leave pressed = 1 */
		else if (speed > 0 && (osd_ticks() + tps - m_next_repeat[code]) >= tps)
		{
			// In the autorepeatcase, we need to double check the key is still pressed
			// as there can be a delay between the key polling and our processing of the event
			m_seqpressed[code] = machine().ioport().type_pressed(ioport_type(code));
			pressed = (m_seqpressed[code] == SEQ_PRESSED_TRUE);
			if (pressed)
				m_next_repeat[code] += 1 * speed * tps / 60;
		}
>>>>>>> upstream/master

		/* otherwise, reset pressed = 0 */
		else
			pressed = false;
	}

	/* if we're not pressed, reset the memory field */
	else
<<<<<<< HEAD
		uidata->next_repeat[code] = 0;
=======
		m_next_repeat[code] = 0;
>>>>>>> upstream/master

g_profiler.stop();

	return pressed;
}
<<<<<<< HEAD
=======

/*-------------------------------------------------
    push_mouse_move_event - pushes a mouse
    move event to the specified render_target
-------------------------------------------------*/

void ui_input_manager::push_mouse_move_event(render_target* target, s32 x, s32 y)
{
	ui_event event = { ui_event::NONE };
	event.event_type = ui_event::MOUSE_MOVE;
	event.target = target;
	event.mouse_x = x;
	event.mouse_y = y;
	push_event(event);
}

/*-------------------------------------------------
    push_mouse_leave_event - pushes a
    mouse leave event to the specified render_target
-------------------------------------------------*/

void ui_input_manager::push_mouse_leave_event(render_target* target)
{
	ui_event event = { ui_event::NONE };
	event.event_type = ui_event::MOUSE_LEAVE;
	event.target = target;
	push_event(event);
}

/*-------------------------------------------------
    push_mouse_down_event - pushes a mouse
    down event to the specified render_target
-------------------------------------------------*/

void ui_input_manager::push_mouse_down_event(render_target* target, s32 x, s32 y)
{
	ui_event event = { ui_event::NONE };
	event.event_type = ui_event::MOUSE_DOWN;
	event.target = target;
	event.mouse_x = x;
	event.mouse_y = y;
	push_event(event);
}

/*-------------------------------------------------
    push_mouse_down_event - pushes a mouse
    down event to the specified render_target
-------------------------------------------------*/

void ui_input_manager::push_mouse_up_event(render_target* target, s32 x, s32 y)
{
	ui_event event = { ui_event::NONE };
	event.event_type = ui_event::MOUSE_UP;
	event.target = target;
	event.mouse_x = x;
	event.mouse_y = y;
	push_event(event);
}

/*-------------------------------------------------
push_mouse_down_event - pushes a mouse
down event to the specified render_target
-------------------------------------------------*/

void ui_input_manager::push_mouse_rdown_event(render_target* target, s32 x, s32 y)
{
	ui_event event = { ui_event::NONE };
	event.event_type = ui_event::MOUSE_RDOWN;
	event.target = target;
	event.mouse_x = x;
	event.mouse_y = y;
	push_event(event);
}

/*-------------------------------------------------
push_mouse_down_event - pushes a mouse
down event to the specified render_target
-------------------------------------------------*/

void ui_input_manager::push_mouse_rup_event(render_target* target, s32 x, s32 y)
{
	ui_event event = { ui_event::NONE };
	event.event_type = ui_event::MOUSE_RUP;
	event.target = target;
	event.mouse_x = x;
	event.mouse_y = y;
	push_event(event);
}

/*-------------------------------------------------
    push_mouse_double_click_event - pushes
    a mouse double-click event to the specified
    render_target
-------------------------------------------------*/
void ui_input_manager::push_mouse_double_click_event(render_target* target, s32 x, s32 y)
{
	ui_event event = { ui_event::NONE };
	event.event_type = ui_event::MOUSE_DOUBLE_CLICK;
	event.target = target;
	event.mouse_x = x;
	event.mouse_y = y;
	push_event(event);
}

/*-------------------------------------------------
    push_char_event - pushes a char event
    to the specified render_target
-------------------------------------------------*/
void ui_input_manager::push_char_event(render_target* target, char32_t ch)
{
	ui_event event = { ui_event::NONE };
	event.event_type = ui_event::IME_CHAR;
	event.target = target;
	event.ch = ch;
	push_event(event);
}

/*-------------------------------------------------
    push_mouse_wheel_event - pushes a mouse
    wheel event to the specified render_target
-------------------------------------------------*/

void ui_input_manager::push_mouse_wheel_event(render_target *target, s32 x, s32 y, short delta, int ucNumLines)
{
	ui_event event = { ui_event::NONE };
	event.event_type = ui_event::MOUSE_WHEEL;
	event.target = target;
	event.mouse_x = x;
	event.mouse_y = y;
	event.zdelta = delta;
	event.num_lines = ucNumLines;
	push_event(event);
}

/*-------------------------------------------------
    mark_all_as_pressed - marks all buttons
    as if they were already pressed once
-------------------------------------------------*/
void ui_input_manager::mark_all_as_pressed()
{
	for (int code = IPT_UI_FIRST + 1; code < IPT_UI_LAST; code++)
		m_next_repeat[code] = osd_ticks();
}
>>>>>>> upstream/master
