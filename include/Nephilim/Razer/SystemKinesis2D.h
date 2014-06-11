#ifndef NephilimRazerSystemKinesis2D_h__
#define NephilimRazerSystemKinesis2D_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/System.h>
#include <Nephilim/KxScene.h>
#include <Nephilim/KxDraw.h>
#include <Nephilim/KxBody.h>
#include <Nephilim/CollisionData.h>

NEPHILIM_NS_BEGIN
namespace rzr
{
/**
	\class SystemKinesis2D
*/
class SystemKinesis2D : public System
{
public:
	SystemKinesis2D();

	void addCollisionData(CollisionData& data);

	void onComponentAdded(std::type_index type_index, void* cdata, Entity* entity);

	void setupTest();

	void addStaticTile(float x, float y, float w, float h)
	{
		mPhysicsScene.CreateStaticBox(x,y,w,h);
	}

	void addDynamicTile(float x, float y, float w, float h)
	{
	//	mPhysicsScene.CreateQuickBox(x,y,w,h);
		mPhysicsScene.CreateQuickCircle(x,y,1);
	}

	virtual void update(const Time& deltaTime);

	KxScene mPhysicsScene; ///< Physics scene
};

};
NEPHILIM_NS_END
#endif // NephilimRazerSystemKinesis2D_h__
