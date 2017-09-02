<<<<<<< HEAD
// license:LGPL-2.1+
// copyright-holders:Tomasz Slanina
#include "audio/seibu.h"    // for seibu_sound_decrypt on the MAIN cpu (not sound)
=======
// license:BSD-3-Clause
// copyright-holders:Tomasz Slanina
#include "audio/seibu.h"    // for seibu_sound_decrypt on the MAIN cpu (not sound)
#include "screen.h"
>>>>>>> upstream/master

class mustache_state : public driver_device
{
public:
	mustache_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"),
		m_videoram(*this, "videoram"),
		m_spriteram(*this, "spriteram"),
<<<<<<< HEAD
		m_decrypted_opcodes(*this, "decrypted_opcodes") { }
=======
		m_dswb(*this, "DSWB") { }
>>>>>>> upstream/master

	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;

<<<<<<< HEAD
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_spriteram;
	required_shared_ptr<UINT8> m_decrypted_opcodes;
=======
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_spriteram;

	required_ioport m_dswb;
>>>>>>> upstream/master

	tilemap_t *m_bg_tilemap;
	int m_control_byte;

	DECLARE_WRITE8_MEMBER(videoram_w);
	DECLARE_WRITE8_MEMBER(video_control_w);
	DECLARE_WRITE8_MEMBER(scroll_w);

	TILE_GET_INFO_MEMBER(get_bg_tile_info);

	DECLARE_DRIVER_INIT(mustache);
<<<<<<< HEAD
	virtual void video_start();
	DECLARE_PALETTE_INIT(mustache);

	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void video_start() override;

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect );

	TIMER_DEVICE_CALLBACK_MEMBER(scanline);
};
