#ifndef SocketHandle_h__
#define SocketHandle_h__

#include "Platform.h"

#if defined(NEPHILIM_WINDOWS)
    #include <basetsd.h>
#endif

NEPHILIM_NS_BEGIN

////////////////////////////////////////////////////////////
// Define the low-level socket handle type, specific to
// each platform
////////////////////////////////////////////////////////////
#if defined(NEPHILIM_WINDOWS)

    typedef UINT_PTR SocketHandle;

#else

    typedef int SocketHandle;

#endif

NEPHILIM_NS_END

#endif // SocketHandle_h__
