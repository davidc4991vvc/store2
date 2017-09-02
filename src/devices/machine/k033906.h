// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/***************************************************************************

    Konami 033906

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __K033906_H__
#define __K033906_H__

#include "emu.h"

=======
#ifndef MAME_MACHINE_K033906_H
#define MAME_MACHINE_K033906_H

#pragma once

#include "video/voodoo.h"
>>>>>>> upstream/master


/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

#define MCFG_K033906_VOODOO(_tag) \
<<<<<<< HEAD
	k033906_device::set_voodoo_tag(*device, _tag);
=======
	k033906_device::set_voodoo_tag(*device, "^" _tag);
>>>>>>> upstream/master

/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/


// ======================> k033906_device

class k033906_device :  public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	k033906_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	static void set_voodoo_tag(device_t &device, const char *tag) { downcast<k033906_device &>(device).m_voodoo_tag = tag; }
=======
	k033906_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	static void set_voodoo_tag(device_t &device, const char *tag) { downcast<k033906_device &>(device).m_voodoo.set_tag(tag); }
>>>>>>> upstream/master

	DECLARE_READ32_MEMBER( read );
	DECLARE_WRITE32_MEMBER( write );
	DECLARE_WRITE_LINE_MEMBER( set_reg );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset() { }
	virtual void device_post_load() { }
	virtual void device_clock_changed() { }

private:

	UINT32 reg_r(int reg);
	void reg_w(int reg, UINT32 data);
=======
	virtual void device_start() override;
	virtual void device_reset() override { }
	virtual void device_post_load() override { }
	virtual void device_clock_changed() override { }

private:
	uint32_t reg_r(int reg);
	void reg_w(int reg, uint32_t data);
>>>>>>> upstream/master

	/* i/o lines */

	int          m_reg_set; // 1 = access reg / 0 = access ram

<<<<<<< HEAD
	const char   *m_voodoo_tag;
	device_t     *m_voodoo;

	UINT32       m_reg[256];
	UINT32       m_ram[32768];
=======
	required_device<voodoo_device> m_voodoo;

	uint32_t       m_reg[256];
	uint32_t       m_ram[32768];
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type K033906;

#endif  /* __K033906_H__ */
=======
DECLARE_DEVICE_TYPE(K033906, k033906_device)

#endif // MAME_MACHINE_K033906_H
>>>>>>> upstream/master
