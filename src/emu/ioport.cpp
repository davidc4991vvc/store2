// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    ioport.c

    Input/output port handling.

****************************************************************************

    Theory of operation

    ------------
    OSD controls
    ------------

    There are three types of controls that the OSD can provide as potential
    input devices: digital controls, absolute analog controls, and relative
    analog controls.

    Digital controls have only two states: on or off. They are generally
    mapped to buttons and digital joystick directions (like a gamepad or a
    joystick hat). The OSD layer must return either 0 (off) or 1 (on) for
    these types of controls.

    Absolute analog controls are analog in the sense that they return a
    range of values depending on how much a given control is moved, but they
    are physically bounded. This means that there is a minimum and maximum
    limit to how far the control can be moved. They are generally mapped to
    analog joystick axes, lightguns, most PC steering wheels, and pedals.
    The OSD layer must determine the minimum and maximum range of each
    analog device and scale that to a value between -65536 and +65536
    representing the position of the control. -65536 generally refers to
    the topmost or leftmost position, while +65536 refers to the bottommost
    or rightmost position. Note that pedals are a special case here, the
    OSD layer needs to return half axis as full -65536 to + 65536 range.

    Relative analog controls are analog as well, but are not physically
    bounded. They can be moved continually in one direction without limit.
    They are generally mapped to trackballs and mice. Because they are
    unbounded, the OSD layer can only return delta values since the last
    read. Because of this, it is difficult to scale appropriately. For
    MAME's purposes, when mapping a mouse devices to a relative analog
    control, one pixel of movement should correspond to 512 units. Other
    analog control types should be scaled to return values of a similar
    magnitude. Like absolute analog controls, negative values refer to
    upward or leftward movement, while positive values refer to downward
    or rightward movement.

    -------------
    Game controls
    -------------

    Similarly, the types of controls used by arcade games fall into the same
    three categories: digital, absolute analog, and relative analog. The
    tricky part is how to map any arbitrary type of OSD control to an
    arbitrary type of game control.

    Digital controls: used for game buttons and standard 4/8-way joysticks,
    as well as many other types of game controls. Mapping an OSD digital
    control to a game's OSD control is trivial. For OSD analog controls,
    the MAME core does not directly support mapping any OSD analog devices
    to digital controls. However, the OSD layer is free to enumerate digital
    equivalents for analog devices. For example, each analog axis in the
    Windows OSD code enumerates to two digital controls, one for the
    negative direction (up/left) and one for the position direction
    (down/right). When these "digital" inputs are queried, the OSD layer
    checks the axis position against the center, adding in a dead zone,
    and returns 0 or 1 to indicate its position.

    Absolute analog controls: used for analog joysticks, lightguns, pedals,
    and wheel controls. Mapping an OSD absolute analog control to this type
    is easy. OSD relative analog controls can be mapped here as well by
    accumulating the deltas and bounding the results. OSD digital controls
    are mapped to these types of controls in pairs, one for a decrement and
    one for an increment, but apart from that, operate the same as the OSD
    relative analog controls by accumulating deltas and applying bounds.
    The speed of the digital delta is user-configurable per analog input.
    In addition, most absolute analog control types have an autocentering
    feature that is activated when using the digital increment/decrement
    sequences, which returns the control back to the center at a user-
    controllable speed if no digital sequences are pressed.

    Relative analog controls: used for trackballs and dial controls. Again,
    mapping an OSD relative analog control to this type is straightforward.
    OSD absolute analog controls can't map directly to these, but if the OSD
    layer provides a digital equivalent for each direction, it can be done.
    OSD digital controls map just like they do for absolute analog controls,
    except that the accumulated deltas are not bounded, but rather wrap.

***************************************************************************/

#include "emu.h"
#include "emuopts.h"
#include "config.h"
#include "xmlfile.h"
#include "profiler.h"
<<<<<<< HEAD
#include "ui/ui.h"
#include "uiinput.h"
#ifdef USE_SHOW_INPUT_LOG
#include "rendfont.h"
#endif /* USE_SHOW_INPUT_LOG */
=======
#include "ui/uimain.h"
#include "inputdev.h"
#include "natkeyboard.h"
>>>>>>> upstream/master

#include "osdepend.h"

#include <ctype.h>
#include <time.h>

<<<<<<< HEAD
=======

namespace {
>>>>>>> upstream/master
// temporary: set this to 1 to enable the originally defined behavior that
// a field specified via PORT_MODIFY which intersects a previously-defined
// field completely wipes out the previous definition
#define INPUT_PORT_OVERRIDE_FULLY_NUKES_PREVIOUS    1


//**************************************************************************
<<<<<<< HEAD
//  DEBUGGING
//**************************************************************************

#define LOG_NATURAL_KEYBOARD    0



//**************************************************************************
=======
>>>>>>> upstream/master
//  CONSTANTS
//**************************************************************************

const int SPACE_COUNT = 3;
<<<<<<< HEAD
const int KEY_BUFFER_SIZE = 4096;
const unicode_char INVALID_CHAR = '?';

#ifdef USE_AUTOFIRE
#define AUTOFIRE_ON             1    /* Autofire enable bit */
#define AUTOFIRE_TOGGLE         2    /* Autofire toggle enable bit */
#endif /* USE_AUTOFIRE */



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// character information
struct char_info
{
	unicode_char ch;
	const char *name;
	const char *alternate;  // alternative string, in UTF-8

	static const char_info *find(unicode_char target);
};
=======
>>>>>>> upstream/master



//**************************************************************************
//  INLINE FUNCTIONS
//**************************************************************************

//-------------------------------------------------
//  compute_scale -- compute an 8.24 scale value
//  from a numerator and a denominator
//-------------------------------------------------

<<<<<<< HEAD
inline INT64 compute_scale(INT32 num, INT32 den)
{
	return (INT64(num) << 24) / den;
=======
inline s64 compute_scale(s32 num, s32 den)
{
	return (s64(num) << 24) / den;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  recip_scale -- compute an 8.24 reciprocal of
//  an 8.24 scale value
//-------------------------------------------------

<<<<<<< HEAD
inline INT64 recip_scale(INT64 scale)
{
	return (INT64(1) << 48) / scale;
=======
inline s64 recip_scale(s64 scale)
{
	return (s64(1) << 48) / scale;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  apply_scale -- apply an 8.24 scale value to
//  a 32-bit value
//-------------------------------------------------

<<<<<<< HEAD
inline INT32 apply_scale(INT32 value, INT64 scale)
{
	return (INT64(value) * scale) >> 24;
=======
inline s32 apply_scale(s32 value, s64 scale)
{
	return (s64(value) * scale) >> 24;
>>>>>>> upstream/master
}



//**************************************************************************
<<<<<<< HEAD
//  GLOBAL VARIABLES
//**************************************************************************

// XML attributes for the different types
static const char *const seqtypestrings[] = { "standard", "increment", "decrement" };

// master character info table
static const char_info charinfo[] =
{
	{ 0x0008,                   "Backspace",    NULL },     // Backspace
	{ 0x0009,                   "Tab",          "    " },   // Tab
	{ 0x000c,                   "Clear",        NULL },     // Clear
	{ 0x000d,                   "Enter",        NULL },     // Enter
	{ 0x001a,                   "Esc",          NULL },     // Esc
	{ 0x0020,                   "Space",        " " },      // Space
	{ 0x0061,                   NULL,           "A" },      // a
	{ 0x0062,                   NULL,           "B" },      // b
	{ 0x0063,                   NULL,           "C" },      // c
	{ 0x0064,                   NULL,           "D" },      // d
	{ 0x0065,                   NULL,           "E" },      // e
	{ 0x0066,                   NULL,           "F" },      // f
	{ 0x0067,                   NULL,           "G" },      // g
	{ 0x0068,                   NULL,           "H" },      // h
	{ 0x0069,                   NULL,           "I" },      // i
	{ 0x006a,                   NULL,           "J" },      // j
	{ 0x006b,                   NULL,           "K" },      // k
	{ 0x006c,                   NULL,           "L" },      // l
	{ 0x006d,                   NULL,           "M" },      // m
	{ 0x006e,                   NULL,           "N" },      // n
	{ 0x006f,                   NULL,           "O" },      // o
	{ 0x0070,                   NULL,           "P" },      // p
	{ 0x0071,                   NULL,           "Q" },      // q
	{ 0x0072,                   NULL,           "R" },      // r
	{ 0x0073,                   NULL,           "S" },      // s
	{ 0x0074,                   NULL,           "T" },      // t
	{ 0x0075,                   NULL,           "U" },      // u
	{ 0x0076,                   NULL,           "V" },      // v
	{ 0x0077,                   NULL,           "W" },      // w
	{ 0x0078,                   NULL,           "X" },      // x
	{ 0x0079,                   NULL,           "Y" },      // y
	{ 0x007a,                   NULL,           "Z" },      // z
	{ 0x00a0,                   NULL,           " " },      // non breaking space
	{ 0x00a1,                   NULL,           "!" },      // inverted exclaimation mark
	{ 0x00a6,                   NULL,           "|" },      // broken bar
	{ 0x00a9,                   NULL,           "(c)" },    // copyright sign
	{ 0x00ab,                   NULL,           "<<" },     // left pointing double angle
	{ 0x00ae,                   NULL,           "(r)" },    // registered sign
	{ 0x00bb,                   NULL,           ">>" },     // right pointing double angle
	{ 0x00bc,                   NULL,           "1/4" },    // vulgar fraction one quarter
	{ 0x00bd,                   NULL,           "1/2" },    // vulgar fraction one half
	{ 0x00be,                   NULL,           "3/4" },    // vulgar fraction three quarters
	{ 0x00bf,                   NULL,           "?" },      // inverted question mark
	{ 0x00c0,                   NULL,           "A" },      // 'A' grave
	{ 0x00c1,                   NULL,           "A" },      // 'A' acute
	{ 0x00c2,                   NULL,           "A" },      // 'A' circumflex
	{ 0x00c3,                   NULL,           "A" },      // 'A' tilde
	{ 0x00c4,                   NULL,           "A" },      // 'A' diaeresis
	{ 0x00c5,                   NULL,           "A" },      // 'A' ring above
	{ 0x00c6,                   NULL,           "AE" },     // 'AE' ligature
	{ 0x00c7,                   NULL,           "C" },      // 'C' cedilla
	{ 0x00c8,                   NULL,           "E" },      // 'E' grave
	{ 0x00c9,                   NULL,           "E" },      // 'E' acute
	{ 0x00ca,                   NULL,           "E" },      // 'E' circumflex
	{ 0x00cb,                   NULL,           "E" },      // 'E' diaeresis
	{ 0x00cc,                   NULL,           "I" },      // 'I' grave
	{ 0x00cd,                   NULL,           "I" },      // 'I' acute
	{ 0x00ce,                   NULL,           "I" },      // 'I' circumflex
	{ 0x00cf,                   NULL,           "I" },      // 'I' diaeresis
	{ 0x00d0,                   NULL,           "D" },      // 'ETH'
	{ 0x00d1,                   NULL,           "N" },      // 'N' tilde
	{ 0x00d2,                   NULL,           "O" },      // 'O' grave
	{ 0x00d3,                   NULL,           "O" },      // 'O' acute
	{ 0x00d4,                   NULL,           "O" },      // 'O' circumflex
	{ 0x00d5,                   NULL,           "O" },      // 'O' tilde
	{ 0x00d6,                   NULL,           "O" },      // 'O' diaeresis
	{ 0x00d7,                   NULL,           "X" },      // multiplication sign
	{ 0x00d8,                   NULL,           "O" },      // 'O' stroke
	{ 0x00d9,                   NULL,           "U" },      // 'U' grave
	{ 0x00da,                   NULL,           "U" },      // 'U' acute
	{ 0x00db,                   NULL,           "U" },      // 'U' circumflex
	{ 0x00dc,                   NULL,           "U" },      // 'U' diaeresis
	{ 0x00dd,                   NULL,           "Y" },      // 'Y' acute
	{ 0x00df,                   NULL,           "SS" },     // sharp S
	{ 0x00e0,                   NULL,           "a" },      // 'a' grave
	{ 0x00e1,                   NULL,           "a" },      // 'a' acute
	{ 0x00e2,                   NULL,           "a" },      // 'a' circumflex
	{ 0x00e3,                   NULL,           "a" },      // 'a' tilde
	{ 0x00e4,                   NULL,           "a" },      // 'a' diaeresis
	{ 0x00e5,                   NULL,           "a" },      // 'a' ring above
	{ 0x00e6,                   NULL,           "ae" },     // 'ae' ligature
	{ 0x00e7,                   NULL,           "c" },      // 'c' cedilla
	{ 0x00e8,                   NULL,           "e" },      // 'e' grave
	{ 0x00e9,                   NULL,           "e" },      // 'e' acute
	{ 0x00ea,                   NULL,           "e" },      // 'e' circumflex
	{ 0x00eb,                   NULL,           "e" },      // 'e' diaeresis
	{ 0x00ec,                   NULL,           "i" },      // 'i' grave
	{ 0x00ed,                   NULL,           "i" },      // 'i' acute
	{ 0x00ee,                   NULL,           "i" },      // 'i' circumflex
	{ 0x00ef,                   NULL,           "i" },      // 'i' diaeresis
	{ 0x00f0,                   NULL,           "d" },      // 'eth'
	{ 0x00f1,                   NULL,           "n" },      // 'n' tilde
	{ 0x00f2,                   NULL,           "o" },      // 'o' grave
	{ 0x00f3,                   NULL,           "o" },      // 'o' acute
	{ 0x00f4,                   NULL,           "o" },      // 'o' circumflex
	{ 0x00f5,                   NULL,           "o" },      // 'o' tilde
	{ 0x00f6,                   NULL,           "o" },      // 'o' diaeresis
	{ 0x00f8,                   NULL,           "o" },      // 'o' stroke
	{ 0x00f9,                   NULL,           "u" },      // 'u' grave
	{ 0x00fa,                   NULL,           "u" },      // 'u' acute
	{ 0x00fb,                   NULL,           "u" },      // 'u' circumflex
	{ 0x00fc,                   NULL,           "u" },      // 'u' diaeresis
	{ 0x00fd,                   NULL,           "y" },      // 'y' acute
	{ 0x00ff,                   NULL,           "y" },      // 'y' diaeresis
	{ 0x2010,                   NULL,           "-" },      // hyphen
	{ 0x2011,                   NULL,           "-" },      // non-breaking hyphen
	{ 0x2012,                   NULL,           "-" },      // figure dash
	{ 0x2013,                   NULL,           "-" },      // en dash
	{ 0x2014,                   NULL,           "-" },      // em dash
	{ 0x2015,                   NULL,           "-" },      // horizontal dash
	{ 0x2018,                   NULL,           "\'" },     // left single quotation mark
	{ 0x2019,                   NULL,           "\'" },     // right single quotation mark
	{ 0x201a,                   NULL,           "\'" },     // single low quotation mark
	{ 0x201b,                   NULL,           "\'" },     // single high reversed quotation mark
	{ 0x201c,                   NULL,           "\"" },     // left double quotation mark
	{ 0x201d,                   NULL,           "\"" },     // right double quotation mark
	{ 0x201e,                   NULL,           "\"" },     // double low quotation mark
	{ 0x201f,                   NULL,           "\"" },     // double high reversed quotation mark
	{ 0x2024,                   NULL,           "." },      // one dot leader
	{ 0x2025,                   NULL,           ".." },     // two dot leader
	{ 0x2026,                   NULL,           "..." },    // horizontal ellipsis
	{ 0x2047,                   NULL,           "??" },     // double question mark
	{ 0x2048,                   NULL,           "?!" },     // question exclamation mark
	{ 0x2049,                   NULL,           "!?" },     // exclamation question mark
	{ 0xff01,                   NULL,           "!" },      // fullwidth exclamation point
	{ 0xff02,                   NULL,           "\"" },     // fullwidth quotation mark
	{ 0xff03,                   NULL,           "#" },      // fullwidth number sign
	{ 0xff04,                   NULL,           "$" },      // fullwidth dollar sign
	{ 0xff05,                   NULL,           "%" },      // fullwidth percent sign
	{ 0xff06,                   NULL,           "&" },      // fullwidth ampersand
	{ 0xff07,                   NULL,           "\'" },     // fullwidth apostrophe
	{ 0xff08,                   NULL,           "(" },      // fullwidth left parenthesis
	{ 0xff09,                   NULL,           ")" },      // fullwidth right parenthesis
	{ 0xff0a,                   NULL,           "*" },      // fullwidth asterisk
	{ 0xff0b,                   NULL,           "+" },      // fullwidth plus
	{ 0xff0c,                   NULL,           "," },      // fullwidth comma
	{ 0xff0d,                   NULL,           "-" },      // fullwidth minus
	{ 0xff0e,                   NULL,           "." },      // fullwidth period
	{ 0xff0f,                   NULL,           "/" },      // fullwidth slash
	{ 0xff10,                   NULL,           "0" },      // fullwidth zero
	{ 0xff11,                   NULL,           "1" },      // fullwidth one
	{ 0xff12,                   NULL,           "2" },      // fullwidth two
	{ 0xff13,                   NULL,           "3" },      // fullwidth three
	{ 0xff14,                   NULL,           "4" },      // fullwidth four
	{ 0xff15,                   NULL,           "5" },      // fullwidth five
	{ 0xff16,                   NULL,           "6" },      // fullwidth six
	{ 0xff17,                   NULL,           "7" },      // fullwidth seven
	{ 0xff18,                   NULL,           "8" },      // fullwidth eight
	{ 0xff19,                   NULL,           "9" },      // fullwidth nine
	{ 0xff1a,                   NULL,           ":" },      // fullwidth colon
	{ 0xff1b,                   NULL,           ";" },      // fullwidth semicolon
	{ 0xff1c,                   NULL,           "<" },      // fullwidth less than sign
	{ 0xff1d,                   NULL,           "=" },      // fullwidth equals sign
	{ 0xff1e,                   NULL,           ">" },      // fullwidth greater than sign
	{ 0xff1f,                   NULL,           "?" },      // fullwidth question mark
	{ 0xff20,                   NULL,           "@" },      // fullwidth at sign
	{ 0xff21,                   NULL,           "A" },      // fullwidth 'A'
	{ 0xff22,                   NULL,           "B" },      // fullwidth 'B'
	{ 0xff23,                   NULL,           "C" },      // fullwidth 'C'
	{ 0xff24,                   NULL,           "D" },      // fullwidth 'D'
	{ 0xff25,                   NULL,           "E" },      // fullwidth 'E'
	{ 0xff26,                   NULL,           "F" },      // fullwidth 'F'
	{ 0xff27,                   NULL,           "G" },      // fullwidth 'G'
	{ 0xff28,                   NULL,           "H" },      // fullwidth 'H'
	{ 0xff29,                   NULL,           "I" },      // fullwidth 'I'
	{ 0xff2a,                   NULL,           "J" },      // fullwidth 'J'
	{ 0xff2b,                   NULL,           "K" },      // fullwidth 'K'
	{ 0xff2c,                   NULL,           "L" },      // fullwidth 'L'
	{ 0xff2d,                   NULL,           "M" },      // fullwidth 'M'
	{ 0xff2e,                   NULL,           "N" },      // fullwidth 'N'
	{ 0xff2f,                   NULL,           "O" },      // fullwidth 'O'
	{ 0xff30,                   NULL,           "P" },      // fullwidth 'P'
	{ 0xff31,                   NULL,           "Q" },      // fullwidth 'Q'
	{ 0xff32,                   NULL,           "R" },      // fullwidth 'R'
	{ 0xff33,                   NULL,           "S" },      // fullwidth 'S'
	{ 0xff34,                   NULL,           "T" },      // fullwidth 'T'
	{ 0xff35,                   NULL,           "U" },      // fullwidth 'U'
	{ 0xff36,                   NULL,           "V" },      // fullwidth 'V'
	{ 0xff37,                   NULL,           "W" },      // fullwidth 'W'
	{ 0xff38,                   NULL,           "X" },      // fullwidth 'X'
	{ 0xff39,                   NULL,           "Y" },      // fullwidth 'Y'
	{ 0xff3a,                   NULL,           "Z" },      // fullwidth 'Z'
	{ 0xff3b,                   NULL,           "[" },      // fullwidth left bracket
	{ 0xff3c,                   NULL,           "\\" },     // fullwidth backslash
	{ 0xff3d,                   NULL,           "]" },      // fullwidth right bracket
	{ 0xff3e,                   NULL,           "^" },      // fullwidth caret
	{ 0xff3f,                   NULL,           "_" },      // fullwidth underscore
	{ 0xff40,                   NULL,           "`" },      // fullwidth backquote
	{ 0xff41,                   NULL,           "a" },      // fullwidth 'a'
	{ 0xff42,                   NULL,           "b" },      // fullwidth 'b'
	{ 0xff43,                   NULL,           "c" },      // fullwidth 'c'
	{ 0xff44,                   NULL,           "d" },      // fullwidth 'd'
	{ 0xff45,                   NULL,           "e" },      // fullwidth 'e'
	{ 0xff46,                   NULL,           "f" },      // fullwidth 'f'
	{ 0xff47,                   NULL,           "g" },      // fullwidth 'g'
	{ 0xff48,                   NULL,           "h" },      // fullwidth 'h'
	{ 0xff49,                   NULL,           "i" },      // fullwidth 'i'
	{ 0xff4a,                   NULL,           "j" },      // fullwidth 'j'
	{ 0xff4b,                   NULL,           "k" },      // fullwidth 'k'
	{ 0xff4c,                   NULL,           "l" },      // fullwidth 'l'
	{ 0xff4d,                   NULL,           "m" },      // fullwidth 'm'
	{ 0xff4e,                   NULL,           "n" },      // fullwidth 'n'
	{ 0xff4f,                   NULL,           "o" },      // fullwidth 'o'
	{ 0xff50,                   NULL,           "p" },      // fullwidth 'p'
	{ 0xff51,                   NULL,           "q" },      // fullwidth 'q'
	{ 0xff52,                   NULL,           "r" },      // fullwidth 'r'
	{ 0xff53,                   NULL,           "s" },      // fullwidth 's'
	{ 0xff54,                   NULL,           "t" },      // fullwidth 't'
	{ 0xff55,                   NULL,           "u" },      // fullwidth 'u'
	{ 0xff56,                   NULL,           "v" },      // fullwidth 'v'
	{ 0xff57,                   NULL,           "w" },      // fullwidth 'w'
	{ 0xff58,                   NULL,           "x" },      // fullwidth 'x'
	{ 0xff59,                   NULL,           "y" },      // fullwidth 'y'
	{ 0xff5a,                   NULL,           "z" },      // fullwidth 'z'
	{ 0xff5b,                   NULL,           "{" },      // fullwidth left brace
	{ 0xff5c,                   NULL,           "|" },      // fullwidth vertical bar
	{ 0xff5d,                   NULL,           "}" },      // fullwidth right brace
	{ 0xff5e,                   NULL,           "~" },      // fullwidth tilde
	{ 0xff5f,                   NULL,           "((" },     // fullwidth double left parenthesis
	{ 0xff60,                   NULL,           "))" },     // fullwidth double right parenthesis
	{ 0xffe0,                   NULL,           "\xC2\xA2" },       // fullwidth cent sign
	{ 0xffe1,                   NULL,           "\xC2\xA3" },       // fullwidth pound sign
	{ 0xffe4,                   NULL,           "\xC2\xA4" },       // fullwidth broken bar
	{ 0xffe5,                   NULL,           "\xC2\xA5" },       // fullwidth yen sign
	{ 0xffe6,                   NULL,           "\xE2\x82\xA9" },   // fullwidth won sign
	{ 0xffe9,                   NULL,           "\xE2\x86\x90" },   // fullwidth left arrow
	{ 0xffea,                   NULL,           "\xE2\x86\x91" },   // fullwidth up arrow
	{ 0xffeb,                   NULL,           "\xE2\x86\x92" },   // fullwidth right arrow
	{ 0xffec,                   NULL,           "\xE2\x86\x93" },   // fullwidth down arrow
	{ 0xffed,                   NULL,           "\xE2\x96\xAA" },   // fullwidth solid box
	{ 0xffee,                   NULL,           "\xE2\x97\xA6" },   // fullwidth open circle
	{ UCHAR_SHIFT_1,            "Shift",        NULL },     // Shift key
	{ UCHAR_SHIFT_2,            "Ctrl",         NULL },     // Ctrl key
	{ UCHAR_MAMEKEY(F1),        "F1",           NULL },     // F1 function key
	{ UCHAR_MAMEKEY(F2),        "F2",           NULL },     // F2 function key
	{ UCHAR_MAMEKEY(F3),        "F3",           NULL },     // F3 function key
	{ UCHAR_MAMEKEY(F4),        "F4",           NULL },     // F4 function key
	{ UCHAR_MAMEKEY(F5),        "F5",           NULL },     // F5 function key
	{ UCHAR_MAMEKEY(F6),        "F6",           NULL },     // F6 function key
	{ UCHAR_MAMEKEY(F7),        "F7",           NULL },     // F7 function key
	{ UCHAR_MAMEKEY(F8),        "F8",           NULL },     // F8 function key
	{ UCHAR_MAMEKEY(F9),        "F9",           NULL },     // F9 function key
	{ UCHAR_MAMEKEY(F10),       "F10",          NULL },     // F10 function key
	{ UCHAR_MAMEKEY(F11),       "F11",          NULL },     // F11 function key
	{ UCHAR_MAMEKEY(F12),       "F12",          NULL },     // F12 function key
	{ UCHAR_MAMEKEY(F13),       "F13",          NULL },     // F13 function key
	{ UCHAR_MAMEKEY(F14),       "F14",          NULL },     // F14 function key
	{ UCHAR_MAMEKEY(F15),       "F15",          NULL },     // F15 function key
	{ UCHAR_MAMEKEY(ESC),       "Esc",          "\033" },   // Esc key
	{ UCHAR_MAMEKEY(INSERT),    "Insert",       NULL },     // Insert key
	{ UCHAR_MAMEKEY(DEL),       "Delete",       "\010" },   // Delete key
	{ UCHAR_MAMEKEY(HOME),      "Home",         "\014" },   // Home key
	{ UCHAR_MAMEKEY(END),       "End",          NULL },     // End key
	{ UCHAR_MAMEKEY(PGUP),      "Page Up",      NULL },     // Page Up key
	{ UCHAR_MAMEKEY(PGDN),      "Page Down",    NULL },     // Page Down key
	{ UCHAR_MAMEKEY(LEFT),      "Cursor Left",  NULL },     // Cursor Left
	{ UCHAR_MAMEKEY(RIGHT),     "Cursor Right", NULL },     // Cursor Right
	{ UCHAR_MAMEKEY(UP),        "Cursor Up",    NULL },     // Cursor Up
	{ UCHAR_MAMEKEY(DOWN),      "Cursor Down",  NULL },     // Cursor Down
	{ UCHAR_MAMEKEY(0_PAD),     "Keypad 0",     NULL },     // 0 on the numeric keypad
	{ UCHAR_MAMEKEY(1_PAD),     "Keypad 1",     NULL },     // 1 on the numeric keypad
	{ UCHAR_MAMEKEY(2_PAD),     "Keypad 2",     NULL },     // 2 on the numeric keypad
	{ UCHAR_MAMEKEY(3_PAD),     "Keypad 3",     NULL },     // 3 on the numeric keypad
	{ UCHAR_MAMEKEY(4_PAD),     "Keypad 4",     NULL },     // 4 on the numeric keypad
	{ UCHAR_MAMEKEY(5_PAD),     "Keypad 5",     NULL },     // 5 on the numeric keypad
	{ UCHAR_MAMEKEY(6_PAD),     "Keypad 6",     NULL },     // 6 on the numeric keypad
	{ UCHAR_MAMEKEY(7_PAD),     "Keypad 7",     NULL },     // 7 on the numeric keypad
	{ UCHAR_MAMEKEY(8_PAD),     "Keypad 8",     NULL },     // 8 on the numeric keypad
	{ UCHAR_MAMEKEY(9_PAD),     "Keypad 9",     NULL },     // 9 on the numeric keypad
	{ UCHAR_MAMEKEY(SLASH_PAD), "Keypad /",     NULL },     // / on the numeric keypad
	{ UCHAR_MAMEKEY(ASTERISK),  "Keypad *",     NULL },     // * on the numeric keypad
	{ UCHAR_MAMEKEY(MINUS_PAD), "Keypad -",     NULL },     // - on the numeric Keypad
	{ UCHAR_MAMEKEY(PLUS_PAD),  "Keypad +",     NULL },     // + on the numeric Keypad
	{ UCHAR_MAMEKEY(DEL_PAD),   "Keypad .",     NULL },     // . on the numeric keypad
	{ UCHAR_MAMEKEY(ENTER_PAD), "Keypad Enter", NULL },     // Enter on the numeric keypad
	{ UCHAR_MAMEKEY(PRTSCR),    "Print Screen", NULL },     // Print Screen key
	{ UCHAR_MAMEKEY(PAUSE),     "Pause",        NULL },     // Pause key
	{ UCHAR_MAMEKEY(LSHIFT),    "Left Shift",   NULL },     // Left Shift key
	{ UCHAR_MAMEKEY(RSHIFT),    "Right Shift",  NULL },     // Right Shift key
	{ UCHAR_MAMEKEY(LCONTROL),  "Left Ctrl",    NULL },     // Left Control key
	{ UCHAR_MAMEKEY(RCONTROL),  "Right Ctrl",   NULL },     // Right Control key
	{ UCHAR_MAMEKEY(LALT),      "Left Alt",     NULL },     // Left Alt key
	{ UCHAR_MAMEKEY(RALT),      "Right Alt",    NULL },     // Right Alt key
	{ UCHAR_MAMEKEY(SCRLOCK),   "Scroll Lock",  NULL },     // Scroll Lock key
	{ UCHAR_MAMEKEY(NUMLOCK),   "Num Lock",     NULL },     // Num Lock key
	{ UCHAR_MAMEKEY(CAPSLOCK),  "Caps Lock",    NULL },     // Caps Lock key
	{ UCHAR_MAMEKEY(LWIN),      "Left Win",     NULL },     // Left Win key
	{ UCHAR_MAMEKEY(RWIN),      "Right Win",    NULL },     // Right Win key
	{ UCHAR_MAMEKEY(MENU),      "Menu",         NULL },     // Menu key
	{ UCHAR_MAMEKEY(CANCEL),    "Break",        NULL }      // Break/Pause key
};



//**************************************************************************
//  COMMON SHARED STRINGS
//**************************************************************************

static const struct
{
	UINT32 id;
=======
//  COMMON SHARED STRINGS
//**************************************************************************

const struct
{
	u32 id;
>>>>>>> upstream/master
	const char *string;
} input_port_default_strings[] =
{
	{ INPUT_STRING_Off, "Off" },
	{ INPUT_STRING_On, "On" },
	{ INPUT_STRING_No, "No" },
	{ INPUT_STRING_Yes, "Yes" },
	{ INPUT_STRING_Lives, "Lives" },
	{ INPUT_STRING_Bonus_Life, "Bonus Life" },
	{ INPUT_STRING_Difficulty, "Difficulty" },
	{ INPUT_STRING_Demo_Sounds, "Demo Sounds" },
	{ INPUT_STRING_Coinage, "Coinage" },
	{ INPUT_STRING_Coin_A, "Coin A" },
	{ INPUT_STRING_Coin_B, "Coin B" },
	{ INPUT_STRING_9C_1C, "9 Coins/1 Credit" },
	{ INPUT_STRING_8C_1C, "8 Coins/1 Credit" },
	{ INPUT_STRING_7C_1C, "7 Coins/1 Credit" },
	{ INPUT_STRING_6C_1C, "6 Coins/1 Credit" },
	{ INPUT_STRING_5C_1C, "5 Coins/1 Credit" },
	{ INPUT_STRING_4C_1C, "4 Coins/1 Credit" },
	{ INPUT_STRING_3C_1C, "3 Coins/1 Credit" },
	{ INPUT_STRING_8C_3C, "8 Coins/3 Credits" },
	{ INPUT_STRING_4C_2C, "4 Coins/2 Credits" },
	{ INPUT_STRING_2C_1C, "2 Coins/1 Credit" },
	{ INPUT_STRING_5C_3C, "5 Coins/3 Credits" },
	{ INPUT_STRING_3C_2C, "3 Coins/2 Credits" },
	{ INPUT_STRING_4C_3C, "4 Coins/3 Credits" },
	{ INPUT_STRING_4C_4C, "4 Coins/4 Credits" },
	{ INPUT_STRING_3C_3C, "3 Coins/3 Credits" },
	{ INPUT_STRING_2C_2C, "2 Coins/2 Credits" },
	{ INPUT_STRING_1C_1C, "1 Coin/1 Credit" },
	{ INPUT_STRING_4C_5C, "4 Coins/5 Credits" },
	{ INPUT_STRING_3C_4C, "3 Coins/4 Credits" },
	{ INPUT_STRING_2C_3C, "2 Coins/3 Credits" },
	{ INPUT_STRING_4C_7C, "4 Coins/7 Credits" },
	{ INPUT_STRING_2C_4C, "2 Coins/4 Credits" },
	{ INPUT_STRING_1C_2C, "1 Coin/2 Credits" },
	{ INPUT_STRING_2C_5C, "2 Coins/5 Credits" },
	{ INPUT_STRING_2C_6C, "2 Coins/6 Credits" },
	{ INPUT_STRING_1C_3C, "1 Coin/3 Credits" },
	{ INPUT_STRING_2C_7C, "2 Coins/7 Credits" },
	{ INPUT_STRING_2C_8C, "2 Coins/8 Credits" },
	{ INPUT_STRING_1C_4C, "1 Coin/4 Credits" },
	{ INPUT_STRING_1C_5C, "1 Coin/5 Credits" },
	{ INPUT_STRING_1C_6C, "1 Coin/6 Credits" },
	{ INPUT_STRING_1C_7C, "1 Coin/7 Credits" },
	{ INPUT_STRING_1C_8C, "1 Coin/8 Credits" },
	{ INPUT_STRING_1C_9C, "1 Coin/9 Credits" },
	{ INPUT_STRING_Free_Play, "Free Play" },
	{ INPUT_STRING_Cabinet, "Cabinet" },
	{ INPUT_STRING_Upright, "Upright" },
	{ INPUT_STRING_Cocktail, "Cocktail" },
	{ INPUT_STRING_Flip_Screen, "Flip Screen" },
	{ INPUT_STRING_Service_Mode, "Service Mode" },
	{ INPUT_STRING_Pause, "Pause" },
	{ INPUT_STRING_Test, "Test" },
	{ INPUT_STRING_Tilt, "Tilt" },
	{ INPUT_STRING_Version, "Version" },
	{ INPUT_STRING_Region, "Region" },
	{ INPUT_STRING_International, "International" },
	{ INPUT_STRING_Japan, "Japan" },
	{ INPUT_STRING_USA, "USA" },
	{ INPUT_STRING_Europe, "Europe" },
	{ INPUT_STRING_Asia, "Asia" },
	{ INPUT_STRING_China, "China" },
	{ INPUT_STRING_Hong_Kong, "Hong Kong" },
	{ INPUT_STRING_Korea, "Korea" },
	{ INPUT_STRING_Southeast_Asia, "Southeast Asia" },
	{ INPUT_STRING_Taiwan, "Taiwan" },
	{ INPUT_STRING_World, "World" },
	{ INPUT_STRING_Language, "Language" },
	{ INPUT_STRING_English, "English" },
	{ INPUT_STRING_Japanese, "Japanese" },
	{ INPUT_STRING_Chinese, "Chinese" },
	{ INPUT_STRING_French, "French" },
	{ INPUT_STRING_German, "German" },
	{ INPUT_STRING_Italian, "Italian" },
	{ INPUT_STRING_Korean, "Korean" },
	{ INPUT_STRING_Spanish, "Spanish" },
	{ INPUT_STRING_Very_Easy, "Very Easy" },
	{ INPUT_STRING_Easiest, "Easiest" },
	{ INPUT_STRING_Easier, "Easier" },
	{ INPUT_STRING_Easy, "Easy" },
	{ INPUT_STRING_Medium_Easy, "Medium Easy" },
	{ INPUT_STRING_Normal, "Normal" },
	{ INPUT_STRING_Medium, "Medium" },
	{ INPUT_STRING_Medium_Hard, "Medium Hard" },
	{ INPUT_STRING_Hard, "Hard" },
	{ INPUT_STRING_Harder, "Harder" },
	{ INPUT_STRING_Hardest, "Hardest" },
	{ INPUT_STRING_Very_Hard, "Very Hard" },
	{ INPUT_STRING_Medium_Difficult, "Medium Difficult" },
	{ INPUT_STRING_Difficult, "Difficult" },
	{ INPUT_STRING_Very_Difficult, "Very Difficult" },
	{ INPUT_STRING_Very_Low, "Very Low" },
	{ INPUT_STRING_Low, "Low" },
	{ INPUT_STRING_High, "High" },
	{ INPUT_STRING_Higher, "Higher" },
	{ INPUT_STRING_Highest, "Highest" },
	{ INPUT_STRING_Very_High, "Very High" },
	{ INPUT_STRING_Players, "Players" },
	{ INPUT_STRING_Controls, "Controls" },
	{ INPUT_STRING_Dual, "Dual" },
	{ INPUT_STRING_Single, "Single" },
	{ INPUT_STRING_Game_Time, "Game Time" },
	{ INPUT_STRING_Continue_Price, "Continue Price" },
	{ INPUT_STRING_Controller, "Controller" },
	{ INPUT_STRING_Light_Gun, "Light Gun" },
	{ INPUT_STRING_Joystick, "Joystick" },
	{ INPUT_STRING_Trackball, "Trackball" },
	{ INPUT_STRING_Continues, "Continues" },
	{ INPUT_STRING_Allow_Continue, "Allow Continue" },
	{ INPUT_STRING_Level_Select, "Level Select" },
	{ INPUT_STRING_Infinite, "Infinite" },
	{ INPUT_STRING_Stereo, "Stereo" },
	{ INPUT_STRING_Mono, "Mono" },
	{ INPUT_STRING_Unused, "Unused" },
	{ INPUT_STRING_Unknown, "Unknown" },
	{ INPUT_STRING_Standard, "Standard" },
	{ INPUT_STRING_Reverse, "Reverse" },
	{ INPUT_STRING_Alternate, "Alternate" },
	{ INPUT_STRING_None, "None" },
};

<<<<<<< HEAD
=======
} // TODO: anonymous namespace


// XML attributes for the different types
const char *const ioport_manager::seqtypestrings[] = { "standard", "increment", "decrement" };


u8 const inp_header::MAGIC[inp_header::OFFS_BASETIME - inp_header::OFFS_MAGIC] = { 'M', 'A', 'M', 'E', 'I', 'N', 'P', 0 };

>>>>>>> upstream/master


//**************************************************************************
//  BUILT-IN CORE MAPPINGS
//**************************************************************************

#include "inpttype.h"



//**************************************************************************
//  PORT CONFIGURATIONS
//**************************************************************************

//**************************************************************************
//  I/O PORT LIST
//**************************************************************************

//-------------------------------------------------
//  append - append the given device's input ports
//  to the current list
//-------------------------------------------------

void ioport_list::append(device_t &device, std::string &errorbuf)
{
	// no constructor, no list
	ioport_constructor constructor = device.input_ports();
<<<<<<< HEAD
	if (constructor == NULL)
=======
	if (constructor == nullptr)
>>>>>>> upstream/master
		return;

	// reset error buffer
	errorbuf.clear();

	// detokenize into the list
	(*constructor)(device, *this, errorbuf);

	// collapse fields and sort the list
<<<<<<< HEAD
	for (ioport_port *port = first(); port != NULL; port = port->next())
		port->collapse_fields(errorbuf);
}


#ifdef USE_CUSTOM_BUTTON
	static INPUT_PORTS_START( custom1p )
		PORT_START("CUSTOM1P")
#ifdef USE_AUTOFIRE
		PORT_BIT( 1 << 0, IP_ACTIVE_HIGH, IPT_TOGGLE_AUTOFIRE ) PORT_PLAYER(1) PORT_TOGGLE
#endif /* USE_AUTOFIRE */
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM1 ) PORT_PLAYER(1)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM2 ) PORT_PLAYER(1)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM3 ) PORT_PLAYER(1)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM4 ) PORT_PLAYER(1)
	INPUT_PORTS_END

	static INPUT_PORTS_START( custom2p )
		PORT_START("CUSTOM2P")
#ifdef USE_AUTOFIRE
		PORT_BIT( 1 << 1, IP_ACTIVE_HIGH, IPT_TOGGLE_AUTOFIRE ) PORT_PLAYER(2) PORT_TOGGLE
#endif /* USE_AUTOFIRE */
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM1 ) PORT_PLAYER(2)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM2 ) PORT_PLAYER(2)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM3 ) PORT_PLAYER(2)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM4 ) PORT_PLAYER(2)
	INPUT_PORTS_END

	static INPUT_PORTS_START( custom3p )
		PORT_START("CUSTOM3P")
#ifdef USE_AUTOFIRE
		PORT_BIT( 1 << 2, IP_ACTIVE_HIGH, IPT_TOGGLE_AUTOFIRE ) PORT_PLAYER(3) PORT_TOGGLE
#endif /* USE_AUTOFIRE */
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM1 ) PORT_PLAYER(3)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM2 ) PORT_PLAYER(3)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM3 ) PORT_PLAYER(3)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM4 ) PORT_PLAYER(3)
	INPUT_PORTS_END

	static INPUT_PORTS_START( custom4p )
		PORT_START("CUSTOM4P")
#ifdef USE_AUTOFIRE
		PORT_BIT( 1 << 3, IP_ACTIVE_HIGH, IPT_TOGGLE_AUTOFIRE ) PORT_PLAYER(4) PORT_TOGGLE
#endif /* USE_AUTOFIRE */
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM1 ) PORT_PLAYER(4)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM2 ) PORT_PLAYER(4)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM3 ) PORT_PLAYER(4)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM4 ) PORT_PLAYER(4)
	INPUT_PORTS_END

	static INPUT_PORTS_START( custom5p )
		PORT_START("CUSTOM5P")
#ifdef USE_AUTOFIRE
		PORT_BIT( 1 << 4, IP_ACTIVE_HIGH, IPT_TOGGLE_AUTOFIRE ) PORT_PLAYER(5) PORT_TOGGLE
#endif /* USE_AUTOFIRE */
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM1 ) PORT_PLAYER(5)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM2 ) PORT_PLAYER(5)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM3 ) PORT_PLAYER(5)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM4 ) PORT_PLAYER(5)
	INPUT_PORTS_END

	static INPUT_PORTS_START( custom6p )
		PORT_START("CUSTOM6P")
#ifdef USE_AUTOFIRE
		PORT_BIT( 1 << 5, IP_ACTIVE_HIGH, IPT_TOGGLE_AUTOFIRE ) PORT_PLAYER(6) PORT_TOGGLE
#endif /* USE_AUTOFIRE */
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM1 ) PORT_PLAYER(6)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM2 ) PORT_PLAYER(6)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM3 ) PORT_PLAYER(6)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM4 ) PORT_PLAYER(6)
	INPUT_PORTS_END

	static INPUT_PORTS_START( custom7p )
		PORT_START("CUSTOM7P")
#ifdef USE_AUTOFIRE
		PORT_BIT( 1 << 6, IP_ACTIVE_HIGH, IPT_TOGGLE_AUTOFIRE ) PORT_PLAYER(7) PORT_TOGGLE
#endif /* USE_AUTOFIRE */
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM1 ) PORT_PLAYER(7)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM2 ) PORT_PLAYER(7)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM3 ) PORT_PLAYER(7)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM4 ) PORT_PLAYER(7)
	INPUT_PORTS_END

	static INPUT_PORTS_START( custom8p )
		PORT_START("CUSTOM8P")
#ifdef USE_AUTOFIRE
		PORT_BIT( 1 << 7, IP_ACTIVE_HIGH, IPT_TOGGLE_AUTOFIRE ) PORT_PLAYER(8) PORT_TOGGLE
#endif /* USE_AUTOFIRE */
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM1 ) PORT_PLAYER(8)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM2 ) PORT_PLAYER(8)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM3 ) PORT_PLAYER(8)
		PORT_BIT( 0, IP_ACTIVE_LOW, IPT_CUSTOM4 ) PORT_PLAYER(8)
	INPUT_PORTS_END

/*-------------------------------------------------
    input_port_list_custom - initialize an input
    port list structure and allocate ports
    according to the given tokens
-------------------------------------------------*/

void ioport_list::append_custom(device_t &device, std::string &errorbuf)
{
	ioport_field *field;
	int nplayer = 0;

	// no constructor, no list
	ioport_constructor constructor = device.input_ports();
	if (constructor == NULL)
		return;

	// reset error buffer
	errorbuf.clear();

	// detokenize into the list
	(*constructor)(device, *this, errorbuf);

	// collapse fields and sort the list 
	for (ioport_port *port = first(); port != NULL; port = port->next())
	{
		for (field = port->first_field(); field != NULL; field = field->next())
		{
			if (nplayer < field->player()+1)
				nplayer = field->player()+1;
		}
		port->collapse_fields(errorbuf);
	}

	// mamep: append custom ports if needed
	if (nplayer > 0)
		INPUT_PORTS_NAME(custom1p)(device, *this, errorbuf);
	if (nplayer > 1)
		INPUT_PORTS_NAME(custom2p)(device, *this, errorbuf);
	if (nplayer > 2)
		INPUT_PORTS_NAME(custom3p)(device, *this, errorbuf);
	if (nplayer > 3)
		INPUT_PORTS_NAME(custom4p)(device, *this, errorbuf);
	if (nplayer > 4)
		INPUT_PORTS_NAME(custom5p)(device, *this, errorbuf);
	if (nplayer > 5)
		INPUT_PORTS_NAME(custom6p)(device, *this, errorbuf);
	if (nplayer > 6)
		INPUT_PORTS_NAME(custom7p)(device, *this, errorbuf);
	if (nplayer > 7)
		INPUT_PORTS_NAME(custom8p)(device, *this, errorbuf);
}
#endif /* USE_CUSTOM_BUTTON */


=======
	for (auto &port : *this)
		port.second->collapse_fields(errorbuf);
}


>>>>>>> upstream/master

//**************************************************************************
//  INPUT TYPE ENTRY
//**************************************************************************

//-------------------------------------------------
//  input_type_entry - constructors
//-------------------------------------------------

input_type_entry::input_type_entry(ioport_type type, ioport_group group, int player, const char *token, const char *name, input_seq standard)
<<<<<<< HEAD
	: m_next(NULL),
=======
	: m_next(nullptr),
>>>>>>> upstream/master
		m_type(type),
		m_group(group),
		m_player(player),
		m_token(token),
		m_name(name)
{
	m_defseq[SEQ_TYPE_STANDARD] = m_seq[SEQ_TYPE_STANDARD] = standard;
}

input_type_entry::input_type_entry(ioport_type type, ioport_group group, int player, const char *token, const char *name, input_seq standard, input_seq decrement, input_seq increment)
<<<<<<< HEAD
	: m_next(NULL),
=======
	: m_next(nullptr),
>>>>>>> upstream/master
		m_type(type),
		m_group(group),
		m_player(player),
		m_token(token),
		m_name(name)
{
	m_defseq[SEQ_TYPE_STANDARD] = m_seq[SEQ_TYPE_STANDARD] = standard;
	m_defseq[SEQ_TYPE_INCREMENT] = m_seq[SEQ_TYPE_INCREMENT] = increment;
	m_defseq[SEQ_TYPE_DECREMENT] = m_seq[SEQ_TYPE_DECREMENT] = decrement;
}


//-------------------------------------------------
//  configure_osd - set the token and name of an
//  OSD entry
//-------------------------------------------------

void input_type_entry::configure_osd(const char *token, const char *name)
{
	assert(m_type >= IPT_OSD_1 && m_type <= IPT_OSD_16);
	m_token = token;
	m_name = name;
}


//-------------------------------------------------
//  restore_default_seq - restores the sequence
//  from the default
//-------------------------------------------------

void input_type_entry::restore_default_seq()
{
	for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
		m_seq[seqtype] = defseq(seqtype);
}


//**************************************************************************
//  DIGITAL JOYSTICKS
//**************************************************************************

//-------------------------------------------------
//  digital_joystick - constructor
//-------------------------------------------------

digital_joystick::digital_joystick(int player, int number)
<<<<<<< HEAD
	:   m_next(NULL),
=======
	:   m_next(nullptr),
>>>>>>> upstream/master
		m_player(player),
		m_number(number),
		m_current(0),
		m_current4way(0),
		m_previous(0)
{
}


//-------------------------------------------------
//  set_axis - configure a single axis of a
//  digital joystick
//-------------------------------------------------

digital_joystick::direction_t digital_joystick::add_axis(ioport_field &field)
{
	direction_t direction = direction_t((field.type() - (IPT_DIGITAL_JOYSTICK_FIRST + 1)) % 4);
	m_field[direction].append(*global_alloc(simple_list_wrapper<ioport_field>(&field)));
	return direction;
}


//-------------------------------------------------
//  frame_update - update the state of digital
//  joysticks prior to accumulating the results
//  in a port
//-------------------------------------------------

void digital_joystick::frame_update()
{
	// remember previous state and reset current state
	m_previous = m_current;
	m_current = 0;

	// read all the associated ports
<<<<<<< HEAD
	running_machine *machine = NULL;
	for (direction_t direction = JOYDIR_UP; direction < JOYDIR_COUNT; ++direction)
		for (const simple_list_wrapper<ioport_field> *i = m_field[direction].first(); i != NULL; i = i->next())
		{
			machine = &i->object()->machine();
			if (machine->input().seq_pressed(i->object()->seq(SEQ_TYPE_STANDARD)))
=======
	running_machine *machine = nullptr;
	for (direction_t direction = JOYDIR_UP; direction < JOYDIR_COUNT; ++direction)
		for (const simple_list_wrapper<ioport_field> &i : m_field[direction])
		{
			machine = &i.object()->machine();
			if (machine->input().seq_pressed(i.object()->seq(SEQ_TYPE_STANDARD)))
>>>>>>> upstream/master
				m_current |= 1 << direction;
		}

	// lock out opposing directions (left + right or up + down)
	if ((m_current & (UP_BIT | DOWN_BIT)) == (UP_BIT | DOWN_BIT))
		m_current &= ~(UP_BIT | DOWN_BIT);
	if ((m_current & (LEFT_BIT | RIGHT_BIT)) == (LEFT_BIT | RIGHT_BIT))
		m_current &= ~(LEFT_BIT | RIGHT_BIT);

	// only update 4-way case if joystick has moved
	if (m_current != m_previous)
	{
		m_current4way = m_current;

		//
		//  If joystick is pointing at a diagonal, acknowledge that the player moved
		//  the joystick by favoring a direction change.  This minimizes frustration
		//  and maximizes responsiveness.
		//
		//  For example, if you are holding "left" then switch to "up" (where both left
		//  and up are briefly pressed at the same time), we'll transition immediately
		//  to "up."
		//
		//  Zero any switches that didn't change from the previous to current state.
		//
		if ((m_current4way & (UP_BIT | DOWN_BIT)) &&
			(m_current4way & (LEFT_BIT | RIGHT_BIT)))
		{
			m_current4way ^= m_current4way & m_previous;
		}

		//
		//  If we are still pointing at a diagonal, we are in an indeterminant state.
		//
		//  This could happen if the player moved the joystick from the idle position directly
		//  to a diagonal, or from one diagonal directly to an extreme diagonal.
		//
		//  The chances of this happening with a keyboard are slim, but we still need to
		//  constrain this case.
		//
		//  For now, just resolve randomly.
		//
		if ((m_current4way & (UP_BIT | DOWN_BIT)) &&
			(m_current4way & (LEFT_BIT | RIGHT_BIT)))
		{
			if (machine->rand() & 1)
				m_current4way &= ~(LEFT_BIT | RIGHT_BIT);
			else
				m_current4way &= ~(UP_BIT | DOWN_BIT);
		}
	}
}



//**************************************************************************
<<<<<<< HEAD
//  NATURAL KEYBOARD
//**************************************************************************

//-------------------------------------------------
//  natural_keyboard - constructor
//-------------------------------------------------

natural_keyboard::natural_keyboard(running_machine &machine)
	: m_machine(machine),
		m_bufbegin(0),
		m_bufend(0),
		m_status_keydown(false),
		m_last_cr(false),
		m_timer(NULL),
		m_current_rate(attotime::zero)
{
	m_queue_chars = ioport_queue_chars_delegate();
	m_accept_char = ioport_accept_char_delegate();
	m_charqueue_empty = ioport_charqueue_empty_delegate();
}

//-------------------------------------------------
//  initialize - initialize natural keyboard
//  support
//-------------------------------------------------

void natural_keyboard::initialize()
{
	// posting keys directly only makes sense for a computer
	if (machine().ioport().has_keyboard())
	{
		m_buffer.resize(KEY_BUFFER_SIZE);
		m_timer = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(natural_keyboard::timer), this));
		build_codes(machine().ioport());
	}
}
//-------------------------------------------------
//  configure - configure callbacks for full-
//  featured keyboard support
//-------------------------------------------------

void natural_keyboard::configure(ioport_queue_chars_delegate queue_chars, ioport_accept_char_delegate accept_char, ioport_charqueue_empty_delegate charqueue_empty)
{
	// set the callbacks
	m_queue_chars = queue_chars;
	m_accept_char = accept_char;
	m_charqueue_empty = charqueue_empty;
}


//-------------------------------------------------
//  post - post a single character
//-------------------------------------------------

void natural_keyboard::post(unicode_char ch)
{
	// ignore any \n that are preceded by \r
	if (m_last_cr && ch == '\n')
	{
		m_last_cr = false;
		return;
	}

	// change all eolns to '\r'
	if (ch == '\n')
		ch = '\r';
	else
		m_last_cr = (ch == '\r');

	// logging
	if (LOG_NATURAL_KEYBOARD)
	{
		const keycode_map_entry *code = find_code(ch);
		std::string tempstr;
		machine().logerror("natural_keyboard::post(): code=%i (%s) field->name='%s'\n", int(ch), unicode_to_string(tempstr, ch), (code != NULL && code->field[0] != NULL) ? code->field[0]->name() : "<null>");
	}

	// can we post this key in the queue directly?
	if (can_post_directly(ch))
		internal_post(ch);

	// can we post this key with an alternate representation?
	else if (can_post_alternate(ch))
	{
		const char_info *info = char_info::find(ch);
		assert(info != NULL && info->alternate != NULL);
		const char *altstring = info->alternate;
		while (*altstring != 0)
		{
			altstring += uchar_from_utf8(&ch, altstring, strlen(altstring));
			internal_post(ch);
		}
	}
}


//-------------------------------------------------
//  post - post a unicode encoded string
//-------------------------------------------------

void natural_keyboard::post(const unicode_char *text, size_t length, const attotime &rate)
{
	// set the fixed rate
	m_current_rate = rate;

	// 0 length means strlen
	if (length == 0)
		for (const unicode_char *scan = text; *scan != 0; scan++)
			length++;

	// iterate over characters or until the buffer is full up
	while (length > 0 && !full())
	{
		// fetch next character
		post(*text++);
		length--;
	}
}


//-------------------------------------------------
//  post_utf8 - post a UTF-8 encoded string
//-------------------------------------------------

void natural_keyboard::post_utf8(const char *text, size_t length, const attotime &rate)
{
	// set the fixed rate
	m_current_rate = rate;

	// 0-length means strlen
	if (length == 0)
		length = strlen(text);

	// iterate until out of characters
	while (length > 0)
	{
		// decode the next character
		unicode_char uc;
		int count = uchar_from_utf8(&uc, text, length);
		if (count < 0)
		{
			count = 1;
			uc = INVALID_CHAR;
		}

		// append to the buffer
		post(uc);
		text += count;
		length -= count;
	}
}


//-------------------------------------------------
//  post_coded - post a coded string
//-------------------------------------------------

void natural_keyboard::post_coded(const char *text, size_t length, const attotime &rate)
{
	static const struct
	{
		const char *key;
		unicode_char code;
	} codes[] =
	{
		{ "BACKSPACE",  8 },
		{ "BS",         8 },
		{ "BKSP",       8 },
		{ "DEL",        UCHAR_MAMEKEY(DEL) },
		{ "DELETE",     UCHAR_MAMEKEY(DEL) },
		{ "END",        UCHAR_MAMEKEY(END) },
		{ "ENTER",      13 },
		{ "ESC",        '\033' },
		{ "HOME",       UCHAR_MAMEKEY(HOME) },
		{ "INS",        UCHAR_MAMEKEY(INSERT) },
		{ "INSERT",     UCHAR_MAMEKEY(INSERT) },
		{ "PGDN",       UCHAR_MAMEKEY(PGDN) },
		{ "PGUP",       UCHAR_MAMEKEY(PGUP) },
		{ "SPACE",      32 },
		{ "TAB",        9 },
		{ "F1",         UCHAR_MAMEKEY(F1) },
		{ "F2",         UCHAR_MAMEKEY(F2) },
		{ "F3",         UCHAR_MAMEKEY(F3) },
		{ "F4",         UCHAR_MAMEKEY(F4) },
		{ "F5",         UCHAR_MAMEKEY(F5) },
		{ "F6",         UCHAR_MAMEKEY(F6) },
		{ "F7",         UCHAR_MAMEKEY(F7) },
		{ "F8",         UCHAR_MAMEKEY(F8) },
		{ "F9",         UCHAR_MAMEKEY(F9) },
		{ "F10",        UCHAR_MAMEKEY(F10) },
		{ "F11",        UCHAR_MAMEKEY(F11) },
		{ "F12",        UCHAR_MAMEKEY(F12) },
		{ "QUOTE",      '\"' }
	};

	// set the fixed rate
	m_current_rate = rate;

	// 0-length means strlen
	if (length == 0)
		length = strlen(text);

	// iterate through the source string
	size_t curpos = 0;
	while (curpos < length)
	{
		// extract next character
		unicode_char ch = text[curpos];
		size_t increment = 1;

		// look for escape characters
		if (ch == '{')
			for (int codenum = 0; codenum < ARRAY_LENGTH(codes); codenum++)
			{
				size_t keylen = strlen(codes[codenum].key);
				if (curpos + keylen + 2 <= length)
					if (core_strnicmp(codes[codenum].key, &text[curpos + 1], keylen) == 0 && text[curpos + keylen + 1] == '}')
					{
						ch = codes[codenum].code;
						increment = keylen + 2;
					}
			}

		// if we got a code, post it
		if (ch != 0)
			post(ch);
		curpos += increment;
	}
}


//-------------------------------------------------
//  build_codes - given an input port table, create
//  an input code table useful for mapping unicode
//  chars
//-------------------------------------------------

void natural_keyboard::build_codes(ioport_manager &manager)
{
	// iterate over shift keys
	ioport_field *shift[UCHAR_SHIFT_END + 1 - UCHAR_SHIFT_BEGIN] = { 0 };
	for (int curshift = 0; curshift <= ARRAY_LENGTH(shift); curshift++)
		if (curshift == 0 || shift[curshift - 1] != NULL)

			// iterate over ports and fields
			for (ioport_port *port = manager.first_port(); port != NULL; port = port->next())
				for (ioport_field *field = port->first_field(); field != NULL; field = field->next())
					if (field->type() == IPT_KEYBOARD)
					{
						// fetch the code, ignoring 0
						unicode_char code = field->keyboard_code(curshift);
						if (code == 0)
							continue;

						// is this a shifter key?
						if (code >= UCHAR_SHIFT_BEGIN && code <= UCHAR_SHIFT_END)
							shift[code - UCHAR_SHIFT_BEGIN] = field;

						// not a shifter key; record normally
						else
						{
							keycode_map_entry newcode;
							if (curshift == 0)
							{
								newcode.field[0] = field;
								newcode.field[1] = 0;
							}
							else
							{
								newcode.field[0] = shift[curshift - 1];
								newcode.field[1] = field;
							}
							newcode.ch = code;
							m_keycode_map.push_back(newcode);

							if (LOG_NATURAL_KEYBOARD)
							{
								std::string tempstr;
								machine().logerror("natural_keyboard: code=%i (%s) port=%p field->name='%s'\n", int(code), unicode_to_string(tempstr, code), (void *)port, field->name());
							}
						}
					}
}


//-------------------------------------------------
//  can_post_directly - determine if the given
//  unicode character can be directly posted
//-------------------------------------------------

bool natural_keyboard::can_post_directly(unicode_char ch)
{
	// if we have a queueing callback, then it depends on whether we can accept the character
	if (!m_queue_chars.isnull())
		return m_accept_char.isnull() ? true : m_accept_char(ch);

	// otherwise, it depends on the input codes
	const keycode_map_entry *code = find_code(ch);
	return (code != NULL && code->field[0] != NULL);
}


//-------------------------------------------------
//  can_post_alternate - determine if the given
//  unicode character can be posted via translation
//-------------------------------------------------

bool natural_keyboard::can_post_alternate(unicode_char ch)
{
	const char_info *info = char_info::find(ch);
	if (info == NULL)
		return false;

	const char *altstring = info->alternate;
	if (altstring == NULL)
		return false;

	while (*altstring != 0)
	{
		unicode_char uchar;
		int count = uchar_from_utf8(&uchar, altstring, strlen(altstring));
		if (count <= 0)
			return false;
		if (!can_post_directly(uchar))
			return false;
		altstring += count;
	}
	return true;
}


//-------------------------------------------------
//  choose_delay - determine the delay between
//  posting keyboard events
//-------------------------------------------------

attotime natural_keyboard::choose_delay(unicode_char ch)
{
	// if we have a live rate, just use that
	if (m_current_rate != attotime::zero)
		return m_current_rate;

	// systems with queue_chars can afford a much smaller delay
	if (!m_queue_chars.isnull())
		return attotime::from_msec(10);

	// otherwise, default to constant delay with a longer delay on CR
	return attotime::from_msec((ch == '\r') ? 200 : 50);
}


//-------------------------------------------------
//  internal_post - post a keyboard event
//-------------------------------------------------

void natural_keyboard::internal_post(unicode_char ch)
{
	// need to start up the timer?
	if (empty())
	{
		m_timer->adjust(choose_delay(ch));
		m_status_keydown = 0;
	}

	// add to the buffer, resizing if necessary
	m_buffer[m_bufend++] = ch;
	if ((m_bufend + 1) % m_buffer.size() == m_bufbegin)
		m_buffer.resize(m_buffer.size() + KEY_BUFFER_SIZE);
	m_bufend %= m_buffer.size();
}


//-------------------------------------------------
//  timer - timer callback to keep things flowing
//  when posting a string of characters
//-------------------------------------------------

void natural_keyboard::timer(void *ptr, int param)
{
	// the driver has a queue_chars handler
	if (!m_queue_chars.isnull())
	{
		while (!empty() && m_queue_chars(&m_buffer[m_bufbegin], 1))
		{
			m_bufbegin = (m_bufbegin + 1) % m_buffer.size();
			if (m_current_rate != attotime::zero)
				break;
		}
	}

	// the driver does not have a queue_chars handler
	else
	{
		if (m_status_keydown)
			m_bufbegin = (m_bufbegin + 1) % m_buffer.size();
		m_status_keydown = !m_status_keydown;
	}

	// need to make sure timerproc is called again if buffer not empty
	if (!empty())
		m_timer->adjust(choose_delay(m_buffer[m_bufbegin]));
}


//-------------------------------------------------
//  unicode_to_string - obtain a string
//  representation of a given code; used for
//  logging and debugging
//-------------------------------------------------

const char *natural_keyboard::unicode_to_string(std::string &buffer, unicode_char ch)
{
	buffer.clear();
	switch (ch)
	{
		// check some magic values
		case '\0':  buffer.assign("\\0");      break;
		case '\r':  buffer.assign("\\r");      break;
		case '\n':  buffer.assign("\\n");      break;
		case '\t':  buffer.assign("\\t");      break;

		default:
			// seven bit ASCII is easy
			if (ch >= 32 && ch < 128)
			{
				char temp[2] = { char(ch), 0 };
				buffer.assign(temp);
			}
			else if (ch >= UCHAR_MAMEKEY_BEGIN)
			{
				// try to obtain a codename with code_name(); this can result in an empty string
				input_code code(DEVICE_CLASS_KEYBOARD, 0, ITEM_CLASS_SWITCH, ITEM_MODIFIER_NONE, input_item_id(ch - UCHAR_MAMEKEY_BEGIN));
				machine().input().code_name(buffer, code);
			}

			// did we fail to resolve? if so, we have a last resort
			if (buffer.length() == 0)
				strprintf(buffer,"U+%04X", unsigned(ch));
			break;
	}
	return buffer.c_str();
}


//-------------------------------------------------
//  find_code - find a code in our lookup table
//-------------------------------------------------

const natural_keyboard::keycode_map_entry *natural_keyboard::find_code(unicode_char ch) const
{
	for (unsigned int index = 0; index < m_keycode_map.size(); index++)
	{
		if (m_keycode_map[index].ch == ch)
			return &m_keycode_map[index];
	}
	return NULL;
}


//-------------------------------------------------
//  frame_update - once per frame update of the
//  natural keyboard state
//-------------------------------------------------

void natural_keyboard::frame_update(ioport_port &port, ioport_value &digital)
{
	// is there currently a key down?
	if (m_status_keydown && !empty())
	{
		// loop through this character's component codes
		const keycode_map_entry *code = find_code(m_buffer[m_bufbegin]);
		if (code != NULL)
			for (int fieldnum = 0; fieldnum < ARRAY_LENGTH(code->field) && code->field[fieldnum] != NULL; fieldnum++)
				if (&code->field[fieldnum]->port() == &port)
					digital |= code->field[fieldnum]->mask();
	}
}


//-------------------------------------------------
//  key_name - returns the name of a specific key
//-------------------------------------------------

const char *natural_keyboard::key_name(std::string &str, unicode_char ch)
{
	// attempt to get the string from the character info table
	const char_info *ci = char_info::find(ch);
	const char *result = (ci != NULL) ? ci->name : NULL;
	if (result != NULL)
		str.assign(result);

	// if that doesn't work, convert to UTF-8
	else if (ch > 0x7F || isprint(ch))
	{
		char buf[10];
		int count = utf8_from_uchar(buf, ARRAY_LENGTH(buf), ch);
		buf[count] = 0;
		str.assign(buf);
	}

	// otherwise, opt for question marks
	else
		str.assign("???");
	return str.c_str();
}


//-------------------------------------------------
//  dump - dumps info to string
//-------------------------------------------------

std::string natural_keyboard::dump()
{
	std::string buffer, tempstr;
	const size_t left_column_width = 24;

	// loop through all codes
	for (unsigned int index = 0; index < m_keycode_map.size(); index++)
	{
		// describe the character code
		const natural_keyboard::keycode_map_entry &code = m_keycode_map[index];
		strcatprintf(buffer,"%08X (%s) ", code.ch, unicode_to_string(tempstr, code.ch));

		// pad with spaces
		while (buffer.length() < left_column_width)
			buffer.push_back(' ');

		// identify the keys used
		for (int field = 0; field < ARRAY_LENGTH(code.field) && code.field[field] != 0; field++)
			strcatprintf(buffer, "%s'%s'", (field > 0) ? ", " : "", code.field[field]->name());

		// carriage return
		buffer.push_back('\n');
	}

	return buffer;
}


//**************************************************************************
=======
>>>>>>> upstream/master
//  I/O PORT CONDITION
//**************************************************************************

//-------------------------------------------------
//  eval - evaluate condition
//-------------------------------------------------

bool ioport_condition::eval() const
{
	// always condition is always true
	if (m_condition == ALWAYS)
		return true;

	// otherwise, read the referenced port and switch off the condition type
	ioport_value condvalue = m_port->read();
	switch (m_condition)
	{
		case ALWAYS:            return true;
		case EQUALS:            return ((condvalue & m_mask) == m_value);
		case NOTEQUALS:         return ((condvalue & m_mask) != m_value);
		case GREATERTHAN:       return ((condvalue & m_mask) > m_value);
		case NOTGREATERTHAN:    return ((condvalue & m_mask) <= m_value);
		case LESSTHAN:          return ((condvalue & m_mask) < m_value);
		case NOTLESSTHAN:       return ((condvalue & m_mask) >= m_value);
	}
	return true;
}


//-------------------------------------------------
//  initialize - create the live state
//-------------------------------------------------

void ioport_condition::initialize(device_t &device)
{
<<<<<<< HEAD
	if (m_tag != NULL)
=======
	if (m_tag != nullptr)
>>>>>>> upstream/master
		m_port = device.ioport(m_tag);
}



//**************************************************************************
//  I/O PORT SETTING
//**************************************************************************

//-------------------------------------------------
//  ioport_setting - constructor
//-------------------------------------------------

ioport_setting::ioport_setting(ioport_field &field, ioport_value _value, const char *_name)
<<<<<<< HEAD
	: m_next(NULL),
=======
	: m_next(nullptr),
>>>>>>> upstream/master
		m_field(field),
		m_value(_value),
		m_name(_name)
{
}



//**************************************************************************
//  I/O PORT DIP LOCATION
//**************************************************************************

//-------------------------------------------------
//  ioport_diplocation - constructor
//-------------------------------------------------

<<<<<<< HEAD
ioport_diplocation::ioport_diplocation(const char *name, UINT8 swnum, bool invert)
	: m_next(NULL),
=======
ioport_diplocation::ioport_diplocation(const char *name, u8 swnum, bool invert)
	: m_next(nullptr),
>>>>>>> upstream/master
		m_name(name),
		m_number(swnum),
		m_invert(invert)
{
}



//**************************************************************************
//  I/O PORT FIELD
//**************************************************************************

//-------------------------------------------------
//  ioport_field - constructor
//-------------------------------------------------

ioport_field::ioport_field(ioport_port &port, ioport_type type, ioport_value defvalue, ioport_value maskbits, const char *name)
<<<<<<< HEAD
	: m_next(NULL),
=======
	: m_next(nullptr),
>>>>>>> upstream/master
		m_port(port),
		m_modcount(port.modcount()),
		m_mask(maskbits),
		m_defvalue(defvalue & maskbits),
		m_type(type),
		m_player(0),
		m_flags(0),
		m_impulse(0),
		m_name(name),
<<<<<<< HEAD
		m_read_param(NULL),
		m_write_param(NULL),
=======
		m_read_param(nullptr),
		m_write_param(nullptr),
>>>>>>> upstream/master
		m_digital_value(false),
		m_min(0),
		m_max(maskbits),
		m_sensitivity(0),
		m_delta(0),
		m_centerdelta(0),
		m_crosshair_axis(CROSSHAIR_AXIS_NONE),
		m_crosshair_scale(1.0),
		m_crosshair_offset(0),
		m_crosshair_altaxis(0),
		m_full_turn_count(0),
<<<<<<< HEAD
		m_remap_table(NULL),
=======
		m_remap_table(nullptr),
>>>>>>> upstream/master
		m_way(0)
{
	// reset sequences and chars
	for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
		m_seq[seqtype].set_default();
<<<<<<< HEAD
	m_chars[0] = m_chars[1] = m_chars[2] = m_chars[3] = unicode_char(0);
=======
	m_chars[0] = m_chars[1] = m_chars[2] = m_chars[3] = char32_t(0);
>>>>>>> upstream/master

	// for DIP switches and configs, look for a default value from the owner
	if (type == IPT_DIPSWITCH || type == IPT_CONFIG)
	{
		const input_device_default *def = device().input_ports_defaults();
<<<<<<< HEAD
		if (def != NULL)
		{
			const char *fulltag = port.tag();
			for ( ; def->tag != NULL; def++)
				if (device().subtag(def->tag) == fulltag && def->mask == m_mask)
					m_defvalue = def->defvalue & m_mask;
		}
=======
		if (def != nullptr)
		{
			const char *fulltag = port.tag();
			for ( ; def->tag != nullptr; def++)
				if (device().subtag(def->tag) == fulltag && def->mask == m_mask)
					m_defvalue = def->defvalue & m_mask;
		}

		m_flags |= FIELD_FLAG_TOGGLE;
>>>>>>> upstream/master
	}
}

void ioport_field::set_value(ioport_value value)
{
	m_digital_value = value != 0;
}


//-------------------------------------------------
//  ~ioport_field - destructor
//-------------------------------------------------

ioport_field::~ioport_field()
{
}


//-------------------------------------------------
//  name - return the field name for a given input
<<<<<<< HEAD
//  field
=======
//  field (this must never return nullptr)
>>>>>>> upstream/master
//-------------------------------------------------

const char *ioport_field::name() const
{
	// if we have a non-default name, use that
<<<<<<< HEAD
	if (m_live != NULL && !m_live->name.empty())
		return m_live->name.c_str();
	if (m_name != NULL)
=======
	if (m_live != nullptr && !m_live->name.empty())
		return m_live->name.c_str();
	if (m_name != nullptr)
>>>>>>> upstream/master
		return m_name;

	// otherwise, return the name associated with the type
	return manager().type_name(m_type, m_player);
}


//-------------------------------------------------
//  seq - return the live input sequence for the
//  given input field
//-------------------------------------------------

const input_seq &ioport_field::seq(input_seq_type seqtype) const
{
	// if no live state, return default
<<<<<<< HEAD
	if (m_live == NULL)
		return defseq(seqtype);

	// if the field is disabled, return no key
	if (unused())
		return input_seq::empty_seq;

=======
	if (m_live == nullptr)
		return defseq(seqtype);

>>>>>>> upstream/master
	// if the sequence is the special default code, return the expanded default value
	if (m_live->seq[seqtype].is_default())
		return manager().type_seq(m_type, m_player, seqtype);

	// otherwise, return the sequence as-is
	return m_live->seq[seqtype];
}


//-------------------------------------------------
//  defseq - return the default input sequence for
//  the given input field
//-------------------------------------------------

const input_seq &ioport_field::defseq(input_seq_type seqtype) const
{
<<<<<<< HEAD
	// if the field is disabled, return no key
	if (unused())
		return input_seq::empty_seq;

=======
>>>>>>> upstream/master
	// if the sequence is the special default code, return the expanded default value
	if (m_seq[seqtype].is_default())
		return manager().type_seq(m_type, m_player, seqtype);

	// otherwise, return the sequence as-is
	return m_seq[seqtype];
}


//-------------------------------------------------
<<<<<<< HEAD
=======
//  set_defseq - dynamically alter the default
//  input sequence for the given input field
//-------------------------------------------------

void ioport_field::set_defseq(input_seq_type seqtype, const input_seq &newseq)
{
	const bool was_changed = seq(seqtype) != defseq(seqtype);

	// set the new sequence
	m_seq[seqtype] = newseq;

	// also update live state unless previously customized
	if (m_live != nullptr && !was_changed)
		m_live->seq[seqtype] = newseq;
}


//-------------------------------------------------
>>>>>>> upstream/master
//  type_class - return the type class for this
//  field
//-------------------------------------------------

ioport_type_class ioport_field::type_class() const
{
<<<<<<< HEAD
	ioport_type_class result;

	switch (m_type)
	{
		case IPT_JOYSTICK_UP:
		case IPT_JOYSTICK_DOWN:
		case IPT_JOYSTICK_LEFT:
		case IPT_JOYSTICK_RIGHT:
		case IPT_JOYSTICKLEFT_UP:
		case IPT_JOYSTICKLEFT_DOWN:
		case IPT_JOYSTICKLEFT_LEFT:
		case IPT_JOYSTICKLEFT_RIGHT:
		case IPT_JOYSTICKRIGHT_UP:
		case IPT_JOYSTICKRIGHT_DOWN:
		case IPT_JOYSTICKRIGHT_LEFT:
		case IPT_JOYSTICKRIGHT_RIGHT:
		case IPT_BUTTON1:
		case IPT_BUTTON2:
		case IPT_BUTTON3:
		case IPT_BUTTON4:
		case IPT_BUTTON5:
		case IPT_BUTTON6:
		case IPT_BUTTON7:
		case IPT_BUTTON8:
		case IPT_BUTTON9:
		case IPT_BUTTON10:
		case IPT_AD_STICK_X:
		case IPT_AD_STICK_Y:
		case IPT_AD_STICK_Z:
		case IPT_TRACKBALL_X:
		case IPT_TRACKBALL_Y:
		case IPT_LIGHTGUN_X:
		case IPT_LIGHTGUN_Y:
		case IPT_MOUSE_X:
		case IPT_MOUSE_Y:
		case IPT_START:
		case IPT_SELECT:
			result = INPUT_CLASS_CONTROLLER;
			break;

		case IPT_KEYPAD:
		case IPT_KEYBOARD:
			result = INPUT_CLASS_KEYBOARD;
			break;

		case IPT_CONFIG:
			result = INPUT_CLASS_CONFIG;
			break;

		case IPT_DIPSWITCH:
			result = INPUT_CLASS_DIPSWITCH;
			break;

		case 0:
			if (m_name != NULL && m_name != (const char *)-1)
				result = INPUT_CLASS_MISC;
			else
				result = INPUT_CLASS_INTERNAL;
			break;

		default:
			result = INPUT_CLASS_INTERNAL;
			break;
	}
	return result;
=======
	// inputs associated with specific players
	ioport_group group = manager().type_group(m_type, m_player);
	if (group >= IPG_PLAYER1 && group <= IPG_PLAYER10)
		return INPUT_CLASS_CONTROLLER;

	// keys (names derived from character codes)
	if (m_type == IPT_KEYPAD || m_type == IPT_KEYBOARD)
		return INPUT_CLASS_KEYBOARD;

	// configuration settings (specific names required)
	if (m_type == IPT_CONFIG)
		return INPUT_CLASS_CONFIG;

	// DIP switches (specific names required)
	if (m_type == IPT_DIPSWITCH)
		return INPUT_CLASS_DIPSWITCH;

	// miscellaneous non-player inputs (named and user-mappable)
	if (group == IPG_OTHER || (group == IPG_INVALID && m_name != nullptr))
		return INPUT_CLASS_MISC;

	// internal inputs (these may be anonymous)
	return INPUT_CLASS_INTERNAL;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  keyboard_code - accesses a particular keyboard
//  code
//-------------------------------------------------

<<<<<<< HEAD
unicode_char ioport_field::keyboard_code(int which) const
{
	unicode_char ch;
=======
char32_t ioport_field::keyboard_code(int which) const
{
	char32_t ch;
>>>>>>> upstream/master

	if (which >= ARRAY_LENGTH(m_chars))
		throw emu_fatalerror("Tried to access keyboard_code with out-of-range index %d\n", which);

	ch = m_chars[which];

	// special hack to allow for PORT_CODE('\xA3')
	if (ch >= 0xffffff80 && ch <= 0xffffffff)
		ch &= 0xff;
	return ch;
}


//-------------------------------------------------
<<<<<<< HEAD
=======
//  key_name - returns the name of a specific key
//-------------------------------------------------

std::string ioport_field::key_name(int which) const
{
	char32_t ch = keyboard_code(which);

	// attempt to get the string from the character info table
	switch (ch)
	{
		case 8: return "Backspace";
		case 9: return "Tab";
		case 12: return "Clear";
		case 13: return "Enter";
		case 27: return "Esc";
		case 32: return "Space";
		case UCHAR_SHIFT_1: return "Shift";
		case UCHAR_SHIFT_2: return "Ctrl";
		case UCHAR_MAMEKEY(ESC): return "Esc";
		case UCHAR_MAMEKEY(INSERT): return "Insert";
		case UCHAR_MAMEKEY(DEL): return "Delete";
		case UCHAR_MAMEKEY(HOME): return "Home";
		case UCHAR_MAMEKEY(END): return "End";
		case UCHAR_MAMEKEY(PGUP): return "Page Up";
		case UCHAR_MAMEKEY(PGDN): return "Page Down";
		case UCHAR_MAMEKEY(LEFT): return "Cursor Left";
		case UCHAR_MAMEKEY(RIGHT): return "Cursor Right";
		case UCHAR_MAMEKEY(UP): return "Cursor Up";
		case UCHAR_MAMEKEY(DOWN): return "Cursor Down";
		case UCHAR_MAMEKEY(SLASH_PAD): return "Keypad /";
		case UCHAR_MAMEKEY(ASTERISK): return "Keypad *";
		case UCHAR_MAMEKEY(MINUS_PAD): return "Keypad -";
		case UCHAR_MAMEKEY(PLUS_PAD): return "Keypad +";
		case UCHAR_MAMEKEY(DEL_PAD): return "Keypad .";
		case UCHAR_MAMEKEY(ENTER_PAD): return "Keypad Enter";
		case UCHAR_MAMEKEY(BS_PAD): return "Keypad Backspace";
		case UCHAR_MAMEKEY(TAB_PAD): return "Keypad Tab";
		case UCHAR_MAMEKEY(00_PAD): return "Keypad 00";
		case UCHAR_MAMEKEY(000_PAD): return "Keypad 000";
		case UCHAR_MAMEKEY(PRTSCR): return "Print Screen";
		case UCHAR_MAMEKEY(PAUSE): return "Pause";
		case UCHAR_MAMEKEY(LSHIFT): return "Left Shift";
		case UCHAR_MAMEKEY(RSHIFT): return "Right Shift";
		case UCHAR_MAMEKEY(LCONTROL): return "Left Ctrl";
		case UCHAR_MAMEKEY(RCONTROL): return "Right Ctrl";
		case UCHAR_MAMEKEY(LALT): return "Left Alt";
		case UCHAR_MAMEKEY(RALT): return "Right Alt";
		case UCHAR_MAMEKEY(SCRLOCK): return "Scroll Lock";
		case UCHAR_MAMEKEY(NUMLOCK): return "Num Lock";
		case UCHAR_MAMEKEY(CAPSLOCK): return "Caps Lock";
		case UCHAR_MAMEKEY(LWIN): return "Left Win";
		case UCHAR_MAMEKEY(RWIN): return "Right Win";
		case UCHAR_MAMEKEY(MENU): return "Menu";
		case UCHAR_MAMEKEY(CANCEL): return "Break";
		default: break;
	}

	// handle function keys
	if (ch >= UCHAR_MAMEKEY(F1) && ch <= UCHAR_MAMEKEY(F20))
		return util::string_format("F%d", ch - UCHAR_MAMEKEY(F1) + 1);

	// handle 0-9 on numeric keypad
	if (ch >= UCHAR_MAMEKEY(0_PAD) && ch <= UCHAR_MAMEKEY(9_PAD))
		return util::string_format("Keypad %d", ch - UCHAR_MAMEKEY(0_PAD));

	// if that doesn't work, convert to UTF-8
	if (ch > 0x7F || isprint(ch))
	{
		char buf[10];
		int count = utf8_from_uchar(buf, ARRAY_LENGTH(buf), ch);
		buf[count] = 0;
		return std::string(buf);
	}

	// otherwise, opt for question marks
	return "???";
}


//-------------------------------------------------
>>>>>>> upstream/master
//  get_user_settings - return the current
//  settings for the given input field
//-------------------------------------------------

void ioport_field::get_user_settings(user_settings &settings)
{
	// zap the entire structure
	memset(&settings, 0, sizeof(settings));

	// copy the basics
	for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
		settings.seq[seqtype] = seq(seqtype);

	// if there's a list of settings or we're an adjuster, copy the current value
<<<<<<< HEAD
	if (first_setting() != NULL || m_type == IPT_ADJUSTER)
		settings.value = m_live->value;

	// if there's analog data, extract the analog settings
	if (m_live->analog != NULL)
=======
	if (!m_settinglist.empty() || m_type == IPT_ADJUSTER)
		settings.value = m_live->value;

	// if there's analog data, extract the analog settings
	if (m_live->analog != nullptr)
>>>>>>> upstream/master
	{
		settings.sensitivity = m_live->analog->sensitivity();
		settings.delta = m_live->analog->delta();
		settings.centerdelta = m_live->analog->centerdelta();
		settings.reverse = m_live->analog->reverse();
	}

	// non-analog settings
	else
	{
		settings.toggle = m_live->toggle;
<<<<<<< HEAD
#ifdef USE_AUTOFIRE
		settings.autofire = m_live->autofire;
#endif /* USE_AUTOFIRE */
=======
		settings.autofire = m_live->autofire;
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  set_user_settings - modify the current
//  settings for the given input field
//-------------------------------------------------

void ioport_field::set_user_settings(const user_settings &settings)
{
	// copy the basics
	for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
	{
		const input_seq &defseq = manager().type_seq(m_type, m_player, input_seq_type(seqtype));
		if (defseq == settings.seq[seqtype])
			m_live->seq[seqtype].set_default();
		else
			m_live->seq[seqtype] = settings.seq[seqtype];
	}

	// if there's a list of settings or we're an adjuster, copy the current value
<<<<<<< HEAD
	if (first_setting() != NULL || m_type == IPT_ADJUSTER)
		m_live->value = settings.value;

	// if there's analog data, extract the analog settings
	if (m_live->analog != NULL)
=======
	if (!m_settinglist.empty() || m_type == IPT_ADJUSTER)
		m_live->value = settings.value;

	// if there's analog data, extract the analog settings
	if (m_live->analog != nullptr)
>>>>>>> upstream/master
	{
		m_live->analog->m_sensitivity = settings.sensitivity;
		m_live->analog->m_delta = settings.delta;
		m_live->analog->m_centerdelta = settings.centerdelta;
		m_live->analog->m_reverse = settings.reverse;
	}

	// non-analog settings
	else
	{
		m_live->toggle = settings.toggle;
<<<<<<< HEAD
#ifdef USE_AUTOFIRE
		m_live->autofire = settings.autofire;
#endif /* USE_AUTOFIRE */
=======
		m_live->autofire = settings.autofire;
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  setting_name - return the expanded setting
//  name for a field
//-------------------------------------------------

const char *ioport_field::setting_name() const
{
	// only makes sense if we have settings
<<<<<<< HEAD
	assert(first_setting() != NULL);

	// scan the list of settings looking for a match on the current value
	for (ioport_setting *setting = first_setting(); setting != NULL; setting = setting->next())
		if (setting->enabled())
			if (setting->value() == m_live->value)
				return setting->name();
=======
	assert(!m_settinglist.empty());

	// scan the list of settings looking for a match on the current value
	for (ioport_setting &setting : m_settinglist)
		if (setting.enabled())
			if (setting.value() == m_live->value)
				return setting.name();
>>>>>>> upstream/master

	return "INVALID";
}


//-------------------------------------------------
//  has_previous_setting - return true if the
//  given field has a "previous" setting
//-------------------------------------------------

bool ioport_field::has_previous_setting() const
{
	// only makes sense if we have settings
<<<<<<< HEAD
	assert(first_setting() != NULL);

	// scan the list of settings looking for a match on the current value
	for (ioport_setting *setting = first_setting(); setting != NULL; setting = setting->next())
		if (setting->enabled())
			return (setting->value() != m_live->value);
=======
	assert(!m_settinglist.empty());

	// scan the list of settings looking for a match on the current value
	for (ioport_setting &setting : m_settinglist)
		if (setting.enabled())
			return (setting.value() != m_live->value);
>>>>>>> upstream/master

	return false;
}


//-------------------------------------------------
//  select_previous_setting - select the previous
//  item for a DIP switch or configuration field
//-------------------------------------------------

void ioport_field::select_previous_setting()
{
	// only makes sense if we have settings
<<<<<<< HEAD
	assert(first_setting() != NULL);

	// scan the list of settings looking for a match on the current value
	ioport_setting *prevsetting = NULL;
	bool found_match = false;
	for (ioport_setting *setting = first_setting(); setting != NULL; setting = setting->next())
		if (setting->enabled())
		{
			if (setting->value() == m_live->value)
			{
				found_match = true;
				if (prevsetting != NULL)
					break;
			}
			prevsetting = setting;
=======
	assert(!m_settinglist.empty());

	// scan the list of settings looking for a match on the current value
	ioport_setting *prevsetting = nullptr;
	bool found_match = false;
	for (ioport_setting &setting : m_settinglist)
		if (setting.enabled())
		{
			if (setting.value() == m_live->value)
			{
				found_match = true;
				if (prevsetting != nullptr)
					break;
			}
			prevsetting = &setting;
>>>>>>> upstream/master
		}

	// if we didn't find a matching value, select the first
	if (!found_match)
	{
<<<<<<< HEAD
		for (prevsetting = first_setting(); prevsetting != NULL; prevsetting = prevsetting->next())
=======
		for (prevsetting = m_settinglist.first(); prevsetting != nullptr; prevsetting = prevsetting->next())
>>>>>>> upstream/master
			if (prevsetting->enabled())
				break;
	}

	// update the value to the previous one
<<<<<<< HEAD
	if (prevsetting != NULL)
=======
	if (prevsetting != nullptr)
>>>>>>> upstream/master
		m_live->value = prevsetting->value();
}


//-------------------------------------------------
//  has_next_setting - return true if the given
//  field has a "next" setting
//-------------------------------------------------

bool ioport_field::has_next_setting() const
{
	// only makes sense if we have settings
<<<<<<< HEAD
	assert(first_setting() != NULL);

	// scan the list of settings looking for a match on the current value
	bool found = false;
	for (ioport_setting *setting = first_setting(); setting != NULL; setting = setting->next())
		if (setting->enabled())
		{
			if (found)
				return true;
			if (setting->value() == m_live->value)
=======
	assert(!m_settinglist.empty());

	// scan the list of settings looking for a match on the current value
	bool found = false;
	for (ioport_setting &setting : m_settinglist)
		if (setting.enabled())
		{
			if (found)
				return true;
			if (setting.value() == m_live->value)
>>>>>>> upstream/master
				found = true;
		}

	return false;
}


//-------------------------------------------------
//  select_next_setting - select the next item for
//  a DIP switch or configuration field
//-------------------------------------------------

void ioport_field::select_next_setting()
{
	// only makes sense if we have settings
<<<<<<< HEAD
	assert(first_setting() != NULL);

	// scan the list of settings looking for a match on the current value
	ioport_setting *nextsetting = NULL;
	ioport_setting *setting;
	for (setting = first_setting(); setting != NULL; setting = setting->next())
=======
	assert(!m_settinglist.empty());

	// scan the list of settings looking for a match on the current value
	ioport_setting *nextsetting = nullptr;
	ioport_setting *setting;
	for (setting = m_settinglist.first(); setting != nullptr; setting = setting->next())
>>>>>>> upstream/master
		if (setting->enabled())
			if (setting->value() == m_live->value)
				break;

	// if we found one, scan forward for the next valid one
<<<<<<< HEAD
	if (setting != NULL)
		for (nextsetting = setting->next(); nextsetting != NULL; nextsetting = nextsetting->next())
=======
	if (setting != nullptr)
		for (nextsetting = setting->next(); nextsetting != nullptr; nextsetting = nextsetting->next())
>>>>>>> upstream/master
			if (nextsetting->enabled())
				break;

	// if we hit the end, search from the beginning
<<<<<<< HEAD
	if (nextsetting == NULL)
		for (nextsetting = first_setting(); nextsetting != NULL; nextsetting = nextsetting->next())
=======
	if (nextsetting == nullptr)
		for (nextsetting = m_settinglist.first(); nextsetting != nullptr; nextsetting = nextsetting->next())
>>>>>>> upstream/master
			if (nextsetting->enabled())
				break;

	// update the value to the previous one
<<<<<<< HEAD
	if (nextsetting != NULL)
=======
	if (nextsetting != nullptr)
>>>>>>> upstream/master
		m_live->value = nextsetting->value();
}


//-------------------------------------------------
//  frame_update_digital - get the state of a
//  digital field
//-------------------------------------------------

<<<<<<< HEAD
void ioport_field::frame_update(ioport_value &result, bool mouse_down)
=======
void ioport_field::frame_update(ioport_value &result)
>>>>>>> upstream/master
{
	// skip if not enabled
	if (!enabled())
		return;

	// handle analog inputs first
<<<<<<< HEAD
	if (m_live->analog != NULL)
=======
	if (m_live->analog != nullptr)
>>>>>>> upstream/master
	{
		m_live->analog->frame_update(machine());
		return;
	}

	// if UI is active, ignore digital inputs
	if (machine().ui().is_menu_active())
		return;

<<<<<<< HEAD
	// if the state changed, look for switch down/switch up
#ifdef USE_AUTOFIRE
	bool curstate = machine().ioport().auto_pressed(this);
#else /* USE_AUTOFIRE */
	bool curstate = mouse_down || machine().input().seq_pressed(seq()) || m_digital_value;
#endif /* USE_AUTOFIRE */
=======
	// if user input is locked out here, bail
	if (m_live->lockout)
	{
		// use just the digital value
		if (m_digital_value)
			result |= m_mask;
		return;
	}

	// if the state changed, look for switch down/switch up
	bool curstate = m_digital_value || machine().input().seq_pressed(seq());
	if (m_live->autofire && !machine().ioport().get_autofire_toggle())
	{
		if (curstate)
		{
			if (m_live->autopressed > machine().ioport().get_autofire_delay())
				m_live->autopressed = 0;
			else if (m_live->autopressed > machine().ioport().get_autofire_delay() / 2)
				curstate = false;
			m_live->autopressed++;
		}
		else
			m_live->autopressed = 0;
	}
>>>>>>> upstream/master
	bool changed = false;
	if (curstate != m_live->last)
	{
		m_live->last = curstate;
		changed = true;
	}

<<<<<<< HEAD
	// if we're a keyboard type and using natural keyboard, bail
	if (m_type == IPT_KEYBOARD && machine().ui().use_natural_keyboard())
		return;

=======
>>>>>>> upstream/master
	// coin impulse option
	int effective_impulse = m_impulse;
	int impulse_option_val = machine().options().coin_impulse();
	if (impulse_option_val != 0)
	{
		if (impulse_option_val < 0)
			effective_impulse = 0;
		else if ((m_type >= IPT_COIN1 && m_type <= IPT_COIN12) || m_impulse != 0)
			effective_impulse = impulse_option_val;
	}

	// if this is a switch-down event, handle impulse and toggle
	if (changed && curstate)
	{
		// impulse controls: reset the impulse counter
		if (effective_impulse != 0 && m_live->impulse == 0)
			m_live->impulse = effective_impulse;

		// toggle controls: flip the toggle state or advance to the next setting
		if (m_live->toggle)
		{
			if (m_settinglist.count() == 0)
<<<<<<< HEAD
			{
				m_live->value ^= m_mask;
#ifdef USE_AUTOFIRE
				m_live->autofire_toggle = !m_live->autofire_toggle;
#endif /* USE_AUTOFIRE */
			}
=======
				m_live->value ^= m_mask;
>>>>>>> upstream/master
			else
				select_next_setting();
		}
	}

	// update the current state with the impulse state
	if (effective_impulse != 0)
	{
		curstate = (m_live->impulse != 0);
		if (curstate)
			m_live->impulse--;
	}

	// for toggle switches, the current value is folded into the port's default value
<<<<<<< HEAD
	// so we always return FALSE here
=======
	// so we always return false here
>>>>>>> upstream/master
	if (m_live->toggle)
		curstate = false;

	// additional logic to restrict digital joysticks
<<<<<<< HEAD
	if (curstate && !m_digital_value && !mouse_down && m_live->joystick != NULL && m_way != 16 && !machine().options().joystick_contradictory())
	{
		UINT8 mask = (m_way == 4) ? m_live->joystick->current4way() : m_live->joystick->current();
=======
	if (curstate && !m_digital_value && m_live->joystick != nullptr && m_way != 16 && !machine().options().joystick_contradictory())
	{
		u8 mask = (m_way == 4) ? m_live->joystick->current4way() : m_live->joystick->current();
>>>>>>> upstream/master
		if (!(mask & (1 << m_live->joydir)))
			curstate = false;
	}

	// skip locked-out coin inputs
<<<<<<< HEAD
	if (curstate && m_type >= IPT_COIN1 && m_type <= IPT_COIN12 && coin_lockout_get_state(machine(), m_type - IPT_COIN1))
=======
	if (curstate && m_type >= IPT_COIN1 && m_type <= IPT_COIN12 && machine().bookkeeping().coin_lockout_get_state(m_type - IPT_COIN1))
>>>>>>> upstream/master
	{
		bool verbose = machine().options().verbose();
#ifdef MAME_DEBUG
		verbose = true;
#endif
		if (machine().options().coin_lockout())
		{
			if (verbose)
				machine().ui().popup_time(3, "Coinlock disabled %s.", name());
			curstate = false;
		}
		else
			if (verbose)
				machine().ui().popup_time(3, "Coinlock disabled, but broken through %s.", name());
	}

	// if we're active, set the appropriate bits in the digital state
	if (curstate)
		result |= m_mask;
}


//-------------------------------------------------
//  crosshair_position - compute the crosshair
//  position
//-------------------------------------------------

void ioport_field::crosshair_position(float &x, float &y, bool &gotx, bool &goty)
{
	double value = m_live->analog->crosshair_read();

	// apply the scale and offset
	if (m_crosshair_scale < 0)
		value = -(1.0 - value) * m_crosshair_scale;
	else
		value *= m_crosshair_scale;
	value += m_crosshair_offset;

	// apply custom mapping if necessary
	if (!m_crosshair_mapper.isnull())
		value = m_crosshair_mapper(*this, value);

	// handle X axis
	if (m_crosshair_axis == CROSSHAIR_AXIS_X)
	{
		x = value;
		gotx = true;
		if (m_crosshair_altaxis != 0)
		{
			y = m_crosshair_altaxis;
			goty = true;
		}
	}

	// handle Y axis
	else
	{
		y = value;
		goty = true;
		if (m_crosshair_altaxis != 0)
		{
			x = m_crosshair_altaxis;
			gotx = true;
		}
	}
}


//-------------------------------------------------
//  expand_diplocation - expand a string-based
//  DIP location into a linked list of
//  descriptions
//-------------------------------------------------

void ioport_field::expand_diplocation(const char *location, std::string &errorbuf)
{
	// if nothing present, bail
<<<<<<< HEAD
	if (location == NULL)
=======
	if (location == nullptr)
>>>>>>> upstream/master
		return;

	m_diploclist.reset();

	// parse the string
	std::string name; // Don't move this variable inside the loop, lastname's lifetime depends on it being outside
<<<<<<< HEAD
	const char *lastname = NULL;
=======
	const char *lastname = nullptr;
>>>>>>> upstream/master
	const char *curentry = location;
	int entries = 0;
	while (*curentry != 0)
	{
		// find the end of this entry
		const char *comma = strchr(curentry, ',');
<<<<<<< HEAD
		if (comma == NULL)
=======
		if (comma == nullptr)
>>>>>>> upstream/master
			comma = curentry + strlen(curentry);

		// extract it to tempbuf
		std::string tempstr;
		tempstr.assign(curentry, comma - curentry);

		// first extract the switch name if present
		const char *number = tempstr.c_str();
		const char *colon = strchr(tempstr.c_str(), ':');

		// allocate and copy the name if it is present
<<<<<<< HEAD
		if (colon != NULL)
=======
		if (colon != nullptr)
>>>>>>> upstream/master
		{
			lastname = name.assign(number, colon - number).c_str();
			number = colon + 1;
		}

		// otherwise, just copy the last name
		else
		{
<<<<<<< HEAD
			if (lastname == NULL)
			{
				strcatprintf(errorbuf, "Switch location '%s' missing switch name!\n", location);
=======
			if (lastname == nullptr)
			{
				errorbuf.append(string_format("Switch location '%s' missing switch name!\n", location));
>>>>>>> upstream/master
				lastname = (char *)"UNK";
			}
			name.assign(lastname);
		}

		// if the number is preceded by a '!' it's active high
		bool invert = false;
		if (*number == '!')
		{
			invert = true;
			number++;
		}

		// now scan the switch number
		int swnum = -1;
		if (sscanf(number, "%d", &swnum) != 1)
<<<<<<< HEAD
			strcatprintf(errorbuf, "Switch location '%s' has invalid format!\n", location);
=======
			errorbuf.append(string_format("Switch location '%s' has invalid format!\n", location));
>>>>>>> upstream/master

		// allocate a new entry
		m_diploclist.append(*global_alloc(ioport_diplocation(name.c_str(), swnum, invert)));
		entries++;

		// advance to the next item
		curentry = comma;
		if (*curentry != 0)
			curentry++;
	}

	// then verify the number of bits in the mask matches
	ioport_value temp;
	int bits;
	for (bits = 0, temp = m_mask; temp != 0 && bits < 32; bits++)
		temp &= temp - 1;
	if (bits != entries)
<<<<<<< HEAD
		strcatprintf(errorbuf, "Switch location '%s' does not describe enough bits for mask %X\n", location, m_mask);
=======
		errorbuf.append(string_format("Switch location '%s' does not describe enough bits for mask %X\n", location, m_mask));
>>>>>>> upstream/master
}


//-------------------------------------------------
//  init_live_state - create live state structures
//-------------------------------------------------

void ioport_field::init_live_state(analog_field *analog)
{
	// resolve callbacks
	m_read.bind_relative_to(device());
	m_write.bind_relative_to(device());
	m_crosshair_mapper.bind_relative_to(device());

	// allocate live state
<<<<<<< HEAD
	m_live.reset(global_alloc(ioport_field_live(*this, analog)));

	m_condition.initialize(device());

	for (ioport_setting *setting = first_setting(); setting != NULL; setting = setting->next())
		setting->condition().initialize(setting->device());
=======
	m_live = std::make_unique<ioport_field_live>(*this, analog);

	m_condition.initialize(device());

	for (ioport_setting &setting : m_settinglist)
		setting.condition().initialize(setting.device());
>>>>>>> upstream/master
}



//**************************************************************************
//  I/O PORT FIELD LIVE
//**************************************************************************

//-------------------------------------------------
//  ioport_field_live - constructor
//-------------------------------------------------

ioport_field_live::ioport_field_live(ioport_field &field, analog_field *analog)
	: analog(analog),
<<<<<<< HEAD
		joystick(NULL),
=======
		joystick(nullptr),
>>>>>>> upstream/master
		value(field.defvalue()),
		impulse(0),
		last(0),
		toggle(field.toggle()),
<<<<<<< HEAD
		joydir(digital_joystick::JOYDIR_COUNT)
#ifdef USE_AUTOFIRE
		,autofire_toggle(0)
		,autofire(0)
		,autopressed(0)
#endif /* USE_AUTOFIRE */
=======
		joydir(digital_joystick::JOYDIR_COUNT),
		autofire(false),
		autopressed(0),
		lockout(false)
>>>>>>> upstream/master
{
	// fill in the basic values
	for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
		seq[seqtype] = field.defseq_unresolved(seqtype);

	// if this is a digital joystick field, make a note of it
	if (field.is_digital_joystick())
	{
		joystick = &field.manager().digjoystick(field.player(), (field.type() - (IPT_DIGITAL_JOYSTICK_FIRST + 1)) / 4);
		joydir = joystick->add_axis(field);
	}

	// Name keyboard key names
<<<<<<< HEAD
	if (field.type_class() == INPUT_CLASS_KEYBOARD && field.specific_name() == NULL)
	{
		// loop through each character on the field
		std::string tempstr;
		for (int which = 0; ; which++)
		{
			unicode_char ch = field.keyboard_code(which);
			if (ch == 0)
				break;
			strcatprintf(name, "%-*s ", MAX(SPACE_COUNT - 1, 0), field.manager().natkeyboard().key_name(tempstr, ch));
=======
	if (field.type_class() == INPUT_CLASS_KEYBOARD && field.specific_name() == nullptr)
	{
		// loop through each character on the field
		for (int which = 0; which < 4; which++)
		{
			char32_t const ch = field.keyboard_code(which);
			if (ch == 0)
				break;
			name.append(string_format("%-*s ", std::max(SPACE_COUNT - 1, 0), field.key_name(which)));
>>>>>>> upstream/master
		}

		// trim extra spaces
		strtrimspace(name);

		// special case
<<<<<<< HEAD
		if (name.length() == 0)
=======
		if (name.empty())
>>>>>>> upstream/master
			name.assign("Unnamed Key");
	}
}



//**************************************************************************
//  I/O PORT
//**************************************************************************

//-------------------------------------------------
//  ioport_port - constructor
//-------------------------------------------------

ioport_port::ioport_port(device_t &owner, const char *tag)
<<<<<<< HEAD
	: m_next(NULL),
=======
	: m_next(nullptr),
>>>>>>> upstream/master
		m_device(owner),
		m_tag(tag),
		m_modcount(0),
		m_active(0)
{
}


//-------------------------------------------------
//  ~ioport_port - destructor
//-------------------------------------------------

ioport_port::~ioport_port()
{
}


//-------------------------------------------------
//  machine - return a reference to the running
//  machine
//-------------------------------------------------

running_machine &ioport_port::machine() const
{
	return m_device.machine();
}


//-------------------------------------------------
//  manager - return a reference to the
//  ioport_manager on the running machine
//-------------------------------------------------

ioport_manager &ioport_port::manager() const
{
	return machine().ioport();
}


//-------------------------------------------------
//  field - return a pointer to the first field
//  that intersects the given mask
//-------------------------------------------------

<<<<<<< HEAD
ioport_field *ioport_port::field(ioport_value mask)
{
	// if we got the port, look for the field
	for (ioport_field *field = first_field(); field != NULL; field = field->next())
		if ((field->mask() & mask) != 0)
			return field;
	return NULL;
=======
ioport_field *ioport_port::field(ioport_value mask) const
{
	// if we got the port, look for the field
	for (ioport_field &field : fields())
		if ((field.mask() & mask) != 0)
			return &field;
	return nullptr;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  read - return the value of an I/O port
//-------------------------------------------------

ioport_value ioport_port::read()
{
	assert_always(manager().safe_to_read(), "Input ports cannot be read at init time!");

	// start with the digital state
	ioport_value result = m_live->digital;

	// insert dynamic read values
<<<<<<< HEAD
	for (dynamic_field *dynfield = m_live->readlist.first(); dynfield != NULL; dynfield = dynfield->next())
		dynfield->read(result);
=======
	for (dynamic_field &dynfield : m_live->readlist)
		dynfield.read(result);
>>>>>>> upstream/master

	// apply active high/low state to digital and dynamic read inputs
	result ^= m_live->defvalue;

	// insert analog portions
<<<<<<< HEAD
	for (analog_field *analog = m_live->analoglist.first(); analog != NULL; analog = analog->next())
		analog->read(result);
=======
	for (analog_field &analog : m_live->analoglist)
		analog.read(result);
>>>>>>> upstream/master

	return result;
}


//-------------------------------------------------
//  write - write a value to a port
//-------------------------------------------------

void ioport_port::write(ioport_value data, ioport_value mem_mask)
{
	// call device line write handlers
	COMBINE_DATA(&m_live->outputvalue);
<<<<<<< HEAD
	for (dynamic_field *dynfield = m_live->writelist.first(); dynfield != NULL; dynfield = dynfield->next())
		if (dynfield->field().type() == IPT_OUTPUT)
			dynfield->write(m_live->outputvalue ^ dynfield->field().defvalue());
=======
	for (dynamic_field &dynfield : m_live->writelist)
		if (dynfield.field().type() == IPT_OUTPUT)
			dynfield.write(m_live->outputvalue ^ dynfield.field().defvalue());
>>>>>>> upstream/master
}


//-------------------------------------------------
//  frame_update - once/frame update
//-------------------------------------------------

<<<<<<< HEAD
void ioport_port::frame_update(ioport_field *mouse_field)
=======
void ioport_port::frame_update()
>>>>>>> upstream/master
{
	// start with 0 values for the digital bits
	m_live->digital = 0;

	// now loop back and modify based on the inputs
<<<<<<< HEAD
	for (ioport_field *field = first_field(); field != NULL; field = field->next())
		field->frame_update(m_live->digital, field == mouse_field);

	// hook for MESS's natural keyboard support
	manager().natkeyboard().frame_update(*this, m_live->digital);
=======
	for (ioport_field &field : fields())
		field.frame_update(m_live->digital);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  collapse_fields - remove any fields that are
//  wholly overlapped by other fields
//-------------------------------------------------

void ioport_port::collapse_fields(std::string &errorbuf)
{
	ioport_value maskbits = 0;
	int lastmodcount = -1;

	// remove the whole list and start from scratch
	ioport_field *field = m_fieldlist.detach_all();
<<<<<<< HEAD
	while (field != NULL)
=======
	while (field != nullptr)
>>>>>>> upstream/master
	{
		// if this modcount doesn't match, reset
		if (field->modcount() != lastmodcount)
		{
			lastmodcount = field->modcount();
			maskbits = 0;
		}

		// reinsert this field
		ioport_field *current = field;
		field = field->next();
		insert_field(*current, maskbits, errorbuf);
	}
}


//-------------------------------------------------
//  insert_field - insert a new field, checking
//  for errors
//-------------------------------------------------

void ioport_port::insert_field(ioport_field &newfield, ioport_value &disallowedbits, std::string &errorbuf)
{
	// verify against the disallowed bits, but only if we are condition-free
	if (newfield.condition().none())
	{
		if ((newfield.mask() & disallowedbits) != 0)
<<<<<<< HEAD
			strcatprintf(errorbuf, "INPUT_TOKEN_FIELD specifies duplicate port bits (port=%s mask=%X)\n", tag(), newfield.mask());
=======
			errorbuf.append(string_format("INPUT_TOKEN_FIELD specifies duplicate port bits (port=%s mask=%X)\n", tag(), newfield.mask()));
>>>>>>> upstream/master
		disallowedbits |= newfield.mask();
	}

	// first modify/nuke any entries that intersect our maskbits
	ioport_field *nextfield;
<<<<<<< HEAD
	for (ioport_field *field = first_field(); field != NULL; field = nextfield)
=======
	for (ioport_field *field = m_fieldlist.first(); field != nullptr; field = nextfield)
>>>>>>> upstream/master
	{
		nextfield = field->next();
		if ((field->mask() & newfield.mask()) != 0 &&
			(newfield.condition().none() || field->condition().none() || field->condition() == newfield.condition()))
		{
			// reduce the mask of the field we found
			field->reduce_mask(newfield.mask());

			// if the new entry fully overrides the previous one, we nuke
			if (INPUT_PORT_OVERRIDE_FULLY_NUKES_PREVIOUS || field->mask() == 0)
				m_fieldlist.remove(*field);
		}
	}

	// make a mask of just the low bit
	ioport_value lowbit = (newfield.mask() ^ (newfield.mask() - 1)) & newfield.mask();

	// scan forward to find where to insert ourselves
	ioport_field *field;
<<<<<<< HEAD
	for (field = first_field(); field != NULL; field = field->next())
=======
	for (field = m_fieldlist.first(); field != nullptr; field = field->next())
>>>>>>> upstream/master
		if (field->mask() > lowbit)
			break;

	// insert it into the list
	m_fieldlist.insert_before(newfield, field);
}


//-------------------------------------------------
//  init_live_state - create the live state
//-------------------------------------------------

void ioport_port::init_live_state()
{
<<<<<<< HEAD
	m_live.reset(global_alloc(ioport_port_live(*this)));
=======
	m_live = std::make_unique<ioport_port_live>(*this);
}


//-------------------------------------------------
//  update_defvalue - force an update to the input
//  port values based on current conditions
//-------------------------------------------------

void ioport_port::update_defvalue(bool flush_defaults)
{
	// only clear on the first pass
	if (flush_defaults)
		m_live->defvalue = 0;

	// recompute the default value for the entire port
	for (ioport_field &field : m_fieldlist)
		if (field.enabled())
			m_live->defvalue = (m_live->defvalue & ~field.mask()) | (field.live().value & field.mask());
>>>>>>> upstream/master
}



//**************************************************************************
//  I/O PORT LIVE STATE
//**************************************************************************

//-------------------------------------------------
//  ioport_port_live - constructor
//-------------------------------------------------

ioport_port_live::ioport_port_live(ioport_port &port)
	: defvalue(0),
		digital(0),
		outputvalue(0)
{
	// iterate over fields
<<<<<<< HEAD
	for (ioport_field *field = port.first_field(); field != NULL; field = field->next())
	{
		// allocate analog state if it's analog
		analog_field *analog = NULL;
		if (field->is_analog())
			analog = &analoglist.append(*global_alloc(analog_field(*field)));

		// allocate a dynamic field for reading
		if (field->has_dynamic_read())
			readlist.append(*global_alloc(dynamic_field(*field)));

		// allocate a dynamic field for writing
		if (field->has_dynamic_write())
			writelist.append(*global_alloc(dynamic_field(*field)));

		// let the field initialize its live state
		field->init_live_state(analog);
=======
	for (ioport_field &field : port.fields())
	{
		// allocate analog state if it's analog
		analog_field *analog = nullptr;
		if (field.is_analog())
			analog = &analoglist.append(*global_alloc(analog_field(field)));

		// allocate a dynamic field for reading
		if (field.has_dynamic_read())
			readlist.append(*global_alloc(dynamic_field(field)));

		// allocate a dynamic field for writing
		if (field.has_dynamic_write())
			writelist.append(*global_alloc(dynamic_field(field)));

		// let the field initialize its live state
		field.init_live_state(analog);
>>>>>>> upstream/master
	}
}



//**************************************************************************
//  I/O PORT MANAGER
//**************************************************************************

//-------------------------------------------------
//  ioport_manager - constructor
//-------------------------------------------------

ioport_manager::ioport_manager(running_machine &machine)
	: m_machine(machine),
		m_safe_to_read(false),
<<<<<<< HEAD
#ifdef USE_SHOW_INPUT_LOG
		m_show_input_log(0),
#endif /* USE_SHOW_INPUT_LOG */
		m_natkeyboard(machine),
=======
>>>>>>> upstream/master
		m_last_frame_time(attotime::zero),
		m_last_delta_nsec(0),
		m_record_file(machine.options().input_directory(), OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS),
		m_playback_file(machine.options().input_directory(), OPEN_FLAG_READ),
<<<<<<< HEAD
#ifdef INP_CAPTION
		m_caption_file(machine.options().input_directory(), OPEN_FLAG_READ),
		m_next_caption_frame(-1),
		m_caption_timer(0),
#endif /* INP_CAPTION */
		m_playback_accumulated_speed(0),
		m_playback_accumulated_frames(0),
		m_has_configs(false),
		m_has_analog(false),
		m_has_dips(false),
		m_has_bioses(false)
{
	memset(m_type_to_entry, 0, sizeof(m_type_to_entry));
#ifdef USE_SHOW_INPUT_LOG
	memset(m_command_buffer, 0, sizeof(m_command_buffer));
#endif /* USE_SHOW_INPUT_LOG */
#ifdef USE_CUSTOM_BUTTON
	memset(m_custom_button, 0, sizeof(m_custom_button));
	memset(m_custom_button_info, 0, sizeof(m_custom_button_info));
#endif /* USE_CUSTOM_BUTTON */
#ifdef USE_AUTOFIRE
	for (int player = 0; player < MAX_PLAYERS; player++)
	{
		m_autofiredelay[player] = 3;	//mamep: 1 is too short for some games
		m_autofiretoggle[player] = 1;
	}
#endif /* USE_AUTOFIRE */
=======
		m_playback_accumulated_speed(0),
		m_playback_accumulated_frames(0),
		m_timecode_file(machine.options().input_directory(), OPEN_FLAG_WRITE | OPEN_FLAG_CREATE | OPEN_FLAG_CREATE_PATHS),
		m_timecode_count(0),
		m_timecode_last_time(attotime::zero),
		m_autofire_toggle(false),
		m_autofire_delay(3)                 // 1 seems too fast for a bunch of games
{
	memset(m_type_to_entry, 0, sizeof(m_type_to_entry));
>>>>>>> upstream/master
}


//-------------------------------------------------
//  initialize - walk the configured ports and
//  create live state information
//-------------------------------------------------

time_t ioport_manager::initialize()
{
	// add an exit callback and a frame callback
<<<<<<< HEAD
	machine().add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(FUNC(ioport_manager::exit), this));
	machine().add_notifier(MACHINE_NOTIFY_FRAME, machine_notify_delegate(FUNC(ioport_manager::frame_update_callback), this));
=======
	machine().add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(&ioport_manager::exit, this));
	machine().add_notifier(MACHINE_NOTIFY_FRAME, machine_notify_delegate(&ioport_manager::frame_update_callback, this));
>>>>>>> upstream/master

	// initialize the default port info from the OSD
	init_port_types();

	// if we have a token list, proceed
	device_iterator iter(machine().root_device());
<<<<<<< HEAD
	for (device_t *device = iter.first(); device != NULL; device = iter.next())
	{
		std::string errors;
#ifdef USE_CUSTOM_BUTTON
		m_portlist.append_custom(*device, errors);
#else
		m_portlist.append(*device, errors);
#endif /* USE_CUSTOM_BUTTON */
=======
	for (device_t &device : iter)
	{
		std::string errors;
		m_portlist.append(device, errors);
>>>>>>> upstream/master
		if (!errors.empty())
			osd_printf_error("Input port errors:\n%s", errors.c_str());
	}

	// renumber player numbers for controller ports
	int player_offset = 0;
<<<<<<< HEAD
	for (device_t *device = iter.first(); device != NULL; device = iter.next())
	{
		int players = 0;
		for (ioport_port *port = first_port(); port != NULL; port = port->next())
		{
			if (&port->device()==device)
			{
				port->init_live_state();
				for (ioport_field *field = port->first_field(); field != NULL; field = field->next())
				{
					if (field->type_class()==INPUT_CLASS_CONTROLLER)
					{
						if (players < field->player() + 1) players = field->player() + 1;
						field->set_player(field->player() + player_offset);
					}
#ifdef USE_CUSTOM_BUTTON
					if (field->type() >= IPT_CUSTOM1 && field->type() < IPT_CUSTOM1 + MAX_CUSTOM_BUTTONS)
						m_custom_button_info[field->player()][field->type() - IPT_CUSTOM1] = field;
#endif /* USE_CUSTOM_BUTTON */
				}
=======
	for (device_t &device : iter)
	{
		int players = 0;
		for (auto &port : m_portlist)
		{
			if (&port.second->device() == &device)
			{
				for (ioport_field &field : port.second->fields())
					if (field.type_class()==INPUT_CLASS_CONTROLLER)
					{
						if (players < field.player() + 1) players = field.player() + 1;
						field.set_player(field.player() + player_offset);
					}
>>>>>>> upstream/master
			}
		}
		player_offset += players;
	}

	// allocate live structures to mirror the configuration
<<<<<<< HEAD
	for (ioport_port *port = first_port(); port != NULL; port = port->next())
		port->init_live_state();
=======
	for (auto &port : m_portlist)
		port.second->init_live_state();
>>>>>>> upstream/master

	// handle autoselection of devices
	init_autoselect_devices(IPT_AD_STICK_X,  IPT_AD_STICK_Y,   IPT_AD_STICK_Z, OPTION_ADSTICK_DEVICE,    "analog joystick");
	init_autoselect_devices(IPT_PADDLE,      IPT_PADDLE_V,     0,              OPTION_PADDLE_DEVICE,     "paddle");
	init_autoselect_devices(IPT_PEDAL,       IPT_PEDAL2,       IPT_PEDAL3,     OPTION_PEDAL_DEVICE,      "pedal");
	init_autoselect_devices(IPT_LIGHTGUN_X,  IPT_LIGHTGUN_Y,   0,              OPTION_LIGHTGUN_DEVICE,   "lightgun");
	init_autoselect_devices(IPT_POSITIONAL,  IPT_POSITIONAL_V, 0,              OPTION_POSITIONAL_DEVICE, "positional");
	init_autoselect_devices(IPT_DIAL,        IPT_DIAL_V,       0,              OPTION_DIAL_DEVICE,       "dial");
	init_autoselect_devices(IPT_TRACKBALL_X, IPT_TRACKBALL_Y,  0,              OPTION_TRACKBALL_DEVICE,  "trackball");
	init_autoselect_devices(IPT_MOUSE_X,     IPT_MOUSE_Y,      0,              OPTION_MOUSE_DEVICE,      "mouse");

	// look for 4-way diagonal joysticks and change the default map if we find any
	const char *joystick_map_default = machine().options().joystick_map();
	if (joystick_map_default[0] == 0 || strcmp(joystick_map_default, "auto") == 0)
<<<<<<< HEAD
		for (ioport_port *port = first_port(); port != NULL; port = port->next())
			for (ioport_field *field = port->first_field(); field != NULL; field = field->next())
				if (field->live().joystick != NULL && field->rotated())
				{
					machine().input().set_global_joystick_map(joystick_map_4way_diagonal);
					break;
				}

	m_natkeyboard.initialize();
	// register callbacks for when we load configurations
	config_register(machine(), "input", config_saveload_delegate(FUNC(ioport_manager::load_config), this), config_saveload_delegate(FUNC(ioport_manager::save_config), this));

	// calculate "has..." values
	{
		m_has_configs = false;
		m_has_analog = false;
		m_has_dips = false;
		m_has_bioses = false;

		// scan the input port array to see what options we need to enable
		for (ioport_port *port = first_port(); port != NULL; port = port->next())
			for (ioport_field *field = port->first_field(); field != NULL; field = field->next())
			{
				if (field->type() == IPT_DIPSWITCH)
					m_has_dips = true;
				if (field->type() == IPT_CONFIG)
					m_has_configs = true;
				if (field->is_analog())
					m_has_analog = true;
			}
		device_iterator deviter(machine().root_device());
		for (device_t *device = deviter.first(); device != NULL; device = deviter.next())
			if (device->rom_region())
				for (const rom_entry *rom = device->rom_region(); !ROMENTRY_ISEND(rom); rom++)
					if (ROMENTRY_ISSYSTEM_BIOS(rom)) { m_has_bioses= true; break; }
	}
=======
		for (auto &port : m_portlist)
			for (ioport_field &field : port.second->fields())
				if (field.live().joystick != nullptr && field.rotated())
				{
					input_class_joystick &devclass = downcast<input_class_joystick &>(machine().input().device_class(DEVICE_CLASS_JOYSTICK));
					devclass.set_global_joystick_map(input_class_joystick::map_4way_diagonal);
					break;
				}

	// initialize natural keyboard
	m_natkeyboard = std::make_unique<natural_keyboard>(machine());

	// register callbacks for when we load configurations
	machine().configuration().config_register("input", config_load_delegate(&ioport_manager::load_config, this), config_save_delegate(&ioport_manager::save_config, this));
>>>>>>> upstream/master

	// open playback and record files if specified
	time_t basetime = playback_init();
	record_init();
<<<<<<< HEAD
=======
	timecode_init();
>>>>>>> upstream/master
	return basetime;
}


//-------------------------------------------------
//  init_port_types - initialize the default
//  type list
//-------------------------------------------------

void ioport_manager::init_port_types()
{
	// convert the array into a list of type states that can be modified
	construct_core_types(m_typelist);

	// ask the OSD to customize the list
	machine().osd().customize_input_type_list(m_typelist);

	// now iterate over the OSD-modified types
<<<<<<< HEAD
	for (input_type_entry *curtype = first_type(); curtype != NULL; curtype = curtype->next())
	{
		// first copy all the OSD-updated sequences into our current state
		curtype->restore_default_seq();

		// also make a lookup table mapping type/player to the appropriate type list entry
		m_type_to_entry[curtype->type()][curtype->player()] = curtype;
=======
	for (input_type_entry &curtype : m_typelist)
	{
		// first copy all the OSD-updated sequences into our current state
		curtype.restore_default_seq();

		// also make a lookup table mapping type/player to the appropriate type list entry
		m_type_to_entry[curtype.type()][curtype.player()] = &curtype;
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  init_autoselect_devices - autoselect a single
//  device based on the input port list passed
//  in and the corresponding option
//-------------------------------------------------

void ioport_manager::init_autoselect_devices(int type1, int type2, int type3, const char *option, const char *ananame)
{
	// if nothing specified, ignore the option
	const char *stemp = machine().options().value(option);
<<<<<<< HEAD
	if (stemp[0] == 0)
		return;

	// extract valid strings
	const char *autostring = "keyboard";
	input_device_class autoenable = DEVICE_CLASS_KEYBOARD;
	if (strcmp(stemp, "mouse") == 0)
	{
		autoenable = DEVICE_CLASS_MOUSE;
		autostring = "mouse";
	}
	else if (strcmp(stemp, "joystick") == 0)
	{
		autoenable = DEVICE_CLASS_JOYSTICK;
		autostring = "joystick";
	}
	else if (strcmp(stemp, "lightgun") == 0)
	{
		autoenable = DEVICE_CLASS_LIGHTGUN;
		autostring = "lightgun";
	}
	else if (strcmp(stemp, "none") == 0)
	{
		// nothing specified
		return;
	}
	else if (strcmp(stemp, "keyboard") != 0)
		osd_printf_error("Invalid %s value %s; reverting to keyboard\n", option, stemp);

	// only scan the list if we haven't already enabled this class of control
	if (first_port() != NULL && !machine().input().device_class(autoenable).enabled())
		for (ioport_port *port = first_port(); port != NULL; port = port->next())
			for (ioport_field *field = port->first_field(); field != NULL; field = field->next())

				// if this port type is in use, apply the autoselect criteria
				if ((type1 != 0 && field->type() == type1) || (type2 != 0 && field->type() == type2) || (type3 != 0 && field->type() == type3))
				{
					osd_printf_verbose("Input: Autoenabling %s due to presence of a %s\n", autostring, ananame);
					machine().input().device_class(autoenable).enable();
=======
	if (stemp[0] == 0 || strcmp(stemp, "none") == 0)
		return;

	// extract valid strings
	input_class *autoenable_class = nullptr;
	for (input_device_class devclass = DEVICE_CLASS_FIRST_VALID; devclass <= DEVICE_CLASS_LAST_VALID; ++devclass)
		if (strcmp(stemp, machine().input().device_class(devclass).name()) == 0)
		{
			autoenable_class = &machine().input().device_class(devclass);
			break;
		}
	if (autoenable_class == nullptr)
	{
		osd_printf_error("Invalid %s value %s; reverting to keyboard\n", option, stemp);
		autoenable_class = &machine().input().device_class(DEVICE_CLASS_KEYBOARD);
	}

	// only scan the list if we haven't already enabled this class of control
	if (!autoenable_class->enabled())
		for (auto &port : m_portlist)
			for (ioport_field &field : port.second->fields())

				// if this port type is in use, apply the autoselect criteria
				if ((type1 != 0 && field.type() == type1) || (type2 != 0 && field.type() == type2) || (type3 != 0 && field.type() == type3))
				{
					osd_printf_verbose("Input: Autoenabling %s due to presence of a %s\n", autoenable_class->name(), ananame);
					autoenable_class->enable();
>>>>>>> upstream/master
					break;
				}
}


//-------------------------------------------------
//  exit - exit callback to ensure we clean up
//  and close our files
//-------------------------------------------------

void ioport_manager::exit()
{
	// close any playback or recording files
	playback_end();
	record_end();
<<<<<<< HEAD
=======
	timecode_end();
}


//-------------------------------------------------
//  ~ioport_manager - destructor
//-------------------------------------------------

ioport_manager::~ioport_manager()
{
>>>>>>> upstream/master
}


//-------------------------------------------------
//  type_name - return the name for the given
//  type/player
//-------------------------------------------------

<<<<<<< HEAD
const char *ioport_manager::type_name(ioport_type type, UINT8 player)
{
	// if we have a machine, use the live state and quick lookup
	input_type_entry *entry = m_type_to_entry[type][player];
	if (entry != NULL)
		return entry->name();

	// if we find nothing, return an invalid group
=======
const char *ioport_manager::type_name(ioport_type type, u8 player)
{
	// if we have a machine, use the live state and quick lookup
	input_type_entry *entry = m_type_to_entry[type][player];
	if (entry != nullptr && entry->name() != nullptr)
		return entry->name();

	// if we find nothing, return a default string (not a null pointer)
>>>>>>> upstream/master
	return "???";
}


//-------------------------------------------------
//  type_group - return the group for the given
//  type/player
//-------------------------------------------------

ioport_group ioport_manager::type_group(ioport_type type, int player)
{
	input_type_entry *entry = m_type_to_entry[type][player];
<<<<<<< HEAD
	if (entry != NULL)
=======
	if (entry != nullptr)
>>>>>>> upstream/master
		return entry->group();

	// if we find nothing, return an invalid group
	return IPG_INVALID;
}


//-------------------------------------------------
//  type_seq - return the input sequence for the
//  given type/player
//-------------------------------------------------

const input_seq &ioport_manager::type_seq(ioport_type type, int player, input_seq_type seqtype)
{
	assert(type >= 0 && type < IPT_COUNT);
	assert(player >= 0 && player < MAX_PLAYERS);

	// if we have a machine, use the live state and quick lookup
	input_type_entry *entry = m_type_to_entry[type][player];
<<<<<<< HEAD
	if (entry != NULL)
=======
	if (entry != nullptr)
>>>>>>> upstream/master
		return entry->seq(seqtype);

	// if we find nothing, return an empty sequence
	return input_seq::empty_seq;
}


//-------------------------------------------------
//  set_type_seq - change the input sequence for
//  the given type/player
//-------------------------------------------------

void ioport_manager::set_type_seq(ioport_type type, int player, input_seq_type seqtype, const input_seq &newseq)
{
	input_type_entry *entry = m_type_to_entry[type][player];
<<<<<<< HEAD
	if (entry != NULL)
=======
	if (entry != nullptr)
>>>>>>> upstream/master
		entry->m_seq[seqtype] = newseq;
}


//-------------------------------------------------
//  type_pressed - return true if the sequence for
//  the given input type/player is pressed
//-------------------------------------------------

bool ioport_manager::type_pressed(ioport_type type, int player)
{
	return machine().input().seq_pressed(type_seq(type, player));
}


//-------------------------------------------------
//  type_class_present - return true if the given
//  ioport_type_class exists in at least one port
//-------------------------------------------------

bool ioport_manager::type_class_present(ioport_type_class inputclass)
{
<<<<<<< HEAD
	for (ioport_port *port = first_port(); port != NULL; port = port->next())
		for (ioport_field *field = port->first_field(); field != NULL; field = field->next())
			if (field->type_class() == inputclass)
=======
	for (auto &port : m_portlist)
		for (ioport_field &field : port.second->fields())
			if (field.type_class() == inputclass)
>>>>>>> upstream/master
				return true;
	return false;
}


//-------------------------------------------------
<<<<<<< HEAD
//  has_keyboard - determine if there is a
//  keyboard present in the control list
//-------------------------------------------------

bool ioport_manager::has_keyboard() const
{
	// iterate over ports and fields
	for (ioport_port *port = first_port(); port != NULL; port = port->next())
		for (ioport_field *field = port->first_field(); field != NULL; field = field->next())
		{
			// if we are at init, check IPT_KEYBOARD
			if (!m_safe_to_read && field->type() == IPT_KEYBOARD)
				return true;

			// else, check if there is a keyboard and if such a keyboard is enabled
			if (field->type() == IPT_KEYBOARD && field->enabled())
				return true;
		}

	return false;
}

//-------------------------------------------------
=======
>>>>>>> upstream/master
//  count_players - counts the number of active
//  players
//-------------------------------------------------

int ioport_manager::count_players() const
{
	int max_player = 0;
<<<<<<< HEAD
	for (ioport_port *port = first_port(); port != NULL; port = port->next())
		for (ioport_field *field = port->first_field(); field != NULL; field = field->next())
			if (field->type_class() == INPUT_CLASS_CONTROLLER && max_player <= field->player() + 1)
				max_player = field->player() + 1;
=======
	for (auto &port : m_portlist)
		for (ioport_field &field : port.second->fields())
			if (field.type_class() == INPUT_CLASS_CONTROLLER && max_player <= field.player() + 1)
				max_player = field.player() + 1;
>>>>>>> upstream/master

	return max_player;
}


//-------------------------------------------------
//  crosshair_position - return the extracted
//  crosshair values for the given player
//-------------------------------------------------

bool ioport_manager::crosshair_position(int player, float &x, float &y)
{
	// read all the lightgun values
	bool gotx = false, goty = false;
<<<<<<< HEAD
	for (ioport_port *port = first_port(); port != NULL; port = port->next())
		for (ioport_field *field = port->first_field(); field != NULL; field = field->next())
			if (field->player() == player && field->crosshair_axis() != CROSSHAIR_AXIS_NONE && field->enabled())
			{
				field->crosshair_position(x, y, gotx, goty);
=======
	for (auto &port : m_portlist)
		for (ioport_field &field : port.second->fields())
			if (field.player() == player && field.crosshair_axis() != CROSSHAIR_AXIS_NONE && field.enabled())
			{
				field.crosshair_position(x, y, gotx, goty);
>>>>>>> upstream/master

				// if we got both, stop
				if (gotx && goty)
					break;
			}

	return (gotx && goty);
}


//-------------------------------------------------
<<<<<<< HEAD
//  update_defaults - force an update to the input
//  port values based on current conditions
//-------------------------------------------------

void ioport_manager::update_defaults()
{
	// two passes to catch conditionals properly
	for (int loopnum = 0; loopnum < 2; loopnum++)
	{
		// loop over all input ports
		for (ioport_port *port = first_port(); port != NULL; port = port->next())
		{
			// only clear on the first pass
			if (loopnum == 0)
				port->live().defvalue = 0;

			// first compute the default value for the entire port
			for (ioport_field *field = port->first_field(); field != NULL; field = field->next())
				if (field->enabled())
					port->live().defvalue = (port->live().defvalue & ~field->mask()) | (field->live().value & field->mask());
		}
	}
}


//-------------------------------------------------
=======
>>>>>>> upstream/master
//  frame_update - core logic for per-frame input
//  port updating
//-------------------------------------------------

digital_joystick &ioport_manager::digjoystick(int player, int number)
{
	// find it in the list
<<<<<<< HEAD
	for (digital_joystick *joystick = m_joystick_list.first(); joystick != NULL; joystick = joystick->next())
		if (joystick->player() == player && joystick->number() == number)
			return *joystick;
=======
	for (digital_joystick &joystick : m_joystick_list)
		if (joystick.player() == player && joystick.number() == number)
			return joystick;
>>>>>>> upstream/master

	// create a new one
	return m_joystick_list.append(*global_alloc(digital_joystick(player, number)));
}


//-------------------------------------------------
//  frame_update - callback for once/frame updating
//-------------------------------------------------

void ioport_manager::frame_update_callback()
{
	// if we're paused, don't do anything
	if (!machine().paused())
		frame_update();
}


//-------------------------------------------------
//  frame_update_internal - core logic for
//  per-frame input port updating
//-------------------------------------------------

void ioport_manager::frame_update()
{
g_profiler.start(PROFILER_INPUT);

	// record/playback information about the current frame
	attotime curtime = machine().time();
	playback_frame(curtime);
	record_frame(curtime);

	// track the duration of the previous frame
	m_last_delta_nsec = (curtime - m_last_frame_time).as_attoseconds() / ATTOSECONDS_PER_NANOSECOND;
	m_last_frame_time = curtime;

	// update the digital joysticks
<<<<<<< HEAD
	for (digital_joystick *joystick = m_joystick_list.first(); joystick != NULL; joystick = joystick->next())
		joystick->frame_update();

	// compute default values for all the ports
	update_defaults();

	// perform mouse hit testing
	INT32 mouse_target_x, mouse_target_y;
	bool mouse_button;
	render_target *mouse_target = ui_input_find_mouse(machine(), &mouse_target_x, &mouse_target_y, &mouse_button);

	// if the button is pressed, map the point and determine what was hit
	ioport_field *mouse_field = NULL;
	if (mouse_button && mouse_target != NULL)
	{
		ioport_port *port = NULL;
		ioport_value mask;
		float x, y;
		if (mouse_target->map_point_input(mouse_target_x, mouse_target_y, port, mask, x, y))
		{
			if (port != NULL)
				mouse_field = port->field(mask);
		}
	}

	// loop over all input ports
	for (ioport_port *port = first_port(); port != NULL; port = port->next())
	{
#ifdef USE_AUTOFIRE
#ifdef USE_CUSTOM_BUTTON
		/* now loop back and modify based on the inputs */
		for (ioport_field *field = port->first_field(); field != NULL; field = field->next())
//			if (input_condition_true(port->machine(), &field->condition, port->owner()))
			{
				/* update autofire status */
				if (field->type() >= IPT_CUSTOM1 && field->type() < IPT_CUSTOM1 + MAX_CUSTOM_BUTTONS)
				{
					if (machine().input().seq_pressed(field->seq(SEQ_TYPE_STANDARD)))
					{
						if (field->live().autopressed > m_autofiredelay[field->player()])
							field->live().autopressed = 0;
	
						field->live().autopressed ++;
					}
					else
						field->live().autopressed = 0;
	
					continue;
				}
			}
#endif /* USE_CUSTOM_BUTTON */
#endif /* USE_AUTOFIRE */

		port->frame_update(mouse_field);

		// handle playback/record
		playback_port(*port);
		record_port(*port);

		// call device line write handlers
		ioport_value newvalue = port->read();
		for (dynamic_field *dynfield = port->live().writelist.first(); dynfield != NULL; dynfield = dynfield->next())
			if (dynfield->field().type() != IPT_OUTPUT)
				dynfield->write(newvalue);
	}

#ifdef USE_SHOW_INPUT_LOG
	/* show input log */
	if (m_show_input_log && (!has_playback_file()))
		make_input_log();
#endif /* USE_SHOW_INPUT_LOG */

=======
	for (digital_joystick &joystick : m_joystick_list)
		joystick.frame_update();

	// compute default values for all the ports
	// two passes to catch conditionals properly
	for (auto &port : m_portlist)
		port.second->update_defvalue(true);
	for (auto &port : m_portlist)
		port.second->update_defvalue(false);

	// loop over all input ports
	for (auto &port : m_portlist)
	{
		port.second->frame_update();

		// handle playback/record
		playback_port(*port.second.get());
		record_port(*port.second.get());

		// call device line write handlers
		ioport_value newvalue = port.second->read();
		for (dynamic_field &dynfield : port.second->live().writelist)
			if (dynfield.field().type() != IPT_OUTPUT)
				dynfield.write(newvalue);
	}

>>>>>>> upstream/master
g_profiler.stop();
}


//-------------------------------------------------
//  frame_interpolate - interpolate between two
//  values based on the time between frames
//-------------------------------------------------

<<<<<<< HEAD
INT32 ioport_manager::frame_interpolate(INT32 oldval, INT32 newval)
=======
s32 ioport_manager::frame_interpolate(s32 oldval, s32 newval)
>>>>>>> upstream/master
{
	// if no last delta, just use new value
	if (m_last_delta_nsec == 0)
		return newval;

	// otherwise, interpolate
	attoseconds_t nsec_since_last = (machine().time() - m_last_frame_time).as_attoseconds() / ATTOSECONDS_PER_NANOSECOND;
<<<<<<< HEAD
	return oldval + (INT64(newval - oldval) * nsec_since_last / m_last_delta_nsec);
=======
	return oldval + (s64(newval - oldval) * nsec_since_last / m_last_delta_nsec);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  load_config - callback to extract configuration
//  data from the XML nodes
//-------------------------------------------------

<<<<<<< HEAD
void ioport_manager::load_config(int config_type, xml_data_node *parentnode)
{
	// in the completion phase, we finish the initialization with the final ports
	if (config_type == CONFIG_TYPE_FINAL)
=======
void ioport_manager::load_config(config_type cfg_type, util::xml::data_node const *parentnode)
{
	// in the completion phase, we finish the initialization with the final ports
	if (cfg_type == config_type::FINAL)
>>>>>>> upstream/master
	{
		m_safe_to_read = true;
		frame_update();
	}

	// early exit if no data to parse
<<<<<<< HEAD
	if (parentnode == NULL)
		return;

	// iterate over all the remap nodes for controller configs only
	if (config_type == CONFIG_TYPE_CONTROLLER)
		load_remap_table(parentnode);

	// iterate over all the port nodes
	for (xml_data_node *portnode = xml_get_sibling(parentnode->child, "port"); portnode; portnode = xml_get_sibling(portnode->next, "port"))
	{
		// get the basic port info from the attributes
		int player;
		int type = token_to_input_type(xml_get_attribute_string(portnode, "type", ""), player);
=======
	if (parentnode == nullptr)
		return;

	// iterate over all the remap nodes for controller configs only
	if (cfg_type == config_type::CONTROLLER)
		load_remap_table(parentnode);

	// load device map table for controller configs only
	if (cfg_type == config_type::CONTROLLER)
	{
		std::unique_ptr<devicemap_table_type> devicemap_table = std::make_unique<devicemap_table_type>();
		for (util::xml::data_node const *mapdevice_node = parentnode->get_child("mapdevice"); mapdevice_node != nullptr; mapdevice_node = mapdevice_node->get_next_sibling("mapdevice"))
		{
			const char *devicename = mapdevice_node->get_attribute_string("device", nullptr);
			const char *controllername = mapdevice_node->get_attribute_string("controller", nullptr);
			if (devicename != nullptr && controllername != nullptr)
			{
				devicemap_table->insert(std::make_pair(std::string(devicename), std::string(controllername)));
			}
		}

		// map device to controller if we have a device map
		if (!devicemap_table->empty())
		{
			machine().input().map_device_to_controller(devicemap_table.get());
		}
	}

	// iterate over all the port nodes
	for (util::xml::data_node const *portnode = parentnode->get_child("port"); portnode; portnode = portnode->get_next_sibling("port"))
	{
		// get the basic port info from the attributes
		int player;
		int type = token_to_input_type(portnode->get_attribute_string("type", ""), player);
>>>>>>> upstream/master

		// initialize sequences to invalid defaults
		input_seq newseq[SEQ_TYPE_TOTAL];
		for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
			newseq[seqtype].set(INPUT_CODE_INVALID);

		// loop over new sequences
<<<<<<< HEAD
		for (xml_data_node *seqnode = xml_get_sibling(portnode->child, "newseq"); seqnode; seqnode = xml_get_sibling(seqnode->next, "newseq"))
		{
			// with a valid type, parse out the new sequence
			input_seq_type seqtype = token_to_seq_type(xml_get_attribute_string(seqnode, "type", ""));
			if (seqtype != -1 && seqnode->value != NULL)
			{
				if (strcmp(seqnode->value, "NONE") == 0)
					newseq[seqtype].set();
				else
					machine().input().seq_from_tokens(newseq[seqtype], seqnode->value);
=======
		for (util::xml::data_node const *seqnode = portnode->get_child("newseq"); seqnode; seqnode = seqnode->get_next_sibling("newseq"))
		{
			// with a valid type, parse out the new sequence
			input_seq_type seqtype = token_to_seq_type(seqnode->get_attribute_string("type", ""));
			if (seqtype != -1 && seqnode->get_value() != nullptr)
			{
				if (strcmp(seqnode->get_value(), "NONE") == 0)
					newseq[seqtype].set();
				else
					machine().input().seq_from_tokens(newseq[seqtype], seqnode->get_value());
>>>>>>> upstream/master
			}
		}

		// if we're loading default ports, apply to the defaults
<<<<<<< HEAD
		if (config_type != CONFIG_TYPE_GAME)
=======
		if (cfg_type != config_type::GAME)
>>>>>>> upstream/master
			load_default_config(portnode, type, player, newseq);
		else
			load_game_config(portnode, type, player, newseq);
	}

<<<<<<< HEAD
#ifdef USE_AUTOFIRE
	if (config_type == CONFIG_TYPE_GAME)
	{
		for (xml_data_node *portnode = xml_get_sibling(parentnode->child, "autofire"); portnode; portnode = xml_get_sibling(portnode->next, "autofire"))
		{
			int player = xml_get_attribute_int(portnode, "player", 0);

			if (player > 0 && player <= MAX_PLAYERS)
				m_autofiredelay[player - 1] = xml_get_attribute_int(portnode, "delay", 3);
		}
	}
#endif /* USE_AUTOFIRE */

	// after applying the controller config, push that back into the backup, since that is
	// what we will diff against
	if (config_type == CONFIG_TYPE_CONTROLLER)
		for (input_type_entry *entry = m_typelist.first(); entry != NULL; entry = entry->next())
			for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
				entry->defseq(seqtype) = entry->seq(seqtype);
=======
	// after applying the controller config, push that back into the backup, since that is
	// what we will diff against
	if (cfg_type == config_type::CONTROLLER)
		for (input_type_entry &entry : m_typelist)
			for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
				entry.defseq(seqtype) = entry.seq(seqtype);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  load_remap_table - extract and apply the
//  global remapping table
//-------------------------------------------------

<<<<<<< HEAD
void ioport_manager::load_remap_table(xml_data_node *parentnode)
{
	// count items first so we can allocate
	int count = 0;
	for (xml_data_node *remapnode = xml_get_sibling(parentnode->child, "remap"); remapnode != NULL; remapnode = xml_get_sibling(remapnode->next, "remap"))
=======
void ioport_manager::load_remap_table(util::xml::data_node const *parentnode)
{
	// count items first so we can allocate
	int count = 0;
	for (util::xml::data_node const *remapnode = parentnode->get_child("remap"); remapnode != nullptr; remapnode = remapnode->get_next_sibling("remap"))
>>>>>>> upstream/master
		count++;

	// if we have some, deal with them
	if (count > 0)
	{
		// allocate tables
		std::vector<input_code> oldtable(count);
		std::vector<input_code> newtable(count);

		// build up the remap table
		count = 0;
<<<<<<< HEAD
		for (xml_data_node *remapnode = xml_get_sibling(parentnode->child, "remap"); remapnode != NULL; remapnode = xml_get_sibling(remapnode->next, "remap"))
		{
			input_code origcode = machine().input().code_from_token(xml_get_attribute_string(remapnode, "origcode", ""));
			input_code newcode = machine().input().code_from_token(xml_get_attribute_string(remapnode, "newcode", ""));
=======
		for (util::xml::data_node const *remapnode = parentnode->get_child("remap"); remapnode != nullptr; remapnode = remapnode->get_next_sibling("remap"))
		{
			input_code origcode = machine().input().code_from_token(remapnode->get_attribute_string("origcode", ""));
			input_code newcode = machine().input().code_from_token(remapnode->get_attribute_string("newcode", ""));
>>>>>>> upstream/master
			if (origcode != INPUT_CODE_INVALID && newcode != INPUT_CODE_INVALID)
			{
				oldtable[count] = origcode;
				newtable[count] = newcode;
				count++;
			}
		}

		// loop over the remapping table, then over default ports, replacing old with new
		for (int remapnum = 0; remapnum < count; remapnum++)
<<<<<<< HEAD
			for (input_type_entry *entry = m_typelist.first(); entry != NULL; entry = entry->next())
				for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
					entry->m_seq[seqtype].replace(oldtable[remapnum], newtable[remapnum]);
=======
			for (input_type_entry &entry : m_typelist)
				for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
					entry.m_seq[seqtype].replace(oldtable[remapnum], newtable[remapnum]);
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  load_default_config - apply configuration
//  data to the default mappings
//-------------------------------------------------

<<<<<<< HEAD
bool ioport_manager::load_default_config(xml_data_node *portnode, int type, int player, const input_seq *newseq)
{
	// find a matching port in the list
	for (input_type_entry *entry = m_typelist.first(); entry != NULL; entry = entry->next())
		if (entry->type() == type && entry->player() == player)
		{
			for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
				if (newseq[seqtype][0] != INPUT_CODE_INVALID)
					entry->m_seq[seqtype] = newseq[seqtype];
=======
bool ioport_manager::load_default_config(util::xml::data_node const *portnode, int type, int player, const input_seq *newseq)
{
	// find a matching port in the list
	for (input_type_entry &entry : m_typelist)
		if (entry.type() == type && entry.player() == player)
		{
			for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
				if (newseq[seqtype][0] != INPUT_CODE_INVALID)
					entry.m_seq[seqtype] = newseq[seqtype];
>>>>>>> upstream/master
			return true;
		}

	return false;
}


//-------------------------------------------------
//  load_game_config - apply configuration
//  data to the current set of input ports
//-------------------------------------------------

<<<<<<< HEAD
bool ioport_manager::load_game_config(xml_data_node *portnode, int type, int player, const input_seq *newseq)
{
	// read the mask, index, and defvalue attributes
	const char *tag = xml_get_attribute_string(portnode, "tag", NULL);
	ioport_value mask = xml_get_attribute_int(portnode, "mask", 0);
	ioport_value defvalue = xml_get_attribute_int(portnode, "defvalue", 0);

	// find the port we want; if no tag, search them all
	for (ioport_port *port = first_port(); port != NULL; port = port->next())
		if (tag == NULL || strcmp(port->tag(), tag) == 0)
			for (ioport_field *field = port->first_field(); field != NULL; field = field->next())

				// find the matching mask and defvalue
				if (field->type() == type && field->player() == player &&
					field->mask() == mask && (field->defvalue() & mask) == (defvalue & mask))
=======
bool ioport_manager::load_game_config(util::xml::data_node const *portnode, int type, int player, const input_seq *newseq)
{
	// read the mask, index, and defvalue attributes
	const char *tag = portnode->get_attribute_string("tag", nullptr);
	ioport_value mask = portnode->get_attribute_int("mask", 0);
	ioport_value defvalue = portnode->get_attribute_int("defvalue", 0);

	// find the port we want; if no tag, search them all
	for (auto &port : m_portlist)
		if (tag == nullptr || strcmp(port.second->tag(), tag) == 0)
			for (ioport_field &field : port.second->fields())

				// find the matching mask and defvalue
				if (field.type() == type && field.player() == player &&
					field.mask() == mask && (field.defvalue() & mask) == (defvalue & mask))
>>>>>>> upstream/master
				{
					// if a sequence was specified, copy it in
					for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
						if (newseq[seqtype][0] != INPUT_CODE_INVALID)
<<<<<<< HEAD
							field->live().seq[seqtype] = newseq[seqtype];

					// fetch configurable attributes
					// for non-analog fields
					if (field->live().analog == NULL)
					{
						// fetch the value
						field->live().value = xml_get_attribute_int(portnode, "value", field->defvalue());

						// fetch yes/no for toggle setting
						const char *togstring = xml_get_attribute_string(portnode, "toggle", NULL);
						if (togstring != NULL)
							field->live().toggle = (strcmp(togstring, "yes") == 0);
#ifdef USE_AUTOFIRE
						if (strcmp(xml_get_attribute_string(portnode, "autofire", "off"), "on") == 0)
							field->live().autofire = AUTOFIRE_ON;
						else if (strcmp(xml_get_attribute_string(portnode, "autofire", "off"), "toggle") == 0)
							field->live().autofire = AUTOFIRE_TOGGLE;
						else
							field->live().autofire = 0;
#endif /* USE_AUTOFIRE */

#ifdef USE_CUSTOM_BUTTON
						if (field->type() >= IPT_CUSTOM1 && field->type() < IPT_CUSTOM1 + MAX_CUSTOM_BUTTONS)
							m_custom_button[field->player()][field->type() - IPT_CUSTOM1] = xml_get_attribute_int(portnode, "custom", 0);
#endif /* USE_CUSTOM_BUTTON */
=======
							field.live().seq[seqtype] = newseq[seqtype];

					// fetch configurable attributes
					// for non-analog fields
					if (field.live().analog == nullptr)
					{
						// fetch the value
						field.live().value = portnode->get_attribute_int("value", field.defvalue());

						// fetch yes/no for toggle setting
						const char *togstring = portnode->get_attribute_string("toggle", nullptr);
						if (togstring != nullptr)
							field.live().toggle = (strcmp(togstring, "yes") == 0);
>>>>>>> upstream/master
					}

					// for analog fields
					else
					{
						// get base attributes
<<<<<<< HEAD
						field->live().analog->m_delta = xml_get_attribute_int(portnode, "keydelta", field->delta());
						field->live().analog->m_centerdelta = xml_get_attribute_int(portnode, "centerdelta", field->centerdelta());
						field->live().analog->m_sensitivity = xml_get_attribute_int(portnode, "sensitivity", field->sensitivity());

						// fetch yes/no for reverse setting
						const char *revstring = xml_get_attribute_string(portnode, "reverse", NULL);
						if (revstring != NULL)
							field->live().analog->m_reverse = (strcmp(revstring, "yes") == 0);
=======
						field.live().analog->m_delta = portnode->get_attribute_int("keydelta", field.delta());
						field.live().analog->m_centerdelta = portnode->get_attribute_int("centerdelta", field.centerdelta());
						field.live().analog->m_sensitivity = portnode->get_attribute_int("sensitivity", field.sensitivity());

						// fetch yes/no for reverse setting
						const char *revstring = portnode->get_attribute_string("reverse", nullptr);
						if (revstring != nullptr)
							field.live().analog->m_reverse = (strcmp(revstring, "yes") == 0);
>>>>>>> upstream/master
					}
					return true;
				}

	return false;
}



//**************************************************************************
//  SETTINGS SAVE
//**************************************************************************

//-------------------------------------------------
//  save_config - config callback for saving input
//  port configuration
//-------------------------------------------------

<<<<<<< HEAD
void ioport_manager::save_config(int config_type, xml_data_node *parentnode)
{
	// if no parentnode, ignore
	if (parentnode == NULL)
		return;

	// default ports save differently
	if (config_type == CONFIG_TYPE_DEFAULT)
		save_default_inputs(parentnode);
	else
		save_game_inputs(parentnode);
=======
void ioport_manager::save_config(config_type cfg_type, util::xml::data_node *parentnode)
{
	// if no parentnode, ignore
	if (parentnode == nullptr)
		return;

	// default ports save differently
	if (cfg_type == config_type::DEFAULT)
		save_default_inputs(*parentnode);
	else
		save_game_inputs(*parentnode);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  save_sequence - add a node for an input
//  sequence
//-------------------------------------------------

<<<<<<< HEAD
void ioport_manager::save_sequence(xml_data_node *parentnode, input_seq_type type, ioport_type porttype, const input_seq &seq)
=======
void ioport_manager::save_sequence(util::xml::data_node &parentnode, input_seq_type type, ioport_type porttype, const input_seq &seq)
>>>>>>> upstream/master
{
	// get the string for the sequence
	std::string seqstring;
	if (seq.length() == 0)
		seqstring.assign("NONE");
	else
<<<<<<< HEAD
		machine().input().seq_to_tokens(seqstring, seq);

	// add the new node
	xml_data_node *seqnode = xml_add_child(parentnode, "newseq", seqstring.c_str());
	if (seqnode != NULL)
		xml_set_attribute(seqnode, "type", seqtypestrings[type]);
=======
		seqstring = machine().input().seq_to_tokens(seq);

	// add the new node
	util::xml::data_node *const seqnode = parentnode.add_child("newseq", seqstring.c_str());
	if (seqnode != nullptr)
		seqnode->set_attribute("type", seqtypestrings[type]);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  save_this_input_field_type - determine if the
//  given port type is worth saving
//-------------------------------------------------

bool ioport_manager::save_this_input_field_type(ioport_type type)
{
	switch (type)
	{
		case IPT_UNUSED:
		case IPT_END:
		case IPT_PORT:
		case IPT_UNKNOWN:
			return false;

		default:
			break;
	}
	return true;
}


//-------------------------------------------------
//  save_default_inputs - add nodes for any default
//  mappings that have changed
//-------------------------------------------------

<<<<<<< HEAD
void ioport_manager::save_default_inputs(xml_data_node *parentnode)
{
	// iterate over ports
	for (input_type_entry *entry = m_typelist.first(); entry != NULL; entry = entry->next())
	{
		// only save if this port is a type we save
		if (save_this_input_field_type(entry->type()))
=======
void ioport_manager::save_default_inputs(util::xml::data_node &parentnode)
{
	// iterate over ports
	for (input_type_entry &entry : m_typelist)
	{
		// only save if this port is a type we save
		if (save_this_input_field_type(entry.type()))
>>>>>>> upstream/master
		{
			// see if any of the sequences have changed
			input_seq_type seqtype;
			for (seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
<<<<<<< HEAD
				if (entry->seq(seqtype) != entry->defseq(seqtype))
=======
				if (entry.seq(seqtype) != entry.defseq(seqtype))
>>>>>>> upstream/master
					break;

			// if so, we need to add a node
			if (seqtype < SEQ_TYPE_TOTAL)
			{
				// add a new port node
<<<<<<< HEAD
				xml_data_node *portnode = xml_add_child(parentnode, "port", NULL);
				if (portnode != NULL)
				{
					// add the port information and attributes
					std::string tempstr;
					xml_set_attribute(portnode, "type", input_type_to_token(tempstr, entry->type(), entry->player()));

					// add only the sequences that have changed from the defaults
					for (input_seq_type type = SEQ_TYPE_STANDARD; type < SEQ_TYPE_TOTAL; ++type)
						if (entry->seq(type) != entry->defseq(type))
							save_sequence(portnode, type, entry->type(), entry->seq(type));
=======
				util::xml::data_node *const portnode = parentnode.add_child("port", nullptr);
				if (portnode != nullptr)
				{
					// add the port information and attributes
					portnode->set_attribute("type", input_type_to_token(entry.type(), entry.player()).c_str());

					// add only the sequences that have changed from the defaults
					for (input_seq_type type = SEQ_TYPE_STANDARD; type < SEQ_TYPE_TOTAL; ++type)
						if (entry.seq(type) != entry.defseq(type))
							save_sequence(*portnode, type, entry.type(), entry.seq(type));
>>>>>>> upstream/master
				}
			}
		}
	}
}


//-------------------------------------------------
//  save_game_inputs - add nodes for any game
//  mappings that have changed
//-------------------------------------------------

<<<<<<< HEAD
void ioport_manager::save_game_inputs(xml_data_node *parentnode)
{
	// iterate over ports
	for (ioport_port *port = first_port(); port != NULL; port = port->next())
		for (ioport_field *field = port->first_field(); field != NULL; field = field->next())
			if (save_this_input_field_type(field->type()))
=======
void ioport_manager::save_game_inputs(util::xml::data_node &parentnode)
{
	// iterate over ports
	for (auto &port : m_portlist)
		for (ioport_field &field : port.second->fields())
			if (save_this_input_field_type(field.type()))
>>>>>>> upstream/master
			{
				// determine if we changed
				bool changed = false;
				for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
<<<<<<< HEAD
					changed |= (field->seq(seqtype) != field->defseq(seqtype));

				// non-analog changes
				if (!field->is_analog())
				{
					changed |= ((field->live().value & field->mask()) != (field->defvalue() & field->mask()));
					changed |= (field->live().toggle != field->toggle());
#ifdef USE_AUTOFIRE
					changed |= (field->live().autofire != 0);
#endif /* USE_AUTOFIRE */
#ifdef USE_CUSTOM_BUTTON
					changed |= field->type() >= IPT_CUSTOM1 && field->type() < IPT_CUSTOM1 + MAX_CUSTOM_BUTTONS &&
						m_custom_button[field->player()][field->type() - IPT_CUSTOM1];
#endif /* USE_CUSTOM_BUTTON */
=======
					changed |= (field.seq(seqtype) != field.defseq(seqtype));

				// non-analog changes
				if (!field.is_analog())
				{
					changed |= ((field.live().value & field.mask()) != (field.defvalue() & field.mask()));
					changed |= (field.live().toggle != field.toggle());
>>>>>>> upstream/master
				}

				// analog changes
				else
				{
<<<<<<< HEAD
					changed |= (field->live().analog->m_delta != field->delta());
					changed |= (field->live().analog->m_centerdelta != field->centerdelta());
					changed |= (field->live().analog->m_sensitivity != field->sensitivity());
					changed |= (field->live().analog->m_reverse != field->analog_reverse());
=======
					changed |= (field.live().analog->m_delta != field.delta());
					changed |= (field.live().analog->m_centerdelta != field.centerdelta());
					changed |= (field.live().analog->m_sensitivity != field.sensitivity());
					changed |= (field.live().analog->m_reverse != field.analog_reverse());
>>>>>>> upstream/master
				}

				// if we did change, add a new node
				if (changed)
				{
					// add a new port node
<<<<<<< HEAD
					xml_data_node *portnode = xml_add_child(parentnode, "port", NULL);
					if (portnode != NULL)
					{
						// add the identifying information and attributes
						std::string tempstr;
						xml_set_attribute(portnode, "tag", port->tag());
						xml_set_attribute(portnode, "type", input_type_to_token(tempstr, field->type(), field->player()));
						xml_set_attribute_int(portnode, "mask", field->mask());
						xml_set_attribute_int(portnode, "defvalue", field->defvalue() & field->mask());

						// add sequences if changed
						for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
							if (field->seq(seqtype) != field->defseq(seqtype))
								save_sequence(portnode, seqtype, field->type(), field->seq(seqtype));

						// write out non-analog changes
						if (!field->is_analog())
						{
							if ((field->live().value & field->mask()) != (field->defvalue() & field->mask()))
								xml_set_attribute_int(portnode, "value", field->live().value & field->mask());
							if (field->live().toggle != field->toggle())
								xml_set_attribute(portnode, "toggle", field->live().toggle ? "yes" : "no");

#ifdef USE_AUTOFIRE
							if (field->live().autofire & AUTOFIRE_ON)
								xml_set_attribute(portnode, "autofire", "on");
							else if (field->live().autofire & AUTOFIRE_TOGGLE)
								xml_set_attribute(portnode, "autofire", "toggle");
#endif /* USE_AUTOFIRE */

#ifdef USE_CUSTOM_BUTTON
							if (field->type() >= IPT_CUSTOM1 && field->type() < IPT_CUSTOM1 + MAX_CUSTOM_BUTTONS &&
							    m_custom_button[field->player()][field->type() - IPT_CUSTOM1])
								xml_set_attribute_int(portnode, "custom", m_custom_button[field->player()][field->type() - IPT_CUSTOM1]);
#endif /* USE_CUSTOM_BUTTON */
=======
					util::xml::data_node *const portnode = parentnode.add_child("port", nullptr);
					if (portnode != nullptr)
					{
						// add the identifying information and attributes
						portnode->set_attribute("tag", port.second->tag());
						portnode->set_attribute("type", input_type_to_token(field.type(), field.player()).c_str());
						portnode->set_attribute_int("mask", field.mask());
						portnode->set_attribute_int("defvalue", field.defvalue() & field.mask());

						// add sequences if changed
						for (input_seq_type seqtype = SEQ_TYPE_STANDARD; seqtype < SEQ_TYPE_TOTAL; ++seqtype)
							if (field.seq(seqtype) != field.defseq(seqtype))
								save_sequence(*portnode, seqtype, field.type(), field.seq(seqtype));

						// write out non-analog changes
						if (!field.is_analog())
						{
							if ((field.live().value & field.mask()) != (field.defvalue() & field.mask()))
								portnode->set_attribute_int("value", field.live().value & field.mask());
							if (field.live().toggle != field.toggle())
								portnode->set_attribute("toggle", field.live().toggle ? "yes" : "no");
>>>>>>> upstream/master
						}

						// write out analog changes
						else
						{
<<<<<<< HEAD
							if (field->live().analog->m_delta != field->delta())
								xml_set_attribute_int(portnode, "keydelta", field->live().analog->m_delta);
							if (field->live().analog->m_centerdelta != field->centerdelta())
								xml_set_attribute_int(portnode, "centerdelta", field->live().analog->m_centerdelta);
							if (field->live().analog->m_sensitivity != field->sensitivity())
								xml_set_attribute_int(portnode, "sensitivity", field->live().analog->m_sensitivity);
							if (field->live().analog->m_reverse != field->analog_reverse())
								xml_set_attribute(portnode, "reverse", field->live().analog->m_reverse ? "yes" : "no");
=======
							if (field.live().analog->m_delta != field.delta())
								portnode->set_attribute_int("keydelta", field.live().analog->m_delta);
							if (field.live().analog->m_centerdelta != field.centerdelta())
								portnode->set_attribute_int("centerdelta", field.live().analog->m_centerdelta);
							if (field.live().analog->m_sensitivity != field.sensitivity())
								portnode->set_attribute_int("sensitivity", field.live().analog->m_sensitivity);
							if (field.live().analog->m_reverse != field.analog_reverse())
								portnode->set_attribute("reverse", field.live().analog->m_reverse ? "yes" : "no");
>>>>>>> upstream/master
						}
					}
				}
			}
<<<<<<< HEAD

#ifdef USE_AUTOFIRE
	for (int portnum = 0; portnum < MAX_PLAYERS; portnum++)
	{
		if (m_autofiredelay[portnum] != 3)
		{
			xml_data_node *childnode = xml_add_child(parentnode, "autofire", NULL);
			if (childnode)
			{
				xml_set_attribute_int(childnode, "player", portnum + 1);
				xml_set_attribute_int(childnode, "delay", m_autofiredelay[portnum]);
			}
		}
	}
#endif /* USE_AUTOFIRE */
=======
>>>>>>> upstream/master
}



//**************************************************************************
//  INPUT PLAYBACK
//**************************************************************************

//-------------------------------------------------
//  playback_read - read a value from the playback
//  file
//-------------------------------------------------

template<typename _Type>
_Type ioport_manager::playback_read(_Type &result)
{
<<<<<<< HEAD
	// protect against NULL handles if previous reads fail
=======
	// protect against nullptr handles if previous reads fail
>>>>>>> upstream/master
	if (!m_playback_file.is_open())
		result = 0;

	// read the value; if we fail, end playback
	else if (m_playback_file.read(&result, sizeof(result)) != sizeof(result))
	{
		playback_end("End of file");
		result = 0;
	}

	// return the appropriate value
	else if (sizeof(result) == 8)
<<<<<<< HEAD
		result = LITTLE_ENDIANIZE_INT64(result);
	else if (sizeof(result) == 4)
		result = LITTLE_ENDIANIZE_INT32(result);
	else if (sizeof(result) == 2)
		result = LITTLE_ENDIANIZE_INT16(result);
=======
		result = little_endianize_int64(result);
	else if (sizeof(result) == 4)
		result = little_endianize_int32(result);
	else if (sizeof(result) == 2)
		result = little_endianize_int16(result);
>>>>>>> upstream/master
	return result;
}

template<>
bool ioport_manager::playback_read<bool>(bool &result)
{
<<<<<<< HEAD
	UINT8 temp;
=======
	u8 temp;
>>>>>>> upstream/master
	playback_read(temp);
	return result = bool(temp);
}


//-------------------------------------------------
//  playback_init - initialize INP playback
//-------------------------------------------------

time_t ioport_manager::playback_init()
{
<<<<<<< HEAD
#ifdef INP_CAPTION
	m_next_caption_frame = -1;
	m_caption_timer = 0;
#endif /* INP_CAPTION */

=======
>>>>>>> upstream/master
	// if no file, nothing to do
	const char *filename = machine().options().playback();
	if (filename[0] == 0)
		return 0;

	// open the playback file
<<<<<<< HEAD
	file_error filerr = m_playback_file.open(filename);
	assert_always(filerr == FILERR_NONE, "Failed to open file for playback");

	// read the header and verify that it is a modern version; if not, print an error
	UINT8 header[INP_HEADER_SIZE];
	if (m_playback_file.read(header, sizeof(header)) != sizeof(header))
		fatalerror(_("Input file is corrupt or invalid (missing header)\n"));
	if (memcmp(header, "MAMEINP\0", 8) != 0)
		fatalerror(_("Input file invalid or in an older, unsupported format\n"));
	if (header[0x10] != INP_HEADER_MAJVERSION)
		fatalerror(_("Input file format version mismatch\n"));

#ifdef INP_CAPTION
	if (strlen(filename) > 4)
	{
		char *fname = core_strdup(filename);

		if (fname)
		{
			strcpy(fname + strlen(fname) - 4, ".cap");
			filerr = m_caption_file.open(fname);
			osd_free(fname);
		}
	}
#endif /* INP_CAPTION */

	// output info to console
	osd_printf_info("Input file: %s\n", filename);
	osd_printf_info("INP version %d.%d\n", header[0x10], header[0x11]);
	time_t basetime = header[0x08] | (header[0x09] << 8) | (header[0x0a] << 16) | (header[0x0b] << 24) |
						((UINT64)header[0x0c] << 32) | ((UINT64)header[0x0d] << 40) | ((UINT64)header[0x0e] << 48) | ((UINT64)header[0x0f] << 56);
	osd_printf_info("Created %s\n", ctime(&basetime));
	osd_printf_info("Recorded using %s\n", header + 0x20);

	// verify the header against the current game
	if (memcmp(machine().system().name, header + 0x14, strlen(machine().system().name) + 1) != 0)
		osd_printf_info("Input file is for %s '%s', not for current %s '%s'\n", emulator_info::get_gamenoun(), header + 0x14, emulator_info::get_gamenoun(), machine().system().name);
=======
	osd_file::error filerr = m_playback_file.open(filename);

	// return an explicit error if file isn't found in given path
	if(filerr == osd_file::error::NOT_FOUND)
		fatalerror("Input file %s not found\n",filename);

	// TODO: bail out any other error laconically for now
	if(filerr != osd_file::error::NONE)
		fatalerror("Failed to open file %s for playback (code error=%d)\n",filename,int(filerr));

	// read the header and verify that it is a modern version; if not, print an error
	inp_header header;
	if (!header.read(m_playback_file))
		fatalerror("Input file is corrupt or invalid (missing header)\n");
	if (!header.check_magic())
		fatalerror("Input file invalid or in an older, unsupported format\n");
	if (header.get_majversion() != inp_header::MAJVERSION)
		fatalerror("Input file format version mismatch\n");

	// output info to console
	osd_printf_info("Input file: %s\n", filename);
	osd_printf_info("INP version %u.%u\n", header.get_majversion(), header.get_minversion());
	time_t basetime = header.get_basetime();
	osd_printf_info("Created %s\n", ctime(&basetime));
	osd_printf_info("Recorded using %s\n", header.get_appdesc().c_str());

	// verify the header against the current game
	std::string const sysname = header.get_sysname();
	if (sysname != machine().system().name)
		osd_printf_info("Input file is for machine '%s', not for current machine '%s'\n", sysname.c_str(), machine().system().name);
>>>>>>> upstream/master

	// enable compression
	m_playback_file.compress(FCOMPRESS_MEDIUM);
	return basetime;
}


//-------------------------------------------------
//  playback_end - end INP playback
//-------------------------------------------------

void ioport_manager::playback_end(const char *message)
{
	// only applies if we have a live file
	if (m_playback_file.is_open())
	{
		// close the file
		m_playback_file.close();

<<<<<<< HEAD
#ifdef INP_CAPTION
		if (m_caption_file.is_open())
		{
			// close the file
			m_caption_file.close();
		}
#endif /* INP_CAPTION */

		// pop a message
		if (message != NULL)
			machine().popmessage("Playback Ended\nReason: %s", message);

#ifdef PLAYBACK_END_PAUSE
		if (machine().options().bool_value(OPTION_PLAYBACK_END_PAUSE))
			machine().pause();
#endif /* PLAYBACK_END_PAUSE */

		// display speed stats
		m_playback_accumulated_speed /= m_playback_accumulated_frames;
		osd_printf_info("Total playback frames: %d\n", UINT32(m_playback_accumulated_frames));
		osd_printf_info("Average recorded speed: %d%%\n", UINT32((m_playback_accumulated_speed * 200 + 1) >> 21));
=======
		// pop a message
		if (message != nullptr)
			machine().popmessage("Playback Ended\nReason: %s", message);

		// display speed stats
		if (m_playback_accumulated_speed > 0)
			m_playback_accumulated_speed /= m_playback_accumulated_frames;
		osd_printf_info("Total playback frames: %d\n", u32(m_playback_accumulated_frames));
		osd_printf_info("Average recorded speed: %d%%\n", u32((m_playback_accumulated_speed * 200 + 1) >> 21));

		// close the program at the end of inp file playback
		if (machine().options().exit_after_playback()) {
			osd_printf_info("Exiting MAME now...\n");
			machine().schedule_exit();
		}
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  playback_frame - start of frame callback for
//  playback
//-------------------------------------------------

void ioport_manager::playback_frame(const attotime &curtime)
{
	// if playing back, fetch the information and verify
	if (m_playback_file.is_open())
	{
		// first the absolute time
		seconds_t seconds_temp;
		attoseconds_t attoseconds_temp;
		playback_read(seconds_temp);
		playback_read(attoseconds_temp);
		attotime readtime(seconds_temp, attoseconds_temp);
		if (readtime != curtime)
			playback_end("Out of sync");

		// then the speed
<<<<<<< HEAD
		UINT32 curspeed;
=======
		u32 curspeed;
>>>>>>> upstream/master
		m_playback_accumulated_speed += playback_read(curspeed);
		m_playback_accumulated_frames++;
	}
}


//-------------------------------------------------
//  playback_port - per-port callback for playback
//-------------------------------------------------

void ioport_manager::playback_port(ioport_port &port)
{
	// if playing back, fetch information about this port
	if (m_playback_file.is_open())
	{
		// read the default value and the digital state
		playback_read(port.live().defvalue);
		playback_read(port.live().digital);

		// loop over analog ports and save their data
<<<<<<< HEAD
		for (analog_field *analog = port.live().analoglist.first(); analog != NULL; analog = analog->next())
		{
			// read current and previous values
			playback_read(analog->m_accum);
			playback_read(analog->m_previous);

			// read configuration information
			playback_read(analog->m_sensitivity);
			playback_read(analog->m_reverse);
=======
		for (analog_field &analog : port.live().analoglist)
		{
			// read current and previous values
			playback_read(analog.m_accum);
			playback_read(analog.m_previous);

			// read configuration information
			playback_read(analog.m_sensitivity);
			playback_read(analog.m_reverse);
>>>>>>> upstream/master
		}
	}
}


//-------------------------------------------------
//  record_write - write a value to the record file
//-------------------------------------------------

template<typename _Type>
void ioport_manager::record_write(_Type value)
{
<<<<<<< HEAD
	// protect against NULL handles if previous reads fail
=======
	// protect against nullptr handles if previous reads fail
>>>>>>> upstream/master
	if (!m_record_file.is_open())
		return;

	// read the value; if we fail, end playback
	if (m_record_file.write(&value, sizeof(value)) != sizeof(value))
		record_end("Out of space");
}

template<>
void ioport_manager::record_write<bool>(bool value)
{
<<<<<<< HEAD
	UINT8 byte = UINT8(value);
	record_write(byte);
}

=======
	u8 byte = u8(value);
	record_write(byte);
}

template<typename _Type>
void ioport_manager::timecode_write(_Type value)
{
	// protect against nullptr handles if previous reads fail
	if (!m_timecode_file.is_open())
		return;

	// read the value; if we fail, end playback
	if (m_timecode_file.write(&value, sizeof(value)) != sizeof(value))
		timecode_end("Out of space");
}

/*template<>
void ioport_manager::timecode_write<bool>(bool value)
{
    u8 byte = u8(value);
    timecode_write(byte);
}*/
template<>
void ioport_manager::timecode_write<std::string>(std::string value) {
	timecode_write(value.c_str());
}

>>>>>>> upstream/master

//-------------------------------------------------
//  record_init - initialize INP recording
//-------------------------------------------------

void ioport_manager::record_init()
{
	// if no file, nothing to do
	const char *filename = machine().options().record();
	if (filename[0] == 0)
		return;

	// open the record file
<<<<<<< HEAD
	file_error filerr = m_record_file.open(filename);
	assert_always(filerr == FILERR_NONE, "Failed to open file for recording");
=======
	osd_file::error filerr = m_record_file.open(filename);
	assert_always(filerr == osd_file::error::NONE, "Failed to open file for recording");
>>>>>>> upstream/master

	// get the base time
	system_time systime;
	machine().base_datetime(systime);

	// fill in the header
<<<<<<< HEAD
	UINT8 header[INP_HEADER_SIZE] = { 0 };
	memcpy(header, "MAMEINP\0", 8);
	header[0x08] = systime.time >> 0;
	header[0x09] = systime.time >> 8;
	header[0x0a] = systime.time >> 16;
	header[0x0b] = systime.time >> 24;
	header[0x0c] = systime.time >> 32;
	header[0x0d] = systime.time >> 40;
	header[0x0e] = systime.time >> 48;
	header[0x0f] = systime.time >> 56;
	header[0x10] = INP_HEADER_MAJVERSION;
	header[0x11] = INP_HEADER_MINVERSION;
	strcpy((char *)header + 0x14, machine().system().name);
	sprintf((char *)header + 0x20, "%s %s", emulator_info::get_appname(), build_version);

	// write it
	m_record_file.write(header, sizeof(header));
=======
	inp_header header;
	header.set_magic();
	header.set_basetime(systime.time);
	header.set_version();
	header.set_sysname(machine().system().name);
	header.set_appdesc(util::string_format("%s %s", emulator_info::get_appname(), emulator_info::get_build_version()));

	// write it
	header.write(m_record_file);
>>>>>>> upstream/master

	// enable compression
	m_record_file.compress(FCOMPRESS_MEDIUM);
}


<<<<<<< HEAD
=======
void ioport_manager::timecode_init() {
	// check if option -record_timecode is enabled
	if (!machine().options().record_timecode()) {
		machine().video().set_timecode_enabled(false);
		return;
	}
	// if no file, nothing to do
	const char *record_filename = machine().options().record();
	if (record_filename[0] == 0) {
		machine().video().set_timecode_enabled(false);
		return;
	}

	machine().video().set_timecode_enabled(true);

	// open the record file
	std::string filename;
	filename.append(record_filename).append(".timecode");
	osd_printf_info("Record input timecode file: %s\n", record_filename);

	osd_file::error filerr = m_timecode_file.open(filename.c_str());
	assert_always(filerr == osd_file::error::NONE, "Failed to open file for input timecode recording");

	m_timecode_file.puts(std::string("# ==========================================\n").c_str());
	m_timecode_file.puts(std::string("# TIMECODE FILE FOR VIDEO PREVIEW GENERATION\n").c_str());
	m_timecode_file.puts(std::string("# ==========================================\n").c_str());
	m_timecode_file.puts(std::string("#\n").c_str());
	m_timecode_file.puts(std::string("# VIDEO_PART:     code of video timecode\n").c_str());
	m_timecode_file.puts(std::string("# START:          start time (hh:mm:ss.mmm)\n").c_str());
	m_timecode_file.puts(std::string("# ELAPSED:        elapsed time (hh:mm:ss.mmm)\n").c_str());
	m_timecode_file.puts(std::string("# MSEC_START:     start time (milliseconds)\n").c_str());
	m_timecode_file.puts(std::string("# MSEC_ELAPSED:   elapsed time (milliseconds)\n").c_str());
	m_timecode_file.puts(std::string("# FRAME_START:    start time (frames)\n").c_str());
	m_timecode_file.puts(std::string("# FRAME_ELAPSED:  elapsed time (frames)\n").c_str());
	m_timecode_file.puts(std::string("#\n").c_str());
	m_timecode_file.puts(std::string("# VIDEO_PART======= START======= ELAPSED===== MSEC_START===== MSEC_ELAPSED=== FRAME_START==== FRAME_ELAPSED==\n").c_str());
}

>>>>>>> upstream/master
//-------------------------------------------------
//  record_end - end INP recording
//-------------------------------------------------

void ioport_manager::record_end(const char *message)
{
	// only applies if we have a live file
	if (m_record_file.is_open())
	{
		// close the file
		m_record_file.close();

		// pop a message
<<<<<<< HEAD
		if (message != NULL)
=======
		if (message != nullptr)
>>>>>>> upstream/master
			machine().popmessage("Recording Ended\nReason: %s", message);
	}
}


<<<<<<< HEAD
=======
void ioport_manager::timecode_end(const char *message)
{
	// only applies if we have a live file
	if (m_timecode_file.is_open()) {
		// close the file
		m_timecode_file.close();

		// pop a message
		if (message != nullptr)
			machine().popmessage("Recording Timecode Ended\nReason: %s", message);
	}
}

>>>>>>> upstream/master
//-------------------------------------------------
//  record_frame - start of frame callback for
//  recording
//-------------------------------------------------

void ioport_manager::record_frame(const attotime &curtime)
{
	// if recording, record information about the current frame
	if (m_record_file.is_open())
	{
		// first the absolute time
		record_write(curtime.seconds());
		record_write(curtime.attoseconds());

		// then the current speed
<<<<<<< HEAD
		record_write(UINT32(machine().video().speed_percent() * double(1 << 20)));
=======
		record_write(u32(machine().video().speed_percent() * double(1 << 20)));
	}

	if (m_timecode_file.is_open() && machine().video().get_timecode_write())
	{
		// Display the timecode
		m_timecode_count++;
		std::string const current_time_str = string_format("%02d:%02d:%02d.%03d",
				(int)curtime.seconds() / (60 * 60),
				(curtime.seconds() / 60) % 60,
				curtime.seconds() % 60,
				(int)(curtime.attoseconds()/ATTOSECONDS_PER_MILLISECOND));

		// Elapsed from previous timecode
		attotime const elapsed_time = curtime - m_timecode_last_time;
		m_timecode_last_time = curtime;
		std::string const elapsed_time_str = string_format("%02d:%02d:%02d.%03d",
				elapsed_time.seconds() / (60 * 60),
				(elapsed_time.seconds() / 60) % 60,
				elapsed_time.seconds() % 60,
				int(elapsed_time.attoseconds()/ATTOSECONDS_PER_MILLISECOND));

		// Number of ms from beginning of playback
		int const mseconds_start = curtime.seconds()*1000 + curtime.attoseconds()/ATTOSECONDS_PER_MILLISECOND;
		std::string const mseconds_start_str = string_format("%015d", mseconds_start);

		// Number of ms from previous timecode
		int mseconds_elapsed = elapsed_time.seconds()*1000 + elapsed_time.attoseconds()/ATTOSECONDS_PER_MILLISECOND;
		std::string const mseconds_elapsed_str = string_format("%015d", mseconds_elapsed);

		// Number of frames from beginning of playback
		int const frame_start = mseconds_start * 60 / 1000;
		std::string const frame_start_str = string_format("%015d", frame_start);

		// Number of frames from previous timecode
		int frame_elapsed = mseconds_elapsed * 60 / 1000;
		std::string const frame_elapsed_str = string_format("%015d", frame_elapsed);

		std::string message;
		std::string timecode_text;
		std::string timecode_key;
		bool show_timecode_counter = false;
		if (m_timecode_count==1) {
			message = string_format("TIMECODE: Intro started at %s", current_time_str);
			timecode_key = "INTRO_START";
			timecode_text = "INTRO";
			show_timecode_counter = true;
		}
		else if (m_timecode_count==2) {
			machine().video().add_to_total_time(elapsed_time);
			message = string_format("TIMECODE: Intro duration %s", elapsed_time_str);
			timecode_key = "INTRO_STOP";
			//timecode_text = "INTRO";
		}
		else if (m_timecode_count==3) {
			message = string_format("TIMECODE: Gameplay started at %s", current_time_str);
			timecode_key = "GAMEPLAY_START";
			timecode_text = "GAMEPLAY";
			show_timecode_counter = true;
		}
		else if (m_timecode_count==4) {
			machine().video().add_to_total_time(elapsed_time);
			message = string_format("TIMECODE: Gameplay duration %s", elapsed_time_str);
			timecode_key = "GAMEPLAY_STOP";
			//timecode_text = "GAMEPLAY";
		}
		else if (m_timecode_count % 2 == 1) {
			message = string_format("TIMECODE: Extra %d started at %s", (m_timecode_count-3)/2, current_time_str);
			timecode_key = string_format("EXTRA_START_%03d", (m_timecode_count-3)/2);
			timecode_text = string_format("EXTRA %d", (m_timecode_count-3)/2);
			show_timecode_counter = true;
		}
		else {
			machine().video().add_to_total_time(elapsed_time);
			message = string_format("TIMECODE: Extra %d duration %s", (m_timecode_count-4)/2, elapsed_time_str);
			timecode_key = string_format("EXTRA_STOP_%03d", (m_timecode_count-4)/2);
		}

		osd_printf_info("%s \n", message.c_str());
		machine().popmessage("%s \n", message.c_str());

		m_timecode_file.printf(
				"%-19s %s %s %s %s %s %s\n",
				timecode_key.c_str(),
				current_time_str.c_str(), elapsed_time_str.c_str(),
				mseconds_start_str.c_str(), mseconds_elapsed_str.c_str(),
				frame_start_str.c_str(), frame_elapsed_str.c_str());

		machine().video().set_timecode_write(false);
		machine().video().set_timecode_text(timecode_text);
		machine().video().set_timecode_start(m_timecode_last_time);
		machine().ui().set_show_timecode_counter(show_timecode_counter);
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  record_port - per-port callback for record
//-------------------------------------------------

void ioport_manager::record_port(ioport_port &port)
{
	// if recording, store information about this port
	if (m_record_file.is_open())
	{
		// store the default value and digital state
		record_write(port.live().defvalue);
		record_write(port.live().digital);

		// loop over analog ports and save their data
<<<<<<< HEAD
		for (analog_field *analog = port.live().analoglist.first(); analog != NULL; analog = analog->next())
		{
			// store current and previous values
			record_write(analog->m_accum);
			record_write(analog->m_previous);

			// store configuration information
			record_write(analog->m_sensitivity);
			record_write(analog->m_reverse);
=======
		for (analog_field &analog : port.live().analoglist)
		{
			// store current and previous values
			record_write(analog.m_accum);
			record_write(analog.m_previous);

			// store configuration information
			record_write(analog.m_sensitivity);
			record_write(analog.m_reverse);
>>>>>>> upstream/master
		}
	}
}



//**************************************************************************
//  I/O PORT CONFIGURER
//**************************************************************************

//-------------------------------------------------
//  ioport_configurer - constructor
//-------------------------------------------------

ioport_configurer::ioport_configurer(device_t &owner, ioport_list &portlist, std::string &errorbuf)
	: m_owner(owner),
		m_portlist(portlist),
		m_errorbuf(errorbuf),
<<<<<<< HEAD
		m_curport(NULL),
		m_curfield(NULL),
		m_cursetting(NULL)
=======
		m_curport(nullptr),
		m_curfield(nullptr),
		m_cursetting(nullptr)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  string_from_token - convert an
//  ioport_token to a default string
//-------------------------------------------------

const char *ioport_configurer::string_from_token(const char *string)
{
	// 0 is an invalid index
<<<<<<< HEAD
	if (string == NULL)
		return NULL;

	// if the index is greater than the count, assume it to be a pointer
	if (FPTR(string) >= INPUT_STRING_COUNT)
		return string;

#if FALSE // Set TRUE, If you want to take care missing-token or wrong-sorting
=======
	if (string == nullptr)
		return nullptr;

	// if the index is greater than the count, assume it to be a pointer
	if (uintptr_t(string) >= INPUT_STRING_COUNT)
		return string;

#if false // Set true, If you want to take care missing-token or wrong-sorting
>>>>>>> upstream/master

	// otherwise, scan the list for a matching string and return it
	{
	int index;
	for (index = 0; index < ARRAY_LENGTH(input_port_default_strings); index++)
<<<<<<< HEAD
		if (input_port_default_strings[index].id == FPTR(string))
=======
		if (input_port_default_strings[index].id == uintptr_t(string))
>>>>>>> upstream/master
			return input_port_default_strings[index].string;
	}
	return "(Unknown Default)";

#else

<<<<<<< HEAD
	return input_port_default_strings[FPTR(string)-1].string;
=======
	return input_port_default_strings[uintptr_t(string)-1].string;
>>>>>>> upstream/master

#endif
}


//-------------------------------------------------
//  port_alloc - allocate a new port
//-------------------------------------------------

<<<<<<< HEAD
void ioport_configurer::port_alloc(const char *tag)
=======
ioport_configurer& ioport_configurer::port_alloc(const char *tag)
>>>>>>> upstream/master
{
	// create the full tag
	std::string fulltag = m_owner.subtag(tag);

	// add it to the list, and reset current field/setting
<<<<<<< HEAD
	m_curport = &m_portlist.append(fulltag.c_str(), *global_alloc(ioport_port(m_owner, fulltag.c_str())));
	m_curfield = NULL;
	m_cursetting = NULL;
=======
	if (m_portlist.count(fulltag) != 0) throw tag_add_exception(fulltag.c_str());
	m_portlist.emplace(std::make_pair(fulltag, std::make_unique<ioport_port>(m_owner, fulltag.c_str())));
	m_curport = m_portlist.find(fulltag)->second.get();
	m_curfield = nullptr;
	m_cursetting = nullptr;
	return *this;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  port_modify - find an existing port and
//  modify it
//-------------------------------------------------

<<<<<<< HEAD
void ioport_configurer::port_modify(const char *tag)
=======
ioport_configurer& ioport_configurer::port_modify(const char *tag)
>>>>>>> upstream/master
{
	// create the full tag
	std::string fulltag = m_owner.subtag(tag);

	// find the existing port
<<<<<<< HEAD
	m_curport = m_portlist.find(fulltag.c_str());
	if (m_curport == NULL)
=======
	m_curport = m_portlist.find(fulltag.c_str())->second.get();
	if (m_curport == nullptr)
>>>>>>> upstream/master
		throw emu_fatalerror("Requested to modify nonexistent port '%s'", fulltag.c_str());

	// bump the modification count, and reset current field/setting
	m_curport->m_modcount++;
<<<<<<< HEAD
	m_curfield = NULL;
	m_cursetting = NULL;
=======
	m_curfield = nullptr;
	m_cursetting = nullptr;
	return *this;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  field_alloc - allocate a new field
//-------------------------------------------------

<<<<<<< HEAD
void ioport_configurer::field_alloc(ioport_type type, ioport_value defval, ioport_value mask, const char *name)
{
	// make sure we have a port
	if (m_curport == NULL)
=======
ioport_configurer& ioport_configurer::field_alloc(ioport_type type, ioport_value defval, ioport_value mask, const char *name)
{
	// make sure we have a port
	if (m_curport == nullptr)
>>>>>>> upstream/master
		throw emu_fatalerror("alloc_field called with no active port (mask=%X defval=%X)\n", mask, defval);
	// append the field
	if (type != IPT_UNKNOWN && type != IPT_UNUSED)
		m_curport->m_active |= mask;
	m_curfield = &m_curport->m_fieldlist.append(*global_alloc(ioport_field(*m_curport, type, defval, mask, string_from_token(name))));

	// reset the current setting
<<<<<<< HEAD
	m_cursetting = NULL;
=======
	m_cursetting = nullptr;
	return *this;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  field_add_char - add a character to a field
//-------------------------------------------------

<<<<<<< HEAD
void ioport_configurer::field_add_char(unicode_char ch)
=======
ioport_configurer& ioport_configurer::field_add_char(char32_t ch)
>>>>>>> upstream/master
{
	for (int index = 0; index < ARRAY_LENGTH(m_curfield->m_chars); index++)
		if (m_curfield->m_chars[index] == 0)
		{
			m_curfield->m_chars[index] = ch;
<<<<<<< HEAD
			return;
=======
			return *this;
>>>>>>> upstream/master
		}

	throw emu_fatalerror("PORT_CHAR(%d) could not be added - maximum amount exceeded\n", ch);
}


//-------------------------------------------------
//  field_add_code - add a character to a field
//-------------------------------------------------

<<<<<<< HEAD
void ioport_configurer::field_add_code(input_seq_type which, input_code code)
{
	m_curfield->m_seq[which] |= code;
=======
ioport_configurer& ioport_configurer::field_add_code(input_seq_type which, input_code code)
{
	m_curfield->m_seq[which] |= code;
	return *this;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  setting_alloc - allocate a new setting
//-------------------------------------------------

<<<<<<< HEAD
void ioport_configurer::setting_alloc(ioport_value value, const char *name)
{
	// make sure we have a field
	if (m_curfield == NULL)
=======
ioport_configurer& ioport_configurer::setting_alloc(ioport_value value, const char *name)
{
	// make sure we have a field
	if (m_curfield == nullptr)
>>>>>>> upstream/master
		throw emu_fatalerror("alloc_setting called with no active field (value=%X name=%s)\n", value, name);

	m_cursetting = global_alloc(ioport_setting(*m_curfield, value & m_curfield->mask(), string_from_token(name)));
	// append a new setting
	m_curfield->m_settinglist.append(*m_cursetting);
<<<<<<< HEAD
=======
	return *this;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  set_condition - set the condition for either
//  the current setting or field
//-------------------------------------------------

<<<<<<< HEAD
void ioport_configurer::set_condition(ioport_condition::condition_t condition, const char *tag, ioport_value mask, ioport_value value)
{
	ioport_condition &target = (m_cursetting != NULL) ? m_cursetting->condition() : m_curfield->condition();
	target.set(condition, tag, mask, value);
=======
ioport_configurer& ioport_configurer::set_condition(ioport_condition::condition_t condition, const char *tag, ioport_value mask, ioport_value value)
{
	ioport_condition &target = (m_cursetting != nullptr) ? m_cursetting->condition() : m_curfield->condition();
	target.set(condition, tag, mask, value);
	return *this;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  onoff_alloc - allocate an on/off DIP switch
//-------------------------------------------------

<<<<<<< HEAD
void ioport_configurer::onoff_alloc(const char *name, ioport_value defval, ioport_value mask, const char *diplocation)
=======
ioport_configurer& ioport_configurer::onoff_alloc(const char *name, ioport_value defval, ioport_value mask, const char *diplocation)
>>>>>>> upstream/master
{
	// allocate a field normally
	field_alloc(IPT_DIPSWITCH, defval, mask, name);

<<<<<<< HEAD
	// special case service mode
	if (name == DEF_STR(Service_Mode))
	{
		field_set_toggle();
		m_curfield->m_seq[SEQ_TYPE_STANDARD].set(KEYCODE_F2);
	}

	// expand the diplocation
	if (diplocation != NULL)
=======
	// expand the diplocation
	if (diplocation != nullptr)
>>>>>>> upstream/master
		field_set_diplocation(diplocation);

	// allocate settings
	setting_alloc(defval & mask, DEF_STR(Off));
	setting_alloc(~defval & mask, DEF_STR(On));
	// clear cursettings set by setting_alloc
<<<<<<< HEAD
	m_cursetting = NULL;
=======
	m_cursetting = nullptr;
	return *this;
>>>>>>> upstream/master
}



/***************************************************************************
    MISCELLANEOUS
***************************************************************************/

//-------------------------------------------------
<<<<<<< HEAD
//  find - look up information about a particular
//  character
//-------------------------------------------------

const char_info *char_info::find(unicode_char target)
{
	// perform a simple binary search to find the proper alternate
	int low = 0;
	int high = ARRAY_LENGTH(charinfo);
	while (high > low)
	{
		int middle = (high + low) / 2;
		unicode_char ch = charinfo[middle].ch;
		if (ch < target)
			low = middle + 1;
		else if (ch > target)
			high = middle;
		else
			return &charinfo[middle];
	}
	return NULL;
}


//-------------------------------------------------
=======
>>>>>>> upstream/master
//  dynamic_field - constructor
//-------------------------------------------------

dynamic_field::dynamic_field(ioport_field &field)
<<<<<<< HEAD
	: m_next(NULL),
=======
	: m_next(nullptr),
>>>>>>> upstream/master
		m_field(field),
		m_shift(0),
		m_oldval(field.defvalue())
{
	// fill in the data
	for (ioport_value mask = field.mask(); !(mask & 1); mask >>= 1)
		m_shift++;
	m_oldval >>= m_shift;
}


//-------------------------------------------------
//  read - read the updated value and merge it
//  into the target
//-------------------------------------------------

void dynamic_field::read(ioport_value &result)
{
	// skip if not enabled
	if (!m_field.enabled())
		return;

	// call the callback to read a new value
	ioport_value newval = m_field.m_read(m_field, m_field.m_read_param);
	m_oldval = newval;

	// merge in the bits (don't invert yet, as all digitals are inverted together)
	result = (result & ~m_field.mask()) | ((newval << m_shift) & m_field.mask());
}


//-------------------------------------------------
//  write - track a change to a value and call
//  the write callback if there's something new
//-------------------------------------------------

void dynamic_field::write(ioport_value newval)
{
	// skip if not enabled
	if (!m_field.enabled())
		return;

	// if the bits have changed, call the handler
	newval = (newval & m_field.mask()) >> m_shift;
	if (m_oldval != newval)
	{
		m_field.m_write(m_field, m_field.m_write_param, m_oldval, newval);
		m_oldval = newval;
	}
}


//-------------------------------------------------
//  analog_field - constructor
//-------------------------------------------------

analog_field::analog_field(ioport_field &field)
<<<<<<< HEAD
	: m_next(NULL),
=======
	: m_next(nullptr),
>>>>>>> upstream/master
		m_field(field),
		m_shift(0),
		m_adjdefvalue(field.defvalue() & field.mask()),
		m_adjmin(field.minval() & field.mask()),
		m_adjmax(field.maxval() & field.mask()),
		m_sensitivity(field.sensitivity()),
		m_reverse(field.analog_reverse()),
		m_delta(field.delta()),
		m_centerdelta(field.centerdelta()),
		m_accum(0),
		m_previous(0),
		m_previousanalog(0),
		m_minimum(INPUT_ABSOLUTE_MIN),
		m_maximum(INPUT_ABSOLUTE_MAX),
		m_center(0),
		m_reverse_val(0),
		m_scalepos(0),
		m_scaleneg(0),
		m_keyscalepos(0),
		m_keyscaleneg(0),
		m_positionalscale(0),
		m_absolute(false),
		m_wraps(false),
		m_autocenter(false),
		m_single_scale(false),
		m_interpolate(false),
		m_lastdigital(false)
{
	// compute the shift amount and number of bits
	for (ioport_value mask = field.mask(); !(mask & 1); mask >>= 1)
		m_shift++;

	// initialize core data
	m_adjdefvalue >>= m_shift;
	m_adjmin >>= m_shift;
	m_adjmax >>= m_shift;

	// set basic parameters based on the configured type
	switch (field.type())
	{
		// paddles and analog joysticks are absolute and autocenter
		case IPT_AD_STICK_X:
		case IPT_AD_STICK_Y:
		case IPT_AD_STICK_Z:
		case IPT_PADDLE:
		case IPT_PADDLE_V:
			m_absolute = true;
			m_autocenter = true;
			m_interpolate = !field.analog_reset();
			break;

		// pedals start at and autocenter to the min range
		case IPT_PEDAL:
		case IPT_PEDAL2:
		case IPT_PEDAL3:
			m_center = INPUT_ABSOLUTE_MIN;
			m_accum = apply_inverse_sensitivity(m_center);
			m_absolute = true;
			m_autocenter = true;
			m_interpolate = !field.analog_reset();
			break;

		// lightguns are absolute as well, but don't autocenter and don't interpolate their values
		case IPT_LIGHTGUN_X:
		case IPT_LIGHTGUN_Y:
			m_absolute = true;
			m_autocenter = false;
			m_interpolate = false;
			break;

		// positional devices are absolute, but can also wrap like relative devices
		// set each position to be 512 units
		case IPT_POSITIONAL:
		case IPT_POSITIONAL_V:
			m_positionalscale = compute_scale(field.maxval(), INPUT_ABSOLUTE_MAX - INPUT_ABSOLUTE_MIN);
			m_adjmin = 0;
			m_adjmax = field.maxval() - 1;
			m_wraps = field.analog_wraps();
			m_autocenter = !m_wraps;
			break;

		// dials, mice and trackballs are relative devices
		// these have fixed "min" and "max" values based on how many bits are in the port
		// in addition, we set the wrap around min/max values to 512 * the min/max values
		// this takes into account the mapping that one mouse unit ~= 512 analog units
		case IPT_DIAL:
		case IPT_DIAL_V:
		case IPT_TRACKBALL_X:
		case IPT_TRACKBALL_Y:
		case IPT_MOUSE_X:
		case IPT_MOUSE_Y:
			m_absolute = false;
			m_wraps = true;
			m_interpolate = !field.analog_reset();
			break;

		default:
			fatalerror("Unknown analog port type -- don't know if it is absolute or not\n");
	}

	// further processing for absolute controls
	if (m_absolute)
	{
		// if the default value is pegged at the min or max, use a single scale value for the whole axis
		m_single_scale = (m_adjdefvalue == m_adjmin) || (m_adjdefvalue == m_adjmax);

		// if not "single scale", compute separate scales for each side of the default
		if (!m_single_scale)
		{
			// unsigned
			m_scalepos = compute_scale(m_adjmax - m_adjdefvalue, INPUT_ABSOLUTE_MAX - 0);
			m_scaleneg = compute_scale(m_adjdefvalue - m_adjmin, 0 - INPUT_ABSOLUTE_MIN);

			if (m_adjmin > m_adjmax)
				m_scaleneg = -m_scaleneg;

			// reverse point is at center
			m_reverse_val = 0;
		}
		else
		{
			// single axis that increases from default
			m_scalepos = compute_scale(m_adjmax - m_adjmin, INPUT_ABSOLUTE_MAX - INPUT_ABSOLUTE_MIN);

			// move from default
			if (m_adjdefvalue == m_adjmax)
				m_scalepos = -m_scalepos;

			// make the scaling the same for easier coding when we need to scale
			m_scaleneg = m_scalepos;

			// reverse point is at max
			m_reverse_val = m_maximum;
		}
	}

	// relative and positional controls all map directly with a 512x scale factor
	else
	{
		// The relative code is set up to allow specifing PORT_MINMAX and default values.
		// The validity checks are purposely set up to not allow you to use anything other
		// a default of 0 and PORT_MINMAX(0,mask).  This is in case the need arises to use
		// this feature in the future.  Keeping the code in does not hurt anything.
		if (m_adjmin > m_adjmax)
			// adjust for signed
			m_adjmin = -m_adjmin;

		if (m_wraps)
			m_adjmax++;

		m_minimum = (m_adjmin - m_adjdefvalue) * INPUT_RELATIVE_PER_PIXEL;
		m_maximum = (m_adjmax - m_adjdefvalue) * INPUT_RELATIVE_PER_PIXEL;

		// make the scaling the same for easier coding when we need to scale
		m_scaleneg = m_scalepos = compute_scale(1, INPUT_RELATIVE_PER_PIXEL);

		if (m_field.analog_reset())
			// delta values reverse from center
			m_reverse_val = 0;
		else
		{
			// positional controls reverse from their max range
			m_reverse_val = m_maximum + m_minimum;

			// relative controls reverse from 1 past their max range
			if (m_wraps)
				m_reverse_val -= INPUT_RELATIVE_PER_PIXEL;
		}
	}

	// compute scale for keypresses
	m_keyscalepos = recip_scale(m_scalepos);
	m_keyscaleneg = recip_scale(m_scaleneg);
}


//-------------------------------------------------
//  apply_min_max - clamp the given input value to
//  the appropriate min/max for the analog control
//-------------------------------------------------

<<<<<<< HEAD
inline INT32 analog_field::apply_min_max(INT32 value) const
{
	// take the analog minimum and maximum values and apply the inverse of the
	// sensitivity so that we can clamp against them before applying sensitivity
	INT32 adjmin = apply_inverse_sensitivity(m_minimum);
	INT32 adjmax = apply_inverse_sensitivity(m_maximum);
=======
inline s32 analog_field::apply_min_max(s32 value) const
{
	// take the analog minimum and maximum values and apply the inverse of the
	// sensitivity so that we can clamp against them before applying sensitivity
	s32 adjmin = apply_inverse_sensitivity(m_minimum);
	s32 adjmax = apply_inverse_sensitivity(m_maximum);
>>>>>>> upstream/master

	// for absolute devices, clamp to the bounds absolutely
	if (!m_wraps)
	{
		if (value > adjmax)
			value = adjmax;
		else if (value < adjmin)
			value = adjmin;
	}

	// for relative devices, wrap around when we go past the edge
	else
	{
<<<<<<< HEAD
		INT32 range = adjmax - adjmin;
=======
		s32 range = adjmax - adjmin;
>>>>>>> upstream/master
		// rolls to other end when 1 position past end.
		value = (value - adjmin) % range;
		if (value < 0)
			value += range;
		value += adjmin;
	}

	return value;
}


//-------------------------------------------------
//  apply_sensitivity - apply a sensitivity
//  adjustment for a current value
//-------------------------------------------------

<<<<<<< HEAD
inline INT32 analog_field::apply_sensitivity(INT32 value) const
{
	return INT32((INT64(value) * m_sensitivity) / 100.0 + 0.5);
=======
inline s32 analog_field::apply_sensitivity(s32 value) const
{
	return s32((s64(value) * m_sensitivity) / 100.0 + 0.5);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  apply_inverse_sensitivity - reverse-apply the
//  sensitivity adjustment for a current value
//-------------------------------------------------

<<<<<<< HEAD
inline INT32 analog_field::apply_inverse_sensitivity(INT32 value) const
{
	return INT32((INT64(value) * 100) / m_sensitivity);
=======
inline s32 analog_field::apply_inverse_sensitivity(s32 value) const
{
	return s32((s64(value) * 100) / m_sensitivity);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  apply_settings - return the value of an
//  analog input
//-------------------------------------------------

<<<<<<< HEAD
INT32 analog_field::apply_settings(INT32 value) const
=======
s32 analog_field::apply_settings(s32 value) const
>>>>>>> upstream/master
{
	// apply the min/max and then the sensitivity
	value = apply_min_max(value);
	value = apply_sensitivity(value);

	// apply reversal if needed
	if (m_reverse)
		value = m_reverse_val - value;
	else if (m_single_scale)
		// it's a pedal or the default value is equal to min/max
		// so we need to adjust the center to the minimum
		value -= INPUT_ABSOLUTE_MIN;

	// map differently for positive and negative values
	if (value >= 0)
		value = apply_scale(value, m_scalepos);
	else
		value = apply_scale(value, m_scaleneg);
	value += m_adjdefvalue;

	return value;
}


//-------------------------------------------------
//  frame_update - update the internals of a
//  single analog field periodically
//-------------------------------------------------

void analog_field::frame_update(running_machine &machine)
{
	// clamp the previous value to the min/max range and remember it
	m_previous = m_accum = apply_min_max(m_accum);

	// get the new raw analog value and its type
	input_item_class itemclass;
<<<<<<< HEAD
	INT32 rawvalue = machine.input().seq_axis_value(m_field.seq(SEQ_TYPE_STANDARD), itemclass);
=======
	s32 rawvalue = machine.input().seq_axis_value(m_field.seq(SEQ_TYPE_STANDARD), itemclass);
>>>>>>> upstream/master

	// if we got an absolute input, it overrides everything else
	if (itemclass == ITEM_CLASS_ABSOLUTE)
	{
		if (m_previousanalog != rawvalue)
		{
			// only update if analog value changed
			m_previousanalog = rawvalue;

			// apply the inverse of the sensitivity to the raw value so that
			// it will still cover the full min->max range requested after
			// we apply the sensitivity adjustment
			if (m_absolute || m_field.analog_reset())
			{
				// if port is absolute, then just return the absolute data supplied
				m_accum = apply_inverse_sensitivity(rawvalue);
			}
			else if (m_positionalscale != 0)
			{
				// if port is positional, we will take the full analog control and divide it
				// into positions, that way as the control is moved full scale,
				// it moves through all the positions
				rawvalue = apply_scale(rawvalue - INPUT_ABSOLUTE_MIN, m_positionalscale) * INPUT_RELATIVE_PER_PIXEL + m_minimum;

				// clamp the high value so it does not roll over
<<<<<<< HEAD
				rawvalue = MIN(rawvalue, m_maximum);
=======
				rawvalue = std::min(rawvalue, m_maximum);
>>>>>>> upstream/master
				m_accum = apply_inverse_sensitivity(rawvalue);
			}
			else
				// if port is relative, we use the value to simulate the speed of relative movement
				// sensitivity adjustment is allowed for this mode
				m_accum += rawvalue;

			m_lastdigital = false;
			// do not bother with other control types if the analog data is changing
			return;
		}
		else
		{
			// we still have to update fake relative from joystick control
			if (!m_absolute && m_positionalscale == 0)
				m_accum += rawvalue;
		}
	}

	// if we got it from a relative device, use that as the starting delta
	// also note that the last input was not a digital one
<<<<<<< HEAD
	INT32 delta = 0;
=======
	s32 delta = 0;
>>>>>>> upstream/master
	if (itemclass == ITEM_CLASS_RELATIVE && rawvalue != 0)
	{
		delta = rawvalue;
		m_lastdigital = false;
	}

<<<<<<< HEAD
	INT64 keyscale = (m_accum >= 0) ? m_keyscalepos : m_keyscaleneg;
=======
	s64 keyscale = (m_accum >= 0) ? m_keyscalepos : m_keyscaleneg;
>>>>>>> upstream/master

	// if the decrement code sequence is pressed, add the key delta to
	// the accumulated delta; also note that the last input was a digital one
	bool keypressed = false;
	if (machine.input().seq_pressed(m_field.seq(SEQ_TYPE_DECREMENT)))
	{
		keypressed = true;
		if (m_delta != 0)
			delta -= apply_scale(m_delta, keyscale);
		else if (!m_lastdigital)
			// decrement only once when first pressed
			delta -= apply_scale(1, keyscale);
		m_lastdigital = true;
	}

	// same for the increment code sequence
	if (machine.input().seq_pressed(m_field.seq(SEQ_TYPE_INCREMENT)))
	{
		keypressed = true;
		if (m_delta)
			delta += apply_scale(m_delta, keyscale);
		else if (!m_lastdigital)
			// increment only once when first pressed
			delta += apply_scale(1, keyscale);
		m_lastdigital = true;
	}

	// if resetting is requested, clear the accumulated position to 0 before
	// applying the deltas so that we only return this frame's delta
	// note that centering only works for relative controls
	// no need to check if absolute here because it is checked by the validity tests
	if (m_field.analog_reset())
		m_accum = 0;

	// apply the delta to the accumulated value
	m_accum += delta;

	// if our last movement was due to a digital input, and if this control
	// type autocenters, and if neither the increment nor the decrement seq
	// was pressed, apply autocentering
	if (m_autocenter)
	{
<<<<<<< HEAD
		INT32 center = apply_inverse_sensitivity(m_center);
=======
		s32 center = apply_inverse_sensitivity(m_center);
>>>>>>> upstream/master
		if (m_lastdigital && !keypressed)
		{
			// autocenter from positive values
			if (m_accum >= center)
			{
				m_accum -= apply_scale(m_centerdelta, m_keyscalepos);
				if (m_accum < center)
				{
					m_accum = center;
					m_lastdigital = false;
				}
			}

			// autocenter from negative values
			else
			{
				m_accum += apply_scale(m_centerdelta, m_keyscaleneg);
				if (m_accum > center)
				{
					m_accum = center;
					m_lastdigital = false;
				}
			}
		}
	}
	else if (!keypressed)
		m_lastdigital = false;
}


//-------------------------------------------------
//  read - read the current value and insert into
//  the provided ioport_value
//-------------------------------------------------

void analog_field::read(ioport_value &result)
{
	// do nothing if we're not enabled
	if (!m_field.enabled())
		return;

	// start with the raw value
<<<<<<< HEAD
	INT32 value = m_accum;
=======
	s32 value = m_accum;
>>>>>>> upstream/master

	// interpolate if appropriate and if time has passed since the last update
	if (m_interpolate)
		value = manager().frame_interpolate(m_previous, m_accum);

	// apply standard analog settings
	value = apply_settings(value);

	// remap the value if needed
<<<<<<< HEAD
	if (m_field.remap_table() != NULL)
=======
	if (m_field.remap_table() != nullptr)
>>>>>>> upstream/master
		value = m_field.remap_table()[value];

	// invert bits if needed
	if (m_field.analog_invert())
		value = ~value;

	// insert into the port
	result = (result & ~m_field.mask()) | ((value << m_shift) & m_field.mask());
}


//-------------------------------------------------
//  crosshair_read - read a value for crosshairs,
//  scaled between 0 and 1
//-------------------------------------------------

float analog_field::crosshair_read()
{
<<<<<<< HEAD
	INT32 rawvalue = apply_settings(m_accum) & (m_field.mask() >> m_shift);
=======
	s32 rawvalue = apply_settings(m_accum) & (m_field.mask() >> m_shift);
>>>>>>> upstream/master
	return float(rawvalue - m_adjmin) / float(m_adjmax - m_adjmin);
}



/***************************************************************************
    TOKENIZATION HELPERS
***************************************************************************/

//-------------------------------------------------
//  token_to_input_type - convert a string token
//  to an input field type and player
//-------------------------------------------------

ioport_type ioport_manager::token_to_input_type(const char *string, int &player) const
{
	// check for our failsafe case first
	int ipnum;
	if (sscanf(string, "TYPE_OTHER(%d,%d)", &ipnum, &player) == 2)
		return ioport_type(ipnum);

	// find the token in the list
<<<<<<< HEAD
	for (input_type_entry *entry = m_typelist.first(); entry != NULL; entry = entry->next())
		if (entry->token() != NULL && !strcmp(entry->token(), string))
		{
			player = entry->player();
			return entry->type();
=======
	for (input_type_entry &entry : m_typelist)
		if (entry.token() != nullptr && !strcmp(entry.token(), string))
		{
			player = entry.player();
			return entry.type();
>>>>>>> upstream/master
		}

	// if we fail, return IPT_UNKNOWN
	player = 0;
	return IPT_UNKNOWN;
}


//-------------------------------------------------
//  input_type_to_token - convert an input field
//  type and player to a string token
//-------------------------------------------------

<<<<<<< HEAD
const char *ioport_manager::input_type_to_token(std::string &str, ioport_type type, int player)
{
	// look up the port and return the token
	input_type_entry *entry = m_type_to_entry[type][player];
	if (entry != NULL)
		return str.assign(entry->token()).c_str();

	// if that fails, carry on
	return strformat(str, "TYPE_OTHER(%d,%d)", type, player).c_str();
=======
std::string ioport_manager::input_type_to_token(ioport_type type, int player)
{
	// look up the port and return the token
	input_type_entry *entry = m_type_to_entry[type][player];
	if (entry != nullptr)
		return std::string(entry->token());

	// if that fails, carry on
	return string_format("TYPE_OTHER(%d,%d)", type, player);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  token_to_seq_type - convert a string to
//  a sequence type
//-------------------------------------------------

input_seq_type ioport_manager::token_to_seq_type(const char *string)
{
	// look up the string in the table of possible sequence types and return the index
	for (int seqindex = 0; seqindex < ARRAY_LENGTH(seqtypestrings); seqindex++)
		if (!core_stricmp(string, seqtypestrings[seqindex]))
			return input_seq_type(seqindex);
	return SEQ_TYPE_INVALID;
}
<<<<<<< HEAD



//-------------------------------------------------
//  validate_natural_keyboard_statics -
//  validates natural keyboard static data
//-------------------------------------------------

/*
int validate_natural_keyboard_statics(void)
{
    int i;
    int error = FALSE;
    unicode_char last_char = 0;
    const char_info *ci;

    // check to make sure that charinfo is in order
    for (i = 0; i < ARRAY_LENGTH(charinfo); i++)
    {
        if (last_char >= charinfo[i].ch)
        {
            osd_printf_error("inputx: charinfo is out of order; 0x%08x should be higher than 0x%08x\n", charinfo[i].ch, last_char);
            error = TRUE;
        }
        last_char = charinfo[i].ch;
    }

    // check to make sure that I can look up everything on alternate_charmap
    for (i = 0; i < ARRAY_LENGTH(charinfo); i++)
    {
        ci = char_info::find(charinfo[i].ch);
        if (ci != &charinfo[i])
        {
            osd_printf_error("ioport: expected char_info::find(0x%08x) to work properly\n", charinfo[i].ch);
            error = TRUE;
        }
    }
    return error;
}
*/


#ifdef USE_AUTOFIRE
bool ioport_manager::auto_pressed(ioport_field *field)
{
/*
	autofire setting:
	 delay,  on, off
	     1,   1,   1
	     2,   2,   1
	     3,   2,   2
	     4,   3,   2
	     5,   3,   3
	     6,   4,   3
*/

#define IS_AUTOKEY(field)	((field->live().autofire & AUTOFIRE_ON) \
							|| ((field->live().autofire & AUTOFIRE_TOGGLE) \
							&& m_autofiretoggle[field->player()]))

	bool pressed = machine().input().seq_pressed(field->seq(SEQ_TYPE_STANDARD));
	int is_auto = IS_AUTOKEY(field);

	if (pressed && (field->toggle()))
		m_autofiretoggle[field->player()] = field->live().autofire_toggle;

#ifdef USE_CUSTOM_BUTTON
	if (field->type() >= IPT_BUTTON1 && field->type() < IPT_BUTTON1 + MAX_NORMAL_BUTTONS)
	{
		UINT16 button_mask = 1 << (field->type() - IPT_BUTTON1);

		int custom;
		for (custom = 0; custom < MAX_CUSTOM_BUTTONS; custom++)
			if (m_custom_button[field->player()][custom] & button_mask)
			{
				ioport_field *custom_info = m_custom_button_info[field->player()][custom];

				if (machine().input().seq_pressed(custom_info->seq(SEQ_TYPE_STANDARD)))
				{
					if (IS_AUTOKEY(custom_info))
					{
						if (pressed)
							is_auto &= 1;
						else
							is_auto = 1;

						field = custom_info;
					}
					else
						is_auto = 0;

					pressed = 1;
				}
			}
	}
#endif /* USE_CUSTOM_BUTTON */

	if (is_auto)
	{
		if (pressed)
		{
			if (field->live().autopressed > m_autofiredelay[field->player()])
				field->live().autopressed = 0;
			else if (field->live().autopressed > m_autofiredelay[field->player()] / 2)
				pressed = false;

			field->live().autopressed ++;
		}
		else
			field->live().autopressed = 0;
	}

	return pressed;

#undef IS_AUTOKEY
}
#endif /* USE_AUTOFIRE */



#ifdef USE_SHOW_INPUT_LOG
void ioport_manager::copy_command_buffer(char log)
{
	char buf[UTF8_CHAR_MAX + 1];
	unicode_char uchar;
	int len;

	for (len = 0; m_command_buffer[len].code; len++)
		;

	if (len >= ARRAY_LENGTH(m_command_buffer) - 1)
	{
		int i;

		for (i = 0; m_command_buffer[i + 1].code; i++)
			m_command_buffer[i] = m_command_buffer[i + 1];

		m_command_buffer[--len].code = '\0';
	}

	buf[0] = '_';
	buf[1] = log;
	buf[2] = '\0';
	convert_command_glyph(buf, ARRAY_LENGTH(buf));

	if (uchar_from_utf8(&uchar, buf, ARRAY_LENGTH(buf)) == -1)
		return;

	m_command_buffer[len].code = uchar;
	m_command_buffer[len].time = machine().time().as_double();
	m_command_buffer[++len].code = '\0';
}



void ioport_manager::make_input_log()
{
	ioport_port *port;
#ifdef USE_CUSTOM_BUTTON
	int i;
#endif /* USE_CUSTOM_BUTTON */
	int player = 0; /* player 1 */
	int normal_buttons = 6;

	/* loop over all the joysticks for player 1*/
	if (player == 0) /* player 1 */
	{
		static int old_dir = -1;
		static int now_dir = 0;

		for (digital_joystick *joystick = m_joystick_list.first(); joystick != NULL; joystick = joystick->next())
		{
			if (joystick->player() == player)
			{
				/* set the status of neutral (assumed to be only in the defaults) */
				now_dir = 0;

				/* if this is a digital joystick type, apply 4-way rules */
				switch (joystick->current())
				{
					case digital_joystick::DOWN_BIT:
						now_dir = 2;
						break;
					case digital_joystick::LEFT_BIT:
						now_dir = 4;
						break;
					case digital_joystick::RIGHT_BIT:
						now_dir = 6;
						break;
					case digital_joystick::UP_BIT:
						now_dir = 8;
						break;
				}

				/* if this is a digital joystick type, apply 8-way rules */
				//if (portentry->way == 8)
				switch (joystick->current())
				{
					case digital_joystick::DOWN_BIT | digital_joystick::LEFT_BIT:
						now_dir = 1;
						break;
					case digital_joystick::DOWN_BIT | digital_joystick::RIGHT_BIT:
						now_dir = 3;
						break;
					case digital_joystick::UP_BIT | digital_joystick::LEFT_BIT:
						now_dir = 7;
						break;
					case digital_joystick::UP_BIT | digital_joystick::RIGHT_BIT:
						now_dir = 9;
						break;
				}

				/* if we're not pressed, reset old_dir = -1 */
				if (now_dir == 0)
					old_dir = -1;
			}
		}

		/* if this is the first press, show input log */
		if (old_dir != now_dir)
		{
			if (now_dir != 0)
			{
				char colorbutton = '0';
				copy_command_buffer(colorbutton + now_dir);
				old_dir = now_dir;
			}
		}
	}
	/* End of loop over all the joysticks for player 1*/

	/* loop over all the buttons */
	if (normal_buttons > 0)
	{
		int is_neogeo = !core_stricmp(machine().system().source_file+17, "neogeo.c")
						|| !core_stricmp(machine().system().source_file+17, "neogeo_noslot.c");
		static UINT16 old_btn = 0;
		static UINT16 now_btn;
		int is_pressed = 0;

		now_btn = 0;

		for (port = machine().ioport().first_port(); port != NULL; port = port->next())
		{
			ioport_field *field;

			for (field = port->first_field(); field != NULL; field = field->next())
			{
				/* if this is current player, read input port */
				if (field->player() == player && machine().input().seq_pressed(field->seq(SEQ_TYPE_STANDARD)))
				{
					/* if this is normal buttons type, apply usable buttons */
					if ((field->type() >= IPT_BUTTON1) && (field->type() < IPT_BUTTON1 + normal_buttons))
						now_btn |= 1 << (field->type() - IPT_BUTTON1);

					/* if this is start button type */
					else if ((field->type() == IPT_START1) || (field->type() == IPT_START))
							now_btn |= 1 << normal_buttons;

					/* if this is select button type (MESS only) */
					else if (field->type() == IPT_SELECT)
						now_btn |= 1 << (normal_buttons + 1);
				}
			}
		}

#ifdef USE_CUSTOM_BUTTON
		/* if this is custon buttons type, apply usable buttons */
		for (i = 0; i < MAX_CUSTOM_BUTTONS; i++)
			if (m_custom_button[0][i] != 0)
			{
				ioport_field *custom_field = m_custom_button_info[0][i];
	
				if (machine().input().seq_pressed(custom_field->seq(SEQ_TYPE_STANDARD)))
					now_btn |= m_custom_button[0][i];
			}
#endif /* USE_CUSTOM_BUTTON */

		/* if buttons press, leave is_pressed = 1 */
		if (now_btn != 0)
			is_pressed |= 1;

		/* if we're not pressed, reset old_btn = -1 */
		if (!is_pressed)
			old_btn = 1 << (normal_buttons + 2);

		/* if this is the first press, show input log */
		if (old_btn != now_btn)
		{
			if (now_btn != 0)
			{
				/* if this is Neo-Geo games, than alphabetic button type */
				/*                           else numerical  button type */
				char colorbutton = is_neogeo ? 'A' : 'a';
				int n = 1;
				int i;

				for (i = 0; i < normal_buttons; i++, n <<= 1)
				{
					if ((now_btn & n) != 0 && (old_btn & n) == 0)
						copy_command_buffer(colorbutton + i);
				}

				/* if this is start button */
				if (now_btn & 1 << normal_buttons)
					copy_command_buffer('S');

				/* if this is select button (MESS only) */
				if (now_btn & 1 << (normal_buttons + 1))
					copy_command_buffer('s');

				old_btn = now_btn;
				now_btn = 0;
			}
		}
	}
	/* End of loop over all the buttons */
}
#endif /* USE_SHOW_INPUT_LOG */



#ifdef INP_CAPTION
void ioport_manager::draw_caption(render_container *container)
{
	static char next_caption[512], caption_text[512];
	static int next_caption_timer;

	if (has_caption_file() && m_next_caption_frame < 0)
	{
		char	read_buf[512];
skip_comment:
		if (m_caption_file.gets(read_buf, 511) == NULL)
		{
			m_caption_file.close();
		}
		else
		{
			char	buf[16] = "";
			int		i, j;

			for (i = 0, j = 0; i < 16; i++)
			{
				if (read_buf[i] == '\t' || read_buf[i] == ' ')
					continue;
				if ((read_buf[i] == '#' || read_buf[i] == '\r' || read_buf[i] == '\n') && j == 0)
					goto skip_comment;
				if (read_buf[i] < '0' || read_buf[i] > '9')
				{
					buf[j++] ='\0';
					break;
				}
				buf[j++] = read_buf[i];
			}

			m_next_caption_frame = strtol(buf, NULL, 10);
			next_caption_timer = 0;
			if (m_next_caption_frame == 0)
			{
				m_next_caption_frame = (int)machine().first_screen()->frame_number();
				strcpy(next_caption, _("Error: illegal caption file"));
				m_caption_file.close();
			}

			for (;;i++)
			{
				if (read_buf[i] == '(')
				{
					for (i++, j = 0;;i++)
					{
						if (read_buf[i] == '\t' || read_buf[i] == ' ')
							continue;
						if (read_buf[i] < '0' || read_buf[i] > '9')
						{
							buf[j++] ='\0';
							break;
						}
						buf[j++] = read_buf[i];
					}

					next_caption_timer = strtol(buf, NULL, 10);

					for (;;i++)
					{
						if (read_buf[i] == '\t' || read_buf[i] == ' ')
							continue;
						if (read_buf[i] == ':')
							break;
					}
				}
				if (read_buf[i] != '\t' && read_buf[i] != ' ' && read_buf[i] != ':')
					break;
			}
			if (next_caption_timer == 0)
			{
				next_caption_timer = 5 * ATTOSECONDS_TO_HZ(machine().first_screen()->frame_period().attoseconds);	// 5sec.
			}

			strcpy(next_caption, &read_buf[i]);

			for (i = 0; next_caption[i] != '\0'; i++)
			{
				if (next_caption[i] == '\r' || next_caption[i] == '\n')
				{
					next_caption[i] = '\0';
					break;
				}
			}
		}
	}
	if (next_caption_timer && m_next_caption_frame <= (int)machine().first_screen()->frame_number())
	{
		m_caption_timer = next_caption_timer;
		strcpy(caption_text, next_caption);
		m_next_caption_frame = -1;
		next_caption_timer = 0;
	}

	if (m_caption_timer)
	{
		machine().ui().draw_text_box(container, caption_text, JUSTIFY_LEFT, 0.5f, 1.0f, UI_BACKGROUND_COLOR);
		m_caption_timer--;
	}
}
#endif /* INP_CAPTION */
=======
>>>>>>> upstream/master
