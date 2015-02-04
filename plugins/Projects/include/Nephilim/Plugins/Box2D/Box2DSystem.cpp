#include "Box2DSystem.h"

#include <Box2D/Box2D.h>

#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Graphics/RectangleShape.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/Math.h>

#include <Nephilim/World/ComponentManager.h>
#include <Nephilim/World/CColliderBox.h>
#include <Nephilim/World/CTransform.h>
#include <Nephilim/World/World.h>
#include <Nephilim/World/RigidBody.h>


NEPHILIM_NS_BEGIN

class RigidBodyBox2D : public RigidBody
{
public:

	/// Our Box2D rigid body to act upon
	b2Body* _body = nullptr;

public:

	RigidBodyBox2D()
	{

	}

	RigidBodyBox2D(b2Body* b)
	{
		_body = b;
	}

	/// Apply a force to the center of the rigid body
	virtual void applyForceToCenter(Vector2D force)
	{
		_body->ApplyLinearImpulse(b2Vec2(force.x, force.y), _body->GetLocalCenter());
	}

	/// Apply a angular impulse to the object (2D)
	virtual void applyAngularImpulse(float impulse2d)
	{
		_body->ApplyAngularImpulse(impulse2d);
	}

	virtual void setRotation(float angle)
	{
		_body->SetTransform(_body->GetPosition(), angle);
	}

	virtual float getRotation2D()
	{
		return _body->GetAngle();
	}

	/// Enable or disable rigid body rotation
	virtual void setFixedRotation(bool enable)
	{
		_body->SetFixedRotation(enable);
	}

	/// Check if the rigid body is sleeping, if supported
	virtual bool isAwake()
	{ 
		return _body->IsAwake();
	}
};

/// Initialize the physics world right away
Box2DSystem::Box2DSystem()
: mSimulation(nullptr)
{
	mSimulation = new b2World(b2Vec2(0.f, -9.8));

	// lets add a ground for now
/*	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position = b2Vec2(0.f, 0.f);
	b2Body* groundBody = mSimulation->CreateBody(&groundBodyDef);

	b2PolygonShape groundShape;
	groundShape.SetAsBox(500.f, 5.f);
	groundBody->CreateFixture(&groundShape, 0.f);

	for (std::size_t i = 0; i < 10; ++i)
	{
		spawnTestBox(Vector2D(i * 20.f - 50.f, math::random(20.f, 60.f)), Vector2D(10.f, 10.f));
	}*/

}

/// Ensure the physics get destroyed
Box2DSystem::~Box2DSystem()
{
	delete mSimulation;
}

/// Step forward the simulation
void Box2DSystem::update(const Time& deltaTime)
{
	mSimulation->Step(deltaTime.seconds(), 8, 8);

	// Compute stuff with the world
	ComponentManager* colliderBoxManager = mWorld->getComponentManager<CColliderBox>();
	ComponentManager* transformManager = mWorld->getComponentManager<CTransform>();

	for (std::size_t i = 0; i < colliderBoxManager->getInstanceCount(); ++i)
	{
		CColliderBox* boxCollider = (CColliderBox*)colliderBoxManager->getInstance(i);
		CTransform* transform = (CTransform*)transformManager->getComponentFromEntity(colliderBoxManager->getInstanceEntity(i));
		if (!transform)
		{
			mWorld->createComponent(CTransform(), colliderBoxManager->getInstanceEntity(i));
			transform = (CTransform*)transformManager->getComponentFromEntity(colliderBoxManager->getInstanceEntity(i));
		}

		if (!boxCollider->userData)
		{
			b2BodyDef groundBodyDef2;
			groundBodyDef2.type = boxCollider->_isDynamic ? b2_dynamicBody : b2_staticBody;
			groundBodyDef2.position = b2Vec2(transform->getPosition().x, transform->getPosition().y);
			b2Body* groundBody2 = mSimulation->CreateBody(&groundBodyDef2);

			b2PolygonShape groundShape2;
			groundShape2.SetAsBox(10.f, 10.f);
			groundBody2->CreateFixture(&groundShape2, 1.f);

			groundBody2->SetUserData(boxCollider);
			boxCollider->userData = groundBody2;
		}
		else
		{
			b2Body* boxColliderBody = (b2Body*)boxCollider->userData;
			transform->position.x = boxColliderBody->GetPosition().x;
			transform->position.y = boxColliderBody->GetPosition().y;
			transform->rotation = Quaternion::fromMatrix(mat4::rotatez(boxColliderBody->GetAngle()));
		}
	}

	// Now let's go through the actors to find stuff in them
	for (std::size_t i = 0; i < mWorld->actors.size(); ++i)
	{
		Actor* actor = mWorld->actors[i];
		SCColliderBox* box = dynamic_cast<SCColliderBox*>(actor->getRootComponent());
		if (box)
		{
			if (!box->userData)
			{
				b2BodyDef groundBodyDef2;
				groundBodyDef2.type = box->_isDynamic ? b2_dynamicBody : b2_staticBody;
				groundBodyDef2.position = b2Vec2(actor->getActorLocation().x, actor->getActorLocation().y);
				b2Body* groundBody2 = mSimulation->CreateBody(&groundBodyDef2);

				b2PolygonShape groundShape2;
				groundShape2.SetAsBox(10.f, 10.f);
				groundBody2->CreateFixture(&groundShape2, 1.f);

				groundBody2->SetUserData(box);
				box->userData = groundBody2;

				box->rigidBody = new RigidBodyBox2D(groundBody2);
				
			}

			// Apply manual forces
			b2Body* boxColliderBody = (b2Body*)box->userData;
			

			CTransform transform = box->t;

			
			transform.position.x = boxColliderBody->GetPosition().x;
			transform.position.y = boxColliderBody->GetPosition().y;
			transform.rotation = Quaternion::fromMatrix(mat4::rotatez(boxColliderBody->GetAngle()));

			// Push the new physics transform back to the actor
			actor->setTransform(transform);
		}
	}
}

/// Debug draw the shapes
void Box2DSystem::debugDraw(GraphicsDevice* graphicsDevice)
{
	// draw ground too
	RectangleShape rc(FloatRect(0.f, 0.f, 500.f, 10.f), Color::Grass);	
	rc.setOrigin(rc.getSize() / 2.f);
	graphicsDevice->setModelMatrix(rc.getTransform().getMatrix());
	graphicsDevice->draw(rc);

	//Log("Found %d bodies", mSimulation->GetBodyCount());
	for (b2Body* body = mSimulation->GetBodyList(); body; body = body->GetNext())
	{
		b2Vec2 bp = body->GetPosition();
		float br = body->GetAngle();

		
		if (body->GetType() == b2_dynamicBody)
		{
			//Log("body is at %f", bp.y);

			RectangleShape rc(FloatRect(bp.x, bp.y, 10.f, 10.f), Color::Red);
			rc.setRotation(math::radianToDegree(br));
			rc.setOrigin(rc.getSize() / 2.f);
			graphicsDevice->setModelMatrix(rc.getTransform().getMatrix());
			graphicsDevice->draw(rc);
		}
	}
}

void Box2DSystem::spawnTestBox(Vector2D position, Vector2D dims)
{
	b2BodyDef groundBodyDef2;
	groundBodyDef2.type = b2_dynamicBody;
	groundBodyDef2.position = b2Vec2(position.x, position.y);
	b2Body* groundBody2 = mSimulation->CreateBody(&groundBodyDef2);

	b2PolygonShape groundShape2;
	groundShape2.SetAsBox(dims.x / 2.f, dims.y / 2.f);
	groundBody2->CreateFixture(&groundShape2, 1.f);
}


NEPHILIM_NS_END