#ifndef NephilimWorldActorAudioComponent_h__
#define NephilimWorldActorAudioComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Component.h>
#include <Nephilim/Foundation/String.h>

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
class NEPHILIM_API AAudioComponent : public Component
{
public:

	/// Attempt to play a sound (can fail)
	void play(const String& filename);


	AudioSystem* _audioSystem = nullptr;
};

NEPHILIM_NS_END
#endif // NephilimWorldActorAudioComponent_h__
