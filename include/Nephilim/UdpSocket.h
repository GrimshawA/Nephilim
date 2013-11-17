#ifndef NephilimUdpSocket_h__
#define NephilimUdpSocket_h__

#include "Platform.h"
#include "Socket.h"

#include <vector>

NEPHILIM_NS_BEGIN

class IpAddress;
class Packet;

////////////////////////////////////////////////////////////
/// \brief Specialized socket using the UDP protocol
///
////////////////////////////////////////////////////////////
class NEPHILIM_API UdpSocket : public Socket
{
public :

    ////////////////////////////////////////////////////////////
    // Constants
    ////////////////////////////////////////////////////////////
    enum
    {
        MaxDatagramSize = 65507 ///< The maximum number of bytes that can be sent in a single UDP datagram
    };

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    UdpSocket();

    ////////////////////////////////////////////////////////////
    /// \brief Get the port to which the socket is bound locally
    ///
    /// If the socket is not bound to a port, this function
    /// returns 0.
    ///
    /// \return Port to which the socket is bound
    ///
    /// \see bind
    ///
    ////////////////////////////////////////////////////////////
    unsigned short getLocalPort() const;

    ////////////////////////////////////////////////////////////
    /// \brief Bind the socket to a specific port
    ///
    /// Binding the socket to a port is necessary for being
    /// able to receive data on that port.
    /// You can use the special value Socket::AnyPort to tell the
    /// system to automatically pick an available port, and then
    /// call getLocalPort to retrieve the chosen port.
    ///
    /// \param port Port to bind the socket to
    ///
    /// \return Status code
    ///
    /// \see unbind, getLocalPort
    ///
    ////////////////////////////////////////////////////////////
    Status bind(unsigned short port);

    ////////////////////////////////////////////////////////////
    /// \brief Unbind the socket from the local port to which it is bound
    ///
    /// The port that the socket was previously using is immediately
    /// available after this function is called. If the
    /// socket is not bound to a port, this function has no effect.
    ///
    /// \see bind
    ///
    ////////////////////////////////////////////////////////////
    void unbind();

    ////////////////////////////////////////////////////////////
    /// \brief Send raw data to a remote peer
    ///
    /// Make sure that \a size is not greater than
    /// UdpSocket::MaxDatagramSize, otherwise this function will
    /// fail and no data will be sent.
    ///
    /// \param data          Pointer to the sequence of bytes to send
    /// \param size          Number of bytes to send
    /// \param remoteAddress Address of the receiver
    /// \param remotePort    Port of the receiver to send the data to
    ///
    /// \return Status code
    ///
    /// \see receive
    ///
    ////////////////////////////////////////////////////////////
    Status send(const void* data, std::size_t size, const IpAddress& remoteAddress, unsigned short remotePort);

    ////////////////////////////////////////////////////////////
    /// \brief Receive raw data from a remote peer
    ///
    /// In blocking mode, this function will wait until some
    /// bytes are actually received.
    /// Be careful to use a buffer which is large enough for
    /// the data that you intend to receive, if it is too small
    /// then an error will be returned and *all* the data will
    /// be lost.
    ///
    /// \param data          Pointer to the array to fill with the received bytes
    /// \param size          Maximum number of bytes that can be received
    /// \param received      This variable is filled with the actual number of bytes received
    /// \param remoteAddress Address of the peer that sent the data
    /// \param remotePort    Port of the peer that sent the data
    ///
    /// \return Status code
    ///
    /// \see send
    ///
    ////////////////////////////////////////////////////////////
    Status receive(void* data, std::size_t size, std::size_t& received, IpAddress& remoteAddress, unsigned short& remotePort);

    ////////////////////////////////////////////////////////////
    /// \brief Send a formatted packet of data to a remote peer
    ///
    /// Make sure that the packet size is not greater than
    /// UdpSocket::MaxDatagramSize, otherwise this function will
    /// fail and no data will be sent.
    ///
    /// \param packet        Packet to send
    /// \param remoteAddress Address of the receiver
    /// \param remotePort    Port of the receiver to send the data to
    ///
    /// \return Status code
    ///
    /// \see receive
    ///
    ////////////////////////////////////////////////////////////
    Status send(Packet& packet, const IpAddress& remoteAddress, unsigned short remotePort);

    ////////////////////////////////////////////////////////////
    /// \brief Receive a formatted packet of data from a remote peer
    ///
    /// In blocking mode, this function will wait until the whole packet
    /// has been received.
    ///
    /// \param packet        Packet to fill with the received data
    /// \param remoteAddress Address of the peer that sent the data
    /// \param remotePort    Port of the peer that sent the data
    ///
    /// \return Status code
    ///
    /// \see send
    ///
    ////////////////////////////////////////////////////////////
    Status receive(Packet& packet, IpAddress& remoteAddress, unsigned short& remotePort);

private:

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::vector<char> m_buffer; ///< Temporary buffer holding the received data in Receive(Packet)
};

NEPHILIM_NS_END

#endif // NephilimUdpSocket_h__
