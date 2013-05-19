#ifndef DataStream_h__
#define DataStream_h__

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

	/// Write a 64-bit integer
	DataStream& operator<<(Int64 value);

	/// Write a String
	DataStream& operator<<(const String& value);

	/// Write a float
	DataStream& operator<<(float value);

	/// Read a 64-bit integer
	DataStream& operator>>(Int64& value);

	/// Read a String
	DataStream& operator>>(String& value);

	/// Read a float
	DataStream& operator>>(float& value);

private:
	IODevice* m_device; ///< The device of the stream
};

NEPHILIM_NS_END
#endif // DataStream_h__
