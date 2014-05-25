#include <Nephilim/Razer/SystemKinesis2D.h>
#include <Nephilim/Razer/ComponentKinesisBody2D.h>
#include <Nephilim/Razer/ComponentTransform.h>
#include <Nephilim/Razer/Scene.h>
#include <Nephilim/Razer/Entity.h>


#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

std::map<Int64, KxBody*> Bodies;

void SystemKinesis2D::update(const Time& deltaTime)
{
	mPhysicsScene.update(deltaTime.asSeconds());

	// Lets sync the transforms and the bodies
	for(std::map<Int64, KxBody*>::iterator it = Bodies.begin(); it != Bodies.end(); ++it)
	{
		Entity ent = mScene->getEntityById(it->first);
		ent.getComponent<ComponentTransform>().x = it->second->getPosition().x;
		ent.getComponent<ComponentTransform>().y = it->second->getPosition().y;
	}
}

void SystemKinesis2D::onComponentAdded(std::type_index type_index, void* cdata, Entity* entity)
{
	if( type_index == getTypeOf<ComponentKinesisBody2D>())
	{
		Log("Kinesis2D system detected a new component being added. %d", type_index);
		KxBody* body = mPhysicsScene.CreateQuickBox(100,-150,35,35);

		ComponentKinesisBody2D& bodyComponent = *static_cast<ComponentKinesisBody2D*>(cdata);
		bodyComponent.body = body;

		Bodies[entity->id] = body;
		
		Log("created a physical body");
	}
}

void SystemKinesis2D::setupTest()
{
	
}

};
NEPHILIM_NS_END