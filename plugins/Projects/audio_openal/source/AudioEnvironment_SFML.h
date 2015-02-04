#ifndef AudioEnvironment_SFML__
#define AudioEnvironment_SFML__

#include <Nephilim/Audio/AudioEnvironment.h>
using namespace nx;

#include <Nephilim/Game/GameCore.h>

class AudioEnvironment_SFML : public AudioEnvironment
{
public:

	/// Construct the audio environment
	AudioEnvironment_SFML(GameCore* _game);

	/// Test API to play a sound
	virtual void play(const String& filename);
};

#endif // AudioEnvironment_SFML__
