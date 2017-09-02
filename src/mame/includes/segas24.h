// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/*
 * Sega System 24
 *
 */

#include "video/segaic24.h"
#include "sound/dac.h"
<<<<<<< HEAD
=======
#include "screen.h"
>>>>>>> upstream/master

class segas24_state : public driver_device
{
public:
	segas24_state(const machine_config &mconfig, device_type type, const char *tag)
<<<<<<< HEAD
		: driver_device(mconfig, type, tag) ,
		m_maincpu(*this, "maincpu"),
		m_subcpu(*this, "subcpu"),
		m_dac(*this, "dac"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"),
		m_generic_paletteram_16(*this, "paletteram")
	{ }

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_subcpu;
	required_device<dac_device> m_dac;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
	required_shared_ptr<UINT16> m_generic_paletteram_16;

	static const UINT8  mahmajn_mlt[8];
	static const UINT8 mahmajn2_mlt[8];
	static const UINT8      qgh_mlt[8];
	static const UINT8 bnzabros_mlt[8];
	static const UINT8   qrouka_mlt[8];
	static const UINT8 quizmeku_mlt[8];
	static const UINT8   dcclub_mlt[8];
=======
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
		, m_subcpu(*this, "subcpu")
		, m_dac(*this, "dac")
		, m_screen(*this, "screen")
		, m_palette(*this, "palette")
		, m_generic_paletteram_16(*this, "paletteram")
		, m_romboard(*this, "romboard")
		, m_gground_hack_timer(nullptr)
		, m_p1(*this, "P1")
		, m_p2(*this, "P2")
		, m_p3(*this, "P3")
		, m_paddle(*this, "PADDLE")
		, m_dials(*this, {"DIAL1", "DIAL2", "DIAL3", "DIAL4"})
		, m_mj_inputs(*this, {"MJ0", "MJ1", "MJ2", "MJ3", "MJ4", "MJ5", "P1", "P2"})
	{
	}

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_subcpu;
	required_device<dac_byte_interface> m_dac;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
	required_shared_ptr<uint16_t> m_generic_paletteram_16;
	optional_memory_region m_romboard;

	static const uint8_t  mahmajn_mlt[8];
	static const uint8_t mahmajn2_mlt[8];
	static const uint8_t      qgh_mlt[8];
	static const uint8_t bnzabros_mlt[8];
	static const uint8_t   qrouka_mlt[8];
	static const uint8_t quizmeku_mlt[8];
	static const uint8_t   dcclub_mlt[8];
>>>>>>> upstream/master

	int fdc_status;
	int fdc_track;
	int fdc_sector;
	int fdc_data;
	int fdc_phys_track;
	int fdc_irq;
	int fdc_drq;
	int fdc_span;
	int fdc_index_count;
<<<<<<< HEAD
	UINT8 *fdc_pt;
	int track_size;
	int cur_input_line;
	UINT8 hotrod_ctrl_cur;
	UINT8 resetcontrol;
	UINT8 prev_resetcontrol;
	UINT8 curbank;
	UINT8 mlatch;
	const UINT8 *mlatch_table;

	UINT16 irq_tdata, irq_tval;
	UINT8 irq_tmode, irq_allow0, irq_allow1;
=======
	uint8_t *fdc_pt;
	int track_size;
	int cur_input_line;
	uint8_t curbank;
	uint8_t mlatch;
	const uint8_t *mlatch_table;

	uint16_t irq_tdata, irq_tval;
	uint8_t irq_tmode, irq_allow0, irq_allow1;
>>>>>>> upstream/master
	int irq_timer_pend0;
	int irq_timer_pend1;
	int irq_yms;
	int irq_vblank;
	int irq_sprite;
	attotime irq_synctime, irq_vsynctime;
	timer_device *irq_timer;
	timer_device *irq_timer_clear;
	//timer_device *irq_frc;
	timer_device *frc_cnt_timer;
<<<<<<< HEAD
	UINT8 frc_mode;

	UINT16 *shared_ram;
	UINT8 (segas24_state::*io_r)(UINT8 port);
	void (segas24_state::*io_w)(UINT8 port, UINT8 data);
	UINT8 io_cnt, io_dir;

	segas24_tile *vtile;
	segas24_sprite *vsprite;
	segas24_mixer *vmixer;
=======
	uint8_t frc_mode;

	bool m_cnt1;

	uint16_t *shared_ram;

	segas24_tile_device *vtile;
	segas24_sprite_device *vsprite;
	segas24_mixer_device *vmixer;
>>>>>>> upstream/master

	DECLARE_WRITE_LINE_MEMBER(irq_ym);
	DECLARE_READ16_MEMBER(  sys16_paletteram_r );
	DECLARE_WRITE16_MEMBER( sys16_paletteram_w );
	DECLARE_READ16_MEMBER(  irq_r );
	DECLARE_WRITE16_MEMBER( irq_w );
	DECLARE_READ16_MEMBER(  fdc_r );
	DECLARE_WRITE16_MEMBER( fdc_w );
	DECLARE_READ16_MEMBER(  fdc_status_r );
	DECLARE_WRITE16_MEMBER( fdc_ctrl_w );
	DECLARE_READ16_MEMBER(  curbank_r );
	DECLARE_WRITE16_MEMBER( curbank_w );
	DECLARE_READ8_MEMBER(  frc_mode_r );
	DECLARE_WRITE8_MEMBER( frc_mode_w );
	DECLARE_READ8_MEMBER(  frc_r );
	DECLARE_WRITE8_MEMBER( frc_w );
	DECLARE_READ16_MEMBER(  mlatch_r );
	DECLARE_WRITE16_MEMBER( mlatch_w );
<<<<<<< HEAD
	DECLARE_READ16_MEMBER(  hotrod3_ctrl_r );
	DECLARE_WRITE16_MEMBER( hotrod3_ctrl_w );
	DECLARE_READ16_MEMBER(  iod_r );
	DECLARE_WRITE16_MEMBER( iod_w );
	DECLARE_READ16_MEMBER ( sys16_io_r );
	DECLARE_WRITE16_MEMBER( sys16_io_w );

	UINT8 hotrod_io_r(UINT8 port);
	UINT8 dcclub_io_r(UINT8 port);
	UINT8 mahmajn_io_r(UINT8 port);

	void hotrod_io_w(UINT8 port, UINT8 data);
	void mahmajn_io_w(UINT8 port, UINT8 data);
=======
	DECLARE_READ8_MEMBER(   dials_r );
	DECLARE_READ16_MEMBER(  iod_r );
	DECLARE_WRITE16_MEMBER( iod_w );

	READ8_MEMBER(dcclub_p1_r);
	READ8_MEMBER(dcclub_p3_r);
	READ8_MEMBER(mahmajn_input_line_r);
	READ8_MEMBER(mahmajn_inputs_r);

	WRITE8_MEMBER(mahmajn_mux_w);
	WRITE8_MEMBER(hotrod_lamps_w);
>>>>>>> upstream/master

	void fdc_init();
	void reset_reset();
	void reset_bank();
	void irq_init();
	void irq_timer_sync();
	void irq_timer_start(int old_tmode);
<<<<<<< HEAD
	void reset_control_w(UINT8 data);
=======
	WRITE_LINE_MEMBER(cnt1);
>>>>>>> upstream/master
	DECLARE_DRIVER_INIT(crkdown);
	DECLARE_DRIVER_INIT(quizmeku);
	DECLARE_DRIVER_INIT(qrouka);
	DECLARE_DRIVER_INIT(roughrac);
	DECLARE_DRIVER_INIT(qgh);
	DECLARE_DRIVER_INIT(gground);
	DECLARE_DRIVER_INIT(mahmajn2);
	DECLARE_DRIVER_INIT(sspiritj);
	DECLARE_DRIVER_INIT(mahmajn);
	DECLARE_DRIVER_INIT(hotrod);
	DECLARE_DRIVER_INIT(sspirits);
	DECLARE_DRIVER_INIT(dcclub);
	DECLARE_DRIVER_INIT(bnzabros);
	DECLARE_DRIVER_INIT(dcclubfd);
	DECLARE_DRIVER_INIT(qsww);
	DECLARE_DRIVER_INIT(sgmast);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	UINT32 screen_update_system24(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	uint32_t screen_update_system24(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	TIMER_DEVICE_CALLBACK_MEMBER(irq_timer_cb);
	TIMER_DEVICE_CALLBACK_MEMBER(irq_timer_clear_cb);
	TIMER_DEVICE_CALLBACK_MEMBER(irq_frc_cb);
	TIMER_DEVICE_CALLBACK_MEMBER(irq_vbl);
<<<<<<< HEAD
=======

	// game specific
	TIMER_CALLBACK_MEMBER(gground_hack_timer_callback);
	emu_timer *m_gground_hack_timer;
	required_ioport m_p1;
	required_ioport m_p2;
	required_ioport m_p3;
	optional_ioport m_paddle;
	optional_ioport_array<4> m_dials;
	optional_ioport_array<8> m_mj_inputs;
>>>>>>> upstream/master
};
