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

#ifndef NephilimSoundRecorder_h__
#define NephilimSoundRecorder_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Thread.h>

#include <vector>

NEPHILIM_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////
/// \brief Abstract base class for capturing sound data
///
////////////////////////////////////////////////////////////////////////////////
class NEPHILIM_API SoundRecorder
{
public :

    ////////////////////////////////////////////////////////////////////////////
    /// \brief destructor
    ///
    ////////////////////////////////////////////////////////////////////////////
    virtual ~SoundRecorder();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Start the capture
    ///
    /// The \a sampleRate parameter defines the number of audio samples
    /// captured per second. The higher, the better the quality
    /// (for example, 44100 samples/sec is CD quality).
    /// This function uses its own thread so that it doesn't block
    /// the rest of the program while the capture runs.
    /// Please note that only one capture can happen at the same time.
    ///
    /// \param sampleRate Desired capture rate, in number of samples per second
    ///
    /// \see stop
    ///
    ////////////////////////////////////////////////////////////////////////////
    void start(unsigned int sampleRate = 44100);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Stop the capture
    ///
    /// \see start
    ///
    ////////////////////////////////////////////////////////////////////////////
    void stop();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get the sample rate
    ///
    /// The sample rate defines the number of audio samples
    /// captured per second. The higher, the better the quality
    /// (for example, 44100 samples/sec is CD quality).
    ///
    /// \return Sample rate, in samples per second
    ///
    ////////////////////////////////////////////////////////////////////////////
    unsigned int getSampleRate() const;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Check if the system supports audio capture
    ///
    /// This function should always be called before using
    /// the audio capture features. If it returns false, then
    /// any attempt to use sf::SoundRecorder or one of its derived
    /// classes will fail.
    ///
    /// \return True if audio capture is supported, false otherwise
    ///
    ////////////////////////////////////////////////////////////////////////////
    static bool isAvailable();

protected :

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// This constructor is only meant to be called by derived classes.
    ///
    ////////////////////////////////////////////////////////////////////////////
    SoundRecorder();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Start capturing audio data
    ///
    /// This virtual function may be overriden by a derived class
    /// if something has to be done every time a new capture
    /// starts. If not, this function can be ignored; the default
    /// implementation does nothing.
    ///
    /// \return True to start the capture, or false to abort it
    ///
    ////////////////////////////////////////////////////////////////////////////
    virtual bool onStart();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Process a new chunk of recorded samples
    ///
    /// This virtual function is called every time a new chunk of
    /// recorded data is available. The derived class can then do
    /// whatever it wants with it (storing it, playing it, sending
    /// it over the network, etc.).
    ///
    /// \param samples     Pointer to the new chunk of recorded samples
    /// \param sampleCount Number of samples pointed by \a samples
    ///
    /// \return True to continue the capture, or false to stop it
    ///
    ////////////////////////////////////////////////////////////////////////////
    virtual bool onProcessSamples(const Int16* samples, std::size_t sampleCount) = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Stop capturing audio data
    ///
    /// This virtual function may be overriden by a derived class
    /// if something has to be done every time the capture
    /// ends. If not, this function can be ignored; the default
    /// implementation does nothing.
    ///
    ////////////////////////////////////////////////////////////////////////////
    virtual void onStop();

private :

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Function called as the entry point of the thread
    ///
    /// This function starts the recording loop, and returns
    /// only when the capture is stopped.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void record();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get the new available audio samples and process them
    ///
    /// This function is called continuously during the
    /// capture loop. It retrieves the captured samples and
    /// forwards them to the derived class.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void processCapturedSamples();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Clean up the recorder's internal resources
    ///
    /// This function is called when the capture stops.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void cleanup();

    ////////////////////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////////////////////
    Thread             m_thread;      ///< Thread running the background recording task
    std::vector<Int16> m_samples;     ///< Buffer to store captured samples
    unsigned int       m_sampleRate;  ///< Sample rate
    bool               m_isCapturing; ///< Capturing state
};

NEPHILIM_NS_END
#endif // NephilimSoundRecorder_h__
