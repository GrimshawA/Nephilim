#ifndef MINIMAL_BUILD

#include "Nephilim/ComponentKinesis.h"
#include "Nephilim/KinesisWorld.h"
#include "Nephilim/Math.h"

PARABOLA_NAMESPACE_BEGIN

/// Creates the compound instance
ComponentPhysicsCompound::ComponentPhysicsCompound(const String &name) : EntityComponent(name){
	
};

/// Called when the component is attached
void ComponentPhysicsCompound::onAttach(){
	createBridge(Vec2f(100,400), Vec2f(800,400), 7);
	createBridge(Vec2f(100,200), Vec2f(800,200), 15);

	createRope(Vec2f(850, 200), 20, 12);
	createRope(Vec2f(870, 200), 20, 14);
	createRope(Vec2f(890, 200), 20, 17);
};

/// Make this compound a bridge (a few bodies, connected by joints)
void ComponentPhysicsCompound::createBridge(Vec2f bridgeStart, Vec2f bridgeEnd, int stepCount){
	/*KinesisWorld *sim = this->getParentEntity()->getParentSceneNode()->getLayerNode()->getKinesisWorld();
	if(sim){
		// A proper tree will always have the remaining calls valid.

		float distance = Math::distance(bridgeStart, bridgeEnd);
		float gap = 2.f;
		float stepWidth = (distance / stepCount);		
		float altStepWidth = sim->ToMeters(stepWidth);

		b2Body* left_support = sim->CreateStaticBox(bridgeStart.x, bridgeStart.y, 5, 5);
		b2Body* right_support = sim->CreateStaticBox(bridgeEnd.x, bridgeEnd.y, 5, 5);


		float xoffset = stepWidth/2;
		b2Body *oldbody = NULL;
		b2Body *body = NULL;
		float old_x_right;
		for(int i = 0; i < stepCount; i++){
			body = sim->CreateQuickBox(bridgeStart.x + xoffset, bridgeStart.y, stepWidth, 3);
			
			if(oldbody){
				// connect to the previous
				b2RevoluteJointDef def;
				b2Vec2 anchor = body->GetWorldCenter();
				anchor.x -= altStepWidth/2;
				def.Initialize(oldbody, body, anchor);
				sim->CreateJoint(&def);
			}
			else if(!oldbody){
				// First one
				b2RevoluteJointDef def;
				def.Initialize(left_support, body, b2Vec2(sim->ToMeters(bridgeStart.x),sim->ToMeters(bridgeStart.y)));
				sim->CreateJoint(&def);
			}
	
			oldbody = body;

			xoffset += stepWidth;		
		}
		// Now connect the last one.
		// First one
		b2RevoluteJointDef def;
		def.Initialize(right_support, body, b2Vec2(sim->ToMeters(bridgeEnd.x),sim->ToMeters(bridgeEnd.y)));
		sim->CreateJoint(&def);
	}*/
};

/// Make this compound own a bridge
void ComponentPhysicsCompound::createRope(Vec2f ropeStart,float fraglen, int fragments){
	/*KinesisWorld *sim = this->getParentEntity()->getParentSceneNode()->getLayerNode()->getKinesisWorld();
	if(sim){
		// A proper tree will always have the remaining calls valid.
	
		
		float altFragLen = sim->ToMeters(fraglen);

		b2Body* left_support = sim->CreateStaticBox(ropeStart.x, ropeStart.y, 5, 5);
		

		float xoffset = fraglen/2;
		b2Body *oldbody = NULL;
		b2Body *body = NULL;
		float old_x_right;
		for(int i = 0; i < fragments; i++){
			body = sim->CreateQuickBox(ropeStart.x + xoffset, ropeStart.y, fraglen, 2);

			if(oldbody){
				// connect to the previous
				b2RevoluteJointDef def;
				b2Vec2 anchor = body->GetWorldCenter();
				anchor.x -= altFragLen/2;
				def.Initialize(oldbody, body, anchor);
				sim->CreateJoint(&def);
			}
			else if(!oldbody){
				// First one
				b2RevoluteJointDef def;
				def.Initialize(left_support, body, b2Vec2(sim->ToMeters(ropeStart.x),sim->ToMeters(ropeStart.y)));
				sim->CreateJoint(&def);
			}

			oldbody = body;

			xoffset += fraglen;		
		}

	}*/
};

PARABOLA_NAMESPACE_END

#endif