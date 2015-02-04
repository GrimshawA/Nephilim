#ifndef NephilimSoundFormatWAV_h__
#define NephilimSoundFormatWAV_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

	typedef struct {
		char  riff[4];//'RIFF'
		unsigned int riffSize;
		char  wave[4];//'WAVE'
		char  fmt[4];//'fmt '
		unsigned int fmtSize;
		unsigned short format;
		unsigned short channels;
		unsigned int samplesPerSec;
		unsigned int bytesPerSec;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char  data[4];//'data'
		unsigned int dataSize;
}BasicWAVEHeader;

//WARNING: This Doesn't Check To See If These Pointers Are Valid
char* readWAV(String filename,BasicWAVEHeader* header);

/**
	\ingroup Audio
	\class SoundFormatWAV
	\brief Parses WAV files
*/
class NEPHILIM_API SoundFormatWAV
{
public:
	
};

NEPHILIM_NS_END
#endif // NephilimSoundFormatWAV_h__
