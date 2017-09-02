// license:BSD-3-Clause
// copyright-holders:Ernesto Corvi
<<<<<<< HEAD
=======

#include "machine/gen_latch.h"
>>>>>>> upstream/master
#include "sound/msm5205.h"

class wc90b_state : public driver_device
{
public:
	wc90b_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
<<<<<<< HEAD
=======
		m_subcpu(*this, "sub"),
>>>>>>> upstream/master
		m_audiocpu(*this, "audiocpu"),
		m_msm(*this, "msm"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
<<<<<<< HEAD
=======
		m_soundlatch(*this, "soundlatch"),
>>>>>>> upstream/master
		m_fgvideoram(*this, "fgvideoram"),
		m_bgvideoram(*this, "bgvideoram"),
		m_txvideoram(*this, "txvideoram"),
		m_scroll1x(*this, "scroll1x"),
		m_scroll2x(*this, "scroll2x"),
		m_scroll1y(*this, "scroll1y"),
		m_scroll2y(*this, "scroll2y"),
		m_scroll_x_lo(*this, "scroll_x_lo"),
		m_spriteram(*this, "spriteram") { }

	required_device<cpu_device> m_maincpu;
<<<<<<< HEAD
=======
	required_device<cpu_device> m_subcpu;
>>>>>>> upstream/master
	required_device<cpu_device> m_audiocpu;
	required_device<msm5205_device> m_msm;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
<<<<<<< HEAD

	required_shared_ptr<UINT8> m_fgvideoram;
	required_shared_ptr<UINT8> m_bgvideoram;
	required_shared_ptr<UINT8> m_txvideoram;
	required_shared_ptr<UINT8> m_scroll1x;
	required_shared_ptr<UINT8> m_scroll2x;
	required_shared_ptr<UINT8> m_scroll1y;
	required_shared_ptr<UINT8> m_scroll2y;
	required_shared_ptr<UINT8> m_scroll_x_lo;
	required_shared_ptr<UINT8> m_spriteram;
=======
	required_device<generic_latch_8_device> m_soundlatch;

	required_shared_ptr<uint8_t> m_fgvideoram;
	required_shared_ptr<uint8_t> m_bgvideoram;
	required_shared_ptr<uint8_t> m_txvideoram;
	required_shared_ptr<uint8_t> m_scroll1x;
	required_shared_ptr<uint8_t> m_scroll2x;
	required_shared_ptr<uint8_t> m_scroll1y;
	required_shared_ptr<uint8_t> m_scroll2y;
	required_shared_ptr<uint8_t> m_scroll_x_lo;
	required_shared_ptr<uint8_t> m_spriteram;
>>>>>>> upstream/master

	tilemap_t *m_tx_tilemap;
	tilemap_t *m_fg_tilemap;
	tilemap_t *m_bg_tilemap;
	int m_msm5205next;
	int m_toggle;

	DECLARE_WRITE8_MEMBER(bankswitch_w);
	DECLARE_WRITE8_MEMBER(bankswitch1_w);
	DECLARE_WRITE8_MEMBER(sound_command_w);
	DECLARE_WRITE8_MEMBER(adpcm_data_w);
	DECLARE_WRITE8_MEMBER(bgvideoram_w);
	DECLARE_WRITE8_MEMBER(fgvideoram_w);
	DECLARE_WRITE8_MEMBER(txvideoram_w);
	DECLARE_WRITE8_MEMBER(adpcm_control_w);
	DECLARE_WRITE_LINE_MEMBER(adpcm_int);
<<<<<<< HEAD
=======
	DECLARE_READ8_MEMBER(master_irq_ack_r);
	DECLARE_WRITE8_MEMBER(slave_irq_ack_w);
>>>>>>> upstream/master

	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
	TILE_GET_INFO_MEMBER(get_tx_tile_info);

<<<<<<< HEAD
	virtual void machine_start();
	virtual void video_start();

	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	virtual void video_start() override;

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, int priority );
};
