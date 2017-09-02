// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
<<<<<<< HEAD
#pragma once

#ifndef __IQ151_MINIGRAF_H__
#define __IQ151_MINIGRAF_H__

#include "emu.h"
=======
#ifndef MAME_BUS_IQ151_MINIGRAF_H
#define MAME_BUS_IQ151_MINIGRAF_H

#pragma once

>>>>>>> upstream/master
#include "iq151.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> iq151_minigraf_device

class iq151_minigraf_device :
		public device_t,
		public device_iq151cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	iq151_minigraf_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_stop();

	// iq151cart_interface overrides
	virtual void read(offs_t offset, UINT8 &data);
	virtual void io_write(offs_t offset, UINT8 data);

	// Aritma MINIGRAF 0507
	void plotter_update(UINT8 control);
	int get_direction(UINT8 old_val, UINT8 new_val);

private:

	UINT8 *     m_rom;
	INT16       m_posx;
	INT16       m_posy;
	UINT8       m_pen;
	UINT8       m_control;

	bitmap_ind16 *  m_paper;
=======
	iq151_minigraf_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_stop() override;

	// iq151cart_interface overrides
	virtual void read(offs_t offset, uint8_t &data) override;
	virtual void io_write(offs_t offset, uint8_t data) override;

	// Aritma MINIGRAF 0507
	void plotter_update(uint8_t control);
	int get_direction(uint8_t old_val, uint8_t new_val);

private:

	uint8_t *     m_rom;
	int16_t       m_posx;
	int16_t       m_posy;
	uint8_t       m_pen;
	uint8_t       m_control;

	std::unique_ptr<bitmap_ind16>  m_paper;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type IQ151_MINIGRAF;

#endif  /* __IQ151_MINIGRAF_H__ */
=======
DECLARE_DEVICE_TYPE(IQ151_MINIGRAF, iq151_minigraf_device)

#endif // MAME_BUS_IQ151_MINIGRAF_H
>>>>>>> upstream/master
