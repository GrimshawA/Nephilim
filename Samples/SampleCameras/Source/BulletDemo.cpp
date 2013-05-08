#include "SampleBasic.h"
#include <Nephilim/Geometry.h>
#include <Nephilim/CGL.h>
#include <Nephilim/MMath.h>
#include <Nephilim/Texture.h>

#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletDynamics/Character/btKinematicCharacterController.h>
#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>

btBroadphaseInterface* broadphase = new btDbvtBroadphase();
btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
btDiscreteDynamicsWorld* dynamicsWorld = NULL;

btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);

btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));


btCollisionShape* fallShape = new btBoxShape(btVector3(1,1,1));
btDefaultMotionState* fallMotionState =
	new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
btScalar mass = 1;
btVector3 fallInertia(0,0,0);
btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);

btKinematicCharacterController* m_character = NULL;
btGhostObject *m_ghostObject = NULL;

struct BoxSim
{
	btRigidBody* rigidBody;
	GeometryData cube;
	mat4 model;
	Texture* texture;
	vec3 position;
};
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

sf::SoundBuffer buffer;
sf::Sound sound;
std::vector<BoxSim> boxes;

Texture mGrassTexture;
GeometryData ground;

std::map<String, Texture*> textures;

bool focus = true;

GeometryData IronMan;
GeometryData House;
Texture IronManTexture;

class FirstPersonCamera
{
public:
	mat4 matrix;

	float current_x_angle;
	float current_y_angle;

	FirstPersonCamera()
	{
		eye = vec3(10,3,25);
		center = vec3(0,3,0);
		up = vec3(0,1,0);

		current_x_angle = Math::pi / 4;
		current_y_angle = Math::pi / 2;

		forward = false;
		forwardSpeed = 10;
		backward = false;
		strafeLeft = false;
		strafeRight = false;
		strafeSpeed = 7;

		lookUp = false;
		lookDown = false;
		lookAngleSpeed = 0.1;

		matrix = mat4::lookAt(eye, center, up);
	}

	void update(float time)
	{
		/*if(forward)
		{
			vec3 direction = vec3(-sin(current_x_angle),0, cos(current_x_angle));
			direction.normalize();
			//Log("Angle: %f, Direction: %f, %f, %f", current_x_angle, direction.x, direction.y, direction.z);
			eye += direction * time * forwardSpeed * -1;
		}*/
		/*if(backward)
		{
			vec3 direction = vec3(-sin(current_x_angle),0, cos(current_x_angle));
			direction.normalize();
			//Log("Angle: %f, Direction: %f, %f, %f", current_x_angle, direction.x, direction.y, direction.z);
			eye += direction * time * forwardSpeed ;
		}
		if(strafeLeft)
		{
			vec3 direction = vec3(cos(current_x_angle),0, sin(current_x_angle));
			eye += direction * time * forwardSpeed * -1;
		}
		if(strafeRight)
		{
			vec3 direction = vec3(cos(current_x_angle),0, sin(current_x_angle));
			eye += direction * time * forwardSpeed;
		}*/
		if(lookUp)
		{
			// look a bit higher
			vec3 dir = center - eye;
			float distance = dir.length();

			// compute new direction
			vec3 newDir = (mat4::rotate(0, lookAngleSpeed * time, 0).transposed() * vec4(dir, 1.f)).xyz();
			newDir.normalize();

			center = eye + newDir * distance;
		}
		if(lookDown)
		{

		}

		matrix = mat4::identity;
		matrix = mat4::translate(-eye.x,-eye.y,-eye.z);
		matrix = mat4::rotatey(current_x_angle) * matrix;
		matrix = mat4::rotatex(current_y_angle) * matrix;
	//	matrix = mat4::rotatez(Math::pi) * matrix;
	}

	void handle(Event event)
	{
		if(event.type == Event::KeyPressed)
		{
			if(event.key.code == Keyboard::W)
			{
				forward = true;
			}
			if(event.key.code == Keyboard::S)
			{
				backward = true;
			}
			if(event.key.code == Keyboard::A)
			{
				strafeLeft = true;
			}
			if(event.key.code == Keyboard::D)
			{
				strafeRight = true;
			}
			if(event.key.code == Keyboard::Up)
			{
				lookUp = true;
			}
		}

		if(event.type == Event::KeyReleased)
		{
			if(event.key.code == Keyboard::W)
			{
				forward = false;
			}
			if(event.key.code == Keyboard::S)
			{
				backward = false;
			}
			if(event.key.code == Keyboard::A)
			{
				strafeLeft = false;
			}
			if(event.key.code == Keyboard::D)
			{
				strafeRight = false;
			}
			if(event.key.code == Keyboard::Up)
			{
				lookUp = false;
			}
		}		
	}

	void mouseMove(int x, int y)
	{
		vec2 movement = vec2(x, y);
		static vec2 oldPos = movement;
		vec2 offset = (movement - vec2(500,500) )* 0.005; // offset angles of the camera

		//Log("Mouse: %f, %f", offset.x, offset.y);

		vec3 dir = center - eye;
		float distance = dir.length();
		dir.normalize();

		// compute new direction
		//vec3 newDir = (mat4::rotate(offset.y, offset.x, 0).transposed() * vec4(dir, 0.f)).xyz();
		//newDir.normalize();
		//center = eye + newDir * distance;

		sound.setPitch(sound.getPitch() - offset.y);
		Log("Sound pitch: %f", sound.getPitch());
		

		float newHAngle = Math::computeAngle(eye.x, eye.z, center.x, center.z) + offset.x;
		float newVAngle = Math::computeAngle(eye.z, eye.y, center.z, center.y) + offset.y;

		vec2 upwardsV = vec2(cos(newVAngle), sin(newVAngle));

		vec3 newDir(cos(newHAngle) * distance, sin(newVAngle) * distance, sin(newHAngle) * distance);
		center = eye + newDir;

		oldPos = movement;

		current_x_angle += offset.x;
		current_y_angle += offset.y;
	}

	bool forward; float forwardSpeed;
	bool backward;
	bool strafeLeft, strafeRight; float strafeSpeed;

	bool lookUp, lookDown; float lookAngleSpeed;

	vec3 eye, center, up;
};

FirstPersonCamera camera;



void SampleUI::onCreate()
{	

	buffer.loadFromFile("engine.WAV");
	sound.setLoop(true);
	sound.setBuffer(buffer);
	sound.play();

	if(threshold(5.f, 1.f) == 5.5f)
	{
		Log("5.5f is within [4.f,6.f]");
	}


	IronManTexture.loadFromFile("maps/mk7.png");
	IronManTexture.setRepeated(true);
	IronMan.loadFromFile("ironman.ngx");
	House.loadFromFile("torusknot.ngx");

	//House.randomFaceColors();
	
	textures["wood"] = new Texture();
	textures["wood"]->loadFromFile("wood.png");

	textures["brick"] = new Texture();
	textures["brick"]->loadFromFile("brick.png");


	mGrassTexture.loadFromFile("grass.png");
	mGrassTexture.setRepeated(true);

	ground.addPlane(1000,1000,0);
	ground.setAllColors(Color::White);
	ground.scaleUV(160);

	btVector3 worldMin(-100,-100,-100);
	btVector3 worldMax(100,100,100);
	btAxisSweep3* sweepBP = new btAxisSweep3(worldMin,worldMax);

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,sweepBP,solver,collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0,-8,0));

	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));

	groundRigidBodyCI.m_friction = 2.f;

	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);

	dynamicsWorld->addRigidBody(groundRigidBody);


	/// Add character capsule
	btTransform startTransform;
	startTransform.setIdentity ();
	//startTransform.setOrigin (btVector3(0.0, 4.0, 0.0));
	startTransform.setOrigin (btVector3(0,5,0));
	
	m_ghostObject = new btPairCachingGhostObject();
	m_ghostObject->setWorldTransform(startTransform);
	sweepBP->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	btScalar characterHeight=1.75;
	btScalar characterWidth =1.75;
	btConvexShape* capsule = new btCapsuleShape(characterWidth,characterHeight);
	m_ghostObject->setCollisionShape (capsule);
	m_ghostObject->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);

	btScalar stepHeight = btScalar(0.2f);
	m_character = new btKinematicCharacterController ((btPairCachingGhostObject*)m_ghostObject,capsule,stepHeight);

	dynamicsWorld->addCollisionObject(m_ghostObject,btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter|btBroadphaseProxy::AllFilter);

	dynamicsWorld->addAction(m_character);

	dynamicsWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(m_ghostObject->getBroadphaseHandle(),dynamicsWorld->getDispatcher());
	dynamicsWorld->getDispatchInfo().m_allowedCcdPenetration=0.00001f;

//	camera.eye = vec3(m_ghostObject->getWorldTransform()->getOrigin().x, m_ghostObject->getWorldTransform()->getOrigin().y, m_ghostObject->getWorldTransform()->getOrigin().z);
}

void SampleUI::onEvent(Event &event)
{
	camera.handle(event);

	if(event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
	{
		m_character->setJumpSpeed(12);
		m_character->jump();
	}

	if(event.type == Event::KeyPressed && event.key.code == Keyboard::W)
	{
	
	}
	if(event.type == Event::KeyReleased && event.key.code == Keyboard::W)
	{
		m_character->setWalkDirection(btVector3(0,0,0));
	}

	if(event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
	{
		close();
	}

	if(event.type == Event::GainedFocus)
	{
		focus = true;
	}
	if(event.type == Event::LostFocus)
	{
		focus = false;
	}
	if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{		
		vec3 direction = vec3(-sin(camera.current_x_angle),0, cos(camera.current_x_angle));
		direction.normalize();
		vec3 finalPosition = camera.eye + direction * 4 * -1;

		btCollisionShape* boxShape = new btBoxShape(btVector3(1,1,1));
		btDefaultMotionState* fallMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(finalPosition.x,2,finalPosition.z)));
		btScalar mass2 = 150;
		btVector3 fallInertia2(0,0,0);
		boxShape->calculateLocalInertia(mass2,fallInertia2);
		btRigidBody::btRigidBodyConstructionInfo newBoxCI(mass2,fallMotionState2,boxShape,fallInertia2);		

		// Add first cube
		BoxSim box;
		box.cube.addBox(2,2,2);
		box.cube.randomFaceColors();
		box.cube.setAllColors(Color::White);
		box.texture = textures["brick"];
		box.rigidBody = new btRigidBody(newBoxCI);
		dynamicsWorld->addRigidBody(box.rigidBody);
		boxes.push_back(box);
		Log("New Box added");
	}
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::T)
	{

		btCollisionShape* boxShape = new btBoxShape(btVector3(0.2,0.2,0.2));
		btDefaultMotionState* fallMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(Math::random(-5,5),30,Math::random(-1,1))));
		btScalar mass2 = 50;
		btVector3 fallInertia2(0,0,0);
		boxShape->calculateLocalInertia(mass2,fallInertia2);
		btRigidBody::btRigidBodyConstructionInfo newBoxCI(mass2,fallMotionState2,boxShape,fallInertia2);		

		// Add first cube
		BoxSim box;
		box.cube.addBox(0.4,0.4,0.4);
		box.cube.randomFaceColors();
		box.cube.setAllColors(Color::White);
		if(Math::randomInt(1, 10) > 5) box.texture = textures["brick"]; else box.texture = textures["wood"];
		box.rigidBody = new btRigidBody(newBoxCI);
		dynamicsWorld->addRigidBody(box.rigidBody);
		boxes.push_back(box);
		Log("New Box added");
	}
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::E)
	{
		vec3 direction = vec3(-sin(camera.current_x_angle),0, cos(camera.current_x_angle));
		direction.normalize();
		vec3 finalPosition = camera.eye + direction * 25 * -1;

		float dim = Math::random(0.5, 2.5);
		btCollisionShape* boxShape = new btBoxShape(btVector3(dim,dim,dim));
		btDefaultMotionState* fallMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(finalPosition.x,25,finalPosition.z)));
		btScalar mass2 = 30 * dim * 2;
		btVector3 fallInertia2(0,0,0);
		boxShape->calculateLocalInertia(mass2,fallInertia2);
		btRigidBody::btRigidBodyConstructionInfo newBoxCI(mass2,fallMotionState2,boxShape,fallInertia2);		

		// Add first cube
		BoxSim box;
		box.cube.addBox(dim*2,dim*2,dim*2);
		box.cube.randomFaceColors();
		box.cube.setAllColors(Color::White);
		if(Math::randomInt(1, 10) > 5) box.texture = textures["brick"]; else box.texture = textures["wood"];
		box.rigidBody = new btRigidBody(newBoxCI);
		dynamicsWorld->addRigidBody(box.rigidBody);
		boxes.push_back(box);
		Log("New Box added");
	}

	if(event.type == Event::MouseMoved)
	{
	
		camera.mouseMove(event.mouseMove.x, event.mouseMove.y);

	}

	if(event.type == Event::KeyPressed && event.key.code == Keyboard::B)
	{
		// explosion
		for(int i = 0; i < boxes.size(); ++i)
		{
			if((boxes[i].position - vec3(0,0,0)).length() < 20)
			{
				boxes[i].rigidBody->setActivationState(1);
				boxes[i].rigidBody->applyCentralImpulse(btVector3(boxes[i].position.x * 300, boxes[i].position.y * 400, boxes[i].position.z * 300));
			}
		}
	}	
}

void SampleUI::onUpdate(Time time)
{ 	

	camera.update(time.asSeconds());

	//dynamicsWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(m_ghostObject->getBroadphaseHandle(),dynamicsWorld->getDispatcher());

	for(int i = 0; i < 4; i++)
	{
		dynamicsWorld->stepSimulation(time.asSeconds() / 4, 100);
	}

	btTransform trans;
	fallRigidBody->getMotionState()->getWorldTransform(trans);

	for(int i = 0;  i < boxes.size(); i++)
	{
		btTransform trans;
		boxes[i].rigidBody->getMotionState()->getWorldTransform(trans);

		btVector3 pos = trans.getOrigin();
		btVector3 rot = trans.getRotation().getAxis();
		//float angle = Math::degreeToRadian(trans.getRotation().getAngle());
		float angle = trans.getRotation().getAngle();
		//Log("Angle obtained: %f Axis (%f,%f,%f)", angle, rot.getX(), rot.getY(), rot.getZ());
		boxes[i].position = vec3(pos.getX(), pos.getY(), pos.getZ());
		//boxes[i].model = mat4::translate(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
		//boxes[i].model = boxes[i].model * mat4::rotate(rot.getX() * angle, rot.getY() * angle, rot.getZ() * angle);

		btScalar mt[16];
		trans.getOpenGLMatrix(mt);
		boxes[i].model = mat4(mt);
		//boxes[i].model = mat4::translate(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()) * mat4::rotate(rot.getX() * angle, rot.getY() * angle, rot.getZ() * angle);
	}

	static int counter = 0;
	counter++;
	if(focus && counter % 8) getWindow().setMousePosition(Vec2i(500,500));

	camera.eye = vec3(m_ghostObject->getWorldTransform().getOrigin().getX(), m_ghostObject->getWorldTransform().getOrigin().getY(), m_ghostObject->getWorldTransform().getOrigin().getZ());


	if(camera.forward)
	{
		vec3 direction = vec3(-sin(camera.current_x_angle),0, cos(camera.current_x_angle));
		direction.normalize();
		//Log("Angle: %f, Direction: %f, %f, %f", current_x_angle, direction.x, direction.y, direction.z);	
		vec3 finalPosition = camera.eye + direction * 2 * -1;
		direction *= -1;
		btVector3 walkDirection = btVector3(direction.x, direction.y, direction.z);
		btScalar walkVelocity = btScalar(1.1) * 6.0; // 4 km/h -> 1.1 m/s
		btScalar walkSpeed = walkVelocity * 1 / 60.f;
		m_character->setWalkDirection(walkDirection*walkSpeed);
	}
	if(camera.backward)
	{
		vec3 direction = vec3(-sin(camera.current_x_angle),0, cos(camera.current_x_angle));
		direction.normalize();
		//Log("Angle: %f, Direction: %f, %f, %f", current_x_angle, direction.x, direction.y, direction.z);	
		vec3 finalPosition = camera.eye + direction * 2 * -1;
		direction *= -1;
		btVector3 walkDirection = btVector3(direction.x, direction.y, direction.z);
		btScalar walkVelocity = btScalar(1.1) * 6.0; // 4 km/h -> 1.1 m/s
		btScalar walkSpeed = walkVelocity * 1 / 60.f;
		m_character->setWalkDirection(-walkDirection*walkSpeed);
	}
}

void SampleUI::onRender()
{	
	getRenderer()->setDefaultViewport();
	getRenderer()->setDepthTestEnabled(true);
	getRenderer()->clearAllBuffers();
	getRenderer()->setClearColor(Color::Blue);
	getRenderer()->setProjectionMatrix(mat4::perspective(45, 1024.f / 768.f, 1.f, 1000.f));
	getRenderer()->setViewMatrix(camera.matrix);

	for(int i = 0;  i < boxes.size(); i++)
	{
		boxes[i].texture->bind();
		getRenderer()->setModelMatrix(boxes[i].model);
		getRenderer()->enableVertexAttribArray(0);
		getRenderer()->enableVertexAttribArray(1);
		getRenderer()->enableVertexAttribArray(2);
		getRenderer()->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &boxes[i].cube.m_vertices[0]);
		getRenderer()->setVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, true, 0, &boxes[i].cube.m_colors[0]);
		getRenderer()->setVertexAttribPointer(2, 2, GL_FLOAT, false, 0, &boxes[i].cube.m_texCoords[0]);
		getRenderer()->drawArrays(Render::Primitive::Triangles, 0, boxes[i].cube.m_vertices.size());
		getRenderer()->setModelMatrix(mat4::identity);
	}

	getRenderer()->setModelMatrix(mat4::identity);	
	mGrassTexture.bind();
	getRenderer()->enableVertexAttribArray(0);
	getRenderer()->enableVertexAttribArray(1);
	getRenderer()->enableVertexAttribArray(2);
	getRenderer()->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &ground.m_vertices[0]);
	getRenderer()->setVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, true, 0, &ground.m_colors[0]);
	getRenderer()->setVertexAttribPointer(2, 2, GL_FLOAT, false, 0, &ground.m_texCoords[0]);
	getRenderer()->drawArrays(Render::Primitive::Triangles, 0, ground.m_vertices.size());
	

	static float angle = 0; angle+=0.005;
	getRenderer()->setModelMatrix(mat4::rotatey(angle) * mat4::translate(0,1,0) * mat4::scale(3,3,3));
	IronManTexture.bind();
	getRenderer()->enableVertexAttribArray(0);
	getRenderer()->enableVertexAttribArray(1);
	getRenderer()->enableVertexAttribArray(2);
	getRenderer()->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &IronMan.m_vertices[0]);
	getRenderer()->setVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, true, 0, &IronMan.m_colors[0]);
	getRenderer()->setVertexAttribPointer(2, 2, GL_FLOAT, false, 0, &IronMan.m_texCoords[0]);
	getRenderer()->drawArrays(Render::Primitive::Triangles, 0, IronMan.m_vertices.size());
	getRenderer()->disableVertexAttribArray(0);
	getRenderer()->disableVertexAttribArray(1);
	getRenderer()->disableVertexAttribArray(2);
	getRenderer()->setModelMatrix(mat4());
	getRenderer()->setDefaultTexture();

	getRenderer()->setModelMatrix(mat4::translate(30,5,0) * mat4::scale(0.05,0.05,0.05) * mat4::rotatex(Math::pi/2 + Math::pi));
	IronManTexture.bind();
	getRenderer()->setDefaultTexture();

	getRenderer()->enableVertexAttribArray(0);
	getRenderer()->enableVertexAttribArray(1);
	//getRenderer()->enableVertexAttribArray(2);
	getRenderer()->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &House.m_vertices[0]);
	getRenderer()->setVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, true, 0, &House.m_colors[0]);
	//getRenderer()->setVertexAttribPointer(2, 2, GL_FLOAT, false, 0, &IronMan.m_texCoords[0]);
	getRenderer()->drawArrays(Render::Primitive::Triangles, 0, House.m_vertices.size());
	getRenderer()->disableVertexAttribArray(0);
	getRenderer()->disableVertexAttribArray(1);
	getRenderer()->disableVertexAttribArray(2);
	getRenderer()->setModelMatrix(mat4());
	getRenderer()->setDefaultTexture();



}
