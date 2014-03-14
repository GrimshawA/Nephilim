#include "SampleBasic.h"

#include <Nephilim/Geometry.h>
#include <Nephilim/Image.h>
#include <Nephilim/Surface.h>
#include <Nephilim/CGL.h>
#include <Nephilim/NxMath.h>    
#include <Nephilim/Texture.h>
#include <Nephilim/Quaternion.h>

#include <Nephilim/SceneGraph.h>
#include <Nephilim/Camera.h>
#include <Nephilim/InputGrabber.h>
#include <Nephilim/BxScene.h>
#include <Nephilim/BxDraw.h>
#include <Nephilim/Font.h>
#include <Nephilim/BxVehicle.h>
#include <Nephilim/Text.h>

#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletDynamics/Character/btKinematicCharacterController.h>
#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>
FPSCamera fpsCamera;

#include "SKNLoader.h"
#include "SKLLoader.h"
#include "ANMLoader.h"

GeometryData champion;
Texture championTexture;
SkeletonSKL skeleton;
AnimationANM animations;

Shader rigShader;

static int currentFrame = 20;

void getBoneTransforms(mat4* transforms, AnimationANM& animation, SkeletonSKL& skeleton)
{
	// lets try to get frame 20 for trying it out

	mat4 localBoneTransforms[128];

	for(int i = 0; i < skeleton.bones.size(); ++i)
	{
		int bone_id = skeleton.findIDByName(skeleton.bones[i].name);

		// Get transformed matrix of the animation
		mat4 absoluteBoneTransform = animation.getAbsoluteTransform(animation.NameToIndex(skeleton.bones[i].name), skeleton, currentFrame);

		transforms[i] = absoluteBoneTransform * skeleton.bones[i].inverseBindPose;
	}
}

String getFileContents(const String& filename)
{
	File myFile(filename, IODevice::TextRead);
	if(!myFile)
		return "";

	String contents;

	while(!myFile.atEnd())
		contents += myFile.getChar();

	contents += '\0';

	return contents;
}

void SampleUI::onCreateExp()
{
	// Time to load the champion
	SKNLoader::Load(champion, "K:\\Users\\Hellhound\\Desktop\\lolmodels\\model.skn");
	champion.m_useNormals = false;

	championTexture.loadFromFile("K:\\Users\\Hellhound\\Desktop\\lolmodels\\texture.png");

	skeleton.Load("K:\\Users\\Hellhound\\Desktop\\lolmodels\\skeleton.skl");
	animations.Load("K:\\Users\\Hellhound\\Desktop\\lolmodels\\Caitlyn_cop_Run.anm");
	//animations.Load("K:\\Users\\Hellhound\\Desktop\\lolmodels\\Caitlyn_cop_Idle2.anm");
	//animations.Load("K:\\Users\\Hellhound\\Desktop\\lolmodels\\Caitlyn_Dance.anm");
	
	// remap bone indices
	for(int i = 0; i < champion.boneIDs.size(); ++i)
	{
		champion.boneIDs[i].x = skeleton.boneIndexToActualBone[champion.boneIDs[i].x];
		champion.boneIDs[i].y = skeleton.boneIndexToActualBone[champion.boneIDs[i].y];
		champion.boneIDs[i].z = skeleton.boneIndexToActualBone[champion.boneIDs[i].z];
		champion.boneIDs[i].w = skeleton.boneIndexToActualBone[champion.boneIDs[i].w];
	}

	rigShader.loadShader(Shader::VertexUnit, getFileContents("K:\\Users\\Hellhound\\Desktop\\lolmodels\\rigged.vert"));
	rigShader.loadShader(Shader::FragmentUnit, getFileContents("K:\\Users\\Hellhound\\Desktop\\lolmodels\\rigged.frag"));
	rigShader.addAttributeLocation(0, "vertex");
	rigShader.addAttributeLocation(1, "color");
	rigShader.addAttributeLocation(2, "texCoord");
	rigShader.addAttributeLocation(3, "in_Normal");
	rigShader.addAttributeLocation(4, "in_BoneID");
	rigShader.addAttributeLocation(5, "in_Weights");

	if(rigShader.create())
	{
		Log("Rigging shader created");
	}
	rigShader.bind();

	String vertexSource = getFileContents("K:\\Users\\Hellhound\\Desktop\\lolmodels\\rigged.vert");

	//std::cout << vertexSource << std::endl;
}

void SampleUI::onRenderExp()
{
	championTexture.bind();

	getRenderer()->setShader(rigShader);
	getRenderer()->setModelMatrix(mat4::translate(0,-2.5f,4) * mat4::scale(0.03,0.03,0.03));
	getRenderer()->setProjectionMatrix(mat4::perspective(80, static_cast<float>(getSurface().getWidth()) / static_cast<float>(getSurface().getHeight()), 1.f, 1000.f));
	getRenderer()->setViewMatrix(fpsCamera.getMatrix());

	mat4 boneTransforms[128];
	for(int i = 0; i < 128; ++i)
		boneTransforms[i] = mat4::identity;

	// update the transforms with the animation
	getBoneTransforms(boneTransforms, animations, skeleton);

	int location = glGetUniformLocation(rigShader.m_id, "u_BoneTransform");
	glUniformMatrix4fv(location, 128, false, reinterpret_cast<float*>(&boneTransforms[0]));

	if(location == -1)
	{
		//Log("Invalid uniform array");
	}

	getRenderer()->draw(champion);
	getRenderer()->setDefaultShader();
}

btKinematicCharacterController* m_character = NULL;
btGhostObject *m_ghostObject = NULL;

BxScene bulletWorld;

Image heightmap;

BxDraw* bulletDrawer;

#ifdef NEPHILIM_WINDOWS
#include <windows.h>
bool winappInFocus(GameCore* game)
{
	HWND handle = static_cast<HWND>(game->getWindow().getHandle());
	bool one = handle == GetFocus();
	bool two = handle == GetForegroundWindow();

	if(one != two) //strange 'half-focus': window is in front but you can't click anything - so we fix it
	{
		SetFocus(handle);
		SetForegroundWindow(handle);
	}

	return one && two;
}
#endif

class BoxSim : public SceneGraph3D::Node
{
public:
	BxBody* rigidBody;
	GeometryData cube;
	mat4 model;
	Texture* texture;
	float mass;
	vec3 position;
};
SceneGraph3D scene;
std::vector<BoxSim> boxes;
Texture mGrassTexture;
Texture mWaterTexture;
GeometryData ground;
std::map<String, Texture*> textures;
bool focus = true;
GeometryData IronMan;
GeometryData House;
Texture IronManTexture;
InputGrabber input;

Font fnt;
Text txt;
GeometryData terrain;

static const float GRID_SIZE = 1.0f;
static const float HEIGHT_FACTOR = 0.1f;
static const float TEXTURE_INCREMENT = 0.2f;
#include <bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
float current_height = -2.f;
float current_z = 0.f;

BxVehicle* vehicle;

GeometryData vehicleChassis;
GeometryData vehicleWheel;

void SampleUI::onCreate()
{	
	getWindow().setSize(1920, 1080);
	getWindow().setFullscreen(true);

	onCreateExp();





	fnt.loadFromFile("DejaVuSans.ttf");
	txt.setFont(fnt);
	txt.setString("Mr. Tony Stark");
	txt.setColor(Color::Orange);

	heightmap.loadFromFile("heightmap.png");

	Uint8* heightmapRaw = new Uint8[heightmap.getSize().x * heightmap.getSize().y];

	int k = 0;
	for( Uint16 x = 0; x < heightmap.getSize().x; ++x )
	{		
		for( Uint16 y = 0; y < heightmap.getSize().y; ++y )
		{
		
			if(x < heightmap.getSize().x-1 && y < heightmap.getSize().y - 1)
			{
				terrain.m_vertices.push_back(vec3(x * GRID_SIZE + GRID_SIZE, heightmap.getPixel(x+1,y).r * HEIGHT_FACTOR, y * GRID_SIZE));
				terrain.m_vertices.push_back(vec3(x * GRID_SIZE + GRID_SIZE, heightmap.getPixel(x+1,y+1).r * HEIGHT_FACTOR, y * GRID_SIZE + GRID_SIZE));
				terrain.m_vertices.push_back(vec3(x * GRID_SIZE, heightmap.getPixel(x,y+1).r * HEIGHT_FACTOR, y * GRID_SIZE + GRID_SIZE));

				terrain.m_texCoords.push_back(vec2(static_cast<float>( x+1 ) / static_cast<float>( heightmap.getSize().x), static_cast<float>( y ) / static_cast<float>( heightmap.getSize().y)));
				terrain.m_texCoords.push_back(vec2(static_cast<float>( x+1 ) / static_cast<float>( heightmap.getSize().x), static_cast<float>( y+1 ) / static_cast<float>( heightmap.getSize().y)));
				terrain.m_texCoords.push_back(vec2(static_cast<float>( x ) / static_cast<float>( heightmap.getSize().x), static_cast<float>( y ) / static_cast<float>( heightmap.getSize().y)));

				terrain.m_vertices.push_back(vec3(x * GRID_SIZE + GRID_SIZE, heightmap.getPixel(x+1,y).r * HEIGHT_FACTOR, y * GRID_SIZE));
				terrain.m_vertices.push_back(vec3(x * GRID_SIZE, heightmap.getPixel(x,y+1).r * HEIGHT_FACTOR, y * GRID_SIZE + GRID_SIZE));
				terrain.m_vertices.push_back(vec3(x * GRID_SIZE, heightmap.getPixel(x,y).r * HEIGHT_FACTOR, y * GRID_SIZE));

				terrain.m_texCoords.push_back(vec2(static_cast<float>( x +1) / static_cast<float>( heightmap.getSize().x), static_cast<float>( y ) / static_cast<float>( heightmap.getSize().y)));
				terrain.m_texCoords.push_back(vec2(static_cast<float>( x ) / static_cast<float>( heightmap.getSize().x), static_cast<float>( y +1) / static_cast<float>( heightmap.getSize().y)));
				terrain.m_texCoords.push_back(vec2(static_cast<float>( x ) / static_cast<float>( heightmap.getSize().x), static_cast<float>( y ) / static_cast<float>( heightmap.getSize().y)));
			}
			

			heightmapRaw[k++] = heightmap.getPixel(x,y).r;
		}
	}

	// Rotate the terrain

	mat4 trf = mat4::rotatey(math::pi/2);
	for(int i = 0; i < terrain.m_vertices.size(); ++i)
	{
		terrain.m_vertices[i].x -= heightmap.getSize().x * GRID_SIZE / 2 - GRID_SIZE/2;
		terrain.m_vertices[i].z -= heightmap.getSize().y * GRID_SIZE / 2 - GRID_SIZE/2;
		terrain.m_vertices[i].y -= 255 * HEIGHT_FACTOR  / 2;
		terrain.m_vertices[i] = (trf * vec4(terrain.m_vertices[i], 1.f)).xyz();

		terrain.m_vertices[i].z *= -1;
	}

	terrain.setAllColors(Color::White);
	terrain.scaleUV(100);


	IronManTexture.loadFromFile("maps/mk7.png");
	IronManTexture.setRepeated(true);
	IronMan.loadFromFile("ironman.ngx");
	House.loadFromFile("torusknot.ngx");

	textures["wood"] = new Texture();
	textures["wood"]->loadFromFile("wood.png");

	textures["brick"] = new Texture();
	textures["brick"]->loadFromFile("brick.png");

	Image grassimg; grassimg.loadFromFile("grass.png");
	mGrassTexture.loadFromImage(grassimg, false);
	mGrassTexture.setRepeated(true);

	mWaterTexture.loadFromFile("water.png");
	mWaterTexture.setRepeated(true);

	ground.addPlane(1000,1000,0);
	ground.setAllColors(Color::White);
	ground.scaleUV(160);

	btHeightfieldTerrainShape* terrainShape = new btHeightfieldTerrainShape(heightmap.getSize().x,heightmap.getSize().y, heightmapRaw, HEIGHT_FACTOR, 0, 255*HEIGHT_FACTOR, 1, PHY_UCHAR, false);
	//terrainShape->setLocalScaling(btVector3(100,0,100));
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));

	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0,groundMotionState,terrainShape,btVector3(0,0,0));

	groundRigidBodyCI.m_friction = 2.f;

	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);

	bulletWorld.m_scene->addRigidBody(groundRigidBody);

	terrainShape->setUseDiamondSubdivision(true);

	/// Add character capsule
	btTransform startTransform;
	startTransform.setIdentity ();
	//startTransform.setOrigin (btVector3(0.0, 4.0, 0.0));
	startTransform.setOrigin (btVector3(0,35,0));
	
	m_ghostObject = new btPairCachingGhostObject();
	m_ghostObject->setWorldTransform(startTransform);
	bulletWorld.m_bp->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	btScalar characterHeight=1.75;
	btScalar characterWidth =1.75;
	btConvexShape* capsule = new btCapsuleShape(characterWidth,characterHeight);
	m_ghostObject->setCollisionShape (capsule);
	m_ghostObject->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);

	btScalar stepHeight = btScalar(0.5f);
	m_character = new btKinematicCharacterController ((btPairCachingGhostObject*)m_ghostObject,capsule,stepHeight);

	bulletWorld.m_scene->addCollisionObject(m_ghostObject,btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter|btBroadphaseProxy::AllFilter);

	bulletWorld.m_scene->addAction(m_character);

	bulletWorld.m_scene->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(m_ghostObject->getBroadphaseHandle(),bulletWorld.m_scene->getDispatcher());
	bulletWorld.m_scene->getDispatchInfo().m_allowedCcdPenetration=0.00001f;

	//m_character->setGravity(0);

	bulletDrawer = new BxDraw();
	bulletDrawer->setDebugMode(BxDraw::DBG_DrawWireframe);
	bulletDrawer->renderer = getRenderer();
	bulletWorld.m_scene->setDebugDrawer(bulletDrawer);

	// Finally the vehicle
	vehicle = new BxVehicle(bulletWorld);

	vehicleChassis.addBox(2,1,4);
	vehicleChassis.setAllColors(Color::White);

	vehicleWheel.addBox(1,1,1);
	vehicleWheel.setAllColors(Color::White);
}

void SampleUI::makeBox(vec3 position, vec3 size, const String& texture, float mass)
{
	btCollisionShape* boxShape = new btBoxShape(btVector3(size.x,size.y,size.z));
	btDefaultMotionState* fallMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(position.x, position.y, position.z)));
	btScalar mass2 = mass;
	btVector3 fallInertia2(0,0,0);
	boxShape->calculateLocalInertia(mass2,fallInertia2);
	btRigidBody::btRigidBodyConstructionInfo newBoxCI(mass2,fallMotionState2,boxShape,fallInertia2);	

	// Add first cube
	BoxSim box;
	box.cube.addBox(size.x*2,size.y*2,size.z*2);
	box.cube.randomFaceColors();
	box.cube.setAllColors(Color::White);
	box.texture = textures[texture];

	box.rigidBody = new BxBody();
	box.rigidBody->m_body = new btRigidBody(newBoxCI);
	box.mass = mass;
	bulletWorld.addBody(box.rigidBody);

	boxes.push_back(box);
	Log("New Box added");
}

void SampleUI::onEvent(Event &event)
{
	input.update(event);

	if(event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
	{
		m_character->jump();
	}
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
	{
		current_height++;
		Log("Current height: %f", current_height);
	}
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
	{
		current_height--;
		Log("Current height: %f", current_height);
	}
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::Right)
	{
		//current_z += 0.5;
		//Log("Current height: %f", current_height);
		currentFrame++;
		if(currentFrame >= animations.numFrames)
		{
			currentFrame = 0;
		}

	}
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::Left)
	{
		//current_z -= 0.5;
		//Log("Current height: %f", current_height);
		currentFrame--;
		if(currentFrame < 0)
			currentFrame = animations.numFrames - 1;
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

	if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right)
	{
		// Shoot
		vec3 direction = fpsCamera.getDirection();
		vec3 finalPosition = fpsCamera.getPosition() + fpsCamera.getDirection() * 150;

		btVector3 Start(fpsCamera.getPosition().x, fpsCamera.getPosition().y, fpsCamera.getPosition().z);
		btVector3 End(finalPosition.x, finalPosition.y, finalPosition.z);

		btCollisionWorld::ClosestRayResultCallback RayCallback(Start, End);

		// Perform raycast
		bulletWorld.m_scene->rayTest(Start, End, RayCallback);

		if(RayCallback.hasHit()) {
			End = RayCallback.m_hitPointWorld;
			//Normal = RayCallback.m_hitNormalWorld;
			
			// Do some clever stuff here
			RayCallback.m_collisionObject->activate(true);
			if(!RayCallback.m_collisionObject->isStaticOrKinematicObject())
			{
				Log("Hit something dynamic");
				btRigidBody* body = (btRigidBody*)RayCallback.m_collisionObject;
				body->applyImpulse(btVector3(direction.x * 5000, direction.y * 5000, direction.z * 5000), body->getCenterOfMassPosition() - RayCallback.m_hitPointWorld);
			}
			else
			{
				Log("No hits");
			}
		}
	}

	/// Add a brick in front of the camera
	if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{	
		makeBox(fpsCamera.getPosition() + fpsCamera.getDirection() * 4, vec3(0.3,0.3,0.3), "wood", 100);
	}
	
	/// Add a little box at origin
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::T){
		makeBox(vec3(0,30,0), vec3(0.2,0.2,0.2), "wood", 50);
	}

	/// Add random sized cubes near me
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::E)
	{
		float dimensions = math::random(0.5, 2.5);
		makeBox(fpsCamera.getPosition() + fpsCamera.getDirection() * 25, vec3(dimensions,dimensions,dimensions), "brick", dimensions * 60);		
	}

	/// Rotate camera
	if(event.type == Event::MouseMoved)
	{	
		vec2 movement = vec2(event.mouseMove.x, event.mouseMove.y);
		static vec2 oldPos = movement;
		vec2 offset = (movement - vec2(500,500) )* 0.005;
		fpsCamera.rotate(offset.x, offset.y);
	}

	/// Boom
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::B)
	{
		// explosion
		for(int i = 0; i < boxes.size(); ++i)
		{
			if((boxes[i].position - vec3(0,0,0)).length() < 20)
			{
				boxes[i].rigidBody->m_body->setActivationState(1);
				static_cast<btRigidBody*>(boxes[i].rigidBody->m_body)->applyCentralImpulse(btVector3(boxes[i].position.x * 300, boxes[i].position.y * 400, boxes[i].position.z * 300));
			}
		}
	}
}

void SampleUI::onUpdate(Time time)
{ 
	for(int i = 0; i < 4; i++)
	{
		bulletWorld.step(time.asSeconds() / 4);
	}
	
	if(focus)
		getWindow().setMousePosition(Vec2i(500,500));

	fpsCamera.setPosition(vec3(m_ghostObject->getWorldTransform().getOrigin().getX(), m_ghostObject->getWorldTransform().getOrigin().getY(), m_ghostObject->getWorldTransform().getOrigin().getZ()));
	
	bool sprinting = input.getKey(Keyboard::LShift);


	if(input.getKey(Keyboard::W))
	{
		vec3 cameraDirection = fpsCamera.getDirection();
		if(sprinting)
			m_character->setWalkDirection(btVector3(cameraDirection.x, cameraDirection.y, cameraDirection.z) * 0.6);		
		else
			m_character->setWalkDirection(btVector3(cameraDirection.x, cameraDirection.y, cameraDirection.z) * 0.2);
	}
	else if(input.getKey(Keyboard::S))
	{
		vec3 cameraDirection = fpsCamera.getDirection();
		m_character->setWalkDirection(-btVector3(cameraDirection.x, cameraDirection.y, cameraDirection.z) * 0.2);
	}
	else if(input.getKey(Keyboard::A))
	{
		vec3 cameraDirection = fpsCamera.getDirection();
		m_character->setWalkDirection(btVector3(cameraDirection.z, cameraDirection.y, -cameraDirection.x) * 0.2);
	}
	else if(input.getKey(Keyboard::D))
	{
		vec3 cameraDirection = fpsCamera.getDirection();
		m_character->setWalkDirection(-btVector3(cameraDirection.z, cameraDirection.y, -cameraDirection.x) * 0.2);
	}
	else
	{
		m_character->setWalkDirection(btVector3(0,0,0));
	}


	if(input.getKey(Keyboard::F))
	{
		// Apply telekinesis lift
		for(int i = 0; i < boxes.size(); ++i)
		{
			if((boxes[i].position - fpsCamera.getPosition()).length() < 20)
			{
				boxes[i].rigidBody->m_body->activate(true);
				static_cast<btRigidBody*>(boxes[i].rigidBody->m_body)->applyCentralForce(btVector3(30,2000 * boxes[i].mass * 0.01,0));
			}
		}
	}

	ground.offsetUV(time.asSeconds() * 0.1, time.asSeconds() * 0.1);

	vehicle->update();

	float enginePower = 2000;
	float steeringAngle = 0.4;
	if(input.getKey(Keyboard::X))
	{
		Log("Applying force!!");
		vehicle->vehicle->applyEngineForce(enginePower,2);
		vehicle->vehicle->applyEngineForce(enginePower,3);
		//vehicle->vehicle->applyEngineForce(200,2);
		//vehicle->vehicle->applyEngineForce(200,3);
	}
	else
	{
		vehicle->vehicle->applyEngineForce(0,2);
		vehicle->vehicle->applyEngineForce(0,3);
	}
	if(input.getKey(Keyboard::C))
	{
		Log("Braking!!!");
		//vehicle->vehicle->setBrake(50,0);
		//vehicle->vehicle->setBrake(50,1);
		vehicle->vehicle->setBrake(50,2);
		vehicle->vehicle->setBrake(50,3);
	}
	else
	{
		//vehicle->vehicle->setBrake(0,0);
		//vehicle->vehicle->setBrake(0,1);
		vehicle->vehicle->setBrake(0,2);
		vehicle->vehicle->setBrake(0,3);
	}

	if(input.getKey(Keyboard::N))
	{
		vehicle->vehicle->setSteeringValue(steeringAngle, 2);
		vehicle->vehicle->setSteeringValue(steeringAngle, 3);
	}
	else if(input.getKey(Keyboard::M))
	{
		vehicle->vehicle->setSteeringValue(-steeringAngle, 2);
		vehicle->vehicle->setSteeringValue(-steeringAngle, 3);
	}
	else
	{
		vehicle->vehicle->setSteeringValue(0, 2);
		vehicle->vehicle->setSteeringValue(0, 3);
	}
}

void SampleUI::onRender()
{	
	/// Initial setup
	getRenderer()->setDefaultViewport();
	getRenderer()->setDepthTestEnabled(true);
	getRenderer()->clearAllBuffers();
	getRenderer()->setClearColor(Color::Blue);
	getRenderer()->setProjectionMatrix(mat4::perspective(80, static_cast<float>(getSurface().getWidth()) / static_cast<float>(getSurface().getHeight()), 1.f, 1000.f));
	getRenderer()->setViewMatrix(fpsCamera.getMatrix());

	/// Draw the floor
	getRenderer()->setModelMatrix(mat4::identity);
	mGrassTexture.bind();
	//getRenderer()->draw(terrain);
	

	getRenderer()->setModelMatrix(mat4::translate(0,current_height,current_z));
	mWaterTexture.bind();
	//getRenderer()->draw(ground);

	getRenderer()->setModelMatrix(mat4::identity);
	//bulletWorld.m_scene->debugDrawWorld();
	//bulletDrawer->finalize();

	/// Draw the boxes
	for(int i = 0;  i < boxes.size(); i++)
	{
		btTransform trans;
		static_cast<btRigidBody*>(boxes[i].rigidBody->m_body)->getMotionState()->getWorldTransform(trans);
		btScalar mt[16];
		trans.getOpenGLMatrix(mt);
		boxes[i].model = mat4(mt);
		boxes[i].position = vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
		boxes[i].texture->bind();
		getRenderer()->setModelMatrix(boxes[i].model);
		getRenderer()->draw(boxes[i].cube);
	}

	// Draw the car body
	textures["wood"]->bind();
	btTransform trans;
	static_cast<btRigidBody*>(vehicle->m_carChassis)->getMotionState()->getWorldTransform(trans);
	btScalar mt[16];
	trans.getOpenGLMatrix(mt);
	getRenderer()->setModelMatrix(mat4(mt));
	getRenderer()->draw(vehicleChassis);

	// Draw wheels
	vehicle->vehicle->getWheelInfo(0).m_worldTransform.getOpenGLMatrix(mt);
	getRenderer()->setModelMatrix(mat4(mt));
	getRenderer()->draw(vehicleWheel);
	vehicle->vehicle->getWheelInfo(1).m_worldTransform.getOpenGLMatrix(mt);
	getRenderer()->setModelMatrix(mat4(mt));
	getRenderer()->draw(vehicleWheel);
	vehicle->vehicle->getWheelInfo(2).m_worldTransform.getOpenGLMatrix(mt);
	getRenderer()->setModelMatrix(mat4(mt));
	getRenderer()->draw(vehicleWheel);
	vehicle->vehicle->getWheelInfo(3).m_worldTransform.getOpenGLMatrix(mt);
	getRenderer()->setModelMatrix(mat4(mt));
	getRenderer()->draw(vehicleWheel);
	
	onRenderExp();

	/// Draw 3D text
	getRenderer()->setModelMatrix(mat4::translate(-3,8,0) * mat4::scale(0.01,-0.01,0.01));
	//getRenderer()->draw(txt);

	/// Draw Iron Man
	static float angle = 0; angle+=0.005;
	getRenderer()->setModelMatrix(mat4::rotatey(angle) * mat4::translate(0,1,0) * mat4::scale(3,3,3));
	IronManTexture.bind();
	//getRenderer()->draw(IronMan);

	/// Draw cross-hair
	getRenderer()->setDefaultTexture();
	getRenderer()->setDefaultDepthTesting();
	getRenderer()->setProjectionMatrix(View(0,0,1024,768).getMatrix());
	getRenderer()->setViewMatrix(mat4::identity);
	getRenderer()->setModelMatrix(mat4::identity);
	getRenderer()->drawDebugCircle(vec2(1024/2,768/2), 4, vec2(), Color::Black);

	/// Draw some UI
	//getRenderer()->draw(txt);
}
