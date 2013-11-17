#include <Nephilim/Platform.h>

#if defined(NEPHILIM_WINDOWS)

    #include "win32_SocketImpl.hpp"

#else

    #include "unix_SocketImpl.hpp"

#endif
