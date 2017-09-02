// license:BSD-3-Clause
// copyright-holders:David Haywood
/************************************************************************************

    Bellfruit dotmatrix driver, (under heavy construction !!!)

*************************************************************************************/
<<<<<<< HEAD
#ifndef BFM_DM01
#define BFM_DM01

#define DM_BYTESPERROW 9

#define MCFG_BF_DM01_BUSY_CB(_devcb) \
	devcb = &bfmdm01_device::set_busy_callback(*device, DEVCB_##_devcb);

class bfmdm01_device : public device_t
{
public:
	bfmdm01_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~bfmdm01_device() {}

	template<class _Object> static devcb_base &set_busy_callback(device_t &device, _Object object) { return downcast<bfmdm01_device &>(device).m_busy_cb.set_callback(object); }
=======
#ifndef MAME_VIDEO_BFM_DM01
#define MAME_VIDEO_BFM_DM01

#pragma once

#include "screen.h"

#define MCFG_BFM_DM01_BUSY_CB(_devcb) \
	devcb = &bfm_dm01_device::set_busy_callback(*device, DEVCB_##_devcb);

class bfm_dm01_device : public device_t
{
public:
	bfm_dm01_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	~bfm_dm01_device() {}

	template <class Object> static devcb_base &set_busy_callback(device_t &device, Object &&cb) { return downcast<bfm_dm01_device &>(device).m_busy_cb.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( control_r );
	DECLARE_WRITE8_MEMBER( control_w );
	DECLARE_READ8_MEMBER( mux_r );
	DECLARE_WRITE8_MEMBER( mux_w );
	DECLARE_READ8_MEMBER( comm_r );
	DECLARE_WRITE8_MEMBER( comm_w );
	DECLARE_READ8_MEMBER( unknown_r );
	DECLARE_WRITE8_MEMBER( unknown_w );

<<<<<<< HEAD
	void writedata(UINT8 data);
=======
	void writedata(uint8_t data);
>>>>>>> upstream/master
	int busy(void);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

private:
=======
	virtual void device_add_mconfig(machine_config &config) override;
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	static constexpr unsigned BYTES_PER_ROW = 9;

	required_device<cpu_device> m_matrixcpu;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;

>>>>>>> upstream/master
	// internal state
	int m_data_avail;
	int m_control;
	int m_xcounter;
	int m_segbuffer[65];
	int m_busy;

<<<<<<< HEAD
	UINT8 m_scanline[DM_BYTESPERROW];
	UINT8 m_comdata;
=======
	uint8_t m_scanline[BYTES_PER_ROW];
	uint8_t m_comdata;
>>>>>>> upstream/master

	devcb_write_line m_busy_cb;

	int read_data(void);
<<<<<<< HEAD
};

extern const device_type BF_DM01;

ADDRESS_MAP_EXTERN( bfm_dm01_memmap,8 );

#endif
=======

	bitmap_ind16 m_tmpbitmap;

	INTERRUPT_GEN_MEMBER(nmi_line_assert);

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
};

DECLARE_DEVICE_TYPE(BFM_DM01, bfm_dm01_device)

#endif // MAME_VIDEO_BFM_DM01
>>>>>>> upstream/master
