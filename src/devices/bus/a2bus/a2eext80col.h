// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    a2eext80col.c

    Apple IIe Extended 80 Column Card

*********************************************************************/

<<<<<<< HEAD
#ifndef __A2EAUX_EXT80COL__
#define __A2EAUX_EXT80COL__

#include "emu.h"
=======
#ifndef MAME_BUS_A2BUS_A2EEXT809COL_H
#define MAME_BUS_A2BUS_A2EEXT809COL_H

#pragma once

>>>>>>> upstream/master
#include "a2eauxslot.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class a2eaux_ext80col_device:
	public device_t,
	public device_a2eauxslot_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	a2eaux_ext80col_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	a2eaux_ext80col_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

protected:
	virtual void device_start();
	virtual void device_reset();

	virtual UINT8 read_auxram(UINT16 offset);
	virtual void write_auxram(UINT16 offset, UINT8 data);
	virtual UINT8 *get_vram_ptr();
	virtual UINT8 *get_auxbank_ptr();
	virtual bool allow_dhr() { return true; }

private:
	UINT8 m_ram[64*1024];
};

// device type definition
extern const device_type A2EAUX_EXT80COL;

#endif  /* __A2EAUX_EXT80COL__ */
=======
	a2eaux_ext80col_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	a2eaux_ext80col_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;

	virtual uint8_t read_auxram(uint16_t offset) override;
	virtual void write_auxram(uint16_t offset, uint8_t data) override;
	virtual uint8_t *get_vram_ptr() override;
	virtual uint8_t *get_auxbank_ptr() override;
	virtual bool allow_dhr() override { return true; }

private:
	uint8_t m_ram[64*1024];
};

// device type definition
DECLARE_DEVICE_TYPE(A2EAUX_EXT80COL, a2eaux_ext80col_device)

#endif // MAME_BUS_A2BUS_A2EEXT809COL_H
>>>>>>> upstream/master
