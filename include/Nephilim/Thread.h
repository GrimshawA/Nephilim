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

#ifndef NephilimThread_h__
#define NephilimThread_h__

#include "Platform.h"
#include <cstdlib>

NEPHILIM_NS_BEGIN

namespace priv
{
    class ThreadImpl;
    struct ThreadFunc;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief Utility class to manipulate threads
///
////////////////////////////////////////////////////////////////////////////////
class NEPHILIM_API Thread/* : NonCopyable*/
{
public :

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Construct the thread from a functor with no argument
    ///
    /// This constructor works for function objects, as well
    /// as free function.
    ///
    /// Use this constructor for this kind of function:
    /// \code
    /// void function();
    ///
    /// // --- or ----
    ///
    /// struct Functor
    /// {
    ///     void operator()();
    /// };
    /// \endcode
    /// Note: this does *not* run the thread, use Launch().
    ///
    /// \param function Functor or free function to use as the entry point of the thread
    ///
    ////////////////////////////////////////////////////////////////////////////
    template <typename F>
    Thread(F function);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Construct the thread from a functor with an argument
    ///
    /// This constructor works for function objects, as well
    /// as free function.
    /// It is a template, which means that the argument can
    /// have any type (int, std::string, void*, Toto, ...).
    ///
    /// Use this constructor for this kind of function:
    /// \code
    /// void function(int arg);
    ///
    /// // --- or ----
    ///
    /// struct Functor
    /// {
    ///     void operator()(std::string arg);
    /// };
    /// \endcode
    /// Note: this does *not* run the thread, use Launch().
    ///
    /// \param function Functor or free function to use as the entry point of the thread
    /// \param argument argument to forward to the function
    ///
    ////////////////////////////////////////////////////////////////////////////
    template <typename F, typename A>
    Thread(F function, A argument);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Construct the thread from a member function and an object
    ///
    /// This constructor is template, which means that you can
    /// use it with any class.
    /// Use this constructor for this kind of function:
    /// \code
    /// class MyClass
    /// {
    /// public :
    ///
    ///     void function();
    /// };
    /// \endcode
    /// Note: this does *not* run the thread, use Launch().
    ///
    /// \param function Entry point of the thread
    /// \param object Pointer to the object to use
    ///
    ////////////////////////////////////////////////////////////////////////////
    template <typename C>
    Thread(void(C::*function)(), C* object);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    /// This destructor calls Wait(), so that the internal thread
    /// cannot survive after its sf::Thread instance is destroyed.
    ///
    ////////////////////////////////////////////////////////////////////////////
    ~Thread();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Run the thread
    ///
    /// This function starts the entry point passed to the
    /// thread's constructor, and returns immediately.
    /// After this function returns, the thread's function is
    /// running in parallel to the calling code.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void launch();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Wait until the thread finishes
    ///
    /// This function will block the execution until the
    /// thread's function ends.
    /// Warning: if the thread function never ends, the calling
    /// thread will block forever.
    /// If this function is called from its owner thread, it
    /// returns without doing anything.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void wait();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Terminate the thread
    ///
    /// This function immediately stops the thread, without waiting
    /// for its function to finish.
    /// Terminating a thread with this function is not safe,
    /// and can lead to local variables not being destroyed
    /// on some operating systems. You should rather try to make
    /// the thread function terminate by itself.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void terminate();

private :

    friend class priv::ThreadImpl;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Internal entry point of the thread
    ///
    /// This function is called by the thread implementation.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void run();

    ////////////////////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////////////////////
    priv::ThreadImpl* m_impl;       ///< OS-specific implementation of the thread
    priv::ThreadFunc* m_entryPoint; ///< Abstraction of the function to run
};

#include "Thread.inl"

NEPHILIM_NS_END

#endif // NephilimThread_h__
