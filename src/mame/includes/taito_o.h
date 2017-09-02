<<<<<<< HEAD
// license:LGPL-2.1+
=======
// license:BSD-3-Clause
>>>>>>> upstream/master
// copyright-holders:Tomasz Slanina
/*************************************************************************

    Taito O system

*************************************************************************/

<<<<<<< HEAD
=======
#include "machine/watchdog.h"
>>>>>>> upstream/master
#include "video/tc0080vco.h"

class taitoo_state : public driver_device
{
public:
	taitoo_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
<<<<<<< HEAD
=======
		m_watchdog(*this, "watchdog"),
>>>>>>> upstream/master
		m_tc0080vco(*this, "tc0080vco"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette") { }

	/* devices */
	required_device<cpu_device> m_maincpu;
<<<<<<< HEAD
=======
	required_device<watchdog_timer_device> m_watchdog;
>>>>>>> upstream/master
	required_device<tc0080vco_device> m_tc0080vco;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

	DECLARE_WRITE16_MEMBER(io_w);
	DECLARE_READ16_MEMBER(io_r);
<<<<<<< HEAD
	virtual void machine_start();
	UINT32 screen_update_parentj(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	uint32_t screen_update_parentj(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	TIMER_DEVICE_CALLBACK_MEMBER(parentj_interrupt);
	void parentj_draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect, int priority );
};
