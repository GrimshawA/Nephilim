#include <Nephilim/KxRope.h>
#include <Nephilim/KxScene.h>

#include <Nephilim/MMath.h>

NEPHILIM_NS_BEGIN	

/// Make this compound a bridge (a few bodies, connected by joints)
void KxRopeBuilder::createBridge(Vec2f bridgeStart, Vec2f bridgeEnd, int stepCount){	
	if(sim){
		// A proper tree will always have the remaining calls valid.

		float distance = math::distance(bridgeStart, bridgeEnd);
		float gap = 2.f;
		float stepWidth = (distance / stepCount);		
		float altStepWidth = sim->toMeters(stepWidth);

		b2Body* left_support = sim->CreateStaticBox(bridgeStart.x, bridgeStart.y, 5, 5);
		b2Body* right_support = sim->CreateStaticBox(bridgeEnd.x, bridgeEnd.y, 5, 5);


		float xoffset = stepWidth/2;
		b2Body *oldbody = NULL;
		b2Body *body = NULL;
		float old_x_right;
		for(int i = 0; i < stepCount; i++){
			body = sim->CreateQuickBox(bridgeStart.x + xoffset, bridgeStart.y, stepWidth, 3)->m_body;
			
			if(oldbody){
				// connect to the previous
				b2RevoluteJointDef def;
				b2Vec2 anchor = body->GetWorldCenter();
				anchor.x -= altStepWidth/2;
				def.Initialize(oldbody, body, anchor);
				sim->get()->CreateJoint(&def);
			}
			else if(!oldbody){
				// First one
				b2RevoluteJointDef def;
				def.Initialize(left_support, body, b2Vec2(sim->toMeters(bridgeStart.x),sim->toMeters(bridgeStart.y)));
				sim->get()->CreateJoint(&def);
			}
	
			oldbody = body;

			xoffset += stepWidth;		
		}
		// Now connect the last one.
		// First one
		b2RevoluteJointDef def;
		def.Initialize(right_support, body, b2Vec2(sim->toMeters(bridgeEnd.x),sim->toMeters(bridgeEnd.y)));
		sim->get()->CreateJoint(&def);
	}
};

/// Make this compound own a bridge
void KxRopeBuilder::createRope(Vec2f ropeStart,float fraglen, int fragments){	
	if(sim){
		// A proper tree will always have the remaining calls valid.	
		
		float altFragLen = sim->toMeters(fraglen);

		b2Body* left_support = sim->CreateStaticBox(ropeStart.x, ropeStart.y, 5, 5);
		

		float xoffset = fraglen/2;
		b2Body *oldbody = NULL;
		b2Body *body = NULL;
		float old_x_right;
		for(int i = 0; i < fragments; i++){
			body = sim->CreateQuickBox(ropeStart.x + xoffset, ropeStart.y, fraglen, 2)->m_body;

			if(oldbody){
				// connect to the previous
				b2RevoluteJointDef def;
				b2Vec2 anchor = body->GetWorldCenter();
				anchor.x -= altFragLen/2;
				def.Initialize(oldbody, body, anchor);
				sim->get()->CreateJoint(&def);
			}
			else if(!oldbody){
				// First one
				b2RevoluteJointDef def;
				//def.enableMotor = true;
				//def.motorSpeed = 1.0f;
				//def.maxMotorTorque = 100000.0f;
				def.Initialize(left_support, body, b2Vec2(sim->toMeters(ropeStart.x),sim->toMeters(ropeStart.y)));
				sim->get()->CreateJoint(&def);
			}

			oldbody = body;

			xoffset += fraglen;		
		}

	}
};

NEPHILIM_NS_END