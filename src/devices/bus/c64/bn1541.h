// license:BSD-3-Clause
// copyright-holders:Curt Coder, smf
/**********************************************************************

    SpeedDOS / Burst Nibbler 1541/1571 Parallel Cable emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __C64_BN1541__
#define __C64_BN1541__


#include "emu.h"
=======
#ifndef MAME_BUS_C64_BN1541_H
#define MAME_BUS_C64_BN1541_H

#pragma once


>>>>>>> upstream/master
#include "user.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> device_c64_floppy_parallel_interface

class device_c64_floppy_parallel_interface
{
public:
	// construction/destruction
	device_c64_floppy_parallel_interface(const machine_config &mconfig, device_t &device);
	virtual ~device_c64_floppy_parallel_interface();

<<<<<<< HEAD
	virtual void parallel_data_w(UINT8 data) = 0;
=======
	virtual void parallel_data_w(uint8_t data) = 0;
>>>>>>> upstream/master
	virtual void parallel_strobe_w(int state) = 0;

	device_c64_floppy_parallel_interface *m_other;

protected:
<<<<<<< HEAD
	UINT8 m_parallel_data;
=======
	uint8_t m_parallel_data;
>>>>>>> upstream/master
};


// ======================> c64_bn1541_device

class c64_bn1541_device : public device_t,
	public device_pet_user_port_interface,
	public device_c64_floppy_parallel_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_bn1541_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();

	// device_c64_floppy_parallel_interface overrides
	virtual void parallel_data_w(UINT8 data);
	virtual void parallel_strobe_w(int state);

	// device_pet_user_port_interface overrides
	virtual DECLARE_WRITE_LINE_MEMBER(input_8);
	virtual WRITE_LINE_MEMBER(input_c) { if (state) m_parallel_output |= 1; else m_parallel_output &= ~1; update_output(); }
	virtual WRITE_LINE_MEMBER(input_d) { if (state) m_parallel_output |= 2; else m_parallel_output &= ~2; update_output(); }
	virtual WRITE_LINE_MEMBER(input_e) { if (state) m_parallel_output |= 4; else m_parallel_output &= ~4; update_output(); }
	virtual WRITE_LINE_MEMBER(input_f) { if (state) m_parallel_output |= 8; else m_parallel_output &= ~8; update_output(); }
	virtual WRITE_LINE_MEMBER(input_h) { if (state) m_parallel_output |= 16; else m_parallel_output &= ~16; update_output(); }
	virtual WRITE_LINE_MEMBER(input_j) { if (state) m_parallel_output |= 32; else m_parallel_output &= ~32; update_output(); }
	virtual WRITE_LINE_MEMBER(input_k) { if (state) m_parallel_output |= 64; else m_parallel_output &= ~64; update_output(); }
	virtual WRITE_LINE_MEMBER(input_l) { if (state) m_parallel_output |= 128; else m_parallel_output &= ~128; update_output(); }

private:
	void update_output();
	UINT8 m_parallel_output;
=======
	c64_bn1541_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_c64_floppy_parallel_interface overrides
	virtual void parallel_data_w(uint8_t data) override;
	virtual void parallel_strobe_w(int state) override;

	// device_pet_user_port_interface overrides
	virtual DECLARE_WRITE_LINE_MEMBER(input_8) override;
	virtual WRITE_LINE_MEMBER(input_c) override { if (state) m_parallel_output |= 1; else m_parallel_output &= ~1; update_output(); }
	virtual WRITE_LINE_MEMBER(input_d) override { if (state) m_parallel_output |= 2; else m_parallel_output &= ~2; update_output(); }
	virtual WRITE_LINE_MEMBER(input_e) override { if (state) m_parallel_output |= 4; else m_parallel_output &= ~4; update_output(); }
	virtual WRITE_LINE_MEMBER(input_f) override { if (state) m_parallel_output |= 8; else m_parallel_output &= ~8; update_output(); }
	virtual WRITE_LINE_MEMBER(input_h) override { if (state) m_parallel_output |= 16; else m_parallel_output &= ~16; update_output(); }
	virtual WRITE_LINE_MEMBER(input_j) override { if (state) m_parallel_output |= 32; else m_parallel_output &= ~32; update_output(); }
	virtual WRITE_LINE_MEMBER(input_k) override { if (state) m_parallel_output |= 64; else m_parallel_output &= ~64; update_output(); }
	virtual WRITE_LINE_MEMBER(input_l) override { if (state) m_parallel_output |= 128; else m_parallel_output &= ~128; update_output(); }

private:
	void update_output();
	uint8_t m_parallel_output;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_BN1541;


#endif
=======
DECLARE_DEVICE_TYPE(C64_BN1541, c64_bn1541_device)


#endif // MAME_BUS_C64_BN1541_H
>>>>>>> upstream/master
