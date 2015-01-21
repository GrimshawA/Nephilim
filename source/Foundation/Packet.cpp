#include <Nephilim/Packet.h>
#include "../Network/SocketImpl.hpp"

#include <iostream>
#include <string.h>
using namespace std;

NEPHILIM_NS_BEGIN

/// Start the empty packet
Packet::Packet(){
	m_readPos = 0;
};

/// Get the size in bytes of the buffer
std::size_t Packet::getDataSize() const{
	return m_data.size();
};

/// Get the data raw pointer
const void* Packet::getData() const{
	return &m_data[0];
};

/// Appends data to the buffer
void Packet::append(const void* data, std::size_t dataSize){
	if (data && (dataSize > 0))
	{
		std::size_t start = m_data.size();
		m_data.resize(start + dataSize);
		memcpy(&m_data[start], data, dataSize);
	}
};

/// Appends a char to the buffer
Packet& Packet::operator<<(char data){
	append(&data, sizeof(data));
	return *this;
};

/// Appends a float to the buffer
Packet& Packet::operator<<(float data){
	append(&data, sizeof(data));
	return *this;
};

/// Appends a Vec2f to the buffer
Packet& Packet::operator<<(const Vec2f& data){
	*this << data.x << data.y;
	return *this;
};

/// Appends a Int16 to the buffer
Packet& Packet::operator<<(Int16 data){
	Int16 toWrite = htons(data);
	append(&toWrite, sizeof(toWrite));
	return *this;
};

/// Appends a Uint32 to the buffer
Packet& Packet::operator<<(Uint32 data){
	Uint32 toWrite = htonl(data);
	append(&toWrite, sizeof(toWrite));
	return *this;
};

/// Appends a String to the buffer
Packet& Packet::operator<<(const String& data)
{
	// First insert string length
	Uint32 length = static_cast<Uint32>(data.size());
	*this << length;

	// Then insert characters
	if (length > 0)
	{
		append(data.c_str(), length * sizeof(std::string::value_type));
	}

	return *this;
}



/// Reads a char from the buffer current position
Packet& Packet::operator>>(char& data)
{
	if (m_readPos + sizeof(data) <= m_data.size())
	{
		data = *reinterpret_cast<const char*>(&m_data[m_readPos]);
		m_readPos += sizeof(data);
	}

	return *this;
};

/// Reads a float from the buffer current position
Packet& Packet::operator>>(float& data)
{
	if (m_readPos + sizeof(data) <= m_data.size())
	{
		data = *reinterpret_cast<const float*>(&m_data[m_readPos]);
		m_readPos += sizeof(data);
	}

	return *this;
};

/// Reads a Vec2f from the buffer current position
Packet& Packet::operator>>(Vec2f& data)
{
	if (m_readPos + sizeof(data) <= m_data.size())
	{
		*this >> data.x >> data.y;
	}

	return *this;
}

/// Reads a Int8 from the buffer current position
Packet& Packet::operator>>(Int8& data)
{
	if (m_readPos + sizeof(data) <= m_data.size())
	{
		data = *reinterpret_cast<const Int8*>(&m_data[m_readPos]);
		m_readPos += sizeof(data);
	}

	return *this;
}

/// Reads a Int16 from the buffer current position
Packet& Packet::operator>>(Int16& data)
{
	if (m_readPos + sizeof(data) <= m_data.size())
	{
		data = ntohs(*reinterpret_cast<const Int16*>(&m_data[m_readPos]));
		m_readPos += sizeof(data);
	}

	return *this;
};

/// Reads a Int32 from the buffer current position
Packet& Packet::operator>>(Int32& data)
{
	if (m_readPos + sizeof(data) <= m_data.size())
	{
		data = ntohl(*reinterpret_cast<const Int32*>(&m_data[m_readPos]));
		m_readPos += sizeof(data);
	}

	return *this;
}

/// Reads a Uint8 from the buffer current position
Packet& Packet::operator>>(Uint8& data)
{
	if (m_readPos + sizeof(data) <= m_data.size())
	{
		data = *reinterpret_cast<const Uint8*>(&m_data[m_readPos]);
		m_readPos += sizeof(data);
	}

	return *this;
}

/// Reads a Uint16 from the buffer current position
Packet& Packet::operator>>(Uint16& data)
{
	if (m_readPos + sizeof(data) <= m_data.size())
	{
		data = ntohs(*reinterpret_cast<const Uint16*>(&m_data[m_readPos]));
		m_readPos += sizeof(data);
	}

	return *this;
}

/// Reads a Uint32 from the buffer current position
Packet& Packet::operator>>(Uint32& data)
{
	if (m_readPos + sizeof(data) <= m_data.size())
	{
		data = ntohl(*reinterpret_cast<const Uint32*>(&m_data[m_readPos]));
		m_readPos += sizeof(data);
	}

	return *this;
};

/// Reads a String from the buffer current position
Packet& Packet::operator>>(String& data)
{
	// First extract string length
	Uint32 length = 0;
	*this >> length;

	data.clear();
	if ((length > 0) && (m_readPos + length*sizeof(String::value_type) <= m_data.size()))
	{
		// Then extract characters
		data.assign(&m_data[m_readPos], length);

		// Update reading position
		m_readPos += length;


	}

	return *this;
};

const void* Packet::onSend(std::size_t& size)
{
	size = getDataSize();
	return getData();
}

void Packet::onReceive(const void* data, std::size_t size)
{
	append(data, size);
}

/// Clear the contents
void Packet::clear()
{
	m_data.clear();
}

//////////////////////////////////////////////////////////////////////////
/*


/// Creates a packet
NetworkPacket::NetworkPacket(ENetEvent *event){
	myPacket = event->packet;
};

/// Destroy the packet, deallocate
NetworkPacket::~NetworkPacket(){
	enet_packet_destroy(myPacket);
};

/// Get the packet size in bytes
std::size_t NetworkPacket::getPacketSize(){
	return myPacket->dataLength;
};

/// Get as a string
String NetworkPacket::toString(){
	return String((char*)myPacket->data, myPacket->dataLength);
};

/// Get the packet as a raw array
void* NetworkPacket::getRawData(){
	return myPacket->data;
};

/// Get the packet as an SFML packet
Packet NetworkPacket::getData(){
	Packet p;
	p.append(myPacket->data, myPacket->dataLength);
	return p;
};
*/
NEPHILIM_NS_END