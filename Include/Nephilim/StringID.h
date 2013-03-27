#ifndef PARABOLA_STRINGID_H
#define PARABOLA_STRINGID_H

#include "Platform.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN
	typedef unsigned long StringID;

		/**
			\function makeStringID
			\brief Transforms a String in its equivalent CRC32 Hash.

			\todo rename and neat up

			By default, the engine keeps record of the String-Hash matches to provide a way to transform a Hash into a String back again.

			However, if you will not need to ever convert the String to the Hash again, you should disable this and save performance:
			@param KeepRecord Set to false to avoid posting the String in the Hash Table.
		*/
		PARABOLA_API StringID makeStringID(const String &Name, bool KeepRecord = true);

		/**
			\function getStringFromStringID
			\brief Looks up the Hash for a String match for backward conversion.

			@param ID The Hash to get the String from.
			@return Returns the correct String if it was stored before in the Hash Table,
					otherwise it returns an empty string.
		*/
		PARABOLA_API String getStringFromStringID(StringID ID);

	
PARABOLA_NAMESPACE_END

#endif