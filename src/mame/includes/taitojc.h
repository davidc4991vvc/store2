// license:LGPL-2.1+
// copyright-holders:Ville Linde, Angelo Salese, hap
/*************************************************************************

  Taito JC System

*************************************************************************/

<<<<<<< HEAD
#include "video/poly.h"
#include "machine/taitoio.h"

#define TAITOJC_POLYGON_FIFO_SIZE       0x20000

struct taitojc_polydata
{
	int tex_base_x;
	int tex_base_y;
	int tex_wrap_x;
	int tex_wrap_y;
};

class taitojc_renderer : public poly_manager<float, taitojc_polydata, 6, 10000>
{
public:
	taitojc_renderer(running_machine &machine, bitmap_ind16 *fb, bitmap_ind16 *zb, const UINT8 *texture_ram)
		: poly_manager<float, taitojc_polydata, 6, 10000>(machine)
	{
		m_framebuffer = fb;
		m_zbuffer = zb;
		m_texture = texture_ram;
	}

	void render_solid_scan(INT32 scanline, const extent_t &extent, const taitojc_polydata &extradata, int threadid);
	void render_shade_scan(INT32 scanline, const extent_t &extent, const taitojc_polydata &extradata, int threadid);
	void render_texture_scan(INT32 scanline, const extent_t &extent, const taitojc_polydata &extradata, int threadid);

	void render_polygons(UINT16 *polygon_fifo, int length);

private:
	bitmap_ind16 *m_framebuffer;
	bitmap_ind16 *m_zbuffer;
	const UINT8 *m_texture;
};
=======
#include "video/tc0780fpa.h"
#include "machine/taitoio.h"
#include "screen.h"
>>>>>>> upstream/master

class taitojc_state : public driver_device
{
public:
	taitojc_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this,"maincpu"),
		m_dsp(*this,"dsp"),
		m_tc0640fio(*this, "tc0640fio"),
		m_gfx2(*this, "gfx2"),
		m_vram(*this, "vram"),
		m_objlist(*this, "objlist"),
<<<<<<< HEAD
		m_snd_shared_ram(*this, "snd_shared"),
=======
>>>>>>> upstream/master
		m_main_ram(*this, "main_ram"),
		m_dsp_shared_ram(*this, "dsp_shared"),
		m_palette_ram(*this, "palette_ram"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"),
<<<<<<< HEAD
		m_analog_ports(*this, "AN")
=======
		m_analog_ports(*this, "AN.%u", 0),
		m_tc0780fpa(*this, "tc0780fpa")
>>>>>>> upstream/master
	{
		m_mcu_output = 0;
		m_speed_meter = 0;
		m_brake_meter = 0;
	}

	// device/memory pointers
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_dsp;
	required_device<tc0640fio_device> m_tc0640fio;
	required_memory_region m_gfx2;

<<<<<<< HEAD
	required_shared_ptr<UINT32> m_vram;
	required_shared_ptr<UINT32> m_objlist;
	required_shared_ptr<UINT32> m_snd_shared_ram;
	required_shared_ptr<UINT32> m_main_ram;
	required_shared_ptr<UINT16> m_dsp_shared_ram;
	required_shared_ptr<UINT32> m_palette_ram;
=======
	required_shared_ptr<uint32_t> m_vram;
	required_shared_ptr<uint32_t> m_objlist;
	required_shared_ptr<uint32_t> m_main_ram;
	required_shared_ptr<uint16_t> m_dsp_shared_ram;
	required_shared_ptr<uint32_t> m_palette_ram;
>>>>>>> upstream/master

	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
	optional_ioport_array<8> m_analog_ports;

<<<<<<< HEAD
	taitojc_renderer *m_renderer;

	int m_texture_x;
	int m_texture_y;

	UINT32 m_dsp_rom_pos;
	UINT16 m_dsp_tex_address;
	UINT16 m_dsp_tex_offset;

	int m_first_dsp_reset;
	INT16 m_viewport_data[3];
	INT16 m_projection_data[3];
	INT16 m_intersection_data[3];

	UINT8 *m_texture;
	bitmap_ind16 m_framebuffer;
	bitmap_ind16 m_zbuffer;

	int m_gfx_index;

	UINT32 *m_char_ram;
	UINT32 *m_tile_ram;
	tilemap_t *m_tilemap;

	UINT16 *m_polygon_fifo;
	int m_polygon_fifo_ptr;

	UINT8 m_mcu_comm_main;
	UINT8 m_mcu_comm_hc11;
	UINT8 m_mcu_data_main;
	UINT8 m_mcu_data_hc11;
	UINT8 m_mcu_output;

	UINT8 m_has_dsp_hack;
=======
	required_device<tc0780fpa_device> m_tc0780fpa;

	uint32_t m_dsp_rom_pos;

	int m_first_dsp_reset;
	int16_t m_viewport_data[3];
	int16_t m_projection_data[3];
	int16_t m_intersection_data[3];

	int m_gfx_index;

	std::unique_ptr<uint32_t[]> m_char_ram;
	std::unique_ptr<uint32_t[]> m_tile_ram;
	tilemap_t *m_tilemap;

	uint8_t m_mcu_comm_main;
	uint8_t m_mcu_comm_hc11;
	uint8_t m_mcu_data_main;
	uint8_t m_mcu_data_hc11;
	uint8_t m_mcu_output;

	uint8_t m_has_dsp_hack;
>>>>>>> upstream/master

	int m_speed_meter;
	int m_brake_meter;

<<<<<<< HEAD
	DECLARE_READ8_MEMBER(mcu_comm_r);
	DECLARE_WRITE8_MEMBER(mcu_comm_w);
	DECLARE_READ32_MEMBER(snd_share_r);
	DECLARE_WRITE32_MEMBER(snd_share_w);
=======
	DECLARE_WRITE8_MEMBER(coin_control_w);

	DECLARE_READ8_MEMBER(mcu_comm_r);
	DECLARE_WRITE8_MEMBER(mcu_comm_w);
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(jc_pcbid_r);
	DECLARE_READ8_MEMBER(jc_lan_r);
	DECLARE_WRITE8_MEMBER(jc_lan_w);
	DECLARE_WRITE8_MEMBER(jc_irq_unk_w);
	DECLARE_WRITE8_MEMBER(dendego_speedmeter_w);
	DECLARE_WRITE8_MEMBER(dendego_brakemeter_w);

	DECLARE_READ8_MEMBER(hc11_comm_r);
	DECLARE_WRITE8_MEMBER(hc11_comm_w);
	DECLARE_WRITE8_MEMBER(hc11_output_w);
	DECLARE_READ8_MEMBER(hc11_data_r);
	DECLARE_READ8_MEMBER(hc11_output_r);
	DECLARE_WRITE8_MEMBER(hc11_data_w);
	DECLARE_READ8_MEMBER(hc11_analog_r);

	DECLARE_READ16_MEMBER(dsp_shared_r);
	DECLARE_WRITE16_MEMBER(dsp_shared_w);
	DECLARE_READ16_MEMBER(dsp_to_main_7fe_r);
	DECLARE_WRITE16_MEMBER(dsp_to_main_7fe_w);
	DECLARE_WRITE16_MEMBER(main_to_dsp_7ff_w);

	DECLARE_READ16_MEMBER(dsp_rom_r);
	DECLARE_WRITE16_MEMBER(dsp_rom_w);
<<<<<<< HEAD
	DECLARE_WRITE16_MEMBER(dsp_texture_w);
	DECLARE_READ16_MEMBER(dsp_texaddr_r);
	DECLARE_WRITE16_MEMBER(dsp_texaddr_w);
	DECLARE_WRITE16_MEMBER(dsp_polygon_fifo_w);
	DECLARE_WRITE16_MEMBER(dsp_unk2_w);
=======
>>>>>>> upstream/master

	DECLARE_WRITE16_MEMBER(dsp_math_viewport_w);
	DECLARE_WRITE16_MEMBER(dsp_math_projection_w);
	DECLARE_READ16_MEMBER(dsp_math_projection_y_r);
	DECLARE_READ16_MEMBER(dsp_math_projection_x_r);
	DECLARE_WRITE16_MEMBER(dsp_math_intersection_w);
	DECLARE_READ16_MEMBER(dsp_math_intersection_r);
	DECLARE_READ16_MEMBER(dsp_math_unk_r);

	DECLARE_READ16_MEMBER(taitojc_dsp_idle_skip_r);
	DECLARE_READ16_MEMBER(dendego2_dsp_idle_skip_r);

	DECLARE_READ32_MEMBER(taitojc_palette_r);
	DECLARE_WRITE32_MEMBER(taitojc_palette_w);
	DECLARE_READ32_MEMBER(taitojc_tile_r);
	DECLARE_READ32_MEMBER(taitojc_char_r);
	DECLARE_WRITE32_MEMBER(taitojc_tile_w);
	DECLARE_WRITE32_MEMBER(taitojc_char_w);
	DECLARE_DRIVER_INIT(dendego2);
	DECLARE_DRIVER_INIT(dangcurv);
	DECLARE_DRIVER_INIT(taitojc);
	TILE_GET_INFO_MEMBER(taitojc_tile_info);
<<<<<<< HEAD
	virtual void machine_reset();
	virtual void machine_start();
	virtual void video_start();
	UINT32 screen_update_taitojc(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_dendego(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	INTERRUPT_GEN_MEMBER(taitojc_vblank);
	void draw_object(bitmap_ind16 &bitmap, const rectangle &cliprect, UINT32 w1, UINT32 w2, UINT8 bank_type);
	void draw_object_bank(bitmap_ind16 &bitmap, const rectangle &cliprect, UINT8 bank_type, UINT8 pri);
	void taitojc_clear_frame();
=======
	virtual void machine_reset() override;
	virtual void machine_start() override;
	virtual void video_start() override;
	uint32_t screen_update_taitojc(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_dendego(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	INTERRUPT_GEN_MEMBER(taitojc_vblank);
	void draw_object(bitmap_ind16 &bitmap, const rectangle &cliprect, uint32_t w1, uint32_t w2, uint8_t bank_type);
	void draw_object_bank(bitmap_ind16 &bitmap, const rectangle &cliprect, uint8_t bank_type, uint8_t pri);
>>>>>>> upstream/master
};
