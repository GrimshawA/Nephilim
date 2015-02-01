#ifndef NephilimExtensionAudio_h__
#define NephilimExtensionAudio_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/Extension.h>

NEPHILIM_NS_BEGIN

/**
	\class ExtensionAudio
	\brief Allows to implement audio solutions

	To keep the engine compact, it doesn't tightly coupled to any given
	audio solution, but rather works with an abstract interface for anything
	related to sound.

	This way, the user is free to use an official plugin or build its own audio
	solution quite easily.

	By dragging a audio plugin DLL to the Plugins directory, we can easily
	have audio support in our game. 
*/
class NEPHILIM_API ExtensionAudio : public Extension
{
public:

	/// Identifier of this environment for querying it back
	String name;

public:

	/// Test API to play a sound
	virtual void play(const String& filename){}
};

NEPHILIM_NS_END
#endif // NephilimExtensionAudio_h__
