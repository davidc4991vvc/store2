// license:LGPL-2.1+
// copyright-holders:Angelo Salese, Olivier Galibert
/*************************************************************************

    Taito Air System

*************************************************************************/

#include "machine/taitoio.h"
<<<<<<< HEAD
#include "video/tc0080vco.h"
=======
#include "machine/taitoio_yoke.h"
#include "video/tc0080vco.h"
#include "screen.h"
>>>>>>> upstream/master

enum { TAITOAIR_FRAC_SHIFT = 16, TAITOAIR_POLY_MAX_PT = 16 };

struct taitoair_spoint {
<<<<<<< HEAD
	INT32 x, y;
=======
	int32_t x, y;
>>>>>>> upstream/master
};

struct taitoair_poly {
	struct taitoair_spoint p[TAITOAIR_POLY_MAX_PT];
	int pcount;
<<<<<<< HEAD
	UINT16 header;
=======
	uint16_t header;
>>>>>>> upstream/master
};


class taitoair_state : public driver_device
{
public:
	taitoair_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
			m_m68000_mainram(*this, "m68000_mainram"),
			m_line_ram(*this, "line_ram"),
			m_dsp_ram(*this, "dsp_ram"),
			m_paletteram(*this, "paletteram"),
			m_gradram(*this, "gradram"),
			m_tc0430grw(*this, "tc0430grw"),
			m_maincpu(*this, "maincpu"),
			m_audiocpu(*this, "audiocpu"),
			m_dsp(*this, "dsp"),
			m_tc0080vco(*this, "tc0080vco"),
			m_tc0220ioc(*this, "tc0220ioc"),
<<<<<<< HEAD
=======
			m_yoke(*this, "yokectrl"),
>>>>>>> upstream/master
			m_gfxdecode(*this, "gfxdecode"),
			m_screen(*this, "screen"),
			m_palette(*this, "palette")
			{ }

	/* memory pointers */
<<<<<<< HEAD
	required_shared_ptr<UINT16> m_m68000_mainram;
	required_shared_ptr<UINT16> m_line_ram;
	required_shared_ptr<UINT16> m_dsp_ram;          // Shared 68000/TMS32025 RAM
	required_shared_ptr<UINT16> m_paletteram;
	required_shared_ptr<UINT16> m_gradram;
	required_shared_ptr<UINT16> m_tc0430grw;
=======
	required_shared_ptr<uint16_t> m_m68000_mainram;
	required_shared_ptr<uint16_t> m_line_ram;
	required_shared_ptr<uint16_t> m_dsp_ram;          // Shared 68000/TMS32025 RAM
	required_shared_ptr<uint16_t> m_paletteram;
	required_shared_ptr<uint16_t> m_gradram;
	required_shared_ptr<uint16_t> m_tc0430grw;
>>>>>>> upstream/master

	/* video-related */
	taitoair_poly  m_q;

	/* misc */
	int           m_dsp_hold_signal;

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<cpu_device> m_dsp;
	required_device<tc0080vco_device> m_tc0080vco;
	required_device<tc0220ioc_device> m_tc0220ioc;
<<<<<<< HEAD
=======
	required_device<taitoio_yoke_device> m_yoke;
>>>>>>> upstream/master
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;

<<<<<<< HEAD
	bitmap_ind16 *m_framebuffer[2];

	/* 3d info */
	INT16 m_frustumLeft;
	INT16 m_frustumBottom;
	INT16 m_eyecoordBuffer[4];  /* homogeneous */

	bool m_gradbank;

	DECLARE_READ16_MEMBER(dsp_m_r);
	DECLARE_WRITE16_MEMBER(dsp_m_w);

	UINT16 m_dsp_test_object_type;
	INT16 m_dsp_test_or_clip, m_dsp_test_and_clip;
	INT16 m_dsp_test_x, m_dsp_test_y, m_dsp_test_z;
=======
	std::unique_ptr<bitmap_ind16> m_framebuffer[2];

	/* 3d info */
	int16_t m_frustumLeft;
	int16_t m_frustumBottom;
	int16_t m_eyecoordBuffer[4];  /* homogeneous */

	bool m_gradbank;

	uint16_t m_dsp_test_object_type;
	int16_t m_dsp_test_or_clip, m_dsp_test_and_clip;
	int16_t m_dsp_test_x, m_dsp_test_y, m_dsp_test_z;
>>>>>>> upstream/master

	DECLARE_WRITE16_MEMBER(dsp_test_start_w);
	DECLARE_WRITE16_MEMBER(dsp_test_x_w);
	DECLARE_WRITE16_MEMBER(dsp_test_y_w);
	DECLARE_WRITE16_MEMBER(dsp_test_z_w);
	DECLARE_READ16_MEMBER(dsp_test_point_r);
	DECLARE_READ16_MEMBER(dsp_test_or_clip_r);
	DECLARE_READ16_MEMBER(dsp_test_and_clip_r);

<<<<<<< HEAD
	INT16 m_dsp_muldiv_a_1, m_dsp_muldiv_b_1, m_dsp_muldiv_c_1;
=======
	int16_t m_dsp_muldiv_a_1, m_dsp_muldiv_b_1, m_dsp_muldiv_c_1;
>>>>>>> upstream/master

	DECLARE_WRITE16_MEMBER(dsp_muldiv_a_1_w);
	DECLARE_WRITE16_MEMBER(dsp_muldiv_b_1_w);
	DECLARE_WRITE16_MEMBER(dsp_muldiv_c_1_w);
	DECLARE_READ16_MEMBER(dsp_muldiv_1_r);

<<<<<<< HEAD
	INT16 m_dsp_muldiv_a_2, m_dsp_muldiv_b_2, m_dsp_muldiv_c_2;
=======
	int16_t m_dsp_muldiv_a_2, m_dsp_muldiv_b_2, m_dsp_muldiv_c_2;
>>>>>>> upstream/master

	DECLARE_WRITE16_MEMBER(dsp_muldiv_a_2_w);
	DECLARE_WRITE16_MEMBER(dsp_muldiv_b_2_w);
	DECLARE_WRITE16_MEMBER(dsp_muldiv_c_2_w);
	DECLARE_READ16_MEMBER(dsp_muldiv_2_r);

	//bitmap_ind16 *m_buffer3d;
	DECLARE_WRITE16_MEMBER(system_control_w);
	DECLARE_READ16_MEMBER(lineram_r);
	DECLARE_WRITE16_MEMBER(lineram_w);
	DECLARE_READ16_MEMBER(dspram_r);
	DECLARE_WRITE16_MEMBER(dspram_w);
	DECLARE_READ16_MEMBER(dsp_HOLD_signal_r);
	DECLARE_WRITE16_MEMBER(dsp_HOLDA_signal_w);
	DECLARE_WRITE16_MEMBER(airsys_paletteram16_w);
	DECLARE_WRITE16_MEMBER(airsys_gradram_w);
	DECLARE_READ16_MEMBER(stick_input_r);
	DECLARE_READ16_MEMBER(stick2_input_r);
<<<<<<< HEAD
=======
	DECLARE_WRITE8_MEMBER(coin_control_w);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(sound_bankswitch_w);
	DECLARE_WRITE16_MEMBER(dsp_flags_w);
	DECLARE_WRITE16_MEMBER(dma_regs_w);

<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	UINT32 screen_update_taitoair(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	uint32_t screen_update_taitoair(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	int draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	int draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect, int start_offset );
	void fb_copy_op(void);
	void fb_fill_op(void);
	void fb_erase_op(void);

<<<<<<< HEAD
	void fill_slope( bitmap_ind16 &bitmap, const rectangle &cliprect, UINT16 header, INT32 x1, INT32 x2, INT32 sl1, INT32 sl2, INT32 y1, INT32 y2, INT32 *nx1, INT32 *nx2 );
	void fill_poly( bitmap_ind16 &bitmap, const rectangle &cliprect, const struct taitoair_poly *q );
	int projectEyeCoordToScreen(float* projectionMatrix,const int Res,INT16* eyePoint3d,int type);
	DECLARE_WRITE_LINE_MEMBER(irqhandler);
=======
	void fill_slope( bitmap_ind16 &bitmap, const rectangle &cliprect, uint16_t header, int32_t x1, int32_t x2, int32_t sl1, int32_t sl2, int32_t y1, int32_t y2, int32_t *nx1, int32_t *nx2 );
	void fill_poly( bitmap_ind16 &bitmap, const rectangle &cliprect, const struct taitoair_poly *q );
>>>>>>> upstream/master
};
