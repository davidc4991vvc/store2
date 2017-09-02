// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
/**************************************************************************

Yamaha SFG01/SFG05 emulation

TODO:
- Use a real YM2164 implementation for SFG05

**************************************************************************/

#include "emu.h"
#include "yamaha.h"
<<<<<<< HEAD
#include "bus/midi/midi.h"


const device_type MSX_CART_SFG01 = &device_creator<msx_cart_sfg01>;
const device_type MSX_CART_SFG05 = &device_creator<msx_cart_sfg05>;


msx_cart_sfg::msx_cart_sfg(const machine_config &mconfig, const device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname)
	: device_t(mconfig, type, name, tag, owner, clock, shortname, __FILE__)
=======

#include "bus/midi/midi.h"
#include "speaker.h"


DEFINE_DEVICE_TYPE(MSX_CART_SFG01, msx_cart_sfg01_device, "msx_cart_sfg01", "MSX Cartridge - SFG01")
DEFINE_DEVICE_TYPE(MSX_CART_SFG05, msx_cart_sfg05_device, "msx_cart_sfg05", "MSX Cartridge - SFG05")


msx_cart_sfg_device::msx_cart_sfg_device(const machine_config &mconfig, const device_type type, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, type, tag, owner, clock)
>>>>>>> upstream/master
	, msx_cart_interface(mconfig, *this)
	, m_region_sfg(*this, "sfg")
	, m_ym2151(*this, "ym2151")
	, m_kbdc(*this, "kbdc")
	, m_ym2148(*this, "ym2148")
	, m_ym2151_irq_state(CLEAR_LINE)
	, m_ym2148_irq_state(CLEAR_LINE)
	, m_rom_mask(0)
{
}


<<<<<<< HEAD
msx_cart_sfg01::msx_cart_sfg01(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: msx_cart_sfg(mconfig, MSX_CART_SFG01, "MSX Cartridge - SFG01", tag, owner, clock, "msx_cart_sfg01")
=======
msx_cart_sfg01_device::msx_cart_sfg01_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: msx_cart_sfg_device(mconfig, MSX_CART_SFG01, tag, owner, clock)
>>>>>>> upstream/master
{
}


<<<<<<< HEAD
msx_cart_sfg05::msx_cart_sfg05(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: msx_cart_sfg(mconfig, MSX_CART_SFG05, "MSX Cartridge - SFG05", tag, owner, clock, "msx_cart_sfg05")
=======
msx_cart_sfg05_device::msx_cart_sfg05_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: msx_cart_sfg_device(mconfig, MSX_CART_SFG05, tag, owner, clock)
>>>>>>> upstream/master
{
}


<<<<<<< HEAD
static MACHINE_CONFIG_FRAGMENT( msx_sfg )
=======
MACHINE_CONFIG_MEMBER( msx_cart_sfg_device::device_add_mconfig )
>>>>>>> upstream/master
	// YM2151 (OPM)
	// YM3012 (DAC)
	// YM2148 (MKS)

	MCFG_SPEAKER_STANDARD_STEREO("lspeaker", "rspeaker")
	MCFG_YM2151_ADD("ym2151", XTAL_3_579545MHz)  // The SFG01 uses a YM2151, the SFG05 uses a YM2164, input clock comes from the main cpu frequency
<<<<<<< HEAD
	MCFG_YM2151_IRQ_HANDLER(WRITELINE(msx_cart_sfg, ym2151_irq_w))
=======
	MCFG_YM2151_IRQ_HANDLER(WRITELINE(msx_cart_sfg_device, ym2151_irq_w))
>>>>>>> upstream/master
	MCFG_SOUND_ROUTE(0, "lspeaker", 0.80)
	MCFG_SOUND_ROUTE(1, "rspeaker", 0.80)

	MCFG_DEVICE_ADD("ym2148", YM2148, XTAL_4MHz)
	MCFG_YM2148_TXD_HANDLER(DEVWRITELINE("mdout", midi_port_device, write_txd))
	MCFG_YM2148_PORT_WRITE_HANDLER(DEVWRITE8("kbdc", msx_audio_kbdc_port_device, write))
	MCFG_YM2148_PORT_READ_HANDLER(DEVREAD8("kbdc", msx_audio_kbdc_port_device, read))
<<<<<<< HEAD
	MCFG_YM2148_IRQ_HANDLER(WRITELINE(msx_cart_sfg,ym2148_irq_w))

	MCFG_MSX_AUDIO_KBDC_PORT_ADD("kbdc", msx_audio_keyboards, NULL)
=======
	MCFG_YM2148_IRQ_HANDLER(WRITELINE(msx_cart_sfg_device, ym2148_irq_w))

	MCFG_MSX_AUDIO_KBDC_PORT_ADD("kbdc", msx_audio_keyboards, nullptr)
>>>>>>> upstream/master

	MCFG_MIDI_PORT_ADD("mdout", midiout_slot, "midiout")

	MCFG_MIDI_PORT_ADD("mdin", midiin_slot, "midiin")
	MCFG_MIDI_RX_HANDLER(DEVWRITELINE("ym2148", ym2148_device, write_rxd))
MACHINE_CONFIG_END


<<<<<<< HEAD
machine_config_constructor msx_cart_sfg::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( msx_sfg );
}


=======
>>>>>>> upstream/master
ROM_START( msx_sfg01 )
	ROM_REGION(0x4000, "sfg", 0)
	ROM_LOAD("sfg01.rom", 0x0, 0x4000, CRC(0995fb36) SHA1(434651305f92aa770a89e40b81125fb22d91603d))
ROM_END


<<<<<<< HEAD
const rom_entry *msx_cart_sfg01::device_rom_region() const
=======
const tiny_rom_entry *msx_cart_sfg01_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( msx_sfg01 );
}


ROM_START( msx_sfg05 )
	ROM_REGION(0x8000, "sfg", 0)
	ROM_LOAD("sfg05.rom", 0x0, 0x8000, CRC(2425c279) SHA1(d956167e234f60ad916120437120f86fc8c3c321))
ROM_END


<<<<<<< HEAD
const rom_entry *msx_cart_sfg05::device_rom_region() const
=======
const tiny_rom_entry *msx_cart_sfg05_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( msx_sfg05 );
}


<<<<<<< HEAD
void msx_cart_sfg::device_start()
=======
void msx_cart_sfg_device::device_start()
>>>>>>> upstream/master
{
	// Set rom mask
	m_rom_mask = m_region_sfg->bytes() - 1;

	// This should probably moved up in the bus/slot hierarchy for the msx driver
	cpu_device *maincpu = machine().device<cpu_device>("maincpu");
<<<<<<< HEAD
	device_execute_interface::static_set_irq_acknowledge_callback(*maincpu, device_irq_acknowledge_delegate(FUNC(msx_cart_sfg::irq_callback),this));
}


IRQ_CALLBACK_MEMBER(msx_cart_sfg::irq_callback)
=======
	device_execute_interface::static_set_irq_acknowledge_callback(*maincpu, device_irq_acknowledge_delegate(FUNC(msx_cart_sfg_device::irq_callback),this));
}


IRQ_CALLBACK_MEMBER(msx_cart_sfg_device::irq_callback)
>>>>>>> upstream/master
{
	return m_ym2148->get_irq_vector();
}


<<<<<<< HEAD
WRITE_LINE_MEMBER(msx_cart_sfg::ym2151_irq_w)
=======
WRITE_LINE_MEMBER(msx_cart_sfg_device::ym2151_irq_w)
>>>>>>> upstream/master
{
	m_ym2151_irq_state = state ? ASSERT_LINE : CLEAR_LINE;
	check_irq();
}


<<<<<<< HEAD
WRITE_LINE_MEMBER(msx_cart_sfg::ym2148_irq_w)
=======
WRITE_LINE_MEMBER(msx_cart_sfg_device::ym2148_irq_w)
>>>>>>> upstream/master
{
	m_ym2148_irq_state = state ? ASSERT_LINE : CLEAR_LINE;
	check_irq();
}


<<<<<<< HEAD
void msx_cart_sfg::check_irq()
=======
void msx_cart_sfg_device::check_irq()
>>>>>>> upstream/master
{
	if (m_ym2151_irq_state != CLEAR_LINE || m_ym2148_irq_state != CLEAR_LINE)
	{
		m_out_irq_cb(ASSERT_LINE);
	}
	else
	{
		m_out_irq_cb(CLEAR_LINE);
	}
}


<<<<<<< HEAD
READ8_MEMBER(msx_cart_sfg::read_cart)
=======
READ8_MEMBER(msx_cart_sfg_device::read_cart)
>>>>>>> upstream/master
{
	switch (offset & 0x3fff)
	{
		case 0x3ff0:     // YM-2151 status read
		case 0x3ff1:     // YM-2151 status read mirror?
			return m_ym2151->status_r(space, 0);

		case 0x3ff2:     // YM-2148 keyboard column read
		case 0x3ff3:     // YM-2148 --
		case 0x3ff4:     // YM-2148 --
		case 0x3ff5:     // YM-2148 MIDI UART data read register
		case 0x3ff6:     // YM-2148 MIDI UART status register
							// ------x- - 1 = received a byte/receive buffer full?
							// -------x - 1 = ready to send next byte/send buffer empty?
			return m_ym2148->read(space, offset & 7);
	}

	if (offset < 0x8000)
	{
<<<<<<< HEAD
		return m_region_sfg->u8(offset & m_rom_mask);
=======
		return m_region_sfg->as_u8(offset & m_rom_mask);
>>>>>>> upstream/master
	}

	return 0xff;
}


<<<<<<< HEAD
WRITE8_MEMBER(msx_cart_sfg::write_cart)
=======
WRITE8_MEMBER(msx_cart_sfg_device::write_cart)
>>>>>>> upstream/master
{
	switch (offset & 0x3fff)
	{
		case 0x3ff0:     // YM-2151 register
			m_ym2151->register_w(space, 0, data);
			break;

		case 0x3ff1:    // YM-2151 data
			m_ym2151->data_w(space, 0, data);
			break;

		case 0x3ff2:   // YM-2148 write keyboard row
		case 0x3ff3:   // YM-2148 MIDI IRQ vector
		case 0x3ff4:   // YM-2148 External IRQ vector
		case 0x3ff5:   // YM-2148 MIDI UART data write register
		case 0x3ff6:   // YM-2148 MIDI UART command register
						// On startup the sfg01 writes 0x80
						// followed by 0x05.
						// Other write seen in the code: 0x15
						//
						// x------- - 1 = reset
						// -----x-- - 1 = enable receiving / sending midi data
						// -------x - 1 = enable receiving / sending midi data
			m_ym2148->write(space, offset & 7, data);
			break;

		default:
<<<<<<< HEAD
			logerror("msx_cart_sfg::write_cart: write %02x to %04x\n", data, offset);
=======
			logerror("msx_cart_sfg_device::write_cart: write %02x to %04x\n", data, offset);
>>>>>>> upstream/master
			break;
	}
}
