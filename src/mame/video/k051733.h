// license:BSD-3-Clause
// copyright-holders:Fabio Priuli,Acho A. Tang, R. Belmont
<<<<<<< HEAD
#pragma once
#ifndef __K051733_H__
#define __K051733_H__
=======
#ifndef MAME_VIDEO_K051733_H
#define MAME_VIDEO_K051733_H

#pragma once

>>>>>>> upstream/master

class k051733_device : public device_t
{
public:
<<<<<<< HEAD
	k051733_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~k051733_device() {}
=======
	k051733_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER( write );
	DECLARE_READ8_MEMBER( read );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();
private:
	// internal state
	UINT8    m_ram[0x20];
	UINT8    m_rng;
};

extern const device_type K051733;
=======
	virtual void device_start() override;
	virtual void device_reset() override;
private:
	// internal state
	uint8_t    m_ram[0x20];
	uint8_t    m_rng;
};

DECLARE_DEVICE_TYPE(K051733, k051733_device)
>>>>>>> upstream/master

#define MCFG_K051733_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, K051733, 0)

<<<<<<< HEAD
#endif
=======
#endif // MAME_VIDEO_K051733_H
>>>>>>> upstream/master
