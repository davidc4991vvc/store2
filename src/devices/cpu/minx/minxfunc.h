// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
UINT8 minx_cpu_device::ADD8( UINT8 arg1, UINT8 arg2 )
{
	UINT32 res = arg1 + arg2;
=======
uint8_t minx_cpu_device::ADD8( uint8_t arg1, uint8_t arg2 )
{
	uint32_t res = arg1 + arg2;
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_O | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( ( arg2 ^ arg1 ^ 0x80 ) & ( arg2 ^ res ) & 0x80 ) ? FLAG_O : 0 )
		| ( ( res & 0xFF00 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res & 0xFF;
}


<<<<<<< HEAD
UINT16 minx_cpu_device::ADD16( UINT16 arg1, UINT16 arg2 )
{
	UINT32 res = arg1 + arg2;
=======
uint16_t minx_cpu_device::ADD16( uint16_t arg1, uint16_t arg2 )
{
	uint32_t res = arg1 + arg2;
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_O | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x8000 ) ? FLAG_S : 0 )
		| ( ( ( arg2 ^ arg1 ^ 0x8000 ) & ( arg2 ^ res ) & 0x8000 ) ? FLAG_O : 0 )
		| ( ( res & 0xFF0000 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res & 0xFFFF;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::ADDC8( UINT8 arg1, UINT8 arg2 )
{
	UINT32 res = arg1 + arg2 + ( ( m_F & FLAG_C ) ? 1 : 0 );
=======
uint8_t minx_cpu_device::ADDC8( uint8_t arg1, uint8_t arg2 )
{
	uint32_t res = arg1 + arg2 + ( ( m_F & FLAG_C ) ? 1 : 0 );
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_O | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( ( arg2 ^ arg1 ^ 0x80 ) & ( arg2 ^ res ) & 0x80 ) ? FLAG_O : 0 )
		| ( ( res & 0xFF00 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res & 0xFF;
}


<<<<<<< HEAD
UINT16 minx_cpu_device::ADDC16( UINT16 arg1, UINT16 arg2 )
{
	UINT32 res = arg1 + arg2 + ( ( m_F & FLAG_C ) ? 1 : 0 );
=======
uint16_t minx_cpu_device::ADDC16( uint16_t arg1, uint16_t arg2 )
{
	uint32_t res = arg1 + arg2 + ( ( m_F & FLAG_C ) ? 1 : 0 );
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_O | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x8000 ) ? FLAG_S : 0 )
		| ( ( ( arg2 ^ arg1 ^ 0x8000 ) & ( arg2 ^ res ) & 0x8000 ) ? FLAG_O : 0 )
		| ( ( res & 0xFF0000 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res & 0xFFFF;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::INC8( UINT8 arg )
{
	UINT8 old_F = m_F;
	UINT8 res = ADD8( arg, 1 );
=======
uint8_t minx_cpu_device::INC8( uint8_t arg )
{
	uint8_t old_F = m_F;
	uint8_t res = ADD8( arg, 1 );
>>>>>>> upstream/master
	m_F = ( old_F & ~ ( FLAG_Z ) )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res;
}


<<<<<<< HEAD
UINT16 minx_cpu_device::INC16( UINT16 arg )
{
	UINT8 old_F = m_F;
	UINT16 res = ADD16( arg, 1 );
=======
uint16_t minx_cpu_device::INC16( uint16_t arg )
{
	uint8_t old_F = m_F;
	uint16_t res = ADD16( arg, 1 );
>>>>>>> upstream/master
	m_F = ( old_F & ~ ( FLAG_Z ) )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::SUB8( UINT8 arg1, UINT8 arg2 )
{
	UINT32 res = arg1 - arg2;
=======
uint8_t minx_cpu_device::SUB8( uint8_t arg1, uint8_t arg2 )
{
	uint32_t res = arg1 - arg2;
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_O | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( ( arg2 ^ arg1 ) & ( arg1 ^ res ) & 0x80 ) ? FLAG_O : 0 )
		| ( ( res & 0xFF00 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res & 0xFF;
}


<<<<<<< HEAD
UINT16 minx_cpu_device::SUB16( UINT16 arg1, UINT16 arg2 )
{
	UINT32 res = arg1 - arg2;
=======
uint16_t minx_cpu_device::SUB16( uint16_t arg1, uint16_t arg2 )
{
	uint32_t res = arg1 - arg2;
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_O | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x8000 ) ? FLAG_S : 0 )
		| ( ( ( arg2 ^ arg1 ) & ( arg1 ^ res ) & 0x8000 ) ? FLAG_O : 0 )
		| ( ( res & 0xFF0000 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res & 0xFFFF;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::SUBC8( UINT8 arg1, UINT8 arg2 )
{
	UINT32 res = arg1 - arg2 - ( ( m_F & FLAG_C ) ? 1 : 0 );
=======
uint8_t minx_cpu_device::SUBC8( uint8_t arg1, uint8_t arg2 )
{
	uint32_t res = arg1 - arg2 - ( ( m_F & FLAG_C ) ? 1 : 0 );
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_O | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( ( arg2 ^ arg1 ) & ( arg1 ^ res ) & 0x80 ) ? FLAG_O : 0 )
		| ( ( res & 0xFF00 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res & 0xFF;
}


<<<<<<< HEAD
UINT16 minx_cpu_device::SUBC16( UINT16 arg1, UINT16 arg2 )
{
	UINT32 res = arg1 - arg2 - ( ( m_F & FLAG_C ) ? 1 : 0 );
=======
uint16_t minx_cpu_device::SUBC16( uint16_t arg1, uint16_t arg2 )
{
	uint32_t res = arg1 - arg2 - ( ( m_F & FLAG_C ) ? 1 : 0 );
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_O | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x8000 ) ? FLAG_S : 0 )
		| ( ( ( arg2 ^ arg1 ) & ( arg1 ^ res ) & 0x8000 ) ? FLAG_O : 0 )
		| ( ( res & 0xFF0000 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res & 0xFFFF;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::DEC8( UINT8 arg )
{
	UINT8 old_F = m_F;
	UINT8 res = SUB8( arg, 1 );
=======
uint8_t minx_cpu_device::DEC8( uint8_t arg )
{
	uint8_t old_F = m_F;
	uint8_t res = SUB8( arg, 1 );
>>>>>>> upstream/master
	m_F = ( old_F & ~ ( FLAG_Z ) )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res;
}


<<<<<<< HEAD
UINT16 minx_cpu_device::DEC16( UINT16 arg )
{
	UINT8 old_F = m_F;
	UINT16 res = SUB16( arg, 1 );
=======
uint16_t minx_cpu_device::DEC16( uint16_t arg )
{
	uint8_t old_F = m_F;
	uint16_t res = SUB16( arg, 1 );
>>>>>>> upstream/master
	m_F = ( old_F & ~ ( FLAG_Z ) )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::AND8( UINT8 arg1, UINT8 arg2 )
{
	UINT8 res = arg1 & arg2;
=======
uint8_t minx_cpu_device::AND8( uint8_t arg1, uint8_t arg2 )
{
	uint8_t res = arg1 & arg2;
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::OR8( UINT8 arg1, UINT8 arg2 )
{
	UINT8 res = arg1 | arg2;
=======
uint8_t minx_cpu_device::OR8( uint8_t arg1, uint8_t arg2 )
{
	uint8_t res = arg1 | arg2;
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::XOR8( UINT8 arg1, UINT8 arg2 )
{
	UINT8 res = arg1 ^ arg2;
=======
uint8_t minx_cpu_device::XOR8( uint8_t arg1, uint8_t arg2 )
{
	uint8_t res = arg1 ^ arg2;
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::NOT8( UINT8 arg )
{
	UINT8 res = ~arg;
=======
uint8_t minx_cpu_device::NOT8( uint8_t arg )
{
	uint8_t res = ~arg;
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::NEG8( UINT8 arg )
{
	UINT8 res = -arg;
=======
uint8_t minx_cpu_device::NEG8( uint8_t arg )
{
	uint8_t res = -arg;
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_O | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::SAL8( UINT8 arg )
{
	UINT16 res = arg << 1;
=======
uint8_t minx_cpu_device::SAL8( uint8_t arg )
{
	uint16_t res = arg << 1;
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_O | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( arg != 0 && res == 0 ) ? FLAG_O : 0 )
		| ( ( arg & 0x80 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::SAR8( UINT8 arg )
{
	UINT16 res = ( arg >> 1 ) | ( arg & 0x80 );
=======
uint8_t minx_cpu_device::SAR8( uint8_t arg )
{
	uint16_t res = ( arg >> 1 ) | ( arg & 0x80 );
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_O | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( arg != 0x80 && res == 0x80 ) ? FLAG_O : 0 )
		| ( ( arg & 0x01 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res & 0xFF;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::SHL8( UINT8 arg )
{
	UINT16 res = arg << 1;
=======
uint8_t minx_cpu_device::SHL8( uint8_t arg )
{
	uint16_t res = arg << 1;
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( arg & 0x80 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::SHR8( UINT8 arg )
{
	UINT16 res = arg >> 1;
=======
uint8_t minx_cpu_device::SHR8( uint8_t arg )
{
	uint16_t res = arg >> 1;
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( arg & 0x01 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res & 0xFF;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::ROLC8( UINT8 arg )
{
	UINT16 res = ( arg << 1 ) | ( ( m_F & FLAG_C ) ? 1 : 0 );
=======
uint8_t minx_cpu_device::ROLC8( uint8_t arg )
{
	uint16_t res = ( arg << 1 ) | ( ( m_F & FLAG_C ) ? 1 : 0 );
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( arg & 0x80 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res & 0xFF;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::RORC8( UINT8 arg )
{
	UINT16 res = ( arg >> 1 ) | ( ( m_F & FLAG_C ) ? 0x80 : 0 );
=======
uint8_t minx_cpu_device::RORC8( uint8_t arg )
{
	uint16_t res = ( arg >> 1 ) | ( ( m_F & FLAG_C ) ? 0x80 : 0 );
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( arg & 0x01 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res & 0xFF;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::ROL8( UINT8 arg )
{
	UINT16 res = ( arg << 1 ) | ( ( arg & 0x80 ) ? 1 : 0 );
=======
uint8_t minx_cpu_device::ROL8( uint8_t arg )
{
	uint16_t res = ( arg << 1 ) | ( ( arg & 0x80 ) ? 1 : 0 );
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( arg & 0x80 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res & 0xFF;
}


<<<<<<< HEAD
UINT8 minx_cpu_device::ROR8( UINT8 arg )
{
	UINT16 res = ( arg >> 1 ) | ( ( arg & 0x01 ) ? 0x80 : 0 );
=======
uint8_t minx_cpu_device::ROR8( uint8_t arg )
{
	uint16_t res = ( arg >> 1 ) | ( ( arg & 0x01 ) ? 0x80 : 0 );
>>>>>>> upstream/master
	m_F = ( m_F & ~ ( FLAG_S | FLAG_C | FLAG_Z ) )
		| ( ( res & 0x80 ) ? FLAG_S : 0 )
		| ( ( arg & 0x01 ) ? FLAG_C : 0 )
		| ( ( res ) ? 0 : FLAG_Z )
	;
	return res & 0xFF;
}


<<<<<<< HEAD
void minx_cpu_device::PUSH8( UINT8 arg )
=======
void minx_cpu_device::PUSH8( uint8_t arg )
>>>>>>> upstream/master
{
	m_SP = m_SP - 1;
	WR( m_SP, arg );
}


<<<<<<< HEAD
void minx_cpu_device::PUSH16( UINT16 arg )
=======
void minx_cpu_device::PUSH16( uint16_t arg )
>>>>>>> upstream/master
{
	PUSH8( arg >> 8 );
	PUSH8( arg & 0x00FF );
}


<<<<<<< HEAD
UINT8 minx_cpu_device::POP8()
{
	UINT8 res = RD( m_SP );
=======
uint8_t minx_cpu_device::POP8()
{
	uint8_t res = RD( m_SP );
>>>>>>> upstream/master
	m_SP = m_SP + 1;
	return res;
}


<<<<<<< HEAD
UINT16 minx_cpu_device::POP16()
=======
uint16_t minx_cpu_device::POP16()
>>>>>>> upstream/master
{
	return POP8() | ( POP8() << 8 );
}


<<<<<<< HEAD
void minx_cpu_device::JMP( UINT16 arg )
=======
void minx_cpu_device::JMP( uint16_t arg )
>>>>>>> upstream/master
{
	m_V = m_U;
	m_PC = arg;
}


<<<<<<< HEAD
void minx_cpu_device::CALL( UINT16 arg )
=======
void minx_cpu_device::CALL( uint16_t arg )
>>>>>>> upstream/master
{
	PUSH8( m_V );
	PUSH16( m_PC );
	JMP( arg );
}


<<<<<<< HEAD
#define AD1_IHL UINT32 addr1 = ( m_I << 16 ) | m_HL
#define AD1_IN8 UINT32 addr1 = ( m_I << 16 ) | ( m_N << 8 ) | rdop()
#define AD1_I16 UINT32 addr1 = ( m_I << 16 ) | rdop16()
#define AD1_XIX UINT32 addr1 = ( m_XI << 16 ) | m_X
#define AD1_YIY UINT32 addr1 = ( m_YI << 16 ) | m_Y
#define AD1_X8  UINT32 addr1 = ( m_XI << 16 ) | ( m_X + rdop() )
#define AD1_Y8  UINT32 addr1 = ( m_YI << 16 ) | ( m_Y + rdop() )
#define AD1_XL  UINT32 addr1 = ( m_XI << 16 ) | ( m_X + ( m_HL & 0x00FF ) )
#define AD1_YL  UINT32 addr1 = ( m_YI << 16 ) | ( m_Y + ( m_HL & 0x00FF ) )
#define AD2_IHL UINT32 addr2 = ( m_I << 16 ) | m_HL
#define AD2_IN8 UINT32 addr2 = ( m_I << 16 ) | ( m_N << 8 ) | rdop()
#define AD2_I16 UINT32 addr2 = ( m_I << 16 ) | rdop(); addr2 |= ( rdop() << 8 )
#define AD2_XIX UINT32 addr2 = ( m_XI << 16 ) | m_X
#define AD2_YIY UINT32 addr2 = ( m_YI << 16 ) | m_Y
#define AD2_X8  UINT32 addr2 = ( m_XI << 16 ) | ( m_X + rdop() )
#define AD2_Y8  UINT32 addr2 = ( m_YI << 16 ) | ( m_Y + rdop() )
#define AD2_XL  UINT32 addr2 = ( m_XI << 16 ) | ( m_X + ( m_HL & 0x00FF ) )
#define AD2_YL  UINT32 addr2 = ( m_YI << 16 ) | ( m_Y + ( m_HL & 0x00FF ) )
=======
#define AD1_IHL uint32_t addr1 = ( m_I << 16 ) | m_HL
#define AD1_IN8 uint32_t addr1 = ( m_I << 16 ) | ( m_N << 8 ) | rdop()
#define AD1_I16 uint32_t addr1 = ( m_I << 16 ) | rdop16()
#define AD1_XIX uint32_t addr1 = ( m_XI << 16 ) | m_X
#define AD1_YIY uint32_t addr1 = ( m_YI << 16 ) | m_Y
#define AD1_X8  uint32_t addr1 = ( m_XI << 16 ) | ( m_X + rdop() )
#define AD1_Y8  uint32_t addr1 = ( m_YI << 16 ) | ( m_Y + rdop() )
#define AD1_XL  uint32_t addr1 = ( m_XI << 16 ) | ( m_X + ( m_HL & 0x00FF ) )
#define AD1_YL  uint32_t addr1 = ( m_YI << 16 ) | ( m_Y + ( m_HL & 0x00FF ) )
#define AD2_IHL uint32_t addr2 = ( m_I << 16 ) | m_HL
#define AD2_IN8 uint32_t addr2 = ( m_I << 16 ) | ( m_N << 8 ) | rdop()
#define AD2_I16 uint32_t addr2 = ( m_I << 16 ) | rdop(); addr2 |= ( rdop() << 8 )
#define AD2_XIX uint32_t addr2 = ( m_XI << 16 ) | m_X
#define AD2_YIY uint32_t addr2 = ( m_YI << 16 ) | m_Y
#define AD2_X8  uint32_t addr2 = ( m_XI << 16 ) | ( m_X + rdop() )
#define AD2_Y8  uint32_t addr2 = ( m_YI << 16 ) | ( m_Y + rdop() )
#define AD2_XL  uint32_t addr2 = ( m_XI << 16 ) | ( m_X + ( m_HL & 0x00FF ) )
#define AD2_YL  uint32_t addr2 = ( m_YI << 16 ) | ( m_Y + ( m_HL & 0x00FF ) )
>>>>>>> upstream/master
