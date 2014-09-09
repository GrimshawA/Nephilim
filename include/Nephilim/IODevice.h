#ifndef PARABOLA_IODEVICE_H
#define PARABOLA_IODEVICE_H

#include <Nephilim/Platform.h>
#include "Strings.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Foundation
	\class IODevice
	\brief Base class for input/output devices, such as files and network sockets.

*/
class NEPHILIM_API IODevice{
public:
	/// Virtual function for all devices to check for the end of read
	virtual bool atEnd() = 0;

	/// Virtual function for all devices to read the next char, can return EOF in some cases
	virtual char getChar() = 0;

	/// Virtual function for all devices to seek reading data
	virtual bool seek(Int64 offset, int origin) = 0;

	/// Virtual function for all devices to query if the device is available to read/write
	virtual bool isReady() = 0;

	/// Virtual function for all devices to write a byte buffer
	virtual Int64 write(const char* buffer, Int64 length) const = 0;

	/// Reads raw data from the stream with size len, stored in the buffer, it protects the reading of protected sections
	/// Returns the amount of bytes read
	virtual Int64 read(char* buffer, Int64 len) const = 0;

	/// Possible modes for opening a device
	enum OpenModes{
		TextRead = 0, ///< Read mode for text files
		TextWrite,	///< Write mode for text files
		BinaryRead, ///< Read mode for binary files
		BinaryWrite ///< Write mode for binary files
	};
};

NEPHILIM_NS_END
#endif