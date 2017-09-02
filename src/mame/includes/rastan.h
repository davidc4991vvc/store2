<<<<<<< HEAD
// license:???
=======
// license:GPL-2.0+
>>>>>>> upstream/master
// copyright-holders:Jarek Burczynski
/*************************************************************************

    Rastan

*************************************************************************/
<<<<<<< HEAD
=======

#include "machine/74157.h"
>>>>>>> upstream/master
#include "sound/msm5205.h"
#include "video/pc080sn.h"
#include "video/pc090oj.h"

class rastan_state : public driver_device
{
public:
	rastan_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_msm(*this, "msm"),
<<<<<<< HEAD
=======
		m_adpcm_sel(*this, "adpcm_sel"),
		m_adpcm_data(*this, "adpcm"),
>>>>>>> upstream/master
		m_pc080sn(*this, "pc080sn"),
		m_pc090oj(*this, "pc090oj") { }

	/* video-related */
<<<<<<< HEAD
	UINT16      m_sprite_ctrl;
	UINT16      m_sprites_flipscreen;

	/* misc */
	int         m_adpcm_pos;
	int         m_adpcm_data;
=======
	u16         m_sprite_ctrl;
	u16         m_sprites_flipscreen;

	/* misc */
	u16         m_adpcm_pos;
	bool        m_adpcm_ff;
>>>>>>> upstream/master

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<msm5205_device> m_msm;
<<<<<<< HEAD
=======
	required_device<ls157_device> m_adpcm_sel;
	required_region_ptr<u8> m_adpcm_data;
>>>>>>> upstream/master
	required_device<pc080sn_device> m_pc080sn;
	required_device<pc090oj_device> m_pc090oj;
	DECLARE_WRITE8_MEMBER(rastan_msm5205_address_w);
	DECLARE_WRITE16_MEMBER(rastan_spritectrl_w);
	DECLARE_WRITE8_MEMBER(rastan_bankswitch_w);
	DECLARE_WRITE8_MEMBER(rastan_msm5205_start_w);
	DECLARE_WRITE8_MEMBER(rastan_msm5205_stop_w);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	UINT32 screen_update_rastan(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	uint32_t screen_update_rastan(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	DECLARE_WRITE_LINE_MEMBER(rastan_msm5205_vck);
};
