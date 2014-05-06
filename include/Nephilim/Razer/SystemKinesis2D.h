#ifndef NephilimRazerSystemKinesis2D_h__
#define NephilimRazerSystemKinesis2D_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/System.h>
#include <Nephilim/KxScene.h>
#include <Nephilim/KxDraw.h>
#include <Nephilim/KxBody.h>

NEPHILIM_NS_BEGIN
namespace rzr
{
/**
	\class SystemKinesis2D
*/
class SystemKinesis2D : public System
{
public:

	void onComponentAdded(std::type_index type_index, void* cdata);

	void setupTest();

	void addStaticTile(float x, float y, float w, float h)
	{
		mScene.CreateStaticBox(x,y,w,h);
	}

	virtual void update(const Time& deltaTime);

	KxScene mScene; ///< Physics scene
};

};
NEPHILIM_NS_END
#endif // NephilimRazerSystemKinesis2D_h__
