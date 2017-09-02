// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Aaron Giles
=======
// copyright-holders:Aaron Giles, Vas Crabb
>>>>>>> upstream/master
/***************************************************************************

    aviio.h

    AVI movie format parsing helpers.

***************************************************************************/

<<<<<<< HEAD
#ifndef __AVIIO_H__
#define __AVIIO_H__
=======
#ifndef MAME_LIB_UTIL_AVIIO_H
#define MAME_LIB_UTIL_AVIIO_H
>>>>>>> upstream/master

#include "osdcore.h"
#include "bitmap.h"

<<<<<<< HEAD

/***************************************************************************
    CONSTANTS
***************************************************************************/

enum avi_error
{
	AVIERR_NONE = 0,
	AVIERR_END,
	AVIERR_INVALID_DATA,
	AVIERR_NO_MEMORY,
	AVIERR_READ_ERROR,
	AVIERR_WRITE_ERROR,
	AVIERR_STACK_TOO_DEEP,
	AVIERR_UNSUPPORTED_FEATURE,
	AVIERR_CANT_OPEN_FILE,
	AVIERR_INCOMPATIBLE_AUDIO_STREAMS,
	AVIERR_INVALID_SAMPLERATE,
	AVIERR_INVALID_STREAM,
	AVIERR_INVALID_FRAME,
	AVIERR_INVALID_BITMAP,
	AVIERR_UNSUPPORTED_VIDEO_FORMAT,
	AVIERR_UNSUPPORTED_AUDIO_FORMAT,
	AVIERR_EXCEEDED_SOUND_BUFFER
};


enum avi_datatype
{
	AVIDATA_VIDEO,
	AVIDATA_AUDIO_CHAN0,
	AVIDATA_AUDIO_CHAN1,
	AVIDATA_AUDIO_CHAN2,
	AVIDATA_AUDIO_CHAN3,
	AVIDATA_AUDIO_CHAN4,
	AVIDATA_AUDIO_CHAN5,
	AVIDATA_AUDIO_CHAN6,
	AVIDATA_AUDIO_CHAN7
};

=======
#include <cstdint>
#include <memory>
#include <string>
>>>>>>> upstream/master


/***************************************************************************
    MACROS
***************************************************************************/

#define AVI_FOURCC(a,b,c,d)     ((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))

#define FORMAT_UYVY             AVI_FOURCC('U','Y','V','Y')
#define FORMAT_VYUY             AVI_FOURCC('V','Y','U','Y')
#define FORMAT_YUY2             AVI_FOURCC('Y','U','Y','2')
#define FORMAT_HFYU             AVI_FOURCC('H','F','Y','U')



<<<<<<< HEAD
/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

struct avi_file;


struct avi_movie_info
{
	UINT32          video_format;               /* format of video data */
	UINT32          video_timescale;            /* timescale for video data */
	UINT32          video_sampletime;           /* duration of a single video sample (frame) */
	UINT32          video_numsamples;           /* total number of video samples */
	UINT32          video_width;                /* width of the video */
	UINT32          video_height;               /* height of the video */
	UINT32          video_depth;                /* depth of the video */

	UINT32          audio_format;               /* format of audio data */
	UINT32          audio_timescale;            /* timescale for audio data */
	UINT32          audio_sampletime;           /* duration of a single audio sample */
	UINT32          audio_numsamples;           /* total number of audio samples */
	UINT32          audio_channels;             /* number of audio channels */
	UINT32          audio_samplebits;           /* number of bits per channel */
	UINT32          audio_samplerate;           /* sample rate of audio */
};



/***************************************************************************
    PROTOTYPES
***************************************************************************/

avi_error avi_open(const char *filename, avi_file **file);
avi_error avi_create(const char *filename, const avi_movie_info *info, avi_file **file);
avi_error avi_close(avi_file *file);

void avi_printf_chunks(avi_file *file);
const char *avi_error_string(avi_error err);

const avi_movie_info *avi_get_movie_info(avi_file *file);
UINT32 avi_first_sample_in_frame(avi_file *file, UINT32 framenum);

avi_error avi_read_video_frame(avi_file *file, UINT32 framenum, bitmap_yuy16 &bitmap);
avi_error avi_read_sound_samples(avi_file *file, int channel, UINT32 firstsample, UINT32 numsamples, INT16 *output);

avi_error avi_append_video_frame(avi_file *file, bitmap_yuy16 &bitmap);
avi_error avi_append_video_frame(avi_file *file, bitmap_rgb32 &bitmap);
avi_error avi_append_sound_samples(avi_file *file, int channel, const INT16 *samples, UINT32 numsamples, UINT32 sampleskip);

#endif
=======
class avi_file
{
public:

	/***********************************************************************
	    CONSTANTS
	***********************************************************************/

	enum class error
	{
		NONE = 0,
		END,
		INVALID_DATA,
		NO_MEMORY,
		READ_ERROR,
		WRITE_ERROR,
		STACK_TOO_DEEP,
		UNSUPPORTED_FEATURE,
		CANT_OPEN_FILE,
		INCOMPATIBLE_AUDIO_STREAMS,
		INVALID_SAMPLERATE,
		INVALID_STREAM,
		INVALID_FRAME,
		INVALID_BITMAP,
		UNSUPPORTED_VIDEO_FORMAT,
		UNSUPPORTED_AUDIO_FORMAT,
		EXCEEDED_SOUND_BUFFER
	};

	enum class datatype
	{
		VIDEO,
		AUDIO_CHAN0,
		AUDIO_CHAN1,
		AUDIO_CHAN2,
		AUDIO_CHAN3,
		AUDIO_CHAN4,
		AUDIO_CHAN5,
		AUDIO_CHAN6,
		AUDIO_CHAN7
	};


	/***********************************************************************
	    TYPE DEFINITIONS
	***********************************************************************/

	struct movie_info
	{
		std::uint32_t   video_format;               // format of video data
		std::uint32_t   video_timescale;            // timescale for video data
		std::uint32_t   video_sampletime;           // duration of a single video sample (frame)
		std::uint32_t   video_numsamples;           // total number of video samples
		std::uint32_t   video_width;                // width of the video
		std::uint32_t   video_height;               // height of the video
		std::uint32_t   video_depth;                // depth of the video

		std::uint32_t   audio_format;               // format of audio data
		std::uint32_t   audio_timescale;            // timescale for audio data
		std::uint32_t   audio_sampletime;           // duration of a single audio sample
		std::uint32_t   audio_numsamples;           // total number of audio samples
		std::uint32_t   audio_channels;             // number of audio channels
		std::uint32_t   audio_samplebits;           // number of bits per channel
		std::uint32_t   audio_samplerate;           // sample rate of audio
	};

	typedef std::unique_ptr<avi_file> ptr;


	/***********************************************************************
	    PROTOTYPES
	***********************************************************************/

	static error open(std::string const &filename, ptr &file);
	static error create(std::string const &filename, movie_info const &info, ptr &file);
	virtual ~avi_file();

	virtual void printf_chunks() = 0;
	static const char *error_string(error err);

	virtual movie_info const &get_movie_info() const = 0;
	virtual std::uint32_t first_sample_in_frame(std::uint32_t framenum) const = 0;

	virtual error read_video_frame(std::uint32_t framenum, bitmap_yuy16 &bitmap) = 0;
	virtual error read_sound_samples(int channel, std::uint32_t firstsample, std::uint32_t numsamples, std::int16_t *output) = 0;

	virtual error append_video_frame(bitmap_yuy16 &bitmap) = 0;
	virtual error append_video_frame(bitmap_rgb32 &bitmap) = 0;
	virtual error append_sound_samples(int channel, std::int16_t const *samples, std::uint32_t numsamples, std::uint32_t sampleskip) = 0;

protected:
	avi_file();
};

#endif // MAME_LIB_UTIL_AVIIO_H
>>>>>>> upstream/master
