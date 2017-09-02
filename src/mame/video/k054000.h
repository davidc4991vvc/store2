// license:BSD-3-Clause
// copyright-holders:David Haywood
<<<<<<< HEAD

#pragma once
#ifndef __K054000_H__
#define __K054000_H__
=======
#ifndef MAME_VIDEO_K054000_H
#define MAME_VIDEO_K054000_H

#pragma once

>>>>>>> upstream/master

#define MCFG_K054000_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, K054000, 0)

class k054000_device : public device_t
{
public:
<<<<<<< HEAD
	k054000_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	k054000_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
	~k054000_device() {}

	DECLARE_WRITE8_MEMBER( write );
	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE16_MEMBER( lsb_w );
	DECLARE_READ16_MEMBER( lsb_r );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();

private:
	// internal state
	UINT8    m_regs[0x20];
};

extern const device_type K054000;




#endif
=======
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	// internal state
	uint8_t    m_regs[0x20];
};

DECLARE_DEVICE_TYPE(K054000, k054000_device)

#endif // MAME_VIDEO_K054000_H
>>>>>>> upstream/master
