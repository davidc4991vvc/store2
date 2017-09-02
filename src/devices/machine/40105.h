// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

<<<<<<< HEAD
    CMOS 40105 FIFO Register emulation

**********************************************************************/

#pragma once

#ifndef __CMOS_40105__
#define __CMOS_40105__

#include "emu.h"
=======
    CD40105/HC40105 4-bit x 16-word FIFO Register

***********************************************************************
                                ____   ____
                       /OE   1 |*   \_/    | 16  Vcc
                       DIR   2 |           | 15  /SO
                        SI   3 |           | 14  DOR
                        D0   4 |           | 13  Q0
                        D1   5 |   40105   | 12  Q1
                        D2   6 |           | 11  Q2
                        D3   7 |           | 10  Q3
                       GND   8 |___________|  9  MR

**********************************************************************/

#ifndef MAME_MACHINE_40105_H
#define MAME_MACHINE_40105_H

#pragma once

>>>>>>> upstream/master
#include <queue>



///*************************************************************************
//  INTERFACE CONFIGURATION MACROS
///*************************************************************************

<<<<<<< HEAD
#define MCFG_40105_ADD(_tag, _dir, _dor) \
	MCFG_DEVICE_ADD(_tag, CMOS_40105, 0) \
	downcast<cmos_40105_device *>(device)->set_dir_callback(DEVCB_##_dir); \
	downcast<cmos_40105_device *>(device)->set_dor_callback(DEVCB_##_dor);
=======
#define MCFG_40105_DATA_IN_READY_CB(_dir) \
	devcb = &downcast<cmos_40105_device *>(device)->set_dir_callback(DEVCB_##_dir);

#define MCFG_40105_DATA_OUT_READY_CB(_dor) \
	devcb = &downcast<cmos_40105_device *>(device)->set_dor_callback(DEVCB_##_dor);

#define MCFG_40105_DATA_OUT_CB(_out) \
	devcb = &downcast<cmos_40105_device *>(device)->set_data_out_callback(DEVCB_##_out);
>>>>>>> upstream/master



///*************************************************************************
//  TYPE DEFINITIONS
///*************************************************************************

// ======================> cmos_40105_device

class cmos_40105_device :  public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	cmos_40105_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	template<class _dir> void set_dir_callback(_dir dir) { m_write_dir.set_callback(dir); }
	template<class _dor> void set_dor_callback(_dor dor) { m_write_dor.set_callback(dor); }

	UINT8 read();
	void write(UINT8 data);
=======
	cmos_40105_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock);

	template <class Object> devcb_base &set_dir_callback(Object &&dir) { return m_write_dir.set_callback(std::forward<Object>(dir)); }
	template <class Object> devcb_base &set_dor_callback(Object &&dor) { return m_write_dor.set_callback(std::forward<Object>(dor)); }
	template <class Object> devcb_base &set_data_out_callback(Object &&out) { return m_write_q.set_callback(std::forward<Object>(out)); }

	u8 read();
	void write(u8 data);
	DECLARE_WRITE8_MEMBER(write);
>>>>>>> upstream/master

	DECLARE_WRITE_LINE_MEMBER( si_w );
	DECLARE_WRITE_LINE_MEMBER( so_w );

	DECLARE_READ_LINE_MEMBER( dir_r );
	DECLARE_READ_LINE_MEMBER( dor_r );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

private:
	devcb_write_line m_write_dir;
	devcb_write_line m_write_dor;

	std::queue<UINT8> m_fifo;

	UINT8 m_d;
	UINT8 m_q;

	int m_dir;
	int m_dor;
	int m_si;
	int m_so;
=======
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	// private helpers
	void load_input();
	void output_ready();

	// callbacks
	devcb_write_line m_write_dir;
	devcb_write_line m_write_dor;
	devcb_write8 m_write_q;

	std::queue<u8> m_fifo;

	u8 m_d;
	u8 m_q;

	bool m_dir;
	bool m_dor;
	bool m_si;
	bool m_so;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type CMOS_40105;



#endif
=======
DECLARE_DEVICE_TYPE(CD40105, cmos_40105_device)
extern const device_type HC40105;

#endif // MAME_MACHINE_40105_H
>>>>>>> upstream/master
