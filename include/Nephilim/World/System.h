#ifndef NephilimWorldSystem_h__
#define NephilimWorldSystem_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Time.h>

#include <typeindex>

#include <vector>
#include <map>

NEPHILIM_NS_BEGIN

class World;

/**
	\class System
	\brief Traverse the world data to perform many functions

	Systems are serial processors of the world data. Each system
	shall be designed to have a very specific responsability, 
	and it will then periodically iterate the world data and do an operation on it.

	Usual systems are:
	- Animation system ( updates all animations )
	- Physics system ( simulates all physics )
	- AI system ( simulates all intelligent based movement )
	- Input system ( send out input orders to components )
	- Render system ( produce an image from the world data )
	- Audio system ( keep the audio playing )
	- Script system ( call methods on scripts and fetch data from them )
*/
class NEPHILIM_API System
{
public:

	virtual ~System();

	virtual void update(const Time& deltaTime){}

	virtual void render(){}

	World* mWorld;
};

NEPHILIM_NS_END
#endif // NephilimWorldSystem_h__
