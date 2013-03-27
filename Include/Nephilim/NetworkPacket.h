#ifndef PARABOLA_NETWORKPACKET_H
#define PARABOLA_NETWORKPACKET_H

#include "Platform.h"
#include "NetworkSocket.h"
#include "Strings.h"
#include <enet/enet.h>
#include <vector>
#include "Vectors.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Network
	\class Packet
	\brief Allows to pack and unpack data for network transfer
*/
class Packet{
public:
	/// Start the empty packet
	Packet();

	/// Appends data to the buffer
	void append(const void* data, std::size_t dataSize);

	/// Get the size in bytes of the buffer
	std::size_t getDataSize() const;

	/// Get the data raw pointer
	const void* getData() const;

	
	/// Appends a char to the buffer
	Packet& operator<<(char data);

	/// Appends a float to the buffer
	Packet& operator<<(float data);

	/// Appends a Vec2f to the buffer
	Packet& operator<<(const Vec2f& data);

	/// Appends a Int16 to the buffer
	Packet& operator<<(Int16 data);

	/// Appends a Uint32 to the buffer
	Packet& operator<<(Uint32 data);

	/// Appends a String to the buffer
	Packet& operator<<(const String& data);




	/// Reads a char from the buffer current position
	Packet& operator>>(char& data);

	/// Reads a float from the buffer current position
	Packet& operator>>(float& data);

	/// Reads a Vec2f from the buffer current position
	Packet& operator>>(Vec2f& data);

	/// Reads a Int16 from the buffer current position
	Packet& operator>>(Int16& data);

	/// Reads a Uint32 from the buffer current position
	Packet& operator>>(Uint32& data);

	/// Reads a String from the buffer current position
	Packet& operator>>(String& data);


private:
	/// The data buffer of the packet
	std::vector<char> m_data;
	/// The reading offset
	std::size_t m_readPos;
};

/**
	\ingroup Network
	\class NetworkPacket
	\brief Holds temporarily an Enet packet, and allows to retrieve the data

	\warning This class' objects are only valid during the callback
*/
class PARABOLA_API NetworkPacket{
public:
	/// Creates a packet
	NetworkPacket(ENetEvent *event);

	/// Destroy the packet, deallocate
	~NetworkPacket();

	/// Get the packet size in bytes
	size_t getPacketSize();

	/// Get the packet as a raw array
	void* getRawData();

	/// Get as a string
	String toString();

	/// Get the packet as an SFML packet
	Packet getData();

private:
	ENetPacket *myPacket;
};
PARABOLA_NAMESPACE_END
#endif