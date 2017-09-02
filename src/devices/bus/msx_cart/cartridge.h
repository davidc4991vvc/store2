// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_CART_CARTRIDGE_H
#define __MSX_CART_CARTRIDGE_H
=======
#ifndef MAME_BUS_MSX_CART_CARTRIDGE_H
#define MAME_BUS_MSX_CART_CARTRIDGE_H

#pragma once
>>>>>>> upstream/master


SLOT_INTERFACE_EXTERN(msx_cart);
SLOT_INTERFACE_EXTERN(msx_yamaha_60pin);   // 60 pin expansion slots as found in yamaha machines


class msx_cart_interface : public device_slot_card_interface
{
public:
<<<<<<< HEAD
	msx_cart_interface(const machine_config &mconfig, device_t &device);

	template<class _Object> void set_out_irq_cb(_Object object) { m_out_irq_cb.set_callback(object); m_out_irq_cb.resolve_safe(); }
=======
	template <class Object> void set_out_irq_cb(Object &&cb) { m_out_irq_cb.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	// This is called after loading cartridge contents and allows the cartridge
	// implementation to perform some additional initialization based on the
	// cartridge contents.
<<<<<<< HEAD
	virtual void initialize_cartridge() {}

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) { return 0xff; }
	virtual DECLARE_WRITE8_MEMBER(write_cart) {}

	// ROM/RAM/SRAM management
	// Mainly used by the cartridge slot when loading images
	void rom_alloc(UINT32 size);
	void ram_alloc(UINT32 size);
	void rom_vlm5030_alloc(UINT32 size);
	void sram_alloc(UINT32 size);

	UINT8* get_rom_base() { return &m_rom[0]; }
	UINT8* get_rom_vlm5030_base() { return &m_rom_vlm5030[0]; }
	UINT8* get_ram_base() { return &m_ram[0]; }
	UINT8* get_sram_base() { return &m_sram[0]; }
	UINT32 get_rom_size() { return m_rom.size(); }
	UINT32 get_rom_vlm5030_size() { return m_rom_vlm5030.size(); }
	UINT32 get_ram_size() { return m_ram.size(); }
	UINT32 get_sram_size() { return m_sram.size(); }

protected:
	dynamic_buffer m_rom;
	dynamic_buffer m_ram;
	dynamic_buffer m_rom_vlm5030;
	dynamic_buffer m_sram;
=======
	virtual void initialize_cartridge() { }

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) { return 0xff; }
	virtual DECLARE_WRITE8_MEMBER(write_cart) { }

	// ROM/RAM/SRAM management
	// Mainly used by the cartridge slot when loading images
	void rom_alloc(uint32_t size);
	void ram_alloc(uint32_t size);
	void rom_vlm5030_alloc(uint32_t size);
	void sram_alloc(uint32_t size);

	uint8_t* get_rom_base() { return &m_rom[0]; }
	uint8_t* get_rom_vlm5030_base() { return &m_rom_vlm5030[0]; }
	uint8_t* get_ram_base() { return &m_ram[0]; }
	uint8_t* get_sram_base() { return &m_sram[0]; }
	uint32_t get_rom_size() { return m_rom.size(); }
	uint32_t get_rom_vlm5030_size() { return m_rom_vlm5030.size(); }
	uint32_t get_ram_size() { return m_ram.size(); }
	uint32_t get_sram_size() { return m_sram.size(); }

protected:
	msx_cart_interface(const machine_config &mconfig, device_t &device);

	virtual void interface_pre_start() override { m_out_irq_cb.resolve_safe(); }

	std::vector<uint8_t> m_rom;
	std::vector<uint8_t> m_ram;
	std::vector<uint8_t> m_rom_vlm5030;
	std::vector<uint8_t> m_sram;
>>>>>>> upstream/master
	devcb_write_line m_out_irq_cb;
};


<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_MSX_CART_CARTRIDGE_H
>>>>>>> upstream/master
