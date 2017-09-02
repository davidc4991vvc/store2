// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:David Graves, Bryan McPhail, Brad Oliver, Andrew Prime, Brian Troha, Nicola Salmoria
=======
// copyright-holders:David Graves, Bryan McPhail, Brad Oliver, Andrew Prime, Brian Troha, Nicola Salmoria,Stephane Humbert
>>>>>>> upstream/master
/*******************************************************************************

    Input port macros used by many games in multiple Taito drivers

*******************************************************************************/


/**************************** Machine Dip Switches ****************************/

/* with location */
#define TAITO_DSWA_BITS_2_TO_3_LOC(DIPBANK) \
	PORT_SERVICE_DIPLOC( 0x04, IP_ACTIVE_LOW, #DIPBANK":3" ) \
	PORT_DIPNAME( 0x08, 0x08, DEF_STR( Demo_Sounds ) ) PORT_DIPLOCATION(#DIPBANK":4") \
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) ) \
	PORT_DIPSETTING(    0x08, DEF_STR( On ) )

#define TAITO_DSWA_BITS_1_TO_3_LOC(DIPBANK) \
	PORT_DIPNAME( 0x02, 0x02, DEF_STR( Flip_Screen ) ) PORT_DIPLOCATION(#DIPBANK":2") \
	PORT_DIPSETTING(    0x02, DEF_STR( Off ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( On ) ) \
	TAITO_DSWA_BITS_2_TO_3_LOC(DIPBANK)

#define TAITO_MACHINE_COCKTAIL_LOC(DIPBANK) \
	PORT_DIPNAME( 0x01, 0x00, DEF_STR( Cabinet ) ) PORT_DIPLOCATION(#DIPBANK":1") \
	PORT_DIPSETTING(    0x00, DEF_STR( Upright ) ) \
	PORT_DIPSETTING(    0x01, DEF_STR( Cocktail ) ) \
	TAITO_DSWA_BITS_1_TO_3_LOC(DIPBANK)

#define TAITO_MACHINE_NO_COCKTAIL_LOC(DIPBANK) \
	PORT_DIPUNUSED_DIPLOC( 0x01, IP_ACTIVE_LOW, #DIPBANK":1" ) \
	TAITO_DSWA_BITS_1_TO_3_LOC(DIPBANK)


/* without location */
#define TAITO_DSWA_BITS_2_TO_3 \
	PORT_SERVICE( 0x04, IP_ACTIVE_LOW ) \
	PORT_DIPNAME( 0x08, 0x08, DEF_STR( Demo_Sounds ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) ) \
	PORT_DIPSETTING(    0x08, DEF_STR( On ) )

#define TAITO_DSWA_BITS_1_TO_3 \
	PORT_DIPNAME( 0x02, 0x02, DEF_STR( Flip_Screen ) ) \
	PORT_DIPSETTING(    0x02, DEF_STR( Off ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( On ) ) \
	TAITO_DSWA_BITS_2_TO_3

#define TAITO_MACHINE_COCKTAIL \
	PORT_DIPNAME( 0x01, 0x00, DEF_STR( Cabinet ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( Upright ) ) \
	PORT_DIPSETTING(    0x01, DEF_STR( Cocktail ) ) \
	TAITO_DSWA_BITS_1_TO_3

#define TAITO_MACHINE_NO_COCKTAIL \
	PORT_DIPUNUSED( 0x01, IP_ACTIVE_LOW ) \
	TAITO_DSWA_BITS_1_TO_3


<<<<<<< HEAD
/**************************** Coinage Dip Swicthes ****************************/
=======
/**************************** Coinage Dip Switches ****************************/
>>>>>>> upstream/master

/* with location */
#define TAITO_COINAGE_JAPAN_OLD_COIN_A_LOC(DIPBANK) \
	PORT_DIPNAME( 0x30, 0x30, DEF_STR( Coin_A ) ) PORT_DIPLOCATION(#DIPBANK":5,6") \
	PORT_DIPSETTING(    0x10, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0x30, DEF_STR( 1C_1C ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( 2C_3C ) ) \
	PORT_DIPSETTING(    0x20, DEF_STR( 1C_2C ) )

#define TAITO_COINAGE_JAPAN_OLD_COIN_B_LOC(DIPBANK) \
	PORT_DIPNAME( 0xc0, 0xc0, DEF_STR( Coin_B ) ) PORT_DIPLOCATION(#DIPBANK":7,8") \
	PORT_DIPSETTING(    0x40, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0xc0, DEF_STR( 1C_1C ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( 2C_3C ) ) \
	PORT_DIPSETTING(    0x80, DEF_STR( 1C_2C ) )

#define TAITO_COINAGE_JAPAN_NEW_COIN_A_LOC(DIPBANK) \
	PORT_DIPNAME( 0x30, 0x30, DEF_STR( Coin_A ) ) PORT_DIPLOCATION(#DIPBANK":5,6") \
	PORT_DIPSETTING(    0x00, DEF_STR( 3C_1C ) ) \
	PORT_DIPSETTING(    0x10, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0x30, DEF_STR( 1C_1C ) ) \
	PORT_DIPSETTING(    0x20, DEF_STR( 1C_2C ) )

#define TAITO_COINAGE_JAPAN_NEW_COIN_B_LOC(DIPBANK) \
	PORT_DIPNAME( 0xc0, 0xc0, DEF_STR( Coin_B ) ) PORT_DIPLOCATION(#DIPBANK":7,8") \
	PORT_DIPSETTING(    0x00, DEF_STR( 3C_1C ) ) \
	PORT_DIPSETTING(    0x40, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0xc0, DEF_STR( 1C_1C ) ) \
	PORT_DIPSETTING(    0x80, DEF_STR( 1C_2C ) )

#define TAITO_COINAGE_WORLD_COIN_A_LOC(DIPBANK) \
	PORT_DIPNAME( 0x30, 0x30, DEF_STR( Coin_A ) ) PORT_DIPLOCATION(#DIPBANK":5,6") \
	PORT_DIPSETTING(    0x00, DEF_STR( 4C_1C ) ) \
	PORT_DIPSETTING(    0x10, DEF_STR( 3C_1C ) ) \
	PORT_DIPSETTING(    0x20, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0x30, DEF_STR( 1C_1C ) )

#define TAITO_COINAGE_WORLD_COIN_B_LOC(DIPBANK) \
	PORT_DIPNAME( 0xc0, 0xc0, DEF_STR( Coin_B ) ) PORT_DIPLOCATION(#DIPBANK":7,8") \
	PORT_DIPSETTING(    0xc0, DEF_STR( 1C_2C ) ) \
	PORT_DIPSETTING(    0x80, DEF_STR( 1C_3C ) ) \
	PORT_DIPSETTING(    0x40, DEF_STR( 1C_4C ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( 1C_6C ) )

#define TAITO_COINAGE_US_COIN_START_LOC(DIPBANK) \
	PORT_DIPNAME( 0x30, 0x30, DEF_STR( Coinage ) ) PORT_DIPLOCATION(#DIPBANK":5,6") \
	PORT_DIPSETTING(    0x00, DEF_STR( 4C_1C ) ) \
	PORT_DIPSETTING(    0x10, DEF_STR( 3C_1C ) ) \
	PORT_DIPSETTING(    0x20, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0x30, DEF_STR( 1C_1C ) )

#define TAITO_COINAGE_US_COIN_CONT_LOC(DIPBANK) \
	PORT_DIPNAME( 0xc0, 0xc0, "Price to Continue" ) PORT_DIPLOCATION(#DIPBANK":7,8") \
	PORT_DIPSETTING(    0x00, DEF_STR( 3C_1C ) ) \
	PORT_DIPSETTING(    0x40, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0x80, DEF_STR( 1C_1C ) ) \
	PORT_DIPSETTING(    0xc0, "Same as Start" )

#define TAITO_COINAGE_JAPAN_OLD_LOC(DIPBANK) \
	TAITO_COINAGE_JAPAN_OLD_COIN_A_LOC(DIPBANK) \
	TAITO_COINAGE_JAPAN_OLD_COIN_B_LOC(DIPBANK)

#define TAITO_COINAGE_JAPAN_NEW_LOC(DIPBANK) \
	TAITO_COINAGE_JAPAN_NEW_COIN_A_LOC(DIPBANK) \
	TAITO_COINAGE_JAPAN_NEW_COIN_B_LOC(DIPBANK)

#define TAITO_COINAGE_WORLD_LOC(DIPBANK) \
	TAITO_COINAGE_WORLD_COIN_A_LOC(DIPBANK) \
	TAITO_COINAGE_WORLD_COIN_B_LOC(DIPBANK)

#define TAITO_COINAGE_US_LOC(DIPBANK) \
	TAITO_COINAGE_US_COIN_START_LOC(DIPBANK) \
	TAITO_COINAGE_US_COIN_CONT_LOC(DIPBANK)


/* without location */
#define TAITO_COINAGE_JAPAN_OLD_COIN_A \
	PORT_DIPNAME( 0x30, 0x30, DEF_STR( Coin_A ) ) \
	PORT_DIPSETTING(    0x10, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0x30, DEF_STR( 1C_1C ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( 2C_3C ) ) \
	PORT_DIPSETTING(    0x20, DEF_STR( 1C_2C ) )

#define TAITO_COINAGE_JAPAN_OLD_COIN_B \
	PORT_DIPNAME( 0xc0, 0xc0, DEF_STR( Coin_B ) ) \
	PORT_DIPSETTING(    0x40, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0xc0, DEF_STR( 1C_1C ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( 2C_3C ) ) \
	PORT_DIPSETTING(    0x80, DEF_STR( 1C_2C ) )

#define TAITO_COINAGE_JAPAN_NEW_COIN_A \
	PORT_DIPNAME( 0x30, 0x30, DEF_STR( Coin_A ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( 3C_1C ) ) \
	PORT_DIPSETTING(    0x10, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0x30, DEF_STR( 1C_1C ) ) \
	PORT_DIPSETTING(    0x20, DEF_STR( 1C_2C ) )

#define TAITO_COINAGE_JAPAN_NEW_COIN_B \
	PORT_DIPNAME( 0xc0, 0xc0, DEF_STR( Coin_B ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( 3C_1C ) ) \
	PORT_DIPSETTING(    0x40, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0xc0, DEF_STR( 1C_1C ) ) \
	PORT_DIPSETTING(    0x80, DEF_STR( 1C_2C ) )

#define TAITO_COINAGE_WORLD_COIN_A \
	PORT_DIPNAME( 0x30, 0x30, DEF_STR( Coin_A ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( 4C_1C ) ) \
	PORT_DIPSETTING(    0x10, DEF_STR( 3C_1C ) ) \
	PORT_DIPSETTING(    0x20, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0x30, DEF_STR( 1C_1C ) )

#define TAITO_COINAGE_WORLD_COIN_B \
	PORT_DIPNAME( 0xc0, 0xc0, DEF_STR( Coin_B ) ) \
	PORT_DIPSETTING(    0xc0, DEF_STR( 1C_2C ) ) \
	PORT_DIPSETTING(    0x80, DEF_STR( 1C_3C ) ) \
	PORT_DIPSETTING(    0x40, DEF_STR( 1C_4C ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( 1C_6C ) )

#define TAITO_COINAGE_US_COIN_START \
	PORT_DIPNAME( 0x30, 0x30, DEF_STR( Coinage ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( 4C_1C ) ) \
	PORT_DIPSETTING(    0x10, DEF_STR( 3C_1C ) ) \
	PORT_DIPSETTING(    0x20, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0x30, DEF_STR( 1C_1C ) )

#define TAITO_COINAGE_US_COIN_CONT \
	PORT_DIPNAME( 0xc0, 0xc0, DEF_STR( Continue_Price ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( 3C_1C ) ) \
	PORT_DIPSETTING(    0x40, DEF_STR( 2C_1C ) ) \
	PORT_DIPSETTING(    0x80, DEF_STR( 1C_1C ) ) \
	PORT_DIPSETTING(    0xc0, "Same as Start" )

#define TAITO_COINAGE_JAPAN_OLD \
	TAITO_COINAGE_JAPAN_OLD_COIN_A \
	TAITO_COINAGE_JAPAN_OLD_COIN_B

#define TAITO_COINAGE_JAPAN_NEW \
	TAITO_COINAGE_JAPAN_NEW_COIN_A \
	TAITO_COINAGE_JAPAN_NEW_COIN_B

#define TAITO_COINAGE_WORLD \
	TAITO_COINAGE_WORLD_COIN_A \
	TAITO_COINAGE_WORLD_COIN_B

#define TAITO_COINAGE_US \
	TAITO_COINAGE_US_COIN_START \
	TAITO_COINAGE_US_COIN_CONT


/************************** Difficulty Dip Switches ***************************/

/* with location */
#define TAITO_DIFFICULTY_LOC(DIPBANK) \
	PORT_DIPNAME( 0x03, 0x03, DEF_STR( Difficulty ) ) PORT_DIPLOCATION(#DIPBANK":1,2") \
	PORT_DIPSETTING(    0x02, DEF_STR( Easy ) ) \
	PORT_DIPSETTING(    0x03, DEF_STR( Medium ) ) \
	PORT_DIPSETTING(    0x01, DEF_STR( Hard ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( Hardest ) )

/* without location */
#define TAITO_DIFFICULTY \
	PORT_DIPNAME( 0x03, 0x03, DEF_STR( Difficulty ) ) \
	PORT_DIPSETTING(    0x02, DEF_STR( Easy ) ) \
	PORT_DIPSETTING(    0x03, DEF_STR( Medium ) ) \
	PORT_DIPSETTING(    0x01, DEF_STR( Hard ) ) \
	PORT_DIPSETTING(    0x00, DEF_STR( Hardest ) )


/************************** Joysticks and buttons *****************************/

/* generic (might be moved elsewhere) */
#define INPUT_GENERIC_JOY_LOW_NIBBLE(PL, STATE, WAY, B01, B02, B04, B08) \
	PORT_BIT( 0x01, STATE, IPT_JOYSTICK_##B01 ) WAY PORT_PLAYER(PL) \
	PORT_BIT( 0x02, STATE, IPT_JOYSTICK_##B02 ) WAY PORT_PLAYER(PL) \
	PORT_BIT( 0x04, STATE, IPT_JOYSTICK_##B04 ) WAY PORT_PLAYER(PL) \
	PORT_BIT( 0x08, STATE, IPT_JOYSTICK_##B08 ) WAY PORT_PLAYER(PL)

#define INPUT_GENERIC_JOY_HIGH_NIBBLE(PL, STATE, WAY, B10, B20, B40, B80) \
	PORT_BIT( 0x10, STATE, IPT_JOYSTICK_##B10 ) WAY PORT_PLAYER(PL) \
	PORT_BIT( 0x20, STATE, IPT_JOYSTICK_##B20 ) WAY PORT_PLAYER(PL) \
	PORT_BIT( 0x40, STATE, IPT_JOYSTICK_##B40 ) WAY PORT_PLAYER(PL) \
	PORT_BIT( 0x80, STATE, IPT_JOYSTICK_##B80 ) WAY PORT_PLAYER(PL)


/* Taito generic (more might be needed) */
#define TAITO_GENERIC_JOY_MONO_UDLR(PL) \
	INPUT_GENERIC_JOY_LOW_NIBBLE(PL, IP_ACTIVE_LOW, PORT_8WAY, UP, DOWN, LEFT, RIGHT)

#define TAITO_GENERIC_JOY_MONO_UDRL(PL) \
	INPUT_GENERIC_JOY_LOW_NIBBLE(PL, IP_ACTIVE_LOW, PORT_8WAY, UP, DOWN, RIGHT, LEFT)

#define TAITO_GENERIC_JOY_MONO_LRUD(PL) \
	INPUT_GENERIC_JOY_LOW_NIBBLE(PL, IP_ACTIVE_LOW, PORT_8WAY, LEFT, RIGHT, UP, DOWN)

#define TAITO_GENERIC_JOY_DUAL_UDLR(PL_L, PL_H) \
	INPUT_GENERIC_JOY_LOW_NIBBLE(PL_L, IP_ACTIVE_LOW, PORT_8WAY, UP, DOWN, LEFT, RIGHT) \
	INPUT_GENERIC_JOY_HIGH_NIBBLE(PL_H, IP_ACTIVE_LOW, PORT_8WAY, UP, DOWN, LEFT, RIGHT)

#define TAITO_GENERIC_JOY_DUAL_UDRL(PL_L, PL_H) \
	INPUT_GENERIC_JOY_LOW_NIBBLE(PL_L, IP_ACTIVE_LOW, PORT_8WAY, UP, DOWN, RIGHT, LEFT) \
	INPUT_GENERIC_JOY_HIGH_NIBBLE(PL_H, IP_ACTIVE_LOW, PORT_8WAY, UP, DOWN, RIGHT, LEFT)


#define TAITO_GENERIC_BUTTONS_LOW_NIBBLE(PL, STATE, BUTTON_A, BUTTON_B, BUTTON_C) \
	PORT_BIT( 0x01, STATE, IPT_##BUTTON_A ) PORT_PLAYER(PL) \
	PORT_BIT( 0x02, STATE, IPT_##BUTTON_B ) PORT_PLAYER(PL) \
	PORT_BIT( 0x04, STATE, IPT_##BUTTON_C ) PORT_PLAYER(PL)
	/* DO NOT fill bit 3 as it may be defined as START button ! */

#define TAITO_GENERIC_BUTTONS_HIGH_NIBBLE(PL, STATE, BUTTON_A, BUTTON_B, BUTTON_C) \
	PORT_BIT( 0x10, STATE, IPT_##BUTTON_A ) PORT_PLAYER(PL) \
	PORT_BIT( 0x20, STATE, IPT_##BUTTON_B ) PORT_PLAYER(PL) \
	PORT_BIT( 0x40, STATE, IPT_##BUTTON_C ) PORT_PLAYER(PL)
	/* DO NOT fill bit 7 as it may be defined as START button ! */

#define TAITO_GENERIC_1_BUTTON(PL) \
	TAITO_GENERIC_BUTTONS_HIGH_NIBBLE(PL, IP_ACTIVE_LOW, BUTTON1, UNKNOWN, UNKNOWN) \
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

#define TAITO_GENERIC_2_BUTTONS(PL) \
	TAITO_GENERIC_BUTTONS_HIGH_NIBBLE(PL, IP_ACTIVE_LOW, BUTTON1, BUTTON2, UNKNOWN) \
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

#define TAITO_GENERIC_3_BUTTONS(PL) \
	TAITO_GENERIC_BUTTONS_HIGH_NIBBLE(PL, IP_ACTIVE_LOW, BUTTON1, BUTTON2, BUTTON3) \
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

#define TAITO_GENERIC_1_BUTTON_START(PL) \
	TAITO_GENERIC_BUTTONS_HIGH_NIBBLE(PL, IP_ACTIVE_LOW, BUTTON1, UNKNOWN, UNKNOWN) \
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_START##PL )

#define TAITO_GENERIC_2_BUTTONS_START(PL) \
	TAITO_GENERIC_BUTTONS_HIGH_NIBBLE(PL, IP_ACTIVE_LOW, BUTTON1, BUTTON2, UNKNOWN) \
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_START##PL )

#define TAITO_GENERIC_3_BUTTONS_START(PL) \
	TAITO_GENERIC_BUTTONS_HIGH_NIBBLE(PL, IP_ACTIVE_LOW, BUTTON1, BUTTON2, BUTTON3) \
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_START##PL )


/* Taito games (more might be needed) */
#define TAITO_JOY_UDLR_1_BUTTON(PL) \
	TAITO_GENERIC_JOY_MONO_UDLR(PL) \
	TAITO_GENERIC_1_BUTTON(PL)

#define TAITO_JOY_UDLR_2_BUTTONS(PL) \
	TAITO_GENERIC_JOY_MONO_UDLR(PL) \
	TAITO_GENERIC_2_BUTTONS(PL)

#define TAITO_JOY_UDLR_3_BUTTONS(PL) \
	TAITO_GENERIC_JOY_MONO_UDLR(PL) \
	TAITO_GENERIC_3_BUTTONS(PL)

#define TAITO_JOY_UDRL_1_BUTTON(PL) \
	TAITO_GENERIC_JOY_MONO_UDRL(PL) \
	TAITO_GENERIC_1_BUTTON(PL)

#define TAITO_JOY_UDRL_2_BUTTONS(PL) \
	TAITO_GENERIC_JOY_MONO_UDRL(PL) \
	TAITO_GENERIC_2_BUTTONS(PL)

#define TAITO_JOY_UDRL_3_BUTTONS(PL) \
	TAITO_GENERIC_JOY_MONO_UDRL(PL) \
	TAITO_GENERIC_3_BUTTONS(PL)

#define TAITO_JOY_LRUD_1_BUTTON(PL) \
	TAITO_GENERIC_JOY_MONO_LRUD(PL) \
	TAITO_GENERIC_1_BUTTON(PL)

#define TAITO_JOY_LRUD_2_BUTTONS(PL) \
	TAITO_GENERIC_JOY_MONO_LRUD(PL) \
	TAITO_GENERIC_2_BUTTONS(PL)

#define TAITO_JOY_LRUD_3_BUTTONS(PL) \
	TAITO_GENERIC_JOY_MONO_LRUD(PL) \
	TAITO_GENERIC_3_BUTTONS(PL)


#define TAITO_JOY_UDLR_1_BUTTON_START(PL) \
	TAITO_GENERIC_JOY_MONO_UDLR(PL) \
	TAITO_GENERIC_1_BUTTON_START(PL)

#define TAITO_JOY_UDLR_2_BUTTONS_START(PL) \
	TAITO_GENERIC_JOY_MONO_UDLR(PL) \
	TAITO_GENERIC_2_BUTTONS_START(PL)

#define TAITO_JOY_UDLR_3_BUTTONS_START(PL) \
	TAITO_GENERIC_JOY_MONO_UDLR(PL) \
	TAITO_GENERIC_3_BUTTONS_START(PL)

#define TAITO_JOY_UDRL_1_BUTTON_START(PL) \
	TAITO_GENERIC_JOY_MONO_UDRL(PL) \
	TAITO_GENERIC_1_BUTTONS_START(PL)

#define TAITO_JOY_UDRL_2_BUTTONS_START(PL) \
	TAITO_GENERIC_JOY_MONO_UDRL(PL) \
	TAITO_GENERIC_2_BUTTONS_START(PL)

#define TAITO_JOY_UDRL_3_BUTTONS_START(PL) \
	TAITO_GENERIC_JOY_MONO_UDRL(PL) \
	TAITO_GENERIC_3_BUTTONS_START(PL)

#define TAITO_JOY_LRUD_1_BUTTON_START(PL) \
	TAITO_GENERIC_JOY_MONO_LRUD(PL) \
	TAITO_GENERIC_1_BUTTON_START(PL)

#define TAITO_JOY_LRUD_2_BUTTONS_START(PL) \
	TAITO_GENERIC_JOY_MONO_LRUD(PL) \
	TAITO_GENERIC_2_BUTTONS_START(PL)

#define TAITO_JOY_LRUD_3_BUTTONS_START(PL) \
	TAITO_GENERIC_JOY_MONO_LRUD(PL) \
	TAITO_GENERIC_3_BUTTONS_START(PL)


#define TAITO_JOY_DUAL_UDLR(PL_L, PL_H) \
	TAITO_GENERIC_JOY_DUAL_UDLR(PL_L, PL_H)

#define TAITO_JOY_DUAL_UDRL(PL_L, PL_H) \
	TAITO_GENERIC_JOY_DUAL_UDRL(PL_L, PL_H)
