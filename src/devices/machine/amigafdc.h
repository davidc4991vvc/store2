// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#ifndef AMIGAFDC_H
#define AMIGAFDC_H

#include "emu.h"
#include "imagedev/floppy.h"

#define MCFG_AMIGA_FDC_INDEX_CALLBACK(_write) \
	devcb = &amiga_fdc::set_index_wr_callback(*device, DEVCB_##_write);

class amiga_fdc : public device_t {
public:
	amiga_fdc(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	template<class _Object> static devcb_base &set_index_wr_callback(device_t &device, _Object object) { return downcast<amiga_fdc &>(device).m_write_index.set_callback(object); }

	DECLARE_WRITE8_MEMBER(ciaaprb_w);

	UINT8 ciaapra_r();
	UINT16 dskbytr_r();
	UINT16 dskpth_r();
	UINT16 dskptl_r();

	void dsksync_w(UINT16 data);
	void dskpth_w(UINT16 data);
	void dskptl_w(UINT16 data);
	void dsklen_w(UINT16 data);
	void adkcon_set(UINT16 data);
	void dmacon_set(UINT16 data);
	UINT16 adkcon_r(void);
=======
#ifndef MAME_MACHINE_AMIGAFDC_H
#define MAME_MACHINE_AMIGAFDC_H

#pragma once

#include "imagedev/floppy.h"

#define MCFG_AMIGA_FDC_INDEX_CALLBACK(_write) \
	devcb = &amiga_fdc_device::set_index_wr_callback(*device, DEVCB_##_write);

class amiga_fdc_device : public device_t {
public:
	amiga_fdc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static devcb_base &set_index_wr_callback(device_t &device, Object &&cb) { return downcast<amiga_fdc_device &>(device).m_write_index.set_callback(std::forward<Object>(cb)); }

	DECLARE_WRITE8_MEMBER(ciaaprb_w);

	uint8_t ciaapra_r();
	uint16_t dskbytr_r();
	uint16_t dskpth_r();
	uint16_t dskptl_r();

	void dsksync_w(uint16_t data);
	void dskpth_w(uint16_t data);
	void dskptl_w(uint16_t data);
	void dsklen_w(uint16_t data);
	void adkcon_set(uint16_t data);
	void dmacon_set(uint16_t data);
	uint16_t adkcon_r(void);
>>>>>>> upstream/master

	DECLARE_FLOPPY_FORMATS( floppy_formats );

protected:
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
>>>>>>> upstream/master

private:
	// Running states
	enum {
		IDLE,
		RUNNING,
		RUNNING_SYNCPOINT
	};

	// DMA states
	enum {
		DMA_IDLE,
		DMA_WAIT_START,
		DMA_RUNNING_BYTE_0,
		DMA_RUNNING_BYTE_1
	};

	struct pll_t {
<<<<<<< HEAD
		UINT16 counter;
		UINT16 increment;
		UINT16 transition_time;
		UINT8 history;
		UINT8 slot;
		UINT8 phase_add, phase_sub, freq_add, freq_sub;
=======
		uint16_t counter;
		uint16_t increment;
		uint16_t transition_time;
		uint8_t history;
		uint8_t slot;
		uint8_t phase_add, phase_sub, freq_add, freq_sub;
>>>>>>> upstream/master
		attotime ctime;

		attotime delays[38];

		attotime write_start_time;
		attotime write_buffer[32];
		int write_position;

		void set_clock(const attotime &period);
		void reset(const attotime &when);
		int get_next_bit(attotime &tm, floppy_image_device *floppy, const attotime &limit);
		bool write_next_bit(bool bit, attotime &tm, floppy_image_device *floppy, const attotime &limit);
		void start_writing(const attotime &tm);
		void commit(floppy_image_device *floppy, const attotime &tm);
		void stop_writing(floppy_image_device *floppy, const attotime &tm);
	};

	struct live_info {
		attotime tm;
		int state, next_state;
<<<<<<< HEAD
		UINT16 shift_reg;
=======
		uint16_t shift_reg;
>>>>>>> upstream/master
		int bit_counter;
		pll_t pll;
	};

	devcb_write_line m_write_index;

	floppy_image_device *floppy;
	floppy_image_device *floppy_devices[4];

	live_info cur_live, checkpoint_live;

	emu_timer *t_gen;
<<<<<<< HEAD
	UINT16 dsklen, pre_dsklen, dsksync, dskbyt, adkcon, dmacon;
	UINT32 dskpt;
	UINT16 dma_value;
=======
	uint16_t dsklen, pre_dsklen, dsksync, dskbyt, adkcon, dmacon;
	uint32_t dskpt;
	uint16_t dma_value;
>>>>>>> upstream/master

	int dma_state;

	void setup_leds();
	void index_callback(floppy_image_device *floppy, int state);
	bool dma_enabled();
	void dma_check();
	void dma_done();
<<<<<<< HEAD
	void dma_write(UINT16 value);
	UINT16 dma_read();
=======
	void dma_write(uint16_t value);
	uint16_t dma_read();
>>>>>>> upstream/master

	void live_start();
	void checkpoint();
	void rollback();
	void live_delay(int state);
	void live_sync();
	void live_abort();
	void live_run(const attotime &limit = attotime::never);
};

<<<<<<< HEAD
extern const device_type AMIGA_FDC;

#endif /* AMIGAFDC_H */
=======
DECLARE_DEVICE_TYPE(AMIGA_FDC, amiga_fdc_device)

#endif // MAME_MACHINE_AMIGAFDC_H
>>>>>>> upstream/master
