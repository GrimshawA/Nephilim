#include <SFMLAudioCode/SoundFormatWAV.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/File.h>

#include <string.h>

NEPHILIM_NS_BEGIN
//WARNING: This Doesn't Check To See If These Pointers Are Valid
char* readWAV(String filename,BasicWAVEHeader* header)
{
	char* buffer = 0;
	File file(filename, IODevice::BinaryRead);
	if (!file)
	{
		return 0;
	}

	if ( file.read(reinterpret_cast<char*>(header), sizeof(BasicWAVEHeader)))
	{
		if (!(//these things *must* be valid with this basic header
			memcmp("RIFF",header->riff,4) ||
			memcmp("WAVE",header->wave,4) ||
			memcmp("fmt ",header->fmt,4)  ||
			memcmp("data",header->data,4)
			)){
				Log("WAV Loader: %d buffer", header->dataSize);
				buffer = new char[header->dataSize];
				if (buffer)
				{
					if (file.read(buffer,header->dataSize))
					{
						return buffer;
					}
					delete[] buffer;
				}
		}
	}
	return 0;
}

NEPHILIM_NS_END
