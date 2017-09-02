// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    EACA Colour Genie Printer Interface EG2012

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __CGENIE_PARALLEL_PRINTER_H__
#define __CGENIE_PARALLEL_PRINTER_H__

#include "emu.h"
=======
#ifndef MAME_BUS_CGENIE_PARALLEL_PRINTER_H
#define MAME_BUS_CGENIE_PARALLEL_PRINTER_H

#pragma once

>>>>>>> upstream/master
#include "parallel.h"
#include "bus/centronics/ctronics.h"


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> cgenie_printer_device

<<<<<<< HEAD
class cgenie_printer_device : public device_t, public device_parallel_interface
{
public:
	// construction/destruction
	cgenie_printer_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

=======
class cgenie_printer_device : public device_t, public device_cg_parallel_interface
{
public:
	// construction/destruction
	cgenie_printer_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual void pa_w(uint8_t data) override;
	virtual uint8_t pb_r() override;
	virtual void pb_w(uint8_t data) override;

private:
>>>>>>> upstream/master
	DECLARE_WRITE_LINE_MEMBER(busy_w);
	DECLARE_WRITE_LINE_MEMBER(perror_w);
	DECLARE_WRITE_LINE_MEMBER(select_w);
	DECLARE_WRITE_LINE_MEMBER(fault_w);

<<<<<<< HEAD
protected:
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_start();
	virtual void device_reset();

	virtual void pa_w(UINT8 data);
	virtual UINT8 pb_r();
	virtual void pb_w(UINT8 data);

private:
=======
>>>>>>> upstream/master
	required_device<centronics_device> m_centronics;
	required_device<output_latch_device> m_latch;

	int m_centronics_busy;
	int m_centronics_out_of_paper;
	int m_centronics_unit_sel;
	int m_centronics_ready;
};

// device type definition
<<<<<<< HEAD
extern const device_type CGENIE_PRINTER;

#endif // __CGENIE_PARALLEL_PRINTER_H__
=======
DECLARE_DEVICE_TYPE(CGENIE_PRINTER, cgenie_printer_device)

#endif // MAME_BUS_CGENIE_PARALLEL_PRINTER_H
>>>>>>> upstream/master
