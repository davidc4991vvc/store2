// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Eric Smith, Brad Oliver, Bernd Wiebelt, Aaron Giles, Andrew Caldwell
#ifndef __AVGDVG__
#define __AVGDVG__

#define MAXVECT      (10000)
=======
// copyright-holders:Mathis Rosenhauer
// thanks-to:Eric Smith, Brad Oliver, Bernd Wiebelt, Aaron Giles, Andrew Caldwell
#ifndef MAME_VIDEO_AVGDVG_H
#define MAME_VIDEO_AVGDVG_H

#pragma once
>>>>>>> upstream/master

#include "video/vector.h"

#define MCFG_AVGDVG_VECTOR(_tag) \
	avgdvg_device::static_set_vector_tag(*device, "^" _tag);

<<<<<<< HEAD
struct vgvector
{
	int x; int y;
	rgb_t color;
	int intensity;
	int arg1; int arg2;
	int status;
};

=======
>>>>>>> upstream/master
// ======================> avgdvg_device

class avgdvg_device : public device_t
{
public:
<<<<<<< HEAD
	// construction/destruction
	avgdvg_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

=======
>>>>>>> upstream/master
	static void static_set_vector_tag(device_t &device, const char *tag);

	DECLARE_CUSTOM_INPUT_MEMBER(done_r);
	DECLARE_WRITE8_MEMBER(go_w);
	DECLARE_WRITE8_MEMBER(reset_w);

	DECLARE_WRITE16_MEMBER(go_word_w);
	DECLARE_WRITE16_MEMBER(reset_word_w);

	/* Tempest and Quantum use this capability */
	void set_flip_x(int flip);
	void set_flip_y(int flip);

	TIMER_CALLBACK_MEMBER(vg_set_halt_callback);
	TIMER_CALLBACK_MEMBER(run_state_machine);
protected:
<<<<<<< HEAD
=======
	static constexpr unsigned MAXVECT = 10000;

	struct vgvector
	{
		int x; int y;
		rgb_t color;
		int intensity;
		int arg1; int arg2;
		int status;
	};

	// construction/destruction
	avgdvg_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

>>>>>>> upstream/master
	void apply_flipping(int *x, int *y);
	void vg_set_halt(int dummy);

	void vg_flush();
	void vg_add_point_buf(int x, int y, rgb_t color, int intensity);
	void vg_add_clip (int xmin, int ymin, int xmax, int ymax);

	void register_state();

<<<<<<< HEAD
	UINT8 *avgdvg_vectorram;
	size_t avgdvg_vectorram_size;

	UINT8 *avgdvg_colorram;
=======
	uint8_t *avgdvg_vectorram;
	size_t avgdvg_vectorram_size;

	uint8_t *avgdvg_colorram;
>>>>>>> upstream/master


	int xmin, xmax, ymin, ymax;
	int xcenter, ycenter;
	emu_timer *vg_run_timer, *vg_halt_timer;

	int flip_x, flip_y;

	int nvect;
	vgvector vectbuf[MAXVECT];


<<<<<<< HEAD
	UINT16 m_pc;
	UINT8 m_sp;
	UINT16 m_dvx;
	UINT16 m_dvy;
	UINT8 m_dvy12;
	UINT16 m_timer;
	UINT16 m_stack[4];
	UINT16 m_data;

	UINT8 m_state_latch;
	UINT8 m_int_latch;
	UINT8 m_scale;
	UINT8 m_bin_scale;
	UINT8 m_intensity;
	UINT8 m_color;
	UINT8 m_enspkl;
	UINT8 m_spkl_shift;
	UINT8 m_map;

	UINT16 m_hst;
	UINT16 m_lst;
	UINT16 m_izblank;

	UINT8 m_op;
	UINT8 m_halt;
	UINT8 m_sync_halt;

	UINT16 m_xdac_xor;
	UINT16 m_ydac_xor;

	INT32 m_xpos;
	INT32 m_ypos;

	INT32 m_clipx_min;
	INT32 m_clipy_min;
	INT32 m_clipx_max;
	INT32 m_clipy_max;
=======
	uint16_t m_pc;
	uint8_t m_sp;
	uint16_t m_dvx;
	uint16_t m_dvy;
	uint8_t m_dvy12;
	uint16_t m_timer;
	uint16_t m_stack[4];
	uint16_t m_data;

	uint8_t m_state_latch;
	uint8_t m_int_latch;
	uint8_t m_scale;
	uint8_t m_bin_scale;
	uint8_t m_intensity;
	uint8_t m_color;
	uint8_t m_enspkl;
	uint8_t m_spkl_shift;
	uint8_t m_map;

	uint16_t m_hst;
	uint16_t m_lst;
	uint16_t m_izblank;

	uint8_t m_op;
	uint8_t m_halt;
	uint8_t m_sync_halt;

	uint16_t m_xdac_xor;
	uint16_t m_ydac_xor;

	int32_t m_xpos;
	int32_t m_ypos;

	int32_t m_clipx_min;
	int32_t m_clipy_min;
	int32_t m_clipx_max;
	int32_t m_clipy_max;
>>>>>>> upstream/master


	virtual int handler_0() = 0;
	virtual int handler_1() = 0;
	virtual int handler_2() = 0;
	virtual int handler_3() = 0;
	virtual int handler_4() = 0;
	virtual int handler_5() = 0;
	virtual int handler_6() = 0;
	virtual int handler_7() = 0;
<<<<<<< HEAD
	virtual UINT8 state_addr() = 0;
=======
	virtual uint8_t state_addr() = 0;
>>>>>>> upstream/master
	virtual void update_databus() = 0;
	virtual void vggo() = 0;
	virtual void vgrst() = 0;

	required_device<vector_device> m_vector;
};

class dvg_device : public avgdvg_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	dvg_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	void dvg_draw_to(int x, int y, int intensity);

	virtual int handler_0();
	virtual int handler_1();
	virtual int handler_2();
	virtual int handler_3();
	virtual int handler_4();
	virtual int handler_5();
	virtual int handler_6();
	virtual int handler_7();
	virtual UINT8 state_addr();
	virtual void update_databus();
	virtual void vggo();
	virtual void vgrst();

	virtual void device_start();
};

// device type definition
extern const device_type DVG;
=======
	dvg_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	void dvg_draw_to(int x, int y, int intensity);

protected:
	virtual int handler_0() override;
	virtual int handler_1() override;
	virtual int handler_2() override;
	virtual int handler_3() override;
	virtual int handler_4() override;
	virtual int handler_5() override;
	virtual int handler_6() override;
	virtual int handler_7() override;
	virtual uint8_t state_addr() override;
	virtual void update_databus() override;
	virtual void vggo() override;
	virtual void vgrst() override;

	virtual void device_start() override;
};

// device type definition
DECLARE_DEVICE_TYPE(DVG, dvg_device)
>>>>>>> upstream/master

class avg_device : public avgdvg_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	avg_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	avg_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
=======
	avg_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	int avg_common_strobe1();
	int avg_common_strobe2();
	int avg_common_strobe3();

<<<<<<< HEAD
	virtual int handler_0();
	virtual int handler_1();
	virtual int handler_2();
	virtual int handler_3();
	virtual int handler_4();
	virtual int handler_5();
	virtual int handler_6();
	virtual int handler_7();
	virtual UINT8 state_addr();
	virtual void update_databus();
	virtual void vggo();
	virtual void vgrst();

	virtual void device_start();
	void avg_start_common();
};

// device type definition
extern const device_type AVG;
=======
protected:
	avg_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual int handler_0() override;
	virtual int handler_1() override;
	virtual int handler_2() override;
	virtual int handler_3() override;
	virtual int handler_4() override;
	virtual int handler_5() override;
	virtual int handler_6() override;
	virtual int handler_7() override;
	virtual uint8_t state_addr() override;
	virtual void update_databus() override;
	virtual void vggo() override;
	virtual void vgrst() override;

	virtual void device_start() override;
};

// device type definition
DECLARE_DEVICE_TYPE(AVG, avg_device)
>>>>>>> upstream/master

class avg_tempest_device : public avg_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	avg_tempest_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual int handler_6();
	virtual int handler_7();
=======
	avg_tempest_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual int handler_6() override;
	virtual int handler_7() override;
>>>>>>> upstream/master
	//virtual void vggo();
};

// device type definition
<<<<<<< HEAD
extern const device_type AVG_TEMPEST;
=======
DECLARE_DEVICE_TYPE(AVG_TEMPEST, avg_tempest_device)
>>>>>>> upstream/master

class avg_mhavoc_device : public avg_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	avg_mhavoc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual int handler_1();
	virtual int handler_6();
	virtual int handler_7();
	virtual void update_databus();
	virtual void vgrst();
};

// device type definition
extern const device_type AVG_MHAVOC;
=======
	avg_mhavoc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual int handler_1() override;
	virtual int handler_6() override;
	virtual int handler_7() override;
	virtual void update_databus() override;
	virtual void vgrst() override;
};

// device type definition
DECLARE_DEVICE_TYPE(AVG_MHAVOC, avg_mhavoc_device)
>>>>>>> upstream/master

class avg_starwars_device : public avg_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	avg_starwars_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual int handler_6();
	virtual int handler_7();
	virtual void update_databus();
};

// device type definition
extern const device_type AVG_STARWARS;
=======
	avg_starwars_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual int handler_6() override;
	virtual int handler_7() override;
	virtual void update_databus() override;
};

// device type definition
DECLARE_DEVICE_TYPE(AVG_STARWARS, avg_starwars_device)
>>>>>>> upstream/master

class avg_quantum_device : public avg_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	avg_quantum_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual int handler_0();
	virtual int handler_1();
	virtual int handler_2();
	virtual int handler_3();
	virtual int handler_4();
	virtual int handler_5();
	virtual int handler_6();
	virtual int handler_7();
	virtual void update_databus();
	virtual void vggo();
};

// device type definition
extern const device_type AVG_QUANTUM;
=======
	avg_quantum_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual int handler_0() override;
	virtual int handler_1() override;
	virtual int handler_2() override;
	virtual int handler_3() override;
	virtual int handler_4() override;
	virtual int handler_5() override;
	virtual int handler_6() override;
	virtual int handler_7() override;
	virtual void update_databus() override;
	virtual void vggo() override;
};

// device type definition
DECLARE_DEVICE_TYPE(AVG_QUANTUM, avg_quantum_device)
>>>>>>> upstream/master

class avg_bzone_device : public avg_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	avg_bzone_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual int handler_1();
	virtual int handler_6();
	virtual int handler_7();
};

// device type definition
extern const device_type AVG_BZONE;
=======
	avg_bzone_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual int handler_1() override;
	virtual int handler_6() override;
	virtual int handler_7() override;
};

// device type definition
DECLARE_DEVICE_TYPE(AVG_BZONE, avg_bzone_device)
>>>>>>> upstream/master

class avg_tomcat_device : public avg_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	avg_tomcat_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual int handler_6();
	virtual int handler_7();
};

// device type definition
extern const device_type AVG_TOMCAT;


#endif
=======
	avg_tomcat_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual int handler_6() override;
	virtual int handler_7() override;
};

// device type definition
DECLARE_DEVICE_TYPE(AVG_TOMCAT, avg_tomcat_device)


#endif // MAME_VIDEO_AVGDVG_H
>>>>>>> upstream/master
