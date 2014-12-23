#ifndef NephilimAudioSystem_h__
#define NephilimAudioSystem_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/System.h>

NEPHILIM_NS_BEGIN


/**
	\class AudioSystem
	\brief Interface for different audio systems that can play the sounds in the scene	
*/
class NEPHILIM_API AudioSystem : public System
{
public:
	virtual void play(const String& filename) = 0;
};

NEPHILIM_NS_END
#endif // NephilimRenderSystem_h__
