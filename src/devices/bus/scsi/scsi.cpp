// license:BSD-3-Clause
// copyright-holders:smf

<<<<<<< HEAD
#include "scsi.h"

SCSI_PORT_DEVICE::SCSI_PORT_DEVICE(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, SCSI_PORT, "SCSI Port", tag, owner, clock, "scsi", __FILE__),
=======
#include "emu.h"
#include "scsi.h"

scsi_port_device::scsi_port_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, SCSI_PORT, tag, owner, clock),
>>>>>>> upstream/master
	m_bsy_handler(*this),
	m_sel_handler(*this),
	m_cd_handler(*this),
	m_io_handler(*this),
	m_msg_handler(*this),
	m_req_handler(*this),
	m_ack_handler(*this),
	m_atn_handler(*this),
	m_rst_handler(*this),
	m_data0_handler(*this),
	m_data1_handler(*this),
	m_data2_handler(*this),
	m_data3_handler(*this),
	m_data4_handler(*this),
	m_data5_handler(*this),
	m_data6_handler(*this),
	m_data7_handler(*this),
	m_device_count(0),
	m_bsy_in(0),
	m_sel_in(0),
	m_cd_in(0),
	m_io_in(0),
	m_msg_in(0),
	m_req_in(0),
	m_ack_in(0),
	m_atn_in(0),
	m_rst_in(0),
	m_data0_in(0),
	m_data1_in(0),
	m_data2_in(0),
	m_data3_in(0),
	m_data4_in(0),
	m_data5_in(0),
	m_data6_in(0),
	m_data7_in(0),
	m_bsy_out(0),
	m_sel_out(0),
	m_cd_out(0),
	m_io_out(0),
	m_msg_out(0),
	m_req_out(0),
	m_ack_out(0),
	m_atn_out(0),
	m_rst_out(0),
	m_data0_out(0),
	m_data1_out(0),
	m_data2_out(0),
	m_data3_out(0),
	m_data4_out(0),
	m_data5_out(0),
	m_data6_out(0),
	m_data7_out(0)
{
}

<<<<<<< HEAD
static MACHINE_CONFIG_FRAGMENT( scsi_port )
=======
MACHINE_CONFIG_MEMBER( scsi_port_device::device_add_mconfig )
>>>>>>> upstream/master
	MCFG_DEVICE_ADD( SCSI_PORT_DEVICE1, SCSI_PORT_SLOT, 0 )
	MCFG_DEVICE_ADD( SCSI_PORT_DEVICE2, SCSI_PORT_SLOT, 0 )
	MCFG_DEVICE_ADD( SCSI_PORT_DEVICE3, SCSI_PORT_SLOT, 0 )
	MCFG_DEVICE_ADD( SCSI_PORT_DEVICE4, SCSI_PORT_SLOT, 0 )
	MCFG_DEVICE_ADD( SCSI_PORT_DEVICE5, SCSI_PORT_SLOT, 0 )
	MCFG_DEVICE_ADD( SCSI_PORT_DEVICE6, SCSI_PORT_SLOT, 0 )
	MCFG_DEVICE_ADD( SCSI_PORT_DEVICE7, SCSI_PORT_SLOT, 0 )
MACHINE_CONFIG_END

<<<<<<< HEAD
machine_config_constructor SCSI_PORT_DEVICE::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( scsi_port );
}

void SCSI_PORT_DEVICE::device_start()
=======
void scsi_port_device::device_start()
>>>>>>> upstream/master
{
	const char *deviceName[] =
	{
		SCSI_PORT_DEVICE1,
		SCSI_PORT_DEVICE2,
		SCSI_PORT_DEVICE3,
		SCSI_PORT_DEVICE4,
		SCSI_PORT_DEVICE5,
		SCSI_PORT_DEVICE6,
		SCSI_PORT_DEVICE7
	};

	m_device_count = 0;

	for (int i = 0; i < 7; i++)
	{
<<<<<<< HEAD
		SCSI_PORT_SLOT_device *slot = subdevice<SCSI_PORT_SLOT_device>(deviceName[i]);
		m_slot[i] = slot;

		if (slot != NULL)
=======
		scsi_port_slot_device *slot = subdevice<scsi_port_slot_device>(deviceName[i]);
		m_slot[i] = slot;

		if (slot != nullptr)
>>>>>>> upstream/master
			m_device_count = i + 1;
	}

	m_bsy_handler.resolve_safe();
	m_sel_handler.resolve_safe();
	m_cd_handler.resolve_safe();
	m_io_handler.resolve_safe();
	m_msg_handler.resolve_safe();
	m_req_handler.resolve_safe();
	m_ack_handler.resolve_safe();
	m_atn_handler.resolve_safe();
	m_rst_handler.resolve_safe();
	m_data0_handler.resolve_safe();
	m_data1_handler.resolve_safe();
	m_data2_handler.resolve_safe();
	m_data3_handler.resolve_safe();
	m_data4_handler.resolve_safe();
	m_data5_handler.resolve_safe();
	m_data6_handler.resolve_safe();
	m_data7_handler.resolve_safe();

	m_data0_handler(0);
	m_data1_handler(0);
	m_data2_handler(0);
	m_data3_handler(0);
	m_data4_handler(0);
	m_data5_handler(0);
	m_data6_handler(0);
	m_data7_handler(0);

	m_bsy_handler(0);
	m_sel_handler(0);
	m_cd_handler(0);
	m_io_handler(0);
	m_msg_handler(0);
	m_req_handler(0);
	m_ack_handler(0);
	m_atn_handler(0);
	m_rst_handler(0);
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_bsy()
=======
void scsi_port_device::update_bsy()
>>>>>>> upstream/master
{
	int bsy = m_bsy_in;
	for (int i = 0; i < m_device_count; i++)
	{
		bsy |= m_slot[i]->m_bsy;
	}

	if (m_bsy_out != bsy)
	{
		m_bsy_out = bsy;
		m_bsy_handler(bsy);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_bsy(bsy);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_sel()
=======
void scsi_port_device::update_sel()
>>>>>>> upstream/master
{
	int sel = m_sel_in;
	for (int i = 0; i < m_device_count; i++)
	{
		sel |= m_slot[i]->m_sel;
	}

	if (m_sel_out != sel)
	{
		m_sel_out = sel;
		m_sel_handler(sel);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_sel(sel);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_cd()
=======
void scsi_port_device::update_cd()
>>>>>>> upstream/master
{
	int cd = m_cd_in;
	for (int i = 0; i < m_device_count; i++)
	{
		cd |= m_slot[i]->m_cd;
	}

	if (m_cd_out != cd)
	{
		m_cd_out = cd;
		m_cd_handler(cd);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_cd(cd);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_io()
=======
void scsi_port_device::update_io()
>>>>>>> upstream/master
{
	int io = m_io_in;
	for (int i = 0; i < m_device_count; i++)
	{
		io |= m_slot[i]->m_io;
	}

	if (m_io_out != io)
	{
		m_io_out = io;
		m_io_handler(io);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_io(io);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_msg()
=======
void scsi_port_device::update_msg()
>>>>>>> upstream/master
{
	int msg = m_msg_in;
	for (int i = 0; i < m_device_count; i++)
	{
		msg |= m_slot[i]->m_msg;
	}

	if (m_msg_out != msg)
	{
		m_msg_out = msg;
		m_msg_handler(msg);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_msg(msg);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_req()
=======
void scsi_port_device::update_req()
>>>>>>> upstream/master
{
	int req = m_req_in;
	for (int i = 0; i < m_device_count; i++)
	{
		req |= m_slot[i]->m_req;
	}

	if (m_req_out != req)
	{
		m_req_out = req;
		m_req_handler(req);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_req(req);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_ack()
=======
void scsi_port_device::update_ack()
>>>>>>> upstream/master
{
	int ack = m_ack_in;
	for (int i = 0; i < m_device_count; i++)
	{
		ack |= m_slot[i]->m_ack;
	}

	if (m_ack_out != ack)
	{
		m_ack_out = ack;
		m_ack_handler(ack);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_ack(ack);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_atn()
=======
void scsi_port_device::update_atn()
>>>>>>> upstream/master
{
	int atn = m_atn_in;
	for (int i = 0; i < m_device_count; i++)
	{
		atn |= m_slot[i]->m_atn;
	}

	if (m_atn_out != atn)
	{
		m_atn_out = atn;
		m_atn_handler(atn);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_atn(atn);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_rst()
=======
void scsi_port_device::update_rst()
>>>>>>> upstream/master
{
	int rst = m_rst_in;
	for (int i = 0; i < m_device_count; i++)
	{
		rst |= m_slot[i]->m_rst;
	}

	if (m_rst_out != rst)
	{
		m_rst_out = rst;
		m_rst_handler(rst);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_rst(rst);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_data0()
=======
void scsi_port_device::update_data0()
>>>>>>> upstream/master
{
	int data0 = m_data0_in;
	for (int i = 0; i < m_device_count; i++)
	{
		data0 |= m_slot[i]->m_data0;
	}

	if (m_data0_out != data0)
	{
		m_data0_out = data0;
		m_data0_handler(data0);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_data0(data0);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_data1()
=======
void scsi_port_device::update_data1()
>>>>>>> upstream/master
{
	int data1 = m_data1_in;
	for (int i = 0; i < m_device_count; i++)
	{
		data1 |= m_slot[i]->m_data1;
	}

	if (m_data1_out != data1)
	{
		m_data1_out = data1;
		m_data1_handler(data1);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_data1(data1);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_data2()
=======
void scsi_port_device::update_data2()
>>>>>>> upstream/master
{
	int data2 = m_data2_in;
	for (int i = 0; i < m_device_count; i++)
	{
		data2 |= m_slot[i]->m_data2;
	}

	if (m_data2_out != data2)
	{
		m_data2_out = data2;
		m_data2_handler(data2);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_data2(data2);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_data3()
=======
void scsi_port_device::update_data3()
>>>>>>> upstream/master
{
	int data3 = m_data3_in;
	for (int i = 0; i < m_device_count; i++)
	{
		data3 |= m_slot[i]->m_data3;
	}

	if (m_data3_out != data3)
	{
		m_data3_out = data3;
		m_data3_handler(data3);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_data3(data3);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_data4()
=======
void scsi_port_device::update_data4()
>>>>>>> upstream/master
{
	int data4 = m_data4_in;
	for (int i = 0; i < m_device_count; i++)
	{
		data4 |= m_slot[i]->m_data4;
	}

	if (m_data4_out != data4)
	{
		m_data4_out = data4;
		m_data4_handler(data4);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_data4(data4);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_data5()
=======
void scsi_port_device::update_data5()
>>>>>>> upstream/master
{
	int data5 = m_data5_in;
	for (int i = 0; i < m_device_count; i++)
	{
		data5 |= m_slot[i]->m_data5;
	}

	if (m_data5_out != data5)
	{
		m_data5_out = data5;
		m_data5_handler(data5);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_data5(data5);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_data6()
=======
void scsi_port_device::update_data6()
>>>>>>> upstream/master
{
	int data6 = m_data6_in;
	for (int i = 0; i < m_device_count; i++)
	{
		data6 |= m_slot[i]->m_data6;
	}

	if (m_data6_out != data6)
	{
		m_data6_out = data6;
		m_data6_handler(data6);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_data6(data6);
		}
	}
}

<<<<<<< HEAD
void SCSI_PORT_DEVICE::update_data7()
=======
void scsi_port_device::update_data7()
>>>>>>> upstream/master
{
	int data7 = m_data7_in;
	for (int i = 0; i < m_device_count; i++)
	{
		data7 |= m_slot[i]->m_data7;
	}

	if (m_data7_out != data7)
	{
		m_data7_out = data7;
		m_data7_handler(data7);

		for (int i = 0; i < m_device_count; i++)
		{
			scsi_port_interface *dev = m_slot[i]->dev();
<<<<<<< HEAD
			if (dev != NULL)
=======
			if (dev != nullptr)
>>>>>>> upstream/master
				dev->input_data7(data7);
		}
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_bsy )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_bsy )
>>>>>>> upstream/master
{
	if (m_bsy_in != state)
	{
		m_bsy_in = state;
		update_bsy();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_sel )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_sel )
>>>>>>> upstream/master
{
	if (m_sel_in != state)
	{
		m_sel_in = state;
		update_sel();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_cd )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_cd )
>>>>>>> upstream/master
{
	if (m_cd_in != state)
	{
		m_cd_in = state;
		update_cd();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_io )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_io )
>>>>>>> upstream/master
{
	if (m_io_in != state)
	{
		m_io_in = state;
		update_io();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_msg )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_msg )
>>>>>>> upstream/master
{
	if (m_msg_in != state)
	{
		m_msg_in = state;
		update_msg();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_req )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_req )
>>>>>>> upstream/master
{
	if (m_req_in != state)
	{
		m_req_in = state;
		update_req();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_ack )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_ack )
>>>>>>> upstream/master
{
	if (m_ack_in != state)
	{
		m_ack_in = state;
		update_ack();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_atn )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_atn )
>>>>>>> upstream/master
{
	if (m_atn_in != state)
	{
		m_atn_in = state;
		update_atn();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_rst )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_rst )
>>>>>>> upstream/master
{
	if (m_rst_in != state)
	{
		m_rst_in = state;
		update_rst();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_data0 )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_data0 )
>>>>>>> upstream/master
{
	if (m_data0_in != state)
	{
		m_data0_in = state;
		update_data0();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_data1 )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_data1 )
>>>>>>> upstream/master
{
	if (m_data1_in != state)
	{
		m_data1_in = state;
		update_data1();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_data2 )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_data2 )
>>>>>>> upstream/master
{
	if (m_data2_in != state)
	{
		m_data2_in = state;
		update_data2();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_data3 )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_data3 )
>>>>>>> upstream/master
{
	if (m_data3_in != state)
	{
		m_data3_in = state;
		update_data3();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_data4 )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_data4 )
>>>>>>> upstream/master
{
	if (m_data4_in != state)
	{
		m_data4_in = state;
		update_data4();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_data5 )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_data5 )
>>>>>>> upstream/master
{
	if (m_data5_in != state)
	{
		m_data5_in = state;
		update_data5();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_data6 )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_data6 )
>>>>>>> upstream/master
{
	if (m_data6_in != state)
	{
		m_data6_in = state;
		update_data6();
	}
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( SCSI_PORT_DEVICE::write_data7 )
=======
WRITE_LINE_MEMBER( scsi_port_device::write_data7 )
>>>>>>> upstream/master
{
	if (m_data7_in != state)
	{
		m_data7_in = state;
		update_data7();
	}
}

<<<<<<< HEAD
const device_type SCSI_PORT = &device_creator<SCSI_PORT_DEVICE>;

SCSI_PORT_SLOT_device::SCSI_PORT_SLOT_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, SCSI_PORT_SLOT, "SCSI Connector", tag, owner, clock, "scsi_slot", __FILE__),
	device_slot_interface(mconfig, *this),
	m_dev(NULL),
=======
DEFINE_DEVICE_TYPE(SCSI_PORT, scsi_port_device, "scsi", "SCSI Port")

scsi_port_slot_device::scsi_port_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, SCSI_PORT_SLOT, tag, owner, clock),
	device_slot_interface(mconfig, *this),
	m_dev(nullptr),
>>>>>>> upstream/master
	m_bsy(0),
	m_sel(0),
	m_cd(0),
	m_io(0),
	m_msg(0),
	m_req(0),
	m_ack(0),
	m_rst(0),
	m_data0(0),
	m_data1(0),
	m_data2(0),
	m_data3(0),
	m_data4(0),
	m_data5(0),
	m_data6(0),
	m_data7(0)
{
<<<<<<< HEAD
	m_port = dynamic_cast<SCSI_PORT_DEVICE *>(device().owner());
}

void SCSI_PORT_SLOT_device::device_config_complete()
=======
	m_port = dynamic_cast<scsi_port_device *>(device().owner());
}

void scsi_port_slot_device::device_config_complete()
>>>>>>> upstream/master
{
	m_dev = dynamic_cast<scsi_port_interface *>(get_card_device());
}

<<<<<<< HEAD
void SCSI_PORT_SLOT_device::device_start()
{
}

const device_type SCSI_PORT_SLOT = &device_creator<SCSI_PORT_SLOT_device>;
=======
void scsi_port_slot_device::device_start()
{
}

DEFINE_DEVICE_TYPE(SCSI_PORT_SLOT, scsi_port_slot_device, "scsi_slot", "SCSI Connector")
>>>>>>> upstream/master

scsi_port_interface::scsi_port_interface(const machine_config &mconfig, device_t &device)
	: device_slot_card_interface(mconfig, device)
{
<<<<<<< HEAD
	m_slot = dynamic_cast<SCSI_PORT_SLOT_device *>(device.owner());
=======
	m_slot = dynamic_cast<scsi_port_slot_device *>(device.owner());
>>>>>>> upstream/master
}

scsi_port_interface::~scsi_port_interface()
{
}
