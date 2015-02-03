#ifndef NephilimWorldSystem_h__
#define NephilimWorldSystem_h__

#include <Nephilim/Foundation/Object.h>
#include <Nephilim/Foundation/Time.h>

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
class NEPHILIM_API System : public Object
{
public:

	/// Every system plugged in knows the world that owns it
	/// and one system cannot be plugged to two Worlds.
	/// Use shared data or messaging for that kind of interaction
	World* _World;

public:

	/// Destructor
	virtual ~System();

	/// Generic update that systems can run
	virtual void update(const Time& deltaTime);

	virtual void render(){}

	/// Get the world this system is attached to
	/// Any plugged system has exactly one World attached to it
	World* getWorld();
};

NEPHILIM_NS_END
#endif // NephilimWorldSystem_h__
