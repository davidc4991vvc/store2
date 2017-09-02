// license:BSD-3-Clause
// copyright-holders:David Haywood
<<<<<<< HEAD


=======
#ifndef MAME_MACHINE_LC89510_H
#define MAME_MACHINE_LC89510_H

#pragma once
>>>>>>> upstream/master

class lc89510_device : public device_t
{
public:
<<<<<<< HEAD
	lc89510_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);



protected:
	virtual void device_start();
	virtual void device_reset();

private:


};


extern const device_type LC89510;
=======
	lc89510_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
};


DECLARE_DEVICE_TYPE(LC89510, lc89510_device)

#endif // MAME_MACHINE_LC89510_H
>>>>>>> upstream/master
