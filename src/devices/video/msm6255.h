// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    OKI MSM6255 Dot Matrix LCD Controller implementation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __MSM6255__
#define __MSM6255__

#include "emu.h"
=======
#ifndef MAME_VIDEO_MSM6255_H
#define MAME_VIDEO_MSM6255_H

#pragma once
>>>>>>> upstream/master



///*************************************************************************
//  TYPE DEFINITIONS
///*************************************************************************

// ======================> msm6255_device

class msm6255_device :  public device_t,
						public device_memory_interface,
						public device_video_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	msm6255_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	msm6255_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	virtual DECLARE_ADDRESS_MAP(map, 8);

	DECLARE_READ8_MEMBER( ir_r );
	DECLARE_WRITE8_MEMBER( ir_w );

	DECLARE_READ8_MEMBER( dr_r );
	DECLARE_WRITE8_MEMBER( dr_w );

<<<<<<< HEAD
	UINT32 screen_update(screen_device &device, bitmap_ind16 &bitmap, const rectangle &cliprect);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;
=======
	uint32_t screen_update(screen_device &device, bitmap_ind16 &bitmap, const rectangle &cliprect);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;
>>>>>>> upstream/master

private:
	// registers
	enum
	{
		REGISTER_MOR = 0,
		REGISTER_PR,
		REGISTER_HNR,
		REGISTER_DVR,
		REGISTER_CPR,
		REGISTER_SLR,
		REGISTER_SUR,
		REGISTER_CLR,
		REGISTER_CUR
	};

<<<<<<< HEAD
	UINT8 read_byte(UINT16 ma, UINT8 ra);

	void update_cursor();
	void draw_scanline(bitmap_ind16 &bitmap, const rectangle &cliprect, int y, UINT16 ma, UINT8 ra = 0);
=======
	uint8_t read_byte(uint16_t ma, uint8_t ra);

	void update_cursor();
	void draw_scanline(bitmap_ind16 &bitmap, const rectangle &cliprect, int y, uint16_t ma, uint8_t ra = 0);
>>>>>>> upstream/master
	void update_graphics(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void update_text(bitmap_ind16 &bitmap, const rectangle &cliprect);

	const address_space_config m_space_config;

<<<<<<< HEAD
	UINT8 m_ir;                     // instruction register
	UINT8 m_mor;                    // mode control register
	UINT8 m_pr;                     // character pitch register
	UINT8 m_hnr;                    // horizontal character number register
	UINT8 m_dvr;                    // duty number register
	UINT8 m_cpr;                    // cursor form register
	UINT8 m_slr;                    // start address (lower) register
	UINT8 m_sur;                    // start address (upper) register
	UINT8 m_clr;                    // cursor address (lower) register
	UINT8 m_cur;                    // cursor address (upper) register
=======
	uint8_t m_ir;                     // instruction register
	uint8_t m_mor;                    // mode control register
	uint8_t m_pr;                     // character pitch register
	uint8_t m_hnr;                    // horizontal character number register
	uint8_t m_dvr;                    // duty number register
	uint8_t m_cpr;                    // cursor form register
	uint8_t m_slr;                    // start address (lower) register
	uint8_t m_sur;                    // start address (upper) register
	uint8_t m_clr;                    // cursor address (lower) register
	uint8_t m_cur;                    // cursor address (upper) register
>>>>>>> upstream/master

	int m_cursor;                   // is cursor displayed
	int m_frame;                    // frame counter
};


// device type definition
<<<<<<< HEAD
extern const device_type MSM6255;



#endif
=======
DECLARE_DEVICE_TYPE(MSM6255, msm6255_device)

#endif // MAME_VIDEO_MSM6255_H
>>>>>>> upstream/master
