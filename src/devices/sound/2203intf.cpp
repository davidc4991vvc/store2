// license:BSD-3-Clause
// copyright-holders:Ernesto Corvi
<<<<<<< HEAD
#include "2203intf.h"
#include "fm.h"

static void psg_set_clock(void *param, int clock)
{
	ym2203_device *ym2203 = (ym2203_device *) param;
	ym2203->ay_set_clock(clock);
}

static void psg_write(void *param, int address, int data)
{
	ym2203_device *ym2203 = (ym2203_device *) param;
	ym2203->ay8910_write_ym(address, data);
}

static int psg_read(void *param)
{
	ym2203_device *ym2203 = (ym2203_device *) param;
	return ym2203->ay8910_read_ym();
}

static void psg_reset(void *param)
{
	ym2203_device *ym2203 = (ym2203_device *) param;
	ym2203->ay8910_reset_ym();
}

static const ssg_callbacks psgintf =
{
	psg_set_clock,
	psg_write,
	psg_read,
	psg_reset
};

/* IRQ Handler */
static void IRQHandler(void *param,int irq)
{
	ym2203_device *ym2203 = (ym2203_device *) param;
	ym2203->_IRQHandler(irq);
}

void ym2203_device::_IRQHandler(int irq)
=======
#include "emu.h"
#include "2203intf.h"
#include "fm.h"

const ssg_callbacks ym2203_device::psgintf =
{
	&ym2203_device::psg_set_clock,
	&ym2203_device::psg_write,
	&ym2203_device::psg_read,
	&ym2203_device::psg_reset
};

/* IRQ Handler */
void ym2203_device::irq_handler(int irq)
>>>>>>> upstream/master
{
	if (!m_irq_handler.isnull())
		m_irq_handler(irq);
}

/* Timer overflow callback from timer.c */
void ym2203_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	switch(id)
	{
	case 0:
		ym2203_timer_over(m_chip,0);
		break;

	case 1:
		ym2203_timer_over(m_chip,1);
		break;
	}
}

<<<<<<< HEAD
static void timer_handler(void *param,int c,int count,int clock)
{
	ym2203_device *ym2203 = (ym2203_device *) param;
	ym2203->_timer_handler(c, count, clock);
}

void ym2203_device::_timer_handler(int c,int count,int clock)
=======
void ym2203_device::timer_handler(int c, int count, int clock)
>>>>>>> upstream/master
{
	if( count == 0 )
	{   /* Reset FM Timer */
		m_timer[c]->enable(false);
	}
	else
	{   /* Start FM Timer */
		attotime period = attotime::from_hz(clock) * count;

		if (!m_timer[c]->enable(true))
			m_timer[c]->adjust(period);
	}
}

<<<<<<< HEAD
/* update request from fm.c */
void ym2203_update_request(void *param)
{
	ym2203_device *ym2203 = (ym2203_device *) param;
	ym2203->_ym2203_update_request();
}

void ym2203_device::_ym2203_update_request()
{
	m_stream->update();
}

=======
>>>>>>> upstream/master
//-------------------------------------------------
//  sound_stream_update - handle a stream update
//-------------------------------------------------


void ym2203_device::stream_generate(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples)
{
	ym2203_update_one(m_chip, outputs[0], samples);
}


void ym2203_device::device_post_load()
{
	ym2203_postload(m_chip);
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void ym2203_device::device_start()
{
	ay8910_device::device_start();

<<<<<<< HEAD
	int rate = clock()/72; /* ??? */

=======
>>>>>>> upstream/master
	m_irq_handler.resolve();

	/* Timer Handler set */
	m_timer[0] = timer_alloc(0);
	m_timer[1] = timer_alloc(1);

	/* stream system initialize */
<<<<<<< HEAD
	m_stream = machine().sound().stream_alloc(*this,0,1,rate, stream_update_delegate(FUNC(ym2203_device::stream_generate),this));

	/* Initialize FM emurator */
	m_chip = ym2203_init(this,this,clock(),rate,timer_handler,IRQHandler,&psgintf);
	assert_always(m_chip != NULL, "Error creating YM2203 chip");
=======
	calculate_rates();

	/* Initialize FM emurator */
	int rate = clock()/72; /* ??? */
	m_chip = ym2203_init(this,clock(),rate,&ym2203_device::static_timer_handler,&ym2203_device::static_irq_handler,&psgintf);
	assert_always(m_chip != nullptr, "Error creating YM2203 chip");
}

void ym2203_device::device_clock_changed()
{
	calculate_rates();
	ym2203_clock_changed(m_chip, clock(), clock() / 72);
}

void ym2203_device::calculate_rates()
{
	int rate = clock()/72; /* ??? */

	if (m_stream != nullptr)
		m_stream->set_sample_rate(rate);
	else
		m_stream = machine().sound().stream_alloc(*this,0,1,rate, stream_update_delegate(&ym2203_device::stream_generate,this));
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_stop - device-specific stop
//-------------------------------------------------

void ym2203_device::device_stop()
{
<<<<<<< HEAD
	ym2203_shutdown(m_chip);
=======
	if (m_chip)
		ym2203_shutdown(m_chip);
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void ym2203_device::device_reset()
{
	ym2203_reset_chip(m_chip);
}


READ8_MEMBER( ym2203_device::read )
{
	return ym2203_read(m_chip, offset & 1);
}

WRITE8_MEMBER( ym2203_device::write )
{
	ym2203_write(m_chip, offset & 1, data);
}

READ8_MEMBER( ym2203_device::status_port_r )
{
	return read(space, 0);
}

READ8_MEMBER( ym2203_device::read_port_r )
{
	return read(space, 1);
}

WRITE8_MEMBER( ym2203_device::control_port_w )
{
	write(space, 0, data);
}

WRITE8_MEMBER( ym2203_device::write_port_w )
{
	write(space, 1, data);
}

<<<<<<< HEAD
const device_type YM2203 = &device_creator<ym2203_device>;

ym2203_device::ym2203_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: ay8910_device(mconfig, YM2203, "YM2203", tag, owner, clock, PSG_TYPE_YM, 3, 2, "ym2203", __FILE__),
		m_irq_handler(*this)
=======
DEFINE_DEVICE_TYPE(YM2203, ym2203_device, "ym2203", "YM2203 OPN")

ym2203_device::ym2203_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: ay8910_device(mconfig, YM2203, tag, owner, clock, PSG_TYPE_YM, 3, 2)
	, m_stream(nullptr)
	, m_timer{ nullptr, nullptr }
	, m_chip(nullptr)
	, m_irq_handler(*this)
>>>>>>> upstream/master
{
}
