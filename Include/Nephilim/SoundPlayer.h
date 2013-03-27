#ifndef PARABOLA_SOUNDPLAYER_H
#define PARABOLA_SOUNDPLAYER_H

#include "Platform.h"
#include "Strings.h"

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>

#include <vector>

PARABOLA_NAMESPACE_BEGIN

class ContentBank;
class GameCore;
class ASEngine;
class SoundSharedDevice;
/**
	\ingroup Sound
	\class SoundPlayer
	\brief Represents a mechanism capable of playing audio, both streamed and not.

	Notice that this class doesn't store any of the actual sound buffers.
	The sound buffers must come from a ContentList already loaded into a ContentBank.
	On-the-fly loading is possible too, but not recommended as it may stagger the playing of a sound
	the first time it is used.

	It only stores a reference to a small warehouse managed by the SoundSharedDevice static class.

	Only a game shall instance SoundPlayer objects, as to keep them tracked, and ensure destruction at end.
	This is important so that when your game loses rendering focus, all its sounds are paused, for later resuming.

	The sound player is registered in the sound device on construction and removed on destruction.
	It is well working under the RAII paradigm.

*/
class PARABOLA_API SoundPlayer{
public:
	/// Can only be instanced by passing a game.
	SoundPlayer(GameCore *parent, const String &name);

	/// Safely destroys all sounds associated and removes itself from the shared device.
	~SoundPlayer();

	/// Associate a content bank
	void setContentBank(ContentBank* contentBank);

	/// Starts streaming a music from a file
	bool playMusic(const String &fileName);

	/// Starts playing a sound
	bool playSound(const String &fileName);

	/// Iterates the music list, while removing items if necessary
	void refreshMusicList();

	/// Iterates the sound list, removing finished sounds.
	void refreshSoundList();

private:
	// Music list
	std::vector<sf::Music*> myMusicList;
	std::vector<sf::Sound*> mySoundList;

	ContentBank* myContentBank;

	friend class GameCore;
	friend class SoundSharedDevice;
	String myName;
	unsigned long myIdentification;



	// Angelscripting functions
	friend class ASEngine;
	void dummy(){}
};

PARABOLA_NAMESPACE_END
#endif
