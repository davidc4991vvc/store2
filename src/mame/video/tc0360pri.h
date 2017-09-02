// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
<<<<<<< HEAD
#ifndef _TC0360PRI_H_
#define _TC0360PRI_H_
=======
#ifndef MAME_VIDEO_TC0360PRI_H
#define MAME_VIDEO_TC0360PRI_H

#pragma once
>>>>>>> upstream/master

class tc0360pri_device : public device_t
{
public:
<<<<<<< HEAD
	tc0360pri_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~tc0360pri_device() {}
=======
	tc0360pri_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER( write );
	DECLARE_READ8_MEMBER( read );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

private:
	// internal state
	UINT8   m_regs[16];
};

extern const device_type TC0360PRI;
=======
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	// internal state
	uint8_t   m_regs[16];
};

DECLARE_DEVICE_TYPE(TC0360PRI, tc0360pri_device)
>>>>>>> upstream/master

#define MCFG_TC0360PRI_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, TC0360PRI, 0)

<<<<<<< HEAD
#endif
=======
#endif // MAME_VIDEO_TC0360PRI_H
>>>>>>> upstream/master
