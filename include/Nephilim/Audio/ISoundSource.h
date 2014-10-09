#ifndef Source_h__
#define Source_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/** 
	\class ISoundSource
	\brief Interface for a sound source being emitted

	The engine does not support any audio backend directly.
	Because of portability issues, as well as dependency managing,
	the engine doesn't commit to any particular audio API.

	Instead, it just implements a base interface for audio, 
	so to support any kind of audio playback library.

	For example, the engine can interact with FMOD or OpenAL
	and others via plugins. 

	However, any audio API tracks all its emitting sounds somehow,
	either referring to them as channels, sources or anything else.

	ISoundSource is the interface used by the engine to play and manipulate 
	these sources of sound in the game world.
*/
class NEPHILIM_API ISoundSource
{
public:

	/// Set the volume for this sound source
	/// Volumes go from 0.0 (silent) to 1.0 (full volume)
	virtual void setVolume(float volume){};

};

NEPHILIM_NS_END
#endif // Source_h__
