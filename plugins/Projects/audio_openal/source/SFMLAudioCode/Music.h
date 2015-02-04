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

#ifndef NephilimMusic_h__
#define NephilimMusic_h__

#include <Nephilim/Platform.h>
#include "SoundStream.h"
#include <Nephilim/Foundation/Mutex.h>
#include <Nephilim/Foundation/Time.h>

#include <string>
#include <vector>

NEPHILIM_NS_BEGIN

namespace priv
{
    class SoundFile;
}

class File;

////////////////////////////////////////////////////////////////////////////////
/// \brief Streamed music played from an audio file
///
////////////////////////////////////////////////////////////////////////////////
class NEPHILIM_API Music : public SoundStream
{
public :

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////////////////////
    Music();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////////////////////
    ~Music();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Open a music from an audio file
    ///
    /// This function doesn't start playing the music (call play()
    /// to do so).
    /// Here is a complete list of all the supported audio formats:
    /// ogg, wav, flac, aiff, au, raw, paf, svx, nist, voc, ircam,
    /// w64, mat4, mat5 pvf, htk, sds, avr, sd2, caf, wve, mpc2k, rf64.
    ///
    /// \param filename Path of the music file to open
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see openFromMemory, openFromStream
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool openFromFile(const std::string& filename);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Open a music from an audio file in memory
    ///
    /// This function doesn't start playing the music (call play()
    /// to do so).
    /// Here is a complete list of all the supported audio formats:
    /// ogg, wav, flac, aiff, au, raw, paf, svx, nist, voc, ircam,
    /// w64, mat4, mat5 pvf, htk, sds, avr, sd2, caf, wve, mpc2k, rf64.
    /// Since the music is not loaded completely but rather streamed
    /// continuously, the \a data must remain available as long as the
    /// music is playing (ie. you can't deallocate it right after calling
    /// this function).
    ///
    /// \param data        Pointer to the file data in memory
    /// \param sizeInBytes Size of the data to load, in bytes
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see openFromFile, openFromStream
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool openFromMemory(const void* data, std::size_t sizeInBytes);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Open a music from an audio file in a custom stream
    ///
    /// This function doesn't start playing the music (call play()
    /// to do so).
    /// Here is a complete list of all the supported audio formats:
    /// ogg, wav, flac, aiff, au, raw, paf, svx, nist, voc, ircam,
    /// w64, mat4, mat5 pvf, htk, sds, avr, sd2, caf, wve, mpc2k, rf64.
    /// Since the music is not loaded completely but rather streamed
    /// continuously, the \a stream must remain alive as long as the
    /// music is playing (ie. you can't destroy it right after calling
    /// this function).
    ///
    /// \param stream Source stream to read from
    ///
    /// \return True if loading succeeded, false if it failed
    ///
    /// \see openFromFile, openFromMemory
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool openFromStream(File& stream);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get the total duration of the music
    ///
    /// \return Music duration
    ///
    ////////////////////////////////////////////////////////////////////////////
    Time getDuration() const;

protected :

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Request a new chunk of audio samples from the stream source
    ///
    /// This function fills the chunk from the next samples
    /// to read from the audio file.
    ///
    /// \param data Chunk of data to fill
    ///
    /// \return True to continue playback, false to stop
    ///
    ////////////////////////////////////////////////////////////////////////////
    virtual bool onGetData(Chunk& data);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Change the current playing position in the stream source
    ///
    /// \param timeOffset New playing position, from the beginning of the music
    ///
    ////////////////////////////////////////////////////////////////////////////
    virtual void onSeek(Time timeOffset);

private :

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Initialize the internal state after loading a new music
    ///
    ////////////////////////////////////////////////////////////////////////////
    void initialize();

    ////////////////////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////////////////////
    priv::SoundFile*   m_file;     ///< Sound file
    Time               m_duration; ///< Music duration
    std::vector<Int16> m_samples;  ///< Temporary buffer of samples
    Mutex              m_mutex;    ///< Mutex protecting the data
};

NEPHILIM_NS_END
#endif // NephilimMusic_h__

