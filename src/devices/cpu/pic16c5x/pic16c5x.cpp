// license:BSD-3-Clause
// copyright-holders:Tony La Porta
	/**************************************************************************\
	*                      Microchip PIC16C5x Emulator                         *
	*                                                                          *
	*                    Copyright Tony La Porta                               *
	*                 Originally written for the MAME project.                 *
	*                                                                          *
	*                                                                          *
	*      Addressing architecture is based on the Harvard addressing scheme.  *
	*                                                                          *
	*                                                                          *
	*  **** Change Log ****                                                    *
	*  TLP (06-Apr-2003)                                                       *
	*   - First Public release.                                                *
	*  BO  (07-Apr-2003) Ver 1.01                                              *
	*   - Renamed 'sleep' function to 'sleepic' to avoid C conflicts.          *
	*  TLP (09-Apr-2003) Ver 1.10                                              *
	*   - Fixed modification of file register $03 (Status).                    *
	*   - Corrected support for 7FFh (12-bit) size ROMs.                       *
	*   - The 'call' and 'goto' instructions weren't correctly handling the    *
	*     STATUS page info correctly.                                          *
	*   - The FSR register was incorrectly oring the data with 0xe0 when read. *
	*   - Prescaler masking information was set to 3 instead of 7.             *
	*   - Prescaler assign bit was set to 4 instead of 8.                      *
	*   - Timer source and edge select flags/masks were wrong.                 *
	*   - Corrected the memory bank selection in GET/SET_REGFILE and also the  *
	*     indirect register addressing.                                        *
	*  BMP (18-May-2003) Ver 1.11                                              *
	*   - pic16c5x_get_reg functions were missing 'returns'.                   *
	*  TLP (27-May-2003) Ver 1.12                                              *
	*   - Fixed the WatchDog timer count.                                      *
	*   - The Prescaler rate was incorrectly being zeroed, instead of the      *
	*     actual Prescaler counter in the CLRWDT and SLEEP instructions.       *
	*   - Added masking to the FSR register. Upper unused bits are always 1.   *
	*  TLP (27-Aug-2009) Ver 1.13                                              *
	*   - Indirect addressing was not taking into account special purpose      *
	*     memory mapped locations.                                             *
	*   - 'iorlw' instruction was saving the result to memory instead of       *
	*     the W register.                                                      *
	*   - 'tris' instruction no longer modifies Port-C on PIC models that      *
	*     do not have Port-C implemented.                                      *
	*  TLP (07-Sep-2009) Ver 1.14                                              *
	*   - Edge sense control for the T0 count input was incorrectly reversed   *
<<<<<<< HEAD
=======
	*  LE (05-Feb-2017) Ver 1.15                                               *
	*   - Allow writing all bits of the status register except TO and PD.      *
	*     This enables e.g. bcf, bsf or clrf to change the flags when the      *
	*     status register is the destination.                                  *
	*   - Changed rlf and rrf to update the carry flag in the last step.       *
	*     Fixes the case where the status register is the destination.         *
	*  hap (12-Feb-2017) Ver 1.16                                              *
	*   - Added basic support for the old GI PIC1650 and PIC1655.              *
	*   - Made RTCC(aka T0CKI) pin an inputline handler.                       *
>>>>>>> upstream/master
	*                                                                          *
	*                                                                          *
	*  **** Notes: ****                                                        *
	*  PIC WatchDog Timer has a separate internal clock. For the moment, we're *
	*     basing the count on a 4MHz input clock, since 4MHz is the typical    *
	*     input frequency (but by no means always).                            *
	*  A single scaler is available for the Counter/Timer or WatchDog Timer.   *
	*     When connected to the Counter/Timer, it functions as a Prescaler,    *
	*     hence prescale overflows, tick the Counter/Timer.                    *
	*     When connected to the WatchDog Timer, it functions as a Postscaler   *
	*     hence WatchDog Timer overflows, tick the Postscaler. This scenario   *
	*     means that the WatchDog timeout occurs when the Postscaler has       *
	*     reached the scaler rate value, not when the WatchDog reaches zero.   *
	*  CLRWDT should prevent the WatchDog Timer from timing out and generating *
	*     a device reset, but how is not known. The manual also mentions that  *
	*     the WatchDog Timer can only be disabled during ROM programming, and  *
	*     no other means seem to exist???                                      *
	*                                                                          *
	\**************************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "debugger.h"
#include "pic16c5x.h"


const device_type PIC16C54 = &device_creator<pic16c54_device>;
const device_type PIC16C55 = &device_creator<pic16c55_device>;
const device_type PIC16C56 = &device_creator<pic16c56_device>;
const device_type PIC16C57 = &device_creator<pic16c57_device>;
const device_type PIC16C58 = &device_creator<pic16c58_device>;
=======
#include "pic16c5x.h"
#include "debugger.h"


DEFINE_DEVICE_TYPE(PIC16C54, pic16c54_device, "pic16c54", "PIC16C54")
DEFINE_DEVICE_TYPE(PIC16C55, pic16c55_device, "pic16c55", "PIC16C55")
DEFINE_DEVICE_TYPE(PIC16C56, pic16c56_device, "pic16c56", "PIC16C56")
DEFINE_DEVICE_TYPE(PIC16C57, pic16c57_device, "pic16c57", "PIC16C57")
DEFINE_DEVICE_TYPE(PIC16C58, pic16c58_device, "pic16c58", "PIC16C58")

DEFINE_DEVICE_TYPE(PIC1650,  pic1650_device,  "pic1650",  "PIC1650")
DEFINE_DEVICE_TYPE(PIC1655,  pic1655_device,  "pic1655",  "PIC1655")
>>>>>>> upstream/master


/****************************************************************************
 *  Internal Memory Maps
 ****************************************************************************/

static ADDRESS_MAP_START( pic16c5x_rom_9, AS_PROGRAM, 16, pic16c5x_device )
	AM_RANGE(0x000, 0x1ff) AM_ROM
ADDRESS_MAP_END

static ADDRESS_MAP_START( pic16c5x_ram_5, AS_DATA, 8, pic16c5x_device )
	AM_RANGE(0x00, 0x07) AM_RAM
	AM_RANGE(0x08, 0x0f) AM_RAM
	AM_RANGE(0x10, 0x1f) AM_RAM
ADDRESS_MAP_END

static ADDRESS_MAP_START( pic16c5x_rom_10, AS_PROGRAM, 16, pic16c5x_device )
	AM_RANGE(0x000, 0x3ff) AM_ROM
ADDRESS_MAP_END

static ADDRESS_MAP_START( pic16c5x_rom_11, AS_PROGRAM, 16, pic16c5x_device )
	AM_RANGE(0x000, 0x7ff) AM_ROM
ADDRESS_MAP_END

static ADDRESS_MAP_START( pic16c5x_ram_7, AS_DATA, 8, pic16c5x_device )
	AM_RANGE(0x00, 0x07) AM_RAM AM_MIRROR(0x60)
	AM_RANGE(0x08, 0x0f) AM_RAM AM_MIRROR(0x60)
	AM_RANGE(0x10, 0x1f) AM_RAM
	AM_RANGE(0x30, 0x3f) AM_RAM
	AM_RANGE(0x50, 0x5f) AM_RAM
	AM_RANGE(0x70, 0x7f) AM_RAM
ADDRESS_MAP_END


<<<<<<< HEAD
pic16c5x_device::pic16c5x_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, int program_width, int data_width, int picmodel)
	: cpu_device(mconfig, type, name, tag, owner, clock, shortname, __FILE__)
	, m_program_config("program", ENDIANNESS_LITTLE, 16, program_width, -1
		, ( ( program_width == 9 ) ? ADDRESS_MAP_NAME(pic16c5x_rom_9) : ( ( program_width == 10 ) ? ADDRESS_MAP_NAME(pic16c5x_rom_10) : ADDRESS_MAP_NAME(pic16c5x_rom_11) )))
	, m_data_config("data", ENDIANNESS_LITTLE, 8, data_width, 0
		, ( ( data_width == 5 ) ? ADDRESS_MAP_NAME(pic16c5x_ram_5) : ADDRESS_MAP_NAME(pic16c5x_ram_7) ) )
=======
pic16c5x_device::pic16c5x_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, int program_width, int data_width, int picmodel)
	: cpu_device(mconfig, type, tag, owner, clock)
	, m_program_config("program", ENDIANNESS_LITTLE, 16, program_width, -1
	, ( ( program_width == 9 ) ? ADDRESS_MAP_NAME(pic16c5x_rom_9) : ( ( program_width == 10 ) ? ADDRESS_MAP_NAME(pic16c5x_rom_10) : ADDRESS_MAP_NAME(pic16c5x_rom_11) )))
	, m_data_config("data", ENDIANNESS_LITTLE, 8, data_width, 0
	, ( ( data_width == 5 ) ? ADDRESS_MAP_NAME(pic16c5x_ram_5) : ADDRESS_MAP_NAME(pic16c5x_ram_7) ) )
>>>>>>> upstream/master
	, m_reset_vector((program_width == 9) ? 0x1ff : ((program_width == 10) ? 0x3ff : 0x7ff))
	, m_picmodel(picmodel)
	, m_temp_config(0)
	, m_picRAMmask((data_width == 5) ? 0x1f : 0x7f)
	, m_read_a(*this)
	, m_read_b(*this)
	, m_read_c(*this)
<<<<<<< HEAD
	, m_write_a(*this)
	, m_write_b(*this)
	, m_write_c(*this)
	, m_read_t0(*this)
{
}


pic16c54_device::pic16c54_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: pic16c5x_device(mconfig, PIC16C54, "PIC16C54", tag, owner, clock, "pic16c54", 9, 5, 0x16C54)
{
}

pic16c55_device::pic16c55_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: pic16c5x_device(mconfig, PIC16C55, "PIC16C55", tag, owner, clock, "pic16c55", 9, 5, 0x16C55)
{
}

pic16c56_device::pic16c56_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: pic16c5x_device(mconfig, PIC16C56, "PIC16C56", tag, owner, clock, "pic16c56", 10, 5, 0x16C56)
{
}

pic16c57_device::pic16c57_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: pic16c5x_device(mconfig, PIC16C57, "PIC16C57", tag, owner, clock, "pic16c57", 11, 7, 0x16C57)
{
}

pic16c58_device::pic16c58_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: pic16c5x_device(mconfig, PIC16C58, "PIC16C58", tag, owner, clock, "pic16c58", 11, 7, 0x16C58)
{
}


offs_t pic16c5x_device::disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options)
{
	extern CPU_DISASSEMBLE( pic16c5x );
	return CPU_DISASSEMBLE_NAME(pic16c5x)(this, buffer, pc, oprom, opram, options);
=======
	, m_read_d(*this)
	, m_write_a(*this)
	, m_write_b(*this)
	, m_write_c(*this)
	, m_write_d(*this)
{
}


pic16c54_device::pic16c54_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: pic16c5x_device(mconfig, PIC16C54, tag, owner, clock, 9, 5, 0x16C54)
{
}

pic16c55_device::pic16c55_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: pic16c5x_device(mconfig, PIC16C55, tag, owner, clock, 9, 5, 0x16C55)
{
}

pic16c56_device::pic16c56_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: pic16c5x_device(mconfig, PIC16C56, tag, owner, clock, 10, 5, 0x16C56)
{
}

pic16c57_device::pic16c57_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: pic16c5x_device(mconfig, PIC16C57, tag, owner, clock, 11, 7, 0x16C57)
{
}

pic16c58_device::pic16c58_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: pic16c5x_device(mconfig, PIC16C58, tag, owner, clock, 11, 7, 0x16C58)
{
}

pic1650_device::pic1650_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: pic16c5x_device(mconfig, PIC1650, tag, owner, clock, 9, 5, 0x1650)
{
}

pic1655_device::pic1655_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: pic16c5x_device(mconfig, PIC1655, tag, owner, clock, 9, 5, 0x1655)
{
}

device_memory_interface::space_config_vector pic16c5x_device::memory_space_config() const
{
	return space_config_vector {
		std::make_pair(AS_PROGRAM, &m_program_config),
		std::make_pair(AS_DATA,    &m_data_config)
	};
}

offs_t pic16c5x_device::disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options)
{
	extern CPU_DISASSEMBLE( pic16c5x );
	return CPU_DISASSEMBLE_NAME(pic16c5x)(this, stream, pc, oprom, opram, options);
>>>>>>> upstream/master
}


void pic16c5x_device::update_internalram_ptr()
{
<<<<<<< HEAD
	m_internalram = (UINT8 *)m_data->get_write_ptr(0x00);
=======
	m_internalram = (uint8_t *)m_data->get_write_ptr(0x00);
>>>>>>> upstream/master
}



#define PIC16C5x_RDOP(A)         (m_direct->read_word((A)<<1))
<<<<<<< HEAD
#define PIC16C5x_RAM_RDMEM(A)    ((UINT8)m_data->read_byte(A))
#define PIC16C5x_RAM_WRMEM(A,V)  (m_data->write_byte(A,V))

#define M_RDRAM(A)      (((A) < 8) ? m_internalram[A] : PIC16C5x_RAM_RDMEM(A))
#define M_WRTRAM(A,V)   do { if ((A) < 8) m_internalram[A] = (V); else PIC16C5x_RAM_WRMEM(A,V); } while (0)
=======
#define PIC16C5x_RAM_RDMEM(A)    ((uint8_t)m_data->read_byte(A))
#define PIC16C5x_RAM_WRMEM(A,V)  (m_data->write_byte(A,V))

#define M_RDRAM(A)      (((A) < 9) ? m_internalram[A] : PIC16C5x_RAM_RDMEM(A))
#define M_WRTRAM(A,V)   do { if ((A) < 9) m_internalram[A] = (V); else PIC16C5x_RAM_WRMEM(A,V); } while (0)
>>>>>>> upstream/master
#define M_RDOP(A)       PIC16C5x_RDOP(A)
#define ADDR_MASK       0x7ff



#define TMR0    m_internalram[1]
#define PCL     m_internalram[2]
#define STATUS  m_internalram[3]
#define FSR     m_internalram[4]
#define PORTA   m_internalram[5]
#define PORTB   m_internalram[6]
#define PORTC   m_internalram[7]
<<<<<<< HEAD
=======
#define PORTD   m_internalram[8]
>>>>>>> upstream/master
#define INDF    M_RDRAM(FSR)

#define ADDR    (m_opcode.b.l & 0x1f)

<<<<<<< HEAD
#define  RISING_EDGE_T0  (( (int)(T0_in - m_old_T0) > 0) ? 1 : 0)
#define FALLING_EDGE_T0  (( (int)(T0_in - m_old_T0) < 0) ? 1 : 0)

=======
>>>>>>> upstream/master

/********  The following is the Status Flag register definition.  *********/
			/* | 7 | 6 | 5 |  4 |  3 | 2 |  1 | 0 | */
			/* |    PA     | TO | PD | Z | DC | C | */
#define PA_REG      0xe0    /* PA   Program Page Preselect - bit 8 is unused here */
#define TO_FLAG     0x10    /* TO   Time Out flag (WatchDog) */
#define PD_FLAG     0x08    /* PD   Power Down flag */
#define Z_FLAG      0x04    /* Z    Zero Flag */
#define DC_FLAG     0x02    /* DC   Digit Carry/Borrow flag (Nibble) */
#define C_FLAG      0x01    /* C    Carry/Borrow Flag (Byte) */

#define PA      (STATUS & PA_REG)
#define TO      (STATUS & TO_FLAG)
#define PD      (STATUS & PD_FLAG)
#define ZERO    (STATUS & Z_FLAG)
#define DC      (STATUS & DC_FLAG)
#define CARRY   (STATUS & C_FLAG)


/********  The following is the Option Flag register definition.  *********/
			/* | 7 | 6 |   5  |   4  |  3  | 2 | 1 | 0 | */
			/* | 0 | 0 | TOCS | TOSE | PSA |    PS     | */
#define T0CS_FLAG   0x20    /* TOCS     Timer 0 clock source select */
#define T0SE_FLAG   0x10    /* TOSE     Timer 0 clock source edge select */
#define PSA_FLAG    0x08    /* PSA      Prescaler Assignment bit */
#define PS_REG      0x07    /* PS       Prescaler Rate select */

#define T0CS    (m_OPTION & T0CS_FLAG)
#define T0SE    (m_OPTION & T0SE_FLAG)
#define PSA     (m_OPTION & PSA_FLAG)
#define PS      (m_OPTION & PS_REG)


/********  The following is the Config Flag register definition.  *********/
	/* | 11 | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 |   2  | 1 | 0 | */
	/* |              CP                     | WDTE |  FOSC | */
							/* CP       Code Protect (ROM read protect) */
#define WDTE_FLAG   0x04    /* WDTE     WatchDog Timer enable */
#define FOSC_FLAG   0x03    /* FOSC     Oscillator source select */

#define WDTE    (m_CONFIG & WDTE_FLAG)
#define FOSC    (m_CONFIG & FOSC_FLAG)


/************************************************************************
 *  Shortcuts
 ************************************************************************/

<<<<<<< HEAD
#define CLR(flagreg, flag) ( flagreg &= (UINT8)(~flag) )
=======
#define CLR(flagreg, flag) ( flagreg &= (uint8_t)(~flag) )
>>>>>>> upstream/master
#define SET(flagreg, flag) ( flagreg |=  flag )


/* Easy bit position selectors */
#define POS  ((m_opcode.b.l >> 5) & 7)
static const unsigned int bit_clr[8] = { 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f };
static const unsigned int bit_set[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };



void pic16c5x_device::CALCULATE_Z_FLAG()
{
	if (m_ALU == 0) SET(STATUS, Z_FLAG);
	else CLR(STATUS, Z_FLAG);
}

void pic16c5x_device::CALCULATE_ADD_CARRY()
{
<<<<<<< HEAD
	if ((UINT8)(m_old_data) > (UINT8)(m_ALU)) {
=======
	if ((uint8_t)(m_old_data) > (uint8_t)(m_ALU)) {
>>>>>>> upstream/master
		SET(STATUS, C_FLAG);
	}
	else {
		CLR(STATUS, C_FLAG);
	}
}

void pic16c5x_device::CALCULATE_ADD_DIGITCARRY()
{
<<<<<<< HEAD
	if (((UINT8)(m_old_data) & 0x0f) > ((UINT8)(m_ALU) & 0x0f)) {
=======
	if (((uint8_t)(m_old_data) & 0x0f) > ((uint8_t)(m_ALU) & 0x0f)) {
>>>>>>> upstream/master
		SET(STATUS, DC_FLAG);
	}
	else {
		CLR(STATUS, DC_FLAG);
	}
}

void pic16c5x_device::CALCULATE_SUB_CARRY()
{
<<<<<<< HEAD
	if ((UINT8)(m_old_data) < (UINT8)(m_ALU)) {
=======
	if ((uint8_t)(m_old_data) < (uint8_t)(m_ALU)) {
>>>>>>> upstream/master
		CLR(STATUS, C_FLAG);
	}
	else {
		SET(STATUS, C_FLAG);
	}
}

void pic16c5x_device::CALCULATE_SUB_DIGITCARRY()
{
<<<<<<< HEAD
	if (((UINT8)(m_old_data) & 0x0f) < ((UINT8)(m_ALU) & 0x0f)) {
=======
	if (((uint8_t)(m_old_data) & 0x0f) < ((uint8_t)(m_ALU) & 0x0f)) {
>>>>>>> upstream/master
		CLR(STATUS, DC_FLAG);
	}
	else {
		SET(STATUS, DC_FLAG);
	}
}



<<<<<<< HEAD
UINT16 pic16c5x_device::POP_STACK()
{
	UINT16 data = m_STACK[1];
	m_STACK[1] = m_STACK[0];
	return (data & ADDR_MASK);
}
void pic16c5x_device::PUSH_STACK(UINT16 data)
=======
uint16_t pic16c5x_device::POP_STACK()
{
	uint16_t data = m_STACK[1];
	m_STACK[1] = m_STACK[0];
	return (data & ADDR_MASK);
}
void pic16c5x_device::PUSH_STACK(uint16_t data)
>>>>>>> upstream/master
{
	m_STACK[0] = m_STACK[1];
	m_STACK[1] = (data & ADDR_MASK);
}



<<<<<<< HEAD
UINT8 pic16c5x_device::GET_REGFILE(offs_t addr) /* Read from internal memory */
{
	UINT8 data;
=======
uint8_t pic16c5x_device::GET_REGFILE(offs_t addr) /* Read from internal memory */
{
	uint8_t data = 0;
>>>>>>> upstream/master

	if (addr == 0) {                        /* Indirect addressing  */
		addr = (FSR & m_picRAMmask);
	}

	if ((m_picmodel == 0x16C57) || (m_picmodel == 0x16C58)) {
		addr |= (FSR & 0x60);     /* FSR bits 6-5 are used for banking in direct mode */
	}

	if ((addr & 0x10) == 0) addr &= 0x0f;

	switch(addr)
	{
<<<<<<< HEAD
		case 00:    /* Not an actual register, so return 0 */
					data = 0;
					break;
		case 04:    data = (FSR | (UINT8)(~m_picRAMmask));
					break;
		case 05:    data = m_read_a(PIC16C5x_PORTA, 0xff);
					data &= m_TRISA;
					data |= ((UINT8)(~m_TRISA) & PORTA);
					data &= 0x0f;       /* 4-bit port (only lower 4 bits used) */
					break;
		case 06:    data = m_read_b(PIC16C5x_PORTB, 0xff);
					data &= m_TRISB;
					data |= ((UINT8)(~m_TRISB) & PORTB);
					break;
		case 07:    if ((m_picmodel == 0x16C55) || (m_picmodel == 0x16C57)) {
						data = m_read_c(PIC16C5x_PORTC, 0xff);
						data &= m_TRISC;
						data |= ((UINT8)(~m_TRISC) & PORTC);
					}
					else {              /* PIC16C54, PIC16C56, PIC16C58 */
=======
		case 0:     /* Not an actual register, so return 0 */
					data = 0;
					break;
		case 4:     data = (FSR | (uint8_t)(~m_picRAMmask));
					break;
		case 5:     /* read port A */
					if (m_picmodel == 0x1650) {
						data = m_read_a(PIC16C5x_PORTA, 0xff) & PORTA;
					}
					else if (m_picmodel == 0x1655) {
						data = m_read_a(PIC16C5x_PORTA, 0xff) & 0x0f;
					}
					else {
						data = m_read_a(PIC16C5x_PORTA, 0xff);
						data &= m_TRISA;
						data |= ((uint8_t)(~m_TRISA) & PORTA);
						data &= 0x0f; /* 4-bit port (only lower 4 bits used) */
					}
					break;
		case 6:     /* read port B */
					if (m_picmodel == 0x1650) {
						data = m_read_b(PIC16C5x_PORTB, 0xff) & PORTB;
					}
					else if (m_picmodel != 0x1655) { /* B is output-only on 1655 */
						data = m_read_b(PIC16C5x_PORTB, 0xff);
						data &= m_TRISB;
						data |= ((uint8_t)(~m_TRISB) & PORTB);
					}
					break;
		case 7:     /* read port C */
					if (m_picmodel == 0x1650 || m_picmodel == 0x1655) {
						data = m_read_c(PIC16C5x_PORTC, 0xff) & PORTC;
					}
					else if ((m_picmodel == 0x16C55) || (m_picmodel == 0x16C57)) {
						data = m_read_c(PIC16C5x_PORTC, 0xff);
						data &= m_TRISC;
						data |= ((uint8_t)(~m_TRISC) & PORTC);
					}
					else { /* PIC16C54, PIC16C56, PIC16C58 */
						data = M_RDRAM(addr);
					}
					break;
		case 8:     /* read port D */
					if (m_picmodel == 0x1650) {
						data = m_read_d(PIC16C5x_PORTD, 0xff) & PORTD;
					}
					else {
>>>>>>> upstream/master
						data = M_RDRAM(addr);
					}
					break;
		default:    data = M_RDRAM(addr);
					break;
	}
	return data;
}

<<<<<<< HEAD
void pic16c5x_device::STORE_REGFILE(offs_t addr, UINT8 data)    /* Write to internal memory */
=======
void pic16c5x_device::STORE_REGFILE(offs_t addr, uint8_t data)    /* Write to internal memory */
>>>>>>> upstream/master
{
	if (addr == 0) {                        /* Indirect addressing  */
		addr = (FSR & m_picRAMmask);
	}

	if ((m_picmodel == 0x16C57) || (m_picmodel == 0x16C58)) {
		addr |= (FSR & 0x60);     /* FSR bits 6-5 are used for banking in direct mode */
	}

	if ((addr & 0x10) == 0) addr &= 0x0f;

	switch(addr)
	{
<<<<<<< HEAD
		case 00:    /* Not an actual register, nothing to save */
					break;
		case 01:    m_delay_timer = 2;      /* Timer starts after next two instructions */
					if (PSA == 0) m_prescaler = 0;  /* Must clear the Prescaler */
					TMR0 = data;
					break;
		case 02:    PCL = data;
					m_PC = ((STATUS & PA_REG) << 4) | data;
					break;
		case 03:    STATUS &= (UINT8)(~PA_REG); STATUS |= (data & PA_REG);
					break;
		case 04:    FSR = (data | (UINT8)(~m_picRAMmask));
					break;
		case 05:    data &= 0x0f;       /* 4-bit port (only lower 4 bits used) */
					m_write_a(PIC16C5x_PORTA, data & (UINT8)(~m_TRISA), 0xff);
					PORTA = data;
					break;
		case 06:    m_write_b(PIC16C5x_PORTB, data & (UINT8)(~m_TRISB), 0xff);
					PORTB = data;
					break;
		case 07:    if ((m_picmodel == 0x16C55) || (m_picmodel == 0x16C57)) {
						m_write_c(PIC16C5x_PORTC, data & (UINT8)(~m_TRISC), 0xff);
						PORTC = data;
					}
					else {      /* PIC16C54, PIC16C56, PIC16C58 */
						M_WRTRAM(addr, data);
					}
=======
		case 0:     /* Not an actual register, nothing to save */
					break;
		case 1:     m_delay_timer = 2; /* Timer starts after next two instructions */
					if (PSA == 0) m_prescaler = 0; /* Must clear the Prescaler */
					TMR0 = data;
					break;
		case 2:     PCL = data;
					m_PC = ((STATUS & PA_REG) << 4) | data;
					break;
		case 3:     STATUS = (STATUS & (TO_FLAG | PD_FLAG)) | (data & (uint8_t)(~(TO_FLAG | PD_FLAG)));
					break;
		case 4:     FSR = (data | (uint8_t)(~m_picRAMmask));
					break;
		case 5:     /* write port A */
					if (m_picmodel == 0x1650) {
						m_write_a(PIC16C5x_PORTA, data, 0xff);
					}
					else if (m_picmodel != 0x1655) { /* A is input-only on 1655 */
						data &= 0x0f; /* 4-bit port (only lower 4 bits used) */
						m_write_a(PIC16C5x_PORTA, data & (uint8_t)(~m_TRISA), 0xff);
					}
					PORTA = data;
					break;
		case 6:     /* write port B */
					if (m_picmodel == 0x1650 || m_picmodel == 0x1655) {
						m_write_b(PIC16C5x_PORTB, data, 0xff);
					}
					else {
						m_write_b(PIC16C5x_PORTB, data & (uint8_t)(~m_TRISB), 0xff);
					}
					PORTB = data;
					break;
		case 7:     /* write port C */
					if (m_picmodel == 0x1650 || m_picmodel == 0x1655) {
						m_write_c(PIC16C5x_PORTC, data, 0xff);
					}
					else if ((m_picmodel == 0x16C55) || (m_picmodel == 0x16C57)) {
						m_write_c(PIC16C5x_PORTC, data & (uint8_t)(~m_TRISC), 0xff);
					}
					PORTC = data; /* also writes to RAM */
					break;
		case 8:     /* write port D */
					if (m_picmodel == 0x1650) {
						m_write_d(PIC16C5x_PORTD, data, 0xff);
					}
					PORTD = data; /* also writes to RAM */
>>>>>>> upstream/master
					break;
		default:    M_WRTRAM(addr, data);
					break;
	}
}


<<<<<<< HEAD
void pic16c5x_device::STORE_RESULT(offs_t addr, UINT8 data)
=======
void pic16c5x_device::STORE_RESULT(offs_t addr, uint8_t data)
>>>>>>> upstream/master
{
	if (m_opcode.b.l & 0x20)
	{
		STORE_REGFILE(addr, data);
	}
	else
	{
		m_W = data;
	}
}


/************************************************************************
 *  Emulate the Instructions
 ************************************************************************/

/* This following function is here to fill in the void for */
/* the opcode call function. This function is never called. */


void pic16c5x_device::illegal()
{
	logerror("PIC16C5x:  PC=%03x,  Illegal opcode = %04x\n", (m_PC-1), m_opcode.w.l);
}

<<<<<<< HEAD
=======
/*
  Note:
  According to the manual, if the STATUS register is the destination for an instruction that affects the Z, DC or C bits
  then the write to these three bits is disabled. These bits are set or cleared according to the device logic.
  To ensure this is correctly emulated, in instructions that write to the file registers, always change the status flags
  *after* storing the result of the instruction.
  e.g. CALCULATE_*, SET(STATUS,*_FLAG) and CLR(STATUS,*_FLAG) should appear as the last steps of the instruction emulation.
*/
>>>>>>> upstream/master

void pic16c5x_device::addwf()
{
	m_old_data = GET_REGFILE(ADDR);
	m_ALU = m_old_data + m_W;
	STORE_RESULT(ADDR, m_ALU);
	CALCULATE_Z_FLAG();
	CALCULATE_ADD_CARRY();
	CALCULATE_ADD_DIGITCARRY();
}

void pic16c5x_device::andwf()
{
	m_ALU = GET_REGFILE(ADDR) & m_W;
	STORE_RESULT(ADDR, m_ALU);
	CALCULATE_Z_FLAG();
}

void pic16c5x_device::andlw()
{
	m_ALU = m_opcode.b.l & m_W;
	m_W = m_ALU;
	CALCULATE_Z_FLAG();
}

void pic16c5x_device::bcf()
{
	m_ALU = GET_REGFILE(ADDR);
	m_ALU &= bit_clr[POS];
	STORE_REGFILE(ADDR, m_ALU);
}

void pic16c5x_device::bsf()
{
	m_ALU = GET_REGFILE(ADDR);
	m_ALU |= bit_set[POS];
	STORE_REGFILE(ADDR, m_ALU);
}

void pic16c5x_device::btfss()
{
	if ((GET_REGFILE(ADDR) & bit_set[POS]) == bit_set[POS])
	{
<<<<<<< HEAD
		m_PC++ ;
=======
		m_PC++;
>>>>>>> upstream/master
		PCL = m_PC & 0xff;
		m_inst_cycles += 1;     /* Add NOP cycles */
	}
}

void pic16c5x_device::btfsc()
{
	if ((GET_REGFILE(ADDR) & bit_set[POS]) == 0)
	{
<<<<<<< HEAD
		m_PC++ ;
=======
		m_PC++;
>>>>>>> upstream/master
		PCL = m_PC & 0xff;
		m_inst_cycles += 1;     /* Add NOP cycles */
	}
}

void pic16c5x_device::call()
{
	PUSH_STACK(m_PC);
	m_PC = ((STATUS & PA_REG) << 4) | m_opcode.b.l;
	m_PC &= 0x6ff;
	PCL = m_PC & 0xff;
}

void pic16c5x_device::clrw()
{
	m_W = 0;
	SET(STATUS, Z_FLAG);
}

void pic16c5x_device::clrf()
{
	STORE_REGFILE(ADDR, 0);
	SET(STATUS, Z_FLAG);
}

void pic16c5x_device::clrwdt()
{
	m_WDT = 0;
	if (PSA) m_prescaler = 0;
	SET(STATUS, TO_FLAG);
	SET(STATUS, PD_FLAG);
}

void pic16c5x_device::comf()
{
<<<<<<< HEAD
	m_ALU = (UINT8)(~(GET_REGFILE(ADDR)));
=======
	m_ALU = (uint8_t)(~(GET_REGFILE(ADDR)));
>>>>>>> upstream/master
	STORE_RESULT(ADDR, m_ALU);
	CALCULATE_Z_FLAG();
}

void pic16c5x_device::decf()
{
	m_ALU = GET_REGFILE(ADDR) - 1;
	STORE_RESULT(ADDR, m_ALU);
	CALCULATE_Z_FLAG();
}

void pic16c5x_device::decfsz()
{
	m_ALU = GET_REGFILE(ADDR) - 1;
	STORE_RESULT(ADDR, m_ALU);
	if (m_ALU == 0)
	{
<<<<<<< HEAD
		m_PC++ ;
=======
		m_PC++;
>>>>>>> upstream/master
		PCL = m_PC & 0xff;
		m_inst_cycles += 1;     /* Add NOP cycles */
	}
}

void pic16c5x_device::goto_op()
{
	m_PC = ((STATUS & PA_REG) << 4) | (m_opcode.w.l & 0x1ff);
	m_PC &= ADDR_MASK;
	PCL = m_PC & 0xff;
}

void pic16c5x_device::incf()
{
	m_ALU = GET_REGFILE(ADDR) + 1;
	STORE_RESULT(ADDR, m_ALU);
	CALCULATE_Z_FLAG();
}

void pic16c5x_device::incfsz()
{
	m_ALU = GET_REGFILE(ADDR) + 1;
	STORE_RESULT(ADDR, m_ALU);
	if (m_ALU == 0)
	{
<<<<<<< HEAD
		m_PC++ ;
=======
		m_PC++;
>>>>>>> upstream/master
		PCL = m_PC & 0xff;
		m_inst_cycles += 1;     /* Add NOP cycles */
	}
}

void pic16c5x_device::iorlw()
{
	m_ALU = m_opcode.b.l | m_W;
	m_W = m_ALU;
	CALCULATE_Z_FLAG();
}

void pic16c5x_device::iorwf()
{
	m_ALU = GET_REGFILE(ADDR) | m_W;
	STORE_RESULT(ADDR, m_ALU);
	CALCULATE_Z_FLAG();
}

void pic16c5x_device::movf()
{
	m_ALU = GET_REGFILE(ADDR);
	STORE_RESULT(ADDR, m_ALU);
	CALCULATE_Z_FLAG();
}

void pic16c5x_device::movlw()
{
	m_W = m_opcode.b.l;
}

void pic16c5x_device::movwf()
{
	STORE_REGFILE(ADDR, m_W);
}

void pic16c5x_device::nop()
{
	/* Do nothing */
}

void pic16c5x_device::option()
{
	m_OPTION = m_W & (T0CS_FLAG | T0SE_FLAG | PSA_FLAG | PS_REG);
}

void pic16c5x_device::retlw()
{
	m_W = m_opcode.b.l;
	m_PC = POP_STACK();
	PCL = m_PC & 0xff;
}

void pic16c5x_device::rlf()
{
	m_ALU = GET_REGFILE(ADDR);
<<<<<<< HEAD
	m_ALU <<= 1;
	if (STATUS & C_FLAG) m_ALU |= 1;
	if (GET_REGFILE(ADDR) & 0x80) SET(STATUS, C_FLAG);
	else CLR(STATUS, C_FLAG);
	STORE_RESULT(ADDR, m_ALU);
=======
	uint8_t bit7 = m_ALU & 0x80;
	m_ALU <<= 1;
	if (STATUS & C_FLAG) m_ALU |= 1;
	STORE_RESULT(ADDR, m_ALU);
	if (bit7) SET(STATUS, C_FLAG);
	else CLR(STATUS, C_FLAG);
>>>>>>> upstream/master
}

void pic16c5x_device::rrf()
{
	m_ALU = GET_REGFILE(ADDR);
<<<<<<< HEAD
	m_ALU >>= 1;
	if (STATUS & C_FLAG) m_ALU |= 0x80;
	if (GET_REGFILE(ADDR) & 1) SET(STATUS, C_FLAG);
	else CLR(STATUS, C_FLAG);
	STORE_RESULT(ADDR, m_ALU);
=======
	uint8_t bit0 = m_ALU & 1;
	m_ALU >>= 1;
	if (STATUS & C_FLAG) m_ALU |= 0x80;
	STORE_RESULT(ADDR, m_ALU);
	if (bit0) SET(STATUS, C_FLAG);
	else CLR(STATUS, C_FLAG);
>>>>>>> upstream/master
}

void pic16c5x_device::sleepic()
{
	if (WDTE) m_WDT = 0;
	if (PSA) m_prescaler = 0;
	SET(STATUS, TO_FLAG);
	CLR(STATUS, PD_FLAG);
}

void pic16c5x_device::subwf()
{
	m_old_data = GET_REGFILE(ADDR);
	m_ALU = m_old_data - m_W;
	STORE_RESULT(ADDR, m_ALU);
	CALCULATE_Z_FLAG();
	CALCULATE_SUB_CARRY();
	CALCULATE_SUB_DIGITCARRY();
}

void pic16c5x_device::swapf()
{
	m_ALU  = ((GET_REGFILE(ADDR) << 4) & 0xf0);
	m_ALU |= ((GET_REGFILE(ADDR) >> 4) & 0x0f);
	STORE_RESULT(ADDR, m_ALU);
}

void pic16c5x_device::tris()
{
	switch(m_opcode.b.l & 0x7)
	{
<<<<<<< HEAD
		case 05:    if   (m_TRISA == m_W) break;
					else { m_TRISA = m_W | 0xf0; m_write_a(PIC16C5x_PORTA, PORTA & (UINT8)(~m_TRISA) & 0x0f, 0xff); break; }
		case 06:    if   (m_TRISB == m_W) break;
					else { m_TRISB = m_W; m_write_b(PIC16C5x_PORTB, PORTB & (UINT8)(~m_TRISB), 0xff); break; }
		case 07:    if ((m_picmodel == 0x16C55) || (m_picmodel == 0x16C57)) {
						if   (m_TRISC == m_W) break;
						else { m_TRISC = m_W; m_write_c(PIC16C5x_PORTC, PORTC & (UINT8)(~m_TRISC), 0xff); break; }
=======
		case 5:     if   (m_TRISA == m_W) break;
					else { m_TRISA = m_W | 0xf0; m_write_a(PIC16C5x_PORTA, PORTA & (uint8_t)(~m_TRISA) & 0x0f, 0xff); break; }
		case 6:     if   (m_TRISB == m_W) break;
					else { m_TRISB = m_W; m_write_b(PIC16C5x_PORTB, PORTB & (uint8_t)(~m_TRISB), 0xff); break; }
		case 7:     if ((m_picmodel == 0x16C55) || (m_picmodel == 0x16C57)) {
						if   (m_TRISC == m_W) break;
						else { m_TRISC = m_W; m_write_c(PIC16C5x_PORTC, PORTC & (uint8_t)(~m_TRISC), 0xff); break; }
>>>>>>> upstream/master
					}
					else {
						illegal(); break;
					}
		default:    illegal(); break;
	}
}

void pic16c5x_device::xorlw()
{
	m_ALU = m_W ^ m_opcode.b.l;
	m_W = m_ALU;
	CALCULATE_Z_FLAG();
}

void pic16c5x_device::xorwf()
{
	m_ALU = GET_REGFILE(ADDR) ^ m_W;
	STORE_RESULT(ADDR, m_ALU);
	CALCULATE_Z_FLAG();
}




/***********************************************************************
 *  Opcode Table (Cycles, Instruction)
 ***********************************************************************/

const pic16c5x_device::pic16c5x_opcode pic16c5x_device::s_opcode_main[256]=
{
<<<<<<< HEAD
/*00*/  {1, &pic16c5x_device::nop     },{0, &pic16c5x_device::illegal   },{1, &pic16c5x_device::movwf     },{1, &pic16c5x_device::movwf     },
		{1, &pic16c5x_device::clrw    },{0, &pic16c5x_device::illegal   },{1, &pic16c5x_device::clrf      },{1, &pic16c5x_device::clrf      },
=======
/*00*/  {1, &pic16c5x_device::nop     },{1, &pic16c5x_device::illegal   },{1, &pic16c5x_device::movwf     },{1, &pic16c5x_device::movwf     },
		{1, &pic16c5x_device::clrw    },{1, &pic16c5x_device::illegal   },{1, &pic16c5x_device::clrf      },{1, &pic16c5x_device::clrf      },
>>>>>>> upstream/master
/*08*/  {1, &pic16c5x_device::subwf   },{1, &pic16c5x_device::subwf     },{1, &pic16c5x_device::subwf     },{1, &pic16c5x_device::subwf     },
		{1, &pic16c5x_device::decf    },{1, &pic16c5x_device::decf      },{1, &pic16c5x_device::decf      },{1, &pic16c5x_device::decf      },
/*10*/  {1, &pic16c5x_device::iorwf   },{1, &pic16c5x_device::iorwf     },{1, &pic16c5x_device::iorwf     },{1, &pic16c5x_device::iorwf     },
		{1, &pic16c5x_device::andwf   },{1, &pic16c5x_device::andwf     },{1, &pic16c5x_device::andwf     },{1, &pic16c5x_device::andwf     },
/*18*/  {1, &pic16c5x_device::xorwf   },{1, &pic16c5x_device::xorwf     },{1, &pic16c5x_device::xorwf     },{1, &pic16c5x_device::xorwf     },
		{1, &pic16c5x_device::addwf   },{1, &pic16c5x_device::addwf     },{1, &pic16c5x_device::addwf     },{1, &pic16c5x_device::addwf     },
/*20*/  {1, &pic16c5x_device::movf    },{1, &pic16c5x_device::movf      },{1, &pic16c5x_device::movf      },{1, &pic16c5x_device::movf      },
		{1, &pic16c5x_device::comf    },{1, &pic16c5x_device::comf      },{1, &pic16c5x_device::comf      },{1, &pic16c5x_device::comf      },
/*28*/  {1, &pic16c5x_device::incf    },{1, &pic16c5x_device::incf      },{1, &pic16c5x_device::incf      },{1, &pic16c5x_device::incf      },
		{1, &pic16c5x_device::decfsz  },{1, &pic16c5x_device::decfsz    },{1, &pic16c5x_device::decfsz    },{1, &pic16c5x_device::decfsz    },
/*30*/  {1, &pic16c5x_device::rrf     },{1, &pic16c5x_device::rrf       },{1, &pic16c5x_device::rrf       },{1, &pic16c5x_device::rrf       },
		{1, &pic16c5x_device::rlf     },{1, &pic16c5x_device::rlf       },{1, &pic16c5x_device::rlf       },{1, &pic16c5x_device::rlf       },
/*38*/  {1, &pic16c5x_device::swapf   },{1, &pic16c5x_device::swapf     },{1, &pic16c5x_device::swapf     },{1, &pic16c5x_device::swapf     },
		{1, &pic16c5x_device::incfsz  },{1, &pic16c5x_device::incfsz    },{1, &pic16c5x_device::incfsz    },{1, &pic16c5x_device::incfsz    },
/*40*/  {1, &pic16c5x_device::bcf     },{1, &pic16c5x_device::bcf       },{1, &pic16c5x_device::bcf       },{1, &pic16c5x_device::bcf       },
		{1, &pic16c5x_device::bcf     },{1, &pic16c5x_device::bcf       },{1, &pic16c5x_device::bcf       },{1, &pic16c5x_device::bcf       },
/*48*/  {1, &pic16c5x_device::bcf     },{1, &pic16c5x_device::bcf       },{1, &pic16c5x_device::bcf       },{1, &pic16c5x_device::bcf       },
		{1, &pic16c5x_device::bcf     },{1, &pic16c5x_device::bcf       },{1, &pic16c5x_device::bcf       },{1, &pic16c5x_device::bcf       },
/*50*/  {1, &pic16c5x_device::bsf     },{1, &pic16c5x_device::bsf       },{1, &pic16c5x_device::bsf       },{1, &pic16c5x_device::bsf       },
		{1, &pic16c5x_device::bsf     },{1, &pic16c5x_device::bsf       },{1, &pic16c5x_device::bsf       },{1, &pic16c5x_device::bsf       },
/*58*/  {1, &pic16c5x_device::bsf     },{1, &pic16c5x_device::bsf       },{1, &pic16c5x_device::bsf       },{1, &pic16c5x_device::bsf       },
		{1, &pic16c5x_device::bsf     },{1, &pic16c5x_device::bsf       },{1, &pic16c5x_device::bsf       },{1, &pic16c5x_device::bsf       },
/*60*/  {1, &pic16c5x_device::btfsc   },{1, &pic16c5x_device::btfsc     },{1, &pic16c5x_device::btfsc     },{1, &pic16c5x_device::btfsc     },
		{1, &pic16c5x_device::btfsc   },{1, &pic16c5x_device::btfsc     },{1, &pic16c5x_device::btfsc     },{1, &pic16c5x_device::btfsc     },
/*68*/  {1, &pic16c5x_device::btfsc   },{1, &pic16c5x_device::btfsc     },{1, &pic16c5x_device::btfsc     },{1, &pic16c5x_device::btfsc     },
		{1, &pic16c5x_device::btfsc   },{1, &pic16c5x_device::btfsc     },{1, &pic16c5x_device::btfsc     },{1, &pic16c5x_device::btfsc     },
/*70*/  {1, &pic16c5x_device::btfss   },{1, &pic16c5x_device::btfss     },{1, &pic16c5x_device::btfss     },{1, &pic16c5x_device::btfss     },
		{1, &pic16c5x_device::btfss   },{1, &pic16c5x_device::btfss     },{1, &pic16c5x_device::btfss     },{1, &pic16c5x_device::btfss     },
/*78*/  {1, &pic16c5x_device::btfss   },{1, &pic16c5x_device::btfss     },{1, &pic16c5x_device::btfss     },{1, &pic16c5x_device::btfss     },
		{1, &pic16c5x_device::btfss   },{1, &pic16c5x_device::btfss     },{1, &pic16c5x_device::btfss     },{1, &pic16c5x_device::btfss     },
/*80*/  {2, &pic16c5x_device::retlw   },{2, &pic16c5x_device::retlw     },{2, &pic16c5x_device::retlw     },{2, &pic16c5x_device::retlw     },
		{2, &pic16c5x_device::retlw   },{2, &pic16c5x_device::retlw     },{2, &pic16c5x_device::retlw     },{2, &pic16c5x_device::retlw     },
/*88*/  {2, &pic16c5x_device::retlw   },{2, &pic16c5x_device::retlw     },{2, &pic16c5x_device::retlw     },{2, &pic16c5x_device::retlw     },
		{2, &pic16c5x_device::retlw   },{2, &pic16c5x_device::retlw     },{2, &pic16c5x_device::retlw     },{2, &pic16c5x_device::retlw     },
/*90*/  {2, &pic16c5x_device::call    },{2, &pic16c5x_device::call      },{2, &pic16c5x_device::call      },{2, &pic16c5x_device::call      },
		{2, &pic16c5x_device::call    },{2, &pic16c5x_device::call      },{2, &pic16c5x_device::call      },{2, &pic16c5x_device::call      },
/*98*/  {2, &pic16c5x_device::call    },{2, &pic16c5x_device::call      },{2, &pic16c5x_device::call      },{2, &pic16c5x_device::call      },
		{2, &pic16c5x_device::call    },{2, &pic16c5x_device::call      },{2, &pic16c5x_device::call      },{2, &pic16c5x_device::call      },
/*A0*/  {2, &pic16c5x_device::goto_op },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },
		{2, &pic16c5x_device::goto_op },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },
/*A8*/  {2, &pic16c5x_device::goto_op },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },
		{2, &pic16c5x_device::goto_op },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },
/*B0*/  {2, &pic16c5x_device::goto_op },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },
		{2, &pic16c5x_device::goto_op },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },
/*B8*/  {2, &pic16c5x_device::goto_op },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },
		{2, &pic16c5x_device::goto_op },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },{2, &pic16c5x_device::goto_op   },
/*C0*/  {1, &pic16c5x_device::movlw   },{1, &pic16c5x_device::movlw     },{1, &pic16c5x_device::movlw     },{1, &pic16c5x_device::movlw     },
		{1, &pic16c5x_device::movlw   },{1, &pic16c5x_device::movlw     },{1, &pic16c5x_device::movlw     },{1, &pic16c5x_device::movlw     },
/*C8*/  {1, &pic16c5x_device::movlw   },{1, &pic16c5x_device::movlw     },{1, &pic16c5x_device::movlw     },{1, &pic16c5x_device::movlw     },
		{1, &pic16c5x_device::movlw   },{1, &pic16c5x_device::movlw     },{1, &pic16c5x_device::movlw     },{1, &pic16c5x_device::movlw     },
/*D0*/  {1, &pic16c5x_device::iorlw   },{1, &pic16c5x_device::iorlw     },{1, &pic16c5x_device::iorlw     },{1, &pic16c5x_device::iorlw     },
		{1, &pic16c5x_device::iorlw   },{1, &pic16c5x_device::iorlw     },{1, &pic16c5x_device::iorlw     },{1, &pic16c5x_device::iorlw     },
/*D8*/  {1, &pic16c5x_device::iorlw   },{1, &pic16c5x_device::iorlw     },{1, &pic16c5x_device::iorlw     },{1, &pic16c5x_device::iorlw     },
		{1, &pic16c5x_device::iorlw   },{1, &pic16c5x_device::iorlw     },{1, &pic16c5x_device::iorlw     },{1, &pic16c5x_device::iorlw     },
/*E0*/  {1, &pic16c5x_device::andlw   },{1, &pic16c5x_device::andlw     },{1, &pic16c5x_device::andlw     },{1, &pic16c5x_device::andlw     },
		{1, &pic16c5x_device::andlw   },{1, &pic16c5x_device::andlw     },{1, &pic16c5x_device::andlw     },{1, &pic16c5x_device::andlw     },
/*E8*/  {1, &pic16c5x_device::andlw   },{1, &pic16c5x_device::andlw     },{1, &pic16c5x_device::andlw     },{1, &pic16c5x_device::andlw     },
		{1, &pic16c5x_device::andlw   },{1, &pic16c5x_device::andlw     },{1, &pic16c5x_device::andlw     },{1, &pic16c5x_device::andlw     },
/*F0*/  {1, &pic16c5x_device::xorlw   },{1, &pic16c5x_device::xorlw     },{1, &pic16c5x_device::xorlw     },{1, &pic16c5x_device::xorlw     },
		{1, &pic16c5x_device::xorlw   },{1, &pic16c5x_device::xorlw     },{1, &pic16c5x_device::xorlw     },{1, &pic16c5x_device::xorlw     },
/*F8*/  {1, &pic16c5x_device::xorlw   },{1, &pic16c5x_device::xorlw     },{1, &pic16c5x_device::xorlw     },{1, &pic16c5x_device::xorlw     },
		{1, &pic16c5x_device::xorlw   },{1, &pic16c5x_device::xorlw     },{1, &pic16c5x_device::xorlw     },{1, &pic16c5x_device::xorlw     }
};


const pic16c5x_device::pic16c5x_opcode pic16c5x_device::s_opcode_00x[16]=
{
<<<<<<< HEAD
/*00*/  {1, &pic16c5x_device::nop     },{0, &pic16c5x_device::illegal   },{1, &pic16c5x_device::option    },{1, &pic16c5x_device::sleepic   },
		{1, &pic16c5x_device::clrwdt  },{1, &pic16c5x_device::tris      },{1, &pic16c5x_device::tris      },{1, &pic16c5x_device::tris      },
/*08*/  {0, &pic16c5x_device::illegal },{0, &pic16c5x_device::illegal   },{0, &pic16c5x_device::illegal   },{0, &pic16c5x_device::illegal   },
		{0, &pic16c5x_device::illegal },{0, &pic16c5x_device::illegal   },{0, &pic16c5x_device::illegal   },{0, &pic16c5x_device::illegal   }
=======
/*00*/  {1, &pic16c5x_device::nop     },{1, &pic16c5x_device::illegal   },{1, &pic16c5x_device::option    },{1, &pic16c5x_device::sleepic   },
		{1, &pic16c5x_device::clrwdt  },{1, &pic16c5x_device::tris      },{1, &pic16c5x_device::tris      },{1, &pic16c5x_device::tris      },
/*08*/  {1, &pic16c5x_device::illegal },{1, &pic16c5x_device::illegal   },{1, &pic16c5x_device::illegal   },{1, &pic16c5x_device::illegal   },
		{1, &pic16c5x_device::illegal },{1, &pic16c5x_device::illegal   },{1, &pic16c5x_device::illegal   },{1, &pic16c5x_device::illegal   }
>>>>>>> upstream/master
};



/****************************************************************************
 *  Inits CPU emulation
 ****************************************************************************/

enum
{
	PIC16C5x_PC=1, PIC16C5x_STK0, PIC16C5x_STK1, PIC16C5x_FSR,
	PIC16C5x_W,    PIC16C5x_ALU,  PIC16C5x_STR,  PIC16C5x_OPT,
<<<<<<< HEAD
	PIC16C5x_TMR0, PIC16C5x_PRTA, PIC16C5x_PRTB, PIC16C5x_PRTC,
=======
	PIC16C5x_TMR0, PIC16C5x_PRTA, PIC16C5x_PRTB, PIC16C5x_PRTC, PIC16C5x_PRTD,
>>>>>>> upstream/master
	PIC16C5x_WDT,  PIC16C5x_TRSA, PIC16C5x_TRSB, PIC16C5x_TRSC,
	PIC16C5x_PSCL
};

void pic16c5x_device::device_start()
{
	m_program = &space(AS_PROGRAM);
	m_direct = &m_program->direct();
	m_data = &space(AS_DATA);

	m_read_a.resolve_safe(0);
	m_read_b.resolve_safe(0);
	m_read_c.resolve_safe(0);
<<<<<<< HEAD
	m_write_a.resolve_safe();
	m_write_b.resolve_safe();
	m_write_c.resolve_safe();
	m_read_t0.resolve_safe(0);
=======
	m_read_d.resolve_safe(0);
	m_write_a.resolve_safe();
	m_write_b.resolve_safe();
	m_write_c.resolve_safe();
	m_write_d.resolve_safe();
>>>>>>> upstream/master

	/* ensure the internal ram pointers are set before get_info is called */
	update_internalram_ptr();

	save_item(NAME(m_W));
	save_item(NAME(m_ALU));
	save_item(NAME(m_OPTION));
<<<<<<< HEAD
	save_item(NAME(TMR0));
	save_item(NAME(PCL));
	save_item(NAME(STATUS));
	save_item(NAME(FSR));
	save_item(NAME(PORTA));
	save_item(NAME(PORTB));
	save_item(NAME(PORTC));
	save_item(NAME(m_TRISA));
	save_item(NAME(m_TRISB));
	save_item(NAME(m_TRISC));
	save_item(NAME(m_old_T0));
=======
	save_item(NAME(m_TRISA));
	save_item(NAME(m_TRISB));
	save_item(NAME(m_TRISC));
	save_item(NAME(m_rtcc));
	save_item(NAME(m_count_pending));
>>>>>>> upstream/master
	save_item(NAME(m_old_data));
	save_item(NAME(m_picRAMmask));
	save_item(NAME(m_WDT));
	save_item(NAME(m_prescaler));
<<<<<<< HEAD
	save_item(NAME(m_STACK[0]));
	save_item(NAME(m_STACK[1]));
=======
	save_item(NAME(m_STACK));
>>>>>>> upstream/master
	save_item(NAME(m_PC));
	save_item(NAME(m_PREVPC));
	save_item(NAME(m_CONFIG));
	save_item(NAME(m_opcode.d));
	save_item(NAME(m_delay_timer));
	save_item(NAME(m_picmodel));
	save_item(NAME(m_reset_vector));

	save_item(NAME(m_temp_config));
	save_item(NAME(m_inst_cycles));

	state_add( PIC16C5x_PC,   "PC",   m_PC).mask(0xfff).formatstr("%03X");
	state_add( PIC16C5x_W,    "W",    m_W).formatstr("%02X");
	state_add( PIC16C5x_ALU,  "ALU",  m_ALU).formatstr("%02X");
	state_add( PIC16C5x_STR,  "STR",  m_debugger_temp).mask(0xff).callimport().callexport().formatstr("%02X");
	state_add( PIC16C5x_TMR0, "TMR",  m_debugger_temp).mask(0xff).callimport().callexport().formatstr("%02X");
	state_add( PIC16C5x_WDT,  "WDT",  m_WDT).formatstr("%04X");
	state_add( PIC16C5x_OPT,  "OPT",  m_OPTION).formatstr("%02X");
	state_add( PIC16C5x_STK0, "STK0", m_STACK[0]).mask(0xfff).formatstr("%03X");
	state_add( PIC16C5x_STK1, "STK1", m_STACK[1]).mask(0xfff).formatstr("%03X");
<<<<<<< HEAD
	state_add( PIC16C5x_PRTA, "PRTA", m_debugger_temp).mask(0xf).callimport().callexport().formatstr("%01X");
	state_add( PIC16C5x_PRTB, "PRTB", m_debugger_temp).mask(0xff).callimport().callexport().formatstr("%02X");
	state_add( PIC16C5x_PRTC, "PRTC", m_debugger_temp).mask(0xff).callimport().callexport().formatstr("%02X");
=======
	state_add( PIC16C5x_PRTA, "PRTA", m_debugger_temp).mask(0xff).callimport().callexport().formatstr("%02X");
	state_add( PIC16C5x_PRTB, "PRTB", m_debugger_temp).mask(0xff).callimport().callexport().formatstr("%02X");
	state_add( PIC16C5x_PRTC, "PRTC", m_debugger_temp).mask(0xff).callimport().callexport().formatstr("%02X");
	state_add( PIC16C5x_PRTD, "PRTD", m_debugger_temp).mask(0xff).callimport().callexport().formatstr("%02X");
>>>>>>> upstream/master
	state_add( PIC16C5x_TRSA, "TRSA", m_TRISA).mask(0xf).formatstr("%01X");
	state_add( PIC16C5x_TRSB, "TRSB", m_TRISB).formatstr("%02X");
	state_add( PIC16C5x_TRSC, "TRSC", m_TRISC).formatstr("%02X");
	state_add( PIC16C5x_FSR,  "FSR",  m_debugger_temp).mask(0xff).callimport().callexport().formatstr("%02X");
	state_add( PIC16C5x_PSCL, "PSCL", m_debugger_temp).callimport().formatstr("%3s");

	state_add( STATE_GENPC, "GENPC", m_PC).noshow();
<<<<<<< HEAD
	state_add( STATE_GENFLAGS, "GENFLAGS", m_OPTION).formatstr("%13s").noshow();
	state_add( STATE_GENPCBASE, "PREVPC", m_PREVPC).noshow();
=======
	state_add( STATE_GENPCBASE, "CURPC", m_PREVPC).noshow();
	state_add( STATE_GENFLAGS, "GENFLAGS", m_OPTION).formatstr("%13s").noshow();
>>>>>>> upstream/master

	m_icountptr = &m_icount;
}


void pic16c5x_device::state_import(const device_state_entry &entry)
{
	switch (entry.index())
	{
		case PIC16C5x_STR:
			STATUS = m_debugger_temp;
			break;
		case PIC16C5x_TMR0:
			TMR0 = m_debugger_temp;
			break;
		case PIC16C5x_PRTA:
			PORTA = m_debugger_temp;
			break;
		case PIC16C5x_PRTB:
			PORTB = m_debugger_temp;
			break;
		case PIC16C5x_PRTC:
			PORTC = m_debugger_temp;
			break;
<<<<<<< HEAD
		case PIC16C5x_FSR:
			FSR = ((m_debugger_temp & m_picRAMmask) | (UINT8)(~m_picRAMmask));
=======
		case PIC16C5x_PRTD:
			PORTD = m_debugger_temp;
			break;
		case PIC16C5x_FSR:
			FSR = ((m_debugger_temp & m_picRAMmask) | (uint8_t)(~m_picRAMmask));
>>>>>>> upstream/master
			break;
		case PIC16C5x_PSCL:
			m_prescaler = m_debugger_temp;
			break;
	}
}

void pic16c5x_device::state_export(const device_state_entry &entry)
{
	switch (entry.index())
	{
		case PIC16C5x_STR:
			m_debugger_temp = STATUS;
			break;
		case PIC16C5x_TMR0:
			m_debugger_temp = TMR0;
			break;
		case PIC16C5x_PRTA:
<<<<<<< HEAD
			m_debugger_temp = PORTA & 0x0f;
=======
			m_debugger_temp = PORTA;
>>>>>>> upstream/master
			break;
		case PIC16C5x_PRTB:
			m_debugger_temp = PORTB;
			break;
		case PIC16C5x_PRTC:
			m_debugger_temp = PORTC;
			break;
<<<<<<< HEAD
		case PIC16C5x_FSR:
			m_debugger_temp = ((FSR) & m_picRAMmask) | (UINT8)(~m_picRAMmask);
=======
		case PIC16C5x_PRTD:
			m_debugger_temp = PORTD;
			break;
		case PIC16C5x_FSR:
			m_debugger_temp = ((FSR) & m_picRAMmask) | (uint8_t)(~m_picRAMmask);
>>>>>>> upstream/master
			break;
	}
}

<<<<<<< HEAD
void pic16c5x_device::state_string_export(const device_state_entry &entry, std::string &str)
=======
void pic16c5x_device::state_string_export(const device_state_entry &entry, std::string &str) const
>>>>>>> upstream/master
{
	switch (entry.index())
	{
		case PIC16C5x_PSCL:
<<<<<<< HEAD
			strprintf(str, "%c%02X", ((m_OPTION & 0x08) ? 'W' : 'T'), m_prescaler);
			break;

		case STATE_GENFLAGS:
			strprintf(str, "%01x%c%c%c%c%c %c%c%c%03x",
=======
			str = string_format("%c%02X", ((m_OPTION & 0x08) ? 'W' : 'T'), m_prescaler);
			break;

		case STATE_GENFLAGS:
			str = string_format("%01x%c%c%c%c%c %c%c%c%03x",
>>>>>>> upstream/master
				(STATUS & 0xe0) >> 5,
				STATUS & 0x10 ? '.':'O',      /* WDT Overflow */
				STATUS & 0x08 ? 'P':'D',      /* Power/Down */
				STATUS & 0x04 ? 'Z':'.',      /* Zero */
				STATUS & 0x02 ? 'c':'b',      /* Nibble Carry/Borrow */
				STATUS & 0x01 ? 'C':'B',      /* Carry/Borrow */

				m_OPTION & 0x20 ? 'C':'T',      /* Counter/Timer */
				m_OPTION & 0x10 ? 'N':'P',      /* Negative/Positive */
				m_OPTION & 0x08 ? 'W':'T',      /* WatchDog/Timer */
				m_OPTION & 0x08 ? (1<<(m_OPTION&7)) : (2<<(m_OPTION&7)) );
			break;
	}
}

/****************************************************************************
 *  Reset registers to their initial values
 ****************************************************************************/

void pic16c5x_device::pic16c5x_reset_regs()
{
	m_PC     = m_reset_vector;
	m_CONFIG = m_temp_config;
	m_TRISA  = 0xff;
	m_TRISB  = 0xff;
	m_TRISC  = 0xff;
	m_OPTION = (T0CS_FLAG | T0SE_FLAG | PSA_FLAG | PS_REG);
	PCL    = 0xff;
<<<<<<< HEAD
	FSR   |= (UINT8)(~m_picRAMmask);
	PORTA &= 0x0f;
	m_prescaler = 0;
	m_delay_timer = 0;
	m_old_T0 = 0;
	m_inst_cycles = 0;
=======
	FSR   |= (uint8_t)(~m_picRAMmask);
	m_prescaler = 0;
	m_delay_timer = 0;
	m_inst_cycles = 0;
	m_count_pending = false;
>>>>>>> upstream/master
}

void pic16c5x_device::pic16c5x_soft_reset()
{
	SET(STATUS, (TO_FLAG | PD_FLAG | Z_FLAG | DC_FLAG | C_FLAG));
	pic16c5x_reset_regs();
}

<<<<<<< HEAD
void pic16c5x_device::pic16c5x_set_config(UINT16 data)
=======
void pic16c5x_device::pic16c5x_set_config(uint16_t data)
>>>>>>> upstream/master
{
	logerror("Writing %04x to the PIC16C5x config register\n",data);
	m_temp_config = data;
}


void pic16c5x_device::device_reset()
{
	pic16c5x_reset_regs();
	CLR(STATUS, PA_REG);
	SET(STATUS, (TO_FLAG | PD_FLAG));
}


/****************************************************************************
 *  WatchDog
 ****************************************************************************/

void pic16c5x_device::pic16c5x_update_watchdog(int counts)
{
	/* WatchDog is set up to count 18,000 (0x464f hex) ticks to provide */
	/* the timeout period of 0.018ms based on a 4MHz input clock. */
	/* Note: the 4MHz clock should be divided by the PIC16C5x_CLOCK_DIVIDER */
	/* which effectively makes the PIC run at 1MHz internally. */

	/* If the current instruction is CLRWDT or SLEEP, don't update the WDT */

	if ((m_opcode.w.l != 3) && (m_opcode.w.l != 4))
	{
<<<<<<< HEAD
		UINT16 old_WDT = m_WDT;
=======
		uint16_t old_WDT = m_WDT;
>>>>>>> upstream/master

		m_WDT -= counts;

		if (m_WDT > 0x464f) {
			m_WDT = 0x464f - (0xffff - m_WDT);
		}

		if (((old_WDT != 0) && (old_WDT < m_WDT)) || (m_WDT == 0))
		{
			if (PSA) {
				m_prescaler++;
				if (m_prescaler >= (1 << PS)) { /* Prescale values from 1 to 128 */
					m_prescaler = 0;
					CLR(STATUS, TO_FLAG);
					pic16c5x_soft_reset();
				}
			}
			else {
				CLR(STATUS, TO_FLAG);
				pic16c5x_soft_reset();
			}
		}
	}
}


/****************************************************************************
 *  Update Timer
 ****************************************************************************/

void pic16c5x_device::pic16c5x_update_timer(int counts)
{
	if (PSA == 0) {
		m_prescaler += counts;
		if (m_prescaler >= (2 << PS)) { /* Prescale values from 2 to 256 */
			TMR0 += (m_prescaler / (2 << PS));
			m_prescaler %= (2 << PS);   /* Overflow prescaler */
		}
	}
	else {
		TMR0 += counts;
	}
}

<<<<<<< HEAD
=======
void pic16c5x_device::execute_set_input(int line, int state)
{
	switch (line)
	{
		/* RTCC/T0CKI pin */
		case PIC16C5x_RTCC:
			if (T0CS && state != m_rtcc) /* Count mode, edge triggered */
				if ((T0SE && !state) || (!T0SE && state))
					m_count_pending = true;

			m_rtcc = state;
			break;

		default:
			break;
	}
}

>>>>>>> upstream/master

/****************************************************************************
 *  Execute IPeriod. Return 0 if emulation should be stopped
 ****************************************************************************/

void pic16c5x_device::execute_run()
{
<<<<<<< HEAD
	UINT8 T0_in;

=======
>>>>>>> upstream/master
	update_internalram_ptr();

	do
	{
<<<<<<< HEAD
		if (PD == 0)                        /* Sleep Mode */
		{
=======
		if (PD == 0) /* Sleep Mode */
		{
			m_count_pending = false;
>>>>>>> upstream/master
			m_inst_cycles = 1;
			debugger_instruction_hook(this, m_PC);
			if (WDTE) {
				pic16c5x_update_watchdog(1);
			}
		}
		else
		{
<<<<<<< HEAD
=======
			if (m_count_pending) { /* RTCC/T0CKI clocked while in Count mode */
				m_count_pending = false;
				pic16c5x_update_timer(1);
			}

>>>>>>> upstream/master
			m_PREVPC = m_PC;

			debugger_instruction_hook(this, m_PC);

			m_opcode.d = M_RDOP(m_PC);
			m_PC++;
			PCL++;

<<<<<<< HEAD
			if ((m_opcode.w.l & 0xff0) != 0x000)    {   /* Do all opcodes except the 00? ones */
=======
			if (m_picmodel == 0x1650 || m_picmodel == 0x1655 || (m_opcode.w.l & 0xff0) != 0x000) { /* Do all opcodes except the 00? ones */
>>>>>>> upstream/master
				m_inst_cycles = s_opcode_main[((m_opcode.w.l >> 4) & 0xff)].cycles;
				(this->*s_opcode_main[((m_opcode.w.l >> 4) & 0xff)].function)();
			}
			else {  /* Opcode 0x00? has many opcodes in its minor nibble */
				m_inst_cycles = s_opcode_00x[(m_opcode.b.l & 0x1f)].cycles;
				(this->*s_opcode_00x[(m_opcode.b.l & 0x1f)].function)();
			}

<<<<<<< HEAD
			if (T0CS) {                     /* Count mode */
				T0_in = m_read_t0() ? 1 : 0;
				if (T0SE) {                 /* Count falling edge T0 input */
					if (FALLING_EDGE_T0) {
						pic16c5x_update_timer(1);
					}
				}
				else {                      /* Count rising edge T0 input */
					if (RISING_EDGE_T0) {
						pic16c5x_update_timer(1);
					}
				}
				m_old_T0 = T0_in;
			}
			else {                          /* Timer mode */
=======
			if (!T0CS) { /* Timer mode */
>>>>>>> upstream/master
				if (m_delay_timer) {
					m_delay_timer--;
				}
				else {
					pic16c5x_update_timer(m_inst_cycles);
				}
			}
			if (WDTE) {
				pic16c5x_update_watchdog(m_inst_cycles);
			}
		}

		m_icount -= m_inst_cycles;

	} while (m_icount > 0);
}
