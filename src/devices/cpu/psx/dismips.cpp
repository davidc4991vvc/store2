// license:BSD-3-Clause
// copyright-holders:smf
/*
 * standalone MIPS disassembler by smf
 *
 * based on DIS68k by Aaron Giles
 *
 */

#include "emu.h"
#include "psx.h"

extern CPU_DISASSEMBLE( r3000le );
<<<<<<< HEAD
extern unsigned dasmmips3(char *,unsigned, UINT32);

static struct
{
	UINT8 id[ 8 ];
	UINT32 text;    /* SCE only */
	UINT32 data;    /* SCE only */
	UINT32 pc0;
	UINT32 gp0;     /* SCE only */
	UINT32 t_addr;
	UINT32 t_size;
	UINT32 d_addr;  /* SCE only */
	UINT32 d_size;  /* SCE only */
	UINT32 b_addr;  /* SCE only */
	UINT32 b_size;  /* SCE only */
	UINT32 s_addr;
	UINT32 s_size;
	UINT32 SavedSP;
	UINT32 SavedFP;
	UINT32 SavedGP;
	UINT32 SavedRA;
	UINT32 SavedS0;
	UINT8 dummy[ 0x800 - 76 ];
=======

static struct
{
	uint8_t id[ 8 ];
	uint32_t text;    /* SCE only */
	uint32_t data;    /* SCE only */
	uint32_t pc0;
	uint32_t gp0;     /* SCE only */
	uint32_t t_addr;
	uint32_t t_size;
	uint32_t d_addr;  /* SCE only */
	uint32_t d_size;  /* SCE only */
	uint32_t b_addr;  /* SCE only */
	uint32_t b_size;  /* SCE only */
	uint32_t s_addr;
	uint32_t s_size;
	uint32_t SavedSP;
	uint32_t SavedFP;
	uint32_t SavedGP;
	uint32_t SavedRA;
	uint32_t SavedS0;
	uint8_t dummy[ 0x800 - 76 ];
>>>>>>> upstream/master
} m_psxexe_header;

#define FORMAT_BIN ( 0 )
#define FORMAT_PSX ( 1 )

#define CPU_PSX ( 0 )
#define CPU_R3000 ( 1 )
#define CPU_R4000 ( 2 )

<<<<<<< HEAD
static UINT8 *filebuf;
static UINT32 offset;
static UINT8 order[] = { 0, 1, 2, 3 };
=======
static uint8_t *filebuf;
static uint32_t offset;
static uint8_t order[] = { 0, 1, 2, 3 };
>>>>>>> upstream/master

static const char *const Options[]=
{
	"begin", "end", "offset", "order", "format", "cpu", 0
};

static void usage (void)
{
	fprintf( stderr,
		"Usage: DISMIPS [options] <filename>\n\n"
		"Available options are:\n"
		" -begin  - Specify begin offset in file to disassemble in bytes [0]\n"
		" -end    - Specify end offset in file to disassemble in bytes [none]\n"
		" -offset - Specify address to load program in bytes [0]\n"
		" -order  - Specify byte order [0123]\n"
		" -format - Specify file format bin|psx [bin]\n"
		" -cpu    - Specify cpu psx|r3000|r4000 [psx]\n\n"
		"All values should be entered in hexadecimal\n" );
	exit( 1 );
}

int main( int argc, char *argv[] )
{
	FILE *f;
<<<<<<< HEAD
	UINT8 i;
	UINT8 j;
	UINT8 n;
	UINT8 p;
	UINT32 begin;
	UINT32 end;
	UINT32 filelen;
	UINT32 len;
	UINT32 pc;
	char buffer[ 80 ];
	char *filename;
	UINT32 format;
	UINT32 cpu;

	filename = NULL;
=======
	uint8_t i;
	uint8_t j;
	uint8_t n;
	uint8_t p;
	uint32_t begin;
	uint32_t end;
	uint32_t filelen;
	uint32_t len;
	uint32_t pc;
	char buffer[ 80 ];
	char *filename;
	uint32_t format;
	uint32_t cpu;

	filename = nullptr;
>>>>>>> upstream/master
	begin = 0;
	end = 0xffffffff;
	format = FORMAT_BIN;
	cpu = CPU_PSX;

	n = 0;
	for( i = 1; i < argc; i++ )
	{
		if( argv[ i ][ 0 ] != '-' )
		{
			switch( n )
			{
			case 0:
				filename = argv[ i ];
				break;
			default:
				usage();
				break;
			}
			n++;
		}
		else
		{
			for( j = 0; Options[ j ]; j++ )
			{
				if( strcmp( argv[ i ] + 1, Options[ j ] ) == 0 )
				{
					break;
				}
			}
			switch( j )
			{
			case 0:
				i++;
				if( i > argc )
				{
					usage();
				}
				begin = strtoul( argv[ i ], 0, 16 );
				break;
			case 1:
				i++;
				if( i > argc )
				{
					usage();
				}
				end = strtoul( argv[ i ], 0, 16 );
				break;
			case 2:
				i++;
				if( i > argc )
				{
					usage();
				}
				offset = strtoul( argv[ i ], 0, 16 );
				break;
			case 3:
				i++;
				if( i > argc )
				{
					usage();
				}
				if( strlen( argv[ i ] ) != 4 )
				{
					usage();
				}
				for( p = 0; p < 4; p++ )
				{
					if( argv[ i ][ p ] < '0' || argv[ i ][ p ] > '3' )
					{
						usage();
					}
					order[ p ] = argv[ i ][ p ] - '0';
				}
				break;
			case 4:
				i++;
				if( i > argc )
				{
					usage();
				}
				if( core_stricmp( argv[ i ], "bin" ) == 0 )
				{
					format = FORMAT_BIN;
				}
				else if( core_stricmp( argv[ i ], "psx" ) == 0 )
				{
					format = FORMAT_PSX;
				}
				else
				{
					usage();
				}
				break;
			case 5:
				i++;
				if( i > argc )
				{
					usage();
				}
				if( core_stricmp( argv[ i ], "psx" ) == 0 )
				{
					cpu = CPU_PSX;
				}
				else if( core_stricmp( argv[ i ], "r3000" ) == 0 )
				{
					cpu = CPU_R3000;
				}
				else if( core_stricmp( argv[ i ], "r4000" ) == 0 )
				{
					cpu = CPU_R4000;
				}
				else
				{
					usage();
				}
				break;
			default:
				usage();
				break;
			}
		}
	}

	if (!filename)
	{
		usage();
		return 1;
	}
	f=fopen (filename,"rb");
	if (!f)
	{
		printf ("Unable to open %s\n",filename);
		return 2;
	}
	fseek (f,0,SEEK_END);
	filelen=ftell (f);

	if( format == FORMAT_PSX )
	{
		fseek( f, 0, SEEK_SET );
		if( fread( &m_psxexe_header, 1, sizeof( m_psxexe_header ), f ) != sizeof( m_psxexe_header ) )
		{
			fprintf( stderr, "error reading ps-x exe header\n" );
			fclose( f );
			return 3;
		}
		if( memcmp( m_psxexe_header.id, "PS-X EXE", sizeof( m_psxexe_header.id ) ) != 0 )
		{
			fprintf( stderr, "invalid ps-x exe header\n" );
			fclose( f );
			return 3;
		}
		printf( "_start = $%08x\n\n", m_psxexe_header.pc0 );
		if( offset == 0 )
		{
			offset = m_psxexe_header.t_addr;
		}
		if( begin == 0 )
		{
			begin = sizeof( m_psxexe_header );
		}
		if( end == 0xffffffff )
		{
			end = sizeof( m_psxexe_header ) + m_psxexe_header.t_size;
		}
	}

	fseek (f,begin,SEEK_SET);
	len=(filelen>end)? (end-begin+1):(filelen-begin);
<<<<<<< HEAD
	filebuf=(UINT8 *)malloc(len+16);
=======
	filebuf=(uint8_t *)malloc(len+16);
>>>>>>> upstream/master
	if (!filebuf)
	{
		printf ("Memory allocation error\n");
		fclose (f);
		return 3;
	}
	memset (filebuf,0,len+16);
	if (fread(filebuf,1,len,f)!=len)
	{
		printf ("Read error\n");
		fclose (f);
		free (filebuf);
		return 4;
	}
	fclose (f);

	pc = 0;
	while( pc < len )
	{
<<<<<<< HEAD
		UINT8 op0 = filebuf[ pc + order[ 0 ] ];
		UINT8 op1 = filebuf[ pc + order[ 1 ] ];
		UINT8 op2 = filebuf[ pc + order[ 2 ] ];
		UINT8 op3 = filebuf[ pc + order[ 3 ] ];
=======
		uint8_t op0 = filebuf[ pc + order[ 0 ] ];
		uint8_t op1 = filebuf[ pc + order[ 1 ] ];
		uint8_t op2 = filebuf[ pc + order[ 2 ] ];
		uint8_t op3 = filebuf[ pc + order[ 3 ] ];
>>>>>>> upstream/master
		filebuf[ pc + 0 ] = op0;
		filebuf[ pc + 1 ] = op1;
		filebuf[ pc + 2 ] = op2;
		filebuf[ pc + 3 ] = op3;

		pc += 4;
	}

	pc = 0;
	while( pc < len )
	{
		switch( cpu )
		{
		case CPU_PSX:
<<<<<<< HEAD
			i = DasmPSXCPU( NULL, buffer, pc + offset, filebuf + pc );
			break;
		case CPU_R3000:
			{
				legacy_cpu_device *device = NULL;
				int options = 0;
				UINT8 *opram = filebuf + pc;
				UINT8 *oprom = opram;
=======
			i = DasmPSXCPU( nullptr, buffer, pc + offset, filebuf + pc );
			break;
		case CPU_R3000:
			{
				cpu_device *device = nullptr;
				int options = 0;
				uint8_t *opram = filebuf + pc;
				uint8_t *oprom = opram;
>>>>>>> upstream/master
				i = CPU_DISASSEMBLE_CALL( r3000le );
			}
			break;
		case CPU_R4000:
			{
<<<<<<< HEAD
				UINT8 *opram = filebuf + pc;
				UINT32 op = ( opram[ 3 ] << 24 ) | ( opram[ 2 ] << 16 ) | ( opram[ 1 ] << 8 ) | ( opram[ 0 ] << 0 );
=======
				uint8_t *opram = filebuf + pc;
				uint32_t op = ( opram[ 3 ] << 24 ) | ( opram[ 2 ] << 16 ) | ( opram[ 1 ] << 8 ) | ( opram[ 0 ] << 0 );
>>>>>>> upstream/master
				i = dasmmips3( buffer, pc + offset, op );
			}
			break;
		}

		i &= DASMFLAG_LENGTHMASK;

		printf( "%08x: ", pc + offset );
		for( j = 0; j < i; j++ )
		{
			printf( "%02x ", filebuf[ pc ] );
			pc++;
		}
		while( j < 10 )
		{
			printf( "   " );
			j++;
		}
		printf( "%s\n", buffer );
	}
	free (filebuf);
	return 0;
}
<<<<<<< HEAD

void *osd_malloc_array(size_t size)
{
	return osd_malloc(size);
}

void *malloc_array_file_line(size_t size, const char *file, int line)
{
	// allocate the memory and fail if we can't
	return osd_malloc_array(size);
}

void free_file_line( void *memory, const char *file, int line )
{
	osd_free( memory );
}

void osd_free( void *memory )
{
#undef free
	free( memory );
}

void *osd_malloc( size_t size )
{
#undef malloc
	return malloc( size );
}
=======
>>>>>>> upstream/master
