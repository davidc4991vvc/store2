// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    segasnd.c

    Sound boards for early Sega G-80 based games.

***************************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "sound/sp0250.h"
#include "segasnd.h"


#define VERBOSE 0
#define LOG(x) do { if (VERBOSE) logerror x; } while (0)
=======
#include "segasnd.h"

#include "sound/sp0250.h"

#include <cmath>


#define VERBOSE 0
#include "logmacro.h"
>>>>>>> upstream/master


/***************************************************************************
    CONSTANTS
***************************************************************************/

#define SPEECH_MASTER_CLOCK 3120000

#define USB_MASTER_CLOCK    6000000
#define USB_2MHZ_CLOCK      (USB_MASTER_CLOCK/3)
#define USB_PCS_CLOCK       (USB_2MHZ_CLOCK/2)
#define USB_GOS_CLOCK       (USB_2MHZ_CLOCK/16/4)
#define MM5837_CLOCK        100000

#define SAMPLE_RATE         (USB_2MHZ_CLOCK/8)



/***************************************************************************
    INLINE FUNCTIONS
***************************************************************************/

<<<<<<< HEAD
INLINE void configure_filter(g80_filter_state *state, double r, double c)
{
	state->capval = 0;
	state->exponent = 1.0 - exp(-1.0 / (r * c * SAMPLE_RATE));
}


INLINE double step_rc_filter(g80_filter_state *state, double input)
{
	state->capval += (input - state->capval) * state->exponent;
	return state->capval;
}


INLINE double step_cr_filter(g80_filter_state *state, double input)
{
	double result = (input - state->capval);
	state->capval += (input - state->capval) * state->exponent;
=======
inline void usb_sound_device::g80_filter_state::configure(double r, double c)
{
	capval = 0.0;
	exponent = 1.0 - std::exp(-1.0 / (r * c * SAMPLE_RATE));
}


inline double usb_sound_device::g80_filter_state::step_rc(double input)
{
	return capval += (input - capval) * exponent;
}


inline double usb_sound_device::g80_filter_state::step_cr(double input)
{
	double const result = input - capval;
	capval += result * exponent;
>>>>>>> upstream/master
	return result;
}



/***************************************************************************
    SPEECH BOARD
***************************************************************************/

<<<<<<< HEAD
const device_type SEGASPEECH = &device_creator<speech_sound_device>;

speech_sound_device::speech_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, SEGASPEECH, "Sega Speech Sound Board", tag, owner, clock, "sega_speech_sound", __FILE__),
=======
DEFINE_DEVICE_TYPE(SEGASPEECH, speech_sound_device, "sega_speech_sound", "Sega Speech Sound Board")

speech_sound_device::speech_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock)
	: device_t(mconfig, SEGASPEECH, tag, owner, clock),
>>>>>>> upstream/master
		device_sound_interface(mconfig, *this),
		m_drq(0),
		m_latch(0),
		m_t0(0),
		m_p2(0),
<<<<<<< HEAD
		m_speech(NULL)
=======
		m_speech(nullptr)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void speech_sound_device::device_start()
{
		m_speech = machine().root_device().memregion("speech")->base();

		save_item(NAME(m_latch));
		save_item(NAME(m_t0));
		save_item(NAME(m_p2));
		save_item(NAME(m_drq));
}


/*************************************
 *
 *  i8035 port accessors
 *
 *************************************/



<<<<<<< HEAD
READ8_MEMBER( speech_sound_device::t0_r )
=======
READ_LINE_MEMBER( speech_sound_device::t0_r )
>>>>>>> upstream/master
{
	return m_t0;
}

<<<<<<< HEAD
READ8_MEMBER( speech_sound_device::t1_r )
=======
READ_LINE_MEMBER( speech_sound_device::t1_r )
>>>>>>> upstream/master
{
	return m_drq;
}

READ8_MEMBER( speech_sound_device::p1_r )
{
	return m_latch & 0x7f;
}

READ8_MEMBER( speech_sound_device::rom_r )
{
	return m_speech[0x100 * (m_p2 & 0x3f) + offset];
}

WRITE8_MEMBER( speech_sound_device::p1_w )
{
	if (!(data & 0x80))
		m_t0 = 0;
}

WRITE8_MEMBER( speech_sound_device::p2_w )
{
	m_p2 = data;
}



/*************************************
 *
 *  i8035 port accessors
 *
 *************************************/

WRITE_LINE_MEMBER(speech_sound_device::drq_w)
{
	m_drq = (state == ASSERT_LINE);
}



/*************************************
 *
 *  External access
 *
 *************************************/

TIMER_CALLBACK_MEMBER( speech_sound_device::delayed_speech_w )
{
	int data = param;
<<<<<<< HEAD
	UINT8 old = m_latch;
=======
	u8 old = m_latch;
>>>>>>> upstream/master

	/* all 8 bits are latched */
	m_latch = data;

	/* the high bit goes directly to the INT line */
	machine().device("audiocpu")->execute().set_input_line(0, (data & 0x80) ? CLEAR_LINE : ASSERT_LINE);

	/* a clock on the high bit clocks a 1 into T0 */
	if (!(old & 0x80) && (data & 0x80))
		m_t0 = 1;
}


WRITE8_MEMBER( speech_sound_device::data_w )
{
	space.machine().scheduler().synchronize(timer_expired_delegate(FUNC(speech_sound_device::delayed_speech_w), this), data);
}


WRITE8_MEMBER( speech_sound_device::control_w )
{
<<<<<<< HEAD
	LOG(("Speech control = %X\n", data));
=======
	LOG("Speech control = %X\n", data);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  sound_stream_update - handle a stream update
//-------------------------------------------------

void speech_sound_device::sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples)
{
}


/*************************************
 *
 *  Speech board address maps
 *
 *************************************/

<<<<<<< HEAD
static ADDRESS_MAP_START( speech_map, AS_PROGRAM, 8, driver_device )
=======
static ADDRESS_MAP_START( speech_map, AS_PROGRAM, 8, speech_sound_device )
>>>>>>> upstream/master
	AM_RANGE(0x0000, 0x07ff) AM_MIRROR(0x0800) AM_ROM
ADDRESS_MAP_END


<<<<<<< HEAD
static ADDRESS_MAP_START( speech_portmap, AS_IO, 8, driver_device )
	AM_RANGE(0x00, 0xff) AM_DEVREAD("segaspeech", speech_sound_device, rom_r)
	AM_RANGE(0x00, 0xff) AM_DEVWRITE("speech", sp0250_device, write)
	AM_RANGE(MCS48_PORT_P1, MCS48_PORT_P1) AM_DEVREADWRITE("segaspeech", speech_sound_device, p1_r, p1_w)
	AM_RANGE(MCS48_PORT_P2, MCS48_PORT_P2) AM_DEVWRITE("segaspeech", speech_sound_device, p2_w)
	AM_RANGE(MCS48_PORT_T0, MCS48_PORT_T0) AM_DEVREAD("segaspeech", speech_sound_device, t0_r)
	AM_RANGE(MCS48_PORT_T1, MCS48_PORT_T1) AM_DEVREAD("segaspeech", speech_sound_device, t1_r)
=======
static ADDRESS_MAP_START( speech_portmap, AS_IO, 8, speech_sound_device )
	AM_RANGE(0x00, 0xff) AM_DEVREAD("segaspeech", speech_sound_device, rom_r)
	AM_RANGE(0x00, 0xff) AM_DEVWRITE("speech", sp0250_device, write)
>>>>>>> upstream/master
ADDRESS_MAP_END


/*************************************
 *
 *  Speech board machine drivers
 *
 *************************************/

<<<<<<< HEAD
MACHINE_CONFIG_FRAGMENT( sega_speech_board )
=======
MACHINE_CONFIG_START( sega_speech_board )
>>>>>>> upstream/master

	/* CPU for the speech board */
	MCFG_CPU_ADD("audiocpu", I8035, SPEECH_MASTER_CLOCK)        /* divide by 15 in CPU */
	MCFG_CPU_PROGRAM_MAP(speech_map)
	MCFG_CPU_IO_MAP(speech_portmap)
<<<<<<< HEAD
=======
	MCFG_MCS48_PORT_P1_IN_CB(DEVREAD8("segaspeech", speech_sound_device, p1_r))
	MCFG_MCS48_PORT_P1_OUT_CB(DEVWRITE8("segaspeech", speech_sound_device, p1_w))
	MCFG_MCS48_PORT_P2_OUT_CB(DEVWRITE8("segaspeech", speech_sound_device, p2_w))
	MCFG_MCS48_PORT_T0_IN_CB(DEVREADLINE("segaspeech", speech_sound_device, t0_r))
	MCFG_MCS48_PORT_T1_IN_CB(DEVREADLINE("segaspeech", speech_sound_device, t1_r))
>>>>>>> upstream/master

	/* sound hardware */
	MCFG_SOUND_ADD("segaspeech", SEGASPEECH, 0)
	MCFG_SOUND_ADD("speech", SP0250, SPEECH_MASTER_CLOCK)
	MCFG_SP0250_DRQ_CALLBACK(DEVWRITELINE("segaspeech", speech_sound_device, drq_w))
<<<<<<< HEAD
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 1.0)
=======
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "speaker", 1.0)
>>>>>>> upstream/master
MACHINE_CONFIG_END



/***************************************************************************
    UNIVERSAL SOUND BOARD
***************************************************************************/

<<<<<<< HEAD
const device_type SEGAUSB = &device_creator<usb_sound_device>;

usb_sound_device::usb_sound_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source)
	: device_t(mconfig, type, name, tag, owner, clock, shortname, source),
		device_sound_interface(mconfig, *this),
		m_ourcpu(*this, "ourcpu"),
		m_stream(NULL),
=======
DEFINE_DEVICE_TYPE(SEGAUSB, usb_sound_device, "segausb", "Sega Universal Sound Board")

usb_sound_device::usb_sound_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, u32 clock)
	: device_t(mconfig, type, tag, owner, clock),
		device_sound_interface(mconfig, *this),
		m_ourcpu(*this, "ourcpu"),
		m_stream(nullptr),
>>>>>>> upstream/master
		m_in_latch(0),
		m_out_latch(0),
		m_last_p2_value(0),
		m_program_ram(*this, "pgmram"),
		m_work_ram(*this, "workram"),
		m_work_ram_bank(0),
		m_t1_clock(0),
		m_t1_clock_mask(0),
		m_noise_shift(0),
		m_noise_state(0),
		m_noise_subcount(0)
{
}

<<<<<<< HEAD
usb_sound_device::usb_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, SEGAUSB, "Sega Universal Sound Board", tag, owner, clock, "segausb", __FILE__),
		device_sound_interface(mconfig, *this),
		m_ourcpu(*this, "ourcpu"),
		m_program_ram(*this, "pgmram"),
		m_work_ram(*this, "workram")
=======
usb_sound_device::usb_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock)
	: usb_sound_device(mconfig, SEGAUSB, tag, owner, clock)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void usb_sound_device::device_start()
{
	g80_filter_state temp;
	int tchan, tgroup;

	/* find the CPU we are associated with */
	m_maincpu = machine().device("maincpu");
<<<<<<< HEAD
	assert(m_maincpu != NULL);
=======
	assert(m_maincpu != nullptr);
>>>>>>> upstream/master

	/* create a sound stream */
	m_stream = machine().sound().stream_alloc(*this, 0, 1, SAMPLE_RATE);

	/* initialize state */
	m_noise_shift = 0x15555;

<<<<<<< HEAD
	for (tgroup = 0; tgroup < 3; tgroup++)
	{
		timer8253 *g = &m_timer_group[tgroup];
		configure_filter(&g->chan_filter[0], 10e3, 1e-6);
		configure_filter(&g->chan_filter[1], 10e3, 1e-6);
		configure_filter(&g->gate1, 100e3, 0.01e-6);
		configure_filter(&g->gate2, 2 * 100e3, 0.01e-6);
	}

	configure_filter(&temp, 100e3, 0.01e-6);
	m_gate_rc1_exp[0] = temp.exponent;
	configure_filter(&temp, 1e3, 0.01e-6);
	m_gate_rc1_exp[1] = temp.exponent;
	configure_filter(&temp, 2 * 100e3, 0.01e-6);
	m_gate_rc2_exp[0] = temp.exponent;
	configure_filter(&temp, 2 * 1e3, 0.01e-6);
	m_gate_rc2_exp[1] = temp.exponent;

	configure_filter(&m_noise_filters[0], 2.7e3 + 2.7e3, 1.0e-6);
	configure_filter(&m_noise_filters[1], 2.7e3 + 1e3, 0.30e-6);
	configure_filter(&m_noise_filters[2], 2.7e3 + 270, 0.15e-6);
	configure_filter(&m_noise_filters[3], 2.7e3 + 0, 0.082e-6);
	configure_filter(&m_noise_filters[4], 33e3, 0.1e-6);

	configure_filter(&m_final_filter, 100e3, 4.7e-6);
=======
	for (timer8253 &g : m_timer_group)
	{
		g.chan_filter[0].configure(10e3, 1e-6);
		g.chan_filter[1].configure(10e3, 1e-6);
		g.gate1.configure(100e3, 0.01e-6);
		g.gate2.configure(2 * 100e3, 0.01e-6);
	}

	temp.configure(100e3, 0.01e-6);
	m_gate_rc1_exp[0] = temp.exponent;
	temp.configure(1e3, 0.01e-6);
	m_gate_rc1_exp[1] = temp.exponent;
	temp.configure(2 * 100e3, 0.01e-6);
	m_gate_rc2_exp[0] = temp.exponent;
	temp.configure(2 * 1e3, 0.01e-6);
	m_gate_rc2_exp[1] = temp.exponent;

	m_noise_filters[0].configure(2.7e3 + 2.7e3, 1.0e-6);
	m_noise_filters[1].configure(2.7e3 + 1e3, 0.30e-6);
	m_noise_filters[2].configure(2.7e3 + 270, 0.15e-6);
	m_noise_filters[3].configure(2.7e3 + 0, 0.082e-6);
	m_noise_filters[4].configure(33e3, 0.1e-6);

	m_final_filter.configure(100e3, 4.7e-6);
>>>>>>> upstream/master

	/* register for save states */
	save_item(NAME(m_in_latch));
	save_item(NAME(m_out_latch));
	save_item(NAME(m_last_p2_value));
	save_item(NAME(m_work_ram_bank));
	save_item(NAME(m_t1_clock));

	for (tgroup = 0; tgroup < 3; tgroup++)
	{
		timer8253 *group = &m_timer_group[tgroup];
		for (tchan = 0; tchan < 3; tchan++)
		{
<<<<<<< HEAD
			timer8253_channel *channel = &group->chan[tchan];
=======
			timer8253::channel *channel = &group->chan[tchan];
>>>>>>> upstream/master
			save_item(NAME(channel->holding), tgroup * 3 + tchan);
			save_item(NAME(channel->latchmode), tgroup * 3 + tchan);
			save_item(NAME(channel->latchtoggle), tgroup * 3 + tchan);
			save_item(NAME(channel->clockmode), tgroup * 3 + tchan);
			save_item(NAME(channel->bcdmode), tgroup * 3 + tchan);
			save_item(NAME(channel->output), tgroup * 3 + tchan);
			save_item(NAME(channel->lastgate), tgroup * 3 + tchan);
			save_item(NAME(channel->gate), tgroup * 3 + tchan);
			save_item(NAME(channel->subcount), tgroup * 3 + tchan);
			save_item(NAME(channel->count), tgroup * 3 + tchan);
			save_item(NAME(channel->remain), tgroup * 3 + tchan);
		}
		save_item(NAME(group->env), tgroup);
		save_item(NAME(group->chan_filter[0].capval), tgroup);
		save_item(NAME(group->chan_filter[1].capval), tgroup);
		save_item(NAME(group->gate1.capval), tgroup);
		save_item(NAME(group->gate2.capval), tgroup);
		save_item(NAME(group->config), tgroup);
	}

	save_item(NAME(m_timer_mode));
	save_item(NAME(m_noise_shift));
	save_item(NAME(m_noise_state));
	save_item(NAME(m_noise_subcount));
	save_item(NAME(m_final_filter.capval));
	save_item(NAME(m_noise_filters[0].capval));
	save_item(NAME(m_noise_filters[1].capval));
	save_item(NAME(m_noise_filters[2].capval));
	save_item(NAME(m_noise_filters[3].capval));
	save_item(NAME(m_noise_filters[4].capval));
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void usb_sound_device::device_reset()
{
	/* halt the USB CPU at reset time */
	m_ourcpu->set_input_line(INPUT_LINE_RESET, ASSERT_LINE);

	/* start the clock timer */
	m_t1_clock_mask = 0x10;
}

/*************************************
 *
 *  Initialization/reset
 *
 *************************************/

TIMER_DEVICE_CALLBACK_MEMBER( usb_sound_device::increment_t1_clock_timer_cb )
{
	/* only increment if it is not being forced clear */
	if (!(m_last_p2_value & 0x80))
		m_t1_clock++;
}

/*************************************
 *
 *  External access
 *
 *************************************/

READ8_MEMBER( usb_sound_device::status_r )
{
<<<<<<< HEAD
	LOG(("%04X:usb_data_r = %02X\n", m_maincpu->safe_pc(), (m_out_latch & 0x81) | (m_in_latch & 0x7e)));
=======
	LOG("%04X:usb_data_r = %02X\n", m_maincpu->safe_pc(), (m_out_latch & 0x81) | (m_in_latch & 0x7e));
>>>>>>> upstream/master

	m_maincpu->execute().adjust_icount(-200);

	/* only bits 0 and 7 are controlled by the I8035; the remaining */
	/* bits 1-6 reflect the current input latch values */
	return (m_out_latch & 0x81) | (m_in_latch & 0x7e);
}


TIMER_CALLBACK_MEMBER( usb_sound_device::delayed_usb_data_w )
{
	int data = param;

	/* look for rising/falling edges of bit 7 to control the RESET line */
	m_ourcpu->set_input_line(INPUT_LINE_RESET, (data & 0x80) ? ASSERT_LINE : CLEAR_LINE);

	/* if the CLEAR line is set, the low 7 bits of the input are ignored */
	if ((m_last_p2_value & 0x40) == 0)
		data &= ~0x7f;

	/* update the effective input latch */
	m_in_latch = data;
}


WRITE8_MEMBER( usb_sound_device::data_w )
{
<<<<<<< HEAD
	LOG(("%04X:usb_data_w = %02X\n", m_maincpu->safe_pc(), data));
=======
	LOG("%04X:usb_data_w = %02X\n", m_maincpu->safe_pc(), data);
>>>>>>> upstream/master
	space.machine().scheduler().synchronize(timer_expired_delegate(FUNC(usb_sound_device::delayed_usb_data_w), this), data);

	/* boost the interleave so that sequences can be sent */
	space.machine().scheduler().boost_interleave(attotime::zero, attotime::from_usec(250));
}


READ8_MEMBER( usb_sound_device::ram_r )
{
	return m_program_ram[offset];
}


WRITE8_MEMBER( usb_sound_device::ram_w )
{
	if (m_in_latch & 0x80)
		m_program_ram[offset] = data;
	else
<<<<<<< HEAD
		LOG(("%04X:sega_usb_ram_w(%03X) = %02X while /LOAD disabled\n", m_maincpu->safe_pc(), offset, data));
=======
		LOG("%04X:sega_usb_ram_w(%03X) = %02X while /LOAD disabled\n", m_maincpu->safe_pc(), offset, data);
>>>>>>> upstream/master
}



/*************************************
 *
 *  I8035 port accesses
 *
 *************************************/

READ8_MEMBER( usb_sound_device::p1_r )
{
	/* bits 0-6 are inputs and map to bits 0-6 of the input latch */
	if ((m_in_latch & 0x7f) != 0)
<<<<<<< HEAD
		LOG(("%03X: P1 read = %02X\n", m_maincpu->safe_pc(), m_in_latch & 0x7f));
=======
		LOG("%03X: P1 read = %02X\n", m_maincpu->safe_pc(), m_in_latch & 0x7f);
>>>>>>> upstream/master
	return m_in_latch & 0x7f;
}


WRITE8_MEMBER( usb_sound_device::p1_w )
{
	/* bit 7 maps to bit 0 on the output latch */
	m_out_latch = (m_out_latch & 0xfe) | (data >> 7);
<<<<<<< HEAD
	LOG(("%03X: P1 write = %02X\n", m_maincpu->safe_pc(), data));
=======
	LOG("%03X: P1 write = %02X\n", m_maincpu->safe_pc(), data);
>>>>>>> upstream/master
}


WRITE8_MEMBER( usb_sound_device::p2_w )
{
<<<<<<< HEAD
	UINT8 old = m_last_p2_value;
=======
	u8 old = m_last_p2_value;
>>>>>>> upstream/master
	m_last_p2_value = data;

	/* low 2 bits control the bank of work RAM we are addressing */
	m_work_ram_bank = data & 3;

	/* bit 6 controls the "ready" bit output to the host */
	/* it also clears the input latch from the host (active low) */
	m_out_latch = ((data & 0x40) << 1) | (m_out_latch & 0x7f);
	if ((data & 0x40) == 0)
		m_in_latch = 0;

	/* bit 7 controls the reset on the upper counter at U33 */
	if ((old & 0x80) && !(data & 0x80))
		m_t1_clock = 0;

<<<<<<< HEAD
	LOG(("%03X: P2 write -> bank=%d ready=%d clock=%d\n", m_maincpu->safe_pc(), data & 3, (data >> 6) & 1, (data >> 7) & 1));
}


READ8_MEMBER( usb_sound_device::t1_r )
=======
	LOG("%03X: P2 write -> bank=%d ready=%d clock=%d\n", m_maincpu->safe_pc(), data & 3, (data >> 6) & 1, (data >> 7) & 1);
}


READ_LINE_MEMBER( usb_sound_device::t1_r )
>>>>>>> upstream/master
{
	/* T1 returns 1 based on the value of the T1 clock; the exact */
	/* pattern is determined by one or more jumpers on the board. */
	return (m_t1_clock & m_t1_clock_mask) != 0;
}



/*************************************
 *
 *  Sound generation
 *
 *************************************/

<<<<<<< HEAD
INLINE void clock_channel(timer8253_channel *ch)
{
	UINT8 lastgate = ch->lastgate;

	/* update the gate */
	ch->lastgate = ch->gate;

	/* if we're holding, skip */
	if (ch->holding)
		return;

	/* switch off the clock mode */
	switch (ch->clockmode)
	{
		/* oneshot; waits for trigger to restart */
		case 1:
			if (!lastgate && ch->gate)
			{
				ch->output = 0;
				ch->remain = ch->count;
			}
			else
			{
				if (--ch->remain == 0)
					ch->output = 1;
=======
inline void usb_sound_device::timer8253::channel::clock()
{
	u8 const old_lastgate = lastgate;

	/* update the gate */
	lastgate = gate;

	/* if we're holding, skip */
	if (holding)
		return;

	/* switch off the clock mode */
	switch (clockmode)
	{
		/* oneshot; waits for trigger to restart */
		case 1:
			if (!old_lastgate && gate)
			{
				output = 0;
				remain = count;
			}
			else
			{
				if (--remain == 0)
					output = 1;
>>>>>>> upstream/master
			}
			break;

		/* square wave: counts down by 2 and toggles output */
		case 3:
<<<<<<< HEAD
			ch->remain = (ch->remain - 1) & ~1;
			if (ch->remain == 0)
			{
				ch->output ^= 1;
				ch->remain = ch->count;
=======
			remain = (remain - 1) & ~1;
			if (remain == 0)
			{
				output ^= 1;
				remain = count;
>>>>>>> upstream/master
			}
			break;
	}
}


/*************************************
 *
 *  USB timer and envelope controls
 *
 *************************************/

<<<<<<< HEAD
void usb_sound_device::timer_w(int which, UINT8 offset, UINT8 data)
{
	timer8253 *g = &m_timer_group[which];
	timer8253_channel *ch;
=======
void usb_sound_device::timer_w(int which, u8 offset, u8 data)
{
	timer8253 *g = &m_timer_group[which];
	timer8253::channel *ch;
>>>>>>> upstream/master
	int was_holding;

	m_stream->update();

	/* switch off the offset */
	switch (offset)
	{
		case 0:
		case 1:
		case 2:
			ch = &g->chan[offset];
			was_holding = ch->holding;

			/* based on the latching mode */
			switch (ch->latchmode)
			{
				case 1: /* low word only */
					ch->count = data;
<<<<<<< HEAD
					ch->holding = FALSE;
=======
					ch->holding = false;
>>>>>>> upstream/master
					break;

				case 2: /* high word only */
					ch->count = data << 8;
<<<<<<< HEAD
					ch->holding = FALSE;
=======
					ch->holding = false;
>>>>>>> upstream/master
					break;

				case 3: /* low word followed by high word */
					if (ch->latchtoggle == 0)
					{
						ch->count = (ch->count & 0xff00) | (data & 0x00ff);
						ch->latchtoggle = 1;
					}
					else
					{
						ch->count = (ch->count & 0x00ff) | (data << 8);
<<<<<<< HEAD
						ch->holding = FALSE;
=======
						ch->holding = false;
>>>>>>> upstream/master
						ch->latchtoggle = 0;
					}
					break;
			}

			/* if we're not holding, load the initial count for some modes */
			if (was_holding && !ch->holding)
				ch->remain = 1;
			break;

		case 3:
			/* break out the components */
			if (((data & 0xc0) >> 6) < 3)
			{
				ch = &g->chan[(data & 0xc0) >> 6];

				/* extract the bits */
<<<<<<< HEAD
				ch->holding = TRUE;
=======
				ch->holding = true;
>>>>>>> upstream/master
				ch->latchmode = (data >> 4) & 3;
				ch->clockmode = (data >> 1) & 7;
				ch->bcdmode = (data >> 0) & 1;
				ch->latchtoggle = 0;
				ch->output = (ch->clockmode == 1);
			}
			break;
	}
}


<<<<<<< HEAD
void usb_sound_device::env_w(int which, UINT8 offset, UINT8 data)
=======
void usb_sound_device::env_w(int which, u8 offset, u8 data)
>>>>>>> upstream/master
{
	timer8253 *g = &m_timer_group[which];

	m_stream->update();

	if (offset < 3)
		g->env[offset] = (double)data;
	else
		g->config = data & 1;
}



/*************************************
 *
 *  USB work RAM access
 *
 *************************************/

READ8_MEMBER( usb_sound_device::workram_r )
{
	offset += 256 * m_work_ram_bank;
	return m_work_ram[offset];
}


WRITE8_MEMBER( usb_sound_device::workram_w )
{
	offset += 256 * m_work_ram_bank;
	m_work_ram[offset] = data;

	/* writes to the low 32 bytes go to various controls */
	switch (offset & ~3)
	{
		case 0x00:  /* CTC0 */
			timer_w(0, offset & 3, data);
			break;

		case 0x04:  /* ENV0 */
			env_w(0, offset & 3, data);
			break;

		case 0x08:  /* CTC1 */
			timer_w(1, offset & 3, data);
			break;

		case 0x0c:  /* ENV1 */
			env_w(1, offset & 3, data);
			break;

		case 0x10:  /* CTC2 */
			timer_w(2, offset & 3, data);
			break;

		case 0x14:  /* ENV2 */
			env_w(2, offset & 3, data);
			break;
	}
}

//-------------------------------------------------
//  sound_stream_update - handle a stream update
//-------------------------------------------------

void usb_sound_device::sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples)
{
	stream_sample_t *dest = outputs[0];

	/* iterate over samples */
	while (samples--)
	{
		double noiseval;
		double sample = 0;
		int group;
		int step;


		/*----------------
		    Noise Source
		  ----------------

		                 RC
		   MM5837 ---> FILTER ---> CR FILTER ---> 3.2x AMP ---> NOISE
		               LADDER
		*/

		/* update the noise source */
		for (step = USB_2MHZ_CLOCK / SAMPLE_RATE; step >= m_noise_subcount; step -= m_noise_subcount)
		{
			m_noise_shift = (m_noise_shift << 1) | (((m_noise_shift >> 13) ^ (m_noise_shift >> 16)) & 1);
			m_noise_state = (m_noise_shift >> 16) & 1;
			m_noise_subcount = USB_2MHZ_CLOCK / MM5837_CLOCK;
		}
		m_noise_subcount -= step;

		/* update the filtered noise value -- this is just an approximation to the pink noise filter */
		/* being applied on the PCB, but it sounds pretty close */
		m_noise_filters[0].capval = 0.99765 * m_noise_filters[0].capval + m_noise_state * 0.0990460;
		m_noise_filters[1].capval = 0.96300 * m_noise_filters[1].capval + m_noise_state * 0.2965164;
		m_noise_filters[2].capval = 0.57000 * m_noise_filters[2].capval + m_noise_state * 1.0526913;
		noiseval = m_noise_filters[0].capval + m_noise_filters[1].capval + m_noise_filters[2].capval + m_noise_state * 0.1848;

		/* final output goes through a CR filter; the scaling factor is arbitrary to get the noise to the */
		/* correct relative volume */
<<<<<<< HEAD
		noiseval = step_cr_filter(&m_noise_filters[4], noiseval);
=======
		noiseval = m_noise_filters[4].step_cr(noiseval);
>>>>>>> upstream/master
		noiseval *= 0.075;

		/* there are 3 identical groups of circuits, each with its own 8253 */
		for (group = 0; group < 3; group++)
		{
			timer8253 *g = &m_timer_group[group];
			double chan0, chan1, chan2, mix;


			/*-------------
			    Channel 0
			  -------------

			    8253        CR                   AD7524
			    OUT0 ---> FILTER ---> BUFFER--->  VRef  ---> 100k ---> mix
			*/

			/* channel 0 clocks with the PCS clock */
			for (step = USB_2MHZ_CLOCK / SAMPLE_RATE; step >= g->chan[0].subcount; step -= g->chan[0].subcount)
			{
				g->chan[0].subcount = USB_2MHZ_CLOCK / USB_PCS_CLOCK;
				g->chan[0].gate = 1;
<<<<<<< HEAD
				clock_channel(&g->chan[0]);
=======
				g->chan[0].clock();
>>>>>>> upstream/master
			}
			g->chan[0].subcount -= step;

			/* channel 0 is mixed in with a resistance of 100k */
<<<<<<< HEAD
			chan0 = step_cr_filter(&g->chan_filter[0], g->chan[0].output) * g->env[0] * (1.0/100.0);
=======
			chan0 = g->chan_filter[0].step_cr(g->chan[0].output) * g->env[0] * (1.0/100.0);
>>>>>>> upstream/master


			/*-------------
			    Channel 1
			  -------------

			    8253        CR                   AD7524
			    OUT1 ---> FILTER ---> BUFFER--->  VRef  ---> 100k ---> mix
			*/

			/* channel 1 clocks with the PCS clock */
			for (step = USB_2MHZ_CLOCK / SAMPLE_RATE; step >= g->chan[1].subcount; step -= g->chan[1].subcount)
			{
				g->chan[1].subcount = USB_2MHZ_CLOCK / USB_PCS_CLOCK;
				g->chan[1].gate = 1;
<<<<<<< HEAD
				clock_channel(&g->chan[1]);
=======
				g->chan[1].clock();
>>>>>>> upstream/master
			}
			g->chan[1].subcount -= step;

			/* channel 1 is mixed in with a resistance of 100k */
<<<<<<< HEAD
			chan1 = step_cr_filter(&g->chan_filter[1], g->chan[1].output) * g->env[1] * (1.0/100.0);
=======
			chan1 = g->chan_filter[1].step_cr(g->chan[1].output) * g->env[1] * (1.0/100.0);
>>>>>>> upstream/master


			/*-------------
			    Channel 2
			  -------------

			  If timer_mode == 0:

			               SWITCHED                                  AD7524
			    NOISE --->    RC   ---> 1.56x AMP ---> INVERTER --->  VRef ---> 33k ---> mix
			                FILTERS

			  If timer mode == 1:

			                             AD7524                                    SWITCHED
			    NOISE ---> INVERTER --->  VRef ---> 33k ---> mix ---> INVERTER --->   RC   ---> 1.56x AMP ---> finalmix
			                                                                        FILTERS
			*/

			/* channel 2 clocks with the 2MHZ clock and triggers with the GOS clock */
			for (step = 0; step < USB_2MHZ_CLOCK / SAMPLE_RATE; step++)
			{
				if (g->chan[2].subcount-- == 0)
				{
					g->chan[2].subcount = USB_2MHZ_CLOCK / USB_GOS_CLOCK / 2 - 1;
					g->chan[2].gate = !g->chan[2].gate;
				}
<<<<<<< HEAD
				clock_channel(&g->chan[2]);
=======
				g->chan[2].clock();
>>>>>>> upstream/master
			}

			/* the exponents for the gate filters are determined by channel 2's output */
			g->gate1.exponent = m_gate_rc1_exp[g->chan[2].output];
			g->gate2.exponent = m_gate_rc2_exp[g->chan[2].output];

			/* based on the envelope mode, we do one of two things with source 2 */
			if (g->config == 0)
			{
<<<<<<< HEAD
				chan2 = step_rc_filter(&g->gate2, step_rc_filter(&g->gate1, noiseval)) * -1.56 * g->env[2] * (1.0/33.0);
=======
				chan2 = g->gate2.step_rc(g->gate1.step_rc(noiseval)) * -1.56 * g->env[2] * (1.0/33.0);
>>>>>>> upstream/master
				mix = chan0 + chan1 + chan2;
			}
			else
			{
				chan2 = -noiseval * g->env[2] * (1.0/33.0);
				mix = chan0 + chan1 + chan2;
<<<<<<< HEAD
				mix = step_rc_filter(&g->gate2, step_rc_filter(&g->gate1, -mix)) * 1.56;
=======
				mix = g->gate2.step_rc(g->gate1.step_rc(-mix)) * 1.56;
>>>>>>> upstream/master
			}

			/* accumulate the sample */
			sample += mix;
		}


		/*-------------
		    Final mix
		  -------------

		  INPUTS
		  EQUAL ---> 1.2x INVERTER ---> CR FILTER ---> out
		  WEIGHT

		*/
<<<<<<< HEAD
		*dest++ = 4000 * step_cr_filter(&m_final_filter, sample);
=======
		*dest++ = 4000 * m_final_filter.step_cr(sample);
>>>>>>> upstream/master
	}
}


/*************************************
 *
 *  USB address maps
 *
 *************************************/

static ADDRESS_MAP_START( usb_map, AS_PROGRAM, 8, usb_sound_device )
	AM_RANGE(0x0000, 0x0fff) AM_RAM AM_SHARE("pgmram")
ADDRESS_MAP_END

static ADDRESS_MAP_START( usb_portmap, AS_IO, 8, usb_sound_device )
	AM_RANGE(0x00, 0xff) AM_READWRITE(workram_r, workram_w) AM_SHARE("workram")
<<<<<<< HEAD
	AM_RANGE(MCS48_PORT_P1, MCS48_PORT_P1) AM_READWRITE(p1_r, p1_w)
	AM_RANGE(MCS48_PORT_P2, MCS48_PORT_P2) AM_WRITE(p2_w)
	AM_RANGE(MCS48_PORT_T1, MCS48_PORT_T1) AM_READ(t1_r)
ADDRESS_MAP_END


/*************************************
 *
 *  USB machine drivers
 *
 *************************************/

MACHINE_CONFIG_FRAGMENT( segausb )
=======
ADDRESS_MAP_END


//-------------------------------------------------
// device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( usb_sound_device::device_add_mconfig )
>>>>>>> upstream/master

	/* CPU for the usb board */
	MCFG_CPU_ADD("ourcpu", I8035, USB_MASTER_CLOCK)     /* divide by 15 in CPU */
	MCFG_CPU_PROGRAM_MAP(usb_map)
	MCFG_CPU_IO_MAP(usb_portmap)
<<<<<<< HEAD
=======
	MCFG_MCS48_PORT_P1_IN_CB(READ8(usb_sound_device, p1_r))
	MCFG_MCS48_PORT_P1_OUT_CB(WRITE8(usb_sound_device, p1_w))
	MCFG_MCS48_PORT_P2_OUT_CB(WRITE8(usb_sound_device, p2_w))
	MCFG_MCS48_PORT_T1_IN_CB(READLINE(usb_sound_device, t1_r))
>>>>>>> upstream/master

	MCFG_TIMER_DRIVER_ADD_PERIODIC("usb_timer", usb_sound_device, increment_t1_clock_timer_cb, attotime::from_hz(USB_2MHZ_CLOCK / 256))
MACHINE_CONFIG_END

<<<<<<< HEAD
machine_config_constructor usb_sound_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( segausb );
}

const device_type SEGAUSBROM = &device_creator<usb_rom_sound_device>;

usb_rom_sound_device::usb_rom_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: usb_sound_device(mconfig, SEGAUSBROM, "Sega Universal Sound Board with ROM", tag, owner, clock, "segausbrom", __FILE__)
=======

DEFINE_DEVICE_TYPE(SEGAUSBROM, usb_rom_sound_device, "segausbrom", "Sega Universal Sound Board with ROM")

usb_rom_sound_device::usb_rom_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock)
	: usb_sound_device(mconfig, SEGAUSBROM, tag, owner, clock)
>>>>>>> upstream/master
{
}

static ADDRESS_MAP_START( usb_map_rom, AS_PROGRAM, 8, usb_sound_device )
	AM_RANGE(0x0000, 0x0fff) AM_ROM AM_REGION(":usbcpu", 0)
ADDRESS_MAP_END

<<<<<<< HEAD
MACHINE_CONFIG_FRAGMENT( segausb_rom )

	/* CPU for the usb board */
	MCFG_CPU_ADD("ourcpu", I8035, USB_MASTER_CLOCK)     /* divide by 15 in CPU */
	MCFG_CPU_PROGRAM_MAP(usb_map_rom)
	MCFG_CPU_IO_MAP(usb_portmap)

	MCFG_TIMER_DRIVER_ADD_PERIODIC("usb_timer", usb_sound_device, increment_t1_clock_timer_cb, attotime::from_hz(USB_2MHZ_CLOCK / 256))
MACHINE_CONFIG_END

machine_config_constructor usb_rom_sound_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( segausb_rom );
}
=======
MACHINE_CONFIG_MEMBER( usb_rom_sound_device::device_add_mconfig )
	usb_sound_device::device_add_mconfig(config);

	/* CPU for the usb board */
	MCFG_CPU_MODIFY("ourcpu")
	MCFG_CPU_PROGRAM_MAP(usb_map_rom)
MACHINE_CONFIG_END
>>>>>>> upstream/master
