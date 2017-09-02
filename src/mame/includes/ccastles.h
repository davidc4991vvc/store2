<<<<<<< HEAD
// license:???
// copyright-holders:Patrick Lawrence, Aaron Giles
=======
// license:BSD-3-Clause
// copyright-holders:Aaron Giles
>>>>>>> upstream/master
/*************************************************************************

    Atari Crystal Castles hardware

*************************************************************************/

#include "cpu/m6502/m6502.h"
#include "machine/x2212.h"
<<<<<<< HEAD
=======
#include "screen.h"
>>>>>>> upstream/master

class ccastles_state : public driver_device
{
public:
	ccastles_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
			m_maincpu(*this, "maincpu"),
			m_nvram_4b(*this, "nvram_4b"),
			m_nvram_4a(*this, "nvram_4a") ,
		m_videoram(*this, "videoram"),
		m_spriteram(*this, "spriteram"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"){ }

	/* devices */
	required_device<m6502_device> m_maincpu;
	required_device<x2212_device> m_nvram_4b;
	required_device<x2212_device> m_nvram_4a;
	/* memory pointers */
<<<<<<< HEAD
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_spriteram;
=======
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_spriteram;
>>>>>>> upstream/master

	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;

	/* video-related */
<<<<<<< HEAD
	const UINT8 *m_syncprom;
	const UINT8 *m_wpprom;
	const UINT8 *m_priprom;
=======
	const uint8_t *m_syncprom;
	const uint8_t *m_wpprom;
	const uint8_t *m_priprom;
>>>>>>> upstream/master
	bitmap_ind16 m_spritebitmap;
	double m_rweights[3];
	double m_gweights[3];
	double m_bweights[3];
<<<<<<< HEAD
	UINT8 m_video_control[8];
	UINT8 m_bitmode_addr[2];
	UINT8 m_hscroll;
	UINT8 m_vscroll;
=======
	uint8_t m_video_control[8];
	uint8_t m_bitmode_addr[2];
	uint8_t m_hscroll;
	uint8_t m_vscroll;
>>>>>>> upstream/master

	/* misc */
	int      m_vblank_start;
	int      m_vblank_end;
	emu_timer *m_irq_timer;
<<<<<<< HEAD
	UINT8    m_irq_state;
	UINT8    m_nvram_store[2];
=======
	uint8_t    m_irq_state;
	uint8_t    m_nvram_store[2];
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER(irq_ack_w);
	DECLARE_WRITE8_MEMBER(led_w);
	DECLARE_WRITE8_MEMBER(ccounter_w);
	DECLARE_WRITE8_MEMBER(bankswitch_w);
	DECLARE_READ8_MEMBER(leta_r);
	DECLARE_WRITE8_MEMBER(nvram_recall_w);
	DECLARE_WRITE8_MEMBER(nvram_store_w);
	DECLARE_READ8_MEMBER(nvram_r);
	DECLARE_WRITE8_MEMBER(nvram_w);
	DECLARE_WRITE8_MEMBER(ccastles_hscroll_w);
	DECLARE_WRITE8_MEMBER(ccastles_vscroll_w);
	DECLARE_WRITE8_MEMBER(ccastles_video_control_w);
	DECLARE_WRITE8_MEMBER(ccastles_paletteram_w);
	DECLARE_WRITE8_MEMBER(ccastles_videoram_w);
	DECLARE_READ8_MEMBER(ccastles_bitmode_r);
	DECLARE_WRITE8_MEMBER(ccastles_bitmode_w);
	DECLARE_WRITE8_MEMBER(ccastles_bitmode_addr_w);
	DECLARE_CUSTOM_INPUT_MEMBER(get_vblank);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	UINT32 screen_update_ccastles(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	TIMER_CALLBACK_MEMBER(clock_irq);
	inline void ccastles_write_vram( UINT16 addr, UINT8 data, UINT8 bitmd, UINT8 pixba );
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	uint32_t screen_update_ccastles(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	TIMER_CALLBACK_MEMBER(clock_irq);
	inline void ccastles_write_vram( uint16_t addr, uint8_t data, uint8_t bitmd, uint8_t pixba );
>>>>>>> upstream/master
	inline void bitmode_autoinc(  );
	inline void schedule_next_irq( int curscanline );
};
