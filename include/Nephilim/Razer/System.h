#ifndef NephilimRazerSystem_h__
#define NephilimRazerSystem_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Time.h>

#include <typeindex>

#include <vector>
#include <map>

NEPHILIM_NS_BEGIN

class World;

namespace rzr
{
class Entity;

/**
	\class System
	\brief Game system manager
*/
class NEPHILIM_API System
{
public:

	virtual ~System();

	virtual void onComponentAdded(std::type_index type_index, void* cdata, Entity* entity){}

	virtual void update(const Time& deltaTime){}

	virtual void render(){}

	World* mScene;
};

};
NEPHILIM_NS_END
#endif // NephilimRazerSystem_h__
