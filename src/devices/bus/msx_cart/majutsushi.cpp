// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
#include "emu.h"
#include "majutsushi.h"

<<<<<<< HEAD
const device_type MSX_CART_MAJUTSUSHI = &device_creator<msx_cart_majutsushi>;


msx_cart_majutsushi::msx_cart_majutsushi(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MSX_CART_MAJUTSUSHI, "MSX Cartridge - Majutsushi", tag, owner, clock, "msx_cart_majutsushi", __FILE__)
	, msx_cart_interface(mconfig, *this)
	, m_dac(*this, "dac")
{
	for (int i = 0; i < 4; i++)
	{
		m_selected_bank[i] = 0;
	}
	for (int i = 0; i < 8; i++)
	{
		m_bank_base[i] = NULL;
=======
#include "sound/volt_reg.h"
#include "speaker.h"


DEFINE_DEVICE_TYPE(MSX_CART_MAJUTSUSHI, msx_cart_majutsushi_device, "msx_cart_majutsushi", "MSX Cartridge - Majutsushi")


msx_cart_majutsushi_device::msx_cart_majutsushi_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MSX_CART_MAJUTSUSHI, tag, owner, clock)
	, msx_cart_interface(mconfig, *this)
	, m_dac(*this, "dac")
{
	for (auto & elem : m_selected_bank)
	{
		elem = 0;
	}
	for (auto & elem : m_bank_base)
	{
		elem = nullptr;
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
static MACHINE_CONFIG_FRAGMENT( majutsushi )
	// This is actually incorrect. The sound output is passed back into the MSX machine where it is mixed internally and output through the system 'speaker'.
	MCFG_SPEAKER_STANDARD_MONO("mono")
	MCFG_SOUND_ADD("dac", DAC, 0)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.10)
MACHINE_CONFIG_END


machine_config_constructor msx_cart_majutsushi::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( majutsushi );
}


void msx_cart_majutsushi::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_majutsushi::restore_banks), this));
}


void msx_cart_majutsushi::restore_banks()
=======
MACHINE_CONFIG_MEMBER( msx_cart_majutsushi_device::device_add_mconfig )
	// This is actually incorrect. The sound output is passed back into the MSX machine where it is mixed internally and output through the system 'speaker'.
	MCFG_SPEAKER_STANDARD_MONO("speaker")
	MCFG_SOUND_ADD("dac", DAC_8BIT_R2R, 0) MCFG_SOUND_ROUTE(ALL_OUTPUTS, "speaker", 0.05) // unknown DAC
	MCFG_DEVICE_ADD("vref", VOLTAGE_REGULATOR, 0) MCFG_VOLTAGE_REGULATOR_OUTPUT(5.0)
	MCFG_SOUND_ROUTE_EX(0, "dac", 1.0, DAC_VREF_POS_INPUT) MCFG_SOUND_ROUTE_EX(0, "dac", -1.0, DAC_VREF_NEG_INPUT)
MACHINE_CONFIG_END


void msx_cart_majutsushi_device::device_start()
{
	save_item(NAME(m_selected_bank));

	machine().save().register_postload(save_prepost_delegate(FUNC(msx_cart_majutsushi_device::restore_banks), this));
}


void msx_cart_majutsushi_device::restore_banks()
>>>>>>> upstream/master
{
	m_bank_base[0] = get_rom_base() + ( m_selected_bank[0] & 0x0f ) * 0x2000;
	m_bank_base[1] = get_rom_base() + ( m_selected_bank[1] & 0x0f ) * 0x2000;
	m_bank_base[2] = get_rom_base() + ( m_selected_bank[0] & 0x0f ) * 0x2000;
	m_bank_base[3] = get_rom_base() + ( m_selected_bank[1] & 0x0f ) * 0x2000;
	m_bank_base[4] = get_rom_base() + ( m_selected_bank[2] & 0x0f ) * 0x2000;
	m_bank_base[5] = get_rom_base() + ( m_selected_bank[3] & 0x0f ) * 0x2000;
	m_bank_base[6] = get_rom_base() + ( m_selected_bank[2] & 0x0f ) * 0x2000;
	m_bank_base[7] = get_rom_base() + ( m_selected_bank[3] & 0x0f ) * 0x2000;
}


<<<<<<< HEAD
void msx_cart_majutsushi::device_reset()
=======
void msx_cart_majutsushi_device::device_reset()
>>>>>>> upstream/master
{
	for (int i = 0; i < 4; i++)
	{
		m_selected_bank[i] = i;
	}
}


<<<<<<< HEAD
void msx_cart_majutsushi::initialize_cartridge()
=======
void msx_cart_majutsushi_device::initialize_cartridge()
>>>>>>> upstream/master
{
	if ( get_rom_size() != 0x20000 )
	{
		fatalerror("majutsushi: Invalid ROM size\n");
	}

	restore_banks();
}


<<<<<<< HEAD
READ8_MEMBER(msx_cart_majutsushi::read_cart)
=======
READ8_MEMBER(msx_cart_majutsushi_device::read_cart)
>>>>>>> upstream/master
{
	return m_bank_base[offset >> 13][offset & 0x1fff];
}


<<<<<<< HEAD
WRITE8_MEMBER(msx_cart_majutsushi::write_cart)
=======
WRITE8_MEMBER(msx_cart_majutsushi_device::write_cart)
>>>>>>> upstream/master
{
	switch (offset & 0xe000)
	{
		case 0x4000:
			if (offset & 0x1000)
			{
<<<<<<< HEAD
				m_dac->write_unsigned8(data);
=======
				m_dac->write(data);
>>>>>>> upstream/master
			}
			break;

		case 0x6000:
			m_selected_bank[1] = data & 0x0f;
			m_bank_base[1] = get_rom_base() + m_selected_bank[1] * 0x2000;
			m_bank_base[3] = get_rom_base() + m_selected_bank[1] * 0x2000;
			break;

		case 0x8000:
			m_selected_bank[2] = data & 0x0f;
			m_bank_base[4] = get_rom_base() + m_selected_bank[2] * 0x2000;
			m_bank_base[6] = get_rom_base() + m_selected_bank[2] * 0x2000;
			break;

		case 0xa000:
			m_selected_bank[3] = data & 0x0f;
			m_bank_base[5] = get_rom_base() + m_selected_bank[3] * 0x2000;
			m_bank_base[7] = get_rom_base() + m_selected_bank[3] * 0x2000;
			break;
	}
}
