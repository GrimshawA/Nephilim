#include <Nephilim/Audio/AudioEnvironment.h>
#include <Nephilim/Plugins/PluginSDK.h>
#include <Nephilim/Game/GameCore.h>
using namespace nx;

#include "AudioEnvironment_SFML.h"

extern "C"
{
	__declspec(dllexport) AudioEnvironment *createAudioEnvironment(GameCore* game)
	{
		return new AudioEnvironment_SFML(game);
	}

	__declspec(dllexport) PluginSDK::Types getPluginType()
	{
		return PluginSDK::Audio;
	}
}
