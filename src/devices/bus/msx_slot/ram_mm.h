// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_SLOT_RAM_MM_H
#define __MSX_SLOT_RAM_MM_H
=======
#ifndef MAME_BUS_MSX_SLOT_RAM_MM_H
#define MAME_BUS_MSX_SLOT_RAM_MM_H
>>>>>>> upstream/master

#include "slot.h"

#define MCFG_MSX_SLOT_RAM_MM_ADD(_tag, _total_size) \
	MCFG_MSX_INTERNAL_SLOT_ADD(_tag, MSX_SLOT_RAM_MM, 0, 4) \
	msx_slot_ram_mm_device::set_total_size(*device, _total_size);

#define MCFG_MSX_SLOT_RAMM_SET_RAMIO_BITS(_ramio_set_bits) \
	msx_slot_ram_mm_device::set_ramio_set_bits(*device, _ramio_set_bits);

<<<<<<< HEAD
class msx_slot_ram_mm_device : public device_t
							, public msx_internal_slot_interface
{
public:
	msx_slot_ram_mm_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	static void set_total_size(device_t &device, UINT32 total_size) { dynamic_cast<msx_slot_ram_mm_device &>(device).m_total_size = total_size; }
	static void set_ramio_set_bits(device_t &device, UINT8 ramio_set_bits) { dynamic_cast<msx_slot_ram_mm_device &>(device).m_ramio_set_bits = ramio_set_bits; }

	virtual void device_start();

	virtual DECLARE_READ8_MEMBER(read);
	virtual DECLARE_WRITE8_MEMBER(write);
=======
class msx_slot_ram_mm_device : public device_t, public msx_internal_slot_interface
{
public:
	msx_slot_ram_mm_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	static void set_total_size(device_t &device, uint32_t total_size) { dynamic_cast<msx_slot_ram_mm_device &>(device).m_total_size = total_size; }
	static void set_ramio_set_bits(device_t &device, uint8_t ramio_set_bits) { dynamic_cast<msx_slot_ram_mm_device &>(device).m_ramio_set_bits = ramio_set_bits; }

	virtual DECLARE_READ8_MEMBER(read) override;
	virtual DECLARE_WRITE8_MEMBER(write) override;
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(read_mapper_bank);
	DECLARE_WRITE8_MEMBER(write_mapper_bank);

<<<<<<< HEAD
	void restore_banks();

private:
	std::vector<UINT8> m_ram;
	UINT32 m_total_size;
	UINT8 m_bank_mask;
	UINT8 m_bank_selected[4];
	UINT8 *m_bank_base[4];
	UINT8 m_ramio_set_bits;
};

extern const device_type MSX_SLOT_RAM_MM;

#endif
=======
protected:
	virtual void device_start() override;

	void restore_banks();

private:
	std::vector<uint8_t> m_ram;
	uint32_t m_total_size;
	uint8_t m_bank_mask;
	uint8_t m_bank_selected[4];
	uint8_t *m_bank_base[4];
	uint8_t m_ramio_set_bits;
};

DECLARE_DEVICE_TYPE(MSX_SLOT_RAM_MM, msx_slot_ram_mm_device)

#endif // MAME_BUS_MSX_SLOT_RAM_MM_H
>>>>>>> upstream/master
