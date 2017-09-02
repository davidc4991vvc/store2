// StreamUtils.h

<<<<<<< HEAD
#ifndef __STREAMUTILS_H
#define __STREAMUTILS_H

#include "../IStream.h"

HRESULT ReadStream(ISequentialInStream *stream, void *data, size_t *size);
HRESULT ReadStream_FALSE(ISequentialInStream *stream, void *data, size_t size);
HRESULT ReadStream_FAIL(ISequentialInStream *stream, void *data, size_t size);
HRESULT WriteStream(ISequentialOutStream *stream, const void *data, size_t size);
=======
#ifndef __STREAM_UTILS_H
#define __STREAM_UTILS_H

#include "../IStream.h"

HRESULT ReadStream(ISequentialInStream *stream, void *data, size_t *size) throw();
HRESULT ReadStream_FALSE(ISequentialInStream *stream, void *data, size_t size) throw();
HRESULT ReadStream_FAIL(ISequentialInStream *stream, void *data, size_t size) throw();
HRESULT WriteStream(ISequentialOutStream *stream, const void *data, size_t size) throw();
>>>>>>> upstream/master

#endif
