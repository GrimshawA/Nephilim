#ifndef PARABOLA_SOUNDSHAREDDEVICE_H
#define PARABOLA_SOUNDSHAREDDEVICE_H

#include "Platform.h"
#include "Strings.h"
#include <SFML/Audio.hpp>

#include <map>

PARABOLA_NAMESPACE_BEGIN

class SoundPlayer;

/**
	\ingroup Sound
	\class SoundSharedDevice
	\brief Static sound device. Shared by all SoundPlayers.

	This class is meant for internal use by the SoundPlayer classes.
	Though, you can use it for some things, check the public API for 
	things you can query/do. 

	May be useful in some cases, but mostly just ignore it.
*/
class PARABOLA_API SoundSharedDevice{
public:
	

private:
	friend class SoundPlayer;

	/// All sound players, by id
	static std::map<unsigned long, SoundPlayer*> myPlayerStorage;

	/// Signs the player as valid
	static void sign(SoundPlayer *player);
	/// Removes the player from the list
	static void unsign(SoundPlayer *player);

	static unsigned long nextID;
};	

PARABOLA_NAMESPACE_END
#endif