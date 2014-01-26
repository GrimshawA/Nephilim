#ifndef NephilimDataStream_h__
#define NephilimDataStream_h__

#include "Platform.h"

NEPHILIM_NS_BEGIN

class IODevice;
class String;

/**
	\ingroup Foundation
	\class DataStream
	\brief Inputs and outputs data to any IODevice
*/
class NEPHILIM_API DataStream
{
public:
	/// Constructs a invalid data stream
	DataStream();

	/// Constructs a data stream from a device
	DataStream(IODevice& device);

	/// Set the device of this data stream
	void setDevice(IODevice& device);

	/// Reads the next byte as a char
	char readChar();

	/// Reads count chars and stores them in the pre allocated buffer destination
	void readChars(int count, char* destination);

	/// Write a 64-bit signed integer
	DataStream& operator<<(Int64 value);

	/// Write a 32-bit signed integer
	DataStream& operator<<(Int32 value);

	/// Write a 16-bit signed integer
	DataStream& operator<<(Int16 value);

	/// Write a 8-bit signed integer
	DataStream& operator<<(Int8 value);

	/// Write a 32-bit unsigned integer
	DataStream& operator<<(Uint32 value);

	/// Write a boolean as a unsigned byte
	DataStream& operator<<(bool value);

	/// Write a String
	DataStream& operator<<(const String& value);

	/// Write a float
	DataStream& operator<<(float value);

	/// Read a 64-bit signed integer
	DataStream& operator>>(Int64& value);

	/// Read a 32-bit signed integer
	DataStream& operator>>(Int32& value);

	/// Read a 16-bit signed integer
	DataStream& operator>>(Int16& value);

	/// Read a 32-bit unsigned integer
	DataStream& operator>>(Uint32& value);

	/// Read a 8-bit boolean
	DataStream& operator>>(bool& value);

	/// Read a 16-bit unsigned integer
	DataStream& operator>>(Uint16& value);

	/// Read a 8-bit unsigned integer
	DataStream& operator>>(Uint8& value);

	/// Read a String
	DataStream& operator>>(String& value);

	/// Read a float
	DataStream& operator>>(float& value);

private:
	IODevice* m_device; ///< The device of the stream
};

NEPHILIM_NS_END
#endif // NephilimDataStream_h__
