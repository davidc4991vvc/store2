// List.h

#ifndef __LIST_H
#define __LIST_H

<<<<<<< HEAD
#include "Common/Wildcard.h"
#include "../Common/LoadCodecs.h"

HRESULT ListArchives(CCodecs *codecs, const CIntVector &formatIndices,
    bool stdInMode,
    UStringVector &archivePaths, UStringVector &archivePathsFull,
=======
#include "../../../Common/Wildcard.h"

#include "../Common/LoadCodecs.h"

HRESULT ListArchives(CCodecs *codecs,
    const CObjectVector<COpenType> &types,
    const CIntVector &excludedFormats,
    bool stdInMode,
    UStringVector &archivePaths, UStringVector &archivePathsFull,
    bool processAltStreams, bool showAltStreams,
>>>>>>> upstream/master
    const NWildcard::CCensorNode &wildcardCensor,
    bool enableHeaders, bool techMode,
    #ifndef _NO_CRYPTO
    bool &passwordEnabled, UString &password,
    #endif
<<<<<<< HEAD
    UInt64 &errors);

#endif

=======
    #ifndef _SFX
    const CObjectVector<CProperty> *props,
    #endif
    UInt64 &errors,
    UInt64 &numWarnings);

#endif
>>>>>>> upstream/master
