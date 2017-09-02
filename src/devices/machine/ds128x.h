// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#ifndef __DS128X_H__
#define __DS128X_H__
=======
#ifndef MAME_MACHINE_DS128X_H
#define MAME_MACHINE_DS128X_H
>>>>>>> upstream/master

#include "mc146818.h"

#define MCFG_DS12885_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, DS12885, XTAL_32_768kHz)

// ======================> mc146818_device

class ds12885_device : public mc146818_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	ds12885_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual int data_size() { return 128; }
};

// device type definition
extern const device_type DS12885;

#endif
=======
	ds12885_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual int data_size() override { return 128; }
};

// device type definition
DECLARE_DEVICE_TYPE(DS12885, ds12885_device)

#endif // MAME_MACHINE_DS128X_H
>>>>>>> upstream/master
