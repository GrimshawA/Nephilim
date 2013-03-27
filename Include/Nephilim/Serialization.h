#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "Platform.h"
#include <string>
#include <vector>

using namespace std;

namespace pE{

	class FileStream;

	/**
		\class Serializable
		\brief Base class for any object that needs to be serialized to a file.

		Just overload its methods with the custom read/write code, and you get a serializable class.

	*/
	class PARABOLA_API Serializable{
	public:
		virtual unsigned long WriteObject(FileStream &Stream);
		virtual unsigned long ReadObject(FileStream &Stream);
		virtual unsigned long SizeOf();

	private:

	};

	namespace Serialization{
		PARABOLA_API unsigned long SizeOf(string &Str);
	};
};

#endif