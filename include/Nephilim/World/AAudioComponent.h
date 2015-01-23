#ifndef NephilimWorldActorAudioComponent_h__
#define NephilimWorldActorAudioComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/GameObject.h>
#include <Nephilim/World/Actor.h>
#include <Nephilim/World/CTransform.h>
#include <Nephilim/World/CInput.h>
#include <Nephilim/World/CStaticMesh.h>
#include <Nephilim/World/CSprite.h>
#include <Nephilim/World/CColliderBox.h>
#include <Nephilim/World/CSkeletalMesh.h>
#include <Nephilim/Foundation/BBox.h>

#include <Nephilim/Scripting/IScript.h>

NEPHILIM_NS_BEGIN

class AudioSystem;

/**
	\class AAudioComponent
	\brief Allows the actor to play sounds

	Purposes:
	1) Group all currently playing sounds per actor
	2) Enable or disable audio for an actor quickly
	3) Interface with the underlying AudioSystems to actually play the sounds
	4) Hold a sound to emit without additional parameters (also useful to be fired via scripts)
*/
class NEPHILIM_API AAudioComponent : public ActorComponent
{
public:

	/// Attempt to play a sound (can fail)
	void play(const String& filename);


	AudioSystem* _audioSystem = nullptr;
};

NEPHILIM_NS_END
#endif // NephilimWorldActorAudioComponent_h__
