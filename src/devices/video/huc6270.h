// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
/**********************************************************************

    Hudson/NEC HuC6270 interface

**********************************************************************/

<<<<<<< HEAD
#ifndef __HUC6270_H_
#define __HUC6270_H_

#include "emu.h"
=======
#ifndef MAME_VIDEO_HUC6270_H
#define MAME_VIDEO_HUC6270_H

#pragma once

>>>>>>> upstream/master

#define MCFG_HUC6270_VRAM_SIZE(_size) \
	huc6270_device::set_vram_size(*device, _size);

#define MCFG_HUC6270_IRQ_CHANGED_CB(_devcb) \
	devcb = &huc6270_device::set_irq_changed_callback(*device, DEVCB_##_devcb);

<<<<<<< HEAD
class huc6270_device :  public device_t
{
public:
	// construction/destruction
	huc6270_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	static void set_vram_size(device_t &device, UINT32 vram_size) { downcast<huc6270_device &>(device).m_vram_size = vram_size; }
	template<class _Object> static devcb_base &set_irq_changed_callback(device_t &device, _Object object) { return downcast<huc6270_device &>(device).m_irq_changed_cb.set_callback(object); }
=======
class huc6270_device : public device_t
{
public:
	// construction/destruction
	huc6270_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	static void set_vram_size(device_t &device, uint32_t vram_size) { downcast<huc6270_device &>(device).m_vram_size = vram_size; }
	template <class Object> static devcb_base &set_irq_changed_callback(device_t &device, Object &&cb) { return downcast<huc6270_device &>(device).m_irq_changed_cb.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE8_MEMBER( write );
	DECLARE_READ16_MEMBER( next_pixel );
	inline DECLARE_READ16_MEMBER( time_until_next_event )
	{
		return m_horz_to_go * 8 + m_horz_steps;
	}

	DECLARE_WRITE_LINE_MEMBER( vsync_changed );
	DECLARE_WRITE_LINE_MEMBER( hsync_changed );

<<<<<<< HEAD
	static const UINT16 HUC6270_SPRITE     = 0x0100;    // sprite colour information
	static const UINT16 HUC6270_BACKGROUND = 0x0000;    // background colour information

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
=======
	static const uint16_t HUC6270_SPRITE     = 0x0100;    // sprite colour information
	static const uint16_t HUC6270_BACKGROUND = 0x0000;    // background colour information

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

	inline void fetch_bat_tile_row();
	void add_sprite( int index, int x, int pattern, int line, int flip_x, int palette, int priority, int sat_lsb );
	void select_sprites();
	inline void handle_vblank();
	inline void next_vert_state();
	inline void next_horz_state();

private:
<<<<<<< HEAD

	enum huc6270_v_state {
		HUC6270_VSW,
		HUC6270_VDS,
		HUC6270_VDW,
		HUC6270_VCR
	};

	enum huc6270_h_state {
		HUC6270_HDS,
		HUC6270_HDW,
		HUC6270_HDE,
		HUC6270_HSW
=======
	enum class v_state : u8 {
		VSW,
		VDS,
		VDW,
		VCR
	};

	enum class h_state : u8 {
		HDS,
		HDW,
		HDE,
		HSW
>>>>>>> upstream/master
	};


	/* Size of Video ram (mandatory) */
<<<<<<< HEAD
	UINT32 m_vram_size;
=======
	uint32_t m_vram_size;
>>>>>>> upstream/master

	/* Callback for when the irq line may have changed (mandatory) */
	devcb_write_line    m_irq_changed_cb;

<<<<<<< HEAD
	UINT8   m_register_index;

	/* HuC6270 registers */
	UINT16  m_mawr;
	UINT16  m_marr;
	UINT16  m_vrr;
	UINT16  m_vwr;
	UINT16  m_cr;
	UINT16  m_rcr;
	UINT16  m_bxr;
	UINT16  m_byr;
	UINT16  m_mwr;
	UINT16  m_hsr;
	UINT16  m_hdr;
	UINT16  m_vpr;
	UINT16  m_vdw;
	UINT16  m_vcr;
	UINT16  m_dcr;
	UINT16  m_sour;
	UINT16  m_desr;
	UINT16  m_lenr;
	UINT16  m_dvssr;
	UINT8   m_status;
=======
	uint8_t   m_register_index;

	/* HuC6270 registers */
	uint16_t  m_mawr;
	uint16_t  m_marr;
	uint16_t  m_vrr;
	uint16_t  m_vwr;
	uint16_t  m_cr;
	uint16_t  m_rcr;
	uint16_t  m_bxr;
	uint16_t  m_byr;
	uint16_t  m_mwr;
	uint16_t  m_hsr;
	uint16_t  m_hdr;
	uint16_t  m_vpr;
	uint16_t  m_vdw;
	uint16_t  m_vcr;
	uint16_t  m_dcr;
	uint16_t  m_sour;
	uint16_t  m_desr;
	uint16_t  m_lenr;
	uint16_t  m_dvssr;
	uint8_t   m_status;
>>>>>>> upstream/master

	/* To keep track of external hsync and vsync signals */
	int m_hsync;
	int m_vsync;

	/* internal variables */
<<<<<<< HEAD
	huc6270_v_state m_vert_state;
	huc6270_h_state m_horz_state;
=======
	v_state m_vert_state;
	h_state m_horz_state;
>>>>>>> upstream/master
	int m_vd_triggered;
	int m_vert_to_go;
	int m_horz_to_go;
	int m_horz_steps;
	int m_raster_count;
	int m_dvssr_written;
	int m_satb_countdown;
	int m_dma_enabled;
<<<<<<< HEAD
	UINT16 m_byr_latched;
	UINT16 m_bxr_latched;
	UINT16 m_bat_address;
	UINT16 m_bat_address_mask;
	UINT16 m_bat_row;
	UINT16 m_bat_column;
	UINT8 m_bat_tile_row[8];
	/* Internal sprite attribute table. SATB DMA is used to transfer data
	   from VRAM to this internal table.
	*/
	UINT16 m_sat[4*64];
	int m_sprites_this_line;
	int m_sprite_row_index;
	UINT16  m_sprite_row[1024];
	UINT16  *m_vram;
	UINT16  m_vram_mask;

	const static UINT8 vram_increments[4];
};


extern const device_type HUC6270;


#endif
=======
	uint16_t m_byr_latched;
	uint16_t m_bxr_latched;
	uint16_t m_bat_address;
	uint16_t m_bat_address_mask;
	uint16_t m_bat_row;
	uint16_t m_bat_column;
	uint8_t m_bat_tile_row[8];
	/* Internal sprite attribute table. SATB DMA is used to transfer data
	   from VRAM to this internal table.
	*/
	uint16_t m_sat[4*64];
	int m_sprites_this_line;
	int m_sprite_row_index;
	uint16_t  m_sprite_row[1024];
	std::unique_ptr<uint16_t[]>  m_vram;
	uint16_t  m_vram_mask;

	static constexpr uint8_t vram_increments[4] = { 1, 32, 64, 128 };
};


DECLARE_DEVICE_TYPE(HUC6270, huc6270_device)

#endif // MAME_VIDEO_HUC6270_H
>>>>>>> upstream/master
