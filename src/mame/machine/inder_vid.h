// license:BSD-3-Clause
// copyright-holders:David Haywood
/* Inder / Dinamic Video */


/* */


<<<<<<< HEAD
#pragma once

#ifndef __INDER_VIDEO__
#define __INDER_VIDEO__
=======
#ifndef MAME_MACHINE_INDER_VID_H
#define MAME_MACHINE_INDER_VID_H

#pragma once
>>>>>>> upstream/master


#include "video/ramdac.h"
#include "cpu/tms34010/tms34010.h"

<<<<<<< HEAD
extern const device_type INDER_VIDEO;
=======
DECLARE_DEVICE_TYPE(INDER_VIDEO, inder_vid_device)
>>>>>>> upstream/master

#define MCFG_INDER_VIDEO_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, INDER_VIDEO, 0)


<<<<<<< HEAD
class inder_vid_device :  public device_t
=======
class inder_vid_device : public device_t
>>>>>>> upstream/master
/*  public device_video_interface */
{
public:
	// construction/destruction
<<<<<<< HEAD
	inder_vid_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	required_shared_ptr<UINT16> m_vram;
	required_device<palette_device> m_palette;
	required_device<tms34010_device> m_tms;

	DECLARE_WRITE_LINE_MEMBER(m68k_gen_int);

	int m_shiftfull; // this might be a driver specific hack for a TMS bug.
	TMS340X0_TO_SHIFTREG_CB_MEMBER(to_shiftreg);
	TMS340X0_FROM_SHIFTREG_CB_MEMBER(from_shiftreg);
	TMS340X0_SCANLINE_RGB32_CB_MEMBER(scanline);

protected:
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_start();
	virtual void device_reset();

private:
};

#endif
=======
	inder_vid_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	required_shared_ptr<uint16_t> m_vram;
	required_device<palette_device> m_palette;
	required_device<tms34010_device> m_tms;

	int m_shiftfull; // this might be a driver specific hack for a TMS bug.

	DECLARE_WRITE_LINE_MEMBER(m68k_gen_int);

	TMS340X0_TO_SHIFTREG_CB_MEMBER(to_shiftreg);
	TMS340X0_FROM_SHIFTREG_CB_MEMBER(from_shiftreg);
	TMS340X0_SCANLINE_RGB32_CB_MEMBER(scanline);
};

#endif // MAME_MACHINE_INDER_VID_H
>>>>>>> upstream/master
