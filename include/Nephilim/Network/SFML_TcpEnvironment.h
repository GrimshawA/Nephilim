#ifndef NephilimSFML_TcpEnvironment_h__
#define NephilimSFML_TcpEnvironment_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Network/NetworkingEnvironment.h>
#include <Nephilim/Network/TcpSocket.h>

NEPHILIM_NS_BEGIN

/**
	\class SFML_TcpEnvironment
	\brief This NetworkingEnvironment allows the game to use SFML tcp socket implementation to create connections
*/
class NEPHILIM_API SFML_TcpEnvironment : public NetworkingEnvironment
{
public:

};

NEPHILIM_NS_END
#endif // NephilimSFML_TcpEnvironment_h__
