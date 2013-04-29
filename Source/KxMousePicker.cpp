#include <Nephilim/KxMousePicker.h>
#include <Nephilim/KinesisQueryCallback.h>
#include <Nephilim/KxScene.h>

NEPHILIM_NS_BEGIN

KxMousePicker::KxMousePicker()
{
	joint = NULL;
}

void KxMousePicker::attachAt(float x, float y)
{
	KinesisQueryCallback query;
	b2AABB aabb;
	float real_x_mouse = scene->toMeters(x);
	float real_y_mouse = scene->toMeters(y);

	aabb.lowerBound.Set(real_x_mouse - 0.002f, real_y_mouse - 0.002f);
	aabb.upperBound.Set(real_x_mouse + 0.002f, real_y_mouse + 0.002f);


	scene->get()->QueryAABB(&query, aabb);

	for(unsigned int i = 0; i < query.getFixtureCount(); i++){

		if(query.getFixture(i)->GetBody()->GetType() == b2_staticBody){

		}
		else{
			if(query.getFixture(i)->TestPoint(b2Vec2(real_x_mouse, real_y_mouse))){
				b2MouseJointDef jointDef;
				jointDef.bodyA = scene->getGroundBody();
				jointDef.bodyB = query.getFixture(i)->GetBody();
				jointDef.target = b2Vec2(real_x_mouse, real_y_mouse);
				jointDef.maxForce = 10000;
				//jointDef.frequencyHz = 1/60;
				query.getFixture(i)->GetBody()->SetAwake(true);

				joint = (b2MouseJoint*)scene->get()->CreateJoint(&jointDef);
			}

		}
	}
}

void KxMousePicker::update(float x, float y)
{
	if(joint) joint->SetTarget(b2Vec2(scene->toMeters(x),scene->toMeters(y)));
}

void KxMousePicker::detach()
{
	if(joint) 
	{
		scene->get()->DestroyJoint(joint);
		joint = NULL;
	}
}

NEPHILIM_NS_END