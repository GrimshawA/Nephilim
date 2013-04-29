#include <Nephilim/KxScene.h>


#include "Nephilim/KinesisQueryCallback.h"

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

KxScene::KxScene()
: m_world(new b2World(b2Vec2(0.f, 1.4f)))
, m_velocityIterations(6)
, m_positionIterations(6)
, m_pixelsPerMeter(100)
{
	pickerMouseJoint = NULL;
	defaultGroundBody = NULL;
}

KxScene::KxScene(Vec2f gravity, int velocityIterations, int positionIterations)
: m_world(new b2World(b2Vec2(gravity.x, gravity.y)))
, m_positionIterations(positionIterations)
, m_velocityIterations(velocityIterations)
, m_pixelsPerMeter(100)
{
	pickerMouseJoint = NULL;
	defaultGroundBody = NULL;
}

/// Destroy the box2d world
KxScene::~KxScene()
{
	delete m_world;
}

/// Get the raw b2World object
b2World* KxScene::get()
{
	return m_world;
}

void KxScene::setVelocityIterations(int velocityIterations){
	m_velocityIterations = velocityIterations;
}
		
int KxScene::getVelocityIterations(){
	return m_velocityIterations;
};
		
void KxScene::setPositionIterations(int positionIterations){
	m_positionIterations = positionIterations;
};
		
int KxScene::getPositionIterations(){
	return m_positionIterations;
};

b2Body* KxScene::getGroundBody(){
	if(!defaultGroundBody)
		return createDefaultGroundBody();
	else
		return defaultGroundBody;
};

b2Body* KxScene::createDefaultGroundBody()
{
	b2BodyDef def;
	def.position = b2Vec2(toMeters(1), toMeters(1));
	def.type = b2_staticBody;

	b2PolygonShape box;
	box.SetAsBox(toMeters(2/2), toMeters(2/2));

	b2Body *body = m_world->CreateBody(&def);

	b2FixtureDef fixDef;
	fixDef.shape = &box;
	fixDef.density = 0.0f;
	fixDef.friction = 0.5f;
	fixDef.restitution = 0.5f;

	body->CreateFixture(&fixDef);

	return body;
}


void KxScene::update(float elapsedTime)
{
	m_world->Step(elapsedTime, m_velocityIterations, m_positionIterations);		
};

b2Body* KxScene::CreateQuickCircle(float x, float y, float r){
		b2BodyDef def;
		def.position = b2Vec2(toMeters(x),toMeters(y));
		def.type = b2_dynamicBody;

		b2CircleShape circle;
		circle.m_radius = toMeters(r);
		circle.m_p = b2Vec2(0, 0);		

		b2Body *body = m_world->CreateBody(&def);

		b2FixtureDef fixDef;
		fixDef.shape = &circle;
		fixDef.density = 1.0f;
		fixDef.friction = 0.5f;
		fixDef.restitution = 0.5f;

		body->CreateFixture(&fixDef);

		return body;
}

KxBody* KxScene::CreateQuickBox(float x, float y, float width, float height)
{
		b2BodyDef def;
		def.position = b2Vec2(toMeters(x), toMeters(y));
		def.type = b2_dynamicBody;
		

		b2PolygonShape box;
		box.SetAsBox(toMeters(width/2), toMeters(height/2));
	

		b2Body *body = m_world->CreateBody(&def);

		b2FixtureDef fixDef;
		fixDef.shape = &box;
		fixDef.density = 0.5f;
		fixDef.friction = 0.5f;
		fixDef.restitution = 0.f;


		body->CreateFixture(&fixDef);

		KxBody *bodyActor = new KxBody(body);
		body -> SetUserData(bodyActor);
		bodyActor->scene = this;
		bodyActor->m_body = body;
		return bodyActor;
}

b2Body* KxScene::CreateStaticBox(float x, float y, float width, float height){
		b2BodyDef def;
		def.position = b2Vec2(toMeters(x), toMeters(y));
		def.type = b2_staticBody;

		b2PolygonShape box;
		box.SetAsBox(toMeters(width/2), toMeters(height/2));

		b2Body *body = m_world->CreateBody(&def);

		b2FixtureDef fixDef;
		fixDef.shape = &box;
		//fixDef.density = 1.0f;
		fixDef.friction = 0.5f;
		fixDef.restitution = 0.1f;

		body->CreateFixture(&fixDef);

		KxBody* Actor = new KxBody(body);
		body->SetUserData(Actor);
		
		return body;
}

void KxScene::CreateQuickLine(float x, float y, float xx, float yy)
{
		/*b2BodyDef def;
		def.position = b2Vec2(ToMeters(xx)/ToMeters(x), ToMeters(yy)/ToMeters(y));
		def.type = b2_dynamicBody;

		b2PolygonShape box;
		b2Vec2 v[2];
		v[0] = b2Vec2(ToMeters(x), ToMeters(y));
		v[1] = b2Vec2(ToMeters(xx), ToMeters(yy));
		box.Set(v, 2);

		b2Body *body = CreateBody(&def);

		b2FixtureDef fixDef;
		fixDef.shape = &box;
		fixDef.density = 1.0f;
		fixDef.friction = 0.5f;
		fixDef.restitution = 0.5f;

		body->CreateFixture(&fixDef);*/
}

float KxScene::getPixelRatio()
{
	return m_pixelsPerMeter;
}


float KxScene::toMeters(float amount)
{
	return amount/getPixelRatio();
}

float KxScene::toPixels(float amount)
{
	return amount*getPixelRatio();
}

NEPHILIM_NS_END	