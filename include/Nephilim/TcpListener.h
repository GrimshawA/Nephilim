#ifndef NephilimTcpListener_h__
#define NephilimTcpListener_h__

#include "Platform.h"
#include "Socket.h"

NEPHILIM_NS_BEGIN

class TcpSocket;

////////////////////////////////////////////////////////////
/// \brief Socket that listens to new TCP connections
///
////////////////////////////////////////////////////////////
class NEPHILIM_API TcpListener : public Socket
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    TcpListener();

    ////////////////////////////////////////////////////////////
    /// \brief Get the port to which the socket is bound locally
    ///
    /// If the socket is not listening to a port, this function
    /// returns 0.
    ///
    /// \return Port to which the socket is bound
    ///
    /// \see listen
    ///
    ////////////////////////////////////////////////////////////
    unsigned short getLocalPort() const;

    ////////////////////////////////////////////////////////////
    /// \brief Start listening for connections
    ///
    /// This functions makes the socket listen to the specified
    /// port, waiting for new connections.
    /// If the socket was previously listening to another port,
    /// it will be stopped first and bound to the new port.
    ///
    /// \param port Port to listen for new connections
    ///
    /// \return Status code
    ///
    /// \see accept, close
    ///
    ////////////////////////////////////////////////////////////
    Status listen(unsigned short port);

    ////////////////////////////////////////////////////////////
    /// \brief Stop listening and close the socket
    ///
    /// This function gracefully stops the listener. If the
    /// socket is not listening, this function has no effect.
    ///
    /// \see listen
    ///
    ////////////////////////////////////////////////////////////
    void close();

    ////////////////////////////////////////////////////////////
    /// \brief Accept a new connection
    ///
    /// If the socket is in blocking mode, this function will
    /// not return until a connection is actually received.
    ///
    /// \param socket Socket that will hold the new connection
    ///
    /// \return Status code
    ///
    /// \see listen
    ///
    ////////////////////////////////////////////////////////////
    Status accept(TcpSocket& socket);
};

NEPHILIM_NS_END

#endif // NephilimTcpListener_h__