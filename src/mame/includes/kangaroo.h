// license:BSD-3-Clause
// copyright-holders:Ville Laitinen, Aaron Giles
/***************************************************************************

    Sun Electronics Kangaroo hardware

    driver by Ville Laitinen

***************************************************************************/

class kangaroo_state : public driver_device
{
public:
	kangaroo_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_video_control(*this, "video_control"),
		m_maincpu(*this, "maincpu"),
		m_palette(*this, "palette") { }

	/* memory pointers */
<<<<<<< HEAD
	required_shared_ptr<UINT8> m_video_control;

	/* video-related */
	UINT32       *m_videoram;

	/* misc */
	UINT8        m_mcu_clock;
=======
	required_shared_ptr<uint8_t> m_video_control;

	/* video-related */
	std::unique_ptr<uint32_t[]>      m_videoram;

	/* misc */
	uint8_t        m_mcu_clock;
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(mcu_sim_r);
	DECLARE_WRITE8_MEMBER(mcu_sim_w);
	DECLARE_WRITE8_MEMBER(kangaroo_coin_counter_w);
	DECLARE_WRITE8_MEMBER(kangaroo_videoram_w);
	DECLARE_WRITE8_MEMBER(kangaroo_video_control_w);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	DECLARE_MACHINE_START(kangaroo_mcu);
	UINT32 screen_update_kangaroo(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	void videoram_write( UINT16 offset, UINT8 data, UINT8 mask );
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	DECLARE_MACHINE_START(kangaroo_mcu);
	uint32_t screen_update_kangaroo(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	void videoram_write( uint16_t offset, uint8_t data, uint8_t mask );
>>>>>>> upstream/master
	void blitter_execute(  );
	required_device<cpu_device> m_maincpu;
	required_device<palette_device> m_palette;
};
