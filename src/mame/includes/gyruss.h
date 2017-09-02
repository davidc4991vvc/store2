// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria, Couriersud
/*************************************************************************

    Gyruss

*************************************************************************/

#include "sound/discrete.h"
<<<<<<< HEAD
=======
#include "screen.h"
>>>>>>> upstream/master

class gyruss_state : public driver_device
{
public:
	gyruss_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_subcpu(*this, "sub"),
		m_audiocpu(*this, "audiocpu"),
		m_audiocpu_2(*this, "audio2"),
		m_discrete(*this, "discrete"),
		m_colorram(*this, "colorram"),
		m_videoram(*this, "videoram"),
<<<<<<< HEAD
		m_flipscreen(*this, "flipscreen"),
=======
>>>>>>> upstream/master
		m_spriteram(*this, "spriteram"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette")
	{ }

	/* devices/memory pointers */
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_subcpu;
	required_device<cpu_device> m_audiocpu;
	required_device<cpu_device> m_audiocpu_2;
	required_device<discrete_device> m_discrete;
<<<<<<< HEAD
	required_shared_ptr<UINT8> m_colorram;
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_flipscreen;
	required_shared_ptr<UINT8> m_spriteram;
=======
	required_shared_ptr<uint8_t> m_colorram;
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_spriteram;
>>>>>>> upstream/master
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;

	tilemap_t *m_tilemap;
<<<<<<< HEAD
	UINT8 m_master_nmi_mask;
	UINT8 m_slave_irq_mask;
=======
	uint8_t m_master_nmi_mask;
	uint8_t m_slave_irq_mask;
	bool m_flipscreen;
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER(gyruss_irq_clear_w);
	DECLARE_WRITE8_MEMBER(gyruss_sh_irqtrigger_w);
	DECLARE_WRITE8_MEMBER(gyruss_i8039_irq_w);
<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER(master_nmi_mask_w);
	DECLARE_WRITE8_MEMBER(slave_irq_mask_w);
	DECLARE_WRITE8_MEMBER(gyruss_spriteram_w);
	DECLARE_READ8_MEMBER(gyruss_scanline_r);
=======
	DECLARE_WRITE_LINE_MEMBER(master_nmi_mask_w);
	DECLARE_WRITE8_MEMBER(slave_irq_mask_w);
	DECLARE_WRITE_LINE_MEMBER(coin_counter_1_w);
	DECLARE_WRITE_LINE_MEMBER(coin_counter_2_w);
	DECLARE_WRITE8_MEMBER(gyruss_spriteram_w);
	DECLARE_READ8_MEMBER(gyruss_scanline_r);
	DECLARE_WRITE_LINE_MEMBER(flipscreen_w);
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(gyruss_portA_r);
	DECLARE_WRITE8_MEMBER(gyruss_dac_w);
	DECLARE_WRITE8_MEMBER(gyruss_filter0_w);
	DECLARE_WRITE8_MEMBER(gyruss_filter1_w);
	DECLARE_DRIVER_INIT(gyruss);
	TILE_GET_INFO_MEMBER(gyruss_get_tile_info);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void video_start();
	DECLARE_PALETTE_INIT(gyruss);
	UINT32 screen_update_gyruss(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(gyruss);
	uint32_t screen_update_gyruss(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	INTERRUPT_GEN_MEMBER(master_vblank_irq);
	INTERRUPT_GEN_MEMBER(slave_vblank_irq);
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	void filter_w(address_space &space, int chip, int data );
};
