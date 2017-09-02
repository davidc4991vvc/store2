// license:BSD-3-Clause
// copyright-holders:Mike Balfour, Aaron Giles
/*************************************************************************

    Atari Cloud 9 (prototype) hardware

*************************************************************************/

#include "cpu/m6502/m6502.h"
<<<<<<< HEAD
#include "machine/x2212.h"
=======
#include "machine/74259.h"
#include "machine/x2212.h"
#include "screen.h"
>>>>>>> upstream/master

class cloud9_state : public driver_device
{
public:
	cloud9_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
			m_maincpu(*this, "maincpu"),
			m_nvram(*this, "nvram") ,
		m_spriteram(*this, "spriteram"),
		m_paletteram(*this, "paletteram"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
<<<<<<< HEAD
		m_palette(*this, "palette"){ }
=======
		m_palette(*this, "palette"),
		m_videolatch(*this, "videolatch") { }
>>>>>>> upstream/master

	/* devices */
	required_device<m6502_device> m_maincpu;
	required_device<x2212_device> m_nvram;
	/* memory pointers */
<<<<<<< HEAD
	UINT8 *     m_videoram;
	required_shared_ptr<UINT8> m_spriteram;
	required_shared_ptr<UINT8> m_paletteram;
=======
	std::unique_ptr<uint8_t[]>    m_videoram;
	required_shared_ptr<uint8_t> m_spriteram;
	required_shared_ptr<uint8_t> m_paletteram;
>>>>>>> upstream/master

	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
<<<<<<< HEAD

	/* video-related */
	const UINT8 *m_syncprom;
	const UINT8 *m_wpprom;
	const UINT8 *m_priprom;
=======
	required_device<ls259_device> m_videolatch;

	/* video-related */
	const uint8_t *m_syncprom;
	const uint8_t *m_wpprom;
	const uint8_t *m_priprom;
>>>>>>> upstream/master
	bitmap_ind16 m_spritebitmap;
	double      m_rweights[3];
	double      m_gweights[3];
	double      m_bweights[3];
<<<<<<< HEAD
	UINT8       m_video_control[8];
	UINT8       m_bitmode_addr[2];
=======
	uint8_t       m_bitmode_addr[2];
>>>>>>> upstream/master

	/* misc */
	int         m_vblank_start;
	int         m_vblank_end;
	emu_timer   *m_irq_timer;
<<<<<<< HEAD
	UINT8       m_irq_state;

	DECLARE_WRITE8_MEMBER(irq_ack_w);
	DECLARE_WRITE8_MEMBER(cloud9_led_w);
	DECLARE_WRITE8_MEMBER(cloud9_coin_counter_w);
	DECLARE_READ8_MEMBER(leta_r);
	DECLARE_WRITE8_MEMBER(nvram_recall_w);
	DECLARE_WRITE8_MEMBER(nvram_store_w);
	DECLARE_WRITE8_MEMBER(cloud9_video_control_w);
=======
	uint8_t       m_irq_state;

	DECLARE_WRITE8_MEMBER(irq_ack_w);
	DECLARE_WRITE_LINE_MEMBER(coin1_counter_w);
	DECLARE_WRITE_LINE_MEMBER(coin2_counter_w);
	DECLARE_WRITE_LINE_MEMBER(led1_w);
	DECLARE_WRITE_LINE_MEMBER(led2_w);
	DECLARE_READ8_MEMBER(leta_r);
	DECLARE_WRITE8_MEMBER(nvram_recall_w);
	DECLARE_WRITE8_MEMBER(nvram_store_w);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(cloud9_paletteram_w);
	DECLARE_WRITE8_MEMBER(cloud9_videoram_w);
	DECLARE_READ8_MEMBER(cloud9_bitmode_r);
	DECLARE_WRITE8_MEMBER(cloud9_bitmode_w);
	DECLARE_WRITE8_MEMBER(cloud9_bitmode_addr_w);
	DECLARE_CUSTOM_INPUT_MEMBER(get_vblank);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	UINT32 screen_update_cloud9(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	TIMER_CALLBACK_MEMBER(clock_irq);
	inline void cloud9_write_vram( UINT16 addr, UINT8 data, UINT8 bitmd, UINT8 pixba );
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	uint32_t screen_update_cloud9(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	TIMER_CALLBACK_MEMBER(clock_irq);
	inline void cloud9_write_vram( uint16_t addr, uint8_t data, uint8_t bitmd, uint8_t pixba );
>>>>>>> upstream/master
	inline void bitmode_autoinc(  );
	inline void schedule_next_irq(int curscanline);
};
