#ifndef ConnectionENET_h__
#define ConnectionENET_h__

#include <Nephilim/Network/Connection.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API ConnectionENET : public Connection
{
public:
	virtual void send(const Packet& pck);
};

NEPHILIM_NS_END
#endif // ConnectionENET_h__

