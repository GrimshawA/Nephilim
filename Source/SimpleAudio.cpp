#include <Nephilim/SimpleAudio.h>

#ifdef NEPHILIM_ANDROID
#include <Nephilim/AndroidInterface.h>
#else
#include <SFML/Audio/Music.hpp>
#endif

NEPHILIM_NS_BEGIN

namespace priv
{
	class SimpleMusicImplementation{
	public:
		/// Opens the music from a file
		virtual bool openFromFile(const String& filename) = 0;
		/// Starts playing
		virtual void play() = 0;
		/// Get the duration of the clip
		virtual Time getDuration() = 0;
		/// Set looping
		virtual void setLoop(bool loop) = 0;
		/// Stop the sound
		virtual void stop() = 0;
		/// Pause the sound
		virtual void pause() = 0;
		/// Set the volume of the clip
		virtual void setVolume(float volume) = 0;
	};

#ifdef NEPHILIM_ANDROID
	class SimpleMusicAndroid : public SimpleMusicImplementation
	{
	public:
		/// Opens the music from a file
		bool openFromFile(const String& filename)
		{
			return false;
		}

		/// Starts playing
		void play()
		{

		}

		/// Get the duration of the clip
		Time getDuration()
		{
			return Time();
		}

		/// Set looping
		void setLoop(bool loop)
		{
			
		}

		/// Stop the sound
		void stop()
		{

		}

		/// Pause the sound
		void pause()
		{

		}

		/// Set the volume of the clip
		void setVolume(float volume)
		{

		}
	};
#else
	class SimpleMusicSFML : public SimpleMusicImplementation
	{
	public:
		/// Opens the music from a file
		bool openFromFile(const String& filename)
		{
			return m_music.openFromFile(filename);
		}

		/// Starts playing
		void play()
		{
			m_music.play();
		}

		/// Stop the sound
		void stop()
		{
			m_music.stop();
		}

		/// Pause the sound
		void pause()
		{
			m_music.pause();
		}

		/// Set looping
		void setLoop(bool loop)
		{
			m_music.setLoop(loop);
		}

		/// Get the duration of the clip
		Time getDuration()
		{
			return Time::fromMiliSeconds(m_music.getDuration().asMilliseconds());
		}

		/// Set the volume of the clip
		void setVolume(float volume)
		{
			m_music.setVolume(volume);
		}

		sf::Music m_music;
	};

#endif	
};



/// Uninitialized music
SimpleMusic::SimpleMusic()
{
#ifdef NEPHILIM_ANDROID
	m_implementation = new priv::SimpleMusicAndroid();
#else
	m_implementation = new priv::SimpleMusicSFML();
#endif
}

/// Assure music destruction
SimpleMusic::~SimpleMusic()
{
	delete m_implementation;
}

/// Opens the music from a file
bool SimpleMusic::openFromFile(const String& filename)
{
	return m_implementation->openFromFile(filename);
}

void SimpleMusic::play()
{
	m_implementation->play();
}

void SimpleMusic::stop()
{
	m_implementation->stop();
}

Time SimpleMusic::getDuration()
{
	return m_implementation->getDuration();
}

void SimpleMusic::setLoop(bool loop)
{
	m_implementation->setLoop(loop);
}

/// Pause the sound
void SimpleMusic::pause()
{
	m_implementation->pause();
}

/// Set the volume of the clip
void SimpleMusic::setVolume(float volume)
{
	m_implementation->setVolume(volume);
}

NEPHILIM_NS_END