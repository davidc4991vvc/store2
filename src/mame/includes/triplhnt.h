<<<<<<< HEAD
// license:???
=======
// license:BSD-3-Clause
>>>>>>> upstream/master
// copyright-holders:Stefan Jokisch
/*************************************************************************

    Atari Triple Hunt hardware

*************************************************************************/

<<<<<<< HEAD
#include "sound/discrete.h"
#include "sound/samples.h"
=======
#include "machine/74259.h"
#include "machine/watchdog.h"
#include "sound/discrete.h"
#include "sound/samples.h"
#include "screen.h"
>>>>>>> upstream/master


/* Discrete Sound Input Nodes */
#define TRIPLHNT_BEAR_ROAR_DATA NODE_01
#define TRIPLHNT_BEAR_EN        NODE_02
#define TRIPLHNT_SHOT_DATA      NODE_03
#define TRIPLHNT_SCREECH_EN     NODE_04
#define TRIPLHNT_LAMP_EN        NODE_05


class triplhnt_state : public driver_device
{
public:
	enum
	{
		TIMER_HIT
	};

	triplhnt_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
<<<<<<< HEAD
		m_playfield_ram(*this, "playfield_ram"),
		m_vpos_ram(*this, "vpos_ram"),
		m_hpos_ram(*this, "hpos_ram"),
		m_orga_ram(*this, "orga_ram"),
		m_code_ram(*this, "code_ram"),
		m_maincpu(*this, "maincpu"),
=======
		m_maincpu(*this, "maincpu"),
		m_latch(*this, "latch"),
		m_watchdog(*this, "watchdog"),
>>>>>>> upstream/master
		m_discrete(*this, "discrete"),
		m_samples(*this, "samples"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
<<<<<<< HEAD
		m_palette(*this, "palette") { }

	UINT8 m_cmos[16];
	UINT8 m_da_latch;
	UINT8 m_misc_flags;
	UINT8 m_cmos_latch;
	UINT8 m_hit_code;
	required_shared_ptr<UINT8> m_playfield_ram;
	required_shared_ptr<UINT8> m_vpos_ram;
	required_shared_ptr<UINT8> m_hpos_ram;
	required_shared_ptr<UINT8> m_orga_ram;
	required_shared_ptr<UINT8> m_code_ram;
	int m_sprite_zoom;
	int m_sprite_bank;
	bitmap_ind16 m_helper;
	tilemap_t* m_bg_tilemap;
	DECLARE_WRITE8_MEMBER(triplhnt_misc_w);
	DECLARE_READ8_MEMBER(triplhnt_cmos_r);
	DECLARE_READ8_MEMBER(triplhnt_input_port_4_r);
	DECLARE_READ8_MEMBER(triplhnt_misc_r);
	DECLARE_READ8_MEMBER(triplhnt_da_latch_r);
	DECLARE_DRIVER_INIT(triplhnt);
	TILE_GET_INFO_MEMBER(get_tile_info);
	virtual void video_start();
	DECLARE_PALETTE_INIT(triplhnt);
	UINT32 screen_update_triplhnt(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void triplhnt_set_collision(int code);
	void triplhnt_update_misc(address_space &space, int offset);
	required_device<cpu_device> m_maincpu;
	required_device<discrete_device> m_discrete;
	required_device<samples_device> m_samples;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
protected:
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
};

/*----------- defined in audio/triplhnt.c -----------*/
=======
		m_palette(*this, "palette"),
		m_playfield_ram(*this, "playfield_ram"),
		m_vpos_ram(*this, "vpos_ram"),
		m_hpos_ram(*this, "hpos_ram"),
		m_orga_ram(*this, "orga_ram"),
		m_code_ram(*this, "code_ram") { }

	required_device<cpu_device> m_maincpu;
	required_device<f9334_device> m_latch;
	required_device<watchdog_timer_device> m_watchdog;
	required_device<discrete_device> m_discrete;
	required_device<samples_device> m_samples;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;

	required_shared_ptr<uint8_t> m_playfield_ram;
	required_shared_ptr<uint8_t> m_vpos_ram;
	required_shared_ptr<uint8_t> m_hpos_ram;
	required_shared_ptr<uint8_t> m_orga_ram;
	required_shared_ptr<uint8_t> m_code_ram;

	uint8_t m_cmos[16];
	uint8_t m_da_latch;
	uint8_t m_cmos_latch;
	uint8_t m_hit_code;
	int m_sprite_zoom;
	int m_sprite_bank;
	bitmap_ind16 m_helper;
	emu_timer *m_hit_timer;
	tilemap_t* m_bg_tilemap;

	DECLARE_WRITE_LINE_MEMBER(ram_2_w);
	DECLARE_WRITE_LINE_MEMBER(sprite_zoom_w);
	DECLARE_WRITE_LINE_MEMBER(sprite_bank_w);
	DECLARE_WRITE_LINE_MEMBER(lamp1_w);
	DECLARE_WRITE_LINE_MEMBER(coin_lockout_w);
	DECLARE_WRITE_LINE_MEMBER(tape_control_w);

	DECLARE_READ8_MEMBER(cmos_r);
	DECLARE_READ8_MEMBER(input_port_4_r);
	DECLARE_READ8_MEMBER(misc_r);
	DECLARE_READ8_MEMBER(da_latch_r);

	DECLARE_DRIVER_INIT(triplhnt);
	TILE_GET_INFO_MEMBER(get_tile_info);
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(triplhnt);

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void set_collision(int code);

protected:
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
};

/*----------- defined in audio/triplhnt.cpp -----------*/
>>>>>>> upstream/master
DISCRETE_SOUND_EXTERN( triplhnt );
extern const char *const triplhnt_sample_names[];
