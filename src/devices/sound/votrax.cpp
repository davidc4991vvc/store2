// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Aaron Giles
=======
// copyright-holders:Olivier Galibert
>>>>>>> upstream/master
/***************************************************************************

    votrax.c

<<<<<<< HEAD
    Simple VOTRAX SC-01 simulator based on sample fragments.

***************************************************************************/

#include "emu.h"
#include "votrax.h"


//**************************************************************************
//  DEBUGGING
//**************************************************************************

#define TEMP_HACKS      (1)

#define LOG_TIMING      (0)
#define LOG_LOWPARAM    (0)
#define LOG_GLOTTAL     (0)
#define LOG_TRANSITION  (0)



//**************************************************************************
//  CONSTANTS
//**************************************************************************

// note that according to the patent timing circuit, p1/p2 and phi1/phi2
// run 4x faster than all references in the patent text
const UINT32 P_CLOCK_BIT = 5;       // 5 according to timing diagram
const UINT32 PHI_CLOCK_BIT = 3;     // 3 according to timing diagram



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

// device type definition
const device_type VOTRAX_SC01 = &device_creator<votrax_sc01_device>;

// ROM definition for the Votrax phoneme ROM
ROM_START( votrax_sc01 )
	ROM_REGION( 0x200, "phoneme", 0 )
	ROM_LOAD( "sc01.bin", 0x0000, 0x200, CRC(0353dd6c) SHA1(00e8e497b96a10bd9f4d7e559433c3c209b0d3a8) )
ROM_END

// textual phoneme names for debugging
const char *const votrax_sc01_device::s_phoneme_table[64] =
=======
    Votrax SC01A simulation

***************************************************************************/

/*
  tp3 stb i1 i2 tp2
  1   1   o  o  white noise
  1   0   -  1  phone timing clock
  1   0   1  0  closure tick
  1   0   0  0  sram write pulse
  0   -   -  -  sram write pulse

i1.o = glottal impulse
i2.o = white noise

tp1 = phi clock (tied to f2q rom access)
*/

#include "emu.h"
#include "votrax.h"


DEFINE_DEVICE_TYPE(VOTRAX_SC01, votrax_sc01_device, "votrax", "Votrax SC-01")

// ROM definition for the Votrax phone ROM
ROM_START( votrax_sc01 )
	ROM_REGION64_LE( 0x200, "internal", 0 )
	ROM_LOAD( "sc01a.bin", 0x000, 0x200, CRC(fc416227) SHA1(1d6da90b1807a01b5e186ef08476119a862b5e6d) )
ROM_END

// textual phone names for debugging
const char *const votrax_sc01_device::s_phone_table[64] =
>>>>>>> upstream/master
{
	"EH3",  "EH2",  "EH1",  "PA0",  "DT",   "A1",   "A2",   "ZH",
	"AH2",  "I3",   "I2",   "I1",   "M",    "N",    "B",    "V",
	"CH",   "SH",   "Z",    "AW1",  "NG",   "AH1",  "OO1",  "OO",
	"L",    "K",    "J",    "H",    "G",    "F",    "D",    "S",
	"A",    "AY",   "Y1",   "UH3",  "AH",   "P",    "O",    "I",
	"U",    "Y",    "T",    "R",    "E",    "W",    "AE",   "AE1",
	"AW2",  "UH2",  "UH1",  "UH",   "O2",   "O1",   "IU",   "U1",
	"THV",  "TH",   "ER",   "EH",   "E1",   "AW",   "PA1",  "STOP"
};

<<<<<<< HEAD
// this waveform is derived from measuring fig. 10 in the patent
// it is only an approximation
const double votrax_sc01_device::s_glottal_wave[16] =
{
	0,
	16.0/22.0,
	-22.0/22.0,
	-17.0/22.0,
	-15.0/22.0,
	-10.0/22.0,
	-7.0/22.0,
	-4.0/22.0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  votrax_sc01_device - constructor
//-------------------------------------------------

votrax_sc01_device::votrax_sc01_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, VOTRAX_SC01, "Votrax SC-01", tag, owner, clock, "votrax", __FILE__),
		device_sound_interface(mconfig, *this),
		m_stream(NULL),
		m_phoneme_timer(NULL), m_rom(NULL), m_inflection(0), m_phoneme(0),
		m_request_cb(*this), m_request_state(0), m_internal_request(0), m_master_clock_freq(0), m_master_clock(0), m_counter_34(0),
		m_latch_70(0), m_latch_72(0), m_beta1(0), m_p2(0), m_p1(0), m_phi2(0), m_phi1(0), m_phi2_20(0), m_phi1_20(0), m_subphoneme_period(0),
		m_subphoneme_count(0), m_clock_88(0), m_latch_42(0), m_counter_84(0), m_latch_92(0), m_srff_132(false), m_srff_114(false), m_srff_112(false),
		m_srff_142(false), m_latch_80(0), m_counter_220(0), m_counter_222(0), m_counter_224(0), m_counter_234(0), m_counter_236(0), m_fgate(0),
		m_glottal_sync(0), m_0625_clock(0), m_counter_46(0), m_latch_46(0), m_latch_168(0), m_latch_170(0), m_f1(0), m_f2(0), m_fc(0), m_f3(0),
		m_f2q(0), m_va(0), m_fa(0), m_noise_clock(0), m_shift_252(0), m_counter_250(0)
{
}

//**************************************************************************
//  READ/WRITE HANDLERS
//**************************************************************************

//-------------------------------------------------
//  write - handle a write to the control register
//-------------------------------------------------

=======
// This waveform is built using a series of transistors as a resistor
// ladder.  There is first a transistor to ground, then a series of
// seven transistors one quarter the size of the first one, then it
// finishes by an active resistor to +9V.
//
// The terminal of the transistor to ground is used as a middle value.
// Index 0 is at that value. Index 1 is at 0V.  Index 2 to 8 start at
// just after the resistor down the latter.  Indices 9+ are the middle
// value again.
//
// For simplicity, we rescale the values to get the middle at 0 and
// the top at 1.  The final wave is very similar to the patent
// drawing.

const double votrax_sc01_device::s_glottal_wave[9] =
{
	0,
	-4/7.0,
	7/7.0,
	6/7.0,
	5/7.0,
	4/7.0,
	3/7.0,
	2/7.0,
	1/7.0
};


votrax_sc01_device::votrax_sc01_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, VOTRAX_SC01, tag, owner, clock),
	  device_sound_interface(mconfig, *this),
	  m_stream(nullptr),
	  m_rom(*this, "internal"),
	  m_ar_cb(*this)
{
}

>>>>>>> upstream/master
WRITE8_MEMBER( votrax_sc01_device::write )
{
	// flush out anything currently processing
	m_stream->update();

<<<<<<< HEAD
	// only 6 bits matter
	m_phoneme = data & 0x3f;
const UINT8 *rom = m_rom + (m_phoneme << 3);
osd_printf_debug("%s: STROBE %s (F1=%X F2=%X FC=%X F3=%X F2Q=%X VA=%X FA=%X CL=%X CLD=%X VD=%X PAC=%X PH=%02X)\n",
		machine().time().as_string(3), s_phoneme_table[m_phoneme],
		rom[0] >> 4, rom[1] >> 4, rom[2] >> 4, rom[3] >> 4, rom[4] >> 4, rom[5] >> 4, rom[6] >> 4,
		rom[3] & 0xf, rom[4] & 0xf, rom[5] & 0xf, rom[6] & 0xf, rom[7]);

	// the STROBE signal resets the phoneme counter
	m_counter_84 = 0xf;

	// not in the schematics, but necessary to fully reset the request latch
	m_latch_92 = 0;

	// clear the request signal
	m_request_cb(m_request_state = m_internal_request = CLEAR_LINE);
	m_phoneme_timer->adjust(attotime::zero);
=======
	u8 prev = m_phone;

	// only 6 bits matter
	m_phone = data & 0x3f;

	if(m_phone != prev || m_phone != 0x3f)
		logerror("phone %02x.%d %s\n", m_phone, m_inflection, s_phone_table[m_phone]);

	m_ar_state = CLEAR_LINE;

	// Schedule a commit/ar reset at roughly 0.1ms in the future (one
	// phi1 transition followed by the rom extra state in practice),
	// but only if there isn't already one on the fly.  It will
	// override an end-of-phone timeout if there's one pending, but
	// that's not a problem since stb does that anyway.
	if(m_timer->expire().is_never() || m_timer->param() != T_COMMIT_PHONE)
		m_timer->adjust(attotime::from_ticks(72, m_mainclock), T_COMMIT_PHONE);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  inflection_w - handle a write to the
//  inflection bits
//-------------------------------------------------

WRITE8_MEMBER( votrax_sc01_device::inflection_w )
{
	// only 2 bits matter
	data &= 3;
<<<<<<< HEAD
	if (m_inflection == data)
		return;

	// append an inflection marker
=======
	if(m_inflection == data)
		return;

>>>>>>> upstream/master
	m_stream->update();
	m_inflection = data;
}


<<<<<<< HEAD

//**************************************************************************
//  CORE LOGIC
//**************************************************************************

//-------------------------------------------------
//  update_subphoneme_clock_period - re-compute the
//  period of the sub-phoneme clock, as a multiple
//  of the master clock
//-------------------------------------------------

void votrax_sc01_device::update_subphoneme_clock_period()
{
	assert(m_latch_80 < 128);

/*
    The sub-phoneme timing circuit is based off the switching capacitor
    technique described in the Votrax patent. Replacing the capacitor
    ladder with [Rx] representing the effective resistance, the circuit
    becomes essentially a pair of op-amps:

         VM
         | i1
        [R1]
         |                       Vc
         +----------------------+
         |        +---|C1|---+  |
        [R2]      |          |  |  |\
         |Vb i2   |    |\    |  +--++\
         +--[Rx]--+----+-\   |     |  >
         |             |  >--+-----+-/
        [R3]      +----++/   Vc    |/
         |i3      |    |/
         +--------+ Va
         |
        [R4]
         |
         0

    We have two op-amps, the left used as a standard amplifier, the right
    one as a comparator.  The circuit triggers when the two inputs of the
    right op-amp are equal.

    The left part of the circuit (before C1) is simply a current injector.
    It's all made of resistors, there's no modulated input, so everything
    is going to be constant.  If you don't know about op-amps used as
    amplifiers, you just need to know that it forces its two inputs to
    have the same voltage while not sending or providing any current
    through there (only though its output in fact).

    In the schema, the injected current is i2.  Basic equations apply:
      Va = R4.i3
      Vb = Va + R3.i3
      Vb = Va + Rx.i2
      Vc = Vb + R2.i1
      VM = Vc + R1.i1
      i1 = i2 + i3

    And the tipping happens when the voltage on the right of C1 reaches
    Vc, so:
      Vc = Va + i2.T/C1

    (i2 being a constant, the integration is kinda easy)

    Some maths later:
      R3.i3 = Rx.i2 -> i3 = Rx/R3.i2
      i1 = (1+Rx/R3).i2
      Va + (Rx + R2 + R2.Rx/R3).i2 = Va + T/C1.i2
      T = C1*(Rx*(1+R2/R3) + R2)

    Which isn't, interestingly though not surprisingly, dependant on Vm,
    R1 or R4.  And you have to round it to the next multiple of
    0.2ms+0.1ms due to the clocking on p2 and its offset to p1 (charging
    only happens on p1 active), and add one p1/p2 cycle (0.2ms) for the
    discharge.

    So now you have your base clock, which you have to multiply by 16 to
    get the phoneme length.

    r2 = 9e3
    r3 = 1e3
    c1 = 1000e-12
    rx = 1/(5KHz * cx)
*/

	// determine total capacitance
	double cx = 0;
	if ((m_latch_80 & 0x01) != 0) cx += 5e-12;
	if ((m_latch_80 & 0x02) != 0) cx += 11e-12;
	if ((m_latch_80 & 0x04) != 0) cx += 21e-12;
	if ((m_latch_80 & 0x08) != 0) cx += 43e-12;
	if ((m_latch_80 & 0x10) != 0) cx += 86e-12;
	if ((m_latch_80 & 0x20) != 0) cx += 173e-12;
	if ((m_latch_80 & 0x40) != 0) cx += 345e-12;

	// apply the equation above to determine charging time
	// note that the 5kHz listed above for P1 is for a nominal master
	// clock frequency of 1.28MHz, meaning it is master clock / 128
	// which should be the P1 clock but appears to be a bit different
	double p1_frequency = double(m_master_clock_freq) / double(1 << (P_CLOCK_BIT + 2));
	double rx = 1.0 / (p1_frequency * cx);
	double period = 1000e-12 * (rx * (1.0 + 9e3 / 1e3) + 9e3);

	// convert to master clock cycles and round up
	m_subphoneme_period = UINT32(ceil(period * double(m_master_clock_freq)));
}

//-------------------------------------------------
//  bits_to_caps - compute the final capacity from
//  a grid of bit-selected caps
//-------------------------------------------------

double votrax_sc01_device::bits_to_caps(UINT32 value, int caps_count, const double *caps_values)
{
	double sum = 0;
	for(int i=0; i<caps_count; i++)
		if(value & (1<<i))
			sum += caps_values[i];
	return sum;
=======
//-------------------------------------------------
//  sound_stream_update - handle update requests
//  for our sound stream
//-------------------------------------------------

void votrax_sc01_device::sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples)
{
	for(int i=0; i<samples; i++) {
		m_sample_count++;
		if(m_sample_count & 1)
			chip_update();
		outputs[0][i] = analog_calc();
	}
}



//**************************************************************************
//  DEVICE INTERFACE
//**************************************************************************

//-------------------------------------------------
//  rom_region - return a pointer to the device's
//  internal ROM region
//-------------------------------------------------

const tiny_rom_entry *votrax_sc01_device::device_rom_region() const
{
	return ROM_NAME( votrax_sc01 );
}


//-------------------------------------------------
//  device_start - handle device startup
//-------------------------------------------------

void votrax_sc01_device::device_start()
{
	// initialize internal state
	m_mainclock = clock();
	m_sclock = m_mainclock / 18.0;
	m_cclock = m_mainclock / 36.0;
	m_stream = stream_alloc(0, 1, m_sclock);
	m_timer = timer_alloc();

	// reset outputs
	m_ar_cb.resolve_safe();
	m_ar_state = ASSERT_LINE;

	// save inputs
	save_item(NAME(m_inflection));
	save_item(NAME(m_phone));

	// save outputs
	save_item(NAME(m_ar_state));

	// save internal state
	save_item(NAME(m_rom_duration));
	save_item(NAME(m_rom_vd));
	save_item(NAME(m_rom_cld));
	save_item(NAME(m_rom_fa));
	save_item(NAME(m_rom_fc));
	save_item(NAME(m_rom_va));
	save_item(NAME(m_rom_f1));
	save_item(NAME(m_rom_f2));
	save_item(NAME(m_rom_f2q));
	save_item(NAME(m_rom_f3));
	save_item(NAME(m_rom_closure));
	save_item(NAME(m_rom_pause));
	save_item(NAME(m_cur_fa));
	save_item(NAME(m_cur_fc));
	save_item(NAME(m_cur_va));
	save_item(NAME(m_cur_f1));
	save_item(NAME(m_cur_f2));
	save_item(NAME(m_cur_f2q));
	save_item(NAME(m_cur_f3));
	save_item(NAME(m_filt_fa));
	save_item(NAME(m_filt_fc));
	save_item(NAME(m_filt_va));
	save_item(NAME(m_filt_f1));
	save_item(NAME(m_filt_f2));
	save_item(NAME(m_filt_f2q));
	save_item(NAME(m_filt_f3));
	save_item(NAME(m_phonetick));
	save_item(NAME(m_ticks));
	save_item(NAME(m_pitch));
	save_item(NAME(m_closure));
	save_item(NAME(m_update_counter));
	save_item(NAME(m_cur_closure));
	save_item(NAME(m_noise));
	save_item(NAME(m_cur_noise));
	save_item(NAME(m_voice_1));
	save_item(NAME(m_voice_2));
	save_item(NAME(m_voice_3));
	save_item(NAME(m_noise_1));
	save_item(NAME(m_noise_2));
	save_item(NAME(m_noise_3));
	save_item(NAME(m_noise_4));
	save_item(NAME(m_vn_1));
	save_item(NAME(m_vn_2));
	save_item(NAME(m_vn_3));
	save_item(NAME(m_vn_4));
	save_item(NAME(m_vn_5));
	save_item(NAME(m_vn_6));
	save_item(NAME(m_f1_a));
	save_item(NAME(m_f1_b));
	save_item(NAME(m_f2v_a));
	save_item(NAME(m_f2v_b));
	save_item(NAME(m_f2n_a));
	save_item(NAME(m_f2n_b));
	save_item(NAME(m_f3_a));
	save_item(NAME(m_f3_b));
	save_item(NAME(m_f4_a));
	save_item(NAME(m_f4_b));
	save_item(NAME(m_fx_a));
	save_item(NAME(m_fx_b));
	save_item(NAME(m_fn_a));
	save_item(NAME(m_fn_b));
}


//-------------------------------------------------
//  device_reset - handle device reset
//-------------------------------------------------

void votrax_sc01_device::device_reset()
{
	// Technically, there's no reset in this chip, and initial state
	// is random.  Still, it's a good idea to start it with something
	// sane.

	m_phone = 0x3f;
	m_inflection = 0;
	m_ar_state = ASSERT_LINE;
	m_ar_cb(m_ar_state);

	m_sample_count = 0;

	// Initialize the m_rom* values
	phone_commit();

	// Clear the interpolation sram
	m_cur_fa = m_cur_fc = m_cur_va = 0;
	m_cur_f1 = m_cur_f2 = m_cur_f2q = m_cur_f3 = 0;

	// Initialize the m_filt* values and the filter coefficients
	filters_commit(true);

	// Clear the rest of the internal digital state
	m_pitch = 0;
	m_closure = 0;
	m_update_counter = 0;
	m_cur_closure = true;
	m_noise = 0;
	m_cur_noise = false;

	// Clear the analog level histories
	memset(m_voice_1, 0, sizeof(m_voice_1));
	memset(m_voice_2, 0, sizeof(m_voice_2));
	memset(m_voice_3, 0, sizeof(m_voice_3));

	memset(m_noise_1, 0, sizeof(m_noise_1));
	memset(m_noise_2, 0, sizeof(m_noise_2));
	memset(m_noise_3, 0, sizeof(m_noise_3));
	memset(m_noise_4, 0, sizeof(m_noise_4));

	memset(m_vn_1, 0, sizeof(m_vn_1));
	memset(m_vn_2, 0, sizeof(m_vn_2));
	memset(m_vn_3, 0, sizeof(m_vn_3));
	memset(m_vn_4, 0, sizeof(m_vn_4));
	memset(m_vn_5, 0, sizeof(m_vn_5));
	memset(m_vn_6, 0, sizeof(m_vn_6));
}


//-------------------------------------------------
//  device_clock_changed - handle dynamic clock
//  changes by altering our output frequency
//-------------------------------------------------

void votrax_sc01_device::device_clock_changed()
{
	// lookup the new frequency of the master clock, and update if changed
	u32 newfreq = clock();
	if(newfreq != m_mainclock) {
		m_stream->update();

		if(!m_timer->expire().is_never()) {
			// determine how many clock ticks remained on the timer
			u64 remaining = m_timer->remaining().as_ticks(m_mainclock);

			// adjust the timer to the same number of ticks based on the new frequency
			m_timer->adjust(attotime::from_ticks(remaining, newfreq));
		}
		m_mainclock = newfreq;
		m_sclock = m_mainclock / 18.0;
		m_cclock = m_mainclock / 36.0;
		m_stream->set_sample_rate(m_sclock);
		filters_commit(true);
	}
}


//-------------------------------------------------
//  device_timer - handle device timer
//-------------------------------------------------

void votrax_sc01_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	m_stream->update();

	switch(param) {
	case T_COMMIT_PHONE:
		// strobe -> commit transition,
		phone_commit();
		m_timer->adjust(attotime::from_ticks(16*(m_rom_duration*4+1)*4*9+2, m_mainclock), T_END_OF_PHONE);
		break;

	case T_END_OF_PHONE:
		// end of phone
		m_ar_state = ASSERT_LINE;
		break;
	}

	m_ar_cb(m_ar_state);
}

void votrax_sc01_device::phone_commit()
{
	// Only these two counters are reset on phone change, the rest is
	// free-running.
	m_phonetick = 0;
	m_ticks = 0;

	// In the real chip, the rom is re-read all the time.  Since it's
	// internal and immutable, no point in not caching it though.
	for(int i=0; i<64; i++) {
		u64 val = reinterpret_cast<const u64 *>(m_rom->base())[i];
		if(m_phone == ((val >> 56) & 0x3f)) {
			m_rom_f1  = bitswap(val,  0,  7, 14, 21);
			m_rom_va  = bitswap(val,  1,  8, 15, 22);
			m_rom_f2  = bitswap(val,  2,  9, 16, 23);
			m_rom_fc  = bitswap(val,  3, 10, 17, 24);
			m_rom_f2q = bitswap(val,  4, 11, 18, 25);
			m_rom_f3  = bitswap(val,  5, 12, 19, 26);
			m_rom_fa  = bitswap(val,  6, 13, 20, 27);

			// These two values have their bit orders inverted
			// compared to everything else due to a bug in the
			// prototype (miswiring of the comparator with the ticks
			// count) they compensated in the rom.

			m_rom_cld = bitswap(val, 34, 32, 30, 28);
			m_rom_vd  = bitswap(val, 35, 33, 31, 29);

			m_rom_closure  = bitswap(val, 36);
			m_rom_duration = bitswap(~val, 37, 38, 39, 40, 41, 42, 43);

			// Hard-wired on the die, not an actual part of the rom.
			m_rom_pause = (m_phone == 0x03) || (m_phone == 0x3e);

			if(0)
				logerror("commit fa=%x va=%x fc=%x f1=%x f2=%x f2q=%x f3=%x dur=%02x cld=%x vd=%d cl=%d pause=%d\n", m_rom_fa, m_rom_va, m_rom_fc, m_rom_f1, m_rom_f2, m_rom_f2q, m_rom_f3, m_rom_duration, m_rom_cld, m_rom_vd, m_rom_closure, m_rom_pause);

			// That does not happen in the sc01(a) rom, but let's
			// cover our behind.
			if(m_rom_cld == 0)
				m_cur_closure = m_rom_closure;

			return;
		}
	}
}

void votrax_sc01_device::interpolate(u8 &reg, u8 target)
{
	// One step of interpolation, adds one eight of the distance
	// between the current value and the target.
	reg = reg - (reg >> 3) + (target << 1);
}

void votrax_sc01_device::chip_update()
{
	// Phone tick counter update.  Stopped when ticks reach 16.
	// Technically the counter keeps updating, but the comparator is
	// disabled.
	if(m_ticks != 0x10) {
		m_phonetick++;
		// Comparator is with duration << 2, but there's a one-tick
		// delay in the path.
		if(m_phonetick == ((m_rom_duration << 2) | 1)) {
			m_phonetick = 0;
			m_ticks++;
			if(m_ticks == m_rom_cld)
				m_cur_closure = m_rom_closure;
		}
	}

	// The two update timing counters.  One divides by 16, the other
	// by 48, and they're phased so that the 208Hz counter ticks
	// exactly between two 625Hz ticks.
	m_update_counter++;
	if(m_update_counter == 0x30)
		m_update_counter = 0;

	bool tick_625 = !(m_update_counter & 0xf);
	bool tick_208 = m_update_counter == 0x28;

	// Formant update.  Die bug there: fc should be updated, not va.
	// The formants are frozen on a pause phone unless both voice and
	// noise volumes are zero.
	if(tick_208 && (!m_rom_pause || !(m_filt_fa || m_filt_va))) {
		//      interpolate(m_cur_va,  m_rom_va);
		interpolate(m_cur_fc,  m_rom_fc);
		interpolate(m_cur_f1,  m_rom_f1);
		interpolate(m_cur_f2,  m_rom_f2);
		interpolate(m_cur_f2q, m_rom_f2q);
		interpolate(m_cur_f3,  m_rom_f3);
		//      logerror("int fa=%x va=%x fc=%x f1=%x f2=%02x f2q=%02x f3=%x\n", m_cur_fa >> 4, m_cur_va >> 4, m_cur_fc >> 4, m_cur_f1 >> 4, m_cur_f2 >> 3, m_cur_f2q >> 4, m_cur_f3 >> 4);
	}

	// Non-formant update. Same bug there, va should be updated, not fc.
	if(tick_625) {
		if(m_ticks >= m_rom_vd)
			interpolate(m_cur_fa, m_rom_fa);
		if(m_ticks >= m_rom_cld)
			//          interpolate(m_cur_fc, m_rom_fc);
			interpolate(m_cur_va, m_rom_va);
		//      logerror("int fa=%x va=%x fc=%x f1=%x f2=%02x f2q=%02x f3=%x\n", m_cur_fa >> 4, m_cur_va >> 4, m_cur_fc >> 4, m_cur_f1 >> 4, m_cur_f2 >> 3, m_cur_f2q >> 4, m_cur_f3 >> 4);
	}

	// Closure counter, reset every other tick in theory when not
	// active (on the extra rom cycle).
	//
	// The closure level is immediatly used in the analog path,
	// there's no pitch synchronization.

	if(!m_cur_closure && (m_filt_fa || m_filt_va))
		m_closure = 0;
	else if(m_closure != 7 << 2)
		m_closure ++;

	// Pitch counter.  Equality comparison, so it's possible to make
	// it miss by manipulating the inflection inputs, but it'll wrap.
	// There's a delay, hence the +1.
	m_pitch = (m_pitch + 1) & 0x7f;
	if(m_pitch == (0x7f ^ (m_inflection << 4) ^ m_filt_f1) + 1)
		m_pitch = 0;

	// Filters are updated in index 1 of the pitch wave, which does
	// indeed mean four times in a row.
	if((m_pitch >> 2) == 1)
		filters_commit(false);

	// Noise shift register.  15 bits, with a nxor on the last two
	// bits for the loop.
	bool inp = (1||m_filt_fa) && m_cur_noise && (m_noise != 0x7fff);
	m_noise = ((m_noise << 1) & 0x7ffe) | inp;
	m_cur_noise = !(((m_noise >> 14) ^ (m_noise >> 13)) & 1);

	//  logerror("tick %02x.%03x 625=%d 208=%d pitch=%02x.%x ns=%04x ni=%d noise=%d cl=%x.%x clf=%d/%d\n", m_ticks, m_phonetick, tick_625, tick_208, m_pitch >> 2, m_pitch & 3, m_noise, inp, m_cur_noise, m_closure >> 2, m_closure & 3, m_rom_closure, m_cur_closure);
}

void votrax_sc01_device::filters_commit(bool force)
{
	m_filt_fa = m_cur_fa >> 4;
	m_filt_fc = m_cur_fc >> 4;
	m_filt_va = m_cur_va >> 4;

	if(force || m_filt_f1 != m_cur_f1 >> 4) {
		m_filt_f1 = m_cur_f1 >> 4;

		build_standard_filter(m_f1_a, m_f1_b,
							  11247,
							  11797,
							  949,
							  52067,
							  2280 + bits_to_caps(m_filt_f1, { 2546, 4973, 9861, 19724 }),
							  166272);
	}

	if(force || m_filt_f2 != m_cur_f2 >> 3 || m_filt_f2q != m_cur_f2q >> 4) {
		m_filt_f2 = m_cur_f2 >> 3;
		m_filt_f2q = m_cur_f2q >> 4;

		build_standard_filter(m_f2v_a, m_f2v_b,
							  24840,
							  29154,
							  829 + bits_to_caps(m_filt_f2q, { 1390, 2965, 5875, 11297 }),
							  38180,
							  2352 + bits_to_caps(m_filt_f2, { 833, 1663, 3164, 6327, 12654 }),
							  34270);

		build_injection_filter(m_f2n_a, m_f2n_b,
							   29154,
							   829 + bits_to_caps(m_filt_f2q, { 1390, 2965, 5875, 11297 }),
							   38180,
							   2352 + bits_to_caps(m_filt_f2, { 833, 1663, 3164, 6327, 12654 }),
							   34270);
	}

	if(force || m_filt_f3 != m_cur_f3 >> 4) {
		m_filt_f3 = m_cur_f3 >> 4;
		build_standard_filter(m_f3_a, m_f3_b,
							  0,
							  17594,
							  868,
							  18828,
							  8480 + bits_to_caps(m_filt_f3, { 2226, 4485, 9056, 18111 }),
							  50019);
	}

	if(force) {
		build_standard_filter(m_f4_a, m_f4_b,
							  0,
							  28810,
							  1165,
							  21457,
							  8558,
							  7289);

		build_lowpass_filter(m_fx_a, m_fx_b,
							 1122,
							 23131);

		build_noise_shaper_filter(m_fn_a, m_fn_b,
								  15500,
								  14854,
								  8450,
								  9523,
								  14083);
	}

	if(0)
		if(m_filt_fa || m_filt_va || m_filt_fc || m_filt_f1 || m_filt_f2 || m_filt_f2q || m_filt_f3)
			logerror("filter fa=%x va=%x fc=%x f1=%x f2=%02x f2q=%x f3=%x\n",
					 m_filt_fa, m_filt_va, m_filt_fc, m_filt_f1, m_filt_f2, m_filt_f2q, m_filt_f3);
}

stream_sample_t votrax_sc01_device::analog_calc()
{
	// Voice-only path.
	// 1. Pick up the pitch wave

	double v = m_pitch >= (9 << 2) ? 0 : s_glottal_wave[m_pitch >> 2];

	// 2. Multiply by the initial amplifier.  It's linear on the die,
	// even if it's not in the patent.
	v = v * m_filt_va / 15.0;
	shift_hist(v, m_voice_1);

	// 3. Apply the f1 filter
	v = apply_filter(m_voice_1, m_voice_2, m_f1_a, m_f1_b);
	shift_hist(v, m_voice_2);

	// 4. Apply the f2 filter, voice half
	v = apply_filter(m_voice_2, m_voice_3, m_f2v_a, m_f2v_b);
	shift_hist(v, m_voice_3);

	// Noise-only path
	// 5. Pick up the noise pitch.  Amplitude is linear.  Base
	// intensity should be checked w.r.t the voice.
	double n = 1e4 * ((m_pitch & 0x40 ? m_cur_noise : false) ? 1 : -1);
	n = n * m_filt_fa / 15.0;
	shift_hist(n, m_noise_1);

	// 6. Apply the noise shaper
	n = apply_filter(m_noise_1, m_noise_2, m_fn_a, m_fn_b);
	shift_hist(n, m_noise_2);

	// 7. Scale with the f2 noise input
	double n2 = n * m_filt_fc / 15.0;
	shift_hist(n2, m_noise_3);

	// 8. Apply the f2 filter, noise half,
	n2 = apply_filter(m_noise_3, m_noise_4, m_f2n_a, m_f2n_b);
	shift_hist(n2, m_noise_4);

	// Mixed path
	// 9. Add the f2 voice and f2 noise outputs
	double vn = v + n2;
	shift_hist(vn, m_vn_1);

	// 10. Apply the f3 filter
	vn = apply_filter(m_vn_1, m_vn_2, m_f3_a, m_f3_b);
	shift_hist(vn, m_vn_2);

	// 11. Second noise insertion
	vn += n * (5 + (15^m_filt_fc))/20.0;
	shift_hist(vn, m_vn_3);

	// 12. Apply the f4 filter
	vn = apply_filter(m_vn_3, m_vn_4, m_f4_a, m_f4_b);
	shift_hist(vn, m_vn_4);

	// 13. Apply the glottal closure amplitude, also linear
	vn = vn * (7 ^ (m_cur_closure >> 2)) / 7.0;
	shift_hist(vn, m_vn_5);

	// 13. Apply the final fixed filter
	vn = apply_filter(m_vn_5, m_vn_6, m_fx_a, m_fx_b);
	shift_hist(vn, m_vn_6);

	return int(vn*50000);
>>>>>>> upstream/master
}

/*
  Playing with analog filters, or where all the magic filter formulas are coming from.

  First you start with an analog circuit, for instance this one:

  |                     +--[R2]--+
  |                     |        |
  |                     +--|C2|--+<V1     +--|C3|--+
  |                     |        |        |        |
  |  Vi   +--[R1]--+    |  |\    |        |  |\    |
  |  -----+        +----+--+-\   |        +--+-\   |
  |       +--|C1|--+       |  >--+--[Rx]--+  |  >--+----- Vo
  |                |     0-++/             0-++/   |
  |                |       |/    +--[R0]--+  |/    |
  |                |             |        |        |
  |                |             |    /|  |        |
  |                |             |   /-+--+--[R0]--+
  |                +--[R4]-------+--<  |
  |                            V2^   \++-0
  |                                   \|

<<<<<<< HEAD
=======
  It happens to be what most of the filters in the sc01a look like.

>>>>>>> upstream/master
  You need to determine the transfer function H(s) of the circuit, which is
  defined as the ratio Vo/Vi.  To do that, you use some properties:

  - The intensity through an element is equal to the voltage
    difference through the element divided by the impedence

  - The impedence of a resistance is equal to its resistance

  - The impedence of a capacitor is 1/(s*C) where C is its capacitance

  - The impedence of elements in series is the sum of the impedences

  - The impedence of elements in parallel is the inverse of the sum of
    the inverses

  - The sum of all intensities flowing into a node is 0 (there's no
    charge accumulation in a wire)

  - An operational amplifier in looped mode is an interesting beast:
    the intensity at its two inputs is always 0, and the voltage is
    forced identical between the inputs.  In our case, since the '+'
    inputs are all tied to ground, that means that the '-' inputs are at
    voltage 0, intensity 0.

  From here we can build some equations.  Noting:
  X1 = 1/(1/R1 + s*C1)
  X2 = 1/(1/R2 + s*C2)
  X3 = 1/(s*C3)

  Then computing the intensity flow at each '-' input we have:
  Vi/X1 + V2/R4 + V1/X2 = 0
  V2/R0 + Vo/R0 = 0
  V1/Rx + Vo/X3 = 0

  Wrangling the equations, one eventually gets:
  |                            1 + s * C1*R1
  | Vo/Vi = H(s) = (R4/R1) * -------------------------------------------
  |                            1 + s * C3*Rx*R4/R2 + s^2 * C2*C3*Rx*R4

  To check the mathematics between the 's' stuff, check "Laplace
  transform".  In short, it's a nice way of manipulating derivatives
  and integrals without having to manipulate derivatives and
  integrals.

  With that transfer function, we first can compute what happens to
  every frequency in the input signal.  You just compute H(2i*pi*f)
  where f is the frequency, which will give you a complex number
  representing the amplitude and phase effect.  To get the usual dB
  curves, compute 20*log10(abs(v))).

  Now, once you have an analog transfer function, you can build a
  digital filter from it using what is called the bilinear transform.

  In our case, we have an analog filter with the transfer function:
  |                 1 + k[0]*s
  |        H(s) = -------------------------
  |                 1 + k[1]*s + k[2]*s^2

  We can always reintroduce the global multipler later, and it's 1 in
  most of our cases anyway.

  The we pose:
  |                    z-1
  |        s(z) = zc * ---
  |                    z+1

  where zc = 2*pi*fr/tan(pi*fr/fs)
  with fs = sampling frequency
  and fr = most interesting frequency

  Then we rewrite H in function of negative integer powers of z.

  Noting m0 = zc*k[0], m1 = zc*k[1], m2=zc*zc*k[2],

  a little equation wrangling then gives:

  |                 (1+m0)    + (3+m0)   *z^-1 + (3-m0)   *z^-2 +    (1-m0)*z^-3
  |        H(z) = ----------------------------------------------------------------
  |                 (1+m1+m2) + (3+m1-m2)*z^-1 + (3-m1-m2)*z^-2 + (1-m1+m2)*z^-3

  That beast in the digital transfer function, of which you can
  extract response curves by posing z = exp(2*i*pi*f/fs).

  Note that the bilinear transform is an approximation, and H(z(f)) =
  H(s(f)) only at frequency fr.  And the shape of the filter will be
  better respected around fr.  If you look at the curves of the
  filters we're interested in, the frequency:
  fr = sqrt(abs(k[0]*k[1]-k[2]))/(2*pi*k[2])

  which is a (good) approximation of the filter peak position is a
  good choice.

  Note that terminology wise, the "standard" bilinear transform is
  with fr = fs/2, and using a different fr is called "pre-warping".

  So now we have a digital transfer function of the generic form:

  |                 a[0] + a[1]*z^-1 + a[2]*z^-2 + a[3]*z^-3
  |        H(z) = --------------------------------------------
  |                 b[0] + b[1]*z^-1 + b[2]*z^-2 + b[3]*z^-3

  The magic then is that the powers of z represent time in samples.
  Noting x the input stream and y the output stream, you have:
  H(z) = y(z)/x(z)

  or in other words:
  y*b[0]*z^0 + y*b[1]*z^-1 + y*b[2]*z^-2 + y*b[3]*z^-3 = x*a[0]*z^0 + x*a[1]*z^-1 + x*a[2]*z^-2 + x*a[3]*z^-3

  i.e.

  y*z^0 = (x*a[0]*z^0 + x*a[1]*z^-1 + x*a[2]*z^-2 + x*a[3]*z^-3 - y*b[1]*z^-1 - y*b[2]*z^-2 - y*b[3]*z^-3) / b[0]

  and powers of z being time in samples,

  y[0] = (x[0]*a[0] + x[-1]*a[1] + x[-2]*a[2] + x[-3]*a[3] - y[-1]*b[1] - y[-2]*b[2] - y[-3]*b[3]) / b[0]

  So you have a filter you can apply.  Note that this is why you want
  negative powers of z.  Positive powers would mean looking into the
  future (which is possible in some cases, in particular with x, and
  has some very interesting properties, but is not very useful in
  analog circuit simulation).

  Note that if you have multiple inputs, all this stuff is linear.
  Or, in other words, you just have to split it in multiple circuits
  with only one input connected each time and sum the results.  It
  will be correct.

  Also, since we're in practice in a dynamic system, for an amplifying
  filter (i.e. where things like r4/r1 is not 1), it's better to
  proceed in two steps:

  - amplify the input by the current value of the coefficient, and
    historize it
  - apply the now non-amplifying filter to the historized amplified
    input

<<<<<<< HEAD
  That way reduces the probability of the output boucing all over the
  place.

*/


//-------------------------------------------------------------
//  filter_s_to_z - analog to digital filter transformation
//-------------------------------------------------------------

void votrax_sc01_device::filter_s_to_z(const double *k, double fs, double *a, double *b)
{
	double fpeak = sqrt(fabs(k[0]*k[1]-k[2]))/(2*M_PI*k[2]);
	double zc = 2*M_PI*fpeak/tan(M_PI*fpeak/fs);

	double m0 = zc*k[0];
	double m1 = zc*k[1];
	double m2 = zc*zc*k[2];
=======
  That way reduces the probability of the output bouncing all over the
  place.

  Except, we're not done yet.  Doing resistors precisely in an IC is
  very hard and/or expensive (you may have heard of "laser cut
  resistors" in DACs of the time).  Doing capacitors is easier, and
  their value is proportional to their surface.  So there are no
  resistors on the sc01 die (which is a lie, there are three, but not
  in the filter path.  They are used to scale the voltage in the pitch
  wave and to generate +5V from the +9V), but a magic thing called a
  switched capacitor.  Lookup patent 4,433,210 for details.  Using
  high frequency switching a capacitor can be turned into a resistor
  of value 1/(C*f) where f is the switching frequency (20Khz,
  main/36).  And the circuit is such that the absolute value of the
  capacitors is irrelevant, only their ratio is useful, which factors
  out the intrinsic capacity-per-surface-area of the IC which may be
  hard to keep stable from one die to another.  As a result all the
  capacitor values we use are actually surfaces in square micrometers.

  For the curious, it looks like the actual capacitance was around 25
  femtofarad per square micrometer.

*/

void votrax_sc01_device::build_standard_filter(double *a, double *b,
											   double c1t, // Unswitched cap, input, top
											   double c1b, // Switched cap, input, bottom
											   double c2t, // Unswitched cap, over first amp-op, top
											   double c2b, // Switched cap, over first amp-op, bottom
											   double c3,  // Cap between the two op-amps
											   double c4)  // Cap over second op-amp
{
	// First compute the three coefficients of H(s).  One can note
	// that there is as many capacitor values on both sides of the
	// division, which confirms that the capacity-per-surface-area
	// is not needed.
	double k0 = c1t / (m_cclock * c1b);
	double k1 = c4 * c2t / (m_cclock * c1b * c3);
	double k2 = c4 * c2b / (m_cclock * m_cclock * c1b * c3);

	// Estimate the filter cutoff frequency
	double fpeak = sqrt(fabs(k0*k1 - k2))/(2*M_PI*k2);

	// Turn that into a warp multiplier
	double zc = 2*M_PI*fpeak/tan(M_PI*fpeak / m_sclock);

	// Finally compute the result of the z-transform
	double m0 = zc*k0;
	double m1 = zc*k1;
	double m2 = zc*zc*k2;
>>>>>>> upstream/master

	a[0] = 1+m0;
	a[1] = 3+m0;
	a[2] = 3-m0;
	a[3] = 1-m0;
	b[0] = 1+m1+m2;
	b[1] = 3+m1-m2;
	b[2] = 3-m1-m2;
	b[3] = 1-m1+m2;
}

<<<<<<< HEAD

//-------------------------------------------------------------
//  apply_filter - apply the digital filter (before output
//                 shifting, so y[0] is one step in the past)
//-------------------------------------------------------------
double votrax_sc01_device::apply_filter(const double *x, const double *y, const double *a, const double *b)
{
	return (x[0]*a[0] + x[1]*a[1] + x[2]*a[2] + x[3]*a[3] - y[0]*b[1] - y[1]*b[2] - y[2]*b[3]) / b[0];
}


//-------------------------------------------------------------
//  shift_hist - shift a value in an output history
//-------------------------------------------------------------

void votrax_sc01_device::shift_hist(double val, double *hist_array, int hist_size)
{
	for(int i = 0; i < hist_size-1; i++)
		hist_array[hist_size-1-i] = hist_array[hist_size-2-i];
	hist_array[0] = val;
}


//-------------------------------------------------
//  sound_stream_update - handle update requests
//  for our sound stream
//-------------------------------------------------

void votrax_sc01_device::sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples)
{
	// determine how many master half-clocks per sample
	int half_clocks_per_sample = (m_master_clock_freq * 2) / stream.sample_rate();

	// iterate over clocks (samples)
	stream_sample_t *dest = outputs[0];
	while (samples--)
	{
		// run the digital logic at the master clock rate
		double glottal_out = 0;
		UINT8 noise_out_digital = 0;
		for (int curclock = 0; curclock < half_clocks_per_sample; curclock++)
		{
if (LOG_TIMING | LOG_LOWPARAM | LOG_GLOTTAL | LOG_TRANSITION)
{
	if (m_counter_34 % 32 == 0 && m_master_clock == 0)
	{
	if (LOG_TIMING)
		osd_printf_debug("MCLK C034 L070 L072 BET1  P1   P2  PHI1 PHI2 PH1' PH2' SUBC C088 C084 L092 IIRQ ");
	if (LOG_LOWPARAM)
		osd_printf_debug("F132 F114 F112 F142 L080 ");
	if (LOG_GLOTTAL)
		osd_printf_debug("C220 C222 C224 C234 C236 FGAT GLSY ");
	if (LOG_TRANSITION)
		osd_printf_debug("0625 C046 L046 A0-2 L168 L170  FC   VA   FA   F1   F2   F3   F2Q ");
	osd_printf_debug("\n");
	}
	if (LOG_TIMING)
		osd_printf_debug("%4X %4X %4X %4X %4X %4X %4X %4X %4X %4X %4X %4X %4X %4X %4X %4X ", m_master_clock, m_counter_34, m_latch_70, m_latch_72, m_beta1, m_p1, m_p2, m_phi1, m_phi2, m_phi1_20, m_phi2_20, m_subphoneme_count, m_clock_88, m_counter_84, m_latch_92, m_internal_request);
	if (LOG_LOWPARAM)
		osd_printf_debug("%d %d %d %d %d ", m_srff_132, m_srff_114, m_srff_112, m_srff_142, m_latch_80);
	if (LOG_GLOTTAL)
		osd_printf_debug("%4X %4X %4X %4X %4X %4X %4X ", m_counter_220, m_counter_222, m_counter_224, m_counter_234, m_counter_236, m_fgate, m_glottal_sync);
	if (LOG_TRANSITION)
		osd_printf_debug("%4X %4X %4X %4X %4X %4X %4X %4X %4X %4X %4X %4X %4X ", m_0625_clock, m_counter_46, m_latch_46, m_latch_72 & 7, m_latch_168, m_latch_170, m_fc, m_va, m_fa, m_f1, m_f2, m_f3, m_f2q);
	osd_printf_debug("\n");
}

			//==============================================
			//
			// Timing circuit (patent figure 2a)
			//
			//==============================================

			// update master clock
			m_master_clock ^= 1;

			// on the falling edge of the master clock, advance the 10-bit counter at 34
			UINT8 old_latch_72 = m_latch_72;
			if (m_master_clock == 0)
				m_counter_34 = (m_counter_34 + 1) & 0x3ff;
			else
			{
				m_latch_70 = m_counter_34 & 0xf;
				m_latch_72 = ((m_counter_34 >> 4) & 7) | ((m_counter_34 >> 6) & 8);
			}

			// derive beta 1 clock:
			//  set if m_latch_70.0 == 1
			//  reset if m_latch_70.0 == 0
//          UINT8 old_beta1 = m_beta1;
			m_beta1 = BIT(m_latch_70, 0);

			// derive p2 clock:
			//  set if (m_counter_34.P_CLOCK_BIT & clock) == 1
			//  reset if (m_counter_34.P_CLOCK_BIT == 0)
			UINT8 old_p2 = m_p2;
			if (BIT(m_counter_34, P_CLOCK_BIT) & m_master_clock)
				m_p2 = 1;
			else if (!BIT(m_counter_34, P_CLOCK_BIT))
				m_p2 = 0;

			// derive p1 clock:
			//  set if (!m_counter_34.P_CLOCK_BIT & clock) == 1
			//  reset if (m_counter_34.P_CLOCK_BIT == 1)
//          UINT8 old_p1 = m_p1;
			if (BIT(~m_counter_34, P_CLOCK_BIT) & m_master_clock)
				m_p1 = 1;
			else if (BIT(m_counter_34, P_CLOCK_BIT))
				m_p1 = 0;

			// derive phi2 clock:
			//  set if (m_counter_34.PHI_CLOCK_BIT & clock) == 1
			//  reset if (m_counter_34.PHI_CLOCK_BIT == 0)
			UINT8 old_phi2 = m_phi2;
			if (BIT(m_counter_34, PHI_CLOCK_BIT) & m_master_clock)
				m_phi2 = 1;
			else if (!BIT(m_counter_34, PHI_CLOCK_BIT))
				m_phi2 = 0;

			// derive phi1 clock:
			//  set if (!m_counter_34.PHI_CLOCK_BIT & clock) == 1
			//  reset if (m_counter_34.PHI_CLOCK_BIT == 1)
			UINT8 old_phi1 = m_phi1;
			if (BIT(~m_counter_34, PHI_CLOCK_BIT) & m_master_clock)
				m_phi1 = 1;
			else if (BIT(m_counter_34, PHI_CLOCK_BIT))
				m_phi1 = 0;

			// derive alternate phi2 clock:
			//  set if (m_counter_34.PHI_CLOCK_BIT & clock) == 1
			//  reset if (m_counter_34.PHI_CLOCK_BIT == 0)
			UINT8 old_phi2_20 = m_phi2_20;
			if (BIT(m_counter_34, PHI_CLOCK_BIT + 2) & m_master_clock)
				m_phi2_20 = 1;
			else if (!BIT(m_counter_34, PHI_CLOCK_BIT + 2))
				m_phi2_20 = 0;

			// derive alternate phi1 clock:
			//  set if (!m_counter_34.PHI_CLOCK_BIT & clock) == 1
			//  reset if (m_counter_34.PHI_CLOCK_BIT == 1)
//          UINT8 old_phi1_20 = m_phi1_20;
			if (BIT(~m_counter_34, PHI_CLOCK_BIT + 2) & m_master_clock)
				m_phi1_20 = 1;
			else if (BIT(m_counter_34, PHI_CLOCK_BIT + 2))
				m_phi1_20 = 0;

			// determine rising edges of each clock of interest
//          UINT8 beta1_rising = (old_beta1 ^ m_beta1) & m_beta1;
			UINT8 p2_rising = (old_p2 ^ m_p2) & m_p2;
//          UINT8 p1_rising = (old_p1 ^ m_p1) & m_p1;
			UINT8 phi2_rising = (old_phi2 ^ m_phi2) & m_phi2;
			UINT8 phi1_rising = (old_phi1 ^ m_phi1) & m_phi1;
			UINT8 phi2_20_rising = (old_phi2_20 ^ m_phi2_20) & m_phi2_20;
//          UINT8 phi1_20_rising = (old_phi1_20 ^ m_phi1_20) & m_phi1_20;
			UINT8 a0_rising = BIT((old_latch_72 ^ m_latch_72) & m_latch_72, 0);
			UINT8 a2_rising = BIT((old_latch_72 ^ m_latch_72) & m_latch_72, 2);
			UINT8 _125k_rising = BIT((old_latch_72 ^ m_latch_72) & m_latch_72, 3);

			// track subphoneme counter state
			if (!(m_latch_42 | m_phi1))
				m_subphoneme_count = 0;
			else
				m_subphoneme_count++;
			if (p2_rising)
				m_latch_42 = (m_subphoneme_count < m_subphoneme_period);

			// update the state of the subphoneme clock line
			UINT8 old_clock_88 = m_clock_88;
			m_clock_88 = !m_latch_42;   //!(m_latch_42 | m_phi1); -- figure 7 seems to be wrong here
			UINT8 clock_88_rising = (old_clock_88 ^ m_clock_88) & m_clock_88;

			// the A/R line holds the counter in reset except during phoneme processing,
			// when it is clocked on the rising edge of the subphoneme timer clock
			if (m_internal_request != CLEAR_LINE)
				m_counter_84 = 0xf;
			else if (clock_88_rising)
			{
				m_counter_84 = (m_counter_84 - 1) & 0x0f;
osd_printf_debug("counter=%d\n", m_counter_84);
			}

			// clock the zero count latch
			if (p2_rising)
				m_latch_92 = ((m_counter_84 == 0) | (m_latch_92 << 1)) & 3;

			// once both bits are set, the request line goes high
			if (m_latch_92 == 3)
			{
				// if the request line was previously low, reset the VD/CLD flip-flops
				if (m_internal_request == CLEAR_LINE)
				{
					m_srff_112 = m_srff_114 = false;
				}
				m_internal_request = ASSERT_LINE;
			}

			//==============================================
			//
			// Low parameter clocking (patent figure 2b)
			//
			//==============================================

			// fetch ROM data; note that the address lines come directly from
			// counter_34 and not from the latches, which are 1 cycle delayed
			UINT8 romdata = m_rom[(m_phoneme << 3) | ((m_counter_34 >> 4) & 7)];

			// update the ROM data; ROM format is (upper nibble/lower nibble)
			//  +00 = F1 parameter / 0
			//  +01 = F2 parameter / 0
			//  +02 = FC parameter / 0
			//  +03 = F3 parameter / CL
			//  +04 = F2Q Parameter / CLD
			//  +05 = VA Parameter / VD
			//  +06 = FA Parameter / PAC
			//  +07 = Phoneme timing (full 7 bits)

			// latch a new value from ROM on phi2
			UINT8 a = m_latch_72 & 7;
			UINT8 romdata_swapped;
			if (phi2_rising)
			{
				switch (a)
				{
					// update CL
					case 3:
						m_srff_132 = m_srff_114 && BIT(~romdata, 3);
						break;

					// update CLD
					case 4:
						romdata_swapped = (BIT(romdata, 0) << 3) | (BIT(romdata, 1) << 2) | (BIT(romdata, 2) << 1) | (BIT(romdata, 3) << 0);
						if (m_counter_84 != 0 && romdata_swapped == (m_counter_84 ^ 0xf))
						{
							m_srff_114 = true;
						}
						break;

					// update VD
					case 5:
						romdata_swapped = (BIT(romdata, 0) << 3) | (BIT(romdata, 1) << 2) | (BIT(romdata, 2) << 1) | (BIT(romdata, 3) << 0);
						if (m_counter_84 != 0 && romdata_swapped == (m_counter_84 ^ 0xf))
						{
							m_srff_112 = true;
						}
						break;

					// update FF == PAC & (VA | FA)
					case 6:
						m_srff_142 = BIT(romdata, 3);
						break;

					// update PH
					case 7:
						if (m_latch_80 != (romdata & 0x7f))
						{
							m_latch_80 = romdata & 0x7f;
osd_printf_debug("[PH=%02X]\n", m_latch_80);
							UINT32 old_period = m_subphoneme_period;
							update_subphoneme_clock_period();
							m_subphoneme_count = (m_subphoneme_count * m_subphoneme_period) / old_period;
							m_phoneme_timer->adjust(attotime::zero);
						}
						break;
				}
			}

			//==============================================
			//
			// Glottal circuit (patent figure 6)
			//
			//==============================================

			// determine the TC output from the counters (note that TC requires ET)
			UINT8 counter_222_tc = (m_counter_222 == 0xf);
			UINT8 counter_220_tc = (m_counter_220 == 0xf && counter_222_tc);
			UINT8 counter_224_tc = (m_counter_224 == 0xf && counter_222_tc);

			// clock glottal counter 224 on rising edge of a0
			if (a0_rising)
			{
				// counter 224 is only enabled if TC of counter 222 is 1
				if (counter_222_tc)
				{
					// if counter 220's TC is 1, do a load instead of a count
					if (counter_220_tc)
						m_counter_224 = (m_inflection << 1) | ((~m_f1 & 0x8) >> 3);
					else
						m_counter_224 = (m_counter_224 + 1) & 0xf;
				}
			}

			// clock remaining glottal counters (220, 222, 236) on rising edge of phi2
			if (phi2_20_rising)
			{
				// counter 220 is only enabled if TC of counter 222 is 1
				if (counter_222_tc)
				{
					// if counter 220's TC is 1, do a load instead of a count
					if (counter_220_tc)
						m_counter_220 = (m_inflection << 1) | ((~m_f1 & 0x8) >> 3);
					else
						m_counter_220 = (m_counter_220 + 1) & 0xf;
				}

				// counter 222 is always enabled
				if (1)
				{
					// if counter 220's TC is 1, do a load instead of a count
					if (counter_220_tc)
						m_counter_222 = (~m_f1 & 0x7) << 1;
					else
						m_counter_222 = (m_counter_222 + 1) & 0xf;
				}

				// counter 236 is always enabled
				if (1)
				{
					m_counter_236 = (m_counter_236 + 1) & 0xf;

					// rising edge of Q1 from counter 236 clocks counter 234
					if ((m_counter_236 & 0x3) == 0x2)
					{
						// counter 234 is only enabled if it has not reached terminal
						if (m_counter_234 != 0xf)
							m_counter_234 = (m_counter_234 + 1) & 0xf;
					}
				}
			}

			// update FGATE state
			if (counter_220_tc)
				m_fgate = 0;
			if (counter_224_tc)
				m_fgate = 1;

			// apply asynchronous clear to counters 234/236
			if (counter_220_tc && m_phi1_20)
				m_counter_236 = m_counter_234 = 0;

			// derive glottal circuit output signals
#if !TEMP_HACKS
			UINT8 old_glottal_sync = m_glottal_sync;
#endif
			m_glottal_sync = (m_counter_234 == 0);
			glottal_out = s_glottal_wave[m_counter_234];

			//==============================================
			//
			// Transition circuit (patent figure 3a/3b)
			//
			//==============================================

			// divide 1.25k clock by 2 (lower-left of 46)
			UINT8 old_0625_clock = m_0625_clock;
			if (_125k_rising)
				m_0625_clock = !m_0625_clock;
			UINT8 _0625_rising = (old_0625_clock ^ m_0625_clock) & m_0625_clock;

			// update counter above
			if (_0625_rising)
			{
				if (m_counter_46 == 0xf)
					m_counter_46 = 0xd;
				else
					m_counter_46 = (m_counter_46 + 1) & 0xf;
			}

			// and then the latch to the right
			if (a2_rising)
				m_latch_46 = (BIT(m_counter_46, 1) << 0) |
								(BIT(m_latch_46, 0) << 1) |
								(m_0625_clock << 2) |
								(BIT(m_latch_46, 2) << 3);

#if TEMP_HACKS
			m_latch_46 = 0xf;
#endif

			// determine the read/write signal
			UINT8 ram_write = 0;
			switch (a)
			{
				// write if not FF and low 2 bits of latch
				// FF is the S/R flip-flop at 142 ANDed with !(/FA & /VA)
				case 0: case 1: case 2: case 3: case 4:
					if ((m_srff_142 && !((m_fa == 0) && (m_va == 0))) == 0 && (m_latch_46 & 0x3) == 0x3)
						ram_write = 1;
					break;

				case 5:
					if ((m_latch_46 & 0xc) == 0xc && m_srff_112)
					{
						ram_write = 1;
					}
					break;

				case 6:
					if ((m_latch_46 & 0xc) == 0xc && m_srff_114)
					{
						ram_write = 1;
					}
					break;
			}

			// gate on the phi2 clock (OR gate @ 172)
			ram_write &= m_phi2;

			// write the transitioned values to RAM if requested
			// (note we consolidate the serial addition and clocking steps here)
			if (ram_write)
			{
				UINT8 old = (m_latch_168 << 4) | m_latch_170;
				m_ram[a] = old - (old >> 3) + ((romdata & 0xf0) >> 3);
			}

			// latch some parameter values on rising edge of phi2
			if (phi2_rising)
			{
				switch (a)
				{
					case 2:
						m_fc = m_latch_168;
						break;

					case 5:
						m_va = m_latch_168;
						break;

					case 6:
						m_fa = m_latch_168;
						break;
				}
			}

			// latch remaining parameter values on rising edge of (phi2 & glottal sync)
#if TEMP_HACKS
			if (phi2_rising)
#else
			UINT8 old_phi2_glottal = (old_phi2 & old_glottal_sync);
			UINT8 new_phi2_glottal = m_phi2 & m_glottal_sync;
			if ((old_phi2_glottal ^ new_phi2_glottal) & new_phi2_glottal)
#endif
				switch (a)
				{
					case 0:
						m_f1 = m_latch_168;
						break;

					case 1:
						m_f2 = (m_latch_168 << 1) | (m_latch_170 >> 3);
						break;

					case 3:
						m_f3 = m_latch_168;
						break;

					case 4:
						m_f2q = m_latch_168;
						break;
				}

			// latch value from RAM on rising edge of phi1
			if (phi1_rising)
			{
				m_latch_168 = m_ram[a] >> 4;
				m_latch_170 = m_ram[a] & 0xf;
			}

			//==============================================
			//
			// Noise generator circuit (patent figure 8)
			//
			//==============================================

			// nose is clocked by the NOR of /FA and P1
			UINT8 old_noise_clock = m_noise_clock;
			m_noise_clock = !((m_fa == 0) | m_p1);
			UINT8 noise_clock_rising = (old_noise_clock ^ m_noise_clock) & m_noise_clock;
			UINT8 noise_clock_falling = (old_noise_clock ^ m_noise_clock) & old_noise_clock;

			// falling edge clocks the shift register
			if (noise_clock_falling)
			{
				// shift register 252 is actually 4 shift registers (2 4-bit, 2 5-bit)
				// d1 and d3 are the 4-bit registers, d2 and d4 are the 5-bit registers
				// XOR'ed input goes into d4, which shifts in to d2, then d3, then d1
				// thus the full 18-bit value is effectively
				//
				//  d4 = (m_shift_252 >> 0) & 0x1f;
				//  d2 = (m_shift_252 >> 5) & 0x1f;
				//  d3 = (m_shift_252 >> 10) & 0xf;
				//  d1 = (m_shift_252 >> 14) & 0xf;
				//
				// input at the low end is ((d1+4 ^ d2+5) ^ (d4+4 ^ d4+5)) ^ !(counter2 | counter3)
				// output is tapped at d3+4

				UINT32 old_shift = m_shift_252;
				m_shift_252 <<= 1;
				m_shift_252 |= ((BIT(old_shift, 17) ^ BIT(old_shift, 9)) ^ (BIT(old_shift, 3) ^ BIT(old_shift, 4))) ^
									((m_counter_250 & 0xc) == 0);
			}

			// rising edge clocks the counter
			if (noise_clock_rising)
			{
				// counter is reset to 1 if terminal, otherwise it increments
				if (m_counter_250 == 0xf)
					m_counter_250 = 0x1;
				else
					m_counter_250 = (m_counter_250 + 1) & 0xf;
			}

			// compute final noise out signal
			noise_out_digital = !(BIT(m_shift_252, 13) & (m_fgate | (m_va == 0)));
		}

		// TODO: cache the filters
		// filter coefs
		double k[3], a[4], b[4];

		// base frequencies
		double fc = m_master_clock_freq / 30.0; // Nominal is 20KHz
		double fs = stream.sample_rate();

		// useful temporaries
		double rcp, rcq, rca;

		// amplification stage
		static const double va_caps[4] = { 27, 53, 107, 213 };
		double va_out = glottal_out * bits_to_caps(m_va, 4, va_caps) / 400;

		shift_hist(va_out, m_va_hist, 4);


		// noise shaping
		static const double fa_caps[4] = { 27, 53, 107, 213 };
		rcp = bits_to_caps(m_fa,  4, fa_caps);

		shift_hist(-noise_out_digital * 400*rcp/(358.0*100000*566*(fc*rcp*1e-12 + 1.0/100000 + 1.0/2000)), m_ni_hist, 4);

		k[0] = 400/(fc*358);
		k[1] = 400*400/(fc*358*566);
		k[2] = 400*400/(fc*fc*358*358);

		filter_s_to_z(k, fs, a, b);
		double no_out = apply_filter(m_ni_hist, m_no_hist, a, b);
		shift_hist(no_out, m_no_hist, 4);


		// stage 1 filter

		static const double s1_p_caps[4] = { 16.4, 33, 66, 130 };
		rcp = 24 + bits_to_caps(m_f1, 4, s1_p_caps);
		rcq = 20;

		k[0] = 253/(fc*270);
		k[1] = 1080*rcq/(fc*270*rcp);
		k[2] = 1080*1080/(fc*fc*270*rcp);

		filter_s_to_z(k, fs, a, b);
		double s1_out = apply_filter(m_va_hist, m_s1_hist, a, b);
		shift_hist(s1_out, m_s1_hist, 4);


		// stage 2 filter, glottal half

		static const double s2_p_caps[5] = { 14, 28, 56, 113, 226 };
		static const double s2_q_caps[4] = { 23, 46, 93, 186 };
		rcp = 46 + bits_to_caps(m_f2,  5, s2_p_caps);
		rcq = 20 + bits_to_caps(m_f2q, 4, s2_q_caps);;

		k[0] = 400/(fc*470);
		k[1] = 620*rcq/(fc*470*rcp);
		k[2] = 620*620/(fc*fc*470*rcp);

		filter_s_to_z(k, fs, a, b);
		double s2g_out = apply_filter(m_s1_hist, m_s2g_hist, a, b);
		shift_hist(s2g_out, m_s2g_hist, 4);


		// stage 2 filter, noise half (rcp and rcq kept from stage 2 glottal)

		static const double s2_n_caps[5] = { 19, 38, 76, 152 };
		rca = bits_to_caps(m_fc, 4, s2_n_caps);

		shift_hist(-no_out*rcq*rca/(470*rcp), m_s2ni_hist, 4);

		k[0] = 400/(fc*470);
		k[1] = 620*rcq/(fc*470*rcp);
		k[2] = 620*620/(fc*fc*470*rcp);

		filter_s_to_z(k, fs, a, b);
		double s2n_out = apply_filter(m_s2ni_hist, m_s2n_hist, a, b);
		shift_hist(s2n_out, m_s2n_hist, 4);

		// sum the stage 2 outputs
		double s2_out = s2g_out + s2n_out;
		shift_hist(s2_out, m_s2_hist, 4);


		// stage 3 filter

		static const double s3_p_caps[4] = { 21, 42, 84, 168 };
		rcp = 76 + bits_to_caps(m_f3, 4, s3_p_caps);
		rcq = 20;

		k[0] = 0;
		k[1] = 420*rcq/(fc*390*rcp);
		k[2] = 420*420/(fc*fc*390*rcp);

		filter_s_to_z(k, fs, a, b);
		double s3_out = apply_filter(m_s2_hist, m_s3_hist, a, b);
		shift_hist(s3_out, m_s3_hist, 4);


		// stage 4 filter, noise injection

		// The resulting non-amplifying filter is identical, so we
		// inject instead of splitting

		static const double s4_n_caps[4] = { 24, 48, 96, 192 };
		rca = 115 + bits_to_caps(~m_fc, 4, s4_n_caps);

		shift_hist(s3_out + no_out*470/rca, m_s4i_hist, 4);


		// stage 4 filter

		rcp = 30;
		rcq = 20;

		k[0] = 0;
		k[1] = 338*rcq/(fc*470*rcp);
		k[2] = 338*338/(fc*fc*470*rcp);

		filter_s_to_z(k, fs, a, b);
		double s4_out = apply_filter(m_s4i_hist, m_s4_hist, a, b);
		shift_hist(s4_out, m_s4_hist, 4);


		// TODO: apply closure circuit (undocumented)

		// output the current result
		*dest++ = INT16(s4_out * 4000);
	}
}



//**************************************************************************
//  DEVICE INTERFACE
//**************************************************************************

//-------------------------------------------------
//  rom_region - return a pointer to the device's
//  internal ROM region
//-------------------------------------------------

const rom_entry *votrax_sc01_device::device_rom_region() const
{
	return ROM_NAME( votrax_sc01 );
}


//-------------------------------------------------
//  device_start - handle device startup
//-------------------------------------------------

void votrax_sc01_device::device_start()
{
	// initialize internal state
	m_master_clock_freq = clock();
	m_stream = stream_alloc(0, 1, m_master_clock_freq / 16);
	m_phoneme_timer = timer_alloc();
	m_rom = memregion("phoneme")->base();

	// reset inputs
	m_inflection = 0;
	m_phoneme = 0x3f;

	// reset outputs
	m_request_cb.resolve_safe();
	m_request_state = ASSERT_LINE;
	m_internal_request = ASSERT_LINE;

	// save inputs
	save_item(NAME(m_inflection));
	save_item(NAME(m_phoneme));

	// save outputs
	save_item(NAME(m_request_state));
	save_item(NAME(m_internal_request));

	// save timing circuit
	save_item(NAME(m_master_clock_freq));
	save_item(NAME(m_master_clock));
	save_item(NAME(m_counter_34));
	save_item(NAME(m_latch_70));
	save_item(NAME(m_latch_72));
	save_item(NAME(m_beta1));
	save_item(NAME(m_p2));
	save_item(NAME(m_p1));
	save_item(NAME(m_phi2));
	save_item(NAME(m_phi1));
	save_item(NAME(m_subphoneme_period));
	save_item(NAME(m_subphoneme_count));
	save_item(NAME(m_clock_88));
	save_item(NAME(m_latch_42));
	save_item(NAME(m_counter_84));
	save_item(NAME(m_latch_92));

	// save low parameter clocking
	save_item(NAME(m_srff_132));
	save_item(NAME(m_srff_114));
	save_item(NAME(m_srff_112));
	save_item(NAME(m_srff_142));
	save_item(NAME(m_latch_80));

	// save glottal circuit
	save_item(NAME(m_counter_220));
	save_item(NAME(m_counter_222));
	save_item(NAME(m_counter_224));
	save_item(NAME(m_counter_234));
	save_item(NAME(m_counter_236));
	save_item(NAME(m_fgate));
	save_item(NAME(m_glottal_sync));

	// save transition circuit
	save_item(NAME(m_0625_clock));
	save_item(NAME(m_counter_46));
	save_item(NAME(m_latch_46));
	save_item(NAME(m_ram));
	save_item(NAME(m_latch_168));
	save_item(NAME(m_latch_170));
	save_item(NAME(m_f1));
	save_item(NAME(m_f2));
	save_item(NAME(m_fc));
	save_item(NAME(m_f3));
	save_item(NAME(m_f2q));
	save_item(NAME(m_va));
	save_item(NAME(m_fa));

	// save noise generator circuit
	save_item(NAME(m_noise_clock));
	save_item(NAME(m_shift_252));
	save_item(NAME(m_counter_250));

	// save filter histories
	save_item(NAME(m_ni_hist));
	save_item(NAME(m_no_hist));
	save_item(NAME(m_va_hist));
	save_item(NAME(m_s1_hist));
	save_item(NAME(m_s2g_hist));
	save_item(NAME(m_s2n_hist));
	save_item(NAME(m_s2ni_hist));
	save_item(NAME(m_s2_hist));
	save_item(NAME(m_s3_hist));
	save_item(NAME(m_s4i_hist));
	save_item(NAME(m_s4_hist));
}


//-------------------------------------------------
//  device_reset - handle device reset
//-------------------------------------------------

void votrax_sc01_device::device_reset()
{
	// set the initial state
	m_stream->update();

	// reset inputs
	m_phoneme = 0x3f;
	m_request_cb(m_internal_request = m_request_state = ASSERT_LINE);

	// reset timing circuit
	m_master_clock = 0;
	m_counter_34 = 0;
	m_latch_70 = 0;
	m_latch_72 = 0;
	m_beta1 = 0;
	m_p2 = 0;
	m_p1 = 0;
	m_phi2 = 0;
	m_phi1 = 0;
	m_subphoneme_period = 1000;
	m_subphoneme_count = 0;
	m_clock_88 = 0;
	m_latch_42 = 0;
	m_counter_84 = 0;
	m_latch_92 = 0;

	// reset low parameter clocking
	m_srff_132 = false;
	m_srff_114 = false;
	m_srff_112 = false;
	m_srff_142 = false;
	m_latch_80 = 50;
	update_subphoneme_clock_period();

	// reset glottal circuit
	m_counter_220 = 0;
	m_counter_222 = 0;
	m_counter_224 = 0;
	m_counter_234 = 0;
	m_counter_236 = 0;
	m_fgate = 0;
	m_glottal_sync = 0;

	// reset transition circuit
	m_0625_clock = 0;
	m_counter_46 = 0;
	m_latch_46 = 0;
	memset(m_ram, 0, sizeof(m_ram));
	m_latch_168 = 0;
	m_latch_170 = 0;
	m_f1 = 0;
	m_f2 = 0;
	m_fc = 0;
	m_f3 = 0;
	m_f2q = 0;
	m_va = 0;
	m_fa = 0;

	// reset noise circuit
	m_noise_clock = 0;
	m_shift_252 = 0;
	m_counter_250 = 0;

	// reset filter histories
	memset(m_ni_hist,   0, sizeof(m_ni_hist));
	memset(m_no_hist,   0, sizeof(m_no_hist));
	memset(m_va_hist,   0, sizeof(m_va_hist));
	memset(m_s1_hist,   0, sizeof(m_s1_hist));
	memset(m_s2g_hist,  0, sizeof(m_s2g_hist));
	memset(m_s2n_hist,  0, sizeof(m_s2n_hist));
	memset(m_s2ni_hist, 0, sizeof(m_s2ni_hist));
	memset(m_s2_hist,   0, sizeof(m_s2_hist));
	memset(m_s3_hist,   0, sizeof(m_s3_hist));
	memset(m_s4i_hist,  0, sizeof(m_s4i_hist));
	memset(m_s4_hist,   0, sizeof(m_s4_hist));
}


//-------------------------------------------------
//  device_clock_changed - handle dynamic clock
//  changes by altering our output frequency
//-------------------------------------------------

void votrax_sc01_device::device_clock_changed()
{
	// compute new frequency of the master clock, and update if changed
	UINT32 newfreq = clock();
	if (newfreq != m_master_clock_freq)
	{
		// if we have a stream
		if (m_stream != NULL)
		{
			m_stream->update();
			m_stream->set_sample_rate(newfreq / 16);
		}

		// determine how many clock ticks remained on the phoneme timer
		UINT64 remaining = m_phoneme_timer->remaining().as_ticks(m_master_clock_freq);

		// recompute the master clock
		m_master_clock_freq = newfreq;

		// adjust the phoneme timer to the same number of ticks based on the new frequency
		if (remaining > 0)
			m_phoneme_timer->adjust(attotime::from_ticks(remaining, newfreq));
	}
}


//-------------------------------------------------
//  device_timer - handle device timer
//-------------------------------------------------

void votrax_sc01_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	// force a stream update
	m_stream->update();

	// if we're requesting more data, no need for timing
	if (m_request_state == ASSERT_LINE)
		return;

	// if we're supposed to have fired, do it now
	if (m_internal_request == ASSERT_LINE)
	{
osd_printf_debug("%s: REQUEST\n", timer.machine().time().as_string(3));
		m_request_cb(m_request_state = ASSERT_LINE);
		return;
	}

	// account for the rest of this subphoneme clock
	UINT32 clocks_until_request = 0;
	if (m_counter_84 != 0)
	{
		if (m_subphoneme_count < m_subphoneme_period)
			clocks_until_request += m_subphoneme_period - m_subphoneme_count;
		clocks_until_request += m_subphoneme_period * (m_counter_84 - 1);
	}

	// plus 1/2
	clocks_until_request = MAX(clocks_until_request, (1 << P_CLOCK_BIT) / 2);
	timer.adjust(attotime::from_ticks(clocks_until_request, m_master_clock_freq));
=======
/*
  Second filter type used once at the end, much simpler:

  |           +--[R1]--+
  |           |        |
  |           +--|C1|--+
  |           |        |
  |  Vi       |  |\    |
  |  ---[R0]--+--+-\   |
  |              |  >--+------ Vo
  |            0-++/
  |              |/


  Vi/R0 = Vo / (1/(1/R1 + s.C1)) = Vo (1/R1 + s.C1)
  H(s) = Vo/Vi = (R1/R0) * (1 / (1 + s.R1.C1))
*/

void votrax_sc01_device::build_lowpass_filter(double *a, double *b,
											  double c1t, // Unswitched cap, over amp-op, top
											  double c1b) // Switched cap, over amp-op, bottom
{
	// Compute the only coefficient we care about
	double k = c1b / (m_cclock * c1t);

	// Compute the filter cutoff frequency
	double fpeak = 1/(2*M_PI*k);

	// Turn that into a warp multiplier
	double zc = 2*M_PI*fpeak/tan(M_PI*fpeak / m_sclock);

	// Finally compute the result of the z-transform
	double m = zc*k;

	a[0] = 1;
	b[0] = 1+m;
	b[1] = 1-m;
}

/*
  Used to shape the white noise

         +-------------------------------------------------------------------+
         |                                                                   |
         +--|C1|--+---------|C3|----------+--|C4|--+                         |
         |        |      +        +       |        |                         |
   Vi    |  |\    |     (1)      (1)      |        |       +        +        |
   -|R0|-+--+-\   |      |        |       |  |\    |      (1)      (1)       |
            |  >--+--(2)-+--|C2|--+---(2)-+--+-\   |       |        |        |
          0-++/          |                   |  >--+--(2)--+--|C5|--+---(2)--+
            |/          Vo                 0-++/
                                             |/
   Equivalent:

         +------------------|R5|-------------------+
         |                                         |
         +--|C1|--+---------|C3|----------+--|C4|--+
         |        |                       |        |
   Vi    |  |\    |                       |        |
   -|R0|-+--+-\   |                       |  |\    |
            |  >--+---------|R2|----------+--+-\   |
          0-++/   |                          |  >--+
            |/   Vo                        0-++/
                                             |/

  We assume r0 = r2
*/

void votrax_sc01_device::build_noise_shaper_filter(double *a, double *b,
												   double c1,  // Cap over first amp-op
												   double c2t, // Unswitched cap between amp-ops, input, top
												   double c2b, // Switched cap between amp-ops, input, bottom
												   double c3,  // Cap over second amp-op
												   double c4)  // Switched cap after second amp-op
{
	// Coefficients of H(s) = k1*s / (1 + k2*s + k3*s^2)
	double k0 = c2t*c3*c2b/c4;
	double k1 = c2t*(m_cclock * c2b);
	double k2 = c1*c2t*c3/(m_cclock * c4);

	// Estimate the filter cutoff frequency
	double fpeak = sqrt(1/k2)/(2*M_PI);

	// Turn that into a warp multiplier
	double zc = 2*M_PI*fpeak/tan(M_PI*fpeak / m_sclock);

	// Finally compute the result of the z-transform
	double m0 = zc*k0;
	double m1 = zc*k1;
	double m2 = zc*zc*k2;

	a[0] = m0;
	a[1] = 0;
	a[2] = -m0;
	b[0] = 1+m1+m2;
	b[1] = 2-2*m2;
	b[2] = 1-m1+m2;
}

/*
  Noise injection in f2

  |                     +--[R2]--+        +--[R1]-------- Vi
  |                     |        |        |
  |                     +--|C2|--+<V1     +--|C3|--+
  |                     |        |        |        |
  |                     |  |\    |        |  |\    |
  |                +----+--+-\   |        +--+-\   |
  |                |       |  >--+--[Rx]--+  |  >--+----- Vo
  |                |     0-++/             0-++/   |
  |                |       |/    +--[R0]--+  |/    |
  |                |             |        |        |
  |                |             |    /|  |        |
  |                |             |   /-+--+--[R0]--+
  |                +--[R4]-------+--<  |
  |                            V2^   \++-0
  |                                   \|

  We drop r0/r1 out of the equation (it factorizes), and we rescale so
  that H(infinity)=1.
*/

void votrax_sc01_device::build_injection_filter(double *a, double *b,
												double c1b, // Switched cap, input, bottom
												double c2t, // Unswitched cap, over first amp-op, top
												double c2b, // Switched cap, over first amp-op, bottom
												double c3,  // Cap between the two op-amps
												double c4)  // Cap over second op-amp
{
	// First compute the three coefficients of H(s) = (k0 + k2*s)/(k1 - k2*s)
	double k0 = m_cclock * c2t;
	double k1 = m_cclock * (c1b * c3 / c2t - c2t);
	double k2 = c2b;

	// Don't pre-warp
	double zc = 2*m_sclock;

	// Finally compute the result of the z-transform
	double m = zc*k2;

	a[0] = k0 + m;
	a[1] = k0 - m;
	b[0] = k1 - m;
	b[1] = k1 + m;

	// That ends up in a numerically unstable filter.  Neutralize it for now.
	a[0] = 1;
	a[1] = 0;
	b[0] = 1;
	b[1] = 0;
>>>>>>> upstream/master
}
