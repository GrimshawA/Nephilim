#include <Nephilim/DataStream.h>
#include <Nephilim/IODevice.h>
#include <Nephilim/Strings.h>

NEPHILIM_NS_BEGIN

/// Constructs a invalid data stream
DataStream::DataStream()
: m_device(NULL)
{

}

/// Constructs a data stream from a device
DataStream::DataStream(IODevice& device)
: m_device(&device)
{

}

/// Set the device of this data stream
void DataStream::setDevice(IODevice& device)
{
	m_device = &device;
}


/// Write a 64-bit integer
DataStream& DataStream::operator<<(Int64 value)
{
	if(m_device)
	{
		m_device->write(reinterpret_cast<const char*>(&value), sizeof(value));
	}
	return *this;
}

/// Write a String
DataStream& DataStream::operator<<(const String& value)
{
	if(m_device)
	{
		*this << static_cast<Int64>(value.length());
		m_device->write(value.c_str(), sizeof(char)*value.length());
	}
	return *this;
}

/// Read a 64-bit integer
DataStream& DataStream::operator>>(Int64& value)
{
	if(m_device)
	{
		m_device->read(reinterpret_cast<char*>(&value), sizeof(Int64));
	}
	return *this;
}

/// Read a String
DataStream& DataStream::operator>>(String& value)
{
	if(m_device)
	{
		Int64 length = 0;
		*this >> length;
		char* buffer = new char[length+1];
		m_device->read(buffer, length);
		buffer[length] = '\0';
		value = buffer;
	}
	return *this;
}

NEPHILIM_NS_END