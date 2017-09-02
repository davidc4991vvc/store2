// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#include "jvs13551.h"

const device_type SEGA_837_13551 = &device_creator<sega_837_13551>;

WRITE_LINE_MEMBER(sega_837_13551::jvs13551_coin_1_w)
=======
#include "emu.h"
#include "jvs13551.h"

#include "cpu/tlcs90/tlcs90.h"

DEFINE_DEVICE_TYPE(SEGA_837_13551, sega_837_13551_device, "jvs13551", "Sega 837-13551 I/O Board")

WRITE_LINE_MEMBER(sega_837_13551_device::jvs13551_coin_1_w)
>>>>>>> upstream/master
{
	if(state)
		inc_coin(0);
}

<<<<<<< HEAD
WRITE_LINE_MEMBER(sega_837_13551::jvs13551_coin_2_w)
=======
WRITE_LINE_MEMBER(sega_837_13551_device::jvs13551_coin_2_w)
>>>>>>> upstream/master
{
	if(state)
		inc_coin(1);
}

static INPUT_PORTS_START(sega_837_13551_coins)
	PORT_START("COINS")
<<<<<<< HEAD
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_COIN1) PORT_WRITE_LINE_DEVICE_MEMBER(DEVICE_SELF, sega_837_13551, jvs13551_coin_1_w)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_COIN2) PORT_WRITE_LINE_DEVICE_MEMBER(DEVICE_SELF, sega_837_13551, jvs13551_coin_2_w)
=======
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_COIN1) PORT_WRITE_LINE_DEVICE_MEMBER(DEVICE_SELF, sega_837_13551_device, jvs13551_coin_1_w)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_COIN2) PORT_WRITE_LINE_DEVICE_MEMBER(DEVICE_SELF, sega_837_13551_device, jvs13551_coin_2_w)
>>>>>>> upstream/master
INPUT_PORTS_END

ROM_START( jvs13551 )
	// TMP90PH44N firmwares
<<<<<<< HEAD
	ROM_REGION( 0x8000, "jvs13551", ROMREGION_ERASE )
	// Sega 838-13683-93
	ROM_LOAD( "sp5001.bin",   0x0000, 0x8000, CRC(2f17e21a) SHA1(ac227ef3ca52ef17321bd60e435dba147645d8b8))
	// Sega 838-13683-93 Rev.B
	ROM_LOAD( "sp5001-b.bin", 0x0000, 0x8000, CRC(121693cd) SHA1(c9834aca671aff5e283ac708788c2a0f4a5bdecc))
	// Sega 838-13683-02
	ROM_LOAD( "sp5002-a.bin", 0x0000, 0x8000, CRC(a088df8c) SHA1(8237e9b18b8367d3f5b99b8f29c528a55c2e0fbf))
	// Sega 837-13551-92 0007 Type1
	ROM_LOAD( "315-6215.bin", 0x0000, 0x8000, CRC(d7c97e40) SHA1(b1ae8db332f869c4fdbbae15967baeca0bc7f57d))
ROM_END

const rom_entry *sega_837_13551::device_rom_region() const
=======
	ROM_REGION( 0x4000, "iomcu", ROMREGION_ERASE )
	// Sega 838-13683-93
	ROM_LOAD( "sp5001.bin",   0x0000, 0x4000, CRC(3456c8cc) SHA1(f3b66ab1d2eab32e97b46077e3ed2ab5b2982325))
	// Sega 838-13683-93 Rev.B
	ROM_LOAD( "sp5001-b.bin", 0x0000, 0x4000, CRC(28b5fb84) SHA1(8784024548d24b6a43057f06de1d53ce3a34eb12))
	// Sega 838-13683-02
	ROM_LOAD( "sp5002-a.bin", 0x0000, 0x4000, CRC(72983a0f) SHA1(aa13276347bc643ef93e81e9ab7c905deb16c415))
	// Sega 837-13551-92 0007 Type1
	ROM_LOAD( "315-6215.bin", 0x0000, 0x4000, CRC(98202738) SHA1(8c4dc85438298e31e25f69542804a78ff0e20962))
ROM_END

const tiny_rom_entry *sega_837_13551_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME(jvs13551);
}

<<<<<<< HEAD
void sega_837_13551::static_set_port_tag(device_t &device, int port, const char *tag)
{
	sega_837_13551 &ctrl = downcast<sega_837_13551 &>(device);
	ctrl.port_tag[port] = tag;
}

ioport_constructor sega_837_13551::device_input_ports() const
=======
void sega_837_13551_device::static_set_port_tag(device_t &device, int port, const char *tag)
{
	sega_837_13551_device &ctrl = downcast<sega_837_13551_device &>(device);
	ctrl.port_tag[port] = tag;
}

MACHINE_CONFIG_MEMBER(sega_837_13551_device::device_add_mconfig)
	MCFG_CPU_ADD("iomcu", TMP90PH44, 10000000) // unknown clock
MACHINE_CONFIG_END

ioport_constructor sega_837_13551_device::device_input_ports() const
>>>>>>> upstream/master
{
	return INPUT_PORTS_NAME(sega_837_13551_coins);
}

<<<<<<< HEAD
sega_837_13551::sega_837_13551(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) : jvs_device(mconfig, SEGA_837_13551, "Sega 837-13551 I/O Board", tag, owner, clock, "jvs13551", __FILE__)
=======
sega_837_13551_device::sega_837_13551_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) : jvs_device(mconfig, SEGA_837_13551, tag, owner, clock)
>>>>>>> upstream/master
{
	memset(port_tag, 0, sizeof(port_tag));
}

<<<<<<< HEAD
const char *sega_837_13551::device_id()
=======
const char *sega_837_13551_device::device_id()
>>>>>>> upstream/master
{
	return "SEGA ENTERPRISES,LTD.;I/O BD JVS;837-13551";
}

<<<<<<< HEAD
UINT8 sega_837_13551::command_format_version()
=======
uint8_t sega_837_13551_device::command_format_version()
>>>>>>> upstream/master
{
	return 0x11;
}

<<<<<<< HEAD
UINT8 sega_837_13551::jvs_standard_version()
=======
uint8_t sega_837_13551_device::jvs_standard_version()
>>>>>>> upstream/master
{
	return 0x20;
}

<<<<<<< HEAD
UINT8 sega_837_13551::comm_method_version()
=======
uint8_t sega_837_13551_device::comm_method_version()
>>>>>>> upstream/master
{
	return 0x10;
}

<<<<<<< HEAD
void sega_837_13551::device_start()
=======
void sega_837_13551_device::device_start()
>>>>>>> upstream/master
{
	jvs_device::device_start();
	for (int i = 0; i < ARRAY_LENGTH(port_tag); i++)
	{
		port[i] = ioport(port_tag[i]);
	}
	save_item(NAME(coin_counter));
}

<<<<<<< HEAD
void sega_837_13551::device_reset()
=======
void sega_837_13551_device::device_reset()
>>>>>>> upstream/master
{
	jvs_device::device_reset();
	coin_counter[0] = 0;
	coin_counter[1] = 0;
}

<<<<<<< HEAD
void sega_837_13551::inc_coin(int coin)
=======
void sega_837_13551_device::inc_coin(int coin)
>>>>>>> upstream/master
{
	coin_counter[coin]++;
	if(coin_counter[coin] == 16384)
		coin_counter[coin] = 0;
}


<<<<<<< HEAD
void sega_837_13551::function_list(UINT8 *&buf)
=======
void sega_837_13551_device::function_list(uint8_t *&buf)
>>>>>>> upstream/master
{
	// SW input - 2 players, 13 bits
	*buf++ = 0x01; *buf++ = 2; *buf++ = 13; *buf++ = 0;

	// Coin input - 2 slots
	*buf++ = 0x02; *buf++ = 2; *buf++ = 0; *buf++ = 0;

	// Analog input - 8 channels
	*buf++ = 0x03; *buf++ = 8; *buf++ = 16; *buf++ = 0;

	// Driver out - 6 channels
	*buf++ = 0x12; *buf++ = 6; *buf++ = 0; *buf++ = 0;
}

<<<<<<< HEAD
bool sega_837_13551::coin_counters(UINT8 *&buf, UINT8 count)
=======
bool sega_837_13551_device::coin_counters(uint8_t *&buf, uint8_t count)
>>>>>>> upstream/master
{
	if(count > 2)
		return false;

	*buf++ = coin_counter[0] >> 8; *buf++ = coin_counter[0];

<<<<<<< HEAD
	if(count > 1)
		*buf++ = coin_counter[1] >> 8; *buf++ = coin_counter[1];
=======
	if(count > 1) {
		*buf++ = coin_counter[1] >> 8; *buf++ = coin_counter[1];
	}
>>>>>>> upstream/master

	return true;
}

<<<<<<< HEAD
bool sega_837_13551::coin_add(UINT8 slot, INT32 count)
=======
bool sega_837_13551_device::coin_add(uint8_t slot, int32_t count)
>>>>>>> upstream/master
{
	if(slot < 1 || slot > 2)
		return false;

	coin_counter[slot-1] += count;

	return true;
}

<<<<<<< HEAD
bool sega_837_13551::switches(UINT8 *&buf, UINT8 count_players, UINT8 bytes_per_switch)
=======
bool sega_837_13551_device::switches(uint8_t *&buf, uint8_t count_players, uint8_t bytes_per_switch)
>>>>>>> upstream/master
{
	if(count_players > 2 || bytes_per_switch > 2)
		return false;

	*buf++ = port[0] ? port[0]->read() : 0;
	for(int i=0; i<count_players; i++) {
<<<<<<< HEAD
		UINT32 val = port[1+i] ? port[1+i]->read() : 0;
=======
		uint32_t val = port[1+i] ? port[1+i]->read() : 0;
>>>>>>> upstream/master
		for(int j=0; j<bytes_per_switch; j++)
			*buf++ = val >> ((1-j) << 3);
	}
	return true;

}

<<<<<<< HEAD
bool sega_837_13551::analogs(UINT8 *&buf, UINT8 count)
=======
bool sega_837_13551_device::analogs(uint8_t *&buf, uint8_t count)
>>>>>>> upstream/master
{
	if(count > 8)
		return false;
	for(int i=0; i<count; i++) {
<<<<<<< HEAD
		UINT16 val = port[3+i] ? port[3+i]->read() : 0x8000;
=======
		uint16_t val = port[3+i] ? port[3+i]->read() : 0x8000;
>>>>>>> upstream/master
		*buf++ = val >> 8;
		*buf++ = val;
	}
	return true;
}

<<<<<<< HEAD
bool sega_837_13551::swoutputs(UINT8 count, const UINT8 *vals)
=======
bool sega_837_13551_device::swoutputs(uint8_t count, const uint8_t *vals)
>>>>>>> upstream/master
{
	// WARNING! JVS standard have reversed bits count order
	// so "board have 6 output bits" means 6 MSB bits is used, the same rules for input too
	if(count > 1)
		return false;
	jvs_outputs = vals[0] & 0xfc;
	logerror("837-13551: output %02x\n", jvs_outputs);
	if (port[11])
	{
		port[11]->write(jvs_outputs, 0xfc);
	}
	return true;
}

<<<<<<< HEAD
bool sega_837_13551::swoutputs(UINT8 id, UINT8 val)
=======
bool sega_837_13551_device::swoutputs(uint8_t id, uint8_t val)
>>>>>>> upstream/master
{
	if(id > 6)
		return false;
	handle_output(port[11], id, val);
	logerror("837-13551: output %d, %d\n", id, val);
	return true;
}
