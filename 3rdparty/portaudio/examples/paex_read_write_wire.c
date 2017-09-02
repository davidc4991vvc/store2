/** @file paex_read_write_wire.c
	@ingroup examples_src
	@brief Tests full duplex blocking I/O by passing input straight to output.
	@author Bjorn Roche. XO Audio LLC for Z-Systems Engineering.
    @author based on code by: Phil Burk  http://www.softsynth.com
    @author based on code by: Ross Bencina rossb@audiomulch.com
*/
/*
 * $Id: patest_read_record.c 757 2004-02-13 07:48:10Z rossbencina $
 *
 * This program uses the PortAudio Portable Audio Library.
 * For more information see: http://www.portaudio.com
 * Copyright (c) 1999-2000 Ross Bencina and Phil Burk
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
<<<<<<< HEAD
 * The text above constitutes the entire PortAudio license; however, 
=======
 * The text above constitutes the entire PortAudio license; however,
>>>>>>> upstream/master
 * the PortAudio community also makes the following non-binding requests:
 *
 * Any person wishing to distribute modifications to the Software is
 * requested to send the modifications to the original developer so that
<<<<<<< HEAD
 * they can be incorporated into the canonical version. It is also 
 * requested that these non-binding requests be included along with the 
=======
 * they can be incorporated into the canonical version. It is also
 * requested that these non-binding requests be included along with the
>>>>>>> upstream/master
 * license above.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portaudio.h"

/* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
<<<<<<< HEAD
#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (1024)
#define NUM_CHANNELS    (2)
#define NUM_SECONDS     (15)
/* #define DITHER_FLAG     (paDitherOff)  */
#define DITHER_FLAG     (0) /**/

/* @todo Underflow and overflow is disabled until we fix priming of blocking write. */
#define CHECK_OVERFLOW  (0)
#define CHECK_UNDERFLOW  (0)


/* Select sample format. */
#if 0
#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_SIZE (4)
#define SAMPLE_SILENCE  (0.0f)
#define CLEAR(a) memset( (a), 0, FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE )
=======
#define SAMPLE_RATE       (44100)
#define FRAMES_PER_BUFFER   (512)
#define NUM_SECONDS          (10)
/* #define DITHER_FLAG     (paDitherOff)  */
#define DITHER_FLAG           (0)

/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_SIZE (4)
#define SAMPLE_SILENCE  (0.0f)
>>>>>>> upstream/master
#define PRINTF_S_FORMAT "%.8f"
#elif 0
#define PA_SAMPLE_TYPE  paInt16
#define SAMPLE_SIZE (2)
#define SAMPLE_SILENCE  (0)
<<<<<<< HEAD
#define CLEAR(a) memset( (a), 0,  FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE )
#define PRINTF_S_FORMAT "%d"
#elif 1
#define PA_SAMPLE_TYPE  paInt24
#define SAMPLE_SIZE (3)
#define SAMPLE_SILENCE  (0)
#define CLEAR(a) memset( (a), 0,  FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE )
=======
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt24
#define SAMPLE_SIZE (3)
#define SAMPLE_SILENCE  (0)
>>>>>>> upstream/master
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
#define SAMPLE_SIZE (1)
#define SAMPLE_SILENCE  (0)
<<<<<<< HEAD
#define CLEAR(a) memset( (a), 0,  FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE )
=======
>>>>>>> upstream/master
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
#define SAMPLE_SIZE (1)
#define SAMPLE_SILENCE  (128)
<<<<<<< HEAD
#define CLEAR( a ) { \
    int i; \
    for( i=0; i<FRAMES_PER_BUFFER*NUM_CHANNELS; i++ ) \
        ((unsigned char *)a)[i] = (SAMPLE_SILENCE); \
}
#define PRINTF_S_FORMAT "%d"
#endif


=======
#define PRINTF_S_FORMAT "%d"
#endif

>>>>>>> upstream/master
/*******************************************************************/
int main(void);
int main(void)
{
    PaStreamParameters inputParameters, outputParameters;
    PaStream *stream = NULL;
    PaError err;
<<<<<<< HEAD
    char *sampleBlock;
    int i;
    int numBytes;
    
    
    printf("patest_read_write_wire.c\n"); fflush(stdout);

    numBytes = FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE ;
    sampleBlock = (char *) malloc( numBytes );
    if( sampleBlock == NULL )
    {
        printf("Could not allocate record array.\n");
        exit(1);
    }
    CLEAR( sampleBlock );

    err = Pa_Initialize();
    if( err != paNoError ) goto error;

    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    printf( "Input device # %d.\n", inputParameters.device );
    printf( "Input LL: %g s\n", Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency );
    printf( "Input HL: %g s\n", Pa_GetDeviceInfo( inputParameters.device )->defaultHighInputLatency );
    inputParameters.channelCount = NUM_CHANNELS;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultHighInputLatency ;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    printf( "Output device # %d.\n", outputParameters.device );
    printf( "Output LL: %g s\n", Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency );
    printf( "Output HL: %g s\n", Pa_GetDeviceInfo( outputParameters.device )->defaultHighOutputLatency );
    outputParameters.channelCount = NUM_CHANNELS;
    outputParameters.sampleFormat = PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultHighOutputLatency;
=======
    const PaDeviceInfo* inputInfo;
    const PaDeviceInfo* outputInfo;
    char *sampleBlock = NULL;
    int i;
    int numBytes;
    int numChannels;

    printf("patest_read_write_wire.c\n"); fflush(stdout);
    printf("sizeof(int) = %lu\n", sizeof(int)); fflush(stdout);
    printf("sizeof(long) = %lu\n", sizeof(long)); fflush(stdout);

    err = Pa_Initialize();
    if( err != paNoError ) goto error2;

    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    printf( "Input device # %d.\n", inputParameters.device );
    inputInfo = Pa_GetDeviceInfo( inputParameters.device );
    printf( "    Name: %s\n", inputInfo->name );
    printf( "      LL: %g s\n", inputInfo->defaultLowInputLatency );
    printf( "      HL: %g s\n", inputInfo->defaultHighInputLatency );

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    printf( "Output device # %d.\n", outputParameters.device );
    outputInfo = Pa_GetDeviceInfo( outputParameters.device );
    printf( "   Name: %s\n", outputInfo->name );
    printf( "     LL: %g s\n", outputInfo->defaultLowOutputLatency );
    printf( "     HL: %g s\n", outputInfo->defaultHighOutputLatency );

    numChannels = inputInfo->maxInputChannels < outputInfo->maxOutputChannels
            ? inputInfo->maxInputChannels : outputInfo->maxOutputChannels;
    printf( "Num channels = %d.\n", numChannels );

    inputParameters.channelCount = numChannels;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = inputInfo->defaultHighInputLatency ;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    outputParameters.channelCount = numChannels;
    outputParameters.sampleFormat = PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = outputInfo->defaultHighOutputLatency;
>>>>>>> upstream/master
    outputParameters.hostApiSpecificStreamInfo = NULL;

    /* -- setup -- */

<<<<<<< HEAD
   err = Pa_OpenStream(
=======
    err = Pa_OpenStream(
>>>>>>> upstream/master
              &stream,
              &inputParameters,
              &outputParameters,
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              NULL, /* no callback, use blocking API */
              NULL ); /* no callback, so no callback userData */
<<<<<<< HEAD
    if( err != paNoError ) goto error;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;
    printf("Wire on. Will run %d seconds.\n", NUM_SECONDS); fflush(stdout);

    for( i=0; i<(NUM_SECONDS*SAMPLE_RATE)/FRAMES_PER_BUFFER; ++i )
    {
       err = Pa_WriteStream( stream, sampleBlock, FRAMES_PER_BUFFER );
       if( err && CHECK_UNDERFLOW ) goto xrun;
       err = Pa_ReadStream( stream, sampleBlock, FRAMES_PER_BUFFER );
       if( err && CHECK_OVERFLOW ) goto xrun;
    }
    err = Pa_StopStream( stream );
    if( err != paNoError ) goto error;

    CLEAR( sampleBlock );
/*
    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;
    printf("Wire on. Interrupt to stop.\n"); fflush(stdout);

    while( 1 )
    {
       err = Pa_WriteStream( stream, sampleBlock, FRAMES_PER_BUFFER );
       if( err ) goto xrun;
       err = Pa_ReadStream( stream, sampleBlock, FRAMES_PER_BUFFER );
       if( err ) goto xrun;
    }
    err = Pa_StopStream( stream );
    if( err != paNoError ) goto error;

    Pa_CloseStream( stream );
*/
=======
    if( err != paNoError ) goto error2;

    numBytes = FRAMES_PER_BUFFER * numChannels * SAMPLE_SIZE ;
    sampleBlock = (char *) malloc( numBytes );
    if( sampleBlock == NULL )
    {
        printf("Could not allocate record array.\n");
        goto error1;
    }
    memset( sampleBlock, SAMPLE_SILENCE, numBytes );

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error1;
    printf("Wire on. Will run %d seconds.\n", NUM_SECONDS); fflush(stdout);

    for( i=0; i<(NUM_SECONDS*SAMPLE_RATE)/FRAMES_PER_BUFFER; ++i )
    {
        // You may get underruns or overruns if the output is not primed by PortAudio.
        err = Pa_WriteStream( stream, sampleBlock, FRAMES_PER_BUFFER );
        if( err ) goto xrun;
        err = Pa_ReadStream( stream, sampleBlock, FRAMES_PER_BUFFER );
        if( err ) goto xrun;
    }
    printf("Wire off.\n"); fflush(stdout);

    err = Pa_StopStream( stream );
    if( err != paNoError ) goto error1;

>>>>>>> upstream/master
    free( sampleBlock );

    Pa_Terminate();
    return 0;

xrun:
<<<<<<< HEAD
=======
    printf("err = %d\n", err); fflush(stdout);
>>>>>>> upstream/master
    if( stream ) {
       Pa_AbortStream( stream );
       Pa_CloseStream( stream );
    }
    free( sampleBlock );
    Pa_Terminate();
    if( err & paInputOverflow )
       fprintf( stderr, "Input Overflow.\n" );
    if( err & paOutputUnderflow )
       fprintf( stderr, "Output Underflow.\n" );
    return -2;
<<<<<<< HEAD

error:
=======
error1:
    free( sampleBlock );
error2:
>>>>>>> upstream/master
    if( stream ) {
       Pa_AbortStream( stream );
       Pa_CloseStream( stream );
    }
<<<<<<< HEAD
    free( sampleBlock );
=======
>>>>>>> upstream/master
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    return -1;
}

