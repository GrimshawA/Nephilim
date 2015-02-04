////////////////////////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2013 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef NephilimSound_h__
#define NephilimSound_h__

#include <Nephilim/Platform.h>
#include "SoundSourceSF.h"
#include <Nephilim/Foundation/Time.h>

#include <cstdlib>

NEPHILIM_NS_BEGIN

class SoundBuffer;

////////////////////////////////////////////////////////////////////////////////
/// \brief Regular sound that can be played in the audio environment
///
////////////////////////////////////////////////////////////////////////////////
class NEPHILIM_API Sound : public SoundSource
{
public :

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////////////////////
    Sound();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Construct the sound with a buffer
    ///
    /// \param buffer Sound buffer containing the audio data to play with the sound
    ///
    ////////////////////////////////////////////////////////////////////////////
    explicit Sound(const SoundBuffer& buffer);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    /// \param copy Instance to copy
    ///
    ////////////////////////////////////////////////////////////////////////////
    Sound(const Sound& copy);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////////////////////
    ~Sound();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Start or resume playing the sound
    ///
    /// This function starts the stream if it was stopped, resumes
    /// it if it was paused, and restarts it from beginning if it
    /// was it already playing.
    /// This function uses its own thread so that it doesn't block
    /// the rest of the program while the sound is played.
    ///
    /// \see pause, stop
    ///
    ////////////////////////////////////////////////////////////////////////////
    void play();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Pause the sound
    ///
    /// This function pauses the sound if it was playing,
    /// otherwise (sound already paused or stopped) it has no effect.
    ///
    /// \see play, stop
    ///
    ////////////////////////////////////////////////////////////////////////////
    void pause();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief stop playing the sound
    ///
    /// This function stops the sound if it was playing or paused,
    /// and does nothing if it was already stopped.
    /// It also resets the playing position (unlike pause()).
    ///
    /// \see play, pause
    ///
    ////////////////////////////////////////////////////////////////////////////
    void stop();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Set the source buffer containing the audio data to play
    ///
    /// It is important to note that the sound buffer is not copied,
    /// thus the sf::SoundBuffer instance must remain alive as long
    /// as it is attached to the sound.
    ///
    /// \param buffer Sound buffer to attach to the sound
    ///
    /// \see getBuffer
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setBuffer(const SoundBuffer& buffer);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Set whether or not the sound should loop after reaching the end
    ///
    /// If set, the sound will restart from beginning after
    /// reaching the end and so on, until it is stopped or
    /// setLoop(false) is called.
    /// The default looping state for sound is false.
    ///
    /// \param loop True to play in loop, false to play once
    ///
    /// \see getLoop
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setLoop(bool loop);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Change the current playing position of the sound
    ///
    /// The playing position can be changed when the sound is
    /// either paused or playing.
    ///
    /// \param timeOffset New playing position, from the beginning of the sound
    ///
    /// \see getPlayingOffset
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setPlayingOffset(Time timeOffset);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get the audio buffer attached to the sound
    ///
    /// \return Sound buffer attached to the sound (can be NULL)
    ///
    ////////////////////////////////////////////////////////////////////////////
    const SoundBuffer* getBuffer() const;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Tell whether or not the sound is in loop mode
    ///
    /// \return True if the sound is looping, false otherwise
    ///
    /// \see setLoop
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool getLoop() const;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get the current playing position of the sound
    ///
    /// \return Current playing position, from the beginning of the sound
    ///
    /// \see setPlayingOffset
    ///
    ////////////////////////////////////////////////////////////////////////////
    Time getPlayingOffset() const;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get the current status of the sound (stopped, paused, playing)
    ///
    /// \return Current status of the sound
    ///
    ////////////////////////////////////////////////////////////////////////////
    Status getStatus() const;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Overload of assignment operator
    ///
    /// \param right Instance to assign
    ///
    /// \return Reference to self
    ///
    ////////////////////////////////////////////////////////////////////////////
    Sound& operator =(const Sound& right);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Reset the internal buffer of the sound
    ///
    /// This function is for internal use only, you don't have
    /// to use it. It is called by the sf::SoundBuffer that
    /// this sound uses, when it is destroyed in order to prevent
    /// the sound from using a dead buffer.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void resetBuffer();

private :

    ////////////////////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////////////////////
    const SoundBuffer* m_buffer; ///< Sound buffer bound to the source
};

NEPHILIM_NS_END
#endif // NephilimSound_h__
