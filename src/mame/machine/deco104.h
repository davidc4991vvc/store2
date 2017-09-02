// license:BSD-3-Clause
// copyright-holders:David Haywood
<<<<<<< HEAD
#pragma once
#ifndef __DECO104_H__
#define __DECO104_H__
=======
#ifndef MAME_MACHINE_DECO104_H
#define MAME_MACHINE_DECO104_H

#pragma once
>>>>>>> upstream/master

#include "deco146.h"


<<<<<<< HEAD

=======
>>>>>>> upstream/master
/* Data East 104 protection chip */

class deco104_device : public deco_146_base_device
{
public:
<<<<<<< HEAD
	deco104_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);




protected:
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();





private:


};

extern const device_type DECO104PROT;
=======
	deco104_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
};

DECLARE_DEVICE_TYPE(DECO104PROT, deco104_device)
>>>>>>> upstream/master


#define MCFG_DECO104_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, DECO104PROT, 0)

<<<<<<< HEAD



#endif
=======
#endif // MAME_MACHINE_DECO104_H
>>>>>>> upstream/master
