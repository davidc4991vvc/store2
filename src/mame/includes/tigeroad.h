// license:BSD-3-Clause
// copyright-holders:Phil Stroffolino
<<<<<<< HEAD
#include "video/bufsprite.h"
#include "sound/msm5205.h"
#include "cpu/m68000/m68000.h"
#include "cpu/z80/z80.h"
#include "sound/2203intf.h"
#include "sound/msm5205.h"
#include "cpu/m6805/m6805.h"
#include "video/tigeroad_spr.h"
=======

#include "video/tigeroad_spr.h"

#include "cpu/m68000/m68000.h"
#include "cpu/m6805/m68705.h"
#include "cpu/z80/z80.h"

#include "machine/gen_latch.h"

#include "sound/2203intf.h"
#include "sound/msm5205.h"

#include "video/bufsprite.h"

>>>>>>> upstream/master

class tigeroad_state : public driver_device
{
public:
	tigeroad_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
<<<<<<< HEAD
			m_spriteram(*this, "spriteram") ,
=======
		m_spriteram(*this, "spriteram"),
>>>>>>> upstream/master
		m_videoram(*this, "videoram"),
		m_ram16(*this, "ram16"),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_msm(*this, "msm"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
<<<<<<< HEAD
		m_mcu(*this, "mcu"),
		m_spritegen(*this, "spritegen"),
		m_has_coinlock(1)
	{ }

	required_device<buffered_spriteram16_device> m_spriteram;
	required_shared_ptr<UINT16> m_videoram;
	required_shared_ptr<UINT16> m_ram16;
=======
		m_spritegen(*this, "spritegen"),
		m_soundlatch(*this, "soundlatch"),
		m_has_coinlock(true)
	{ }

	required_device<buffered_spriteram16_device> m_spriteram;
	required_shared_ptr<uint16_t> m_videoram;
	required_shared_ptr<uint16_t> m_ram16;
>>>>>>> upstream/master
	int m_bgcharbank;
	tilemap_t *m_bg_tilemap;
	tilemap_t *m_fg_tilemap;
	DECLARE_WRITE16_MEMBER(f1dream_control_w);
	DECLARE_WRITE16_MEMBER(tigeroad_soundcmd_w);
	DECLARE_WRITE16_MEMBER(tigeroad_videoram_w);
	DECLARE_WRITE16_MEMBER(tigeroad_videoctrl_w);
	DECLARE_WRITE16_MEMBER(tigeroad_scroll_w);
	DECLARE_WRITE8_MEMBER(msm5205_w);
	DECLARE_DRIVER_INIT(f1dream);
<<<<<<< HEAD
	DECLARE_DRIVER_INIT(pushman);
	DECLARE_DRIVER_INIT(bballs);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
	TILEMAP_MAPPER_MEMBER(tigeroad_tilemap_scan);
	virtual void video_start();
	UINT32 screen_update_tigeroad(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void f1dream_protection_w(address_space &space);
	DECLARE_WRITE_LINE_MEMBER(irqhandler);
=======
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
	TILEMAP_MAPPER_MEMBER(tigeroad_tilemap_scan);
	virtual void video_start() override;
	uint32_t screen_update_tigeroad(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void f1dream_protection_w(address_space &space);
>>>>>>> upstream/master
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	optional_device<msm5205_device> m_msm;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
<<<<<<< HEAD
	optional_device<cpu_device> m_mcu;
	required_device<tigeroad_spr_device> m_spritegen;

	UINT16     m_control[2];

	/* misc */
	UINT8      m_shared_ram[8];
	UINT16     m_latch;
	UINT16     m_new_latch;
	int m_has_coinlock;

	/* protection handling */
	DECLARE_READ16_MEMBER(pushman_68705_r);
	DECLARE_WRITE16_MEMBER(pushman_68705_w);
	DECLARE_READ16_MEMBER(bballs_68705_r);
	DECLARE_WRITE16_MEMBER(bballs_68705_w);
	DECLARE_READ8_MEMBER(pushman_68000_r);
	DECLARE_WRITE8_MEMBER(pushman_68000_w);
	DECLARE_MACHINE_RESET(pushman);
	DECLARE_MACHINE_RESET(bballs);

	virtual void machine_start();

=======
	required_device<tigeroad_spr_device> m_spritegen;
	required_device<generic_latch_8_device> m_soundlatch;

protected:
	/* misc */
	bool m_has_coinlock;
};


class pushman_state : public tigeroad_state
{
public:
	pushman_state(const machine_config &mconfig, device_type type, const char *tag)
		: tigeroad_state(mconfig, type, tag)
		, m_mcu(*this, "mcu")
		, m_host_semaphore(false)
		, m_mcu_semaphore(false)
		, m_host_latch(0xffff)
		, m_mcu_latch(0xffff)
		, m_mcu_output(0xffff)
		, m_mcu_latch_ctl(0xff)
	{
		m_has_coinlock = false;
	}

	DECLARE_READ16_MEMBER(mcu_comm_r);
	DECLARE_WRITE16_MEMBER(pushman_mcu_comm_w);
	DECLARE_WRITE16_MEMBER(bballs_mcu_comm_w);

	DECLARE_WRITE8_MEMBER(mcu_pa_w);
	DECLARE_WRITE8_MEMBER(mcu_pb_w);
	DECLARE_WRITE8_MEMBER(mcu_pc_w);

protected:
	virtual void machine_start() override;

	required_device<m68705u_device> m_mcu;

	bool    m_host_semaphore, m_mcu_semaphore;
	u16     m_host_latch, m_mcu_latch;
	u16     m_mcu_output;
	u8      m_mcu_latch_ctl;
>>>>>>> upstream/master
};
