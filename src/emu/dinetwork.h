// license:BSD-3-Clause
// copyright-holders:Carl, Miodrag Milanovic
<<<<<<< HEAD
#ifndef __DINETWORK_H__
#define __DINETWORK_H__
=======
#ifndef MAME_EMU_DINETWORK_H
#define MAME_EMU_DINETWORK_H
>>>>>>> upstream/master

class osd_netdev;

class device_network_interface : public device_interface
{
public:
	device_network_interface(const machine_config &mconfig, device_t &device, float bandwidth);
	virtual ~device_network_interface();

	void set_interface(int id);
	void set_promisc(bool promisc);
	void set_mac(const char *mac);

<<<<<<< HEAD
	const char *get_mac() { return m_mac; }
	bool get_promisc() { return m_promisc; }
	int get_interface() { return m_intf; }

	int send(UINT8 *buf, int len) const;
	virtual void recv_cb(UINT8 *buf, int len);
=======
	const char *get_mac() const { return m_mac; }
	bool get_promisc() const { return m_promisc; }
	int get_interface() const { return m_intf; }

	int send(u8 *buf, int len) const;
	virtual void recv_cb(u8 *buf, int len);
>>>>>>> upstream/master

protected:
	bool m_promisc;
	char m_mac[6];
	float m_bandwidth;
<<<<<<< HEAD
	auto_pointer<class osd_netdev> m_dev;
=======
	std::unique_ptr<osd_netdev> m_dev;
>>>>>>> upstream/master
	int m_intf;
};


// iterator
typedef device_interface_iterator<device_network_interface> network_interface_iterator;

<<<<<<< HEAD
#endif
=======
#endif // MAME_EMU_DINETWORK_H
>>>>>>> upstream/master
