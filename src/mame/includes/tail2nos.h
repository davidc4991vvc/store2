// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
/*************************************************************************

    Tail to Nose / Super Formula

*************************************************************************/

<<<<<<< HEAD
=======
#include "machine/6850acia.h"
#include "machine/gen_latch.h"
>>>>>>> upstream/master
#include "video/k051316.h"

class tail2nos_state : public driver_device
{
public:
	tail2nos_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_txvideoram(*this, "txvideoram"),
		m_spriteram(*this, "spriteram"),
		m_zoomram(*this, "k051316"),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_k051316(*this, "k051316"),
		m_gfxdecode(*this, "gfxdecode"),
<<<<<<< HEAD
		m_palette(*this, "palette")  { }

	/* memory pointers */
	required_shared_ptr<UINT16> m_txvideoram;
	required_shared_ptr<UINT16> m_spriteram;
	required_shared_ptr<UINT16> m_zoomram;
=======
		m_palette(*this, "palette"),
		m_soundlatch(*this, "soundlatch"),
		m_acia(*this, "acia") { }

	/* memory pointers */
	required_shared_ptr<uint16_t> m_txvideoram;
	required_shared_ptr<uint16_t> m_spriteram;
	required_shared_ptr<uint16_t> m_zoomram;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t   *m_tx_tilemap;
	int         m_txbank;
	int         m_txpalette;
<<<<<<< HEAD
	int         m_video_enable;
=======
	bool        m_video_enable;
	bool        m_flip_screen;
>>>>>>> upstream/master

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<k051316_device> m_k051316;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
<<<<<<< HEAD

	DECLARE_WRITE16_MEMBER(sound_command_w);
	DECLARE_WRITE16_MEMBER(tail2nos_txvideoram_w);
	DECLARE_WRITE16_MEMBER(tail2nos_zoomdata_w);
	DECLARE_WRITE16_MEMBER(tail2nos_gfxbank_w);
	DECLARE_WRITE8_MEMBER(sound_bankswitch_w);
	TILE_GET_INFO_MEMBER(get_tile_info);
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	UINT32 screen_update_tail2nos(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void tail2nos_postload();
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	DECLARE_WRITE_LINE_MEMBER(irqhandler);
=======
	required_device<generic_latch_8_device> m_soundlatch;
	required_device<acia6850_device> m_acia;

	DECLARE_CUSTOM_INPUT_MEMBER(analog_in_r);
	DECLARE_WRITE16_MEMBER(tail2nos_txvideoram_w);
	DECLARE_WRITE16_MEMBER(tail2nos_zoomdata_w);
	DECLARE_WRITE8_MEMBER(tail2nos_gfxbank_w);
	DECLARE_WRITE8_MEMBER(sound_bankswitch_w);
	DECLARE_READ8_MEMBER(sound_semaphore_r);
	TILE_GET_INFO_MEMBER(get_tile_info);
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	uint32_t screen_update_tail2nos(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void tail2nos_postload();
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
>>>>>>> upstream/master
	K051316_CB_MEMBER(zoom_callback);
};
