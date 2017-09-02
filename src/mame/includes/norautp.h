// license:BSD-3-Clause
// copyright-holders:Angelo Salese, Roberto Fresca
<<<<<<< HEAD
#include "sound/discrete.h"
=======
#include "machine/i8255.h"
#include "sound/discrete.h"
#include "screen.h"
>>>>>>> upstream/master


/* Discrete Sound Input Nodes */
#define NORAUTP_SND_EN                  NODE_01
#define NORAUTP_FREQ_DATA               NODE_02


class norautp_state : public driver_device
{
public:
	norautp_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag) ,
		m_maincpu(*this, "maincpu"),
<<<<<<< HEAD
		m_discrete(*this, "discrete"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette")  { }

	UINT16 *m_np_vram;
	UINT16 m_np_addr;
	DECLARE_READ8_MEMBER(test_r);
	DECLARE_READ8_MEMBER(vram_data_r);
	DECLARE_WRITE8_MEMBER(vram_data_w);
	DECLARE_WRITE8_MEMBER(vram_addr_w);
=======
		m_ppi8255(*this, "ppi8255_%u", 0),
		m_discrete(*this, "discrete"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette")  { }

	std::unique_ptr<uint16_t[]> m_np_vram;
	DECLARE_WRITE_LINE_MEMBER(ppi2_obf_w);
	TIMER_CALLBACK_MEMBER(ppi2_ack);
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(test2_r);
	DECLARE_WRITE8_MEMBER(mainlamps_w);
	DECLARE_WRITE8_MEMBER(soundlamps_w);
	DECLARE_WRITE8_MEMBER(counterlamps_w);
	DECLARE_DRIVER_INIT(ssa);
	DECLARE_DRIVER_INIT(enc);
	DECLARE_DRIVER_INIT(deb);
<<<<<<< HEAD
	virtual void video_start();
	DECLARE_PALETTE_INIT(norautp);
	UINT32 screen_update_norautp(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	required_device<cpu_device> m_maincpu;
	required_device<discrete_device> m_discrete;
	required_device<gfxdecode_device> m_gfxdecode;
=======
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(norautp);
	uint32_t screen_update_norautp(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	required_device<cpu_device> m_maincpu;
	required_device_array<i8255_device, 3> m_ppi8255;
	required_device<discrete_device> m_discrete;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
>>>>>>> upstream/master
	required_device<palette_device> m_palette;
};

/*----------- defined in audio/norautp.c -----------*/
DISCRETE_SOUND_EXTERN( norautp );
DISCRETE_SOUND_EXTERN( dphl );
DISCRETE_SOUND_EXTERN( kimble );
