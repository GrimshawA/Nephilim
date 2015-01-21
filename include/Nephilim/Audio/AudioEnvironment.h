#ifndef NephilimAudioEnvironment_h__
#define NephilimAudioEnvironment_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

/**
	\class AudioEnvironment
	\brief Interface for implementing audio solutions

	To keep the engine compact, it doesn't tightly coupled to any given
	audio solution, but rather works with an abstract interface for anything
	related to sound.

	This way, the user is free to use an official plugin or build its own audio
	solution quite easily.

	By dragging a audio plugin DLL to the Plugins directory, we can easily
	have audio support in our game. 
*/
class NEPHILIM_API AudioEnvironment
{
public:

	/// Identifier of this environment for querying it back
	String name;

public:

	/// Test API to play a sound
	virtual void play(const String& filename){}
};

NEPHILIM_NS_END
#endif // NephilimAudioEnvironment_h__
