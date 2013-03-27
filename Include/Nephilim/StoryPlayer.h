#ifndef PARABOLA_STORYLINE_PLAYER_H
#define PARABOLA_STORYLINE_PLAYER_H

#include "Platform.h"
#include <map>

#include "Strings.h"
#include "TextFileStream.h"
#include "SceneRenderer.h"
#include "LinkedPointer.h"
//#include "SoundManager.h"

#include "Storyline.h"


PARABOLA_NAMESPACE_BEGIN

namespace PlayModes{
	enum PlayType{
		PLAYING = 0,
		PAUSED,
		STOPPED
	};
}

	class PackageStream;
	class Event;
	/**
		\class StoryPlayer
		\brief Is capable of loading, executing and manipulating stories.
	*/
	class PARABOLA_API StoryPlayer{
	public:
		/// Creates a new story player. It works but is limited until you bind some resources to it.
		StoryPlayer();

		/// Loads all data from a specified file into this player's data warehouse.
		/// Returns false in case of something is wrong with the file syntax.
		bool loadStoryFromFile(String fileName);
		/// Loads all data from a specified package stream into this player's data warehouse.
		/// Returns false in case of something is wrong with the file syntax.
		/// The stream must be already set in the desired file.
		/// \todo Complete support for this.
		bool loadStoryFromPackage(PackageStream *stream);

		/// Feeds events to the storyline
		void onEvent(Event &event);
		/// Updates the story playback
		void onUpdate(double deltaTime);
		/// Draws the story to the specific target
		void onDraw();

		/// Plays the story from where it stopped, or from the beginning if it was not playing
		void play();
		/// Pauses the execution of the story line
		void pause();
		/// Stops the execution of the story line and pushes it back to the beginning
		void stop();

		/// Returns the current state of playing of the story player
		PlayModes::PlayType getStatus();

		/// Get the amount of storyline loaded
		int storyCount();

		/// Links to external resources, required for some commands.
		linked_ptr<SceneRenderer> renderer;
//linked_ptr<SoundPlayer> soundPlayer;
	protected:

		/// Maps a storyline name to it's structure
		std::map<String, Storyline> stories;
		Storyline *current_story;
		

	private:
		bool loadFromStream(TextStream &stream, String parentFileName);
		void parseBlock(String token, String args, String styles, TextStream &stream, bool hasBlock, String parentFileName);
		void parseTable(String token, String args, String styles, TextStream &stream, bool hasBlock);
		void parseStyle(String token, String args, String styles, TextStream &stream, bool hasBlock);
		void parseStory(String token, String args, String styles, TextStream &stream, bool hasBlock);

		void parseStoryCommand(Storyline &story, String command);

		
		PlayModes::PlayType status;

	};

PARABOLA_NAMESPACE_END
#endif