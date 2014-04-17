#include <Nephilim/Razer/SystemKinesis2D.h>
#include <Nephilim/Razer/ComponentKinesisBody2D.h>
#include <Nephilim/Razer/Scene.h>

#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

void SystemKinesis2D::onComponentAdded(std::type_index type_index, void* cdata)
{
	if( type_index == getTypeOf<ComponentKinesisBody2D>())
	{
		Log("Kinesis2D system detected a new component being added. %d", type_index);
		KxBody* body = mScene.CreateQuickBox(100,-150,35,35);

		ComponentKinesisBody2D& bodyComponent = *static_cast<ComponentKinesisBody2D*>(cdata);
		bodyComponent.body = body;
	}
}

void SystemKinesis2D::setupTest()
{
	// A basic scene for testing
	mScene.CreateQuickBox(200,200,20,20);
	mScene.CreateQuickBox(200,200,20,20);
	mScene.CreateQuickBox(200,200,20,20);
	mScene.CreateQuickBox(200,200,20,20);
	mScene.CreateQuickBox(200,200,20,20);
	mScene.CreateQuickBox(200,200,20,20);
	mScene.CreateStaticBox(500, 400, 1000, 10);
}

};
NEPHILIM_NS_END