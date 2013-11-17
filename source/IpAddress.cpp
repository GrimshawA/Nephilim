#include <Nephilim/IpAddress.h>
//#include <SFML/Network/Http.hpp>
#include "SocketImpl.hpp"
#include <cstring>


namespace
{
    nx::Uint32 resolve(const std::string& address)
    {
        if (address == "255.255.255.255")
        {
            // The broadcast address needs to be handled explicitely,
            // because it is also the value returned by inet_addr on error
            return INADDR_BROADCAST;
        }
        else
        {
            // Try to convert the address as a byte representation ("xxx.xxx.xxx.xxx")
            nx::Uint32 ip = inet_addr(address.c_str());
            if (ip != INADDR_NONE)
                return ip;

            // Not a valid address, try to convert it as a host name
            addrinfo hints;
            std::memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_INET;
            addrinfo* result = NULL;
            if (getaddrinfo(address.c_str(), NULL, &hints, &result) == 0)
            {
                if (result)
                {
                    ip = reinterpret_cast<sockaddr_in*>(result->ai_addr)->sin_addr.s_addr;
                    freeaddrinfo(result);
                    return ip;
                }
            }

            // Not a valid address nor a host name
            return 0;
        }
    }
}

NEPHILIM_NS_BEGIN

////////////////////////////////////////////////////////////
const IpAddress IpAddress::None;
const IpAddress IpAddress::LocalHost(127, 0, 0, 1);
const IpAddress IpAddress::Broadcast(255, 255, 255, 255);


////////////////////////////////////////////////////////////
IpAddress::IpAddress() :
m_address(0)
{
    // We're using 0 (INADDR_ANY) instead of INADDR_NONE to represent the invalid address,
    // because the latter is also the broadcast address (255.255.255.255); it's ok because
    // SFML doesn't publicly use INADDR_ANY (it is always used implicitely)
}


////////////////////////////////////////////////////////////
IpAddress::IpAddress(const std::string& address) :
m_address(resolve(address))
{
}


////////////////////////////////////////////////////////////
IpAddress::IpAddress(const char* address) :
m_address(resolve(address))
{
}


////////////////////////////////////////////////////////////
IpAddress::IpAddress(Uint8 byte0, Uint8 byte1, Uint8 byte2, Uint8 byte3) :
m_address(htonl((byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3))
{
}


////////////////////////////////////////////////////////////
IpAddress::IpAddress(Uint32 address) :
m_address(htonl(address))
{
}


////////////////////////////////////////////////////////////
std::string IpAddress::toString() const
{
    in_addr address;
    address.s_addr = m_address;

    return inet_ntoa(address);
}


////////////////////////////////////////////////////////////
Uint32 IpAddress::toInteger() const
{
    return ntohl(m_address);
}


////////////////////////////////////////////////////////////
IpAddress IpAddress::getLocalAddress()
{
    // The method here is to connect a UDP socket to anyone (here to localhost),
    // and get the local socket address with the getsockname function.
    // UDP connection will not send anything to the network, so this function won't cause any overhead.

    IpAddress localAddress;

    // Create the socket
    SocketHandle sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == priv::SocketImpl::invalidSocket())
        return localAddress;

    // Connect the socket to localhost on any port
    sockaddr_in address = priv::SocketImpl::createAddress(ntohl(INADDR_LOOPBACK), 9);
    if (connect(sock, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == -1)
    {
        priv::SocketImpl::close(sock);
        return localAddress;
    }

    // Get the local address of the socket connection
    priv::SocketImpl::AddrLength size = sizeof(address);
    if (getsockname(sock, reinterpret_cast<sockaddr*>(&address), &size) == -1)
    {
        priv::SocketImpl::close(sock);
        return localAddress;
    }

    // Close the socket
    priv::SocketImpl::close(sock);

    // Finally build the IP address
    localAddress = IpAddress(ntohl(address.sin_addr.s_addr));

    return localAddress;
}


////////////////////////////////////////////////////////////
IpAddress IpAddress::getPublicAddress(Time timeout)
{
    // The trick here is more complicated, because the only way
    // to get our public IP address is to get it from a distant computer.
    // Here we get the web page from http://www.sfml-dev.org/ip-provider.php
    // and parse the result to extract our IP address
    // (not very hard: the web page contains only our IP address).

/*    Http server("www.sfml-dev.org");
    Http::Request request("/ip-provider.php", Http::Request::Get);
    Http::Response page = server.sendRequest(request, timeout);
    if (page.getStatus() == Http::Response::Ok)
        return IpAddress(page.getBody());
		*/
    // Something failed: return an invalid address
    return IpAddress();
}


////////////////////////////////////////////////////////////
bool operator ==(const IpAddress& left, const IpAddress& right)
{
    return left.toInteger() == right.toInteger();
}


////////////////////////////////////////////////////////////
bool operator !=(const IpAddress& left, const IpAddress& right)
{
    return !(left == right);
}


////////////////////////////////////////////////////////////
bool operator <(const IpAddress& left, const IpAddress& right)
{
    return left.toInteger() < right.toInteger();
}


////////////////////////////////////////////////////////////
bool operator >(const IpAddress& left, const IpAddress& right)
{
    return right < left;
}


////////////////////////////////////////////////////////////
bool operator <=(const IpAddress& left, const IpAddress& right)
{
    return !(right < left);
}


////////////////////////////////////////////////////////////
bool operator >=(const IpAddress& left, const IpAddress& right)
{
    return !(left < right);
}


////////////////////////////////////////////////////////////
std::istream& operator >>(std::istream& stream, IpAddress& address)
{
    std::string str;
    stream >> str;
    address = IpAddress(str);

    return stream;
}


////////////////////////////////////////////////////////////
std::ostream& operator <<(std::ostream& stream, const IpAddress& address)
{
    return stream << address.toString();
}

NEPHILIM_NS_END