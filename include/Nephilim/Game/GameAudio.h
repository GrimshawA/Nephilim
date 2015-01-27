#ifndef NephilimGameAudio_h__
#define NephilimGameAudio_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

#include <vector>

NEPHILIM_NS_BEGIN

class AudioEnvironment;

/**
	\class GameAudio
	\brief Central audio manager for games to deal with audio

	This is a central hub for managing everything about audio in our game.
	It will interact with audio environments instanced from plugins or not,
	and use them to play sounds and all kinds of things.

	It also has a "static" interface to play sounds in a simple way, using any audio API
	that might be loaded and set as default. This allows to get prototypes up _VERY_
	quickly, without concerning with small details.
*/
class NEPHILIM_API GameAudio
{
public:
	/// List of currently setup audio solutions
	std::vector<AudioEnvironment*> audioEnvironments;

public:

	/// Play a given sound, prototyping
	void play(const String& filename);

};

NEPHILIM_NS_END
#endif //NephilimGameAudio_h__