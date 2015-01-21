#include <Nephilim/Foundation/DataStream.h>
#include <Nephilim/Foundation/IODevice.h>
#include <Nephilim/Foundation/String.h>

#include <assert.h>
#include <stdio.h>

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

/// Read <size> bytes from the stream
void DataStream::read(void* destination, uint32_t size)
{
	assert(m_device);
	m_device->read(reinterpret_cast<char*>(destination), size);
}

/// Write a memory segment to the stream as-is
void DataStream::write(void* source, uint32_t size)
{
	assert(m_device);
	m_device->write(reinterpret_cast<char*>(source), size);
}

/// Write a uint32_t to the stream
void DataStream::write_uint32(uint32_t v)
{
	assert(m_device);
	m_device->write(reinterpret_cast<const char*>(&v), sizeof(v));
}


/// Reads the next byte as a char
char DataStream::readChar()
{
	char c = EOF;
	if(m_device)
	{
		m_device->read(&c, sizeof(char));
	}
	return c;
}

/// Reads count chars and stores them in the pre allocated buffer destination
void DataStream::readChars(int count, char* destination)
{
	if(m_device)
	{
		for(int i = 0; i < count; ++i)
		{
			m_device->read(&destination[i], sizeof(char));
		}
	}
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

/// Write a 64-bit signed integer
DataStream& DataStream::operator<<(Int32 value)
{
	if(m_device)
	{
		m_device->write(reinterpret_cast<const char*>(&value), sizeof(value));
	}
	return *this;
}

/// Write a 16-bit signed integer
DataStream& DataStream::operator<<(Int16 value)
{
	if(m_device)
	{
		m_device->write(reinterpret_cast<const char*>(&value), sizeof(value));
	}
	return *this;
}

/// Write a 8-bit signed integer
DataStream& DataStream::operator<<(Int8 value)
{
	if(m_device)
	{
		m_device->write(reinterpret_cast<const char*>(&value), sizeof(value));
	}
	return *this;
}

/// Write a 32-bit unsigned integer
DataStream& DataStream::operator<<(Uint32 value)
{
	if(m_device)
	{
		m_device->write(reinterpret_cast<const char*>(&value), sizeof(value));
	}
	return *this;
}

/// Write a boolean as a unsigned byte
DataStream& DataStream::operator<<(bool value)
{
	if(m_device)
	{
		Uint8 tempValue = static_cast<Uint8>(value);
		m_device->write(reinterpret_cast<const char*>(&tempValue), sizeof(tempValue));
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

/// Write a float
DataStream& DataStream::operator<<(float value)
{
	if(m_device)
	{
		m_device->write(reinterpret_cast<const char*>(&value), sizeof(value));
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

/// Read a 32-bit signed integer
DataStream& DataStream::operator>>(Int32& value)
{
	if(m_device)
	{
		m_device->read(reinterpret_cast<char*>(&value), sizeof(Int32));
	}
	return *this;
}

/// Read a 16-bit signed integer
DataStream& DataStream::operator>>(Int16& value)
{
	if(m_device)
	{
		m_device->read(reinterpret_cast<char*>(&value), sizeof(Int16));
	}
	return *this;
}

/// Read a 32-bit unsigned integer
DataStream& DataStream::operator>>(Uint32& value)
{
	if(m_device)
	{
		m_device->read(reinterpret_cast<char*>(&value), sizeof(Uint32));
	}
	return *this;
}

/// Read a 16-bit unsigned integer
DataStream& DataStream::operator>>(Uint16& value)
{
	if(m_device)
	{
		m_device->read(reinterpret_cast<char*>(&value), sizeof(Uint16));
	}
	return *this;
}

/// Read a 8-bit unsigned integer
DataStream& DataStream::operator>>(Uint8& value)
{
	if(m_device)
	{
		m_device->read(reinterpret_cast<char*>(&value), sizeof(Uint8));
	}
	return *this;
}

/// Read a 8-bit boolean
DataStream& DataStream::operator>>(bool& value)
{
	if(m_device)
	{
		Uint8 tempValue;
		m_device->read(reinterpret_cast<char*>(&tempValue), sizeof(Uint8));
		value = static_cast<bool>(tempValue);
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

/// Read a float
DataStream& DataStream::operator>>(float& value)
{
	if(m_device)
	{
		m_device->read(reinterpret_cast<char*>(&value), sizeof(float));
	}
	return *this;
}

NEPHILIM_NS_END
