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

#ifndef NephilimLock_h__
#define NephilimLock_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

class Mutex;

////////////////////////////////////////////////////////////////////////////////
/// \brief Automatic wrapper for locking and unlocking mutexes
///
////////////////////////////////////////////////////////////////////////////////
class NEPHILIM_API Lock/* : NonCopyable*/
{
public :

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Construct the lock with a target mutex
    ///
    /// The mutex passed to sf::Lock is automatically locked.
    ///
    /// \param mutex Mutex to lock
    ///
    ////////////////////////////////////////////////////////////////////////////
    explicit Lock(Mutex& mutex);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    /// The destructor of sf::Lock automatically unlocks its mutex.
    ///
    ////////////////////////////////////////////////////////////////////////////
    ~Lock();

private :

    ////////////////////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////////////////////
    Mutex& m_mutex; ///< Mutex to lock / unlock
};

NEPHILIM_NS_END
#endif // NephilimLock_h__
