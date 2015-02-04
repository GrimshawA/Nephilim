#include "AudioEnvironment_SFML.h"

#include <SFMLAudioCode/Music.h>

/// Construct the audio environment
AudioEnvironment_SFML::AudioEnvironment_SFML(GameCore* _game)
{
	name = "openal";
}

/// Test API to play a sound
void AudioEnvironment_SFML::play(const String& filename)
{
	Log("PLAYING SOUND THROUGH SFML");

	Music* m = new Music();
	m->openFromFile(filename);
	m->play();
}