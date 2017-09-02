// license:BSD-3-Clause
// copyright-holders:Takahiro Nogi
#include "includes/nb1413m3.h"
<<<<<<< HEAD
=======
#include "screen.h"
>>>>>>> upstream/master

class pastelg_state : public driver_device
{
public:
	enum
	{
		TIMER_BLITTER
	};

	pastelg_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag) ,
		m_maincpu(*this, "maincpu"),
		m_nb1413m3(*this, "nb1413m3"),
		m_screen(*this, "screen"),
		m_clut(*this, "clut") { }

	required_device<cpu_device> m_maincpu;
	required_device<nb1413m3_device> m_nb1413m3;
	required_device<screen_device> m_screen;
<<<<<<< HEAD
	required_shared_ptr<UINT8> m_clut;

	UINT8 m_mux_data;
=======
	required_shared_ptr<uint8_t> m_clut;

	uint8_t m_mux_data;
>>>>>>> upstream/master
	int m_blitter_destx;
	int m_blitter_desty;
	int m_blitter_sizex;
	int m_blitter_sizey;
	int m_blitter_src_addr;
	int m_gfxrom;
	int m_dispflag;
	int m_flipscreen;
	int m_blitter_direction_x;
	int m_blitter_direction_y;
	int m_palbank;
<<<<<<< HEAD
	UINT8 *m_videoram;
	int m_flipscreen_old;
=======
	std::unique_ptr<uint8_t[]> m_videoram;
	int m_flipscreen_old;
	emu_timer *m_blitter_timer;
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(pastelg_sndrom_r);
	DECLARE_READ8_MEMBER(pastelg_irq_ack_r);
	DECLARE_READ8_MEMBER(threeds_inputport1_r);
	DECLARE_READ8_MEMBER(threeds_inputport2_r);
	DECLARE_WRITE8_MEMBER(threeds_inputportsel_w);
	DECLARE_WRITE8_MEMBER(pastelg_blitter_w);
	DECLARE_WRITE8_MEMBER(threeds_romsel_w);
	DECLARE_WRITE8_MEMBER(threeds_output_w);
	DECLARE_READ8_MEMBER(threeds_rom_readback_r);
	DECLARE_WRITE8_MEMBER(pastelg_romsel_w);

	DECLARE_CUSTOM_INPUT_MEMBER(nb1413m3_busyflag_r);
	DECLARE_CUSTOM_INPUT_MEMBER(nb1413m3_hackbusyflag_r);

<<<<<<< HEAD
	virtual void machine_start();
	virtual void video_start();

	DECLARE_PALETTE_INIT(pastelg);
	UINT32 screen_update_pastelg(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	virtual void video_start() override;

	DECLARE_PALETTE_INIT(pastelg);
	uint32_t screen_update_pastelg(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	int pastelg_blitter_src_addr_r();
	void pastelg_vramflip();
	void pastelg_gfxdraw();

protected:
<<<<<<< HEAD
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
>>>>>>> upstream/master
};
