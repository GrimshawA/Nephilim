#ifndef NephilimRazerSystem_h__
#define NephilimRazerSystem_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Time.h>

#include <vector>
#include <map>
#include <typeindex>

NEPHILIM_NS_BEGIN
namespace rzr
{

class Scene;
/**
	\class System
	\brief Game system manager
*/
class NEPHILIM_API System
{
public:

	virtual ~System();

	virtual void onComponentAdded(std::type_index type_index, void* cdata){}

	virtual void update(const Time& deltaTime){}

	virtual void render(){}

	Scene* mScene;
};

};
NEPHILIM_NS_END
#endif // NephilimRazerSystem_h__
