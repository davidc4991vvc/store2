// license:BSD-3-Clause
// copyright-holders:Brad Oliver
/*************************************************************************

    Zero Zone

*************************************************************************/

<<<<<<< HEAD
#include "emu.h"
=======
#include "machine/gen_latch.h"
>>>>>>> upstream/master
#include "cpu/z80/z80.h"

class zerozone_state : public driver_device
{
public:
	zerozone_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
			m_maincpu(*this, "maincpu"),
			m_audiocpu(*this, "audiocpu"),
<<<<<<< HEAD
=======
			m_soundlatch(*this, "soundlatch"),
>>>>>>> upstream/master
			m_vram(*this, "videoram"),
			m_gfxdecode(*this, "gfxdecode")
	{ }

	// in drivers/zerozone.c
	DECLARE_WRITE16_MEMBER(sound_w);

	// in video/zerozone.c
	DECLARE_WRITE16_MEMBER(tilemap_w);
	DECLARE_WRITE16_MEMBER(tilebank_w);

	// devices
	required_device<cpu_device> m_maincpu;
	required_device<z80_device> m_audiocpu;
<<<<<<< HEAD

	// shared pointers
	required_shared_ptr<UINT16> m_vram;
=======
	required_device<generic_latch_8_device> m_soundlatch;

	// shared pointers
	required_shared_ptr<uint16_t> m_vram;
>>>>>>> upstream/master
	// currently this driver uses generic palette handling

	required_device<gfxdecode_device> m_gfxdecode;
	// state
	// video-related
<<<<<<< HEAD
	UINT16         m_tilebank;
	tilemap_t     *m_zz_tilemap;

	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	uint16_t         m_tilebank;
	tilemap_t     *m_zz_tilemap;

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master

protected:

	// driver_device overrides
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();

	virtual void video_start();
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;

	virtual void video_start() override;
>>>>>>> upstream/master
	TILE_GET_INFO_MEMBER(get_zerozone_tile_info);
};
