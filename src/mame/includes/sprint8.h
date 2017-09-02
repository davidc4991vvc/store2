<<<<<<< HEAD
// license:???
// copyright-holders:Stefan Jokisch
#include "sound/discrete.h"
=======
// license:BSD-3-Clause
// copyright-holders:Stefan Jokisch
#include "machine/74259.h"
#include "sound/discrete.h"
#include "screen.h"
>>>>>>> upstream/master

class sprint8_state : public driver_device
{
public:
	sprint8_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
<<<<<<< HEAD
		m_video_ram(*this, "video_ram"),
		m_pos_h_ram(*this, "pos_h_ram"),
		m_pos_v_ram(*this, "pos_v_ram"),
		m_pos_d_ram(*this, "pos_d_ram"),
		m_team(*this, "team"),
		m_discrete(*this, "discrete"),
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette") { }
=======
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"),
		m_discrete(*this, "discrete"),
		m_video_ram(*this, "video_ram"),
		m_pos_h_ram(*this, "pos_h_ram"),
		m_pos_v_ram(*this, "pos_v_ram"),
		m_pos_d_ram(*this, "pos_d_ram") { }

	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
	required_device<discrete_device> m_discrete;

	required_shared_ptr<uint8_t> m_video_ram;
	required_shared_ptr<uint8_t> m_pos_h_ram;
	required_shared_ptr<uint8_t> m_pos_v_ram;
	required_shared_ptr<uint8_t> m_pos_d_ram;
>>>>>>> upstream/master

	int m_steer_dir[8];
	int m_steer_flag[8];
	int m_collision_reset;
	int m_collision_index;
<<<<<<< HEAD
	UINT8 m_dial[8];
	required_shared_ptr<UINT8> m_video_ram;
	required_shared_ptr<UINT8> m_pos_h_ram;
	required_shared_ptr<UINT8> m_pos_v_ram;
	required_shared_ptr<UINT8> m_pos_d_ram;
	required_shared_ptr<UINT8> m_team;
	required_device<discrete_device> m_discrete;
=======
	uint8_t m_dial[8];
	int m_team;

>>>>>>> upstream/master
	tilemap_t* m_tilemap1;
	tilemap_t* m_tilemap2;
	bitmap_ind16 m_helper1;
	bitmap_ind16 m_helper2;
<<<<<<< HEAD
	DECLARE_READ8_MEMBER(sprint8_collision_r);
	DECLARE_READ8_MEMBER(sprint8_input_r);
	DECLARE_WRITE8_MEMBER(sprint8_lockout_w);
	DECLARE_WRITE8_MEMBER(sprint8_int_reset_w);
	DECLARE_WRITE8_MEMBER(sprint8_video_ram_w);
	TILE_GET_INFO_MEMBER(get_tile_info1);
	TILE_GET_INFO_MEMBER(get_tile_info2);
	virtual void machine_reset();
	virtual void video_start();
	DECLARE_PALETTE_INIT(sprint8);
	UINT32 screen_update_sprint8(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void screen_eof_sprint8(screen_device &screen, bool state);
	TIMER_CALLBACK_MEMBER(sprint8_collision_callback);
	TIMER_DEVICE_CALLBACK_MEMBER(input_callback);
	DECLARE_WRITE8_MEMBER(sprint8_crash_w);
	DECLARE_WRITE8_MEMBER(sprint8_screech_w);
	DECLARE_WRITE8_MEMBER(sprint8_attract_w);
	DECLARE_WRITE8_MEMBER(sprint8_motor_w);
	void set_pens();
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void sprint8_set_collision(int n);
	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
};

/*----------- defined in audio/sprint8.c -----------*/
=======
	emu_timer *m_collision_timer;

	DECLARE_READ8_MEMBER(collision_r);
	DECLARE_READ8_MEMBER(input_r);
	DECLARE_WRITE8_MEMBER(lockout_w);
	DECLARE_WRITE_LINE_MEMBER(int_reset_w);
	DECLARE_WRITE_LINE_MEMBER(team_w);
	DECLARE_WRITE8_MEMBER(video_ram_w);

	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(sprint8);

	TILE_GET_INFO_MEMBER(get_tile_info1);
	TILE_GET_INFO_MEMBER(get_tile_info2);
	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	DECLARE_WRITE_LINE_MEMBER(screen_vblank);
	TIMER_CALLBACK_MEMBER(collision_callback);
	TIMER_DEVICE_CALLBACK_MEMBER(input_callback);

	void set_pens();
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void set_collision(int n);
};

/*----------- defined in audio/sprint8.c -----------*/
MACHINE_CONFIG_EXTERN( sprint8_audio );
>>>>>>> upstream/master
DISCRETE_SOUND_EXTERN( sprint8 );
