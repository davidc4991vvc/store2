// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Motorola MC6852 Synchronous Serial Data Adapter emulation

**********************************************************************/

/*

    TODO:

    - FIFO
    - receive
    - transmit
    - parity
    - 1-sync-character mode
    - 2-sync-character mode
    - external sync mode
    - interrupts

*/

<<<<<<< HEAD
#include "mc6852.h"

=======
#include "emu.h"
#include "mc6852.h"

//#define VERBOSE 1
#include "logmacro.h"

>>>>>>> upstream/master

//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type MC6852 = &device_creator<mc6852_device>;



//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define LOG 0


#define S_RDA           0x01
#define S_TDRA          0x02
#define S_DCD           0x04
#define S_CTS           0x08
#define S_TUF           0x10
#define S_RX_OVRN       0x20
#define S_PE            0x40
#define S_IRQ           0x80


#define C1_RX_RS        0x01
#define C1_TX_RS        0x02
#define C1_STRIP_SYNC   0x04
#define C1_CLEAR_SYNC   0x08
#define C1_TIE          0x10
#define C1_RIE          0x20
#define C1_AC_MASK      0xc0
#define C1_AC_C2        0x00
#define C1_AC_C3        0x40
#define C1_AC_SYNC      0x80
#define C1_AC_TX_FIFO   0xc0


#define C2_PC1          0x01
#define C2_PC2          0x02
#define C2_1_2_BYTE     0x04
#define C2_WS_MASK      0x38
#define C2_WS_6_E       0x00
#define C2_WS_6_O       0x08
#define C2_WS_7         0x10
#define C2_WS_8         0x18
#define C2_WS_7_E       0x20
#define C2_WS_7_O       0x28
#define C2_WS_8_E       0x30
#define C2_WS_8_O       0x38
#define C2_TX_SYNC      0x40
#define C2_EIE          0x80


#define C3_E_I_SYNC     0x01
#define C3_1_2_SYNC     0x02
#define C3_CLEAR_CTS    0x04
#define C3_CTUF         0x08
=======
DEFINE_DEVICE_TYPE(MC6852, mc6852_device, "mc6852", "Motorola MC6852 SSDA")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  mc6852_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
mc6852_device::mc6852_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, MC6852, "MC6852", tag, owner, clock, "mc6852", __FILE__),
=======
mc6852_device::mc6852_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, MC6852, tag, owner, clock),
>>>>>>> upstream/master
	device_serial_interface(mconfig, *this),
	m_write_tx_data(*this),
	m_write_irq(*this),
	m_write_sm_dtr(*this),
	m_write_tuf(*this),
	m_rx_clock(0),
	m_tx_clock(0),
	m_cts(1),
	m_dcd(1),
	m_sm_dtr(0),
	m_tuf(0)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void mc6852_device::device_start()
{
	// resolve callbacks
	m_write_tx_data.resolve_safe();
	m_write_irq.resolve_safe();
	m_write_sm_dtr.resolve_safe();
	m_write_tuf.resolve_safe();

<<<<<<< HEAD
=======
	set_rcv_rate(m_rx_clock);
	set_tra_rate(m_tx_clock);

>>>>>>> upstream/master
	// register for state saving
	save_item(NAME(m_status));
	save_item(NAME(m_cr));
	save_item(NAME(m_scr));
	save_item(NAME(m_tdr));
	save_item(NAME(m_tsr));
	save_item(NAME(m_rdr));
	save_item(NAME(m_rsr));
	save_item(NAME(m_cts));
	save_item(NAME(m_dcd));
	save_item(NAME(m_sm_dtr));
	save_item(NAME(m_tuf));
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void mc6852_device::device_reset()
{
<<<<<<< HEAD
	m_rx_fifo = std::queue<UINT8>();
	m_tx_fifo = std::queue<UINT8>();

	transmit_register_reset();
	receive_register_reset();

	set_rcv_rate(m_rx_clock);
	set_tra_rate(m_tx_clock);

	/* set receiver shift register to all 1's */
	m_rsr = 0xff;

	/* reset and inhibit receiver/transmitter sections */
	m_cr[0] |= (C1_TX_RS | C1_RX_RS);
}


//-------------------------------------------------
//  device_timer - handler timer events
//-------------------------------------------------

void mc6852_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	device_serial_interface::device_timer(timer, id, param, ptr);
=======
	m_rx_fifo = std::queue<uint8_t>();
	m_tx_fifo = std::queue<uint8_t>();

	receive_register_reset();
	transmit_register_reset();

	/* reset and inhibit receiver/transmitter sections */
	m_cr[0] |= (C1_TX_RS | C1_RX_RS);
	m_cr[1] &= ~(C2_EIE | C2_PC2 | C2_PC1);
	m_status &= ~S_TDRA;

	/* set receiver shift register to all 1's */
	m_rsr = 0xff;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  tra_callback -
//-------------------------------------------------

void mc6852_device::tra_callback()
{
	m_write_tx_data(transmit_register_get_data_bit());
}


//-------------------------------------------------
//  tra_complete -
//-------------------------------------------------

void mc6852_device::tra_complete()
{
	// TODO
}


//-------------------------------------------------
//  rcv_complete -
//-------------------------------------------------

void mc6852_device::rcv_complete()
{
	// TODO
}


//-------------------------------------------------
//  read -
//-------------------------------------------------

READ8_MEMBER( mc6852_device::read )
{
<<<<<<< HEAD
	UINT8 data = 0;
=======
	uint8_t data = 0;
>>>>>>> upstream/master

	if (BIT(offset, 0))
	{
		if (m_rx_fifo.size() > 0)
		{
			data = m_rx_fifo.front();
			m_rx_fifo.pop();
		}
	}
	else
	{
		data = m_status;
	}

	return data;
}


//-------------------------------------------------
//  write -
//-------------------------------------------------

WRITE8_MEMBER( mc6852_device::write )
{
	if (BIT(offset, 0))
	{
		switch (m_cr[0] & C1_AC_MASK)
		{
<<<<<<< HEAD
		case C1_AC_C2:
			/* control 2 */
			m_cr[1] = data;
=======
		case C1_AC_C2: {
			/* control 2 */
			LOG("MC6852 Control 2 %02x\n", data);
			m_cr[1] = data;

			int data_bit_count = 0;
			parity_t parity = PARITY_NONE;
			stop_bits_t stop_bits = STOP_BITS_1;

			switch (data & C2_WS_MASK)
			{
			case 0: data_bit_count = 6; parity = PARITY_EVEN; break;
			case 1: data_bit_count = 6; parity = PARITY_ODD; break;
			case 2: data_bit_count = 7; parity = PARITY_NONE; break;
			case 3: data_bit_count = 8; parity = PARITY_NONE; break;
			case 4: data_bit_count = 7; parity = PARITY_EVEN; break;
			case 5: data_bit_count = 7; parity = PARITY_ODD; break;
			case 6: data_bit_count = 8; parity = PARITY_EVEN; break;
			case 7: data_bit_count = 8; parity = PARITY_ODD; break;
			}

			set_data_frame(1, data_bit_count, parity, stop_bits);
			}
>>>>>>> upstream/master
			break;

		case C1_AC_C3:
			/* control 3 */
<<<<<<< HEAD
=======
			LOG("MC6852 Control 3 %02x\n", data);
>>>>>>> upstream/master
			m_cr[2] = data;
			break;

		case C1_AC_SYNC:
			/* sync code */
<<<<<<< HEAD
=======
			LOG("MC6852 Sync Code %02x\n", data);
>>>>>>> upstream/master
			m_scr = data;
			break;

		case C1_AC_TX_FIFO:
			/* transmit data FIFO */
			if (m_tx_fifo.size() < 3)
			{
<<<<<<< HEAD
=======
				LOG("MC6852 Transmit FIFO %02x\n", data);
>>>>>>> upstream/master
				m_tx_fifo.push(data);
			}
			break;
		}
	}
	else
	{
<<<<<<< HEAD
=======
		LOG("MC6852 Control 1 %02x\n", data);

>>>>>>> upstream/master
		/* receiver reset */
		if (data & C1_RX_RS)
		{
			/* When Rx Rs is set, it clears the receiver
			control logic, sync logic, error logic, Rx Data FIFO Control,
			Parity Error status bit, and DCD interrupt. The Receiver Shift
			Register is set to ones.
			*/

<<<<<<< HEAD
			if (LOG) logerror("MC6852 '%s' Receiver Reset\n", tag());

			m_status &= ~(S_RX_OVRN | S_PE | S_DCD | S_RDA);
			m_rsr = 0xff;
=======
			LOG("MC6852 Receiver Reset\n");

			m_status &= ~(S_RX_OVRN | S_PE | S_DCD | S_RDA);
			m_rsr = 0xff;

			receive_register_reset();
>>>>>>> upstream/master
		}

		/* transmitter reset */
		if (data & C1_TX_RS)
		{
			/* When Tx Rs is set, it clears the transmitter
			control section, Transmitter Shift Register, Tx Data FIFO
			Control (the Tx Data FIFO can be reloaded after one E clock
			pulse), the Transmitter Underflow status bit, and the CTS interrupt,
			and inhibits the TDRA status bit (in the one-sync-character
			and two-sync-character modes).*/

<<<<<<< HEAD
			if (LOG) logerror("MC6852 '%s' Transmitter Reset\n", tag());

			m_status &= ~(S_TUF | S_CTS | S_TDRA);
		}

		if (LOG)
		{
			if (data & C1_STRIP_SYNC) logerror("MC6852 '%s' Strip Synchronization Characters\n", tag());
			if (data & C1_CLEAR_SYNC) logerror("MC6852 '%s' Clear Synchronization\n", tag());
		}

=======
			LOG("MC6852 Transmitter Reset\n");

			m_status &= ~(S_TUF | S_CTS | S_TDRA);

			transmit_register_reset();
		}

		if (data & C1_STRIP_SYNC) LOG("MC6852 Strip Synchronization Characters\n");
		if (data & C1_CLEAR_SYNC) LOG("MC6852 Clear Synchronization\n");

>>>>>>> upstream/master
		m_cr[0] = data;
	}
}
