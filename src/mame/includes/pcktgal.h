// license:BSD-3-Clause
// copyright-holders:Bryan McPhail
<<<<<<< HEAD
=======

#include "machine/gen_latch.h"
>>>>>>> upstream/master
#include "sound/msm5205.h"
#include "video/decbac06.h"

class pcktgal_state : public driver_device
{
public:
	pcktgal_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_msm(*this, "msm"),
		m_tilegen1(*this, "tilegen1"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
<<<<<<< HEAD
=======
		m_soundlatch(*this, "soundlatch"),
>>>>>>> upstream/master
		m_spriteram(*this, "spriteram") { }

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<msm5205_device> m_msm;
	required_device<deco_bac06_device> m_tilegen1;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
<<<<<<< HEAD

	required_shared_ptr<UINT8> m_spriteram;
=======
	required_device<generic_latch_8_device> m_soundlatch;

	required_shared_ptr<uint8_t> m_spriteram;
>>>>>>> upstream/master

	int m_msm5205next;
	int m_toggle;

	DECLARE_WRITE8_MEMBER(bank_w);
	DECLARE_WRITE8_MEMBER(sound_bank_w);
	DECLARE_WRITE8_MEMBER(sound_w);
	DECLARE_WRITE8_MEMBER(adpcm_data_w);
	DECLARE_READ8_MEMBER(adpcm_reset_r);
	DECLARE_WRITE_LINE_MEMBER(adpcm_int);

	DECLARE_DRIVER_INIT(pcktgal);
	DECLARE_PALETTE_INIT(pcktgal);
<<<<<<< HEAD
	virtual void machine_start();

	UINT32 screen_update_pcktgal(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_pcktgalb(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;

	uint32_t screen_update_pcktgal(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_pcktgalb(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect);
};
