// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    RCA VIP Expansion Board VP-575 emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "vp575.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type VP575 = &device_creator<vp575_device>;
=======
DEFINE_DEVICE_TYPE(VP575, vp575_device, "vp575", "VP-575 System Expansion")
>>>>>>> upstream/master


//-------------------------------------------------
//  VIP_EXPANSION_INTERFACE( expansion_intf )
//-------------------------------------------------

void vp575_device::update_interrupts()
{
	int interrupt = CLEAR_LINE;
	int dma_out = CLEAR_LINE;
	int dma_in = CLEAR_LINE;

	for (int i = 0; i < MAX_SLOTS; i++)
	{
		interrupt |= m_int[i];
		dma_out |= m_dma_out[i];
		dma_in |= m_dma_in[i];
	}

	m_slot->interrupt_w(interrupt);
	m_slot->dma_out_w(dma_out);
	m_slot->dma_in_w(dma_in);
}


//-------------------------------------------------
<<<<<<< HEAD
//  MACHINE_CONFIG_FRAGMENT( vp575 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( vp575 )
	MCFG_VIP_EXPANSION_SLOT_ADD("exp1", XTAL_3_52128MHz/2, vip_expansion_cards, NULL)
=======
//  MACHINE_CONFIG_START( vp575 )
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( vp575_device::device_add_mconfig )
	MCFG_VIP_EXPANSION_SLOT_ADD("exp1", XTAL_3_52128MHz/2, vip_expansion_cards, nullptr)
>>>>>>> upstream/master
	MCFG_VIP_EXPANSION_SLOT_INT_CALLBACK(WRITELINE(vp575_device, exp1_int_w))
	MCFG_VIP_EXPANSION_SLOT_DMA_OUT_CALLBACK(WRITELINE(vp575_device, exp1_dma_out_w))
	MCFG_VIP_EXPANSION_SLOT_DMA_IN_CALLBACK(WRITELINE(vp575_device, exp1_dma_in_w))

<<<<<<< HEAD
	MCFG_VIP_EXPANSION_SLOT_ADD("exp2", XTAL_3_52128MHz/2, vip_expansion_cards, NULL)
=======
	MCFG_VIP_EXPANSION_SLOT_ADD("exp2", XTAL_3_52128MHz/2, vip_expansion_cards, nullptr)
>>>>>>> upstream/master
	MCFG_VIP_EXPANSION_SLOT_INT_CALLBACK(WRITELINE(vp575_device, exp2_int_w))
	MCFG_VIP_EXPANSION_SLOT_DMA_OUT_CALLBACK(WRITELINE(vp575_device, exp2_dma_out_w))
	MCFG_VIP_EXPANSION_SLOT_DMA_IN_CALLBACK(WRITELINE(vp575_device, exp2_dma_in_w))

<<<<<<< HEAD
	MCFG_VIP_EXPANSION_SLOT_ADD("exp3", XTAL_3_52128MHz/2, vip_expansion_cards, NULL)
=======
	MCFG_VIP_EXPANSION_SLOT_ADD("exp3", XTAL_3_52128MHz/2, vip_expansion_cards, nullptr)
>>>>>>> upstream/master
	MCFG_VIP_EXPANSION_SLOT_INT_CALLBACK(WRITELINE(vp575_device, exp3_int_w))
	MCFG_VIP_EXPANSION_SLOT_DMA_OUT_CALLBACK(WRITELINE(vp575_device, exp3_dma_out_w))
	MCFG_VIP_EXPANSION_SLOT_DMA_IN_CALLBACK(WRITELINE(vp575_device, exp3_dma_in_w))

<<<<<<< HEAD
	MCFG_VIP_EXPANSION_SLOT_ADD("exp4", XTAL_3_52128MHz/2, vip_expansion_cards, NULL)
=======
	MCFG_VIP_EXPANSION_SLOT_ADD("exp4", XTAL_3_52128MHz/2, vip_expansion_cards, nullptr)
>>>>>>> upstream/master
	MCFG_VIP_EXPANSION_SLOT_INT_CALLBACK(WRITELINE(vp575_device, exp4_int_w))
	MCFG_VIP_EXPANSION_SLOT_DMA_OUT_CALLBACK(WRITELINE(vp575_device, exp4_dma_out_w))
	MCFG_VIP_EXPANSION_SLOT_DMA_IN_CALLBACK(WRITELINE(vp575_device, exp4_dma_in_w))

<<<<<<< HEAD
	MCFG_VIP_EXPANSION_SLOT_ADD("exp5", XTAL_3_52128MHz/2, vip_expansion_cards, NULL)
=======
	MCFG_VIP_EXPANSION_SLOT_ADD("exp5", XTAL_3_52128MHz/2, vip_expansion_cards, nullptr)
>>>>>>> upstream/master
	MCFG_VIP_EXPANSION_SLOT_INT_CALLBACK(WRITELINE(vp575_device, exp5_int_w))
	MCFG_VIP_EXPANSION_SLOT_DMA_OUT_CALLBACK(WRITELINE(vp575_device, exp5_dma_out_w))
	MCFG_VIP_EXPANSION_SLOT_DMA_IN_CALLBACK(WRITELINE(vp575_device, exp5_dma_in_w))
MACHINE_CONFIG_END


<<<<<<< HEAD
//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor vp575_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( vp575 );
}


=======
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  vp575_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
vp575_device::vp575_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, VP575, "VP575", tag, owner, clock, "vp575", __FILE__),
	device_vip_expansion_card_interface(mconfig, *this)
=======
vp575_device::vp575_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, VP575, tag, owner, clock),
	device_vip_expansion_card_interface(mconfig, *this),
	m_expansion_slot(*this, "exp%u", 1)
>>>>>>> upstream/master
{
	for (int i = 0; i < MAX_SLOTS; i++)
	{
		m_int[i] = CLEAR_LINE;
		m_dma_out[i] = CLEAR_LINE;
		m_dma_in[i] = CLEAR_LINE;
	}
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void vp575_device::device_start()
{
<<<<<<< HEAD
	// find devices
	m_expansion_slot[0] = dynamic_cast<vip_expansion_slot_device *>(subdevice("exp1"));
	m_expansion_slot[1] = dynamic_cast<vip_expansion_slot_device *>(subdevice("exp2"));
	m_expansion_slot[2] = dynamic_cast<vip_expansion_slot_device *>(subdevice("exp3"));
	m_expansion_slot[3] = dynamic_cast<vip_expansion_slot_device *>(subdevice("exp4"));
	m_expansion_slot[4] = dynamic_cast<vip_expansion_slot_device *>(subdevice("exp5"));
=======
>>>>>>> upstream/master
}


//-------------------------------------------------
//  vip_program_r - program read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 vp575_device::vip_program_r(address_space &space, offs_t offset, int cs, int cdef, int *minh)
{
	UINT8 data = 0xff;

	for (int i = 0; i < MAX_SLOTS; i++)
	{
		data &= m_expansion_slot[i]->program_r(space, offset, cs, cdef, minh);
=======
uint8_t vp575_device::vip_program_r(address_space &space, offs_t offset, int cs, int cdef, int *minh)
{
	uint8_t data = 0xff;

	for (auto & elem : m_expansion_slot)
	{
		data &= elem->program_r(space, offset, cs, cdef, minh);
>>>>>>> upstream/master
	}

	return data;
}


//-------------------------------------------------
//  vip_program_w - program write
//-------------------------------------------------

<<<<<<< HEAD
void vp575_device::vip_program_w(address_space &space, offs_t offset, UINT8 data, int cdef, int *minh)
{
	for (int i = 0; i < MAX_SLOTS; i++)
	{
		m_expansion_slot[i]->program_w(space, offset, data, cdef, minh);
=======
void vp575_device::vip_program_w(address_space &space, offs_t offset, uint8_t data, int cdef, int *minh)
{
	for (auto & elem : m_expansion_slot)
	{
		elem->program_w(space, offset, data, cdef, minh);
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  vip_io_r - I/O read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 vp575_device::vip_io_r(address_space &space, offs_t offset)
{
	UINT8 data = 0xff;

	for (int i = 0; i < MAX_SLOTS; i++)
	{
		data &= m_expansion_slot[i]->io_r(space, offset);
=======
uint8_t vp575_device::vip_io_r(address_space &space, offs_t offset)
{
	uint8_t data = 0xff;

	for (auto & elem : m_expansion_slot)
	{
		data &= elem->io_r(space, offset);
>>>>>>> upstream/master
	}

	return data;
}


//-------------------------------------------------
//  vip_io_w - I/O write
//-------------------------------------------------

<<<<<<< HEAD
void vp575_device::vip_io_w(address_space &space, offs_t offset, UINT8 data)
{
	for (int i = 0; i < MAX_SLOTS; i++)
	{
		m_expansion_slot[i]->io_w(space, offset, data);
=======
void vp575_device::vip_io_w(address_space &space, offs_t offset, uint8_t data)
{
	for (auto & elem : m_expansion_slot)
	{
		elem->io_w(space, offset, data);
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  vip_dma_r - DMA read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 vp575_device::vip_dma_r(address_space &space, offs_t offset)
{
	UINT8 data = 0xff;

	for (int i = 0; i < MAX_SLOTS; i++)
	{
		data &= m_expansion_slot[i]->dma_r(space, offset);
=======
uint8_t vp575_device::vip_dma_r(address_space &space, offs_t offset)
{
	uint8_t data = 0xff;

	for (auto & elem : m_expansion_slot)
	{
		data &= elem->dma_r(space, offset);
>>>>>>> upstream/master
	}

	return data;
}


//-------------------------------------------------
//  vip_dma_w - DMA write
//-------------------------------------------------

<<<<<<< HEAD
void vp575_device::vip_dma_w(address_space &space, offs_t offset, UINT8 data)
{
	for (int i = 0; i < MAX_SLOTS; i++)
	{
		m_expansion_slot[i]->dma_w(space, offset, data);
=======
void vp575_device::vip_dma_w(address_space &space, offs_t offset, uint8_t data)
{
	for (auto & elem : m_expansion_slot)
	{
		elem->dma_w(space, offset, data);
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  vip_screen_update - screen update
//-------------------------------------------------

<<<<<<< HEAD
UINT32 vp575_device::vip_screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect)
{
	UINT32 data = 0;

	for (int i = 0; i < MAX_SLOTS; i++)
	{
		data |= m_expansion_slot[i]->screen_update(screen, bitmap, cliprect);
=======
uint32_t vp575_device::vip_screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect)
{
	uint32_t data = 0;

	for (auto & elem : m_expansion_slot)
	{
		data |= elem->screen_update(screen, bitmap, cliprect);
>>>>>>> upstream/master
	}

	return data;
}


//-------------------------------------------------
//  vip_ef1_r - EF1 flag read
//-------------------------------------------------

int vp575_device::vip_ef1_r()
{
	int state = CLEAR_LINE;

<<<<<<< HEAD
	for (int i = 0; i < MAX_SLOTS; i++)
	{
		state |= m_expansion_slot[i]->ef1_r();
=======
	for (auto & elem : m_expansion_slot)
	{
		state |= elem->ef1_r();
>>>>>>> upstream/master
	}

	return state;
}


//-------------------------------------------------
//  vip_ef3_r - EF3 flag read
//-------------------------------------------------

int vp575_device::vip_ef3_r()
{
	int state = CLEAR_LINE;

<<<<<<< HEAD
	for (int i = 0; i < MAX_SLOTS; i++)
	{
		state |= m_expansion_slot[i]->ef3_r();
=======
	for (auto & elem : m_expansion_slot)
	{
		state |= elem->ef3_r();
>>>>>>> upstream/master
	}

	return state;
}


//-------------------------------------------------
//  vip_ef4_r - EF4 flag read
//-------------------------------------------------

int vp575_device::vip_ef4_r()
{
	int state = CLEAR_LINE;

<<<<<<< HEAD
	for (int i = 0; i < MAX_SLOTS; i++)
	{
		state |= m_expansion_slot[i]->ef4_r();
=======
	for (auto & elem : m_expansion_slot)
	{
		state |= elem->ef4_r();
>>>>>>> upstream/master
	}

	return state;
}


//-------------------------------------------------
//  vip_sc_w - status code write
//-------------------------------------------------

void vp575_device::vip_sc_w(int data)
{
<<<<<<< HEAD
	for (int i = 0; i < MAX_SLOTS; i++)
	{
		m_expansion_slot[i]->sc_w(data);
=======
	for (auto & elem : m_expansion_slot)
	{
		elem->sc_w(data);
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  vip_q_w - Q write
//-------------------------------------------------

void vp575_device::vip_q_w(int state)
{
<<<<<<< HEAD
	for (int i = 0; i < MAX_SLOTS; i++)
	{
		m_expansion_slot[i]->q_w(state);
=======
	for (auto & elem : m_expansion_slot)
	{
		elem->q_w(state);
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  vip_run_w - RUN write
//-------------------------------------------------

void vp575_device::vip_run_w(int state)
{
<<<<<<< HEAD
	for (int i = 0; i < MAX_SLOTS; i++)
	{
		m_expansion_slot[i]->run_w(state);
=======
	for (auto & elem : m_expansion_slot)
	{
		elem->run_w(state);
>>>>>>> upstream/master
	}
}
