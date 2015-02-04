////////////////////////////////////////////////////////////////////////////////
// SFML Derived Code - Check their license
////////////////////////////////////////////////////////////////////////////////

#include <SFMLAudioCode/SoundBuffer.h>
#include <SFMLAudioCode/Sound.h>
#include <Nephilim/Foundation/File.h>
#include <Nephilim/Foundation/Logging.h>
#include <SFMLAudioCode/SoundFormatWAV.h>

#include "ALCheck.hpp"
#include "SoundFile.h"
#include "AudioDevice.hpp"

#include <memory>

NEPHILIM_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////
SoundBuffer::SoundBuffer()
: m_buffer  (0)
, m_duration()
{
    priv::ensureALInit();

    // Create the buffer
    alCheck(alGenBuffers(1, &m_buffer));
}


////////////////////////////////////////////////////////////////////////////////
SoundBuffer::SoundBuffer(const SoundBuffer& copy) :
m_buffer  (0),
m_samples (copy.m_samples),
m_duration(copy.m_duration),
m_sounds  () // don't copy the attached sounds
{
    // Create the buffer
    alCheck(alGenBuffers(1, &m_buffer));

    // Update the internal buffer with the new samples
    update(copy.getChannelCount(), copy.getSampleRate());
}


////////////////////////////////////////////////////////////////////////////////
SoundBuffer::~SoundBuffer()
{
    // First detach the buffer from the sounds that use it (to avoid OpenAL errors)
    for (SoundList::const_iterator it = m_sounds.begin(); it != m_sounds.end(); ++it)
        (*it)->resetBuffer();

    // Destroy the buffer
    if (m_buffer)
        alCheck(alDeleteBuffers(1, &m_buffer));
}

bool SoundBuffer::loadFromFile(const String& filename)
{
    priv::SoundFile file;
    if (file.openRead(filename))
	{
        return initialize(file);
	}
    else
	{
		return false;
	}

	// trick to load directly a wav
	/*BasicWAVEHeader header;
	char* data = readWAV(filename,&header);
	if(data)
	{ 
		Log("WAV just loaded sucessfully");
		if(header.bitsPerSample == 16)
		{
			Log("16 bits samples");
			loadFromSamples(reinterpret_cast<Int16*>(data), header.dataSize / 2, header.channels, header.samplesPerSec);

		}
		Log("Passed WAV Samples to sound buffer");
		return true;
	}
	else
		return false;*/
}


////////////////////////////////////////////////////////////////////////////////
bool SoundBuffer::loadFromMemory(const void* data, std::size_t sizeInBytes)
{
    priv::SoundFile file;
    if (file.openRead(data, sizeInBytes))
        return initialize(file);
    else
        return false;
}


////////////////////////////////////////////////////////////////////////////////
bool SoundBuffer::loadFromStream(File& stream)
{
    priv::SoundFile file;
    if (file.openRead(stream))
        return initialize(file);
    else
        return false;
}


////////////////////////////////////////////////////////////////////////////////
bool SoundBuffer::loadFromSamples(const Int16* samples, std::size_t sampleCount, unsigned int channelCount, unsigned int sampleRate)
{
    if (samples && sampleCount && channelCount && sampleRate)
    {
        // Copy the new audio samples
        m_samples.assign(samples, samples + sampleCount);

        // Update the internal buffer with the new samples
        return update(channelCount, sampleRate);
    }
    else
    {
        // Error...
        Log("Failed to load sound buffer from samples (array: %x, count: %d, channels: %d, sampleRate: %d)", samples, sampleCount, channelCount, sampleRate);
        return false;
    }
}


////////////////////////////////////////////////////////////////////////////////
bool SoundBuffer::saveToFile(const std::string& filename) const
{
    // Create the sound file in write mode
    priv::SoundFile file;
    if (file.openWrite(filename, getChannelCount(), getSampleRate()))
    {
        // Write the samples to the opened file
        file.write(&m_samples[0], m_samples.size());
        return true;
    }
    else
    {
        return false;
    }
}


////////////////////////////////////////////////////////////////////////////////
const Int16* SoundBuffer::getSamples() const
{
    return m_samples.empty() ? NULL : &m_samples[0];
}


////////////////////////////////////////////////////////////////////////////////
std::size_t SoundBuffer::getSampleCount() const
{
    return m_samples.size();
}


////////////////////////////////////////////////////////////////////////////////
unsigned int SoundBuffer::getSampleRate() const
{
    ALint sampleRate;
    alCheck(alGetBufferi(m_buffer, AL_FREQUENCY, &sampleRate));

    return sampleRate;
}


////////////////////////////////////////////////////////////////////////////////
unsigned int SoundBuffer::getChannelCount() const
{
    ALint channelCount;
    alCheck(alGetBufferi(m_buffer, AL_CHANNELS, &channelCount));

    return channelCount;
}


////////////////////////////////////////////////////////////////////////////////
Time SoundBuffer::getDuration() const
{
    return m_duration;
}


////////////////////////////////////////////////////////////////////////////////
SoundBuffer& SoundBuffer::operator =(const SoundBuffer& right)
{
    SoundBuffer temp(right);

    std::swap(m_samples,  temp.m_samples);
    std::swap(m_buffer,   temp.m_buffer);
    std::swap(m_duration, temp.m_duration);
    std::swap(m_sounds,   temp.m_sounds); // swap sounds too, so that they are detached when temp is destroyed

    return *this;
}


////////////////////////////////////////////////////////////////////////////////
bool SoundBuffer::initialize(priv::SoundFile& file)
{
    // Retrieve the sound parameters
    std::size_t  sampleCount  = file.getSampleCount();
    unsigned int channelCount = file.getChannelCount();
    unsigned int sampleRate   = file.getSampleRate();

    // Read the samples from the provided file
    m_samples.resize(sampleCount);
    if (file.read(&m_samples[0], sampleCount) == sampleCount)
    {
        // Update the internal buffer with the new samples
        return update(channelCount, sampleRate);
    }
    else
    {
        return false;
    }
}


////////////////////////////////////////////////////////////////////////////////
bool SoundBuffer::update(unsigned int channelCount, unsigned int sampleRate)
{
    // Check parameters
    if (!channelCount || !sampleRate || m_samples.empty())
        return false;

    // Find the good format according to the number of channels
    ALenum format = priv::AudioDevice::getFormatFromChannelCount(channelCount);

    // Check if the format is valid
    if (format == 0)
    {
      //  err() << "Failed to load sound buffer (unsupported number of channels: " << channelCount << ")" << std::endl;
        return false;
    }

    // Fill the buffer
    ALsizei size = static_cast<ALsizei>(m_samples.size()) * sizeof(Int16);
    alCheck(alBufferData(m_buffer, format, &m_samples[0], size, sampleRate));

    // Compute the duration
    m_duration = Time::fromMiliSeconds(1000 * m_samples.size() / sampleRate / channelCount);

    return true;
}


////////////////////////////////////////////////////////////////////////////////
void SoundBuffer::attachSound(Sound* sound) const
{
    m_sounds.insert(sound);
}


////////////////////////////////////////////////////////////////////////////////
void SoundBuffer::detachSound(Sound* sound) const
{
    m_sounds.erase(sound);
}

NEPHILIM_NS_END
