// license:GPL-2.0+
// copyright-holders:Fabio Priuli, byuu
<<<<<<< HEAD
#ifndef __SNS_SPC7110_H
#define __SNS_SPC7110_H
=======
#ifndef MAME_BUS_SNES_SPC7110_H
#define MAME_BUS_SNES_SPC7110_H

#pragma once
>>>>>>> upstream/master

#include "snes_slot.h"
#include "rom21.h"


<<<<<<< HEAD
enum RTC_State
{
	RTCS_Inactive,
	RTCS_ModeSelect,
	RTCS_IndexSelect,
	RTCS_Write
};

enum RTC_Mode
{
	RTCM_Linear = 0x03,
	RTCM_Indexed = 0x0c
};

class SPC7110_Decomp
{
public:
	SPC7110_Decomp(running_machine &machine);

	running_machine &machine() const { return m_machine; }

	void init(running_machine &machine, UINT8 *ROM, UINT32 len, UINT32 mode, UINT32 offset, UINT32 index);
	void reset();

	UINT8 read(UINT8 *ROM, UINT32 len);
	void write(UINT8 data);
	void mode0(UINT8 init, UINT8 *ROM, UINT32 len);
	void mode1(UINT8 init, UINT8 *ROM, UINT32 len);
	void mode2(UINT8 init, UINT8 *ROM, UINT32 len);

private:

	UINT8 dataread(UINT8 *ROM, UINT32 len);
	UINT8 probability(UINT32 n);
	UINT8 next_lps(UINT32 n);
	UINT8 next_mps(UINT32 n);
	UINT8 toggle_invert(UINT32 n);
	UINT32 morton_2x8(UINT32 data);
	UINT32 morton_4x8(UINT32 data);

	UINT32 m_decomp_mode;
	UINT32 m_decomp_offset;

	UINT8 *m_decomp_buffer;
	UINT32 m_decomp_buffer_rdoffset;
	UINT32 m_decomp_buffer_wroffset;
	UINT32 m_decomp_buffer_length;

	struct ContextState
	{
		UINT8 index;
		UINT8 invert;
	} m_context[32];

	UINT32 m_morton16[2][256];
	UINT32 m_morton32[4][256];

	// mode 0 vars
	UINT8 m_m0_val, m_m0_in, m_m0_span;
	INT32 m_m0_out, m_m0_inverts, m_m0_lps, m_m0_in_count;

	// mode 1 vars
	INT32 m_m1_pixelorder[4], m_m1_realorder[4];
	UINT8 m_m1_in, m_m1_val, m_m1_span;
	INT32 m_m1_out, m_m1_inverts, m_m1_lps, m_m1_in_count;

	// mode 2 vars
	INT32 m_m2_pixelorder[16], m_m2_realorder[16];
	UINT8 m_m2_bitplanebuffer[16], m_m2_buffer_index;
	UINT8 m_m2_in, m_m2_val, m_m2_span;
	INT32 m_m2_out0, m_m2_out1, m_m2_inverts, m_m2_lps, m_m2_in_count;

	running_machine& m_machine;
	//UINT32 m_rom_size;
};

=======
>>>>>>> upstream/master
// ======================> sns_rom_spc7110_device

class sns_rom_spc7110_device : public sns_rom21_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_spc7110_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	sns_rom_spc7110_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);

	virtual DECLARE_READ8_MEMBER(chip_read);
	virtual DECLARE_WRITE8_MEMBER(chip_write);

	void spc7110_start();
	UINT32 spc7110_datarom_addr(UINT32 addr, UINT32 len);
	UINT32 spc7110_data_pointer();
	UINT32 spc7110_data_adjust();
	UINT32 spc7110_data_increment();
	void spc7110_set_data_pointer(UINT32 addr);
	void spc7110_set_data_adjust(UINT32 addr);
	void spc7110_update_time(UINT8 offset);
=======
	sns_rom_spc7110_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

	virtual DECLARE_READ8_MEMBER(chip_read) override;
	virtual DECLARE_WRITE8_MEMBER(chip_write) override;

protected:
	sns_rom_spc7110_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;

	class SPC7110_Decomp
	{
	public:
		SPC7110_Decomp(running_machine &machine);

		running_machine &machine() const { return m_machine; }

		void init(running_machine &machine, uint8_t *ROM, uint32_t len, uint32_t mode, uint32_t offset, uint32_t index);
		void reset();

		uint8_t read(uint8_t *ROM, uint32_t len);
		void write(uint8_t data);
		void mode0(uint8_t init, uint8_t *ROM, uint32_t len);
		void mode1(uint8_t init, uint8_t *ROM, uint32_t len);
		void mode2(uint8_t init, uint8_t *ROM, uint32_t len);

	private:

		uint8_t dataread(uint8_t *ROM, uint32_t len);
		uint8_t probability(uint32_t n);
		uint8_t next_lps(uint32_t n);
		uint8_t next_mps(uint32_t n);
		uint8_t toggle_invert(uint32_t n);
		uint32_t morton_2x8(uint32_t data);
		uint32_t morton_4x8(uint32_t data);

		uint32_t m_decomp_mode;
		uint32_t m_decomp_offset;

		std::unique_ptr<uint8_t[]> m_decomp_buffer;
		uint32_t m_decomp_buffer_rdoffset;
		uint32_t m_decomp_buffer_wroffset;
		uint32_t m_decomp_buffer_length;

		struct ContextState
		{
			uint8_t index;
			uint8_t invert;
		} m_context[32];

		uint32_t m_morton16[2][256];
		uint32_t m_morton32[4][256];

		// mode 0 vars
		uint8_t m_m0_val, m_m0_in, m_m0_span;
		int32_t m_m0_out, m_m0_inverts, m_m0_lps, m_m0_in_count;

		// mode 1 vars
		int32_t m_m1_pixelorder[4], m_m1_realorder[4];
		uint8_t m_m1_in, m_m1_val, m_m1_span;
		int32_t m_m1_out, m_m1_inverts, m_m1_lps, m_m1_in_count;

		// mode 2 vars
		int32_t m_m2_pixelorder[16], m_m2_realorder[16];
		uint8_t m_m2_bitplanebuffer[16], m_m2_buffer_index;
		uint8_t m_m2_in, m_m2_val, m_m2_span;
		int32_t m_m2_out0, m_m2_out1, m_m2_inverts, m_m2_lps, m_m2_in_count;

		running_machine& m_machine;
		//uint32_t m_rom_size;
	};

	void spc7110_start();
	uint32_t spc7110_datarom_addr(uint32_t addr, uint32_t len);
	uint32_t spc7110_data_pointer();
	uint32_t spc7110_data_adjust();
	uint32_t spc7110_data_increment();
	void spc7110_set_data_pointer(uint32_t addr);
	void spc7110_set_data_adjust(uint32_t addr);
	void spc7110_update_time(uint8_t offset);
>>>>>>> upstream/master


	//==================
	//decompression unit
	//==================
<<<<<<< HEAD
	UINT8 m_r4801;        // compression table low
	UINT8 m_r4802;        // compression table high
	UINT8 m_r4803;        // compression table bank
	UINT8 m_r4804;        // compression table index
	UINT8 m_r4805;        // decompression buffer index low
	UINT8 m_r4806;        // decompression buffer index high
	UINT8 m_r4807;        // ???
	UINT8 m_r4808;        // ???
	UINT8 m_r4809;        // compression length low
	UINT8 m_r480a;        // compression length high
	UINT8 m_r480b;        // decompression control register
	UINT8 m_r480c;        // decompression status

	SPC7110_Decomp* m_decomp;

	UINT8 m_r4811;        // data pointer low
	UINT8 m_r4812;        // data pointer high
	UINT8 m_r4813;        // data pointer bank
	UINT8 m_r4814;        // data adjust low
	UINT8 m_r4815;        // data adjust high
	UINT8 m_r4816;        // data increment low
	UINT8 m_r4817;        // data increment high
	UINT8 m_r4818;        // data port control register

	UINT8 m_r481x;

	UINT8 m_r4814_latch;
	UINT8 m_r4815_latch;
=======
	uint8_t m_r4801;        // compression table low
	uint8_t m_r4802;        // compression table high
	uint8_t m_r4803;        // compression table bank
	uint8_t m_r4804;        // compression table index
	uint8_t m_r4805;        // decompression buffer index low
	uint8_t m_r4806;        // decompression buffer index high
	uint8_t m_r4807;        // ???
	uint8_t m_r4808;        // ???
	uint8_t m_r4809;        // compression length low
	uint8_t m_r480a;        // compression length high
	uint8_t m_r480b;        // decompression control register
	uint8_t m_r480c;        // decompression status

	std::unique_ptr<SPC7110_Decomp> m_decomp;

	uint8_t m_r4811;        // data pointer low
	uint8_t m_r4812;        // data pointer high
	uint8_t m_r4813;        // data pointer bank
	uint8_t m_r4814;        // data adjust low
	uint8_t m_r4815;        // data adjust high
	uint8_t m_r4816;        // data increment low
	uint8_t m_r4817;        // data increment high
	uint8_t m_r4818;        // data port control register

	uint8_t m_r481x;

	uint8_t m_r4814_latch;
	uint8_t m_r4815_latch;
>>>>>>> upstream/master

	//=========
	//math unit
	//=========
<<<<<<< HEAD
	UINT8 m_r4820;        // 16-bit multiplicand B0, 32-bit dividend B0
	UINT8 m_r4821;        // 16-bit multiplicand B1, 32-bit dividend B1
	UINT8 m_r4822;        // 32-bit dividend B2
	UINT8 m_r4823;        // 32-bit dividend B3
	UINT8 m_r4824;        // 16-bit multiplier B0
	UINT8 m_r4825;        // 16-bit multiplier B1
	UINT8 m_r4826;        // 16-bit divisor B0
	UINT8 m_r4827;        // 16-bit divisor B1
	UINT8 m_r4828;        // 32-bit product B0, 32-bit quotient B0
	UINT8 m_r4829;        // 32-bit product B1, 32-bit quotient B1
	UINT8 m_r482a;        // 32-bit product B2, 32-bit quotient B2
	UINT8 m_r482b;        // 32-bit product B3, 32-bit quotient B3
	UINT8 m_r482c;        // 16-bit remainder B0
	UINT8 m_r482d;        // 16-bit remainder B1
	UINT8 m_r482e;        // math control register
	UINT8 m_r482f;        // math status
=======
	uint8_t m_r4820;        // 16-bit multiplicand B0, 32-bit dividend B0
	uint8_t m_r4821;        // 16-bit multiplicand B1, 32-bit dividend B1
	uint8_t m_r4822;        // 32-bit dividend B2
	uint8_t m_r4823;        // 32-bit dividend B3
	uint8_t m_r4824;        // 16-bit multiplier B0
	uint8_t m_r4825;        // 16-bit multiplier B1
	uint8_t m_r4826;        // 16-bit divisor B0
	uint8_t m_r4827;        // 16-bit divisor B1
	uint8_t m_r4828;        // 32-bit product B0, 32-bit quotient B0
	uint8_t m_r4829;        // 32-bit product B1, 32-bit quotient B1
	uint8_t m_r482a;        // 32-bit product B2, 32-bit quotient B2
	uint8_t m_r482b;        // 32-bit product B3, 32-bit quotient B3
	uint8_t m_r482c;        // 16-bit remainder B0
	uint8_t m_r482d;        // 16-bit remainder B1
	uint8_t m_r482e;        // math control register
	uint8_t m_r482f;        // math status
>>>>>>> upstream/master

	//===================
	//memory mapping unit
	//===================
<<<<<<< HEAD
	UINT8 m_r4830;        // SRAM write enable
	UINT8 m_r4831;        // $[d0-df]:[0000-ffff] mapping
	UINT8 m_r4832;        // $[e0-ef]:[0000-ffff] mapping
	UINT8 m_r4833;        // $[f0-ff]:[0000-ffff] mapping
	UINT8 m_r4834;        // ???

	UINT32 m_dx_offset;
	UINT32 m_ex_offset;
	UINT32 m_fx_offset;
=======
	uint8_t m_r4830;        // SRAM write enable
	uint8_t m_r4831;        // $[d0-df]:[0000-ffff] mapping
	uint8_t m_r4832;        // $[e0-ef]:[0000-ffff] mapping
	uint8_t m_r4833;        // $[f0-ff]:[0000-ffff] mapping
	uint8_t m_r4834;        // ???

	uint32_t m_dx_offset;
	uint32_t m_ex_offset;
	uint32_t m_fx_offset;
>>>>>>> upstream/master

	//====================
	//real-time clock unit
	//====================
<<<<<<< HEAD
	UINT8 m_r4840;        // RTC latch
	UINT8 m_r4841;        // RTC index/data port
	UINT8 m_r4842;        // RTC status

	UINT32 m_rtc_state;
	UINT32 m_rtc_mode;
	UINT32 m_rtc_index;

	UINT64 m_rtc_offset;
=======
	uint8_t m_r4840;        // RTC latch
	uint8_t m_r4841;        // RTC index/data port
	uint8_t m_r4842;        // RTC status

	uint32_t m_rtc_state;
	uint32_t m_rtc_mode;
	uint32_t m_rtc_index;

	uint64_t m_rtc_offset;
>>>>>>> upstream/master

	system_time m_rtc_basetime;

	//this is now allocated in the main snes cart class, to allow saving to nvram
<<<<<<< HEAD
	//UINT8 m_rtc_ram[16];  // 0-12 secs, min, hrs, etc.; 13-14-15 control registers
=======
	//uint8_t m_rtc_ram[16];  // 0-12 secs, min, hrs, etc.; 13-14-15 control registers
>>>>>>> upstream/master
};

// ======================> sns_rom_spc7110_device

class sns_rom_spc7110rtc_device : public sns_rom_spc7110_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_spc7110rtc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
=======
	sns_rom_spc7110rtc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// reading and writing

// we just use the spc7110 ones for the moment, pending the split of regs 0x4840-0x4842 (RTC) from the base add-on
//  virtual DECLARE_READ8_MEMBER(read_l);
//  virtual DECLARE_READ8_MEMBER(read_h);

//  virtual DECLARE_READ8_MEMBER(chip_read);
//  virtual DECLARE_WRITE8_MEMBER(chip_write);
<<<<<<< HEAD
};

// device type definition
extern const device_type SNS_HIROM_SPC7110;
extern const device_type SNS_HIROM_SPC7110_RTC;

#endif
=======

protected:
	// device-level overrides
	virtual void device_start() override;
};

// device type definition
DECLARE_DEVICE_TYPE(SNS_HIROM_SPC7110,     sns_rom_spc7110_device)
DECLARE_DEVICE_TYPE(SNS_HIROM_SPC7110_RTC, sns_rom_spc7110rtc_device)

#endif // MAME_BUS_SNES_SPC7110_H
>>>>>>> upstream/master
