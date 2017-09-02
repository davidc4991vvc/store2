// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/*************************************************************************

    Atari Shuuz hardware

*************************************************************************/

#include "machine/atarigen.h"
#include "video/atarimo.h"

class shuuz_state : public atarigen_state
{
public:
	shuuz_state(const machine_config &mconfig, device_type type, const char *tag)
		: atarigen_state(mconfig, type, tag),
			m_vad(*this, "vad") { }

	required_device<atari_vad_device> m_vad;

	int m_cur[2];

<<<<<<< HEAD
	virtual void update_interrupts();
=======
	virtual void update_interrupts() override;
>>>>>>> upstream/master

	DECLARE_WRITE16_MEMBER(latch_w);
	DECLARE_READ16_MEMBER(leta_r);
	DECLARE_READ16_MEMBER(special_port0_r);

<<<<<<< HEAD
	virtual void machine_start();

	TILE_GET_INFO_MEMBER(get_playfield_tile_info);

	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;

	TILE_GET_INFO_MEMBER(get_playfield_tile_info);

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master

	static const atari_motion_objects_config s_mob_config;
};
