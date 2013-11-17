#ifndef SocketSelector_h__
#define SocketSelector_h__

#include "Platform.h"
#include "Time.h"

NEPHILIM_NS_BEGIN

class Socket;

////////////////////////////////////////////////////////////
/// \brief Multiplexer that allows to read from multiple sockets
///
////////////////////////////////////////////////////////////
class NEPHILIM_API SocketSelector
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    SocketSelector();

    ////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    /// \param copy Instance to copy
    ///
    ////////////////////////////////////////////////////////////
    SocketSelector(const SocketSelector& copy);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~SocketSelector();

    ////////////////////////////////////////////////////////////
    /// \brief Add a new socket to the selector
    ///
    /// This function keeps a weak reference to the socket,
    /// so you have to make sure that the socket is not destroyed
    /// while it is stored in the selector.
    /// This function does nothing if the socket is not valid.
    ///
    /// \param socket Reference to the socket to add
    ///
    /// \see remove, clear
    ///
    ////////////////////////////////////////////////////////////
    void add(Socket& socket);

    ////////////////////////////////////////////////////////////
    /// \brief Remove a socket from the selector
    ///
    /// This function doesn't destroy the socket, it simply
    /// removes the reference that the selector has to it.
    ///
    /// \param socket Reference to the socket to remove
    ///
    /// \see add, clear
    ///
    ////////////////////////////////////////////////////////////
    void remove(Socket& socket);

    ////////////////////////////////////////////////////////////
    /// \brief Remove all the sockets stored in the selector
    ///
    /// This function doesn't destroy any instance, it simply
    /// removes all the references that the selector has to
    /// external sockets.
    ///
    /// \see add, remove
    ///
    ////////////////////////////////////////////////////////////
    void clear();

    ////////////////////////////////////////////////////////////
    /// \brief Wait until one or more sockets are ready to receive
    ///
    /// This function returns as soon as at least one socket has
    /// some data available to be received. To know which sockets are
    /// ready, use the isReady function.
    /// If you use a timeout and no socket is ready before the timeout
    /// is over, the function returns false.
    ///
    /// \param timeout Maximum time to wait, (use Time::Zero for infinity)
    ///
    /// \return True if there are sockets ready, false otherwise
    ///
    /// \see isReady
    ///
    ////////////////////////////////////////////////////////////
    bool wait(Time timeout = Time::Zero);

    ////////////////////////////////////////////////////////////
    /// \brief Test a socket to know if it is ready to receive data
    ///
    /// This function must be used after a call to Wait, to know
    /// which sockets are ready to receive data. If a socket is
    /// ready, a call to receive will never block because we know
    /// that there is data available to read.
    /// Note that if this function returns true for a TcpListener,
    /// this means that it is ready to accept a new connection.
    ///
    /// \param socket Socket to test
    ///
    /// \return True if the socket is ready to read, false otherwise
    ///
    /// \see isReady
    ///
    ////////////////////////////////////////////////////////////
    bool isReady(Socket& socket) const;

    ////////////////////////////////////////////////////////////
    /// \brief Overload of assignment operator
    ///
    /// \param right Instance to assign
    ///
    /// \return Reference to self
    ///
    ////////////////////////////////////////////////////////////
    SocketSelector& operator =(const SocketSelector& right);

private :

    struct SocketSelectorImpl;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    SocketSelectorImpl* m_impl; ///< Opaque pointer to the implementation (which requires OS-specific types)
};

NEPHILIM_NS_END
#endif // SocketSelector_h__
