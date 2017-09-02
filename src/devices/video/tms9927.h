// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/**********************************************************************

    TI TMS9927 and compatible CRT controller emulation

**********************************************************************/

<<<<<<< HEAD
#ifndef __TMS9927__
#define __TMS9927__
=======
#ifndef MAME_VIDEO_TMS9927_H
#define MAME_VIDEO_TMS9927_H
>>>>>>> upstream/master


#define MCFG_TMS9927_VSYN_CALLBACK(_write) \
	devcb = &tms9927_device::set_vsyn_wr_callback(*device, DEVCB_##_write);

#define MCFG_TMS9927_CHAR_WIDTH(_pixels) \
	tms9927_device::set_char_width(*device, _pixels);

#define MCFG_TMS9927_REGION(_tag) \
<<<<<<< HEAD
	tms9927_device::set_region_tag(*device, _tag);


class tms9927_device : public device_t,
						public device_video_interface
{
public:
	tms9927_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	tms9927_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	~tms9927_device() {}

	template<class _Object> static devcb_base &set_vsyn_wr_callback(device_t &device, _Object object) { return downcast<tms9927_device &>(device).m_write_vsyn.set_callback(object); }

	static void set_char_width(device_t &device, int pixels) { downcast<tms9927_device &>(device).m_hpixels_per_column = pixels; }
	static void set_region_tag(device_t &device, const char *tag) { downcast<tms9927_device &>(device).m_selfload_region = tag; }
=======
	tms9927_device::set_region_tag(*device, "^" _tag);

#define MCFG_TMS9927_OVERSCAN(_left, _right, _top, _bottom) \
	tms9927_device::set_overscan(*device, _left, _right, _top, _bottom);

class tms9927_device : public device_t, public device_video_interface
{
public:
	tms9927_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static devcb_base &set_vsyn_wr_callback(device_t &device, Object &&cb) { return downcast<tms9927_device &>(device).m_write_vsyn.set_callback(std::forward<Object>(cb)); }

	static void set_char_width(device_t &device, int pixels) { downcast<tms9927_device &>(device).m_hpixels_per_column = pixels; }
	static void set_region_tag(device_t &device, const char *tag) { downcast<tms9927_device &>(device).m_selfload.set_tag(tag); }
	static void set_overscan(device_t &device, int left, int right, int top, int bottom) {
		tms9927_device &dev = downcast<tms9927_device &>(device);
		dev.m_overscan_left = left;
		dev.m_overscan_right = right;
		dev.m_overscan_top = top;
		dev.m_overscan_bottom = bottom;
	}
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER(write);
	DECLARE_READ8_MEMBER(read);

	int screen_reset();
	int upscroll_offset();
	int cursor_bounds(rectangle &bounds);

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_start();
	virtual void device_stop();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	tms9927_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_stop() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
>>>>>>> upstream/master

private:
	enum
	{
		TIMER_VSYNC
	};

	void state_postload();
<<<<<<< HEAD
	void recompute_parameters(int postload);
=======
	void recompute_parameters(bool postload);
>>>>>>> upstream/master
	void generic_access(address_space &space, offs_t offset);

	devcb_write_line m_write_vsyn;
	int m_hpixels_per_column;         /* number of pixels per video memory address */
<<<<<<< HEAD
	const char *m_selfload_region;    /* name of the region with self-load data */

	// internal state
	const UINT8 *m_selfload;

	/* live state */
	UINT32  m_clock;
	UINT8   m_reg[9];
	UINT8   m_start_datarow;
	UINT8   m_reset;

	/* derived state; no need to save */
	UINT8   m_valid_config;
	UINT16  m_total_hpix, m_total_vpix;
	UINT16  m_visible_hpix, m_visible_vpix;
=======
	uint16_t  m_overscan_left;
	uint16_t  m_overscan_right;
	uint16_t  m_overscan_top;
	uint16_t  m_overscan_bottom;

	// internal state
	optional_region_ptr<uint8_t> m_selfload;

	/* live state */
	uint32_t  m_clock;
	uint8_t   m_reg[9];
	uint8_t   m_start_datarow;
	uint8_t   m_reset;

	/* derived state; no need to save */
	uint8_t   m_valid_config;
	uint16_t  m_total_hpix, m_total_vpix;
	uint16_t  m_visible_hpix, m_visible_vpix;
>>>>>>> upstream/master

	int m_vsyn;

	emu_timer *m_vsync_timer;
};

<<<<<<< HEAD
extern const device_type TMS9927;
=======
>>>>>>> upstream/master

class crt5027_device : public tms9927_device
{
public:
<<<<<<< HEAD
	crt5027_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

extern const device_type CRT5027;
=======
	crt5027_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

>>>>>>> upstream/master

class crt5037_device : public tms9927_device
{
public:
<<<<<<< HEAD
	crt5037_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

extern const device_type CRT5037;
=======
	crt5037_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

>>>>>>> upstream/master

class crt5057_device : public tms9927_device
{
public:
<<<<<<< HEAD
	crt5057_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

extern const device_type CRT5057;


#endif
=======
	crt5057_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};


DECLARE_DEVICE_TYPE(TMS9927, tms9927_device)
DECLARE_DEVICE_TYPE(CRT5027, crt5027_device)
DECLARE_DEVICE_TYPE(CRT5037, crt5037_device)
DECLARE_DEVICE_TYPE(CRT5057, crt5057_device)

#endif // MAME_VIDEO_TMS9927_H
>>>>>>> upstream/master
