// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
#include "emu.h"
#include "h8_port.h"

<<<<<<< HEAD
const device_type H8_PORT = &device_creator<h8_port_device>;

h8_port_device::h8_port_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, H8_PORT, "H8 digital port", tag, owner, clock, "h8_digital_port", __FILE__),
=======
DEFINE_DEVICE_TYPE(H8_PORT, h8_port_device, "h8_digital_port", "H8 digital port")

h8_port_device::h8_port_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, H8_PORT, tag, owner, clock),
>>>>>>> upstream/master
	cpu(*this, DEVICE_SELF_OWNER), io(nullptr), address(0), default_ddr(0), ddr(0), pcr(0), odr(0), mask(0), dr(0), last_output(0)
{
}

<<<<<<< HEAD
void h8_port_device::set_info(int _address, UINT8 _default_ddr, UINT8 _mask)
=======
void h8_port_device::set_info(int _address, uint8_t _default_ddr, uint8_t _mask)
>>>>>>> upstream/master
{
	address = 2*_address;
	default_ddr = _default_ddr;
	mask = _mask;
}

WRITE8_MEMBER(h8_port_device::ddr_w)
{
<<<<<<< HEAD
	//  logerror("%s: ddr_w %02x\n", tag(), data);
=======
	//  logerror("ddr_w %02x\n", data);
>>>>>>> upstream/master
	ddr = data;
	update_output();
}

WRITE8_MEMBER(h8_port_device::dr_w)
{
<<<<<<< HEAD
	//  logerror("%s: dr_w %02x\n", tag(), data);
=======
	//  logerror("dr_w %02x\n", data);
>>>>>>> upstream/master
	dr = data;
	update_output();
}

READ8_MEMBER(h8_port_device::dr_r)
{
<<<<<<< HEAD
	//  logerror("%s: dr_r %02x\n", tag(), (dr | mask) & 0xff);
=======
	//  logerror("dr_r %02x\n", (dr | mask) & 0xff);
>>>>>>> upstream/master
	return dr | mask;
}

READ8_MEMBER(h8_port_device::port_r)
{
<<<<<<< HEAD
	UINT8 res = mask | (dr & ddr);
	if((ddr & ~mask) != UINT8(~mask))
		res |= io->read_word(address) & ~ddr;

	//  logerror("%s: port_r %02x (%02x %02x)\n", tag(), res, ddr & ~mask, UINT8(~mask));
=======
	uint8_t res = mask | (dr & ddr);
	if((ddr & ~mask) != uint8_t(~mask))
		res |= io->read_word(address) & ~ddr;

	//  logerror("port_r %02x (%02x %02x)\n", res, ddr & ~mask, uint8_t(~mask));
>>>>>>> upstream/master
	return res;
}

WRITE8_MEMBER(h8_port_device::pcr_w)
{
<<<<<<< HEAD
	logerror("%s: pcr_w %02x\n", tag(), data);
=======
	logerror("pcr_w %02x\n", data);
>>>>>>> upstream/master
	pcr = data;
}

READ8_MEMBER(h8_port_device::pcr_r)
{
<<<<<<< HEAD
	logerror("%s: dr_r %02x\n", tag(), (pcr | mask) & 0xff);
=======
	logerror("dr_r %02x\n", (pcr | mask) & 0xff);
>>>>>>> upstream/master
	return pcr | mask;
}

WRITE8_MEMBER(h8_port_device::odr_w)
{
<<<<<<< HEAD
	logerror("%s: odr_w %02x\n", tag(), data);
=======
	logerror("odr_w %02x\n", data);
>>>>>>> upstream/master
	odr = data;
}

READ8_MEMBER(h8_port_device::odr_r)
{
<<<<<<< HEAD
	logerror("%s: odr_r %02x\n", tag(), (odr | mask) & 0xff);
=======
	logerror("odr_r %02x\n", (odr | mask) & 0xff);
>>>>>>> upstream/master
	return odr | ~mask;
}

void h8_port_device::update_output()
{
<<<<<<< HEAD
	UINT8 res = dr & ddr & ~mask;
=======
	uint8_t res = dr & ddr & ~mask;
>>>>>>> upstream/master
	if(res != last_output) {
		last_output = res;
		io->write_word(address, res);
	}
}

void h8_port_device::device_start()
{
	io = &cpu->space(AS_IO);
	save_item(NAME(ddr));
	save_item(NAME(dr));
	save_item(NAME(pcr));
	save_item(NAME(odr));
	save_item(NAME(last_output));
	last_output = 0;
}

void h8_port_device::device_reset()
{
	dr = 0;
	ddr = default_ddr;
	pcr = 0;
	odr = 0;
	update_output();
}
