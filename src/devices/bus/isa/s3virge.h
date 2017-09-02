// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
/*
 * s3virge.h
 *
 * S3 ViRGE 2D/3D video card
 *
 */

<<<<<<< HEAD
#ifndef S3VIRGE_H_
#define S3VIRGE_H_

#include "emu.h"
=======
#ifndef MAME_BUS_ISA_S3VIRGE_H
#define MAME_BUS_ISA_S3VIRGE_H

#pragma once

>>>>>>> upstream/master
#include "video/pc_vga.h"

// ======================> s3virge_vga_device

class s3virge_vga_device :  public s3_vga_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	s3virge_vga_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	s3virge_vga_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	virtual READ8_MEMBER(port_03b0_r);
	virtual WRITE8_MEMBER(port_03b0_w);
	virtual READ8_MEMBER(port_03c0_r);
	virtual WRITE8_MEMBER(port_03c0_w);
	virtual READ8_MEMBER(port_03d0_r);
	virtual WRITE8_MEMBER(port_03d0_w);
	virtual READ8_MEMBER(mem_r);
	virtual WRITE8_MEMBER(mem_w);

	ibm8514a_device* get_8514() { fatalerror("s3virge requested non-existant 8514/A device\n"); return NULL; }
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

private:
	virtual UINT8 s3_crtc_reg_read(UINT8 index);
	virtual void s3_define_video_mode(void);
	virtual void s3_crtc_reg_write(UINT8 index, UINT8 data);
=======
	s3virge_vga_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual READ8_MEMBER(port_03b0_r) override;
	virtual WRITE8_MEMBER(port_03b0_w) override;
	virtual READ8_MEMBER(port_03c0_r) override;
	virtual WRITE8_MEMBER(port_03c0_w) override;
	virtual READ8_MEMBER(port_03d0_r) override;
	virtual WRITE8_MEMBER(port_03d0_w) override;
	virtual READ8_MEMBER(mem_r) override;
	virtual WRITE8_MEMBER(mem_w) override;

	ibm8514a_device* get_8514() { fatalerror("s3virge requested non-existant 8514/A device\n"); return nullptr; }

protected:
	s3virge_vga_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	virtual uint8_t s3_crtc_reg_read(uint8_t index);
	virtual void s3_define_video_mode(void);
	virtual void s3_crtc_reg_write(uint8_t index, uint8_t data);
>>>>>>> upstream/master
	// has no 8514/A device
};


// ======================> s3virgedx_vga_device

class s3virgedx_vga_device :  public s3virge_vga_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	s3virgedx_vga_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	s3virgedx_vga_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
=======
	s3virgedx_vga_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	s3virgedx_vga_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master
};

// ======================> s3virgedx_vga_device

class s3virgedx_rev1_vga_device :  public s3virgedx_vga_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	s3virgedx_rev1_vga_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
};

// device type definition
extern const device_type S3VIRGE;
extern const device_type S3VIRGEDX;
extern const device_type S3VIRGEDX1;

#endif /* S3VIRGE_H_ */
=======
	s3virgedx_rev1_vga_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
};

// device type definition
DECLARE_DEVICE_TYPE(S3VIRGE,    s3virge_vga_device)
DECLARE_DEVICE_TYPE(S3VIRGEDX,  s3virgedx_vga_device)
DECLARE_DEVICE_TYPE(S3VIRGEDX1, s3virgedx_rev1_vga_device)

#endif // MAME_BUS_ISA_S3VIRGE_H
>>>>>>> upstream/master
