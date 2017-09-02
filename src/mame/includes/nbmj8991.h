// license:BSD-3-Clause
// copyright-holders:Takahiro Nogi
<<<<<<< HEAD
#include "includes/nb1413m3.h"
=======

#include "includes/nb1413m3.h"
#include "machine/gen_latch.h"
#include "screen.h"
>>>>>>> upstream/master

class nbmj8991_state : public driver_device
{
public:
	nbmj8991_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag) ,
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_nb1413m3(*this, "nb1413m3"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"),
<<<<<<< HEAD
=======
		m_soundlatch(*this, "soundlatch"),
>>>>>>> upstream/master
		m_generic_paletteram_8(*this, "paletteram") { }

	required_device<cpu_device> m_maincpu;
	optional_device<cpu_device> m_audiocpu;
	required_device<nb1413m3_device> m_nb1413m3;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
<<<<<<< HEAD

	required_shared_ptr<UINT8> m_generic_paletteram_8;
=======
	optional_device<generic_latch_8_device> m_soundlatch;

	required_shared_ptr<uint8_t> m_generic_paletteram_8;
>>>>>>> upstream/master

	enum
	{
		TIMER_BLITTER
	};

	int m_scrollx;
	int m_scrolly;
	int m_blitter_destx;
	int m_blitter_desty;
	int m_blitter_sizex;
	int m_blitter_sizey;
	int m_blitter_src_addr;
	int m_blitter_direction_x;
	int m_blitter_direction_y;
	int m_gfxrom;
	int m_dispflag;
	int m_flipscreen;
	int m_clutsel;
	int m_screen_refresh;
	bitmap_ind16 m_tmpbitmap;
<<<<<<< HEAD
	UINT8 *m_videoram;
	UINT8 *m_clut;
=======
	std::unique_ptr<uint8_t[]> m_videoram;
	std::unique_ptr<uint8_t[]> m_clut;
>>>>>>> upstream/master
	int m_flipscreen_old;
	emu_timer *m_blitter_timer;

	DECLARE_WRITE8_MEMBER(soundbank_w);
	DECLARE_WRITE8_MEMBER(palette_type1_w);
	DECLARE_WRITE8_MEMBER(palette_type2_w);
	DECLARE_WRITE8_MEMBER(palette_type3_w);
	DECLARE_WRITE8_MEMBER(blitter_w);
	DECLARE_READ8_MEMBER(clut_r);
	DECLARE_WRITE8_MEMBER(clut_w);
	DECLARE_CUSTOM_INPUT_MEMBER(nb1413m3_busyflag_r);

	DECLARE_DRIVER_INIT(galkaika);
	DECLARE_DRIVER_INIT(tokimbsj);
	DECLARE_DRIVER_INIT(tokyogal);
	DECLARE_DRIVER_INIT(finalbny);
<<<<<<< HEAD
	virtual void machine_reset();
	virtual void video_start();

	UINT32 screen_update_type1(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_type2(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_reset() override;
	virtual void video_start() override;

	uint32_t screen_update_type1(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_type2(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void vramflip();
	void update_pixel(int x, int y);
	void gfxdraw();

	void postload();

protected:
<<<<<<< HEAD
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
>>>>>>> upstream/master
};
