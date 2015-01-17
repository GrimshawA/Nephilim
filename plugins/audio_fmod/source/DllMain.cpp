#include <stdio.h>

#include <fmod.hpp>
#include <fmod_errors.h>

#include <Nephilim/Logger.h>

#include <Nephilim/World/World.h>
#include <Nephilim/World/AudioSystem.h>
#include <Nephilim/World/AAudioComponent.h>

#include <Nephilim/Audio/ISoundSource.h>
using namespace nx;

class FmodSoundSource : public ISoundSource
{
public:
	FMOD::Channel *channel = nullptr;

	void setVolume(float volume)
	{
		if (channel)
		{
			channel->setVolume(volume);
		}
	}
};

class AudioSystemFMOD : public AudioSystem
{
public:
	AudioSystemFMOD()
	{
		Log("FMOD INIT");
	}

	void update(const Time& t)
	{
	//	Log("Audio update");

		for (std::size_t i = 0; i < mWorld->actors.size(); ++i)
		{
			Actor* actor = mWorld->actors[i];

			AAudioComponent* audioComponent = actor->searchComponent<AAudioComponent>();
			if (audioComponent)
			{
				audioComponent->_audioSystem = this;
			}
		}
	}

	void play(const String& filename)
	{
		FMOD_RESULT result;
		FMOD::System *system;

		FmodSoundSource* soundSource = new FmodSoundSource();
		//source = soundSource;

		result = FMOD::System_Create(&system);		// Create the main system object.
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			//exit(-1);
		}

		result = system->init(100, FMOD_INIT_NORMAL, 0);	// Initialize FMOD.
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			//exit(-1);
		}
		else
		{
			printf("FMOD is ready!\n");
		}

		FMOD::Sound *sound;
		result = system->createSound(filename.c_str(), FMOD_LOOP_NORMAL, 0, &sound);
		if (result != FMOD_OK)
		{
			printf("Failed to create sound!\n");
		}

		FMOD::Channel *channel;
		result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
		if (result != FMOD_OK)
		{
			printf("Failed to play sound!\n");
		}
		else
		{
			printf("Playing, hopefully..\n");
			channel->setLoopCount(-1);
			soundSource->channel = channel;
		}
	}

};

extern "C"
{
	AudioSystem __declspec(dllexport) *createAudioSystem()
	{
		return new AudioSystemFMOD();
	}
}
