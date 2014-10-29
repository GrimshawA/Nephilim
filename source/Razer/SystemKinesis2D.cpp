#include <Nephilim/Razer/SystemKinesis2D.h>
#include <Nephilim/Razer/ComponentKinesisBody2D.h>
#include <Nephilim/Razer/CTransform.h>
#include <Nephilim/Razer/World.h>
#include <Nephilim/Razer/Entity.h>

#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

std::map<Int64, KxBody*> Bodies;

SystemKinesis2D::SystemKinesis2D()
: System()
{
	mPhysicsScene.m_pixelsPerMeter = 1;
}

void SystemKinesis2D::update(const Time& deltaTime)
{
	/*mPhysicsScene.update(deltaTime.asSeconds());

	// Lets sync the transforms and the bodies
	for(std::map<Int64, KxBody*>::iterator it = Bodies.begin(); it != Bodies.end(); ++it)
	{
		Entity ent = mScene->getEntityById(it->first);
		ent.getComponent<ComponentTransform>().position.x = it->second->getPosition().x;
		ent.getComponent<ComponentTransform>().position.y = it->second->getPosition().y;
	}*/
}

void SystemKinesis2D::addCollisionData(CollisionData& data)
{
	/*Log("The message is: %s", data.s.c_str());

	for(CollisionData::BodyIterator it = data.mBodies.begin(); it != data.mBodies.end(); ++it)
	{
		for(CollisionData::ShapeIterator it2 = (*it).mShapes.begin(); it2 != (*it).mShapes.end(); ++it2)
		{
			mPhysicsScene.CreateStaticBox(it2->position.x, -it2->position.y, it2->size.x, it2->size.y);
			Log("ADDED BOX");
		}
	}*/
}

void SystemKinesis2D::onComponentAdded(std::type_index type_index, void* cdata, Entity* entity)
{
	/*if( type_index == getTypeOf<ComponentKinesisBody2D>())
	{
		Log("Kinesis2D system detected a new component being added. %d", type_index);
		KxBody* body = mPhysicsScene.CreateQuickBox(4,0,1,1);

		ComponentKinesisBody2D& bodyComponent = *static_cast<ComponentKinesisBody2D*>(cdata);
		bodyComponent.body = body;

		Bodies[entity->id] = body;
		
		Log("created a physical body");
	}*/
}

void SystemKinesis2D::setupTest()
{
	
}

};
NEPHILIM_NS_END