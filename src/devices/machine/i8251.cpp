// license:BSD-3-Clause
// copyright-holders:smf
/*********************************************************************

    i8251.c

    Intel 8251 Universal Synchronous/Asynchronous Receiver Transmitter code
    NEC uPD71051 is a clone

    The V53/V53A use a customized version with only the Asynchronous mode
    and a split command / mode register



*********************************************************************/

#include "emu.h"
#include "i8251.h"

<<<<<<< HEAD

/***************************************************************************
    MACROS
***************************************************************************/

#define VERBOSE 0

#define LOG(x)  do { if (VERBOSE) logerror x; } while (0)
=======
//#define VERBOSE 1
#include "logmacro.h"

>>>>>>> upstream/master

//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type I8251 = &device_creator<i8251_device>;
const device_type V53_SCU = &device_creator<v53_scu_device>;
=======
DEFINE_DEVICE_TYPE(I8251,   i8251_device,  "i8251",    "Intel 8251 USART")
DEFINE_DEVICE_TYPE(V53_SCU, v53_scu_device, "v63_scu", "NEC V53 SCU")

>>>>>>> upstream/master

//-------------------------------------------------
//  i8251_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
i8251_device::i8251_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname)
	: device_t(mconfig, type, name, tag, owner, clock, shortname, __FILE__),
=======
i8251_device::i8251_device(
		const machine_config &mconfig,
		device_type type,
		const char *tag,
		device_t *owner,
		uint32_t clock)
	: device_t(mconfig, type, tag, owner, clock),
>>>>>>> upstream/master
	device_serial_interface(mconfig, *this),
	m_txd_handler(*this),
	m_dtr_handler(*this),
	m_rts_handler(*this),
	m_rxrdy_handler(*this),
	m_txrdy_handler(*this),
	m_txempty_handler(*this),
	m_syndet_handler(*this),
	m_cts(1),
	m_dsr(1),
	m_rxd(0),
	m_rxc(0),
	m_txc(0)
{
}

<<<<<<< HEAD
i8251_device::i8251_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, I8251, "8251 USART", tag, owner, clock, "i8251", __FILE__),
	device_serial_interface(mconfig, *this),
	m_txd_handler(*this),
	m_dtr_handler(*this),
	m_rts_handler(*this),
	m_rxrdy_handler(*this),
	m_txrdy_handler(*this),
	m_txempty_handler(*this),
	m_syndet_handler(*this),
	m_cts(1),
	m_dsr(1),
	m_rxd(0),
	m_rxc(0),
	m_txc(0)
{
}

v53_scu_device::v53_scu_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: i8251_device(mconfig, V53_SCU, "V53 SCU", tag, owner, clock, "v53_scu")
=======
i8251_device::i8251_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: i8251_device(mconfig, I8251, tag, owner, clock)
{
}

v53_scu_device::v53_scu_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: i8251_device(mconfig, V53_SCU, tag, owner, clock)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void i8251_device::device_start()
{
	// resolve callbacks
	m_txd_handler.resolve_safe();
	m_rts_handler.resolve_safe();
	m_dtr_handler.resolve_safe();
	m_rxrdy_handler.resolve_safe();
	m_txrdy_handler.resolve_safe();
	m_txempty_handler.resolve_safe();
	save_item(NAME(m_flags));
	save_item(NAME(m_sync_byte_offset));
	save_item(NAME(m_sync_byte_count));
	save_item(NAME(m_sync_bytes));
	save_item(NAME(m_status));
	save_item(NAME(m_command));
	save_item(NAME(m_mode_byte));
	save_item(NAME(m_cts));
	save_item(NAME(m_dsr));
	save_item(NAME(m_rxd));
	save_item(NAME(m_rxc));
	save_item(NAME(m_txc));
	save_item(NAME(m_rxc_count));
	save_item(NAME(m_txc_count));
	save_item(NAME(m_br_factor));
	save_item(NAME(m_rx_data));
	save_item(NAME(m_tx_data));
<<<<<<< HEAD
	device_serial_interface::register_save_state(machine().save(), this);
=======
>>>>>>> upstream/master
}




/*-------------------------------------------------
    update_rx_ready
-------------------------------------------------*/

void i8251_device::update_rx_ready()
{
<<<<<<< HEAD
	int state;

	state = m_status & I8251_STATUS_RX_READY;

	/* masked? */
	if ((m_command & (1<<2))==0)
	{
		state = 0;
	}
=======
	int state = m_status & I8251_STATUS_RX_READY;

	// masked?
	if (!BIT(m_command, 2))
		state = 0;
>>>>>>> upstream/master

	m_rxrdy_handler(state != 0);
}



/*-------------------------------------------------
    receive_clock
-------------------------------------------------*/

void i8251_device::receive_clock()
{
<<<<<<< HEAD
	m_rxc_count++;

	if (m_rxc_count == m_br_factor)
		m_rxc_count = 0;
	else
		return;

	/* receive enable? */
	if (m_command & (1<<2))
	{
		//logerror("I8251\n");
		/* get bit received from other side and update receive register */
		receive_register_update_bit(m_rxd);
=======
	/* receive enable? */
	if (BIT(m_command, 2))
	{
		const bool sync = is_receive_register_synchronized();
		if (sync)
		{
			--m_rxc_count;
			if (m_rxc_count)
				return;
		}

		//logerror("I8251\n");
		/* get bit received from other side and update receive register */
		receive_register_update_bit(m_rxd);
		if (is_receive_register_synchronized())
			m_rxc_count = sync ? m_br_factor : (3 * m_br_factor / 2);
>>>>>>> upstream/master

		if (is_receive_register_full())
		{
			receive_register_extract();
			receive_character(get_received_char());
		}
	}
}

/*-------------------------------------------------
    is_tx_enabled
-------------------------------------------------*/
<<<<<<< HEAD
bool i8251_device::is_tx_enabled(void) const
{
        return BIT(m_command , 0) != 0 && m_cts == 0;
=======
bool i8251_device::is_tx_enabled() const
{
	return BIT(m_command , 0) && !m_cts;
>>>>>>> upstream/master
}

/*-------------------------------------------------
    check_for_tx_start
-------------------------------------------------*/
<<<<<<< HEAD
void i8251_device::check_for_tx_start(void)
{
        if (is_tx_enabled() && (m_status & (I8251_STATUS_TX_EMPTY | I8251_STATUS_TX_READY)) == I8251_STATUS_TX_EMPTY) {
                start_tx();
        }
=======
void i8251_device::check_for_tx_start()
{
	if (is_tx_enabled() && (m_status & (I8251_STATUS_TX_EMPTY | I8251_STATUS_TX_READY)) == I8251_STATUS_TX_EMPTY)
		start_tx();
>>>>>>> upstream/master
}

/*-------------------------------------------------
    start_tx
-------------------------------------------------*/
<<<<<<< HEAD
void i8251_device::start_tx(void)
{
=======
void i8251_device::start_tx()
{
	LOG("start_tx %02x\n", m_tx_data);
>>>>>>> upstream/master
	transmit_register_setup(m_tx_data);
	m_status &= ~I8251_STATUS_TX_EMPTY;
	m_status |= I8251_STATUS_TX_READY;
}

/*-------------------------------------------------
    transmit_clock
-------------------------------------------------*/

void i8251_device::transmit_clock()
{
	m_txc_count++;
<<<<<<< HEAD

	if (m_txc_count == m_br_factor)
		m_txc_count = 0;
	else
		return;

        if (is_transmit_register_empty()) {
                if ((m_status & I8251_STATUS_TX_READY) == 0 && (is_tx_enabled() || (m_flags & I8251_DELAYED_TX_EN) != 0)) {
                        start_tx();
                } else {
                        m_status |= I8251_STATUS_TX_EMPTY;
                }
                update_tx_ready();
                update_tx_empty();
        }
        /* if diserial has bits to send, make them so */
        if (!is_transmit_register_empty())
            {
                UINT8 data = transmit_register_get_data_bit();
                m_txd_handler(data);
            }
=======
	if (m_txc_count != m_br_factor)
		return;

	m_txc_count = 0;

	if (is_transmit_register_empty())
	{
		if ((m_status & I8251_STATUS_TX_READY) == 0 && (is_tx_enabled() || (m_flags & I8251_DELAYED_TX_EN) != 0))
			start_tx();
		else
			m_status |= I8251_STATUS_TX_EMPTY;

		update_tx_ready();
		update_tx_empty();
	}

	/* if diserial has bits to send, make them so */
	if (!is_transmit_register_empty())
	{
		uint8_t data = transmit_register_get_data_bit();
		m_txd_handler(data);
	}
>>>>>>> upstream/master

#if 0
	/* hunt mode? */
	/* after each bit has been shifted in, it is compared against the current sync byte */
<<<<<<< HEAD
	if (m_command & (1<<7))
=======
	if (BIT(m_command, 7))
>>>>>>> upstream/master
	{
		/* data matches sync byte? */
		if (m_data == m_sync_bytes[m_sync_byte_offset])
		{
			/* sync byte matches */
			/* update for next sync byte? */
			m_sync_byte_offset++;

			/* do all sync bytes match? */
			if (m_sync_byte_offset == m_sync_byte_count)
			{
				/* ent hunt mode */
<<<<<<< HEAD
				m_command &=~(1<<7);
=======
				m_command &= ~(1<<7);
>>>>>>> upstream/master
			}
		}
		else
		{
			/* if there is no match, reset */
			m_sync_byte_offset = 0;
		}
	}
#endif
}



/*-------------------------------------------------
    update_tx_ready
-------------------------------------------------*/

void i8251_device::update_tx_ready()
{
	/* clear tx ready state */
	int tx_ready;

	/* tx ready output is set if:
	    DB Buffer Empty &
	    CTS is set &
	    Transmit enable is 1
	*/

	tx_ready = is_tx_enabled() && (m_status & I8251_STATUS_TX_READY) != 0;

	m_txrdy_handler(tx_ready);
}



/*-------------------------------------------------
    update_tx_empty
-------------------------------------------------*/

void i8251_device::update_tx_empty()
{
	if (m_status & I8251_STATUS_TX_EMPTY)
	{
		/* tx is in marking state (high) when tx empty! */
		m_txd_handler(1);
	}

	m_txempty_handler((m_status & I8251_STATUS_TX_EMPTY) != 0);
}



//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void i8251_device::device_reset()
{
<<<<<<< HEAD
	LOG(("I8251: Reset\n"));
=======
	LOG("I8251: Reset\n");
>>>>>>> upstream/master

	/* what is the default setup when the 8251 has been reset??? */

	/* i8251 datasheet explains the state of tx pin at reset */
	/* tx is set to 1 */
	m_txd_handler(1);

	/* assumption */
	m_rts_handler(1);
	m_dtr_handler(1);

	transmit_register_reset();
	receive_register_reset();
	m_flags = 0;
	/* expecting mode byte */
	m_flags |= I8251_EXPECTING_MODE;
	/* not expecting a sync byte */
	m_flags &= ~I8251_EXPECTING_SYNC_BYTE;

	/* no character to read by cpu */
	/* transmitter is ready and is empty */
	m_status = I8251_STATUS_TX_EMPTY | I8251_STATUS_TX_READY;
	m_mode_byte = 0;
	m_command = 0;
	m_rx_data = 0;
	m_tx_data = 0;
	m_rxc_count = m_txc_count = 0;
	m_br_factor = 1;

	/* update tx empty pin output */
	update_tx_empty();
	/* update rx ready pin output */
	update_rx_ready();
	/* update tx ready pin output */
	update_tx_ready();
}



/*-------------------------------------------------
    control_w
-------------------------------------------------*/

<<<<<<< HEAD
WRITE8_MEMBER(i8251_device::command_w)
{
	/* command */
	LOG(("I8251: Command byte\n"));

	m_command = data;

	LOG(("Command byte: %02x\n", data));

	if (data & (1<<7))
	{
		LOG(("hunt mode\n"));
	}

	if (data & (1<<5))
	{
		LOG(("/rts set to 0\n"));
	}
	else
	{
		LOG(("/rts set to 1\n"));
	}

	if (data & (1<<2))
	{
		LOG(("receive enable\n"));
	}
	else
	{
		LOG(("receive disable\n"));
	}

	if (data & (1<<1))
	{
		LOG(("/dtr set to 0\n"));
	}
	else
	{
		LOG(("/dtr set to 1\n"));
	}

	if (data & (1<<0))
	{
		LOG(("transmit enable\n"));
	}
	else
	{
                LOG(("transmit disable\n"));
	}
=======
void i8251_device::command_w(uint8_t data)
{
	/* command */
	LOG("I8251: Command byte\n");

	m_command = data;

	LOG("Command byte: %02x\n", data);

	if (BIT(data, 7))
		LOG("hunt mode\n");

	if (BIT(data, 5))
		LOG("/rts set to 0\n");
	else
		LOG("/rts set to 1\n");

	if (BIT(data, 2))
		LOG("receive enable\n");
	else
		LOG("receive disable\n");

	if (BIT(data, 1))
		LOG("/dtr set to 0\n");
	else
		LOG("/dtr set to 1\n");

	if (BIT(data, 0))
		LOG("transmit enable\n");
	else
		LOG("transmit disable\n");
>>>>>>> upstream/master


	/*  bit 7:
	        0 = normal operation
	        1 = hunt mode
	    bit 6:
	        0 = normal operation
	        1 = internal reset
	    bit 5:
	        0 = /RTS set to 1
	        1 = /RTS set to 0
	    bit 4:
	        0 = normal operation
	        1 = reset error flag
	    bit 3:
	        0 = normal operation
	        1 = send break character
	    bit 2:
	        0 = receive disable
	        1 = receive enable
	    bit 1:
	        0 = /DTR set to 1
	        1 = /DTR set to 0
	    bit 0:
	        0 = transmit disable
	        1 = transmit enable
	*/

	m_rts_handler(!BIT(data, 5));
	m_dtr_handler(!BIT(data, 1));

<<<<<<< HEAD
	if (data & (1<<4))
	{
		m_status &= ~(I8251_STATUS_PARITY_ERROR | I8251_STATUS_OVERRUN_ERROR | I8251_STATUS_FRAMING_ERROR);
	}

	if (data & (1<<6))
=======
	if (BIT(data, 4))
		m_status &= ~(I8251_STATUS_PARITY_ERROR | I8251_STATUS_OVERRUN_ERROR | I8251_STATUS_FRAMING_ERROR);

	if (BIT(data, 6))
>>>>>>> upstream/master
	{
		// datasheet says "returns to mode format", not
		// completely resets the chip.  behavior of DEC Rainbow
		// backs this up.
		m_flags |= I8251_EXPECTING_MODE;
	}

<<<<<<< HEAD
        check_for_tx_start();
	update_rx_ready();
	update_tx_ready();
        update_tx_empty();
}

WRITE8_MEMBER(i8251_device::mode_w)
{
	LOG(("I8251: Mode byte\n"));
=======
	check_for_tx_start();
	update_rx_ready();
	update_tx_ready();
	update_tx_empty();
}

void i8251_device::mode_w(uint8_t data)
{
	LOG("I8251: Mode byte = %X\n", data);
>>>>>>> upstream/master

	m_mode_byte = data;

	/* Synchronous or Asynchronous? */
	if ((data & 0x03) != 0)
	{
		/*  Asynchronous

		    bit 7,6: stop bit length
		    0 = inhibit
		    1 = 1 bit
		    2 = 1.5 bits
		    3 = 2 bits
		    bit 5: parity type
		    0 = parity odd
		    1 = parity even
		    bit 4: parity test enable
		    0 = disable
		    1 = enable
		    bit 3,2: character length
		    0 = 5 bits
		    1 = 6 bits
		    2 = 7 bits
		    3 = 8 bits
		    bit 1,0: baud rate factor
		    0 = defines command byte for synchronous or asynchronous
		    1 = x1
		    2 = x16
		    3 = x64
		    */

<<<<<<< HEAD
		LOG(("I8251: Asynchronous operation\n"));

		LOG(("Character length: %d\n", (((data >> 2) & 0x03) + 5)));

		parity_t parity;

		if (data & (1 << 4))
		{
			LOG(("enable parity checking\n"));

			if (data & (1 << 5))
			{
				LOG(("even parity\n"));
=======
		LOG("I8251: Asynchronous operation\n");

		const int data_bits_count = ((data >> 2) & 0x03) + 5;
		LOG("Character length: %d\n", data_bits_count);

		parity_t parity;
		if (BIT(data, 4))
		{
			if (BIT(data, 5))
			{
				LOG("enable parity checking (even parity)\n");
>>>>>>> upstream/master
				parity = PARITY_EVEN;
			}
			else
			{
<<<<<<< HEAD
				LOG(("odd parity\n"));
=======
				LOG("enable parity checking (odd parity)\n");
>>>>>>> upstream/master
				parity = PARITY_ODD;
			}
		}
		else
		{
<<<<<<< HEAD
			LOG(("parity check disabled\n"));
=======
			LOG("parity check disabled\n");
>>>>>>> upstream/master
			parity = PARITY_NONE;
		}

		stop_bits_t stop_bits;
<<<<<<< HEAD

=======
>>>>>>> upstream/master
		switch ((data >> 6) & 0x03)
		{
		case 0:
		default:
			stop_bits = STOP_BITS_0;
<<<<<<< HEAD
			LOG(("stop bit: inhibit\n"));
=======
			LOG("stop bit: inhibit\n");
>>>>>>> upstream/master
			break;

		case 1:
			stop_bits = STOP_BITS_1;
<<<<<<< HEAD
			LOG(("stop bit: 1 bit\n"));
=======
			LOG("stop bit: 1 bit\n");
>>>>>>> upstream/master
			break;

		case 2:
			stop_bits = STOP_BITS_1_5;
<<<<<<< HEAD
			LOG(("stop bit: 1.5 bits\n"));
=======
			LOG("stop bit: 1.5 bits\n");
>>>>>>> upstream/master
			break;

		case 3:
			stop_bits = STOP_BITS_2;
<<<<<<< HEAD
			LOG(("stop bit: 2 bits\n"));
			break;
		}

		int data_bits_count = ((data >> 2) & 0x03) + 5;
=======
			LOG("stop bit: 2 bits\n");
			break;
		}

>>>>>>> upstream/master

		set_data_frame(1, data_bits_count, parity, stop_bits);
		receive_register_reset();

		switch (data & 0x03)
		{
		case 1: m_br_factor = 1; break;
		case 2: m_br_factor = 16; break;
		case 3: m_br_factor = 64; break;
		}

<<<<<<< HEAD
		m_rxc_count = m_txc_count = 0;
=======
		m_txc_count = 0;
>>>>>>> upstream/master

#if 0
		/* data bits */
		m_receive_char_length = (((data >> 2) & 0x03) + 5);

<<<<<<< HEAD
		if (data & (1 << 4))
=======
		if (BIT(data, 4))
>>>>>>> upstream/master
		{
			/* parity */
			m_receive_char_length++;
		}

		/* stop bits */
		m_receive_char_length++;

		m_receive_flags &= ~I8251_TRANSFER_RECEIVE_SYNCHRONISED;
		m_receive_flags |= I8251_TRANSFER_RECEIVE_WAITING_FOR_START_BIT;
#endif
		/* not expecting mode byte now */
		m_flags &= ~I8251_EXPECTING_MODE;
		//              m_status = I8251_STATUS_TX_EMPTY | I8251_STATUS_TX_READY;
	}
	else
	{
		/*  bit 7: Number of sync characters
		        0 = 1 character
		        1 = 2 character
		        bit 6: Synchronous mode
		        0 = Internal synchronisation
		        1 = External synchronisation
		        bit 5: parity type
		        0 = parity odd
		        1 = parity even
		        bit 4: parity test enable
		        0 = disable
		        1 = enable
		        bit 3,2: character length
		        0 = 5 bits
		        1 = 6 bits
		        2 = 7 bits
		        3 = 8 bits
		        bit 1,0 = 0
		        */
<<<<<<< HEAD
		LOG(("I8251: Synchronous operation\n"));
=======
		LOG("I8251: Synchronous operation\n");
>>>>>>> upstream/master

		/* setup for sync byte(s) */
		m_flags |= I8251_EXPECTING_SYNC_BYTE;
		m_sync_byte_offset = 0;
		if (data & 0x07)
		{
			m_sync_byte_count = 1;
		}
		else
		{
			m_sync_byte_count = 2;
		}

	}
}

WRITE8_MEMBER(i8251_device::control_w)
{
	if (m_flags & I8251_EXPECTING_MODE)
	{
		if (m_flags & I8251_EXPECTING_SYNC_BYTE)
		{
<<<<<<< HEAD
			LOG(("I8251: Sync byte\n"));

			LOG(("Sync byte: %02x\n", data));
=======
			LOG("I8251: Sync byte\n");

			LOG("Sync byte: %02x\n", data);
>>>>>>> upstream/master
			/* store sync byte written */
			m_sync_bytes[m_sync_byte_offset] = data;
			m_sync_byte_offset++;

			if (m_sync_byte_offset == m_sync_byte_count)
			{
				/* finished transfering sync bytes, now expecting command */
				m_flags &= ~(I8251_EXPECTING_MODE | I8251_EXPECTING_SYNC_BYTE);
				m_sync_byte_offset = 0;
			//  m_status = I8251_STATUS_TX_EMPTY | I8251_STATUS_TX_READY;
			}
		}
		else
		{
<<<<<<< HEAD
			mode_w(space, offset, data);
=======
			mode_w(data);
>>>>>>> upstream/master
		}
	}
	else
	{
<<<<<<< HEAD
		command_w(space, offset, data);
=======
		command_w(data);
>>>>>>> upstream/master
	}
}



/*-------------------------------------------------
    status_r
-------------------------------------------------*/

READ8_MEMBER(i8251_device::status_r)
{
<<<<<<< HEAD
	UINT8 status = (m_dsr << 7) | m_status;

	LOG(("status: %02x\n", status));
=======
	uint8_t status = (m_dsr << 7) | m_status;

	LOG("status: %02x\n", status);
>>>>>>> upstream/master
	return status;
}



/*-------------------------------------------------
    data_w
-------------------------------------------------*/

WRITE8_MEMBER(i8251_device::data_w)
{
	m_tx_data = data;

<<<<<<< HEAD
        LOG(("data_w %02x\n" , data));
=======
		LOG("data_w %02x\n" , data);
>>>>>>> upstream/master

	/* writing clears */
	m_status &=~I8251_STATUS_TX_READY;
	update_tx_ready();

<<<<<<< HEAD
        // Store state of tx enable when writing to DB buffer
        if (is_tx_enabled()) {
                m_flags |= I8251_DELAYED_TX_EN;
        } else {
                m_flags &= ~I8251_DELAYED_TX_EN;
        }

        check_for_tx_start();
=======
		// Store state of tx enable when writing to DB buffer
		if (is_tx_enabled()) {
				m_flags |= I8251_DELAYED_TX_EN;
		} else {
				m_flags &= ~I8251_DELAYED_TX_EN;
		}

		check_for_tx_start();
>>>>>>> upstream/master

	/* if transmitter is active, then tx empty will be signalled */

	update_tx_ready();
	update_tx_empty();
}



/*-------------------------------------------------
    receive_character - called when last
    bit of data has been received
-------------------------------------------------*/

<<<<<<< HEAD
void i8251_device::receive_character(UINT8 ch)
{
=======
void i8251_device::receive_character(uint8_t ch)
{
	LOG("receive_character %02x\n", ch);

>>>>>>> upstream/master
	m_rx_data = ch;

	/* char has not been read and another has arrived! */
	if (m_status & I8251_STATUS_RX_READY)
<<<<<<< HEAD
	{
		m_status |= I8251_STATUS_OVERRUN_ERROR;
	}
=======
		m_status |= I8251_STATUS_OVERRUN_ERROR;

>>>>>>> upstream/master
	m_status |= I8251_STATUS_RX_READY;

	update_rx_ready();
}



/*-------------------------------------------------
    data_r - read data
-------------------------------------------------*/

READ8_MEMBER(i8251_device::data_r)
{
<<<<<<< HEAD
	LOG(("read data: %02x, STATUS=%02x\n",m_rx_data,m_status));
=======
	LOG("read data: %02x, STATUS=%02x\n",m_rx_data,m_status);
>>>>>>> upstream/master
	/* reading clears */
	m_status &= ~I8251_STATUS_RX_READY;

	update_rx_ready();
	return m_rx_data;
}


<<<<<<< HEAD
void i8251_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	device_serial_interface::device_timer(timer, id, param, ptr);
}


=======
>>>>>>> upstream/master
WRITE_LINE_MEMBER(i8251_device::write_rxd)
{
	m_rxd = state;
//  device_serial_interface::rx_w(state);
}

WRITE_LINE_MEMBER(i8251_device::write_cts)
{
	m_cts = state;

<<<<<<< HEAD
        check_for_tx_start();
        update_tx_ready();
        update_tx_empty();
=======
	check_for_tx_start();
	update_tx_ready();
	update_tx_empty();
>>>>>>> upstream/master
}

WRITE_LINE_MEMBER(i8251_device::write_dsr)
{
	m_dsr = !state;
}

WRITE_LINE_MEMBER(i8251_device::write_rxc)
{
	if (m_rxc != state)
	{
		m_rxc = state;

		if (m_rxc)
			receive_clock();
	}
}

WRITE_LINE_MEMBER(i8251_device::write_txc)
{
	if (m_txc != state)
	{
		m_txc = state;

		if (!m_txc)
			transmit_clock();
	}
}
<<<<<<< HEAD
=======

WRITE8_MEMBER(v53_scu_device::command_w)
{
	i8251_device::command_w(data);
}

WRITE8_MEMBER(v53_scu_device::mode_w)
{
	i8251_device::mode_w(data);
}
>>>>>>> upstream/master
