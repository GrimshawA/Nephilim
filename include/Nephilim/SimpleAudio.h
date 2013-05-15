#ifndef SimpleAudio_h__
#define SimpleAudio_h__

#include "Platform.h"
#include "Strings.h"
#include "Clock.h"

NEPHILIM_NS_BEGIN

namespace priv
{
	class SimpleMusicImplementation;
}

/**
	\ingroup Audio
	\class SimpleMusic
	\brief Allows to play music in the simplest form possible.

	It doesn't support a lot of features, it just works as a basic audio support until more efficient (portable) audio is done.
*/
class NEPHILIM_API SimpleMusic
{
public:
	/// Uninitialized music
	SimpleMusic();

	/// Assure music destruction
	~SimpleMusic();

	/// Opens the music from a file
	bool openFromFile(const String& filename);

	/// Starts playing
	void play();

	/// Stop the sound
	void stop();

	/// Pause the sound
	void pause();

	/// Get the duration of the clip
	Time getDuration();

	/// Set the volume of the clip
	void setVolume(float volume);

	/// Set looping
	void setLoop(bool loop);

private:
	priv::SimpleMusicImplementation* m_implementation;
};

NEPHILIM_NS_END
#endif // SimpleAudio_h__
