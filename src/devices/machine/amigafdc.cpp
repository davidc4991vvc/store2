// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/***************************************************************************

    Amiga floppy disk controller emulation

***************************************************************************/


#include "emu.h"
#include "includes/amiga.h"
#include "formats/ami_dsk.h"
#include "amigafdc.h"

<<<<<<< HEAD
const device_type AMIGA_FDC = &device_creator<amiga_fdc>;

FLOPPY_FORMATS_MEMBER( amiga_fdc::floppy_formats )
	FLOPPY_ADF_FORMAT
FLOPPY_FORMATS_END

amiga_fdc::amiga_fdc(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, AMIGA_FDC, "Amiga FDC", tag, owner, clock, "amiga_fdc", __FILE__),
	m_write_index(*this), floppy(nullptr), t_gen(nullptr), dsklen(0), pre_dsklen(0), dsksync(0), dskbyt(0), adkcon(0), dmacon(0), dskpt(0), dma_value(0), dma_state(0)
{
}

void amiga_fdc::device_start()
=======
DEFINE_DEVICE_TYPE(AMIGA_FDC, amiga_fdc_device, "amiga_fdc", "Amiga FDC")

FLOPPY_FORMATS_MEMBER( amiga_fdc_device::floppy_formats )
	FLOPPY_ADF_FORMAT
FLOPPY_FORMATS_END

amiga_fdc_device::amiga_fdc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, AMIGA_FDC, tag, owner, clock),
	m_write_index(*this),
	floppy(nullptr), t_gen(nullptr), dsklen(0), pre_dsklen(0), dsksync(0), dskbyt(0), adkcon(0), dmacon(0), dskpt(0), dma_value(0), dma_state(0)
{
}

void amiga_fdc_device::device_start()
>>>>>>> upstream/master
{
	m_write_index.resolve_safe();

	static const char *names[] = { "0", "1", "2", "3" };
	for(int i=0; i != 4; i++) {
		floppy_connector *con = subdevice<floppy_connector>(names[i]);
		if(con)
			floppy_devices[i] = con->get_device();
		else
<<<<<<< HEAD
			floppy_devices[i] = 0;
	}

	floppy = 0;
=======
			floppy_devices[i] = nullptr;
	}

	floppy = nullptr;
>>>>>>> upstream/master

	t_gen = timer_alloc(0);
}


<<<<<<< HEAD
void amiga_fdc::device_reset()
{
	floppy = 0;
=======
void amiga_fdc_device::device_reset()
{
	floppy = nullptr;
>>>>>>> upstream/master
	dsklen = 0x4000;
	dsksync = 0x4489;
	adkcon = 0;
	dmacon = 0;
	dskpt = 0;
	dskbyt = 0;
	pre_dsklen = 0x4000;
	dma_value = 0;
	dma_state = DMA_IDLE;

	live_abort();
}

<<<<<<< HEAD
void amiga_fdc::dma_done()
=======
void amiga_fdc_device::dma_done()
>>>>>>> upstream/master
{
	amiga_state *state = machine().driver_data<amiga_state>();
	if(dskbyt & 0x2000) {
		dskbyt &= ~0x2000;
		cur_live.pll.stop_writing(floppy, cur_live.tm);
	}

	dma_state = DMA_IDLE;
	state->custom_chip_w(REG_INTREQ, INTENA_SETCLR | INTENA_DSKBLK);
}

<<<<<<< HEAD
void amiga_fdc::dma_write(UINT16 value)
=======
void amiga_fdc_device::dma_write(uint16_t value)
>>>>>>> upstream/master
{
	amiga_state *state = machine().driver_data<amiga_state>();
	state->chip_ram_w(dskpt, value);

	dskpt += 2;
	dsklen--;

	if(dsklen & 0x3fff)
		dma_state = DMA_RUNNING_BYTE_0;
	else
		dma_done();
}

<<<<<<< HEAD
UINT16 amiga_fdc::dma_read()
{
	amiga_state *state = machine().driver_data<amiga_state>();
	UINT16 res = state->chip_ram_r(dskpt);
=======
uint16_t amiga_fdc_device::dma_read()
{
	amiga_state *state = machine().driver_data<amiga_state>();
	uint16_t res = state->chip_ram_r(dskpt);
>>>>>>> upstream/master

	dskpt += 2;
	dsklen--;

	// This loses the last word.  So does the real hardware.
	if(dsklen & 0x3fff)
		dma_state = DMA_RUNNING_BYTE_0;
	else
		dma_done();

	return res;
}

<<<<<<< HEAD
void amiga_fdc::live_start()
=======
void amiga_fdc_device::live_start()
>>>>>>> upstream/master
{
	cur_live.tm = machine().time();
	cur_live.state = RUNNING;
	cur_live.next_state = -1;
	cur_live.shift_reg = 0;
	cur_live.bit_counter = 0;
	cur_live.pll.reset(cur_live.tm);
	cur_live.pll.set_clock(clocks_to_attotime(1));
	checkpoint_live = cur_live;

	live_run();
}

<<<<<<< HEAD
void amiga_fdc::checkpoint()
=======
void amiga_fdc_device::checkpoint()
>>>>>>> upstream/master
{
	cur_live.pll.commit(floppy, cur_live.tm);
	checkpoint_live = cur_live;
}

<<<<<<< HEAD
void amiga_fdc::rollback()
=======
void amiga_fdc_device::rollback()
>>>>>>> upstream/master
{
	cur_live = checkpoint_live;
}

<<<<<<< HEAD
void amiga_fdc::live_delay(int state)
=======
void amiga_fdc_device::live_delay(int state)
>>>>>>> upstream/master
{
	cur_live.next_state = state;
	if(cur_live.tm != machine().time())
		t_gen->adjust(cur_live.tm - machine().time());
}

<<<<<<< HEAD
void amiga_fdc::live_sync()
=======
void amiga_fdc_device::live_sync()
>>>>>>> upstream/master
{
	if(!cur_live.tm.is_never()) {
		if(cur_live.tm > machine().time()) {
			rollback();
			live_run(machine().time());
			cur_live.pll.commit(floppy, cur_live.tm);

		} else {
			cur_live.pll.commit(floppy, cur_live.tm);

			if(cur_live.next_state != -1) {
				cur_live.state = cur_live.next_state;
				cur_live.next_state = -1;
			}
			if(cur_live.state == IDLE) {
				cur_live.pll.stop_writing(floppy, cur_live.tm);
				cur_live.tm = attotime::never;
			}
		}
		cur_live.next_state = -1;
		checkpoint();
	}
}

<<<<<<< HEAD
void amiga_fdc::live_abort()
=======
void amiga_fdc_device::live_abort()
>>>>>>> upstream/master
{
	if(!cur_live.tm.is_never() && cur_live.tm > machine().time()) {
		rollback();
		live_run(machine().time());
	}

	cur_live.pll.stop_writing(floppy, cur_live.tm);
	cur_live.tm = attotime::never;
	cur_live.state = IDLE;
	cur_live.next_state = -1;
}

<<<<<<< HEAD
void amiga_fdc::live_run(const attotime &limit)
=======
void amiga_fdc_device::live_run(const attotime &limit)
>>>>>>> upstream/master
{
	amiga_state *state = machine().driver_data<amiga_state>();

	if(cur_live.state == IDLE || cur_live.next_state != -1)
		return;

	for(;;) {
		switch(cur_live.state) {
		case RUNNING: {
			if(!(dskbyt & 0x2000)) {
				int bit = cur_live.pll.get_next_bit(cur_live.tm, floppy, limit);
				if(bit < 0)
					return;

				cur_live.shift_reg = (cur_live.shift_reg << 1) | bit;
				cur_live.bit_counter++;

				if((adkcon & 0x0200) && !(cur_live.shift_reg & 0x80)) {
					cur_live.bit_counter--;

					// Avoid any risk of livelock
					live_delay(RUNNING_SYNCPOINT);
					return;
				}

				if(cur_live.bit_counter > 8)
<<<<<<< HEAD
					fatalerror("amiga_fdc::live_run - cur_live.bit_counter > 8\n");
=======
					fatalerror("amiga_fdc_device::live_run - cur_live.bit_counter > 8\n");
>>>>>>> upstream/master

				if(cur_live.bit_counter == 8) {
					live_delay(RUNNING_SYNCPOINT);
					return;
				}
				if(dskbyt & 0x1000) {
					if(cur_live.shift_reg != dsksync) {
						live_delay(RUNNING_SYNCPOINT);
						return;
					}
				} else {
					if(cur_live.shift_reg == dsksync) {
						live_delay(RUNNING_SYNCPOINT);
						return;
					}
				}
			} else {
				int bit = (dma_state == DMA_RUNNING_BYTE_0 ? 15 : 7) - cur_live.bit_counter;
				if(cur_live.pll.write_next_bit((dma_value >> bit) & 1, cur_live.tm, floppy, limit))
					return;
				cur_live.bit_counter++;
				if(cur_live.bit_counter > 8)
<<<<<<< HEAD
					fatalerror("amiga_fdc::live_run - cur_live.bit_counter > 8\n");
=======
					fatalerror("amiga_fdc_device::live_run - cur_live.bit_counter > 8\n");
>>>>>>> upstream/master

				if(cur_live.bit_counter == 8) {
					live_delay(RUNNING_SYNCPOINT);
					return;
				}
			}
			break;
		}

		case RUNNING_SYNCPOINT: {
			if(!(dskbyt & 0x2000)) {
				if(cur_live.shift_reg == dsksync) {
					if(adkcon & 0x0400) {
						if(dma_state == DMA_WAIT_START) {
							cur_live.bit_counter = 0;

							if(!(dsklen & 0x3fff))
								dma_done();
							else if(dsklen & 0x4000) {
								dskbyt |= 0x2000;
								cur_live.bit_counter = 0;
								dma_value = dma_read();

							} else
								dma_write(dsksync);

						} else if(dma_state != DMA_IDLE) {
							dma_write(dsksync);
							cur_live.bit_counter = 0;

						} else if(cur_live.bit_counter != 8)
							cur_live.bit_counter = 0;
					}
					dskbyt |= 0x1000;
					state->custom_chip_w(REG_INTREQ, INTENA_SETCLR | INTENA_DSKSYN);
				} else
					dskbyt &= ~0x1000;

				if(cur_live.bit_counter == 8) {
					dskbyt = (dskbyt & 0xff00) | 0x8000 | (cur_live.shift_reg & 0xff);
					cur_live.bit_counter = 0;

					switch(dma_state) {
					case DMA_IDLE:
					case DMA_WAIT_START:
						break;

					case DMA_RUNNING_BYTE_0:
						dma_value = (cur_live.shift_reg & 0xff) << 8;
						dma_state = DMA_RUNNING_BYTE_1;
						break;

					case DMA_RUNNING_BYTE_1: {
						dma_value |= cur_live.shift_reg & 0xff;
						dma_write(dma_value);
						break;
					}
					}
				}
			} else {
				if(cur_live.bit_counter != 8)
<<<<<<< HEAD
					fatalerror("amiga_fdc::live_run - cur_live.bit_counter != 8\n");
=======
					fatalerror("amiga_fdc_device::live_run - cur_live.bit_counter != 8\n");
>>>>>>> upstream/master
				cur_live.bit_counter = 0;

				switch(dma_state) {
				case DMA_IDLE:
				case DMA_WAIT_START:
					break;

				case DMA_RUNNING_BYTE_0:
					dma_state = DMA_RUNNING_BYTE_1;
					break;

				case DMA_RUNNING_BYTE_1: {
					dma_value = dma_read();
					break;
				}
				}
			}

			cur_live.state = RUNNING;
			checkpoint();
			break;
		}
		}
	}
}

<<<<<<< HEAD
bool amiga_fdc::dma_enabled()
=======
bool amiga_fdc_device::dma_enabled()
>>>>>>> upstream/master
{
	return (dsklen & 0x8000) && ((dmacon & 0x0210) == 0x0210);
}

<<<<<<< HEAD
void amiga_fdc::dma_check()
=======
void amiga_fdc_device::dma_check()
>>>>>>> upstream/master
{
	bool was_writing = dskbyt & 0x2000;
	dskbyt &= 0x9fff;
	if(dma_enabled()) {
		if(dma_state == IDLE) {
			dma_state = adkcon & 0x0400 ? DMA_WAIT_START : DMA_RUNNING_BYTE_0;
			if(dma_state == DMA_RUNNING_BYTE_0) {
				if(!(dsklen & 0x3fff))
					dma_done();
				else if(dsklen & 0x4000) {
					dskbyt |= 0x2000;
					cur_live.bit_counter = 0;
					dma_value = dma_read();
				}
			}
		} else {
			dskbyt |= 0x4000;
			if(dsklen & 0x4000)
				dskbyt |= 0x2000;
		}
	} else
		dma_state = IDLE;

	if(was_writing && !(dskbyt & 0x2000))
		cur_live.pll.stop_writing(floppy, cur_live.tm);
	if(!was_writing && (dskbyt & 0x2000))
		cur_live.pll.start_writing(cur_live.tm);

}

<<<<<<< HEAD
void amiga_fdc::adkcon_set(UINT16 data)
=======
void amiga_fdc_device::adkcon_set(uint16_t data)
>>>>>>> upstream/master
{
	live_sync();
	adkcon = data;
	live_run();
}

<<<<<<< HEAD
UINT16 amiga_fdc::adkcon_r(void)
=======
uint16_t amiga_fdc_device::adkcon_r(void)
>>>>>>> upstream/master
{
	return adkcon;
}

<<<<<<< HEAD
void amiga_fdc::dsklen_w(UINT16 data)
=======
void amiga_fdc_device::dsklen_w(uint16_t data)
>>>>>>> upstream/master
{
	live_sync();
	if(!(data & 0x8000) || (data == pre_dsklen)) {
		dsklen = pre_dsklen = data;
		dma_check();

	} else
		pre_dsklen = data;
	live_run();
}

<<<<<<< HEAD
void amiga_fdc::dskpth_w(UINT16 data)
=======
void amiga_fdc_device::dskpth_w(uint16_t data)
>>>>>>> upstream/master
{
	live_sync();
	dskpt = (dskpt & 0xffff) | (data << 16);
	live_run();
}

<<<<<<< HEAD
void amiga_fdc::dskptl_w(UINT16 data)
=======
void amiga_fdc_device::dskptl_w(uint16_t data)
>>>>>>> upstream/master
{
	live_sync();
	dskpt = (dskpt & 0xffff0000) | data;
	live_run();
}

<<<<<<< HEAD
UINT16 amiga_fdc::dskpth_r()
=======
uint16_t amiga_fdc_device::dskpth_r()
>>>>>>> upstream/master
{
	return dskpt >> 16;
}

<<<<<<< HEAD
UINT16 amiga_fdc::dskptl_r()
=======
uint16_t amiga_fdc_device::dskptl_r()
>>>>>>> upstream/master
{
	return dskpt;
}

<<<<<<< HEAD
void amiga_fdc::dsksync_w(UINT16 data)
=======
void amiga_fdc_device::dsksync_w(uint16_t data)
>>>>>>> upstream/master
{
	live_sync();
	dsksync = data;
	live_run();
}

<<<<<<< HEAD
void amiga_fdc::dmacon_set(UINT16 data)
=======
void amiga_fdc_device::dmacon_set(uint16_t data)
>>>>>>> upstream/master
{
	live_sync();
	dmacon = data;
	dma_check();
	live_run();
}

<<<<<<< HEAD
UINT16 amiga_fdc::dskbytr_r()
{
	UINT16 res = dskbyt;
=======
uint16_t amiga_fdc_device::dskbytr_r()
{
	uint16_t res = dskbyt;
>>>>>>> upstream/master
	dskbyt &= 0x7fff;
	return res;
}

<<<<<<< HEAD
void amiga_fdc::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
=======
void amiga_fdc_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
>>>>>>> upstream/master
{
	live_sync();
	live_run();
}

<<<<<<< HEAD
void amiga_fdc::setup_leds()
=======
void amiga_fdc_device::setup_leds()
>>>>>>> upstream/master
{
	if(floppy) {
		int drive =
			floppy == floppy_devices[0] ? 0 :
			floppy == floppy_devices[1] ? 1 :
			floppy == floppy_devices[2] ? 2 :
			3;

<<<<<<< HEAD
		output_set_value("drive_0_led", drive == 0);
		output_set_value("drive_1_led", drive == 1);
		output_set_value("drive_2_led", drive == 2);
		output_set_value("drive_3_led", drive == 3);

		set_led_status(machine(), 1, drive == 0); /* update internal drive led */
		set_led_status(machine(), 2, drive == 1); /* update external drive led */
	}
}

WRITE8_MEMBER( amiga_fdc::ciaaprb_w )
=======
		machine().output().set_value("drive_0_led", drive == 0);
		machine().output().set_value("drive_1_led", drive == 1);
		machine().output().set_value("drive_2_led", drive == 2);
		machine().output().set_value("drive_3_led", drive == 3);

		machine().output().set_led_value(1, drive == 0); /* update internal drive led */
		machine().output().set_led_value(2, drive == 1); /* update external drive led */
	}
}

WRITE8_MEMBER( amiga_fdc_device::ciaaprb_w )
>>>>>>> upstream/master
{
	floppy_image_device *old_floppy = floppy;

	live_sync();

	if(!(data & 0x08))
		floppy = floppy_devices[0];
	else if(!(data & 0x10))
		floppy = floppy_devices[1];
	else if(!(data & 0x20))
		floppy = floppy_devices[2];
	else if(!(data & 0x40))
		floppy = floppy_devices[3];
	else
<<<<<<< HEAD
		floppy = 0;
=======
		floppy = nullptr;
>>>>>>> upstream/master

	if(old_floppy != floppy) {
		if(old_floppy)
			old_floppy->setup_index_pulse_cb(floppy_image_device::index_pulse_cb());
		if(floppy)
<<<<<<< HEAD
			floppy->setup_index_pulse_cb(floppy_image_device::index_pulse_cb(FUNC(amiga_fdc::index_callback), this));
=======
			floppy->setup_index_pulse_cb(floppy_image_device::index_pulse_cb(&amiga_fdc_device::index_callback, this));
>>>>>>> upstream/master
	}

	if(floppy) {
		floppy->ss_w(!((data >> 2) & 1));
		floppy->dir_w((data >> 1) & 1);
		floppy->stp_w(data & 1);
		floppy->mon_w((data >> 7) & 1);
<<<<<<< HEAD
		output_set_value("fdc_led", data & 0x80); // LED directly connected to FDC motor
=======
		machine().output().set_value("fdc_led", data & 0x80); // LED directly connected to FDC motor
>>>>>>> upstream/master
	}

	if(floppy) {
		if(cur_live.state == IDLE)
			live_start();
	} else
		live_abort();

	setup_leds();
	live_run();
}

<<<<<<< HEAD
UINT8 amiga_fdc::ciaapra_r()
{
	UINT8 ret = 0x3c;
=======
uint8_t amiga_fdc_device::ciaapra_r()
{
	uint8_t ret = 0x3c;
>>>>>>> upstream/master
	if(floppy) {
		//if(!floppy->ready_r()) fixit: seems to not work well with multiple disk drives
			ret &= ~0x20;
		if(!floppy->trk00_r())
			ret &= ~0x10;
		if(floppy->wpt_r())
			ret &= ~0x08;
		if(!floppy->dskchg_r())
			ret &= ~0x04;
	}

	return ret;
}

<<<<<<< HEAD
void amiga_fdc::index_callback(floppy_image_device *floppy, int state)
=======
void amiga_fdc_device::index_callback(floppy_image_device *floppy, int state)
>>>>>>> upstream/master
{
	/* Issue a index pulse when a disk revolution completes */
	m_write_index(!state);
}

<<<<<<< HEAD
void amiga_fdc::pll_t::set_clock(const attotime &period)
=======
void amiga_fdc_device::pll_t::set_clock(const attotime &period)
>>>>>>> upstream/master
{
	for(int i=0; i<38; i++)
		delays[i] = period*(i+1);
}

<<<<<<< HEAD
void amiga_fdc::pll_t::reset(const attotime &when)
=======
void amiga_fdc_device::pll_t::reset(const attotime &when)
>>>>>>> upstream/master
{
	counter = 0;
	increment = 146;
	transition_time = 0xffff;
	history = 0x80;
	slot = 0;
	ctime = when;
	phase_add = 0x00;
	phase_sub = 0x00;
	freq_add  = 0x00;
	freq_sub  = 0x00;
}

<<<<<<< HEAD
int amiga_fdc::pll_t::get_next_bit(attotime &tm, floppy_image_device *floppy, const attotime &limit)
=======
int amiga_fdc_device::pll_t::get_next_bit(attotime &tm, floppy_image_device *floppy, const attotime &limit)
>>>>>>> upstream/master
{
	attotime when = floppy ? floppy->get_next_transition(ctime) : attotime::never;

	for(;;) {
		attotime etime = ctime+delays[slot];
		if(etime > limit)
			return -1;
		if(transition_time == 0xffff && !when.is_never() && etime >= when)
			transition_time = counter;
		if(slot < 8) {
<<<<<<< HEAD
			UINT8 mask = 1 << slot;
=======
			uint8_t mask = 1 << slot;
>>>>>>> upstream/master
			if(phase_add & mask)
				counter += 258;
			else if(phase_sub & mask)
				counter += 34;
			else
				counter += increment;

			if((freq_add & mask) && increment < 159)
				increment++;
			else if((freq_sub & mask) && increment > 134)
				increment--;
		} else
			counter += increment;

		slot++;
		tm = etime;
		if(counter & 0x800)
			break;
	}

	int bit = transition_time != 0xffff;

	if(transition_time != 0xffff) {
<<<<<<< HEAD
		static const UINT8 pha[8] = { 0xf, 0x7, 0x3, 0x1, 0, 0, 0, 0 };
		static const UINT8 phs[8] = { 0, 0, 0, 0, 0x1, 0x3, 0x7, 0xf };
		static const UINT8 freqa[4][8] = {
=======
		static const uint8_t pha[8] = { 0xf, 0x7, 0x3, 0x1, 0, 0, 0, 0 };
		static const uint8_t phs[8] = { 0, 0, 0, 0, 0x1, 0x3, 0x7, 0xf };
		static const uint8_t freqa[4][8] = {
>>>>>>> upstream/master
			{ 0xf, 0x7, 0x3, 0x1, 0, 0, 0, 0 },
			{ 0x7, 0x3, 0x1, 0, 0, 0, 0, 0 },
			{ 0x7, 0x3, 0x1, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		};
<<<<<<< HEAD
		static const UINT8 freqs[4][8] = {
=======
		static const uint8_t freqs[4][8] = {
>>>>>>> upstream/master
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0x1, 0x3, 0x7 },
			{ 0, 0, 0, 0, 0, 0x1, 0x3, 0x7 },
			{ 0, 0, 0, 0, 0x1, 0x3, 0x7, 0xf },
		};

		int cslot = transition_time >> 8;
		phase_add = pha[cslot];
		phase_sub = phs[cslot];
		int way = transition_time & 0x400 ? 1 : 0;
		if(history & 0x80)
			history = way ? 0x80 : 0x83;
		else if(history & 0x40)
			history = way ? history & 2 : (history & 2) | 1;
		freq_add = freqa[history & 3][cslot];
		freq_sub = freqs[history & 3][cslot];
		history = way ? (history >> 1) | 2 : history >> 1;

	} else
		phase_add = phase_sub = freq_add = freq_sub = 0;

	counter &= 0x7ff;

	ctime = tm;
	transition_time = 0xffff;
	slot = 0;

	return bit;
}

<<<<<<< HEAD
void amiga_fdc::pll_t::start_writing(const attotime & tm)
=======
void amiga_fdc_device::pll_t::start_writing(const attotime & tm)
>>>>>>> upstream/master
{
	write_start_time = tm;
	write_position = 0;
}

<<<<<<< HEAD
void amiga_fdc::pll_t::stop_writing(floppy_image_device *floppy, const attotime &tm)
=======
void amiga_fdc_device::pll_t::stop_writing(floppy_image_device *floppy, const attotime &tm)
>>>>>>> upstream/master
{
	commit(floppy, tm);
	write_start_time = attotime::never;
}

<<<<<<< HEAD
bool amiga_fdc::pll_t::write_next_bit(bool bit, attotime &tm, floppy_image_device *floppy, const attotime &limit)
=======
bool amiga_fdc_device::pll_t::write_next_bit(bool bit, attotime &tm, floppy_image_device *floppy, const attotime &limit)
>>>>>>> upstream/master
{
	if(write_start_time.is_never()) {
		write_start_time = ctime;
		write_position = 0;
	}

	for(;;) {
		attotime etime = ctime+delays[slot];
		if(etime > limit)
			return true;
<<<<<<< HEAD
		UINT16 pre_counter = counter;
=======
		uint16_t pre_counter = counter;
>>>>>>> upstream/master
		counter += increment;
		if(bit && !(pre_counter & 0x400) && (counter & 0x400))
			if(write_position < ARRAY_LENGTH(write_buffer))
				write_buffer[write_position++] = etime;
		slot++;
		tm = etime;
		if(counter & 0x800)
			break;
	}

	counter &= 0x7ff;

	ctime = tm;
	slot = 0;

	return false;
}


<<<<<<< HEAD
void amiga_fdc::pll_t::commit(floppy_image_device *floppy, const attotime &tm)
=======
void amiga_fdc_device::pll_t::commit(floppy_image_device *floppy, const attotime &tm)
>>>>>>> upstream/master
{
	if(write_start_time.is_never() || tm == write_start_time)
		return;

	if(floppy)
		floppy->write_flux(write_start_time, tm, write_position, write_buffer);
	write_start_time = tm;
	write_position = 0;
}
