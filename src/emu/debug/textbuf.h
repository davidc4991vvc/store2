// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    textbuf.h

    Debugger text buffering engine.

***************************************************************************/

<<<<<<< HEAD
#ifndef __TEXTBUF_H__
#define __TEXTBUF_H__

=======
#ifndef MAME_EMU_DEBUG_TEXTBUF_H
#define MAME_EMU_DEBUG_TEXTBUF_H

#include "emucore.h"
>>>>>>> upstream/master

/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

struct text_buffer;



/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

/* allocate a new text buffer */
<<<<<<< HEAD
text_buffer *text_buffer_alloc(UINT32 bytes, UINT32 lines);
=======
text_buffer *text_buffer_alloc(u32 bytes, u32 lines);
>>>>>>> upstream/master

/* free a text buffer */
void text_buffer_free(text_buffer *text);

/* clear a text buffer */
void text_buffer_clear(text_buffer *text);

/* "print" data to a text buffer */
void text_buffer_print(text_buffer *text, const char *data);

/* "print" data to a text buffer with word wrapping to a given column */
void text_buffer_print_wrap(text_buffer *text, const char *data, int wrapcol);

/* get the maximum width of lines seen so far */
<<<<<<< HEAD
UINT32 text_buffer_max_width(text_buffer *text);

/* get the current number of lines in the buffer */
UINT32 text_buffer_num_lines(text_buffer *text);

/* get an absolute sequence number for a given line */
UINT32 text_buffer_line_index_to_seqnum(text_buffer *text, UINT32 index);

/* get a sequenced line from the text buffer */
const char *text_buffer_get_seqnum_line(text_buffer *text, UINT32 seqnum);


#endif  /* __TEXTBUF_H__ */
=======
u32 text_buffer_max_width(text_buffer *text);

/* get the current number of lines in the buffer */
u32 text_buffer_num_lines(text_buffer *text);

/* get an absolute sequence number for a given line */
u32 text_buffer_line_index_to_seqnum(text_buffer *text, u32 index);

/* get a sequenced line from the text buffer */
const char *text_buffer_get_seqnum_line(text_buffer *text, u32 seqnum);


#endif  /* MAME_EMU_DEBUG_TEXTBUF_H */
>>>>>>> upstream/master
