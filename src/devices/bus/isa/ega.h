// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#pragma once

#ifndef __ISA_EGA_H__
#define __ISA_EGA_H__

#include "emu.h"
=======
#ifndef MAME_BUS_ISA_EGA_H
#define MAME_BUS_ISA_EGA_H

#pragma once

>>>>>>> upstream/master
#include "isa.h"
#include "video/crtc_ega.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> isa8_ega_device

class isa8_ega_device :
		public device_t,
		public device_isa8_card_interface
{
public:
<<<<<<< HEAD
		// construction/destruction
		isa8_ega_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
		isa8_ega_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

		// optional information overrides
		virtual machine_config_constructor device_mconfig_additions() const;
		virtual const rom_entry *device_rom_region() const;
		virtual ioport_constructor device_input_ports() const;

		DECLARE_READ8_MEMBER(read);
		DECLARE_WRITE8_MEMBER(write);
		DECLARE_READ8_MEMBER(pc_ega8_3b0_r);
		DECLARE_WRITE8_MEMBER(pc_ega8_3b0_w);
		DECLARE_READ8_MEMBER(pc_ega8_3c0_r);
		DECLARE_WRITE8_MEMBER(pc_ega8_3c0_w);
		DECLARE_READ8_MEMBER(pc_ega8_3d0_r);
		DECLARE_WRITE8_MEMBER(pc_ega8_3d0_w);
		DECLARE_WRITE_LINE_MEMBER(de_changed);
		DECLARE_WRITE_LINE_MEMBER(hsync_changed);
		DECLARE_WRITE_LINE_MEMBER(vsync_changed);
		DECLARE_WRITE_LINE_MEMBER(vblank_changed);

		CRTC_EGA_ROW_UPDATE(ega_update_row);
		CRTC_EGA_ROW_UPDATE(pc_ega_graphics);
		CRTC_EGA_ROW_UPDATE(pc_ega_text);

protected:
		// device-level overrides
		virtual void device_start();
		virtual void device_reset();

		UINT8 alu_op( UINT8 data, UINT8 latch_data );

public:
		crtc_ega_device *m_crtc_ega;

		void install_banks();
		void change_mode();
		DECLARE_WRITE8_MEMBER(pc_ega8_3X0_w);
		DECLARE_READ8_MEMBER(pc_ega8_3X0_r);

		/* Video memory and related variables */
		memory_region   *m_vram;
		UINT8   *m_plane[4];
		UINT8   m_read_latch[4];
		UINT8   *m_videoram;
		UINT8   *m_charA;
		UINT8   *m_charB;

		/* Registers */
		UINT8   m_misc_output;
		UINT8   m_feature_control;

		/* Attribute registers AR00 - AR14
		*/
		struct {
			UINT8   index;
			UINT8   data[32];
			UINT8   index_write;
		} m_attribute;

		/* Sequencer registers SR00 - SR04
		*/
		struct {
			UINT8   index;
			UINT8   data[8];
		} m_sequencer;

		/* Graphics controller registers GR00 - GR08
		*/
		struct {
			UINT8   index;
			UINT8   data[16];
		} m_graphics_controller;

		UINT8   m_frame_cnt;
		UINT8   m_hsync;
		UINT8   m_vsync;
		UINT8   m_vblank;
		UINT8   m_display_enable;
		int     m_video_mode;
		required_device<palette_device> m_palette;
=======
	// construction/destruction
	isa8_ega_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ8_MEMBER(read);
	DECLARE_WRITE8_MEMBER(write);
	DECLARE_READ8_MEMBER(pc_ega8_3b0_r);
	DECLARE_WRITE8_MEMBER(pc_ega8_3b0_w);
	DECLARE_READ8_MEMBER(pc_ega8_3c0_r);
	DECLARE_WRITE8_MEMBER(pc_ega8_3c0_w);
	DECLARE_READ8_MEMBER(pc_ega8_3d0_r);
	DECLARE_WRITE8_MEMBER(pc_ega8_3d0_w);

	CRTC_EGA_ROW_UPDATE(pc_ega_graphics);
	CRTC_EGA_ROW_UPDATE(pc_ega_text);

protected:
	isa8_ega_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual ioport_constructor device_input_ports() const override;

	uint8_t alu_op( uint8_t data, uint8_t latch_data );

private:
	DECLARE_WRITE_LINE_MEMBER(de_changed);
	DECLARE_WRITE_LINE_MEMBER(hsync_changed);
	DECLARE_WRITE_LINE_MEMBER(vsync_changed);
	DECLARE_WRITE_LINE_MEMBER(vblank_changed);

	CRTC_EGA_ROW_UPDATE(ega_update_row);

public:
	crtc_ega_device *m_crtc_ega;

	void install_banks();
	void change_mode();
	DECLARE_WRITE8_MEMBER(pc_ega8_3X0_w);
	DECLARE_READ8_MEMBER(pc_ega8_3X0_r);

	/* Video memory and related variables */
	memory_region   *m_vram;
	uint8_t   *m_plane[4];
	uint8_t   m_read_latch[4];
	uint8_t   *m_videoram;
	uint8_t   *m_charA;
	uint8_t   *m_charB;

	/* Registers */
	uint8_t   m_misc_output;
	uint8_t   m_feature_control;

	/* Attribute registers AR00 - AR14
	*/
	struct {
		uint8_t   index;
		uint8_t   data[32];
		uint8_t   index_write;
	} m_attribute;

	/* Sequencer registers SR00 - SR04
	*/
	struct {
		uint8_t   index;
		uint8_t   data[8];
	} m_sequencer;

	/* Graphics controller registers GR00 - GR08
	*/
	struct {
		uint8_t   index;
		uint8_t   data[16];
	} m_graphics_controller;

	uint8_t   m_frame_cnt;
	uint8_t   m_hsync;
	uint8_t   m_vsync;
	uint8_t   m_vblank;
	uint8_t   m_display_enable;
	int     m_video_mode;
	required_device<palette_device> m_palette;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type ISA8_EGA;

#endif  /* __ISA_EGA_H__ */
=======
DECLARE_DEVICE_TYPE(ISA8_EGA, isa8_ega_device)

#endif // MAME_BUS_ISA_EGA_H
>>>>>>> upstream/master
