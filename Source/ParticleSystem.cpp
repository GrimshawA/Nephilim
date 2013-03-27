#include "Nephilim/ParticleSystem.h"
/*#include "Nephilim/ASEngine.h"

#include <iostream>
using namespace std;


PARABOLA_NAMESPACE_BEGIN
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// TEXTURE

bool ParticleTexture::loadTexture(const String &path){

	GLuint texture = 0;
	{
		Image image;
		if (!image.loadFromFile(path))
			return false;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}

	myTextureID = texture;
	return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// SYSTEM

ParticleSystem::ParticleSystem(){
	SPK::System::setClampStep(true,0.1f);		// clamp the step to 100 ms
	SPK::System::useAdaptiveStep(0.001f,0.01f);
	mySystem = SPK::System::create(true);
};

/// Create a named, empty particle system 
ParticleSystem::ParticleSystem(const String &name){
	myName = name;
	SPK::System::setClampStep(true,0.1f);		// clamp the step to 100 ms
	SPK::System::useAdaptiveStep(0.001f,0.01f);
	mySystem = SPK::System::create(true);
};


/// Get the internal spark system
SPK::Ref<SPK::System> ParticleSystem::getSparkSystem(){
	return mySystem;
};

/// Loads from a script
bool ParticleSystem::loadFromScript(const String &filePath){
	ASEngine::loadParticleSystem(filePath, this, false);
	return true;
};

/// Adds a new group to the system
ParticleGroup* ParticleSystem::addGroup(const String &name, int capacity){
	ParticleGroup* group = new ParticleGroup(this);
	group->myGroup = mySystem->createGroup(capacity);
	group->myGroup->setName(name);
	myGroups[name] = group;
	return group;
};

/// Remove group from the system
void ParticleSystem::removeGroup(const String &name){
	std::map<String, ParticleGroup*>:: iterator it = myGroups.find(name);
	if(it != myGroups.end()){
		ParticleGroup* group = it->second;
		mySystem->removeGroup(group->myGroup);
		delete group;
		myGroups.erase(it);
	}
};

/// Get a group in the system
ParticleGroup* ParticleSystem::getGroup(const String &name){
	std::map<String, ParticleGroup*>:: iterator it = myGroups.find(name);
	if(it != myGroups.end()){
		return it->second;
	}
	else return NULL;
};

/// Remove the renderer with the right name
void ParticleSystem::removeRenderer(const String &name){
	std::map<String, ParticleRenderer*>:: iterator it = myRenderers.find(name);
	if(it != myRenderers.end()){
		ParticleRenderer* r = it->second;
		delete r;
		myRenderers.erase(it);
	}
};

/// Erases everything in this system
void ParticleSystem::clear(){
	for(std::map<String,ParticleGroup*>::iterator it = myGroups.begin(); it != myGroups.end(); it++){
		removeGroup(it->first);
	}

	for(std::map<String,ParticleRenderer*>::iterator it = myRenderers.begin(); it != myRenderers.end(); it++){
		removeRenderer(it->first);
	}

	//...
};

String ParticleSystem::getName(){
	return myName;
}

/// Set a new name to the particle system
void ParticleSystem::setName(const String &newName){
	myName = newName;
};


ParticleRenderer& ParticleSystem::createPointRenderer(const String &name, float pointSize){
	ParticleRenderer *pRend = new ParticleRenderer();

	return *pRend;
}

ParticleEmitter& ParticleSystem::createSphericEmitter(const String &name, float direction_x, float direction_y, float direction_z,
	float angleMin, float angleMax, ParticleZone &zone,
	bool full, int tank, float flow, float forceMin, float forceMax){

		ParticleEmitter *pRend = new ParticleEmitter();
		pRend->myEmitter = SPK::SphericEmitter::create(SPK::Vector3D(direction_x, direction_y, direction_z),angleMin, angleMax, zone.myZone , full, tank, flow, forceMin, forceMax);

		myEmitters[name] = pRend;
		return *pRend;
}

ParticleTexture& ParticleSystem::createTexture(const String &name, const String &path){
	ParticleTexture *pRend = new ParticleTexture();
//	pRend->loadTexture(path);
	//myTextures[name] = pRend;
	return *pRend;
}


ParticleZone& ParticleSystem::createSphereZone(const String &name, float x, float y, float z, float radius){
	ParticleZone *pRend = new ParticleZone();
	pRend->myZone = SPK::Sphere::create(SPK::Vector3D(x,y,z), radius);
	myZones[name] = pRend;
	return *pRend;
}

ParticleModifier& ParticleSystem::createGravityModifier(const String &name, float x, float y, float z){
	ParticleModifier *pRend = new ParticleModifier();
	pRend->myModifier = SPK::Gravity::create(SPK::Vector3D(x,y,z));
	myModifiers[name] = pRend;
	return *pRend;
}

/// A simple system
void ParticleSystem::createSampleSparkles(const String &zoneName){

};

/// Called to order rendering, when the drawing was issued in the traditional way ( m_renderer->draw(m_sprite) )
void ParticleSystem::onDraw(Renderer* renderer){

};


	
/// Update the state of the particles.
void ParticleSystem::update(float elapsedTime){
	mySystem->updateParticles(elapsedTime);
};



//////////////////////////////////////////////////////////////////////////

void ParticleGroup::defaultGroup1(){

	//ParticleTexture *tt = new ParticleTexture();
	//if(!tt->loadTexture("part.png"))cout<<"COULD NOT LOAD TEXTURE"<<endl;

	SPK::Ref<ParticlePointRenderer> rn = ParticlePointRenderer::create(10);
	//rn->setTexture(tt->myTextureID);
	//rn->setType(SPK::POINT_TYPE_SQUARE);
	//rn->setScreenSize(20);
	//rn->setBlendMode(SPK::BLEND_MODE_ALPHA);
	//rn->setAlphaTestThreshold()
	//rn->setType(SPK::POINT_TYPE_SPRITE);
	myGroup->setRenderer(rn);
	//effectgroup->setRenderer(SPK::GL::GLLineRenderer::create(10, 5));
	
	//mySphere = SPK::Sphere::create(SPK::Vector3D(300.f,300.f,0.f),4.0f);

	SPK::Ref<SPK::Sphere> m_sphere = SPK::Sphere::create(SPK::Vector3D(400.f,400.f,0.f),20.0f);

	//effectgroup->setRenderer(renderer);
	myGroup->setLifeTime(3,6);
	myGroup->setColorInterpolator(SPK::ColorRandomInterpolator::create(SPK::Color(255,0,0,255),SPK::Color(255,50,0,255),SPK::Color(255,30,40,255),SPK::Color(255,0,160,255)));
	myGroup->addEmitter(SPK::SphericEmitter::create(SPK::Vector3D(1.0f,0.0f,0.0f),0.0f,2*3.14159f,m_sphere,true,-1,300.0f,1.2f,2.5f));
	//myGroup->setParamInterpolator(SPK::PARAM_TEXTURE_INDEX,SPK::FloatRandomInitializer::create(0.0f,4.0f));
	myGroup->setParamInterpolator(SPK::PARAM_ROTATION_SPEED,SPK::FloatRandomInitializer::create(-0.1f,1.0f));
	myGroup->setParamInterpolator(SPK::PARAM_ANGLE,SPK::FloatRandomInitializer::create(0.0f,2.0f * 3.14159f));
	myGroup->addModifier(SPK::Gravity::create(SPK::Vector3D(0.0f, -1,0.0f)));
	myGroup->setColorInterpolator(SPK::ColorSimpleInterpolator::create(0xFF802080,0xFF000000));
	myGroup->setRadius(20.f);
	myGroup->setPhysicalRadius(1);
	//myGroup->addModifier(SPK::Rotator::create());
	myGroup->setGraphicalRadius(20);
	//myGroup->set

	//ParticleTexture *tt2 = new ParticleTexture();
	//if(!tt2->loadTexture("explosion.png"))cout<<"COULD NOT LOAD TEXTURE"<<endl;

}


PARABOLA_NAMESPACE_END
*/