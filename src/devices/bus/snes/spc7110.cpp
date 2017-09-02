// license:GPL-2.0+
// copyright-holders:Fabio Priuli, byuu
/***********************************************************************************************************

 SPC-7110 add-on chip emulation (for SNES/SFC)

 Based on C++ implementation by Byuu in BSNES.

 Byuu's code is released under GNU General Public License
 version 2 as published by the Free Software Foundation.

 ***********************************************************************************************************/


#include "emu.h"
#include "spc7110.h"


<<<<<<< HEAD
=======
namespace {

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

} // anonymous namespace

>>>>>>> upstream/master
//-------------------------------------------------
//  constructor
//-------------------------------------------------

<<<<<<< HEAD
const device_type SNS_HIROM_SPC7110 = &device_creator<sns_rom_spc7110_device>;
const device_type SNS_HIROM_SPC7110_RTC = &device_creator<sns_rom_spc7110rtc_device>;


sns_rom_spc7110_device::sns_rom_spc7110_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source)
			: sns_rom21_device(mconfig, type, name, tag, owner, clock, shortname, source), m_r4801(0), m_r4802(0), m_r4803(0), m_r4804(0), m_r4805(0), m_r4806(0), m_r4807(0),
	m_r4808(0), m_r4809(0), m_r480a(0), m_r480b(0), m_r480c(0), m_decomp(nullptr), m_r4811(0), m_r4812(0), m_r4813(0), m_r4814(0), m_r4815(0), m_r4816(0), m_r4817(0), m_r4818(0),
	m_r481x(0), m_r4814_latch(0), m_r4815_latch(0), m_r4820(0), m_r4821(0), m_r4822(0), m_r4823(0), m_r4824(0), m_r4825(0), m_r4826(0), m_r4827(0), m_r4828(0), m_r4829(0), m_r482a(0),
	m_r482b(0), m_r482c(0), m_r482d(0), m_r482e(0), m_r482f(0), m_r4830(0), m_r4831(0), m_r4832(0), m_r4833(0), m_r4834(0), m_dx_offset(0), m_ex_offset(0), m_fx_offset(0), m_r4840(0),
	m_r4841(0), m_r4842(0), m_rtc_state(0), m_rtc_mode(0), m_rtc_index(0), m_rtc_offset(0)
		{
}

sns_rom_spc7110_device::sns_rom_spc7110_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
			: sns_rom21_device(mconfig, SNS_HIROM_SPC7110, "SNES Cart + SPC-7110", tag, owner, clock, "sns_rom_spc7110", __FILE__), m_r4801(0), m_r4802(0), m_r4803(0), m_r4804(0), m_r4805(0), m_r4806(0), m_r4807(0),
	m_r4808(0), m_r4809(0), m_r480a(0), m_r480b(0), m_r480c(0), m_decomp(nullptr), m_r4811(0), m_r4812(0), m_r4813(0), m_r4814(0), m_r4815(0), m_r4816(0), m_r4817(0), m_r4818(0),
	m_r481x(0), m_r4814_latch(0), m_r4815_latch(0), m_r4820(0), m_r4821(0), m_r4822(0), m_r4823(0), m_r4824(0), m_r4825(0), m_r4826(0), m_r4827(0), m_r4828(0), m_r4829(0), m_r482a(0),
	m_r482b(0), m_r482c(0), m_r482d(0), m_r482e(0), m_r482f(0), m_r4830(0), m_r4831(0), m_r4832(0), m_r4833(0), m_r4834(0), m_dx_offset(0), m_ex_offset(0), m_fx_offset(0), m_r4840(0),
	m_r4841(0), m_r4842(0), m_rtc_state(0), m_rtc_mode(0), m_rtc_index(0), m_rtc_offset(0)
{
}

sns_rom_spc7110rtc_device::sns_rom_spc7110rtc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
			: sns_rom_spc7110_device(mconfig, SNS_HIROM_SPC7110_RTC, "SNES Cart + SPC-7110 + RTC", tag, owner, clock, "sns_rom_spc7110rtc", __FILE__)
=======
DEFINE_DEVICE_TYPE(SNS_HIROM_SPC7110,     sns_rom_spc7110_device,    "sns_rom_spc7110",    "SNES Cart + SPC7110")
DEFINE_DEVICE_TYPE(SNS_HIROM_SPC7110_RTC, sns_rom_spc7110rtc_device, "sns_rom_spc7110rtc", "SNES Cart + SPC7110 + RTC")


sns_rom_spc7110_device::sns_rom_spc7110_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock)
	: sns_rom21_device(mconfig, type, tag, owner, clock)
	, m_r4801(0), m_r4802(0), m_r4803(0), m_r4804(0), m_r4805(0), m_r4806(0), m_r4807(0), m_r4808(0), m_r4809(0), m_r480a(0), m_r480b(0), m_r480c(0)
	, m_decomp(nullptr)
	, m_r4811(0), m_r4812(0), m_r4813(0), m_r4814(0), m_r4815(0), m_r4816(0), m_r4817(0), m_r4818(0), m_r481x(0), m_r4814_latch(0), m_r4815_latch(0)
	, m_r4820(0), m_r4821(0), m_r4822(0), m_r4823(0), m_r4824(0), m_r4825(0), m_r4826(0), m_r4827(0), m_r4828(0), m_r4829(0), m_r482a(0), m_r482b(0), m_r482c(0), m_r482d(0), m_r482e(0), m_r482f(0)
	, m_r4830(0), m_r4831(0), m_r4832(0), m_r4833(0), m_r4834(0)
	, m_dx_offset(0), m_ex_offset(0), m_fx_offset(0)
	, m_r4840(0), m_r4841(0), m_r4842(0)
	, m_rtc_state(0), m_rtc_mode(0), m_rtc_index(0), m_rtc_offset(0)
{
}

sns_rom_spc7110_device::sns_rom_spc7110_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: sns_rom_spc7110_device(mconfig, SNS_HIROM_SPC7110, tag, owner, clock)
{
}

sns_rom_spc7110rtc_device::sns_rom_spc7110rtc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: sns_rom_spc7110_device(mconfig, SNS_HIROM_SPC7110_RTC, tag, owner, clock)
>>>>>>> upstream/master
{
}


void sns_rom_spc7110_device::spc7110_start()
{
<<<<<<< HEAD
	m_decomp = auto_alloc(machine(), SPC7110_Decomp(machine()));
=======
	m_decomp = std::make_unique<SPC7110_Decomp>(machine());
>>>>>>> upstream/master

	// The SPC7110 works in conjunction with 0x2000 of RAM, which is battery backed up (and hence emulated by our m_nvram)

	m_r4801 = 0x00;
	m_r4802 = 0x00;
	m_r4803 = 0x00;
	m_r4804 = 0x00;
	m_r4805 = 0x00;
	m_r4806 = 0x00;
	m_r4807 = 0x00;
	m_r4808 = 0x00;
	m_r4809 = 0x00;
	m_r480a = 0x00;
	m_r480b = 0x00;
	m_r480c = 0x00;

	m_r4811 = 0x00;
	m_r4812 = 0x00;
	m_r4813 = 0x00;
	m_r4814 = 0x00;
	m_r4815 = 0x00;
	m_r4816 = 0x00;
	m_r4817 = 0x00;
	m_r4818 = 0x00;

	m_r481x = 0x00;
	m_r4814_latch = 0;
	m_r4815_latch = 0;

	m_r4820 = 0x00;
	m_r4821 = 0x00;
	m_r4822 = 0x00;
	m_r4823 = 0x00;
	m_r4824 = 0x00;
	m_r4825 = 0x00;
	m_r4826 = 0x00;
	m_r4827 = 0x00;
	m_r4828 = 0x00;
	m_r4829 = 0x00;
	m_r482a = 0x00;
	m_r482b = 0x00;
	m_r482c = 0x00;
	m_r482d = 0x00;
	m_r482e = 0x00;
	m_r482f = 0x00;

	m_r4830 = 0x00;
	m_r4831 = 0;
	m_dx_offset = spc7110_datarom_addr(0 * 0x100000, 0x200000); // we would need the rom length here...
	m_r4832 = 1;
	m_ex_offset = spc7110_datarom_addr(1 * 0x100000, 0x200000); // we would need the rom length here...
	m_r4833 = 2;
	m_fx_offset = spc7110_datarom_addr(2 * 0x100000, 0x200000); // we would need the rom length here...
	m_r4834 = 0x00;

	m_r4840 = 0x00;
	m_r4841 = 0x00;
	m_r4842 = 0x00;

	save_item(NAME(m_r4801));
	save_item(NAME(m_r4802));
	save_item(NAME(m_r4803));
	save_item(NAME(m_r4804));
	save_item(NAME(m_r4805));
	save_item(NAME(m_r4806));
	save_item(NAME(m_r4807));
	save_item(NAME(m_r4808));
	save_item(NAME(m_r4809));
	save_item(NAME(m_r480a));
	save_item(NAME(m_r480b));
	save_item(NAME(m_r480c));
	save_item(NAME(m_r4811));
	save_item(NAME(m_r4812));
	save_item(NAME(m_r4813));
	save_item(NAME(m_r4814));
	save_item(NAME(m_r4815));
	save_item(NAME(m_r4816));
	save_item(NAME(m_r4817));
	save_item(NAME(m_r4818));
	save_item(NAME(m_r481x));
	save_item(NAME(m_r4814_latch));
	save_item(NAME(m_r4815_latch));
	save_item(NAME(m_r4820));
	save_item(NAME(m_r4821));
	save_item(NAME(m_r4822));
	save_item(NAME(m_r4823));
	save_item(NAME(m_r4824));
	save_item(NAME(m_r4825));
	save_item(NAME(m_r4826));
	save_item(NAME(m_r4827));
	save_item(NAME(m_r4828));
	save_item(NAME(m_r4829));
	save_item(NAME(m_r482a));
	save_item(NAME(m_r482b));
	save_item(NAME(m_r482c));
	save_item(NAME(m_r482d));
	save_item(NAME(m_r482e));
	save_item(NAME(m_r482f));
	save_item(NAME(m_r4830));
	save_item(NAME(m_r4831));
	save_item(NAME(m_r4832));
	save_item(NAME(m_r4833));
	save_item(NAME(m_r4834));
	save_item(NAME(m_r4840));
	save_item(NAME(m_r4841));
	save_item(NAME(m_r4842));
	save_item(NAME(m_dx_offset));
	save_item(NAME(m_ex_offset));
	save_item(NAME(m_fx_offset));
}

void sns_rom_spc7110_device::device_start()
{
	spc7110_start();
}

void sns_rom_spc7110rtc_device::device_start()
{
	spc7110_start();

	// RTC
	m_rtc_state = RTCS_Inactive;
	m_rtc_mode  = RTCM_Linear;
	m_rtc_index = 0;
	m_rtc_offset = 0;

// at this stage, rtc_ram is not yet allocated. this will be fixed when converting RTC to be a separate device.
//  spc7110_update_time(0);

	// set basetime for RTC
	machine().current_datetime(m_rtc_basetime);

	save_item(NAME(m_rtc_state));
	save_item(NAME(m_rtc_mode));
	save_item(NAME(m_rtc_index));
	save_item(NAME(m_rtc_offset));
}


/*-------------------------------------------------
 mapper specific handlers
 -------------------------------------------------*/

#define SPC7110_DECOMP_BUFFER_SIZE 64

<<<<<<< HEAD
static const UINT8 spc7110_evolution_table[53][4] =
=======
static const uint8_t spc7110_evolution_table[53][4] =
>>>>>>> upstream/master
{
	{ 0x5a,  1,  1, 1 },
	{ 0x25,  6,  2, 0 },
	{ 0x11,  8,  3, 0 },
	{ 0x08, 10,  4, 0 },
	{ 0x03, 12,  5, 0 },
	{ 0x01, 15,  5, 0 },

	{ 0x5a,  7,  7, 1 },
	{ 0x3f, 19,  8, 0 },
	{ 0x2c, 21,  9, 0 },
	{ 0x20, 22, 10, 0 },
	{ 0x17, 23, 11, 0 },
	{ 0x11, 25, 12, 0 },
	{ 0x0c, 26, 13, 0 },
	{ 0x09, 28, 14, 0 },
	{ 0x07, 29, 15, 0 },
	{ 0x05, 31, 16, 0 },
	{ 0x04, 32, 17, 0 },
	{ 0x03, 34, 18, 0 },
	{ 0x02, 35,  5, 0 },

	{ 0x5a, 20, 20, 1 },
	{ 0x48, 39, 21, 0 },
	{ 0x3a, 40, 22, 0 },
	{ 0x2e, 42, 23, 0 },
	{ 0x26, 44, 24, 0 },
	{ 0x1f, 45, 25, 0 },
	{ 0x19, 46, 26, 0 },
	{ 0x15, 25, 27, 0 },
	{ 0x11, 26, 28, 0 },
	{ 0x0e, 26, 29, 0 },
	{ 0x0b, 27, 30, 0 },
	{ 0x09, 28, 31, 0 },
	{ 0x08, 29, 32, 0 },
	{ 0x07, 30, 33, 0 },
	{ 0x05, 31, 34, 0 },
	{ 0x04, 33, 35, 0 },
	{ 0x04, 33, 36, 0 },
	{ 0x03, 34, 37, 0 },
	{ 0x02, 35, 38, 0 },
	{ 0x02, 36,  5, 0 },

	{ 0x58, 39, 40, 1 },
	{ 0x4d, 47, 41, 0 },
	{ 0x43, 48, 42, 0 },
	{ 0x3b, 49, 43, 0 },
	{ 0x34, 50, 44, 0 },
	{ 0x2e, 51, 45, 0 },
	{ 0x29, 44, 46, 0 },
	{ 0x25, 45, 24, 0 },

	{ 0x56, 47, 48, 1 },
	{ 0x4f, 47, 49, 0 },
	{ 0x47, 48, 50, 0 },
	{ 0x41, 49, 51, 0 },
	{ 0x3c, 50, 52, 0 },
	{ 0x37, 51, 43, 0 },
};

<<<<<<< HEAD
static const UINT8 spc7110_mode2_context_table[32][2] =
=======
static const uint8_t spc7110_mode2_context_table[32][2] =
>>>>>>> upstream/master
{
	{  1,  2 },

	{  3,  8 },
	{ 13, 14 },

	{ 15, 16 },
	{ 17, 18 },
	{ 19, 20 },
	{ 21, 22 },
	{ 23, 24 },
	{ 25, 26 },
	{ 25, 26 },
	{ 25, 26 },
	{ 25, 26 },
	{ 25, 26 },
	{ 27, 28 },
	{ 29, 30 },

	{ 31, 31 },
	{ 31, 31 },
	{ 31, 31 },
	{ 31, 31 },
	{ 31, 31 },
	{ 31, 31 },
	{ 31, 31 },
	{ 31, 31 },
	{ 31, 31 },
	{ 31, 31 },
	{ 31, 31 },
	{ 31, 31 },
	{ 31, 31 },
	{ 31, 31 },
	{ 31, 31 },
	{ 31, 31 },

	{ 31, 31 },
};

<<<<<<< HEAD
SPC7110_Decomp::SPC7110_Decomp(running_machine &machine)
				:  m_machine(machine)
{
	m_decomp_buffer = (UINT8*)auto_alloc_array(machine, UINT8, SPC7110_DECOMP_BUFFER_SIZE);
	reset();

	for (int i = 0; i < 256; i++)
	{
#define map(x, y) (((i >> x) & 1) << y)
		//2x8-bit
		m_morton16[1][i] = map(7, 15) + map(6,  7) + map(5, 14) + map(4,  6)
		+ map(3, 13) + map(2,  5) + map(1, 12) + map(0,  4);
		m_morton16[0][i] = map(7, 11) + map(6,  3) + map(5, 10) + map(4,  2)
		+ map(3,  9) + map(2,  1) + map(1,  8) + map(0,  0);
		//4x8-bit
		m_morton32[3][i] = map(7, 31) + map(6, 23) + map(5, 15) + map(4,  7)
		+ map(3, 30) + map(2, 22) + map(1, 14) + map(0,  6);
		m_morton32[2][i] = map(7, 29) + map(6, 21) + map(5, 13) + map(4,  5)
		+ map(3, 28) + map(2, 20) + map(1, 12) + map(0,  4);
		m_morton32[1][i] = map(7, 27) + map(6, 19) + map(5, 11) + map(4,  3)
		+ map(3, 26) + map(2, 18) + map(1, 10) + map(0,  2);
		m_morton32[0][i] = map(7, 25) + map(6, 17) + map(5,  9) + map(4,  1)
		+ map(3, 24) + map(2, 16) + map(1,  8) + map(0,  0);
#undef map
=======
sns_rom_spc7110_device::SPC7110_Decomp::SPC7110_Decomp(running_machine &machine) :  m_machine(machine)
{
	m_decomp_buffer = std::make_unique<uint8_t[]>(SPC7110_DECOMP_BUFFER_SIZE);
	reset();

	for (uint32_t i = 0; i < 256; i++)
	{
		//2x8-bit
		m_morton16[0][i] = (bitswap<4>(i, 7, 5, 3, 1) << 8) | (bitswap<4>(i, 6, 4, 2, 0) << 0);
		m_morton16[1][i] = m_morton16[0][i] << 4;
		//4x8-bit
		m_morton32[0][i] = (bitswap<2>(i, 7, 3) << 24) | (bitswap<2>(i, 6, 2) << 16) | (bitswap<2>(i, 5, 1) << 8) | (bitswap<2>(i, 4, 0) << 0);
		m_morton32[1][i] = m_morton32[0][i] << 2;
		m_morton32[2][i] = m_morton32[0][i] << 4;
		m_morton32[3][i] = m_morton32[0][i] << 6;
>>>>>>> upstream/master
	}

	m_machine.save().save_item(m_decomp_mode, "SNES_SPC7110/m_decomp_mode");
	m_machine.save().save_item(m_decomp_offset, "SNES_SPC7110/m_decomp_offset");
<<<<<<< HEAD
	m_machine.save().save_pointer(m_decomp_buffer, "SNES_SPC7110/m_decomp_buffer", SPC7110_DECOMP_BUFFER_SIZE);
=======
	m_machine.save().save_pointer(m_decomp_buffer.get(), "SNES_SPC7110/m_decomp_buffer", SPC7110_DECOMP_BUFFER_SIZE);
>>>>>>> upstream/master
	m_machine.save().save_item(m_decomp_buffer_rdoffset, "SNES_SPC7110/m_decomp_buffer_rdoffset");
	m_machine.save().save_item(m_decomp_buffer_wroffset, "SNES_SPC7110/m_decomp_buffer_wroffset");
	m_machine.save().save_item(m_decomp_buffer_length, "SNES_SPC7110/m_decomp_buffer_length");

	for (int i = 0; i < 32; i++)
	{
		m_machine.save().save_item(m_context[i].index, "SNES_SPC7110/m_context[i].index", i);
		m_machine.save().save_item(m_context[i].invert, "SNES_SPC7110/m_context[i].invert", i);
	}

	m_machine.save().save_item(m_m0_val, "SNES_SPC7110/m_m0_val");
	m_machine.save().save_item(m_m0_in, "SNES_SPC7110/m_m0_in");
	m_machine.save().save_item(m_m0_span, "SNES_SPC7110/m_m0_span");
	m_machine.save().save_item(m_m0_out, "SNES_SPC7110/m_m0_out");
	m_machine.save().save_item(m_m0_inverts, "SNES_SPC7110/m_m0_inverts");
	m_machine.save().save_item(m_m0_lps, "SNES_SPC7110/m_m0_lps");
	m_machine.save().save_item(m_m0_in_count, "SNES_SPC7110/m_m0_in_count");

	m_machine.save().save_item(m_m1_pixelorder, "SNES_SPC7110/m_m1_pixelorder");
	m_machine.save().save_item(m_m1_realorder, "SNES_SPC7110/m_m1_realorder");
	m_machine.save().save_item(m_m1_val, "SNES_SPC7110/m_m1_val");
	m_machine.save().save_item(m_m1_in, "SNES_SPC7110/m_m1_in");
	m_machine.save().save_item(m_m1_span, "SNES_SPC7110/m_m1_span");
	m_machine.save().save_item(m_m1_out, "SNES_SPC7110/m_m1_out");
	m_machine.save().save_item(m_m1_inverts, "SNES_SPC7110/m_m1_inverts");
	m_machine.save().save_item(m_m1_lps, "SNES_SPC7110/m_m1_lps");
	m_machine.save().save_item(m_m1_in_count, "SNES_SPC7110/m_m1_in_count");

	m_machine.save().save_item(m_m2_pixelorder, "SNES_SPC7110/m_m2_pixelorder");
	m_machine.save().save_item(m_m2_realorder, "SNES_SPC7110/m_m2_realorder");
	m_machine.save().save_item(m_m2_bitplanebuffer, "SNES_SPC7110/m_m2_bitplanebuffer");
	m_machine.save().save_item(m_m2_buffer_index, "SNES_SPC7110/m_m2_buffer_index");
	m_machine.save().save_item(m_m2_val, "SNES_SPC7110/m_m2_val");
	m_machine.save().save_item(m_m2_in, "SNES_SPC7110/m_m2_in");
	m_machine.save().save_item(m_m2_span, "SNES_SPC7110/m_m2_span");
	m_machine.save().save_item(m_m2_out0, "SNES_SPC7110/m_m2_out0");
	m_machine.save().save_item(m_m2_out1, "SNES_SPC7110/m_m2_out1");
	m_machine.save().save_item(m_m2_inverts, "SNES_SPC7110/m_m2_inverts");
	m_machine.save().save_item(m_m2_lps, "SNES_SPC7110/m_m2_lps");
	m_machine.save().save_item(m_m2_in_count, "SNES_SPC7110/m_m2_in_count");
}

<<<<<<< HEAD
void SPC7110_Decomp::reset()
=======
void sns_rom_spc7110_device::SPC7110_Decomp::reset()
>>>>>>> upstream/master
{
	//mode 3 is invalid; this is treated as a special case to always return 0x00
	//set to mode 3 so that reading decomp port before starting first decomp will return 0x00
	m_decomp_mode = 3;

	m_decomp_buffer_rdoffset = 0;
	m_decomp_buffer_wroffset = 0;
	m_decomp_buffer_length   = 0;
}

<<<<<<< HEAD
void SPC7110_Decomp::init(running_machine &machine, UINT8 *ROM, UINT32 len, UINT32 mode, UINT32 offset, UINT32 index)
=======
void sns_rom_spc7110_device::SPC7110_Decomp::init(running_machine &machine, uint8_t *ROM, uint32_t len, uint32_t mode, uint32_t offset, uint32_t index)
>>>>>>> upstream/master
{
	m_decomp_mode = mode;
	m_decomp_offset = offset;

	m_decomp_buffer_rdoffset = 0;
	m_decomp_buffer_wroffset = 0;
	m_decomp_buffer_length   = 0;

	//reset context states
<<<<<<< HEAD
	for (int i = 0; i < 32; i++)
	{
		m_context[i].index  = 0;
		m_context[i].invert = 0;
=======
	for (auto & elem : m_context)
	{
		elem.index  = 0;
		elem.invert = 0;
>>>>>>> upstream/master
	}

	switch (m_decomp_mode)
	{
		case 0: mode0(1, ROM, len); break;
		case 1: mode1(1, ROM, len); break;
		case 2: mode2(1, ROM, len); break;
	}

	//decompress up to requested output data index
	while (index--)
	{
		read(ROM, len);
	}
}

<<<<<<< HEAD
UINT8 SPC7110_Decomp::read(UINT8 *ROM, UINT32 len)
{
	UINT8 data;
=======
uint8_t sns_rom_spc7110_device::SPC7110_Decomp::read(uint8_t *ROM, uint32_t len)
{
	uint8_t data;
>>>>>>> upstream/master

	if (m_decomp_buffer_length == 0)
	{
		//decompress at least (SPC7110_DECOMP_BUFFER_SIZE / 2) bytes to the buffer
		switch (m_decomp_mode)
		{
			case 0:
				mode0(0, ROM, len);
				break;

			case 1:
				mode1(0, ROM, len);
				break;

			case 2:
				mode2(0, ROM, len);
				break;

			default:
				return 0x00;
		}
	}

	data = m_decomp_buffer[m_decomp_buffer_rdoffset++];
	m_decomp_buffer_rdoffset &= SPC7110_DECOMP_BUFFER_SIZE - 1;
	m_decomp_buffer_length--;
	return data;
}

<<<<<<< HEAD
void SPC7110_Decomp::write(UINT8 data)
=======
void sns_rom_spc7110_device::SPC7110_Decomp::write(uint8_t data)
>>>>>>> upstream/master
{
	m_decomp_buffer[m_decomp_buffer_wroffset++] = data;
	m_decomp_buffer_wroffset &= SPC7110_DECOMP_BUFFER_SIZE - 1;
	m_decomp_buffer_length++;
}

<<<<<<< HEAD
UINT8 SPC7110_Decomp::dataread(UINT8 *ROM, UINT32 len)
{
	UINT32 size = len - 0x100000;
=======
uint8_t sns_rom_spc7110_device::SPC7110_Decomp::dataread(uint8_t *ROM, uint32_t len)
{
	uint32_t size = len - 0x100000;
>>>>>>> upstream/master
	while (m_decomp_offset >= size)
	{
		m_decomp_offset -= size;
	}
	return ROM[0x100000 + m_decomp_offset++];
}

<<<<<<< HEAD
void SPC7110_Decomp::mode0(UINT8 init, UINT8 *ROM, UINT32 len)
=======
void sns_rom_spc7110_device::SPC7110_Decomp::mode0(uint8_t init, uint8_t *ROM, uint32_t len)
>>>>>>> upstream/master
{
	if (init == 1)
	{
		m_m0_out = m_m0_inverts = m_m0_lps = 0;
		m_m0_span = 0xff;
		m_m0_val = dataread(ROM, len);
		m_m0_in = dataread(ROM, len);
		m_m0_in_count = 8;
		return;
	}

	while (m_decomp_buffer_length < (SPC7110_DECOMP_BUFFER_SIZE >> 1))
	{
		for (int bit = 0; bit < 8; bit++)
		{
			//get context
<<<<<<< HEAD
			UINT8 mask = (1 << (bit & 3)) - 1;
			UINT8 con = mask + ((m_m0_inverts & mask) ^ (m_m0_lps & mask));
			UINT32 prob, mps, flag_lps;
			UINT32 shift = 0;
=======
			uint8_t mask = (1 << (bit & 3)) - 1;
			uint8_t con = mask + ((m_m0_inverts & mask) ^ (m_m0_lps & mask));
			uint32_t prob, mps, flag_lps;
			uint32_t shift = 0;
>>>>>>> upstream/master
			if (bit > 3)
			{
				con += 15;
			}

			//get prob and mps
			prob = probability(con);
			mps = (((m_m0_out >> 15) & 1) ^ m_context[con].invert);

			//get bit
			if (m_m0_val <= m_m0_span - prob) //mps
			{
				m_m0_span = m_m0_span - prob;
				m_m0_out = (m_m0_out << 1) + mps;
				flag_lps = 0;
			}
			else //lps
			{
				m_m0_val = m_m0_val - (m_m0_span - (prob - 1));
				m_m0_span = prob - 1;
				m_m0_out = (m_m0_out << 1) + 1 - mps;
				flag_lps = 1;
			}

			//renormalize
			while (m_m0_span < 0x7f)
			{
				shift++;

				m_m0_span = (m_m0_span << 1) + 1;
				m_m0_val = (m_m0_val << 1) + (m_m0_in >> 7);

				m_m0_in <<= 1;
				if (--m_m0_in_count == 0)
				{
					m_m0_in = dataread(ROM, len);
					m_m0_in_count = 8;
				}
			}

			//update processing info
			m_m0_lps = (m_m0_lps << 1) + flag_lps;
			m_m0_inverts = (m_m0_inverts << 1) + m_context[con].invert;

			//update context state
			if (flag_lps & toggle_invert(con))
			{
				m_context[con].invert ^= 1;
			}
			if (flag_lps)
			{
				m_context[con].index = next_lps(con);
			}
			else if (shift)
			{
				m_context[con].index = next_mps(con);
			}
		}

		//save byte
		write(m_m0_out);
	}
}

<<<<<<< HEAD
void SPC7110_Decomp::mode1(UINT8 init, UINT8 *ROM, UINT32 len)
=======
void sns_rom_spc7110_device::SPC7110_Decomp::mode1(uint8_t init, uint8_t *ROM, uint32_t len)
>>>>>>> upstream/master
{
	if (init == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			m_m1_pixelorder[i] = i;
		}
		m_m1_out = m_m1_inverts = m_m1_lps = 0;
		m_m1_span = 0xff;
		m_m1_val = dataread(ROM, len);
		m_m1_in = dataread(ROM, len);
		m_m1_in_count = 8;
		return;
	}

	while (m_decomp_buffer_length < (SPC7110_DECOMP_BUFFER_SIZE >> 1))
	{
<<<<<<< HEAD
		UINT16 data;
		for (int pixel = 0; pixel < 8; pixel++)
		{
			//get first symbol context
			UINT32 a = ((m_m1_out >> (1 * 2)) & 3);
			UINT32 b = ((m_m1_out >> (7 * 2)) & 3);
			UINT32 c = ((m_m1_out >> (8 * 2)) & 3);
			UINT32 con = (a == b) ? (b != c) : (b == c) ? 2 : 4 - (a == c);

			//update pixel order
			UINT32 m, n;
=======
		uint16_t data;
		for (int pixel = 0; pixel < 8; pixel++)
		{
			//get first symbol context
			uint32_t a = ((m_m1_out >> (1 * 2)) & 3);
			uint32_t b = ((m_m1_out >> (7 * 2)) & 3);
			uint32_t c = ((m_m1_out >> (8 * 2)) & 3);
			uint32_t con = (a == b) ? (b != c) : (b == c) ? 2 : 4 - (a == c);

			//update pixel order
			uint32_t m, n;
>>>>>>> upstream/master
			for (m = 0; m < 4; m++)
			{
				if (m_m1_pixelorder[m] == a)
				{
					break;
				}
			}
			for (n = m; n > 0; n--)
			{
				m_m1_pixelorder[n] = m_m1_pixelorder[n - 1];
			}
			m_m1_pixelorder[0] = a;

			//calculate the real pixel order
			for (m = 0; m < 4; m++)
			{
				m_m1_realorder[m] = m_m1_pixelorder[m];
			}

			//rotate reference pixel c value to top
			for (m = 0; m < 4; m++)
			{
				if (m_m1_realorder[m] == c)
				{
					break;
				}
			}
			for (n = m; n > 0; n--)
			{
				m_m1_realorder[n] = m_m1_realorder[n - 1];
			}
			m_m1_realorder[0] = c;

			//rotate reference pixel b value to top
			for (m = 0; m < 4; m++)
			{
				if (m_m1_realorder[m] == b)
				{
					break;
				}
			}
			for (n = m; n > 0; n--)
			{
				m_m1_realorder[n] = m_m1_realorder[n - 1];
			}
			m_m1_realorder[0] = b;

			//rotate reference pixel a value to top
			for (m = 0; m < 4; m++)
			{
				if (m_m1_realorder[m] == a)
				{
					break;
				}
			}
			for (n = m; n > 0; n--)
			{
				m_m1_realorder[n] = m_m1_realorder[n - 1];
			}
			m_m1_realorder[0] = a;

			//get 2 symbols
			for (int bit = 0; bit < 2; bit++)
			{
				//get prob
<<<<<<< HEAD
				UINT32 prob = probability(con);
				UINT32 shift = 0;

				//get symbol
				UINT32 flag_lps;
=======
				uint32_t prob = probability(con);
				uint32_t shift = 0;

				//get symbol
				uint32_t flag_lps;
>>>>>>> upstream/master
				if (m_m1_val <= m_m1_span - prob) //mps
				{
					m_m1_span = m_m1_span - prob;
					flag_lps = 0;
				}
				else //lps
				{
					m_m1_val = m_m1_val - (m_m1_span - (prob - 1));
					m_m1_span = prob - 1;
					flag_lps = 1;
				}

				//renormalize
				while (m_m1_span < 0x7f)
				{
					shift++;

					m_m1_span = (m_m1_span << 1) + 1;
					m_m1_val = (m_m1_val << 1) + (m_m1_in >> 7);

					m_m1_in <<= 1;
					if (--m_m1_in_count == 0)
					{
						m_m1_in = dataread(ROM, len);
						m_m1_in_count = 8;
					}
				}

				//update processing info
				m_m1_lps = (m_m1_lps << 1) + flag_lps;
				m_m1_inverts = (m_m1_inverts << 1) + m_context[con].invert;

				//update context state
				if (flag_lps & toggle_invert(con))
				{
					m_context[con].invert ^= 1;
				}
				if (flag_lps)
				{
					m_context[con].index = next_lps(con);
				}
				else if (shift)
				{
					m_context[con].index = next_mps(con);
				}

				//get next context
				con = 5 + (con << 1) + ((m_m1_lps ^ m_m1_inverts) & 1);
			}

			//get pixel
			b = m_m1_realorder[(m_m1_lps ^ m_m1_inverts) & 3];
			m_m1_out = (m_m1_out << 2) + b;
		}

		//turn pixel data into bitplanes
		data = morton_2x8(m_m1_out);
		write(data >> 8);
		write(data >> 0);
	}
}

<<<<<<< HEAD
void SPC7110_Decomp::mode2(UINT8 init, UINT8 *ROM, UINT32 len)
=======
void sns_rom_spc7110_device::SPC7110_Decomp::mode2(uint8_t init, uint8_t *ROM, uint32_t len)
>>>>>>> upstream/master
{
	if (init == 1)
	{
		for (int i = 0; i < 16; i++)
		{
			m_m2_pixelorder[i] = i;
		}
		m_m2_buffer_index = 0;
		m_m2_out0 = m_m2_out1 = m_m2_inverts = m_m2_lps = 0;
		m_m2_span = 0xff;
		m_m2_val = dataread(ROM, len);
		m_m2_in = dataread(ROM, len);
		m_m2_in_count = 8;
		return;
	}

	while (m_decomp_buffer_length < (SPC7110_DECOMP_BUFFER_SIZE >> 1))
	{
<<<<<<< HEAD
		UINT32 data;
		for (int pixel = 0; pixel < 8; pixel++)
		{
			//get first symbol context
			UINT32 a = ((m_m2_out0 >> (0 * 4)) & 15);
			UINT32 b = ((m_m2_out0 >> (7 * 4)) & 15);
			UINT32 c = ((m_m2_out1 >> (0 * 4)) & 15);
			UINT32 con = 0;
			UINT32 refcon = (a == b) ? (b != c) : (b == c) ? 2 : 4 - (a == c);

			//update pixel order
			UINT32 m, n;
=======
		uint32_t data;
		for (int pixel = 0; pixel < 8; pixel++)
		{
			//get first symbol context
			uint32_t a = ((m_m2_out0 >> (0 * 4)) & 15);
			uint32_t b = ((m_m2_out0 >> (7 * 4)) & 15);
			uint32_t c = ((m_m2_out1 >> (0 * 4)) & 15);
			uint32_t con = 0;
			uint32_t refcon = (a == b) ? (b != c) : (b == c) ? 2 : 4 - (a == c);

			//update pixel order
			uint32_t m, n;
>>>>>>> upstream/master
			for (m = 0; m < 16; m++)
			{
				if (m_m2_pixelorder[m] == a)
				{
					break;
				}
			}
			for (n = m; n >  0; n--)
			{
				m_m2_pixelorder[n] = m_m2_pixelorder[n - 1];
			}
			m_m2_pixelorder[0] = a;

			//calculate the real pixel order
			for (m = 0; m < 16; m++)
			{
				m_m2_realorder[m] = m_m2_pixelorder[m];
			}

			//rotate reference pixel c value to top
			for (m = 0; m < 16; m++)
			{
				if (m_m2_realorder[m] == c)
				{
					break;
				}
			}
			for (n = m; n >  0; n--)
			{
				m_m2_realorder[n] = m_m2_realorder[n - 1];
			}
			m_m2_realorder[0] = c;

			//rotate reference pixel b value to top
			for (m = 0; m < 16; m++)
			{
				if (m_m2_realorder[m] == b)
				{
					break;
				}
			}
			for (n = m; n >  0; n--)
			{
				m_m2_realorder[n] = m_m2_realorder[n - 1];
			}
			m_m2_realorder[0] = b;

			//rotate reference pixel a value to top
			for (m = 0; m < 16; m++)
			{
				if (m_m2_realorder[m] == a)
				{
					break;
				}
			}
			for (n = m; n >  0; n--)
			{
				m_m2_realorder[n] = m_m2_realorder[n - 1];
			}
			m_m2_realorder[0] = a;

			//get 4 symbols
			for (int bit = 0; bit < 4; bit++)
			{
<<<<<<< HEAD
				UINT32 invertbit, shift;

				//get prob
				UINT32 prob = probability(con);

				//get symbol
				UINT32 flag_lps;
=======
				uint32_t invertbit, shift;

				//get prob
				uint32_t prob = probability(con);

				//get symbol
				uint32_t flag_lps;
>>>>>>> upstream/master
				if (m_m2_val <= m_m2_span - prob) //mps
				{
					m_m2_span = m_m2_span - prob;
					flag_lps = 0;
				}
				else //lps
				{
					m_m2_val = m_m2_val - (m_m2_span - (prob - 1));
					m_m2_span = prob - 1;
					flag_lps = 1;
				}

				//renormalize
				shift = 0;
				while (m_m2_span < 0x7f)
				{
					shift++;

					m_m2_span = (m_m2_span << 1) + 1;
					m_m2_val = (m_m2_val << 1) + (m_m2_in >> 7);

					m_m2_in <<= 1;
					if (--m_m2_in_count == 0)
					{
						m_m2_in = dataread(ROM, len);
						m_m2_in_count = 8;
					}
				}

				//update processing info
				m_m2_lps = (m_m2_lps << 1) + flag_lps;
				invertbit = m_context[con].invert;
				m_m2_inverts = (m_m2_inverts << 1) + invertbit;

				//update context state
				if (flag_lps & toggle_invert(con))
				{
					m_context[con].invert ^= 1;
				}
				if (flag_lps)
				{
					m_context[con].index = next_lps(con);
				}
				else if (shift)
				{
					m_context[con].index = next_mps(con);
				}

				//get next context
				con = spc7110_mode2_context_table[con][flag_lps ^ invertbit] + (con == 1 ? refcon : 0);
			}

			//get pixel
			b = m_m2_realorder[(m_m2_lps ^ m_m2_inverts) & 0x0f];
			m_m2_out1 = (m_m2_out1 << 4) + ((m_m2_out0 >> 28) & 0x0f);
			m_m2_out0 = (m_m2_out0 << 4) + b;
		}

		//convert pixel data into bitplanes
		data = morton_4x8(m_m2_out0);
		write(data >> 24);
		write(data >> 16);
		m_m2_bitplanebuffer[m_m2_buffer_index++] = data >> 8;
		m_m2_bitplanebuffer[m_m2_buffer_index++] = data >> 0;

		if (m_m2_buffer_index == 16)
		{
<<<<<<< HEAD
			for (int i = 0; i < 16; i++)
			{
				write(m_m2_bitplanebuffer[i]);
=======
			for (auto & elem : m_m2_bitplanebuffer)
			{
				write(elem);
>>>>>>> upstream/master
			}
			m_m2_buffer_index = 0;
		}
	}
}

<<<<<<< HEAD
UINT8 SPC7110_Decomp::probability(UINT32 n)
=======
uint8_t sns_rom_spc7110_device::SPC7110_Decomp::probability(uint32_t n)
>>>>>>> upstream/master
{
	return spc7110_evolution_table[m_context[n].index][0];
}

<<<<<<< HEAD
UINT8 SPC7110_Decomp::next_lps(UINT32 n)
=======
uint8_t sns_rom_spc7110_device::SPC7110_Decomp::next_lps(uint32_t n)
>>>>>>> upstream/master
{
	return spc7110_evolution_table[m_context[n].index][1];
}

<<<<<<< HEAD
UINT8 SPC7110_Decomp::next_mps(UINT32 n)
=======
uint8_t sns_rom_spc7110_device::SPC7110_Decomp::next_mps(uint32_t n)
>>>>>>> upstream/master
{
	return spc7110_evolution_table[m_context[n].index][2];
}

<<<<<<< HEAD
UINT8 SPC7110_Decomp::toggle_invert(UINT32 n)
=======
uint8_t sns_rom_spc7110_device::SPC7110_Decomp::toggle_invert(uint32_t n)
>>>>>>> upstream/master
{
	return spc7110_evolution_table[m_context[n].index][3];
}

<<<<<<< HEAD
UINT32 SPC7110_Decomp::morton_2x8(UINT32 data)
=======
uint32_t sns_rom_spc7110_device::SPC7110_Decomp::morton_2x8(uint32_t data)
>>>>>>> upstream/master
{
	//reverse morton lookup: de-interleave two 8-bit values
	//15, 13, 11,  9,  7,  5,  3,  1 -> 15- 8
	//14, 12, 10,  8,  6,  4,  2,  0 ->  7- 0
	return m_morton16[0][(data >>  0) & 255] + m_morton16[1][(data >>  8) & 255];
}

<<<<<<< HEAD
UINT32 SPC7110_Decomp::morton_4x8(UINT32 data)
=======
uint32_t sns_rom_spc7110_device::SPC7110_Decomp::morton_4x8(uint32_t data)
>>>>>>> upstream/master
{
	//reverse morton lookup: de-interleave four 8-bit values
	//31, 27, 23, 19, 15, 11,  7,  3 -> 31-24
	//30, 26, 22, 18, 14, 10,  6,  2 -> 23-16
	//29, 25, 21, 17, 13,  9,  5,  1 -> 15- 8
	//28, 24, 20, 16, 12,  8,  4,  0 ->  7- 0
	return m_morton32[0][(data >>  0) & 255] + m_morton32[1][(data >>  8) & 255]
	+ m_morton32[2][(data >> 16) & 255] + m_morton32[3][(data >> 24) & 255];
}


<<<<<<< HEAD
static const UINT32 spc7110_months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

UINT32 sns_rom_spc7110_device::spc7110_datarom_addr(UINT32 addr, UINT32 rom_len)
{
	UINT32 size = rom_len - 0x100000;
=======
static const uint32_t spc7110_months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

uint32_t sns_rom_spc7110_device::spc7110_datarom_addr(uint32_t addr, uint32_t rom_len)
{
	uint32_t size = rom_len - 0x100000;
>>>>>>> upstream/master
	while (addr >= size)
	{
		addr -= size;
	}
	return addr + 0x100000;
}

<<<<<<< HEAD
UINT32 sns_rom_spc7110_device::spc7110_data_pointer(void)
=======
uint32_t sns_rom_spc7110_device::spc7110_data_pointer(void)
>>>>>>> upstream/master
{
	return m_r4811 + (m_r4812 << 8) + (m_r4813 << 16);
}

<<<<<<< HEAD
UINT32 sns_rom_spc7110_device::spc7110_data_adjust(void)
=======
uint32_t sns_rom_spc7110_device::spc7110_data_adjust(void)
>>>>>>> upstream/master
{
	return m_r4814 + (m_r4815 << 8);
}

<<<<<<< HEAD
UINT32 sns_rom_spc7110_device::spc7110_data_increment(void)
=======
uint32_t sns_rom_spc7110_device::spc7110_data_increment(void)
>>>>>>> upstream/master
{
	return m_r4816 + (m_r4817 << 8);
}

<<<<<<< HEAD
void sns_rom_spc7110_device::spc7110_set_data_pointer(UINT32 addr)
=======
void sns_rom_spc7110_device::spc7110_set_data_pointer(uint32_t addr)
>>>>>>> upstream/master
{
	m_r4811 = addr;
	m_r4812 = addr >> 8;
	m_r4813 = addr >> 16;
}

<<<<<<< HEAD
void sns_rom_spc7110_device::spc7110_set_data_adjust(UINT32 addr)
=======
void sns_rom_spc7110_device::spc7110_set_data_adjust(uint32_t addr)
>>>>>>> upstream/master
{
	m_r4814 = addr;
	m_r4815 = addr >> 8;
}

// FIXME: SPC7110 RTC is capable of rounding/adding/zero-ing seconds, so
// we should probably keep track internally of the time rather than updating
// to the system time at each call with a "offset" tracking as we do now...
// (and indeed current code fails to pass Tengai Makyou Zero tests)
<<<<<<< HEAD
void sns_rom_spc7110_device::spc7110_update_time(UINT8 offset)
{
	system_time curtime;
	machine().current_datetime(curtime);
	INT64 diff = curtime.time - m_rtc_basetime.time - offset;
//  printf("diff %llx\n", diff);
	bool update = TRUE;
=======
void sns_rom_spc7110_device::spc7110_update_time(uint8_t offset)
{
	system_time curtime;
	machine().current_datetime(curtime);
	int64_t diff = curtime.time - m_rtc_basetime.time - offset;
//  printf("diff %llx\n", diff);
	bool update = true;
>>>>>>> upstream/master

	// TEST: can we go beyond 24hrs of rounding?!? I doubt it will ever go beyond 3600, but I could be wrong...
	assert(diff < 86400);

	/* do not update if CR0 or CR2 timer disable flags are set */
	if ((m_rtc_ram[13] & 0x01) || (m_rtc_ram[15] & 0x03))
<<<<<<< HEAD
		update = FALSE;
=======
		update = false;
>>>>>>> upstream/master

	if (update && diff > 0)
	{
		/* update time with offset, assuming offset < 3600s */
<<<<<<< HEAD
		UINT32 second = m_rtc_ram[0] + m_rtc_ram[1] * 10;
		UINT8 minute = m_rtc_ram[2] + m_rtc_ram[3] * 10;
		UINT8 hour = m_rtc_ram[4] + m_rtc_ram[5] * 10;
		UINT8 day = m_rtc_ram[6] + m_rtc_ram[7] * 10;
		UINT8 month = m_rtc_ram[8] + m_rtc_ram[9] * 10;
		UINT8 year = m_rtc_ram[10] + m_rtc_ram[11] * 10;
		UINT8 weekday = m_rtc_ram[12];
=======
		uint32_t second = m_rtc_ram[0] + m_rtc_ram[1] * 10;
		uint8_t minute = m_rtc_ram[2] + m_rtc_ram[3] * 10;
		uint8_t hour = m_rtc_ram[4] + m_rtc_ram[5] * 10;
		uint8_t day = m_rtc_ram[6] + m_rtc_ram[7] * 10;
		uint8_t month = m_rtc_ram[8] + m_rtc_ram[9] * 10;
		uint8_t year = m_rtc_ram[10] + m_rtc_ram[11] * 10;
		uint8_t weekday = m_rtc_ram[12];
>>>>>>> upstream/master
		day--;
		month--;
		year += (year >= 90) ? 1900 : 2000;

<<<<<<< HEAD
		second += (UINT32)diff;
=======
		second += (uint32_t)diff;
>>>>>>> upstream/master
		while (second >= 60)
		{
			second -= 60;
			minute++;

			// are we below 60 minutes?
			if (minute < 60)
				continue;
			// otherwise we have to increase hour!
			minute = 0;
			hour++;

			// are we below 24 hours?
			if (hour < 24)
				continue;
			// otherwise we have to increase day!
			hour = 0;
			day++;

			weekday = (weekday + 1) % 7;

<<<<<<< HEAD
			UINT8 days = spc7110_months[month % 12];
			// check for feb 29th
			if (days == 28)
			{
				bool leap = FALSE;
				if ((year % 4) == 0)
				{
					if(year % 100 || !(year % 400))
						leap = TRUE;
=======
			uint8_t days = spc7110_months[month % 12];
			// check for feb 29th
			if (days == 28)
			{
				bool leap = false;
				if ((year % 4) == 0)
				{
					if(year % 100 || !(year % 400))
						leap = true;
>>>>>>> upstream/master
				}
				if (leap)
					days++;
			}

			// are we below end of month?
			if (day < days)
				continue;
			// otherwise we have to increase month!
			day = 0;
			month++;

			// are we below end of year?
			if (month < 12)
				continue;
			// otherwise we have to increase year!
			month = 0;
			year++;
		}

		day++;
		month++;
		year %= 100;

		m_rtc_ram[0] = second % 10;
		m_rtc_ram[1] = second / 10;
		m_rtc_ram[2] = minute % 10;
		m_rtc_ram[3] = minute / 10;
		m_rtc_ram[4] = hour % 10;
		m_rtc_ram[5] = hour / 10;
		m_rtc_ram[6] = day % 10;
		m_rtc_ram[7] = day / 10;
		m_rtc_ram[8] = month % 10;
		m_rtc_ram[9] = month / 10;
		m_rtc_ram[10] = year % 10;
		m_rtc_ram[11] = (year / 10) % 10;
		m_rtc_ram[12] = weekday % 7;
		m_rtc_basetime = curtime;
	}
}

READ8_MEMBER(sns_rom_spc7110_device::chip_read)
{
<<<<<<< HEAD
	UINT8 *ROM = get_rom_base();
	UINT32 len = get_rom_size();
	UINT16 addr = offset & 0xffff;
=======
	uint8_t *ROM = get_rom_base();
	uint32_t len = get_rom_size();
	uint16_t addr = offset & 0xffff;
>>>>>>> upstream/master

	switch (addr)
	{
		//==================
		//decompression unit
		//==================

		case 0x4800:
		{
<<<<<<< HEAD
			UINT16 counter = (m_r4809 + (m_r480a << 8));
=======
			uint16_t counter = (m_r4809 + (m_r480a << 8));
>>>>>>> upstream/master
			counter--;
			m_r4809 = counter;
			m_r480a = counter >> 8;
			return m_decomp->read(ROM, len);
		}
		case 0x4801: return m_r4801;
		case 0x4802: return m_r4802;
		case 0x4803: return m_r4803;
		case 0x4804: return m_r4804;
		case 0x4805: return m_r4805;
		case 0x4806: return m_r4806;
		case 0x4807: return m_r4807;
		case 0x4808: return m_r4808;
		case 0x4809: return m_r4809;
		case 0x480a: return m_r480a;
		case 0x480b: return m_r480b;
		case 0x480c:
		{
<<<<<<< HEAD
			UINT8 status = m_r480c;
=======
			uint8_t status = m_r480c;
>>>>>>> upstream/master
			m_r480c &= 0x7f;
			return status;
		}

		//==============
		//data port unit
		//==============

		case 0x4810:
		{
<<<<<<< HEAD
			UINT8 data;
			UINT32 address, adjust, adjustaddr;
=======
			uint8_t data;
			uint32_t address, adjust, adjustaddr;
>>>>>>> upstream/master

			if (m_r481x != 0x07) return 0x00;

			address = spc7110_data_pointer();
			adjust = spc7110_data_adjust();
			if (m_r4818 & 8)
			{
<<<<<<< HEAD
				adjust = (INT16)adjust;  //16-bit sign extend
=======
				adjust = (int16_t)adjust;  //16-bit sign extend
>>>>>>> upstream/master
			}

			adjustaddr = address;
			if (m_r4818 & 2)
			{
				adjustaddr += adjust;
				spc7110_set_data_adjust(adjust + 1);
			}

			data = ROM[spc7110_datarom_addr(adjustaddr, len)];
			if (!(m_r4818 & 2))
			{
<<<<<<< HEAD
				UINT32 increment = (m_r4818 & 1) ? spc7110_data_increment() : 1;
				if (m_r4818 & 4)
				{
					increment = (INT16)increment;  //16-bit sign extend
=======
				uint32_t increment = (m_r4818 & 1) ? spc7110_data_increment() : 1;
				if (m_r4818 & 4)
				{
					increment = (int16_t)increment;  //16-bit sign extend
>>>>>>> upstream/master
				}

				if ((m_r4818 & 16) == 0)
				{
					spc7110_set_data_pointer(address + increment);
				}
				else
				{
					spc7110_set_data_adjust(adjust + increment);
				}
			}

			return data;
		}
		case 0x4811: return m_r4811;
		case 0x4812: return m_r4812;
		case 0x4813: return m_r4813;
		case 0x4814: return m_r4814;
		case 0x4815: return m_r4815;
		case 0x4816: return m_r4816;
		case 0x4817: return m_r4817;
		case 0x4818: return m_r4818;
		case 0x481a:
		{
<<<<<<< HEAD
			UINT8 data;
			UINT32 address, adjust;
=======
			uint8_t data;
			uint32_t address, adjust;
>>>>>>> upstream/master
			if (m_r481x != 0x07)
			{
				return 0x00;
			}

			address = spc7110_data_pointer();
			adjust = spc7110_data_adjust();
			if (m_r4818 & 8)
			{
<<<<<<< HEAD
				adjust = (INT16)adjust;  //16-bit sign extend
=======
				adjust = (int16_t)adjust;  //16-bit sign extend
>>>>>>> upstream/master
			}

			data = ROM[spc7110_datarom_addr(address + adjust, len)];
			if ((m_r4818 & 0x60) == 0x60)
			{
				if ((m_r4818 & 16) == 0)
				{
					spc7110_set_data_pointer(address + adjust);
				}
				else
				{
					spc7110_set_data_adjust(adjust + adjust);
				}
			}

			return data;
		}

		//=========
		//math unit
		//=========

		case 0x4820: return m_r4820;
		case 0x4821: return m_r4821;
		case 0x4822: return m_r4822;
		case 0x4823: return m_r4823;
		case 0x4824: return m_r4824;
		case 0x4825: return m_r4825;
		case 0x4826: return m_r4826;
		case 0x4827: return m_r4827;
		case 0x4828: return m_r4828;
		case 0x4829: return m_r4829;
		case 0x482a: return m_r482a;
		case 0x482b: return m_r482b;
		case 0x482c: return m_r482c;
		case 0x482d: return m_r482d;
		case 0x482e: return m_r482e;
		case 0x482f:
		{
<<<<<<< HEAD
			UINT8 status = m_r482f;
=======
			uint8_t status = m_r482f;
>>>>>>> upstream/master
			m_r482f &= 0x7f;
			return status;
		}

		//===================
		//memory mapping unit
		//===================

		case 0x4830: return m_r4830;
		case 0x4831: return m_r4831;
		case 0x4832: return m_r4832;
		case 0x4833: return m_r4833;
		case 0x4834: return m_r4834;

		//====================
		//real-time clock unit
		//====================
		case 0x4840: return m_r4840;
		case 0x4841:
		{
<<<<<<< HEAD
			UINT8 data = 0;
=======
			uint8_t data;
>>>>>>> upstream/master
			if (m_rtc_state == RTCS_Inactive || m_rtc_state == RTCS_ModeSelect)
				return 0x00;

			m_r4842 = 0x80;
			data = m_rtc_ram[m_rtc_index];
			m_rtc_index = (m_rtc_index + 1) & 15;
			return data;
		}
		case 0x4842:
		{
<<<<<<< HEAD
			UINT8 status = m_r4842;
=======
			uint8_t status = m_r4842;
>>>>>>> upstream/master
			m_r4842 &= 0x7f;
			return status;
		}
	}

	return 0xff;
}

WRITE8_MEMBER(sns_rom_spc7110_device::chip_write)
{
<<<<<<< HEAD
	UINT8 *ROM = get_rom_base();
	UINT32 len = get_rom_size();
	UINT16 addr = offset & 0xffff;
=======
	uint8_t *ROM = get_rom_base();
	uint32_t len = get_rom_size();
	uint16_t addr = offset & 0xffff;
>>>>>>> upstream/master

	switch (addr)
	{
		//==================
		//decompression unit
		//==================

		case 0x4801: m_r4801 = data; break;
		case 0x4802: m_r4802 = data; break;
		case 0x4803: m_r4803 = data; break;
		case 0x4804: m_r4804 = data; break;
		case 0x4805: m_r4805 = data; break;
		case 0x4806:
		{
<<<<<<< HEAD
			UINT32 table, index, address, mode, offset;
=======
			uint32_t table, index, address, mode, offset;
>>>>>>> upstream/master
			m_r4806 = data;

			table   = (m_r4801 + (m_r4802 << 8) + (m_r4803 << 16));
			index   = (m_r4804 << 2);
			//length  = (m_r4809 + (m_r480a << 8));
			address = spc7110_datarom_addr(table + index, len);
			mode    = (ROM[address + 0]);
			offset  = (ROM[address + 1] << 16)
			+ (ROM[address + 2] <<  8)
			+ (ROM[address + 3] <<  0);

			m_decomp->init(machine(), ROM, len, mode, offset, (m_r4805 + (m_r4806 << 8)) << mode);
			m_r480c = 0x80;
		}
			break;

		case 0x4807: m_r4807 = data; break;
		case 0x4808: m_r4808 = data; break;
		case 0x4809: m_r4809 = data; break;
		case 0x480a: m_r480a = data; break;
		case 0x480b: m_r480b = data; break;

		//==============
		//data port unit
		//==============

		case 0x4811: m_r4811 = data; m_r481x |= 0x01; break;
		case 0x4812: m_r4812 = data; m_r481x |= 0x02; break;
		case 0x4813: m_r4813 = data; m_r481x |= 0x04; break;
		case 0x4814:
		{
			m_r4814 = data;
			m_r4814_latch = 1;
			if (!m_r4815_latch)
			{
				break;
			}
			if (!(m_r4818 & 2))
			{
				break;
			}
			if (m_r4818 & 0x10)
			{
				break;
			}

			if ((m_r4818 & 0x60) == 0x20)
			{
<<<<<<< HEAD
				UINT32 increment = spc7110_data_adjust() & 0xff;
				if (m_r4818 & 8)
				{
					increment = (INT8)increment;  //8-bit sign extend
=======
				uint32_t increment = spc7110_data_adjust() & 0xff;
				if (m_r4818 & 8)
				{
					increment = (int8_t)increment;  //8-bit sign extend
>>>>>>> upstream/master
				}
				spc7110_set_data_pointer(spc7110_data_pointer() + increment);
			}
			else if ((m_r4818 & 0x60) == 0x40)
			{
<<<<<<< HEAD
				UINT32 increment = spc7110_data_adjust();
				if (m_r4818 & 8)
				{
					increment = (INT16)increment;  //16-bit sign extend
=======
				uint32_t increment = spc7110_data_adjust();
				if (m_r4818 & 8)
				{
					increment = (int16_t)increment;  //16-bit sign extend
>>>>>>> upstream/master
				}
				spc7110_set_data_pointer(spc7110_data_pointer() + increment);
			}
			break;
		}

		case 0x4815:
		{
			m_r4815 = data;
			m_r4815_latch = 1;
			if (!m_r4814_latch)
			{
				break;
			}
			if (!(m_r4818 & 2))
			{
				break;
			}
			if (m_r4818 & 0x10)
			{
				break;
			}

			if ((m_r4818 & 0x60) == 0x20)
			{
<<<<<<< HEAD
				UINT32 increment = spc7110_data_adjust() & 0xff;
				if (m_r4818 & 8)
				{
					increment = (INT8)increment;  //8-bit sign extend
=======
				uint32_t increment = spc7110_data_adjust() & 0xff;
				if (m_r4818 & 8)
				{
					increment = (int8_t)increment;  //8-bit sign extend
>>>>>>> upstream/master
				}
				spc7110_set_data_pointer(spc7110_data_pointer() + increment);
			}
			else if ((m_r4818 & 0x60) == 0x40)
			{
<<<<<<< HEAD
				UINT32 increment = spc7110_data_adjust();
				if (m_r4818 & 8)
				{
					increment = (INT16)increment;  //16-bit sign extend
=======
				uint32_t increment = spc7110_data_adjust();
				if (m_r4818 & 8)
				{
					increment = (int16_t)increment;  //16-bit sign extend
>>>>>>> upstream/master
				}
				spc7110_set_data_pointer(spc7110_data_pointer() + increment);
			}
			break;
		}

		case 0x4816: m_r4816 = data; break;
		case 0x4817: m_r4817 = data; break;
		case 0x4818:
		{
			if (m_r481x != 0x07)
				break;

			m_r4818 = data;
			m_r4814_latch = m_r4815_latch = 0;
			break;
		}

		//=========
		//math unit
		//=========

		case 0x4820: m_r4820 = data; break;
		case 0x4821: m_r4821 = data; break;
		case 0x4822: m_r4822 = data; break;
		case 0x4823: m_r4823 = data; break;
		case 0x4824: m_r4824 = data; break;
		case 0x4825:
		{
			m_r4825 = data;

			if (m_r482e & 1)
			{
				//signed 16-bit x 16-bit multiplication
<<<<<<< HEAD
				INT16 r0 = (INT16)(m_r4824 + (m_r4825 << 8));
				INT16 r1 = (INT16)(m_r4820 + (m_r4821 << 8));

				INT32 result = r0 * r1;
=======
				int16_t r0 = (int16_t)(m_r4824 + (m_r4825 << 8));
				int16_t r1 = (int16_t)(m_r4820 + (m_r4821 << 8));

				int32_t result = r0 * r1;
>>>>>>> upstream/master
				m_r4828 = result;
				m_r4829 = result >> 8;
				m_r482a = result >> 16;
				m_r482b = result >> 24;
			}
			else
			{
				//unsigned 16-bit x 16-bit multiplication
<<<<<<< HEAD
				UINT16 r0 = (UINT16)(m_r4824 + (m_r4825 << 8));
				UINT16 r1 = (UINT16)(m_r4820 + (m_r4821 << 8));

				UINT32 result = r0 * r1;
=======
				uint16_t r0 = (uint16_t)(m_r4824 + (m_r4825 << 8));
				uint16_t r1 = (uint16_t)(m_r4820 + (m_r4821 << 8));

				uint32_t result = r0 * r1;
>>>>>>> upstream/master
				m_r4828 = result;
				m_r4829 = result >> 8;
				m_r482a = result >> 16;
				m_r482b = result >> 24;
			}

			m_r482f = 0x80;
			break;
		}

		case 0x4826: m_r4826 = data; break;
		case 0x4827:
		{
			m_r4827 = data;

			if (m_r482e & 1)
			{
				//signed 32-bit x 16-bit division
<<<<<<< HEAD
				INT32 dividend = (INT32)(m_r4820 + (m_r4821 << 8) + (m_r4822 << 16) + (m_r4823 << 24));
				INT16 divisor  = (INT16)(m_r4826 + (m_r4827 << 8));

				INT32 quotient;
				INT16 remainder;

				if (divisor)
				{
					quotient  = (INT32)(dividend / divisor);
					remainder = (INT32)(dividend % divisor);
=======
				int32_t dividend = (int32_t)(m_r4820 + (m_r4821 << 8) + (m_r4822 << 16) + (m_r4823 << 24));
				int16_t divisor  = (int16_t)(m_r4826 + (m_r4827 << 8));

				int32_t quotient;
				int16_t remainder;

				if (divisor)
				{
					quotient  = (int32_t)(dividend / divisor);
					remainder = (int32_t)(dividend % divisor);
>>>>>>> upstream/master
				}
				else
				{
					//illegal division by zero
					quotient  = 0;
					remainder = dividend & 0xffff;
				}

				m_r4828 = quotient;
				m_r4829 = quotient >> 8;
				m_r482a = quotient >> 16;
				m_r482b = quotient >> 24;

				m_r482c = remainder;
				m_r482d = remainder >> 8;
			}
			else
			{
				//unsigned 32-bit x 16-bit division
<<<<<<< HEAD
				UINT32 dividend = (UINT32)(m_r4820 + (m_r4821 << 8) + (m_r4822 << 16) + (m_r4823 << 24));
				UINT16 divisor  = (UINT16)(m_r4826 + (m_r4827 << 8));

				UINT32 quotient;
				UINT16 remainder;

				if (divisor)
				{
					quotient  = (UINT32)(dividend / divisor);
					remainder = (UINT16)(dividend % divisor);
=======
				uint32_t dividend = (uint32_t)(m_r4820 + (m_r4821 << 8) + (m_r4822 << 16) + (m_r4823 << 24));
				uint16_t divisor  = (uint16_t)(m_r4826 + (m_r4827 << 8));

				uint32_t quotient;
				uint16_t remainder;

				if (divisor)
				{
					quotient  = (uint32_t)(dividend / divisor);
					remainder = (uint16_t)(dividend % divisor);
>>>>>>> upstream/master
				}
				else
				{
					//illegal division by zero
					quotient  = 0;
					remainder = dividend & 0xffff;
				}

				m_r4828 = quotient;
				m_r4829 = quotient >> 8;
				m_r482a = quotient >> 16;
				m_r482b = quotient >> 24;

				m_r482c = remainder;
				m_r482d = remainder >> 8;
			}

			m_r482f = 0x80;
			break;
		}

		case 0x482e:
		{
			//reset math unit
			m_r4820 = m_r4821 = m_r4822 = m_r4823 = 0;
			m_r4824 = m_r4825 = m_r4826 = m_r4827 = 0;
			m_r4828 = m_r4829 = m_r482a = m_r482b = 0;
			m_r482c = m_r482d = 0;

			m_r482e = data;
			break;
		}

		//===================
		//memory mapping unit
		//===================

		case 0x4830: m_r4830 = data; break;

		case 0x4831:
		{
			m_r4831 = data;
			m_dx_offset = spc7110_datarom_addr(data * 0x100000, len);
			break;
		}

		case 0x4832:
		{
			m_r4832 = data;
			m_ex_offset = spc7110_datarom_addr(data * 0x100000, len);
			break;
		}

		case 0x4833:
		{
			m_r4833 = data;
			m_fx_offset = spc7110_datarom_addr(data * 0x100000, len);
			break;
		}

		case 0x4834: m_r4834 = data; break;

		//====================
		//real-time clock unit
		//====================

		case 0x4840:
		{
			m_r4840 = data;

			if (!(m_r4840 & 1))
			{
				//disable RTC
				m_rtc_state = RTCS_Inactive;
				spc7110_update_time(0);
			}
			else
			{
				//enable RTC
				m_r4842 = 0x80;
				m_rtc_state = RTCS_ModeSelect;
			}
		}
			break;

		case 0x4841:
		{
			m_r4841 = data;

			switch (m_rtc_state)
			{
				case RTCS_ModeSelect:
					if (data == RTCM_Linear || data == RTCM_Indexed)
					{
						m_r4842 = 0x80;
						m_rtc_state = RTCS_IndexSelect;
						m_rtc_mode = (RTC_Mode)data;
						m_rtc_index = 0;
					}
					break;

				case RTCS_IndexSelect:
					m_r4842 = 0x80;
					m_rtc_index = data & 15;
					if (m_rtc_mode == RTCM_Linear)
						m_rtc_state = RTCS_Write;
					break;

				case RTCS_Write:
					m_r4842 = 0x80;

					//control register 0
					if (m_rtc_index == 13)
					{
						//increment second counter
						if (data & 2)
							spc7110_update_time(1);

						//round minute counter
						if (data & 8)
						{
							spc7110_update_time(0);

<<<<<<< HEAD
							UINT8 second = m_rtc_ram[0] + m_rtc_ram[1] * 10;
=======
							uint8_t second = m_rtc_ram[0] + m_rtc_ram[1] * 10;
>>>>>>> upstream/master
							//clear seconds
							m_rtc_ram[0] = 0;
							m_rtc_ram[1] = 0;

							if (second >= 30)
								spc7110_update_time(60);
						}
					}

					//control register 2
					if (m_rtc_index == 15)
					{
						//disable timer and clear second counter
						if ((data & 1) && !(m_rtc_ram[15]  & 1))
						{
							spc7110_update_time(0);

							//clear seconds
							m_rtc_ram[0] = 0;
							m_rtc_ram[1] = 0;
						}

						//disable timer
						if ((data & 2) && !(m_rtc_ram[15] & 2))
							spc7110_update_time(0);
					}

					m_rtc_ram[m_rtc_index] = data & 15;
					m_rtc_index = (m_rtc_index + 1) & 15;
					break;
			}
		}
			break;
	}
}

READ8_MEMBER(sns_rom_spc7110_device::read_l)
{
	if (offset < 0x400000)
		return m_rom[rom_bank_map[offset / 0x8000] * 0x8000 + (offset & 0x7fff)];

	return 0xff;
}

READ8_MEMBER(sns_rom_spc7110_device::read_h)
{
<<<<<<< HEAD
	UINT16 address = offset & 0xfffff;
=======
	uint16_t address = offset & 0xfffff;
>>>>>>> upstream/master

	if (offset < 0x400000)
		return m_rom[rom_bank_map[offset / 0x8000] * 0x8000 + (offset & 0x7fff)];
	else
	{
		switch (offset & 0x300000)
		{
			case 0x000000:
				return m_rom[rom_bank_map[(offset - 0x400000) / 0x8000] * 0x8000 + (offset & 0x7fff)];
			case 0x100000:
				return m_rom[m_dx_offset + address];
			case 0x200000:
				return m_rom[m_ex_offset + address];
			case 0x300000:
				return m_rom[m_fx_offset + address];
			default:
				break;
		}
	}

	return 0xff;
}


READ8_MEMBER( sns_rom_spc7110_device::read_ram )
{
	return m_nvram[offset & 0x1fff];
}

WRITE8_MEMBER( sns_rom_spc7110_device::write_ram )
{
	m_nvram[offset & 0x1fff] = data;
}
