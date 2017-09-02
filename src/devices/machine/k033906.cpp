// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/***************************************************************************

    Konami IC 033906 (PCI bridge)

***************************************************************************/

#include "emu.h"
#include "k033906.h"
<<<<<<< HEAD
#include "video/voodoo.h"
=======
>>>>>>> upstream/master


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

// device type definition
<<<<<<< HEAD
const device_type K033906 = &device_creator<k033906_device>;
=======
DEFINE_DEVICE_TYPE(K033906, k033906_device, "k033906", "K033906 PCI bridge")
>>>>>>> upstream/master

//-------------------------------------------------
//  k033906_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
k033906_device::k033906_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, K033906, "K033906 PCI bridge", tag, owner, clock, "k033906", __FILE__), m_reg_set(0), m_voodoo_tag(nullptr), m_voodoo(nullptr)
=======
k033906_device::k033906_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, K033906, tag, owner, clock)
	, m_reg_set(0)
	, m_voodoo(*this, finder_base::DUMMY_TAG)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void k033906_device::device_start()
{
<<<<<<< HEAD
	m_voodoo = machine().device(m_voodoo_tag);

=======
>>>>>>> upstream/master
	m_reg_set = 0;

	save_item(NAME(m_reg));
	save_item(NAME(m_ram));
	save_item(NAME(m_reg_set));
}


WRITE_LINE_MEMBER(k033906_device::set_reg)
{
	m_reg_set = state & 1;
}

<<<<<<< HEAD
UINT32 k033906_device::reg_r(int reg)
=======
uint32_t k033906_device::reg_r(int reg)
>>>>>>> upstream/master
{
	switch (reg)
	{
		case 0x00:      return 0x0001121a;          // PCI Vendor ID (0x121a = 3dfx), Device ID (0x0001 = Voodoo)
		case 0x02:      return 0x04000000;          // Revision ID
		case 0x04:      return m_reg[0x04];         // memBaseAddr
		case 0x0f:      return m_reg[0x0f];         // interrupt_line, interrupt_pin, min_gnt, max_lat

		default:
<<<<<<< HEAD
			fatalerror("%s: k033906_reg_r: %08X\n", machine().describe_context(), reg);
=======
			fatalerror("%s: k033906_reg_r: %08X\n", machine().describe_context().c_str(), reg);
>>>>>>> upstream/master
	}
	// never executed
	//return 0;
}

<<<<<<< HEAD
void k033906_device::reg_w(int reg, UINT32 data)
=======
void k033906_device::reg_w(int reg, uint32_t data)
>>>>>>> upstream/master
{
	switch (reg)
	{
		case 0x00:
			break;

		case 0x01:      // command register
			break;

		case 0x04:      // memBaseAddr
		{
			if (data == 0xffffffff)
			{
				m_reg[0x04] = 0xff000000;
			}
			else
			{
				m_reg[0x04] = data & 0xff000000;
			}
			break;
		}

		case 0x0f:      // interrupt_line, interrupt_pin, min_gnt, max_lat
		{
			m_reg[0x0f] = data;
			break;
		}

		case 0x10:      // initEnable
		{
<<<<<<< HEAD
			voodoo_set_init_enable(m_voodoo, data);
=======
			m_voodoo->voodoo_set_init_enable(data);
>>>>>>> upstream/master
			break;
		}

		case 0x11:      // busSnoop0
		case 0x12:      // busSnoop1
			break;

		case 0x38:      // ???
			break;

		default:
<<<<<<< HEAD
			fatalerror("%s:K033906_w: %08X, %08X\n", machine().describe_context(), data, reg);
=======
			fatalerror("%s:K033906_w: %08X, %08X\n", machine().describe_context().c_str(), data, reg);
>>>>>>> upstream/master
	}
}

READ32_MEMBER(k033906_device::read)
{
	if (m_reg_set)
		return reg_r(offset);
	else
		return m_ram[offset];
}

WRITE32_MEMBER(k033906_device::write)
{
	if (m_reg_set)
		reg_w(offset, data);
	else
		m_ram[offset] = data;
}
