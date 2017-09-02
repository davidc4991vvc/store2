// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
#include "emu.h"
#include "msx_audio_kb.h"


<<<<<<< HEAD
const device_type MSX_AUDIO_KBDC_PORT = &device_creator<msx_audio_kbdc_port_device>;


msx_audio_kbdc_port_device::msx_audio_kbdc_port_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MSX_AUDIO_KBDC_PORT, "MSX Audio keyboard connector port", tag, owner, clock, "msx_audio_kbdc_port", __FILE__),
	device_slot_interface(mconfig, *this),
	m_keyboard(NULL)
=======
DEFINE_DEVICE_TYPE(MSX_AUDIO_KBDC_PORT, msx_audio_kbdc_port_device, "msx_audio_kbdc_port", "MSX Audio keyboard connector port")


msx_audio_kbdc_port_device::msx_audio_kbdc_port_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MSX_AUDIO_KBDC_PORT, tag, owner, clock)
	, device_slot_interface(mconfig, *this)
	, m_keyboard(nullptr)
>>>>>>> upstream/master
{
}


void msx_audio_kbdc_port_device::device_start()
{
	m_keyboard = dynamic_cast<msx_audio_kb_port_interface *>(get_card_device());
}


WRITE8_MEMBER(msx_audio_kbdc_port_device::write)
{
	if (m_keyboard)
	{
		m_keyboard->write(space, offset, data);
	}
}


READ8_MEMBER(msx_audio_kbdc_port_device::read)
{
	if (m_keyboard)
	{
		return m_keyboard->read(space, offset);
	}
	return 0xff;
}


<<<<<<< HEAD
extern const device_type MSX_AUDIO_KB_HXMU901;
extern const device_type MSX_AUDIO_KB_NMS1160;


class msx_hxmu901 : public device_t
					, public msx_audio_kb_port_interface
{
public:
	msx_hxmu901(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: device_t(mconfig, MSX_AUDIO_KB_HXMU901, "Toshiba HXMU901", tag, owner, clock, "hxmu901", __FILE__)
		, msx_audio_kb_port_interface(mconfig, *this)
		, m_row(0)
		, m_keyboard(*this, "KEY")
	{ };

	virtual ioport_constructor device_input_ports() const;

	virtual DECLARE_READ8_MEMBER(read)
	{
		UINT8 result = 0xff;
=======
DECLARE_DEVICE_TYPE(MSX_AUDIO_KB_HXMU901, msx_hxmu901_device)
DECLARE_DEVICE_TYPE(MSX_AUDIO_KB_NMS1160, msx_nms1160_device)


class msx_hxmu901_device : public device_t, public msx_audio_kb_port_interface
{
public:
	msx_hxmu901_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
		: device_t(mconfig, MSX_AUDIO_KB_HXMU901, tag, owner, clock)
		, msx_audio_kb_port_interface(mconfig, *this)
		, m_row(0)
		, m_keyboard(*this, "KEY.%u", 0)
	{
	}

	virtual ioport_constructor device_input_ports() const override;

	virtual DECLARE_READ8_MEMBER(read) override
	{
		uint8_t result = 0xff;
>>>>>>> upstream/master

		for (int i = 0; i < 8; i++)
		{
			if (BIT(m_row,i))
			{
				result &= m_keyboard[i]->read();
			}
		}
		return result;
	}

<<<<<<< HEAD
	virtual DECLARE_WRITE8_MEMBER(write)
=======
	virtual DECLARE_WRITE8_MEMBER(write) override
>>>>>>> upstream/master
	{
		m_row = data;
	}

protected:
<<<<<<< HEAD
	virtual void device_start() { }

private:
	UINT8 m_row;
=======
	virtual void device_start() override { }

private:
	uint8_t m_row;
>>>>>>> upstream/master
	required_ioport_array<8> m_keyboard;
};


static INPUT_PORTS_START( hxmu901)
	PORT_START("KEY.0")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C#1")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D1")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D#1")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_UNKNOWN)  // Multi sensor related?
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("E1")
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F1")
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F#1")
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C1")

	PORT_START("KEY.1")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G1")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G#1")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A1")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_UNKNOWN)  // Multi sensor related?
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A#1")
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("B1")
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C2")
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)

	PORT_START("KEY.2")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C#2")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D2")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D#2")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_UNKNOWN)  // Multi sensor related?
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("E2")
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F2")
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F#2")
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)

	PORT_START("KEY.3")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G2")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G#2")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A2")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_UNKNOWN)  // Multi sensor related?
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A#2")
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("B2")
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C3")
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)

	PORT_START("KEY.4")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C#3")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D3")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D#3")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_UNKNOWN)  // Multi sensor related?
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("E3")
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F3")
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F#3")
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)

	PORT_START("KEY.5")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G3")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G#3")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A3")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_UNKNOWN)  // Multi sensor related?
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A#3")
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("B3")
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C4")
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)

	PORT_START("KEY.6")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C#4")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D4")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D#4")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_UNKNOWN)  // Multi sensor related?
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("E4")
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F4")
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F#4")
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)

	PORT_START("KEY.7")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G4")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G#4")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A4")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_UNKNOWN)  // Multi sensor related?
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A#4")
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("B4")
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C5")
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
INPUT_PORTS_END


<<<<<<< HEAD
ioport_constructor msx_hxmu901::device_input_ports() const
=======
ioport_constructor msx_hxmu901_device::device_input_ports() const
>>>>>>> upstream/master
{
	return INPUT_PORTS_NAME( hxmu901 );
}


<<<<<<< HEAD
class msx_nms1160 : public device_t
					, public msx_audio_kb_port_interface
{
public:
	msx_nms1160(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: device_t(mconfig, MSX_AUDIO_KB_NMS1160, "Philips NMS-1160", tag, owner, clock, "nms1160", __FILE__)
		, msx_audio_kb_port_interface(mconfig, *this)
		, m_row(0)
		, m_keyboard(*this, "KEY")
	{ };

	virtual ioport_constructor device_input_ports() const;

	virtual DECLARE_READ8_MEMBER(read)
	{
		UINT8 result = 0xff;
=======
class msx_nms1160_device : public device_t, public msx_audio_kb_port_interface
{
public:
	msx_nms1160_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
		: device_t(mconfig, MSX_AUDIO_KB_NMS1160, tag, owner, clock)
		, msx_audio_kb_port_interface(mconfig, *this)
		, m_row(0)
		, m_keyboard(*this, "KEY.%u", 0)
	{
	}

	virtual ioport_constructor device_input_ports() const override;

	virtual DECLARE_READ8_MEMBER(read) override
	{
		uint8_t result = 0xff;
>>>>>>> upstream/master

		for (int i = 0; i < 8; i++)
		{
			if (BIT(m_row,i))
			{
				result &= m_keyboard[i]->read();
			}
		}
		return result;
	}

<<<<<<< HEAD
	virtual DECLARE_WRITE8_MEMBER(write)
=======
	virtual DECLARE_WRITE8_MEMBER(write) override
>>>>>>> upstream/master
	{
		logerror("msx_nms1160::write %02x\n", data);
		m_row = data;
	}

protected:
<<<<<<< HEAD
	virtual void device_start() { }

private:
	UINT8 m_row;
=======
	virtual void device_start() override { }

private:
	uint8_t m_row;
>>>>>>> upstream/master
	required_ioport_array<8> m_keyboard;
};


static INPUT_PORTS_START( nms1160 )
	PORT_START("KEY.0")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C1")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C#1")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D1")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D#1")
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("E1")
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F1")
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F#1")
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G1")

	PORT_START("KEY.1")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G#1")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A1")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A#1")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("B1")
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C2")
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C#2")
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D2")
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D#2")

	PORT_START("KEY.2")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("E2")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F2")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F#2")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G2")
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G#2")
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A2")
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A#2")
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("B2")

	PORT_START("KEY.3")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C3")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C#3")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D3")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D#3")
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("E3")
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F3")
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F#3")
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G3")

	PORT_START("KEY.4")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G#3")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A3")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A#3")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("B3")
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C4")
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C#4")
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D4")
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D#4")

	PORT_START("KEY.5")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("E4")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F4")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F#4")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G4")
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G#4")
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A4")
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A#4")
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("B4")

	PORT_START("KEY.6")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C5")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C#5")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D5")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D#5")
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("E5")
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F5")
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F#5")
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G5")

	PORT_START("KEY.7")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G#5")
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A5")
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A#5")
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("B5")
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C6")
	PORT_BIT(0xe0, IP_ACTIVE_LOW, IPT_UNUSED)
INPUT_PORTS_END


<<<<<<< HEAD
ioport_constructor msx_nms1160::device_input_ports() const
=======
ioport_constructor msx_nms1160_device::device_input_ports() const
>>>>>>> upstream/master
{
	return INPUT_PORTS_NAME( nms1160 );
}



<<<<<<< HEAD
const device_type MSX_AUDIO_KB_HXMU901 = &device_creator<msx_hxmu901>;
const device_type MSX_AUDIO_KB_NMS1160 = &device_creator<msx_nms1160>;
=======
DEFINE_DEVICE_TYPE(MSX_AUDIO_KB_HXMU901, msx_hxmu901_device, "hxmu901", "Toshiba HXMU901")
DEFINE_DEVICE_TYPE(MSX_AUDIO_KB_NMS1160, msx_nms1160_device, "nms1160", "Philips NMS-1160")
>>>>>>> upstream/master


SLOT_INTERFACE_START( msx_audio_keyboards )
	SLOT_INTERFACE("hxmu901", MSX_AUDIO_KB_HXMU901)
	SLOT_INTERFACE("nms1160", MSX_AUDIO_KB_NMS1160)
SLOT_INTERFACE_END
