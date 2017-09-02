// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore 9060/9090 Hard Disk Drive emulation

**********************************************************************/

/*

    Use the CHDMAN utility to create a 5MB image for D9060:

    $ chdman createhd -o tm602s.chd -chs 153,4,32 -ss 256

    or a 10MB image for D9090:

    $ chdman createhd -o tm603s.chd -chs 153,6,32 -ss 256

    Start the PET emulator with the D9060 attached on the IEEE-488 bus,
    with the new CHD mounted:

    $ mess pet8032 -ieee8 d9060 -hard tm602s.chd
    $ mess pet8032 -ieee8 d9090 -hard tm603s.chd

    Enter 'HEADER "LABEL",D0,I01' to format the hard drive.
    Wait up to 1 hour and 20 minutes.

*/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "d9060.h"
#include "bus/scsi/d9060hd.h"



//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define M6502_DOS_TAG   "7e"
#define M6532_0_TAG     "7f"
#define M6532_1_TAG     "7g"

#define M6502_HDC_TAG   "4a"
#define M6522_TAG       "4b"

#define AM2910_TAG      "9d"

#define SASIBUS_TAG     "sasi"

enum
{
	LED_POWER = 0,
	LED_READY,
	LED_ERROR
};



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type D9060 = &device_creator<d9060_t>;
const device_type D9090 = &device_creator<d9090_t>;
=======
DEFINE_DEVICE_TYPE(D9060, d9060_device, "d9060", "Commodore D9060")
DEFINE_DEVICE_TYPE(D9090, d9090_device, "d9090", "Commodore D9090")
>>>>>>> upstream/master


//-------------------------------------------------
//  ROM( d9060 )
//-------------------------------------------------

ROM_START( d9060 )
	ROM_REGION( 0x4000, M6502_DOS_TAG, 0 )
	ROM_DEFAULT_BIOS("rc")
	ROM_SYSTEM_BIOS( 0, "ra", "Revision A" )
	ROMX_LOAD( "300516-001.7c", 0x0000, 0x2000, NO_DUMP, ROM_BIOS(1) )
	ROMX_LOAD( "300517-001.7d", 0x2000, 0x2000, CRC(566df630) SHA1(b1602dfff408b165ee52a6a4ca3e2ec27e689ba9), ROM_BIOS(1) )
	ROM_SYSTEM_BIOS( 1, "rb", "Revision B" )
	ROMX_LOAD( "300516-002.7c", 0x0000, 0x2000, CRC(2d758a14) SHA1(c959cc9dde84fc3d64e95e58a0a096a26d8107fd), ROM_BIOS(2) )
	ROMX_LOAD( "300517-002.7d", 0x2000, 0x2000, CRC(f0382bc3) SHA1(0b0a8dc520f5b41ffa832e4a636b3d226ccbb7f1), ROM_BIOS(2) )
	ROM_SYSTEM_BIOS( 2, "rc", "Revision C" )
	ROMX_LOAD( "300516-003.7c", 0x0000, 0x2000, CRC(d6a3e88f) SHA1(bb1ddb5da94a86266012eca54818aa21dc4cef6a), ROM_BIOS(3) )
	ROMX_LOAD( "300517-003.7d", 0x2000, 0x2000, CRC(2a9ad4ad) SHA1(4c17d014de48c906871b9b6c7d037d8736b1fd52), ROM_BIOS(3) )

	ROM_REGION( 0x800, M6502_HDC_TAG, 0 )
	ROM_LOAD( "300515-001.4c", 0x000, 0x800, CRC(99e096f7) SHA1(a3d1deb27bf5918b62b89c27fa3e488eb8f717a4) ) // Revision A
	ROM_LOAD( "300515-002.4c", 0x000, 0x800, CRC(49adf4fb) SHA1(59dafbd4855083074ba8dc96a04d4daa5b76e0d6) ) // Revision B

<<<<<<< HEAD
	ROM_REGION( 0x5000, AM2910_TAG, 0 )
	ROM_LOAD( "441.5b", 0x0000, 0x1000, NO_DUMP ) // 82S137
	ROM_LOAD( "442.6b", 0x1000, 0x1000, NO_DUMP ) // 82S137
	ROM_LOAD( "573.7b", 0x2000, 0x1000, NO_DUMP ) // 82S137
	ROM_LOAD( "444.8b", 0x3000, 0x1000, NO_DUMP ) // 82S137
	ROM_LOAD( "445.9b", 0x4000, 0x1000, NO_DUMP ) // 82S137
=======
	ROM_REGION( 0x1400, AM2910_TAG, 0 )
	ROM_LOAD( "44_1.5b", 0x0000, 0x0400, CRC(67a49dd3) SHA1(be39f55bc0ff9a508ec55224c52549856ad3270a) ) // 82S137
	ROM_LOAD( "44_2.6b", 0x0400, 0x0400, CRC(f6d1bdbc) SHA1(bca7a96a60144c36eff1124485ec26df7cfa8143) ) // 82S137
	ROM_LOAD( "44_3.7b", 0x0800, 0x0400, CRC(68af3a1f) SHA1(d3823a0d23e828a2dff6d89211fbcd7034112298) ) // 82S137
	ROM_LOAD( "44_4.8b", 0x0c00, 0x0400, CRC(a767b1dc) SHA1(fff11b662c74040981822ccdcc8cbd0e22b517a9) ) // 82S137
	ROM_LOAD( "44_5.9b", 0x1000, 0x0400, CRC(85743073) SHA1(95a48835bc2bd1c79fb1a63778de3807fb731ac6) ) // 82S137
>>>>>>> upstream/master
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *d9060_base_t::device_rom_region() const
=======
const tiny_rom_entry *d9060_device_base::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( d9060 );
}


//-------------------------------------------------
//  ADDRESS_MAP( d9060_main_mem )
//-------------------------------------------------

<<<<<<< HEAD
static ADDRESS_MAP_START( d9060_main_mem, AS_PROGRAM, 8, d9060_base_t )
	AM_RANGE(0x0000, 0x007f) AM_MIRROR(0x0100) AM_DEVICE(M6532_0_TAG, mos6532_t, ram_map)
	AM_RANGE(0x0080, 0x00ff) AM_MIRROR(0x0100) AM_DEVICE(M6532_1_TAG, mos6532_t, ram_map)
	AM_RANGE(0x0200, 0x021f) AM_MIRROR(0x0d60) AM_DEVICE(M6532_0_TAG, mos6532_t, io_map)
	AM_RANGE(0x0280, 0x029f) AM_MIRROR(0x0d60) AM_DEVICE(M6532_1_TAG, mos6532_t, io_map)
=======
static ADDRESS_MAP_START( d9060_main_mem, AS_PROGRAM, 8, d9060_device_base )
	AM_RANGE(0x0000, 0x007f) AM_MIRROR(0x0100) AM_DEVICE(M6532_0_TAG, mos6532_new_device, ram_map)
	AM_RANGE(0x0080, 0x00ff) AM_MIRROR(0x0100) AM_DEVICE(M6532_1_TAG, mos6532_new_device, ram_map)
	AM_RANGE(0x0200, 0x021f) AM_MIRROR(0x0d60) AM_DEVICE(M6532_0_TAG, mos6532_new_device, io_map)
	AM_RANGE(0x0280, 0x029f) AM_MIRROR(0x0d60) AM_DEVICE(M6532_1_TAG, mos6532_new_device, io_map)
>>>>>>> upstream/master
	AM_RANGE(0x1000, 0x13ff) AM_MIRROR(0x0c00) AM_RAM AM_SHARE("share1")
	AM_RANGE(0x2000, 0x23ff) AM_MIRROR(0x0c00) AM_RAM AM_SHARE("share2")
	AM_RANGE(0x3000, 0x33ff) AM_MIRROR(0x0c00) AM_RAM AM_SHARE("share3")
	AM_RANGE(0x4000, 0x43ff) AM_MIRROR(0x0c00) AM_RAM AM_SHARE("share4")
	AM_RANGE(0xc000, 0xffff) AM_ROM AM_REGION(M6502_DOS_TAG, 0)
ADDRESS_MAP_END


//-------------------------------------------------
//  ADDRESS_MAP( d9060_hdc_mem )
//-------------------------------------------------

<<<<<<< HEAD
static ADDRESS_MAP_START( d9060_hdc_mem, AS_PROGRAM, 8, d9060_base_t )
	ADDRESS_MAP_GLOBAL_MASK(0x1fff)
	AM_RANGE(0x0000, 0x007f) AM_MIRROR(0x300) AM_RAM
	AM_RANGE(0x0080, 0x008f) AM_MIRROR(0x380) AM_DEVREADWRITE(M6522_TAG, via6522_device, read, write)
=======
static ADDRESS_MAP_START( d9060_hdc_mem, AS_PROGRAM, 8, d9060_device_base )
	ADDRESS_MAP_GLOBAL_MASK(0x1fff)
	AM_RANGE(0x0000, 0x007f) AM_MIRROR(0x300) AM_RAM
	AM_RANGE(0x0080, 0x008f) AM_MIRROR(0x370) AM_DEVREADWRITE(M6522_TAG, via6522_device, read, write)
>>>>>>> upstream/master
	AM_RANGE(0x0400, 0x07ff) AM_RAM AM_SHARE("share1")
	AM_RANGE(0x0800, 0x0bff) AM_RAM AM_SHARE("share2")
	AM_RANGE(0x0c00, 0x0fff) AM_RAM AM_SHARE("share3")
	AM_RANGE(0x1000, 0x13ff) AM_RAM AM_SHARE("share4")
	AM_RANGE(0x1800, 0x1fff) AM_ROM AM_REGION(M6502_HDC_TAG, 0)
ADDRESS_MAP_END


//-------------------------------------------------
//  riot6532 0
//-------------------------------------------------

<<<<<<< HEAD
READ8_MEMBER( d9060_base_t::dio_r )
=======
READ8_MEMBER( d9060_device_base::dio_r )
>>>>>>> upstream/master
{
	/*

	    bit     description

	    PA0     DI0
	    PA1     DI1
	    PA2     DI2
	    PA3     DI3
	    PA4     DI4
	    PA5     DI5
	    PA6     DI6
	    PA7     DI7

	*/

	return m_bus->dio_r();
}


<<<<<<< HEAD
WRITE8_MEMBER( d9060_base_t::dio_w )
=======
WRITE8_MEMBER( d9060_device_base::dio_w )
>>>>>>> upstream/master
{
	/*

	    bit     description

	    PB0     DO0
	    PB1     DO1
	    PB2     DO2
	    PB3     DO3
	    PB4     DO4
	    PB5     DO5
	    PB6     DO6
	    PB7     DO7

	*/

	m_bus->dio_w(this, data);
}


//-------------------------------------------------
//  riot6532 1
//-------------------------------------------------

<<<<<<< HEAD
READ8_MEMBER( d9060_base_t::riot1_pa_r )
=======
READ8_MEMBER( d9060_device_base::riot1_pa_r )
>>>>>>> upstream/master
{
	/*

	    bit     description

	    PA0
	    PA1
	    PA2
	    PA3
	    PA4
	    PA5     EOII
	    PA6     DAVI
	    PA7     _ATN

	*/

<<<<<<< HEAD
	UINT8 data = 0;
=======
	uint8_t data = 0;
>>>>>>> upstream/master

	// end or identify in
	data |= m_bus->eoi_r() << 5;

	// data valid in
	data |= m_bus->dav_r() << 6;

	// attention
	data |= !m_bus->atn_r() << 7;

	return data;
}

<<<<<<< HEAD
WRITE8_MEMBER( d9060_base_t::riot1_pa_w )
=======
WRITE8_MEMBER( d9060_device_base::riot1_pa_w )
>>>>>>> upstream/master
{
	/*

	    bit     description

	    PA0     ATNA
	    PA1     DACO
	    PA2     RFDO
	    PA3     EOIO
	    PA4     DAVO
	    PA5
	    PA6
	    PA7

	*/

	// attention acknowledge
	m_atna = BIT(data, 0);

	// data accepted out
	m_daco = BIT(data, 1);

	// not ready for data out
	m_rfdo = BIT(data, 2);

	// end or identify out
	m_bus->eoi_w(this, BIT(data, 3));

	// data valid out
	m_bus->dav_w(this, BIT(data, 4));

	update_ieee_signals();
}

<<<<<<< HEAD
READ8_MEMBER( d9060_base_t::riot1_pb_r )
=======
READ8_MEMBER( d9060_device_base::riot1_pb_r )
>>>>>>> upstream/master
{
	/*

	    bit     description

	    PB0     device #
	    PB1     device #
	    PB2     device #
	    PB3
	    PB4
	    PB5
	    PB6     DACI
	    PB7     RFDI

	*/

<<<<<<< HEAD
	UINT8 data = 0;
=======
	uint8_t data = 0;
>>>>>>> upstream/master

	// device number selection
	data |= m_slot->get_address() - 8;

	// data accepted in
	data |= m_bus->ndac_r() << 6;

	// ready for data in
	data |= m_bus->nrfd_r() << 7;

	return data;
}

<<<<<<< HEAD
WRITE8_MEMBER( d9060_base_t::riot1_pb_w )
=======
WRITE8_MEMBER( d9060_device_base::riot1_pb_w )
>>>>>>> upstream/master
{
	/*

	    bit     description

	    PB0
	    PB1
	    PB2
	    PB3
	    PB4     DRIVE RDY
	    PB5     PWR ON AND NO ERRORS
	    PB6
	    PB7

	*/

	// ready led
<<<<<<< HEAD
	output_set_led_value(LED_READY, BIT(data, 4));

	// power led
	output_set_led_value(LED_POWER, BIT(data, 5));

	// error led
	output_set_led_value(LED_ERROR, !BIT(data, 5));
}


WRITE8_MEMBER( d9060_base_t::via_pb_w )
=======
	machine().output().set_led_value(LED_READY, BIT(data, 4));

	// power led
	machine().output().set_led_value(LED_POWER, BIT(data, 5));

	// error led
	machine().output().set_led_value(LED_ERROR, !BIT(data, 5));
}


WRITE8_MEMBER( d9060_device_base::via_pb_w )
>>>>>>> upstream/master
{
	/*

	    bit     description

	    PB0     SEL
	    PB1     RST
	    PB2     C/D
	    PB3     BUSY
	    PB4     J14 (1=9060, 0=9090)
	    PB5     J13
	    PB6     I/O
	    PB7     MSG

	*/

	m_sasibus->write_sel(BIT(data, 0));
	m_sasibus->write_rst(BIT(data, 1));
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( d9060_base_t::ack_w )
=======
WRITE_LINE_MEMBER( d9060_device_base::ack_w )
>>>>>>> upstream/master
{
	m_sasibus->write_ack(!state);
}

<<<<<<< HEAD
WRITE_LINE_MEMBER( d9060_base_t::enable_w )
=======
WRITE_LINE_MEMBER( d9060_device_base::enable_w )
>>>>>>> upstream/master
{
	m_enable = state;

	if( !m_enable )
	{
		m_sasi_data_out->write( m_data );
	}
	else
	{
		m_sasi_data_out->write( 0 );
	}
}

<<<<<<< HEAD
WRITE8_MEMBER( d9060_base_t::scsi_data_w )
=======
WRITE8_MEMBER( d9060_device_base::scsi_data_w )
>>>>>>> upstream/master
{
	m_data = data;

	if( !m_enable )
	{
		m_sasi_data_out->write( m_data );
	}
}


//-------------------------------------------------
<<<<<<< HEAD
//  MACHINE_CONFIG_FRAGMENT( d9060 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( d9060 )
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( d9060_device_base::device_add_mconfig )
>>>>>>> upstream/master
	// DOS
	MCFG_CPU_ADD(M6502_DOS_TAG, M6502, XTAL_4MHz/4)
	MCFG_CPU_PROGRAM_MAP(d9060_main_mem)

<<<<<<< HEAD
	MCFG_DEVICE_ADD(M6532_0_TAG, MOS6532n, XTAL_4MHz/4)
	MCFG_MOS6530n_IN_PA_CB(READ8(d9060_base_t, dio_r))
	MCFG_MOS6530n_OUT_PB_CB(WRITE8(d9060_base_t, dio_w))

	MCFG_DEVICE_ADD(M6532_1_TAG, MOS6532n, XTAL_4MHz/4)
	MCFG_MOS6530n_IN_PA_CB(READ8(d9060_base_t, riot1_pa_r))
	MCFG_MOS6530n_OUT_PA_CB(WRITE8(d9060_base_t, riot1_pa_w))
	MCFG_MOS6530n_IN_PB_CB(READ8(d9060_base_t, riot1_pb_r))
	MCFG_MOS6530n_OUT_PB_CB(WRITE8(d9060_base_t, riot1_pb_w))
=======
	MCFG_DEVICE_ADD(M6532_0_TAG, MOS6532_NEW, XTAL_4MHz/4)
	MCFG_MOS6530n_IN_PA_CB(READ8(d9060_device_base, dio_r))
	MCFG_MOS6530n_OUT_PB_CB(WRITE8(d9060_device_base, dio_w))

	MCFG_DEVICE_ADD(M6532_1_TAG, MOS6532_NEW, XTAL_4MHz/4)
	MCFG_MOS6530n_IN_PA_CB(READ8(d9060_device_base, riot1_pa_r))
	MCFG_MOS6530n_OUT_PA_CB(WRITE8(d9060_device_base, riot1_pa_w))
	MCFG_MOS6530n_IN_PB_CB(READ8(d9060_device_base, riot1_pb_r))
	MCFG_MOS6530n_OUT_PB_CB(WRITE8(d9060_device_base, riot1_pb_w))
>>>>>>> upstream/master
	MCFG_MOS6530n_IRQ_CB(INPUTLINE(M6502_DOS_TAG, INPUT_LINE_IRQ0))

	// controller
	MCFG_CPU_ADD(M6502_HDC_TAG, M6502, XTAL_4MHz/4)
	MCFG_CPU_PROGRAM_MAP(d9060_hdc_mem)

	MCFG_DEVICE_ADD(M6522_TAG, VIA6522, XTAL_4MHz/4)
<<<<<<< HEAD
	MCFG_VIA6522_WRITEPA_HANDLER(WRITE8(d9060_base_t, scsi_data_w))
	MCFG_VIA6522_WRITEPB_HANDLER(WRITE8(d9060_base_t, via_pb_w))
	MCFG_VIA6522_CA2_HANDLER(WRITELINE(d9060_base_t, ack_w))
	MCFG_VIA6522_CB2_HANDLER(WRITELINE(d9060_base_t, enable_w))
	MCFG_VIA6522_IRQ_HANDLER(DEVWRITELINE(M6502_HDC_TAG, m6502_device, irq_line))
=======
	MCFG_VIA6522_WRITEPA_HANDLER(WRITE8(d9060_device_base, scsi_data_w))
	MCFG_VIA6522_WRITEPB_HANDLER(WRITE8(d9060_device_base, via_pb_w))
	MCFG_VIA6522_CA2_HANDLER(WRITELINE(d9060_device_base, ack_w))
	MCFG_VIA6522_CB2_HANDLER(WRITELINE(d9060_device_base, enable_w))
	MCFG_VIA6522_IRQ_HANDLER(INPUTLINE(M6502_HDC_TAG, M6502_IRQ_LINE))
>>>>>>> upstream/master

	MCFG_DEVICE_ADD(SASIBUS_TAG, SCSI_PORT, 0)
	MCFG_SCSI_REQ_HANDLER(DEVWRITELINE(M6522_TAG, via6522_device, write_ca1))
	MCFG_SCSI_CD_HANDLER(DEVWRITELINE(M6522_TAG, via6522_device, write_pb2))
	MCFG_SCSI_BSY_HANDLER(DEVWRITELINE(M6522_TAG, via6522_device, write_pb3))
	MCFG_SCSI_IO_HANDLER(DEVWRITELINE(M6522_TAG, via6522_device, write_pb6))
	MCFG_SCSI_MSG_HANDLER(DEVWRITELINE(M6522_TAG, via6522_device, write_pb7))
	MCFG_SCSI_DATA0_HANDLER(DEVWRITELINE(M6522_TAG, via6522_device, write_pa0))
	MCFG_SCSI_DATA1_HANDLER(DEVWRITELINE(M6522_TAG, via6522_device, write_pa1))
	MCFG_SCSI_DATA2_HANDLER(DEVWRITELINE(M6522_TAG, via6522_device, write_pa2))
	MCFG_SCSI_DATA3_HANDLER(DEVWRITELINE(M6522_TAG, via6522_device, write_pa3))
	MCFG_SCSI_DATA4_HANDLER(DEVWRITELINE(M6522_TAG, via6522_device, write_pa4))
	MCFG_SCSI_DATA5_HANDLER(DEVWRITELINE(M6522_TAG, via6522_device, write_pa5))
	MCFG_SCSI_DATA6_HANDLER(DEVWRITELINE(M6522_TAG, via6522_device, write_pa6))
	MCFG_SCSI_DATA7_HANDLER(DEVWRITELINE(M6522_TAG, via6522_device, write_pa7))

	MCFG_SCSI_OUTPUT_LATCH_ADD("sasi_data_out", SASIBUS_TAG)

	MCFG_SCSIDEV_ADD(SASIBUS_TAG ":" SCSI_PORT_DEVICE1, "harddisk", D9060HD, SCSI_ID_0)
MACHINE_CONFIG_END


//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor d9060_base_t::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( d9060 );
}


//-------------------------------------------------
=======
>>>>>>> upstream/master
//  INPUT_PORTS( d9060 )
//-------------------------------------------------

static INPUT_PORTS_START( d9060 )
	PORT_START("ADDRESS")
	PORT_DIPNAME( 0x07, 0x01, "Device Address" )
	PORT_DIPSETTING(    0x00, "8" )
	PORT_DIPSETTING(    0x01, "9" )
	PORT_DIPSETTING(    0x02, "10" )
	PORT_DIPSETTING(    0x03, "11" )
	PORT_DIPSETTING(    0x04, "12" )
	PORT_DIPSETTING(    0x05, "13" )
	PORT_DIPSETTING(    0x06, "14" )
	PORT_DIPSETTING(    0x07, "15" )
INPUT_PORTS_END


//-------------------------------------------------
//  input_ports - device-specific input ports
//-------------------------------------------------

<<<<<<< HEAD
ioport_constructor d9060_base_t::device_input_ports() const
=======
ioport_constructor d9060_device_base::device_input_ports() const
>>>>>>> upstream/master
{
	return INPUT_PORTS_NAME( d9060 );
}



//**************************************************************************
//  INLINE HELPERS
//**************************************************************************

//-------------------------------------------------
//  update_ieee_signals -
//-------------------------------------------------

<<<<<<< HEAD
inline void d9060_base_t::update_ieee_signals()
=======
inline void d9060_device_base::update_ieee_signals()
>>>>>>> upstream/master
{
	int atn = m_bus->atn_r();
	int nrfd = !(!(!(atn && m_atna) && m_rfdo) || !(atn || m_atna));
	int ndac = !(m_daco || !(atn || m_atna));

	m_bus->nrfd_w(this, nrfd);
	m_bus->ndac_w(this, ndac);
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  d9060_base_t - constructor
//-------------------------------------------------

d9060_base_t::d9060_base_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, UINT32 variant, const char *shortname, const char *source)
	: device_t(mconfig, type, name, tag, owner, clock, shortname, source),
		device_ieee488_interface(mconfig, *this),
		m_maincpu(*this, M6502_DOS_TAG),
		m_hdccpu(*this, M6502_HDC_TAG),
		m_riot0(*this, M6532_0_TAG),
		m_riot1(*this, M6532_1_TAG),
		m_via(*this, M6522_TAG),
		m_sasibus(*this, SASIBUS_TAG),
		m_sasi_data_out(*this, "sasi_data_out"),
		m_address(*this, "ADDRESS"),
		m_rfdo(1),
		m_daco(1),
		m_atna(1), m_ifc(0),
		m_enable(0), m_data(0),
		m_variant(variant)
=======
//  d9060_device_base - constructor
//-------------------------------------------------

d9060_device_base::d9060_device_base(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, uint32_t variant)
	: device_t(mconfig, type, tag, owner, clock)
	, device_ieee488_interface(mconfig, *this)
	, m_maincpu(*this, M6502_DOS_TAG)
	, m_hdccpu(*this, M6502_HDC_TAG)
	, m_riot0(*this, M6532_0_TAG)
	, m_riot1(*this, M6532_1_TAG)
	, m_via(*this, M6522_TAG)
	, m_sasibus(*this, SASIBUS_TAG)
	, m_sasi_data_out(*this, "sasi_data_out")
	, m_address(*this, "ADDRESS")
	, m_rfdo(1)
	, m_daco(1)
	, m_atna(1)
	, m_ifc(0)
	, m_enable(0)
	, m_data(0)
	, m_variant(variant)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
<<<<<<< HEAD
//  d9060_t - constructor
//-------------------------------------------------

d9060_t::d9060_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: d9060_base_t(mconfig, D9060, "D9060", tag, owner, clock, TYPE_9060, "d9060", __FILE__) { }


//-------------------------------------------------
//  d9090_t - constructor
//-------------------------------------------------

d9090_t::d9090_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: d9060_base_t(mconfig, D9090, "D9090", tag, owner, clock, TYPE_9090, "d9090", __FILE__) { }
=======
//  d9060_device - constructor
//-------------------------------------------------

d9060_device::d9060_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: d9060_device_base(mconfig, D9060, tag, owner, clock, TYPE_9060)
{
}


//-------------------------------------------------
//  d9090_device - constructor
//-------------------------------------------------

d9090_device::d9090_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: d9060_device_base(mconfig, D9090, tag, owner, clock, TYPE_9090)
{
}
>>>>>>> upstream/master


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void d9060_base_t::device_start()
=======
void d9060_device_base::device_start()
>>>>>>> upstream/master
{
	// state saving
	save_item(NAME(m_rfdo));
	save_item(NAME(m_daco));
	save_item(NAME(m_atna));
	save_item(NAME(m_enable));

	m_via->write_pb4(!(m_variant == TYPE_9090)); // J14 (6 HEADS)
	m_via->write_pb5(!(m_variant == TYPE_9060)); // J13 (4 HEADS)
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void d9060_base_t::device_reset()
=======
void d9060_device_base::device_reset()
>>>>>>> upstream/master
{
	m_maincpu->set_input_line(M6502_SET_OVERFLOW, ASSERT_LINE);
	m_maincpu->set_input_line(M6502_SET_OVERFLOW, CLEAR_LINE);

	m_hdccpu->set_input_line(M6502_SET_OVERFLOW, ASSERT_LINE);

	m_riot1->pa7_w(1);
}


//-------------------------------------------------
//  ieee488_atn - attention
//-------------------------------------------------

<<<<<<< HEAD
void d9060_base_t::ieee488_atn(int state)
=======
void d9060_device_base::ieee488_atn(int state)
>>>>>>> upstream/master
{
	update_ieee_signals();

	m_riot1->pa7_w(state);
}


//-------------------------------------------------
//  ieee488_ifc - interface clear
//-------------------------------------------------

<<<<<<< HEAD
void d9060_base_t::ieee488_ifc(int state)
=======
void d9060_device_base::ieee488_ifc(int state)
>>>>>>> upstream/master
{
	if (!m_ifc && state)
	{
		device_reset();
	}

	m_ifc = state;
}
