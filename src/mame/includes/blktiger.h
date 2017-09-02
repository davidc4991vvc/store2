<<<<<<< HEAD
// license:???
=======
// license:BSD-3-Clause
>>>>>>> upstream/master
// copyright-holders:Paul Leaman
/***************************************************************************

    Black Tiger

***************************************************************************/

#include "video/bufsprite.h"

class blktiger_state : public driver_device
{
public:
	blktiger_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
			m_spriteram(*this, "spriteram") ,
		m_txvideoram(*this, "txvideoram"),
		m_mcu(*this, "mcu"),
		m_audiocpu(*this, "audiocpu"),
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette") { }

	/* memory pointers */
	required_device<buffered_spriteram8_device> m_spriteram;
<<<<<<< HEAD
	required_shared_ptr<UINT8> m_txvideoram;
=======
	required_shared_ptr<uint8_t> m_txvideoram;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t *m_tx_tilemap;
	tilemap_t *m_bg_tilemap8x4;
	tilemap_t *m_bg_tilemap4x8;
<<<<<<< HEAD
	UINT32  m_scroll_bank;
	UINT8   m_scroll_x[2];
	UINT8   m_scroll_y[2];
	UINT8   *m_scroll_ram;
	UINT8   m_screen_layout;
	UINT8   m_chon;
	UINT8   m_objon;
	UINT8   m_bgon;

	/* mcu-related */
	UINT8   m_z80_latch;
	UINT8   m_i8751_latch;
=======
	uint32_t  m_scroll_bank;
	uint8_t   m_scroll_x[2];
	uint8_t   m_scroll_y[2];
	std::unique_ptr<uint8_t[]>   m_scroll_ram;
	uint8_t   m_screen_layout;
	uint8_t   m_chon;
	uint8_t   m_objon;
	uint8_t   m_bgon;

	/* mcu-related */
	uint8_t   m_z80_latch;
	uint8_t   m_i8751_latch;
>>>>>>> upstream/master

	/* devices */
	optional_device<cpu_device> m_mcu;
	required_device<cpu_device> m_audiocpu;
	DECLARE_READ8_MEMBER(blktiger_from_mcu_r);
	DECLARE_WRITE8_MEMBER(blktiger_to_mcu_w);
	DECLARE_READ8_MEMBER(blktiger_from_main_r);
	DECLARE_WRITE8_MEMBER(blktiger_to_main_w);
	DECLARE_WRITE8_MEMBER(blktiger_bankswitch_w);
	DECLARE_WRITE8_MEMBER(blktiger_coinlockout_w);
	DECLARE_WRITE8_MEMBER(blktiger_txvideoram_w);
	DECLARE_READ8_MEMBER(blktiger_bgvideoram_r);
	DECLARE_WRITE8_MEMBER(blktiger_bgvideoram_w);
	DECLARE_WRITE8_MEMBER(blktiger_bgvideoram_bank_w);
	DECLARE_WRITE8_MEMBER(blktiger_scrolly_w);
	DECLARE_WRITE8_MEMBER(blktiger_scrollx_w);
	DECLARE_WRITE8_MEMBER(blktiger_video_control_w);
	DECLARE_WRITE8_MEMBER(blktiger_video_enable_w);
	DECLARE_WRITE8_MEMBER(blktiger_screen_layout_w);
	TILEMAP_MAPPER_MEMBER(bg8x4_scan);
	TILEMAP_MAPPER_MEMBER(bg4x8_scan);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(get_tx_tile_info);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	UINT32 screen_update_blktiger(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	DECLARE_WRITE_LINE_MEMBER(irqhandler);
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	uint32_t screen_update_blktiger(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
>>>>>>> upstream/master
	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

	DECLARE_DRIVER_INIT(blktigerb3);
};
