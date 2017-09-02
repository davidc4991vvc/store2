// license:BSD-3-Clause
// copyright-holders:F.Ulivi
/***************************************************************************

    dipty.h

    Device PTY interface

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __EMU_H__
#error Dont include this file directly; include emu.h instead.
#endif

#ifndef __DIPTY_H__
#define __DIPTY_H__
=======
#ifndef MAME_EMU_DIPTY_H
#define MAME_EMU_DIPTY_H
>>>>>>> upstream/master

class device_pty_interface : public device_interface
{
public:
<<<<<<< HEAD
		// construction/destruction
		device_pty_interface(const machine_config &mconfig, device_t &device);
		virtual ~device_pty_interface();

		bool open(void);
		void close(void);

		bool is_open(void) const;

		ssize_t read(UINT8 *rx_chars , size_t count) const;
		void write(UINT8 tx_char) const;

		bool is_slave_connected(void) const;

		const char *slave_name(void) const;

protected:
		osd_file *m_pty_master;
		std::string m_slave_name;
		bool m_opened;
=======
	// construction/destruction
	device_pty_interface(const machine_config &mconfig, device_t &device);
	virtual ~device_pty_interface();

	bool open();
	void close();

	bool is_open() const;

	ssize_t read(u8 *rx_chars , size_t count) const;
	void write(u8 tx_char) const;

	bool is_slave_connected() const;

	const char *slave_name() const;

protected:
	osd_file::ptr m_pty_master;
	std::string m_slave_name;
	bool m_opened;
>>>>>>> upstream/master
};

// iterator
typedef device_interface_iterator<device_pty_interface> pty_interface_iterator;

<<<<<<< HEAD
#endif  /* __DIPTY_H__ */
=======
#endif // MAME_EMU_DIPTY_H
>>>>>>> upstream/master
