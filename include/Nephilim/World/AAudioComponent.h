#ifndef NephilimWorld_AAudioComponent_h__
#define NephilimWorld_AAudioComponent_h__

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

	AudioSystem* _audioSystem = nullptr;

public:

	/// Attempt to play a sound (can fail)
	void play(const String& filename);
};

NEPHILIM_NS_END
#endif // NephilimWorld_AAudioComponent_h__
