#ifndef PARABOLA_PARTICLESYSTEMS_H
#define PARABOLA_PARTICLESYSTEMS_H

#include "Platform.h"
#include "Drawable.h"
#include "Strings.h"
#include "Textures.h"
#include "Animation.h"
#include "ReferenceCountable.h"

#include "ParticlePointRenderer.h"

#include "SPARK.h"

PARABOLA_NAMESPACE_BEGIN

class ParticleSystem;


/**
	\ingroup Graphics
	\class ParticleRenderer
	\brief Wrapper for a SPARK renderer. Scripting convenience.
*/
class PARABOLA_API ParticleRenderer{
public:	
	//SPK::Ref<SPK::GL::GLRenderer> myRenderer;
};

/**
	\ingroup Graphics
	\class ParticleTexture
	\brief Wrapper for a SPARK textures. Scripting convenience.
*/
class PARABOLA_API ParticleTexture{
public:
	//bool loadTexture(const String &path);
	//GLuint myTextureID;
};

/**
	\ingroup Graphics
	\class ParticleModifier
	\brief Wrapper for a SPARK modifiers. Scripting convenience.
*/
class PARABOLA_API ParticleModifier{
public:
	SPK::Ref<SPK::Modifier> myModifier;
};

/**
	\ingroup Graphics
	\class ParticleZone
	\brief Wrapper for a SPARK zones. Scripting convenience.
*/
class PARABOLA_API ParticleZone : public Animable{
public:

	void animable_set_position(float x, float y){
		myZone->setPosition(SPK::Vector3D(x,y,0.f));
	}

	Vec2f animable_get_position(){
		return Vec2f(myZone->getPosition().x, myZone->getPosition().y);
	};

	SPK::Ref<SPK::Zone> myZone;
};

/**
	\ingroup Graphics
	\class ParticleEmitter
	\brief Wrapper for a SPARK emitters. Scripting convenience.
*/
class PARABOLA_API ParticleEmitter{
public:
	SPK::Ref<SPK::Emitter> myEmitter;
};

/**
	\ingroup Graphics
	\class ParticleGroup
	\brief Wrapper for a SPARK groups. Scripting convenience.
*/
class PARABOLA_API ParticleGroup{
public:
	ParticleGroup(ParticleSystem* parent){
		myParent = parent;
	}

	/// Just a test - creates a funny effect
	void defaultGroup1();

	String getName(){
		return myGroup->getName();
	}	

	void addEmitter(ParticleEmitter &emitter){
		myGroup->addEmitter(emitter.myEmitter);
	}

	void addModifier(ParticleModifier &modifier){
		myGroup->addModifier(modifier.myModifier);
	}



	void setLifeTime(float minLife, float maxLife){
		if(minLife < 0 || maxLife < 0)
			myGroup->setImmortal(true);
		else
			myGroup->setLifeTime(minLife, maxLife);
	}

	void setRenderer(ParticleRenderer &pRenderer){
//		myGroup->setRenderer(pRenderer.myRenderer);
	}

	SPK::Ref<SPK::Group> myGroup;
	ParticleSystem *myParent;
};

/**
	\ingroup Graphics
	\class ParticleSystem
	\brief A configurable particle effect

	\todo Remove the clamp step from constructor
	...
*/
class PARABOLA_API ParticleSystem: public RefCountable, public Drawable{
public:
	/// Creates an empty Particle System
	ParticleSystem();

	/// Create a named, empty particle system 
	ParticleSystem(const String &name);

	/// Called to order rendering, when the drawing was issued in the traditional way ( m_renderer->draw(m_sprite) )
	void onDraw(Renderer* renderer);

	/// Loads from a script
	bool loadFromScript(const String &filePath);
	
	/// Adds a new group to the system
	ParticleGroup* addGroup(const String &name, int capacity);

	/// Remove group from the system
	void removeGroup(const String &name);

	/// Get a group in the system
	ParticleGroup* getGroup(const String &name);

	/// Remove the renderer with the right name
	void removeRenderer(const String &name);

	/// Erases everything in this system
	void clear();

	/// Update the state of the particles.
	void update(float elapsedTime);

	/// Draw the system
//	void draw(SceneRenderer* renderer);

	/// Get the internal spark system
	SPK::Ref<SPK::System> getSparkSystem();

	/// Get the name of this particle system
	String getName();

	/// Set a new name to the particle system
	void setName(const String &newName);

	/// Create a texture to be used within the particle system
	ParticleTexture& createTexture(const String &name, const String &path);

	/// Create a point renderer, further configurable later.
	ParticleRenderer& createPointRenderer(const String &name, float pointSize);

	/// Create a sphere type zone, further configurable later.
	ParticleZone& createSphereZone(const String &name, float x, float y, float z, float radius);

	/// Create a gravity modifier
	ParticleModifier& createGravityModifier(const String &name, float x, float y, float z);

	/// Create a spheric type emitter, configurable later.
	ParticleEmitter& createSphericEmitter(const String &name, float direction_x, float direction_y, float direction_z,float angleMin, float angleMax, ParticleZone &zone,
											bool full, int tank, float flow, float forceMin, float forceMax);

	/// Cleans all renderers, zones, emitters, textures and modifiers that are not being used
	void cleanUnusedResources();

	/// Creates a sample system directly with the given zone name for possibly animating it later or other uses.
	void createSampleSparkles(const String &zoneName);

private:
	/// Internal spark system
	SPK::Ref<SPK::System> mySystem;

	/// Particle system name, or effect name
	String myName;

	/// All resources this system has
	std::map<String, ParticleGroup*> myGroups;
	std::map<String, ParticleRenderer*> myRenderers;
	std::map<String, ParticleZone*> myZones;
	std::map<String, ParticleEmitter*> myEmitters;
	std::map<String, ParticleTexture*> myTextures;
	std::map<String, ParticleModifier*> myModifiers;
};

PARABOLA_NAMESPACE_END
#endif