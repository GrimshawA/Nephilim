#ifndef PARABOLA_STREAM_H
#define PARABOLA_STREAM_H

#include "Platform.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN

	/// Holds the modes a stream can be opened
	namespace StreamMode {
		enum AccessModes{
			ReadOnly = 0,
			WriteOnly,
			AppendOnly,
			ReadWrite,
			WriteRead,
			AppendRead,
			Unknown
		};
	};

	/**
		\class DataStream
		\brief Base class for data streams.

		DataStream defines a common interface for all data sources/destinations to extend.

		Specifically, an abstract DataStream is able to write and read bytes, as well as write and read a few basic types.

		This implementation of streams overloads the operators >> and << to read and write some predefined types.

		When implementing an actual stream, any of the virtual functions or operators can be implemented.
		The goal is that every stream has a common interface, allowing data to be sent/received the same
		way from different streams like:

		- Strings
		- Network socket
		- Files
		- Etc.
		
		\todo Finish the interface.
	*/	
	class PARABOLA_API DataStream{
	public:

		/// Virtual method to check if the stream reached its end
		/// Not all streams may support this type of checking, so it is not purely virtual
		virtual bool atEnd(){return true;};

		/// Virtual output operator using operator<< . Multiple Types allowed.
		virtual DataStream& operator<<(const String &value){return *this;};

		/// Virtual input operator using operator>> . Multiple Types allowed.
		virtual DataStream& operator>>(String &value){return *this;};
	};

PARABOLA_NAMESPACE_END

#endif