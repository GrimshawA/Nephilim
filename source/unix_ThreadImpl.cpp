////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2012 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
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
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Nephilim/Platform.h>
#ifndef NEPHILIM_WINDOWS

#include "unix_ThreadImpl.h"
#include <Nephilim/Thread.h>
#include <Nephilim/Foundation/Logging.h>

#include <iostream>
#include <cassert>

NEPHILIM_NS_BEGIN

namespace priv
{
////////////////////////////////////////////////////////////
ThreadImpl::ThreadImpl(Thread* owner) :
m_isActive(true)
{
    m_isActive = pthread_create(&m_thread, NULL, &ThreadImpl::entryPoint, owner) == 0;

    if (!m_isActive)
        std::cerr << "Failed to create thread" << std::endl;
}


////////////////////////////////////////////////////////////
void ThreadImpl::wait()
{
    if (m_isActive)
    {
        assert(pthread_equal(pthread_self(), m_thread) == 0); // A thread cannot wait for itself!
        pthread_join(m_thread, NULL);
    }
}


////////////////////////////////////////////////////////////
void ThreadImpl::terminate()
{
#ifdef NEPHILIM_ANDROID
	Log("Sorry. Thread::terminate() is not implemented in android.");
#else
    if (m_isActive)
        pthread_cancel(m_thread);
#endif
}


////////////////////////////////////////////////////////////
void* ThreadImpl::entryPoint(void* userData)
{
    // The Thread instance is stored in the user data
    Thread* owner = static_cast<Thread*>(userData);

    // Tell the thread to handle cancel requests immediatly
#ifdef NEPHILIM_ANDROID
	Log("Thread Problem: pthread_setcanceltype unavailable in android");
#else
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
#endif

    // Forward to the owner
    owner->run();

    return NULL;
}

} // namespace priv

NEPHILIM_NS_END
#endif