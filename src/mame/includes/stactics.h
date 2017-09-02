// license:BSD-3-Clause
// copyright-holders:Frank Palazzolo
/****************************************************************************

    Sega "Space Tactics" Driver

    Frank Palazzolo (palazzol@home.com)

****************************************************************************/


<<<<<<< HEAD
=======
#include "machine/74259.h"

>>>>>>> upstream/master
class stactics_state : public driver_device
{
public:
	stactics_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
<<<<<<< HEAD
		m_palette_val(*this, "paletteram"),
		m_motor_on(*this, "motor_on"),
		m_lamps(*this, "lamps"),
=======
		m_outlatch(*this, "outlatch"),
>>>>>>> upstream/master
		m_display_buffer(*this, "display_buffer"),
		m_videoram_b(*this, "videoram_b"),
		m_videoram_d(*this, "videoram_d"),
		m_videoram_e(*this, "videoram_e"),
		m_videoram_f(*this, "videoram_f") { }

	required_device<cpu_device> m_maincpu;
<<<<<<< HEAD

	required_shared_ptr<UINT8> m_palette_val;
	required_shared_ptr<UINT8> m_motor_on;
	required_shared_ptr<UINT8> m_lamps;
	required_shared_ptr<UINT8> m_display_buffer;
	required_shared_ptr<UINT8> m_videoram_b;
	required_shared_ptr<UINT8> m_videoram_d;
	required_shared_ptr<UINT8> m_videoram_e;
	required_shared_ptr<UINT8> m_videoram_f;
=======
	required_device<ls259_device> m_outlatch;

	required_shared_ptr<uint8_t> m_display_buffer;
	required_shared_ptr<uint8_t> m_videoram_b;
	required_shared_ptr<uint8_t> m_videoram_d;
	required_shared_ptr<uint8_t> m_videoram_e;
	required_shared_ptr<uint8_t> m_videoram_f;
>>>>>>> upstream/master

	/* machine state */
	int    m_vert_pos;
	int    m_horiz_pos;
<<<<<<< HEAD

	/* video state */
	UINT8  m_y_scroll_d;
	UINT8  m_y_scroll_e;
	UINT8  m_y_scroll_f;
	UINT8  m_frame_count;
	UINT8  m_shot_standby;
	UINT8  m_shot_arrive;
	UINT16 m_beam_state;
	UINT16 m_old_beam_state;
	UINT16 m_beam_states_per_frame;

	DECLARE_READ8_MEMBER(vert_pos_r);
	DECLARE_READ8_MEMBER(horiz_pos_r);
	DECLARE_WRITE8_MEMBER(coinlockout_w);
=======
	bool   m_motor_on;

	/* video state */
	uint8_t  m_y_scroll_d;
	uint8_t  m_y_scroll_e;
	uint8_t  m_y_scroll_f;
	uint8_t  m_frame_count;
	uint8_t  m_shot_standby;
	uint8_t  m_shot_arrive;
	uint16_t m_beam_state;
	uint16_t m_old_beam_state;
	uint16_t m_beam_states_per_frame;
	uint8_t  m_palette_bank;

	DECLARE_READ8_MEMBER(vert_pos_r);
	DECLARE_READ8_MEMBER(horiz_pos_r);
	DECLARE_WRITE_LINE_MEMBER(coin_lockout_1_w);
	DECLARE_WRITE_LINE_MEMBER(coin_lockout_2_w);
	DECLARE_WRITE_LINE_MEMBER(palette_bank_w);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(scroll_ram_w);
	DECLARE_WRITE8_MEMBER(speed_latch_w);
	DECLARE_WRITE8_MEMBER(shot_trigger_w);
	DECLARE_WRITE8_MEMBER(shot_flag_clear_w);
<<<<<<< HEAD
=======
	DECLARE_WRITE_LINE_MEMBER(motor_w);
>>>>>>> upstream/master

	DECLARE_CUSTOM_INPUT_MEMBER(get_frame_count_d3);
	DECLARE_CUSTOM_INPUT_MEMBER(get_shot_standby);
	DECLARE_CUSTOM_INPUT_MEMBER(get_not_shot_arrive);
	DECLARE_CUSTOM_INPUT_MEMBER(get_motor_not_ready);
	DECLARE_CUSTOM_INPUT_MEMBER(get_rng);
	INTERRUPT_GEN_MEMBER(interrupt);

<<<<<<< HEAD
	virtual void machine_start();
	virtual void video_start();
	DECLARE_PALETTE_INIT(stactics);

	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void update_beam();
	inline int get_pixel_on_plane(UINT8 *videoram, UINT8 y, UINT8 x, UINT8 y_scroll);
=======
	DECLARE_WRITE_LINE_MEMBER(barrier_lamp_w);
	DECLARE_WRITE_LINE_MEMBER(start_lamp_w);
	DECLARE_WRITE_LINE_MEMBER(base_1_lamp_w);
	DECLARE_WRITE_LINE_MEMBER(base_2_lamp_w);
	DECLARE_WRITE_LINE_MEMBER(base_3_lamp_w);
	DECLARE_WRITE_LINE_MEMBER(base_4_lamp_w);
	DECLARE_WRITE_LINE_MEMBER(base_5_lamp_w);

	virtual void machine_start() override;
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(stactics);

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void update_beam();
	inline int get_pixel_on_plane(uint8_t *videoram, uint8_t y, uint8_t x, uint8_t y_scroll);
>>>>>>> upstream/master
	void draw_background(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void set_indicator_leds(int data, const char *output_name, int base_index);
	void update_artwork();
	void move_motor();
};
/*----------- defined in video/stactics.c -----------*/
MACHINE_CONFIG_EXTERN( stactics_video );
