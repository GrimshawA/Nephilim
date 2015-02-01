#include <Nephilim/Game/GameAudio.h>
#include <Nephilim/Extensions/ExtensionAudio.h>

NEPHILIM_NS_BEGIN

/// Play a given sound, prototyping
void GameAudio::play(const String& filename)
{
	if (audioEnvironments.size() > 0)
	{
		audioEnvironments[0]->play(filename);
	}
}

NEPHILIM_NS_END