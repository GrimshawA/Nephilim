////////////////////////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2013 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef NephilimMutex_h__
#define NephilimMutex_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

namespace priv
{
    class MutexImpl;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief Blocks concurrent access to shared resources
///        from multiple threads
///
////////////////////////////////////////////////////////////////////////////////
class NEPHILIM_API Mutex/* : NonCopyable*/
{
public :

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////////////////////
    Mutex();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////////////////////
    ~Mutex();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Lock the mutex
    ///
    /// If the mutex is already locked in another thread,
    /// this call will block the execution until the mutex
    /// is released.
    ///
    /// \see unlock
    ///
    ////////////////////////////////////////////////////////////////////////////
    void lock();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Unlock the mutex
    ///
    /// \see lock
    ///
    ////////////////////////////////////////////////////////////////////////////
    void unlock();

private :

    ////////////////////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////////////////////
    priv::MutexImpl* m_mutexImpl; ///< OS-specific implementation
};

NEPHILIM_NS_END

#endif // NephilimMutex_h__
