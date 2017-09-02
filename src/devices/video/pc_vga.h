// license:BSD-3-Clause
// copyright-holders:Nathan Woods, Peter Trauner, Angelo Salese
/***************************************************************************

    pc_vga.h

    PC standard VGA adaptor

***************************************************************************/

<<<<<<< HEAD
#ifndef PC_VGA_H
#define PC_VGA_H
=======
#ifndef MAME_VIDEO_PC_VGA_H
#define MAME_VIDEO_PC_VGA_H

#include "screen.h"
>>>>>>> upstream/master

MACHINE_CONFIG_EXTERN( pcvideo_vga );
MACHINE_CONFIG_EXTERN( pcvideo_trident_vga );
MACHINE_CONFIG_EXTERN( pcvideo_gamtor_vga );
MACHINE_CONFIG_EXTERN( pcvideo_s3_vga );

<<<<<<< HEAD
enum
{
	SCREEN_OFF = 0,
	TEXT_MODE,
	VGA_MODE,
	EGA_MODE,
	CGA_MODE,
	MONO_MODE,
	RGB8_MODE,
	RGB15_MODE,
	RGB16_MODE,
	RGB24_MODE,
	RGB32_MODE
};

// ======================> vga_device

class vga_device :  public device_t
=======
// ======================> vga_device

class vga_device : public device_t
>>>>>>> upstream/master
{
	friend class ibm8514a_device;

public:
	// construction/destruction
<<<<<<< HEAD
	vga_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	vga_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	virtual void zero();
	virtual UINT32 screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
=======
	vga_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void zero();
	virtual uint32_t screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master

	virtual READ8_MEMBER(port_03b0_r);
	virtual WRITE8_MEMBER(port_03b0_w);
	virtual READ8_MEMBER(port_03c0_r);
	virtual WRITE8_MEMBER(port_03c0_w);
	virtual READ8_MEMBER(port_03d0_r);
	virtual WRITE8_MEMBER(port_03d0_w);
	virtual READ8_MEMBER(mem_r);
	virtual WRITE8_MEMBER(mem_w);
	virtual READ8_MEMBER(mem_linear_r);
	virtual WRITE8_MEMBER(mem_linear_w);
	virtual TIMER_CALLBACK_MEMBER(vblank_timer_cb);
<<<<<<< HEAD
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
=======

protected:
	enum
	{
		SCREEN_OFF = 0,
		TEXT_MODE,
		VGA_MODE,
		EGA_MODE,
		CGA_MODE,
		MONO_MODE,
		RGB8_MODE,
		RGB15_MODE,
		RGB16_MODE,
		RGB24_MODE,
		RGB32_MODE
	};

	vga_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

	void vga_vh_text(bitmap_rgb32 &bitmap, const rectangle &cliprect);
	void vga_vh_ega(bitmap_rgb32 &bitmap,  const rectangle &cliprect);
	void vga_vh_vga(bitmap_rgb32 &bitmap, const rectangle &cliprect);
	void vga_vh_cga(bitmap_rgb32 &bitmap, const rectangle &cliprect);
	void vga_vh_mono(bitmap_rgb32 &bitmap, const rectangle &cliprect);
<<<<<<< HEAD
	virtual UINT8 pc_vga_choosevideomode();
	void recompute_params_clock(int divisor, int xtal);
	UINT8 crtc_reg_read(UINT8 index);
	void recompute_params();
	void crtc_reg_write(UINT8 index, UINT8 data);
	void seq_reg_write(UINT8 index, UINT8 data);
	UINT8 vga_vblank();
	READ8_MEMBER(vga_crtc_r);
	WRITE8_MEMBER(vga_crtc_w);
	UINT8 gc_reg_read(UINT8 index);
	void attribute_reg_write(UINT8 index, UINT8 data);
	void gc_reg_write(UINT8 index,UINT8 data);
	virtual UINT16 offset();
	inline UINT8 vga_latch_write(int offs, UINT8 data);
	inline UINT8 rotate_right(UINT8 val) { return (val >> vga.gc.rotate_count) | (val << (8 - vga.gc.rotate_count)); }
	inline UINT8 vga_logical_op(UINT8 data, UINT8 plane, UINT8 mask)
	{
		UINT8 res = 0;

		switch(vga.gc.logical_op & 3)
		{
			case 0: /* NONE */
				res = (data & mask) | (vga.gc.latch[plane] & ~mask);
				break;
			case 1: /* AND */
				res = (data | ~mask) & (vga.gc.latch[plane]);
				break;
			case 2: /* OR */
				res = (data & mask) | (vga.gc.latch[plane]);
				break;
			case 3: /* XOR */
				res = (data & mask) ^ (vga.gc.latch[plane]);
				break;
=======
	virtual uint8_t pc_vga_choosevideomode();
	void recompute_params_clock(int divisor, int xtal);
	uint8_t crtc_reg_read(uint8_t index);
	virtual void recompute_params();
	void crtc_reg_write(uint8_t index, uint8_t data);
	void seq_reg_write(uint8_t index, uint8_t data);
	uint8_t vga_vblank();
	READ8_MEMBER(vga_crtc_r);
	WRITE8_MEMBER(vga_crtc_w);
	uint8_t gc_reg_read(uint8_t index);
	void attribute_reg_write(uint8_t index, uint8_t data);
	void gc_reg_write(uint8_t index,uint8_t data);
	virtual uint16_t offset();
	inline uint8_t vga_latch_write(int offs, uint8_t data);
	inline uint8_t rotate_right(uint8_t val) { return (val >> vga.gc.rotate_count) | (val << (8 - vga.gc.rotate_count)); }
	inline uint8_t vga_logical_op(uint8_t data, uint8_t plane, uint8_t mask)
	{
		uint8_t res = 0;

		switch (vga.gc.logical_op & 3)
		{
		case 0: /* NONE */
			res = (data & mask) | (vga.gc.latch[plane] & ~mask);
			break;
		case 1: /* AND */
			res = (data | ~mask) & (vga.gc.latch[plane]);
			break;
		case 2: /* OR */
			res = (data & mask) | (vga.gc.latch[plane]);
			break;
		case 3: /* XOR */
			res = (data & mask) ^ (vga.gc.latch[plane]);
			break;
>>>>>>> upstream/master
		}

		return res;
	}


	struct
	{
		read8_delegate read_dipswitch;
		struct
		{
			size_t vram_size;
			int seq_regcount;
			int crtc_regcount;
		} svga_intf;

<<<<<<< HEAD
		dynamic_buffer memory;
		UINT32 pens[16]; /* the current 16 pens */

		UINT8 miscellaneous_output;
		UINT8 feature_control;

		struct
		{
			UINT8 index;
			UINT8 data[0x100];
			UINT8 map_mask;
			struct
			{
				UINT8 A, B;
=======
		std::vector<uint8_t> memory;
		uint32_t pens[16]; /* the current 16 pens */

		uint8_t miscellaneous_output;
		uint8_t feature_control;

		struct
		{
			uint8_t index;
			uint8_t data[0x100];
			uint8_t map_mask;
			struct
			{
				uint8_t A, B;
>>>>>>> upstream/master
			}char_sel;
		} sequencer;

		/* An empty comment at the start of the line indicates that register is currently unused */
		struct
		{
<<<<<<< HEAD
			UINT8 index;
			UINT8 data[0x100];
			UINT16 horz_total;
			UINT16 horz_disp_end;
	/**/    UINT8 horz_blank_start;
	/**/    UINT8 horz_blank_end;
	/**/    UINT8 horz_retrace_start;
	/**/    UINT8 horz_retrace_skew;
	/**/    UINT8 horz_retrace_end;
	/**/    UINT8 disp_enable_skew;
	/**/    UINT8 evra;
			UINT16 vert_total;
			UINT16 vert_disp_end;
	/**/    UINT16 vert_retrace_start;
	/**/    UINT8 vert_retrace_end;
	/**/    UINT16 vert_blank_start;
			UINT16 line_compare;
	/**/    UINT32 cursor_addr;
	/**/    UINT8 byte_panning;
	/**/    UINT8 preset_row_scan;
			UINT8 scan_doubling;
	/**/    UINT8 maximum_scan_line;
	/**/    UINT8 cursor_enable;
	/**/    UINT8 cursor_scan_start;
	/**/    UINT8 cursor_skew;
	/**/    UINT8 cursor_scan_end;
			UINT32 start_addr;
			UINT32 start_addr_latch;
	/**/    UINT8 protect_enable;
	/**/    UINT8 bandwidth;
	/**/    UINT16 offset;
	/**/    UINT8 word_mode;
	/**/    UINT8 dw;
	/**/    UINT8 div4;
	/**/    UINT8 underline_loc;
	/**/    UINT16 vert_blank_end;
			UINT8 sync_en;
	/**/    UINT8 aw;
	/**/    UINT8 div2;
	/**/    UINT8 sldiv;
	/**/    UINT8 map14;
	/**/    UINT8 map13;
	/**/    UINT8 irq_clear;
	/**/    UINT8 irq_disable;
=======
			uint8_t index;
			uint8_t data[0x100];
			uint16_t horz_total;
			uint16_t horz_disp_end;
	/**/    uint8_t horz_blank_start;
	/**/    uint8_t horz_blank_end;
	/**/    uint8_t horz_retrace_start;
	/**/    uint8_t horz_retrace_skew;
	/**/    uint8_t horz_retrace_end;
	/**/    uint8_t disp_enable_skew;
	/**/    uint8_t evra;
			uint16_t vert_total;
			uint16_t vert_disp_end;
	/**/    uint16_t vert_retrace_start;
	/**/    uint8_t vert_retrace_end;
			uint16_t vert_blank_start;
			uint16_t line_compare;
			uint32_t cursor_addr;
	/**/    uint8_t byte_panning;
			uint8_t preset_row_scan;
			uint8_t scan_doubling;
			uint8_t maximum_scan_line;
			uint8_t cursor_enable;
			uint8_t cursor_scan_start;
	/**/    uint8_t cursor_skew;
			uint8_t cursor_scan_end;
			uint32_t start_addr;
			uint32_t start_addr_latch;
			uint8_t protect_enable;
	/**/    uint8_t bandwidth;
			uint16_t offset;
			uint8_t word_mode;
			uint8_t dw;
	/**/    uint8_t div4;
	/**/    uint8_t underline_loc;
			uint16_t vert_blank_end;
			uint8_t sync_en;
	/**/    uint8_t aw;
			uint8_t div2;
	/**/    uint8_t sldiv;
	/**/    uint8_t map14;
	/**/    uint8_t map13;
	/**/    uint8_t irq_clear;
	/**/    uint8_t irq_disable;
>>>>>>> upstream/master
		} crtc;

		struct
		{
<<<<<<< HEAD
			UINT8 index;
			UINT8 latch[4];
			UINT8 set_reset;
			UINT8 enable_set_reset;
			UINT8 color_compare;
			UINT8 logical_op;
			UINT8 rotate_count;
			UINT8 shift256;
			UINT8 shift_reg;
			UINT8 read_map_sel;
			UINT8 read_mode;
			UINT8 write_mode;
			UINT8 color_dont_care;
			UINT8 bit_mask;
			UINT8 alpha_dis;
			UINT8 memory_map_sel;
			UINT8 host_oe;
			UINT8 chain_oe;
=======
			uint8_t index;
			uint8_t latch[4];
			uint8_t set_reset;
			uint8_t enable_set_reset;
			uint8_t color_compare;
			uint8_t logical_op;
			uint8_t rotate_count;
			uint8_t shift256;
			uint8_t shift_reg;
			uint8_t read_map_sel;
			uint8_t read_mode;
			uint8_t write_mode;
			uint8_t color_dont_care;
			uint8_t bit_mask;
			uint8_t alpha_dis;
			uint8_t memory_map_sel;
			uint8_t host_oe;
			uint8_t chain_oe;
>>>>>>> upstream/master
		} gc;

		struct
		{
<<<<<<< HEAD
			UINT8 index, data[0x15]; int state;
			UINT8 prot_bit;
			UINT8 pel_shift;
			UINT8 pel_shift_latch;
		} attribute;


		struct {
			UINT8 read_index, write_index, mask;
			int read;
			int state;
			struct { UINT8 red, green, blue; } color[0x100];
=======
			uint8_t index, data[0x15]; int state;
			uint8_t prot_bit;
			uint8_t pel_shift;
			uint8_t pel_shift_latch;
		} attribute;

		struct {
			uint8_t read_index, write_index, mask;
			int read;
			int state;
			uint8_t color[0x300]; /* flat RGB triplets */
>>>>>>> upstream/master
			int dirty;
		} dac;

		struct {
<<<<<<< HEAD
			UINT8 visible;
		} cursor;

		/* oak vga */
		struct { UINT8 reg; } oak;
=======
			uint8_t visible;
		} cursor;

		/* oak vga */
		struct { uint8_t reg; } oak;
>>>>>>> upstream/master
	} vga;

	emu_timer *m_vblank_timer;
	required_device<palette_device> m_palette;
	required_device<screen_device> m_screen;
};


// device type definition
<<<<<<< HEAD
extern const device_type VGA;
=======
DECLARE_DEVICE_TYPE(VGA, vga_device)
>>>>>>> upstream/master

// ======================> svga_device

class svga_device :  public vga_device
{
public:
<<<<<<< HEAD
	// construction/destruction
	svga_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	virtual void zero();
	virtual UINT32 screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
protected:
=======
	virtual void zero() override;
	virtual uint32_t screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect) override;

protected:
	// construction/destruction
	svga_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

>>>>>>> upstream/master
	void svga_vh_rgb8(bitmap_rgb32 &bitmap, const rectangle &cliprect);
	void svga_vh_rgb15(bitmap_rgb32 &bitmap, const rectangle &cliprect);
	void svga_vh_rgb16(bitmap_rgb32 &bitmap, const rectangle &cliprect);
	void svga_vh_rgb24(bitmap_rgb32 &bitmap, const rectangle &cliprect);
	void svga_vh_rgb32(bitmap_rgb32 &bitmap, const rectangle &cliprect);
<<<<<<< HEAD
	virtual UINT8 pc_vga_choosevideomode();
	virtual void device_start();
	struct
	{
		UINT8 bank_r,bank_w;
		UINT8 rgb8_en;
		UINT8 rgb15_en;
		UINT8 rgb16_en;
		UINT8 rgb24_en;
		UINT8 rgb32_en;
		UINT8 id;
	}svga;
private:
=======
	virtual uint8_t pc_vga_choosevideomode() override;
	virtual void device_start() override;
	struct
	{
		uint8_t bank_r,bank_w;
		uint8_t rgb8_en;
		uint8_t rgb15_en;
		uint8_t rgb16_en;
		uint8_t rgb24_en;
		uint8_t rgb32_en;
		uint8_t id;
	} svga;
>>>>>>> upstream/master
};

// ======================> ibm8514_device

<<<<<<< HEAD
class ibm8514a_device :  public device_t
{
public:
	ibm8514a_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	ibm8514a_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
class ibm8514a_device : public device_t
{
public:
	ibm8514a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	void set_vga(const char* tag) { m_vga_tag.assign(tag); }
	void set_vga_owner() { m_vga = dynamic_cast<vga_device*>(owner()); }

	void enabled();

	READ16_MEMBER(ibm8514_gpstatus_r);
	WRITE16_MEMBER(ibm8514_cmd_w);
	READ16_MEMBER(ibm8514_line_error_r);
	WRITE16_MEMBER(ibm8514_line_error_w);
	READ16_MEMBER(ibm8514_status_r);
	WRITE16_MEMBER(ibm8514_htotal_w);
	READ16_MEMBER(ibm8514_substatus_r);
	WRITE16_MEMBER(ibm8514_subcontrol_w);
	READ16_MEMBER(ibm8514_subcontrol_r);
	READ16_MEMBER(ibm8514_htotal_r);
	READ16_MEMBER(ibm8514_vtotal_r);
	WRITE16_MEMBER(ibm8514_vtotal_w);
	READ16_MEMBER(ibm8514_vdisp_r);
	WRITE16_MEMBER(ibm8514_vdisp_w);
	READ16_MEMBER(ibm8514_vsync_r);
	WRITE16_MEMBER(ibm8514_vsync_w);
	READ16_MEMBER(ibm8514_desty_r);
	WRITE16_MEMBER(ibm8514_desty_w);
	READ16_MEMBER(ibm8514_destx_r);
	WRITE16_MEMBER(ibm8514_destx_w);
	READ16_MEMBER(ibm8514_ssv_r);
	WRITE16_MEMBER(ibm8514_ssv_w);
	READ16_MEMBER(ibm8514_currentx_r);
	WRITE16_MEMBER(ibm8514_currentx_w);
	READ16_MEMBER(ibm8514_currenty_r);
	WRITE16_MEMBER(ibm8514_currenty_w);
	READ16_MEMBER(ibm8514_width_r);
	WRITE16_MEMBER(ibm8514_width_w);
	READ16_MEMBER(ibm8514_fgcolour_r);
	WRITE16_MEMBER(ibm8514_fgcolour_w);
	READ16_MEMBER(ibm8514_bgcolour_r);
	WRITE16_MEMBER(ibm8514_bgcolour_w);
	READ16_MEMBER(ibm8514_multifunc_r);
	WRITE16_MEMBER(ibm8514_multifunc_w);
	READ16_MEMBER(ibm8514_backmix_r);
	WRITE16_MEMBER(ibm8514_backmix_w);
	READ16_MEMBER(ibm8514_foremix_r);
	WRITE16_MEMBER(ibm8514_foremix_w);
	READ16_MEMBER(ibm8514_pixel_xfer_r);
	WRITE16_MEMBER(ibm8514_pixel_xfer_w);
	READ16_MEMBER(ibm8514_read_mask_r);
	WRITE16_MEMBER(ibm8514_read_mask_w);
	READ16_MEMBER(ibm8514_write_mask_r);
	WRITE16_MEMBER(ibm8514_write_mask_w);
	void ibm8514_wait_draw();
	struct
	{
<<<<<<< HEAD
		UINT16 htotal;  // Horizontal total (9 bits)
		UINT16 vtotal;  // Vertical total adjust (3 bits), Vertical total base (9 bit)
		UINT16 vdisp;
		UINT16 vsync;
		UINT16 subctrl;
		UINT16 substatus;
		UINT16 ssv;
		UINT16 ec0;
		UINT16 ec1;
		UINT16 ec2;
		UINT16 ec3;
		bool gpbusy;
		bool data_avail;
		INT16 dest_x;
		INT16 dest_y;
		INT16 curr_x;
		INT16 curr_y;
		INT16 prev_x;
		INT16 prev_y;
		INT16 line_axial_step;
		INT16 line_diagonal_step;
		INT16 line_errorterm;
		UINT16 current_cmd;
		UINT16 src_x;
		UINT16 src_y;
		INT16 scissors_left;
		INT16 scissors_right;
		INT16 scissors_top;
		INT16 scissors_bottom;
		UINT16 rect_width;
		UINT16 rect_height;
		UINT32 fgcolour;
		UINT32 bgcolour;
		UINT16 fgmix;
		UINT16 bgmix;
		UINT32 pixel_xfer;
		UINT16 pixel_control;
		UINT8 bus_size;
		UINT8 multifunc_sel;
		UINT16 multifunc_misc;
		UINT32 read_mask;
		UINT32 write_mask;

		int state;
		UINT8 wait_vector_len;
		UINT8 wait_vector_dir;
		bool wait_vector_draw;
		UINT8 wait_vector_count;

	} ibm8514;
protected:
	virtual void device_start();
	virtual void device_config_complete();
	vga_device* m_vga;  // for pass-through
	std::string m_vga_tag;  // pass-through device tag
private:
	void ibm8514_draw_vector(UINT8 len, UINT8 dir, bool draw);
	void ibm8514_wait_draw_ssv();
	void ibm8514_draw_ssv(UINT8 data);
	void ibm8514_wait_draw_vector();
	void ibm8514_write_fg(UINT32 offset);
	void ibm8514_write_bg(UINT32 offset);
	void ibm8514_write(UINT32 offset, UINT32 src);

	//UINT8* m_vram;  // the original 8514/A has it's own VRAM, but most VGA+8514 combination cards will have
					// only one set of VRAM, so this will only be needed in standalone 8514/A cards
	//UINT32 m_vramsize;
};

// device type definition
extern const device_type IBM8514A;
=======
		uint16_t htotal;  // Horizontal total (9 bits)
		uint16_t vtotal;  // Vertical total adjust (3 bits), Vertical total base (9 bit)
		uint16_t vdisp;
		uint16_t vsync;
		uint16_t subctrl;
		uint16_t substatus;
		uint16_t ssv;
		uint16_t ec0;
		uint16_t ec1;
		uint16_t ec2;
		uint16_t ec3;
		bool gpbusy;
		bool data_avail;
		int16_t dest_x;
		int16_t dest_y;
		int16_t curr_x;
		int16_t curr_y;
		int16_t prev_x;
		int16_t prev_y;
		int16_t line_axial_step;
		int16_t line_diagonal_step;
		int16_t line_errorterm;
		uint16_t current_cmd;
		uint16_t src_x;
		uint16_t src_y;
		int16_t scissors_left;
		int16_t scissors_right;
		int16_t scissors_top;
		int16_t scissors_bottom;
		uint16_t rect_width;
		uint16_t rect_height;
		uint32_t fgcolour;
		uint32_t bgcolour;
		uint16_t fgmix;
		uint16_t bgmix;
		uint32_t pixel_xfer;
		uint16_t pixel_control;
		uint8_t bus_size;
		uint8_t multifunc_sel;
		uint16_t multifunc_misc;
		uint32_t read_mask;
		uint32_t write_mask;

		int state;
		uint8_t wait_vector_len;
		uint8_t wait_vector_dir;
		bool wait_vector_draw;
		uint8_t wait_vector_count;

	} ibm8514;

protected:
	ibm8514a_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_config_complete() override;
	vga_device* m_vga;  // for pass-through
	std::string m_vga_tag;  // pass-through device tag
private:
	void ibm8514_draw_vector(uint8_t len, uint8_t dir, bool draw);
	void ibm8514_wait_draw_ssv();
	void ibm8514_draw_ssv(uint8_t data);
	void ibm8514_wait_draw_vector();
	void ibm8514_write_fg(uint32_t offset);
	void ibm8514_write_bg(uint32_t offset);
	void ibm8514_write(uint32_t offset, uint32_t src);

	//uint8_t* m_vram;  // the original 8514/A has it's own VRAM, but most VGA+8514 combination cards will have
					// only one set of VRAM, so this will only be needed in standalone 8514/A cards
	//uint32_t m_vramsize;
};

// device type definition
DECLARE_DEVICE_TYPE(IBM8514A, ibm8514a_device)
>>>>>>> upstream/master

#define MCFG_8514A_ADD(_tag, _param) \
		MCFG_DEVICE_ADD(_tag, IBM8514A, 0) \
		downcast<ibm8514a_device*>(device)->set_vga(_param);

#define MCFG_8514A_ADD_OWNER(_tag) \
		MCFG_DEVICE_ADD(_tag, IBM8514A, 0) \
		downcast<ibm8514a_device*>(device)->set_vga_owner();


<<<<<<< HEAD
class mach8_device :  public ibm8514a_device
{
public:
	mach8_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	mach8_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
class mach8_device : public ibm8514a_device
{
public:
	mach8_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	READ16_MEMBER(mach8_ec0_r);
	WRITE16_MEMBER(mach8_ec0_w);
	READ16_MEMBER(mach8_ec1_r);
	WRITE16_MEMBER(mach8_ec1_w);
	READ16_MEMBER(mach8_ec2_r);
	WRITE16_MEMBER(mach8_ec2_w);
	READ16_MEMBER(mach8_ec3_r);
	WRITE16_MEMBER(mach8_ec3_w);
	READ16_MEMBER(mach8_ext_fifo_r);
	WRITE16_MEMBER(mach8_linedraw_index_w);
	READ16_MEMBER(mach8_bresenham_count_r);
	WRITE16_MEMBER(mach8_bresenham_count_w);
	WRITE16_MEMBER(mach8_linedraw_w);
	READ16_MEMBER(mach8_linedraw_r);
	READ16_MEMBER(mach8_scratch0_r);
	WRITE16_MEMBER(mach8_scratch0_w);
	READ16_MEMBER(mach8_scratch1_r);
	WRITE16_MEMBER(mach8_scratch1_w);
	READ16_MEMBER(mach8_config1_r);
	READ16_MEMBER(mach8_config2_r);
	READ16_MEMBER(mach8_sourcex_r);
	READ16_MEMBER(mach8_sourcey_r);
	WRITE16_MEMBER(mach8_ext_leftscissor_w);
	WRITE16_MEMBER(mach8_ext_topscissor_w);
	READ16_MEMBER(mach8_clksel_r) { return mach8.clksel; }

protected:
<<<<<<< HEAD
	virtual void device_start();
	struct
	{
		UINT16 scratch0;
		UINT16 scratch1;
		UINT16 linedraw;
		UINT16 clksel;
=======
	mach8_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);
	virtual void device_start() override;
	struct
	{
		uint16_t scratch0;
		uint16_t scratch1;
		uint16_t linedraw;
		uint16_t clksel;
>>>>>>> upstream/master
	} mach8;
};

// device type definition
<<<<<<< HEAD
extern const device_type MACH8;
=======
DECLARE_DEVICE_TYPE(MACH8, mach8_device)
>>>>>>> upstream/master

#define MCFG_MACH8_ADD(_tag, _param) \
		MCFG_DEVICE_ADD(_tag, MACH8, 0) \
		downcast<mach8_device*>(device)->set_vga(_param);

#define MCFG_MACH8_ADD_OWNER(_tag) \
		MCFG_DEVICE_ADD(_tag, MACH8, 0) \
		downcast<mach8_device*>(device)->set_vga_owner();

// ======================> tseng_vga_device

class tseng_vga_device :  public svga_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	tseng_vga_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual READ8_MEMBER(port_03b0_r);
	virtual WRITE8_MEMBER(port_03b0_w);
	virtual READ8_MEMBER(port_03c0_r);
	virtual WRITE8_MEMBER(port_03c0_w);
	virtual READ8_MEMBER(port_03d0_r);
	virtual WRITE8_MEMBER(port_03d0_w);
	virtual READ8_MEMBER(mem_r);
	virtual WRITE8_MEMBER(mem_w);

protected:
	virtual void device_start();

private:
	void tseng_define_video_mode();
	UINT8 tseng_crtc_reg_read(UINT8 index);
	void tseng_crtc_reg_write(UINT8 index, UINT8 data);
	UINT8 tseng_seq_reg_read(UINT8 index);
	void tseng_seq_reg_write(UINT8 index, UINT8 data);
	void tseng_attribute_reg_write(UINT8 index, UINT8 data);

	struct
	{
		UINT8 reg_3d8;
		UINT8 dac_ctrl;
		UINT8 dac_state;
		UINT8 horz_overflow;
		UINT8 aux_ctrl;
		bool ext_reg_ena;
		UINT8 misc1;
		UINT8 misc2;
=======
	tseng_vga_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual READ8_MEMBER(port_03b0_r) override;
	virtual WRITE8_MEMBER(port_03b0_w) override;
	virtual READ8_MEMBER(port_03c0_r) override;
	virtual WRITE8_MEMBER(port_03c0_w) override;
	virtual READ8_MEMBER(port_03d0_r) override;
	virtual WRITE8_MEMBER(port_03d0_w) override;
	virtual READ8_MEMBER(mem_r) override;
	virtual WRITE8_MEMBER(mem_w) override;

protected:
	virtual void device_start() override;

private:
	void tseng_define_video_mode();
	uint8_t tseng_crtc_reg_read(uint8_t index);
	void tseng_crtc_reg_write(uint8_t index, uint8_t data);
	uint8_t tseng_seq_reg_read(uint8_t index);
	void tseng_seq_reg_write(uint8_t index, uint8_t data);
	void tseng_attribute_reg_write(uint8_t index, uint8_t data);

	struct
	{
		uint8_t reg_3d8;
		uint8_t dac_ctrl;
		uint8_t dac_state;
		uint8_t horz_overflow;
		uint8_t aux_ctrl;
		bool ext_reg_ena;
		uint8_t misc1;
		uint8_t misc2;
>>>>>>> upstream/master
	}et4k;

};


// device type definition
<<<<<<< HEAD
extern const device_type TSENG_VGA;
=======
DECLARE_DEVICE_TYPE(TSENG_VGA, tseng_vga_device)
>>>>>>> upstream/master


// ======================> ati_vga_device

<<<<<<< HEAD
class ati_vga_device :  public svga_device
{
public:
	// construction/destruction
	ati_vga_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	ati_vga_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	virtual READ8_MEMBER(mem_r);
	virtual WRITE8_MEMBER(mem_w);

	// VGA registers
	virtual READ8_MEMBER(port_03c0_r);
	READ8_MEMBER(ati_port_ext_r);
	WRITE8_MEMBER(ati_port_ext_w);

	virtual machine_config_constructor device_mconfig_additions() const;
	virtual UINT16 offset();

	mach8_device* get_8514() { return m_8514; }
protected:
	virtual void device_start();
=======
class ati_vga_device : public svga_device
{
public:
	// construction/destruction
	ati_vga_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual READ8_MEMBER(mem_r) override;
	virtual WRITE8_MEMBER(mem_w) override;

	// VGA registers
	virtual READ8_MEMBER(port_03c0_r) override;
	READ8_MEMBER(ati_port_ext_r);
	WRITE8_MEMBER(ati_port_ext_w);

	virtual uint16_t offset() override;

	mach8_device* get_8514() { return m_8514; }
protected:
	ati_vga_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_add_mconfig(machine_config &config) override;

>>>>>>> upstream/master
private:
	void ati_define_video_mode();
	struct
	{
<<<<<<< HEAD
		UINT8 ext_reg[64];
		UINT8 ext_reg_select;
		UINT8 vga_chip_id;
=======
		uint8_t ext_reg[64];
		uint8_t ext_reg_select;
		uint8_t vga_chip_id;
>>>>>>> upstream/master
	} ati;
	mach8_device* m_8514;
};

// device type definition
<<<<<<< HEAD
extern const device_type ATI_VGA;
=======
DECLARE_DEVICE_TYPE(ATI_VGA, ati_vga_device)
>>>>>>> upstream/master


// ======================> s3_vga_device

<<<<<<< HEAD
class s3_vga_device :  public ati_vga_device
{
public:
	// construction/destruction
	s3_vga_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	s3_vga_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	virtual READ8_MEMBER(port_03b0_r);
	virtual WRITE8_MEMBER(port_03b0_w);
	virtual READ8_MEMBER(port_03c0_r);
	virtual WRITE8_MEMBER(port_03c0_w);
	virtual READ8_MEMBER(port_03d0_r);
	virtual WRITE8_MEMBER(port_03d0_w);
	virtual READ8_MEMBER(mem_r);
	virtual WRITE8_MEMBER(mem_w);

	virtual UINT32 screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);

	virtual machine_config_constructor device_mconfig_additions() const;

	ibm8514a_device* get_8514() { return m_8514; }
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	struct
	{
		UINT8 memory_config;
		UINT8 ext_misc_ctrl_2;
		UINT8 crt_reg_lock;
		UINT8 reg_lock1;
		UINT8 reg_lock2;
		UINT8 enable_8514;
		UINT8 enable_s3d;
		UINT8 cr3a;
		UINT8 cr42;
		UINT8 cr43;
		UINT8 cr53;
		UINT8 id_high;
		UINT8 id_low;
		UINT8 revision;
		UINT8 id_cr30;
		UINT32 strapping;  // power-on strapping bits
		UINT8 sr10;   // MCLK PLL
		UINT8 sr11;   // MCLK PLL
		UINT8 sr12;   // DCLK PLL
		UINT8 sr13;   // DCLK PLL
		UINT8 sr15;   // CLKSYN control 2
		UINT8 sr17;   // CLKSYN test
		UINT8 clk_pll_r;  // individual DCLK PLL values
		UINT8 clk_pll_m;
		UINT8 clk_pll_n;

		// data for memory-mapped I/O
		UINT16 mmio_9ae8;
		UINT16 mmio_bee8;
		UINT16 mmio_96e8;

		// hardware graphics cursor
		UINT8 cursor_mode;
		UINT16 cursor_x;
		UINT16 cursor_y;
		UINT16 cursor_start_addr;
		UINT8 cursor_pattern_x;  // cursor pattern origin
		UINT8 cursor_pattern_y;
		UINT8 cursor_fg[4];
		UINT8 cursor_bg[4];
		UINT8 cursor_fg_ptr;
		UINT8 cursor_bg_ptr;
		UINT8 extended_dac_ctrl;
	} s3;
	virtual UINT16 offset();

private:
	UINT8 s3_crtc_reg_read(UINT8 index);
	void s3_define_video_mode(void);
	void s3_crtc_reg_write(UINT8 index, UINT8 data);
	UINT8 s3_seq_reg_read(UINT8 index);
	void s3_seq_reg_write(UINT8 index, UINT8 data);
=======
class s3_vga_device : public ati_vga_device
{
public:
	// construction/destruction
	s3_vga_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual READ8_MEMBER(port_03b0_r) override;
	virtual WRITE8_MEMBER(port_03b0_w) override;
	virtual READ8_MEMBER(port_03c0_r) override;
	virtual WRITE8_MEMBER(port_03c0_w) override;
	virtual READ8_MEMBER(port_03d0_r) override;
	virtual WRITE8_MEMBER(port_03d0_w) override;
	virtual READ8_MEMBER(mem_r) override;
	virtual WRITE8_MEMBER(mem_w) override;

	virtual uint32_t screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect) override;

	virtual TIMER_CALLBACK_MEMBER(vblank_timer_cb) override;

	ibm8514a_device* get_8514() { return m_8514; }

protected:
	s3_vga_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

	struct
	{
		uint8_t memory_config;
		uint8_t ext_misc_ctrl_2;
		uint8_t crt_reg_lock;
		uint8_t reg_lock1;
		uint8_t reg_lock2;
		uint8_t enable_8514;
		uint8_t enable_s3d;
		uint8_t cr3a;
		uint8_t cr42;
		uint8_t cr43;
		uint8_t cr53;
		uint8_t id_high;
		uint8_t id_low;
		uint8_t revision;
		uint8_t id_cr30;
		uint32_t strapping;  // power-on strapping bits
		uint8_t sr10;   // MCLK PLL
		uint8_t sr11;   // MCLK PLL
		uint8_t sr12;   // DCLK PLL
		uint8_t sr13;   // DCLK PLL
		uint8_t sr15;   // CLKSYN control 2
		uint8_t sr17;   // CLKSYN test
		uint8_t clk_pll_r;  // individual DCLK PLL values
		uint8_t clk_pll_m;
		uint8_t clk_pll_n;

		// data for memory-mapped I/O
		uint16_t mmio_9ae8;
		uint16_t mmio_bee8;
		uint16_t mmio_96e8;

		// hardware graphics cursor
		uint8_t cursor_mode;
		uint16_t cursor_x;
		uint16_t cursor_y;
		uint16_t cursor_start_addr;
		uint8_t cursor_pattern_x;  // cursor pattern origin
		uint8_t cursor_pattern_y;
		uint8_t cursor_fg[4];
		uint8_t cursor_bg[4];
		uint8_t cursor_fg_ptr;
		uint8_t cursor_bg_ptr;
		uint8_t extended_dac_ctrl;
	} s3;
	virtual uint16_t offset() override;

private:
	uint8_t s3_crtc_reg_read(uint8_t index);
	void s3_define_video_mode(void);
	void s3_crtc_reg_write(uint8_t index, uint8_t data);
	uint8_t s3_seq_reg_read(uint8_t index);
	void s3_seq_reg_write(uint8_t index, uint8_t data);
>>>>>>> upstream/master
	ibm8514a_device* m_8514;
};

// device type definition
<<<<<<< HEAD
extern const device_type S3_VGA;
=======
DECLARE_DEVICE_TYPE(S3_VGA, s3_vga_device)
>>>>>>> upstream/master

// ======================> gamtor_vga_device

class gamtor_vga_device :  public svga_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	gamtor_vga_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);


	virtual READ8_MEMBER(port_03b0_r);
	virtual WRITE8_MEMBER(port_03b0_w);
	virtual READ8_MEMBER(port_03c0_r);
	virtual WRITE8_MEMBER(port_03c0_w);
	virtual READ8_MEMBER(port_03d0_r);
	virtual WRITE8_MEMBER(port_03d0_w);
	virtual READ8_MEMBER(mem_r);
	virtual WRITE8_MEMBER(mem_w);

protected:
private:
=======
	gamtor_vga_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);


	virtual READ8_MEMBER(port_03b0_r) override;
	virtual WRITE8_MEMBER(port_03b0_w) override;
	virtual READ8_MEMBER(port_03c0_r) override;
	virtual WRITE8_MEMBER(port_03c0_w) override;
	virtual READ8_MEMBER(port_03d0_r) override;
	virtual WRITE8_MEMBER(port_03d0_w) override;
	virtual READ8_MEMBER(mem_r) override;
	virtual WRITE8_MEMBER(mem_w) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type GAMTOR_VGA;
=======
DECLARE_DEVICE_TYPE(GAMTOR_VGA, gamtor_vga_device)
>>>>>>> upstream/master

/*
  pega notes (paradise)
  build in amstrad pc1640

  ROM_LOAD("40100", 0xc0000, 0x8000, CRC(d2d1f1ae))

  4 additional dipswitches
  seems to have emulation modes at register level
  (mda/hgc lines bit 8 not identical to ega/vga)

  standard ega/vga dipswitches
  00000000  320x200
  00000001  640x200 hanging
  00000010  640x200 hanging
  00000011  640x200 hanging

  00000100  640x350 hanging
  00000101  640x350 hanging EGA mono
  00000110  320x200
  00000111  640x200

  00001000  640x200
  00001001  640x200
  00001010  720x350 partial visible
  00001011  720x350 partial visible

  00001100  320x200
  00001101  320x200
  00001110  320x200
  00001111  320x200

*/

/*
  oak vga (oti 037 chip)
  (below bios patch needed for running)

  ROM_LOAD("oakvga.bin", 0xc0000, 0x8000, CRC(318c5f43))
*/


<<<<<<< HEAD
#endif /* PC_VGA_H */
=======
#endif // MAME_VIDEO_PC_VGA_H
>>>>>>> upstream/master
