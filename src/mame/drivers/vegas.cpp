// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/*************************************************************************

    Driver for Atari/Midway Vegas hardware games

    driver by Aaron Giles

    Games supported:
        * Gauntlet Legends [200MHz R5000, 8MB RAM, Vegas + Vegas SIO + Voodoo 2, 2-TMU * 4MB]
        * War: Final Assault [250MHz R5000, 8MB RAM, Vegas + Vegas SIO + Voodoo 2, 2-TMU * 4MB]
        * NBA on NBC
        * Tenth Degree/ Juko Threat
        * NBA Showtime Gold + NFL Blitz 2000 Gold

    Durango PCB (uses an RM7000 or RM5271 @ 250MHz):
        * Gauntlet Dark Legacy [Atari, 200MHz]
        * Road Burners [250MHz QED5271, 32MB RAM, Durango + DSIO + Voodoo 2, 2-TMU * 4MB]
        * San Francisco Rush 2049 [250MHz RM7000, 32MB RAM, Durango + Denver + Voodoo 3, 16MB]
        * San Francisco Rush 2049 Tournament Edition (PIC ID = 348)
        * CART Fury

    Known bugs:
        * not working yet

***************************************************************************

    Interrupt summary:

                        __________
    UART clear-to-send |          |
    -------(0x2000)--->|          |
                       |          |
    UART data ready    |          |
    -------(0x1000)--->|          |                     __________
                       |          |   VSYNC            |          |
    Main-to-sound empty|  IOASIC  |   -------(0x20)--->|          |
    -------(0x0080)--->|          |                    |          |
                       |          |   Ethernet         |          |   SIO Summary
    Sound-to-main full |          |   -------(0x10)--->|   SIO    |--------------+
    -------(0x0040)--->|          |                    |          |              |
                       |          |                    |          |              |
    Sound FIFO empty   |          |   IOASIC Summary   |          |              |
    -------(0x0008)--->|          |----------(0x04)--->|          |              |
                       |__________|                    |__________|              |
<<<<<<< HEAD
                                                                                 |
=======
                                      NSS/Hi-Link  (0x08)                        |
                                      A2D IRQ      (0x02)                        |
                                      SIO Watchdog (0x01)                        |
>>>>>>> upstream/master
 +-------------------------------------------------------------------------------+
 |
 |                      __________                      __________
 |  IDE Controller     |          |                    |          |
 |  -------(0x0800)--->|          |                    |          |
 |                     |          |----------(IRQ5)--->|          |
 |  SIO Summary        |          |                    |          |
 +---------(0x0400)--->|          |----------(IRQ4)--->|          |
                       |          |                    |          |
    Timer 2            |          |----------(IRQ3)--->|   CPU    |
    -------(0x0040)--->|   NILE   |                    |          |
                       |          |----------(IRQ2)--->|          |
    Timer 3            |          |                    |          |
    -------(0x0020)--->|          |----------(IRQ1)--->|          |
                       |          |                    |          |
    UART Transmit      |          |----------(IRQ0)--->|          |
    -------(0x0010)--->|          |                    |__________|
                       |__________|

<<<<<<< HEAD

=======
>>>>>>> upstream/master
***************************************************************************

 PCB Summary:

    Three boards per game. CPU board, sound I/O board, and a video board.

    CPU boards:
        Vegas    - R5000 @ 200-250MHz, 8MB RAM
        Vegas32  - R5000 @ 200-250MHz, 32MB RAM
        Durango  - RM7000 or RM5271 @ 250-300MHz, 8-32MB RAM

    Sound I/O boards:
        Vegas SIO  - ADSP2104 @ 16MHz, boot ROM, 4MB RAM
        Deluxe SIO - ADSP2181 @ 32MHz, no ROM, 4MB RAM
        Denver SIO - ADSP2181 @ 33MHz, no ROM, 4MB RAM

    Video boards:
        Voodoo 2
        Voodoo Banshee
        Voodoo 3


***************************************************************************

 Gauntlet Legends info:


 CPU PCB:  Vegas CPU  Midway no.5770-15563-06
 --------------------------------------------

 U16   33.3333MHz Oscillator (to U2 uPD82157N7-002)
 U9   100.0000MHz Oscillator (to U10 MPC948)

 U1   79RV5000-200      IDT 64-bit Processor     TBGA
 U2   uPD82157N7-002    NEC                      TBGA (huge)
 U3   uPD4516161ag5-A10 NEC 1Megx16 SDRAM        TSOP
 U4   uPD4516161ag5-A10 NEC 1Megx16 SDRAM        TSOP
 U5   uPD4516161ag5-A10 NEC 1Megx16 SDRAM        TSOP
 U6   uPD4516161ag5-A10 NEC 1Megx16 SDRAM        TSOP
 U13  EPM7032LC44-15T   Altera PLD               Midway no.A-22544
 U11  93LC46B           Microchip EEPROM         Midway no.A-22545
 U18  27C4001           Boot ROM
 U10  MPC948            Motorola low voltage clock distribution chip
 U21  PC1646U2          CMD EIDE Controller


 Sound I/O PCB: Vegas 7-7-7 SIO-4 PCB  Midway no.5770-15534-04
 -------------------------------------------------------------

 U1   33.3333MHz  Oscillator
 Y1   20.0000MHz  XTAL       (to U24 SMC91C94QFP)
 Y2    4.0000MHz  XTAL       (to U37 PIC micro)
 Y3   16.0000MHz  XTAL       (to U14 ADSP)

 U28  M4T28-BR12SH1    ST Timer Keeper Snap Hat RAM
 U14  ADSP2104         Analog Devices DSP
 U8   EPF6016TC144-2   Altera FLEX 6000 PLD    144 pin TQFP
 U11  5410-14589-00    Midway Custom           164 pin QFP
 U34  5410-14590-00    Midway Custom            80 pin PQFP
 U18  ADC0848CCN       NSC ADC
 U24  SMC91C94QFP      SMC ISA/PCMCIA Ethernet & Modem Controller
 U5   AD1866R          Analog Devices dual 16-bit audio DAC
 U31  IS61C256AH-15J   ISSI 32kx8 SRAM
 U32  IS61C256AH-15J   ISSI 32kx8 SRAM
 U33  IS61C256AH-15J   ISSI 32kx8 SRAM
 U25  TMS418160ADZ     TI 1048576x16 DRAM
 U26  TMS418160ADZ     TI 1048576x16 DRAM
 U37  PIC16C57C        Microchip PIC  Atari no.322 Gauntlet 27"
 U44  27C256           Vegas SIO Audio Boot ROM
 U1   AM7201-35JC      AMD opamp
 U2   AM7201-35JC      AMD opamp


 GFX Card: Quantum 3D - Obsidian2 PCI (3DFx Voodoo2)
 ---------------------------------------------------

 U1    500-0009-01      3DFX Pixel processor    256 pin PQFP
 U26   500-0010-01      3DFX Texture processor  208 pin PQFP
 U2    500-0010-01      3DFX Texture processor  208 pin PQFP
 U20   ICS5342-3        ICS DAC
 U21   XC9572           Xilinx CPLD Firmware 546-0014-02
 U53   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U54   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U55   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U56   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U37   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U38   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U39   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U40   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U45   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U46   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U47   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U48   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U49   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U50   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U51   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U52   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U57   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U58   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U59   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg
 U60   SM81C256K16CJ-25 Silicon Magic 100MHz EDO RAM, 4Meg


***************************************************************************

 Gauntlet Dark Legacy Info:


 CPU board: Durango 5770-15982-00    sticker with RM5271 on it
 --------------------------------
 1x RM5271 CPU(assuming this is correct...don't want to remove the heatsink from my good board)
 1x medium sized BGA, has heatsink
 1x Atmel ATF1500A  PLD  A-22912
 4x MT48LC1M16AT RAM
 1x 93clc46b       label A-22911   config eeprom
 1x texas instruments 8CA00YF (don't know what it is)
 1x motorolla MPC948 clock distribution chip
 100MHz crystal
 1x CMDPCI646U2 IDE controller
 1x 7segment LED display (cycles IOASIC if you try to load a game that doesnt match the PIC, spins during normal play)
 1x 232ACBN serial port controller
 other misc 74xxx parts
 Boot ROM 1.7

 Connectors:
   P1 4 pin marked "Reset/Interrupt"
   P2 20 pin marked "PCI Extend"
   P8B Standard PCI connector found on PC motherboards (although is custom mounted on the side of the PCB) Voodoo connects here
   P3 DB15 labeled "Video In" Voodoo connects here, but is not required if you connect directly to the Voodoo card.
   P4 Standard IDE connector marked "IDE HDD"
   P5 9 pin marked "Serial"
   Non-designated connector marked "EXP CONN" Standard PCI connector found on PC motherboards(custom mounted on the side of the PCB), SIO connects here



 SIO board: Vegas777 5770-15534-05
 ---------------------------------
 1x Midway 5410-14589-00 IO chip
 1x ADSP-2104  (16MHz crystal attached to clock pins)
 1x ADC0848CCN analog input chip
 1x ST M4t28-br12sh1  timekeeper
 1x Altera Flex epf6016tc144   pld
 1x Midway security PIC Gauntlet DL 27" 346xxxxxx (4MHz crystal attached)
 2x KM416C1200CJ-6  RAM
 1x SMSC LAN91C94 ethernet
 1x Midway 5410-14590-00 ???
 3x CY7C199-15VC  32Kx8 SRAM
 1x AD1866 DAC
 20MHz crystal attached to LAN chip
 other misc parts
 SIO ROM 1.0



 Voodoo card: Quantum3D Obsidian2 PCI 650-0818-03D
 -------------------------------------------------
 (SLI pin holes filled with solder, no connector, has no VGA input/passthrough connector, only VGA out)

 1x XC9572 label 546-0014-02
 20x silicon magic 100MHz   sm81c256k16cj-25   RAM (8MB for texture RAM, 2MB for framebuffer?)
 2x 3dfx 500-0010-01 texelfx
 1x 3dfx 500-0009-01 pixelfx
 1x 14.318MHz crystal
 1 x 3384q 10bit bus switch(i think)
 1x ICS GenDAC ICS5342-3
 other misc IC's


***************************************************************************

 Gauntlet Legends versus Gauntlet Dark Legacy


 CPU board: Vegas 5770-15563-06
 ------------------------------
 4x NEC D4516161A65-A10-9NF 8MB RAM  (other difference here...this PCB only has spots for these chips, the Durango has alternate positions for RAM, I assume for larger chips)
 1x 33.3333MHz crystal (in addition to the 100MHz crystal, on Durango this spot is present but unpopulated)
 1x Atmel ATF1500A  PLD A-22560 (replaces A-22912 on Durango)
 1x 93lc46b (A-22545 config EEPROM, dump is mostly FF and 00)
 Boot ROM "Gauntlet Update Boot v1.5 A-5343-30022-7"



 SIO board: Vegas777 5770-15534-05 (same as Legacy)
 --------------------------------------------------
 Security PIC "Gauntlet 27" 322xxxxxx"
 Sound ROM "Gauntlet 3D U44 Sound 1.0"
 2x TMS418160ADZ RAM instead of 2x KM416C1200CJ-6 on Legacy
 20MHz crystal attached to LAN chip
 1x Valor  SF1012 ethernet physical interface(also on other board)

 Connectors:
   P1 5 pin marked "Snd Line In"
   P5 5 pin marked "Snd Line Out"
   unmarked 4 pin PC style power connector(for hard drive)
   standard JAMMA connection
   P7 14 pin marked "PLYR4"
   P14 14 pin marked "PLYR3"
   P23 10 pin marked "Coin DR"
   P10 unmarked 10 pin connector (no idea)
   P21 99 pin unmarked -right on top of PCI edge connection to CPU board
   P15 20 pin marked "Aux Latched Out"
   P8 14 pin unmarked
   P2 11 pin marked "Gun 2 I/O"
   P4 11 pin marked "Gun 1 I/O"
   P 18 standard ethernet connector


**************************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "cpu/adsp2100/adsp2100.h"
#include "cpu/mips/mips3.h"
#include "audio/dcs.h"
#include "machine/timekpr.h"
#include "machine/idectrl.h"
#include "machine/midwayic.h"
#include "machine/smc91c9x.h"
#include "video/voodoo.h"

=======
#include "audio/dcs.h"

#include "cpu/adsp2100/adsp2100.h"
#include "cpu/mips/mips3.h"
#include "machine/idectrl.h"
#include "machine/midwayic.h"
#include "machine/smc91c9x.h"
#include "machine/timekpr.h"
#include "machine/pci.h"
#include "machine/vrc5074.h"
#include "machine/pci-ide.h"
#include "video/voodoo_pci.h"
#include "screen.h"
#include "machine/ins8250.h"
#include "bus/rs232/rs232.h"
#include "machine/terminal.h"

#include "sf2049.lh"
>>>>>>> upstream/master

/*************************************
 *
 *  Debugging constants
 *
 *************************************/

<<<<<<< HEAD
#define LOG_NILE            (0)
#define LOG_NILE_IRQS       (0)
#define LOG_PCI             (0)
#define LOG_TIMERS          (0)
#define LOG_TIMEKEEPER      (0)
#define LOG_SIO             (0)
#define LOG_DYNAMIC         (0)
#define PRINTF_SERIAL       (1)


=======
#define LOG_TIMEKEEPER      (0)
#define LOG_SIO             (0)
>>>>>>> upstream/master

/*************************************
 *
 *  Core constants
 *
 *************************************/

<<<<<<< HEAD
#define SYSTEM_CLOCK        100000000
#define TIMER_PERIOD        attotime::from_hz(SYSTEM_CLOCK)

#define MAX_DYNAMIC_ADDRESSES   32

#define NOP_HANDLER         read32_delegate()



/*************************************
 *
 *  NILE constants
 *
 *************************************/

/* NILE 4 registers 0x000-0x0ff */
#define NREG_SDRAM0         (0x000/4)
#define NREG_SDRAM1         (0x008/4)
#define NREG_DCS2           (0x010/4)   /* SIO misc */
#define NREG_DCS3           (0x018/4)   /* ADC */
#define NREG_DCS4           (0x020/4)   /* CMOS */
#define NREG_DCS5           (0x028/4)   /* SIO */
#define NREG_DCS6           (0x030/4)   /* IOASIC */
#define NREG_DCS7           (0x038/4)   /* ethernet */
#define NREG_DCS8           (0x040/4)
#define NREG_PCIW0          (0x060/4)
#define NREG_PCIW1          (0x068/4)
#define NREG_INTCS          (0x070/4)
#define NREG_BOOTCS         (0x078/4)
#define NREG_CPUSTAT        (0x080/4)
#define NREG_INTCTRL        (0x088/4)
#define NREG_INTSTAT0       (0x090/4)
#define NREG_INTSTAT1       (0x098/4)
#define NREG_INTCLR         (0x0A0/4)
#define NREG_INTPPES        (0x0A8/4)
#define NREG_PCIERR         (0x0B8/4)
#define NREG_MEMCTRL        (0x0C0/4)
#define NREG_ACSTIME        (0x0C8/4)
#define NREG_CHKERR         (0x0D0/4)
#define NREG_PCICTRL        (0x0E0/4)
#define NREG_PCIARB         (0x0E8/4)
#define NREG_PCIINIT0       (0x0F0/4)
#define NREG_PCIINIT1       (0x0F8/4)

/* NILE 4 registers 0x100-0x1ff */
#define NREG_LCNFG          (0x100/4)
#define NREG_LCST2          (0x110/4)
#define NREG_LCST3          (0x118/4)
#define NREG_LCST4          (0x120/4)
#define NREG_LCST5          (0x128/4)
#define NREG_LCST6          (0x130/4)
#define NREG_LCST7          (0x138/4)
#define NREG_LCST8          (0x140/4)
#define NREG_DCSFN          (0x150/4)
#define NREG_DCSIO          (0x158/4)
#define NREG_BCST           (0x178/4)
#define NREG_DMACTRL0       (0x180/4)
#define NREG_DMASRCA0       (0x188/4)
#define NREG_DMADESA0       (0x190/4)
#define NREG_DMACTRL1       (0x198/4)
#define NREG_DMASRCA1       (0x1A0/4)
#define NREG_DMADESA1       (0x1A8/4)
#define NREG_T0CTRL         (0x1C0/4)
#define NREG_T0CNTR         (0x1C8/4)
#define NREG_T1CTRL         (0x1D0/4)
#define NREG_T1CNTR         (0x1D8/4)
#define NREG_T2CTRL         (0x1E0/4)
#define NREG_T2CNTR         (0x1E8/4)
#define NREG_T3CTRL         (0x1F0/4)
#define NREG_T3CNTR         (0x1F8/4)

/* NILE 4 registers 0x200-0x2ff */
#define NREG_VID            (0x200/4)
#define NREG_DID            (0x202/4)
#define NREG_PCICMD         (0x204/4)
#define NREG_PCISTS         (0x206/4)
#define NREG_REVID          (0x208/4)
#define NREG_CLASS          (0x209/4)
#define NREG_CLSIZ          (0x20C/4)
#define NREG_MLTIM          (0x20D/4)
#define NREG_HTYPE          (0x20E/4)
#define NREG_BIST           (0x20F/4)
#define NREG_BARC           (0x210/4)
#define NREG_BAR0           (0x218/4)
#define NREG_BAR1           (0x220/4)
#define NREG_CIS            (0x228/4)
#define NREG_SSVID          (0x22C/4)
#define NREG_SSID           (0x22E/4)
#define NREG_ROM            (0x230/4)
#define NREG_INTLIN         (0x23C/4)
#define NREG_INTPIN         (0x23D/4)
#define NREG_MINGNT         (0x23E/4)
#define NREG_MAXLAT         (0x23F/4)
#define NREG_BAR2           (0x240/4)
#define NREG_BAR3           (0x248/4)
#define NREG_BAR4           (0x250/4)
#define NREG_BAR5           (0x258/4)
#define NREG_BAR6           (0x260/4)
#define NREG_BAR7           (0x268/4)
#define NREG_BAR8           (0x270/4)
#define NREG_BARB           (0x278/4)

/* NILE 4 registers 0x300-0x3ff */
#define NREG_UARTRBR        (0x300/4)
#define NREG_UARTTHR        (0x300/4)
#define NREG_UARTIER        (0x308/4)
#define NREG_UARTDLL        (0x300/4)
#define NREG_UARTDLM        (0x308/4)
#define NREG_UARTIIR        (0x310/4)
#define NREG_UARTFCR        (0x310/4)
#define NREG_UARTLCR        (0x318/4)
#define NREG_UARTMCR        (0x320/4)
#define NREG_UARTLSR        (0x328/4)
#define NREG_UARTMSR        (0x330/4)
#define NREG_UARTSCR        (0x338/4)

/* NILE 4 interrupts */
#define NINT_CPCE           (0)
#define NINT_CNTD           (1)
#define NINT_MCE            (2)
#define NINT_DMA            (3)
#define NINT_UART           (4)
#define NINT_WDOG           (5)
#define NINT_GPT            (6)
#define NINT_LBRTD          (7)
#define NINT_INTA           (8)
#define NINT_INTB           (9)
#define NINT_INTC           (10)
#define NINT_INTD           (11)
#define NINT_INTE           (12)
#define NINT_RESV           (13)
#define NINT_PCIS           (14)
#define NINT_PCIE           (15)


struct dynamic_address
{
	offs_t          start;
	offs_t          end;
	read32_delegate   read;
	write32_delegate write;
};
=======
#define PCI_ID_NILE     ":pci:00.0"
#define PCI_ID_VIDEO    ":pci:03.0"
#define PCI_ID_IDE      ":pci:05.0"
>>>>>>> upstream/master

class vegas_state : public driver_device
{
public:
	vegas_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
<<<<<<< HEAD
		m_timekeeper(*this, "timekeeper") ,
		m_ide(*this, "ide"),
		m_ethernet(*this, "ethernet"),
		m_rambase(*this, "rambase"),
		m_nile_regs(*this, "nile_regs"),
		m_rombase(*this, "rombase"),
		m_dcs(*this, "dcs"),
		m_ioasic(*this, "ioasic"),
		m_io_analog(*this, "AN")
	{ }

	required_device<mips3_device> m_maincpu;
	required_device<m48t37_device> m_timekeeper;
	required_device<bus_master_ide_controller_device> m_ide;
	required_device<smc91c94_device> m_ethernet;
	required_shared_ptr<UINT32> m_rambase;
	required_shared_ptr<UINT32> m_nile_regs;
	required_shared_ptr<UINT32> m_rombase;
	required_device<dcs_audio_device> m_dcs;
	required_device<midway_ioasic_device> m_ioasic;
	optional_ioport_array<8> m_io_analog;

	UINT16 m_nile_irq_state;
	UINT16 m_ide_irq_state;
	UINT32 m_pci_bridge_regs[0x40];
	UINT32 m_pci_ide_regs[0x40];
	UINT32 m_pci_3dfx_regs[0x40];
	emu_timer *m_timer[4];
	UINT8 m_vblank_state;
	UINT8 m_sio_data[4];
	UINT8 m_sio_irq_clear;
	UINT8 m_sio_irq_enable;
	UINT8 m_sio_irq_state;
	UINT8 m_sio_led_state;
	UINT8 m_pending_analog_read;
	UINT8 m_cmos_unlocked;
	device_t *m_voodoo;
	UINT8 m_dcs_idma_cs;
	int m_count;
	int m_dynamic_count;
	dynamic_address m_dynamic[MAX_DYNAMIC_ADDRESSES];
	DECLARE_WRITE_LINE_MEMBER(ide_interrupt);
=======
		m_nile(*this, PCI_ID_NILE),
		m_timekeeper(*this, "timekeeper") ,
		m_ethernet(*this, "ethernet"),
		m_dcs(*this, "dcs"),
		m_ioasic(*this, "ioasic"),
		m_uart0(*this, "uart0"),
		m_uart1(*this, "uart1"),
		m_uart2(*this, "uart2"),
		m_io_analog(*this, "AN.%u", 0),
		m_a2d_shift(0)
	{ }
	static constexpr unsigned SYSTEM_CLOCK = 100000000;

	required_device<mips3_device> m_maincpu;
	required_device<vrc5074_device> m_nile;
	required_device<m48t37_device> m_timekeeper;
	required_device<smc91c94_device> m_ethernet;
	required_device<dcs_audio_device> m_dcs;
	required_device<midway_ioasic_device> m_ioasic;
	optional_device<generic_terminal_device> m_uart0;
	optional_device<ns16550_device> m_uart1;
	optional_device<ns16550_device> m_uart2;
	optional_ioport_array<8> m_io_analog;
	int m_a2d_shift;
	uint8_t m_vblank_state;
	uint8_t m_cpuio_data[4];
	uint8_t m_sio_reset_ctrl;
	uint8_t m_sio_irq_clear;
	uint8_t m_sio_irq_enable;
	uint8_t m_sio_irq_state;
	uint8_t m_sio_led_state;
	uint8_t m_pending_analog_read;
	uint8_t m_cmos_unlocked;
	uint8_t m_dcs_idma_cs;
	uint32_t m_i40_data;
	uint32_t m_keypad_select;
	uint32_t m_gear;

	DECLARE_WRITE_LINE_MEMBER(uart1_irq_cb);
	DECLARE_WRITE_LINE_MEMBER(uart2_irq_cb);
>>>>>>> upstream/master
	DECLARE_WRITE_LINE_MEMBER(vblank_assert);
	DECLARE_DRIVER_INIT(gauntleg);
	DECLARE_DRIVER_INIT(cartfury);
	DECLARE_DRIVER_INIT(tenthdeg);
	DECLARE_DRIVER_INIT(nbashowt);
	DECLARE_DRIVER_INIT(warfa);
	DECLARE_DRIVER_INIT(roadburn);
	DECLARE_DRIVER_INIT(sf2049te);
	DECLARE_DRIVER_INIT(gauntdl);
	DECLARE_DRIVER_INIT(nbanfl);
	DECLARE_DRIVER_INIT(sf2049);
	DECLARE_DRIVER_INIT(sf2049se);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	UINT32 screen_update_vegas(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	TIMER_CALLBACK_MEMBER(nile_timer_callback);
	void remap_dynamic_addresses();
	void update_nile_irqs();
	void update_sio_irqs();
	inline void _add_dynamic_address(offs_t start, offs_t end, read32_delegate read, write32_delegate write);

	DECLARE_WRITE32_MEMBER( cmos_unlock_w );
	DECLARE_WRITE32_MEMBER(timekeeper_w);
	DECLARE_READ32_MEMBER(timekeeper_r);
	DECLARE_READ32_MEMBER( pci_bridge_r );
	DECLARE_WRITE32_MEMBER( pci_bridge_w );
	DECLARE_READ32_MEMBER( pci_ide_r );
	DECLARE_WRITE32_MEMBER( pci_ide_w );
	DECLARE_READ32_MEMBER( pci_3dfx_r );
	DECLARE_WRITE32_MEMBER( pci_3dfx_w );
	DECLARE_READ32_MEMBER( nile_r );
	DECLARE_WRITE32_MEMBER( nile_w );
	DECLARE_READ32_MEMBER( sio_irq_clear_r );
	DECLARE_WRITE32_MEMBER( sio_irq_clear_w );
	DECLARE_READ32_MEMBER( sio_irq_enable_r );
	DECLARE_WRITE32_MEMBER( sio_irq_enable_w );
	DECLARE_READ32_MEMBER( sio_irq_cause_r );
	DECLARE_READ32_MEMBER( sio_irq_status_r );
	DECLARE_WRITE32_MEMBER( sio_led_w );
	DECLARE_READ32_MEMBER( sio_led_r );
	DECLARE_WRITE32_MEMBER( sio_w );
	DECLARE_READ32_MEMBER( sio_r );
	DECLARE_READ32_MEMBER( analog_port_r );
	DECLARE_WRITE32_MEMBER( analog_port_w );
	DECLARE_WRITE32_MEMBER( vegas_watchdog_w );
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;

	void update_sio_irqs();

	DECLARE_WRITE_LINE_MEMBER(watchdog_reset);
	DECLARE_WRITE_LINE_MEMBER(watchdog_irq);
	DECLARE_WRITE32_MEMBER(timekeeper_w);
	DECLARE_READ32_MEMBER(timekeeper_r);
	void reset_sio(void);
	DECLARE_READ8_MEMBER(sio_r);
	DECLARE_WRITE8_MEMBER(sio_w);
	DECLARE_WRITE8_MEMBER( cpu_io_w );
	DECLARE_READ8_MEMBER( cpu_io_r );
	DECLARE_READ32_MEMBER( analog_port_r );
	DECLARE_WRITE32_MEMBER( analog_port_w );
>>>>>>> upstream/master
	DECLARE_WRITE32_MEMBER( asic_fifo_w );
	DECLARE_READ32_MEMBER( ide_main_r );
	DECLARE_WRITE32_MEMBER( ide_main_w );
	DECLARE_READ32_MEMBER( ide_alt_r );
	DECLARE_WRITE32_MEMBER( ide_alt_w );
	DECLARE_READ32_MEMBER( ide_bus_master32_r );
	DECLARE_WRITE32_MEMBER( ide_bus_master32_w );
	DECLARE_READ32_MEMBER( ethernet_r );
	DECLARE_WRITE32_MEMBER( ethernet_w );
	DECLARE_WRITE32_MEMBER( dcs3_fifo_full_w );
	DECLARE_WRITE_LINE_MEMBER(ethernet_interrupt);
	DECLARE_WRITE_LINE_MEMBER(ioasic_irq);
<<<<<<< HEAD
};


/*************************************
 *
 *  Video start and update
 *
 *************************************/

UINT32 vegas_state::screen_update_vegas(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect)
{
	return voodoo_update(m_voodoo, bitmap, cliprect) ? 0 : UPDATE_HAS_NOT_CHANGED;
}

=======
	DECLARE_READ32_MEMBER(unknown_r);
	DECLARE_READ8_MEMBER(parallel_r);
	DECLARE_WRITE8_MEMBER(parallel_w);
	DECLARE_WRITE32_MEMBER(i40_w);
	DECLARE_CUSTOM_INPUT_MEMBER(i40_r);
	DECLARE_CUSTOM_INPUT_MEMBER(keypad_r);
	DECLARE_CUSTOM_INPUT_MEMBER(gearshift_r);
	DECLARE_WRITE32_MEMBER(wheel_board_w);

	std::string sioIRQString(uint8_t data);

};
>>>>>>> upstream/master

/*************************************
 *
 *  Machine init
 *
 *************************************/

void vegas_state::machine_start()
{
<<<<<<< HEAD
	m_voodoo = machine().device("voodoo");

	/* allocate timers for the NILE */
	m_timer[0] = machine().scheduler().timer_alloc(FUNC_NULL);
	m_timer[1] = machine().scheduler().timer_alloc(FUNC_NULL);
	m_timer[2] = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(vegas_state::nile_timer_callback),this));
	m_timer[3] = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(vegas_state::nile_timer_callback),this));

	/* identify our sound board */
	if (machine().device("dsio") != NULL)
		m_dcs_idma_cs = 6;
	else if (machine().device("denver") != NULL)
		m_dcs_idma_cs = 7;
	else
		m_dcs_idma_cs = 0;
=======
	/* identify our sound board */
	if (machine().device("dcs:dsio") != nullptr) {
		m_dcs_idma_cs = 6;
		if (LOG_SIO)
			logerror("Found dsio\n");
	}
	else if (machine().device("dcs:denver") != nullptr) {
		m_dcs_idma_cs = 7;
		if (LOG_SIO)
			logerror("Found denver\n");
	}
	else {
		m_dcs_idma_cs = 0;
		if (LOG_SIO)
			logerror("Did not find dcs2 sound board\n");
	}
>>>>>>> upstream/master

	/* set the fastest DRC options, but strict verification */
	m_maincpu->mips3drc_set_options(MIPS3DRC_FASTEST_OPTIONS + MIPS3DRC_STRICT_VERIFY + MIPS3DRC_FLUSH_PC);

<<<<<<< HEAD
	/* configure fast RAM regions */
	m_maincpu->add_fastram(0x00000000, m_rambase.bytes() - 1, FALSE, m_rambase);
	m_maincpu->add_fastram(0x1fc00000, 0x1fc7ffff, TRUE, m_rombase);

	/* register for save states */
	save_item(NAME(m_nile_irq_state));
	save_item(NAME(m_ide_irq_state));
	save_item(NAME(m_pci_bridge_regs));
	save_item(NAME(m_pci_ide_regs));
	save_item(NAME(m_pci_3dfx_regs));
	save_item(NAME(m_vblank_state));
	save_item(NAME(m_sio_data));
=======
	/* register for save states */
	save_item(NAME(m_vblank_state));
	save_item(NAME(m_cpuio_data));
	save_item(NAME(m_sio_reset_ctrl));
>>>>>>> upstream/master
	save_item(NAME(m_sio_irq_clear));
	save_item(NAME(m_sio_irq_enable));
	save_item(NAME(m_sio_irq_state));
	save_item(NAME(m_sio_led_state));
	save_item(NAME(m_pending_analog_read));
	save_item(NAME(m_cmos_unlocked));
<<<<<<< HEAD
	machine().save().register_postload(save_prepost_delegate(FUNC(vegas_state::remap_dynamic_addresses), this));
=======
	save_item(NAME(m_i40_data));
	save_item(NAME(m_keypad_select));
	save_item(NAME(m_gear));
>>>>>>> upstream/master
}


void vegas_state::machine_reset()
{
<<<<<<< HEAD
	/* reset dynamic addressing */
	memset(m_nile_regs, 0, 0x1000);
	memset(m_pci_ide_regs, 0, sizeof(m_pci_ide_regs));
	memset(m_pci_3dfx_regs, 0, sizeof(m_pci_3dfx_regs));

	/* reset the DCS system if we have one */
	if (machine().device("dcs") != NULL)
=======

	/* reset the DCS system if we have one */
	if (machine().device("dcs") != nullptr)
>>>>>>> upstream/master
	{
		m_dcs->reset_w(1);
		m_dcs->reset_w(0);
	}
<<<<<<< HEAD

	/* initialize IRQ states */
	m_ide_irq_state = 0;
	m_nile_irq_state = 0;
	m_sio_irq_state = 0;
}

=======
	// Clear CPU IO registers
	memset(m_cpuio_data, 0, ARRAY_LENGTH(m_cpuio_data));
	// Clear SIO registers
	reset_sio();
	m_i40_data = 0;
	m_keypad_select = 0;
	m_gear = 1;
}

/*************************************
*  Watchdog interrupts
*************************************/
#define WD_IRQ 0x1
WRITE_LINE_MEMBER(vegas_state::watchdog_irq)
{
	if (state && !(m_sio_irq_state & WD_IRQ)) {
		logerror("%s: vegas_state::watchdog_irq state = %i\n", machine().describe_context(), state);
		m_sio_irq_state |= WD_IRQ;
		update_sio_irqs();
	}
	else if (!state && (m_sio_irq_state & WD_IRQ)) {
		logerror("%s: vegas_state::watchdog_irq state = %i\n", machine().describe_context(), state);
		m_sio_irq_state &= ~WD_IRQ;
		update_sio_irqs();
	}
}

/*************************************
*  Watchdog Reset
*************************************/
WRITE_LINE_MEMBER(vegas_state::watchdog_reset)
{
	if (state) {
		printf("vegas_state::watchdog_reset!!!\n");
		logerror("vegas_state::watchdog_reset!!!\n");
		machine().schedule_soft_reset();
	}
}
>>>>>>> upstream/master

/*************************************
 *
 *  Timekeeper access
 *
 *************************************/

<<<<<<< HEAD
WRITE32_MEMBER( vegas_state::cmos_unlock_w )
{
	m_cmos_unlocked = 1;
}


=======
>>>>>>> upstream/master
WRITE32_MEMBER( vegas_state::timekeeper_w )
{
	if (m_cmos_unlocked)
	{
<<<<<<< HEAD
		if ((mem_mask & 0x000000ff) != 0)
			m_timekeeper->write(space, offset * 4 + 0, data >> 0, 0xff);
		if ((mem_mask & 0x0000ff00) != 0)
			m_timekeeper->write(space, offset * 4 + 1, data >> 8, 0xff);
		if ((mem_mask & 0x00ff0000) != 0)
			m_timekeeper->write(space, offset * 4 + 2, data >> 16, 0xff);
		if ((mem_mask & 0xff000000) != 0)
=======
		if (ACCESSING_BITS_0_7)
			m_timekeeper->write(space, offset * 4 + 0, data >> 0, 0xff);
		if (ACCESSING_BITS_8_15)
			m_timekeeper->write(space, offset * 4 + 1, data >> 8, 0xff);
		if (ACCESSING_BITS_16_23)
			m_timekeeper->write(space, offset * 4 + 2, data >> 16, 0xff);
		if (ACCESSING_BITS_24_31)
>>>>>>> upstream/master
			m_timekeeper->write(space, offset * 4 + 3, data >> 24, 0xff);
		if (offset*4 >= 0x7ff0)
			if (LOG_TIMEKEEPER) logerror("timekeeper_w(%04X & %08X) = %08X\n", offset*4, mem_mask, data);
		m_cmos_unlocked = 0;
	}
	else
		logerror("%08X:timekeeper_w(%04X,%08X & %08X) without CMOS unlocked\n", safe_pc(), offset, data, mem_mask);
}


READ32_MEMBER( vegas_state::timekeeper_r )
{
<<<<<<< HEAD
	UINT32 result = 0xffffffff;
	if ((mem_mask & 0x000000ff) != 0)
		result = (result & ~0x000000ff) | (m_timekeeper->read(space, offset * 4 + 0, 0xff) << 0);
	if ((mem_mask & 0x0000ff00) != 0)
		result = (result & ~0x0000ff00) | (m_timekeeper->read(space, offset * 4 + 1, 0xff) << 8);
	if ((mem_mask & 0x00ff0000) != 0)
		result = (result & ~0x00ff0000) | (m_timekeeper->read(space, offset * 4 + 2, 0xff) << 16);
	if ((mem_mask & 0xff000000) != 0)
=======
	uint32_t result = 0xffffffff;
	if (ACCESSING_BITS_0_7)
		result = (result & ~0x000000ff) | (m_timekeeper->read(space, offset * 4 + 0, 0xff) << 0);
	if (ACCESSING_BITS_8_15)
		result = (result & ~0x0000ff00) | (m_timekeeper->read(space, offset * 4 + 1, 0xff) << 8);
	if (ACCESSING_BITS_16_23)
		result = (result & ~0x00ff0000) | (m_timekeeper->read(space, offset * 4 + 2, 0xff) << 16);
	if (ACCESSING_BITS_24_31)
>>>>>>> upstream/master
		result = (result & ~0xff000000) | (m_timekeeper->read(space, offset * 4 + 3, 0xff) << 24);
	if (offset*4 >= 0x7ff0)
		if (LOG_TIMEKEEPER) logerror("timekeeper_r(%04X & %08X) = %08X\n", offset*4, mem_mask, result);
	return result;
}



<<<<<<< HEAD
/*************************************
 *
 *  PCI bridge accesses
 *
 *************************************/

READ32_MEMBER( vegas_state::pci_bridge_r )
{
	UINT32 result = m_pci_bridge_regs[offset];

	switch (offset)
	{
		case 0x00:      /* ID register: 0x005a = VRC 5074, 0x1033 = NEC */
			result = 0x005a1033;
			break;

		case 0x02:      /* revision ID register */
			result = 0x00000004;
			break;
	}

	if (LOG_PCI)
		logerror("%06X:PCI bridge read: reg %d = %08X\n", safe_pc(), offset, result);
	return result;
}


WRITE32_MEMBER( vegas_state::pci_bridge_w )
{
	m_pci_bridge_regs[offset] = data;
	if (LOG_PCI)
		logerror("%06X:PCI bridge write: reg %d = %08X\n", safe_pc(), offset, data);
}



/*************************************
 *
 *  PCI IDE accesses
 *
 *************************************/

READ32_MEMBER( vegas_state::pci_ide_r )
{
	UINT32 result = m_pci_ide_regs[offset];

	switch (offset)
	{
		case 0x00:      /* ID register: 0x0646 = 646 EIDE controller, 0x1095 = CMD */
			result = 0x06461095;
			break;

		case 0x14:      /* interrupt pending */
			result &= 0xffffff00;
			if (m_ide_irq_state)
				result |= 4;
			break;
	}

	if (LOG_PCI)
		logerror("%06X:PCI IDE read: reg %d = %08X\n", safe_pc(), offset, result);
	return result;
}


WRITE32_MEMBER( vegas_state::pci_ide_w )
{
	m_pci_ide_regs[offset] = data;

	switch (offset)
	{
		case 0x04:      /* address register */
			m_pci_ide_regs[offset] &= 0xfffffff0;
			remap_dynamic_addresses();
			break;

		case 0x05:      /* address register */
			m_pci_ide_regs[offset] &= 0xfffffffc;
			remap_dynamic_addresses();
			break;

		case 0x08:      /* address register */
			m_pci_ide_regs[offset] &= 0xfffffff0;
			remap_dynamic_addresses();
			break;

		case 0x14:      /* interrupt pending */
			if (data & 4)
				ide_interrupt(0);
			break;
	}
	if (LOG_PCI)
		logerror("%06X:PCI IDE write: reg %d = %08X\n", safe_pc(), offset, data);
}



/*************************************
 *
 *  PCI 3dfx accesses
 *
 *************************************/

READ32_MEMBER( vegas_state::pci_3dfx_r )
{
	int voodoo_type = voodoo_get_type(m_voodoo);
	UINT32 result = m_pci_3dfx_regs[offset];

	switch (offset)
	{
		case 0x00:      /* ID register: 0x0002 = SST-2, 0x121a = 3dfx */
			if (voodoo_type == TYPE_VOODOO_2)
				result = 0x0002121a;
			else
				result = 0x0003121a;
			break;

		case 0x02:      /* revision ID register */
			result = 0x00000002;
			break;

		case 0x10:      /* fab ID register?? */
			result = 0x00044000;
			break;

		case 0x15:      /* ???? -- gauntleg wants 0s in the bits below */
			result &= 0xf000ffff;
			break;
	}

	if (LOG_PCI)
		logerror("%06X:PCI 3dfx read: reg %d = %08X\n", safe_pc(), offset, result);
	return result;
}


WRITE32_MEMBER( vegas_state::pci_3dfx_w )
{
	int voodoo_type = voodoo_get_type(m_voodoo);

	m_pci_3dfx_regs[offset] = data;

	switch (offset)
	{
		case 0x04:      /* address register */
			if (voodoo_type == TYPE_VOODOO_2)
				m_pci_3dfx_regs[offset] &= 0xff000000;
			else
				m_pci_3dfx_regs[offset] &= 0xfe000000;
			remap_dynamic_addresses();
			break;

		case 0x05:      /* address register */
			if (voodoo_type >= TYPE_VOODOO_BANSHEE)
			{
				m_pci_3dfx_regs[offset] &= 0xfe000000;
				remap_dynamic_addresses();
			}
			break;

		case 0x06:      /* I/O register */
			if (voodoo_type >= TYPE_VOODOO_BANSHEE)
			{
				m_pci_3dfx_regs[offset] &= 0xffffff00;
				remap_dynamic_addresses();
			}
			break;

		case 0x0c:      /* romBaseAddr register */
			if (voodoo_type >= TYPE_VOODOO_BANSHEE)
			{
				m_pci_3dfx_regs[offset] &= 0xffff0000;
				remap_dynamic_addresses();
			}
			break;

		case 0x10:      /* initEnable register */
			voodoo_set_init_enable(m_voodoo, data);
			break;

	}
	if (LOG_PCI)
		logerror("%06X:PCI 3dfx write: reg %d = %08X\n", safe_pc(), offset, data);
}



/*************************************
 *
 *  nile timers & interrupts
 *
 *************************************/

void vegas_state::update_nile_irqs()
{
	UINT32 intctll = m_nile_regs[NREG_INTCTRL+0];
	UINT32 intctlh = m_nile_regs[NREG_INTCTRL+1];
	UINT8 irq[6];
	int i;

	/* check for UART transmit IRQ enable and synthsize one */
	if (m_nile_regs[NREG_UARTIER] & 2)
		m_nile_irq_state |= 0x0010;
	else
		m_nile_irq_state &= ~0x0010;

	irq[0] = irq[1] = irq[2] = irq[3] = irq[4] = irq[5] = 0;
	m_nile_regs[NREG_INTSTAT0+0] = 0;
	m_nile_regs[NREG_INTSTAT0+1] = 0;
	m_nile_regs[NREG_INTSTAT1+0] = 0;
	m_nile_regs[NREG_INTSTAT1+1] = 0;

	/* handle the lower interrupts */
	for (i = 0; i < 8; i++)
		if (m_nile_irq_state & (1 << i))
			if ((intctll >> (4*i+3)) & 1)
			{
				int vector = (intctll >> (4*i)) & 7;
				if (vector < 6)
				{
					irq[vector] = 1;
					m_nile_regs[NREG_INTSTAT0 + vector/2] |= 1 << (i + 16*(vector&1));
				}
			}

	/* handle the upper interrupts */
	for (i = 0; i < 8; i++)
		if (m_nile_irq_state & (1 << (i+8)))
			if ((intctlh >> (4*i+3)) & 1)
			{
				int vector = (intctlh >> (4*i)) & 7;
				if (vector < 6)
				{
					irq[vector] = 1;
					m_nile_regs[NREG_INTSTAT0 + vector/2] |= 1 << (i + 8 + 16*(vector&1));
				}
			}

	/* push out the state */
	if (LOG_NILE_IRQS) logerror("NILE IRQs:");
	for (i = 0; i < 6; i++)
	{
		if (irq[i])
		{
			if (LOG_NILE_IRQS) logerror(" 1");
			m_maincpu->set_input_line(MIPS3_IRQ0 + i, ASSERT_LINE);
		}
		else
		{
			if (LOG_NILE_IRQS) logerror(" 0");
			m_maincpu->set_input_line(MIPS3_IRQ0 + i, CLEAR_LINE);
		}
	}
	if (LOG_NILE_IRQS) logerror("\n");
}


TIMER_CALLBACK_MEMBER(vegas_state::nile_timer_callback)
{
	int which = param;
	UINT32 *regs = &m_nile_regs[NREG_T0CTRL + which * 4];
	if (LOG_TIMERS) logerror("timer %d fired\n", which);

	/* adjust the timer to fire again */
	{
		UINT32 scale = regs[0];
		if (regs[1] & 2)
			logerror("Unexpected value: timer %d is prescaled\n", which);
		if (scale != 0)
			m_timer[which]->adjust(TIMER_PERIOD * scale, which);
	}

	/* trigger the interrupt */
	if (which == 2)
		m_nile_irq_state |= 1 << 6;
	if (which == 3)
		m_nile_irq_state |= 1 << 5;

	update_nile_irqs();
}



/*************************************
 *
 *  Nile system controller
 *
 *************************************/

READ32_MEMBER( vegas_state::nile_r )
{
	UINT32 result = m_nile_regs[offset];
	int logit = 1, which;

	switch (offset)
	{
		case NREG_CPUSTAT+0:    /* CPU status */
		case NREG_CPUSTAT+1:    /* CPU status */
			if (LOG_NILE) logerror("%08X:NILE READ: CPU status(%03X) = %08X\n", safe_pc(), offset*4, result);
			logit = 0;
			break;

		case NREG_INTCTRL+0:    /* Interrupt control */
		case NREG_INTCTRL+1:    /* Interrupt control */
			if (LOG_NILE) logerror("%08X:NILE READ: interrupt control(%03X) = %08X\n", safe_pc(), offset*4, result);
			logit = 0;
			break;

		case NREG_INTSTAT0+0:   /* Interrupt status 0 */
		case NREG_INTSTAT0+1:   /* Interrupt status 0 */
			if (LOG_NILE) logerror("%08X:NILE READ: interrupt status 0(%03X) = %08X\n", safe_pc(), offset*4, result);
			logit = 0;
			break;

		case NREG_INTSTAT1+0:   /* Interrupt status 1 */
		case NREG_INTSTAT1+1:   /* Interrupt status 1 */
			if (LOG_NILE) logerror("%08X:NILE READ: interrupt status 1/enable(%03X) = %08X\n", safe_pc(), offset*4, result);
			logit = 0;
			break;

		case NREG_INTCLR+0:     /* Interrupt clear */
		case NREG_INTCLR+1:     /* Interrupt clear */
			if (LOG_NILE) logerror("%08X:NILE READ: interrupt clear(%03X) = %08X\n", safe_pc(), offset*4, result);
			logit = 0;
			break;

		case NREG_INTPPES+0:    /* PCI Interrupt control */
		case NREG_INTPPES+1:    /* PCI Interrupt control */
			if (LOG_NILE) logerror("%08X:NILE READ: PCI interrupt control(%03X) = %08X\n", safe_pc(), offset*4, result);
			logit = 0;
			break;

		case NREG_PCIERR+0:     /* PCI error */
		case NREG_PCIERR+1:     /* PCI error */
		case NREG_PCICTRL+0:    /* PCI control */
		case NREG_PCICTRL+1:    /* PCI arbiter */
		case NREG_PCIINIT0+0:   /* PCI master */
		case NREG_PCIINIT0+1:   /* PCI master */
		case NREG_PCIINIT1+0:   /* PCI master */
		case NREG_PCIINIT1+1:   /* PCI master */
			logit = 0;
			break;

		case NREG_T0CNTR:       /* SDRAM timer control (counter) */
		case NREG_T1CNTR:       /* bus timeout timer control (counter) */
		case NREG_T2CNTR:       /* general purpose timer control (counter) */
		case NREG_T3CNTR:       /* watchdog timer control (counter) */
			which = (offset - NREG_T0CTRL) / 4;
			if (m_nile_regs[offset - 1] & 1)
			{
				if (m_nile_regs[offset] & 2)
					logerror("Unexpected value: timer %d is prescaled\n", which);
				result = m_nile_regs[offset + 1] = m_timer[which]->remaining().as_double() * (double)SYSTEM_CLOCK;
			}

			if (LOG_TIMERS) logerror("%08X:NILE READ: timer %d counter(%03X) = %08X\n", safe_pc(), which, offset*4, result);
			logit = 0;
			break;

		case NREG_UARTIIR:          /* serial port interrupt ID */
			if (m_nile_regs[NREG_UARTIER] & 2)
				result = 0x02;          /* transmitter buffer IRQ pending */
			else
				result = 0x01;          /* no IRQ pending */
			break;

		case NREG_UARTLSR:          /* serial port line status */
			result = 0x60;
			logit = 0;
			break;

		case NREG_VID:
		case NREG_PCICMD:
		case NREG_REVID:
		case NREG_CLSIZ:
		case NREG_BARC:
		case NREG_BAR0:
		case NREG_BAR1:
		case NREG_CIS:
		case NREG_SSVID:
		case NREG_ROM:
		case NREG_INTLIN:
		case NREG_BAR2:
		case NREG_BAR3:
		case NREG_BAR4:
		case NREG_BAR5:
		case NREG_BAR6:
		case NREG_BAR7:
		case NREG_BAR8:
		case NREG_BARB:
			result = pci_bridge_r(space, offset & 0x3f, mem_mask);
			break;

	}

	if (LOG_NILE && logit)
		logerror("%06X:nile read from offset %03X = %08X\n", safe_pc(), offset*4, result);
=======

/*************************************
 *
 *  SIO interrupts
 *
 *************************************/
std::string vegas_state::sioIRQString(uint8_t data)
{
	std::string sioBitDef[6] = { "SIO_WD", "A2D", "IOASIC", "NSS", "ETHER", "VSYNC" };
	std::string sioBitSel = "";
	for (int i = 0; i < 6; i++)
		if (data & (1 << i)) sioBitSel += " " + sioBitDef[i];
	return sioBitSel;

}

void vegas_state::update_sio_irqs()
{
	if (m_sio_irq_state & m_sio_irq_enable) {
		m_nile->pci_intr_c(ASSERT_LINE);
	}
	else {
		m_nile->pci_intr_c(CLEAR_LINE);
	}
	if (LOG_SIO) {
		std::string sioEnable = sioIRQString(m_sio_irq_enable);
		std::string sioState = sioIRQString(m_sio_irq_state);
		logerror("update_sio_irqs: irq_enable: %02x %s irq_state: %02x %s\n", m_sio_irq_enable, sioEnable, m_sio_irq_state, sioState);
	}
}

WRITE_LINE_MEMBER(vegas_state::uart1_irq_cb)
{
	if (state)
		m_sio_irq_state |= (1 << 4);
	else
		m_sio_irq_state &= ~(1 << 4);
	update_sio_irqs();
}

WRITE_LINE_MEMBER(vegas_state::uart2_irq_cb)
{
	if (state)
		m_sio_irq_state |= (1 << 4);
	else
		m_sio_irq_state &= ~(1 << 4);
	update_sio_irqs();
}

WRITE_LINE_MEMBER(vegas_state::vblank_assert)
{
	if (LOG_SIO)
		logerror("vblank_assert: state: %d\n", state);
	// latch on the correct polarity transition
	if ((state && !(m_sio_reset_ctrl & 0x10)) || (!state && (m_sio_reset_ctrl & 0x10)))
	{
		m_sio_irq_state |= 0x20;
		update_sio_irqs();
	}
}


WRITE_LINE_MEMBER(vegas_state::ioasic_irq)
{
	if (state)
		m_sio_irq_state |= 0x04;
	else
		m_sio_irq_state &= ~0x04;
	update_sio_irqs();
}

WRITE_LINE_MEMBER(vegas_state::ethernet_interrupt)
{
	if (state)
		m_sio_irq_state |= 0x10;
	else
		m_sio_irq_state &= ~0x10;
	update_sio_irqs();
}

void vegas_state::reset_sio()
{
	m_sio_reset_ctrl = 0;
	m_sio_irq_clear = 0;
	m_sio_irq_enable = 0;
	m_sio_irq_state = 0;
	m_sio_led_state = 0;
	update_sio_irqs();
}

READ8_MEMBER(vegas_state::sio_r)
{
	uint32_t result = 0x0;
	int index = offset >> 12;
	switch (index) {
	case 0:
		// Reset Control:  Bit 0=>Reset IOASIC, Bit 1=>Reset NSS Connection, Bit 2=>Reset SMC, Bit 3=>Reset VSYNC, Bit 4=>VSYNC Polarity
		result = m_sio_irq_clear;
		// Hack for fpga programming finished
		m_cpuio_data[3] |= 0x1;
		break;
	case 1:
		// Interrupt Enable
		result = m_sio_irq_enable;
		if (LOG_SIO) {
			std::string sioBitSel = sioIRQString(result);
			logerror("%08X: sio_r: INTR ENABLE 0x%02x %s\n", machine().device("maincpu")->safe_pc(), result, sioBitSel);
		}
		break;
	case 2:
		// Interrupt Cause
		result = m_sio_irq_state & m_sio_irq_enable;
		if (LOG_SIO) {
			std::string sioBitSel = sioIRQString(result);
			logerror("%08X: sio_r: INTR CAUSE 0x%02x %s\n", machine().device("maincpu")->safe_pc(), result, sioBitSel);
		}
		break;
	case 3:
		// Interrupt Status
		result = m_sio_irq_state;
		if (LOG_SIO) {
			std::string sioBitSel = sioIRQString(result);
			logerror("%08X: sio_r: INTR STATUS 0x%02x %s\n", machine().device("maincpu")->safe_pc(), result, sioBitSel);
		}
		break;
	case 4:
		// LED
		result = m_sio_led_state;
		break;
	case 5:
	{
		result = 0x00;
		switch (offset & 0x7) {
		case 0:
			// Gun 1 H Low
			break;
		case 1:
			// Gun 1 H High
			break;
		case 2:
			// Gun 1 V Low
			break;
		case 3:
			// Gun 1 V High
			break;
		case 4:
			// Gun 2 H Low
			break;
		case 5:
			// Gun 2 H High
			break;
		case 6:
			// Gun 2 V Low
			break;
		case 7:
			// Gun 2 V High
			break;
		}
		break;
	}
	}
	if (LOG_SIO && (index < 0x1 || index > 0x4))
		logerror("%08X: sio_r: offset: %08x index: %d result: %02X\n", machine().device("maincpu")->safe_pc(), offset, index, result);
>>>>>>> upstream/master
	return result;
}


<<<<<<< HEAD
WRITE32_MEMBER( vegas_state::nile_w )
{
	UINT32 olddata = m_nile_regs[offset];
	int logit = 1, which;

	COMBINE_DATA(&m_nile_regs[offset]);

	switch (offset)
	{
		case NREG_CPUSTAT+0:    /* CPU status */
		case NREG_CPUSTAT+1:    /* CPU status */
			if (LOG_NILE) logerror("%08X:NILE WRITE: CPU status(%03X) = %08X & %08X\n", safe_pc(), offset*4, data, mem_mask);
			logit = 0;
			break;

		case NREG_INTCTRL+0:    /* Interrupt control */
		case NREG_INTCTRL+1:    /* Interrupt control */
			if (LOG_NILE) logerror("%08X:NILE WRITE: interrupt control(%03X) = %08X & %08X\n", safe_pc(), offset*4, data, mem_mask);
			logit = 0;
			update_nile_irqs();
			break;

		case NREG_INTSTAT0+0:   /* Interrupt status 0 */
		case NREG_INTSTAT0+1:   /* Interrupt status 0 */
			if (LOG_NILE) logerror("%08X:NILE WRITE: interrupt status 0(%03X) = %08X & %08X\n", safe_pc(), offset*4, data, mem_mask);
			logit = 0;
			update_nile_irqs();
			break;

		case NREG_INTSTAT1+0:   /* Interrupt status 1 */
		case NREG_INTSTAT1+1:   /* Interrupt status 1 */
			if (LOG_NILE) logerror("%08X:NILE WRITE: interrupt status 1/enable(%03X) = %08X & %08X\n", safe_pc(), offset*4, data, mem_mask);
			logit = 0;
			update_nile_irqs();
			break;

		case NREG_INTCLR+0:     /* Interrupt clear */
		case NREG_INTCLR+1:     /* Interrupt clear */
			if (LOG_NILE) logerror("%08X:NILE WRITE: interrupt clear(%03X) = %08X & %08X\n", safe_pc(), offset*4, data, mem_mask);
			logit = 0;
			m_nile_irq_state &= ~(m_nile_regs[offset] & ~0xf00);
			update_nile_irqs();
			break;

		case NREG_INTPPES+0:    /* PCI Interrupt control */
		case NREG_INTPPES+1:    /* PCI Interrupt control */
			if (LOG_NILE) logerror("%08X:NILE WRITE: PCI interrupt control(%03X) = %08X & %08X\n", safe_pc(), offset*4, data, mem_mask);
			logit = 0;
			break;

		case NREG_PCIERR+0:     /* PCI error */
		case NREG_PCIERR+1:     /* PCI error */
		case NREG_PCICTRL+0:    /* PCI control */
		case NREG_PCICTRL+1:    /* PCI arbiter */
		case NREG_PCIINIT0+0:   /* PCI master */
		case NREG_PCIINIT0+1:   /* PCI master */
		case NREG_PCIINIT1+1:   /* PCI master */
			logit = 0;
			break;

		case NREG_PCIINIT1+0:   /* PCI master */
			if (((olddata & 0xe) == 0xa) != ((m_nile_regs[offset] & 0xe) == 0xa))
				remap_dynamic_addresses();
			logit = 0;
			break;

		case NREG_T0CTRL+1:     /* SDRAM timer control (control bits) */
		case NREG_T1CTRL+1:     /* bus timeout timer control (control bits) */
		case NREG_T2CTRL+1:     /* general purpose timer control (control bits) */
		case NREG_T3CTRL+1:     /* watchdog timer control (control bits) */
			which = (offset - NREG_T0CTRL) / 4;
			if (LOG_NILE) logerror("%08X:NILE WRITE: timer %d control(%03X) = %08X & %08X\n", safe_pc(), which, offset*4, data, mem_mask);
			logit = 0;

			/* timer just enabled? */
			if (!(olddata & 1) && (m_nile_regs[offset] & 1))
			{
				UINT32 scale = m_nile_regs[offset + 1];
				if (m_nile_regs[offset] & 2)
					logerror("Unexpected value: timer %d is prescaled\n", which);
				if (scale != 0)
					m_timer[which]->adjust(TIMER_PERIOD * scale, which);
				if (LOG_TIMERS) logerror("Starting timer %d at a rate of %d Hz\n", which, (int)ATTOSECONDS_TO_HZ((TIMER_PERIOD * (m_nile_regs[offset + 1] + 1)).attoseconds()));
			}

			/* timer disabled? */
			else if ((olddata & 1) && !(m_nile_regs[offset] & 1))
			{
				if (m_nile_regs[offset] & 2)
					logerror("Unexpected value: timer %d is prescaled\n", which);
				m_nile_regs[offset + 1] = m_timer[which]->remaining().as_double() * SYSTEM_CLOCK;
				m_timer[which]->adjust(attotime::never, which);
			}
			break;

		case NREG_T0CNTR:       /* SDRAM timer control (counter) */
		case NREG_T1CNTR:       /* bus timeout timer control (counter) */
		case NREG_T2CNTR:       /* general purpose timer control (counter) */
		case NREG_T3CNTR:       /* watchdog timer control (counter) */
			which = (offset - NREG_T0CTRL) / 4;
			if (LOG_TIMERS) logerror("%08X:NILE WRITE: timer %d counter(%03X) = %08X & %08X\n", safe_pc(), which, offset*4, data, mem_mask);
			logit = 0;

			if (m_nile_regs[offset - 1] & 1)
			{
				if (m_nile_regs[offset - 1] & 2)
					logerror("Unexpected value: timer %d is prescaled\n", which);
				m_timer[which]->adjust(TIMER_PERIOD * m_nile_regs[offset], which);
			}
			break;

		case NREG_UARTTHR:      /* serial port output */
			if (PRINTF_SERIAL) osd_printf_debug("%c", data & 0xff);
			logit = 0;
			break;
		case NREG_UARTIER:      /* serial interrupt enable */
			update_nile_irqs();
			break;

		case NREG_VID:
		case NREG_PCICMD:
		case NREG_REVID:
		case NREG_CLSIZ:
		case NREG_BARC:
		case NREG_BAR0:
		case NREG_BAR1:
		case NREG_CIS:
		case NREG_SSVID:
		case NREG_ROM:
		case NREG_INTLIN:
		case NREG_BAR2:
		case NREG_BAR3:
		case NREG_BAR4:
		case NREG_BAR5:
		case NREG_BAR6:
		case NREG_BAR7:
		case NREG_BAR8:
		case NREG_BARB:
			pci_bridge_w(space, offset & 0x3f, data, mem_mask);
			break;

		case NREG_DCS2:
		case NREG_DCS3:
		case NREG_DCS4:
		case NREG_DCS5:
		case NREG_DCS6:
		case NREG_DCS7:
		case NREG_DCS8:
		case NREG_PCIW0:
		case NREG_PCIW1:
			remap_dynamic_addresses();
			break;
	}

	if (LOG_NILE && logit)
		logerror("%06X:nile write to offset %03X = %08X & %08X\n", safe_pc(), offset*4, data, mem_mask);
}



/*************************************
 *
 *  IDE interrupts
 *
 *************************************/

WRITE_LINE_MEMBER(vegas_state::ide_interrupt)
{
	m_ide_irq_state = state;
	if (state)
		m_nile_irq_state |= 0x800;
	else
		m_nile_irq_state &= ~0x800;
	update_nile_irqs();
}



/*************************************
 *
 *  SIO interrupts
 *
 *************************************/

void vegas_state::update_sio_irqs()
{
	if (m_sio_irq_state & m_sio_irq_enable)
		m_nile_irq_state |= 0x400;
	else
		m_nile_irq_state &= ~0x400;
	update_nile_irqs();
}


WRITE_LINE_MEMBER(vegas_state::vblank_assert)
{
	if (!m_vblank_state && state)
	{
		m_sio_irq_state |= 0x20;
		update_sio_irqs();
	}
	m_vblank_state = state;

	/* if we have stalled DMA, restart */
//  if (dma_pending_on_vblank[0]) { perform_dma(0); }
//  if (dma_pending_on_vblank[1]) { perform_dma(1); }
//  if (dma_pending_on_vblank[2]) { perform_dma(2); }
//  if (dma_pending_on_vblank[3]) { perform_dma(3); }
}


WRITE_LINE_MEMBER(vegas_state::ioasic_irq)
{
	if (state)
		m_sio_irq_state |= 0x04;
	else
		m_sio_irq_state &= ~0x04;
	update_sio_irqs();
}

WRITE_LINE_MEMBER(vegas_state::ethernet_interrupt)
{
	if (state)
		m_sio_irq_state |= 0x10;
	else
		m_sio_irq_state &= ~0x10;
	update_sio_irqs();
}


READ32_MEMBER( vegas_state::sio_irq_clear_r )
{
	return m_sio_irq_clear;
}


WRITE32_MEMBER( vegas_state::sio_irq_clear_w )
{
	if (ACCESSING_BITS_0_7)
	{
		m_sio_irq_clear = data;

		/* bit 0x01 seems to be used to reset the IOASIC */
		if (!(data & 0x01))
		{
			m_ioasic->ioasic_reset();
			m_dcs->reset_w(data & 0x01);
		}

		/* they toggle bit 0x08 low to reset the VBLANK */
		if (!(data & 0x08))
		{
			m_sio_irq_state &= ~0x20;
			update_sio_irqs();
		}
	}
}


READ32_MEMBER( vegas_state::sio_irq_enable_r )
{
	return m_sio_irq_enable;
}


WRITE32_MEMBER( vegas_state::sio_irq_enable_w )
{
	if (ACCESSING_BITS_0_7)
	{
		m_sio_irq_enable = data;
		update_sio_irqs();
	}
}


READ32_MEMBER( vegas_state::sio_irq_cause_r )
{
	return m_sio_irq_state & m_sio_irq_enable;
}


READ32_MEMBER( vegas_state::sio_irq_status_r )
{
	return m_sio_irq_state;
}


WRITE32_MEMBER( vegas_state::sio_led_w )
{
	if (ACCESSING_BITS_0_7)
		m_sio_led_state = data;
}


READ32_MEMBER( vegas_state::sio_led_r )
{
	return m_sio_led_state;
}



/*************************************
 *
 *  SIO FPGA accesses
 *
 *************************************/

WRITE32_MEMBER( vegas_state::sio_w )
{
	if (ACCESSING_BITS_0_7) offset += 0;
	if (ACCESSING_BITS_8_15) offset += 1;
	if (ACCESSING_BITS_16_23) offset += 2;
	if (ACCESSING_BITS_24_31) offset += 3;
	if (LOG_SIO && offset != 0)
		logerror("%08X:sio write to offset %X = %02X\n", safe_pc(), offset, data >> (offset*8));
	if (offset < 4)
		m_sio_data[offset] = data >> (offset*8);
	if (offset == 1)
		m_sio_data[2] = (m_sio_data[2] & ~0x02) | ((m_sio_data[1] & 0x01) << 1) | (m_sio_data[1] & 0x01);
}


READ32_MEMBER( vegas_state::sio_r )
{
	UINT32 result = 0;
	if (ACCESSING_BITS_0_7) offset += 0;
	if (ACCESSING_BITS_8_15) offset += 1;
	if (ACCESSING_BITS_16_23) offset += 2;
	if (ACCESSING_BITS_24_31) offset += 3;
	if (offset < 4)
		result = m_sio_data[0] | (m_sio_data[1] << 8) | (m_sio_data[2] << 16) | (m_sio_data[3] << 24);
	if (LOG_SIO && offset != 2)
		logerror("%08X:sio read from offset %X = %02X\n", safe_pc(), offset, result >> (offset*8));
=======
WRITE8_MEMBER(vegas_state::sio_w)
{
	// Bit 0 of data is used to program the 6016 FPGA in programming mode (m_cpio_data[3](Bit 0)==0)
	if (m_cpuio_data[3] & 0x1) {
		int index = offset >> 12;
		switch (index) {
		case 0:
			if (LOG_SIO)
				logerror("sio_w: Reset Control offset: %08x index: %d data: %02X\n", offset, index, data);
			// Reset Control:  Bit 0=>Reset IOASIC, Bit 1=>Reset NSS Connection, Bit 2=>Reset SMC, Bit 3=>Reset VSYNC, Bit 4=>VSYNC Polarity
			m_sio_reset_ctrl = data;
			/* bit 0x01 is used to reset the IOASIC */
			if (!(data & 0x01))
			{
				m_ioasic->ioasic_reset();
				m_dcs->reset_w(data & 0x01);
			}
			/* toggle bit 0x08 low to reset the VBLANK */
			if (!(data & 0x08))
			{
				m_sio_irq_state &= ~0x20;
				update_sio_irqs();
			}
			m_sio_irq_clear = data;
			break;
		case 1:
			// Interrupt Enable
			// Bit 0 => SIO Watchdog
			// Bit 1 => A/D Converter
			// Bit 2 => IOASIC
			// Bit 3 => NSS / Hi-Link
			// Bit 4 => Ethernet
			// Bit 5 => Vsync
			if (LOG_SIO) {
				std::string sioBitSel = sioIRQString(data);
				logerror("sio_w: Interrupt Enable 0x%02x %s\n", data, sioBitSel);
				//logerror("sio_w: Interrupt Enable offset: %08x index: %d data: %02X\n", offset, index, data);
			}
			m_sio_irq_enable = data;
			update_sio_irqs();
			break;
		case 4:
			// LED
			if (LOG_SIO)
				logerror("sio_w: LED offset: %08x index: %d data: %02X\n", offset, index, data);
			m_sio_led_state = data;
			break;
		case 6:
			// CMOS Unlock
			m_cmos_unlocked = 1;
			break;
		case 7:
			// Watchdog
			m_timekeeper->watchdog_write(space, offset, data);
			if (0 && LOG_SIO)
				logerror("sio_w: Watchdog: %08x index: %d data: %02X\n", offset, index, data);
			//space.device().execute().eat_cycles(100);
			break;
		}
	}
}

/*************************************
 *
 *  CPU IO accesses
 *
 *************************************/

WRITE8_MEMBER(vegas_state::cpu_io_w)
{
	// 0: system LED
	// 1: PLD Config / Clock Gen
	// 2: PLD Status / Jammma Serial Sense Bit 7:4=>Revision, Bit 1=>Busy, Bit 0=>Config Done
	// 3: System Reset Bit 0=>enable sio, Bit 1=>enable ide, Bit 2=>enable PCI
	m_cpuio_data[offset] = data;
	switch (offset) {
	case 0:
	{
		char digit = 'U';
		switch (data & 0xff) {
		case 0xc0: digit = '0'; break;
		case 0xf9: digit = '1'; break;
		case 0xa4: digit = '2'; break;
		case 0xb0: digit = '3'; break;
		case 0x99: digit = '4'; break;
		case 0x92: digit = '5'; break;
		case 0x82: digit = '6'; break;
		case 0xf8: digit = '7'; break;
		case 0x80: digit = '8'; break;
		case 0x90: digit = '9'; break;
		case 0x88: digit = 'A'; break;
		case 0x83: digit = 'B'; break;
		case 0xc6: digit = 'C'; break;
		case 0xa7: digit = 'c'; break;
		case 0xa1: digit = 'D'; break;
		case 0x86: digit = 'E'; break;
		case 0x87: digit = 'F'; break;
		case 0x7f: digit = '.'; break;
		case 0xf7: digit = '_'; break;
		case 0xbf: digit = '|'; break;
		case 0xfe: digit = '-'; break;
		case 0xff: digit = 'Z'; break;
		}
		if (LOG_SIO) {
			popmessage("System LED: %C", digit);
			//logerror("%08X: cpu_io_w System LED offset %X = %02X '%c'\n", machine().device("maincpu")->safe_pc(), offset, data, digit);
		}
	}
		break;
	case 1:
		m_cpuio_data[2] = (m_cpuio_data[2] & ~0x02) | ((m_cpuio_data[1] & 0x01) << 1) | (m_cpuio_data[1] & 0x01);
		if (!(data & 0x1)) {
			// Need to clear this register while programming SIO FPGA so that fpga config data doesn't register in sio_w
			m_cpuio_data[3] &= ~0x1;
			// Reset the SIO registers
			reset_sio();
		}
		if (LOG_SIO)
			logerror("%08X: cpu_io_w PLD Config offset %X = %02X\n", machine().device("maincpu")->safe_pc(), offset, data);
		break;
	case 2:
		if (LOG_SIO && (m_cpuio_data[3] & 0x1))
			logerror("%08X: cpu_io_w PLD Status / Jamma Serial Sense offset %X = %02X\n", machine().device("maincpu")->safe_pc(), offset, data);
		break;
	case 3:
		// Bit 0: Enable SIO, Bit 1: Enable SIO_R0/IDE, Bit 2: Enable PCI
		if (LOG_SIO)
			logerror("%08X: cpu_io_w System Reset offset %X = %02X\n", machine().device("maincpu")->safe_pc(), offset, data);
		break;
	default:
		logerror("%08X: cpu_io_w unknown offset %X = %02X\n", machine().device("maincpu")->safe_pc(), offset, data);
		break;
	}
}

READ8_MEMBER( vegas_state::cpu_io_r )
{
	uint32_t result = 0;
	if (offset < 4)
		result = m_cpuio_data[offset];
	if (LOG_SIO && !(!(m_cpuio_data[3] & 0x1)))
		logerror("%08X:cpu_io_r offset %X = %02X\n", machine().device("maincpu")->safe_pc(), offset, result);
>>>>>>> upstream/master
	return result;
}



/*************************************
 *
 *  Analog input handling
 *
 *************************************/

READ32_MEMBER( vegas_state::analog_port_r )
{
<<<<<<< HEAD
	return m_pending_analog_read;
=======
	//logerror("%08X: analog_port_r = %08X & %08X\n", machine().device("maincpu")->safe_pc(), m_pending_analog_read, mem_mask);
	// Clear interrupt
	if (m_sio_irq_enable & 0x02) {
		m_sio_irq_state &= ~0x02;
		update_sio_irqs();
	}
	// TODO: Need to look at the proper shift value for sf2049
	return m_pending_analog_read << (m_a2d_shift << 1);
>>>>>>> upstream/master
}


WRITE32_MEMBER( vegas_state::analog_port_w )
{
<<<<<<< HEAD
	if (data < 8 || data > 15)
		logerror("%08X:Unexpected analog port select = %08X\n", safe_pc(), data);
	m_pending_analog_read = m_io_analog[data & 7] ? m_io_analog[data & 7]->read() : 0;
}



/*************************************
 *
 *  Misc accesses
 *
 *************************************/

WRITE32_MEMBER( vegas_state::vegas_watchdog_w )
{
	space.device().execute().eat_cycles(100);
}


WRITE32_MEMBER( vegas_state::asic_fifo_w )
{
	m_ioasic->fifo_w(data);
}


READ32_MEMBER( vegas_state::ide_main_r )
{
	return m_ide->read_cs0(space, offset, mem_mask);
}


WRITE32_MEMBER( vegas_state::ide_main_w )
{
	m_ide->write_cs0(space, offset, data, mem_mask);
}


READ32_MEMBER( vegas_state::ide_alt_r )
{
	return m_ide->read_cs1(space, offset + 1, mem_mask);
}


WRITE32_MEMBER( vegas_state::ide_alt_w )
{
	m_ide->write_cs1(space, offset + 1, data, mem_mask);
}


READ32_MEMBER( vegas_state::ide_bus_master32_r )
{
	return m_ide->bmdma_r(space, offset, mem_mask);
}


WRITE32_MEMBER( vegas_state::ide_bus_master32_w )
{
	m_ide->bmdma_w(space, offset, data, mem_mask);
}


READ32_MEMBER( vegas_state::ethernet_r )
{
	UINT32 result = 0;
=======
	uint32_t shift_data = data >> m_a2d_shift;
	int index = shift_data & 0x7;
	m_pending_analog_read = (m_io_analog[index].read_safe(0));
	//logerror("%08X: analog_port_w = %08X & %08X index = %d\n", machine().device("maincpu")->safe_pc(), data, mem_mask, index);
	if (m_sio_irq_enable & 0x02) {
		m_sio_irq_state |= 0x02;
		update_sio_irqs();
	}

}



/*************************************
 *
 *  Misc accesses
 *
 *************************************/

WRITE32_MEMBER( vegas_state::asic_fifo_w )
{
	m_ioasic->fifo_w(data);
}

READ32_MEMBER( vegas_state::ethernet_r )
{
	uint32_t result = 0;
>>>>>>> upstream/master
	if (ACCESSING_BITS_0_15)
		result |= m_ethernet->read(space, offset * 2 + 0, mem_mask);
	if (ACCESSING_BITS_16_31)
		result |= m_ethernet->read(space, offset * 2 + 1, mem_mask >> 16) << 16;
<<<<<<< HEAD
=======
	//logerror("ethernet_r: offset %08x = %08x & %08x\n", offset, result, mem_mask);
>>>>>>> upstream/master
	return result;
}


WRITE32_MEMBER( vegas_state::ethernet_w )
{
	if (ACCESSING_BITS_0_15)
		m_ethernet->write(space, offset * 2 + 0, data, mem_mask);
	if (ACCESSING_BITS_16_31)
		m_ethernet->write(space, offset * 2 + 1, data >> 16, mem_mask >> 16);
<<<<<<< HEAD
=======
	//logerror("ethernet_w: offset %08x = %08x & %08x\n", offset, data, mem_mask);
>>>>>>> upstream/master
}


WRITE32_MEMBER( vegas_state::dcs3_fifo_full_w )
{
	m_ioasic->fifo_full_w(data);
}

<<<<<<< HEAD


/*************************************
 *
 *  Dynamic addressing
 *
 *************************************/

#define add_dynamic_address(s,e,r,w)         _add_dynamic_address(s,e,r,w)


inline void vegas_state::_add_dynamic_address(offs_t start, offs_t end, read32_delegate read, write32_delegate write)
{
	dynamic_address *dynamic = m_dynamic;
	dynamic[m_dynamic_count].start = start;
	dynamic[m_dynamic_count].end = end;
	dynamic[m_dynamic_count].read = read;
	dynamic[m_dynamic_count].write = write;
	m_dynamic_count++;
}

void vegas_state::remap_dynamic_addresses()
{
	dynamic_address *dynamic = m_dynamic;
	int voodoo_type = voodoo_get_type(m_voodoo);
	offs_t base;
	int addr;

	/* unmap everything we know about */
	for (addr = 0; addr < m_dynamic_count; addr++)
		m_maincpu->space(AS_PROGRAM).unmap_readwrite(dynamic[addr].start, dynamic[addr].end);

	/* the build the list of stuff */
	m_dynamic_count = 0;

	/* DCS2 */
	base = m_nile_regs[NREG_DCS2] & 0x1fffff00;
	if (base >= m_rambase.bytes())
	{
		add_dynamic_address(base + 0x0000, base + 0x0003, read32_delegate(FUNC(vegas_state::sio_irq_clear_r), this), write32_delegate(FUNC(vegas_state::sio_irq_clear_w), this));
		add_dynamic_address(base + 0x1000, base + 0x1003, read32_delegate(FUNC(vegas_state::sio_irq_enable_r), this), write32_delegate(FUNC(vegas_state::sio_irq_enable_w), this));
		add_dynamic_address(base + 0x2000, base + 0x2003, read32_delegate(FUNC(vegas_state::sio_irq_cause_r), this), write32_delegate());
		add_dynamic_address(base + 0x3000, base + 0x3003, read32_delegate(FUNC(vegas_state::sio_irq_status_r), this), write32_delegate());
		add_dynamic_address(base + 0x4000, base + 0x4003, read32_delegate(FUNC(vegas_state::sio_led_r), this), write32_delegate(FUNC(vegas_state::sio_led_w), this));
		add_dynamic_address(base + 0x5000, base + 0x5007, NOP_HANDLER, write32_delegate());
		add_dynamic_address(base + 0x6000, base + 0x6003, read32_delegate(), write32_delegate(FUNC(vegas_state::cmos_unlock_w), this));
		add_dynamic_address(base + 0x7000, base + 0x7003, read32_delegate(), write32_delegate(FUNC(vegas_state::vegas_watchdog_w), this));
	}

	/* DCS3 */
	base = m_nile_regs[NREG_DCS3] & 0x1fffff00;
	if (base >= m_rambase.bytes())
		add_dynamic_address(base + 0x0000, base + 0x0003, read32_delegate(FUNC(vegas_state::analog_port_r), this), write32_delegate(FUNC(vegas_state::analog_port_w), this));

	/* DCS4 */
	base = m_nile_regs[NREG_DCS4] & 0x1fffff00;
	if (base >= m_rambase.bytes())
		add_dynamic_address(base + 0x0000, base + 0x7fff, read32_delegate(FUNC(vegas_state::timekeeper_r), this), write32_delegate(FUNC(vegas_state::timekeeper_w), this));

	/* DCS5 */
	base = m_nile_regs[NREG_DCS5] & 0x1fffff00;
	if (base >= m_rambase.bytes())
		add_dynamic_address(base + 0x0000, base + 0x0003, read32_delegate(FUNC(vegas_state::sio_r), this), write32_delegate(FUNC(vegas_state::sio_w), this));

	/* DCS6 */
	base = m_nile_regs[NREG_DCS6] & 0x1fffff00;
	if (base >= m_rambase.bytes())
	{
		add_dynamic_address(base + 0x0000, base + 0x003f, read32_delegate(FUNC(midway_ioasic_device::packed_r),(midway_ioasic_device*)m_ioasic), write32_delegate(FUNC(midway_ioasic_device::packed_w),(midway_ioasic_device*)m_ioasic));
		add_dynamic_address(base + 0x1000, base + 0x1003, read32_delegate(), write32_delegate(FUNC(vegas_state::asic_fifo_w), this));
		if (m_dcs_idma_cs != 0)
			add_dynamic_address(base + 0x3000, base + 0x3003, read32_delegate(), write32_delegate(FUNC(vegas_state::dcs3_fifo_full_w), this));
		if (m_dcs_idma_cs == 6)
		{
			add_dynamic_address(base + 0x5000, base + 0x5003, read32_delegate(), write32_delegate(FUNC(dcs_audio_device::dsio_idma_addr_w),(dcs_audio_device*)m_dcs));
			add_dynamic_address(base + 0x7000, base + 0x7003, read32_delegate(FUNC(dcs_audio_device::dsio_idma_data_r),(dcs_audio_device*)m_dcs), write32_delegate(FUNC(dcs_audio_device::dsio_idma_data_w),(dcs_audio_device*)m_dcs));
		}
	}

	/* DCS7 */
	base = m_nile_regs[NREG_DCS7] & 0x1fffff00;
	if (base >= m_rambase.bytes())
	{
		add_dynamic_address(base + 0x1000, base + 0x100f, read32_delegate(FUNC(vegas_state::ethernet_r), this), write32_delegate(FUNC(vegas_state::ethernet_w), this));
		if (m_dcs_idma_cs == 7)
		{
			add_dynamic_address(base + 0x5000, base + 0x5003, read32_delegate(), write32_delegate(FUNC(dcs_audio_device::dsio_idma_addr_w),(dcs_audio_device*)m_dcs));
			add_dynamic_address(base + 0x7000, base + 0x7003, read32_delegate(FUNC(dcs_audio_device::dsio_idma_data_r),(dcs_audio_device*)m_dcs), write32_delegate(FUNC(dcs_audio_device::dsio_idma_data_w),(dcs_audio_device*)m_dcs));
		}
	}

	/* PCI config space */
	if ((m_nile_regs[NREG_PCIINIT1] & 0xe) == 0xa)
	{
		base = m_nile_regs[NREG_PCIW1] & 0x1fffff00;
		if (base >= m_rambase.bytes())
		{
			add_dynamic_address(base + (1 << (21 + 4)) + 0x0000, base + (1 << (21 + 4)) + 0x00ff, read32_delegate(FUNC(vegas_state::pci_3dfx_r), this),  write32_delegate(FUNC(vegas_state::pci_3dfx_w), this));
			add_dynamic_address(base + (1 << (21 + 5)) + 0x0000, base + (1 << (21 + 5)) + 0x00ff, read32_delegate(FUNC(vegas_state::pci_ide_r), this),  write32_delegate(FUNC(vegas_state::pci_ide_w), this));
		}
	}

	/* PCI real space */
	else
	{
		/* IDE controller */
		base = m_pci_ide_regs[0x04] & 0xfffffff0;
		if (base >= m_rambase.bytes() && base < 0x20000000)
			add_dynamic_address(base + 0x0000, base + 0x000f, read32_delegate(FUNC(vegas_state::ide_main_r), this),  write32_delegate(FUNC(vegas_state::ide_main_w), this));

		base = m_pci_ide_regs[0x05] & 0xfffffffc;
		if (base >= m_rambase.bytes() && base < 0x20000000)
			add_dynamic_address(base + 0x0000, base + 0x0003, read32_delegate(FUNC(vegas_state::ide_alt_r), this), write32_delegate(FUNC(vegas_state::ide_alt_w), this));

		base = m_pci_ide_regs[0x08] & 0xfffffff0;
		if (base >= m_rambase.bytes() && base < 0x20000000)
			add_dynamic_address(base + 0x0000, base + 0x0007, read32_delegate(FUNC(vegas_state::ide_bus_master32_r), this), write32_delegate(FUNC(vegas_state::ide_bus_master32_w), this));

		/* 3dfx card */
		base = m_pci_3dfx_regs[0x04] & 0xfffffff0;
		if (base >= m_rambase.bytes() && base < 0x20000000)
		{
			if (voodoo_type == TYPE_VOODOO_2)
				add_dynamic_address(base + 0x000000, base + 0xffffff, read32_delegate(FUNC(voodoo_device::voodoo_r),(voodoo_device*)m_voodoo), write32_delegate(FUNC(voodoo_device::voodoo_w),(voodoo_device*)m_voodoo));
			else
				add_dynamic_address(base + 0x000000, base + 0x1ffffff, read32_delegate(FUNC(voodoo_banshee_device::banshee_r),(voodoo_banshee_device*)m_voodoo), write32_delegate(FUNC(voodoo_banshee_device::banshee_w),(voodoo_banshee_device*)m_voodoo));
		}

		if (voodoo_type >= TYPE_VOODOO_BANSHEE)
		{
			base = m_pci_3dfx_regs[0x05] & 0xfffffff0;
			if (base >= m_rambase.bytes() && base < 0x20000000)
				add_dynamic_address(base + 0x0000000, base + 0x1ffffff, read32_delegate(FUNC(voodoo_banshee_device::banshee_fb_r),(voodoo_banshee_device*)m_voodoo), write32_delegate(FUNC(voodoo_banshee_device::banshee_fb_w),(voodoo_banshee_device*)m_voodoo));

			base = m_pci_3dfx_regs[0x06] & 0xfffffff0;
			if (base >= m_rambase.bytes() && base < 0x20000000)
				add_dynamic_address(base + 0x0000000, base + 0x00000ff, read32_delegate(FUNC(voodoo_banshee_device::banshee_io_r),(voodoo_banshee_device*)m_voodoo), write32_delegate(FUNC(voodoo_banshee_device::banshee_io_w),(voodoo_banshee_device*)m_voodoo));

			base = m_pci_3dfx_regs[0x0c] & 0xffff0000;
			if (base >= m_rambase.bytes() && base < 0x20000000)
				add_dynamic_address(base + 0x0000000, base + 0x000ffff, read32_delegate(FUNC(voodoo_banshee_device::banshee_rom_r),(voodoo_banshee_device*)m_voodoo), write32_delegate());
		}
	}

	/* now remap everything */
	if (LOG_DYNAMIC) logerror("remap_dynamic_addresses:\n");
	address_space &space = m_maincpu->space(AS_PROGRAM);
	for (addr = 0; addr < m_dynamic_count; addr++)
	{
		if (LOG_DYNAMIC) logerror("  installing: %08X-%08X \n", dynamic[addr].start, dynamic[addr].end);

		if (dynamic[addr].read == NOP_HANDLER)
			space.nop_read(dynamic[addr].start, dynamic[addr].end);
		else if (!dynamic[addr].read.isnull())
			space.install_read_handler(dynamic[addr].start, dynamic[addr].end, 0, 0, dynamic[addr].read);
		if (!dynamic[addr].write.isnull())
			space.install_write_handler(dynamic[addr].start, dynamic[addr].end, 0, 0, dynamic[addr].write);
	}

	if (LOG_DYNAMIC)
	{
		++m_count;
		popmessage("Remaps = %d", m_count);
	}
}



/*************************************
 *
 *  Memory maps
 *
 *************************************/

static ADDRESS_MAP_START( vegas_map_8mb, AS_PROGRAM, 32, vegas_state )
	ADDRESS_MAP_UNMAP_HIGH
	AM_RANGE(0x00000000, 0x007fffff) AM_RAM AM_SHARE("rambase")
	AM_RANGE(0x1fa00000, 0x1fa00fff) AM_READWRITE(nile_r, nile_w) AM_SHARE("nile_regs")

	AM_RANGE(0x01700000, 0x017fffff) AM_ROM AM_REGION("update", 0)

	AM_RANGE(0x1fc00000, 0x1fc7ffff) AM_ROM AM_REGION("user1", 0) AM_SHARE("rombase")
ADDRESS_MAP_END


static ADDRESS_MAP_START( vegas_map_32mb, AS_PROGRAM, 32, vegas_state )
	ADDRESS_MAP_UNMAP_HIGH
	AM_RANGE(0x00000000, 0x01ffffff) AM_RAM AM_SHARE("rambase")
	AM_RANGE(0x1fa00000, 0x1fa00fff) AM_READWRITE(nile_r, nile_w) AM_SHARE("nile_regs")


	AM_RANGE(0x01700000, 0x017fffff) AM_ROM AM_REGION("update", 0)

	AM_RANGE(0x1fc00000, 0x1fc7ffff) AM_ROM AM_REGION("user1", 0) AM_SHARE("rombase")
ADDRESS_MAP_END


=======
READ32_MEMBER(vegas_state::unknown_r)
{
	uint32_t result = 0xffffffff;
	if (1)
		logerror("unknown_r: offset: %08X data: %08X mask: %08X\n", offset * 4, result, mem_mask);
	return result;
}

/*************************************
* Parallel Port
*************************************/
READ8_MEMBER(vegas_state::parallel_r)
{
	uint8_t result = 0x3;
	logerror("%06X: parallel_r %08x = %02x\n", machine().device("maincpu")->safe_pc(), offset, result);
	return result;
}

WRITE8_MEMBER(vegas_state::parallel_w)
{
	logerror("%06X: parallel_w %08x = %02x\n", machine().device("maincpu")->safe_pc(), offset, data);
}

/*************************************
* Optical 49 Way Joystick I40 Board
*************************************/
WRITE32_MEMBER(vegas_state::i40_w)
{
	//printf("i40_w: data = %08x\n", data);
	//logerror("i40_w: data = %08x\n", data);
	m_i40_data = data;
}

CUSTOM_INPUT_MEMBER(vegas_state::i40_r)
{
	static const uint8_t translate49[7] = { 0x8, 0xc, 0xe, 0xf, 0x3, 0x1, 0x0 };
	int index = m_i40_data & 0xf;
	uint8_t data = 0;
	switch (index) {
	case 0:
		data = translate49[ioport("49WAYX_P1")->read() >> 4];
		break;
	case 1:
		data = translate49[ioport("49WAYY_P1")->read() >> 4];
		break;
	case 2:
		data = translate49[ioport("49WAYX_P2")->read() >> 4];
		break;
	case 3:
		data = translate49[ioport("49WAYY_P2")->read() >> 4];
		break;
	case 4:
		data = translate49[ioport("49WAYX_P3")->read() >> 4];
		break;
	case 5:
		data = translate49[ioport("49WAYY_P3")->read() >> 4];
		break;
	case 6:
		data = translate49[ioport("49WAYX_P4")->read() >> 4];
		break;
	case 7:
		data = translate49[ioport("49WAYY_P4")->read() >> 4];
		break;
	case 10:
	case 11:
	case 12:
		// I40 Detection
		data = ~index & 0xf;
		break;
	default:
		break;
	}
	//if (m_i40_data & 0x1000)
	//  printf("%08X: i40_r: select: %x index: %d data: %x\n", machine().device("maincpu")->safe_pc(), m_i40_data, index, data);
	//m_i40_data &= ~0x1000;
	return data;
}

/*************************************
* Keypad
*************************************/
WRITE32_MEMBER(vegas_state::wheel_board_w)
{
	//logerror("wheel_board_w: data = %08x\n", data);
	/* two writes in pairs. bit 11 high, bit 10 flag, flag off first, on second. arg remains the same. */
	bool valid = (data & (1 << 11));
	bool flag = (data & (1 << 10));
	uint8_t op = (data >> 8) & 0x3;
	uint8_t arg = data & 0xff;

	if (valid && flag)
	{
		switch (op)
		{
		case 0x0:
			machine().output().set_value("wheel", arg); // target wheel angle. signed byte.
			break;

		case 0x1:
			for (uint8_t bit = 0; bit < 8; bit++)
				machine().output().set_lamp_value(bit, (arg >> bit) & 0x1);

			/* leader lamp bit is included in every write, for some reason. */
			machine().output().set_lamp_value(8, (data >> 12) & 0x1);
			break;

		case 0x2:
			m_keypad_select = arg;
			break;
		}
	}
}

CUSTOM_INPUT_MEMBER(vegas_state::keypad_r)
{
	int row_sel;
	for (row_sel=0; row_sel<4; row_sel++)
	{
		if (!(m_keypad_select & (1 << row_sel)))
			break;
	}
	if (row_sel <= 3) {
		uint32_t bits = ioport((const char *)param)->read();
		bits >>= row_sel * 3;
		return bits & 0x7;
	}
	else
		return 0x7;
}

/*************************************
*
*  Gearshift
*
*************************************/
DECLARE_CUSTOM_INPUT_MEMBER(vegas_state::gearshift_r)
{
	// Check for gear change and save gear selection
	uint32_t gear = ioport("GEAR")->read();
	for (int i = 0; i < 4; i++)
	{
		if (gear & (1 << i))
			m_gear = 1 << i;
	}
	return m_gear;
}
>>>>>>> upstream/master

/*************************************
 *
 *  Input ports
 *
 *************************************/

static INPUT_PORTS_START( vegas_common )
	PORT_START("DIPS")
	PORT_DIPNAME( 0x0001, 0x0001, "Unknown0001" )
	PORT_DIPSETTING(      0x0001, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x0002, 0x0002, "Unknown0002" )
	PORT_DIPSETTING(      0x0002, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x0004, 0x0004, "Unknown0004" )
	PORT_DIPSETTING(      0x0004, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x0008, 0x0008, "Unknown0008" )
	PORT_DIPSETTING(      0x0008, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x0010, 0x0010, "Unknown0010" )
	PORT_DIPSETTING(      0x0010, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x0020, 0x0020, "Unknown0020" )
	PORT_DIPSETTING(      0x0020, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x0040, 0x0040, "Unknown0040" )
	PORT_DIPSETTING(      0x0040, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x0080, 0x0080, "Unknown0080" )
	PORT_DIPSETTING(      0x0080, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x0100, 0x0100, "Unknown0100" )
	PORT_DIPSETTING(      0x0100, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x0200, 0x0200, "Unknown0200" )
	PORT_DIPSETTING(      0x0200, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x0400, 0x0400, "Unknown0400" )
	PORT_DIPSETTING(      0x0400, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x0800, 0x0800, "Unknown0800" )
	PORT_DIPSETTING(      0x0800, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x1000, 0x1000, "Unknown1000" )
	PORT_DIPSETTING(      0x1000, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x2000, 0x2000, "Unknown2000" )
	PORT_DIPSETTING(      0x2000, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x4000, 0x4000, "Unknown4000" )
	PORT_DIPSETTING(      0x4000, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x8000, 0x8000, "Unknown8000" )
	PORT_DIPSETTING(      0x8000, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )

	PORT_START("SYSTEM")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_TILT )
	PORT_SERVICE_NO_TOGGLE( 0x0010, IP_ACTIVE_LOW )
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_START2 )
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_COIN4 )
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_START3 )
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_START4 )
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_VOLUME_DOWN )
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_VOLUME_UP )
	PORT_BIT( 0x6000, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_BILL1 )

	PORT_START("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_UP    ) PORT_PLAYER(1) PORT_8WAY
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN  ) PORT_PLAYER(1) PORT_8WAY
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT  ) PORT_PLAYER(1) PORT_8WAY
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_PLAYER(1) PORT_8WAY
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_UP    ) PORT_PLAYER(2) PORT_8WAY
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN  ) PORT_PLAYER(2) PORT_8WAY
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT  ) PORT_PLAYER(2) PORT_8WAY
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_PLAYER(2) PORT_8WAY
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNUSED )

	PORT_START("IN2")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_UP    ) PORT_PLAYER(3) PORT_8WAY
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN  ) PORT_PLAYER(3) PORT_8WAY
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT  ) PORT_PLAYER(3) PORT_8WAY
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_PLAYER(3) PORT_8WAY
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(3)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_UP    ) PORT_PLAYER(4) PORT_8WAY
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN  ) PORT_PLAYER(4) PORT_8WAY
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT  ) PORT_PLAYER(4) PORT_8WAY
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_PLAYER(4) PORT_8WAY
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(4)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(4)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(4)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNUSED )
<<<<<<< HEAD
=======

	PORT_START("AN.0") PORT_BIT( 0xff, 0x80, IPT_SPECIAL )
	PORT_START("AN.1") PORT_BIT( 0xff, 0x80, IPT_SPECIAL )
	PORT_START("AN.2") PORT_BIT( 0xff, 0x80, IPT_SPECIAL )
	PORT_START("AN.3") PORT_BIT( 0xff, 0x80, IPT_SPECIAL )
	PORT_START("AN.4") PORT_BIT( 0xff, 0x80, IPT_SPECIAL )
	PORT_START("AN.5") PORT_BIT( 0xff, 0x80, IPT_SPECIAL )
	PORT_START("AN.6") PORT_BIT( 0xff, 0x80, IPT_SPECIAL )
	PORT_START("AN.7") PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

>>>>>>> upstream/master
INPUT_PORTS_END



/*************************************
 *
 *  Input ports
 *
 *************************************/

static INPUT_PORTS_START( gauntleg )
	PORT_INCLUDE(vegas_common)

	PORT_MODIFY("DIPS")
	PORT_DIPNAME( 0x0001, 0x0001, "PM Dump" )
	PORT_DIPSETTING(      0x0001, "Watchdog resets only" )
	PORT_DIPSETTING(      0x0000, "All resets" )
	PORT_DIPNAME( 0x0040, 0x0040, "Boot ROM Test" )
	PORT_DIPSETTING(      0x0040, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x0800, 0x0800, "SIO Rev" )
	PORT_DIPSETTING(      0x0800, "1 or later")
	PORT_DIPSETTING(      0x0000, "0")
	PORT_DIPNAME( 0x1000, 0x1000, "Harness" )
	PORT_DIPSETTING(      0x1000, "JAMMA" )
	PORT_DIPSETTING(      0x0000, "Midway" )
	PORT_DIPNAME( 0x2000, 0x2000, "Joysticks" )
	PORT_DIPSETTING(      0x2000, "8-Way" )
	PORT_DIPSETTING(      0x0000, "49-Way" )
	PORT_DIPNAME( 0xc000, 0x4000, "Resolution" )
	PORT_DIPSETTING(      0xc000, "Standard Res 512x256" )
	PORT_DIPSETTING(      0x4000, "Medium Res 512x384" )
	PORT_DIPSETTING(      0x0000, "VGA Res 640x480" )
INPUT_PORTS_END


static INPUT_PORTS_START( gauntdl )
	PORT_INCLUDE(vegas_common)

	PORT_MODIFY("DIPS")
	PORT_DIPNAME( 0x0001, 0x0001, "PM Dump" )
	PORT_DIPSETTING(      0x0001, "Watchdog resets only" )
	PORT_DIPSETTING(      0x0000, "All resets" )
	PORT_DIPNAME( 0x0002, 0x0002, "Quantum 3dfx card rev" )
	PORT_DIPSETTING(      0x0002, "4 or later" )
	PORT_DIPSETTING(      0x0000, "3 or earlier" )
	PORT_DIPNAME( 0x0004, 0x0004, "DRAM" )
	PORT_DIPSETTING(      0x0004, "8MB" )
	PORT_DIPSETTING(      0x0000, "32MB" )
<<<<<<< HEAD
	PORT_DIPNAME( 0x0040, 0x0040, "Boot ROM Test" )
	PORT_DIPSETTING(      0x0040, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
=======
	PORT_DIPNAME( 0x00c0, 0x00c0, "Test Mode" )
	PORT_DIPSETTING(      0x00c0, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0040, "Disk-based Test" )
	PORT_DIPSETTING(      0x0080, "EPROM-based Test" )
	PORT_DIPSETTING(      0x0000, "Interactive Diagnostics" )
>>>>>>> upstream/master
	PORT_DIPNAME( 0x0800, 0x0800, "SIO Rev" )
	PORT_DIPSETTING(      0x0800, "1 or later")
	PORT_DIPSETTING(      0x0000, "0")
	PORT_DIPNAME( 0x1000, 0x1000, "Harness" )
	PORT_DIPSETTING(      0x1000, "JAMMA" )
	PORT_DIPSETTING(      0x0000, "Midway" )
	PORT_DIPNAME( 0x2000, 0x2000, "Joysticks" )
	PORT_DIPSETTING(      0x2000, "8-Way" )
	PORT_DIPSETTING(      0x0000, "49-Way" )
	PORT_DIPNAME( 0xc000, 0x4000, "Resolution" )
	PORT_DIPSETTING(      0xc000, "Standard Res 512x256" )
	PORT_DIPSETTING(      0x4000, "Medium Res 512x384" )
	PORT_DIPSETTING(      0x0000, "VGA Res 640x480" )
INPUT_PORTS_END


static INPUT_PORTS_START( tenthdeg )
	PORT_INCLUDE(vegas_common)

	PORT_MODIFY("DIPS")
	PORT_DIPNAME( 0x0040, 0x0040, "Boot ROM Test" )
	PORT_DIPSETTING(      0x0040, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0xc000, 0xc000, "Resolution" )
	PORT_DIPSETTING(      0xc000, "Standard Res 512x256" )
	PORT_DIPSETTING(      0x4000, "Medium Res 512x384" )
	PORT_DIPSETTING(      0x0000, "VGA Res 640x480" )

	PORT_MODIFY("IN2")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_PLAYER(1)   /* P1 roundhouse */
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_BUTTON5 ) PORT_PLAYER(1)   /* P1 fierce */
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_BUTTON6 ) PORT_PLAYER(1)   /* P1 forward */
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_PLAYER(2)   /* P2 roundhouse */
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON6 ) PORT_PLAYER(2)   /* P2 forward */
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON5 ) PORT_PLAYER(2)   /* P2 fierce */
	PORT_BIT( 0xff80, IP_ACTIVE_LOW, IPT_UNUSED )
INPUT_PORTS_END


static INPUT_PORTS_START( warfa )
	PORT_INCLUDE(vegas_common)

	PORT_MODIFY("DIPS")
	PORT_DIPNAME( 0x0001, 0x0001, "PM Dump" )
<<<<<<< HEAD
	PORT_DIPSETTING(      0x0001, "Watchdog resets only" )
	PORT_DIPSETTING(      0x0000, "All resets" )
	PORT_DIPNAME( 0x0002, 0x0002, "Quantum 3dfx card rev" )
	PORT_DIPSETTING(      0x0002, "4" )
	PORT_DIPSETTING(      0x0000, "?" )
	PORT_DIPNAME( 0x0040, 0x0040, "Boot ROM Test" )
	PORT_DIPSETTING(      0x0040, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0xc000, 0x4000, "Resolution" )
	PORT_DIPSETTING(      0xc000, "Standard Res 512x256" )
	PORT_DIPSETTING(      0x4000, "Medium Res 512x384" )
	PORT_DIPSETTING(      0x0000, "VGA Res 640x480" )

	PORT_START("AN.0")
	PORT_BIT( 0xff, 0x80, IPT_AD_STICK_X ) PORT_SENSITIVITY(100) PORT_KEYDELTA(10) PORT_PLAYER(1)

	PORT_START("AN.1")
	PORT_BIT( 0xff, 0x80, IPT_AD_STICK_Y ) PORT_SENSITIVITY(100) PORT_KEYDELTA(10) PORT_PLAYER(1)

	PORT_START("AN.2")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.3")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.4")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.5")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.6")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.7")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )
=======
	PORT_DIPSETTING( 0x0001, "Watchdog resets only" )
	PORT_DIPSETTING( 0x0000, "All resets" )
	PORT_DIPNAME( 0x0002, 0x0002, "Quantum 3dfx card rev" )
	PORT_DIPSETTING( 0x0002, "4" )
	PORT_DIPSETTING( 0x0000, "?" )
	PORT_DIPNAME( 0x0040, 0x0040, "Boot ROM Test" )
	PORT_DIPSETTING( 0x0040, DEF_STR( Off ) )
	PORT_DIPSETTING( 0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x0080, 0x0080, "Boot ROM Test v1.3" )
	PORT_DIPSETTING( 0x0080, DEF_STR( Off ) )
	PORT_DIPSETTING( 0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0xc000, 0x4000, "Resolution" )
	PORT_DIPSETTING( 0xc000, "Standard Res 512x256" )
	PORT_DIPSETTING( 0x4000, "Medium Res 512x384" )
	PORT_DIPSETTING( 0x0000, "VGA Res 640x480" )

	PORT_MODIFY("IN1")
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_CODE(KEYCODE_J) PORT_NAME("Trigger")
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_CODE(KEYCODE_K) PORT_NAME("Discard")
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_CODE(KEYCODE_L) PORT_NAME("Jump")
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_CODE(KEYCODE_U) PORT_NAME("View")
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_CODE(KEYCODE_W) PORT_NAME("Forward")
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_CODE(KEYCODE_S) PORT_NAME("Back")
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_CODE(KEYCODE_A) PORT_NAME("Dodge Left")
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_CODE(KEYCODE_D) PORT_NAME("Dodge Right")

	PORT_MODIFY("AN.0")
	PORT_BIT( 0xff, 0x80, IPT_AD_STICK_X ) PORT_SENSITIVITY(100) PORT_KEYDELTA(10) PORT_PLAYER(1)

	PORT_MODIFY("AN.1")
	PORT_BIT( 0xff, 0x80, IPT_AD_STICK_Y ) PORT_SENSITIVITY(100) PORT_KEYDELTA(10) PORT_PLAYER(1)

>>>>>>> upstream/master
INPUT_PORTS_END


static INPUT_PORTS_START( roadburn )
	PORT_INCLUDE(vegas_common)

	PORT_MODIFY("DIPS")
<<<<<<< HEAD
	PORT_DIPNAME( 0x0002, 0x0002, "Boot ROM Test" )
	PORT_DIPSETTING(      0x0002, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x0040, 0x0040, "Quantum 3dfx card rev" )
	PORT_DIPSETTING(      0x0040, "4" )
	PORT_DIPSETTING(      0x0000, "?" )
	PORT_DIPNAME( 0x0080, 0x0080, "PM Dump" )
	PORT_DIPSETTING(      0x0080, "Watchdog resets only" )
	PORT_DIPSETTING(      0x0000, "All resets" )
	PORT_DIPNAME( 0x0300, 0x0300, "Resolution" )
=======
	PORT_DIPNAME( 0x0003, 0x0003, "Test Mode" )
	PORT_DIPSETTING(      0x0003, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0002, "Disk-based Test" )
	PORT_DIPSETTING(      0x0001, "EPROM-based Test" )
	PORT_DIPSETTING(      0x0000, "Interactive Diagnostics" )
	PORT_DIPNAME( 0x0300, 0x0200, "Resolution" )
>>>>>>> upstream/master
	PORT_DIPSETTING(      0x0300, "Standard Res 512x256" )
	PORT_DIPSETTING(      0x0200, "Medium Res 512x384" )
	PORT_DIPSETTING(      0x0000, "VGA Res 640x480" )

<<<<<<< HEAD
	PORT_START("AN.0")   /* Steer */
	PORT_BIT( 0xff, 0x80, IPT_PADDLE ) PORT_MINMAX(0x10, 0xf0) PORT_SENSITIVITY(25) PORT_KEYDELTA(5)

	PORT_START("AN.1")   /* Accel */
	PORT_BIT( 0xff, 0x80, IPT_PEDAL ) PORT_MINMAX(0x00, 0xff) PORT_SENSITIVITY(25) PORT_KEYDELTA(20)

	PORT_START("AN.2")   /* Brake */
	PORT_BIT( 0xff, 0x80, IPT_PEDAL2 ) PORT_MINMAX(0x00, 0xff) PORT_SENSITIVITY(25) PORT_KEYDELTA(100)

	PORT_START("AN.3")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.4")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.5")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.6")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.7")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )
=======
	PORT_MODIFY("AN.0")   /* Accel */
	PORT_BIT( 0xff, 0x80, IPT_PEDAL ) PORT_MINMAX(0x00, 0xff) PORT_SENSITIVITY(100) PORT_KEYDELTA(20)

	PORT_MODIFY("AN.1")   /* Steer */
	PORT_BIT( 0xff, 0x80, IPT_PADDLE ) PORT_MINMAX(0x00, 0xff) PORT_SENSITIVITY(50) PORT_KEYDELTA(10)

	PORT_MODIFY("AN.2")   /* Seat Tilt */
	PORT_BIT( 0xff, 0x80, IPT_AD_STICK_X ) PORT_MINMAX(0x00, 0xff) PORT_SENSITIVITY(50) PORT_KEYDELTA(10)

>>>>>>> upstream/master
INPUT_PORTS_END


static INPUT_PORTS_START( nbashowt )
	PORT_INCLUDE(vegas_common)

	PORT_MODIFY("DIPS")
	PORT_DIPNAME( 0x0001, 0x0000, "Coinage Source" )
	PORT_DIPSETTING(      0x0001, "Dipswitch" )
	PORT_DIPSETTING(      0x0000, "CMOS" )
	PORT_DIPNAME( 0x000e, 0x000e, DEF_STR( Coinage ) )
	PORT_DIPSETTING(      0x000e, "Mode 1" )
<<<<<<< HEAD
	PORT_DIPSETTING(      0x0008, "Mode 2" )
	PORT_DIPSETTING(      0x0009, "Mode 3" )
	PORT_DIPSETTING(      0x0002, "Mode 4" )
	PORT_DIPSETTING(      0x000c, "Mode ECA" )
//  PORT_DIPSETTING(      0x0004, "Not Used 1" )        /* Marked as Unused in the manual */
//  PORT_DIPSETTING(      0x0008, "Not Used 2" )        /* Marked as Unused in the manual */
=======
	PORT_DIPSETTING(      0x000c, "Mode 2" )
	PORT_DIPSETTING(      0x000a, "Mode 3" )
	PORT_DIPSETTING(      0x0008, "Mode 4" )
	PORT_DIPSETTING(      0x0006, "Mode 5")
	PORT_DIPSETTING(      0x0004, "Mode 6")
	PORT_DIPSETTING(      0x0002, "Mode 7")
>>>>>>> upstream/master
	PORT_DIPSETTING(      0x0000, DEF_STR( Free_Play ) )
	PORT_DIPNAME( 0x0030, 0x0030, "Curency Type" )
	PORT_DIPSETTING(      0x0030, DEF_STR( USA ) )
	PORT_DIPSETTING(      0x0020, DEF_STR( French ) )
	PORT_DIPSETTING(      0x0010, DEF_STR( German ) )
<<<<<<< HEAD
//  PORT_DIPSETTING(      0x0000, "Not Used" )      /* Marked as Unused in the manual */
	PORT_DIPSETTING(      0x0000, DEF_STR( Free_Play ) )
	PORT_DIPNAME( 0x0040, 0x0000, DEF_STR( Unknown ) )  /* Marked as Unused in the manual */
	PORT_DIPSETTING(      0x0040, "0" )
	PORT_DIPSETTING(      0x0000, "1" )
	PORT_DIPNAME( 0x0080, 0x0080, "Game" )
	PORT_DIPSETTING(      0x0080, "NBA Showtime" )
	PORT_DIPSETTING(      0x0000, "Blitz 99" )
	PORT_DIPNAME( 0x0100, 0x0100, "Joysticks" )
	PORT_DIPSETTING(      0x0100, "8-Way" )
	PORT_DIPSETTING(      0x0000, "49-Way" )
	PORT_DIPNAME( 0x0600, 0x0200, "Graphics Mode" )
	PORT_DIPSETTING(      0x0200, "512x385 @ 25KHz" )
	PORT_DIPSETTING(      0x0400, "512x256 @ 15KHz" )
//  PORT_DIPSETTING(      0x0600, "0" )         /* Marked as Unused in the manual */
//  PORT_DIPSETTING(      0x0000, "3" )         /* Marked as Unused in the manual */
	PORT_DIPNAME( 0x1800, 0x1800, "Graphics Speed" )
	PORT_DIPSETTING(      0x0000, "45 MHz" )
	PORT_DIPSETTING(      0x0800, "47 MHz" )
	PORT_DIPSETTING(      0x1000, "49 MHz" )
	PORT_DIPSETTING(      0x1800, "51 MHz" )
	PORT_DIPNAME( 0x2000, 0x0000, "Number of Players" )
=======
	PORT_DIPSETTING(      0x0000, DEF_STR( Free_Play ) )
	PORT_DIPNAME( 0x0040, 0x0040, "Select Game" )
	PORT_DIPSETTING(      0x0040, DEF_STR(Yes))
	PORT_DIPSETTING(      0x0000, DEF_STR(No))
	PORT_DIPNAME( 0x0080, 0x0080, "Game Powerup" )
	PORT_DIPSETTING(      0x0080, "NBA Showtime" )
	PORT_DIPSETTING(      0x0000, "NFL Blitz" )
	PORT_DIPNAME( 0x0100, 0x0000, "Joysticks" )
	PORT_DIPSETTING(      0x0100, "8-Way" )
	PORT_DIPSETTING(      0x0000, "49-Way" )
	PORT_DIPNAME( 0x0200, 0x0200, "Graphics Mode" )
	PORT_DIPSETTING(      0x0200, "Med Res" )
	PORT_DIPSETTING(      0x0000, "Low Res" )
	PORT_DIPUNUSED(       0x1c00, 0x1c00 )
	PORT_DIPNAME( 0x2000, 0x2000, "Number of Players" )
>>>>>>> upstream/master
	PORT_DIPSETTING(      0x2000, "2" )
	PORT_DIPSETTING(      0x0000, "4" )
	PORT_DIPNAME( 0x4000, 0x0000, "Power On Self Test" )
	PORT_DIPSETTING(      0x0000, DEF_STR( No ) )
	PORT_DIPSETTING(      0x4000, DEF_STR( Yes ) )
	PORT_DIPNAME( 0x8000, 0x8000, "Test Switch" )
	PORT_DIPSETTING(      0x8000, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
<<<<<<< HEAD
=======

	PORT_MODIFY("IN1")
	PORT_BIT( 0x000f, IP_ACTIVE_LOW, IPT_UNUSED) // P1 Joystick
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0f00, IP_ACTIVE_LOW, IPT_UNUSED) // P2 Joystick
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNUSED )

	PORT_MODIFY("IN2")
	PORT_BIT( 0x000f, IP_ACTIVE_LOW, IPT_UNUSED) // P3 Joystick
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(3)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0f00, IP_ACTIVE_LOW, IPT_SPECIAL) PORT_CUSTOM_MEMBER(DEVICE_SELF, vegas_state, i40_r, nullptr)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(4)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(4)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(4)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNUSED )

	PORT_START("49WAYX_P1")
	PORT_BIT( 0xff, 0x38, IPT_AD_STICK_X ) PORT_MINMAX(0x00,0x6f) PORT_SENSITIVITY(100) PORT_KEYDELTA(10) PORT_PLAYER(1)

	PORT_START("49WAYY_P1")
	PORT_BIT( 0xff, 0x38, IPT_AD_STICK_Y ) PORT_MINMAX(0x00,0x6f) PORT_SENSITIVITY(100) PORT_KEYDELTA(10) PORT_PLAYER(1)

	PORT_START("49WAYX_P2")
	PORT_BIT(0xff, 0x38, IPT_AD_STICK_X) PORT_MINMAX(0x00, 0x6f) PORT_SENSITIVITY(100) PORT_KEYDELTA(10) PORT_PLAYER(2)

	PORT_START("49WAYY_P2")
	PORT_BIT(0xff, 0x38, IPT_AD_STICK_Y) PORT_MINMAX(0x00, 0x6f) PORT_SENSITIVITY(100) PORT_KEYDELTA(10) PORT_PLAYER(2)

	PORT_START("49WAYX_P3")
	PORT_BIT(0xff, 0x38, IPT_AD_STICK_X) PORT_MINMAX(0x00, 0x6f) PORT_SENSITIVITY(100) PORT_KEYDELTA(10) PORT_PLAYER(3)

	PORT_START("49WAYY_P3")
	PORT_BIT(0xff, 0x38, IPT_AD_STICK_Y) PORT_MINMAX(0x00, 0x6f) PORT_SENSITIVITY(100) PORT_KEYDELTA(10) PORT_PLAYER(3)

	PORT_START("49WAYX_P4")
	PORT_BIT(0xff, 0x38, IPT_AD_STICK_X) PORT_MINMAX(0x00, 0x6f) PORT_SENSITIVITY(100) PORT_KEYDELTA(10) PORT_PLAYER(4)

	PORT_START("49WAYY_P4")
	PORT_BIT(0xff, 0x38, IPT_AD_STICK_Y) PORT_MINMAX(0x00, 0x6f) PORT_SENSITIVITY(100) PORT_KEYDELTA(10) PORT_PLAYER(4)

>>>>>>> upstream/master
INPUT_PORTS_END


static INPUT_PORTS_START( sf2049 )
	PORT_INCLUDE(vegas_common)

	PORT_MODIFY("DIPS")
	PORT_DIPNAME( 0x0003, 0x0003, "Test Mode" )
	PORT_DIPSETTING(      0x0003, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0002, "Disk-based Test" )
	PORT_DIPSETTING(      0x0001, "EPROM-based Test" )
	PORT_DIPSETTING(      0x0000, "Interactive Diagnostics" )
	PORT_DIPNAME( 0x0080, 0x0080, "PM Dump" )
	PORT_DIPSETTING(      0x0080, "Watchdog resets only" )
	PORT_DIPSETTING(      0x0000, "All resets" )
<<<<<<< HEAD
	PORT_DIPNAME( 0x0100, 0x0200, "Resolution" )
	PORT_DIPSETTING(      0x0000, "Standard Res 512x256" )
	PORT_DIPSETTING(      0x0200, "Medium Res 512x384" )
	PORT_DIPSETTING(      0x0300, "VGA Res 640x480" )

	PORT_START("AN.0")   /* Steer */
	PORT_BIT( 0xff, 0x80, IPT_PADDLE ) PORT_MINMAX(0x10, 0xf0) PORT_SENSITIVITY(25) PORT_KEYDELTA(5)

	PORT_START("AN.1")   /* Accel */
	PORT_BIT( 0xff, 0x80, IPT_PEDAL ) PORT_MINMAX(0x00, 0xff) PORT_SENSITIVITY(25) PORT_KEYDELTA(20)

	PORT_START("AN.2")   /* Brake */
	PORT_BIT( 0xff, 0x80, IPT_PEDAL2 ) PORT_MINMAX(0x00, 0xff) PORT_SENSITIVITY(25) PORT_KEYDELTA(100)

	PORT_START("AN.3")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.4")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.5")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.6")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.7")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )
INPUT_PORTS_END


static INPUT_PORTS_START( sf2049se )
	PORT_INCLUDE(vegas_common)

	PORT_MODIFY("DIPS")

	PORT_START("AN.0")   /* Steer */
	PORT_BIT( 0xff, 0x80, IPT_PADDLE ) PORT_MINMAX(0x10, 0xf0) PORT_SENSITIVITY(25) PORT_KEYDELTA(5)

	PORT_START("AN.1")   /* Accel */
	PORT_BIT( 0xff, 0x80, IPT_PEDAL ) PORT_MINMAX(0x00, 0xff) PORT_SENSITIVITY(25) PORT_KEYDELTA(20)

	PORT_START("AN.2")   /* Brake */
	PORT_BIT( 0xff, 0x80, IPT_PEDAL2 ) PORT_MINMAX(0x00, 0xff) PORT_SENSITIVITY(25) PORT_KEYDELTA(100)

	PORT_START("AN.3")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.4")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.5")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.6")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.7")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )
INPUT_PORTS_END


static INPUT_PORTS_START( sf2049te )
	PORT_INCLUDE(vegas_common)

	PORT_MODIFY("DIPS")

	PORT_START("AN.0")   /* Steer */
	PORT_BIT( 0xff, 0x80, IPT_PADDLE ) PORT_MINMAX(0x10, 0xf0) PORT_SENSITIVITY(25) PORT_KEYDELTA(5)

	PORT_START("AN.1")   /* Accel */
	PORT_BIT( 0xff, 0x80, IPT_PEDAL ) PORT_MINMAX(0x00, 0xff) PORT_SENSITIVITY(25) PORT_KEYDELTA(20)

	PORT_START("AN.2")   /* Brake */
	PORT_BIT( 0xff, 0x80, IPT_PEDAL2 ) PORT_MINMAX(0x00, 0xff) PORT_SENSITIVITY(25) PORT_KEYDELTA(100)

	PORT_START("AN.3")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.4")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.5")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.6")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.7")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )
INPUT_PORTS_END


static INPUT_PORTS_START( cartfury )
	PORT_INCLUDE(vegas_common)

	PORT_MODIFY("DIPS")

	PORT_START("AN.0")   /* Steer */
	PORT_BIT( 0xff, 0x80, IPT_PADDLE ) PORT_MINMAX(0x10, 0xf0) PORT_SENSITIVITY(25) PORT_KEYDELTA(5)

	PORT_START("AN.1")   /* Accel */
	PORT_BIT( 0xff, 0x80, IPT_PEDAL ) PORT_MINMAX(0x00, 0xff) PORT_SENSITIVITY(25) PORT_KEYDELTA(20)

	PORT_START("AN.2")   /* Brake */
	PORT_BIT( 0xff, 0x80, IPT_PEDAL2 ) PORT_MINMAX(0x00, 0xff) PORT_SENSITIVITY(25) PORT_KEYDELTA(100)

	PORT_START("AN.3")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.4")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.5")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.6")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )

	PORT_START("AN.7")
	PORT_BIT( 0xff, 0x80, IPT_SPECIAL )
INPUT_PORTS_END


=======
	PORT_DIPNAME( 0x0300, 0x0000, "Resolution" )
	PORT_DIPSETTING(      0x0300, "Standard Res 512x256" )
	PORT_DIPSETTING(      0x0200, "Medium Res 512x384" )
	PORT_DIPSETTING(      0x0000, "VGA Res 640x480" )

	PORT_MODIFY("SYSTEM")
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_START1 ) PORT_NAME("Abort") PORT_PLAYER(1) /* Abort */
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON8 ) PORT_NAME(DEF_STR( Reverse )) PORT_PLAYER(1)    /* reverse */

	PORT_MODIFY("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_BUTTON9 ) PORT_NAME("View 1") PORT_PLAYER(1)   /* view 1 */
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_BUTTON10 ) PORT_NAME("View 2") PORT_PLAYER(1)   /* view 2 */
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_BUTTON11 ) PORT_NAME("View 3") PORT_PLAYER(1)  /* view 3 */
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_BUTTON12 ) PORT_NAME("Music") PORT_PLAYER(1)   /* music */
	PORT_BIT( 0x0070, IP_ACTIVE_HIGH, IPT_SPECIAL) PORT_CUSTOM_MEMBER(DEVICE_SELF, vegas_state, keypad_r, "KEYPAD" )
	PORT_BIT( 0x0f00, IP_ACTIVE_HIGH, IPT_SPECIAL) PORT_CUSTOM_MEMBER(DEVICE_SELF, vegas_state, gearshift_r, "GEAR" )

	PORT_START("GEAR")
	PORT_BIT( 0x1, IP_ACTIVE_HIGH, IPT_BUTTON4 ) PORT_NAME("1st Gear") PORT_PLAYER(1) /* 1st gear */
	PORT_BIT( 0x2, IP_ACTIVE_HIGH, IPT_BUTTON5 ) PORT_NAME("2nd Gear") PORT_PLAYER(1) /* 2nd gear */
	PORT_BIT( 0x4, IP_ACTIVE_HIGH, IPT_BUTTON6 ) PORT_NAME("3rd Gear") PORT_PLAYER(1) /* 3rd gear */
	PORT_BIT( 0x8, IP_ACTIVE_HIGH, IPT_BUTTON7 ) PORT_NAME("4th Gear") PORT_PLAYER(1) /* 4th gear */

	PORT_START("KEYPAD")
	PORT_BIT(0x0200, IP_ACTIVE_LOW, IPT_KEYPAD) PORT_CHAR(UCHAR_MAMEKEY(1_PAD)) PORT_CODE(KEYCODE_1_PAD) /* keypad 1 */
	PORT_BIT(0x0040, IP_ACTIVE_LOW, IPT_KEYPAD) PORT_CHAR(UCHAR_MAMEKEY(4_PAD)) PORT_CODE(KEYCODE_4_PAD) /* keypad 4 */
	PORT_BIT(0x0008, IP_ACTIVE_LOW, IPT_KEYPAD) PORT_CHAR(UCHAR_MAMEKEY(7_PAD)) PORT_CODE(KEYCODE_7_PAD) /* keypad 7 */
	PORT_BIT(0x0001, IP_ACTIVE_LOW, IPT_KEYPAD) PORT_CHAR(UCHAR_MAMEKEY(ASTERISK)) PORT_CODE(KEYCODE_ASTERISK) /* keypad * */
	PORT_BIT(0x0400, IP_ACTIVE_LOW, IPT_KEYPAD) PORT_CHAR(UCHAR_MAMEKEY(2_PAD)) PORT_CODE(KEYCODE_2_PAD) /* keypad 2 */
	PORT_BIT(0x0080, IP_ACTIVE_LOW, IPT_KEYPAD) PORT_CHAR(UCHAR_MAMEKEY(5_PAD)) PORT_CODE(KEYCODE_5_PAD) /* keypad 5 */
	PORT_BIT(0x0010, IP_ACTIVE_LOW, IPT_KEYPAD) PORT_CHAR(UCHAR_MAMEKEY(8_PAD)) PORT_CODE(KEYCODE_8_PAD) /* keypad 8 */
	PORT_BIT(0x0002, IP_ACTIVE_LOW, IPT_KEYPAD) PORT_CHAR(UCHAR_MAMEKEY(0_PAD)) PORT_CODE(KEYCODE_0_PAD) /* keypad 0 */
	PORT_BIT(0x0800, IP_ACTIVE_LOW, IPT_KEYPAD) PORT_CHAR(UCHAR_MAMEKEY(3_PAD)) PORT_CODE(KEYCODE_3_PAD) /* keypad 3 */
	PORT_BIT(0x0100, IP_ACTIVE_LOW, IPT_KEYPAD) PORT_CHAR(UCHAR_MAMEKEY(6_PAD)) PORT_CODE(KEYCODE_6_PAD) /* keypad 6 */
	PORT_BIT(0x0020, IP_ACTIVE_LOW, IPT_KEYPAD) PORT_CHAR(UCHAR_MAMEKEY(9_PAD)) PORT_CODE(KEYCODE_9_PAD) /* keypad 9 */
	PORT_BIT(0x0004, IP_ACTIVE_LOW, IPT_KEYPAD) PORT_NAME("Keypad #") PORT_CODE(KEYCODE_PLUS_PAD)   /* keypad + */

	PORT_MODIFY("AN.2")   /* Accel */
	PORT_BIT( 0xff, 0x00, IPT_PEDAL ) PORT_SENSITIVITY(25) PORT_KEYDELTA(20) PORT_PLAYER(1)

	PORT_MODIFY("AN.3")   /* Clutch */
	PORT_BIT( 0xff, 0x00, IPT_PEDAL3 ) PORT_SENSITIVITY(25) PORT_KEYDELTA(100) PORT_PLAYER(1)

	PORT_MODIFY("AN.6")   /* Brake */
	PORT_BIT( 0xff, 0x00, IPT_PEDAL2 ) PORT_SENSITIVITY(25) PORT_KEYDELTA(100) PORT_PLAYER(1)

	PORT_MODIFY("AN.7")   /* Steer */
	PORT_BIT( 0xff, 0x80, IPT_PADDLE ) PORT_MINMAX(0x10, 0xf0) PORT_SENSITIVITY(25) PORT_KEYDELTA(5)
INPUT_PORTS_END

static INPUT_PORTS_START( sf2049se )
	PORT_INCLUDE(sf2049)

	PORT_MODIFY("DIPS")
	PORT_DIPUNUSED( 0x001e, 0x001e )
	PORT_DIPNAME(0x0020, 0x0020, "Boot Message")
	PORT_DIPSETTING(      0x0020, "Quiet")
	PORT_DIPSETTING(      0x0000, "Squawk During Boot")
	PORT_DIPNAME( 0x00c0, 0x00c0, "Test Mode" )
	PORT_DIPSETTING(      0x00c0, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0080, "Disk-based Test" )
	PORT_DIPSETTING(      0x0040, "EPROM-based Test" )
	PORT_DIPSETTING(      0x0000, "Interactive Diagnostics" )
	PORT_DIPNAME( 0x0001, 0x0001, "PM Dump" )
	PORT_DIPSETTING(      0x0001, "Watchdog resets only" )
	PORT_DIPSETTING(      0x0000, "All resets" )
	PORT_DIPUNUSED( 0x1f00, 0x1f00 )
	PORT_DIPNAME( 0xc000, 0x8000, "Resolution" )
	PORT_DIPSETTING(      0xc000, "Standard Res 512x256" )
	PORT_DIPSETTING(      0x4000, "Medium Res 512x384" )
	PORT_DIPSETTING(      0x8000, "VGA Res 640x480" )
	PORT_DIPNAME( 0x2000, 0x2000, "Cabinet Type" )
	PORT_DIPSETTING(      0x2000, "Sit down cabinet" )
	PORT_DIPSETTING(      0x0000, "Upright cabinet" )
INPUT_PORTS_END

static INPUT_PORTS_START( cartfury )
	PORT_INCLUDE(vegas_common)

	PORT_MODIFY("DIPS")
	PORT_DIPNAME( 0x0001, 0x0000, "Coinage Source" )
	PORT_DIPSETTING(      0x0001, "Dipswitch" )
	PORT_DIPSETTING(      0x0000, "CMOS" )
	PORT_DIPNAME( 0x000e, 0x000e, DEF_STR( Coinage ) )
	PORT_DIPSETTING(      0x000e, "Mode 1" )
	PORT_DIPSETTING(      0x000c, "Mode 2" )
	PORT_DIPSETTING(      0x000a, "Mode 3" )
	PORT_DIPSETTING(      0x0008, "Mode 4" )
	PORT_DIPSETTING(      0x0006, "Mode 5")
	PORT_DIPSETTING(      0x0004, "Mode 6")
	PORT_DIPSETTING(      0x0002, "Mode 7")
	PORT_DIPSETTING(      0x0000, DEF_STR( Free_Play ) )
	PORT_DIPNAME( 0x0030, 0x0030, "Curency Type" )
	PORT_DIPSETTING(      0x0030, DEF_STR( USA ) )
	PORT_DIPSETTING(      0x0020, DEF_STR( French ) )
	PORT_DIPSETTING(      0x0010, DEF_STR( German ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( Free_Play ) )
	PORT_DIPNAME( 0x2000, 0x2000, "Disable Brake" )
	PORT_DIPSETTING(      0x2000, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )
	PORT_DIPNAME( 0x8000, 0x8000, "Test Switch" )
	PORT_DIPSETTING(      0x8000, DEF_STR( Off ) )
	PORT_DIPSETTING(      0x0000, DEF_STR( On ) )

	PORT_MODIFY("IN1")
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON9 ) PORT_NAME("View 1") PORT_PLAYER(1)   /* view 1 */
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON10 ) PORT_NAME("View 2") PORT_PLAYER(1)   /* view 2 */
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON11 ) PORT_NAME("View 3") PORT_PLAYER(1)  /* view 3 */
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_BUTTON12 ) PORT_NAME("Music") PORT_PLAYER(1)   /* music */
	PORT_BIT( 0x0f00, IP_ACTIVE_HIGH, IPT_SPECIAL) PORT_CUSTOM_MEMBER(DEVICE_SELF, vegas_state, gearshift_r, "GEAR" )

	PORT_START("GEAR")
	PORT_BIT( 0x1, IP_ACTIVE_HIGH, IPT_BUTTON4 ) PORT_NAME("1st Gear") PORT_PLAYER(1) /* 1st gear */
	PORT_BIT( 0x2, IP_ACTIVE_HIGH, IPT_BUTTON5 ) PORT_NAME("2nd Gear") PORT_PLAYER(1) /* 2nd gear */
	PORT_BIT( 0x4, IP_ACTIVE_HIGH, IPT_BUTTON6 ) PORT_NAME("3rd Gear") PORT_PLAYER(1) /* 3rd gear */
	PORT_BIT( 0x8, IP_ACTIVE_HIGH, IPT_BUTTON7 ) PORT_NAME("4th Gear") PORT_PLAYER(1) /* 4th gear */

	PORT_MODIFY("AN.0")   /* Steer */
	PORT_BIT( 0xff, 0x80, IPT_PADDLE ) PORT_MINMAX(0x10, 0xf0) PORT_SENSITIVITY(25) PORT_KEYDELTA(5)

	PORT_MODIFY("AN.1")   /* Accel */
	PORT_BIT( 0xff, 0x00, IPT_PEDAL ) PORT_SENSITIVITY(25) PORT_KEYDELTA(20) PORT_PLAYER(1)

	PORT_MODIFY("AN.2")   /* Brake */
	PORT_BIT( 0xff, 0x00, IPT_PEDAL2 ) PORT_SENSITIVITY(25) PORT_KEYDELTA(100) PORT_PLAYER(1)

INPUT_PORTS_END

/*************************************
*
*  Memory maps
*
*************************************/
static ADDRESS_MAP_START(vegas_cs2_map, AS_PROGRAM, 32, vegas_state)
	AM_RANGE(0x00000000, 0x00007003) AM_READWRITE8(sio_r, sio_w, 0xffffffff)
ADDRESS_MAP_END

static ADDRESS_MAP_START(vegas_cs3_map, AS_PROGRAM, 32, vegas_state)
	AM_RANGE(0x00000000, 0x00000003) AM_READWRITE(analog_port_r, analog_port_w)
	//AM_RANGE(0x00001000, 0x00001003) AM_READWRITE(lcd_r, lcd_w)
ADDRESS_MAP_END

static ADDRESS_MAP_START(vegas_cs4_map, AS_PROGRAM, 32, vegas_state)
	AM_RANGE(0x00000000, 0x00007fff) AM_READWRITE(timekeeper_r, timekeeper_w)
ADDRESS_MAP_END

static ADDRESS_MAP_START(vegas_cs5_map, AS_PROGRAM, 32, vegas_state)
	AM_RANGE(0x00000000, 0x00000003) AM_READWRITE8(cpu_io_r, cpu_io_w, 0xffffffff)
	AM_RANGE(0x00100000, 0x001fffff) AM_READ(unknown_r)
ADDRESS_MAP_END

static ADDRESS_MAP_START(vegas_cs6_map, AS_PROGRAM, 32, vegas_state)
	AM_RANGE(0x00000000, 0x0000003f) AM_DEVREADWRITE("ioasic", midway_ioasic_device, packed_r, packed_w)
	AM_RANGE(0x00001000, 0x00001003) AM_WRITE(asic_fifo_w)
	AM_RANGE(0x00003000, 0x00003003) AM_WRITE(dcs3_fifo_full_w)  // if (m_dcs_idma_cs != 0)
	AM_RANGE(0x00005000, 0x00005003) AM_DEVWRITE("dcs", dcs_audio_device, dsio_idma_addr_w) // if (m_dcs_idma_cs == 6)
	AM_RANGE(0x00007000, 0x00007003) AM_DEVREADWRITE("dcs", dcs_audio_device, dsio_idma_data_r, dsio_idma_data_w) // if (m_dcs_idma_cs == 6)
ADDRESS_MAP_END

static ADDRESS_MAP_START(vegas_cs7_map, AS_PROGRAM, 32, vegas_state)
	//AM_RANGE(0x00000000, 0x00000003) AM_READWRITE8(nss_r, nss_w, 0xffffffff)
	AM_RANGE(0x00001000, 0x0000100f) AM_READWRITE(ethernet_r, ethernet_w)
	AM_RANGE(0x00005000, 0x00005003) AM_DEVWRITE("dcs", dcs_audio_device, dsio_idma_addr_w) // if (m_dcs_idma_cs == 7)
	AM_RANGE(0x00007000, 0x00007003) AM_DEVREADWRITE("dcs", dcs_audio_device, dsio_idma_data_r, dsio_idma_data_w) // if (m_dcs_idma_cs == 7)
ADDRESS_MAP_END

static ADDRESS_MAP_START(vegas_cs8_map, AS_PROGRAM, 32, vegas_state)
	AM_RANGE(0x01000000, 0x0100001f) AM_DEVREADWRITE8("uart2", ns16550_device, ins8250_r, ins8250_w, 0xff) // Serial UART2 (TL16C552 CS0)
	AM_RANGE(0x01400000, 0x0140001f) AM_DEVREADWRITE8("uart1", ns16550_device, ins8250_r, ins8250_w, 0xff) // Serial UART1 (TL16C552 CS1)
	AM_RANGE(0x01800000, 0x0180001f) AM_READWRITE8(parallel_r, parallel_w, 0xff) // Parallel UART (TL16C552 CS2)
ADDRESS_MAP_END
>>>>>>> upstream/master

/*************************************
 *
 *  Machine drivers
 *
 *************************************/

<<<<<<< HEAD
static MACHINE_CONFIG_START( vegascore, vegas_state )

	/* basic machine hardware */
	MCFG_CPU_ADD("maincpu", R5000LE, SYSTEM_CLOCK*2)
	MCFG_MIPS3_ICACHE_SIZE(16384)
	MCFG_MIPS3_DCACHE_SIZE(16384)
	MCFG_MIPS3_SYSTEM_CLOCK(SYSTEM_CLOCK)
	MCFG_CPU_PROGRAM_MAP(vegas_map_8mb)

	MCFG_M48T37_ADD("timekeeper")

	MCFG_BUS_MASTER_IDE_CONTROLLER_ADD("ide", ata_devices, "hdd", NULL, true)
	MCFG_ATA_INTERFACE_IRQ_HANDLER(WRITELINE(vegas_state, ide_interrupt))
	MCFG_BUS_MASTER_IDE_CONTROLLER_SPACE("maincpu", AS_PROGRAM)
=======
static MACHINE_CONFIG_START( vegascore )

	/* basic machine hardware */
	MCFG_CPU_ADD("maincpu", R5000LE, vegas_state::SYSTEM_CLOCK*2)
	MCFG_MIPS3_ICACHE_SIZE(16384)
	MCFG_MIPS3_DCACHE_SIZE(16384)
	MCFG_MIPS3_SYSTEM_CLOCK(vegas_state::SYSTEM_CLOCK)

	// PCI Bus Devices
	MCFG_PCI_ROOT_ADD(":pci")

	MCFG_VRC5074_ADD(PCI_ID_NILE, ":maincpu")
	MCFG_VRC5074_SET_SDRAM(0, 0x00800000)
	MCFG_VRC5074_SET_CS(2, vegas_cs2_map)
	MCFG_VRC5074_SET_CS(3, vegas_cs3_map)
	MCFG_VRC5074_SET_CS(4, vegas_cs4_map)
	MCFG_VRC5074_SET_CS(5, vegas_cs5_map)
	MCFG_VRC5074_SET_CS(6, vegas_cs6_map)
	MCFG_VRC5074_SET_CS(7, vegas_cs7_map)

	MCFG_IDE_PCI_ADD(PCI_ID_IDE, 0x10950646, 0x07, 0x0)
	MCFG_IDE_PCI_IRQ_HANDLER(DEVWRITELINE(PCI_ID_NILE, vrc5074_device, pci_intr_d))
	//MCFG_IDE_PCI_SET_PIF(0x8f)

	MCFG_VOODOO_PCI_ADD(PCI_ID_VIDEO, TYPE_VOODOO_2, ":maincpu")
	MCFG_VOODOO_PCI_FBMEM(2)
	MCFG_VOODOO_PCI_TMUMEM(4, 4)
	MCFG_DEVICE_MODIFY(PCI_ID_VIDEO":voodoo")
	MCFG_VOODOO_VBLANK_CB(DEVWRITELINE(":", vegas_state, vblank_assert))

	MCFG_M48T37_ADD("timekeeper")
	MCFG_M48T37_RESET_HANDLER(WRITELINE(vegas_state, watchdog_reset))
	MCFG_M48T37_IRQ_HANDLER(WRITELINE(vegas_state, watchdog_irq))
>>>>>>> upstream/master

	MCFG_SMC91C94_ADD("ethernet")
	MCFG_SMC91C94_IRQ_CALLBACK(WRITELINE(vegas_state, ethernet_interrupt))

<<<<<<< HEAD
	MCFG_DEVICE_ADD("voodoo", VOODOO_2, STD_VOODOO_2_CLOCK)
	MCFG_VOODOO_FBMEM(2)
	MCFG_VOODOO_TMUMEM(4,4)
	MCFG_VOODOO_SCREEN_TAG("screen")
	MCFG_VOODOO_CPU_TAG("maincpu")
	MCFG_VOODOO_VBLANK_CB(WRITELINE(vegas_state,vblank_assert))

=======
>>>>>>> upstream/master
	/* video hardware */
	MCFG_SCREEN_ADD("screen", RASTER)
	MCFG_SCREEN_REFRESH_RATE(57)
	MCFG_SCREEN_SIZE(640, 480)
	MCFG_SCREEN_VISIBLE_AREA(0, 639, 0, 479)
<<<<<<< HEAD
	MCFG_SCREEN_UPDATE_DRIVER(vegas_state, screen_update_vegas)
=======
	MCFG_SCREEN_UPDATE_DEVICE(PCI_ID_VIDEO, voodoo_pci_device, screen_update)

	/* sound hardware */
>>>>>>> upstream/master
MACHINE_CONFIG_END


static MACHINE_CONFIG_DERIVED( vegas, vegascore )
MACHINE_CONFIG_END


static MACHINE_CONFIG_DERIVED( vegas250, vegascore )
	MCFG_CPU_MODIFY("maincpu")
<<<<<<< HEAD
	MCFG_CPU_CLOCK(SYSTEM_CLOCK*2.5)
MACHINE_CONFIG_END


static MACHINE_CONFIG_DERIVED( vegas32m, vegascore )
	MCFG_CPU_MODIFY("maincpu")
	MCFG_CPU_PROGRAM_MAP(vegas_map_32mb)
MACHINE_CONFIG_END


static MACHINE_CONFIG_DERIVED( vegasban, vegascore )
	MCFG_CPU_MODIFY("maincpu")
	MCFG_CPU_PROGRAM_MAP(vegas_map_32mb)

	MCFG_DEVICE_REMOVE("voodoo")
	MCFG_DEVICE_ADD("voodoo", VOODOO_BANSHEE, STD_VOODOO_BANSHEE_CLOCK)
	MCFG_VOODOO_FBMEM(16)
	MCFG_VOODOO_SCREEN_TAG("screen")
	MCFG_VOODOO_CPU_TAG("maincpu")
	MCFG_VOODOO_VBLANK_CB(WRITELINE(vegas_state,vblank_assert))
MACHINE_CONFIG_END


static MACHINE_CONFIG_DERIVED( vegasv3, vegas32m )
	MCFG_CPU_REPLACE("maincpu", RM7000LE, SYSTEM_CLOCK*2.5)
	MCFG_MIPS3_ICACHE_SIZE(16384)
	MCFG_MIPS3_DCACHE_SIZE(16384)
	MCFG_MIPS3_SYSTEM_CLOCK(SYSTEM_CLOCK)
	MCFG_CPU_PROGRAM_MAP(vegas_map_8mb)

	MCFG_DEVICE_REMOVE("voodoo")
	MCFG_DEVICE_ADD("voodoo", VOODOO_3, STD_VOODOO_3_CLOCK)
	MCFG_VOODOO_FBMEM(16)
	MCFG_VOODOO_SCREEN_TAG("screen")
	MCFG_VOODOO_CPU_TAG("maincpu")
	MCFG_VOODOO_VBLANK_CB(WRITELINE(vegas_state,vblank_assert))
=======
	MCFG_CPU_CLOCK(vegas_state::SYSTEM_CLOCK*2.5)
MACHINE_CONFIG_END


static MACHINE_CONFIG_DERIVED( vegas32m, vegas250)
	MCFG_DEVICE_MODIFY(PCI_ID_NILE)
	MCFG_VRC5074_SET_SDRAM(0, 0x02000000)
MACHINE_CONFIG_END


static MACHINE_CONFIG_DERIVED( vegasban, vegas32m)
	// Short term hack to get nbashowt, nbanfl, nbagold to boot.
	// Probably due to CRTC registers not used for timing in voodoo
	MCFG_SCREEN_MODIFY("screen")
	MCFG_SCREEN_REFRESH_RATE(120)

	MCFG_DEVICE_REMOVE(PCI_ID_VIDEO)
	MCFG_VOODOO_PCI_ADD(PCI_ID_VIDEO, TYPE_VOODOO_BANSHEE, ":maincpu")
	MCFG_VOODOO_PCI_FBMEM(16)
	MCFG_DEVICE_MODIFY(PCI_ID_VIDEO":voodoo")
	MCFG_VOODOO_VBLANK_CB(DEVWRITELINE(":", vegas_state, vblank_assert))
MACHINE_CONFIG_END


static MACHINE_CONFIG_DERIVED( vegasv3, vegas32m)
	MCFG_CPU_REPLACE("maincpu", RM7000LE, vegas_state::SYSTEM_CLOCK*2.5)
	MCFG_MIPS3_ICACHE_SIZE(16384)
	MCFG_MIPS3_DCACHE_SIZE(16384)
	MCFG_MIPS3_SYSTEM_CLOCK(vegas_state::SYSTEM_CLOCK)

	// Short term hack to get cartfury to boot.
	// Probably due to CRTC registers not used for timing in voodoo
	MCFG_SCREEN_MODIFY("screen")
	MCFG_SCREEN_REFRESH_RATE(120)

	MCFG_DEVICE_REMOVE(PCI_ID_VIDEO)
	MCFG_VOODOO_PCI_ADD(PCI_ID_VIDEO, TYPE_VOODOO_3, ":maincpu")
	MCFG_VOODOO_PCI_FBMEM(16)
	MCFG_DEVICE_MODIFY(PCI_ID_VIDEO":voodoo")
	MCFG_VOODOO_VBLANK_CB(DEVWRITELINE(":", vegas_state, vblank_assert))
>>>>>>> upstream/master
MACHINE_CONFIG_END


static MACHINE_CONFIG_DERIVED( denver, vegascore )
<<<<<<< HEAD
	MCFG_CPU_REPLACE("maincpu", RM7000LE, SYSTEM_CLOCK*2.5)
	MCFG_MIPS3_ICACHE_SIZE(16384)
	MCFG_MIPS3_DCACHE_SIZE(16384)
	MCFG_MIPS3_SYSTEM_CLOCK(SYSTEM_CLOCK)
	MCFG_CPU_PROGRAM_MAP(vegas_map_32mb)

	MCFG_DEVICE_REMOVE("voodoo")
	MCFG_DEVICE_ADD("voodoo", VOODOO_3, STD_VOODOO_3_CLOCK)
	MCFG_VOODOO_FBMEM(16)
	MCFG_VOODOO_SCREEN_TAG("screen")
	MCFG_VOODOO_CPU_TAG("maincpu")
	MCFG_VOODOO_VBLANK_CB(WRITELINE(vegas_state,vblank_assert))
=======
	MCFG_CPU_REPLACE("maincpu", RM7000LE, vegas_state::SYSTEM_CLOCK*2.5)
	MCFG_MIPS3_ICACHE_SIZE(16384)
	MCFG_MIPS3_DCACHE_SIZE(16384)
	MCFG_MIPS3_SYSTEM_CLOCK(vegas_state::SYSTEM_CLOCK)

	MCFG_DEVICE_MODIFY(PCI_ID_NILE)
	MCFG_VRC5074_SET_SDRAM(0, 0x02000000)
	MCFG_VRC5074_SET_CS(8, vegas_cs8_map)

	MCFG_DEVICE_REMOVE(PCI_ID_VIDEO)
	MCFG_VOODOO_PCI_ADD(PCI_ID_VIDEO, TYPE_VOODOO_3, ":maincpu")
	MCFG_VOODOO_PCI_FBMEM(16)
	MCFG_DEVICE_MODIFY(PCI_ID_VIDEO":voodoo")
	MCFG_VOODOO_VBLANK_CB(DEVWRITELINE(":", vegas_state, vblank_assert))

	// TL16C552 UART
	MCFG_DEVICE_ADD("uart1", NS16550, vegas_state::SYSTEM_CLOCK / 12)
	MCFG_INS8250_OUT_TX_CB(DEVWRITELINE("com1", rs232_port_device, write_txd))
	MCFG_INS8250_OUT_DTR_CB(DEVWRITELINE("com1", rs232_port_device, write_dtr))
	MCFG_INS8250_OUT_RTS_CB(DEVWRITELINE("com1", rs232_port_device, write_rts))
	MCFG_INS8250_OUT_INT_CB(DEVWRITELINE(":", vegas_state, uart1_irq_cb))

	MCFG_DEVICE_ADD("uart2", NS16550, vegas_state::SYSTEM_CLOCK / 12)
	MCFG_INS8250_OUT_TX_CB(DEVWRITELINE("com2", rs232_port_device, write_txd))
	MCFG_INS8250_OUT_DTR_CB(DEVWRITELINE("com2", rs232_port_device, write_dtr))
	MCFG_INS8250_OUT_RTS_CB(DEVWRITELINE("com2", rs232_port_device, write_rts))
	MCFG_INS8250_OUT_INT_CB(DEVWRITELINE(":", vegas_state, uart2_irq_cb))

	MCFG_RS232_PORT_ADD("com1", default_rs232_devices, nullptr)
	MCFG_RS232_RXD_HANDLER(DEVWRITELINE("uart1", ins8250_uart_device, rx_w))
	MCFG_RS232_DCD_HANDLER(DEVWRITELINE("uart1", ins8250_uart_device, dcd_w))
	MCFG_RS232_DSR_HANDLER(DEVWRITELINE("uart1", ins8250_uart_device, dsr_w))
	MCFG_RS232_RI_HANDLER(DEVWRITELINE("uart1", ins8250_uart_device, ri_w))
	MCFG_RS232_CTS_HANDLER(DEVWRITELINE("uart1", ins8250_uart_device, cts_w))

	MCFG_RS232_PORT_ADD("com2", default_rs232_devices, nullptr)
	MCFG_RS232_RXD_HANDLER(DEVWRITELINE("uart2", ins8250_uart_device, rx_w))
	MCFG_RS232_DCD_HANDLER(DEVWRITELINE("uart2", ins8250_uart_device, dcd_w))
	MCFG_RS232_DSR_HANDLER(DEVWRITELINE("uart2", ins8250_uart_device, dsr_w))
	MCFG_RS232_RI_HANDLER(DEVWRITELINE("uart2", ins8250_uart_device, ri_w))
	MCFG_RS232_CTS_HANDLER(DEVWRITELINE("uart2", ins8250_uart_device, cts_w))

>>>>>>> upstream/master
MACHINE_CONFIG_END

// Per driver configs

static MACHINE_CONFIG_DERIVED( gauntleg, vegas )
	MCFG_DEVICE_ADD("dcs", DCS2_AUDIO_2104, 0)
	MCFG_DCS2_AUDIO_DRAM_IN_MB(4)
	MCFG_DCS2_AUDIO_POLLING_OFFSET(0x0b5d)

	MCFG_DEVICE_ADD("ioasic", MIDWAY_IOASIC, 0)
	MCFG_MIDWAY_IOASIC_SHUFFLE(MIDWAY_IOASIC_CALSPEED)
	MCFG_MIDWAY_IOASIC_UPPER(340/* 340=39", 322=27", others? */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
	MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
MACHINE_CONFIG_END

static MACHINE_CONFIG_DERIVED( gauntdl, vegas )
	MCFG_DEVICE_ADD("dcs", DCS2_AUDIO_2104, 0)
	MCFG_DCS2_AUDIO_DRAM_IN_MB(4)
	MCFG_DCS2_AUDIO_POLLING_OFFSET(0x0b5d)

	MCFG_DEVICE_ADD("ioasic", MIDWAY_IOASIC, 0)
	MCFG_MIDWAY_IOASIC_SHUFFLE(MIDWAY_IOASIC_GAUNTDL)
	MCFG_MIDWAY_IOASIC_UPPER(346/* 347, others? */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
	MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
MACHINE_CONFIG_END

static MACHINE_CONFIG_DERIVED( warfa, vegas250 )
	MCFG_DEVICE_ADD("dcs", DCS2_AUDIO_2104, 0)
	MCFG_DCS2_AUDIO_DRAM_IN_MB(4)
	MCFG_DCS2_AUDIO_POLLING_OFFSET(0x0b5d)

	MCFG_DEVICE_ADD("ioasic", MIDWAY_IOASIC, 0)
	MCFG_MIDWAY_IOASIC_SHUFFLE(MIDWAY_IOASIC_MACE)
	MCFG_MIDWAY_IOASIC_UPPER(337/* others? */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
	MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
MACHINE_CONFIG_END

static MACHINE_CONFIG_DERIVED( tenthdeg, vegas )
<<<<<<< HEAD
	MCFG_DEVICE_ADD("dcs", DCS2_AUDIO_2104, 0)
=======
	MCFG_DEVICE_ADD("dcs", DCS2_AUDIO_2115, 0)
>>>>>>> upstream/master
	MCFG_DCS2_AUDIO_DRAM_IN_MB(4)
	MCFG_DCS2_AUDIO_POLLING_OFFSET(0x0afb)

	MCFG_DEVICE_ADD("ioasic", MIDWAY_IOASIC, 0)
	MCFG_MIDWAY_IOASIC_SHUFFLE(MIDWAY_IOASIC_GAUNTDL)
	MCFG_MIDWAY_IOASIC_UPPER(330/* others? */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
	MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
MACHINE_CONFIG_END

static MACHINE_CONFIG_DERIVED( roadburn, vegas32m )
	MCFG_DEVICE_ADD("dcs", DCS2_AUDIO_DSIO, 0)
	MCFG_DCS2_AUDIO_DRAM_IN_MB(4)
<<<<<<< HEAD
	MCFG_DCS2_AUDIO_POLLING_OFFSET(0) /* no place to hook :-( */
=======
	MCFG_DCS2_AUDIO_POLLING_OFFSET(0x200a)
>>>>>>> upstream/master

	MCFG_DEVICE_ADD("ioasic", MIDWAY_IOASIC, 0)
	MCFG_MIDWAY_IOASIC_SHUFFLE(MIDWAY_IOASIC_STANDARD)
	MCFG_MIDWAY_IOASIC_UPPER(325/* others? */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
	MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
MACHINE_CONFIG_END

static MACHINE_CONFIG_DERIVED( nbashowt, vegasban )
	MCFG_DEVICE_ADD("dcs", DCS2_AUDIO_2104, 0)
	MCFG_DCS2_AUDIO_DRAM_IN_MB(4)
<<<<<<< HEAD

	MCFG_DEVICE_ADD("ioasic", MIDWAY_IOASIC, 0)
	MCFG_MIDWAY_IOASIC_SHUFFLE(MIDWAY_IOASIC_MACE)
	MCFG_MIDWAY_IOASIC_UPPER(528/* or 478 or 487 */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
	MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
=======
	MCFG_DCS2_AUDIO_POLLING_OFFSET(0x0b5d)

	MCFG_DEVICE_ADD("ioasic", MIDWAY_IOASIC, 0)
	MCFG_MIDWAY_IOASIC_SHUFFLE(MIDWAY_IOASIC_MACE)
	// 528 494 478 development pic, 487 NBA
	MCFG_MIDWAY_IOASIC_UPPER(487/* or 478 or 487 */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
	//MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
	MCFG_MIDWAY_IOASIC_AUX_OUT_CB(WRITE32(vegas_state, i40_w))
>>>>>>> upstream/master
MACHINE_CONFIG_END

static MACHINE_CONFIG_DERIVED( nbanfl, vegasban )
	MCFG_DEVICE_ADD("dcs", DCS2_AUDIO_2104, 0)
	MCFG_DCS2_AUDIO_DRAM_IN_MB(4)

	MCFG_DEVICE_ADD("ioasic", MIDWAY_IOASIC, 0)
	MCFG_MIDWAY_IOASIC_SHUFFLE(MIDWAY_IOASIC_BLITZ99)
	MCFG_MIDWAY_IOASIC_UPPER(498/* or 478 or 487 */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
<<<<<<< HEAD
	MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
=======
	//MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
	MCFG_MIDWAY_IOASIC_AUX_OUT_CB(WRITE32(vegas_state, i40_w))
MACHINE_CONFIG_END

static MACHINE_CONFIG_DERIVED( nbagold, vegasban)
	MCFG_DEVICE_ADD("dcs", DCS2_AUDIO_2104, 0)
	MCFG_DCS2_AUDIO_DRAM_IN_MB(4)

	MCFG_DEVICE_ADD("ioasic", MIDWAY_IOASIC, 0)
	MCFG_MIDWAY_IOASIC_SHUFFLE(MIDWAY_IOASIC_GAUNTDL)
	MCFG_MIDWAY_IOASIC_UPPER( 494 /* 494 109 ??? */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
	//MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
	MCFG_MIDWAY_IOASIC_AUX_OUT_CB(WRITE32(vegas_state, i40_w))
>>>>>>> upstream/master
MACHINE_CONFIG_END

static MACHINE_CONFIG_DERIVED( sf2049 , denver )
	MCFG_DEVICE_ADD("dcs", DCS2_AUDIO_DENVER, 0)
<<<<<<< HEAD
	MCFG_DCS2_AUDIO_DRAM_IN_MB(8)
=======
	MCFG_DCS2_AUDIO_DRAM_IN_MB(16)
	MCFG_DCS2_AUDIO_POLLING_OFFSET(0x200d)
>>>>>>> upstream/master

	MCFG_DEVICE_ADD("ioasic", MIDWAY_IOASIC, 0)
	MCFG_MIDWAY_IOASIC_SHUFFLE(MIDWAY_IOASIC_STANDARD)
	MCFG_MIDWAY_IOASIC_UPPER(336/* others? */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
	MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
<<<<<<< HEAD
=======
	MCFG_MIDWAY_IOASIC_AUX_OUT_CB(WRITE32(vegas_state, wheel_board_w))
>>>>>>> upstream/master
MACHINE_CONFIG_END

static MACHINE_CONFIG_DERIVED( sf2049se, denver )
	MCFG_DEVICE_ADD("dcs", DCS2_AUDIO_DENVER, 0)
<<<<<<< HEAD
	MCFG_DCS2_AUDIO_DRAM_IN_MB(8)

	MCFG_DEVICE_ADD("ioasic", MIDWAY_IOASIC, 0)
	MCFG_MIDWAY_IOASIC_SHUFFLE(MIDWAY_IOASIC_SFRUSHRK)
	MCFG_MIDWAY_IOASIC_UPPER(336/* others? */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
	MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
=======
	MCFG_DCS2_AUDIO_DRAM_IN_MB(16)

	MCFG_DEVICE_ADD("ioasic", MIDWAY_IOASIC, 0)
	MCFG_MIDWAY_IOASIC_SHUFFLE(MIDWAY_IOASIC_SFRUSHRK)
	MCFG_MIDWAY_IOASIC_UPPER(352/*352 336 others? */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
	MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
	MCFG_MIDWAY_IOASIC_AUX_OUT_CB(WRITE32(vegas_state, wheel_board_w))
>>>>>>> upstream/master
MACHINE_CONFIG_END

static MACHINE_CONFIG_DERIVED( sf2049te, denver )
	MCFG_DEVICE_ADD("dcs", DCS2_AUDIO_DENVER, 0)
<<<<<<< HEAD
	MCFG_DCS2_AUDIO_DRAM_IN_MB(8)

	MCFG_DEVICE_ADD("ioasic", MIDWAY_IOASIC, 0)
	MCFG_MIDWAY_IOASIC_SHUFFLE(MIDWAY_IOASIC_SFRUSHRK)
	MCFG_MIDWAY_IOASIC_UPPER(348/* others? */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
	MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
=======
	MCFG_DCS2_AUDIO_DRAM_IN_MB(16)

	MCFG_DEVICE_ADD("ioasic", MIDWAY_IOASIC, 0)
	MCFG_MIDWAY_IOASIC_SHUFFLE(MIDWAY_IOASIC_SFRUSHRK)
	MCFG_MIDWAY_IOASIC_UPPER(348/* 348 others? */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
	MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
	MCFG_MIDWAY_IOASIC_AUX_OUT_CB(WRITE32(vegas_state, wheel_board_w))
>>>>>>> upstream/master
MACHINE_CONFIG_END

static MACHINE_CONFIG_DERIVED( cartfury, vegasv3 )
	MCFG_DEVICE_ADD("dcs", DCS2_AUDIO_2104, 0)
	MCFG_DCS2_AUDIO_DRAM_IN_MB(4)

	MCFG_DEVICE_ADD("ioasic", MIDWAY_IOASIC, 0)
	MCFG_MIDWAY_IOASIC_SHUFFLE(MIDWAY_IOASIC_CARNEVIL)
<<<<<<< HEAD
	MCFG_MIDWAY_IOASIC_UPPER(495/* others? */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
	MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
=======
	// 433, 495 Development PIC
	MCFG_MIDWAY_IOASIC_UPPER(495/*433,  495 others? */)
	MCFG_MIDWAY_IOASIC_YEAR_OFFS(80)
	MCFG_MIDWAY_IOASIC_IRQ_CALLBACK(WRITELINE(vegas_state, ioasic_irq))
	//MCFG_MIDWAY_IOASIC_AUTO_ACK(1)
>>>>>>> upstream/master
MACHINE_CONFIG_END


/*************************************
 *
 *  ROM definitions
 *
 *************************************/

	// there is a socket next to the main bios roms for updates, this is what the update region is.


ROM_START( gauntleg )
<<<<<<< HEAD
	ROM_REGION32_LE( 0x80000, "user1", 0 )
	ROM_LOAD( "legend15.bin", 0x000000, 0x80000, CRC(a8372d70) SHA1(d8cd4fd4d7007ee38bb58b5a818d0f83043d5a48) ) // EPROM Boot code. Version: Nov 17 1998 19:18:28 / 1.5 Nov 17 1998 19:21:49

	ROM_REGION32_LE( 0x100000, "update", ROMREGION_ERASEFF )

	DISK_REGION( "ide:0:hdd:image" )    /* Guts 1.5 1/14/1999 Game 1/14/1999 */
=======
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )
	ROM_LOAD( "legend15.bin", 0x000000, 0x80000, CRC(a8372d70) SHA1(d8cd4fd4d7007ee38bb58b5a818d0f83043d5a48) ) // EPROM Boot code. Version: Nov 17 1998 19:18:28 / 1.5 Nov 17 1998 19:21:49

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )

	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )    /* Guts 1.5 1/14/1999 Game 1/14/1999 */
>>>>>>> upstream/master
	DISK_IMAGE( "gauntleg", 0, SHA1(66eb70e2fba574a7abe54be8bd45310654b24b08) )

	ROM_REGION16_LE( 0x10000, "dcs", 0 )    /* Vegas SIO boot ROM */
	ROM_LOAD16_BYTE( "vegassio.bin", 0x000000, 0x8000, CRC(d1470e23) SHA1(f6e8405cfa604528c0224401bc374a6df9caccef) )
ROM_END


ROM_START( gauntleg12 )
<<<<<<< HEAD
	ROM_REGION32_LE( 0x80000, "user1", 0 )
	ROM_LOAD( "legend13.bin", 0x000000, 0x80000, CRC(34674c5f) SHA1(92ec1779f3ab32944cbd953b6e1889503a57794b) ) //  EPROM Boot code. Version: Sep 25 1998 18:34:43 / 1.3 Sep 25 1998 18:33:45
	ROM_LOAD( "legend14.bin", 0x000000, 0x80000, CRC(66869402) SHA1(bf470e0b9198b80f8baf8b9432a7e1df8c7d18ca) ) //  EPROM Boot code. Version: Oct 30 1998 17:48:21 / 1.4 Oct 30 1998 17:44:29

	ROM_REGION32_LE( 0x100000, "update", ROMREGION_ERASEFF )
=======
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )
	ROM_LOAD( "legend13.bin", 0x000000, 0x80000, CRC(34674c5f) SHA1(92ec1779f3ab32944cbd953b6e1889503a57794b) ) //  EPROM Boot code. Version: Sep 25 1998 18:34:43 / 1.3 Sep 25 1998 18:33:45
	ROM_LOAD( "legend14.bin", 0x000000, 0x80000, CRC(66869402) SHA1(bf470e0b9198b80f8baf8b9432a7e1df8c7d18ca) ) //  EPROM Boot code. Version: Oct 30 1998 17:48:21 / 1.4 Oct 30 1998 17:44:29

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )
>>>>>>> upstream/master
	ROM_SYSTEM_BIOS( 0, "noupdate",       "No Update Rom" )

	ROM_SYSTEM_BIOS( 1, "up16_1",       "Disk Update 1.2 to 1.6 Step 1 of 3" )
	ROMX_LOAD("12to16.1.bin", 0x000000, 0x100000, CRC(253c6bf2) SHA1(5e129576afe2bc4c638242e010735655d269a747), ROM_BIOS(2))
	ROM_SYSTEM_BIOS( 2, "up16_2",       "Disk Update 1.2 to 1.6 Step 2 of 3" )
	ROMX_LOAD("12to16.2.bin", 0x000000, 0x100000, CRC(15b1fe78) SHA1(532c4937b55befcc3a8cb25b0282d63e206fba47), ROM_BIOS(3))
	ROM_SYSTEM_BIOS( 3, "up16_3",       "Disk Update 1.2 to 1.6 Step 3 of 3" )
	ROMX_LOAD("12to16.3.bin", 0x000000, 0x100000, CRC(1027e54f) SHA1(a841f5cc5b022ddfaf70c97a64d1582f0a2ca70e), ROM_BIOS(4))



<<<<<<< HEAD
	DISK_REGION( "ide:0:hdd:image" )    /* Guts 1.4 10/22/1998 Main 10/23/1998 */
=======
	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )    /* Guts 1.4 10/22/1998 Main 10/23/1998 */
>>>>>>> upstream/master
	DISK_IMAGE( "gauntl12", 0, SHA1(62917fbd692d004bc391287349041ebe669385cf) ) // compressed with -chs 4969,16,63 (which is apparently correct for a Quantum FIREBALL 2.5 GB and allows the update program to work)

	ROM_REGION16_LE( 0x10000, "dcs", 0 )    /* Vegas SIO boot ROM */
	ROM_LOAD16_BYTE( "vegassio.bin", 0x000000, 0x8000, CRC(d1470e23) SHA1(f6e8405cfa604528c0224401bc374a6df9caccef) )
ROM_END


ROM_START( gauntdl )
<<<<<<< HEAD
	ROM_REGION32_LE( 0x80000, "user1", 0 )  /* EPROM 1.7 12/14/1999 */
	ROM_LOAD( "gauntdl.bin", 0x000000, 0x80000, CRC(3d631518) SHA1(d7f5a3bc109a19c9c7a711d607ff87e11868b536) )

	ROM_REGION32_LE( 0x100000, "update", ROMREGION_ERASEFF )


	DISK_REGION( "ide:0:hdd:image" )    /* Guts: 1.9 3/17/2000 Game 5/9/2000 */
=======
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )  /* EPROM 1.7 12/14/1999 */
	ROM_LOAD( "gauntdl.bin", 0x000000, 0x80000, CRC(3d631518) SHA1(d7f5a3bc109a19c9c7a711d607ff87e11868b536) )

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )


	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )    /* Guts: 1.9 3/17/2000 Game 5/9/2000 */
>>>>>>> upstream/master
	DISK_IMAGE( "gauntdl", 0, SHA1(ba3af48171e727c2f7232c06dcf8411cbcf14de8) )

	ROM_REGION16_LE( 0x10000, "dcs", 0 )    /* Vegas SIO boot ROM */
	ROM_LOAD16_BYTE( "vegassio.bin", 0x000000, 0x8000, CRC(d1470e23) SHA1(f6e8405cfa604528c0224401bc374a6df9caccef) )
ROM_END


ROM_START( gauntdl24 )
<<<<<<< HEAD
	ROM_REGION32_LE( 0x80000, "user1", 0 )  /* EPROM 1.7 12/14/1999 */
	ROM_LOAD( "gauntdl.bin", 0x000000, 0x80000, CRC(3d631518) SHA1(d7f5a3bc109a19c9c7a711d607ff87e11868b536) )

	ROM_REGION32_LE( 0x100000, "update", ROMREGION_ERASEFF )


	DISK_REGION( "ide:0:hdd:image" )    /* Guts: 1.9 3/17/2000 Game 3/19/2000 */
=======
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )  /* EPROM 1.7 12/14/1999 */
	ROM_LOAD( "gauntdl.bin", 0x000000, 0x80000, CRC(3d631518) SHA1(d7f5a3bc109a19c9c7a711d607ff87e11868b536) )

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )


	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )    /* Guts: 1.9 3/17/2000 Game 3/19/2000 */
>>>>>>> upstream/master
	DISK_IMAGE( "gauntd24", 0, SHA1(3e055794d23d62680732e906cfaf9154765de698) )

	ROM_REGION16_LE( 0x10000, "dcs", 0 )    /* Vegas SIO boot ROM */
	ROM_LOAD16_BYTE( "vegassio.bin", 0x000000, 0x8000, CRC(d1470e23) SHA1(f6e8405cfa604528c0224401bc374a6df9caccef) )
ROM_END


ROM_START( warfa )
<<<<<<< HEAD
	ROM_REGION32_LE( 0x80000, "user1", 0 )  /* EPROM 1.9 3/25/1999 */
	ROM_LOAD( "warboot.v19", 0x000000, 0x80000, CRC(b0c095cd) SHA1(d3b8cccdca83f0ecb49aa7993864cfdaa4e5c6f0) )

	ROM_REGION32_LE( 0x100000, "update", ROMREGION_ERASEFF )


	DISK_REGION( "ide:0:hdd:image" )    /* Guts 1.3 4/20/1999 Game 4/20/1999 */
=======
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )  /* EPROM 1.9 3/25/1999 */
	ROM_LOAD( "warboot.v19", 0x000000, 0x80000, CRC(b0c095cd) SHA1(d3b8cccdca83f0ecb49aa7993864cfdaa4e5c6f0) )

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )


	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )    /* Guts 1.3 4/20/1999 Game 4/20/1999 */
>>>>>>> upstream/master
	DISK_IMAGE( "warfa", 0, SHA1(87f8a8878cd6be716dbd6c68fb1bc7f564ede484) )

	ROM_REGION16_LE( 0x10000, "dcs", 0 )    /* Vegas SIO boot ROM */
	ROM_LOAD16_BYTE( "warsnd.106", 0x000000, 0x8000, CRC(d1470e23) SHA1(f6e8405cfa604528c0224401bc374a6df9caccef) )
ROM_END

ROM_START( warfaa )
<<<<<<< HEAD
	ROM_REGION32_LE( 0x80000, "user1", 0 )  /* EPROM 1.6 Jan 14 1999 */
	ROM_LOAD( "warboot.v16", 0x000000, 0x80000, CRC(1c44b3a3) SHA1(e81c15d7c9bc19078787d39c7f5e48eab003c5f4) )

	ROM_REGION32_LE( 0x100000, "update", ROMREGION_ERASEFF )


	DISK_REGION( "ide:0:hdd:image" )    /* GUTS 1.1 Mar 16 1999, GAME Mar 16 1999 */
=======
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )  /* EPROM 1.6 Jan 14 1999 */
	ROM_LOAD( "warboot.v16", 0x000000, 0x80000, CRC(1c44b3a3) SHA1(e81c15d7c9bc19078787d39c7f5e48eab003c5f4) )

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )


	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )    /* GUTS 1.1 Mar 16 1999, GAME Mar 16 1999 */
>>>>>>> upstream/master
	DISK_IMAGE( "warfaa", 0, SHA1(b443ba68003f8492e5c20156e0d3091fe51e9224) )

	ROM_REGION16_LE( 0x10000, "dcs", 0 )    /* Vegas SIO boot ROM */
	ROM_LOAD16_BYTE( "warsnd.106", 0x000000, 0x8000, CRC(d1470e23) SHA1(f6e8405cfa604528c0224401bc374a6df9caccef) )
ROM_END

<<<<<<< HEAD

ROM_START( tenthdeg )
	ROM_REGION32_LE( 0x80000, "user1", 0 )
	ROM_LOAD( "tenthdeg.bio", 0x000000, 0x80000, CRC(1cd2191b) SHA1(a40c48f3d6a9e2760cec809a79a35abe762da9ce) )

	ROM_REGION32_LE( 0x100000, "update", ROMREGION_ERASEFF )


	DISK_REGION( "ide:0:hdd:image" )    /* Guts 5/26/1998 Main 8/25/1998 */
=======
ROM_START( warfab )
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )  // test: EPROM 1.3 Apr 7 1999
	// label: WAR 42CE / BOOT V1.9 / PROG V1.6
	ROM_LOAD( "war42ce.bin", 0x000000, 0x80000, CRC(1a6e7f59) SHA1(0d8b4ce1e4b1132689796c4374aa54447b9a3369) )

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )

	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )    // test: Guts 1.3 Apr7 1999 Game 1.3 Apr7 1999
	// V1.5
	DISK_IMAGE( "warfa15", 0, SHA1(bd538bf2f6a245545dae4ea97c433bb3f7d4394e) )

	ROM_REGION16_LE( 0x10000, "dcs", 0 )    /* Vegas SIO boot ROM */
	ROM_LOAD16_BYTE( "warsnd.106", 0x000000, 0x8000, CRC(d1470e23) SHA1(f6e8405cfa604528c0224401bc374a6df9caccef) )
ROM_END

ROM_START( warfac )
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )  // test: EPROM 1.91 Apr 13 1999
	ROM_LOAD( "war__upgrade__ver_1.91.u27", 0x000000, 0x80000, CRC(4d8fe0f8) SHA1(b809d29760ff229200509ba6751d8255faca7082) )

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )

	// required HDD image version is guess
	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )    /* Guts 1.3 4/20/1999 Game 4/20/1999 */
	DISK_IMAGE( "warfa", 0, SHA1(87f8a8878cd6be716dbd6c68fb1bc7f564ede484) )

	ROM_REGION16_LE( 0x10000, "dcs", 0 )    /* Vegas SIO boot ROM */
	ROM_LOAD16_BYTE( "warsnd.106", 0x000000, 0x8000, CRC(d1470e23) SHA1(f6e8405cfa604528c0224401bc374a6df9caccef) )
ROM_END

ROM_START( tenthdeg )
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )
	ROM_LOAD( "tenthdeg.bio", 0x000000, 0x80000, CRC(1cd2191b) SHA1(a40c48f3d6a9e2760cec809a79a35abe762da9ce) )

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )


	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )    /* Guts 5/26/1998 Main 8/25/1998 */
>>>>>>> upstream/master
	DISK_IMAGE( "tenthdeg", 0, SHA1(41a1a045a2d118cf6235be2cc40bf16dbb8be5d1) )

	ROM_REGION16_LE( 0x10000, "dcs", 0 )    /* Vegas SIO boot ROM */
	ROM_LOAD16_BYTE( "tenthdeg.snd", 0x000000, 0x8000, CRC(1c75c1c1) SHA1(02ac1419b0fd4acc3f39676e7dce879e926d998b) )
ROM_END


<<<<<<< HEAD
ROM_START( roadburn )
	ROM_REGION32_LE( 0x80000, "user1", 0 )  /* EPROM 2.6 4/22/1999 */
	ROM_LOAD( "rbmain.bin", 0x000000, 0x80000, CRC(060e1aa8) SHA1(2a1027d209f87249fe143500e721dfde7fb5f3bc) )

	ROM_REGION32_LE( 0x100000, "update", ROMREGION_ERASEFF )


	DISK_REGION( "ide:0:hdd:image" )    /* Guts 4/22/1999 Game 4/22/1999 */
=======
ROM_START( roadburn ) /* version 1.04 - verified on hardware */
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )  /* EPROM 2.6 4/22/1999 */
	ROM_LOAD( "rbmain.bin", 0x000000, 0x80000, CRC(060e1aa8) SHA1(2a1027d209f87249fe143500e721dfde7fb5f3bc) )

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )


	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )    /* Guts 5/19/1999 Game 5/19/1999 */
	DISK_IMAGE( "ROAD BURNERS V1.04", 0, SHA1(30567241c000ee572a9cfb1b080c02a51a2b12d2) )
ROM_END

ROM_START( roadburn1 ) /* version 1.0 - verified on hardware */
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )  /* EPROM 2.6 4/22/1999 */
	ROM_LOAD( "rbmain.bin", 0x000000, 0x80000, CRC(060e1aa8) SHA1(2a1027d209f87249fe143500e721dfde7fb5f3bc) )

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )


	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )    /* Guts 4/22/1999 Game 4/22/1999 */
>>>>>>> upstream/master
	DISK_IMAGE( "roadburn", 0, SHA1(a62870cceafa6357d7d3505aca250c3f16087566) )
ROM_END


ROM_START( nbashowt )
<<<<<<< HEAD
	ROM_REGION32_LE( 0x80000, "user1", 0 )
	ROM_LOAD( "showtime_mar15_1999.u27", 0x000000, 0x80000, CRC(ff5d620d) SHA1(8f07567929f40a2269a42495dfa9dd5edef688fe) ) // 16:09:14 Mar 15 1999 BIOS FOR SHOWTIME USING BANSHEE / 16:09:01 Mar 15 1999. POST FOR SHOWTIME USING BANSHEE

	ROM_REGION32_LE( 0x100000, "update", ROMREGION_ERASEFF )


	DISK_REGION( "ide:0:hdd:image" )
=======
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )
	ROM_LOAD( "showtime_mar15_1999.u27", 0x000000, 0x80000, CRC(ff5d620d) SHA1(8f07567929f40a2269a42495dfa9dd5edef688fe) ) // 16:09:14 Mar 15 1999 BIOS FOR SHOWTIME USING BANSHEE / 16:09:01 Mar 15 1999. POST FOR SHOWTIME USING BANSHEE

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )


	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )
>>>>>>> upstream/master
	// various strings from this image
	// SHOWTIME REV 2.0
	// BUILD DATE: Apr 25 1999 (diag.exe?)
	// BUILD DATE: Apr 21 1999 (game?)
	DISK_IMAGE( "nbashowt", 0, SHA1(f7c56bc3dcbebc434de58034986179ae01127f87) )

	ROM_REGION16_LE( 0x10000, "dcs", 0 )    /* Vegas SIO boot ROM */
	ROM_LOAD16_BYTE( "vegassio.bin", 0x000000, 0x8000, CRC(d1470e23) SHA1(f6e8405cfa604528c0224401bc374a6df9caccef) )
ROM_END


ROM_START( nbanfl )
<<<<<<< HEAD
	ROM_REGION32_LE( 0x80000, "user1", 0 )
	ROM_LOAD( "blitz00_sep22_1999.u27", 0x000000, 0x80000, CRC(6a9bd382) SHA1(18b942df6af86ea944c24166dbe88148334eaff9) ) // 16:00:32 Sep 22 1999 BIOS FOR BLITZ00 USING BANSHEE / 16:00:26 Sep 22 1999 POST FOR BLITZ00 USING BANSHEE
//  ROM_LOAD( "bootnflnba.bin", 0x000000, 0x80000, CRC(3def7053) SHA1(8f07567929f40a2269a42495dfa9dd5edef688fe) ) // 1 byte different to above (0x51b95 is 0x1b instead of 0x18)
	ROM_LOAD( "blitz00_nov30_1999.u27", 0x000000, 0x80000, CRC(4242bf14) SHA1(c1fcec67d7463df5f41afc89f22c3b4484279534) ) // 15:10:49 Nov 30 1999 BIOS FOR BLITZ00 USING BANSHEE / 15:10:43 Nov 30 1999 POST FOR BLITZ00 USING BANSHEE

	ROM_REGION32_LE( 0x100000, "update", ROMREGION_ERASEFF )


	DISK_REGION( "ide:0:hdd:image" )
=======
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )
	ROM_LOAD( "blitz00_sep22_1999.u27", 0x000000, 0x80000, CRC(6a9bd382) SHA1(18b942df6af86ea944c24166dbe88148334eaff9) ) // 16:00:32 Sep 22 1999 BIOS FOR BLITZ00 USING BANSHEE / 16:00:26 Sep 22 1999 POST FOR BLITZ00 USING BANSHEE
//  ROM_LOAD( "bootnflnba.bin", 0x000000, 0x80000, CRC(3def7053) SHA1(8f07567929f40a2269a42495dfa9dd5edef688fe) ) // 1 byte different to above (0x51b95 is 0x1b instead of 0x18)
	// Bad dump: First 3 bytes of reset vector (0x0) are FF's.  Reset vector is fixed in driver init.
	ROM_LOAD( "blitz00_nov30_1999.u27", 0x000000, 0x80000, CRC(4242bf14) SHA1(c1fcec67d7463df5f41afc89f22c3b4484279534) BAD_DUMP) // 15:10:49 Nov 30 1999 BIOS FOR BLITZ00 USING BANSHEE / 15:10:43 Nov 30 1999 POST FOR BLITZ00 USING BANSHEE

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )


	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )
>>>>>>> upstream/master
	// various strings from this image
	//NBA SHOWTIME 2.1
	//BUILD DATE: Sep 22 1999 (diag.exe?)
	//BUILD DATE: Sep 21 1999 (game?)
	DISK_IMAGE( "nbanfl", 0, SHA1(f60c627f85f1bf58f2ea674063736a1e516e7e9e) )

	ROM_REGION16_LE( 0x10000, "dcs", 0 )    /* Vegas SIO boot ROM */
	ROM_LOAD16_BYTE( "vegassio.bin", 0x000000, 0x8000, CRC(d1470e23) SHA1(f6e8405cfa604528c0224401bc374a6df9caccef) )
ROM_END

// I'm not sure if NBA Showtime: NBA on NBC Gold was a standalone release, or the version with NBA Showtime: NBA on NBC Gold is actually 'Sports Station'
// it's possible the boot rom and CHD are mismatched here
ROM_START( nbagold )
<<<<<<< HEAD
	ROM_REGION32_LE( 0x80000, "user1", 0 )
	ROM_LOAD( "nbagold_jan10_2000.u27", 0x000000, 0x80000, CRC(6768e802) SHA1(d994e3efe14f57e261841134ddd1489fa67d418b) ) // 11:29:11 Jan 10 2000. BIOS FOR NBAGOLD USING BANSHEE / 11:23:58 Jan 10 2000. POST FOR NBAGOLD USING BANSHEE

	ROM_REGION32_LE( 0x100000, "update", ROMREGION_ERASEFF )


	DISK_REGION( "ide:0:hdd:image" )
=======
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )
	ROM_LOAD( "nbagold_jan10_2000.u27", 0x000000, 0x80000, CRC(6768e802) SHA1(d994e3efe14f57e261841134ddd1489fa67d418b) ) // 11:29:11 Jan 10 2000. BIOS FOR NBAGOLD USING BANSHEE / 11:23:58 Jan 10 2000. POST FOR NBAGOLD USING BANSHEE

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )


	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )
>>>>>>> upstream/master
	// various strings from this image
	//NBA SHOWTIME GOLD 3.00
	//BUILD DATE Feb 18 2000 (diag.exe)
	//BUILD DATE:Feb 17 2000 (game?)
	//BUILD DATE:Feb 10 2000 (something else?)
	DISK_IMAGE( "nbanfl3", 0,  SHA1(19a51346ce5ae4e06e8dff3eb4bed59ec1ee855f))
	// these both contain the same strings / build dates, same thing with different user data / drive sizes?
//  DISK_IMAGE( "nbanfl27", 0, SHA1(da371d27e2fbceec493e2203055e0c1399eaf3b9) )
//  DISK_IMAGE( "sportstn", 0, SHA1(9442feefaeb5ae4a090422e937615f8a2d8e8f31) )


	ROM_REGION16_LE( 0x10000, "dcs", 0 )    /* Vegas SIO boot ROM */
	ROM_LOAD16_BYTE( "vegassio.bin", 0x000000, 0x8000, CRC(d1470e23) SHA1(f6e8405cfa604528c0224401bc374a6df9caccef) )

	// also a PIC?
ROM_END


ROM_START( cartfury )
<<<<<<< HEAD
	ROM_REGION32_LE( 0x80000, "user1", 0 )
	ROM_LOAD( "cart_mar8_2000.u27", 0x000000, 0x80000, CRC(c44550a2) SHA1(ad30f1c3382ff2f5902a4cbacbb1f0c4e37f42f9) ) // 10:40:17 Mar  8 2000 BIOS FOR CART USING VOODOO3 / 10:39:55 Mar  8 2000 POST FOR CART USING VOODOO3

	ROM_REGION32_LE( 0x100000, "update", ROMREGION_ERASEFF )


	DISK_REGION( "ide:0:hdd:image" )
=======
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )
	ROM_LOAD( "cart_mar8_2000.u27", 0x000000, 0x80000, CRC(c44550a2) SHA1(ad30f1c3382ff2f5902a4cbacbb1f0c4e37f42f9) ) // 10:40:17 Mar  8 2000 BIOS FOR CART USING VOODOO3 / 10:39:55 Mar  8 2000 POST FOR CART USING VOODOO3

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )


	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )
>>>>>>> upstream/master
	DISK_IMAGE( "cartfury", 0, SHA1(4c5bc2803297ea9a191bbd8b002d0e46b4ae1563) )

	ROM_REGION16_LE( 0x10000, "dcs", 0 )    /* ADSP-2105 data */
	ROM_LOAD16_BYTE( "vegassio.bin", 0x000000, 0x8000, CRC(d1470e23) SHA1(f6e8405cfa604528c0224401bc374a6df9caccef) )
ROM_END


ROM_START( sf2049 )
<<<<<<< HEAD
	ROM_REGION32_LE( 0x80000, "user1", 0 )  /* EPROM 1.02 7/9/1999 */
	ROM_LOAD( "sf2049.u27", 0x000000, 0x80000, CRC(174ba8fe) SHA1(baba83b811eca659f00514a008a86ef0ac9680ee) )

	ROM_REGION32_LE( 0x100000, "update", ROMREGION_ERASEFF )


	DISK_REGION( "ide:0:hdd:image" )    /* Guts 1.03 9/3/1999 Game 9/8/1999 */
=======
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )  /* EPROM 1.02 7/9/1999 */
	ROM_LOAD( "sf2049.u27", 0x000000, 0x80000, CRC(174ba8fe) SHA1(baba83b811eca659f00514a008a86ef0ac9680ee) )

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )


	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )    /* Guts 1.03 9/3/1999 Game 9/8/1999 */
>>>>>>> upstream/master
	DISK_IMAGE( "sf2049", 0, SHA1(9e0661b8566a6c78d18c59c11cd3a6628d025405) )
ROM_END


ROM_START( sf2049se )
<<<<<<< HEAD
	ROM_REGION32_LE( 0x80000, "user1", 0 )
	ROM_LOAD( "sf2049se.u27", 0x000000, 0x80000, CRC(da4ecd9c) SHA1(2574ff3d608ebcc59a63cf6dea13ee7650ae8921) )

	ROM_REGION32_LE( 0x100000, "update", ROMREGION_ERASEFF )


	DISK_REGION( "ide:0:hdd:image" )
=======
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )
	// Bad Dump
	// POST Message: Boot EPROM checksum...FAILED. Computed: F7017455
	// End of file including checksum area is filled with FF's.
	ROM_LOAD( "sf2049se.u27", 0x000000, 0x80000, CRC(da4ecd9c) SHA1(2574ff3d608ebcc59a63cf6dea13ee7650ae8921) BAD_DUMP )

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )


	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )
>>>>>>> upstream/master
	DISK_IMAGE( "sf2049se", 0, SHA1(7b27a8ce2a953050ce267548bb7160b41f3e8054) )
ROM_END


ROM_START( sf2049te )
<<<<<<< HEAD
	ROM_REGION32_LE( 0x80000, "user1", 0 )
	ROM_LOAD( "sf2049te.u27", 0x000000, 0x80000, CRC(cc7c8601) SHA1(3f37dbd1b32b3ac5caa300725468e8e426f0fb83) )

	ROM_REGION32_LE( 0x100000, "update", ROMREGION_ERASEFF )


	DISK_REGION( "ide:0:hdd:image" )
=======
	ROM_REGION32_LE( 0x80000, PCI_ID_NILE":rom", 0 )
	ROM_LOAD( "sf2049te.u27", 0x000000, 0x80000, CRC(cc7c8601) SHA1(3f37dbd1b32b3ac5caa300725468e8e426f0fb83) )

	ROM_REGION32_LE( 0x100000, PCI_ID_NILE":update", ROMREGION_ERASEFF )


	DISK_REGION( PCI_ID_IDE":ide:0:hdd:image" )
>>>>>>> upstream/master
	DISK_IMAGE( "sf2049te", 0, SHA1(625aa36436587b7bec3e7db1d19793b760e2ea51) )
ROM_END



/*************************************
 *
 *  Driver init
 *
 *************************************/

DRIVER_INIT_MEMBER(vegas_state,gauntleg)
{
	/* speedups */
	m_maincpu->mips3drc_add_hotspot(0x80015430, 0x8CC38060, 250);     /* confirmed */
	m_maincpu->mips3drc_add_hotspot(0x80015464, 0x3C09801E, 250);     /* confirmed */
	m_maincpu->mips3drc_add_hotspot(0x800C8918, 0x8FA2004C, 250);     /* confirmed */
	m_maincpu->mips3drc_add_hotspot(0x800C8890, 0x8FA20024, 250);     /* confirmed */
}


DRIVER_INIT_MEMBER(vegas_state,gauntdl)
{
	/* speedups */
	m_maincpu->mips3drc_add_hotspot(0x800158B8, 0x8CC3CC40, 250);     /* confirmed */
	m_maincpu->mips3drc_add_hotspot(0x800158EC, 0x3C0C8022, 250);     /* confirmed */
	m_maincpu->mips3drc_add_hotspot(0x800D40C0, 0x8FA2004C, 250);     /* confirmed */
	m_maincpu->mips3drc_add_hotspot(0x800D4038, 0x8FA20024, 250);     /* confirmed */
}


DRIVER_INIT_MEMBER(vegas_state,warfa)
{
	/* speedups */
	m_maincpu->mips3drc_add_hotspot(0x8009436C, 0x0C031663, 250);     /* confirmed */
}


DRIVER_INIT_MEMBER(vegas_state,tenthdeg)
{
	/* speedups */
	m_maincpu->mips3drc_add_hotspot(0x80051CD8, 0x0C023C15, 250);     /* confirmed */
	m_maincpu->mips3drc_add_hotspot(0x8005E674, 0x3C028017, 250);     /* confirmed */
	m_maincpu->mips3drc_add_hotspot(0x8002DBCC, 0x8FA2002C, 250);     /* confirmed */
	m_maincpu->mips3drc_add_hotspot(0x80015930, 0x8FC20244, 250);     /* confirmed */
}


DRIVER_INIT_MEMBER(vegas_state,roadburn)
{
}


DRIVER_INIT_MEMBER(vegas_state,nbashowt)
{
}


DRIVER_INIT_MEMBER(vegas_state,nbanfl)
{
<<<<<<< HEAD
=======
	// The first three bytes of the blitz00_nov30_1999.u27 ROM are FF's which breaks the reset vector.
	// These bytes are from blitz00_sep22_1999.u27 which allows the other ROM to start.
	// The last byte which is part of the checksum is also FF. By changing it to 0x01 the 4 byte checksum matches with the other 3 changes.
	uint8_t *romPtr = machine().root_device().memregion(PCI_ID_NILE":rom")->base();
	romPtr[0x0] = 0xe2;
	romPtr[0x1] = 0x00;
	romPtr[0x2] = 0xf0;
	romPtr[0x7ffff] = 0x01;
>>>>>>> upstream/master
}


DRIVER_INIT_MEMBER(vegas_state,sf2049)
{
<<<<<<< HEAD
=======
	m_a2d_shift = 4;
>>>>>>> upstream/master
}


DRIVER_INIT_MEMBER(vegas_state,sf2049se)
{
<<<<<<< HEAD
=======
	m_a2d_shift = 4;
>>>>>>> upstream/master
}


DRIVER_INIT_MEMBER(vegas_state,sf2049te)
{
<<<<<<< HEAD
=======
	m_a2d_shift = 4;
>>>>>>> upstream/master
}


DRIVER_INIT_MEMBER(vegas_state,cartfury)
{
}



/*************************************
 *
 *  Game drivers
 *
 *************************************/

/* Vegas + Vegas SIO + Voodoo 2 */
<<<<<<< HEAD
GAME( 1998, gauntleg,   0,        gauntleg,    gauntleg, vegas_state, gauntleg, ROT0, "Atari Games",  "Gauntlet Legends (version 1.6)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, gauntleg12, gauntleg, gauntleg,    gauntleg, vegas_state, gauntleg, ROT0, "Atari Games",  "Gauntlet Legends (version 1.2)", MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE )
GAME( 1998, tenthdeg, 0,        tenthdeg,    tenthdeg, vegas_state, tenthdeg, ROT0, "Atari Games",  "Tenth Degree (prototype)", MACHINE_SUPPORTS_SAVE )

/* Durango + Vegas SIO + Voodoo 2 */
GAME( 1999, gauntdl,  0,        gauntdl,    gauntdl, vegas_state,  gauntdl,  ROT0, "Midway Games", "Gauntlet Dark Legacy (version DL 2.52)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, gauntdl24,gauntdl,  gauntdl,    gauntdl, vegas_state,  gauntdl,  ROT0, "Midway Games", "Gauntlet Dark Legacy (version DL 2.4)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, warfa,    0,        warfa, warfa, vegas_state,    warfa,    ROT0, "Atari Games",  "War: The Final Assault (EPROM 1.9 Mar 25 1999, GUTS 1.3 Apr 20 1999, GAME Apr 20 1999)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 1999, warfaa,   warfa,    warfa, warfa, vegas_state,    warfa,    ROT0, "Atari Games",  "War: The Final Assault (EPROM 1.6 Jan 14 1999, GUTS 1.1 Mar 16 1999, GAME Mar 16 1999)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )


/* Durango + DSIO + Voodoo 2 */
GAME( 1999, roadburn, 0,        roadburn, roadburn, vegas_state, roadburn, ROT0, "Atari Games",  "Road Burners", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )

/* Durango + DSIO? + Voodoo banshee */
GAME( 1998, nbashowt, 0,        nbashowt, nbashowt, vegas_state, nbashowt, ROT0, "Midway Games", "NBA Showtime: NBA on NBC (ver 2.0)", MACHINE_NO_SOUND | MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 1999, nbanfl,   0,        nbanfl, nbashowt, vegas_state, nbanfl,   ROT0, "Midway Games", "NBA Showtime / NFL Blitz 2000 (ver 2.1)", MACHINE_NO_SOUND | MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2000, nbagold , 0,        nbanfl, nbashowt, vegas_state, nbanfl,   ROT0, "Midway Games", "NBA Showtime Gold / NFL Blitz 2000 (ver 3.0) (Sports Station?)", MACHINE_NO_SOUND | MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )


/* Durango + Denver SIO + Voodoo 3 */
GAME( 1998, sf2049,   0,        sf2049,   sf2049, vegas_state,   sf2049,   ROT0, "Atari Games",  "San Francisco Rush 2049", MACHINE_NO_SOUND | MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 1998, sf2049se, sf2049,   sf2049se,   sf2049se, vegas_state, sf2049se, ROT0, "Atari Games",  "San Francisco Rush 2049: Special Edition", MACHINE_NO_SOUND | MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 1998, sf2049te, sf2049,   sf2049te,   sf2049te, vegas_state, sf2049te, ROT0, "Atari Games",  "San Francisco Rush 2049: Tournament Edition", MACHINE_NO_SOUND | MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE)

/* Durango + Vegas SIO + Voodoo 3 */
GAME( 2000, cartfury, 0,        cartfury,  cartfury, vegas_state, cartfury, ROT0, "Midway Games", "Cart Fury", MACHINE_NO_SOUND | MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
=======
GAME( 1998, gauntleg,   0,        gauntleg, gauntleg, vegas_state, gauntleg, ROT0, "Atari Games",   "Gauntlet Legends (version 1.6)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, gauntleg12, gauntleg, gauntleg, gauntleg, vegas_state, gauntleg, ROT0, "Atari Games",   "Gauntlet Legends (version 1.2)", MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE )
GAME( 1998, tenthdeg,   0,        tenthdeg, tenthdeg, vegas_state, tenthdeg, ROT0, "Atari Games",   "Tenth Degree (prototype)", MACHINE_SUPPORTS_SAVE )

/* Durango + Vegas SIO + Voodoo 2 */
GAME( 1999, gauntdl,    0,        gauntdl,  gauntdl,  vegas_state,  gauntdl,  ROT0, "Midway Games", "Gauntlet Dark Legacy (version DL 2.52)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, gauntdl24,  gauntdl,  gauntdl,  gauntdl,  vegas_state,  gauntdl,  ROT0, "Midway Games", "Gauntlet Dark Legacy (version DL 2.4)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, warfa,      0,        warfa,    warfa,    vegas_state,  warfa,    ROT0, "Atari Games",  "War: The Final Assault (EPROM 1.9 Mar 25 1999, GUTS 1.3 Apr 20 1999, GAME Apr 20 1999)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 1999, warfaa,     warfa,    warfa,    warfa,    vegas_state,  warfa,    ROT0, "Atari Games",  "War: The Final Assault (EPROM 1.6 Jan 14 1999, GUTS 1.1 Mar 16 1999, GAME Mar 16 1999)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 1999, warfab,     warfa,    warfa,    warfa,    vegas_state,  warfa,    ROT0, "Atari Games",  "War: The Final Assault (EPROM 1.3 Apr 7 1999, GUTS 1.3 Apr 7 1999, GAME Apr 7 1999)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE ) // version numbers comes from test mode, can be unreliable
GAME( 1999, warfac,     warfa,    warfa,    warfa,    vegas_state,  warfa,    ROT0, "Atari Games",  "War: The Final Assault (EPROM 1.91 Apr 13 1999, GUTS 1.3 Apr 7 1999, GAME Apr 7 1999)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )


/* Durango + DSIO + Voodoo 2 */
GAME( 1999, roadburn,   0,        roadburn, roadburn, vegas_state, roadburn, ROT0, "Atari Games",   "Road Burners (ver 1.04)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 1999, roadburn1,  roadburn, roadburn, roadburn, vegas_state, roadburn, ROT0, "Atari Games",   "Road Burners (ver 1.0)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )

/* Durango + DSIO? + Voodoo banshee */
GAME( 1998, nbashowt,   0,        nbashowt, nbashowt, vegas_state, nbashowt, ROT0, "Midway Games",  "NBA Showtime: NBA on NBC (ver 2.0)", MACHINE_NO_SOUND | MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 1999, nbanfl,     0,        nbanfl,   nbashowt, vegas_state, nbanfl,   ROT0, "Midway Games",  "NBA Showtime / NFL Blitz 2000 (ver 2.1)", MACHINE_NO_SOUND | MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2000, nbagold ,   0,        nbagold,  nbashowt, vegas_state, nbanfl,   ROT0, "Midway Games",  "NBA Showtime Gold / NFL Blitz 2000 (ver 3.0) (Sports Station?)", MACHINE_NO_SOUND | MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )


/* Durango + Denver SIO + Voodoo 3 */
GAMEL( 1998, sf2049,     0,        sf2049,   sf2049,   vegas_state, sf2049,   ROT0, "Atari Games",   "San Francisco Rush 2049", MACHINE_NO_SOUND | MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE, layout_sf2049 )
GAMEL( 1998, sf2049se,   sf2049,   sf2049se, sf2049se, vegas_state, sf2049se, ROT0, "Atari Games",   "San Francisco Rush 2049: Special Edition", MACHINE_NO_SOUND | MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE, layout_sf2049 )
GAMEL( 1998, sf2049te,   sf2049,   sf2049te, sf2049se, vegas_state, sf2049te, ROT0, "Atari Games",   "San Francisco Rush 2049: Tournament Edition", MACHINE_NO_SOUND | MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE, layout_sf2049 )

/* Durango + Vegas SIO + Voodoo 3 */
GAME( 2000, cartfury,   0,        cartfury, cartfury, vegas_state, cartfury, ROT0, "Midway Games",  "Cart Fury", MACHINE_NO_SOUND | MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
>>>>>>> upstream/master
