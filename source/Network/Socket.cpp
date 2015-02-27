#ifdef IGNOREMENOW

#include <Nephilim/Network/Socket.h>
#include "SocketImpl.hpp"

NEPHILIM_NS_BEGIN

////////////////////////////////////////////////////////////
Socket::Socket(Type type) :
m_type      (type),
m_socket    (priv::SocketImpl::invalidSocket()),
m_isBlocking(true)
{

}


////////////////////////////////////////////////////////////
Socket::~Socket()
{
    // Close the socket before it gets destructed
    close();
}


////////////////////////////////////////////////////////////
void Socket::setBlocking(bool blocking)
{
    // Apply if the socket is already created
    if (m_socket != priv::SocketImpl::invalidSocket())
        priv::SocketImpl::setBlocking(m_socket, blocking);

    m_isBlocking = blocking;
}


////////////////////////////////////////////////////////////
bool Socket::isBlocking() const
{
    return m_isBlocking;
}


////////////////////////////////////////////////////////////
SocketHandle Socket::getHandle() const
{
    return m_socket;
}


////////////////////////////////////////////////////////////
void Socket::create()
{
    // Don't create the socket if it already exists
    if (m_socket == priv::SocketImpl::invalidSocket())
    {
        SocketHandle handle = socket(PF_INET, m_type == Tcp ? SOCK_STREAM : SOCK_DGRAM, 0);
        create(handle);
    }
}


////////////////////////////////////////////////////////////
void Socket::create(SocketHandle handle)
{
    // Don't create the socket if it already exists
    if (m_socket == priv::SocketImpl::invalidSocket())
    {
        // Assign the new handle
        m_socket = handle;

        // Set the current blocking state
        setBlocking(m_isBlocking);

        if (m_type == Tcp)
        {
            // Disable the Nagle algorithm (ie. removes buffering of TCP packets)
            int yes = 1;
            if (setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
            {
                /*err() << "Failed to set socket option \"TCP_NODELAY\" ; "
                      << "all your TCP packets will be buffered" << std::endl;*/
            }

            // On Mac OS X, disable the SIGPIPE signal on disconnection
            #ifdef SFML_SYSTEM_MACOS
                if (setsockopt(m_socket, SOL_SOCKET, SO_NOSIGPIPE, reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
                {
                    /*err() << "Failed to set socket option \"SO_NOSIGPIPE\"" << std::endl;*/
                }
            #endif
        }
        else
        {
            // Enable broadcast by default for UDP sockets
            int yes = 1;
            if (setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
            {
/*                err() << "Failed to enable broadcast on UDP socket" << std::endl;*/
            }
        }
    }
}


////////////////////////////////////////////////////////////
void Socket::close()
{
    // Close the socket
    if (m_socket != priv::SocketImpl::invalidSocket())
    {
        priv::SocketImpl::close(m_socket);
        m_socket = priv::SocketImpl::invalidSocket();
    }
}

NEPHILIM_NS_END

#endif