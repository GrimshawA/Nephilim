#ifndef PARABOLA_CRC32_H
#define PARABOLA_CRC32_H

#include "Platform.h"

PARABOLA_NAMESPACE_BEGIN

	/**
		\ingroup Foundation
		\class CRC32
		\brief Utility class to make CRC32 hashes of your data.
		\todo tidy up a bit

		Using this you can easily generate a unique hash for your data array.
	*/
	class PARABOLA_API CRC32
	{
	private:
		unsigned long LookupTable[256];
		unsigned long Reflect(unsigned long Reflect, char Char);
	public:
		static CRC32 Instance;

		/// Constructs the default instance
		CRC32();

		/**
			\brief Computes the CRC32 hash of the data.

			\param Data array to get the hash from
			\param Size of the data array
		*/
		unsigned long CRC(const unsigned char *Data, unsigned long DataLength);
	};

PARABOLA_NAMESPACE_END
#endif