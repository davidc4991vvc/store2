// license:BSD-3-Clause
// copyright-holders:Steve Ellenoff,R. Belmont,Ryan Holtz
#include "emu.h"
#include "arm7.h"
#include "arm7core.h"
#include "arm7help.h"

// this is our master dispatch jump table for THUMB mode, representing [(INSN & 0xffc0) >> 6] bits of the 16-bit decoded instruction
const arm7_cpu_device::arm7thumb_ophandler arm7_cpu_device::thumb_handler[0x40*0x10] =
{
<<<<<<< HEAD
// #define THUMB_SHIFT_R       ((UINT16)0x0800)
=======
// #define THUMB_SHIFT_R       ((uint16_t)0x0800)
>>>>>>> upstream/master
	&arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,
	&arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,
	&arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,
	&arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,
	&arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,
	&arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,
	&arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,
	&arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,     &arm7_cpu_device::tg00_0,
	&arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,
	&arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,
	&arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,
	&arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,
	&arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,
	&arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,
	&arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,
	&arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,     &arm7_cpu_device::tg00_1,
<<<<<<< HEAD
// #define THUMB_INSN_ADDSUB   ((UINT16)0x0800)   // #define THUMB_ADDSUB_TYPE   ((UINT16)0x0600)
=======
// #define THUMB_INSN_ADDSUB   ((uint16_t)0x0800)   // #define THUMB_ADDSUB_TYPE   ((uint16_t)0x0600)
>>>>>>> upstream/master
	&arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,
	&arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,
	&arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,
	&arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,
	&arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,
	&arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,
	&arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,
	&arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,     &arm7_cpu_device::tg01_0,
	&arm7_cpu_device::tg01_10,    &arm7_cpu_device::tg01_10,    &arm7_cpu_device::tg01_10,    &arm7_cpu_device::tg01_10,
	&arm7_cpu_device::tg01_10,    &arm7_cpu_device::tg01_10,    &arm7_cpu_device::tg01_10,    &arm7_cpu_device::tg01_10,
	&arm7_cpu_device::tg01_11,    &arm7_cpu_device::tg01_11,    &arm7_cpu_device::tg01_11,    &arm7_cpu_device::tg01_11,
	&arm7_cpu_device::tg01_11,    &arm7_cpu_device::tg01_11,    &arm7_cpu_device::tg01_11,    &arm7_cpu_device::tg01_11,
	&arm7_cpu_device::tg01_12,    &arm7_cpu_device::tg01_12,    &arm7_cpu_device::tg01_12,    &arm7_cpu_device::tg01_12,
	&arm7_cpu_device::tg01_12,    &arm7_cpu_device::tg01_12,    &arm7_cpu_device::tg01_12,    &arm7_cpu_device::tg01_12,
	&arm7_cpu_device::tg01_13,    &arm7_cpu_device::tg01_13,    &arm7_cpu_device::tg01_13,    &arm7_cpu_device::tg01_13,
	&arm7_cpu_device::tg01_13,    &arm7_cpu_device::tg01_13,    &arm7_cpu_device::tg01_13,    &arm7_cpu_device::tg01_13,
<<<<<<< HEAD
// #define THUMB_INSN_CMP      ((UINT16)0x0800)
=======
// #define THUMB_INSN_CMP      ((uint16_t)0x0800)
>>>>>>> upstream/master
	&arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,
	&arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,
	&arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,
	&arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,
	&arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,
	&arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,
	&arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,
	&arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,     &arm7_cpu_device::tg02_0,
	&arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,
	&arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,
	&arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,
	&arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,
	&arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,
	&arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,
	&arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,
	&arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,     &arm7_cpu_device::tg02_1,
<<<<<<< HEAD
// #define THUMB_INSN_SUB      ((UINT16)0x0800)
=======
// #define THUMB_INSN_SUB      ((uint16_t)0x0800)
>>>>>>> upstream/master
	&arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,
	&arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,
	&arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,
	&arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,
	&arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,
	&arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,
	&arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,
	&arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,     &arm7_cpu_device::tg03_0,
	&arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,
	&arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,
	&arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,
	&arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,
	&arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,
	&arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,
	&arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,
	&arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,     &arm7_cpu_device::tg03_1,
<<<<<<< HEAD
//#define THUMB_GROUP4_TYPE   ((UINT16)0x0c00)  //#define THUMB_ALUOP_TYPE    ((UINT16)0x03c0)  // #define THUMB_HIREG_OP      ((UINT16)0x0300)  // #define THUMB_HIREG_H       ((UINT16)0x00c0)
=======
//#define THUMB_GROUP4_TYPE   ((uint16_t)0x0c00)  //#define THUMB_ALUOP_TYPE    ((uint16_t)0x03c0)  // #define THUMB_HIREG_OP      ((uint16_t)0x0300)  // #define THUMB_HIREG_H       ((uint16_t)0x00c0)
>>>>>>> upstream/master
	&arm7_cpu_device::tg04_00_00, &arm7_cpu_device::tg04_00_01, &arm7_cpu_device::tg04_00_02, &arm7_cpu_device::tg04_00_03,
	&arm7_cpu_device::tg04_00_04, &arm7_cpu_device::tg04_00_05, &arm7_cpu_device::tg04_00_06, &arm7_cpu_device::tg04_00_07,
	&arm7_cpu_device::tg04_00_08, &arm7_cpu_device::tg04_00_09, &arm7_cpu_device::tg04_00_0a, &arm7_cpu_device::tg04_00_0b,
	&arm7_cpu_device::tg04_00_0c, &arm7_cpu_device::tg04_00_0d, &arm7_cpu_device::tg04_00_0e, &arm7_cpu_device::tg04_00_0f,
	&arm7_cpu_device::tg04_01_00, &arm7_cpu_device::tg04_01_01, &arm7_cpu_device::tg04_01_02, &arm7_cpu_device::tg04_01_03,
	&arm7_cpu_device::tg04_01_10, &arm7_cpu_device::tg04_01_11, &arm7_cpu_device::tg04_01_12, &arm7_cpu_device::tg04_01_13,
	&arm7_cpu_device::tg04_01_20, &arm7_cpu_device::tg04_01_21, &arm7_cpu_device::tg04_01_22, &arm7_cpu_device::tg04_01_23,
	&arm7_cpu_device::tg04_01_30, &arm7_cpu_device::tg04_01_31, &arm7_cpu_device::tg04_01_32, &arm7_cpu_device::tg04_01_33,
	&arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,
	&arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,
	&arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,
	&arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,
	&arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,
	&arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,
	&arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,
	&arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,  &arm7_cpu_device::tg04_0203,
<<<<<<< HEAD
//#define THUMB_GROUP5_TYPE   ((UINT16)0x0e00)
=======
//#define THUMB_GROUP5_TYPE   ((uint16_t)0x0e00)
>>>>>>> upstream/master
	&arm7_cpu_device::tg05_0,     &arm7_cpu_device::tg05_0,     &arm7_cpu_device::tg05_0,     &arm7_cpu_device::tg05_0,
	&arm7_cpu_device::tg05_0,     &arm7_cpu_device::tg05_0,     &arm7_cpu_device::tg05_0,     &arm7_cpu_device::tg05_0,
	&arm7_cpu_device::tg05_1,     &arm7_cpu_device::tg05_1,     &arm7_cpu_device::tg05_1,     &arm7_cpu_device::tg05_1,
	&arm7_cpu_device::tg05_1,     &arm7_cpu_device::tg05_1,     &arm7_cpu_device::tg05_1,     &arm7_cpu_device::tg05_1,
	&arm7_cpu_device::tg05_2,     &arm7_cpu_device::tg05_2,     &arm7_cpu_device::tg05_2,     &arm7_cpu_device::tg05_2,
	&arm7_cpu_device::tg05_2,     &arm7_cpu_device::tg05_2,     &arm7_cpu_device::tg05_2,     &arm7_cpu_device::tg05_2,
	&arm7_cpu_device::tg05_3,     &arm7_cpu_device::tg05_3,     &arm7_cpu_device::tg05_3,     &arm7_cpu_device::tg05_3,
	&arm7_cpu_device::tg05_3,     &arm7_cpu_device::tg05_3,     &arm7_cpu_device::tg05_3,     &arm7_cpu_device::tg05_3,
	&arm7_cpu_device::tg05_4,     &arm7_cpu_device::tg05_4,     &arm7_cpu_device::tg05_4,     &arm7_cpu_device::tg05_4,
	&arm7_cpu_device::tg05_4,     &arm7_cpu_device::tg05_4,     &arm7_cpu_device::tg05_4,     &arm7_cpu_device::tg05_4,
	&arm7_cpu_device::tg05_5,     &arm7_cpu_device::tg05_5,     &arm7_cpu_device::tg05_5,     &arm7_cpu_device::tg05_5,
	&arm7_cpu_device::tg05_5,     &arm7_cpu_device::tg05_5,     &arm7_cpu_device::tg05_5,     &arm7_cpu_device::tg05_5,
	&arm7_cpu_device::tg05_6,     &arm7_cpu_device::tg05_6,     &arm7_cpu_device::tg05_6,     &arm7_cpu_device::tg05_6,
	&arm7_cpu_device::tg05_6,     &arm7_cpu_device::tg05_6,     &arm7_cpu_device::tg05_6,     &arm7_cpu_device::tg05_6,
	&arm7_cpu_device::tg05_7,     &arm7_cpu_device::tg05_7,     &arm7_cpu_device::tg05_7,     &arm7_cpu_device::tg05_7,
	&arm7_cpu_device::tg05_7,     &arm7_cpu_device::tg05_7,     &arm7_cpu_device::tg05_7,     &arm7_cpu_device::tg05_7,
<<<<<<< HEAD
//#define THUMB_LSOP_L        ((UINT16)0x0800)
=======
//#define THUMB_LSOP_L        ((uint16_t)0x0800)
>>>>>>> upstream/master
	&arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,
	&arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,
	&arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,
	&arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,
	&arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,
	&arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,
	&arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,
	&arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,     &arm7_cpu_device::tg06_0,
	&arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,
	&arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,
	&arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,
	&arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,
	&arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,
	&arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,
	&arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,
	&arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,     &arm7_cpu_device::tg06_1,
<<<<<<< HEAD
//#define THUMB_LSOP_L        ((UINT16)0x0800)
=======
//#define THUMB_LSOP_L        ((uint16_t)0x0800)
>>>>>>> upstream/master
	&arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,
	&arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,
	&arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,
	&arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,
	&arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,
	&arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,
	&arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,
	&arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,     &arm7_cpu_device::tg07_0,
	&arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,
	&arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,
	&arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,
	&arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,
	&arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,
	&arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,
	&arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,
	&arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,     &arm7_cpu_device::tg07_1,
<<<<<<< HEAD
// #define THUMB_HALFOP_L      ((UINT16)0x0800)
=======
// #define THUMB_HALFOP_L      ((uint16_t)0x0800)
>>>>>>> upstream/master
	&arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,
	&arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,
	&arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,
	&arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,
	&arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,
	&arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,
	&arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,
	&arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,     &arm7_cpu_device::tg08_0,
	&arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,
	&arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,
	&arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,
	&arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,
	&arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,
	&arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,
	&arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,
	&arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,     &arm7_cpu_device::tg08_1,
<<<<<<< HEAD
// #define THUMB_STACKOP_L     ((UINT16)0x0800)
=======
// #define THUMB_STACKOP_L     ((uint16_t)0x0800)
>>>>>>> upstream/master
	&arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,
	&arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,
	&arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,
	&arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,
	&arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,
	&arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,
	&arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,
	&arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,     &arm7_cpu_device::tg09_0,
	&arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,
	&arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,
	&arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,
	&arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,
	&arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,
	&arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,
	&arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,
	&arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,     &arm7_cpu_device::tg09_1,
<<<<<<< HEAD
// #define THUMB_RELADDR_SP    ((UINT16)0x0800)
=======
// #define THUMB_RELADDR_SP    ((uint16_t)0x0800)
>>>>>>> upstream/master
	&arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,
	&arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,
	&arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,
	&arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,
	&arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,
	&arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,
	&arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,
	&arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,     &arm7_cpu_device::tg0a_0,
	&arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,
	&arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,
	&arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,
	&arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,
	&arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,
	&arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,
	&arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,
	&arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,     &arm7_cpu_device::tg0a_1,
<<<<<<< HEAD
// #define THUMB_STACKOP_TYPE  ((UINT16)0x0f00)
=======
// #define THUMB_STACKOP_TYPE  ((uint16_t)0x0f00)
>>>>>>> upstream/master
	&arm7_cpu_device::tg0b_0,     &arm7_cpu_device::tg0b_0,     &arm7_cpu_device::tg0b_0,     &arm7_cpu_device::tg0b_0,
	&arm7_cpu_device::tg0b_1,     &arm7_cpu_device::tg0b_1,     &arm7_cpu_device::tg0b_1,     &arm7_cpu_device::tg0b_1,
	&arm7_cpu_device::tg0b_2,     &arm7_cpu_device::tg0b_2,     &arm7_cpu_device::tg0b_2,     &arm7_cpu_device::tg0b_2,
	&arm7_cpu_device::tg0b_3,     &arm7_cpu_device::tg0b_3,     &arm7_cpu_device::tg0b_3,     &arm7_cpu_device::tg0b_3,
	&arm7_cpu_device::tg0b_4,     &arm7_cpu_device::tg0b_4,     &arm7_cpu_device::tg0b_4,     &arm7_cpu_device::tg0b_4,
	&arm7_cpu_device::tg0b_5,     &arm7_cpu_device::tg0b_5,     &arm7_cpu_device::tg0b_5,     &arm7_cpu_device::tg0b_5,
	&arm7_cpu_device::tg0b_6,     &arm7_cpu_device::tg0b_6,     &arm7_cpu_device::tg0b_6,     &arm7_cpu_device::tg0b_6,
	&arm7_cpu_device::tg0b_7,     &arm7_cpu_device::tg0b_7,     &arm7_cpu_device::tg0b_7,     &arm7_cpu_device::tg0b_7,
	&arm7_cpu_device::tg0b_8,     &arm7_cpu_device::tg0b_8,     &arm7_cpu_device::tg0b_8,     &arm7_cpu_device::tg0b_8,
	&arm7_cpu_device::tg0b_9,     &arm7_cpu_device::tg0b_9,     &arm7_cpu_device::tg0b_9,     &arm7_cpu_device::tg0b_9,
	&arm7_cpu_device::tg0b_a,     &arm7_cpu_device::tg0b_a,     &arm7_cpu_device::tg0b_a,     &arm7_cpu_device::tg0b_a,
	&arm7_cpu_device::tg0b_b,     &arm7_cpu_device::tg0b_b,     &arm7_cpu_device::tg0b_b,     &arm7_cpu_device::tg0b_b,
	&arm7_cpu_device::tg0b_c,     &arm7_cpu_device::tg0b_c,     &arm7_cpu_device::tg0b_c,     &arm7_cpu_device::tg0b_c,
	&arm7_cpu_device::tg0b_d,     &arm7_cpu_device::tg0b_d,     &arm7_cpu_device::tg0b_d,     &arm7_cpu_device::tg0b_d,
	&arm7_cpu_device::tg0b_e,     &arm7_cpu_device::tg0b_e,     &arm7_cpu_device::tg0b_e,     &arm7_cpu_device::tg0b_e,
	&arm7_cpu_device::tg0b_f,     &arm7_cpu_device::tg0b_f,     &arm7_cpu_device::tg0b_f,     &arm7_cpu_device::tg0b_f,
<<<<<<< HEAD
// #define THUMB_MULTLS        ((UINT16)0x0800)
=======
// #define THUMB_MULTLS        ((uint16_t)0x0800)
>>>>>>> upstream/master
	&arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,
	&arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,
	&arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,
	&arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,
	&arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,
	&arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,
	&arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,
	&arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,     &arm7_cpu_device::tg0c_0,
	&arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,
	&arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,
	&arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,
	&arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,
	&arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,
	&arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,
	&arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,
	&arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,     &arm7_cpu_device::tg0c_1,
<<<<<<< HEAD
// #define THUMB_COND_TYPE     ((UINT16)0x0f00)
=======
// #define THUMB_COND_TYPE     ((uint16_t)0x0f00)
>>>>>>> upstream/master
	&arm7_cpu_device::tg0d_0,     &arm7_cpu_device::tg0d_0,     &arm7_cpu_device::tg0d_0,     &arm7_cpu_device::tg0d_0,
	&arm7_cpu_device::tg0d_1,     &arm7_cpu_device::tg0d_1,     &arm7_cpu_device::tg0d_1,     &arm7_cpu_device::tg0d_1,
	&arm7_cpu_device::tg0d_2,     &arm7_cpu_device::tg0d_2,     &arm7_cpu_device::tg0d_2,     &arm7_cpu_device::tg0d_2,
	&arm7_cpu_device::tg0d_3,     &arm7_cpu_device::tg0d_3,     &arm7_cpu_device::tg0d_3,     &arm7_cpu_device::tg0d_3,
	&arm7_cpu_device::tg0d_4,     &arm7_cpu_device::tg0d_4,     &arm7_cpu_device::tg0d_4,     &arm7_cpu_device::tg0d_4,
	&arm7_cpu_device::tg0d_5,     &arm7_cpu_device::tg0d_5,     &arm7_cpu_device::tg0d_5,     &arm7_cpu_device::tg0d_5,
	&arm7_cpu_device::tg0d_6,     &arm7_cpu_device::tg0d_6,     &arm7_cpu_device::tg0d_6,     &arm7_cpu_device::tg0d_6,
	&arm7_cpu_device::tg0d_7,     &arm7_cpu_device::tg0d_7,     &arm7_cpu_device::tg0d_7,     &arm7_cpu_device::tg0d_7,
	&arm7_cpu_device::tg0d_8,     &arm7_cpu_device::tg0d_8,     &arm7_cpu_device::tg0d_8,     &arm7_cpu_device::tg0d_8,
	&arm7_cpu_device::tg0d_9,     &arm7_cpu_device::tg0d_9,     &arm7_cpu_device::tg0d_9,     &arm7_cpu_device::tg0d_9,
	&arm7_cpu_device::tg0d_a,     &arm7_cpu_device::tg0d_a,     &arm7_cpu_device::tg0d_a,     &arm7_cpu_device::tg0d_a,
	&arm7_cpu_device::tg0d_b,     &arm7_cpu_device::tg0d_b,     &arm7_cpu_device::tg0d_b,     &arm7_cpu_device::tg0d_b,
	&arm7_cpu_device::tg0d_c,     &arm7_cpu_device::tg0d_c,     &arm7_cpu_device::tg0d_c,     &arm7_cpu_device::tg0d_c,
	&arm7_cpu_device::tg0d_d,     &arm7_cpu_device::tg0d_d,     &arm7_cpu_device::tg0d_d,     &arm7_cpu_device::tg0d_d,
	&arm7_cpu_device::tg0d_e,     &arm7_cpu_device::tg0d_e,     &arm7_cpu_device::tg0d_e,     &arm7_cpu_device::tg0d_e,
	&arm7_cpu_device::tg0d_f,     &arm7_cpu_device::tg0d_f,     &arm7_cpu_device::tg0d_f,     &arm7_cpu_device::tg0d_f,
<<<<<<< HEAD
// #define THUMB_BLOP_LO       ((UINT16)0x0800)
=======
// #define THUMB_BLOP_LO       ((uint16_t)0x0800)
>>>>>>> upstream/master
	&arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,
	&arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,
	&arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,
	&arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,
	&arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,
	&arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,
	&arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,
	&arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,     &arm7_cpu_device::tg0e_0,
	&arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,
	&arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,
	&arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,
	&arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,
	&arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,
	&arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,
	&arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,
	&arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,     &arm7_cpu_device::tg0e_1,
<<<<<<< HEAD
// #define THUMB_BLOP_LO       ((UINT16)0x0800)
=======
// #define THUMB_BLOP_LO       ((uint16_t)0x0800)
>>>>>>> upstream/master
	&arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,
	&arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,
	&arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,
	&arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,
	&arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,
	&arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,
	&arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,
	&arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,     &arm7_cpu_device::tg0f_0,
	&arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,
	&arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,
	&arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,
	&arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,
	&arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,
	&arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,
	&arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,
	&arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,     &arm7_cpu_device::tg0f_1,
};

	/* Shift operations */

<<<<<<< HEAD
void arm7_cpu_device::tg00_0(UINT32 pc, UINT32 op) /* Shift left */
{
	UINT32 rs, rd, rrs;
	INT32 offs;

	SET_CPSR(GET_CPSR & ~(N_MASK | Z_MASK));

	rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	rrs = GET_REGISTER(rs);
	offs = (op & THUMB_SHIFT_AMT) >> THUMB_SHIFT_AMT_SHIFT;
	if (offs != 0)
	{
		SET_REGISTER(rd, rrs << offs);
		if (rrs & (1 << (31 - (offs - 1))))
		{
			SET_CPSR(GET_CPSR | C_MASK);
		}
		else
		{
			SET_CPSR(GET_CPSR & ~C_MASK);
=======
void arm7_cpu_device::tg00_0(uint32_t pc, uint32_t op) /* Shift left */
{
	uint32_t rs, rd, rrs;
	int32_t offs;

	set_cpsr(GET_CPSR & ~(N_MASK | Z_MASK));

	rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	rrs = GetRegister(rs);
	offs = (op & THUMB_SHIFT_AMT) >> THUMB_SHIFT_AMT_SHIFT;
	if (offs != 0)
	{
		SetRegister(rd, rrs << offs);
		if (rrs & (1 << (31 - (offs - 1))))
		{
			set_cpsr(GET_CPSR | C_MASK);
		}
		else
		{
			set_cpsr(GET_CPSR & ~C_MASK);
>>>>>>> upstream/master
		}
	}
	else
	{
<<<<<<< HEAD
		SET_REGISTER(rd, rrs);
	}
	SET_CPSR(GET_CPSR & ~(Z_MASK | N_MASK));
	SET_CPSR(GET_CPSR | HandleALUNZFlags(GET_REGISTER(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg00_1(UINT32 pc, UINT32 op) /* Shift right */
{
	UINT32 rs, rd, rrs;
	INT32 offs;

	rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	rrs = GET_REGISTER(rs);
	offs = (op & THUMB_SHIFT_AMT) >> THUMB_SHIFT_AMT_SHIFT;
	if (offs != 0)
	{
		SET_REGISTER(rd, rrs >> offs);
		if (rrs & (1 << (offs - 1)))
		{
			SET_CPSR(GET_CPSR | C_MASK);
		}
		else
		{
			SET_CPSR(GET_CPSR & ~C_MASK);
=======
		SetRegister(rd, rrs);
	}
	set_cpsr(GET_CPSR & ~(Z_MASK | N_MASK));
	set_cpsr(GET_CPSR | HandleALUNZFlags(GetRegister(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg00_1(uint32_t pc, uint32_t op) /* Shift right */
{
	uint32_t rs, rd, rrs;
	int32_t offs;

	rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	rrs = GetRegister(rs);
	offs = (op & THUMB_SHIFT_AMT) >> THUMB_SHIFT_AMT_SHIFT;
	if (offs != 0)
	{
		SetRegister(rd, rrs >> offs);
		if (rrs & (1 << (offs - 1)))
		{
			set_cpsr(GET_CPSR | C_MASK);
		}
		else
		{
			set_cpsr(GET_CPSR & ~C_MASK);
>>>>>>> upstream/master
		}
	}
	else
	{
<<<<<<< HEAD
		SET_REGISTER(rd, 0);
		if (rrs & 0x80000000)
		{
			SET_CPSR(GET_CPSR | C_MASK);
		}
		else
		{
			SET_CPSR(GET_CPSR & ~C_MASK);
		}
	}
	SET_CPSR(GET_CPSR & ~(Z_MASK | N_MASK));
	SET_CPSR(GET_CPSR | HandleALUNZFlags(GET_REGISTER(rd)));
=======
		SetRegister(rd, 0);
		if (rrs & 0x80000000)
		{
			set_cpsr(GET_CPSR | C_MASK);
		}
		else
		{
			set_cpsr(GET_CPSR & ~C_MASK);
		}
	}
	set_cpsr(GET_CPSR & ~(Z_MASK | N_MASK));
	set_cpsr(GET_CPSR | HandleALUNZFlags(GetRegister(rd)));
>>>>>>> upstream/master
	R15 += 2;
}

	/* Arithmetic */

<<<<<<< HEAD
void arm7_cpu_device::tg01_0(UINT32 pc, UINT32 op)
{
	UINT32 rs, rd, rrs;
	INT32 offs;
=======
void arm7_cpu_device::tg01_0(uint32_t pc, uint32_t op)
{
	uint32_t rs, rd, rrs;
	int32_t offs;
>>>>>>> upstream/master
	/* ASR.. */
	//if (op & THUMB_SHIFT_R) /* Shift right */
	{
		rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
		rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
<<<<<<< HEAD
		rrs = GET_REGISTER(rs);
=======
		rrs = GetRegister(rs);
>>>>>>> upstream/master
		offs = (op & THUMB_SHIFT_AMT) >> THUMB_SHIFT_AMT_SHIFT;
		if (offs == 0)
		{
			offs = 32;
		}
		if (offs >= 32)
		{
			if (rrs >> 31)
			{
<<<<<<< HEAD
				SET_CPSR(GET_CPSR | C_MASK);
			}
			else
			{
				SET_CPSR(GET_CPSR & ~C_MASK);
			}
			SET_REGISTER(rd, (rrs & 0x80000000) ? 0xFFFFFFFF : 0x00000000);
=======
				set_cpsr(GET_CPSR | C_MASK);
			}
			else
			{
				set_cpsr(GET_CPSR & ~C_MASK);
			}
			SetRegister(rd, (rrs & 0x80000000) ? 0xFFFFFFFF : 0x00000000);
>>>>>>> upstream/master
		}
		else
		{
			if ((rrs >> (offs - 1)) & 1)
			{
<<<<<<< HEAD
				SET_CPSR(GET_CPSR | C_MASK);
			}
			else
			{
				SET_CPSR(GET_CPSR & ~C_MASK);
			}
			SET_REGISTER(rd,
=======
				set_cpsr(GET_CPSR | C_MASK);
			}
			else
			{
				set_cpsr(GET_CPSR & ~C_MASK);
			}
			SetRegister(rd,
>>>>>>> upstream/master
							(rrs & 0x80000000)
							? ((0xFFFFFFFF << (32 - offs)) | (rrs >> offs))
							: (rrs >> offs));
		}
<<<<<<< HEAD
		SET_CPSR(GET_CPSR & ~(N_MASK | Z_MASK));
		SET_CPSR(GET_CPSR | HandleALUNZFlags(GET_REGISTER(rd)));
=======
		set_cpsr(GET_CPSR & ~(N_MASK | Z_MASK));
		set_cpsr(GET_CPSR | HandleALUNZFlags(GetRegister(rd)));
>>>>>>> upstream/master
		R15 += 2;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg01_10(UINT32 pc, UINT32 op)  /* ADD Rd, Rs, Rn */
{
	UINT32 rn = GET_REGISTER((op & THUMB_ADDSUB_RNIMM) >> THUMB_ADDSUB_RNIMM_SHIFT);
	UINT32 rs = GET_REGISTER((op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT);
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SET_REGISTER(rd, rs + rn);
	HandleThumbALUAddFlags(GET_REGISTER(rd), rs, rn);

}

void arm7_cpu_device::tg01_11(UINT32 pc, UINT32 op) /* SUB Rd, Rs, Rn */
{
	UINT32 rn = GET_REGISTER((op & THUMB_ADDSUB_RNIMM) >> THUMB_ADDSUB_RNIMM_SHIFT);
	UINT32 rs = GET_REGISTER((op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT);
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SET_REGISTER(rd, rs - rn);
	HandleThumbALUSubFlags(GET_REGISTER(rd), rs, rn);

}

void arm7_cpu_device::tg01_12(UINT32 pc, UINT32 op) /* ADD Rd, Rs, #imm */
{
	UINT32 imm = (op & THUMB_ADDSUB_RNIMM) >> THUMB_ADDSUB_RNIMM_SHIFT;
	UINT32 rs = GET_REGISTER((op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT);
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SET_REGISTER(rd, rs + imm);
	HandleThumbALUAddFlags(GET_REGISTER(rd), rs, imm);

}

void arm7_cpu_device::tg01_13(UINT32 pc, UINT32 op) /* SUB Rd, Rs, #imm */
{
	UINT32 imm = (op & THUMB_ADDSUB_RNIMM) >> THUMB_ADDSUB_RNIMM_SHIFT;
	UINT32 rs = GET_REGISTER((op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT);
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SET_REGISTER(rd, rs - imm);
	HandleThumbALUSubFlags(GET_REGISTER(rd), rs,imm);
=======
void arm7_cpu_device::tg01_10(uint32_t pc, uint32_t op)  /* ADD Rd, Rs, Rn */
{
	uint32_t rn = GetRegister((op & THUMB_ADDSUB_RNIMM) >> THUMB_ADDSUB_RNIMM_SHIFT);
	uint32_t rs = GetRegister((op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT);
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SetRegister(rd, rs + rn);
	HandleThumbALUAddFlags(GetRegister(rd), rs, rn);

}

void arm7_cpu_device::tg01_11(uint32_t pc, uint32_t op) /* SUB Rd, Rs, Rn */
{
	uint32_t rn = GetRegister((op & THUMB_ADDSUB_RNIMM) >> THUMB_ADDSUB_RNIMM_SHIFT);
	uint32_t rs = GetRegister((op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT);
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SetRegister(rd, rs - rn);
	HandleThumbALUSubFlags(GetRegister(rd), rs, rn);

}

void arm7_cpu_device::tg01_12(uint32_t pc, uint32_t op) /* ADD Rd, Rs, #imm */
{
	uint32_t imm = (op & THUMB_ADDSUB_RNIMM) >> THUMB_ADDSUB_RNIMM_SHIFT;
	uint32_t rs = GetRegister((op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT);
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SetRegister(rd, rs + imm);
	HandleThumbALUAddFlags(GetRegister(rd), rs, imm);

}

void arm7_cpu_device::tg01_13(uint32_t pc, uint32_t op) /* SUB Rd, Rs, #imm */
{
	uint32_t imm = (op & THUMB_ADDSUB_RNIMM) >> THUMB_ADDSUB_RNIMM_SHIFT;
	uint32_t rs = GetRegister((op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT);
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SetRegister(rd, rs - imm);
	HandleThumbALUSubFlags(GetRegister(rd), rs,imm);
>>>>>>> upstream/master

}

	/* CMP / MOV */

<<<<<<< HEAD
void arm7_cpu_device::tg02_0(UINT32 pc, UINT32 op)
{
	UINT32 rd = (op & THUMB_INSN_IMM_RD) >> THUMB_INSN_IMM_RD_SHIFT;
	UINT32 op2 = (op & THUMB_INSN_IMM);
	SET_REGISTER(rd, op2);
	SET_CPSR(GET_CPSR & ~(Z_MASK | N_MASK));
	SET_CPSR(GET_CPSR | HandleALUNZFlags(GET_REGISTER(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg02_1(UINT32 pc, UINT32 op)
{
	UINT32 rn = GET_REGISTER((op & THUMB_INSN_IMM_RD) >> THUMB_INSN_IMM_RD_SHIFT);
	UINT32 op2 = op & THUMB_INSN_IMM;
	UINT32 rd = rn - op2;
=======
void arm7_cpu_device::tg02_0(uint32_t pc, uint32_t op)
{
	uint32_t rd = (op & THUMB_INSN_IMM_RD) >> THUMB_INSN_IMM_RD_SHIFT;
	uint32_t op2 = (op & THUMB_INSN_IMM);
	SetRegister(rd, op2);
	set_cpsr(GET_CPSR & ~(Z_MASK | N_MASK));
	set_cpsr(GET_CPSR | HandleALUNZFlags(GetRegister(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg02_1(uint32_t pc, uint32_t op)
{
	uint32_t rn = GetRegister((op & THUMB_INSN_IMM_RD) >> THUMB_INSN_IMM_RD_SHIFT);
	uint32_t op2 = op & THUMB_INSN_IMM;
	uint32_t rd = rn - op2;
>>>>>>> upstream/master
	HandleThumbALUSubFlags(rd, rn, op2);
}

	/* ADD/SUB immediate */

<<<<<<< HEAD
void arm7_cpu_device::tg03_0(UINT32 pc, UINT32 op) /* ADD Rd, #Offset8 */
{
	UINT32 rn = GET_REGISTER((op & THUMB_INSN_IMM_RD) >> THUMB_INSN_IMM_RD_SHIFT);
	UINT32 op2 = op & THUMB_INSN_IMM;
	UINT32 rd = rn + op2;
	SET_REGISTER((op & THUMB_INSN_IMM_RD) >> THUMB_INSN_IMM_RD_SHIFT, rd);
	HandleThumbALUAddFlags(rd, rn, op2);
}

void arm7_cpu_device::tg03_1(UINT32 pc, UINT32 op) /* SUB Rd, #Offset8 */
{
	UINT32 rn = GET_REGISTER((op & THUMB_INSN_IMM_RD) >> THUMB_INSN_IMM_RD_SHIFT);
	UINT32 op2 = op & THUMB_INSN_IMM;
	UINT32 rd = rn - op2;
	SET_REGISTER((op & THUMB_INSN_IMM_RD) >> THUMB_INSN_IMM_RD_SHIFT, rd);
=======
void arm7_cpu_device::tg03_0(uint32_t pc, uint32_t op) /* ADD Rd, #Offset8 */
{
	uint32_t rn = GetRegister((op & THUMB_INSN_IMM_RD) >> THUMB_INSN_IMM_RD_SHIFT);
	uint32_t op2 = op & THUMB_INSN_IMM;
	uint32_t rd = rn + op2;
	SetRegister((op & THUMB_INSN_IMM_RD) >> THUMB_INSN_IMM_RD_SHIFT, rd);
	HandleThumbALUAddFlags(rd, rn, op2);
}

void arm7_cpu_device::tg03_1(uint32_t pc, uint32_t op) /* SUB Rd, #Offset8 */
{
	uint32_t rn = GetRegister((op & THUMB_INSN_IMM_RD) >> THUMB_INSN_IMM_RD_SHIFT);
	uint32_t op2 = op & THUMB_INSN_IMM;
	uint32_t rd = rn - op2;
	SetRegister((op & THUMB_INSN_IMM_RD) >> THUMB_INSN_IMM_RD_SHIFT, rd);
>>>>>>> upstream/master
	HandleThumbALUSubFlags(rd, rn, op2);
}

	/* Rd & Rm instructions */

<<<<<<< HEAD
void arm7_cpu_device::tg04_00_00(UINT32 pc, UINT32 op) /* AND Rd, Rs */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SET_REGISTER(rd, GET_REGISTER(rd) & GET_REGISTER(rs));
	SET_CPSR(GET_CPSR & ~(Z_MASK | N_MASK));
	SET_CPSR(GET_CPSR | HandleALUNZFlags(GET_REGISTER(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_01(UINT32 pc, UINT32 op) /* EOR Rd, Rs */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SET_REGISTER(rd, GET_REGISTER(rd) ^ GET_REGISTER(rs));
	SET_CPSR(GET_CPSR & ~(Z_MASK | N_MASK));
	SET_CPSR(GET_CPSR | HandleALUNZFlags(GET_REGISTER(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_02(UINT32 pc, UINT32 op) /* LSL Rd, Rs */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	UINT32 rrd = GET_REGISTER(rd);
	INT32 offs = GET_REGISTER(rs) & 0x000000ff;
=======
void arm7_cpu_device::tg04_00_00(uint32_t pc, uint32_t op) /* AND Rd, Rs */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SetRegister(rd, GetRegister(rd) & GetRegister(rs));
	set_cpsr(GET_CPSR & ~(Z_MASK | N_MASK));
	set_cpsr(GET_CPSR | HandleALUNZFlags(GetRegister(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_01(uint32_t pc, uint32_t op) /* EOR Rd, Rs */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SetRegister(rd, GetRegister(rd) ^ GetRegister(rs));
	set_cpsr(GET_CPSR & ~(Z_MASK | N_MASK));
	set_cpsr(GET_CPSR | HandleALUNZFlags(GetRegister(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_02(uint32_t pc, uint32_t op) /* LSL Rd, Rs */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	uint32_t rrd = GetRegister(rd);
	int32_t offs = GetRegister(rs) & 0x000000ff;
>>>>>>> upstream/master
	if (offs > 0)
	{
		if (offs < 32)
		{
<<<<<<< HEAD
			SET_REGISTER(rd, rrd << offs);
			if (rrd & (1 << (31 - (offs - 1))))
			{
				SET_CPSR(GET_CPSR | C_MASK);
			}
			else
			{
				SET_CPSR(GET_CPSR & ~C_MASK);
=======
			SetRegister(rd, rrd << offs);
			if (rrd & (1 << (31 - (offs - 1))))
			{
				set_cpsr(GET_CPSR | C_MASK);
			}
			else
			{
				set_cpsr(GET_CPSR & ~C_MASK);
>>>>>>> upstream/master
			}
		}
		else if (offs == 32)
		{
<<<<<<< HEAD
			SET_REGISTER(rd, 0);
			if (rrd & 1)
			{
				SET_CPSR(GET_CPSR | C_MASK);
			}
			else
			{
				SET_CPSR(GET_CPSR & ~C_MASK);
=======
			SetRegister(rd, 0);
			if (rrd & 1)
			{
				set_cpsr(GET_CPSR | C_MASK);
			}
			else
			{
				set_cpsr(GET_CPSR & ~C_MASK);
>>>>>>> upstream/master
			}
		}
		else
		{
<<<<<<< HEAD
			SET_REGISTER(rd, 0);
			SET_CPSR(GET_CPSR & ~C_MASK);
		}
	}
	SET_CPSR(GET_CPSR & ~(Z_MASK | N_MASK));
	SET_CPSR(GET_CPSR | HandleALUNZFlags(GET_REGISTER(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_03(UINT32 pc, UINT32 op) /* LSR Rd, Rs */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	UINT32 rrd = GET_REGISTER(rd);
	INT32 offs = GET_REGISTER(rs) & 0x000000ff;
=======
			SetRegister(rd, 0);
			set_cpsr(GET_CPSR & ~C_MASK);
		}
	}
	set_cpsr(GET_CPSR & ~(Z_MASK | N_MASK));
	set_cpsr(GET_CPSR | HandleALUNZFlags(GetRegister(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_03(uint32_t pc, uint32_t op) /* LSR Rd, Rs */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	uint32_t rrd = GetRegister(rd);
	int32_t offs = GetRegister(rs) & 0x000000ff;
>>>>>>> upstream/master
	if (offs >  0)
	{
		if (offs < 32)
		{
<<<<<<< HEAD
			SET_REGISTER(rd, rrd >> offs);
			if (rrd & (1 << (offs - 1)))
			{
				SET_CPSR(GET_CPSR | C_MASK);
			}
			else
			{
				SET_CPSR(GET_CPSR & ~C_MASK);
=======
			SetRegister(rd, rrd >> offs);
			if (rrd & (1 << (offs - 1)))
			{
				set_cpsr(GET_CPSR | C_MASK);
			}
			else
			{
				set_cpsr(GET_CPSR & ~C_MASK);
>>>>>>> upstream/master
			}
		}
		else if (offs == 32)
		{
<<<<<<< HEAD
			SET_REGISTER(rd, 0);
			if (rrd & 0x80000000)
			{
				SET_CPSR(GET_CPSR | C_MASK);
			}
			else
			{
				SET_CPSR(GET_CPSR & ~C_MASK);
=======
			SetRegister(rd, 0);
			if (rrd & 0x80000000)
			{
				set_cpsr(GET_CPSR | C_MASK);
			}
			else
			{
				set_cpsr(GET_CPSR & ~C_MASK);
>>>>>>> upstream/master
			}
		}
		else
		{
<<<<<<< HEAD
			SET_REGISTER(rd, 0);
			SET_CPSR(GET_CPSR & ~C_MASK);
		}
	}
	SET_CPSR(GET_CPSR & ~(Z_MASK | N_MASK));
	SET_CPSR(GET_CPSR | HandleALUNZFlags(GET_REGISTER(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_04(UINT32 pc, UINT32 op) /* ASR Rd, Rs */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	UINT32 rrs = GET_REGISTER(rs)&0xff;
	UINT32 rrd = GET_REGISTER(rd);
=======
			SetRegister(rd, 0);
			set_cpsr(GET_CPSR & ~C_MASK);
		}
	}
	set_cpsr(GET_CPSR & ~(Z_MASK | N_MASK));
	set_cpsr(GET_CPSR | HandleALUNZFlags(GetRegister(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_04(uint32_t pc, uint32_t op) /* ASR Rd, Rs */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	uint32_t rrs = GetRegister(rs)&0xff;
	uint32_t rrd = GetRegister(rd);
>>>>>>> upstream/master
	if (rrs != 0)
	{
		if (rrs >= 32)
		{
			if (rrd >> 31)
			{
<<<<<<< HEAD
				SET_CPSR(GET_CPSR | C_MASK);
			}
			else
			{
				SET_CPSR(GET_CPSR & ~C_MASK);
			}
			SET_REGISTER(rd, (GET_REGISTER(rd) & 0x80000000) ? 0xFFFFFFFF : 0x00000000);
=======
				set_cpsr(GET_CPSR | C_MASK);
			}
			else
			{
				set_cpsr(GET_CPSR & ~C_MASK);
			}
			SetRegister(rd, (GetRegister(rd) & 0x80000000) ? 0xFFFFFFFF : 0x00000000);
>>>>>>> upstream/master
		}
		else
		{
			if ((rrd >> (rrs-1)) & 1)
			{
<<<<<<< HEAD
				SET_CPSR(GET_CPSR | C_MASK);
			}
			else
			{
				SET_CPSR(GET_CPSR & ~C_MASK);
			}
			SET_REGISTER(rd, (rrd & 0x80000000)
=======
				set_cpsr(GET_CPSR | C_MASK);
			}
			else
			{
				set_cpsr(GET_CPSR & ~C_MASK);
			}
			SetRegister(rd, (rrd & 0x80000000)
>>>>>>> upstream/master
							? ((0xFFFFFFFF << (32 - rrs)) | (rrd >> rrs))
							: (rrd >> rrs));
		}
	}
<<<<<<< HEAD
	SET_CPSR(GET_CPSR & ~(N_MASK | Z_MASK));
	SET_CPSR(GET_CPSR | HandleALUNZFlags(GET_REGISTER(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_05(UINT32 pc, UINT32 op) /* ADC Rd, Rs */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	UINT32 op2 = (GET_CPSR & C_MASK) ? 1 : 0;
	UINT32 rn = GET_REGISTER(rd) + GET_REGISTER(rs) + op2;
	HandleThumbALUAddFlags(rn, GET_REGISTER(rd), (GET_REGISTER(rs))); // ?
	SET_REGISTER(rd, rn);
}

void arm7_cpu_device::tg04_00_06(UINT32 pc, UINT32 op)  /* SBC Rd, Rs */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	UINT32 op2 = (GET_CPSR & C_MASK) ? 0 : 1;
	UINT32 rn = GET_REGISTER(rd) - GET_REGISTER(rs) - op2;
	HandleThumbALUSubFlags(rn, GET_REGISTER(rd), (GET_REGISTER(rs))); //?
	SET_REGISTER(rd, rn);
}

void arm7_cpu_device::tg04_00_07(UINT32 pc, UINT32 op) /* ROR Rd, Rs */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	UINT32 rrd = GET_REGISTER(rd);
	UINT32 imm = GET_REGISTER(rs) & 0x0000001f;
	SET_REGISTER(rd, (rrd >> imm) | (rrd << (32 - imm)));
	if (rrd & (1 << (imm - 1)))
	{
		SET_CPSR(GET_CPSR | C_MASK);
	}
	else
	{
		SET_CPSR(GET_CPSR & ~C_MASK);
	}
	SET_CPSR(GET_CPSR & ~(Z_MASK | N_MASK));
	SET_CPSR(GET_CPSR | HandleALUNZFlags(GET_REGISTER(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_08(UINT32 pc, UINT32 op) /* TST Rd, Rs */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SET_CPSR(GET_CPSR & ~(Z_MASK | N_MASK));
	SET_CPSR(GET_CPSR | HandleALUNZFlags(GET_REGISTER(rd) & GET_REGISTER(rs)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_09(UINT32 pc, UINT32 op) /* NEG Rd, Rs */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	UINT32 rrs = GET_REGISTER(rs);
	SET_REGISTER(rd, 0 - rrs);
	HandleThumbALUSubFlags(GET_REGISTER(rd), 0, rrs);
}

void arm7_cpu_device::tg04_00_0a(UINT32 pc, UINT32 op) /* CMP Rd, Rs */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	UINT32 rn = GET_REGISTER(rd) - GET_REGISTER(rs);
	HandleThumbALUSubFlags(rn, GET_REGISTER(rd), GET_REGISTER(rs));
}

void arm7_cpu_device::tg04_00_0b(UINT32 pc, UINT32 op) /* CMN Rd, Rs - check flags, add dasm */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	UINT32 rn = GET_REGISTER(rd) + GET_REGISTER(rs);
	HandleThumbALUAddFlags(rn, GET_REGISTER(rd), GET_REGISTER(rs));
}

void arm7_cpu_device::tg04_00_0c(UINT32 pc, UINT32 op) /* ORR Rd, Rs */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SET_REGISTER(rd, GET_REGISTER(rd) | GET_REGISTER(rs));
	SET_CPSR(GET_CPSR & ~(Z_MASK | N_MASK));
	SET_CPSR(GET_CPSR | HandleALUNZFlags(GET_REGISTER(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_0d(UINT32 pc, UINT32 op) /* MUL Rd, Rs */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	UINT32 rn = GET_REGISTER(rd) * GET_REGISTER(rs);
	SET_CPSR(GET_CPSR & ~(Z_MASK | N_MASK));
	SET_REGISTER(rd, rn);
	SET_CPSR(GET_CPSR | HandleALUNZFlags(rn));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_0e(UINT32 pc, UINT32 op) /* BIC Rd, Rs */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SET_REGISTER(rd, GET_REGISTER(rd) & (~GET_REGISTER(rs)));
	SET_CPSR(GET_CPSR & ~(Z_MASK | N_MASK));
	SET_CPSR(GET_CPSR | HandleALUNZFlags(GET_REGISTER(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_0f(UINT32 pc, UINT32 op) /* MVN Rd, Rs */
{
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	UINT32 op2 = GET_REGISTER(rs);
	SET_REGISTER(rd, ~op2);
	SET_CPSR(GET_CPSR & ~(Z_MASK | N_MASK));
	SET_CPSR(GET_CPSR | HandleALUNZFlags(GET_REGISTER(rd)));
=======
	set_cpsr(GET_CPSR & ~(N_MASK | Z_MASK));
	set_cpsr(GET_CPSR | HandleALUNZFlags(GetRegister(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_05(uint32_t pc, uint32_t op) /* ADC Rd, Rs */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	uint32_t op2 = (GET_CPSR & C_MASK) ? 1 : 0;
	uint32_t rn = GetRegister(rd) + GetRegister(rs) + op2;
	HandleThumbALUAddFlags(rn, GetRegister(rd), (GetRegister(rs))); // ?
	SetRegister(rd, rn);
}

void arm7_cpu_device::tg04_00_06(uint32_t pc, uint32_t op)  /* SBC Rd, Rs */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	uint32_t op2 = (GET_CPSR & C_MASK) ? 0 : 1;
	uint32_t rn = GetRegister(rd) - GetRegister(rs) - op2;
	HandleThumbALUSubFlags(rn, GetRegister(rd), (GetRegister(rs))); //?
	SetRegister(rd, rn);
}

void arm7_cpu_device::tg04_00_07(uint32_t pc, uint32_t op) /* ROR Rd, Rs */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	uint32_t rrd = GetRegister(rd);
	uint32_t imm = GetRegister(rs) & 0x0000001f;
	SetRegister(rd, (rrd >> imm) | (rrd << (32 - imm)));
	if (rrd & (1 << (imm - 1)))
	{
		set_cpsr(GET_CPSR | C_MASK);
	}
	else
	{
		set_cpsr(GET_CPSR & ~C_MASK);
	}
	set_cpsr(GET_CPSR & ~(Z_MASK | N_MASK));
	set_cpsr(GET_CPSR | HandleALUNZFlags(GetRegister(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_08(uint32_t pc, uint32_t op) /* TST Rd, Rs */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	set_cpsr(GET_CPSR & ~(Z_MASK | N_MASK));
	set_cpsr(GET_CPSR | HandleALUNZFlags(GetRegister(rd) & GetRegister(rs)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_09(uint32_t pc, uint32_t op) /* NEG Rd, Rs */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	uint32_t rrs = GetRegister(rs);
	SetRegister(rd, 0 - rrs);
	HandleThumbALUSubFlags(GetRegister(rd), 0, rrs);
}

void arm7_cpu_device::tg04_00_0a(uint32_t pc, uint32_t op) /* CMP Rd, Rs */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	uint32_t rn = GetRegister(rd) - GetRegister(rs);
	HandleThumbALUSubFlags(rn, GetRegister(rd), GetRegister(rs));
}

void arm7_cpu_device::tg04_00_0b(uint32_t pc, uint32_t op) /* CMN Rd, Rs - check flags, add dasm */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	uint32_t rn = GetRegister(rd) + GetRegister(rs);
	HandleThumbALUAddFlags(rn, GetRegister(rd), GetRegister(rs));
}

void arm7_cpu_device::tg04_00_0c(uint32_t pc, uint32_t op) /* ORR Rd, Rs */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SetRegister(rd, GetRegister(rd) | GetRegister(rs));
	set_cpsr(GET_CPSR & ~(Z_MASK | N_MASK));
	set_cpsr(GET_CPSR | HandleALUNZFlags(GetRegister(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_0d(uint32_t pc, uint32_t op) /* MUL Rd, Rs */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	uint32_t rn = GetRegister(rd) * GetRegister(rs);
	set_cpsr(GET_CPSR & ~(Z_MASK | N_MASK));
	SetRegister(rd, rn);
	set_cpsr(GET_CPSR | HandleALUNZFlags(rn));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_0e(uint32_t pc, uint32_t op) /* BIC Rd, Rs */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SetRegister(rd, GetRegister(rd) & (~GetRegister(rs)));
	set_cpsr(GET_CPSR & ~(Z_MASK | N_MASK));
	set_cpsr(GET_CPSR | HandleALUNZFlags(GetRegister(rd)));
	R15 += 2;
}

void arm7_cpu_device::tg04_00_0f(uint32_t pc, uint32_t op) /* MVN Rd, Rs */
{
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	uint32_t op2 = GetRegister(rs);
	SetRegister(rd, ~op2);
	set_cpsr(GET_CPSR & ~(Z_MASK | N_MASK));
	set_cpsr(GET_CPSR | HandleALUNZFlags(GetRegister(rd)));
>>>>>>> upstream/master
	R15 += 2;
}

/* ADD Rd, Rs group */

<<<<<<< HEAD
void arm7_cpu_device::tg04_01_00(UINT32 pc, UINT32 op)
=======
void arm7_cpu_device::tg04_01_00(uint32_t pc, uint32_t op)
>>>>>>> upstream/master
{
	fatalerror("%08x: G4-1-0 Undefined Thumb instruction: %04x %x\n", pc, op, (op & THUMB_HIREG_H) >> THUMB_HIREG_H_SHIFT);
}

<<<<<<< HEAD
void arm7_cpu_device::tg04_01_01(UINT32 pc, UINT32 op) /* ADD Rd, HRs */
{
	UINT32 rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	UINT32 rd = op & THUMB_HIREG_RD;
	SET_REGISTER(rd, GET_REGISTER(rd) + GET_REGISTER(rs+8));
	// emulate the effects of pre-fetch
	if (rs == 7)
	{
		SET_REGISTER(rd, GET_REGISTER(rd) + 4);
=======
void arm7_cpu_device::tg04_01_01(uint32_t pc, uint32_t op) /* ADD Rd, HRs */
{
	uint32_t rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	uint32_t rd = op & THUMB_HIREG_RD;
	SetRegister(rd, GetRegister(rd) + GetRegister(rs+8));
	// emulate the effects of pre-fetch
	if (rs == 7)
	{
		SetRegister(rd, GetRegister(rd) + 4);
>>>>>>> upstream/master
	}

	R15 += 2;
}

<<<<<<< HEAD
void arm7_cpu_device::tg04_01_02(UINT32 pc, UINT32 op) /* ADD HRd, Rs */
{
	UINT32 rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	UINT32 rd = op & THUMB_HIREG_RD;
	SET_REGISTER(rd+8, GET_REGISTER(rd+8) + GET_REGISTER(rs));
=======
void arm7_cpu_device::tg04_01_02(uint32_t pc, uint32_t op) /* ADD HRd, Rs */
{
	uint32_t rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	uint32_t rd = op & THUMB_HIREG_RD;
	SetRegister(rd+8, GetRegister(rd+8) + GetRegister(rs));
>>>>>>> upstream/master
	if (rd == 7)
	{
		R15 += 2;
	}

	R15 += 2;
}

<<<<<<< HEAD
void arm7_cpu_device::tg04_01_03(UINT32 pc, UINT32 op) /* Add HRd, HRs */
{
	UINT32 rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	UINT32 rd = op & THUMB_HIREG_RD;
	SET_REGISTER(rd+8, GET_REGISTER(rd+8) + GET_REGISTER(rs+8));
	// emulate the effects of pre-fetch
	if (rs == 7)
	{
		SET_REGISTER(rd+8, GET_REGISTER(rd+8) + 4);
=======
void arm7_cpu_device::tg04_01_03(uint32_t pc, uint32_t op) /* Add HRd, HRs */
{
	uint32_t rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	uint32_t rd = op & THUMB_HIREG_RD;
	SetRegister(rd+8, GetRegister(rd+8) + GetRegister(rs+8));
	// emulate the effects of pre-fetch
	if (rs == 7)
	{
		SetRegister(rd+8, GetRegister(rd+8) + 4);
>>>>>>> upstream/master
	}
	if (rd == 7)
	{
		R15 += 2;
	}

	R15 += 2;
}

<<<<<<< HEAD
void arm7_cpu_device::tg04_01_10(UINT32 pc, UINT32 op)  /* CMP Rd, Rs */
{
	UINT32 rs = GET_REGISTER(((op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT));
	UINT32 rd = GET_REGISTER(op & THUMB_HIREG_RD);
	UINT32 rn = rd - rs;
	HandleThumbALUSubFlags(rn, rd, rs);
}

void arm7_cpu_device::tg04_01_11(UINT32 pc, UINT32 op) /* CMP Rd, Hs */
{
	UINT32 rs = GET_REGISTER(((op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT) + 8);
	UINT32 rd = GET_REGISTER(op & THUMB_HIREG_RD);
	UINT32 rn = rd - rs;
	HandleThumbALUSubFlags(rn, rd, rs);
}

void arm7_cpu_device::tg04_01_12(UINT32 pc, UINT32 op) /* CMP Hd, Rs */
{
	UINT32 rs = GET_REGISTER(((op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT));
	UINT32 rd = GET_REGISTER((op & THUMB_HIREG_RD) + 8);
	UINT32 rn = rd - rs;
	HandleThumbALUSubFlags(rn, rd, rs);
}

void arm7_cpu_device::tg04_01_13(UINT32 pc, UINT32 op) /* CMP Hd, Hs */
{
	UINT32 rs = GET_REGISTER(((op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT) + 8);
	UINT32 rd = GET_REGISTER((op & THUMB_HIREG_RD) + 8);
	UINT32 rn = rd - rs;
=======
void arm7_cpu_device::tg04_01_10(uint32_t pc, uint32_t op)  /* CMP Rd, Rs */
{
	uint32_t rs = GetRegister(((op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT));
	uint32_t rd = GetRegister(op & THUMB_HIREG_RD);
	uint32_t rn = rd - rs;
	HandleThumbALUSubFlags(rn, rd, rs);
}

void arm7_cpu_device::tg04_01_11(uint32_t pc, uint32_t op) /* CMP Rd, Hs */
{
	uint32_t rs = GetRegister(((op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT) + 8);
	uint32_t rd = GetRegister(op & THUMB_HIREG_RD);
	uint32_t rn = rd - rs;
	HandleThumbALUSubFlags(rn, rd, rs);
}

void arm7_cpu_device::tg04_01_12(uint32_t pc, uint32_t op) /* CMP Hd, Rs */
{
	uint32_t rs = GetRegister(((op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT));
	uint32_t rd = GetRegister((op & THUMB_HIREG_RD) + 8);
	uint32_t rn = rd - rs;
	HandleThumbALUSubFlags(rn, rd, rs);
}

void arm7_cpu_device::tg04_01_13(uint32_t pc, uint32_t op) /* CMP Hd, Hs */
{
	uint32_t rs = GetRegister(((op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT) + 8);
	uint32_t rd = GetRegister((op & THUMB_HIREG_RD) + 8);
	uint32_t rn = rd - rs;
>>>>>>> upstream/master
	HandleThumbALUSubFlags(rn, rd, rs);
}

/* MOV group */

// "The action of H1 = 0, H2 = 0 for Op = 00 (ADD), Op = 01 (CMP) and Op = 10 (MOV) is undefined, and should not be used."
<<<<<<< HEAD
void arm7_cpu_device::tg04_01_20(UINT32 pc, UINT32 op) /* MOV Rd, Rs (undefined) */
{
	UINT32 rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	UINT32 rd = op & THUMB_HIREG_RD;
	SET_REGISTER(rd, GET_REGISTER(rs));
	R15 += 2;
}

void arm7_cpu_device::tg04_01_21(UINT32 pc, UINT32 op) /* MOV Rd, Hs */
{
	UINT32 rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	UINT32 rd = op & THUMB_HIREG_RD;
	SET_REGISTER(rd, GET_REGISTER(rs + 8));
	if (rs == 7)
	{
		SET_REGISTER(rd, GET_REGISTER(rd) + 4);
=======
void arm7_cpu_device::tg04_01_20(uint32_t pc, uint32_t op) /* MOV Rd, Rs (undefined) */
{
	uint32_t rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	uint32_t rd = op & THUMB_HIREG_RD;
	SetRegister(rd, GetRegister(rs));
	R15 += 2;
}

void arm7_cpu_device::tg04_01_21(uint32_t pc, uint32_t op) /* MOV Rd, Hs */
{
	uint32_t rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	uint32_t rd = op & THUMB_HIREG_RD;
	SetRegister(rd, GetRegister(rs + 8));
	if (rs == 7)
	{
		SetRegister(rd, GetRegister(rd) + 4);
>>>>>>> upstream/master
	}
	R15 += 2;
}

<<<<<<< HEAD
void arm7_cpu_device::tg04_01_22(UINT32 pc, UINT32 op) /* MOV Hd, Rs */
{
	UINT32 rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	UINT32 rd = op & THUMB_HIREG_RD;
	SET_REGISTER(rd + 8, GET_REGISTER(rs));
=======
void arm7_cpu_device::tg04_01_22(uint32_t pc, uint32_t op) /* MOV Hd, Rs */
{
	uint32_t rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	uint32_t rd = op & THUMB_HIREG_RD;
	SetRegister(rd + 8, GetRegister(rs));
>>>>>>> upstream/master
	if (rd != 7)
	{
		R15 += 2;
	}
	else
	{
		R15 &= ~1;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg04_01_23(UINT32 pc, UINT32 op) /* MOV Hd, Hs */
{
	UINT32 rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	UINT32 rd = op & THUMB_HIREG_RD;
	if (rs == 7)
	{
		SET_REGISTER(rd + 8, GET_REGISTER(rs+8)+4);
	}
	else
	{
		SET_REGISTER(rd + 8, GET_REGISTER(rs+8));
=======
void arm7_cpu_device::tg04_01_23(uint32_t pc, uint32_t op) /* MOV Hd, Hs */
{
	uint32_t rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	uint32_t rd = op & THUMB_HIREG_RD;
	if (rs == 7)
	{
		SetRegister(rd + 8, GetRegister(rs+8)+4);
	}
	else
	{
		SetRegister(rd + 8, GetRegister(rs+8));
>>>>>>> upstream/master
	}
	if (rd != 7)
	{
		R15 += 2;
	}
	else
	{
		R15 &= ~1;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg04_01_30(UINT32 pc, UINT32 op)
{
	UINT32 rd = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	UINT32 addr = GET_REGISTER(rd);
=======
void arm7_cpu_device::tg04_01_30(uint32_t pc, uint32_t op)
{
	uint32_t rd = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	uint32_t addr = GetRegister(rd);
>>>>>>> upstream/master
	if (addr & 1)
	{
		addr &= ~1;
	}
	else
	{
<<<<<<< HEAD
		SET_CPSR(GET_CPSR & ~T_MASK);
=======
		set_cpsr(GET_CPSR & ~T_MASK);
>>>>>>> upstream/master
		if (addr & 2)
		{
			addr += 2;
		}
	}
	R15 = addr;
}

<<<<<<< HEAD
void arm7_cpu_device::tg04_01_31(UINT32 pc, UINT32 op)
{
	UINT32 rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	UINT32 addr = GET_REGISTER(rs+8);
=======
void arm7_cpu_device::tg04_01_31(uint32_t pc, uint32_t op)
{
	uint32_t rs = (op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT;
	uint32_t addr = GetRegister(rs+8);
>>>>>>> upstream/master
	if (rs == 7)
	{
		addr += 2;
	}
	if (addr & 1)
	{
		addr &= ~1;
	}
	else
	{
<<<<<<< HEAD
		SET_CPSR(GET_CPSR & ~T_MASK);
=======
		set_cpsr(GET_CPSR & ~T_MASK);
>>>>>>> upstream/master
		if (addr & 2)
		{
			addr += 2;
		}
	}
	R15 = addr;
}

/* BLX */
<<<<<<< HEAD
void arm7_cpu_device::tg04_01_32(UINT32 pc, UINT32 op)
{
	UINT32 addr = GET_REGISTER((op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT);
	SET_REGISTER(14, (R15 + 2) | 1);
=======
void arm7_cpu_device::tg04_01_32(uint32_t pc, uint32_t op)
{
	uint32_t addr = GetRegister((op & THUMB_HIREG_RS) >> THUMB_HIREG_RS_SHIFT);
	SetRegister(14, (R15 + 2) | 1);
>>>>>>> upstream/master

	// are we also switching to ARM mode?
	if (!(addr & 1))
	{
<<<<<<< HEAD
		SET_CPSR(GET_CPSR & ~T_MASK);
=======
		set_cpsr(GET_CPSR & ~T_MASK);
>>>>>>> upstream/master
		if (addr & 2)
		{
			addr += 2;
		}
	}
	else
	{
		addr &= ~1;
	}

	R15 = addr;
}

<<<<<<< HEAD
void arm7_cpu_device::tg04_01_33(UINT32 pc, UINT32 op)
=======
void arm7_cpu_device::tg04_01_33(uint32_t pc, uint32_t op)
>>>>>>> upstream/master
{
	fatalerror("%08x: G4-3 Undefined Thumb instruction: %04x\n", pc, op);
}

<<<<<<< HEAD
void arm7_cpu_device::tg04_0203(UINT32 pc, UINT32 op)
{
	UINT32 readword = READ32((R15 & ~2) + 4 + ((op & THUMB_INSN_IMM) << 2));
	SET_REGISTER((op & THUMB_INSN_IMM_RD) >> THUMB_INSN_IMM_RD_SHIFT, readword);
=======
void arm7_cpu_device::tg04_0203(uint32_t pc, uint32_t op)
{
	uint32_t readword = READ32((R15 & ~2) + 4 + ((op & THUMB_INSN_IMM) << 2));
	SetRegister((op & THUMB_INSN_IMM_RD) >> THUMB_INSN_IMM_RD_SHIFT, readword);
>>>>>>> upstream/master
	R15 += 2;
}

/* LDR* STR* group */

<<<<<<< HEAD
void arm7_cpu_device::tg05_0(UINT32 pc, UINT32 op)  /* STR Rd, [Rn, Rm] */
{
	UINT32 rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	UINT32 rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	UINT32 rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	UINT32 addr = GET_REGISTER(rn) + GET_REGISTER(rm);
	WRITE32(addr, GET_REGISTER(rd));
	R15 += 2;
}

void arm7_cpu_device::tg05_1(UINT32 pc, UINT32 op)  /* STRH Rd, [Rn, Rm] */
{
	UINT32 rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	UINT32 rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	UINT32 rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	UINT32 addr = GET_REGISTER(rn) + GET_REGISTER(rm);
	WRITE16(addr, GET_REGISTER(rd));
	R15 += 2;
}

void arm7_cpu_device::tg05_2(UINT32 pc, UINT32 op)  /* STRB Rd, [Rn, Rm] */
{
	UINT32 rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	UINT32 rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	UINT32 rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	UINT32 addr = GET_REGISTER(rn) + GET_REGISTER(rm);
	WRITE8(addr, GET_REGISTER(rd));
	R15 += 2;
}

void arm7_cpu_device::tg05_3(UINT32 pc, UINT32 op)  /* LDSB Rd, [Rn, Rm] todo, add dasm */
{
	UINT32 rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	UINT32 rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	UINT32 rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	UINT32 addr = GET_REGISTER(rn) + GET_REGISTER(rm);
	UINT32 op2 = READ8(addr);
=======
void arm7_cpu_device::tg05_0(uint32_t pc, uint32_t op)  /* STR Rd, [Rn, Rm] */
{
	uint32_t rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	uint32_t rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	uint32_t rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	uint32_t addr = GetRegister(rn) + GetRegister(rm);
	WRITE32(addr, GetRegister(rd));
	R15 += 2;
}

void arm7_cpu_device::tg05_1(uint32_t pc, uint32_t op)  /* STRH Rd, [Rn, Rm] */
{
	uint32_t rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	uint32_t rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	uint32_t rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	uint32_t addr = GetRegister(rn) + GetRegister(rm);
	WRITE16(addr, GetRegister(rd));
	R15 += 2;
}

void arm7_cpu_device::tg05_2(uint32_t pc, uint32_t op)  /* STRB Rd, [Rn, Rm] */
{
	uint32_t rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	uint32_t rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	uint32_t rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	uint32_t addr = GetRegister(rn) + GetRegister(rm);
	WRITE8(addr, GetRegister(rd));
	R15 += 2;
}

void arm7_cpu_device::tg05_3(uint32_t pc, uint32_t op)  /* LDSB Rd, [Rn, Rm] todo, add dasm */
{
	uint32_t rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	uint32_t rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	uint32_t rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	uint32_t addr = GetRegister(rn) + GetRegister(rm);
	uint32_t op2 = READ8(addr);
>>>>>>> upstream/master
	if (op2 & 0x00000080)
	{
		op2 |= 0xffffff00;
	}
<<<<<<< HEAD
	SET_REGISTER(rd, op2);
	R15 += 2;
}

void arm7_cpu_device::tg05_4(UINT32 pc, UINT32 op)  /* LDR Rd, [Rn, Rm] */
{
	UINT32 rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	UINT32 rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	UINT32 rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	UINT32 addr = GET_REGISTER(rn) + GET_REGISTER(rm);
	UINT32 op2 = READ32(addr);
	SET_REGISTER(rd, op2);
	R15 += 2;
}

void arm7_cpu_device::tg05_5(UINT32 pc, UINT32 op)  /* LDRH Rd, [Rn, Rm] */
{
	UINT32 rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	UINT32 rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	UINT32 rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	UINT32 addr = GET_REGISTER(rn) + GET_REGISTER(rm);
	UINT32 op2 = READ16(addr);
	SET_REGISTER(rd, op2);
	R15 += 2;
}

void arm7_cpu_device::tg05_6(UINT32 pc, UINT32 op)  /* LDRB Rd, [Rn, Rm] */
{
	UINT32 rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	UINT32 rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	UINT32 rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	UINT32 addr = GET_REGISTER(rn) + GET_REGISTER(rm);
	UINT32 op2 = READ8(addr);
	SET_REGISTER(rd, op2);
	R15 += 2;
}

void arm7_cpu_device::tg05_7(UINT32 pc, UINT32 op)  /* LDSH Rd, [Rn, Rm] */
{
	UINT32 rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	UINT32 rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	UINT32 rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	UINT32 addr = GET_REGISTER(rn) + GET_REGISTER(rm);
	UINT32 op2 = READ16(addr);
=======
	SetRegister(rd, op2);
	R15 += 2;
}

void arm7_cpu_device::tg05_4(uint32_t pc, uint32_t op)  /* LDR Rd, [Rn, Rm] */
{
	uint32_t rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	uint32_t rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	uint32_t rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	uint32_t addr = GetRegister(rn) + GetRegister(rm);
	uint32_t op2 = READ32(addr);
	SetRegister(rd, op2);
	R15 += 2;
}

void arm7_cpu_device::tg05_5(uint32_t pc, uint32_t op)  /* LDRH Rd, [Rn, Rm] */
{
	uint32_t rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	uint32_t rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	uint32_t rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	uint32_t addr = GetRegister(rn) + GetRegister(rm);
	uint32_t op2 = READ16(addr);
	SetRegister(rd, op2);
	R15 += 2;
}

void arm7_cpu_device::tg05_6(uint32_t pc, uint32_t op)  /* LDRB Rd, [Rn, Rm] */
{
	uint32_t rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	uint32_t rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	uint32_t rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	uint32_t addr = GetRegister(rn) + GetRegister(rm);
	uint32_t op2 = READ8(addr);
	SetRegister(rd, op2);
	R15 += 2;
}

void arm7_cpu_device::tg05_7(uint32_t pc, uint32_t op)  /* LDSH Rd, [Rn, Rm] */
{
	uint32_t rm = (op & THUMB_GROUP5_RM) >> THUMB_GROUP5_RM_SHIFT;
	uint32_t rn = (op & THUMB_GROUP5_RN) >> THUMB_GROUP5_RN_SHIFT;
	uint32_t rd = (op & THUMB_GROUP5_RD) >> THUMB_GROUP5_RD_SHIFT;
	uint32_t addr = GetRegister(rn) + GetRegister(rm);
	uint32_t op2 = READ16(addr);
>>>>>>> upstream/master
	if (op2 & 0x00008000)
	{
		op2 |= 0xffff0000;
	}
<<<<<<< HEAD
	SET_REGISTER(rd, op2);
=======
	SetRegister(rd, op2);
>>>>>>> upstream/master
	R15 += 2;
}

	/* Word Store w/ Immediate Offset */

<<<<<<< HEAD
void arm7_cpu_device::tg06_0(UINT32 pc, UINT32 op) /* Store */
{
	UINT32 rn = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = op & THUMB_ADDSUB_RD;
	INT32 offs = ((op & THUMB_LSOP_OFFS) >> THUMB_LSOP_OFFS_SHIFT) << 2;
	WRITE32(GET_REGISTER(rn) + offs, GET_REGISTER(rd));
	R15 += 2;
}

void arm7_cpu_device::tg06_1(UINT32 pc, UINT32 op) /* Load */
{
	UINT32 rn = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = op & THUMB_ADDSUB_RD;
	INT32 offs = ((op & THUMB_LSOP_OFFS) >> THUMB_LSOP_OFFS_SHIFT) << 2;
	SET_REGISTER(rd, READ32(GET_REGISTER(rn) + offs)); // fix
=======
void arm7_cpu_device::tg06_0(uint32_t pc, uint32_t op) /* Store */
{
	uint32_t rn = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = op & THUMB_ADDSUB_RD;
	int32_t offs = ((op & THUMB_LSOP_OFFS) >> THUMB_LSOP_OFFS_SHIFT) << 2;
	WRITE32(GetRegister(rn) + offs, GetRegister(rd));
	R15 += 2;
}

void arm7_cpu_device::tg06_1(uint32_t pc, uint32_t op) /* Load */
{
	uint32_t rn = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = op & THUMB_ADDSUB_RD;
	int32_t offs = ((op & THUMB_LSOP_OFFS) >> THUMB_LSOP_OFFS_SHIFT) << 2;
	SetRegister(rd, READ32(GetRegister(rn) + offs)); // fix
>>>>>>> upstream/master
	R15 += 2;
}

/* Byte Store w/ Immeidate Offset */

<<<<<<< HEAD
void arm7_cpu_device::tg07_0(UINT32 pc, UINT32 op) /* Store */
{
	UINT32 rn = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = op & THUMB_ADDSUB_RD;
	INT32 offs = (op & THUMB_LSOP_OFFS) >> THUMB_LSOP_OFFS_SHIFT;
	WRITE8(GET_REGISTER(rn) + offs, GET_REGISTER(rd));
	R15 += 2;
}

void arm7_cpu_device::tg07_1(UINT32 pc, UINT32 op)  /* Load */
{
	UINT32 rn = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = op & THUMB_ADDSUB_RD;
	INT32 offs = (op & THUMB_LSOP_OFFS) >> THUMB_LSOP_OFFS_SHIFT;
	SET_REGISTER(rd, READ8(GET_REGISTER(rn) + offs));
=======
void arm7_cpu_device::tg07_0(uint32_t pc, uint32_t op) /* Store */
{
	uint32_t rn = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = op & THUMB_ADDSUB_RD;
	int32_t offs = (op & THUMB_LSOP_OFFS) >> THUMB_LSOP_OFFS_SHIFT;
	WRITE8(GetRegister(rn) + offs, GetRegister(rd));
	R15 += 2;
}

void arm7_cpu_device::tg07_1(uint32_t pc, uint32_t op)  /* Load */
{
	uint32_t rn = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = op & THUMB_ADDSUB_RD;
	int32_t offs = (op & THUMB_LSOP_OFFS) >> THUMB_LSOP_OFFS_SHIFT;
	SetRegister(rd, READ8(GetRegister(rn) + offs));
>>>>>>> upstream/master
	R15 += 2;
}

/* Load/Store Halfword */

<<<<<<< HEAD
void arm7_cpu_device::tg08_0(UINT32 pc, UINT32 op) /* Store */
{
	UINT32 imm = (op & THUMB_HALFOP_OFFS) >> THUMB_HALFOP_OFFS_SHIFT;
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	WRITE16(GET_REGISTER(rs) + (imm << 1), GET_REGISTER(rd));
	R15 += 2;
}

void arm7_cpu_device::tg08_1(UINT32 pc, UINT32 op) /* Load */
{
	UINT32 imm = (op & THUMB_HALFOP_OFFS) >> THUMB_HALFOP_OFFS_SHIFT;
	UINT32 rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	UINT32 rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SET_REGISTER(rd, READ16(GET_REGISTER(rs) + (imm << 1)));
=======
void arm7_cpu_device::tg08_0(uint32_t pc, uint32_t op) /* Store */
{
	uint32_t imm = (op & THUMB_HALFOP_OFFS) >> THUMB_HALFOP_OFFS_SHIFT;
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	WRITE16(GetRegister(rs) + (imm << 1), GetRegister(rd));
	R15 += 2;
}

void arm7_cpu_device::tg08_1(uint32_t pc, uint32_t op) /* Load */
{
	uint32_t imm = (op & THUMB_HALFOP_OFFS) >> THUMB_HALFOP_OFFS_SHIFT;
	uint32_t rs = (op & THUMB_ADDSUB_RS) >> THUMB_ADDSUB_RS_SHIFT;
	uint32_t rd = (op & THUMB_ADDSUB_RD) >> THUMB_ADDSUB_RD_SHIFT;
	SetRegister(rd, READ16(GetRegister(rs) + (imm << 1)));
>>>>>>> upstream/master
	R15 += 2;
}

/* Stack-Relative Load/Store */

<<<<<<< HEAD
void arm7_cpu_device::tg09_0(UINT32 pc, UINT32 op) /* Store */
{
	UINT32 rd = (op & THUMB_STACKOP_RD) >> THUMB_STACKOP_RD_SHIFT;
	INT32 offs = (UINT8)(op & THUMB_INSN_IMM);
	WRITE32(GET_REGISTER(13) + ((UINT32)offs << 2), GET_REGISTER(rd));
	R15 += 2;
}

void arm7_cpu_device::tg09_1(UINT32 pc, UINT32 op) /* Load */
{
	UINT32 rd = (op & THUMB_STACKOP_RD) >> THUMB_STACKOP_RD_SHIFT;
	INT32 offs = (UINT8)(op & THUMB_INSN_IMM);
	UINT32 readword = READ32(GET_REGISTER(13) + ((UINT32)offs << 2));
	SET_REGISTER(rd, readword);
=======
void arm7_cpu_device::tg09_0(uint32_t pc, uint32_t op) /* Store */
{
	uint32_t rd = (op & THUMB_STACKOP_RD) >> THUMB_STACKOP_RD_SHIFT;
	int32_t offs = (uint8_t)(op & THUMB_INSN_IMM);
	WRITE32(GetRegister(13) + ((uint32_t)offs << 2), GetRegister(rd));
	R15 += 2;
}

void arm7_cpu_device::tg09_1(uint32_t pc, uint32_t op) /* Load */
{
	uint32_t rd = (op & THUMB_STACKOP_RD) >> THUMB_STACKOP_RD_SHIFT;
	int32_t offs = (uint8_t)(op & THUMB_INSN_IMM);
	uint32_t readword = READ32(GetRegister(13) + ((uint32_t)offs << 2));
	SetRegister(rd, readword);
>>>>>>> upstream/master
	R15 += 2;
}

/* Get relative address */

<<<<<<< HEAD
void arm7_cpu_device::tg0a_0(UINT32 pc, UINT32 op)  /* ADD Rd, PC, #nn */
{
	UINT32 rd = (op & THUMB_RELADDR_RD) >> THUMB_RELADDR_RD_SHIFT;
	INT32 offs = (UINT8)(op & THUMB_INSN_IMM) << 2;
	SET_REGISTER(rd, ((R15 + 4) & ~2) + offs);
	R15 += 2;
}

void arm7_cpu_device::tg0a_1(UINT32 pc, UINT32 op) /* ADD Rd, SP, #nn */
{
	UINT32 rd = (op & THUMB_RELADDR_RD) >> THUMB_RELADDR_RD_SHIFT;
	INT32 offs = (UINT8)(op & THUMB_INSN_IMM) << 2;
	SET_REGISTER(rd, GET_REGISTER(13) + offs);
=======
void arm7_cpu_device::tg0a_0(uint32_t pc, uint32_t op)  /* ADD Rd, PC, #nn */
{
	uint32_t rd = (op & THUMB_RELADDR_RD) >> THUMB_RELADDR_RD_SHIFT;
	int32_t offs = (uint8_t)(op & THUMB_INSN_IMM) << 2;
	SetRegister(rd, ((R15 + 4) & ~2) + offs);
	R15 += 2;
}

void arm7_cpu_device::tg0a_1(uint32_t pc, uint32_t op) /* ADD Rd, SP, #nn */
{
	uint32_t rd = (op & THUMB_RELADDR_RD) >> THUMB_RELADDR_RD_SHIFT;
	int32_t offs = (uint8_t)(op & THUMB_INSN_IMM) << 2;
	SetRegister(rd, GetRegister(13) + offs);
>>>>>>> upstream/master
	R15 += 2;
}

	/* Stack-Related Opcodes */

<<<<<<< HEAD
void arm7_cpu_device::tg0b_0(UINT32 pc, UINT32 op) /* ADD SP, #imm */
{
	UINT32 addr = (op & THUMB_INSN_IMM);
	addr &= ~THUMB_INSN_IMM_S;
	SET_REGISTER(13, GET_REGISTER(13) + ((op & THUMB_INSN_IMM_S) ? -(addr << 2) : (addr << 2)));
	R15 += 2;
}

void arm7_cpu_device::tg0b_1(UINT32 pc, UINT32 op)
=======
void arm7_cpu_device::tg0b_0(uint32_t pc, uint32_t op) /* ADD SP, #imm */
{
	uint32_t addr = (op & THUMB_INSN_IMM);
	addr &= ~THUMB_INSN_IMM_S;
	SetRegister(13, GetRegister(13) + ((op & THUMB_INSN_IMM_S) ? -(addr << 2) : (addr << 2)));
	R15 += 2;
}

void arm7_cpu_device::tg0b_1(uint32_t pc, uint32_t op)
>>>>>>> upstream/master
{
	fatalerror("%08x: Gb Undefined Thumb instruction: %04x\n", pc, op);
}

<<<<<<< HEAD
void arm7_cpu_device::tg0b_2(UINT32 pc, UINT32 op)
=======
void arm7_cpu_device::tg0b_2(uint32_t pc, uint32_t op)
>>>>>>> upstream/master
{
	fatalerror("%08x: Gb Undefined Thumb instruction: %04x\n", pc, op);
}

<<<<<<< HEAD
void arm7_cpu_device::tg0b_3(UINT32 pc, UINT32 op)
=======
void arm7_cpu_device::tg0b_3(uint32_t pc, uint32_t op)
>>>>>>> upstream/master
{
	fatalerror("%08x: Gb Undefined Thumb instruction: %04x\n", pc, op);
}

<<<<<<< HEAD
void arm7_cpu_device::tg0b_4(UINT32 pc, UINT32 op) /* PUSH {Rlist} */
{
	for (INT32 offs = 7; offs >= 0; offs--)
	{
		if (op & (1 << offs))
		{
			SET_REGISTER(13, GET_REGISTER(13) - 4);
			WRITE32(GET_REGISTER(13), GET_REGISTER(offs));
=======
void arm7_cpu_device::tg0b_4(uint32_t pc, uint32_t op) /* PUSH {Rlist} */
{
	for (int32_t offs = 7; offs >= 0; offs--)
	{
		if (op & (1 << offs))
		{
			SetRegister(13, GetRegister(13) - 4);
			WRITE32(GetRegister(13), GetRegister(offs));
>>>>>>> upstream/master
		}
	}
	R15 += 2;
}

<<<<<<< HEAD
void arm7_cpu_device::tg0b_5(UINT32 pc, UINT32 op) /* PUSH {Rlist}{LR} */
{
	SET_REGISTER(13, GET_REGISTER(13) - 4);
	WRITE32(GET_REGISTER(13), GET_REGISTER(14));
	for (INT32 offs = 7; offs >= 0; offs--)
	{
		if (op & (1 << offs))
		{
			SET_REGISTER(13, GET_REGISTER(13) - 4);
			WRITE32(GET_REGISTER(13), GET_REGISTER(offs));
=======
void arm7_cpu_device::tg0b_5(uint32_t pc, uint32_t op) /* PUSH {Rlist}{LR} */
{
	SetRegister(13, GetRegister(13) - 4);
	WRITE32(GetRegister(13), GetRegister(14));
	for (int32_t offs = 7; offs >= 0; offs--)
	{
		if (op & (1 << offs))
		{
			SetRegister(13, GetRegister(13) - 4);
			WRITE32(GetRegister(13), GetRegister(offs));
>>>>>>> upstream/master
		}
	}
	R15 += 2;
}

<<<<<<< HEAD
void arm7_cpu_device::tg0b_6(UINT32 pc, UINT32 op)
=======
void arm7_cpu_device::tg0b_6(uint32_t pc, uint32_t op)
>>>>>>> upstream/master
{
	fatalerror("%08x: Gb Undefined Thumb instruction: %04x\n", pc, op);
}

<<<<<<< HEAD
void arm7_cpu_device::tg0b_7(UINT32 pc, UINT32 op)
=======
void arm7_cpu_device::tg0b_7(uint32_t pc, uint32_t op)
>>>>>>> upstream/master
{
	fatalerror("%08x: Gb Undefined Thumb instruction: %04x\n", pc, op);
}

<<<<<<< HEAD
void arm7_cpu_device::tg0b_8(UINT32 pc, UINT32 op)
=======
void arm7_cpu_device::tg0b_8(uint32_t pc, uint32_t op)
>>>>>>> upstream/master
{
	fatalerror("%08x: Gb Undefined Thumb instruction: %04x\n", pc, op);
}

<<<<<<< HEAD
void arm7_cpu_device::tg0b_9(UINT32 pc, UINT32 op)
=======
void arm7_cpu_device::tg0b_9(uint32_t pc, uint32_t op)
>>>>>>> upstream/master
{
	fatalerror("%08x: Gb Undefined Thumb instruction: %04x\n", pc, op);
}

<<<<<<< HEAD
void arm7_cpu_device::tg0b_a(UINT32 pc, UINT32 op)
=======
void arm7_cpu_device::tg0b_a(uint32_t pc, uint32_t op)
>>>>>>> upstream/master
{
	fatalerror("%08x: Gb Undefined Thumb instruction: %04x\n", pc, op);
}

<<<<<<< HEAD
void arm7_cpu_device::tg0b_b(UINT32 pc, UINT32 op)
=======
void arm7_cpu_device::tg0b_b(uint32_t pc, uint32_t op)
>>>>>>> upstream/master
{
	fatalerror("%08x: Gb Undefined Thumb instruction: %04x\n", pc, op);
}

<<<<<<< HEAD
void arm7_cpu_device::tg0b_c(UINT32 pc, UINT32 op) /* POP {Rlist} */
{
	for (INT32 offs = 0; offs < 8; offs++)
	{
		if (op & (1 << offs))
		{
			SET_REGISTER(offs, READ32(GET_REGISTER(13)));
			SET_REGISTER(13, GET_REGISTER(13) + 4);
=======
void arm7_cpu_device::tg0b_c(uint32_t pc, uint32_t op) /* POP {Rlist} */
{
	for (int32_t offs = 0; offs < 8; offs++)
	{
		if (op & (1 << offs))
		{
			SetRegister(offs, READ32(GetRegister(13)));
			SetRegister(13, GetRegister(13) + 4);
>>>>>>> upstream/master
		}
	}
	R15 += 2;
}

<<<<<<< HEAD
void arm7_cpu_device::tg0b_d(UINT32 pc, UINT32 op) /* POP {Rlist}{PC} */
{
	for (INT32 offs = 0; offs < 8; offs++)
	{
		if (op & (1 << offs))
		{
			SET_REGISTER(offs, READ32(GET_REGISTER(13)));
			SET_REGISTER(13, GET_REGISTER(13) + 4);
		}
	}
	UINT32 addr = READ32(GET_REGISTER(13));
=======
void arm7_cpu_device::tg0b_d(uint32_t pc, uint32_t op) /* POP {Rlist}{PC} */
{
	for (int32_t offs = 0; offs < 8; offs++)
	{
		if (op & (1 << offs))
		{
			SetRegister(offs, READ32(GetRegister(13)));
			SetRegister(13, GetRegister(13) + 4);
		}
	}
	uint32_t addr = READ32(GetRegister(13));
>>>>>>> upstream/master
	if (m_archRev < 5)
	{
		R15 = addr & ~1;
	}
	else
	{
		if (addr & 1)
		{
			addr &= ~1;
		}
		else
		{
<<<<<<< HEAD
			SET_CPSR(GET_CPSR & ~T_MASK);
=======
			set_cpsr(GET_CPSR & ~T_MASK);
>>>>>>> upstream/master
			if (addr & 2)
			{
				addr += 2;
			}
		}

		R15 = addr;
	}
<<<<<<< HEAD
	SET_REGISTER(13, GET_REGISTER(13) + 4);
}

void arm7_cpu_device::tg0b_e(UINT32 pc, UINT32 op)
=======
	SetRegister(13, GetRegister(13) + 4);
}

void arm7_cpu_device::tg0b_e(uint32_t pc, uint32_t op)
>>>>>>> upstream/master
{
	fatalerror("%08x: Gb Undefined Thumb instruction: %04x\n", pc, op);
}

<<<<<<< HEAD
void arm7_cpu_device::tg0b_f(UINT32 pc, UINT32 op)
=======
void arm7_cpu_device::tg0b_f(uint32_t pc, uint32_t op)
>>>>>>> upstream/master
{
	fatalerror("%08x: Gb Undefined Thumb instruction: %04x\n", pc, op);
}

/* Multiple Load/Store */

// "The address should normally be a word aligned quantity and non-word aligned addresses do not affect the instruction."
// "However, the bottom 2 bits of the address will appear on A[1:0] and might be interpreted by the memory system."

// GBA "BB Ball" performs an unaligned read with A[1:0] = 2 and expects A[1] not to be ignored [BP 800B90A,(R4&3)!=0]
// GBA "Gadget Racers" performs an unaligned read with A[1:0] = 1 and expects A[0] to be ignored [BP B72,(R0&3)!=0]

<<<<<<< HEAD
void arm7_cpu_device::tg0c_0(UINT32 pc, UINT32 op) /* Store */
{
	UINT32 rd = (op & THUMB_MULTLS_BASE) >> THUMB_MULTLS_BASE_SHIFT;
	UINT32 ld_st_address = GET_REGISTER(rd);
	for (INT32 offs = 0; offs < 8; offs++)
	{
		if (op & (1 << offs))
		{
			WRITE32(ld_st_address & ~3, GET_REGISTER(offs));
			ld_st_address += 4;
		}
	}
	SET_REGISTER(rd, ld_st_address);
	R15 += 2;
}

void arm7_cpu_device::tg0c_1(UINT32 pc, UINT32 op) /* Load */
{
	UINT32 rd = (op & THUMB_MULTLS_BASE) >> THUMB_MULTLS_BASE_SHIFT;
	int rd_in_list = op & (1 << rd);
	UINT32 ld_st_address = GET_REGISTER(rd);
	for (INT32 offs = 0; offs < 8; offs++)
	{
		if (op & (1 << offs))
		{
			SET_REGISTER(offs, READ32(ld_st_address & ~1));
=======
void arm7_cpu_device::tg0c_0(uint32_t pc, uint32_t op) /* Store */
{
	uint32_t rd = (op & THUMB_MULTLS_BASE) >> THUMB_MULTLS_BASE_SHIFT;
	uint32_t ld_st_address = GetRegister(rd);
	for (int32_t offs = 0; offs < 8; offs++)
	{
		if (op & (1 << offs))
		{
			WRITE32(ld_st_address & ~3, GetRegister(offs));
			ld_st_address += 4;
		}
	}
	SetRegister(rd, ld_st_address);
	R15 += 2;
}

void arm7_cpu_device::tg0c_1(uint32_t pc, uint32_t op) /* Load */
{
	uint32_t rd = (op & THUMB_MULTLS_BASE) >> THUMB_MULTLS_BASE_SHIFT;
	int rd_in_list = op & (1 << rd);
	uint32_t ld_st_address = GetRegister(rd);
	for (int32_t offs = 0; offs < 8; offs++)
	{
		if (op & (1 << offs))
		{
			SetRegister(offs, READ32(ld_st_address & ~1));
>>>>>>> upstream/master
			ld_st_address += 4;
		}
	}
	if (!rd_in_list)
	{
<<<<<<< HEAD
		SET_REGISTER(rd, ld_st_address);
=======
		SetRegister(rd, ld_st_address);
>>>>>>> upstream/master
	}
	R15 += 2;
}

/* Conditional Branch */

<<<<<<< HEAD
void arm7_cpu_device::tg0d_0(UINT32 pc, UINT32 op) // COND_EQ:
{
	INT32 offs = (INT8)(op & THUMB_INSN_IMM);
=======
void arm7_cpu_device::tg0d_0(uint32_t pc, uint32_t op) // COND_EQ:
{
	int32_t offs = (int8_t)(op & THUMB_INSN_IMM);
>>>>>>> upstream/master
	if (Z_IS_SET(GET_CPSR))
	{
		R15 += 4 + (offs << 1);
	}
	else
	{
		R15 += 2;
	}

}

<<<<<<< HEAD
void arm7_cpu_device::tg0d_1(UINT32 pc, UINT32 op) // COND_NE:
{
	INT32 offs = (INT8)(op & THUMB_INSN_IMM);
=======
void arm7_cpu_device::tg0d_1(uint32_t pc, uint32_t op) // COND_NE:
{
	int32_t offs = (int8_t)(op & THUMB_INSN_IMM);
>>>>>>> upstream/master
	if (Z_IS_CLEAR(GET_CPSR))
	{
		R15 += 4 + (offs << 1);
	}
	else
	{
		R15 += 2;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg0d_2(UINT32 pc, UINT32 op) // COND_CS:
{
	INT32 offs = (INT8)(op & THUMB_INSN_IMM);
=======
void arm7_cpu_device::tg0d_2(uint32_t pc, uint32_t op) // COND_CS:
{
	int32_t offs = (int8_t)(op & THUMB_INSN_IMM);
>>>>>>> upstream/master
	if (C_IS_SET(GET_CPSR))
	{
		R15 += 4 + (offs << 1);
	}
	else
	{
		R15 += 2;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg0d_3(UINT32 pc, UINT32 op) // COND_CC:
{
	INT32 offs = (INT8)(op & THUMB_INSN_IMM);
=======
void arm7_cpu_device::tg0d_3(uint32_t pc, uint32_t op) // COND_CC:
{
	int32_t offs = (int8_t)(op & THUMB_INSN_IMM);
>>>>>>> upstream/master
	if (C_IS_CLEAR(GET_CPSR))
	{
		R15 += 4 + (offs << 1);
	}
	else
	{
		R15 += 2;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg0d_4(UINT32 pc, UINT32 op) // COND_MI:
{
	INT32 offs = (INT8)(op & THUMB_INSN_IMM);
=======
void arm7_cpu_device::tg0d_4(uint32_t pc, uint32_t op) // COND_MI:
{
	int32_t offs = (int8_t)(op & THUMB_INSN_IMM);
>>>>>>> upstream/master
	if (N_IS_SET(GET_CPSR))
	{
		R15 += 4 + (offs << 1);
	}
	else
	{
		R15 += 2;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg0d_5(UINT32 pc, UINT32 op) // COND_PL:
{
	INT32 offs = (INT8)(op & THUMB_INSN_IMM);
=======
void arm7_cpu_device::tg0d_5(uint32_t pc, uint32_t op) // COND_PL:
{
	int32_t offs = (int8_t)(op & THUMB_INSN_IMM);
>>>>>>> upstream/master
	if (N_IS_CLEAR(GET_CPSR))
	{
		R15 += 4 + (offs << 1);
	}
	else
	{
		R15 += 2;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg0d_6(UINT32 pc, UINT32 op) // COND_VS:
{
	INT32 offs = (INT8)(op & THUMB_INSN_IMM);
=======
void arm7_cpu_device::tg0d_6(uint32_t pc, uint32_t op) // COND_VS:
{
	int32_t offs = (int8_t)(op & THUMB_INSN_IMM);
>>>>>>> upstream/master
	if (V_IS_SET(GET_CPSR))
	{
		R15 += 4 + (offs << 1);
	}
	else
	{
		R15 += 2;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg0d_7(UINT32 pc, UINT32 op) // COND_VC:
{
	INT32 offs = (INT8)(op & THUMB_INSN_IMM);
=======
void arm7_cpu_device::tg0d_7(uint32_t pc, uint32_t op) // COND_VC:
{
	int32_t offs = (int8_t)(op & THUMB_INSN_IMM);
>>>>>>> upstream/master
	if (V_IS_CLEAR(GET_CPSR))
	{
		R15 += 4 + (offs << 1);
	}
	else
	{
		R15 += 2;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg0d_8(UINT32 pc, UINT32 op) // COND_HI:
{
	INT32 offs = (INT8)(op & THUMB_INSN_IMM);
=======
void arm7_cpu_device::tg0d_8(uint32_t pc, uint32_t op) // COND_HI:
{
	int32_t offs = (int8_t)(op & THUMB_INSN_IMM);
>>>>>>> upstream/master
	if (C_IS_SET(GET_CPSR) && Z_IS_CLEAR(GET_CPSR))
	{
		R15 += 4 + (offs << 1);
	}
	else
	{
		R15 += 2;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg0d_9(UINT32 pc, UINT32 op) // COND_LS:
{
	INT32 offs = (INT8)(op & THUMB_INSN_IMM);
=======
void arm7_cpu_device::tg0d_9(uint32_t pc, uint32_t op) // COND_LS:
{
	int32_t offs = (int8_t)(op & THUMB_INSN_IMM);
>>>>>>> upstream/master
	if (C_IS_CLEAR(GET_CPSR) || Z_IS_SET(GET_CPSR))
	{
		R15 += 4 + (offs << 1);
	}
	else
	{
		R15 += 2;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg0d_a(UINT32 pc, UINT32 op) // COND_GE:
{
	INT32 offs = (INT8)(op & THUMB_INSN_IMM);
=======
void arm7_cpu_device::tg0d_a(uint32_t pc, uint32_t op) // COND_GE:
{
	int32_t offs = (int8_t)(op & THUMB_INSN_IMM);
>>>>>>> upstream/master
	if (!(GET_CPSR & N_MASK) == !(GET_CPSR & V_MASK))
	{
		R15 += 4 + (offs << 1);
	}
	else
	{
		R15 += 2;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg0d_b(UINT32 pc, UINT32 op) // COND_LT:
{
	INT32 offs = (INT8)(op & THUMB_INSN_IMM);
=======
void arm7_cpu_device::tg0d_b(uint32_t pc, uint32_t op) // COND_LT:
{
	int32_t offs = (int8_t)(op & THUMB_INSN_IMM);
>>>>>>> upstream/master
	if (!(GET_CPSR & N_MASK) != !(GET_CPSR & V_MASK))
	{
		R15 += 4 + (offs << 1);
	}
	else
	{
		R15 += 2;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg0d_c(UINT32 pc, UINT32 op) // COND_GT:
{
	INT32 offs = (INT8)(op & THUMB_INSN_IMM);
=======
void arm7_cpu_device::tg0d_c(uint32_t pc, uint32_t op) // COND_GT:
{
	int32_t offs = (int8_t)(op & THUMB_INSN_IMM);
>>>>>>> upstream/master
	if (Z_IS_CLEAR(GET_CPSR) && !(GET_CPSR & N_MASK) == !(GET_CPSR & V_MASK))
	{
		R15 += 4 + (offs << 1);
	}
	else
	{
		R15 += 2;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg0d_d(UINT32 pc, UINT32 op) // COND_LE:
{
	INT32 offs = (INT8)(op & THUMB_INSN_IMM);
=======
void arm7_cpu_device::tg0d_d(uint32_t pc, uint32_t op) // COND_LE:
{
	int32_t offs = (int8_t)(op & THUMB_INSN_IMM);
>>>>>>> upstream/master
	if (Z_IS_SET(GET_CPSR) || !(GET_CPSR & N_MASK) != !(GET_CPSR & V_MASK))
	{
		R15 += 4 + (offs << 1);
	}
	else
	{
		R15 += 2;
	}
}

<<<<<<< HEAD
void arm7_cpu_device::tg0d_e(UINT32 pc, UINT32 op) // COND_AL:
=======
void arm7_cpu_device::tg0d_e(uint32_t pc, uint32_t op) // COND_AL:
>>>>>>> upstream/master
{
	fatalerror("%08x: Undefined Thumb instruction: %04x (ARM9 reserved)\n", pc, op);
}

<<<<<<< HEAD
void arm7_cpu_device::tg0d_f(UINT32 pc, UINT32 op) // COND_NV:   // SWI (this is sort of a "hole" in the opcode encoding)
{
	m_pendingSwi = 1;
	ARM7_CHECKIRQ;
=======
void arm7_cpu_device::tg0d_f(uint32_t pc, uint32_t op) // COND_NV:   // SWI (this is sort of a "hole" in the opcode encoding)
{
	m_pendingSwi = 1;
	update_irq_state();
	arm7_check_irq_state();
>>>>>>> upstream/master
}

/* B #offs */

<<<<<<< HEAD
void arm7_cpu_device::tg0e_0(UINT32 pc, UINT32 op)
{
	INT32 offs = (op & THUMB_BRANCH_OFFS) << 1;
=======
void arm7_cpu_device::tg0e_0(uint32_t pc, uint32_t op)
{
	int32_t offs = (op & THUMB_BRANCH_OFFS) << 1;
>>>>>>> upstream/master
	if (offs & 0x00000800)
	{
		offs |= 0xfffff800;
	}
	R15 += 4 + offs;
}

<<<<<<< HEAD
void arm7_cpu_device::tg0e_1(UINT32 pc, UINT32 op)
{
	UINT32 addr = GET_REGISTER(14);
	addr += (op & THUMB_BLOP_OFFS) << 1;
	addr &= 0xfffffffc;
	SET_REGISTER(14, (R15 + 4) | 1);
	R15 = addr;
=======
void arm7_cpu_device::tg0e_1(uint32_t pc, uint32_t op)
{
	uint32_t addr = GetRegister(14);
	addr += (op & THUMB_BLOP_OFFS) << 1;
	addr &= 0xfffffffc;
	SetRegister(14, (R15 + 4) | 1);
	R15 = addr;
	set_cpsr(GET_CPSR & ~T_MASK);
>>>>>>> upstream/master
}

	/* BL */

<<<<<<< HEAD
void arm7_cpu_device::tg0f_0(UINT32 pc, UINT32 op)
{
	UINT32 addr = (op & THUMB_BLOP_OFFS) << 12;
=======
void arm7_cpu_device::tg0f_0(uint32_t pc, uint32_t op)
{
	uint32_t addr = (op & THUMB_BLOP_OFFS) << 12;
>>>>>>> upstream/master
	if (addr & (1 << 22))
	{
		addr |= 0xff800000;
	}
	addr += R15 + 4;
<<<<<<< HEAD
	SET_REGISTER(14, addr);
	R15 += 2;
}

void arm7_cpu_device::tg0f_1(UINT32 pc, UINT32 op) /* BL */
{
	UINT32 addr = GET_REGISTER(14) & ~1;
	addr += (op & THUMB_BLOP_OFFS) << 1;
	SET_REGISTER(14, (R15 + 2) | 1);
=======
	SetRegister(14, addr);
	R15 += 2;
}

void arm7_cpu_device::tg0f_1(uint32_t pc, uint32_t op) /* BL */
{
	uint32_t addr = GetRegister(14) & ~1;
	addr += (op & THUMB_BLOP_OFFS) << 1;
	SetRegister(14, (R15 + 2) | 1);
>>>>>>> upstream/master
	R15 = addr;
	//R15 += 2;
}
