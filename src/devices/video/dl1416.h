// license:GPL-2.0+
<<<<<<< HEAD
// copyright-holders:Dirk Best
=======
// copyright-holders:Dirk Best, Vas Crabb
>>>>>>> upstream/master
/*****************************************************************************
 *
 *  DL1416
 *
 * 4-Digit 16-Segment Alphanumeric Intelligent Display
 * with Memory/Decoder/Driver
 *
 * See video/dl1416.c for more info
 *
 ****************************************************************************/

<<<<<<< HEAD
#ifndef DL1416_H_
#define DL1416_H_
=======
#ifndef MAME_VIDEO_DL1416_H
#define MAME_VIDEO_DL1416_H

#pragma once


/***************************************************************************
    DEVICE TYPES
***************************************************************************/

extern device_type const DL1414T;
extern device_type const DL1416B;
extern device_type const DL1416T;
>>>>>>> upstream/master


/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

<<<<<<< HEAD
=======
#define MCFG_DL1414_UPDATE_HANDLER(_devcb) \
	devcb = &dl1414_device::set_update_handler(*device, DEVCB_##_devcb);

>>>>>>> upstream/master
#define MCFG_DL1416_UPDATE_HANDLER(_devcb) \
	devcb = &dl1416_device::set_update_handler(*device, DEVCB_##_devcb);


/***************************************************************************
<<<<<<< HEAD
    FUNCTION PROTOTYPES
***************************************************************************/

/* device get info callback */
class dl1416_device : public device_t
{
public:
	dl1416_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	~dl1416_device() {}

	template<class _Object> static devcb_base &set_update_handler(device_t &device, _Object object) { return downcast<dl1416_device &>(device).m_update.set_callback(object); }

	/* inputs */
	DECLARE_WRITE_LINE_MEMBER( wr_w ); /* write enable */
	DECLARE_WRITE_LINE_MEMBER( ce_w ); /* chip enable */
	DECLARE_WRITE_LINE_MEMBER( cu_w ); /* cursor enable */
	DECLARE_WRITE8_MEMBER( data_w );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

private:
	// internal state
	int m_write_enable;
	int m_chip_enable;
	int m_cursor_enable;
	devcb_write16 m_update;

	UINT16 m_digit_ram[4]; // holds the digit code for each position
	UINT8 m_cursor_state[4]; // holds the cursor state for each position, 0=off, 1=on
};

class dl1416b_device : public dl1416_device
{
public:
	dl1416b_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

extern const device_type DL1416B;

class dl1416t_device : public dl1416_device
{
public:
	dl1416t_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

extern const device_type DL1416T;


#endif /* DL1416_H_ */
=======
    TYPE DECLARATIONS
***************************************************************************/

class dl1414_device : public device_t
{
public:
	template <typename Object> static devcb_base &set_update_handler(device_t &device, Object &&cb)
	{ return downcast<dl1414_device &>(device).m_update_cb.set_callback(std::forward<Object>(cb)); }

	// signal-level interface
	DECLARE_WRITE_LINE_MEMBER(wr_w); // write strobe (rising edge)
	DECLARE_WRITE_LINE_MEMBER(ce_w); // chip enable (active low)
	void addr_w(uint8_t state);
	void data_w(uint8_t state);

	// bus interface - still requires cu_w to set cursor enable state
	virtual DECLARE_WRITE8_MEMBER(bus_w);

protected:
	dl1414_device(
			machine_config const &mconfig,
			device_type type,
			char const *tag,
			device_t *owner,
			uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	void set_cursor_state(offs_t offset, bool state);
	virtual uint16_t translate(u8 digit, bool cursor) const = 0;

private:
	devcb_write16 m_update_cb;

	// internal state
	uint8_t m_digit_ram[4]; // holds the digit code for each position
	bool m_cursor_state[4]; // holds the cursor state for each position

	// input line state
	bool m_wr_in;
	bool m_ce_in, m_ce_latch;
	uint8_t m_addr_in, m_addr_latch;
	uint8_t m_data_in;
};

class dl1416_device : public dl1414_device
{
public:
	DECLARE_WRITE_LINE_MEMBER(cu_w); // cursor enable (active low)

protected:
	dl1416_device(
			machine_config const &mconfig,
			device_type type,
			char const *tag,
			device_t *owner,
			uint32_t clock);

	// device-level overrides
	virtual void device_start() override;

	bool cu_in() const { return m_cu_in; }

private:
	// input line state
	bool m_cu_in;
};

#endif // MAME_VIDEO_DL1416_H
>>>>>>> upstream/master
