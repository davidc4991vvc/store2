// license:BSD-3-Clause
// copyright-holders:David Haywood
/* 32X */
<<<<<<< HEAD


// Fifa96 needs the CPUs swapped for the gameplay to enter due to some race conditions
// when using the DRC core.  Needs further investigation, the non-DRC core works either
// way
#define _32X_SWAP_MASTER_SLAVE_HACK
#define _32X_COMMS_PORT_SYNC 0
#define MAX_HPOSITION 480
/* need to make some pwm stuff part of device */
#define PWM_FIFO_SIZE m_pwm_tm_reg // guess, Marsch calls this register as FIFO width
#define PWM_CLOCK m_32x_pal ? ((MASTER_CLOCK_PAL*3) / 7) : ((MASTER_CLOCK_NTSC*3) / 7)



#define SH2_VRES_IRQ_LEVEL 14
#define SH2_VINT_IRQ_LEVEL 12
#define SH2_HINT_IRQ_LEVEL 10
#define SH2_CINT_IRQ_LEVEL 8
#define SH2_PINT_IRQ_LEVEL 6

#define MASTER_CLOCK_NTSC 53693175
#define MASTER_CLOCK_PAL  53203424
=======
#ifndef MAME_MACHINE_MEGA32X_H
#define MAME_MACHINE_MEGA32X_H

#pragma once
>>>>>>> upstream/master

#include "cpu/sh2/sh2.h"
#include "cpu/sh2/sh2comn.h"
#include "sound/dac.h"

class sega_32x_device : public device_t
{
public:
<<<<<<< HEAD
	sega_32x_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	required_device<sh2_device> m_master_cpu;
	required_device<sh2_device> m_slave_cpu;
	required_device<dac_device> m_lch_pwm;
	required_device<dac_device> m_rch_pwm;

	required_shared_ptr<UINT32> m_sh2_shared;

=======
>>>>>>> upstream/master
	void pause_cpu();

	// set some variables at start, depending on region (shall be moved to a device interface?)
	void set_framerate(int rate) { m_framerate = rate; }
	void set_32x_pal(bool pal) { m_32x_pal = pal ? 1 : 0; }
	void set_total_scanlines(int total) { m_base_total_scanlines = total; }     // this get set at start only
<<<<<<< HEAD
	void update_total_scanlines(bool mode3) { m_total_scanlines = mode3 ? (m_base_total_scanlines * 2) : m_base_total_scanlines; }  // this gets set at each EOF
=======

	void screen_eof(bool mode3)
	{
		m_32x_vblank_flag = 0;
		m_32x_hcount_compare_val = -1;
		update_total_scanlines(mode3);
	}
>>>>>>> upstream/master

	// static configuration
	static void static_set_palette_tag(device_t &device, const char *tag);

	DECLARE_READ32_MEMBER( _32x_sh2_master_4000_common_4002_r );
	DECLARE_READ32_MEMBER( _32x_sh2_slave_4000_common_4002_r );
	DECLARE_READ32_MEMBER( _32x_sh2_common_4004_common_4006_r );
	DECLARE_WRITE32_MEMBER( _32x_sh2_master_4000_common_4002_w );
	DECLARE_WRITE32_MEMBER( _32x_sh2_slave_4000_common_4002_w );
	DECLARE_WRITE32_MEMBER( _32x_sh2_common_4004_common_4006_w );
	DECLARE_WRITE32_MEMBER( _32x_sh2_master_4014_master_4016_w );
	DECLARE_WRITE32_MEMBER( _32x_sh2_master_4018_master_401a_w );
	DECLARE_WRITE32_MEMBER( _32x_sh2_master_401c_master_401e_w );
	DECLARE_WRITE32_MEMBER( _32x_sh2_slave_4014_slave_4016_w );
	DECLARE_WRITE32_MEMBER( _32x_sh2_slave_4018_slave_401a_w );
	DECLARE_WRITE32_MEMBER( _32x_sh2_slave_401c_slave_401e_w );


	DECLARE_READ16_MEMBER( _32x_68k_palette_r );
	DECLARE_WRITE16_MEMBER( _32x_68k_palette_w );
	DECLARE_READ16_MEMBER( _32x_68k_dram_r );
	DECLARE_WRITE16_MEMBER( _32x_68k_dram_w );
	DECLARE_READ16_MEMBER( _32x_68k_dram_overwrite_r );
	DECLARE_WRITE16_MEMBER( _32x_68k_dram_overwrite_w );
	DECLARE_READ16_MEMBER( _32x_68k_a15106_r );
	DECLARE_WRITE16_MEMBER( _32x_68k_a15106_w );
	DECLARE_READ16_MEMBER( _32x_dreq_common_r );
	DECLARE_WRITE16_MEMBER( _32x_dreq_common_w );
	DECLARE_READ16_MEMBER( _32x_68k_a1511a_r );
	DECLARE_WRITE16_MEMBER( _32x_68k_a1511a_w );
	DECLARE_READ16_MEMBER( _32x_68k_m_hint_vector_r );
	DECLARE_WRITE16_MEMBER( _32x_68k_m_hint_vector_w );
	DECLARE_READ16_MEMBER( _32x_68k_MARS_r );
	DECLARE_READ16_MEMBER( _32x_68k_a15100_r );
	DECLARE_WRITE16_MEMBER( _32x_68k_a15100_w );
	DECLARE_READ16_MEMBER( _32x_68k_a15102_r );
	DECLARE_WRITE16_MEMBER( _32x_68k_a15102_w );
	DECLARE_READ16_MEMBER( _32x_68k_a15104_r );
	DECLARE_WRITE16_MEMBER( _32x_68k_a15104_w );
	DECLARE_READ16_MEMBER( _32x_68k_m_commsram_r );
	DECLARE_WRITE16_MEMBER( _32x_68k_m_commsram_w );
	DECLARE_READ16_MEMBER( _32x_pwm_r );
	DECLARE_WRITE16_MEMBER( _32x_pwm_w );
	DECLARE_WRITE16_MEMBER( _32x_68k_pwm_w );
	DECLARE_READ16_MEMBER( _32x_common_vdp_regs_r );
	DECLARE_WRITE16_MEMBER( _32x_common_vdp_regs_w );
	DECLARE_READ16_MEMBER( _32x_sh2_master_4000_r );
	DECLARE_WRITE16_MEMBER( _32x_sh2_master_4000_w );
	DECLARE_READ16_MEMBER( _32x_sh2_slave_4000_r );
	DECLARE_WRITE16_MEMBER( _32x_sh2_slave_4000_w );
	DECLARE_READ16_MEMBER( _32x_sh2_common_4002_r );
	DECLARE_WRITE16_MEMBER( _32x_sh2_common_4002_w );
	DECLARE_READ16_MEMBER( _32x_sh2_common_4004_r );
	DECLARE_WRITE16_MEMBER( _32x_sh2_common_4004_w );
	DECLARE_READ16_MEMBER( _32x_sh2_common_4006_r );
	DECLARE_WRITE16_MEMBER( _32x_sh2_common_4006_w );
	DECLARE_WRITE16_MEMBER( _32x_sh2_master_4014_w );
	DECLARE_WRITE16_MEMBER( _32x_sh2_slave_4014_w );
	DECLARE_WRITE16_MEMBER( _32x_sh2_master_4016_w );
	DECLARE_WRITE16_MEMBER( _32x_sh2_slave_4016_w );
	DECLARE_WRITE16_MEMBER( _32x_sh2_master_4018_w );
	DECLARE_WRITE16_MEMBER( _32x_sh2_slave_4018_w ) ;
	DECLARE_WRITE16_MEMBER( _32x_sh2_master_401a_w );
	DECLARE_WRITE16_MEMBER( _32x_sh2_slave_401a_w );
	DECLARE_WRITE16_MEMBER( _32x_sh2_master_401c_w );
	DECLARE_WRITE16_MEMBER( _32x_sh2_slave_401c_w );
	DECLARE_WRITE16_MEMBER( _32x_sh2_master_401e_w );
	DECLARE_WRITE16_MEMBER( _32x_sh2_slave_401e_w );

	SH2_DMA_FIFO_DATA_AVAILABLE_CB(_32x_fifo_available_callback);

	void _32x_render_videobuffer_to_screenbuffer_helper(int scanline);
<<<<<<< HEAD
	void _32x_render_videobuffer_to_screenbuffer(int x, UINT32 priority, UINT16 &lineptr);
=======
	void _32x_render_videobuffer_to_screenbuffer(int x, uint32_t priority, uint16_t &lineptr);
>>>>>>> upstream/master
	int sh2_master_pwmint_enable, sh2_slave_pwmint_enable;

	void _32x_check_framebuffer_swap(bool enabled);
	void _32x_check_irqs();
	void _32x_interrupt_cb(int scanline, int irq6);

<<<<<<< HEAD
	/* our main vblank handler resets this */
=======
protected:
	sega_32x_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	required_shared_ptr<uint32_t> m_sh2_shared;

	virtual void device_start() override;
	virtual void device_reset() override;

	void update_total_scanlines(bool mode3) { m_total_scanlines = mode3 ? (m_base_total_scanlines * 2) : m_base_total_scanlines; }  // this gets set at each EOF

	/* our main vblank handler resets this */
	required_device<sh2_device> m_master_cpu;
	required_device<sh2_device> m_slave_cpu;
	required_device<dac_word_interface> m_ldac;
	required_device<dac_word_interface> m_rdac;

>>>>>>> upstream/master
	int m_32x_hcount_compare_val;
	int m_32x_vblank_flag;
	int m_sh2_are_running;
	int m_32x_240mode;
<<<<<<< HEAD
	UINT16 m_32x_a1518a_reg;

	void handle_pwm_callback();
	void calculate_pwm_timer();
	UINT16 m_pwm_ctrl, m_pwm_cycle, m_pwm_tm_reg;
	UINT16 m_cur_lch[0x10],m_cur_rch[0x10];
	UINT16 m_pwm_cycle_reg; //used for latching
	UINT8 m_pwm_timer_tick;
	UINT8 m_lch_index_r, m_rch_index_r, m_lch_index_w, m_rch_index_w;
	UINT16 m_lch_fifo_state, m_rch_fifo_state;


	UINT16 get_hposition(void);

	emu_timer *m_32x_pwm_timer;

protected:
	virtual void device_start();
	virtual void device_reset();

	// optional information overrides
//  virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

=======
	uint16_t m_32x_a1518a_reg;

	TIMER_CALLBACK_MEMBER(handle_pwm_callback);
	void calculate_pwm_timer();
	uint16_t m_pwm_ctrl, m_pwm_cycle, m_pwm_tm_reg;
	uint16_t m_cur_lch[0x10],m_cur_rch[0x10];
	uint16_t m_pwm_cycle_reg; //used for latching
	uint8_t m_pwm_timer_tick;
	uint8_t m_lch_index_r, m_rch_index_r, m_lch_index_w, m_rch_index_w;
	uint16_t m_lch_fifo_state, m_rch_fifo_state;


	uint16_t get_hposition(void);

	emu_timer *m_32x_pwm_timer;

>>>>>>> upstream/master
private:

	int m_32x_displaymode;
	int m_32x_videopriority;
<<<<<<< HEAD
	UINT32 m_32x_linerender[320+258]; // tmp buffer (bigger than it needs to be to simplify RLE decode)

//  virtual void device_config_complete();
=======
	uint32_t m_32x_linerender[320+258]; // tmp buffer (bigger than it needs to be to simplify RLE decode)

>>>>>>> upstream/master
	int m_32x_adapter_enabled;
	int m_32x_access_auth;
	int m_32x_screenshift;

<<<<<<< HEAD
	UINT16 m_32x_68k_a15104_reg;
=======
	uint16_t m_32x_68k_a15104_reg;
>>>>>>> upstream/master
	int m_sh2_master_vint_enable, m_sh2_slave_vint_enable;
	int m_sh2_master_hint_enable, m_sh2_slave_hint_enable;
	int m_sh2_master_cmdint_enable, m_sh2_slave_cmdint_enable;
	int m_sh2_hint_in_vbl;
	int m_sh2_master_vint_pending;
	int m_sh2_slave_vint_pending;
	int m_32x_fb_swap;
	int m_32x_hcount_reg;

<<<<<<< HEAD
	UINT16 m_32x_autofill_length;
	UINT16 m_32x_autofill_address;
	UINT16 m_32x_autofill_data;
	UINT16 m_a15106_reg;
	UINT16 m_dreq_src_addr[2],m_dreq_dst_addr[2],m_dreq_size;
	UINT8 m_sega_tv;
	UINT16 m_hint_vector[2];
	UINT16 m_a15100_reg;
=======
	uint16_t m_32x_autofill_length;
	uint16_t m_32x_autofill_address;
	uint16_t m_32x_autofill_data;
	uint16_t m_a15106_reg;
	uint16_t m_dreq_src_addr[2],m_dreq_dst_addr[2],m_dreq_size;
	uint8_t m_sega_tv;
	uint16_t m_hint_vector[2];
	uint16_t m_a15100_reg;
>>>>>>> upstream/master
	int m_32x_68k_a15102_reg;

	int m_32x_pal;
	int m_framerate;
	int m_base_total_scanlines;
	int m_total_scanlines;

<<<<<<< HEAD
	UINT16 m_commsram[8];

	UINT16* m_32x_dram0;
	UINT16* m_32x_dram1;
	UINT16 *m_32x_display_dram, *m_32x_access_dram;
	UINT16* m_32x_palette;
	UINT16* m_32x_palette_lookup;

	UINT16 m_fifo_block_a[4];
	UINT16 m_fifo_block_b[4];
	UINT16* m_current_fifo_block;
	UINT16* m_current_fifo_readblock;
=======
	uint16_t m_commsram[8];

	std::unique_ptr<uint16_t[]> m_32x_dram0;
	std::unique_ptr<uint16_t[]> m_32x_dram1;
	uint16_t *m_32x_display_dram, *m_32x_access_dram;
	std::unique_ptr<uint16_t[]> m_32x_palette;
	std::unique_ptr<uint16_t[]> m_32x_palette_lookup;

	uint16_t m_fifo_block_a[4];
	uint16_t m_fifo_block_b[4];
	uint16_t* m_current_fifo_block;
	uint16_t* m_current_fifo_readblock;
>>>>>>> upstream/master
	int m_current_fifo_write_pos;
	int m_current_fifo_read_pos;
	int m_fifo_block_a_full;
	int m_fifo_block_b_full;

	required_device<palette_device> m_palette;
};


class sega_32x_ntsc_device : public sega_32x_device
{
<<<<<<< HEAD
	public:
		sega_32x_ntsc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
public:
	sega_32x_ntsc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

};

class sega_32x_pal_device : public sega_32x_device
{
<<<<<<< HEAD
	public:
		sega_32x_pal_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	protected:
		virtual machine_config_constructor device_mconfig_additions() const;
};


extern const device_type SEGA_32X_NTSC;
extern const device_type SEGA_32X_PAL;

#define MCFG_SEGA_32X_PALETTE(_palette_tag) \
	sega_32x_device::static_set_palette_tag(*device, "^" _palette_tag);
=======
public:
	sega_32x_pal_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
};


DECLARE_DEVICE_TYPE(SEGA_32X_NTSC, sega_32x_ntsc_device)
DECLARE_DEVICE_TYPE(SEGA_32X_PAL,  sega_32x_pal_device)

#define MCFG_SEGA_32X_PALETTE(_palette_tag) \
	sega_32x_device::static_set_palette_tag(*device, "^" _palette_tag);

#endif // MAME_MACHINE_MEGA32X_H
>>>>>>> upstream/master
