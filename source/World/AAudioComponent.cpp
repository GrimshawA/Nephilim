#include <Nephilim/World/AAudioComponent.h>
#include <Nephilim/World/World.h>
#include <Nephilim/World/AudioSystem.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

/// Attempt to play a sound (can fail)
void AAudioComponent::play(const String& filename)
{
	if (_audioSystem)
	{
		_audioSystem->play(filename);
		Log("Playing a new %s", filename.c_str());
	}
}

NEPHILIM_NS_END